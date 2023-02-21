/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_flash.h"
#include "fsl_flash_ffr.h"
#include "fsl_flexspi_nor_flash.h"
#include "fsl_runbootloader.h"

/*! @brief Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.runBootloader"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x1302FC00U)

/*!
 * @name flash, ffr, flexspi nor flash Structure
 * @{
 */

typedef union functionCommandOption
{
    uint32_t commandAddr;
    status_t (*isFlashAreaReadable)(flash_config_t *config, uint32_t startAddress, uint32_t lengthInBytes);
    status_t (*isFlashAreaModifiable)(flash_config_t *config, uint32_t startAddress, uint32_t lengthInBytes);
} function_command_option_t;

/*!
 * @brief Structure of version property.
 *
 * @ingroup bl_core
 */
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

/*! @brief Interface for the flash driver.*/
typedef struct FlashDriverInterface
{
    standard_version_t version; /*!< flash driver API version number. */
    /* Flash driver */
    status_t (*flash_init)(flash_config_t *config);
    status_t (*flash_erase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program)(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_verify_erase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_verify_program)(flash_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_get_property)(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);

    status_t (*flash_erase_with_checker)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program_with_checker)(flash_config_t *config,
                                           uint32_t start,
                                           uint8_t *src,
                                           uint32_t lengthInBytes);
    status_t (*flash_verify_program_with_checker)(flash_config_t *config,
                                                  uint32_t start,
                                                  uint32_t lengthInBytes,
                                                  const uint8_t *expectedData,
                                                  uint32_t *failedAddress,
                                                  uint32_t *failedData);
    /*!< Flash FFR driver */
    status_t (*ffr_init)(flash_config_t *config);
    status_t (*ffr_lock)(flash_config_t *config);
    status_t (*ffr_cust_factory_page_write)(flash_config_t *config, uint8_t *page_data, bool seal_part);
    status_t (*ffr_get_uuid)(flash_config_t *config, uint8_t *uuid);
    status_t (*ffr_get_customer_data)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
    status_t (*ffr_cust_keystore_write)(flash_config_t *config, ffr_key_store_t *pKeyStore);
    status_t reserved0;
    status_t reserved1;
    status_t (*ffr_infield_page_write)(flash_config_t *config, uint8_t *page_data, uint32_t valid_len);
    status_t (*ffr_get_customer_infield_data)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
    status_t (*flash_read)(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes);
    status_t (*ffr_seclib_init)(flash_config_t *config, uint32_t *context);
    status_t (*flash_get_cust_keystore)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
    status_t (*flash_erase_non_blocking)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_get_command_state)(flash_config_t *config);
} flash_driver_interface_t;

/*! @brief FLEXSPI Flash driver API Interface */
typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*page_program)(uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src);
    status_t (*erase_all)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*erase)(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);
    status_t (*erase_sector)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*erase_block)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*get_config)(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);
    status_t (*read)(uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes);
    status_t (*xfer)(uint32_t instance, flexspi_xfer_t *xfer);
    status_t (*update_lut)(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq);
    status_t (*set_clock_source)(uint32_t clockSrc);
    void (*config_clock)(uint32_t instance, uint32_t freqOption, uint32_t sampleClkMode);
} flexspi_nor_flash_driver_t;

/*! @}*/

/*!
 * @brief Root of the bootloader API tree.
 *
 * An instance of this struct resides in read-only memory in the bootloader. It
 * provides a user application access to APIs exported by the bootloader.
 *
 * @note The order of existing fields must not be changed.
 */
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg);                   /*!< Function to start the bootloader executing.*/
    standard_version_t version;                         /*!< Bootloader version number.*/
    const char *copyright;                              /*!< Copyright string.*/
    const uint32_t reserved0;                           /*!< reserved*/
    const flash_driver_interface_t *flashDriver;        /*!< Internal Flash driver API.*/
    const uint32_t reserved1[5];                        /*!< reserved*/
    const uint32_t nbootDriver;                         /*!< Please refer to "fsl_nboot.h" */
    const flexspi_nor_flash_driver_t *flexspiNorDriver; /*!< FlexSPI NOR FLASH Driver API.*/
    const uint32_t reserved2;                           /*!< reserved*/
    const uint32_t memoryInterface;                     /*!< Please refer to "fsl_mem_interface.h" */
} bootloader_tree_t;

/*******************************************************************************
 * API
 ******************************************************************************/

void bootloader_user_entry(void *arg)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    BOOTLOADER_API_TREE_POINTER->runBootloader(arg);
}
