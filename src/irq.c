/*
 * File      : irq.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-24     Bernard      first version
 * 2006-05-03     Bernard      add IRQ_DEBUG
 */

#include <rthw.h>
#include <rtthread.h>

/* #define IRQ_DEBUG */

/**
 * @addtogroup Kernel
 */

/*@{*/

volatile rt_uint8_t rt_interrupt_nest;

/**
 * This function will be invoked by BSP, when enter interrupt service routine
 *
 * @note please don't invoke this routine in application
 *
 * @see rt_interrupt_leave
 */
void rt_interrupt_enter(void)
{
	rt_base_t level;

	RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq comming..., irq nest:%d\n", rt_interrupt_nest));

	level = rt_hw_interrupt_disable();
	rt_interrupt_nest ++;
	rt_hw_interrupt_enable(level);
}

/**
 * This function will be invoked by BSP, when leave interrupt service routine
 *
 * @note please don't invoke this routine in application
 *
 * @see rt_interrupt_enter
 */
void rt_interrupt_leave(void)
{
	rt_base_t level;

	RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq leave, irq nest:%d\n", rt_interrupt_nest));

	level = rt_hw_interrupt_disable();
	rt_interrupt_nest --;
	rt_hw_interrupt_enable(level);
}

/**
 * This function will return the nest of interrupt.
 * 
 * User application can invoke this function to get whenther current 
 * context is interrupt context.
 * 
 * @return the number of nested interrupts.
 */
rt_uint8_t rt_interrupt_get_nest(void)
{
	return rt_interrupt_nest;
}

/*@}*/

