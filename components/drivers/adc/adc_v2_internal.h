/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file adc_v2_internal.h
 * @brief Internal ADC V2 framework declarations.
 */

#ifndef __ADC_V2_INTERNAL_H__
#define __ADC_V2_INTERNAL_H__

#include <rtconfig.h>
#include <drivers/adc_v2.h>

#if defined(RT_ADC_USING_TRIGGER)
/**
 * @brief Initialize the cached ADC trigger state to the default software-started mode.
 * @param device Pointer to the ADC device object.
 */
void adc_trigger_init(rt_adc_device_t device);

/**
 * @brief Preconfigure the active device-level ADC trigger before hardware configuration.
 * @param device Pointer to the ADC device object.
 * @return RT_EOK on success, otherwise an RT-Thread error code.
 */
rt_err_t adc_trigger_preconfig(rt_adc_device_t device);

/**
 * @brief Get the active device-level ADC trigger configuration.
 * @param device Pointer to the ADC device object.
 * @return Pointer to the cached trigger configuration, or RT_NULL when no hardware trigger is configured.
 */
const struct rt_adc_trigger_cfg *adc_trigger_active_get(rt_adc_device_t device);

/**
 * @brief Trigger-source lifecycle actions used after ADC hardware is armed.
 */
enum adc_trigger_source_action
{
    ADC_TRIGGER_SOURCE_START = 0, /**< Start the active trigger source. */
    ADC_TRIGGER_SOURCE_STOP       /**< Stop the previously started trigger source. */
};

/**
 * @brief Control the active trigger source around an armed ADC conversion path.
 * @param device Pointer to the ADC device object.
 * @param action Trigger-source lifecycle action.
 * @param started Pointer to the trigger-start state.
 * @param current_result Transfer result before trigger stop, ignored for start.
 * @return For start, trigger-source start result; for stop, @p current_result unless trigger stop is the first
 *         observed failure.
 */
rt_err_t adc_trigger_source_control(rt_adc_device_t device, enum adc_trigger_source_action action,
                                    rt_bool_t *started, rt_err_t current_result);

#endif /* defined(RT_ADC_USING_TRIGGER) */

#endif /* __ADC_V2_INTERNAL_H__ */
