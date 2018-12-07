/*
 * File      : drv_i2c.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_PWM

rt_err_t pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

const struct rt_pwm_ops pwm_ops = {pwm_control};
struct rt_device_pwm _device_pwm0;
struct rt_device_pwm _device_pwm1;
struct rt_device_pwm _device_pwm2;
struct rt_device_pwm _device_pwm3;

rt_err_t pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration configuration = {0};

    RT_ASSERT(device)

    configuration = *(struct rt_pwm_configuration *)arg;

    if (&_device_pwm0 == device)
    {
        switch (cmd)
        {
        case PWM_CMD_ENABLE:
            if (2 == configuration.channel)
            {
                PWM_Start(PWM0, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Start(PWM0, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Start(PWM0, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Start(PWM0, 0, 0);
            }
            break;
        case PWM_CMD_DISABLE:
            if (2 == configuration.channel)
            {
                PWM_Stop(PWM0, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Stop(PWM0, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Stop(PWM0, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Stop(PWM0, 0, 0);
            }
            break;
        case PWM_CMD_SET:
            PWM_SetHDuty(PWM0, configuration.channel, configuration.pulse);
            PWM_SetCycle(PWM0, configuration.channel, configuration.period);
            break;
        case PWM_CMD_GET:
            configuration.pulse = PWM_GetHDuty(PWM0, configuration.channel);
            break;
        default:
            break;
        }
    }
    else if (&_device_pwm1 == device)
    {
        switch (cmd)
        {
        case PWM_CMD_ENABLE:
            if (2 == configuration.channel)
            {
                PWM_Start(PWM1, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Start(PWM1, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Start(PWM1, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Start(PWM1, 0, 0);
            }
            break;
        case PWM_CMD_DISABLE:
            if (2 == configuration.channel)
            {
                PWM_Stop(PWM1, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Stop(PWM1, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Stop(PWM1, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Stop(PWM1, 0, 0);
            }
            break;
        case PWM_CMD_SET:
            PWM_SetHDuty(PWM1, configuration.channel, configuration.pulse);
            PWM_SetCycle(PWM1, configuration.channel, configuration.period);
            break;
        case PWM_CMD_GET:
            configuration.pulse = PWM_GetHDuty(PWM1, configuration.channel);
            break;

        default:
            break;
        }
    }
    else if (&_device_pwm2 == device)
    {
        switch (cmd)
        {
        case PWM_CMD_ENABLE:
            if (2 == configuration.channel)
            {
                PWM_Start(PWM2, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Start(PWM2, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Start(PWM2, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Start(PWM2, 0, 0);
            }
            break;
        case PWM_CMD_DISABLE:
            if (2 == configuration.channel)
            {
                PWM_Stop(PWM2, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Stop(PWM2, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Stop(PWM2, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Stop(PWM2, 0, 0);
            }
            break;
        case PWM_CMD_SET:
            PWM_SetHDuty(PWM2, configuration.channel, configuration.pulse);
            PWM_SetCycle(PWM2, configuration.channel, configuration.period);
            break;
        case PWM_CMD_GET:
            configuration.pulse = PWM_GetHDuty(PWM2, configuration.channel);
            break;

        default:
            break;
        }
    }
    else if (&_device_pwm3 == device)
    {
        switch (cmd)
        {
        case PWM_CMD_ENABLE:
            if (2 == configuration.channel)
            {
                PWM_Start(PWM3, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Start(PWM3, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Start(PWM3, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Start(PWM3, 0, 0);
            }
            break;
        case PWM_CMD_DISABLE:
            if (2 == configuration.channel)
            {
                PWM_Stop(PWM3, 1, 1);
            }
            if (1 == configuration.channel)
            {
                PWM_Stop(PWM3, 0, 1);
            }
            if (0 == configuration.channel)
            {
                PWM_Stop(PWM3, 1, 0);
            }
            if (3 == configuration.channel)
            {
                PWM_Stop(PWM3, 0, 0);
            }
            break;
        case PWM_CMD_SET:
            PWM_SetHDuty(PWM3, configuration.channel, configuration.pulse);
            PWM_SetCycle(PWM3, configuration.channel, configuration.period);
            break;
        case PWM_CMD_GET:
            configuration.pulse = PWM_GetHDuty(PWM3, configuration.channel);
            break;

        default:
            break;
        }
    }
    else
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

int pwm_register(PWM_TypeDef *PWMx, const char *name)
{
    struct rt_device_pwm *device_pwm;
    const struct rt_pwm_ops *ops = &pwm_ops;
    void *user_data = NULL;
    PWM_InitStructure PWM_initStruct;

    PWM_initStruct.clk_div = PWM_CLKDIV_8; //F_PWM = 20M/8 = 2.5M
    PWM_initStruct.mode = PWM_MODE_INDEP;  //A路和B路独立输出
    PWM_initStruct.cycleA = 10000;         //2.5M/10000 = 250Hz
    PWM_initStruct.hdutyA = 2500;          //2500/10000 = 25%
    PWM_initStruct.initLevelA = 1;
    PWM_initStruct.cycleB = 10000;
    PWM_initStruct.hdutyB = 5000; //5000/10000 = 50%
    PWM_initStruct.initLevelB = 1;
    PWM_initStruct.HEndAIEn = 0;
    PWM_initStruct.NCycleAIEn = 0;
    PWM_initStruct.HEndBIEn = 0;
    PWM_initStruct.NCycleBIEn = 0;

    if (PWMx == PWM0)
    {
        PWM_Init(PWM0, &PWM_initStruct);
        PORT_Init(PORTA, PIN4, FUNMUX0_PWM0A_OUT, 0);
        PORT_Init(PORTA, PIN10, FUNMUX0_PWM0B_OUT, 0);

        device_pwm = &_device_pwm0;
    }
    else if (PWMx == PWM1)
    {
        PWM_Init(PWM1, &PWM_initStruct);
        PORT_Init(PORTA, PIN5, FUNMUX1_PWM1A_OUT, 0);
        PORT_Init(PORTA, PIN9, FUNMUX1_PWM1B_OUT, 0);
        device_pwm = &_device_pwm1;
    }
    else if (PWMx == PWM2)
    {
        PWM_Init(PWM2, &PWM_initStruct);
        PORT_Init(PORTP, PIN0, FUNMUX0_PWM2A_OUT, 0);
        PORT_Init(PORTP, PIN2, FUNMUX0_PWM2B_OUT, 0);
        device_pwm = &_device_pwm2;
    }
    else if (PWMx == PWM3)
    {
        PWM_Init(PWM3, &PWM_initStruct);
        PORT_Init(PORTP, PIN1, FUNMUX1_PWM3A_OUT, 0);
        PORT_Init(PORTP, PIN3, FUNMUX1_PWM3B_OUT, 0);
        device_pwm = &_device_pwm3;
    }
    else
    {
        return -1;
    }

    return rt_device_pwm_register(device_pwm, name, (struct rt_pwm_ops *)ops, user_data);
}

int drv_pwm_init(void)
{
    int result = 0;
#ifdef BSP_USING_PWM0
    result = pwm_register(PWM0, "pwm0");
#endif

#ifdef BSP_USING_PWM1
    result = pwm_register(PWM1, "pwm1");
#endif

#ifdef BSP_USING_PWM2
    result = pwm_register(PWM2, "pwm2");
#endif

#ifdef BSP_USING_PWM3
    result = pwm_register(PWM3, "pwm3");
#endif

    return result;
}
INIT_DEVICE_EXPORT(drv_pwm_init);

#endif //RT_USING_PWM
