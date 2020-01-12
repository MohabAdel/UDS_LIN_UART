/*
 * tp_transiver.c
 *
 *  Created on: Sep 9, 2017
 *      Author: Mohab Adel
 */

#include "tp_transiver.h"
//#define DEBUG


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode


void TP_UART_Default_Interrupt_Task(void);
void TP_Sender_TX_RX_Handler(void);
void TP_Receiver_TX_RX_Handler(void);
#define FFrame_DataSize	6
#define ConFrame_DataSize 7 
 
#define FF_ID				0x10	//Frist Frame
#define FC_ID				0x30  //FlowControl
#define COF_ID			0x21	//Cons. Frame
#define COF_ID_END  0x3F  //
static void send_single_frame(uint8 * buffer, uint8 len);
static void send_first_frame(uint8 * buffer, uint8 len);
static void send_cons_frame(uint8 * buffer, uint8 numConFrame, uint8 stMin);

static int32_t NewSwData;   //semaphore
static int32_t NewReceData;
static int32_t Peripheral_Mutex;
static uint8 currentDataposition = 0;
static gCFrame_t c_frame_T;

void tp_Init(void){
	OS_InitSemaphore(&NewSwData,0);
	OS_InitSemaphore(&NewReceData,0);
	OS_InitSemaphore(&Peripheral_Mutex,1);
	UART_Init(115200);
	installNIVCISRFunction(UART0,TP_UART_Default_Interrupt_Task);
	
}


void tp_sender(uint8_t *buffer, uint8 len){
    /*single frame*/
	  OS_Wait(&Peripheral_Mutex);
	  installNIVCISRFunction(UART0,TP_Sender_TX_RX_Handler);
    if (len < 8)
    {
        send_single_frame(buffer, len);
    }
    /*Con Frame*/
/*
#ifdef  UART0
		//os_wait(&UART_Mutex);
	
		//installNIVCISRFunction(UART0,TP_Sender_TX_RX_UART_Handler);
		
#endif
		#ifdef CAN
		 //install(CAN0,TP_Sender_TX_RX_CAN_Handler);
		#endif
*/
	
    else if (len > 7)
			
    {
			  //OS_InitSemaphore(&NewSwData,0);
        send_first_frame(buffer, len);
			
			
				
			   
			 
        gFlowFrame_t flowBuffer;
        c_frame_T.ID = COF_ID;
        while (currentDataposition < len)
        {
            /*ISR Routine using RTOS for 50 ms MAX waiting */
					  OS_Wait(&NewSwData);
            CAN_RX((uint8_t*) &flowBuffer);
            if (flowBuffer.ID == FC_ID)
            {
                if (0 == flowBuffer.NumberFrames)
                {
                    send_cons_frame(buffer, len - currentDataposition,
                                    flowBuffer.stMin);
									
                }
                else
                {
                    send_cons_frame(buffer, (flowBuffer.NumberFrames * 7),
                                    flowBuffer.stMin);
									  
                }

            }
            else
            {
                /*Do nothing*/
            }
        }

    }
		deInstallNIVCISRFunction(UART0);
		OS_Signal(&Peripheral_Mutex);
		
}

static void send_single_frame(uint8 * buffer, uint8 len)
{
    gSFrame_t s_frame;
    s_frame.DLC = len;
    uint8 index = 0;
    for (index = 0; index < len; index++)
    {
        s_frame.data[index] = buffer[index];
    }
    CAN_TX((uint8_t*) &s_frame);
		
		//LIN_TX();
}

static void send_first_frame(uint8 * buffer, uint8 len)
{
    /*send first frame*/

    gFFrame_t f_frame;

    f_frame.ID = FF_ID;
    f_frame.DLC = len;
    uint8 index = 0;
    for (index = 0; index < FFrame_DataSize; index++)
    {
        f_frame.data[index] = buffer[index];
    }
    CAN_TX((uint8*) &f_frame);
		currentDataposition = FFrame_DataSize;
}

static void send_cons_frame(uint8 * buffer, uint8 dataSize, uint8 stMin)
{
  
   
    
    uint8 counter = 0;
    uint8 index;
    for (index = currentDataposition;
            index < (currentDataposition + (dataSize)); index++)
    {
        c_frame_T.data[counter] = buffer[index];
        counter++;
        if (counter == ConFrame_DataSize || ((currentDataposition + dataSize) - 1 == index))
        {
            
            CAN_TX((uint8*) &c_frame_T);
				   	c_frame_T.ID++;
            counter = 0;
            if (c_frame_T.ID == COF_ID_END)
            {
                c_frame_T.ID = COF_ID;
            }
            
						for(int i= 0; i< ConFrame_DataSize ;i++){
							c_frame_T.data[i]=0;
						}
						/* wait stMin */
						OS_Sleep(stMin);
        }
				if(((currentDataposition + dataSize) - 1 == index)){
					break;
				}
				
    }
    currentDataposition = index+1;
}


