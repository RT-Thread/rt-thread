/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_MEM_INTERFACE_H_
#define FSL_MEM_INTERFACE_H_

#include "fsl_sbloader.h"
#include "fsl_common.h"

/*!
 * @addtogroup memory_interface
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Bit mask for device ID. */
#define DEVICE_ID_MASK (0xffU)
/*! @brief Bit position of device ID. */
#define DEVICE_ID_SHIFT 0U
/*! @brief Bit mask for group ID. */
#define GROUP_ID_MASK (0xf00U)
/*! @brief Bit position of group ID. */
#define GROUP_ID_SHIFT 8U

/*! @brief Construct a memory ID from a given group ID and device ID. */
#define MAKE_MEMORYID(group, device) \
    ((((group) << GROUP_ID_SHIFT) & GROUP_ID_MASK) | (((device) << DEVICE_ID_SHIFT) & DEVICE_ID_MASK))
/*! @brief Get group ID from a given memory ID. */
#define GROUPID(memoryId) (((memoryId)&GROUP_ID_MASK) >> GROUP_ID_SHIFT)

/*! @brief Get device ID from a given memory ID. */
#define DEVICEID(memoryId) (((memoryId)&DEVICE_ID_MASK) >> DEVICE_ID_SHIFT)

/*! @brief Memory group definition. */
enum
{
    kMemoryGroup_Internal = 0U, /*!<  Memory belongs internal 4G memory region. */
    kMemoryGroup_External = 1U, /*!<  Memory belongs external memory region. */
};

/*! @brief Memory device ID definition. */
enum
{
    /*  Memory ID bitfiled definition.
        | 11 | 10 | 9 |    8    |  7   |  6   |  5   |  4  |  3   |  2   |  1  |  0  |
        |  Reserved   | INT/EXT | Type                     | Sub-Type                |
        |             | 0: INT  | INT:                     |                         |
        |             | 1: EXT  | 0: NorFlash0             | 0: Internal Flash(FTFX) |
        |             |         |                          | 1: QSPI                 |
        |             |         |                          | 4: IFR                  |
        |             |         |                          | 5: LPC FFR              |
        |             |         |                          | 8: SEMC                 |
        |             |         |                          | 9: FlexSPI              |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | 1: ExecuteOnlyRegion     | 0: Internal Flash(FTFX) |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | others: Unused           |                         |
        |             |         |                          |                         |
        |             |         | EXT:                     |                         |
        |             |         | 0: NandFlash             | 0: SEMC                 |
        |             |         |                          | 1: FlexSPI              |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | 1: NorFlash/EEPROM       | 0: LPSPI                |
        |             |         |                          | 1: LPI2C                |
        |             |         |                          | others: Unused          |
        |             |         |                          |                         |
        |             |         | 2: SD/SDHC/SDXC/MMC/eMMC | 0: uSDHC SD             |
        |             |         |                          | 1: uSDHC MMC            |
        |             |         |                          | others: Unused          |
        |             |         | others: Unused           |                         |

        INT : Internal 4G memory, including internal memory modules, and XIP external memory modules.
        EXT : Non-XIP external memory modules.
    */
    kMemoryInternal = MAKE_MEMORYID(kMemoryGroup_Internal, 0U), /*!< Internal memory (include all on chip memory) */
    kMemoryQuadSpi0 = MAKE_MEMORYID(kMemoryGroup_Internal, 1U), /*!< Qsuad SPI memory 0 */
    kMemoryIFR0 =
        MAKE_MEMORYID(kMemoryGroup_Internal, 4U), /*!< Nonvolatile information register 0. Only used by SB loader. */
    kMemoryFFR              = MAKE_MEMORYID(kMemoryGroup_Internal, 5U),    /*!< LPCc040hd flash FFR region. */
    kMemorySemcNor          = MAKE_MEMORYID(kMemoryGroup_Internal, 8U),    /*!< SEMC Nor memory */
    kMemoryFlexSpiNor       = MAKE_MEMORYID(kMemoryGroup_Internal, 9U),    /*!< Flex SPI Nor memory */
    kMemorySpifiNor         = MAKE_MEMORYID(kMemoryGroup_Internal, 0xAU),  /*!< SPIFI Nor memory */
    kMemoryFlashExecuteOnly = MAKE_MEMORYID(kMemoryGroup_Internal, 0x10U), /*!< Execute-only region on internal Flash */

