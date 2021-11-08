/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-10-26     KevinXu           first version
 */
#ifndef __PWM_CONFIG_H__
#define __PWM_CONFIG_H__

#include <rtthread.h>
#include <drv_config.h>
#include "hal_data.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
#ifdef BSP_USING_PWM0
    BSP_PWM0_INDEX,
#endif
#ifdef BSP_USING_PWM1
    BSP_PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    BSP_PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    BSP_PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    BSP_PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    BSP_PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM6
    BSP_PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    BSP_PWM7_INDEX,
#endif
#ifdef BSP_USING_PWM8
    BSP_PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    BSP_PWM9_INDEX,
#endif
    BSP_PWMS_NUM
};

#define PWM_DRV_INITIALIZER(num)        \
    {                                   \
        .name = "pwm"#num ,             \
        .g_cfg = &g_timer##num##_cfg,   \
        .g_ctrl = &g_timer##num##_ctrl, \
        .g_timer = &g_timer##num,       \
    }

#ifdef __cplusplus
}
#endif

#endif /* __PWM_CONFIG_H__ */
