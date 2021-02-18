/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          format file
 */

#include "drv_rtc.h"

#ifdef RT_USING_RTC
#ifdef BSP_USING_RTC

//#define DRV_DEBUG
#define LOG_TAG "drv.rtc"
#include <drv_log.h>

static struct rt_device rtc_device;

static uint32_t calcWeekDay(uint32_t year, uint32_t month, uint32_t date)
{
    uint32_t i, cnt = 0;
    const uint32_t daysOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (i = 1; i < month; i++)
        cnt += daysOfMonth[i];

    cnt += date;

    if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)) && (month >= 3))
        cnt += 1;

    cnt += (year - 1901) * 365;

    for (i = 1901; i < year; i++)
    {
        if ((i % 4 == 0) && ((i % 100 != 0) || (i % 400 == 0)))
            cnt += 1;
    }

    return (cnt + 1) % 7;
}

static time_t swm_get_rtc_time_stamp(void)
{
    RTC_DateTime get_datetime = {0};
    struct tm tm_new;

    RTC_GetDateTime(RTC, &get_datetime);

    tm_new.tm_sec = get_datetime.Second;
    tm_new.tm_min = get_datetime.Minute;
    tm_new.tm_hour = get_datetime.Hour;
    tm_new.tm_mday = get_datetime.Date;
    tm_new.tm_mon = get_datetime.Month - 1;
    tm_new.tm_year = get_datetime.Year - 1900;

    LOG_D("get rtc time.");
    return mktime(&tm_new);
}
static rt_err_t swm_set_rtc_time_stamp(time_t time_stamp)
{
    RTC_DateTime set_datetime = {0};
    struct tm *p_tm;

    p_tm = gmtime(&time_stamp);

    set_datetime.Second = p_tm->tm_sec;
    set_datetime.Minute = p_tm->tm_min;
    set_datetime.Hour = p_tm->tm_hour;
    set_datetime.Date = p_tm->tm_mday;
    set_datetime.Month = p_tm->tm_mon + 1;
    set_datetime.Year = p_tm->tm_year + 1900;
    //    datetime.Day = p_tm->tm_wday;

    RTC_Stop(RTC);
    while (RTC->CFGABLE == 0)
        ;
    RTC->MINSEC = (set_datetime.Second << RTC_MINSEC_SEC_Pos) |
                  (set_datetime.Minute << RTC_MINSEC_MIN_Pos);
    RTC->DATHUR = (set_datetime.Hour << RTC_DATHUR_HOUR_Pos) |
                  ((set_datetime.Date) << RTC_DATHUR_DATE_Pos);
    RTC->MONDAY = (calcWeekDay(set_datetime.Year, set_datetime.Month, set_datetime.Date)
                   << RTC_MONDAY_DAY_Pos) |
                  ((set_datetime.Month) << RTC_MONDAY_MON_Pos);
    RTC->YEAR = set_datetime.Year - 1901;
    RTC->LOAD = 1 << RTC_LOAD_TIME_Pos;
    RTC_Start(RTC);

    LOG_D("set rtc time.");
    return RT_EOK;
}

static rt_err_t swm_rtc_control(rt_device_t rtc_device, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(rtc_device != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = swm_get_rtc_time_stamp();
        LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        if (swm_set_rtc_time_stamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);
        break;
    default:
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops swm_rtc_ops =
    {
        RT_NULL,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        swm_rtc_control};
#endif

static void swm_rtc_init(void)
{
    RTC_InitStructure rtc_initstruct;

    rtc_initstruct.Year = 2020;
    rtc_initstruct.Month = 6;
    rtc_initstruct.Date = 8;
    rtc_initstruct.Hour = 12;
    rtc_initstruct.Minute = 0;
    rtc_initstruct.Second = 0;
    rtc_initstruct.SecondIEn = 0;
    rtc_initstruct.MinuteIEn = 0;
    RTC_Init(RTC, &rtc_initstruct);
    RTC_Start(RTC);
}

static rt_err_t rt_hw_rtc_register(rt_device_t rtc_device, const char *name, rt_uint32_t flag)
{
    RT_ASSERT(rtc_device != RT_NULL);

    swm_rtc_init();

#ifdef RT_USING_DEVICE_OPS
    rtc_device->ops = &swm_rtc_ops;
#else
    rtc_device->init = RT_NULL;
    rtc_device->open = RT_NULL;
    rtc_device->close = RT_NULL;
    rtc_device->read = RT_NULL;
    rtc_device->write = RT_NULL;
    rtc_device->control = swm_rtc_control;
#endif
    rtc_device->type = RT_Device_Class_RTC;
    rtc_device->rx_indicate = RT_NULL;
    rtc_device->tx_complete = RT_NULL;
    rtc_device->user_data = RT_NULL;

    /* register a character device */
    return rt_device_register(rtc_device, name, flag);
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;
    result = rt_hw_rtc_register(&rtc_device, "rtc", RT_DEVICE_FLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
#endif /* RT_USING_RTC */
