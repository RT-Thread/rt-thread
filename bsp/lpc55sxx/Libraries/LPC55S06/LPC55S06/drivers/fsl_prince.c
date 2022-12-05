/*
 * Copyright 2018 - 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_prince.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */

#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.prince"
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if !defined(FSL_PRINCE_DRIVER_LPC55S3x)
static secure_bool_t PRINCE_CheckerAlgorithm(uint32_t address,
                                             uint32_t length,
                                             prince_flags_t flag,
                                             flash_config_t *flash_context)
{
    uint32_t temp_base = 0, temp_sr = 0, region_index = 0, contiguous_start_index = 0, contiguous_end_index = 32;
    secure_bool_t is_prince_region_contiguous      = kSECURE_TRUE;
    uint8_t prince_iv_code[FLASH_FFR_IV_CODE_SIZE] = {0};

    if (address >= flash_context->ffrConfig.ffrBlockBase)
    {
        /* If it is not in flash region, return true to allow erase/write operation. */
        return kSECURE_TRUE;
    }

    /* Iterate for all PRINCE regions */
    for (region_index = (uint32_t)kPRINCE_Region0; region_index <= (uint32_t)kPRINCE_Region2; region_index++)
    {
        contiguous_start_index = 0;
        contiguous_end_index   = 32;
        switch (region_index)
        {
            case (uint32_t)kPRINCE_Region0:
                temp_base = PRINCE->BASE_ADDR0;
                temp_sr   = PRINCE->SR_ENABLE0;
                break;

            case (uint32_t)kPRINCE_Region1:
                temp_base = PRINCE->BASE_ADDR1;
                temp_sr   = PRINCE->SR_ENABLE1;
                break;

            case (uint32_t)kPRINCE_Region2:
                temp_base = PRINCE->BASE_ADDR2;
                temp_sr   = PRINCE->SR_ENABLE2;
                break;

            default:
                /* All the cases have been listed above, the default clause should not be reached. */
                break;
        }

        if (((address >= temp_base) &&
             ((address + length) < (temp_base + (FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 32U * 1024U)))) &&
            (temp_sr != 0U))
        {
            /* Check if the mask is contiguous */
            secure_bool_t first_set_bit_found  = kSECURE_FALSE;
            secure_bool_t contiguous_end_found = kSECURE_FALSE;
            for (uint32_t i = 0; i < 32U; i++)
            {
                if (0U != (temp_sr & (1UL << i)))
                {
                    if (kSECURE_FALSE == first_set_bit_found)
                    {
                        first_set_bit_found    = kSECURE_TRUE;
                        contiguous_start_index = i;
                    }
                    if (kSECURE_TRUE == contiguous_end_found)
                    {
                        is_prince_region_contiguous = kSECURE_FALSE;
                        break;
                    }
                }
                else
                {
                    if ((kSECURE_TRUE == first_set_bit_found) && (kSECURE_FALSE == contiguous_end_found))
                    {
                        contiguous_end_found = kSECURE_TRUE;
                        contiguous_end_index = i;
                    }
                }
            }
        }
        else
        {
            continue; /* No encryption enabled, continue with the next region checking. */
        }

        /* Check if the provided memory range covers all addresses defined in the SR mask */
        if ((kSECURE_TRUE == is_prince_region_contiguous) &&
            ((address <= (temp_base + (contiguous_start_index * FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U)))) &&
            (((address + length) >=
              (temp_base + (contiguous_end_index * FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U)))))
        {
            /* In case of erase operation, invalidate the old PRINCE IV by regenerating the new one */
            if (kPRINCE_Flag_EraseCheck == flag)
            {
                /* Re-generate the PRINCE IV in case of erase operation */

                /* Generate new IV code for the PRINCE region and store the new IV into the respective FFRs */
                if (kStatus_Success ==
                    PRINCE_GenNewIV((prince_region_t)region_index, &prince_iv_code[0], true, flash_context))
                {
                    /* Store the new IV for the PRINCE region into PRINCE registers. */
                    if (kStatus_Success == PRINCE_LoadIV((prince_region_t)region_index, &prince_iv_code[0]))
                    {
                        /* Encryption is enabled, all subregions are to be erased/written at once, IV successfully
                         * regenerated, return true to allow erase operation. */
                        return kSECURE_TRUE;
                    }
                }
                /* Encryption is enabled, all subregions are to be erased/written at once but IV has not been correctly
                 * regenerated, return false to disable erase operation. */
                return kSECURE_FALSE;
            }

            /* Encryption is enabled and all subregions are to be erased/written at once, return true to allow
             * erase/write operation. */
            return kSECURE_TRUE;
        }
        /* The provided memory range does not cover all addresses defined in the SR mask. */
        else
        {
            /* Is the provided memory range outside the addresses defined by the SR mask? */
            if ((kSECURE_TRUE == is_prince_region_contiguous) &&
                ((((address + length) <=
                   (temp_base + (contiguous_start_index * FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U)))) ||
                 ((address >= (temp_base + (contiguous_end_index * FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U))))))
            {
                /* No encryption enabled for the provided memory range, true could be returned to allow erase/write
                   operation, but due to the same base address for all three prince regions on Niobe4Mini we should
                   continue with other regions (SR mask) checking. */
                continue;
            }
            else
            {
                /* Encryption is enabled but not all subregions are to be erased/written at once, return false to
                 * disable erase/write operation. */
                return kSECURE_FALSE;
            }
        }
    }
    return kSECURE_TRUE;
}
#endif /* !defined(FSL_PRINCE_DRIVER_LPC55S3x) */

