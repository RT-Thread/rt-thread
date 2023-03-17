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

static char device_name[] = "wdt";
static rt_device_t wdg_dev;

static struct rt_work wdt_feed;
static void wdt_feed_func(struct rt_work *work, void *work_data)
{
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
    rt_work_submit(&wdt_feed, 1200);
}

static int wdt_feed_init(void)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 2;

    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }

    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return -RT_ERROR;
    }
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }

    rt_work_init(&wdt_feed, wdt_feed_func, RT_NULL);
    rt_work_submit(&wdt_feed, 1200);
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(wdt_feed_init);
