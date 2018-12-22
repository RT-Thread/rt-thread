/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "inc/fh_driverlib.h"

void PWM_Enable(struct fh_pwm_obj *pwm_obj, int enable)
{
    SET_REG(pwm_obj->base + OFFSET_PWM_CTRL, enable);
}

unsigned int PWM_GetPwmCmd(struct fh_pwm_obj *pwm_obj, int device_id)
{
    return GET_REG(pwm_obj->base + OFFSET_PWM_CMD(device_id));
}

void PWM_SetPwmCmd(struct fh_pwm_obj *pwm_obj, int device_id, unsigned int reg)
{
    SET_REG(pwm_obj->base + OFFSET_PWM_CMD(device_id), reg);
}
