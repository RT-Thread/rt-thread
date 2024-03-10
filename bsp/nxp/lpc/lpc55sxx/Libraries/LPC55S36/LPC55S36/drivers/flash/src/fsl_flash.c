/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_flash.h"
#include "fsl_flash_ffr.h"
#include "fsl_flexspi_nor_flash.h"

/*! @brief Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.niobe4analog_iap"
#endif

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
    uint32_t version;   /*!< combined version numbers */
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
    void (*runBootloader)(void *arg);            /*!< Function to start the bootloader executing.*/
    standard_version_t version;                  /*!< Bootloader version number.*/
    const char *copyright;                       /*!< Copyright string.*/
    const uint32_t reserved0;                    /*!< reserved*/
    const flash_driver_interface_t *flashDriver; /*!< Internal Flash driver API.*/
    const uint32_t reserved1[5];                  /*!< reserved*/
    const uint32_t nbootDriver;                   /*!< Please refer to "fsl_nboot.h" */
    const flexspi_nor_flash_driver_t *flexspiNorDriver; /*!< FlexSPI NOR FLASH Driver API.*/
    const uint32_t reserved2;                        /*!< reserved*/
    const uint32_t memoryInterface;                   /*!< Please refer to "fsl_mem_interface.h" */
} bootloader_tree_t;

/*******************************************************************************
 * Code
 ******************************************************************************/

/********************************************************************************
 * Internal Flash driver API
 *******************************************************************************/
/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 */
status_t FLASH_Init(flash_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_init(config);
}

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 */
status_t FLASH_Erase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_erase(config, start, lengthInBytes, key);
}

status_t FLASH_EraseNonBlocking(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_erase_non_blocking(config, start, lengthInBytes, key);

}

/*!
 * @brief Programs flash with data at locations passed in through parameters.
 *
 * This function programs the flash memory with the desired data for a given
 * flash area as determined by the start address and the length.
 */
status_t FLASH_Program(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_program(config, start, src, lengthInBytes);
}

/*!
 * @brief Verifies an erasure of the desired flash area at a specified margin level.
 *
 * This function checks the appropriate number of flash sectors based on
 * the desired start address and length to check whether the flash is erased
 * to the specified read margin level.
 */
status_t FLASH_VerifyErase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_erase(config, start, lengthInBytes);
}

/*!
 * @brief Reads flash at locations passed in through parameters.
 *
 * This function read the flash memory from a given flash area as determined
 * by the start address and the length.
 */
status_t FLASH_Read(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_read(config, start, dest, lengthInBytes);
}

/*!
 * @brief Verifies programming of the desired flash area at a specified margin level.
 *
 * This function verifies the data programed in the flash memory using the
 * Flash Program Check Command and compares it to the expected data for a given
 * flash area as determined by the start address and length.
 */
status_t FLASH_VerifyProgram(flash_config_t *config,
                             uint32_t start,
                             uint32_t lengthInBytes,
                             const uint8_t *expectedData,
                             uint32_t *failedAddress,
                             uint32_t *failedData)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_program(config, start, lengthInBytes, expectedData,
                                                                          failedAddress, failedData);
}

/*!
 * @brief Returns the desired flash property.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_get_property(config, whichProperty, value);
}

#if defined(BL_FEATURE_HAS_BUS_CRYPTO_ENGINE) && BL_FEATURE_HAS_BUS_CRYPTO_ENGINE
status_t FLASH_ErasePrologue(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_erase_with_checker(config, start, lengthInBytes, key);
}

status_t FLASH_ProgramPrologue(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_program_with_checker(config, start, src, lengthInBytes);
}

status_t FLASH_VerifyProgramPrologue(flash_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_verify_program_with_checker(
        config, start, lengthInBytes, expectedData, failedAddress, failedData);
}

#endif // BL_FEATURE_HAS_BUS_CRYPTO_ENGINE

#if defined(FSL_FEATURE_SYSCON_HAS_FLASH_HIDING) && (FSL_FEATURE_SYSCON_HAS_FLASH_HIDING == 1)
/*!
 * @brief Validates the given address range is loaded in the flash hiding region.
 */
status_t FLASH_IsFlashAreaReadable(flash_config_t *config, uint32_t startAddress, uint32_t lengthInBytes)
{
    function_command_option_t runCmdFuncOption;
    runCmdFuncOption.commandAddr = 0x13028c41U; /*!< get the flash erase api location adress in rom */
    return runCmdFuncOption.isFlashAreaReadable(config, startAddress, lengthInBytes);
}
#endif

#if defined(FSL_FEATURE_SYSCON_HAS_CDPA) && (FSL_FEATURE_SYSCON_HAS_CDPA == 1)
/*!
 * @brief Validates the given address range is loaded in the Flash firewall page locked region.
 */
status_t FLASH_IsFlashAreaModifiable(flash_config_t *config, uint32_t startAddress, uint32_t lengthInBytes)
{
    function_command_option_t runCmdFuncOption;
    runCmdFuncOption.commandAddr = 0x13028ca1U; /*!< get the flash erase api location adress in rom */
    return runCmdFuncOption.isFlashAreaModifiable(config, startAddress, lengthInBytes);
}
#endif

/*!
 * @brief Get flash command execute status.
 */
