/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
 */

#include "drv_wdt.h"

#ifdef RT_USING_WDT
#ifdef BSP_USING_WDT
//#define DRV_DEBUG
#define LOG_TAG "drv.wdt"
#include <drv_log.h>

struct swm_wdt_cfg
{
    const char *name;
    WDT_TypeDef *WDTx;
};

struct swm_wdt_device
{
    struct swm_wdt_cfg *wdt_cfg;
    struct rt_watchdog_device wdt_device;
};

static struct swm_wdt_cfg swm_wdt_cfg =
    {
        .name = "wdt",
        .WDTx = WDT,
};

static struct swm_wdt_device wdt_obj;

static rt_err_t swm_wdt_configure(rt_watchdog_t *wdt_device)
{
    return RT_EOK;
}

static rt_err_t swm_wdt_control(rt_watchdog_t *wdt_device, int cmd, void *arg)
{
    struct swm_wdt_cfg *wdt_cfg;
    RT_ASSERT(wdt_device != RT_NULL);
    wdt_cfg = wdt_device->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WDT_Feed(wdt_cfg->WDTx);
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        WDT_Init(wdt_cfg->WDTx, 0, (1024 * (*(rt_uint32_t *)arg)));
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = (wdt_cfg->WDTx->RSTVAL) / 1024;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        // not support
        break;
    case RT_DEVICE_CTRL_WDT_START:
        WDT_Start(wdt_cfg->WDTx);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        WDT_Stop(wdt_cfg->WDTx);
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops swm_wdt_ops =
    {
        .init = swm_wdt_configure,
        .control = swm_wdt_control};

int swm_wdt_init(void)
{
    int result = RT_EOK;

    wdt_obj.wdt_cfg = &swm_wdt_cfg;
    wdt_obj.wdt_device.ops = &swm_wdt_ops;

    result = rt_hw_watchdog_register(&wdt_obj.wdt_device, wdt_obj.wdt_cfg->name, RT_DEVICE_FLAG_RDWR, wdt_obj.wdt_cfg);
    if(result != RT_EOK)
    {
        LOG_E("wdt device register fail.");
    }
    else
    {
        LOG_D("wdt device register success.");
    }
    return result;
}
INIT_BOARD_EXPORT(swm_wdt_init);

#endif /* BSP_USING_WDT */
#endif /* RT_USING_WDT */
