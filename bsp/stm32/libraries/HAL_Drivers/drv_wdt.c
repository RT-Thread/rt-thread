/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

struct stm32_wdt_obj
{
    rt_watchdog_t watchdog;
    IWDG_HandleTypeDef hiwdg;
    rt_uint16_t is_start;
};
static struct stm32_wdt_obj stm32_wdt;
static struct rt_watchdog_ops ops;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        if(HAL_IWDG_Refresh(&stm32_wdt.hiwdg) != HAL_OK)
        {
            LOG_E("watch dog keepalive fail.");
        }
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            stm32_wdt.hiwdg.Init.Reload = (*((rt_uint32_t*)arg)) * LSI_VALUE / 256 ;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
        if(stm32_wdt.hiwdg.Init.Reload > 0xFFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds",0xFFF * 256 / LSI_VALUE);
            return -RT_EINVAL;
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        if(stm32_wdt.is_start)
        {
            if (HAL_IWDG_Init(&stm32_wdt.hiwdg) != HAL_OK)
            {
                LOG_E("wdg set timeout failed.");
                return -RT_ERROR;
            }
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            (*((rt_uint32_t*)arg)) = stm32_wdt.hiwdg.Init.Reload * 256 / LSI_VALUE;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (HAL_IWDG_Init(&stm32_wdt.hiwdg) != HAL_OK)
        {
            LOG_E("wdt start failed.");
            return -RT_ERROR;
        }
        stm32_wdt.is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
#if defined(SOC_SERIES_STM32H7)
    stm32_wdt.hiwdg.Instance = IWDG1;
#else
    stm32_wdt.hiwdg.Instance = IWDG;
#endif
    stm32_wdt.hiwdg.Init.Prescaler = IWDG_PRESCALER_256;

    stm32_wdt.hiwdg.Init.Reload = 0x00000FFF;
#if defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F7) \
    || defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32L0)
    stm32_wdt.hiwdg.Init.Window = 0x00000FFF;
#endif
    stm32_wdt.is_start = 0;

    ops.init = &wdt_init;
    ops.control = &wdt_control;
    stm32_wdt.watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&stm32_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */
