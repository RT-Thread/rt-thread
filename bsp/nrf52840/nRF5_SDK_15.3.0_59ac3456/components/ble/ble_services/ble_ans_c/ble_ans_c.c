/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/* Attention!
 * To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile
 * qualification listings, this section of source code must not be modified.
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_ANS_C)
#include "ble_ans_c.h"
#include <string.h>
#include <stdbool.h>
#include "ble_err.h"
#include "nrf_assert.h"
#include "ble_db_discovery.h"
#define NRF_LOG_MODULE_NAME ble_ans_c
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define NOTIFICATION_DATA_LENGTH 2                              /**< The mandatory length of notification data. After the mandatory data, the optional message is located. */
#define READ_DATA_LENGTH_MIN     1                              /**< Minimum data length in a valid Alert Notification Read Response message. */

#define TX_BUFFER_MASK           0x07                           /**< TX Buffer mask, must be a mask of contiguous zeroes, followed by contiguous sequence of ones: 000...111. */
#define TX_BUFFER_SIZE           (TX_BUFFER_MASK + 1)           /**< Size of send buffer, which is 1 higher than the mask. */
#define WRITE_MESSAGE_LENGTH     2                              /**< Length of the write message for CCCD/control point. */


typedef enum
{
    READ_REQ = 1,                                               /**< Type identifying that this tx_message is a read request. */
    WRITE_REQ                                                   /**< Type identifying that this tx_message is a write request. */
} ans_tx_request_t;


/**@brief Structure for writing a message to the central, i.e. Control Point or CCCD.
 */
typedef struct
{
    uint8_t                  gattc_value[WRITE_MESSAGE_LENGTH]; /**< The message to write. */
    ble_gattc_write_params_t gattc_params;                      /**< GATTC parameters for this message. */
} ans_write_params_t;

/**@brief Structure for holding data to be transmitted to the connected central.
 */
typedef struct
{
    uint16_t         conn_handle;                               /**< Connection handle to be used when transmitting this message. */
    ans_tx_request_t type;                                      /**< Type of this message, i.e. read or write message. */
    union
    {
        uint16_t       read_handle;                             /**< Read request message. */
        ans_write_params_t write_req;                           /**< Write request message. */
    } req;
} ans_tx_message_t;

static ans_tx_message_t m_tx_buffer[TX_BUFFER_SIZE];            /**< Transmit buffer for messages to be transmitted to the central. */
static uint32_t     m_tx_insert_index = 0;                      /**< Current index in the transmit buffer where next message should be inserted. */
static uint32_t     m_tx_index = 0;                             /**< Current index in the transmit buffer from where the next message to be transmitted resides. */


/**@brief Function for passing any pending request from the buffer to the stack.
 */
static void tx_buffer_process(void)
{
    if (m_tx_index != m_tx_insert_index)
    {
        uint32_t err_code;

        if (m_tx_buffer[m_tx_index].type == READ_REQ)
        {
            err_code = sd_ble_gattc_read(m_tx_buffer[m_tx_index].conn_handle,
                                         m_tx_buffer[m_tx_index].req.read_handle,
                                         0);
        }
        else
        {
            err_code = sd_ble_gattc_write(m_tx_buffer[m_tx_index].conn_handle,
                                          &m_tx_buffer[m_tx_index].req.write_req.gattc_params);
        }
        if (err_code == NRF_SUCCESS)
        {
            ++m_tx_index;
            m_tx_index &= TX_BUFFER_MASK;
        }
    }
}


/** @brief Function for copying a characteristic.
 */
static void char_set(ble_gattc_char_t * p_dest_char, ble_gattc_char_t const * p_source_char)
{
    memcpy(p_dest_char, p_source_char, sizeof(ble_gattc_char_t));
}

static void char_cccd_set(ble_gattc_desc_t * p_cccd, uint16_t cccd_handle)
{
    p_cccd->handle = cccd_handle;
}

