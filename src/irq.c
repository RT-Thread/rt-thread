/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-24     Bernard      first version
 * 2006-05-03     Bernard      add IRQ_DEBUG
 * 2016-08-09     ArdaFu       add interrupt enter and leave hook.
 * 2018-11-22     Jesven       rt_interrupt_get_nest function add disable irq
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
#endif /* RT_USING_HOOK */

/**
 * @addtogroup Kernel
 */

/**@{*/

#ifdef RT_USING_SMP
#define rt_interrupt_nest rt_cpu_self()->irq_nest
#else
volatile rt_uint8_t rt_interrupt_nest = 0;
#endif /* RT_USING_SMP */

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

#ifdef RT_USING_SMP
    level = rt_hw_local_irq_disable();
#else
    level = rt_hw_interrupt_disable();
#endif
    rt_interrupt_nest ++;
    RT_OBJECT_HOOK_CALL(rt_interrupt_enter_hook,());
#ifdef RT_USING_SMP
    rt_hw_local_irq_enable(level);
#else
    rt_hw_interrupt_enable(level);
#endif

    RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq has come..., irq current nest:%d\n",
                                rt_interrupt_nest));
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

    RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq is going to leave, irq current nest:%d\n",
                                rt_interrupt_nest));

#ifdef RT_USING_SMP
    level = rt_hw_local_irq_disable();
#else
    level = rt_hw_interrupt_disable();
#endif
    rt_interrupt_nest --;
    RT_OBJECT_HOOK_CALL(rt_interrupt_leave_hook,());
#ifdef RT_USING_SMP
    rt_hw_local_irq_enable(level);
#else
    rt_hw_interrupt_enable(level);
#endif
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
RT_WEAK rt_uint8_t rt_interrupt_get_nest(void)
{
    rt_uint8_t ret;
    rt_base_t level;

#ifdef RT_USING_SMP
    level = rt_hw_local_irq_disable();
#else
    level = rt_hw_interrupt_disable();
#endif
    ret = rt_interrupt_nest;
#ifdef RT_USING_SMP
    rt_hw_local_irq_enable(level);
#else
    rt_hw_interrupt_enable(level);
#endif
    return ret;
}
RTM_EXPORT(rt_interrupt_get_nest);

RTM_EXPORT(rt_hw_interrupt_disable);
RTM_EXPORT(rt_hw_interrupt_enable);

/**@}*/

