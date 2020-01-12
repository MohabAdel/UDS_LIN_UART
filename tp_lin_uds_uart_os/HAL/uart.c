/*
 *   \file     uart.c
 *
 *   \brief    this file contains the device abstraction layer APIs for UART
 *
 *   \date     Aug 31,2017
 *   \Author:  Mohab Adel
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "uart.h"
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

gUARTError_t UART_IN(uint32 base,uint8 *data){
	gUARTError_t state= Pass;
	if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	   base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7   ){
		while (HW_READ_BIT(base+UART_FLAG_OFFSET , UART_FLAG_RXFE_BitNum));
		*data= HW_READ_REG32_MASKED(base+UART_DATA_OFFSET , UART_DATA_DATA_Field);
	}else{
		state= INCORRECT_MODULE;
	}
	return state;
	}



gUARTError_t UART_InNonblocking(uint32 base,uint8 *data){
	gUARTError_t state= Pass;
	if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	   base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7   ){
		if (HW_READ_BIT(base+UART_FLAG_OFFSET , UART_FLAG_RXFE_BitNum)==0){
			*data= HW_READ_REG32_MASKED(base+UART_DATA_OFFSET, UART_DATA_DATA_Field);
		}else{
			state= RXFIFO_EMPTY;
		}
	}else{
			state= INCORRECT_MODULE;
}
	return state;
}


gUARTError_t UART_Out(uint32 base ,uint8 data){
   gUARTError_t state=Pass;
   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
   	   base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7   ){
	   while(HW_READ_BIT(base+UART_FLAG_OFFSET , UART_FLAG_TXFF_BitNum));
	   HW_WRITE_REG32_MASKED(base+UART_DATA_OFFSET , data , UART_DATA_DATA_Field);
   }else{
   			state= INCORRECT_MODULE;
   }
   	return state;
}


gUARTError_t UART_OutNonblocking(uint32 base,uint8 data){
	gUARTError_t state=Pass;
	   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	   	   base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7   ){
		   if(HW_READ_BIT(base+UART_FLAG_OFFSET , UART_FLAG_TXFF_BitNum)==0){
		   HW_WRITE_REG32_MASKED(base+UART_DATA_OFFSET , data , UART_DATA_DATA_Field);
		   }else{
			   state= TXFIFO_FULL;
		   }
	   }else{
	   			state= INCORRECT_MODULE;
	   }
	   	return state;
}


gUARTError_t DataFormatConfig(uint32 base , gdataformat_t *obj){
	gUARTError_t state=Pass;
	   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
		      if (obj->word_Lenght > MAX_UART_WLEN ){
			      state=INCORRECT_WORD_LENGTH;
		      }else{
			  HW_WRITE_REG32_MASKED(base+UART_LINE_CONTROL_OFFSET , (obj->word_Lenght)<<5 , UART_LINE_CONTROL_WLEN_Field);
		      }
		      if(obj->PariyType==PARITY_NONE||obj->PariyType==PARITY_EVEN||obj->PariyType==PARITY_ODD
		    		  ||obj->PariyType==PARITY_ONE||obj->PariyType==PARITY_ZERO){

			      if (obj->PariyType==PARITY_NONE){
				      HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_PEN_BitNum);
			      }else if(obj->PariyType==PARITY_EVEN){
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_PEN_BitNum);
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_EPS_BitNum);
			      }else if (obj->PariyType==PARITY_ODD){
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_PEN_BitNum);
			          HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_EPS_BitNum);
			      }else if(obj->PariyType==PARITY_ONE){
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_PEN_BitNum);
				      HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_EPS_BitNum);
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_SPS_BitNum);
			      }else if (obj->PariyType==PARITY_ZERO){
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_PEN_BitNum);
				      HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_EPS_BitNum);
		              HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_SPS_BitNum);
			      }
			      if(obj->stop_bits==1||obj->stop_bits==2){
			    	  if(obj->stop_bits==1){
			    		  HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_STP2_BitNum);
			    	  }else if(obj->stop_bits==2){
			   			  HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_STP2_BitNum);
			    	  }
			    	  if (obj->Fifos_En==TRUE){
			    		  HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_FEN_BitNum);
			    	  }else if (obj->Fifos_En==FALSE){
			    	  	  HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_FEN_BitNum);
			    	  }else{
			    	  	  state=INCORRECT_Value;
			    	  }
			      }else{
				      state=INCORRECT_StopBitsNum;
			      }

			  }else{
				  state=INCORRECT_PARITY_MODE;
			  }
	   }else{
  			state= INCORRECT_MODULE;
       }
  	return state;

  }


gUARTError_t UARTDisable(uint32 base){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   HW_RESET_BIT(base+UART_CONTROL_OFFSET , UART_CONTROL_UARTEN_BitNum);
			   while(HW_READ_BIT(base+UART_FLAG_OFFSET , UART_FLAG_BUSY_BitNum));
			   HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET , UART_LINE_CONTROL_FEN_BitNum);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UARTEnable(uint32 base){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   HW_SET_BIT(base+UART_CONTROL_OFFSET , UART_CONTROL_UARTEN_BitNum);
			   HW_SET_BIT(base+UART_CONTROL_OFFSET , UART_CONTROL_TXE_BitNum);
			   HW_SET_BIT(base+UART_CONTROL_OFFSET , UART_CONTROL_RXE_BitNum);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t SetBaudRate (uint32 base ,uint32 baud,fp32 UARTclk){
	gUARTError_t state=Pass;
	uint8 FifoEn;
	fp32 Baud=(fp32)baud;
	fp32 CLKDIV;
    fp32 divisor;
    fp32 DivInt;
    fp32 DivFrac;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
						FifoEn=HW_READ_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);
			      UARTDisable(base);
               if((baud*16)>UARTclk){
            	   CLKDIV=Baud8;
            	   HW_SET_BIT(base+UART_CONTROL_OFFSET , UART_CONTROL_HSE_BitNum);
               }else{
            	   CLKDIV=Baud16;
            	   HW_RESET_BIT(base+UART_CONTROL_OFFSET , UART_CONTROL_HSE_BitNum);
               }
               divisor=UARTclk/(CLKDIV*Baud);
               DivInt=(uint32)divisor;
               DivFrac=divisor - DivInt;
							 DivFrac=DivFrac * 64.0f + 0.5f;
               HW_WRITE_REG_32BIT(base+UART_INTEGER_BAUD_RATE_DIVISOR_OFFSET,(uint32)DivInt);
               HW_WRITE_REG_32BIT(base+UART_FRACTIONAL_BAUD_RATE_DIVISOR_OFFSET,DivFrac);
							 HW_WRITE_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
               UARTEnable(base);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UARTInterruptConfig(uint32 base , gUARTInterrConfig_t *obj){
	gUARTError_t state=Pass;
	uint8 FifoEn;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			  if (obj->Mode_9BIT==FALSE) {
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_9BITIM_BitNum);
			  }else{
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_9BITIM_BitNum);
			  }
			  if (obj->OverrunError==FALSE) {
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_OEIM_BitNum);
			  }else{
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_OEIM_BitNum);
			  }
			  if (obj->BreakError==FALSE) {
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_BEIM_BitNum);
			  }else{
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_BEIM_BitNum);
			  }
			  if (obj->ParityError==FALSE) {
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_PEIM_BitNum);
			  }else{
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_PEIM_BitNum);
			  }
			  if (obj->FramingError==FALSE) {
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_FEIM_BitNum);
			  }else{
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_FEIM_BitNum);
			  }
			  if (obj->ReceiveTimeOutError==FALSE) {
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_RTIM_BitNum);
			  }else{
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_RTIM_BitNum);
			  }
			  if(obj->RXFIFILevelSel==NONE_RX_Int){
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_RXIM_BitNum);
			  }else if(obj->RXFIFILevelSel==RX_FIFO_1_8 ||obj->RXFIFILevelSel==RX_FIFO_1_4 || obj->RXFIFILevelSel==RX_FIFO_1_2
					  || obj->RXFIFILevelSel==RX_FIFO_3_4 || obj->RXFIFILevelSel==RX_FIFO_7_8){
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_RXIM_BitNum);
				  HW_WRITE_REG32_MASKED(base+UART_INTERRUPT_FIFO_LEVEL_SELECT_OFFSET , (obj->RXFIFILevelSel)<<3 , UART_INTERRUPT_FIFO_LEVEL_SELECT_RXIFLSEL_Field);
			  }else{
				  state=INCORRECT_InterruptConfig;
			  }
			  if(obj->TXFIFILevelSel==NONE_TX_Int){
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_TXIM_BitNum);
			  }else if (obj->TXFIFILevelSel==TX_FIFO_7_8 || obj->TXFIFILevelSel==TX_FIFO_3_4 || obj->TXFIFILevelSel==TX_FIFO_1_2
					  || obj->TXFIFILevelSel==TX_FIFO_1_4 ||obj->TXFIFILevelSel==TX_FIFO_1_8){
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_RXIM_BitNum);
				  HW_WRITE_REG32_MASKED(base+UART_INTERRUPT_FIFO_LEVEL_SELECT_OFFSET , obj->RXFIFILevelSel , UART_INTERRUPT_FIFO_LEVEL_SELECT_RXIFLSEL_Field);
			  }else if(obj->TXFIFILevelSel==END_OF_TRANSMIT){
				//The UART_CONTROL register should not be changed while the UART is enabled or else the results
				//  are unpredictable.
					FifoEn=HW_READ_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);
				  UARTDisable(base);
				  HW_SET_BIT(base+UART_CONTROL_OFFSET,UART_CONTROL_EOT_BitNum);
					HW_WRITE_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
				  UARTEnable(base);
			  }else{
				  state=INCORRECT_InterruptConfig;
			  }
			  if((obj->ClearToSend==FALSE)&&(base==BASE_UART1)){
				  HW_RESET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_CTSIM_BitNum);
			  }else if ((obj->ClearToSend!=FALSE)&&(base==BASE_UART1)){
				  HW_SET_BIT(base+UART_INTERRUPT_MASK_OFFSET,UART_INTERRUPT_MASK_CTSIM_BitNum);
			  }else if ((obj->ClearToSend==FALSE)&&(base!=BASE_UART1)){}
			  else{
				  state=INCORRECT_InterruptConfig;
			  }
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}

gUARTError_t UARTBreak(uint32 base ,uint8 send){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
		      if (send==FALSE){
			      HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_BRK_BitNum);
		       }else{
     	          HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_BRK_BitNum);
		       }
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}

gUARTError_t UARTDMAEnable(uint32 base ,uint8 flags){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   if(flags & DMA_on_Error)   HW_SET_BIT(base+UART_DMA_CONTROL_OFFSET,UART_DMA_CONTROL_DMAERR_BitNum);
			   if(flags & Transmit_DMA)   HW_SET_BIT(base+UART_DMA_CONTROL_OFFSET,UART_DMA_CONTROL_TXDMAE_BitNum);
			   if(flags & Receive_DMA)   HW_SET_BIT(base+UART_DMA_CONTROL_OFFSET,UART_DMA_CONTROL_RXDMAE_BitNum);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UARTDMADisable(uint32 base ,uint8 flags){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   if(flags & DMA_on_Error)   HW_RESET_BIT(base+UART_DMA_CONTROL_OFFSET,UART_DMA_CONTROL_DMAERR_BitNum);
			   if(flags & Transmit_DMA)   HW_RESET_BIT(base+UART_DMA_CONTROL_OFFSET,UART_DMA_CONTROL_TXDMAE_BitNum);
			   if(flags & Receive_DMA)    HW_RESET_BIT(base+UART_DMA_CONTROL_OFFSET,UART_DMA_CONTROL_RXDMAE_BitNum);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UART9bitEnable (uint32 base){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   HW_SET_BIT(base+UART_9BIT_SELF_ADDRESS_OFFSET,UART_9BIT_SELF_ADDRESS_9BITEN_BitNum);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}

gUARTError_t UART9bitDisable (uint32 base){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   HW_RESET_BIT(base+UART_9BIT_SELF_ADDRESS_OFFSET,UART_9BIT_SELF_ADDRESS_9BITEN_BitNum);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UART9bitAddrSet(uint32 base , uint32 add ,uint32 mask){
	gUARTError_t state=Pass;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   HW_WRITE_REG32_MASKED(base+UART_9BIT_SELF_ADDRESS_OFFSET , add , UART_9BIT_SELF_ADDRESS_ADDR_Field) ;
			   HW_WRITE_REG_32BIT(base+UART_9BIT_SELF_ADDRESS_OFFSET,mask);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UART9bitAddrSend(uint32 base ,uint32 add){
	gUARTError_t state=Pass;
	uint32 PastLineControlReg;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){
			   // Wait until the FIFO is empty and the UART is not busy To match the transmission time with correct parity settings.
			   while((HW_READ_BIT(UART_FLAG_OFFSET,UART_FLAG_TXFE_BitNum)==0)||(HW_READ_BIT(UART_FLAG_OFFSET,UART_FLAG_BUSY_BitNum)==1));
			   // Force the address/data bit to 1 to indicate this is an address byte by changing the parity settings to sticky parity
			   //with odd parity
			   PastLineControlReg=HW_READ_REG_32BIT(base+UART_LINE_CONTROL_OFFSET);
			   HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_SPS_BitNum);
			   HW_RESET_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_EPS_BitNum);
			   HW_SET_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_PEN_BitNum);
			   // Send the address.
			   HW_WRITE_REG_32BIT(base+UART_DATA_OFFSET,add);
			   // Wait until the address has been sent.
			   while((HW_READ_BIT(UART_FLAG_OFFSET,UART_FLAG_TXFE_BitNum)==0)||(HW_READ_BIT(UART_FLAG_OFFSET,UART_FLAG_BUSY_BitNum)==1));
			   // Restore the Line control setting.
			   HW_WRITE_REG_32BIT(base+UART_LINE_CONTROL_OFFSET,PastLineControlReg);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


void UART1FlowControlSet( uint8 RTS_State, uint8 CTS_Enable ){
	uint8 FifoEn;
FifoEn=HW_READ_BIT(BASE_UART1+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);	
			   UARTDisable(BASE_UART1);
			   if (RTS_State==HW_RequestToSend){
				   HW_SET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_RTSEN_BitNum);
			   }else{
				   HW_RESET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_RTSEN_BitNum);
			   }
			   if (CTS_Enable ==FALSE){
				   HW_RESET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_CTSEN_BitNum);
			   }else{
				   HW_SET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_CTSEN_BitNum);
			   }
				 HW_WRITE_BIT(BASE_UART1+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
			   UARTEnable(BASE_UART1);
		   }

void UART1FlowControlDisable( uint8 RTS_Disable, uint8 CTS_Disable ){
		uint8 FifoEn;
FifoEn=HW_READ_BIT(BASE_UART1+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);
				   UARTDisable(BASE_UART1);
			   if (RTS_Disable)   {
				   HW_RESET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_RTSEN_BitNum);
				   HW_RESET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_RTS_BitNum);
			   }
			   if (CTS_Disable)   HW_RESET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_CTSEN_BitNum);
				 HW_WRITE_BIT(BASE_UART1+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
			   UARTEnable(BASE_UART1);
		   }

void UART1RequestToSend(void){
			uint8 FifoEn;
FifoEn=HW_READ_BIT(BASE_UART1+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);
	UARTDisable(BASE_UART1);
	HW_SET_BIT(BASE_UART1+UART_CONTROL_OFFSET , UART_CONTROL_RTS_BitNum);
	HW_WRITE_BIT(BASE_UART1+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
	UARTEnable(BASE_UART1);
}

gUARTError_t EnableSIR(uint32 base , uint8 lowPowerEn ,fp32 SysClk){
	gUARTError_t state=Pass;
	uint8 FifoEn;
	uint32 IrLPDivisor;
		   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
	    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){

			   //The UART_CONTROL register should not be changed while the UART is enabled or else the results
			   //  are unpredictable.
				 FifoEn=HW_READ_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);		
			   UARTDisable(base);
			   HW_SET_BIT(base+UART_CONTROL_OFFSET,UART_CONTROL_SIREN_BitNum);
			   IrLPDivisor=(uint32)SysClk/FIrLPBaud16;
			   HW_WRITE_REG_32BIT(base+UART_IRDA_LOW_POWER_REGISTER_OFFSET,IrLPDivisor);
			   if(lowPowerEn==FALSE){
			   HW_RESET_BIT(base+UART_CONTROL_OFFSET,UART_CONTROL_SIRLP_BitNum);
			   }else{
			   HW_SET_BIT(base+UART_CONTROL_OFFSET,UART_CONTROL_SIRLP_BitNum);
			   }
				 HW_WRITE_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
			   UARTEnable(base);
		   }else{
	  			state= INCORRECT_MODULE;
	       }
	  	return state;
}


gUARTError_t UARTDisableSIR(uint32 base){
	uint8 FifoEn;
	gUARTError_t state=Pass;
			   if(base==BASE_UART0 || base==BASE_UART1 || base==BASE_UART2 || base==BASE_UART3 ||
		    	  base==BASE_UART4 || base==BASE_UART5 || base==BASE_UART6 || base==BASE_UART7 ){

				   //The UART_CONTROL register should not be changed while the UART is enabled or else the results
				   //  are unpredictable.
					 FifoEn=HW_READ_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum);	
				   UARTDisable(base);
				   HW_RESET_BIT(base+UART_CONTROL_OFFSET,UART_CONTROL_SIREN_BitNum);
					 HW_WRITE_BIT(base+UART_LINE_CONTROL_OFFSET,UART_LINE_CONTROL_FEN_BitNum,FifoEn);
				   UARTEnable(base);
				   		   }else{
				   	  			state= INCORRECT_MODULE;
				   	       }
				   	  	return state;
}


