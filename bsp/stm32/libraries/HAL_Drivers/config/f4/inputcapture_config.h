/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     ryan         first version
 */

#ifndef __IC_CONFIG_H__
#define __IC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_IC3
#ifndef IC3_CONFIG
#define IC3_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM3,                     \
       .tim_irqn                = TIM3_IRQn,                \
       .name                    = "inputcapture3",                 \
    }
#endif /* IC3_CONFIG */
#endif /* BSP_USING_IC3 */

#ifdef BSP_USING_IC5
#ifndef IC5_CONFIG
#define IC5_CONFIG                                         \
    {                                                       \
       .tim_handle.Instance     = TIM5,                     \
       .tim_irqn                = TIM5_IRQn,                \
       .name                    = "inputcapture5",                 \
    }
#endif /* IC5_CONFIG */
#endif /* BSP_USING_IC5 */

#ifdef BSP_USING_IC8
#ifndef IC8_CONFIG
#define IC8_CONFIG                             \
    {                                           \
       .tim_handle.Instance     = TIM8,         \
       .tim_irqn                = TIM8_CC_IRQn,                \
       .name                    = "inputcapture8",       \
       .channel                 = 0             \
    }
#endif /* IC8_CONFIG */
#endif /* BSP_USING_IC8 */

#ifdef __cplusplus
}
#endif

#endif /* __IC_CONFIG_H__ */
