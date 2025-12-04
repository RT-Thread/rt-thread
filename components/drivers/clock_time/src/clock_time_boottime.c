/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    Boottime implementation using clock_time
 */

#include <rtdevice.h>
#include <sys/time.h>

/**
 * @brief Get boottime in microsecond precision
 * 
 * @param tv Output timeval structure
 * @return RT_EOK on success
 */
rt_err_t rt_boottime_get_us(struct timeval *tv)
{
    return rt_clock_time_boottime_us(tv);
}

/**
 * @brief Get boottime in second precision
 * 
 * @param t Output time_t value
 * @return RT_EOK on success
 */
rt_err_t rt_boottime_get_s(time_t *t)
{
    return rt_clock_time_boottime_s(t);
}

/**
 * @brief Get boottime in nanosecond precision
 * 
 * @param ts Output timespec structure
 * @return RT_EOK on success
 */
rt_err_t rt_boottime_get_ns(struct timespec *ts)
{
    return rt_clock_time_boottime_ns(ts);
}
