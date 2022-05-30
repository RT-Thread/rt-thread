/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-22     ryan         first version
 */

#include <board.h>
#ifdef BSP_USING_INPUTCAPTURE
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.inputcapture"
#include <drv_log.h>

#define MAX_PERIOD          65535
#define MAX_PULSE           1000    //支持最大脉宽宽度65.535000s = 65535us * 1000

enum
{
#ifdef BSP_USING_IC1
        IC1_INDEX,
#endif
#ifdef BSP_USING_IC2
        IC2_INDEX,
#endif
#ifdef BSP_USING_IC3
        IC3_INDEX,
#endif
#ifdef BSP_USING_IC4
        IC4_INDEX,
#endif
#ifdef BSP_USING_IC5
        IC5_INDEX,
#endif
#ifdef BSP_USING_IC6
        IC6_INDEX,
#endif
#ifdef BSP_USING_IC7
        IC7_INDEX,
#endif
#ifdef BSP_USING_IC8
        IC8_INDEX,
#endif

};

typedef enum {
    POLARITY_BOTHEDGE,      /* 所有脉冲 */
    POLARITY_RISING,        /* 高电位脉冲 */
    POLARITY_FALLING,       /* 低电位脉冲 */
}trigger_polarity;

struct pulse_data
{
    rt_uint32_t                     last_overflow;  //最近一次触发时定时器溢出次数
    rt_uint32_t                     last_cnt;       //最近一次触发时定时器读数
    trigger_polarity                polarity;       //当前极性
};

struct stm32_inputcapture
{
    struct rt_inputcapture_device   ic_device;
    TIM_HandleTypeDef               tim_handle;
    IRQn_Type                       tim_irqn;
    rt_uint32_t                     tim_overflow;     //定时器溢出次数
    rt_uint8_t                      channel;
    char                            *name;
    struct pulse_data               data[4];

};

static struct stm32_inputcapture stm32_inputcapture_obj[] =
{
#ifdef BSP_USING_IC1
        IC1_CONFIG,
#endif

#ifdef BSP_USING_IC2
        IC2_CONFIG,
#endif

#ifdef BSP_USING_IC3
        IC3_CONFIG,
#endif

#ifdef BSP_USING_IC4
        IC4_CONFIG,
#endif

#ifdef BSP_USING_IC5
        IC5_CONFIG,
#endif

#ifdef BSP_USING_IC6
        IC6_CONFIG,
#endif

#ifdef BSP_USING_IC7
        IC7_CONFIG,
#endif

#ifdef BSP_USING_IC8
        IC8_CONFIG,
#endif

};

static rt_err_t drv_inputcapture_control(struct rt_inputcapture_device *device, int cmd, void *arg);
static struct rt_inputcapture_ops drv_ops =
{
    .control = drv_inputcapture_control,
};

static rt_err_t drv_inputcapture_enable(TIM_HandleTypeDef *htim,
                                                    struct rt_inputcapture_configuration *configuration,
                                                    rt_bool_t enable)
{
    /* Converts the channel number to the channel number of Hal library */
    rt_uint32_t channel = 0x04 * (configuration->channel - 1);

    if (!enable)
    {
        HAL_TIM_IC_Stop_IT(htim, channel);
    }
    else
    {
        HAL_TIM_IC_Start_IT(htim, channel);
    }

    return RT_EOK;
}

static rt_err_t drv_inputcapture_control(struct rt_inputcapture_device *device, int cmd, void *arg)
{
    struct rt_inputcapture_configuration *configuration = (struct rt_inputcapture_configuration *)arg;
    TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)device->parent.user_data;

    switch (cmd)
    {
    case INPUTCAPTURE_CMD_ENABLE:
        return drv_inputcapture_enable(htim, configuration, RT_TRUE);
    case INPUTCAPTURE_CMD_DISABLE:
        return drv_inputcapture_enable(htim, configuration, RT_FALSE);
    default:
        return RT_EINVAL;
    }
}

static rt_uint64_t get_timer_clock(TIM_HandleTypeDef *htim)
{
    rt_uint64_t tim_clock = 0;

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    if (htim->Instance == TIM9 || htim->Instance == TIM10 || htim->Instance == TIM11 || htim->Instance == TIM1 || htim->Instance == TIM8)
#elif defined(SOC_SERIES_STM32L4)
    if (htim->Instance == TIM15 || htim->Instance == TIM16 || htim->Instance == TIM17)
#elif defined(SOC_SERIES_STM32MP1)
    if (htim->Instance == TIM4)
#elif defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)
    if (0)
#endif
    {
#if !defined(SOC_SERIES_STM32F0) && !defined(SOC_SERIES_STM32G0)
        tim_clock = HAL_RCC_GetPCLK2Freq() * 2;
#endif
    }
    else
    {
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)
        tim_clock = HAL_RCC_GetPCLK1Freq();
#else
        tim_clock = HAL_RCC_GetPCLK1Freq() * 2;
#endif
    }

    return tim_clock;
}

void _inputcapture_data_init(struct stm32_inputcapture *device, uint32_t channel)
{
    uint32_t channel_index = 0;

    if (channel == TIM_CHANNEL_1)
    {
        channel_index = 0;
    }
    else if (channel == TIM_CHANNEL_2)
    {
        channel_index = 1;
    }
    else if (channel == TIM_CHANNEL_3)
    {
        channel_index = 2;
    }
    else if (channel == TIM_CHANNEL_4)
    {
        channel_index = 3;
    }
    else
    {
        return;
    }

    device->tim_overflow = 0;
    device->data[channel_index].last_overflow = 0;
    device->data[channel_index].last_cnt = 0;
    device->data[channel_index].polarity = POLARITY_RISING;
}

static rt_err_t stm32_hw_inputcapture_init(struct stm32_inputcapture *device)
{
    TIM_HandleTypeDef *tim = RT_NULL;
    TIM_IC_InitTypeDef ic_config = {0};
    TIM_MasterConfigTypeDef master_config = {0};
    TIM_ClockConfigTypeDef clock_config = {0};
    rt_uint64_t tim_clock = 0;

    RT_ASSERT(device != RT_NULL);

    tim = (TIM_HandleTypeDef *)&device->tim_handle;

    tim_clock = get_timer_clock(tim) / 1000000;

    /* configure the timer to ic mode */
    tim->Init.Prescaler = tim_clock-1;
    tim->Init.CounterMode = TIM_COUNTERMODE_UP;
    tim->Init.Period = MAX_PERIOD-1;
    tim->Init.AutoReloadPreload = MAX_PERIOD-1;
    tim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4)
    tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#else
    tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
#endif

    if (HAL_TIM_Base_Init(tim) != HAL_OK)
    {
        LOG_E("%s ic init failed", device->name);
        return -RT_ERROR;
    }

    clock_config.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(tim, &clock_config) != HAL_OK)
    {
        LOG_E("%s clock init failed", device->name);
        return -RT_ERROR;
    }

    master_config.MasterOutputTrigger = TIM_TRGO_RESET;
    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(tim, &master_config) != HAL_OK)
    {
        LOG_E("%s master config failed", device->name);
        return -RT_ERROR;
    }

    ic_config.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    ic_config.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ic_config.ICPrescaler = TIM_ICPSC_DIV1;
    ic_config.ICFilter = 0;

    /* config inputcapture channel */
    if (device->channel & 0x01)
    {
        _inputcapture_data_init(device, TIM_CHANNEL_1);
        if (HAL_TIM_IC_ConfigChannel(tim, &ic_config, TIM_CHANNEL_1) != HAL_OK)
        {
            LOG_E("%s channel1 config failed", device->name);
            return -RT_ERROR;
        }
    }

    if (device->channel & 0x02)
    {
        _inputcapture_data_init(device, TIM_CHANNEL_2);
        if (HAL_TIM_IC_ConfigChannel(tim, &ic_config, TIM_CHANNEL_2) != HAL_OK)
        {
            LOG_E("%s channel2 config failed", device->name);
            return -RT_ERROR;
        }
    }

    if (device->channel & 0x04)
    {
        _inputcapture_data_init(device, TIM_CHANNEL_3);
        if (HAL_TIM_IC_ConfigChannel(tim, &ic_config, TIM_CHANNEL_3) != HAL_OK)
        {
            LOG_E("%s channel3 config failed", device->name);
            return -RT_ERROR;
        }
    }

    if (device->channel & 0x08)
    {
        _inputcapture_data_init(device, TIM_CHANNEL_4);
        if (HAL_TIM_IC_ConfigChannel(tim, &ic_config, TIM_CHANNEL_4) != HAL_OK)
        {
            LOG_E("%s channel4 config failed", device->name);
            return -RT_ERROR;
        }
    }

    /* enable update request source */
    __HAL_TIM_URS_ENABLE(tim);
    __HAL_TIM_ENABLE_IT(tim,TIM_IT_UPDATE);

    return RT_EOK;
}

static void inputcapture_get_channel(void)
{
#ifdef BSP_USING_IC1_CH1
        stm32_inputcapture_obj[IC1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC1_CH2
        stm32_inputcapture_obj[IC1_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC1_CH3
        stm32_inputcapture_obj[IC1_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC1_CH4
        stm32_inputcapture_obj[IC1_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC2_CH1
        stm32_inputcapture_obj[IC2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC2_CH2
        stm32_inputcapture_obj[IC2_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC2_CH3
        stm32_inputcapture_obj[IC2_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC2_CH4
        stm32_inputcapture_obj[IC2_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC3_CH1
        stm32_inputcapture_obj[IC3_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC3_CH2
        stm32_inputcapture_obj[IC3_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC3_CH3
        stm32_inputcapture_obj[IC3_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC3_CH4
        stm32_inputcapture_obj[IC3_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC4_CH1
        stm32_inputcapture_obj[IC4_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC4_CH2
        stm32_inputcapture_obj[IC4_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC4_CH3
        stm32_inputcapture_obj[IC4_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC4_CH4
        stm32_inputcapture_obj[IC4_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC5_CH1
        stm32_inputcapture_obj[IC5_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC5_CH2
        stm32_inputcapture_obj[IC5_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC5_CH3
        stm32_inputcapture_obj[IC5_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC5_CH4
        stm32_inputcapture_obj[IC5_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC6_CH1
        stm32_inputcapture_obj[IC6_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC6_CH2
        stm32_inputcapture_obj[IC6_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC6_CH3
        stm32_inputcapture_obj[IC6_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC6_CH4
        stm32_inputcapture_obj[IC6_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC7_CH1
        stm32_inputcapture_obj[IC7_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC7_CH2
        stm32_inputcapture_obj[IC7_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC7_CH3
        stm32_inputcapture_obj[IC7_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC7_CH4
        stm32_inputcapture_obj[IC7_INDEX].channel |= 1 << 3;
#endif
#ifdef BSP_USING_IC8_CH1
        stm32_inputcapture_obj[IC8_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_IC8_CH2
        stm32_inputcapture_obj[IC8_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_IC8_CH3
        stm32_inputcapture_obj[IC8_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_IC8_CH4
        stm32_inputcapture_obj[IC8_INDEX].channel |= 1 << 3;
#endif
}

#ifdef BSP_USING_IC8
void TIM8_UP_TIM13_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_inputcapture_obj[IC8_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}

void TIM8_CC_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_inputcapture_obj[IC8_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/*
*   计算脉冲
*/
void _capture_computer(struct stm32_inputcapture *ic, rt_uint32_t channel)
{
    struct rt_inputcapture_data data = {0};
    rt_uint32_t channel_index = 0;
    rt_uint32_t trigger_overflow = 0;
    rt_uint32_t trigger_cnt = 0;

    if (channel == TIM_CHANNEL_1)
    {
        channel_index = 0;
    }
    else if (channel == TIM_CHANNEL_2)
    {
        channel_index = 1;
    }
    else if (channel == TIM_CHANNEL_3)
    {
        channel_index = 2;
    }
    else if (channel == TIM_CHANNEL_4)
    {
        channel_index = 3;
    }
    else
    {
        return;
    }

    if (ic->data[channel_index].polarity == POLARITY_RISING)
    {
        TIM_RESET_CAPTUREPOLARITY(&ic->tim_handle, channel);                      //清除原来的设置
        TIM_SET_CAPTUREPOLARITY(&ic->tim_handle,channel, TIM_ICPOLARITY_FALLING); //设置上升沿捕获
        ic->data[channel_index].polarity = POLARITY_FALLING;
    }
    else
    {
        TIM_RESET_CAPTUREPOLARITY(&ic->tim_handle, channel);                      //清除原来的设置
        TIM_SET_CAPTUREPOLARITY(&ic->tim_handle,channel, TIM_ICPOLARITY_RISING);  //设置下降沿捕获
        ic->data[channel_index].polarity = POLARITY_RISING;
    }

    /* 获取计数 */
    trigger_cnt = HAL_TIM_ReadCapturedValue(&ic->tim_handle, channel);
    trigger_overflow = ic->tim_overflow;

    /* 脉宽超过最大值 */
    if((trigger_overflow < ic->data[channel_index].last_overflow) ||
       ((trigger_overflow - ic->data[channel_index].last_overflow) > MAX_PULSE))
    {
        ic->data[channel_index].last_overflow = trigger_overflow;
        ic->data[channel_index].last_cnt = trigger_cnt;

        return;
    }

    /* 计算脉宽 */
    data.pulsewidth_us = (trigger_overflow - ic->data[channel_index].last_overflow)*MAX_PERIOD
                            + trigger_cnt - ic->data[channel_index].last_cnt;
    if (ic->data[channel_index].polarity == POLARITY_FALLING)
    {
        data.pulsewidth_us = -data.pulsewidth_us;
    }
    data.channel = (inputcapture_ch_t)(channel_index+1);
    rt_hw_inputcapture_isr(&ic->ic_device, &data);

    ic->data[channel_index].last_overflow = trigger_overflow;
    ic->data[channel_index].last_cnt = trigger_cnt;

    return;
}

void HAL_TIM_IC_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
#ifdef BSP_USING_IC8
    if (htim->Instance == TIM8)
    {
        stm32_inputcapture_obj[IC8_INDEX].tim_overflow++;
    }
#endif
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
#ifdef BSP_USING_IC8
    if (htim->Instance == TIM8)
    {
        /* 计算脉宽 */
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            _capture_computer(&stm32_inputcapture_obj[IC8_INDEX], TIM_CHANNEL_1);
        }
        else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            _capture_computer(&stm32_inputcapture_obj[IC8_INDEX], TIM_CHANNEL_2);
        }
        else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            _capture_computer(&stm32_inputcapture_obj[IC8_INDEX], TIM_CHANNEL_3);
        }
        else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            _capture_computer(&stm32_inputcapture_obj[IC8_INDEX], TIM_CHANNEL_4);
        }

    }
#endif
}

static int stm32_inputcapture_init(void)
{
    int i = 0;

    inputcapture_get_channel();

    for (i = 0; i < sizeof(stm32_inputcapture_obj) / sizeof(stm32_inputcapture_obj[0]); i++)
    {
        /* inputcapture init */
        if (stm32_hw_inputcapture_init(&stm32_inputcapture_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", stm32_inputcapture_obj[i].name);
            return -RT_ERROR;
        }
        else
        {
            LOG_D("%s init success", stm32_inputcapture_obj[i].name);

            /* register inputcapture device */
            if (rt_device_inputcapture_register(&stm32_inputcapture_obj[i].ic_device, stm32_inputcapture_obj[i].name,
                                                &drv_ops, &stm32_inputcapture_obj[i].tim_handle) == RT_EOK)
            {
                LOG_D("%s register success", stm32_inputcapture_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", stm32_inputcapture_obj[i].name);
                return -RT_ERROR;
            }
        }
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(stm32_inputcapture_init);
#endif /* BSP_USING_INPUTCAPTURE */
