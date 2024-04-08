/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-24     Bernard      first version
 * 2006-05-03     Bernard      add IRQ_DEBUG
 * 2016-08-09     ArdaFu       add interrupt enter and leave hook.
 * 2018-11-22     Jesven       rt_interrupt_get_nest function add disable irq
 * 2021-08-15     Supperthomas fix the comment
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to irq.c
 * 2022-07-04     Yunjie       fix RT_DEBUG_LOG
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2024-01-05     Shell        Fixup of data racing in rt_interrupt_get_nest
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG           "kernel.irq"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)

static void (*rt_interrupt_enter_hook)(void);
static void (*rt_interrupt_leave_hook)(void);

/**
 * @ingroup Hook
 *
 * @brief This function set a hook function when the system enter a interrupt
 *
 * @note The hook function must be simple and never be blocked or suspend.
 *
 * @param hook the function point to be called
 */
void rt_interrupt_enter_sethook(void (*hook)(void))
{
    rt_interrupt_enter_hook = hook;
}

/**
 * @ingroup Hook
 *
 * @brief This function set a hook function when the system exit a interrupt.
 *
 * @note The hook function must be simple and never be blocked or suspend.
 *
 * @param hook the function point to be called
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
volatile rt_atomic_t rt_interrupt_nest = 0;
#endif /* RT_USING_SMP */


/**
 * @brief This function will be invoked by BSP, when enter interrupt service routine
 *
 * @note Please don't invoke this routine in application
 *
 * @see rt_interrupt_leave
 */
rt_weak void rt_interrupt_enter(void)
{
    rt_atomic_add(&(rt_interrupt_nest), 1);
    RT_OBJECT_HOOK_CALL(rt_interrupt_enter_hook,());
    LOG_D("irq has come..., irq current nest:%d",
          (rt_int32_t)rt_atomic_load(&(rt_interrupt_nest)));
}
RTM_EXPORT(rt_interrupt_enter);


/**
 * @brief This function will be invoked by BSP, when leave interrupt service routine
 *
 * @note Please don't invoke this routine in application
 *
 * @see rt_interrupt_enter
 */
rt_weak void rt_interrupt_leave(void)
{
    LOG_D("irq is going to leave, irq current nest:%d",
                 (rt_int32_t)rt_atomic_load(&(rt_interrupt_nest)));
    RT_OBJECT_HOOK_CALL(rt_interrupt_leave_hook,());
    rt_atomic_sub(&(rt_interrupt_nest), 1);

}
RTM_EXPORT(rt_interrupt_leave);


/**
 * @brief This function will return the nest of interrupt.
 *
 * User application can invoke this function to get whether current
 * context is interrupt context.
 *
 * @return the number of nested interrupts.
 */
rt_weak rt_uint8_t rt_interrupt_get_nest(void)
{
    rt_uint8_t ret;
    rt_base_t level;

    level = rt_hw_local_irq_disable();
    ret = rt_atomic_load(&rt_interrupt_nest);
    rt_hw_local_irq_enable(level);
    return ret;
}
RTM_EXPORT(rt_interrupt_get_nest);

RTM_EXPORT(rt_hw_interrupt_disable);
RTM_EXPORT(rt_hw_interrupt_enable);

rt_weak rt_bool_t rt_hw_interrupt_is_disabled(void)
{
    return RT_FALSE;
}
RTM_EXPORT(rt_hw_interrupt_is_disabled);
/**@}*/

