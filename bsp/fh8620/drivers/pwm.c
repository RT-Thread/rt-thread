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

#include "fh_def.h"
#include "pwm.h"
#include "interrupt.h"
#include "board_info.h"
#include "inc/fh_driverlib.h"
#include <rtthread.h>
#include <rtdevice.h>
#ifdef FH_PWM_DEBUG
#define PRINT_PWM_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_PWM_DEBUG: ");   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_PWM_DBG(fmt, args...)  do { } while (0)
#endif


static struct pwm_driver pwm_drv =
{

};




static int pwm_get_duty_cycle_ns(struct pwm_device* pwm)
{
    struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;
    rt_uint32_t reg, period, duty;
    rt_uint32_t clk_rate = 1000000/*todo: clk_get_rate(fh_pwm_ctrl.clk)*/;

    reg = PWM_GetPwmCmd(pwm_obj, pwm->id);
    period = reg & 0x0fff;
    duty = (reg >> 16) & 0xfff;
    duty = period - duty;       //reverse duty cycle

    if(period == 0)
    {
        period = duty;
    }

    pwm->counter_ns = duty * 1000000000 / clk_rate;
    pwm->period_ns = period * 1000000000 / clk_rate;

    PRINT_PWM_DBG("get duty: %d, period: %d, reg: 0x%x\n", duty, period, reg);

    return 0;
}

static int pwm_set_duty_cycle_ns(struct pwm_device* pwm)
{
    struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;
    rt_uint32_t period, duty, reg, clk_rate, duty_revert;
    clk_rate = 1000000/*todo: clk_get_rate(fh_pwm_ctrl.clk)*/;
    if(!clk_rate)
    {
        rt_kprintf("PWM: clock rate is 0\n");
        return -RT_EIO;
    }
    period = pwm->period_ns / (1000000000 / clk_rate);

    if(period < 8)
    {
        rt_kprintf("PWM: min period is 8\n");
        return -RT_EIO;
    }

    duty = pwm->counter_ns / (1000000000 / clk_rate);

    if(period < duty)
    {
        rt_kprintf("PWM: period < duty\n");
        return -RT_EIO;
    }

    duty_revert = period - duty;

    if(duty == period)
    {
        reg = (duty & 0xfff) << 16 | (0 & 0xfff);
    }
    else
    {
        reg = (duty_revert & 0xfff) << 16 | (period & 0xfff);
    }

    PRINT_PWM_DBG("set duty_revert: %d, period: %d, reg: 0x%x\n", duty_revert, period, reg);

    PWM_SetPwmCmd(pwm_obj, pwm->id, reg);
    return 0;
}




static rt_err_t fh_pwm_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;
    PWM_Enable(pwm_obj, RT_TRUE);
    return 0;
}

static rt_err_t fh_pwm_close(rt_device_t dev)
{
    struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;
    PWM_Enable(pwm_obj, RT_FALSE);
    return 0;
}

static rt_err_t fh_pwm_ioctl(rt_device_t dev, int cmd, void *arg)
{
    int ret = 0;
    struct pwm_device *pwm;
    struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)pwm_drv.priv;

    switch(cmd)
    {
    case ENABLE_PWM:
        PWM_Enable(pwm_obj, RT_FALSE);
        break;
    case DISABLE_PWM:
        PWM_Enable(pwm_obj, RT_TRUE);
        break;
    case SET_PWM_DUTY_CYCLE:
        pwm = (struct pwm_device *)arg;
        PRINT_PWM_DBG("ioctl: pwm addr: %p, pwm->period: %d ns\n", pwm, pwm->period_ns);
        pwm_set_duty_cycle_ns(pwm);
        break;
    case GET_PWM_DUTY_CYCLE:
        pwm = (struct pwm_device *)arg;
        PRINT_PWM_DBG("ioctl: pwm->id: %d, pwm->counter: %d, pwm->period: %d\n", pwm->id, pwm->counter_ns, pwm->period_ns);
        pwm_get_duty_cycle_ns(pwm);
        break;
    }

    return ret;
}

int fh_pwm_probe(void *priv_data)
{
    rt_device_t pwm_dev ;
    struct fh_pwm_obj *pwm_obj = (struct fh_pwm_obj *)priv_data;

    rt_memset(&pwm_drv, 0, sizeof(struct pwm_driver));

    pwm_drv.pwm[0].id = 0;
    pwm_drv.pwm[1].id = 1;
    pwm_drv.pwm[2].id = 2;

    pwm_drv.pwm[0].working = 0;
    pwm_drv.pwm[1].working = 0;
    pwm_drv.pwm[2].working = 0;

    pwm_drv.priv = pwm_obj;

    //todo: clk

    PWM_Enable(pwm_obj, RT_FALSE);

    pwm_dev = rt_calloc(1,sizeof(struct rt_device));

    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("ERROR: %s rt_device calloc failed\n", __func__);
        return -RT_ENOMEM;
    }
    
    pwm_dev->user_data = &pwm_drv;
    pwm_dev->open =fh_pwm_open;
    pwm_dev->close = fh_pwm_close;
    pwm_dev->control = fh_pwm_ioctl;
    pwm_dev->type    = RT_Device_Class_Miscellaneous;

    rt_device_register(pwm_dev, "pwm", RT_DEVICE_FLAG_RDWR);



    return 0;
}

int fh_pwm_exit(void *priv_data)
{
    return 0;
}

struct fh_board_ops pwm_driver_ops =
{
        .probe = fh_pwm_probe,
        .exit = fh_pwm_exit,
};

void rt_hw_pwm_init(void)
{
    PRINT_PWM_DBG("%s start\n", __func__);
    fh_board_driver_register("pwm", &pwm_driver_ops);
    PRINT_PWM_DBG("%s end\n", __func__);
}

