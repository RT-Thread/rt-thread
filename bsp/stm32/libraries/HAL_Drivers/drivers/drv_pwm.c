/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-13     zylx         first version
 * 2021-01-23     thread-liu   Fix the timer clock frequency doubling problem
 */

#include <board.h>
#include <rtthread.h>

#ifdef BSP_USING_PWM
#include "drv_config.h"
#include "drv_tim.h"
#include <drivers/dev_pwm.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE 2

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
#ifdef BSP_USING_PWM6
    PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
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

struct stm32_pwm
{
    struct rt_device_pwm pwm_device;
    TIM_HandleTypeDef    tim_handle;
    rt_uint8_t channel;
    char *name;
};

static struct stm32_pwm stm32_pwm_obj[] =
{
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif

#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif

#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif

#ifdef BSP_USING_PWM4
    PWM4_CONFIG,
#endif

#ifdef BSP_USING_PWM5
    PWM5_CONFIG,
#endif

#ifdef BSP_USING_PWM6
    PWM6_CONFIG,
#endif

#ifdef BSP_USING_PWM7
    PWM7_CONFIG,
#endif

#ifdef BSP_USING_PWM8
    PWM8_CONFIG,
#endif

#ifdef BSP_USING_PWM9
    PWM9_CONFIG,
#endif

#ifdef BSP_USING_PWM10
    PWM10_CONFIG,
#endif

#ifdef BSP_USING_PWM11
    PWM11_CONFIG,
#endif

#ifdef BSP_USING_PWM12
    PWM12_CONFIG,
#endif

#ifdef BSP_USING_PWM13
    PWM13_CONFIG,
#endif

#ifdef BSP_USING_PWM14
    PWM14_CONFIG,
#endif

#ifdef BSP_USING_PWM15
    PWM15_CONFIG,
#endif

#ifdef BSP_USING_PWM16
    PWM16_CONFIG,
#endif

#ifdef BSP_USING_PWM17
    PWM17_CONFIG,
#endif
};

static rt_uint64_t tim_clock_get(TIM_HandleTypeDef *htim)
{
    rt_uint32_t pclk1_doubler, pclk2_doubler;
    rt_uint64_t tim_clock;

    stm32_tim_pclkx_doubler_get(&pclk1_doubler, &pclk2_doubler);

/* Some series may only have APBPERIPH_BASE, don't have HAL_RCC_GetPCLK2Freq */
#if defined(APBPERIPH_BASE)
    tim_clock = (rt_uint32_t)(HAL_RCC_GetPCLK1Freq() * pclk1_doubler);
#elif defined(APB1PERIPH_BASE) || defined(APB2PERIPH_BASE)
    if ((rt_uint32_t)htim->Instance >= APB2PERIPH_BASE)
    {
        tim_clock = (rt_uint32_t)(HAL_RCC_GetPCLK2Freq() * pclk2_doubler);
    }
    else
    {
        tim_clock = (rt_uint32_t)(HAL_RCC_GetPCLK1Freq() * pclk1_doubler);
    }
#endif

    return tim_clock;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* Converts the channel number to the channel number of Hal library */
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);

    if (!configuration->complementary)
    {
        if (!enable)
        {
            HAL_TIM_PWM_Stop(htim, channel);
        }
        else
        {
            HAL_TIM_PWM_Start(htim, channel);
        }
    }
    else if (configuration->complementary)
    {
        if (!enable)
        {
            HAL_TIMEx_PWMN_Stop(htim, channel);
        }
        else
        {
            HAL_TIMEx_PWMN_Start(htim, channel);
        }
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_get(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    /* Converts the channel number to the channel number of Hal library */
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);
    rt_uint64_t tim_clock;

    tim_clock = tim_clock_get(htim);
    if (__HAL_TIM_GET_CLOCKDIVISION(htim) == TIM_CLOCKDIVISION_DIV2)
    {
        tim_clock = tim_clock / 2;
    }
    else if (__HAL_TIM_GET_CLOCKDIVISION(htim) == TIM_CLOCKDIVISION_DIV4)
    {
        tim_clock = tim_clock / 4;
    }

    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    configuration->period = (__HAL_TIM_GET_AUTORELOAD(htim) + 1) * (htim->Instance->PSC + 1) * 1000UL / tim_clock;
    configuration->pulse = (__HAL_TIM_GET_COMPARE(htim, channel) + 1) * (htim->Instance->PSC + 1) * 1000UL / tim_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock, psc;
    /* Converts the channel number to the channel number of Hal library */
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);

    tim_clock = tim_clock_get(htim);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    period = (rt_uint64_t)configuration->period * tim_clock / 1000ULL ;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    __HAL_TIM_SET_PRESCALER(htim, psc - 1);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    __HAL_TIM_SET_AUTORELOAD(htim, period - 1);

    pulse = (rt_uint64_t)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    /*To determine user input, output high level is required*/
    else if (pulse >= period)
    {
        pulse = period + 1;
    }
    __HAL_TIM_SET_COMPARE(htim, channel, pulse - 1);

    /* If you want the PWM setting to take effect immediately,
    please uncommon the following code, but it will cause the last PWM cycle not complete. */
    //__HAL_TIM_SET_COUNTER(htim, 0);

    //HAL_TIM_GenerateEvent(htim, TIM_EVENTSOURCE_UPDATE); /* Update frequency value */

    return RT_EOK;
}

static rt_err_t drv_pwm_set_period(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period;
    rt_uint64_t tim_clock, psc;

    tim_clock = tim_clock_get(htim);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    period = (rt_uint64_t)configuration->period * tim_clock / 1000ULL ;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    __HAL_TIM_SET_PRESCALER(htim, psc - 1);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    __HAL_TIM_SET_AUTORELOAD(htim, period - 1);

    return RT_EOK;
}

static rt_err_t drv_pwm_set_pulse(TIM_HandleTypeDef *htim, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock;
    /* Converts the channel number to the channel number of Hal library */
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);

    tim_clock = tim_clock_get(htim);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;

    period = (__HAL_TIM_GET_AUTORELOAD(htim) + 1) * (htim->Instance->PSC + 1) * 1000UL / tim_clock;
    pulse = (rt_uint64_t)configuration->pulse * (__HAL_TIM_GET_AUTORELOAD(htim) + 1) / period;

    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }
    __HAL_TIM_SET_COMPARE(htim, channel, pulse - 1);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(htim, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(htim, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(htim, configuration);
    case PWM_CMD_SET_PERIOD:
        return drv_pwm_set_period(htim, configuration);
    case PWM_CMD_SET_PULSE:
        return drv_pwm_set_pulse(htim, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(htim, configuration);
    default:
        return -RT_EINVAL;
    }
}

static rt_err_t stm32_hw_pwm_init(struct stm32_pwm *device)
{
    rt_err_t result = RT_EOK;
    TIM_HandleTypeDef *tim = RT_NULL;
    TIM_OC_InitTypeDef oc_config = {0};
    TIM_MasterConfigTypeDef master_config = {0};
    TIM_ClockConfigTypeDef clock_config = {0};

    RT_ASSERT(device != RT_NULL);

    tim = (TIM_HandleTypeDef *)&device->tim_handle;

    /* configure the timer to pwm mode */
    tim->Init.Prescaler = 0;
    tim->Init.CounterMode = TIM_COUNTERMODE_UP;
    tim->Init.Period = 0;
    tim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4)
    tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#endif
    if (HAL_TIM_Base_Init(tim) != HAL_OK)
    {
        LOG_E("%s pwm init failed", device->name);
        result = -RT_ERROR;
        goto __exit;
    }

    stm32_tim_enable_clock(tim);

    clock_config.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(tim, &clock_config) != HAL_OK)
    {
        LOG_E("%s clock init failed", device->name);
        result = -RT_ERROR;
        goto __exit;
    }

    if (HAL_TIM_PWM_Init(tim) != HAL_OK)
    {
        LOG_E("%s pwm init failed", device->name);
        result = -RT_ERROR;
        goto __exit;
    }

    if(IS_TIM_MASTER_INSTANCE(tim->Instance))
    {
        master_config.MasterOutputTrigger = TIM_TRGO_RESET;
        master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        if (HAL_TIMEx_MasterConfigSynchronization(tim, &master_config) != HAL_OK)
        {
            LOG_E("%s master config failed", device->name);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    oc_config.OCMode = TIM_OCMODE_PWM1;
    oc_config.Pulse = 0;
    oc_config.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc_config.OCFastMode = TIM_OCFAST_DISABLE;
    oc_config.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    oc_config.OCIdleState  = TIM_OCIDLESTATE_RESET;

    /* config pwm channel */
    if (device->channel & 0x01)
    {
        if (HAL_TIM_PWM_ConfigChannel(tim, &oc_config, TIM_CHANNEL_1) != HAL_OK)
        {
            LOG_E("%s channel1 config failed", device->name);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    if (device->channel & 0x02)
    {
        if (HAL_TIM_PWM_ConfigChannel(tim, &oc_config, TIM_CHANNEL_2) != HAL_OK)
        {
            LOG_E("%s channel2 config failed", device->name);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    if (device->channel & 0x04)
    {
        if (HAL_TIM_PWM_ConfigChannel(tim, &oc_config, TIM_CHANNEL_3) != HAL_OK)
        {
            LOG_E("%s channel3 config failed", device->name);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    if (device->channel & 0x08)
    {
        if (HAL_TIM_PWM_ConfigChannel(tim, &oc_config, TIM_CHANNEL_4) != HAL_OK)
        {
            LOG_E("%s channel4 config failed", device->name);
            result = -RT_ERROR;
            goto __exit;
        }
    }

    /* pwm pin configuration */
    void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
    HAL_TIM_MspPostInit(tim);

    /* enable update request source */
    __HAL_TIM_URS_ENABLE(tim);

__exit:
    return result;
}

static void stm32_pwm_get_channel(void)
{
#ifdef BSP_USING_PWM1_CH1
    stm32_pwm_obj[PWM1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM1_CH2
    stm32_pwm_obj[PWM1_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM1_CH3
    stm32_pwm_obj[PWM1_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM1_CH4
    stm32_pwm_obj[PWM1_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM2_CH1
    stm32_pwm_obj[PWM2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM2_CH2
    stm32_pwm_obj[PWM2_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM2_CH3
    stm32_pwm_obj[PWM2_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM2_CH4
    stm32_pwm_obj[PWM2_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM3_CH1
    stm32_pwm_obj[PWM3_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM3_CH2
    stm32_pwm_obj[PWM3_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM3_CH3
    stm32_pwm_obj[PWM3_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM3_CH4
    stm32_pwm_obj[PWM3_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM4_CH1
    stm32_pwm_obj[PWM4_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM4_CH2
    stm32_pwm_obj[PWM4_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM4_CH3
    stm32_pwm_obj[PWM4_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM4_CH4
    stm32_pwm_obj[PWM4_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM5_CH1
    stm32_pwm_obj[PWM5_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM5_CH2
    stm32_pwm_obj[PWM5_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM5_CH3
    stm32_pwm_obj[PWM5_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM5_CH4
    stm32_pwm_obj[PWM5_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM6_CH1
    stm32_pwm_obj[PWM6_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM6_CH2
    stm32_pwm_obj[PWM6_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM6_CH3
    stm32_pwm_obj[PWM6_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM6_CH4
    stm32_pwm_obj[PWM6_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM7_CH1
    stm32_pwm_obj[PWM7_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM7_CH2
    stm32_pwm_obj[PWM7_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM7_CH3
    stm32_pwm_obj[PWM7_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM7_CH4
    stm32_pwm_obj[PWM7_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM8_CH1
    stm32_pwm_obj[PWM8_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM8_CH2
    stm32_pwm_obj[PWM8_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM8_CH3
    stm32_pwm_obj[PWM8_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM8_CH4
    stm32_pwm_obj[PWM8_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM9_CH1
    stm32_pwm_obj[PWM9_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM9_CH2
    stm32_pwm_obj[PWM9_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM9_CH3
    stm32_pwm_obj[PWM9_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_PWM9_CH4
    stm32_pwm_obj[PWM9_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_PWM10_CH1
    stm32_pwm_obj[PWM10_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM11_CH1
    stm32_pwm_obj[PWM11_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM12_CH1
    stm32_pwm_obj[PWM12_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM12_CH2
    stm32_pwm_obj[PWM12_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_PWM13_CH1
    stm32_pwm_obj[PWM13_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM14_CH1
    stm32_pwm_obj[PWM14_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM15_CH1
    stm32_pwm_obj[PWM15_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM16_CH1
    stm32_pwm_obj[PWM16_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_PWM17_CH1
    stm32_pwm_obj[PWM17_INDEX].channel |= 1 << 0;
#endif
}

static int stm32_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    stm32_pwm_get_channel();

    for (i = 0; i < sizeof(stm32_pwm_obj) / sizeof(stm32_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (stm32_hw_pwm_init(&stm32_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", stm32_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            LOG_D("%s init success", stm32_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&stm32_pwm_obj[i].pwm_device, stm32_pwm_obj[i].name, &drv_ops, &stm32_pwm_obj[i].tim_handle) == RT_EOK)
            {
                LOG_D("%s register success", stm32_pwm_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", stm32_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(stm32_pwm_init);
#endif /* BSP_USING_PWM */
