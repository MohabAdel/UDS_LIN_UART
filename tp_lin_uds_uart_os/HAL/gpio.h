/**
 *  \file     gpio.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of GPIO.
 *            This also contains some related macros.
 *
 *  \details  The detailed description of gpio is:
 *            -# Up to 43 GPIOs, depending on configuration.
 *            -# Highly flexible pin muxing allows use as GPIO or one of several peripheral functions.
 *            -# Ports A-F accessed through the Advanced Peripheral Bus (APB).
 *            -# Fast toggle capable of a change every clock cycle for ports on AHB,
 *               every two clock cycles for ports on APB.
 *            -# 5-V-tolerant in input configuration.
 *            -# Programmable control for GPIO interrupts:
 *                -# Interrupt generation masking.
 *                -# Edge-triggered on rising, falling, or both.
 *                -# Level-sensitive on High or Low values.
 *            -# Bit masking in both read and write operations through address lines.
 *            -# Can be used to initiate an ADC sample sequence or a μDMA transfer.
 *            -# Pin state can be retained during Hibernation mode.
 *            -# Pins configured as digital inputs are Schmitt-triggered.
 *            -# Programmable control for GPIO pad configuration :
 *                 -# Weak pull-up or pull-down resistors.
 *                 -# 2-mA, 4-mA, and 8-mA pad drive for digital communication;
 *                    up to four pads can sink 18-mA for high-current applications.
 *                 -# Slew rate control for 8-mA pad drive.
 *                 -# Open drain enables.
 *                 -# Digital input enables.
 *
 *  \date     Aug 6, 2017
 *
 *  \author   Mohab Adel
 */

#ifndef GPIO_H_
#define GPIO_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "../RAL/types.h"
#include "../RAL/hw_types.h"
#include "../RAL/hw_gpio.h"
/* ========================================================================== */
/*                             Macros & Typedefs                              */
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

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** \brief Max gpio port pins*/
#define MAX_PORT_PINS         8
/** \brief Hardware mask to access all the GPIO data register bits.*/
#define GPIO_DATA_HW_MASK     0x3FC
/** \brief Value used to unlock port to enable the Commit register.*/
#define GPIO_UNLOCK_PORT      0x4C4F434B
/** \brief Value used to lock port to disable the Commit register ;Any value other than 0x4C4F434B.*/
#define GPIO_LOCK_PORT        0xFFFFFFFF
/** \brief Max analog pins in analog mode select register. */
#define MAX_ANALOG_PINS       3
/** \brief Max value that can be hold by analog mode select register. */
#define MAX_ANALOG_REG_VAL    16
/** \brief    This value is used to mask 4 bits to be changed in port control
 *            register and leaves the others ,28 bit, unchanged.
 *
 *  \details  The port control register is used to activate alternate functionality.
 *            Each gpio pin has a 4 bits in this register that control its behavior.
 *            So the mask is enabling these 4 bits to change the value in these 4 bits
 *            only and leaves other bits unchanged. */
#define GPIO_PORTCONTROL_MASK 0xF
/**  \brief    This is used as step for the GPIO port control register.
 *
 *    \details  This step is used to shift the value to write to gpio port control
 *              register and shift the mask by 4 as each gpio pin has 4 bits in the
 *              gpio port control register that controls its behavior so the step
 *              is 4 from on pin and the previous pin.
 *              4 * pin number == the specified 4 bits in the gpio port control register for
 *                                the specified pin.
 *              */
#define PORT_CONTROL_STEP     4
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Enumerate the types of errors in the gpio module.*/
typedef enum {
	PASS , INCORRECT_PORT , INCORRECT_PIN_NUM , DIRECTION_ERROR ,
	INCORRECT_MASK , INCORRECT_VALUE , INCORRECT_INTERRUPT_SENSE
}gGPIOError_t;

/** \brief Enumerate the types of resistors in the gpio module.*/
typedef enum{
	PULL_UP_RES , PULL_DOWN_RES ,OPEN_DRAIN
}gResType_t;

/** \brief Enumerate the types of current driven in the gpio module.*/
typedef enum{
	 CURRENT_2MA, CURRENT_4MA, CURRENT_8MA
}gCurrentVal_t;

/** \brief Enumerate the types of interrupt sensitivity in the gpio module.*/
typedef enum
{
    FALING_EDGE, RAISNG_EDGE, BOTH_EDGES, LOW_LEVEL, HIGH_LEVEL
} gInterrSenseControl_t;

