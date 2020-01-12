/*
 * tp_transiver.h
 *
 *  Created on: Sep 9, 2017
 *      Author: Mohab Adel
 */

#ifndef TP_TRANSIVER_H_
#define TP_TRANSIVER_H_
#include "../RAL/types.h"
#include "../CPX/UART/UART.h"
#include "../os/os.h"
#include "NVICInterruptHandler.h"

#define CAN_TX uart_tpSendFrame
#define CAN_RX uart_tpRecevFrame




typedef struct S_Frame{
uint8 DLC;
uint8 data[7];    //Unsigned ???
}gSFrame_t;

typedef struct F_Frame{
uint8 ID;
uint8 DLC;
uint8 data[6];  //Unsigned ???
}gFFrame_t;

typedef struct C_Frame{
uint8 ID;
uint8 data[7];   //Unsigned ???
}gCFrame_t;

typedef struct Flow_Frame{
uint8 ID;
uint8 NumberFrames;
uint8 stMin;
uint8 remainBytes[5];
}gFlowFrame_t;

typedef enum frametype{
	SingleFrame,
	FirstFrame,
	FlowControlFrame,
	ConsFrame
}g_frametype_t;

typedef enum ErrorType{
	PASS,INVALIDFRAME
	
}g_ErrorType;
void tp_Init(void);
void tp_sender(uint8*buffer , uint8 len);
void tp_receiver(uint8 *buffer,uint8 *Datalen);
#endif /* TP_TRANSIVER_H_ */
