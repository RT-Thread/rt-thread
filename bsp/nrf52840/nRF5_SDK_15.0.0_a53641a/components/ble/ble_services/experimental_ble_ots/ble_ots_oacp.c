/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#include "ble_ots_oacp.h"

#include <string.h>
#include "fds.h"
#include "crc32.h"

#include "ble_ots.h"
#include "ble_ots_l2cap.h"
#include "ble_ots_object.h"

#define NRF_LOG_MODULE_NAME ble_ots_oacp
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define OTS_FILE_ID 1234
#define OTS_FDS_KEY 4321


/**@brief Checks if the cccd handle is configured for indication
 *
 * @param[in] cccd_handle The CCCD handle.
 */
bool is_cccd_configured(ble_ots_oacp_t * const p_ots_oacp)
{
    uint32_t          err_code;
    uint8_t           cccd_value_buf[BLE_CCCD_VALUE_LEN];
    bool              is_oacp_indic_enabled = false;
    ble_gatts_value_t gatts_value;

    uint16_t cccd_handle = p_ots_oacp->oacp_handles.cccd_handle;
    uint16_t conn_handle = p_ots_oacp->p_ots->conn_handle;
    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.offset  = 0;
    gatts_value.p_value = cccd_value_buf;

    err_code = sd_ble_gatts_value_get(conn_handle,
                                      cccd_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        // Report error to application
        if (p_ots_oacp->p_ots->error_handler != NULL)
        {
            p_ots_oacp->p_ots->error_handler(err_code);
        }
    }

    is_oacp_indic_enabled = ble_srv_is_indication_enabled(cccd_value_buf);

    return is_oacp_indic_enabled;
}



/** @brief This is the l2cap connection oriented channel event handler.
 *
 * @param[in] p_ots_l2cap   Pointer to the l2cap module
 * @param[in] p_evt         The pointer to the event.
 */
static void ots_l2cap_evt_handler(ble_ots_l2cap_t * p_ots_l2cap, ble_ots_l2cap_evt_t * p_evt)
{
    uint32_t err_code;

    switch (p_evt->type)
    {
        case BLE_OTS_L2CAP_EVT_CH_CONNECTED:
            NRF_LOG_INFO("BLE_OTS_L2CAP_EVT_CH_CONNECTED.");
            break;
        case BLE_OTS_L2CAP_EVT_CH_DISCONNECTED:
            NRF_LOG_INFO("BLE_OTS_L2CAP_EVT_CH_DISCONNECTED.");
            break;
        case BLE_OTS_L2CAP_EVT_SEND_COMPLETE:
            p_ots_l2cap->p_ots_oacp->p_ots->p_current_object->is_locked = false;
            break;
        case BLE_OTS_L2CAP_EVT_RECV_COMPLETE:
            NRF_LOG_INFO("BLE_OTS_L2CAP_EVT_RECV_COMPLETE.");
            memcpy(p_ots_l2cap->p_ots_oacp->p_ots->p_current_object->data, 
                   p_ots_l2cap->rx_params.sdu_buf.p_data, 
                   p_ots_l2cap->rx_params.sdu_buf.len);
            err_code = ble_ots_object_set_current_size(&p_ots_l2cap->p_ots_oacp->p_ots->object_chars,
                                                       p_ots_l2cap->p_ots_oacp->p_ots->p_current_object,
                                                       p_ots_l2cap->p_ots_oacp->p_ots->p_current_object->current_size);
            if (err_code != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("ble_ots_object_set_current_size returned error 0x%x", err_code);
            }
            ble_ots_evt_t evt;
            evt.type = BLE_OTS_EVT_OBJECT_RECEIVED;
            p_ots_l2cap->p_ots_oacp->p_ots->evt_handler(p_ots_l2cap->p_ots_oacp->p_ots, &evt);
            break;
    }
}


/**@brief Adds the OACP characteristic
 *
 * @param[in] p_ots_oacp        Pointer to the OACP structure.
 * @param[in] service_handle    The service handle to attach the characteristic to.
 * @param[in] write_access      The write security level for the OACP value handle.
 * @param[in] cccd_write_access The write security level for the OACP cccd handle.
 *
 * @return NRF_SUCCESS When added successfully, else an error code from characteristic_add().
 */
