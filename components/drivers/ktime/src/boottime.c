/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     xqyjlj       The first version.
 */

#include "ktime.h"

#define __KTIME_MUL ((1000ULL * 1000 * 1000) / RT_TICK_PER_SECOND)

rt_weak rt_err_t rt_ktime_boottime_get_us(struct timeval *tv)
{
    RT_ASSERT(tv != RT_NULL);

    rt_uint64_t ns = (rt_ktime_cputimer_getcnt() * rt_ktime_cputimer_getres()) / RT_KTIME_RESMUL;

    tv->tv_sec  = ns / (1000ULL * 1000 * 1000);
    tv->tv_usec = (ns % (1000ULL * 1000 * 1000)) / 1000;

    return RT_EOK;
}

rt_weak rt_err_t rt_ktime_boottime_get_s(time_t *t)
{
    RT_ASSERT(t != RT_NULL);

    rt_uint64_t ns = (rt_ktime_cputimer_getcnt() * rt_ktime_cputimer_getres()) / RT_KTIME_RESMUL;

    *t = ns / (1000ULL * 1000 * 1000);

    return RT_EOK;
}

rt_weak rt_err_t rt_ktime_boottime_get_ns(struct timespec *ts)
{
    RT_ASSERT(ts != RT_NULL);

    rt_uint64_t ns = (rt_ktime_cputimer_getcnt() * rt_ktime_cputimer_getres()) / RT_KTIME_RESMUL;

    ts->tv_sec  = ns / (1000ULL * 1000 * 1000);
    ts->tv_nsec = ns % (1000ULL * 1000 * 1000);

    return RT_EOK;
}
