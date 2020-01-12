// os.c
// Runs on LM4F120/TM4C123/MSP432
// A priority/blocking real-time operating system 
// Lab 4 starter file.
// Daniel Valvano
// March 25, 2016
// Hint: Copy solutions from Lab 3 into Lab 4
#include <stdint.h>
#include "os.h"

#include "../RAL/tm4c123gh6pm.h"
#define FIFOSIZE 16

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void StartOS(void);
// function definitions in osasm.s
#define STCTRL          (*((volatile uint32_t *)0xE000E010))
#define STRELOAD        (*((volatile uint32_t *)0xE000E014))
#define STCURRENT       (*((volatile uint32_t *)0xE000E018))
#define INTCTRL         (*((volatile uint32_t *)0xE000ED04))
#define SYSPRI1         (*((volatile uint32_t *)0xE000ED18))
#define SYSPRI2         (*((volatile uint32_t *)0xE000ED1C))
#define SYSPRI3         (*((volatile uint32_t *)0xE000ED20))
#define SYSHNDCTRL      (*((volatile uint32_t *)0xE000ED24))
#define FAULTSTAT       (*((volatile uint32_t *)0xE000ED28))
#define HFAULTSTAT      (*((volatile uint32_t *)0xE000ED2C))
#define MMADDR          (*((volatile uint32_t *)0xE000ED34))
#define FAULTADDR       (*((volatile uint32_t *)0xE000ED38))



#define NUMTHREADS 7 // maximum number of threads
#define NUMPERIODIC 2 // maximum number of periodic threads
#define STACKSIZE 100 // number of 32-bit words in stack per thread
//new
struct tcb{
 int32_t *sp; // pointer to stack (valid for threads not running
 struct tcb *next; // linked-list pointer
//*FILL THIS IN****
 int32_t *blocked;
 uint32_t sleep;
 uint8_t Priority; // 0 is highest, 254 lowest
};
typedef struct tcb tcbType;
tcbType tcbs[NUMTHREADS];
tcbType *RunPt;
int32_t Stacks[NUMTHREADS][STACKSIZE];
void static runperiodicevents(void);

