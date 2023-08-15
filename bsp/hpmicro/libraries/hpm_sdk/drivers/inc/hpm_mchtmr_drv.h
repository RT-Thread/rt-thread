/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MCHTMR_DRV_H
#define HPM_MCHTMR_DRV_H
#include "hpm_common.h"
#include "hpm_mchtmr_regs.h"

/**
 * @brief MCHTMR driver APIs
 * @defgroup mchtmr_interface MCHTMR driver APIs
 * @ingroup io_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief mchtmr get counter value
 *
 * @param [in] ptr MCHTMR base address
 */
static inline uint64_t mchtmr_get_count(MCHTMR_Type *ptr)
{
    return (ptr->MTIME & MCHTMR_MTIME_MTIME_MASK) >> MCHTMR_MTIME_MTIME_SHIFT;
}

/**
 * @brief mchtmr set comparator value
 *
 * @param [in] ptr MCHTMR base address
 * @param [in] target comparator target value
 */
static inline void mchtmr_set_compare_value(MCHTMR_Type *ptr, uint64_t target)
{
    ptr->MTIMECMP = MCHTMR_MTIMECMP_MTIMECMP_SET(target);
}

/**
 * @brief mchtmr set delay value
 *
 * @param [in] ptr MCHTMR base address
 * @param [in] delay delay cycles
 */
static inline void mchtmr_delay(MCHTMR_Type *ptr, uint64_t delay)
{
    mchtmr_set_compare_value(ptr, mchtmr_get_count(ptr) + delay);
}

/**
 * @brief initialize mchtmr counter
 *
 * @param [in] ptr MCHTMR base address
 * @param [in] v value to be set
 */
void mchtmr_init_counter(MCHTMR_Type *ptr, uint64_t v);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
#endif /* HPM_MCHTMR_DRV_H */
