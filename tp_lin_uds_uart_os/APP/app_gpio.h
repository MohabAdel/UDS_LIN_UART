/**
 *  \file   app_gpio.h
 *  \brief  This file contains the function declarations and data structures
 *          corresponding to the gpio.
 *  \date   Aug 8, 2017
 *  \author Mohab Adel
 */

#ifndef APP_GPIO_H_
#define APP_GPIO_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "../HAL/gpio.h"
#include "../HAL/sysctrl.h"
/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/** \brief  values for the RGB led on portF.*/
#define RGB_RED      0x02
#define RGB_BLUE     0x04
#define RGB_GREEN    0x08
#define RGB_YELLOW   0x0A
#define RGB_SKYBLUE  0x0C
#define RGB_WHITE    0x0E
#define RGB_PINk     0x06
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/** \brief structure holding the GPIO pin object.*/
typedef struct gpioIns{
	uint8 pin_num;
	/**< GPIO pin number.*/
	uint32 base;
	/**< GPIO port :
	 *        -# BASE_A
	 *        -# BASE_B
	 *        -# BASE_C
	 *        -# BASE_D
	 *        -# BASE_E
	 *        -# BASE_F          */
	uint8 dir;
	/**< Pin direction :
	 *          -# INPUT
	 *          -# OUTPUT
	 *          */
	gConfigPad_t configPadObj;
	/**< GPIO pin configuration structure.*/

}gGPIOObj_t;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \name   initPin
 *
 *  \brief  perform GPIO pin digital initializations.
 *
 *  \param  obj Pointer to the GPIO object.
 *
 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t initPin(gGPIOObj_t *obj);

/**
 *  \name   initPort
 *
 *  \brief  perform GPIO port initializations.
 *
 *  \param  obj Pointer to the GPIO object.
 *  \param  val For port direction.
 *
 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t initPort(gGPIOObj_t *obj,uint8 val);

/**
 *  \name   digitalPinWrite
 *
 *  \brief  write values to a GPIO pin.
 *
 *  \param  obj Pointer to the GPIO object.
 *  \param  val the value to be written to the GPIO pin.
 *          val can take one of two values :
 *              -# HIGH
 *              -# LOW
 *
 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t digitalPinWrite(gGPIOObj_t *obj , uint8 val);

/**
 *  \name   digitalPortWrite
 *
 *
 *  \brief  write values to a GPIO port.
 *  \param  obj Pointer to the GPIO object.
 *  \param  val the value to be written to the GPIO port.

 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t digitalPortWrite(gGPIOObj_t *obj , uint8 val);

/**
 *  \name   digitalPinRead
 *
 *  \brief  Reads the value of a GPIO pin.
 *
 *  \param  obj Pointer to the GPIO object.
 *  \param  data a pointer that holds the pin value.

 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t digitalPinRead(gGPIOObj_t *obj , uint8 *data);

/**
 *  \name   digitalPortRead
 *
 *  \brief  Read the value of a GPIO port.
 *
 *  \param  obj Pointer to the GPIO object.
 *  \param  data a pointer that holds the port value.

 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t digitalPortRead(gGPIOObj_t *obj , uint8 *data);

/**
 *  \name   digitalWriteHWMaskedPins
 *
 *  \brief  Write the value of a GPIO pins using hardware masking.
 *
 *  \param  obj Pointer to the GPIO object.
 *  \param  mask the mask to read specific bits only.
 *  \param  val   values to be written to specific bits.

 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t digitalWriteHWMaskedPins(gGPIOObj_t *obj , uint8 mask , uint8 val);

/**
 *  \name   digitalReadHWMaskedPins
 *
 *  \brief  Read the value of a GPIO pins using hardware masking.
 *
 *  \param  obj Pointer to the GPIO object.
 *  \param  mask the mask to read specific bits only.
 *  \param  data a pointer that holds the port value.

 *  \retVal Value of the enumeration gGPIOError_t
 * */
gGPIOError_t digitalReadHWMaskedPins(gGPIOObj_t *obj , uint8 mask , uint8 *data);

#endif /* APP_GPIO_H_ */
