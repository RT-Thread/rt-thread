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
#include "ble_gatts_evt_conn.h"
#include "ble_serialization.h"
#include "ble_gatts_struct_serialization.h"
#include "conn_ble_user_mem.h"
#include "app_util.h"

extern sercon_ble_user_mem_t m_conn_user_mem_table[];


uint32_t ble_gatts_evt_rw_authorize_request_enc(ble_evt_t const * const p_event,
                                                uint32_t                event_len,
                                                uint8_t * const         p_buf,
                                                uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gatts_evt.params.authorize_request, ble_gatts_evt_rw_authorize_request_t_enc);

    if ((p_event->evt.gatts_evt.params.authorize_request.type == BLE_GATTS_AUTHORIZE_TYPE_WRITE) &&
       ((p_event->evt.gatts_evt.params.authorize_request.request.write.op == BLE_GATTS_OP_EXEC_WRITE_REQ_NOW) ||
        (p_event->evt.gatts_evt.params.authorize_request.request.write.op == BLE_GATTS_OP_PREP_WRITE_REQ)))
    {
        uint32_t conn_index;

        if (conn_ble_user_mem_context_find(p_event->evt.gatts_evt.conn_handle, &conn_index) != NRF_ERROR_NOT_FOUND)
        {
            err_code = len16data_enc(m_conn_user_mem_table[conn_index].mem_block.p_mem, m_conn_user_mem_table[conn_index].mem_block.len, p_buf, *p_buf_len, &index);
            SER_ASSERT(err_code == NRF_SUCCESS, err_code);
        }
    }

    SER_EVT_ENC_END;
}


uint32_t ble_gatts_evt_hvc_enc(ble_evt_t const * const p_event,
                               uint32_t                event_len,
                               uint8_t * const         p_buf,
                               uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_HVC);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gatts_evt.params.hvc, ble_gatts_evt_hvc_t_enc);

    SER_EVT_ENC_END;
}


uint32_t ble_gatts_evt_sc_confirm_enc(ble_evt_t const * const p_event,
                                      uint32_t                event_len,
                                      uint8_t * const         p_buf,
                                      uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_HVC);
    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_EVT_ENC_END;
}


uint32_t ble_gatts_evt_sys_attr_missing_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_SYS_ATTR_MISSING);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gatts_evt.params.sys_attr_missing, ble_gatts_evt_sys_attr_missing_t_enc);

    SER_EVT_ENC_END;
}


uint32_t ble_gatts_evt_timeout_enc(ble_evt_t const * const p_event,
                                   uint32_t                event_len,
                                   uint8_t * const         p_buf,
                                   uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_TIMEOUT);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gatts_evt.params.timeout, ble_gatts_evt_timeout_t_enc);

    SER_EVT_ENC_END;
}


uint32_t ble_gatts_evt_write_enc(ble_evt_t const * const p_event,
                                 uint32_t                event_len,
                                 uint8_t * const         p_buf,
                                 uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_WRITE);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gatts_evt.params.write, ble_gatts_evt_write_t_enc);

    if ((p_event->evt.gatts_evt.params.write.op == BLE_GATTS_OP_WRITE_REQ) || (p_event->evt.gatts_evt.params.write.op == BLE_GATTS_OP_EXEC_WRITE_REQ_NOW))
    {
        uint32_t conn_index;
        if (conn_ble_user_mem_context_find(p_event->evt.gatts_evt.conn_handle, &conn_index) != NRF_ERROR_NOT_FOUND)
        {
            SER_PUSH_len16data(m_conn_user_mem_table[conn_index].mem_block.p_mem, m_conn_user_mem_table[conn_index].mem_block.len);
        }
    }

    SER_EVT_ENC_END;
}


uint32_t ble_gatts_evt_exchange_mtu_request_enc(ble_evt_t const * const p_event,
                                                uint32_t                event_len,
                                                uint8_t * const         p_buf,
                                                uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gatts_evt.params.exchange_mtu_request, ble_gatts_evt_exchange_mtu_request_t_enc);

    SER_EVT_ENC_END;
}

#if NRF_SD_BLE_API_VERSION >= 4
uint32_t ble_gatts_evt_hvn_tx_complete_enc(ble_evt_t const * const p_event,
                                           uint32_t                event_len,
                                           uint8_t * const         p_buf,
                                           uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GATTS_EVT_HVN_TX_COMPLETE);

    SER_PUSH_uint16(&p_event->evt.gatts_evt.conn_handle);
    SER_PUSH_uint8(&p_event->evt.gatts_evt.params.hvn_tx_complete.count);

    SER_EVT_ENC_END;
}
#endif