/** \brief structure holding pad configurations.*/
typedef struct configPad{
	gResType_t resType;
	/**< Select resistor type.*/
	gCurrentVal_t currentVal;
	/**< Select driven current.*/
	uint8 lockFlag;
	/**< Specify if the pad is locked or unlocked
	 *    -# TRUE  :   locked.
	 *    -# FALSE :   unlocked*/
}gConfigPad_t;

/** \brief structure holding interrupt configurations.*/
typedef struct intcfg{
	gInterrSenseControl_t interruptSenseControl;
	/**< pointer to function that holds the address of the function that will be
	 *   executed when interrupt occurs.*/
}gInterrConfig_t;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief   Set pin direction INPUT or OUTPUT
 *
 *  \param   base The memory address of the GPIO instance being used.
 *           base can have 5 values :
 *             -# BASE_A
 *             -# BASE_B
 *             -# BASE_C
 *             -# BASE_D
 *             -# BASE_E
 *             -# BASE_F
 *  \param   pin  The number of the pin in the GPIO instance.
 *  \param   dir  The required direction for the GPIO pin.
 *           dir   can take one of two values :
 *            -# INPUT
 *            -# OUTPUT
 *
 *   \retval  returns a value specified in the enum
 *             -# gGPIOError_t
 * */
gGPIOError_t setPinDir(uint32 base , uint8 pin , uint8 dir);

/**
 *  \brief   Write value to a GPIO pin
 *
 *  \param   base The memory address of the GPIO instance being used.
 *           base can have 5 values :
 *             -# BASE_A
 *             -# BASE_B
 *             -# BASE_C
 *             -# BASE_D
 *             -# BASE_E
 *             -# BASE_F
 *  \param   pin  The number of the pin in the GPIO instance.
 *  \param   val  The required value to be written to the GPIO pin.
 *           val   can take one of two values :
 *            -# HIGH
 *            -# LOW
 *
 *   \retval  returns a value specified in the enum
 *             -# gGPIOError_t
 * */
gGPIOError_t writePin(uint32 base , uint8 pin , uint8 val);

/**
 *  \brief   Read a GPIO pin value.
 *
 *  \param   base  The memory address of the GPIO instance being used.
 *  *        base can have 5 values :
 *             -# BASE_A
 *             -# BASE_B
 *             -# BASE_C
 *             -# BASE_D
 *             -# BASE_E
 *             -# BASE_F
 *  \param   pin   The number of the pin in the GPIO instance.
 *  \param   data  The pin value.
 *           data  can have only one of two values ( 0 or 1).
 *
 *  \retval  returns a value specified in the enum
 *             -# gGPIOError_t
 * */
gGPIOError_t readPin(uint32 base , uint8 pin , uint8 *data);

/**
 *  \brief   Set port direction.
 *
 *  \param   base The memory address of the GPIO instance being used.
 *  *        base can have 5 values :
 *             -# BASE_A
 *             -# BASE_B
 *             -# BASE_C
 *             -# BASE_D
 *             -# BASE_E
 *             -# BASE_F
 *  \param   dirVal  The required direction for the GPIO port.
 *
 *   \retval  returns a value specified in the enum
 *             -# gGPIOError_t
 * */
gGPIOError_t setPortDir(uint32 base , uint8 dirVal);

/**
 *  \brief   write value to a GPIO port.
 *
 *  \param   base The memory address of the GPIO instance being used.
 *           base can have 5 values :
 *             -# BASE_A
 *             -# BASE_B
 *             -# BASE_C
 *             -# BASE_D
 *             -# BASE_E
 *             -# BASE_F
 *  \param   val  The value to be written to the GPIO port.
 *
 *   \retval  returns a value specified in the enum
 *             -# gGPIOError_t
 * */
gGPIOError_t writePort(uint32 base , uint8 val);

/**
 *  \name      readPort
 *
 *  \brief     read the GPIO port value.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     data  Holds the GPIO port value.
 *
 *   \retval  returns a value specified in the enum
 *             -# gGPIOError_t
 * */
gGPIOError_t readPort(uint32 base , uint8 *data);

/**
 *  \name      writeHWMaskedPins
 *
 *  \brief     write pins using hardware masking.
 *
 *  \param     base  The memory address of the GPIO instance being used.
 *             base  can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val  Holds value to be written to specific bits.
 *  \param     mask used to allow or disallow hardware masking for bits :
 *             if mask bit opposite to GPIO pin is set , hardware masking is enabled for this pin.
 *             if mask bit opposite to GPIO pin is cleared , hardware masking is disabled for this pin.
 *  \retval    returns a value specified in the enum
 *               -# gGPIOError_t
 *
 *  \details   Tiva C has a hardware masking feature in reading and writing to the GPIO data
 *             register.
 *             This hardware masking is faster than the software masking.
 *
 * */
