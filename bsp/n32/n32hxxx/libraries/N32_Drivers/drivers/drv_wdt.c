/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-02-24     ox-horse         first version
 * 2026-06-16     li.mengmeng      fix issues and add stop handler
 */

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_WDT

//#define DRV_DEBUG
#define LOG_TAG "drv.wdt"
#include <drv_log.h>

struct n32_wdt_obj
{
    rt_watchdog_t watchdog;
    IWDG_Module  *IWDGx;
    uint32_t      IWDG_Clk;
    void          (*IWDGX_ClkCmd)(uint32_t periph, FunctionalState Cmd);

    rt_uint32_t current_threshold_s;
    rt_uint32_t Reload;
    rt_uint16_t Prescaler;
    rt_uint16_t is_start;
};

static struct n32_wdt_obj     n32_wdt;
static struct rt_watchdog_ops ops;

static rt_uint32_t wdt_get_prescaler_factor(rt_uint16_t prescaler)
{
    switch (prescaler)
    {
    case IWDG_PRESCALER_DIV4:
        return 4;
    case IWDG_PRESCALER_DIV8:
        return 8;
    case IWDG_PRESCALER_DIV16:
        return 16;
    case IWDG_PRESCALER_DIV32:
        return 32;
    case IWDG_PRESCALER_DIV64:
        return 64;
    case IWDG_PRESCALER_DIV128:
        return 128;
    case IWDG_PRESCALER_DIV256:
    default:
        return 256;
    }
}

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    n32_wdt.IWDGX_ClkCmd(n32_wdt.IWDG_Clk, ENABLE);

    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint32_t reload_value;
    rt_uint32_t max_threshold_s;
    rt_uint32_t prescaler_factor;

    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        IWDG_ReloadKey(n32_wdt.IWDGx);
        break;

    /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        if (n32_wdt.is_start)
        {
            LOG_W("IWDG is already running, cannot change timeout\n");
            return -RT_EBUSY;
        }

        reload_value     = (*(rt_uint32_t *)arg);
        prescaler_factor = wdt_get_prescaler_factor(n32_wdt.Prescaler);

        if (LSI_VALUE)
        {
            max_threshold_s = ((n32_wdt.Reload + 1U) * prescaler_factor) / LSI_VALUE;

            if (reload_value > max_threshold_s)
            {
                LOG_W("wdg set timeout parameter too large, please less than %d-s\n", max_threshold_s);
                return -RT_EINVAL;
            }
            else
            {
                n32_wdt.current_threshold_s = reload_value;
                /* Calculate Reload Value */
                reload_value = (reload_value * (LSI_VALUE / prescaler_factor)) - 1U;

                /* Enable write access to IWDG_PR and IWDG_RLR registers */
                IWDG_WriteConfig(n32_wdt.IWDGx, IWDG_WRITE_ENABLE);
                /* Set IWDG PREDIV */
                IWDG_SetPrescalerDiv(n32_wdt.IWDGx, n32_wdt.Prescaler);
                /* Set Counter Reload Value */
                IWDG_CntReload(n32_wdt.IWDGx, (uint16_t)reload_value);
                /* Reload IWDG counter */
                IWDG_ReloadKey(n32_wdt.IWDGx);

                /* Disable write access to IWDG_PR and IWDG_RLR registers */
                IWDG_WriteConfig(n32_wdt.IWDGx, IWDG_WRITE_DISABLE);
            }
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
#else
#error "Please define the value of LSI_VALUE!"
#endif
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = n32_wdt.current_threshold_s;
        break;

    case RT_DEVICE_CTRL_WDT_START:
        if (n32_wdt.is_start)
        {
            LOG_W("IWDG is already started\n");
            return RT_EOK;
        }
        IWDG_Enable(n32_wdt.IWDGx);
        n32_wdt.is_start = 1;
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        LOG_W("IWDG cannot be stopped once started\n");
        return -RT_ENOSYS;

    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
#if defined(SOC_SERIES_N32H7xx)
    n32_wdt.IWDGx        = IWDG1;
    n32_wdt.IWDG_Clk     = (RCC_APB5_PERIPHEN_IWDG1PCLK | RCC_APB5_PERIPHEN_IWDG1PCLKLP);
    n32_wdt.IWDGX_ClkCmd = RCC_EnableAPB5PeriphClk2;
#endif

    n32_wdt.Prescaler = IWDG_PRESCALER_DIV256;
    n32_wdt.Reload    = 0xFFFU;
    n32_wdt.is_start  = 0U;

    ops.init             = &wdt_init;
    ops.control          = &wdt_control;
    n32_wdt.watchdog.ops = &ops;

    /* register watchdog device */
    if (rt_hw_watchdog_register(&n32_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */
