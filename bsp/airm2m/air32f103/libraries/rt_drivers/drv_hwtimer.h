/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include <rtthread.h>

#ifdef BSP_USING_TIM
#include <board.h>

struct hwtimer_device
{
    struct rt_hwtimer_device parent;
    TIM_TypeDef *periph;
    IRQn_Type irqn;
    char *name;
};

#ifdef BSP_USING_TIM1
struct hwtimer_device hwtimer_device1 =
    {
        .periph = TIM1,
        .irqn = TIM1_UP_IRQn,
        .name = "timer1"};
#endif

#ifdef BSP_USING_TIM2
struct hwtimer_device hwtimer_device2 =
    {
        .periph = TIM2,
        .irqn = TIM2_IRQn,
        .name = "timer2"};
#endif

#ifdef BSP_USING_TIM3
struct hwtimer_device hwtimer_device3 =
    {
        .periph = TIM3,
        .irqn = TIM3_IRQn,
        .name = "timer3"};
#endif

#ifdef BSP_USING_TIM4
struct hwtimer_device hwtimer_device4 =
    {
        .periph = TIM4,
        .irqn = TIM4_IRQn,
        .name = "timer4"};
#endif

#endif /* BSP_USING_HWTIMER */
#endif /* __DRV_HWTIMER_H__ */
