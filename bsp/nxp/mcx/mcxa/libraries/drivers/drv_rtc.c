/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-19     Alex Yang    Add MCXA346 RTC driver for RT-Thread
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#ifdef BSP_USING_RTC

#define DBG_TAG    "drv.rtc"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#include "fsl_rtc.h"
#include "fsl_clock.h"


/* Get RTC timestamp */
static time_t get_rtc_timestamp(void)
{
    rtc_datetime_t datetime;
    struct tm tm_new;

    /* Get current time from RTC */
    RTC_GetDatetime(RTC0, &datetime);

    tm_new.tm_sec  = datetime.second;
    tm_new.tm_min  = datetime.minute;
    tm_new.tm_hour = datetime.hour;
    tm_new.tm_mday = datetime.day;
    tm_new.tm_mon  = datetime.month - 1;
    tm_new.tm_year = datetime.year - 1900;
    tm_new.tm_isdst = 0;

    LOG_D("get rtc time: %04d-%02d-%02d %02d:%02d:%02d",
          datetime.year, datetime.month, datetime.day,
          datetime.hour, datetime.minute, datetime.second);

    return mktime(&tm_new);
}

/* Set RTC timestamp */
static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    rtc_datetime_t datetime;
    struct tm *time_tm;

    time_tm = gmtime(&time_stamp);
    if (time_tm->tm_year < 70) /* Year should be >= 1970 */
    {
        LOG_E("Invalid year: %d", time_tm->tm_year + 1900);
        return -RT_ERROR;
    }

    /* Convert to RTC datetime format */
    datetime.year   = time_tm->tm_year + 1900;
    datetime.month  = time_tm->tm_mon + 1;
    datetime.day    = time_tm->tm_mday;
    datetime.hour   = time_tm->tm_hour;
    datetime.minute = time_tm->tm_min;
    datetime.second = time_tm->tm_sec;

    /* Set RTC time */
    RTC_StopTimer(RTC0);

    RTC_SetDatetime(RTC0, &datetime);

    RTC_StartTimer(RTC0);

    LOG_D("set rtc time: %04d-%02d-%02d %02d:%02d:%02d",
          datetime.year, datetime.month, datetime.day,
          datetime.hour, datetime.minute, datetime.second);

    return RT_EOK;
}

/* RTC configuration */
static rt_err_t rt_rtc_config(void)
{
    rtc_config_t rtc_config;

    /* Get default RTC configuration */
    RTC_GetDefaultConfig(&rtc_config);

    /* Initialize RTC - Note: RTC_Init returns void, not status */
    RTC_Init(RTC0, &rtc_config);

    /* Start RTC timer */
    RTC_StartTimer(RTC0);

    return RT_EOK;
}

/* RTC initialization */
static rt_err_t _rtc_init(void)
{

    /* Configure RTC */
    if (rt_rtc_config() != RT_EOK)
    {
        LOG_E("RTC config failed.");
        return -RT_ERROR;
    }

    LOG_D("RTC initialized successfully");
    return RT_EOK;
}

/* Get RTC seconds */
static rt_err_t _rtc_get_secs(time_t *args)
{
    RT_ASSERT(args != RT_NULL);

    *args = get_rtc_timestamp();
    LOG_D("RTC: get rtc_time %x", *args);

    return RT_EOK;
}

/* Set RTC seconds */
static rt_err_t _rtc_set_secs(time_t *args)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(args != RT_NULL);

    if (set_rtc_time_stamp(*args) != RT_EOK)
    {
        result = -RT_ERROR;
    }
    LOG_D("RTC: set rtc_time %x", *args);

    return result;
}

