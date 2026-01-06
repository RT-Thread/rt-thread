/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * (scheduler_comm.c) Common API of scheduling routines.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-18     Shell        Separate scheduling related codes from thread.c, scheduler_.*
 * 2025-09-01     Rbb666       Add thread stack overflow hook.
 */

#define DBG_TAG           "kernel.sched"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#include <rtthread.h>

/**
 * @brief Initialize thread scheduling context
 *
 * @param thread The thread to be initialized
 * @param tick Initial time slice value for the thread
 * @param priority Initial priority of the thread
 *
 * @details This function performs the following initialization:
 *   - Sets thread status to INIT
 *   - For SMP systems:
 *     * Sets bind CPU to none (RT_CPUS_NR)
 *     * Marks CPU as detached (RT_CPU_DETACHED)
 *   - Calls rt_sched_thread_init_priv() for private scheduling data initialization
 */
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

/**
 * @brief Start the thread timer for scheduling
 *
 * @param thread The thread whose timer needs to be started
 *
 * @return rt_err_t Always returns RT_EOK on success
 *
 * @details This function:
 *   - Requires scheduler lock to be held.
 *   - Sets the thread's timer flag (sched_flag_ttmr_set) to indicate timer is active
 */
rt_err_t rt_sched_thread_timer_start(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    RT_SCHED_CTX(thread).sched_flag_ttmr_set = 1;
    return RT_EOK;
}

/**
 * @brief Stop the thread timer for scheduling
 *
 * @param thread The thread whose timer needs to be stopped
 *
 * @return rt_err_t
 *   - RT_EOK if timer was successfully stopped or not active
 *   - Other error codes from rt_timer_stop() if stop operation failed
 */
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

/**
 * @brief Get the current status of a thread
 *
 * @param thread The thread to get status from
 *
 * @return rt_uint8_t The thread status masked with RT_THREAD_STAT_MASK
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - Returns the thread's status field masked with RT_THREAD_STAT_MASK
 */
rt_uint8_t rt_sched_thread_get_stat(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    return RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK;
}

/**
 * @brief Get the current priority of a thread
 *
 * @param thread The thread to get priority from
 *
 * @return rt_uint8_t The current priority value of the thread
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - Returns the thread's current priority field from its private scheduling data
 */
rt_uint8_t rt_sched_thread_get_curr_prio(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    return RT_SCHED_PRIV(thread).current_priority;
}

/**
 * @brief Get the initial priority of a thread
 *
 * @param thread The thread to get priority from
 *
 * @return rt_uint8_t The initial priority value of the thread
 *
 * @details This function:
 *   - Returns the thread's initial priority field from its private scheduling data
 *   - Does not require scheduler lock as it accesses read-only fields
 */
rt_uint8_t rt_sched_thread_get_init_prio(struct rt_thread *thread)
{
    /* read only fields, so lock is unnecessary */
    return RT_SCHED_PRIV(thread).init_priority;
}

/**
 * @brief Check if a thread is in suspended state
 *
 * @param thread The thread to check
 *
 * @return rt_uint8_t
 *   - 1 if thread is suspended (matches RT_THREAD_SUSPEND_MASK)
 *   - 0 otherwise
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - Checks thread's status field against RT_THREAD_SUSPEND_MASK
 *
 * @note Caller must hold the scheduler lock before calling this function
 */
rt_uint8_t rt_sched_thread_is_suspended(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    return (RT_SCHED_CTX(thread).stat & RT_THREAD_SUSPEND_MASK) == RT_THREAD_SUSPEND_MASK;
}

/**
 * @brief Close a thread by setting its status to CLOSED
 *
 * @param thread The thread to be closed
 * @return rt_err_t Always returns RT_EOK on success
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - Sets the thread's status to RT_THREAD_CLOSE
 *
 * @note Must be called with scheduler lock held
 */
rt_err_t rt_sched_thread_close(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;
    RT_SCHED_CTX(thread).stat = RT_THREAD_CLOSE;
    return RT_EOK;
}

