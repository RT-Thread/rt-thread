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
#include <stdint.h>
#include <string.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "cgms_racp.h"
#include "cgms_db.h"
#include "cgms_meas.h"

#define OPERAND_FILTER_TYPE_RESV        0x00 // !< Filter type value reserved for future use.
#define OPERAND_FILTER_TYPE_SEQ_NUM     0x01 // !< Filter data using Sequence Number criteria.
#define OPERAND_FILTER_TYPE_FACING_TIME 0x02 // !< Filter data using User Facing Time criteria.

/**@brief Function for adding a characteristic for the Record Access Control Point.
 *
 * @param[in] p_cgms  Service instance.
 *
 * @return NRF_SUCCESS if characteristic was successfully added, otherwise an error code.
 */
ret_code_t cgms_racp_char_add(nrf_ble_cgms_t * p_cgms)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid                = BLE_UUID_RECORD_ACCESS_CONTROL_POINT_CHAR;
    add_char_params.max_len             = BLE_GATT_ATT_MTU_DEFAULT;
    add_char_params.init_len            = 0;
    add_char_params.p_init_value        = 0;
    add_char_params.is_var_len          = true;
    add_char_params.write_access        = SEC_JUST_WORKS;
    add_char_params.char_props.write    = true;
    add_char_params.char_props.indicate = true;
    add_char_params.cccd_write_access   = SEC_JUST_WORKS;
    add_char_params.is_defered_write    = 1;

    return characteristic_add(p_cgms->service_handle,
                              &add_char_params,
                              &p_cgms->char_handles.racp);
}


/**@brief Function for sending response from Specific Operation Control Point.
 *
 * @param[in]   p_cgms        Service instance.
 * @param[in]   p_racp_val   RACP value to be sent.
 */
