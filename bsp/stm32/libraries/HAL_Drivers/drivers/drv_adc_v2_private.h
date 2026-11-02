/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

/**
 * @file drv_adc_v2_private.h
 * @brief Private declarations for the STM32 ADC V2 backend.
 */

#ifndef __DRV_ADC_V2_PRIVATE_H__
#define __DRV_ADC_V2_PRIVATE_H__

#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)

#include "drv_adc_v2.h"
#include <stddef.h>

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4)

/* STM32 HAL ADC support is detected here when the HAL exposes a stable
 * feature macro. Keep series-specific defaults and internal-channel routing
 * overrides in config/<series>/adc_config_v2.h; keep HAL structure/API
 * compatibility here so new series normally inherit support from their HAL
 * headers.
 */

/* STM32F0-like sequencers use ADC_RANK_CHANNEL_NUMBER instead of a numeric
 * regular-rank slot. Other HALs that expose ADC_REGULAR_RANK_x constants can
 * use those constants directly; otherwise plain rank numbers are used.
 */
#if defined(ADC_RANK_CHANNEL_NUMBER)
#define STM32_ADC_HAS_CHANNEL_NUMBER_RANK 1
#elif defined(ADC_REGULAR_RANK_1)
#define STM32_ADC_HAS_ENUM_RANK 1
#endif /* defined(ADC_RANK_CHANNEL_NUMBER) */

#if defined(ADC_CONVERSIONDATA_DR) && defined(ADC_CONVERSIONDATA_DMA_CIRCULAR)
#define STM32_ADC_HAS_INIT_CONVERSION_DATA_MANAGEMENT 1
#endif /* defined(ADC_CONVERSIONDATA_DR) && defined(ADC_CONVERSIONDATA_DMA_CIRCULAR) */

#if defined(ADC_SCAN_ENABLE)
#define STM32_ADC_SCAN_MODE_ENABLE ADC_SCAN_ENABLE
#elif defined(ADC_SCAN_DIRECTION_FORWARD)
#define STM32_ADC_SCAN_MODE_ENABLE ADC_SCAN_DIRECTION_FORWARD
#else
#define STM32_ADC_SCAN_MODE_ENABLE ENABLE
#endif /* defined(ADC_SCAN_ENABLE) */

#if defined(ADC_SCAN_DISABLE)
#define STM32_ADC_SCAN_MODE_DISABLE ADC_SCAN_DISABLE
#elif defined(ADC_SCAN_DIRECTION_FORWARD)
#define STM32_ADC_SCAN_MODE_DISABLE ADC_SCAN_DIRECTION_FORWARD
#else
#define STM32_ADC_SCAN_MODE_DISABLE DISABLE
#endif /* defined(ADC_SCAN_DISABLE) */

/* Channel configuration fields are tied to HAL channel-mode and offset macros.
 * A config file may still override these before including this driver header if
 * a vendor HAL variant exposes a different field layout.
 */
#if !defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS)
#if defined(ADC_SINGLE_ENDED) && defined(ADC_DIFFERENTIAL_ENDED)
#define STM32_ADC_HAS_SINGLE_DIFF_FIELDS 1
#define STM32_ADC_SINGLE_ENDED_VALUE     ADC_SINGLE_ENDED
#define STM32_ADC_DIFFERENTIAL_VALUE     ADC_DIFFERENTIAL_ENDED
#elif defined(LL_ADC_SINGLE_ENDED) && defined(LL_ADC_DIFFERENTIAL_ENDED)
#define STM32_ADC_HAS_SINGLE_DIFF_FIELDS 1
#define STM32_ADC_SINGLE_ENDED_VALUE     LL_ADC_SINGLE_ENDED
#define STM32_ADC_DIFFERENTIAL_VALUE     LL_ADC_DIFFERENTIAL_ENDED
#endif /* defined(ADC_SINGLE_ENDED) && defined(ADC_DIFFERENTIAL_ENDED) */
#endif /* !defined(STM32_ADC_HAS_SINGLE_DIFF_FIELDS) */

#if defined(ADC_OFFSET_NONE)
#ifndef STM32_ADC_HAS_CONFIG_OFFSET
#define STM32_ADC_HAS_CONFIG_OFFSET 1
#endif /* STM32_ADC_HAS_CONFIG_OFFSET */
#ifndef STM32_ADC_HAS_CONFIG_OFFSET_NUMBER
#define STM32_ADC_HAS_CONFIG_OFFSET_NUMBER 1
#endif /* STM32_ADC_HAS_CONFIG_OFFSET_NUMBER */
#endif /* defined(ADC_OFFSET_NONE) */

#if defined(ADC_RESOLUTION_12B)
#define STM32_ADC_HAS_CONFIGURABLE_RESOLUTION 1
#endif /* defined(ADC_RESOLUTION_12B) */

#if defined(ADC_CALIB_OFFSET_LINEARITY)
#define STM32_ADC_HAS_LINEAR_CALIBRATION 1
#endif /* defined(ADC_CALIB_OFFSET_LINEARITY) */

#if defined(STM32_ADC_HAS_SIMPLE_CALIBRATION) || defined(STM32_ADC_HAS_LINEAR_CALIBRATION)
#define STM32_ADC_HAS_CALIBRATION 1
#endif /* defined(STM32_ADC_HAS_SIMPLE_CALIBRATION) || defined(STM32_ADC_HAS_LINEAR_CALIBRATION) */

