/*
 *   \file     uart.h
 *
 *   \brief    this file contains the prototype of the APIs present in the
 *              device abstraction layer file of UART.
 *
 *   \details  The TM4C123GH6PM controller includes eight Universal Asynchronous Receiver/Transmitter
 *                 (UART) with the following features:
 *             -# Programmable baud-rate generator allowing speeds up to 5 Mbps for regular speed (divide by 16)
 *                and 10 Mbps for high speed (divide by 8)
 *             -# Separate 16x8 transmit (TX) and receive (RX) FIFOs to reduce CPU interrupt service loading
 *             -# Programmable FIFO length, including 1-byte deep operation providing conventional
 *                double-buffered interface
 *             -# FIFO trigger levels of 1/8, 1/4, 1/2, 3/4, and 7/8
 *             -# Standard asynchronous communication bits for start, stop, and parity
 *             -# Line-break generation and detection
 *             -# Fully programmable serial interface characteristics
 *                   -# 5, 6, 7, or 8 data bits
 *                   -# Even, odd, stick, or no-parity bit generation/detection
 *                   -# 1 or 2 stop bit generation
 *             -# IrDA serial-IR (SIR) encoder/decoder providing
 *                   -# Programmable use of IrDA Serial Infrared (SIR) or UART input/output
 *                   -# Support of IrDA SIR encoder/decoder functions for data rates up to 115.2 Kbps half-duplex
 *                   -# Support of normal 3/16 and low-power (1.41-2.23 μs) bit durations
 *                   -# Programmable internal clock generator enabling division of reference clock by 1 to 256 for
 *                      low-power mode bit duration
 *             -# Support for communication with ISO 7816 smart cards
 *             -# Modem flow control (on UART1)
 *             -# EIA-485 9-bit support
 *             -# Standard FIFO-level and End-of-Transmission interrupts
 *             -# Efficient transfers using Micro Direct Memory Access Controller (μDMA)
 *                   -# Separate channels for transmit and receive
 *                   -# Receive single request asserted when data is in the FIFO; burst request asserted at
 *                         programmed FIFO level
 *
 *
 *   \date    Aug 31,2017
 *   \Author: Mohab Adel
 */

#ifndef UART_H_
#define UART_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "../RAL/types.h"
#include "../RAL/hw_types.h"
#include "../RAL/hw_uart.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief  MAX data bits in a frame.*/
#define MAX_UART_WLEN  3

/**\brief when enabling high speed (Buad8),the reference clock is divided by 8*/
#define Baud8 	 8.0
/**\brief when disabling high speed (Buad16),the reference clock is divided by 16*/
#define Baud16   16.0

/** \brief  the value used to select System clock in the UART_CLOCK_CONFIGURATION register  */
#define UART_BaudClock_SystemClock    0x0
/** \brief  the value used to select PIOSC in the UART_CLOCK_CONFIGURATION register  */
#define UART_BaudClock_PIOSC    0x5

/** brief Values that can be passed to UARTDMAEnable() */
#define DMA_on_Error   0x01
#define Transmit_DMA   0x02
#define Receive_DMA    0x04

/** -The duration of SIR pulses generated when low-power mode
 *    is enabled is three times the period of the IrLPBaud16 clock.
 * -FIrLPBaud16  must take values such that 1.42 MHz < FIrLPBaud16 < 2.12 MHz,
 *  resulting in a low-power pulse duration of 1.41�2.11 microsecond (three times the
 * period of IrLPBaud16). The minimum frequency of IrLPBaud16 ensures that pulses less than
 * one period of IrLPBaud16 are rejected, but pulses greater than 1.4 microsecond are accepted as valid pulses.
 * Note: Zero is an illegal value. Programming a zero value results in no IrLPBaud16 pulses being
 * generated. */
#define FIrLPBaud16   1.8432

/** brief Values that can be passed to UARTFlowControlSet function */
#define HW_RequestToSend  FALSE
#define SW_RequestToSend  TRUE
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**  \brief   Enumerate the types of errors in the UART module*/
typedef enum {
 Pass , INCORRECT_MODULE ,RXFIFO_EMPTY ,TXFIFO_FULL ,INCORRECT_WORD_LENGTH ,INCORRECT_PARITY_MODE ,INCORRECT_StopBitsNum ,
 INCORRECT_ClkSource ,INCORRECT_Value ,INCORRECT_InterruptConfig
}gUARTError_t;

/** \brief   Enumerate the types of parity mode in the UART module */
typedef enum {
	PARITY_NONE , PARITY_EVEN ,PARITY_ODD , PARITY_ONE , PARITY_ZERO
}gParityType_t;

/** \brief   Enumerate the types of word length transmitted or received in a frame.*/
typedef enum {
	WordLength_5 , WordLength_6 , WordLength_7 , WordLength_8
}gword_Lenght_t;

/** \brief   Enumerate the types of the Receive Interrupt FIFO Level Select */
typedef enum {
	NONE_RX_Int,          //No Receive Interrupt
	RX_FIFO_1_8 ,  //RX FIFO >= 1/8 full
	RX_FIFO_1_4 ,  //RX FIFO >= 1/4 full
	RX_FIFO_1_2 ,  //RX FIFO >= 1/2 full
	RX_FIFO_3_4 ,  //RX FIFO >= 3/4 full
	RX_FIFO_7_8    //RX FIFO >= 7/8 full
}gRXFIFILevelSel_t;

/** \brief   Enumerate the types of the Transmit Interrupt FIFO Level Select */
typedef enum {
	NONE_TX_Int,           // No Transmit Interrupt
	TX_FIFO_7_8 ,   //TX FIFO <= 7/8 full
	TX_FIFO_3_4 ,   //TX FIFO <= 3/4 full
	TX_FIFO_1_2 ,   //TX FIFO <= 1/2 full
	TX_FIFO_1_4 ,   //TX FIFO <= 1/4 full
	TX_FIFO_1_8 ,   //TX FIFO <= 1/8 full
	END_OF_TRANSMIT //only after all data are transmitted
}gTXFIFILevelSel_t;



/** brief  structure holding data format configurations */
typedef struct dataformat{
	gword_Lenght_t word_Lenght;
	/**<select the number of data bits transmitted or received in a frame. 
	 *            -# WordLength_5
   *            -# WordLength_6
   *            -# WordLength_7
   *            -# WordLength_8  */
	uint8 stop_bits;
	/**<indicate the number of stop bits are transmitted at the end of a frame. 
	 *            -# 0
	 *            -# 1   */
	gParityType_t PariyType;
	/**<select parity mode .*/
	uint8 Fifos_En;
	/**<UART Enable FIFOs
	 *   -# true :  The transmit and receive FIFObuffers are enabled (FIFOmode).
	 *   -# false:  The FIFOs are disabled (Character mode). The FIFOs become
   *                               1-byte-deep holding registers.
	 */
}gdataformat_t;

/** brief  structure holding UART interrupt configurations */
typedef struct UARTIntConfig{
	uint8 Mode_9BIT;
	/**< Select 9-Bit Mode interrupt
	 *    -# TRUE
	 *    -# FALSE	 */
	uint8 OverrunError;
	/**< Select Overrun Error interrupt
	 *    -# TRUE
	 *    -# FALSE	 */
	uint8 BreakError;
	/**< Select Break Error interrupt
	 *    -# TRUE
	 *    -# FALSE	 */
	uint8 ParityError ;
	/**< Select Parity Error Interrupt
	 *    -# TRUE
	 *    -# FALSE	 */
	uint8 FramingError;
	/**< Select Framing Error interrupt
	 *    -# TRUE
	 *    -# FALSE	 */
	uint8 ReceiveTimeOutError;
	/**< Select Receive Time-Out Error interrupt
	 *   -# TRUE
	 *   -# FALSR	 */
	uint8 ClearToSend;
	/**< Select Clear to Send Modem Interrupt
	 *    -# TRUE
	 *    -# FALSE
	 *    \note  this interrup t is only available for UART1 module. */
	gTXFIFILevelSel_t TXFIFILevelSel;
	/**< Transmit Interrupt FIFO Level Select */
	gRXFIFILevelSel_t RXFIFILevelSel;
	/**<Receive Interrupt FIFO Level Select */
}gUARTInterrConfig_t;
/* ========================================================================== */
/*                         Global variables  Declarations                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
/**
 * \name       UART_In
 *
 * \brief      UART input
 *             Wait for new serial port input
 *
 * \param      Base:  the memory address of the UART used
 *                       base can have 8 values :
 *                            -# BASE_UART0
 *                            -# BASE_UART1
 *                            -# BASE_UART2
 *                            -# BASE_UART3
 *                            -# BASE_UART4
 *                            -# BASE_UART5
 *                            -# BASE_UART6
 *                            -# BASE_UART7
 * \param      data:  received data
 *
 * \retval     the value specified in the enum
 *                  -# gUARTError_t
 **/
gUARTError_t UART_In(uint32 base,uint8 *data);


/**
 * \name     UART_InNonblocking
 *
 * \brief    UART input nonblocking
 *           Get oldest serial port input and return immediately
 *              if there is no data.
 *
 * \param    Base:  the memory address of the UART used.
 *                         base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 * \param      data:  received data.
 *
 * \retval     the value specified in the enum
 *                -#gUARTError_t
 **/
