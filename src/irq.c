/*
 * File      : irq.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-24     Bernard      first version
 * 2006-05-03     Bernard      add IRQ_DEBUG
 * 2016-08-09     ArdaFu       add interrupt enter and leave hook.
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_HOOK

static void (*rt_interrupt_enter_hook)(void);
static void (*rt_interrupt_leave_hook)(void);

/**
 * @ingroup Hook
 * This function set a hook function when the system enter a interrupt 
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
void rt_interrupt_enter_sethook(void (*hook)(void))
{
    rt_interrupt_enter_hook = hook;
}
/**
 * @ingroup Hook
 * This function set a hook function when the system exit a interrupt. 
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
void rt_interrupt_leave_sethook(void (*hook)(void))
{
    rt_interrupt_leave_hook = hook;
}
#endif

/* #define IRQ_DEBUG */

/**
 * @addtogroup Kernel
 */

/**@{*/

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

    RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq coming..., irq nest:%d\n",
                                rt_interrupt_nest));

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest ++;
    RT_OBJECT_HOOK_CALL(rt_interrupt_enter_hook,());
    rt_hw_interrupt_enable(level);
}
RTM_EXPORT(rt_interrupt_enter);

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

    RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq leave, irq nest:%d\n",
                                rt_interrupt_nest));

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest --;
    RT_OBJECT_HOOK_CALL(rt_interrupt_leave_hook,());
    rt_hw_interrupt_enable(level);
}
RTM_EXPORT(rt_interrupt_leave);

/**
 * This function will return the nest of interrupt.
 *
 * User application can invoke this function to get whether current
 * context is interrupt context.
 *
 * @return the number of nested interrupts.
 */
rt_uint8_t rt_interrupt_get_nest(void)
{
    return rt_interrupt_nest;
}
RTM_EXPORT(rt_interrupt_get_nest);

RTM_EXPORT(rt_hw_interrupt_disable);
RTM_EXPORT(rt_hw_interrupt_enable);

/**@}*/

