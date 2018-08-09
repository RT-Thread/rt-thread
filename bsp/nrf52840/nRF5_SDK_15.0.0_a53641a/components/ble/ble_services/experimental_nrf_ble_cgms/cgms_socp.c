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
#include <stdint.h>
#include <string.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "cgms_sst.h"
#include "cgms_socp.h"


#define NRF_BLE_CGMS_PLUS_INFINTE                     0x07FE
#define NRF_BLE_CGMS_MINUS_INFINTE                    0x0802

/**@brief Specific Operation Control Point opcodes. */
#define SOCP_OPCODE_RESERVED                          0x00 /**< Specific Operation Control Point opcode - Reserved for future use. */
#define SOCP_WRITE_CGM_COMMUNICATION_INTERVAL         0x01
#define SOCP_READ_CGM_COMMUNICATION_INTERVAL          0x02
#define SOCP_READ_CGM_COMMUNICATION_INTERVAL_RESPONSE 0x03
#define SOCP_WRITE_GLUCOSE_CALIBRATION_VALUE          0x04
#define SOCP_READ_GLUCOSE_CALIBRATION_VALUE           0x05
#define SOCP_READ_GLUCOSE_CALIBRATION_VALUE_RESPONSE  0x06
#define SOCP_WRITE_PATIENT_HIGH_ALERT_LEVEL           0x07
#define SOCP_READ_PATIENT_HIGH_ALERT_LEVEL            0x08
#define SOCP_READ_PATIENT_HIGH_ALERT_LEVEL_RESPONSE   0x09
#define SOCP_WRITE_PATIENT_LOW_ALERT_LEVEL            0x0A
#define SOCP_READ_PATIENT_LOW_ALERT_LEVEL             0x0B
#define SOCP_READ_PATIENT_LOW_ALERT_LEVEL_RESPONSE    0x0C
#define SOCP_SET_HYPO_ALERT_LEVEL                     0x0D /**Set Hypo Alert Level    Hypo Alert Level value in mg/dL    The response to this control point is Response Code.                                            */
#define SOCP_GET_HYPO_ALERT_LEVEL                     0x0E /**Get Hypo Alert Level    N/A    The normal response to this control point is Op Code 0x0F. For error conditions, the response is Response Code              */
#define SOCP_HYPO_ALERT_LEVEL_RESPONSE                0x0F /**Hypo Alert Level Response    Hypo Alert Level value in mg/dL    This is the normal response to Op Code 0x0E                                             */
#define SOCP_SET_HYPER_ALERT_LEVEL                    0x10 /**Set Hyper Alert Level    Hyper Alert Level value in mg/dL    The response to this control point is Response Code.                                    */
#define SOCP_GET_HYPER_ALERT_LEVEL                    0x11 /**Get Hyper Alert Level    N/A    The normal response to this control point is Op Code 0x12. For error conditions, the response is Response Code          */
#define SOCP_HYPER_ALERT_LEVEL_RESPONSE               0x12 /**Hyper Alert Level Response    Hyper Alert Level value in mg/dL    This is the normal response to Op Code 0x11                                         */
#define SOCP_SET_RATE_OF_DECREASE_ALERT_LEVEL         0x13 /**Set Rate of Decrease Alert Level    Rate of Decrease Alert Level value in mg/dL/min    The response to this control point is Response Code.                */
#define SOCP_GET_RATE_OF_DECREASE_ALERT_LEVEL         0x14 /**Get Rate of Decrease Alert Level    N/A    The normal response to this control point is Op Code 0x15. For error conditions, the response is Response Code  */
#define SOCP_RATE_OF_DECREASE_ALERT_LEVEL_RESPONSE    0x15 /**Rate of Decrease Alert Level Response    Rate of Decrease Alert Level value in mg/dL/min    This is the normal response to Op Code 0x14                 */
#define SOCP_SET_RATE_OF_INCREASE_ALERT_LEVEL         0x16 /**Set Rate of Increase Alert Level    Rate of Increase Alert Level value in mg/dL/min    The response to this control point is Response Code.                */
#define SOCP_GET_RATE_OF_INCREASE_ALERT_LEVEL         0x17 /**Get Rate of Increase Alert Level    N/A    The normal response to this control point is Op Code 0x18. For error conditions, the response is Response Code  */
#define SOCP_RATE_OF_INCREASE_ALERT_LEVEL_RESPONSE    0x18 /**Rate of Increase Alert Level Response    Rate of Increase Alert Level value in mg/dL/min    This is the normal response to Op Code 0x17                 */
#define SOCP_RESET_DEVICE_SPECIFIC_ALERT              0x19 /**Reset Device Specific Alert    N/A    The response to this control point is Response Code.                                                                */

#define SOCP_START_THE_SESSION                        0x1A
#define SOCP_STOP_THE_SESSION                         0x1B
#define SOCP_RESPONSE_CODE                            0x1C

#define SOCP_RSP_RESERVED_FOR_FUTURE_USE              0x00
#define SOCP_RSP_SUCCESS                              0x01
#define SOCP_RSP_OP_CODE_NOT_SUPPORTED                0x02
#define SOCP_RSP_INVALID_OPERAND                      0x03
#define SOCP_RSP_PROCEDURE_NOT_COMPLETED              0x04
#define SOCP_RSP_OUT_OF_RANGE                         0x05

static void ble_socp_decode(uint8_t data_len, uint8_t const * p_data, ble_cgms_socp_value_t * p_socp_val)
{
    p_socp_val->opcode      = 0xFF;
    p_socp_val->operand_len = 0;
    p_socp_val->p_operand   = NULL;

    if (data_len > 0)
    {
        p_socp_val->opcode = p_data[0];
    }
    if (data_len > 1)
    {
        p_socp_val->operand_len = data_len - 1;
        p_socp_val->p_operand   = (uint8_t*)&p_data[1]; // lint !e416
    }
}


uint8_t ble_socp_encode(const ble_socp_rsp_t * p_socp_rsp, uint8_t * p_data)
{
    uint8_t len = 0;
    int     i;


    if (p_data != NULL)
    {
        p_data[len++] = p_socp_rsp->opcode;

        if (
            (p_socp_rsp->opcode != SOCP_READ_CGM_COMMUNICATION_INTERVAL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_READ_PATIENT_HIGH_ALERT_LEVEL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_READ_PATIENT_LOW_ALERT_LEVEL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_HYPO_ALERT_LEVEL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_HYPER_ALERT_LEVEL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_RATE_OF_DECREASE_ALERT_LEVEL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_RATE_OF_INCREASE_ALERT_LEVEL_RESPONSE)
            && (p_socp_rsp->opcode != SOCP_READ_GLUCOSE_CALIBRATION_VALUE_RESPONSE)
           )
        {
            p_data[len++] = p_socp_rsp->req_opcode;
            p_data[len++] = p_socp_rsp->rsp_code;
        }

        for (i = 0; i < p_socp_rsp->size_val; i++)
        {
            p_data[len++] = p_socp_rsp->resp_val[i];
        }
    }

    return len;
}


/**@brief Function for adding a characteristic for the Specific Operations Control Point.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS if characteristic was successfully added, otherwise an error code.
 */
ret_code_t cgms_socp_char_add(nrf_ble_cgms_t * p_cgms)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid                = BLE_UUID_CGM_SPECIFIC_OPS_CTRLPT;
    add_char_params.max_len             = BLE_GATT_ATT_MTU_DEFAULT;
    add_char_params.init_len            = 0;
    add_char_params.p_init_value        = 0;
    add_char_params.is_var_len          = true;
    add_char_params.char_props.indicate = true;
    add_char_params.char_props.write    = true;
    add_char_params.write_access        = SEC_JUST_WORKS;
    add_char_params.cccd_write_access   = SEC_JUST_WORKS;
    add_char_params.is_defered_write    = 1;

    return characteristic_add(p_cgms->service_handle,
                              &add_char_params,
                              &p_cgms->char_handles.socp);
}


/**@brief Function for sending a response from the Specific Operation Control Point.
 *
 * @param[in]   p_cgms        Service instance.
 */
