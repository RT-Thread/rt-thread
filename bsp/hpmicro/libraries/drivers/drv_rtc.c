/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2021-09-19   HPMicro     First version
 * 2023-05-08   HPMicro     Adapt RT-Thread V5.0.0
 */
#include "board.h"
#include "drv_rtc.h"
#include "hpm_rtc_drv.h"
#include "hpm_bpor_drv.h"

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#ifdef RT_USING_RTC

/*******************************************************************************************
 *
 *  Prototypes
 *
 ******************************************************************************************/
static rt_err_t hpm_rtc_init(rt_device_t dev);
static rt_err_t hpm_rtc_open(rt_device_t dev, rt_uint16_t oflag);
static rt_err_t hpm_rtc_close(rt_device_t dev);
static rt_ssize_t hpm_rtc_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size);
static rt_ssize_t hpm_rtc_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size);
static rt_err_t hpm_rtc_control(rt_device_t dev, int cmd, void *args);

static time_t hpm_rtc_get_timestamp(void);
static int hpm_rtc_set_timestamp(time_t timestamp);

/*******************************************************************************************
 *
 *  Variables
 *
 ******************************************************************************************/
#ifdef RT_USING_DEVICE_OPS
const struct rt_device_ops hpm_rtc_ops = {
    .init = hpm_rtc_init,
    .open = hpm_rtc_open,
    .close = hpm_rtc_close,
    .read = hpm_rtc_read,
    .write = hpm_rtc_write,
    .control = hpm_rtc_control,
};
#endif
static struct rt_device hpm_rtc= {
    .type = RT_Device_Class_RTC,
#ifdef RT_USING_DEVICE_OPS
    .ops = &hpm_rtc_ops,
#else
    .init = hpm_rtc_init,
    .open = hpm_rtc_open,
    .close = hpm_rtc_close,
    .read = hpm_rtc_read,
    .write = hpm_rtc_write,
    .control = hpm_rtc_control,
#endif
};

/*******************************************************************************************
 *
 *  Codes
 *
 ******************************************************************************************/
static rt_err_t hpm_rtc_init(rt_device_t dev)
{
    /* Enable Power retention mode for the battery domain */
    bpor_enable_reg_value_retention(HPM_BPOR);
    return RT_EOK;
}
static rt_err_t hpm_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}
static rt_err_t hpm_rtc_close(rt_device_t dev)
{
    return RT_EOK;
}
static rt_ssize_t hpm_rtc_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t size)
{
    return 0;
}
static rt_ssize_t hpm_rtc_write(rt_device_t dev, rt_off_t pos, const void *buf, rt_size_t size)
{
    return 0;
}
static rt_err_t hpm_rtc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    rt_err_t err = RT_EOK;

    switch(cmd) {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
            *(uint32_t *)args = hpm_rtc_get_timestamp();
            break;
        case RT_DEVICE_CTRL_RTC_SET_TIME:
            hpm_rtc_set_timestamp(*(time_t *)args);
            break;
        default:
            err = RT_EINVAL;
            break;
    }

    return err;
}

static time_t hpm_rtc_get_timestamp(void)
{
    time_t time = rtc_get_time(HPM_RTC);

    return time;
}

static int hpm_rtc_set_timestamp(time_t timestamp)
{
    (void)rtc_config_time(HPM_RTC, timestamp);

    return RT_EOK;
}


int rt_hw_rtc_init(void)
{
    rt_err_t err = RT_EOK;

    err = rt_device_register(&hpm_rtc, "rtc", RT_DEVICE_FLAG_RDWR);
    if (err != RT_EOK) {
        LOG_E("rt device %s failed, status=%d\n", "rtc", err);
        return err;
    }

    rt_device_open(&hpm_rtc, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* RT_USING_RTC */
