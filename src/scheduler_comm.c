/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * (scheduler_comm.c) Common API of scheduling routines.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-18     Shell        Separate scheduling related codes from thread.c, scheduler_.*
 */

#define DBG_TAG           "kernel.sched"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#include <rtthread.h>

void rt_sched_thread_init_ctx(struct rt_thread *thread, rt_uint32_t tick, rt_uint8_t priority)
{
    /* setup thread status */
    RT_SCHED_CTX(thread).stat  = RT_THREAD_INIT;

#ifdef RT_USING_SMP
    /* not bind on any cpu */
    RT_SCHED_CTX(thread).bind_cpu = RT_CPUS_NR;
    RT_SCHED_CTX(thread).oncpu = RT_CPU_DETACHED;
#endif /* RT_USING_SMP */

    rt_sched_thread_init_priv(thread, tick, priority);
}

rt_err_t rt_sched_thread_timer_start(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    RT_SCHED_CTX(thread).sched_flag_ttmr_set = 1;
    return RT_EOK;
}

rt_err_t rt_sched_thread_timer_stop(struct rt_thread *thread)
{
    rt_err_t error;
    RT_SCHED_DEBUG_IS_LOCKED;

    if (RT_SCHED_CTX(thread).sched_flag_ttmr_set)
    {
        error = rt_timer_stop(&thread->thread_timer);

        /* mask out timer flag no matter stop success or not */
        RT_SCHED_CTX(thread).sched_flag_ttmr_set = 0;
    }
    else
    {
        error = RT_EOK;
    }
    return error;
}

rt_uint8_t rt_sched_thread_get_stat(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    return RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK;
}

rt_uint8_t rt_sched_thread_get_curr_prio(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    return RT_SCHED_PRIV(thread).current_priority;
}

rt_uint8_t rt_sched_thread_get_init_prio(struct rt_thread *thread)
{
    /* read only fields, so lock is unecessary */
    return RT_SCHED_PRIV(thread).init_priority;
}

/**
 * @note Caller must hold the scheduler lock
 */
