/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     tyustli      the first version.
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_WDT

#if !defined(BSP_USING_WDT1) && !defined(BSP_USING_WDT3)
#error "Please define at least one BSP_USING_WDOGx"
#endif

#define LOG_TAG             "drv.wdt"
#include <drv_log.h>

#include "drv_wdt.h"
#include <rthw.h>
#include "rtdevice.h"

#if defined(BSP_USING_WDT3)
#include "fsl_rtwdog.h"

static rt_watchdog_t imxrt_watchdog3;
static rtwdog_config_t rtwdog_config_t_value;

static rt_err_t imxrt_hp_wdog3_close(rt_watchdog_t *wdt)
{
    rt_uint32_t level;
    RTWDOG_Type *base;
    base = (RTWDOG_Type *)wdt->parent.user_data;

    level = rt_hw_interrupt_disable();
    RTWDOG_Unlock(base);
    RTWDOG_Disable(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t imxrt_hp_wdog3_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    RTWDOG_Type *base;
    base = (RTWDOG_Type *)wdt->parent.user_data;

    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    RTWDOG_Unlock(base);
    RTWDOG_Enable(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t imxrt_hp_wdog3_init(rt_watchdog_t *wdt)
{
    RTWDOG_Type *base;
    base = (RTWDOG_Type *)wdt->parent.user_data;

    RTWDOG_GetDefaultConfig(&rtwdog_config_t_value);
    RTWDOG_Init(base, &rtwdog_config_t_value);
    imxrt_hp_wdog3_close(wdt);

    return RT_EOK;
}

static rt_err_t imxrt_hp_wdog3_refresh(rt_watchdog_t *wdt)
{
    RTWDOG_Type *base;
    base = (RTWDOG_Type *)wdt->parent.user_data;

    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    RTWDOG_Refresh(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @function control rtwdog
 *
 * @param
 *    wdt  whick wdog used
 *    cmd  control wdog options
 *    args argument of conrtol
 * @retval rt_err_t the status of control result
 *
 * @attention rtwdog unit is not seconds because seconds for system is to inaccurate
 *
 */
static rt_err_t imxrt_hp_wdog3_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    RT_ASSERT(wdt != NULL);

    RTWDOG_Type *base;
    base = (RTWDOG_Type *)wdt->parent.user_data;

    switch(cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
    {
        *(uint16_t *)args = base->TOVAL;
    }
    break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
    {
        RT_ASSERT(*(uint16_t *)args != 0);
        RTWDOG_Unlock(base);
        RTWDOG_SetTimeoutValue(base, *(uint16_t *)args);
        imxrt_hp_wdog3_close(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
    {
        *(uint16_t *)args = base->TOVAL - base->CNT;
    }
    break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
    {
        imxrt_hp_wdog3_refresh(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_START:
    {
        imxrt_hp_wdog3_open(wdt, *(rt_uint32_t *)args);
    }
    break;
    case RT_DEVICE_CTRL_WDT_STOP:
    {
        imxrt_hp_wdog3_close(wdt);
    }
    break;
    default:
        return RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops imxrt_wdog3_ops =
{
    .init = imxrt_hp_wdog3_init,
    .control = imxrt_hp_wdog3_control,
};

#endif /* BSP_USING_WDT3 */

#if defined(BSP_USING_WDT1)
#include "fsl_wdog.h"

static rt_watchdog_t imxrt_watchdog;
static wdog_config_t WDOG_1_config =
{
    .timeoutValue = 10,
    .enablePowerDown = false,
    .softwareResetExtension = false,
    .enableTimeOutAssert = false,
    .enableWdog = true,
    .workMode =
    {
        .enableWait = false,
        .enableStop = false,
        .enableDebug = false,
    },
    .enableInterrupt = false,
    .interruptTimeValue = 0,
};

static rt_err_t imxrt_hp_wdog_close(rt_watchdog_t *wdt)
{
    rt_uint32_t level;
    WDOG_Type *base;
    base = (WDOG_Type *)wdt->parent.user_data;

    level = rt_hw_interrupt_disable();
    WDOG_Disable(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t imxrt_hp_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    WDOG_Type *base;
    base = (WDOG_Type *)wdt->parent.user_data;
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    WDOG_Enable(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t imxrt_hp_wdog_init(rt_watchdog_t *wdt)
{
    WDOG_Type *base;
    base = (WDOG_Type *)wdt->parent.user_data;

    WDOG_Init(base, &WDOG_1_config);
    imxrt_hp_wdog_close(wdt);

    return RT_EOK;
}

static rt_err_t imxrt_hp_wdog_refresh(rt_watchdog_t *wdt)
{
    WDOG_Type *base;
    base = (WDOG_Type *)wdt->parent.user_data;

    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    WDOG_Refresh(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @function control wdog
 *
 * @param
 *    wdt  whick wdog used
 *    cmd  control wdog options
 *    args argument of conrtol
 * @retval rt_err_t the status of control result
 *
 * @attention wdog1/wdog2 is can not get left time(register not exist)  and wdogs unit is seconds
 *
 */
static rt_err_t imxrt_hp_wdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    RT_ASSERT(wdt != NULL);

    WDOG_Type *base;
    base = (WDOG_Type *)wdt->parent.user_data;

    switch(cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
    {
        *(uint16_t *)args = (base->WCR >> 8)  / 2;
    }
    break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
    {
        RT_ASSERT(*(uint16_t *)args != 0);
        WDOG_SetTimeoutValue(base, (*(uint16_t *)args) * 2);
        imxrt_hp_wdog_close(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
    {
        imxrt_hp_wdog_refresh(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_START:
    {
        imxrt_hp_wdog_open(wdt, *(rt_uint32_t *)args);
    }
    break;
    case RT_DEVICE_CTRL_WDT_STOP:
    {
        imxrt_hp_wdog_close(wdt);
    }
    break;
    default:
        return RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops imxrt_wdog_ops =
{
    .init = imxrt_hp_wdog_init,
    .control = imxrt_hp_wdog_control,
};

#endif /* BSP_USING_WDT1 */

int rt_hw_wdt_init(void)
{
    rt_err_t ret = RT_EOK;

#if defined (BSP_USING_WDT1)
    imxrt_watchdog.ops = &imxrt_wdog_ops;

    ret = rt_hw_watchdog_register(&imxrt_watchdog, "wdog1", RT_DEVICE_FLAG_RDWR, WDOG1);

    if (ret != RT_EOK)
    {
        LOG_E("rt device register failed %d\n", ret);
    }
#endif /* BSP_USING_WDT1 */

#if defined(BSP_USING_WDT3)
    imxrt_watchdog3.ops = &imxrt_wdog3_ops;

    ret = rt_hw_watchdog_register(&imxrt_watchdog3, "wdog3", RT_DEVICE_FLAG_RDWR, RTWDOG);

    if (ret != RT_EOK)
    {
        LOG_E("rt device register failed %d\n", ret);
    }
#endif /* BSP_USING_WDT3 */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */
