/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_ftfx_controller.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flash"
#endif

/*!
 * @name Flash controller command numbers
 * @{
 */
#define FTFx_VERIFY_BLOCK                    0x00U /*!< RD1BLK*/
#define FTFx_VERIFY_SECTION                  0x01U /*!< RD1SEC*/
#define FTFx_PROGRAM_CHECK                   0x02U /*!< PGMCHK*/
#define FTFx_READ_RESOURCE                   0x03U /*!< RDRSRC*/
#define FTFx_PROGRAM_LONGWORD                0x06U /*!< PGM4*/
#define FTFx_PROGRAM_PHRASE                  0x07U /*!< PGM8*/
#define FTFx_ERASE_BLOCK                     0x08U /*!< ERSBLK*/
#define FTFx_ERASE_SECTOR                    0x09U /*!< ERSSCR*/
#define FTFx_PROGRAM_SECTION                 0x0BU /*!< PGMSEC*/
#define FTFx_GENERATE_CRC                    0x0CU /*!< CRCGEN*/
#define FTFx_VERIFY_ALL_BLOCK                0x40U /*!< RD1ALL*/
#define FTFx_READ_ONCE                       0x41U /*!< RDONCE or RDINDEX*/
#define FTFx_PROGRAM_ONCE                    0x43U /*!< PGMONCE or PGMINDEX*/
#define FTFx_ERASE_ALL_BLOCK                 0x44U /*!< ERSALL*/
#define FTFx_SECURITY_BY_PASS                0x45U /*!< VFYKEY*/
#define FTFx_SWAP_CONTROL                    0x46U /*!< SWAP*/
#define FTFx_ERASE_ALL_BLOCK_UNSECURE        0x49U /*!< ERSALLU*/
#define FTFx_VERIFY_ALL_EXECUTE_ONLY_SEGMENT 0x4AU /*!< RD1XA*/
#define FTFx_ERASE_ALL_EXECUTE_ONLY_SEGMENT  0x4BU /*!< ERSXA*/
#define FTFx_PROGRAM_PARTITION               0x80U /*!< PGMPART*/
#define FTFx_SET_FLEXRAM_FUNCTION            0x81U /*!< SETRAM*/
/*@}*/

/*!
 * @brief Constants for execute-in-RAM flash function.
 */
enum _ftfx_ram_func_constants
{
    kFTFx_RamFuncMaxSizeInWords = 16U, /*!< The maximum size of execute-in-RAM function.*/
};

/*! @brief A function pointer used to point to relocated flash_run_command() */
typedef void (*callFtfxRunCommand_t)(FTFx_REG8_ACCESS_TYPE ftfx_fstat);

/*!
 * @name Enumeration for Flash security register code
 * @{
 */
enum _ftfx_fsec_register_code
{
    kFTFx_FsecRegCode_KEYEN_Enabled = 0x80U,
    kFTFx_FsecRegCode_SEC_Unsecured = 0x02U
};
/*@}*/

#if defined(FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD) && FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
/*!
 * @brief Enumeration for flash config area.
 */
enum _ftfx_pflash_config_area_range
{
    kFTFx_PflashConfigAreaStart = 0x400U,
    kFTFx_PflashConfigAreaEnd   = 0x40FU
};
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*! @brief Init IFR memory related info */
static void ftfx_init_ifr(ftfx_config_t *config);

#if FTFx_DRIVER_IS_FLASH_RESIDENT
/*! @brief Copy flash_run_command() to RAM*/
static void ftfx_copy_run_command_to_ram(uint32_t *ftfxRunCommand);
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

/*! @brief Internal function Flash command sequence. Called by driver APIs only*/
static status_t ftfx_command_sequence(ftfx_config_t *config);

/*! @brief Internal function Flash asynchronous command sequence. Called by driver APIs only*/
static void ftfx_command_sequence_non_blocking(ftfx_config_t *config);

/*! @brief Validates the range and alignment of the given address range.*/
static status_t ftfx_check_mem_range(ftfx_config_t *config,
                                     uint32_t startAddress,
                                     uint32_t lengthInBytes,
                                     uint8_t alignmentBaseline);

/*! @brief Validates the given user key for flash erase APIs.*/
static status_t ftfx_check_user_key(uint32_t key);

/*! @brief Reads word from byte address.*/
static uint32_t ftfx_read_word_from_byte_address(const uint8_t *src);

/*! @brief Writes word to byte address.*/
static void ftfx_write_word_to_byte_address(uint8_t *dst, uint32_t word);

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
/*! @brief Validates the range of the given resource address.*/
static status_t ftfx_check_resource_range(ftfx_config_t *config,
                                          uint32_t start,
                                          uint32_t lengthInBytes,
                                          uint32_t alignmentBaseline,
                                          ftfx_read_resource_opt_t option);
#endif /* FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD */

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
/*! @brief Validates the given flexram function option.*/
static inline status_t ftfx_check_flexram_function_option(ftfx_flexram_func_opt_t option);
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

#if defined(FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD) && FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
/*! @brief Validates the given swap control option.*/
static status_t ftfx_check_swap_control_option(ftfx_swap_control_opt_t option);
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if FTFx_DRIVER_IS_FLASH_RESIDENT
/*!
 * @brief Position independent code of flash_run_command
 *
 * Note1: The prototype of C function is shown as below:
 * @code
 *   void flash_run_command(FTFx_REG8_ACCESS_TYPE ftfx_fstat)
 *   {
 *       *ftfx_fstat = FTFx_FSTAT_CCIF_MASK;
 *
 *       while (!((*ftfx_fstat) & FTFx_FSTAT_CCIF_MASK))
 *       {
 *       }
 *   }
 * @endcode
 * Note2: The binary code is generated by IAR 7.70.1
 */
static const uint32_t s_ftfxRunCommandFunctionCode[] = {
    0x70012180u,
    0x420a7802u,
    0x4770d0fcu,
};
#if (!FTFx_DRIVER_IS_EXPORTED)
/*! @brief A static buffer used to hold flash_run_command() */
static uint32_t s_ftfxRunCommand[kFTFx_RamFuncMaxSizeInWords];
#endif /* (!FTFx_DRIVER_IS_EXPORTED) */
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

/*! @brief Access to FTFx Registers */
static volatile uint32_t *const kFCCOBx = (volatile uint32_t *)(uint32_t)&FTFx_FCCOB3_REG;

