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
#include <string.h>

#include "nrf_ble_bms.h"
#include "ble_srv_common.h"

#define NRF_LOG_MODULE_NAME ble_bms
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/*@brief Check if a returned error code is NRF_SUCCESS, and call the error handler if not.
 *
 * @param[in] err_code Error code that should be checked.
 * @param[in] err_handler Error handler that should be called.
 */
static void error_check(ret_code_t err_code, ble_srv_error_handler_t err_handler)
{
    if (err_code != NRF_SUCCESS)
    {
        err_handler(err_code);
    }
}


/**@brief Function for adding the Bond Management Control Point characteristic.
 *
 * @param[in]   p_bms       Bond Management Service structure.
 * @param[in]   p_bms_init  Information needed to initialize the service.
 *
 * @return  NRF_SUCCESS on success, otherwise an error code returned by @ref characteristic_add.
 */
static ret_code_t ctrlpt_char_add(nrf_ble_bms_t * p_bms, nrf_ble_bms_init_t const * p_bms_init)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid             = BLE_UUID_BMS_CTRLPT;
    add_char_params.char_props.write = 1;
    add_char_params.is_defered_write = true;
    add_char_params.is_var_len       = true;
    add_char_params.max_len          = NRF_BLE_BMS_CTRLPT_MAX_LEN;
    add_char_params.read_access      = SEC_NO_ACCESS;
    add_char_params.write_access     = p_bms_init->bms_ctrlpt_sec_req;

    if (p_bms_init->p_qwr != NULL)
    {
        add_char_params.char_ext_props.reliable_wr = 1;
    }

    return characteristic_add(p_bms->service_handle, &add_char_params, &p_bms->ctrlpt_handles);
}


/**@brief Forward an authorization request to the application, if necessary.
 *
 * @param[in] p_bms    Bond Management Service structure.
 * @param[in] p_ctrlpt Pointer to the received Control Point value.
 */
static void ctrlpt_auth(nrf_ble_bms_t * p_bms, nrf_ble_bms_ctrlpt_t * p_ctrlpt)
{
    nrf_ble_bms_features_t * p_feature = &p_bms->feature;

    p_bms->auth_status = NRF_BLE_BMS_AUTH_STATUS_ALLOWED;

    /* Check if the authorization feature is enabled for this op code. */
    if ((
            (p_ctrlpt->op_code == NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_LE_ONLY) &&
            (p_feature->delete_requesting_auth)
        ) ||
        (
            (p_ctrlpt->op_code == NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_LE_ONLY) &&
            (p_feature->delete_all_auth)
        ) ||
        (
            (p_ctrlpt->op_code == NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_LE_ONLY) &&
            (p_feature->delete_all_but_requesting_auth)
        )
    )
    {
        if (p_bms->evt_handler != NULL)
        {
            nrf_ble_bms_evt_t bms_evt;

            memset(&bms_evt, 0, sizeof(bms_evt));
            bms_evt.evt_type      = NRF_BLE_BMS_EVT_AUTH;
            bms_evt.auth_code.len = p_ctrlpt->auth_code.len;
            memcpy(bms_evt.auth_code.code, p_ctrlpt->auth_code.code, p_ctrlpt->auth_code.len);

            p_bms->auth_status = NRF_BLE_BMS_AUTH_STATUS_PENDING;

            p_bms->evt_handler(p_bms, &bms_evt);
        }
        else
        {
            p_bms->auth_status = NRF_BLE_BMS_AUTH_STATUS_DENIED;
        }
    }
}


/**@brief Decode an incoming Control Point write.
 *
 * @param[in]    p_rcvd_val Received write value.
 * @param[in]    len        Value length.
 * @param[out]   p_ctrlpt   Decoded control point structure.
 *
 * @retval NRF_ERROR_INVALID_LENGTH The supplied value length is invalid.
 * @retval NRF_ERROR_NOT_SUPPORTED  The supplied op code is not supported.
 * @retval NRF_SUCCESS              Operation successful.
 */
