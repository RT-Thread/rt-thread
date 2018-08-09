/**
 * Copyright (c) 2015-2017 - 2018, Nordic Semiconductor ASA
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
#ifdef COMMISSIONING_ENABLED

#include <string.h>
#include "ble_ncfgs.h"
#include "app_error.h"
#include "ble.h"
#include "nordic_common.h"

/**@brief NCFGS database encapsulation.  */
typedef struct
{
    uint16_t                     service_handle;
    ble_gatts_char_handles_t     ssid_handles;
    ble_gatts_char_handles_t     keys_store_handles;
    ble_gatts_char_handles_t     ctrlp_handles;
} ble_database_t;

static ble_ncfgs_state_t         m_service_state = NCFGS_STATE_IDLE;                                /**< Module state value. */
static ble_ncfgs_evt_handler_t   m_app_evt_handler;                                                 /**< Parent module callback function. */
static ble_database_t            m_database;                                                        /**< GATT handles database. */
static uint8_t                   m_ctrlp_value_buffer[NCFGS_CTRLP_VALUE_LEN];                       /**< Stores received Control Point value before parsing. */
static ble_ncfgs_data_t          m_ncfgs_data;                                                      /**< Stores all values written by the peer device. */

#if NCFGS_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME ble_ncfgs

#define NRF_LOG_LEVEL       NCFGS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NCFGS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NCFGS_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define NCFGS_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define NCFGS_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define NCFGS_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define NCFGS_ENTRY()                       NCFGS_TRC(">> %s", __func__)
#define NCFGS_EXIT()                        NCFGS_TRC("<< %s", __func__)

#else // NCFGS_CONFIG_LOG_ENABLED

#define NCFGS_TRC(...)                                                                           /**< Disables traces. */
#define NCFGS_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define NCFGS_ERR(...)                                                                           /**< Disables error logs. */

#define NCFGS_ENTRY(...)
#define NCFGS_EXIT(...)

#endif // NCFGS_CONFIG_LOG_ENABLED

