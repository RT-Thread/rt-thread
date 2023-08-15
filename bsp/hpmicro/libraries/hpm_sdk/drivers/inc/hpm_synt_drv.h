/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SYNT_DRV_H
#define HPM_SYNT_DRV_H
#include "hpm_common.h"
#include "hpm_synt_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void synt_enable_counter(SYNT_Type *ptr, bool enable)
{
    ptr->GCR = (ptr->GCR & ~(SYNT_GCR_CEN_MASK)) | SYNT_GCR_CEN_SET(enable);
}

static inline void synt_reset_counter(SYNT_Type *ptr)
{
    ptr->GCR |= SYNT_GCR_CRST_MASK;
    ptr->GCR &= ~SYNT_GCR_CRST_MASK;
}

static inline hpm_stat_t synt_set_comparator(SYNT_Type *ptr,
                                       uint8_t cmp_index,
                                       uint32_t count)
{
    if (cmp_index > SYNT_CMP_3) {
        return status_invalid_argument;
    }
    ptr->CMP[cmp_index] = SYNT_CMP_CMP_SET(count);
    return status_success;
}

static inline void synt_set_reload(SYNT_Type *ptr, uint32_t reload_count)
{
    ptr->RLD = SYNT_RLD_RLD_SET(reload_count);
}

static inline uint32_t synt_get_current_count(SYNT_Type *ptr)
{
    return (ptr->CNT & SYNT_CNT_CNT_MASK) >> SYNT_CNT_CNT_SHIFT;
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_SYNT_DRV_H */
