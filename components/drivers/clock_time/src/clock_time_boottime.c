/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Boottime APIs implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/clock_time.h>
#include <sys/time.h>

rt_weak rt_err_t rt_clock_boottime_get_us(struct timeval *tv)
{
    RT_ASSERT(tv != RT_NULL);

    rt_uint64_t ns = (rt_clock_cputimer_getcnt() * rt_clock_cputimer_getres()) / RT_CLOCK_TIME_RESMUL;

    tv->tv_sec  = ns / (1000ULL * 1000 * 1000);
    tv->tv_usec = (ns % (1000ULL * 1000 * 1000)) / 1000;

    return RT_EOK;
}

rt_weak rt_err_t rt_clock_boottime_get_s(time_t *t)
{
    RT_ASSERT(t != RT_NULL);

    rt_uint64_t ns = (rt_clock_cputimer_getcnt() * rt_clock_cputimer_getres()) / RT_CLOCK_TIME_RESMUL;

    *t = ns / (1000ULL * 1000 * 1000);

    return RT_EOK;
}

rt_weak rt_err_t rt_clock_boottime_get_ns(struct timespec *ts)
{
    RT_ASSERT(ts != RT_NULL);

    rt_uint64_t ns = (rt_clock_cputimer_getcnt() * rt_clock_cputimer_getres()) / RT_CLOCK_TIME_RESMUL;

    ts->tv_sec  = ns / (1000ULL * 1000 * 1000);
    ts->tv_nsec = ns % (1000ULL * 1000 * 1000);

    return RT_EOK;
}
