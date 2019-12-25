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
#include "nrf_dfu_ble.h"

#include <stddef.h>
#include "sdk_common.h"
#include "nrf_dfu_transport.h"
#include "nrf_dfu_types.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_handling_error.h"
#include "nrf_sdm.h"
#include "nrf_dfu_mbr.h"
#include "nrf_bootloader_info.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "ble_hci.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_balloc.h"
#include "nrf_delay.h"
#include "nrf_dfu_settings.h"
#include "nrf_dfu_ble.h"

#define NRF_LOG_MODULE_NAME nrf_dfu_ble
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#ifndef NRF_DFU_BLE_ADV_INTERVAL
#define NRF_DFU_BLE_ADV_INTERVAL 40 /* 40 * 0,625ms = 25ms */
#warning "sdk_config.h is not up to date."
#endif

#define APP_BLE_CONN_CFG_TAG                1                                                       /**< A tag identifying the SoftDevice BLE configuration. */

#define APP_ADV_DATA_HEADER_SIZE            9                                                       /**< Size of encoded advertisement data header (not including device name). */
#define APP_ADV_DURATION                    BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED                   /**< The advertising duration in units of 10 milliseconds. This is set to @ref BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED so that the advertisement is done as long as there there is a call to @ref dfu_transport_close function.*/

#define GATT_HEADER_LEN                     3                                                       /**< GATT header length. */
#define GATT_PAYLOAD(mtu)                   ((mtu) - GATT_HEADER_LEN)                               /**< Length of the ATT payload for a given ATT MTU. */
#define MAX_DFU_PKT_LEN                     (NRF_SDH_BLE_GATT_MAX_MTU_SIZE - GATT_HEADER_LEN)       /**< Maximum length (in bytes) of the DFU Packet characteristic (3 bytes are used for the GATT opcode and handle). */
#define MAX_RESPONSE_LEN                    17                                                      /**< Maximum length (in bytes) of the response to a Control Point command. */
#define RESPONSE_HEADER_LEN                 3                                                       /**< The length of the header of a response. I.E. the index of the opcode-specific payload. */

#define DFU_BLE_FLAG_INITIALIZED            (1 << 0)                                                /**< Flag to check if the DFU service was initialized by the application.*/
#define DFU_BLE_FLAG_USE_ADV_NAME           (1 << 1)                                                /**< Flag to indicate that advertisement name is to be used. */
#define DFU_BLE_RESETTING_SOON              (1 << 2)                                                /**< Flag to indicate that the device will reset soon. */

#define BLE_OBSERVER_PRIO                   2                                                       /**< BLE observer priority. Controls the priority for BLE event handler. */

#if (NRF_DFU_BLE_BUFFERS_OVERRIDE)
/* If selected, use the override value. */
#define MAX_DFU_BUFFERS     NRF_DFU_BLE_BUFFERS
#else
#define MAX_DFU_BUFFERS     ((CODE_PAGE_SIZE / MAX_DFU_PKT_LEN) + 1)
#endif

#if (NRF_DFU_BLE_REQUIRES_BONDS) && (!NRF_SDH_BLE_SERVICE_CHANGED)
#error NRF_DFU_BLE_REQUIRES_BONDS requires NRF_SDH_BLE_SERVICE_CHANGED.   \
       Please update the SoftDevice BLE stack configuration in sdk_config.h
#endif

#if (MAX_DFU_PKT_LEN % 4)
#error Payload length should be a multiple of four. \
       Payload length is set to NRF_SDH_BLE_GATT_MAX_MTU_SIZE - 3.
#endif


DFU_TRANSPORT_REGISTER(nrf_dfu_transport_t const ble_dfu_transport) =
{
    .init_func  = ble_dfu_transport_init,
    .close_func = ble_dfu_transport_close,
};

#if (NRF_DFU_BLE_REQUIRES_BONDS)
static nrf_dfu_peer_data_t m_peer_data;
#else
static nrf_dfu_adv_name_t  m_adv_name;
#endif

static uint32_t           m_flags;
static ble_dfu_t          m_dfu;                                                                    /**< Structure used to identify the Device Firmware Update service. */
static uint16_t           m_pkt_notif_target;                                                       /**< Number of packets of firmware data to be received before transmitting the next Packet Receipt Notification to the DFU Controller. */
static uint16_t           m_pkt_notif_target_cnt;                                                   /**< Number of packets of firmware data received after sending last Packet Receipt Notification or since the receipt of a @ref BLE_DFU_PKT_RCPT_NOTIF_ENABLED event from the DFU service, which ever occurs later.*/
static uint16_t           m_conn_handle = BLE_CONN_HANDLE_INVALID;                                  /**< Handle of the current connection. */
static uint8_t            m_adv_handle  = BLE_GAP_ADV_SET_HANDLE_NOT_SET;                           /**< Advertising handle used to identify an advertising set. */
static nrf_dfu_observer_t m_observer;                                                               /**< Observer function called on certain events. */

static ble_gap_conn_params_t const m_gap_conn_params =
{
    .min_conn_interval = NRF_DFU_BLE_MIN_CONN_INTERVAL,
    .max_conn_interval = NRF_DFU_BLE_MAX_CONN_INTERVAL,
    /* This value is expressed in units of 10 ms, rather than 1 ms. */
    .conn_sup_timeout  = NRF_DFU_BLE_CONN_SUP_TIMEOUT_MS / 10,
    .slave_latency     = 0,
};

NRF_BALLOC_DEF(m_buffer_pool, MAX_DFU_PKT_LEN, MAX_DFU_BUFFERS);


/**@brief     Function for the Advertising functionality initialization.
 *
 * @details   Encodes the required advertising data and passes it to the stack.
 *            The advertising data encoded here is specific for DFU.
 */
static uint32_t advertising_init(uint8_t adv_flags, ble_gap_adv_params_t const * const p_adv_params)
{
    uint32_t err_code;
    uint16_t actual_device_name_length = BLE_GAP_ADV_SET_DATA_SIZE_MAX - APP_ADV_DATA_HEADER_SIZE;

    /* This needs to be static because of SoftDevice API requirements. */
    static uint8_t m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];

    ble_gap_adv_data_t m_adv_data =
    {
        .adv_data =
        {
            .p_data = m_enc_advdata,
            .len    = APP_ADV_DATA_HEADER_SIZE,
        }
    };

    /* Encode flags. */
    m_enc_advdata[0] = 0x2;
    m_enc_advdata[1] = BLE_GAP_AD_TYPE_FLAGS;
    m_enc_advdata[2] = adv_flags;

    /* Encode 'more available' UUID list. */
    m_enc_advdata[3] = 0x3;
    m_enc_advdata[4] = BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE;
    m_enc_advdata[5] = LSB_16(BLE_DFU_SERVICE_UUID);
    m_enc_advdata[6] = MSB_16(BLE_DFU_SERVICE_UUID);

    /* Get GAP device name and length. */
    err_code = sd_ble_gap_device_name_get(&m_enc_advdata[9], &actual_device_name_length);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Set GAP device in advertising data.
    m_enc_advdata[7] = actual_device_name_length + 1; // (actual_length + ADV_AD_TYPE_FIELD_SIZE(1))
    m_enc_advdata[8] = BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME;

    m_adv_data.adv_data.len += actual_device_name_length;

    return sd_ble_gap_adv_set_configure(&m_adv_handle, &m_adv_data, p_adv_params);
}


/**@brief Function for starting advertising.
 */
static uint32_t advertising_start(void)
{
    uint32_t err_code;
    uint8_t  adv_flag = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    ble_gap_adv_params_t adv_params =
    {
        .properties.type = BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED,
        .p_peer_addr     = NULL,
        .filter_policy   = BLE_GAP_ADV_FP_ANY,
        .interval        = NRF_DFU_BLE_ADV_INTERVAL,
        .duration        = APP_ADV_DURATION,
        .primary_phy     = BLE_GAP_PHY_1MBPS,
    };

    NRF_LOG_DEBUG("Advertising...");

#if (NRF_DFU_BLE_REQUIRES_BONDS)
    ble_gap_irk_t empty_irk = {{0}};

    if (memcmp(m_peer_data.ble_id.id_info.irk, empty_irk.irk, sizeof(ble_gap_irk_t)) != 0)
    {
        adv_flag                 = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
        adv_params.filter_policy = BLE_GAP_ADV_FP_FILTER_CONNREQ;

        ble_gap_addr_t   const * const p_gap_addr   = &m_peer_data.ble_id.id_addr_info;
        ble_gap_id_key_t const * const p_gap_id_key = &m_peer_data.ble_id;

        err_code = sd_ble_gap_whitelist_set(&p_gap_addr, 1);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_WARNING("sd_ble_gap_whitelist_set() returned %s",
                            NRF_LOG_ERROR_STRING_GET(err_code));
        }

        err_code = sd_ble_gap_device_identities_set(&p_gap_id_key, NULL, 1);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_WARNING("sd_ble_gap_device_identities_set() returned %s",
                            NRF_LOG_ERROR_STRING_GET(err_code));
        }
    }
#endif /* NRF_DFU_BLE_REQUIRES_BONDS */

    err_code = advertising_init(adv_flag, &adv_params);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_gap_adv_stop(m_adv_handle);
    UNUSED_RETURN_VALUE(err_code);

    return sd_ble_gap_adv_start(m_adv_handle, APP_BLE_CONN_CFG_TAG);
}


static bool is_cccd_configured(ble_dfu_t * p_dfu)
{
    uint8_t cccd_val_buf[BLE_CCCD_VALUE_LEN];

    ble_gatts_value_t gatts_value =
    {
        .len     = BLE_CCCD_VALUE_LEN,
        .p_value = cccd_val_buf
    };

    /* Check the CCCD Value of DFU Control Point. */
    uint32_t err_code = sd_ble_gatts_value_get(m_conn_handle,
                                               p_dfu->dfu_ctrl_pt_handles.cccd_handle,
                                               &gatts_value);
    VERIFY_SUCCESS(err_code);

    return ble_srv_is_notification_enabled(cccd_val_buf);
}