    kMemorySemcNand     = MAKE_MEMORYID(kMemoryGroup_External, 0U),    /*!< SEMC NAND memory */
    kMemorySpiNand      = MAKE_MEMORYID(kMemoryGroup_External, 1U),    /*!< SPI NAND memory */
    kMemorySpiNorEeprom = MAKE_MEMORYID(kMemoryGroup_External, 0x10U), /*!< SPI NOR/EEPROM memory */
    kMemoryI2cNorEeprom = MAKE_MEMORYID(kMemoryGroup_External, 0x11U), /*!< I2C NOR/EEPROM memory */
    kMemorySDCard       = MAKE_MEMORYID(kMemoryGroup_External, 0x20U), /*!< eSD, SD, SDHC, SDXC memory Card */
    kMemoryMMCCard      = MAKE_MEMORYID(kMemoryGroup_External, 0x21U), /*!< MMC, eMMC memory Card */
};

/*! @brief Bootloader status group numbers.
 *
 * @ingroup bl_core
 */
enum
{
    kStatusGroup_Bootloader      = 100, /*!< Bootloader status group number (100). */
    kStatusGroup_MemoryInterface = 102, /*!< Memory interface status group number (102). */
};

/*! @brief Memory interface status codes. */
enum
{
    kStatusMemoryRangeInvalid                    = MAKE_STATUS(kStatusGroup_MemoryInterface, 0),
    kStatusMemoryReadFailed                      = MAKE_STATUS(kStatusGroup_MemoryInterface, 1),
    kStatusMemoryWriteFailed                     = MAKE_STATUS(kStatusGroup_MemoryInterface, 2),
    kStatusMemoryCumulativeWrite                 = MAKE_STATUS(kStatusGroup_MemoryInterface, 3),
    kStatusMemoryAppOverlapWithExecuteOnlyRegion = MAKE_STATUS(kStatusGroup_MemoryInterface, 4),
    kStatusMemoryNotConfigured                   = MAKE_STATUS(kStatusGroup_MemoryInterface, 5),
    kStatusMemoryAlignmentError                  = MAKE_STATUS(kStatusGroup_MemoryInterface, 6),
    kStatusMemoryVerifyFailed                    = MAKE_STATUS(kStatusGroup_MemoryInterface, 7),
    kStatusMemoryWriteProtected                  = MAKE_STATUS(kStatusGroup_MemoryInterface, 8),
    kStatusMemoryAddressError                    = MAKE_STATUS(kStatusGroup_MemoryInterface, 9),
    kStatusMemoryBlankCheckFailed                = MAKE_STATUS(kStatusGroup_MemoryInterface, 10),
    kStatusMemoryBlankPageReadDisallowed         = MAKE_STATUS(kStatusGroup_MemoryInterface, 11),
    kStatusMemoryProtectedPageReadDisallowed     = MAKE_STATUS(kStatusGroup_MemoryInterface, 12),
    kStatusMemoryFfrSpecRegionWriteBroken        = MAKE_STATUS(kStatusGroup_MemoryInterface, 13),
    kStatusMemoryUnsupportedCommand              = MAKE_STATUS(kStatusGroup_MemoryInterface, 14),
};

/*! @brief Bootloader status codes. */
enum
{
    kStatus_UnknownCommand     = MAKE_STATUS(kStatusGroup_Bootloader, 0),
    kStatus_SecurityViolation  = MAKE_STATUS(kStatusGroup_Bootloader, 1),
    kStatus_AbortDataPhase     = MAKE_STATUS(kStatusGroup_Bootloader, 2),
    kStatus_Ping               = MAKE_STATUS(kStatusGroup_Bootloader, 3),
    kStatus_NoResponse         = MAKE_STATUS(kStatusGroup_Bootloader, 4),
    kStatus_NoResponseExpected = MAKE_STATUS(kStatusGroup_Bootloader, 5),
    kStatus_CommandUnsupported = MAKE_STATUS(kStatusGroup_Bootloader, 6),
};

