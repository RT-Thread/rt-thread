/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-26     Shell        lockless rt_completion for MP system
 */

#define DBG_TAG           "drivers.ipc"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#define RT_COMPLETED        1
#define RT_UNCOMPLETED      0
#define RT_WAKING           (-1)
#define RT_OCCUPIED         (-2)

#define RT_COMPLETION_NEW_STAT(thread, flag) (((flag) & 1) | (((rt_base_t)thread) & ~1))

/**
 * The C11 atomic can be ~5% and even faster in testing on the arm64 platform
 * compared to rt_atomic. So the C11 way is always preferred.
 */
#ifdef RT_USING_STDC_ATOMIC
#include <stdatomic.h>

#define IPC_STORE(dst, val, morder) atomic_store_explicit(dst, val, morder)
#define IPC_LOAD(dst, morder)       atomic_load_explicit(dst, morder)
#define IPC_BARRIER(morder)         atomic_thread_fence(morder)
#define IPC_CAS(dst, exp, desired, succ, fail) \
    atomic_compare_exchange_strong_explicit(dst, exp, desired, succ, fail)

#else /* !RT_USING_STDC_ATOMIC */
#include <rtatomic.h>

#define IPC_STORE(dst, val, morder) rt_atomic_store(dst, val)
#define IPC_LOAD(dst, morder)       rt_atomic_load(dst)
#define IPC_BARRIER(morder)
#define IPC_CAS(dst, exp, desired, succ, fail) \
    rt_atomic_compare_exchange_strong(dst, exp, desired)
#endif /* RT_USING_STDC_ATOMIC */

static rt_err_t _comp_susp_thread(struct rt_completion *completion,
                                  rt_thread_t thread, rt_int32_t timeout,
                                  int suspend_flag);

/**
 * @brief This function will initialize a completion object.
 *
 * @param completion is a pointer to a completion object.
 */
void rt_completion_init(struct rt_completion *completion)
{
    RT_ASSERT(completion != RT_NULL);

    IPC_STORE(&completion->susp_thread_n_flag, RT_UNCOMPLETED,
              memory_order_relaxed);
}
RTM_EXPORT(rt_completion_init);

/**
 * @brief This is same as rt_completion_wait_flags(), except that this API is NOT
 *        ISR-safe (you can NOT call completion_done() on isr routine).
 *
 * @param completion is a pointer to a completion object.
 * @param timeout is a timeout period (unit: OS ticks). If the completion is unavailable, the thread will wait for
 *                the completion done up to the amount of time specified by the argument.
 *                NOTE: Generally, we use the macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *                completion is unavailable, the thread will be waitting forever.
 * @param suspend_flag suspend flags. See rt_thread_suspend_with_flag()
 *
 * @return Return the operation status. ONLY when the return value is RT_EOK, the operation is successful.
 *         If the return value is any other values, it means that the completion wait failed.
 *
 * @warning This function can ONLY be called in the thread context. It MUST NOT be called in interrupt context.
 */
rt_err_t rt_completion_wait_flags_noisr(struct rt_completion *completion,
                                        rt_int32_t timeout, int suspend_flag)
{
    rt_err_t result = -RT_ERROR;
    rt_thread_t thread;
    rt_bool_t exchange_succ;
    rt_base_t expected_value;
    RT_ASSERT(completion != RT_NULL);

    /* current context checking */
    RT_DEBUG_SCHEDULER_AVAILABLE(timeout != 0);

    thread = rt_thread_self();

    do
    {
        /* try to consume one completion */
        expected_value = RT_COMPLETED;
        exchange_succ =
            IPC_CAS(&completion->susp_thread_n_flag, &expected_value,
                    RT_UNCOMPLETED, memory_order_acquire, memory_order_relaxed);

        if (exchange_succ)
        {
            /* consume succeed, now return EOK */
            result = RT_EOK;
            break;
        }
        else if (expected_value == RT_WAKING)
        {
            /* previous wake is not done yet, yield thread & try again */
            rt_thread_yield();
        }
        else
        {
            /**
             * API rules say: only one thread can suspend on complete.
             * So we assert if debug.
             */
            RT_ASSERT(expected_value == RT_UNCOMPLETED);

            if (timeout != 0)
            {
                /**
                 * try to occupy completion, noted that we are assuming that
                 * `expected_value == RT_UNCOMPLETED`
                 */
                exchange_succ = IPC_CAS(
                    &completion->susp_thread_n_flag, &expected_value,
                    RT_OCCUPIED, memory_order_relaxed, memory_order_relaxed);

                if (exchange_succ)
                {
                    /* complete waiting business and return result */
                    result = _comp_susp_thread(completion, thread, timeout,
                                               suspend_flag);

                    RT_ASSERT(rt_atomic_load(&completion->susp_thread_n_flag) !=
                              RT_OCCUPIED);

                    break;
                }
                else
                {
                    /* try again */
                }
            }
            else
            {
                result = -RT_ETIMEOUT;
                break;
            }
        }
    } while (1);

    return result;
}

/**
 * @brief This function will wait for a completion, if the completion is unavailable, the thread shall wait for
 *        the completion up to a specified time.
 *
 * @param completion is a pointer to a completion object.
 * @param timeout is a timeout period (unit: OS ticks). If the completion is unavailable, the thread will wait for
 *                the completion done up to the amount of time specified by the argument.
 *                NOTE: Generally, we use the macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *                completion is unavailable, the thread will be waitting forever.
 * @param suspend_flag suspend flags. See rt_thread_suspend_with_flag()
 *
 * @return Return the operation status. ONLY when the return value is RT_EOK, the operation is successful.
 *         If the return value is any other values, it means that the completion wait failed.
 *
 * @warning This function can ONLY be called in the thread context. It MUST NOT be called in interrupt context.
 */
rt_err_t rt_completion_wait_flags(struct rt_completion *completion,
                                  rt_int32_t timeout, int suspend_flag)
{
    rt_err_t error;
    rt_ubase_t level;
    level = rt_hw_local_irq_disable();
    error = rt_completion_wait_flags_noisr(completion, timeout, suspend_flag);
    rt_hw_local_irq_enable(level);
    return error;
}

static rt_base_t _wait_until_update(struct rt_completion *completion, rt_base_t expected)
{
    rt_base_t current_value;

    /* spinning for update */
    do
    {
        rt_hw_isb();
        current_value =
            IPC_LOAD(&completion->susp_thread_n_flag, memory_order_relaxed);
    } while (current_value == expected);

    return current_value;
}

/**
 * Try to suspend thread and update completion
 */
static rt_err_t _comp_susp_thread(struct rt_completion *completion,
                                  rt_thread_t thread, rt_int32_t timeout,
                                  int suspend_flag)
{
    rt_err_t error = -RT_ERROR;
    rt_base_t clevel;
    rt_base_t comp_waiting;

    /* suspend thread */
    clevel = rt_enter_critical();

    /* reset thread error number */
    thread->error = RT_EOK;

    error = rt_thread_suspend_with_flag(thread, suspend_flag);

    if (error)
    {
        rt_exit_critical_safe(clevel);
        RT_ASSERT(rt_atomic_load(&completion->susp_thread_n_flag) ==
                  RT_OCCUPIED);
        IPC_STORE(&completion->susp_thread_n_flag, RT_UNCOMPLETED,
                  memory_order_relaxed);
    }
    else
    {
        /* set to waiting */
        comp_waiting = RT_COMPLETION_NEW_STAT(thread, RT_UNCOMPLETED);
        RT_ASSERT(rt_atomic_load(&completion->susp_thread_n_flag) ==
                  RT_OCCUPIED);
        IPC_STORE(&completion->susp_thread_n_flag, comp_waiting,
                  memory_order_relaxed);

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

        /* do schedule */
        rt_schedule();

        rt_exit_critical_safe(clevel);

        /* thread is woken up */
        error = thread->error;
        error = error > 0 ? -error : error;

        /* clean completed flag & remove susp_thread on the case of waking by timeout */
        if (!error)
        {
            /* completion done successfully */
            RT_ASSERT(rt_atomic_load(&completion->susp_thread_n_flag) !=
                      comp_waiting);

            /* the necessary barrier is done during thread sched */
        }
        else
        {
            /* try to cancel waiting if woken up expectedly or timeout */
            if (!IPC_CAS(&completion->susp_thread_n_flag, &comp_waiting,
                         RT_UNCOMPLETED, memory_order_relaxed,
                         memory_order_relaxed))
            {
                /* cancel failed, producer had woken us in the past, fix error */
                if (comp_waiting == RT_WAKING)
                {
                    _wait_until_update(completion, RT_WAKING);
                }
                IPC_BARRIER(memory_order_acquire);
                error = RT_EOK;
            }
        }
    }

    return error;
}

/**
 * @brief   This function indicates a completion has done and wakeup the thread
 *          and update its errno. No update is applied if it's a negative value.
 *
 * @param   completion is a pointer to a completion object.
 * @param   thread_errno is the errno set to waking thread.
 * @return  RT_EOK if wakeup succeed.
 *          RT_EEMPTY if wakeup failure and the completion is set to completed.
 *          RT_EBUSY if the completion is still in completed state
 */
rt_err_t rt_completion_wakeup_by_errno(struct rt_completion *completion,
                                       rt_err_t thread_errno)
{
    rt_err_t error = -RT_ERROR;
    rt_thread_t suspend_thread;
    rt_bool_t exchange_succ;
    rt_base_t expected_value;
    RT_ASSERT(completion != RT_NULL);

    do
    {
        /* try to transform from uncompleted to completed */
        expected_value = RT_UNCOMPLETED;

        exchange_succ =
            IPC_CAS(&completion->susp_thread_n_flag, &expected_value,
                    RT_COMPLETED, memory_order_release, memory_order_relaxed);

        if (exchange_succ)
        {
            error = -RT_EEMPTY;
            break;
        }
        else
        {
            if (expected_value == RT_COMPLETED)
            {
                /* completion still in completed state */
                error = -RT_EBUSY;
                break;
            }
            else if (expected_value == RT_OCCUPIED ||
                     expected_value == RT_WAKING)
            {
                continue;
            }
            else
            {
                /* try to resume the thread and set uncompleted */
                exchange_succ = IPC_CAS(
                    &completion->susp_thread_n_flag, &expected_value,
                    RT_WAKING, memory_order_relaxed, memory_order_relaxed);

                if (exchange_succ)
                {
                    #define GET_THREAD(val) ((rt_thread_t)((val) & ~1))
                    suspend_thread = GET_THREAD(expected_value);

                    if (thread_errno >= 0)
                    {
                        suspend_thread->error = thread_errno;
                    }

                    /* safe to assume publication done even on resume failure */
                    RT_ASSERT(rt_atomic_load(&completion->susp_thread_n_flag) ==
                              RT_WAKING);
                    IPC_STORE(&completion->susp_thread_n_flag, RT_UNCOMPLETED,
                              memory_order_release);
                    rt_thread_resume(suspend_thread);
                    error = RT_EOK;
                    break;
                }
                else
                {
                    /* failed in racing to resume thread, try again */
                }
            }
        }
    } while (1);

    return error;
}
