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
#include "nrf_ble_escs.h"
#include <string.h>
#include "es_app_config.h"

#ifdef BLE_HANDLER_DEBUG
    #include "SEGGER_RTT.h"
    #define DEBUG_PRINTF SEGGER_RTT_printf
#else
    #define DEBUG_PRINTF(...)
#endif

#define EID_BUFF_SIZE       64

typedef struct
{
    uint16_t uuid;
    uint8_t read:1;
    uint8_t write:1;
    uint8_t rd_auth:1;
    uint8_t wr_auth:1;
    uint8_t vlen:1;
    uint8_t vloc:2;
    uint8_t init_len;
    uint8_t max_len;
} char_init_t;

typedef struct
{
    uint16_t val_handle;
    uint16_t uuid;
} val_handle_to_uuid_t;

static const char_init_t BROADCAST_CAP_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_BROADCAST_CAP_CHAR,
    .read = 1,
    .write = 0,
    .rd_auth = 1,
    .wr_auth = 0,
    .vlen = 1,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = NRF_BLE_ESCS_BROADCAST_CAP_LEN,
    .max_len = NRF_BLE_ESCS_BROADCAST_CAP_LEN
};

static const char_init_t ACTIVE_SLOT_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_ACTIVE_SLOT_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_USER,
    .init_len = sizeof(nrf_ble_escs_active_slot_t),
    .max_len = sizeof(nrf_ble_escs_active_slot_t)
};

static const char_init_t ADV_INTERVAL_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_ADV_INTERVAL_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = sizeof(nrf_ble_escs_adv_interval_t),
    .max_len = sizeof(nrf_ble_escs_adv_interval_t)
};

static const char_init_t RADIO_TX_PWR_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_RADIO_TX_PWR_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = sizeof(nrf_ble_escs_radio_tx_pwr_t),
    .max_len = sizeof(nrf_ble_escs_radio_tx_pwr_t)
};

static const char_init_t ADV_TX_PWR_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_ADV_TX_PWR_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = sizeof(nrf_ble_escs_adv_tx_pwr_t),
    .max_len = sizeof(nrf_ble_escs_adv_tx_pwr_t)
};

static const char_init_t LOCK_STATE_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_LOCK_STATE_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 1,
    .vloc = BLE_GATTS_VLOC_USER,
    .init_len = 1,
    .max_len = 17
};

static const char_init_t UNLOCK_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_UNLOCK_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = 1,
    .max_len = ESCS_AES_KEY_SIZE
};

static const char_init_t PUBLIC_ECDH_KEY_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_PUBLIC_ECDH_KEY_CHAR,
    .read = 1,
    .write = 0,
    .rd_auth = 1,
    .wr_auth = 0,
    .vlen = 1,
    .init_len = 1,
    .vloc = BLE_GATTS_VLOC_STACK,
    .max_len = ESCS_ECDH_KEY_SIZE
};

static const char_init_t EID_ID_KEY_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_EID_ID_KEY_CHAR,
    .read = 1,
    .write = 0,
    .rd_auth = 1,
    .wr_auth = 0,
    .vlen = 1,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = 1,
    .max_len = ESCS_AES_KEY_SIZE
};

static const char_init_t RW_ADV_SLOT_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_RW_ADV_SLOT_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 1,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = 0,
    .max_len = ESCS_ADV_SLOT_CHAR_LENGTH_MAX
};

static const char_init_t FACTORY_RESET_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_FACTORY_RESET_CHAR,
    .read = 0,
    .write = 1,
    .rd_auth = 0,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = sizeof(nrf_ble_escs_factory_reset_t),
    .max_len = sizeof(nrf_ble_escs_factory_reset_t)
};

static const char_init_t REMAIN_CONNECTABLE_CHAR_INIT =
{
    .uuid = BLE_UUID_ESCS_REMAIN_CONNECTABLE_CHAR,
    .read = 1,
    .write = 1,
    .rd_auth = 1,
    .wr_auth = 1,
    .vlen = 0,
    .vloc = BLE_GATTS_VLOC_STACK,
    .init_len = 1,
    .max_len = 1
};

