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
/**@file
 *
 * @defgroup sdk_nrf_dfu_req_handler Request handling
 * @{
 * @ingroup  nrf_dfu
 */

#ifndef NRF_DFU_REQ_HANDLER_H__
#define NRF_DFU_REQ_HANDLER_H__

#include <stdint.h>
#include <stdbool.h>
#include "app_util_platform.h"
#include "nrf_dfu_flash.h"
#include "nrf_dfu_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

ANON_UNIONS_ENABLE;

/**
 * @brief DFU object types.
 */
typedef enum
{
    NRF_DFU_OBJ_TYPE_INVALID,                   //!< Invalid object type.
    NRF_DFU_OBJ_TYPE_COMMAND,                   //!< Command object.
    NRF_DFU_OBJ_TYPE_DATA,                      //!< Data object.
} nrf_dfu_obj_type_t;

/**
 * @brief DFU protocol operation.
 */
typedef enum
{
    NRF_DFU_OP_PROTOCOL_VERSION     = 0x00,     //!< Retrieve protocol version.
    NRF_DFU_OP_OBJECT_CREATE        = 0x01,     //!< Create selected object.
    NRF_DFU_OP_RECEIPT_NOTIF_SET    = 0x02,     //!< Set receipt notification.
    NRF_DFU_OP_CRC_GET              = 0x03,     //!< Request CRC of selected object.
    NRF_DFU_OP_OBJECT_EXECUTE       = 0x04,     //!< Execute selected object.
    NRF_DFU_OP_OBJECT_SELECT        = 0x06,     //!< Select object.
    NRF_DFU_OP_MTU_GET              = 0x07,     //!< Retrieve MTU size.
    NRF_DFU_OP_OBJECT_WRITE         = 0x08,     //!< Write selected object.
    NRF_DFU_OP_PING                 = 0x09,     //!< Ping.
    NRF_DFU_OP_HARDWARE_VERSION     = 0x0A,     //!< Retrieve hardware version.
    NRF_DFU_OP_FIRMWARE_VERSION     = 0x0B,     //!< Retrieve firmware version.
    NRF_DFU_OP_ABORT                = 0x0C,     //!< Abort the DFU procedure.
    NRF_DFU_OP_RESPONSE             = 0x60,     //!< Response.
    NRF_DFU_OP_INVALID              = 0xFF,
} nrf_dfu_op_t;

/**
 * @brief DFU operation result code.
 */
typedef enum
{
    NRF_DFU_RES_CODE_INVALID                 = 0x00,    //!< Invalid opcode.
    NRF_DFU_RES_CODE_SUCCESS                 = 0x01,    //!< Operation successful.
    NRF_DFU_RES_CODE_OP_CODE_NOT_SUPPORTED   = 0x02,    //!< Opcode not supported.
    NRF_DFU_RES_CODE_INVALID_PARAMETER       = 0x03,    //!< Missing or invalid parameter value.
    NRF_DFU_RES_CODE_INSUFFICIENT_RESOURCES  = 0x04,    //!< Not enough memory for the data object.
    NRF_DFU_RES_CODE_INVALID_OBJECT          = 0x05,    //!< Data object does not match the firmware and hardware requirements, the signature is wrong, or parsing the command failed.
    NRF_DFU_RES_CODE_UNSUPPORTED_TYPE        = 0x07,    //!< Not a valid object type for a Create request.
    NRF_DFU_RES_CODE_OPERATION_NOT_PERMITTED = 0x08,    //!< The state of the DFU process does not allow this operation.
    NRF_DFU_RES_CODE_OPERATION_FAILED        = 0x0A,    //!< Operation failed.
    NRF_DFU_RES_CODE_EXT_ERROR               = 0x0B,    //!< Extended error. The next byte of the response contains the error code of the extended error (see @ref nrf_dfu_ext_error_code_t.
} nrf_dfu_result_t;

typedef enum
{
    NRF_DFU_FIRMWARE_TYPE_SOFTDEVICE    = 0x00,
    NRF_DFU_FIRMWARE_TYPE_APPLICATION   = 0x01,
    NRF_DFU_FIRMWARE_TYPE_BOOTLOADER    = 0x02,
    NRF_DFU_FIRMWARE_TYPE_UNKNOWN       = 0xFF,
} nrf_dfu_firmware_type_t;

/**
 * @brief @ref NRF_DFU_OP_PROTOCOL_VERSION response details.
 */
typedef struct
{
    uint8_t version;                    //!< Protocol version.
} nrf_dfu_response_protocol_t;

/**
 * @brief @ref NRF_DFU_OP_HARDWARE_VERSION response details.
 */
typedef struct
{
    uint32_t part;                      //!< Hardware part, from FICR register.
    uint32_t variant;                   //!< Hardware variant, from FICR register.
    struct
    {
        uint32_t rom_size;              //!< ROM size, in bytes.
        uint32_t ram_size;              //!< RAM size, in bytes.
        uint32_t rom_page_size;         //!< ROM flash page size, in bytes.
    } memory;
} nrf_dfu_response_hardware_t;

/**
 * @brief @ref NRF_DFU_OP_FIRMWARE_VERSION response details.
 */
typedef struct
{
    nrf_dfu_firmware_type_t type;       //!< Firmware type.
    uint32_t                version;    //!< Firmware version.
    uint32_t                addr;       //!< Firmware address in flash.
    uint32_t                len;        //!< Firmware length in bytes.
} nrf_dfu_response_firmware_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_SELECT response details.
 */
typedef struct
{
    uint32_t offset;                    //!< Current offset.
    uint32_t crc;                       //!< Current CRC.
    uint32_t max_size;                  //!< Maximum size of selected object.
} nrf_dfu_response_select_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_CREATE response details.
 */
typedef struct
{
    uint32_t offset;                    //!< Current offset
    uint32_t crc;                       //!< Current CRC.
} nrf_dfu_response_create_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_WRITE response details.
 */
typedef struct
{
    uint32_t offset;                    //!< Used only when packet receipt notification is used.
    uint32_t crc;                       //!< Used only when packet receipt notification is used.
} nrf_dfu_response_write_t;

/**
 * @brief @ref NRF_DFU_OP_CRC_GET response details.
 */
typedef struct
{
    uint32_t offset;                    //!< Current offset.
    uint32_t crc;                       //!< Current CRC.
} nrf_dfu_response_crc_t;

/**
 * @brief @ref NRF_DFU_OP_PING response details.
 */
typedef struct
{
    uint8_t id;                         //!< The received ID which is echoed back.
} nrf_dfu_response_ping_t;

/**
 * @brief @ref NRF_DFU_OP_MTU_GET response details.
 */
typedef struct
{
    uint16_t size;                      //!< The MTU size as specified by the local transport.
} nrf_dfu_response_mtu_t;

/**
 * @brief DFU response message.
 */
typedef struct
{
    nrf_dfu_op_t     request;                      //!< Requested operation.
    nrf_dfu_result_t result;                       //!< Result of the operation.
    union
    {
        nrf_dfu_response_protocol_t protocol;      //!< Protocol version response.
        nrf_dfu_response_hardware_t hardware;      //!< Hardware version response.
        nrf_dfu_response_firmware_t firmware;      //!< Firmware version response.
        nrf_dfu_response_select_t   select;        //!< Select object response..
        nrf_dfu_response_create_t   create;        //!< Create object response..
        nrf_dfu_response_write_t    write;         //!< Write object response.
        nrf_dfu_response_crc_t      crc;           //!< CRC response.
        nrf_dfu_response_ping_t     ping;          //!< Ping response.
        nrf_dfu_response_mtu_t      mtu;           //!< MTU response.
    };
} nrf_dfu_response_t;

/**
 * @brief @ref NRF_DFU_OP_FIRMWARE_VERSION request details.
 */
typedef struct
{
    uint8_t image_number;  //!< Index of the firmware.
} nrf_dfu_request_firmware_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_SELECT request details.
 */
typedef struct
{
    uint32_t object_type;  //!< Object type. See @ref nrf_dfu_obj_type_t.
} nrf_dfu_request_select_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_CREATE request details.
 */
typedef struct
{
    uint32_t object_type;  //!< Object type. See @ref nrf_dfu_obj_type_t.
    uint32_t object_size;  //!< Object size in bytes.
} nrf_dfu_request_create_t;

/**
 * @brief @ref NRF_DFU_OP_OBJECT_WRITE request details.
 */
typedef struct
{
    uint8_t  const * p_data; //!< Data.
    uint16_t         len;    //!< Length of data in @ref nrf_dfu_request_write_t::p_data.
} nrf_dfu_request_write_t;

/**
 * @brief @ref NRF_DFU_OP_PING request details.
 */
typedef struct
{
    uint8_t id;             //!< Ping ID that will be returned in response.
} nrf_dfu_request_ping_t;

/**
 * @brief @ref NRF_DFU_OP_MTU_GET request details.
 */
typedef struct
{
    uint16_t size;          //!< Transport MTU size in bytes.
} nrf_dfu_request_mtu_t;

/**
 * @brief @ref NRF_DFU_OP_RECEIPT_NOTIF_SET request details.
 */
typedef struct
{
    uint32_t target;        //!< Target PRN.
} nrf_dfu_request_prn_t;


typedef void (*nrf_dfu_response_callback_t)(nrf_dfu_response_t * p_res, void * p_context);

/**
 *@brief DFU request.
 */
typedef struct
{
    nrf_dfu_op_t   request;     //!< Requested operation.
    void         * p_context;
    struct
    {
        nrf_dfu_response_callback_t response; //!< Callback to call to send the response.
        nrf_dfu_flash_callback_t    write;
    } callback;
    union
    {
        nrf_dfu_request_firmware_t firmware;    //!< Firmware version request.
        nrf_dfu_request_select_t   select;      //!< Select object request.
        nrf_dfu_request_create_t   create;      //!< Create object request.
        nrf_dfu_request_write_t    write;       //!< Write object request.
        nrf_dfu_request_ping_t     ping;        //!< Ping.
        nrf_dfu_request_mtu_t      mtu;         //!< MTU size request.
        nrf_dfu_request_prn_t      prn;         //!< Set receipt notification request.
    };
} nrf_dfu_request_t;


/**@brief  Function for initializing the request handling module.
 *
 * @param observer  Function for receiving notifications.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_INTERNAL      If the init packet in flash is not valid.
 * @retval NRF_ERROR_INVALID_PARAM If observer is not provided.
 */
ret_code_t nrf_dfu_req_handler_init(nrf_dfu_observer_t observer);


/**@brief  Function for scheduling processing of a DFU request.
 *
 * Requests are processed asynchronously by the scheduler.
 *
 * @param[in] p_req  Request to be handled. The response callback must be non-null.
 *
 * @retval NRF_SUCCESS              If the command request was executed successfully.
 * @retval NRF_ERROR_NO_MEM         If the scheduler ran out of memory.
 * @retval NRF_ERROR_INVALID_PARAM  If the response callback is NULL.
 */
ret_code_t nrf_dfu_req_handler_on_req(nrf_dfu_request_t * p_req);


ANON_UNIONS_DISABLE;

#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_REQ_HANDLER_H__

/** @} */
