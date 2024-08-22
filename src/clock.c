/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-12     Bernard      first version
 * 2006-05-27     Bernard      add support for same priority thread schedule
 * 2006-08-10     Bernard      remove the last rt_schedule in rt_tick_increase
 * 2010-03-08     Bernard      remove rt_passed_second
 * 2010-05-20     Bernard      fix the tick exceeds the maximum limits
 * 2010-07-13     Bernard      fix rt_tick_from_millisecond issue found by kuronca
 * 2011-06-26     Bernard      add rt_tick_set function.
 * 2018-11-22     Jesven       add per cpu tick
 * 2020-12-29     Meco Man     implement rt_tick_get_millisecond()
 * 2021-06-01     Meco Man     add critical section projection for rt_tick_increase()
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2023-10-16     RiceChen     fix: only the main core detection rt_timer_check(), in SMP mode
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtatomic.h>

#if defined(RT_USING_SMART) && defined(RT_USING_VDSO)
#include <vdso.h>
#endif

#ifdef RT_USING_SMP
#define rt_tick rt_cpu_index(0)->tick
#else
static volatile rt_atomic_t rt_tick = 0;
#endif /* RT_USING_SMP */

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
static void (*rt_tick_hook)(void);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * @brief This function will set a hook function, which will be invoked when tick increase
 *
 *
 * @param hook the hook function
 */
void rt_tick_sethook(void (*hook)(void))
{
    rt_tick_hook = hook;
}
/**@}*/
#endif /* RT_USING_HOOK */

/**
 * @addtogroup Clock
 */

/**@{*/

/**
 * @brief    This function will return current tick from operating system startup.
 *
 * @return   Return current tick.
 */
rt_tick_t rt_tick_get(void)
{
    /* return the global tick */
    return (rt_tick_t)rt_atomic_load(&(rt_tick));
}
RTM_EXPORT(rt_tick_get);

/**
 * @brief    This function will set current tick.
 *
 * @param    tick is the value that you will set.
 */
void rt_tick_set(rt_tick_t tick)
{
    rt_atomic_store(&(rt_tick), tick);
}

#ifdef RT_USING_CPU_USAGE_TRACER
static void _update_process_times(rt_tick_t tick)
{
    struct rt_thread *thread = rt_thread_self();
    struct rt_cpu *pcpu = rt_cpu_self();

    if (!LWP_IS_USER_MODE(thread))
    {
        thread->user_time += tick;
        pcpu->cpu_stat.user += tick;
    }
    else
    {
        thread->system_time += tick;
        if (thread == pcpu->idle_thread)
        {
            pcpu->cpu_stat.idle += tick;
        }
        else
        {
            pcpu->cpu_stat.system += tick;
        }
    }
}

#else

#define _update_process_times(tick)
#endif /* RT_USING_CPU_USAGE_TRACER */

/**
 * @brief    This function will notify kernel there is one tick passed.
 *           Normally, this function is invoked by clock ISR.
 */
void rt_tick_increase(void)
{
    RT_ASSERT(rt_interrupt_get_nest() > 0);

    RT_OBJECT_HOOK_CALL(rt_tick_hook, ());

    /* tracing cpu usage */
    _update_process_times(1);

    /* increase the global tick */
#ifdef RT_USING_SMP
    /* get percpu and increase the tick */
    rt_atomic_add(&(rt_cpu_self()->tick), 1);
#else
    rt_atomic_add(&(rt_tick), 1);
#endif /* RT_USING_SMP */

    /* check time slice */
    rt_sched_tick_increase(1);

    /* check timer */
#ifdef RT_USING_SMP
    if (rt_cpu_get_id() != 0)
    {
        return;
    }
#endif
    rt_timer_check();
}

/**
 * @brief    This function will notify kernel there is n tick passed.
 *           Normally, this function is invoked by clock ISR.
 */
void rt_tick_increase_tick(rt_tick_t tick)
{
    RT_ASSERT(rt_interrupt_get_nest() > 0);

    RT_OBJECT_HOOK_CALL(rt_tick_hook, ());

    /* tracing cpu usage */
    _update_process_times(tick);

    /* increase the global tick */
#ifdef RT_USING_SMP
    /* get percpu and increase the tick */
    rt_atomic_add(&(rt_cpu_self()->tick), tick);
#else
    rt_atomic_add(&(rt_tick), tick);
#endif /* RT_USING_SMP */

    /* check time slice */
    rt_sched_tick_increase(tick);

    /* check timer */
#ifdef RT_USING_SMP
    if (rt_cpu_get_id() != 0)
    {
        return;
    }
#endif
    rt_timer_check();

#ifdef RT_USING_VDSO
    rt_vdso_update_glob_time();
#endif
}

/**
 * @brief    This function will calculate the tick from millisecond.
 *
 * @param    ms is the specified millisecond.
 *              - Negative Number wait forever
 *              - Zero not wait
 *              - Max 0x7fffffff
 *
 * @return   Return the calculated tick.
 */
rt_tick_t rt_tick_from_millisecond(rt_int32_t ms)
{
    rt_tick_t tick;

    if (ms < 0)
    {
        tick = (rt_tick_t)RT_WAITING_FOREVER;
    }
    else
    {
        tick = RT_TICK_PER_SECOND * (ms / 1000);
        tick += (RT_TICK_PER_SECOND * (ms % 1000) + 999) / 1000;
    }

    /* return the calculated tick */
    return tick;
}
RTM_EXPORT(rt_tick_from_millisecond);

/**
 * @brief    This function will return the passed millisecond from boot.
 *
 * @note     if the value of RT_TICK_PER_SECOND is lower than 1000 or
 *           is not an integral multiple of 1000, this function will not
 *           provide the correct 1ms-based tick.
 *
 * @return   Return passed millisecond from boot.
 */
rt_weak rt_tick_t rt_tick_get_millisecond(void)
{
#if RT_TICK_PER_SECOND == 0 /* make cppcheck happy*/
#error "RT_TICK_PER_SECOND must be greater than zero"
#endif

#if 1000 % RT_TICK_PER_SECOND == 0u
    return rt_tick_get() * (1000u / RT_TICK_PER_SECOND);
#else
    #warning "rt-thread cannot provide a correct 1ms-based tick any longer,\
    please redefine this function in another file by using a high-precision hard-timer."
    return 0;
#endif /* 1000 % RT_TICK_PER_SECOND == 0u */
}

/**@}*/
