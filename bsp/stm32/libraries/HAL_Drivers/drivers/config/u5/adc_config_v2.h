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

/** @brief Whether any ADC instance requests a stream DMA backend. */
#if defined(BSP_ADC1_USING_DMA) || defined(BSP_ADC2_USING_DMA) || \
    defined(BSP_ADC3_USING_DMA) || defined(BSP_ADC4_USING_DMA)
#define STM32_ADC_HAS_STREAM_DMA_BSP 1
#else
#define STM32_ADC_HAS_STREAM_DMA_BSP 0
#endif /* defined(BSP_ADC1_USING_DMA) || defined(BSP_ADC2_USING_DMA) || defined(BSP_ADC3_USING_DMA) || defined(BSP_ADC4_USING_DMA) */

/** @brief Whether stream mode is compiled in through the STM32 DMA-backed backend. */
#if defined(RT_ADC_USING_STREAM) && defined(HAL_DMA_MODULE_ENABLED) && STM32_ADC_HAS_STREAM_DMA_BSP
#define STM32_ADC_USING_STREAM 1
#else
#define STM32_ADC_USING_STREAM 0
#endif /* defined(RT_ADC_USING_STREAM) && defined(HAL_DMA_MODULE_ENABLED) && STM32_ADC_HAS_STREAM_DMA_BSP */

/** @brief Whether the compiled STM32 ADC stream backend uses DMA transport. */
#define STM32_ADC_USING_DMA_STREAM STM32_ADC_USING_STREAM

#if STM32_ADC_USING_STREAM
#if defined(BSP_ADC1_USING_DMA) && defined(ADC1_DMA_INSTANCE) && defined(ADC1_DMA_RCC) && defined(ADC1_DMA_IRQ)
#if defined(ADC1_DMA_REQUEST)
#define STM32_ADC1_DMA_REQUEST_VALUE ADC1_DMA_REQUEST
#else
#define STM32_ADC1_DMA_REQUEST_VALUE 0U
#endif /* defined(ADC1_DMA_REQUEST) */

#if defined(STM32_DMA_USES_GPDMA) && defined(ADC1_DMA_REQUEST)
#define ADC1_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC1_DMA_CONFIG =
    STM32_GPDMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC1_DMA_INSTANCE,
                                                ADC1_DMA_RCC,
                                                ADC1_DMA_IRQ,
                                                ADC1_DMA_REQUEST,
                                                STM32_DMA_DEFAULT_PRIORITY,
                                                STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                                STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC1_DMA_CHANNEL)
#define ADC1_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC1_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC1_DMA_INSTANCE,
                                             ADC1_DMA_RCC,
                                             ADC1_DMA_IRQ,
                                             ADC1_DMA_CHANNEL,
                                             STM32_ADC1_DMA_REQUEST_VALUE,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC1_DMA_REQUEST)
#define ADC1_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC1_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC1_DMA_INSTANCE,
                                             ADC1_DMA_RCC,
                                             ADC1_DMA_IRQ,
                                             0U,
                                             ADC1_DMA_REQUEST,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#endif /* defined(STM32_DMA_USES_GPDMA) && defined(ADC1_DMA_REQUEST) */
#endif /* defined(BSP_ADC1_USING_DMA) && defined(ADC1_DMA_INSTANCE) && defined(ADC1_DMA_RCC) && defined(ADC1_DMA_IRQ) */

#if defined(BSP_ADC2_USING_DMA) && defined(ADC2_DMA_INSTANCE) && defined(ADC2_DMA_RCC) && defined(ADC2_DMA_IRQ)
#if defined(ADC2_DMA_REQUEST)
#define STM32_ADC2_DMA_REQUEST_VALUE ADC2_DMA_REQUEST
#else
#define STM32_ADC2_DMA_REQUEST_VALUE 0U
#endif /* defined(ADC2_DMA_REQUEST) */

#if defined(STM32_DMA_USES_GPDMA) && defined(ADC2_DMA_REQUEST)
#define ADC2_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC2_DMA_CONFIG =
    STM32_GPDMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC2_DMA_INSTANCE,
                                                ADC2_DMA_RCC,
                                                ADC2_DMA_IRQ,
                                                ADC2_DMA_REQUEST,
                                                STM32_DMA_DEFAULT_PRIORITY,
                                                STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                                STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC2_DMA_CHANNEL)
#define ADC2_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC2_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC2_DMA_INSTANCE,
                                             ADC2_DMA_RCC,
                                             ADC2_DMA_IRQ,
                                             ADC2_DMA_CHANNEL,
                                             STM32_ADC2_DMA_REQUEST_VALUE,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC2_DMA_REQUEST)
#define ADC2_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC2_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC2_DMA_INSTANCE,
                                             ADC2_DMA_RCC,
                                             ADC2_DMA_IRQ,
                                             0U,
                                             ADC2_DMA_REQUEST,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#endif /* defined(STM32_DMA_USES_GPDMA) && defined(ADC2_DMA_REQUEST) */
#endif /* defined(BSP_ADC2_USING_DMA) && defined(ADC2_DMA_INSTANCE) && defined(ADC2_DMA_RCC) && defined(ADC2_DMA_IRQ) */

#if defined(BSP_ADC3_USING_DMA) && defined(ADC3_DMA_INSTANCE) && defined(ADC3_DMA_RCC) && defined(ADC3_DMA_IRQ)
#if defined(ADC3_DMA_REQUEST)
#define STM32_ADC3_DMA_REQUEST_VALUE ADC3_DMA_REQUEST
#else
#define STM32_ADC3_DMA_REQUEST_VALUE 0U
#endif /* defined(ADC3_DMA_REQUEST) */

