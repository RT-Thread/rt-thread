/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-5        YCHuang12        First version
*
* Note: 2 channels of a tpwm have the same output.
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_TPWM) && defined(RT_USING_PWM))

#define LOG_TAG                 "drv.tpwm"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define TPWM_CHANNEL_NUM        2
#include <rtdbg.h>

#include <stdint.h>
#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"

/* Private define ---------------------------------------------------------------*/
#define NU_TPWM_DEVICE(tpwm) (nu_tpwm_t *)(tpwm)

/* Private typedef --------------------------------------------------------------*/
typedef struct nu_tpwm
{
    struct rt_device_pwm tpwm_dev;
    char *name;
    TIMER_T *tpwm_base;
    rt_uint32_t channel_mask; //TPWM_CH0 | TPWM_CH1
} nu_tpwm_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_tpwm_enable(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config, rt_bool_t enable);
static rt_err_t nu_tpwm_set(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config);
static rt_err_t nu_tpwm_get(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config);
static rt_err_t nu_tpwm_control(struct rt_device_pwm *tpwm_dev, int cmd, void *arg);

/* Private variables ------------------------------------------------------------*/
#ifdef BSP_USING_TPWM0
    static nu_tpwm_t nu_tpwm0;
#endif

#ifdef BSP_USING_TPWM1
    static nu_tpwm_t nu_tpwm1;
#endif

#ifdef BSP_USING_TPWM2
    static nu_tpwm_t nu_tpwm2;
#endif

#ifdef BSP_USING_TPWM3
    static nu_tpwm_t nu_tpwm3;
#endif

static struct rt_pwm_ops nu_tpwm_ops =
{
    nu_tpwm_control
};

/* Functions define ------------------------------------------------------------*/
static rt_err_t nu_tpwm_enable(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config, rt_bool_t enable)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t tpwm_channel = tpwm_config->channel;
    nu_tpwm_t *nu_tpwm = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);

    if (enable == RT_TRUE)
    {
        if (nu_tpwm->channel_mask == 0)
        {
            TPWM_START_COUNTER(nu_tpwm->tpwm_base);
        }
        nu_tpwm->channel_mask |= (1 << tpwm_channel);
        TPWM_ENABLE_OUTPUT(nu_tpwm->tpwm_base, nu_tpwm->channel_mask);
    }
    else
    {
        nu_tpwm->channel_mask &= ~(1 << tpwm_channel);
        TPWM_ENABLE_OUTPUT(nu_tpwm->tpwm_base, nu_tpwm->channel_mask);
        if (nu_tpwm->channel_mask == 0)
        {
            TPWM_STOP_COUNTER(nu_tpwm->tpwm_base);
        }
    }

    return result;
}

static rt_err_t nu_tpwm_set(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config)
{
    if (tpwm_config->period <= 0)
        return -(RT_ERROR);

    rt_uint32_t tpwm_freq, tpwm_dutycycle ;
    rt_uint32_t tpwm_period = tpwm_config->period;
    rt_uint32_t tpwm_pulse = tpwm_config->pulse;
    nu_tpwm_t *nu_tpwm = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);

    rt_uint32_t pre_tpwm_prescaler = TPWM_GET_PRESCALER(nu_tpwm->tpwm_base);

    tpwm_freq = 1000000000 / tpwm_period;
    tpwm_dutycycle = (tpwm_pulse * 100) / tpwm_period;

    TPWM_ConfigOutputFreqAndDuty(nu_tpwm->tpwm_base, tpwm_freq, tpwm_dutycycle) ;

    return RT_EOK;
}

static rt_err_t nu_tpwm_get(struct rt_device_pwm *tpwm_dev, struct rt_pwm_configuration *tpwm_config)
{
    rt_uint32_t tpwm_real_period, tpwm_real_duty, time_tick, u32TPWMClockFreq ;

    nu_tpwm_t *nu_tpwm = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);
    rt_uint32_t tpwm_prescale = TPWM_GET_PRESCALER(nu_tpwm->tpwm_base);
    rt_uint32_t tpwm_period = TPWM_GET_PERIOD(nu_tpwm->tpwm_base);
    rt_uint32_t tpwm_pulse = TPWM_GET_CMPDAT(nu_tpwm->tpwm_base);

    u32TPWMClockFreq = TIMER_GetModuleClock(nu_tpwm->tpwm_base);
    time_tick = 1000000000000 / u32TPWMClockFreq;

    tpwm_real_period = (((tpwm_prescale + 1) * (tpwm_period + 1)) * time_tick) / 1000;
    tpwm_real_duty = (((tpwm_prescale + 1) * tpwm_pulse * time_tick)) / 1000;
    tpwm_config->period = tpwm_real_period;
    tpwm_config->pulse = tpwm_real_duty;

    LOG_I("%s %d %d %d\n", nu_tpwm->name, tpwm_config->channel, tpwm_config->period, tpwm_config->pulse);

    return RT_EOK;
}

static rt_err_t nu_tpwm_control(struct rt_device_pwm *tpwm_dev, int cmd, void *arg)
{
    struct rt_pwm_configuration *tpwm_config = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(tpwm_dev != RT_NULL);
    RT_ASSERT(tpwm_config != RT_NULL);

    nu_tpwm_t *nu_tpwm = NU_TPWM_DEVICE(tpwm_dev->parent.user_data);
    RT_ASSERT(nu_tpwm != RT_NULL);
    RT_ASSERT(nu_tpwm->tpwm_base != RT_NULL);

    if ((tpwm_config->channel + 1) > TPWM_CHANNEL_NUM)
        return -(RT_ERROR);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return nu_tpwm_enable(tpwm_dev, tpwm_config, RT_TRUE);
    case PWM_CMD_DISABLE:
        return nu_tpwm_enable(tpwm_dev, tpwm_config, RT_FALSE);
    case PWM_CMD_SET:
        return nu_tpwm_set(tpwm_dev, tpwm_config);
    case PWM_CMD_GET:
        return nu_tpwm_get(tpwm_dev, tpwm_config);
    default:
        break;
    }
    return -(RT_EINVAL);
}

int rt_hw_tpwm_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_TPWM0
    nu_tpwm0.tpwm_base = TIMER0;
    nu_tpwm0.name = "tpwm0";
    nu_tpwm0.channel_mask = 0;
    ret = rt_device_pwm_register(&nu_tpwm0.tpwm_dev, nu_tpwm0.name, &nu_tpwm_ops, &nu_tpwm0);
    if (ret != RT_EOK)
    {
        rt_kprintf("tpwm0 register failed\n");
    }
    SYS_ResetModule(TMR0_RST);
    CLK_EnableModuleClock(TMR0_MODULE);
    TPWM_ENABLE_PWM_MODE(TIMER0);
#endif

#ifdef BSP_USING_TPWM1
    nu_tpwm1.tpwm_base = TIMER1;
    nu_tpwm1.name = "tpwm1";
    nu_tpwm1.channel_mask = 0;
    ret = rt_device_pwm_register(&nu_tpwm1.tpwm_dev, nu_tpwm1.name, &nu_tpwm_ops, &nu_tpwm1);
    if (ret != RT_EOK)
    {
        rt_kprintf("tpwm1 register failed\n");
    }
    SYS_ResetModule(TMR1_RST);
    CLK_EnableModuleClock(TMR1_MODULE);
    TPWM_ENABLE_PWM_MODE(TIMER1);
#endif

#ifdef BSP_USING_TPWM2
    nu_tpwm2.tpwm_base = TIMER2;
    nu_tpwm2.name = "tpwm2";
    nu_tpwm2.channel_mask = 0;
    ret = rt_device_pwm_register(&nu_tpwm2.tpwm_dev, nu_tpwm2.name, &nu_tpwm_ops, &nu_tpwm2);
    if (ret != RT_EOK)
    {
        rt_kprintf("tpwm2 register failed\n");
    }
    SYS_ResetModule(TMR2_RST);
    CLK_EnableModuleClock(TMR2_MODULE);
    TPWM_ENABLE_PWM_MODE(TIMER2);
#endif

#ifdef BSP_USING_TPWM3
    nu_tpwm3.tpwm_base = TIMER3;
    nu_tpwm3.name = "tpwm3";
    nu_tpwm3.channel_mask = 0;
    ret = rt_device_pwm_register(&nu_tpwm3.tpwm_dev, nu_tpwm3.name, &nu_tpwm_ops, &nu_tpwm3);
    if (ret != RT_EOK)
    {
        rt_kprintf("tpwm3 register failed\n");
    }
    SYS_ResetModule(TMR3_RST);
    CLK_EnableModuleClock(TMR3_MODULE);
    TPWM_ENABLE_PWM_MODE(TIMER3);
#endif

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_tpwm_init);

#endif //#if (defined(BSP_USING_TPWM) && defined(RT_USING_PWM))
