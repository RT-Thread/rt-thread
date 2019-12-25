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
#if NRF_MODULE_ENABLED(BLE_BPS)
#include "ble_bps.h"
#include "ble_err.h"
#include <string.h>
#include "nordic_common.h"
#include "ble_srv_common.h"


#define OPCODE_LENGTH   1     /**< Length of opcode inside Blood Pressure Measurement packet. */
#define HANDLE_LENGTH   2     /**< Length of handle inside Blood Pressure Measurement packet. */
#define MAX_BPM_LEN     (BLE_GATT_ATT_MTU_DEFAULT - OPCODE_LENGTH - HANDLE_LENGTH)    /**< Maximum size of a transmitted Blood Pressure Measurement. */

// Blood Pressure Measurement Flags bits
#define BPS_MEAS_BLOOD_PRESSURE_UNITS_FLAG_BIT (0x01 << 0)  /**< Blood Pressure Units Flag bit. */
#define BPS_MEAS_TIME_STAMP_FLAG_BIT           (0x01 << 1)  /**< Time Stamp Flag bit. */
#define BPS_MEAS_PULSE_RATE_FLAG_BIT           (0x01 << 2)  /**< Pulse Rate Flag bit. */
#define BPS_MEAS_USER_ID_FLAG_BIT              (0x01 << 3)  /**< User ID Flag bit. */
#define BPS_MEAS_MEASUREMENT_STATUS_FLAG_BIT   (0x01 << 4)  /**< Measurement Status Flag bit. */


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_bps       Blood Pressure Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_bps_t * p_bps, ble_evt_t const * p_ble_evt)
{
    p_bps->conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_bps       Blood Pressure Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_bps_t * p_bps, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_bps->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for handling the write events to the Blood Pressure Measurement characteristic.
 *
 * @param[in]   p_bps         Blood Pressure Service structure.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_cccd_write(ble_bps_t * p_bps, ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == 2)
    {
        // CCCD written, update indication state
        if (p_bps->evt_handler != NULL)
        {
            ble_bps_evt_t evt;

            if (ble_srv_is_indication_enabled(p_evt_write->data))
            {
                evt.evt_type = BLE_BPS_EVT_INDICATION_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_BPS_EVT_INDICATION_DISABLED;
            }

            p_bps->evt_handler(p_bps, &evt);
        }
    }
}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bps       Blood Pressure Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_bps_t * p_bps, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle == p_bps->meas_handles.cccd_handle)
    {
        on_cccd_write(p_bps, p_evt_write);
    }
}


