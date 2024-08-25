/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_TRDC_SOC_H_
#define _FSL_TRDC_SOC_H_

#include "fsl_common.h"

/*!
 * @addtogroup trdc_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 /* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.trdc_soc"
#endif

/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.0. */
#define FSL_TRDC_SOC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#define TRDC_MBC_MEM_GLBCFG_NBLKS_MASK      0x000003FFUL
#define TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_MASK  0x001F0000UL
#define TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_SHIFT 16U
#define TRDC_MBC_NSE_BLK_CLR_ALL_MEMSEL(x)  (((uint32_t)(x) & 0xFUL) << 8U)
#define TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL(x) (((uint32_t)(x) & 0x1UL) << 16U)

/*!@brief TRDC feature */
#define FSL_FEATURE_TRDC_DOMAIN_COUNT 1

/*!@brief TRDC base address convert macro */
#define TRDC_MBC_COUNT 1
#define TRDC_MBC_OFFSET(x)  0x0000 /* MBC register offset in TRDC_Type structure. */
#define TRDC_MBC_ARRAY_STEP 0U     /* Offset between two MBC control block, useless if there is only one. */

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_TRDC_SOC_H_ */
