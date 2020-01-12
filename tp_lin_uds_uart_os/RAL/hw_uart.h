/*
 *   \file     hw_uart.h
 *
 *   \brief    this file contains the physical addresses of UART module
 *
 *
 *   \date     Aug 31,2017
 *   \Author   Mohab Adel
 */

#ifndef HW_UART_H_
#define HW_UART_H_
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BASE_UART0  0x4000C000
#define BASE_UART1  0x4000D000
#define BASE_UART2  0x4000E000
#define BASE_UART3  0x4000F000
#define BASE_UART4  0x40010000
#define BASE_UART5  0x40011000
#define BASE_UART6  0x40012000
#define BASE_UART7  0x40013000

/************************** UART register offsets *****************************/
#define UART_DATA_OFFSET                         0x000 //UART Data
#define UART_RECEIVE_STATUS_OFFSET               0x004 //UART Receive Status
#define UART_ERROR_CLEAR_OFFSET                  0x004 //UART Error Clear
#define UART_FLAG_OFFSET                         0x018 //UART Flag
#define UART_IRDA_LOW_POWER_REGISTER_OFFSET      0x020 //UART IrDA Low-Power Register
#define UART_INTEGER_BAUD_RATE_DIVISOR_OFFSET    0x024 //UART Integer Baud-Rate Divisor
#define UART_FRACTIONAL_BAUD_RATE_DIVISOR_OFFSET 0x028 //UART Fractional Baud-Rate Divisor
#define UART_LINE_CONTROL_OFFSET                 0x02C //UART Line Control
#define UART_CONTROL_OFFSET                      0x030 //UART Control
#define UART_INTERRUPT_FIFO_LEVEL_SELECT_OFFSET  0x034 //UART Interrupt FIFO Level Select
#define UART_INTERRUPT_MASK_OFFSET               0x038 //UART Interrupt Mask
#define UART_RAW_INTERRUPT_STATUS_OFFSET         0x03C //UART Raw Interrupt Status
#define UART_MASKED_INTERRUPT_STATUS_OFFSET      0x040 //UART Masked Interrupt Status
#define UART_INTERRUPT_CLEAR_OFFSET              0x044 //UART Interrupt Clear
#define UART_DMA_CONTROL_OFFSET                  0x048 //UART DMA Control
#define UART_9BIT_SELF_ADDRESS_OFFSET            0x0A4 //UART 9-Bit Self Address
#define UART_9BIT_SELF_ADDRESS_MASK_OFFSET       0x0A8 //UART 9-Bit Self Address Mask
#define UART_PERIPHERAL_PROPERTIES_OFFSET        0xFC0 //UART Peripheral Properties
#define UART_CLOCK_CONFIGURATION_OFFSET          0xFC8 //UART Clock Configuration
#define UART_PERIPHERAL_ID_4_OFFSET              0xFD0 //UART Peripheral Identification 4
#define UART_PERIPHERAL_ID_5_OFFSET              0xFD4 //UART Peripheral Identification 5
#define UART_PERIPHERAL_ID_6_OFFSET              0xFD8 //UART Peripheral Identification 6
#define UART_PERIPHERAL_ID_7_OFFSET              0xFDC //UART Peripheral Identification 7
#define UART_PERIPHERAL_ID_0_OFFSET              0xFE0 //UART Peripheral Identification 0
#define UART_PERIPHERAL_ID_1_OFFSET              0xFE4 //UART Peripheral Identification 1
#define UART_PERIPHERAL_ID_2_OFFSET              0xFE8 //UART Peripheral Identification 2
#define UART_PERIPHERAL_ID_3_OFFSET              0xFEC //UART Peripheral Identification 3
#define UART_PRIMECELL_ID_0_OFFSET               0xFF0 //UART PrimeCell Identification 0
#define UART_PRIMECELL_ID_1_OFFSET               0xFF4 //UART PrimeCell Identification 1
#define UART_PRIMECELL_ID_2_OFFSET               0xFF8 //UART PrimeCell Identification 2
#define UART_PRIMECELL_ID_3_OFFSET               0xFFC //UART PrimeCell Identification 3

/**************** the bit numbers in the UART_DATA register ***************/
#define UART_DATA_FE_BitNum              8 //UART Framing Error
#define UART_DATA_PE_BitNum              9 //UART Parity Error
#define UART_DATA_BE_BitNum              10 //UART Break Error
#define UART_DATA_OE_BitNum              11 //UART Overrun Error