static void socp_send(nrf_ble_cgms_t * p_cgms)
{
    uint32_t               err_code;
    uint8_t                encoded_resp[25];
    uint8_t                len;
    uint16_t               hvx_len;
    ble_gatts_hvx_params_t hvx_params;

    // Send indication
    len     = ble_socp_encode(&(p_cgms->socp_response), encoded_resp);
    hvx_len = len;

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_params.handle = p_cgms->char_handles.socp.value_handle;
    hvx_params.type   = BLE_GATT_HVX_INDICATION;
    hvx_params.offset = 0;
    hvx_params.p_len  = &hvx_len;
    hvx_params.p_data = encoded_resp;

    err_code = sd_ble_gatts_hvx(p_cgms->conn_handle, &hvx_params);

    // Error handling
    if ((err_code == NRF_SUCCESS) && (hvx_len != len))
    {
        err_code = NRF_ERROR_DATA_SIZE;
    }

    switch (err_code)
    {
        case NRF_SUCCESS:
            // Wait for HVC event.
            p_cgms->cgms_com_state = STATE_SOCP_RESPONSE_IND_VERIF;
            break;

        case NRF_ERROR_RESOURCES:
            // Wait for TX_COMPLETE event to retry transmission.
            p_cgms->cgms_com_state = STATE_SOCP_RESPONSE_PENDING;
            break;

        case NRF_ERROR_INVALID_STATE:
            // Make sure state machine returns to the default state.
            p_cgms->cgms_com_state = STATE_NO_COMM;
            break;

        default:
            // Report error to application.
            if (p_cgms->error_handler != NULL)
            {
                p_cgms->error_handler(err_code);
            }

            // Make sure state machine returns to the default state.
            p_cgms->cgms_com_state = STATE_NO_COMM;
            break;
    }
}


void encode_get_response(uint8_t rsp_code, ble_socp_rsp_t * p_rsp, uint16_t in_val)
{
    p_rsp->opcode    = rsp_code;
    p_rsp->rsp_code  = SOCP_RSP_SUCCESS;
    p_rsp->size_val += uint16_encode(in_val, &(p_rsp->resp_val[p_rsp->size_val]));
}


void decode_set_opcode(nrf_ble_cgms_t        * p_cgms,
                       ble_cgms_socp_value_t * rcv_val,
                       uint16_t                min,
                       uint16_t                max,
                       uint16_t              * p_val)
{
    uint16_t rcvd_val = uint16_decode(rcv_val->p_operand);

    if ((rcvd_val == NRF_BLE_CGMS_PLUS_INFINTE)
        || (rcvd_val == NRF_BLE_CGMS_MINUS_INFINTE)
        || (rcvd_val > max)
        || (rcvd_val < min))
    {
        p_cgms->socp_response.rsp_code = SOCP_RSP_OUT_OF_RANGE;
    }
    else
    {
        p_cgms->socp_response.rsp_code = SOCP_RSP_SUCCESS;
        *p_val                         = rcvd_val;
    }
}


static bool is_feature_present(nrf_ble_cgms_t * p_cgms, uint32_t feature)
{
    return (p_cgms->feature.feature & feature);
}


/**@brief Function for handling a write event to the Specific Operation Control Point.
 *
 * @param[in]   p_cgms        Service instance.
 * @param[in]   p_evt_write   WRITE event to be handled.
 */
