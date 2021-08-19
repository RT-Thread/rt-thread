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
#if !defined(BSP_USING_TIM1_CH1) && !defined(BSP_USING_TIM1_CH2) && \
    !defined(BSP_USING_TIM1_CH3) && !defined(BSP_USING_TIM1_CH4) && \
    !defined(BSP_USING_TIM2_CH1) && !defined(BSP_USING_TIM2_CH2) && \
    !defined(BSP_USING_TIM2_CH3) && !defined(BSP_USING_TIM2_CH4) && \
    !defined(BSP_USING_TIM3_CH1) && !defined(BSP_USING_TIM3_CH2) && \
    !defined(BSP_USING_TIM3_CH3) && !defined(BSP_USING_TIM3_CH4)
#error "Please define at least one BSP_USING_TIMx_CHx"
#endif
#endif /* RT_USING_PWM */

#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#define MAX_PERIOD 65535
struct rt_device_pwm pwm_device;

struct at32_pwm
{
    struct rt_device_pwm pwm_device;
    TMR_Type* tim_handle;
    rt_uint8_t channel;
    char *name;
};

static struct at32_pwm at32_pwm_obj[] =
{
  #ifdef BSP_USING_TIM1_CH1
    PWM1_CONFIG,
  #endif

  #ifdef BSP_USING_TIM1_CH2
    PWM2_CONFIG,
  #endif

  #ifdef BSP_USING_TIM1_CH3
    PWM3_CONFIG,
  #endif

  #ifdef BSP_USING_TIM1_CH4
    PWM4_CONFIG,
  #endif

  #ifdef BSP_USING_TIM2_CH1
    PWM5_CONFIG,
  #endif

  #ifdef BSP_USING_TIM2_CH2
    PWM6_CONFIG,
  #endif

  #ifdef BSP_USING_TIM2_CH3
    PWM7_CONFIG,
  #endif

  #ifdef BSP_USING_TIM2_CH4
    PWM8_CONFIG,
  #endif

  #ifdef BSP_USING_TIM3_CH1
    PWM9_CONFIG,
  #endif

  #ifdef BSP_USING_TIM3_CH2
    PWM10_CONFIG,
  #endif

  #ifdef BSP_USING_TIM3_CH3
    PWM11_CONFIG,
  #endif

  #ifdef BSP_USING_TIM3_CH4
    PWM12_CONFIG,
  #endif
};

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(TMR_Type* TIMx, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* Get the value of channel */
    rt_uint32_t channel = configuration->channel;

    if (!enable)
    {
        if(channel == 1)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_1, TIM_CCx_Disable);
        }
        else if(channel == 2)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_2, TIM_CCx_Disable);
        }
        else if(channel == 3)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_3, TIM_CCx_Disable);
        }
        else if(channel == 4)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_4, TIM_CCx_Disable);
        }
    }
    else
    {
        if(channel == 1)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_1, TIM_CCx_Enable);
        }
        else if(channel == 2)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_1, TIM_CCx_Enable);
        }
        else if(channel == 3)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_1, TIM_CCx_Enable);
        }
        else if(channel == 4)
        {
          TIM_CCxCmd(TIMx, TIM_Channel_1, TIM_CCx_Enable);
        }
    }

    /* TIMx enable counter */
    TIM_Cmd(TIMx, ENABLE);

    return RT_EOK;
}

static rt_err_t drv_pwm_get(TMR_Type* TIMx, struct rt_pwm_configuration *configuration)
{
    RCC_ClockType  RCC_Clockstruct;
    rt_uint32_t ar, div, cc1, cc2, cc3, cc4;
    rt_uint32_t channel = configuration->channel;
    rt_uint64_t tim_clock;

    ar   = TIMx->AR;
    div  = TIMx->DIV;
    cc1  = TIMx->CC1;
    cc2  = TIMx->CC2;
    cc3  = TIMx->CC3;
    cc4  = TIMx->CC4;

    RCC_GetClocksFreq(&RCC_Clockstruct);

    tim_clock = RCC_Clockstruct.APB2CLK_Freq;

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

static rt_err_t drv_pwm_set(TMR_Type* TIMx, struct rt_pwm_configuration *configuration)
{
    TIM_TimerBaseInitType TIM_TIMeBaseStructure;
    TIM_OCInitType  TIM_OCInitStructure;
    rt_uint32_t period, pulse;
    rt_uint64_t psc;
    /* Get the channel number */
    rt_uint32_t channel = configuration->channel;

    /* Init timer pin and enable clock */
    at32_msp_tmr_init(TIMx);

    /* Convert nanosecond to frequency and duty cycle. */
    period = (unsigned long long)configuration->period ;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;

    /* TIMe base configuration */
    TIM_TimeBaseStructInit(&TIM_TIMeBaseStructure);
    TIM_TIMeBaseStructure.TIM_Period = period;
    TIM_TIMeBaseStructure.TIM_DIV = psc - 1;
    TIM_TIMeBaseStructure.TIM_ClockDivision = 0;
    TIM_TIMeBaseStructure.TIM_CounterMode = TIM_CounterDIR_Up;

    TIM_TimeBaseInit(TIMx, &TIM_TIMeBaseStructure);

    pulse = (unsigned long long)configuration->pulse;

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = pulse;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    if(channel == 1)
    {
      TIM_OC1Init(TIMx, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    else if(channel == 2)
    {
      TIM_OC2Init(TIMx, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    else if(channel == 3)
    {
      TIM_OC3Init(TIMx, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    else if(channel == 4)
    {
      TIM_OC4Init(TIMx, &TIM_OCInitStructure);
      TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }

    TIM_ARPreloadConfig(TIMx, ENABLE);

#if defined (SOC_SERIES_AT32F415)
    if(TIMx == TIM1)
#else
    if(TIMx == TIM1 || TIMx == TIM8)
#endif
    {
      TIM_CtrlPWMOutputs(TIMx,ENABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TIM_Type *TIMx = (TIM_Type *)device->parent.user_data;

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

    for(i = 0; i < sizeof(at32_pwm_obj) / sizeof(at32_pwm_obj[0]); i++)
    {
        if(rt_device_pwm_register(&at32_pwm_obj[i].pwm_device, at32_pwm_obj[i].name, &drv_ops, at32_pwm_obj[i].tim_handle) == RT_EOK)
        {
          LOG_D("%s register success", at32_pwm_obj[i].name);
        }
        else
        {
          LOG_D("%s register failed", at32_pwm_obj[i].name);
          result = -RT_ERROR;
        }
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_pwm_init);
