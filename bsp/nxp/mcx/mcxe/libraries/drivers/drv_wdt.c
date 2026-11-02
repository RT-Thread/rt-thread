/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-25     hywing       The first version for NXP MCXA153 Board
 */

#include <rtthread.h>
#include "drv_wdt.h"

#include "fsl_wdog32.h"
#include "fsl_clock.h"

#ifdef RT_USING_WDT

#define WDT                   WDOG
#define WDT_CLOCK_SOURCE      kWDOG32_ClockSource1 /* 0: Bus, 1: LPO, 2: SOSC, 3: SIRC */
#define WDT_CLOCK_SOURCE_FREQ (128 * 1000 / 256)   /* 128kHz LPO divided by 256 */

#define APP_WDT_IRQn        WDOG_EWM_IRQn
#define APP_WDT_IRQ_HANDLER WDOG_EWM_IRQHandler

struct mcx_wdt
{
    rt_watchdog_t watchdog;
    WDOG_Type    *wdt_base;
};

static struct mcx_wdt wdt_dev;

void APP_WDT_IRQ_HANDLER(void)
{
    /* ---- There's no WARN feature for WDOG32, will reset. ---- */
    for (;;)
    {
    }
}

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    wdog32_config_t config;

    WDOG32_GetDefaultConfig(&config);

    config.enableWdog32    = false;
    config.clockSource     = WDT_CLOCK_SOURCE;
    config.prescaler       = kWDOG32_ClockPrescalerDivide256;
    config.timeoutValue    = WDT_CLOCK_SOURCE_FREQ * 5;
    config.enableInterrupt = true;

    WDOG32_Init(WDT, &config);
    NVIC_EnableIRQ(APP_WDT_IRQn);

    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    /* Feed fast path */
    if (cmd == RT_DEVICE_CTRL_WDT_KEEPALIVE)
    {
        WDOG32_Refresh(wdt_dev.wdt_base);
        return RT_EOK;
    }

    __disable_irq();
    WDOG32_Unlock(wdt_dev.wdt_base);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_START:
        WDOG32_Enable(wdt_dev.wdt_base);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        WDOG32_Disable(wdt_dev.wdt_base);
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (arg != RT_NULL)
        {
            uint32_t timeout = *((uint32_t *)arg);
            timeout          = timeout * WDT_CLOCK_SOURCE_FREQ;
            WDOG32_SetTimeoutValue(wdt_dev.wdt_base, timeout);
        }
        break;

    default:
        break;
    }

    __enable_irq();
    return RT_EOK;
}

static struct rt_watchdog_ops wdt_ops =
    {
        wdt_init,
        wdt_control,
};

int rt_hw_wdt_init(void)
{
    wdt_dev.wdt_base     = WDT;
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
