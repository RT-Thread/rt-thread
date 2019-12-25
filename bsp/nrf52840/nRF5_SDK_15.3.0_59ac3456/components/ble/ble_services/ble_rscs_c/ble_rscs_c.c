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
/**@cond To Make Doxygen skip documentation generation for this file.
 * @{
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_RSCS_C)
#include "ble_rscs_c.h"
#include "ble_db_discovery.h"
#include "ble_types.h"
#include "ble_srv_common.h"
#include "ble_gattc.h"

#define NRF_LOG_MODULE_NAME ble_rscs_c
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define TX_BUFFER_MASK         0x07                  /**< TX Buffer mask, must be a mask of continuous zeroes, followed by continuous sequence of ones: 000...111. */
#define TX_BUFFER_SIZE         (TX_BUFFER_MASK + 1)  /**< Size of send buffer, which is 1 higher than the mask. */

#define WRITE_MESSAGE_LENGTH   BLE_CCCD_VALUE_LEN    /**< Length of the write message for CCCD. */

typedef enum
{
    READ_REQ,  /**< Type identifying that this tx_message is a read request. */
    WRITE_REQ  /**< Type identifying that this tx_message is a write request. */
} tx_request_t;

/**@brief Structure for writing a message to the peer, i.e. CCCD.
 */
typedef struct
{
    uint8_t                  gattc_value[WRITE_MESSAGE_LENGTH];  /**< The message to write. */
    ble_gattc_write_params_t gattc_params;                       /**< GATTC parameters for this message. */
} write_params_t;

/**@brief Structure for holding data to be transmitted to the connected central.
 */
typedef struct
{
    uint16_t     conn_handle;  /**< Connection handle to be used when transmitting this message. */
    tx_request_t type;         /**< Type of this message, i.e. read or write message. */
    union
    {
        uint16_t       read_handle;  /**< Read request message. */
        write_params_t write_req;    /**< Write request message. */
    } req;
} tx_message_t;


static tx_message_t   m_tx_buffer[TX_BUFFER_SIZE];  /**< Transmit buffer for messages to be transmitted to the central. */
static uint32_t       m_tx_insert_index = 0;        /**< Current index in the transmit buffer where the next message should be inserted. */
static uint32_t       m_tx_index = 0;               /**< Current index in the transmit buffer from where the next message to be transmitted resides. */


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
            NRF_LOG_DEBUG("SD Read/Write API returns Success.");
            m_tx_index++;
            m_tx_index &= TX_BUFFER_MASK;
        }
        else
        {
            NRF_LOG_DEBUG("SD Read/Write API returns error. This message sending will be "
                          "attempted again..");
        }
    }
}


/**@brief     Function for handling write response events.
 *
 * @param[in] p_ble_rscs_c Pointer to the Running Speed and Cadence Client structure.
 * @param[in] p_ble_evt    Pointer to the BLE event received.
 */
static void on_write_rsp(ble_rscs_c_t * p_ble_rscs_c, const ble_evt_t * p_ble_evt)
{
    // Check if the event if on the link for this instance
    if (p_ble_rscs_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }
    // Check if there is any message to be sent across to the peer and send it.
    tx_buffer_process();
}


/**@brief     Function for handling Handle Value Notification received from the SoftDevice.
 *
 * @details   This function will uses the Handle Value Notification received from the SoftDevice
 *            and checks if it is a notification of the Running Speed and Cadence measurement from
 *            the peer. If it is, this function will decode the Running Speed measurement and send it
 *            to the application.
 *
 * @param[in] p_ble_rscs_c Pointer to the Running Speed and Cadence Client structure.
 * @param[in] p_ble_evt    Pointer to the BLE event received.
 */
