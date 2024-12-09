/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_TSNS_DRV_H
#define HPM_TSNS_DRV_H

#include "hpm_common.h"
#include "hpm_tsns_regs.h"

/**
 * @brief TSNS driver APIs
 * @defgroup tsns_interface TSNS driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/
#define TSNS_TEMP_SCALE 256

typedef enum {
    tsns_clear_min = TSNS_FLAG_RECORD_MIN_CLR_MASK,
    tsns_clear_max = TSNS_FLAG_RECORD_MAX_CLR_MASK,
    tsns_clear_under_temp = TSNS_FLAG_UNDER_TEMP_MASK,
    tsns_clear_over_temp = TSNS_FLAG_OVER_TEMP_MASK,
    tsns_clear_irq = TSNS_FLAG_IRQ_MASK,
} tsns_clear_type_mask_t;

typedef enum {
    tsns_event_irq = 0,
    tsns_event_reset,
} tsns_event_t;

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief  Enable temperature sensor
 *
 * @param ptr base address
 */
static inline void tsns_enable(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_ENABLE_MASK;
}

/**
 * @brief   Disable temperature sensor
 *
 * @param ptr base address
 */
static inline void tsns_disable(TSNS_Type *ptr)
{
    ptr->CONFIG &= ~TSNS_CONFIG_ENABLE_MASK;
}

/**
 * @brief   Check if current temperature value is valid or not
 *
 * @param ptr base address
 *
 * @return  true the value is valid
 */
static inline bool tsns_temperature_is_valid(TSNS_Type *ptr)
{
    return ptr->STATUS & TSNS_STATUS_VALID_MASK;
}

/**
 * @brief   Get maximum measured temperature in raw
 *
 * @param ptr base address
 *
 * @return raw maximum temperature value scaled by TSNS_TEMP_SCALE
 */
static inline int32_t tsns_get_max_temp_raw(TSNS_Type *ptr)
{
    return TSNS_TMAX_T_GET(ptr->TMAX);
}

/**
 * @brief    Get minimum measured temperature in raw
 *
 * @param ptr base address
 *
 * @return  raw minimum temperature value scaled by TSNS_TEMP_SCALE
 */
static inline int32_t tsns_get_min_temp_raw(TSNS_Type *ptr)
{
    return TSNS_TMIN_T_GET(ptr->TMIN);
}

/**
 * @brief   Get current temperature in raw
 *
 * @param ptr base address
 *
 * @return  raw temperature value scaled by TSNS_TEMP_SCALE
 */
static inline int32_t tsns_get_current_temp_in_raw(TSNS_Type *ptr)
{
    while (!tsns_temperature_is_valid(ptr)) {
        ;
    }
    return TSNS_T_T_GET(ptr->T);
}

/**
 * @brief   Get current temperature in celsius degree
 *
 * @param ptr base address
 *
 * @return  current temperature in celsius degree
 */
static inline float tsns_get_current_temp(TSNS_Type *ptr)
{
    return (float)(((int32_t)tsns_get_current_temp_in_raw(ptr) / TSNS_TEMP_SCALE));
}

/**
 * @brief   Get temperature age
 *
 * @param ptr base address
 *
 * @return  temperature age
 */
static inline uint32_t tsns_get_temp_age(TSNS_Type *ptr)
{
    return TSNS_AGE_AGE_GET(ptr->AGE);
}

/**
 * @brief   Set temperature high limit to trigger rest
 *
 * @param ptr base address
 * @param high temperature value
 */
static inline void tsns_set_reset_threshold_high(TSNS_Type *ptr, uint32_t high)
{
    ptr->UPPER_LIM_IRQ = TSNS_UPPER_LIM_RST_T_SET(high);
}

/**
 * @brief   Set temperature low limit to trigger reset
 *
 * @param ptr base address
 * @param low temperature value
 */
static inline void tsns_set_reset_threshold_low(TSNS_Type *ptr, uint32_t low)
{
    ptr->LOWER_LIM_IRQ = TSNS_LOWER_LIM_RST_T_SET(low);
}

/**
 * @brief   Enable temperature limit to trigger irq
 *
 * @param ptr base address
 */
static inline void tsns_enable_limit_trigger_reset(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_RST_EN_MASK;
}

/**
 * @brief   Disable temperature limit to trigger irq
 *
 * @param ptr base address
 */
static inline void tsns_disable_limit_trigger_irq(TSNS_Type *ptr)
{
    ptr->CONFIG &= ~TSNS_CONFIG_RST_EN_MASK;
}

/**
 * @brief   Set temperature high limit to trigger irq
 *
 * @param ptr base address
 * @param high temperature value
 */
static inline void tsns_set_irq_threshold_high(TSNS_Type *ptr, uint32_t high)
{
    ptr->UPPER_LIM_IRQ = TSNS_UPPER_LIM_IRQ_T_SET(high);
}

/**
 * @brief   Set temperature low limit to trigger irq
 *
 * @param ptr base address
 * @param low temperature value
 */
static inline void tsns_set_irq_threshold_low(TSNS_Type *ptr, uint32_t low)
{
    ptr->LOWER_LIM_IRQ = TSNS_LOWER_LIM_IRQ_T_SET(low);
}

/**
 * @brief   Enable temperature limit to trigger irq
 *
 * @param ptr base address
 */
static inline void tsns_enable_limit_trigger_irq(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_IRQ_EN_MASK;
}

/**
 * @brief   Set validity of current measured temperature in 24Mhz clock cycles
 *
 * @param ptr base address
 * @param validity  clock cycle count
 */
