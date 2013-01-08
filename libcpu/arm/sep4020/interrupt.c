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
 * 2006-03-13     Bernard      first version
 */

#include <rtthread.h>
#include <sep4020.h>

#define MAX_HANDLERS	32

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
rt_isr_handler_t isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup S3C24X0
 */
/*@{*/

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector)
{
	rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
	return RT_NULL;
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init()
{
	register rt_uint32_t idx;

	/*Make sure all intc registers in proper state*/

	/*mask all the irq*/
	*(RP)(INTC_IMR) = 0xFFFFFFFF;

	/*enable all the irq*/
	*(RP)(INTC_IER)	= 0XFFFFFFFF;

	/*Dont use any forced irq*/
	*(RP)(INTC_IFR) = 0x0;

	/*Disable all the fiq*/
	*(RP)(INTC_FIER) = 0x0;

	/*Mask all the fiq*/
	*(RP)(INTC_FIMR) = 0x0F;

	/*Dont use forced fiq*/
	*(RP)(INTC_FIFR) = 0x0;

	/*Intrrupt priority register*/
	*(RP)(INTC_IPLR) = 0x0;

	/* init exceptions table */
	for(idx=0; idx < MAX_HANDLERS; idx++)
	{
		isr_table[idx] = (rt_isr_handler_t)rt_hw_interrupt_handle;
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
void rt_hw_interrupt_mask(rt_uint32_t vector)
{
	*(RP)(INTC_IMR) |= 1 << vector;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(rt_uint32_t vector)
{
	if(vector == 16)
	{
		rt_kprintf("Interrupt vec %d is not used!\n", vector);
	}
	else
		*(RP)(INTC_IMR) &= ~(1 << vector);
}


/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_install(rt_uint32_t vector, rt_isr_handler_t new_handler, rt_isr_handler_t *old_handler)
{
	if(vector < MAX_HANDLERS)
	{
		if (*old_handler != RT_NULL)
			*old_handler = isr_table[vector];
		if (new_handler != RT_NULL) 
			isr_table[vector] = new_handler;
	}
}

/*@}*/
