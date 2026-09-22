/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-22     seteiro      CH32V203: start or feed the independent watchdog
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

#ifdef BSP_USING_IWDT

static int wdt(int argc, char **argv)
{
    rt_device_t dev;
    rt_uint32_t timeout;
    rt_err_t err;

    if (argc < 2)
    {
        rt_kprintf("wdt start <seconds> | wdt feed\n");
        return -RT_ERROR;
    }

    dev = rt_device_find("wdt");
    if (dev == RT_NULL)
    {
        rt_kprintf("wdt device not found\n");
        return -RT_ERROR;
    }

    if (!rt_strcmp(argv[1], "start"))
    {
        if (argc < 3)
        {
            rt_kprintf("wdt start <seconds>\n");
            return -RT_ERROR;
        }
        timeout = atoi(argv[2]);
        err = rt_device_init(dev);
        if (err != RT_EOK)
        {
            return err;
        }
        err = rt_device_control(dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
        if (err != RT_EOK)
        {
            return err;
        }
        err = rt_device_control(dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
        rt_kprintf("wdt start %u %s\n", timeout, err == RT_EOK ? "ok" : "fail");
        return err;
    }

    if (!rt_strcmp(argv[1], "feed"))
    {
        err = rt_device_control(dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
        rt_kprintf("wdt feed %s\n", err == RT_EOK ? "ok" : "fail");
        return err;
    }

    rt_kprintf("wdt start <seconds> | wdt feed\n");
    return -RT_ERROR;
}
MSH_CMD_EXPORT(wdt, start or feed independent watchdog);

#endif
