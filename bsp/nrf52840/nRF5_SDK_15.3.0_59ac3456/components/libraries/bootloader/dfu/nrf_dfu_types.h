/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**@file
 *
 * @defgroup sdk_nrf_dfu_types DFU types
 * @{
 * @ingroup  nrf_dfu
 */

#ifndef NRF_DFU_TYPES_H__
#define NRF_DFU_TYPES_H__

#include <stdint.h>
#include <stddef.h>

#include "sdk_common.h"
#include "nrf.h"
#include "nrf_mbr.h"
#include "app_util_platform.h"
#include "sdk_config.h"

#if defined(NRF_DFU_TRANSPORT_BLE) && NRF_DFU_TRANSPORT_BLE
#include "ble_gap.h"
#define SYSTEM_SERVICE_ATT_SIZE 8   /**< Size of the system service attribute length including CRC-16 at the end. */
#endif

#ifdef __cplusplus
extern "C" {
#endif


#define INIT_COMMAND_MAX_SIZE      512 /**< Maximum size of the init command stored in dfu_settings. */
#define INIT_COMMAND_MAX_SIZE_v1   256 /**< Maximum size of the init command in settings version 1. */

/** @brief  Size of a flash page. This value is used for calculating the size of the reserved
 *          flash space in the bootloader region.
 */
#if defined(NRF51)
    #define CODE_PAGE_SIZE            (PAGE_SIZE_IN_WORDS * sizeof(uint32_t))
#elif defined(NRF52_SERIES)
    #define CODE_PAGE_SIZE            (MBR_PAGE_SIZE_IN_WORDS * sizeof(uint32_t))
#else
    #error "Architecture not set."
#endif

/** @brief  Maximum size of a data object.*/
#if defined(NRF51)
    #define DATA_OBJECT_MAX_SIZE           (CODE_PAGE_SIZE * 4)
#elif defined(NRF52_SERIES) || defined (__SDK_DOXYGEN__)
    #define DATA_OBJECT_MAX_SIZE           (CODE_PAGE_SIZE)
#else
    #error "Architecture not set."
#endif

/** @brief  Page location of the bootloader settings address.
 */
#if defined  (NRF51)
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x0003FC00UL)
#elif defined( NRF52810_XXAA )
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x0002F000UL)
#elif defined( NRF52811_XXAA )
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x0002F000UL)
#elif defined( NRF52832_XXAA )
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x0007F000UL)
#elif defined(NRF52840_XXAA)
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x000FF000UL)
#else
    #error No valid target set for BOOTLOADER_SETTINGS_ADDRESS.
#endif

#define BOOTLOADER_SETTINGS_PAGE_SIZE       (CODE_PAGE_SIZE)

/**
 * @brief Location of the pointer to MBR params page.
 *
 * See also @c MBR_PARAMS_PAGE_ADDRESS in @c app_util.h.
 */
#define NRF_UICR_MBR_PARAMS_PAGE_ADDRESS    (MBR_PARAM_PAGE_ADDR)
#define NRF_MBR_PARAMS_PAGE_SIZE            (CODE_PAGE_SIZE)

/** @brief Page location of the MBR parameters page address.
 */
#if defined(NRF52840_XXAA) || defined(NRF52840_XXAA_ENGA)
    #define NRF_MBR_PARAMS_PAGE_ADDRESS         (0x000FE000UL)
#elif defined(NRF52832_XXAA)
    #define NRF_MBR_PARAMS_PAGE_ADDRESS         (0x0007E000UL)
#elif defined(NRF52810_XXAA)
    #define NRF_MBR_PARAMS_PAGE_ADDRESS         (0x0002E000UL)
#elif defined(NRF52811_XXAA)
    #define NRF_MBR_PARAMS_PAGE_ADDRESS         (0x0002E000UL)
#endif

#define BOOTLOADER_SETTINGS_BACKUP_ADDRESS NRF_MBR_PARAMS_PAGE_ADDRESS


#ifndef NRF_DFU_APP_DATA_AREA_SIZE
#define NRF_DFU_APP_DATA_AREA_SIZE (CODE_PAGE_SIZE * 3)
#endif

STATIC_ASSERT((NRF_DFU_APP_DATA_AREA_SIZE % CODE_PAGE_SIZE) == 0, "NRF_DFU_APP_DATA_AREA_SIZE must be a multiple of the flash page size.");

#define DFU_APP_DATA_RESERVED      NRF_DFU_APP_DATA_AREA_SIZE // For backward compatibility with 15.0.0.

/** @brief Total size of the region between the SoftDevice and the bootloader.
 */
#define DFU_REGION_END(bootloader_start_addr) ((bootloader_start_addr) - (NRF_DFU_APP_DATA_AREA_SIZE))

#if defined(BLE_STACK_SUPPORT_REQD) || defined(ANT_STACK_SUPPORT_REQD)
#define DFU_REGION_START                    (nrf_dfu_bank0_start_addr())
#else
#define DFU_REGION_START                    (MBR_SIZE)
#endif

#define DFU_REGION_TOTAL_SIZE               ((DFU_REGION_END) - (DFU_REGION_START))

#define NRF_DFU_CURRENT_BANK_0 0x00
#define NRF_DFU_CURRENT_BANK_1 0x01

#define NRF_DFU_BANK_LAYOUT_DUAL   0x00
#define NRF_DFU_BANK_LAYOUT_SINGLE 0x01

/** @brief DFU bank state codes.
 *
 * @details The DFU bank state indicates the content of a bank:
 *          A valid image of a certain type or an invalid image.
 */

#define NRF_DFU_BANK_INVALID         0x00 /**< Invalid image. */
#define NRF_DFU_BANK_VALID_APP       0x01 /**< Valid application. */
#define NRF_DFU_BANK_VALID_SD        0xA5 /**< Valid SoftDevice. */
#define NRF_DFU_BANK_VALID_BL        0xAA /**< Valid bootloader. */
#define NRF_DFU_BANK_VALID_SD_BL     0xAC /**< Valid SoftDevice and bootloader. */
#define NRF_DFU_BANK_VALID_EXT_APP   0xB1 /**< Valid application designated for a remote node. */

/** @brief Description of a single bank. */
#pragma pack(4)
typedef struct
{
    uint32_t                image_size;         /**< Size of the image in the bank. */
    uint32_t                image_crc;          /**< CRC of the image. If set to 0, the CRC is ignored. */
    uint32_t                bank_code;          /**< Identifier code for the bank. */
} nrf_dfu_bank_t;

/**@brief DFU progress.
 *
 * Be aware of the difference between objects and firmware images. A firmware image consists of multiple objects, each of a maximum size @ref DATA_OBJECT_MAX_SIZE.
 *
 * @note The union inside this struct is cleared when CREATE_OBJECT of command type is executed, and when there is a valid post-validation.
 *       In DFU activation (after reset) the @ref dfu_progress_t::update_start_address will be used in case of a SD/SD+BL update.
 */
ANON_UNIONS_ENABLE;
typedef struct
{
    uint32_t command_size;              /**< The size of the current init command stored in the DFU settings. */
    uint32_t command_offset;            /**< The offset of the currently received init command data. The offset will increase as the init command is received. */
    uint32_t command_crc;               /**< The calculated CRC of the init command (calculated after the transfer is completed). */
    uint32_t data_object_size;          /**< The size of the last object created. Note that this size is not the size of the whole firmware image.*/
    union
    {
        struct
        {
            uint32_t firmware_image_crc;        /**< CRC value of the current firmware (continuously calculated as data is received). */
            uint32_t firmware_image_crc_last;   /**< The CRC of the last executed object. */
            uint32_t firmware_image_offset;     /**< The offset of the current firmware image being transferred. Note that this offset is the offset in the entire firmware image and not only the current object. */
            uint32_t firmware_image_offset_last;/**< The offset of the last executed object from the start of the firmware image. */
        };
        struct
        {
            uint32_t update_start_address;      /**< Value indicating the start address of the new firmware (before copy). It's always used, but it's most important for an SD/SD+BL update where the SD changes size or if the DFU process had a power loss when updating a SD with changed size. */
        };
    };
} dfu_progress_t;
ANON_UNIONS_DISABLE;

/** @brief Event types in the bootloader and DFU process. */
typedef enum
{
    NRF_DFU_EVT_DFU_INITIALIZED,        /**< Starting DFU. */
    NRF_DFU_EVT_TRANSPORT_ACTIVATED,    /**< Transport activated (e.g. BLE connected, USB plugged in). */
    NRF_DFU_EVT_TRANSPORT_DEACTIVATED,  /**< Transport deactivated (e.g. BLE disconnected, USB plugged out). */
    NRF_DFU_EVT_DFU_STARTED,            /**< DFU process started. */
    NRF_DFU_EVT_OBJECT_RECEIVED,        /**< A DFU data object has been received. */
    NRF_DFU_EVT_DFU_FAILED,             /**< DFU process has failed, been interrupted, or hung. */
    NRF_DFU_EVT_DFU_COMPLETED,          /**< DFU process completed. */
    NRF_DFU_EVT_DFU_ABORTED,            /**< DFU process aborted. */
} nrf_dfu_evt_type_t;

/**
 * @brief Function for notifying DFU state.
 */
typedef void (*nrf_dfu_observer_t)(nrf_dfu_evt_type_t notification);

#define NRF_DFU_PEER_DATA_LEN 64 /**< The length in bytes of nrf_dfu_peer_data_t expected by tools manipulating the settings page. Do not change without changing the settings page version. */
#define NRF_DFU_ADV_NAME_LEN  28 /**< The length in bytes of nrf_dfu_adv_name_t expected by tools manipulating the settings page. Do not change without changing the settings page version. */

#if defined(NRF_DFU_TRANSPORT_BLE) && NRF_DFU_TRANSPORT_BLE