/**@brief Function for adding the SSID Store characteristic.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t add_ssid_characteristic(ble_uuid_t * p_srv_uuid)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          char_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0x00, sizeof(char_md));

    char_md.char_props.read  = 1;
    char_md.char_props.write = 1;

    memset(&attr_md, 0x00, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.wr_auth = 1;
    attr_md.vloc    = BLE_GATTS_VLOC_USER;

    memset(&attr_char_value, 0x00, sizeof(attr_char_value));

    char_uuid.type = p_srv_uuid->type;
    char_uuid.uuid = BLE_UUID_NCFGS_SSID_CHAR;

    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = NCFGS_SSID_MAX_LEN;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = NCFGS_SSID_MAX_LEN;
    attr_char_value.p_value   = &m_ncfgs_data.ssid_from_router.ssid[0];

    return sd_ble_gatts_characteristic_add(m_database.service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &m_database.ssid_handles);
}


/**@brief Function for adding the Keys Store characteristic.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t add_keys_store_characteristic(ble_uuid_t * p_srv_uuid)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          char_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0x00, sizeof(char_md));

    char_md.char_props.read  = 1;
    char_md.char_props.write = 1;

    memset(&attr_md, 0x00, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.wr_auth    = 1;
    attr_md.vloc       = BLE_GATTS_VLOC_USER;

    memset(&attr_char_value, 0x00, sizeof(attr_char_value));

    char_uuid.type = p_srv_uuid->type;
    char_uuid.uuid = BLE_UUID_NCFGS_KEYS_STORE_CHAR;

    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = NCFGS_KEYS_MAX_LEN;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = NCFGS_KEYS_MAX_LEN;
    attr_char_value.p_value   = &m_ncfgs_data.keys_from_router.keys[0];

    return sd_ble_gatts_characteristic_add(m_database.service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &m_database.keys_store_handles);
}


/**@brief Function for adding the Control Point characteristic.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t add_ip_cfg_cp_characteristic(ble_uuid_t * p_srv_uuid)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          char_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0x00, sizeof(char_md));

    char_md.char_props.read  = 1;
    char_md.char_props.write = 1;

    memset(&attr_md, 0x00, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.wr_auth    = 1;
    attr_md.vloc       = BLE_GATTS_VLOC_USER;

    memset(&attr_char_value, 0x00, sizeof(attr_char_value));

    char_uuid.type = p_srv_uuid->type;
    char_uuid.uuid = BLE_UUID_NCFGS_CTRLPT_CHAR;

    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = NCFGS_CTRLP_VALUE_LEN;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = NCFGS_CTRLP_VALUE_LEN;
    attr_char_value.p_value   = &m_ctrlp_value_buffer[0];

    return sd_ble_gatts_characteristic_add(m_database.service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &m_database.ctrlp_handles);
}


/**@brief Function for creating the GATT database.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t ble_ncfgs_create_database(void)
{
    uint32_t   err_code = NRF_SUCCESS;

    // Add service.
    ble_uuid_t service_uuid;

    const ble_uuid128_t base_uuid128 =
    {
        {
            0x73, 0x3E, 0x2D, 0x02, 0xB7, 0x6B, 0xBE, 0xBE, \
            0xE5, 0x4F, 0x40, 0x8F, 0x00, 0x00, 0x20, 0x54
        }
    };

    service_uuid.uuid = BLE_UUID_NODE_CFG_SERVICE;

    err_code = sd_ble_uuid_vs_add(&base_uuid128, &(service_uuid.type));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,  \
                                        &service_uuid,                \
                                        &m_database.service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = add_ssid_characteristic(&service_uuid);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = add_keys_store_characteristic(&service_uuid);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = add_ip_cfg_cp_characteristic(&service_uuid);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    return err_code;
}


uint32_t ble_ncfgs_init(ble_ncfgs_evt_handler_t ble_ncfgs_cb)
{
    NCFGS_ENTRY();
    uint32_t err_code;
    memset(&m_ncfgs_data, 0x00, sizeof(m_ncfgs_data));

    m_app_evt_handler = ble_ncfgs_cb;

    err_code = ble_ncfgs_create_database();
    NCFGS_EXIT();
    return err_code;
}


/**@brief Function for decoding the Control Point characteristic value.
 *
 * @return    NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t ctrlp_value_decode(const ble_evt_t * p_ble_evt)
{
    uint16_t wr_req_value_len = \
                p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.len;

    memcpy(m_ctrlp_value_buffer,                                                  \
           p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.data,  \
           wr_req_value_len);

    m_ncfgs_data.ctrlp_value.opcode           = \
        (ble_ncfgs_opcode_t)m_ctrlp_value_buffer[0];
    memcpy((void *)&m_ncfgs_data.ctrlp_value.delay_sec,  \
           &m_ctrlp_value_buffer[NCFGS_CTRLP_OPCODE_LEN],      \
           sizeof(uint32_t));
    m_ncfgs_data.ctrlp_value.delay_sec        = \
        HTONL(m_ncfgs_data.ctrlp_value.delay_sec);
    memcpy((void *)&m_ncfgs_data.ctrlp_value.duration_sec,           \
           &m_ctrlp_value_buffer[NCFGS_CTRLP_OPCODE_LEN+NCFGS_CTRLP_DELAY_LEN],  \
           sizeof(uint32_t));
    m_ncfgs_data.ctrlp_value.duration_sec     = \
        HTONL(m_ncfgs_data.ctrlp_value.duration_sec);
    m_ncfgs_data.ctrlp_value.state_on_failure = \
        (state_on_failure_t)m_ctrlp_value_buffer[NCFGS_CTRLP_OPCODE_LEN+    \
                                                 NCFGS_CTRLP_DELAY_LEN+     \
                                                 NCFGS_CTRLP_DURATION_LEN];

    if ((m_ncfgs_data.ctrlp_value.state_on_failure != NCFGS_SOF_NO_CHANGE)    && \
        (m_ncfgs_data.ctrlp_value.state_on_failure != NCFGS_SOF_PWR_OFF)      && \
        (m_ncfgs_data.ctrlp_value.state_on_failure != NCFGS_SOF_CONFIG_MODE))
    {
        return NRF_ERROR_INVALID_DATA;
    }

    uint16_t id_data_len = wr_req_value_len - NCFGS_CTRLP_ALL_BUT_ID_DATA_LEN;
    if (id_data_len != 0)
    {
        m_ncfgs_data.id_data.identity_data_len = id_data_len;

        memcpy(m_ncfgs_data.id_data.identity_data,                      \
               &m_ctrlp_value_buffer[NCFGS_CTRLP_ALL_BUT_ID_DATA_LEN],  \
               id_data_len);
    }

    return NRF_SUCCESS;
}


void ble_ncfgs_ble_evt_handler(const ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
        {
            if (p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.op == \
                    BLE_GATTS_OP_WRITE_REQ)
            {
                uint16_t wr_req_handle = \
                    p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.handle;
                uint16_t wr_req_value_len = \
                    p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.len;

                ble_gatts_rw_authorize_reply_params_t reply_params;
                memset(&reply_params, 0x00, sizeof(reply_params));

                reply_params.type                = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
                reply_params.params.write.update = 1;
                reply_params.params.write.offset = p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.offset;
                reply_params.params.write.len    = p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.len;
                reply_params.params.write.p_data = p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.data;

                if (wr_req_handle == m_database.ssid_handles.value_handle)
                {
                    NCFGS_TRC("> wr_req: ssid_handle");

                    if ((wr_req_value_len > NCFGS_SSID_MAX_LEN)  || \
                        (wr_req_value_len < NCFGS_SSID_MIN_LEN))
                    {
                        reply_params.params.write.gatt_status = \
                            BLE_GATT_STATUS_ATTERR_INVALID_ATT_VAL_LENGTH;
                    }
                    else
                    {
                        m_ncfgs_data.ssid_from_router.ssid_len = wr_req_value_len;
                        m_service_state |= NCFGS_STATE_SSID_WRITTEN;

                        reply_params.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
                    }

                    UNUSED_RETURN_VALUE( \
                        sd_ble_gatts_rw_authorize_reply(p_ble_evt->evt.gap_evt.conn_handle, \
                                                        &reply_params));
                    NCFGS_TRC("< wr_req: ssid_handle");
                    return;
                }

                else if (wr_req_handle == m_database.keys_store_handles.value_handle)
                {
                    NCFGS_TRC("> wr_req: keys_store_handle");

                    if (wr_req_value_len > NCFGS_KEYS_MAX_LEN)
                    {
                        reply_params.params.write.gatt_status  = \
                            BLE_GATT_STATUS_ATTERR_INVALID_ATT_VAL_LENGTH;
                    }
                    else
                    {
                        m_ncfgs_data.keys_from_router.keys_len = wr_req_value_len;
                        m_service_state |= NCFGS_STATE_KEYS_STORE_WRITTEN;
                        reply_params.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
                    }

                    UNUSED_RETURN_VALUE( \
                        sd_ble_gatts_rw_authorize_reply(p_ble_evt->evt.gap_evt.conn_handle, \
                                                        &reply_params));
                    NCFGS_TRC("< wr_req: keys_store_handle");
                    return;
                }

                else if (wr_req_handle == m_database.ctrlp_handles.value_handle)
                {
                    NCFGS_TRC("> wr_req: ctrlp_handle");

                    bool notify_app = false;

                    if ((wr_req_value_len > NCFGS_CTRLP_VALUE_LEN)            || \
                        (wr_req_value_len < NCFGS_CTRLP_ALL_BUT_ID_DATA_LEN))
                    {
                        reply_params.params.write.gatt_status = \
                            BLE_GATT_STATUS_ATTERR_INVALID_ATT_VAL_LENGTH;
                    }
                    else
                    {
                        ble_ncfgs_opcode_t opcode_in = (ble_ncfgs_opcode_t) \
                            p_ble_evt->evt.gatts_evt.params.authorize_request.request.write.data[0];

                        reply_params.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;

                        if ((opcode_in != NCFGS_OPCODE_GOTO_JOINING_MODE)      &&  \
                            (opcode_in != NCFGS_OPCODE_GOTO_CONFIG_MODE)       &&  \
                            (opcode_in != NCFGS_OPCODE_GOTO_IDENTITY_MODE))
                        {
                            reply_params.params.write.gatt_status = APP_GATTERR_UNKNOWN_OPCODE;
                        }

                        if (opcode_in == NCFGS_OPCODE_GOTO_JOINING_MODE)
                        {
                            if (!((m_service_state & NCFGS_STATE_SSID_WRITTEN)         && \
                                  (m_service_state & NCFGS_STATE_KEYS_STORE_WRITTEN)))
                            {
                                reply_params.params.write.gatt_status = APP_GATTERR_NOT_CONFIGURED;
                            }
                        }

                        if (reply_params.params.write.gatt_status == BLE_GATT_STATUS_SUCCESS)
                        {
                            uint32_t err_code = ctrlp_value_decode(p_ble_evt);
                            if (err_code != NRF_SUCCESS)
                            {
                                reply_params.params.write.gatt_status = \
                                    APP_GATTERR_INVALID_ATTR_VALUE;
                            }
                            else
                            {
                                notify_app = true;
                            }
                        }
                    }

                    UNUSED_RETURN_VALUE(sd_ble_gatts_rw_authorize_reply(
                                            p_ble_evt->evt.gap_evt.conn_handle,
                                            &reply_params));

                    if (notify_app == true)
                    {
                        NCFGS_TRC("> do notify parent");

                        m_app_evt_handler(&m_ncfgs_data);

                        NCFGS_TRC("< do notify parent");
                    }
                    NCFGS_TRC("< wr_req: ctrlp_handle");
                }
                else
                {
                    // Invalid handle.
                    reply_params.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_INVALID_HANDLE;
                    UNUSED_RETURN_VALUE(sd_ble_gatts_rw_authorize_reply(
                                            p_ble_evt->evt.gap_evt.conn_handle, &reply_params));
                }
            }

            break;
        }

        case BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST:
        {
            ble_gap_data_length_params_t dl_params;

            // Clearing the struct will effectively set members to @ref BLE_GAP_DATA_LENGTH_AUTO.
            memset(&dl_params, 0, sizeof(ble_gap_data_length_params_t));
            UNUSED_RETURN_VALUE(sd_ble_gap_data_length_update(p_ble_evt->evt.gap_evt.conn_handle, &dl_params, NULL));
            break;
        }

        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
        {
            NCFGS_TRC("> PHY update request.");

            ble_gap_phys_t const phys =
            {
                .rx_phys = BLE_GAP_PHY_AUTO,
                .tx_phys = BLE_GAP_PHY_AUTO,
            };

            UNUSED_RETURN_VALUE(sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle, &phys);

            NCFGS_TRC("< PHY update request.");
            break;
        }

        default:
        {
            break;
        }
    }
}

#endif // COMMISSIONING_ENABLED
