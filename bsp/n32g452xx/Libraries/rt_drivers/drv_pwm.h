/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-1-13      Leo          first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>
#include <drivers/rt_drv_pwm.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_TIM3_CH1
#ifndef PWM1_TIM3_CONFIG
#define PWM1_TIM3_CONFIG         \
    {                              \
        .tim_handle   = TIM3,        \
        .name         = "tim3pwm1",  \
        .channel      = 1            \
    }
#endif /* PWM1_TIM3_CONFIG */
#endif /* BSP_USING_TIM3_CH1 */

#ifdef BSP_USING_TIM3_CH2
#ifndef PWM2_TIM3_CONFIG
#define PWM2_TIM3_CONFIG         \
    {                              \
        .tim_handle   = TIM3,        \
        .name         = "tim3pwm2",  \
        .channel      = 2            \
    }
#endif /* PWM2_TIM3_CONFIG */
#endif /* BSP_USING_TIM3_CH2 */

#ifdef BSP_USING_TIM3_CH3
#ifndef PWM3_TIM3_CONFIG
#define PWM3_TIM3_CONFIG         \
    {                              \
        .tim_handle   = TIM3,        \
        .name         = "tim3pwm3",  \
        .channel      = 3            \
    }
#endif /* PWM3_TIM3_CONFIG */
#endif /* BSP_USING_TIM3_CH3 */

#ifdef BSP_USING_TIM3_CH4
#ifndef PWM4_TIM3_CONFIG
#define PWM4_TIM3_CONFIG             \
    {                              \
        .tim_handle   = TIM3,        \
        .name         = "tim3pwm4",  \
        .channel      = 4            \
    }
#endif /* PWM4_TIM3_CONFIG */
#endif /* BSP_USING_TIM3_CH4 */

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