gUARTError_t UART_InNonblocking(uint32 base,uint8 *data);

/**
 * \name     UART_Out
 *
 * \brief    UART output
 *
 * \param   base:  the memory address of the UART used.
 *                         base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 * \param   data:  data to be transmitted
 *
 * \retval  the value specified in the enum
 *                -#gUARTError_t
**/
gUARTError_t UART_Out(uint32 base ,uint8 data);

/**
 * \name     UART_OutNonblocking
 *
 * \brief    UART output nonblocking
 *
 * \param   base:  the memory address of the UART used.
 *                         base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 * \param   data:  data to be transmitted
 *
 * \retval  the value specified in the enum
 *                -#gUARTError_t
**/
gUARTError_t UART_OutNonblocking(uint32 base,uint8 data);

/**
 *  \name    DataFormatConfig
 *
 *  \brief   set data format configurations
 *
 *  \param   base:  the memory address of the UART used.
 *                         base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *  \param   opj:   pointer to the data format configuration structure
 *                       -#gdataformat_t
 *
 *  \retval  the value specified in the enum
 *                       -#gUARTError_t
 *
 *  \note      After using the SetBaudRate function ,you must write to the
 *             UART_LINE_CONTROL register using DataFormatConfig function.
 */
gUARTError_t DataFormatConfig(uint32 base ,gdataformat_t *obj);



/**
 *  \name     UARTDiable
 *
 *  \brief     ->Disables transmitting and receiving.
 *             If the UART is disabled in the middle of transmission or reception, it
 *             completes the current character before stopping.
 *             ->this function also Wait for the end of transmission or reception of the current character
 *             ,Flush the transmit FIFO(recommended before making changes to the UART_CONTROL register.)
 *
 *  \param     base:  the memory address of the UART used.
 *                         base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UARTDisable(uint32 base);

/**
 *  \name     UARTEnable
 *
 *  \brief    Enable UART ,transmit section and receive section.
 *
  * \param     base:  the memory address of the UART used.
 *                         base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UARTEnable(uint32 base);

/**
 *  \name    SetBaudRate
 *
 *  \brief   this function set the baud rate by
 *           1-disable the UART
 *           2-determine if there is a need to use high speed or not.
 *           3-calculate the divisor.
 *           4-write the integer and fraction part of the divisor in the registers.
 *
 *
 *  \param    base:       the memory address of the UART used.
 *                        base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *  \param    baud :      the desired baud rate.
 *  \param    UARTclk:    the system clock connected to the UART.
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 *
 *  \note      After using the SetBaudRate function ,you must write to the
 *             UART_LINE_CONTROL register using DataFormatConfig function.
 */
gUARTError_t SetBaudRate (uint32 base ,uint32 baud,fp32 UARTclk);

/**
 *  \name    UARTInterruptConfig
 *
 *  \btief   Configures interrupts for the UART module.
 *
 *  \parram  base:       the memory address of the UART used.
 *                        base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *  \param   obj:      pointer to the object holding the UART interrupt configurations.
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 *
 *  \note    Clear to Send Modem Interrupt is only available for UART1 module.
 */
gUARTError_t UARTInterruptConfig(uint32 base , gUARTInterrConfig_t *obj);

/**
 *  \name    UARTBreak
 *
 *  \brief   this function Causes a BREAK to be sent or not .
 *
 *  \param   base:       the memory address of the UART used.
 *                        base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *  \param   send:        UART send break
 *                             -# TRUE    A Low level is continually output on the UARTnTx signal, after
 *                                          completing transmission of the current character.
 *                             -# FALSE   Normal use.
 *
 *  \note  For the proper execution of the break command, software must set this bit for
 *               at least two frames (character periods).
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UARTBreak(uint32 base ,uint8 send);

/**
 *  \name    UARTDMAEnable
 *
 *  \brief   Enable UART uDMA operation.
 *           The UART can be configured to use uDMA for transmit or receive and to disable
 *           receive if an error occurs.
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
 *  \param  flags   the value to determine which flag to enable
 *                    -# DMA_on_Error
 *                    -# Transmit_DMA
 *                    -# Receive_DMA
 *                    if you want to operate more than flag for example to enable Transmit DMA and
 *                    Receive DMA write (Transmit_DMA + Receive_DMA).
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 *
 *  \note     uDMA controller must also be set up before DMA can be used
 *              with the UART.
 *            If DMA is enabled, then the uDMA controller triggers an interrupt when a transfer is complete. The
 *            interrupt occurs on the UART interrupt vector. Therefore, if interrupts are used for UART operation
 *            and DMA is enabled, the UART interrupt handler must be designed to handle the uDMA completion
 *               interrupt.
 */
