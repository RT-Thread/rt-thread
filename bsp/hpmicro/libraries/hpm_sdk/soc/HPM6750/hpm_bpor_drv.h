/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BPOR_DRV_H
#define HPM_BPOR_DRV_H

#include "hpm_common.h"
#include "hpm_bpor_regs.h"

/**
 *
 * @brief BPOR driver APIs
 * @defgroup bpor_interface BPOR driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

/** @brief Define BPOR power on cause */
typedef enum {
    bpor_power_on_cause_wbutn = 1 << 0,
    bpor_power_on_cause_safety_violation = 1 << 1,
    bpor_power_on_cause_rtc_0 = 1 << 2,
    bpor_power_on_cause_rtc_1 = 1 << 3,
    bpor_power_on_cause_gpio = 1 << 4
} bpor_power_on_cause_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get power on cause
 *
 * @param[in] ptr BPOR base address
 * @retval POR_CAUSE register value
 */
static inline uint32_t bpor_get_power_on_cause(BPOR_Type *ptr)
{
    return ptr->POR_CAUSE;
}

/**
 * @brief Clear power on cause
 *
 * @param[in] ptr BPOR base address
 * @param[in] mask cause status to be cleared
 */
static inline void bpor_clear_power_on_cause(BPOR_Type *ptr, uint8_t mask)
{
    ptr->POR_CAUSE |= mask;
}

/**
 * @brief enable power on cause
 *
 * @param[in] ptr BPOR base address
 * @param[in] cause wake up cause to be enabled
 */
static inline void bpor_enable_power_on_cause(BPOR_Type *ptr, bpor_power_on_cause_t cause)
{
    ptr->POR_SELECT |= cause;
}

/**
 * @brief disable power on cause
 *
 * @param[in] ptr BPOR base address
 * @param[in] cause wake up cause to be disabled
 */
static inline void bpor_disable_power_on_cause(BPOR_Type *ptr, bpor_power_on_cause_t cause)
{
    ptr->POR_SELECT &= ~cause;
}

/**
 * @brief Set power on cause
 *
 * @param[in] ptr BPOR base address
 * @param[in] cause wake up cause to be used
 */
static inline void bpor_set_power_on_cause(BPOR_Type *ptr, uint8_t cause)
{
    ptr->POR_SELECT = (ptr->POR_SELECT & ~BPOR_POR_SELECT_SELECT_MASK) | cause;
}

/**
 * @brief Enable register value retention when power down occurs
 *
 * @param[in] ptr BPOR base address
 */
static inline void bpor_enable_reg_value_retention(BPOR_Type *ptr)
{
    ptr->POR_CONFIG |= BPOR_POR_CONFIG_RETENTION_MASK;
}

/**
 * @brief Disable register value retention when power down occurs
 *
 * @param[in] ptr BPOR base address
 */
static inline void bpor_disable_reg_value_retention(BPOR_Type *ptr)
{
    ptr->POR_CONFIG &= ~BPOR_POR_CONFIG_RETENTION_MASK;
}

/**
 * @brief Set power down counter
 *
 * @param[in] ptr BPOR base address
 * @param[in] counter counter value
 */
static inline void bpor_set_power_down_counter(BPOR_Type *ptr, uint16_t counter)
{
    ptr->POR_CONTROL = BPOR_POR_CONTROL_COUNTER_SET(counter);
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BPOR_DRV_H */
