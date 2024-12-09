/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-09     Your Name    The first version for MCXN236
 */

#include <rtthread.h>
#include "drv_wdt.h"

#include "fsl_wwdt.h"
#include "fsl_clock.h"

#ifdef RT_USING_WDT

#define WDT_CLK_FREQ        CLOCK_GetWdtClkFreq(0)

struct mcx_wdt
{
    rt_watchdog_t watchdog;
    WWDT_Type *wdt_base;
    clock_name_t clock_src;
    clock_ip_name_t clock_ip_name;
};

static struct mcx_wdt wdt_dev;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    uint32_t wdtFreq;

    wwdt_config_t config;

    /* The WDT divides the input frequency into it by 4 */
    wdtFreq = WDT_CLK_FREQ / 4;

    /* Enable FRO 1M clock for WWDT module. */
    SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK;

    WWDT_GetDefaultConfig(&config);

    config.timeoutValue = wdtFreq * 1;
    config.windowValue  = wdtFreq * 1;

    /* Configure WWDT to reset on timeout */
    config.enableWatchdogReset = true;

    /* Setup watchdog clock frequency(Hz). */
    config.clockFreq_Hz = WDT_CLK_FREQ;

    CLOCK_EnableClock(wdt_dev.clock_ip_name);
    CLOCK_SetClkDiv(kCLOCK_DivWdt0Clk, 1U);

    WWDT_Init(wdt_dev.wdt_base, &config);

    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        case RT_DEVICE_CTRL_WDT_START:
            WWDT_Enable(wdt_dev.wdt_base);
            return RT_EOK;

        case RT_DEVICE_CTRL_WDT_STOP:
            WWDT_Disable(wdt_dev.wdt_base);
            return RT_EOK;

        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            WWDT_Refresh(wdt_dev.wdt_base);
            return RT_EOK;

        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
            if (arg != RT_NULL)
            {
                uint32_t timeout = *((uint32_t *)arg);
                timeout = timeout * WDT_CLK_FREQ / 4;
                WWDT_SetTimeoutValue(wdt_dev.wdt_base, timeout);
                return RT_EOK;
            }
            return -RT_ERROR;

        default:
            return -RT_ERROR;
    }
}

static struct rt_watchdog_ops wdt_ops =
{
    wdt_init,
    wdt_control,
};

int rt_hw_wdt_init(void)
{
    wdt_dev.wdt_base = WWDT0;
    wdt_dev.clock_src = kCLOCK_Clk1M;
    wdt_dev.clock_ip_name = kCLOCK_Wwdt0;

    wdt_dev.watchdog.ops = &wdt_ops;

    if (rt_hw_watchdog_register(&wdt_dev.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        rt_kprintf("wdt register failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* RT_USING_WDT */