static uint32_t oacp_char_add(ble_ots_oacp_t * const p_ots_oacp,
                              uint16_t       service_handle,
                              security_req_t write_access,
                              security_req_t cccd_write_access)
{
    ble_add_char_params_t add_char_params;
    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid                = BLE_UUID_OTS_OACP;
    add_char_params.uuid_type           = BLE_UUID_TYPE_BLE;
    add_char_params.max_len             = BLE_OTS_MAX_OACP_SIZE;
    add_char_params.init_len            = 0;
    add_char_params.is_var_len          = 1;
    add_char_params.char_props.indicate = true;
    add_char_params.char_props.write    = true;
    add_char_params.cccd_write_access   = cccd_write_access;
    //add_char_params.is_defered_write    = true;
    add_char_params.write_access        = write_access;

    return characteristic_add(service_handle,
                              &add_char_params,
                              &p_ots_oacp->oacp_handles);
}


/**@brief Handling the OACP write procedure.
 *
 * @details The object is opened, and a l2cap transfer is started.
 *
 * @param[in] p_ots_oacp        Pointer to the OACP structure.
 * @param[in] offset            The offset for where the read should start.
 * @param[in] length            The length of the read.
 */
static inline ble_ots_oacp_res_code_t oacp_write_proc(ble_ots_oacp_t * p_ots_oacp,
                                                     uint32_t offset,
                                                     uint32_t length,
                                                     uint8_t mode)
{
    uint32_t err_code;

    if (p_ots_oacp->p_ots->p_current_object == NULL)
    {
        return BLE_OTS_OACP_RES_INV_OBJ;
    }
    if (p_ots_oacp->p_ots->p_current_object->is_valid == false)
    {
        return BLE_OTS_OACP_RES_INV_OBJ;
    }


    if (p_ots_oacp->p_ots->p_current_object->properties.decoded.is_write_permitted == false)
    {
        return BLE_OTS_OACP_RES_NOT_PERMITTED;
    }

    if (ble_ots_l2cap_is_channel_available(&p_ots_oacp->ots_l2cap) == false)
    {
        return BLE_OTS_OACP_RES_CHAN_UNAVAIL;
    }

    if (length + offset > p_ots_oacp->p_ots->p_current_object->alloc_len)
    {
        return BLE_OTS_OACP_RES_INV_PARAM;
    }

    if (p_ots_oacp->p_ots->p_current_object->is_locked)
    {
        return BLE_OTS_OACP_RES_OBJ_LOCKED;
    }

    err_code = ble_ots_l2cap_start_recv(&p_ots_oacp->ots_l2cap,  length);
    if (err_code != NRF_SUCCESS)
    {
        return BLE_OTS_OACP_RES_OPER_FAILED;
    }

    ble_ots_evt_t ble_ots_evt;

    ble_ots_evt.type = BLE_OTS_EVT_OACP;

    ble_ots_evt.evt.oacp_evt.type = BLE_OTS_OACP_EVT_REQ_WRITE;
    ble_ots_evt.evt.oacp_evt.evt.p_object = p_ots_oacp->p_ots->p_current_object;

    p_ots_oacp->p_ots->p_current_object->current_size = length;

    p_ots_oacp->p_ots->evt_handler(p_ots_oacp->p_ots, &ble_ots_evt);

    return BLE_OTS_OACP_RES_SUCCESS;
}



/**@brief Handling the OACP read procedure.
 *
 * @details The object is opened, and a l2cap transfer is started.
 *
 * @param[in] p_ots_oacp        Pointer to the OACP structure.
 * @param[in] offset            The offset for where the read should start.
 * @param[in] length            The length of the read.
 */
