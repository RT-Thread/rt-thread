/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
 * @ingroup  sdk_nrf_dfu
 */

#ifndef NRF_DFU_TYPES_H__
#define NRF_DFU_TYPES_H__

#include <stdint.h>
#include <stddef.h>

#include "nrf.h"
#include "nrf_mbr.h"
#ifdef SOFTDEVICE_PRESENT
#include "nrf_sdm.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOFTDEVICE_PRESENT)

#include "nrf_sdm.h"

/** @brief Start address of the SoftDevice (excluding the area for the MBR).
 */
#define SOFTDEVICE_REGION_START             MBR_SIZE


#ifndef CODE_REGION_1_START
#define CODE_REGION_1_START                 SD_SIZE_GET(MBR_SIZE)
#endif


#else

#ifndef CODE_REGION_1_START
#define CODE_REGION_1_START                 MBR_SIZE
#endif

#endif


#define INIT_COMMAND_MAX_SIZE       256     /**< Maximum size of the init command stored in dfu_settings. */

/** @brief  Size of a flash codepage. This value is used for calculating the size of the reserved
 *          flash space in the bootloader region. It is checked against NRF_UICR->CODEPAGESIZE
 *          at run time to ensure that the region is correct.
 */
#if defined(NRF51)
    #define CODE_PAGE_SIZE            (PAGE_SIZE_IN_WORDS * sizeof(uint32_t))
#elif defined(NRF52) || defined(NRF52840_XXAA)
    #define CODE_PAGE_SIZE            (MBR_PAGE_SIZE_IN_WORDS * sizeof(uint32_t))
#else
    #error "Architecture not set."
#endif


/** @brief  Maximum size of a data object.*/
#if defined( NRF51 )
    #define DATA_OBJECT_MAX_SIZE           (CODE_PAGE_SIZE * 4)
#elif defined( NRF52_SERIES ) || defined ( __SDK_DOXYGEN__ )
    #define DATA_OBJECT_MAX_SIZE           (CODE_PAGE_SIZE)
#else
    #error "Architecture not set."
#endif

/** @brief  Page location of the bootloader settings address.
 */

#if defined ( NRF51 )
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x0003FC00UL)
#elif defined( NRF52832_XXAA )
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x0007F000UL)
#elif defined( NRF52840_XXAA )
    #define BOOTLOADER_SETTINGS_ADDRESS     (0x000FF000UL)
#else
    #error No valid target set for BOOTLOADER_SETTINGS_ADDRESS.
#endif



#if defined(NRF52832_XXAA)

/**
 * @brief   MBR parameters page in UICR.
 *
 * Register location in UICR where the page address of the MBR parameters page is stored (only used by the nRF52 MBR).
 *
 * @note If the value at the given location is 0xFFFFFFFF, no MBR parameters page is set.
 */
#define NRF_UICR_MBR_PARAMS_PAGE_ADDRESS    (NRF_UICR_BASE + 0x18)


/** @brief Page location of the MBR parameters page address.
 *
 */
#define NRF_MBR_PARAMS_PAGE_ADDRESS         (0x0007E000UL)

#endif

#if defined(NRF52840_XXAA)

/**
 * @brief   MBR parameters page in UICR.
 *
 * Register location in UICR where the page address of the MBR parameters page is stored (only used by the nRF52 MBR).
 *
 * @note If the value at the given location is 0xFFFFFFFF, no MBR parameters page is set.
 */
#define NRF_UICR_MBR_PARAMS_PAGE_ADDRESS     (NRF_UICR_BASE + 0x18)


/** @brief Page location of the MBR parameters page address.
 *
 */
#define NRF_MBR_PARAMS_PAGE_ADDRESS         (0x000FE000UL)

#endif


/** @brief  Size of the flash space reserved for application data.
 */
#ifndef DFU_APP_DATA_RESERVED
#define DFU_APP_DATA_RESERVED               CODE_PAGE_SIZE * 3
#endif


/** @brief Total size of the region between the SoftDevice and the bootloader.
 */
