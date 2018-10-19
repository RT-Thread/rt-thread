/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef FH_TIMER_H_
#define FH_TIMER_H_

 /****************************************************************************
 * #include section
 *	add #include here if any
 ***************************************************************************/
#include "fh_def.h"




 /****************************************************************************
 * #define section
 *	add constant #define here if any
 ***************************************************************************/
#define TIMER_CTRL_ENABLE   (1u << 0)
#define TIMER_CTRL_MODE     (1u << 1)
#define TIMER_CTRL_INTMASK  (1u << 2)
#define TIMER_CTRL_PWMEN    (1u << 3)



 /****************************************************************************
 * ADT section
 *	add Abstract Data Type definition here
 ***************************************************************************/
typedef struct {
	RwReg TIMER_LOAD_COUNT;
	RwReg TIMER_CURRENT_VALUE;
	RwReg TIMER_CTRL_REG;
	RwReg TIMER_EOI;
	RwReg TIMER_INT_STATUS;
}timer;

 enum timer_mode {
 	TIMER_MODE_PERIODIC = 0,
 	TIMER_MODE_ONESHOT = 1,
 };




/****************************************************************************
*  extern variable declaration section
***************************************************************************/

/****************************************************************************
*  section
*	add function prototype here if any
***************************************************************************/


int timer_init(timer *tim);

int timer_set_mode(timer *tim, enum timer_mode);

void timer_set_period(timer *tim, UINT32 period, UINT32 clock);

void timer_enable(timer *tim);

void timer_disable(timer *tim);

void timer_enable_irq(timer *tim);

void timer_disable_irq(timer *tim);

UINT32 timer_get_status(timer *tim);

void udelay(unsigned long usec);


#endif /* #ifndef _TIMER_ */