#if defined(STM32_DMA_USES_GPDMA) && defined(ADC3_DMA_REQUEST)
#define ADC3_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC3_DMA_CONFIG =
    STM32_GPDMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC3_DMA_INSTANCE,
                                                ADC3_DMA_RCC,
                                                ADC3_DMA_IRQ,
                                                ADC3_DMA_REQUEST,
                                                STM32_DMA_DEFAULT_PRIORITY,
                                                STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                                STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC3_DMA_CHANNEL)
#define ADC3_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC3_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC3_DMA_INSTANCE,
                                             ADC3_DMA_RCC,
                                             ADC3_DMA_IRQ,
                                             ADC3_DMA_CHANNEL,
                                             STM32_ADC3_DMA_REQUEST_VALUE,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC3_DMA_REQUEST)
#define ADC3_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC3_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC3_DMA_INSTANCE,
                                             ADC3_DMA_RCC,
                                             ADC3_DMA_IRQ,
                                             0U,
                                             ADC3_DMA_REQUEST,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#endif /* defined(STM32_DMA_USES_GPDMA) && defined(ADC3_DMA_REQUEST) */
#endif /* defined(BSP_ADC3_USING_DMA) && defined(ADC3_DMA_INSTANCE) && defined(ADC3_DMA_RCC) && defined(ADC3_DMA_IRQ) */

#if defined(BSP_ADC4_USING_DMA) && defined(ADC4_DMA_INSTANCE) && defined(ADC4_DMA_RCC) && defined(ADC4_DMA_IRQ)
#if defined(ADC4_DMA_REQUEST)
#define STM32_ADC4_DMA_REQUEST_VALUE ADC4_DMA_REQUEST
#else
#define STM32_ADC4_DMA_REQUEST_VALUE 0U
#endif /* defined(ADC4_DMA_REQUEST) */

#if defined(STM32_DMA_USES_GPDMA) && defined(ADC4_DMA_REQUEST)
#define ADC4_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC4_DMA_CONFIG =
    STM32_GPDMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC4_DMA_INSTANCE,
                                                ADC4_DMA_RCC,
                                                ADC4_DMA_IRQ,
                                                ADC4_DMA_REQUEST,
                                                STM32_DMA_DEFAULT_PRIORITY,
                                                STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                                STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC4_DMA_CHANNEL)
#define ADC4_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC4_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC4_DMA_INSTANCE,
                                             ADC4_DMA_RCC,
                                             ADC4_DMA_IRQ,
                                             ADC4_DMA_CHANNEL,
                                             STM32_ADC4_DMA_REQUEST_VALUE,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#elif defined(ADC4_DMA_REQUEST)
#define ADC4_V2_HAS_DMA_CONFIG 1
static const struct stm32_dma_config ADC4_DMA_CONFIG =
    STM32_DMA_RX_WORD_CIRCULAR_CONFIG_INIT_EX(ADC4_DMA_INSTANCE,
                                             ADC4_DMA_RCC,
                                             ADC4_DMA_IRQ,
                                             0U,
                                             ADC4_DMA_REQUEST,
                                             STM32_DMA_DEFAULT_PRIORITY,
                                             STM32_DMA_DEFAULT_PREEMPT_PRIORITY,
                                             STM32_DMA_DEFAULT_SUB_PRIORITY);
#endif /* defined(STM32_DMA_USES_GPDMA) && defined(ADC4_DMA_REQUEST) */
#endif /* defined(BSP_ADC4_USING_DMA) && defined(ADC4_DMA_INSTANCE) && defined(ADC4_DMA_RCC) && defined(ADC4_DMA_IRQ) */

#endif /* STM32_ADC_USING_STREAM */

#if defined(ADC1_V2_HAS_DMA_CONFIG)
#define ADC1_V2_DMA_CONFIG_FIELD .dma_rx = &ADC1_DMA_CONFIG,
#else
#define ADC1_V2_DMA_CONFIG_FIELD
#endif /* defined(ADC1_V2_HAS_DMA_CONFIG) */

#if defined(ADC2_V2_HAS_DMA_CONFIG)
#define ADC2_V2_DMA_CONFIG_FIELD .dma_rx = &ADC2_DMA_CONFIG,
#else
#define ADC2_V2_DMA_CONFIG_FIELD
#endif /* defined(ADC2_V2_HAS_DMA_CONFIG) */

#if defined(ADC3_V2_HAS_DMA_CONFIG)
#define ADC3_V2_DMA_CONFIG_FIELD .dma_rx = &ADC3_DMA_CONFIG,
#else
#define ADC3_V2_DMA_CONFIG_FIELD
#endif /* defined(ADC3_V2_HAS_DMA_CONFIG) */

#if defined(ADC4_V2_HAS_DMA_CONFIG)
#define ADC4_V2_DMA_CONFIG_FIELD .dma_rx = &ADC4_DMA_CONFIG,
#else
#define ADC4_V2_DMA_CONFIG_FIELD
#endif /* defined(ADC4_V2_HAS_DMA_CONFIG) */



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
        ADC1_V2_DMA_CONFIG_FIELD                                    \
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
        ADC2_V2_DMA_CONFIG_FIELD                                    \
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
        ADC3_V2_DMA_CONFIG_FIELD                                    \
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
        ADC4_V2_DMA_CONFIG_FIELD                                    \
    }
#endif /* BSP_USING_ADC4 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(RT_USING_ADC_V2) */

#endif /* __ADC_CONFIG_V2_H__ */
