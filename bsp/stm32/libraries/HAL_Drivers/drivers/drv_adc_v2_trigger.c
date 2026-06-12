/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-24     wdfk-prog    add STM32 ADC V2 timer trigger backend
 */

/**
 * @file drv_adc_v2_trigger.c
 * @brief STM32 ADC V2 trigger selector backend.
 */
#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)

#include "drv_config.h"
#include "drv_adc_v2_private.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4)

#define DRV_DEBUG
#define LOG_TAG "drv.adc"
#include <drv_log.h>

#if defined(STM32_ADC_USING_TRIGGER)
/** @brief Invalid trigger selector array slot. */
#define STM32_ADC_TRIGGER_SELECTOR_NONE { 0U, RT_FALSE }

/** @brief Valid trigger selector array slot initializer. */
#define STM32_ADC_TRIGGER_SELECTOR(_selector) { (_selector), RT_TRUE }

/** @brief Maximum compare channel index encoded by the STM32 ADC trigger tables. */
#define STM32_ADC_TIMER_COMPARE_CHANNEL_MAX 4U

/**
 * @brief STM32 ADC trigger selector slot.
 */
struct stm32_adc_trigger_selector
{
    rt_uint32_t selector;  /**< HAL ADC external trigger selector. */
    rt_bool_t valid;       /**< Whether selector is valid for this slot. */
};

/**
 * @brief Encode one ADC trigger edge as STM32 HAL external trigger edge.
 * @param edge ADC framework trigger edge.
 * @param hal_edge Pointer to the HAL edge selector output.
 * @return Operation status.
 */
static rt_err_t stm32_adc_trigger_edge_encode(enum rt_adc_trigger_edge edge, rt_uint32_t *hal_edge)
{
    if (hal_edge == RT_NULL)
    {
        return -RT_EINVAL;
    }

#if defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE)
    switch (edge)
    {
    case RT_ADC_TRIGGER_EDGE_NONE:
#if defined(ADC_EXTERNALTRIGCONVEDGE_NONE)
        *hal_edge = ADC_EXTERNALTRIGCONVEDGE_NONE;
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_NONE) */

    case RT_ADC_TRIGGER_EDGE_RISING:
#if defined(ADC_EXTERNALTRIGCONVEDGE_RISING)
        *hal_edge = ADC_EXTERNALTRIGCONVEDGE_RISING;
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_RISING) */

    case RT_ADC_TRIGGER_EDGE_FALLING:
#if defined(ADC_EXTERNALTRIGCONVEDGE_FALLING)
        *hal_edge = ADC_EXTERNALTRIGCONVEDGE_FALLING;
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_FALLING) */

    case RT_ADC_TRIGGER_EDGE_BOTH:
#if defined(ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING)
        *hal_edge = ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING;
        return RT_EOK;
#else
        return -RT_ENOSYS;
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING) */

    default:
        return -RT_EINVAL;
    }
#else
    if ((edge != RT_ADC_TRIGGER_EDGE_NONE) && (edge != RT_ADC_TRIGGER_EDGE_RISING))
    {
        return -RT_ENOSYS;
    }

    *hal_edge = 0U;
    return RT_EOK;
#endif /* defined(STM32_ADC_HAS_INIT_EXT_TRIG_EDGE) */
}

#if defined(STM32_ADC_USING_TIMER_TRIGGER)
/**
 * @brief STM32 timer to ADC trigger selector mapping entry.
 */
struct stm32_adc_timer_trigger_map
{
    TIM_TypeDef *instance;                    /**< TIM hardware instance. */
    rt_uint32_t adc_instance_mask;            /**< ADC instances allowed to use this trigger. */
    struct stm32_adc_trigger_selector update; /**< TIM update/TRGO trigger selector. */

    /** TIM compare trigger selectors indexed by 1-based channel number. */
    struct stm32_adc_trigger_selector compare[STM32_ADC_TIMER_COMPARE_CHANNEL_MAX + 1U];
};

