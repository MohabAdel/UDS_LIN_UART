/*
 *  \file   app_uart.h
 *
 *  \brief
 *
 *  \date: sept 6,2017
 *  \Author: Mohab Adel
 */

#ifndef APP_UART_H_
#define APP_UART_H_
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "../HAL/uart.h"
#include "../HAL/sysctrl.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/** \brief  enumerate the Baud Clock Source types  */
typedef enum {
	System_clock ,PIOSC
}gUARTClkSource_t;
/** \brief  structure holding the UART object. */
typedef struct uartobj{
	uint32 base;
	/**< UART base
 *        -# BASE_UART0
 *        -# BASE_UART1
 *        -# BASE_UART2
 *        -# BASE_UART3
 *        -# BASE_UART4
 *        -# BASE_UART5
 *        -# BASE_UART6
 *        -# BASE_UART7	 */
	uint32 BaudRate;
	/**< desired baud rate */
	gdataformat_t DataFormate;
	/**< UART data format configurations structure */
	gUARTClkSource_t UARTClkSource;
	/**< select Baud Clock Source
	 *       -# System_clock
	 *       -# PIOSC
	 *       note:   If the PIOSC is used for the UART baud clock, the system clock frequency must be at least
     *                    9 MHz in Run mode.*/
}gUARTObj_t;

/* ========================================================================== */
/*                         Global variables  Declarations                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
/**
 *  \name   initUART
 *
 *  \brief  perform UART initializations
 *
 *  \param  obj:  pointer to the UART object.
 *
 *  \retval     the value specified in the enum
 *                  -# gUARTError_t
 */
gUARTError_t initUART(gUARTObj_t *obj);

/**
 *  \name   UARTEnableSIR
 *
 *  \brief  Enables SIR (IrDA) mode on the specified UART
 *          , select it operates on low power or not
 *          and set set low-power counter divisor used to derive the low-power
 *                  SIR pulse width clock.
 *
 *  \param  base:       the memory address of the UART used.
 *                        base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *  \param  lowPowerEn   Enable low power mode
 *                         -# TRUE  Enable
 *                         -# FALSE Disable
 *
 *  \retval     the value specified in the enum
 *                  -# gUARTError_t
 */
gUARTError_t UARTEnableSIR(uint32 base , uint8 lowPowerEn);









#endif /* APP_UART_H_ */
