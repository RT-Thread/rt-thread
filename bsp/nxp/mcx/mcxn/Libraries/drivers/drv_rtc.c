/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-06     Yilin Sun    Initial version.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "drv_rtc.h"
#include "fsl_common.h"
#include "fsl_irtc.h"

#ifdef RT_USING_RTC

static rt_err_t mcx_rtc_init(rt_device_t dev)
{
    irtc_config_t rtc_cfg;

    IRTC_GetDefaultConfig(&rtc_cfg);

    //rtc_cfg.clockSelect = kIRTC_Clk32K;

    if (IRTC_Init(RTC0, &rtc_cfg) != kStatus_Success)
    {
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t mcx_rtc_get_time(time_t *ts)
{
    struct tm tm_new = {0};

    irtc_datetime_t rtc_date;

    IRTC_GetDatetime(RTC0, &rtc_date);

    tm_new.tm_sec = rtc_date.second;
    tm_new.tm_min = rtc_date.minute;
    tm_new.tm_hour = rtc_date.hour;

    tm_new.tm_mday = rtc_date.day;
    tm_new.tm_mon = rtc_date.month - 1;
    tm_new.tm_year = rtc_date.year - 1900;

    *ts = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t mcx_rtc_set_time(time_t *ts)
{
    struct tm now;
    irtc_datetime_t rtc_date;

    gmtime_r(ts, &now);

    rtc_date.second = now.tm_sec ;
    rtc_date.minute = now.tm_min ;
    rtc_date.hour   = now.tm_hour;

    rtc_date.weekDay = now.tm_wday;
    rtc_date.day     = now.tm_mday;
    rtc_date.month   = now.tm_mon  + 1;
    rtc_date.year    = now.tm_year + 1900;

    IRTC_SetWriteProtection(RTC0, false);
    IRTC_SetDatetime(RTC0, &rtc_date);

    return RT_EOK;
}

static rt_err_t mcx_rtc_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        mcx_rtc_get_time((time_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        mcx_rtc_set_time((time_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
    /* TODO: Implement alarm features */
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_device device =
{
    .type    = RT_Device_Class_RTC,
    .init    = mcx_rtc_init,
    .open    = RT_NULL,
    .close   = RT_NULL,
    .read    = RT_NULL,
    .write   = RT_NULL,
    .control = mcx_rtc_control,
};

int rt_hw_rtc_init(void)
{
    rt_err_t ret = RT_EOK;

    ret = rt_device_register(&device, "rtc", RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        return ret;
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /*RT_USING_RTC */
