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
 * @name Flash status
 * @{
 */
/*! @brief Flash driver status group. */
#if defined(kStatusGroup_FlashDriver)
#define kStatusGroupGeneric     kStatusGroup_Generic
#define kStatusGroupFlashDriver kStatusGroup_FlashDriver
#elif defined(kStatusGroup_FLASHIAP)
#define kStatusGroupGeneric     kStatusGroup_Generic
#define kStatusGroupFlashDriver kStatusGroup_FLASH
#else
#define kStatusGroupGeneric     0
#define kStatusGroupFlashDriver 1
#endif

/*! @brief Constructs a status code value from a group and a code number. */
#if !defined(MAKE_STATUS)
#define MAKE_STATUS(group, code) ((((group) * 100) + (code)))
#endif

/*!
 * @brief Flash driver status codes.
 */
enum
{
    kStatus_FLASH_Success         = MAKE_STATUS(kStatusGroupGeneric, 0),     /*!< API is executed successfully*/
    kStatus_FLASH_InvalidArgument = MAKE_STATUS(kStatusGroupGeneric, 4),     /*!< Invalid argument*/
    kStatus_FLASH_SizeError       = MAKE_STATUS(kStatusGroupFlashDriver, 0), /*!< Error size*/
    kStatus_FLASH_AlignmentError =
        MAKE_STATUS(kStatusGroupFlashDriver, 1), /*!< Parameter is not aligned with the specified baseline*/
    kStatus_FLASH_AddressError = MAKE_STATUS(kStatusGroupFlashDriver, 2), /*!< Address is out of range */
    kStatus_FLASH_AccessError =
        MAKE_STATUS(kStatusGroupFlashDriver, 3), /*!< Invalid instruction codes and out-of bound addresses */
    kStatus_FLASH_ProtectionViolation = MAKE_STATUS(
        kStatusGroupFlashDriver, 4), /*!< The program/erase operation is requested to execute on protected areas */
    kStatus_FLASH_CommandFailure =
        MAKE_STATUS(kStatusGroupFlashDriver, 5), /*!< Run-time error during command execution. */
    kStatus_FLASH_UnknownProperty = MAKE_STATUS(kStatusGroupFlashDriver, 6), /*!< Unknown property.*/
    kStatus_FLASH_EraseKeyError   = MAKE_STATUS(kStatusGroupFlashDriver, 7)  /*!< API erase key is invalid.*/
};
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

/*!
 * @name Flash API
 * @{
 */

/*!
 * @brief Initializes the global flash properties structure members
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 *
 * @param config Pointer to the storage for the driver runtime state.
 *
 */
static inline status_t FLASH_Init(flash_config_t *config)
{
    return FLASH_API->flash_init(config);
}

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 *
 * @param config The pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be erased.
 *              NOTE: The start address need to be 4 Bytes-aligned.
 *
 * @param lengthInBytes The length, given in bytes need be 4 Bytes-aligned.
 *
 * @param key The value used to validate all flash erase APIs.
 *
 */
static inline status_t FLASH_EraseSector(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    return FLASH_API->flash_erase_sector(config, start, lengthInBytes, key);
}

/*!
 * @brief Programs flash phrases with data at locations passed in through parameters
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 */
static inline status_t FLASH_ProgramPhrase(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    return FLASH_API->flash_program_phrase(config, start, src, lengthInBytes);
}

/*!
 * @brief Programs flash page with data at locations passed in through parameters
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be programmed. Must be
 *              word-aligned.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be programmed. Must be word-aligned.
 *
 */
static inline status_t FLASH_ProgramPage(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    return FLASH_API->flash_program_page(config, start, src, lengthInBytes);
}

/*!
 * @brief Verifies programming of the desired flash area
 *
 * This function verifies the data programed in the flash memory using the
 * Flash Program Check Command and compares it to the expected data for a given
 * flash area as determined by the start address and length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified. Must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 * @param expectedData A pointer to the expected data that is to be
 *        verified against.
 * @param failedAddress A pointer to the returned failing address.
 * @param failedData A pointer to the returned failing data.  Some derivatives do
 *        not include failed data as part of the FCCOBx registers.  In this
 *        case, zeros are returned upon failure.
 *
 */
static inline status_t FLASH_VerifyProgram(flash_config_t *config,
                                           uint32_t start,
                                           uint32_t lengthInBytes,
                                           const uint8_t *expectedData,
                                           uint32_t *failedAddress,
                                           uint32_t *failedData)
{
    return FLASH_API->flash_verify_program(config, start, lengthInBytes, expectedData, failedAddress, failedData);
}

/*!
 * @brief Verify that the flash phrases are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 */
static inline status_t FLASH_VerifyErasePhrase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    return FLASH_API->flash_verify_erase_phrase(config, start, lengthInBytes);
}

