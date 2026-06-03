/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-15     Liuguang     the first version.
 * 2019-07-19     Magicoe      The first version for LPC55S6x
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "drv_rtc.h"
#include "fsl_common.h"
#include "fsl_rtc.h"

#ifdef RT_USING_RTC

static rt_err_t lpc_get_timestamp(time_t *timestamp)
{
    struct tm tm_new = {0};
    rtc_datetime_t rtcDate;

    /* Get date time */
    RTC_GetDatetime(RTC, &rtcDate);

    tm_new.tm_sec  = rtcDate.second;
    tm_new.tm_min  = rtcDate.minute;
    tm_new.tm_hour = rtcDate.hour;

    tm_new.tm_mday = rtcDate.day;
    tm_new.tm_mon  = rtcDate.month - 1;
    tm_new.tm_year = rtcDate.year - 1900;

    timegm(&tm_new);
    *timestamp = timegm(&tm_new);
    return RT_EOK;
}

static int lpc_set_timestamp(time_t timestamp)
{
    struct tm now;
    rtc_datetime_t rtcDate;

    gmtime_r(&timestamp, &now);

    rtcDate.second = now.tm_sec ;
    rtcDate.minute = now.tm_min ;
    rtcDate.hour   = now.tm_hour;

    rtcDate.day    = now.tm_mday;
    rtcDate.month  = now.tm_mon  + 1;
    rtcDate.year   = now.tm_year + 1900;

    /* RTC time counter has to be stopped before setting the date & time in the TSR register */
    RTC_StopTimer(RTC);

    /* Set RTC time to default */
    RTC_SetDatetime(RTC, &rtcDate);

    /* Start the RTC time counter */
    RTC_StartTimer(RTC);

    return RT_EOK;
}

static rt_err_t lpc_rtc_init(rt_device_t dev)
{
    /* Init RTC */
    RTC_Init(RTC);

    /* Start the RTC time counter */
    RTC_StartTimer(RTC);

    return RT_EOK;
}

static rt_err_t lpc_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t lpc_rtc_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t lpc_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return 0;
}

static rt_ssize_t lpc_rtc_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t lpc_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch(cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
        {
            lpc_get_timestamp(args);
        }
        break;

        case RT_DEVICE_CTRL_RTC_SET_TIME:
        {
            lpc_set_timestamp(*(time_t *)args);
        }
        break;

        default:
            return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_device device =
{
    .type    = RT_Device_Class_RTC,
    .init    = lpc_rtc_init,
    .open    = lpc_rtc_open,
    .close   = lpc_rtc_close,
    .read    = lpc_rtc_read,
    .write   = lpc_rtc_write,
    .control = lpc_rtc_control,
};

int rt_hw_rtc_init(void)
{
    rt_err_t ret = RT_EOK;

    ret = rt_device_register(&device, "rtc", RT_DEVICE_FLAG_RDWR);
    if(ret != RT_EOK)
    {
        return ret;
    }

    rt_device_open(&device, RT_DEVICE_OFLAG_RDWR);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /*RT_USING_RTC */
