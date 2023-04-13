/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-03-14     wcx1024979076 first version
 */

#include "drv_wdt.h"

#ifdef RT_USING_WDT
#ifdef BSP_USING_WDT
#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.WDT"

struct rt_watchdog_device wdt_device;

static rt_err_t _wdt_configure(rt_watchdog_t *wdt_device)
{
    struct bflb_device_s* wdt = bflb_device_get_by_name("watchdog");
    struct bflb_wdg_config_s wdg_cfg;

    wdg_cfg.clock_source = BFLB_SYSTEM_XCLK;
    wdg_cfg.clock_div = 40;
    wdg_cfg.comp_val = 10000000;
    wdg_cfg.mode = WDG_MODE_RESET;
    bflb_wdg_init(wdt, &wdg_cfg);

    return RT_EOK;
}

static rt_err_t _wdt_control(rt_watchdog_t *wdt_device, int cmd, void *arg)
{
    RT_ASSERT(wdt_device != RT_NULL);

    struct bflb_device_s* wdt = bflb_device_get_by_name("watchdog");
    struct bflb_wdg_config_s wdg_cfg;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        bflb_wdg_reset_countervalue(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        wdg_cfg.clock_source = BFLB_SYSTEM_XCLK;
        wdg_cfg.clock_div = 40;
        wdg_cfg.comp_val = 10000000 * (*(rt_uint32_t *)arg);
        wdg_cfg.mode = WDG_MODE_RESET;
        bflb_wdg_init(wdt, &wdg_cfg);
        bflb_wdg_start(wdt);
        wdt_device->parent.user_data = (rt_uint32_t)(*(rt_uint32_t *)arg);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = (rt_uint32_t)wdt_device->parent.user_data;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(rt_uint32_t *)arg = bflb_wdg_get_countervalue(wdt) / 10000000;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        bflb_wdg_start(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        bflb_wdg_stop(wdt);
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops _wdt_ops =
{
    .init = _wdt_configure,
    .control = _wdt_control
};

int rt_hw_wdt_init(void)
{
    int result = RT_EOK;

    wdt_device.ops = &_wdt_ops;
    result = rt_hw_watchdog_register(&wdt_device, "wdt", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if(result != RT_EOK)
    {
        LOG_E("wdt device register fail.");
    }
    return result;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */
#endif /* RT_USING_WDT */