/**
 * @brief ADC timer trigger selector table.
 *
 * @note Compare selectors are intentionally encoded with array indexes so
 *       channel 1 maps to compare[1], channel 2 maps to compare[2], etc.
 */
static const struct stm32_adc_timer_trigger_map stm32_adc_timer_trigger_table[] = {
#if defined(TIM1)
    {
        TIM1,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T1_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T1_TRGO),
#elif defined(ADC_EXTERNALTRIG_T1_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T1_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T1_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T1_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T1_CC1),
#elif defined(ADC_EXTERNALTRIG_T1_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T1_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T1_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T1_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T1_CC2),
#elif defined(ADC_EXTERNALTRIG_T1_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T1_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T1_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T1_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T1_CC3),
#elif defined(ADC_EXTERNALTRIG_T1_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T1_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T1_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T1_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T1_CC4),
#elif defined(ADC_EXTERNALTRIG_T1_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T1_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T1_CC4) */
        },
    },
#endif /* defined(TIM1) */
#if defined(TIM2)
    {
        TIM2,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T2_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T2_TRGO),
#elif defined(ADC_EXTERNALTRIG_T2_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T2_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T2_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T2_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T2_CC1),
#elif defined(ADC_EXTERNALTRIG_T2_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T2_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T2_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T2_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T2_CC2),
#elif defined(ADC_EXTERNALTRIG_T2_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T2_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T2_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T2_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T2_CC3),
#elif defined(ADC_EXTERNALTRIG_T2_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T2_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T2_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T2_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T2_CC4),
#elif defined(ADC_EXTERNALTRIG_T2_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T2_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T2_CC4) */
        },
    },
#endif /* defined(TIM2) */
#if defined(TIM3)
    {
        TIM3,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T3_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T3_TRGO),
#elif defined(ADC_EXTERNALTRIG_T3_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T3_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T3_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T3_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T3_CC1),
#elif defined(ADC_EXTERNALTRIG_T3_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T3_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T3_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T3_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T3_CC2),
#elif defined(ADC_EXTERNALTRIG_T3_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T3_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T3_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T3_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T3_CC3),
#elif defined(ADC_EXTERNALTRIG_T3_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T3_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T3_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T3_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T3_CC4),
#elif defined(ADC_EXTERNALTRIG_T3_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T3_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T3_CC4) */
        },
    },
#endif /* defined(TIM3) */
#if defined(TIM4)
    {
        TIM4,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T4_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T4_TRGO),
#elif defined(ADC_EXTERNALTRIG_T4_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T4_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T4_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T4_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T4_CC1),
#elif defined(ADC_EXTERNALTRIG_T4_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T4_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T4_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T4_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T4_CC2),
#elif defined(ADC_EXTERNALTRIG_T4_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T4_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T4_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T4_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T4_CC3),
#elif defined(ADC_EXTERNALTRIG_T4_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T4_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T4_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T4_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T4_CC4),
#elif defined(ADC_EXTERNALTRIG_T4_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T4_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T4_CC4) */
        },
    },
#endif /* defined(TIM4) */
#if defined(TIM5)
    {
        TIM5,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T5_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T5_TRGO),
#elif defined(ADC_EXTERNALTRIG_T5_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T5_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T5_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T5_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T5_CC1),
#elif defined(ADC_EXTERNALTRIG_T5_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T5_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T5_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T5_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T5_CC2),
#elif defined(ADC_EXTERNALTRIG_T5_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T5_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T5_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T5_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T5_CC3),
#elif defined(ADC_EXTERNALTRIG_T5_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T5_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T5_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T5_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T5_CC4),
#elif defined(ADC_EXTERNALTRIG_T5_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T5_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T5_CC4) */
        },
    },
#endif /* defined(TIM5) */
#if defined(TIM6)
    {
        TIM6,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T6_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T6_TRGO),