static ret_code_t ctrlpt_decode(uint8_t const        * p_rcvd_val,
                                uint16_t               len,
                                nrf_ble_bms_ctrlpt_t * p_ctrlpt)
{
    uint16_t pos = 0;

    VERIFY_TRUE(len >= NRF_BLE_BMS_CTRLPT_MIN_LEN, NRF_ERROR_INVALID_LENGTH);
    VERIFY_TRUE(len <= NRF_BLE_BMS_CTRLPT_MAX_LEN, NRF_ERROR_INVALID_LENGTH);

    p_ctrlpt->op_code       = (nrf_ble_bms_op_t) p_rcvd_val[pos++];
    p_ctrlpt->auth_code.len = (len - pos);
    memcpy(p_ctrlpt->auth_code.code, &(p_rcvd_val[pos]), p_ctrlpt->auth_code.len);

    return NRF_SUCCESS;
}


/**@brief Function for performing an operation requested through the Control Point.
 *
 * @param[in]   p_bms   Bond Management Service structure.
 * @param[in]   op_code Op code to execute.
 */
static void ctrlpt_execute(nrf_ble_bms_t * p_bms, nrf_ble_bms_op_t op_code)
{
    switch (op_code)
    {
        case NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_LE_ONLY:
            /* Delete single bond */
            p_bms->bond_callbacks.delete_requesting(p_bms);
            break; // NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_LE_ONLY

        case NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_LE_ONLY:
            /* Delete all bonds */
            p_bms->bond_callbacks.delete_all(p_bms);
            break; // NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_LE_ONLY

        case NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_LE_ONLY:
            /* Delete all but current bond */
            p_bms->bond_callbacks.delete_all_except_requesting(p_bms);
            break; // NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_LE_ONLY

        default:
            /* No implemementation needed. */
            break;
    }
}


/*@brief Validate an incoming Control Point write.
 *
 * @param[in] op_code   Received op code.
 * @param[in] p_feature Supported features.
 *
 * @returns True if the op code is supported, or false.
 */
static bool ctrlpt_validate(nrf_ble_bms_ctrlpt_t * p_ctrlpt, nrf_ble_bms_features_t * p_feature)
{
    switch (p_ctrlpt->op_code)
    {
        case NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_LE_ONLY:
            if (p_feature->delete_requesting || p_feature->delete_requesting_auth)
            {
                return true;
            }
            break;

        case NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_LE_ONLY:
            if (p_feature->delete_all || p_feature->delete_all_auth)
            {
                return true;
            }
            break;

        case NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_LE_ONLY:
            if (p_feature->delete_all_but_requesting || p_feature->delete_all_but_requesting_auth)
            {
                return true;
            }
            break;

        default:
            /* No implementation needed. */
            break;
    }

    return false;
}


/**@brief Function for processing a write to the Control Point.
 *
 * @param[in]   p_bms       Bond Management Service structure.
 * @param[in]   p_rcvd_val  Received write value.
 * @param[in]   len         Value length.
 * @param[out]  p_ctrlpt    Decoded control point structure.
 */
static uint16_t ctrlpt_process(nrf_ble_bms_t        * p_bms,
                               uint8_t const        * p_rcvd_val,
                               uint16_t               len,
                               nrf_ble_bms_ctrlpt_t * p_ctrlpt)
{
    ret_code_t err_code;

    /* Decode operation */
    err_code = ctrlpt_decode(p_rcvd_val, len, p_ctrlpt);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Control point write: Operation failed.");
        return NRF_BLE_BMS_OPERATION_FAILED;
    }

    /* Verify that the operation is allowed. */
    if (!ctrlpt_validate(p_ctrlpt, &p_bms->feature))
    {
        NRF_LOG_ERROR("Control point write: Invalid op code.");
        return NRF_BLE_BMS_OPCODE_NOT_SUPPORTED;
    }

    /* Request authorization */
    ctrlpt_auth(p_bms, p_ctrlpt);
    if (p_bms->auth_status != NRF_BLE_BMS_AUTH_STATUS_ALLOWED)
    {
        NRF_LOG_ERROR("Control point long write: Invalid auth.");
        return BLE_GATT_STATUS_ATTERR_INSUF_AUTHORIZATION;
    }

    return BLE_GATT_STATUS_SUCCESS;
}


/**@brief Function for encoding the Bond Management Feature characteristic.
 *
 * @param[in]   p_bms              Bond Management Service structure.
 * @param[out]  p_encoded_feature  Encoded features.
 *
 * @return      Size of the encoded feature.
 */
