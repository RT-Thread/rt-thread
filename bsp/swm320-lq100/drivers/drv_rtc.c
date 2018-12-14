/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>
#include <time.h>

struct rt_device_rtc;
struct rt_rtc_ops
{
    rt_err_t (*control)(struct rt_device_rtc *device, int cmd, void *arg);
};
struct rt_device_rtc
{
    struct rt_device parent;
    const struct rt_rtc_ops *ops;
};

static rt_err_t rtc_control(struct rt_device_rtc *device, int cmd, void *arg);

const static struct rt_rtc_ops rtc_ops = {rtc_control};
static struct rt_device_rtc rtc_device;

/**
 * This function will get the weed day from a date.
 *
 * @param year the year of time
 * @param month the month of time
 * @param date the date of time
 *
 * @return the week day 0 ~ 6 : sun ~ sat
 *
 * @note No
 */
static uint32_t calcWeekDay(uint32_t year, uint32_t month, uint32_t date)
{
    uint32_t i, cnt = 0;
    const uint32_t daysOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (i = 1; i < month; i++)
        cnt += daysOfMonth[i];

    cnt += date;

    if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)) &&
            (month >= 3))
        cnt += 1;

    cnt += (year - 1901) * 365;

    for (i = 1901; i < year; i++)
    {
        if ((i % 4 == 0) && ((i % 100 != 0) || (i % 400 == 0)))
            cnt += 1;
    }

    return (cnt + 1) % 7;
}

static void RTC_SetDateTime(RTC_TypeDef *RTCx, RTC_DateTime *dateTime)
{
    RTC_Stop(RTCx);

    while (RTCx->CFGABLE == 0)
        ;

    RTCx->MINSEC = (dateTime->Second << RTC_MINSEC_SEC_Pos) |
                   (dateTime->Minute << RTC_MINSEC_MIN_Pos);

    RTCx->DATHUR = (dateTime->Hour << RTC_DATHUR_HOUR_Pos) |
                   ((dateTime->Date - 1) << RTC_DATHUR_DATE_Pos);

    RTCx->MONDAY = (calcWeekDay(dateTime->Year, dateTime->Month, dateTime->Date)
                    << RTC_MONDAY_DAY_Pos) |
                   ((dateTime->Month - 1) << RTC_MONDAY_MON_Pos);

    RTCx->YEAR = dateTime->Year - 1901;

    RTCx->LOAD = 1 << RTC_LOAD_TIME_Pos;

    RTC_Start(RTC);
}

static rt_err_t rtc_control(struct rt_device_rtc *device, int cmd, void *arg)
{
    RT_ASSERT(device)

    struct tm time_temp;
    struct tm *pNow;
    RTC_DateTime dateTime;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        RTC_GetDateTime(RTC, &dateTime);
        time_temp.tm_sec = dateTime.Second;
        time_temp.tm_min = dateTime.Minute;
        time_temp.tm_hour = dateTime.Hour;
        time_temp.tm_mday = dateTime.Date;
        time_temp.tm_mon = dateTime.Month - 1;
        time_temp.tm_year = dateTime.Year - 1900;
        *((time_t *)arg) = mktime(&time_temp);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        rt_enter_critical();
        /* converts calendar time time into local time. */
        pNow = localtime((const time_t *)arg);
        /* copy the statically located variable */
        memcpy(&time_temp, pNow, sizeof(struct tm));
        /* unlock scheduler. */
        rt_exit_critical();

        dateTime.Hour = time_temp.tm_hour;
        dateTime.Minute = time_temp.tm_min;
        dateTime.Second = time_temp.tm_sec;
        dateTime.Year = time_temp.tm_year + 1900;
        dateTime.Month = time_temp.tm_mon + 1;
        dateTime.Date = time_temp.tm_mday;
        RTC_SetDateTime(RTC, &dateTime);
        break;
    case RT_DEVICE_CTRL_RTC_GET_ALARM:

        break;
    case RT_DEVICE_CTRL_RTC_SET_ALARM:

        break;
    default:
        break;
    }

    return RT_EOK;
}

static rt_size_t swm320_rtc_read(rt_device_t dev,
                                 rt_off_t pos,
                                 void *buffer,
                                 rt_size_t size)
{
    RTC_GetDateTime(RTC, (RTC_DateTime *)buffer);

    return size;
}

static rt_size_t swm320_rtc_write(rt_device_t dev,
                                  rt_off_t pos,
                                  const void *buffer,
                                  rt_size_t size)
{
    RTC_SetDateTime(RTC, (RTC_DateTime *)buffer);

    return size;
}

static rt_err_t swm320_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct rt_device_rtc *rtc = (struct rt_device_rtc *)dev;

    if (rtc->ops->control)
    {
        result = rtc->ops->control(rtc, cmd, args);
    }

    return result;
}

static rt_err_t rt_device_rtc_register(struct rt_device_rtc *device,
                                       const char *name,
                                       const struct rt_rtc_ops *ops)
{
    rt_err_t result = RT_EOK;

    memset(device, 0, sizeof(struct rt_device_rtc));

    device->parent.type = RT_Device_Class_RTC;

    device->parent.init = RT_NULL;
    device->parent.open = RT_NULL;
    device->parent.close = RT_NULL;
    device->parent.read = swm320_rtc_read;
    device->parent.write = swm320_rtc_write;
    device->parent.control = swm320_rtc_control;

    device->ops = ops;

    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

static int rtc_register(RTC_TypeDef *RTCx, const char *name)
{
    RTC_InitStructure RTC_initStruct;
    struct rt_device_rtc *p_rtc_device;
    const struct rt_rtc_ops *pops = &rtc_ops;

    RTC_initStruct.Year = 2018;
    RTC_initStruct.Month = 1;
    RTC_initStruct.Date = 1;
    RTC_initStruct.Hour = 12;
    RTC_initStruct.Minute = 0;
    RTC_initStruct.Second = 0;
    RTC_initStruct.SecondIEn = 0;
    RTC_initStruct.MinuteIEn = 0;
    RTC_Init(RTCx, &RTC_initStruct);

    RTC_Start(RTC);

    p_rtc_device = &rtc_device;
    rt_device_rtc_register(p_rtc_device, name, pops);

    return RT_EOK;
}

int rt_hw_rtc_init(void)
{
    int result = 0;
#ifdef BSP_USING_RTC
    result = rtc_register(RTC, "rtc");
#endif

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