#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
/*! @brief Table of eeprom sizes. */
static const uint16_t kEepromDensities[16] = {
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0000, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0001,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0010, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0011,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0100, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0101,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0110, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0111,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1000, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1001,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1010, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1011,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1100, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1101,
    FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1110, FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1111};
/*! @brief Table of dflash sizes. */
static const uint32_t kDflashDensities[16] = {
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0000, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0001,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0010, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0011,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0100, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0101,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0110, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0111,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1000, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1001,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1010, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1011,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1100, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1101,
    FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1110, FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1111};
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initializes the global flash properties structure members.
 */
void FTFx_API_Init(ftfx_config_t *config)
{
    if (config == NULL)
    {
        return;
    }
    config->runCmdFuncAddr.callFlashCommand = NULL;
    config->flexramBlockBase                = FSL_FEATURE_FLASH_FLEX_RAM_START_ADDRESS;
    config->flexramTotalSize                = FSL_FEATURE_FLASH_FLEX_RAM_SIZE;

    /* copy required flash command to RAM */
#if FTFx_DRIVER_IS_FLASH_RESIDENT
    config->runCmdFuncAddr.commadAddr = (uint32_t)s_ftfxRunCommand;
    ftfx_copy_run_command_to_ram((uint32_t *)config->runCmdFuncAddr.commadAddr);
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

    ftfx_init_ifr(config);
}

#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
/*!
 * @brief Updates FlexNVM memory partition status according to data flash 0 IFR.
 */
status_t FTFx_API_UpdateFlexnvmPartitionStatus(ftfx_config_t *config)
{
    struct _dflash_ifr_field_config
    {
        uint32_t reserved0;
        uint8_t FlexNVMPartitionCode;
        uint8_t EEPROMDataSetSize;
        uint16_t reserved1;
    } dataIFRReadOut;
    uint32_t flexnvmInfoIfrAddr;
    status_t returnCode;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    flexnvmInfoIfrAddr =
        config->ifrDesc.resRange.dflashIfrStart + config->ifrDesc.resRange.ifrMemSize - sizeof(dataIFRReadOut);

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
    /* Get FlexNVM memory partition info from data flash IFR */
    returnCode = FTFx_CMD_ReadResource(config, flexnvmInfoIfrAddr, (uint8_t *)&dataIFRReadOut, sizeof(dataIFRReadOut),
                                       kFTFx_ResourceOptionFlashIfr);
    if (returnCode != kStatus_FTFx_Success)
    {
        return kStatus_FTFx_PartitionStatusUpdateFailure;
    }
#else
#error "Cannot get FlexNVM memory partition info"
#endif /* FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD */

    /* Fill out partitioned EEPROM size */
    dataIFRReadOut.EEPROMDataSetSize &= 0x0FU;
    config->eepromTotalSize = kEepromDensities[dataIFRReadOut.EEPROMDataSetSize];

    /* Fill out partitioned DFlash size */
    dataIFRReadOut.FlexNVMPartitionCode &= 0x0FU;
    config->flashDesc.totalSize = kDflashDensities[dataIFRReadOut.FlexNVMPartitionCode];

    return kStatus_FTFx_Success;
}
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 */
status_t FTFx_CMD_Erase(ftfx_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    uint32_t sectorSize;
    uint32_t endAddress;      /* storing end address */
    uint32_t numberOfSectors; /* number of sectors calculated by endAddress */
    status_t returnCode;
    uint32_t eraseStart;

    /* Check the supplied address range. */
    returnCode = ftfx_check_mem_range(config, start, lengthInBytes, config->opsConfig.addrAligment.sectorCmd);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* Validate the user key */
    returnCode = ftfx_check_user_key(key);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    eraseStart = config->opsConfig.convertedAddress;
    sectorSize = config->flashDesc.sectorSize;

    /* Calculate Flash end address */
    endAddress = eraseStart + lengthInBytes - 1U;

    /* re-calculate the endAddress and align it to the start of the next sector
     * which will be used in the comparison below */
    if (0U != (endAddress % sectorSize))
    {
        numberOfSectors = endAddress / sectorSize + 1U;
        endAddress      = numberOfSectors * sectorSize - 1U;
    }

    /* the start address will increment to the next sector address
     * until it reaches the endAdddress */
    while (eraseStart <= endAddress)
    {
        /* preparing passing parameter to erase a flash block */
        kFCCOBx[0] = BYTE2WORD_1_3(FTFx_ERASE_SECTOR, eraseStart);

        /* calling flash command sequence function to execute the command */
        returnCode = ftfx_command_sequence(config);

        /* checking the success of command execution */
        if (kStatus_FTFx_Success != returnCode)
        {
            break;
        }
        else
        {
            /* Increment to the next sector */
            eraseStart += sectorSize;
        }
    }

    return returnCode;
}

/*!
 * @brief erases one flash sector size based on the start address.
 */
status_t FTFx_CMD_EraseSectorNonBlocking(ftfx_config_t *config, uint32_t start, uint32_t key)
{
    uint32_t eraseStart;
    uint8_t aligmentInBytes;
    status_t returnCode    = kStatus_FTFx_AddressError;
    aligmentInBytes        = config->opsConfig.addrAligment.sectorCmd;
    uint32_t lengthInBytes = config->flashDesc.sectorSize;

    returnCode = ftfx_check_mem_range(config, start, lengthInBytes, aligmentInBytes);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }
    /* Validate the user key */
    returnCode = ftfx_check_user_key(key);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    eraseStart = config->opsConfig.convertedAddress;

    /* preparing passing parameter to erase a flash block */
    kFCCOBx[0] = BYTE2WORD_1_3(FTFx_ERASE_SECTOR, eraseStart);
    /* calling flash command sequence function to execute the command */
    ftfx_command_sequence_non_blocking(config);

    return returnCode;
}

/*!
 * @brief Erases entire flash
 */
