/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-17     JasonHu      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <time.h>
#include <rtdbg.h>

#include <sunxi_hal_rtc.h>

#ifdef RT_USING_RTC

static rt_err_t rtc_init(struct rt_device *dev)
{
    if (hal_rtc_init() != 0)
    {
        LOG_E("init rtc hal failed!");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct tm time_temp;
    struct tm *time_now;
    struct rtc_time hal_rtc_time;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:

        if (hal_rtc_gettime(&hal_rtc_time) != 0)
        {
            LOG_E("rtc gettime failed!\n");
            return -RT_ERROR;
        }

        time_temp.tm_sec = hal_rtc_time.tm_sec;
        time_temp.tm_min = hal_rtc_time.tm_min;
        time_temp.tm_hour = hal_rtc_time.tm_hour;
        time_temp.tm_mday = hal_rtc_time.tm_mday;
        time_temp.tm_mon = hal_rtc_time.tm_mon;
        time_temp.tm_year = hal_rtc_time.tm_year;

        *((time_t *)args) = mktime(&time_temp);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:

        rt_enter_critical();
        /* converts calendar time time into local time. */
        time_now = localtime((const time_t *)args);
        /* copy the statically located variable */
        memcpy(&time_temp, time_now, sizeof(struct tm));
        /* unlock scheduler. */
        rt_exit_critical();

        hal_rtc_time.tm_sec = time_temp.tm_sec;
        hal_rtc_time.tm_min = time_temp.tm_min;
        hal_rtc_time.tm_hour = time_temp.tm_hour;
        hal_rtc_time.tm_mday = time_temp.tm_mday;
        hal_rtc_time.tm_mon = time_temp.tm_mon;
        hal_rtc_time.tm_year = time_temp.tm_year;
        if (hal_rtc_settime(&hal_rtc_time) != 0)
        {
            LOG_E("rtc settime failed!\n");
            return -RT_ERROR;
        }
        break;
    default:
        return -RT_EINVAL;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rt_hw_rtc_ops =
{
    rtc_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rtc_control
};
#endif

int rt_hw_rtc_init(void)
{
    rt_err_t ret = RT_EOK;
    static struct rt_device rtc_dev;

    rtc_dev.type = RT_Device_Class_RTC;
    rtc_dev.rx_indicate = RT_NULL;
    rtc_dev.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    rtc_dev.ops = &rt_hw_rtc_ops;
#else
    rtc_dev.init = rtc_init;
    rtc_dev.open = RT_NULL;
    rtc_dev.close = RT_NULL;
    rtc_dev.read = RT_NULL;
    rtc_dev.write = RT_NULL;
    rtc_dev.control = rtc_control;
#endif

    rtc_dev.user_data = RT_NULL;

#ifdef BSP_USING_RTC
    ret = rt_device_register(&rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);
#endif

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif
