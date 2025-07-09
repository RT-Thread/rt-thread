/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_IEE_H_
#define FSL_IEE_H_

#include "fsl_common.h"

/*!
 * @addtogroup iee
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief IEE driver version. Version 2.1.1.
 *
 * Current version: 2.1.1
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version
 * - Version 2.1.0
 *   - Add region lock function IEE_LockRegionConfig() and driver clock control
 * - Version 2.1.1
 *   - Fixed MISRA issues.
 * - Version 2.2.0
 *   - Add ELE (EdgeLock Enclave) key provisioning feature.
 */
#define FSL_IEE_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*! @} */

/*! @brief IEE region. */
typedef enum _iee_region
{
    kIEE_Region0 = 0U, /*!< IEE region 0 */
    kIEE_Region1 = 1U, /*!< IEE region 1 */
    kIEE_Region2 = 2U, /*!< IEE region 2 */
    kIEE_Region3 = 3U, /*!< IEE region 3 */
    kIEE_Region4 = 4U, /*!< IEE region 4 */
    kIEE_Region5 = 5U, /*!< IEE region 5 */
    kIEE_Region6 = 6U, /*!< IEE region 6 */
    kIEE_Region7 = 7U  /*!< IEE region 7 */
} iee_region_t;

/*! @brief IEE AES enablement/bypass. */
typedef enum _iee_aes_bypass
{
    kIEE_AesUseMdField = 0U, /*!< AES encryption/decryption enabled */
    kIEE_AesBypass     = 1U  /*!< AES encryption/decryption bypass */
} iee_aes_bypass_t;

/*! @brief IEE AES mode. */
typedef enum _iee_aes_mode
{
    kIEE_ModeNone            = 0U, /*!< AES NONE mode */
    kIEE_ModeAesXTS          = 1U, /*!< AES XTS mode */
    kIEE_ModeAesCTRWAddress  = 2U, /*!< AES CTR w address binding mode */
    kIEE_ModeAesCTRWOAddress = 3U, /*!< AES CTR w/o address binding mode */
    kIEE_ModeAesCTRkeystream = 4U  /*!< AES CTR keystream only */
} iee_aes_mode_t;

/*! @brief IEE AES key size. */
typedef enum _iee_aes_key_size
{
    kIEE_AesCTR128XTS256 = 0U, /*!< AES 128 bits (CTR), 256 bits (XTS) */
    kIEE_AesCTR256XTS512 = 1U  /*!< AES 256 bits (CTR), 512 bits (XTS) */
} iee_aes_key_size_t;

/*! @brief IEE AES key number. */
typedef enum _iee_aes_key_num
{
    kIEE_AesKey1 = 1U, /*!< AES Key 1 */
    kIEE_AesKey2 = 2U  /*!< AES Key 2 */
} iee_aes_key_num_t;

/*! @brief IEE configuration structure. */
typedef struct _iee_config
{
    iee_aes_bypass_t bypass;    /*!< AES encryption/decryption bypass */
    iee_aes_mode_t mode;        /*!< AES mode */
    iee_aes_key_size_t keySize; /*!< size of AES key */
    uint32_t pageOffset;        /*!< Offset to physical memory location from IEE start address */
} iee_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Resets IEE module to factory default values.
 *
 * This function performs hardware reset of IEE module. Attributes and keys of all regions are cleared.
 *
 * @param base IEER peripheral address.
 */
void IEE_Init(IEE_Type *base);

/*!
 * @brief Loads default values to the IEE configuration structure.
 *
 * Loads default values to the IEE region configuration structure. The default values are as follows.
 * @code
 *   config->bypass = kIEE_AesUseMdField;
 *   config->mode = kIEE_ModeNone;
 *   config->keySize = kIEE_AesCTR128XTS256;
 *   config->pageOffset = 0U;
 * @endcode
 *
 * @param config Configuration for the selected IEE region.
 */
void IEE_GetDefaultConfig(iee_config_t *config);

/*!
 * @brief Sets the IEE module according to the configuration structure.
 *
 * This function configures IEE region according to configuration structure.
 *
 * @param base IEE peripheral address.
 * @param region Selection of the IEE region to be configured.
 * @param config Configuration for the selected IEE region.
 */
void IEE_SetRegionConfig(IEE_Type *base, iee_region_t region, iee_config_t *config);

/*!
 * @brief Sets the IEE module key.
 *
 * This function sets specified AES key for the given region.
 *
 * @param base IEE peripheral address.
 * @param region Selection of the IEE region to be configured.
 * @param keyNum Selection of AES KEY1 or KEY2.
 * @param key AES key.
 * @param keySize Size of AES key.
 */
status_t IEE_SetRegionKey(
    IEE_Type *base, iee_region_t region, iee_aes_key_num_t keyNum, const uint8_t *key, size_t keySize);

/*!
 * @brief Computes IEE offset to be set for specifed memory location.
 *
 * This function calculates offset that must be set for IEE region to access physical memory location.
 *
 * @param addressIee Address of IEE peripheral.
 * @param addressMemory Address of physical memory location.
 */
static inline uint32_t IEE_GetOffset(uint32_t addressIee, uint32_t addressMemory)
{
    return (addressMemory - addressIee) >> 12;
}

/*!
 * @brief Lock the IEE region configuration.
 *
 * This function locks IEE region registers for Key, Offset and Attribute.
 * Only system reset can clear the Lock bit.
 *
 * @param base IEE peripheral address.
 * @param region Selection of the IEE region to be locked.
 */
void IEE_LockRegionConfig(IEE_Type *base, iee_region_t region);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif /* FSL_IEE_H_ */