status_t FTFx_CMD_EraseAll(ftfx_config_t *config, uint32_t key)
{
    status_t returnCode;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* preparing passing parameter to erase all flash blocks */
    kFCCOBx[0] = BYTE2WORD_1_3(FTFx_ERASE_ALL_BLOCK, 0xFFFFFFU);

    /* Validate the user key */
    returnCode = ftfx_check_user_key(key);
    if (kStatus_FTFx_Success != returnCode)
    {
        return returnCode;
    }

    /* calling flash command sequence function to execute the command */
    returnCode = ftfx_command_sequence(config);

#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
    /* Data flash IFR will be erased by erase all command, so we need to
     *  update FlexNVM memory partition status synchronously */
    if (returnCode == kStatus_FTFx_Success)
    {
        if (config->ifrDesc.resRange.dflashIfrStart != config->ifrDesc.resRange.pflashIfrStart)
        {
            returnCode = FTFx_API_UpdateFlexnvmPartitionStatus(config);
        }
    }
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */

    return returnCode;
}

#if defined(FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD) && FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD
/*!
 * @brief Erases the entire flash, including protected sectors.
 */
status_t FTFx_CMD_EraseAllUnsecure(ftfx_config_t *config, uint32_t key)
{
    status_t returnCode;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Prepare passing parameter to erase all flash blocks (unsecure). */
    kFCCOBx[0] = BYTE2WORD_1_3(FTFx_ERASE_ALL_BLOCK_UNSECURE, 0xFFFFFFU);

    /* Validate the user key */
    returnCode = ftfx_check_user_key(key);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* calling flash command sequence function to execute the command */
    returnCode = ftfx_command_sequence(config);

#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
    /* Data flash IFR will be erased by erase all unsecure command, so we need to
     *  update FlexNVM memory partition status synchronously */
    if (returnCode == kStatus_FTFx_Success)
    {
        if (config->ifrDesc.resRange.dflashIfrStart != config->ifrDesc.resRange.pflashIfrStart)
        {
            returnCode = FTFx_API_UpdateFlexnvmPartitionStatus(config);
        }
    }
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */

    return returnCode;
}
#endif /* FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD */

/*!
 * @brief Erases all program flash execute-only segments defined by the FXACC registers.
 */
