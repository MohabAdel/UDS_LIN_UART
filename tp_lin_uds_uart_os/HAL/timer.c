/*
 * timer.c
 *
 *  Created on: Aug 21, 2017
 *      Author: Mohab Adel
 */
#include "timer.h"

gError_t TIMER_SELECT_WIDTH(uint32 base, gTwidth WIDTH)
{
    gError_t res = PASS;
    if (base == BASE_TIMER0 || base == BASE_TIMER1 || base == BASE_TIMER2
            || base == BASE_TIMER3 || base == BASE_TIMER4 || base == BASE_TIMER5
            || base == BASE_W_TIMER0 || base == BASE_W_TIMER1
            || base == BASE_W_TIMER2 || base == BASE_W_TIMER3
            || base == BASE_W_TIMER4 || base == BASE_W_TIMER5)
    {
        if (WIDTH == MODE32 || WIDTH == RTC || WIDTH == MODE16)
        {
        HW_WRITE_REG_32BIT(base+OFFSET_CFG,WIDTH);
        }
        else {
            res = INVALID_WIDTH;
        }
    }
    else
    {
        res = INVALID_MODULE;
    }
//CFG register
return res;
}

/*
 * This function is to confg the timer mode
 * For timers A-B
 * Writes the value in TAMR or TBMR register
 *  \\param
 *  base : the add  of timer_base
 *  mode : from the enum gTmode
 *  example  : TIMER_SET_MODE(BASE_TIMER2,PERIODIC)
 *  output :
 *  Enumerated value from gError_t defined in timer.h
 */
gError_t TIMER_SET_MODE(uint32 base, gTmode mode)
{

gError_t res = PASS;

if (base == BASE_TIMER0 || base == BASE_TIMER1 || base == BASE_TIMER2
        || base == BASE_TIMER3 || base == BASE_TIMER4 || base == BASE_TIMER5)
{
    if (mode == PERIODIC || mode == ONESHOT || mode == CAPTURE)
    {
    }
    //TAMR - TBMR

}
else
{
    res = INVALID_MODULE;
}
return res;
}

gError_t TIMER_COUNTMODE(uint32 base, uint8 CMODE)
{

}
gError_t TIMER_LOAD(uint32 base, uint32 value)
{
//TAILR  TBILR
}

gError_t TIMER_SET_PRESCALER(uint32 base, uint32 preValue)
{

}
gError_t TIMER_START(uint32 base)
{

}
gError_t TIMER_STOP(uint32 base)
{

}
