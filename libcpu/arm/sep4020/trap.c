/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-25     Bernard      first version
 * 2010-03-18     zchong       for sep4020
 */

#include <rtthread.h>
#include <rthw.h>

#include "sep4020.h"

/**
 * @addtogroup SEP4020
 */
/*@{*/

extern rt_isr_handler_t isr_table[];

void rt_hw_trap_irq()
{
	rt_uint32_t intstat,intnum;
    rt_uint8_t i = 0;
	rt_isr_handler_t isr_func;
    
    /* get interrupt source */
	intstat = INTC_IFSR;

	intnum = intstat;
    if (intstat == INTGLOBAL) return;

	while(intnum != 0x00000001)
	{
		intnum = intnum>>1;
		i++;
	}
	/* get interrupt service routine */
	isr_func = isr_table[i];

	/* turn to interrupt service routine */
	isr_func(intstat);

}

void rt_hw_trap_fiq()
{
    rt_kprintf("fast interrupt request\n");
}

extern struct rt_thread* rt_current_thread;
void rt_hw_trap_abort()
{
	rt_kprintf("Abort occured!!! Thread [%s] suspended.\n",rt_current_thread->name);
	rt_thread_suspend(rt_current_thread);
	rt_schedule();

}
/*@}*/
