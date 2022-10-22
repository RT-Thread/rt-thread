/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-20     MXH          the first version
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include <rtthread.h>
#ifdef BSP_USING_PWM
#include "ch32v30x_tim.h"
#include <drivers/rt_drv_pwm.h>
#include <drivers/hwtimer.h>
#include <board.h>

#ifndef ITEM_NUM
#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
#endif

#define MAX_COUNTER     65535
#define MIN_COUNTER     2
#define MIN_PULSE       2
#define FLAG_NOT_INIT   0xFF

struct rtdevice_pwm_device
{
    struct rt_device_pwm parent;
    TIM_TypeDef* periph;
    rt_uint8_t channel[4];
    char* name;
};

#endif/* BSP_USING_PWM */

#endif/* __DRV_PWM_H__ */
