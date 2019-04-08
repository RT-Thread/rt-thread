/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-04-01     wangyq        the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_pm.h"
#include <ald_pmu.h>

#ifdef RT_USING_PM

static void _drv_pm_enter(struct rt_pm *pm)
{
    rt_uint32_t mode;

    mode = pm->current_mode;

    switch (mode)
    {
    case PM_RUN_MODE_NORMAL:
        break;

    case PM_SLEEP_MODE_SLEEP:
        __WFI();
        break;

    case PM_SLEEP_MODE_TIMER:
        pmu_stop2_enter();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        pmu_standby_enter(PMU_STANDBY_PORT_NONE);
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

static void _drv_pm_exit(struct rt_pm *pm)
{
    rt_uint32_t mode;

    RT_ASSERT(pm != RT_NULL);

    mode = pm->current_mode;

    switch (mode)
    {
    case PM_RUN_MODE_NORMAL:
        break;

    case PM_SLEEP_MODE_SLEEP:
        break;

    case PM_SLEEP_MODE_TIMER:
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

#if PM_RUN_MODE_COUNT > 1
static void _drv_pm_frequency_change(struct rt_pm *pm, rt_uint32_t frequency)
{
    return;
}
#endif

static int drv_hw_pm_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        _drv_pm_enter,
        _drv_pm_exit,

#if PM_RUN_MODE_COUNT > 1
        _drv_pm_frequency_change,
#endif
        RT_NULL,
        RT_NULL,
        RT_NULL
    };

    rt_uint8_t timer_mask;

    /* initialize timer mask */
    timer_mask = 1UL << PM_SLEEP_MODE_TIMER;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}
INIT_BOARD_EXPORT(drv_hw_pm_init);

#endif