gGPIOError_t writeHWMaskedPins(uint32 base , uint8 val, uint8 mask);

/**
 *  \name      readHWMaskedPins
 *
 *  \brief     read pins using hardware masking.
 *
 *  \param     base  The memory address of the GPIO instance being used.
 *             base  can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     data  Holds value of hardware masked bits.
 *  \param     mask used to allow or disallow hardware masking for bits :
 *             if mask bit opposite to GPIO pin is set , hardware masking is enabled for this pin.
 *             if mask bit opposite to GPIO pin is cleared , hardware masking is disabled for this pin.
 *  \retval    returns a value specified in the enum
 *               -# gGPIOError_t
 *
 *  \details   Tiva C has a hardware masking feature in reading and writing to the GPIO data
 *             register.
 *             This hardware masking is faster than the software masking.
 *
 * */
gGPIOError_t readHWMaskedPins(uint32 base , uint16 mask , uint8 *data);

/**
 *  \name      pinAlternateFunctionSel
 *
 *  \brief     Select if GPIO pin will operate as a GPIO or an alternate function.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     data  Holds the GPIO port value.
 *  \param     pin   The number of the GPIO pin.
 *  \param     val   The value to enable or disable alternate function.
 *             val   can take one of two values :
 *                -# TRUE
 *                -# FALSE
 *  \retval    returns a value specified in the enum
 *               -# gGPIOError_t
 * */