/* Get RTC alarm */
static rt_err_t _rtc_get_alarm(struct rt_rtc_wkalarm *wkalarm)
{
    rtc_datetime_t datetime;

    RT_ASSERT(wkalarm != RT_NULL);

    /* Get alarm time from RTC */
    RTC_GetAlarm(RTC0, &datetime);

    /* Convert to wkalarm format */
    wkalarm->tm_sec  = datetime.second;
    wkalarm->tm_min  = datetime.minute;
    wkalarm->tm_hour = datetime.hour;
    wkalarm->tm_mday = datetime.day;
    wkalarm->tm_mon  = datetime.month - 1;
    wkalarm->tm_year = datetime.year - 1900;

    /* Check if alarm is enabled */
    wkalarm->enable = (RTC_GetEnabledInterrupts(RTC0) & kRTC_AlarmInterruptEnable) ? 1 : 0;

    LOG_D("RTC: get alarm %04d-%02d-%02d %02d:%02d:%02d (%s)",
          datetime.year, datetime.month, datetime.day,
          datetime.hour, datetime.minute, datetime.second,
          wkalarm->enable ? "ENABLED" : "DISABLED");

    return RT_EOK;
}

/* Set RTC alarm */
static rt_err_t _rtc_set_alarm(struct rt_rtc_wkalarm *wkalarm)
{
    rtc_datetime_t datetime;

    RT_ASSERT(wkalarm != RT_NULL);

    /* Convert from wkalarm format */
    datetime.year   = wkalarm->tm_year + 1900;
    datetime.month  = wkalarm->tm_mon + 1;
    datetime.day    = wkalarm->tm_mday;
    datetime.hour   = wkalarm->tm_hour;
    datetime.minute = wkalarm->tm_min;
    datetime.second = wkalarm->tm_sec;

    /* Set alarm time */
    RTC_SetAlarm(RTC0, &datetime);

    /* Enable/disable alarm interrupt */
    if (wkalarm->enable)
    {
        RTC_EnableInterrupts(RTC0, kRTC_AlarmInterruptEnable);
        EnableIRQ(RTC_IRQn);  /* Use RTC_IRQn instead of RTC0_IRQn */
        LOG_D("RTC alarm enabled");
    }
    else
    {
        RTC_DisableInterrupts(RTC0, kRTC_AlarmInterruptEnable);
        LOG_D("RTC alarm disabled");
    }

    LOG_D("RTC: set alarm %04d-%02d-%02d %02d:%02d:%02d",
          datetime.year, datetime.month, datetime.day,
          datetime.hour, datetime.minute, datetime.second);

    return RT_EOK;
}

/* RTC operations structure */
static const struct rt_rtc_ops _rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    _rtc_get_alarm,
    _rtc_set_alarm,
    RT_NULL,  /* get_timeval */
    RT_NULL,  /* set_timeval */
};

static rt_rtc_dev_t mcxa_rtc_dev;

/* RTC interrupt handler */
void RTC_IRQHandler(void)
{
    rt_interrupt_enter();

    /* Get interrupt status */
    uint32_t status = RTC_GetStatusFlags(RTC0);

    /* Handle alarm interrupt */
    if (status & kRTC_AlarmFlag)
    {
        /* Clear alarm flag */
        RTC_ClearStatusFlags(RTC0, kRTC_AlarmFlag);

        LOG_D("RTC alarm triggered");

        /* If alarm framework is available, notify it */
#ifdef RT_USING_ALARM
        /* Send alarm event to alarm thread */
        rt_event_send(&_container.event, 1);
#endif
    }

    /* Handle seconds interrupt if needed */
    if (status & kRTC_SecondsInterruptEnable)
    {
        LOG_D("RTC seconds interrupt");
    }

    rt_interrupt_leave();
}

/* Hardware RTC initialization */
int rt_hw_rtc_init(void)
{
    rt_err_t result;

    /* Set RTC operations */
    mcxa_rtc_dev.ops = &_rtc_ops;

    /* Register RTC device */
    result = rt_hw_rtc_register(&mcxa_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("RTC register failed, err code: %d", result);
        return result;
    }

    LOG_D("RTC init success");
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
