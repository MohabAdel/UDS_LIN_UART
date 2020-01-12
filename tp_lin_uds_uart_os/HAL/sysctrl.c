/**
 *  \file    sysctrl.c
 *
 *  \brief   This file contains the device abstraction layer APIs for System Control.
 *
 *  \date    Aug 8, 2017
 *  \author  Mohab Adel
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sysctrl.h"

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
/**  \brief    the frequency of the system.
 *             16000000 :the default frequency.
 *   \note     when changing the frequency you must update the value of this variable. */
static fp32 SysClk =16000000;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

sSysCtrlError_t clockGating(sSysCtrlModules_t obj) {
	sSysCtrlError_t state = PASSED;
	/** GPIO Moduels */
	if (obj == GPIOA) {
#ifdef GPIO_HIGH_SPEED_BUS
		/* Enable AHB bus*/
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET,
				0, HIGH);
#endif
		/* Enable GPIOA Clock. */
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				0, HIGH);
	} else if (obj == GPIOB) {
#ifdef GPIO_HIGH_SPEED_BUS
		/* Enable AHB bus*/
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET,
				1, HIGH);
#endif
		/* Enable GPIOB Clock. */
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				1, HIGH);
	} else if (obj == GPIOC) {
#ifdef GPIO_HIGH_SPEED_BUS
		/* Enable AHB bus*/
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET,
				2, HIGH);
#endif
		/* Enable GPIOC Clock. */
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				2, HIGH);
	} else if (obj == GPIOD) {
#ifdef GPIO_HIGH_SPEED_BUS
		/* Enable AHB bus*/
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET,
				3, HIGH);
#endif
		/* Enable GPIOD Clock. */
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				3, HIGH);
	} else if (obj == GPIOE) {
#ifdef GPIO_HIGH_SPEED_BUS
		/* Enable AHB bus*/
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET,
				4, HIGH);
#endif
		/* Enable GPIOE Clock. */
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				4, HIGH);
	} else if (obj == GPIOF) {
#ifdef GPIO_HIGH_SPEED_BUS
		/* Enable AHB bus*/
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET,
				5, HIGH);
#endif
		/* Enable GPIOF Clock. */
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				5, HIGH);
		/*Enable UART0 clock. */
	}else if(obj==UART_0){
		HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				0, HIGH);
		/*Enable UART1 clock. */
	}else if(obj==UART_1){
				HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				1, HIGH);
		/*Enable UART2 clock. */
	}else if(obj==UART_2){
				HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				2, HIGH);
		/*Enable UART3 clock. */
	}else if(obj==UART_3){
				HW_WRITE_BIT(
				BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				3, HIGH);
		/*Enable UART4 clock. */
	}else if(obj==UART_4){
				HW_WRITE_BIT(
				        BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
				        4, HIGH);
		/*Enable UART5 clock. */
	}else if(obj==UART_5){
				HW_WRITE_BIT(
		        		BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
	     		     	5, HIGH);
    	/*Enable UART6 clock. */
	}else if(obj==UART_6){
				HW_WRITE_BIT(
						BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
						6, HIGH);
		/*Enable UART7 clock. */
	}else if(obj==UART_7){
				HW_WRITE_BIT(
						BASE_SYSTEM_CONTROL + UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET,
						7, HIGH);


	} else {
		state = MODULE_NOT_EXIST;
	}
	return state;
}

sSysCtrlError_t NVICInterruptEnable(g_ISRVirIdx_t obj, uint8 priority,
		uint8 pending) {
	sSysCtrlError_t state = PASSED;
	if (obj == GPIOA_IRQ) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, GPIOA_INT_NUMBER, HIGH);
		/* assign priority to PRI0 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_0_3_PRIORITY, priority << 5, 0X7UL << 5);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, GPIOA_INT_NUMBER, pending);
	} else if (obj == GPIOB_IRQ) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, GPIOB_INT_NUMBER, HIGH);
		/* assign priority to PRI0 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_0_3_PRIORITY, priority << 13,
				0X7UL << 13);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, GPIOB_INT_NUMBER, pending);
	} else if (obj == GPIOC_IRQ) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, GPIOC_INT_NUMBER, HIGH);
		/* assign priority to PRI0 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_0_3_PRIORITY, priority << 21,
				0X7UL << 21);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, GPIOC_INT_NUMBER, pending);
	} else if (obj == GPIOD_IRQ) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, GPIOD_INT_NUMBER, HIGH);
		/* assign priority to PRI0 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_0_3_PRIORITY, priority << 29,
				0X7UL << 29);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, GPIOD_INT_NUMBER, pending);
	} else if (obj == GPIOE_IRQ) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, GPIOE_INT_NUMBER, HIGH);
		/* assign priority to PRI1 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_4_7_PRIORITY, priority << 5, 0X7UL << 5);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, GPIOE_INT_NUMBER, pending);
	} else if (obj == GPIOF_IRQ) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, GPIOF_INT_NUMBER, HIGH);
		/* assign priority to PRI7 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_28_31_PRIORITY, priority << 21,
				0X7UL << 21);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, GPIOF_INT_NUMBER, pending);
	} else if (obj == UART0) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, UART0_INT_NUMBER, HIGH);
		/* assign priority to PRI1 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_4_7_PRIORITY, priority << 13,
				0X7UL << 13);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, UART0_INT_NUMBER, pending);
	} else if (obj == UART1) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_ENABLE, UART1_INT_NUMBER, HIGH);
		/* assign priority to PRI1 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_4_7_PRIORITY, priority << 21,
				0X7UL << 21);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_0_31_SET_PENDING, UART1_INT_NUMBER, pending);
	} else if (obj == UART2) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_ENABLE, UART2_INT_NUMBER-32, HIGH);
		/* assign priority to PRI8 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_32_35_PRIORITY, priority << 13,
				0X7UL << 13);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_PENDING, UART2_INT_NUMBER-32, pending);
	} else if (obj == UART3) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_ENABLE, UART3_INT_NUMBER-32, HIGH);
		/* assign priority to PRI14 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_56_59_PRIORITY, priority << 29,
				0X7UL << 29);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_PENDING, UART3_INT_NUMBER-32, pending);
	} else if (obj == UART4) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_ENABLE, UART4_INT_NUMBER-32, HIGH);
		/* assign priority to PRI15 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_60_63_PRIORITY, priority << 5,
				0X7UL << 5);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_PENDING, UART4_INT_NUMBER-32, pending);
	} else if (obj == UART5) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_ENABLE, UART5_INT_NUMBER-32, HIGH);
		/* assign priority to PRI5 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_60_63_PRIORITY, priority << 13,
				0X7UL << 13);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_PENDING, UART5_INT_NUMBER-32, pending);
	} else if (obj == UART6) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_ENABLE, UART6_INT_NUMBER-32, HIGH);
		/* assign priority to PRI15 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_60_63_PRIORITY, priority << 21,
				0X7UL << 21);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_PENDING, UART6_INT_NUMBER-32, pending);
	} else if (obj == UART7) {
		/* enable interrupt*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_ENABLE, UART7_INT_NUMBER-32, HIGH);
		/* assign priority to PRI15 register*/
		HW_WRITE_REG32_MASKED(INTERRUPT_60_63_PRIORITY, priority << 29,
				0X7UL << 29);
		/* set interrupt pending*/
		HW_WRITE_BIT(INTERRUPT_32_63_SET_PENDING, UART7_INT_NUMBER-32, pending);
	} else {
		state = IRQ_NOT_EXIST;
	}
	return state;
}


fp32 GetSysFrequency(void){
return SysClk;
}