#if defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7RS)
/** @brief Enable D-Cache-safe ADC DMA stream handling for Cortex-M7 STM32 series. */
#define STM32_ADC_NEEDS_DMA_CACHE_MAINTENANCE 1
#endif /* defined(SOC_SERIES_STM32H7) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32H7RS) */

#if defined(BSP_ADC_USING_TRIGGER) && defined(RT_ADC_USING_TRIGGER)
/** @brief Whether the STM32 ADC trigger backend support is compiled in. */
#define STM32_ADC_USING_TRIGGER 1
#endif /* defined(BSP_ADC_USING_TRIGGER) && defined(RT_ADC_USING_TRIGGER) */

#if defined(STM32_ADC_USING_TRIGGER) && defined(BSP_ADC_USING_TIMER_TRIGGER) && defined(RT_ADC_TRIGGER_USING_TIMER) && defined(BSP_USING_TIM)
/** @brief Whether the STM32 ADC timer trigger selector backend is compiled in. */
#define STM32_ADC_USING_TIMER_TRIGGER 1
#endif /* defined(STM32_ADC_USING_TRIGGER) && defined(BSP_ADC_USING_TIMER_TRIGGER) && defined(RT_ADC_TRIGGER_USING_TIMER) && defined(BSP_USING_TIM) */

#if defined(STM32_ADC_USING_TRIGGER) && defined(BSP_ADC_USING_ANALOG_COMPARE_TRIGGER)
#if defined(RT_ADC_TRIGGER_USING_COMPARE)
/** @brief Whether the STM32 ADC analog-comparator trigger selector backend is compiled in. */
#define STM32_ADC_USING_ANALOG_COMPARE_TRIGGER 1
#endif /* defined(RT_ADC_TRIGGER_USING_COMPARE) */
#endif /* defined(STM32_ADC_USING_TRIGGER) && defined(BSP_ADC_USING_ANALOG_COMPARE_TRIGGER) */

#if defined(__LL_ADC_CALC_VREFANALOG_VOLTAGE) && defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION)
#define STM32_ADC_HAS_LL_VREF_CALC 1
#endif /* defined(__LL_ADC_CALC_VREFANALOG_VOLTAGE) && defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION) */

#if defined(STM32_ADC_HAS_LL_VREF_CALC)
#if defined(STM32_ADC_VREF_NEEDS_INSTANCE)
/* Calculate VDDA in millivolts with an instance-aware LL helper. */
#define STM32_ADC_CALC_VREF_MV(_adc, _raw) \
    __LL_ADC_CALC_VREFANALOG_VOLTAGE((_adc)->handle.Instance, (_raw), (_adc)->handle.Init.Resolution)
#else
/* Calculate VDDA in millivolts with the generic LL helper. */
#define STM32_ADC_CALC_VREF_MV(_adc, _raw) \
    __LL_ADC_CALC_VREFANALOG_VOLTAGE((_raw), (_adc)->handle.Init.Resolution)
#endif /* defined(STM32_ADC_VREF_NEEDS_INSTANCE) */
#endif /* defined(STM32_ADC_HAS_LL_VREF_CALC) */

#if defined(__LL_ADC_CALC_TEMPERATURE) && defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION)
#define STM32_ADC_HAS_LL_TEMPERATURE_CALC 1

#if defined(STM32_ADC_TEMPERATURE_NEEDS_INSTANCE)
/* Calculate temperature in degrees Celsius with an instance-aware LL helper. */
#define STM32_ADC_CALC_TEMPERATURE(_adc, _vref_mv, _raw, _resolution) \
    __LL_ADC_CALC_TEMPERATURE((_adc)->handle.Instance, (_vref_mv), (_raw), (_resolution))
#else
/* Calculate temperature in degrees Celsius with the generic LL helper. */
#define STM32_ADC_CALC_TEMPERATURE(_adc, _vref_mv, _raw, _resolution) \
    __LL_ADC_CALC_TEMPERATURE((_vref_mv), (_raw), (_resolution))
#endif /* defined(STM32_ADC_TEMPERATURE_NEEDS_INSTANCE) */

#endif /* defined(__LL_ADC_CALC_TEMPERATURE) && defined(STM32_ADC_HAS_CONFIGURABLE_RESOLUTION) */

#if defined(TEMPSENSOR_CAL1_ADDR) && defined(TEMPSENSOR_CAL2_ADDR) && defined(TEMPSENSOR_CAL1_TEMP) && \
    defined(TEMPSENSOR_CAL2_TEMP) && defined(TEMPSENSOR_CAL_VREFANALOG)
#define STM32_ADC_HAS_TEMPSENSOR_CALIBRATION_DATA 1
#endif /* defined(TEMPSENSOR_CAL1_ADDR) && defined(TEMPSENSOR_CAL2_ADDR) && defined(TEMPSENSOR_CAL1_TEMP) && defined(TEMPSENSOR_CAL2_TEMP) && defined(TEMPSENSOR_CAL_VREFANALOG) */