static inline ble_ots_oacp_res_code_t oacp_read_proc(ble_ots_oacp_t * p_ots_oacp,
                                                     uint32_t offset,
                                                     uint32_t length)
{

    if (p_ots_oacp->p_ots->p_current_object == NULL)
    {
        return BLE_OTS_OACP_RES_INV_OBJ;
    }
    if (p_ots_oacp->p_ots->p_current_object->is_valid == false)
    {
        return BLE_OTS_OACP_RES_INV_OBJ;
    }


    if (p_ots_oacp->p_ots->p_current_object->properties.decoded.is_read_permitted == false)
    {
        return BLE_OTS_OACP_RES_NOT_PERMITTED;
    }

    if (ble_ots_l2cap_is_channel_available(&p_ots_oacp->ots_l2cap) == false)
    {
        return BLE_OTS_OACP_RES_CHAN_UNAVAIL;
    }

    if (length + offset > p_ots_oacp->p_ots->p_current_object->current_size)
    {
        return BLE_OTS_OACP_RES_INV_PARAM;
    }

    if (p_ots_oacp->p_ots->p_current_object->is_locked)
    {
        return BLE_OTS_OACP_RES_OBJ_LOCKED;
    }

    ble_ots_evt_t ble_ots_evt;

    ble_ots_evt.type = BLE_OTS_EVT_OACP;

    ble_ots_evt.evt.oacp_evt.type = BLE_OTS_OACP_EVT_REQ_READ;
    ble_ots_evt.evt.oacp_evt.evt.p_object = p_ots_oacp->p_ots->p_current_object;

    p_ots_oacp->p_ots->evt_handler(p_ots_oacp->p_ots, &ble_ots_evt);
    
    ret_code_t err_code = ble_ots_l2cap_start_send(&p_ots_oacp->ots_l2cap, 
                                                   p_ots_oacp->p_ots->p_current_object->data,
                                                   p_ots_oacp->p_ots->p_current_object->current_size);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("ble_ots_l2cap_start_send returned error 0x%x", err_code);
    }
    return BLE_OTS_OACP_RES_SUCCESS;
}


/**@brief Handling the OACP abort procedure.
 *
 * @details The transmission is aborted.
 *
 * @param[in] p_ots_oacp        Pointer to the OACP structure.
 */
static inline ble_ots_oacp_res_code_t oacp_abort_proc(ble_ots_oacp_t * p_ots_oacp)
{
    uint32_t err_code;

    err_code = ble_ots_l2cap_abort_transmission(&p_ots_oacp->ots_l2cap);
    if (err_code != NRF_SUCCESS)
    {
        return BLE_OTS_OACP_RES_OPER_FAILED;
    }

    p_ots_oacp->p_ots->p_current_object->is_locked = false;

    ble_ots_evt_t ble_ots_evt;

    ble_ots_evt.type = BLE_OTS_EVT_OACP;

    ble_ots_evt.evt.oacp_evt.type = BLE_OTS_OACP_EVT_ABORT;
    ble_ots_evt.evt.oacp_evt.evt.p_object = p_ots_oacp->p_ots->p_current_object;
    p_ots_oacp->p_ots->evt_handler(p_ots_oacp->p_ots, &ble_ots_evt);

    return BLE_OTS_OACP_RES_SUCCESS;
}

/**@brief Sending the oacp procedure response back to the client.
 *
 * @details Encodes and sends the response.
 *
 * @param[in] p_ots_oacp        Pointer to the OACP structure.
 * @param[in] req_op_code       The operation code of the procedure.
 * @param[in] result_code       The result of the procedure.
 * @param[in] conn_handle       The connection handle to send the result to.
 */
static uint32_t ble_ots_oacp_response_send(ble_ots_oacp_t *          p_ots_oacp,
                                           ble_ots_oacp_proc_type_t  req_op_code,
                                           ble_ots_oacp_res_code_t   result_code,
                                           uint16_t                  conn_handle)
{
    uint16_t  index = 0;
    uint8_t * p_data;
    ble_gatts_hvx_params_t *p_hvx_params;

    ble_hvx_t * p_hvx = ble_hvx_get_p_to_next_hvx(&p_ots_oacp->p_ots->hvx_buf);
    p_data       = p_hvx->data;
    p_hvx_params = &p_hvx->params;

    p_data[index++] = BLE_OTS_OACP_PROC_RESP;

    // Encode the Request Op code
    p_data[index++] = (uint8_t)req_op_code;

    // Encode the Result code.
    p_data[index++] = (uint8_t)result_code;


    memset(p_hvx_params, 0, sizeof(ble_gatts_hvx_params_t));

    p_hvx_params->handle   = p_ots_oacp->oacp_handles.value_handle;
    p_hvx_params->type     = BLE_GATT_HVX_INDICATION;
    p_hvx_params->offset   = 0;
    p_hvx_params->p_len    = &index;
    p_hvx_params->p_data   = p_data;

    return ble_hvx_buffer_process(&p_ots_oacp->p_ots->hvx_buf);
}

