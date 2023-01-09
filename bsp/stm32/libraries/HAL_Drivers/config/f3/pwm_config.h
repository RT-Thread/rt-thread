/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-13     zylx         first version
 */

#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PWM1
#define PWM1_CONFIG                             \
    {                                           \
       .tim_handle.Instance     = TIM1,         \
       .name                    = "pwm1",       \
       .channel                 = RT_NULL       \
    }
#endif /* BSP_USING_PWM1 */

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
