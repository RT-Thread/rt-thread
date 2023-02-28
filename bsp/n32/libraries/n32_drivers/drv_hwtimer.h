/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __DRV_HWTIMER__
#define __DRV_HWTIMER__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* n32 config class */
struct n32_hwtimer_config
{
    const char  *name;
    TIM_Module* timer_periph;
    IRQn_Type   irqn;
};

struct n32_hwtimer
{
    rt_hwtimer_t              time_device;
    struct n32_hwtimer_config *config;
};

int rt_hwtimer_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_HWTIMER__ */