static uint8_t feature_encode(nrf_ble_bms_features_t const * p_feature, uint8_t * p_encoded_feature)
{
    uint32_t data = 0;

    if (p_feature->delete_all_auth)
    {
        data |= NRF_BLE_BMS_ALL_BONDS_LE_AUTH_CODE;
    }
    if (p_feature->delete_all_but_requesting_auth)
    {
        data |= NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE_AUTH_CODE;
    }
    if (p_feature->delete_all_but_requesting)
    {
        data |= NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE;
    }
    if (p_feature->delete_all)
    {
        data |= NRF_BLE_BMS_ALL_BONDS_LE;
    }
    if (p_feature->delete_requesting_auth)
    {
        data |= NRF_BLE_BMS_REQUESTING_DEVICE_LE_AUTH_CODE;
    }
    if (p_feature->delete_requesting)
    {
        data |= NRF_BLE_BMS_REQUESTING_DEVICE_LE;
    }

    return (uint24_encode(data, p_encoded_feature));
}


/**@brief Function for adding the Bond Management Feature characteristic.
 *
 * @param[in]   p_bms       Bond Management Service structure.
 * @param[in]   p_bms_init  Information needed to initialize the service.
 *
 * @return  NRF_SUCCESS on success, otherwise an error code returned by @ref characteristic_add.
 */
static ret_code_t feature_char_add(nrf_ble_bms_t * p_bms, nrf_ble_bms_init_t const * p_bms_init)
{
    uint8_t                  encoded_feature[NRF_BLE_BMS_FEATURE_LEN];
    uint8_t                  init_value_len;
    ble_add_char_params_t    add_char_params;
    nrf_ble_bms_features_t * p_feature = &p_bms->feature;

    if ((p_feature->delete_all_auth) ||
        (p_feature->delete_all_but_requesting_auth) ||
        (p_feature->delete_requesting_auth))
    {
        VERIFY_PARAM_NOT_NULL(p_bms_init->evt_handler);
    }

    if ((p_feature->delete_requesting_auth) ||
        (p_feature->delete_requesting))
    {
        VERIFY_PARAM_NOT_NULL(p_bms_init->bond_callbacks.delete_requesting);
    }

    if ((p_feature->delete_all) ||
        (p_feature->delete_all_auth))
    {
        VERIFY_PARAM_NOT_NULL(p_bms_init->bond_callbacks.delete_all);
    }

    if ((p_feature->delete_all_but_requesting) ||
        (p_feature->delete_all_but_requesting_auth))
    {
        VERIFY_PARAM_NOT_NULL(p_bms_init->bond_callbacks.delete_all_except_requesting);
    }

    init_value_len = feature_encode(&p_bms->feature, encoded_feature);

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid            = BLE_UUID_BMS_FEATURE;
    add_char_params.char_props.read = true;
    add_char_params.max_len         = init_value_len;
    add_char_params.p_init_value    = encoded_feature;
    add_char_params.init_len        = init_value_len;
    add_char_params.read_access     = p_bms_init->bms_feature_sec_req;
    add_char_params.write_access    = SEC_NO_ACCESS;

    return characteristic_add(p_bms->service_handle, &add_char_params, &p_bms->feature_handles);
}


/**@brief Handle a write event to the Bond Management Service Control Point.
 *
 * @param[in] p_bms        Bond Management Service structure.
 * @param[in] p_evt_write  WRITE event to be handled.
 */
static void on_ctrlpt_write(nrf_ble_bms_t                * p_bms,
                            ble_gatts_evt_write_t const  * p_evt_write,
                            ble_gatts_authorize_params_t * p_auth_params)
{
    ret_code_t           err_code;
    nrf_ble_bms_ctrlpt_t ctrlpt;

    err_code = ctrlpt_process(p_bms, p_evt_write->data, p_evt_write->len, &ctrlpt);
    if (err_code != NRF_SUCCESS)
    {
        p_auth_params->gatt_status = err_code;
        p_auth_params->update      = 0;

        return;
    }

    p_auth_params->gatt_status = BLE_GATT_STATUS_SUCCESS;
    p_auth_params->update      = 1;

    NRF_LOG_INFO("Control point write: Success");

    /* Execute the requested operation. */
    ctrlpt_execute(p_bms, ctrlpt.op_code);
}


/**@brief Authorize WRITE request event handler.
 *
 * @details Handles WRITE events from the BLE stack.
 *
 * @param[in]   p_bms        Bond Management Service structure.
 * @param[in]   p_gatts_evt  GATTS Event received from the BLE stack.
 *
 */
