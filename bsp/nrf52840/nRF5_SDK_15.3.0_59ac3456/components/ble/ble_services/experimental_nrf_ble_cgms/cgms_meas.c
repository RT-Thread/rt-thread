/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include <stdint.h>
#include <string.h>
#include "ble.h"
#include "sdk_macros.h"
#include "ble_srv_common.h"
#include "nrf_ble_cgms.h"
#include "cgms_meas.h"
#include "cgms_db.h"

/**@brief Function for encoding a Glucose measurement.
 *
 * @param[in]  p_meas           Measurement to be encoded.
 * @param[out] p_encoded_buffer Pointer to buffer where the encoded measurement is to be stored.
 *
 * @return Size of encoded measurement.
 */
static uint8_t cgms_meas_encode(nrf_ble_cgms_t            * p_cgms,
                                const nrf_ble_cgms_meas_t * p_meas,
                                uint8_t                   * p_encoded_buffer)
{
    uint8_t len = 2;

    uint8_t flags = p_meas->flags;

    len += uint16_encode(p_meas->glucose_concentration,
                         &p_encoded_buffer[len]);
    len += uint16_encode(p_meas->time_offset,
                         &p_encoded_buffer[len]);

    if (p_meas->sensor_status_annunciation.warning != 0)
    {
        p_encoded_buffer[len++] = p_meas->sensor_status_annunciation.warning;
        flags                  |= NRF_BLE_CGMS_STATUS_FLAGS_WARNING_OCT_PRESENT;
    }

    if (p_meas->sensor_status_annunciation.calib_temp != 0)
    {
        p_encoded_buffer[len++] = p_meas->sensor_status_annunciation.calib_temp;
        flags                  |= NRF_BLE_CGMS_STATUS_FLAGS_CALTEMP_OCT_PRESENT;
    }

    if (p_meas->sensor_status_annunciation.status != 0)
    {
        p_encoded_buffer[len++] = p_meas->sensor_status_annunciation.status;
        flags                  |= NRF_BLE_CGMS_STATUS_FLAGS_STATUS_OCT_PRESENT;
    }

    // Trend field
    if (p_cgms->feature.feature & NRF_BLE_CGMS_FEAT_CGM_TREND_INFORMATION_SUPPORTED)
    {
        if (flags & NRF_BLE_CGMS_FLAG_TREND_INFO_PRESENT)
        {
            len += uint16_encode(p_meas->trend, &p_encoded_buffer[len]);
        }
    }

    // Quality field
    if (p_cgms->feature.feature & NRF_BLE_CGMS_FEAT_CGM_QUALITY_SUPPORTED)
    {
        if (flags & NRF_BLE_CGMS_FLAGS_QUALITY_PRESENT)
        {
            len += uint16_encode(p_meas->quality, &p_encoded_buffer[len]);
        }
    }

    p_encoded_buffer[1] = flags;
    p_encoded_buffer[0] = len;
    return len;
}


/**@brief Function for adding a characteristic for the Continuous Glucose Meter Measurement.
 *
 * @param[in] p_cgms Service instance.
 *
 * @return NRF_SUCCESS if characteristic was successfully added, otherwise an error code.
 */
ret_code_t cgms_meas_char_add(nrf_ble_cgms_t * p_cgms)
{
    uint8_t               num_recs;
    uint8_t               encoded_cgms_meas[NRF_BLE_CGMS_MEAS_LEN_MAX];
    ble_add_char_params_t add_char_params;
    ble_cgms_rec_t        initial_cgms_rec_value;

    memset(&add_char_params, 0, sizeof(add_char_params));
    memset(&initial_cgms_rec_value, 0, sizeof(ble_cgms_rec_t));

    num_recs = cgms_db_num_records_get();
    if (num_recs > 0)
    {
        uint32_t err_code = cgms_db_record_get(num_recs - 1, &initial_cgms_rec_value);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    add_char_params.uuid     = BLE_UUID_CGM_MEASUREMENT;
    add_char_params.max_len  = NRF_BLE_CGMS_MEAS_LEN_MAX;
    add_char_params.init_len = cgms_meas_encode(p_cgms,
                                                &initial_cgms_rec_value.meas,
                                                encoded_cgms_meas);
    add_char_params.p_init_value      = encoded_cgms_meas;
    add_char_params.is_var_len        = true;
    add_char_params.char_props.notify = true;
    add_char_params.cccd_write_access = SEC_JUST_WORKS;


    return characteristic_add(p_cgms->service_handle,
                              &add_char_params,
                              &p_cgms->char_handles.measurment);
}


ret_code_t cgms_meas_send(nrf_ble_cgms_t * p_cgms, ble_cgms_rec_t * p_rec, uint8_t * p_count)
{

    uint32_t               err_code;
    uint8_t                encoded_meas[NRF_BLE_CGMS_MEAS_LEN_MAX + NRF_BLE_CGMS_MEAS_REC_LEN_MAX];
    uint16_t               len     = 0;
    uint16_t               hvx_len = NRF_BLE_CGMS_MEAS_LEN_MAX;
    int                    i;
    ble_gatts_hvx_params_t hvx_params;

    for (i = 0; i < *p_count; i++)
    {
        uint8_t meas_len = cgms_meas_encode(p_cgms, &(p_rec[i].meas), (encoded_meas + len));
        if (len + meas_len >= NRF_BLE_CGMS_MEAS_LEN_MAX)
        {
            break;
        }
        len += meas_len;
    }
    *p_count = i;
    hvx_len  = len;

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_params.handle = p_cgms->char_handles.measurment.value_handle;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    hvx_params.offset = 0;
    hvx_params.p_len  = &hvx_len;
    hvx_params.p_data = encoded_meas;

    err_code = sd_ble_gatts_hvx(p_cgms->conn_handle, &hvx_params);
    if (err_code == NRF_SUCCESS)
    {
        if (hvx_len != len)
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
        else
        {
            // Measurement successfully sent
            p_cgms->racp_data.racp_proc_records_reported += *p_count;
            p_cgms->racp_data.racp_proc_records_reported_since_txcomplete++;
        }
    }

    return err_code;
}


/**@brief Function for handling the Glucose measurement CCCD write event.
 *
 * @param[in]   p_cgms         Service instance.
 * @param[in]   p_evt_write   WRITE event to be handled.
 */
static void on_meas_cccd_write(nrf_ble_cgms_t * p_cgms, ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == 2)
    {
        // CCCD written, update notification state
        if (p_cgms->evt_handler != NULL)
        {
            nrf_ble_cgms_evt_t evt;

            if (ble_srv_is_notification_enabled(p_evt_write->data))
            {
                evt.evt_type = NRF_BLE_CGMS_EVT_NOTIFICATION_ENABLED;
            }
            else
            {
                evt.evt_type = NRF_BLE_CGMS_EVT_NOTIFICATION_DISABLED;
            }

            p_cgms->evt_handler(p_cgms, &evt);
        }
    }
}


/**@brief Function for handling the WRITE event.
 *
 * @details Handles WRITE events from the BLE stack.
 *
 * @param[in]   p_cgms      Glucose Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void cgms_meas_on_write(nrf_ble_cgms_t * p_cgms, ble_gatts_evt_write_t const * p_evt_write)
{

    if (p_evt_write->handle == p_cgms->char_handles.measurment.cccd_handle)
    {
        on_meas_cccd_write(p_cgms, p_evt_write);
    }
}