#if !defined(FSL_PRINCE_DRIVER_LPC55S3x)
/*!
 * @brief Generate new IV code.
 *
 * This function generates new IV code and stores it into the persistent memory.
 * Ensure about 800 bytes free space on the stack when calling this routine with the store parameter set to true!
 *
 * @param region PRINCE region index.
 * @param iv_code IV code pointer used for storing the newly generated 52 bytes long IV code.
 * @param store flag to allow storing the newly generated IV code into the persistent memory (FFR).
 * @param flash_context pointer to the flash driver context structure.
 *
 * @return kStatus_Success upon success
 * @return kStatus_Fail    otherwise, kStatus_Fail is also returned if the key code for the particular
 *                         PRINCE region is not present in the keystore (though new IV code has been provided)
 */
status_t PRINCE_GenNewIV(prince_region_t region, uint8_t *iv_code, bool store, flash_config_t *flash_context)
{
    status_t status                                = kStatus_Fail;
    uint8_t prince_iv_code[FLASH_FFR_IV_CODE_SIZE] = {0};
    uint8_t tempBuffer[FLASH_FFR_MAX_PAGE_SIZE]    = {0};

    /* Make sure PUF is started to allow key and IV code decryption and generation */
    if (true != PUF_IsGetKeyAllowed(PUF))
    {
        return status;
    }

    /* Generate new IV code for the PRINCE region */
    status =
        PUF_SetIntrinsicKey(PUF, (puf_key_index_register_t)(uint32_t)((uint32_t)kPUF_KeyIndex_02 + (uint32_t)region), 8,
                            &prince_iv_code[0], FLASH_FFR_IV_CODE_SIZE);
    if ((kStatus_Success == status) && (true == store))
    {
        /* Store the new IV code for the PRINCE region into the respective FFRs. */
        /* Create a new version of "Customer Field Programmable" (CFP) page. */
        if ((int32_t)kStatus_FLASH_Success ==
            FFR_GetCustomerInfieldData(flash_context, (uint8_t *)tempBuffer, 0, FLASH_FFR_MAX_PAGE_SIZE))
        {
            /* Set the IV code in the page */
            (void)memcpy(&tempBuffer[offsetof(cfpa_cfg_info_t, ivCodePrinceRegion) +
                                     (((uint32_t)region * sizeof(cfpa_cfg_iv_code_t))) + 4U],
                         &prince_iv_code[0], FLASH_FFR_IV_CODE_SIZE);

            uint32_t *p32    = (uint32_t *)(uint32_t)tempBuffer;
            uint32_t version = p32[1];
            if (version == 0xFFFFFFFFu)
            {
                return kStatus_Fail;
            }
            version++;
            p32[1] = version;

            /* Program the page and enable firewall for "Customer field area" */
            if ((int32_t)kStatus_FLASH_Success ==
                FFR_InfieldPageWrite(flash_context, (uint8_t *)tempBuffer, FLASH_FFR_MAX_PAGE_SIZE))
            {
                status = kStatus_Success;
            }
            else
            {
                status = kStatus_Fail;
            }
        }
    }
    if (status == kStatus_Success)
    {
        /* Pass the new IV code */
        (void)memcpy(iv_code, &prince_iv_code[0], FLASH_FFR_IV_CODE_SIZE);
    }

    return status;
}
#endif /* !defined(FSL_PRINCE_DRIVER_LPC55S3x) */

#if !defined(FSL_PRINCE_DRIVER_LPC55S3x)
/*!
 * @brief Load IV code.
 *
 * This function enables IV code loading into the PRINCE bus encryption engine.
 *
 * @param region PRINCE region index.
 * @param iv_code IV code pointer used for passing the IV code.
 *
 * @return kStatus_Success upon success
 * @return kStatus_Fail    otherwise
 */
status_t PRINCE_LoadIV(prince_region_t region, uint8_t *iv_code)
{
    status_t status      = kStatus_Fail;
    uint32_t keyIndex    = (0x0Fu & (uint32_t)iv_code[1]);
    uint8_t prince_iv[8] = {0};

    /* Make sure PUF is started to allow key and IV code decryption and generation */
    if (true != PUF_IsGetKeyAllowed(PUF))
    {
        return kStatus_Fail;
    }

    /* Check if region number matches the PUF index value */
    if (((uint32_t)kPUF_KeyIndex_02 + (uint32_t)region) == (uint32_t)keyIndex)
    {
        /* Decrypt the IV */
        if (kStatus_Success == PUF_GetKey(PUF, iv_code, FLASH_FFR_IV_CODE_SIZE, &prince_iv[0], 8))
        {
            /* Store the new IV for the PRINCE region into PRINCE registers. */
            (void)PRINCE_SetRegionIV(PRINCE, (prince_region_t)region, prince_iv);
            status = kStatus_Success;
        }
    }

    return status;
}
#endif /* !defined(FSL_PRINCE_DRIVER_LPC55S3x) */

