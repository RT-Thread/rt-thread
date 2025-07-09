/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_iee.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iee"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Resets IEE module to factory default values.
 *
 * This function performs hardware reset of IEE module. Attributes and keys of all regions are cleared.
 *
 * param base IEER peripheral address.
 */
void IEE_Init(IEE_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable IEE clock. */
    CLOCK_EnableClock(kCLOCK_Iee);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_IEE_ELE_PROVISIONED_KEY) && (FSL_FEATURE_IEE_ELE_PROVISIONED_KEY > 0u))
    /* Reset IEE module and wait the reset operation done. */
    base->GCFG |= IEE_GCFG_RST_MASK;
#endif /* !FSL_FEATURE_IEE_ELE_PROVISIONED_KEY */
}

/*!
 * brief Loads default values to the IEE configuration structure.
 *
 * Loads default values to the IEE region configuration structure. The default values are as follows.
 * code
 *   config->bypass = kIEE_AesUseMdField;
 *   config->mode = kIEE_ModeNone;
 *   config->keySize = kIEE_AesCTR128XTS256;
 *   config->pageOffset = 0U;
 * endcode
 *
 * param config Configuration for the selected IEE region.
 */
void IEE_GetDefaultConfig(iee_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->bypass     = kIEE_AesUseMdField;
    config->mode       = kIEE_ModeNone;
    config->keySize    = kIEE_AesCTR128XTS256;
    config->pageOffset = 0U;
}

/*!
 * brief Sets the IEE module according to the configuration structure.
 *
 * This function configures IEE region according to configuration structure.
 *
 * Note: if key is provisioned by ELE, the attributes are set by ELE
 *
 * param base IEE peripheral address.
 * param region Selection of the IEE region to be configured.
 * param config Configuration for the selected IEE region.
 */
void IEE_SetRegionConfig(IEE_Type *base, iee_region_t region, iee_config_t *config)
{
#if !(defined(FSL_FEATURE_IEE_ELE_PROVISIONED_KEY) && (FSL_FEATURE_IEE_ELE_PROVISIONED_KEY > 0u))
    base->REGX[region].REGATTR =
        IEE_REGATTR_BYP(config->bypass) | IEE_REGATTR_MD(config->mode) | IEE_REGATTR_KS(config->keySize);
#if (defined(FSL_IEE_USE_PAGE_OFFSET) && (FSL_IEE_USE_PAGE_OFFSET > 0U))
    base->REGX[region].REGPO = IEE_REGPO_PGOFF(config->pageOffset);
#endif /* FSL_IEE_USE_PAGE_OFFSET */
#endif /* !FSL_FEATURE_IEE_ELE_PROVISIONED_KEY */
}

/*!
 * brief Sets the IEE module key.
 *
 * This function sets specified AES key for the given region.
 *
 * param base IEE peripheral address.
 * param region Selection of the IEE region to be configured.
 * param keyNum Selection of AES KEY1 or KEY2.
 * param key AES key.
 * param keySize Size of AES key.
 */
status_t IEE_SetRegionKey(
    IEE_Type *base, iee_region_t region, iee_aes_key_num_t keyNum, const uint8_t *key, size_t keySize)
{
#if !(defined(FSL_FEATURE_IEE_ELE_PROVISIONED_KEY) && (FSL_FEATURE_IEE_ELE_PROVISIONED_KEY > 0u))
    register const uint32_t *from32  = (const uint32_t *)(uintptr_t)key;
    register volatile uint32_t *to32 = NULL;

    if (keyNum == kIEE_AesKey1)
    {
        to32 = &base->REGX[region].REGKEY1[0];
    }

    else if (keyNum == kIEE_AesKey2)
    {
        to32 = &base->REGX[region].REGKEY2[0];
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    while (keySize >= sizeof(uint32_t))
    {
        *to32 = *from32;
        keySize -= sizeof(uint32_t);
        from32++;
        to32++;
    }

    return kStatus_Success;
#else
    return kStatus_Fail;
#endif /* !defined(FSL_FEATURE_IEE_ELE_PROVISIONED_KEY) */
}

/*!
 * brief Lock the IEE region configuration.
 *
 * IEE region Key, Offset and Attribute registers are locked.
 * Only system reset can clear the Lock bit.
 *
 * param base IEE peripheral address.
 * param region Selection of the IEE region to be locked.
 */
void IEE_LockRegionConfig(IEE_Type *base, iee_region_t region)
{
    base->GCFG |= (uint32_t)(0x1UL << (uint32_t)region);
}