/*!
 * @brief Interface to memory operations.
 *
 * This is the main abstract interface to all memory operations.
 */
typedef struct
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer, uint32_t memoryId);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer, uint32_t memoryId);
    status_t (*fill)(uint32_t address, uint32_t length, uint32_t pattern);
    status_t (*flush)(void);
    status_t (*finalize)(void);
    status_t (*erase)(uint32_t address, uint32_t length, uint32_t memoryId);
} memory_interface_t;

/*! @brief Interface to memory operations for one region of memory. */
typedef struct
{
    status_t (*init)(void);
    status_t (*read)(uint32_t address, uint32_t length, uint8_t *buffer);
    status_t (*write)(uint32_t address, uint32_t length, const uint8_t *buffer);
    status_t (*fill)(uint32_t address, uint32_t length, uint32_t pattern);
    status_t (*flush)(void);
    status_t (*erase)(uint32_t address, uint32_t length);
    status_t (*config)(uint32_t *buffer);
    status_t (*erase_all)(void);
} memory_region_interface_t;

/*! @brief Structure of a memory map entry.*/
typedef struct
{
    uint32_t startAddress;
    uint32_t endAddress;
    uint32_t memoryProperty;
    uint32_t memoryId;
    const memory_region_interface_t *memoryInterface;
} memory_map_entry_t;

/*! @brief Structure of version property. */
typedef union StandardVersion
{
    struct
    {
        uint8_t bugfix; /*!< bugfix version [7:0] */
        uint8_t minor;  /*!< minor version [15:8] */
        uint8_t major;  /*!< major version [23:16] */
        char name;      /*!< name [31:24] */
    };
    uint32_t version; /*!< combined version numbers */
} standard_version_t;

/*! @brief API initialization data structure */
typedef struct kb_api_parameter_struct
{
    uint32_t allocStart;
    uint32_t allocSize;
} kp_api_init_param_t;

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

standard_version_t API_Version(void);

/*! @brief Initialize the IAP API runtime environment */
status_t API_Init(api_core_context_t *coreCtx, const kp_api_init_param_t *param);

/*! @brief Deinitialize the IAP API runtime environment */
status_t API_Deinit(api_core_context_t *coreCtx);

/*!
 * @brief Initialize memory interface.
 *
 * @retval #kStatus_Fail
 * @retval #kStatus_Success
 */
status_t MEM_Init(api_core_context_t *coreCtx);

/*!
 * @brief Configure memory interface
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param memoryId Indicates the index of the memory type. Please refer to "Memory group definition"

 * @retval #kStatus_Success
 * @retval #kStatus_CommandUnsupported
 * @retval #kStatus_InvalidArgument
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatusMemoryRangeInvalid
 * @retval #kStatus_Fail
 * @retval #kStatus_OutOfRange
 * @retval #kStatus_SPI_BaudrateNotSupport
*/
status_t MEM_Config(api_core_context_t *coreCtx, uint32_t *config, uint32_t memoryId);

/*!
 * @brief Write memory.
 *
 * @param address The start address of the desired flash memory to be programmed.
                  For internal flash the address need to be 512bytes-aligned.
 * @param length Number of bytes to be programmed.
 * @param buffer A pointer to the source buffer of data that is to be programmed into the flash.
 * @param memoryId Indicates the index of the memory type. Please refer to "Memory group definition"
 *
 * @retval #kStatus_Success
 * @retval #kStatus_Fail
 * @retval #kStatusMemoryRangeInvalid
 * @retval #kStatus_CommandUnsupported
 * @retval #kStatus_FLASH_AlignmentError
 * @retval #kStatusMemoryCumulativeWrite
 * @retval #kStatus_FLASH_InvalidArgument
 * @retval #kStatus_FLASH_AddressError
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatus_FLASH_CommandFailure
 * @retval #kStatus_FLASH_CommandNotSupported
 * @retval #kStatus_FLASH_EccError
 * @retval #kStatus_FLASH_RegulationLoss
 * @retval #kStatus_FLASH_Success
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed
 * @retval #kStatus_FLASH_CompareError
 * @retval #kStatusMemoryNotConfigured
 * @retval #kStatusMemoryVerifyFailed
 */
status_t MEM_Write(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, const uint8_t *buf, uint32_t memoryId);