#if !defined(FSL_PRINCE_DRIVER_LPC55S3x)
/*!
 * @brief Allow encryption/decryption for specified address range.
 *
 * This function sets the encryption/decryption for specified address range.
 * The SR mask value for the selected Prince region is calculated from provided
 * start_address and length parameters. This calculated value is OR'ed with the
 * actual SR mask value and stored into the PRINCE SR_ENABLE register and also
 * into the persistent memory (FFR) to be used after the device reset. It is
 * possible to define several nonadjacent encrypted areas within one Prince
 * region when calling this function repeatedly. If the length parameter is set
 * to 0, the SR mask value is set to 0 and thus the encryption/decryption for
 * the whole selected Prince region is disabled.
 * Ensure about 800 bytes free space on the stack when calling this routine!
 *
 * @param region PRINCE region index.
 * @param start_address start address of the area to be encrypted/decrypted.
 * @param length length of the area to be encrypted/decrypted.
 * @param flash_context pointer to the flash driver context structure.
 * @param regenerate_iv flag to allow IV code regenerating, storing into
 *        the persistent memory (FFR) and loading into the PRINCE engine
 *
 * @return kStatus_Success upon success
 * @return kStatus_Fail    otherwise
 */
status_t PRINCE_SetEncryptForAddressRange(
    prince_region_t region, uint32_t start_address, uint32_t length, flash_config_t *flash_context, bool regenerate_iv)
{
    status_t status           = kStatus_Fail;
    uint32_t srEnableRegister = 0;
    uint32_t alignedStartAddress;
    uint32_t prince_base_addr_ffr_word          = 0;
    uint32_t end_address                        = start_address + length;
    uint32_t prince_region_base_address         = 0;
    uint8_t tempBuffer[FLASH_FFR_MAX_PAGE_SIZE] = {0};

    /* Check input parameters. */
    if (NULL == flash_context)
    {
        return kStatus_Fail;
    }

    /* Check the address range, region borders crossing. */
#if (defined(FSL_PRINCE_DRIVER_LPC55S0x)) || (defined(FSL_PRINCE_DRIVER_LPC55S1x)) || \
    (defined(FSL_PRINCE_DRIVER_LPC55S2x)) || (defined(FSL_PRINCE_DRIVER_LPC55S3x))
    if ((start_address > FSL_PRINCE_DRIVER_MAX_FLASH_ADDR) ||
        ((start_address < FSL_PRINCE_DRIVER_MAX_FLASH_ADDR) && (end_address > FSL_PRINCE_DRIVER_MAX_FLASH_ADDR)))
    {
        return kStatus_Fail;
    }
#endif
#if (defined(FSL_PRINCE_DRIVER_LPC55S6x))
    if ((start_address > FSL_PRINCE_DRIVER_MAX_FLASH_ADDR) ||
        ((start_address < 0x40000U) && (end_address > 0x40000U)) ||
        ((start_address < 0x80000U) && (end_address > 0x80000U)) ||
        ((start_address < FSL_PRINCE_DRIVER_MAX_FLASH_ADDR) && (end_address > FSL_PRINCE_DRIVER_MAX_FLASH_ADDR)))
    {
        return kStatus_Fail;
    }
#endif

    if (true == regenerate_iv)
    {
        uint8_t prince_iv_code[FLASH_FFR_IV_CODE_SIZE] = {0};

        /* Generate new IV code for the PRINCE region and store the new IV into the respective FFRs */
        status = PRINCE_GenNewIV((prince_region_t)region, &prince_iv_code[0], true, flash_context);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        /* Store the new IV for the PRINCE region into PRINCE registers. */
        status = PRINCE_LoadIV((prince_region_t)region, &prince_iv_code[0]);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }
    }

    alignedStartAddress = ALIGN_DOWN(start_address, (int32_t)FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024);

    uint32_t subregion = alignedStartAddress / (FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U);
    if (subregion < (32U))
    {
        /* PRINCE_Region0 */
        prince_region_base_address = 0;
    }
    else if (subregion < (64U))
    {
        /* PRINCE_Region1 */
        subregion                  = subregion - 32U;
        prince_region_base_address = 0x40000;
    }
    else
    {
        /* PRINCE_Region2 */
        subregion                  = subregion - 64U;
        prince_region_base_address = 0x80000;
    }

    /* If length > 0 then srEnableRegister mask is set based on the alignedStartAddress and the length.
       If the length is 0, srEnableRegister should be kept 0 (no subregion enabled). */
    if (length != 0U)
    {
        srEnableRegister = (1UL << subregion);
        alignedStartAddress += (FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U);

        while (alignedStartAddress < (start_address + length))
        {
            subregion++;
            srEnableRegister |= (1UL << subregion);
            alignedStartAddress += (FSL_PRINCE_DRIVER_SUBREGION_SIZE_IN_KB * 1024U);
        }

        uint32_t srEnableRegisterActual = 0;
        (void)PRINCE_GetRegionSREnable(PRINCE, (prince_region_t)region, &srEnableRegisterActual);
        srEnableRegister |= srEnableRegisterActual;
    }

    /* Store BASE_ADDR into PRINCE register before storing the SR to avoid en/decryption triggering
       from addresses being defined by current BASE_ADDR register content (could be 0 and the decryption
       of actually executed code can be started causing the hardfault then). */
    status = PRINCE_SetRegionBaseAddress(PRINCE, (prince_region_t)region, prince_region_base_address);
    if (kStatus_Success != status)
    {
        return status;
    }

    /* Store SR into PRINCE register */
    status = PRINCE_SetRegionSREnable(PRINCE, (prince_region_t)region, srEnableRegister);
    if (kStatus_Success != status)
    {
        return status;
    }

    /* Store SR and BASE_ADDR into CMPA FFR */
    if (kStatus_Success == FFR_GetCustomerData(flash_context, (uint8_t *)&tempBuffer, 0, FLASH_FFR_MAX_PAGE_SIZE))
    {
        /* Set the PRINCE_SR_X in the page */
        (void)memcpy((uint32_t *)(uintptr_t)&tempBuffer[offsetof(cmpa_cfg_info_t, princeSr) +
                                                        ((uint32_t)region * sizeof(uint32_t))],
                     &srEnableRegister, sizeof(uint32_t));
        /* Set the ADDRX_PRG in the page */
        (void)memcpy(&prince_base_addr_ffr_word,
                     (const uint32_t *)(uintptr_t)&tempBuffer[offsetof(cmpa_cfg_info_t, princeBaseAddr)],
                     sizeof(uint32_t));
        prince_base_addr_ffr_word &=
            ~(((uint32_t)FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG_MASK) << ((uint32_t)region * 4U));
        prince_base_addr_ffr_word |= (((prince_region_base_address >> PRINCE_BASE_ADDR0_ADDR_PRG_SHIFT) &
                                       FLASH_CMPA_PRINCE_BASE_ADDR_ADDR0_PRG_MASK)
                                      << ((uint32_t)region * 4U));
        (void)memcpy((uint32_t *)(uintptr_t)&tempBuffer[offsetof(cmpa_cfg_info_t, princeBaseAddr)],
                     &prince_base_addr_ffr_word, sizeof(uint32_t));

        /* Program the CMPA page, set seal_part parameter to false (used during development to avoid sealing the
         * part)
         */
        status = FFR_CustFactoryPageWrite(flash_context, (uint8_t *)tempBuffer, false);
    }

    return status;
}
#endif /* !defined(FSL_PRINCE_DRIVER_LPC55S3x) */

