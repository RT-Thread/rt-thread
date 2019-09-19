/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     zylx         first version
 */

#include <board.h>
#ifdef BSP_USING_TIM
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.hwtimer"
#include <drv_log.h>

#ifdef RT_USING_HWTIMER
enum
{
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_TIM3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_TIM4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_TIM5
    TIM5_INDEX,
#endif
#ifdef BSP_USING_TIM6
    TIM6_INDEX,
#endif
#ifdef BSP_USING_TIM7
    TIM7_INDEX,
#endif
#ifdef BSP_USING_TIM8
    TIM8_INDEX,
#endif
#ifdef BSP_USING_TIM9
    TIM9_INDEX,
#endif
#ifdef BSP_USING_TIM10
    TIM10_INDEX,
#endif
#ifdef BSP_USING_TIM11
    TIM11_INDEX,
#endif
#ifdef BSP_USING_TIM12
    TIM12_INDEX,
#endif
#ifdef BSP_USING_TIM13
    TIM13_INDEX,
#endif
#ifdef BSP_USING_TIM14
    TIM14_INDEX,
#endif
#ifdef BSP_USING_TIM15
    TIM15_INDEX,
#endif
#ifdef BSP_USING_TIM16
    TIM16_INDEX,
#endif
#ifdef BSP_USING_TIM17
    TIM17_INDEX,
#endif
};

struct stm32_hwtimer
{
    rt_hwtimer_t time_device;
    TIM_HandleTypeDef    tim_handle;
    IRQn_Type tim_irqn;
    char *name;
};

static struct stm32_hwtimer stm32_hwtimer_obj[] =
{
#ifdef BSP_USING_TIM1
    TIM1_CONFIG,
#endif

#ifdef BSP_USING_TIM2
    TIM2_CONFIG,
#endif

#ifdef BSP_USING_TIM3
    TIM3_CONFIG,
#endif

#ifdef BSP_USING_TIM4
    TIM4_CONFIG,
#endif

#ifdef BSP_USING_TIM5
    TIM5_CONFIG,
#endif

#ifdef BSP_USING_TIM6
    TIM6_CONFIG,
#endif

#ifdef BSP_USING_TIM7
    TIM7_CONFIG,
#endif

#ifdef BSP_USING_TIM8
    TIM8_CONFIG,
#endif

#ifdef BSP_USING_TIM9
    TIM9_CONFIG,
#endif

#ifdef BSP_USING_TIM10
    TIM10_CONFIG,
#endif

#ifdef BSP_USING_TIM11
    TIM11_CONFIG,
#endif

#ifdef BSP_USING_TIM12
    TIM12_CONFIG,
#endif

#ifdef BSP_USING_TIM13
    TIM13_CONFIG,
#endif

#ifdef BSP_USING_TIM14
    TIM14_CONFIG,
#endif

#ifdef BSP_USING_TIM15
    TIM15_CONFIG,
#endif

#ifdef BSP_USING_TIM16
    TIM16_CONFIG,
#endif

#ifdef BSP_USING_TIM17
    TIM17_CONFIG,
#endif
};

static void timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    uint32_t prescaler_value = 0;
    TIM_HandleTypeDef *tim = RT_NULL;
    struct stm32_hwtimer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        tim = (TIM_HandleTypeDef *)timer->parent.user_data;
        tim_device = (struct stm32_hwtimer *)timer;

        /* time init */
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
        if (tim->Instance == TIM9 || tim->Instance == TIM10 || tim->Instance == TIM11)
#elif defined(SOC_SERIES_STM32L4)
        if (tim->Instance == TIM15 || tim->Instance == TIM16 || tim->Instance == TIM17)
#elif defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)
        if (0)
#endif
        {
#if !defined(SOC_SERIES_STM32F0) && !defined(SOC_SERIES_STM32G0)
            prescaler_value = (uint32_t)(HAL_RCC_GetPCLK2Freq() * 2 / 10000) - 1;
#endif
        }
        else
        {
            prescaler_value = (uint32_t)(HAL_RCC_GetPCLK1Freq() * 2 / 10000) - 1;
        }
        tim->Init.Period            = 10000 - 1;
        tim->Init.Prescaler         = prescaler_value;
        tim->Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            tim->Init.CounterMode   = TIM_COUNTERMODE_UP;
        }
        else
        {
            tim->Init.CounterMode   = TIM_COUNTERMODE_DOWN;
        }
        tim->Init.RepetitionCounter = 0;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)
        tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#endif
        if (HAL_TIM_Base_Init(tim) != HAL_OK)
        {
            LOG_E("%s init failed", tim_device->name);
            return;
        }
        else
        {
            /* set the TIMx priority */
            HAL_NVIC_SetPriority(tim_device->tim_irqn, 3, 0);

            /* enable the TIMx global Interrupt */
            HAL_NVIC_EnableIRQ(tim_device->tim_irqn);

            /* clear update flag */
            __HAL_TIM_CLEAR_FLAG(tim, TIM_FLAG_UPDATE);
            /* enable update request source */
            __HAL_TIM_URS_ENABLE(tim);

            LOG_D("%s init success", tim_device->name);
        }
    }
}

static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* set tim cnt */
    __HAL_TIM_SET_AUTORELOAD(tim, t - 1);

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        tim->Instance->CR1 |= TIM_OPMODE_SINGLE;
    }
    else
    {
        tim->Instance->CR1 &= (~TIM_OPMODE_SINGLE);
    }
	
    /* start timer */
    if (HAL_TIM_Base_Start_IT(tim) != HAL_OK)
    {
        LOG_E("TIM start failed");
        result = -RT_ERROR;
    }

    return result;
}

static void timer_stop(rt_hwtimer_t *timer)
{
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* stop timer */
    HAL_TIM_Base_Stop_IT(tim);
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    TIM_HandleTypeDef *tim = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        rt_uint16_t val;

        /* set timer frequence */
        freq = *((rt_uint32_t *)arg);

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
        if (tim->Instance == TIM9 || tim->Instance == TIM10 || tim->Instance == TIM11)
#elif defined(SOC_SERIES_STM32L4)
        if (tim->Instance == TIM15 || tim->Instance == TIM16 || tim->Instance == TIM17)
#elif defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)
        if (0)
#endif
        {
#if defined(SOC_SERIES_STM32L4)
            val = HAL_RCC_GetPCLK2Freq() / freq;
#elif defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            val = HAL_RCC_GetPCLK2Freq() * 2 / freq;
#endif
        }
        else
        {
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            val = HAL_RCC_GetPCLK1Freq() * 2 / freq;
#elif defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)
            val = HAL_RCC_GetPCLK1Freq() / freq;
#endif
        }
        __HAL_TIM_SET_PRESCALER(tim, val - 1);

        /* Update frequency value */
        tim->Instance->EGR |= TIM_EVENTSOURCE_UPDATE;
    }
    break;
    default:
    {
        result = -RT_ENOSYS;
    }
    break;
    }

    return result;
}

static rt_uint32_t timer_counter_get(rt_hwtimer_t *timer)
{
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    return tim->Instance->CNT;
}

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;

static const struct rt_hwtimer_ops _ops =
{
    .init = timer_init,
    .start = timer_start,
    .stop = timer_stop,
    .count_get = timer_counter_get,
    .control = timer_ctrl,
};

#ifdef BSP_USING_TIM2
void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM2_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM3
void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM3_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM4
void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM4_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM5
void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM5_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM11
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM11_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM13
void TIM8_UP_TIM13_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM13_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM14
#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    void TIM8_TRG_COM_TIM14_IRQHandler(void)
#elif defined(SOC_SERIES_STM32F0)
    void TIM14_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM14_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM15
void TIM1_BRK_TIM15_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM15_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM16
#if defined(SOC_SERIES_STM32L4)
    void TIM1_UP_TIM16_IRQHandler(void)
#elif defined(SOC_SERIES_STM32F0)
    void TIM16_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM16_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM17
#if defined(SOC_SERIES_STM32L4)
    void TIM1_TRG_COM_TIM17_IRQHandler(void)
#elif defined(SOC_SERIES_STM32F0)
    void TIM17_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_hwtimer_obj[TIM17_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
#ifdef BSP_USING_TIM2
    if (htim->Instance == TIM2)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM2_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM3
    if (htim->Instance == TIM3)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM3_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM4
    if (htim->Instance == TIM4)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM4_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM5
    if (htim->Instance == TIM5)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM5_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM11
    if (htim->Instance == TIM11)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM11_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM13
    if (htim->Instance == TIM13)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM13_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM14
    if (htim->Instance == TIM14)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM14_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM15
    if (htim->Instance == TIM15)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM15_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM16
    if (htim->Instance == TIM16)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM16_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM17
    if (htim->Instance == TIM17)
    {
        rt_device_hwtimer_isr(&stm32_hwtimer_obj[TIM17_INDEX].time_device);
    }
#endif
}

static int stm32_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(stm32_hwtimer_obj) / sizeof(stm32_hwtimer_obj[0]); i++)
    {
        stm32_hwtimer_obj[i].time_device.info = &_info;
        stm32_hwtimer_obj[i].time_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&stm32_hwtimer_obj[i].time_device, stm32_hwtimer_obj[i].name, &stm32_hwtimer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", stm32_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", stm32_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(stm32_hwtimer_init);

#endif /* RT_USING_HWTIMER */
#endif /* BSP_USING_TIM */