static inline void tsns_set_validity(TSNS_Type *ptr, uint32_t validity)
{
    ptr->VALIDITY = TSNS_VALIDITY_VALIDITY_SET(validity);
}

/**
 * @brief   Set temperature limit to trigger irq
 *
 * @param ptr base address
 * @param high high temperature
 * @param low low temperature
 */
static inline void tsns_config_irq_threshold(TSNS_Type *ptr, uint32_t high, uint32_t low)
{
    tsns_set_irq_threshold_low(ptr, low);
    tsns_set_irq_threshold_high(ptr, high);
}

/**
 * @brief   Set temperature limit to trigger reset
 *
 * @param ptr base address
 * @param high high temperature
 * @param low low temperature
 */
static inline void tsns_config_reset_threshold(TSNS_Type *ptr, uint32_t high, uint32_t low)
{
    tsns_set_reset_threshold_low(ptr, low);
    tsns_set_reset_threshold_high(ptr, high);
}

/**
 * @brief   Enable compare max temperature
 *
 * @param ptr base address
 */
static inline void tsns_enable_compare_max(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_COMPARE_MAX_EN_MASK;
}

/**
 * @brief   Enable compare min temperature
 *
 * @param ptr base address
 */
static inline void tsns_enable_compare_min(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_COMPARE_MIN_EN_MASK;
}

/**
 * @brief   Disable compare max temperature
 *
 * @param ptr base address
 */
static inline void tsns_disable_compare_max(TSNS_Type *ptr)
{
    ptr->CONFIG &= ~TSNS_CONFIG_COMPARE_MAX_EN_MASK;
}

/**
 * @brief   Disable compare min temperature
 *
 * @param ptr base address
 */
static inline void tsns_disable_compare_min(TSNS_Type *ptr)
{
    ptr->CONFIG &= ~TSNS_CONFIG_COMPARE_MIN_EN_MASK;
}

/**
 * @brief   Set measurement speed
 *
 * @param ptr base address
 * @param speed speed from 24-255
 */
static inline void tsns_set_speed(TSNS_Type *ptr, uint8_t speed)
{
    assert(speed >= 24);
    ptr->CONFIG = (ptr->CONFIG & ~TSNS_CONFIG_SPEED_MASK) | TSNS_CONFIG_SPEED_SET(speed);
}

/**
 * @brief   Set average
 *
 * @param ptr base address
 * @param average range 0 - 7 (0: 2^0 = 1 means measure once and return  ... 2: 2^2 = 4 means measure 4 times and average)
 */
static inline void tsns_set_average(TSNS_Type *ptr, uint8_t average)
{
    ptr->CONFIG = (ptr->CONFIG & ~TSNS_CONFIG_AVERAGE_MASK) | TSNS_CONFIG_AVERAGE_SET(average);
}

/**
 * @brief   Enable Async mode
 *
 * @param ptr base address
 */
static inline void tsns_enable_async_mode(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_ASYNC_MASK;
}

/**
 * @brief   Disable Async mode and switch to active mode
 *
 * @param ptr base address
 */
static inline void tsns_disable_async_mode(TSNS_Type *ptr)
{
    ptr->CONFIG &= ~TSNS_CONFIG_ASYNC_MASK;
}

/**
 * @brief   Enable trigger mode
 *
 * @param ptr base address
 */
static inline void tsns_enable_trigger_mode(TSNS_Type *ptr)
{
    ptr->CONFIG &= ~TSNS_CONFIG_CONTINUOUS_MASK;
}

/**
 * @brief   Enable continuous mode
 *
 * @param ptr base address
 */
static inline void tsns_enable_continuous_mode(TSNS_Type *ptr)
{
    ptr->CONFIG |= TSNS_CONFIG_CONTINUOUS_MASK;
}

/**
 * @brief   trigger measurement
 *
 * @param ptr base address
 */
static inline void tsns_trigger_measurement(TSNS_Type *ptr)
{
    uint32_t tmp = ptr->CONFIG;
    ptr->CONFIG &= ~TSNS_CONFIG_CONTINUOUS_MASK;
    ptr->STATUS |= TSNS_STATUS_TRIGGER_MASK;
    ptr->CONFIG = tmp;
}

/**
 * @brief   clear tsns flag or recorded data
 *
 * @param ptr base address
 * @param mask flag or data to be cleared
 */
static inline void tsns_clear_with_mask(TSNS_Type *ptr, tsns_clear_type_mask_t mask)
{
    ptr->FLAG |= mask;
}


/**
 * @brief   configure low temperature limite to trigger event
 *
 * @param ptr base address
 * @param low temperature value
 * @param e event type, tsns_event_irq or tsns_event_reset
 */
void tsns_configure_low_limit_event(TSNS_Type *ptr, int32_t low, tsns_event_t e);

/**
 * @brief   configure high temperature limite to trigger event
 *
 * @param ptr base address
 * @param high temperature value
 * @param e event type, tsns_event_irq or tsns_event_reset
 */
void tsns_configure_high_limit_event(TSNS_Type *ptr, int32_t high, tsns_event_t e);

/**
 * @brief   configure temperature limite to trigger event
 *
 * @param ptr base address
 * @param high temperature value
 * @param low temperature value
 * @param e event type, tsns_event_irq or tsns_event_reset
 */
void tsns_configure_limit_event(TSNS_Type *ptr, int32_t high, int32_t low, tsns_event_t e);

#ifdef __cplusplus
}
#endif
/**
 * @}
 *
 */
#endif /* HPM_TSNS_DRV_H */
