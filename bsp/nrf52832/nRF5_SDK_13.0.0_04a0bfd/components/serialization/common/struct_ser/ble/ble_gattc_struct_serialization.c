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
#include "ble_gatt_struct_serialization.h"
#include "ble_gattc_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_serialization.h"
#include "app_util.h"
#include "ble_gattc.h"
#include "cond_field_serialization.h"
#include <string.h>

uint32_t ble_gattc_evt_char_val_by_uuid_read_rsp_t_enc(void const * const p_void_struct,
                                                       uint8_t * const    p_buf,
                                                       uint32_t           buf_len,
                                                       uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_char_val_by_uuid_read_rsp_t);

    SER_PUSH_uint16(&p_struct->count);
    SER_PUSH_uint16(&p_struct->value_len);

    // Copy the whole packed list.
    uint16_t list_length = (p_struct->value_len + sizeof(uint16_t)) * p_struct->count;
    SER_PUSH_uint8array(p_struct->handle_value, list_length);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_char_val_by_uuid_read_rsp_t_dec(uint8_t const * const p_buf,
                                                       uint32_t              buf_len,
                                                       uint32_t * const      p_index,
                                                       uint32_t * const      p_ext_len,
                                                       void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_char_val_by_uuid_read_rsp_t);

    SER_PULL_uint16(&p_struct->count);
    SER_PULL_uint16(&p_struct->value_len);

    uint16_t list_length = (p_struct->value_len + sizeof(uint16_t)) * p_struct->count;
    SER_ASSERT_LENGTH_LEQ(list_length, *p_ext_len);
    SER_PULL_uint8array(p_struct->handle_value, list_length);
    *p_ext_len = list_length;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_char_vals_read_rsp_t_enc(void const * const p_void_struct,
                                                uint8_t * const    p_buf,
                                                uint32_t           buf_len,
                                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_char_vals_read_rsp_t);

    SER_PUSH_uint16(&p_struct->len);
    SER_PUSH_uint8array(p_struct->values, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_char_vals_read_rsp_t_dec(uint8_t const * const p_buf,
                                                uint32_t              buf_len,
                                                uint32_t * const      p_index,
                                                uint32_t * const      p_ext_len,
                                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_char_vals_read_rsp_t);

    SER_PULL_uint16(&p_struct->len);

    SER_ASSERT_LENGTH_LEQ(p_struct->len, *p_ext_len);
    SER_PULL_uint8array(p_struct->values, p_struct->len);
    *p_ext_len = p_struct->len;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_handle_range_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_handle_range_t);

    SER_PUSH_uint16(&p_struct->start_handle);
    SER_PUSH_uint16(&p_struct->end_handle);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_handle_range_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_handle_range_t);

    SER_PULL_uint16(&p_struct->start_handle);
    SER_PULL_uint16(&p_struct->end_handle);

    SER_STRUCT_DEC_END;
}


