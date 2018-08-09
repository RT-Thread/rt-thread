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
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_gatt_struct_serialization.h"
#include "cond_field_serialization.h"
#include "app_util.h"
#include "ble_gatt.h"
#include <string.h>

uint32_t ble_gatt_char_props_t_enc(void const * const p_void_struct,
                              uint8_t * const    p_buf,
                              uint32_t           buf_len,
                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatt_char_props_t);

    uint8_t ser_data = (p_struct->broadcast         & 0x01)
                       | ((p_struct->read           & 0x01) << 1)
                       | ((p_struct->write_wo_resp  & 0x01) << 2)
                       | ((p_struct->write          & 0x01) << 3)
                       | ((p_struct->notify         & 0x01) << 4)
                       | ((p_struct->indicate       & 0x01) << 5)
                       | ((p_struct->auth_signed_wr & 0x01) << 6);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatt_char_props_t_dec(uint8_t const * const p_buf,
                              uint32_t              buf_len,
                              uint32_t * const      p_index,
                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatt_char_props_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->broadcast      = ser_data & 0x01;
    p_struct->read           = (ser_data >> 1) & 0x01;
    p_struct->write_wo_resp  = (ser_data >> 2) & 0x01;
    p_struct->write          = (ser_data >> 3) & 0x01;
    p_struct->notify         = (ser_data >> 4) & 0x01;
    p_struct->indicate       = (ser_data >> 5) & 0x01;
    p_struct->auth_signed_wr = (ser_data >> 6) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gatt_char_ext_props_t_enc(void const * const p_void_struct,
                              uint8_t * const    p_buf,
                              uint32_t           buf_len,
                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatt_char_ext_props_t);

    uint8_t ser_data = (p_struct->reliable_wr & 0x01)
                       | ((p_struct->wr_aux   & 0x01) << 1);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gatt_char_ext_props_t_dec(uint8_t const * const p_buf,
                              uint32_t              buf_len,
                              uint32_t * const      p_index,
                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatt_char_ext_props_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->reliable_wr = ser_data & 0x01;
    p_struct->wr_aux      = (ser_data >> 1) & 0x01;

    SER_STRUCT_DEC_END;
}

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gatt_enable_params_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatt_enable_params_t);
    SER_PUSH_uint16(&p_struct->att_mtu);
    SER_STRUCT_ENC_END;
}


uint32_t ble_gatt_enable_params_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatt_enable_params_t);
    SER_PULL_uint16(&p_struct->att_mtu);
    SER_STRUCT_DEC_END;
}
#else
uint32_t ble_gatt_conn_cfg_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gatt_conn_cfg_t);
    SER_PUSH_uint16(&p_struct->att_mtu);
    SER_STRUCT_ENC_END;
}


uint32_t ble_gatt_conn_cfg_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gatt_conn_cfg_t);
    SER_PULL_uint16(&p_struct->att_mtu);
    SER_STRUCT_DEC_END;
}
#endif
