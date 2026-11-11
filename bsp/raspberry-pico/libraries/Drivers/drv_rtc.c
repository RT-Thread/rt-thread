/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2024-01-13   ChuShicheng   first version
 */

#include "board.h"
#include <rtdevice.h>
#include "hardware/rtc.h"
#include "pico/util/datetime.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.RTC"

struct rtc_device_object
{
    rt_rtc_dev_t  rtc_dev;
};

static struct rtc_device_object rtc_device;

static rt_err_t pico_rtc_get_timeval(struct timeval *tv)
{
    datetime_t t;
    struct tm tm_new = {0};
    rtc_get_datetime(&t);

    tm_new.tm_sec  = t.sec;
    tm_new.tm_min  = t.min;
    tm_new.tm_hour = t.hour;
    tm_new.tm_wday = t.dotw;
    tm_new.tm_mday = t.day;
    tm_new.tm_mon  = t.month - 1;
    tm_new.tm_year = t.year - 1900;

    tv->tv_sec = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t pico_rtc_init(void)
{
    rtc_init();

    datetime_t t;
    t.sec     = 0 ;
    t.min     = 0;
    t.hour    = 0;
    t.day     = 01;
    t.month   = 01;
    t.year    = 1970;
    t.dotw    = 4;
    rtc_set_datetime(&t);

    return RT_EOK;
}

static rt_err_t pico_rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    pico_rtc_get_timeval(&tv);
    *(time_t *) sec = tv.tv_sec;
    LOG_D("RTC: get rtc_time %d", *sec);

    return RT_EOK;
}

static rt_err_t pico_rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;
    datetime_t t;
    struct tm tm = {0};

    gmtime_r(sec, &tm);

    t.sec     = tm.tm_sec ;
    t.min     = tm.tm_min ;
    t.hour    = tm.tm_hour;
    t.day     = tm.tm_mday;
    t.month   = tm.tm_mon  + 1;
    t.year    = tm.tm_year + 1900;
    t.dotw    = tm.tm_wday;

    rtc_set_datetime(&t);
    LOG_D("RTC: set rtc_time");
#ifdef RT_USING_ALARM
    rt_alarm_update(&rtc_device.rtc_dev.parent, 1);
#endif
    return result;
}

static const struct rt_rtc_ops pico_rtc_ops =
{
    pico_rtc_init,
    pico_rtc_get_secs,
    pico_rtc_set_secs,
    RT_NULL,
    RT_NULL,
    pico_rtc_get_timeval,
    RT_NULL,
};

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    rtc_device.rtc_dev.ops = &pico_rtc_ops;
    result = rt_hw_rtc_register(&rtc_device.rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
