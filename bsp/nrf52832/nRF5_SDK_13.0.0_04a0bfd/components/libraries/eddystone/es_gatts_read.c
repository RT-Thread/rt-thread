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

#include "es_gatts_read.h"
#include "es_adv.h"
#include "es_gatts.h"
#include "es_security.h"
#include "es_slot.h"

static ret_code_t send_read_reply(nrf_ble_escs_t * p_escs, ble_gatts_rw_authorize_reply_params_t * p_reply)
{
    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_reply);

    p_reply->type               = BLE_GATTS_AUTHORIZE_TYPE_READ;
    p_reply->params.read.update = 1;
    p_reply->params.read.offset = 0;

    return es_gatts_send_reply(p_escs, p_reply);
}


static ret_code_t read_value(nrf_ble_escs_t * p_escs, uint8_t length, const void * p_value)
{
    VERIFY_PARAM_NOT_NULL(p_escs);
    VERIFY_PARAM_NOT_NULL(p_value);

    ble_gatts_rw_authorize_reply_params_t reply = {0};
    reply.params.read.len                       = length;
    reply.params.read.p_data                    = p_value;
    reply.params.read.gatt_status               = BLE_GATT_STATUS_SUCCESS;

    return send_read_reply(p_escs, &reply);
}


static ret_code_t read_from_gattdb(nrf_ble_escs_t * p_escs, uint16_t val_handle)
{
    VERIFY_PARAM_NOT_NULL(p_escs);

    ret_code_t err_code;

    // Go straight to the characteristic
    uint8_t           value_buffer[ESCS_ADV_SLOT_CHAR_LENGTH_MAX] = {0};
    ble_gatts_value_t value = {.len = sizeof(value_buffer),
                               .offset = 0,
                               .p_value = &(value_buffer[0])};

    err_code = sd_ble_gatts_value_get(p_escs->conn_handle, val_handle, &value);
    RETURN_IF_ERROR(err_code);

    return read_value(p_escs, value.len, value.p_value);
}


static ret_code_t read_adv_slot(nrf_ble_escs_t * p_escs, uint8_t active_slot, const es_slot_reg_t * p_reg)
{
    VERIFY_PARAM_NOT_NULL(p_escs);

    ble_gatts_rw_authorize_reply_params_t reply = {0};
    uint8_t                               eid_buf[14];

    // If an EID slot is read, load scaler, clock value and ephemeral ID.
    if (p_reg->slots[active_slot].adv_frame.type == ES_FRAME_TYPE_EID)
    {
        /*lint -save -e666 */
        uint32_t clock_value = es_security_clock_get(active_slot);
        clock_value          = BYTES_REVERSE_32BIT(clock_value);
        /*lint -restore */

        reply.params.read.len = ES_EID_GATTS_READ_LENGTH;

        // Fill EID buffer with data
        eid_buf[ES_EID_GATTS_READ_FRAME_TYPE_IDX] = ES_FRAME_TYPE_EID;
        eid_buf[ES_EID_GATTS_READ_EXPONENT_IDX]   = es_security_scaler_get(active_slot);

        memcpy(&eid_buf[ES_EID_GATTS_READ_CLCK_VALUE_IDX], &clock_value, sizeof(clock_value));
        /*lint -save -e545 */
        memcpy(&eid_buf[ES_EID_GATTS_READ_EID_IDX],
               &p_reg->slots[active_slot].adv_frame.frame.eid.eid,
               ES_EID_ID_LENGTH);
        /*lint -restore */
        reply.params.read.p_data = eid_buf;
    }

    // Otherwise, simply load the contents of the frame.
    else
    {
        // Check if slot being read is an eTLM slot.
        if ((p_reg->num_configured_eid_slots > 0) && p_reg->tlm_configured && (p_reg->tlm_slot == active_slot))
        {
            // Fill eTLM slot using EID key from first EID slot.
            es_slot_etlm_update(p_reg->eid_slots_configured[0]);
        }
        reply.params.read.len    = p_reg->slots[active_slot].adv_frame.length;
        reply.params.read.p_data = (uint8_t *)&p_reg->slots[active_slot].adv_frame.frame;
    }

    reply.params.read.gatt_status = BLE_GATT_STATUS_SUCCESS;

    return send_read_reply(p_escs, &reply);
}


