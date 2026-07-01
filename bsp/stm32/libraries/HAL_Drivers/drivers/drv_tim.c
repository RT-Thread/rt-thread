/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     zylx         first version
 * 2020-06-16     thread-liu   Porting for stm32mp1
 * 2020-08-25     linyongkang  Fix the timer clock frequency doubling problem
 * 2020-10-14     PeakRacing   Porting for stm32wbxx
 * 2020-11-18     leizhixiong  add STM32H7 series support
 * 2023-08-21     Donocean     fix the MCU crash when using timer6
 * 2023-12-24     Meco Man     add TIMx existing check
 */

#include <rtdevice.h>
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.tim"
#include <drv_log.h>

#if defined(BSP_USING_TIM1) && !defined(TIM1)
#error "timer1 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM1"
#endif
#if defined(BSP_USING_TIM2) && !defined(TIM2)
#error "timer2 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM2"
#endif
#if defined(BSP_USING_TIM3) && !defined(TIM3)
#error "timer3 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM3"
#endif
#if defined(BSP_USING_TIM4) && !defined(TIM4)
#error "timer4 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM4"
#endif
#if defined(BSP_USING_TIM5) && !defined(TIM5)
#error "timer5 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM5"
#endif
#if defined(BSP_USING_TIM6) && !defined(TIM6)
#error "timer6 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM6"
#endif
#if defined(BSP_USING_TIM7) && !defined(TIM7)
#error "timer7 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM7"
#endif
#if defined(BSP_USING_TIM8) && !defined(TIM8)
#error "timer8 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM8"
#endif
#if defined(BSP_USING_TIM9) && !defined(TIM9)
#error "timer9 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM9"
#endif
#if defined(BSP_USING_TIM10) && !defined(TIM10)
#error "timer10 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM10"
#endif
#if defined(BSP_USING_TIM11) && !defined(TIM11)
#error "timer11 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM11"
#endif
#if defined(BSP_USING_TIM12) && !defined(TIM12)
#error "timer12 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM12"
#endif
#if defined(BSP_USING_TIM13) && !defined(TIM13)
#error "timer13 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM13"
#endif
#if defined(BSP_USING_TIM14) && !defined(TIM14)
#error "timer14 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM14"
#endif
#if defined(BSP_USING_TIM15) && !defined(TIM15)
#error "timer15 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM15"
#endif
#if defined(BSP_USING_TIM16) && !defined(TIM16)
#error "timer16 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM16"
#endif
#if defined(BSP_USING_TIM17) && !defined(TIM17)
#error "timer17 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM17"
#endif
#if defined(BSP_USING_TIM18) && !defined(TIM18)
#error "timer18 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM18"
#endif
#if defined(BSP_USING_TIM19) && !defined(TIM19)
#error "timer19 doesn't exist in this STM32 series, but you enabled the BSP_USING_TIM19"
#endif

/* APBx timer clocks frequency doubler state related to APB1CLKDivider value */
void stm32_tim_pclkx_doubler_get(rt_uint32_t *pclk1_doubler, rt_uint32_t *pclk2_doubler)
{
    rt_uint32_t flatency = 0;
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RT_ASSERT(pclk1_doubler != RT_NULL);
    RT_ASSERT(pclk1_doubler != RT_NULL);

    HAL_RCC_GetClockConfig(&RCC_ClkInitStruct, &flatency);

    *pclk1_doubler = 1;
    *pclk2_doubler = 1;

#if defined(SOC_SERIES_STM32MP1)
    if (RCC_ClkInitStruct.APB1_Div != RCC_APB1_DIV1)
    {
        *pclk1_doubler = 2;
    }
    if (RCC_ClkInitStruct.APB2_Div != RCC_APB2_DIV1)
    {
        *pclk2_doubler = 2;
    }
#else
    if (RCC_ClkInitStruct.APB1CLKDivider != RCC_HCLK_DIV1)
    {
         *pclk1_doubler = 2;
    }
#if !(defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0))
    if (RCC_ClkInitStruct.APB2CLKDivider != RCC_HCLK_DIV1)
    {
         *pclk2_doubler = 2;
    }
#endif /* !(defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0)) */
#endif /* defined(SOC_SERIES_STM32MP1) */
}

#if defined(RT_USING_CLOCK_TIMER_TRIGGER)
/**
 * @brief Get the effective input clock frequency of one STM32 timer.
 * @param tim Pointer to the STM32 HAL timer handle.
 * @param timer_clk Pointer to the output timer clock frequency in hertz.
 * @return Operation status.
 */
static rt_err_t stm32_tim_clock_get(TIM_HandleTypeDef *tim, rt_uint32_t *timer_clk)
{
    rt_uint32_t pclk1_doubler;
    rt_uint32_t pclk2_doubler;

    stm32_tim_pclkx_doubler_get(&pclk1_doubler, &pclk2_doubler);

#if defined(APBPERIPH_BASE)
    *timer_clk = HAL_RCC_GetPCLK1Freq() * pclk1_doubler;
#elif defined(APB1PERIPH_BASE) || defined(APB2PERIPH_BASE)
    if ((rt_uint32_t)tim->Instance >= APB2PERIPH_BASE)
    {
        *timer_clk = HAL_RCC_GetPCLK2Freq() * pclk2_doubler;
    }
    else
    {
        *timer_clk = HAL_RCC_GetPCLK1Freq() * pclk1_doubler;
    }
#else
#error "This driver has not supported this series yet!"
#endif /* defined(APBPERIPH_BASE) */

    if (*timer_clk == 0U)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif /* defined(RT_USING_CLOCK_TIMER_TRIGGER) */

void stm32_tim_enable_clock(TIM_HandleTypeDef* htim_base)
{
    RT_ASSERT(htim_base != RT_NULL);

    if(RT_FALSE);
#ifdef TIM1
    else if(htim_base->Instance==TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
    }
#endif /* TIM1 */
#ifdef TIM2
    else if(htim_base->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }
#endif /* TIM2 */
#ifdef TIM3
    else if(htim_base->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
    }
#endif /* TIM3 */
#ifdef TIM4
    else if(htim_base->Instance==TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
    }
#endif /* TIM4 */
#ifdef TIM5
    else if(htim_base->Instance==TIM5)
    {
        __HAL_RCC_TIM5_CLK_ENABLE();
    }
#endif /* TIM5 */
#ifdef TIM6
    else if(htim_base->Instance==TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();
    }
#endif /* TIM6 */
#ifdef TIM7
    else if(htim_base->Instance==TIM7)
    {
        __HAL_RCC_TIM7_CLK_ENABLE();
    }
#endif /* TIM7 */
#ifdef TIM8
    else if(htim_base->Instance==TIM8)
    {
        __HAL_RCC_TIM8_CLK_ENABLE();
    }
#endif /* TIM8 */
#ifdef TIM9
    else if(htim_base->Instance==TIM9)
    {
        __HAL_RCC_TIM9_CLK_ENABLE();
    }
#endif /* TIM9 */
#ifdef TIM10
    else if(htim_base->Instance==TIM10)
    {
        __HAL_RCC_TIM10_CLK_ENABLE();
    }
#endif /* TIM10 */
#ifdef TIM11
    else if(htim_base->Instance==TIM11)
    {
        __HAL_RCC_TIM11_CLK_ENABLE();
    }
#endif /* TIM11 */
#ifdef TIM12
    else if(htim_base->Instance==TIM12)
    {
        __HAL_RCC_TIM12_CLK_ENABLE();
    }
#endif /* TIM12 */
#ifdef TIM13
    else if(htim_base->Instance==TIM13)
    {
        __HAL_RCC_TIM13_CLK_ENABLE();
    }
#endif /* TIM13 */
#ifdef TIM14
    else if(htim_base->Instance==TIM14)
    {
        __HAL_RCC_TIM14_CLK_ENABLE();
    }
#endif /* TIM14 */
#ifdef TIM15
    else if(htim_base->Instance==TIM15)
    {
        __HAL_RCC_TIM15_CLK_ENABLE();
    }
#endif /* TIM15 */
#ifdef TIM16
    else if(htim_base->Instance==TIM16)
    {
        __HAL_RCC_TIM16_CLK_ENABLE();
    }
#endif /* TIM16 */
#ifdef TIM17
    else if(htim_base->Instance==TIM17)
    {
        __HAL_RCC_TIM17_CLK_ENABLE();
    }
#endif /* TIM17 */
#ifdef TIM18
    else if(htim_base->Instance==TIM18)
    {
        __HAL_RCC_TIM18_CLK_ENABLE();
    }
#endif /* TIM18 */
#ifdef TIM19
    else if(htim_base->Instance==TIM19)
    {
        __HAL_RCC_TIM19_CLK_ENABLE();
    }
#endif /* TIM19 */
    else
    {
        RT_ASSERT(RT_TRUE);
    }
}

#ifdef BSP_USING_TIM

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

struct stm32_clock_timer
{
    rt_clock_timer_t time_device;
    TIM_HandleTypeDef    tim_handle;
    IRQn_Type tim_irqn;
    char *name;
#if defined(RT_USING_CLOCK_TIMER_TRIGGER)
    enum rt_clock_timer_trigger_event trigger_event; /**< Cached trigger output event. */
    rt_uint16_t trigger_channel;                     /**< Cached compare channel, or 0 for update event. */
#endif /* defined(RT_USING_CLOCK_TIMER_TRIGGER) */
};

static struct stm32_clock_timer stm32_clock_timer_obj[] =
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

static void timer_init(struct rt_clock_timer_device *timer, rt_uint32_t state)
{
    uint32_t prescaler_value = 0;
    uint32_t pclk1_doubler, pclk2_doubler;
    TIM_HandleTypeDef *tim = RT_NULL;
    struct stm32_clock_timer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        tim = (TIM_HandleTypeDef *)timer->parent.user_data;
        tim_device = (struct stm32_clock_timer *)timer;

        stm32_tim_pclkx_doubler_get(&pclk1_doubler, &pclk2_doubler);

        /* time init */
        /* Some series may only have APBPERIPH_BASE, don't have HAL_RCC_GetPCLK2Freq */
#if defined(APBPERIPH_BASE)
        prescaler_value = (uint32_t)(HAL_RCC_GetPCLK1Freq() * pclk1_doubler / 10000) - 1;
#elif defined(APB1PERIPH_BASE) || defined(APB2PERIPH_BASE)
        if ((rt_uint32_t)tim->Instance >= APB2PERIPH_BASE)
        {
            prescaler_value = (uint32_t)(HAL_RCC_GetPCLK2Freq() * pclk2_doubler / 10000) - 1;
        }
        else
        {
            prescaler_value = (uint32_t)(HAL_RCC_GetPCLK1Freq() * pclk1_doubler / 10000) - 1;
        }
#endif
        tim->Init.Period            = 10000 - 1;
        tim->Init.Prescaler         = prescaler_value;
        tim->Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
        if (timer->info->cntmode == CLOCK_TIMER_CNTMODE_UP)
        {
            tim->Init.CounterMode   = TIM_COUNTERMODE_UP;
        }
        else
        {
            tim->Init.CounterMode   = TIM_COUNTERMODE_DOWN;
        }
        tim->Init.RepetitionCounter = 0;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB)
        tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#endif
        if (HAL_TIM_Base_Init(tim) != HAL_OK)
        {
            LOG_E("%s init failed", tim_device->name);
            return;
        }

        stm32_tim_enable_clock(tim);
        HAL_NVIC_SetPriority(tim_device->tim_irqn, 3, 0); /* set the TIMx priority */
        HAL_NVIC_EnableIRQ(tim_device->tim_irqn); /* enable the TIMx global Interrupt */
        __HAL_TIM_CLEAR_FLAG(tim, TIM_FLAG_UPDATE); /* clear update flag */
        __HAL_TIM_URS_ENABLE(tim); /* enable update request source */
        LOG_D("%s init success", tim_device->name);
    }
}

static rt_err_t timer_start(rt_clock_timer_t *timer, rt_uint32_t t, rt_clock_timer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* set tim cnt */
    __HAL_TIM_SET_COUNTER(tim, 0);
    /* set tim arr */
    __HAL_TIM_SET_AUTORELOAD(tim, t - 1);

    if (opmode == CLOCK_TIMER_MODE_ONESHOT)
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

static void timer_stop(rt_clock_timer_t *timer)
{
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    /* stop timer */
    HAL_TIM_Base_Stop_IT(tim);

    /* set tim cnt */
    __HAL_TIM_SET_COUNTER(tim, 0);
}

#if defined(RT_USING_CLOCK_TIMER_TRIGGER)
/**
 * @brief Calculate STM32 timer divider values for hardware trigger output.
 * @param timer Pointer to the RT-Thread clock timer device.
 * @param freq_hz Target trigger frequency in hertz.
 * @param prescaler Pointer to the output PSC register value.
 * @param period Pointer to the output ARR register value.
 * @return Operation status.
 */
static rt_err_t timer_trigger_calc(rt_clock_timer_t *timer, rt_uint32_t freq_hz, rt_uint32_t *prescaler, rt_uint32_t *period)
{
    TIM_HandleTypeDef *tim;
    rt_uint32_t timer_clk;
    rt_uint32_t max_period;
    rt_uint64_t cycles;
    rt_uint64_t prescaler_div;
    rt_uint64_t period_count;
    rt_err_t result;

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;
    result = stm32_tim_clock_get(tim, &timer_clk);
    if (result != RT_EOK)
    {
        return result;
    }

    if (freq_hz > timer_clk)
    {
        return -RT_EINVAL;
    }

    cycles = ((rt_uint64_t)timer_clk + (freq_hz / 2U)) / freq_hz;
    if (cycles == 0U)
    {
        return -RT_EINVAL;
    }

    max_period = ((timer->info != RT_NULL) && (timer->info->maxcnt != 0U)) ? timer->info->maxcnt : 0xffffU;
    prescaler_div = (cycles + max_period - 1U) / max_period;
    if ((prescaler_div == 0U) || (prescaler_div > 0x10000ULL))
    {
        return -RT_EINVAL;
    }

    period_count = cycles / prescaler_div;
    if (period_count == 0U)
    {
        period_count = 1U;
    }
    if (period_count > max_period)
    {
        period_count = max_period;
    }

    *prescaler = (rt_uint32_t)(prescaler_div - 1U);
    *period = (rt_uint32_t)(period_count - 1U);

    return RT_EOK;
}


/** @brief Maximum compare channel index encoded by the STM32 TIM trigger backend. */
#define STM32_TIM_TRIGGER_COMPARE_CHANNEL_MAX 4U

/**
 * @brief STM32 HAL timer compare channel slot.
 */
struct stm32_tim_compare_channel
{
    rt_uint32_t channel; /**< HAL TIM channel selector. */
    rt_uint32_t flag;    /**< HAL TIM compare flag. */
    rt_bool_t valid;     /**< Whether channel and flag are valid. */
};

/**
 * @brief HAL TIM compare channel table indexed by 1-based timer channel number.
 */
static const struct stm32_tim_compare_channel stm32_tim_compare_channel_table[STM32_TIM_TRIGGER_COMPARE_CHANNEL_MAX + 1U] = {
#if defined(TIM_CHANNEL_1) && defined(TIM_FLAG_CC1)
    [1] = { TIM_CHANNEL_1, TIM_FLAG_CC1, RT_TRUE },
#endif /* defined(TIM_CHANNEL_1) && defined(TIM_FLAG_CC1) */
#if defined(TIM_CHANNEL_2) && defined(TIM_FLAG_CC2)
    [2] = { TIM_CHANNEL_2, TIM_FLAG_CC2, RT_TRUE },
#endif /* defined(TIM_CHANNEL_2) && defined(TIM_FLAG_CC2) */
#if defined(TIM_CHANNEL_3) && defined(TIM_FLAG_CC3)
    [3] = { TIM_CHANNEL_3, TIM_FLAG_CC3, RT_TRUE },
#endif /* defined(TIM_CHANNEL_3) && defined(TIM_FLAG_CC3) */
#if defined(TIM_CHANNEL_4) && defined(TIM_FLAG_CC4)
    [4] = { TIM_CHANNEL_4, TIM_FLAG_CC4, RT_TRUE },
#endif /* defined(TIM_CHANNEL_4) && defined(TIM_FLAG_CC4) */
};

/**
 * @brief Get a HAL compare channel slot from a 1-based timer channel number.
 * @param channel 1-based timer compare channel number.
 * @return Pointer to a valid channel slot, or RT_NULL when unsupported.
 */
static const struct stm32_tim_compare_channel *timer_trigger_compare_channel_get(rt_uint16_t channel)
{
    const struct stm32_tim_compare_channel *slot;

    if (channel >= RT_ARRAY_SIZE(stm32_tim_compare_channel_table))
    {
        return RT_NULL;
    }

    slot = &stm32_tim_compare_channel_table[channel];
    return (slot->valid == RT_TRUE) ? slot : RT_NULL;
}

/**
 * @brief Fill the common STM32 timer base configuration for trigger output.
 * @param tim Pointer to the STM32 HAL timer handle.
 * @param prescaler PSC register value.
 * @param period ARR register value.
 */
static void timer_trigger_base_fill(TIM_HandleTypeDef *tim, rt_uint32_t prescaler, rt_uint32_t period)
{
    tim->Init.Prescaler = prescaler;
    tim->Init.Period = period;
    tim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim->Init.CounterMode = TIM_COUNTERMODE_UP;
    tim->Init.RepetitionCounter = 0;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB)
    tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
#endif /* defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G4) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) */
}

/**
 * @brief Configure one STM32 timer update event as a hardware trigger source.
 * @param timer_device Pointer to the STM32 clock timer object.
 * @param prescaler PSC register value.
 * @param period ARR register value.
 * @return Operation status.
 */
static rt_err_t timer_trigger_update_config(struct stm32_clock_timer *timer_device, rt_uint32_t prescaler, rt_uint32_t period)
{
#if defined(TIM_TRGO_UPDATE)
    TIM_HandleTypeDef *tim;
    TIM_MasterConfigTypeDef master = {0};

    tim = &timer_device->tim_handle;
    HAL_TIM_Base_Stop(tim);
    timer_trigger_base_fill(tim, prescaler, period);

    if (HAL_TIM_Base_Init(tim) != HAL_OK)
    {
        LOG_E("TIM trigger base init failed");
        return -RT_ERROR;
    }

    master.MasterOutputTrigger = TIM_TRGO_UPDATE;
#if defined(TIM_MASTERSLAVEMODE_DISABLE)
    master.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
#endif /* defined(TIM_MASTERSLAVEMODE_DISABLE) */
    if (HAL_TIMEx_MasterConfigSynchronization(tim, &master) != HAL_OK)
    {
        LOG_E("TIM trigger master config failed");
        return -RT_ERROR;
    }

    timer_device->trigger_event = CLOCK_TIMER_TRIGGER_EVENT_UPDATE;
    timer_device->trigger_channel = 0U;
    tim->Instance->CR1 &= (~TIM_OPMODE_SINGLE);
    __HAL_TIM_SET_COUNTER(tim, 0);
    __HAL_TIM_CLEAR_FLAG(tim, TIM_FLAG_UPDATE);

    return RT_EOK;
#else
    RT_UNUSED(timer_device);
    RT_UNUSED(prescaler);
    RT_UNUSED(period);
    return -RT_ENOSYS;
#endif /* defined(TIM_TRGO_UPDATE) */
}


/**
 * @brief Configure one STM32 timer compare event as a hardware trigger source.
 * @param timer_device Pointer to the STM32 clock timer object.
 * @param cfg Pointer to the hardware trigger configuration.
 * @param prescaler PSC register value.
 * @param period ARR register value.
 * @return Operation status.
 */
static rt_err_t timer_trigger_compare_config(struct stm32_clock_timer *timer_device,
                                            const struct rt_clock_timer_trigger_cfg *cfg,
                                            rt_uint32_t prescaler, rt_uint32_t period)
{
#if defined(TIM_OCMODE_TIMING)
    const struct stm32_tim_compare_channel *slot;
    TIM_HandleTypeDef *tim;
    TIM_OC_InitTypeDef oc = {0};
    rt_uint32_t pulse;

    slot = timer_trigger_compare_channel_get(cfg->channel);
    if (slot == RT_NULL)
    {
        return -RT_EINVAL;
    }

    tim = &timer_device->tim_handle;
    HAL_TIM_OC_Stop(tim, slot->channel);
    HAL_TIM_Base_Stop(tim);
    timer_trigger_base_fill(tim, prescaler, period);

    if (HAL_TIM_Base_Init(tim) != HAL_OK)
    {
        LOG_E("TIM trigger compare base init failed");
        return -RT_ERROR;
    }
    if (HAL_TIM_OC_Init(tim) != HAL_OK)
    {
        LOG_E("TIM trigger compare init failed");
        return -RT_ERROR;
    }

    pulse = (period + 1U) / 2U;
    if (pulse > period)
    {
        pulse = period;
    }

    oc.OCMode = TIM_OCMODE_PWM2;
    oc.Pulse = pulse;
#if defined(TIM_OCPOLARITY_HIGH)
    oc.OCPolarity = TIM_OCPOLARITY_HIGH;
#endif /* defined(TIM_OCPOLARITY_HIGH) */
#if defined(TIM_OCNPOLARITY_HIGH)
    oc.OCNPolarity = TIM_OCNPOLARITY_HIGH;
#endif /* defined(TIM_OCNPOLARITY_HIGH) */
#if defined(TIM_OCFAST_DISABLE)
    oc.OCFastMode = TIM_OCFAST_DISABLE;
#endif /* defined(TIM_OCFAST_DISABLE) */
#if defined(TIM_OCIDLESTATE_RESET)
    oc.OCIdleState = TIM_OCIDLESTATE_RESET;
#endif /* defined(TIM_OCIDLESTATE_RESET) */
#if defined(TIM_OCNIDLESTATE_RESET)
    oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;
#endif /* defined(TIM_OCNIDLESTATE_RESET) */

    if (HAL_TIM_OC_ConfigChannel(tim, &oc, slot->channel) != HAL_OK)
    {
        LOG_E("TIM trigger compare channel config failed");
        return -RT_ERROR;
    }

    timer_device->trigger_event = CLOCK_TIMER_TRIGGER_EVENT_COMPARE;
    timer_device->trigger_channel = cfg->channel;
    tim->Instance->CR1 &= (~TIM_OPMODE_SINGLE);
    __HAL_TIM_SET_COUNTER(tim, 0);
    __HAL_TIM_CLEAR_FLAG(tim, slot->flag);

    return RT_EOK;
#else
    RT_UNUSED(timer_device);
    RT_UNUSED(cfg);
    RT_UNUSED(prescaler);
    RT_UNUSED(period);
    return -RT_ENOSYS;
#endif /* defined(TIM_OCMODE_TIMING) */
}

/**
 * @brief Configure one STM32 timer as a hardware trigger source.
 * @param timer Pointer to the RT-Thread clock timer device.
 * @param cfg Pointer to the hardware trigger configuration.
 * @return Operation status.
 */
static rt_err_t timer_trigger_config(rt_clock_timer_t *timer, const struct rt_clock_timer_trigger_cfg *cfg)
{
    struct stm32_clock_timer *timer_device;
    rt_uint32_t prescaler;
    rt_uint32_t period;
    rt_err_t result;

    if (cfg->freq_hz == 0U)
    {
        return -RT_EINVAL;
    }

    if ((cfg->event != CLOCK_TIMER_TRIGGER_EVENT_UPDATE) &&
        (cfg->event != CLOCK_TIMER_TRIGGER_EVENT_COMPARE))
    {
        return -RT_EINVAL;
    }

    timer_device = (struct stm32_clock_timer *)timer;
    if (timer_device->time_device.parent.user_data == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = timer_trigger_calc(timer, cfg->freq_hz, &prescaler, &period);
    if (result != RT_EOK)
    {
        return result;
    }

    stm32_tim_enable_clock(&timer_device->tim_handle);

    switch (cfg->event)
    {
    case CLOCK_TIMER_TRIGGER_EVENT_UPDATE:
        return timer_trigger_update_config(timer_device, prescaler, period);

    case CLOCK_TIMER_TRIGGER_EVENT_COMPARE:
        return timer_trigger_compare_config(timer_device, cfg, prescaler, period);

    default:
        return -RT_EINVAL;
    }
}

/**
 * @brief Start hardware trigger output on one STM32 timer.
 * @param timer Pointer to the RT-Thread clock timer device.
 * @return Operation status.
 */
static rt_err_t timer_trigger_start(rt_clock_timer_t *timer)
{
    struct stm32_clock_timer *timer_device;
    const struct stm32_tim_compare_channel *slot;
    TIM_HandleTypeDef *tim;

    timer_device = (struct stm32_clock_timer *)timer;
    if (timer_device->time_device.parent.user_data == RT_NULL)
    {
        return -RT_EINVAL;
    }

    tim = &timer_device->tim_handle;
    tim->Instance->CR1 &= (~TIM_OPMODE_SINGLE);
    __HAL_TIM_SET_COUNTER(tim, 0);

    if (timer_device->trigger_event == CLOCK_TIMER_TRIGGER_EVENT_COMPARE)
    {
        slot = timer_trigger_compare_channel_get(timer_device->trigger_channel);
        if (slot == RT_NULL)
        {
            return -RT_EINVAL;
        }
        __HAL_TIM_CLEAR_FLAG(tim, slot->flag);
        return (HAL_TIM_OC_Start(tim, slot->channel) == HAL_OK) ? RT_EOK : -RT_ERROR;
    }

    __HAL_TIM_CLEAR_FLAG(tim, TIM_FLAG_UPDATE);
    return (HAL_TIM_Base_Start(tim) == HAL_OK) ? RT_EOK : -RT_ERROR;
}

/**
 * @brief Stop hardware trigger output on one STM32 timer.
 * @param timer Pointer to the RT-Thread clock timer device.
 * @return Operation status.
 */
static rt_err_t timer_trigger_stop(rt_clock_timer_t *timer)
{
    struct stm32_clock_timer *timer_device;
    const struct stm32_tim_compare_channel *slot;
    TIM_HandleTypeDef *tim;
    rt_err_t result;

    timer_device = (struct stm32_clock_timer *)timer;
    if (timer_device->time_device.parent.user_data == RT_NULL)
    {
        return -RT_EINVAL;
    }

    tim = &timer_device->tim_handle;

    if (timer_device->trigger_event == CLOCK_TIMER_TRIGGER_EVENT_COMPARE)
    {
        slot = timer_trigger_compare_channel_get(timer_device->trigger_channel);
        if (slot == RT_NULL)
        {
            return -RT_EINVAL;
        }
        result = (HAL_TIM_OC_Stop(tim, slot->channel) == HAL_OK) ? RT_EOK : -RT_ERROR;
        __HAL_TIM_CLEAR_FLAG(tim, slot->flag);
    }
    else
    {
        result = (HAL_TIM_Base_Stop(tim) == HAL_OK) ? RT_EOK : -RT_ERROR;
        __HAL_TIM_CLEAR_FLAG(tim, TIM_FLAG_UPDATE);
    }

    __HAL_TIM_SET_COUNTER(tim, 0);
    return result;
}

/**
 * @brief Release and deinitialize hardware trigger output on one STM32 timer.
 * @param timer Pointer to the RT-Thread clock timer device.
 * @return Operation status.
 * @note Timer trigger sources are dedicated to trigger output. Releasing a
 *       trigger source stops the timer, clears the trigger output when the HAL
 *       exposes a reset selector, and deinitializes the HAL TIM base state. It
 *       does not unregister the RT-Thread timer device object.
 */
static rt_err_t timer_trigger_release(rt_clock_timer_t *timer)
{
    struct stm32_clock_timer *timer_device;
    TIM_HandleTypeDef *tim;
    rt_err_t result = RT_EOK;

    timer_device = (struct stm32_clock_timer *)timer;
    if (timer_device->time_device.parent.user_data == RT_NULL)
    {
        return -RT_EINVAL;
    }

    tim = &timer_device->tim_handle;

    if (timer_trigger_stop(timer) != RT_EOK)
    {
        result = -RT_ERROR;
    }

#if defined(TIM_TRGO_RESET)
    TIM_MasterConfigTypeDef master = {0};
    master.MasterOutputTrigger = TIM_TRGO_RESET;
#if defined(TIM_MASTERSLAVEMODE_DISABLE)
    master.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
#endif /* defined(TIM_MASTERSLAVEMODE_DISABLE) */
    if (HAL_TIMEx_MasterConfigSynchronization(tim, &master) != HAL_OK)
    {
        result = -RT_ERROR;
    }
#endif /* defined(TIM_TRGO_RESET) */

    if (HAL_TIM_Base_DeInit(tim) != HAL_OK)
    {
        result = -RT_ERROR;
    }

    timer_device->trigger_event = CLOCK_TIMER_TRIGGER_EVENT_UPDATE;
    timer_device->trigger_channel = 0U;
    return result;
}

#endif /* defined(RT_USING_CLOCK_TIMER_TRIGGER) */

static rt_err_t timer_ctrl(rt_clock_timer_t *timer, rt_uint32_t cmd, void *arg)
{
    TIM_HandleTypeDef *tim = RT_NULL;
    rt_err_t result = -RT_ERROR;
    uint32_t pclk1_doubler, pclk2_doubler;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        rt_uint16_t val=0;

        if (arg == RT_NULL)
        {
            result = -RT_EINVAL;
            break;
        }

        /* set timer frequence */
        freq = *((rt_uint32_t *)arg);

        stm32_tim_pclkx_doubler_get(&pclk1_doubler, &pclk2_doubler);

#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
        if (0
#ifdef TIM1
        || tim->Instance == TIM1
#endif /* TIM1 */
#ifdef TIM8
        || tim->Instance == TIM8
#endif /* TIM8 */
#ifdef TIM9
        || tim->Instance == TIM9
#endif /* TIM9 */
#ifdef TIM10
        || tim->Instance == TIM10
#endif /* TIM10 */
#ifdef TIM11
        || tim->Instance == TIM11
#endif /* TIM11 */
        )
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G4)
        if (0
#ifdef TIM15
        || tim->Instance == TIM15
#endif /* TIM15 */
#ifdef TIM16
        || tim->Instance == TIM16
#endif /* TIM16 */
#ifdef TIM17
        || tim->Instance == TIM17
#endif /* TIM17 */
        )
#elif defined(SOC_SERIES_STM32WB)
        if (0
#ifdef TIM16
        || tim->Instance == TIM16
#endif /* TIM16 */
#ifdef TIM17
        || tim->Instance == TIM17
#endif /* TIM17 */
        )
#elif defined(SOC_SERIES_STM32MP1)
        if(0
#ifdef TIM14
        || tim->Instance == TIM14
#endif /* TIM14 */
#ifdef TIM16
        || tim->Instance == TIM16
#endif /* TIM16 */
#ifdef TIM17
        || tim->Instance == TIM17
#endif /* TIM17 */
        )
#elif defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32H7)
        if (0)
#else
#error "This driver has not supported this series yet!"
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
        {
#if !defined(SOC_SERIES_STM32F0) && !defined(SOC_SERIES_STM32G0)
            val = HAL_RCC_GetPCLK2Freq() * pclk2_doubler / freq;
#endif /* !defined(SOC_SERIES_STM32F0) && !defined(SOC_SERIES_STM32G0) */
        }
        else
        {
            val = HAL_RCC_GetPCLK1Freq() * pclk1_doubler / freq;
        }
        __HAL_TIM_SET_PRESCALER(tim, val - 1);

        /* Update frequency value */
        tim->Instance->EGR |= TIM_EVENTSOURCE_UPDATE;

        result = RT_EOK;
    }
    break;