static void on_hvx(ble_rscs_c_t * p_ble_rscs_c, const ble_evt_t * p_ble_evt)
{
    const ble_gattc_evt_hvx_t * p_notif = &p_ble_evt->evt.gattc_evt.params.hvx;

    // Check if the event if on the link for this instance
    if (p_ble_rscs_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }

    // Check if this is a Running Speed and Cadence notification.
    if (p_ble_evt->evt.gattc_evt.params.hvx.handle == p_ble_rscs_c->peer_db.rsc_handle)
    {
        uint32_t         index = 0;
        ble_rscs_c_evt_t ble_rscs_c_evt;
        ble_rscs_c_evt.evt_type    = BLE_RSCS_C_EVT_RSC_NOTIFICATION;
        ble_rscs_c_evt.conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;

        //lint -save -e415 -e416 -e662 "Access of out of bounds pointer" "Creation of out of bounds pointer"

        // Flags field
        ble_rscs_c_evt.params.rsc.is_inst_stride_len_present = p_notif->data[index] >> BLE_RSCS_INSTANT_STRIDE_LEN_PRESENT    & 0x01;
        ble_rscs_c_evt.params.rsc.is_total_distance_present  = p_notif->data[index] >> BLE_RSCS_TOTAL_DISTANCE_PRESENT        & 0x01;
        ble_rscs_c_evt.params.rsc.is_running                 = p_notif->data[index] >> BLE_RSCS_WALKING_OR_RUNNING_STATUS_BIT & 0x01;
        index++;

        // Instantaneous Speed
        ble_rscs_c_evt.params.rsc.inst_speed = uint16_decode(&p_notif->data[index]);
        index += sizeof(uint16_t);

        // Instantaneous Cadence
        ble_rscs_c_evt.params.rsc.inst_cadence = p_notif->data[index];
        index++;

        // Instantaneous Stride Length
        if (ble_rscs_c_evt.params.rsc.is_inst_stride_len_present == true)
        {
            ble_rscs_c_evt.params.rsc.inst_stride_length = uint16_decode(&p_notif->data[index]);
            index += sizeof(uint16_t);
        }

        // Total distance field
        if (ble_rscs_c_evt.params.rsc.is_total_distance_present == true)
        {
            ble_rscs_c_evt.params.rsc.total_distance = uint32_decode(&p_notif->data[index]);
            //index += sizeof(uint32_t);
        }

        p_ble_rscs_c->evt_handler(p_ble_rscs_c, &ble_rscs_c_evt);

        //lint -restore
    }
}


/**@brief     Function for handling events from the database discovery module.
 *
 * @details   This function will handle an event from the database discovery module, and determine
 *            if it relates to the discovery of heart rate service at the peer. If so, it will
 *            call the application's event handler indicating that the Running Speed and Cadence
 *            service has been discovered at the peer. It also populates the event with the service
 *            related information before providing it to the application.
 *
 * @param[in] p_evt Pointer to the event received from the database discovery module.
 *
 */
void ble_rscs_on_db_disc_evt(ble_rscs_c_t * p_ble_rscs_c, const ble_db_discovery_evt_t * p_evt)
{
    // Check if the Heart Rate Service was discovered.
    if (p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE &&
        p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_RUNNING_SPEED_AND_CADENCE &&
        p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE)
    {
        ble_rscs_c_evt_t evt;
        evt.conn_handle = p_evt->conn_handle;

        // Find the CCCD Handle of the Running Speed and Cadence characteristic.
        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            if (p_evt->params.discovered_db.charateristics[i].characteristic.uuid.uuid ==
                BLE_UUID_RSC_MEASUREMENT_CHAR)
            {
                // Found Running Speed and Cadence characteristic. Store CCCD handle and break.
                evt.params.rscs_db.rsc_cccd_handle =
                    p_evt->params.discovered_db.charateristics[i].cccd_handle;
                evt.params.rscs_db.rsc_handle      =
                    p_evt->params.discovered_db.charateristics[i].characteristic.handle_value;
                break;
            }
        }

        NRF_LOG_DEBUG("Running Speed and Cadence Service discovered at peer.");

        //If the instance has been assigned prior to db_discovery, assign the db_handles
        if (p_ble_rscs_c->conn_handle != BLE_CONN_HANDLE_INVALID)
        {
            if ((p_ble_rscs_c->peer_db.rsc_cccd_handle == BLE_GATT_HANDLE_INVALID)&&
                (p_ble_rscs_c->peer_db.rsc_handle == BLE_GATT_HANDLE_INVALID))
            {
                p_ble_rscs_c->peer_db = evt.params.rscs_db;
            }
        }

        evt.evt_type = BLE_RSCS_C_EVT_DISCOVERY_COMPLETE;

        p_ble_rscs_c->evt_handler(p_ble_rscs_c, &evt);
    }
}


