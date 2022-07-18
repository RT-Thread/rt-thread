/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-08-31   AisinoChip    first add to bsp
 */

#include "board.h"
#include <sys/time.h>
#include <rtdevice.h>

#ifdef BSP_USING_RTC

static RTC_ConfigTypeDef RTC_Handle;

rt_inline rt_uint8_t dec2hex(rt_uint8_t dec)
{
    return ((dec / 10) << 4) + (dec % 10);
}

rt_inline rt_uint8_t hex2dec(rt_uint8_t hex)
{
    return ((hex / 16) * 10) + (hex % 16);
}

static time_t get_rtc_timestamp(void)
{
    RTC_TimeTypeDef RTC_TimeStruct = {0};
    RTC_DateTypeDef RTC_DateStruct = {0};
    struct tm tm_new = {0};

    HAL_RTC_GetTime(&RTC_TimeStruct);
    HAL_RTC_GetDate(&RTC_DateStruct);

    tm_new.tm_sec  = hex2dec(RTC_TimeStruct.u8_Seconds);
    tm_new.tm_min  = hex2dec(RTC_TimeStruct.u8_Minutes);
    tm_new.tm_hour = hex2dec(RTC_TimeStruct.u8_Hours);
    tm_new.tm_mday = hex2dec(RTC_DateStruct.u8_Date);
    tm_new.tm_mon  = hex2dec(RTC_DateStruct.u8_Month) - 1;
    tm_new.tm_year = hex2dec(RTC_DateStruct.u8_Year) + 100;

    return timegm(&tm_new);
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    RTC_TimeTypeDef RTC_TimeStruct = {0};
    RTC_DateTypeDef RTC_DateStruct = {0};
    struct tm now;

    gmtime_r(&time_stamp, &now);
    if (now.tm_year < 100)
    {
        return -RT_ERROR;
    }

    RTC_TimeStruct.u8_Seconds = dec2hex(now.tm_sec);
    RTC_TimeStruct.u8_Minutes = dec2hex(now.tm_min);
    RTC_TimeStruct.u8_Hours   = dec2hex(now.tm_hour);
    RTC_DateStruct.u8_Date    = dec2hex(now.tm_mday);
    RTC_DateStruct.u8_Month   = dec2hex(now.tm_mon + 1);
    RTC_DateStruct.u8_Year    = dec2hex(now.tm_year - 100);
    RTC_DateStruct.u8_WeekDay = dec2hex(now.tm_wday) + 1;

    HAL_RTC_SetTime(&RTC_TimeStruct);
    HAL_RTC_SetDate(&RTC_DateStruct);

    return RT_EOK;
}

static rt_err_t _rtc_init(void)
{
    RTC_Handle.u32_ClockSource       = RTC_CLOCK_XTL;
    RTC_Handle.u32_Compensation      = COMPENSATION_INCREASE;
    RTC_Handle.u32_CompensationValue = 0x05;

    HAL_RTC_Config(&RTC_Handle);

    return RT_EOK;
}

static rt_err_t _rtc_get_secs(void *args)
{
    *(rt_uint32_t *)args = get_rtc_timestamp();
    return RT_EOK;
}

static rt_err_t _rtc_set_secs(void *args)
{
    rt_err_t result = RT_EOK;
    if (set_rtc_time_stamp(*(rt_uint32_t *)args))
    {
        result = -RT_ERROR;
    }

    return result;
}

static const struct rt_rtc_ops acm32_rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

static rt_rtc_dev_t acm32_rtc_dev;

static int rt_hw_rtc_init(void)
{
    acm32_rtc_dev.ops = &acm32_rtc_ops;

    return rt_hw_rtc_register(&acm32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_RTC */

