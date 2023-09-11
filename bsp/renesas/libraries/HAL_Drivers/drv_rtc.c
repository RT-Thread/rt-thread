/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-14     Mr.Tiger     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include <sys/time.h>
#include "hal_data.h"

#ifdef BSP_USING_ONCHIP_RTC

#define DBG_TAG              "drv.rtc"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

static rt_err_t ra_rtc_init(void)
{
    rt_err_t result = RT_EOK;

    if (R_RTC_Open(&g_rtc_ctrl, &g_rtc_cfg) != RT_EOK)
    {
        LOG_E("rtc init failed.");
        result = -RT_ERROR;
    }

    return result;
}

static time_t get_rtc_timestamp(void)
{
    struct tm tm_new = {0};
    rtc_time_t g_current_time = {0};

    R_RTC_CalendarTimeGet(&g_rtc_ctrl, &g_current_time);

    tm_new.tm_year  = g_current_time.tm_year;
    tm_new.tm_mon   = g_current_time.tm_mon;
    tm_new.tm_mday  = g_current_time.tm_mday;

    tm_new.tm_hour  = g_current_time.tm_hour;
    tm_new.tm_min   = g_current_time.tm_min;
    tm_new.tm_sec   = g_current_time.tm_sec;

    tm_new.tm_wday  = g_current_time.tm_wday;
    tm_new.tm_yday  = g_current_time.tm_yday;
    tm_new.tm_isdst = g_current_time.tm_isdst;

    return timegm(&tm_new);
}

static rt_err_t ra_get_secs(time_t *sec)
{
    *(rt_uint32_t *)sec = get_rtc_timestamp();
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)sec);

    return RT_EOK;
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    struct tm now;
    rtc_time_t g_current_time = {0};
    gmtime_r(&time_stamp, &now);
    if (now.tm_year < 100)
    {
        return -RT_ERROR;
    }

    g_current_time.tm_sec    = now.tm_sec ;
    g_current_time.tm_min    = now.tm_min ;
    g_current_time.tm_hour   = now.tm_hour;
    g_current_time.tm_mday   = now.tm_mday;
    g_current_time.tm_mon    = now.tm_mon;
    g_current_time.tm_year   = now.tm_year;
    g_current_time.tm_wday   = now.tm_wday;
    g_current_time.tm_yday   = now.tm_yday;

    if (R_RTC_CalendarTimeSet(&g_rtc_ctrl, &g_current_time) != FSP_SUCCESS)
    {
        LOG_E("set rtc time failed.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t ra_set_secs(time_t *sec)
{

    rt_err_t result = RT_EOK;

    if (set_rtc_time_stamp(*(rt_uint32_t *)sec))
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)sec);

    return result;
}

#ifdef RT_USING_ALARM
static rt_err_t ra_get_alarm(struct rt_rtc_wkalarm *alarm)
{
    rt_err_t result = RT_EOK;
    struct rt_rtc_wkalarm *wkalarm = alarm;
    rtc_alarm_time_t alarm_time_get =
    {
        .sec_match        =  RT_FALSE,
        .min_match        =  RT_FALSE,
        .hour_match       =  RT_FALSE,
        .mday_match       =  RT_FALSE,
        .mon_match        =  RT_FALSE,
        .year_match       =  RT_FALSE,
        .dayofweek_match  =  RT_FALSE,
    };

    if (RT_EOK == R_RTC_CalendarAlarmGet(&g_rtc_ctrl, &alarm_time_get))
    {
        wkalarm->tm_hour = alarm_time_get.time.tm_hour;
        wkalarm->tm_min  = alarm_time_get.time.tm_min;
        wkalarm->tm_sec  = alarm_time_get.time.tm_sec;
    }
    else
    {
        LOG_E("Calendar alarm Get failed.");
    }

    return result;
}

static rt_err_t ra_set_alarm(struct rt_rtc_wkalarm *alarm)
{
    rt_err_t result = RT_EOK;
    struct rt_rtc_wkalarm *wkalarm = alarm;
    rtc_alarm_time_t alarm_time_set =
    {
        .sec_match        =  RT_TRUE,
        .min_match        =  RT_TRUE,
        .hour_match       =  RT_TRUE,
        .mday_match       =  RT_FALSE,
        .mon_match        =  RT_FALSE,
        .year_match       =  RT_FALSE,
        .dayofweek_match  =  RT_FALSE,
    };

    alarm_time_set.time.tm_hour = wkalarm->tm_hour;
    alarm_time_set.time.tm_min  = wkalarm->tm_min;
    alarm_time_set.time.tm_sec  = wkalarm->tm_sec;
    if (1 == wkalarm->enable)
    {
        if (RT_EOK != R_RTC_CalendarAlarmSet(&g_rtc_ctrl, &alarm_time_set))
        {
            LOG_E("Calendar alarm Set failed.");
            result = -RT_ERROR;
        }
    }
    else
    {
        alarm_time_set.sec_match        =  RT_FALSE;
        alarm_time_set.min_match        =  RT_FALSE;
        alarm_time_set.hour_match       =  RT_FALSE;
        if (RT_EOK != R_RTC_CalendarAlarmSet(&g_rtc_ctrl, &alarm_time_set))
        {
            LOG_E("Calendar alarm Stop failed.");
            result = -RT_ERROR;
        }
    }
    return result;
}
#endif /* RT_USING_ALARM */

void rtc_callback(rtc_callback_args_t *p_args)
{
#ifdef RT_USING_ALARM
    static rt_device_t ra_device;
    if (RTC_EVENT_ALARM_IRQ == p_args->event)
    {
        rt_alarm_update(ra_device, 1);
    }
#endif
}

static const struct rt_rtc_ops ra_rtc_ops =
{
    .init      = ra_rtc_init,
    .get_secs  = ra_get_secs,
    .set_secs  = ra_set_secs,
#ifdef RT_USING_ALARM
    .set_alarm = ra_set_alarm,
    .get_alarm = ra_get_alarm,
#endif
};

static rt_rtc_dev_t ra_rtc_dev;

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    ra_rtc_dev.ops = &ra_rtc_ops;

    result = rt_hw_rtc_register(&ra_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif
