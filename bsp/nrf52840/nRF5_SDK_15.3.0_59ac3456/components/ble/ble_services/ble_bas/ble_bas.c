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
#if NRF_MODULE_ENABLED(BLE_BAS)
#include "ble_bas.h"
#include <string.h>
#include "ble_srv_common.h"
#include "ble_conn_state.h"

#define NRF_LOG_MODULE_NAME ble_bas
#if BLE_BAS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       BLE_BAS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  BLE_BAS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR BLE_BAS_CONFIG_DEBUG_COLOR
#else // BLE_BAS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // BLE_BAS_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#define INVALID_BATTERY_LEVEL 255


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_bas_t * p_bas, ble_evt_t const * p_ble_evt)
{
    if (!p_bas->is_notification_supported)
    {
        return;
    }

    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (    (p_evt_write->handle == p_bas->battery_level_handles.cccd_handle)
        &&  (p_evt_write->len == 2))
    {
        if (p_bas->evt_handler == NULL)
        {
            return;
        }

        ble_bas_evt_t evt;

        if (ble_srv_is_notification_enabled(p_evt_write->data))
        {
            evt.evt_type = BLE_BAS_EVT_NOTIFICATION_ENABLED;
        }
        else
        {
            evt.evt_type = BLE_BAS_EVT_NOTIFICATION_DISABLED;
        }
        evt.conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;

        // CCCD written, call application event handler.
        p_bas->evt_handler(p_bas, &evt);
    }
}


