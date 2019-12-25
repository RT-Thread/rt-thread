/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#include "ble_ots_object.h"

#include <string.h>
#include "ble_srv_common.h"

#include "ble_ots.h"

#define BLE_OTS_WRITE_REQUEST_REJECTED      0x80

#define BLE_OTS_OBJECT_NOT_SELECTED         0x81
#define BLE_OTS_CONCURRENCY_LIMIT_EXCEEDED  0x82
#define BLE_OTS_OBJ_NAME_ALREADY_EXISTS     0x83
#define BLE_SIZE_DATE_TIME                  7


uint32_t ble_ots_object_refresh_current(ble_ots_object_chars_t * p_ots_object_chars)
{
    uint32_t           err_code;
    ble_ots_object_t * p_obj;

    p_obj = p_ots_object_chars->p_ots->p_current_object;

    if (p_obj == NULL)
    {
        // Clear all characteristics
        return NRF_SUCCESS;
    }


    // obtain the largest necessary buffer
    typedef union {
        uint8_t type_buf[sizeof(ble_ots_obj_type_t)+sizeof(uint8_t)];
        uint8_t size_buf[2*sizeof(uint32_t)];
        uint8_t prop_buf[sizeof(uint32_t)];
    } buffer_t;

    buffer_t buffer;

    ble_gatts_value_t gatts_value;
    
    memset(&gatts_value, 0, sizeof(gatts_value));

    // name
    gatts_value.len = strlen((const char *)p_obj->name) + 1;
    gatts_value.p_value = p_obj->name;
    err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                      p_ots_object_chars->obj_name_handles.value_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // type
    if (p_obj->type.len == sizeof(uint16_t))
    {
        gatts_value.len = uint16_encode(p_obj->type.param.type16, buffer.type_buf);
        gatts_value.p_value = buffer.type_buf;
        err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                          p_ots_object_chars->obj_type_handles.value_handle,
                                          &gatts_value);
    }
    else
    {
        gatts_value.len = uint16_encode(p_obj->type.param.type16, buffer.type_buf);
        gatts_value.p_value = p_obj->type.param.type128;
        err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                          p_ots_object_chars->obj_type_handles.value_handle,
                                          &gatts_value);
    }
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    gatts_value.len = uint32_encode(p_obj->current_size, &buffer.size_buf[0]);
    gatts_value.len += uint32_encode(p_obj->alloc_len, &buffer.size_buf[gatts_value.len]);
    gatts_value.p_value = &buffer.size_buf[0];
    err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                      p_ots_object_chars->obj_size_handles.value_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    gatts_value.len = uint32_encode(p_obj->properties.raw, buffer.prop_buf);
    gatts_value.p_value = buffer.prop_buf;
    err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                      p_ots_object_chars->obj_properties_handles.value_handle,
                                      &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}

/**@brief Function for adding the object name characteristic.
 *
 * @param[in] p_ots_object_chars    Pointer the the object characteristics.
 * @param[in] service_handle        The service handle where the characteristic should be added.
 * @param[in] read_access           The read security level for the characteristic.
 * @param[in] write_access          The write security level for the characteristic.
 *
 * @return NRF_SUCCESS if the characteristic was successfully added, else a return code from
 *                     characteristic_add().
 */
static uint32_t obj_name_char_add(ble_ots_object_chars_t * const p_ots_object_chars,
                                  uint16_t               service_handle,
                                  security_req_t         read_access,
                                  security_req_t         write_access)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid             = BLE_UUID_OTS_OBJECT_NAME;
    add_char_params.uuid_type        = BLE_UUID_TYPE_BLE;
    add_char_params.max_len          = BLE_OTS_NAME_MAX_SIZE;
    add_char_params.is_var_len       = 1;
    add_char_params.char_props.read  = 1;
    add_char_params.read_access      = read_access;
    add_char_params.char_props.write = 0;

    return characteristic_add(service_handle,
                              &add_char_params,
                              &p_ots_object_chars->obj_name_handles);
}

