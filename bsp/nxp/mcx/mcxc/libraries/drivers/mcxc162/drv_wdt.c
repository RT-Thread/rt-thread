/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-03     Alex Yang    Add MCXC162 WWDT0 support
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "fsl_clock.h"
#include "fsl_wwdt.h"

#ifdef BSP_USING_WDT

#define DBG_TAG "drv.wwdt"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define MCXC162_WWDT_DEFAULT_TIMEOUT 5U

struct mcxc162_wwdt
{
    rt_watchdog_t watchdog;
    rt_uint32_t timeout;
    rt_bool_t started;
};

static struct mcxc162_wwdt mcxc162_wwdt = {
    .timeout = MCXC162_WWDT_DEFAULT_TIMEOUT,
};

static uint32_t mcxc162_wwdt_ticks_per_second(void)
{
    return CLOCK_GetWwdtClkFreq() / 4U;
}

static rt_err_t mcxc162_wwdt_set_timeout(rt_uint32_t timeout)
{
    uint64_t count = (uint64_t)mcxc162_wwdt_ticks_per_second() * timeout;

    if ((timeout == 0U) || (count > WWDT_TC_COUNT_MASK))
    {
        return -RT_EINVAL;
    }

    mcxc162_wwdt.timeout = timeout;
    if (mcxc162_wwdt.started)
    {
        WWDT_SetTimeoutValue(WWDT0, (uint32_t)count);
        WWDT_Refresh(WWDT0);
    }

    return RT_EOK;
}

static rt_err_t mcxc162_wwdt_init(rt_watchdog_t *watchdog)
{
    RT_UNUSED(watchdog);

    CLOCK_SetClockDiv(kCLOCK_DivWWDT0, 1U);

    return RT_EOK;
}

static rt_err_t mcxc162_wwdt_control(rt_watchdog_t *watchdog, int command, void *argument)
{
    rt_uint32_t *value = (rt_uint32_t *)argument;

    RT_UNUSED(watchdog);

    switch (command)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *value = mcxc162_wwdt.timeout;
        return RT_EOK;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        return mcxc162_wwdt_set_timeout(*value);

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *value = (WWDT0->TV + mcxc162_wwdt_ticks_per_second() - 1U) /
                 mcxc162_wwdt_ticks_per_second();
        return RT_EOK;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WWDT_Refresh(WWDT0);
        return RT_EOK;

    case RT_DEVICE_CTRL_WDT_START:
        if (!mcxc162_wwdt.started)
        {
            wwdt_config_t config;

            WWDT_GetDefaultConfig(&config);
            config.enableWatchdogReset = true;
            config.timeoutValue = mcxc162_wwdt_ticks_per_second() * mcxc162_wwdt.timeout;
            config.clockFreq_Hz = CLOCK_GetWwdtClkFreq();
            WWDT_Init(WWDT0, &config);
            mcxc162_wwdt.started = RT_TRUE;
        }
        else
        {
            WWDT_Refresh(WWDT0);
        }
        return RT_EOK;

    case RT_DEVICE_CTRL_WDT_STOP:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }
}

static const struct rt_watchdog_ops mcxc162_wwdt_ops = {
    .init = mcxc162_wwdt_init,
    .control = mcxc162_wwdt_control,
};

int rt_hw_wdt_init(void)
{
    mcxc162_wwdt.watchdog.ops = &mcxc162_wwdt_ops;

    if ((CMC->SRS & CMC_SRS_WWDT0_MASK) != 0U)
    {
        LOG_I("last reset was caused by WWDT0");
    }

    return rt_hw_watchdog_register(&mcxc162_wwdt.watchdog, "wdt",
                                   RT_DEVICE_FLAG_DEACTIVATE, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */
