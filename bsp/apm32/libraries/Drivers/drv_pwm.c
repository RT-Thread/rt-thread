/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add apm32F4 serie MCU support
 * 2022-12-26     luobeihai         add apm32F0 serie MCU support
 */

#include <board.h>

#ifdef RT_USING_PWM
#include <drivers/rt_drv_pwm.h>

#define DBG_TAG               "drv.pwm"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE  2

/* Init timer gpio and enable clock */
extern void apm32_msp_timer_init(void *Instance);

enum
{
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM8
    PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    PWM9_INDEX,
#endif
#ifdef BSP_USING_PWM10
    PWM10_INDEX,
#endif
#ifdef BSP_USING_PWM11
    PWM11_INDEX,
#endif
#ifdef BSP_USING_PWM12
    PWM12_INDEX,
#endif
#ifdef BSP_USING_PWM13
    PWM13_INDEX,
#endif
#ifdef BSP_USING_PWM14
    PWM14_INDEX,
#endif
#ifdef BSP_USING_PWM15
    PWM15_INDEX,
#endif
#ifdef BSP_USING_PWM16
    PWM16_INDEX,
#endif
#ifdef BSP_USING_PWM17
    PWM17_INDEX,
#endif
};

struct apm32_pwm
{
    char       *name;
    TMR_T      *tmr;
    rt_uint8_t channel;
    struct rt_device_pwm pwm_device;
};

static struct apm32_pwm pwm_config[] =
{
#ifdef BSP_USING_PWM1
    {
        "pwm1",
        TMR1,
        0,
    },
#endif
#ifdef BSP_USING_PWM2
    {
        "pwm2",
        TMR2,
        0,
    },
#endif
#ifdef BSP_USING_PWM3
    {
        "pwm3",
        TMR3,
        0,
    },
#endif
#ifdef BSP_USING_PWM4
    {
        "pwm4",
        TMR4,
        0,
    },
#endif
#ifdef BSP_USING_PWM5
    {
        "pwm5",
        TMR5,
        0,
    },
#endif
#ifdef BSP_USING_PWM8
    {
        "pwm8",
        TMR8,
        0,
    },
#endif
#ifdef BSP_USING_PWM9
    {
        "pwm9",
        TMR9,
        0,
    },
#endif
#ifdef BSP_USING_PWM10
    {
        "pwm10",
        TMR10,
        0,
    },
#endif
#ifdef BSP_USING_PWM11
    {
        "pwm11",
        TMR11,
        0,
    },
#endif
#ifdef BSP_USING_PWM12
    {
        "pwm12",
        TMR12,
        0,
    },
#endif
#ifdef BSP_USING_PWM13
    {
        "pwm13",
        TMR13,
        0,
    },
#endif
#ifdef BSP_USING_PWM14
    {
        "pwm14",
        TMR14,
        0,
    },
#endif
#ifdef BSP_USING_PWM15
    {
        "pwm15",
        TMR15,
        0,
    },
#endif
#ifdef BSP_USING_PWM16
    {
        "pwm16",
        TMR16,
        0,
    },
#endif
#ifdef BSP_USING_PWM17
    {
        "pwm17",
        TMR17,
        0,
    },
#endif
};