status_t FLASH_GetCommandState(flash_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_get_command_state(config);
}

/********************************************************************************
 * fsl iap ffr CODE
 *******************************************************************************/

/*!
 * @brief Initializes the global FFR properties structure members.
 */
status_t FFR_Init(flash_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_init(config);
}

/*!
 * @brief Enable firewall for all flash banks.
 */
status_t FFR_Lock(flash_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_lock(config);
}

/*!
 * @brief APIs to access CMPA pages;
 * This routine will erase "customer factory page" and program the page with passed data.
 */
status_t FFR_CustFactoryPageWrite(flash_config_t *config, uint8_t *page_data, bool seal_part)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_cust_factory_page_write(config, page_data, seal_part);
}

/*!
 * @brief See fsl_iap_ffr.h for documentation of this function.
 */
status_t FFR_GetUUID(flash_config_t *config, uint8_t *uuid)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_get_uuid(config, uuid);
}

/*!
 * @brief APIs to access CMPA pages
 * Read data stored in 'Customer Factory CFG Page'.
 */
status_t FFR_GetCustomerData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_get_customer_data(config, pData, offset, len);
}

/*!
 * @brief This routine writes the 3 pages allocated for Key store data.
 */
status_t FFR_CustKeystoreWrite(flash_config_t *config, ffr_key_store_t *pKeyStore)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_cust_keystore_write(config, pKeyStore);
}

/*!
 * @brief APIs to access CFPA pages
 * This routine will erase CFPA and program the CFPA page with passed data.
 */
status_t FFR_InfieldPageWrite(flash_config_t *config, uint8_t *page_data, uint32_t valid_len)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_infield_page_write(config, page_data, valid_len);
}

/*!
 * @brief APIs to access CFPA pages
 * Generic read function, used by customer to read data stored in 'Customer In-field Page'.
 */
status_t FFR_GetCustomerInfieldData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_get_customer_infield_data(config, pData, offset, len);
}

/*!
 * @brief Initialize the Security Library for FFR driver
 */
status_t FFR_SecLibInit(flash_config_t *config, uint32_t *context)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->ffr_seclib_init(config, context);
}

/*!
 * @brief The API is used for getting the customer key store data from the customer key store region(0x3e400 ¨C 0x3e600),
 * and the API should be called after the FLASH_Init and FFR_Init.
 */
status_t FFR_GetCustKeystoreData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flashDriver->flash_get_cust_keystore(config, pData, offset, len);
}

/********************************************************************************
 * FlexSPI NOR FLASH Driver API
 *******************************************************************************/
/*!
 * @brief Initialize Serial NOR devices via FLEXSPI.
 */
status_t FLEXSPI_NorFlash_Init(uint32_t instance, flexspi_nor_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->init(instance, config);
}

/*!
 * @brief Program data to Serial NOR via FlexSPI
 */
status_t FLEXSPI_NorFlash_ProgramPage(uint32_t instance,
                                      flexspi_nor_config_t *config,
                                      uint32_t dstAddr,
                                      const uint32_t *src)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->page_program(instance, config, dstAddr, src);
}

/*!
 * @brief Erase all the Serial NOR devices connected on FlexSPI
 */
status_t FLEXSPI_NorFlash_EraseAll(uint32_t instance, flexspi_nor_config_t *config)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->erase_all(instance, config);
}

/*!
 * @brief Erase Flash Region specified by address and length
 */
status_t FLEXSPI_NorFlash_Erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->erase(instance, config, start, length);
}

/*!
 * @brief Erase one sector specified by address
 */
status_t FLEXSPI_NorFlash_EraseSector(uint32_t instance, flexspi_nor_config_t *config, uint32_t address)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->erase_sector(instance, config, address);
}

/*!
 * @brief Erase one block specified by address
 */
status_t FLEXSPI_NorFlash_EraseBlock(uint32_t instance, flexspi_nor_config_t *config, uint32_t address)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->erase_block(instance, config, address);
}

/*!
 * @brief Get FlexSPI NOR Configuration Block based on specified option
 */
status_t FLEXSPI_NorFlash_GetConfig(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->get_config(instance, config, option);
}

/*!
 * @brief Read data from Serial NOR
 */
status_t FLEXSPI_NorFlash_Read(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->read(instance, config, dst, start, bytes);
}

/*!
 * @brief Perform FlexSPI command
 */
status_t FLEXSPI_NorFlash_CommandXfer(uint32_t instance, flexspi_xfer_t *xfer)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->xfer(instance, xfer);
}

/*!
 * @brief Configure FlexSPI Lookup table
 */
status_t FLEXSPI_NorFlash_UpdateLut(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->update_lut(instance, seqIndex, lutBase, numberOfSeq);
}

/*!
 * @brief Set flexspi clock source
 */
status_t FLEXSPI_NorFlash_SetClockSource(uint32_t clockSource)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->set_clock_source(clockSource);
}

/*!
 * @brief config flexspi clock
 */
void FLEXSPI_NorFlash_ConfigClock(uint32_t instance, uint32_t freqOption, uint32_t sampleClkMode)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    BOOTLOADER_API_TREE_POINTER->flexspiNorDriver->config_clock(instance, freqOption, sampleClkMode);
}