void ble_bas_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_bas_t * p_bas = (ble_bas_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
            on_write(p_bas, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for adding the Battery Level characteristic.
 *
 * @param[in]   p_bas        Battery Service structure.
 * @param[in]   p_bas_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t battery_level_char_add(ble_bas_t * p_bas, const ble_bas_init_t * p_bas_init)
{
    ret_code_t             err_code;
    ble_add_char_params_t  add_char_params;
    ble_add_descr_params_t add_descr_params;
    uint8_t                initial_battery_level;
    uint8_t                init_len;
    uint8_t                encoded_report_ref[BLE_SRV_ENCODED_REPORT_REF_LEN];

    // Add battery level characteristic
    initial_battery_level = p_bas_init->initial_batt_level;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid              = BLE_UUID_BATTERY_LEVEL_CHAR;
    add_char_params.max_len           = sizeof(uint8_t);
    add_char_params.init_len          = sizeof(uint8_t);
    add_char_params.p_init_value      = &initial_battery_level;
    add_char_params.char_props.notify = p_bas->is_notification_supported;
    add_char_params.char_props.read   = 1;
    add_char_params.cccd_write_access = p_bas_init->bl_cccd_wr_sec;
    add_char_params.read_access       = p_bas_init->bl_rd_sec;

    err_code = characteristic_add(p_bas->service_handle,
                                  &add_char_params,
                                  &(p_bas->battery_level_handles));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (p_bas_init->p_report_ref != NULL)
    {
        // Add Report Reference descriptor
        init_len = ble_srv_report_ref_encode(encoded_report_ref, p_bas_init->p_report_ref);

        memset(&add_descr_params, 0, sizeof(add_descr_params));
        add_descr_params.uuid        = BLE_UUID_REPORT_REF_DESCR;
        add_descr_params.read_access = p_bas_init->bl_report_rd_sec;
        add_descr_params.init_len    = init_len;
        add_descr_params.max_len     = add_descr_params.init_len;
        add_descr_params.p_value     = encoded_report_ref;

        err_code = descriptor_add(p_bas->battery_level_handles.value_handle,
                                  &add_descr_params,
                                  &p_bas->report_ref_handle);
        return err_code;
    }
    else
    {
        p_bas->report_ref_handle = BLE_GATT_HANDLE_INVALID;
    }

    return NRF_SUCCESS;
}


ret_code_t ble_bas_init(ble_bas_t * p_bas, const ble_bas_init_t * p_bas_init)
{
    if (p_bas == NULL || p_bas_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_code_t err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_bas->evt_handler               = p_bas_init->evt_handler;
    p_bas->is_notification_supported = p_bas_init->support_notification;
    p_bas->battery_level_last        = INVALID_BATTERY_LEVEL;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_BATTERY_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_bas->service_handle);
    VERIFY_SUCCESS(err_code);

    // Add battery level characteristic
    err_code = battery_level_char_add(p_bas, p_bas_init);
    return err_code;
}


/**@brief Function for sending notifications with the Battery Level characteristic.
 *
 * @param[in]   p_hvx_params Pointer to structure with notification data.
 * @param[in]   conn_handle  Connection handle.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t battery_notification_send(ble_gatts_hvx_params_t * const p_hvx_params,
                                            uint16_t                       conn_handle)
{
    ret_code_t err_code = sd_ble_gatts_hvx(conn_handle, p_hvx_params);
    if (err_code == NRF_SUCCESS)
    {
        NRF_LOG_INFO("Battery notification has been sent using conn_handle: 0x%04X", conn_handle);
    }
    else
    {
        NRF_LOG_DEBUG("Error: 0x%08X while sending notification with conn_handle: 0x%04X",
                      err_code,
                      conn_handle);
    }
    return err_code;
}


ret_code_t ble_bas_battery_level_update(ble_bas_t * p_bas,
                                        uint8_t     battery_level,
                                        uint16_t    conn_handle)
{
    if (p_bas == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_code_t         err_code = NRF_SUCCESS;
    ble_gatts_value_t  gatts_value;

    if (battery_level != p_bas->battery_level_last)
    {
        // Initialize value struct.
        memset(&gatts_value, 0, sizeof(gatts_value));

        gatts_value.len     = sizeof(uint8_t);
        gatts_value.offset  = 0;
        gatts_value.p_value = &battery_level;

        // Update database.
        err_code = sd_ble_gatts_value_set(BLE_CONN_HANDLE_INVALID,
                                          p_bas->battery_level_handles.value_handle,
                                          &gatts_value);
        if (err_code == NRF_SUCCESS)
        {
            NRF_LOG_INFO("Battery level has been updated: %d%%", battery_level)

            // Save new battery value.
            p_bas->battery_level_last = battery_level;
        }
        else
        {
            NRF_LOG_DEBUG("Error during battery level update: 0x%08X", err_code)

            return err_code;
        }

        // Send value if connected and notifying.
        if (p_bas->is_notification_supported)
        {
            ble_gatts_hvx_params_t hvx_params;

            memset(&hvx_params, 0, sizeof(hvx_params));

            hvx_params.handle = p_bas->battery_level_handles.value_handle;
            hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
            hvx_params.offset = gatts_value.offset;
            hvx_params.p_len  = &gatts_value.len;
            hvx_params.p_data = gatts_value.p_value;

            if (conn_handle == BLE_CONN_HANDLE_ALL)
            {
                ble_conn_state_conn_handle_list_t conn_handles = ble_conn_state_conn_handles();

                // Try sending notifications to all valid connection handles.
                for (uint32_t i = 0; i < conn_handles.len; i++)
                {
                    if (ble_conn_state_status(conn_handles.conn_handles[i]) == BLE_CONN_STATUS_CONNECTED)
                    {
                        if (err_code == NRF_SUCCESS)
                        {
                            err_code = battery_notification_send(&hvx_params,
                                                                 conn_handles.conn_handles[i]);
                        }
                        else
                        {
                            // Preserve the first non-zero error code
                            UNUSED_RETURN_VALUE(battery_notification_send(&hvx_params,
                                                                          conn_handles.conn_handles[i]));
                        }
                    }
                }
            }
            else
            {
                err_code = battery_notification_send(&hvx_params, conn_handle);
            }
        }
        else
        {
            err_code = NRF_ERROR_INVALID_STATE;
        }
    }

    return err_code;
}


ret_code_t ble_bas_battery_lvl_on_reconnection_update(ble_bas_t * p_bas,
                                                      uint16_t    conn_handle)
{
    if (p_bas == NULL)
    {
        return NRF_ERROR_NULL;
    }

    ret_code_t err_code;

    if (p_bas->is_notification_supported)
    {
        ble_gatts_hvx_params_t hvx_params;
        uint16_t               len = sizeof(uint8_t);

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_bas->battery_level_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &len;
        hvx_params.p_data = &p_bas->battery_level_last;

        err_code = battery_notification_send(&hvx_params, conn_handle);

        return err_code;
    }

    return NRF_ERROR_INVALID_STATE;
}


#endif // NRF_MODULE_ENABLED(BLE_BAS)
