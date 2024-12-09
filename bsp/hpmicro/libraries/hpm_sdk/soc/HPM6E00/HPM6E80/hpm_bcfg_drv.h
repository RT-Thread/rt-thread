/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BCFG_DRV_H
#define HPM_BCFG_DRV_H

#include "hpm_common.h"
#include "hpm_bcfg_regs.h"

/**
 *
 * @brief BCFG driver APIs
 * @defgroup bcfg_interface BCFG driver APIs
 * @ingroup io_interfaces
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief enable power save mode
 *
 * @param[in] ptr base address
 */
static inline void bcfg_vbg_enable_power_save_mode(BCFG_Type *ptr)
{
    ptr->VBG_CFG |= BCFG_VBG_CFG_POWER_SAVE_MASK;
}

/**
 * @brief disable power save mode
 *
 * @param[in] ptr base address
 */
static inline void bcfg_vbg_disable_power_save_mode(BCFG_Type *ptr)
{
    ptr->VBG_CFG &= ~BCFG_VBG_CFG_POWER_SAVE_MASK;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BCFG_DRV_H */