/**
 * @brief Yield the current thread's remaining time slice
 *
 * @param thread The thread to yield
 * @return rt_err_t Always returns RT_EOK on success
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - Resets the thread's remaining tick count to its initial value
 *   - Sets the thread's status to YIELD state
 *
 * @note Must be called with scheduler lock held
 */
rt_err_t rt_sched_thread_yield(struct rt_thread *thread)
{
    RT_SCHED_DEBUG_IS_LOCKED;

    RT_SCHED_PRIV(thread).remaining_tick = RT_SCHED_PRIV(thread).init_tick;
    RT_SCHED_CTX(thread).stat |= RT_THREAD_STAT_YIELD;

    return RT_EOK;
}

/**
 * @brief Make a suspended thread ready for scheduling
 *
 * @param thread The thread to be made ready
 *
 * @return rt_err_t
 *   - RT_EOK if operation succeeded
 *   - -RT_EINVAL if thread is not suspended
 *   - Other error codes from rt_sched_thread_timer_stop() if timer stop failed
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - Checks if thread is suspended (returns -RT_EINVAL if not)
 *   - Stops thread timer if active
 *   - Removes thread from suspend list
 *   - Clears wakeup handler (if RT_USING_SMART is defined)
 *   - Inserts thread into ready queue
 *
 * @note Must be called with scheduler lock held
 *       May fail due to racing conditions with timeout ISR
 */
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

/**
 * @brief Increase the system tick and update thread's remaining time slice
 *
 * @param tick The number of ticks to increase
 * @return rt_err_t Always returns RT_EOK
 *
 * @details This function:
 *   - Gets the current thread
 *   - Locks the scheduler
 *   - Decreases the thread's remaining tick count by the specified amount
 *   - If remaining ticks reach zero:
 *     * Calls rt_sched_thread_yield() to yield the thread
 *     * Requests a reschedule with rt_sched_unlock_n_resched()
 *   - Otherwise simply unlocks the scheduler
 *
 * @note This function is typically called from timer interrupt context
 *       It handles both SMP and non-SMP cases
 */
