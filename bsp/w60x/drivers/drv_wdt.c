/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2018-11-9      fanwenl       1st version
 */

#include <rtdevice.h>
#include "wm_watchdog.h"

#ifdef BSP_USING_WDT

static rt_err_t wm_wdg_init(rt_watchdog_t *wdt)
{
    /*init for 10S*/
    tls_watchdog_init(1000000);
    tls_watchdog_stop();
    return RT_EOK;
}

static rt_err_t wm_wdg_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    uint64_t  timeout_us = 0;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        timeout_us = *((rt_uint32_t *)arg) * 1000000;
        if (timeout_us >= 0xFFFFFFFF)
            timeout_us = 0xFFFFFFFF;
        tls_watchdog_set_timeout((rt_uint32_t)timeout_us);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        timeout_us = tls_watchdog_get_timeout();
        *((rt_uint32_t *)arg) = timeout_us / 1000000;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        timeout_us = tls_watchdog_get_timeleft();
        *((rt_uint32_t *)arg) = timeout_us / 1000000;
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        tls_watchdog_clr();
        break;
    case RT_DEVICE_CTRL_WDT_START:
        tls_watchdog_start();
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        tls_watchdog_stop();
        break;
    default:
        return -RT_EIO;
    }
    return RT_EOK;
}

static const struct rt_watchdog_ops wm_wdg_pos =
{
    wm_wdg_init,
    wm_wdg_control,
};

static rt_watchdog_t wm_wdg;

int wm_hw_wdg_init(void)
{
    wm_wdg.ops = &wm_wdg_pos;
    rt_hw_watchdog_register(&wm_wdg, "wdg", 0, RT_NULL);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(wm_hw_wdg_init);

#endif /*BSP_USING_WDT */
