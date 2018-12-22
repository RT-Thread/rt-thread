/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
#include "inc/fh_driverlib.h"
/*****************************************************************************
 * Define section
 * add all #define here
 *****************************************************************************/

/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/



/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/

/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/


/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/




 /* function body */


/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/
int timer_init(timer *tim)
{
	tim->TIMER_CTRL_REG = 0;
}

int timer_set_mode(timer *tim, enum timer_mode mode)
{
	switch (mode)
	{
		case TIMER_MODE_PERIODIC:
			tim->TIMER_CTRL_REG |= TIMER_CTRL_MODE;
			break;
		case TIMER_MODE_ONESHOT:
			tim->TIMER_CTRL_REG |= TIMER_CTRL_MODE;
			break;
		default:
			rt_kprintf("Not support TIMER mode\n");
			return -1;
			break;
	}

	return 0;
}

void timer_set_period(timer *tim, UINT32 period, UINT32 clock)
{
	tim->TIMER_LOAD_COUNT = clock/period;
}



void timer_enable(timer *tim)
{
	tim->TIMER_CTRL_REG |= TIMER_CTRL_ENABLE;
}

void timer_disable(timer *tim)
{
	tim->TIMER_CTRL_REG &= ~TIMER_CTRL_ENABLE;
}

void timer_enable_irq(timer *tim)
{
	tim->TIMER_CTRL_REG &= ~TIMER_CTRL_INTMASK;
}

void timer_disable_irq(timer *tim)
{
	tim->TIMER_CTRL_REG |= TIMER_CTRL_INTMASK;
}

UINT32 timer_get_status(timer *tim)
{
	return tim->TIMER_INT_STATUS;
}

UINT32 timer_get_eoi(timer *tim)
{
	return tim->TIMER_EOI;
}

UINT32 timer_get_value(timer *tim)
{
	return tim->TIMER_LOAD_COUNT - tim->TIMER_CURRENT_VALUE;
}
