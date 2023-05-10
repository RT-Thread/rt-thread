/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-12-15     liuhy        the first version
 */

#include "drv_pm.h"

#ifdef RT_USING_PM

/* 注意：进入睡眠前，如果有中断挂起（SYSTICK、PENDSV、UART、EXTI等），睡眠将被瞬间唤醒。*/
static void sleep(struct rt_pm *pm, uint8_t mode)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_hw_interrupt_enable(0x88);

    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:
        ald_pmu_stop_enter();
        break;

    case PM_SLEEP_MODE_DEEP:
        ald_pmu_stop_enter();
        break;

    case PM_SLEEP_MODE_STANDBY:
        ald_pmu_stop_enter();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        ald_pmu_stop_enter();
        break;

    default:
        RT_ASSERT(0);
        break;
    }

    rt_hw_interrupt_enable(level);
}

static void run(struct rt_pm *pm, uint8_t mode)
{
    static uint8_t last_mode;

    if (mode == last_mode)
        return;
    last_mode = mode;

    switch (mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:
    case PM_RUN_MODE_NORMAL_SPEED:
    case PM_RUN_MODE_MEDIUM_SPEED:
    case PM_RUN_MODE_LOW_SPEED:
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
static rt_tick_t es32f3_pm_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq = 1;

    return (freq * tick / RT_TICK_PER_SECOND);
}

/**
 * This function caculate the OS tick from PM tick
 *
 * @param tick PM tick
 *
 * @return the OS tick
 */
static rt_tick_t es32f3_os_tick_from_pm_tick(rt_uint32_t tick)
{
    static rt_uint32_t os_tick_remain = 0;
    rt_uint32_t ret, freq;

    freq = 1;
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
        timeout = es32f3_pm_tick_from_os_tick(timeout);
        /* MAX 0xFFFF */
        if (timeout > 0xFFFF)
        {
            timeout = 0xFFFF;
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

    timer_tick = 1;

    return es32f3_os_tick_from_pm_tick(timer_tick);
}

/**
 * This function initialize the power manager
 */
int drv_pm_hw_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        sleep,
        run,
        pm_timer_start,
        pm_timer_stop,
        pm_timer_get_tick
    };

    rt_uint8_t timer_mask = 0;

    /* initialize timer mask */
    timer_mask = 1UL << PM_SLEEP_MODE_DEEP;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}
INIT_BOARD_EXPORT(drv_pm_hw_init);

#endif
