/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-07     Meco Man     first Version
 */

#include <sys/types.h>
#include <rtthread.h>
#include <rthw.h>

/**
 * @brief    Delays the execution of the current thread for the specified number of milliseconds.
 *
 * @param    msecs The number of milliseconds to sleep.
 */
void msleep(unsigned int msecs)
{
    rt_thread_mdelay(msecs);
}
RTM_EXPORT(msleep);

/**
 * @brief    Delays the execution of the current thread for the specified number of seconds.
 *
 * @param    seconds The number of seconds to sleep.
 */
void ssleep(unsigned int seconds)
{
    msleep(seconds * 1000);
}
RTM_EXPORT(ssleep);

/**
 * @brief    Delays the execution of the current thread for the specified number of milliseconds.
 *
 * @param    msecs The number of milliseconds to delay.
 */
void mdelay(unsigned long msecs)
{
    rt_hw_us_delay(msecs * 1000);
}
RTM_EXPORT(mdelay);

/**
 * @brief    Delays the execution of the current thread for the specified number of microseconds.
 *
 * @param    usecs The number of microseconds to delay.
 */
void udelay(unsigned long usecs)
{
    rt_hw_us_delay(usecs);
}
RTM_EXPORT(udelay);

/**
 * @brief    Delays the execution of the current thread for approximately one microsecond.
 *
 * @param    nsecs This parameter is ignored.
 */
void ndelay(unsigned long nsecs)
{
    rt_hw_us_delay(1);
}
RTM_EXPORT(ndelay);

/**
 * @brief    Delays the execution of the current thread for the specified number of seconds.
 *
 * @param    seconds The number of seconds to sleep.
 *
 * @return   Returns 0 on success.
 */
unsigned int sleep(unsigned int seconds)
{
    if (rt_thread_self() != RT_NULL)
    {
        ssleep(seconds);
    }
    else /* scheduler has not run yet */
    {
        while(seconds > 0)
        {
            udelay(1000000u);
            seconds --;
        }
    }

    return 0;
}
RTM_EXPORT(sleep);

/**
 * @brief    Delays the execution of the current thread for the specified number of microseconds.
 *
 * @param    usec The number of microseconds to sleep.
 *
 * @return   Returns 0 on success.
 */
int usleep(useconds_t usec)
{
    if (rt_thread_self() != RT_NULL)
    {
        msleep(usec / 1000u);
        udelay(usec % 1000u);
    }
    else  /* scheduler has not run yet */
    {
        udelay(usec);
    }

    return 0;
}
RTM_EXPORT(usleep);