/******************* Functions Prototypes *******************/
g_frametype_t static Check_Frame_type(void);
void static send_Control_Frame(uint8_t BLockS, uint8_t stMin);
uint8 static generate_BS_decision(uint8_t RemaingBytes);
uint8 static Get_remaing_frames_number(uint8 RemaingBytes);
static uint8_t InFrame[8];


/******************* tp_receiver *******************/
void tp_receiver(uint8 *Mainbuffer,uint8 *Datalen){ //interrupt from physical layer UART INput
	 OS_Wait(&Peripheral_Mutex);
	 installNIVCISRFunction(UART0,TP_Receiver_TX_RX_Handler);
	#ifdef DEBUG
	 static uint8 Data[34];
	#endif
	//single Frame
	OS_Wait(&NewReceData); //signaled from uart_rx_handler
	g_frametype_t FrameType;
	
	FrameType = Check_Frame_type();
	/***************** Single Frame *****************/
	if(FrameType == SingleFrame){
		gSFrame_t* SFrame;
		SFrame = (gSFrame_t*)InFrame;
		//int8_t DArr[SFrame->DLC]; open heap
		*Datalen = SFrame->DLC;
		
		for(uint8_t i=0; i<=(uint8_t)(SFrame->DLC);i++ ){
			#ifdef DEBUG
			Data[i]=SFrame->data[i];
			*Mainbuffer=Data[i];
			Mainbuffer++;
			#endif
			*Mainbuffer=SFrame->data[i];
			Mainbuffer++;
			
		}
		//Data
		//buffer=Data;
		
	}
	/***************** First Frame *****************/
	else if(FrameType == FirstFrame){
		    uint8 ErrorFlag=0;
				uint8_t i;
				uint8 BS_Real;
				gFFrame_t* FFrame;
				gCFrame_t c_frame_R; //cons. frame
				//Accept FFrame
				uint8_t RemBytes,RemFrames,BS_size;
				FFrame = (gFFrame_t*)InFrame;
				// count DLC - Data received
				*Datalen = FFrame->DLC;
				RemBytes = FFrame->DLC - FFrame_DataSize;   //remian data size will be sent by next cons Frames
				for( i=0; i<FFrame_DataSize;i++ ){
					#ifdef DEBUG
					Data[i]=FFrame->data[i];
					*Mainbuffer=Data[i];
					Mainbuffer++;
					#endif
					*Mainbuffer=FFrame->data[i];
					Mainbuffer++;
				}
				RemFrames=Get_remaing_frames_number(RemBytes);
				
				/***************** Cons. Frame *****************/
				while(RemFrames){
				//generate block size decision
				//Send control Frame
					if(ErrorFlag==1){
						*Datalen=0;
						break;
					}
					BS_size= generate_BS_decision(RemFrames);
					BS_Real= BS_size;
					if(BS_size==RemFrames){   
						BS_size=0;
					}
					send_Control_Frame(BS_size,20);  //The pointer to the MainBuffer corrupted here ?????
					for(int j=0;j<BS_Real;j++){
							OS_Wait(&NewReceData);
						//receive the remain Con Frames
						CAN_RX((uint8_t*)&c_frame_R);
						 if(c_frame_R.ID == COF_ID+j){
							 if(c_frame_R.ID == COF_ID_END){}
							 for(int w=0; w< ConFrame_DataSize ; w++ ){
								/* if(w==RemBytes){
								 }*/
								 #ifdef DEBUG
								 Data[i]=c_frame_R.data[w];
								 *Mainbuffer=Data[i];
								 Mainbuffer++;
								 #endif
								 *Mainbuffer=c_frame_R.data[w];
								 Mainbuffer++;
								 
								 i++;
								 RemBytes--;
							 }
							 RemFrames--;
						 }
						 else  {
							 ErrorFlag=1;
							 
							 break;
						 }
					 
			}
		}
		//buffer=Data;
	}
	
	else {
		*Datalen =0;
	}
		//receive FF [0x10,DLC,6-Data]
		deInstallNIVCISRFunction(UART0);
		OS_Signal(&Peripheral_Mutex);
	
	
}

















//this method access shared resource CAN_RX
g_frametype_t static Check_Frame_type(){
	g_frametype_t FrameType=SingleFrame;
	//os_wait(&mutex)
	CAN_RX((uint8_t*)InFrame);
	if(InFrame[0]==FF_ID){
		FrameType = FirstFrame;
	}
	else if(InFrame[0] == FC_ID){
		FrameType = FlowControlFrame;
	}
	else if(InFrame[0] >= COF_ID && InFrame[0] <= COF_ID_END ) {
		FrameType = ConsFrame;
	}
	else{
		
	}
	return FrameType;
	
}

//This method access shared resource CAN_TX
void static send_Control_Frame(uint8_t BLockS, uint8_t stMin){
	gFlowFrame_t FCFrame;
	FCFrame.ID=FC_ID;
	FCFrame.NumberFrames=BLockS;
	FCFrame.stMin=stMin;
	for(int i=0;i<5;i++){
	FCFrame.remainBytes[i]=0;
	}
	
	//os_wait(&Mutex)
	CAN_TX((uint8*)&FCFrame);
	
	
}
uint8 static Get_remaing_frames_number(uint8 RemaingBytes){
	uint8 remFrame=0;
  remFrame=RemaingBytes/ConFrame_DataSize;
  if(RemaingBytes-remFrame*7){
	   remFrame++;
	}		
	//Generate number of remaing Frames
	return remFrame;
	
}
uint8 static generate_BS_decision(uint8_t RemaingFrames){
	static uint8 count;
	count ++;
	return RemaingFrames;
}




void TP_UART_Default_Interrupt_Task(void){
		if(UART0_RIS_R&UART_RIS_TXRIS){       // hardware TX FIFO <= 2 items
    UART0_ICR_R = UART_ICR_TXIC;        // acknowledge TX FIFO
    // copy from software TX FIFO to hardware TX FIFO
    copySoftwareToHardware();
    if(TxFifo_Size() == 0){             // software TX FIFO is empty
      UART0_IM_R &= ~UART_IM_TXIM;      // disable TX FIFO interrupt
    }
  }
		else{
		UART0_ICR_R = UART0_RIS_R; //clear all

		}
}

void TP_Receiver_TX_RX_Handler(){
	//if(RX_flag)
  //FF OR Cons.Frame	
	//if(tx_flag)
	//FControl
		if(UART0_RIS_R&UART_RIS_TXRIS){       // hardware TX FIFO <= 2 items
    UART0_ICR_R = UART_ICR_TXIC;        // acknowledge TX FIFO
    // copy from software TX FIFO to hardware TX FIFO
    copySoftwareToHardware();
    if(TxFifo_Size() == 0){             // software TX FIFO is empty
      UART0_IM_R &= ~UART_IM_TXIM;      // disable TX FIFO interrupt
    }
  }
  if(UART0_RIS_R&UART_RIS_RXRIS){       // hardware RX FIFO >= 2 items
    UART0_ICR_R = UART_ICR_RXIC;        // acknowledge RX FIFO
    // copy from hardware RX FIFO to software RX FIFO
    copyHardwareToSoftware();
		//OS_Signal(&NewSwData);
		OS_Signal(&NewReceData);
  }
  if(UART0_RIS_R&UART_RIS_RTRIS){       // receiver timed out
    UART0_ICR_R = UART_ICR_RTIC;        // acknowledge receiver time out
    // copy from hardware RX FIFO to software RX FIFO
    copyHardwareToSoftware();
  }
}

void TP_Sender_TX_RX_Handler(){
	
		//if(RX_flag)
  //FF OR Cons.Frame	
	//if(tx_flag)
	//FControl
		if(UART0_RIS_R&UART_RIS_TXRIS){       // hardware TX FIFO <= 2 items
    UART0_ICR_R = UART_ICR_TXIC;        // acknowledge TX FIFO
    // copy from software TX FIFO to hardware TX FIFO
    copySoftwareToHardware();
    if(TxFifo_Size() == 0){             // software TX FIFO is empty
      UART0_IM_R &= ~UART_IM_TXIM;      // disable TX FIFO interrupt
    }
  }
  if(UART0_RIS_R&UART_RIS_RXRIS){       // hardware RX FIFO >= 2 items
    UART0_ICR_R = UART_ICR_RXIC;        // acknowledge RX FIFO
    // copy from hardware RX FIFO to software RX FIFO
    copyHardwareToSoftware();
		OS_Signal(&NewSwData);
		//OS_Signal(&NewReceData);
  }
  if(UART0_RIS_R&UART_RIS_RTRIS){       // receiver timed out
    UART0_ICR_R = UART_ICR_RTIC;        // acknowledge receiver time out
    // copy from hardware RX FIFO to software RX FIFO
    copyHardwareToSoftware();
  }
}
