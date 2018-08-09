/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include "ble_gap_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_serialization.h"
#include "cond_field_serialization.h"
#include "app_util.h"
#include "string.h"
#include "ble_gatts.h"

#ifndef S112
uint32_t ble_gap_evt_adv_report_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_adv_report_t);
#if NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_FIELD(&p_struct->type, ble_gap_adv_report_type_t_enc);
    SER_PUSH_FIELD(&p_struct->peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_FIELD(&p_struct->direct_addr, ble_gap_addr_t_enc);
    SER_PUSH_uint8(&p_struct->primary_phy);
    SER_PUSH_uint8(&p_struct->secondary_phy);
    SER_PUSH_int8(&p_struct->tx_power);
    SER_PUSH_int8(&p_struct->rssi);
    SER_PUSH_uint8(&p_struct->ch_index);
    SER_PUSH_uint8(&p_struct->set_id);
    uint16_t temp = p_struct->data_id;
    SER_PUSH_uint16(&temp);
    SER_PUSH_FIELD(&p_struct->data, ble_data_t_enc);
    SER_PUSH_FIELD(&p_struct->aux_pointer, ble_gap_aux_pointer_t_enc);
#else
    uint8_t ser_data = (p_struct->scan_rsp & 0x01)
                       | ((p_struct->type & 0x03) << 1);
    uint8_t data_len = (p_struct->dlen & 0x1F);
    SER_PUSH_FIELD(&p_struct->peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_FIELD(&p_struct->direct_addr, ble_gap_addr_t_enc);
    SER_PUSH_int8(&p_struct->rssi);
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_len8data(p_struct->data, data_len);
#endif
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_adv_report_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_adv_report_t);

#if NRF_SD_BLE_API_VERSION > 5
    SER_PULL_FIELD(&p_struct->type, ble_gap_adv_report_type_t_dec);
    SER_PULL_FIELD(&p_struct->peer_addr, ble_gap_addr_t_dec);
    SER_PULL_FIELD(&p_struct->direct_addr, ble_gap_addr_t_dec);
    SER_PULL_uint8(&p_struct->primary_phy);
    SER_PULL_uint8(&p_struct->secondary_phy);
    SER_PULL_int8(&p_struct->tx_power);
    SER_PULL_int8(&p_struct->rssi);
    SER_PULL_uint8(&p_struct->ch_index);
    SER_PULL_uint8(&p_struct->set_id);
    uint16_t temp;
    SER_PULL_uint16(&temp);
    p_struct->data_id = temp & 0x0FFF;
    SER_PULL_FIELD(&p_struct->data, ble_data_t_dec);
    SER_PULL_FIELD(&p_struct->aux_pointer, ble_gap_aux_pointer_t_dec);
#else
    uint8_t ser_data;
    uint8_t data_len = BLE_GAP_ADV_MAX_SIZE;
    uint8_t * p_field_data = p_struct->data;
    SER_PULL_FIELD(&p_struct->peer_addr, ble_gap_addr_t_dec);
    SER_PULL_FIELD(&p_struct->direct_addr, ble_gap_addr_t_dec);
    SER_PULL_int8(&p_struct->rssi);
    SER_PULL_uint8(&ser_data);
    SER_PULL_len8data(&p_field_data, &data_len);

    p_struct->scan_rsp = ser_data & 0x01;
    p_struct->type     = (ser_data >> 1) & 0x03;
    p_struct->dlen     = data_len;
#endif
    SER_STRUCT_DEC_END;
}
#endif

