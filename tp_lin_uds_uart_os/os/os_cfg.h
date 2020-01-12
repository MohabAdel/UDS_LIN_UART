// OS.h
// Runs on either the TM4C123 or MSP432 with an Educational BoosterPack MKII (BOOSTXL-EDUMKII)
// This file contains the function prototypes for the software interface to the MKII BoosterPack.
// This board support package (OS) is an abstraction layer,
//   forming a bridge between the low-level hardware and the high-level software.

// Daniel and Jonathan Valvano
// June 8, 2016

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
   ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
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


void OS_Clock_InitFastest(void);

// ------------OS_Clock_GetFreq------------
// Return the current system clock frequency for the
// LaunchPad.
// Input: none
// Output: system clock frequency in cycles/second
uint32_t OS_Clock_GetFreq(void);

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
void OS_PeriodicTask_Init(void(*task)(void), uint32_t freq, uint8_t priority);

// ------------OS_PeriodicTask_Stop------------
// Deactivate the interrupt running a user task
// periodically.
// The automatic grader in TExaS calls this function and
// uses this hardware.  Do not call this function if using
// the automatic grader.
// Input: none
// Output: none
void OS_PeriodicTask_Stop(void);

// ------------OS_PeriodicTask_Restart------------
// Reactivate the interrupt running a user task periodically.
// Input: none
// Output: none
void OS_PeriodicTask_Restart(void);

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
void OS_PeriodicTask_InitB(void(*task)(void), uint32_t freq, uint8_t priority);
 
// ------------OS_PeriodicTask_StopB------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void OS_PeriodicTask_StopB(void);

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
void OS_PeriodicTask_InitC(void(*task)(void), uint32_t freq, uint8_t priority);

// ------------OS_PeriodicTask_StopC------------
// Deactivate the interrupt running a user task
// periodically.
// Input: none
// Output: none
void OS_PeriodicTask_StopC(void);

// ------------OS_Time_Init------------
// Activate a 32-bit timer to count the number of
// microseconds since the timer was initialized.
// Input: none
// Output: none
// Assumes: OS_Clock_InitFastest() has been called
void OS_Time_Init(void);

// ------------OS_Time_Get------------
// Return the system time in microseconds, which is the
// number of 32-bit timer counts since the timer was
// initialized.  This will work properly for at least 23
// minutes after which it could roll over.
// Input: none
// Output: system time in microseconds
// Assumes: OS_Time_Init() has been called
uint32_t OS_Time_Get(void);