gGPIOError_t pinAlternateFunctionSel(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      portAlternateFunctionSel
 *
 *  \brief     Select if GPIO port will operate as a GPIO or an alternate function.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   The value to enable or disable alternate function.

 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 * */
gGPIOError_t portAlternateFunctionSel(uint32 base , uint8 val);

/**
 *  \name      pinSetPadConfig
 *
 *  \brief     Set pad configuartion for a GPIO pin.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   The GPIO pin number.
 *  \param     obj   Pointer to the pad configuration struct.
 *             Its contented can be viewed in structure :
 *               -# gConfigPad_t

 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 * */
gGPIOError_t pinSetPadConfig(uint32 base , uint8 pin , gConfigPad_t *obj);

/**
 *  \name      portSetPadConfig
 *
 *  \brief     Set pad configuartion for a GPIO pin.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     obj   Pointer to the pad configuration struct.
 *             Its contented can be viewed in structure :
 *               -# gConfigPad_t

 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 * */
gGPIOError_t portSetPadConfig(uint32 base , gConfigPad_t *obj);

/**
 *  \name      portUnLock
 *
 *  \brief     Unlock the GPIO instance to allow updating values.
 *             Unlocks the commit register.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   Is to Lock or Unlock the port.
 *             val   can take one of the values :
 *                -# TRUE  : to unlock port.
 *                -# FALSE : to lock port.

 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 *  \note      Before using portCommit function , you must Unlock the port first
 *              using portUnlock function.
 * */
gGPIOError_t portUnLock(uint32 base , uint8 val);

/**
 *  \name      portCommit
 *
 *  \brief     Allows GPIO registers to be updated.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   Used to allow or disallow updates to a GPIO port.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 *  \note      Before using portCommit function , you must Unlock the port first
 *             using portUnlock function.
 * */
gGPIOError_t portCommit(uint32 base , uint8 val);

/**
 *  \name      pinCommit
 *
 *  \brief     Allows GPIO pin to be updated.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   The GPIO pin number.
 *  \param     val   Used to allow or disallow updates to a GPIO pin.
 *             val   can take on of two values
 *               -# TRUE  : enables  update.
 *               -# FALSE : disables update.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 *  \note      Before using portCommit function , you must Unlock the port first
 *             using portUnlock function.
 * */
gGPIOError_t pinCommit(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      portDigitalEnable
 *
 *  \brief     Set or rest GPIO digital functionality.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   Value to enable or disable digital functionality.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t

 * */
gGPIOError_t portDigitalEnable(uint32 base , uint8 val);

/**
 *  \name      pinDigitalEnable
 *
 *  \brief     Set or rest GPIO pin digital functionality.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   Pin number in the GPIO instance.
 *  \param     val   Value to enable or disable digital functionality.
 *             val   take one of two values :
 *               -# TRUE : digital enable.
 *               -# FALSE: digital disable.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t

 * */
gGPIOError_t pinDigitalEnable(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      pinAnalogModeSelect
 *
 *  \brief     Set or rest GPIO pin to analog functionality.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   Pin number in the GPIO instance.
 *  \param     val   Value to enable or disable analog functionality.
 *             val   take one of two values :
 *               -# TRUE : analog enable.
 *               -# FALSE: analog disable.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t

 * */
gGPIOError_t pinAnalogModeSelect(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      portAnalogModeSelect
 *
 *  \brief     Set or rest GPIO portto analog functionality.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   Value to enable or disable analog functionality.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t

 * */
gGPIOError_t portAnalogModeSelect(uint32 base , uint8 val);

/**
 *  \name      portAdcTrigger
 *
 *  \brief     Configure GPIO port to trigger ADC.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   Value to enable or disable  adc trigger for port pins.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 * */
gGPIOError_t portAdcTrigger(uint32 base , uint8 val);

/**
 *  \name      pinAdcTrigger
 *
 *  \brief     Configure GPIO port to trigger ADC.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   pin number in the GPIO instance.
 *  \param     val   Value to enable or disable  adc trigger for port pins.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 * */

gGPIOError_t pinAdcTrigger(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      GPIOPortDMATrigger
 *
 *  \brief     Configure GPIO port to trigger DMA.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val   Value to enable or disable  DMA trigger for port pins.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 * */
gGPIOError_t GPIOPortDMATrigger(uint32 base , uint8 val);

/**
 *  \name      GPIOPinDMATrigger
 *
 *  \brief     Configure GPIO pin to trigger DMA.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   pin number in the GPIO instance.
 *  \param     val   Value to enable or disable  DMA trigger for port pins.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 * */
gGPIOError_t GPIOPinDMATrigger(uint32 base , uint8 pin ,uint8 val);

/**
 *  \name      GPIOPinControl
 *
 *  \brief     Controls the functionality of GPIO pin.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin   pin number in the GPIO instance.
 *  \param     val   Value to select the functionality of port pins.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 * */
gGPIOError_t GPIOPinControl(uint32 base , uint8 pin ,uint32 val);

/**
 *  \name      GPIOPortControl
 *
 *  \brief     Sets the GPIO functionality to digital functionality.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 * */
gGPIOError_t GPIOPortControlClear(uint32 base );

/**
 *  \name      portSlewRateControl
 *
 *  \brief     Allows the slew rate control.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin  the number of the GPIO pin.
 *  \param     val  the value to enable slew rate control.
 *             val can take one of two values :
 *               -# TRUE : enable slew rate control.
 *               -# FALSE: disable slew rate control.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 *  \note      ## TO use slew rate control the driven current must be 8 mA.
 *  */
gGPIOError_t pinSlewRateControl(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      portSlewRateControl
 *
 *  \brief     Allows the slew rate control.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     val  the value to enable slew rate control.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 *
 *  \note      ## TO use slew rate control the driven current must be 8 mA.
 * */
gGPIOError_t portSlewRateControl(uint32 base , uint8 val);

/**
 *  \name      gpioPinInterruptConfig
 *
 *  \brief     Configures interrupts for the GPIO pin.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin  the pin number in the GPIO instance.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 * */
gGPIOError_t gpioPinInterruptConfig(uint32 base,uint8 pin,gInterrConfig_t  *obj);

/**
 *  \name      gpioPinInterruptUnMask
 *
 *  \brief     Mask or unmask interrupt for GPIO pin.
 *             used mainly to mask the interrupt.
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin  the pin number in the GPIO instance.
 *  \param     val  the value to mask or unmask interrupt
 *             val  can take one if two values :
 *               -# TRUE : unmask interrupt
 *               -# FALSE: mask interrupt
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 * */
gGPIOError_t gpioPinInterruptUnMask(uint32 base , uint8 pin , uint8 val);

/**
 *  \name      gpioPinInterruptClear
 *
 *  \brief     Clears interrupt flag
 *
 *  \param     base The memory address of the GPIO instance being used.
 *             base can have 5 values :
 *               -# BASE_A
 *               -# BASE_B
 *               -# BASE_C
 *               -# BASE_D
 *               -# BASE_E
 *               -# BASE_F
 *  \param     pin  the pin number in the GPIO instance.
 *
 *  \retval    returns a value specified in the enum
 *              -# gGPIOError_t
 * */
gGPIOError_t gpioPinInterruptClear(uint32 base , uint8 pin);
#endif /* GPIO_HAL_GPIO_H_ */
