/*
 * Copyright (c) 2021 hpmicro
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
    bpor_power_on_cause_wbutn = 0,
    bpor_power_on_cause_safety_violation = 1,
    bpor_power_on_cause_rtc_0 = 2,
    bpor_power_on_cause_rtc_1 = 3,
    bpor_power_on_cause_gpio = 4
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
 * @brief Select power on cause
 *
 * @param[in] ptr BPOR base address
 * @param[in] cause bpor_power_on_cause_t
 */
static inline void bpor_select_power_on_cause(BPOR_Type *ptr, bpor_power_on_cause_t cause)
{
    ptr->POR_SELECT |= 1 << cause;
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
