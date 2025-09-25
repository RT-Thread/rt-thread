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
#include <sys/time.h>

rt_err_t rt_clock_boottime_get_us(struct timeval *tv)
{
    rt_uint64_t cnt;
    rt_uint64_t freq;

    RT_ASSERT(tv != RT_NULL);

    cnt = rt_clock_time_get_counter();
    freq = rt_clock_time_get_freq();
    if (freq == 0)
    {
        return -RT_ERROR;
    }

    tv->tv_sec = (time_t)(cnt / freq);
    tv->tv_usec = rt_muldiv_u64(cnt % freq, MICROSECOND_PER_SECOND, freq, NULL);

    return RT_EOK;
}

rt_err_t rt_clock_boottime_get_s(time_t *t)
{
    rt_uint64_t cnt;
    rt_uint64_t freq;

    RT_ASSERT(t != RT_NULL);

    cnt = rt_clock_time_get_counter();
    freq = rt_clock_time_get_freq();
    if (freq == 0)
    {
        return -RT_ERROR;
    }

    *t = (time_t)(cnt / freq);

    return RT_EOK;
}

rt_err_t rt_clock_boottime_get_ns(struct timespec *ts)
{
    rt_uint64_t cnt;
    rt_uint64_t freq;

    RT_ASSERT(ts != RT_NULL);

    cnt = rt_clock_time_get_counter();
    freq = rt_clock_time_get_freq();
    if (freq == 0)
    {
        return -RT_ERROR;
    }

    ts->tv_sec = (time_t)(cnt / freq);
    ts->tv_nsec = rt_muldiv_u64(cnt % freq, NANOSECOND_PER_SECOND, freq, NULL);

    return RT_EOK;
}
