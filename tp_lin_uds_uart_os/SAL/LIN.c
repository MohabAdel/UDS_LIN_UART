/*
 * LIN.c
 *
 */

#include "LIN.h"
//#include "NIVCInteruptHandler.h"
//#include "APP/LINConfig.h"

extern const uint8 SizeofSlaveID;
extern const IDInfo_t SlaveIDTable[];

static TypesOfLINError_t TypeOfError = NO_ERROR;
static  uint8 DataRec[8];
static  uint8 *DataSent;
static	uint8 NumOFDatatoRec  = 0;
static  uint8 NumOFDatatosent = 0;
static  uint8 CurrentidxOfincomingData = 0;
static  uint8 idx = 0;
static LINState_t Statues = WaitForNextRequest;

static void ProccessTheIncommingByte(uint8 recData)
{
	switch(Statues)
	{
		case WaitForNextRequest:
		{
			if(recData == 0x80){
				Statues = SleepMode;
			}else if(recData == 0x00){
				Statues =  BreakFirstByte;
			}else{
				TypeOfError = SYNCH_BREAK_ERROR;
			}
			break;
		}
		case BreakFirstByte:
		{
			if(recData == 0x07){
				Statues = BreakSecondByte;
			}else{
				TypeOfError = SYNCH_BREAK_ERROR;
			}
			break;
		}
		case BreakSecondByte:
		{
			if(recData == 0x55){
				Statues =  SynchByte;
			}else{
				TypeOfError = SYNCH_BREAK_ERROR;
			}
			break;
		}
		case SynchByte:
		{
			Statues = WaitForNextRequest;
			int i;
			recData <<= 4;
			recData >>= 4;
			for(i = 0;i < SizeofSlaveID;i++)
			{
				if(SlaveIDTable[i].Info.Identifier == recData){
					Statues = Identifier;
					break;
				}else{

				}
			}
			if(Statues == Identifier){
				if(SlaveIDTable[i].Info.dir == ID_DATARECIVE){
					idx = i;
					NumOFDatatoRec = SlaveIDTable[i].Info.length;
					Statues = StoreincomingData;
				}else{
					NumOFDatatosent = SlaveIDTable[i].Info.length;
					DataSent = SlaveIDTable[i].DataSent();
					for(i = 0;i < NumOFDatatosent;i++)
					{
						//UART_SentData(DataSent[i]);
					}
					uint32 Sum = 0,i;
					for(i = 0;i < NumOFDatatoRec;i++)
					{
						Sum += DataRec[i];
					}
					Sum = Sum % 256;
					Sum = ~Sum;
					//UART_SentData((uint8)Sum);
				}
			}else{

			}
			break;
		}
		case StoreincomingData:
		{
			DataRec[CurrentidxOfincomingData++] = recData;
			if(CurrentidxOfincomingData == NumOFDatatoRec){
				Statues =  CheckSum;
				CurrentidxOfincomingData = 0;
				SlaveIDTable[idx].DataReceived(DataRec);
			}else{

			}
			break;
		}
		case CheckSum:
		{
			Statues =  WaitForNextRequest;
			uint32 Sum = 0,i;
			for(i = 0;i < NumOFDatatoRec;i++)
			{
				Sum += DataRec[i];
			}
			Sum = Sum % 256;
			Sum = ~Sum;
			if(Sum != recData){
				TypeOfError = CHECKSUM_ERROR;
			}else{

			}
			break;
		}
		case SleepMode:
		{
			if(recData == 0x80){
				Statues =  WaitForNextRequest;
			}else{
				Statues = SleepMode;
			}
			break;
		}
		default :
		{
			TypeOfError = DATA_RECEIVED;
			break;
		}
	}
}
void UART_RX_ISR()
{
	/*Note :
	 * Change the next line .
	 * asm
	 * */
	uint8 recByte = 0;
	ProccessTheIncommingByte(recByte);
}
TypesOfLINError_t ErrorDetect(void)
{
	TypesOfLINError_t ret = TypeOfError;
	TypeOfError = NO_ERROR;
	return ret;
}
TypesOfLINError_t InitLINSlave(g_ISRVirIdx_t USED_UART)
{
	TypesOfLINError_t ret = NO_ERROR;
	installNIVCISRFunction(USED_UART,UART_RX_ISR);
	return ret;
}
#ifdef MASTER
extern const Header_t MasterIDTable[];
extern const uint8 SizeofMasterID;
extern const uint32 TSlot;

