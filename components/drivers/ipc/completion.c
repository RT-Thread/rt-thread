/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-30     Bernard      first version.
 * 2021-08-18     chenyingchun add comments
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2024-01-25     Shell        reduce resource usage in completion for better synchronization
 *                             and smaller footprint.
 */

#define DBG_TAG           "drivers.ipc"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#include <rthw.h>
#include <rtdevice.h>

#define RT_COMPLETED    1
#define RT_UNCOMPLETED  0
#define RT_COMPLETION_FLAG(comp) ((comp)->susp_thread_n_flag & 1)
#define RT_COMPLETION_THREAD(comp) ((rt_thread_t)((comp)->susp_thread_n_flag & ~1))
#define RT_COMPLETION_NEW_STAT(thread, flag) (((flag) & 1) | (((rt_base_t)thread) & ~1))

static struct rt_spinlock _completion_lock = RT_SPINLOCK_INIT;

/**
 * @brief This function will initialize a completion object.
 *
 * @param completion is a pointer to a completion object.
 */
void rt_completion_init(struct rt_completion *completion)
{
    RT_ASSERT(completion != RT_NULL);

    completion->susp_thread_n_flag = RT_COMPLETION_NEW_STAT(RT_NULL, RT_UNCOMPLETED);
}
RTM_EXPORT(rt_completion_init);

/**
 * @brief This function will wait for a completion, if the completion is unavailable, the thread shall wait for
 *        the completion up to a specified time.
 *
 * @param completion is a pointer to a completion object.
 *
 * @param timeout is a timeout period (unit: OS ticks). If the completion is unavailable, the thread will wait for
 *                the completion done up to the amount of time specified by the argument.
 *                NOTE: Generally, we use the macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *                completion is unavailable, the thread will be waitting forever.
 *
 * @return Return the operation status. ONLY when the return value is RT_EOK, the operation is successful.
 *         If the return value is any other values, it means that the completion wait failed.
 *
 * @warning This function can ONLY be called in the thread context. It MUST NOT be called in interrupt context.
 */
rt_err_t rt_completion_wait(struct rt_completion *completion,
                            rt_int32_t            timeout)
{
    rt_err_t result;
    rt_base_t level;
    rt_thread_t thread;
    RT_ASSERT(completion != RT_NULL);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    result = RT_EOK;
    thread = rt_thread_self();

    level = rt_spin_lock_irqsave(&_completion_lock);
    if (RT_COMPLETION_FLAG(completion) != RT_COMPLETED)
    {
        /* only one thread can suspend on complete */
        RT_ASSERT(RT_COMPLETION_THREAD(completion) == RT_NULL);

        if (timeout == 0)
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }
        else
        {
            /* reset thread error number */
            thread->error = RT_EOK;

            /* suspend thread */
            result = rt_thread_suspend_with_flag(thread, RT_UNINTERRUPTIBLE);
            if (result == RT_EOK)
            {
                /* add to suspended thread */
                completion->susp_thread_n_flag = RT_COMPLETION_NEW_STAT(thread, RT_UNCOMPLETED);

                /* current context checking */
                RT_DEBUG_NOT_IN_INTERRUPT;

                /* start timer */
                if (timeout > 0)
                {
                    /* reset the timeout of thread timer and start it */
                    rt_timer_control(&(thread->thread_timer),
                                     RT_TIMER_CTRL_SET_TIME,
                                     &timeout);
                    rt_timer_start(&(thread->thread_timer));
                }
                /* enable interrupt */
                rt_spin_unlock_irqrestore(&_completion_lock, level);

                /* do schedule */
                rt_schedule();

                /* thread is waked up */
                result = thread->error;

                level = rt_spin_lock_irqsave(&_completion_lock);
            }
        }
    }

    /* clean completed flag & remove susp_thread on the case of waking by timeout */
    completion->susp_thread_n_flag = RT_COMPLETION_NEW_STAT(RT_NULL, RT_UNCOMPLETED);

__exit:
    rt_spin_unlock_irqrestore(&_completion_lock, level);

    return result;
}
RTM_EXPORT(rt_completion_wait);

/**
 * @brief This function indicates a completion has done.
 *
 * @param completion is a pointer to a completion object.
 */
static int _completion_done(struct rt_completion *completion)
{
    rt_base_t level;
    rt_err_t error;
    rt_thread_t suspend_thread;
    RT_ASSERT(completion != RT_NULL);

    level = rt_spin_lock_irqsave(&_completion_lock);
    if (RT_COMPLETION_FLAG(completion) == RT_COMPLETED)
    {
        rt_spin_unlock_irqrestore(&_completion_lock, level);
        return -RT_EBUSY;
    }

    suspend_thread = RT_COMPLETION_THREAD(completion);
    if (suspend_thread)
    {
        /* there is one thread in suspended list */

        /* resume it */
        error = rt_thread_resume(suspend_thread);
        if (error)
        {
            LOG_D("%s: failed to resume thread", __func__);
        }
    }
    else
    {
        /* no thread waiting */
        error = -RT_EEMPTY;
    }

    completion->susp_thread_n_flag = RT_COMPLETION_NEW_STAT(RT_NULL, RT_COMPLETED);

    rt_spin_unlock_irqrestore(&_completion_lock, level);

    return error;
}

/**
 * @brief This function indicates a completion has done.
 *
 * @param completion is a pointer to a completion object.
 */
void rt_completion_done(struct rt_completion *completion)
{
    _completion_done(completion);
}
RTM_EXPORT(rt_completion_done);

/**
 * @brief This function indicates a completion has done and wakeup the thread
 *
 * @param completion is a pointer to a completion object.
 */
rt_err_t rt_completion_wakeup(struct rt_completion *completion)
{
    return _completion_done(completion);
}
RTM_EXPORT(rt_completion_wakeup);

