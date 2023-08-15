/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MONO_DRV_H
#define HPM_MONO_DRV_H

#include "hpm_common.h"
#include "hpm_mono_regs.h"

/**
 *
 * @brief MONO driver APIs
 * @defgroup mono_interface MONO driver APIs
 * @ingroup io_interfaces
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Get counter high
 *
 * @param[in] ptr MONO base address
 *
 * @return counter value high 16 bits
 */
static inline uint16_t mono_get_counter_high(MONO_Type *ptr)
{
    return MONO_MONOH_COUNTER_GET(ptr->MONOH);
}

/**
 * @brief   Get counter low
 *
 * @param[in] ptr MONO base address
 *
 * @return counter value low 32 bits
 */
static inline uint32_t mono_get_counter_low(MONO_Type *ptr)
{
    return MONO_MONOL_COUNTER_GET(ptr->MONOL);
}

/**
 * @brief   Get counter
 *
 * @param[in] ptr MONO base address
 *
 * @return 48 bits counter value
 */
static inline uint64_t mono_get_counter(MONO_Type *ptr)
{
    return (uint64_t)((uint64_t)mono_get_counter_high(ptr) << 32)
        | (uint64_t)mono_get_counter_low(ptr);
}

/**
 * @brief   Get epoch
 *
 * @param[in] ptr MONO Base address
 *
 * @return epoch value 16 bits
 */
static inline uint32_t mono_get_epoch(MONO_Type *ptr)
{
    return MONO_MONOH_EPOCH_GET(ptr->MONOH);
}


/**
 * @brief   Update MONO counter by 1
 *
 * @param[in] ptr MONO base
 */
static inline void mono_update(MONO_Type *ptr)
{
    ptr->MONOL = 1;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_MONO_DRV_H */

