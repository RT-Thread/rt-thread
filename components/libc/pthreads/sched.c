/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <sched.h>

int sched_yield(void)
{
    rt_thread_yield();

    return 0;
}
RTM_EXPORT(sched_yield);

int sched_get_priority_min(int policy)
{
    if (policy != SCHED_FIFO && policy != SCHED_RR)
        return EINVAL;

    return 0;
}
RTM_EXPORT(sched_get_priority_min);

int sched_get_priority_max(int policy)
{
    if (policy != SCHED_FIFO && policy != SCHED_RR)
        return EINVAL;

    return RT_THREAD_PRIORITY_MAX - 1;
}
RTM_EXPORT(sched_get_priority_max);

int sched_setscheduler(pid_t pid, int policy)
{
    return EOPNOTSUPP;
}
RTM_EXPORT(sched_setscheduler);
