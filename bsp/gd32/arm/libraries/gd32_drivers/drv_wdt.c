/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-25     iysheng           first version
 * 2025-10-09     kurisaw           fix inaccurate WDT clock timeout feeding issue
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>

#define DBG_TAG "drv.wdt"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#ifdef RT_USING_WDT

/* User-configurable macros for WDT clock source and prescaler */
/* Default select oscillator type: RCU_LXTAL */
#define WDT_OSCI_TYPE              RCU_LXTAL

/* Prescaler divider value (must match WDT_PSC_VALUE) */
#define WDT_PSC_DIVIDER            256U
/* Prescaler register value */
#define WDT_PSC_VALUE              FWDGT_PSC_DIV256

/* Derived values */
#define WDT_CLOCK_FREQ             LXTAL_VALUE

#define WDT_TICK_HZ                (WDT_CLOCK_FREQ / WDT_PSC_DIVIDER)
#define WDT_MAX_RELOAD_VALUE       0xfffU

typedef struct
{
    struct rt_watchdog_device wdt;
    rt_uint32_t min_threshold_s;
    rt_uint32_t max_threshold_s;
    rt_uint32_t current_threshold_s;
} gd32_wdt_device_t;

static gd32_wdt_device_t g_wdt_dev;

static rt_err_t gd32_wdt_init(rt_watchdog_t *wdt)
{
#if defined(SOC_SERIES_GD32H7xx)
    /* Enable and wait for oscillator stabilization */
    rcu_osci_on(WDT_OSCI_TYPE);
    if (ERROR == rcu_osci_stab_wait(WDT_OSCI_TYPE))
    {
        LOG_E("failed init %u clock for free watchdog.", WDT_OSCI_TYPE);
        return -RT_EINVAL;
    }
#endif

    /* Calculate thresholds */
    g_wdt_dev.min_threshold_s = 1U;
    g_wdt_dev.max_threshold_s = ((WDT_MAX_RELOAD_VALUE + 1U) * WDT_PSC_DIVIDER) / WDT_CLOCK_FREQ;
    LOG_I("WDT clock: %u Hz (tick: %u Hz), threshold section [%u, %u]",
          WDT_CLOCK_FREQ, WDT_TICK_HZ,
          g_wdt_dev.min_threshold_s, g_wdt_dev.max_threshold_s);

    /* Configure FWDGT with max timeout */
    fwdgt_write_enable();
    if (fwdgt_config(WDT_MAX_RELOAD_VALUE, WDT_PSC_VALUE) != SUCCESS)
    {
        LOG_E("failed to configure FWDGT");
        return -RT_ERROR;
    }
    fwdgt_enable();

    return RT_EOK;
}

static rt_err_t gd32_wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint32_t param;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        fwdgt_counter_reload();
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        param = *(rt_uint32_t *)arg;
        if ((param > g_wdt_dev.max_threshold_s) ||
            (param < g_wdt_dev.min_threshold_s))
        {
            LOG_E("invalid param@%u (out of [%u, %u])", param,
                  g_wdt_dev.min_threshold_s, g_wdt_dev.max_threshold_s);
            return -RT_EINVAL;
        }
        else
        {
            g_wdt_dev.current_threshold_s = param;
            rt_uint32_t reload_value = (param * WDT_TICK_HZ) - 1U;
            fwdgt_write_enable();
            if (fwdgt_config(reload_value, WDT_PSC_VALUE) != SUCCESS)
            {
                LOG_E("failed to set timeout %u s", param);
                return -RT_ERROR;
            }
            fwdgt_write_disable();
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = g_wdt_dev.current_threshold_s;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        fwdgt_enable();
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops g_wdt_ops = {
    gd32_wdt_init,
    gd32_wdt_control,
};

static int rt_hw_wdt_init(void)
{
    rt_err_t ret = RT_EOK;

    g_wdt_dev.wdt.ops = &g_wdt_ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&g_wdt_dev.wdt, "wdt",
                                RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        ret = -RT_ERROR;
    }
    else
    {
        LOG_D("wdt device register success.");
    }

    return ret;
}
INIT_PREV_EXPORT(rt_hw_wdt_init);
#endif
