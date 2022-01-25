/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-15     iysheng           first release
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <drivers/hwtimer.h>

typedef struct {
    TIMER_TypeDef *reg_base;
    IRQn_Type irqn;
    rcu_periph_enum rcu;
} gd32_hwtimer_data;

typedef struct {
    char dev_name[RT_NAME_MAX];
    const gd32_hwtimer_data hw_data;
    rt_hwtimer_t hwtimer_dev;
    const struct rt_hwtimer_info hwtimer_info;
} gd32_hwtimer_device;

#ifdef __cplusplus
}
#endif

#endif /* __DRV_HWTIMER_H__ */

