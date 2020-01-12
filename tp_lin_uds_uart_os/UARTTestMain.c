// UARTTestMain.c
// Runs on LM4F120/TM4C123
// Used to test the UART.c driver
// Daniel Valvano
// May 30, 2014

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

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
#include <stdint.h>
//#include "CPX/PLL/PLL.h"
#include "CPX/UART/UART.h"
#include "SAL/tp_transiver.h"
#include "os/os.h"
//Interactive Task with TP layer
int count0,count1,count2,count3,count4,count5,count6;
#define THREADFREQ 1000
uint8 DataMain[40];
uint8 DataLen;

void Task0(){

			while(1){
				// tp_sender("ROUND 7 Test X", 15);
				
				 tp_receiver(DataMain,&DataLen);
				 count0++;
				 if(DataLen !=0){
				 UART_OutStringLen((char*)DataMain,DataLen);
			   }	
	     }
}

//Idle Task
void Task1(){
	while(1){
		tp_sender("ROUND 7 Test X", 15);
		count1++;
		
	}
}

void Task2(){
	while(1){
		count2++;
	}
}

void Task3(){
	while(1){
		count3++;
	}
}

void Task4(){
	while(1){
		count4++;
	}
}

void Task5(){
	while(1){
		count5++;
	}
}

void Task6(){
	while(1){
		count6++;
	}
}

/*
//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void static OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
*/
//debug code
 char ch;
int main(void){
 
  //char string[50];  // global to assist in debugging
 // uint32_t n;
	OS_Init();
  OS_AddThreads(&Task0,0,&Task1,0,&Task2,0,&Task3,0,&Task4,0,&Task5,0,&Task6,0);
			/*PLL_Init(Bus80MHz);
			//UART_Init(115200);              // initialize UART
			*/
	tp_Init();
	OS_Launch(OS_Clock_GetFreq()/THREADFREQ); // doesn't return, interrupts enabled in here
	while(1){
  // tp_sender("Mohab Adel bla",15);
		

	}
}




