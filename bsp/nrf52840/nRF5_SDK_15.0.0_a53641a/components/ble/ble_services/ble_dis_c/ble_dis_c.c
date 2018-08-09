/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_DIS_C)
#include <stdlib.h>

#include "ble.h"
#include "ble_dis_c.h"
#include "ble_gattc.h"
#include "nrf_bitmask.h"
#include "nrf_queue.h"
#include "app_error.h"

#define NRF_LOG_MODULE_NAME ble_dis
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


// Value Field lengths for System ID characteristic.
#define BLE_DIS_C_MANUF_ID_LEN            5 /**< Length of Manufacturer ID field inside System ID characteristic. */
#define BLE_DIS_C_OU_ID_LEN               3 /**< Length of Organizationally Unique ID field inside System ID characteristic. */

// Value Field lengths for PnP ID characteristic.
#define BLE_DIS_C_VENDOR_ID_SRC_LEN       1 /**< Length of Vendor ID Source field inside PnP ID characteristic. */
#define BLE_DIS_C_VENDOR_ID_LEN           2 /**< Length of Vendor ID field inside PnP ID characteristic. */
#define BLE_DIS_C_PRODUCT_ID_LEN          2 /**< Length of Product ID field inside PnP ID characteristic. */
#define BLE_DIS_C_PRODUCT_VER_LEN         2 /**< Length of Product Version field inside PnP ID characteristic. */

#define BLE_DIS_C_ALL_CHARS_DISABLED_MASK 0x0000 /**< All DIS characteristics should be disabled. */
#define BLE_DIS_C_ALL_CHARS_ENABLED_MASK  0xFFFF /**< All DIS characteristics should be enabled. */


/**@brief Structure for describing Client read request.
 */
typedef struct
{
    uint16_t conn_handle; /**< Connection handle for the read request. */
    uint16_t att_handle;  /**< Attribute handle for the read request. */
} ble_dis_c_req_t;

/**@brief Queue for holding Client read requests.
 */
NRF_QUEUE_DEF(ble_dis_c_req_t, m_ble_dis_c_queue, BLE_DIS_C_QUEUE_SIZE, NRF_QUEUE_MODE_NO_OVERFLOW);
NRF_QUEUE_INTERFACE_DEC(ble_dis_c_req_t, ble_dis_c_queue);
NRF_QUEUE_INTERFACE_DEF(ble_dis_c_req_t, ble_dis_c_queue, &m_ble_dis_c_queue);


/**@brief Function for decoding System ID characteristic value.
 *
 * @param[in]  p_data     Pointer to System ID characteristic data.
 * @param[in]  len        Length of the System ID characteristic data.
 * @param[out] p_sys_id   Decoded System ID characteristic.
 *
 * @retval     NRF_SUCCESS               If the characteristic was initialized successfully.
 * @retval     NRF_ERROR_INVALID_LENGTH  Any parameter is NULL.
 */