static void on_socp_value_write(nrf_ble_cgms_t * p_cgms, ble_gatts_evt_write_t const * p_evt_write)
{
    ble_cgms_socp_value_t                 socp_request;
    nrf_ble_cgms_evt_t                    evt;
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    uint32_t                              err_code;

    memset(&auth_reply, 0, sizeof(auth_reply));

    auth_reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;

    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
    auth_reply.params.write.update      = 1;

    err_code = sd_ble_gatts_rw_authorize_reply(p_cgms->conn_handle, &auth_reply);
    if (err_code != NRF_SUCCESS)
    {
        if (p_cgms->error_handler != NULL)
        {
            p_cgms->error_handler(err_code);
        }
        return;
    }

    // Decode request
    ble_socp_decode(p_evt_write->len, p_evt_write->data, &socp_request);

    p_cgms->socp_response.opcode     = SOCP_RESPONSE_CODE;
    p_cgms->socp_response.req_opcode = socp_request.opcode;
    p_cgms->socp_response.rsp_code   = SOCP_RSP_OP_CODE_NOT_SUPPORTED;
    p_cgms->socp_response.size_val   = 0;


    switch (socp_request.opcode)
    {
        case SOCP_WRITE_CGM_COMMUNICATION_INTERVAL:
            p_cgms->socp_response.rsp_code = SOCP_RSP_SUCCESS;
            p_cgms->comm_interval          = socp_request.p_operand[0];
            evt.evt_type                   = NRF_BLE_CGMS_EVT_WRITE_COMM_INTERVAL;
            p_cgms->evt_handler(p_cgms, &evt);
            break;

        case SOCP_READ_CGM_COMMUNICATION_INTERVAL:
            p_cgms->socp_response.opcode      = SOCP_READ_CGM_COMMUNICATION_INTERVAL_RESPONSE;
            p_cgms->socp_response.resp_val[0] = p_cgms->comm_interval;
            p_cgms->socp_response.size_val++;
            break;

        case SOCP_START_THE_SESSION:
            if (p_cgms->is_session_started)
            {
                p_cgms->socp_response.rsp_code = SOCP_RSP_PROCEDURE_NOT_COMPLETED;
            }
            else if ((p_cgms->nb_run_session != 0) &&
                     !(is_feature_present(p_cgms, NRF_BLE_CGMS_FEAT_MULTIPLE_SESSIONS_SUPPORTED)))
            {
                p_cgms->socp_response.rsp_code = SOCP_RSP_PROCEDURE_NOT_COMPLETED;
            }
            else
            {
                p_cgms->socp_response.rsp_code = SOCP_RSP_SUCCESS;
                p_cgms->is_session_started     = true;
                p_cgms->nb_run_session++;

                if (p_cgms->evt_handler != NULL)
                {
                    evt.evt_type = NRF_BLE_CGMS_EVT_START_SESSION;
                    p_cgms->evt_handler(p_cgms, &evt);
                }

                ble_cgms_sst_t sst;
                memset(&sst, 0, sizeof(ble_cgms_sst_t));

                err_code = cgms_sst_set(p_cgms, &sst);
                if (err_code != NRF_SUCCESS)
                {
                    if (p_cgms->error_handler != NULL)
                    {
                        p_cgms->error_handler(err_code);
                    }
                }
                p_cgms->sensor_status.time_offset    = 0;
                p_cgms->sensor_status.status.status &= (~NRF_BLE_CGMS_STATUS_SESSION_STOPPED);

                err_code = nrf_ble_cgms_update_status(p_cgms, &p_cgms->sensor_status);
                if (err_code != NRF_SUCCESS)
                {
                    if (p_cgms->error_handler != NULL)
                    {
                        p_cgms->error_handler(err_code);
                    }
                }
            }
            break;

        case SOCP_STOP_THE_SESSION:
        {
            nrf_ble_cgm_status_t status;
            memset(&status, 0, sizeof(nrf_ble_cgm_status_t));

            p_cgms->evt_handler(p_cgms, &evt);
            p_cgms->socp_response.rsp_code = SOCP_RSP_SUCCESS;
            p_cgms->is_session_started     = false;

            status.time_offset   = p_cgms->sensor_status.time_offset;
            status.status.status = p_cgms->sensor_status.status.status |
                                   NRF_BLE_CGMS_STATUS_SESSION_STOPPED;

            if (p_cgms->evt_handler != NULL)
            {
                evt.evt_type = NRF_BLE_CGMS_EVT_STOP_SESSION;
                p_cgms->evt_handler(p_cgms, &evt);
            }
            err_code = nrf_ble_cgms_update_status(p_cgms, &status);
            if (err_code != NRF_SUCCESS)
            {
                if (p_cgms->error_handler != NULL)
                {
                    p_cgms->error_handler(err_code);
                }
            }
            break;
        }

        default:
            p_cgms->socp_response.rsp_code = SOCP_RSP_OP_CODE_NOT_SUPPORTED;
            break;
    }

    socp_send(p_cgms);
}


void cgms_socp_on_rw_auth_req(nrf_ble_cgms_t                             * p_cgms,
                              ble_gatts_evt_rw_authorize_request_t const * p_auth_req)
{
    if (p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        if (p_auth_req->request.write.handle == p_cgms->char_handles.socp.value_handle)
        {
            on_socp_value_write(p_cgms, &p_auth_req->request.write);
        }
    }
}


void cgms_socp_on_tx_complete(nrf_ble_cgms_t * p_cgms)
{
    if (p_cgms->cgms_com_state == STATE_SOCP_RESPONSE_PENDING)
    {
        socp_send(p_cgms);
    }
}


