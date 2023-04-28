/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     tyustli      the first version.
 * 2019-07-15     Magicoe      The first version for LPC55S6x, timeout unit is S not mS
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_WDT

#if !defined(BSP_USING_WDT)
#error "Please define at least one BSP_USING_WDOGx"
#endif

#define LOG_TAG             "drv.wdt"
#include <drv_log.h>

#include "drv_wdt.h"
#include <rthw.h>
#include "rtdevice.h"

#if defined(BSP_USING_WDT)
#include "fsl_wwdt.h"

struct lpc_wdt_obj
{
    rt_watchdog_t watchdog;
    rt_uint16_t is_start;
};

static struct lpc_wdt_obj lpc_wdt;
static wwdt_config_t WWDT1_config =
{
    /* Enable the watch dog */
    .enableWwdt   = true,
    /* Disable the watchdog timeout reset */
    .enableWatchdogReset = false,
    /* Disable the watchdog protection for updating the timeout value */
    .enableWatchdogProtect = false,
    /* Windowing is not in effect */
    .windowValue = 0xFFFFFFU,
    /* Set the timeout value to the max */
    .timeoutValue = 0xFFFFFFU,
    /* No warning is provided */
    .warningValue = 0,
    /* Set clock frequency. */
    .clockFreq_Hz = 0U,
};

void WDT_BOD_IRQHandler(void)
{
    uint32_t wdtStatus = WWDT_GetStatusFlags(WWDT);

    /* The chip will reset before this happens */
    if (wdtStatus & kWWDT_TimeoutFlag)
    {
        /* A watchdog feed didn't occur prior to window timeout */
        /* Stop WDT */
        WWDT_Disable(WWDT);
        WWDT_ClearStatusFlags(WWDT, kWWDT_TimeoutFlag);
        /* Needs restart */
        WWDT_Enable(WWDT);
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
}

static rt_err_t lpc_wwdt_close(rt_watchdog_t *wdt)
{
    rt_uint32_t level;
    WWDT_Type *base;
    base = (WWDT_Type *)wdt->parent.user_data;

    level = rt_hw_interrupt_disable();
    WWDT_Disable(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t lpc_wwdt_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    WWDT_Type *base;
    base = (WWDT_Type *)wdt->parent.user_data;
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    WWDT_Enable(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t lpc_wwdt_init(rt_watchdog_t *wdt)
{
    WWDT_Type *base;
    base = (WWDT_Type *)wdt->parent.user_data;

    /* Enable FRO 1M clock for WWDT module. */
    SYSCON->CLOCK_CTRL |= SYSCON_CLOCK_CTRL_FRO1MHZ_CLK_ENA_MASK;
    /* Set clock divider for WWDT clock source. */
    CLOCK_SetClkDiv(kCLOCK_DivWdtClk, 1U, true);

    WWDT_GetDefaultConfig(&WWDT1_config);

    /*
     * Set watchdog feed time constant to approximately 4s
     * Set watchdog warning time to 512 ticks after feed time constant
     * Set watchdog window time to 1s
     */
    /* The WDT divides the input frequency into it by 4 */
    WWDT1_config.timeoutValue = (CLOCK_GetWdtClkFreq() / 4) * 4;
    WWDT1_config.warningValue = 512;
    WWDT1_config.windowValue  = (CLOCK_GetWdtClkFreq() / 4) * 1;
    /* Configure WWDT to reset on timeout */
    WWDT1_config.enableWatchdogReset = true;
    /* Setup watchdog clock frequency(Hz). */
    WWDT1_config.clockFreq_Hz = CLOCK_GetWdtClkFreq();

    WWDT_Init(base, &WWDT1_config);
    lpc_wwdt_close(wdt);

    return RT_EOK;
}

static rt_err_t lpc_wwdt_refresh(rt_watchdog_t *wdt)
{
    WWDT_Type *base;
    base = (WWDT_Type *)wdt->parent.user_data;

    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    WWDT_Refresh(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @function control wdog
 *
 * @param
 *    wdt  whick wdog used
 *    cmd  control wdog options
 *    args argument of conrtol
 * @retval rt_err_t the status of control result
 *
 * @attention wdog1 is can not get left time(register not exist)  and wdogs unit is seconds
 *
 */
static rt_err_t lpc_wwdt_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    RT_ASSERT(wdt != NULL);

    WWDT_Type *base;
    base = (WWDT_Type *)wdt->parent.user_data;

    switch(cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
    {
        *(uint16_t *)args = WWDT1_config.timeoutValue;
    }
    break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
    {
        RT_ASSERT(*(uint16_t *)args != 0);

        WWDT1_config.timeoutValue = (CLOCK_GetWdtClkFreq() / 4) * (*(uint16_t *)args) * 2;
        WWDT1_config.warningValue = 512;
        WWDT1_config.windowValue  = (CLOCK_GetWdtClkFreq() / 4) * (*(uint16_t *)args) * 2 / 4;

        base->TC = WWDT_TC_COUNT(WWDT1_config.timeoutValue);
        base->WINDOW  = WWDT_WINDOW_WINDOW(WWDT1_config.windowValue);
        base->WARNINT = WWDT_WARNINT_WARNINT(WWDT1_config.warningValue);
        WWDT_Refresh(base);

        lpc_wwdt_close(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
    {
        lpc_wwdt_refresh(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_START:
    {
        lpc_wwdt_open(wdt, *(rt_uint32_t *)args);
    }
    break;
    case RT_DEVICE_CTRL_WDT_STOP:
    {
        lpc_wwdt_close(wdt);
    }
    break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops lpc_wwdt_ops =
{
    .init = lpc_wwdt_init,
    .control = lpc_wwdt_control,
};

#endif /* BSP_USING_WDT */

int rt_hw_wdt_init(void)
{
    rt_err_t ret = RT_EOK;

#if defined (BSP_USING_WDT)
    lpc_wdt.watchdog.ops = &lpc_wwdt_ops;

    ret = rt_hw_watchdog_register(&lpc_wdt.watchdog, "wdt", RT_DEVICE_FLAG_RDWR, WWDT);

    if (ret != RT_EOK)
    {
        LOG_E("rt device register failed %d\n", ret);
    }
#endif /* BSP_USING_WDT */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */
