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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_BLE_QWR)
#include <stdlib.h>
#include "nrf_ble_qwr.h"
#include "ble.h"
#include "ble_srv_common.h"


#define NRF_BLE_QWR_INITIALIZED 0xDE // Non-zero value used to make sure the given structure has been initialized by the module.
#define MODULE_INITIALIZED      (p_qwr->initialized == NRF_BLE_QWR_INITIALIZED)
#include "sdk_macros.h"

ret_code_t nrf_ble_qwr_init(nrf_ble_qwr_t            * p_qwr,
                            nrf_ble_qwr_init_t const * p_qwr_init)
{
    VERIFY_PARAM_NOT_NULL(p_qwr);
    VERIFY_PARAM_NOT_NULL(p_qwr_init);
    if (MODULE_INITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    p_qwr->error_handler = p_qwr_init->error_handler;
    p_qwr->initialized   = NRF_BLE_QWR_INITIALIZED;
    p_qwr->conn_handle   = BLE_CONN_HANDLE_INVALID;
#if (NRF_BLE_QWR_MAX_ATTR > 0)
    memset(p_qwr->attr_handles, 0, sizeof(p_qwr->attr_handles));
    p_qwr->nb_registered_attr        = 0;
    p_qwr->is_user_mem_reply_pending = false;
    p_qwr->mem_buffer                = p_qwr_init->mem_buffer;
    p_qwr->callback                  = p_qwr_init->callback;
    p_qwr->nb_written_handles        = 0;
#endif
    return NRF_SUCCESS;
}


#if (NRF_BLE_QWR_MAX_ATTR > 0)
ret_code_t nrf_ble_qwr_attr_register(nrf_ble_qwr_t * p_qwr, uint16_t attr_handle)
{
    VERIFY_PARAM_NOT_NULL(p_qwr);
    VERIFY_MODULE_INITIALIZED();

    if ((p_qwr->nb_registered_attr == NRF_BLE_QWR_MAX_ATTR)
        || (p_qwr->mem_buffer.p_mem == NULL)
        || (p_qwr->mem_buffer.len == 0))
    {
        return (NRF_ERROR_NO_MEM);
    }

    if (attr_handle == BLE_GATT_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_qwr->attr_handles[p_qwr->nb_registered_attr] = attr_handle;
    p_qwr->nb_registered_attr++;

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_qwr_value_get(nrf_ble_qwr_t * p_qwr,
                                 uint16_t        attr_handle,
                                 uint8_t       * p_mem,
                                 uint16_t      * p_len)
{
    VERIFY_PARAM_NOT_NULL(p_qwr);
    VERIFY_PARAM_NOT_NULL(p_mem);
    VERIFY_PARAM_NOT_NULL(p_len);
    VERIFY_MODULE_INITIALIZED();

    uint16_t i          = 0;
    uint16_t handle     = BLE_GATT_HANDLE_INVALID;
    uint16_t val_len    = 0;
    uint16_t val_offset = 0;
    uint16_t cur_len    = 0;

    do
    {
        handle = uint16_decode(&(p_qwr->mem_buffer.p_mem[i]));

        if (handle == BLE_GATT_HANDLE_INVALID)
        {
            break;
        }

        i         += sizeof(uint16_t);
        val_offset = uint16_decode(&(p_qwr->mem_buffer.p_mem[i]));
        i         += sizeof(uint16_t);
        val_len    = uint16_decode(&(p_qwr->mem_buffer.p_mem[i]));
        i         += sizeof(uint16_t);

        if (handle == attr_handle)
        {
            cur_len = val_offset + val_len;
            if (cur_len <= *p_len)
            {
                memcpy((p_mem + val_offset), &(p_qwr->mem_buffer.p_mem[i]), val_len);
            }
            else
            {
                return NRF_ERROR_NO_MEM;
            }
        }

        i += val_len;
    }
    while (i < p_qwr->mem_buffer.len);

    *p_len = cur_len;
    return NRF_SUCCESS;
}
#endif


ret_code_t nrf_ble_qwr_conn_handle_assign(nrf_ble_qwr_t * p_qwr,
                                          uint16_t        conn_handle)
{
    VERIFY_PARAM_NOT_NULL(p_qwr);
    VERIFY_MODULE_INITIALIZED();
    p_qwr->conn_handle = conn_handle;
    return NRF_SUCCESS;
}


/**@brief checks if a user_mem_reply is pending, if so attempts to send it.
 *
 * @param[in]   p_qwr        QWR structure.
 */
static void user_mem_reply(nrf_ble_qwr_t * p_qwr)
{
    if (p_qwr->is_user_mem_reply_pending)
    {
        ret_code_t err_code;
#if (NRF_BLE_QWR_MAX_ATTR == 0)
        err_code = sd_ble_user_mem_reply(p_qwr->conn_handle, NULL);
#else
        err_code = sd_ble_user_mem_reply(p_qwr->conn_handle, &p_qwr->mem_buffer);
#endif
        if (err_code == NRF_SUCCESS)
        {
            p_qwr->is_user_mem_reply_pending = false;
        }
        else if (err_code == NRF_ERROR_BUSY)
        {
            p_qwr->is_user_mem_reply_pending = true;
        }
        else
        {
            p_qwr->error_handler(err_code);
        }
    }
}


/**@brief Handle a user memory request event.
 *
 * @param[in]   p_qwr        QWR structure.
 * @param[in]   p_common_evt User_mem_request event to be handled.
 */
static void on_user_mem_request(nrf_ble_qwr_t          * p_qwr,
                                ble_common_evt_t const * p_common_evt)
{
    if ((p_common_evt->params.user_mem_request.type == BLE_USER_MEM_TYPE_GATTS_QUEUED_WRITES) &&
        (p_common_evt->conn_handle == p_qwr->conn_handle))
    {
        p_qwr->is_user_mem_reply_pending = true;
        user_mem_reply(p_qwr);
    }
}


/**@brief Handle a user memory release event.
 *
 * @param[in]   p_qwr        QWR structure.
 * @param[in]   p_common_evt User_mem_release event to be handled.
 */
static void on_user_mem_release(nrf_ble_qwr_t          * p_qwr,
                                ble_common_evt_t const * p_common_evt)
{
#if (NRF_BLE_QWR_MAX_ATTR > 0)
    if ((p_common_evt->params.user_mem_release.type == BLE_USER_MEM_TYPE_GATTS_QUEUED_WRITES) &&
        (p_common_evt->conn_handle == p_qwr->conn_handle))
    {
        // Cancel the current operation.
        p_qwr->nb_written_handles = 0;
    }
#endif
}


#if (NRF_BLE_QWR_MAX_ATTR > 0)
/**@brief Handle a prepare write event.
 *
 * @param[in]   p_qwr        QWR structure.
 * @param[in]   p_evt_write  WRITE event to be handled.
 */
static void on_prepare_write(nrf_ble_qwr_t               * p_qwr,
                             ble_gatts_evt_write_t const * p_evt_write)
{
    uint32_t                              err_code;
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    memset(&auth_reply, 0, sizeof(auth_reply));

    auth_reply.params.write.gatt_status = NRF_BLE_QWR_REJ_REQUEST_ERR_CODE;
    auth_reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;

    uint32_t i;

    for (i = 0; i < p_qwr->nb_written_handles; i++)
    {
        if (p_qwr->written_attr_handles[i] == p_evt_write->handle)
        {
            auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
            break;
        }
    }

    if (auth_reply.params.write.gatt_status != BLE_GATT_STATUS_SUCCESS)
    {
        for (i = 0; i < p_qwr->nb_registered_attr; i++)
        {
            if (p_qwr->attr_handles[i] == p_evt_write->handle)
            {
                auth_reply.params.write.gatt_status                      = BLE_GATT_STATUS_SUCCESS;
                p_qwr->written_attr_handles[p_qwr->nb_written_handles++] = p_evt_write->handle;
                break;
            }
        }
    }

    err_code = sd_ble_gatts_rw_authorize_reply(p_qwr->conn_handle, &auth_reply);
    if (err_code != NRF_SUCCESS)
    {
        // Cancel the current operation.
        p_qwr->nb_written_handles = 0;

        // Report error to application.
        p_qwr->error_handler(err_code);
    }

}


/**@brief Handle an execute write event.
 *
 * @param[in]   p_qwr        QWR structure.
 * @param[in]   p_evt_write  EXEC WRITE event to be handled.
 */
static void on_execute_write(nrf_ble_qwr_t               * p_qwr,
                             ble_gatts_evt_write_t const * p_evt_write)
{
    uint32_t                              err_code;
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    memset(&auth_reply, 0, sizeof(auth_reply));

    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
    auth_reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;

    if (p_qwr->nb_written_handles == 0)
    {
        auth_reply.params.write.gatt_status = NRF_BLE_QWR_REJ_REQUEST_ERR_CODE;
        err_code = sd_ble_gatts_rw_authorize_reply(p_qwr->conn_handle, &auth_reply);
        if (err_code != NRF_SUCCESS)
        {
            // Report error to application.
            p_qwr->error_handler(err_code);
        }
        return;
    }

    for (uint16_t i = 0; i < p_qwr->nb_written_handles; i++)
    {
        nrf_ble_qwr_evt_t evt;
        uint16_t          ret_val;

        evt.evt_type    = NRF_BLE_QWR_EVT_AUTH_REQUEST;
        evt.attr_handle = p_qwr->written_attr_handles[i];
        ret_val         = p_qwr->callback(p_qwr, &evt);
        if (ret_val != BLE_GATT_STATUS_SUCCESS)
        {
            auth_reply.params.write.gatt_status = ret_val;
        }
    }

    err_code = sd_ble_gatts_rw_authorize_reply(p_qwr->conn_handle, &auth_reply);
    if (err_code != NRF_SUCCESS)
    {
        // Report error to application.
        p_qwr->error_handler(err_code);
    }

    // If the execute has not been rejected by any of the registered applications, propagate execute write event to all written handles. */
    if (auth_reply.params.write.gatt_status == BLE_GATT_STATUS_SUCCESS)
    {
        for (uint16_t i = 0; i < p_qwr->nb_written_handles; i++)
        {
            nrf_ble_qwr_evt_t evt;
            evt.evt_type    = NRF_BLE_QWR_EVT_EXECUTE_WRITE;
            evt.attr_handle = p_qwr->written_attr_handles[i];
            /*lint -e534 -save "Ignoring return value of function" */
            p_qwr->callback(p_qwr, &evt);
            /*lint -restore*/

            auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
        }
    }
    p_qwr->nb_written_handles = 0;
}


/**@brief Handle a cancel write event.
 *
 * @param[in]   p_qwr        QWR structure.
 * @param[in]   p_evt_write  EXEC WRITE event to be handled.
 */
static void on_cancel_write(nrf_ble_qwr_t               * p_qwr,
                            ble_gatts_evt_write_t const * p_evt_write)
{
    uint32_t                              err_code;
    ble_gatts_rw_authorize_reply_params_t auth_reply;
    memset(&auth_reply, 0, sizeof(auth_reply));

    auth_reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
    auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;

    err_code = sd_ble_gatts_rw_authorize_reply(p_qwr->conn_handle, &auth_reply);
    if (err_code != NRF_SUCCESS)
    {
        // Report error to application.
        p_qwr->error_handler(err_code);
    }
    p_qwr->nb_written_handles = 0;
}
#endif

/**@brief Handle a rw_authorize_request event.
 *
 * @param[in]   p_qwr        QWR structure.
 * @param[in]   p_gatts_evt  RW_authorize_request event to be handled.
 */
static void on_rw_authorize_request(nrf_ble_qwr_t         * p_qwr,
                                    ble_gatts_evt_t const * p_gatts_evt)
{
    if (p_gatts_evt->conn_handle != p_qwr->conn_handle)
    {
        return;
    }

    ble_gatts_evt_rw_authorize_request_t const * p_auth_req = &p_gatts_evt->params.authorize_request;

    if (p_auth_req->type != BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        return;
    }

#if (NRF_BLE_QWR_MAX_ATTR == 0)
    // Handle only queued write related operations.
    if ((p_auth_req->request.write.op != BLE_GATTS_OP_PREP_WRITE_REQ) &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_NOW) &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL))
    {
        return;
    }

    // Prepare the response.
    ble_gatts_rw_authorize_reply_params_t auth_reply = {0};

    auth_reply.type                     = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
    auth_reply.params.write.gatt_status = NRF_BLE_QWR_REJ_REQUEST_ERR_CODE;
    if (p_auth_req->request.write.op == BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL)
    {
        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
    }

    ret_code_t err_code = sd_ble_gatts_rw_authorize_reply(p_gatts_evt->conn_handle, &auth_reply);
    if (err_code != NRF_SUCCESS)
    {
        // Report error to application.
        p_qwr->error_handler(err_code);
    }
#else
    switch (p_auth_req->request.write.op)
    {
        case BLE_GATTS_OP_PREP_WRITE_REQ:
            on_prepare_write(p_qwr, &p_auth_req->request.write);
            break; // BLE_GATTS_OP_PREP_WRITE_REQ

        case BLE_GATTS_OP_EXEC_WRITE_REQ_NOW:
            on_execute_write(p_qwr, &p_auth_req->request.write);
            break; // BLE_GATTS_OP_EXEC_WRITE_REQ_NOW

        case BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL:
            on_cancel_write(p_qwr, &p_auth_req->request.write);
            break; // BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL

        default:
            // No implementation needed.
            break;
    }
#endif
}


void nrf_ble_qwr_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_context);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    nrf_ble_qwr_t * p_qwr = (nrf_ble_qwr_t *)p_context;

    VERIFY_MODULE_INITIALIZED_VOID();

    if (p_ble_evt->evt.common_evt.conn_handle == p_qwr->conn_handle)
    {
        user_mem_reply(p_qwr);
    }

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_EVT_USER_MEM_REQUEST:
            on_user_mem_request(p_qwr, &p_ble_evt->evt.common_evt);
            break; // BLE_EVT_USER_MEM_REQUEST

        case BLE_EVT_USER_MEM_RELEASE:
            on_user_mem_release(p_qwr, &p_ble_evt->evt.common_evt);
            break; // BLE_EVT_USER_MEM_REQUEST

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_authorize_request(p_qwr, &p_ble_evt->evt.gatts_evt);
            break; // BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST

        case BLE_GAP_EVT_DISCONNECTED:
            if (p_ble_evt->evt.gap_evt.conn_handle == p_qwr->conn_handle)
            {
                p_qwr->conn_handle = BLE_CONN_HANDLE_INVALID;
#if (NRF_BLE_QWR_MAX_ATTR > 0)
                p_qwr->nb_written_handles = 0;
#endif
            }
            break; // BLE_GAP_EVT_DISCONNECTED

        default:
            break;
    }

}
#endif // NRF_MODULE_ENABLED(NRF_BLE_QWR)
