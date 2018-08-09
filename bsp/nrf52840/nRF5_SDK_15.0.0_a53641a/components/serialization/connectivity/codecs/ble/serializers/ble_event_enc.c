/**
 * Copyright (c) 2013 - 2018, Nordic Semiconductor ASA
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
#include "ble_conn.h"
#include "ble_evt_conn.h"
#include "ble_gap_evt_conn.h"
#include "ble_gattc_evt_conn.h"
#include "ble_gatts_evt_conn.h"
#include "ble_l2cap_evt_conn.h"
#include "ble_serialization.h"
#include "app_util.h"
#include "nrf_log.h"

uint32_t ble_event_enc(ble_evt_t const * const p_event,
                       uint32_t                event_len,
                       uint8_t * const         p_buf,
                       uint32_t * const        p_buf_len)
{
    uint32_t ret_val = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);
    SER_ASSERT_NOT_NULL(p_event);

    switch (p_event->header.evt_id)
    {
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
        case BLE_EVT_TX_COMPLETE:
            ret_val = ble_evt_tx_complete_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif
        case BLE_EVT_USER_MEM_RELEASE:
            ret_val = ble_evt_user_mem_release_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_EVT_USER_MEM_REQUEST:
            ret_val = ble_evt_user_mem_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
        case BLE_EVT_DATA_LENGTH_CHANGED:
            ret_val = ble_evt_data_length_changed_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif

        case BLE_GAP_EVT_CONN_PARAM_UPDATE:
            ret_val = ble_gap_evt_conn_param_update_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#ifndef S112
        case BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST:
            ret_val = ble_gap_evt_conn_param_update_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif //!S112
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            ret_val = ble_gap_evt_sec_params_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_SEC_INFO_REQUEST:
            ret_val = ble_gap_evt_sec_info_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_AUTH_STATUS:
            ret_val = ble_gap_evt_auth_status_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_PASSKEY_DISPLAY:
            ret_val = ble_gap_evt_passkey_display_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_AUTH_KEY_REQUEST:
            ret_val = ble_gap_evt_auth_key_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_CONN_SEC_UPDATE:
            ret_val = ble_gap_evt_conn_sec_update_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_RSSI_CHANGED:
            ret_val = ble_gap_evt_rssi_changed_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_TIMEOUT:
            ret_val = ble_gap_evt_timeout_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            ret_val = ble_gap_evt_disconnected_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_CONNECTED:
            ret_val = ble_gap_evt_connected_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GAP_EVT_SEC_REQUEST:
            ret_val = ble_gap_evt_sec_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
        case BLE_GAP_EVT_KEY_PRESSED:
            ret_val = ble_gap_evt_key_pressed_enc(p_event, event_len, p_buf, p_buf_len);
            break;
        case BLE_GAP_EVT_LESC_DHKEY_REQUEST:
            ret_val = ble_gap_evt_lesc_dhkey_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#if NRF_SD_BLE_API_VERSION >= 5
        case BLE_GAP_EVT_PHY_UPDATE:
            ret_val = ble_gap_evt_phy_update_enc(p_event, event_len, p_buf, p_buf_len);
            break;
        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
            ret_val = ble_gap_evt_phy_update_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif
#if NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)
        case BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST:
            ret_val = ble_gap_evt_data_length_update_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
        case BLE_GAP_EVT_DATA_LENGTH_UPDATE:
            ret_val = ble_gap_evt_data_length_update_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif //NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)
        case BLE_GATTC_EVT_CHAR_DISC_RSP:
            ret_val = ble_gattc_evt_char_disc_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_DESC_DISC_RSP:
            ret_val = ble_gattc_evt_desc_disc_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP:
            ret_val = ble_gattc_evt_char_val_by_uuid_read_rsp_enc(p_event,
                                                                  event_len,
                                                                  p_buf,
                                                                  p_buf_len);
            break;

        case BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP:
            ret_val = ble_gattc_evt_prim_srvc_disc_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_HVX:
            ret_val = ble_gattc_evt_hvx_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_READ_RSP:
            ret_val = ble_gattc_evt_read_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_TIMEOUT:
            ret_val = ble_gattc_evt_timeout_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_WRITE_RSP:
            ret_val = ble_gattc_evt_write_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_REL_DISC_RSP:
            ret_val = ble_gattc_evt_rel_disc_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_CHAR_VALS_READ_RSP:
            ret_val = ble_gattc_evt_char_vals_read_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_ATTR_INFO_DISC_RSP:
            ret_val = ble_gattc_evt_attr_info_disc_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTC_EVT_EXCHANGE_MTU_RSP:
            ret_val = ble_gattc_evt_exchange_mtu_rsp_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#if NRF_SD_BLE_API_VERSION >= 4
        case BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE:
            ret_val = ble_gattc_evt_write_cmd_tx_complete_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif

        case BLE_GATTS_EVT_HVC:
            ret_val = ble_gatts_evt_hvc_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTS_EVT_TIMEOUT:
            ret_val = ble_gatts_evt_timeout_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTS_EVT_SC_CONFIRM:
            ret_val = ble_gatts_evt_sc_confirm_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTS_EVT_WRITE:
            ret_val = ble_gatts_evt_write_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            ret_val = ble_gatts_evt_rw_authorize_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            ret_val = ble_gatts_evt_sys_attr_missing_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            ret_val = ble_gatts_evt_exchange_mtu_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#if NRF_SD_BLE_API_VERSION >= 4
        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            ret_val = ble_gatts_evt_hvn_tx_complete_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
        case BLE_L2CAP_EVT_RX:
            ret_val = ble_l2cap_evt_rx_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION >= 5 && !defined(S112)
        case BLE_L2CAP_EVT_CH_SETUP_REQUEST:
            ret_val = ble_l2cap_evt_ch_setup_request_enc(p_event, event_len, p_buf, p_buf_len);
            break;
        case BLE_L2CAP_EVT_CH_SETUP_REFUSED:
            ret_val = ble_l2cap_evt_ch_setup_refused_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_L2CAP_EVT_CH_SETUP:
            ret_val = ble_l2cap_evt_ch_setup_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_L2CAP_EVT_CH_RELEASED:
            ret_val = ble_l2cap_evt_ch_released_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED:
            ret_val = ble_l2cap_evt_ch_sdu_buf_released_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_L2CAP_EVT_CH_CREDIT:
            ret_val = ble_l2cap_evt_ch_credit_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_L2CAP_EVT_CH_RX:
            ret_val = ble_l2cap_evt_ch_rx_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        case BLE_L2CAP_EVT_CH_TX:
            ret_val = ble_l2cap_evt_ch_tx_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif //defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION >= 5 && !defined(S112)
#ifndef S112
        case BLE_GAP_EVT_ADV_REPORT:
            ret_val = ble_gap_evt_adv_report_enc(p_event, event_len, p_buf, p_buf_len);
            break;
#endif //!S112
        case BLE_GAP_EVT_SCAN_REQ_REPORT:
            ret_val = ble_gap_evt_scan_req_report_enc(p_event, event_len, p_buf, p_buf_len);
            break;

        default:
            ret_val    = NRF_ERROR_NOT_SUPPORTED;
            *p_buf_len = 0;
            break;
    }

    return ret_val;
}
