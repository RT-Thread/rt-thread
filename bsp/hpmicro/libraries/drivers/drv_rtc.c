/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2021-09-19   HPMicro     First version
 * 2023-05-08   HPMicro     Adapt RT-Thread V5.0.0
 * 2025-05-23   HPMicro     Support setting and getting timeval
 * 2025-05-26   HPMicro     Support 64-bit time_t and alarm set/getting
 */
#include "board.h"
#include "drv_rtc.h"
#include "hpm_rtc_drv.h"
#include "hpm_bpor_drv.h"

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#ifdef RT_USING_RTC

/*******************************************************************************************
 *
 *  Prototypes
 *
 ******************************************************************************************/
static rt_err_t hpm_rtc_init(rt_device_t dev);
static rt_err_t hpm_rtc_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t hpm_rtc_close(rt_device_t dev);
static rt_ssize_t hpm_rtc_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size);
static rt_ssize_t hpm_rtc_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size);
static rt_err_t hpm_rtc_control(rt_device_t dev, int cmd, void *args);

static time_t hpm_rtc_get_timestamp(void);
static int hpm_rtc_set_timestamp(time_t timestamp);
static int hpm_rtc_set_alarm(struct rt_rtc_wkalarm *alarm);
static int hpm_rtc_get_alarm(struct rt_rtc_wkalarm *alarm);

/*******************************************************************************************
 *
 *  Variables
 *
 ******************************************************************************************/
#ifdef RT_USING_DEVICE_OPS
const struct rt_device_ops hpm_rtc_ops = {
    .init = hpm_rtc_init,
    .open = hpm_rtc_open,
    .close = hpm_rtc_close,
    .read = hpm_rtc_read,
    .write = hpm_rtc_write,
    .control = hpm_rtc_control,
};
#endif
static struct rt_device hpm_rtc= {
    .type = RT_Device_Class_RTC,
#ifdef RT_USING_DEVICE_OPS
    .ops = &hpm_rtc_ops,
#else
    .init = hpm_rtc_init,
    .open = hpm_rtc_open,
    .close = hpm_rtc_close,
    .read = hpm_rtc_read,
    .write = hpm_rtc_write,
    .control = hpm_rtc_control,
#endif
};

/*****************************************************
 * RTC interrupt handler
******************************************************/
#ifdef RT_USING_ALARM
void rtc_isr(void)
{
    uint32_t rtc_alarm_flag = rtc_get_alarm_flags(HPM_RTC);
    if ((rtc_alarm_flag & RTC_ALARM_FLAG_ALARM0_MASK) != 0)
    {
        rt_alarm_update(&hpm_rtc, 1);
    }
    rtc_clear_alarm_flags(HPM_RTC, RTC_ALARM_FLAG_ALARM0_MASK | RTC_ALARM_FLAG_ALARM1_MASK);
}
RTT_DECLARE_EXT_ISR_M(IRQn_RTC, rtc_isr);
#endif
/*******************************************************************************************
 *
 *  Codes
 *
 ******************************************************************************************/
static rt_err_t hpm_rtc_init(rt_device_t dev)
{
    /* Enable Power retention mode for the battery domain */
    bpor_enable_reg_value_retention(HPM_BPOR);
    return RT_EOK;
}
static rt_err_t hpm_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}
static rt_err_t hpm_rtc_close(rt_device_t dev)
{
    return RT_EOK;
}
static rt_ssize_t hpm_rtc_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
    return 0;
}
static rt_ssize_t hpm_rtc_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size)
{
    return 0;
}
static rt_err_t hpm_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    rt_err_t err = RT_EOK;

    struct timeval tv;

    switch(cmd) {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
            if (sizeof(uint32_t) == sizeof(time_t)) {
                *(uint32_t *)args = hpm_rtc_get_timestamp();
            } else if (sizeof(uint64_t) == sizeof(time_t)) {
                *(uint64_t *)args = hpm_rtc_get_timestamp();
            }
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIME:
            hpm_rtc_set_timestamp(*(time_t *)args);
            break;
        case RT_DEVICE_CTRL_RTC_GET_TIMEVAL:
            tv = rtc_get_timeval(HPM_RTC);
            memcpy(args, &tv, sizeof(tv));
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIMEVAL:
            memcpy(&tv, args, sizeof(tv));
            rtc_config_time(HPM_RTC, tv.tv_sec);
            break;
        case RT_DEVICE_CTRL_RTC_SET_ALARM:
            err = hpm_rtc_set_alarm((struct rt_rtc_wkalarm *)args);
            break;
        case RT_DEVICE_CTRL_RTC_GET_ALARM:
            err = hpm_rtc_get_alarm((struct rt_rtc_wkalarm *)args);
            break;
        default:
            err = RT_EINVAL;
            break;
    }

    return err;
}

