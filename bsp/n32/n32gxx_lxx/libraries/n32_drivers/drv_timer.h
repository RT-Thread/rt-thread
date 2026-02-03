/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __DRV_CLOCK_TIMER__
#define __DRV_CLOCK_TIMER__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* n32 config class */
struct n32_clock_timer_config
{
    const char  *name;
    TIM_Module* timer_periph;
    IRQn_Type   irqn;
};

struct n32_clock_timer
{
    rt_clock_timer_t              time_device;
    struct n32_clock_timer_config *config;
};

int rt_clock_timer_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CLOCK_TIMER__ */