#if defined(RT_USING_CLOCK_TIMER_TRIGGER)
    case CLOCK_TIMER_CTRL_TRIGGER_CONFIG:
    {
        if (arg == RT_NULL)
        {
            result = -RT_EINVAL;
            break;
        }
        result = timer_trigger_config(timer, (const struct rt_clock_timer_trigger_cfg *)arg);
    }
    break;
    case CLOCK_TIMER_CTRL_TRIGGER_START:
    {
        result = timer_trigger_start(timer);
    }
    break;
    case CLOCK_TIMER_CTRL_TRIGGER_STOP:
    {
        result = timer_trigger_stop(timer);
    }
    break;
    case CLOCK_TIMER_CTRL_TRIGGER_RELEASE:
    {
        result = timer_trigger_release(timer);
    }
    break;
#endif /* defined(RT_USING_CLOCK_TIMER_TRIGGER) */
    default:
    {
        result = -RT_EINVAL;
    }
    break;
    }

    return result;
}

static rt_uint32_t timer_counter_get(rt_clock_timer_t *timer)
{
    TIM_HandleTypeDef *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (TIM_HandleTypeDef *)timer->parent.user_data;

    return tim->Instance->CNT;
}

static const struct rt_clock_timer_info _info = TIM_DEV_INFO_CONFIG;

