/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_iap.h"
#include "fsl_iap_ffr.h"
#include "fsl_iap_kbp.h"
#include "fsl_iap_skboot_authenticate.h"
#include "fsl_device_registers.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iap1"
#endif

#if (defined(LPC5512_SERIES) || defined(LPC5514_SERIES) || defined(LPC55S14_SERIES) || defined(LPC5516_SERIES) || \
     defined(LPC55S16_SERIES) || defined(LPC5524_SERIES) || defined(LPC5502_SERIES) || defined(LPC5504_SERIES) || \
     defined(LPC5506_SERIES) || defined(LPC55S04_SERIES) || defined(LPC55S06_SERIES))

#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x1301fe00U)

#elif (defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES) || defined(LPC5526_SERIES) || \
       defined(LPC55S26_SERIES) || defined(LPC5528_SERIES) || defined(LPC55S28_SERIES) ||                       \
       defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES))

#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x130010f0U)

#else
#error "No valid CPU defined!"

#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t get_cfpa_higher_version(flash_config_t *config);

/*!
 * @name flash and ffr Structure
 * @{
 */

typedef union functionCommandOption
{
    uint32_t commandAddr;
    status_t (*eraseCommand)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*programCommand)(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*verifyProgramCommand)(flash_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flashReadCommand)(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes);
} function_command_option_t;

/*
 *!@brief Structure of version property.
 *
 *!@ingroup bl_core
 */
typedef union StandardVersion
{
    struct
    {
        uint32_t bugfix : 8; /*!< bugfix version [7:0] */
        uint32_t minor : 8;  /*!< minor version [15:8] */
        uint32_t major : 8;  /*!< major version [23:16] */
        uint32_t name : 8;   /*!< name [31:24] */
    };
    uint32_t version; /*!< combined version numbers. */
#if defined(__cplusplus)
    StandardVersion() : version(0)
    {
    }
    StandardVersion(uint32_t version) : version(version)
    {
    }
#endif
} standard_version_t;

/*! @brief Interface for the flash driver.*/
typedef struct version1FlashDriverInterface
{
    standard_version_t version; /*!< flash driver API version number.*/

    /*!< Flash driver.*/
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
    uint32_t reserved[3]; /*! Reserved for future use */
    /*!< Flash FFR driver*/
    status_t (*ffr_init)(flash_config_t *config);
    status_t (*ffr_lock_all)(flash_config_t *config);
    status_t (*ffr_cust_factory_page_write)(flash_config_t *config, uint8_t *page_data, bool seal_part);
    status_t (*ffr_get_uuid)(flash_config_t *config, uint8_t *uuid);
    status_t (*ffr_get_customer_data)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
    status_t (*ffr_keystore_write)(flash_config_t *config, ffr_key_store_t *pKeyStore);
    status_t (*ffr_keystore_get_ac)(flash_config_t *config, uint8_t *pActivationCode);
    status_t (*ffr_keystore_get_kc)(flash_config_t *config, uint8_t *pKeyCode, ffr_key_type_t keyIndex);
    status_t (*ffr_infield_page_write)(flash_config_t *config, uint8_t *page_data, uint32_t valid_len);
    status_t (*ffr_get_customer_infield_data)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
} version1_flash_driver_interface_t;

/*! @brief Interface for the flash driver.*/
typedef struct version0FlashDriverInterface
{
    standard_version_t version; /*!< flash driver API version number.*/

    /*!< Flash driver.*/
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

    /*!< Flash FFR driver*/
    status_t (*ffr_init)(flash_config_t *config);
    status_t (*ffr_lock_all)(flash_config_t *config);
    status_t (*ffr_cust_factory_page_write)(flash_config_t *config, uint8_t *page_data, bool seal_part);
    status_t (*ffr_get_uuid)(flash_config_t *config, uint8_t *uuid);
    status_t (*ffr_get_customer_data)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
    status_t (*ffr_keystore_write)(flash_config_t *config, ffr_key_store_t *pKeyStore);
    status_t (*ffr_keystore_get_ac)(flash_config_t *config, uint8_t *pActivationCode);
    status_t (*ffr_keystore_get_kc)(flash_config_t *config, uint8_t *pKeyCode, ffr_key_type_t keyIndex);
    status_t (*ffr_infield_page_write)(flash_config_t *config, uint8_t *page_data, uint32_t valid_len);
    status_t (*ffr_get_customer_infield_data)(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len);
} version0_flash_driver_interface_t;

typedef union flashDriverInterface
{
    const version1_flash_driver_interface_t *version1FlashDriver;
    const version0_flash_driver_interface_t *version0FlashDriver;
} flash_driver_interface_t;

