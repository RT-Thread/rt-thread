/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-04     Alex         First version for MCXC444
 */

#include <rtthread.h>
#include "drv_wdt.h"

#include "fsl_cop.h"
#include "fsl_clock.h"


struct mcx_cop
{
    rt_watchdog_t watchdog;
    SIM_Type *cop_base;
};

static struct mcx_cop cop_dev;

static rt_err_t cop_init(rt_watchdog_t *wdt)
{
    cop_config_t config;

    COP_GetDefaultConfig(&config);

    config.timeoutMode = kCOP_ShortTimeoutMode;
    config.clockSource = kCOP_LpoClock;
    config.timeoutCycles = kCOP_2Power10CyclesOr2Power18Cycles;
    config.enableStop = true;
    config.enableDebug = true;


    COP_Init(cop_dev.cop_base, &config);

    return RT_EOK;
}

static rt_err_t cop_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        case RT_DEVICE_CTRL_WDT_START:
        {
            return RT_EOK;
        }
        case RT_DEVICE_CTRL_WDT_STOP:
        {
            COP_Disable(cop_dev.cop_base);
            return RT_EOK;
        }
        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        {
            COP_Refresh(cop_dev.cop_base);
            return RT_EOK;
        }
        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
            return -RT_ERROR;

        default:
            return -RT_ERROR;
    }
}

static struct rt_watchdog_ops cop_ops =
{
    cop_init,
    cop_control,
};

int rt_hw_cop_init(void)
{
    cop_dev.cop_base = SIM;

    cop_dev.watchdog.ops = &cop_ops;

    if (rt_hw_watchdog_register(&cop_dev.watchdog, "cop", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        rt_kprintf("cop register failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_cop_init);

