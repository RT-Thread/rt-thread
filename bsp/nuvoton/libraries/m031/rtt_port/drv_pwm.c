/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-02-04      klcheng      First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_PWM)

#define LOG_TAG                 "drv.pwm"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <stdint.h>
#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"

enum
{
    PWM_START = -1,
#if defined(BSP_USING_PWM0)
    PWM0_IDX,
#endif
#if defined(BSP_USING_PWM1)
    PWM1_IDX,
#endif
    PWM_CNT
};

struct nu_pwm
{
    struct rt_device_pwm dev;
    char *name;
    PWM_T *pwm_base;
    rt_int32_t pwm_period_time;
};

typedef struct nu_pwm *nu_pwm_t;

static struct nu_pwm nu_pwm_arr [] =
{
#if defined(BSP_USING_PWM0)
    {
        .name = "pwm0",
        .pwm_base = PWM0,
    },
#endif

#if defined(BSP_USING_PWM1)
    {
        .name = "pwm1",
        .pwm_base = PWM1,
    },
#endif
    {0}
}; /* pwm nu_pwm */

static rt_err_t nu_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops nu_pwm_ops =
{
    .control = nu_pwm_control
};

static rt_err_t nu_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_err_t result = RT_EOK;

    PWM_T *pwm_base = ((nu_pwm_t)device)->pwm_base;
    rt_uint32_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;

    if (enable == RT_TRUE)
    {
        PWM_EnableOutput(pwm_base, 1 << pwm_channel);
        PWM_Start(pwm_base, 1 << pwm_channel);
    }
    else
    {
        PWM_DisableOutput(pwm_base, 1 << pwm_channel);
        PWM_ForceStop(pwm_base, 1 << pwm_channel);
    }

    return result;
}

static rt_err_t nu_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    if ((((struct rt_pwm_configuration *)configuration)->period) <= 0)
        return -(RT_ERROR);
    rt_uint8_t  pwm_channel_pair;
    rt_uint32_t pwm_freq, pwm_dutycycle ;
    PWM_T *pwm_base = ((nu_pwm_t)device)->pwm_base;
    rt_uint8_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;
    rt_uint32_t pwm_period = ((struct rt_pwm_configuration *)configuration)->period;
    rt_uint32_t pwm_pulse = ((struct rt_pwm_configuration *)configuration)->pulse;

    //rt_uint32_t pre_pwm_prescaler = PWM_GET_PRESCALER(pwm_base, pwm_channel);

    if ((pwm_channel % 2) == 0)
        pwm_channel_pair = pwm_channel + 1;
    else
        pwm_channel_pair = pwm_channel - 1;

    if (PWM_GET_CNR(pwm_base, pwm_channel_pair!= 0))
    {
        pwm_period = ((nu_pwm_t)device)->pwm_period_time;
        LOG_I("%s output frequency is determined, user can only change the duty\n", ((nu_pwm_t)device)->name);
    }
    else
    {
         ((nu_pwm_t)device)->pwm_period_time = pwm_period;
    }

    pwm_freq = 1000000000 / pwm_period;
    pwm_dutycycle = (pwm_pulse * 100) / pwm_period;
    PWM_ConfigOutputChannel(pwm_base, pwm_channel, pwm_freq, pwm_dutycycle) ;

    return RT_EOK;
}

static rt_uint32_t nu_pwm_clksr(struct rt_device_pwm *device)
{
    rt_uint32_t u32Src, u32PWMClockSrc;
    PWM_T *pwm_base = ((nu_pwm_t)device)->pwm_base;
    if (pwm_base == PWM0)
    {
        u32Src = CLK->CLKSEL2 & CLK_CLKSEL2_PWM0SEL_Msk;
    }
    else     /* (pwm == PWM1) */
    {
        u32Src = CLK->CLKSEL2 & CLK_CLKSEL2_PWM1SEL_Msk;
    }

    if (u32Src == 0U)
    {
        /* clock source is from PLL clock */
        u32PWMClockSrc = CLK_GetPLLClockFreq();
    }
    else
    {
        /* clock source is from PCLK */
        SystemCoreClockUpdate();
        if (pwm_base == PWM0)
        {
            u32PWMClockSrc = CLK_GetPCLK0Freq();
        }
        else     /* (pwm == PWM1) */
        {
            u32PWMClockSrc = CLK_GetPCLK1Freq();
        }
    }
    return u32PWMClockSrc;
}

static rt_err_t nu_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t pwm_real_period, pwm_real_duty, time_tick, u32PWMClockSrc ;

    PWM_T *pwm_base = ((nu_pwm_t)device)->pwm_base;
    rt_uint32_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;
    rt_uint32_t pwm_prescale = PWM_GET_PRESCALER(pwm_base, pwm_channel);
    rt_uint32_t pwm_period = PWM_GET_CNR(pwm_base, pwm_channel);
    rt_uint32_t pwm_pulse = PWM_GET_CMR(pwm_base, pwm_channel);

    u32PWMClockSrc = nu_pwm_clksr(device);
    time_tick = 1000000000000 / u32PWMClockSrc;

    pwm_real_period = (((pwm_prescale + 1) * (pwm_period + 1)) * time_tick) / 1000;
    pwm_real_duty = (((pwm_prescale + 1) * pwm_pulse * time_tick)) / 1000;
    ((struct rt_pwm_configuration *)configuration)->period = pwm_real_period;
    ((struct rt_pwm_configuration *)configuration)->pulse = pwm_real_duty;

    LOG_I("%s %d %d %d\n", ((nu_pwm_t)device)->name, configuration->channel, configuration->period, configuration->pulse);

    return RT_EOK;
}

static rt_err_t nu_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    if (((((struct rt_pwm_configuration *)configuration)->channel) + 1) > PWM_CHANNEL_NUM)
        return -(RT_ERROR);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return nu_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return nu_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return nu_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return nu_pwm_get(device, configuration);
    }
    return -(RT_EINVAL);
}

int rt_hw_pwm_init(void)
{
    rt_err_t ret;
    int i;

    for (i = (PWM_START + 1); i < PWM_CNT; i++)
    {
        ret = rt_device_pwm_register(&nu_pwm_arr[i].dev, nu_pwm_arr[i].name, &nu_pwm_ops, RT_NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#ifdef RT_USING_FINSH
#include <finsh.h>

#ifdef FINSH_USING_MSH

static int xpwm_get(int argc, char **argv)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;
    struct rt_pwm_configuration configuration = {0};

    if (argc != 3)
    {
        rt_kprintf("Usage: pwm_get pwm1 1\n");
        result = -RT_ERROR;
        goto _exit;
    }

    device = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }

    configuration.channel = atoi(argv[2]);
    result = rt_device_control(&device->parent, PWM_CMD_GET, &configuration);

_exit:
    return result;
}

MSH_CMD_EXPORT(xpwm_get, xpwm_get <pwm_dev> <channel>);

#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */

#endif
