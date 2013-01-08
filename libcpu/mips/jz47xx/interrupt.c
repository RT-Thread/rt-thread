/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-09     Bernard      first version
 */
#include <rtthread.h>
#include "jz47xx.h"

#define JZ47XX_MAX_INTR 32

extern rt_uint32_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static rt_isr_handler_t irq_handle_table[JZ47XX_MAX_INTR];

/**
 * @addtogroup Jz47xx
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
	rt_int32_t index;

	for (index = 0; index < JZ47XX_MAX_INTR; index ++)
	{
		irq_handle_table[index] = (rt_isr_handler_t)rt_hw_interrupt_handler;
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
	/* mask interrupt */
	INTC_IMSR = (1 << vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	INTC_IMCR = (1 << vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	if (vector >= 0 && vector < JZ47XX_MAX_INTR)
	{
		if (old_handler != RT_NULL)
			*old_handler = irq_handle_table[vector];
		if (new_handler != RT_NULL)
			irq_handle_table[vector] = (rt_isr_handler_t)new_handler;
	}
}

void rt_interrupt_dispatch(void *ptreg)
{
    int i;
	rt_isr_handler_t irq_func;
	static rt_uint32_t pending = 0;

    /* the hardware interrupt */
	pending |= INTC_IPR;
	if (!pending) return;

    for (i = JZ47XX_MAX_INTR; i > 0; --i)
    {
		if ((pending & (1<<i)))
        {
			pending &= ~(1<<i);
			irq_func = irq_handle_table[i];

			/* do interrupt */
			(*irq_func)(i);

			/* ack interrupt */
			INTC_IPR = (1 << i);
		}
	}
}

/*@}*/