/**@brief Function for adding the object type characteristic.
 *
 * @param[in] p_ots_object_chars    Pointer the the object characteristics.
 * @param[in] service_handle        The service handle where the characteristic should be added.
 * @param[in] read_access           The read security level for the characteristic.
 *
 * @return NRF_SUCCESS if the characteristic was successfully added, else a return code from
 *                     characteristic_add().
 */
static uint32_t obj_type_char_add(ble_ots_object_chars_t * const p_ots_object_chars,
                                  uint16_t               service_handle,
                                  security_req_t         read_access)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid            = BLE_UUID_OTS_OBJECT_TYPE;
    add_char_params.uuid_type       = BLE_UUID_TYPE_BLE;
    add_char_params.max_len         = sizeof(ble_ots_obj_type_t);
    add_char_params.is_var_len      = 1;
    add_char_params.char_props.read = 1;
    add_char_params.read_access     = read_access;

    return characteristic_add(service_handle,
                              &add_char_params,
                              &p_ots_object_chars->obj_type_handles);
}

/**@brief Function for adding the object size characteristic.
 *
 * @param[in] p_ots_object_chars    Pointer the the object characteristics.
 * @param[in] service_handle        The service handle where the characteristic should be added.
 * @param[in] read_access           The read security level for the characteristic.
 *
 * @return NRF_SUCCESS if the characteristic was successfully added, else a return code from
 *                     characteristic_add().
 */
static uint32_t obj_size_char_add(ble_ots_object_chars_t * const p_ots_object_chars,
                                  uint16_t                 service_handle,
                                  security_req_t           read_access)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid            = BLE_UUID_OTS_OBJECT_SIZE;
    add_char_params.uuid_type       = BLE_UUID_TYPE_BLE;
    add_char_params.max_len         = NRF_BLE_OTS_SIZE_CHAR_LEN;
    add_char_params.is_var_len      = 0;
    add_char_params.char_props.read = 1;
    add_char_params.read_access     = read_access;

    return characteristic_add(service_handle,
                              &add_char_params,
                              &p_ots_object_chars->obj_size_handles);
}

/**@brief Function for adding the object properties characteristic.
 *
 * @param[in] p_ots_object_chars    Pointer the the object characteristics.
 * @param[in] service_handle        The service handle where the characteristic should be added.
 * @param[in] read_access           The read security level for the characteristic.
 * @param[in] write_access          The write security level for the characteristic.
 *
 * @return NRF_SUCCESS if the characteristic was successfully added, else a return code from
 *                     characteristic_add().
 */
static uint32_t obj_prop_char_add(ble_ots_object_chars_t   * const p_ots_object_chars,
                                  uint16_t                   service_handle,
                                  security_req_t             read_access,
                                  security_req_t             write_access)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid             = BLE_UUID_OTS_OBJECT_PROPERTIES;
    add_char_params.uuid_type        = BLE_UUID_TYPE_BLE;
    add_char_params.max_len          = sizeof(uint32_t);
    add_char_params.is_var_len       = 0;
    add_char_params.char_props.read  = 1;
    add_char_params.read_access      = read_access;

    add_char_params.is_defered_write = 1;
    add_char_params.write_access     = write_access;

    return characteristic_add(service_handle,
                              &add_char_params,
                              &p_ots_object_chars->obj_properties_handles);
}


uint32_t ble_ots_object_representation_init(ble_ots_object_chars_t * p_ots_object_chars,
                                            ble_ots_object_chars_init_t * p_ots_object_chars_init)
{
    if (p_ots_object_chars == NULL || p_ots_object_chars_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t err_code;

    p_ots_object_chars->p_ots = p_ots_object_chars_init->p_ots;

    err_code = obj_name_char_add(p_ots_object_chars,
                                 p_ots_object_chars_init->p_ots->service_handle,
                                 p_ots_object_chars_init->name_read_access,
                                 p_ots_object_chars_init->name_write_access);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = obj_type_char_add(p_ots_object_chars,
                                 p_ots_object_chars_init->p_ots->service_handle,
                                 p_ots_object_chars_init->type_read_access);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = obj_size_char_add(p_ots_object_chars,
                                 p_ots_object_chars_init->p_ots->service_handle,
                                 p_ots_object_chars_init->size_read_access);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = obj_prop_char_add(p_ots_object_chars,
                                 p_ots_object_chars_init->p_ots->service_handle,
                                 p_ots_object_chars_init->properties_read_access,
                                 p_ots_object_chars_init->properties_write_access);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    return ble_ots_object_refresh_current(p_ots_object_chars);
}


uint32_t ble_ots_object_set_name(ble_ots_object_chars_t * p_ots_object_chars,
                                 ble_ots_object_t * p_object,
                                 const char * new_name)
{
    if (p_ots_object_chars == NULL || p_object == NULL || new_name == NULL)
    {
        return NRF_ERROR_NULL;
    }



    strncpy((char *)p_object->name, new_name, BLE_OTS_NAME_MAX_SIZE);

    if (p_object == p_ots_object_chars->p_ots->p_current_object)
    {
        // update characteristic
        uint32_t          err_code;
        ble_gatts_value_t gatts_value;
        
        memset(&gatts_value, 0, sizeof(gatts_value));

        gatts_value.len = strlen((const char *)p_object->name) + 1;
        gatts_value.p_value = p_object->name;
        err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                          p_ots_object_chars->obj_name_handles.value_handle,
                                          &gatts_value);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }


    return NRF_SUCCESS;
}

uint32_t ble_ots_object_set_type(ble_ots_object_chars_t * p_ots_object_chars,
                                 ble_ots_object_t * p_object,
                                 ble_ots_obj_type_t * p_new_type)
{
    if (p_ots_object_chars == NULL || p_object == NULL || p_new_type == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (p_new_type->len != sizeof(p_new_type->param.type16) && p_new_type->len != sizeof(p_new_type->param.type128))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    memcpy(&p_object->type, p_new_type, sizeof(ble_ots_obj_type_t));

    if (p_object == p_ots_object_chars->p_ots->p_current_object)
    {
        // update characteristic
        uint32_t          err_code;
        uint8_t           buffer[sizeof(p_new_type->param.type16)];
        ble_gatts_value_t gatts_value;

        memset(&gatts_value, 0, sizeof(gatts_value));

        if (p_object->type.len == sizeof(uint16_t))
        {
            gatts_value.len = uint16_encode(p_object->type.param.type16, buffer);
            gatts_value.p_value = buffer;
            err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                              p_ots_object_chars->obj_type_handles.value_handle,
                                              &gatts_value);
        }
        else
        {
            gatts_value.len = uint16_encode(p_object->type.param.type16, buffer);
            gatts_value.p_value = p_object->type.param.type128;
            err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                              p_ots_object_chars->obj_type_handles.value_handle,
                                              &gatts_value);
        }
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }


    return NRF_SUCCESS;

}

uint32_t ble_ots_object_set_current_size(ble_ots_object_chars_t * p_ots_object_chars,
                                         ble_ots_object_t * p_object,
                                         uint32_t new_current_size)
{
    if (p_ots_object_chars == NULL || p_object == NULL)
    {
        return NRF_ERROR_NULL;
    }

    p_object->current_size = new_current_size;

    if (p_object == p_ots_object_chars->p_ots->p_current_object)
    {
        // update characteristic
        uint32_t          err_code;
        uint8_t           buffer[NRF_BLE_OTS_SIZE_CHAR_LEN];
        ble_gatts_value_t gatts_value;

        memset(&gatts_value, 0, sizeof(gatts_value));

        gatts_value.len = 0;
        gatts_value.len += uint32_encode(p_object->current_size, &buffer[gatts_value.len]);
        gatts_value.len += uint32_encode(p_object->alloc_len, &buffer[gatts_value.len]);
        gatts_value.p_value = &buffer[0];
        err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                          p_ots_object_chars->obj_size_handles.value_handle,
                                          &gatts_value);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }


    return NRF_SUCCESS;

}


/**@brief     Function for handling write on object properties meta data.
 *
 * @param[in] p_ots_object_chars    Pointer the the object characteristics.
 * @param[in] p_ble_evt             Pointer to the event received from BLE stack.
 */
static uint32_t on_obj_properties_write(ble_ots_object_chars_t * p_ots_object_chars,
                                        ble_evt_t const * p_ble_evt)
{
    ble_gatts_rw_authorize_reply_params_t write_authorize_reply;
    ble_gatts_evt_write_t const         * p_write_evt;

    p_write_evt = &p_ble_evt->evt.gatts_evt.params.authorize_request.request.write;

    write_authorize_reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;

    uint32_t raw_prop = uint32_decode(p_write_evt->data);
    if ((raw_prop & 0xFFFFFF80) != 0)
    {
        write_authorize_reply.params.write.gatt_status = BLE_OTS_WRITE_REQUEST_REJECTED;
    }
    else
    {
        p_ots_object_chars->p_ots->p_current_object->properties.raw = raw_prop;
        write_authorize_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;

        ble_ots_evt_t ble_ots_evt;

        ble_ots_evt.type = BLE_OTS_EVT_OBJECT;

        ble_ots_evt.evt.object_evt.type = BLE_OTS_OBJECT_EVT_PROPERTIES_CHANGED;
        ble_ots_evt.evt.object_evt.evt.p_object = p_ots_object_chars->p_ots->p_current_object;
        p_ots_object_chars->p_ots->evt_handler(p_ots_object_chars->p_ots, &ble_ots_evt);

    }
    return sd_ble_gatts_rw_authorize_reply(p_ble_evt->evt.gatts_evt.conn_handle, &write_authorize_reply);
}

uint32_t ble_ots_object_set_properties(ble_ots_object_chars_t * p_ots_object_chars,
                                       ble_ots_object_t * p_object,
                                       ble_ots_obj_properties_t * p_new_properties)
{
    if (p_ots_object_chars == NULL || p_object == NULL)
    {
        return NRF_ERROR_NULL;
    }

    memcpy(&p_object->properties, p_new_properties, sizeof(ble_ots_obj_properties_t));


    if (p_object == p_ots_object_chars->p_ots->p_current_object)
    {
        // update characteristic
        uint32_t          err_code;
        uint8_t           buffer[sizeof(ble_ots_obj_properties_t)];
        ble_gatts_value_t gatts_value;
        
        memset(&gatts_value, 0, sizeof(gatts_value));

        gatts_value.len = uint32_encode(p_object->properties.raw, buffer);
        gatts_value.p_value = buffer;
        err_code = sd_ble_gatts_value_set(p_ots_object_chars->p_ots->conn_handle,
                                          p_ots_object_chars->obj_properties_handles.value_handle,
                                          &gatts_value);

        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}


/**@brief     Function for handling the @ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST event.
 *
 * @param[in] p_ots_object_chars    Pointer the the object characteristics.
 * @param[in] p_ble_evt             Pointer to the event received from BLE stack.
 */
static void on_rw_auth_req(ble_ots_object_chars_t * p_ots_object_chars, ble_evt_t const * p_ble_evt)
{
    uint32_t err_code;
    ble_gatts_evt_rw_authorize_request_t const * p_authorize_request;

    p_authorize_request = &(p_ble_evt->evt.gatts_evt.params.authorize_request);

    if (p_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        if (p_authorize_request->request.write.handle == p_ots_object_chars->obj_name_handles.value_handle)
        {
            //err_code = on_name_prepare_write(p_ots_object_chars, p_ble_evt);

           // if (err_code != NRF_SUCCESS)
           // {
           //     p_ots_object_chars->p_ots->error_handler(err_code);
           // }
        }
        else
        if (p_authorize_request->request.write.handle == p_ots_object_chars->obj_properties_handles.value_handle)
        {
            err_code = on_obj_properties_write(p_ots_object_chars, p_ble_evt);
            if (err_code != NRF_SUCCESS)
            {
                p_ots_object_chars->p_ots->error_handler(err_code);
            }
        }
    }
}


void ble_ots_object_on_ble_evt(ble_ots_object_chars_t * p_ots_chars, ble_evt_t const * p_ble_evt)
{
    if ((p_ots_chars == NULL) || (p_ble_evt == NULL))
    {
        return;
    }
//    uint32_t err_code;
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
//            err_code = ble_ots_object_refresh_current(p_ots_chars);
//            if (err_code != NRF_SUCCESS)
//            {
//                p_ots_chars->p_ots->error_handler(err_code);
//            }
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_auth_req(p_ots_chars, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}