static time_t hpm_rtc_get_timestamp(void)
{
    time_t time = rtc_get_time(HPM_RTC);

    return time;
}

static int hpm_rtc_set_timestamp(time_t timestamp)
{
    (void)rtc_config_time(HPM_RTC, timestamp);

    return RT_EOK;
}

static int hpm_rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    rtc_alarm_config_t config;
    time_t now;
    time_t alarm_time;
    struct tm tm_alarm = {0};
    if (alarm->enable == RT_TRUE) {
        /* Clear all pending interrupt flags first */
        rtc_clear_alarm_flag(HPM_RTC, 0);
        rtc_clear_alarm_flag(HPM_RTC, 1);
        tm_alarm.tm_sec = alarm->tm_sec;
        tm_alarm.tm_min = alarm->tm_min;
        tm_alarm.tm_hour = alarm->tm_hour;
        tm_alarm.tm_mday = alarm->tm_mday;
        tm_alarm.tm_mon = alarm->tm_mon;
        tm_alarm.tm_year = alarm->tm_year;
#ifdef RT_ALARM_USING_LOCAL_TIME
        alarm_time = mktime(&tm_alarm);
#else
        alarm_time = timegm(&tm_alarm);
#endif
        now = rtc_get_time(HPM_RTC);
        if (alarm_time <= now) {
            return -RT_ERROR;
        }
        config.period = alarm_time;
        config.type = RTC_ALARM_TYPE_ABSOLUTE_TIME_ONE_SHOT;
        config.index = 0;
        if (rtc_config_alarm(HPM_RTC, &config) != status_success) {
            return -RT_ERROR;
        }
        rtc_enable_alarm_interrupt(HPM_RTC, 0, true);
        intc_m_enable_irq_with_priority(IRQn_RTC, 1);
    } else {
        rtc_enable_alarm_interrupt(HPM_RTC, 0, false);
        intc_m_disable_irq(IRQn_RTC);
    }
    return RT_EOK;
#else
    return -RT_EINVAL;
#endif
}

static int hpm_rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
#ifdef RT_USING_ALARM
    time_t alarm_time;
    struct tm alarm_tm;
    if (RTC_ALARM_EN_ENABLE0_GET(HPM_RTC->ALARM_EN) == 0) {
        alarm->enable = RT_FALSE;
    } else {
        alarm->enable = RT_TRUE;
    }
    alarm_time = RTC_ALARM0_ALARM_GET(HPM_RTC->ALARM0);
#ifdef RT_ALARM_USING_LOCAL_TIME
    localtime_r(&alarm_time, &alarm_tm);
#else
    gmtime_r(&alarm_time, &alarm_tm);
#endif
    alarm->tm_sec = alarm_tm.tm_sec;
    alarm->tm_min = alarm_tm.tm_min;
    alarm->tm_hour = alarm_tm.tm_hour;
    alarm->tm_mday = alarm_tm.tm_mday;
    alarm->tm_mon = alarm_tm.tm_mon;
    alarm->tm_year = alarm_tm.tm_year;
    return RT_EOK;
#else
    return -RT_EINVAL;
#endif
}

int rt_hw_rtc_init(void)
{
    rt_err_t err = RT_EOK;

    err = rt_device_register(&hpm_rtc, "rtc", RT_DEVICE_FLAG_RDWR);
    if (err != RT_EOK) {
        LOG_E("rt device %s failed, status=%d\n", "rtc", err);
        return err;
    }

    rt_device_open(&hpm_rtc, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* RT_USING_RTC */
