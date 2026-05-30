/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Clock time boottime helpers
 */

#include <drivers/clock_time.h>

rt_err_t rt_clock_boottime_get_us(struct timeval *tv)
{
    rt_uint64_t cnt;
    rt_uint64_t res;
    rt_uint64_t ns;

    RT_ASSERT(tv != RT_NULL);

    cnt = rt_clock_time_get_counter();
    res = rt_clock_time_get_res_scaled();
    if (res == 0)
    {
        return -RT_ERROR;
    }

    ns = (cnt * res) / RT_CLOCK_TIME_RESMUL;

    tv->tv_sec  = ns / (1000ULL * 1000 * 1000);
    tv->tv_usec = (ns % (1000ULL * 1000 * 1000)) / 1000;

    return RT_EOK;
}

rt_err_t rt_clock_boottime_get_s(time_t *t)
{
    rt_uint64_t cnt;
    rt_uint64_t res;
    rt_uint64_t ns;

    RT_ASSERT(t != RT_NULL);

    cnt = rt_clock_time_get_counter();
    res = rt_clock_time_get_res_scaled();
    if (res == 0)
    {
        return -RT_ERROR;
    }

    ns = (cnt * res) / RT_CLOCK_TIME_RESMUL;
    *t = ns / (1000ULL * 1000 * 1000);

    return RT_EOK;
}

rt_err_t rt_clock_boottime_get_ns(struct timespec *ts)
{
    rt_uint64_t cnt;
    rt_uint64_t res;
    rt_uint64_t ns;

    RT_ASSERT(ts != RT_NULL);

    cnt = rt_clock_time_get_counter();
    res = rt_clock_time_get_res_scaled();
    if (res == 0)
    {
        return -RT_ERROR;
    }

    ns = (cnt * res) / RT_CLOCK_TIME_RESMUL;

    ts->tv_sec  = ns / (1000ULL * 1000 * 1000);
    ts->tv_nsec = ns % (1000ULL * 1000 * 1000);

    return RT_EOK;
}
