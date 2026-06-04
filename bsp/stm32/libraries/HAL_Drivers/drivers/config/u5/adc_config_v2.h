/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-21     wdfk-prog    add stm32u5 adc v2 configuration
 */

/**
 * @file adc_config_v2.h
 * @brief STM32U5 ADC V2 configuration defaults.
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

/** @brief Default ADC clock prescaler for STM32U5. */
#if defined(ADC_CLOCK_SYNC_PCLK_DIV4)
#define ADC_DEFAULT_CLOCK_PRESCALER ADC_CLOCK_SYNC_PCLK_DIV4
#elif defined(ADC_CLOCK_ASYNC_DIV1)
#define ADC_DEFAULT_CLOCK_PRESCALER ADC_CLOCK_ASYNC_DIV1
#endif /* defined(ADC_CLOCK_SYNC_PCLK_DIV4) */

/** @brief Default ADC data alignment for STM32U5. */
#define ADC_DEFAULT_DATA_ALIGN ADC_DATAALIGN_RIGHT

/** @brief Default ADC resolution for STM32 ADC V2. */
#ifdef ADC_RESOLUTION_12B
#define ADC_DEFAULT_RESOLUTION ADC_RESOLUTION_12B
#else
#define ADC_DEFAULT_RESOLUTION 0U
#endif /* ADC_RESOLUTION_12B */

/** @brief Default ADC sampling time for STM32U5. */
#if defined(ADC_SAMPLETIME_814CYCLES)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_814CYCLES
#else
#define ADC_DEFAULT_SAMPLING_TIME 0U
#endif /* defined(ADC_SAMPLETIME_814CYCLES) */


/** @brief Maximum regular sequence length supported by the STM32U5 driver. */
#define STM32_ADC_MAX_SEQUENCE 16

/** @brief Whether sequence mode is compiled in. */
#define STM32_ADC_USING_SEQUENCE 1


/* ADC V2 internal-channel routing policy for this STM32 series. */
/** @brief STM32U5 default internal ADC source instance mask. */
#define STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK ((1UL << 0) | (1UL << 1))

#if defined(ADC_CHANNEL_TEMPSENSOR)
/** @brief STM32U5 temperature sensor HAL ADC channel for the default internal route. */
#define STM32_ADC_TEMP_HAL_CHANNEL ADC_CHANNEL_TEMPSENSOR
#endif /* defined(ADC_CHANNEL_TEMPSENSOR) */

#if defined(ADC_CHANNEL_VBAT)
/** @brief STM32U5 VBAT HAL ADC channel for the default internal route. */
#define STM32_ADC_VBAT_HAL_CHANNEL ADC_CHANNEL_VBAT
#endif /* defined(ADC_CHANNEL_VBAT) */

#if defined(ADC_CHANNEL_VREFINT)
/** @brief STM32U5 VREFINT HAL ADC channel for the multi-instance route. */
#define STM32_ADC_VREF_HAL_CHANNEL ADC_CHANNEL_VREFINT
/** @brief STM32U5 ADC instances that can sample VREFINT. */
#define STM32_ADC_VREF_INSTANCE_MASK ((1UL << 0) | (1UL << 1) | (1UL << 3))
#endif /* defined(ADC_CHANNEL_VREFINT) */

#if defined(ADC_CHANNEL_TEMPSENSOR_ADC4)
/** @brief STM32U5 alternate temperature sensor HAL ADC channel. */
#define STM32_ADC_TEMP_ALT_HAL_CHANNEL ADC_CHANNEL_TEMPSENSOR_ADC4
/** @brief STM32U5 ADC instances that can sample the alternate temperature sensor channel. */
#define STM32_ADC_TEMP_ALT_INSTANCE_MASK (1UL << 3)
#endif /* defined(ADC_CHANNEL_TEMPSENSOR_ADC4) */

#if defined(ADC_CHANNEL_VBAT_ADC4)
/** @brief STM32U5 alternate VBAT HAL ADC channel. */
#define STM32_ADC_VBAT_ALT_HAL_CHANNEL ADC_CHANNEL_VBAT_ADC4
/** @brief STM32U5 ADC instances that can sample the alternate VBAT channel. */
#define STM32_ADC_VBAT_ALT_INSTANCE_MASK (1UL << 3)
#endif /* defined(ADC_CHANNEL_VBAT_ADC4) */


/* ADC V2 HAL feature policy for this STM32 series. */
#if defined(ADC_EXTERNALTRIGCONVEDGE_NONE)
#define STM32_ADC_HAS_INIT_EXT_TRIG_EDGE 1
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_NONE) */

#define STM32_ADC_HAS_INIT_NBR_OF_CONVERSION      1
#define STM32_ADC_HAS_INIT_NBR_OF_DISC_CONVERSION 1

#if defined(ADC_EOC_SINGLE_CONV)
#define STM32_ADC_HAS_INIT_EOC_SELECTION 1
#endif /* defined(ADC_EOC_SINGLE_CONV) */

#define STM32_ADC_NEEDS_ANALOG_SUPPLY 1
#define STM32_ADC_VREF_NEEDS_INSTANCE 1


#ifdef BSP_USING_ADC1
/** @brief Default STM32U5 ADC1 V2 object initializer. */
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

#ifdef BSP_USING_ADC2
/** @brief Default STM32U5 ADC2 V2 object initializer. */
#define ADC2_V2_CONFIG                                              \
    {                                                               \
        .name = "adc2",                                             \
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
            .Instance = ADC2,                                       \
        },                                                          \
    }
#endif /* BSP_USING_ADC2 */

#ifdef BSP_USING_ADC3
/** @brief Default STM32U5 ADC3 V2 object initializer. */
#define ADC3_V2_CONFIG                                              \
    {                                                               \
        .name = "adc3",                                             \
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
            .Instance = ADC3,                                       \
        },                                                          \
    }
#endif /* BSP_USING_ADC3 */

#ifdef BSP_USING_ADC4
/** @brief Default STM32U5 ADC4 V2 object initializer. */
#define ADC4_V2_CONFIG                                              \
    {                                                               \
        .name = "adc4",                                             \
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
            .Instance = ADC4,                                       \
        },                                                          \
    }
#endif /* BSP_USING_ADC4 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(RT_USING_ADC_V2) */

#endif /* __ADC_CONFIG_V2_H__ */