static void on_rw_auth_req(nrf_ble_bms_t * p_bms, ble_gatts_evt_t const * p_gatts_evt)
{
    ret_code_t err_code;
    ble_gatts_rw_authorize_reply_params_t auth_reply;

    ble_gatts_evt_rw_authorize_request_t const * p_auth_req =
        &p_gatts_evt->params.authorize_request;

    memset(&auth_reply, 0, sizeof(auth_reply));

    if ((p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE) &&
        (p_auth_req->request.write.op == BLE_GATTS_OP_WRITE_REQ) &&
        (p_auth_req->request.write.handle == p_bms->ctrlpt_handles.value_handle))
    {
        auth_reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
        on_ctrlpt_write(p_bms, &p_auth_req->request.write, &auth_reply.params.write);

        /* Send authorization reply */
        err_code = sd_ble_gatts_rw_authorize_reply(p_bms->conn_handle, &auth_reply);
        error_check(err_code, p_bms->error_handler);
    }

}


/**@brief Handle authorization request events from the Queued Write module.
 *
 * @param[in]   p_bms   Bond Management Service structure.
 * @param[in]   p_qwr   Queued Write Structure.
 * @param[in]   p_evt   Event received from the Queued Writes module.
 *
 * @retval BLE_GATT_STATUS_SUCCESS                    If the received event is accepted.
 * @retval BLE_BMS_OPCODE_OPERATION_FAILED            If the received event is not relevant for any of this module's attributes.
 * @retval BLE_BMS_OPCODE_NOT_SUPPORTED               If the received opcode is not supported.
 * @retval BLE_GATT_STATUS_ATTERR_INSUF_AUTHORIZATION If the application handler returns that the authorization code is not valid.
 */
uint16_t on_qwr_auth_req(nrf_ble_bms_t * p_bms, nrf_ble_qwr_t * p_qwr, nrf_ble_qwr_evt_t * p_evt)
{
    ret_code_t           err_code;
    uint16_t             len = NRF_BLE_BMS_CTRLPT_MAX_LEN;
    uint8_t              mem_buffer[NRF_BLE_BMS_CTRLPT_MAX_LEN];
    nrf_ble_bms_ctrlpt_t ctrlpt;

    err_code = nrf_ble_qwr_value_get(p_qwr, p_evt->attr_handle, mem_buffer, &len);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Control point write: Operation failed.");
        return NRF_BLE_BMS_OPERATION_FAILED;
    }

    return ctrlpt_process(p_bms, mem_buffer, len, &ctrlpt);
}


/**@brief Handle execute write events to from the Queued Write module.
 *
 * @param[in]   p_bms   Bond Management Service structure.
 * @param[in]   p_qwr   Queued Write Structure.
 * @param[in]   p_evt   Event received from the Queued Writes module.
 *
 * @retval BLE_GATT_STATUS_SUCCESS                    If the received event is accepted.
 * @retval BLE_BMS_OPCODE_OPERATION_FAILED            If the received event is not relevant for any of this module's attributes.
 * @retval BLE_BMS_OPCODE_NOT_SUPPORTED               If the received opcode is not supported.
 */
uint16_t on_qwr_exec_write(nrf_ble_bms_t * p_bms, nrf_ble_qwr_t * p_qwr, nrf_ble_qwr_evt_t * p_evt)
{
    ret_code_t           err_code;
    uint16_t             len = NRF_BLE_BMS_CTRLPT_MAX_LEN;
    uint8_t              mem_buffer[NRF_BLE_BMS_CTRLPT_MAX_LEN];
    nrf_ble_bms_ctrlpt_t ctrlpt;
    ble_gatts_value_t    ctrlpt_value;

    ctrlpt_value.len     = NRF_BLE_BMS_CTRLPT_MAX_LEN;
    ctrlpt_value.offset  = 0;
    ctrlpt_value.p_value = mem_buffer;

    const uint16_t ctrlpt_handle = p_bms->ctrlpt_handles.value_handle;
    err_code = sd_ble_gatts_value_get(p_bms->conn_handle, ctrlpt_handle, &ctrlpt_value);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Control point write: Operation failed.");
        return NRF_BLE_BMS_OPERATION_FAILED;
    }

    /* Decode operation */
    err_code = ctrlpt_decode(ctrlpt_value.p_value, len, &ctrlpt);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Control point write: Operation failed.");
        return NRF_BLE_BMS_OPERATION_FAILED;
    }

    /* Execute the requested operation. */
    ctrlpt_execute(p_bms, ctrlpt.op_code);

    /* Reset authorization status */
    p_bms->auth_status = NRF_BLE_BMS_AUTH_STATUS_DENIED;

    return BLE_GATT_STATUS_SUCCESS;
}


