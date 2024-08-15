/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-26     Shell        lockless rt_completion
 */
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

/**
 * @brief This function indicates a completion has done.
 *
 * @param completion is a pointer to a completion object.
 */
void rt_completion_done(struct rt_completion *completion)
{
    rt_completion_wakeup_by_errno(completion, -1);
}
RTM_EXPORT(rt_completion_done);

/**
 * @brief   This function indicates a completion has done and wakeup the thread
 *
 * @param   completion is a pointer to a completion object.
 * @return  RT_EOK if wakeup succeed.
 *          RT_EEMPTY if wakeup failure and the completion is set to completed.
 *          RT_EBUSY if the completion is still in completed state
 */
rt_err_t rt_completion_wakeup(struct rt_completion *completion)
{
    return rt_completion_wakeup_by_errno(completion, -1);
}

/**
 * @brief This is same as rt_completion_wait(), except that this API is NOT
 *        ISR-safe (you can NOT call completion_done() on isr routine).
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
rt_err_t rt_completion_wait_noisr(struct rt_completion *completion,
                                  rt_int32_t            timeout)
{
    return rt_completion_wait_flags_noisr(completion, timeout, RT_UNINTERRUPTIBLE);
}

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
    return rt_completion_wait_flags(completion, timeout, RT_UNINTERRUPTIBLE);
}
RTM_EXPORT(rt_completion_wait);