/** @brief Function to check that all handles required by the client to use the server are present.
 */
static bool is_valid_ans_srv_discovered(ble_ans_c_service_t const * p_srv)
{
    if ((p_srv->alert_notif_ctrl_point.handle_value == BLE_GATT_HANDLE_INVALID)    ||
        (p_srv->suported_new_alert_cat.handle_value == BLE_GATT_HANDLE_INVALID)    ||
        (p_srv->suported_unread_alert_cat.handle_value == BLE_GATT_HANDLE_INVALID) ||
        (p_srv->new_alert.handle_value == BLE_GATT_HANDLE_INVALID)                 ||
        (p_srv->unread_alert_status.handle_value == BLE_GATT_HANDLE_INVALID)       ||
        (p_srv->new_alert_cccd.handle == BLE_GATT_HANDLE_INVALID)                  ||
        (p_srv->unread_alert_cccd.handle == BLE_GATT_HANDLE_INVALID)
        )
    {
        // At least one required characteristic is missing on the server side.
        return false;
    }
    return true;
}


void ble_ans_c_on_db_disc_evt(ble_ans_c_t * p_ans, ble_db_discovery_evt_t const * p_evt)
{
    ble_ans_c_evt_t evt;

    memset(&evt, 0, sizeof(ble_ans_c_evt_t));
    evt.conn_handle = p_evt->conn_handle;
    evt.evt_type = BLE_ANS_C_EVT_DISCOVERY_FAILED;

    // Check if the Alert Notification Service was discovered.
    if (p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE
        &&
        p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_ALERT_NOTIFICATION_SERVICE
        &&
        p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE)
    {
        // Find the characteristics inside the service.
        for (uint8_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            ble_gatt_db_char_t const * p_char = &(p_evt->params.discovered_db.charateristics[i]);

            switch (p_char->characteristic.uuid.uuid)
            {
                case BLE_UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR:
                    NRF_LOG_DEBUG("Found Ctrlpt \r\n\r");
                    char_set(&evt.data.service.alert_notif_ctrl_point, &p_char->characteristic);
                    break;

                case BLE_UUID_UNREAD_ALERT_CHAR:
                    NRF_LOG_DEBUG("Found Unread Alert \r\n\r");
                    char_set(&evt.data.service.unread_alert_status, &p_char->characteristic);
                    char_cccd_set(&evt.data.service.unread_alert_cccd,
                                  p_char->cccd_handle);
                    break;

                case BLE_UUID_NEW_ALERT_CHAR:
                    NRF_LOG_DEBUG("Found New Alert \r\n\r");
                    char_set(&evt.data.service.new_alert, &p_char->characteristic);
                    char_cccd_set(&evt.data.service.new_alert_cccd,
                                  p_char->cccd_handle);
                    break;

                case BLE_UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR:
                    NRF_LOG_DEBUG("Found supported unread alert category \r\n\r");
                    char_set(&evt.data.service.suported_unread_alert_cat, &p_char->characteristic);
                    break;

                case BLE_UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR:
                    NRF_LOG_DEBUG("Found supported new alert category \r\n\r");
                    char_set(&evt.data.service.suported_new_alert_cat, &p_char->characteristic);
                    break;

                default:
                    // No implementation needed.
                    break;
            }
        }
        if (is_valid_ans_srv_discovered(&evt.data.service))
        {
            evt.evt_type = BLE_ANS_C_EVT_DISCOVERY_COMPLETE;
        }
    }
    p_ans->evt_handler(&evt);
}


/**@brief Function for receiving and validating notifications received from the central.
 */
