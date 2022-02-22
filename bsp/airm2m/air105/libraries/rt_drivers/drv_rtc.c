/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */


#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

#ifndef RTC_BKP_DR1
#define RTC_BKP_DR1 RT_NULL
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

static rt_err_t air105_rtc_init(void)
{
    RTC_GlobalInit();
    return RT_EOK;
}

static rt_err_t air105_rtc_get_secs(void *args)
{
    *(rt_uint32_t *) args = RTC_GetUTC();
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t air105_rtc_set_secs(void *args)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t stamp = *(rt_uint32_t *)args;
    RTC_SetStamp(stamp);
    LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);

    return result;
}

static rt_err_t air105_rtc_get_timeval(void *args)
{
    struct timeval *tv = (struct timeval *) args;
    tv->tv_sec = RTC_GetUTC();
    return RT_EOK;
}

static const struct rt_rtc_ops air105_rtc_ops =
{
    air105_rtc_init,
    air105_rtc_get_secs,
    air105_rtc_set_secs,
    RT_NULL,
    RT_NULL,
    air105_rtc_get_timeval,
    RT_NULL,
};

static rt_rtc_dev_t air105_rtc_dev;

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    air105_rtc_dev.ops = &air105_rtc_ops;
    result = rt_hw_rtc_register(&air105_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_ONCHIP_RTC */
