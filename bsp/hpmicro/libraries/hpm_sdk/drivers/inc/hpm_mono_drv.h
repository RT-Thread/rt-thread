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
 * @brief   Get counter
 *
 * @param[in] ptr MONO base address
 *
 * @return 64 bits counter value
 */
static inline uint64_t mono_get_counter(MONO_Type *ptr)
{
    return (uint64_t)((uint64_t)((ptr->MONOH) << 32))
        | (uint64_t)((ptr->MONOL));
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

