/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#include "ble_racp.h"
#include "ble_srv_common.h"

#include "ble_date_time.h"
#include "sdk_common.h"

#include "nrf_ble_cgms.h"
#include "cgms_db.h"
#include "cgms_meas.h"
#include "cgms_racp.h"
#include "cgms_socp.h"
#include "cgms_sst.h"

#define OPERAND_FILTER_TYPE_RESV        0x00 /**< Filter type value reserved for future use. */
#define OPERAND_FILTER_TYPE_SEQ_NUM     0x01 /**< Filter data using Sequence Number criteria. */
#define OPERAND_FILTER_TYPE_FACING_TIME 0x02 /**< Filter data using User Facing Time criteria. */


/**@brief Function for setting next sequence number by reading the last record in the data base.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
static uint32_t next_sequence_number_set(void)
{
    uint16_t       num_records;
    ble_cgms_rec_t rec;

    num_records = cgms_db_num_records_get();
    if (num_records > 0)
    {
        // Get last record
        uint32_t err_code = cgms_db_record_get(num_records - 1, &rec);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}


uint8_t encode_feature_location_type(uint8_t * p_out_buffer, nrf_ble_cgms_feature_t * p_in_feature)
{
    uint8_t len = 0;

    len                += uint24_encode(p_in_feature->feature, &p_out_buffer[len]);
    p_out_buffer[len++] = (p_in_feature->sample_location << 4) | (p_in_feature->type & 0x0F);
    len                += uint16_encode(0xFFFF, &p_out_buffer[len]);

    return len;
}


/**@brief Function for adding a characteristic for the glucose feature.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS if characteristic was successfully added, otherwise an error code.
 */
static uint32_t glucose_feature_char_add(nrf_ble_cgms_t * p_cgms)
{
    uint8_t               init_value_len;
    uint8_t               encoded_initial_feature[NRF_BLE_CGMS_FEATURE_LEN];
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    init_value_len = encode_feature_location_type(encoded_initial_feature, &(p_cgms->feature));

    add_char_params.uuid         = BLE_UUID_CGM_FEATURE;
    add_char_params.max_len      = init_value_len;
    add_char_params.init_len     = init_value_len;
    add_char_params.p_init_value = encoded_initial_feature;
    add_char_params.read_access  = SEC_JUST_WORKS;
    add_char_params.write_access = SEC_NO_ACCESS;


    return characteristic_add(p_cgms->service_handle,
                              &add_char_params,
                              &p_cgms->char_handles.feature);
}


uint8_t encode_status(uint8_t * p_out_buffer, nrf_ble_cgms_t * p_cgms)
{
    uint8_t len = 0;

    len += uint16_encode(p_cgms->sensor_status.time_offset, &p_out_buffer[len]);

    p_out_buffer[len++] = p_cgms->sensor_status.status.status;
    p_out_buffer[len++] = p_cgms->sensor_status.status.calib_temp;
    p_out_buffer[len++] = p_cgms->sensor_status.status.warning;

    return len;
}


/**@brief Function for adding a status characteristic for the CGMS.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS if characteristic was successfully added, otherwise an error code.
 */
static uint32_t status_char_add(nrf_ble_cgms_t * p_cgms)
{
    uint8_t               init_value_len;
    uint8_t               encoded_initial_status[NRF_BLE_CGMS_STATUS_LEN];
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    init_value_len = encode_status(encoded_initial_status, p_cgms);

    add_char_params.uuid         = BLE_UUID_CGM_STATUS;
    add_char_params.max_len      = init_value_len;
    add_char_params.init_len     = init_value_len;
    add_char_params.p_init_value = encoded_initial_status;
    add_char_params.read_access  = SEC_JUST_WORKS;
    add_char_params.write_access = SEC_NO_ACCESS;

    return characteristic_add(p_cgms->service_handle,
                              &add_char_params,
                              &p_cgms->char_handles.status);
}


/**@brief Function for adding a characteristic for the Session Run Time.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS if characteristic was successfully added, otherwise an error code.
 */
static uint32_t srt_char_add(nrf_ble_cgms_t * p_cgms)
{
    uint8_t               len = 0;
    uint8_t               encoded_initial_srt[NRF_BLE_CGMS_SRT_LEN];
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));


    len += uint16_encode(p_cgms->session_run_time, &(encoded_initial_srt[len]));

    add_char_params.uuid            = BLE_UUID_CGM_SESSION_RUN_TIME;
    add_char_params.max_len         = NRF_BLE_CGMS_SRT_LEN;
    add_char_params.init_len        = len;
    add_char_params.p_init_value    = encoded_initial_srt;
    add_char_params.read_access     = SEC_JUST_WORKS;
    add_char_params.write_access    = SEC_NO_ACCESS;
    add_char_params.char_props.read = true;

    return characteristic_add(p_cgms->service_handle,
                              &add_char_params,
                              &p_cgms->char_handles.srt);
}


