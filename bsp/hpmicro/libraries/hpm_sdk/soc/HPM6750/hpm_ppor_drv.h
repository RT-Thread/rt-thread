/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PPOR_DRV_H
#define HPM_PPOR_DRV_H
#include "hpm_ppor_regs.h"

typedef enum {
    ppor_reset_brownout = 1 << 0,
    ppor_reset_temperature = 1 << 1,
    ppor_reset_pin = 1 << 2,
    ppor_reset_debug = 1 << 4,
    ppor_reset_security_violation = 1 << 5,
    ppor_reset_jtag = 1 << 6,
    ppor_reset_cpu0_lockup = 1 << 8,
    ppor_reset_cpu1_lockup = 1 << 9,
    ppor_reset_cpu0_request = 1 << 10,
    ppor_reset_cpu1_request = 1 << 11,
    ppor_reset_wdog0 = 1 << 16,
    ppor_reset_wdog1 = 1 << 17,
    ppor_reset_wdog2 = 1 << 18,
    ppor_reset_wdog3 = 1 << 19,
    ppor_reset_pmic_wdog = 1 << 20,
    ppor_reset_software = 1 << 31,
} ppor_reset_source_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * perform software reset in counter * (1/24Mhz) seconds
 */
static inline void ppor_sw_reset(PPOR_Type *ptr, uint32_t counter)
{
    ptr->SOFTWARE_RESET = PPOR_SOFTWARE_RESET_COUNTER_SET(counter); }

/*
 * clear enable reset source according to the given mask
 */
static inline void ppor_reset_mask_clear_source_enable(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_ENABLE &= ~mask;
}

/*
 * set enable reset source according to the given mask
 */
static inline void ppor_reset_mask_set_source_enable(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_ENABLE |= mask;
}

/*
 * set enable reset source
 */
static inline void ppor_reset_set_source_enable(PPOR_Type *ptr, uint32_t reset_sources)
{
    ptr->RESET_ENABLE = reset_sources;
}

/*
 * get enabled reset source
 */
static inline uint32_t ppor_reset_get_enabled_source(PPOR_Type *ptr)
{
    return ptr->RESET_ENABLE;
}

/*
 * get reset status
 */
static inline uint32_t ppor_reset_get_status(PPOR_Type *ptr)
{
    return ptr->RESET_STATUS;
}

/*
 * get reset flags
 */
static inline uint32_t ppor_reset_get_flags(PPOR_Type *ptr)
{
    return ptr->RESET_FLAG;
}

/*
 * clear reset flags
 */
static inline void ppor_reset_clear_flags(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_FLAG |= mask;
}

/*
 * set cold reset
 */
static inline void ppor_reset_set_cold_reset_enable(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_COLD = mask;
}

/*
 * clear cold reset
 */
static inline void ppor_reset_clear_cold_reset_enable(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_COLD &= ~mask;
}

/*
 * set hot reset
 */
static inline void ppor_reset_set_hot_reset_enable(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_HOT = mask;
}

/*
 * clear hot reset
 */
static inline void ppor_reset_clear_hot_reset_enable(PPOR_Type *ptr, uint32_t mask)
{
    ptr->RESET_HOT &= ~mask;
}

#ifdef __cplusplus
}
#endif
#endif