rt_uint8_t rt_sched_thread_is_suspended(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    return (RT_SCHED_CTX(thread).stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK;
}

rt_err_t rt_sched_thread_close(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    RT_SCHED_CTX(thread).stat = RT_THREAD_CLOSE;
    return RT_EOK;
}

rt_err_t rt_sched_thread_yield(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;

    RT_SCHED_PRIV(thread).remaining_tick = RT_SCHED_PRIV(thread).init_tick;
    RT_SCHED_CTX(thread).stat |= RT_THREAD_STAT_YIELD;

    return RT_EOK;
}

rt_err_t rt_sched_thread_ready(struct rt_thread *thread)
{
    rt_err_t error;

    RT_SCHED_DEBUG_IS_LOCKED;

    if (!rt_sched_thread_is_suspended(thread))
    {
        /* failed to proceed, and that's possibly due to a racing condition */
        error = -RT_EINVAL;
    }
    else
    {
        if (RT_SCHED_CTX(thread).sched_flag_ttmr_set)
        {
            /**
             * Quiet timeout timer first if set. and don't continue if we
             * failed, because it probably means that a timeout ISR racing to
             * resume thread before us.
             */
            error = rt_sched_thread_timer_stop(thread);
        }
        else
        {
            error = RT_EOK;
        }

        if (!error)
        {
            /* remove from suspend list */
            rt_list_remove(&RT_THREAD_LIST_NODE(thread));

        #ifdef RT_USING_SMART
            thread->wakeup_handle.func = RT_NULL;
        #endif

            /* insert to schedule ready list and remove from susp list */
            rt_sched_insert_thread(thread);
        }
    }

    return error;
}

rt_err_t rt_sched_tick_increase(void)
{
    struct rt_thread *thread;
    rt_sched_lock_level_t slvl;

    thread = rt_thread_self();

    rt_sched_lock(&slvl);

    RT_SCHED_PRIV(thread).remaining_tick--;
    if (RT_SCHED_PRIV(thread).remaining_tick)
    {
        rt_sched_unlock(slvl);
    }
    else
    {
        rt_sched_thread_yield(thread);

        /* request a rescheduling even though we are probably in an ISR */
        rt_sched_unlock_n_resched(slvl);
    }

    return RT_EOK;
}

/**
 * @brief Update priority of the target thread
 */
rt_err_t rt_sched_thread_change_priority(struct rt_thread *thread, rt_uint8_t priority)
{
    RT_ASSERT(priority < RT_THREAD_PRIORITY_MAX);
    RT_SCHED_DEBUG_IS_LOCKED;

    /* for ready thread, change queue; otherwise simply update the priority */
    if ((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_READY)
    {
        /* remove thread from schedule queue first */
        rt_sched_remove_thread(thread);

        /* change thread priority */
        RT_SCHED_PRIV(thread).current_priority = priority;

        /* recalculate priority attribute */
#if RT_THREAD_PRIORITY_MAX > 32
        RT_SCHED_PRIV(thread).number = RT_SCHED_PRIV(thread).current_priority >> 3;               /* 5bit */
        RT_SCHED_PRIV(thread).number_mask = 1 << RT_SCHED_PRIV(thread).number;
        RT_SCHED_PRIV(thread).high_mask = 1 << (RT_SCHED_PRIV(thread).current_priority & 0x07);   /* 3bit */
#else
        RT_SCHED_PRIV(thread).number_mask = 1 << RT_SCHED_PRIV(thread).current_priority;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
        RT_SCHED_CTX(thread).stat = RT_THREAD_INIT;

        /* insert thread to schedule queue again */
        rt_sched_insert_thread(thread);
    }
    else
    {
        RT_SCHED_PRIV(thread).current_priority = priority;

        /* recalculate priority attribute */
#if RT_THREAD_PRIORITY_MAX > 32
        RT_SCHED_PRIV(thread).number = RT_SCHED_PRIV(thread).current_priority >> 3;               /* 5bit */
        RT_SCHED_PRIV(thread).number_mask = 1 << RT_SCHED_PRIV(thread).number;
        RT_SCHED_PRIV(thread).high_mask = 1 << (RT_SCHED_PRIV(thread).current_priority & 0x07);   /* 3bit */
#else
        RT_SCHED_PRIV(thread).number_mask = 1 << RT_SCHED_PRIV(thread).current_priority;
#endif /* RT_THREAD_PRIORITY_MAX > 32 */
    }

    return RT_EOK;
}

#ifdef RT_USING_OVERFLOW_CHECK
void rt_scheduler_stack_check(struct rt_thread *thread)
{
    RT_ASSERT(thread != RT_NULL);

#ifdef RT_USING_SMART
#ifndef ARCH_MM_MMU
    struct rt_lwp *lwp = thread ? (struct rt_lwp *)thread->lwp : 0;

    /* if stack pointer locate in user data section skip stack check. */
    if (lwp && ((rt_uint32_t)thread->sp > (rt_uint32_t)lwp->data_entry &&
    (rt_uint32_t)thread->sp <= (rt_uint32_t)lwp->data_entry + (rt_uint32_t)lwp->data_size))
    {
        return;
    }
#endif /* not defined ARCH_MM_MMU */
#endif /* RT_USING_SMART */

#ifndef RT_USING_HW_STACK_GUARD
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
    if (*((rt_uint8_t *)((rt_ubase_t)thread->stack_addr + thread->stack_size - 1)) != '#' ||
#else
    if (*((rt_uint8_t *)thread->stack_addr) != '#' ||
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */
        (rt_ubase_t)thread->sp <= (rt_ubase_t)thread->stack_addr ||
        (rt_ubase_t)thread->sp >
        (rt_ubase_t)thread->stack_addr + (rt_ubase_t)thread->stack_size)
    {
        rt_base_t dummy = 1;

        LOG_E("thread:%s stack overflow\n", thread->parent.name);

        while (dummy);
    }
#endif /* RT_USING_HW_STACK_GUARD */
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
#ifndef RT_USING_HW_STACK_GUARD
    else if ((rt_ubase_t)thread->sp > ((rt_ubase_t)thread->stack_addr + thread->stack_size))
#else
    if ((rt_ubase_t)thread->sp > ((rt_ubase_t)thread->stack_addr + thread->stack_size))
#endif
    {
        LOG_W("warning: %s stack is close to the top of stack address.\n",
                   thread->parent.name);
    }
#else
#ifndef RT_USING_HW_STACK_GUARD
    else if ((rt_ubase_t)thread->sp <= ((rt_ubase_t)thread->stack_addr + 32))
#else
    if ((rt_ubase_t)thread->sp <= ((rt_ubase_t)thread->stack_addr + 32))
#endif
    {
        LOG_W("warning: %s stack is close to end of stack address.\n",
                   thread->parent.name);
    }
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */
}

#endif /* RT_USING_OVERFLOW_CHECK */
