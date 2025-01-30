/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-12-23     Bernard           first version
 * 2025-01-30     wumingzi          transform to doxygen comment
 */

#include <rtdevice.h>
#include <rtthread.h>
#include <sys/errno.h>

/**
 * @addtogroup  Drivers                 RTTHREAD Driver
 * @defgroup    cputimer                cputimer
 * @brief       cputimer driver api
 * @ingroup     Drivers
 * @addtogroup  cputimer
 * @{
 */

static const struct rt_clock_cputime_ops *_cputime_ops  = RT_NULL;

/**
 * @brief   The clock_cpu_getres() function shall return the resolution of CPU time, the
 * number of nanosecond per tick.
 *
 * @return  the number of nanosecond per tick(x (1000UL * 1000))
 */
uint64_t clock_cpu_getres(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_getres();

    rt_set_errno(ENOSYS);
    return 0;
}

/**
 * @brief   The clock_cpu_gettime() function shall return the current value of cpu time tick.
 *
 * @return  the cpu tick
 */
uint64_t clock_cpu_gettime(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_gettime();

    rt_set_errno(ENOSYS);
    return 0;
}

/**
 * @brief   The clock_cpu_settimeout() fucntion set timeout time and timeout callback function
 * The timeout callback function will be called when the timeout time is reached
 *
 * @param tick the Timeout tick
 * @param timeout the Timeout function
 * @param param the Parameters of timeout function
 *
 * @return  RT_FALSE or RT_TURE
 */
int clock_cpu_settimeout(uint64_t tick, void (*timeout)(void *param), void *param)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_settimeout(tick, timeout, param);

    rt_set_errno(ENOSYS);
    return 0;
}

/**
 * @brief   Check if cputimer timeout callback function has been set
 *
 * @return  RT_FALSE or RT_TURE
 */
int clock_cpu_issettimeout(void)
{
    if (_cputime_ops)
        return _cputime_ops->cputime_settimeout != RT_NULL;
    return RT_FALSE;
}

/**
 * @brief   The clock_cpu_microsecond() fucntion shall return the microsecond according to
 * cpu_tick parameter.
 *
 * @param cpu_tick the cpu tick
 *
 * @return  the microseconds
 */
uint64_t clock_cpu_microsecond(uint64_t cpu_tick)
{
    uint64_t unit = clock_cpu_getres();

    return (uint64_t)(((cpu_tick * unit) / (1000UL * 1000)) / 1000);
}

/**
 * @brief   The clock_cpu_millisecond() fucntion shall return the millisecond according to
 * cpu_tick parameter.
 *
 * @param cpu_tick the cpu tick
 *
 * @return  the milliseconds
 */
uint64_t clock_cpu_millisecond(uint64_t cpu_tick)
{
    uint64_t unit = clock_cpu_getres();

    return (uint64_t)(((cpu_tick * unit) / (1000UL * 1000)) / (1000UL * 1000));
}

/**
 * @brief   The clock_cpu_seops() function shall set the ops of cpu time.
 *
 * @return  always return 0.
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
/*! @}*/