/*!
 * @brief Gets the PRINCE Sub-Region Enable register.
 *
 * This function gets PRINCE SR_ENABLE register.
 *
 * @param base PRINCE peripheral address.
 * @param region PRINCE region index.
 * @param sr_enable Sub-Region Enable register pointer.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_GetRegionSREnable(PRINCE_Type *base, prince_region_t region, uint32_t *sr_enable)
{
    status_t status = kStatus_Success;

    switch (region)
    {
        case kPRINCE_Region0:
            *sr_enable = base->SR_ENABLE0;
            break;

        case kPRINCE_Region1:
            *sr_enable = base->SR_ENABLE1;
            break;

        case kPRINCE_Region2:
            *sr_enable = base->SR_ENABLE2;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

/*!
 * @brief Gets the PRINCE region base address register.
 *
 * This function gets PRINCE BASE_ADDR register.
 *
 * @param base PRINCE peripheral address.
 * @param region PRINCE region index.
 * @param region_base_addr Region base address pointer.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_GetRegionBaseAddress(PRINCE_Type *base, prince_region_t region, uint32_t *region_base_addr)
{
    status_t status = kStatus_Success;

    switch (region)
    {
        case kPRINCE_Region0:
            *region_base_addr = base->BASE_ADDR0;
            break;

        case kPRINCE_Region1:
            *region_base_addr = base->BASE_ADDR1;
            break;

        case kPRINCE_Region2:
            *region_base_addr = base->BASE_ADDR2;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

/*!
 * @brief Sets the PRINCE region IV.
 *
 * This function sets specified AES IV for the given region.
 *
 * @param base PRINCE peripheral address.
 * @param region Selection of the PRINCE region to be configured.
 * @param iv 64-bit AES IV in little-endian byte order.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_SetRegionIV(PRINCE_Type *base, prince_region_t region, const uint8_t iv[8])
{
    status_t status              = kStatus_Fail;
    volatile uint32_t *IVMsb_reg = NULL;
    volatile uint32_t *IVLsb_reg = NULL;

    switch (region)
    {
        case kPRINCE_Region0:
            IVLsb_reg = &base->IV_LSB0;
            IVMsb_reg = &base->IV_MSB0;
            break;

        case kPRINCE_Region1:
            IVLsb_reg = &base->IV_LSB1;
            IVMsb_reg = &base->IV_MSB1;
            break;

        case kPRINCE_Region2:
            IVLsb_reg = &base->IV_LSB2;
            IVMsb_reg = &base->IV_MSB2;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    if (status != kStatus_InvalidArgument)
    {
        *IVLsb_reg = ((uint32_t *)(uintptr_t)iv)[0];
        *IVMsb_reg = ((uint32_t *)(uintptr_t)iv)[1];
        status     = kStatus_Success;
    }

    return status;
}

/*!
 * @brief Sets the PRINCE region base address.
 *
 * This function configures PRINCE region base address.
 *
 * @param base PRINCE peripheral address.
 * @param region Selection of the PRINCE region to be configured.
 * @param region_base_addr Base Address for region.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_SetRegionBaseAddress(PRINCE_Type *base, prince_region_t region, uint32_t region_base_addr)
{
    status_t status = kStatus_Success;

    /* Check input parameters. */
