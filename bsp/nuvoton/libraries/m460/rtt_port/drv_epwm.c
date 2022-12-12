/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-9-22       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_EPWM) && defined(RT_USING_PWM))

#define LOG_TAG                 "drv.epwm"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"

enum
{
    EPWM_START = -1,
#if defined(BSP_USING_EPWM0)
    EPWM0_IDX,
#endif
#if defined(BSP_USING_EPWM1)
    EPWM1_IDX,
#endif
    EPWM_CNT
};

struct nu_epwm
{
    struct rt_device_pwm dev;
    char                *name;
    EPWM_T              *base;
    uint32_t             rstidx;
    uint32_t             modid;
};

typedef struct nu_epwm *nu_epwm_t;

static struct nu_epwm nu_epwm_arr [] =
{
#if defined(BSP_USING_EPWM0)
    { .name = "epwm0", .base = EPWM0, .rstidx = EPWM0_RST, .modid = EPWM0_MODULE },
#endif

#if defined(BSP_USING_EPWM1)
    { .name = "epwm1", .base = EPWM1, .rstidx = EPWM1_RST, .modid = EPWM1_MODULE },
#endif

#if (EPWM_CNT==0)
    0
#endif
}; /* epwm nu_epwm */

static rt_err_t nu_epwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops nu_epwm_ops =
{
    .control = nu_epwm_control
};

static rt_err_t nu_epwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_err_t result = RT_EOK;

    EPWM_T *pwm_base = ((nu_epwm_t)device)->base;
    rt_uint32_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;

    if (enable == RT_TRUE)
    {
        EPWM_EnableOutput(pwm_base, 1 << pwm_channel);
        EPWM_Start(pwm_base, 1 << pwm_channel);
    }
    else
    {
        EPWM_DisableOutput(pwm_base, 1 << pwm_channel);
        EPWM_ForceStop(pwm_base, 1 << pwm_channel);
    }

    return result;
}

static rt_err_t nu_epwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    if ((((struct rt_pwm_configuration *)configuration)->period) <= 0)
        return -(RT_ERROR);

    rt_uint8_t  pwm_channel_pair;
    rt_uint32_t pwm_freq, pwm_dutycycle ;
    EPWM_T *pwm_base = ((nu_epwm_t)device)->base;
    rt_uint8_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;
    rt_uint32_t pwm_period = ((struct rt_pwm_configuration *)configuration)->period;
    rt_uint32_t pwm_pulse = ((struct rt_pwm_configuration *)configuration)->pulse;
    rt_uint32_t pre_pwm_prescaler = EPWM_GET_PRESCALER(pwm_base, pwm_channel);

    if ((pwm_channel % 2) == 0)
        pwm_channel_pair = pwm_channel + 1;
    else
        pwm_channel_pair = pwm_channel - 1;

    pwm_freq = (uint64_t)1000000000 / pwm_period;
    pwm_dutycycle = (pwm_pulse * 100) / pwm_period;

    EPWM_ConfigOutputChannel(pwm_base, pwm_channel, pwm_freq, pwm_dutycycle) ;

    if ((pre_pwm_prescaler != 0) || (EPWM_GET_CNR(pwm_base, pwm_channel_pair) != 0) || (EPWM_GET_CMR(pwm_base, pwm_channel_pair) != 0))
    {
        if (pre_pwm_prescaler < EPWM_GET_PRESCALER(pwm_base, pwm_channel))
        {
            EPWM_SET_CNR(pwm_base, pwm_channel_pair, ((EPWM_GET_CNR(pwm_base, pwm_channel_pair) + 1) * (pre_pwm_prescaler + 1)) / (EPWM_GET_PRESCALER(pwm_base, pwm_channel) + 1));
            EPWM_SET_CMR(pwm_base, pwm_channel_pair, (EPWM_GET_CMR(pwm_base, pwm_channel_pair) * (pre_pwm_prescaler + 1)) / (EPWM_GET_PRESCALER(pwm_base, pwm_channel) + 1));
        }
        else if (pre_pwm_prescaler > EPWM_GET_PRESCALER(pwm_base, pwm_channel))
        {
            EPWM_SET_CNR(pwm_base, pwm_channel, ((EPWM_GET_CNR(pwm_base, pwm_channel) + 1) * (EPWM_GET_PRESCALER(pwm_base, pwm_channel) + 1)) / (pre_pwm_prescaler + 1));
            EPWM_SET_CMR(pwm_base, pwm_channel, (EPWM_GET_CMR(pwm_base, pwm_channel) * (EPWM_GET_PRESCALER(pwm_base, pwm_channel) + 1)) / (pre_pwm_prescaler + 1));
        }
    }
    return RT_EOK;
}

static rt_uint32_t nu_epwm_clksr(struct rt_device_pwm *device)
{
    return CLK_GetPCLK0Freq(); //Both PCLK0 && PCLK1 are the same.
}

static rt_err_t nu_epwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t pwm_real_period, pwm_real_duty, time_tick, u32EPWMClockSrc ;

    EPWM_T *pwm_base = ((nu_epwm_t)device)->base;
    rt_uint32_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;
    rt_uint32_t pwm_prescale = EPWM_GET_PRESCALER(pwm_base, pwm_channel);
    rt_uint32_t pwm_period = EPWM_GET_CNR(pwm_base, pwm_channel);
    rt_uint32_t pwm_pulse = EPWM_GET_CMR(pwm_base, pwm_channel);

    u32EPWMClockSrc = nu_epwm_clksr(device);
    time_tick = (uint64_t)1000000000000 / u32EPWMClockSrc;

    pwm_real_period = (((pwm_prescale + 1) * (pwm_period + 1)) * time_tick) / 1000;
    pwm_real_duty = (((pwm_prescale + 1) * pwm_pulse * time_tick)) / 1000;
    ((struct rt_pwm_configuration *)configuration)->period = pwm_real_period;
    ((struct rt_pwm_configuration *)configuration)->pulse = pwm_real_duty;

    LOG_I("%s %d %d %d\n", ((nu_epwm_t)device)->name, configuration->channel, configuration->period, configuration->pulse);

    return RT_EOK;
}

static rt_err_t nu_epwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(device);
    RT_ASSERT(configuration);

    if (((((struct rt_pwm_configuration *)configuration)->channel) + 1) > EPWM_CHANNEL_NUM)
        return -(RT_ERROR);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return nu_epwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return nu_epwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return nu_epwm_set(device, configuration);
    case PWM_CMD_GET:
        return nu_epwm_get(device, configuration);
    }
    return -(RT_EINVAL);
}

int rt_hw_epwm_init(void)
{
    rt_err_t ret;
    int i;

    for (i = (EPWM_START + 1); i < EPWM_CNT; i++)
    {

        CLK_EnableModuleClock(nu_epwm_arr[i].modid);

        SYS_ResetModule(nu_epwm_arr[i].rstidx);

        ret = rt_device_pwm_register(&nu_epwm_arr[i].dev, nu_epwm_arr[i].name, &nu_epwm_ops, &nu_epwm_arr[i]);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_epwm_init);

#endif