/*!
 * @brief Fill memory with a word pattern.
 *
 * @param address The start address of the desired flash memory to be programmed.
 *                For internal flash the address need to be 512bytes-aligned.
 * @param length  Number of bytes to be programmed.
 * @param pattern The data to be written into the specified memory area.
 *
 * @retval #kStatus_CommandUnsupported
 * @retval #kStatus_Success
 * @retval #kStatus_FLASH_AlignmentError
 * @retval #kStatusMemoryCumulativeWrite
 * @retval #kStatus_Fail
 * @retval #kStatus_FLASH_InvalidArgument
 * @retval #kStatus_FLASH_AddressError
 * @retval #kStatus_FLASH_Success
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatus_FLASH_CommandFailure
 * @retval #kStatus_FLASH_CommandNotSupported
 * @retval #kStatus_FLASH_EccError
 * @retval #kStatus_FLASH_RegulationLoss
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed
 */
status_t MEM_Fill(
    api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t pattern, uint32_t memoryId);

/*!
 * @brief Flush memory.
 *
 * @retval #kStatus_Success
 * @retval #kStatus_Fail
 * @retval #kStatusMemoryCumulativeWrite
 * @retval #kStatus_FLASH_InvalidArgument
 * @retval #kStatus_FLASH_AlignmentError
 * @retval #kStatus_FLASH_Success
 * @retval #kStatus_FLASH_AddressError
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatus_FLASH_CommandFailure
 * @retval #kStatus_FLASH_CommandNotSupported
 * @retval #kStatus_FLASH_EccError
 * @retval #kStatus_FLASH_RegulationLoss
 * @retval #kStatus_FLASH_ReadHidingAreaDisallowed
 * @retval #kStatusMemoryVerifyFailed
 */
status_t MEM_Flush(api_core_context_t *coreCtx);

/*!
 * @brief Erase memory.
 *
 * @param address The start address of the desired flash memory to be erased.
 * @param length Number of bytes to be read.
 * @param memoryId Indicates the index of the memory type. Please refer to "Memory group definition"
 *
 * @retval #kStatus_Success
 * @retval #kStatusMemoryRangeInvalid
 * @retval #kStatusMemoryAddressError
 * @retval #kStatus_FLASH_InvalidArgument
 * @retval #kStatus_FLASH_AlignmentError
 * @retval #kStatus_FLASH_Success
 * @retval #kStatus_FLASH_AddressError
 * @retval #kStatus_FLASH_EraseKeyError
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatus_Fail
 * @retval #kStatus_FLASH_CommandFailure
 * @retval #kStatus_FLASH_CommandNotSupported
 * @retval #kStatus_FLASH_EccError
 * @retval #kStatus_FLASH_RegulationLoss
 * @retval #kStatusMemoryNotConfigured
 * @retval #kStatusMemoryVerifyFailed

 */
status_t MEM_Erase(api_core_context_t *coreCtx, uint32_t start, uint32_t lengthInBytes, uint32_t memoryId);

/*!
 * @brief Erase entire memory based on memoryId
 *
 * @param memoryId Indicates the index of the memory type. Please refer to "Memory group definition"
 *
 * @retval #kStatus_Success
 * @retval #kStatus_Fail
 * @retval #kStatus_CommandUnsupported
 * @retval #kStatus_FLASH_InvalidArgument
 * @retval #kStatus_FLASH_AlignmentError
 * @retval #kStatus_FLASH_Success
 * @retval #kStatus_FLASH_AddressError
 * @retval #kStatus_FLASH_EraseKeyError
 * @retval #kStatus_FLASH_CommandFailure
 * @retval #kStatus_FLASH_CommandNotSupported
 * @retval #kStatus_FLASH_EccError
 * @retval #kStatus_FLASH_RegulationLoss
 * @retval #kStatus_FLASH_ModifyProtectedAreaDisallowed
 * @retval #kStatusMemoryVerifyFailed
 * @retval #kStatusMemoryNotConfigured
 * @retval #kStatus_InvalidArgument
 */
status_t MEM_EraseAll(api_core_context_t *coreCtx, uint32_t memoryId);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* FSL_MEM_INTERFACE_H_ */
