/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     Zero-Free    first version
 * 2024-07-04     wdfk-prog    lptimer is supported
 */

#include <board.h>
#include <drv_lptim.h>
#include <rtdevice.h>

/*#define DRV_DEBUG*/
#define LOG_TAG             "drv.pm"
#include <drv_log.h>

#ifdef RT_USING_PM

#ifndef BSP_USING_PM_TIMER
/*
! Using LPTIM timer, the maximum sleep time is 65535, less than 1 min. Use RTC alarm timers for longer periods.
! For example: packages can be used :https://packages.rt-thread.org/detail.html?package=multi_rtimer
*/
#ifdef BSP_USING_LPTIM1
#define BSP_USING_PM_TIMER "lptim1"
#elif BSP_USING_LPTIM2
#define BSP_USING_PM_TIMER "lptim2"
#elif BSP_USING_LPTIM3
#define BSP_USING_PM_TIMER "lptim3"
#else
#error "Please define BSP_USING_PM_TIMER"
#endif

static rt_device_t timer = RT_NULL;

/* Re-configure the system clock */
rt_weak void SystemClock_ReConfig(uint8_t run_mode)
{
    /*todo add your code here*/
}

rt_weak void stm32_pm_device_run(struct rt_pm *pm, uint8_t mode)
{
    /*todo add your code here*/
}

/**
 * This function will put STM32L4xx into sleep mode.
 *
 * @param pm pointer to power manage structure
 */
static void sleep(struct rt_pm *pm, uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:
        if (pm->run_mode == PM_RUN_MODE_LOW_SPEED)
        {
            /* Enter LP SLEEP Mode, Enable low-power regulator */
            HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        }
        else
        {
            /* Enter SLEEP Mode, Main regulator is ON */
            HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        }
        break;

    case PM_SLEEP_MODE_DEEP:
#if defined(SOC_SERIES_STM32L4)
        /* Enter STOP 2 mode  */
        HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
        /* Re-configure the system clock */
        SystemClock_ReConfig(pm->run_mode);
#endif /* defined(SOC_SERIES_STM32L4) */
        break;

    case PM_SLEEP_MODE_STANDBY:
        /* Enter STANDBY mode */
        HAL_PWR_EnterSTANDBYMode();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
#if defined(SOC_SERIES_STM32L4)
        /* Enter SHUTDOWNN mode */
        HAL_PWREx_EnterSHUTDOWNMode();
#endif /* defined(SOC_SERIES_STM32L4) */
        break;

    default:
        break;
    }
}

/**
 * This function caculate the PM tick from OS tick
 *
 * @param tick OS tick
 *
 * @return the PM tick
 */
static rt_tick_t stm32_pm_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq = 0;
    rt_err_t ret = rt_device_control(timer, DRV_HW_LPTIMER_CTRL_GET_FREQ, &freq);
    if(ret != RT_EOK)
    {
        LOG_E("Get PM timer %s frequency failed %d", timer->parent.name, ret);
        return 0;
    }
    else
    {
        LOG_D("Get PM timer %s frequency %d", timer->parent.name, freq);
    }

    return (freq * tick / RT_TICK_PER_SECOND);
}

/**
 * This function caculate the OS tick from PM tick
 *
 * @param tick PM tick
 *
 * @return the OS tick
 */
static rt_tick_t stm32_os_tick_from_pm_tick(rt_uint32_t tick)
{
    static rt_uint32_t os_tick_remain = 0;
    rt_tick_t os_tick = 0;
    rt_uint32_t freq = 0;

    rt_err_t ret = rt_device_control(timer, DRV_HW_LPTIMER_CTRL_GET_FREQ, &freq);
    if(ret != RT_EOK)
    {
        LOG_E("Get PM timer %s frequency failed %d", timer->parent.name, ret);
        return 0;
    }

    os_tick = (tick * RT_TICK_PER_SECOND + os_tick_remain) / freq;

    os_tick_remain += (tick * RT_TICK_PER_SECOND);
    os_tick_remain %= freq;

    return os_tick;
}

/**
 * This function start the timer of pm
 *
 * @param pm Pointer to power manage structure
 * @param timeout How many OS Ticks that MCU can sleep
 */
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    RT_ASSERT(pm != RT_NULL);
    RT_ASSERT(timeout > 0);
    RT_ASSERT(timer != RT_NULL);

    if (timeout != RT_TICK_MAX)
    {
        rt_uint32_t max_tick = 0;
        rt_err_t ret = rt_device_control(timer, DRV_HW_LPTIMER_CTRL_GET_TICK_MAX, &max_tick);
        if(ret != RT_EOK)
        {
            LOG_E("Get PM timer %s max tick failed %d", timer->parent.name, ret);
            return;
        }

        /* Convert OS Tick to pmtimer timeout value */
        timeout = stm32_pm_tick_from_os_tick(timeout);

        if (timeout > max_tick)
        {
            timeout = max_tick;
        }

        /* Enter PM_TIMER_MODE */
        ret = rt_device_control(timer, DRV_HW_LPTIMER_CTRL_START, &timeout);
        if(ret != RT_EOK)
        {
            LOG_E("Get PM timer %s max tick failed %d", timer->parent.name, ret);
            return;
        }
    }
}

/**
 * This function stop the timer of pm
 *
 * @param pm Pointer to power manage structure
 */
static void pm_timer_stop(struct rt_pm *pm)
{
    RT_ASSERT(pm != RT_NULL);

    /* Reset pmtimer status */
    rt_device_control(timer, HWTIMER_CTRL_STOP, RT_NULL);
}

/**
 * This function calculate how many OS Ticks that MCU have suspended
 *
 * @param pm Pointer to power manage structure
 *
 * @return OS Ticks
 */
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    rt_uint32_t timer_tick;

    RT_ASSERT(pm != RT_NULL);

    rt_err_t ret = rt_device_control(timer, DRV_HW_LPTIMER_CTRL_GET_COUNT, &timer_tick);

    if(ret != RT_EOK)
    {
        LOG_E("Get PM timer %s count failed %d", timer->parent.name, ret);
        return 0;
    }
    else
    {
        return stm32_os_tick_from_pm_tick(timer_tick);
    }
}

static const struct rt_pm_ops _ops =
{
    sleep,
    stm32_pm_device_run,
    pm_timer_start,
    pm_timer_stop,
    pm_timer_get_tick
};

/**
 * This function initialize the power manager
 */
int drv_pm_hw_init(void)
{
    rt_uint8_t timer_mask = 0;

    /* Enable Power Clock */
#if !defined(SOC_SERIES_STM32H7) && !defined(SOC_SERIES_STM32WL) && !defined(SOC_SERIES_STM32WB)
    __HAL_RCC_PWR_CLK_ENABLE();
#ifdef SOC_SERIES_STM32F1
    __HAL_RCC_BKP_CLK_ENABLE();
#endif
#endif

    /* initialize timer mask */
    timer_mask = 1UL << PM_SLEEP_MODE_DEEP;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    timer = rt_device_find(BSP_USING_PM_TIMER);

    if(timer == RT_NULL)
    {
        LOG_E("Can't find PM timer device");
        return -RT_ERROR;
    }
    else
    {
        return rt_device_init(timer);
    }
}

INIT_CORE_EXPORT(drv_pm_hw_init);
#endif /* RT_USING_PM */
