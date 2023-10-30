/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <sched.h>
/**
 * @brief   Yield the processor voluntarily.
 *
 * This function yields the processor to another thread or task, allowing
 * other threads to execute. It is used to implement cooperative multitasking.
 *
 * @return  Always returns 0 to indicate success.
 */
int sched_yield(void)
{
    rt_thread_yield();
    return 0;
}
RTM_EXPORT(sched_yield);

/**
 * @brief   Get the minimum priority for a specified scheduling policy.
 *
 * @param   policy is the scheduling policy (SCHED_FIFO or SCHED_RR).
 *
 * @return  The minimum priority value for the specified scheduling policy,
 *          or an error code (EINVAL) on failure.
 */
int sched_get_priority_min(int policy)
{
    if (policy != SCHED_FIFO && policy != SCHED_RR)
        return EINVAL;

    return 0;
}
RTM_EXPORT(sched_get_priority_min);

/**
 * @brief   Get the maximum priority for a specified scheduling policy.
 *
 * @param   policy is the scheduling policy (SCHED_FIFO or SCHED_RR).
 *
 * @return  The maximum priority value for the specified scheduling policy,
 *          or an error code (EINVAL) on failure.
 */
int sched_get_priority_max(int policy)
{
    if (policy != SCHED_FIFO && policy != SCHED_RR)
        return EINVAL;

    return RT_THREAD_PRIORITY_MAX - 1;
}
RTM_EXPORT(sched_get_priority_max);

/**
 * @brief   Set the scheduling policy for a process.
 *
 * @param   pid     is not used in this implementation.
 * @param   policy  is the scheduling policy to be set.
 *
 * @return  Always returns EOPNOTSUPP to indicate that setting the scheduling
 *          policy is not supported in this implementation.
 */
int sched_setscheduler(pid_t pid, int policy)
{
    return EOPNOTSUPP;
}
RTM_EXPORT(sched_setscheduler);

/**
 * @brief   Get the time quantum for the round-robin scheduling policy.
 *
 * @param   pid is not used in this implementation.
 * @param   tp  is a pointer to a struct timespec to store the time quantum.
 *
 * @return  -1 to indicate an unsupported feature in this implementation.
 */
int sched_rr_get_interval(pid_t pid, struct timespec *tp)
{
    if (pid != 0)
        return EINVAL;

    rt_set_errno(-EINVAL);

    /* Coarse model, don't support */
    // TODO
    return -1;
}
RTM_EXPORT(sched_rr_get_interval);