#if defined(ADC_OVERSAMPLING_RATIO_2) && defined(ADC_RIGHTBITSHIFT_1)
#if defined(ADC_TRIGGEREDMODE_SINGLE_TRIGGER) && defined(ADC_REGOVERSAMPLING_CONTINUED_MODE)
#define STM32_ADC_HAS_HW_OVERSAMPLING 1
#endif /* defined(ADC_TRIGGEREDMODE_SINGLE_TRIGGER) && defined(ADC_REGOVERSAMPLING_CONTINUED_MODE) */
#endif /* defined(ADC_OVERSAMPLING_RATIO_2) && defined(ADC_RIGHTBITSHIFT_1) */

/** @brief Marker for an unavailable STM32 HAL ADC channel. */
#ifndef STM32_ADC_INVALID_CHANNEL
#define STM32_ADC_INVALID_CHANNEL 0xFFFFFFFFUL
#endif /* STM32_ADC_INVALID_CHANNEL */

/** @brief Invalid RT-Thread logical ADC channel marker. */
#ifndef STM32_ADC_INVALID_LOGICAL_CHANNEL
#define STM32_ADC_INVALID_LOGICAL_CHANNEL (-1)
#endif /* STM32_ADC_INVALID_LOGICAL_CHANNEL */

/** @brief STM32 ADC instance mask bit for ADC1. */
#ifndef STM32_ADC_INSTANCE_MASK_ADC1
#define STM32_ADC_INSTANCE_MASK_ADC1 (1UL << 0)
#endif /* STM32_ADC_INSTANCE_MASK_ADC1 */

/** @brief STM32 ADC instance mask bit for ADC2. */
#ifndef STM32_ADC_INSTANCE_MASK_ADC2
#define STM32_ADC_INSTANCE_MASK_ADC2 (1UL << 1)
#endif /* STM32_ADC_INSTANCE_MASK_ADC2 */

/** @brief STM32 ADC instance mask bit for ADC3. */
#ifndef STM32_ADC_INSTANCE_MASK_ADC3
#define STM32_ADC_INSTANCE_MASK_ADC3 (1UL << 2)
#endif /* STM32_ADC_INSTANCE_MASK_ADC3 */

/** @brief STM32 ADC instance mask bit for ADC4. */
#ifndef STM32_ADC_INSTANCE_MASK_ADC4
#define STM32_ADC_INSTANCE_MASK_ADC4 (1UL << 3)
#endif /* STM32_ADC_INSTANCE_MASK_ADC4 */

/** @brief STM32 ADC instance mask bit for ADC5. */
#ifndef STM32_ADC_INSTANCE_MASK_ADC5
#define STM32_ADC_INSTANCE_MASK_ADC5 (1UL << 4)
#endif /* STM32_ADC_INSTANCE_MASK_ADC5 */

/** @brief Mask value that allows every known STM32 ADC instance. */
#ifndef STM32_ADC_INSTANCE_MASK_ALL
#define STM32_ADC_INSTANCE_MASK_ALL 0xffffffffUL
#endif /* STM32_ADC_INSTANCE_MASK_ALL */

/** @brief Convert a STM32 HAL ADC channel literal into a RT-Thread logical channel number. */
#ifndef STM32_ADC_HAL_CHANNEL_TO_LOGICAL
#if defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB)
#define STM32_ADC_HAL_CHANNEL_TO_LOGICAL(_channel) __HAL_ADC_CHANNEL_TO_DECIMAL_NB(_channel)
#elif defined(__LL_ADC_CHANNEL_TO_DECIMAL_NB)
#define STM32_ADC_HAL_CHANNEL_TO_LOGICAL(_channel) __LL_ADC_CHANNEL_TO_DECIMAL_NB(_channel)
#else
#define STM32_ADC_HAL_CHANNEL_TO_LOGICAL(_channel) STM32_ADC_INVALID_LOGICAL_CHANNEL
#endif /* defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB) */
#endif /* STM32_ADC_HAL_CHANNEL_TO_LOGICAL */

/** @brief Maximum HAL ADC channel-table entries exposed by the active STM32 HAL. */
#ifndef STM32_ADC_MAX_CHANNELS
#if defined(ADC_CHANNEL_31)
#define STM32_ADC_MAX_CHANNELS 32
#elif defined(ADC_CHANNEL_30)
#define STM32_ADC_MAX_CHANNELS 31
#elif defined(ADC_CHANNEL_29)
#define STM32_ADC_MAX_CHANNELS 30
#elif defined(ADC_CHANNEL_28)
#define STM32_ADC_MAX_CHANNELS 29
#elif defined(ADC_CHANNEL_27)
#define STM32_ADC_MAX_CHANNELS 28
#elif defined(ADC_CHANNEL_26)
#define STM32_ADC_MAX_CHANNELS 27
#elif defined(ADC_CHANNEL_25)
#define STM32_ADC_MAX_CHANNELS 26
#elif defined(ADC_CHANNEL_24)
#define STM32_ADC_MAX_CHANNELS 25
#elif defined(ADC_CHANNEL_23)
#define STM32_ADC_MAX_CHANNELS 24
#elif defined(ADC_CHANNEL_22)
#define STM32_ADC_MAX_CHANNELS 23
#elif defined(ADC_CHANNEL_21)
#define STM32_ADC_MAX_CHANNELS 22
#elif defined(ADC_CHANNEL_20)
#define STM32_ADC_MAX_CHANNELS 21
#elif defined(ADC_CHANNEL_19)
#define STM32_ADC_MAX_CHANNELS 20
#elif defined(ADC_CHANNEL_18)
#define STM32_ADC_MAX_CHANNELS 19
#elif defined(ADC_CHANNEL_17)
#define STM32_ADC_MAX_CHANNELS 18
#elif defined(ADC_CHANNEL_16)
#define STM32_ADC_MAX_CHANNELS 17
#else
#define STM32_ADC_MAX_CHANNELS 16
#endif /* defined(ADC_CHANNEL_31) */
#endif /* STM32_ADC_MAX_CHANNELS */

