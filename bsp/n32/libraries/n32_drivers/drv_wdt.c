/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_wdt.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
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
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
    {
    }
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
#define WDT_RELOAD_SECOND       ((IWDG->RELV * LsiFreq) / IWDG->PREDIV)
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
            *(uint16_t *)args = relv*LsiFreq/prediv;
        }
        break;
        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        {
            RT_ASSERT(*(uint16_t *)args != 0);
            reload_value = *(uint16_t *)args;    
            if(reload_value >  0xFFF * 32 *1000 / LsiFreq)
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
            *(uint16_t *)args = relv*LsiFreq/prediv - \
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
            return RT_EINVAL;
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

