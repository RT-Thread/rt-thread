/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

/** @file
 *
 * @brief TFTP DFU Example - Background DFU transport implementation.
 *
 */
#include "tftp_dfu.h"

#include "background_dfu_transport.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "app_timer.h"
#include "background_dfu_block.h"
#include "background_dfu_transport.h"
#include "cJSON.h"
#include "cJSON_iot_hooks.h"
#include "crc16.h"
#include "iot_file_static.h"
#include "iot_tftp.h"
#include "nrf.h"
#include "nrf_assert.h"
#include "nrf_delay.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_settings.h"
#include "nrf_dfu_utils.h"
#include "nrf_log_ctrl.h"

#define NRF_LOG_LEVEL 4
#define NRF_LOG_MODULE_NAME TFTP_DFU
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define MAX_LENGTH_FILENAME 32                                                                      /**< Maximum length of the filename. */
#define MAX_CONFIG_SIZE     1024                                                                    /**< Maximum DFU of the config size. */

#define CONFIG_APP_KEY                  "app"
#define CONFIG_SD_KEY                   "sd"
#define CONFIG_APPSD_KEY                "appsd"
#define CONFIG_BL_KEY                   "bl"
#define CONFIG_PATH_KEY                 "p"
#define CONFIG_INIT_PATH_KEY            "i"
#define CONFIG_SIZE_KEY                 "s"
#define CONFIG_ID_KEY                   "id"
#define CONFIG_INIT_SIZE_KEY            "is"
#define CONFIG_INIT_ID_KEY              "iid"

#define APP_TFTP_BLOCK_SIZE             512                                                         /**< Maximum or negotiated size of data block. */
#define APP_TFTP_RETRANSMISSION_TIME    3                                                           /**< Number of milliseconds between retransmissions. */

#define BOOTLOADER_REGION_START         0x0007D000                                                  /**< This field should correspond to start address of the bootloader, found in UICR.RESERVED, 0x10001014, register.
                                                                                                         This value is used for sanity check, so the bootloader will fail immediately if this value differs from runtime value.
                                                                                                         The value is used to determine max application size for updating. */

#define TFTP_SOFTDEVICE_UPGRADE_SUPPORT false                                                       /**< Upgrade of softdevice or bootloader is not supported with current version of Background DFU module. */

/** The device info offset can be modified to place the device info settings at a different location.
  * If the customer reserved UICR location is used for other application specific data, the offset
  * must be updated to avoid collision with that data.:
  */
/** [DFU UICR DEV offset] */
#define UICR_CUSTOMER_DEVICE_INFO_OFFSET    0x0                                                     /**< Device info offset inside the customer UICR reserved area. Customers may change this value to place the device information in a user-preferred location. */
/** [DFU UICR DEV offset] */
#define UICR_CUSTOMER_RESERVED_OFFSET       0x80                                                    /**< Customer reserved area in the UICR. The area from UICR + 0x80 is reserved for customer usage. */
#define DFU_DEVICE_INFO_BASE                (NRF_UICR_BASE + \
                                             UICR_CUSTOMER_RESERVED_OFFSET + \
                                             UICR_CUSTOMER_DEVICE_INFO_OFFSET)                      /**< The device information base address inside of UICR. */
#define DFU_DEVICE_INFO                     ((dfu_device_info_t *)DFU_DEVICE_INFO_BASE)             /**< The memory mapped structure for device information data. */


/**@brief Structure holding basic device information settings.
 */
typedef struct
{
    uint16_t device_type;                                                                           /**< Device type (2 bytes), for example Heart Rate. This number must be defined by the customer before production. It can be located in UICR or FICR. */
    uint16_t device_rev;                                                                            /**< Device revision (2 bytes), for example major revision 1, minor revision 0. This number must be defined by the customer before production. It can be located in UICR or FICR. */
} dfu_device_info_t;

/**@brief Description of single block of firmware. */
typedef struct
{
    uint32_t size;                           /**< Size of firmware block. */
    uint32_t crc;                            /**< CRC of firmware block. Set to 0 if no checksum checking is needed. */
    uint32_t init_size;                      /**< Size of init file. */
    uint32_t init_crc;                       /**< CRC of init file. */
} iot_dfu_firmware_block_t;


/**@brief Description of the new firmware that has been written into flash memory. */
typedef struct
{
    iot_dfu_firmware_block_t application;    /**< Description of Application block in firmware image. */
    iot_dfu_firmware_block_t softdevice;     /**< Description of SoftDevice block in firmware image. */
    iot_dfu_firmware_block_t bootloader;     /**< Description of Bootloader block in firmware image. */
} iot_dfu_firmware_desc_t;

/**@brief Type of image being updated by the DFU module. */
typedef enum
{
    TFTP_DFU_IMAGE_TYPE_APPLICATION,       /**< DFU updates application. */
    TFTP_DFU_IMAGE_TYPE_SOFTDEVICE,        /**< DFU updates softdevice and application. */
    TFTP_DFU_IMAGE_TYPE_BOOTLOADER,        /**< DFU updates bootloader. */
} tftp_dfu_image_type_t;

/**@brief Static data used by TFTP DFU module. */
typedef struct
{
    iot_tftp_t              tftp;                                                                  /**< TFTP instance. */
    char                    resource_path[MAX_LENGTH_FILENAME];                                    /**< Path of remote resource to get. */
    uint32_t                block_number;                                                          /**< Number of block that will be passed to background DFU module. */
    uint8_t                 block[DEFAULT_BLOCK_SIZE];                                             /**< Buffer for parts of blocks to pass to background DFU module. */
    uint16_t                block_size;                                                            /**< Size of data in block buffer. */
    tftp_dfu_image_type_t   image_type;                                                            /**< Type of image that is currently updated. */
    iot_file_t              config_file;                                                           /**< Pointer to the file used for config of DFU. */
    uint8_t                 config_mem[MAX_CONFIG_SIZE];                                           /**< Static memory for configuration file. */
    cJSON                 * p_config_json;                                                         /**< Pointer of cJSON instance. */
    iot_dfu_firmware_desc_t firmware_desc;                                                         /**< Details from configuration file. */
} tftp_dfu_context_t;

static background_dfu_context_t m_dfu_ctx;                                                         /**< Background DFU context. */
static tftp_dfu_context_t       m_tftp_dfu_ctx;                                                    /**< TFTP DFU context. */

/***************************************************************************************************
 * @section Common operations
 **************************************************************************************************/

/**@brief Set resource path to trigger (config) file. */
static void trigger_path_set(void)
{
    int retval = snprintf(m_tftp_dfu_ctx.resource_path,
                          sizeof(m_tftp_dfu_ctx.resource_path),
                          "/dfu/c/%d/%d",
                          DFU_DEVICE_INFO->device_type,
                          DFU_DEVICE_INFO->device_rev);
    if (retval < 0) {
        NRF_LOG_ERROR("Failed to set path using snprintf, retval: %d", retval);
    }
}

/**@brief Function for reading binary path from JSON configuration.
 *
 * @param[out] p_dst_str Pointer to memory, where path should be stored.
 * @param[in]  p_key     Key inside JSON configuration file, describing firmware.
 *
 * @return    NRF_SUCCESS if path found and stored in p_dst_str, otherwise error code.
 */