/* Optional ADC channel encodings supplied by the active STM32 HAL. */
#ifndef STM32_ADC_CHANNEL_16
#ifdef ADC_CHANNEL_16
#define STM32_ADC_CHANNEL_16 ADC_CHANNEL_16
#else
#define STM32_ADC_CHANNEL_16 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_16 */
#endif /* STM32_ADC_CHANNEL_16 */

#ifndef STM32_ADC_CHANNEL_17
#ifdef ADC_CHANNEL_17
#define STM32_ADC_CHANNEL_17 ADC_CHANNEL_17
#else
#define STM32_ADC_CHANNEL_17 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_17 */
#endif /* STM32_ADC_CHANNEL_17 */

#ifndef STM32_ADC_CHANNEL_18
#ifdef ADC_CHANNEL_18
#define STM32_ADC_CHANNEL_18 ADC_CHANNEL_18
#else
#define STM32_ADC_CHANNEL_18 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_18 */
#endif /* STM32_ADC_CHANNEL_18 */

#ifndef STM32_ADC_CHANNEL_19
#ifdef ADC_CHANNEL_19
#define STM32_ADC_CHANNEL_19 ADC_CHANNEL_19
#else
#define STM32_ADC_CHANNEL_19 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_19 */
#endif /* STM32_ADC_CHANNEL_19 */

#ifndef STM32_ADC_CHANNEL_20
#ifdef ADC_CHANNEL_20
#define STM32_ADC_CHANNEL_20 ADC_CHANNEL_20
#else
#define STM32_ADC_CHANNEL_20 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_20 */
#endif /* STM32_ADC_CHANNEL_20 */

#ifndef STM32_ADC_CHANNEL_21
#ifdef ADC_CHANNEL_21
#define STM32_ADC_CHANNEL_21 ADC_CHANNEL_21
#else
#define STM32_ADC_CHANNEL_21 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_21 */
#endif /* STM32_ADC_CHANNEL_21 */

#ifndef STM32_ADC_CHANNEL_22
#ifdef ADC_CHANNEL_22
#define STM32_ADC_CHANNEL_22 ADC_CHANNEL_22
#else
#define STM32_ADC_CHANNEL_22 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_22 */
#endif /* STM32_ADC_CHANNEL_22 */

#ifndef STM32_ADC_CHANNEL_23
#ifdef ADC_CHANNEL_23
#define STM32_ADC_CHANNEL_23 ADC_CHANNEL_23
#else
#define STM32_ADC_CHANNEL_23 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_23 */
#endif /* STM32_ADC_CHANNEL_23 */

#ifndef STM32_ADC_CHANNEL_24
#ifdef ADC_CHANNEL_24
#define STM32_ADC_CHANNEL_24 ADC_CHANNEL_24
#else
#define STM32_ADC_CHANNEL_24 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_24 */
#endif /* STM32_ADC_CHANNEL_24 */

#ifndef STM32_ADC_CHANNEL_25
#ifdef ADC_CHANNEL_25
#define STM32_ADC_CHANNEL_25 ADC_CHANNEL_25
#else
#define STM32_ADC_CHANNEL_25 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_25 */
#endif /* STM32_ADC_CHANNEL_25 */

#ifndef STM32_ADC_CHANNEL_26
#ifdef ADC_CHANNEL_26
#define STM32_ADC_CHANNEL_26 ADC_CHANNEL_26
#else
#define STM32_ADC_CHANNEL_26 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_26 */
#endif /* STM32_ADC_CHANNEL_26 */

#ifndef STM32_ADC_CHANNEL_27
#ifdef ADC_CHANNEL_27
#define STM32_ADC_CHANNEL_27 ADC_CHANNEL_27
#else
#define STM32_ADC_CHANNEL_27 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_27 */
#endif /* STM32_ADC_CHANNEL_27 */

#ifndef STM32_ADC_CHANNEL_28
#ifdef ADC_CHANNEL_28
#define STM32_ADC_CHANNEL_28 ADC_CHANNEL_28
#else
#define STM32_ADC_CHANNEL_28 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_28 */
#endif /* STM32_ADC_CHANNEL_28 */

#ifndef STM32_ADC_CHANNEL_29
#ifdef ADC_CHANNEL_29
#define STM32_ADC_CHANNEL_29 ADC_CHANNEL_29
#else
#define STM32_ADC_CHANNEL_29 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_29 */
#endif /* STM32_ADC_CHANNEL_29 */

#ifndef STM32_ADC_CHANNEL_30
#ifdef ADC_CHANNEL_30
#define STM32_ADC_CHANNEL_30 ADC_CHANNEL_30
#else
#define STM32_ADC_CHANNEL_30 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_30 */
#endif /* STM32_ADC_CHANNEL_30 */

#ifndef STM32_ADC_CHANNEL_31
#ifdef ADC_CHANNEL_31
#define STM32_ADC_CHANNEL_31 ADC_CHANNEL_31
#else
#define STM32_ADC_CHANNEL_31 STM32_ADC_INVALID_CHANNEL
#endif /* ADC_CHANNEL_31 */
#endif /* STM32_ADC_CHANNEL_31 */

/**
 * @brief Default ADC instance mask for common STM32 internal ADC sources.
 *
 * Series configuration files should override this macro only when internal
 * sources are not routed to ADC1 by default.
 */
#ifndef STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#define STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC1
#endif /* STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK */

/* Resolve temperature sensor HAL channel and supported ADC instances. */
#ifndef STM32_ADC_TEMP_HAL_CHANNEL
#if defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
#define STM32_ADC_TEMP_HAL_CHANNEL ADC_CHANNEL_TEMPSENSOR_ADC1
#ifndef STM32_ADC_TEMP_CHANNEL_AVAILABLE
#define STM32_ADC_TEMP_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_TEMP_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_TEMP_INSTANCE_MASK
#define STM32_ADC_TEMP_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC1
#endif /* STM32_ADC_TEMP_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_TEMPSENSOR_ADC3)
#define STM32_ADC_TEMP_HAL_CHANNEL ADC_CHANNEL_TEMPSENSOR_ADC3
#ifndef STM32_ADC_TEMP_CHANNEL_AVAILABLE
#define STM32_ADC_TEMP_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_TEMP_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_TEMP_INSTANCE_MASK
#define STM32_ADC_TEMP_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC3
#endif /* STM32_ADC_TEMP_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_TEMPSENSOR)
#define STM32_ADC_TEMP_HAL_CHANNEL ADC_CHANNEL_TEMPSENSOR
#ifndef STM32_ADC_TEMP_CHANNEL_AVAILABLE
#define STM32_ADC_TEMP_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_TEMP_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_TEMP_INSTANCE_MASK
#define STM32_ADC_TEMP_INSTANCE_MASK STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#endif /* STM32_ADC_TEMP_INSTANCE_MASK */
#else
#define STM32_ADC_TEMP_HAL_CHANNEL STM32_ADC_INVALID_CHANNEL
#ifndef STM32_ADC_TEMP_CHANNEL_AVAILABLE
#define STM32_ADC_TEMP_CHANNEL_AVAILABLE 0
#endif /* STM32_ADC_TEMP_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_TEMP_INSTANCE_MASK
#define STM32_ADC_TEMP_INSTANCE_MASK 0UL
#endif /* STM32_ADC_TEMP_INSTANCE_MASK */
#endif /* defined(ADC_CHANNEL_TEMPSENSOR_ADC1) */
#endif /* STM32_ADC_TEMP_HAL_CHANNEL */

/** @brief Whether the primary temperature-sensor HAL channel can be used. */
#ifndef STM32_ADC_TEMP_CHANNEL_AVAILABLE
#define STM32_ADC_TEMP_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_TEMP_CHANNEL_AVAILABLE */

#ifndef STM32_ADC_TEMP_INSTANCE_MASK
#if STM32_ADC_TEMP_CHANNEL_AVAILABLE
/** @brief ADC instances that can sample the temperature sensor. */
#define STM32_ADC_TEMP_INSTANCE_MASK STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#else
/** @brief ADC instances that can sample the temperature sensor. */
#define STM32_ADC_TEMP_INSTANCE_MASK 0UL
#endif /* STM32_ADC_TEMP_CHANNEL_AVAILABLE */
#endif /* STM32_ADC_TEMP_INSTANCE_MASK */

#ifndef STM32_ADC_TEMP_CHANNEL
#if !STM32_ADC_TEMP_CHANNEL_AVAILABLE
#define STM32_ADC_TEMP_CHANNEL STM32_ADC_INVALID_LOGICAL_CHANNEL
#elif defined(STM32_ADC_TEMP_LOGICAL_OVERRIDE)
#define STM32_ADC_TEMP_CHANNEL STM32_ADC_TEMP_LOGICAL_OVERRIDE
#elif defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB) || defined(__LL_ADC_CHANNEL_TO_DECIMAL_NB)
#define STM32_ADC_TEMP_CHANNEL STM32_ADC_HAL_CHANNEL_TO_LOGICAL(STM32_ADC_TEMP_HAL_CHANNEL)
#else
#error "STM32 ADC V2: define STM32_ADC_TEMP_LOGICAL_OVERRIDE for this legacy HAL series."
#endif /* !STM32_ADC_TEMP_CHANNEL_AVAILABLE */
#endif /* STM32_ADC_TEMP_CHANNEL */

