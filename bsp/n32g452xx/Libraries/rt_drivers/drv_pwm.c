/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     breo.com     first version
 */

#include <board.h>
#include "drv_pwm.h"

#ifdef RT_USING_PWM
    #if !defined(BSP_USING_TIM1_CH1) && !defined(BSP_USING_TIM1_CH2) && \
        !defined(BSP_USING_TIM1_CH3) && !defined(BSP_USING_TIM1_CH4) && \
        !defined(BSP_USING_TIM2_CH1) && !defined(BSP_USING_TIM2_CH2) && \
        !defined(BSP_USING_TIM2_CH3) && !defined(BSP_USING_TIM2_CH4) && \
        !defined(BSP_USING_TIM3_CH1) && !defined(BSP_USING_TIM3_CH2) && \
        !defined(BSP_USING_TIM3_CH3) && !defined(BSP_USING_TIM3_CH4) && \
        !defined(BSP_USING_TIM4_CH1) && !defined(BSP_USING_TIM4_CH2) && \
        !defined(BSP_USING_TIM4_CH3) && !defined(BSP_USING_TIM4_CH4) && \
        !defined(BSP_USING_TIM5_CH1) && !defined(BSP_USING_TIM5_CH2) && \
        !defined(BSP_USING_TIM5_CH3) && !defined(BSP_USING_TIM5_CH4) && \
        !defined(BSP_USING_TIM8_CH1) && !defined(BSP_USING_TIM8_CH2) && \
        !defined(BSP_USING_TIM8_CH3) && !defined(BSP_USING_TIM8_CH4)
        #error "Please define at least one BSP_USING_TIMx_CHx"
    #endif
#endif /* RT_USING_PWM */

#define MAX_PERIOD 65535
#define MIN_PERIOD 3

#ifdef BSP_USING_PWM

struct n32_pwm
{
    TIM_Module *tim_handle;
    const char *name;
    struct rt_device_pwm pwm_device;
    int8_t tim_en;
    uint8_t ch_en;
    uint32_t period;
    uint32_t psc;
};

