/*
 * File      : drv_iwg.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-11-08     ZYH            the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#ifdef RT_USING_WDT
IWDG_HandleTypeDef hiwdg;
static rt_err_t drv_init(rt_watchdog_t *wdt)
{
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_16; //1s
    hiwdg.Init.Reload = 4095;
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
    {
        RT_ASSERT(0);
    }
    return RT_EOK;
}

static rt_err_t drv_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        hiwdg.Init.Reload = (rt_uint32_t)arg;
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