static ret_code_t response_send(uint8_t * p_buf, uint16_t len)
{
    ble_gatts_hvx_params_t hvx_params =
    {
        .handle = m_dfu.dfu_ctrl_pt_handles.value_handle,
        .type   = BLE_GATT_HVX_NOTIFICATION,
        .p_data = (uint8_t *)(p_buf),
        .p_len  = &len,
    };

    return sd_ble_gatts_hvx(m_conn_handle, &hvx_params);
}


#if (NRF_DFU_BLE_REQUIRES_BONDS)
static uint32_t service_changed_send(void)
{
    uint32_t err_code;

    NRF_LOG_DEBUG("Sending Service Changed indication");

    err_code = sd_ble_gatts_sys_attr_set(m_conn_handle,
                                         m_peer_data.sys_serv_attr,
                                         sizeof(m_peer_data.sys_serv_attr),
                                         BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_gatts_sys_attr_set(m_conn_handle,
                                         NULL,
                                         0,
                                         BLE_GATTS_SYS_ATTR_FLAG_USR_SRVCS);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_gatts_service_changed(m_conn_handle, m_dfu.service_handle, 0xFFFF);

    if (   (err_code == BLE_ERROR_INVALID_CONN_HANDLE)
        || (err_code == NRF_ERROR_INVALID_STATE)
        || (err_code == NRF_ERROR_BUSY))
    {
        /* These errors can be expected when trying to send a Service Changed indication */
        /* if the CCCD is not set to indicate. Thus, set the returning error code to success. */
        NRF_LOG_WARNING("Client did not have the Service Changed indication set to enabled."
                        "Error: 0x%08x", err_code);
        err_code = NRF_SUCCESS;
    }

    return err_code;
}
#endif


/**@brief Function for encoding the beginning of a response.
 *
 * @param[inout] p_buffer  The buffer to encode into.
 * @param[in]    op_code   The opcode of the response.
 * @param[in]    result    The result of the operation.
 *
 * @return The length added to the buffer.
 */
static uint32_t response_prepare(uint8_t * p_buffer, uint8_t op_code, uint8_t result)
{
    ASSERT(p_buffer);
    p_buffer[0] = NRF_DFU_OP_RESPONSE;
    p_buffer[1] = op_code;
    p_buffer[2] = result;
    return RESPONSE_HEADER_LEN;
}


/**@brief Function for encoding a select object response into a buffer.
 *
 * The select object response consists of a maximum object size, a firmware offset, and a CRC value.
 *
 * @param[inout] p_buffer   The buffer to encode the response into.
 * @param[in]    max_size   The maximum object size value to encode.
 * @param[in]    fw_offset  The firmware offset value to encode.
 * @param[in]    crc        The CRC value to encode.
 *
 * @return The length added to the buffer.
 */
static uint32_t response_select_obj_add(uint8_t  * p_buffer,
                                        uint32_t   max_size,
                                        uint32_t   fw_offset,
                                        uint32_t   crc)
{
    uint16_t offset = uint32_encode(max_size,  &p_buffer[RESPONSE_HEADER_LEN]);
    offset         += uint32_encode(fw_offset, &p_buffer[RESPONSE_HEADER_LEN + offset]);
    offset         += uint32_encode(crc,       &p_buffer[RESPONSE_HEADER_LEN + offset]);
    return offset;
}


/**@brief Function for encoding a CRC response into a buffer.
 *
 * The CRC response consists of a firmware offset and a CRC value.
 *
 * @param[inout] p_buffer   The buffer to encode the response into.
 * @param[in]    fw_offset  The firmware offset value to encode.
 * @param[in]    crc        The CRC value to encode.
 *
 * @return The length added to the buffer.
 */
static uint32_t response_crc_add(uint8_t * p_buffer, uint32_t fw_offset, uint32_t crc)
{
    uint16_t offset = uint32_encode(fw_offset, &p_buffer[RESPONSE_HEADER_LEN]);
    offset         += uint32_encode(crc,       &p_buffer[RESPONSE_HEADER_LEN + offset]);
    return offset;
}


/**@brief Function for appending an extended error code to the response buffer.
 *
 * @param[inout] p_buffer    The buffer to append the extended error code to.
 * @param[in]    result      The error code to append.
 * @param[in]    buf_offset  The current length of the buffer.
 *
 * @return The length added to the buffer.
 */
static uint32_t response_ext_err_payload_add(uint8_t * p_buffer, uint8_t result, uint32_t buf_offset)
{
    p_buffer[buf_offset] = ext_error_get();
    (void) ext_error_set(NRF_DFU_EXT_ERROR_NO_ERROR);
    return 1;
}


static void ble_dfu_req_handler_callback(nrf_dfu_response_t * p_res, void * p_context)
{
    ASSERT(p_res);
    ASSERT(p_context);

    uint8_t len = 0;
    uint8_t buffer[MAX_RESPONSE_LEN] = {0};

    if (p_res->request == NRF_DFU_OP_OBJECT_WRITE)
    {
        --m_pkt_notif_target_cnt;
        if ((m_pkt_notif_target == 0) || (m_pkt_notif_target_cnt && m_pkt_notif_target > 0))
        {
            return;
        }

        /* Reply with a CRC message and reset the packet counter. */
        m_pkt_notif_target_cnt = m_pkt_notif_target;

        p_res->request = NRF_DFU_OP_CRC_GET;
    }

    len += response_prepare(buffer, p_res->request, p_res->result);

    if (p_res->result != NRF_DFU_RES_CODE_SUCCESS)
    {
        NRF_LOG_WARNING("DFU request %d failed with error: 0x%x", p_res->request, p_res->result);

        if (p_res->result == NRF_DFU_RES_CODE_EXT_ERROR)
        {
            len += response_ext_err_payload_add(buffer, p_res->result, len);
        }

        (void) response_send(buffer, len);
        return;
    }

    switch (p_res->request)
    {
        case NRF_DFU_OP_OBJECT_CREATE:
        case NRF_DFU_OP_OBJECT_EXECUTE:
            break;

        case NRF_DFU_OP_OBJECT_SELECT:
        {
            len += response_select_obj_add(buffer,
                                           p_res->select.max_size,
                                           p_res->select.offset,
                                           p_res->select.crc);
        } break;

        case NRF_DFU_OP_OBJECT_WRITE:
        {
            len += response_crc_add(buffer, p_res->write.offset, p_res->write.crc);
        } break;

        case NRF_DFU_OP_CRC_GET:
        {
            len += response_crc_add(buffer, p_res->crc.offset, p_res->crc.crc);
        } break;

        default:
        {
            // No action.
        } break;
    }

    (void) response_send(buffer, len);
}


/**@brief     Function for handling a Write event on the Control Point characteristic.
 *
 * @param[in] p_dfu             DFU Service Structure.
 * @param[in] p_ble_write_evt   Pointer to the write event received from BLE stack.
 *
 * @return    NRF_SUCCESS on successful processing of control point write. Otherwise an error code.
 */
static uint32_t on_ctrl_pt_write(ble_dfu_t * p_dfu, ble_gatts_evt_write_t const * p_ble_write_evt)
{
    //lint -save -e415 -e416 : Out-of-bounds access on p_ble_write_evt->data
    nrf_dfu_request_t request =
    {
        .request           = (nrf_dfu_op_t)(p_ble_write_evt->data[0]),
        .p_context         = p_dfu,
        .callback.response = ble_dfu_req_handler_callback,
    };

    switch (request.request)
    {
        case NRF_DFU_OP_OBJECT_SELECT:
        {
            /* Set object type to read info about */
            request.select.object_type = p_ble_write_evt->data[1];
        } break;

        case NRF_DFU_OP_OBJECT_CREATE:
        {
            /* Reset the packet receipt notification on create object */
            m_pkt_notif_target_cnt = m_pkt_notif_target;

            request.create.object_type = p_ble_write_evt->data[1];
            request.create.object_size = uint32_decode(&(p_ble_write_evt->data[2]));

            if (request.create.object_type == NRF_DFU_OBJ_TYPE_COMMAND)
            {
                /* Activity on the current transport. Close all except the current one. */
                (void) nrf_dfu_transports_close(&ble_dfu_transport);
            }
        } break;

        case NRF_DFU_OP_RECEIPT_NOTIF_SET:
        {
            NRF_LOG_DEBUG("Set receipt notif");

            m_pkt_notif_target     = uint16_decode(&(p_ble_write_evt->data[1]));
            m_pkt_notif_target_cnt = m_pkt_notif_target;
        } break;

        default:
            break;
    }
    //lint -restore : Out-of-bounds access

    return nrf_dfu_req_handler_on_req(&request);
}


/**@brief     Function for handling the @ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST event from the
 *            SoftDevice.
 *
 * @param[in] p_dfu     DFU Service Structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static bool on_rw_authorize_req(ble_dfu_t * p_dfu, ble_evt_t const * p_ble_evt)
{
    uint32_t err_code;

    ble_gatts_evt_rw_authorize_request_t const * p_authorize_request;
    ble_gatts_evt_write_t                const * p_ble_write_evt;

    p_authorize_request = &(p_ble_evt->evt.gatts_evt.params.authorize_request);
    p_ble_write_evt     = &(p_ble_evt->evt.gatts_evt.params.authorize_request.request.write);

    if (    (p_authorize_request->type                 != BLE_GATTS_AUTHORIZE_TYPE_WRITE)
        ||  (p_authorize_request->request.write.handle != p_dfu->dfu_ctrl_pt_handles.value_handle)
        ||  (p_authorize_request->request.write.op     != BLE_GATTS_OP_WRITE_REQ))
    {
        return false;
    }

    ble_gatts_rw_authorize_reply_params_t auth_reply =
    {
        .type                = BLE_GATTS_AUTHORIZE_TYPE_WRITE,
        .params.write.update = 1,
        .params.write.offset = p_ble_write_evt->offset,
        .params.write.len    = p_ble_write_evt->len,
        .params.write.p_data = p_ble_write_evt->data,
    };

    if (!is_cccd_configured(p_dfu))
    {
        /* Send an error response to the peer indicating that the CCCD is improperly configured. */
        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_CPS_CCCD_CONFIG_ERROR;

        /* Ignore response of auth reply */
        (void) sd_ble_gatts_rw_authorize_reply(m_conn_handle, &auth_reply);
        return false;
    }
    else
    {
        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;

        err_code = sd_ble_gatts_rw_authorize_reply(m_conn_handle, &auth_reply);
        return err_code  == NRF_SUCCESS ? true : false;
    }
}


static void on_flash_write(void * p_buf)
{
    NRF_LOG_DEBUG("Freeing buffer %p", p_buf);
    nrf_balloc_free(&m_buffer_pool, p_buf);
}


/**@brief   Function for handling the @ref BLE_GATTS_EVT_WRITE event from the SoftDevice.
 *
 * @param[in] p_dfu     DFU Service Structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_write(ble_dfu_t * p_dfu, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * const p_write_evt = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_write_evt->handle != p_dfu->dfu_pkt_handles.value_handle)
    {
        return;
    }

    /* Allocate a buffer to receive data. */
    uint8_t * p_balloc_buf = nrf_balloc_alloc(&m_buffer_pool);
    if (p_balloc_buf == NULL)
    {
        /* Operations are retried by the host; do not give up here. */
        NRF_LOG_WARNING("cannot allocate memory buffer!");
        return;
    }

    NRF_LOG_DEBUG("Buffer %p acquired, len %d (%d)",
                  p_balloc_buf, p_write_evt->len, MAX_DFU_PKT_LEN);

    /* Copy payload into buffer. */
    memcpy(p_balloc_buf, p_write_evt->data, p_write_evt->len);

    /* Set up the request. */
    nrf_dfu_request_t request =
    {
        .request      = NRF_DFU_OP_OBJECT_WRITE,
        .p_context    = p_dfu,
        .callback     =
        {
            .response = ble_dfu_req_handler_callback,
            .write    = on_flash_write,
        }
    };

    /* Set up the request buffer. */
    request.write.p_data   = p_balloc_buf;
    request.write.len      = p_write_evt->len;

    /* Schedule handling of the request. */
    ret_code_t rc = nrf_dfu_req_handler_on_req(&request);
    if (rc != NRF_SUCCESS)
    {
        /* The error is logged in nrf_dfu_req_handler_on_req().
         * Free the buffer.
         */
        (void) nrf_balloc_free(&m_buffer_pool, p_balloc_buf);
    }
}


/**@brief Function for the Application's SoftDevice event handler.
 *
 * @param[in] p_ble_evt SoftDevice event.
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    uint32_t                    err_code;
    ble_gap_evt_t const * const p_gap = &p_ble_evt->evt.gap_evt;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            NRF_LOG_DEBUG("Connected");

            m_conn_handle = p_gap->conn_handle;

            if (m_observer)
            {
                m_observer(NRF_DFU_EVT_TRANSPORT_ACTIVATED);
            }

            err_code = sd_ble_gap_conn_param_update(m_conn_handle, &m_gap_conn_params);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("Failure to update connection parameters: 0x%x", err_code);
            }
        } break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            m_conn_handle = BLE_CONN_HANDLE_INVALID;

            /* Restart advertising so that the DFU Controller can reconnect if possible. */
            if (!(m_flags & DFU_BLE_RESETTING_SOON))
            {
                err_code = advertising_start();
                APP_ERROR_CHECK(err_code);
            }

            if (m_observer)
            {
                m_observer(NRF_DFU_EVT_TRANSPORT_DEACTIVATED);
            }
        } break;

        case BLE_GATTS_EVT_WRITE:
        {
            on_write(&m_dfu, p_ble_evt);
        } break;

        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
        {
            uint16_t const mtu_requested =
                p_ble_evt->evt.gatts_evt.params.exchange_mtu_request.client_rx_mtu;

            /* If the requested MTU is smaller than the maximum, we can accept with the given
             * stack configuration, and the payload is not word-aligned, reply with a smaller MTU
             * that has a word-aligned payload. This ensures that the length of data we write to
             * flash is a multiple of the word size.
             */
            uint16_t mtu_reply;

            if (mtu_requested < NRF_SDH_BLE_GATT_MAX_MTU_SIZE)
            {
                /* Round the payload size down to a multiple of 4 so it is word-aligned. */
                if (GATT_PAYLOAD(mtu_requested) % 4)
                {
                    mtu_reply = GATT_PAYLOAD(mtu_requested) - 4;
                    mtu_reply = ALIGN_NUM(4, mtu_reply);
                    /* Add the header len to the MTU. */
                    mtu_reply += GATT_HEADER_LEN;
                }
                else
                {
                    mtu_reply = mtu_requested;
                }
            }
            else
            {
                mtu_reply = NRF_SDH_BLE_GATT_MAX_MTU_SIZE;
            }

            NRF_LOG_DEBUG("Received BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST (request: %d, reply: %d).",
                          mtu_requested, mtu_reply);

            err_code = sd_ble_gatts_exchange_mtu_reply(m_conn_handle, mtu_reply);
            APP_ERROR_CHECK(err_code);
        } break;
#ifndef S112
        case BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST.");

            ble_gap_data_length_params_t const dlp =
            {
                .max_rx_octets = BLE_GAP_DATA_LENGTH_AUTO,
                .max_tx_octets = BLE_GAP_DATA_LENGTH_AUTO,
            };

            err_code = sd_ble_gap_data_length_update(p_ble_evt->evt.gatts_evt.conn_handle,
                                                     &dlp, NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GAP_EVT_DATA_LENGTH_UPDATE:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_DATA_LENGTH_UPDATE (%u, max_rx_time %u).",
                          p_gap->params.data_length_update.effective_params.max_rx_octets,
                          p_gap->params.data_length_update.effective_params.max_rx_time_us);
        } break;