/*! @}*/

/*!
 * @name Bootloader API and image authentication Structure
 * @{
 */

/*! @brief Interface for Bootloader API functions. */
typedef struct _kb_interface
{
    /*!< Initialize the API. */
    status_t (*kb_init_function)(kb_session_ref_t **session, const kb_options_t *options);
    status_t (*kb_deinit_function)(kb_session_ref_t *session);
    status_t (*kb_execute_function)(kb_session_ref_t *session, const uint8_t *data, uint32_t dataLength);
} kb_interface_t;

//! @brief Interface for image authentication API
typedef struct _skboot_authenticate_interface
{
    skboot_status_t (*skboot_authenticate_function)(const uint8_t *imageStartAddr, secure_bool_t *isSignVerified);
    void (*skboot_hashcrypt_irq_handler)(void);
} skboot_authenticate_interface_t;
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
    void (*runBootloader)(void *arg);      /*!< Function to start the bootloader executing. */
    standard_version_t bootloader_version; /*!< Bootloader version number. */
    const char *copyright;                 /*!< Copyright string. */
    const uint32_t reserved0;              /*!< Do NOT use. */
    flash_driver_interface_t flashDriver;
    const kb_interface_t *kbApi;                               /*!< Bootloader API. */
    const uint32_t reserved1[4];                               /*!< Do NOT use. */
    const skboot_authenticate_interface_t *skbootAuthenticate; /*!< Image authentication API. */
} bootloader_tree_t;

/*******************************************************************************
 * Prototype
 ******************************************************************************/
static uint32_t get_rom_api_version(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! Get pointer to flash driver API table in ROM. */
#define VERSION1_FLASH_API_TREE       BOOTLOADER_API_TREE_POINTER->flashDriver.version1FlashDriver
#define VERSION0_FLASH_API_TREE       BOOTLOADER_API_TREE_POINTER->flashDriver.version0FlashDriver
#define LPC55S69_REV0_FLASH_READ_ADDR (0x130043a3U)
#define LPC55S69_REV1_FLASH_READ_ADDR (0x13007539U)
#define LPC55S16_REV0_FLASH_READ_ADDR (0x1300ade5U)

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t get_rom_api_version(void)
{
    if (BOOTLOADER_API_TREE_POINTER->bootloader_version.major == 3u)
    {
        return 1u;
    }
    else
    {
        return 0u;
    }
}

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function checks and initializes the Flash module for the other Flash APIs.
 */
status_t FLASH_Init(flash_config_t *config)
{
    status_t status;
    /* Initialize the clock to 96MHz */
    config->modeConfig.sysFreqInMHz = (uint32_t)kSysToFlashFreq_defaultInMHz;
    if (get_rom_api_version() == 1u)
    {
        status = VERSION1_FLASH_API_TREE->flash_init(config);
    }
    else
    {
        status = VERSION0_FLASH_API_TREE->flash_init(config);
    }

    if (config->PFlashTotalSize == 0xA0000U)
    {
        config->PFlashTotalSize -= 17U * config->PFlashPageSize;
    }

    return status;
}

/*!
 * @brief Erases the flash sectors encompassed by parameters passed into function.
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 */
status_t FLASH_Erase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    if (get_rom_api_version() == 0u)
    {
        function_command_option_t runCmdFuncOption;
        runCmdFuncOption.commandAddr = 0x1300413bU; /*!< get the flash erase api location adress in rom */
        return runCmdFuncOption.eraseCommand(config, start, lengthInBytes, key);
    }
    else
    {
        return VERSION1_FLASH_API_TREE->flash_erase(config, start, lengthInBytes, key);
    }
}

/*! See fsl_iap.h for documentation of this function. */
status_t FLASH_Program(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    if (get_rom_api_version() == 0u)
    {
        function_command_option_t runCmdFuncOption;
        runCmdFuncOption.commandAddr = 0x1300419dU; /*!< get the flash program api location adress in rom*/
        return runCmdFuncOption.programCommand(config, start, src, lengthInBytes);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->flash_program(config, start, src, lengthInBytes);
    }
}

/*! See fsl_iap.h for documentation of this function. */
status_t FLASH_Read(flash_config_t *config, uint32_t start, uint8_t *dest, uint32_t lengthInBytes)
{
    if (get_rom_api_version() == 0u)
    {
        /*!< get the flash read api location adress in rom*/
        function_command_option_t runCmdFuncOption;
        runCmdFuncOption.commandAddr = LPC55S69_REV0_FLASH_READ_ADDR;
        return runCmdFuncOption.flashReadCommand(config, start, dest, lengthInBytes);
    }
    else
    {
        /*!< get the flash read api location adress in rom*/
        function_command_option_t runCmdFuncOption;
        if ((SYSCON->DIEID & SYSCON_DIEID_REV_ID_MASK) != 0u)
        {
            runCmdFuncOption.commandAddr = LPC55S69_REV1_FLASH_READ_ADDR;
        }
        else
        {
            runCmdFuncOption.commandAddr = LPC55S16_REV0_FLASH_READ_ADDR;
        }
        return runCmdFuncOption.flashReadCommand(config, start, dest, lengthInBytes);
    }
}

