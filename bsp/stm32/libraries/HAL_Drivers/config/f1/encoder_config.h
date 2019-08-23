/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-23     balanceTWK   first version
 */

#ifndef __ENCODER_CONFIG_H__
#define __ENCODER_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_ENCODER1
#ifndef ENCODER1_CONFIG
#define ENCODER1_CONFIG                         \
    {                                           \
       .tim_handler.Instance     = TIM1,        \
       .name                    = "encoder1"    \
    }
#endif /* ENCODER1_CONFIG */
#endif /* BSP_USING_ENCODER1 */

#ifdef BSP_USING_ENCODER2
#ifndef ENCODER2_CONFIG
#define ENCODER2_CONFIG                         \
    {                                           \
       .tim_handler.Instance     = TIM2,        \
       .name                    = "encoder2"    \
    }
#endif /* ENCODER2_CONFIG */
#endif /* BSP_USING_ENCODER2 */

#ifdef BSP_USING_ENCODER3
#ifndef ENCODER3_CONFIG
#define ENCODER3_CONFIG                         \
    {                                           \
       .tim_handler.Instance     = TIM3,        \
       .name                    = "encoder3"    \
    }
#endif /* ENCODER3_CONFIG */
#endif /* BSP_USING_ENCODER3 */

#ifdef BSP_USING_ENCODER4
#ifndef ENCODER4_CONFIG
#define ENCODER4_CONFIG                         \
    {                                           \
       .tim_handler.Instance     = TIM4,        \
       .name                    = "encoder4"    \
    }
#endif /* ENCODER4_CONFIG */
#endif /* BSP_USING_ENCODER4 */

#ifdef __cplusplus
}
#endif

#endif /* __ENCODER_CONFIG_H__ */
