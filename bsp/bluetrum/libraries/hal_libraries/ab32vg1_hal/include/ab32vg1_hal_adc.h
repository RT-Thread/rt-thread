/*
 * Copyright (c) 2020-2021, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_ADC_H__
#define AB32VG1_HAL_ADC_H__

#include "ab32vg1_hal_def.h"

/**
 * @defgroup ADC_channels
 * @{
 */
#define ADC_CHANNEL_0       (1u <<  0)
#define ADC_CHANNEL_1       (1u <<  1)
#define ADC_CHANNEL_2       (1u <<  2)
#define ADC_CHANNEL_3       (1u <<  3)
#define ADC_CHANNEL_4       (1u <<  4)
#define ADC_CHANNEL_5       (1u <<  5)
#define ADC_CHANNEL_6       (1u <<  6)
#define ADC_CHANNEL_7       (1u <<  7)
#define ADC_CHANNEL_8       (1u <<  8)
#define ADC_CHANNEL_9       (1u <<  9)
#define ADC_CHANNEL_10      (1u << 10)
#define ADC_CHANNEL_11      (1u << 11)
#define ADC_CHANNEL_12      (1u << 12)
#define ADC_CHANNEL_13      (1u << 13)
#define ADC_CHANNEL_14      (1u << 14)
#define ADC_CHANNEL_15      (1u << 15)
/**
 * @}
 * 
 */

/**
 * @brief Enable ADC
 * 
 * @param enable 
 */
void hal_adc_enable(uint8_t enable);

/**
 * @brief Starts conversion of the channels
 * 
 * @param channel @ref ADC_channels
 */
void hal_adc_start(uint32_t channel);

/**
 * @brief Poll for conversion complete
 * 
 * @param timeout Timeout value in millisecond
 * @return hal_error_t 
 */
hal_error_t hal_adc_poll_for_conversion(uint32_t timeout);

#endif
