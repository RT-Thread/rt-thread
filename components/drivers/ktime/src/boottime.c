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

rt_weak rt_err_t rt_ktime_boottime_get_us(struct timeval *tv)
{
    RT_ASSERT(tv != RT_NULL);

    rt_tick_t cnt = rt_ktime_cputimer_getcnt();
    rt_uint32_t freq = rt_ktime_cputimer_getfrq();

    tv->tv_sec = (time_t)(cnt / freq);
    tv->tv_usec = rt_muldiv_u32((rt_uint32_t)(cnt % freq), MICROSECOND_PER_SECOND, freq, NULL);

    return RT_EOK;
}

rt_weak rt_err_t rt_ktime_boottime_get_s(time_t *t)
{
    RT_ASSERT(t != RT_NULL);

    rt_tick_t cnt = rt_ktime_cputimer_getcnt();
    rt_uint32_t freq = rt_ktime_cputimer_getfrq();

    *t = (time_t)(cnt / freq);

    return RT_EOK;
}

rt_weak rt_err_t rt_ktime_boottime_get_ns(struct timespec *ts)
{
    RT_ASSERT(ts != RT_NULL);

    rt_tick_t cnt = rt_ktime_cputimer_getcnt();
    rt_uint32_t freq = rt_ktime_cputimer_getfrq();

    ts->tv_sec = (time_t)(cnt / freq);
    ts->tv_nsec = rt_muldiv_u32((rt_uint32_t)(cnt % freq), NANOSECOND_PER_SECOND, freq, NULL);

    return RT_EOK;
}
