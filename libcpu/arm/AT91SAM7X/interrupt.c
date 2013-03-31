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
 * 2006-08-23     Bernard      first version
 * 2013-03-29     aozima       Modify the interrupt interface implementations.
 */

#include <rtthread.h>
#include <rthw.h>
#include "AT91SAM7X256.h"

#define MAX_HANDLERS	32

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS]; 

extern rt_uint32_t rt_interrupt_nest;

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup AT91SAM7
 */
/*@{*/

static void rt_hw_interrupt_handler(int vector, void *param)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
	rt_base_t index;

    /* init exceptions table */
    for(index=0; index < MAX_HANDLERS; index++)
    {
        irq_desc[index].handler = (rt_isr_handler_t)rt_hw_interrupt_handler;
        irq_desc[index].param = RT_NULL;
    }

	for (index = 0; index < MAX_HANDLERS; index ++)
	{
		AT91C_BASE_AIC->AIC_SVR[index] = (rt_uint32_t)rt_hw_interrupt_handler;
	}

	/* init interrupt nest, and context in thread sp */
	rt_interrupt_nest = 0;
	rt_interrupt_from_thread = 0;
	rt_interrupt_to_thread = 0;
	rt_thread_switch_interrupt_flag = 0;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
	/* disable interrupt */
	AT91C_BASE_AIC->AIC_IDCR = 1 << vector;

	/* clear interrupt */
	AT91C_BASE_AIC->AIC_ICCR = 1 << vector;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	AT91C_BASE_AIC->AIC_IECR = 1 << vector;
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the parameter for interrupt service routine
 * @name unused.
 *
 * @return the old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, 
									void *param, char *name)
{
	rt_isr_handler_t old_handler = RT_NULL;
	if(vector >= 0 && vector < MAX_HANDLERS)
	{
		old_handler = irq_desc[vector].handler;
		if (handler != RT_NULL)
		{
			irq_desc[vector].handler = (rt_isr_handler_t)handler;
			irq_desc[vector].param = param;
		}
	}

	return old_handler;
}

/*@}*/
