/*
 * hw_timer.h
 *
 *  Created on: Aug 21, 2017
 *      Author: Mohab Adel
 */

#ifndef DRIVERS_RAL_HW_TIMER_H_
#define DRIVERS_RAL_HW_TIMER_H_

#define BASE_TIMER0     0x40030000
#define BASE_TIMER1     0x40031000
#define BASE_TIMER2     0x40032000
#define BASE_TIMER3     0x40033000
#define BASE_TIMER4     0x40034000
#define BASE_TIMER5     0x40035000

#define BASE_W_TIMER0   0x40036000
#define BASE_W_TIMER1   0x40037000
#define BASE_W_TIMER2   0x4003C000
#define BASE_W_TIMER3   0x4003D000
#define BASE_W_TIMER4   0x4003E000
#define BASE_W_TIMER5   0x4003F000

#define OFFSET_CFG      0x000
#define OFFSET_TAMR     0x004
#define OFFSET_TBMR     0x008
#define OFFSET_CTL      0x00C
#define OFFSET_SYNC     0x010
#define OFFSET_IMR      0x018
#define OFFSET_RIS      0x01C
#define OFFSET_MIS      0x020
#define OFFSET_ICR      0x024
#define OFFSET_TAILR    0x028
#define OFFSET_TBILR    0x02C
#define OFFSET_TAMATCHER   0x30
#define OFFSET_TBMATCHER   0x34
#define OFFSET_TAPR     0x038
#define OFFSET_TBPR     0x03C
#define OFFSET_TAPMR    0x040
#define OFFSET_TBPMR    0x044
#define OFFSET_TAR      0x048
#define OFFSET_TBR      0x04C
#define OFFSET_TAV      0x050
#define OFFSET_TBV      0x054
#define OFFSET_RTCPD    0x058
#define OFFSET_TAPS     0x05C
#define OFFSET_TBPS     0x060
#define OFFSET_TAPV     0x064
#define OFFSET_TBPV     0x068
#define OFFSET_PP       0xFC0
#endif /* DRIVERS_RAL_HW_TIMER_H_ */
