/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 */

#include <board.h>
#include "rtthread.h"
#include "rtdevice.h"

static rt_err_t swm320_wdt_init(rt_watchdog_t *wdt)
{
    WDT_Init(WDT, SystemCoreClock / 2, WDT_MODE_INTERRUPT);

    return RT_EOK;
}

static rt_err_t swm320_wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(uint32_t *)arg = WDT->LOAD;
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        WDT_Stop(WDT);
        WDT->LOAD = SystemCoreClock / 1000 * (*(uint32_t *)arg);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(uint32_t *)arg = WDT_GetValue(WDT);
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WDT_Feed(WDT);
        break;
    case RT_DEVICE_CTRL_WDT_START:
        WDT_Start(WDT);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        WDT_Stop(WDT);
        break;
    default:
        break;
    }

    return RT_EOK;
}

rt_watchdog_t swm320_wdt;
const static struct rt_watchdog_ops swm320_wdt_ops =
{
    swm320_wdt_init,
    swm320_wdt_control
};

int rt_hw_wdt_init(void)
{
    rt_err_t result = RT_EOK;

    swm320_wdt.ops = &swm320_wdt_ops;

    result = rt_hw_watchdog_register(&swm320_wdt,
                                     "wdt",
                                     RT_DEVICE_FLAG_RDWR,
                                     WDT);

    return result;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

void WDT_Handler(void)
{
    WDT_INTClr(WDT);
}