// ******** OS_Init ************
// Initialize operating system, disable interrupts
// Initialize OS controlled I/O: periodic interrupt, bus clock as fast as possible
// Initialize OS global variables
// Inputs:  none
// Outputs: none
//new
int32_t numPeriodicEvents;
void OS_Init(void){
  DisableInterrupts();
  OS_Clock_InitFastest();// set processor clock to fastest speed
// perform any initializations needed, 
// set up periodic timer to run runperiodicevents to implement sleeping
  numPeriodicEvents = 0;
  OS_PeriodicTask_Init(&runperiodicevents, 1000, 0);
  EnableInterrupts();
}
//new
void SetInitialStack(int i){
 // ****IMPLEMENT THIS**** 
 // **Same as Lab 2 and Lab 3****
 tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
 Stacks[i][STACKSIZE-1] = 0x01000000; // thumb bit
 Stacks[i][STACKSIZE-3] = 0x14141414; // R14
 Stacks[i][STACKSIZE-4] = 0x12121212; // R12
 Stacks[i][STACKSIZE-5] = 0x03030303; // R3
 Stacks[i][STACKSIZE-6] = 0x02020202; // R2
 Stacks[i][STACKSIZE-7] = 0x01010101; // R1
 Stacks[i][STACKSIZE-8] = 0x00000000; // R0
 Stacks[i][STACKSIZE-9] = 0x11111111; // R11
 Stacks[i][STACKSIZE-10] = 0x10101010; // R10
 Stacks[i][STACKSIZE-11] = 0x09090909; // R9
 Stacks[i][STACKSIZE-12] = 0x08080808; // R8
 Stacks[i][STACKSIZE-13] = 0x07070707; // R7
 Stacks[i][STACKSIZE-14] = 0x06060606; // R6
 Stacks[i][STACKSIZE-15] = 0x05050505; // R5
 Stacks[i][STACKSIZE-16] = 0x04040404; // R4
}
//******** OS_AddThreads ***************
// Add eight main threads to the scheduler
// Inputs: function pointers to eight void/void main threads
//         priorites for each main thread (0 highest)
// Outputs: 1 if successful, 0 if this thread can not be added
// This function will only be called once, after OS_Init and before OS_Launch
//new
int OS_AddThreads(void(*thread0)(void), uint32_t p0,
    void(*thread1)(void), uint32_t p1,
    void(*thread2)(void), uint32_t p2,
    void(*thread3)(void), uint32_t p3,
	  void(*thread4)(void), uint32_t p4,
		void(*thread5)(void), uint32_t p5,
		void(*thread6)(void), uint32_t p6
)
 {
// **similar to Lab 3. initialize priority field****
 int32_t status; 
 status = StartCritical();
for(int i = 0; i < NUMTHREADS; i++){
 tcbs[i].next = &tcbs[((i+1) % NUMTHREADS)];
 tcbs[i].blocked = 0;
 tcbs[i].sleep = 0;
}
 
 SetInitialStack(0); Stacks[0][STACKSIZE-2] = (int32_t)(thread0); // PC
 SetInitialStack(1); Stacks[1][STACKSIZE-2] = (int32_t)(thread1); // PC
 SetInitialStack(2); Stacks[2][STACKSIZE-2] = (int32_t)(thread2); // PC
 SetInitialStack(3); Stacks[3][STACKSIZE-2] = (int32_t)(thread3); // PC
 SetInitialStack(4); Stacks[4][STACKSIZE-2] = (int32_t)(thread4); // PC
 SetInitialStack(5); Stacks[5][STACKSIZE-2] = (int32_t)(thread5); // PC
 SetInitialStack(6); Stacks[6][STACKSIZE-2] = (int32_t)(thread6); // PC
 tcbs[0].Priority = p0; // priority
 tcbs[1].Priority = p1; // priority
 tcbs[2].Priority = p2; // priority
 tcbs[3].Priority = p3; // priority
 tcbs[4].Priority = p4; // priority
 tcbs[5].Priority = p5; // priority
 tcbs[5].Priority = p6; // priority
 RunPt = &tcbs[0]; // thread 0 will run first
 EndCritical(status); 
 return 1; // successful
}

//new

void static runperiodicevents(void){
  for (int i = 0; i < NUMTHREADS; i++) {
    if (tcbs[i].sleep) 
      tcbs[i].sleep--;
  } 
}

//******** OS_Launch ***************
// Start the scheduler, enable interrupts
// Inputs: number of clock cycles for each time slice
// Outputs: none (does not return)
// Errors: theTimeSlice must be less than 16,777,216
void OS_Launch(uint32_t theTimeSlice){
  STCTRL = 0;                  // disable SysTick during setup
  STCURRENT = 0;               // any write to current clears it
  SYSPRI3 =(SYSPRI3&0x00FFFFFF)|0xE0000000; // priority 7
  STRELOAD = theTimeSlice - 1; // reload value
  STCTRL = 0x00000007;         // enable, core clock and interrupt arm
  StartOS();                   // start on the first task
}
// runs every ms
//new
void Scheduler(void){      // every time slice
// ****IMPLEMENT THIS****
//-- look at all threads in TCB list choose
// highest priority thread not blocked and not sleeping 
// If there are multiple highest priority (not blocked, not sleeping) run these round robin
uint32_t max = 255; //max
	tcbType *pt;
	tcbType *bestPt;
	pt = RunPt; //search for highest priority thread that was not blocked and not sleeping
	
	do{
		pt = pt->next;
		if((pt->Priority < max)&&((pt->blocked)== 0)&&((pt->sleep)== 0)){
			max = pt->Priority;
			bestPt = pt;
		}
	}while(RunPt != pt);
	RunPt = bestPt;

}

//******** OS_Suspend ***************
// Called by main thread to cooperatively suspend operation
// Inputs: none
// Outputs: none
// Will be run again depending on sleep/block status
void OS_Suspend(void){
  STCURRENT = 0;        // any write to current clears it
  INTCTRL = 0x04000000; // trigger SysTick
// next thread gets a full time slice
}

