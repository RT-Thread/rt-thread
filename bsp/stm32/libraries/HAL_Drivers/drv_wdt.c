/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-12-07     balanceTWK        first version
 */

#include <board.h>

#ifdef RT_USING_WDT

//#define DRV_DEBUG
#define LOG_TAG             "drv.wdt"
#include <drv_log.h>

static IWDG_HandleTypeDef hiwdg;
static struct rt_watchdog_ops ops;
static rt_watchdog_t watchdog;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_256;

    hiwdg.Init.Reload = 0x00000FFF;
#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F7)
    hiwdg.Init.Window = 0x00000FFF;
#endif

    if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
    {
        LOG_E("wdt init failed.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        HAL_IWDG_Refresh(&hiwdg);
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            hiwdg.Init.Reload = (*((rt_uint32_t*)arg)) * LSI_VALUE / 256 ;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        if(hiwdg.Init.Reload > 0xFFF)
        {
            LOG_E("wdg set timeout parameter too large.");
            return -RT_EINVAL;
        }
        if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
        {
            LOG_E("wdg set timeout failed.");
            return -RT_ERROR;
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            (*((rt_uint32_t*)arg)) = hiwdg.Init.Reload * 256 / LSI_VALUE;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        break;
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    ops.init = &wdt_init;
    ops.control = &wdt_control;
    watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */
