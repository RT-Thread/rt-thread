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

#include "fsl_wwdt.h"
#include "fsl_clock.h"

#ifdef RT_USING_WDT

#define WDT_CLK_FREQ        CLOCK_GetWwdtClkFreq()
#define WWDT                WWDT0
#define APP_WDT_IRQn        WWDT0_IRQn
#define APP_WDT_IRQ_HANDLER WWDT0_IRQHandler

struct mcx_wdt
{
    rt_watchdog_t watchdog;
    WWDT_Type *wdt_base;
};

static struct mcx_wdt wdt_dev;

void APP_WDT_IRQ_HANDLER(void)
{
    uint32_t wdtStatus = WWDT_GetStatusFlags(WWDT);

    /*APP_LED_TOGGLE;*/

    /* The chip will reset before this happens */
    if (wdtStatus & kWWDT_TimeoutFlag)
    {
        WWDT_ClearStatusFlags(WWDT, kWWDT_TimeoutFlag);
    }

    /* Handle warning interrupt */
    if (wdtStatus & kWWDT_WarningFlag)
    {
        /* A watchdog feed didn't occur prior to warning timeout */
        WWDT_ClearStatusFlags(WWDT, kWWDT_WarningFlag);
        /* User code. User can do urgent case before timeout reset.
         * IE. user can backup the ram data or ram log to flash.
         * the period is set by config.warningValue, user need to
         * check the period between warning interrupt and timeout.
         */
    }
    SDK_ISR_EXIT_BARRIER;
}

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    wwdt_config_t config;
    uint32_t wdtFreq;
    bool timeOutResetEnable;

    /* Enable the WWDT time out to reset the CPU. */
    timeOutResetEnable = true;


    /* The WDT divides the input frequency into it by 4 */
    wdtFreq = WDT_CLK_FREQ / 4;

    WWDT_GetDefaultConfig(&config);

    /*
     * Set watchdog feed time constant to approximately 4s
     * Set watchdog warning time to 512 ticks after feed time constant
     * Set watchdog window time to 1s
     */
    config.timeoutValue = wdtFreq * 4;
    config.warningValue = 512;
    config.windowValue  = wdtFreq * 1;
    /* Configure WWDT to reset on timeout */
    config.enableWatchdogReset = true;
    /* Setup watchdog clock frequency(Hz). */
    config.clockFreq_Hz = WDT_CLK_FREQ;

    WWDT_Init(WWDT, &config);
    NVIC_EnableIRQ(APP_WDT_IRQn);

    return RT_EOK;
}

void delayWwdtWindow(void)
{
    /* For the TV counter register value will decrease after feed watch dog,
     * we can use it to as delay. But in user scene, user need feed watch dog
     * in the time period after enter Window but before warning intterupt.
     */
    while (WWDT->TV > WWDT->WINDOW)
    {
        __NOP();
    }
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
            delayWwdtWindow();
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
    wdt_dev.wdt_base = WWDT;

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