#endif

        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_SEC_PARAMS_REQUEST");

            uint16_t cccd;
            ble_gatts_value_t gatts_value =
            {
                .len     = BLE_CCCD_VALUE_LEN,
                .p_value = (uint8_t*)&cccd
            };

            err_code = sd_ble_gatts_value_get(m_conn_handle,
                                              BLE_UUID_GATT_CHARACTERISTIC_SERVICE_CHANGED,
                                              &gatts_value);
            APP_ERROR_CHECK(err_code);

            NRF_LOG_DEBUG("CCCD for service changed is 0x%04x", cccd);

            err_code = sd_ble_gap_sec_params_reply(m_conn_handle,
                                                   BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP,
                                                   NULL,
                                                   NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_CONN_PARAM_UPDATE");

            ble_gap_conn_params_t const * p_conn =
                &p_gap->params.conn_param_update.conn_params;

            NRF_LOG_DEBUG("max_conn_interval: %d", p_conn->max_conn_interval);
            NRF_LOG_DEBUG("min_conn_interval: %d", p_conn->min_conn_interval);
            NRF_LOG_DEBUG("slave_latency: %d",     p_conn->slave_latency);
            NRF_LOG_DEBUG("conn_sup_timeout: %d",  p_conn->conn_sup_timeout);
        } break;

#ifndef S112
        case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST");

            err_code = sd_ble_gap_conn_param_update(m_conn_handle,
                &p_gap->params.conn_param_update_request.conn_params);

            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("Failure to update connection parameter request: 0x%x", err_code);
            }

            APP_ERROR_CHECK(err_code);
        } break;