/*! See fsl_iap.h for documentation of this function. */
status_t FLASH_VerifyErase(flash_config_t *config, uint32_t start, uint32_t lengthInBytes)
{
    assert(VERSION1_FLASH_API_TREE);
    return VERSION1_FLASH_API_TREE->flash_verify_erase(config, start, lengthInBytes);
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
    if (get_rom_api_version() == 0u)
    {
        function_command_option_t runCmdFuncOption;
        runCmdFuncOption.commandAddr = 0x1300427dU; /*!< get the flash verify program api location adress in rom*/
        return runCmdFuncOption.verifyProgramCommand(config, start, lengthInBytes, expectedData, failedAddress,
                                                     failedData);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->flash_verify_program(config, start, lengthInBytes, expectedData, failedAddress,
                                                             failedData);
    }
}

/*!
 * @brief Returns the desired flash property.
 */
status_t FLASH_GetProperty(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value)
{
    assert(VERSION1_FLASH_API_TREE);
    return VERSION1_FLASH_API_TREE->flash_get_property(config, whichProperty, value);
}
/********************************************************************************
 * fsl iap ffr CODE
 *******************************************************************************/

static status_t get_cfpa_higher_version(flash_config_t *config)
{
    uint32_t pageData[FLASH_FFR_MAX_PAGE_SIZE / sizeof(uint32_t)];
    uint32_t versionPing = 0U;
    uint32_t versionPong = 0U;

    /* Get the CFPA ping page data and the corresponding version */
    config->ffrConfig.cfpaPageOffset = 1U;
    status_t status = FFR_GetCustomerInfieldData(config, (uint8_t *)pageData, 0U, FLASH_FFR_MAX_PAGE_SIZE);
    if (status != (int32_t)kStatus_FLASH_Success)
    {
        return status;
    }
    versionPing = pageData[1];

    /* Get the CFPA pong page data and the corresponding version */
    config->ffrConfig.cfpaPageOffset = 2U;
    status = FFR_GetCustomerInfieldData(config, (uint8_t *)pageData, 0U, FLASH_FFR_MAX_PAGE_SIZE);
    if (status != (int32_t)kStatus_FLASH_Success)
    {
        return status;
    }
    versionPong = pageData[1];

    /* Compare the CFPA ping version and pong version and set it correctly in flash_config structure */
    if (versionPing > versionPong)
    {
        config->ffrConfig.cfpaPageVersion = versionPing;
        config->ffrConfig.cfpaPageOffset  = 1U;
    }
    else
    {
        config->ffrConfig.cfpaPageVersion = versionPong;
        config->ffrConfig.cfpaPageOffset  = 2U;
    }
    return (int32_t)kStatus_FLASH_Success;
}

/*!
 * Initializes the global FFR properties structure members.
 */
status_t FFR_Init(flash_config_t *config)
{
    status_t status;
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        status = VERSION0_FLASH_API_TREE->ffr_init(config);
        if (status != (status_t)kStatus_FLASH_Success)
        {
            return status;
        }
        return get_cfpa_higher_version(config);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        status = VERSION1_FLASH_API_TREE->ffr_init(config);
        if (status != (status_t)kStatus_FLASH_Success)
        {
            return status;
        }
        return get_cfpa_higher_version(config);
    }
}

/*!
 * Enable firewall for all flash banks.
 */
status_t FFR_Lock_All(flash_config_t *config)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_lock_all(config);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_lock_all(config);
    }
}

/*!
 * APIs to access CMPA pages;
 * This routine will erase "customer factory page" and program the page with passed data.
 */
status_t FFR_CustFactoryPageWrite(flash_config_t *config, uint8_t *page_data, bool seal_part)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_cust_factory_page_write(config, page_data, seal_part);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_cust_factory_page_write(config, page_data, seal_part);
    }
}

/*!
 * See fsl_iap_ffr.h for documentation of this function.
 */
status_t FFR_GetUUID(flash_config_t *config, uint8_t *uuid)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_get_uuid(config, uuid);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_get_uuid(config, uuid);
    }
}

/*!
 * APIs to access CMPA pages
 * Read data stored in 'Customer Factory CFG Page'.
 */
