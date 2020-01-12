// OS.c
// Runs on TM4C123 with an Educational BoOSterPack MKII (BOOSTXL-EDUMKII)
// This file contains the software interface to the MKII BoOSterPack.
// This board support package (OS) is an abstraction layer,
//   forming a bridge between the low-level hardware and the high-level software.

// Remember to remove R9 and R10 to use the LCD since R10
// connects PD1 (accelerometer Y) to PB7 (LCD SPI data).
// Daniel and Jonathan Valvano
// June 8, 2016

/* This example accompanies the books
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
      ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
      ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
      ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2016

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

//  J1   J3               J4   J2
// [ 1] [21]             [40] [20]
// [ 2] [22]             [39] [19]
// [ 3] [23]             [38] [18]
// [ 4] [24]             [37] [17]
// [ 5] [25]             [36] [16]
// [ 6] [26]             [35] [15]
// [ 7] [27]             [34] [14]
// [ 8] [28]             [33] [13]
// [ 9] [29]             [32] [12]
// [10] [30]             [31] [11]



#include <stdint.h>
#include "os_cfg.h"
#include "../RAL/tm4c123gh6pm.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

static uint32_t ClockFrequency = 16000000; // cycles/second


void OS_Clock_InitFastest(void){
  // 0) configure the system to use RCC2 for advanced features
  //    such as 400 MHz PLL and non-integer System Clock Divisor
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  // 2) select the crystal value and OScillator source
  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear OScillator source field
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main OScillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  // 4) set the desired system divider and the system divider least significant bit
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
                  + (4<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
  ClockFrequency = 80000000;
}

// ------------OS_Clock_GetFreq------------
// Return the current system clock frequency for the
// LaunchPad.
// Input: none
// Output: system clock frequency in cycles/second
uint32_t OS_Clock_GetFreq(void){
  return ClockFrequency;
}

// ------------OS_PeriodicTask_Init------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTask)(void);   // user function
void OS_PeriodicTask_Init(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTask = task;             // user function
  // ***************** Wide Timer5A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x20;     // activate clock for Wide Timer5
  while((SYSCTL_PRWTIMER_R&0x20) == 0){};// allow time for clock to stabilize
  WTIMER5_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer5A during setup
  WTIMER5_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   
  WTIMER5_TAMR_R = TIMER_TAMR_TAMR_PERIOD; // configure for periodic mode, default down-count settings
  WTIMER5_TAILR_R = (ClockFrequency/freq - 1); // reload value
  WTIMER5_TAPR_R = 0;              // bus clock resolution
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER5A timeout flag
  WTIMER5_IMR_R |= TIMER_IMR_TATOIM;// arm timeout interrupt
//PRIn Bit   Interrupt
//Bits 31:29 Interrupt [4n+3]
//Bits 23:21 Interrupt [4n+2], 
//Bits 15:13 Interrupt [4n+1]
//Bits 7:5   Interrupt [4n]   n=26 => (4n)=104
  NVIC_PRI26_R = (NVIC_PRI26_R&0xFFFFFF00)|(priority<<5); // priority
// interrupts enabled in the main program after all devices initialized
// vector number 120, interrupt number 104
// 32 bits in each NVIC_ENx_R register, 104/32 = 3 remainder 8
  NVIC_EN3_R = 1<<8;               // enable IRQ 104 in NVIC
  WTIMER5_CTL_R |= TIMER_CTL_TAEN; // enable Wide Timer0A 32-b
  EndCritical(sr);
}

void WTIMER5A_Handler(void){
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// acknowledge Wide Timer5A timeout
  (*PeriodicTask)();               // execute user task
}

// ------------OS_PeriodicTask_Stop------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void OS_PeriodicTask_Stop(void){
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER5A timeout flag
  NVIC_DIS3_R = 1<<8;              // disable IRQ 104 in NVIC
}
// ------------OS_PeriodicTask_Restart------------
// Reactivate the interrupt running a user task periodically.
// Input: none
// Output: none
void OS_PeriodicTask_Restart(void){
  WTIMER5_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER5A timeout flag
  NVIC_EN3_R = 1<<8;              // enable IRQ 104 in NVIC
}

// ------------OS_PeriodicTask_InitB------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTaskB)(void);   // user function
void OS_PeriodicTask_InitB(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTaskB = task;             // user function
  // ***************** Wide Timer4A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x10;     // activate clock for Wide Timer4
  while((SYSCTL_PRWTIMER_R&0x10) == 0){};// allow time for clock to stabilize
  WTIMER4_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer4A during setup
  WTIMER4_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER4_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  WTIMER4_TAILR_R = (ClockFrequency/freq - 1); // reload value
  WTIMER4_TAPR_R = 0;              // bus clock resolution
  WTIMER4_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER4A timeout flag
  WTIMER4_IMR_R |= TIMER_IMR_TATOIM;// arm timeout interrupt
//PRIn Bit   Interrupt
//Bits 31:29 Interrupt [4n+3]
//Bits 23:21 Interrupt [4n+2], n=25 => (4n+2)=102
//Bits 15:13 Interrupt [4n+1]
//Bits 7:5 Interrupt [4n]
  NVIC_PRI25_R = (NVIC_PRI25_R&0xFF00FFFF)|(priority<<21); // priority
// interrupts enabled in the main program after all devices initialized
// vector number 118, interrupt number 102
// 32 bits in each NVIC_ENx_R register, 102/32 = 3 remainder 6
  NVIC_EN3_R = 1<<6;               // enable IRQ 102 in NVIC
  WTIMER4_CTL_R |= TIMER_CTL_TAEN; // enable Wide Timer4A 32-b
  EndCritical(sr);
}

void WTIMER4A_Handler(void){
  WTIMER4_ICR_R = TIMER_ICR_TATOCINT;// acknowledge Wide Timer4A timeout
  (*PeriodicTaskB)();               // execute user task
}

// ------------OS_PeriodicTask_StopB------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void OS_PeriodicTask_StopB(void){
  WTIMER4_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER4A timeout flag
  NVIC_DIS3_R = 1<<6;              // disable IRQ 102 in NVIC
}


// ------------OS_PeriodicTask_InitC------------
// Activate an interrupt to run a user task periodically.
// Give it a priority 0 to 6 with lower numbers
// signifying higher priority.  Equal priority is
// handled sequentially.
// Input:  task is a pointer to a user function
//         freq is number of interrupts per second
//           1 Hz to 10 kHz
//         priority is a number 0 to 6
// Output: none
void (*PeriodicTaskC)(void);   // user function
void OS_PeriodicTask_InitC(void(*task)(void), uint32_t freq, uint8_t priority){long sr;
  if((freq == 0) || (freq > 10000)){
    return;                        // invalid input
  }
  if(priority > 6){
    priority = 6;
  }
  sr = StartCritical();
  PeriodicTaskC = task;             // user function
  // ***************** Wide Timer3A initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x08;     // activate clock for Wide Timer3
  while((SYSCTL_PRWTIMER_R&0x08) == 0){};// allow time for clock to stabilize
  WTIMER3_CTL_R &= ~TIMER_CTL_TAEN;// disable Wide Timer3A during setup
  WTIMER3_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER3_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  WTIMER3_TAILR_R = (ClockFrequency/freq - 1); // reload value
  WTIMER3_TAPR_R = 0;              // bus clock resolution
  WTIMER3_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER3A timeout flag
  WTIMER3_IMR_R |= TIMER_IMR_TATOIM;// arm timeout interrupt
//PRIn Bit   Interrupt
//Bits 31:29 Interrupt [4n+3]
//Bits 23:21 Interrupt [4n+2]
//Bits 15:13 Interrupt [4n+1]
//Bits 7:5   Interrupt [4n]  , n=25 => (4n+0)=100
  NVIC_PRI25_R = (NVIC_PRI25_R&0xFFFFFF00)|(priority<<5); // priority
// interrupts enabled in the main program after all devices initialized
// vector number 116, interrupt number 100
// 32 bits in each NVIC_ENx_R register, 100/32 = 3 remainder 4
  NVIC_EN3_R = 1<<4;               // enable IRQ 100 in NVIC
  WTIMER3_CTL_R |= TIMER_CTL_TAEN; // enable Wide Timer3A 32-b
  EndCritical(sr);
}

void WTIMER3A_Handler(void){
  WTIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge Wide Timer3A timeout
  (*PeriodicTaskC)();               // execute user task
}

// ------------OS_PeriodicTask_StopC------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void OS_PeriodicTask_StopC(void){
  WTIMER3_ICR_R = TIMER_ICR_TATOCINT;// clear WTIMER3A timeout flag
  NVIC_DIS3_R = 1<<4;              // disable IRQ 100 in NVIC
}

// ------------OS_Time_Init------------
// Activate a 32-bit timer to count the number of
// micrOSeconds since the timer was initialized.
// Input: none
// Output: none
// Assumes: OS_Clock_InitFastest() has been called
//          so clock = 80/80 = 1 MHz
void OS_Time_Init(void){long sr;
  sr = StartCritical();
  // ***************** Wide Timer5B initialization *****************
  SYSCTL_RCGCWTIMER_R |= 0x20;     // activate clock for Wide Timer5
  while((SYSCTL_PRWTIMER_R&0x20) == 0){};// allow time for clock to stabilize
  WTIMER5_CTL_R &= ~TIMER_CTL_TBEN;// disable Wide Timer5B during setup
  WTIMER5_CFG_R = TIMER_CFG_16_BIT;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER5_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
  WTIMER5_TBILR_R = 0xFFFFFFFF;    // reload value
  WTIMER5_TBPR_R = 79;             // 1 MHz resolution
  WTIMER5_ICR_R = TIMER_ICR_TBTOCINT;// clear WTIMER5B timeout flag
  WTIMER5_IMR_R &= ~TIMER_IMR_TBTOIM;// disarm timeout interrupt
  WTIMER5_CTL_R |= TIMER_CTL_TBEN; // enable Wide Timer0B 32-b
  EndCritical(sr);
}

// ------------OS_Time_Get------------
// Return the system time in micrOSeconds, which is the
// number of 32-bit timer counts since the timer was
// initialized.  This will work properly for at least 71
// minutes after which it could roll over.
// Input: none
// Output: system time in micrOSeconds
// Assumes: OS_Time_Init() has been called
uint32_t OS_Time_Get(void){
  // 2*32/1,000,000 = 4,294 seconds, about 71 minutes
  return (0xFFFFFFFF - WTIMER5_TBV_R);
}