static struct n32_pwm n32_pwm_obj[] =
{
#if defined(BSP_USING_TIM1_CH1) || defined(BSP_USING_TIM1_CH2) || \
        defined(BSP_USING_TIM1_CH3) || defined(BSP_USING_TIM1_CH4)
    {
        .tim_handle = TIM1,
        .name = "tim1pwm",
    },
#endif

#if defined(BSP_USING_TIM2_CH1) || defined(BSP_USING_TIM2_CH2) || \
        defined(BSP_USING_TIM2_CH3) || defined(BSP_USING_TIM2_CH4)
    {
        .tim_handle = TIM2,
        .name = "tim2pwm",
    },
#endif

#if defined(BSP_USING_TIM3_CH1) || defined(BSP_USING_TIM3_CH2) || \
        defined(BSP_USING_TIM3_CH3) || defined(BSP_USING_TIM3_CH4)
    {
        .tim_handle = TIM3,
        .name = "tim3pwm",
    },
#endif

#if defined(BSP_USING_TIM4_CH1) || defined(BSP_USING_TIM4_CH2) || \
        defined(BSP_USING_TIM4_CH3) || defined(BSP_USING_TIM4_CH4)
    {
        .tim_handle = TIM4,
        .name = "tim4pwm",
    },
#endif

#if defined(BSP_USING_TIM5_CH1) || defined(BSP_USING_TIM5_CH2) || \
        defined(BSP_USING_TIM5_CH3) || defined(BSP_USING_TIM5_CH4)
    {
        .tim_handle = TIM5,
        .name = "tim5pwm",
    },
#endif

#if defined(BSP_USING_TIM8_CH1) || defined(BSP_USING_TIM8_CH2) || \
        defined(BSP_USING_TIM8_CH3) || defined(BSP_USING_TIM8_CH4)
    {
        .tim_handle = TIM8,
        .name = "tim8pwm",
    }
#endif

};

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(struct n32_pwm *pwm_dev, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* Get the value of channel */
    rt_uint32_t channel = configuration->channel;
    TIM_Module *TIMx = pwm_dev->tim_handle;

    if (enable)
    {
        pwm_dev->ch_en |= 0x1 << channel;
    }
    else
    {
        pwm_dev->ch_en &= ~(0x1 << channel);
    }

    if (enable)
    {
        if (channel == 1)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_1, TIM_CAP_CMP_ENABLE);
        }
        else if (channel == 2)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_2, TIM_CAP_CMP_ENABLE);
        }
        else if (channel == 3)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_3, TIM_CAP_CMP_ENABLE);
        }
        else if (channel == 4)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_4, TIM_CAP_CMP_ENABLE);
        }
    }
    else
    {
        if (channel == 1)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_1, TIM_CAP_CMP_DISABLE);
        }
        else if (channel == 2)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_2, TIM_CAP_CMP_DISABLE);
        }
        else if (channel == 3)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_3, TIM_CAP_CMP_DISABLE);
        }
        else if (channel == 4)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_4, TIM_CAP_CMP_DISABLE);
        }
    }

    if (pwm_dev->ch_en)
    {
        pwm_dev->tim_en = 0x1;
        TIM_Enable(TIMx, ENABLE);
    }
    else
    {
        pwm_dev->tim_en = 0x0;
        TIM_Enable(TIMx, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(struct n32_pwm *pwm_dev, struct rt_pwm_configuration *configuration)
{
    RCC_ClocksType  RCC_Clockstruct;
    rt_uint32_t ar, div, cc1, cc2, cc3, cc4;
    rt_uint64_t tim_clock;
    rt_uint32_t channel = configuration->channel;
    TIM_Module *TIMx = pwm_dev->tim_handle;

    ar   = TIMx->AR;
    div  = TIMx->PSC;
    cc1  = TIMx->CCDAT1;
    cc2  = TIMx->CCDAT2;
    cc3  = TIMx->CCDAT3;
    cc4  = TIMx->CCDAT4;

    RCC_GetClocksFreqValue(&RCC_Clockstruct);

    tim_clock = RCC_Clockstruct.Pclk2Freq;

    /* Convert nanosecond to frequency and duty cycle. */
    tim_clock /= 1000000UL;
    configuration->period = (ar + 1) * (div + 1) * 1000UL / tim_clock;
    if (channel == 1)
        configuration->pulse = (cc1 + 1) * (div + 1) * 1000UL / tim_clock;
    if (channel == 2)
        configuration->pulse = (cc2 + 1) * (div + 1) * 1000UL / tim_clock;
    if (channel == 3)
        configuration->pulse = (cc3 + 1) * (div + 1) * 1000UL / tim_clock;
    if (channel == 4)
        configuration->pulse = (cc4 + 1) * (div + 1) * 1000UL / tim_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(struct n32_pwm *pwm_dev, struct rt_pwm_configuration *configuration)
{
    TIM_Module *TIMx = pwm_dev->tim_handle;
    rt_uint32_t channel = configuration->channel;
    rt_uint32_t period;
    rt_uint64_t psc;
    rt_uint32_t pulse;

    RCC_ClocksType RCC_Clock;
    RCC_GetClocksFreqValue(&RCC_Clock);
    rt_uint64_t input_clock;
    if ((TIM1 == TIMx) || (TIM8 == TIMx))
    {
        RCC_ConfigTim18Clk(RCC_TIM18CLK_SRC_SYSCLK);
        input_clock = RCC_Clock.SysclkFreq;
    }
    else
    {
        if (1 == (RCC_Clock.HclkFreq / RCC_Clock.Pclk1Freq))
            input_clock = RCC_Clock.Pclk1Freq;
        else
            input_clock = RCC_Clock.Pclk1Freq * 2;
    }

    input_clock /= 1000000UL;
    /* Convert nanosecond to frequency and duty cycle. */
    period = (unsigned long long)configuration->period * input_clock / 1000ULL;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    if ((pwm_dev->period != period) || (pwm_dev->psc != psc))
    {
        /* Tim base configuration */
        TIM_TimeBaseInitType TIM_TIMeBaseStructure;
        TIM_InitTimBaseStruct(&TIM_TIMeBaseStructure);
        TIM_TIMeBaseStructure.Period = period - 1;
        TIM_TIMeBaseStructure.Prescaler = psc - 1;
        TIM_TIMeBaseStructure.ClkDiv = 0;
        TIM_TIMeBaseStructure.CntMode = TIM_CNT_MODE_UP;
        TIM_InitTimeBase(TIMx, &TIM_TIMeBaseStructure);
    }

    pulse = (unsigned long long)configuration->pulse * input_clock / psc / 1000ULL;
    if (pulse > period)
    {
        pulse = period;
    }

    /* PWM1 Mode configuration: Channel1 */
    OCInitType  TIM_OCInitStructure;
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OcMode = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse = pulse;
    TIM_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH;

    if (channel == 1)
    {
        TIM_InitOc1(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc1Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
        if (!(pwm_dev->ch_en & (0x1 << channel)))
            TIM_EnableCapCmpCh(TIMx, TIM_CH_1, TIM_CAP_CMP_DISABLE);
    }
    else if (channel == 2)
    {
        TIM_InitOc2(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc2Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
        if (!(pwm_dev->ch_en & (0x1 << channel)))
            TIM_EnableCapCmpCh(TIMx, TIM_CH_2, TIM_CAP_CMP_DISABLE);
    }
    else if (channel == 3)
    {
        TIM_InitOc3(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc3Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
        if (!(pwm_dev->ch_en & (0x1 << channel)))
            TIM_EnableCapCmpCh(TIMx, TIM_CH_3, TIM_CAP_CMP_DISABLE);
    }
    else if (channel == 4)
    {
        TIM_InitOc4(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc4Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
        if (!(pwm_dev->ch_en & (0x1 << channel)))
            TIM_EnableCapCmpCh(TIMx, TIM_CH_4, TIM_CAP_CMP_DISABLE);
    }

    TIM_ConfigArPreload(TIMx, ENABLE);
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct n32_pwm *pwm_dev = (struct n32_pwm *)(device->parent.user_data);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm_dev, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm_dev, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(pwm_dev, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm_dev, configuration);
    default:
        return -RT_EINVAL;
    }
}

static int rt_hw_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(n32_pwm_obj) / sizeof(n32_pwm_obj[0]); i++)
    {
        if (rt_device_pwm_register(&n32_pwm_obj[i].pwm_device,
                                   n32_pwm_obj[i].name, &drv_ops, &(n32_pwm_obj[i])) == RT_EOK)
        {
            /* Init timer pin and enable clock */
            void n32_msp_tim_init(void *Instance);
            n32_msp_tim_init(n32_pwm_obj[i].tim_handle);
        }
        else
        {
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_pwm_init);

#endif

