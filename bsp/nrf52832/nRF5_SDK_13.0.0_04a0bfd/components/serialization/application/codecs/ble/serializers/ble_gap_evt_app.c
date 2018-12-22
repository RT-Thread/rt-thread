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
#include "ble_gap_evt_app.h"
#include "ble_serialization.h"
#include "app_util.h"
#include "app_ble_gap_sec_keys.h"
#include "ble_gap_struct_serialization.h"
#include "cond_field_serialization.h"
#include <string.h>

extern ser_ble_gap_app_keyset_t m_app_keys_table[];


uint32_t ble_gap_evt_adv_report_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    ble_evt_t * const     p_event,
                                    uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_ADV_REPORT, gap, adv_report);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.adv_report, ble_gap_evt_adv_report_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_auth_key_request_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          ble_evt_t * const     p_event,
                                          uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_AUTH_KEY_REQUEST, gap, auth_key_request);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.gap_evt.params.auth_key_request.key_type);

    SER_EVT_DEC_END;
}


extern ser_ble_gap_app_keyset_t m_app_keys_table[];

uint32_t ble_gap_evt_auth_status_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     ble_evt_t * const     p_event,
                                     uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_AUTH_STATUS, gap, auth_status);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.auth_status, ble_gap_evt_auth_status_t_dec);

    // keyset is an extension of standard event data - used to synchronize keys at application
    uint32_t conn_index;
    err_code = app_ble_gap_sec_context_find(p_event->evt.gap_evt.conn_handle, &conn_index);
    if (err_code == NRF_SUCCESS)
    {
        SER_PULL_FIELD(&(m_app_keys_table[conn_index].keyset), ble_gap_sec_keyset_t_dec);

        err_code = app_ble_gap_sec_context_destroy(p_event->evt.gap_evt.conn_handle);
        SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    }

    SER_EVT_DEC_END;
}


uint32_t ble_gap_evt_conn_param_update_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           ble_evt_t * const     p_event,
                                           uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_CONN_PARAM_UPDATE, gap, conn_param_update);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.conn_param_update, ble_gap_evt_conn_param_update_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gap_evt_conn_param_update_request_dec(uint8_t const * const p_buf,
                                                   uint32_t              packet_len,
                                                   ble_evt_t * const     p_event,
                                                   uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST, gap, conn_param_update_request);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.conn_param_update_request,
                   ble_gap_evt_conn_param_update_request_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gap_evt_conn_sec_update_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         ble_evt_t * const     p_event,
                                         uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST, gap, conn_sec_update);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.conn_sec_update, ble_gap_evt_conn_sec_update_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_connected_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   ble_evt_t * const     p_event,
                                   uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_CONNECTED, gap, connected);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.connected, ble_gap_evt_connected_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gap_evt_disconnected_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      ble_evt_t * const     p_event,
                                      uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_DISCONNECTED, gap, disconnected);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.disconnected, ble_gap_evt_disconnected_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_key_pressed_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   ble_evt_t * const     p_event,
                                   uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_KEY_PRESSED, gap, key_pressed);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.gap_evt.params.key_pressed.kp_not);

    SER_EVT_DEC_END;
}


uint32_t ble_gap_evt_lesc_dhkey_request_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            ble_evt_t * const     p_event,
                                            uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_LESC_DHKEY_REQUEST, gap, lesc_dhkey_request);

    uint8_t ser_data;
    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);

    // keyset is an extension of standard event data - used to synchronize keys at application
    uint32_t conn_index;
    err_code = app_ble_gap_sec_context_find(p_event->evt.gap_evt.conn_handle, &conn_index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    p_event->evt.gap_evt.params.lesc_dhkey_request.p_pk_peer = m_app_keys_table[conn_index].keyset.keys_peer.p_pk;
    SER_PULL_COND(&p_event->evt.gap_evt.params.lesc_dhkey_request.p_pk_peer, ble_gap_lesc_p256_pk_t_dec);

    SER_PULL_uint8(&ser_data);
    p_event->evt.gap_evt.params.lesc_dhkey_request.oobd_req = ser_data & 0x01;

    SER_EVT_DEC_END;
}


#define PASSKEY_LEN sizeof (p_event->evt.gap_evt.params.passkey_display.passkey)


uint32_t ble_gap_evt_passkey_display_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         ble_evt_t * const     p_event,
                                         uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_PASSKEY_DISPLAY, gap, passkey_display);

    uint8_t ser_data;
    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_uint8array(p_event->evt.gap_evt.params.passkey_display.passkey, BLE_GAP_PASSKEY_LEN);
    SER_PULL_uint8(&ser_data);
    p_event->evt.gap_evt.params.passkey_display.match_request = (ser_data & 0x01);

    SER_EVT_DEC_END;
}



uint32_t ble_gap_evt_rssi_changed_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      ble_evt_t * const     p_event,
                                      uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_RSSI_CHANGED, gap, rssi_changed);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_int8(&p_event->evt.gap_evt.params.rssi_changed.rssi);

    SER_EVT_DEC_END;
}


uint32_t ble_gap_evt_scan_req_report_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         ble_evt_t * const     p_event,
                                         uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_SCAN_REQ_REPORT, gap, scan_req_report);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.scan_req_report.peer_addr, ble_gap_addr_t_dec);
    SER_PULL_int8(&p_event->evt.gap_evt.params.scan_req_report.rssi);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_sec_info_request_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          ble_evt_t * const     p_event,
                                          uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_SEC_INFO_REQUEST, gap, sec_info_request);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.sec_info_request, ble_gap_evt_sec_info_request_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_sec_params_request_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            ble_evt_t * const     p_event,
                                            uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_SEC_PARAMS_REQUEST, gap, sec_params_request);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.sec_params_request, ble_gap_evt_sec_params_request_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_sec_request_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     ble_evt_t * const     p_event,
                                     uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_SEC_REQUEST, gap, sec_request);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.sec_request, ble_gap_evt_sec_request_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gap_evt_timeout_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 ble_evt_t * const     p_event,
                                 uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_TIMEOUT, gap, timeout);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.gap_evt.params.timeout.src);

    SER_EVT_DEC_END;
}

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_gap_evt_phy_update_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   ble_evt_t * const     p_event,
                                   uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_PHY_UPDATE, gap, phy_update);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_uint8(&p_event->evt.gap_evt.params.phy_update.status);
    SER_PULL_uint8(&p_event->evt.gap_evt.params.phy_update.tx_phy);
    SER_PULL_uint8(&p_event->evt.gap_evt.params.phy_update.rx_phy);

    SER_EVT_DEC_END;
}
#endif
#if NRF_SD_BLE_API_VERSION >= 4
uint32_t ble_gap_evt_data_length_update_request_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 ble_evt_t * const     p_event,
                                 uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST, gap, timeout);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.data_length_update_request.peer_params, ble_gap_data_length_params_t_dec);

    SER_EVT_DEC_END;
}
uint32_t ble_gap_evt_data_length_update_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 ble_evt_t * const     p_event,
                                 uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GAP_EVT_DATA_LENGTH_UPDATE, gap, timeout);

    SER_PULL_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PULL_FIELD(&p_event->evt.gap_evt.params.data_length_update.effective_params, ble_gap_data_length_params_t_dec);

    SER_EVT_DEC_END;
}
#endif