#elif defined(ADC_EXTERNALTRIG_T6_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T6_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T6_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T6_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T6_CC1),
#elif defined(ADC_EXTERNALTRIG_T6_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T6_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T6_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T6_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T6_CC2),
#elif defined(ADC_EXTERNALTRIG_T6_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T6_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T6_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T6_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T6_CC3),
#elif defined(ADC_EXTERNALTRIG_T6_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T6_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T6_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T6_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T6_CC4),
#elif defined(ADC_EXTERNALTRIG_T6_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T6_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T6_CC4) */
        },
    },
#endif /* defined(TIM6) */
#if defined(TIM7)
    {
        TIM7,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T7_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T7_TRGO),
#elif defined(ADC_EXTERNALTRIG_T7_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T7_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T7_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T7_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T7_CC1),
#elif defined(ADC_EXTERNALTRIG_T7_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T7_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T7_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T7_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T7_CC2),
#elif defined(ADC_EXTERNALTRIG_T7_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T7_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T7_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T7_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T7_CC3),
#elif defined(ADC_EXTERNALTRIG_T7_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T7_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T7_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T7_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T7_CC4),
#elif defined(ADC_EXTERNALTRIG_T7_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T7_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T7_CC4) */
        },
    },
#endif /* defined(TIM7) */
#if defined(TIM8)
    {
        TIM8,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T8_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T8_TRGO),
#elif defined(ADC_EXTERNALTRIG_T8_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T8_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T8_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T8_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T8_CC1),
#elif defined(ADC_EXTERNALTRIG_T8_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T8_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T8_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T8_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T8_CC2),
#elif defined(ADC_EXTERNALTRIG_T8_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T8_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T8_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T8_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T8_CC3),
#elif defined(ADC_EXTERNALTRIG_T8_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T8_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T8_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T8_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T8_CC4),
#elif defined(ADC_EXTERNALTRIG_T8_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T8_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T8_CC4) */
        },
    },
#endif /* defined(TIM8) */
#if defined(TIM9)
    {
        TIM9,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T9_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T9_TRGO),
#elif defined(ADC_EXTERNALTRIG_T9_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T9_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T9_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T9_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T9_CC1),
#elif defined(ADC_EXTERNALTRIG_T9_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T9_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T9_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T9_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T9_CC2),
#elif defined(ADC_EXTERNALTRIG_T9_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T9_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T9_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T9_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T9_CC3),
#elif defined(ADC_EXTERNALTRIG_T9_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T9_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T9_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T9_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T9_CC4),
#elif defined(ADC_EXTERNALTRIG_T9_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T9_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T9_CC4) */
        },
    },
#endif /* defined(TIM9) */
#if defined(TIM10)
    {
        TIM10,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T10_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T10_TRGO),
#elif defined(ADC_EXTERNALTRIG_T10_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T10_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T10_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T10_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T10_CC1),
#elif defined(ADC_EXTERNALTRIG_T10_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T10_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T10_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T10_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T10_CC2),
#elif defined(ADC_EXTERNALTRIG_T10_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T10_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T10_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T10_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T10_CC3),
#elif defined(ADC_EXTERNALTRIG_T10_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T10_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T10_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T10_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T10_CC4),
#elif defined(ADC_EXTERNALTRIG_T10_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T10_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T10_CC4) */
        },
    },
#endif /* defined(TIM10) */
#if defined(TIM11)
    {
        TIM11,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T11_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T11_TRGO),
#elif defined(ADC_EXTERNALTRIG_T11_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T11_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T11_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T11_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T11_CC1),
#elif defined(ADC_EXTERNALTRIG_T11_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T11_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T11_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T11_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T11_CC2),
#elif defined(ADC_EXTERNALTRIG_T11_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T11_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T11_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T11_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T11_CC3),
#elif defined(ADC_EXTERNALTRIG_T11_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T11_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T11_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T11_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T11_CC4),
#elif defined(ADC_EXTERNALTRIG_T11_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T11_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T11_CC4) */
        },
    },
#endif /* defined(TIM11) */
#if defined(TIM12)
    {
        TIM12,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T12_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T12_TRGO),
#elif defined(ADC_EXTERNALTRIG_T12_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T12_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T12_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T12_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T12_CC1),
#elif defined(ADC_EXTERNALTRIG_T12_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T12_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T12_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T12_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T12_CC2),
#elif defined(ADC_EXTERNALTRIG_T12_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T12_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T12_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T12_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T12_CC3),
#elif defined(ADC_EXTERNALTRIG_T12_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T12_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T12_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T12_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T12_CC4),
#elif defined(ADC_EXTERNALTRIG_T12_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T12_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T12_CC4) */
        },
    },
#endif /* defined(TIM12) */
#if defined(TIM13)
    {
        TIM13,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T13_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T13_TRGO),
#elif defined(ADC_EXTERNALTRIG_T13_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T13_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T13_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T13_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T13_CC1),
#elif defined(ADC_EXTERNALTRIG_T13_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T13_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T13_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T13_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T13_CC2),
#elif defined(ADC_EXTERNALTRIG_T13_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T13_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T13_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T13_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T13_CC3),
#elif defined(ADC_EXTERNALTRIG_T13_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T13_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T13_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T13_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T13_CC4),
#elif defined(ADC_EXTERNALTRIG_T13_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T13_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T13_CC4) */
        },
    },
#endif /* defined(TIM13) */
#if defined(TIM14)
    {
        TIM14,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T14_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T14_TRGO),
#elif defined(ADC_EXTERNALTRIG_T14_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T14_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T14_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T14_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T14_CC1),
#elif defined(ADC_EXTERNALTRIG_T14_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T14_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T14_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T14_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T14_CC2),
#elif defined(ADC_EXTERNALTRIG_T14_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T14_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T14_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T14_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T14_CC3),
#elif defined(ADC_EXTERNALTRIG_T14_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T14_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T14_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T14_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T14_CC4),
#elif defined(ADC_EXTERNALTRIG_T14_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T14_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T14_CC4) */
        },
    },
#endif /* defined(TIM14) */
#if defined(TIM15)
    {
        TIM15,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T15_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T15_TRGO),
#elif defined(ADC_EXTERNALTRIG_T15_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T15_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T15_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T15_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T15_CC1),
#elif defined(ADC_EXTERNALTRIG_T15_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T15_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T15_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T15_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T15_CC2),
#elif defined(ADC_EXTERNALTRIG_T15_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T15_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T15_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T15_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T15_CC3),
#elif defined(ADC_EXTERNALTRIG_T15_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T15_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T15_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T15_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T15_CC4),
#elif defined(ADC_EXTERNALTRIG_T15_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T15_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T15_CC4) */
        },
    },
#endif /* defined(TIM15) */
#if defined(TIM16)
    {
        TIM16,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T16_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T16_TRGO),
#elif defined(ADC_EXTERNALTRIG_T16_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T16_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T16_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T16_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T16_CC1),
#elif defined(ADC_EXTERNALTRIG_T16_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T16_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T16_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T16_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T16_CC2),
#elif defined(ADC_EXTERNALTRIG_T16_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T16_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T16_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T16_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T16_CC3),
#elif defined(ADC_EXTERNALTRIG_T16_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T16_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T16_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T16_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T16_CC4),
#elif defined(ADC_EXTERNALTRIG_T16_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T16_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T16_CC4) */
        },
    },
#endif /* defined(TIM16) */
#if defined(TIM17)
    {
        TIM17,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T17_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T17_TRGO),
#elif defined(ADC_EXTERNALTRIG_T17_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T17_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T17_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T17_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T17_CC1),
#elif defined(ADC_EXTERNALTRIG_T17_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T17_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T17_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T17_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T17_CC2),
#elif defined(ADC_EXTERNALTRIG_T17_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T17_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T17_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T17_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T17_CC3),
#elif defined(ADC_EXTERNALTRIG_T17_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T17_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T17_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T17_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T17_CC4),
#elif defined(ADC_EXTERNALTRIG_T17_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T17_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T17_CC4) */
        },
    },
#endif /* defined(TIM17) */
#if defined(TIM18)
{
    TIM18,
    STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T18_TRGO)
    STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T18_TRGO),
#elif defined(ADC_EXTERNALTRIG_T18_TRGO)
    STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T18_TRGO),
#else
    STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T18_TRGO) */
    {
#if defined(ADC_EXTERNALTRIGCONV_T18_CC1)
        [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T18_CC1),
#elif defined(ADC_EXTERNALTRIG_T18_CC1)
        [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T18_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T18_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T18_CC2)
        [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T18_CC2),
#elif defined(ADC_EXTERNALTRIG_T18_CC2)
        [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T18_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T18_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T18_CC3)
        [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T18_CC3),
#elif defined(ADC_EXTERNALTRIG_T18_CC3)
        [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T18_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T18_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T18_CC4)
        [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T18_CC4),
#elif defined(ADC_EXTERNALTRIG_T18_CC4)
        [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T18_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T18_CC4) */
    },
},
#endif /* defined(TIM18) */
#if defined(TIM19)
{
    TIM19,
    STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T19_TRGO)
    STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T19_TRGO),
#elif defined(ADC_EXTERNALTRIG_T19_TRGO)
    STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T19_TRGO),
#else
    STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T19_TRGO) */
    {
#if defined(ADC_EXTERNALTRIGCONV_T19_CC1)
        [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T19_CC1),
#elif defined(ADC_EXTERNALTRIG_T19_CC1)
        [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T19_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T19_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T19_CC2)
        [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T19_CC2),
#elif defined(ADC_EXTERNALTRIG_T19_CC2)
        [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T19_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T19_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T19_CC3)
        [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T19_CC3),
#elif defined(ADC_EXTERNALTRIG_T19_CC3)
        [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T19_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T19_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T19_CC4)
        [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T19_CC4),
#elif defined(ADC_EXTERNALTRIG_T19_CC4)
        [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T19_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T19_CC4) */
    },
},
#endif /* defined(TIM19) */
#if defined(TIM20)
    {
        TIM20,
        STM32_ADC_INSTANCE_MASK_ALL,
#if defined(ADC_EXTERNALTRIGCONV_T20_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T20_TRGO),
#elif defined(ADC_EXTERNALTRIG_T20_TRGO)
        STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T20_TRGO),
#else
        STM32_ADC_TRIGGER_SELECTOR_NONE,
#endif /* defined(ADC_EXTERNALTRIGCONV_T20_TRGO) */
        {
#if defined(ADC_EXTERNALTRIGCONV_T20_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T20_CC1),
#elif defined(ADC_EXTERNALTRIG_T20_CC1)
            [1] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T20_CC1),
#endif /* defined(ADC_EXTERNALTRIGCONV_T20_CC1) */
#if defined(ADC_EXTERNALTRIGCONV_T20_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T20_CC2),
#elif defined(ADC_EXTERNALTRIG_T20_CC2)
            [2] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T20_CC2),
#endif /* defined(ADC_EXTERNALTRIGCONV_T20_CC2) */
#if defined(ADC_EXTERNALTRIGCONV_T20_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T20_CC3),
#elif defined(ADC_EXTERNALTRIG_T20_CC3)
            [3] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T20_CC3),
#endif /* defined(ADC_EXTERNALTRIGCONV_T20_CC3) */
#if defined(ADC_EXTERNALTRIGCONV_T20_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_T20_CC4),
#elif defined(ADC_EXTERNALTRIG_T20_CC4)
            [4] = STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_T20_CC4),
#endif /* defined(ADC_EXTERNALTRIGCONV_T20_CC4) */
        },
    },
#endif /* defined(TIM20) */
};

/**
 * @brief Resolve an ADC external trigger selector from a TIM event.
 * @param adc Pointer to the STM32 ADC device object.
 * @param instance TIM hardware instance.
 * @param channel Timer compare channel, or 0 for update/TRGO.
 * @param selector Pointer to the output HAL ADC trigger selector.
 * @return RT_TRUE if the timer event is supported by this HAL build and ADC instance.
 */
static rt_bool_t stm32_adc_timer_trigger_selector_get(struct stm32_adc *adc, TIM_TypeDef *instance,
                                                      rt_uint16_t channel, rt_uint32_t *selector)
{
    rt_size_t index;

    for (index = 0; index < RT_ARRAY_SIZE(stm32_adc_timer_trigger_table); index++)
    {
        const struct stm32_adc_timer_trigger_map *map = &stm32_adc_timer_trigger_table[index];
        const struct stm32_adc_trigger_selector *slot;

        if (map->instance != instance)
        {
            continue;
        }

        if (stm32_adc_instance_match(adc->handle.Instance, map->adc_instance_mask) != RT_TRUE)
        {
            return RT_FALSE;
        }

        if (channel == 0U)
        {
            slot = &map->update;
        }
        else
        {
            if (channel > STM32_ADC_TIMER_COMPARE_CHANNEL_MAX)
            {
                return RT_FALSE;
            }
            slot = &map->compare[channel];
        }

        if (slot->valid != RT_TRUE)
        {
            return RT_FALSE;
        }

        *selector = slot->selector;
        return RT_TRUE;
    }

    return RT_FALSE;
}

/**
 * @brief Encode one STM32 ADC timer trigger configuration.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the ADC trigger configuration object.
 * @param selector Pointer to the output HAL ADC trigger selector.
 * @param edge Pointer to the output HAL ADC trigger edge selector.
 * @return Operation status.
 */
static rt_err_t stm32_adc_encode_timer_trigger(struct stm32_adc *adc, const struct rt_adc_trigger_cfg *cfg,
                                               rt_uint32_t *selector, rt_uint32_t *edge)
{
    TIM_HandleTypeDef *tim;
    rt_uint16_t channel;
    rt_err_t result;

    if (cfg->event.timer.timer == RT_NULL)
    {
        LOG_E("%s timer trigger source is null", adc->name);
        return -RT_EINVAL;
    }

    tim = (TIM_HandleTypeDef *)cfg->event.timer.timer->user_data;
    if (tim == RT_NULL)
    {
        LOG_E("%s timer trigger source has no TIM handle", adc->name);
        return -RT_EINVAL;
    }

    switch (cfg->type)
    {
    case RT_ADC_TRIGGER_TIMER_UPDATE:
        channel = 0U;
        break;

    case RT_ADC_TRIGGER_TIMER_COMPARE:
        channel = cfg->event.timer.channel;
        if (channel == 0U)
        {
            LOG_E("%s timer compare trigger channel is invalid", adc->name);
            return -RT_EINVAL;
        }
        break;

    default:
        return -RT_EINVAL;
    }

    if (stm32_adc_timer_trigger_selector_get(adc, tim->Instance, channel, selector) != RT_TRUE)
    {
        LOG_E("%s timer trigger source unsupported", adc->name);
        return -RT_ENOSYS;
    }

    result = stm32_adc_trigger_edge_encode(RT_ADC_TRIGGER_EDGE_RISING, edge);
    return result;
}
#endif /* defined(STM32_ADC_USING_TIMER_TRIGGER) */

#if defined(STM32_ADC_USING_ANALOG_COMPARE_TRIGGER)
/**
 * @brief STM32 comparator to ADC trigger selector table entry.
 */
struct stm32_adc_compare_trigger_slot
{
    rt_uint32_t adc_instance_mask;              /**< ADC instances allowed to use this comparator trigger. */
    struct stm32_adc_trigger_selector trigger;  /**< COMPx_OUT trigger selector. */
};

/**
 * @brief ADC analog comparator trigger selector table indexed by comparator channel.
 */
static const struct stm32_adc_compare_trigger_slot stm32_adc_compare_trigger_table[] = {
    [0] = { 0U, STM32_ADC_TRIGGER_SELECTOR_NONE },
#if defined(ADC_EXTERNALTRIGCONV_COMP1_OUT)
    [1] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP1_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP1_OUT)
    [1] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP1_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP1)
    [1] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP1) },