/* Resolve VBAT HAL channel and supported ADC instances. */
#ifndef STM32_ADC_VBAT_HAL_CHANNEL
#if defined(ADC_CHANNEL_VBAT_ADC1)
#define STM32_ADC_VBAT_HAL_CHANNEL ADC_CHANNEL_VBAT_ADC1
#ifndef STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VBAT_INSTANCE_MASK
#define STM32_ADC_VBAT_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC1
#endif /* STM32_ADC_VBAT_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_VBAT_ADC2)
#define STM32_ADC_VBAT_HAL_CHANNEL ADC_CHANNEL_VBAT_ADC2
#ifndef STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VBAT_INSTANCE_MASK
#define STM32_ADC_VBAT_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC2
#endif /* STM32_ADC_VBAT_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_VBAT_ADC3)
#define STM32_ADC_VBAT_HAL_CHANNEL ADC_CHANNEL_VBAT_ADC3
#ifndef STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VBAT_INSTANCE_MASK
#define STM32_ADC_VBAT_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC3
#endif /* STM32_ADC_VBAT_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_VBAT)
#define STM32_ADC_VBAT_HAL_CHANNEL ADC_CHANNEL_VBAT
#ifndef STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VBAT_INSTANCE_MASK
#define STM32_ADC_VBAT_INSTANCE_MASK STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#endif /* STM32_ADC_VBAT_INSTANCE_MASK */
#else
#define STM32_ADC_VBAT_HAL_CHANNEL STM32_ADC_INVALID_CHANNEL
#ifndef STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL_AVAILABLE 0
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VBAT_INSTANCE_MASK
#define STM32_ADC_VBAT_INSTANCE_MASK 0UL
#endif /* STM32_ADC_VBAT_INSTANCE_MASK */
#endif /* defined(ADC_CHANNEL_VBAT_ADC1) */
#endif /* STM32_ADC_VBAT_HAL_CHANNEL */

/** @brief Whether the primary VBAT HAL channel can be used. */
#ifndef STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */

#ifndef STM32_ADC_VBAT_INSTANCE_MASK
#if STM32_ADC_VBAT_CHANNEL_AVAILABLE
/** @brief ADC instances that can sample VBAT. */
#define STM32_ADC_VBAT_INSTANCE_MASK STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#else
/** @brief ADC instances that can sample VBAT. */
#define STM32_ADC_VBAT_INSTANCE_MASK 0UL
#endif /* STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#endif /* STM32_ADC_VBAT_INSTANCE_MASK */

#ifndef STM32_ADC_VBAT_CHANNEL
#if !STM32_ADC_VBAT_CHANNEL_AVAILABLE
#define STM32_ADC_VBAT_CHANNEL STM32_ADC_INVALID_LOGICAL_CHANNEL
#elif defined(STM32_ADC_VBAT_LOGICAL_OVERRIDE)
#define STM32_ADC_VBAT_CHANNEL STM32_ADC_VBAT_LOGICAL_OVERRIDE
#elif defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB) || defined(__LL_ADC_CHANNEL_TO_DECIMAL_NB)
#define STM32_ADC_VBAT_CHANNEL STM32_ADC_HAL_CHANNEL_TO_LOGICAL(STM32_ADC_VBAT_HAL_CHANNEL)
#else
#error "STM32 ADC V2: define STM32_ADC_VBAT_LOGICAL_OVERRIDE for this legacy HAL series."
#endif /* !STM32_ADC_VBAT_CHANNEL_AVAILABLE */
#endif /* STM32_ADC_VBAT_CHANNEL */

/* Resolve VREFINT HAL channel and supported ADC instances. */
#ifndef STM32_ADC_VREF_HAL_CHANNEL
#if defined(ADC_CHANNEL_VREFINT_ADC1)
#define STM32_ADC_VREF_HAL_CHANNEL ADC_CHANNEL_VREFINT_ADC1
#ifndef STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VREF_INSTANCE_MASK
#define STM32_ADC_VREF_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC1
#endif /* STM32_ADC_VREF_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_VREFINT_ADC2)
#define STM32_ADC_VREF_HAL_CHANNEL ADC_CHANNEL_VREFINT_ADC2
#ifndef STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VREF_INSTANCE_MASK
#define STM32_ADC_VREF_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC2
#endif /* STM32_ADC_VREF_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_VREFINT_ADC3)
#define STM32_ADC_VREF_HAL_CHANNEL ADC_CHANNEL_VREFINT_ADC3
#ifndef STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VREF_INSTANCE_MASK
#define STM32_ADC_VREF_INSTANCE_MASK STM32_ADC_INSTANCE_MASK_ADC3
#endif /* STM32_ADC_VREF_INSTANCE_MASK */
#elif defined(ADC_CHANNEL_VREFINT)
#define STM32_ADC_VREF_HAL_CHANNEL ADC_CHANNEL_VREFINT
#ifndef STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VREF_INSTANCE_MASK
#define STM32_ADC_VREF_INSTANCE_MASK STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#endif /* STM32_ADC_VREF_INSTANCE_MASK */
#else
#define STM32_ADC_VREF_HAL_CHANNEL STM32_ADC_INVALID_CHANNEL
#ifndef STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL_AVAILABLE 0
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */
#ifndef STM32_ADC_VREF_INSTANCE_MASK
#define STM32_ADC_VREF_INSTANCE_MASK 0UL
#endif /* STM32_ADC_VREF_INSTANCE_MASK */
#endif /* defined(ADC_CHANNEL_VREFINT_ADC1) */
#endif /* STM32_ADC_VREF_HAL_CHANNEL */