/**@brief Function for handling the HVC event.
 *
 * @details Handles HVC events from the BLE stack.
 *
 * @param[in]   p_bps       Blood Pressure Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_hvc(ble_bps_t * p_bps, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_hvc_t const * p_hvc = &p_ble_evt->evt.gatts_evt.params.hvc;

    if (p_hvc->handle == p_bps->meas_handles.value_handle)
    {
        ble_bps_evt_t evt;

        evt.evt_type = BLE_BPS_EVT_INDICATION_CONFIRMED;
        p_bps->evt_handler(p_bps, &evt);
    }
}


void ble_bps_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_bps_t * p_bps = (ble_bps_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_bps, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_bps, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_bps, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVC:
            on_hvc(p_bps, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for encoding a Blood Pressure Measurement.
 *
 * @param[in]   p_bps              Blood Pressure Service structure.
 * @param[in]   p_bps_meas         Measurement to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t bps_measurement_encode(ble_bps_t      * p_bps,
                                      ble_bps_meas_t * p_bps_meas,
                                      uint8_t        * p_encoded_buffer)
{
    uint8_t  flags = 0;
    uint8_t  len   = 1;
    uint16_t encoded_sfloat;

    // Set measurement units flag
    if (p_bps_meas->blood_pressure_units_in_kpa)
    {
        flags |= BPS_MEAS_BLOOD_PRESSURE_UNITS_FLAG_BIT;
    }

    // Blood Pressure Measurement - Systolic
    encoded_sfloat = ((p_bps_meas->blood_pressure_systolic.exponent << 12) & 0xF000) |
                     ((p_bps_meas->blood_pressure_systolic.mantissa <<  0) & 0x0FFF);
    len += uint16_encode(encoded_sfloat, &p_encoded_buffer[len]);

    // Blood Pressure Measurement - Diastolic
    encoded_sfloat = ((p_bps_meas->blood_pressure_diastolic.exponent << 12) & 0xF000) |
                     ((p_bps_meas->blood_pressure_diastolic.mantissa <<  0) & 0x0FFF);
    len += uint16_encode(encoded_sfloat, &p_encoded_buffer[len]);

    // Blood Pressure Measurement - Mean Arterial Pressure
    encoded_sfloat = ((p_bps_meas->mean_arterial_pressure.exponent << 12) & 0xF000) |
                     ((p_bps_meas->mean_arterial_pressure.mantissa <<  0) & 0x0FFF);
    len += uint16_encode(encoded_sfloat, &p_encoded_buffer[len]);

    // Time Stamp field
    if (p_bps_meas->time_stamp_present)
    {
        flags |= BPS_MEAS_TIME_STAMP_FLAG_BIT;
        len   += ble_date_time_encode(&p_bps_meas->time_stamp, &p_encoded_buffer[len]);
    }

    // Pulse Rate
    if (p_bps_meas->pulse_rate_present)
    {
        flags |= BPS_MEAS_PULSE_RATE_FLAG_BIT;

        encoded_sfloat = ((p_bps_meas->pulse_rate.exponent << 12) & 0xF000) |
                         ((p_bps_meas->pulse_rate.mantissa <<  0) & 0x0FFF);
        len += uint16_encode(encoded_sfloat, &p_encoded_buffer[len]);
    }

    // User ID
    if (p_bps_meas->user_id_present)
    {
        flags                  |= BPS_MEAS_USER_ID_FLAG_BIT;
        p_encoded_buffer[len++] = p_bps_meas->user_id;
    }

    // Measurement Status
    if (p_bps_meas->measurement_status_present)
    {
        flags |= BPS_MEAS_MEASUREMENT_STATUS_FLAG_BIT;
        len   += uint16_encode(p_bps_meas->measurement_status, &p_encoded_buffer[len]);
    }

    // Flags field
    p_encoded_buffer[0] = flags;

    return len;
}


uint32_t ble_bps_init(ble_bps_t * p_bps, ble_bps_init_t const * p_bps_init)
{
    uint32_t              err_code;
    uint8_t               init_value_encoded[MAX_BPM_LEN];
    uint8_t               initial_feature_len;
    ble_bps_meas_t        initial_bpm;
    ble_uuid_t            ble_uuid;
    ble_add_char_params_t add_char_params;

    // Initialize service structure
    p_bps->evt_handler = p_bps_init->evt_handler;
    p_bps->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_bps->feature     = p_bps_init->feature;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_BLOOD_PRESSURE_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_bps->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add measurement characteristic
    memset(&initial_bpm, 0, sizeof(initial_bpm));
    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid                = BLE_UUID_BLOOD_PRESSURE_MEASUREMENT_CHAR;
    add_char_params.max_len             = MAX_BPM_LEN;
    add_char_params.is_var_len          = true;
    add_char_params.init_len            = bps_measurement_encode(p_bps, &initial_bpm, init_value_encoded);
    add_char_params.p_init_value        = init_value_encoded;
    add_char_params.char_props.indicate = 1;
    add_char_params.cccd_write_access   = p_bps_init->bp_cccd_wr_sec;

    err_code = characteristic_add(p_bps->service_handle, &add_char_params, &p_bps->meas_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add feature characteristic
    initial_feature_len = uint16_encode(p_bps_init->feature, init_value_encoded);

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid            = BLE_UUID_BLOOD_PRESSURE_FEATURE_CHAR;
    add_char_params.max_len         = initial_feature_len;
    add_char_params.init_len        = initial_feature_len;
    add_char_params.p_init_value    = init_value_encoded;
    add_char_params.char_props.read = 1;
    add_char_params.read_access     = p_bps_init->bp_feature_rd_sec;

    err_code = characteristic_add(p_bps->service_handle, &add_char_params, &p_bps->feature_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}


uint32_t ble_bps_measurement_send(ble_bps_t * p_bps, ble_bps_meas_t * p_bps_meas)
{
    uint32_t err_code;

    // Send value if connected
    if (p_bps->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        uint8_t                encoded_bps_meas[MAX_BPM_LEN];
        uint16_t               len;
        uint16_t               hvx_len;
        ble_gatts_hvx_params_t hvx_params;

        len     = bps_measurement_encode(p_bps, p_bps_meas, encoded_bps_meas);
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_bps->meas_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_INDICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = encoded_bps_meas;

        err_code = sd_ble_gatts_hvx(p_bps->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}


uint32_t ble_bps_is_indication_enabled(ble_bps_t * p_bps, bool * p_indication_enabled)
{
    uint32_t err_code;
    uint8_t  cccd_value_buf[BLE_CCCD_VALUE_LEN];
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = cccd_value_buf;

    err_code = sd_ble_gatts_value_get(p_bps->conn_handle,
                                      p_bps->meas_handles.cccd_handle,
                                      &gatts_value);

    if (err_code == NRF_SUCCESS)
    {
        *p_indication_enabled = ble_srv_is_indication_enabled(cccd_value_buf);
    }
    if (err_code == BLE_ERROR_GATTS_SYS_ATTR_MISSING)
    {
        *p_indication_enabled = false;
        return NRF_SUCCESS;
    }
    return err_code;
}
#endif // NRF_MODULE_ENABLED(BLE_BPS)
