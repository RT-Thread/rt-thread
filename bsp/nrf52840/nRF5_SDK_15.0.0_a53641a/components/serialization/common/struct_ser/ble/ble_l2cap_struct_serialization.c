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
#include "ble_l2cap_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_serialization.h"
#include "app_util.h"
#include "cond_field_serialization.h"
#include <string.h>

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_l2cap_header_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_l2cap_header_t);

    SER_PUSH_uint16(&p_struct->len);
    SER_PUSH_uint16(&p_struct->cid);

    SER_STRUCT_ENC_END;
}

uint32_t ble_l2cap_header_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_l2cap_header_t);

    SER_PULL_uint16(&p_struct->len);
    SER_PULL_uint16(&p_struct->cid);

    SER_STRUCT_DEC_END;
}

uint32_t ble_l2cap_evt_rx_t_enc(void const * const p_void_struct,
                                uint8_t * const    p_buf,
                                uint32_t           buf_len,
                                uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_l2cap_evt_rx_t);

    SER_PUSH_FIELD(&p_struct->header, ble_l2cap_header_t_enc);
    SER_PUSH_uint8array(p_struct->data, p_struct->header.len);

    SER_STRUCT_ENC_END;
}

uint32_t ble_l2cap_evt_rx_t_dec(uint8_t const * const p_buf,
                                uint32_t              buf_len,
                                uint32_t * const      p_index,
                                uint32_t * const      p_ext_len,
                                void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_l2cap_evt_rx_t);

    SER_PULL_FIELD(&p_struct->header, ble_l2cap_header_t_dec);

    uint32_t data_len = (SUB1(p_struct->header.len));
    SER_ASSERT_LENGTH_LEQ(data_len, *p_ext_len);

    SER_PULL_uint8array(p_struct->data, p_struct->header.len);

    *p_ext_len = data_len;
    SER_STRUCT_DEC_END;
}
#endif

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_l2cap_conn_cfg_t_enc(void const * const p_void_struct,
                                  uint8_t * const    p_buf,
                                  uint32_t           buf_len,
                                  uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_l2cap_conn_cfg_t);

    SER_PUSH_uint16(&p_struct->rx_mps);
    SER_PUSH_uint16(&p_struct->tx_mps);
    SER_PUSH_uint8(&p_struct->rx_queue_size);
    SER_PUSH_uint8(&p_struct->tx_queue_size);
    SER_PUSH_uint8(&p_struct->ch_count);

    SER_STRUCT_ENC_END;
}

uint32_t ble_l2cap_conn_cfg_t_dec(uint8_t const * const p_buf,
                                  uint32_t              buf_len,
                                  uint32_t * const      p_index,
                                  void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_l2cap_conn_cfg_t);

    SER_PULL_uint16(&p_struct->rx_mps);
    SER_PULL_uint16(&p_struct->tx_mps);
    SER_PULL_uint8(&p_struct->rx_queue_size);
    SER_PULL_uint8(&p_struct->tx_queue_size);
    SER_PULL_uint8(&p_struct->ch_count);

    SER_STRUCT_DEC_END;
}

uint32_t ble_l2cap_ch_rx_params_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_l2cap_ch_rx_params_t);

    SER_PUSH_uint16(&p_struct->rx_mtu);
    SER_PUSH_uint16(&p_struct->rx_mps);
    SER_PUSH_uint16(&p_struct->sdu_buf.len);
    SER_PUSH_uint32(&p_struct->sdu_buf.p_data);

    SER_STRUCT_ENC_END;
}

uint32_t ble_l2cap_ch_rx_params_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_l2cap_ch_rx_params_t);

    SER_PULL_uint16(&p_struct->rx_mtu);
    SER_PULL_uint16(&p_struct->rx_mps);
    SER_PULL_uint16(&p_struct->sdu_buf.len);
    SER_PULL_uint32(&p_struct->sdu_buf.p_data);

    SER_STRUCT_DEC_END;
}

uint32_t ble_l2cap_ch_setup_params_t_enc(void const * const p_void_struct,
                                         uint8_t * const    p_buf,
                                         uint32_t           buf_len,
                                         uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_l2cap_ch_setup_params_t);

    SER_PUSH_FIELD(&p_struct->rx_params, ble_l2cap_ch_rx_params_t_enc);
    SER_PUSH_uint16(&p_struct->le_psm);
    SER_PUSH_uint16(&p_struct->status);

    SER_STRUCT_ENC_END;
}

uint32_t ble_l2cap_ch_setup_params_t_dec(uint8_t const * const p_buf,
                                         uint32_t              buf_len,
                                         uint32_t * const      p_index,
                                         void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_l2cap_ch_setup_params_t);

    SER_PULL_FIELD(&p_struct->rx_params, ble_l2cap_ch_rx_params_t_dec);
    SER_PULL_uint16(&p_struct->le_psm);
    SER_PULL_uint16(&p_struct->status);

    SER_STRUCT_DEC_END;
}

uint32_t ble_l2cap_ch_tx_params_t_enc(void const * const p_void_struct,
                                      uint8_t * const    p_buf,
                                      uint32_t           buf_len,
                                      uint32_t * const   p_index)
{
    SER_STRUCT_ENC_BEGIN(ble_l2cap_ch_tx_params_t);

    SER_PUSH_uint16(&p_struct->tx_mtu);
    SER_PUSH_uint16(&p_struct->peer_mps);
    SER_PUSH_uint16(&p_struct->tx_mps);
    SER_PUSH_uint16(&p_struct->credits);

    SER_STRUCT_ENC_END;
}

uint32_t ble_l2cap_ch_tx_params_t_dec(uint8_t const * const p_buf,
                                      uint32_t              buf_len,
                                      uint32_t * const      p_index,
                                      void * const          p_void_struct)
{
    SER_STRUCT_DEC_BEGIN(ble_l2cap_ch_tx_params_t);

    SER_PULL_uint16(&p_struct->tx_mtu);
    SER_PULL_uint16(&p_struct->peer_mps);
    SER_PULL_uint16(&p_struct->tx_mps);
    SER_PULL_uint16(&p_struct->credits);

    SER_STRUCT_DEC_END;
}
#endif //NRF_SD_BLE_API_VERSION >= 5