uint32_t ble_gap_irk_t_enc(void const * const p_void_struct,
                           uint8_t * const    p_buf,
                           uint32_t           buf_len,
                           uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_irk_t);
    SER_PUSH_uint8array(p_struct->irk, BLE_GAP_SEC_KEY_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_irk_t_dec(uint8_t const * const p_buf,
                           uint32_t              buf_len,
                           uint32_t * const      p_index,
                           void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_irk_t);
    SER_PULL_uint8array(p_struct->irk, BLE_GAP_SEC_KEY_LEN);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_addr_t_enc(void const * const p_void_struct,
                            uint8_t * const    p_buf,
                            uint32_t           buf_len,
                            uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_addr_t);

    uint8_t ser_data = (p_struct->addr_id_peer & 0x01)
                       | ((p_struct->addr_type & 0x7F) << 1);
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint8array(p_struct->addr, BLE_GAP_ADDR_LEN);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_addr_t_dec(uint8_t const * const p_buf,
                            uint32_t              buf_len,
                            uint32_t * const      p_index,
                            void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_addr_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    SER_PULL_uint8array(p_struct->addr, BLE_GAP_ADDR_LEN);

    p_struct->addr_id_peer = ser_data & 0x01;
    p_struct->addr_type    = (ser_data >> 1) & 0x7F;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_sec_levels_t_enc(void const * const p_void_struct,
                                  uint8_t * const    p_buf,
                                  uint32_t           buf_len,
                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_sec_levels_t);

    uint8_t sec_levels_serialized = (p_struct->lv1 << 0) | (p_struct->lv2 << 1)
                                    | (p_struct->lv3 << 2) | (p_struct->lv4 << 3);
    SER_PUSH_uint8(&sec_levels_serialized);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_sec_levels_t_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_sec_levels_t);

    uint32_t sec_levels_serialized;
    SER_PULL_uint8(&sec_levels_serialized);

    p_struct->lv1 = sec_levels_serialized & 0x01;
    p_struct->lv2 = (sec_levels_serialized >> 1) & 0x01;
    p_struct->lv3 = (sec_levels_serialized >> 2) & 0x01;
    p_struct->lv4 = (sec_levels_serialized >> 3) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_sec_keys_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_sec_keys_t);

    SER_PUSH_COND(p_struct->p_enc_key, ble_gap_enc_key_t_enc);
    SER_PUSH_COND(p_struct->p_id_key, ble_gap_id_key_t_enc);
    SER_PUSH_COND(p_struct->p_sign_key, ble_gap_sign_info_t_enc);
    SER_PUSH_COND(p_struct->p_pk, ble_gap_lesc_p256_pk_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_sec_keys_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_sec_keys_t);

    SER_PULL_COND(&(p_struct->p_enc_key), ble_gap_enc_key_t_dec);
    SER_PULL_COND(&(p_struct->p_id_key), ble_gap_id_key_t_dec);
    SER_PULL_COND(&(p_struct->p_sign_key), ble_gap_sign_info_t_dec);
    SER_PULL_COND(&(p_struct->p_pk), ble_gap_lesc_p256_pk_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_enc_info_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_enc_info_t);

    SER_PUSH_uint8array(p_struct->ltk, BLE_GAP_SEC_KEY_LEN);
    uint8_t ser_data = (p_struct->lesc & 0x01)
                       | ((p_struct->auth & 0x01) << 1)
                       | ((p_struct->ltk_len & 0x3F) << 2);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_enc_info_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_enc_info_t);

    uint8_t ser_data;
    SER_PULL_uint8array(p_struct->ltk, BLE_GAP_SEC_KEY_LEN);
    SER_PULL_uint8(&ser_data);
    p_struct->lesc    = ser_data & 0x01;
    p_struct->auth    = (ser_data >> 1) & 0x01;
    p_struct->ltk_len = (ser_data >> 2) & 0x3F;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_sign_info_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_sign_info_t);
    SER_PUSH_uint8array(p_struct->csrk, BLE_GAP_SEC_KEY_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_sign_info_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_sign_info_t);
    SER_PULL_uint8array(p_struct->csrk, BLE_GAP_SEC_KEY_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_auth_status_t_enc(void const * const p_void_struct,
                                       uint8_t * const    p_buf,
                                       uint32_t           buf_len,
                                       uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_auth_status_t);
    uint8_t ser_data = (p_struct->error_src) | ((p_struct->bonded) << 2);
#if NRF_SD_BLE_API_VERSION >= 5
    ser_data |= ((p_struct->lesc) << 3);
#endif
    SER_PUSH_uint8(&(p_struct->auth_status));
    SER_PUSH_uint8(&ser_data);

    SER_PUSH_FIELD(&(p_struct->sm1_levels), ble_gap_sec_levels_t_enc);
    SER_PUSH_FIELD(&(p_struct->sm2_levels), ble_gap_sec_levels_t_enc);
    SER_PUSH_FIELD(&(p_struct->kdist_own), ble_gap_sec_kdist_t_enc);
    SER_PUSH_FIELD(&(p_struct->kdist_peer), ble_gap_sec_kdist_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_auth_status_t_dec(uint8_t const * const p_buf,
                                       uint32_t              buf_len,
                                       uint32_t * const      p_index,
                                       void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_auth_status_t);

    uint8_t ser_data;
    SER_PULL_uint8(&(p_struct->auth_status));
    SER_PULL_uint8(&ser_data);
    p_struct->error_src = ser_data & 0x03;
    p_struct->bonded    = (ser_data >> 2) & 0x01;
#if NRF_SD_BLE_API_VERSION >= 5
    p_struct->lesc    = (ser_data >> 3) & 0x01;
#endif

    SER_PULL_FIELD(&(p_struct->sm1_levels), ble_gap_sec_levels_t_dec);
    SER_PULL_FIELD(&(p_struct->sm2_levels), ble_gap_sec_levels_t_dec);
    SER_PULL_FIELD(&(p_struct->kdist_own), ble_gap_sec_kdist_t_dec);
    SER_PULL_FIELD(&(p_struct->kdist_peer), ble_gap_sec_kdist_t_dec);

    SER_STRUCT_DEC_END;
}


uint32_t ble_gap_conn_sec_mode_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_conn_sec_mode_t);

    uint8_t ser_data = (p_struct->sm & 0x0F)
                       | ((p_struct->lv & 0x0F) << 4);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_conn_sec_mode_t_dec(uint8_t const * const p_buf,
                                     uint32_t              buf_len,
                                     uint32_t * const      p_index,
                                     void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_conn_sec_mode_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->sm = ser_data & 0x0F;
    p_struct->lv = (ser_data >> 4) & 0x0F;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_conn_sec_update_t_enc(void const * const p_void_struct,
                                           uint8_t * const    p_buf,
                                           uint32_t           buf_len,
                                           uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_conn_sec_update_t);
    SER_PUSH_FIELD(&(p_struct->conn_sec), ble_gap_conn_sec_t_enc);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_conn_sec_update_t_dec(uint8_t const * const p_buf,
                                           uint32_t              buf_len,
                                           uint32_t * const      p_index,
                                           void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_conn_sec_update_t);
    SER_PULL_FIELD(&(p_struct->conn_sec), ble_gap_conn_sec_t_dec);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_conn_sec_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_conn_sec_t);

    SER_PUSH_FIELD(&p_struct->sec_mode, ble_gap_conn_sec_mode_t_enc);
    SER_PUSH_uint8(&p_struct->encr_key_size);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_conn_sec_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_conn_sec_t);

    SER_PULL_FIELD(&p_struct->sec_mode, ble_gap_conn_sec_mode_t_dec);
    SER_PULL_uint8(&p_struct->encr_key_size);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_sec_info_request_t_enc(void const * const p_void_struct,
                                            uint8_t * const    p_buf,
                                            uint32_t           buf_len,
                                            uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_sec_info_request_t);

    uint8_t ser_data = (p_struct->enc_info & 0x01)
                       | ((p_struct->id_info & 0x01) << 1)
                       | ((p_struct->sign_info& 0x01) << 2);
    SER_PUSH_FIELD(&p_struct->peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_FIELD(&p_struct->master_id, ble_gap_master_id_t_enc);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_sec_info_request_t_dec(uint8_t const * const p_buf,
                                            uint32_t              buf_len,
                                            uint32_t * const      p_index,
                                            void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_sec_info_request_t);

    uint8_t ser_data;
    SER_PULL_FIELD(&p_struct->peer_addr, ble_gap_addr_t_dec);
    SER_PULL_FIELD(&p_struct->master_id, ble_gap_master_id_t_dec);
    SER_PULL_uint8(&ser_data);
    p_struct->enc_info  = ser_data & 0x01;
    p_struct->id_info   = (ser_data >> 1) & 0x01;
    p_struct->sign_info = (ser_data >> 2) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_connected_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_connected_t);

    SER_PUSH_FIELD(&p_struct->peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_uint8(&p_struct->role);
    SER_PUSH_FIELD(&p_struct->conn_params, ble_gap_conn_params_t_enc);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&p_struct->adv_handle);
    SER_PUSH_uint16(&p_struct->adv_data.adv_data.len);
    SER_PUSH_uint16(&p_struct->adv_data.scan_rsp_data.len);
