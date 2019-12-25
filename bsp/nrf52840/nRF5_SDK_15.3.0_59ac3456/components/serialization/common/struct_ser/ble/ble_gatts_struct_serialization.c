/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include "ble_gatt_struct_serialization.h"
#include "ble_gatts_struct_serialization.h"
#include "ble_gap_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_serialization.h"
#include "app_util.h"
#include "ble_gatts.h"
#include "cond_field_serialization.h"
#include <string.h>

uint32_t ble_gatts_char_pf_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_char_pf_t);

    SER_PUSH_uint8(&p_struct->format);
    SER_PUSH_int8(&p_struct->exponent);
    SER_PUSH_uint16(&p_struct->unit);
    SER_PUSH_uint8(&p_struct->name_space);
    SER_PUSH_uint16(&p_struct->desc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_char_pf_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_char_pf_t);

    SER_PULL_uint8(&p_struct->format);
    SER_PULL_int8(&p_struct->exponent);
    SER_PULL_uint16(&p_struct->unit);
    SER_PULL_uint8(&p_struct->name_space);
    SER_PULL_uint16(&p_struct->desc);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_attr_md_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_attr_md_t);

    SER_PUSH_FIELD(&p_struct->read_perm, ble_gap_conn_sec_mode_t_enc);
    SER_PUSH_FIELD(&p_struct->write_perm, ble_gap_conn_sec_mode_t_enc);
    uint8_t ser_data = (p_struct->vlen & 0x01)
                       | ((p_struct->vloc & 0x03) << 1)
                       | ((p_struct->rd_auth & 0x01) << 3)
                       | ((p_struct->wr_auth & 0x01) << 4);
    SER_PUSH_uint8(&ser_data);

    // Serializer does not support attributes on stack.
    if (p_struct->vloc != BLE_GATTS_VLOC_STACK)
    {
        err_code = NRF_ERROR_INVALID_PARAM;
    }

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_attr_md_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_attr_md_t);

    uint8_t ser_data;
    SER_PULL_FIELD(&p_struct->read_perm, ble_gap_conn_sec_mode_t_dec);
    SER_PULL_FIELD(&p_struct->write_perm, ble_gap_conn_sec_mode_t_dec);
    SER_PULL_uint8(&ser_data);

    p_struct->vlen    = ser_data & 0x01;
    p_struct->vloc    = (ser_data >> 1) & 0x03;
    p_struct->rd_auth = (ser_data >> 3) & 0x01;
    p_struct->wr_auth = (ser_data >> 4) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_char_md_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_char_md_t);

    SER_PUSH_FIELD(&p_struct->char_props, ble_gatt_char_props_t_enc);
    SER_PUSH_FIELD(&p_struct->char_ext_props, ble_gatt_char_ext_props_t_enc);
    SER_PUSH_uint16(&p_struct->char_user_desc_max_size);
    SER_ERROR_CHECK(p_struct->char_user_desc_size <= BLE_GATTS_VAR_ATTR_LEN_MAX,
                    NRF_ERROR_INVALID_PARAM);
    SER_PUSH_len16data(p_struct->p_char_user_desc, p_struct->char_user_desc_size);
    SER_PUSH_COND(p_struct->p_char_pf, ble_gatts_char_pf_t_enc);
    SER_PUSH_COND(p_struct->p_user_desc_md, ble_gatts_attr_md_t_enc);
    SER_PUSH_COND(p_struct->p_cccd_md, ble_gatts_attr_md_t_enc);
    SER_PUSH_COND(p_struct->p_sccd_md, ble_gatts_attr_md_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_char_md_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_char_md_t);

    SER_PULL_FIELD(&p_struct->char_props, ble_gatt_char_props_t_dec);
    SER_PULL_FIELD(&p_struct->char_ext_props, ble_gatt_char_ext_props_t_dec);
    SER_PULL_uint16(&p_struct->char_user_desc_max_size);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
    SER_PULL_len16data(&p_struct->p_char_user_desc, &p_struct->char_user_desc_size);
#else
    SER_PULL_len16data((uint8_t * *  )&p_struct->p_char_user_desc, &p_struct->char_user_desc_size);
