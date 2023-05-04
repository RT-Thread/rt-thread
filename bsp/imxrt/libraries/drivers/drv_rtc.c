/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-15     Liuguang     the first version.
 * 2019-04-22     tyustli      add imxrt series support
 *
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#ifdef BSP_USING_RTC

#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#include "drv_rtc.h"
#include "fsl_snvs_hp.h"
#include "fsl_snvs_lp.h"
#include <sys/time.h>

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

static time_t imxrt_hp_get_timestamp(void)
{
    struct tm tm_new = {0};
    snvs_hp_rtc_datetime_t rtcDate = {0};
    snvs_lp_srtc_datetime_t srtcDate = {0};

    SNVS_LP_SRTC_GetDatetime(SNVS, &srtcDate);
    SNVS_HP_RTC_TimeSynchronize(SNVS);
    SNVS_HP_RTC_GetDatetime(SNVS, &rtcDate);

    tm_new.tm_sec  = rtcDate.second;
    tm_new.tm_min  = rtcDate.minute;
    tm_new.tm_hour = rtcDate.hour;

    tm_new.tm_mday = rtcDate.day;
    tm_new.tm_mon  = rtcDate.month - 1;
    tm_new.tm_year = rtcDate.year - 1900;

    return timegm(&tm_new);
}

static int imxrt_hp_set_timestamp(time_t timestamp)
{
    struct tm now;
    snvs_lp_srtc_datetime_t srtcDate = {0};

    gmtime_r(&timestamp, &now);

    srtcDate.second = now.tm_sec;
    srtcDate.minute = now.tm_min;
    srtcDate.hour = now.tm_hour;

    srtcDate.day = now.tm_mday;
    srtcDate.month = now.tm_mon + 1;
    srtcDate.year = now.tm_year + 1900;


    if (SNVS_LP_SRTC_SetDatetime(SNVS, &srtcDate) != kStatus_Success)
    {
        LOG_E("set rtc date time failed\n");
        return -RT_ERROR;
    }

    SNVS_HP_RTC_TimeSynchronize(SNVS);

    return RT_EOK;
}

static rt_err_t imxrt_hp_rtc_init(rt_device_t dev)
{
    snvs_hp_rtc_config_t snvsRtcConfig;
    snvs_lp_srtc_config_t snvsSrtcConfig;

    /* Init SNVS_HP */
    SNVS_HP_RTC_GetDefaultConfig(&snvsRtcConfig);
    SNVS_HP_RTC_Init(SNVS, &snvsRtcConfig);

    /* Init SNVS_LP */
    SNVS_LP_SRTC_GetDefaultConfig(&snvsSrtcConfig);
    SNVS_LP_SRTC_Init(SNVS, &snvsSrtcConfig);
    return RT_EOK;
}

static rt_err_t imxrt_hp_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    SNVS_HP_RTC_StartTimer(SNVS);
    SNVS_LP_SRTC_StartTimer(SNVS);
    return RT_EOK;
}

static rt_err_t imxrt_hp_rtc_close(rt_device_t dev)
{
    SNVS_HP_RTC_StopTimer(SNVS);

    return RT_EOK;
}

static rt_ssize_t imxrt_hp_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return -RT_EINVAL;
}

static rt_ssize_t imxrt_hp_rtc_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    return -RT_EINVAL;
}

static rt_err_t imxrt_hp_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch(cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
    {
        *(uint32_t *)args = imxrt_hp_get_timestamp();
    }
    break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        imxrt_hp_set_timestamp(*(time_t *)args);
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
    .init    = imxrt_hp_rtc_init,
    .open    = imxrt_hp_rtc_open,
    .close   = imxrt_hp_rtc_close,
    .read    = imxrt_hp_rtc_read,
    .write   = imxrt_hp_rtc_write,
    .control = imxrt_hp_rtc_control,
};

int rt_hw_rtc_init(void)
{
    rt_err_t ret = RT_EOK;

    ret = rt_device_register(&device, "rtc", RT_DEVICE_FLAG_RDWR);

    if(ret != RT_EOK)
    {
        LOG_E("rt device register failed %d\n", ret);
        return ret;
    }

    rt_device_open(&device, RT_DEVICE_OFLAG_RDWR);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#include <rtthread.h>
#include <rtdevice.h>

#define RTC_NAME       "rtc"

static int rtc_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    time_t now;
    rt_device_t device = RT_NULL;

    device = rt_device_find(RTC_NAME);
    if (!device)
    {
      LOG_E("find %s failed!", RTC_NAME);
      return -RT_ERROR;
    }

    if(rt_device_open(device, 0) != RT_EOK)
    {
      LOG_E("open %s failed!", RTC_NAME);
      return -RT_ERROR;
    }

    ret = set_date(2018, 12, 3);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC date failed\n");
        return ret;
    }

    ret = set_time(11, 15, 50);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC time failed\n");
        return ret;
    }

    rt_thread_mdelay(1000);

    now = time(RT_NULL);
    rt_kprintf("%s\n", ctime(&now));

    return ret;
}
MSH_CMD_EXPORT(rtc_sample, rtc sample);
#endif /* BSP_USING_RTC */
