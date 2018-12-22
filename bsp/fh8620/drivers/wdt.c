/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#include "fh_def.h"
#include "wdt.h"
#include "interrupt.h"
#include "board_info.h"
#include "inc/fh_driverlib.h"
#include <rtdevice.h>
#include <drivers/watchdog.h>

#define FH_WDT_DEBUG

#ifdef FH_WDT_DEBUG
#define PRINT_WDT_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_WDT_DEBUG: ");   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_WDT_DBG(fmt, args...)  do { } while (0)
#endif

static int heartbeat = WDT_HEARTBEAT;

static rt_uint32_t fh_wdt_time_left(struct wdt_driver *wdt_drv)
{
    struct fh_wdt_obj *wdt_obj = wdt_drv->priv;
    //todo: get clk
    //return  WDT_GetCurrCount(wdt_obj) / WDT_CLOCK;
    return  WDT_GetCurrCount(wdt_obj) / 1800000;
}


static void fh_wdt_keepalive(struct wdt_driver *wdt_drv)
{
    struct fh_wdt_obj *wdt_obj = wdt_drv->priv;
    WDT_Kick(wdt_obj);
}

static inline void fh_wdt_set_next_heartbeat(struct wdt_driver *wdt_drv)
{
    wdt_drv->next_heartbeat = rt_tick_get() + heartbeat * RT_TICK_PER_SECOND;
}

static inline int fh_wdt_top_in_seconds(struct wdt_driver *wdt_drv, unsigned top)
{
    /*
     * There are 16 possible timeout values in 0..15 where the number of
     * cycles is 2 ^ (16 + i) and the watchdog counts down.
     */
    //todo: get_clk
    return (1 << (17 + top)) / 1800000;
}

static int fh_wdt_set_top(struct wdt_driver *wdt_drv, unsigned top_s)
{
    int i, top_val = FH_WDT_MAX_TOP;
    struct fh_wdt_obj *wdt_obj = wdt_drv->priv;

    /*
     * Iterate over the timeout values until we find the closest match. We
     * always look for >=.
     */

    for (i = 0; i <= FH_WDT_MAX_TOP; ++i)
        if (fh_wdt_top_in_seconds(wdt_drv, i) >= top_s) {
            top_val = i;
            break;
        }

    /* Set the new value in the watchdog. */
    PRINT_WDT_DBG("[wdt] set topval: %d\n", top_val);
    WDT_SetTopValue(wdt_obj, top_val);

    fh_wdt_set_next_heartbeat(wdt_drv);

    return fh_wdt_top_in_seconds(wdt_drv, top_val);
}


rt_err_t fh_watchdog_init(rt_watchdog_t *wdt)
{
    struct wdt_driver *wdt_drv = wdt->parent.user_data;
    struct fh_wdt_obj *wdt_obj = wdt_drv->priv;
    if (wdt_drv->in_use)
        return -RT_EBUSY;

    //todo: spinlock
    fh_wdt_set_top(wdt_drv, WDT_HW_TIMEOUT);///3000);
    if (!WDT_IsEnable(wdt_obj))
    {
        /*
         * The watchdog is not currently enabled. Set the timeout to
         * the maximum and then start it.
         */
        rt_uint32_t value;
        value = WDOG_CONTROL_REG_WDT_EN_MASK;
        value |= WDOG_CONTROL_REG_RMOD_MASK;
        WDT_SetCtrl(wdt_obj, value);
        fh_wdt_keepalive(wdt_drv);
    }

    fh_wdt_set_next_heartbeat(wdt_drv);

    //todo: unlock

    return RT_EOK;
}

rt_err_t fh_watchdog_ctrl(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct wdt_driver *wdt_drv = wdt->parent.user_data;
    struct fh_wdt_obj *wdt_obj = wdt_drv->priv;
    rt_uint32_t val;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_START:
        WDT_Enable(wdt_obj, RT_TRUE);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        WDT_Enable(wdt_obj, RT_FALSE);
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        //fh_wdt_set_next_heartbeat(wdt_drv);
        fh_wdt_keepalive(wdt_drv);
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        heartbeat = *((int*)(arg));
        PRINT_WDT_DBG("[wdt] settime value %lu\n", heartbeat);
        fh_wdt_set_top(wdt_drv, heartbeat);///3000);
        fh_wdt_keepalive(wdt_drv);
        fh_wdt_set_next_heartbeat(wdt_drv);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        arg = &heartbeat;
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        val = fh_wdt_time_left(wdt_drv);
        arg = &val;
        break;

    default:
        return -RT_EIO;
    }
    return RT_EOK;
}

static void fh_wdt_interrupt(int irq, void *param)
{
    //todo: stop
    //fh81_pmu_stop();
}

struct rt_watchdog_ops fh_watchdog_ops =
{
    .init = &fh_watchdog_init,
    .control = &fh_watchdog_ctrl,
};


int fh_wdt_probe(void *priv_data)
{
    rt_watchdog_t *wdt_dev;
    struct wdt_driver *wdt_drv;
    struct fh_wdt_obj *wdt_obj = (struct fh_wdt_obj *)priv_data;

    wdt_drv = (struct wdt_driver *)rt_malloc(sizeof(struct wdt_driver));
    rt_memset(wdt_drv, 0, sizeof(struct wdt_driver));

    wdt_drv->priv = wdt_obj;

    rt_hw_interrupt_install(wdt_obj->irq, fh_wdt_interrupt, (void *)wdt_drv, "wdt_irq");
    rt_hw_interrupt_umask(wdt_obj->irq);

    //todo: clk

    wdt_dev = (rt_watchdog_t *)rt_malloc(sizeof(rt_watchdog_t));

    if (wdt_dev == RT_NULL)
    {
        rt_kprintf("ERROR: %s rt_watchdog_t malloc failed\n", __func__);
    }

    wdt_dev->ops = &fh_watchdog_ops;

    rt_hw_watchdog_register(wdt_dev, "fh_wdt", RT_DEVICE_OFLAG_RDWR, wdt_drv);

    return 0;
}

int fh_wdt_exit(void *priv_data)
{
    return 0;
}

struct fh_board_ops wdt_driver_ops =
{
        .probe = fh_wdt_probe,
        .exit = fh_wdt_exit,
};

void rt_hw_wdt_init(void)
{
    PRINT_WDT_DBG("%s start\n", __func__);
    fh_board_driver_register("wdt", &wdt_driver_ops);
    PRINT_WDT_DBG("%s end\n", __func__);
}

void wdt_start(int timeout, int kick_times)
{
    rt_device_t wdt_dev;
    int ret;

    wdt_dev = rt_device_find("fh_wdt");

    rt_device_open(wdt_dev, 0);

    ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);

    int i = 0;
    for( ; i < kick_times; i ++ )
    {
        rt_thread_sleep(timeout * RT_TICK_PER_SECOND / 2);
        ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, &timeout);
        rt_kprintf( "kicked\n" );
    }

    rt_kprintf( "stop kick the watchdog, it shall reboot for %d seconds.\n", timeout * 2);

}

#ifdef RT_USING_WDT
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(wdt_start, enable wdt);
#endif
#endif