#endif

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_connected_t_dec(uint8_t const * const p_buf,
                                     uint32_t              buf_len,
                                     uint32_t * const      p_index,
                                     void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_connected_t);

    SER_PULL_FIELD(&p_struct->peer_addr, ble_gap_addr_t_dec);
    SER_PULL_uint8(&p_struct->role);
    SER_PULL_FIELD(&p_struct->conn_params, ble_gap_conn_params_t_dec);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
    SER_PULL_uint8(&p_struct->adv_handle);
    SER_PULL_uint16(&p_struct->adv_data.adv_data.len);
    SER_PULL_uint16(&p_struct->adv_data.scan_rsp_data.len);
#endif

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_sec_params_t_enc(void const * const p_void_struct,
                                  uint8_t * const    p_buf,
                                  uint32_t           buf_len,
                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_sec_params_t);

    uint8_t ser_data = (p_struct->bond      & 0x01)
                       | ((p_struct->mitm     & 0x01) << 1)
                       | ((p_struct->lesc     & 0x01) << 2)
                       | ((p_struct->keypress & 0x01) << 3)
                       | ((p_struct->io_caps  & 0x07) << 4)
                       | ((p_struct->oob      & 0x01) << 7);
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint8(&p_struct->min_key_size);
    SER_PUSH_uint8(&p_struct->max_key_size);
    SER_PUSH_FIELD(&p_struct->kdist_own, ble_gap_sec_kdist_t_enc);
    SER_PUSH_FIELD(&p_struct->kdist_peer, ble_gap_sec_kdist_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_sec_params_t_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_sec_params_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    SER_PULL_uint8(&p_struct->min_key_size);
    SER_PULL_uint8(&p_struct->max_key_size);
    SER_PULL_FIELD(&p_struct->kdist_own, ble_gap_sec_kdist_t_dec);
    SER_PULL_FIELD(&p_struct->kdist_peer, ble_gap_sec_kdist_t_dec);
    p_struct->bond     = ser_data & 0x01;
    p_struct->mitm     = (ser_data >> 1) & 0x01;
    p_struct->lesc     = (ser_data >> 2) & 0x01;
    p_struct->keypress = (ser_data >> 3) & 0x01;
    p_struct->io_caps  = (ser_data >> 4) & 0x07;
    p_struct->oob      = (ser_data >> 7) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_sec_params_request_t_enc(void const * const p_void_struct,
                                              uint8_t * const    p_buf,
                                              uint32_t           buf_len,
                                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_sec_params_request_t);
    SER_PUSH_FIELD(&(p_struct->peer_params), ble_gap_sec_params_t_enc);
    SER_STRUCT_ENC_END;
}

 uint32_t ble_gap_evt_sec_params_request_t_dec(uint8_t const * const p_buf,
                                               uint32_t              buf_len,
                                               uint32_t * const      p_index,
                                               void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_sec_params_request_t);
    SER_PULL_FIELD(&(p_struct->peer_params), ble_gap_sec_params_t_dec);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_conn_param_update_t_enc(void const * const p_void_struct,
                                             uint8_t * const    p_buf,
                                             uint32_t           buf_len,
                                             uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_conn_param_update_t);
    SER_PUSH_FIELD(&(p_struct->conn_params), ble_gap_conn_params_t_enc);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_conn_param_update_t_dec(uint8_t const * const p_buf,
                                             uint32_t              buf_len,
                                             uint32_t * const      p_index,
                                             void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_conn_param_update_t);
    SER_PULL_FIELD(&(p_struct->conn_params), ble_gap_conn_params_t_dec);
    SER_STRUCT_DEC_END;
}

#ifndef S112
uint32_t ble_gap_evt_conn_param_update_request_t_enc(void const * const p_void_struct,
                                                     uint8_t * const    p_buf,
                                                     uint32_t           buf_len,
                                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_conn_param_update_request_t);
    SER_PUSH_FIELD(&(p_struct->conn_params), ble_gap_conn_params_t_enc);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_conn_param_update_request_t_dec(uint8_t const * const p_buf,
                                             uint32_t              buf_len,
                                             uint32_t * const      p_index,
                                             void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_conn_param_update_request_t);
    SER_PULL_FIELD(&(p_struct->conn_params), ble_gap_conn_params_t_dec);
    SER_STRUCT_DEC_END;
}
#endif //!S112

uint32_t ble_gap_conn_params_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_conn_params_t);

    SER_PUSH_uint16(&p_struct->min_conn_interval);
    SER_PUSH_uint16(&p_struct->max_conn_interval);
    SER_PUSH_uint16(&p_struct->slave_latency);
    SER_PUSH_uint16(&p_struct->conn_sup_timeout);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_conn_params_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_conn_params_t);

    SER_PULL_uint16(&p_struct->min_conn_interval);
    SER_PULL_uint16(&p_struct->max_conn_interval);
    SER_PULL_uint16(&p_struct->slave_latency);
    SER_PULL_uint16(&p_struct->conn_sup_timeout);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_disconnected_t_enc(void const * const p_void_struct,
                                        uint8_t * const    p_buf,
                                        uint32_t           buf_len,
                                        uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_disconnected_t);
    SER_PUSH_uint8(&p_struct->reason);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_disconnected_t_dec(uint8_t const * const p_buf,
                                        uint32_t              buf_len,
                                        uint32_t * const      p_index,
                                        void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_disconnected_t);
    SER_PULL_uint8(&p_struct->reason);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_master_id_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_master_id_t);
    SER_PUSH_uint16(&p_struct->ediv);
    SER_PUSH_uint8array(p_struct->rand, BLE_GAP_SEC_RAND_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_master_id_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_master_id_t);
    SER_PULL_uint16(&p_struct->ediv);
    SER_PULL_uint8array(p_struct->rand, BLE_GAP_SEC_RAND_LEN);
    SER_STRUCT_DEC_END;
}

#ifndef S112
uint32_t ble_gap_scan_params_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_scan_params_t);
    uint8_t ser_data;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
    ser_data = (p_struct->active & 0x01)
             | ((p_struct->use_whitelist & 0x01) << 1)
             | ((p_struct->adv_dir_report & 0x01) << 2);
    SER_PUSH_uint8(&ser_data);
#else
    ser_data =
            ((p_struct->extended & 0x01)               << 0) |
            ((p_struct->report_incomplete_evts & 0x01) << 1) |
            ((p_struct->active & 0x01)                 << 2) |
            ((p_struct->filter_policy & 0x03)          << 3);
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint8(&p_struct->scan_phys);
    SER_PUSH_buf(p_struct->channel_mask, 5);
#endif
    SER_PUSH_uint16(&p_struct->interval);
    SER_PUSH_uint16(&p_struct->window);
    SER_PUSH_uint16(&p_struct->timeout);

    SER_STRUCT_ENC_END;
}
uint32_t ble_gap_scan_params_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_scan_params_t);

    uint8_t ser_data;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
    SER_PULL_uint8(&ser_data);
    p_struct->active         = ser_data & 0x01;
    p_struct->use_whitelist  = (ser_data >> 1) & 0x01;
    p_struct->adv_dir_report = (ser_data >> 2) & 0x01;
#else
    SER_PULL_uint8(&ser_data);
    p_struct->extended               = ser_data & 0x01;
    p_struct->report_incomplete_evts = (ser_data >> 1) & 0x01;
    p_struct->active                 = (ser_data >> 2) & 0x01;
    p_struct->filter_policy          = (ser_data >> 3) & 0x03;

    SER_PULL_uint8(&p_struct->scan_phys);
    uint8_t * p_channel_mask = (uint8_t *)p_struct->channel_mask;
    SER_PULL_buf(&p_channel_mask, 5, 5);
#endif
    SER_PULL_uint16(&p_struct->interval);
    SER_PULL_uint16(&p_struct->window);
    SER_PULL_uint16(&p_struct->timeout);

    SER_STRUCT_DEC_END;
}
#endif //!S112

