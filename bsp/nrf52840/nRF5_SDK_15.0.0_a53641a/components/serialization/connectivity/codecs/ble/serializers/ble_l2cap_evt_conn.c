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
#include "ble_l2cap_evt_conn.h"
#include <string.h>
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_l2cap_struct_serialization.h"
#include "app_util.h"
#include "conn_ble_l2cap_sdu_pool.h"

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_l2cap_evt_rx_enc(ble_evt_t const * const p_event,
                              uint32_t                event_len,
                              uint8_t * const         p_buf,
                              uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_RX);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.l2cap_evt.params.rx, ble_l2cap_evt_rx_t_enc);

    SER_EVT_ENC_END;
}
#endif

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_l2cap_evt_ch_setup_request_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_SETUP_REQUEST);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.ch_setup_request.le_psm);
    SER_PUSH_FIELD(&p_event->evt.l2cap_evt.params.ch_setup_request.tx_params, ble_l2cap_ch_tx_params_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_setup_refused_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_SETUP_REFUSED);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_uint8(&p_event->evt.l2cap_evt.params.ch_setup_refused.source);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.ch_setup_refused.status);

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_setup_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_SETUP);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_FIELD(&p_event->evt.l2cap_evt.params.ch_setup.tx_params, ble_l2cap_ch_tx_params_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_released_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_RELEASED);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_sdu_buf_released_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.ch_sdu_buf_released.sdu_buf.len);

    uint32_t * p_data = (uint32_t *)p_event->evt.l2cap_evt.params.ch_sdu_buf_released.sdu_buf.p_data;
    if (p_data)
    {
        uint32_t id = *(p_data - 1);
        conn_ble_l2cap_sdu_pool_free(p_data);
        SER_PUSH_uint32(&id);
    }

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_credit_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_CREDIT);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.credit.credits);

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_rx_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_RX);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.rx.sdu_len);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.rx.sdu_buf.len);

    uint32_t * p_data = (uint32_t *)p_event->evt.l2cap_evt.params.rx.sdu_buf.p_data;
    uint32_t id = *(p_data - 1);
    SER_PUSH_uint32(&id);
    SER_PUSH_buf(p_event->evt.l2cap_evt.params.rx.sdu_buf.p_data, p_event->evt.l2cap_evt.params.rx.sdu_buf.len);
    conn_ble_l2cap_sdu_pool_free(p_data);

    SER_EVT_ENC_END;
}

uint32_t ble_l2cap_evt_ch_tx_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_L2CAP_EVT_CH_TX);

    SER_PUSH_uint16(&p_event->evt.l2cap_evt.conn_handle);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.local_cid);
    SER_PUSH_uint16(&p_event->evt.l2cap_evt.params.tx.sdu_buf.len);

    uint32_t * p_data = (uint32_t *)p_event->evt.l2cap_evt.params.tx.sdu_buf.p_data;
    if (p_data)
    {
        uint32_t id = *(p_data - 1);
        conn_ble_l2cap_sdu_pool_free(p_data);
        SER_PUSH_uint32(&id);
    }

    SER_EVT_ENC_END;
}
#endif
