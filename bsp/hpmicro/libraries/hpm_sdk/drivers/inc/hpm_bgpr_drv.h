/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BGPR_DRV_H
#define HPM_BGPR_DRV_H

#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_bgpr_regs.h"

/**
 *
 * @brief BGPR driver APIs
 * @defgroup bgpr_interfaces BGPR driver APIs
 * @ingroup io_interfaces
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * @brief   read BGPR value
 *
 * @note the bgpr_index range is 0 ~ (GPR count of BGPR - 1)
 *
 * @param ptr BGPR base address
 * @param bgpr_index BGPR GPR index
 * @param bgpr_val  the BGPR GPR value pointer
 *
 * @return hpm_stat_t status_success if read bgpr without any error
 */
static inline hpm_stat_t bgpr_read32(BGPR_Type *ptr, uint8_t bgpr_index, uint32_t *bgpr_val)
{
    hpm_stat_t stat = status_invalid_argument;
    uint8_t gpr_count = sizeof(ptr->GPR) / sizeof(uint32_t);
    if (bgpr_index < gpr_count) {
        (*bgpr_val) = ptr->GPR[bgpr_index];
        stat = status_success;
    }
    return stat;
}

/**
 * @brief   write BGPR value
 *
 * @note the bgpr_index range is 0 ~ (GPR count of BGPR - 1)
 *
 * @param ptr BGPR base address
 * @param bgpr_index BGPR GPR index
 * @param bgpr_val  the BGPR GPR value
 *
 * @return hpm_stat_t status_success if write bgpr without any error
 */
static inline hpm_stat_t bgpr_write32(BGPR_Type *ptr, uint8_t bgpr_index, uint32_t bgpr_val)
{
    hpm_stat_t stat = status_invalid_argument;
    uint8_t gpr_count = sizeof(ptr->GPR) / sizeof(uint32_t);
    if (bgpr_index < gpr_count) {
        ptr->GPR[bgpr_index] = bgpr_val;
        stat = status_success;
    }
    return stat;
}

/**
 * @}
 */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif
