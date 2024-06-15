/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/02/19     flyingcys    first version
 */
#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include "cvi_pwm.h"

#define PWM_MAX_CH          3

int rt_hw_pwm_init(void);

#endif /* __DRV_PWM_H__ */