static ret_code_t system_id_decode(uint8_t          const * p_data,
                                   uint16_t                 len,
                                   ble_dis_sys_id_t * const p_sys_id)
{
    uint16_t const expected_len = (BLE_DIS_C_MANUF_ID_LEN + BLE_DIS_C_OU_ID_LEN);

    // Validate response length.
    if (expected_len != len)
    {
        NRF_LOG_ERROR("System ID characteristic data cannot be decoded.");
        NRF_LOG_ERROR("Expected data length != Received data length: %d != %d", expected_len, len);
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Decode Manufacturer ID.
    p_sys_id->manufacturer_id = uint40_decode(p_data);
    p_data                   += BLE_DIS_C_MANUF_ID_LEN;

    // Decode Organizationally unique ID.
    p_sys_id->organizationally_unique_id = uint24_decode(p_data);

    return NRF_SUCCESS;
}


/**@brief Function for decoding PnP ID characteristic value.
 *
 * @param[in]  p_data     Pointer to PnP ID characteristic data.
 * @param[in]  len        Length of the PnP ID characteristic data.
 * @param[out] p_pnp_id   Decoded PnP ID characteristic.
 *
 * @retval     NRF_SUCCESS               If the characteristic was initialized successfully.
 * @retval     NRF_ERROR_INVALID_LENGTH  Any parameter is NULL.
 */
static ret_code_t pnp_id_decode(uint8_t          const * p_data,
                                uint16_t                 len,
                                ble_dis_pnp_id_t * const p_pnp_id)
{
    uint16_t const expected_len = (BLE_DIS_C_VENDOR_ID_SRC_LEN + BLE_DIS_C_VENDOR_ID_LEN +
                                   BLE_DIS_C_PRODUCT_ID_LEN + BLE_DIS_C_PRODUCT_VER_LEN);

    // Validate response length.
    if (expected_len != len)
    {
        NRF_LOG_ERROR("PnP ID characteristic data cannot be decoded.");
        NRF_LOG_ERROR("Expected data length != Received data length: %d != %d", expected_len, len);
        return NRF_ERROR_INVALID_LENGTH;
    }

    // Decode Vendor ID Source.
    p_pnp_id->vendor_id_source = p_data[0];
    p_data                    += BLE_DIS_C_VENDOR_ID_SRC_LEN;

    // Decode Vendor ID.
    p_pnp_id->vendor_id = uint16_decode(p_data);
    p_data             += BLE_DIS_C_VENDOR_ID_LEN;

    // Decode Product ID.
    p_pnp_id->product_id = uint16_decode(p_data);
    p_data              += BLE_DIS_C_PRODUCT_ID_LEN;

    // Decode Product Version.
    p_pnp_id->product_version = uint16_decode(p_data);

    return NRF_SUCCESS;
}


/**@brief Function for matching DIS Client characteristic type with the provided response handle.
 *
 * @param[in] p_ble_dis_c      Pointer to the Device Information Client Structure.
 * @param[in] response_handle  Attribute handle from the response event.
 */
static ble_dis_c_char_type_t char_type_get(ble_dis_c_t * p_ble_dis_c, uint16_t response_handle)
{
    for (ble_dis_c_char_type_t char_type = (ble_dis_c_char_type_t) 0;
         char_type < BLE_DIS_C_CHAR_TYPES_NUM;
         char_type++)
    {
        if (response_handle == p_ble_dis_c->handles[char_type])
        {
            return char_type;
        }
    }
    return BLE_DIS_C_CHAR_TYPES_NUM;
}


/**@brief Function for passing any pending request from the queue to the stack.
 *
 * @param[in] p_ble_dis_c   Pointer to the Device Information Client Structure.
 */
static void queue_process(ble_dis_c_t * p_ble_dis_c)
{
    ret_code_t      err_code;
    ble_dis_c_req_t dis_c_req;

    err_code = ble_dis_c_queue_peek(&dis_c_req);
    if (err_code == NRF_SUCCESS) // Queue is not empty
    {
        err_code = sd_ble_gattc_read(dis_c_req.conn_handle,
                                     dis_c_req.att_handle,
                                     0);
        if (err_code == NRF_ERROR_BUSY) // SoftDevice is processing another Client procedure
        {
            NRF_LOG_DEBUG("SD is currently busy. This request for Client Read procedure will be \
                          attempted again.",
                          err_code);
        }
        else
        {
            UNUSED_RETURN_VALUE(ble_dis_c_queue_pop(&dis_c_req));
            if (err_code == NRF_SUCCESS)
            {
                NRF_LOG_DEBUG("SD Read/Write API returns Success.");
            }
            else
            {
                NRF_LOG_ERROR("SD Read API returns error: 0x%08X.", err_code);
                if (p_ble_dis_c->error_handler != NULL)
                {
                    p_ble_dis_c->error_handler(err_code);
                }
            }
        }
    }
}


/**@brief     Function for handling read response events.
 *
 * @details   This function will validate the read response and raise the appropriate
 *            event to the application.
 *
 * @param[in] p_ble_dis_c   Pointer to the Device Information Client Structure.
 * @param[in] p_ble_evt     Pointer to the SoftDevice event.
 */
static void on_read_rsp(ble_dis_c_t * p_ble_dis_c, ble_evt_t const * p_ble_evt)
{
    ret_code_t                       err_code;
    ble_gattc_evt_read_rsp_t const * p_response = &p_ble_evt->evt.gattc_evt.params.read_rsp;
    ble_dis_c_evt_t                  ble_dis_c_evt;
    ble_dis_c_char_type_t            char_type;

    // Check if the event is on the link for this instance and the event handler is present.
    if ((p_ble_dis_c->evt_handler == NULL) ||
        (p_ble_dis_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle))
    {
        return;
    }

    char_type = char_type_get(p_ble_dis_c, p_response->handle);
    if (char_type < BLE_DIS_C_CHAR_TYPES_NUM) // Characteristic type is valid.
    {
        memset(&ble_dis_c_evt, 0, sizeof(ble_dis_c_evt_t));

        ble_dis_c_evt.conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;

        if (p_ble_evt->evt.gattc_evt.gatt_status == BLE_GATT_STATUS_SUCCESS)
        {
            ble_dis_c_evt_read_rsp_t * const p_dis_rsp = &ble_dis_c_evt.params.read_rsp;

            ble_dis_c_evt.evt_type = BLE_DIS_C_EVT_DIS_C_READ_RSP;

            p_dis_rsp->char_type = char_type;
            p_dis_rsp->handle    = p_response->handle;

            // Decode characteristic value.
            switch (char_type)
            {
                case BLE_DIS_C_MANUF_NAME:
                case BLE_DIS_C_MODEL_NUM:
                case BLE_DIS_C_SERIAL_NUM:
                case BLE_DIS_C_HW_REV:
                case BLE_DIS_C_FW_REV:
                case BLE_DIS_C_SW_REV:
                    p_dis_rsp->content.string.p_data = (uint8_t *) p_response->data;
                    p_dis_rsp->content.string.len    = p_response->len;
                    break;

                case BLE_DIS_C_SYS_ID:
                    err_code = system_id_decode(p_response->data,
                                                p_response->len,
                                                &p_dis_rsp->content.sys_id);
                    if ((p_ble_dis_c->error_handler != NULL) && (err_code != NRF_SUCCESS))
                    {
                        p_ble_dis_c->error_handler(err_code);
                    }
                    break;

                case BLE_DIS_C_CERT_LIST:
                    p_dis_rsp->content.cert_list.p_list   = (uint8_t *) p_response->data;
                    p_dis_rsp->content.cert_list.list_len = p_response->len;
                    break;

                case BLE_DIS_C_PNP_ID:
                    err_code = pnp_id_decode(p_response->data,
                                             p_response->len,
                                             &p_dis_rsp->content.pnp_id);
                    if ((p_ble_dis_c->error_handler != NULL) && (err_code != NRF_SUCCESS))
                    {
                        p_ble_dis_c->error_handler(err_code);
                    }
                    break;

                default:
                    break;
            }

            p_ble_dis_c->evt_handler(p_ble_dis_c, &ble_dis_c_evt);
            NRF_LOG_DEBUG("Received correct read response.");
        }
        else // Generate error event.
        {
            ble_dis_c_evt.evt_type = BLE_DIS_C_EVT_DIS_C_READ_RSP_ERROR;

            ble_dis_c_evt.params.read_rsp_err.char_type   = char_type;
            ble_dis_c_evt.params.read_rsp_err.err_handle  = p_ble_evt->evt.gattc_evt.error_handle;
            ble_dis_c_evt.params.read_rsp_err.gatt_status = p_ble_evt->evt.gattc_evt.gatt_status;

            p_ble_dis_c->evt_handler(p_ble_dis_c, &ble_dis_c_evt);
            NRF_LOG_ERROR("Read request failed: 0x%04X.", p_ble_evt->evt.gattc_evt.gatt_status);
        }
    }
}


/**@brief     Function for handling Disconnected event received from the SoftDevice.
 *
 * @details   This function checks if the disconnect event is happening on the link
 *            associated with the current instance of the module. If so, it will set its
 *            conn_handle to invalid.
 *
 * @param[in] p_ble_dis_c   Pointer to the Device Information Client Structure.
 * @param[in] p_ble_evt     Pointer to the BLE event received.
 */
static void on_disconnected(ble_dis_c_t * p_ble_dis_c, const ble_evt_t * p_ble_evt)
{
    if (p_ble_dis_c->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ble_dis_c->conn_handle = BLE_CONN_HANDLE_INVALID;

        if (p_ble_dis_c->evt_handler != NULL)
        {
            ble_dis_c_evt_t dis_c_evt =
            {
                .evt_type    = BLE_DIS_C_EVT_DISCONNECTED,
                .conn_handle = p_ble_evt->evt.gap_evt.conn_handle
            };

            p_ble_dis_c->evt_handler(p_ble_dis_c, &dis_c_evt);
        }
    }
}


ret_code_t ble_dis_c_init(ble_dis_c_t * p_ble_dis_c, ble_dis_c_init_t * p_ble_dis_c_init)
{
    ble_uuid_t dis_uuid;

    VERIFY_PARAM_NOT_NULL(p_ble_dis_c);
    VERIFY_PARAM_NOT_NULL(p_ble_dis_c_init);

    dis_uuid.type = BLE_UUID_TYPE_BLE;
    dis_uuid.uuid = BLE_UUID_DEVICE_INFORMATION_SERVICE;

    p_ble_dis_c->conn_handle   = BLE_CONN_HANDLE_INVALID;
    p_ble_dis_c->evt_handler   = p_ble_dis_c_init->evt_handler;
    p_ble_dis_c->error_handler = p_ble_dis_c_init->error_handler;
    memset(p_ble_dis_c->handles, BLE_GATT_HANDLE_INVALID, sizeof(p_ble_dis_c->handles));

    // Enable only selected characteristics if characteristic group is defined.
    if (p_ble_dis_c_init->char_group.p_char_type != NULL)
    {
        p_ble_dis_c->char_mask = BLE_DIS_C_ALL_CHARS_DISABLED_MASK;

        for (uint8_t i = 0; i < p_ble_dis_c_init->char_group.size; i++)
        {
            nrf_bitmask_bit_set(p_ble_dis_c_init->char_group.p_char_type[i],
                                &p_ble_dis_c->char_mask);
        }
    }
    else
    {
        p_ble_dis_c->char_mask = BLE_DIS_C_ALL_CHARS_ENABLED_MASK;
    }

    return ble_db_discovery_evt_register(&dis_uuid);
}


void ble_dis_c_on_db_disc_evt(ble_dis_c_t * p_ble_dis_c, ble_db_discovery_evt_t * p_evt)
{
    ble_gatt_db_char_t * p_chars = p_evt->params.discovered_db.charateristics;
    ble_dis_c_evt_t      ble_dis_c_evt;

    // Check if the service discovery is necessary for the link and if the event handler is present.
    if ((p_ble_dis_c->evt_handler == NULL) ||
        (p_ble_dis_c->conn_handle == p_evt->conn_handle))
    {
        return;
    }

    // Check if the DIS was discovered.
    if ((p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE) &&
        (p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_DEVICE_INFORMATION_SERVICE) &&
        (p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE))
    {
        memset(&ble_dis_c_evt, 0, sizeof(ble_dis_c_evt_t));
        ble_dis_c_evt.evt_type    = BLE_DIS_C_EVT_DISCOVERY_COMPLETE;
        ble_dis_c_evt.conn_handle = p_evt->conn_handle;

        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            switch (p_chars[i].characteristic.uuid.uuid)
            {
                case BLE_UUID_MANUFACTURER_NAME_STRING_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_MANUF_NAME] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_MODEL_NUMBER_STRING_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_MODEL_NUM] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_SERIAL_NUMBER_STRING_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_SERIAL_NUM] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_HARDWARE_REVISION_STRING_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_HW_REV] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_FIRMWARE_REVISION_STRING_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_FW_REV] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_SOFTWARE_REVISION_STRING_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_SW_REV] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_SYSTEM_ID_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_SYS_ID] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_CERT_LIST] =
                        p_chars[i].characteristic.handle_value;
                    break;

                case BLE_UUID_PNP_ID_CHAR:
                    ble_dis_c_evt.params.disc_complete.handles[BLE_DIS_C_PNP_ID] =
                        p_chars[i].characteristic.handle_value;
                    break;

                default:
                    break;
            }
        }

        // Forget handle values for disabled characteristics
        for (ble_dis_c_char_type_t char_type = (ble_dis_c_char_type_t) 0;
             char_type < BLE_DIS_C_CHAR_TYPES_NUM;
             char_type++)
        {
            if (!nrf_bitmask_bit_is_set(char_type, &p_ble_dis_c->char_mask))
            {
                ble_dis_c_evt.params.disc_complete.handles[char_type] = BLE_GATT_HANDLE_INVALID;
            }
        }

        p_ble_dis_c->evt_handler(p_ble_dis_c, &ble_dis_c_evt);
    }
}


void ble_dis_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_dis_c_t * p_ble_dis_c = (ble_dis_c_t *) p_context;

    if ((p_ble_dis_c == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    if (p_ble_dis_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return;
    }

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTC_EVT_READ_RSP:
            on_read_rsp(p_ble_dis_c, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_ble_dis_c, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }

    // Process any DIS Client read requests that are pending.
    queue_process(p_ble_dis_c);
}


ret_code_t ble_dis_c_read(ble_dis_c_t * p_ble_dis_c, ble_dis_c_char_type_t char_type)
{
    ret_code_t      err_code;
    ble_dis_c_req_t dis_c_req;

    VERIFY_PARAM_NOT_NULL(p_ble_dis_c);
    VERIFY_TRUE(char_type < BLE_DIS_C_CHAR_TYPES_NUM, NRF_ERROR_INVALID_PARAM);

    if ((p_ble_dis_c->conn_handle == BLE_CONN_HANDLE_INVALID) ||
        (p_ble_dis_c->handles[char_type] == BLE_GATT_HANDLE_INVALID))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    dis_c_req.conn_handle = p_ble_dis_c->conn_handle;
    dis_c_req.att_handle  = p_ble_dis_c->handles[char_type];

    err_code = ble_dis_c_queue_push(&dis_c_req);
    VERIFY_SUCCESS(err_code);

    queue_process(p_ble_dis_c);
    return err_code;
}


ret_code_t ble_dis_c_handles_assign(ble_dis_c_t              * p_ble_dis_c,
                                    uint16_t                   conn_handle,
                                    ble_dis_c_handle_t const * p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_ble_dis_c);

    p_ble_dis_c->conn_handle = conn_handle;
    ble_dis_c_queue_reset();
    if (p_peer_handles != NULL)
    {
        memcpy(p_ble_dis_c->handles, p_peer_handles, sizeof(p_ble_dis_c->handles));
    }
    else
    {
        memset(p_ble_dis_c->handles, BLE_GATT_HANDLE_INVALID, sizeof(p_ble_dis_c->handles));
    }
    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(BLE_DIS_C)

