/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-03     Alex Yang    Add MCXC162 RTC0 support
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#include "fsl_clock.h"
#include "fsl_rtc.h"

#ifdef BSP_USING_RTC

static rt_rtc_dev_t mcxc162_rtc;

static rt_err_t mcxc162_rtc_init(void)
{
    rtc_config_t config;

    CLOCK_SetupFRO16KClocking(kCLOCK_Clk16kToSysAndCore);
    RTC_GetDefaultConfig(&config);
    RTC_Init(RTC0, &config);
    RTC_StartTimer(RTC0);

    return RT_EOK;
}

static rt_err_t mcxc162_rtc_get_secs(time_t *seconds)
{
    *seconds = (time_t)RTC0->TSR;

    return RT_EOK;
}

static rt_err_t mcxc162_rtc_set_secs(time_t *seconds)
{
    if ((rt_uint64_t)*seconds > 0xFFFFFFFFULL)
    {
        return -RT_EINVAL;
    }

    RTC_StopTimer(RTC0);
    RTC0->TSR = (uint32_t)*seconds;
    RTC_StartTimer(RTC0);
#ifdef RT_USING_ALARM
    rt_alarm_update(&mcxc162_rtc.parent, 1U);
#endif

    return RT_EOK;
}

static rt_err_t mcxc162_rtc_get_alarm(struct rt_rtc_wkalarm *alarm)
{
    time_t timestamp = (time_t)RTC0->TAR;
    struct tm date;

#ifdef RT_ALARM_USING_LOCAL_TIME
    localtime_r(&timestamp, &date);
#else
    gmtime_r(&timestamp, &date);
#endif
    alarm->enable = (RTC_GetEnabledInterrupts(RTC0) & kRTC_AlarmInterruptEnable) != 0U;
    alarm->tm_sec = date.tm_sec;
    alarm->tm_min = date.tm_min;
    alarm->tm_hour = date.tm_hour;
    alarm->tm_mday = date.tm_mday;
    alarm->tm_mon = date.tm_mon;
    alarm->tm_year = date.tm_year;

    return RT_EOK;
}

static rt_err_t mcxc162_rtc_set_alarm(struct rt_rtc_wkalarm *alarm)
{
    rtc_datetime_t date;
    struct tm calendar = {
        .tm_sec = alarm->tm_sec,
        .tm_min = alarm->tm_min,
        .tm_hour = alarm->tm_hour,
        .tm_mday = alarm->tm_mday,
        .tm_mon = alarm->tm_mon,
        .tm_year = alarm->tm_year,
    };
#ifdef RT_ALARM_USING_LOCAL_TIME
    time_t timestamp;
#endif

    if (!alarm->enable)
    {
        RTC_DisableInterrupts(RTC0, kRTC_AlarmInterruptEnable);
        DisableIRQ(RTC_IRQn);
        RTC_ClearStatusFlags(RTC0, kRTC_AlarmFlag);
        return RT_EOK;
    }

#ifdef RT_ALARM_USING_LOCAL_TIME
    calendar.tm_isdst = -1;
    timestamp = mktime(&calendar);
    if (timestamp == (time_t)-1)
    {
        return -RT_EINVAL;
    }
    gmtime_r(&timestamp, &calendar);
#endif
    date.second = (uint8_t)calendar.tm_sec;
    date.minute = (uint8_t)calendar.tm_min;
    date.hour = (uint8_t)calendar.tm_hour;
    date.day = (uint8_t)calendar.tm_mday;
    date.month = (uint8_t)(calendar.tm_mon + 1);
    date.year = (uint16_t)(calendar.tm_year + 1900);

    if (RTC_SetAlarm(RTC0, &date) != kStatus_Success || RTC0->TAR <= RTC0->TSR)
    {
        RTC_DisableInterrupts(RTC0, kRTC_AlarmInterruptEnable);
        DisableIRQ(RTC_IRQn);
        RTC_ClearStatusFlags(RTC0, kRTC_AlarmFlag);
        return -RT_EINVAL;
    }

    RTC_ClearStatusFlags(RTC0, kRTC_AlarmFlag);
    RTC_EnableInterrupts(RTC0, kRTC_AlarmInterruptEnable);
    NVIC_ClearPendingIRQ(RTC_IRQn);
    EnableIRQ(RTC_IRQn);

    return RT_EOK;
}

static const struct rt_rtc_ops mcxc162_rtc_ops = {
    .init = mcxc162_rtc_init,
    .get_secs = mcxc162_rtc_get_secs,
    .set_secs = mcxc162_rtc_set_secs,
    .get_alarm = mcxc162_rtc_get_alarm,
    .set_alarm = mcxc162_rtc_set_alarm,
    .get_timeval = RT_NULL,
    .set_timeval = RT_NULL,
};

void RTC_IRQHandler(void)
{
    rt_interrupt_enter();

    if ((RTC_GetStatusFlags(RTC0) & kRTC_AlarmFlag) != 0U)
    {
        RTC_ClearStatusFlags(RTC0, kRTC_AlarmFlag);
#ifdef RT_USING_ALARM
        rt_alarm_update(&mcxc162_rtc.parent, 1U);
#endif
    }

    rt_interrupt_leave();
    SDK_ISR_EXIT_BARRIER;
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    mcxc162_rtc.ops = &mcxc162_rtc_ops;

    result = rt_hw_rtc_register(&mcxc162_rtc, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        return result;
    }

    return rt_device_init(&mcxc162_rtc.parent);
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
