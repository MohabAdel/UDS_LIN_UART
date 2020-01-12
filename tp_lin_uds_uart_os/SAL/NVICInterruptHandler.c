/*
 * NVICInterruptHandler.c
 *
 *  Created on: Aug 13, 2017
 *      Author: Mohab Adel
 */
#include "NVICInterruptHandler.h"
void (*g_pfnVirualOLDVectors[])(void) =
{
        IntVirDefaultFun, // GPIO Port A
        IntVirDefaultFun,// GPIO Port B
        IntVirDefaultFun,// GPIO Port C
        IntVirDefaultFun,// GPIO Port D
        IntVirDefaultFun,// GPIO Port E
        IntVirDefaultFun,// UART0 Rx and Tx
        IntVirDefaultFun,// UART1 Rx and Tx
        IntVirDefaultFun,// SSI0 Rx and Tx
        IntVirDefaultFun,// I2C0 Master and Slave
        IntVirDefaultFun,// PWM Fault
        IntVirDefaultFun,// PWM Generator 0
        IntVirDefaultFun,// PWM Generator 1
        IntVirDefaultFun,// PWM Generator 2
        IntVirDefaultFun,// Quadrature Encoder 0
        IntVirDefaultFun,// ADC Sequence 0
        IntVirDefaultFun,// ADC Sequence 1
        IntVirDefaultFun,// ADC Sequence 2
        IntVirDefaultFun,// ADC Sequence 3
        IntVirDefaultFun,// Watchdog timer
        IntVirDefaultFun,// Timer 0 subtimer A
        IntVirDefaultFun,// Timer 0 subtimer B
        IntVirDefaultFun,// Timer 1 subtimer A
        IntVirDefaultFun,// Timer 1 subtimer B
        IntVirDefaultFun,// Timer 2 subtimer A
        IntVirDefaultFun,// Timer 2 subtimer B
        IntVirDefaultFun,// Analog Comparator 0
        IntVirDefaultFun,// Analog Comparator 1
        IntVirDefaultFun,// Analog Comparator 2
        IntVirDefaultFun,// System Control (PLL, OSC, BO)
        IntVirDefaultFun,// FLASH Control
        IntVirDefaultFun,// GPIO Port F
        IntVirDefaultFun,// GPIO Port G
        IntVirDefaultFun,// GPIO Port H
        IntVirDefaultFun,// UART2 Rx and Tx
        IntVirDefaultFun,// SSI1 Rx and Tx
        IntVirDefaultFun,// Timer 3 subtimer A
        IntVirDefaultFun,// Timer 3 subtimer B
        IntVirDefaultFun,// I2C1 Master and Slave
        IntVirDefaultFun,// Quadrature Encoder 1
        IntVirDefaultFun,// CAN0
        IntVirDefaultFun,// CAN1
        IntVirDefaultFun,// Hibernate
        IntVirDefaultFun,// USB0
        IntVirDefaultFun,// PWM Generator 3
        IntVirDefaultFun,// uDMA Software Transfer
        IntVirDefaultFun,// uDMA Error
        IntVirDefaultFun,// ADC1 Sequence 0
        IntVirDefaultFun,// ADC1 Sequence 1
        IntVirDefaultFun,// ADC1 Sequence 2
        IntVirDefaultFun,// ADC1 Sequence 3
        IntVirDefaultFun,// GPIO Port J
        IntVirDefaultFun,// GPIO Port K
        IntVirDefaultFun,// GPIO Port L
        IntVirDefaultFun,// SSI2 Rx and Tx
        IntVirDefaultFun,// SSI3 Rx and Tx
        IntVirDefaultFun,// UART3 Rx and Tx
        IntVirDefaultFun,// UART4 Rx and Tx
        IntVirDefaultFun,// UART5 Rx and Tx
        IntVirDefaultFun,// UART6 Rx and Tx
        IntVirDefaultFun,// UART7 Rx and Tx
        IntVirDefaultFun,// I2C2 Master and Slave
        IntVirDefaultFun,// I2C3 Master and Slave
        IntVirDefaultFun,// Timer 4 subtimer A
        IntVirDefaultFun,// Timer 4 subtimer B
        IntVirDefaultFun,// Timer 5 subtimer A
        IntVirDefaultFun,// Timer 5 subtimer B
        IntVirDefaultFun,// Wide Timer 0 subtimer A
        IntVirDefaultFun,// Wide Timer 0 subtimer B
        IntVirDefaultFun,// Wide Timer 1 subtimer A
        IntVirDefaultFun,// Wide Timer 1 subtimer B
        IntVirDefaultFun,// Wide Timer 2 subtimer A
        IntVirDefaultFun,// Wide Timer 2 subtimer B
        IntVirDefaultFun,// Wide Timer 3 subtimer A
        IntVirDefaultFun,// Wide Timer 3 subtimer B
        IntVirDefaultFun,// Wide Timer 4 subtimer A
        IntVirDefaultFun,// Wide Timer 4 subtimer B
        IntVirDefaultFun,// Wide Timer 5 subtimer A
        IntVirDefaultFun,// Wide Timer 5 subtimer B
        IntVirDefaultFun,// FPU
        IntVirDefaultFun,// I2C4 Master and Slave
        IntVirDefaultFun,// I2C5 Master and Slave
        IntVirDefaultFun,// GPIO Port M
        IntVirDefaultFun,// GPIO Port N
        IntVirDefaultFun,// Quadrature Encoder 2
        IntVirDefaultFun,// GPIO Port P (Summary or P0)
        IntVirDefaultFun,// GPIO Port P1
        IntVirDefaultFun,// GPIO Port P2
        IntVirDefaultFun,// GPIO Port P3
        IntVirDefaultFun,// GPIO Port P4
        IntVirDefaultFun,// GPIO Port P5
        IntVirDefaultFun,// GPIO Port P6
        IntVirDefaultFun,// GPIO Port P7
        IntVirDefaultFun,// GPIO Port Q (Summary or Q0)
        IntVirDefaultFun,// GPIO Port Q1
        IntVirDefaultFun,// GPIO Port Q2
        IntVirDefaultFun,// GPIO Port Q3
        IntVirDefaultFun,// GPIO Port Q4
        IntVirDefaultFun,// GPIO Port Q5
        IntVirDefaultFun,// GPIO Port Q6
        IntVirDefaultFun,// GPIO Port Q7
        IntVirDefaultFun,// GPIO Port R
        IntVirDefaultFun,// GPIO Port S
        IntVirDefaultFun,// PWM 1 Generator 0
        IntVirDefaultFun,// PWM 1 Generator 1
        IntVirDefaultFun,// PWM 1 Generator 2
        IntVirDefaultFun,// PWM 1 Generator 3
        IntVirDefaultFun// PWM 1 Fault
};