uint32_t ble_gap_enc_key_t_enc(void const * const p_void_struct,
                               uint8_t * const    p_buf,
                               uint32_t           buf_len,
                               uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_enc_key_t);

    SER_PUSH_FIELD(&p_struct->enc_info, ble_gap_enc_info_t_enc);
    SER_PUSH_FIELD(&p_struct->master_id, ble_gap_master_id_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_enc_key_t_dec(uint8_t const * const p_buf,
                               uint32_t              buf_len,
                               uint32_t * const      p_index,
                               void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_enc_key_t);

    SER_PULL_FIELD(&p_struct->enc_info, ble_gap_enc_info_t_dec);
    SER_PULL_FIELD(&p_struct->master_id, ble_gap_master_id_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_id_key_t_enc(void const * const p_void_struct,
                              uint8_t * const    p_buf,
                              uint32_t           buf_len,
                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_id_key_t);

    SER_PUSH_FIELD(&p_struct->id_info, ble_gap_irk_t_enc);
    SER_PUSH_FIELD(&p_struct->id_addr_info, ble_gap_addr_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_id_key_t_dec(uint8_t const * const p_buf,
                              uint32_t              buf_len,
                              uint32_t * const      p_index,
                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_id_key_t);

    SER_PULL_FIELD(&p_struct->id_info, ble_gap_irk_t_dec);
    SER_PULL_FIELD(&p_struct->id_addr_info, ble_gap_addr_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_sec_keyset_t_enc(void const * const p_void_struct,
                                  uint8_t * const    p_buf,
                                  uint32_t           buf_len,
                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_sec_keyset_t);

    SER_PUSH_FIELD(&p_struct->keys_own, ble_gap_sec_keys_t_enc);
    SER_PUSH_FIELD(&p_struct->keys_peer, ble_gap_sec_keys_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_sec_keyset_t_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_sec_keyset_t);

    SER_PULL_FIELD(&p_struct->keys_own, ble_gap_sec_keys_t_dec);
    SER_PULL_FIELD(&p_struct->keys_peer, ble_gap_sec_keys_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_sec_request_t_enc(void const * const p_void_struct,
                                       uint8_t * const    p_buf,
                                       uint32_t           buf_len,
                                       uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_sec_request_t);

    uint8_t ser_data = (p_struct->bond & 0x01)
                       | ((p_struct->mitm & 0x01) << 1)
                       | ((p_struct->lesc & 0x01) << 2)
                       | ((p_struct->keypress & 0x01) << 3);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_sec_request_t_dec(uint8_t const * const p_buf,
                                       uint32_t              buf_len,
                                       uint32_t * const      p_index,
                                       void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_sec_request_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->bond = ser_data & 0x01;
    p_struct->mitm = (ser_data >> 1) & 0x01;
    p_struct->lesc = (ser_data >> 2) & 0x01;
    p_struct->keypress = (ser_data >> 3) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_sec_kdist_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_sec_kdist_t);

    uint8_t ser_data =   (p_struct->enc  & 0x01)
                       | (p_struct->id   & 0x01) << 1
                       | (p_struct->sign & 0x01) << 2
                       | (p_struct->link & 0x01) << 3;
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_sec_kdist_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_sec_kdist_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->enc   = ser_data & 0x01;
    p_struct->id    = (ser_data >> 1) & 0x01;
    p_struct->sign  = (ser_data >> 2) & 0x01;
    p_struct->link  = (ser_data >> 3) & 0x01;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_opt_ch_map_t_enc(void const * const p_void_struct,
                                  uint8_t * const    p_buf,
                                  uint32_t           buf_len,
                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_ch_map_t);

    SER_PUSH_uint16(&p_struct->conn_handle);
    SER_PUSH_uint8array(p_struct->ch_map, 5);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_ch_map_t_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_ch_map_t);

    SER_PULL_uint16(&p_struct->conn_handle);
    SER_PULL_uint8array(p_struct->ch_map, 5);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_opt_local_conn_latency_t_enc(void const * const p_void_struct,
                                              uint8_t * const    p_buf,
                                              uint32_t           buf_len,
                                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_local_conn_latency_t);

    SER_PUSH_uint16(&p_struct->conn_handle);
    SER_PUSH_uint16(&p_struct->requested_latency);
    SER_PUSH_COND(p_struct->p_actual_latency, uint16_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_local_conn_latency_t_dec(uint8_t const * const p_buf,
                                              uint32_t              buf_len,
                                              uint32_t * const      p_index,
                                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_local_conn_latency_t);

    SER_PULL_uint16(&p_struct->conn_handle);
    SER_PULL_uint16(&p_struct->requested_latency);
    SER_PULL_COND(&p_struct->p_actual_latency, uint16_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_opt_passkey_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_passkey_t);
    SER_PUSH_buf(p_struct->p_passkey, BLE_GAP_PASSKEY_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_passkey_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_passkey_t);
    SER_PULL_buf((uint8_t**)&p_struct->p_passkey, BLE_GAP_PASSKEY_LEN, BLE_GAP_PASSKEY_LEN);
    SER_STRUCT_DEC_END;
}
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
uint32_t ble_gap_opt_scan_req_report_t_enc(void const * const p_void_struct,
                                           uint8_t * const    p_buf,
                                           uint32_t           buf_len,
                                           uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_scan_req_report_t);

    uint8_t ser_data = p_struct->enable & 0x01;
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_scan_req_report_t_dec(uint8_t const * const p_buf,
                                           uint32_t              buf_len,
                                           uint32_t * const      p_index,
                                           void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_scan_req_report_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->enable = ser_data & 0x01;

    SER_STRUCT_DEC_END;
}
#endif

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gap_opt_compat_mode_t_enc(void const * const p_void_struct,
                                       uint8_t * const    p_buf,
                                       uint32_t           buf_len,
                                       uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_compat_mode_t);

    uint8_t ser_data = p_struct->mode_1_enable & 0x01;
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_compat_mode_t_dec(uint8_t const * const p_buf,
                                       uint32_t              buf_len,
                                       uint32_t * const      p_index,
                                       void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_compat_mode_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->mode_1_enable = ser_data & 0x01;

    SER_STRUCT_DEC_END;
}
#endif

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
uint32_t ble_gap_adv_ch_mask_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_adv_ch_mask_t);

    uint8_t ser_data = (p_struct->ch_37_off & 0x01)
                       | ((p_struct->ch_38_off & 0x01) << 1)
                       | ((p_struct->ch_39_off & 0x01) << 2);
    SER_PUSH_uint8(&ser_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_adv_ch_mask_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_adv_ch_mask_t);

    uint8_t ser_data;
    SER_PULL_uint8(&ser_data);
    p_struct->ch_37_off = ser_data & 0x01;
    p_struct->ch_38_off = (ser_data >> 1) & 0x01;
    p_struct->ch_39_off = (ser_data >> 2) & 0x01;

    SER_STRUCT_DEC_END;
}
#endif

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gap_enable_params_t_enc(void const * const p_void_struct,
                                     uint8_t * const    p_buf,
                                     uint32_t           buf_len,
                                     uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_enable_params_t);

    SER_PUSH_uint8(&p_struct->periph_conn_count);
    SER_PUSH_uint8(&p_struct->central_conn_count);
    SER_PUSH_uint8(&p_struct->central_sec_count);
    SER_PUSH_COND(p_struct->p_device_name, ble_gap_device_name_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_enable_params_t_dec(uint8_t const * const p_buf,
                                     uint32_t              buf_len,
                                     uint32_t * const      p_index,
                                     void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_enable_params_t);

    SER_PULL_uint8(&p_struct->periph_conn_count);
    SER_PULL_uint8(&p_struct->central_conn_count);
    SER_PULL_uint8(&p_struct->central_sec_count);
    SER_PULL_COND(&p_struct->p_device_name, ble_gap_device_name_t_dec);

    SER_STRUCT_DEC_END;
}
#endif

uint32_t ble_gap_lesc_p256_pk_t_enc(void const * const p_void_struct,
                               uint8_t * const    p_buf,
                               uint32_t           buf_len,
                               uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_lesc_p256_pk_t);
    SER_PUSH_uint8array(p_struct->pk, BLE_GAP_LESC_P256_PK_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_lesc_p256_pk_t_dec(uint8_t const * const p_buf,
                               uint32_t              buf_len,
                               uint32_t * const      p_index,
                               void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_lesc_p256_pk_t);
    SER_PULL_uint8array(p_struct->pk, BLE_GAP_LESC_P256_PK_LEN);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_lesc_dhkey_t_enc(void const * const p_void_struct,
                               uint8_t * const    p_buf,
                               uint32_t           buf_len,
                               uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_lesc_dhkey_t);
    SER_PUSH_uint8array(p_struct->key, BLE_GAP_LESC_DHKEY_LEN);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_lesc_dhkey_t_dec(uint8_t const * const p_buf,
                               uint32_t              buf_len,
                               uint32_t * const      p_index,
                               void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_lesc_dhkey_t);
    SER_PULL_uint8array(p_struct->key, BLE_GAP_LESC_DHKEY_LEN);
    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_lesc_oob_data_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_lesc_oob_data_t);

    SER_PUSH_FIELD(&p_struct->addr, ble_gap_addr_t_enc);
    SER_PUSH_uint8array(p_struct->r, BLE_GAP_SEC_KEY_LEN);
    SER_PUSH_uint8array(p_struct->c, BLE_GAP_SEC_KEY_LEN);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_lesc_oob_data_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_lesc_oob_data_t);

    SER_PULL_FIELD(&p_struct->addr, ble_gap_addr_t_dec);
    SER_PULL_uint8array(p_struct->r, BLE_GAP_SEC_KEY_LEN);
    SER_PULL_uint8array(p_struct->c, BLE_GAP_SEC_KEY_LEN);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_adv_params_t_enc(void const * const p_void_struct,
                                 uint8_t * const    p_buf,
                                 uint32_t           buf_len,
                                 uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_adv_params_t);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
    SER_PUSH_uint8(&p_struct->type);
    SER_PUSH_COND(p_struct->p_peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_uint8(&p_struct->fp);
    SER_PUSH_uint16(&p_struct->interval);
    SER_PUSH_uint16(&p_struct->timeout);
    SER_PUSH_FIELD(&p_struct->channel_mask, ble_gap_adv_ch_mask_t_enc);
#else
    SER_PUSH_FIELD(&p_struct->properties, ble_gap_adv_properties_t_enc);
    SER_PUSH_COND(p_struct->p_peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_uint32(&p_struct->interval);
    SER_PUSH_uint16(&p_struct->duration);
    SER_PUSH_uint8(&p_struct->max_adv_evts);
    SER_PUSH_buf(p_struct->channel_mask, 5);
    SER_PUSH_uint8(&p_struct->filter_policy);
    SER_PUSH_uint8(&p_struct->primary_phy);
    SER_PUSH_uint8(&p_struct->secondary_phy);
    uint8_t temp = p_struct->set_id | (p_struct->scan_req_notification << 4);
    SER_PUSH_uint8(&temp);

#endif
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_adv_params_t_dec(uint8_t const * const p_buf,
                                 uint32_t              buf_len,
                                 uint32_t * const      p_index,
                                 void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_adv_params_t);

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
    SER_PULL_uint8(&p_struct->type);
    SER_PULL_COND(&p_struct->p_peer_addr, ble_gap_addr_t_dec);
    SER_PULL_uint8(&p_struct->fp);
    SER_PULL_uint16(&p_struct->interval);
    SER_PULL_uint16(&p_struct->timeout);
    SER_PULL_FIELD(&p_struct->channel_mask, ble_gap_adv_ch_mask_t_dec);
#else
    SER_PULL_FIELD(&p_struct->properties, ble_gap_adv_properties_t_dec);
    SER_PULL_COND(&p_struct->p_peer_addr, ble_gap_addr_t_dec);
    SER_PULL_uint32(&p_struct->interval);
    SER_PULL_uint16(&p_struct->duration);
    SER_PULL_uint8(&p_struct->max_adv_evts);
    uint8_t * p_channel_mask = p_struct->channel_mask;
    SER_PULL_buf((uint8_t **)&p_channel_mask, 5, 5);
    SER_PULL_uint8(&p_struct->filter_policy);
    SER_PULL_uint8(&p_struct->primary_phy);
    SER_PULL_uint8(&p_struct->secondary_phy);

    uint8_t temp;
    SER_PULL_uint8(&temp);
    p_struct->set_id = temp & 0x0F;
    p_struct->scan_req_notification = (temp & 0x10) ? 1 : 0;

#endif

    SER_STRUCT_DEC_END;
}
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gap_opt_ext_len_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_ext_len_t);
    SER_PUSH_uint8(&p_struct->rxtx_max_pdu_payload_size);
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_ext_len_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_ext_len_t);
    SER_PULL_uint8(&p_struct->rxtx_max_pdu_payload_size);
    SER_STRUCT_DEC_END;
}
#endif
uint32_t ble_gap_opt_auth_payload_timeout_t_enc(void const * const p_void_struct,
                                                uint8_t * const    p_buf,
                                                uint32_t           buf_len,
                                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_auth_payload_timeout_t);

    SER_PUSH_uint16(&p_struct->conn_handle);
    SER_PUSH_uint16(&p_struct->auth_payload_timeout);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_auth_payload_timeout_t_dec(uint8_t const * const p_buf,
                                                uint32_t              buf_len,
                                                uint32_t * const      p_index,
                                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_auth_payload_timeout_t);

    SER_PULL_uint16(&p_struct->conn_handle);
    SER_PULL_uint16(&p_struct->auth_payload_timeout);

    SER_STRUCT_DEC_END;
}

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gap_device_name_t_enc
#else
uint32_t ble_gap_cfg_device_name_t_enc
#endif
                                  (void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)

{
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
    SER_STRUCT_ENC_BEGIN(ble_gap_device_name_t);
#else
    SER_STRUCT_ENC_BEGIN(ble_gap_cfg_device_name_t);
#endif
    /* serializer does not support attributes on stack */
    if (p_struct->vloc != BLE_GATTS_VLOC_STACK)
    {
        err_code = NRF_ERROR_INVALID_PARAM;
    }

    SER_PUSH_FIELD(&p_struct->write_perm, ble_gap_conn_sec_mode_t_enc);

    uint8_t ser_data = p_struct->vloc & 0x03;
    SER_PUSH_uint8(&ser_data);
    SER_PUSH_uint16(&p_struct->current_len);
    SER_PUSH_uint16(&p_struct->max_len);
    SER_PUSH_buf(p_struct->p_value, p_struct->current_len);

    SER_STRUCT_ENC_END;
}

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_gap_device_name_t_dec
#else
uint32_t ble_gap_cfg_device_name_t_dec
#endif
                                  (uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
    SER_STRUCT_DEC_BEGIN(ble_gap_device_name_t);
#else
    SER_STRUCT_DEC_BEGIN(ble_gap_cfg_device_name_t);
#endif

    uint16_t value_max_len = p_struct->max_len;
    uint8_t  ser_data;
    SER_PULL_FIELD(&p_struct->write_perm, ble_gap_conn_sec_mode_t_dec);
    SER_PULL_uint8(&ser_data);
    p_struct->vloc = ser_data & 0x03;
    SER_PULL_uint16(&p_struct->current_len);
    SER_PULL_uint16(&p_struct->max_len);
    SER_PULL_buf(&p_struct->p_value,value_max_len, p_struct->current_len);

    SER_STRUCT_DEC_END;
}



