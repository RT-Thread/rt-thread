/*
 * Copyright 2023 NXP
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

/*!@brief TRDC base table */
#define TRDC_BASE_PTRS \
    {                  \
        TRDC           \
    }
/* @} */

#define TRDC_MBC_MEM_GLBCFG_NBLKS_MASK      TRDC_MBC_INDEX_MBC_MEM_GLBCFG_NBLKS_MASK
#define TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_MASK  TRDC_MBC_INDEX_MBC_MEM_GLBCFG_SIZE_LOG2_MASK
#define TRDC_MBC_MEM_GLBCFG_SIZE_LOG2_SHIFT TRDC_MBC_INDEX_MBC_MEM_GLBCFG_SIZE_LOG2_SHIFT
#define TRDC_MBC_NSE_BLK_CLR_ALL_MEMSEL     TRDC_MBC_INDEX_MBC_NSE_BLK_CLR_ALL_MEMSEL
#define TRDC_MBC_NSE_BLK_CLR_ALL_DID_SEL    TRDC_MBC_INDEX_MBC_NSE_BLK_CLR_ALL_DID_SEL0

/*!@brief TRDC feature */
#define FSL_FEATURE_TRDC_DOMAIN_COUNT 1

/*!@brief TRDC base address convert macro */
#define TRDC_MBC_COUNT 1
#define TRDC_MBC_OFFSET(x)  0x0
#define TRDC_MBC_ARRAY_STEP 0U

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
