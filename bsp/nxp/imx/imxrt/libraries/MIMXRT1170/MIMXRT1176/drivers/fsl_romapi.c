/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_romapi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "driver.romapi"
#endif

typedef status_t (*clearCacheCommand_t)(uint32_t instance);

/*!
 * @brief Structure of version property.
 *
 * @ingroup bl_core
 */
typedef union _standard_version
{
    struct
    {
        uint8_t bugfix; /*!< bugfix version [7:0] */
        uint8_t minor;  /*!< minor version [15:8] */
        uint8_t major;  /*!< major version [23:16] */
        char name;      /*!< name [31:24] */
    };
    uint32_t version; /*!< combined version numbers */

#if defined(__cplusplus)
    StandardVersion() : version(0)
    {
    }
    StandardVersion(uint32_t version) : version(version)
    {
    }
#endif
} standard_version_t;

/*!
 * @brief Interface for the ROM FLEXSPI NOR flash driver.
 */
typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*page_program)(uint32_t instance, flexspi_nor_config_t *config, uint32_t dst_addr, const uint32_t *src);
    status_t (*erase_all)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*erase)(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);
    status_t (*read)(uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes);
    void (*clear_cache)(uint32_t instance);
    status_t (*xfer)(uint32_t instance, flexspi_xfer_t *xfer);
    status_t (*update_lut)(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq);
    status_t (*get_config)(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);
    status_t (*erase_sector)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*erase_block)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    const uint32_t reserved0; /*!< Reserved */
    status_t (*wait_busy)(uint32_t instance, flexspi_nor_config_t *config, bool isParallelMode, uint32_t address);
    const uint32_t reserved1[2]; /*!< Reserved */
} flexspi_nor_driver_interface_t;

/*!
 * @brief Root of the bootloader api tree.
 *
 * An instance of this struct resides in read-only memory in the bootloader. It
 * provides a user application access to APIs exported by the bootloader.
 *
 * @note The order of existing fields must not be changed.
 */
typedef struct
{
    void (*runBootloader)(void *arg);                       /*!< Function to start the bootloader executing.*/
    standard_version_t version;                             /*!< Bootloader version number.*/
    const char *copyright;                                  /*!< Copyright string.*/
    const flexspi_nor_driver_interface_t *flexSpiNorDriver; /*!< FlexSPI NOR FLASH Driver API.*/
    const uint32_t reserved[8];                             /*!< Reserved */
} bootloader_api_entry_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_BOOT_ROM_HAS_ROMAPI) && FSL_FEATURE_BOOT_ROM_HAS_ROMAPI

static bootloader_api_entry_t *g_bootloaderTree = NULL;

/*******************************************************************************
 * ROM FLEXSPI NOR driver
 ******************************************************************************/
/*!
 * @brief ROM API init.
 */
void ROM_API_Init(void)
{
    if ((ANADIG_MISC->MISC_DIFPROG & ANADIG_MISC_MISC_DIFPROG_CHIPID(0x10U)) != 0U)
    {
        g_bootloaderTree = ((bootloader_api_entry_t *)*(uint32_t *)0x0021001cU);
    }
    else
    {
        g_bootloaderTree = ((bootloader_api_entry_t *)*(uint32_t *)0x0020001cU);
    }
}

#if defined(FSL_ROM_HAS_RUNBOOTLOADER_API) && FSL_ROM_HAS_RUNBOOTLOADER_API
/*!
 * @brief Enter Bootloader.
 *
 * @param arg A pointer to the storage for the bootloader param.
 *        refer to System Boot Chapter in device reference manual for details.
 */
