/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef FH_PWM_H_
#define FH_PWM_H_

#define OFFSET_PWM_CTRL                (0x00)
#define OFFSET_PWM_CMD(n)              (((n) * 4) + OFFSET_PWM_CTRL + 4)

struct fh_pwm_obj
{
    int                 id;
    int                 irq;
    unsigned int         base;
};

void PWM_Enable(struct fh_pwm_obj *pwm_obj, int enable);
void PWM_SetPwmCmd(struct fh_pwm_obj *pwm_obj, int device_id, unsigned int reg);
unsigned int PWM_GetPwmCmd(struct fh_pwm_obj *pwm_obj, int device_id);

#endif /* FH_PWM_H_ */
