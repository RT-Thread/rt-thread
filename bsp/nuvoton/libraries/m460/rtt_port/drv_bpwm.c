/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-4-8        Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_BPWM) && defined(RT_USING_PWM))

#define LOG_TAG                 "drv.bpwm"
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
    BPWM_START = -1,
#if defined(BSP_USING_BPWM0)
    BPWM0_IDX,
#endif
#if defined(BSP_USING_BPWM1)
    BPWM1_IDX,
#endif
    BPWM_CNT
};

struct nu_bpwm
{
    struct rt_device_pwm dev;
    char                *name;
    BPWM_T              *base;
    uint32_t             rstidx;
    uint32_t             modid;
    rt_int32_t  pwm_period_time;
};

typedef struct nu_bpwm *nu_bpwm_t;

static struct nu_bpwm nu_bpwm_arr [] =
{
#if defined(BSP_USING_BPWM0)
    { .name = "bpwm0", .base = BPWM0, .rstidx = BPWM0_RST, .modid = BPWM0_MODULE },
#endif

#if defined(BSP_USING_BPWM1)
    { .name = "bpwm1", .base = BPWM1, .rstidx = BPWM1_RST, .modid = BPWM1_MODULE },
#endif

#if (BPWM_CNT==0)
    0
#endif
}; /* bpwm nu_bpwm */

static rt_err_t nu_bpwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops nu_bpwm_ops =
{
    .control = nu_bpwm_control
};

static rt_err_t nu_bpwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_err_t result = RT_EOK;

    BPWM_T *pwm_base = ((nu_bpwm_t)device)->base;
    rt_uint32_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;

    if (enable == RT_TRUE)
    {
        BPWM_EnableOutput(pwm_base, 1 << pwm_channel);
        BPWM_Start(pwm_base, 1 << pwm_channel);
    }
    else
    {
        BPWM_DisableOutput(pwm_base, 1 << pwm_channel);
        BPWM_ForceStop(pwm_base, 1 << pwm_channel);
    }

    return result;
}

static rt_err_t nu_bpwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    if ((((struct rt_pwm_configuration *)configuration)->period) <= 0)
        return -(RT_ERROR);

    rt_uint32_t pwm_freq, pwm_dutycycle;
    BPWM_T *pwm_base = ((nu_bpwm_t)device)->base;
    rt_uint8_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;
    rt_uint32_t pwm_period = ((struct rt_pwm_configuration *)configuration)->period;
    rt_uint32_t pwm_pulse = ((struct rt_pwm_configuration *)configuration)->pulse;

    pwm_dutycycle = (pwm_pulse * 100) / pwm_period;

    if (BPWM_GET_CNR(pwm_base, pwm_channel) != 0)
    {
        pwm_period = ((nu_bpwm_t)device)->pwm_period_time;
        LOG_I("%s output frequency is determined, user can only change the duty\n", ((nu_bpwm_t)device)->name);
    }
    else
    {
        ((nu_bpwm_t)device)->pwm_period_time = pwm_period;
    }

    pwm_freq = 1000000000 / pwm_period;


    BPWM_ConfigOutputChannel(pwm_base, pwm_channel, pwm_freq, pwm_dutycycle) ;

    return RT_EOK;
}

static rt_uint32_t nu_bpwm_clksr(struct rt_device_pwm *device)
{
    return CLK_GetPCLK0Freq(); //Both PCLK0 && PCLK1 are the same.
}

static rt_err_t nu_bpwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t pwm_real_period, pwm_real_duty, time_tick, u32BPWMClockSrc ;

    BPWM_T *pwm_base = ((nu_bpwm_t)device)->base;
    rt_uint32_t pwm_channel = ((struct rt_pwm_configuration *)configuration)->channel;
    rt_uint32_t pwm_prescale = pwm_base->CLKPSC;
    rt_uint32_t pwm_period = BPWM_GET_CNR(pwm_base, pwm_channel);
    rt_uint32_t pwm_pulse = BPWM_GET_CMR(pwm_base, pwm_channel);

    u32BPWMClockSrc = nu_bpwm_clksr(device);
    time_tick = (uint64_t)1000000000000 / u32BPWMClockSrc;

    pwm_real_period = (((pwm_prescale + 1) * (pwm_period + 1)) * time_tick) / 1000;
    pwm_real_duty = (((pwm_prescale + 1) * pwm_pulse * time_tick)) / 1000;
    ((struct rt_pwm_configuration *)configuration)->period = pwm_real_period;
    ((struct rt_pwm_configuration *)configuration)->pulse = pwm_real_duty;

    LOG_I("%s %d %d %d\n", ((nu_bpwm_t)device)->name, configuration->channel, configuration->period, configuration->pulse);

    return RT_EOK;
}

static rt_err_t nu_bpwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(device);
    RT_ASSERT(configuration);

    if (((((struct rt_pwm_configuration *)configuration)->channel) + 1) > BPWM_CHANNEL_NUM)
        return -(RT_ERROR);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return nu_bpwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return nu_bpwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return nu_bpwm_set(device, configuration);
    case PWM_CMD_GET:
        return nu_bpwm_get(device, configuration);
    }
    return -(RT_EINVAL);
}

int rt_hw_bpwm_init(void)
{
    rt_err_t ret;
    int i;

    for (i = (BPWM_START + 1); i < BPWM_CNT; i++)
    {

        CLK_EnableModuleClock(nu_bpwm_arr[i].modid);

        SYS_ResetModule(nu_bpwm_arr[i].rstidx);
        ret = rt_device_pwm_register(&nu_bpwm_arr[i].dev, nu_bpwm_arr[i].name, &nu_bpwm_ops, RT_NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_bpwm_init);

#endif