uint32_t ble_gap_privacy_params_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_privacy_params_t);

    SER_PUSH_uint8(&p_struct->privacy_mode);
    SER_PUSH_uint8(&p_struct->private_addr_type);
    SER_PUSH_uint16(&p_struct->private_addr_cycle_s);
    SER_PUSH_COND(p_struct->p_device_irk, ble_gap_irk_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_privacy_params_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_privacy_params_t);

    SER_PULL_uint8(&p_struct->privacy_mode);
    SER_PULL_uint8(&p_struct->private_addr_type);
    SER_PULL_uint16(&p_struct->private_addr_cycle_s);
    SER_PULL_COND(&p_struct->p_device_irk, ble_gap_irk_t_dec);

    SER_STRUCT_DEC_END;
}




#if NRF_SD_BLE_API_VERSION >= 4
#ifndef S112
uint32_t ble_gap_opt_compat_mode_1_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_compat_mode_1_t);

    uint8_t enable = p_struct->enable;
    SER_PUSH_uint8(&enable);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_compat_mode_1_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_compat_mode_1_t);

    uint8_t enable;
    SER_PULL_uint8(&enable);
    p_struct->enable = enable;

    SER_STRUCT_DEC_END;
}
#endif //!S112

uint32_t ble_gap_opt_slave_latency_disable_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_slave_latency_disable_t);

    SER_PUSH_uint16(&p_struct->conn_handle);
    uint8_t disable = p_struct->disable;
    SER_PUSH_uint8(&disable);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_slave_latency_disable_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_slave_latency_disable_t);

    SER_PULL_uint16(&p_struct->conn_handle);
    uint8_t disable;
    SER_PULL_uint8(&disable);
    p_struct->disable = disable;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_conn_cfg_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_conn_cfg_t);

    SER_PUSH_uint8(&p_struct->conn_count);
    SER_PUSH_uint16(&p_struct->event_length);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_conn_cfg_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_conn_cfg_t);

    SER_PULL_uint8(&p_struct->conn_count);
    SER_PULL_uint16(&p_struct->event_length);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_cfg_role_count_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_cfg_role_count_t);

    SER_PUSH_uint8(&p_struct->periph_role_count);
#ifndef S112
    SER_PUSH_uint8(&p_struct->central_role_count);
    SER_PUSH_uint8(&p_struct->central_sec_count);
#endif //!S112
#if NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&p_struct->adv_set_count);
#ifndef S112
    uint32_t temp = p_struct->qos_channel_survey_role_available;
    SER_PUSH_uint8(&temp);
#endif //!S112
#endif
    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_cfg_role_count_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_cfg_role_count_t);

    SER_PULL_uint8(&p_struct->periph_role_count);
#ifndef S112
    SER_PULL_uint8(&p_struct->central_role_count);
    SER_PULL_uint8(&p_struct->central_sec_count);
#endif //!S112
#if NRF_SD_BLE_API_VERSION > 5
    SER_PULL_uint8(&p_struct->adv_set_count);
#ifndef S112
    uint8_t temp;
    SER_PULL_uint8(&temp);
    p_struct->qos_channel_survey_role_available = temp;
#endif //!S112
#endif
    SER_STRUCT_DEC_END;
}

#ifndef S112
uint32_t ble_gap_data_length_params_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_data_length_params_t);

    SER_PUSH_uint16(&p_struct->max_tx_octets);
    SER_PUSH_uint16(&p_struct->max_rx_octets);
    SER_PUSH_uint16(&p_struct->max_tx_time_us);
    SER_PUSH_uint16(&p_struct->max_rx_time_us);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_data_length_params_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_data_length_params_t);

    SER_PULL_uint16(&p_struct->max_tx_octets);
    SER_PULL_uint16(&p_struct->max_rx_octets);
    SER_PULL_uint16(&p_struct->max_tx_time_us);
    SER_PULL_uint16(&p_struct->max_rx_time_us);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_data_length_limitation_t_enc(void const * const p_void_struct,
                                              uint8_t * const    p_buf,
                                              uint32_t           buf_len,
                                              uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_data_length_limitation_t);

    SER_PUSH_uint16(&p_struct->tx_payload_limited_octets);
    SER_PUSH_uint16(&p_struct->rx_payload_limited_octets);
    SER_PUSH_uint16(&p_struct->tx_rx_time_limited_us);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_data_length_limitation_t_dec(uint8_t const * const p_buf,
                                              uint32_t              buf_len,
                                              uint32_t * const      p_index,
                                              void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_data_length_limitation_t);

    SER_PULL_uint16(&p_struct->tx_payload_limited_octets);
    SER_PULL_uint16(&p_struct->rx_payload_limited_octets);
    SER_PULL_uint16(&p_struct->tx_rx_time_limited_us);

    SER_STRUCT_DEC_END;
}
#endif //!S112
#endif

