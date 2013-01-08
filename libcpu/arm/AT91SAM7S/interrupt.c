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
 */

#include <rtthread.h>
#include "AT91SAM7S.h"

#define MAX_HANDLERS	32

extern rt_uint32_t rt_interrupt_nest;

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup AT91SAM7
 */
/*@{*/

void rt_hw_interrupt_handler(int vector)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init()
{
	rt_base_t index;

	for (index = 0; index < MAX_HANDLERS; index ++)
	{
		AT91C_AIC_SVR(index) = (rt_uint32_t)rt_hw_interrupt_handler;
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
	AT91C_AIC_IDCR = 1 << vector;

	/* clear interrupt */
	AT91C_AIC_ICCR = 1 << vector;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	AT91C_AIC_IECR = 1 << vector;
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	if(vector >= 0 && vector < MAX_HANDLERS)
	{
		if (*old_handler != RT_NULL) *old_handler = (rt_isr_handler_t)AT91C_AIC_SVR(vector);
		if (new_handler != RT_NULL) AT91C_AIC_SVR(vector) = (rt_uint32_t)new_handler;
	}
}

/*@}*/
