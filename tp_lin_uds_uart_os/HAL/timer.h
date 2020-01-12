/*
 * timer.h
 *
 *  Created on: Aug 21, 2017
 *      Author: Mohab Adel
 */

#ifndef DRIVERS_HAL_TIMER_H_
#define DRIVERS_HAL_TIMER_H_
#include "../RAL/types.h"
#include "../RAL/hw_types.h"
#include "../RAL/hw_timer.h"
/*ENUM to define ERROR TYPES*/
typedef enum{
    PASS,INVALID_MODULE,INVALID_WIDTH

}gError_t;



/*ENUM to define Timer Width*/
typedef enum{
    MODE32=0,
    RTC=1,
    MODE16=4
}gTwidth;
/*ENUM to define timer modes*/
typedef enum{
    ONESHOT=1,
    PERIODIC,
    CAPTURE
}gTmode;
/*
 *
 */
typedef struct timer{
uint32 base;
gTwidth Objwidth;
gTmode Objmode;



}gtimer_t;

#endif /* DRIVERS_HAL_TIMER_H_ */
