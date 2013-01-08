/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-15     Bernard      first version
 * 2010-10-15     lgnq         modified for LS1B
 */

#include <rtthread.h>
#include "ls1b.h"

#define MAX_INTR 32

extern rt_uint32_t rt_interrupt_nest;
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

static rt_isr_handler_t irq_handle_table[MAX_INTR];
void rt_interrupt_dispatch(void *ptreg);
void rt_hw_timer_handler();

static struct ls1b_intc_regs volatile *ls1b_hw0_icregs
	= (struct ls1b_intc_regs volatile *)(LS1B_INTREG_BASE);

/**
 * @addtogroup Loongson LS1B
 */

/*@{*/

void rt_hw_interrupt_handler(int vector)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
	rt_int32_t index;

	/* pci active low */ 
	ls1b_hw0_icregs->int_pol = -1; 	   //must be done here 20110802 lgnq
	/* make all interrupts level triggered */ 	
	(ls1b_hw0_icregs+0)->int_edge = 0x0000e000;
	/* mask all interrupts */
	(ls1b_hw0_icregs+0)->int_clr = 0xffffffff;

	for (index = 0; index < MAX_INTR; index ++)
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
	(ls1b_hw0_icregs+(vector>>5))->int_en &= ~(1 << (vector&0x1f));
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
	(ls1b_hw0_icregs+(vector>>5))->int_en |= (1 << (vector&0x1f));
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_install(int vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	if (vector >= 0 && vector < MAX_INTR)
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
	static rt_uint32_t status = 0;
	rt_uint32_t c0_status;
	rt_uint32_t c0_cause;
	volatile rt_uint32_t cause_im;
	volatile rt_uint32_t status_im;
	rt_uint32_t pending_im;

	/* check os timer */
	c0_status = read_c0_status();
	c0_cause = read_c0_cause();

	cause_im = c0_cause & ST0_IM;
	status_im = c0_status & ST0_IM;
	pending_im = cause_im & status_im;

	if (pending_im & CAUSEF_IP7)
	{
		rt_hw_timer_handler();
	}

	if (pending_im & CAUSEF_IP2)
	{
		/* the hardware interrupt */
		status = ls1b_hw0_icregs->int_isr;
		if (!status) 
			return;

		for (i = MAX_INTR; i > 0; --i)
		{
			if ((status & (1<<i)))
			{
				status &= ~(1<<i);
				irq_func = irq_handle_table[i];

				/* do interrupt */
				(*irq_func)(i);

				/* ack interrupt */
				ls1b_hw0_icregs->int_clr |= (1 << i);
			}
		}
	}
	else if (pending_im & CAUSEF_IP3)
	{		
		rt_kprintf("%s %d\r\n", __FUNCTION__, __LINE__);
	}
	else if (pending_im & CAUSEF_IP4)
	{		
		rt_kprintf("%s %d\r\n", __FUNCTION__, __LINE__);
	}
	else if (pending_im & CAUSEF_IP5)
	{		
		rt_kprintf("%s %d\r\n", __FUNCTION__, __LINE__);
	}
	else if (pending_im & CAUSEF_IP6)
	{		
		rt_kprintf("%s %d\r\n", __FUNCTION__, __LINE__);
	}
}

/*@}*/
