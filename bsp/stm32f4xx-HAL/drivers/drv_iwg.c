/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-11-08     ZYH            the first version
 */
#include <rtthread.h>
#include "board.h"
#include <rtdevice.h>
#include <rthw.h>
#ifdef RT_USING_WDT
IWDG_HandleTypeDef hiwdg;
static rt_err_t drv_init(rt_watchdog_t *wdt)
{
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_16;//1s
    hiwdg.Init.Reload = 4095;
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
    {
        while (1)
        {
        }
    }
    return RT_EOK;
}

static rt_err_t drv_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        hiwdg.Init.Reload = (rt_uint32_t)*arg;
        if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
        {
            return RT_ERROR;
        }
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        HAL_IWDG_Refresh(&hiwdg);
        break;
    default:
        return RT_ERROR;
    }
    return RT_EOK;
}

static struct rt_watchdog_ops _ops =
{
    drv_init,
    drv_control
};

static rt_watchdog_t _iwg =
{
    .ops = &_ops
};

int rt_iwg_init(void)
{
    return rt_hw_watchdog_register(&_iwg, "iwg", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL);
}
INIT_BOARD_EXPORT(rt_iwg_init);
#endif