/** @brief Whether the primary VREFINT HAL channel can be used. */
#ifndef STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL_AVAILABLE 1
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */

#ifndef STM32_ADC_VREF_INSTANCE_MASK
#if STM32_ADC_VREF_CHANNEL_AVAILABLE
/** @brief ADC instances that can sample VREFINT. */
#define STM32_ADC_VREF_INSTANCE_MASK STM32_ADC_INTERNAL_DEFAULT_INSTANCE_MASK
#else
/** @brief ADC instances that can sample VREFINT. */
#define STM32_ADC_VREF_INSTANCE_MASK 0UL
#endif /* STM32_ADC_VREF_CHANNEL_AVAILABLE */
#endif /* STM32_ADC_VREF_INSTANCE_MASK */

#ifndef STM32_ADC_VREF_CHANNEL
#if !STM32_ADC_VREF_CHANNEL_AVAILABLE
#define STM32_ADC_VREF_CHANNEL STM32_ADC_INVALID_LOGICAL_CHANNEL
#elif defined(STM32_ADC_VREF_LOGICAL_OVERRIDE)
#define STM32_ADC_VREF_CHANNEL STM32_ADC_VREF_LOGICAL_OVERRIDE
#elif defined(__HAL_ADC_CHANNEL_TO_DECIMAL_NB) || defined(__LL_ADC_CHANNEL_TO_DECIMAL_NB)
#define STM32_ADC_VREF_CHANNEL STM32_ADC_HAL_CHANNEL_TO_LOGICAL(STM32_ADC_VREF_HAL_CHANNEL)
#else
#error "STM32 ADC V2: define STM32_ADC_VREF_LOGICAL_OVERRIDE for this legacy HAL series."
#endif /* !STM32_ADC_VREF_CHANNEL_AVAILABLE */
#endif /* STM32_ADC_VREF_CHANNEL */

#ifndef STM32_ADC_TEMP_ALT_HAL_CHANNEL
#define STM32_ADC_TEMP_ALT_HAL_CHANNEL STM32_ADC_INVALID_CHANNEL
#endif /* STM32_ADC_TEMP_ALT_HAL_CHANNEL */

#ifndef STM32_ADC_TEMP_ALT_INSTANCE_MASK
#define STM32_ADC_TEMP_ALT_INSTANCE_MASK 0UL
#endif /* STM32_ADC_TEMP_ALT_INSTANCE_MASK */

#ifndef STM32_ADC_VBAT_ALT_HAL_CHANNEL
#define STM32_ADC_VBAT_ALT_HAL_CHANNEL STM32_ADC_INVALID_CHANNEL
#endif /* STM32_ADC_VBAT_ALT_HAL_CHANNEL */

#ifndef STM32_ADC_VBAT_ALT_INSTANCE_MASK
#define STM32_ADC_VBAT_ALT_INSTANCE_MASK 0UL
#endif /* STM32_ADC_VBAT_ALT_INSTANCE_MASK */

#ifndef STM32_ADC_VREF_ALT_HAL_CHANNEL
#define STM32_ADC_VREF_ALT_HAL_CHANNEL STM32_ADC_INVALID_CHANNEL
#endif /* STM32_ADC_VREF_ALT_HAL_CHANNEL */

#ifndef STM32_ADC_VREF_ALT_INSTANCE_MASK
#define STM32_ADC_VREF_ALT_INSTANCE_MASK 0UL
#endif /* STM32_ADC_VREF_ALT_INSTANCE_MASK */

#ifndef STM32_ADC_USING_STREAM
#define STM32_ADC_USING_STREAM 0
#endif /* STM32_ADC_USING_STREAM */

#ifndef STM32_ADC_USING_DMA_STREAM
#define STM32_ADC_USING_DMA_STREAM STM32_ADC_USING_STREAM
#endif /* STM32_ADC_USING_DMA_STREAM */


#if defined(STM32_ADC_USING_TRIGGER)
/**
 * @brief Prepared STM32 ADC external trigger fields.
 */
struct stm32_adc_trigger_fields
{
    rt_uint32_t selector; /**< HAL ADC external trigger selector. */
    rt_uint32_t edge;     /**< HAL ADC external trigger edge selector. */
};
#endif /* defined(STM32_ADC_USING_TRIGGER) */

/**
 * @brief STM32 ADC device object.
 *
 * @note The HAL ADC handle must remain the first member. STM32 HAL
 *       callbacks receive an ADC_HandleTypeDef pointer, and this driver
 *       casts it back to struct stm32_adc while handling callbacks.
 */
