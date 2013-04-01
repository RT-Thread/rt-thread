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
#include <rthw.h>
#include "jz47xx.h"

#define JZ47XX_MAX_INTR 32

extern rt_uint32_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static struct rt_irq_desc irq_handle_table[JZ47XX_MAX_INTR];

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

    rt_memset(irq_handle_table, 0x00, sizeof(irq_handle_table));
	for (index = 0; index < JZ47XX_MAX_INTR; index ++)
	{
		irq_handle_table[index].handler = (rt_isr_handler_t)rt_hw_interrupt_handler;
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
 * @param handler the interrupt service routine to be installed
 * @param param the interrupt service function parameter
 * @param name the interrupt name
 * @return old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector,
                             rt_isr_handler_t  handler,
                             void *param,
                             char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

	if (vector >= 0 && vector < JZ47XX_MAX_INTR)
	{
        old_handler = irq_handle_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
        rt_strncpy(irq_handle_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
        irq_handle_table[vector].handler = handler;
        irq_handle_table[vector].param = param;
	}

    return old_handler;
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
			irq_func = irq_handle_table[i].handler;

			/* do interrupt */
			(*irq_func)(i, irq_handle_table[i].param);

#ifdef RT_USING_INTERRUPT_INFO
			irq_handle_table[i].counter++;
#endif /* RT_USING_INTERRUPT_INFO */

			/* ack interrupt */
			INTC_IPR = (1 << i);
		}
	}
}

/*@}*/
