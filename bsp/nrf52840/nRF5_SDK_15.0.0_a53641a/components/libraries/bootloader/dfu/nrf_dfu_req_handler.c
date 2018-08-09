/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "nrf_dfu.h"
#include "nrf_dfu_types.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_handling_error.h"
#include "nrf_dfu_settings.h"
#include "nrf_dfu_utils.h"
#include "nrf_dfu_flash.h"
#include "nrf_fstorage.h"
#include "nrf_bootloader_info.h"
#include "app_util.h"
#include "pb.h"
#include "pb_common.h"
#include "pb_decode.h"
#include "dfu-cc.pb.h"
#include "crc32.h"
#include "app_scheduler.h"
#include "sdk_macros.h"
#include "nrf_crypto.h"
#include "nrf_assert.h"
#include "nrf_dfu_validation.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_req_handler
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define NRF_DFU_PROTOCOL_VERSION    (0x01)


STATIC_ASSERT(DFU_SIGNED_COMMAND_SIZE <= INIT_COMMAND_MAX_SIZE);

static uint32_t m_firmware_start_addr;          /**< Start address of the current firmware image. */
static uint32_t m_firmware_size_req;            /**< The size of the entire firmware image. Defined by the init command. */

static nrf_dfu_observer_t m_observer;


static void on_dfu_complete(nrf_fstorage_evt_t * p_evt)
{
    UNUSED_PARAMETER(p_evt);

    NRF_LOG_DEBUG("All flash operations have completed. DFU completed.");

    m_observer(NRF_DFU_EVT_DFU_COMPLETED);
}


static nrf_dfu_result_t ext_err_code_handle(nrf_dfu_result_t ret_val)
{
    if (ret_val < NRF_DFU_RES_CODE_EXT_ERROR)
    {
        return ret_val;
    }
    else
    {
        nrf_dfu_ext_error_code_t ext_err =
                (nrf_dfu_ext_error_code_t)((uint8_t)ret_val - (uint8_t)NRF_DFU_RES_CODE_EXT_ERROR);
        return ext_error_set(ext_err);
    }
}


static void on_protocol_version_request(nrf_dfu_request_t const * p_req, nrf_dfu_response_t * p_res)
{
    UNUSED_PARAMETER(p_req);
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_PROTOCOL_VERSION");

    if (NRF_DFU_PROTOCOL_VERSION_MSG)
    {
        p_res->protocol.version = NRF_DFU_PROTOCOL_VERSION;
    }
    else
    {
        NRF_LOG_DEBUG("NRF_DFU_OP_PROTOCOL_VERSION disabled.");
        p_res->result = NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED;
    }
}


static void on_hw_version_request(nrf_dfu_request_t const * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_HARDWARE_VERSION");

    p_res->hardware.part    = NRF_FICR->INFO.PART;
    p_res->hardware.variant = NRF_FICR->INFO.VARIANT;

    /* FICR values are in Kilobytes, we report them in bytes. */
    p_res->hardware.memory.ram_size      = NRF_FICR->INFO.RAM   * 1024;
    p_res->hardware.memory.rom_size      = NRF_FICR->INFO.FLASH * 1024;
    p_res->hardware.memory.rom_page_size = NRF_FICR->CODEPAGESIZE;
}


static void on_fw_version_request(nrf_dfu_request_t const * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_FIRMWARE_VERSION");
    NRF_LOG_DEBUG("Firmware image requested: %d", p_req->firmware.image_number);

    if (NRF_DFU_PROTOCOL_FW_VERSION_MSG)
    {
        uint8_t fw_count = 1;

        if (SD_PRESENT)
        {
            fw_count++;
        }

        if (s_dfu_settings.bank_0.bank_code == NRF_DFU_BANK_VALID_APP)
        {
            fw_count++;
        }

        p_res->result = NRF_DFU_RES_CODE_SUCCESS;

        if (p_req->firmware.image_number == 0)
        {
            /* Bootloader is always present and it is always image zero. */
            p_res->firmware.type    = NRF_DFU_FIRMWARE_TYPE_BOOTLOADER;
            p_res->firmware.version = s_dfu_settings.bootloader_version;
            p_res->firmware.addr    = BOOTLOADER_START_ADDR;
            p_res->firmware.len     = BOOTLOADER_SIZE;
        }
        else if ((p_req->firmware.image_number == 1) && SD_PRESENT)
        {
            /* If a SoftDevice is present, it will be firmware image one. */
            p_res->firmware.type    = NRF_DFU_FIRMWARE_TYPE_SOFTDEVICE;
            p_res->firmware.version = SD_VERSION_GET(MBR_SIZE);
            p_res->firmware.addr    = MBR_SIZE;
            p_res->firmware.len     = SD_SIZE_GET(MBR_SIZE);
        }
        else if ((p_req->firmware.image_number < fw_count))
        {
            /* Either there is no SoftDevice and the firmware image requested is one,
             * or there is a SoftDevice and the firmware image requested is two.
             */
            p_res->firmware.type    = NRF_DFU_FIRMWARE_TYPE_APPLICATION;
            p_res->firmware.version = s_dfu_settings.app_version;
            p_res->firmware.addr    = nrf_dfu_app_start_address();
            p_res->firmware.len     = s_dfu_settings.bank_0.image_size;
        }
        else
        {
            NRF_LOG_DEBUG("No such firmware image");
            p_res->firmware.type    = NRF_DFU_FIRMWARE_TYPE_UNKNOWN;
            p_res->firmware.version = 0x00;
            p_res->firmware.addr    = 0x00;
            p_res->firmware.len     = 0x00;
        }
    }
    else
    {
        NRF_LOG_DEBUG("NRF_DFU_OP_FIRMWARE_VERSION disabled.");
        p_res->result        = NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED;
        p_res->firmware.type = NRF_DFU_FIRMWARE_TYPE_UNKNOWN;
    }
}


static void on_ping_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_PING");
    p_res->ping.id = p_req->ping.id;
}


static void on_mtu_get_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_MTU_GET");
    p_res->mtu.size = p_req->mtu.size;
}


static void on_prn_set_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    UNUSED_PARAMETER(p_req);
    UNUSED_PARAMETER(p_res);
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_RECEIPT_NOTIF_SET");
}


static void on_abort_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    UNUSED_PARAMETER(p_req);
    UNUSED_PARAMETER(p_res);
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_ABORT");

    m_observer(NRF_DFU_EVT_DFU_ABORTED);
}


/* Set offset and CRC fields in the response for a 'command' message. */
static void cmd_response_offset_and_crc_set(nrf_dfu_response_t * const p_res)
{
    ASSERT(p_res);

    /* Copy the CRC and offset of the init packet. */
    p_res->crc.offset = s_dfu_settings.progress.command_offset;
    p_res->crc.crc    = s_dfu_settings.progress.command_crc;
}


static void on_cmd_obj_select_request(nrf_dfu_request_t const * p_req, nrf_dfu_response_t * p_res)
{
    UNUSED_PARAMETER(p_req);
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_SELECT (command)");

    p_res->select.max_size = INIT_COMMAND_MAX_SIZE;
    cmd_response_offset_and_crc_set(p_res);
}


static void on_cmd_obj_create_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    ASSERT(p_req);
    ASSERT(p_res);

    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_CREATE (command)");

    m_observer(NRF_DFU_EVT_DFU_STARTED);

    nrf_dfu_result_t ret_val = nrf_dfu_validation_init_cmd_create(p_req->create.object_size);
    p_res->result = ext_err_code_handle(ret_val);
}


static void on_cmd_obj_write_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    ASSERT(p_req);
    ASSERT(p_req->write.p_data);
    ASSERT(p_req->write.len);
    ASSERT(p_res);

    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_WRITE (command)");

    nrf_dfu_result_t ret_val;

    ret_val = nrf_dfu_validation_init_cmd_append(p_req->write.p_data, p_req->write.len);
    p_res->result = ext_err_code_handle(ret_val);

    /* Update response. This is only used when the PRN is triggered and the 'write' message
     * is answered with a CRC message and these field are copied into the response. */
    cmd_response_offset_and_crc_set(p_res);

    /* If a callback to free the request payload buffer was provided, invoke it now. */
    if (p_req->callback.write)
    {
        p_req->callback.write((void*)p_req->write.p_data);
    }
}


