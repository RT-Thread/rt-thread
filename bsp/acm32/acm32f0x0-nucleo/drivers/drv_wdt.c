/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-25     AisinoChip        First Version
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>


#ifdef RT_USING_WDT
#include "board.h"

struct acm32_wdt_obj
{
    union
    {
        WDT_HandleTypeDef       wdt;
        IWDT_HandleTypeDef      iwdt;
    } handle;
    rt_uint16_t             is_start;
    rt_uint16_t             type;
    rt_watchdog_t           watchdog;
};

#define TYPE_WDT         0
#define TYPE_IWDT        1
#define IWDT_FREQ        (32000)

#ifdef BSP_USING_WDT
    #define WDT_NAME        "wdt"
    static struct acm32_wdt_obj acm32_wdt;
#endif

#ifdef BSP_USING_IWDT
    #define IWDT_NAME       "iwdt"
    static struct acm32_wdt_obj acm32_iwdt;
#endif

static struct rt_watchdog_ops ops;

rt_inline rt_base_t calc_wdt_divisor_load(rt_uint32_t freq, rt_uint32_t sec, rt_uint32_t *divisor, rt_uint32_t *load)
{
    rt_uint32_t freqMaxSec = 0;
    rt_uint32_t minFreqDiv = WDT_DIVISOR_NONE;

    freqMaxSec = RT_UINT32_MAX / freq;

    while (minFreqDiv <= WDT_DIVISOR_128)
    {
        if (sec < freqMaxSec)
        {
            break;
        }
        minFreqDiv ++;
        freqMaxSec = RT_UINT32_MAX / freq * (1 << minFreqDiv);
    }

    if (minFreqDiv > WDT_DIVISOR_128)
    {
        return -1;
    }

    *divisor = minFreqDiv;
    *load = sec * (freq >> minFreqDiv);
    return 0;
}

rt_inline rt_base_t calc_iwdt_divisor_load(rt_uint32_t freq, rt_uint32_t sec, rt_uint32_t *divisor, rt_uint32_t *load)
{
    rt_uint32_t minFreqDiv = IWDT_CLOCK_PRESCALER_4;
    rt_uint32_t freqMaxMs = 0;

    freqMaxMs = IWDT_RELOAD_MAX_VALUE * 1000 / (freq >> (2 + minFreqDiv));

    while (minFreqDiv <= IWDT_CLOCK_PRESCALER_256)
    {
        if (sec * 1000 < freqMaxMs)
        {
            break;
        }
        minFreqDiv ++;
        freqMaxMs = IWDT_RELOAD_MAX_VALUE * 1000 / (freq >> (2 + minFreqDiv));
    }

    if (minFreqDiv > IWDT_CLOCK_PRESCALER_256)
    {
        return -1;
    }

    *divisor = minFreqDiv;
    if (sec < 1000)
    {
        *load = (sec * 1000) * IWDT_RELOAD_MAX_VALUE / freqMaxMs;
    }
    else
    {
        *load = (sec) * IWDT_RELOAD_MAX_VALUE / freqMaxMs / 1000;
    }
    return 0;
}

rt_inline rt_uint32_t calc_wdt_timeout(rt_uint32_t freq, rt_uint32_t divisor, rt_uint32_t count)
{
    /* 1 / ( freq / (1<<divisor) ) * (count) */
    return (rt_uint32_t)(((rt_uint64_t)count) * (1 << divisor) / (freq));
}