status_t FFR_GetCustomerData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_get_customer_data(config, pData, offset, len);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_get_customer_data(config, pData, offset, len);
    }
}

/*!
 * This routine writes the 3 pages allocated for Key store data,
 * Used during manufacturing. Should write pages when 'customer factory page' is not in sealed state.
 */
status_t FFR_KeystoreWrite(flash_config_t *config, ffr_key_store_t *pKeyStore)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_keystore_write(config, pKeyStore);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_keystore_write(config, pKeyStore);
    }
}

/*! See fsl_iap_ffr.h for documentation of this function. */
status_t FFR_KeystoreGetAC(flash_config_t *config, uint8_t *pActivationCode)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_keystore_get_ac(config, pActivationCode);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_keystore_get_ac(config, pActivationCode);
    }
}

/*! See fsl_iap_ffr.h for documentation of this function. */
status_t FFR_KeystoreGetKC(flash_config_t *config, uint8_t *pKeyCode, ffr_key_type_t keyIndex)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_keystore_get_kc(config, pKeyCode, keyIndex);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_keystore_get_kc(config, pKeyCode, keyIndex);
    }
}

/*!
 * APIs to access CFPA pages
 * This routine will erase CFPA and program the CFPA page with passed data.
 */
status_t FFR_InfieldPageWrite(flash_config_t *config, uint8_t *page_data, uint32_t valid_len)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_infield_page_write(config, page_data, valid_len);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_infield_page_write(config, page_data, valid_len);
    }
}

/*!
 * APIs to access CFPA pages
 * Generic read function, used by customer to read data stored in 'Customer In-field Page'.
 */
status_t FFR_GetCustomerInfieldData(flash_config_t *config, uint8_t *pData, uint32_t offset, uint32_t len)
{
    if (get_rom_api_version() == 0u)
    {
        assert(VERSION0_FLASH_API_TREE);
        return VERSION0_FLASH_API_TREE->ffr_get_customer_infield_data(config, pData, offset, len);
    }
    else
    {
        assert(VERSION1_FLASH_API_TREE);
        return VERSION1_FLASH_API_TREE->ffr_get_customer_infield_data(config, pData, offset, len);
    }
}

/********************************************************************************
 * Bootloader API
 *******************************************************************************/
/*!
 * @brief Initialize ROM API for a given operation.
 *
 * Inits the ROM API based on the options provided by the application in the second
 * argument. Every call to rom_init() should be paired with a call to rom_deinit().
 */
status_t kb_init(kb_session_ref_t **session, const kb_options_t *options)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->kbApi->kb_init_function(session, options);
}

/*!
 * @brief Cleans up the ROM API context.
 *
 * After this call, the @a context parameter can be reused for another operation
 * by calling rom_init() again.
 */
status_t kb_deinit(kb_session_ref_t *session)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->kbApi->kb_deinit_function(session);
}

/*!
 * Perform the operation configured during init.
 *
 * This application must call this API repeatedly, passing in sequential chunks of
 * data from the boot image (SB file) that is to be processed. The ROM will perform
 * the selected operation on this data and return. The application may call this
 * function with as much or as little data as it wishes, which can be used to select
 * the granularity of time given to the application in between executing the operation.
 *
 * @param context Current ROM context pointer.
 * @param data Buffer of boot image data provided to the ROM by the application.
 * @param dataLength Length in bytes of the data in the buffer provided to the ROM.
 *
 * @retval #kStatus_Success The operation has completed successfully.
 * @retval #kStatus_Fail An error occurred while executing the operation.
 * @retval #kStatus_RomApiNeedMoreData No error occurred, but the ROM needs more data to
 *     continue processing the boot image.
 */
status_t kb_execute(kb_session_ref_t *session, const uint8_t *data, uint32_t dataLength)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->kbApi->kb_execute_function(session, data, dataLength);
}

/********************************************************************************
 * Image authentication API
 *******************************************************************************/

/*!
 * @brief Authenticate entry function with ARENA allocator init
 *
 * This is called by ROM boot or by ROM API g_skbootAuthenticateInterface
 */
skboot_status_t skboot_authenticate(const uint8_t *imageStartAddr, secure_bool_t *isSignVerified)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->skbootAuthenticate->skboot_authenticate_function(imageStartAddr,
                                                                                         isSignVerified);
}

/*!
 * @brief Interface for image authentication API
 */
void HASH_IRQHandler(void)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    BOOTLOADER_API_TREE_POINTER->skbootAuthenticate->skboot_hashcrypt_irq_handler();
}
/********************************************************************************
 * EOF
 *******************************************************************************/