/*Default Virtual interrupt vector table*/
void (*g_pfnVirualVectors[])(void) =
{
        IntVirDefaultFun, // GPIO Port A
        IntVirDefaultFun,// GPIO Port B
        IntVirDefaultFun,// GPIO Port C
        IntVirDefaultFun,// GPIO Port D
        IntVirDefaultFun,// GPIO Port E
        IntVirDefaultFun,// UART0 Rx and Tx
        IntVirDefaultFun,// UART1 Rx and Tx
        IntVirDefaultFun,// SSI0 Rx and Tx
        IntVirDefaultFun,// I2C0 Master and Slave
        IntVirDefaultFun,// PWM Fault
        IntVirDefaultFun,// PWM Generator 0
        IntVirDefaultFun,// PWM Generator 1
        IntVirDefaultFun,// PWM Generator 2
        IntVirDefaultFun,// Quadrature Encoder 0
        IntVirDefaultFun,// ADC Sequence 0
        IntVirDefaultFun,// ADC Sequence 1
        IntVirDefaultFun,// ADC Sequence 2
        IntVirDefaultFun,// ADC Sequence 3
        IntVirDefaultFun,// Watchdog timer
        IntVirDefaultFun,// Timer 0 subtimer A
        IntVirDefaultFun,// Timer 0 subtimer B
        IntVirDefaultFun,// Timer 1 subtimer A
        IntVirDefaultFun,// Timer 1 subtimer B
        IntVirDefaultFun,// Timer 2 subtimer A
        IntVirDefaultFun,// Timer 2 subtimer B
        IntVirDefaultFun,// Analog Comparator 0
        IntVirDefaultFun,// Analog Comparator 1
        IntVirDefaultFun,// Analog Comparator 2
        IntVirDefaultFun,// System Control (PLL, OSC, BO)
        IntVirDefaultFun,// FLASH Control
        IntVirDefaultFun,// GPIO Port F
        IntVirDefaultFun,// GPIO Port G
        IntVirDefaultFun,// GPIO Port H
        IntVirDefaultFun,// UART2 Rx and Tx
        IntVirDefaultFun,// SSI1 Rx and Tx
        IntVirDefaultFun,// Timer 3 subtimer A
        IntVirDefaultFun,// Timer 3 subtimer B
        IntVirDefaultFun,// I2C1 Master and Slave
        IntVirDefaultFun,// Quadrature Encoder 1
        IntVirDefaultFun,// CAN0
        IntVirDefaultFun,// CAN1
        IntVirDefaultFun,// Hibernate
        IntVirDefaultFun,// USB0
        IntVirDefaultFun,// PWM Generator 3
        IntVirDefaultFun,// uDMA Software Transfer
        IntVirDefaultFun,// uDMA Error
        IntVirDefaultFun,// ADC1 Sequence 0
        IntVirDefaultFun,// ADC1 Sequence 1
        IntVirDefaultFun,// ADC1 Sequence 2
        IntVirDefaultFun,// ADC1 Sequence 3
        IntVirDefaultFun,// GPIO Port J
        IntVirDefaultFun,// GPIO Port K
        IntVirDefaultFun,// GPIO Port L
        IntVirDefaultFun,// SSI2 Rx and Tx
        IntVirDefaultFun,// SSI3 Rx and Tx
        IntVirDefaultFun,// UART3 Rx and Tx
        IntVirDefaultFun,// UART4 Rx and Tx
        IntVirDefaultFun,// UART5 Rx and Tx
        IntVirDefaultFun,// UART6 Rx and Tx
        IntVirDefaultFun,// UART7 Rx and Tx
        IntVirDefaultFun,// I2C2 Master and Slave
        IntVirDefaultFun,// I2C3 Master and Slave
        IntVirDefaultFun,// Timer 4 subtimer A
        IntVirDefaultFun,// Timer 4 subtimer B
        IntVirDefaultFun,// Timer 5 subtimer A
        IntVirDefaultFun,// Timer 5 subtimer B
        IntVirDefaultFun,// Wide Timer 0 subtimer A
        IntVirDefaultFun,// Wide Timer 0 subtimer B
        IntVirDefaultFun,// Wide Timer 1 subtimer A
        IntVirDefaultFun,// Wide Timer 1 subtimer B
        IntVirDefaultFun,// Wide Timer 2 subtimer A
        IntVirDefaultFun,// Wide Timer 2 subtimer B
        IntVirDefaultFun,// Wide Timer 3 subtimer A
        IntVirDefaultFun,// Wide Timer 3 subtimer B
        IntVirDefaultFun,// Wide Timer 4 subtimer A
        IntVirDefaultFun,// Wide Timer 4 subtimer B
        IntVirDefaultFun,// Wide Timer 5 subtimer A
        IntVirDefaultFun,// Wide Timer 5 subtimer B
        IntVirDefaultFun,// FPU
        IntVirDefaultFun,// I2C4 Master and Slave
        IntVirDefaultFun,// I2C5 Master and Slave
        IntVirDefaultFun,// GPIO Port M
        IntVirDefaultFun,// GPIO Port N
        IntVirDefaultFun,// Quadrature Encoder 2
        IntVirDefaultFun,// GPIO Port P (Summary or P0)
        IntVirDefaultFun,// GPIO Port P1
        IntVirDefaultFun,// GPIO Port P2
        IntVirDefaultFun,// GPIO Port P3
        IntVirDefaultFun,// GPIO Port P4
        IntVirDefaultFun,// GPIO Port P5
        IntVirDefaultFun,// GPIO Port P6
        IntVirDefaultFun,// GPIO Port P7
        IntVirDefaultFun,// GPIO Port Q (Summary or Q0)
        IntVirDefaultFun,// GPIO Port Q1
        IntVirDefaultFun,// GPIO Port Q2
        IntVirDefaultFun,// GPIO Port Q3
        IntVirDefaultFun,// GPIO Port Q4
        IntVirDefaultFun,// GPIO Port Q5
        IntVirDefaultFun,// GPIO Port Q6
        IntVirDefaultFun,// GPIO Port Q7
        IntVirDefaultFun,// GPIO Port R
        IntVirDefaultFun,// GPIO Port S
        IntVirDefaultFun,// PWM 1 Generator 0
        IntVirDefaultFun,// PWM 1 Generator 1
        IntVirDefaultFun,// PWM 1 Generator 2
        IntVirDefaultFun,// PWM 1 Generator 3
        IntVirDefaultFun// PWM 1 Fault
};


void installNIVCISRFunction(g_ISRVirIdx_t idx, void (*isr)(void))
{   g_pfnVirualOLDVectors[idx] =  g_pfnVirualVectors[idx];
    g_pfnVirualVectors[idx] = isr;
}

void deInstallNIVCISRFunction(g_ISRVirIdx_t idx)
{
    g_pfnVirualVectors[idx] = g_pfnVirualOLDVectors[idx];
}

void IntVirDefaultFun(void)
{
    /*Default Interrupt do nothing */
}

void GPIOA_Handler(void)
{
    g_pfnVirualVectors[GPIOA_IRQ]();
}

void GPIOB_Handler(void)
{
    g_pfnVirualVectors[GPIOB_IRQ]();
}

void GPIOC_Handler(void)
{
    g_pfnVirualVectors[GPIOC_IRQ]();
}

void GPIOD_Handler(void)
{
    g_pfnVirualVectors[GPIOD_IRQ]();
}

void GPIOE_Handler(void)
{
    g_pfnVirualVectors[GPIOE_IRQ]();
}
void GPIOF_Handler(void){
    g_pfnVirualVectors[GPIOF_IRQ]();
}

void UART0_Handler(void){
	g_pfnVirualVectors[UART0]();
}
