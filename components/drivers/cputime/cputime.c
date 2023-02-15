/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-12-23     Bernard           first version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include <sys/errno.h>

static const struct rt_clock_cputime_ops *_cputime_ops  = RT_NULL;

/**
 * The clock_cpu_getres() function shall return the resolution of CPU time, the
 * number of nanosecond per tick.
 *
 * @return the number of nanosecond per tick
 */
double clock_cpu_getres(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_getres();

    rt_set_errno(ENOSYS);
    return 0;
}

/**
 * The clock_cpu_gettime() function shall return the current value of cpu time tick.
 *
 * @return the cpu tick
 */
uint64_t clock_cpu_gettime(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_gettime();

    rt_set_errno(ENOSYS);
    return 0;
}

/**
 * The clock_cpu_settimeout() fucntion set timeout time and timeout callback function
 * The timeout callback function will be called when the timeout time is reached
 *
 * @param tick the Timeout tick
 * @param timeout the Timeout function
 * @param parameter the Parameters of timeout function
 *
 */
int clock_cpu_settimeout(uint64_t tick, void (*timeout)(void *param), void *param)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_settimeout(tick, timeout, param);

    rt_set_errno(ENOSYS);
    return 0;
}

int clock_cpu_issettimeout(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_settimeout != RT_NULL;
    return RT_FALSE;
}

/**
 * The clock_cpu_microsecond() fucntion shall return the microsecond according to
 * cpu_tick parameter.
 *
 * @param cpu_tick the cpu tick
 *
 * @return the microsecond
 */
uint64_t clock_cpu_microsecond(uint64_t cpu_tick)
{
    double unit = clock_cpu_getres();

    return (uint64_t)((cpu_tick * unit) / 1000);
}

/**
 * The clock_cpu_microsecond() fucntion shall return the millisecond according to
 * cpu_tick parameter.
 *
 * @param cpu_tick the cpu tick
 *
 * @return the millisecond
 */
uint64_t clock_cpu_millisecond(uint64_t cpu_tick)
{
    double unit = clock_cpu_getres();

    return (uint64_t)((cpu_tick * unit) / (1000 * 1000));
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