uint8_t init_calib_val[] = {
    0x3E,
    0x00,
    0x07,
    0x00,
    0x06,
    0x07,
    0x00,
    0x00,
    0x00,
    0x00,
};
ret_code_t nrf_ble_cgms_init(nrf_ble_cgms_t * p_cgms, const nrf_ble_cgms_init_t * p_cgms_init)
{
    VERIFY_PARAM_NOT_NULL(p_cgms);
    VERIFY_PARAM_NOT_NULL(p_cgms_init);
    VERIFY_PARAM_NOT_NULL(p_cgms_init->evt_handler);

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize data base
    err_code = cgms_db_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = next_sequence_number_set();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Initialize service structure
    p_cgms->evt_handler        = p_cgms_init->evt_handler;
    p_cgms->error_handler      = p_cgms_init->error_handler;
    p_cgms->feature            = p_cgms_init->feature;
    p_cgms->sensor_status      = p_cgms_init->initial_sensor_status;
    p_cgms->session_run_time   = p_cgms_init->initial_run_time;
    p_cgms->is_session_started = false;
    p_cgms->nb_run_session     = 0;
    p_cgms->conn_handle        = BLE_CONN_HANDLE_INVALID;

    p_cgms->feature.feature         = 0;
    p_cgms->feature.feature        |= NRF_BLE_CGMS_FEAT_MULTIPLE_BOND_SUPPORTED;
    p_cgms->feature.feature        |= NRF_BLE_CGMS_FEAT_MULTIPLE_SESSIONS_SUPPORTED;
    p_cgms->feature.type            = NRF_BLE_CGMS_MEAS_TYPE_VEN_BLOOD;
    p_cgms->feature.sample_location = NRF_BLE_CGMS_MEAS_LOC_AST;
    p_cgms->feature.feature        |= NRF_BLE_CGMS_FEAT_MULTIPLE_BOND_SUPPORTED;

    memcpy(p_cgms->calibration_val[0].value, init_calib_val, NRF_BLE_CGMS_MAX_CALIB_LEN);

    // Initialize global variables
    p_cgms->cgms_com_state = STATE_NO_COMM;
    p_cgms->racp_data.racp_proc_records_reported_since_txcomplete = 0;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_CGM_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_cgms->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add glucose measurement characteristic
    err_code = cgms_meas_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add glucose measurement feature characteristic
    err_code = glucose_feature_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add glucose measurement status characteristic
    err_code = status_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add record control access point characteristic
    err_code = cgms_racp_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Start Session Time characteristic
    err_code = cgms_sst_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Session Run Time characteristic
    err_code = srt_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Specific Operations Control Point characteristic
    err_code = cgms_socp_char_add(p_cgms);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}


