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
 * @brief enable VBAT LP mode
 *
 * @param[in] ptr base address
 */
static inline void bcfg_vbg_enable_lp_mode(BCFG_Type *ptr)
{
    ptr->VBG_CFG |= BCFG_VBG_CFG_LP_MODE_MASK;
}

/**
 * @brief disable VBAT LP mode
 *
 * @param[in] ptr base address
 */
static inline void bcfg_vbg_disable_lp_mode(BCFG_Type *ptr)
{
    ptr->VBG_CFG &= ~BCFG_VBG_CFG_LP_MODE_MASK;
}

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

/**
 * @brief set ldo voltage
 *
 * @param[in] ptr base address
 * @param[in] voltage target voltage
 */
static inline void bcfg_ldo_set_voltage(BCFG_Type *ptr, uint16_t voltage)
{
    ptr->LDO_CFG = (ptr->LDO_CFG & ~(BCFG_LDO_CFG_VOLT_MASK)) | BCFG_LDO_CFG_VOLT_SET(voltage);
}

/**
 * @brief enable ldo
 *
 * @param[in] ptr base address
 */
static inline void bcfg_ldo_enable(BCFG_Type *ptr)
{
    ptr->LDO_CFG |= BCFG_LDO_CFG_ENABLE_MASK;
}

/**
 * @brief disable ldo
 *
 * @param[in] ptr base address
 */
static inline void bcfg_ldo_disable(BCFG_Type *ptr)
{
    ptr->LDO_CFG &= ~BCFG_LDO_CFG_ENABLE_MASK;
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BCFG_DRV_H */

