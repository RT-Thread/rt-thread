/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-27     wdfk-prog    add stm32h5 adc v2 configuration
 */

/**
 * @file adc_config_v2.h
 * @brief STM32H5 ADC V2 configuration defaults.
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

/** @brief Default ADC clock prescaler for STM32H5. */
#if defined(ADC_CLOCK_SYNC_PCLK_DIV4)
#define ADC_DEFAULT_CLOCK_PRESCALER ADC_CLOCK_SYNC_PCLK_DIV4
#elif defined(ADC_CLOCK_ASYNC_DIV1)
#define ADC_DEFAULT_CLOCK_PRESCALER ADC_CLOCK_ASYNC_DIV1
#endif /* defined(ADC_CLOCK_SYNC_PCLK_DIV4) */

/** @brief Default ADC data alignment for STM32H5. */
#if defined(ADC_DATAALIGN_RIGHT)
#define ADC_DEFAULT_DATA_ALIGN ADC_DATAALIGN_RIGHT
#else
#define ADC_DEFAULT_DATA_ALIGN 0U
#endif /* defined(ADC_DATAALIGN_RIGHT) */

/** @brief Default ADC resolution for STM32H5. */
#ifdef ADC_RESOLUTION_12B
#define ADC_DEFAULT_RESOLUTION ADC_RESOLUTION_12B
#else
#define ADC_DEFAULT_RESOLUTION 0U
#endif /* ADC_RESOLUTION_12B */

/** @brief Default ADC sampling time for STM32H5. */
#if defined(ADC_SAMPLETIME_814CYCLES)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_814CYCLES
#elif defined(ADC_SAMPLETIME_810CYCLES_5)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_810CYCLES_5
#elif defined(ADC_SAMPLETIME_247CYCLES_5)
#define ADC_DEFAULT_SAMPLING_TIME ADC_SAMPLETIME_247CYCLES_5
#else
#define ADC_DEFAULT_SAMPLING_TIME 0U
#endif /* defined(ADC_SAMPLETIME_814CYCLES) */


/** @brief Maximum regular sequence length supported by the STM32H5 driver. */
#define STM32_ADC_MAX_SEQUENCE 16

/** @brief Whether sequence mode is compiled in. */
#define STM32_ADC_USING_SEQUENCE 1


/* ADC V2 internal-channel routing policy for this STM32 series. */
#if defined(ADC_CHANNEL_VBAT)
/** @brief STM32H5 VBAT HAL ADC channel for the series-specific route. */
#define STM32_ADC_VBAT_HAL_CHANNEL ADC_CHANNEL_VBAT
#if defined(ADC2)
/** @brief STM32H5 ADC instances that can sample VBAT. */
#define STM32_ADC_VBAT_INSTANCE_MASK (1UL << 1)
#else
/** @brief STM32H5 ADC instances that can sample VBAT. */
#define STM32_ADC_VBAT_INSTANCE_MASK (1UL << 0)
#endif /* defined(ADC2) */
#endif /* defined(ADC_CHANNEL_VBAT) */

#if defined(ADC_CHANNEL_VBAT_ADC4)
/** @brief STM32H5 alternate VBAT HAL ADC channel. */
#define STM32_ADC_VBAT_ALT_HAL_CHANNEL ADC_CHANNEL_VBAT_ADC4
/** @brief STM32H5 ADC instances that can sample the alternate VBAT channel. */
#define STM32_ADC_VBAT_ALT_INSTANCE_MASK (1UL << 2)
#endif /* defined(ADC_CHANNEL_VBAT_ADC4) */


/* ADC V2 HAL feature policy for this STM32 series. */
#if defined(ADC_DEFAULT_DATA_ALIGN)
#define STM32_ADC_HAS_INIT_DATA_ALIGN 1
#endif /* defined(ADC_DEFAULT_DATA_ALIGN) */

#if defined(ADC_EXTERNALTRIGCONVEDGE_NONE)
#define STM32_ADC_HAS_INIT_EXT_TRIG_EDGE 1
#endif /* defined(ADC_EXTERNALTRIGCONVEDGE_NONE) */

#define STM32_ADC_HAS_INIT_NBR_OF_CONVERSION      1
#define STM32_ADC_HAS_INIT_NBR_OF_DISC_CONVERSION 1

#if defined(ADC_EOC_SINGLE_CONV)
#define STM32_ADC_HAS_INIT_EOC_SELECTION 1
#endif /* defined(ADC_EOC_SINGLE_CONV) */


#ifdef BSP_USING_ADC1
/** @brief Default STM32H5 ADC1 V2 object initializer. */
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
/** @brief Default STM32H5 ADC2 V2 object initializer. */
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(RT_USING_ADC_V2) */

#endif /* __ADC_CONFIG_V2_H__ */