rt_err_t rt_sched_tick_increase(rt_tick_t tick)
{
    struct rt_thread *thread;
    rt_sched_lock_level_t slvl;

    thread = rt_thread_self();

    rt_sched_lock(&slvl);

    if(RT_SCHED_PRIV(thread).remaining_tick > tick)
    {
        RT_SCHED_PRIV(thread).remaining_tick -= tick;
    }
    else
    {
        RT_SCHED_PRIV(thread).remaining_tick = 0;
    }

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
 * @brief Update thread priority and adjust scheduling attributes
 *
 * @param thread The thread to update priority for
 * @param priority New priority value to set
 * @param update_init_prio Flag to determine if initial priority should also be updated
 * @return rt_err_t Always returns RT_EOK on success
 *
 * @details This function:
 *   - Requires scheduler lock to be held (RT_SCHED_DEBUG_IS_LOCKED)
 *   - For ready threads:
 *     * Removes from ready queue
 *     * Updates priority values
 *     * Recalculates priority attributes (number, mask, etc.)
 *     * Reinserts into ready queue with new priority
 *   - For non-ready threads:
 *     * Only updates priority values and attributes
 *   - Handles both 32-bit and >32-bit priority systems
 *
 * @note Must be called with scheduler lock held
 *       Thread status must be valid before calling
 */
static rt_err_t _rt_sched_update_priority(struct rt_thread *thread, rt_uint8_t priority, rt_bool_t update_init_prio)
{
    RT_ASSERT(priority < RT_THREAD_PRIORITY_MAX);
    RT_SCHED_DEBUG_IS_LOCKED;

    /* for ready thread, change queue; otherwise simply update the priority */
    if ((RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK) == RT_THREAD_READY)
    {
        /* remove thread from schedule queue first */
        rt_sched_remove_thread(thread);

        /* change thread priority */
        if (update_init_prio)
        {
            RT_SCHED_PRIV(thread).init_priority = priority;
        }
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
        if (update_init_prio)
        {
            RT_SCHED_PRIV(thread).init_priority = priority;
        }
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

/**
 * @brief Update priority of the target thread
 */
rt_err_t rt_sched_thread_change_priority(struct rt_thread *thread, rt_uint8_t priority)
{
    return _rt_sched_update_priority(thread, priority, RT_FALSE);
}

/**
 * @brief Reset priority of the target thread
 */
rt_err_t rt_sched_thread_reset_priority(struct rt_thread *thread, rt_uint8_t priority)
{
    return _rt_sched_update_priority(thread, priority, RT_TRUE);
}

#ifdef RT_USING_OVERFLOW_CHECK

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
static rt_err_t (*rt_stack_overflow_hook)(struct rt_thread *thread);

/**
 * @brief Set a hook function to be called when stack overflow is detected
 *
 * @param hook The function pointer to be called when stack overflow is detected.
 *             Pass RT_NULL to disable the hook.
 *             The hook function should return RT_EOK if overflow is handled,
 *             otherwise the system will halt in an infinite loop.
 *
 * @note The hook function must be simple and never be blocked or suspended.
 *       This function is typically used for error logging, recovery, or graceful shutdown.
 *
 * @details Hook function behavior:
 *   - Return RT_EOK: System continues execution after overflow handling
 *   - Return any other value: System enters infinite loop (halt)
 *   - Hook is called from rt_scheduler_stack_check() when overflow is detected
 *   - Hook execution context depends on when stack check is performed
 *
 * @see rt_scheduler_stack_check()
 */
void rt_scheduler_stack_overflow_sethook(rt_err_t (*hook)(struct rt_thread *thread))
{
    rt_stack_overflow_hook = hook;
}
#endif /* RT_USING_HOOK */

/**
 * @brief Check thread stack for overflow or near-overflow conditions
 *
 * @param thread The thread to check stack for
 *
 * @details This function performs the following checks:
 *   - For SMART mode without MMU: skips check if SP is in user data section
 *   - Without hardware stack guard:
 *     * For upward-growing stacks: checks magic number at top and SP range
 *     * For downward-growing stacks: checks magic number at bottom and SP range
 *     * Triggers error and infinite loop on overflow
 *   - Additional warnings when stack pointer is near boundaries
 */
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
    if (*((rt_uint8_t *)((rt_uintptr_t)thread->stack_addr + thread->stack_size - 1)) != '#' ||
#else
    if (*((rt_uint8_t *)thread->stack_addr) != '#' ||
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */
        (rt_uintptr_t)thread->sp <= (rt_uintptr_t)thread->stack_addr ||
        (rt_uintptr_t)thread->sp >
        (rt_uintptr_t)thread->stack_addr + (rt_uintptr_t)thread->stack_size)
    {
        rt_base_t dummy = 1;
        rt_err_t hook_result = -RT_ERROR;

        LOG_E("thread:%s stack overflow\n", thread->parent.name);

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
        if (rt_stack_overflow_hook != RT_NULL)
        {
            hook_result = rt_stack_overflow_hook(thread);
        }
#endif /* RT_USING_HOOK */

        /* If hook handled the overflow successfully, don't enter infinite loop */
        if (hook_result != RT_EOK)
        {
            while (dummy);
        }
    }
#endif /* RT_USING_HW_STACK_GUARD */
#ifdef ARCH_CPU_STACK_GROWS_UPWARD
#ifndef RT_USING_HW_STACK_GUARD
    else if ((rt_uintptr_t)thread->sp > ((rt_uintptr_t)thread->stack_addr + thread->stack_size))
#else
    if ((rt_uintptr_t)thread->sp > ((rt_uintptr_t)thread->stack_addr + thread->stack_size))
#endif
    {
        LOG_W("warning: %s stack is close to the top of stack address.\n",
                   thread->parent.name);
    }
#else
#ifndef RT_USING_HW_STACK_GUARD
    else if ((rt_uintptr_t)thread->sp <= ((rt_uintptr_t)thread->stack_addr + 32))
#else
    if ((rt_uintptr_t)thread->sp <= ((rt_uintptr_t)thread->stack_addr + 32))
#endif
    {
        LOG_W("warning: %s stack is close to end of stack address.\n",
                   thread->parent.name);
    }
#endif /* ARCH_CPU_STACK_GROWS_UPWARD */
}

#endif /* RT_USING_OVERFLOW_CHECK */