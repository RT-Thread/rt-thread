/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-10-13   AisinoChip    first add to bsp
 */

#include "board.h"
#include <rtdevice.h>

#if defined(RT_USING_PM)

#define IWDT_SRC_CLK        32000
#define IWDT_CLK_PRESCALER  IWDT_CLOCK_PRESCALER_32
#define IWDT_CLK            (IWDT_SRC_CLK / (4<<IWDT_CLK_PRESCALER))

static IWDT_HandleTypeDef hiwdt;

static rt_tick_t get_pm_tick_from_os_tick(rt_tick_t tick)
{
    return (rt_tick_t)(IWDT_CLK * tick / RT_TICK_PER_SECOND);
}

static rt_tick_t get_os_tick_from_pm_tick(rt_tick_t tick)
{
    static rt_uint32_t os_tick_remain = 0;
    rt_uint32_t ret;

    ret = (tick * RT_TICK_PER_SECOND + os_tick_remain) / IWDT_CLK;

    os_tick_remain += (tick * RT_TICK_PER_SECOND);
    os_tick_remain %= IWDT_CLK;

    return ret;
}

static void _pm_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    RT_ASSERT(pm != RT_NULL);

    switch(mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:
        System_Enter_Sleep_Mode(SLEEPENTRY_WFI);
        break;

    case PM_SLEEP_MODE_DEEP:
        System_Enter_Stop_Mode(STOPENTRY_WFI);
        break;

    case PM_SLEEP_MODE_STANDBY:
        System_Enter_Standby_Mode();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    default:
        return;
    }
}

static void _pm_run(struct rt_pm *pm, rt_uint8_t mode)
{
    static rt_uint8_t prev_mode = 0;

    RT_ASSERT(pm != RT_NULL);

    if(prev_mode == mode)
    {
        return;
    }

    switch(mode)
    {
    case PM_RUN_MODE_HIGH_SPEED: /* 64Mhz */
    case PM_RUN_MODE_NORMAL_SPEED: /* 64Mhz */
        System_Clock_Init(64000000);
        break;

    case PM_RUN_MODE_MEDIUM_SPEED: /* 32Mhz */
        System_Clock_Init(32000000);
        break;

    case PM_RUN_MODE_LOW_SPEED: /* 8Mhz */
        System_Clock_Init(8000000);
        break;

    default:
        return;
    }

    SysTick_Config(System_Get_SystemClock() / RT_TICK_PER_SECOND);
    prev_mode = mode;
}

static void _pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    int tick;

    RT_ASSERT(pm != RT_NULL);
    IWDT_HandleTypeDef *phiwdt = (IWDT_HandleTypeDef *)(pm->parent.user_data);

    if(timeout != RT_TICK_MAX)
    {
        tick = get_pm_tick_from_os_tick(timeout);
        phiwdt->Instance = IWDT;
        phiwdt->Init.Prescaler = IWDT_CLK_PRESCALER;
        phiwdt->Init.Reload = tick;
        phiwdt->Init.Window = tick;  /* window function disabled when window >= reload */
        phiwdt->Init.Wakeup = tick - 1;  /* wakeup function disabled when wakeup >= reload */
        HAL_IWDT_Init(phiwdt);
    }
}

static void _pm_timer_stop(struct rt_pm *pm)
{
    RT_ASSERT(pm != RT_NULL);

    IWDT_HandleTypeDef *phiwdt = (IWDT_HandleTypeDef *)(pm->parent.user_data);

    phiwdt->Instance->CMDR = 0xFFFF;
}

static rt_tick_t _pm_timer_get_tick(struct rt_pm *pm)
{
    rt_tick_t tick;
    RT_ASSERT(pm != RT_NULL);

    tick = 1;

    return get_os_tick_from_pm_tick(tick);
}

static const struct rt_pm_ops _pm_ops =
{
    _pm_sleep,
    _pm_run,
    _pm_timer_start,
    _pm_timer_stop,
    _pm_timer_get_tick
};

/**
 * This function initialize the power manager
 */
int drv_pm_hw_init(void)
{

    rt_uint8_t timer_mask = 0;

    /* initialize timer mask */
    timer_mask = (1UL << PM_SLEEP_MODE_DEEP) | (1UL << PM_SLEEP_MODE_STANDBY);

    /* initialize system pm module */
    rt_system_pm_init(&_pm_ops, timer_mask, &hiwdt);

    return 0;
}
INIT_BOARD_EXPORT(drv_pm_hw_init);

#endif /* RT_USING_PM */

