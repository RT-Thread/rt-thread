/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     Zero-Free    first version
 */

#include <rtdevice.h>

#ifdef RT_USING_PM

#include <drv_pmhw.h>

/**
 * This function caculate the PM tick from OS tick
 *
 * @param tick OS tick
 *
 * @return the PM tick
 */
static rt_tick_t stm32_pm_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq = pm_hwtim_get_countfreq();

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
    rt_uint32_t ret, freq;

    freq = pm_hwtim_get_countfreq();
    ret = (tick * RT_TICK_PER_SECOND + os_tick_remain) / freq;

    os_tick_remain += (tick * RT_TICK_PER_SECOND);
    os_tick_remain %= freq;

    return ret;
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

    if (timeout != RT_TICK_MAX)
    {
        /* Convert OS Tick to pmtimer timeout value */
        timeout = stm32_pm_tick_from_os_tick(timeout);
        if (timeout > pm_hwtim_get_tick_max())
        {
            timeout = pm_hwtim_get_tick_max();
        }

        /* Enter PM_TIMER_MODE */
        pm_hwtim_start(timeout);
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
    pm_hwtim_stop();
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

    timer_tick = pm_hwtim_get_current_tick();

    return stm32_os_tick_from_pm_tick(timer_tick);
}

/**
 * This function initialize the power manager
 */
int drv_pm_hw_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        pm_hw_sleep,
        pm_hw_run,
        pm_timer_start,
        pm_timer_stop,
        pm_timer_get_tick
    };

    rt_uint8_t timer_mask = 0;

    /* Enable Power Clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* initialize timer mask */
    timer_mask = 1UL << PM_SLEEP_MODE_DEEP;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}

INIT_BOARD_EXPORT(drv_pm_hw_init);

#endif  /* RT_USING_PM */
