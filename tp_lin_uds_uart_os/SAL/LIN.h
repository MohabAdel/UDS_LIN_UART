#ifndef SERVICE_LAYER_LIN_H_
#define SERVICE_LAYER_LIN_H_

#include "../RAL/hw_types.h"
#include "NVICInterruptHandler.h"


typedef enum
{
	BreakFirstByte,
	BreakSecondByte,
	SynchByte,
	Identifier,
	DataBytes,
	StoreincomingData,
	CheckSum,
	SleepMode,
	WaitForNextRequest,
}LINState_t;

typedef enum
{
	NO_ERROR,BIT_ERROR,ID_PARITY_ERROR,CHECKSUM_ERROR,
	NO_ID_MATCH,TIMEOUT_ERROR,DATA_RECEIVED,DATA_REQUEST,
	WAKE_UP,UART_ERROR,SYNCH_BREAK_ERROR,
}TypesOfLINError_t;
typedef enum
{
	_0ByteMode = 0,
	_2ByteMode = 2,
	_4ByteMode = 4,
	_8ByteMode = 8,
}NumberOfByte_t;

typedef enum
{
	ID_DATARECIVE,
	ID_DATASENT,
}MessageDirection_t;

typedef struct
{
	uint8 Identifier;
	MessageDirection_t dir;
	NumberOfByte_t length;
}IDList_t;

typedef struct
{
	uint8 ID;
	NumberOfByte_t length;
}Header_t;
typedef struct
{
	uint8 Data[8];
	uint8 Checksum;
}Response_t;
typedef struct
{
	uint8 *(*DataSent)(void);
	void (*DataReceived)(uint8 *Data);
	IDList_t Info;
}IDInfo_t;
TypesOfLINError_t LIN_InitMaster(g_ISRVirIdx_t Used_Timer,g_ISRVirIdx_t USED_UART);
TypesOfLINError_t LIN_SendWakeUpSignal(void);
TypesOfLINError_t LIN_SendSleepSignal(void);
TypesOfLINError_t InitLINSlave(g_ISRVirIdx_t USED_UART);
TypesOfLINError_t ErrorDetect(void);
#endif /* SERVICE_LAYER_LIN_H_ */
