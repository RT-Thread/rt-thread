/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#include "ble_ln_cp.h"
#include "ble_ln_db.h"
#include "ble_ln_common.h"
#include "sdk_common.h"

#define NRF_LOG_MODULE_NAME ble_ln_cp
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

// Feature Mask bits
#define FEATURE_MASK_INSTANTANEOUS_SPEED                 (0x01 << 0)         /**< Instantaneous Speed mask bit. */
#define FEATURE_MASK_TOTAL_DISTANCE                      (0x01 << 1)         /**< Total Distance mask bit. */
#define FEATURE_MASK_LOCATION                            (0x01 << 2)         /**< Location mask bit. */
#define FEATURE_MASK_ELEVATION                           (0x01 << 3)         /**< Elevation mask bit. */
#define FEATURE_MASK_HEADING                             (0x01 << 4)         /**< Heading mask bit. */
#define FEATURE_MASK_ROLLING_TIME                        (0x01 << 5)         /**< Rolling Time mask bit. */
#define FEATURE_MASK_UTC_TIME                            (0x01 << 6)         /**< UTC Time mask bit. */

// Data Control point parameter type lengths.
#define INT8_LEN   1
#define INT16_LEN  2
#define INT24_LEN  3
#define INT32_LEN  4

#define OPCODE_LENGTH                                   1  /**< Length of opcode inside Location and Navigation Measurement packet. */
#define HANDLE_LENGTH                                   2  /**< Length of handle inside Location and Navigation Measurement packet. */

static ble_lncp_rsp_code_t notify_app(ble_lncp_t const * p_lncp, ble_lncp_evt_t const * p_evt)
{
    ble_lncp_rsp_code_t rsp = LNCP_RSP_SUCCESS;

    if (p_lncp->evt_handler != NULL)
    {
        rsp = p_lncp->evt_handler(p_lncp, p_evt);
    }

    return rsp;
}


static void resp_send(ble_lncp_t * p_lncp)
{
    // Send indication
    uint16_t               hvx_len;
    uint8_t                hvx_data[MAX_CTRL_POINT_RESP_PARAM_LEN];
    ble_gatts_hvx_params_t hvx_params;
    uint32_t               err_code;

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_len = 3 + p_lncp->pending_rsp.rsp_param_len;
    hvx_data[0] = LNCP_OP_RESPONSE_CODE;
    hvx_data[1] = p_lncp->pending_rsp.op_code;
    hvx_data[2] = p_lncp->pending_rsp.rsp_code;

    memcpy(&hvx_data[3], &p_lncp->pending_rsp.rsp_param[0], p_lncp->pending_rsp.rsp_param_len);

    hvx_params.handle   = p_lncp->ctrlpt_handles.value_handle;
    hvx_params.type     = BLE_GATT_HVX_INDICATION;
    hvx_params.offset   = 0;
    hvx_params.p_len    = &hvx_len;
    hvx_params.p_data   = hvx_data;

    err_code = sd_ble_gatts_hvx(p_lncp->conn_handle, &hvx_params);

    // Error handling
    if ((err_code == NRF_SUCCESS) && (hvx_len != p_lncp->pending_rsp.rsp_param_len + 3))
    {
        err_code = NRF_ERROR_DATA_SIZE;
    }

    switch (err_code)
    {
        case NRF_SUCCESS:
            p_lncp->procedure_status = LNCP_STATE_CONFIRMATION_PENDING;
            // Wait for HVC event
            break;

        case NRF_ERROR_RESOURCES:
            // Wait for TX_COMPLETE event to retry transmission
            p_lncp->procedure_status = LNCP_STATE_INDICATION_PENDING;
            break;

        default:
            p_lncp->procedure_status = LNCP_STATE_INDICATION_PENDING;
            // error
            if (p_lncp->error_handler != NULL)
            {
                p_lncp->error_handler(err_code);
            }
            break;
    }
}


static void on_connect(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt)
{
    memset(&p_lncp->mask, 0, sizeof(ble_lncp_mask_t));
    p_lncp->conn_handle        = p_ble_evt->evt.gap_evt.conn_handle;
    p_lncp->procedure_status   = LNCP_STATE_NO_PROC_IN_PROGRESS;
}


static void on_disconnect(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_lncp->conn_handle        = BLE_CONN_HANDLE_INVALID;
    p_lncp->procedure_status   = LNCP_STATE_NO_PROC_IN_PROGRESS;
}


static void on_hvc_confirm(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt)
{
    if (p_ble_evt->evt.gatts_evt.params.hvc.handle == p_lncp->ctrlpt_handles.value_handle)
    {
        if (p_lncp->procedure_status == LNCP_STATE_CONFIRMATION_PENDING)
        {
            p_lncp->procedure_status = LNCP_STATE_NO_PROC_IN_PROGRESS;
        }
        else
        {
            if (p_lncp->error_handler != NULL)
            {
                p_lncp->error_handler(NRF_ERROR_INVALID_STATE);
            }
        }
    }
}


static void on_tx_complete(ble_lncp_t * p_lncp)
{
    if (p_lncp->procedure_status == LNCP_STATE_INDICATION_PENDING)
    {
        resp_send(p_lncp);
    }
}


/**@brief Handle write events to the control point cccd.
 *
 * @param[in]   p_lncp       Location and Navigation Service structure.
 * @param[in]   p_evt_write Write event received from the BLE stack.
 */
static void on_lncp_cccd_write(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == BLE_CCCD_VALUE_LEN)
    {
        // CCCD written, update indications state
        p_lncp->is_ctrlpt_indication_enabled = ble_srv_is_indication_enabled(p_evt_write->data);
    }
}


/**@brief Handle write events to the navigation cccd.
 *
 * @param[in]   p_lncp      Location and Navigation Service structure.
 * @param[in]   p_evt_write Write event received from the BLE stack.
 */