/**@brief Decode an OACP command, and extract its data.
 *
 * @param[in]   p_ble_write_evt The write event from BLE stack.
 * @param[out]  p_proc          The decoded OACP procedure is sent out.
 *
 * @return BLE_OTS_WRITE_SUCCESS If the filter was decoded correctly, else an error code.
 */
static inline ble_ots_oacp_res_code_t decode_oacp_command(ble_gatts_evt_write_t const * p_ble_write_evt,
                                                          ble_ots_oacp_proc_t * p_proc)
{
    uint32_t index = 0;

    p_proc->type = (ble_ots_oacp_proc_type_t)p_ble_write_evt->data[index++];

    switch (p_proc->type)
    {
        case BLE_OTS_OACP_PROC_READ:
            if (p_ble_write_evt->len !=
                    sizeof(p_proc->params.read_params.offset)
                    + sizeof(p_proc->params.read_params.length)
                    + index)
            {
                return BLE_OTS_OACP_RES_INV_PARAM;
            }
/*lint --e{415} --e{416} -save suppress Warning 415: Likely access of out-of-bounds pointer */
            p_proc->params.read_params.offset = uint32_decode(&(p_ble_write_evt->data[index]));
            index += 4;
            p_proc->params.read_params.length = uint32_decode(&(p_ble_write_evt->data[index]));
/*lint -restore*/
            break;
            //return BLE_OTS_OACP_RES_SUCCESS;
        case BLE_OTS_OACP_PROC_WRITE:
            p_proc->params.write_params.offset = uint32_decode(&(p_ble_write_evt->data[index]));
            index += sizeof(uint32_t);
            p_proc->params.write_params.length = uint32_decode(&(p_ble_write_evt->data[index]));
            index += sizeof(uint32_t);
            p_proc->params.write_params.write_mode = p_ble_write_evt->data[index];
            break;
        default:
            // No implementation needed
            break;
    }
    return BLE_OTS_OACP_RES_SUCCESS;
}


/**@brief     Function for handling the BLE_GAP_EVT_DISCONNECTED event.
 *
 * @param[in] p_ots_oacp  OTS OACP Structure.
 * @param[in] p_ble_evt   Pointer to the event received from BLE stack.
 */
static inline void on_disconnect(ble_ots_oacp_t * p_ots_oacp, ble_evt_t const * p_ble_evt)
{
    uint32_t err_code;
    err_code = fds_gc();
    if (err_code != NRF_SUCCESS)
    {
        p_ots_oacp->p_ots->error_handler(err_code);
    }

}


