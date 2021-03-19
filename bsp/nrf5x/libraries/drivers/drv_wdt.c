/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-08-18     ylz0923           first version
 */

#include <board.h>
#include <rtdevice.h>
#include <nrfx_wdt.h>

#ifdef RT_USING_WDT

struct nrf5x_wdt_obj
{
    rt_watchdog_t watchdog;
    nrfx_wdt_t wdt;
    nrfx_wdt_channel_id ch;
    rt_uint16_t is_start;
};
static struct nrf5x_wdt_obj nrf5x_wdt = {
    .wdt = NRFX_WDT_INSTANCE(0),
};
static nrfx_wdt_config_t nrf5x_wdt_cfg = NRFX_WDT_DEFAULT_CONFIG;
static struct rt_watchdog_ops ops;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        nrfx_wdt_feed(&nrf5x_wdt.wdt);
        break;
    /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        nrf5x_wdt_cfg.reload_value = (rt_uint32_t)arg * 1000;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *((rt_uint32_t*)arg) = nrf5x_wdt_cfg.reload_value;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (nrf5x_wdt.is_start != 1)
        {
            nrfx_wdt_init(&nrf5x_wdt.wdt, &nrf5x_wdt_cfg, RT_NULL);
            nrfx_wdt_channel_alloc(&nrf5x_wdt.wdt, &nrf5x_wdt.ch);
            nrfx_wdt_enable(&nrf5x_wdt.wdt);
            nrf5x_wdt.is_start = 1;
        }
        break;
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    nrf5x_wdt.is_start = 0;
    ops.init = &wdt_init;
    ops.control = &wdt_control;
    nrf5x_wdt.watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&nrf5x_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

static int wdt_sample(int argc, char *argv[])
{
    rt_device_t wdt = rt_device_find("wdt");
    rt_device_init(wdt);
    rt_device_control(wdt, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, (void *)2);
    rt_device_control(wdt, RT_DEVICE_CTRL_WDT_START, RT_NULL);
}
MSH_CMD_EXPORT(wdt_sample, wdt sample);

#endif /* RT_USING_WDT */
