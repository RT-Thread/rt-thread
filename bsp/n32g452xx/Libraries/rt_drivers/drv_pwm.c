/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-1-13      Leo         first version
 */

#include <board.h>
#include "drv_pwm.h"

#ifdef RT_USING_PWM
#if !defined(BSP_USING_TIM3_CH1) && !defined(BSP_USING_TIM3_CH2) && \
    !defined(BSP_USING_TIM3_CH3) && !defined(BSP_USING_TIM3_CH4)
#error "Please define at least one BSP_USING_TIMx_CHx"
#endif
#endif /* RT_USING_PWM */

#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#define MAX_PERIOD 65535
struct rt_device_pwm pwm_device;

struct n32_pwm
{
    struct rt_device_pwm pwm_device;
    TIM_Module* tim_handle;
    rt_uint8_t channel;
    char *name;
};

static struct n32_pwm n32_pwm_obj[] =
{
#ifdef BSP_USING_TIM3_CH1
    PWM1_TIM3_CONFIG,
#endif

#ifdef BSP_USING_TIM3_CH2
    PWM2_TIM3_CONFIG,
#endif

#ifdef BSP_USING_TIM3_CH3
    PWM3_TIM3_CONFIG,
#endif

#ifdef BSP_USING_TIM3_CH4
    PWM4_TIM3_CONFIG,
#endif
};

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(TIM_Module* TIMx, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* Get the value of channel */
    rt_uint32_t channel = configuration->channel;

    if (!enable)
    {
        if(channel == 1)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_1, TIM_CAP_CMP_DISABLE);
        }
        else if(channel == 2)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_2, TIM_CAP_CMP_DISABLE);
        }
        else if(channel == 3)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_3, TIM_CAP_CMP_DISABLE);
        }
        else if(channel == 4)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_4, TIM_CAP_CMP_DISABLE);
        }
    }
    else
    {
        if(channel == 1)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_1, TIM_CAP_CMP_ENABLE);
        }
        else if(channel == 2)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_2, TIM_CAP_CMP_ENABLE);
        }
        else if(channel == 3)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_3, TIM_CAP_CMP_ENABLE);
        }
        else if(channel == 4)
        {
            TIM_EnableCapCmpCh(TIMx, TIM_CH_4, TIM_CAP_CMP_ENABLE);
        }
    }

    TIM_Enable(TIMx, ENABLE);

    return RT_EOK;
}

static rt_err_t drv_pwm_get(TIM_Module* TIMx, struct rt_pwm_configuration *configuration)
{
    RCC_ClocksType  RCC_Clockstruct;
    rt_uint32_t ar, div, cc1, cc2, cc3, cc4;
    rt_uint32_t channel = configuration->channel;
    rt_uint64_t tim_clock;

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
    if(channel == 1)
        configuration->pulse = (cc1 + 1) * (div + 1) * 1000UL / tim_clock;
    if(channel == 2)
        configuration->pulse = (cc2 + 1) * (div+ 1) * 1000UL / tim_clock;
    if(channel == 3)
        configuration->pulse = (cc3 + 1) * (div + 1) * 1000UL / tim_clock;
    if(channel == 4)
        configuration->pulse = (cc4 + 1) * (div + 1) * 1000UL / tim_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(TIM_Module* TIMx, struct rt_pwm_configuration *configuration)
{
    /* Init timer pin and enable clock */
    n32_msp_tim_init(TIMx);

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
        if (1 == (RCC_Clock.HclkFreq/RCC_Clock.Pclk1Freq))
            input_clock = RCC_Clock.Pclk1Freq;
        else
            input_clock = RCC_Clock.Pclk1Freq * 2;
    }

    /* Convert nanosecond to frequency and duty cycle. */
    rt_uint32_t period = (unsigned long long)configuration->period ;
    rt_uint64_t psc = period / MAX_PERIOD + 1;
    period = period / psc;
    psc = psc * (input_clock / 1000000);

    /* TIMe base configuration */
    TIM_TimeBaseInitType TIM_TIMeBaseStructure;
    TIM_InitTimBaseStruct(&TIM_TIMeBaseStructure);
    TIM_TIMeBaseStructure.Period = period;
    TIM_TIMeBaseStructure.Prescaler = psc - 1;
    TIM_TIMeBaseStructure.ClkDiv = 0;
    TIM_TIMeBaseStructure.CntMode = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIMx, &TIM_TIMeBaseStructure);

    rt_uint32_t pulse = (unsigned long long)configuration->pulse;
    /* PWM1 Mode configuration: Channel1 */
    OCInitType  TIM_OCInitStructure;
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OcMode = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse = pulse;
    TIM_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH;

    rt_uint32_t channel = configuration->channel;
    if(channel == 1)
    {
        TIM_InitOc1(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc1Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
    }
    else if(channel == 2)
    {
        TIM_InitOc2(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc2Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
    }
    else if(channel == 3)
    {
        TIM_InitOc3(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc3Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
    }
    else if(channel == 4)
    {
        TIM_InitOc4(TIMx, &TIM_OCInitStructure);
        TIM_ConfigOc4Preload(TIMx, TIM_OC_PRE_LOAD_ENABLE);
    }

    TIM_ConfigArPreload(TIMx, ENABLE);
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TIM_Module *TIMx = (TIM_Module *)device->parent.user_data;

    switch (cmd)
    {
        case PWM_CMD_ENABLE:
            return drv_pwm_enable(TIMx, configuration, RT_TRUE);
        case PWM_CMD_DISABLE:
            return drv_pwm_enable(TIMx, configuration, RT_FALSE);
        case PWM_CMD_SET:
            return drv_pwm_set(TIMx, configuration);
        case PWM_CMD_GET:
            return drv_pwm_get(TIMx, configuration);
        default:
            return RT_EINVAL;
    }
}

static int rt_hw_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for(i = 0; i < sizeof(n32_pwm_obj) / sizeof(n32_pwm_obj[0]); i++)
    {
        if(rt_device_pwm_register(&n32_pwm_obj[i].pwm_device, n32_pwm_obj[i].name, &drv_ops, n32_pwm_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", n32_pwm_obj[i].name);
        }
        else
        {
            LOG_D("%s register failed", n32_pwm_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_pwm_init);
