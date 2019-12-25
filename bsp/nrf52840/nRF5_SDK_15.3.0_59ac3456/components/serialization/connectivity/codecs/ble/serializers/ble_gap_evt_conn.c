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
#include "ble.h"
#include "ble_gap_evt_conn.h"
#include <string.h>
#include "ble_serialization.h"
#include "cond_field_serialization.h"
#include "ble_gap_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "conn_ble_gap_sec_keys.h"
#include "app_util.h"

extern ser_ble_gap_conn_keyset_t m_conn_keys_table[];

#ifndef S112
uint32_t ble_gap_evt_adv_report_enc(ble_evt_t const * const p_event,
                                    uint32_t                event_len,
                                    uint8_t * const         p_buf,
                                    uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_ADV_REPORT);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.adv_report, ble_gap_evt_adv_report_t_enc);

#if NRF_SD_BLE_API_VERSION > 5
    conn_ble_gap_scan_data_unset(false);
#endif

    SER_EVT_ENC_END;
}
#endif //!S112

uint32_t ble_gap_evt_auth_key_request_enc(ble_evt_t const * const p_event,
                                          uint32_t                event_len,
                                          uint8_t * const         p_buf,
                                          uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_AUTH_KEY_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.auth_key_request.key_type);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_auth_status_enc(ble_evt_t const * const p_event,
                                     uint32_t                event_len,
                                     uint8_t * const         p_buf,
                                     uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_AUTH_STATUS);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.auth_status, ble_gap_evt_auth_status_t_enc);

    // keyset is an extension of standard event data - used to synchronize keys at application
    uint32_t conn_index;
    err_code = conn_ble_gap_sec_context_find(p_event->evt.gap_evt.conn_handle, &conn_index);
    if (err_code == NRF_SUCCESS)
    {
        SER_PUSH_FIELD(&(m_conn_keys_table[conn_index].keyset), ble_gap_sec_keyset_t_enc);

        err_code = conn_ble_gap_sec_context_destroy(p_event->evt.gap_evt.conn_handle);
        SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    }
    else
    {
        err_code = NRF_SUCCESS;
    }

    SER_EVT_ENC_END;
}


uint32_t ble_gap_evt_conn_param_update_enc(ble_evt_t const * const p_event,
                                           uint32_t                event_len,
                                           uint8_t * const         p_buf,
                                           uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_CONN_PARAM_UPDATE);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.conn_param_update, ble_gap_evt_conn_param_update_t_enc);

    SER_EVT_ENC_END;
}

#ifndef S112
uint32_t ble_gap_evt_conn_param_update_request_enc(ble_evt_t const * const p_event,
                                                   uint32_t                event_len,
                                                   uint8_t * const         p_buf,
                                                   uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.conn_param_update_request,
                   ble_gap_evt_conn_param_update_request_t_enc);

    SER_EVT_ENC_END;
}
#endif //!S112

uint32_t ble_gap_evt_conn_sec_update_enc(ble_evt_t const * const p_event,
                                         uint32_t                event_len,
                                         uint8_t * const         p_buf,
                                         uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_CONN_SEC_UPDATE);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.conn_sec_update, ble_gap_evt_conn_sec_update_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_connected_enc(ble_evt_t const * const p_event,
                                   uint32_t                event_len,
                                   uint8_t * const         p_buf,
                                   uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_CONNECTED);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.connected, ble_gap_evt_connected_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_disconnected_enc(ble_evt_t const * const p_event,
                                      uint32_t                event_len,
                                      uint8_t * const         p_buf,
                                      uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_DISCONNECTED);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.disconnected, ble_gap_evt_disconnected_t_enc);

    // If disconnected and context is not yet destroyed, destroy it now
    uint32_t conn_index;
    err_code = conn_ble_gap_sec_context_find(p_event->evt.gap_evt.conn_handle, &conn_index);
    if (err_code == NRF_SUCCESS)
    {
        err_code = conn_ble_gap_sec_context_destroy(p_event->evt.gap_evt.conn_handle);
        SER_ASSERT(err_code == NRF_SUCCESS, err_code);
    }
    err_code = NRF_SUCCESS;

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_key_pressed_enc(ble_evt_t const * const p_event,
                                   uint32_t                event_len,
                                   uint8_t * const         p_buf,
                                   uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_KEY_PRESSED);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.key_pressed.kp_not);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_lesc_dhkey_request_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_LESC_DHKEY_REQUEST);

    uint8_t ser_data = p_event->evt.gap_evt.params.lesc_dhkey_request.oobd_req & 0x01;
    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_COND(p_event->evt.gap_evt.params.lesc_dhkey_request.p_pk_peer, ble_gap_lesc_p256_pk_t_enc);
    SER_PUSH_uint8(&ser_data);

    SER_EVT_ENC_END;
}

#define PASSKEY_LEN sizeof (p_event->evt.gap_evt.params.passkey_display.passkey)