#if (defined(FSL_PRINCE_DRIVER_LPC55S0x)) || (defined(FSL_PRINCE_DRIVER_LPC55S1x)) || \
    (defined(FSL_PRINCE_DRIVER_LPC55S2x)) || (defined(FSL_PRINCE_DRIVER_LPC55S3x))
    if (region_base_addr > 0U)
    {
        return kStatus_InvalidArgument;
    }
#endif
#if (defined(FSL_PRINCE_DRIVER_LPC55S6x))
    if (region_base_addr > 0x80000U)
    {
        return kStatus_InvalidArgument;
    }
#endif

    switch (region)
    {
        case kPRINCE_Region0:
            base->BASE_ADDR0 = region_base_addr;
            break;

        case kPRINCE_Region1:
            base->BASE_ADDR1 = region_base_addr;
            break;

        case kPRINCE_Region2:
            base->BASE_ADDR2 = region_base_addr;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

/*!
 * @brief Sets the PRINCE Sub-Region Enable register.
 *
 * This function configures PRINCE SR_ENABLE register.
 *
 * @param base PRINCE peripheral address.
 * @param region Selection of the PRINCE region to be configured.
 * @param sr_enable Sub-Region Enable register value.
 *
 * @return kStatus_Success upon success
 * @return kStatus_InvalidArgument
 */
status_t PRINCE_SetRegionSREnable(PRINCE_Type *base, prince_region_t region, uint32_t sr_enable)
{
    status_t status = kStatus_Success;

    switch (region)
    {
        case kPRINCE_Region0:
            base->SR_ENABLE0 = sr_enable;
            break;

        case kPRINCE_Region1:
            base->SR_ENABLE1 = sr_enable;
            break;

        case kPRINCE_Region2:
            base->SR_ENABLE2 = sr_enable;
            break;

        default:
            status = kStatus_InvalidArgument;
            break;
    }

    return status;
}

#if !defined(FSL_PRINCE_DRIVER_LPC55S3x)
/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length. It deals with the flash erase function
 * complenentary to the standard erase API of the IAP1 driver. This implementation
 * additionally checks if the whole encrypted PRINCE subregions are erased at once
 * to avoid secrets revealing. The checker implementation is limited to one contiguous
 * PRINCE-controlled memory area.
 *
 * @param config The pointer to the flash driver context structure.
 * @param start The start address of the desired flash memory to be erased.
 *              The start address needs to be prince-sburegion-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *                      to be erased. Must be prince-sburegion-size-aligned.
 * @param key The value used to validate all flash erase APIs.
 *
 * @return #kStatus_FLASH_Success API was executed successfully.
 * @return #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @return #kStatus_FLASH_AlignmentError The parameter is not aligned with the specified baseline.
 * @return #kStatus_FLASH_AddressError The address is out of range.
 * @return #kStatus_FLASH_EraseKeyError The API erase key is invalid.
 * @return #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @return #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 * @return #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @return #kStatus_FLASH_EncryptedRegionsEraseNotDoneAtOnce Encrypted flash subregions are not erased at once.
 */
status_t PRINCE_FlashEraseWithChecker(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    /* Check input parameters. */
    if (NULL == config)
    {
        return kStatus_Fail;
    }
    /* Check that the whole encrypted region is erased at once. */
    if (kSECURE_TRUE != PRINCE_CheckerAlgorithm(start, lengthInBytes, kPRINCE_Flag_EraseCheck, config))
    {
        return (int32_t)kStatus_FLASH_EncryptedRegionsEraseNotDoneAtOnce;
    }
    return FLASH_Erase(config, start, lengthInBytes, key);
}

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length. It deals with the
 * flash program function complenentary to the standard program API of the IAP1 driver.
 * This implementation additionally checks if the whole PRINCE subregions are
 * programmed at once to avoid secrets revealing. The checker implementation is limited
 * to one contiguous PRINCE-controlled memory area.
 *
 * @param config The pointer to the flash driver context structure.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              prince-sburegion-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be prince-sburegion-size-aligned.
 *
 * @return #kStatus_FLASH_Success API was executed successfully.
 * @return #kStatus_FLASH_InvalidArgument An invalid argument is provided.
 * @return #kStatus_FLASH_AlignmentError Parameter is not aligned with the specified baseline.
 * @return #kStatus_FLASH_AddressError Address is out of range.
 * @return #kStatus_FLASH_AccessError Invalid instruction codes and out-of bounds addresses.
 * @return #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @return #kStatus_FLASH_CommandFailure Run-time error during the command execution.
 * @return #kStatus_FLASH_CommandNotSupported Flash API is not supported.
 * @return #kStatus_FLASH_EccError A correctable or uncorrectable error during command execution.
 * @return #kStatus_FLASH_SizeError Encrypted flash subregions are not programmed at once.
 */
status_t PRINCE_FlashProgramWithChecker(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    /* Check input parameters. */
    if (NULL == config)
    {
        return kStatus_Fail;
    }
    /* Check that the whole encrypted subregions will be writen at once. */
    if (kSECURE_TRUE != PRINCE_CheckerAlgorithm(start, lengthInBytes, kPRINCE_Flag_WriteCheck, config))
    {
        return (int32_t)kStatus_FLASH_SizeError;
    }
    return FLASH_Program(config, start, src, lengthInBytes);
}
#endif /* !defined(FSL_PRINCE_DRIVER_LPC55S3x) */

#if defined(FSL_PRINCE_DRIVER_LPC55S3x)
static status_t PRINCE_CSS_generate_random(uint8_t *output, size_t outputByteLen);
static status_t PRINCE_CSS_check_key(uint8_t keyIdx, mcuxClCss_KeyProp_t *pKeyProp);
static status_t PRINCE_CSS_gen_iv_key(void);
static status_t PRINCE_CSS_enable(void);
static status_t PRINCE_CSS_calculate_iv(uint32_t *IvReg);

/*!
 * @brief Configures PRINCE setting.
 *
 * This function does the initial PRINCE configuration via ROM IAP API call.
 * PRINCE_SR_x configuration for each region configuration is stored into FFR (CMPA).
 * PRINCE IV erase counters (MCTR_INT_IV_CTRx) in CFPA are updated accordingly.
 *
 * Note: This function is expected to be called once in the device lifetime,
 * typically during the initial device provisioning, since it is programming the CMPA pages in PFR flash.
 *
 * @param coreCtx The pointer to the ROM API driver context structure.
 * @param config The pointer to the PRINCE driver configuration structure.
 *
 * @retval #kStatus_Success
 * @retval #kStatus_CommandUnsupported
 * @retval #kStatus_InvalidArgument
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatusMemoryRangeInvalid
 * @retval #kStatus_Fail
 * @retval #kStatus_OutOfRange
 * @retval #kStatus_SPI_BaudrateNotSupport
 */
status_t PRINCE_Configure(api_core_context_t *coreCtx, prince_prot_region_arg_t *config)
{
    /* Enable CSS and check keys */
    if (kStatus_Success != PRINCE_CSS_enable())
    {
        return kStatus_Fail;
    }

    return MEM_Config(coreCtx, (uint32_t *)config, kMemoryInternal);
}

/*!
 * @brief Configures PRINCE setting.
 *
 * This function is used to re-configure PRINCE IP based on configuration stored in FFR.
 * This function also needs to be called after wake up from power-down mode to regenerate IV
 * encryption key in CSS key store whose presence is necessary for correct PRINCE operation
 * during erase and write operations to encrypted regions of internal flash memory
 * (dependency for correct operation of MEM_Erase() and MEM_Write() after wake up from power-down mode).
 *
 * @param coreCtx The pointer to the ROM API driver context structure.
 *
 * @retval #kStatus_Success
 * @retval #kStatus_Fail
 */
status_t PRINCE_Reconfigure(api_core_context_t *coreCtx)
{
    status_t status = kStatus_Fail;
    uint64_t princeMask;
    uint32_t IvReg[4] = {0};
    uint32_t ivEraseCounter[3];
    uint32_t srEnable[3];
    uint32_t uuid[4];
    flash_config_t flash_config;
    uint32_t lockWord;
    uint8_t lock[3];

    /* Enable CSS and check keys */
    status = PRINCE_CSS_enable();
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    /* Set PRINCE mask value. */
    status = PRINCE_CSS_generate_random((uint8_t *)&princeMask, sizeof(princeMask));
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }
    PRINCE_SetMask(PRINCE, princeMask);

    /* Clean up Flash driver structure and Init*/
    memset(&flash_config, 0, sizeof(flash_config_t));
    if (FLASH_Init(&flash_config) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* FFR Init */
    if (FFR_Init(&flash_config) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Get UUID from FFR */
    status = FFR_GetUUID(&flash_config, (uint8_t *)uuid);
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    /* Check version of CFPA scratch first */
    uint32_t cfpaScratchVer = 0u;
    memcpy(&cfpaScratchVer, (void *)(CFPA_SCRATCH_VER), sizeof(uint32_t));

    /* Get CFPA version using FFR ROM API */
    uint32_t cfpaVer = 0u;
    if (kStatus_Success !=
        FFR_GetCustomerInfieldData(&flash_config, (uint8_t *)&cfpaVer, CFPA_VER_OFFSET, sizeof(uint32_t)))
    {
        status = kStatus_Fail;
        return status;
    }

    /* Compare the version of CFPA scratch and version of CFPA returned by ROM API */
    if (cfpaScratchVer > cfpaVer)
    {
        /* Get PRINCE_IV_CTRs from CFPA scratch */
        memcpy(&ivEraseCounter, (void *)CFPA_SCRATCH_IV, sizeof(uint32_t) * PRINCE_REGION_COUNT);
    }
    else
    {
        /* Get PRINCE_IV_CTRs IVs from CFPA ping/pong page */
        status = FFR_GetCustomerInfieldData(&flash_config, (uint8_t *)ivEraseCounter, CFPA_PRINCE_IV_OFFSET,
                                            sizeof(uint32_t) * PRINCE_REGION_COUNT);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }
    }

    /* Get PRINCE sub-region enable word from FFR */
    status = FFR_GetCustomerData(&flash_config, (uint8_t *)srEnable, CMPA_PRINCE_SR_OFFSET,
                                 sizeof(uint32_t) * PRINCE_REGION_COUNT);
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    /* Get PRINCE lock setting from FFR */
    status = FFR_GetCustomerData(&flash_config, (uint8_t *)&lockWord, CMPA_PRINCE_LOCK_OFFSET, sizeof(uint32_t));
    if (kStatus_Success != status)
    {
        return kStatus_Fail;
    }

    lock[0] = (lockWord & PRINCE_BASE_ADDR_LOCK_REG0_MASK) >> PRINCE_BASE_ADDR_LOCK_REG0_SHIFT;
    lock[1] = (lockWord & PRINCE_BASE_ADDR_LOCK_REG1_MASK) >> PRINCE_BASE_ADDR_LOCK_REG1_SHIFT;
    lock[2] = (lockWord & PRINCE_BASE_ADDR_LOCK_REG2_MASK) >> PRINCE_BASE_ADDR_LOCK_REG2_SHIFT;

    /* Iterate for all internal PRINCE regions */
    for (prince_region_t region = kPRINCE_Region0; region <= kPRINCE_Region2; region++)
    {
        /* Set region base address. Should be always 0x0 on LPC55S36 */
        status = PRINCE_SetRegionBaseAddress(PRINCE, (prince_region_t)region, 0x0u);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        status = PRINCE_SetRegionSREnable(PRINCE, region, srEnable[region]);
        if (kStatus_Success != status)
        {
            return kStatus_Fail;
        }

        /* Prepare ivSeed for current region */
        IvReg[0] = uuid[0];
        IvReg[1] = uuid[1];
        IvReg[2] = uuid[2] ^ region;
        IvReg[3] = ivEraseCounter[region];

        /* Calculate IV as IvReg = AES_ECB_ENC(DUK_derived_key, {ctx_erase_counter, ctx_id}) */
        status = PRINCE_CSS_calculate_iv(IvReg);
        if (status != kStatus_Success)
        {
            return kStatus_Fail;
        }

        /* Load IV into PRINCE registers */
        status = PRINCE_SetRegionIV(PRINCE, (prince_region_t)region, (uint8_t *)IvReg);
        if (status != kStatus_Success)
        {
            return kStatus_Fail;
        }

        /* Lock region if required */
        if ((lock[region] == 0x1u) || (lock[region] == 0x2u) || (lock[region] == 0x3u))
        {
            PRINCE_SetLock(PRINCE, (kPRINCE_Region0Lock << region));
        }
    }

    /* Break the main loop in case that error occured during PRINCE configuration */
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* When ENC_ENABLE is set, reading from PRINCE-encrypted regions is disabled. */
    /* For LPC55S36, the ENC_ENABLE is self-cleared after programming memory. */
    PRINCE_EncryptDisable(PRINCE);
    return status;
}

static status_t PRINCE_CSS_generate_random(uint8_t *output, size_t outputByteLen)
{
    status_t status = kStatus_Fail;

    // PRNG needs to be initialized; this can be done by calling mcuxClCss_KeyDelete_Async
    // (delete any key slot, can be empty)
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCss_KeyDelete_Async(18));
    // mcuxClCss_KeyDelete_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_KeyDelete_Async) != token) || (MCUXCLCSS_STATUS_OK_WAIT != result))
        return kStatus_Fail; // Expect that no error occurred, meaning that the mcuxClCss_KeyDelete_Async operation was
                             // started.
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    // Wait for operation to finish
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
    // mcuxClCss_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) != token) || (MCUXCLCSS_STATUS_OK != result))
        return kStatus_Fail; // Expect that no error occurred, meaning that the mcuxClCss_WaitForOperation operation was
                             // started.
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCss_Prng_GetRandom(output, outputByteLen));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom) != token) || (MCUXCLCSS_STATUS_OK != result))
        return kStatus_Fail;
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    status = kStatus_Success;
    return status;
}