status_t FTFx_CMD_EraseAllExecuteOnlySegments(ftfx_config_t *config, uint32_t key)
{
    status_t returnCode;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* preparing passing parameter to erase all execute-only segments
     * 1st element for the FCCOB register */
    kFCCOBx[0] = BYTE2WORD_1_3(FTFx_ERASE_ALL_EXECUTE_ONLY_SEGMENT, 0xFFFFFFU);

    /* Validate the user key */
    returnCode = ftfx_check_user_key(key);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    /* calling flash command sequence function to execute the command */
    returnCode = ftfx_command_sequence(config);

    return returnCode;
}

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 */
status_t FTFx_CMD_Program(ftfx_config_t *config, uint32_t start, const uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    uint8_t blockWriteUnitSize = config->opsConfig.addrAligment.blockWriteUnitSize;
    uint32_t programStart;
    uint32_t remainingLength;
    if (src == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Check the supplied address range. */
    returnCode = ftfx_check_mem_range(config, start, lengthInBytes, blockWriteUnitSize);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    programStart    = config->opsConfig.convertedAddress;
    remainingLength = lengthInBytes;

    while (remainingLength > 0U)
    {
        /* preparing passing parameter to program the flash block */
        kFCCOBx[1] = ftfx_read_word_from_byte_address((const uint8_t *)src);
        src        = &src[4];

        if (4U == blockWriteUnitSize)
        {
            kFCCOBx[0] = BYTE2WORD_1_3(FTFx_PROGRAM_LONGWORD, programStart);
        }
        else if (8U == blockWriteUnitSize)
        {
            kFCCOBx[2] = ftfx_read_word_from_byte_address((const uint8_t *)src);
            src        = &src[4];
            kFCCOBx[0] = BYTE2WORD_1_3(FTFx_PROGRAM_PHRASE, programStart);
        }
        else
        {
            return kStatus_FTFx_InvalidArgument;
        }

        /* calling flash command sequence function to execute the command */
        returnCode = ftfx_command_sequence(config);

        /* checking for the success of command execution */
        if (kStatus_FTFx_Success != returnCode)
        {
            break;
        }
        else
        {
            /* update programStart address for next iteration */
            programStart += blockWriteUnitSize;

            /* update remainingLength for next iteration */
            remainingLength -= blockWriteUnitSize;
        }
    }

    return returnCode;
}

/*!
 * @brief Programs Program Once Field through parameters.
 */
status_t FTFx_CMD_ProgramOnce(ftfx_config_t *config, uint32_t index, const uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;

    if ((config == NULL) || (src == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* pass parameters to FTFx */
    kFCCOBx[0] = BYTE2WORD_1_1_2(FTFx_PROGRAM_ONCE, index, 0xFFFFU);

    kFCCOBx[1] = ftfx_read_word_from_byte_address((const uint8_t *)src);

    /* Note: Have to separate the first index from the rest if it equals 0
     * to avoid a pointless comparison of unsigned int to 0 compiler warning */
    if (config->ifrDesc.feature.has8ByteIdxSupport != 0U)
    {
        if (config->ifrDesc.feature.has4ByteIdxSupport != 0U)
        {
            if (((index == config->ifrDesc.idxInfo.mix8byteIdxStart) ||
                 ((index >= ((uint32_t)config->ifrDesc.idxInfo.mix8byteIdxStart + 1U)) &&
                  (index <= config->ifrDesc.idxInfo.mix8byteIdxEnd))) &&
                (lengthInBytes == 8U))
            {
                kFCCOBx[2] = ftfx_read_word_from_byte_address(&src[4]);
            }
        }
        else
        {
            kFCCOBx[2] = ftfx_read_word_from_byte_address(&src[4]);
        }
    }

    /* calling flash command sequence function to execute the command */
    returnCode = ftfx_command_sequence(config);

    return returnCode;
}

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
/*!
 * @brief Programs flash with data at locations passed in through parameters via the Program Section command.
 */
status_t FTFx_CMD_ProgramSection(ftfx_config_t *config, uint32_t start, const uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    uint32_t sectorSize;
    uint32_t programaddress;
    uint8_t aligmentInBytes   = config->opsConfig.addrAligment.sectionCmd;
    const uint8_t *srcaddress = src;
#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
    bool needSwitchFlexRamMode = false;
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

    if (srcaddress == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Check the supplied address range. */
    returnCode = ftfx_check_mem_range(config, start, lengthInBytes, aligmentInBytes);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    programaddress = config->opsConfig.convertedAddress;
    sectorSize     = config->flashDesc.sectorSize;

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
    /* Switch function of FlexRAM if needed */
    if ((FTFx->FCNFG & FTFx_FCNFG_RAMRDY_MASK) == 0U)
    {
        needSwitchFlexRamMode = true;

        returnCode = FTFx_CMD_SetFlexramFunction(config, kFTFx_FlexramFuncOptAvailableAsRam);
        if (returnCode != kStatus_FTFx_Success)
        {
            return returnCode;
        }
    }
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

    while (lengthInBytes > 0U)
    {
        /* Make sure the write operation doesn't span two sectors */
        uint32_t endAddressOfCurrentSector = ALIGN_UP(programaddress, sectorSize);
        uint32_t lengthTobeProgrammedOfCurrentSector;
        uint32_t currentOffset = 0U;

        if (endAddressOfCurrentSector == programaddress)
        {
            endAddressOfCurrentSector += sectorSize;
        }

        if ((lengthInBytes + programaddress) > endAddressOfCurrentSector)
        {
            lengthTobeProgrammedOfCurrentSector = endAddressOfCurrentSector - programaddress;
        }
        else
        {
            lengthTobeProgrammedOfCurrentSector = lengthInBytes;
        }

        /* Program Current Sector */
        while (lengthTobeProgrammedOfCurrentSector > 0U)
        {
            /* Make sure the program size doesn't exceeds Acceleration RAM size */
            uint32_t programSizeOfCurrentPass;
            uint32_t numberOfPhases;

            if (lengthTobeProgrammedOfCurrentSector > (uint32_t)kFLASH_AccelerationRamSize)
            {
                programSizeOfCurrentPass = (uint32_t)kFLASH_AccelerationRamSize;
            }
            else
            {
                programSizeOfCurrentPass = lengthTobeProgrammedOfCurrentSector;
            }

            /* Copy data to FlexRAM */
            (void)memcpy((uint8_t *)config->flexramBlockBase, &srcaddress[currentOffset], programSizeOfCurrentPass);
            /* Set programaddress address of the data to be programmed */
            kFCCOBx[0] = BYTE2WORD_1_3(FTFx_PROGRAM_SECTION, programaddress + currentOffset);
            /* Set program size in terms of FEATURE_FLASH_SECTION_CMD_ADDRESS_ALIGMENT */
            numberOfPhases = programSizeOfCurrentPass / aligmentInBytes;

            kFCCOBx[1] = BYTE2WORD_2_2(numberOfPhases, 0xFFFFU);

            /* Peform command sequence */
            returnCode = ftfx_command_sequence(config);

            if (returnCode != kStatus_FTFx_Success)
            {
                return returnCode;
            }

            lengthTobeProgrammedOfCurrentSector -= programSizeOfCurrentPass;
            currentOffset += programSizeOfCurrentPass;
        }

        srcaddress = &srcaddress[currentOffset];
        programaddress += currentOffset;
        lengthInBytes -= currentOffset;
    }

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
    /* Restore function of FlexRAM if needed. */
    if (needSwitchFlexRamMode)
    {
        returnCode = FTFx_CMD_SetFlexramFunction(config, kFTFx_FlexramFuncOptAvailableForEeprom);
        if (returnCode != kStatus_FTFx_Success)
        {
            return returnCode;
        }
    }
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

    return returnCode;
}
#endif /* FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD */

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_PARTITION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_PARTITION_CMD
/*!
 * @brief Prepares the FlexNVM block for use as data flash, EEPROM backup, or a combination of both and initializes the
 * FlexRAM.
 */
status_t FTFx_CMD_ProgramPartition(ftfx_config_t *config,
                                   ftfx_partition_flexram_load_opt_t option,
                                   uint32_t eepromDataSizeCode,
                                   uint32_t flexnvmPartitionCode)
{
    status_t returnCode;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* eepromDataSizeCode[7:6], flexnvmPartitionCode[7:4] should be all 1'b0
     *  or it will cause access error. */
    /* eepromDataSizeCode bit with 0x3FU;  */
    /* flexnvmPartitionCode bit with 0x0FU; */

    /* preparing passing parameter to program the flash block */
    kFCCOBx[0] = BYTE2WORD_1_2_1(FTFx_PROGRAM_PARTITION, 0xFFFFU, option);
    kFCCOBx[1] = BYTE2WORD_1_1_2(eepromDataSizeCode, flexnvmPartitionCode, 0xFFFFU);

    /* calling flash command sequence function to execute the command */
    returnCode = ftfx_command_sequence(config);

#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
    /* Data flash IFR will be updated by program partition command during reset sequence,
     * so we just set reserved values for partitioned FlexNVM size here */
    config->eepromTotalSize     = 0xFFFFU;
    config->flashDesc.totalSize = 0xFFFFFFFFU;
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */

    return (returnCode);
}
#endif /* FSL_FEATURE_FLASH_HAS_PROGRAM_PARTITION_CMD */

/*!
 * @brief Reads the Program Once Field through parameters.
 */
status_t FTFx_CMD_ReadOnce(ftfx_config_t *config, uint32_t index, uint8_t *dst, uint32_t lengthInBytes)
{
    status_t returnCode;

    if ((config == NULL) || (dst == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* pass parameters to FTFx */
    kFCCOBx[0] = BYTE2WORD_1_1_2(FTFx_READ_ONCE, index, 0xFFFFU);

    /* calling flash command sequence function to execute the command */
    returnCode = ftfx_command_sequence(config);

    if (returnCode == kStatus_FTFx_Success)
    {
        ftfx_write_word_to_byte_address(dst, kFCCOBx[1]);
        /* Note: Have to separate the first index from the rest if it equals 0
         *       to avoid a pointless comparison of unsigned int to 0 compiler warning */
        if (config->ifrDesc.feature.has8ByteIdxSupport != 0U)
        {
            if (config->ifrDesc.feature.has4ByteIdxSupport != 0U)
            {
                if (((index == config->ifrDesc.idxInfo.mix8byteIdxStart) ||
                     ((index >= ((uint32_t)config->ifrDesc.idxInfo.mix8byteIdxStart + 1U)) &&
                      (index <= config->ifrDesc.idxInfo.mix8byteIdxEnd))) &&
                    (lengthInBytes == 8U))
                {
                    ftfx_write_word_to_byte_address(&dst[4], kFCCOBx[2]);
                }
            }
            else
            {
                ftfx_write_word_to_byte_address(&dst[4], kFCCOBx[2]);
            }
        }
    }

    return returnCode;
}

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
/*!
 * @brief Reads the resource with data at locations passed in through parameters.
 *
 * this function can read  date from  program flash IFR, data flash IFR space,
 * and the Version ID field.
 */
status_t FTFx_CMD_ReadResource(
    ftfx_config_t *config, uint32_t start, uint8_t *dst, uint32_t lengthInBytes, ftfx_read_resource_opt_t option)
{
    status_t returnCode;
    uint32_t readstart;
    uint8_t *destaddress;
    uint32_t readlengthBytes;
    readstart       = start;
    destaddress     = dst;
    readlengthBytes = lengthInBytes;
    if ((config == NULL) || (dst == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    uint8_t aligmentInBytes = config->opsConfig.addrAligment.resourceCmd;

    /* Check the supplied address range. */
    returnCode = ftfx_check_resource_range(config, readstart, readlengthBytes, aligmentInBytes, option);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    while (readlengthBytes > 0U)
    {
        /* preparing passing parameter */
        kFCCOBx[0] = BYTE2WORD_1_3(FTFx_READ_RESOURCE, readstart);
        if (aligmentInBytes == 4U)
        {
            kFCCOBx[2] = BYTE2WORD_1_3(option, 0xFFFFFFU);
        }
        else if (aligmentInBytes == 8U)
        {
            kFCCOBx[1] = BYTE2WORD_1_3(option, 0xFFFFFFU);
        }
        else
        {
            return kStatus_FTFx_InvalidArgument;
        }

        /* calling flash command sequence function to execute the command */
        returnCode = ftfx_command_sequence(config);

        if (kStatus_FTFx_Success != returnCode)
        {
            break;
        }

        /* fetch data */
        ftfx_write_word_to_byte_address(destaddress, kFCCOBx[1]);
        destaddress = &destaddress[4];
        if (aligmentInBytes == 8U)
        {
            ftfx_write_word_to_byte_address(destaddress, kFCCOBx[2]);
            destaddress = &destaddress[4];
        }
        /* update readstart address for next iteration */
        readstart += aligmentInBytes;
        /* update readlengthBytes for next iteration */
        readlengthBytes -= aligmentInBytes;
    }

    return (returnCode);
}
#endif /* FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD */

/*!
 * @brief Verifies an erasure of the desired flash area at a specified margin level.
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 * to the specified read margin level.
 */
status_t FTFx_CMD_VerifyErase(ftfx_config_t *config, uint32_t start, uint32_t lengthInBytes, ftfx_margin_value_t margin)
{
    /* Check arguments. */
    uint32_t blockSize;
    uint32_t nextBlockStartAddress;
    uint32_t remainingBytes;
    uint8_t aligmentInBytes = config->opsConfig.addrAligment.sectionCmd;
    status_t returnCode;
    uint32_t erasestart;

    /* Validates the range and alignment of the given address range.*/
    returnCode = ftfx_check_mem_range(config, start, lengthInBytes, aligmentInBytes);
    if (kStatus_FTFx_Success != returnCode)
    {
        return returnCode;
    }

    erasestart = config->opsConfig.convertedAddress;
    blockSize  = config->flashDesc.totalSize / config->flashDesc.blockCount;

    /* Calculate the next block start address */
    nextBlockStartAddress = ALIGN_UP(erasestart, blockSize);

    if (nextBlockStartAddress == erasestart)
    {
        nextBlockStartAddress += blockSize;
    }

    remainingBytes = lengthInBytes;

    while (0U != remainingBytes)
    {
        uint32_t numberOfPhrases;

        uint32_t verifyLength = nextBlockStartAddress - erasestart;
        /* Calculate the size to be verified, this flash does not support erase and program across block. */
        if (verifyLength > remainingBytes)
        {
            verifyLength = remainingBytes;
        }

        /* Calculate the number of phrases to be verified */
        numberOfPhrases = verifyLength / aligmentInBytes;

        /* Fill in verify section command parameters. */
        kFCCOBx[0] = BYTE2WORD_1_3(FTFx_VERIFY_SECTION, erasestart);
        kFCCOBx[1] = BYTE2WORD_2_1_1(numberOfPhrases, margin, 0xFFU);

        /* calling flash command sequence function to execute the command */
        returnCode = ftfx_command_sequence(config);
        if (kStatus_FTFx_Success != returnCode)
        {
            return returnCode;
        }

        remainingBytes -= verifyLength;
        erasestart += verifyLength;
        nextBlockStartAddress += blockSize;
    }

    return kStatus_FTFx_Success;
}

/*!
 * @brief Verifies erasure of the entire flash at a specified margin level.
 */
status_t FTFx_CMD_VerifyEraseAll(ftfx_config_t *config, ftfx_margin_value_t margin)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* preparing passing parameter to verify all block command */
    kFCCOBx[0] = BYTE2WORD_1_1_2(FTFx_VERIFY_ALL_BLOCK, margin, 0xFFFFU);

    /* calling flash command sequence function to execute the command */
    return ftfx_command_sequence(config);
}

/*!
 * @brief Verifies whether the program flash execute-only segments have been erased to
 *  the specified read margin level.
 */
status_t FTFx_CMD_VerifyEraseAllExecuteOnlySegments(ftfx_config_t *config, ftfx_margin_value_t margin)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* preparing passing parameter to verify erase all execute-only segments command */
    kFCCOBx[0] = BYTE2WORD_1_1_2(FTFx_VERIFY_ALL_EXECUTE_ONLY_SEGMENT, margin, 0xFFFFU);

    /* calling flash command sequence function to execute the command */
    return ftfx_command_sequence(config);
}

/*!
 * @brief Verifies programming of the desired flash area at a specified margin level.
 *
 * This function verifies the data programed in the flash memory using the
 * Flash Program Check Command and compares it to the expected data for a given
 * flash area as determined by the start address and length.
 */
status_t FTFx_CMD_VerifyProgram(ftfx_config_t *config,
                                uint32_t start,
                                uint32_t lengthInBytes,
                                const uint8_t *expectedData,
                                ftfx_margin_value_t margin,
                                uint32_t *failedAddress,
                                uint32_t *failedData)
{
    status_t returnCode;
    uint8_t aligmentInBytes = config->opsConfig.addrAligment.checkCmd;
    uint32_t programstart;
    uint32_t programlength;
    programlength = lengthInBytes;
    if (expectedData == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Validates the range and alignment of the given address range */
    returnCode = ftfx_check_mem_range(config, start, lengthInBytes, aligmentInBytes);
    if (kStatus_FTFx_Success != returnCode)
    {
        return returnCode;
    }

    programstart = config->opsConfig.convertedAddress;

    while (0U != programlength)
    {
        /* preparing passing parameter to program check the flash block */
        kFCCOBx[0] = BYTE2WORD_1_3(FTFx_PROGRAM_CHECK, programstart);
        kFCCOBx[1] = BYTE2WORD_1_3(margin, 0xFFFFFFU);
        kFCCOBx[2] = ftfx_read_word_from_byte_address((const uint8_t *)expectedData);

        /* calling flash command sequence function to execute the command */
        returnCode = ftfx_command_sequence(config);

        /* checking for the success of command execution */
        if (kStatus_FTFx_Success != returnCode)
        {
            if (failedAddress != NULL)
            {
                *failedAddress = programstart;
            }
            if (failedData != NULL)
            {
                *failedData = 0U;
            }
            break;
        }

        programlength -= aligmentInBytes;
        expectedData = &expectedData[aligmentInBytes];
        programstart += aligmentInBytes;
    }

    return (returnCode);
}

/*!
 * @brief Allows users to bypass security with a backdoor key.
 */
status_t FTFx_CMD_SecurityBypass(ftfx_config_t *config, const uint8_t *backdoorKey)
{
    uint8_t registerValue; /* registerValue */
    status_t returnCode;   /* return code variable */

    if ((config == NULL) || (backdoorKey == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* set the default return code as kStatus_Success */
    returnCode = kStatus_FTFx_Success;

    /* Get flash security register value */
    registerValue = FTFx->FSEC;

    /* Check to see if flash is in secure state (any state other than 0x2)
     * If not, then skip this since flash is not secure */
    if (0x02U != (registerValue & 0x03U))
    {
        /* preparing passing parameter to erase a flash block */
        kFCCOBx[0] = BYTE2WORD_1_3(FTFx_SECURITY_BY_PASS, 0xFFFFFFU);
        kFCCOBx[1] = BYTE2WORD_1_1_1_1(backdoorKey[0], backdoorKey[1], backdoorKey[2], backdoorKey[3]);
        kFCCOBx[2] = BYTE2WORD_1_1_1_1(backdoorKey[4], backdoorKey[5], backdoorKey[6], backdoorKey[7]);

        /* calling flash command sequence function to execute the command */
        returnCode = ftfx_command_sequence(config);
    }

    return (returnCode);
}

/*!
 * @brief Returns the security state via the pointer passed into the function.
 */
status_t FTFx_REG_GetSecurityState(ftfx_config_t *config, ftfx_security_state_t *state)
{
    /* store data read from flash register */
    uint8_t registerValue;
    if ((config == NULL) || (state == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Get flash security register value */
    registerValue = FTFx->FSEC;

    /* check the status of the flash security bits in the security register */
    if ((uint8_t)kFTFx_FsecRegCode_SEC_Unsecured == (registerValue & FTFx_FSEC_SEC_MASK))
    {
        /* Flash in unsecured state */
        *state = kFTFx_SecurityStateNotSecure;
    }
    else
    {
        /* Flash in secured state
         * check for backdoor key security enable bit */
        if ((uint8_t)kFTFx_FsecRegCode_KEYEN_Enabled == (registerValue & FTFx_FSEC_KEYEN_MASK))
        {
            /* Backdoor key security enabled */
            *state = kFTFx_SecurityStateBackdoorEnabled;
        }
        else
        {
            /* Backdoor key security disabled */
            *state = kFTFx_SecurityStateBackdoorDisabled;
        }
    }

    return kStatus_FTFx_Success;
}

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
/*!
 * @brief Sets the FlexRAM function command.
 */
status_t FTFx_CMD_SetFlexramFunction(ftfx_config_t *config, ftfx_flexram_func_opt_t option)
{
    status_t status;
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    status = ftfx_check_flexram_function_option(option);
    if (kStatus_FTFx_Success != status)
    {
        return status;
    }

    /* preparing passing parameter to verify all block command */
    kFCCOBx[0] = BYTE2WORD_1_1_2(FTFx_SET_FLEXRAM_FUNCTION, option, 0xFFFFU);

    /* calling flash command sequence function to execute the command */
    return ftfx_command_sequence(config);
}
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

#if defined(FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD) && FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
/*!
 * @brief Configures the Swap function or checks the swap state of the Flash module.
 */
status_t FTFx_CMD_SwapControl(ftfx_config_t *config,
                              uint32_t address,
                              ftfx_swap_control_opt_t option,
                              ftfx_swap_state_config_t *returnInfo)
{
    status_t returnCode;

    if ((config == NULL) || (returnInfo == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    if ((address & ((uint32_t)FSL_FEATURE_FLASH_PFLASH_SWAP_CONTROL_CMD_ADDRESS_ALIGMENT - 1u)) != 0U)
    {
        return kStatus_FTFx_AlignmentError;
    }

    /* Make sure address provided is in the lower half of Program flash but not in the Flash Configuration Field */
    if ((address >= (config->flashDesc.totalSize / 2u)) ||
        ((address >= (uint32_t)kFTFx_PflashConfigAreaStart) && (address <= (uint32_t)kFTFx_PflashConfigAreaEnd)))
    {
        return kStatus_FTFx_SwapIndicatorAddressError;
    }

    /* Checking the option. */
    returnCode = ftfx_check_swap_control_option(option);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    kFCCOBx[0] = BYTE2WORD_1_3(FTFx_SWAP_CONTROL, address);
    kFCCOBx[1] = BYTE2WORD_1_3(option, 0xFFFFFFU);

    returnCode = ftfx_command_sequence(config);

    returnInfo->flashSwapState         = (ftfx_swap_state_t)FTFx_FCCOB5_REG;
    returnInfo->currentSwapBlockStatus = (ftfx_swap_block_status_t)FTFx_FCCOB6_REG;
    returnInfo->nextSwapBlockStatus    = (ftfx_swap_block_status_t)FTFx_FCCOB7_REG;

    return returnCode;
}
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */

static void ftfx_init_ifr(ftfx_config_t *config)
{
#if FSL_FEATURE_FLASH_IS_FTFA
    /* FTFA parts(eg. K80, KL80, L5K) support both 4-bytes and 8-bytes unit size */
    config->ifrDesc.feature.has4ByteIdxSupport = 1U;
    config->ifrDesc.feature.has8ByteIdxSupport = 1U;
    config->ifrDesc.idxInfo.mix8byteIdxStart   = 0x10U;
    config->ifrDesc.idxInfo.mix8byteIdxEnd     = 0x13U;
#elif FSL_FEATURE_FLASH_IS_FTFE
    /* FTFE parts(eg. K65, KE18) only support 8-bytes unit size */
    config->ifrDesc.feature.has4ByteIdxSupport = 0U;
    config->ifrDesc.feature.has8ByteIdxSupport = 1U;
#elif FSL_FEATURE_FLASH_IS_FTFL
    /* FTFL parts(eg. K20) only support 4-bytes unit size */
    config->ifrDesc.feature.has4ByteIdxSupport = 1U;
    config->ifrDesc.feature.has8ByteIdxSupport = 0U;
#endif

    config->ifrDesc.resRange.pflashIfrStart = 0x0000U;
    config->ifrDesc.resRange.versionIdSize  = 0x08U;
#if FSL_FEATURE_FLASH_IS_FTFE
    config->ifrDesc.resRange.versionIdStart = 0x08U;
    config->ifrDesc.resRange.ifrMemSize     = 0x0400U;
#else /* FSL_FEATURE_FLASH_IS_FTFL == 1 or FSL_FEATURE_FLASH_IS_FTFA = =1 */
    config->ifrDesc.resRange.versionIdStart    = 0x00U;
    config->ifrDesc.resRange.ifrMemSize        = 0x0100U;
#endif

#if FSL_FEATURE_FLASH_HAS_FLEX_NVM
    config->ifrDesc.resRange.dflashIfrStart = 0x800000U;
#endif

#if FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
#if FSL_FEATURE_FLASH_IS_FTFE
    config->ifrDesc.resRange.pflashSwapIfrStart = 0x40000U;
#else /* FSL_FEATURE_FLASH_IS_FTFL == 1 or FSL_FEATURE_FLASH_IS_FTFA == 1 */
    config->ifrDesc.resRange.pflashSwapIfrStart = config->flashDesc.totalSize / 4;
#endif
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */
}

#if FTFx_DRIVER_IS_FLASH_RESIDENT
/*!
 * @brief Copy PIC of flash_run_command() to RAM
 */
static void ftfx_copy_run_command_to_ram(uint32_t *ftfxRunCommand)
{
    assert(sizeof(s_ftfxRunCommandFunctionCode) <= ((uint32_t)kFTFx_RamFuncMaxSizeInWords * 4U));

    /* Since the value of ARM function pointer is always odd, but the real start address
     * of function memory should be even, that's why +1 operation exist. */
    (void)memcpy(ftfxRunCommand, s_ftfxRunCommandFunctionCode, sizeof(s_ftfxRunCommandFunctionCode));
}
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

/*!
 * @brief FTFx Command Sequence
 *
 * This function is used to perform the command write sequence to the flash.
 *
 * @param driver Pointer to storage for the driver runtime state.
 * @return An error code or kStatus_FTFx_Success
 */
static status_t ftfx_command_sequence(ftfx_config_t *config)
{
    uint8_t registerValue;

#if FTFx_DRIVER_IS_FLASH_RESIDENT
    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FTFx->FSTAT = FTFx_FSTAT_RDCOLERR_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_FPVIOL_MASK;

    /* Since the value of ARM function pointer is always odd, but the real start address
     * of function memory should be even, that's why +1 operation exist. */
    config->runCmdFuncAddr.commadAddr += 1UL;
    callFtfxRunCommand_t callFtfxRunCommand = config->runCmdFuncAddr.callFlashCommand;

    /* We pass the ftfx_fstat address as a parameter to flash_run_comamnd() instead of using
     * pre-processed MICRO sentences or operating global variable in flash_run_comamnd()
     * to make sure that flash_run_command() will be compiled into position-independent code (PIC). */
    callFtfxRunCommand((FTFx_REG8_ACCESS_TYPE)(&FTFx->FSTAT));
    config->runCmdFuncAddr.commadAddr -= 1UL;
#else
    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FTFx->FSTAT = FTFx_FSTAT_RDCOLERR_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_FPVIOL_MASK;

    /* clear CCIF bit */
    FTFx->FSTAT = FTFx_FSTAT_CCIF_MASK;

    /* Check CCIF bit of the flash status register, wait till it is set.
     * IP team indicates that this loop will always complete. */
    while (!(FTFx->FSTAT & FTFx_FSTAT_CCIF_MASK))
    {
    }
#endif /* FTFx_DRIVER_IS_FLASH_RESIDENT */

    /* Check error bits */
    /* Get flash status register value */
    registerValue = FTFx->FSTAT;

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

static void ftfx_command_sequence_non_blocking(ftfx_config_t *config)
{
#if FTFx_DRIVER_IS_FLASH_RESIDENT
    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FTFx->FSTAT = FTFx_FSTAT_RDCOLERR_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_FPVIOL_MASK;

    /* Since the value of ARM function pointer is always odd, but the real start address
     * of function memory should be even, that's why +1 operation exist. */
    config->runCmdFuncAddr.commadAddr += 1UL;
    callFtfxRunCommand_t callFtfxRunCommand = config->runCmdFuncAddr.callFlashCommand;

    /* We pass the ftfx_fstat address as a parameter to flash_run_comamnd() instead of using
     * pre-processed MICRO sentences or operating global variable in flash_run_comamnd()
     * to make sure that flash_run_command() will be compiled into position-independent code (PIC). */
    callFtfxRunCommand((FTFx_REG8_ACCESS_TYPE)(&FTFx->FSTAT));
    config->runCmdFuncAddr.commadAddr -= 1UL;
#else
    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FTFx->FSTAT = FTFx_FSTAT_RDCOLERR_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_FPVIOL_MASK;

    /* clear CCIF bit */
    FTFx->FSTAT = FTFx_FSTAT_CCIF_MASK;
#endif
}

/*! @brief Validates the range and alignment of the given address range.*/
static status_t ftfx_check_mem_range(ftfx_config_t *config,
                                     uint32_t startAddress,
                                     uint32_t lengthInBytes,
                                     uint8_t alignmentBaseline)
{
    status_t status = kStatus_FTFx_AddressError;

    /* Verify the start and length are alignmentBaseline aligned. */
    if ((0U != (startAddress & (uint8_t)(alignmentBaseline - 1U))) ||
        (0U != (lengthInBytes & (uint8_t)(alignmentBaseline - 1U))))
    {
        return kStatus_FTFx_AlignmentError;
    }

    /* check for valid range of the target addresses */
    if ((startAddress >= config->flashDesc.blockBase) &&
        ((startAddress + lengthInBytes) <= (config->flashDesc.blockBase + config->flashDesc.totalSize)))
    {
        status = kStatus_FTFx_Success;
    }
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS) && FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS
    else if ((startAddress >= config->flashDesc.aliasBlockBase) &&
             ((startAddress + lengthInBytes) <= (config->flashDesc.aliasBlockBase + config->flashDesc.totalSize)))
    {
        status = kStatus_FTFx_Success;
    }
    else
    {
        status = kStatus_FTFx_AddressError;
    }
#endif

    return status;
}

/*! @brief Validates the given user key for flash erase APIs.*/
static status_t ftfx_check_user_key(uint32_t key)
{
    /* Validate the user key */
    if (key != (uint32_t)kFTFx_ApiEraseKey)
    {
        return kStatus_FTFx_EraseKeyError;
    }

    return kStatus_FTFx_Success;
}

/*! @brief Reads word from byte address.*/
static uint32_t ftfx_read_word_from_byte_address(const uint8_t *src)
{
    uint32_t word          = 0U;
    const uint8_t *readsrc = src;
    /* If the source address is aligned with 4 bytes */
    if (0U == ((uint32_t)readsrc % 4U))
    {
        word = *(const uint32_t *)(uint32_t)readsrc;
    }
    /* Read 4 bytes from a non-4-byte aligned address, 1 byte one time */
    else
    {
        for (uint32_t i = 0U; i < 4U; i++)
        {
            word |= (uint32_t)(*readsrc) << (i * 8U);
            readsrc++;
        }
    }

    return word;
}

/*! @brief Writes word to byte address.*/
static void ftfx_write_word_to_byte_address(uint8_t *dst, uint32_t word)
{
    uint8_t *writedst = dst;
    /* If the source address is aligned with 4 bytes */
    if (0U == ((uint32_t)writedst % 4U))
    {
        *(uint32_t *)(uint32_t)writedst = word;
    }
    else
    {
        /* Write 4 bytes into a non-4-byte aligned address memory, 1 byte one time */
        for (uint32_t i = 0U; i < 4U; i++)
        {
            *writedst = (uint8_t)((word >> (i * 8U)) & 0xFFU);
            writedst++;
        }
    }
}

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
/*! @brief Validates the range of the given resource address.*/
static status_t ftfx_check_resource_range(ftfx_config_t *config,
                                          uint32_t start,
                                          uint32_t lengthInBytes,
                                          uint32_t alignmentBaseline,
                                          ftfx_read_resource_opt_t option)
{
    status_t status;
    uint32_t maxReadbleAddress;

    if ((0U != (start & (alignmentBaseline - 1u))) || (0U != (lengthInBytes & (alignmentBaseline - 1u))))
    {
        return kStatus_FTFx_AlignmentError;
    }

    status = kStatus_FTFx_Success;

    maxReadbleAddress = start + lengthInBytes - 1u;
    /* read resource code from the version ID field */
    if (option == kFTFx_ResourceOptionVersionId)
    {
        if ((start != config->ifrDesc.resRange.versionIdStart) ||
            (lengthInBytes != config->ifrDesc.resRange.versionIdSize))
        {
            status = kStatus_FTFx_InvalidArgument;
        }
    }
    else if (option == kFTFx_ResourceOptionFlashIfr)
    {
        /* read resource code from the  program flash IFR space */
        if ((start >= config->ifrDesc.resRange.pflashIfrStart) &&
            (maxReadbleAddress < (config->ifrDesc.resRange.pflashIfrStart + config->ifrDesc.resRange.ifrMemSize)))
        {
        }
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
        /* read resource code from the  date flash IFR space */
        else if ((start >= config->ifrDesc.resRange.dflashIfrStart) &&
                 (maxReadbleAddress < (config->ifrDesc.resRange.dflashIfrStart + config->ifrDesc.resRange.ifrMemSize)))
        {
        }
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */
#if defined(FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD) && FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
        /* read resource code from the  Program Flash Swap IFR space */
        else if ((start >= config->ifrDesc.resRange.pflashSwapIfrStart) &&
                 (maxReadbleAddress <
                  (config->ifrDesc.resRange.pflashSwapIfrStart + config->ifrDesc.resRange.ifrMemSize)))
        {
        }
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */
        else
        {
            status = kStatus_FTFx_InvalidArgument;
        }
    }
    else
    {
        status = kStatus_FTFx_InvalidArgument;
    }

    return status;
}
#endif /* FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD */

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
/*! @brief Validates the given flexram function option.*/
static inline status_t ftfx_check_flexram_function_option(ftfx_flexram_func_opt_t option)
{
    if ((option != kFTFx_FlexramFuncOptAvailableAsRam) && (option != kFTFx_FlexramFuncOptAvailableForEeprom))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    return kStatus_FTFx_Success;
}
#endif /* FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD */

#if defined(FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD) && FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD
/*! @brief Validates the given swap control option.*/
static status_t ftfx_check_swap_control_option(ftfx_swap_control_opt_t option)
{
    if ((option == kFTFx_SwapControlOptionIntializeSystem) || (option == kFTFx_SwapControlOptionSetInUpdateState) ||
        (option == kFTFx_SwapControlOptionSetInCompleteState) || (option == kFTFx_SwapControlOptionReportStatus) ||
        (option == kFTFx_SwapControlOptionDisableSystem))
    {
        return kStatus_FTFx_Success;
    }

    return kStatus_FTFx_InvalidArgument;
}
#endif /* FSL_FEATURE_FLASH_HAS_SWAP_CONTROL_CMD */
