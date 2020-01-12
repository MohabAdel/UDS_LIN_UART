// UART.c
// Runs on LM3S811, LM3S1968, LM3S8962, LM4F120, TM4C123
// Simple device driver for the UART.
// Daniel Valvano
// May 30, 2014
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu
#include "UART.h"
/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Program 4.12, Section 4.9.4, Figures 4.26 and 4.40

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

//extern int32_t NewSwData;  //semaphore TP layer
//extern int32_t NewReceData;
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode



//------------UART_Init------------
// Initialize the UART for 115,200 baud rate (assuming 50 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(uint32_t baudrate){
	uint32_t x =(OS_Clock_GetFreq()/ (16* baudrate));
  SYSCTL_RCGCUART_R |= 0x01;            // activate UART0
  SYSCTL_RCGCGPIO_R |= 0x01;            // activate port A
	RxFifo_Init();
	TxFifo_Init();
  while((SYSCTL_PRGPIO_R&0x01) == 0){};
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	UART0_LCRH_R &=~UART_LCRH_FEN;
  UART0_IBRD_R = (int)x;                     // IBRD = int(80,000,000 / (16 * 115,200)) = int(3.4028)
  UART0_FBRD_R = (int) ((x- (int)(x))*64 + 0.5);                   // FBRD = int(0.4028 * 64 + 0.5) = 26
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_IFLS_R &= ~0x3F;                // clear TX and RX interrupt FIFO level fields
                                        // configure interrupt for TX FIFO <= 1/8 full
                                        // configure interrupt for RX FIFO >= 1/8 full
  UART0_IFLS_R += (UART_IFLS_TX4_8|UART_IFLS_RX4_8);  // 4_8 8 Bytesreceived Interrupt !!!
                                        // enable TX and RX FIFO interrupts and RX time-out interrupt
  UART0_IM_R |= (UART_IM_RXIM|UART_IM_TXIM);
	//	UART0_IM_R |= (UART_IM_RXIM);
  UART0_CTL_R |= 0x301;                 // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R = 0;               // disable analog functionality on PA
                                        // UART0=priority 2
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFF00FF)|0x00004000; // bits 13-15
  NVIC_EN0_R = NVIC_EN0_INT5;           // enable interrupt 5 in NVIC
  EnableInterrupts();
}

// copy from hardware RX FIFO to software RX FIFO
// stop when hardware RX FIFO is empty or software RX FIFO is full
void copyHardwareToSoftware(void){
  char letter;
  while(((UART0_FR_R&UART_FR_RXFE) == 0) && (RxFifo_Size() < (FIFOSIZE - 1))){
    letter = UART0_DR_R;
    RxFifo_Put(letter);
  }
}

// copy from software TX FIFO to hardware TX FIFO
// stop when software TX FIFO is empty or hardware TX FIFO is full
void copySoftwareToHardware(void){
  char letter;
  while(((UART0_FR_R&UART_FR_TXFF) == 0) && (TxFifo_Size() > 0)){
    TxFifo_Get(&letter);
    UART0_DR_R = letter;
  }
}
/*
//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void){
  //while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((char)(UART0_DR_R&0xFF));
}
*/
// input ASCII character from UART
// spin if RxFifo is empty
char UART_InChar(void){  //USING FIFO
  char letter;
  while( (RxFifo_Get(&letter) == FIFOFAIL)){};
	return(letter);
}


/*
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}
*/

// output ASCII character to UART
// spin if TxFifo is full
void UART_OutChar(char data){  //USING FIFO
  while(TxFifo_Put(data) == FIFOFAIL){};
  UART0_IM_R &= ~UART_IM_TXIM;          // disable TX FIFO interrupt
  copySoftwareToHardware();
  UART0_IM_R |= UART_IM_TXIM;           // enable TX FIFO interrupt
}


//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}

void UART_OutStringLen(char *pt,int32_t len){
	 while(len--){
    UART_OutChar(*pt);
    pt++;
  }
}


