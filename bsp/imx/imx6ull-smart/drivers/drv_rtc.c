/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-25     Lyons        first version
 */

#include <rtconfig.h>

#ifdef BSP_USING_ONCHIP_RTC

#include "board.h"

#define DBG_TAG "drv.rtc"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#define _DEVICE_NAME        "rtc"

_internal_rw struct rt_device _s_rtc_device;

static time_t _get_rtc_timestamp(void)
{
    snvs_hp_rtc_datetime_t rtcDate;
    SNVS_Type *snvs = (SNVS_Type*)g_snvs_vbase;
    struct tm tm_new;

    SNVS_HP_RTC_GetDatetime(snvs, &rtcDate);

    tm_new.tm_sec  = rtcDate.second;
    tm_new.tm_min  = rtcDate.minute;
    tm_new.tm_hour = rtcDate.hour;
    tm_new.tm_mday = rtcDate.day;
    tm_new.tm_mon  = rtcDate.month - 1;
    tm_new.tm_year = rtcDate.year - 1900;

    return mktime(&tm_new);
}

static rt_err_t _set_rtc_time_stamp(time_t time_stamp)
{
    snvs_hp_rtc_datetime_t rtcDate;
    SNVS_Type *snvs = (SNVS_Type*)g_snvs_vbase;
    struct tm *p_tm;

    p_tm = localtime(&time_stamp);

    rtcDate.second = p_tm->tm_sec;
    rtcDate.minute = p_tm->tm_min;
    rtcDate.hour   = p_tm->tm_hour;
    rtcDate.day    = p_tm->tm_mday;
    rtcDate.month  = p_tm->tm_mon + 1;
    rtcDate.year   = p_tm->tm_year + 1900;

    if (kStatus_Success != SNVS_HP_RTC_SetDatetime(snvs, &rtcDate))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static void _rtc_init(void)
{
    snvs_hp_rtc_config_t snvsRtcConfig;
    SNVS_Type *snvs = (SNVS_Type*)g_snvs_vbase;

    SNVS_HP_RTC_GetDefaultConfig(&snvsRtcConfig);
    SNVS_HP_RTC_Init(snvs, &snvsRtcConfig);

    SNVS_HP_RTC_StartTimer(snvs);
}

static rt_err_t _rtc_config(struct rt_device *dev)
{
    return RT_EOK;
}

static rt_err_t _rtc_ops_control( rt_device_t dev, int cmd, void *args )
{
    rt_err_t result;

    RT_ASSERT(RT_NULL != dev);

    result = RT_EOK;
    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
            *(time_t *)args = _get_rtc_timestamp();
            LOG_D("RTC: get rtc_time %x", *(time_t *)args);
            break;

        case RT_DEVICE_CTRL_RTC_SET_TIME:
            if (_set_rtc_time_stamp(*(time_t *)args))
            {
                result = -RT_ERROR;
            }
            LOG_D("RTC: set rtc_time %x", *(time_t *)args);
            break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
_internal_ro struct rt_device_ops _k_rtc_ops =
{
    RT_NULL,            /* init */
    RT_NULL,            /* open */
    RT_NULL,            /* close */
    RT_NULL,            /* read */
    RT_NULL,            /* write */
    _rtc_ops_control,   /* control */
};
#endif

static rt_err_t _rt_rtc_register( rt_device_t device, const char *name, rt_uint32_t flag )
{
    RT_ASSERT(RT_NULL != device);

    _rtc_init();
    if (RT_EOK != _rtc_config(device))
    {
        return -RT_ERROR;
    }

    device->type        = RT_Device_Class_RTC;
#ifdef RT_USING_DEVICE_OPS
    device->ops         = &_k_rtc_ops;
#else
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = _rtc_ops_control;
#endif
    device->user_data   = RT_NULL;

    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    result = _rt_rtc_register(&_s_rtc_device, _DEVICE_NAME, RT_DEVICE_FLAG_RDWR);
    if (RT_EOK != result)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }

    LOG_D("rtc init success.");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_ONCHIP_RTC */
