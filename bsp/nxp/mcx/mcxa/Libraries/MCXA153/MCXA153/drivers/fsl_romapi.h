/*
 * Copyright 2023, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ROMAPI_H_
#define _FSL_ROMAPI_H_

#include "fsl_common.h"

/*!
 * @addtogroup romapi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.romapi"
#endif

/*! @name Driver version */
/*@{*/

/*! @brief romapi driver version 2.0.0. */
#define FSL_ROMAPI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!
 * @brief Enumeration for various flash properties.
 */
typedef enum _flash_property_tag
{
    kFLASH_PropertyPflashSectorSize    = 0x00U, /*!< Pflash sector size property.*/
    kFLASH_PropertyPflashTotalSize     = 0x01U, /*!< Pflash total size property.*/
    kFLASH_PropertyPflashBlockSize     = 0x02U, /*!< Pflash block size property.*/
    kFLASH_PropertyPflashBlockCount    = 0x03U, /*!< Pflash block count property.*/
    kFLASH_PropertyPflashBlockBaseAddr = 0x04U, /*!< Pflash block base address property.*/
    kFLASH_PropertyPflashPageSize      = 0x30U, /*!< Pflash page size property.*/
    kFLASH_PropertyPflashSystemFreq    = 0x31U, /*!< System Frequency property.*/
    kFLASH_PropertyFfrSectorSize       = 0x40U, /*!< FFR sector size property.*/
    kFLASH_PropertyFfrTotalSize        = 0x41U, /*!< FFR total size property.*/
    kFLASH_PropertyFfrBlockBaseAddr    = 0x42U, /*!< FFR block base address property.*/
    kFLASH_PropertyFfrPageSize         = 0x43U, /*!< FFR page size property.*/
} flash_property_tag_t;

/*! @brief Flash controller paramter config. */
typedef struct _flash_ffr_config
{
    uint32_t ffrBlockBase;
    uint32_t ffrTotalSize;
    uint32_t ffrPageSize;
    uint32_t sectorSize;
    uint32_t cfpaPageVersion;
    uint32_t cfpaPageOffset;
} flash_ffr_config_t;

/*! @brief Flash driver state information.
 *
 * An instance of this structure is allocated by the user of the flash driver and
 * passed into each of the driver APIs.
 */
typedef struct _flash_config
{
    uint32_t PFlashBlockBase;  /*!< A base address of the first PFlash block */
    uint32_t PFlashTotalSize;  /*!< The size of the combined PFlash block. */
    uint32_t PFlashBlockCount; /*!< A number of PFlash blocks. */
    uint32_t PFlashPageSize;   /*!< The size in bytes of a page of PFlash. */
    uint32_t PFlashSectorSize; /*!< The size in bytes of a sector of PFlash. */
    flash_ffr_config_t ffrConfig;
} flash_config_t;

/*! @brief Interface for the flash driver. */
typedef struct _flash_driver_interface
{
    /* Flash driver */
    status_t (*flash_init)(flash_config_t *config);
    status_t (*flash_erase_sector)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program_phrase)(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_program_page)(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_verify_program)(flash_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_verify_erase_phrase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_verify_erase_page)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_verify_erase_sector)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_get_property)(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);
    /* IFR driver */
    status_t (*ifr_verify_erase_phrase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*ifr_verify_erase_page)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*ifr_verify_erase_sector)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_read)(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes);
    /* version */
    uint32_t version;
} flash_driver_interface_t;

/*! @brief Constructs the four character code for the Flash driver API key. */
#if !defined(FOUR_CHAR_CODE)
#define FOUR_CHAR_CODE(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | ((a)))
#endif

/*!
 * @brief Enumeration for Flash driver API keys.
 *
 * @note The resulting value is built with a byte order such that the string
 * being readable in expected order when viewed in a hex editor, if the value
 * is treated as a 32-bit little endian value.
 */
enum _flash_driver_api_keys
{
    kFLASH_ApiEraseKey = FOUR_CHAR_CODE('l', 'f', 'e', 'k') /*!< Key value used to validate all flash erase APIs.*/
};

/*   API prototype fields definition.
| 31 : 24   |    23 : 20        |     19 : 16        |  15 : 12             |  11 : 8     |  7 ： 0   |
|     Tag   |   Boot mode       | bootloader periphal|  Instance            |  Image Index| Reserved  |
|           |                   |                    |  Used For Boot mode 0|             |           |
|           | 0: Passive mode   | 0 - Auto detection |                      |             |           |
|           | 1: ISP mode       | 1 - USB-HID        |                      |             |           |
|           |                   | 2 - UART           |                      |             |           |
|           |                   | 3 - SPI            |                      |             |           |
|           |                   | 4 - I2C            |                      |             |           |
|           |                   | 5 - CAN            |                      |             |           |
*/
typedef struct
{
    union
    {
        struct
        {
            uint32_t reserved : 8;
            uint32_t boot_image_index : 4;
            uint32_t instance : 4;
            uint32_t boot_interface : 4;
            uint32_t mode : 4;
            uint32_t tag : 8;
        } B;
        uint32_t U;
    } option;
} user_app_boot_invoke_option_t;

/*! @brief Root of the bootloader API tree.
 *
 *  An instance of this struct resides in read-only memory in the bootloader. It
 *  provides a user application access to APIs exported by the bootloader.
 *
 */
typedef struct _bootloader_tree
{
    void (*run_bootloader)(void *arg);            /*!< Function to start the bootloader executing. */
    const flash_driver_interface_t *flash_driver; /*!< Internal Flash driver API. */
    void (*jump)(void *arg);
} bootloader_tree_t;

/** ROM API base address */
#define ROM_API_BASE (0x03003fe0u)
/** ROM API base pointer */
#define ROM_API ((bootloader_tree_t *)ROM_API_BASE)
/** FLASH API base pointer */
#define FLASH_API (ROM_API->flash_driver)

/*! @} */

#endif /* _FSL_RESET_H_ */