static const struct rt_clock_timer_ops _ops =
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
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM2_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#if defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx)
#if defined(BSP_USING_TIM3) || defined(BSP_USING_TIM4)
void TIM3_TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
#ifdef BSP_USING_TIM3
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM3_INDEX].tim_handle);
#endif
#ifdef BSP_USING_TIM4
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM4_INDEX].tim_handle);
#endif
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#else
#ifdef BSP_USING_TIM3
void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM3_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM4
void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM4_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif
#ifdef BSP_USING_TIM5
void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM5_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM6
void TIM6_DAC_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM6_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM7
void TIM7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM7_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM8
void TIM8_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM8_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM11
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM11_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM13
void TIM8_UP_TIM13_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM13_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM14
#if defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
    void TIM8_TRG_COM_TIM14_IRQHandler(void)
#elif defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32MP1)
    void TIM14_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM14_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM15
void TIM1_BRK_TIM15_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM15_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM16
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WB)|| defined(SOC_SERIES_STM32G4)
    void TIM1_UP_TIM16_IRQHandler(void)
#elif defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32MP1)
    void TIM16_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM16_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_TIM17
#if defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32G4)
    void TIM1_TRG_COM_TIM17_IRQHandler(void)
#elif defined(SOC_SERIES_STM32F0) || defined(SOC_SERIES_STM32MP1)
    void TIM17_IRQHandler(void)
#endif
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_clock_timer_obj[TIM17_INDEX].tim_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
#ifdef BSP_USING_TIM2
    if (htim->Instance == TIM2)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM2_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM3
    if (htim->Instance == TIM3)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM3_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM4
    if (htim->Instance == TIM4)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM4_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM5
    if (htim->Instance == TIM5)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM5_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM6
    if (htim->Instance == TIM6)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM6_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM7
    if (htim->Instance == TIM7)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM7_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM8
    if (htim->Instance == TIM8)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM8_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM11
    if (htim->Instance == TIM11)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM11_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM13
    if (htim->Instance == TIM13)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM13_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM14
    if (htim->Instance == TIM14)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM14_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM15
    if (htim->Instance == TIM15)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM15_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM16
    if (htim->Instance == TIM16)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM16_INDEX].time_device);
    }
#endif
#ifdef BSP_USING_TIM17
    if (htim->Instance == TIM17)
    {
        rt_clock_timer_isr(&stm32_clock_timer_obj[TIM17_INDEX].time_device);
    }
#endif
}

static int stm32_clock_timer_init(void)
{
    rt_uint32_t i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(stm32_clock_timer_obj) / sizeof(stm32_clock_timer_obj[0]); i++)
    {
        stm32_clock_timer_obj[i].time_device.info = &_info;
        stm32_clock_timer_obj[i].time_device.ops  = &_ops;
        if (rt_clock_timer_register(&stm32_clock_timer_obj[i].time_device,
            stm32_clock_timer_obj[i].name, &stm32_clock_timer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", stm32_clock_timer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", stm32_clock_timer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(stm32_clock_timer_init);

#endif /* BSP_USING_TIM */
