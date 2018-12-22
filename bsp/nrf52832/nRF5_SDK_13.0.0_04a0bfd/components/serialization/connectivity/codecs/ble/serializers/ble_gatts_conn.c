/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#include "ble_gatts_conn.h"
#include <string.h>
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_gatts_struct_serialization.h"
#include "app_util.h"
#include "cond_field_serialization.h"

uint32_t ble_gatts_attr_get_req_dec(uint8_t   const * const p_buf,
                                    uint32_t                packet_len,
                                    uint16_t              * p_handle,
                                    ble_uuid_t          * * pp_uuid,
                                    ble_gatts_attr_md_t * * pp_md)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_ATTR_GET);

    SER_PULL_uint16(p_handle);
    SER_PULL_COND(pp_uuid, NULL);
    SER_PULL_COND(pp_md, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_gatts_attr_get_rsp_enc(uint32_t               return_code,
                                    uint8_t * const        p_buf,
                                    uint32_t * const       p_buf_len,
                                    ble_uuid_t           * p_uuid,
                                    ble_gatts_attr_md_t  * p_md)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_ATTR_GET);

    SER_PUSH_COND(p_uuid, ble_uuid_t_enc);
    SER_PUSH_COND(p_md, ble_gatts_attr_md_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_characteristic_add_req_dec(uint8_t const * const              p_buf,
                                              uint32_t                           packet_len,
                                              uint16_t *                         p_service_handle,
                                              ble_gatts_char_md_t * * const      pp_char_md,
                                              ble_gatts_attr_t * * const         pp_attr_char_value,
                                              ble_gatts_char_handles_t * * const pp_handles)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_CHARACTERISTIC_ADD);

    SER_PULL_uint16(p_service_handle);
    SER_PULL_COND(pp_char_md, ble_gatts_char_md_t_dec);
    SER_PULL_COND(pp_attr_char_value, ble_gatts_attr_t_dec);
    SER_PULL_COND(pp_handles, NULL);

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_characteristic_add_rsp_enc(uint32_t                               return_code,
                                              uint8_t * const                        p_buf,
                                              uint32_t * const                       p_buf_len,
                                              ble_gatts_char_handles_t const * const p_handles)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_CHARACTERISTIC_ADD);

    SER_PUSH_COND(p_handles, ble_gatts_char_handles_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_descriptor_add_req_dec(uint8_t const * const      p_buf,
                                          uint32_t                   packet_len,
                                          uint16_t * const           p_char_handle,
                                          ble_gatts_attr_t * * const pp_attr,
                                          uint16_t * * const         pp_handle)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_DESCRIPTOR_ADD);

    SER_PULL_uint16(p_char_handle);
    SER_PULL_COND(pp_attr, ble_gatts_attr_t_dec);
    SER_PULL_COND(pp_handle, NULL);

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_descriptor_add_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len,
                                          uint16_t *       p_handle)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_DESCRIPTOR_ADD);

    SER_PUSH_COND(p_handle,uint16_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_hvx_req_dec(uint8_t const * const            p_buf,
                               uint32_t                         packet_len,
                               uint16_t * const                 p_conn_handle,
                               ble_gatts_hvx_params_t * * const pp_hvx_params)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_HVX);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_COND(pp_hvx_params, ble_gatts_hvx_params_t_dec);

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_hvx_rsp_enc(uint32_t               return_code,
                               uint8_t * const        p_buf,
                               uint32_t * const       p_buf_len,
                               uint16_t const * const p_bytes_written)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_HVX);

    SER_PUSH_COND(p_bytes_written, uint16_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_include_add_req_dec(uint8_t const * const p_buf,
                                       uint16_t              packet_len,
                                       uint16_t * const      p_service_handle,
                                       uint16_t * const      p_inc_srvc_handle,
                                       uint16_t * * const    pp_include_handle)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_INCLUDE_ADD);

    SER_PULL_uint16(p_service_handle);
    SER_PULL_uint16(p_inc_srvc_handle);
    SER_PULL_COND(pp_include_handle, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_gatts_include_add_rsp_enc(uint32_t               return_code,
                                       uint8_t * const        p_buf,
                                       uint32_t * const       p_buf_len,
                                       uint16_t const * const p_include_handle)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_INCLUDE_ADD);

    SER_PUSH_COND(p_include_handle, uint16_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_initial_user_handle_get_req_dec(uint8_t   const * const p_buf,
                                                   uint32_t                packet_len,
                                                   uint16_t            * * pp_handle)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_INITIAL_USER_HANDLE_GET);

    SER_PULL_COND(pp_handle, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_gatts_initial_user_handle_get_rsp_enc(uint32_t           return_code,
                                                   uint8_t * const    p_buf,
                                                   uint32_t * const   p_buf_len,
                                                   uint16_t         * p_handle)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_INITIAL_USER_HANDLE_GET);

    SER_PUSH_COND(p_handle, uint16_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_rw_authorize_reply_req_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              uint16_t *            p_conn_handle,
                    ble_gatts_rw_authorize_reply_params_t * * const pp_reply_params)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_RW_AUTHORIZE_REPLY);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_COND(pp_reply_params, ble_gatts_rw_authorize_reply_params_t_dec);
    SER_REQ_DEC_END;
}

uint32_t ble_gatts_rw_authorize_reply_rsp_enc(uint32_t         return_code,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_GATTS_RW_AUTHORIZE_REPLY);
}

uint32_t ble_gatts_service_add_req_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint8_t * const       p_type,
                                       ble_uuid_t * * const  pp_uuid,
                                       uint16_t * * const    pp_handle)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_SERVICE_ADD);

    SER_PULL_uint8(p_type);
    SER_PULL_COND(pp_uuid, ble_uuid_t_dec);
    SER_PULL_COND(pp_handle, NULL);

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_service_add_rsp_enc(uint32_t               return_code,
                                       uint8_t * const        p_buf,
                                       uint32_t * const       p_buf_len,
                                       uint16_t const * const p_handle)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_SERVICE_ADD);

    SER_PUSH_COND(p_handle, uint16_t_enc);
    //SER_PUSH_uint16(p_handle);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_service_changed_req_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint16_t *            p_conn_handle,
                                           uint16_t *            p_start_handle,
                                           uint16_t *            p_end_handle)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_SERVICE_CHANGED);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_start_handle);
    SER_PULL_uint16(p_end_handle);

    SER_REQ_DEC_END;
}


uint32_t ble_gatts_service_changed_rsp_enc(uint32_t         return_code,
                                           uint8_t * const  p_buf,
                                           uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_GATTS_SERVICE_CHANGED);
}

uint32_t ble_gatts_sys_attr_get_req_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint16_t * const      p_conn_handle,
                                        uint8_t * * const     pp_sys_attr_data,
                                        uint16_t * * const    pp_sys_attr_data_len,
                                        uint32_t * const      p_flags)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_SYS_ATTR_GET);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_COND(pp_sys_attr_data_len, uint16_t_dec);
    SER_PULL_COND(pp_sys_attr_data, NULL);
    SER_PULL_uint32(p_flags);

    SER_REQ_DEC_END;
}


uint32_t ble_gatts_sys_attr_get_rsp_enc(uint32_t               return_code,
                                        uint8_t * const        p_buf,
                                        uint32_t * const       p_buf_len,
                                        uint8_t const * const  p_sys_attr_data,
                                        uint16_t const * const p_sys_attr_data_len)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_SYS_ATTR_GET);

    SER_PUSH_COND(p_sys_attr_data_len, uint16_t_enc);
    if (p_sys_attr_data_len)
    {
        SER_PUSH_buf(p_sys_attr_data, *p_sys_attr_data_len);
    }

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_sys_attr_set_req_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint16_t * const      p_conn_handle,
                                        uint8_t * * const     pp_sys_attr_data,
                                        uint16_t * const      p_sys_attr_data_len,
                                        uint32_t * const      p_flags)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_SYS_ATTR_SET);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_len16data(pp_sys_attr_data, p_sys_attr_data_len);
    SER_PULL_uint32(p_flags);

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_sys_attr_set_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_GATTS_SYS_ATTR_SET);
}

uint32_t ble_gatts_value_get_req_dec(uint8_t const * const       p_buf,
                                     uint16_t                    packet_len,
                                     uint16_t * const            p_conn_handle,
                                     uint16_t * const            p_handle,
                                     ble_gatts_value_t * * const pp_value)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_VALUE_GET);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_handle);

    //Special case: skip the data.
    SER_PULL_COND(pp_value, NULL);
    if (*pp_value)
    {
        SER_PULL_uint16(&(*pp_value)->offset);
        SER_PULL_uint16(&(*pp_value)->len);
        SER_PULL_COND(&(*pp_value)->p_value, NULL);
    }

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_value_get_rsp_enc(uint32_t                   return_code,
                                     uint8_t * const            p_buf,
                                     uint32_t * const           p_buf_len,
                                     ble_gatts_value_t * const  p_value)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_VALUE_GET);

    SER_PUSH_COND(p_value, ble_gatts_value_t_enc);

    SER_RSP_ENC_END;
}

uint32_t ble_gatts_value_set_req_dec(uint8_t const * const       p_buf,
                                     uint16_t                    packet_len,
                                     uint16_t *                  p_conn_handle,
                                     uint16_t *                  p_handle,
                                     ble_gatts_value_t * * const pp_value)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_VALUE_SET);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_handle);
    SER_PULL_COND(pp_value, ble_gatts_value_t_dec);

    SER_REQ_DEC_END;
}


uint32_t ble_gatts_value_set_rsp_enc(uint32_t            return_code,
                                     uint8_t * const     p_buf,
                                     uint32_t * const    p_buf_len,
                                     ble_gatts_value_t * p_value)
{
    SER_RSP_ENC_BEGIN(SD_BLE_GATTS_VALUE_SET);

    SER_PUSH_COND(p_value, ble_gatts_value_t_enc);

    SER_RSP_ENC_END;
}


uint32_t ble_gatts_exchange_mtu_reply_req_dec(uint8_t const * const       p_buf,
                                              uint16_t                    packet_len,
                                              uint16_t * const            p_conn_handle,
                                              uint16_t * const            p_server_rx_mtu)
{
    SER_REQ_DEC_BEGIN(SD_BLE_GATTS_EXCHANGE_MTU_REPLY);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_server_rx_mtu);

    SER_REQ_DEC_END;
}

uint32_t ble_gatts_exchange_mtu_reply_rsp_enc(uint32_t         return_code,
                                              uint8_t * const  p_buf,
                                              uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_GATTS_EXCHANGE_MTU_REPLY);
}
