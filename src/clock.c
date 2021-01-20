/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
 * 2020-12-29     Meco Man     add function rt_tick_get_millisecond()
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_SMP
#define rt_tick rt_cpu_index(0)->tick
#else
static rt_tick_t rt_tick = 0;
#endif

/**
 * @addtogroup Clock
 */

/**@{*/

/**
 * This function will return current tick from operating system startup
 *
 * @return current tick
 */
rt_tick_t rt_tick_get(void)
{
    /* return the global tick */
    return rt_tick;
}
RTM_EXPORT(rt_tick_get);

/**
 * This function will set current tick
 */
void rt_tick_set(rt_tick_t tick)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    rt_tick = tick;
    rt_hw_interrupt_enable(level);
}

/**
 * This function will notify kernel there is one tick passed. Normally,
 * this function is invoked by clock ISR.
 */
void rt_tick_increase(void)
{
    struct rt_thread *thread;

    /* increase the global tick */
#ifdef RT_USING_SMP
    rt_cpu_self()->tick ++;
#else
    ++ rt_tick;
#endif

    /* check time slice */
    thread = rt_thread_self();

    -- thread->remaining_tick;
    if (thread->remaining_tick == 0)
    {
        /* change to initialized tick */
        thread->remaining_tick = thread->init_tick;

        thread->stat |= RT_THREAD_STAT_YIELD;

        rt_schedule();
    }

    /* check timer */
    rt_timer_check();
}

/**
 * This function will calculate the tick from millisecond.
 *
 * @param ms the specified millisecond
 *           - Negative Number wait forever
 *           - Zero not wait
 *           - Max 0x7fffffff
 *
 * @return the calculated tick
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
 * This function will provide the passed millisecond from boot.
 *
 * @return passed millisecond from boot
 */
RT_WEAK rt_tick_t rt_tick_get_millisecond(void)
{
#if 1000 % RT_TICK_PER_SECOND == 0u
    return rt_tick_get() * (1000u / RT_TICK_PER_SECOND);
#else
    #warning "rt-thread cannot provide a correct 1ms-based tick any longer,\
    please redefine this function in another file by using a high-precision hard-timer."
    return 0;
#endif
}

/**@}*/