/***************** the bit fields in the UART_DATA tegister******************************/
#define UART_DATA_DATA_Field       0xff  //Data Transmitted or Received

/*********************the bit numbers in the UART_RECEIVE_STATUS register ***************/
#define UART_RECEIVE_STATUS_FE_BitNum    0 //UART Framing Error
#define UART_RECEIVE_STATUS_PE_BitNum    1 //UART Parity Error
#define UART_RECEIVE_STATUS_BE_BitNum    2 //UART Break Error
#define UART_RECEIVE_STATUS_OE_BitNum    3 //UART Overrun Error

/**********************the bit fields in the UART_ERROR_CLEAR register ******************/
#define UART_ERROR_CLEAR_DATA_Field     0xff //Error Clear

/**********************the bit numbers in the UART_FLAG register ************************/
#define UART_FLAG_CTS_BitNum          0 //Clear To Send
#define UART_FLAG_BUSY_BitNum         3 //UART Busy
#define UART_FLAG_RXFE_BitNum         4 //UART Receive FIFO Empty
#define UART_FLAG_TXFF_BitNum         5 //UART Transmit FIFO Full
#define UART_FLAG_RXFF_BitNum         6 //UART Receive FIFO Full
#define UART_FLAG_TXFE_BitNum         7 //UART Transmit FIFO Empty

/*******************the bit numbers in the UART_LINE_CONTROL register **********************/
#define UART_LINE_CONTROL_BRK_BitNum          0 //UART Send Break
#define UART_LINE_CONTROL_PEN_BitNum          1 //UART Parity Enable
#define UART_LINE_CONTROL_EPS_BitNum          2 //UART Even Parity Select
#define UART_LINE_CONTROL_STP2_BitNum         3 //UART Two Stop Bits Select
#define UART_LINE_CONTROL_FEN_BitNum          4 //UART Enable FIFOs
#define UART_LINE_CONTROL_SPS_BitNum          7 //UART Stick Parity Select

/******************the bit fields in the UART_LINE_CONTROL register **************************/
#define UART_LINE_CONTROL_WLEN_Field          0x60   //UART Word Length
                                                     //  -# 0x0 5 bits (default)
                                                     //  -# 0x1 6 bits
                                                     //  -# 0x2 7 bits
                                                     //  -# 0x3 8 bits

/*****************the bit numbers in the UART_CONTROL register ******************************/
#define UART_CONTROL_UARTEN_BitNum           0  //UART Enable
#define UART_CONTROL_SIREN_BitNum            1  //UART SIR Enable
#define UART_CONTROL_SIRLP_BitNum            2  //UART SIR Low-Power Mode
#define UART_CONTROL_SMART_BitNum            3  //ISO 7816 Smart Card Support
#define UART_CONTROL_EOT_BitNum              4  //End of Transmission
#define UART_CONTROL_HSE_BitNum              5  //High-Speed Enable
#define UART_CONTROL_LBE_BitNum              7  //UART Loop Back Enable
#define UART_CONTROL_TXE_BitNum              8  //UART Transmit Enable
#define UART_CONTROL_RXE_BitNum              9  //UART Receive Enable
#define UART_CONTROL_RTS_BitNum              11  //Request to Send
#define UART_CONTROL_RTSEN_BitNum            14  //Enable Request to Send
#define UART_CONTROL_CTSEN_BitNum            15  //Enable Clear To Send

/*******************the bit fields in the UART_INTERRUPT_FIFO_LEVEL_SELECT register **************/
#define UART_INTERRUPT_FIFO_LEVEL_SELECT_TXIFLSEL_Field    0x07  // UART Transmit Interrupt FIFO Level Select
                                                                 //0x0 TX FIFO <= 1/8 empty
                                                                 // -# 0x1 TX FIFO <= 3/4 empty
                                                                 //-# 0x2 TX FIFO <= 1/2 empty (default)
                                                                 // -# 0x3 TX FIFO <= 1/4 empty
                                                                 // -# 0x4 TX FIFO <= 1/8 empty
                                                                 // -# 0x5-0x7 Reserved
#define UART_INTERRUPT_FIFO_LEVEL_SELECT_RXIFLSEL_Field    0x38  //UART Receive Interrupt FIFO Level Select
                                                                 // -# 0x0 RX FIFO >= 1/8 full
                                                                 // -# 0x1 RX FIFO >= 1/4 full
                                                                 // -# 0x2 RX FIFO >= 1/2 full (default)
                                                                 // -# 0x3 RX FIFO >= 3/4 full
                                                                 // -# 0x4 RX FIFO >= 1/8 full
                                                                 // -# 0x5-0x7 Reserved

