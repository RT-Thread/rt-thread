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
 
#ifndef PWM_H_
#define PWM_H_


#include <rtthread.h>
#define ENABLE_PWM                  (0x10)
#define DISABLE_PWM                 (0x11)

#define SET_PWM_DUTY_CYCLE          (0x12)
#define GET_PWM_DUTY_CYCLE          (0x13)

struct pwm_device
{
    int id;
    int working;
    rt_uint32_t period_ns;
    rt_uint32_t counter_ns;
};

struct pwm_driver
{
    //struct clk          *clk;
    struct pwm_device   pwm[3];
    struct pwm_device   *cur;
    void*  priv;

};



#endif /* PWM_H_ */