/**@brief Function for handling the write events to the Blood Pressure Measurement characteristic.
 *
 * @param[in]   p_bps         Blood Pressure Service structure.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_cccd_write(ble_ots_oacp_t * p_ots_oacp, ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == 2)
    {
        // CCCD written, update indication state
        if (p_ots_oacp->p_ots->evt_handler != NULL)
        {
            ble_ots_evt_t evt;

            if (ble_srv_is_indication_enabled(p_evt_write->data))
            {
                evt.type = BLE_OTS_EVT_INDICATION_ENABLED;
            }
            else
            {
                evt.type = BLE_OTS_EVT_INDICATION_DISABLED;
            }

            p_ots_oacp->p_ots->evt_handler(p_ots_oacp->p_ots, &evt);
        }
    }
}


static void on_oacp_write(ble_ots_oacp_t * p_ots_oacp, ble_gatts_evt_write_t const * p_ble_evt_write)
{
    ret_code_t              err_code;
    ble_ots_oacp_res_code_t oacp_status;
    ble_ots_oacp_proc_t     oacp_proc;

    memset(&oacp_proc, 0, sizeof(oacp_proc));

    oacp_status = decode_oacp_command(p_ble_evt_write, &oacp_proc);

    if (oacp_status == BLE_OTS_OACP_RES_SUCCESS)
    {
        oacp_status = ble_ots_oacp_do_proc(p_ots_oacp, &oacp_proc);
    }

    err_code =  ble_ots_oacp_response_send(p_ots_oacp,
                                           oacp_proc.type,
                                           oacp_status,
                                           p_ots_oacp->p_ots->conn_handle);

    if (err_code != NRF_SUCCESS)
    {
        p_ots_oacp->p_ots->error_handler(err_code);
    }
}



/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bps       Blood Pressure Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_ots_oacp_t * p_ots_oacp, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle == p_ots_oacp->p_ots->oacp_chars.oacp_handles.cccd_handle)
    {
        on_cccd_write(p_ots_oacp, p_evt_write);
    }
    if (p_evt_write->handle == p_ots_oacp->p_ots->oacp_chars.oacp_handles.value_handle)
    {
        on_oacp_write(p_ots_oacp, p_evt_write);
    }
}


void ble_ots_oacp_on_ble_evt(ble_ots_oacp_t * p_ots_oacp, ble_evt_t const * p_ble_evt)
{
    if ((p_ots_oacp == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_ots_l2cap_on_ble_evt(&p_ots_oacp->ots_l2cap, p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_ots_oacp, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_ots_oacp, p_ble_evt);
            break;
        default:
            // No implementation needed.
            break;
    }
}

uint32_t ble_ots_oacp_init(ble_ots_oacp_t * p_ots_oacp, ble_ots_oacp_init_t * p_ots_oacp_init)
{
    uint32_t err_code;

    if (p_ots_oacp == NULL || p_ots_oacp_init == NULL)
    {
        return NRF_ERROR_NULL;
    }
    p_ots_oacp->p_ots = p_ots_oacp_init->p_ots;
    p_ots_oacp->on_create_obj_properties_raw = p_ots_oacp_init->on_create_obj_properties_raw;

    ble_ots_l2cap_init_t l2cap_init;

    l2cap_init.p_ots_oacp        = p_ots_oacp;
    l2cap_init.evt_handler       = ots_l2cap_evt_handler;
    l2cap_init.p_transfer_buffer = p_ots_oacp_init->p_l2cap_buffer;
    l2cap_init.buffer_len        = p_ots_oacp_init->l2cap_buffer_len;

    err_code = ble_ots_l2cap_init(&p_ots_oacp->ots_l2cap, &l2cap_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }


    return oacp_char_add(p_ots_oacp,
                         p_ots_oacp->p_ots->service_handle,
                         p_ots_oacp_init->write_access,
                         p_ots_oacp_init->cccd_write_access);
}


ble_ots_oacp_res_code_t ble_ots_oacp_do_proc(ble_ots_oacp_t * p_ots_oacp,
                                             ble_ots_oacp_proc_t * p_oacp_proc)
{
    if (p_ots_oacp == NULL || p_oacp_proc == NULL)
    {
        return BLE_OTS_OACP_RES_INV_PARAM;
    }

    ble_ots_oacp_res_code_t oacp_status;

    switch (p_oacp_proc->type)
    {
        case BLE_OTS_OACP_PROC_WRITE:
            oacp_status = oacp_write_proc(p_ots_oacp,
                                 p_oacp_proc->params.write_params.offset,
                                 p_oacp_proc->params.write_params.length,
                                 p_oacp_proc->params.write_params.write_mode);
        break;
        case BLE_OTS_OACP_PROC_READ:
            oacp_status = oacp_read_proc(p_ots_oacp,
                                         p_oacp_proc->params.read_params.offset,
                                         p_oacp_proc->params.read_params.length);
            break;

        case BLE_OTS_OACP_PROC_ABORT:
            oacp_status = oacp_abort_proc(p_ots_oacp);
            break;

        default:
            // Unsupported op code.
            oacp_status = BLE_OTS_OACP_RES_OPCODE_NOT_SUP;

    }
    return oacp_status;
}