// ******** OS_Sleep ************
// place this thread into a dormant state
// input:  number of msec to sleep
// output: none
// OS_Sleep(0) implements cooperative multitasking
//new
void OS_Sleep(uint32_t sleepTime){
// ****IMPLEMENT THIS****
// set sleep parameter in TCB, same as Lab 3
// suspend, stops running
 DisableInterrupts();
 RunPt->sleep = sleepTime; // reason it is blocked
 EnableInterrupts(); // interrupts can occur here
 OS_Suspend(); // run thread switcher
 
}

// ******** OS_InitSemaphore ************
// Initialize counting semaphore
// Inputs:  pointer to a semaphore
//          initial value of semaphore
// Outputs: none
//new
void OS_InitSemaphore(int32_t *semaPt, int32_t value){
// ****IMPLEMENT THIS****
// Same as Lab 3
	DisableInterrupts();
	(*semaPt) = value;
	EnableInterrupts();
}
// ******** OS_Wait ************
// Decrement semaphore and block if less than zero
// Lab2 spinlock (does not suspend while spinning)
// Lab3 block if less than zero
// Inputs:  pointer to a counting semaphore
// Outputs: none
//new
void OS_Wait(int32_t *semaPt){
  DisableInterrupts();  
  (*semaPt)--;
  
  if ((*semaPt) < 0) {
    RunPt->blocked = semaPt;
    EnableInterrupts();
    OS_Suspend();
  }
  EnableInterrupts();
}

// ******** OS_Signal ************
// Increment semaphore
// Lab2 spinlock
// Lab3 wakeup blocked thread if appropriate
// Inputs:  pointer to a counting semaphore
// Outputs: none
//new
void OS_Signal(int32_t *semaPt){
// ****IMPLEMENT THIS****
// Same as Lab 3
 tcbType *pt;
 DisableInterrupts();
 (*semaPt) = (*semaPt) + 1;
 if((*semaPt) <= 0){
 pt = RunPt->next; // search for a thread blocked on this semaphore
 while(pt->blocked != semaPt){
 pt = pt->next;
 }
 pt->blocked = 0; // wakeup this one
 }
 EnableInterrupts();
}

#define FSIZE 14    // can be any size
uint32_t PutI;      // index of where to put next
uint32_t GetI;      // index of where to get next
uint8_t Fifo[FSIZE];
int32_t CurrentSize;// 0 means FIFO empty, FSIZE means full
uint32_t LostData;  // number of lost pieces of data

// ******** OS_FIFO_Init ************
// Initialize FIFO.  The "put" and "get" indices initially
// are equal, which means that the FIFO is empty.  Also
// initialize semaphores to track properties of the FIFO
// such as size and busy status for Put and Get operations,
// which is important if there are multiple data producers
// or multiple data consumers.
// Inputs:  none
// Outputs: none

//new
void OS_FIFO_Init(void){
  PutI = 0;
  GetI = 0;
  OS_InitSemaphore(&CurrentSize, 0);
  LostData = 0;
}

// ******** OS_FIFO_Put ************
// Put an entry in the FIFO.  Consider using a unique
// semaphore to wait on busy status if more than one thread
// is putting data into the FIFO and there is a chance that
// this function may interrupt itself.
// Inputs:  data to be stored
// Outputs: 0 if successful, -1 if the FIFO is full
//new
int OS_FIFO_Put(uint8_t data){
// ****IMPLEMENT THIS****
// Same as Lab 3
 if (CurrentSize == FSIZE){
 LostData++;
 return -1; // Full
 }else {
 Fifo[PutI] = data; // Put 
 PutI = (PutI+1)%FSIZE; 
// OS_Signal(&CurrentSize);
 return 0; // success
 }
}


// ******** OS_FIFO_Get ************
// Get an entry from the FIFO.  Consider using a unique
// semaphore to wait on busy status if more than one thread
// is getting data from the FIFO and there is a chance that
// this function may interrupt itself.
// Inputs:  none
// Outputs: data retrieved
//new
uint8_t OS_FIFO_Get(void){uint8_t data;
// ****IMPLEMENT THIS****
// Same as Lab 3
// OS_Wait(&CurrentSize); // block if empty
 data = Fifo[GetI]; // get
 GetI = (GetI+1)%FSIZE; // plae to get next
 return data;
}
// *****periodic events****************
int32_t *PeriodicSemaphore0;
uint32_t Period0; // time between signals
int32_t *PeriodicSemaphore1;
uint32_t Period1; // time between signals