typedef struct
{
    uint32_t            crc;                                    /**< CRC of the rest of the parameters in this struct. */
    ble_gap_id_key_t    ble_id;                                 /**< BLE GAP identity key of the device that initiated the DFU process. */
    ble_gap_enc_key_t   enc_key;                                /**< Encryption key structure containing encrypted diversifier and LTK for reestablishing the bond. */
    uint8_t             sys_serv_attr[SYSTEM_SERVICE_ATT_SIZE]; /**< System service attributes for restoring of Service Changed Indication setting in DFU mode. */
} nrf_dfu_peer_data_t;

typedef enum
{
    DFU_PEER_DATA_STATE_INVALID             = 0,
    DFU_PEER_DATA_STATE_INITIALIZED         = 1,
    DFU_PEER_DATA_STATE_WRITE_REQUESTED     = 2,
    DFU_PEER_DATA_STATE_WRITE_FINISHED      = 3,
    DFU_PEER_DATA_STATE_WRITE_FAILED        = 4,
} nrf_dfu_peer_data_state_t;

typedef struct
{
    uint32_t    crc;                            /**< CRC of the rest of the parameters in this struct. Calculated by the bootloader. */
    uint8_t     name[20];                       /**< New advertisement name to set. */
    uint32_t    len;                            /**< Length of the advertisement name. */
} nrf_dfu_adv_name_t;

typedef enum
{
    DFU_ADV_NAME_STATE_INVALID              = 0,
    DFU_ADV_NAME_STATE_INITIALIZED          = 1,
    DFU_ADV_NAME_STATE_WRITE_REQUESTED      = 2,
    DFU_ADV_NAME_STATE_WRITE_FINISHED       = 3,
    DFU_ADV_NAME_STATE_WRITE_FAILED         = 4,
} nrf_dfu_set_adv_name_state_t;

#else
typedef struct
{
    uint8_t dummy_data[NRF_DFU_PEER_DATA_LEN];
} nrf_dfu_peer_data_t;

typedef struct
{
    uint8_t dummy_data[NRF_DFU_ADV_NAME_LEN];
} nrf_dfu_adv_name_t;
#endif // NRF_DFU_TRANSPORT_BLE

STATIC_ASSERT(sizeof(nrf_dfu_peer_data_t) == NRF_DFU_PEER_DATA_LEN, "nrf_dfu_peer_data_t has unexpected length. This can cause incompatibility with tools.");
STATIC_ASSERT(sizeof(nrf_dfu_adv_name_t)  == NRF_DFU_ADV_NAME_LEN,  "nrf_dfu_adv_name_t has unexpected length. This can cause incompatibility with tools.");

#define SETTINGS_RESERVED_AREA_SIZE    16 /**< The number of words in the reserved area of the DFU settings. */
#define SETTINGS_BOOT_VALIDATION_SIZE  64 /**< The number of bytes reserved for boot_validation value. */


typedef enum
{
    NO_VALIDATION,
    VALIDATE_CRC,
    VALIDATE_SHA256,
    VALIDATE_ECDSA_P256_SHA256,
} boot_validation_type_t;

typedef struct
{
    boot_validation_type_t type;
    uint8_t                bytes[SETTINGS_BOOT_VALIDATION_SIZE];
} boot_validation_t;

/**@brief DFU settings for application and bank data.
 */
typedef struct
{
    uint32_t            crc;                /**< CRC for the stored DFU settings, not including the CRC itself. If 0xFFFFFFF, the CRC has never been calculated. */
    uint32_t            settings_version;   /**< Version of the current DFU settings struct layout. */
    uint32_t            app_version;        /**< Version of the last stored application. */
    uint32_t            bootloader_version; /**< Version of the last stored bootloader. */

    uint32_t            bank_layout;        /**< Bank layout: single bank or dual bank. This value can change. */
    uint32_t            bank_current;       /**< The bank that is currently used. */

    nrf_dfu_bank_t      bank_0;             /**< Bank 0. */
    nrf_dfu_bank_t      bank_1;             /**< Bank 1. */

    uint32_t            write_offset;       /**< Write offset for the current operation. */
    uint32_t            sd_size;            /**< Size of the SoftDevice. */

    dfu_progress_t      progress;           /**< Current DFU progress. */

    uint32_t            enter_buttonless_dfu;
    uint8_t             init_command[INIT_COMMAND_MAX_SIZE];  /**< Buffer for storing the init command. */

    uint32_t            boot_validation_crc;
    boot_validation_t   boot_validation_softdevice;
    boot_validation_t   boot_validation_app;
    boot_validation_t   boot_validation_bootloader;

    nrf_dfu_peer_data_t peer_data;          /**< Not included in calculated CRC. */
    nrf_dfu_adv_name_t  adv_name;           /**< Not included in calculated CRC. */
} nrf_dfu_settings_t;

#pragma pack() // revert pack settings

#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_TYPES_H__

/** @} */