static void pwm_channel_init(void)
{
#ifdef BSP_USING_PWM1_CH1
    pwm_config[PWM1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM1_CH2
    pwm_config[PWM1_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM1_CH3
    pwm_config[PWM1_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM1_CH4
    pwm_config[PWM1_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM2_CH1
    pwm_config[PWM2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM2_CH2
    pwm_config[PWM2_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM2_CH3
    pwm_config[PWM2_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM2_CH4
    pwm_config[PWM2_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM3_CH1
    pwm_config[PWM3_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM3_CH2
    pwm_config[PWM3_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM3_CH3
    pwm_config[PWM3_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM3_CH4
    pwm_config[PWM3_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM4_CH1
    pwm_config[PWM4_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM4_CH2
    pwm_config[PWM4_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM4_CH3
    pwm_config[PWM4_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM4_CH4
    pwm_config[PWM4_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM5_CH1
    pwm_config[PWM5_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM5_CH2
    pwm_config[PWM5_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM5_CH3
    pwm_config[PWM5_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM5_CH4
    pwm_config[PWM5_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM8_CH1
    pwm_config[PWM8_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM8_CH2
    pwm_config[PWM8_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM8_CH3
    pwm_config[PWM8_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM8_CH4
    pwm_config[PWM8_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM9_CH1
    pwm_config[PWM9_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM9_CH2
    pwm_config[PWM9_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM10_CH1
    pwm_config[PWM10_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM11_CH1
    pwm_config[PWM11_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM12_CH1
    pwm_config[PWM12_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM12_CH2
    pwm_config[PWM12_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM13_CH1
    pwm_config[PWM13_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM14_CH1
    pwm_config[PWM14_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM15_CH1
    pwm_config[PWM15_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM15_CH2
    pwm_config[PWM15_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM16_CH1
    pwm_config[PWM16_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM17_CH1
    pwm_config[PWM17_INDEX].channel |= 1 << 0;
#endif
}

static rt_err_t apm32_pwm_hw_init(struct apm32_pwm *device)
{
    rt_err_t result = RT_EOK;
    TMR_T *tmr = RT_NULL;
    
    RT_ASSERT(device != RT_NULL);
    tmr = (TMR_T *)device->tmr;
    
    /* Init timer gpio and enable clock */
    apm32_msp_timer_init(tmr);
    
#if defined(SOC_SERIES_APM32F0)
    TMR_TimeBase_T   base_config;
    TMR_OCConfig_T     oc_config;
    
    /* configure the tmrer to pwm mode */
    base_config.div = 0;
    base_config.counterMode = TMR_COUNTER_MODE_UP;
    base_config.period = 0;
    base_config.clockDivision = TMR_CKD_DIV1;
    TMR_ConfigTimeBase(tmr, &base_config);

    TMR_SelectOutputTrigger(tmr, TMR_TRGOSOURCE_RESET);
    TMR_DisableMasterSlaveMode(tmr);

    oc_config.OC_Mode = TMR_OC_MODE_PWM1;
    oc_config.Pulse = 0;
    oc_config.OC_Polarity = TMR_OC_POLARITY_HIGH;
    oc_config.OC_NIdlestate = TMR_OCNIDLESTATE_RESET;
    oc_config.OC_Idlestate  = TMR_OCIDLESTATE_RESET;
    oc_config.OC_OutputState = TMR_OUTPUT_STATE_ENABLE;

    /* config pwm channel */
    if (device->channel & 0x01)
    {
        TMR_OC1Config(tmr, &oc_config);
    }

    if (device->channel & 0x02)
    {
        TMR_OC2Config(tmr, &oc_config);
    }

    if (device->channel & 0x04)
    {
        TMR_OC3Config(tmr, &oc_config);
    }

    if (device->channel & 0x08)
    {
        TMR_OC4Config(tmr, &oc_config);
    }

    /* enable update request source */
    TMR_ConfigUPdateRequest(tmr, TMR_UPDATE_SOURCE_REGULAR);
#else
    TMR_BaseConfig_T   base_config;
    TMR_OCConfig_T     oc_config;

    /* configure the tmrer to pwm mode */
    base_config.division = 0;
    base_config.countMode = TMR_COUNTER_MODE_UP;
    base_config.period = 0;
    base_config.clockDivision = TMR_CLOCK_DIV_1;
    TMR_ConfigTimeBase(tmr, &base_config);

    TMR_SelectOutputTrigger(tmr, TMR_TRGO_SOURCE_RESET);
    TMR_DisableMasterSlaveMode(tmr);

    oc_config.mode = TMR_OC_MODE_PWM1;
    oc_config.pulse = 0;
    oc_config.polarity = TMR_OC_POLARITY_HIGH;
    oc_config.nIdleState = TMR_OC_NIDLE_STATE_RESET;
    oc_config.idleState  = TMR_OC_IDLE_STATE_RESET;
    oc_config.outputState = TMR_OC_STATE_ENABLE;

    /* config pwm channel */
    if (device->channel & 0x01)
    {
        TMR_ConfigOC1(tmr, &oc_config);
    }

    if (device->channel & 0x02)
    {
        TMR_ConfigOC2(tmr, &oc_config);
    }

    if (device->channel & 0x04)
    {
        TMR_ConfigOC3(tmr, &oc_config);
    }

    if (device->channel & 0x08)
    {
        TMR_ConfigOC4(tmr, &oc_config);
    }

    /* enable update request source */
    TMR_ConfigUpdateRequest(tmr, TMR_UPDATE_SOURCE_REGULAR);
#endif

    return result;
}

static rt_uint32_t timer_clock_get(TMR_T *tmr)
{
#if defined(SOC_SERIES_APM32F0)
    uint32_t pclk1;
    
    pclk1 = RCM_ReadPCLKFreq();
    
    return (rt_uint32_t)(pclk1 * ((RCM->CFG1_B.APB1PSC != 0) ? 2 : 1));
#else
    uint32_t pclk1, pclk2;

    RCM_ReadPCLKFreq(&pclk1, &pclk2);

    if (tmr == TMR1 || tmr == TMR8 || tmr == TMR9 || tmr == TMR10 || tmr == TMR11)
    {
        return (rt_uint32_t)(pclk2 * ((RCM->CFG_B.APB2PSC != 0) ? 2 : 1));
    }
    else
    {
        return (rt_uint32_t)(pclk1 * ((RCM->CFG_B.APB1PSC != 0) ? 2 : 1));
    }
#endif
}

static rt_err_t drv_pwm_enable(TMR_T *tmr, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint32_t channel = (configuration->channel - 1) << 2;

    if (enable)
    {
        if (configuration->complementary)
        {
            TMR_EnableCCxNChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
        else
        {
            TMR_EnableCCxChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
#if defined(SOC_SERIES_APM32F0)
        if (tmr == TMR1 || tmr == TMR15 || tmr == TMR16 || tmr == TMR17)
#else
        if (tmr == TMR1 || tmr == TMR8)
#endif
        {
            TMR_EnablePWMOutputs(tmr);
        }
        TMR_Enable(tmr);
    }
    else
    {
        if (configuration->complementary)
        {
            TMR_DisableCCxNChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
        else
        {
            TMR_DisableCCxChannel(tmr, (TMR_CHANNEL_T)(0x01 << (channel & 0x1FU)));
        }
#if defined(SOC_SERIES_APM32F0)
        if (tmr == TMR1 || tmr == TMR15 || tmr == TMR16 || tmr == TMR17)
#else
        if (tmr == TMR1 || tmr == TMR8)
#endif
        {
            TMR_DisablePWMOutputs(tmr);
        }
        TMR_Disable(tmr);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(TMR_T *tmr, struct rt_pwm_configuration *configuration)
{
    /* Converts the channel number to the channel number of library */
    rt_uint32_t channel = (configuration->channel - 1) << 2;
    rt_uint64_t timer_clock;
    rt_uint32_t timer_reload, timer_psc;

    timer_clock = timer_clock_get(tmr);
    
#if defined(SOC_SERIES_APM32F0)
    if (tmr->CTRL1_B.CLKDIV == TMR_CKD_DIV2)
#else
    if (tmr->CTRL1_B.CLKDIV == TMR_CLOCK_DIV_2)
#endif
    {
        timer_clock = timer_clock / 2;
    }
#if defined(SOC_SERIES_APM32F0)
    if (tmr->CTRL1_B.CLKDIV == TMR_CKD_DIV4)
#else
    else if (tmr->CTRL1_B.CLKDIV == TMR_CLOCK_DIV_4)
#endif
    {
        timer_clock = timer_clock / 4;
    }
    
    uint32_t temp;
    temp = (uint32_t)tmr;
    temp += (uint32_t)(0x34 + channel);
    /* Convert nanosecond to frequency and duty cycle.*/
    timer_clock /= 1000000UL;

    timer_reload = tmr->AUTORLD;
    timer_psc = tmr->PSC;
    configuration->period = (timer_reload + 1) * (timer_psc + 1) * 1000UL / timer_clock;
    configuration->pulse = ((*(__IO uint32_t *)temp) + 1) * (timer_psc + 1) * 1000UL / timer_clock;
    
    return RT_EOK;
}

static rt_err_t drv_pwm_set(TMR_T *tmr, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t timer_clock, psc;
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);
    uint32_t temp = (uint32_t)tmr;
    
    timer_clock = timer_clock_get(tmr);

    /* Convert nanosecond to frequency and duty cycle. */
    timer_clock /= 1000000UL;
    period = (unsigned long long)configuration->period * timer_clock / 1000ULL ;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    tmr->PSC = (uint16_t)(psc - 1);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    tmr->AUTORLD = (uint16_t)(period - 1);

    pulse = (unsigned long long)configuration->pulse * timer_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }

    temp += (uint32_t)(0x34 + channel);
    *(__IO uint32_t *)temp = pulse - 1;

    tmr->CNT = 0;

    /* Update frequency value */
    TMR_GenerateEvent(tmr, TMR_EVENT_UPDATE);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TMR_T *tmr = (TMR_T *)device->parent.user_data;

    switch (cmd)
    {
    case PWMN_CMD_ENABLE:
        configuration->complementary = RT_TRUE;
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(tmr, configuration, RT_TRUE);
    case PWMN_CMD_DISABLE:
        configuration->complementary = RT_FALSE;
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(tmr, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(tmr, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(tmr, configuration);
    default:
        return -RT_EINVAL;
    }
}

static const struct rt_pwm_ops drv_pwm_ops =
{
    drv_pwm_control
};

static int rt_hw_pwm_init(void)
{
    rt_uint32_t i = 0;
    rt_err_t result = RT_EOK;

    pwm_channel_init();

    for (i = 0; i < sizeof(pwm_config) / sizeof(pwm_config[0]); i++)
    {
        /* pwm init */
        if (apm32_pwm_hw_init(&pwm_config[i]) != RT_EOK)
        {
            LOG_E("%s init failed", pwm_config[i].name);
            return -RT_ERROR;
        }
        else
        {
            LOG_D("%s init success", pwm_config[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&pwm_config[i].pwm_device, pwm_config[i].name, &drv_pwm_ops, pwm_config[i].tmr) == RT_EOK)
            {
                LOG_D("%s register success", pwm_config[i].name);
            }
            else
            {
                LOG_E("%s register failed", pwm_config[i].name);
                result = -RT_ERROR;
            }
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* RT_USING_PWM */