//new
void RealTimeEvents(void) {
  int flag=0;
  static int32_t realCount = -10;

  realCount++;
  if(realCount >= 0){
		if((realCount%Period0)==0){
      OS_Signal(PeriodicSemaphore0);
      flag = 1;
		}
    if((realCount%Period1)==0){
      OS_Signal(PeriodicSemaphore1);
      flag=1;
    }
    if(flag){
      OS_Suspend();
    }
  }
}

// ******** OS_PeriodTrigger0_Init ************
// Initialize periodic timer interrupt to signal 
// Inputs:  semaphore to signal
//          period in ms
// priority level at 0 (highest
// Outputs: none
//new
void OS_PeriodTrigger0_Init(int32_t *semaPt, uint32_t period){
	PeriodicSemaphore0 = semaPt;
	Period0 = period;
	OS_PeriodicTask_InitC(&RealTimeEvents,1000,0);
}

// ******** OS_PeriodTrigger1_Init ************
// Initialize periodic timer interrupt to signal 
// Inputs:  semaphore to signal
//          period in ms
// priority level at 0 (highest
// Outputs: none
//new
void OS_PeriodTrigger1_Init(int32_t *semaPt, uint32_t period){
	PeriodicSemaphore1 = semaPt;
	Period1 = period;
	OS_PeriodicTask_InitB(&RealTimeEvents,1000,0);
}

//****edge-triggered event************
int32_t *edgeSemaphore;
// ******** OS_EdgeTrigger_Init ************
// Initialize button1, PD6, to signal on a falling edge interrupt
// Inputs:  semaphore to signal
//          priority
// Outputs: none
//new

void OS_EdgeTrigger_Init(int32_t *semaPt, uint8_t priority){
	edgeSemaphore = semaPt;

  SYSCTL_RCGCGPIO_R |= 0x08;                                  
  while((SYSCTL_PRGPIO_R&0x08) == 0){}                     
  //GPIO_PORTD_LOCK_R = 0x4C4F434B;                          
  GPIO_PORTD_AMSEL_R &= ~0x40;                                
  GPIO_PORTD_CR_R = 0x40;                                    
  GPIO_PORTD_AFSEL_R &= ~0x40;                               
  GPIO_PORTD_DIR_R &= ~0x40;                                 
  GPIO_PORTD_DEN_R |= 0x40;                                  
  GPIO_PORTD_PUR_R &= ~0x40;                                 
  GPIO_PORTD_IS_R &= ~0x40;                                  
  GPIO_PORTD_IBE_R &= ~0x40;                                 
  GPIO_PORTD_IEV_R &= ~0x40;                                 
  GPIO_PORTD_ICR_R = 0x40;                                   
  GPIO_PORTD_IM_R |= 0x40;                                   
  NVIC_PRI0_R = (NVIC_PRI0_R&0x1FFFFFFF)|(priority << 29);   
  NVIC_EN0_R = 0x00000008;                                   
 }


// ******** OS_EdgeTrigger_Restart ************
// restart button1 to signal on a falling edge interrupt
// rearm interrupt
// Inputs:  none
// Outputs: none
 //new
void OS_EdgeTrigger_Restart(void){
  GPIO_PORTD_IM_R |= 0x40;
  GPIO_PORTD_ICR_R = 0x40;
}

//new
void GPIOPortD_Handler(void){
//***IMPLEMENT THIS***
	// step 1 acknowledge by clearing flag
  // step 2 signal semaphore (no need to run scheduler)
  // step 3 disarm interrupt to prevent bouncing to create multiple signals
	GPIO_PORTD_ICR_R = 0x40;    // step 1 acknowledge by clearing flag
  OS_Signal(edgeSemaphore);   // step 2 signal semaphore (no need to run scheduler)
  GPIO_PORTD_IM_R &= ~0x40; 	//disarm
	OS_Suspend();
}


