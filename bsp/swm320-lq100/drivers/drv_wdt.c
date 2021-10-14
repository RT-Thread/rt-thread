/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          format file
 */

#include "drv_wdt.h"

#ifdef RT_USING_WDT
#ifdef BSP_USING_WDT
//#define DRV_DEBUG
#define LOG_TAG "drv.wdt"
#include <drv_log.h>

static struct swm_wdt_cfg wdt_cfg =
    {
        .name = "wdt",
        .WDTx = WDT,
};

static struct swm_wdt wdt_drv;

static rt_err_t swm_wdt_init(rt_watchdog_t *wdt_device)
{
    return RT_EOK;
}

static rt_err_t swm_wdt_control(rt_watchdog_t *wdt_device, int cmd, void *arg)
{
    struct swm_wdt_cfg *cfg;
    RT_ASSERT(wdt_device != RT_NULL);
    cfg = wdt_device->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WDT_Feed(cfg->WDTx);
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        WDT_Init(cfg->WDTx, (SystemCoreClock * (*(rt_uint32_t *)arg)), WDT_MODE_RESET);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = (cfg->WDTx->LOAD) / SystemCoreClock;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(rt_uint32_t *)arg = WDT_GetValue(cfg->WDTx) / SystemCoreClock;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        WDT_Start(cfg->WDTx);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        WDT_Stop(cfg->WDTx);
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

const static struct rt_watchdog_ops swm_wdt_ops =
    {
        swm_wdt_init,
        swm_wdt_control};

int rt_hw_wdt_init(void)
{
    wdt_drv.cfg = &wdt_cfg;
    wdt_drv.wdt_device.ops = &swm_wdt_ops;

    if (rt_hw_watchdog_register(&wdt_drv.wdt_device, wdt_drv.cfg->name, RT_DEVICE_FLAG_RDWR, wdt_drv.cfg) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */
#endif /* RT_USING_WDT */
