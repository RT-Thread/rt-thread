/*
 * Copyright (c) 2024, Your Company Name
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-04     Alex         First version for MCXC444
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#include "drv_rtc.h"

#include "fsl_rtc.h"
#include "fsl_clock.h"

#define DBG_TAG               "drv.rtc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

static rt_err_t mcxc444_rtc_init(rt_device_t dev)
{
    rtc_config_t rtcConfig;

    CLOCK_EnableClock(kCLOCK_Rtc0);

    RTC_GetDefaultConfig(&rtcConfig);

    RTC_Init(RTC, &rtcConfig);

    RTC_SetClockSource(RTC);

    rt_thread_mdelay(10);

    RTC_StartTimer(RTC);

    return RT_EOK;
}

static rt_err_t mcxc444_rtc_get_time(time_t *ts)
{
    if (ts == RT_NULL)
    {
        return -RT_EINVAL;
    }

    *ts = RTC->TSR;

    return RT_EOK;
}

static rt_err_t mcxc444_rtc_set_time(time_t *ts)
{
    if (ts == RT_NULL)
    {
        return -RT_EINVAL;
    }

    RTC_StopTimer(RTC);
    RTC->TSR = *ts;
    RTC_StartTimer(RTC);

    return RT_EOK;
}

static rt_err_t mcxc444_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        result = mcxc444_rtc_get_time((time_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        result = mcxc444_rtc_set_time((time_t *)args);
        break;

    default:
        return -RT_EINVAL;
    }

    return result;
}

static struct rt_device rtc_device;

int rt_hw_rtc_init(void)
{
    rt_err_t ret;

    rtc_device.type    = RT_Device_Class_RTC;
    rtc_device.init    = mcxc444_rtc_init;
    rtc_device.open    = RT_NULL;
    rtc_device.close   = RT_NULL;
    rtc_device.read    = RT_NULL;
    rtc_device.write   = RT_NULL;
    rtc_device.control = mcxc444_rtc_control;

    ret = rt_device_register(&rtc_device, "rtc", RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        LOG_E("rtc register err code: %d\n", ret);
        return ret;
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);


