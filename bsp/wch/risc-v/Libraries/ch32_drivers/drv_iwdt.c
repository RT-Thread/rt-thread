/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-10     charlown          first version
 * 2022-09-27     hg0720            the first version which add from wch
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "ch32v30x_iwdg.h"

#ifdef BSP_USING_IWDT

#define LOG_TAG "drv.wdt"
#include "drv_log.h"

#ifndef LSI_VALUE
#error "Please define the value of LSI_VALUE!"
#endif

struct watchdog_device
{
    rt_watchdog_t parent;
    IWDG_TypeDef *instance;
    rt_uint32_t prescaler;
    rt_uint32_t reload;
    rt_uint16_t is_start;
};
static struct watchdog_device watchdog_dev;

static rt_err_t ch32_wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t ch32_wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct watchdog_device *wdt_dev;

    wdt_dev = (struct watchdog_device *)wdt;

    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        IWDG_ReloadCounter();
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (LSI_VALUE)
        {
            wdt_dev->reload = (*((rt_uint32_t *)arg)) * LSI_VALUE / 256;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
        if (wdt_dev->reload > 0xFFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds", 0xFFF * 256 / LSI_VALUE);
            return -RT_EINVAL;
        }

        if (wdt_dev->is_start)
        {
            IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
            IWDG_SetPrescaler(wdt_dev->prescaler);
            IWDG_SetReload(wdt_dev->reload);
            IWDG_ReloadCounter();
            IWDG_Enable();
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        if (LSI_VALUE)
        {
            (*((rt_uint32_t *)arg)) = wdt_dev->reload * 256 / LSI_VALUE;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
        break;
    case RT_DEVICE_CTRL_WDT_START:
        IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
        IWDG_SetPrescaler(wdt_dev->prescaler);
        IWDG_SetReload(wdt_dev->reload);
        IWDG_ReloadCounter();
        IWDG_Enable();
        wdt_dev->is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static struct rt_watchdog_ops watchdog_ops =
{
    .init = ch32_wdt_init,
    .control = ch32_wdt_control,
};

int rt_hw_wdt_init(void)
{
    watchdog_dev.instance = IWDG;
    watchdog_dev.prescaler = IWDG_Prescaler_256;
    watchdog_dev.reload = 0x0000FFF;
    watchdog_dev.is_start = 0;
    watchdog_dev.parent.ops = &watchdog_ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&watchdog_dev.parent, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_IWDT */