static void on_nav_cccd_write(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == BLE_CCCD_VALUE_LEN)
    {
        // CCCD written, update notification state
        p_lncp->is_nav_notification_enabled = ble_srv_is_notification_enabled(p_evt_write->data);
    }
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_set_cumulative_value(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    if ( !(p_lncp->available_features & BLE_LNS_FEATURE_TOTAL_DISTANCE_SUPPORTED) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH + INT24_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const uint32_t total_distance = uint24_decode(&p_evt_write->data[1]);

    const ble_lncp_evt_t evt = {
        .evt_type = LNCP_EVT_TOTAL_DISTANCE_SET,
        .params.total_distance = total_distance
    };
    p_lncp->pending_rsp.rsp_code = notify_app(p_lncp, &evt);

    if (p_lncp->pending_rsp.rsp_code == LNCP_RSP_SUCCESS)
    {
        p_lncp->total_distance = total_distance;
    }

}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_mask_loc_speed_content(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    if ( !(p_lncp->available_features & BLE_LNS_FEATURE_LOC_AND_SPEED_CONTENT_MASKING_SUPPORTED) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH + INT16_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    uint16_t rcvd_mask = uint16_decode(&p_evt_write->data[1]);

    if (rcvd_mask > 0x7F)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const ble_lncp_evt_t evt = {
        .evt_type = LNCP_EVT_MASK_SET,
        .params.mask.flags = rcvd_mask
    };
    p_lncp->pending_rsp.rsp_code = notify_app(p_lncp, &evt);

    if (p_lncp->pending_rsp.rsp_code == LNCP_RSP_SUCCESS)
    {
        p_lncp->mask.flags = rcvd_mask;
    }
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_nav_control(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    if ( !(p_lncp->is_navigation_present) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != LNCP_NAV_CMD_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    /*lint --e{415} --e{416} -save suppress Warning 415: possible access out of bond */
    const uint8_t data_buf = p_evt_write->data[1];
    /*lint -restore*/

    if (data_buf > LNCP_NAV_CMD_MAX)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const ble_lncp_nav_cmd_t cmd = (ble_lncp_nav_cmd_t) data_buf;

    if (cmd == LNCP_CMD_NAV_START || cmd == LNCP_CMD_NAV_CONTINUE || cmd == LNCP_CMD_NAV_NEAREST)
    {
        p_lncp->is_navigation_running = true;
    }
    else if (cmd == LNCP_CMD_NAV_STOP || cmd == LNCP_CMD_NAV_PAUSE)
    {
        p_lncp->is_navigation_running = false;
    }

    const ble_lncp_evt_t evt = {
        .evt_type = LNCP_EVT_NAV_COMMAND,
        .params.nav_cmd = cmd
    };
    p_lncp->pending_rsp.rsp_code = notify_app(p_lncp, &evt);
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_req_num_routes(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    p_lncp->pending_rsp.rsp_code = LNCP_RSP_SUCCESS;

    if ( !(p_lncp->is_navigation_present) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const uint8_t num_records = ble_ln_db_num_records_get();
    p_lncp->pending_rsp.rsp_param_len = uint16_encode(num_records, &p_lncp->pending_rsp.rsp_param[0]);
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_req_name_of_route(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    uint8_t * p_name;
    uint32_t err_code;

    p_lncp->pending_rsp.rsp_code = LNCP_RSP_SUCCESS;

    if ( !(p_lncp->is_navigation_present) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH + INT16_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    /*lint --e{415} --e{416} -save suppress Warning 415: possible access out of bond */
    const uint16_t route_num = uint16_decode(&p_evt_write->data[1]);
    /*lint -restore*/

    err_code = ble_ln_db_record_name_get(route_num, &p_name);
    if (err_code != NRF_SUCCESS)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OPERATION_FAILED;
        return;
    }
    memcpy(&p_lncp->pending_rsp.rsp_param[0], p_name, BLE_LNS_MAX_ROUTE_NAME_LEN);

    p_lncp->pending_rsp.rsp_param_len = BLE_LNS_MAX_ROUTE_NAME_LEN;
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_select_route(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    if ( !(p_lncp->is_navigation_present))
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH + INT16_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const uint16_t route_num  = uint16_decode(&p_evt_write->data[1]);
    const uint16_t stored_num = ble_ln_db_num_records_get();

    if (route_num >= stored_num)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const ble_lncp_evt_t evt = {
        .evt_type = LNCP_EVT_ROUTE_SELECTED,
        .params.selected_route = route_num
    };
    p_lncp->pending_rsp.rsp_code = notify_app(p_lncp, &evt);

    if (p_lncp->pending_rsp.rsp_code == LNCP_RSP_SUCCESS)
    {
        p_lncp->selected_route = route_num;
    }
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_set_fix_rate(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    p_lncp->pending_rsp.rsp_code = LNCP_RSP_SUCCESS;

    if ( !(p_lncp->available_features & BLE_LNS_FEATURE_FIX_RATE_SETTING_SUPPORTED) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH + INT8_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    /*lint --e{415} --e{416} -save suppress Warning 415: possible access out of bond */
    const uint8_t fix_rate = p_evt_write->data[1];
    /*lint -restore*/

    const ble_lncp_evt_t evt = {
        .evt_type           = LNCP_EVT_FIX_RATE_SET,
        .params.fix_rate    = fix_rate
    };
    p_lncp->pending_rsp.rsp_code = notify_app(p_lncp, &evt);

    if (p_lncp->pending_rsp.rsp_code == LNCP_RSP_SUCCESS)
    {
        p_lncp->fix_rate = fix_rate;
    }
}


/**@brief Event handler for control point write.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_set_elevation(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    p_lncp->pending_rsp.rsp_code = LNCP_RSP_SUCCESS;

    if ( !(p_lncp->available_features & BLE_LNS_FEATURE_ELEVATION_SETTING_SUPPORTED) )
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
        return;
    }

    if (p_evt_write->len != OPCODE_LENGTH + INT24_LEN)
    {
        p_lncp->pending_rsp.rsp_code = LNCP_RSP_INVALID_PARAMETER;
        return;
    }

    const uint32_t elevation = uint24_decode(&p_evt_write->data[1]);
    ble_lncp_evt_t evt = {
        .evt_type = LNCP_EVT_ELEVATION_SET,
        .params.elevation = elevation
    };
    p_lncp->pending_rsp.rsp_code = notify_app(p_lncp, &evt);

    if (p_lncp->pending_rsp.rsp_code == LNCP_RSP_SUCCESS)
    {
        p_lncp->elevation = elevation;
    }
}


/**@brief Handle write events to the Location and Navigation Service Control Point characteristic.
 *
 * @param[in]   p_lncp         Location and Navigation Service structure.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_ctrlpt_write(ble_lncp_t * p_lncp, ble_gatts_evt_write_t const * p_evt_write)
{
    uint32_t      err_code;

    p_lncp->pending_rsp.rsp_param_len = 0;

    ble_gatts_rw_authorize_reply_params_t write_authorize_reply;
    memset(&write_authorize_reply, 0, sizeof(write_authorize_reply));

    write_authorize_reply.type   = BLE_GATTS_AUTHORIZE_TYPE_WRITE;

    if (p_lncp->is_ctrlpt_indication_enabled)
    {
        if (p_lncp->procedure_status == LNCP_STATE_NO_PROC_IN_PROGRESS)
        {
            write_authorize_reply.params.write.update      = 1;
            write_authorize_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;

            // if the op code is navigation control, its cccd must be checked
            if (p_evt_write->len > 0 && p_lncp->is_navigation_present)
            {
                if (   p_evt_write->data[0] == LNCP_OP_NAV_CONTROL
                    || p_evt_write->data[0] == LNCP_OP_REQ_NAME_OF_ROUTE
                    || p_evt_write->data[0] == LNCP_OP_REQ_NUM_ROUTES)
                {
                    if (!p_lncp->is_nav_notification_enabled)
                    {
                        write_authorize_reply.params.write.gatt_status = LNCP_RSP_CCCD_CONFIG_IMPROPER;
                    }
                }
            }
        }
        else
        {
            write_authorize_reply.params.write.gatt_status = LNCP_RSP_PROC_ALR_IN_PROG;
        }
    }
    else
    {
        write_authorize_reply.params.write.gatt_status = LNCP_RSP_CCCD_CONFIG_IMPROPER;
    }

    // reply to the write authorization
    do {
        err_code = sd_ble_gatts_rw_authorize_reply(p_lncp->conn_handle, &write_authorize_reply);
        if (err_code != NRF_SUCCESS && err_code != NRF_ERROR_BUSY)
        {
            if (p_lncp->error_handler != NULL)
            {
                p_lncp->error_handler(err_code);
            }
        }
    } while (err_code == NRF_ERROR_BUSY);


    if (write_authorize_reply.params.write.gatt_status != BLE_GATT_STATUS_SUCCESS)
    {
        return;
    }

    // Start executing the control point write action
    p_lncp->procedure_status = LNCP_STATE_INDICATION_PENDING;
    if (p_evt_write->len > 0)
    {
        p_lncp->pending_rsp.op_code = (ble_lncp_op_code_t) p_evt_write->data[0];
        switch (p_lncp->pending_rsp.op_code)
        {
            case LNCP_OP_SET_CUMULATIVE_VALUE:
                on_set_cumulative_value(p_lncp, p_evt_write);
                break;

            case LNCP_OP_MASK_LOC_SPEED_CONTENT:
                on_mask_loc_speed_content(p_lncp, p_evt_write);
                break;

            case LNCP_OP_NAV_CONTROL:
                on_nav_control(p_lncp, p_evt_write);
                break;

            case LNCP_OP_REQ_NUM_ROUTES:
                on_req_num_routes(p_lncp, p_evt_write);
                break;

            case LNCP_OP_REQ_NAME_OF_ROUTE:
                on_req_name_of_route(p_lncp, p_evt_write);
                break;

            case LNCP_OP_SELECT_ROUTE:
                on_select_route(p_lncp, p_evt_write);
                break;

            case LNCP_OP_SET_FIX_RATE:
                on_set_fix_rate(p_lncp, p_evt_write);
                break;

            case LNCP_OP_SET_ELEVATION:
                on_set_elevation(p_lncp, p_evt_write);
                break;

            // Unrecognized Op Code
            default:
                p_lncp->pending_rsp.rsp_code = LNCP_RSP_OP_CODE_NOT_SUPPORTED;
                break;
        }

        resp_send(p_lncp);
    }
    else
    {
        p_lncp->procedure_status = LNCP_STATE_NO_PROC_IN_PROGRESS;
    }
}


/**@brief Write authorization request event handler.
 *
 * @details The write authorization request event handler is only called when writing to the control point.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_rw_authorize_req(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt)
{
    const ble_gatts_evt_rw_authorize_request_t * p_auth_req =
        &p_ble_evt->evt.gatts_evt.params.authorize_request;

    if (
        (p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
        &&
        (p_auth_req->request.write.handle == p_lncp->ctrlpt_handles.value_handle)
        &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_PREP_WRITE_REQ)
        &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)
        &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL)
       )
    {
        on_ctrlpt_write(p_lncp, &p_auth_req->request.write);
    }

}


/**@brief Write event handler.
 *
 * @param[in]   p_lncp     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_write(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt)
{
    const ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle == p_lncp->ctrlpt_handles.cccd_handle)
    {
        on_lncp_cccd_write(p_lncp, p_evt_write);
    }
    else if (p_evt_write->handle == p_lncp->navigation_handles.cccd_handle)
    {
        on_nav_cccd_write(p_lncp, p_evt_write);
    }
}


void ble_lncp_on_ble_evt(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_lncp);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_lncp, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            if (p_ble_evt->evt.gap_evt.conn_handle == p_lncp->conn_handle)
            {
                on_disconnect(p_lncp, p_ble_evt);
            }
            break;

        case BLE_GATTS_EVT_WRITE:
            if (p_ble_evt->evt.gatts_evt.conn_handle == p_lncp->conn_handle)
            {
                on_write(p_lncp, p_ble_evt);
            }
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            if (p_ble_evt->evt.gatts_evt.conn_handle == p_lncp->conn_handle)
            {
                on_rw_authorize_req(p_lncp, p_ble_evt);
            }
            break;

        case BLE_GATTS_EVT_HVC:
            if (p_ble_evt->evt.gatts_evt.conn_handle == p_lncp->conn_handle)
            {
                on_hvc_confirm(p_lncp, p_ble_evt);
            }
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            on_tx_complete(p_lncp);
            break;

        default:
            // no implementation
            break;
    }
}


uint32_t ble_lncp_total_distance_get(ble_lncp_t const * p_lncp)
{
    if (p_lncp == NULL)
    {
        return 0;
    }

    return p_lncp->total_distance;
}


uint32_t ble_lncp_elevation_get(ble_lncp_t const * p_lncp)
{
    if (p_lncp == NULL)
    {
        return 0;
    }

    return p_lncp->elevation;
}


ble_lncp_mask_t ble_lncp_mask_get(ble_lncp_t const * p_lncp)
{
    if (p_lncp == NULL)
    {
        const ble_lncp_mask_t empty_mask = {0};
        return empty_mask;
    }

    return p_lncp->mask;
}


bool ble_lncp_is_navigation_running(ble_lncp_t const * p_lncp)
{
    if (p_lncp == NULL)
    {
        return false;
    }

    return p_lncp->is_navigation_running;
}


ret_code_t ble_lncp_init(ble_lncp_t * p_lncp, ble_lncp_init_t const * p_lncp_init)
{
    VERIFY_PARAM_NOT_NULL(p_lncp);
    VERIFY_PARAM_NOT_NULL(p_lncp_init);

    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    p_lncp->service_handle               = p_lncp_init->service_handle;
    p_lncp->evt_handler                  = p_lncp_init->evt_handler;
    p_lncp->error_handler                = p_lncp_init->error_handler;
    p_lncp->available_features           = p_lncp_init->available_features;
    p_lncp->is_position_quality_present  = p_lncp_init->is_position_quality_present;
    p_lncp->is_navigation_present        = p_lncp_init->is_navigation_present;
    p_lncp->total_distance               = p_lncp_init->total_distance;
    p_lncp->elevation                    = p_lncp_init->elevation;
    p_lncp->navigation_handles           = p_lncp_init->navigation_handles;

    p_lncp->fix_rate                     = BLE_LNS_NO_FIX;
    p_lncp->selected_route               = BLE_LNS_INVALID_ROUTE;

    p_lncp->procedure_status             = LNCP_STATE_NO_PROC_IN_PROGRESS;
    p_lncp->conn_handle                  = BLE_CONN_HANDLE_INVALID;
    p_lncp->is_navigation_running        = false;
    p_lncp->is_nav_notification_enabled  = false;
    p_lncp->is_ctrlpt_indication_enabled = false;

    memset(&p_lncp->mask, 0, sizeof(ble_lncp_mask_t));

    add_char_params.uuid                 = BLE_UUID_LN_CONTROL_POINT_CHAR;
    add_char_params.max_len              = 0;
    add_char_params.char_props.indicate  = true;
    add_char_params.char_props.write     = true;
    add_char_params.is_defered_write     = true;
    add_char_params.is_var_len           = true;
    add_char_params.max_len              = BLE_GATT_ATT_MTU_DEFAULT;
    add_char_params.write_access         = p_lncp_init->write_perm;
    add_char_params.cccd_write_access    = p_lncp_init->cccd_write_perm;

    NRF_LOG_DEBUG("Initialized");

    return characteristic_add(p_lncp->service_handle,
                              &add_char_params,
                              &p_lncp->ctrlpt_handles);
}
