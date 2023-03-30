/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2023-03-12       wcx1024979076    first version
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__
#include "bflb_pwm_v2.h"
#include "bflb_clock.h"
#include "board.h"
#include "hardware/pwm_v2_reg.h"
int rt_hw_pwm_init(void);

#endif /* __DRV_PWM_H__ */
