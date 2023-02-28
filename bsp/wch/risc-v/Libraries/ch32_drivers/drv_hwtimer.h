/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-10     MXH          the first version
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include <rtthread.h>
#if defined(SOC_RISCV_SERIES_CH32V3)
#include "ch32v30x_tim.h"
#endif
#if defined(SOC_RISCV_SERIES_CH32V2)
#include "ch32v20x_tim.h"
#endif

#ifdef BSP_USING_HWTIMER

typedef struct
{
    TIM_TypeDef *instance;
    TIM_TimeBaseInitTypeDef init;
    rt_uint32_t rcc;

}TIM_HandleTypeDef;

struct ch32_hwtimer
{
    rt_hwtimer_t device;
    TIM_HandleTypeDef handle;
    IRQn_Type irqn;
    char *name;
};

/* TIM CONFIG */
#ifndef TIM_DEV_INFO_CONFIG
#define TIM_DEV_INFO_CONFIG                     \
    {                                           \
        .maxfreq = 1000000,                     \
        .minfreq = 3000,                        \
        .maxcnt  = 0xFFFF,                      \
        .cntmode = HWTIMER_CNTMODE_UP,          \
    }
#endif /* TIM_DEV_INFO_CONFIG */

#ifdef BSP_USING_TIM1
#define TIM1_CONFIG                         \
{                                           \
    .handle.instance = TIM1,                \
    .handle.rcc = RCC_APB2Periph_TIM1,      \
    .irqn = TIM1_UP_IRQn,                   \
    .name = "timer1",                       \
}
#endif /* BSP_USING_TIM1 */

#ifdef BSP_USING_TIM2
#define TIM2_CONFIG                         \
{                                           \
    .handle.instance = TIM2,                \
    .handle.rcc = RCC_APB1Periph_TIM2,      \
    .irqn = TIM2_IRQn,                      \
    .name = "timer2",                       \
}
#endif /* BSP_USING_TIM2 */

#ifdef BSP_USING_TIM3
#define TIM3_CONFIG                         \
{                                           \
    .handle.instance = TIM3,                \
    .handle.rcc = RCC_APB1Periph_TIM3,      \
    .irqn = TIM3_IRQn,                      \
    .name = "timer3",                       \
}
#endif /* BSP_USING_TIM3 */

#ifdef BSP_USING_TIM4
#define TIM4_CONFIG                         \
{                                           \
    .handle.instance = TIM4,                \
    .handle.rcc = RCC_APB1Periph_TIM4,      \
    .irqn = TIM4_IRQn,                      \
    .name = "timer4",                       \
}
#endif /* BSP_USING_TIM4 */

#ifdef BSP_USING_TIM5
#define TIM5_CONFIG                         \
{                                           \
    .handle.instance = TIM5,                \
    .handle.rcc = RCC_APB1Periph_TIM5,      \
    .irqn = TIM5_IRQn,                      \
    .name = "timer5",                       \
}
#endif /* BSP_USING_TIM5 */

#ifdef BSP_USING_TIM6
#define TIM6_CONFIG                         \
{                                           \
    .handle.instance = TIM6,                \
    .handle.rcc = RCC_APB1Periph_TIM6,      \
    .irqn = TIM6_IRQn,                      \
    .name = "timer6",                       \
}
#endif /* BSP_USING_TIM6 */

#ifdef BSP_USING_TIM7
#define TIM7_CONFIG                         \
{                                           \
    .handle.instance = TIM7,                \
    .handle.rcc = RCC_APB1Periph_TIM7,      \
    .irqn = TIM7_IRQn,                      \
    .name = "timer7",                       \
}
#endif /* BSP_USING_TIM7 */

#ifdef BSP_USING_TIM8
#define TIM8_CONFIG                         \
{                                           \
    .handle.instance = TIM8,                \
    .handle.rcc = RCC_APB2Periph_TIM8,      \
    .irqn = TIM8_UP_IRQn,                   \
    .name = "timer8",                       \
}
#endif /* BSP_USING_TIM8 */

#ifdef BSP_USING_TIM9
#define TIM9_CONFIG                         \
{                                           \
    .handle.instance = TIM9,                \
    .handle.rcc = RCC_APB2Periph_TIM9,      \
    .irqn = TIM9_UP_IRQn,                   \
    .name = "timer9",                       \
}
#endif /* BSP_USING_TIM9 */

#ifdef BSP_USING_TIM10
#define TIM10_CONFIG                        \
{                                           \
    .handle.instance = TIM10,               \
    .handle.rcc = RCC_APB2Periph_TIM10,     \
    .irqn = TIM10_UP_IRQn,                  \
    .name = "timer10",                      \
}
#endif /* BSP_USING_TIM10 */

#endif /* BSP_USING_HWTIMER */
#endif /* __DRV_HWTIMER_H__ */