/**@brief Function for handling the WRITE event.
 *
 * @details Handles WRITE events from the BLE stack.
 *
 * @param[in]   p_cgms      Glucose Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
static void on_write(nrf_ble_cgms_t * p_cgms, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    cgms_meas_on_write(p_cgms, p_evt_write);
}


/**@brief Function for handling the TX_COMPLETE event.
 *
 * @details Handles TX_COMPLETE events from the BLE stack.
 *
 * @param[in]   p_cgms      Glucose Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
static void on_tx_complete(nrf_ble_cgms_t * p_cgms, ble_evt_t const * p_ble_evt)
{
    p_cgms->racp_data.racp_proc_records_reported_since_txcomplete = 0;

    cgms_racp_on_tx_complete(p_cgms);
    cgms_socp_on_tx_complete(p_cgms);
}


/**@brief Function for handling the HVC event.
 *
 * @details Handles HVC events from the BLE stack.
 *
 * @param[in]   p_cgms      Glucose Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
static void on_hvc(nrf_ble_cgms_t * p_cgms, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_hvc_t const * p_hvc = &p_ble_evt->evt.gatts_evt.params.hvc;

    if (p_hvc->handle == p_cgms->char_handles.racp.value_handle)
    {
        if (p_cgms->cgms_com_state == STATE_RACP_RESPONSE_IND_VERIF)
        {
            // Indication has been acknowledged. Return to default state.
            p_cgms->cgms_com_state = STATE_NO_COMM;
        }
        else
        {
            // We did not expect this event in this state. Report error to application.
            if (p_cgms->error_handler != NULL)
            {
                p_cgms->error_handler(NRF_ERROR_INVALID_STATE);
            }
        }
    }
    if (p_hvc->handle == p_cgms->char_handles.socp.value_handle)
    {
        if (p_cgms->cgms_com_state == STATE_SOCP_RESPONSE_IND_VERIF)
        {
            // Indication has been acknowledged. Return to default state.
            p_cgms->cgms_com_state = STATE_NO_COMM;
        }
        else
        {
            // We did not expect this event in this state. Report error to application.
            if (p_cgms->error_handler != NULL)
            {
                p_cgms->error_handler(NRF_ERROR_INVALID_STATE);
            }
        }
    }
}


static void on_rw_authorize_request(nrf_ble_cgms_t * p_cgms, ble_gatts_evt_t const * p_gatts_evt)
{
    ble_gatts_evt_rw_authorize_request_t const * p_auth_req =
        &p_gatts_evt->params.authorize_request;

    cgms_racp_on_rw_auth_req(p_cgms, p_auth_req);
    cgms_socp_on_rw_auth_req(p_cgms, p_auth_req);
    cgms_sst_on_rw_auth_req(p_cgms, p_auth_req);
}


void nrf_ble_cgms_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    nrf_ble_cgms_t * p_cgms = (nrf_ble_cgms_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            p_cgms->conn_handle    = p_ble_evt->evt.gap_evt.conn_handle;
            p_cgms->cgms_com_state = STATE_NO_COMM;
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            p_cgms->conn_handle = BLE_CONN_HANDLE_INVALID;
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_cgms, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            on_tx_complete(p_cgms, p_ble_evt);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_authorize_request(p_cgms, &p_ble_evt->evt.gatts_evt);
            break;

        case BLE_GATTS_EVT_HVC:
            on_hvc(p_cgms, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}


ret_code_t nrf_ble_cgms_meas_create(nrf_ble_cgms_t * p_cgms, ble_cgms_rec_t * p_rec)
{
    uint32_t err_code       = NRF_SUCCESS;
    uint8_t  nb_rec_to_send = 1;

    err_code = cgms_db_record_add(p_rec);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    if ((p_cgms->conn_handle != BLE_CONN_HANDLE_INVALID) && (p_cgms->comm_interval != 0))
    {
        err_code = cgms_meas_send(p_cgms, p_rec, &nb_rec_to_send);
    }
    return err_code;
}


ret_code_t nrf_ble_cgms_update_status(nrf_ble_cgms_t * p_cgms, nrf_ble_cgm_status_t * p_status)
{
    uint8_t           encoded_status[NRF_BLE_CGMS_STATUS_LEN];
    ble_gatts_value_t status_val;

    memset(&status_val, 0, sizeof(status_val));
    p_cgms->sensor_status = *p_status;
    status_val.len        = encode_status(encoded_status, p_cgms);
    status_val.p_value    = encoded_status;
    status_val.offset     = 0;

    return (sd_ble_gatts_value_set(p_cgms->conn_handle, p_cgms->char_handles.status.value_handle,
                                   &status_val));
}


ret_code_t nrf_ble_cgms_conn_handle_assign(nrf_ble_cgms_t * p_cgms, uint16_t conn_handle)
{
    VERIFY_PARAM_NOT_NULL(p_cgms);
    p_cgms->conn_handle = conn_handle;
    return NRF_SUCCESS;
}


ret_code_t nrf_ble_cgms_srt_set(nrf_ble_cgms_t * p_cgms, uint16_t run_time)
{
    ble_gatts_value_t srt_val;
    uint8_t           encoded_session_run_time[NRF_BLE_CGMS_SRT_LEN];
    uint8_t           gatts_value_set_len = 0;

    gatts_value_set_len = uint16_encode(run_time, encoded_session_run_time); // (p_sst, encoded_start_session_time);

    memset(&srt_val, 0, sizeof(ble_gatts_value_t));
    srt_val.len     = gatts_value_set_len;
    srt_val.p_value = encoded_session_run_time;
    srt_val.offset  = 0;

    return (sd_ble_gatts_value_set(p_cgms->conn_handle, p_cgms->char_handles.srt.value_handle,
                                   &srt_val));
}