gUARTError_t UARTDMAEnable(uint32 base ,uint8 flags);

/**
 *  \name    UARTDMADisable
 *
 *  \brief  Disable UART uDMA operation
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
 *  \param  flags   the value to determine which flag to disable
 *                    -# DMA_on_Error
 *                    -# Transmit_DMA
 *                    -# Receive_DMA
 *                    if you want to disable more than flag for example to disable Transmit DMA and
 *                    Receive DMA write (Transmit_DMA + Receive_DMA).
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UARTDMADisable(uint32 base ,uint8 flags);


/**
 *  \name     UART9bitEnable
 *
 *  \brief    Enables 9-bit mode on the specified UART.
 *
 *  \parram   base:       the memory address of the UART used.
 *                        base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 *
 *  \note     If the UART is in 9-bit mode, then
 *             the receiver operates with no parity mode
 */
gUARTError_t UART9bitEnable (uint32 base);
/**
 *  \name    UART9bitEnable
 *
 *  \brief   Disable 9-bit mode on the specified UART.
 *
 *  \parram   base:       the memory address of the UART used.
 *                        base can have 8 values :
 *                                 -# BASE_UART0
 *                                 -# BASE_UART1
 *                                 -# BASE_UART2
 *                                 -# BASE_UART3
 *                                 -# BASE_UART4
 *                                 -# BASE_UART5
 *                                 -# BASE_UART6
 *                                 -# BASE_UART7
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UART9bitDisable (uint32 base);

/**
 *  \name   UART9bitAddrSet
 *
 *  \brief  Sets the device address(es) for 9-bit mode.
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
 *  \param  add:         the device address.
 *  \param  mask:         is the device address mask.
 *                        -To extend the address to a set of addresses.
 *                        -By default, the mask is 0xFF, meaning that only the specified address is matched.
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UART9bitAddrSet(uint32 base , uint32 add ,uint32 mask);

/*
 *  \name    UART9bitAddrSend
 *
 *  \brief   Sends an address operating in 9-bit mode.
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
 *  \param  add:    is the address to be transmitted.
 *
 *  \retval    the value specified in the enum
 *                       -#gUARTError_t
 */
gUARTError_t UART9bitAddrSend(uint32 base ,uint32 add);

/**
 *  \name   EnableSIR
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
 *  \param  SysClk       the frequency of the system clock
 *
 *  \retval     the value specified in the enum
 *                  -# gUARTError_t
 */
gUARTError_t EnableSIR(uint32 base , uint8 lowPowerEn ,fp32 SysClk);

/**
 *  \name    UARTDisableSIR
 *
 *  \brief   Disable SIR (IrDA) mode on the specified UART.
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
 *
 *  \retval     the value specified in the enum
 *                  -# gUARTError_t
 */
gUARTError_t UARTDisableSIR(uint32 base);

/*
 *  \name    UART1FlowControlSet
 *
 *  \brief   Sets the configurations of flow control signals for UART1
 *
 *  \param   RTS_State:   Request to send state determines when the system outputs a Request-To-Send signal.
 *                         -# HW_RequestToSend    The Request-To-Send signal remains asserted until the preprogrammed
 *                                                watermark level is reached, indicating that the Receive FIFO has no
 *                                                space to store additional characters
 *                         -# SW_RequestToSend    The Request-To-Send signal is sent by the software using
 *                                                      UARTRequestToSend function
 *  \param  CTS_Enable    the action the system take when receive a Clear_To_Send signal.
 *                         -# TRUE     The Clear_To_Send input controls the transmitter. The transmitter only transmit
 *                                       data when the Clear_To_Send input is asserted.
 *                         -# FALSE    normal use.
 *                           ->note The Clear_To_Send input can generate an interrupt using UARTInterruptConfig function.
 *
 *  \note      this function is only available for UART1.
 */
void UART1FlowControlSet( uint8 RTS_State, uint8 CTS_Enable );

/*
 *  \name   UART1FlowControlClear
 *
 *  \brief  Disable the DTR and/or RTS flow control modes.
 *
 *  \param  RTS_Disable   Disable the request to send mode
 *                          -# TRUE
 *                          -# FALSE
 *  \param  CTS_Disable   Disable the clear to send mode
 *                          -# TRUE
 *                          -# FALSE
 *
 *  \note      this function is only available for UART1.
 */
void UART1FlowControlDisable(uint8 RTS_Disable, uint8 CTS_Disable );

/**
 *  \name    UART1RequestToSend
 *
 *  \brief   Outputs a Request_To_Send signal.
 *
 *  \note    this function is only available for UART1.
 *           to use this function you must enable the software request to send mode using
 *           UART1FlowControlSet function.
 */
void UART1RequestToSend(void);

#endif /* UART_H_ */
