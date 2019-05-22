/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-04-01     wangyq        the first version
 * 2019-05-06     Zero-Free     adapt to the new power management interface
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_pm.h"
#include <ald_pmu.h>

#ifdef RT_USING_PM

static void _drv_pm_enter(struct rt_pm *pm, uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        __WFI();
        break;

    case PM_SLEEP_MODE_LIGHT:
        break;

    case PM_SLEEP_MODE_DEEP:
        pmu_stop2_enter();
        break;

    case PM_SLEEP_MODE_STANDBY:
        pmu_standby_enter(PMU_STANDBY_PORT_NONE);
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

static int drv_hw_pm_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        _drv_pm_enter,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        RT_NULL
    };

    rt_uint8_t timer_mask = 0;

    /* initialize timer mask(no need tickless) */
    timer_mask = 1UL << PM_SLEEP_MODE_DEEP;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}
INIT_BOARD_EXPORT(drv_hw_pm_init);

#endif