void ROM_RunBootloader(void *arg)
{
    g_bootloaderTree->runBootloader(arg);
}
#endif /* FSL_ROM_HAS_RUNBOOTLOADER_API */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG
/*! @brief Get FLEXSPI NOR Configuration Block based on specified option. */
status_t ROM_FLEXSPI_NorFlash_GetConfig(uint32_t instance,
                                        flexspi_nor_config_t *config,
                                        serial_nor_config_option_t *option)
{
    return g_bootloaderTree->flexSpiNorDriver->get_config(instance, config, option);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG */

/*!
 * @brief Initialize Serial NOR devices via FLEXSPI.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 */
status_t ROM_FLEXSPI_NorFlash_Init(uint32_t instance, flexspi_nor_config_t *config)
{
    return g_bootloaderTree->flexSpiNorDriver->init(instance, config);
}

/*!
 * @brief Program data to Serial NOR via FLEXSPI.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config  A pointer to the storage for the driver runtime state.
 * @param dst_addr A pointer to the desired flash memory to be programmed.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the NOR flash.
 */
status_t ROM_FLEXSPI_NorFlash_ProgramPage(uint32_t instance,
                                          flexspi_nor_config_t *config,
                                          uint32_t dst_addr,
                                          const uint32_t *src)
{
    return g_bootloaderTree->flexSpiNorDriver->page_program(instance, config, dst_addr, src);
}

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ
/*!
 * @brief Read data from Serial NOR
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config  A pointer to the storage for the driver runtime state.
 * @param dst     A pointer to the dest buffer of data that is to be read from the NOR flash.
 * @param lengthInBytes The length, given in bytes to be read.
 */
status_t ROM_FLEXSPI_NorFlash_Read(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t lengthInBytes)
{
    return g_bootloaderTree->flexSpiNorDriver->read(instance, config, dst, start, lengthInBytes);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ */

/*!
 * @brief Erase Flash Region specified by address and length.
 *
 * @param instance storage the index of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired NOR flash memory to be erased.
 * @param length The length, given in bytes to be erased.
 */
status_t ROM_FLEXSPI_NorFlash_Erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length)
{
    return g_bootloaderTree->flexSpiNorDriver->erase(instance, config, start, length);
}

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR
/*!
 * @brief Erase one sector specified by address.
 *
 * @param instance storage the index of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired NOR flash memory to be erased.
 */
status_t ROM_FLEXSPI_NorFlash_EraseSector(uint32_t instance, flexspi_nor_config_t *config, uint32_t start)
{
    return g_bootloaderTree->flexSpiNorDriver->erase_sector(instance, config, start);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK
/*!
 * @brief Erase one block specified by address.
 *
 * @param instance storage the index of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired NOR flash memory to be erased.
 */
status_t ROM_FLEXSPI_NorFlash_EraseBlock(uint32_t instance, flexspi_nor_config_t *config, uint32_t start)
{
    return g_bootloaderTree->flexSpiNorDriver->erase_block(instance, config, start);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL
/*! @brief Erase all the Serial NOR devices connected on FLEXSPI. */
status_t ROM_FLEXSPI_NorFlash_EraseAll(uint32_t instance, flexspi_nor_config_t *config)
{
    return g_bootloaderTree->flexSpiNorDriver->erase_all(instance, config);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER
/*! @brief FLEXSPI command */
status_t ROM_FLEXSPI_NorFlash_CommandXfer(uint32_t instance, flexspi_xfer_t *xfer)
{
    return g_bootloaderTree->flexSpiNorDriver->xfer(instance, xfer);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT
/*! @brief Configure FLEXSPI Lookup table. */
status_t ROM_FLEXSPI_NorFlash_UpdateLut(uint32_t instance,
                                        uint32_t seqIndex,
                                        const uint32_t *lutBase,
                                        uint32_t seqNumber)
{
    return g_bootloaderTree->flexSpiNorDriver->update_lut(instance, seqIndex, lutBase, seqNumber);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT */

/*! @brief Software reset for the FLEXSPI logic. */
void ROM_FLEXSPI_NorFlash_ClearCache(uint32_t instance)
{
    uint32_t clearCacheFunctionAddress;
    if ((ANADIG_MISC->MISC_DIFPROG & ANADIG_MISC_MISC_DIFPROG_CHIPID(0x10U)) != 0U)
    {
        clearCacheFunctionAddress = 0x0021a3b7U;
    }
    else
    {
        clearCacheFunctionAddress = 0x0020426bU;
    }
    clearCacheCommand_t clearCacheCommand;
    MISRA_CAST(clearCacheCommand_t, clearCacheCommand, uint32_t, clearCacheFunctionAddress);
    (void)clearCacheCommand(instance);
}

/*! @brief Wait until device is idle*/
status_t ROM_FLEXSPI_NorFlash_WaitBusy(uint32_t instance,
                                       flexspi_nor_config_t *config,
                                       bool isParallelMode,
                                       uint32_t address)
{
    return g_bootloaderTree->flexSpiNorDriver->wait_busy(instance, config, isParallelMode, address);
}

#endif /* FSL_FEATURE_BOOT_ROM_HAS_ROMAPI */
