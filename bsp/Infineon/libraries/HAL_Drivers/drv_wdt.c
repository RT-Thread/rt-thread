/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-21     Rbb666            first version
 */

#include "drv_wdt.h"

#ifdef RT_USING_WDT

//#define DRV_DEBUG
#define LOG_TAG "drv.wdt"
#include <drv_log.h>

cyhal_wdt_t WDT;

static struct ifx_wdt_cfg wdt_cfg =
{
    .name = "wdt",
    .WDTx = &WDT,
};

static struct ifx_wdt wdt_drv;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt_device, int cmd, void *arg)
{
    RT_ASSERT(wdt_device != RT_NULL);

    struct ifx_wdt_cfg *cfg;
    cfg = wdt_device->parent.user_data;

    rt_uint32_t timeout_ms = 0;

    switch (cmd)
    {
        /* feed the watchdog */
        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            cyhal_wdt_kick(cfg->WDTx);
            break;

        /* set watchdog timeout */
        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        {
            timeout_ms = *((rt_uint32_t *)arg) * 1000;

            rt_uint32_t max_timeout_ms = cyhal_wdt_get_max_timeout_ms();

            if (timeout_ms >= max_timeout_ms)
                timeout_ms = max_timeout_ms;

            /* Initialize the WDT */
            int result = cyhal_wdt_init(cfg->WDTx, (rt_uint32_t)timeout_ms);
            /* WDT initialization failed. Stop program execution */
            RT_ASSERT(result == RT_EOK);
        }
        break;

        case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
            timeout_ms = cyhal_wdt_get_timeout_ms(cfg->WDTx);
            *(rt_uint32_t *)arg = timeout_ms / 1000;
            break;

        case RT_DEVICE_CTRL_WDT_START:
            cyhal_wdt_start(cfg->WDTx);
            break;

        case RT_DEVICE_CTRL_WDT_STOP:
            cyhal_wdt_stop(cfg->WDTx);
            break;

        default:
            LOG_W("This command is not supported.");
            return -RT_ERROR;
    }

    return RT_EOK;
}

const static struct rt_watchdog_ops ifx_wdt_ops =
{
    wdt_init,
    wdt_control
};

int rt_hw_wdt_init(void)
{
    wdt_drv.cfg = &wdt_cfg;
    wdt_drv.wdt_device.ops = &ifx_wdt_ops;

    if (rt_hw_watchdog_register(&wdt_drv.wdt_device, wdt_drv.cfg->name, RT_DEVICE_FLAG_RDWR, wdt_drv.cfg) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }

    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* RT_USING_WDT */
