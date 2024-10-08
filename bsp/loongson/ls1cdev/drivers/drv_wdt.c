/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     sundm75       first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef  RT_USING_WDT

#include "drivers/dev_watchdog.h"
#include "drv_wdt.h"

#include "ls1c_wdog.h"
#include "ls1c_clock.h"

typedef enum
{
    RESTENABLE      = 0x0,
    INTERRUPTENABLE = 0x1,
}wdt_enable_mode;

static rt_uint32_t heartbeat = 0;

static rt_err_t wdt_stop(void)
{
    rt_err_t ret = RT_EOK;

    Wdog_Reset();
    ret = (rt_err_t) Wdog_Disable();
    if (ret != RT_EOK)
    {
        rt_kprintf("Wdog_Disable error!\n");
        return -RT_ERROR;
    }
    return ret;
}

static rt_err_t wdt_start(int mode)
{
    rt_err_t ret = RT_EOK;
    wdt_enable_mode wdt_mode = RESTENABLE;

    ret = (rt_err_t) Wdog_Disable();
    if (ret != RT_EOK)
    {
        rt_kprintf("Wdog_Disable error!\n");
        return -RT_ERROR;
    }

    if((mode == RESTENABLE) || (mode == INTERRUPTENABLE))
    {
        wdt_mode = mode;
    }
    Wdog_Enable();
    Wdog_Set();
    if (ret != RT_EOK)
    {
        rt_kprintf("Wdog_Enable error!\n");
        return -RT_ERROR;
    }

    return ret;
}

static rt_err_t wdt_keepalive(void)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t index = 0;

    index = heartbeat * clk_get_apb_rate();
    ret = (rt_err_t) Wdog_LoadValue(index);
    Wdog_Set();
    if (ret != 0)
    {
        rt_kprintf("LS1C_Wdog_ClrTimeout error!\n");
        return -RT_ERROR;
    }

    return ret;
}

static rt_uint32_t wdt_get_timeleft(void)
{
    rt_uint32_t  cnt = 0;
    rt_uint32_t second  = 0;

    cnt =  (rt_uint32_t) Wdog_GetValue();
    second = cnt/clk_get_apb_rate();

    return second;
}

static rt_err_t wdt_set_timeout(rt_uint32_t second)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t index = 0;

    index = second * clk_get_apb_rate();
    ret = (rt_err_t) Wdog_LoadValue(index);
    if (ret != RT_EOK)
    {
        rt_kprintf("Wdog_LoadValue error!\n");
        return -RT_ERROR;
    }
    return ret;
}

static rt_err_t watchdog_init(rt_watchdog_t *wdt)
{
    struct wdt_driver *wdt_drv = wdt->parent.user_data;
    if (wdt_drv->in_use) return -RT_EBUSY;

    Wdog_Init();

    return RT_EOK;
}

static rt_err_t watchdog_ctrl(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint32_t val;
    int mode;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_WDT_START:
            mode = *((int *)(arg));
            wdt_start(mode);
            break;

        case RT_DEVICE_CTRL_WDT_STOP:
            Wdog_Disable();
            break;

        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            wdt_keepalive();
            break;

        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
            heartbeat = *((rt_uint32_t *)(arg));
            wdt_set_timeout(heartbeat);
            break;

        case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
            arg = &heartbeat;
            break;

        case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
            val = (rt_uint32_t) wdt_get_timeleft();
            arg = &val;
            break;

        default:
            return -RT_EIO;
    }
    return RT_EOK;
}

struct rt_watchdog_ops watchdog_ops =
{
    .init = &watchdog_init,
    .control = &watchdog_ctrl,
};

int wdt_exit(void *priv_data)
{
    return 0;
}

int rt_hw_wdt_init(void)
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

    wdt_dev->ops = &watchdog_ops;

    rt_hw_watchdog_register(wdt_dev, "wdt", RT_DEVICE_OFLAG_RDWR, wdt_drv);

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif
