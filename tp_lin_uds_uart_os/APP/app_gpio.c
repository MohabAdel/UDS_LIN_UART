/**
 *  \file   app_gpio.c
 *
 *  \param  Source file containing the GPIO IP related configuration functions.
 *         These functions will be called by example application.
 *
 *  \date   Aug 8, 2017
 *  \author Mohab Adel
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "../APP/app_gpio.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

gGPIOError_t initPin(gGPIOObj_t *obj){
	gGPIOError_t state = PASS;
	/**< Enable GPIO Clock*/
	if(obj->base == BASE_A){
		clockGating(GPIOA);
	}else if(obj->base == BASE_B){
		clockGating(GPIOB);
	}else if(obj->base == BASE_C){
		clockGating(GPIOC);
	}else if(obj->base == BASE_D){
		clockGating(GPIOD);
	}else if(obj->base == BASE_E){
		clockGating(GPIOE);
	}else if(obj->base == BASE_F){
		clockGating(GPIOF);
	}
	 portUnLock(obj->base,TRUE);
	pinCommit(obj->base,obj->pin_num,TRUE);
	state = setPinDir(obj->base,obj->pin_num,obj->dir);
	if(state == PASS){
	pinAlternateFunctionSel(obj->base,obj->pin_num,FALSE);
	pinAnalogModeSelect(obj->base,obj->pin_num,FALSE);
    pinAdcTrigger(obj->base,obj->pin_num,FALSE);
    pinSetPadConfig(obj->base,obj->pin_num,&(obj->configPadObj));
    pinDigitalEnable(obj->base,obj->pin_num,TRUE);
    pinAnalogModeSelect(obj->base,obj->pin_num,FALSE);
    GPIOPinControl(obj->base,obj->pin_num,0);
	}
	return state;
}

gGPIOError_t initPort(gGPIOObj_t *obj,uint8 val){
	gGPIOError_t state = PASS;
	/**< Enable GPIO Clock*/
	if(obj->base == BASE_A){
		clockGating(GPIOA);
	}else if(obj->base == BASE_B){
		clockGating(GPIOB);
	}else if(obj->base == BASE_C){
		clockGating(GPIOC);
	}else if(obj->base == BASE_D){
		clockGating(GPIOD);
	}else if(obj->base == BASE_E){
		clockGating(GPIOE);
	}else if(obj->base == BASE_F){
		clockGating(GPIOF);
	}
    portUnLock(obj->base,TRUE);
    portCommit(obj->base,0XFF);
	state = setPortDir(obj->base,val);
	if(state == PASS){
	portAlternateFunctionSel(obj->base,FALSE);
	portAnalogModeSelect(obj->base,FALSE);
    portAdcTrigger(obj->base,FALSE);
    portSetPadConfig(obj->base,&(obj->configPadObj));
    portDigitalEnable(obj->base,0XFF);
    portAnalogModeSelect(obj->base,FALSE);
    GPIOPortControlClear(obj->base);
	}
	return state;
}

gGPIOError_t digitalPinWrite(gGPIOObj_t *obj , uint8 val){
	gGPIOError_t state = PASS;
	state = writePin(obj->base,obj->pin_num,val);
	return state;
}

gGPIOError_t digitalPortWrite(gGPIOObj_t *obj , uint8 val){
	gGPIOError_t state = PASS;
	state = writePort(obj->base,val);
	return state;
}

gGPIOError_t digitalPinRead(gGPIOObj_t *obj , uint8 *data){
	gGPIOError_t state = PASS;
	state = readPin(obj->base,obj->pin_num,data);
	return state;
}

gGPIOError_t digitalPortRead(gGPIOObj_t *obj , uint8 *data){
	gGPIOError_t state = PASS;
	state = readPort(obj->base,data);
	return state;
}

gGPIOError_t digitalReadHWMaskedPins(gGPIOObj_t *obj , uint8 mask , uint8 *data){
	gGPIOError_t state = PASS;
	state = readHWMaskedPins(obj->base,mask,data);
	return state;
}

gGPIOError_t digitalWriteHWMaskedPins(gGPIOObj_t *obj , uint8 mask , uint8 val){
	gGPIOError_t state = PASS;
	state = writeHWMaskedPins(obj->base,val,mask);
	return state;
}
