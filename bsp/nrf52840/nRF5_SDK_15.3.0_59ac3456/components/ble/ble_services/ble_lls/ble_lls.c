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
#if NRF_MODULE_ENABLED(BLE_LLS)
#include "ble_lls.h"
#include <string.h>
#include "ble_hci.h"
#include "ble_srv_common.h"


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_lls   Link Loss Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_lls_t * p_lls, ble_evt_t const * p_ble_evt)
{
    // Link reconnected, notify application with a no_alert event
    ble_lls_evt_t evt;

    p_lls->conn_handle     = p_ble_evt->evt.gap_evt.conn_handle;

    evt.evt_type           = BLE_LLS_EVT_LINK_LOSS_ALERT;
    evt.params.alert_level = BLE_CHAR_ALERT_LEVEL_NO_ALERT;
    p_lls->evt_handler(p_lls, &evt);
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_lls       Link Loss Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_lls_t * p_lls, ble_evt_t const * p_ble_evt)
{
    uint8_t reason = p_ble_evt->evt.gap_evt.params.disconnected.reason;

    if (reason == BLE_HCI_CONNECTION_TIMEOUT)
    {
        // Link loss detected, notify application
        uint32_t      err_code;
        ble_lls_evt_t evt;

        evt.evt_type = BLE_LLS_EVT_LINK_LOSS_ALERT;

        err_code = ble_lls_alert_level_get(p_lls, &evt.params.alert_level);
        if (err_code == NRF_SUCCESS)
        {
            p_lls->evt_handler(p_lls, &evt);
        }
        else
        {
            if (p_lls->error_handler != NULL)
            {
                p_lls->error_handler(err_code);
            }
        }
    }
}


/**@brief Function for handling the Authentication Status event.
 *
 * @param[in]   p_lls       Link Loss Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_auth_status(ble_lls_t * p_lls, ble_evt_t const * p_ble_evt)
{
    if (p_ble_evt->evt.gap_evt.params.auth_status.auth_status == BLE_GAP_SEC_STATUS_SUCCESS)
    {
        ble_lls_evt_t evt;

        evt.evt_type           = BLE_LLS_EVT_LINK_LOSS_ALERT;
        evt.params.alert_level = BLE_CHAR_ALERT_LEVEL_NO_ALERT;

        p_lls->evt_handler(p_lls, &evt);
    }
}


void ble_lls_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_lls_t * p_lls = (ble_lls_t *)p_context;

    if (p_lls == NULL || p_ble_evt == NULL)
    {
        return;
    }

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_lls, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_lls, p_ble_evt);
            break;

        case BLE_GAP_EVT_AUTH_STATUS:
            on_auth_status(p_lls, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


uint32_t ble_lls_init(ble_lls_t * p_lls, const ble_lls_init_t * p_lls_init)
{
    uint32_t              err_code;
    ble_uuid_t            ble_uuid;
    ble_add_char_params_t add_char_params;

    if (p_lls == NULL || p_lls_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_lls_init->evt_handler == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Initialize service structure
    p_lls->evt_handler   = p_lls_init->evt_handler;
    p_lls->error_handler = p_lls_init->error_handler;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_LINK_LOSS_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_lls->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add alert level characteristic
    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid             = BLE_UUID_ALERT_LEVEL_CHAR;
    add_char_params.max_len          = sizeof(uint8_t);
    add_char_params.char_props.read  = 1;
    add_char_params.char_props.write = 1;
    add_char_params.write_access     = p_lls_init->alert_level_wr_sec;
    add_char_params.read_access      = p_lls_init->alert_level_rd_sec;
    add_char_params.init_len         = sizeof(uint8_t);
    add_char_params.p_init_value     = (uint8_t *) &(p_lls_init->initial_alert_level);

    return characteristic_add(p_lls->service_handle,
                              &add_char_params,
                              &p_lls->alert_level_handles);
}


uint32_t ble_lls_alert_level_get(ble_lls_t * p_lls, uint8_t * p_alert_level)
{
    ble_gatts_value_t gatts_value;

    if (p_lls == NULL || p_alert_level == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = sizeof(uint8_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = p_alert_level;

    return sd_ble_gatts_value_get(p_lls->conn_handle,
                                  p_lls->alert_level_handles.value_handle,
                                  &gatts_value);
}
#endif // NRF_MODULE_ENABLED(BLE_LLS)
