/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-30     pomin        first version
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include <rthw.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_HWTIMER

typedef struct {
    uint32_t reg_base;
    IRQn_Type irqn;
    rcu_periph_enum rcu;
} gd32_hwtimer_data;

typedef struct {
    char dev_name[RT_NAME_MAX];
    const gd32_hwtimer_data hw_data;
    rt_hwtimer_t hwtimer_dev;
    const struct rt_hwtimer_info hwtimer_info;
} gd32_hwtimer_device;

enum timer_index_E {
#ifdef BSP_USING_HWTIMER0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_HWTIMER1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_HWTIMER2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_HWTIMER5
    TIM5_INDEX,
#endif
#ifdef BSP_USING_HWTIMER15
    TIM15_INDEX,
#endif
#ifdef BSP_USING_HWTIMER16
    TIM16_INDEX,
#endif
};

#endif

#ifdef __cplusplus
}
#endif

#endif /* __DRV_HWTIMER_H__ */
