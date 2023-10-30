/**
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
 * @brief   Sleep for a specified number of milliseconds.
 *
 * @param   msecs   is the number of milliseconds to sleep.
 */
void msleep(unsigned int msecs)
{
    rt_thread_mdelay(msecs);
}
RTM_EXPORT(msleep);

/**
 * @brief   Sleep for a specified number of seconds.
 *
 * @param   seconds is the number of seconds to sleep.
 */
void ssleep(unsigned int seconds)
{
    msleep(seconds * 1000);
}
RTM_EXPORT(ssleep);

/**
 * @brief   Delay for a specified number of milliseconds.
 *
 * @param   msecs   is the number of milliseconds to delay.
 */
void mdelay(unsigned long msecs)
{
    rt_hw_us_delay(msecs * 1000);
}
RTM_EXPORT(mdelay);

/**
 * @brief   Delay for a specified number of microseconds.
 *
 * @param   usecs   is the number of microseconds to delay.
 */
void udelay(unsigned long usecs)
{
    rt_hw_us_delay(usecs);
}
RTM_EXPORT(udelay);

/**
 * @brief   Delay for a specified number of nanoseconds (approximately).
 *
 * @param   nsecs   is the number of nanoseconds to delay (approximately).
 */
void ndelay(unsigned long nsecs)
{
    rt_hw_us_delay(1);
}
RTM_EXPORT(ndelay);

/**
 * @brief   Sleep for a specified number of seconds (or microseconds if the scheduler is not running).
 *
 * @param   seconds is the number of seconds to sleep.
 *
 * @return  Always returns 0.
 */
unsigned int sleep(unsigned int seconds)
{
    if (rt_thread_self() != RT_NULL)
    {
        ssleep(seconds);
    }
    else /* scheduler has not run yet */
    {
        while (seconds > 0)
        {
            udelay(1000000u);
            seconds--;
        }
    }

    return 0;
}
RTM_EXPORT(sleep);

/**
 * @brief   Sleep for a specified number of microseconds (or nanoseconds if the scheduler is not running).
 *
 * @param   usec    is the number of microseconds to sleep.
 *
 * @return  Always returns 0.
 */
int usleep(useconds_t usec)
{
    if (rt_thread_self() != RT_NULL)
    {
        msleep(usec / 1000u);
        udelay(usec % 1000u);
    }
    else /* scheduler has not run yet */
    {
        udelay(usec);
    }

    return 0;
}
RTM_EXPORT(usleep);
