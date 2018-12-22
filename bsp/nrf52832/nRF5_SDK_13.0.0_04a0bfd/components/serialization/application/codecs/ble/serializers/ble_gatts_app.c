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
#include "ble_gatts_app.h"
#include <stdlib.h>
#include <string.h>
#include "ble_serialization.h"
#include "ble_gatts_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "cond_field_serialization.h"
#include "app_util.h"


uint32_t ble_gatts_attr_get_req_enc(uint16_t              handle,
                                    ble_uuid_t          * p_uuid,
                                    ble_gatts_attr_md_t * p_md,
                                    uint8_t * const       p_buf,
                                    uint32_t *            p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_ATTR_GET);

    SER_PUSH_uint16(&handle);
    SER_PUSH_COND(p_uuid, NULL);
    SER_PUSH_COND(p_md, NULL);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_attr_get_rsp_dec(uint8_t const * const  p_buf,
                                    uint32_t               packet_len,
                                    ble_uuid_t          ** pp_uuid,
                                    ble_gatts_attr_md_t ** pp_md,
                                    uint32_t * const       p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_ATTR_GET);
    SER_PULL_COND(pp_uuid, ble_uuid_t_dec);
    SER_PULL_COND(pp_md, ble_gatts_attr_md_t_dec);
    SER_RSP_DEC_END;
}


uint32_t ble_gatts_characteristic_add_req_enc(
    uint16_t                               service_handle,
    ble_gatts_char_md_t const * const      p_char_md,
    ble_gatts_attr_t const * const         p_attr_char_value,
    ble_gatts_char_handles_t const * const p_handles,
    uint8_t * const                        p_buf,
    uint32_t * const                       p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_CHARACTERISTIC_ADD);

    SER_PUSH_uint16(&service_handle);
    SER_PUSH_COND(p_char_md, ble_gatts_char_md_t_enc);
    SER_PUSH_COND(p_attr_char_value, ble_gatts_attr_t_enc);
    SER_PUSH_COND(p_handles, NULL);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_characteristic_add_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              uint16_t * * const    pp_handles,
                                              uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_CHARACTERISTIC_ADD);

    SER_PULL_COND(pp_handles, ble_gatts_char_handles_t_dec);

    SER_RSP_DEC_END;
}



uint32_t ble_gatts_descriptor_add_req_enc(uint16_t                       char_handle,
                                          ble_gatts_attr_t const * const p_attr,
                                          uint16_t * const               p_handle,
                                          uint8_t * const                p_buf,
                                          uint32_t * const               p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_DESCRIPTOR_ADD);

    SER_PUSH_uint16(&char_handle);
    SER_PUSH_COND(p_attr, ble_gatts_attr_t_enc);
    SER_PUSH_COND(p_handle, NULL);

    SER_REQ_ENC_END;
}

uint32_t ble_gatts_descriptor_add_rsp_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          uint16_t * const      p_handle,
                                          uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_DESCRIPTOR_ADD);

    SER_PULL_COND(&p_handle, uint16_t_dec);

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_hvx_req_enc(uint16_t                             conn_handle,
                               ble_gatts_hvx_params_t const * const p_hvx_params,
                               uint8_t * const                      p_buf,
                               uint32_t * const                     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_HVX);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_hvx_params, ble_gatts_hvx_params_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_hvx_rsp_dec(uint8_t const * const p_buf,
                               uint32_t              packet_len,
                               uint32_t * const      p_result_code,
                               uint16_t * * const    pp_bytes_written)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_HVX);

    SER_PULL_COND(pp_bytes_written, uint16_t_dec);

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_include_add_req_enc(uint16_t         service_handle,
                                       uint16_t         inc_srvc_handle,
                                       uint16_t * const p_include_handle,
                                       uint8_t * const  p_buf,
                                       uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_INCLUDE_ADD);

    SER_PUSH_uint16(&service_handle);
    SER_PUSH_uint16(&inc_srvc_handle);
    SER_PUSH_COND(p_include_handle, NULL);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_include_add_rsp_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint16_t * const      p_include_handle,
                                       uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_INCLUDE_ADD);

    SER_PULL_COND(&p_include_handle, uint16_t_dec);

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_initial_user_handle_get_req_enc(uint16_t      * p_handle,
                                                   uint8_t * const p_buf,
                                                   uint32_t *      p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_INITIAL_USER_HANDLE_GET);

    SER_PUSH_COND(p_handle, NULL);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_initial_user_handle_get_rsp_dec(uint8_t const * const  p_buf,
                                                   uint32_t               packet_len,
                                                   uint16_t **            pp_handle,
                                                   uint32_t * const       p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_INITIAL_USER_HANDLE_GET);

    SER_PULL_COND(pp_handle, uint16_t_dec);

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_rw_authorize_reply_req_enc(uint16_t         conn_handle,
           ble_gatts_rw_authorize_reply_params_t const * const p_reply_params,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_RW_AUTHORIZE_REPLY);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_reply_params, ble_gatts_rw_authorize_reply_params_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_rw_authorize_reply_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GATTS_RW_AUTHORIZE_REPLY);
}


uint32_t ble_gatts_service_add_req_enc(uint8_t                  type,
                                       ble_uuid_t const * const p_uuid,
                                       uint16_t const * const   p_conn_handle,
                                       uint8_t * const          p_buf,
                                       uint32_t * const         p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_SERVICE_ADD);

    SER_PUSH_uint8(&type);
    SER_PUSH_COND(p_uuid, ble_uuid_t_enc);
    SER_PUSH_COND(p_conn_handle, NULL);

    SER_REQ_ENC_END;
}

uint32_t ble_gatts_service_add_rsp_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint16_t * const      p_conn_handle,
                                       uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_SERVICE_ADD);

    SER_PULL_COND(&p_conn_handle, uint16_t_dec);

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_service_changed_req_enc(uint16_t         conn_handle,
                                           uint16_t         start_handle,
                                           uint16_t         end_handle,
                                           uint8_t * const  p_buf,
                                           uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_SERVICE_CHANGED);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&start_handle);
    SER_PUSH_uint16(&end_handle);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_service_changed_rsp_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GATTS_SERVICE_CHANGED);
}


uint32_t ble_gatts_sys_attr_get_req_enc(uint16_t               conn_handle,
                                        uint8_t const * const  p_sys_attr_data,
                                        uint16_t const * const p_sys_attr_data_len,
                                        uint32_t               flags,
                                        uint8_t * const        p_buf,
                                        uint32_t *             p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_SYS_ATTR_GET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_sys_attr_data_len, uint16_t_enc);
    SER_PUSH_COND(p_sys_attr_data, NULL);
    SER_PUSH_uint32(&flags);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_sys_attr_get_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint8_t * * const     pp_sys_attr_data,
                                        uint16_t * * const    pp_sys_attr_data_len,
                                        uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_SYS_ATTR_GET);

    SER_PULL_COND(pp_sys_attr_data_len, uint16_t_dec);
    if (*pp_sys_attr_data_len)
    {
        SER_PULL_buf(pp_sys_attr_data, **pp_sys_attr_data_len, **pp_sys_attr_data_len);
    }

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_sys_attr_set_req_enc(uint16_t              conn_handle,
                                        uint8_t const * const p_sys_attr_data,
                                        uint16_t              sys_attr_data_len,
                                        uint32_t              flags,
                                        uint8_t * const       p_buf,
                                        uint32_t * const      p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_SYS_ATTR_SET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_len16data(p_sys_attr_data, sys_attr_data_len);
    SER_PUSH_uint32(&flags);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_sys_attr_set_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code)
{
    return ser_ble_cmd_rsp_dec(p_buf, packet_len, SD_BLE_GATTS_SYS_ATTR_SET, p_result_code);
}


uint32_t ble_gatts_value_get_req_enc(uint16_t                        conn_handle,
                                     uint16_t                        handle,
                                     ble_gatts_value_t const * const p_value,
                                     uint8_t * const                 p_buf,
                                     uint32_t * const                p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_VALUE_GET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&handle);

    //Special case: skip the data.
    SER_PUSH_COND(p_value, NULL);
    if (p_value)
    {
        SER_PUSH_uint16(&p_value->offset);
        SER_PUSH_uint16(&p_value->len);
        SER_PUSH_COND(p_value->p_value, NULL);
    }

    SER_REQ_ENC_END;
}

uint32_t ble_gatts_value_get_rsp_dec(uint8_t const * const     p_buf,
                                     uint32_t                  packet_len,
                                     ble_gatts_value_t * const p_value,
                                     uint32_t * const          p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_VALUE_GET);

    SER_PULL_COND(&p_value, ble_gatts_value_t_dec);

    SER_RSP_DEC_END;
}


uint32_t ble_gatts_value_set_req_enc(uint16_t             conn_handle,
                                     uint16_t             handle,
                                     ble_gatts_value_t *  p_value,
                                     uint8_t * const      p_buf,
                                     uint32_t * const     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_VALUE_SET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&handle);
    SER_PUSH_COND(p_value, ble_gatts_value_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_value_set_rsp_dec(uint8_t const * const       p_buf,
                                     uint32_t                    packet_len,
                                     ble_gatts_value_t * const   p_value,
                                     uint32_t * const            p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GATTS_VALUE_SET);

    SER_PULL_COND(&p_value, ble_gatts_value_t_dec);

    SER_RSP_DEC_END;
}

uint32_t ble_gatts_exchange_mtu_reply_req_enc(uint16_t          conn_handle,
                                              uint16_t          server_rx_mtu,
                                              uint8_t * const   p_buf,
                                              uint32_t * const  p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GATTS_EXCHANGE_MTU_REPLY);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&server_rx_mtu);

    SER_REQ_ENC_END;
}


uint32_t ble_gatts_exchange_mtu_reply_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GATTS_EXCHANGE_MTU_REPLY);
}
