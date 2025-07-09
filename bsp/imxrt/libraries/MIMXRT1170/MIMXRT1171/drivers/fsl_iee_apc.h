/*
 * Copyright 2020-2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_IEE_APC_H_
#define FSL_IEE_APC_H_

#include "fsl_common.h"

/*!
 * @addtogroup ieer
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief IEE_APC driver version. Version 2.0.2.
 *
 * Current version: 2.0.2
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version
 * - Version 2.0.1
 *   - Fixed MISRA issues.
 * - Version 2.0.2
 *   - Update to newer version of implementation in HW.
 */
#define FSL_IEE_APC_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*! @} */

/*! @brief APC IEE regions. */
typedef enum _iee_apc_region
{
    kIEE_APC_Region0 = 0U, /*!< APC IEE region 0 */
    kIEE_APC_Region1 = 1U, /*!< APC IEE region 1 */
    kIEE_APC_Region2 = 2U, /*!< APC IEE region 2 */
    kIEE_APC_Region3 = 3U, /*!< APC IEE region 3 */
    kIEE_APC_Region4 = 4U, /*!< APC IEE region 4 */
    kIEE_APC_Region5 = 5U, /*!< APC IEE region 5 */
    kIEE_APC_Region6 = 6U, /*!< APC IEE region 6 */
    kIEE_APC_Region7 = 7U  /*!< APC IEE region 7 */
} iee_apc_region_t;

/*! @brief APC IEE domains. */
typedef enum _apc_iee_domain
{
    kIEE_APC_Domain0 = 0U, /*!< APC IEE region 0 */
    kIEE_APC_Domain1 = 1U  /*!< APC IEE region 1 */
} iee_apc_domain_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enable the APC IEE Region setting.
 *
 * This function enables IOMUXC LPSR GPR and APC IEE for setting the region.
 *
 * @param base APC IEE peripheral address.
 */
void IEE_APC_GlobalEnable(IEE_APC_Type *base);

/*!
 * @brief Disables the APC IEE Region setting.
 *
 * This function disables IOMUXC LPSR GPR and APC IEE for setting the region.
 *
 * @param base APC IEE peripheral address.
 */
void IEE_APC_GlobalDisable(IEE_APC_Type *base);

/*!
 * @brief Sets the APC IEE Memory Region Descriptors.
 *
 * This function configures APC IEE Memory Region Descriptor according to region configuration structure.
 *
 * @param base APC IEE peripheral address.
 * @param region Selection of the APC IEE region to be configured.
 * @param startAddr Start encryption adress for the selected APC IEE region.
 * @param endAddr End encryption adress for the selected APC IEE region.
 */
status_t IEE_APC_SetRegionConfig(IEE_APC_Type *base, iee_apc_region_t region, uint32_t startAddr, uint32_t endAddr);


#if !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u))
/*!
 * @brief Lock the APC IEE configuration.
 *
 * This function locks writting to APC IEE encryption region setting registers.
 * Only system reset can clear Lock bit
 *
 * @param base APC IEE peripheral address.
 * @param region Selection of the APC IEE region to be locked.
 * @param domain The ID is driven by TRDC
 */
status_t IEE_APC_LockRegionConfig(IEE_APC_Type *base, iee_apc_region_t region, uint8_t domain);
#endif /* !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)) */

#if !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u))
/*!
 * @brief Set access control of the APC IEE.
 *
 * This function configure APC IEE encryption region access control settings.
 *
 * @param base APC IEE peripheral address.
 * @param region Selection of the APC IEE region to be locked.
 * @param allowNonSecure Allow nonsecure mode access
 * @param allowUser Allow user mode access
 */
status_t IEE_APC_SetAccessControl(IEE_APC_Type *base, iee_apc_region_t region, bool allowNonSecure, bool allowUser);
#endif /* !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)) */


#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
/*!
 * @brief Lock the LPSR GPR and APC IEE configuration.
 *
 * This function locks writting to IOMUXC LPSR GPR and APC IEE encryption region setting registers.
 * Only system reset can clear the LPSR GPR and APC IEE-RDC_D0/1 Lock bit
 *
 * @param base APC IEE peripheral address.
 * @param region Selection of the APC IEE region to be locked.
 * @param domain Core domain ID
 */
status_t IEE_APC_LockRegionConfig(IEE_APC_Type *base, iee_apc_region_t region, iee_apc_domain_t domain);
#endif

/*!
 * @brief Enable the IEE encryption/decryption and can lock this setting.
 *
 * This function enables encryption/decryption by writting to IOMUXC LPSR GPR.
 *
 * @param base APC IEE peripheral address.
 * @param region Selection of the APC IEE region to be enabled.
 */
void IEE_APC_RegionEnable(IEE_APC_Type *base, iee_apc_region_t region);

#if !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u))
/*!
 * @brief Disable the IEE encryption/decryption for specific region.
 *
 * This function disables encryption/decryption by writting to IOMUXC LPSR GPR.
 *
 * @param base APC IEE peripheral address.
 * @param region Selection of the APC IEE region to be enabled.
 */
void IEE_APC_RegionDisable(IEE_APC_Type *base, iee_apc_region_t region);
#endif /* !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)) */

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* FSL_IEE_APC_H_ */