//------------UART_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t UART_InUDec(void){
uint32_t number=0, length=0;
char character;
  character = UART_InChar();
  while(character != CR){ // accepts until <enter> is typed
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      //UART_OutChar(character);
    }
// If the input is a backspace, then the return number is
// changed and a backspace is outputted to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      //UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

//-----------------------UART_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART_OutUDec(uint32_t n){
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
  if(n >= 10){
    UART_OutUDec(n/10);
    n = n%10;
  }
  UART_OutChar(n+'0'); /* n is between 0 and 9 */
}

//---------------------UART_InUHex----------------------------------------
// Accepts ASCII input in unsigned hexadecimal (base 16) format
// Input: none
// Output: 32-bit unsigned number
// No '$' or '0x' need be entered, just the 1 to 8 hex digits
// It will convert lower case a-f to uppercase A-F
//     and converts to a 16 bit unsigned number
//     value range is 0 to FFFFFFFF
// If you enter a number above FFFFFFFF, it will return an incorrect value
// Backspace will remove last digit typed
uint32_t UART_InUHex(void){
uint32_t number=0, digit, length=0;
char character;
  character = UART_InChar();
  while(character != CR){
    digit = 0x10; // assume bad
    if((character>='0') && (character<='9')){
      digit = character-'0';
    }
    else if((character>='A') && (character<='F')){
      digit = (character-'A')+0xA;
    }
    else if((character>='a') && (character<='f')){
      digit = (character-'a')+0xA;
    }
// If the character is not 0-9 or A-F, it is ignored and not echoed
    if(digit <= 0xF){
      number = number*0x10+digit;
      length++;
      //UART_OutChar(character);
    }
// Backspace outputted and return value changed if a backspace is inputted
    else if((character==BS) && length){
      number /= 0x10;
      length--;
      //UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

//--------------------------UART_OutUHex----------------------------
// Output a 32-bit number in unsigned hexadecimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1 to 8 digits with no space before or after
void UART_OutUHex(uint32_t number){
// This function uses recursion to convert the number of
//   unspecified length as an ASCII string
  if(number >= 0x10){
    UART_OutUHex(number/0x10);
    UART_OutUHex(number%0x10);
  }
  else{
    if(number < 0xA){
      UART_OutChar(number+'0');
     }
    else{
      UART_OutChar((number-0x0A)+'A');
    }
  }
}

//------------UART_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is inputted.
// If a backspace is inputted, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void UART_InString(char *bufPt, uint16_t max) {
int length=0;

char character;
  character = UART_InChar();
  while(character != '*'){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
       // UART_OutChar(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      //UART_OutChar(character);
    }
    character = UART_InChar();
  }
  *bufPt = 0;
}
/*
// at least one of three things has happened:
// hardware TX FIFO goes from 3 to 2 or less items
// hardware RX FIFO goes from 1 to 2 or more items
// UART receiver has timed out
void UART0_Handler(void){
  
}
*/






void uart_tpSendFrame(uint8_t *buffer)
{
#ifdef DEBUG
    uint8 testData[8], index = 0;
    for (index = 0; index < 8; index++)
    {

        testData[index] = buffer[index];
    }
#endif
    uint8_t count = 8;
    while (count--)
    {
        //while ((UART0_FR_R & (1 << 5)) != 0){}
           UART_OutChar(*buffer);
        buffer++;
    }
}

void uart_tpRecevFrame(uint8_t * buffer)
{
    uint8_t count = 8;
    while (count--)
    {
      /*  while ((UART0_FR_R & (1 << 4)) != 0)
            ;*/

        *buffer = UART_InChar();
        buffer++;
    }

#ifdef DEBUG
    uint8 testData[8],index = 0;
    for (index = 0; index < 8; index++)
    {

        testData[index] = buffer[index];
    }
#endif
}


void UART_Enable_LoopBack(void){
	UART0_CTL_R|=0x80;
}

void UART_Send_Break(void){
  UART0_LCRH_R|=0x01;
}
void UART_Stop_Break(void){
	UART0_LCRH_R&=~0x01;
}
