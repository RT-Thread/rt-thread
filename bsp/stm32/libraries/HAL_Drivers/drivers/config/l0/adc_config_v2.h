/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-27     wdfk-prog    add stm32l0 adc v2 configuration
 */

/**
 * @file adc_config_v2.h
 * @brief STM32L0 ADC V2 configuration defaults.
 */

#ifndef __ADC_CONFIG_V2_H__
#define __ADC_CONFIG_V2_H__

#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)

#include <rtthread.h>
#include <drivers/adc_v2.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @brief Default ADC clock prescaler for STM32L0. */
#if defined(ADC_CLOCK_SYNC_PCLK_DIV4)
#define ADC_DEFAULT_CLOCK_PRESCALER ADC_CLOCK_SYNC_PCLK_DIV4
#elif defined(ADC_CLOCK_ASYNC_DIV1)
#define ADC_DEFAULT_CLOCK_PRESCALER ADC_CLOCK_ASYNC_DIV1
#endif /* defined(ADC_CLOCK_SYNC_PCLK_DIV4) */

/** @brief Default ADC data alignment for STM32L0. */
#if defined(ADC_DATAALIGN_RIGHT)
#define ADC_DEFAULT_DATA_ALIGN ADC_DATAALIGN_RIGHT
#else
#define ADC_DEFAULT_DATA_ALIGN 0U
#endif /* defined(ADC_DATAALIGN_RIGHT) */

/** @brief Default ADC resolution for STM32L0. */
#ifdef ADC_RESOLUTION_12B
#define ADC_DEFAULT_RESOLUTION ADC_RESOLUTION_12B
#else
#define ADC_DEFAULT_RESOLUTION 0U
#endif /* ADC_RESOLUTION_12B */

/** @brief Default ADC sampling time for STM32L0. */
#if defined(ADC_SAMPLETIME_160CYCLES_5)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_160CYCLES_5
#elif defined(ADC_SAMPLETIME_79CYCLES_5)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_79CYCLES_5
#elif defined(ADC_SAMPLETIME_39CYCLES_5)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_39CYCLES_5
#else
#define ADC_DEFAULT_SAMPLING_TIME 0U
#endif /* defined(ADC_SAMPLETIME_160CYCLES_5) */


/** @brief Maximum regular sequence length supported by the STM32L0 driver. */
#define STM32_ADC_MAX_SEQUENCE 16

/** @brief Whether sequence mode is compiled in. */
#define STM32_ADC_USING_SEQUENCE 1


/* ADC V2 internal-channel routing policy for this STM32 series. */
/** @brief STM32L0 legacy internal ADC source logical channel overrides. */
#if !defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB) && !defined(__LL_ADC_CHANNEL_TO_DECIMAL_NB)
#define STM32_ADC_TEMP_LOGICAL_OVERRIDE 16
#define STM32_ADC_VREF_LOGICAL_OVERRIDE 17
#define STM32_ADC_VBAT_LOGICAL_OVERRIDE 18
#endif /* !defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB) && !defined(__LL_ADC_CHANNEL_TO_DECIMAL_NB) */


/* ADC V2 HAL feature policy for this STM32 series. */
#if defined(ADC_DEFAULT_DATA_ALIGN)
#define STM32_ADC_HAS_INIT_DATA_ALIGN 1
#endif /* defined(ADC_DEFAULT_DATA_ALIGN) */

#if defined(ADC_EXTERNALTRIGCONVEDGE_NONE)
#define STM32_ADC_HAS_INIT_EXT_TRIG_EDGE 1
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_NONE) */

#define STM32_ADC_HAS_INIT_DMA_CONT_REQUESTS 1

#if defined(ADC_EOC_SINGLE_CONV)
#define STM32_ADC_HAS_INIT_EOC_SELECTION 1
#endif /* defined(ADC_EOC_SINGLE_CONV) */

#ifdef BSP_USING_ADC1
/** @brief Default STM32L0 ADC1 V2 object initializer. */
#define ADC1_V2_CONFIG                                              \
    {                                                               \
        .name = "adc1",                                             \
        .config =                                                   \
        {                                                           \
            .sampling_time = ADC_DEFAULT_SAMPLING_TIME,             \
            .resolution = ADC_DEFAULT_RESOLUTION,                   \
            .data_align = ADC_DEFAULT_DATA_ALIGN,                   \
            .input_modes = RT_ADC_INPUT_MODE_SINGLE_ENDED,          \
            .oversampling_ratio = 0U,                               \
            .oversampling_right_shift = 0U,                         \
        },                                                          \
        .handle =                                                   \
        {                                                           \
            .Instance = ADC1,                                       \
        },                                                          \
    }
#endif /* BSP_USING_ADC1 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(RT_USING_ADC_V2) */

#endif /* __ADC_CONFIG_V2_H__ */
