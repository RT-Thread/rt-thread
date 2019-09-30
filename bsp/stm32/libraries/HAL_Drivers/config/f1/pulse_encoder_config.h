/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-23     balanceTWK   first version
 */

#ifndef __PULSE_ENCODER_CONFIG_H__
#define __PULSE_ENCODER_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PULSE_ENCODER1
#ifndef PULSE_ENCODER1_CONFIG
#define PULSE_ENCODER1_CONFIG                     \
    {                                             \
       .tim_handler.Instance     = TIM1,          \
       .encoder_irqn             = TIM1_UP_IRQn,  \
       .name                     = "pulse1"       \
    }
#endif /* PULSE_ENCODER1_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER1 */

#ifdef BSP_USING_PULSE_ENCODER2
#ifndef PULSE_ENCODER2_CONFIG
#define PULSE_ENCODER2_CONFIG                  \
    {                                          \
       .tim_handler.Instance     = TIM2,       \
       .encoder_irqn             = TIM2_IRQn,  \
       .name                     = "pulse2"    \
    }
#endif /* PULSE_ENCODER2_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER2 */

#ifdef BSP_USING_PULSE_ENCODER3
#ifndef PULSE_ENCODER3_CONFIG
#define PULSE_ENCODER3_CONFIG                  \
    {                                          \
       .tim_handler.Instance     = TIM3,       \
       .encoder_irqn             = TIM3_IRQn,  \
       .name                     = "pulse3"    \
    }
#endif /* PULSE_ENCODER3_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER3 */

#ifdef BSP_USING_PULSE_ENCODER4
#ifndef PULSE_ENCODER4_CONFIG
#define PULSE_ENCODER4_CONFIG                  \
    {                                          \
       .tim_handler.Instance     = TIM4,       \
       .encoder_irqn             = TIM4_IRQn,  \
       .name                     = "pulse4"    \
    }
#endif /* PULSE_ENCODER4_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER4 */

#ifdef __cplusplus
}
#endif

#endif /* __PULSE_ENCODER_CONFIG_H__ */
