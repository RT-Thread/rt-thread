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

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Interface for the ROM FLEXSPI NOR flash driver.
 */
typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*program)(uint32_t instance, flexspi_nor_config_t *config, uint32_t dst_addr, const uint32_t *src);
    uint32_t reserved0;
    status_t (*erase)(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t lengthInBytes);
    uint32_t reserved1;
    void (*clear_cache)(uint32_t instance);
    status_t (*xfer)(uint32_t instance, flexspi_xfer_t *xfer);
    status_t (*update_lut)(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t seqNumber);
    uint32_t reserved2;
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
    void (*runBootloader)(void *arg); /*!< Function to start the bootloader executing */
    const uint32_t version;           /*!< Bootloader version number */
    const uint8_t *copyright;         /*!< Bootloader Copyright */
    const uint32_t reserved0;
    flexspi_nor_driver_interface_t *flexSpiNorDriver; /*!< FLEXSPI NOR flash api */
} bootloader_api_entry_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

#define g_bootloaderTree ((bootloader_api_entry_t *)*(uint32_t *)0x0020001cU)

#define api_flexspi_nor_erase_sector \
    ((status_t(*)(uint32_t instance, flexspi_nor_config_t * config, uint32_t address))0x0021055dU)
#define api_flexspi_nor_erase_block \
    ((status_t(*)(uint32_t instance, flexspi_nor_config_t * config, uint32_t address))0x002104a9U)
/*******************************************************************************
 * Codes
 ******************************************************************************/

/*******************************************************************************
 * ROM FLEXSPI NOR driver
 ******************************************************************************/
#if defined(FSL_FEATURE_BOOT_ROM_HAS_ROMAPI) && FSL_FEATURE_BOOT_ROM_HAS_ROMAPI

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
 * @param dstAddr A pointer to the desired flash memory to be programmed.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the NOR flash.
 */
status_t ROM_FLEXSPI_NorFlash_ProgramPage(uint32_t instance,
                                          flexspi_nor_config_t *config,
                                          uint32_t dstAddr,
                                          const uint32_t *src)
{
    return g_bootloaderTree->flexSpiNorDriver->program(instance, config, dstAddr, src);
}

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
    return api_flexspi_nor_erase_sector(instance, config, start);
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
    return api_flexspi_nor_erase_block(instance, config, start);
}
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK */

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
    g_bootloaderTree->flexSpiNorDriver->clear_cache(instance);
}

#endif /* FSL_FEATURE_BOOT_ROM_HAS_ROMAPI */
