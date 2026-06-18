/* Copyright (c) 2006-2026, RT-Thread Development Team */

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
#include "ds1307.h"

static struct rt_device g_rtc_dev;

static rt_err_t ns800_rtc_init(struct rt_device *dev)
{
    uint8_t sec;
    rt_err_t ret;

    ret = ds1307_init();
    if (ret != RT_EOK)
    {
        rt_kprintf("ds1307: i2c bus not found\n");
        return ret;
    }

    return RT_EOK;
}

static rt_err_t ns800_rtc_control(struct rt_device *dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct tm time_struct;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        result = ds1307_get_time(&time_struct);
        if (result == RT_EOK)
            *(time_t *)args = mktime(&time_struct);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        result = ds1307_set_time(localtime((const time_t *)args));
        break;

    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    g_rtc_dev.type    = RT_Device_Class_RTC;
    g_rtc_dev.init    = ns800_rtc_init;
    g_rtc_dev.open    = RT_NULL;
    g_rtc_dev.close   = RT_NULL;
    g_rtc_dev.read    = RT_NULL;
    g_rtc_dev.write   = RT_NULL;
    g_rtc_dev.control = ns800_rtc_control;

    result = rt_device_register(&g_rtc_dev, "rtc",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    if (result != RT_EOK)
    {
        rt_kprintf("rtc register failed\n");
        return -1;
    }

    result = ns800_rtc_init(&g_rtc_dev);
    if (result != RT_EOK)
    {
        rt_kprintf("ds1307 init failed\n");
        return -1;
    }

    rt_kprintf("ds1307 rtc ready\n");
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
