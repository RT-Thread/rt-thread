/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-29     aozima       first version.
 * 2012-04-12     aozima       optimization: find rtc device only first.
 * 2012-04-16     aozima       add scheduler lock for set_date and set_time.
 * 2018-02-16     armink       add auto sync time by NTP
 */

#include <sys/time.h>
#include <string.h>
#include <rtthread.h>

#ifdef RT_USING_RTC

/* Using NTP auto sync RTC time */
#ifdef RTC_SYNC_USING_NTP
/* NTP first sync delay time for network connect, unit: second */
#ifndef RTC_NTP_FIRST_SYNC_DELAY
#define RTC_NTP_FIRST_SYNC_DELAY                 (30)
#endif
/* NTP sync period, unit: second */
#ifndef RTC_NTP_SYNC_PERIOD
#define RTC_NTP_SYNC_PERIOD                      (1L*60L*60L)
#endif
#endif /* RTC_SYNC_USING_NTP */

/**
 * Set system date(time not modify, local timezone).
 *
 * @param rt_uint32_t year  e.g: 2012.
 * @param rt_uint32_t month e.g: 12 (1~12).
 * @param rt_uint32_t day   e.g: 31.
 *
 * @return rt_err_t if set success, return RT_EOK.
 *
 */
rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
{
    time_t now;
    struct tm *p_tm;
    struct tm tm_new;
    rt_device_t device;
    rt_err_t ret = -RT_ERROR;

    /* get current time */
    now = time(RT_NULL);

    /* lock scheduler. */
    rt_enter_critical();
    /* converts calendar time into local time. */
    p_tm = localtime(&now);
    /* copy the statically located variable */
    rt_memcpy(&tm_new, p_tm, sizeof(struct tm));
    /* unlock scheduler. */
    rt_exit_critical();

    /* update date. */
    tm_new.tm_year = year - 1900;
    tm_new.tm_mon  = month - 1; /* tm_mon: 0~11 */
    tm_new.tm_mday = day;

    /* converts the local time into the calendar time. */
    now = mktime(&tm_new);

    device = rt_device_find("rtc");
    if (device == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* update to RTC device. */
    ret = rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);

    return ret;
}

/**
 * Set system time(date not modify, local timezone).
 *
 * @param rt_uint32_t hour   e.g: 0~23.
 * @param rt_uint32_t minute e.g: 0~59.
 * @param rt_uint32_t second e.g: 0~59.
 *
 * @return rt_err_t if set success, return RT_EOK.
 *
 */
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
{
    time_t now;
    struct tm *p_tm;
    struct tm tm_new;
    rt_device_t device;
    rt_err_t ret = -RT_ERROR;

    /* get current time */
    now = time(RT_NULL);

    /* lock scheduler. */
    rt_enter_critical();
    /* converts calendar time into local time. */
    p_tm = localtime(&now);
    /* copy the statically located variable */
    rt_memcpy(&tm_new, p_tm, sizeof(struct tm));
    /* unlock scheduler. */
    rt_exit_critical();

    /* update time. */
    tm_new.tm_hour = hour;
    tm_new.tm_min  = minute;
    tm_new.tm_sec  = second;

    /* converts the local time into the calendar time. */
    now = mktime(&tm_new);

    device = rt_device_find("rtc");
    if (device == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* update to RTC device. */
    ret = rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);

    return ret;
}

#ifdef RTC_SYNC_USING_NTP
static void ntp_sync_thread_enrty(void *param)
{
    extern time_t ntp_sync_to_rtc(const char *host_name);
    /* first sync delay for network connect */
    rt_thread_delay(RTC_NTP_FIRST_SYNC_DELAY * RT_TICK_PER_SECOND);

    while (1)
    {
        ntp_sync_to_rtc(NULL);
        rt_thread_delay(RTC_NTP_SYNC_PERIOD * RT_TICK_PER_SECOND);
    }
}

int rt_rtc_ntp_sync_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;
    rt_thread_t thread;

    if (init_ok)
    {
        return 0;
    }

    thread = rt_thread_create("ntp_sync", ntp_sync_thread_enrty, RT_NULL, 1536, 26, 2);
    if (thread)
    {
        rt_thread_startup(thread);
    }
    else
    {
        return -RT_ENOMEM;
    }

    init_ok = RT_TRUE;
		
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_rtc_ntp_sync_init);
#endif /* RTC_SYNC_USING_NTP */

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <rtdevice.h>

/**
 * show date and time (local timezone)
 */
void list_date(void)
{
    time_t now;

    now = time(RT_NULL);
    rt_kprintf("%.*s\n", 25, ctime(&now));
}
FINSH_FUNCTION_EXPORT(list_date, show date and time (local timezone))
FINSH_FUNCTION_EXPORT(set_date, set date(local timezone) e.g: set_date(2010,2,28))
FINSH_FUNCTION_EXPORT(set_time, set time(local timezone) e.g: set_time(23,59,59))


#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
/**
 * get date and time or set (local timezone) [year month day hour min sec]
 */
static void date(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        time_t now;
        /* output current time */
        now = time(RT_NULL);
        rt_kprintf("%.*s", 25, ctime(&now));
    }
    else if (argc >= 7)
    {
        /* set time and date */
        uint16_t year;
        uint8_t month, day, hour, min, sec;
        year = atoi(argv[1]);
        month = atoi(argv[2]);
        day = atoi(argv[3]);
        hour = atoi(argv[4]);
        min = atoi(argv[5]);
        sec = atoi(argv[6]);
        if (year > 2099 || year < 2000)
        {
            rt_kprintf("year is out of range [2000-2099]\n");
            return;
        }
        if (month == 0 || month > 12)
        {
            rt_kprintf("month is out of range [1-12]\n");
            return;
        }
        if (day == 0 || day > 31)
        {
            rt_kprintf("day is out of range [1-31]\n");
            return;
        }
        if (hour > 23)
        {
            rt_kprintf("hour is out of range [0-23]\n");
            return;
        }
        if (min > 59)
        {
            rt_kprintf("minute is out of range [0-59]\n");
            return;
        }
        if (sec > 59)
        {
            rt_kprintf("second is out of range [0-59]\n");
            return;
        }
        set_time(hour, min, sec);
        set_date(year, month, day);
    }
    else
    {
        rt_kprintf("please input: date [year month day hour min sec] or date\n");
        rt_kprintf("e.g: date 2018 01 01 23 59 59 or date\n");
    }
}
MSH_CMD_EXPORT(list_date, show date and time (local timezone))
MSH_CMD_EXPORT(date, get date and time or set (local timezone) [year month day hour min sec])

#endif /* defined(RT_USING_FINSH) && defined(FINSH_USING_MSH) */
#endif /* RT_USING_FINSH */
#endif /* RT_USING_RTC */
