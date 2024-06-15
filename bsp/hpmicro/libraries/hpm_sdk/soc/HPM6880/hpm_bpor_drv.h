/*
 * Copyright (c) 2023 HPMicro
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


#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BPOR_DRV_H */