/******************the bit numbers in the UART_INTERRUPT_MASK register *************************/
#define UART_INTERRUPT_MASK_CTSIM_BitNum      1  //UART Clear to Send Modem Interrupt Mask
#define UART_INTERRUPT_MASK_RXIM_BitNum       4  //UART Receive Interrupt Mask
#define UART_INTERRUPT_MASK_TXIM_BitNum       5  //UART Transmit Interrupt Mask
#define UART_INTERRUPT_MASK_RTIM_BitNum       6  //UART Receive Time-Out Interrupt Mask
#define UART_INTERRUPT_MASK_FEIM_BitNum       7  //UART Framing Error Interrupt Mask
#define UART_INTERRUPT_MASK_PEIM_BitNum       8  //UART Parity Error Interrupt Mask
#define UART_INTERRUPT_MASK_BEIM_BitNum       9  //UART Break Error Interrupt Mask
#define UART_INTERRUPT_MASK_OEIM_BitNum       10 //UART Overrun Error Interrupt Mask
#define UART_INTERRUPT_MASK_9BITIM_BitNum     12 //9-Bit Mode Interrupt Mask

/******************* the bit numbers in the UART_INTERRUPT_CLEAR register ***********************/
#define UART_INTERRUPT_CLEAR_CTSMIC_BitNum    1  //UART Clear to Send Modem Interrupt Clear
#define UART_INTERRUPT_CLEAR_RXIC_BitNum      4  //Receive Interrupt Clear
#define UART_INTERRUPT_CLEAR_BitNum      5  //Transmit Interrupt Clear
#define UART_INTERRUPT_CLEAR_RTIC_BitNum      6  //Receive Time-Out Interrupt Clear
#define UART_INTERRUPT_CLEAR_FEIC_BitNum      7  //Framing Error Interrupt Clear
#define UART_INTERRUPT_CLEAR_PEIC_BitNum      8  //Parity Error Interrupt Clear
#define UART_INTERRUPT_CLEAR_BEIC_BitNum      9  //Break Error Interrupt Clear
#define UART_INTERRUPT_CLEAR_OEIC_BitNum      10  //Overrun Error Interrupt Clear
#define UART_INTERRUPT_CLEAR_9BITIC_BitNum    12  //9-Bit Mode Interrupt Clear

/********************* the bit numbers in the UART_DMA_CONTROL register***************************/
#define UART_DMA_CONTROL_RXDMAE_BitNum        0  //Receive DMA Enable
#define UART_DMA_CONTROL_TXDMAE_BitNum        1  //Transmit DMA Enable
#define UART_DMA_CONTROL_DMAERR_BitNum        2 //DMA on Error


/********************* the bit numbers in the UART_9BIT_SELF_ADDRESS register *********************/
#define UART_9BIT_SELF_ADDRESS_9BITEN_BitNum       15  //Enable 9-Bit Mode

/*********************the bit fields in the UART_9BIT_SELF_ADDRESS register ************************/
#define UART_9BIT_SELF_ADDRESS_ADDR_Field          0xff  //Self Address for 9-Bit Mode

/********************* the bit fields in the UART_9BIT_SELF_ADDRESS_MASK register *******************/
#define UART_9BIT_SELF_ADDRESS_MASK_MASK_Field     0xff //Self Address Mask for 9-Bit Mode

/**********************the bit numbers in the UART_PERIPHERAL_PROPERTIES register ******************/
#define UART_PERIPHERAL_PROPERTIES_SC_BitNum    0  //Smart Card Support
#define UART_PERIPHERAL_PROPERTIES_NB_BitNum    1 //9-Bit Support

/********************* the bit fields in the UART_CLOCK_CONFIGURATION register *********************/
#define UART_CLOCK_CONFIGURATION_CS_Field    0x0f  //UART Baud Clock Source
                                                   // -# 0x0      System clock (based on clock source and divisor factor)
                                                   // -# 0x1-0x4  reserved
                                                   // -# 0x5      PIOSC
                                                   // -# 0x5-0xF  Reserved



/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global variables  Declarations                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */

/* None */






#endif /* HW_UART_H_ */
