/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-05     Chushicheng  the first version
 */

#include "drv_wdt.h"
#include <hardware/watchdog.h>

#define DBG_TAG              "drv.wdt"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

static struct pico_wdt pico_wdt_obj;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    static rt_uint32_t delay_ms;
    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        watchdog_update();
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        delay_ms = *((rt_uint32_t*)arg) * 1000;
        watchdog_reboot(0, RT_NULL, delay_ms);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        (*((rt_uint32_t*)arg)) = watchdog_get_count();
        break;
    case RT_DEVICE_CTRL_WDT_START:
        watchdog_enable(delay_ms, 1);
        pico_wdt_obj.is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static const struct rt_watchdog_ops ops =
{
    .init    = wdt_init,
    .control = wdt_control,
};

int rt_hw_wdt_init(void)
{
    int result = RT_EOK;

    pico_wdt_obj.watchdog.ops = &ops;
    /* register wdt device */
    if (rt_hw_watchdog_register(&pico_wdt_obj.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) == RT_EOK)
    {
        LOG_D("wdt init success");
    }
    else
    {
        LOG_E("wdt register failed");
        result = -RT_ERROR;
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);