static uint32_t get_path(char * p_dst_str, const char * p_key)
{
    cJSON * p_cursor;

    if ((m_tftp_dfu_ctx.p_config_json == NULL) || (p_dst_str == NULL))
    {
        NRF_LOG_ERROR("Invalid parameters");
        return NRF_ERROR_INVALID_PARAM;
    }

    p_cursor = cJSON_GetObjectItem(m_tftp_dfu_ctx.p_config_json, CONFIG_PATH_KEY);
    if (p_cursor != NULL)
    {
        p_cursor = cJSON_GetObjectItem(p_cursor, (const char *)p_key);
        if ((p_cursor != NULL) && (p_cursor->type == cJSON_String))
        {
            memcpy(p_dst_str, p_cursor->valuestring, strlen(p_cursor->valuestring));
        }
        else
        {
            return NRF_ERROR_INVALID_PARAM;
        }
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    return NRF_SUCCESS;
}

/**@brief Function for reading init binary path from JSON configuration.
 *
 * @param[out] p_dst_str Pointer to memory, where path should be stored.
 * @param[in]  p_key     Key inside JSON configuration file, describing firmware.
 *
 * @return    NRF_SUCCESS if path found and stored in p_dst_str, otherwise error code.
 */
static uint32_t get_init_path(char * p_dst_str, const char * p_key)
{
    cJSON * p_cursor;

    if ((m_tftp_dfu_ctx.p_config_json == NULL) || (p_dst_str == NULL))
    {
        NRF_LOG_ERROR("Invalid parameters");
        return NRF_ERROR_INVALID_PARAM;
    }

    p_cursor = cJSON_GetObjectItem(m_tftp_dfu_ctx.p_config_json, CONFIG_INIT_PATH_KEY);
    if (p_cursor != NULL)
    {
        p_cursor = cJSON_GetObjectItem(p_cursor, (const char *)p_key);
        if ((p_cursor != NULL) && (p_cursor->type == cJSON_String))
        {
            memcpy(p_dst_str, p_cursor->valuestring, strlen(p_cursor->valuestring));
        }
        else
        {
            return NRF_ERROR_INVALID_PARAM;
        }
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    return NRF_SUCCESS;
}

/**@brief Function for parsing JSON file to get details of an application.
 *
 * @param[in]  p_key   Key inside JSON configuration file, describing firmware.
 * @param[out] p_block Pointer to structure containing description of single block of firmware.
 *
 * @returns NRF_SUCCESS if correctly parsed data. Otherwise an error code indicating failure reason.
 */
static uint32_t details_parse(const char * p_key, iot_dfu_firmware_block_t * p_block)
{
    cJSON * p_cursor;
    cJSON * p_cursor_back;

    // Clear output parameters.
    memset(p_block, 0, sizeof(*p_block));

    if (m_tftp_dfu_ctx.p_config_json == NULL)
    {
        NRF_LOG_ERROR("Invalid JSON file");
        return NRF_ERROR_INVALID_DATA;
    }

    p_cursor = cJSON_GetObjectItem(m_tftp_dfu_ctx.p_config_json, (const char *)p_key);
    if (p_cursor != NULL)
    {
        p_cursor_back = p_cursor;
        p_cursor = cJSON_GetObjectItem(p_cursor, CONFIG_ID_KEY);
        if (p_cursor != NULL)
        {
            if (p_cursor->type != cJSON_Number)
            {
                return NRF_ERROR_INVALID_DATA;
            }

            p_block->crc = p_cursor->valueint;
        }
        else
        {
            NRF_LOG_ERROR("No binary ID inside JSON.");
            return NRF_ERROR_INVALID_DATA;
        }

        p_cursor = p_cursor_back;
        p_cursor = cJSON_GetObjectItem(p_cursor, CONFIG_INIT_SIZE_KEY);
        if (p_cursor != NULL)
        {
            if (p_cursor->type != cJSON_Number)
            {
                return NRF_ERROR_INVALID_DATA;
            }

            p_block->init_size = p_cursor->valueint;
        }
        else
        {
            NRF_LOG_ERROR("No init SIZE inside JSON.");
            return NRF_ERROR_INVALID_DATA;
        }

        p_cursor = p_cursor_back;
        p_cursor = cJSON_GetObjectItem(p_cursor, CONFIG_INIT_ID_KEY);
        if (p_cursor != NULL)
        {
            if (p_cursor->type != cJSON_Number)
            {
                return NRF_ERROR_INVALID_DATA;
            }

            p_block->init_crc = p_cursor->valueint;
        }
        else
        {
            NRF_LOG_ERROR("No init ID inside JSON.");
            return NRF_ERROR_INVALID_DATA;
        }

        p_cursor = p_cursor_back;
        p_cursor = cJSON_GetObjectItem(p_cursor, CONFIG_SIZE_KEY);
        if (p_cursor != NULL)
        {
            if ((p_cursor->type != cJSON_Number) || (p_cursor->valueint == 0))
            {
                return NRF_ERROR_INVALID_DATA;
            }

            p_block->size = p_cursor->valueint;
        }
        else
        {
            NRF_LOG_ERROR("No binary SIZE inside JSON.");
            return NRF_ERROR_INVALID_DATA;
        }
    }
    else
    {
        NRF_LOG_ERROR("No binary KEY inside JSON.");
        return NRF_ERROR_INVALID_DATA;
    }

    return NRF_SUCCESS;
}


/**@brief Function for parsing and processing config file.
 *
 * @param[out] p_dfu_firmware_desc Details of available firmware images (size and CRC)
 * @param[out] p_filename          Remote path to init file that should be downloaded in DFU process
 *
 * @return NRF_SUCCESS If config file is valid. Otherwise an error code indicating failure reason.
 */
static uint32_t app_dfu_config_process(iot_dfu_firmware_desc_t * p_dfu_firmware_desc,
                                       char                    * p_filename)
{
    uint32_t                 err_code = NRF_SUCCESS;
    iot_dfu_firmware_block_t app;
#if TFTP_SOFTDEVICE_UPGRADE_SUPPORT
    iot_dfu_firmware_block_t sd;
    iot_dfu_firmware_block_t bl;
#endif // TFTP_SOFTDEVICE_UPGRADE_SUPPORT
    bool                     app_present = false;
#if TFTP_SOFTDEVICE_UPGRADE_SUPPORT
    bool                     sd_present  = false;
    bool                     bl_present  = false;
#endif // TFTP_SOFTDEVICE_UPGRADE_SUPPORT

    // Clear global parameters before parsing a new one.
    memset(p_filename, 0, MAX_LENGTH_FILENAME);

    m_tftp_dfu_ctx.p_config_json = cJSON_Parse((const char *)m_tftp_dfu_ctx.config_mem);
    if (m_tftp_dfu_ctx.p_config_json == NULL)
    {
        NRF_LOG_ERROR("JSON parse failed.");
        return NRF_ERROR_INVALID_DATA;
    }

#if TFTP_SOFTDEVICE_UPGRADE_SUPPORT
    if (details_parse(CONFIG_SD_KEY, &sd) == NRF_SUCCESS)
    {
        sd_present = true;
    }

    if (details_parse(CONFIG_BL_KEY, &bl) == NRF_SUCCESS)
    {
        bl_present = true;
    }
#endif // TFTP_SOFTDEVICE_UPGRADE_SUPPORT

    if (details_parse(CONFIG_APP_KEY, &app) == NRF_SUCCESS)
    {
        app_present = true;
    }

#if TFTP_SOFTDEVICE_UPGRADE_SUPPORT
    // Background DFU does not support SoftDevice or bootloader update yet.
    if ((sd_present) && (app_present))
    {
        NRF_LOG_INFO("Update Softdevice with Application.");
        m_tftp_dfu_ctx.image_type = TFTP_DFU_IMAGE_TYPE_SOFTDEVICE;
    }
    else if (bl_present)
    {
        NRF_LOG_INFO("Update Bootloader.");
        m_tftp_dfu_ctx.image_type = TFTP_DFU_IMAGE_TYPE_BOOTLOADER;
    }
    else
#endif // TFTP_SOFTDEVICE_UPGRADE_SUPPORT
    {
        if (app_present)
        {
            NRF_LOG_INFO("Update Application only.");
            m_tftp_dfu_ctx.image_type = TFTP_DFU_IMAGE_TYPE_APPLICATION;
        }
        else
        {
            // This example application does not implement SoftDevice with Bootloader update
            NRF_LOG_INFO("Device firmware up to date.");
            err_code = NRF_ERROR_NOT_FOUND;
        }
    }

    if (err_code == NRF_SUCCESS)
    {
        switch (m_tftp_dfu_ctx.image_type)
        {
            case TFTP_DFU_IMAGE_TYPE_APPLICATION:
                err_code = get_init_path(p_filename, CONFIG_APP_KEY);
                if (err_code == NRF_SUCCESS)
                {
                    p_dfu_firmware_desc->application = app;
                }

                break;

#if TFTP_SOFTDEVICE_UPGRADE_SUPPORT
            case TFTP_DFU_IMAGE_TYPE_BOOTLOADER:
                err_code = get_init_path(p_filename, CONFIG_BL_KEY);
                if (err_code == NRF_SUCCESS)
                {
                    p_dfu_firmware_desc->bootloader = bl;
                }

                break;

            case TFTP_DFU_IMAGE_TYPE_SOFTDEVICE:
                err_code = get_init_path(p_filename, CONFIG_APPSD_KEY);
                if (err_code == NRF_SUCCESS)
                {
                    p_dfu_firmware_desc->softdevice  = sd;
                    p_dfu_firmware_desc->application = app;
                }

                break;
#endif // TFTP_SOFTDEVICE_UPGRADE_SUPPORT

            default:
                ASSERT(false);
        }
    }

    if (p_filename[0] == '\0')
    {
        NRF_LOG_ERROR("File name has not be found.");
        err_code = NRF_ERROR_INVALID_PARAM;
    }

    cJSON_Delete(m_tftp_dfu_ctx.p_config_json);

    return err_code;
}

/** @brief Set resource path to point to firmware binary file.
 *
 * @param [out]  p_filename  Pointer to resource path.
 *
 * @return NRF_SUCCESS if setting firmware path succeeded or error code indicating failure reason.
 */
static uint32_t set_firmware_path(char * p_filename)
{
    uint32_t err_code = NRF_SUCCESS;

    m_tftp_dfu_ctx.p_config_json = cJSON_Parse((const char *)m_tftp_dfu_ctx.config_mem);
    if (m_tftp_dfu_ctx.p_config_json == NULL)
    {
        NRF_LOG_ERROR("JSON parse failed.");
        return NRF_ERROR_INVALID_DATA;
    }

    switch (m_tftp_dfu_ctx.image_type)
    {
        case TFTP_DFU_IMAGE_TYPE_APPLICATION:
            err_code = get_path(p_filename, CONFIG_APP_KEY);
            break;

        case TFTP_DFU_IMAGE_TYPE_BOOTLOADER:
            err_code = get_path(p_filename, CONFIG_BL_KEY);
            break;

        case TFTP_DFU_IMAGE_TYPE_SOFTDEVICE:
            err_code = get_path(p_filename, CONFIG_APPSD_KEY);
            break;

        default:
            ASSERT(false);
    }

    if (p_filename[0] == '\0')
    {
        NRF_LOG_ERROR("File name has not be found.");
        err_code = NRF_ERROR_INVALID_PARAM;
    }

    cJSON_Delete(m_tftp_dfu_ctx.p_config_json);

    return err_code;
}

/** @brief Send download request to the TFTP server.
 *
 * @param[in]  p_file  Pointer to file instance used to store file. May be NULL if file is not
 *                     stored by TFTP module.
 */
static void send_request(iot_file_t * p_file)
{
    uint32_t                err_code;
    iot_tftp_trans_params_t trans_params;

    trans_params.block_size = APP_TFTP_BLOCK_SIZE;
    trans_params.next_retr  = APP_TFTP_RETRANSMISSION_TIME;

    err_code = iot_tftp_set_params(&m_tftp_dfu_ctx.tftp, &trans_params);
    ASSERT(err_code == NRF_SUCCESS);

    err_code = iot_tftp_get(&m_tftp_dfu_ctx.tftp, p_file, m_tftp_dfu_ctx.resource_path);
    ASSERT(err_code == NRF_SUCCESS);

    UNUSED_VARIABLE(err_code);
}

/***************************************************************************************************
 * @section TFTP handler
 **************************************************************************************************/

/**
 * @brief Process retrieved config file
 *
 * @param[in]  p_file  Pointer to retrieved config file.
 */
static void config_file_retrieved(iot_file_t * p_file)
{
    uint32_t                   err_code;
    background_dfu_trigger_t   trigger;
    iot_dfu_firmware_block_t * p_firmware_block = NULL;

    NRF_LOG_INFO("Config file successfully downloaded.");

    m_tftp_dfu_ctx.config_mem[p_file->file_size] = 0;
    memset(&m_tftp_dfu_ctx.firmware_desc, 0, sizeof(m_tftp_dfu_ctx.firmware_desc));

    err_code = app_dfu_config_process(&m_tftp_dfu_ctx.firmware_desc, m_tftp_dfu_ctx.resource_path);

    if (err_code == NRF_SUCCESS)
    {
        NRF_LOG_INFO("New sofware available. Starting downloading procedure.");

        switch(m_tftp_dfu_ctx.image_type)
        {
            case TFTP_DFU_IMAGE_TYPE_APPLICATION:
                p_firmware_block = &m_tftp_dfu_ctx.firmware_desc.application;
                break;

            case TFTP_DFU_IMAGE_TYPE_BOOTLOADER:
                p_firmware_block = &m_tftp_dfu_ctx.firmware_desc.bootloader;
                break;

            case TFTP_DFU_IMAGE_TYPE_SOFTDEVICE:
                p_firmware_block = &m_tftp_dfu_ctx.firmware_desc.softdevice;
                break;
        }

        memset(&trigger, 0, sizeof(trigger));
        trigger.init_length  = uint32_big_decode((const uint8_t *)&p_firmware_block->init_size);
        trigger.init_crc     = uint32_big_decode((const uint8_t *)&p_firmware_block->init_crc);
        trigger.image_length = uint32_big_decode((const uint8_t *)&p_firmware_block->size);
        trigger.image_crc    = uint32_big_decode((const uint8_t *)&p_firmware_block->crc);

        if (background_dfu_validate_trigger(&m_dfu_ctx, (uint8_t *)&trigger, sizeof(trigger)))
        {
            if (!background_dfu_process_trigger(&m_dfu_ctx, (uint8_t *)&trigger, sizeof(trigger)))
            {
                NRF_LOG_ERROR("Error in TFTP background_dfu_process_trigger");
            }

            if (m_dfu_ctx.dfu_state == BACKGROUND_DFU_IDLE)
            {
                // State in DFU_IDLE, nothing to download.
                err_code = iot_tftp_uninit(&m_tftp_dfu_ctx.tftp);
                if (err_code != NRF_SUCCESS)
                {
                    NRF_LOG_ERROR("Error in TFTP uninit (%d)", err_code);
                }
            }
        }
    }
    else
    {
        NRF_LOG_INFO("No new sofware available or incorrect JSON file.");
    }
}

/**
 * @brief Pass block of retrieved data to background DFU module.
 *
 * @param[in]  p_block  Pointer to block of retrieved data.
 */
static void process_block(uint8_t * p_block)
{
    background_dfu_block_t        block;
    background_dfu_block_result_t result;

    block.number    = m_tftp_dfu_ctx.block_number;
    block.size      = DEFAULT_BLOCK_SIZE;
    block.p_payload = p_block;

    m_tftp_dfu_ctx.block_number++;

    result = background_dfu_process_block(&m_dfu_ctx, &block);
    if (result != BACKGROUND_DFU_BLOCK_SUCCESS)
    {
        NRF_LOG_ERROR("Error in TFTP background_dfu_process_block (%d)", result);
    }
}

/**
 * @brief Process retrieved data chunk.
 *
 * Split retrieved data to blocks of DEFAULT_BLOCK_SIZE bytes and pass to DFU module.
 *
 * @param[in]  p_data_received  Pointer to structure describing received data chunk.
 */
static void data_chunk_retrieved(iot_tftp_evt_data_received_t * p_data_received)
{
    uint16_t processed_bytes = 0;

    // Process part of block from previous chunk
    if (m_tftp_dfu_ctx.block_size)
    {
        uint16_t first_block_missing_size = DEFAULT_BLOCK_SIZE - m_tftp_dfu_ctx.block_size;

        if (p_data_received->size < first_block_missing_size)
        {
            first_block_missing_size = p_data_received->size;
        }

        memcpy(&m_tftp_dfu_ctx.block[m_tftp_dfu_ctx.block_size],
               p_data_received->p_data,
               first_block_missing_size);

        process_block(m_tftp_dfu_ctx.block);

        processed_bytes = first_block_missing_size;
    }

    // Process received chunks
    while (p_data_received->size - processed_bytes >= DEFAULT_BLOCK_SIZE)
    {
        process_block(&p_data_received->p_data[processed_bytes]);
        processed_bytes += DEFAULT_BLOCK_SIZE;
    }

    m_tftp_dfu_ctx.block_size = p_data_received->size - processed_bytes;

    // Leave not processed data
    if (p_data_received->size > processed_bytes)
    {
        memcpy(m_tftp_dfu_ctx.block,
               &p_data_received->p_data[processed_bytes],
               m_tftp_dfu_ctx.block_size);
    }
}

/**
 * @brief Process data left from previous chunk.
 */
static void preserved_block_process(void)
{
    process_block(m_tftp_dfu_ctx.block);
    m_tftp_dfu_ctx.block_size = 0;
}

/**
 * @brief Handler of TFTP events.
 */
static void tftp_dfu_tftp_handler(iot_tftp_t * p_tftp, iot_tftp_evt_t * p_evt)
{
    switch (p_evt->id)
    {
        case IOT_TFTP_EVT_TRANSFER_DATA_RECEIVED:
            switch (m_dfu_ctx.dfu_state)
            {
                case BACKGROUND_DFU_DOWNLOAD_TRIG:
                    break;

                case BACKGROUND_DFU_DOWNLOAD_INIT_CMD:
                case BACKGROUND_DFU_DOWNLOAD_FIRMWARE:
                    data_chunk_retrieved(&p_evt->param.data_received);
                    break;

                default:
                    ASSERT(false);
                    break;
            }
            break;

        case IOT_TFTP_EVT_TRANSFER_GET_COMPLETE:
            switch (m_dfu_ctx.dfu_state)
            {
                case BACKGROUND_DFU_DOWNLOAD_TRIG:
                    config_file_retrieved(p_evt->p_file);
                    break;

                case BACKGROUND_DFU_DOWNLOAD_INIT_CMD:
                case BACKGROUND_DFU_DOWNLOAD_FIRMWARE:
                    preserved_block_process();
                    break;

                default:
                    ASSERT(false);
                    break;
            }
            break;

        case IOT_TFTP_EVT_ERROR:
            background_dfu_handle_error();
            break;

        default:
            ASSERT(false);
            break;
    }
}

static void dfu_observer(nrf_dfu_evt_type_t evt_type)
{
    switch (evt_type)
    {
        case NRF_DFU_EVT_DFU_COMPLETED:
            NRF_LOG_FINAL_FLUSH();

#if NRF_MODULE_ENABLED(NRF_LOG_BACKEND_RTT)
            // To allow the buffer to be flushed by the host.
            nrf_delay_ms(100);
#endif

            NVIC_SystemReset();
            break;

        default:
            break;
    }
}


/***************************************************************************************************
 * @section Private API
 **************************************************************************************************/

void background_dfu_transport_block_request_send(background_dfu_context_t        * p_dfu_ctx,
                                                 background_dfu_request_bitmap_t * p_req_bmp)
{
    // Intentionally empty: multicast DFU not implemented.
}

void background_dfu_transport_send_request(background_dfu_context_t * p_dfu_ctx)
{
    switch (m_dfu_ctx.dfu_state)
    {
        case BACKGROUND_DFU_DOWNLOAD_TRIG:
            send_request(&m_tftp_dfu_ctx.config_file);
            break;

        default:
            // In other states download operation is triggered by state_update() notification.
            break;
    }
}

void background_dfu_transport_state_update(background_dfu_context_t * p_dfu_ctx)
{
    switch (p_dfu_ctx->dfu_state)
    {
        case BACKGROUND_DFU_DOWNLOAD_TRIG:
            trigger_path_set();
            break;

        case BACKGROUND_DFU_DOWNLOAD_INIT_CMD:
            m_tftp_dfu_ctx.block_number = 0;
            m_tftp_dfu_ctx.block_size   = 0;
            send_request(NULL);
            break;

        case BACKGROUND_DFU_DOWNLOAD_FIRMWARE:
            m_tftp_dfu_ctx.block_number = 0;
            m_tftp_dfu_ctx.block_size   = 0;
            UNUSED_RETURN_VALUE(set_firmware_path(m_tftp_dfu_ctx.resource_path));
            send_request(NULL);
            break;

        case BACKGROUND_DFU_WAIT_FOR_RESET:
        case BACKGROUND_DFU_IDLE:
            // Do nothing.
            break;

        default:
            NRF_LOG_WARNING("Unhandled state in background_dfu_transport_state_update (s: %s).",
                    (uint32_t)background_dfu_state_to_string(p_dfu_ctx->dfu_state));
    }
}

uint32_t background_dfu_random(void)
{
    // Intentionally empty: multicast DFU not implemented.
    return 0;
}

/***************************************************************************************************
 * @section Public API
 **************************************************************************************************/

uint32_t tftp_dfu_init(void)
{
    uint32_t err_code = NRF_SUCCESS;

    memset(&m_tftp_dfu_ctx, 0, sizeof(m_tftp_dfu_ctx));

    err_code = nrf_dfu_settings_init(true);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = nrf_dfu_req_handler_init(dfu_observer);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    background_dfu_state_init(&m_dfu_ctx);

    cJSON_Init();

    // Initialize file static instance.
    IOT_FILE_STATIC_INIT(&m_tftp_dfu_ctx.config_file,
                         m_tftp_dfu_ctx.resource_path,
                         m_tftp_dfu_ctx.config_mem,
                         MAX_CONFIG_SIZE);

    return err_code;
}

uint32_t tftp_dfu_trigger(const ipv6_addr_t * p_host_ipv6, uint16_t src_port, uint16_t dst_port)
{
    uint32_t        err_code;
    iot_tftp_init_t tftp_init_params;

    NRF_LOG_INFO("Triggering DFU");

    if (p_host_ipv6 == NULL)
    {
        NRF_LOG_WARNING("NULL IPv6 address");
        return NRF_ERROR_NULL;
    }

    if (m_dfu_ctx.dfu_state != BACKGROUND_DFU_IDLE)
    {
        NRF_LOG_WARNING("Invalid state");
        return NRF_ERROR_INVALID_STATE;
    }

    // Set TFTP configuration
    memset(&tftp_init_params, 0, sizeof(iot_tftp_init_t));
    tftp_init_params.p_ipv6_addr = (ipv6_addr_t *)p_host_ipv6;
    tftp_init_params.src_port    = src_port;
    tftp_init_params.dst_port    = dst_port;
    tftp_init_params.callback    = tftp_dfu_tftp_handler;

    // Initialize instance, bind socket, check parameters.
    err_code = iot_tftp_init(&m_tftp_dfu_ctx.tftp, &tftp_init_params);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Error in TFTP init (%d)", err_code);
        return err_code;
    }

    trigger_path_set();

    // Transition from DFU_IDLE to DFU_DOWNLOAD_TRIG.
    return background_dfu_handle_event(&m_dfu_ctx, BACKGROUND_DFU_EVENT_TRANSFER_COMPLETE);
}

void background_dfu_handle_error(void)
{
    UNUSED_RETURN_VALUE(iot_tftp_uninit(&m_tftp_dfu_ctx.tftp));
    tftp_dfu_handle_error();
}

__WEAK void tftp_dfu_handle_error(void)
{

}

bool nrf_dfu_button_enter_check(void)
{
    // Dummy function for Keil compilation. This should not be called.
    return false;
}