static uint32 Count = 0;
static uint32 numTslot[MAXNUMBEROFSLAVE];
static uint8  tempHeader[4];
static uint8  CurrentNode = 0;

static void AuxISR(void)
{
	if(Count == numTslot[CurrentNode]){
		Count = 0;
		CurrentNode++;
		if(CurrentNode == SizeofMasterID){
			CurrentNode = 0;
		}else{
			//Empty
		}
	}else{
		Count++;
	}
	//__asm("MSR {r15},{r4}\n");
}
void LIN_Timer_ISR(void)
{
	//__asm("POP {r4} \nPUSH {r3}\n");
	AuxISR();
}
TypesOfLINError_t LIN_InitMaster(g_ISRVirIdx_t Used_Timer,g_ISRVirIdx_t USED_UART)
{
	TypesOfLINError_t ret = NO_ERROR;
	uint32 i;
	for(i = 0;i < SizeofMasterID;i++)
	{
		numTslot[i] =  1 + ((1.4 * ((MasterIDTable[i].length + 4) * (BUDERATE / 8)) / 1000) / TSlot);
	}
	tempHeader[0] = 0x00;
	tempHeader[1] = 0x07;
	tempHeader[2] = 0x55;
	installNIVCISRFunction(Used_Timer,LIN_Timer_ISR);
	InitLINSlave(USED_UART);
	return ret;
}
static itsOK_t SendHeader(Header_t id)
{
	itsOK_t ret = TRUE;
	int i;
	tempHeader[3] = id.ID;
	if(id.ID != 0x80){
		switch(id.length)
		{
			case _2ByteMode :
			{
				break;
			}
			case _4ByteMode :
			{
				tempHeader[3] |= (1 << 5);
				break;
			}
			case _8ByteMode :
			{
				tempHeader[3] |= (1 << 5);
				tempHeader[3] |= (1 << 4);
				break;
			}
			default :
			{
				ret = FALSE;
			}
		}
		if((tempHeader[3] & 1) ^ ((tempHeader[3] >> 1) & 1) ^ ((tempHeader[3] >> 2) & 1) ^ ((tempHeader[3] >> 4) & 1)){
			tempHeader[3] |= (1 << 6);
		}else{

		}
		if(((tempHeader[3] >> 3) & 1) ^ ((tempHeader[3] >> 1) & 1) ^ ((tempHeader[3] >> 5) & 1) ^ ((tempHeader[3] >> 4) & 1)){
			tempHeader[3] |= (1 << 7);
		}else{

		}
		for(i = 0;i < 4;i++)
		{
			//UART_TX(tempHeader[i]);
		}
	}else{
		//UART_TX(0x80);
	}
	return ret;
}
TypesOfLINError_t LIN_SendWakeUpSignal(void)
{
	TypesOfLINError_t ret = NO_ERROR;
	Header_t temp = {0x80,_0ByteMode};
	SendHeader(temp);
	return ret;
}
TypesOfLINError_t LIN_SendSleepSignal(void)
{
	TypesOfLINError_t ret = NO_ERROR;
	Header_t temp = {0x80,_0ByteMode};
	SendHeader(temp);
	return ret;
}
#endif

	/*
	 * No thing to Write here because -> Master node have slave Task like slave node.
	 */
#ifdef SLAVE

#endif
