/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-30     rcitach      first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <time.h>
#include "drv_rtc.h"
#include "soft_rtc.h"

#ifndef BSP_RTC_SOFT_DEFAULT_YEAR
#define BSP_RTC_SOFT_DEFAULT_YEAR      2026
#endif

#ifndef BSP_RTC_SOFT_DEFAULT_MONTH
#define BSP_RTC_SOFT_DEFAULT_MONTH     1
#endif

#ifndef BSP_RTC_SOFT_DEFAULT_DAY
#define BSP_RTC_SOFT_DEFAULT_DAY       1
#endif

#ifndef BSP_RTC_SOFT_DEFAULT_HOUR
#define BSP_RTC_SOFT_DEFAULT_HOUR      0
#endif

#ifndef BSP_RTC_SOFT_DEFAULT_MIN
#define BSP_RTC_SOFT_DEFAULT_MIN       0
#endif

#ifndef BSP_RTC_SOFT_DEFAULT_SEC
#define BSP_RTC_SOFT_DEFAULT_SEC       0
#endif

struct soft_rtc_device
{
    time_t base_sec;
    rt_tick_t base_tick;
    rt_bool_t valid;
};

static struct soft_rtc_device g_soft_rtc;

static rt_bool_t soft_rtc_is_leap_year(int year)
{
    return (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) ? RT_TRUE : RT_FALSE;
}

static rt_uint8_t soft_rtc_month_days(int year, int mon)
{
    static const rt_uint8_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((mon == 1) && soft_rtc_is_leap_year(year))
    {
        return 29;
    }

    return days[mon];
}

static rt_bool_t soft_rtc_tm_is_valid(const struct tm *tm)
{
    int year;

    if (tm == RT_NULL)
    {
        return RT_FALSE;
    }

    year = tm->tm_year + 1900;
    if ((year < 1970) ||
        (tm->tm_mon < 0) || (tm->tm_mon > 11) ||
        (tm->tm_mday < 1) || (tm->tm_mday > soft_rtc_month_days(year, tm->tm_mon)) ||
        (tm->tm_hour < 0) || (tm->tm_hour > 23) ||
        (tm->tm_min < 0) || (tm->tm_min > 59) ||
        (tm->tm_sec < 0) || (tm->tm_sec > 59))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void soft_rtc_set_secs(time_t sec)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    g_soft_rtc.base_sec = sec;
    g_soft_rtc.base_tick = rt_tick_get();
    g_soft_rtc.valid = RT_TRUE;
    rt_hw_interrupt_enable(level);
}

static time_t soft_rtc_get_secs(void)
{
    time_t base_sec;
    rt_tick_t base_tick;
    rt_bool_t valid;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    base_sec = g_soft_rtc.base_sec;
    base_tick = g_soft_rtc.base_tick;
    valid = g_soft_rtc.valid;
    rt_hw_interrupt_enable(level);

    if (!valid)
    {
        return 0;
    }

    return base_sec + (time_t)(rt_tick_get_delta(base_tick) / RT_TICK_PER_SECOND);
}

rt_err_t soft_rtc_init(void)
{
    struct tm default_time;

    if (g_soft_rtc.valid)
    {
        return RT_EOK;
    }

    rt_memset(&default_time, 0, sizeof(default_time));
    default_time.tm_year = BSP_RTC_SOFT_DEFAULT_YEAR - 1900;
    default_time.tm_mon = BSP_RTC_SOFT_DEFAULT_MONTH - 1;
    default_time.tm_mday = BSP_RTC_SOFT_DEFAULT_DAY;
    default_time.tm_hour = BSP_RTC_SOFT_DEFAULT_HOUR;
    default_time.tm_min = BSP_RTC_SOFT_DEFAULT_MIN;
    default_time.tm_sec = BSP_RTC_SOFT_DEFAULT_SEC;
    default_time.tm_isdst = -1;

    if (!soft_rtc_tm_is_valid(&default_time))
    {
        return -RT_EINVAL;
    }

    soft_rtc_set_secs(mktime(&default_time));
    return RT_EOK;
}

rt_err_t soft_rtc_get_time(struct tm *tm)
{
    time_t sec;

    if (tm == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (!g_soft_rtc.valid)
    {
        rt_err_t result = soft_rtc_init();
        if (result != RT_EOK)
        {
            return result;
        }
    }

    sec = soft_rtc_get_secs();
    localtime_r(&sec, tm);

    return RT_EOK;
}

rt_err_t soft_rtc_set_time(const struct tm *tm)
{
    struct tm time_copy;
    time_t sec;

    if (!soft_rtc_tm_is_valid(tm))
    {
        return -RT_EINVAL;
    }

    time_copy = *tm;
    time_copy.tm_isdst = -1;
    sec = mktime(&time_copy);
    soft_rtc_set_secs(sec);

    return RT_EOK;
}

static rt_err_t soft_rtc_backend_init(void *user_data)
{
    RT_UNUSED(user_data);

    return soft_rtc_init();
}

static rt_err_t soft_rtc_backend_get_time(void *user_data, struct tm *tm)
{
    RT_UNUSED(user_data);

    return soft_rtc_get_time(tm);
}

static rt_err_t soft_rtc_backend_set_time(void *user_data, const struct tm *tm)
{
    RT_UNUSED(user_data);

    return soft_rtc_set_time(tm);
}

static const struct ns800_rtc_ops soft_rtc_ops =
{
    soft_rtc_backend_init,
    soft_rtc_backend_get_time,
    soft_rtc_backend_set_time,
};

int rt_hw_soft_rtc_init(void)
{
    rt_err_t result;

    result = ns800_rtc_register("soft_rtc", &soft_rtc_ops, &g_soft_rtc);
    if (result != RT_EOK)
    {
        rt_kprintf("soft_rtc: register rtc backend failed, result %d\n", result);
        return -1;
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_soft_rtc_init);