struct stm32_adc
{
    ADC_HandleTypeDef handle;              /**< HAL ADC handle; keep first for HAL callback owner cast. */
    const char *name;                      /**< Device name. */
    struct stm32_adc_private_cfg config;   /**< Default STM32 backend private configuration. */
    struct rt_adc_device device;           /**< RT-Thread ADC device object. */
#if STM32_ADC_USING_DMA_STREAM
    const struct stm32_dma_config *dma_rx; /**< ADC stream DMA RX configuration. */
    DMA_HandleTypeDef dma_handle;          /**< HAL DMA handle used by stream mode. */
#if defined(STM32_ADC_NEEDS_DMA_CACHE_MAINTENANCE)
    rt_uint32_t *cache_dma_buffer;         /**< Cache-aligned stream DMA buffer when caller buffer is not safe. */
#endif /* defined(STM32_ADC_NEEDS_DMA_CACHE_MAINTENANCE) */
#endif /* STM32_ADC_USING_DMA_STREAM */
#if defined(STM32_ADC_USING_TRIGGER)
    struct stm32_adc_trigger_fields prepared_trigger; /**< Cached trigger selector fields for the next stream config. */
    rt_bool_t prepared_trigger_valid;                 /**< Whether prepared_trigger contains a valid cached selector. */
#endif /* defined(STM32_ADC_USING_TRIGGER) */
};

/*
 * HAL callbacks receive ADC_HandleTypeDef *. The driver casts it back to
 * struct stm32_adc, so the HAL handle must remain the first member.
 */
RT_STATIC_ASSERT(stm32_adc_handle_must_be_first, offsetof(struct stm32_adc, handle) == 0U);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Check whether an ADC peripheral instance matches an instance mask.
 * @param instance ADC peripheral instance.
 * @param mask STM32_ADC_INSTANCE_MASK_x bit mask.
 * @return RT_TRUE if the instance is included, otherwise RT_FALSE.
 */
rt_bool_t stm32_adc_instance_match(ADC_TypeDef *instance, rt_uint32_t mask);

/**
 * @brief Get the HAL ADC channel identifier.
 * @param channel RT-Thread ADC channel identifier.
 * @param hal_channel Pointer to the output HAL ADC channel identifier.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_channel(rt_uint8_t channel, uint32_t *hal_channel);

/**
 * @brief Get the logical channel used to sample STM32 internal VREFINT.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Pointer to the output logical VREFINT channel.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_vref_logical_channel(struct stm32_adc *adc, rt_uint8_t *channel);

/**
 * @brief Get the logical channel used to sample STM32 internal temperature sensor.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Pointer to the output logical temperature-sensor channel.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_tempsensor_logical_channel(struct stm32_adc *adc, rt_uint8_t *channel);

/**
 * @brief Get the logical channel used to sample STM32 internal VBAT divider.
 * @param adc Pointer to the STM32 ADC device object.
 * @param channel Pointer to the output logical VBAT channel.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_vbat_logical_channel(struct stm32_adc *adc, rt_uint8_t *channel);

/**
 * @brief Get one HAL sampling-time value from STM32 private configuration.
 * @param cfg Pointer to the STM32 backend private configuration.
 * @param sampling_time Pointer to the output HAL sampling-time value.
 * @return Operation status.
 */
rt_err_t stm32_adc_get_sampling_time(const struct stm32_adc_private_cfg *cfg, uint32_t *sampling_time);

/**
 * @brief Get the current ADC resolution in bits.
 * @param adc Pointer to the STM32 ADC device object.
 * @return Resolution in bits, or 12 when it cannot be determined.
 */
rt_uint8_t stm32_adc_get_resolution_bits(const struct stm32_adc *adc);

/**
 * @brief Calculate STM32 internal temperature sensor value in degrees Celsius.
 * @param device ADC device handle.
 * @param raw_value Raw ADC sample value from the temperature sensor channel.
 * @param vref_mv Current analog reference voltage in millivolts.
 * @param resolution_bits ADC conversion resolution used for @p raw_value.
 * @param temperature_c Pointer to the output temperature in degrees Celsius.
 * @return Operation status.
 */
rt_err_t stm32_adc_calc_temperature(rt_adc_device_t device, rt_uint32_t raw_value,
                                    rt_uint32_t vref_mv, rt_uint8_t resolution_bits,
                                    rt_int32_t *temperature_c);

/**
 * @brief Calculate VDDA from a raw VREFINT sample.
 * @param device Pointer to the ADC device object.
 * @param vref_mv Pointer to the raw VREFINT sample on input and VDDA millivolts on output.
 * @return Operation status.
 */
rt_err_t stm32_adc_calc_vref_mv(struct rt_adc_device *device, rt_uint32_t *vref_mv);


#if defined(STM32_ADC_USING_TRIGGER)
/**
 * @brief Resolve STM32 ADC trigger selector fields.
 * @param adc Pointer to the STM32 ADC device object.
 * @param cfg Pointer to the ADC trigger configuration, or RT_NULL for software start.
 * @param fields Pointer to the output STM32 trigger fields.
 * @return Operation status.
 */
rt_err_t stm32_adc_trigger_fields_get(struct stm32_adc *adc, const struct rt_adc_trigger_cfg *cfg,
                                      struct stm32_adc_trigger_fields *fields);

/**
 * @brief Preconfigure STM32 ADC trigger selector state for the next stream configuration.
 * @param device Pointer to the ADC framework device object.
 * @param cfg Pointer to the ADC trigger configuration, or RT_NULL for software start.
 * @return Operation status.
 */
rt_err_t stm32_adc_trigger_prepare(struct rt_adc_device *device, const struct rt_adc_trigger_cfg *cfg);
#endif /* defined(STM32_ADC_USING_TRIGGER) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4) */

#endif /* defined(RT_USING_ADC_V2) */

#endif /* __DRV_ADC_V2_PRIVATE_H__ */