ret_code_t es_gatts_read_handle_locked_read(nrf_ble_escs_t * p_escs, uint16_t uuid, uint8_t lock_state)
{
    VERIFY_PARAM_NOT_NULL(p_escs);

    if (uuid == BLE_UUID_ESCS_REMAIN_CONNECTABLE_CHAR)
    {
        uint8_t retval = APP_IS_REMAIN_CONNECTABLE_SUPPORTED;
        return read_value(p_escs, sizeof(retval), &retval);
    }

    else if (uuid == BLE_UUID_ESCS_LOCK_STATE_CHAR)
    {
        return read_value(p_escs, sizeof(lock_state), &lock_state);
    }

    else
    {
        return es_gatts_send_op_not_permitted(p_escs, true);
    }
}


ret_code_t es_gatts_read_handle_unlock(nrf_ble_escs_t * p_escs)
{
    VERIFY_PARAM_NOT_NULL(p_escs);

    ret_code_t err_code;
    uint8_t    key_buff[ESCS_AES_KEY_SIZE];

    err_code = es_security_random_challenge_generate(key_buff);
    RETURN_IF_ERROR(err_code);

    es_security_unlock_prepare(key_buff);

    return read_value(p_escs, ESCS_AES_KEY_SIZE, key_buff);
}


ret_code_t es_gatts_read_handle_unlocked_read(nrf_ble_escs_t * p_escs,
                                              uint16_t         uuid,
                                              uint16_t         val_handle,
                                              uint8_t          active_slot,
                                              uint8_t          lock_state)
{
    VERIFY_PARAM_NOT_NULL(p_escs);

    const es_slot_reg_t * p_reg = es_slot_get_registry();

    switch (uuid)
    {
        case BLE_UUID_ESCS_BROADCAST_CAP_CHAR:
        case BLE_UUID_ESCS_UNLOCK_CHAR:
        case BLE_UUID_ESCS_PUBLIC_ECDH_KEY_CHAR:
        case BLE_UUID_ESCS_ACTIVE_SLOT_CHAR:
            return read_from_gattdb(p_escs, val_handle);

        case BLE_UUID_ESCS_LOCK_STATE_CHAR:
            return read_value(p_escs, sizeof(lock_state), &lock_state);

        case BLE_UUID_ESCS_ADV_INTERVAL_CHAR:
        {
            nrf_ble_escs_adv_interval_t adv_interval = es_adv_interval_get();
            adv_interval                             = BYTES_SWAP_16BIT(adv_interval);
            return read_value(p_escs, sizeof(adv_interval), &adv_interval);
        }

        case BLE_UUID_ESCS_RADIO_TX_PWR_CHAR:
            return read_value(p_escs,
                              sizeof(nrf_ble_escs_radio_tx_pwr_t),
                              &p_reg->slots[active_slot].radio_tx_pwr);

        case BLE_UUID_ESCS_ADV_TX_PWR_CHAR:
            return read_value(p_escs,
                              sizeof(nrf_ble_escs_radio_tx_pwr_t),
                              p_reg->slots[active_slot].adv_custom_tx_power
                                  ? (uint8_t *)(&p_reg->slots[active_slot].custom_tx_power)
                                  : (uint8_t *)(&p_reg->slots[active_slot].radio_tx_pwr));

        case BLE_UUID_ESCS_REMAIN_CONNECTABLE_CHAR:
        {
            uint8_t retval = APP_IS_REMAIN_CONNECTABLE_SUPPORTED;
            return read_value(p_escs, sizeof(retval), &retval);
        }

        case BLE_UUID_ESCS_EID_ID_KEY_CHAR:
            if (p_reg->slots[active_slot].configured &&
                (p_reg->slots[active_slot].adv_frame.type == ES_FRAME_TYPE_EID))
            {
                return read_value(p_escs,
                                  sizeof(nrf_ble_escs_eid_id_key_t),
                                  &p_reg->slots[active_slot].encrypted_eid_id_key);
            }

            else
            {
                return es_gatts_send_op_not_permitted(p_escs, true);
            }

        case BLE_UUID_ESCS_RW_ADV_SLOT_CHAR:
            return read_adv_slot(p_escs, active_slot, p_reg);

        default:
            return NRF_ERROR_INVALID_PARAM;
    }
}
