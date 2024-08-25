/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_ftfx_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flash"
#endif

/*!
 * @brief Enumeration for special memory property.
 */
enum _ftfx_special_mem_property
{
    kFTFx_AccessSegmentUnitSize = 256UL,
    kFTFx_MinProtectBlockSize   = 1024UL,
};

#if defined(FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD) && FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
/*!
 * @brief Enumeration for the index of read/program once record
 */
enum _k3_flash_read_once_index
{
    kFLASH_RecordIndexSwapAddr    = 0xA1U, /*!< Index of Swap indicator address.*/
    kFLASH_RecordIndexSwapEnable  = 0xA2U, /*!< Index of Swap system enable.*/
    kFLASH_RecordIndexSwapDisable = 0xA3U, /*!< Index of Swap system disable.*/
};
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*! @brief init flash features */
static void flash_init_features(ftfx_config_t *config);

/*! @brief init  protection feature */
static void flash_protection_init(flash_config_t *config, uint8_t flashIndex);

/*! @brief init access segment feature */
#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
static void flash_access_init(flash_config_t *config, uint8_t flashIndex);
#endif

/*! @brief init flash operation config */
static void flash_opsonfig_Init(flash_config_t *config, uint8_t flashIndex);

/*! @brief Calculate flash memory size based on given parameter */
static uint32_t flash_calculate_mem_size(uint32_t pflashBlockCount,
                                         uint32_t pflashBlockSize,
                                         uint32_t pfsizeMask,
                                         uint32_t pfsizeShift);

static uint32_t flash_calculate_prot_segment_size(uint32_t flashSize, uint32_t segmentCount);

/*! @brief Validates the given address to get current flash index */
static status_t flash_check_range_to_get_index(flash_config_t *config,
                                               uint32_t start,
                                               uint32_t lengthInBytes,
                                               uint8_t *flashIndex);

/*! @brief Decide whether to convert the start address from primary flash to secondary flash based on the current start
 * address*/
static void flash_convert_start_address(ftfx_config_t *config, uint32_t start);

#if defined(FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP) && FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP
/*! @brief Validates the given address to see if it is equal to swap indicator address in pflash swap IFR.*/
static status_t flash_validate_swap_indicator_address(ftfx_config_t *config, uint32_t address);
#endif /* FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP */

/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile uint32_t *const kFPROTL = (volatile uint32_t *)(uint32_t)&FTFx_FPROT_LOW_REG;
#if defined(FTFx_FLASH0_HAS_HIGH_PROT_REG) && FTFx_FLASH0_HAS_HIGH_PROT_REG
static volatile uint32_t *const kFPROTH = (volatile uint32_t *)(uint32_t)&FTFx_FPROT_HIGH_REG;
#endif /* FTFx_FLASH0_HAS_HIGH_PROT_REG */
#if defined(FTFx_FLASH1_HAS_INT_PROT_REG) && FTFx_FLASH1_HAS_INT_PROT_REG
volatile uint8_t *const kFPROTSL = (volatile uint8_t *)(uint32_t)&FTFx_FPROTSL_REG;
volatile uint8_t *const kFPROTSH = (volatile uint8_t *)(uint32_t)&FTFx_FPROTSH_REG;
#endif /* FTFx_FLASH1_HAS_INT_PROT_REG */

/*!
 * @brief Table of pflash sizes.
 *
 *  The index into this table is the value of the SIM_FCFG1.PFSIZE bitfield.
 *
 *  The values in this table have been right shifted 10 bits so that they will all fit within
 *  an 16-bit integer. To get the actual flash density, you must left shift the looked up value
 *  by 10 bits.
 *
 *  Elements of this table have a value of 0 in cases where the PFSIZE bitfield value is
 *  reserved.
 *
 *  Code to use the table:
 *  @code
 *      uint8_t pfsize = (SIM->FCFG1 & SIM_FCFG1_PFSIZE_MASK) >> SIM_FCFG1_PFSIZE_SHIFT;
 *      flashDensity = ((uint32_t)kPFlashDensities[pfsize]) << 10;
 *  @endcode
 */
#if defined(FSL_FEATURE_FLASH_SIZE_ENCODING_RULE_VERSION) && (FSL_FEATURE_FLASH_SIZE_ENCODING_RULE_VERSION == 1)
static const uint16_t kPFlashDensities[] = {
    0u,    /* 0x0 - undefined */
    0u,    /* 0x1 - undefined */
    0u,    /* 0x2 - undefined */
    0u,    /* 0x3 - undefined */
    0u,    /* 0x4 - undefined */
    0u,    /* 0x5 - undefined */
    0u,    /* 0x6 - undefined */
    0u,    /* 0x7 - undefined */
    0u,    /* 0x8 - undefined */
    0u,    /* 0x9 - undefined */
    256u,  /* 0xa - 262144, 256KB */
    512u,  /* 0xb - 524288, 512KB */
    1024u, /* 0xc - 1048576, 1MB */
    0u,    /* 0xd - undefined */
    0u,    /* 0xe - undefined */
    0u,    /* 0xf - undefined */
};
#else
static const uint16_t kPFlashDensities[] = {
    8u,    /* 0x0 - 8192, 8KB */
    16u,   /* 0x1 - 16384, 16KB */
    24u,   /* 0x2 - 24576, 24KB */
    32u,   /* 0x3 - 32768, 32KB */
    48u,   /* 0x4 - 49152, 48KB */
    64u,   /* 0x5 - 65536, 64KB */
    96u,   /* 0x6 - 98304, 96KB */
    128u,  /* 0x7 - 131072, 128KB */
    192u,  /* 0x8 - 196608, 192KB */
    256u,  /* 0x9 - 262144, 256KB */
    384u,  /* 0xa - 393216, 384KB */
    512u,  /* 0xb - 524288, 512KB */
    768u,  /* 0xc - 786432, 768KB */
    1024u, /* 0xd - 1048576, 1MB */
    1536u, /* 0xe - 1572864, 1.5MB */
    /* 2048u,  0xf - 2097152, 2MB */
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_PartitionStatusUpdateFailure Failed to update the partition status.
 */
status_t FLASH_Init(flash_config_t *config)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    for (uint8_t flashIndex = 0U; flashIndex < FTFx_FLASH_COUNT; flashIndex++)
    {
        /* init flash type, kinetis has Pflash and flxnvm, pflash is often used to store executable code
         * and flexnvm can be used as date flash to store user data, and can also be configured as eeprom backup space
         * with flexram.
         */
        config->ftfxConfig[flashIndex].flashDesc.type = (uint8_t)kFTFx_MemTypePflash;
        /* init the current flash index */
        config->ftfxConfig[flashIndex].flashDesc.index = flashIndex;
        /* init flash features */
        flash_init_features(&config->ftfxConfig[flashIndex]);
        /* init flash Operation Config */
        flash_opsonfig_Init(config, flashIndex);

#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
        if (0U != (config->ftfxConfig[flashIndex].flashDesc.feature.hasXaccControl))
        {
            /* init access segment feature */
            flash_access_init(config, flashIndex);
        }
#endif /* FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL */
#if (FTFx_FLASH_COUNT > 1U)
        if (0U != (config->ftfxConfig[flashIndex].flashDesc.feature.hasProtControl))
#endif
        {
            /* init  protection feature */
            flash_protection_init(config, flashIndex);
        }

        /* Init FTFx Kernel */
        FTFx_API_Init(&config->ftfxConfig[flashIndex]);
    }

    return kStatus_FTFx_Success;
}

