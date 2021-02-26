/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-02     hqfang       first version
 */

#include "drv_pwm.h"
// #define DBG_LVL               DBG_INFO

#include <rtdbg.h>

#ifdef BSP_USING_PWM

#if !defined(BSP_USING_PWM0) && !defined(BSP_USING_PWM1) && !defined(BSP_USING_PWM2) \
    && !defined(BSP_USING_PWM3) && !defined(BSP_USING_PWM4)
    #error "Please define at least one BSP_USING_PWMx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable PWM */
#endif

static struct gd32_pwm_config pwm_config[] =
{
#ifdef BSP_USING_PWM0
    {
        "pwm0",
        TIMER0,
        1000000,
    },
#endif
#ifdef BSP_USING_PWM1
    {
        "pwm1",
        TIMER1,
        1000000,
    },
#endif
#ifdef BSP_USING_PWM2
    {
        "pwm2",
        TIMER2,
        1000000,
    },
#endif
#ifdef BSP_USING_PWM3
    {
        "pwm3",
        TIMER3,
        1000000,
    },
#endif
#ifdef BSP_USING_PWM4
    {
        "pwm4",
        TIMER4,
        1000000,
    },
#endif
};

#define GD32_MAX_PWM_CHANNELS   TIMER_CH_3
static struct gd32_pwm pwm_obj[sizeof(pwm_config) / sizeof(pwm_config[0])] = {0};

static rt_err_t gd32_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    struct gd32_pwm_config *config;
    config = (struct gd32_pwm_config *)device->parent.user_data;
    RT_ASSERT(config);

    if (configuration->channel > GD32_MAX_PWM_CHANNELS)
    {
        return RT_EINVAL;
    }
    if (!enable)
    {
        timer_channel_output_state_config(config->periph, configuration->channel, TIMER_CCX_DISABLE);
    }
    else
    {
        timer_channel_output_state_config(config->periph, configuration->channel, TIMER_CCX_ENABLE);
    }

    return RT_EOK;
}

static uint32_t gd32_get_pwm_clk(rt_uint32_t periph)
{
    uint32_t clk;
    uint8_t clkpre;
    if (periph != TIMER0)
    {
        clk = rcu_clock_freq_get(CK_APB1);
        clkpre = GET_BITS(RCU_CFG0, 8, 10);
    }
    else
    {
        clk = rcu_clock_freq_get(CK_APB2);
        clkpre = GET_BITS(RCU_CFG0, 11, 13);
    }
    if (clkpre >= 4)
    {
        clk = clk * 2;
    }
    return clk;
}

static rt_err_t gd32_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    uint32_t pwmclk;
    uint16_t prescale, period, clkdiv, pulse;
    struct gd32_pwm_config *config;
    config = (struct gd32_pwm_config *)device->parent.user_data;
    RT_ASSERT(config);

    pwmclk = gd32_get_pwm_clk(config->periph);
    prescale = (uint16_t)TIMER_PSC(config->periph) + 1;
    clkdiv = ((uint16_t)(TIMER_CTL0(config->periph) & TIMER_CTL0_CKDIV) >> 8);
    clkdiv = 1 << clkdiv;
    period = (uint16_t)TIMER_CAR(config->periph) + 1;
    pulse = (uint16_t)REG32((config->periph) + 0x34U + configuration->channel << 2) + 1;

    pwmclk = pwmclk / prescale / clkdiv;
    LOG_I("current pwmclk is %d\n", pwmclk);

    configuration->period = (uint64_t)period * 1000000000 / pwmclk;
    configuration->pulse = (uint64_t)pulse * 1000000000 / pwmclk;
    return RT_EOK;
}

static rt_err_t gd32_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;
    uint32_t pwmclk, pwmclkv2;
    uint64_t period_cmp;
    uint16_t prescale, period, clkdiv, pulse;
    struct gd32_pwm_config *config;
    config = (struct gd32_pwm_config *)device->parent.user_data;
    RT_ASSERT(config);

    if (configuration->channel > GD32_MAX_PWM_CHANNELS)
    {
        LOG_I("max channel supported is %d\n", GD32_MAX_PWM_CHANNELS);
        return RT_EINVAL;
    }
    if (configuration->period < configuration->pulse)
    {
        LOG_I("period should > pulse \n");
        return RT_EINVAL;
    }

    pwmclk = gd32_get_pwm_clk(config->periph);

    // min period value >= 100
    period_cmp = (uint64_t)(1000000000 / pwmclk) * 10;
    if (configuration->period < period_cmp)
    {
        return RT_EINVAL;
    }
    period_cmp = (uint64_t)(1000000000 / (pwmclk / 65536 / 4)) * 65536;
    if (configuration->period > period_cmp)
    {
        return RT_EINVAL;
    }

    period_cmp = (uint64_t) pwmclk * configuration->period / 1000000000;

    if (period_cmp < 65536)
    {
        prescale = 0;
        clkdiv = TIMER_CKDIV_DIV1;
        period = period_cmp;
    }
    else if (period_cmp < 4294967296)
    {
        prescale = period_cmp / 65536;
        period = period_cmp / (prescale + 1);
        clkdiv = TIMER_CKDIV_DIV1;
    }
    else if (period_cmp < 8589934592)
    {
        prescale = period_cmp / 65536;
        period = period_cmp / (prescale + 1) / 2;
        clkdiv = TIMER_CKDIV_DIV2;
    }
    else
    {
        prescale = period_cmp / 65536;
        period = period_cmp / (prescale + 1) / 4;
        clkdiv = TIMER_CKDIV_DIV4;
    }

    pwmclkv2 = pwmclk / (prescale + 1) / (1 << clkdiv);
    LOG_I("current pwmclk is %d\n", pwmclkv2);

    LOG_I("Set channel %d, period %dns, pulse %dns\n", configuration->channel, \
          configuration->period, configuration->pulse);
    pulse = (uint64_t)period * configuration->pulse / configuration->period;
    LOG_I("pwmclk %d, pwmcmp %d, prescale %d, period %d, pulse %d, clkdiv %d\n", \
          pwmclk, (uint32_t)period_cmp, prescale, period, pulse, clkdiv);

    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER configuration */
    timer_initpara.prescaler         = prescale;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = period;
    timer_initpara.clockdivision     = clkdiv;
    timer_initpara.repetitioncounter = 0;
    timer_init(config->periph, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* CH0, CH1 and CH2 configuration in PWM mode */
    timer_ocinitpara.outputstate  = TIMER_CCX_DISABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(config->periph, configuration->channel, &timer_ocinitpara);

    /* Channel configuration in PWM mode */
    timer_channel_output_pulse_value_config(config->periph, configuration->channel, pulse);
    timer_channel_output_mode_config(config->periph, configuration->channel, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(config->periph, configuration->channel, TIMER_OC_SHADOW_DISABLE);

    timer_primary_output_config(config->periph, ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(config->periph);
    timer_enable(config->periph);

    return RT_EOK;
}

static rt_err_t gd32_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return gd32_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return gd32_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return gd32_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return gd32_pwm_get(device, configuration);
    default:
        return RT_EINVAL;
    }
}

static rt_err_t gd32_pwm_init(struct gd32_pwm_config *config)
{
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;
    uint32_t pwmclk;
    uint16_t prescale;

    pwmclk = gd32_get_pwm_clk(config->periph);

    /* period 1ms, duty 50% */
    prescale = pwmclk / 1000 / 1000 - 1;

    config->period = 1000000;

    LOG_I("pwmclk %d, prescale %d, period %d, clkdiv %d\n", pwmclk, prescale, 999, 0);

    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER configuration */
    timer_initpara.prescaler         = prescale;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 999;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(config->periph, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* CH0, CH1 and CH2 configuration in PWM mode */
    timer_ocinitpara.outputstate  = TIMER_CCX_DISABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    /* Channel configuration in PWM mode */
    for (int i = 0; i <= GD32_MAX_PWM_CHANNELS; i ++)
    {
        timer_channel_output_config(config->periph, i, &timer_ocinitpara);
        timer_channel_output_pulse_value_config(config->periph, i, 499);
        timer_channel_output_mode_config(config->periph, i, TIMER_OC_MODE_PWM0);
        timer_channel_output_shadow_config(config->periph, i, TIMER_OC_SHADOW_DISABLE);
    }

    timer_primary_output_config(config->periph, ENABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(config->periph);
    timer_enable(config->periph);

    return RT_EOK;
}

static struct rt_pwm_ops gd32_drv_ops =
{
    .control = gd32_pwm_control
};

static int rt_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

#ifdef BSP_USING_PWM0
    rcu_periph_clock_enable(RCU_TIMER0);
#endif
#ifdef BSP_USING_PWM1
    rcu_periph_clock_enable(RCU_TIMER1);
#endif
#ifdef BSP_USING_PWM2
    rcu_periph_clock_enable(RCU_TIMER2);
#endif
#ifdef BSP_USING_PWM3
    rcu_periph_clock_enable(RCU_TIMER3);
#endif
#ifdef BSP_USING_PWM4
    rcu_periph_clock_enable(RCU_TIMER4);
#endif
    rcu_periph_clock_enable(RCU_AF);

    for (i = 0; i < sizeof(pwm_obj) / sizeof(pwm_obj[0]); i++)
    {
        pwm_obj[i].config = &pwm_config[i];
        rt_device_pwm_register(&pwm_obj[i].pwm_device, pwm_config[i].name, &gd32_drv_ops, pwm_obj[i].config);
        gd32_pwm_init(&pwm_config[i]);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_pwm_init);

#endif /* RT_USING_PWM */