#endif

        case BLE_GAP_EVT_PHY_UPDATE:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_PHY_UPDATE (RX:%d, TX:%d, status:%d)",
                          p_gap->params.phy_update.rx_phy,
                          p_gap->params.phy_update.tx_phy,
                          p_gap->params.phy_update.status);
            break;
        }

        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_PHY_UPDATE_REQUEST.");

            ble_gap_phys_t const phys =
            {
                .rx_phys = BLE_GAP_PHY_AUTO,
                .tx_phys = BLE_GAP_PHY_AUTO,
            };

            err_code = sd_ble_gap_phy_update(p_gap->conn_handle, &phys);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_TIMEOUT:
        {
            if (p_ble_evt->evt.gatts_evt.params.timeout.src == BLE_GATT_TIMEOUT_SRC_PROTOCOL)
            {
                err_code = sd_ble_gap_disconnect(m_conn_handle,
                                                 BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
                APP_ERROR_CHECK(err_code);
            }
        } break;

        case BLE_EVT_USER_MEM_REQUEST:
        {
            err_code = sd_ble_user_mem_reply(m_conn_handle, NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
        {
            if (p_ble_evt->evt.gatts_evt.params.authorize_request.type
                != BLE_GATTS_AUTHORIZE_TYPE_INVALID)
            {
                if (on_rw_authorize_req(&m_dfu, p_ble_evt))
                {
                    err_code = on_ctrl_pt_write(&m_dfu,
                           &(p_ble_evt->evt.gatts_evt.params.authorize_request.request.write));

                    if (err_code != NRF_SUCCESS)
                    {
                        NRF_LOG_ERROR("Could not handle on_ctrl_pt_write. err_code: 0x%04x", err_code);
                    }
                }
            }
        } break;

        case BLE_GAP_EVT_SEC_INFO_REQUEST:
        {
            NRF_LOG_DEBUG("Received BLE_GAP_EVT_SEC_INFO_REQUEST");

            ble_gap_enc_info_t * p_enc_info = NULL;
            ble_gap_irk_t      * p_id_info  = NULL;

            #if (NRF_DFU_BLE_REQUIRES_BONDS)
                /* If there is a match in diversifier, then set the correct keys. */
                if (p_gap->params.sec_info_request.master_id.ediv ==
                    m_peer_data.enc_key.master_id.ediv)
                {
                    p_enc_info = &m_peer_data.enc_key.enc_info;
                }
                p_id_info = &m_peer_data.ble_id.id_info;
            #endif

            err_code = sd_ble_gap_sec_info_reply(p_gap->conn_handle, p_enc_info, p_id_info, NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
        {
            #if (NRF_DFU_BLE_REQUIRES_BONDS)
                err_code = service_changed_send();
            #else
                err_code = sd_ble_gatts_sys_attr_set(p_gap->conn_handle, NULL, 0, 0);
            #endif
            APP_ERROR_CHECK(err_code);
            NRF_LOG_DEBUG("Finished handling conn sec update");
        } break;

        default:
            /* No implementation needed. */
            break;
    }
}


#if (!NRF_DFU_BLE_REQUIRES_BONDS)
static uint32_t gap_address_change(void)
{
    uint32_t       err_code;
    ble_gap_addr_t addr;

    err_code = sd_ble_gap_addr_get(&addr);
    VERIFY_SUCCESS(err_code);

    /* Increase the BLE address by one when advertising openly. */
    addr.addr[0] += 1;

    err_code = sd_ble_gap_addr_set(&addr);
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}
#endif


/**@brief     Function for initializing GAP.
 *
 * @details   This function sets up all necessary GAP (Generic Access Profile) parameters of
 *            the device. It also sets the permissions and appearance.
 */
static uint32_t gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_sec_mode_t sec_mode;
    uint8_t const *         device_name;
    uint32_t                name_len;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

#if (!NRF_DFU_BLE_REQUIRES_BONDS)

    err_code = gap_address_change();
    VERIFY_SUCCESS(err_code);

    if ((m_flags & DFU_BLE_FLAG_USE_ADV_NAME) != 0)
    {
        NRF_LOG_DEBUG("Setting adv name: %s, length: %d", m_adv_name.name, m_adv_name.len);
        device_name = m_adv_name.name;
        name_len    = m_adv_name.len;
    }
    else
#endif
    {
        NRF_LOG_DEBUG("Using default advertising name");
        device_name = (uint8_t const *)(NRF_DFU_BLE_ADV_NAME);
        name_len    = strlen(NRF_DFU_BLE_ADV_NAME);
    }

    err_code = sd_ble_gap_device_name_set(&sec_mode, device_name, name_len);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_gap_ppcp_set(&m_gap_conn_params);
    return err_code;
}


static uint32_t ble_stack_init()
{
    ret_code_t err_code;
    uint32_t   ram_start = 0;

    /* Register as a BLE event observer to receive BLE events. */
    NRF_SDH_BLE_OBSERVER(m_ble_evt_observer, BLE_OBSERVER_PRIO, ble_evt_handler, NULL);

#if (!defined(NRF_DFU_BLE_SKIP_SD_INIT)) || (NRF_DFU_BLE_SKIP_SD_INIT == 0)
    err_code = nrf_dfu_mbr_init_sd();
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("Setting up vector table: 0x%08x", BOOTLOADER_START_ADDR);
    err_code = sd_softdevice_vector_table_base_set(BOOTLOADER_START_ADDR);
    VERIFY_SUCCESS(err_code);
#endif

    NRF_LOG_DEBUG("Enabling SoftDevice.");
    err_code = nrf_sdh_enable_request();
    VERIFY_SUCCESS(err_code);

    /* Fetch the start address of the application RAM. */
    err_code = nrf_sdh_ble_app_ram_start_get(&ram_start);
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("Configuring BLE stack.");
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    VERIFY_SUCCESS(err_code);

    /* Enable the BLE stack. */
    NRF_LOG_DEBUG("Enabling the BLE stack.");
    return nrf_sdh_ble_enable(&ram_start);
}


/**@brief       Function for adding DFU Packet characteristic to the BLE Stack.
 *
 * @param[in]   p_dfu DFU Service structure.
 *
 * @return      NRF_SUCCESS on success. Otherwise an error code.
 */
static uint32_t dfu_pkt_char_add(ble_dfu_t * const p_dfu)
{
    ble_gatts_char_md_t char_md =
    {
        .char_props.write_wo_resp = 1,
    };

    ble_uuid_t char_uuid =
    {
        .type = p_dfu->uuid_type,
        .uuid = BLE_DFU_PKT_CHAR_UUID,
    };

    ble_gatts_attr_md_t attr_md =
    {
        .vloc = BLE_GATTS_VLOC_STACK,
        .vlen = 1,
        .write_perm =
        {
            .sm = 1,
        #if NRF_DFU_BLE_REQUIRES_BONDS
            .lv = 2,
        #else
            .lv = 1,
        #endif
        }
    };

    ble_gatts_attr_t attr_char_value =
    {
        .p_uuid    = &char_uuid,
        .p_attr_md = &attr_md,
        .max_len   = MAX_DFU_PKT_LEN,
    };

    return sd_ble_gatts_characteristic_add(p_dfu->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_dfu->dfu_pkt_handles);
}


/**@brief       Function for adding DFU Control Point characteristic to the BLE Stack.
 *
 * @param[in]   p_dfu DFU Service structure.
 *
 * @return      NRF_SUCCESS on success. Otherwise an error code.
 */
static uint32_t dfu_ctrl_pt_add(ble_dfu_t * const p_dfu)
{
    ble_gatts_char_md_t char_md =
    {
        .char_props.write  = 1,
        .char_props.notify = 1,
    };

    ble_uuid_t char_uuid =
    {
        .type = p_dfu->uuid_type,
        .uuid = BLE_DFU_CTRL_PT_UUID,
    };

    ble_gatts_attr_md_t attr_md =
    {
        .vloc    = BLE_GATTS_VLOC_STACK,
        .wr_auth = 1,
        .vlen    = 1,
        .write_perm =
        {
            .sm = 1,
        #if NRF_DFU_BLE_REQUIRES_BONDS
            .lv = 2,
        #else
            .lv = 1,
        #endif
        },
    };

    ble_gatts_attr_t attr_char_value =
    {
        .p_uuid    = &char_uuid,
        .p_attr_md = &attr_md,
        .max_len   = BLE_GATT_ATT_MTU_DEFAULT,
    };

    return sd_ble_gatts_characteristic_add(p_dfu->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_dfu->dfu_ctrl_pt_handles);
}


/**@brief     Function for checking if the CCCD of DFU Control point is configured for Notification.
 *
 * @details   This function checks if the CCCD of DFU Control Point characteristic is configured
 *            for Notification by the DFU Controller.
 *
 * @param[in] p_dfu DFU Service structure.
 *
 * @return    True if the CCCD of DFU Control Point characteristic is configured for Notification.
 *            False otherwise.
 */
uint32_t ble_dfu_init(ble_dfu_t * p_dfu)
{
    ASSERT(p_dfu != NULL);

    ble_uuid_t service_uuid;
    uint32_t   err_code;

    m_conn_handle = BLE_CONN_HANDLE_INVALID;

    BLE_UUID_BLE_ASSIGN(service_uuid, BLE_DFU_SERVICE_UUID);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &(p_dfu->service_handle));
    VERIFY_SUCCESS(err_code);

    ble_uuid128_t const base_uuid128 =
    {
        {
            0x50, 0xEA, 0xDA, 0x30, 0x88, 0x83, 0xB8, 0x9F,
            0x60, 0x4F, 0x15, 0xF3,  0x00, 0x00, 0xC9, 0x8E
        }
    };

    err_code = sd_ble_uuid_vs_add(&base_uuid128, &p_dfu->uuid_type);
    VERIFY_SUCCESS(err_code);

    err_code = dfu_pkt_char_add(p_dfu);
    VERIFY_SUCCESS(err_code);

    err_code = dfu_ctrl_pt_add(p_dfu);
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}


uint32_t ble_dfu_transport_init(nrf_dfu_observer_t observer)
{
    uint32_t err_code = NRF_SUCCESS;

    if (m_flags & DFU_BLE_FLAG_INITIALIZED)
    {
        return err_code;
    }

    NRF_LOG_DEBUG("Initializing BLE DFU transport");

    m_observer = observer;

    err_code = nrf_balloc_init(&m_buffer_pool);
    UNUSED_RETURN_VALUE(err_code);

    err_code = ble_stack_init();
    VERIFY_SUCCESS(err_code);

#if (NRF_DFU_BLE_REQUIRES_BONDS)
    /* Copy out the peer data if bonds are required */
    if (nrf_dfu_settings_peer_data_is_valid())
    {
        NRF_LOG_DEBUG("Copying peer data");

        err_code = nrf_dfu_settings_peer_data_copy(&m_peer_data);
        UNUSED_RETURN_VALUE(err_code);
    }
    else
    {
        APP_ERROR_HANDLER(NRF_ERROR_INTERNAL);
    }
#else
    /* Copy out the new advertisement name when bonds are not required and the name is set. */
    if (nrf_dfu_settings_adv_name_is_valid())
    {
        err_code = nrf_dfu_settings_adv_name_copy(&m_adv_name);
        UNUSED_RETURN_VALUE(err_code);

        /* Set flags for advertisement name that is to be used */
        m_flags |= DFU_BLE_FLAG_USE_ADV_NAME;
    }
    else
    {
        NRF_LOG_DEBUG("No advertising name found");
    }
#endif

    err_code = gap_params_init();
    VERIFY_SUCCESS(err_code);

    /* Initialize the Device Firmware Update Service. */
    err_code = ble_dfu_init(&m_dfu);
    VERIFY_SUCCESS(err_code);

    err_code = advertising_start();
    VERIFY_SUCCESS(err_code);

    m_flags |= DFU_BLE_FLAG_INITIALIZED;

    NRF_LOG_DEBUG("BLE DFU transport initialized.");

    return NRF_SUCCESS;
}


uint32_t ble_dfu_transport_close(nrf_dfu_transport_t const * p_exception)
{
    uint32_t err_code = NRF_SUCCESS;

    if ((m_flags & DFU_BLE_FLAG_INITIALIZED) && (p_exception != &ble_dfu_transport))
    {
        NRF_LOG_DEBUG("Shutting down BLE transport.");

        if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
        {
            NRF_LOG_DEBUG("Disconnecting.");

            /* Set flag to prevent advertisement from starting */
            m_flags |= DFU_BLE_RESETTING_SOON;

            /* Disconnect from the peer. */
            err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            VERIFY_SUCCESS(err_code);

            /* Wait a bit for the disconnect event to be sent on air. */
            nrf_delay_ms(200);
        }
        else
        {
            err_code = sd_ble_gap_adv_stop(m_adv_handle);
            UNUSED_RETURN_VALUE(err_code);
        }

        err_code = nrf_sdh_disable_request();
        if (err_code == NRF_SUCCESS)
        {
            NRF_LOG_DEBUG("BLE transport shut down.");
        }
    }

    return err_code;
}

uint32_t ble_dfu_transport_disconnect(void)
{
    uint32_t err_code = NRF_SUCCESS;

    if (m_flags & DFU_BLE_FLAG_INITIALIZED)
    {
        NRF_LOG_DEBUG("Disconnect from BLE peer.");

        if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
        {
            NRF_LOG_DEBUG("Disconnecting.");

            /* Disconnect from the peer. */
            err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            VERIFY_SUCCESS(err_code);
        }
    }

    return err_code;
}