uint32_t ble_gap_evt_passkey_display_enc(ble_evt_t const * const p_event,
                                         uint32_t                event_len,
                                         uint8_t * const         p_buf,
                                         uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_PASSKEY_DISPLAY);

    uint8_t ser_data = p_event->evt.gap_evt.params.passkey_display.match_request & 0x01;
    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_uint8array(p_event->evt.gap_evt.params.passkey_display.passkey, BLE_GAP_PASSKEY_LEN);
    SER_PUSH_uint8(&ser_data);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_rssi_changed_enc(ble_evt_t const * const p_event,
                                      uint32_t                event_len,
                                      uint8_t * const         p_buf,
                                      uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_RSSI_CHANGED);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_int8(&p_event->evt.gap_evt.params.rssi_changed.rssi);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.rssi_changed.ch_index);
#endif

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_scan_req_report_enc(ble_evt_t const * const p_event,
                                         uint32_t                event_len,
                                         uint8_t * const         p_buf,
                                         uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_SCAN_REQ_REPORT);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.scan_req_report.adv_handle);
#endif
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.scan_req_report.peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_int8(&p_event->evt.gap_evt.params.scan_req_report.rssi);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_sec_info_request_enc(ble_evt_t const * const p_event,
                                          uint32_t                event_len,
                                          uint8_t * const         p_buf,
                                          uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_SEC_INFO_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.sec_info_request, ble_gap_evt_sec_info_request_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_sec_params_request_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_SEC_PARAMS_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.sec_params_request, ble_gap_evt_sec_params_request_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_sec_request_enc(ble_evt_t const * const p_event,
                                     uint32_t                event_len,
                                     uint8_t * const         p_buf,
                                     uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_SEC_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.sec_request, ble_gap_evt_sec_request_t_enc);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_timeout_enc(ble_evt_t const * const p_event,
                                 uint32_t                event_len,
                                 uint8_t * const         p_buf,
                                 uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_TIMEOUT);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.timeout.src);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5 && !defined(S112)
    if (p_event->evt.gap_evt.params.timeout.src == BLE_GAP_TIMEOUT_SRC_SCAN)
    {
        SER_PUSH_FIELD(&p_event->evt.gap_evt.params.timeout.params.adv_report_buffer, ble_data_t_enc);
    }
#endif
    SER_EVT_ENC_END;
}

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_gap_evt_phy_update_enc(ble_evt_t const * const p_event,
                                    uint32_t                event_len,
                                    uint8_t * const         p_buf,
                                    uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_PHY_UPDATE);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.phy_update.status);
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.phy_update.tx_phy);
    SER_PUSH_uint8(&p_event->evt.gap_evt.params.phy_update.rx_phy);

    SER_EVT_ENC_END;
}

uint32_t ble_gap_evt_phy_update_request_enc(ble_evt_t const * const p_event,
                                            uint32_t                event_len,
                                            uint8_t * const         p_buf,
                                            uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_PHY_UPDATE_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.phy_update_request, ble_gap_phys_t_enc);

    SER_EVT_ENC_END;
}
#endif
#if NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)
uint32_t ble_gap_evt_data_length_update_request_enc(ble_evt_t const * const p_event,
                                 uint32_t                event_len,
                                 uint8_t * const         p_buf,
                                 uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.data_length_update_request.peer_params, ble_gap_data_length_params_t_enc);

    SER_EVT_ENC_END;
}
uint32_t ble_gap_evt_data_length_update_enc(ble_evt_t const * const p_event,
                                 uint32_t                event_len,
                                 uint8_t * const         p_buf,
                                 uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_DATA_LENGTH_UPDATE);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.data_length_update.effective_params, ble_gap_data_length_params_t_enc);

    SER_EVT_ENC_END;
}
#endif // NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)

#if NRF_SD_BLE_API_VERSION > 5
uint32_t ble_gap_evt_adv_set_terminated_enc(ble_evt_t const * const p_event,
                                 uint32_t                event_len,
                                 uint8_t * const         p_buf,
                                 uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_ADV_SET_TERMINATED);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);

    SER_PUSH_FIELD(&p_event->evt.gap_evt.params.adv_set_terminated, ble_gap_evt_adv_set_terminated_t_enc);

    SER_EVT_ENC_END;
}
#ifndef S112
uint32_t ble_gap_evt_qos_channel_survey_report_enc(ble_evt_t const * const p_event,
                                 uint32_t                event_len,
                                 uint8_t * const         p_buf,
                                 uint32_t * const        p_buf_len)
{
    SER_EVT_ENC_BEGIN(BLE_GAP_EVT_QOS_CHANNEL_SURVEY_REPORT);

    SER_PUSH_uint16(&p_event->evt.gap_evt.conn_handle);
    SER_PUSH_uint8array((uint8_t *)p_event->evt.gap_evt.params.qos_channel_survey_report.channel_energy,
                        BLE_GAP_CHANNEL_COUNT);

    SER_EVT_ENC_END;
}
#endif //!S112
#endif//NRF_SD_BLE_API_VERSION > 5