uint16_t nrf_ble_bms_on_qwr_evt(nrf_ble_bms_t     * p_bms,
                                nrf_ble_qwr_t     * p_qwr,
                                nrf_ble_qwr_evt_t * p_evt)
{
    VERIFY_TRUE(p_bms != NULL, (NRF_BLE_QWR_REJ_REQUEST_ERR_CODE));
    VERIFY_TRUE(p_qwr != NULL, (NRF_BLE_QWR_REJ_REQUEST_ERR_CODE));
    VERIFY_TRUE(p_evt != NULL, (NRF_BLE_QWR_REJ_REQUEST_ERR_CODE));
    VERIFY_TRUE(p_evt->attr_handle == p_bms->ctrlpt_handles.value_handle,
            (NRF_BLE_QWR_REJ_REQUEST_ERR_CODE));

    if (p_evt->evt_type == NRF_BLE_QWR_EVT_AUTH_REQUEST)
    {
        return on_qwr_auth_req(p_bms, p_qwr, p_evt);
    }
    else if ((p_evt->evt_type == NRF_BLE_QWR_EVT_EXECUTE_WRITE) &&
             (p_bms->auth_status == NRF_BLE_BMS_AUTH_STATUS_ALLOWED))
    {
        return on_qwr_exec_write(p_bms, p_qwr, p_evt);
    }

    return BLE_GATT_STATUS_SUCCESS;
}


void nrf_ble_bms_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_context);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    nrf_ble_bms_t * p_bms = (nrf_ble_bms_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_auth_req(p_bms, &p_ble_evt->evt.gatts_evt);
            break;

        default:
            break;
    }
}


ret_code_t nrf_ble_bms_set_conn_handle(nrf_ble_bms_t * p_bms, uint16_t conn_handle)
{
    VERIFY_PARAM_NOT_NULL(p_bms);

    p_bms->conn_handle = conn_handle;
    return NRF_SUCCESS;
}


ret_code_t nrf_ble_bms_init(nrf_ble_bms_t * p_bms, nrf_ble_bms_init_t * p_bms_init)
{
    ret_code_t err_code;
    ble_uuid_t ble_uuid;

    VERIFY_PARAM_NOT_NULL(p_bms_init);
    VERIFY_PARAM_NOT_NULL(p_bms);

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_BMS_SERVICE);

    p_bms->evt_handler    = p_bms_init->evt_handler;
    p_bms->error_handler  = p_bms_init->error_handler;
    p_bms->feature        = p_bms_init->feature;
    p_bms->bond_callbacks = p_bms_init->bond_callbacks;
    p_bms->conn_handle    = BLE_CONN_HANDLE_INVALID;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_bms->service_handle);
    VERIFY_SUCCESS(err_code);

    err_code = feature_char_add(p_bms, p_bms_init);
    VERIFY_SUCCESS(err_code);

    err_code = ctrlpt_char_add(p_bms, p_bms_init);
    VERIFY_SUCCESS(err_code);

    if (p_bms_init->p_qwr != NULL)
    {
        return nrf_ble_qwr_attr_register(p_bms_init->p_qwr, p_bms->ctrlpt_handles.value_handle);
    }

    NRF_LOG_INFO("Init complete.");

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_bms_auth_response(nrf_ble_bms_t * p_bms, bool authorize)
{
    VERIFY_PARAM_NOT_NULL(p_bms);
    VERIFY_TRUE(p_bms->auth_status == NRF_BLE_BMS_AUTH_STATUS_PENDING, NRF_ERROR_INVALID_STATE);

    if (authorize)
    {
        p_bms->auth_status = NRF_BLE_BMS_AUTH_STATUS_ALLOWED;
    }
    else
    {
        p_bms->auth_status = NRF_BLE_BMS_AUTH_STATUS_DENIED;
    }

    return NRF_SUCCESS;
}