#define DFU_REGION_TOTAL_SIZE               ((* (uint32_t *)NRF_UICR_BOOTLOADER_START_ADDRESS) - CODE_REGION_1_START)

#ifdef SOFTDEVICE_PRESENT
/** @brief Start address of the SoftDevice (excluding the area for the MBR).
 */
#define SOFTDEVICE_REGION_START             MBR_SIZE


/** @brief Size of the Code Region 0, found in the UICR.CLEN0 register.
 *
 * @details This value is identical to the start of Code Region 1. This value is used for
 *          compilation safety, because the linker will fail if the application expands
 *          into the bootloader. At run time, the bootloader uses the value found in UICR.CLEN0.
 */

#ifndef CODE_REGION_1_START
#define CODE_REGION_1_START                 SD_SIZE_GET(MBR_SIZE)
#endif
#else
#ifndef CODE_REGION_1_START
#define CODE_REGION_1_START                 MBR_SIZE
#endif
#endif

#define NRF_DFU_CURRENT_BANK_0 0x00
#define NRF_DFU_CURRENT_BANK_1 0x01

#define NRF_DFU_BANK_LAYOUT_DUAL   0x00
#define NRF_DFU_BANK_LAYOUT_SINGLE 0x01


/** @brief DFU bank state codes.
 *
 * @details The DFU bank state indicates the content of a bank:
 *          A valid image of a certain type or an invalid image.
 */

#define NRF_DFU_BANK_INVALID     0x00 /**< Invalid image. */
#define NRF_DFU_BANK_VALID_APP   0x01 /**< Valid application. */
#define NRF_DFU_BANK_VALID_SD    0xA5 /**< Valid SoftDevice. */
#define NRF_DFU_BANK_VALID_BL    0xAA /**< Valid bootloader. */
#define NRF_DFU_BANK_VALID_SD_BL 0xAC /**< Valid SoftDevice and bootloader. */


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
 */
typedef struct
{
    uint32_t command_size;              /**< The size of the current init command stored in the DFU settings. */
    uint32_t command_offset;            /**< The offset of the currently received init command data. The offset will increase as the init command is received. */
    uint32_t command_crc;               /**< The calculated CRC of the init command (calculated after the transfer is completed). */

    uint32_t data_object_size;          /**< The size of the last object created. Note that this size is not the size of the whole firmware image.*/

    uint32_t firmware_image_crc;        /**< CRC value of the current firmware (continuously calculated as data is received). */
    uint32_t firmware_image_crc_last;   /**< The CRC of the last executed object. */
    uint32_t firmware_image_offset;     /**< The offset of the current firmware image being transferred. Note that this offset is the offset in the entire firmware image and not only the current object. */
    uint32_t firmware_image_offset_last;/**< The offset of the last executed object from the start of the firmware image. */
} dfu_progress_t;


/**@brief DFU settings for application and bank data.
 */
typedef struct
{
    uint32_t            crc;                /**< CRC for the stored DFU settings, not including the CRC itself. If 0xFFFFFFF, the CRC has never been calculated. */
    uint32_t            settings_version;   /**< Version of the currect dfu settings struct layout.*/
    uint32_t            app_version;        /**< Version of the last stored application. */
    uint32_t            bootloader_version; /**< Version of the last stored bootloader. */

    uint32_t            bank_layout;        /**< Bank layout: single bank or dual bank. This value can change. */
    uint32_t            bank_current;       /**< The bank that is currently used. */

    nrf_dfu_bank_t      bank_0;             /**< Bank 0. */
    nrf_dfu_bank_t      bank_1;             /**< Bank 1. */

    uint32_t            write_offset;       /**< Write offset for the current operation. */
    uint32_t            sd_size;            /**< SoftDevice size (if combined BL and SD). */

    dfu_progress_t      progress;           /**< Current DFU progress. */

    uint32_t            enter_buttonless_dfu;
    uint8_t             init_command[INIT_COMMAND_MAX_SIZE];  /**< Buffer for storing the init command. */
} nrf_dfu_settings_t;
#pragma pack() // revert pack settings


#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_TYPES_H__

/** @} */
