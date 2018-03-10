/*
 * File      : drv_wdt.c
 * This file is part of GK710X BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 GOKE Microelectronics Co., Ltd.
 * All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "drv_wdt.h"

#include <rtdef.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/watchdog.h>

#include "gtypes.h"
#include "gd_wdog.h"
#include "gd_timer.h"
#include "platform.h"


typedef enum
{
    RESTENABLE      = 0x4,
    INTERRUPTENABLE = 0x2,
}wdt_enable_mode;

static rt_uint32_t heartbeat = 0;

static rt_err_t gk_wdt_start(int mode)
{
    rt_err_t ret = RT_EOK;
    wdt_enable_mode wdt_mode = RESTENABLE;

    ret = GD_Wdog_Disable();
    if (ret != RT_EOK)
    {
        rt_kprintf("GD_Wdog_Disable error!\n");
        return RT_ERROR;
    }

    if ((mode == RESTENABLE) || (mode == INTERRUPTENABLE))
    {
        wdt_mode = mode;
    }

    ret = GD_Wdog_Enable(wdt_mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("GD_Wdog_Enable error!\n");
        return RT_ERROR;
    }

    return ret;
}

static rt_err_t gk_wdt_keepalive(void)
{
    rt_err_t ret = RT_EOK;

    ret = GD_Wdog_ClrTimeout();
    if (ret != GD_OK)
    {
        rt_kprintf("GD_Wdog_ClrTimeout error!\n");
        return RT_ERROR;
    }

    return ret;
}

static rt_uint32_t gk_wdt_get_timeleft(void)
{
    GERR index = GD_OK;
    rt_uint32_t second  = 0;

    index = GD_Wdog_GetValue();
    if (index < GD_OK )
    {
        rt_kprintf("GD_Wdog_GetValue error!\n");
        return RT_ERROR;
    }

    second = index/GD_GET_APB_ClkHz();

    return second;
}

static rt_err_t gk_wdt_set_timeout(rt_uint32_t second)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t index = 0;

    index = second * GD_GET_APB_ClkHz();
    ret = GD_Wdog_LoadValue(index);
    if (ret != GD_OK)
    {
        rt_kprintf("GD_Wdog_LoadValue error!\n");
        return RT_ERROR;
    }

    return ret;
}

static rt_err_t gk_watchdog_init(rt_watchdog_t *wdt)
{
    struct wdt_driver *wdt_drv = wdt->parent.user_data;
    if (wdt_drv->in_use) return -RT_EBUSY;

    GD_Wdog_Init();

    return RT_EOK;
}

static rt_err_t gk_watchdog_ctrl(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint32_t val;
    int mode;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_WDT_START:
            mode = *((int *)(arg));
            gk_wdt_start(mode);
            break;

        case RT_DEVICE_CTRL_WDT_STOP:
            GD_Wdog_Disable();
            break;

        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            gk_wdt_keepalive();
            break;

        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
            heartbeat = *((rt_uint32_t *)(arg));
            gk_wdt_set_timeout(heartbeat);
            break;

        case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
            arg = &heartbeat;
            break;

        case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
            val = gk_wdt_get_timeleft();
            arg = &val;
            break;

        default:
            return -RT_EIO;
    }
    return RT_EOK;
}


struct rt_watchdog_ops gk_watchdog_ops = {
    .init = &gk_watchdog_init, .control = &gk_watchdog_ctrl,
};

int gk_wdt_probe(void *priv_data)
{
    rt_watchdog_t *wdt_dev;
    struct wdt_driver *wdt_drv;

    wdt_drv = (struct wdt_driver *)rt_malloc(sizeof(struct wdt_driver));
    rt_memset(wdt_drv, 0, sizeof(struct wdt_driver));

    wdt_dev = (rt_watchdog_t *)rt_malloc(sizeof(rt_watchdog_t));

    if (wdt_dev == RT_NULL)
    {
        rt_kprintf("ERROR: %s rt_watchdog_t malloc failed\n", __func__);
    }

    wdt_dev->ops = &gk_watchdog_ops;

    rt_hw_watchdog_register(wdt_dev, "gk_wdt", RT_DEVICE_OFLAG_RDWR, wdt_drv);

    return 0;
}

int gk_wdt_exit(void *priv_data) { return 0; }
struct gk_platform_driver wdt_driver_ops = {
    .name = "wdt", .probe = gk_wdt_probe, .remove = gk_wdt_exit,
};

void rt_hw_wdt_init(void)
{
	gk_platform_driver_init(&wdt_driver_ops);
}

void gk_wdt_test(int timeout, int mode)
{
    rt_device_t wdt_dev;

    wdt_dev = rt_device_find("gk_wdt");
    if (!wdt_dev)
    {
        rt_kprintf("cann't find the wdt dev\n");
    }

    rt_device_open(wdt_dev, 0);

    rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_START, &mode);

    rt_kprintf("system shall reboot in %d seconds.\n", timeout);

    for (; timeout > 0; timeout--)
    {
        rt_kprintf("kicked %d\n", timeout);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

#ifdef RT_USING_WDT
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(gk_wdt_test, enable wdt);
#endif
#endif
