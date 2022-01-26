/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-07     Tanek        first implementation
 * 2019-05-06     Zero-Free    adapt to the new power management interface
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifndef RT_USING_TIMER_SOFT
    #error "Please enable soft timer feature!"
#endif

#define TIMER_APP_DEFAULT_TICK  (RT_TICK_PER_SECOND * 2)

#ifdef RT_USING_PM

static rt_timer_t timer1;

static void _timeout_entry(void *parameter)
{
    rt_kprintf("current tick: %ld\n", rt_tick_get());
}

static int timer_app_init(void)
{
    timer1 = rt_timer_create("timer_app",
                             _timeout_entry,
                             RT_NULL,
                             TIMER_APP_DEFAULT_TICK,
                             RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
    if (timer1 != RT_NULL)
    {
        rt_timer_start(timer1);

        /* keep in timer mode */
        rt_pm_request(PM_SLEEP_MODE_DEEP);

        return 0;
    }
    else
    {
        return -1;
    }
}
INIT_APP_EXPORT(timer_app_init);

#endif /* RT_USING_PM */