uint32_t ble_rscs_c_init(ble_rscs_c_t * p_ble_rscs_c, ble_rscs_c_init_t * p_ble_rscs_c_init)
{
    VERIFY_PARAM_NOT_NULL(p_ble_rscs_c);
    VERIFY_PARAM_NOT_NULL(p_ble_rscs_c_init);

    ble_uuid_t rscs_uuid;

    rscs_uuid.type = BLE_UUID_TYPE_BLE;
    rscs_uuid.uuid = BLE_UUID_RUNNING_SPEED_AND_CADENCE;

    p_ble_rscs_c->evt_handler             = p_ble_rscs_c_init->evt_handler;
    p_ble_rscs_c->conn_handle             = BLE_CONN_HANDLE_INVALID;
    p_ble_rscs_c->peer_db.rsc_cccd_handle = BLE_GATT_HANDLE_INVALID;
    p_ble_rscs_c->peer_db.rsc_handle      = BLE_GATT_HANDLE_INVALID;

    return ble_db_discovery_evt_register(&rscs_uuid);
}


uint32_t ble_rscs_c_handles_assign(ble_rscs_c_t *    p_ble_rscs_c,
                                   uint16_t         conn_handle,
                                   ble_rscs_c_db_t * p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_ble_rscs_c);
    p_ble_rscs_c->conn_handle = conn_handle;
    if (p_peer_handles != NULL)
    {
        p_ble_rscs_c->peer_db = *p_peer_handles;
    }

    return NRF_SUCCESS;
}


/**@brief     Function for handling Disconnected event received from the SoftDevice.
 *
 * @details   This function check if the disconnect event is happening on the link
 *            associated with the current instance of the module, if so it will set its
 *            conn_handle to invalid.
 *
 * @param[in] p_ble_rscs_c Pointer to the RSC Client structure.
 * @param[in] p_ble_evt   Pointer to the BLE event received.
 */
static void on_disconnected(ble_rscs_c_t * p_ble_rscs_c, const ble_evt_t * p_ble_evt)
{
    if (p_ble_rscs_c->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ble_rscs_c->conn_handle             = BLE_CONN_HANDLE_INVALID;
        p_ble_rscs_c->peer_db.rsc_cccd_handle = BLE_GATT_HANDLE_INVALID;
        p_ble_rscs_c->peer_db.rsc_handle      = BLE_GATT_HANDLE_INVALID;
    }
}


void ble_rscs_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_rscs_c_t * p_ble_rscs_c = (ble_rscs_c_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTC_EVT_HVX:
            on_hvx(p_ble_rscs_c, p_ble_evt);
            break;

        case BLE_GATTC_EVT_WRITE_RSP:
            on_write_rsp(p_ble_rscs_c, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_ble_rscs_c, p_ble_evt);
            break;

        default:
            break;
    }
}


/**@brief Function for creating a message for writing to the CCCD.
 */
static uint32_t cccd_configure(uint16_t conn_handle, uint16_t handle_cccd, bool enable)
{
    NRF_LOG_DEBUG("Configuring CCCD. CCCD Handle = %d, Connection Handle = %d",
                  handle_cccd, conn_handle);

    tx_message_t * p_msg;
    uint16_t       cccd_val = enable ? BLE_GATT_HVX_NOTIFICATION : 0;

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


uint32_t ble_rscs_c_rsc_notif_enable(ble_rscs_c_t * p_ble_rscs_c)
{
    VERIFY_PARAM_NOT_NULL(p_ble_rscs_c);

    if (p_ble_rscs_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    return cccd_configure(p_ble_rscs_c->conn_handle, p_ble_rscs_c->peer_db.rsc_cccd_handle, true);
}

/** @}
 *  @endcond
 */
#endif // NRF_MODULE_ENABLED(BLE_RSCS_C)