static void racp_send(nrf_ble_cgms_t * p_cgms, ble_racp_value_t * p_racp_val)
{
    uint32_t               err_code;
    uint8_t                encoded_resp[25];
    uint8_t                len;
    uint16_t               hvx_len;
    ble_gatts_hvx_params_t hvx_params;

    if (
        (p_cgms->cgms_com_state != STATE_RACP_RESPONSE_PENDING)
        &&
        (p_cgms->racp_data.racp_proc_records_reported_since_txcomplete > 0)
       )
    {
        p_cgms->cgms_com_state = STATE_RACP_RESPONSE_PENDING;
        return;
    }

    // Send indication
    len     = ble_racp_encode(p_racp_val, encoded_resp);
    hvx_len = len;

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_params.handle = p_cgms->char_handles.racp.value_handle;
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
            p_cgms->cgms_com_state = STATE_RACP_RESPONSE_IND_VERIF;
            break;

        case NRF_ERROR_RESOURCES:
            // Wait for TX_COMPLETE event to retry transmission.
            p_cgms->cgms_com_state = STATE_RACP_RESPONSE_PENDING;
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


/**@brief Function for sending a RACP response containing a Response Code Op Code and Response Code Value.
 *
 * @param[in]   p_cgms   Service instance.
 * @param[in]   opcode   RACP Op Code.
 * @param[in]   value    RACP Response Code Value.
 */
static void racp_response_code_send(nrf_ble_cgms_t * p_cgms, uint8_t opcode, uint8_t value)
{
    p_cgms->racp_data.pending_racp_response.opcode      = RACP_OPCODE_RESPONSE_CODE;
    p_cgms->racp_data.pending_racp_response.operator    = RACP_OPERATOR_NULL;
    p_cgms->racp_data.pending_racp_response.operand_len = 2;
    p_cgms->racp_data.pending_racp_response.p_operand   =
        p_cgms->racp_data.pending_racp_response_operand;

    p_cgms->racp_data.pending_racp_response_operand[0] = opcode;
    p_cgms->racp_data.pending_racp_response_operand[1] = value;

    racp_send(p_cgms, &p_cgms->racp_data.pending_racp_response);
}


/**@brief Function for responding to the ALL operation.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t racp_report_records_all(nrf_ble_cgms_t * p_cgms)
{
    uint16_t total_records = cgms_db_num_records_get();
    uint16_t cur_nb_rec;
    uint8_t  i;
    uint8_t  nb_rec_to_send;

    if (p_cgms->racp_data.racp_proc_record_ndx >= total_records)
    {
        p_cgms->cgms_com_state = STATE_NO_COMM;
    }
    else
    {
        uint32_t       err_code;
        ble_cgms_rec_t rec[NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX];

        cur_nb_rec = total_records - p_cgms->racp_data.racp_proc_record_ndx;
        if (cur_nb_rec > NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX)
        {
            cur_nb_rec = NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX;
        }
        nb_rec_to_send = (uint8_t)cur_nb_rec;

        for (i = 0; i < cur_nb_rec; i++)
        {
            err_code = cgms_db_record_get(p_cgms->racp_data.racp_proc_record_ndx + i, &(rec[i]));
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
        err_code = cgms_meas_send(p_cgms, rec, &nb_rec_to_send);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        p_cgms->racp_data.racp_proc_record_ndx += nb_rec_to_send;
    }

    return NRF_SUCCESS;
}


/**@brief Function for responding to the FIRST or the LAST operation.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t racp_report_records_first_last(nrf_ble_cgms_t * p_cgms)
{
    uint32_t       err_code;
    ble_cgms_rec_t rec;
    uint16_t       total_records;
    uint8_t        nb_rec_to_send = 1;

    total_records = cgms_db_num_records_get();

    if ((p_cgms->racp_data.racp_proc_records_reported != 0) || (total_records == 0))
    {
        p_cgms->cgms_com_state = STATE_NO_COMM;
    }
    else
    {
        if (p_cgms->racp_data.racp_proc_operator == RACP_OPERATOR_FIRST)
        {
            err_code = cgms_db_record_get(0, &rec);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
        else if (p_cgms->racp_data.racp_proc_operator == RACP_OPERATOR_LAST)
        {
            err_code = cgms_db_record_get(total_records - 1, &rec);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }

        err_code = cgms_meas_send(p_cgms, &rec, &nb_rec_to_send);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        p_cgms->racp_data.racp_proc_record_ndx++;
    }

    return NRF_SUCCESS;
}


/**@brief Function for responding to the LESS OR EQUAL operation.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t racp_report_records_less_equal(nrf_ble_cgms_t * p_cgms)
{
    uint16_t total_rec_nb;
    uint16_t total_rec_nb_to_send;
    uint16_t rec_nb_left_to_send;
    uint8_t nb_rec_to_send;
    uint16_t offset;
    uint16_t i;

    if(p_cgms->racp_data.racp_request.operand_len != 2)
    {
        if (p_cgms->error_handler != NULL)
        {
            p_cgms->error_handler(NRF_ERROR_INVALID_LENGTH);
        }
    }

    total_rec_nb         = cgms_db_num_records_get();

    offset = uint16_decode(p_cgms->racp_data.racp_request.p_operand);
    if (offset >= total_rec_nb)
    {
        p_cgms->cgms_com_state = STATE_NO_COMM;
        return NRF_SUCCESS;
    }

    total_rec_nb_to_send = offset;

    if (p_cgms->racp_data.racp_proc_record_ndx >= total_rec_nb_to_send)
    {
        p_cgms->cgms_com_state = STATE_NO_COMM;
    }
    else
    {
        uint32_t       err_code;
        ble_cgms_rec_t rec[NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX];

        rec_nb_left_to_send = total_rec_nb_to_send - p_cgms->racp_data.racp_proc_records_reported;

        if (rec_nb_left_to_send > NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX)
        {
            nb_rec_to_send = NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX;
        }
        else
        {
            nb_rec_to_send = (uint8_t)rec_nb_left_to_send;
        }

        p_cgms->racp_data.racp_proc_record_ndx = 0;

        for (i = 0; i < nb_rec_to_send; i++)
        {
            err_code = cgms_db_record_get(p_cgms->racp_data.racp_proc_record_ndx + i, &(rec[i]));
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
        err_code = cgms_meas_send(p_cgms, rec, &nb_rec_to_send);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        p_cgms->racp_data.racp_proc_record_ndx += nb_rec_to_send;
    }

   return NRF_SUCCESS;
}


/**@brief Function for responding to the GREATER OR EQUAL operation.
 *
 * @param[in]   p_cgms   Service instance.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t racp_report_records_greater_equal(nrf_ble_cgms_t * p_cgms)
{
    uint16_t total_rec_nb;
    uint16_t total_rec_nb_to_send;
    uint16_t rec_nb_left_to_send;
    uint8_t nb_rec_to_send;
    uint16_t offset;
    uint16_t i;

    if(p_cgms->racp_data.racp_request.operand_len != 2)
    {
        if (p_cgms->error_handler != NULL)
        {
            p_cgms->error_handler(NRF_ERROR_INVALID_LENGTH);
        }
    }

    total_rec_nb         = cgms_db_num_records_get();

    offset = uint16_decode(p_cgms->racp_data.racp_request.p_operand);
    if (offset >= total_rec_nb)
    {
        p_cgms->cgms_com_state = STATE_NO_COMM;
        return NRF_SUCCESS;
    }

    total_rec_nb_to_send = total_rec_nb - offset;

    if (p_cgms->racp_data.racp_proc_record_ndx >= total_rec_nb_to_send)
    {
        p_cgms->cgms_com_state = STATE_NO_COMM;
    }
    else
    {
        uint32_t       err_code;
        ble_cgms_rec_t rec[NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX];

        rec_nb_left_to_send = total_rec_nb_to_send - p_cgms->racp_data.racp_proc_records_reported;

        if (rec_nb_left_to_send > NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX)
        {
            nb_rec_to_send = NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX;
        }
        else
        {
            nb_rec_to_send = (uint8_t)rec_nb_left_to_send;
        }

        p_cgms->racp_data.racp_proc_record_ndx = offset;

        for (i = 0; i < nb_rec_to_send; i++)
        {
            err_code = cgms_db_record_get(p_cgms->racp_data.racp_proc_record_ndx + i, &(rec[i]));
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
        err_code = cgms_meas_send(p_cgms, rec, &nb_rec_to_send);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        p_cgms->racp_data.racp_proc_record_ndx += nb_rec_to_send;
    }

   return NRF_SUCCESS;
}

/**@brief Function for informing that the REPORT RECORDS procedure is completed.
 *
 * @param[in]   p_cgms   Service instance.
 */
static void racp_report_records_completed(nrf_ble_cgms_t * p_cgms)
{
    uint8_t resp_code_value;

    if (p_cgms->racp_data.racp_proc_records_reported > 0)
    {
        resp_code_value = RACP_RESPONSE_SUCCESS;
    }
    else
    {
        resp_code_value = RACP_RESPONSE_NO_RECORDS_FOUND;
    }

    racp_response_code_send(p_cgms, RACP_OPCODE_REPORT_RECS, resp_code_value);
}


/**@brief Function for the RACP report records procedure.
 *
 * @param[in]   p_cgms   Service instance.
 */
static void racp_report_records_procedure(nrf_ble_cgms_t * p_cgms)
{
    uint32_t err_code;

    while (p_cgms->cgms_com_state == STATE_RACP_PROC_ACTIVE)
    {
        // Execute requested procedure
        switch (p_cgms->racp_data.racp_proc_operator)
        {
            case RACP_OPERATOR_ALL:
                err_code = racp_report_records_all(p_cgms);
                break;

            case RACP_OPERATOR_FIRST:
            case RACP_OPERATOR_LAST:
                err_code = racp_report_records_first_last(p_cgms);
                break;
            case RACP_OPERATOR_GREATER_OR_EQUAL:
                err_code = racp_report_records_greater_equal(p_cgms);
                break;
            case RACP_OPERATOR_LESS_OR_EQUAL:
                err_code = racp_report_records_less_equal(p_cgms);
                break;
            default:
                // Report error to application
                if (p_cgms->error_handler != NULL)
                {
                    p_cgms->error_handler(NRF_ERROR_INTERNAL);
                }

                // Make sure state machine returns to the default state
                // state_set(STATE_NO_COMM);
                p_cgms->cgms_com_state = STATE_NO_COMM;
                return;
        }

        // Error handling
        switch (err_code)
        {
            case NRF_SUCCESS:
                if (p_cgms->cgms_com_state != STATE_RACP_PROC_ACTIVE)
                {
                    racp_report_records_completed(p_cgms);
                }
                break;

            case NRF_ERROR_RESOURCES:
                // Wait for TX_COMPLETE event to resume transmission.
                return;

            case NRF_ERROR_INVALID_STATE:
                // Notification is probably not enabled. Ignore request.
                p_cgms->cgms_com_state = STATE_NO_COMM;
                return;

            default:
                // Report error to application.
                if (p_cgms->error_handler != NULL)
                {
                    p_cgms->error_handler(err_code);
                }

                // Make sure state machine returns to the default state.
                p_cgms->cgms_com_state = STATE_NO_COMM;
                return;
        }
    }
}


/**@brief Function for testing if the received request is to be executed.
 *
 * @param[in]    p_racp_request    Request to be checked.
 * @param[out]   p_response_code   Response code to be sent in case the request is rejected.
 *                                 RACP_RESPONSE_RESERVED is returned if the received message is
 *                                 to be rejected without sending a respone.
 *
 * @return       TRUE if the request is to be executed, FALSE if it is to be rejected.
 *               If it is to be rejected, p_response_code will contain the response code to be
 *               returned to the central.
 */
static bool is_request_to_be_executed(nrf_ble_cgms_t         * p_cgms,
                                      const ble_racp_value_t * p_racp_request,
                                      uint8_t                * p_response_code)
{
    *p_response_code = RACP_RESPONSE_RESERVED;

    if (p_racp_request->opcode == RACP_OPCODE_ABORT_OPERATION)
    {
        if (p_cgms->cgms_com_state == STATE_RACP_PROC_ACTIVE)
        {
            if (p_racp_request->operator != RACP_OPERATOR_NULL)
            {
                *p_response_code = RACP_RESPONSE_INVALID_OPERATOR;
            }
            else if (p_racp_request->operand_len != 0)
            {
                *p_response_code = RACP_RESPONSE_INVALID_OPERAND;
            }
            else
            {
                *p_response_code = RACP_RESPONSE_SUCCESS;
            }
        }
        else
        {
            *p_response_code = RACP_RESPONSE_ABORT_FAILED;
        }
    }
    else if (p_cgms->cgms_com_state != STATE_NO_COMM)
    {
        return false;
    }
    // supported opcodes
    else if ((p_racp_request->opcode == RACP_OPCODE_REPORT_RECS) ||
             (p_racp_request->opcode == RACP_OPCODE_REPORT_NUM_RECS))
    {
        switch (p_racp_request->operator)
        {
            // operators WITHOUT a filter
            case RACP_OPERATOR_ALL:
            case RACP_OPERATOR_FIRST:
            case RACP_OPERATOR_LAST:
                if (p_racp_request->operand_len != 0)
                {
                    *p_response_code = RACP_RESPONSE_INVALID_OPERAND;
                }
                break;

            // operators WITH a filter
            case RACP_OPERATOR_GREATER_OR_EQUAL:
                //*p_response_code = RACP_RESPONSE_OPERATOR_UNSUPPORTED;
                break;

            // unsupported operators
            case RACP_OPERATOR_LESS_OR_EQUAL:
                break;
            case RACP_OPERATOR_RANGE:
                *p_response_code = RACP_RESPONSE_OPERATOR_UNSUPPORTED;
                break;

            // invalid operators
            case RACP_OPERATOR_NULL:
            default:
                *p_response_code = RACP_RESPONSE_INVALID_OPERATOR;
                break;
        }
    }
    // unsupported opcodes
    else if (p_racp_request->opcode == RACP_OPCODE_DELETE_RECS)
    {
        *p_response_code = RACP_RESPONSE_OPCODE_UNSUPPORTED;
    }
    // unknown opcodes
    else
    {
        *p_response_code = RACP_RESPONSE_OPCODE_UNSUPPORTED;
    }

    // NOTE: The computation of the return value will change slightly when deferred write has been
    // implemented in the stack.
    return (*p_response_code == RACP_RESPONSE_RESERVED);
}


/**@brief Function for processing a REPORT RECORDS request.
 *
 * @param[in]   p_cgms           Service instance.
 * @param[in]   p_racp_request   Request to be executed.
 */
static void report_records_request_execute(nrf_ble_cgms_t   * p_cgms,
                                           ble_racp_value_t * p_racp_request)
{
    p_cgms->cgms_com_state = STATE_RACP_PROC_ACTIVE;

    p_cgms->racp_data.racp_proc_record_ndx       = 0;
    p_cgms->racp_data.racp_proc_operator         = p_racp_request->operator;
    p_cgms->racp_data.racp_proc_records_reported = 0;
    //p_cgms->
    racp_report_records_procedure(p_cgms);
}


/**@brief Function for processing a REPORT NUM RECORDS request.
 *
 * @param[in]   p_cgms           Service instance.
 * @param[in]   p_racp_request   Request to be executed.
 */
static void report_num_records_request_execute(nrf_ble_cgms_t   * p_cgms,
                                               ble_racp_value_t * p_racp_request)
{
    uint16_t total_records;
    uint16_t num_records;

    total_records = cgms_db_num_records_get();
    num_records   = 0;

    if (p_racp_request->operator == RACP_OPERATOR_ALL)
    {
        num_records = total_records;
    }
    else if ((p_racp_request->operator == RACP_OPERATOR_FIRST) ||
             (p_racp_request->operator == RACP_OPERATOR_LAST))
    {
        if (total_records > 0)
        {
            num_records = 1;
        }
    }

    p_cgms->racp_data.pending_racp_response.opcode      = RACP_OPCODE_NUM_RECS_RESPONSE;
    p_cgms->racp_data.pending_racp_response.operator    = RACP_OPERATOR_NULL;
    p_cgms->racp_data.pending_racp_response.operand_len = sizeof(uint16_t);
    p_cgms->racp_data.pending_racp_response.p_operand   =
        p_cgms->racp_data.pending_racp_response_operand;

    p_cgms->racp_data.pending_racp_response_operand[0] = num_records & 0xFF;
    p_cgms->racp_data.pending_racp_response_operand[1] = num_records >> 8;

    racp_send(p_cgms, &p_cgms->racp_data.pending_racp_response);
}


/**@brief Function for handling a write event to the Record Access Control Point.
 *
 * @param[in]   p_cgms      Service instance.
 * @param[in]   p_evt_write WRITE event to be handled.
 */
static void on_racp_value_write(nrf_ble_cgms_t * p_cgms, ble_gatts_evt_write_t * p_evt_write)
{
//    ble_racp_value_t racp_request;
    uint8_t          response_code;

    // set up reply to authorized write.
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    uint32_t                              err_code;

    auth_reply.type                = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
    auth_reply.params.write.offset = 0;
    auth_reply.params.write.len    = 0;
    auth_reply.params.write.p_data = NULL;

    // Decode request
    ble_racp_decode(p_evt_write->len, p_evt_write->data, &p_cgms->racp_data.racp_request);

    // Check if request is to be executed
    if (is_request_to_be_executed(p_cgms,&p_cgms->racp_data.racp_request, &response_code))
    {
        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        auth_reply.params.write.update      = 1;

        err_code = sd_ble_gatts_rw_authorize_reply(p_cgms->conn_handle,
                                                   &auth_reply);
        if (err_code != NRF_SUCCESS)
        {
            if (p_cgms->error_handler != NULL)
            {
                p_cgms->error_handler(err_code);
            }
            return;
        }

        // Execute request
        if (p_cgms->racp_data.racp_request.opcode == RACP_OPCODE_REPORT_RECS)
        {
            report_records_request_execute(p_cgms, &p_cgms->racp_data.racp_request);
        }
        else if (p_cgms->racp_data.racp_request.opcode == RACP_OPCODE_REPORT_NUM_RECS)
        {
            report_num_records_request_execute(p_cgms, &p_cgms->racp_data.racp_request);
        }
    }
    else if (response_code != RACP_RESPONSE_RESERVED)
    {
        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        auth_reply.params.write.update      = 1;
        err_code                            = sd_ble_gatts_rw_authorize_reply(p_cgms->conn_handle,
                                                                              &auth_reply);

        if (err_code != NRF_SUCCESS)
        {
            if (p_cgms->error_handler != NULL)
            {
                p_cgms->error_handler(err_code);
            }
            return;
        }
        // Abort any running procedure
        p_cgms->cgms_com_state = STATE_NO_COMM;

        // Respond with error code
        racp_response_code_send(p_cgms, p_cgms->racp_data.racp_request.opcode, response_code);
    }
    else
    {
        // ignore request
        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        auth_reply.params.write.update      = 1;
        err_code                            = sd_ble_gatts_rw_authorize_reply(p_cgms->conn_handle,
                                                                              &auth_reply);

        if (err_code != NRF_SUCCESS)
        {
            if (p_cgms->error_handler != NULL)
            {
                p_cgms->error_handler(err_code);
            }
            return;
        }
    }
}


void cgms_racp_on_rw_auth_req(nrf_ble_cgms_t                       * p_cgms,
                              ble_gatts_evt_rw_authorize_request_t * p_auth_req)
{
    if (p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        if (p_auth_req->request.write.handle == p_cgms->char_handles.racp.value_handle)
        {
            on_racp_value_write(p_cgms, &p_auth_req->request.write);
        }
    }
}


/**@brief Function for handling BLE_GATTS_EVT_HVN_TX_COMPLETE events.
 *
 * @param[in]   p_cgms      Glucose Service structure.
 */
void cgms_racp_on_tx_complete(nrf_ble_cgms_t * p_cgms)
{
    p_cgms->racp_data.racp_proc_records_reported_since_txcomplete = 0;

    if (p_cgms->cgms_com_state == STATE_RACP_RESPONSE_PENDING)
    {
        racp_send(p_cgms, &p_cgms->racp_data.pending_racp_response);
    }
    else if (p_cgms->cgms_com_state == STATE_RACP_PROC_ACTIVE)
    {
        racp_report_records_procedure(p_cgms);
    }
}


