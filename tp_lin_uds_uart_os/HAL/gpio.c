/**
 *   \file   gpio.c
 *
 *   \brief  This file contains the device abstraction layer APIs for GPIO
 *            peripheral.
 *
 *   \date   Aug 6, 2017
 *   \author Mohab Adel
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "gpio.h"


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

gGPIOError_t setPinDir(uint32 base , uint8 pin , uint8 dir){
	gGPIOError_t state = PASS;
    if(base == BASE_A || base == BASE_B|| base == BASE_C||
       base == BASE_D || base == BASE_E|| base == BASE_F){
    	if(pin > MAX_PORT_PINS){
    		state = INCORRECT_PIN_NUM;
    	}else{
    		if(dir == INPUT){
              HW_WRITE_BIT(base+GPIO_DIRECTION_OFFSET,pin,dir);
    		}else if(dir == OUTPUT){
    	      HW_WRITE_BIT(base+GPIO_DIRECTION_OFFSET,pin,dir);
    		}else{
    			state =DIRECTION_ERROR;
    		}
    	}
    }else {
    	state = INCORRECT_PORT;
    }
    return state;
}

gGPIOError_t writePin(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
    if(base == BASE_A || base == BASE_B|| base == BASE_C||
       base == BASE_D || base == BASE_E|| base == BASE_F){
    	if(pin > MAX_PORT_PINS){
    		state = INCORRECT_PIN_NUM;
    	}else{
    		if(val == HIGH){
              HW_WRITE_BIT(base+GPIO_DATA_OFFSET+GPIO_DATA_HW_MASK,pin,val);
    		}else if(val == LOW){
    	      HW_WRITE_BIT(base+GPIO_DATA_OFFSET+GPIO_DATA_HW_MASK,pin,val);
    		}else{
    			state =INCORRECT_VALUE;
    		}
    	}
    }else {
    	state = INCORRECT_PORT;
    }
    return state;
}

gGPIOError_t readPin(uint32 base , uint8 pin , uint8 *data){
	gGPIOError_t state = PASS;
    if(base == BASE_A || base == BASE_B|| base == BASE_C||
       base == BASE_D || base == BASE_E|| base == BASE_F){
    	if(pin > MAX_PORT_PINS){
    		state = INCORRECT_PIN_NUM;
    	}else{
    		*data = HW_READ_BIT(base+GPIO_DATA_OFFSET+GPIO_DATA_HW_MASK,pin);
    	}
    }else {
    	state = INCORRECT_PORT;
    }
    return state;
}

gGPIOError_t setPortDir(uint32 base , uint8 dirVal){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	HW_WRITE_REG_32BIT(base+GPIO_DIRECTION_OFFSET,dirVal);
	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}


gGPIOError_t writePort(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	HW_WRITE_REG_32BIT(base+GPIO_DATA_OFFSET+GPIO_DATA_HW_MASK,val);
	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}


gGPIOError_t readPort(uint32 base , uint8 *data){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	*data = HW_READ_REG_32BIT(base+GPIO_DATA_OFFSET+GPIO_DATA_HW_MASK);
	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}


gGPIOError_t writeHWMaskedPins(uint32 base , uint8 val, uint8 mask){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	if(mask > GPIO_DATA_HW_MASK){
	    		state = INCORRECT_MASK;
	    	}else{
	    	HW_WRITE_REG_32BIT(base+GPIO_DATA_OFFSET+(mask>>2),val);
	    	}
	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}


gGPIOError_t readHWMaskedPins(uint32 base , uint16 mask , uint8 *data){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	if(mask > GPIO_DATA_HW_MASK){
	    		state = INCORRECT_MASK;
	    	}else{
	    	*data = HW_READ_REG_32BIT(base+GPIO_DATA_OFFSET+(mask>>2));
	    	}
	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}


gGPIOError_t pinAlternateFunctionSel(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	if(pin > MAX_PORT_PINS){
	    		state = INCORRECT_PIN_NUM;
	    	}else{
	    		if(val == TRUE || val == FALSE){
	    		HW_WRITE_BIT(base+GPIO_ALTERNATE_FUNC_SEL_OFFSET,pin,val);
	    		}else{
	    			state = INCORRECT_VALUE;
	    		}
	    	}

	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}

gGPIOError_t portAlternateFunctionSel(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){

	    		HW_WRITE_REG_32BIT(base+GPIO_ALTERNATE_FUNC_SEL_OFFSET,val);
	    }else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}

gGPIOError_t pinSetPadConfig(uint32 base , uint8 pin , gConfigPad_t *obj){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){
	    	if(pin > MAX_PORT_PINS){
	    		state = INCORRECT_PIN_NUM;
	    	}else{
	    		if(obj->currentVal == CURRENT_2MA){
	    			HW_WRITE_BIT(base+GPIO_2_MA_DRIVE_SEL_OFFSET,pin,HIGH);
	    		}else if(obj->currentVal == CURRENT_4MA){
	    			HW_WRITE_BIT(base+GPIO_4_MA_DRIVE_SEL_OFFSET,pin,HIGH);
	    		}else if(obj->currentVal == CURRENT_8MA){
	    			HW_WRITE_BIT(base+GPIO_8_MA_DRIVE_SEL_OFFSET,pin,HIGH);
	    		}
	    		if(obj->resType == PULL_DOWN_RES){
	    			HW_WRITE_BIT(base+GPIO_PULL_DOWN_SEL_OFFSET,pin,HIGH);
	    		}else if(obj->resType == PULL_UP_RES){
	    			HW_WRITE_BIT(base+GPIO_PULL_UP_SEL_OFFSET,pin,HIGH);
	    		}else if(obj->resType == OPEN_DRAIN){
	    			HW_WRITE_BIT(base+GPIO_OPEN_DRAIN_SEL_OFFSET,pin,HIGH);
	    		}
                 HW_WRITE_BIT(base+GPIO_COMMIT_OFFSET,pin,obj->lockFlag);
	    	}
	    } else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}

gGPIOError_t portSetPadConfig(uint32 base , gConfigPad_t *obj){
	gGPIOError_t state = PASS;
	    if(base == BASE_A || base == BASE_B|| base == BASE_C||
	       base == BASE_D || base == BASE_E|| base == BASE_F){

	    		if(obj->currentVal == CURRENT_2MA){
	    			HW_WRITE_REG_32BIT(base+GPIO_2_MA_DRIVE_SEL_OFFSET,0xFF);
	    		}else if(obj->currentVal == CURRENT_4MA){
	    			HW_WRITE_REG_32BIT(base+GPIO_4_MA_DRIVE_SEL_OFFSET,0xFF);
	    		}else if(obj->currentVal == CURRENT_8MA){
	    			HW_WRITE_REG_32BIT(base+GPIO_8_MA_DRIVE_SEL_OFFSET,0xFF);
	    		}else{
	    			state = INCORRECT_VALUE;
	    		}
	    		if(obj->resType == PULL_DOWN_RES){
	    			HW_WRITE_REG_32BIT(base+GPIO_PULL_DOWN_SEL_OFFSET,0xFF);
	    		}else if(obj->resType == PULL_UP_RES){
	    			HW_WRITE_REG_32BIT(base+GPIO_PULL_UP_SEL_OFFSET,0xFF);
	    		}else if(obj->resType == OPEN_DRAIN){
	    			HW_WRITE_REG_32BIT(base+GPIO_OPEN_DRAIN_SEL_OFFSET,0xFF);
	    		}else{
	    			state = INCORRECT_VALUE;
	    		}
	    		if(obj->lockFlag == TRUE){
	    		HW_WRITE_REG_32BIT(base+GPIO_COMMIT_OFFSET,0xFF);
	    		HW_WRITE_REG_32BIT(base+GPIO_LOCK_OFFSET,GPIO_UNLOCK_PORT);
	    		}else if(obj->lockFlag == FALSE){
	    	    HW_WRITE_REG_32BIT(base+GPIO_COMMIT_OFFSET,0x00);
	    	    HW_WRITE_REG_32BIT(base+GPIO_LOCK_OFFSET,GPIO_LOCK_PORT);
	    		}else{
	    			state = INCORRECT_VALUE;
	    		}

	    } else {
	    	state = INCORRECT_PORT;
	    }
	    return state;
	}

gGPIOError_t portUnLock(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
		    if(base == BASE_A || base == BASE_B|| base == BASE_C||
		       base == BASE_D || base == BASE_E|| base == BASE_F){
		    		if(val == TRUE){
		    		HW_WRITE_REG_32BIT(base+GPIO_LOCK_OFFSET,GPIO_UNLOCK_PORT);
		    		}else if(val == FALSE){
		    		HW_WRITE_REG_32BIT(base+GPIO_LOCK_OFFSET,GPIO_LOCK_PORT);
		    		}else{
		    			state = INCORRECT_VALUE;
		    }
		    }else {
		    	state = INCORRECT_PORT;
		    }
		    return state;
}

gGPIOError_t portCommit(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    		HW_WRITE_REG_32BIT(base+GPIO_COMMIT_OFFSET,val);
			    }else {
			    	state = INCORRECT_PORT;
			    }
			    return state;
}

gGPIOError_t pinCommit(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    	if(pin > MAX_PORT_PINS){
			    		state = INCORRECT_PIN_NUM;
			    	}else{
			    		if(val == TRUE || val == FALSE){
			    		HW_WRITE_BIT(base+GPIO_COMMIT_OFFSET,pin,val);
			    		}else{
			    			state = INCORRECT_VALUE;
			    	}
			    	}
			    }else {
			    	state = INCORRECT_PORT;
			    }
			    return state;
}

gGPIOError_t portDigitalEnable(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    		HW_WRITE_REG_32BIT(base+GPIO_DIGITAL_EN_OFFSET,val);
			    }else {
			    	state = INCORRECT_PORT;
			    }
			    return state;
}

gGPIOError_t pinDigitalEnable(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    	if(pin > MAX_PORT_PINS){
			    		state = INCORRECT_PIN_NUM;
			    	}else{
			    		if(val == TRUE || val == FALSE){
			    		HW_WRITE_BIT(base+GPIO_DIGITAL_EN_OFFSET,pin,val);
			    		}else{
			    			state = INCORRECT_VALUE;
			    }
			    	}
			    }else {
			    	state = INCORRECT_PORT;
			    }
			    return state;
}

gGPIOError_t pinAnalogModeSelect(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){
			    	if(pin > MAX_ANALOG_PINS){
			    		state = INCORRECT_PIN_NUM;
			    	}else{
			    		if(val == TRUE || val == FALSE){
			    		HW_WRITE_BIT(base+GPIO_ANALOG_MODE_SEL_OFFSET,pin,val);
			    		}else{
			    			state = INCORRECT_VALUE;
			    }
			    	}
			    }else {
			    	state = INCORRECT_PORT;
			    }
			    return state;
}

gGPIOError_t portAnalogModeSelect(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
			    if(base == BASE_A || base == BASE_B|| base == BASE_C||
			       base == BASE_D || base == BASE_E|| base == BASE_F){

			    		if(val > MAX_ANALOG_REG_VAL){
			    		HW_WRITE_REG_32BIT(base+GPIO_ANALOG_MODE_SEL_OFFSET,val);
			    		}else{
			    			state = INCORRECT_VALUE;
			    }

			    }else {
			    	state = INCORRECT_PORT;
			    }
			    return state;
}

gGPIOError_t portAdcTrigger(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
				    if(base == BASE_A || base == BASE_B|| base == BASE_C||
				       base == BASE_D || base == BASE_E|| base == BASE_F){
				    	HW_WRITE_REG_32BIT(base+GPIO_ADC_CONTROL_OFFSET,val);
				    }else {
				    	state = INCORRECT_PORT;
				    }
				    return state;
	}

gGPIOError_t pinAdcTrigger(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
				    if(base == BASE_A || base == BASE_B|| base == BASE_C||
				       base == BASE_D || base == BASE_E|| base == BASE_F){
				    	if(pin>MAX_PORT_PINS){
				    		state = INCORRECT_PIN_NUM;
				    	}else{
				    		if(val == TRUE || val == FALSE){
				    			HW_WRITE_BIT(base+GPIO_ADC_CONTROL_OFFSET,pin,val);
				    		}else{
				    			state = INCORRECT_VALUE;
				    		}
				    	}

				    }else {
				    	state = INCORRECT_PORT;
				    }
				    return state;
	}

gGPIOError_t GPIOPortDMATrigger(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
				    if(base == BASE_A || base == BASE_B|| base == BASE_C||
				       base == BASE_D || base == BASE_E|| base == BASE_F){
				    		HW_WRITE_REG_32BIT(base+GPIO_DMA_CONTROL_OFFSET,val);

				    }else {
				    	state = INCORRECT_PORT;
				    }
				    return state;
	}

gGPIOError_t GPIOPinDMATrigger(uint32 base , uint8 pin ,uint8 val){
	gGPIOError_t state = PASS;
				    if(base == BASE_A || base == BASE_B|| base == BASE_C||
				       base == BASE_D || base == BASE_E|| base == BASE_F){
				    	if(pin>MAX_PORT_PINS){
				    		state = INCORRECT_PIN_NUM;
				    	}else{
				    		if(val == TRUE || val == FALSE){
				    		HW_WRITE_BIT(base+GPIO_DMA_CONTROL_OFFSET,pin,val);
				    		}else{
				    		state = INCORRECT_VALUE;
				    		}
				    	}

				    }else {
				    	state = INCORRECT_PORT;
				    }
				    return state;
	}

gGPIOError_t GPIOPinControl(uint32 base , uint8 pin ,uint32 val){
	gGPIOError_t state = PASS;
	uint8 mask = GPIO_PORTCONTROL_MASK << (pin * PORT_CONTROL_STEP) ;
	val = val << (pin * PORT_CONTROL_STEP) ;
				    if(base == BASE_A || base == BASE_B|| base == BASE_C||
				       base == BASE_D || base == BASE_E|| base == BASE_F){
				    	if(pin>MAX_PORT_PINS){
				    		state = INCORRECT_PIN_NUM;
				    	}else{
				    		HW_WRITE_REG32_MASKED(base+GPIO_PORT_CONTROL_OFFSET,val,mask);
				    	}
				    }else {
				    	state = INCORRECT_PORT;
				    }
				    return state;
	}

gGPIOError_t GPIOPortControlClear(uint32 base ){
	gGPIOError_t state = PASS;
				    if(base == BASE_A || base == BASE_B|| base == BASE_C||
				       base == BASE_D || base == BASE_E|| base == BASE_F){

				    		HW_WRITE_REG_32BIT(base+GPIO_PORT_CONTROL_OFFSET,0);

				    }else {
				    	state = INCORRECT_PORT;
				    }
				    return state;
	}

gGPIOError_t pinSlewRateControl(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
					    if(base == BASE_A || base == BASE_B|| base == BASE_C||
					       base == BASE_D || base == BASE_E|| base == BASE_F){
					    	if(pin>MAX_PORT_PINS){
					    		state = INCORRECT_PIN_NUM;
					    	}else{
					    		if(val == TRUE || val == FALSE){
					    		HW_WRITE_BIT(base+GPIO_SLEW_RATE_CONTROL_SEL_OFFSET,pin,val);
					    		}else{
					    			state = INCORRECT_VALUE;
					    		}
					    	}
					    }else {
					    	state = INCORRECT_PORT;
					    }
					    return state;
}

gGPIOError_t portSlewRateControl(uint32 base , uint8 val){
	gGPIOError_t state = PASS;
					    if(base == BASE_A || base == BASE_B|| base == BASE_C||
					       base == BASE_D || base == BASE_E|| base == BASE_F){
					    		HW_WRITE_REG_32BIT(base+GPIO_SLEW_RATE_CONTROL_SEL_OFFSET,val);
					    }else {
					    	state = INCORRECT_PORT;
					    }
					    return state;
}

gGPIOError_t gpioPinInterruptConfig(uint32 base,uint8 pin,gInterrConfig_t  *obj){
	gGPIOError_t state = PASS;
	/* Unmask interrupt on the specified pin.*/
	if(pin >MAX_PORT_PINS){
		state = INCORRECT_PIN_NUM;
	}else{
	HW_WRITE_BIT(base+GPIO_INTERRUPT_MASK_OFFSET,pin,HIGH);
     if(obj->interruptSenseControl == LOW_LEVEL || obj->interruptSenseControl == HIGH_LEVEL ){
    	 /*Enable Level sensitive interrupt.*/
    	 HW_WRITE_BIT(base+GPIO_INTERRUPT_SENSE_OFFSET,pin,HIGH);
    	 if(obj->interruptSenseControl == LOW_LEVEL){
    		 HW_WRITE_BIT(base+GPIO_INTERRUPT_EVENT_OFFSET,pin,LOW);
    	 }else if(obj->interruptSenseControl == HIGH_LEVEL){
    		 HW_WRITE_BIT(base+GPIO_INTERRUPT_EVENT_OFFSET,pin,HIGH);
    	 }else {
    		 state = INCORRECT_INTERRUPT_SENSE;
    	 }
     }else if(obj->interruptSenseControl == FALING_EDGE || obj->interruptSenseControl == RAISNG_EDGE ||
    		 obj->interruptSenseControl == BOTH_EDGES){
    	 /*Enable edge sensitive interrupt.*/
    	 HW_WRITE_BIT(base+GPIO_INTERRUPT_SENSE_OFFSET,pin,LOW);
    	 if(obj->interruptSenseControl == BOTH_EDGES){
    		 /*Enable interrupts on both edges*/
    		 HW_WRITE_BIT(base+GPIO_INTERRUPT_BOTH_EDGE_OFFSET,pin,HIGH);
    	 }else if(obj->interruptSenseControl == FALING_EDGE){
    		 HW_WRITE_BIT(base+GPIO_INTERRUPT_EVENT_OFFSET,pin,LOW);
    	 }else if(obj->interruptSenseControl == RAISNG_EDGE){
    		 HW_WRITE_BIT(base+GPIO_INTERRUPT_EVENT_OFFSET,pin,HIGH);
    	 }
     }else{
    	 state = INCORRECT_INTERRUPT_SENSE;
     }
	}
	return state;
}

gGPIOError_t gpioPinInterruptUnMask(uint32 base , uint8 pin , uint8 val){
	gGPIOError_t state = PASS;
	if(pin > MAX_PORT_PINS){
		state = INCORRECT_PIN_NUM;
	}else{
		if(val == TRUE || val == FALSE){
			HW_WRITE_BIT(base+GPIO_INTERRUPT_MASK_OFFSET,pin,val);
		}else{
			state = INCORRECT_VALUE;
		}
	}
	return state;
}

gGPIOError_t gpioPinInterruptClear(uint32 base , uint8 pin){
	gGPIOError_t state = PASS;
	if(pin > MAX_PORT_PINS){
		state = INCORRECT_PIN_NUM;
	}else{
		HW_WRITE_BIT(base+GPIO_INTERRUPT_CLEAR_OFFSET,pin,HIGH);
		}

	return state;
}