#elif defined(ADC_EXTERNALTRIG_COMP1)
    [1] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP1) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP1_OUT) */
#if defined(ADC_EXTERNALTRIGCONV_COMP2_OUT)
    [2] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP2_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP2_OUT)
    [2] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP2_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP2)
    [2] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP2) },
#elif defined(ADC_EXTERNALTRIG_COMP2)
    [2] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP2) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP2_OUT) */
#if defined(ADC_EXTERNALTRIGCONV_COMP3_OUT)
    [3] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP3_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP3_OUT)
    [3] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP3_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP3)
    [3] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP3) },
#elif defined(ADC_EXTERNALTRIG_COMP3)
    [3] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP3) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP3_OUT) */
#if defined(ADC_EXTERNALTRIGCONV_COMP4_OUT)
    [4] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP4_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP4_OUT)
    [4] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP4_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP4)
    [4] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP4) },
#elif defined(ADC_EXTERNALTRIG_COMP4)
    [4] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP4) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP4_OUT) */
#if defined(ADC_EXTERNALTRIGCONV_COMP5_OUT)
    [5] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP5_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP5_OUT)
    [5] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP5_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP5)
    [5] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP5) },
#elif defined(ADC_EXTERNALTRIG_COMP5)
    [5] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP5) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP5_OUT) */
#if defined(ADC_EXTERNALTRIGCONV_COMP6_OUT)
    [6] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP6_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP6_OUT)
    [6] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP6_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP6)
    [6] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP6) },
#elif defined(ADC_EXTERNALTRIG_COMP6)
    [6] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP6) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP6_OUT) */
#if defined(ADC_EXTERNALTRIGCONV_COMP7_OUT)
    [7] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP7_OUT) },
#elif defined(ADC_EXTERNALTRIG_COMP7_OUT)
    [7] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP7_OUT) },
#elif defined(ADC_EXTERNALTRIGCONV_COMP7)
    [7] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIGCONV_COMP7) },
#elif defined(ADC_EXTERNALTRIG_COMP7)
    [7] = { STM32_ADC_INSTANCE_MASK_ALL, STM32_ADC_TRIGGER_SELECTOR(ADC_EXTERNALTRIG_COMP7) },
#endif /* defined(ADC_EXTERNALTRIGCONV_COMP7_OUT) */
};

/**
 * @brief Resolve an ADC external trigger selector from a comparator channel.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Comparator channel.
 * @param selector Pointer to the output HAL ADC trigger selector.
 * @return RT_TRUE if the comparator channel is supported by this HAL build and ADC instance.
 */
static rt_bool_t stm32_adc_compare_trigger_selector_get(struct stm32_adc *adc, rt_uint16_t channel, rt_uint32_t *selector)
{
    const struct stm32_adc_compare_trigger_slot *slot;

    if (channel >= RT_ARRAY_SIZE(stm32_adc_compare_trigger_table))
    {
        return RT_FALSE;
    }

    slot = &stm32_adc_compare_trigger_table[channel];
    if (slot->trigger.valid != RT_TRUE)
    {
        return RT_FALSE;
    }

    if (stm32_adc_instance_match(adc->handle.Instance, slot->adc_instance_mask) != RT_TRUE)
    {
        return RT_FALSE;
    }

    *selector = slot->trigger.selector;
    return RT_TRUE;
}

/**
 * @brief Encode one STM32 ADC analog comparator trigger configuration.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the ADC trigger configuration object.
 * @param selector Pointer to the output HAL ADC trigger selector.
 * @param edge Pointer to the output HAL ADC trigger edge selector.
 * @return Operation status.
 */
static rt_err_t stm32_adc_encode_compare_trigger(struct stm32_adc *adc, const struct rt_adc_trigger_cfg *cfg,
                                                 rt_uint32_t *selector, rt_uint32_t *edge)
{
    rt_err_t result;

    if ((cfg->event.compare.channel == 0U) ||
        (cfg->event.compare.edge == RT_ADC_TRIGGER_EDGE_NONE))
    {
        LOG_E("%s analog compare trigger config invalid", adc->name);
        return -RT_EINVAL;
    }

    if (stm32_adc_compare_trigger_selector_get(adc, cfg->event.compare.channel, selector) != RT_TRUE)
    {
        LOG_E("%s analog compare trigger source unsupported", adc->name);
        return -RT_ENOSYS;
    }

    result = stm32_adc_trigger_edge_encode(cfg->event.compare.edge, edge);
    return result;
}
#endif /* defined(STM32_ADC_USING_ANALOG_COMPARE_TRIGGER) */

/**
 * @brief Encode one STM32 ADC trigger configuration into HAL selector fields.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the ADC trigger configuration object, or RT_NULL for software/default trigger.
 * @param selector Pointer to the output HAL ADC trigger selector.
 * @param edge Pointer to the output HAL ADC trigger edge selector.
 * @return Operation status.
 */
static rt_err_t stm32_adc_encode_trigger(struct stm32_adc *adc, const struct rt_adc_trigger_cfg *cfg,
                                         rt_uint32_t *selector, rt_uint32_t *edge)
{
    rt_err_t result;

    if (cfg == RT_NULL)
    {
        *selector = ADC_SOFTWARE_START;
        return stm32_adc_trigger_edge_encode(RT_ADC_TRIGGER_EDGE_NONE, edge);
    }

    switch (cfg->type)
    {
#if defined(STM32_ADC_USING_TIMER_TRIGGER)
    case RT_ADC_TRIGGER_TIMER_UPDATE:
    case RT_ADC_TRIGGER_TIMER_COMPARE:
        result = stm32_adc_encode_timer_trigger(adc, cfg, selector, edge);
        break;
#endif /* defined(STM32_ADC_USING_TIMER_TRIGGER) */

#if defined(STM32_ADC_USING_ANALOG_COMPARE_TRIGGER)
    case RT_ADC_TRIGGER_ANALOG_COMPARE:
        result = stm32_adc_encode_compare_trigger(adc, cfg, selector, edge);
        break;
#endif /* defined(STM32_ADC_USING_ANALOG_COMPARE_TRIGGER) */


    default:
        LOG_E("%s trigger type unsupported: %d", adc->name, (int)cfg->type);
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

/**
 * @brief Resolve STM32 ADC trigger selector fields.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the ADC trigger configuration, or RT_NULL for software start.
 * @param fields Pointer to the output STM32 trigger fields.
 * @return Operation status.
 */
rt_err_t stm32_adc_trigger_fields_get(struct stm32_adc *adc, const struct rt_adc_trigger_cfg *cfg,
                                      struct stm32_adc_trigger_fields *fields)
{
    return stm32_adc_encode_trigger(adc, cfg, &fields->selector, &fields->edge);
}

/**
 * @brief Preconfigure STM32 ADC trigger selector state for the next stream configuration.
 * @param device Pointer to the ADC framework device object.
 * @param cfg Pointer to the ADC trigger configuration, or RT_NULL for software start.
 * @return Operation status.
 */
rt_err_t stm32_adc_trigger_prepare(struct rt_adc_device *device, const struct rt_adc_trigger_cfg *cfg)
{
    struct stm32_adc *adc;
    struct stm32_adc_trigger_fields fields;
    rt_err_t result;

    adc = (struct stm32_adc *)device->parent.user_data;
    if (adc == RT_NULL)
    {
        return -RT_EINVAL;
    }

    result = stm32_adc_trigger_fields_get(adc, cfg, &fields);
    if (result != RT_EOK)
    {
        adc->prepared_trigger_valid = RT_FALSE;
        return result;
    }

    adc->prepared_trigger = fields;
    adc->prepared_trigger_valid = RT_TRUE;
    return RT_EOK;
}
#endif /* defined(STM32_ADC_USING_TRIGGER) */

#endif /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4) */

#endif /* defined(RT_USING_ADC_V2) */