static void on_cmd_obj_execute_request(nrf_dfu_request_t const * p_req, nrf_dfu_response_t * p_res)
{
    ASSERT(p_req);
    ASSERT(p_res);

    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_EXECUTE (command)");

    nrf_dfu_result_t ret_val;
    ret_val = nrf_dfu_validation_init_cmd_execute(&m_firmware_start_addr, &m_firmware_size_req);
    p_res->result = ext_err_code_handle(ret_val);

    if (p_res->result == NRF_DFU_RES_CODE_SUCCESS)
    {
        if (nrf_dfu_settings_write(NULL) == NRF_SUCCESS)
        {
            /* Setting DFU to initialized */
            NRF_LOG_DEBUG("Writing valid init command to flash.");
        }
        else
        {
            p_res->result = NRF_DFU_RES_CODE_OPERATION_FAILED;
        }
    }
}


static void on_cmd_obj_crc_request(nrf_dfu_request_t const * p_req, nrf_dfu_response_t * p_res)
{
    UNUSED_PARAMETER(p_req);
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_CRC_GET (command)");

    cmd_response_offset_and_crc_set(p_res);
}


/** @brief Function handling command requests from the transport layer.
 *
 * @param   p_req[in]       Pointer to the structure holding the DFU request.
 * @param   p_res[out]      Pointer to the structure holding the DFU response.
 *
 * @retval NRF_SUCCESS      If the command request was executed successfully.
 *                          Any other error code indicates that the data request
 *                          could not be handled.
 */
static void nrf_dfu_command_req(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    ASSERT(p_req);
    ASSERT(p_res);

    switch (p_req->request)
    {
        case NRF_DFU_OP_OBJECT_CREATE:
        {
            on_cmd_obj_create_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_CRC_GET:
        {
            on_cmd_obj_crc_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            on_cmd_obj_write_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_OBJECT_EXECUTE:
        {
            on_cmd_obj_execute_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_OBJECT_SELECT:
        {
            on_cmd_obj_select_request(p_req, p_res);
        } break;

        default:
        {
            ASSERT(false);
        } break;
    }
}


static void on_data_obj_select_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_SELECT (data)");

    p_res->select.crc    = s_dfu_settings.progress.firmware_image_crc;
    p_res->select.offset = s_dfu_settings.progress.firmware_image_offset;

    p_res->select.max_size = DATA_OBJECT_MAX_SIZE;

    NRF_LOG_DEBUG("crc = 0x%x, offset = 0x%x, max_size = 0x%x",
                  p_res->select.crc,
                  p_res->select.offset,
                  p_res->select.max_size);
}


static void on_data_obj_create_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_CREATE (data)");

    if (!nrf_dfu_validation_init_cmd_present())
    {
        /* Can't accept data because DFU isn't initialized by init command. */
        NRF_LOG_ERROR("Cannot create data object without valid init command");
        p_res->result = NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED;
        return;
    }

    if (p_req->create.object_size == 0)
    {
        NRF_LOG_ERROR("Object size cannot be 0.")
        p_res->result = NRF_DFU_RES_CODE_INVALID_PARAMETER;
        return;
    }

    if (  ((p_req->create.object_size & (CODE_PAGE_SIZE - 1)) != 0)
        && (s_dfu_settings.progress.firmware_image_offset_last + p_req->create.object_size != m_firmware_size_req))
    {
        NRF_LOG_ERROR("Object size must be page aligned");
        p_res->result = NRF_DFU_RES_CODE_INVALID_PARAMETER;
        return;
    }

    if (p_req->create.object_size > DATA_OBJECT_MAX_SIZE)
    {
        /* It is impossible to handle the command because the size is too large */
        NRF_LOG_ERROR("Invalid size for object (too large)");
        p_res->result = NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES;
        return;
    }

    if ((s_dfu_settings.progress.firmware_image_offset_last + p_req->create.object_size) >
        m_firmware_size_req)
    {
        NRF_LOG_ERROR("Creating the object with size 0x%08x would overflow firmware size. "
                      "Offset is 0x%08x and firmware size is 0x%08x.",
                      p_req->create.object_size,
                      s_dfu_settings.progress.firmware_image_offset_last,
                      m_firmware_size_req);

        p_res->result = NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED;
        return;
    }

    s_dfu_settings.progress.data_object_size      = p_req->create.object_size;
    s_dfu_settings.progress.firmware_image_crc    = s_dfu_settings.progress.firmware_image_crc_last;
    s_dfu_settings.progress.firmware_image_offset = s_dfu_settings.progress.firmware_image_offset_last;
    s_dfu_settings.write_offset                   = s_dfu_settings.progress.firmware_image_offset_last;

    /* Erase the page we're at. */
    if (nrf_dfu_flash_erase((m_firmware_start_addr + s_dfu_settings.progress.firmware_image_offset),
                            CEIL_DIV(p_req->create.object_size, CODE_PAGE_SIZE), NULL) != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Erase operation failed");
        p_res->result = NRF_DFU_RES_CODE_INVALID_OBJECT;
        return;
    }

    NRF_LOG_DEBUG("Creating object with size: %d. Offset: 0x%08x, CRC: 0x%08x",
                 s_dfu_settings.progress.data_object_size,
                 s_dfu_settings.progress.firmware_image_offset,
                 s_dfu_settings.progress.firmware_image_crc);
}


static void on_data_obj_write_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_WRITE (data)");

    if (!nrf_dfu_validation_init_cmd_present())
    {
        /* Can't accept data because DFU isn't initialized by init command. */
        p_res->result = NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED;
        return;
    }

    uint32_t const data_object_offset = s_dfu_settings.progress.firmware_image_offset -
                                        s_dfu_settings.progress.firmware_image_offset_last;

    if ((p_req->write.len + data_object_offset) > s_dfu_settings.progress.data_object_size)
    {
        /* Can't accept data because too much data has been received. */
        NRF_LOG_ERROR("Write request too long");
        p_res->result = NRF_DFU_RES_CODE_INVALID_PARAMETER;
        return;
    }

    uint32_t const write_addr = m_firmware_start_addr + s_dfu_settings.write_offset;

    ASSERT(p_req->callback.write);

    ret_code_t ret =
        nrf_dfu_flash_store(write_addr, p_req->write.p_data, p_req->write.len, p_req->callback.write);

    if (ret != NRF_SUCCESS)
    {
        /* When nrf_dfu_flash_store() fails because there is no space in the queue,
         * stop processing the request so that the peer can detect a CRC error
         * and retransmit this object. Remember to manually free the buffer !
         */
        p_req->callback.write((void*)p_req->write.p_data);
        return;
    }

    /* Update the CRC of the firmware image. */
    s_dfu_settings.write_offset                   += p_req->write.len;
    s_dfu_settings.progress.firmware_image_offset += p_req->write.len;
    s_dfu_settings.progress.firmware_image_crc     =
        crc32_compute(p_req->write.p_data, p_req->write.len, &s_dfu_settings.progress.firmware_image_crc);

    /* This is only used when the PRN is triggered and the 'write' message
     * is answered with a CRC message and these field are copied into the response.
     */
    p_res->write.crc    = s_dfu_settings.progress.firmware_image_crc;
    p_res->write.offset = s_dfu_settings.progress.firmware_image_offset;
}


static void on_data_obj_crc_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_CRC_GET (data)");
    NRF_LOG_DEBUG("Offset:%d, CRC:0x%08x",
                 s_dfu_settings.progress.firmware_image_offset,
                 s_dfu_settings.progress.firmware_image_crc);

    p_res->crc.crc    = s_dfu_settings.progress.firmware_image_crc;
    p_res->crc.offset = s_dfu_settings.progress.firmware_image_offset;
}


static void on_data_obj_execute_request_sched(void * p_evt, uint16_t event_length)
{
    UNUSED_PARAMETER(event_length);

    nrf_dfu_request_t * p_req = (nrf_dfu_request_t *)(p_evt);

    /* Wait for all buffers to be written in flash. */
    if (nrf_fstorage_is_busy(NULL))
    {
        ret_code_t ret = app_sched_event_put(p_req,
                                             sizeof(nrf_dfu_request_t),
                                             on_data_obj_execute_request_sched);
        if (ret != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Failed to schedule object execute: 0x%x.", ret);
        }
        return;
    }

    nrf_dfu_response_t res =
    {
        .request = NRF_DFU_OP_OBJECT_EXECUTE,
    };

    nrf_dfu_flash_callback_t dfu_settings_callback;

    /* Whole firmware image was received, validate it. */
    if (s_dfu_settings.progress.firmware_image_offset == m_firmware_size_req)
    {
        NRF_LOG_DEBUG("Postvalidation of firmware image.");

        res.result = nrf_dfu_validation_post_data_execute(m_firmware_start_addr, m_firmware_size_req);
        res.result = ext_err_code_handle(res.result);

        /* Callback to on_dfu_complete() after updating the settings. */
        dfu_settings_callback = (nrf_dfu_flash_callback_t)(on_dfu_complete);
    }
    else
    {
        res.result = NRF_DFU_RES_CODE_SUCCESS;
        /* No callback required. */
        dfu_settings_callback = NULL;
    }

    /* Provide response to transport */
    p_req->callback.response(&res, p_req->p_context);

    /* Store settings to flash if the whole image was received or if configured
     * to save progress information in flash.
     */
    if ((dfu_settings_callback != NULL) || NRF_DFU_SAVE_PROGRESS_IN_FLASH)
    {
        ret_code_t ret = nrf_dfu_settings_write(dfu_settings_callback);
        UNUSED_RETURN_VALUE(ret);
    }

    NRF_LOG_DEBUG("Request handling complete. Result: 0x%x", res.result);
}


static bool on_data_obj_execute_request(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    NRF_LOG_DEBUG("Handle NRF_DFU_OP_OBJECT_EXECUTE (data)");

    uint32_t const data_object_size = s_dfu_settings.progress.firmware_image_offset -
                                      s_dfu_settings.progress.firmware_image_offset_last;

    if (s_dfu_settings.progress.data_object_size != data_object_size)
    {
        /* The size of the written object was not as expected. */
        NRF_LOG_ERROR("Invalid data. expected: %d, got: %d",
                      s_dfu_settings.progress.data_object_size,
                      data_object_size);

        p_res->result = NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED;
        return true;
    }

    /* Update the offset and crc values for the last object written. */
    s_dfu_settings.progress.data_object_size           = 0;
    s_dfu_settings.progress.firmware_image_crc_last    = s_dfu_settings.progress.firmware_image_crc;
    s_dfu_settings.progress.firmware_image_offset_last = s_dfu_settings.progress.firmware_image_offset;

    on_data_obj_execute_request_sched(p_req, 0);

    m_observer(NRF_DFU_EVT_OBJECT_RECEIVED);

    return false;
}


static bool nrf_dfu_data_req(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    ASSERT(p_req);
    ASSERT(p_res);

    bool response_ready = true;

    switch (p_req->request)
    {
        case NRF_DFU_OP_OBJECT_CREATE:
        {
            on_data_obj_create_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            on_data_obj_write_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_CRC_GET:
        {
            on_data_obj_crc_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_OBJECT_EXECUTE:
        {
            response_ready = on_data_obj_execute_request(p_req, p_res);
        } break;

        case NRF_DFU_OP_OBJECT_SELECT:
        {
            on_data_obj_select_request(p_req, p_res);
        } break;

        default:
        {
            ASSERT(false);
        } break;
    }

    return response_ready;
}


/**@brief Function for handling requests to manipulate data or command objects.
 *
 * @param[in]  p_req    Request.
 * @param[out] p_res    Response.
 *
 * @return  Whether response is ready to be sent.
 */
static bool nrf_dfu_obj_op(nrf_dfu_request_t * p_req, nrf_dfu_response_t * p_res)
{
    /* Keep track of the current object type since write and execute requests don't contain it. */
    static nrf_dfu_obj_type_t current_object = NRF_DFU_OBJ_TYPE_COMMAND;

    if (    (p_req->request == NRF_DFU_OP_OBJECT_SELECT)
        ||  (p_req->request == NRF_DFU_OP_OBJECT_CREATE))
    {
        STATIC_ASSERT(offsetof(nrf_dfu_request_select_t, object_type) ==
                      offsetof(nrf_dfu_request_create_t, object_type),
                      "Wrong object_type offset!");

        current_object = (nrf_dfu_obj_type_t)(p_req->select.object_type);
    }

    bool response_ready = true;

    switch (current_object)
    {
        case NRF_DFU_OBJ_TYPE_COMMAND:
            nrf_dfu_command_req(p_req, p_res);
            break;

        case NRF_DFU_OBJ_TYPE_DATA:
            response_ready = nrf_dfu_data_req(p_req, p_res);
            break;

        default:
            /* The select request had an invalid object type. */
            NRF_LOG_ERROR("Invalid object type in request.");
            current_object = NRF_DFU_OBJ_TYPE_INVALID;
            p_res->result  = NRF_DFU_RES_CODE_INVALID_OBJECT;
            break;
    }

    return response_ready;
}


static void nrf_dfu_req_handler_req_process(nrf_dfu_request_t * p_req)
{
    ASSERT(p_req->callback.response);

    bool response_ready = true;

    /* The request handlers assume these values to be set. */
    nrf_dfu_response_t response =
    {
        .request = p_req->request,
        .result  = NRF_DFU_RES_CODE_SUCCESS,
    };


    switch (p_req->request)
    {
        case NRF_DFU_OP_PROTOCOL_VERSION:
        {
            on_protocol_version_request(p_req, &response);
        } break;

        case NRF_DFU_OP_HARDWARE_VERSION:
        {
            on_hw_version_request(p_req, &response);
        } break;

        case NRF_DFU_OP_FIRMWARE_VERSION:
        {
            on_fw_version_request(p_req, &response);
        } break;

        case NRF_DFU_OP_PING:
        {
            on_ping_request(p_req, &response);
        } break;

        case NRF_DFU_OP_RECEIPT_NOTIF_SET:
        {
            on_prn_set_request(p_req, &response);
        } break;

        case NRF_DFU_OP_MTU_GET:
        {
            on_mtu_get_request(p_req, &response);
        } break;

        case NRF_DFU_OP_ABORT:
        {
            on_abort_request(p_req, &response);
        } break;

        case NRF_DFU_OP_OBJECT_CREATE:
            /* Restart the inactivity timer on CREATE messages. */
            /* Fallthrough. */
        case NRF_DFU_OP_OBJECT_SELECT:
        case NRF_DFU_OP_OBJECT_WRITE:
        case NRF_DFU_OP_OBJECT_EXECUTE:
        case NRF_DFU_OP_CRC_GET:
        {
            response_ready = nrf_dfu_obj_op(p_req, &response);
        } break;

        default:
            NRF_LOG_INFO("Invalid opcode received: 0x%x.", p_req->request);
            response.result = NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED;
            break;
    }

    if (response_ready)
    {
        NRF_LOG_DEBUG("Request handling complete. Result: 0x%x", response.result);

        p_req->callback.response(&response, p_req->p_context);

        if (response.result != NRF_DFU_RES_CODE_SUCCESS)
        {
            m_observer(NRF_DFU_EVT_DFU_FAILED);
        }
    }
}


static void nrf_dfu_req_handler_req(void * p_evt, uint16_t event_length)
{
    nrf_dfu_request_t * p_req = (nrf_dfu_request_t *)(p_evt);
    nrf_dfu_req_handler_req_process(p_req);
}


ret_code_t nrf_dfu_req_handler_on_req(nrf_dfu_request_t * p_req)
{
    ret_code_t ret;

    if (p_req->callback.response == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    ret = app_sched_event_put(p_req, sizeof(nrf_dfu_request_t), nrf_dfu_req_handler_req);
    if (ret != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("Scheduler ran out of space!");
    }

    return ret;
}


ret_code_t nrf_dfu_req_handler_init(nrf_dfu_observer_t observer)
{
    ret_code_t       ret_val;
    nrf_dfu_result_t result;

    if (observer == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

#ifdef BLE_STACK_SUPPORT_REQD
    ret_val  = nrf_dfu_flash_init(true);
#else
    ret_val = nrf_dfu_flash_init(false);
#endif
    if (ret_val != NRF_SUCCESS)
    {
        return ret_val;
    }

    nrf_dfu_validation_init();
    if (nrf_dfu_validation_init_cmd_present())
    {
        /* Execute a previously received init packed. Subsequent executes will have no effect. */
        result = nrf_dfu_validation_init_cmd_execute(&m_firmware_start_addr, &m_firmware_size_req);
        if (result != NRF_DFU_RES_CODE_SUCCESS)
        {
            /* Init packet in flash is not valid! */
            return NRF_ERROR_INTERNAL;
        }
    }

    m_observer = observer;

    /* Initialize extended error handling with "No error" as the most recent error. */
    result = ext_error_set(NRF_DFU_EXT_ERROR_NO_ERROR);
    UNUSED_RETURN_VALUE(result);

    return NRF_SUCCESS;
}
