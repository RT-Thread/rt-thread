/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-21     wdfk-prog    add stm32 adc v2 driver declarations
 */

/**
 * @file drv_adc_v2.h
 * @brief STM32 ADC V2 driver declarations.
 */

#ifndef __DRV_ADC_V2_H__
#define __DRV_ADC_V2_H__

#include <rtconfig.h>

#if defined(RT_USING_ADC_V2)
#include <board.h>
#include <rtdevice.h>
#include <drivers/adc_v2.h>

/**
 * @brief STM32 ADC backend private device configuration.
 *
 * @note The fields map directly to STM32 HAL ADC initialization values. Use
 *       ADC_RESOLUTION_xxx, ADC_OVERSAMPLING_RATIO_xxx, and
 *       ADC_RIGHTBITSHIFT_xxx macros from the active STM32 HAL headers when
 *       the corresponding feature exists. The configuration should be updated
 *       before opening the ADC device.
 */
struct stm32_adc_private_cfg
{
    rt_uint32_t sampling_time;             /**< HAL ADC sampling-time value; 0 uses ADC_DEFAULT_SAMPLING_TIME. */
    rt_uint32_t resolution;                /**< HAL ADC resolution value; 0 uses ADC_DEFAULT_RESOLUTION. */
    rt_uint32_t data_align;                /**< HAL ADC data-alignment value; 0 uses ADC_DEFAULT_DATA_ALIGN. */
    rt_uint8_t input_modes;                /**< Bit mask of enum rt_adc_input_mode values; 0 uses single-ended input. */
    rt_uint8_t reserved[3];                /**< Reserved for alignment and future STM32 backend options. */
    rt_uint32_t oversampling_ratio;        /**< HAL ADC oversampling ratio; 0 disables hardware oversampling. */
    rt_uint32_t oversampling_right_shift;  /**< HAL ADC oversampling right shift; 0 uses no right shift. */
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Initialize and register STM32 ADC devices.
 * @return Operation status.
 */
int stm32_adc_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* defined(RT_USING_ADC_V2) */

#endif /* __DRV_ADC_V2_H__ */