static status_t PRINCE_CSS_check_key(uint8_t keyIdx, mcuxClCss_KeyProp_t *pKeyProp)
{
    /* Check if CSS required keys are available in CSS keystore */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClCss_GetKeyProperties(keyIdx, pKeyProp)); // Get key propertis from the CSS.
    // mcuxClCss_GetKeyProperties is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetKeyProperties) != token) || (MCUXCLCSS_STATUS_OK != result))
        return kStatus_Fail;
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return kStatus_Success;
}

static status_t PRINCE_CSS_gen_iv_key(void)
{
    /* The NXP_DIE_MEM_IV_ENC_SK is not loaded and needs to be regenerated (power-down wakeup) */
    /* Set KDF mask and key properties for NXP_DIE_MEM_IV_ENC_SK */
    SYSCON->CSS_KDF_MASK            = SYSCON_CSS_KDF_MASK;
    static const uint32_t ddata2[3] = {0x62032504, 0x72f04280, 0x87a2bbae};
    mcuxClCss_KeyProp_t keyProp;
    /* Set key properties in structure */
    keyProp.word.value = CSS_CSS_KS2_ks2_uaes_MASK | CSS_CSS_KS2_ks2_fgp_MASK | CSS_CSS_KS2_ks2_kact_MASK;
    status_t status    = kStatus_Fail;

    /* Generate the key using CKDF */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
        result, token,
        mcuxClCss_Ckdf_Sp800108_Async((mcuxClCss_KeyIndex_t)0, (mcuxClCss_KeyIndex_t)NXP_DIE_MEM_IV_ENC_SK, keyProp,
                                      (uint8_t const *)ddata2));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Ckdf_Sp800108_Async) != token) && (MCUXCLCSS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Wait for CKDF to finish */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) == token) && (MCUXCLCSS_STATUS_OK == result))
    {
        status = kStatus_Success;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return status;
}

