/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-04     RT-Thread    CPU time and legacy cputime API implementation
 */

#include <rtdevice.h>
#include <rthw.h>
#include <sys/errno.h>

/**
 * @brief Get CPU time resolution
 * 
 * @return Resolution in nanoseconds * 1000000
 */
uint64_t clock_cpu_getres(void)
{
    return rt_clock_time_getres();
}

/**
 * @brief Get current CPU time counter value
 * 
 * @return Current counter value
 */
uint64_t clock_cpu_gettime(void)
{
    return rt_clock_time_getcnt();
}

/**
 * @brief Convert CPU ticks to microseconds
 * 
 * @param cpu_tick CPU tick count
 * @return Microseconds
 */
uint64_t clock_cpu_microsecond(uint64_t cpu_tick)
{
    return rt_clock_time_cnt_to_us(cpu_tick);
}

/**
 * @brief Convert CPU ticks to milliseconds
 * 
 * @param cpu_tick CPU tick count
 * @return Milliseconds
 */
uint64_t clock_cpu_millisecond(uint64_t cpu_tick)
{
    return rt_clock_time_cnt_to_ms(cpu_tick);
}

/**
 * @brief High-precision nanosecond delay
 * 
 * @param ns Nanoseconds to delay
 * @return RT_EOK on success
 */
rt_err_t rt_cputime_ndelay(rt_uint64_t ns)
{
    return rt_clock_ndelay((unsigned long)ns);
}

/**
 * @brief High-precision microsecond delay
 * 
 * @param us Microseconds to delay
 * @return RT_EOK on success
 */
rt_err_t rt_cputime_udelay(rt_uint64_t us)
{
    return rt_clock_udelay((unsigned long)us);
}

/**
 * @brief High-precision millisecond delay
 * 
 * @param ms Milliseconds to delay
 * @return RT_EOK on success
 */
rt_err_t rt_cputime_mdelay(rt_uint64_t ms)
{
    return rt_clock_mdelay((unsigned long)ms);
}
