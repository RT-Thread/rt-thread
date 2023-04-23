/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-29     aozima       first version.
 * 2012-04-12     aozima       optimization: find rtc device only first.
 * 2012-04-16     aozima       add scheduler lock for set_date and set_time.
 * 2018-02-16     armink       add auto sync time by NTP
 * 2021-05-09     Meco Man     remove NTP
 * 2021-06-11     iysheng      implement RTC framework V2.0
 * 2021-07-30     Meco Man     move rtc_core.c to rtc.c
 */

#include <string.h>
#include <stdlib.h>
#include <rtthread.h>
#include <drivers/rtc.h>

#ifdef RT_USING_RTC

static rt_device_t _rtc_device;
/*
 * This function initializes rtc_core
 */
static rt_err_t rt_rtc_init(struct rt_device *dev)
{
    rt_rtc_dev_t *rtc_core;

    RT_ASSERT(dev != RT_NULL);
    rtc_core = (rt_rtc_dev_t *)dev;
    if (rtc_core->ops->init)
    {
        return (rtc_core->ops->init());
    }

    return -RT_ENOSYS;
}

static rt_err_t rt_rtc_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_rtc_close(struct rt_device *dev)
{
    /* Add close member function in rt_rtc_ops when need,
     * then call that function here.
     * */
    return RT_EOK;
}

static rt_err_t rt_rtc_control(struct rt_device *dev, int cmd, void *args)
{
#define TRY_DO_RTC_FUNC(rt_rtc_dev, func_name, args) \
    rt_rtc_dev->ops->func_name ?  rt_rtc_dev->ops->func_name(args) : -RT_EINVAL;

    rt_rtc_dev_t *rtc_device;
    rt_err_t ret = -RT_EINVAL;

    RT_ASSERT(dev != RT_NULL);
    rtc_device = (rt_rtc_dev_t *)dev;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
            ret = TRY_DO_RTC_FUNC(rtc_device, get_secs, args);
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIME:
            ret = TRY_DO_RTC_FUNC(rtc_device, set_secs, args);
            break;
        case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
            ret = TRY_DO_RTC_FUNC(rtc_device, get_timeval, args);
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
            ret = TRY_DO_RTC_FUNC(rtc_device, set_timeval, args);
            break;
        case RT_DEVICE_CTRL_RTC_GET_ALARM:
            ret = TRY_DO_RTC_FUNC(rtc_device, get_alarm, args);
            break;
        case RT_DEVICE_CTRL_RTC_SET_ALARM:
            ret = TRY_DO_RTC_FUNC(rtc_device, set_alarm, args);
            break;
        default:
            break;
    }

    return ret;

#undef TRY_DO_RTC_FUNC
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtc_core_ops =
{
    rt_rtc_init,
    rt_rtc_open,
    rt_rtc_close,
    RT_NULL,
    RT_NULL,
    rt_rtc_control,
};
#endif /* RT_USING_DEVICE_OPS */

