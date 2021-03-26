/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include<rtdevice.h>
#include<rthw.h>

struct tm4c123_pwm
{
    struct tm4c123_pwm_config *config;
    struct rt_device_pwm  pwm_device;
};

/* tm4c123 config class */
struct tm4c123_pwm_config
{
    rt_uint8_t channel;
    char *name;
    uint32_t   counterMode;
    uint32_t   syncMode;
};

int rt_hw_pwm_init(void);

#endif /*__DRV_PWM_H__*/

/************************** end of file ******************/
