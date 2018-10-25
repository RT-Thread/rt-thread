/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-12-23     Bernard           first version
 */

#include <rtdevice.h>
#include <rtthread.h>

static const struct rt_clock_cputime_ops *_cputime_ops  = RT_NULL;

/**
 * The clock_cpu_getres() function shall return the resolution of CPU time, the 
 * number of nanosecond per tick.
 *
 * @return the number of nanosecond per tick
 */
float clock_cpu_getres(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_getres();

    rt_set_errno(-ENOSYS);
    return 0;
}

/**
 * The clock_cpu_gettime() function shall return the current value of cpu time tick.
 *
 * @return the cpu tick
 */
uint32_t clock_cpu_gettime(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_gettime();

    rt_set_errno(-ENOSYS);
    return 0;
}

/**
 * The clock_cpu_microsecond() fucntion shall return the microsecond according to 
 * cpu_tick parameter.
 *
 * @param cpu_tick the cpu tick
 *
 * @return the microsecond
 */
uint32_t clock_cpu_microsecond(uint32_t cpu_tick)
{
    float unit = clock_cpu_getres();

    return (uint32_t)((cpu_tick * unit) / 1000);
}

/**
 * The clock_cpu_microsecond() fucntion shall return the millisecond according to 
 * cpu_tick parameter.
 *
 * @param cpu_tick the cpu tick
 *
 * @return the millisecond
 */
uint32_t clock_cpu_millisecond(uint32_t cpu_tick)
{
    float unit = clock_cpu_getres();

    return (uint32_t)((cpu_tick * unit) / (1000 * 1000));
}

/**
 * The clock_cpu_seops() function shall set the ops of cpu time.
 * 
 * @return always return 0.
 */
int clock_cpu_setops(const struct rt_clock_cputime_ops *ops)
{
    _cputime_ops = ops;
    if (ops)
    {
        RT_ASSERT(ops->cputime_getres  != RT_NULL);
        RT_ASSERT(ops->cputime_gettime != RT_NULL);
    }

    return 0;
}