rt_err_t rt_hw_rtc_register(rt_rtc_dev_t  *rtc,
                            const char    *name,
                            rt_uint32_t    flag,
                            void          *data)
{
    struct rt_device *device;
    RT_ASSERT(rtc != RT_NULL);

    device = &(rtc->parent);

    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rtc_core_ops;
#else
    device->init        = rt_rtc_init;
    device->open        = rt_rtc_open;
    device->close       = rt_rtc_close;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_rtc_control;
#endif /* RT_USING_DEVICE_OPS */
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

/**
 * Set system date(time not modify, local timezone).
 *
 * @param rt_uint32_t year  e.g: 2012.
 * @param rt_uint32_t month e.g: 12 (1~12).
 * @param rt_uint32_t day   e.g: 31.
 *
 * @return rt_err_t if set success, return RT_EOK.
 */
rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
{
    time_t now, old_timestamp = 0;
    struct tm tm_new = {0};
    rt_err_t ret = -RT_ERROR;

    if (_rtc_device == RT_NULL)
    {
        _rtc_device = rt_device_find("rtc");
        if (_rtc_device == RT_NULL)
        {
            return -RT_ERROR;
        }
    }

    /* get current time */
    ret = rt_device_control(_rtc_device, RT_DEVICE_CTRL_RTC_GET_TIME, &old_timestamp);
    if (ret != RT_EOK)
    {
        return ret;
    }

    /* converts calendar time into local time. */
    localtime_r(&old_timestamp, &tm_new);

    /* update date. */
    tm_new.tm_year = year - 1900;
    tm_new.tm_mon  = month - 1; /* tm_mon: 0~11 */
    tm_new.tm_mday = day;

    /* converts the local time into the calendar time. */
    now = mktime(&tm_new);

    /* update to RTC device. */
    ret = rt_device_control(_rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);
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
 */
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
{
    time_t now, old_timestamp = 0;
    struct tm tm_new = {0};
    rt_err_t ret = -RT_ERROR;

    if (_rtc_device == RT_NULL)
    {
        _rtc_device = rt_device_find("rtc");
        if (_rtc_device == RT_NULL)
        {
            return -RT_ERROR;
        }
    }

    /* get current time */
    ret = rt_device_control(_rtc_device, RT_DEVICE_CTRL_RTC_GET_TIME, &old_timestamp);
    if (ret != RT_EOK)
    {
        return ret;
    }

    /* converts calendar time into local time. */
    localtime_r(&old_timestamp, &tm_new);

    /* update time. */
    tm_new.tm_hour = hour;
    tm_new.tm_min  = minute;
    tm_new.tm_sec  = second;

    /* converts the local time into the calendar time. */
    now = mktime(&tm_new);

    /* update to RTC device. */
    ret = rt_device_control(_rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);
    return ret;
}

/**
 * Set timestamp(UTC).
 *
 * @param time_t timestamp
 *
 * @return rt_err_t if set success, return RT_EOK.
 */
rt_err_t set_timestamp(time_t timestamp)
{
    if (_rtc_device == RT_NULL)
    {
        _rtc_device = rt_device_find("rtc");
        if (_rtc_device == RT_NULL)
        {
            return -RT_ERROR;
        }
    }

    /* update to RTC device. */
    return rt_device_control(_rtc_device, RT_DEVICE_CTRL_RTC_SET_TIME, &timestamp);
}

/**
 * Get timestamp(UTC).
 *
 * @param time_t* timestamp
 *
 * @return rt_err_t if set success, return RT_EOK.
 */
rt_err_t get_timestamp(time_t *timestamp)
{
    if (_rtc_device == RT_NULL)
    {
        _rtc_device = rt_device_find("rtc");
        if (_rtc_device == RT_NULL)
        {
            return -RT_ERROR;
        }
    }

    /* Get timestamp from RTC device. */
    return rt_device_control(_rtc_device, RT_DEVICE_CTRL_RTC_GET_TIME, timestamp);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
/**
 * get date and time or set (local timezone) [year month day hour min sec]
 */
static void date(int argc, char **argv)
{
    time_t now = (time_t)0;

    if (argc == 1)
    {
        struct timeval tv = { 0 };
        struct timezone tz = { 0 };

        gettimeofday(&tv, &tz);
        now = tv.tv_sec;
        /* output current time */
        rt_kprintf("local time: %.*s", 25, ctime(&now));
        rt_kprintf("timestamps: %ld\n", (long)tv.tv_sec);
        rt_kprintf("timezone: UTC%c%d\n", -tz.tz_minuteswest > 0 ? '+' : '-', -tz.tz_minuteswest / 60);
    }
    else if (argc >= 7)
    {
        /* set time and date */
        struct tm tm_new = {0};
        time_t old = (time_t)0;
        rt_err_t err;

        tm_new.tm_year = atoi(argv[1]) - 1900;
        tm_new.tm_mon = atoi(argv[2]) - 1; /* .tm_min's range is [0-11] */
        tm_new.tm_mday = atoi(argv[3]);
        tm_new.tm_hour = atoi(argv[4]);
        tm_new.tm_min = atoi(argv[5]);
        tm_new.tm_sec = atoi(argv[6]);
        if (tm_new.tm_year <= 0)
        {
            rt_kprintf("year is out of range [1900-]\n");
            return;
        }
        if (tm_new.tm_mon > 11) /* .tm_min's range is [0-11] */
        {
            rt_kprintf("month is out of range [1-12]\n");
            return;
        }
        if (tm_new.tm_mday == 0 || tm_new.tm_mday > 31)
        {
            rt_kprintf("day is out of range [1-31]\n");
            return;
        }
        if (tm_new.tm_hour > 23)
        {
            rt_kprintf("hour is out of range [0-23]\n");
            return;
        }
        if (tm_new.tm_min > 59)
        {
            rt_kprintf("minute is out of range [0-59]\n");
            return;
        }
        if (tm_new.tm_sec > 60)
        {
            rt_kprintf("second is out of range [0-60]\n");
            return;
        }
        /* save old timestamp */
        err = get_timestamp(&old);
        if (err != RT_EOK)
        {
            rt_kprintf("Get current timestamp failed. %d\n", err);
            return;
        }
        /* converts the local time into the calendar time. */
        now = mktime(&tm_new);
        err = set_timestamp(now);
        if (err != RT_EOK)
        {
            rt_kprintf("set date failed. %d\n", err);
            return;
        }
        get_timestamp(&now); /* get new timestamp */
        rt_kprintf("old: %.*s", 25, ctime(&old));
        rt_kprintf("now: %.*s", 25, ctime(&now));
    }
    else
    {
        rt_kprintf("please input: date [year month day hour min sec] or date\n");
        rt_kprintf("e.g: date 2018 01 01 23 59 59 or date\n");
    }
}
MSH_CMD_EXPORT(date, get date and time or set (local timezone) [year month day hour min sec])
#endif /* RT_USING_FINSH */

#endif /* RT_USING_RTC */
