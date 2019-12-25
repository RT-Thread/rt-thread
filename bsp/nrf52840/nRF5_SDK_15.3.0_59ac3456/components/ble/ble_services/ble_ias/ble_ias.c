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
#if NRF_MODULE_ENABLED(BLE_IAS)
#include "ble_ias.h"
#include <string.h>
#include "ble_srv_common.h"

#define NRF_LOG_MODULE_NAME ble_ias
#if BLE_IAS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       BLE_IAS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  BLE_IAS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR BLE_IAS_CONFIG_DEBUG_COLOR
#else // BLE_IAS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // BLE_IAS_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#define INITIAL_ALERT_LEVEL BLE_CHAR_ALERT_LEVEL_NO_ALERT


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_ias       Immediate Alert Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_ias_t * p_ias, ble_evt_t const * p_ble_evt)
{
    ret_code_t                 err_code;
    ble_ias_client_context_t * p_client = NULL;

    err_code = blcm_link_ctx_get(p_ias->p_link_ctx_storage,
                                 p_ble_evt->evt.gap_evt.conn_handle,
                                 (void *) &p_client);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.",
                      p_ble_evt->evt.gap_evt.conn_handle);
    }
    else
    {
        p_client->alert_level = INITIAL_ALERT_LEVEL;
    }
}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_ias       Immediate Alert Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_ias_t * p_ias, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if ((p_evt_write->handle == p_ias->alert_level_handles.value_handle) && (p_evt_write->len == 1))
    {
        // Alert level written, call application event handler
        ret_code_t                 err_code;
        ble_ias_evt_t              evt;
        ble_ias_client_context_t * p_client;

        err_code = blcm_link_ctx_get(p_ias->p_link_ctx_storage,
                                     p_ble_evt->evt.gatts_evt.conn_handle,
                                     (void *) &p_client);
        if (err_code != NRF_SUCCESS)
        {
            NRF_LOG_ERROR("Link context for 0x%02X connection handle could not be fetched.",
                          p_ble_evt->evt.gatts_evt.conn_handle);
        }
        else
        {
            p_client->alert_level = p_evt_write->data[0];
        }

        evt.evt_type    = BLE_IAS_EVT_ALERT_LEVEL_UPDATED;
        evt.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;
        evt.p_link_ctx  = p_client;

        p_ias->evt_handler(p_ias, &evt);
    }
}


void ble_ias_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_ias_t * p_ias = (ble_ias_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_ias, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_ias, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


uint32_t ble_ias_init(ble_ias_t * p_ias, const ble_ias_init_t * p_ias_init)
{
    uint32_t              err_code;
    uint8_t               initial_alert_level;
    ble_uuid_t            ble_uuid;
    ble_add_char_params_t add_char_params;

    // Initialize service structure
    if (p_ias_init->evt_handler == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    p_ias->evt_handler = p_ias_init->evt_handler;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_IMMEDIATE_ALERT_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_ias->service_handle);
    VERIFY_SUCCESS(err_code);

    // Add alert level characteristic
    initial_alert_level = INITIAL_ALERT_LEVEL;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                     = BLE_UUID_ALERT_LEVEL_CHAR;
    add_char_params.max_len                  = sizeof (uint8_t);
    add_char_params.init_len                 = sizeof (uint8_t);
    add_char_params.p_init_value             = &initial_alert_level;
    add_char_params.char_props.write_wo_resp = 1;
    add_char_params.write_access             = p_ias_init->alert_wr_sec;

    return characteristic_add(p_ias->service_handle,
                              &add_char_params,
                              &p_ias->alert_level_handles);
}


uint32_t ble_ias_alert_level_get(ble_ias_t * p_ias, uint16_t conn_handle, uint8_t * p_alert_level)
{
    ret_code_t                 err_code;
    ble_ias_client_context_t * p_client;

    err_code = blcm_link_ctx_get(p_ias->p_link_ctx_storage, conn_handle, (void *) &p_client);
    VERIFY_SUCCESS(err_code);

    *p_alert_level = p_client->alert_level;
    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(BLE_IAS)