#endif
    SER_PULL_COND(&p_struct->p_char_pf, ble_gatts_char_pf_t_dec);
    SER_PULL_COND(&p_struct->p_user_desc_md, ble_gatts_attr_md_t_dec);
    SER_PULL_COND(&p_struct->p_cccd_md, ble_gatts_attr_md_t_dec);
    SER_PULL_COND(&p_struct->p_sccd_md, ble_gatts_attr_md_t_dec);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_attr_t_enc(void const * const p_void_struct,
                              uint8_t * const    p_buf,
                              uint32_t           buf_len,
                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_attr_t);

    SER_PUSH_COND(p_struct->p_uuid, ble_uuid_t_enc);
    SER_PUSH_COND(p_struct->p_attr_md, ble_gatts_attr_md_t_enc);
    SER_PUSH_uint16(&p_struct->init_offs);
    SER_PUSH_uint16(&p_struct->max_len);
    SER_ERROR_CHECK(p_struct->init_len <= BLE_GATTS_VAR_ATTR_LEN_MAX, NRF_ERROR_INVALID_PARAM);
    SER_PUSH_len16data(p_struct->p_value, p_struct->init_len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_attr_t_dec(uint8_t const * const p_buf,
                            uint32_t              buf_len,
                            uint32_t * const      p_index,
                            void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_attr_t);

    SER_PULL_COND(&p_struct->p_uuid, ble_uuid_t_dec);
    SER_PULL_COND(&p_struct->p_attr_md, ble_gatts_attr_md_t_dec);
    SER_PULL_uint16(&p_struct->init_offs);
    SER_PULL_uint16(&p_struct->max_len);
    SER_PULL_len16data(&p_struct->p_value, &p_struct->init_len);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_char_handles_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_char_handles_t);

    SER_PUSH_uint16(&p_struct->value_handle);
    SER_PUSH_uint16(&p_struct->user_desc_handle);
    SER_PUSH_uint16(&p_struct->cccd_handle);
    SER_PUSH_uint16(&p_struct->sccd_handle);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_char_handles_t_dec(uint8_t const * const p_buf,
                                    uint32_t              buf_len,
                                    uint32_t * const      p_index,
                                    void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_char_handles_t);

    SER_PULL_uint16(&p_struct->value_handle);
    SER_PULL_uint16(&p_struct->user_desc_handle);
    SER_PULL_uint16(&p_struct->cccd_handle);
    SER_PULL_uint16(&p_struct->sccd_handle);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_hvx_params_t_enc(void const * const p_void_struct,
                                    uint8_t * const    p_buf,
                                    uint32_t           buf_len,
                                    uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_hvx_params_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_uint8(&p_struct->type);
    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_COND(p_struct->p_len, uint16_t_enc);
    if (p_struct->p_len)
    {
        SER_PUSH_buf(p_struct->p_data, *p_struct->p_len);
    }

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_hvx_params_t_dec(uint8_t const * const p_buf,
                                    uint32_t              buf_len,
                                    uint32_t * const      p_index,
                                    void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_hvx_params_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_uint8(&p_struct->type);
    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_COND(&p_struct->p_len, uint16_t_dec);
    if (p_struct->p_len)
    {
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
    SER_PULL_buf(&p_struct->p_data, *p_struct->p_len, *p_struct->p_len);
#else
    SER_PULL_buf((uint8_t**)&p_struct->p_data, *p_struct->p_len, *p_struct->p_len);
#endif
    }

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_evt_write_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_write_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_FIELD(&p_struct->uuid, ble_uuid_t_enc);
    SER_PUSH_uint8(&p_struct->op);
    SER_PUSH_uint8(&p_struct->auth_required);
    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_uint16(&p_struct->len);
    SER_PUSH_uint8array(p_struct->data, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_write_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   uint32_t * const      p_ext_len,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_write_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_FIELD(&p_struct->uuid, ble_uuid_t_dec);
    SER_PULL_uint8(&p_struct->op);
    SER_PULL_uint8(&p_struct->auth_required);
    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_uint16(&p_struct->len);

    // Data field is defined as 1-element array, so the first element
    // is always allocated in the structure.
    SER_ASSERT_LENGTH_LEQ(p_struct->len, *p_ext_len + 1);
    SER_PULL_uint8array(p_struct->data, p_struct->len);
    *p_ext_len = (p_struct->len > 1) ? p_struct->len - 1 : 0;

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_read_t_enc(void const * const p_void_struct,
                                  uint8_t * const    p_buf,
                                  uint32_t           buf_len,
                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_read_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_FIELD(&p_struct->uuid, ble_uuid_t_enc);
    SER_PUSH_uint16(&p_struct->offset);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_read_t_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_read_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_FIELD(&p_struct->uuid, ble_uuid_t_dec);
    SER_PULL_uint16(&p_struct->offset);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_evt_rw_authorize_request_t_enc(void const * const p_void_struct,
                                                  uint8_t * const    p_buf,
                                                  uint32_t           buf_len,
                                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_rw_authorize_request_t);

    SER_PUSH_uint8(&p_struct->type);

    switch (p_struct->type)
    {
        case BLE_GATTS_AUTHORIZE_TYPE_READ:
            SER_PUSH_FIELD(&p_struct->request.read, ble_gatts_evt_read_t_enc);
            break;

        case BLE_GATTS_AUTHORIZE_TYPE_WRITE:
            SER_PUSH_FIELD(&p_struct->request.write, ble_gatts_evt_write_t_enc);
            break;

        default:
        case BLE_GATTS_AUTHORIZE_TYPE_INVALID:
            err_code = NRF_ERROR_INVALID_PARAM;
            break;
    }

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_rw_authorize_request_t_dec(uint8_t const * const p_buf,
                                                  uint32_t              buf_len,
                                                  uint32_t * const      p_index,
                                                  uint32_t * const      p_ext_len,
                                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_rw_authorize_request_t);

    SER_PULL_uint8(&p_struct->type);

    switch (p_struct->type)
    {
        case BLE_GATTS_AUTHORIZE_TYPE_READ:
            SER_PULL_FIELD(&p_struct->request.read, ble_gatts_evt_read_t_dec);
            break;

        case BLE_GATTS_AUTHORIZE_TYPE_WRITE:
            err_code = ble_gatts_evt_write_t_dec(p_buf,
                                                 buf_len,
                                                 p_index,
                                                 p_ext_len,
                                                 &p_struct->request.write);
            SER_ASSERT(err_code == NRF_SUCCESS, err_code);
            break;

        default:
        case BLE_GATTS_AUTHORIZE_TYPE_INVALID:
            return NRF_ERROR_INVALID_DATA;
    }

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_authorize_params_t_enc(void const * const p_void_struct,
                                          uint8_t * const    p_buf,
                                          uint32_t           buf_len,
                                          uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_authorize_params_t);

    uint8_t ser_data = p_struct->update & 0x01;
    SER_PUSH_uint16(&p_struct->gatt_status);
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_len16data(p_struct->p_data, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_authorize_params_t_dec(uint8_t const * const p_buf,
                                          uint32_t              buf_len,
                                          uint32_t * const      p_index,
                                          void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_authorize_params_t);

    uint8_t ser_data;
    SER_PULL_uint16(&p_struct->gatt_status);
    SER_PULL_uint8(&ser_data);
    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_len16data((uint8_t **) &p_struct->p_data, &p_struct->len);

    p_struct->update = ser_data & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_rw_authorize_reply_params_t_enc(void const * const p_void_struct,
                                                   uint8_t * const    p_buf,
                                                   uint32_t           buf_len,
                                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_rw_authorize_reply_params_t);

    SER_PUSH_uint8(&p_struct->type);
    if (p_struct->type == BLE_GATTS_AUTHORIZE_TYPE_READ)
    {
        SER_PUSH_FIELD(&p_struct->params.read, ble_gatts_authorize_params_t_enc);
    }
    else if (p_struct->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        SER_PUSH_FIELD(&p_struct->params.write, ble_gatts_authorize_params_t_enc);
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_rw_authorize_reply_params_t_dec(uint8_t const * const p_buf,
                                                   uint32_t              buf_len,
                                                   uint32_t * const      p_index,
                                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_rw_authorize_reply_params_t);

    SER_PULL_uint8(&p_struct->type);
    if (p_struct->type == BLE_GATTS_AUTHORIZE_TYPE_READ)
    {
        SER_PULL_FIELD(&p_struct->params.read, ble_gatts_authorize_params_t_dec);
    }
    else if (p_struct->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
    {
        SER_PULL_FIELD(&p_struct->params.write, ble_gatts_authorize_params_t_dec);
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    SER_STRUCT_DEC_END;
}
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gatts_enable_params_t_enc(void const * const p_void_struct,
                                       uint8_t * const    p_buf,
                                       uint32_t           buf_len,
                                       uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_enable_params_t);

    uint8_t ser_data = p_struct->service_changed & 0x01;
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint32(&p_struct->attr_tab_size);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_enable_params_t_dec(uint8_t const * const p_buf,
                                       uint32_t              buf_len,
                                       uint32_t * const      p_index,
                                       void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_enable_params_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    SER_PULL_uint32(&p_struct->attr_tab_size);

    p_struct->service_changed = ser_data & 0x01;

    SER_STRUCT_DEC_END;
}
#endif

uint32_t ble_gatts_value_t_enc(void const * const p_void_struct,
                               uint8_t * const    p_buf,
                               uint32_t           buf_len,
                               uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_value_t);

    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_len16data(p_struct->p_value, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_value_t_dec(uint8_t const * const p_buf,
                               uint32_t              buf_len,
                               uint32_t * const      p_index,
                               void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_value_t);

    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_len16data(&p_struct->p_value, &p_struct->len);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_evt_exchange_mtu_request_t_enc(void const * const p_void_struct,
                                                  uint8_t * const    p_buf,
                                                  uint32_t           buf_len,
                                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_exchange_mtu_request_t);
    SER_PUSH_uint16(&p_struct->client_rx_mtu);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_exchange_mtu_request_t_dec(uint8_t const * const p_buf,
                                                  uint32_t              buf_len,
                                                  uint32_t * const      p_index,
                                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_exchange_mtu_request_t);
    SER_PULL_uint16(&p_struct->client_rx_mtu);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_evt_hvc_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_hvc_t);
    SER_PUSH_uint16(&p_struct->handle);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_hvc_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_hvc_t);
    SER_PULL_uint16(&p_struct->handle);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_evt_sys_attr_missing_t_enc(void const * const p_void_struct,
                                              uint8_t * const    p_buf,
                                              uint32_t           buf_len,
                                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_sys_attr_missing_t);
    SER_PUSH_uint8(&p_struct->hint);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_sys_attr_missing_t_dec(uint8_t const * const p_buf,
                                              uint32_t              buf_len,
                                              uint32_t * const      p_index,
                                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_sys_attr_missing_t);
    SER_PULL_uint8(&p_struct->hint);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_evt_timeout_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_evt_timeout_t);
    SER_PUSH_uint8(&p_struct->src);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_evt_timeout_t_dec(uint8_t const * const p_buf,
                                     uint32_t              buf_len,
                                     uint32_t * const      p_index,
                                     void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_evt_timeout_t);
    SER_PULL_uint8(&p_struct->src);
    SER_STRUCT_DEC_END;
}

#if NRF_SD_BLE_API_VERSION >= 4
uint32_t ble_gatts_conn_cfg_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_conn_cfg_t);
    SER_PUSH_uint8(&p_struct->hvn_tx_queue_size);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_conn_cfg_t_dec(uint8_t const * const p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index,
                                     void * const       p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_conn_cfg_t);
    SER_PULL_uint8(&p_struct->hvn_tx_queue_size);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gatts_cfg_service_changed_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_cfg_service_changed_t);
    uint8_t service_changed = p_struct->service_changed;
    SER_PUSH_uint8(&service_changed);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_cfg_service_changed_t_dec(uint8_t const * const p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index,
                                     void * const       p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_cfg_service_changed_t);
    uint8_t service_changed;
    SER_PULL_uint8(&service_changed);
    p_struct->service_changed = service_changed;
    SER_STRUCT_DEC_END;
}
uint32_t ble_gatts_cfg_attr_tab_size_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatts_cfg_attr_tab_size_t);
    SER_PUSH_uint32(&p_struct->attr_tab_size);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gatts_cfg_attr_tab_size_t_dec(uint8_t const * const p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index,
                                     void * const       p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatts_cfg_attr_tab_size_t);
    SER_PULL_uint32(&p_struct->attr_tab_size);
    SER_STRUCT_DEC_END;
}


#endif
