/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
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

#include "ble_sc_ctrlpt.h"
#include <string.h>
#include "nordic_common.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "app_util.h"

#define SC_CTRLPT_NACK_PROC_ALREADY_IN_PROGRESS   (BLE_GATT_STATUS_ATTERR_APP_BEGIN + 0)
#define SC_CTRLPT_NACK_CCCD_IMPROPERLY_CONFIGURED (BLE_GATT_STATUS_ATTERR_APP_BEGIN + 1)

uint32_t ble_sc_ctrlpt_init(ble_sc_ctrlpt_t            * p_sc_ctrlpt,
                            const ble_cs_ctrlpt_init_t * p_sc_ctrlpt_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    p_sc_ctrlpt->conn_handle      = BLE_CONN_HANDLE_INVALID;
    p_sc_ctrlpt->procedure_status = BLE_SCPT_NO_PROC_IN_PROGRESS;

    p_sc_ctrlpt->size_list_supported_locations = p_sc_ctrlpt_init->size_list_supported_locations;

    if ((p_sc_ctrlpt_init->size_list_supported_locations != 0) &&
        (p_sc_ctrlpt_init->list_supported_locations != NULL))
    {
        memcpy(p_sc_ctrlpt->list_supported_locations,
               p_sc_ctrlpt_init->list_supported_locations,
               p_sc_ctrlpt->size_list_supported_locations * sizeof(ble_sensor_location_t));
    }

    p_sc_ctrlpt->service_handle         = p_sc_ctrlpt_init->service_handle;
    p_sc_ctrlpt->evt_handler            = p_sc_ctrlpt_init->evt_handler;
    p_sc_ctrlpt->supported_functions    = p_sc_ctrlpt_init->supported_functions;
    p_sc_ctrlpt->sensor_location_handle = p_sc_ctrlpt_init->sensor_location_handle;
    p_sc_ctrlpt->error_handler          = p_sc_ctrlpt_init->error_handler;

    memset(&cccd_md, 0, sizeof(cccd_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    cccd_md.write_perm = p_sc_ctrlpt_init->sc_ctrlpt_attr_md.cccd_write_perm;
    cccd_md.vloc       = BLE_GATTS_VLOC_STACK;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.indicate = 1;
    char_md.char_props.write    = 1;
    char_md.p_char_user_desc    = NULL;
    char_md.p_char_pf           = NULL;
    char_md.p_user_desc_md      = NULL;
    char_md.p_cccd_md           = &cccd_md;
    char_md.p_sccd_md           = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_SC_CTRLPT_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    attr_md.write_perm = p_sc_ctrlpt_init->sc_ctrlpt_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 1;
    attr_md.vlen       = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 0;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BLE_SC_CTRLPT_MAX_LEN;
    attr_char_value.p_value   = 0;

    return sd_ble_gatts_characteristic_add(p_sc_ctrlpt->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_sc_ctrlpt->sc_ctrlpt_handles);
}


/**@brief Decode an incoming control point write.
 *
 * @param[in]    rcvd_val       received write value
 * @param[in]    len            value length
 * @param[out]   decoded_ctrlpt decoded control point structure
 */
static uint32_t sc_ctrlpt_decode(uint8_t             * p_rcvd_val,
                                 uint8_t               len,
                                 ble_sc_ctrlpt_val_t * p_write_val)
{
    int pos = 0;

    if (len < BLE_SC_CTRLPT_MIN_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_write_val->opcode = (ble_scpt_operator_t) p_rcvd_val[pos++];

    switch (p_write_val->opcode)
    {
        case BLE_SCPT_REQUEST_SUPPORTED_SENSOR_LOCATIONS:
            break;

        case BLE_SCPT_START_AUTOMATIC_CALIBRATION:
            break;

        case BLE_SCPT_UPDATE_SENSOR_LOCATION:
            p_write_val->location = (ble_sensor_location_t)p_rcvd_val[pos];
            break;

        case BLE_SCPT_SET_CUMULATIVE_VALUE:
            p_write_val->cumulative_value = uint32_decode(&(p_rcvd_val[pos]));
            break;

        default:
            return NRF_ERROR_INVALID_PARAM;
    }
    return NRF_SUCCESS;
}


/**@brief encode a control point response indication.
 *
 * @param[in]   p_sc_ctrlpt      SC Ctrlpt structure.
 * @param[in]   p_ctrlpt_rsp  structure containing response data to be encoded
 * @param[out]  p_data        pointer where data needs to be written
 * @return                    size of encoded data
 */
static int ctrlpt_rsp_encode(ble_sc_ctrlpt_t     * p_sc_ctrlpt,
                             ble_sc_ctrlpt_rsp_t * p_ctrlpt_rsp,
                             uint8_t             * p_data)
{
    int len = 0;

    p_data[len++] = BLE_SCPT_RESPONSE_CODE;
    p_data[len++] = p_ctrlpt_rsp->opcode;
    p_data[len++] = p_ctrlpt_rsp->status;

    if (p_ctrlpt_rsp->status == BLE_SCPT_SUCCESS)
    {
        switch (p_ctrlpt_rsp->opcode)
        {
            case BLE_SCPT_REQUEST_SUPPORTED_SENSOR_LOCATIONS:
            {
                int i;
                for (i = 0; i < p_sc_ctrlpt->size_list_supported_locations; i++)
                {
                    p_data[len++] = p_sc_ctrlpt->list_supported_locations[i];
                }
                break;
            }

            default:
                // No implementation needed.
                break;
        }
    }
    return len;
}


/**@brief check if a given sensor location is supported or not.
 *
 * @param[in]   p_sc_ctrlpt      SC Ctrlpt structure.
 * @param[in]   location         sensor location to check.
 * @return  true if the given location is found in the list of supported locations, false otherwise.
 */
static bool is_location_supported(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_sensor_location_t location)
{
    int i;

    for (i = 0; i < p_sc_ctrlpt->size_list_supported_locations; i++)
    {
        if (p_sc_ctrlpt->list_supported_locations[i] == location)
        {
            return true;
        }
    }
    return false;
}


/**@brief check if the cccd is configured
 *
 * @param[in]   p_sc_ctrlpt      SC Ctrlpt structure.
 * @return  true if the sc_control point's cccd is correctly configured, false otherwise.
 */
static bool is_cccd_configured(ble_sc_ctrlpt_t * p_sc_ctrlpt)
{
    uint32_t err_code;
    uint8_t  cccd_value_buf[BLE_CCCD_VALUE_LEN];
    bool     is_sccp_indic_enabled = false;
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = cccd_value_buf;

    err_code = sd_ble_gatts_value_get(p_sc_ctrlpt->conn_handle,
                                      p_sc_ctrlpt->sc_ctrlpt_handles.cccd_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        // Report error to application
        if (p_sc_ctrlpt->error_handler != NULL)
        {
            p_sc_ctrlpt->error_handler(err_code);
        }
    }

    is_sccp_indic_enabled = ble_srv_is_indication_enabled(cccd_value_buf);

    return is_sccp_indic_enabled;
}


/**@brief sends a control point indication.
 *
 * @param[in]   p_sc_ctrlpt      SC Ctrlpt structure.
 */
static void sc_ctrlpt_resp_send(ble_sc_ctrlpt_t * p_sc_ctrlpt)
{
    uint16_t               hvx_len;
    ble_gatts_hvx_params_t hvx_params;
    uint32_t               err_code;

    if ((p_sc_ctrlpt->procedure_status == BLE_SCPT_INDICATION_PENDING))
    {
        hvx_len = p_sc_ctrlpt->response.len;
        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_sc_ctrlpt->sc_ctrlpt_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_INDICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = p_sc_ctrlpt->response.encoded_ctrl_rsp;

        err_code = sd_ble_gatts_hvx(p_sc_ctrlpt->conn_handle, &hvx_params);

        // Error handling
        if ((err_code == NRF_SUCCESS) && (hvx_len != p_sc_ctrlpt->response.len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }

        switch (err_code)
        {
            case NRF_SUCCESS:
                p_sc_ctrlpt->procedure_status = BLE_SCPT_IND_CONFIRM_PENDING;
                // Wait for HVC event
                break;

            case NRF_ERROR_RESOURCES:
                // Wait for TX_COMPLETE event to retry transmission.
                p_sc_ctrlpt->procedure_status = BLE_SCPT_INDICATION_PENDING;
                break;

            default:
                // Report error to application.
                p_sc_ctrlpt->procedure_status = BLE_SCPT_NO_PROC_IN_PROGRESS;
                if (p_sc_ctrlpt->error_handler != NULL)
                {
                    p_sc_ctrlpt->error_handler(err_code);
                }
                break;
        }
    }
}


/**@brief Handle a write event to the Speed and Cadence Control Point.
 *
 * @param[in]   p_sc_ctrlpt      SC Ctrlpt structure.
 * @param[in]   p_evt_write      WRITE event to be handled.
 */
static void on_ctrlpt_write(ble_sc_ctrlpt_t       * p_sc_ctrlpt,
                            ble_gatts_evt_write_t * p_evt_write)
{
    ble_sc_ctrlpt_val_t                   rcvd_ctrlpt =
    { BLE_SCPT_RESPONSE_CODE , 0, BLE_SENSOR_LOCATION_OTHER };

    ble_sc_ctrlpt_rsp_t                   rsp;
    uint32_t                              err_code;
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    ble_sc_ctrlpt_evt_t                   evt;

    auth_reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
    auth_reply.params.write.offset      = 0;
    auth_reply.params.write.len         = 0;
    auth_reply.params.write.p_data      = NULL;
    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
    auth_reply.params.write.update      = 1;

    if (is_cccd_configured(p_sc_ctrlpt))
    {
        if (p_sc_ctrlpt->procedure_status == BLE_SCPT_NO_PROC_IN_PROGRESS)
        {
            auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        }
        else
        {
            auth_reply.params.write.gatt_status = SC_CTRLPT_NACK_PROC_ALREADY_IN_PROGRESS;
        }
    }
    else
    {
        auth_reply.params.write.gatt_status = SC_CTRLPT_NACK_CCCD_IMPROPERLY_CONFIGURED;
    }

    err_code = sd_ble_gatts_rw_authorize_reply(p_sc_ctrlpt->conn_handle, &auth_reply);
    if (err_code != NRF_SUCCESS)
    {
        // Report error to application.
        if (p_sc_ctrlpt->error_handler != NULL)
        {
            p_sc_ctrlpt->error_handler(err_code);
        }
    }

    if (auth_reply.params.write.gatt_status != BLE_GATT_STATUS_SUCCESS)
    {
        return;
    }

    p_sc_ctrlpt->procedure_status = BLE_SCPT_INDICATION_PENDING;
    rsp.status                    = BLE_SCPT_OP_CODE_NOT_SUPPORTED;

    err_code = sc_ctrlpt_decode(p_evt_write->data, p_evt_write->len, &rcvd_ctrlpt);
    if (err_code != NRF_SUCCESS)
    {
        rsp.opcode = rcvd_ctrlpt.opcode;
        rsp.status = BLE_SCPT_OP_CODE_NOT_SUPPORTED;
    }
    else
    {
        rsp.opcode = rcvd_ctrlpt.opcode;

        switch (rcvd_ctrlpt.opcode)
        {
            case BLE_SCPT_REQUEST_SUPPORTED_SENSOR_LOCATIONS:
                if ((p_sc_ctrlpt->supported_functions &
                     BLE_SRV_SC_CTRLPT_SENSOR_LOCATIONS_OP_SUPPORTED) ==
                     BLE_SRV_SC_CTRLPT_SENSOR_LOCATIONS_OP_SUPPORTED)
                {
                    rsp.status = BLE_SCPT_SUCCESS;
                }
                else
                {
                    rsp.status = BLE_SCPT_OP_CODE_NOT_SUPPORTED;
                }
                break;

            case BLE_SCPT_UPDATE_SENSOR_LOCATION:
                if ((p_sc_ctrlpt->supported_functions &
                     BLE_SRV_SC_CTRLPT_SENSOR_LOCATIONS_OP_SUPPORTED) ==
                     BLE_SRV_SC_CTRLPT_SENSOR_LOCATIONS_OP_SUPPORTED)
                {
                    if (is_location_supported(p_sc_ctrlpt, rcvd_ctrlpt.location))
                    {
                        ble_gatts_value_t gatts_value;
                        uint8_t  rcvd_location = (uint8_t)rcvd_ctrlpt.location;
                        rsp.status = BLE_SCPT_SUCCESS;

                        // Initialize value struct.
                        memset(&gatts_value, 0, sizeof(gatts_value));

                        gatts_value.len     = sizeof(uint8_t);
                        gatts_value.offset  = 0;
                        gatts_value.p_value = &rcvd_location;

                        evt.evt_type               = BLE_SC_CTRLPT_EVT_UPDATE_LOCATION;
                        evt.params.update_location = rcvd_ctrlpt.location;
                        if (p_sc_ctrlpt->evt_handler != NULL)
                        {
                            rsp.status = p_sc_ctrlpt->evt_handler(p_sc_ctrlpt, &evt);
                        }
                        if (rsp.status == BLE_SCPT_SUCCESS)
                        {
                            err_code = sd_ble_gatts_value_set(p_sc_ctrlpt->conn_handle,
                                                              p_sc_ctrlpt->sensor_location_handle,
                                                              &gatts_value);
                            if (err_code != NRF_SUCCESS)
                            {
                                // Report error to application
                                if (p_sc_ctrlpt->error_handler != NULL)
                                {
                                    p_sc_ctrlpt->error_handler(err_code);
                                }
                                rsp.status = BLE_SCPT_OPERATION_FAILED;
                            }
                        }
                    }
                    else
                    {
                        rsp.status = BLE_SCPT_INVALID_PARAMETER;
                    }
                }
                else
                {
                    rsp.status = BLE_SCPT_OP_CODE_NOT_SUPPORTED;
                }
                break;

            case BLE_SCPT_SET_CUMULATIVE_VALUE:
                if ((p_sc_ctrlpt->supported_functions &
                     BLE_SRV_SC_CTRLPT_CUM_VAL_OP_SUPPORTED) ==
                     BLE_SRV_SC_CTRLPT_CUM_VAL_OP_SUPPORTED)
                {
                    rsp.status = BLE_SCPT_SUCCESS;

                    evt.evt_type                = BLE_SC_CTRLPT_EVT_SET_CUMUL_VALUE;
                    evt.params.cumulative_value = rcvd_ctrlpt.cumulative_value;
                    if (p_sc_ctrlpt->evt_handler != NULL)
                    {
                        rsp.status = p_sc_ctrlpt->evt_handler(p_sc_ctrlpt, &evt);
                    }
                }
                else
                {
                    rsp.status = BLE_SCPT_OP_CODE_NOT_SUPPORTED;
                }
                break;

            case BLE_SCPT_START_AUTOMATIC_CALIBRATION:
                if ((p_sc_ctrlpt->supported_functions &
                     BLE_SRV_SC_CTRLPT_START_CALIB_OP_SUPPORTED) ==
                     BLE_SRV_SC_CTRLPT_START_CALIB_OP_SUPPORTED)
                {
                    p_sc_ctrlpt->procedure_status = BLE_SCPT_AUTOMATIC_CALIB_IN_PROGRESS;
                    evt.evt_type                  = BLE_SC_CTRLPT_EVT_START_CALIBRATION;
                    if (p_sc_ctrlpt->evt_handler != NULL)
                    {
                        rsp.status = p_sc_ctrlpt->evt_handler(p_sc_ctrlpt, &evt);
                        if (rsp.status != BLE_SCPT_SUCCESS)
                        {
                            p_sc_ctrlpt->procedure_status = BLE_SCPT_INDICATION_PENDING; // If the application returns an error, the response is to be sent right away and the calibration is considered as not started.
                        }
                    }
                }
                else
                {
                    rsp.status = BLE_SCPT_OP_CODE_NOT_SUPPORTED;
                }
                break;

            default:
                rsp.status = BLE_SCPT_OP_CODE_NOT_SUPPORTED;
                break;
        }

    }

    p_sc_ctrlpt->response.len = ctrlpt_rsp_encode(p_sc_ctrlpt, &rsp,
                                                  p_sc_ctrlpt->response.encoded_ctrl_rsp);


    if (p_sc_ctrlpt->procedure_status == BLE_SCPT_INDICATION_PENDING)
    {
        sc_ctrlpt_resp_send(p_sc_ctrlpt);
    }
}


/**@brief Authorize WRITE request event handler.
 *
 * @details Handles WRITE events from the BLE stack.
 *
 * @param[in]   p_sc_ctrlpt  SC Ctrlpt structure.
 * @param[in]   p_gatts_evt  GATTS Event received from the BLE stack.
 *
 */
static void on_rw_authorize_request(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_gatts_evt_t * p_gatts_evt)
{
    ble_gatts_evt_rw_authorize_request_t * p_auth_req = &p_gatts_evt->params.authorize_request;
    if (p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        if (   (p_gatts_evt->params.authorize_request.request.write.op
                != BLE_GATTS_OP_PREP_WRITE_REQ)
            && (p_gatts_evt->params.authorize_request.request.write.op
                != BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)
            && (p_gatts_evt->params.authorize_request.request.write.op
                != BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL)
           )
        {
            if (p_auth_req->request.write.handle == p_sc_ctrlpt->sc_ctrlpt_handles.value_handle)
            {
                on_ctrlpt_write(p_sc_ctrlpt, &p_auth_req->request.write);
            }
        }
    }
}


/**@brief Tx Complete event handler.
 *
 * @details Tx Complete event handler.
 *          Handles WRITE events from the BLE stack and if an indication was pending try sending it
 *          again.
 *
 * @param[in]   p_sc_ctrlpt  SC Ctrlpt structure.
 *
 */
static void on_tx_complete(ble_sc_ctrlpt_t * p_sc_ctrlpt)
{
    if (p_sc_ctrlpt->procedure_status == BLE_SCPT_INDICATION_PENDING)
    {
        sc_ctrlpt_resp_send(p_sc_ctrlpt);
    }
}


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_sc_ctrlpt  SC Ctrlpt structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_evt_t * p_ble_evt)
{
    p_sc_ctrlpt->conn_handle      = p_ble_evt->evt.gap_evt.conn_handle;
    p_sc_ctrlpt->procedure_status = BLE_SCPT_NO_PROC_IN_PROGRESS;
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_sc_ctrlpt  SC Ctrlpt structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_sc_ctrlpt->conn_handle      = BLE_CONN_HANDLE_INVALID;
    p_sc_ctrlpt->procedure_status = BLE_SCPT_NO_PROC_IN_PROGRESS;
}


/**@brief Function for handling the BLE_GATTS_EVT_HVC event.
 *
 * @param[in]   p_sc_ctrlpt  SC Ctrlpt structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_sc_hvc_confirm(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_evt_t * p_ble_evt)
{
    if (p_ble_evt->evt.gatts_evt.params.hvc.handle == p_sc_ctrlpt->sc_ctrlpt_handles.value_handle)
    {
        if (p_sc_ctrlpt->procedure_status == BLE_SCPT_IND_CONFIRM_PENDING)
        {
            p_sc_ctrlpt->procedure_status = BLE_SCPT_NO_PROC_IN_PROGRESS;
        }
    }
}


void ble_sc_ctrlpt_on_ble_evt(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_sc_ctrlpt, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_sc_ctrlpt, p_ble_evt);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_authorize_request(p_sc_ctrlpt, &p_ble_evt->evt.gatts_evt);
            break;

        case BLE_GATTS_EVT_HVC:
            on_sc_hvc_confirm(p_sc_ctrlpt, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            on_tx_complete(p_sc_ctrlpt);
            break;

        default:
            break;
    }
}


uint32_t ble_sc_ctrlpt_rsp_send(ble_sc_ctrlpt_t * p_sc_ctrlpt, ble_scpt_response_t response_status)
{
    uint32_t               err_code = NRF_SUCCESS;
    ble_sc_ctrlpt_rsp_t    rsp;
    uint8_t                encoded_ctrl_rsp[BLE_SC_CTRLPT_MAX_LEN];
    uint16_t               hvx_len;
    ble_gatts_hvx_params_t hvx_params;

    if (p_sc_ctrlpt->procedure_status != BLE_SCPT_AUTOMATIC_CALIB_IN_PROGRESS)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    rsp.status = response_status;
    rsp.opcode = BLE_SCPT_START_AUTOMATIC_CALIBRATION;
    hvx_len    = ctrlpt_rsp_encode(p_sc_ctrlpt, &rsp, encoded_ctrl_rsp);

    // Send indication
    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_params.handle = p_sc_ctrlpt->sc_ctrlpt_handles.value_handle;
    hvx_params.type   = BLE_GATT_HVX_INDICATION;
    hvx_params.offset = 0;
    hvx_params.p_len  = &hvx_len;
    hvx_params.p_data = encoded_ctrl_rsp;

    err_code = sd_ble_gatts_hvx(p_sc_ctrlpt->conn_handle, &hvx_params);

    if (err_code == NRF_SUCCESS)
    {
        p_sc_ctrlpt->procedure_status = BLE_SCPT_NO_PROC_IN_PROGRESS;
    }
    return err_code;
}