static val_handle_to_uuid_t m_handle_to_uuid_map[BLE_ESCS_NUMBER_OF_CHARACTERISTICS]; //!< Map from handle to UUID.
static uint8_t              m_handle_to_uuid_map_idx = 0;   //!< Index of map from handle to UUID.
static uint8_t              m_eid_mem[EID_BUFF_SIZE] = {0}; //!< Memory buffer used for EID writes.
static ble_user_mem_block_t m_eid_mem_block =
{
    .p_mem = m_eid_mem,
    .len = EID_BUFF_SIZE
};                                                          //!<  Memory block used for EID writes.



/**@brief Function for adding characteristic to Eddystone service.
 *
 * @param[in] p_escs       Eddystone Configuration Service structure.
 * @param[in] p_escs_init  Information needed to initialize the service.
 * @param[in] p_char_init  Information needed to initialize the characteristic.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t char_add(const char_init_t        * p_char_init,
                         nrf_ble_escs_t           * p_escs,
                         void                     * p_value,
                         ble_gatts_char_handles_t * p_handles)
{
    uint32_t err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    VERIFY_PARAM_NOT_NULL(p_char_init);
    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_value);
    VERIFY_PARAM_NOT_NULL(p_handles);

    memset(&char_md, 0, sizeof(char_md));
    memset(&attr_char_value, 0, sizeof(attr_char_value));
    memset(&ble_uuid, 0, sizeof(ble_uuid));
    memset(&attr_md, 0, sizeof(attr_md));

    if(p_char_init->read)
    {
        char_md.char_props.read  = 1;
        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    }

    else
    {
        BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    }

    if(p_char_init->write)
    {
        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
        char_md.char_props.write  = 1;
    }

    else
    {
        BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);
    }

    ble_uuid.type = p_escs->uuid_type;
    ble_uuid.uuid = p_char_init->uuid;

    attr_md.vloc    = p_char_init->vloc;
    attr_md.rd_auth = p_char_init->rd_auth;
    attr_md.wr_auth = p_char_init->wr_auth;
    attr_md.vlen    = p_char_init->vlen;

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = p_char_init->init_len;
    attr_char_value.p_value   = p_value;
    attr_char_value.max_len   = p_char_init->max_len;

    err_code = sd_ble_gatts_characteristic_add(p_escs->service_handle,
                                               &char_md,
                                               &attr_char_value,
                                               p_handles);

    if(err_code == NRF_SUCCESS)
    {
        ASSERT(m_handle_to_uuid_map_idx < BLE_ESCS_NUMBER_OF_CHARACTERISTICS);
        m_handle_to_uuid_map[m_handle_to_uuid_map_idx].val_handle = p_handles->value_handle;
        m_handle_to_uuid_map[m_handle_to_uuid_map_idx].uuid = p_char_init->uuid;
        m_handle_to_uuid_map_idx++;
    }

    return err_code;
}


/**@brief Function for handling the @ref BLE_GAP_EVT_CONNECTED event from the SoftDevice.
 *
 * @param[in] p_escs     Eddystone Configuration Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_connect(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_escs);
    p_escs->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


/**@brief Function for handling the @ref BLE_GAP_EVT_DISCONNECTED event from the SoftDevice.
 *
 * @param[in] p_escs    Eddystone Configuration Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_disconnect(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_escs);
    UNUSED_PARAMETER(p_ble_evt);
    p_escs->conn_handle = BLE_CONN_HANDLE_INVALID;
}


static uint32_t get_evt_type_for_handle(uint16_t handle, uint16_t * p_uuid)
{
    VERIFY_PARAM_NOT_NULL(p_uuid);

    for(uint8_t i = 0; i < BLE_ESCS_NUMBER_OF_CHARACTERISTICS; ++i)
    {
        if(m_handle_to_uuid_map[i].val_handle == handle)
        {
            *p_uuid = m_handle_to_uuid_map[i].uuid;
            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NOT_FOUND;
}

/**@brief Function for handling the @ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST: BLE_GATTS_AUTHORIZE_TYPE_WRITE event from the SoftDevice.
 *
 * @param[in] p_escs     Eddystone Configuration Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static ret_code_t on_write(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    uint32_t err_code;
    uint16_t write_evt_uuid = 0;

    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_ble_evt);

    ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.authorize_request.request.write;

    err_code = get_evt_type_for_handle(p_evt_write->handle, &write_evt_uuid);
    RETURN_IF_ERROR(err_code);

    p_escs->write_evt_handler(p_escs,
                              write_evt_uuid,
                              p_evt_write->handle,
                              p_evt_write->data,
                              p_evt_write->len);

    return NRF_SUCCESS;
}


/**@brief Function for handling the @ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST: BLE_GATTS_AUTHORIZE_TYPE_WRITE:  event from the SoftDevice.
 *
 * @param[in] p_escs     Eddystone Configuration Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_long_write(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    static uint16_t write_evt_uuid;
    static bool write_evt_uuid_set = false;
    uint32_t err_code;

    VERIFY_PARAM_NOT_NULL_VOID(p_escs);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    ble_gatts_evt_write_t * p_evt_write =
        &p_ble_evt->evt.gatts_evt.params.authorize_request.request.write;
    ble_gatts_rw_authorize_reply_params_t reply = {0};

    if (p_evt_write->op == BLE_GATTS_OP_PREP_WRITE_REQ)
    {
        err_code = get_evt_type_for_handle(p_evt_write->handle, &write_evt_uuid);
        APP_ERROR_CHECK(err_code);

        write_evt_uuid_set = true;

        reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
        reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        reply.params.write.update      = 0;
        reply.params.write.offset      = 0;
        reply.params.write.len         = p_evt_write->len;
        reply.params.write.p_data      = NULL;

        err_code = sd_ble_gatts_rw_authorize_reply(p_escs->conn_handle, &reply);
        APP_ERROR_CHECK(err_code);
    }

    else if (p_evt_write->op == BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)
    {
        uint8_t           value_buffer[ESCS_ADV_SLOT_CHAR_LENGTH_MAX] = {0};
        ble_gatts_value_t value =
        {
            .len = sizeof(value_buffer),
            .offset = 0,
            .p_value = &(value_buffer[0])
        };

        ASSERT(write_evt_uuid_set);
        write_evt_uuid_set = false;

        reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
        reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        reply.params.write.update      = 0;
        reply.params.write.offset      = 0;
        reply.params.write.len         = p_evt_write->len;
        reply.params.write.p_data      = NULL;

        err_code = sd_ble_gatts_rw_authorize_reply(p_escs->conn_handle, &reply);
        APP_ERROR_CHECK(err_code);

        // Now that the value has been accepted using 'sd_ble_gatts_rw_authorize_reply', it can be found in the database.
        err_code = sd_ble_gatts_value_get(  p_escs->conn_handle,
                                            p_escs->rw_adv_slot_handles.value_handle,
                                            &value);
        APP_ERROR_CHECK(err_code);

        p_escs->write_evt_handler(p_escs,
                                  write_evt_uuid,
                                  p_evt_write->handle,
                                  value.p_value,
                                  value.len);
    }
    else
    {
    }
}


/**@brief Function for handling events from the SoftDevice related to long writes.
 *
 * @param[in] p_escs     Eddystone Configuration Service structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static ret_code_t on_read(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_ble_evt);
    ret_code_t err_code;
    uint16_t read_evt_uuid = 0;
    uint16_t val_handle = p_ble_evt->evt.gatts_evt.params.authorize_request.request.read.handle;
    err_code = get_evt_type_for_handle(val_handle, &read_evt_uuid);
    RETURN_IF_ERROR(err_code);

    p_escs->read_evt_handler(p_escs, read_evt_uuid, val_handle);

    return NRF_SUCCESS;
}


static ret_code_t on_rw_authorize_req(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    ret_code_t err_code;
    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_ble_evt);

    ble_gatts_evt_rw_authorize_request_t *ar = &p_ble_evt->evt.gatts_evt.params.authorize_request;
    if (ar->type == BLE_GATTS_AUTHORIZE_TYPE_READ)
    {
        err_code = on_read(p_escs, p_ble_evt);
        RETURN_IF_ERROR(err_code);
    }
    else if (ar->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        if (ar->request.write.op == BLE_GATTS_OP_WRITE_REQ
         || ar->request.write.op == BLE_GATTS_OP_WRITE_CMD)
        {
            err_code = on_write(p_escs, p_ble_evt);
            RETURN_IF_ERROR(err_code);
        }

        else if(ar->request.write.op == BLE_GATTS_OP_PREP_WRITE_REQ
             || ar->request.write.op == BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)
        {
            on_long_write(p_escs, p_ble_evt);
        }
        else
        {
        }
    }
    else
    {
        return NRF_ERROR_INVALID_STATE;
    }

    return NRF_SUCCESS;
}



ret_code_t nrf_ble_escs_on_ble_evt(nrf_ble_escs_t * p_escs, ble_evt_t * p_ble_evt)
{
    ret_code_t err_code;

    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_escs, p_ble_evt);

            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_escs, p_ble_evt);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            err_code = on_rw_authorize_req(p_escs, p_ble_evt);
            VERIFY_SUCCESS(err_code);
            break;

        // BLE_EVT_USER_MEM_REQUEST & BLE_EVT_USER_MEM_RELEASE are for long writes to the RW ADV slot characteristic
        case BLE_EVT_USER_MEM_REQUEST:
            err_code = sd_ble_user_mem_reply(p_escs->conn_handle, &m_eid_mem_block);
            VERIFY_SUCCESS(err_code);
            break;

        case BLE_EVT_USER_MEM_RELEASE:
            break;

        default:
            // No implementation needed.
            break;
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_escs_init(nrf_ble_escs_t * p_escs, const nrf_ble_escs_init_t * p_escs_init)
{
    uint32_t      err_code;
    ble_uuid_t    ble_uuid;
    ble_uuid128_t ecs_base_uuid = ESCS_BASE_UUID;
    uint8_t       zero_val = 0;

    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_escs_init);

    // Initialize the service structure.
    p_escs->conn_handle       = BLE_CONN_HANDLE_INVALID;
    p_escs->write_evt_handler = p_escs_init->write_evt_handler;
    p_escs->read_evt_handler  = p_escs_init->read_evt_handler;

    // Add a custom base UUID.
    err_code = sd_ble_uuid_vs_add(&ecs_base_uuid, &p_escs->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_escs->uuid_type;
    ble_uuid.uuid = BLE_UUID_ESCS_SERVICE;

    // Add the service.
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_escs->service_handle);
    VERIFY_SUCCESS(err_code);

    m_handle_to_uuid_map_idx = 0;

    // Set up initial values for characteristics

    // Eddystone spec requires big endian
    nrf_ble_escs_broadcast_cap_t temp = p_escs_init->p_init_vals->broadcast_cap;
    temp.supp_frame_types = BYTES_SWAP_16BIT(temp.supp_frame_types);

    nrf_ble_escs_adv_interval_t temp_interval = p_escs_init->p_init_vals->adv_interval;
    temp_interval = BYTES_SWAP_16BIT(temp_interval);

    // Adding chracteristics

    err_code = char_add(&BROADCAST_CAP_CHAR_INIT, p_escs,
                        &temp, &p_escs->broadcast_cap_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&ACTIVE_SLOT_CHAR_INIT, p_escs,
                        p_escs->p_active_slot, &p_escs->active_slot_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&ADV_INTERVAL_CHAR_INIT, p_escs,
                        &temp_interval, &p_escs->adv_interval_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&RADIO_TX_PWR_CHAR_INIT, p_escs,
                        &(p_escs_init->p_init_vals->radio_tx_pwr), &p_escs->radio_tx_pwr_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&ADV_TX_PWR_CHAR_INIT, p_escs,
                        &(p_escs_init->p_init_vals->adv_tx_pwr), &p_escs->adv_tx_pwr_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&LOCK_STATE_CHAR_INIT, p_escs,
                        p_escs->p_lock_state, &p_escs->lock_state_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&UNLOCK_CHAR_INIT, p_escs,
                        &zero_val, &p_escs->unlock_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&PUBLIC_ECDH_KEY_CHAR_INIT,  p_escs,
                        &zero_val, &p_escs->pub_ecdh_key_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&EID_ID_KEY_CHAR_INIT, p_escs,
                        &zero_val, &p_escs->eid_id_key_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&RW_ADV_SLOT_CHAR_INIT, p_escs,
                        &zero_val, &p_escs->rw_adv_slot_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&FACTORY_RESET_CHAR_INIT, p_escs,
                        &(p_escs_init->p_init_vals->factory_reset), &p_escs->factory_reset_handles);
    VERIFY_SUCCESS(err_code);

    err_code = char_add(&REMAIN_CONNECTABLE_CHAR_INIT, p_escs,
                        &(p_escs_init->p_init_vals->remain_connectable.r_is_non_connectable_supported),
                        &p_escs->remain_connectable_handles);
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}