/*!
 * @brief Erases the Dflash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be erased.
 *              The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words)
 *                      to be erased. Must be word-aligned.
 * @param key The value used to validate all flash erase APIs.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully; the appropriate number of flash sectors based on the
 *         desired start address and length was erased successfully.
 *
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_AlignmentError The parameter is not aligned with the specified baseline.
 * @retval #kStatus_FTFx_AddressError The address is out of range.
 * @retval #kStatus_FTFx_EraseKeyError The API erase key is invalid.
 * @retval #kStatus_FTFx_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_FTFx_AccessError Invalid instruction codes and out-of bounds addresses.
 * @retval #kStatus_FTFx_ProtectionViolation The program/erase operation is requested to execute on protected areas.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during the command execution.
 */
status_t FLASH_Erase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    status_t returnCode;
    uint8_t flashIndex;

    /* check the supplied address range to get flash index  */
    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* Decide whether to convert the start address from primary flash to secondary flash based on the current address */
    flash_convert_start_address(&config->ftfxConfig[flashIndex], start);

    return FTFx_CMD_Erase(&config->ftfxConfig[flashIndex], start, lengthInBytes, key);
}

/*!
 * @brief Erases the Dflash sectors encompassed by parameters passed into function.
 *
 * This function erases one flash sector size based on the start address, and it is
 * executed asynchronously.
 */
status_t FLASH_EraseSectorNonBlocking(flash_config_t *config, uint32_t start, uint32_t key)
{
    status_t returnCode;
    uint8_t flashIndex;
    uint32_t lengthInBytes = FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE;

    /* check the supplied address range to get flash index  */
    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* Decide whether to convert the start address from primary flash to secondary flash based on the current address */
    flash_convert_start_address(&config->ftfxConfig[flashIndex], start);

    return FTFx_CMD_EraseSectorNonBlocking(&config->ftfxConfig[flashIndex], start, key);
}

/*!
 * @brief Erases entire flexnvm
 */
status_t FLASH_EraseAll(flash_config_t *config, uint32_t key)
{
    return FTFx_CMD_EraseAll(&config->ftfxConfig[0], key);
}

#if defined(FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD) && FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD
/*!
 * @brief Erases the entire flexnvm, including protected sectors.
 */
status_t FLASH_EraseAllUnsecure(flash_config_t *config, uint32_t key)
{
    return FTFx_CMD_EraseAllUnsecure(&config->ftfxConfig[0], key);
}
#endif

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 */
status_t FLASH_Program(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    uint8_t flashIndex;

    /* check range to get flash index */
    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }
    /* convert the start address from primary flash to secondary flash based on the current address */
    flash_convert_start_address(&config->ftfxConfig[flashIndex], start);

    /* Programs flash */
    return FTFx_CMD_Program(&config->ftfxConfig[flashIndex], start, src, lengthInBytes);
}

/*!
 * @brief Reads the Program Once Field through parameters.
 */
status_t FLASH_ProgramOnce(flash_config_t *config, uint32_t index, uint8_t *src, uint32_t lengthInBytes)
{
    return FTFx_CMD_ProgramOnce(&config->ftfxConfig[0], index, src, lengthInBytes);
}

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
/*!
 * @brief Programs flash with data at locations passed in through parameters via the Program Section command.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and length.
 *
 */
status_t FLASH_ProgramSection(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    uint8_t flashIndex;

    /* Validates the range of the given address range and get flash index */
    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* convert the start address from primary flash to secondary flash based on the current address */
    flash_convert_start_address(&config->ftfxConfig[flashIndex], start);

    return FTFx_CMD_ProgramSection(&config->ftfxConfig[flashIndex], start, src, lengthInBytes);
}
#endif

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
/*!
 * @brief Reads the resource with data at locations passed in through parameters.
 */
status_t FLASH_ReadResource(
    flash_config_t *config, uint32_t start, uint8_t *dst, uint32_t lengthInBytes, ftfx_read_resource_opt_t option)
{
    return FTFx_CMD_ReadResource(&config->ftfxConfig[0], start, dst, lengthInBytes, option);
}
#endif

/*!
 * @brief Reads the Program Once Field through parameters.
 */
status_t FLASH_ReadOnce(flash_config_t *config, uint32_t index, uint8_t *dst, uint32_t lengthInBytes)
{
    return FTFx_CMD_ReadOnce(&config->ftfxConfig[0], index, dst, lengthInBytes);
}

/*!
 * @brief Verifies an erasure of the desired flash area at a specified margin level.
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 * to the specified read margin level.
 */
status_t FLASH_VerifyErase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, ftfx_margin_value_t margin)
{
    status_t returnCode;
    uint8_t flashIndex;

    /* check range to get flash index */
    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* convert the start address from primary flash to secondary flash based on the current start address*/
    flash_convert_start_address(&config->ftfxConfig[flashIndex], start);

    return FTFx_CMD_VerifyErase(&config->ftfxConfig[flashIndex], start, lengthInBytes, margin);
}

/*!
 * @brief Verifies erasure of the entire flash at a specified margin level.
 */
status_t FLASH_VerifyEraseAll(flash_config_t *config, ftfx_margin_value_t margin)
{
    return FTFx_CMD_VerifyEraseAll(&config->ftfxConfig[0], margin);
}

/*!
 * @brief Verifies programming of the desired flash area at a specified margin level.
 *
 * This function verifies the data programmed in the flash memory using the
 * Flash Program Check Command and compares it to the expected data for a given
 * flash area as determined by the start address and length.
 */
status_t FLASH_VerifyProgram(flash_config_t *config,
                             uint32_t start,
                             uint32_t lengthInBytes,
                             const uint8_t *expectedData,
                             ftfx_margin_value_t margin,
                             uint32_t *failedAddress,
                             uint32_t *failedData)
{
    status_t returnCode;
    uint8_t flashIndex;

    /* Validates the given address to get current flash index */
    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* convert the start address from primary flash to secondary flash based on the current start address */
    flash_convert_start_address(&config->ftfxConfig[flashIndex], start);

    return FTFx_CMD_VerifyProgram(&config->ftfxConfig[flashIndex], start, lengthInBytes, expectedData, margin,
                                  failedAddress, failedData);
}

/*!
 * @brief Returns the security state via the pointer passed into the function.
 */
status_t FLASH_GetSecurityState(flash_config_t *config, ftfx_security_state_t *state)
{
    return FTFx_REG_GetSecurityState(&config->ftfxConfig[0], state);
}

/*!
 * @brief Allows users to bypass security with a backdoor key.
 */
status_t FLASH_SecurityBypass(flash_config_t *config, const uint8_t *backdoorKey)
{
    return FTFx_CMD_SecurityBypass(&config->ftfxConfig[0], backdoorKey);
}

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
/*!
 * @brief Sets the FlexRAM function command.
 */
status_t FLASH_SetFlexramFunction(flash_config_t *config, ftfx_flexram_func_opt_t option)
{
    return FTFx_CMD_SetFlexramFunction(&config->ftfxConfig[0], option);
}
#endif

