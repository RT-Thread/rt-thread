/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-15     JasonHu      first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <sunxi_hal_watchdog.h>

#define DBG_SECTION_NAME "wdt"
#include <rtdbg.h>

#if defined(RT_USING_WDT) && defined(BSP_USING_WDT)

/* hardware only support (1-16)s */
static rt_uint32_t wdg_timeout = 0;

static rt_err_t wdg_init(rt_watchdog_t *wdt)
{
    wdg_timeout = 0;
    hal_watchdog_init();
    return RT_EOK;
}

static rt_err_t wdg_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (arg)
        {
            wdg_timeout = *(rt_uint32_t *)arg;
        }
        else
        {
            LOG_E("arg is NULL!");
            return -RT_EIO;
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        if (arg)
        {
            *((rt_uint32_t *)arg) = wdg_timeout;
        }
        else
        {
            LOG_E("arg is NULL!");
            return -RT_EIO;
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        LOG_E("not support RT_DEVICE_CTRL_WDT_GET_TIMELEFT on this platform!");
        if (arg)
        {
            *((rt_uint32_t *)arg) = 0;
        }
        else
        {
            LOG_E("arg is NULL!");
        }
        return -RT_EIO;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        hal_watchdog_feed();
        break;
    case RT_DEVICE_CTRL_WDT_START:
        hal_watchdog_start(wdg_timeout);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        hal_watchdog_stop(wdg_timeout);
        break;
    default:
        return -RT_EIO;
    }
    return RT_EOK;
}

static const struct rt_watchdog_ops wdg_pos =
{
    wdg_init,
    wdg_control,
};

static rt_watchdog_t wdg;

int rt_hw_wdg_init(void)
{
    wdg.ops = &wdg_pos;
    rt_hw_watchdog_register(&wdg, "wdt", 0, RT_NULL);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_wdg_init);

void rt_hw_cpu_reset(void)
{
    rt_hw_interrupt_disable();
    hal_watchdog_start(1);
    while(1);
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);

#endif /* RT_USING_WDT && BSP_USING_WDT */