static status_t PRINCE_CSS_enable(void)
{
    mcuxClCss_KeyProp_t key_properties;
    status_t status = kStatus_Fail;

    /* Enable CSS and related clocks */
    status = CSS_PowerDownWakeupInit(CSS);
    if (status != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Check if MEM_ENC_SK key is available in CSS keystore */
    status = PRINCE_CSS_check_key(NXP_DIE_MEM_ENC_SK, &key_properties);
    if (status != kStatus_Success || key_properties.bits.kactv != 1u)
    {
        return kStatus_Fail;
    }

    /* Check if MEM_IV_ENC_SK key is available in CSS keystore */
    status = PRINCE_CSS_check_key(NXP_DIE_MEM_IV_ENC_SK, &key_properties);
    if (status != kStatus_Success || key_properties.bits.kactv != 1u)
    {
        return PRINCE_CSS_gen_iv_key();
    }

    return kStatus_Success;
}

static status_t PRINCE_CSS_calculate_iv(uint32_t *IvReg)
{
    mcuxClCss_CipherOption_t cipherOptions = {0};
    status_t status                        = kStatus_Fail;

    /* Configure CSS for AES ECB-128, using NXP_DIE_MEM_IV_ENC_SK key */
    cipherOptions.bits.cphmde = MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_ECB;
    cipherOptions.bits.dcrpt  = MCUXCLCSS_CIPHER_ENCRYPT;
    cipherOptions.bits.extkey = MCUXCLCSS_CIPHER_INTERNAL_KEY;

    do
    {
        /* Calculate IV as IvReg = AES_ECB_ENC(NXP_DIE_MEM_IV_ENC_SK, ivSeed[127:0]) */
        /* ivSeed[127:0] = {UUID[96:0] ^ regionNumber[1:0], ivEraseCounter[31:0]} */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
            result, token,
            mcuxClCss_Cipher_Async(cipherOptions, (mcuxClCss_KeyIndex_t)NXP_DIE_MEM_IV_ENC_SK, NULL,
                                   MCUXCLCSS_CIPHER_KEY_SIZE_AES_128, (uint8_t *)IvReg, MCUXCLCSS_CIPHER_BLOCK_SIZE_AES,
                                   NULL, (uint8_t *)IvReg));
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cipher_Async) != token) || (MCUXCLCSS_STATUS_OK_WAIT != result))
            break;
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(
            result, token,
            mcuxClCss_WaitForOperation(
                MCUXCLCSS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClCss_Enable_Async operation to complete.
        // mcuxClCss_WaitForOperation is a flow-protected function: Check the protection token and the return value
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) == token) && (MCUXCLCSS_STATUS_OK == result))
        {
            status = kStatus_Success;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
    } while (0);

    return status;
}
#endif /* defined(FSL_PRINCE_DRIVER_LPC55S3x) */
