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
#if NRF_MODULE_ENABLED(BLE_TPS)
#include "ble_tps.h"
#include <string.h>
#include "ble_srv_common.h"


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_tps       TX Power Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_tps_t * p_tps, ble_evt_t const * p_ble_evt)
{
    p_tps->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


void ble_tps_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_tps_t * p_tps = (ble_tps_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_tps, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


uint32_t ble_tps_init(ble_tps_t * p_tps, const ble_tps_init_t * p_tps_init)
{
    uint32_t              err_code;
    ble_uuid_t            ble_uuid;
    ble_add_char_params_t add_char_params;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_TX_POWER_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_tps->service_handle);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add TX Power Level characteristic
    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid            = BLE_UUID_TX_POWER_LEVEL_CHAR;
    add_char_params.max_len         = sizeof(uint8_t);
    add_char_params.init_len        = sizeof(uint8_t);
    add_char_params.p_init_value    = (uint8_t *) &p_tps_init->initial_tx_power_level;
    add_char_params.char_props.read = 1;
    add_char_params.read_access     = p_tps_init->tpl_rd_sec;

    return characteristic_add(p_tps->service_handle,
                              &add_char_params,
                              &p_tps->tx_power_level_handles);
}


uint32_t ble_tps_tx_power_level_set(ble_tps_t * p_tps, int8_t tx_power_level)
{
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = sizeof(uint8_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = (uint8_t*)&tx_power_level;

    // Update database
    return sd_ble_gatts_value_set(p_tps->conn_handle,
                                  p_tps->tx_power_level_handles.value_handle,
                                  &gatts_value);
}
#endif // NRF_MODULE_ENABLED(BLE_TPS)
