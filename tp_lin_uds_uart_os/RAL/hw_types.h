/**
 *   \file   hw_types.h
 *
 *   \brief  This file contains the in-line functions required to read/write
 *           values from/to the hardware registers. This file also contains field
 *           manipulation macros to get and set field values.
 *
 *   \date   Aug 6, 2017
 *
 *   \author Mohab Adel
 */

#ifndef HW_TYPES_H_
#define HW_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#ifndef INPUT
#define INPUT 0
#endif

#ifndef OUTPUT
#define OUTPUT 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif


/**
 *
 *  \brief  Macro to read a 32 bit register.
 *
 *  \param  address  32bit register address.
 *
 */
#define HW_READ_REG_32BIT(address) (*(volatile uint32*)(address))

/**
 *
 *  \brief  Macro to write a value to a 32 bit register.
 *
 *  \param  address  32bit register address.
 *  \param  value    value to write to the 32bit register.
 *
 */
#define HW_WRITE_REG_32BIT(address,value) ((*(volatile uint32*)(address)) = value )

/**
 *
 *  \brief  Macro to set a bit in a 32bit register.
 *
 *  \param  addr  32bit register address.
 *  \param  bit   the bit number to be set.
 *
 */
#define HW_SET_BIT(addr,bit) \
	(HW_READ_REG_32BIT(addr) |=(1<<bit))

/**
 *
 *  \brief  Macro to reset a 32 bit register.
 *
 *  \param  addr  32bit register address.
 *  \param  bit   the bit number to be reset.
 *
 */
#define HW_RESET_BIT(addr,bit) \
	(HW_READ_REG_32BIT(addr) &=~(1<<bit))

/**
 *
 *  \brief  Macro to write a 32 bit register software masked.
 *
 *  \param  addr   32bit register address.
 *  \param  value  value to be written.
 *  \param  mask   the required mask.
 *
 *  \details This function is used to write values to a specific number of bits
 *           and lets the other bits unchanged.
 *           This is controlled by the mask param , when a bit in he mask is set so the opposite bit
 *           in the register can be changed using the value in the value param.
 *           If the bit in the mask is cleared , the opposite bit in the register remains unchanged.
 *
 */
#define HW_WRITE_REG32_MASKED(add , value , mask) HW_WRITE_REG_32BIT(add,\
                                                               (HW_READ_REG_32BIT(add) & ~mask)|(value & mask))

/**
 *
 *  \brief  Macro to read a 32 bit register software masked.
 *
 *  \param  addr   32bit register address.
 *  \param  mask   the required mask.
 *
 *  \details This function is used to read values from a specific number of bits in a register.
 *           This is controlled by the mask param , when a bit in he mask is set so the opposite bit
 *           in the register can be read.
 *           If the bit in the mask is cleared , the opposite bit in the register read as 0.
 */
#define HW_READ_REG32_MASKED(add , mask)  (HW_READ_REG_32BIT(add)&(mask))
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Global Variables Declarations                        */
/* ========================================================================== */

/* None */


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/**
 *  \brief  This function is to write a bit within a 32bit register.
 *
 *  \param  reg  32bit register
 *  \param  pin  pin number for the pin to change its value.
 *  \param  val  the value to update the pin content.
 *
 */
static void HW_WRITE_BIT(uint32 reg, uint8 pin , uint8 val);


/**
 *  \brief  This function is to read a bit within a 32bit register.
 *
 *  \param  reg  32bit register
 *  \param  pin  pin number for the pin to read its value.
 *
 *  \retval bit-field value of the pin.(shifted to LSB ,return value will only be (0 or 1)
 *
 */
static uint8 HW_READ_BIT(uint32 reg,uint8 pin);


/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */


static void HW_WRITE_BIT(uint32 reg, uint8 pin , uint8 val){
	if(val == HIGH){
	HW_READ_REG_32BIT(reg) |= (1<<pin);
	}else if(val == LOW){
		HW_READ_REG_32BIT(reg) &= ~(1<<pin);
	}
}

static  uint8 HW_READ_BIT(uint32 reg,uint8 pin){

	return ((HW_READ_REG_32BIT(reg)&(1<<pin))>>pin);
}
#endif /* HW_TYPES_H_ */
