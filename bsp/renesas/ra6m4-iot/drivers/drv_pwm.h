/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-25     KevinXu      first version
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>
#include <hal_data.h>

/* PWM device object structure */
struct ra_pwm
{
    struct rt_device_pwm            pwm_device;
    gpt_instance_ctrl_t             *g_ctrl;
    timer_instance_t const *const   g_timer;
    timer_cfg_t const *const        g_cfg;
    char                            *name;
};

/* Get ra6m4 pwm device object from the general pwm device object */
#define _GET_RA6M4_PWM_OBJ(ptr) rt_container_of(ptr, struct ra_pwm, pwm_device)

#endif /* __DRV_PWM_H__ */
