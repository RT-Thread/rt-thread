/*
 * File      : porttimer.c
 * This file is part of freemodbus in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-04     yi.qiu      first version
 */
 
/* ----------------------- System includes --------------------------------*/
#include <rtthread.h>
#include <rthw.h>

/* ----------------------- Modbus includes ----------------------------------*/

/* ----------------------- Variables ----------------------------------------*/
static int level;

/* ----------------------- Start implementation -----------------------------*/
void EnterCriticalSection(void)
{
	level = rt_hw_interrupt_disable();
}

void ExitCriticalSection(void)
{
	rt_hw_interrupt_enable(level);
}