uint32_t ble_gattc_service_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_service_t);

    SER_PUSH_FIELD(&p_struct->uuid, ble_uuid_t_enc);
    SER_PUSH_FIELD(&p_struct->handle_range, ble_gattc_handle_range_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_service_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_service_t);

    SER_PULL_FIELD(&p_struct->uuid, ble_uuid_t_dec);
    SER_PULL_FIELD(&p_struct->handle_range, ble_gattc_handle_range_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_include_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_include_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_FIELD(&p_struct->included_srvc, ble_gattc_service_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_include_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_include_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_FIELD(&p_struct->included_srvc, ble_gattc_service_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_rel_disc_rsp_t_enc(void const * const p_void_struct,
                                          uint8_t * const    p_buf,
                                          uint32_t           buf_len,
                                          uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_rel_disc_rsp_t);

    SER_PUSH_uint16(&p_struct->count);

    ble_gattc_include_t * p_include = &(p_struct->includes[0]);
    uint32_t i;

    for (i = 0; i < p_struct->count; i++)
    {
        SER_PUSH_FIELD(p_include, ble_gattc_include_t_enc);
        ++p_include;
    }

    SER_STRUCT_ENC_END;
}



uint32_t ble_gattc_evt_rel_disc_rsp_t_dec(uint8_t const * const p_buf,
                                          uint32_t              buf_len,
                                          uint32_t * const      p_index,
                                          uint32_t * const      p_ext_len,
                                          void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_rel_disc_rsp_t);

    SER_PULL_uint16(&p_struct->count);

    uint32_t data_len = (SUB1(p_struct->count) * sizeof(ble_gattc_include_t));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    ble_gattc_include_t * p_include = &(p_struct->includes[0]);
    uint32_t i;

    for (i = 0; i < p_struct->count; i++)
    {
        SER_PULL_FIELD(p_include, ble_gattc_include_t_dec);
        ++p_include;
    }

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_write_params_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_write_params_t);

    SER_PUSH_uint8(&p_struct->write_op);
    SER_PUSH_uint8(&p_struct->flags);
    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_len16data(p_struct->p_value, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_write_params_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_write_params_t);

    SER_PULL_uint8(&p_struct->write_op);
    SER_PULL_uint8(&p_struct->flags);
    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_len16data((uint8_t **) &p_struct->p_value, &p_struct->len);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_attr_info16_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_attr_info16_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_FIELD(&(p_struct->uuid), ble_uuid_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_attr_info16_t_dec(uint8_t const * const p_buf,
                                     uint32_t              buf_len,
                                     uint32_t * const      p_index,
                                     void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_attr_info16_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_FIELD(&(p_struct->uuid), ble_uuid_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_attr_info128_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_attr_info128_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_FIELD(&(p_struct->uuid), ble_uuid128_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_attr_info128_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_attr_info128_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_FIELD(&(p_struct->uuid), ble_uuid128_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_attr_info_disc_rsp_t_enc(void const * const p_void_struct,
                                                uint8_t * const    p_buf,
                                                uint32_t           buf_len,
                                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_attr_info_disc_rsp_t);

    SER_PUSH_uint16(&p_struct->count);
    SER_PUSH_uint8(&p_struct->format);

    field_encoder_handler_t fp_encoder = (p_struct->format == BLE_GATTC_ATTR_INFO_FORMAT_16BIT) ?
                                ble_gattc_attr_info16_t_enc : ble_gattc_attr_info128_t_enc;

    uint32_t i;
    for (i = 0; i < p_struct->count; ++i)
    {
        void * uuid_struct;
        uuid_struct = (p_struct->format == BLE_GATTC_ATTR_INFO_FORMAT_16BIT) ?
            (void *)&(p_struct->info.attr_info16[i]) : (void *)&(p_struct->info.attr_info128[i]);
        SER_PUSH_FIELD(uuid_struct, fp_encoder);
    }

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_attr_info_disc_rsp_t_dec(uint8_t const * const p_buf,
                                                uint32_t              buf_len,
                                                uint32_t * const      p_index,
                                                uint32_t * const      p_ext_len,
                                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_attr_info_disc_rsp_t);

    SER_PULL_uint16(&p_struct->count);
    SER_PULL_uint8(&p_struct->format);

    uint32_t i;
    uint32_t data_len;
    field_decoder_handler_t fp_decoder;
    if (p_struct->format == BLE_GATTC_ATTR_INFO_FORMAT_16BIT)
    {
        fp_decoder = ble_gattc_attr_info16_t_dec;
        data_len = (SUB1(p_struct->count) * sizeof(ble_gattc_attr_info16_t));
    }
    else
    {
        fp_decoder = ble_gattc_attr_info128_t_dec;
        data_len = (SUB1(p_struct->count) * sizeof(ble_gattc_attr_info128_t));
    }
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    for (i = 0; i < p_struct->count; i++)
    {
        void * uuid_struct;
        uuid_struct = (p_struct->format == BLE_GATTC_ATTR_INFO_FORMAT_16BIT) ?
                (void *)&(p_struct->info.attr_info16[i]) : (void *)&(p_struct->info.attr_info128[i]);
        SER_PULL_FIELD(uuid_struct, fp_decoder);
    }

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_char_t_enc(void const * const p_void_struct,
                              uint8_t * const    p_buf,
                              uint32_t           buf_len,
                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_char_t);

    uint8_t ser_data;
    SER_PUSH_FIELD(&p_struct->uuid, ble_uuid_t_enc);
    SER_PUSH_FIELD(&p_struct->char_props, ble_gatt_char_props_t_enc);
    ser_data = p_struct->char_ext_props & 0x01;
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint16(&p_struct->handle_decl);
    SER_PUSH_uint16(&p_struct->handle_value);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_char_t_dec(uint8_t const * const p_buf,
                              uint32_t              buf_len,
                              uint32_t * const      p_index,
                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_char_t);

    uint8_t ser_data;
    SER_PULL_FIELD(&p_struct->uuid, ble_uuid_t_dec);
    SER_PULL_FIELD(&p_struct->char_props, ble_gatt_char_props_t_dec);
    SER_PULL_uint8(&ser_data);
    p_struct->char_ext_props = ser_data & 0x01;
    SER_PULL_uint16(&p_struct->handle_decl);
    SER_PULL_uint16(&p_struct->handle_value);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_char_disc_rsp_t_enc(void const * const p_void_struct,
                                           uint8_t * const    p_buf,
                                           uint32_t           buf_len,
                                           uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_char_disc_rsp_t);

    SER_PUSH_uint16(&p_struct->count);
    SER_PUSH_FIELD_ARRAY(p_struct->chars, ble_gattc_char_t_enc, p_struct->count);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_char_disc_rsp_t_dec(uint8_t const * const p_buf,
                                           uint32_t              buf_len,
                                           uint32_t * const      p_index,
                                           uint32_t * const      p_ext_len,
                                           void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_char_disc_rsp_t);

    SER_PULL_uint16(&p_struct->count);
    uint32_t data_len = (SUB1(p_struct->count) * sizeof(ble_gattc_char_t));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_FIELD_ARRAY(p_struct->chars, ble_gattc_char_t_dec, p_struct->count);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_desc_t_enc(void const * const p_void_struct,
                              uint8_t * const    p_buf,
                              uint32_t           buf_len,
                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_desc_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_FIELD(&p_struct->uuid, ble_uuid_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_desc_t_dec(uint8_t const * const p_buf,
                              uint32_t              buf_len,
                              uint32_t * const      p_index,
                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_desc_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_FIELD(&p_struct->uuid, ble_uuid_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_desc_disc_rsp_t_enc(void const * const p_void_struct,
                                           uint8_t * const    p_buf,
                                           uint32_t           buf_len,
                                           uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_desc_disc_rsp_t);

    SER_PUSH_uint16(&p_struct->count);
    SER_PUSH_FIELD_ARRAY(p_struct->descs, ble_gattc_desc_t_enc, p_struct->count);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_desc_disc_rsp_t_dec(uint8_t const * const p_buf,
                                           uint32_t              buf_len,
                                           uint32_t * const      p_index,
                                           uint32_t * const      p_ext_len,
                                           void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_desc_disc_rsp_t);

    SER_PULL_uint16(&p_struct->count);
    uint32_t data_len = (SUB1(p_struct->count) * sizeof(ble_gattc_desc_t));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_FIELD_ARRAY(p_struct->descs, ble_gattc_desc_t_dec, p_struct->count);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_hvx_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_hvx_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_uint8(&p_struct->type);
    SER_PUSH_uint16(&p_struct->len);
    SER_PUSH_uint8array(p_struct->data, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_hvx_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 uint32_t * const      p_ext_len,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_hvx_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_uint8(&p_struct->type);
    SER_PULL_uint16(&p_struct->len);

    uint32_t data_len = (SUB1(p_struct->len));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_uint8array(p_struct->data, p_struct->len);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_prim_srvc_disc_rsp_t_enc(void const * const p_void_struct,
                                                uint8_t * const    p_buf,
                                                uint32_t           buf_len,
                                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_prim_srvc_disc_rsp_t);

    SER_PUSH_uint16(&p_struct->count);
    SER_PUSH_FIELD_ARRAY(p_struct->services, ble_gattc_service_t_enc, p_struct->count);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_prim_srvc_disc_rsp_t_dec(uint8_t const * const p_buf,
                                                uint32_t              buf_len,
                                                uint32_t * const      p_index,
                                                uint32_t * const      p_ext_len,
                                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_prim_srvc_disc_rsp_t);

    SER_PULL_uint16(&p_struct->count);
    uint32_t data_len = (SUB1(p_struct->count) * sizeof(ble_gattc_service_t));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_FIELD_ARRAY(p_struct->services, ble_gattc_service_t_dec, p_struct->count);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_read_rsp_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_read_rsp_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_uint16(&p_struct->len);
    SER_PUSH_uint8array(p_struct->data, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_read_rsp_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      uint32_t * const      p_ext_len,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_read_rsp_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_uint16(&p_struct->len);

    uint32_t data_len = (SUB1(p_struct->len));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_uint8array(p_struct->data, p_struct->len);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_timeout_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_timeout_t);
    SER_PUSH_uint8(&p_struct->src);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_timeout_t_dec(uint8_t const * const p_buf,
                                     uint32_t              buf_len,
                                     uint32_t * const      p_index,
                                     void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_timeout_t);
    SER_PULL_uint8(&p_struct->src);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_write_rsp_t_enc(void const * const p_void_struct,
                                       uint8_t * const    p_buf,
                                       uint32_t           buf_len,
                                       uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_write_rsp_t);

    SER_PUSH_uint16(&p_struct->handle);
    SER_PUSH_uint8(&p_struct->write_op);
    SER_PUSH_uint16(&p_struct->offset);
    SER_PUSH_uint16(&p_struct->len);
    SER_PUSH_uint8array(p_struct->data, p_struct->len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_write_rsp_t_dec(uint8_t const * const p_buf,
                                       uint32_t              buf_len,
                                       uint32_t * const      p_index,
                                       uint32_t * const      p_ext_len,
                                       void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_write_rsp_t);

    SER_PULL_uint16(&p_struct->handle);
    SER_PULL_uint8(&p_struct->write_op);
    SER_PULL_uint16(&p_struct->offset);
    SER_PULL_uint16(&p_struct->len);

    uint32_t data_len = (SUB1(p_struct->len));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_uint8array(p_struct->data, p_struct->len);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}

uint32_t ble_gattc_evt_exchange_mtu_rsp_t_enc(void const * const p_void_struct,
                                              uint8_t * const    p_buf,
                                              uint32_t           buf_len,
                                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_evt_exchange_mtu_rsp_t);
    SER_PUSH_uint16(&p_struct->server_rx_mtu);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_evt_exchange_mtu_rsp_t_dec(uint8_t const * const p_buf,
                                              uint32_t              buf_len,
                                              uint32_t * const      p_index,
                                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_evt_exchange_mtu_rsp_t);
    SER_PULL_uint16(&p_struct->server_rx_mtu);
    SER_STRUCT_DEC_END;
}

#if NRF_SD_BLE_API_VERSION >= 4
uint32_t ble_gattc_conn_cfg_t_enc(void const * const p_void_struct,
                                              uint8_t * const    p_buf,
                                              uint32_t           buf_len,
                                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gattc_conn_cfg_t);
    SER_PUSH_uint8(&p_struct->write_cmd_tx_queue_size);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gattc_conn_cfg_t_dec(uint8_t const * const p_buf,
                                              uint32_t              buf_len,
                                              uint32_t * const      p_index,
                                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gattc_conn_cfg_t);
    SER_PULL_uint8(&p_struct->write_cmd_tx_queue_size);
    SER_STRUCT_DEC_END;
}
#endif
