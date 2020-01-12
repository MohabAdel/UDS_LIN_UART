/*
 *  \file   app_uart.c
 *
 *  \brief
 *
 *  \date:    sept 6,2017
 *  \Author: Mohab Adel
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "app_uart.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

gUARTError_t initUART(gUARTObj_t *obj){
	gUARTError_t state= Pass;
	fp32 UARTClk;
		if(obj->base==BASE_UART0 || obj->base==BASE_UART1 || obj->base==BASE_UART2 || obj->base==BASE_UART3 ||
		   obj->base==BASE_UART4 || obj->base==BASE_UART5 || obj->base==BASE_UART6 || obj->base==BASE_UART7   ){
			if(obj->base==BASE_UART0){
				           clockGating(UART_0);
			}else if (obj->base==BASE_UART1){
				           clockGating(UART_1);
			}else if (obj->base==BASE_UART2){
				           clockGating(UART_2);
			}else if (obj->base==BASE_UART3){
				           clockGating(UART_3);
			}else if (obj->base==BASE_UART4){
						   clockGating(UART_4);
			}else if (obj->base==BASE_UART5){
						   clockGating(UART_5);
			}else if (obj->base==BASE_UART6){
						   clockGating(UART_6);
			}else if (obj->base==BASE_UART7){
						   clockGating(UART_7);
			}
			if(obj->UARTClkSource==PIOSC||obj->UARTClkSource==System_clock){
			    if(obj->UARTClkSource==PIOSC){
				    HW_WRITE_REG_32BIT(obj->base+UART_CLOCK_CONFIGURATION_OFFSET ,UART_BaudClock_PIOSC);
				    UARTClk=16000000;
			    }else if (obj->UARTClkSource==System_clock){
			    	HW_WRITE_REG_32BIT(obj->base+UART_CLOCK_CONFIGURATION_OFFSET ,UART_BaudClock_SystemClock);
			    	UARTClk=GetSysFrequency();
			    }
			    SetBaudRate (obj->base ,obj->BaudRate,UARTClk);
			    DataFormatConfig(obj->base , &(obj->DataFormate));
			}else{
				state=INCORRECT_ClkSource;
			}

		}else{
			state= INCORRECT_MODULE;
		}
		return state;
}

gUARTError_t UARTEnableSIR(uint32 base , uint8 lowPowerEn){
	gUARTError_t state= Pass;
	fp32 UARTClk;
		if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
		   base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7   ){
			UARTClk=GetSysFrequency();
			EnableSIR(base,lowPowerEn ,UARTClk);
		}else{
			state= INCORRECT_MODULE;
		}
		return state;
}