#if NRF_SD_BLE_API_VERSION == 4

uint32_t ble_gap_opt_compat_mode_2_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_opt_compat_mode_2_t);

    uint8_t enable = p_struct->enable;
    SER_PUSH_uint8(&enable);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_opt_compat_mode_2_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_opt_compat_mode_2_t);

    uint8_t enable;
    SER_PULL_uint8(&enable);
    p_struct->enable = enable;

    SER_STRUCT_DEC_END;
}

#endif

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_gap_phys_t_enc(void const * const p_void_struct,
                            uint8_t * const    p_buf,
                            uint32_t           buf_len,
                            uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_phys_t);

    SER_PUSH_uint8(&p_struct->tx_phys);
    SER_PUSH_uint8(&p_struct->rx_phys);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_phys_t_dec(uint8_t const * const p_buf,
                            uint32_t              buf_len,
                            uint32_t * const      p_index,
                            void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_phys_t);

    SER_PULL_uint8(&p_struct->tx_phys);
    SER_PULL_uint8(&p_struct->rx_phys);

    SER_STRUCT_DEC_END;
}
#endif

#if NRF_SD_BLE_API_VERSION > 5
uint32_t ble_gap_adv_properties_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_adv_properties_t);

    SER_PUSH_uint8(&p_struct->type);
    uint8_t temp = p_struct->anonymous | (p_struct->include_tx_power << 1);
    SER_PUSH_uint8(&temp);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_adv_properties_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_adv_properties_t);

    SER_PULL_uint8(&p_struct->type);
    uint8_t temp;
    SER_PULL_uint8(&temp);
    p_struct->anonymous        = temp & 0x01;
    p_struct->include_tx_power = (temp & 0x02) ? 1 : 0;

    SER_STRUCT_DEC_END;
}

#ifndef S112
uint32_t ble_gap_adv_report_type_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_adv_report_type_t);

    uint16_t temp =
            (p_struct->connectable   << 0) |
            (p_struct->scannable     << 1) |
            (p_struct->directed      << 2) |
            (p_struct->scan_response << 3) |
            (p_struct->extended_pdu  << 4) |
            (p_struct->status        << 5) |
            (p_struct->reserved      << 7);
    SER_PUSH_uint16(&temp);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_adv_report_type_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_adv_report_type_t);

    uint16_t temp;
    SER_PULL_uint16(&temp);
    p_struct->connectable   =  (temp >> 0) & 0x01;
    p_struct->scannable     =  (temp >> 1) & 0x01;
    p_struct->directed      =  (temp >> 2) & 0x01;
    p_struct->scan_response =  (temp >> 3) & 0x01;
    p_struct->extended_pdu  =  (temp >> 4) & 0x01;
    p_struct->status        =  (temp >> 5) & 0x03;
    p_struct->reserved      =  (temp >> 7) & 0x1FF;

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_aux_pointer_t_enc(void const * const p_void_struct,
                                   uint8_t * const    p_buf,
                                   uint32_t           buf_len,
                                   uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_aux_pointer_t);

    SER_PUSH_uint16(&p_struct->aux_offset);
    SER_PUSH_uint8(&p_struct->aux_phy);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_aux_pointer_t_dec(uint8_t const * const p_buf,
                                   uint32_t              buf_len,
                                   uint32_t * const      p_index,
                                   void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_aux_pointer_t);

    SER_PULL_uint16(&p_struct->aux_offset);
    SER_PULL_uint8(&p_struct->aux_phy);

    SER_STRUCT_DEC_END;
}
#endif //!S112

uint32_t ble_gap_adv_data_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_adv_data_t);

    SER_PUSH_FIELD(&p_struct->adv_data, ble_data_t_enc);
    SER_PUSH_FIELD(&p_struct->scan_rsp_data, ble_data_t_enc);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_adv_data_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_adv_data_t);

    SER_PULL_FIELD(&p_struct->adv_data, ble_data_t_dec);
    SER_PULL_FIELD(&p_struct->scan_rsp_data, ble_data_t_dec);

    SER_STRUCT_DEC_END;
}

uint32_t ble_gap_evt_adv_set_terminated_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_gap_evt_adv_set_terminated_t);

    SER_PUSH_uint8(&p_struct->reason);
    SER_PUSH_uint8(&p_struct->adv_handle);
    SER_PUSH_uint8(&p_struct->num_completed_adv_events);
    SER_PUSH_uint16(&p_struct->adv_data.adv_data.len);
    SER_PUSH_COND(&p_struct->adv_data.adv_data.p_data, NULL);
    SER_PUSH_uint16(&p_struct->adv_data.scan_rsp_data.len);
    SER_PUSH_COND(&p_struct->adv_data.scan_rsp_data.p_data, NULL);

    SER_STRUCT_ENC_END;
}

uint32_t ble_gap_evt_adv_set_terminated_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_gap_evt_adv_set_terminated_t);

    SER_PULL_uint8(&p_struct->reason);
    SER_PULL_uint8(&p_struct->adv_handle);
    SER_PULL_uint8(&p_struct->num_completed_adv_events);
    SER_PULL_uint16(&p_struct->adv_data.adv_data.len);
    SER_PULL_COND(&p_struct->adv_data.adv_data.p_data, NULL);
    SER_PULL_uint16(&p_struct->adv_data.scan_rsp_data.len);
    SER_PULL_COND(&p_struct->adv_data.scan_rsp_data.p_data, NULL);

    SER_STRUCT_DEC_END;
}
#endif
