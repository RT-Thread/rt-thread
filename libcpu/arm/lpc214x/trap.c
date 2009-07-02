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
 */

#include <rthw.h>
#include <rtthread.h>
#include "lpc214x.h"

/**
 * @addtogroup LPC214x
 */
/*@{*/

void rt_hw_trap_irq()
{
	rt_isr_handler_t isr_func;
	
	isr_func = (rt_isr_handler_t) VICVectAddr;
	isr_func(0);
	
	/* acknowledge Interrupt */
	// VICVectAddr = 0;
}

void rt_hw_trap_fiq()
{
    rt_kprintf("fast interrupt request\n");
}

/*@}*/