static void event_notify(ble_ans_c_t * p_ans, ble_evt_t const * p_ble_evt)
{
    uint32_t                       message_length;
    ble_ans_c_evt_t                event;
    ble_ans_alert_notification_t * p_alert        = &event.data.alert;
    ble_gattc_evt_hvx_t const    * p_notification = &p_ble_evt->evt.gattc_evt.params.hvx;

    // Message is not valid -> ignore.
    event.evt_type = BLE_ANS_C_EVT_NOTIFICATION;
    if (p_notification->len < NOTIFICATION_DATA_LENGTH)
    {
        return;
    }
    message_length = p_notification->len - NOTIFICATION_DATA_LENGTH;

    if (p_notification->handle == p_ans->service.new_alert.handle_value)
    {
        BLE_UUID_COPY_INST(event.uuid, p_ans->service.new_alert.uuid);
    }
    else if (p_notification->handle == p_ans->service.unread_alert_status.handle_value)
    {
        BLE_UUID_COPY_INST(event.uuid, p_ans->service.unread_alert_status.uuid);
    }
    else
    {
        // Nothing to process.
        return;
    }

    p_alert->alert_category       = p_notification->data[0];
    p_alert->alert_category_count = p_notification->data[1];                       //lint !e415
    p_alert->alert_msg_length     = (message_length > p_ans->message_buffer_size)
                                    ? p_ans->message_buffer_size
                                    : message_length;
    p_alert->p_alert_msg_buf = p_ans->p_message_buffer;

    memcpy(p_alert->p_alert_msg_buf,
           &p_notification->data[NOTIFICATION_DATA_LENGTH],
           p_alert->alert_msg_length); //lint !e416

    p_ans->evt_handler(&event);
}


/**@brief Function for handling write response events.
 */
static void event_write_rsp(ble_ans_c_t * p_ans, ble_evt_t const * p_ble_evt)
{
    tx_buffer_process();
}


/**@brief Function for validating and passing the response to the application,
 *        when a read response is received.
 */
static void event_read_rsp(ble_ans_c_t * p_ans, ble_evt_t const * p_ble_evt)
{
    ble_ans_c_evt_t                  event;
    ble_gattc_evt_read_rsp_t const * p_response;

    p_response     = &p_ble_evt->evt.gattc_evt.params.read_rsp;
    event.evt_type = BLE_ANS_C_EVT_READ_RESP;

    if (p_response->len < READ_DATA_LENGTH_MIN)
    {
        tx_buffer_process();
        return;
    }

    if (p_response->handle == p_ans->service.suported_new_alert_cat.handle_value)
    {
        BLE_UUID_COPY_INST(event.uuid, p_ans->service.suported_new_alert_cat.uuid);
    }
    else if (p_response->handle == p_ans->service.suported_unread_alert_cat.handle_value)
    {
        BLE_UUID_COPY_INST(event.uuid, p_ans->service.suported_unread_alert_cat.uuid);
    }
    else
    {
        // Bad response, ignore.
        tx_buffer_process();
        return;
    }

    event.data.settings = *(ble_ans_alert_settings_t *)(p_response->data);

    if (p_response->len == READ_DATA_LENGTH_MIN)
    {
        // Those must default to 0, if they are not returned by central.
        event.data.settings.ans_high_prioritized_alert_support = 0;
        event.data.settings.ans_instant_message_support        = 0;
    }

    p_ans->evt_handler(&event);

    tx_buffer_process();
}


/**@brief Function for disconnecting and cleaning the current service.
 */
static void event_disconnect(ble_ans_c_t * p_ans, ble_evt_t const * p_ble_evt)
{
    if (p_ans->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ans->conn_handle = BLE_CONN_HANDLE_INVALID;

        // Clearing all data for the service will also set all handle values to @ref BLE_GATT_HANDLE_INVALID
        memset(&p_ans->service, 0, sizeof(ble_ans_c_service_t));

        // There was a valid instance of IAS on the peer. Send an event to the
        // application, so that it can do any clean up related to this module.
        ble_ans_c_evt_t evt;

        evt.evt_type = BLE_ANS_C_EVT_DISCONN_COMPLETE;
        p_ans->evt_handler(&evt);
    }
}


/**@brief Function for handling of BLE stack events. */
void ble_ans_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_ans_c_t * p_ans = (ble_ans_c_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTC_EVT_HVX:
            event_notify(p_ans, p_ble_evt);
            break;

        case BLE_GATTC_EVT_WRITE_RSP:
            event_write_rsp(p_ans, p_ble_evt);
            break;

        case BLE_GATTC_EVT_READ_RSP:
            event_read_rsp(p_ans, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            event_disconnect(p_ans, p_ble_evt);
            break;
    }
}


uint32_t ble_ans_c_init(ble_ans_c_t * p_ans, ble_ans_c_init_t const * p_ans_init)
{
    VERIFY_PARAM_NOT_NULL(p_ans);
    VERIFY_PARAM_NOT_NULL(p_ans_init);
    VERIFY_PARAM_NOT_NULL(p_ans_init->evt_handler);

    // clear all handles
    memset(p_ans, 0, sizeof(ble_ans_c_t));
    memset(m_tx_buffer, 0, TX_BUFFER_SIZE);
    p_ans->conn_handle = BLE_CONN_HANDLE_INVALID;

    p_ans->evt_handler         = p_ans_init->evt_handler;
    p_ans->error_handler       = p_ans_init->error_handler;
    p_ans->message_buffer_size = p_ans_init->message_buffer_size;
    p_ans->p_message_buffer    = p_ans_init->p_message_buffer;

    BLE_UUID_BLE_ASSIGN(p_ans->service.service.uuid, BLE_UUID_ALERT_NOTIFICATION_SERVICE);
    BLE_UUID_BLE_ASSIGN(p_ans->service.new_alert.uuid, BLE_UUID_NEW_ALERT_CHAR);
    BLE_UUID_BLE_ASSIGN(p_ans->service.alert_notif_ctrl_point.uuid,
                        BLE_UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR);
    BLE_UUID_BLE_ASSIGN(p_ans->service.unread_alert_status.uuid, BLE_UUID_UNREAD_ALERT_CHAR);
    BLE_UUID_BLE_ASSIGN(p_ans->service.suported_new_alert_cat.uuid,
                        BLE_UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR);
    BLE_UUID_BLE_ASSIGN(p_ans->service.suported_unread_alert_cat.uuid,
                        BLE_UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR);

    BLE_UUID_BLE_ASSIGN(p_ans->service.new_alert_cccd.uuid, BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG);
    BLE_UUID_BLE_ASSIGN(p_ans->service.unread_alert_cccd.uuid,
                        BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG);

    return ble_db_discovery_evt_register(&p_ans->service.service.uuid);
}


/**@brief Function for creating a TX message for writing a CCCD.
 */
static uint32_t cccd_configure(uint16_t conn_handle, uint16_t handle_cccd, bool enable)
{
    ans_tx_message_t * p_msg;
    uint16_t           cccd_val = enable ? BLE_GATT_HVX_NOTIFICATION : 0;

    p_msg              = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    p_msg->req.write_req.gattc_params.handle   = handle_cccd;
    p_msg->req.write_req.gattc_params.len      = WRITE_MESSAGE_LENGTH;
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;
    p_msg->req.write_req.gattc_value[0]        = LSB_16(cccd_val);
    p_msg->req.write_req.gattc_value[1]        = MSB_16(cccd_val);
    p_msg->conn_handle                         = conn_handle;
    p_msg->type                                = WRITE_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_ans_c_enable_notif_new_alert(ble_ans_c_t const * p_ans)
{
    if (p_ans->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    else
    {
        return cccd_configure(p_ans->conn_handle,
                              p_ans->service.new_alert_cccd.handle,
                              true);
    }
}


uint32_t ble_ans_c_disable_notif_new_alert(ble_ans_c_t const * p_ans)
{
    return cccd_configure(p_ans->conn_handle,
                          p_ans->service.new_alert_cccd.handle,
                          false);
}


uint32_t ble_ans_c_enable_notif_unread_alert(ble_ans_c_t const * p_ans)
{
    if ( p_ans->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    return cccd_configure(p_ans->conn_handle,
                          p_ans->service.unread_alert_cccd.handle,
                          true);
}


uint32_t ble_ans_c_disable_notif_unread_alert(ble_ans_c_t const * p_ans)
{
    return cccd_configure(p_ans->conn_handle,
                          p_ans->service.unread_alert_cccd.handle,
                          false);
}


uint32_t ble_ans_c_control_point_write(ble_ans_c_t const             * p_ans,
                                       ble_ans_control_point_t const * p_control_point)
{
    ans_tx_message_t * p_msg;

    p_msg              = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    p_msg->req.write_req.gattc_params.handle   = p_ans->service.alert_notif_ctrl_point.handle_value;
    p_msg->req.write_req.gattc_params.len      = WRITE_MESSAGE_LENGTH;
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;
    p_msg->req.write_req.gattc_value[0]        = p_control_point->command;
    p_msg->req.write_req.gattc_value[1]        = p_control_point->category;
    p_msg->conn_handle                         = p_ans->conn_handle;
    p_msg->type                                = WRITE_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_ans_c_new_alert_read(ble_ans_c_t const * p_ans)
{
    ans_tx_message_t * msg;

    msg                = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    msg->req.read_handle = p_ans->service.suported_new_alert_cat.handle_value;
    msg->conn_handle     = p_ans->conn_handle;
    msg->type            = READ_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_ans_c_unread_alert_read(ble_ans_c_t const * p_ans)
{
    ans_tx_message_t * msg;

    msg                = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    msg->req.read_handle = p_ans->service.suported_unread_alert_cat.handle_value;
    msg->conn_handle     = p_ans->conn_handle;
    msg->type            = READ_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ble_ans_c_new_alert_notify(ble_ans_c_t const * p_ans, ble_ans_category_id_t category_id)
{
    ble_ans_control_point_t control_point;

    control_point.command  = ANS_NOTIFY_NEW_INCOMING_ALERT_IMMEDIATELY;
    control_point.category = category_id;

    return ble_ans_c_control_point_write(p_ans, &control_point);
}


uint32_t ble_ans_c_unread_alert_notify(ble_ans_c_t const * p_ans, ble_ans_category_id_t category_id)
{
    ble_ans_control_point_t control_point;

    control_point.command  = ANS_NOTIFY_UNREAD_CATEGORY_STATUS_IMMEDIATELY;
    control_point.category = category_id;

    return ble_ans_c_control_point_write(p_ans, &control_point);
}


uint32_t ble_ans_c_handles_assign(ble_ans_c_t               * p_ans,
                                  uint16_t                    conn_handle,
                                  ble_ans_c_service_t const * p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_ans);

    if (!is_valid_ans_srv_discovered(p_peer_handles))
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    p_ans->conn_handle = conn_handle;

    if (p_peer_handles != NULL)
    {
        // Copy the handles from the discovered characteristics over to the provided client instance.
        char_set(&p_ans->service.alert_notif_ctrl_point, &p_peer_handles->alert_notif_ctrl_point);
        char_set(&p_ans->service.suported_new_alert_cat, &p_peer_handles->suported_new_alert_cat);
        char_set(&p_ans->service.suported_unread_alert_cat, &p_peer_handles->suported_unread_alert_cat);
        char_set(&p_ans->service.new_alert, &p_peer_handles->new_alert);
        char_cccd_set(&p_ans->service.new_alert_cccd, p_peer_handles->new_alert_cccd.handle);
        char_set(&p_ans->service.unread_alert_status, &p_peer_handles->unread_alert_status);
        char_cccd_set(&p_ans->service.unread_alert_cccd, p_peer_handles->unread_alert_cccd.handle);
    }

    return NRF_SUCCESS;
}
#endif // NRF_MODULE_ENABLED(BLE_ANS_C)
