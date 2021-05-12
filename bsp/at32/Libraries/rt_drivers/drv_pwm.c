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
#if !defined(BSP_USING_TMR1_CH1) && !defined(BSP_USING_TMR1_CH2) && \
    !defined(BSP_USING_TMR1_CH3) && !defined(BSP_USING_TMR1_CH4) && \
    !defined(BSP_USING_TMR2_CH1) && !defined(BSP_USING_TMR2_CH2) && \
    !defined(BSP_USING_TMR2_CH3) && !defined(BSP_USING_TMR2_CH4) && \
    !defined(BSP_USING_TMR3_CH1) && !defined(BSP_USING_TMR3_CH2) && \
    !defined(BSP_USING_TMR3_CH3) && !defined(BSP_USING_TMR3_CH4)
#error "Please define at least one BSP_USING_TMRx_CHx"
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
  #ifdef BSP_USING_TMR1_CH1
    PWM1_CONFIG,
  #endif

  #ifdef BSP_USING_TMR1_CH2
    PWM2_CONFIG,
  #endif

  #ifdef BSP_USING_TMR1_CH3
    PWM3_CONFIG,
  #endif

  #ifdef BSP_USING_TMR1_CH4
    PWM4_CONFIG,
  #endif

  #ifdef BSP_USING_TMR2_CH1
    PWM5_CONFIG,
  #endif

  #ifdef BSP_USING_TMR2_CH2
    PWM6_CONFIG,
  #endif

  #ifdef BSP_USING_TMR2_CH3
    PWM7_CONFIG,
  #endif

  #ifdef BSP_USING_TMR2_CH4
    PWM8_CONFIG,
  #endif

  #ifdef BSP_USING_TMR3_CH1
    PWM9_CONFIG,
  #endif

  #ifdef BSP_USING_TMR3_CH2
    PWM10_CONFIG,
  #endif

  #ifdef BSP_USING_TMR3_CH3
    PWM11_CONFIG,
  #endif

  #ifdef BSP_USING_TMR3_CH4
    PWM12_CONFIG,
  #endif
};

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(TMR_Type* TMRx, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* Get the value of channel */
    rt_uint32_t channel = configuration->channel;

    if (!enable)
    {
        if(channel == 1)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_1, TMR_CCx_Disable);
        }
        else if(channel == 2)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_2, TMR_CCx_Disable);
        }
        else if(channel == 3)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_3, TMR_CCx_Disable);
        }
        else if(channel == 4)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_4, TMR_CCx_Disable);
        }
    }
    else
    {
        if(channel == 1)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_1, TMR_CCx_Enable);
        }
        else if(channel == 2)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_1, TMR_CCx_Enable);
        }
        else if(channel == 3)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_1, TMR_CCx_Enable);
        }
        else if(channel == 4)
        {
          TMR_CCxCmd(TMRx, TMR_Channel_1, TMR_CCx_Enable);
        }
    }

    /* TMRx enable counter */
    TMR_Cmd(TMRx, ENABLE);

    return RT_EOK;
}

static rt_err_t drv_pwm_get(TMR_Type* TMRx, struct rt_pwm_configuration *configuration)
{
    RCC_ClockType  RCC_Clockstruct;
    rt_uint32_t ar, div, cc1, cc2, cc3, cc4;
    rt_uint32_t channel = configuration->channel;
    rt_uint64_t tim_clock;

    ar   = TMRx->AR;
    div  = TMRx->DIV;
    cc1  = TMRx->CC1;
    cc2  = TMRx->CC2;
    cc3  = TMRx->CC3;
    cc4  = TMRx->CC4;

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

static rt_err_t drv_pwm_set(TMR_Type* TMRx, struct rt_pwm_configuration *configuration)
{
    TMR_TimerBaseInitType TMR_TMReBaseStructure;
    TMR_OCInitType  TMR_OCInitStructure;
    rt_uint32_t period, pulse;
    rt_uint64_t psc;
    /* Get the channel number */
    rt_uint32_t channel = configuration->channel;

    /* Init timer pin and enable clock */
    at32_msp_tmr_init(TMRx);

    /* Convert nanosecond to frequency and duty cycle. */
    period = (unsigned long long)configuration->period ;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;

    /* TMRe base configuration */
    TMR_TimeBaseStructInit(&TMR_TMReBaseStructure);
    TMR_TMReBaseStructure.TMR_Period = period;
    TMR_TMReBaseStructure.TMR_DIV = psc - 1;
    TMR_TMReBaseStructure.TMR_ClockDivision = 0;
    TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;

    TMR_TimeBaseInit(TMRx, &TMR_TMReBaseStructure);

    pulse = (unsigned long long)configuration->pulse;

    /* PWM1 Mode configuration: Channel1 */
    TMR_OCStructInit(&TMR_OCInitStructure);
    TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM1;
    TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
    TMR_OCInitStructure.TMR_Pulse = pulse;
    TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_High;

    if(channel == 1)
    {
      TMR_OC1Init(TMRx, &TMR_OCInitStructure);
      TMR_OC1PreloadConfig(TMRx, TMR_OCPreload_Enable);
    }
    else if(channel == 2)
    {
      TMR_OC2Init(TMRx, &TMR_OCInitStructure);
      TMR_OC2PreloadConfig(TMRx, TMR_OCPreload_Enable);
    }
    else if(channel == 3)
    {
      TMR_OC3Init(TMRx, &TMR_OCInitStructure);
      TMR_OC3PreloadConfig(TMRx, TMR_OCPreload_Enable);
    }
    else if(channel == 4)
    {
      TMR_OC4Init(TMRx, &TMR_OCInitStructure);
      TMR_OC4PreloadConfig(TMRx, TMR_OCPreload_Enable);
    }

    TMR_ARPreloadConfig(TMRx, ENABLE);

#if defined (SOC_SERIES_AT32F415)
    if(TMRx == TMR1)
#else
    if(TMRx == TMR1 || TMRx == TMR8)
#endif
    {
      TMR_CtrlPWMOutputs(TMRx,ENABLE);
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TMR_Type *TMRx = (TMR_Type *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(TMRx, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(TMRx, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(TMRx, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(TMRx, configuration);
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