rt_inline rt_uint32_t calc_iwdt_timeout(rt_uint32_t freq, rt_uint32_t divisor, rt_uint32_t count)
{
    /* (freq >> (2+divisor)) / IWDT_RELOAD_MAX_VALUE * count */
    return count / (freq >> (2 + divisor));
}

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct acm32_wdt_obj *wdtObj = NULL;
    rt_uint32_t timer_clk_hz;
    rt_uint32_t divisor, load;

    RT_ASSERT(wdt != RT_NULL);

    wdtObj = rt_container_of(wdt, struct acm32_wdt_obj, watchdog);
    timer_clk_hz = System_Get_APBClock();

    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        if (TYPE_WDT == wdtObj->type)
        {
            HAL_WDT_Feed(&wdtObj->handle.wdt);
        }
        else
        {
            HAL_IWDT_Kick_Watchdog_Wait_For_Done(&wdtObj->handle.iwdt);
        }
        break;
    /* set watchdog timeout, seconds */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (TYPE_WDT == wdtObj->type)
        {
            if (calc_wdt_divisor_load(timer_clk_hz, (*((rt_uint32_t *)arg)), &divisor, &load))
            {
                return -RT_ERROR;
            }
            wdtObj->handle.wdt.Init.WDTDivisor = (WDT_DIVISOR)divisor;
            wdtObj->handle.wdt.Init.WDTLoad = load;
            HAL_WDT_Init(&wdtObj->handle.wdt);
        }
        else
        {
            if (calc_iwdt_divisor_load(IWDT_FREQ, (*((rt_uint32_t *)arg)), &divisor, &load))
            {
                return -RT_ERROR;
            }
            wdtObj->handle.iwdt.Instance = IWDT;
            wdtObj->handle.iwdt.Init.Prescaler = divisor;
            wdtObj->handle.iwdt.Init.Reload = load;
        }

        if (wdtObj->is_start)
        {
            if (TYPE_WDT == wdtObj->type)
            {
                HAL_WDT_Init(&wdtObj->handle.wdt);
            }
            else
            {
                HAL_IWDT_Init(&wdtObj->handle.iwdt);
            }
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        if (TYPE_WDT == wdtObj->type)
        {
            (*((rt_uint32_t *)arg)) = calc_wdt_timeout(timer_clk_hz,
                                      wdtObj->handle.wdt.Init.WDTDivisor,
                                      wdtObj->handle.wdt.Instance->COUNT);
        }
        else
        {
            return -RT_EINVAL;
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        if (TYPE_WDT == wdtObj->type)
        {
            (*((rt_uint32_t *)arg)) = calc_wdt_timeout(timer_clk_hz,
                                      wdtObj->handle.wdt.Init.WDTDivisor,
                                      wdtObj->handle.wdt.Init.WDTLoad);
        }
        else
        {
            (*((rt_uint32_t *)arg)) = calc_iwdt_timeout(IWDT_FREQ,
                                      wdtObj->handle.iwdt.Init.Prescaler,
                                      wdtObj->handle.iwdt.Init.Reload);
        }
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (TYPE_WDT == wdtObj->type)
        {
            wdtObj->handle.wdt.Instance = WDT;
            wdtObj->handle.wdt.Init.WDTMode = WDT_MODE_RST;
            wdtObj->handle.wdt.Init.WDTINTCLRTIME = 0xffff;
            HAL_WDT_Init(&wdtObj->handle.wdt);
            HAL_WDT_Start(&wdtObj->handle.wdt);
        }
        else
        {
            wdtObj->handle.iwdt.Instance->CMDR = IWDT_ENABLE_COMMAND;
            wdtObj->handle.iwdt.Init.Window = IWDT_RELOAD_MAX_VALUE;  /* window function disabled when window >= reload */
            wdtObj->handle.iwdt.Init.Wakeup = IWDT_RELOAD_MAX_VALUE;  /* wakeup function disabled when wakeup >= reload */
            HAL_IWDT_Init(&wdtObj->handle.iwdt);
        }
        wdtObj->is_start = 1;
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        if (TYPE_WDT == wdtObj->type)
        {
            HAL_WDT_Stop(&wdtObj->handle.wdt);
        }
        else
        {
            wdtObj->handle.iwdt.Instance->CMDR = IWDT_DISABLE_COMMAND;
        }
        wdtObj->is_start = 0;
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

#ifdef BSP_USING_WDT
    acm32_wdt.type = TYPE_WDT;
    acm32_wdt.is_start = 0;
    acm32_wdt.watchdog.ops = &ops;
    if (rt_hw_watchdog_register(&acm32_wdt.watchdog, WDT_NAME, RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        return -RT_ERROR;
    }
#endif
#ifdef BSP_USING_IWDT
    acm32_iwdt.type = TYPE_IWDT;
    acm32_iwdt.is_start = 0;
    acm32_iwdt.watchdog.ops = &ops;
    if (rt_hw_watchdog_register(&acm32_iwdt.watchdog, IWDT_NAME, RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        return -RT_ERROR;
    }
#endif

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */

