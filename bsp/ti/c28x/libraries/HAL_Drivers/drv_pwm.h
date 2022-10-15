/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-24     qiyu      first version
 */

#ifndef DRIVERS_DRV_PWM_H_
#define DRIVERS_DRV_PWM_H_
#include <board.h>
#include "rtdevice.h"

#ifdef BSP_USING_PWM
struct c28x_pwm
{
    struct rt_device_pwm pwm_device;
    volatile struct EPWM_REGS *pwm_regs;
    const char *name;
};

int c28x_pwm_init(void);
#endif /* BSP_USING_PWM */
#endif /* DRIVERS_DRV_PWM_H_ */