#if defined(FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP) && FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP
/*!
 * @brief Swaps the lower half flash with the higher half flash.
 */
status_t FLASH_Swap(flash_config_t *config, uint32_t address, bool isSetEnable)
{
    status_t returnCode;
    ftfx_swap_state_config_t returnInfo;
    ftfx_config_t *ftfxConfig;
    uint8_t flashIndex;

    returnCode = flash_check_range_to_get_index(config, address, 1U, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    ftfxConfig = &config->ftfxConfig[flashIndex];

    (void)memset(&returnInfo, 0xFF, sizeof(returnInfo));

    do
    {
        returnCode = FTFx_CMD_SwapControl(ftfxConfig, address, kFTFx_SwapControlOptionReportStatus, &returnInfo);
        if (returnCode != kStatus_FTFx_Success)
        {
            return returnCode;
        }

        if (!isSetEnable)
        {
            if (returnInfo.flashSwapState == kFTFx_SwapStateDisabled)
            {
                return kStatus_FTFx_Success;
            }
            else if (returnInfo.flashSwapState == kFTFx_SwapStateUninitialized)
            {
                /* The swap system changed to the DISABLED state with Program flash block 0
                 * located at relative flash address 0x0_0000 */
                returnCode =
                    FTFx_CMD_SwapControl(ftfxConfig, address, kFTFx_SwapControlOptionDisableSystem, &returnInfo);
            }
            else
            {
                /* Swap disable should be requested only when swap system is in the uninitialized state */
                return kStatus_FTFx_SwapSystemNotInUninitialized;
            }
        }
        else
        {
            /* When first swap: the initial swap state is Uninitialized, flash swap indicator address is unset,
             *    the swap procedure should be Uninitialized -> Update-Erased -> Complete.
             * After the first swap has been completed, the flash swap inidicator address cannot be modified
             *    unless EraseAllBlocks command is issued, the swap procedure is changed to Update -> Update-Erased ->
             *    Complete. */
            switch (returnInfo.flashSwapState)
            {
                case kFTFx_SwapStateUninitialized:
                    /* If current swap mode is Uninitialized, Initialize Swap to Initialized/READY state. */
                    returnCode =
                        FTFx_CMD_SwapControl(ftfxConfig, address, kFTFx_SwapControlOptionIntializeSystem, &returnInfo);
                    break;
                case kFTFx_SwapStateReady:
                    /* Validate whether the address provided to the swap system is matched to
                     * swap indicator address in the IFR */
                    returnCode = flash_validate_swap_indicator_address(ftfxConfig, address);
                    if (returnCode == kStatus_FTFx_Success)
                    {
                        /* If current swap mode is Initialized/Ready, Initialize Swap to UPDATE state. */
                        returnCode = FTFx_CMD_SwapControl(ftfxConfig, address, kFTFx_SwapControlOptionSetInUpdateState,
                                                          &returnInfo);
                    }
                    break;
                case kFTFx_SwapStateUpdate:
                    /* If current swap mode is Update, Erase indicator sector in non active block
                     * to proceed swap system to update-erased state */
                    returnCode = FLASH_Erase(config, address + (ftfxConfig->flashDesc.totalSize >> 1u),
                                             ftfxConfig->opsConfig.addrAligment.sectorCmd, (uint32_t)kFTFx_ApiEraseKey);
                    break;
                case kFTFx_SwapStateUpdateErased:
                    /* If current swap mode is Update or Update-Erased, progress Swap to COMPLETE State */
                    returnCode = FTFx_CMD_SwapControl(ftfxConfig, address, kFTFx_SwapControlOptionSetInCompleteState,
                                                      &returnInfo);
                    break;
                case kFTFx_SwapStateComplete:
                    break;
                case kFTFx_SwapStateDisabled:
                    /* When swap system is in disabled state, We need to clear swap system back to uninitialized
                     * by issuing EraseAllBlocks command */
                    returnCode = kStatus_FTFx_SwapSystemNotInUninitialized;
                    break;
                default:
                    returnCode = kStatus_FTFx_InvalidArgument;
                    break;
            }
        }
        if (returnCode != kStatus_FTFx_Success)
        {
            break;
        }
    } while (!((kFTFx_SwapStateComplete == returnInfo.flashSwapState) && isSetEnable));

    return returnCode;
}
#endif /* FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP */

/*!
 * @brief Returns the protection state of the desired flash area via the pointer passed into the function.
 */
status_t FLASH_IsProtected(flash_config_t *config,
                           uint32_t start,
                           uint32_t lengthInBytes,
                           flash_prot_state_t *protection_state)
{
    status_t returnCode;
    ftfx_config_t *ftfxConfig;
    uint8_t flashIndex;

    if (protection_state == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    ftfxConfig = &config->ftfxConfig[flashIndex];

#if (FTFx_FLASH_COUNT > 1U)
    if (0U != (ftfxConfig->flashDesc.feature.hasProtControl))
#endif
    {
        uint32_t endAddress;           /* end address for protection check */
        uint32_t regionCheckedCounter; /* increments each time the flash address was checked for
                                        * protection status */
        uint32_t regionCounter;        /* incrementing variable used to increment through the flash
                                        * protection regions */
        uint32_t protectStatusCounter; /* increments each time a flash region was detected as protected */
        uint8_t flashRegionProtectStatus[MAX_FLASH_PROT_REGION_COUNT]; /* array of the protection
                                                                        * status for each
                                                                        * protection region */
        for (uint32_t i = 0U; i < (uint32_t)MAX_FLASH_PROT_REGION_COUNT;
             i++)                                        /* The protection register is initialized to the */
        {                                                /* unprotected state by default. */
            flashRegionProtectStatus[i] = (uint8_t)0xFF; /* The array is initialized to all 1 */
        }

        uint32_t
            flashRegionAddress[MAX_FLASH_PROT_REGION_COUNT + 1U]; /* array of the start addresses for each flash
                                                                   * protection region. Note this is REGION_COUNT+1
                                                                   * due to requiring the next start address after
                                                                   * the end of flash for loop-check purposes below */
        bool isBreakNeeded = false;
        /* Calculate Flash end address */
        endAddress = start + lengthInBytes;

        /* populate the flashRegionAddress array with the start address of each flash region */
        regionCounter = 0U; /* make sure regionCounter is initialized to 0 first */
        /* populate up to 33rd element of array, this is the next address after end of flash array */
        while (regionCounter <= ftfxConfig->flashDesc.protectRegionMem.count)
        {
            flashRegionAddress[regionCounter] = ftfxConfig->flashDesc.protectRegionMem.base +
                                                ftfxConfig->flashDesc.protectRegionMem.size * regionCounter;
            regionCounter++;
        }

        /* populate flashRegionProtectStatus array with status information
         * Protection status for each region is stored in the FPROT[3:0] registers
         * Each bit represents one region of flash
         * 4 registers * 8-bits-per-register = 32-bits (32-regions)
         * The convention is:
         * FPROT3[bit 0] is the first protection region (start of flash memory)
         * FPROT0[bit 7] is the last protection region (end of flash memory)
         * regionCounter is used to determine which FPROT[3:0] register to check for protection status
         * Note: FPROT=1 means NOT protected, FPROT=0 means protected */
        regionCounter                            = 0U; /* make sure regionCounter is initialized to 0 first */
        static volatile uint32_t *const kFPROTLx = (volatile uint32_t *)(uint32_t)&FTFx_FPROTL3_REG;

#if defined(FTFx_FLASH0_HAS_HIGH_PROT_REG) && FTFx_FLASH0_HAS_HIGH_PROT_REG
        static volatile uint32_t *const kFPROTHx = (volatile uint32_t *)(uint32_t)&FTFx_FPROTH3_REG;
#endif

#if defined(FTFx_FLASH1_HAS_INT_PROT_REG) && FTFx_FLASH1_HAS_INT_PROT_REG
        static volatile uint16_t *const kFPROTSx = (volatile uint16_t *)(uint32_t)&FTFx_FPROTSL_REG;
#endif
        while (regionCounter < ftfxConfig->flashDesc.protectRegionMem.count)
        {
#if (FTFx_FLASH_COUNT > 1U)
            if ((0U == ftfxConfig->flashDesc.index) || (0U != ftfxConfig->flashDesc.feature.hasIndProtReg))
#endif
            {
#if defined(MAX_FLASH_PROT_REGION_COUNT) && (MAX_FLASH_PROT_REGION_COUNT <= 32U)
                if (regionCounter < (uint32_t)MAX_FLASH_PROT_REGION_COUNT)
                {
                    flashRegionProtectStatus[regionCounter] = (uint8_t)(((kFPROTLx[0]) >> regionCounter) & 0x1U);
                }
#else
                if (regionCounter < 32u)
                {
                    flashRegionProtectStatus[regionCounter] = (uint8_t)(((kFPROTLx[0]) >> regionCounter) & 0x1U);
                }
#endif
#if defined(MAX_FLASH_PROT_REGION_COUNT) && (MAX_FLASH_PROT_REGION_COUNT == 64u)
                else if (regionCounter < 64U)
                {
                    flashRegionProtectStatus[regionCounter] =
                        (uint8_t)(((kFPROTHx[0]) >> (regionCounter - 32U)) & 0x1U);
                }
#endif
                else
                {
                    isBreakNeeded = true;
                }
                regionCounter++;
            }
#if defined(FTFx_FLASH1_HAS_INT_PROT_REG) && FTFx_FLASH1_HAS_INT_PROT_REG
            else if ((1U == ftfxConfig->flashDesc.index) && (0U != ftfxConfig->flashDesc.feature.hasIndProtReg))
            {
                /* Note: So far protection region count may be 8/16 */
                if (regionCounter < 16U)
                {
                    flashRegionProtectStatus[regionCounter] = (uint8_t)((kFPROTSx[0] >> regionCounter) & (0x01u));
                }
                else
                {
                    isBreakNeeded = true;
                }
                regionCounter++;
            }
#endif /* FTFx_FLASH1_HAS_INT_PROT_REG */
#if (FTFx_FLASH_COUNT > 1U)
            else
            {
                return kStatus_FTFx_InvalidArgument;
            }
#endif
            if (isBreakNeeded)
            {
                break;
            }
        }

        /* loop through the flash regions and check
         * desired flash address range for protection status
         * loop stops when it is detected that start has exceeded the endAddress */
        regionCounter        = 0U; /* make sure regionCounter is initialized to 0 first */
        regionCheckedCounter = 0U;
        protectStatusCounter = 0U; /* make sure protectStatusCounter is initialized to 0 first */
        while (start < endAddress)
        {
            /* check to see if the address falls within this protection region
             * Note that if the entire flash is to be checked, the last protection
             * region checked would consist of the last protection start address and
             * the start address following the end of flash */
            if ((start >= flashRegionAddress[regionCounter]) && (start < flashRegionAddress[regionCounter + 1U]))
            {
                /* increment regionCheckedCounter to indicate this region was checked */
                regionCheckedCounter++;

                /* check the protection status of this region
                 * Note: FPROT=1 means NOT protected, FPROT=0 means protected */
                if (0U == flashRegionProtectStatus[regionCounter])
                {
                    /* increment protectStatusCounter to indicate this region is protected */
                    protectStatusCounter++;
                }
                start +=
                    ftfxConfig->flashDesc.protectRegionMem.size; /* increment to an address within the next region */
            }
            regionCounter++; /* increment regionCounter to check for the next flash protection region */
        }

        /* if protectStatusCounter == 0, then no region of the desired flash region is protected */
        if (protectStatusCounter == 0U)
        {
            *protection_state = kFLASH_ProtectionStateUnprotected;
        }
        /* if protectStatusCounter == regionCheckedCounter, then each region checked was protected */
        else if (protectStatusCounter == regionCheckedCounter)
        {
            *protection_state = kFLASH_ProtectionStateProtected;
        }
        /* if protectStatusCounter != regionCheckedCounter, then protection status is mixed
         * In other words, some regions are protected while others are unprotected */
        else
        {
            *protection_state = kFLASH_ProtectionStateMixed;
        }
    }
#if (FTFx_FLASH_COUNT > 1U)
    else
    {
        *protection_state = kFLASH_ProtectionStateUnprotected;
    }
#endif

    return kStatus_FTFx_Success;
}

#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
/*!
 * @brief Returns the access state of the desired flash area via the pointer passed into the function.
 *
 * This function retrieves the current flash access status for a given
 * flash area as determined by the start address and length.
 */
status_t FLASH_IsExecuteOnly(flash_config_t *config,
                             uint32_t start,
                             uint32_t lengthInBytes,
                             flash_xacc_state_t *access_state)
{
    status_t returnCode;
    ftfx_config_t *ftfxConfig;
    uint8_t flashIndex;

    if (access_state == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    returnCode = flash_check_range_to_get_index(config, start, lengthInBytes, &flashIndex);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    ftfxConfig = &config->ftfxConfig[flashIndex];

    /* store the execute only segment count */
    uint32_t executeOnlySegmentCounter = 0U;

    /* Calculate end address */
    uint32_t endAddress = start + lengthInBytes;

    /* Aligning start address and end address */
    uint32_t alignedStartAddress = ALIGN_DOWN(start, ftfxConfig->flashDesc.accessSegmentMem.size);
    uint32_t alignedEndAddress   = ALIGN_UP(endAddress, ftfxConfig->flashDesc.accessSegmentMem.size);

    uint32_t u32flag      = 1U;
    uint32_t segmentIndex = 0U;

    /* Calculate the execute only segment Count */
    uint32_t maxSupportedExecuteOnlySegmentCount =
        (alignedEndAddress - alignedStartAddress) / ftfxConfig->flashDesc.accessSegmentMem.size;

    while (start < endAddress)
    {
        uint32_t xacc              = 0U;
        bool isInvalidSegmentIndex = false;

        /* Calculate which segmentIndex the address is in */
        segmentIndex =
            (start - ftfxConfig->flashDesc.accessSegmentMem.base) / ftfxConfig->flashDesc.accessSegmentMem.size;

        if ((0U == ftfxConfig->flashDesc.index) || (0U != ftfxConfig->flashDesc.feature.hasIndXaccReg))
        {
            /* For primary flash, The eight XACC registers allow up to 64 restricted segments of equal memory size.
             */
            if (segmentIndex < 32U)
            {
                xacc = *(const volatile uint32_t *)(uint32_t)&FTFx_XACCL3_REG;
            }
            else if (segmentIndex < ftfxConfig->flashDesc.accessSegmentMem.count)
            {
                xacc = *(const volatile uint32_t *)(uint32_t)&FTFx_XACCH3_REG;
                segmentIndex -= 32U;
            }
            else
            {
                isInvalidSegmentIndex = true;
            }
        }
#if defined(FTFx_FLASH1_HAS_INT_XACC_REG) && FTFx_FLASH1_HAS_INT_XACC_REG
        else if ((ftfxConfig->flashDesc.index == 1U) && (0u != ftfxConfig->flashDesc.feature.hasIndXaccReg))
        {
            /* For secondary flash, The two XACCS registers allow up to 16 restricted segments of equal memory size.
             */
            if (segmentIndex < 8U)
            {
                xacc = *(const volatile uint8_t *)&FTFx_XACCSL_REG;
            }
            else if (segmentIndex < ftfxConfig->flashDesc.accessSegmentMem.count)
            {
                xacc = *(const volatile uint8_t *)&FTFx_XACCSH_REG;
                segmentIndex -= 8U;
            }
            else
            {
                isInvalidSegmentIndex = true;
            }
        }
#endif
        else
        {
            return kStatus_FTFx_InvalidArgument;
        }

        if (isInvalidSegmentIndex)
        {
            break;
        }

        /* Determine if this address range is in a execute-only protection flash segment. */
        if (0U != ((~xacc) & (u32flag << segmentIndex)))
        {
            executeOnlySegmentCounter++;
        }
        /* Calculate tne next start address */
        start += ftfxConfig->flashDesc.accessSegmentMem.size;
    }

    if (executeOnlySegmentCounter < 1u)
    {
        *access_state = kFLASH_AccessStateUnLimited;
    }
    else if (executeOnlySegmentCounter < maxSupportedExecuteOnlySegmentCount)
    {
        *access_state = kFLASH_AccessStateMixed;
    }
    else
    {
        *access_state = kFLASH_AccessStateExecuteOnly;
    }

    return kStatus_FTFx_Success;
}
#endif /* FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL */

/*!
 * @brief Sets the PFlash Protection to the intended protection status.
 *
 * @param config A pointer to storage for the driver runtime state.
 * @param protectStatus The expected protect status to set to the PFlash protection register. Each bit is
 * corresponding to protection of 1/32(64) of the total PFlash. The least significant bit is corresponding to the lowest
 * address area of PFlash. The most significant bit is corresponding to the highest address area of PFlash. There are
 * two possible cases as shown below:
 *       0: this area is protected.
 *       1: this area is unprotected.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_CommandFailure Run-time error during command execution.
 */
status_t FLASH_PflashSetProtection(flash_config_t *config, pflash_prot_status_t *protectStatus)
{
    if ((config == NULL) || (protectStatus == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Most boards support program flash protect feature, The FPROT registers
     * define which program flash regions are protected from program and erase operations.
     * Protected flash regions cannot have their content changed;
     * that is, these regions cannot be programmed and cannot be erased by any flash command
     */
#if (FTFx_FLASH_COUNT > 1U)
    if (0U != (config->ftfxConfig[0].flashDesc.feature.hasProtControl))
#endif
    {
        if (config->ftfxConfig[0].flashDesc.feature.ProtRegBits >= 32U)
        {
            /* set PFlash protection register, unprotected regions are marked with a 1 and
             * setting PFlash protection register, unprotected regions are marked with a 1 and
             * protected regions use a 0; each bit of FPROT register can only be changed from 1s to 0s
             * while all bits with 0s to 1s transitions are ignored.
             */
            *kFPROTL = protectStatus->protl;
            if (protectStatus->protl != *kFPROTL)
            {
                return kStatus_FTFx_CommandFailure;
            }
        }
#if defined(FTFx_FLASH0_HAS_HIGH_PROT_REG) && FTFx_FLASH0_HAS_HIGH_PROT_REG
        /* For primary flash with eight PROT registers allow up to 64 protected segments of equal memory size. */
        if (config->ftfxConfig[0].flashDesc.feature.ProtRegBits == 64U)
        {
            *kFPROTH = protectStatus->proth;
            if (protectStatus->proth != *kFPROTH)
            {
                return kStatus_FTFx_CommandFailure;
            }
        }
#endif
    }
#if defined(FTFx_FLASH1_HAS_INT_PROT_REG) && FTFx_FLASH1_HAS_INT_PROT_REG
    else if ((0U != config->ftfxConfig[1].flashDesc.feature.hasProtControl) &&
             (0U != config->ftfxConfig[1].flashDesc.feature.hasIndProtReg))
    {
        /* For secondary flash with two FPROT registers allow up to 16 protected segments of equal memory size. */
        if (config->ftfxConfig[1].flashDesc.feature.ProtRegBits == 16U)
        {
            *kFPROTSL = protectStatus->protsl;
            if (protectStatus->protsl != *kFPROTSL)
            {
                return kStatus_FTFx_CommandFailure;
            }
            *kFPROTSH = protectStatus->protsh;
            if (protectStatus->protsh != *kFPROTSH)
            {
                return kStatus_FTFx_CommandFailure;
            }
        }
    }
#endif
#if (FTFx_FLASH_COUNT > 1U)
    else
    {
        /*do nothing*/
    }
#endif

    return kStatus_FTFx_Success;
}

/*!
 * @brief Gets the PFlash protection status.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param protectStatus  Protect status returned by the PFlash IP. Each bit is corresponding to the protection of
 * 1/32(64)
 * of the total PFlash. The least significant bit corresponds to the lowest address area of the PFlash.
 * The most significant bit corresponds to the highest address area of PFlash. There are two possible cases as shown
 * below: 0: this area is protected. 1: this area is unprotected.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 */
status_t FLASH_PflashGetProtection(flash_config_t *config, pflash_prot_status_t *protectStatus)
{
    if ((config == NULL) || (protectStatus == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

#if (FTFx_FLASH_COUNT > 1U)
    if (0U != (config->ftfxConfig[0].flashDesc.feature.hasProtControl))
#endif
    {
        /* get the flash protect status */
        if (config->ftfxConfig[0].flashDesc.feature.ProtRegBits >= 32U)
        {
            protectStatus->protl = *kFPROTL;
        }
#if defined(FTFx_FLASH0_HAS_HIGH_PROT_REG) && FTFx_FLASH0_HAS_HIGH_PROT_REG
        /* For primary flash with eight PROT registers allow up to 64 protected segments of equal memory size. */
        if (config->ftfxConfig[0].flashDesc.feature.ProtRegBits == 64U)
        {
            protectStatus->proth = *kFPROTH;
        }
#endif
    }
#if defined(FTFx_FLASH1_HAS_INT_PROT_REG) && FTFx_FLASH1_HAS_INT_PROT_REG
    /* For secondary flash with two FPROT registers allow up to 16 protected segments of equal memory size. */
    else if ((0U != config->ftfxConfig[1].flashDesc.feature.hasProtControl) &&
             (0U != config->ftfxConfig[1].flashDesc.feature.hasIndProtReg))
    {
        if (config->ftfxConfig[0].flashDesc.feature.ProtRegBits == 16U)
        {
            protectStatus->protsl = *kFPROTSL;
            protectStatus->protsh = *kFPROTSH;
        }
    }
#endif
#if (FTFx_FLASH_COUNT > 1U)
    else
    {
        /*do nothing*/
    }
#endif
    return kStatus_FTFx_Success;
}

/*!
 * @brief Returns the desired flash property.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param whichProperty The desired property from the list of properties in
 *        enum flash_property_tag_t
 * @param value A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_FTFx_Success API was executed successfully.
 * @retval #kStatus_FTFx_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_FTFx_UnknownProperty An unknown property tag.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    if ((config == NULL) || (value == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    status_t status = kStatus_FTFx_Success;

    switch (whichProperty)
    {
        /* gat Pflash0 sector size */
        case kFLASH_PropertyPflash0SectorSize:
            *value = config->ftfxConfig[0].flashDesc.sectorSize;
            break;
        /* gat Pflash0 total size */
        case kFLASH_PropertyPflash0TotalSize:
            *value = config->ftfxConfig[0].flashDesc.totalSize;
            break;
        /* gat Pflash0 block size */
        case kFLASH_PropertyPflash0BlockSize:
            *value = config->ftfxConfig[0].flashDesc.totalSize / config->ftfxConfig[0].flashDesc.blockCount;
            break;
        /* gat Pflash0 block cont */
        case kFLASH_PropertyPflash0BlockCount:
            *value = config->ftfxConfig[0].flashDesc.blockCount;
            break;
        /* gat Pflash0 block base address */
        case kFLASH_PropertyPflash0BlockBaseAddr:
            *value = config->ftfxConfig[0].flashDesc.blockBase;
            break;
        /* gat Pflash0 fac support feature */
        case kFLASH_PropertyPflash0FacSupport:
            *value = (uint32_t)config->ftfxConfig[0].flashDesc.feature.hasXaccControl;
            break;
        /* gat Pflash0 access segment size feature */
        case kFLASH_PropertyPflash0AccessSegmentSize:
            *value = config->ftfxConfig[0].flashDesc.accessSegmentMem.size;
            break;
        /* gat Pflash0 access segment count feature */
        case kFLASH_PropertyPflash0AccessSegmentCount:
            *value = config->ftfxConfig[0].flashDesc.accessSegmentMem.count;
            break;

#if defined(FTFx_DRIVER_HAS_FLASH1_SUPPORT) && FTFx_DRIVER_HAS_FLASH1_SUPPORT
        case kFLASH_PropertyPflash1SectorSize:
            *value = config->ftfxConfig[1].flashDesc.sectorSize;
            break;
        case kFLASH_PropertyPflash1TotalSize:
            *value = config->ftfxConfig[1].flashDesc.totalSize;
            break;
        case kFLASH_PropertyPflash1BlockSize:
            *value = config->ftfxConfig[1].flashDesc.totalSize / config->ftfxConfig[1].flashDesc.blockCount;
            break;
        case kFLASH_PropertyPflash1BlockCount:
            *value = config->ftfxConfig[1].flashDesc.blockCount;
            break;
        case kFLASH_PropertyPflash1BlockBaseAddr:
            *value = config->ftfxConfig[1].flashDesc.blockBase;
            break;
        case kFLASH_PropertyPflash1FacSupport:
            *value = (uint32_t)config->ftfxConfig[1].flashDesc.feature.hasXaccControl;
            break;
        case kFLASH_PropertyPflash1AccessSegmentSize:
            *value = config->ftfxConfig[1].flashDesc.accessSegmentMem.size;
            break;
        case kFLASH_PropertyPflash1AccessSegmentCount:
            *value = config->ftfxConfig[1].flashDesc.accessSegmentMem.count;
            break;
#endif
        /* gat FlexRam block base addrese */
        case kFLASH_PropertyFlexRamBlockBaseAddr:
            *value = config->ftfxConfig[0].flexramBlockBase;
            break;
        /* gat FlexRam total size  */
        case kFLASH_PropertyFlexRamTotalSize:
            *value = config->ftfxConfig[0].flexramTotalSize;
            break;

        default: /* catch inputs that are not recognized */
            status = kStatus_FTFx_UnknownProperty;
            break;
    }

    return status;
}

/*!
 * @brief init flash FPROT, XACC registers and Independent flash block
 */
static void flash_init_features(ftfx_config_t *config)
{
    /* Initialize whether flash0 has independent block, protection registers and
     * execute only access registers */
#if (FTFx_FLASH_COUNT > 1U)
    if (config->flashDesc.index == 0U)
#endif
    {
        config->flashDesc.feature.isIndBlock      = 1U;
        config->flashDesc.feature.hasIndPfsizeReg = 1U;
        config->flashDesc.feature.hasIndProtReg   = 1U;
        config->flashDesc.feature.hasIndXaccReg   = 1U;
    }
    /* if another flash exists */
#if defined(FTFx_DRIVER_HAS_FLASH1_SUPPORT) && FTFx_DRIVER_HAS_FLASH1_SUPPORT
    else if (config->flashDesc.index == 1U)
    {
        config->flashDesc.feature.isIndBlock      = FTFx_FLASH1_IS_INDEPENDENT_BLOCK;
        config->flashDesc.feature.hasIndPfsizeReg = config->flashDesc.feature.isIndBlock;
        config->flashDesc.feature.hasIndProtReg   = FTFx_FLASH1_HAS_INT_PROT_REG;
        config->flashDesc.feature.hasIndXaccReg   = FTFx_FLASH1_HAS_INT_XACC_REG;
    }
#endif
#if (FTFx_FLASH_COUNT > 1U)
    else
    {
        /*do nothing*/
    }
#endif
    /* init  protection Registers feature*/
    config->flashDesc.feature.hasProtControl = 1U;
    /* init  Execute-only Access Registers feature*/
    config->flashDesc.feature.hasXaccControl = FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL;
}

/*!
 * @brief Initializes the flash operation config.
 */
static void flash_opsonfig_Init(flash_config_t *config, uint8_t flashIndex)
{
    uint32_t pflashStartAddress;
    uint32_t pflashBlockSize;
    uint32_t pflashBlockCount;
    uint32_t pflashBlockSectorSize;
    uint32_t pfsizeMask;
    uint32_t pfsizeShift;
    uint32_t pflashBlockWriteUnitSize;  /* store P-Flash write unit size */
    uint32_t pflashSectorCmdAlignment;  /* store P-Flash Erase sector command address alignment */
    uint32_t pflashSectionCmdAlignment; /* store Rrogram/Verify section command address alignment */

#if (FTFx_FLASH_COUNT > 1U)
    if (flashIndex == 1U)
    {
        pflashStartAddress        = FLASH1_FEATURE_PFLASH_START_ADDRESS;
        pflashBlockSize           = FLASH1_FEATURE_PFLASH_BLOCK_SIZE;
        pflashBlockCount          = FLASH1_FEATURE_PFLASH_BLOCK_COUNT;
        pflashBlockSectorSize     = FLASH1_FEATURE_PFLASH_BLOCK_SECTOR_SIZE;
        pflashBlockWriteUnitSize  = FLASH1_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE;
        pflashSectorCmdAlignment  = FLASH1_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT;
        pflashSectionCmdAlignment = FLASH1_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT;
        pfsizeMask                = SIM_FLASH1_PFSIZE_MASK;
        pfsizeShift               = SIM_FLASH1_PFSIZE_SHIFT;
    }
    else
#endif
    {
        pflashStartAddress        = FLASH0_FEATURE_PFLASH_START_ADDRESS; /* get P-Flash start address */
        pflashBlockSize           = FLASH0_FEATURE_PFLASH_BLOCK_SIZE;
        pflashBlockCount          = FLASH0_FEATURE_PFLASH_BLOCK_COUNT;
        pflashBlockSectorSize     = FLASH0_FEATURE_PFLASH_BLOCK_SECTOR_SIZE;
        pflashBlockWriteUnitSize  = FLASH0_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE;
        pflashSectorCmdAlignment  = FLASH0_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT;
        pflashSectionCmdAlignment = FLASH0_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT;
        pfsizeMask                = SIM_FLASH0_PFSIZE_MASK;
        pfsizeShift               = SIM_FLASH0_PFSIZE_SHIFT;
    }
    /* init current flash start address */
    config->ftfxConfig[flashIndex].flashDesc.blockBase = pflashStartAddress;
    /* init current flash block count */
    config->ftfxConfig[flashIndex].flashDesc.blockCount = pflashBlockCount;
    /* init current flash block sector size */
    config->ftfxConfig[flashIndex].flashDesc.sectorSize = pflashBlockSectorSize;

#if (FTFx_FLASH_COUNT > 1U)
    if ((0U != config->ftfxConfig[flashIndex].flashDesc.feature.isIndBlock) &&
        (0U != config->ftfxConfig[flashIndex].flashDesc.feature.hasIndPfsizeReg))
#endif
    {
        /* Calculate flash memory size based on given parameter */
        config->ftfxConfig[flashIndex].flashDesc.totalSize =
            flash_calculate_mem_size(pflashBlockCount, pflashBlockSize, pfsizeMask, pfsizeShift);
    }
#if (FTFx_FLASH_COUNT > 1U)
    else
    {
        config->ftfxConfig[flashIndex].flashDesc.totalSize = pflashBlockCount * pflashBlockSize;
    }
#endif

    /* init P-Flash write unit size */
    config->ftfxConfig[flashIndex].opsConfig.addrAligment.blockWriteUnitSize = (uint8_t)pflashBlockWriteUnitSize;
    /* init P-Flash Erase sector command address alignment */
    config->ftfxConfig[flashIndex].opsConfig.addrAligment.sectorCmd = (uint8_t)pflashSectorCmdAlignment;
    /* init P-Flash Rrogram/Verify section command address alignment */
    config->ftfxConfig[flashIndex].opsConfig.addrAligment.sectionCmd = (uint8_t)pflashSectionCmdAlignment;
    /* init P-Flash Read resource command address alignment. */
    config->ftfxConfig[flashIndex].opsConfig.addrAligment.resourceCmd =
        (uint8_t)FSL_FEATURE_FLASH_PFLASH_RESOURCE_CMD_ADDRESS_ALIGMENT;
    /* init P-Flash Program check command address alignment. */
    config->ftfxConfig[flashIndex].opsConfig.addrAligment.checkCmd =
        (uint8_t)FSL_FEATURE_FLASH_PFLASH_CHECK_CMD_ADDRESS_ALIGMENT;
    /* init P-Flash swap command address alignment */
    config->ftfxConfig[flashIndex].opsConfig.addrAligment.swapCtrlCmd =
        (uint8_t)FSL_FEATURE_FLASH_PFLASH_SWAP_CONTROL_CMD_ADDRESS_ALIGMENT;
}

#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
/*! @brief init access segment feature */
static void flash_access_init(flash_config_t *config, uint8_t flashIndex)
{
    ftfx_spec_mem_t *specMem;

    /* start to initialize the structure of access segment */
#if defined(FTFx_FLASH1_HAS_INT_XACC_REG) && FTFx_FLASH1_HAS_INT_XACC_REG
    specMem = &config->ftfxConfig[flashIndex].flashDesc.accessSegmentMem;
    if (flashIndex == 1U)
    {
        specMem->base  = config->ftfxConfig[flashIndex].flashDesc.blockBase;
        specMem->size  = (uint32_t)kFTFx_AccessSegmentUnitSize << FTFx_FACSSS_REG;
        specMem->count = FTFx_FACSNS_REG;
    }
    else
#else
    specMem = &config->ftfxConfig[0].flashDesc.accessSegmentMem;
#endif /* FTFx_FLASH1_HAS_INT_XACC_REG */
    {
        specMem->base  = config->ftfxConfig[0].flashDesc.blockBase;
        specMem->size  = (uint32_t)kFTFx_AccessSegmentUnitSize << FTFx_FACSS_REG;
        specMem->count = FTFx_FACSN_REG;
    }
}
#endif /* FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL */

/*! @brief init protection feature */
static void flash_protection_init(flash_config_t *config, uint8_t flashIndex)
{
    uint32_t pflashProtectionRegionCount;
#if (FTFx_FLASH_COUNT > 1U)
    uint8_t i;

    if (flashIndex == 1U)
    {
        /* store flash0 Protection region count */
        pflashProtectionRegionCount = FLASH1_FEATURE_PFLASH_PROTECTION_REGION_COUNT;
    }
    else
#endif // #if (FTFx_FLASH_COUNT > 1U)
    {
        /* store flash0 Protection region count */
        pflashProtectionRegionCount = FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT;
    }

    /* Start to initialize the structure of protection features */
    ftfx_spec_mem_t *specMem;
    specMem = &config->ftfxConfig[flashIndex].flashDesc.protectRegionMem;
#if (FTFx_FLASH_COUNT > 1U)
    if (0U != (config->ftfxConfig[flashIndex].flashDesc.feature.hasIndProtReg))
#endif // #if (FTFx_FLASH_COUNT > 1U)
    {
        specMem->base  = config->ftfxConfig[flashIndex].flashDesc.blockBase;
        specMem->count = pflashProtectionRegionCount;
        /* Calculate flash prot segment size */
        specMem->size =
            flash_calculate_prot_segment_size(config->ftfxConfig[flashIndex].flashDesc.totalSize, specMem->count);
    }
#if (FTFx_FLASH_COUNT > 1U)
    else
    {
        uint32_t pflashTotalSize = 0U;
        specMem->base            = config->ftfxConfig[0].flashDesc.blockBase;
        specMem->count           = FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT;
        if (flashIndex == FTFx_FLASH_COUNT - 1U)
        {
            uint32_t segmentSize; /* store the flash protection region count */
            for (i = 0U; i < FTFx_FLASH_COUNT; i++)
            {
                /* get pflash total size*/
                pflashTotalSize += config->ftfxConfig[flashIndex].flashDesc.totalSize;
            }
            /* get pflash port segment size based on parameters */
            segmentSize = flash_calculate_prot_segment_size(pflashTotalSize, specMem->count);
            for (i = 0U; i < FTFx_FLASH_COUNT; i++)
            {
                /* init flash0 and flash1 port segment size */
                config->ftfxConfig[i].flashDesc.protectRegionMem.size = segmentSize;
            }
        }
    }
#endif // #if (FTFx_FLASH_COUNT > 1U)
}

/*!
 * @brief Calculate flash memory size based on given parameter
 */
static uint32_t flash_calculate_mem_size(uint32_t pflashBlockCount,
                                         uint32_t pflashBlockSize,
                                         uint32_t pfsizeMask,
                                         uint32_t pfsizeShift)
{
    uint8_t pfsize;
    uint32_t flashDensity;

    /* PFSIZE=0xf means that on customer parts the IFR was not correctly programmed.
     * We just use the pre-defined flash size in feature file here to support pre-production parts */
    pfsize = (uint8_t)((SIM_FCFG1_REG & pfsizeMask) >> pfsizeShift);
    if (pfsize == 0xfU)
    {
        flashDensity = pflashBlockCount * pflashBlockSize;
    }
    else
    {
        flashDensity = ((uint32_t)kPFlashDensities[pfsize]) << 10U;
    }

    return flashDensity;
}

/*!
 * @brief Calculate flash prot segment size
 */
static uint32_t flash_calculate_prot_segment_size(uint32_t flashSize, uint32_t segmentCount)
{
    uint32_t segmentSize;

    /* Calculate the size of the flash protection region
     * If the flash density is > 32KB, then protection region is 1/32 of total flash density
     * Else if flash density is < 32KB, then flash protection region is set to 1KB */
    if (flashSize > segmentCount * (uint32_t)kFTFx_MinProtectBlockSize)
    {
        segmentSize = flashSize / segmentCount;
    }
    else
    {
        segmentSize = (uint32_t)kFTFx_MinProtectBlockSize;
    }

    return segmentSize;
}

/*!
 * @brief Validates the given start address and length to get flash index
 */
static status_t flash_check_range_to_get_index(flash_config_t *config,
                                               uint32_t start,
                                               uint32_t lengthInBytes,
                                               uint8_t *flashIndex)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Validates the range of the given address */
    for (uint8_t index = 0U; index < FTFx_FLASH_COUNT; index++)
    {
        if ((start >= config->ftfxConfig[index].flashDesc.blockBase) &&
            ((start + lengthInBytes) <=
             (config->ftfxConfig[index].flashDesc.blockBase + config->ftfxConfig[index].flashDesc.totalSize)))
        {
            *flashIndex = config->ftfxConfig[index].flashDesc.index;
            return kStatus_FTFx_Success;
        }
    }

    return kStatus_FTFx_AddressError;
}

/*!
 * @brief Decide whether to convert the start address from primary flash to secondary flash based on the current start
 * address
 */
static void flash_convert_start_address(ftfx_config_t *config, uint32_t start)
{
    // The caller will guarantee that the config is valid
#if (FTFx_FLASH_COUNT > 1U)
    if ((0U != config->flashDesc.index) && (0U != config->flashDesc.feature.isIndBlock))
    {
        /* When required by the command, address bit 23 selects between main flash memory
         * (=0) and secondary flash memory (=1).*/
        config->opsConfig.convertedAddress = start - config->flashDesc.blockBase + 0x800000U;
    }
    else
#endif
    {
        config->opsConfig.convertedAddress = start;
    }
}

#if defined(FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP) && FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP
/*!
 * @brief Validates the given address to see if it is equal to swap indicator address in pflash swap IFR.
 */
static status_t flash_validate_swap_indicator_address(ftfx_config_t *config, uint32_t address)
{
    status_t returnCode;
    struct _flash_swap_ifr_field_config
    {
        uint16_t swapIndicatorAddress; /*!< A Swap indicator address field.*/
        uint16_t swapEnableWord;       /*!< A Swap enable word field.*/
        uint8_t reserved0[4];          /*!< A reserved field.*/
        uint8_t reserved1[2];          /*!< A reserved field.*/
        uint16_t swapDisableWord;      /*!< A Swap disable word field.*/
        uint8_t reserved2[4];          /*!< A reserved field.*/
    } flashSwapIfrFieldData;
    uint32_t swapIndicatorAddress;

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
    returnCode =
        FTFx_CMD_ReadResource(config, config->ifrDesc.resRange.pflashSwapIfrStart, (uint8_t *)&flashSwapIfrFieldData,
                              sizeof(flashSwapIfrFieldData), kFTFx_ResourceOptionFlashIfr);

    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }
#else
    {
        /* From RM, the actual info are stored in FCCOB6,7 */
        uint32_t returnValue[2];
        returnCode = FTFx_CMD_ReadOnce(config, (uint32_t)kFLASH_RecordIndexSwapAddr, (uint8_t *)returnValue, 4U);
        if (returnCode != kStatus_FTFx_Success)
        {
            return returnCode;
        }
        flashSwapIfrFieldData.swapIndicatorAddress = (uint16_t)returnValue[0];
        returnCode = FTFx_CMD_ReadOnce(config, (uint32_t)kFLASH_RecordIndexSwapEnable, (uint8_t *)returnValue, 4U);
        if (returnCode != kStatus_FTFx_Success)
        {
            return returnCode;
        }

        returnCode = FTFx_CMD_ReadOnce(config, (uint32_t)kFLASH_RecordIndexSwapDisable, (uint8_t *)returnValue, 4U);
        if (returnCode != kStatus_FTFx_Success)
        {
            return returnCode;
        }
    }
#endif

    /* The high bits value of Swap Indicator Address is stored in Program Flash Swap IFR Field,
     * the low several bit value of Swap Indicator Address is always 1'b0 */
    swapIndicatorAddress =
        (uint32_t)flashSwapIfrFieldData.swapIndicatorAddress * config->opsConfig.addrAligment.swapCtrlCmd;
    if (address != swapIndicatorAddress)
    {
        return kStatus_FTFx_SwapIndicatorAddressError;
    }

    return returnCode;
}
#endif /* FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP */

status_t FLASH_GetCommandState(void)
{
    uint8_t registerValue;
    uint32_t idleFlag;

    /* Get flash status register value */
    registerValue = FTFx->FSTAT;

    /* Check DONE bit of the flash status register */
    idleFlag = ((uint32_t)registerValue & FTFx_FSTAT_CCIF_MASK) >> FTFx_FSTAT_CCIF_SHIFT;
    if (idleFlag == 0U)
    {
        return kStatus_FTFx_CommandOperationInProgress;
    }
    else
    {
        /* Check error bits */
        /* checking access error */
        if (0U != (registerValue & FTFx_FSTAT_ACCERR_MASK))
        {
            return kStatus_FTFx_AccessError;
        }
        /* checking protection error */
        else if (0U != (registerValue & FTFx_FSTAT_FPVIOL_MASK))
        {
            return kStatus_FTFx_ProtectionViolation;
        }
        /* checking MGSTAT0 non-correctable error */
        else if (0U != (registerValue & FTFx_FSTAT_MGSTAT0_MASK))
        {
            return kStatus_FTFx_CommandFailure;
        }
        else
        {
            return kStatus_FTFx_Success;
        }
    }
}
