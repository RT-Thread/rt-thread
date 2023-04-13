/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdbg.h>
#include "rtdevice.h"
#include "board.h"

#ifdef RT_USING_WDT

__IO uint32_t LsiFreq     = 40000;

static rt_err_t n32_wdt_close(rt_watchdog_t *wdt)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    /* Disable the LSI OSC */
    RCC_EnableLsi(DISABLE);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t n32_wdt_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    /* Enable the LSI OSC */
    RCC_EnableLsi(ENABLE);

    /* Wait till LSI is ready */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
    {
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    while (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET)
    {
    }
#endif

    /* Reload IWDG counter */
    IWDG_ReloadKey();
    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t n32_wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t n32_wdt_refresh(rt_watchdog_t *wdt)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    /* Reload IWDG counter */
    IWDG_ReloadKey();
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @function control wdt
 *
 * @param
 *    wdt  whick wdt used
 *    cmd  control wdt options
 *    args argument of conrtol
 * @retval rt_err_t the status of control result
 *
 *
 */
static rt_err_t n32_wdt_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    RT_ASSERT(wdt != NULL);

    uint16_t reload_value;
    uint32_t relv, prediv;
    static rt_tick_t last_tick = 0;

    relv = IWDG->RELV;
    prediv = IWDG->PREDIV;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
            {
                *(uint16_t *)args = ((relv * LsiFreq) / prediv);
            }
            break;

        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
            {
                RT_ASSERT(*(uint16_t *)args != 0);
                reload_value = *(uint16_t *)args;
                if (reload_value >  0xFFF * 32 *1000 / LsiFreq)
                {
                    LOG_W("wdg set timeout parameter too large, please less than %d ms\n", 0xFFF * 32 *1000 / LsiFreq);
                    return -RT_EINVAL;
                }
                /* Enable write access to IWDG_PR and IWDG_RLR registers */
                IWDG_WriteConfig(IWDG_WRITE_ENABLE);
                /* IWDG counter clock: LSI/32 */
                IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);
                reload_value = ((uint32_t)reload_value * LsiFreq / 1000) / 32;
                IWDG_CntReload(reload_value);
                IWDG_WriteConfig(IWDG_WRITE_DISABLE);
            }
            break;

        case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
            *(uint16_t *)args = ((relv * LsiFreq) / prediv) - \
                                (rt_tick_get() - last_tick) / RT_TICK_PER_SECOND;

            break;

        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            {
                last_tick = rt_tick_get();
                n32_wdt_refresh(wdt);
            }
            break;

        case RT_DEVICE_CTRL_WDT_START:
            {
                n32_wdt_open(wdt, *(rt_uint32_t *)args);
                last_tick = rt_tick_get();
            }
            break;

        case RT_DEVICE_CTRL_WDT_STOP:
            {
                n32_wdt_close(wdt);
            }
            break;

        default:
            return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops n32_wdt_ops =
{
    .init = n32_wdt_init,
    .control = n32_wdt_control,
};

static struct rt_watchdog_device n32_wdt_device;

int rt_hw_wdt_init(void)
{
    int result = RT_EOK;

    /* Disable the LSI OSC */
    RCC_EnableLsi(DISABLE);
    n32_wdt_device.ops = &n32_wdt_ops;
    /* register watchdog device */
    result = rt_hw_watchdog_register(&n32_wdt_device, "wdt", RT_DEVICE_FLAG_RDWR, (void *)IWDG);

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */

