/*
 * NVICInterruptHandler.h
 *
 *  Created on: Aug 13, 2017
 *      Author: Mohab Adel
 */

#include "../HAL/sysctrl.h"
#ifndef DRIVERS_SL_NVICINTERRUPTHANDLER_H_
#define DRIVERS_SL_NVICINTERRUPTHANDLER_H_


void installNIVCISRFunction(g_ISRVirIdx_t idx, void (*isr)(void));
void deInstallNIVCISRFunction(g_ISRVirIdx_t idx);
void IntVirDefaultFun(void);

#endif /* DRIVERS_SL_NVICINTERRUPTHANDLER_H_ */