/*!
 * @brief Verify that the flash pages are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 */
static inline status_t FLASH_VerifyErasePage(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    return FLASH_API->flash_verify_erase_page(config, start, lengthInBytes);
}

/*!
 * @brief Verify that the flash sectors are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 */
static inline status_t FLASH_VerifyEraseSector(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    return FLASH_API->flash_verify_erase_sector(config, start, lengthInBytes);
}

/*!
 * @brief Returns the desired flash property
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param whichProperty The desired property from the list of properties in
 *        enum flash_property_tag_t
 * @param value A pointer to the value returned for the desired flash property.
 *
 */
static inline status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    return FLASH_API->flash_get_property(config, whichProperty, value);
}

/*!
 * @brief Verify that the IFR0 phrases are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 */
static inline status_t IFR_VerifyErasePhrase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    return FLASH_API->ifr_verify_erase_phrase(config, start, lengthInBytes);
}

/*!
 * @brief Verify that the IFR0 pages are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 */
static inline status_t IFR_VerifyErasePage(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    return FLASH_API->ifr_verify_erase_page(config, start, lengthInBytes);
}

/*!
 * @brief Verify that the IFR0 sectors are erased
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be verified.
 *        The start address does not need to be sector-aligned but must be word-aligned.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *        to be verified. Must be word-aligned.
 *
 */
static inline status_t IFR_VerifyEraseSector(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    return FLASH_API->ifr_verify_erase_sector(config, start, lengthInBytes);
}

/*!
 * @brief Reads flash at locations passed in through parameters
 *
 * This function read the flash memory from a given flash area as determined
 * by the start address and the length.
 *
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired flash memory to be read.
 * @param dest A pointer to the dest buffer of data that is to be read
 *            from the flash.
 * @param lengthInBytes The length, given in bytes (not words or long-words),
 *                      to be read.
 *
 */
static inline status_t FLASH_Read(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes)
{
    return FLASH_API->flash_read(config, start, dest, lengthInBytes);
}

/*!
 * @brief Get ROM API version.
 *
 * This function read the ROM API version.
 *
 */
static inline uint32_t ROMAPI_GetVersion(void)
{
    return FLASH_API->version;
}

/*!
 * @brief Run the Bootloader API  to force into the ISP mode base on the user arg
 *
 * @param arg Indicates API prototype fields definition.
 *          Refer to the above #user_app_boot_invoke_option_t structure
 */
static inline void ROMAPI_RunBootloader(void *arg)
{
    ROM_API->run_bootloader(arg);
}

/*!
 * @brief Get the UUID
 *
 * @param uuid UUID data array
 *
 */
static inline void ROMAPI_GetUUID(uint8_t *uuid)
{
#define MCXA_UUID_ADDR (0x01100800U)
#define MCXA_UUID_SIZE (16U)

    uint8_t *p = (uint8_t *)MCXA_UUID_ADDR;
    for (uint8_t i = 0; i < MCXA_UUID_SIZE; i++)
    {
        *uuid = *p;
        uuid++;
        p++;
    }
}

/* @} */

/*! @} */

#endif /* _FSL_RESET_H_ */
