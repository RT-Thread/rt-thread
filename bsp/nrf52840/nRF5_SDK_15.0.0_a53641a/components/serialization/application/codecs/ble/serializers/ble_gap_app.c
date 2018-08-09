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
#include "ble_gap_app.h"
#include <stdlib.h>
#include <string.h>
#include "ble_serialization.h"
#include "ble_gap_struct_serialization.h"
#include "ble_struct_serialization.h"
#include "cond_field_serialization.h"
#include "app_util.h"

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 6
uint32_t ble_gap_adv_data_set_req_enc(uint8_t const * const p_data,
                                      uint8_t               dlen,
                                      uint8_t const * const p_sr_data,
                                      uint8_t               srdlen,
                                      uint8_t * const       p_buf,
                                      uint32_t * const      p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ADV_DATA_SET);

    SER_PUSH_len8data(p_data, dlen);
    SER_PUSH_len8data(p_sr_data, srdlen);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_adv_data_set_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_ADV_DATA_SET);
}
#endif

uint32_t ble_gap_adv_start_req_enc(
#if NRF_SD_BLE_API_VERSION > 5
                                   uint8_t adv_handle,
#else
                                   ble_gap_adv_params_t const * const p_adv_params,
#endif
#if NRF_SD_BLE_API_VERSION >= 4
                                   uint8_t                            conn_cfg_tag,
#endif
                                   uint8_t * const                    p_buf,
                                   uint32_t * const                   p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ADV_START);

#if NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&adv_handle);
#else
    SER_PUSH_COND(p_adv_params, ble_gap_adv_params_t_enc);
#endif

#if NRF_SD_BLE_API_VERSION >= 4
    SER_PUSH_uint8(&conn_cfg_tag);
#endif
    SER_REQ_ENC_END;
}


uint32_t ble_gap_adv_start_rsp_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_ADV_START);
}


uint32_t ble_gap_adv_stop_req_enc(
#if NRF_SD_BLE_API_VERSION > 5
                                  uint8_t adv_handle,
#endif
                                  uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ADV_STOP);
#if NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&adv_handle);
#endif
    SER_REQ_ENC_END;
}

uint32_t ble_gap_adv_stop_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_ADV_STOP);
}



uint32_t ble_gap_appearance_get_req_enc(uint16_t const * const p_appearance,
                                        uint8_t * const        p_buf,
                                        uint32_t * const       p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_APPEARANCE_GET);
    SER_PUSH_COND(p_appearance, NULL);
    SER_REQ_ENC_END;
}


uint32_t ble_gap_appearance_get_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint16_t * const      p_appearance,
                                        uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_APPEARANCE_GET);
    SER_PULL_COND(&p_appearance, uint16_t_dec);
    SER_RSP_DEC_END;
}


uint32_t ble_gap_appearance_set_req_enc(uint16_t         appearance,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_APPEARANCE_SET);
    SER_PUSH_uint16(&appearance);
    SER_REQ_ENC_END;
}


uint32_t ble_gap_appearance_set_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_APPEARANCE_SET);
}


uint32_t ble_gap_auth_key_reply_req_enc(uint16_t              conn_handle,
                                        uint8_t               key_type,
                                        uint8_t const * const p_key,
                                        uint8_t * const       p_buf,
                                        uint32_t * const      p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_AUTH_KEY_REPLY);

    uint8_t key_len;
    switch (key_type)
    {
        case BLE_GAP_AUTH_KEY_TYPE_NONE:
            key_len = 0;
            break;

        case BLE_GAP_AUTH_KEY_TYPE_PASSKEY:
            key_len = 6;
            break;

        case BLE_GAP_AUTH_KEY_TYPE_OOB:
            key_len = 16;
            break;

        default:
            return NRF_ERROR_INVALID_PARAM;
    }

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint8(&key_type);
    SER_PUSH_buf(p_key, key_len);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_auth_key_reply_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_AUTH_KEY_REPLY);
}



uint32_t ble_gap_authenticate_req_enc(uint16_t                           conn_handle,
                                      ble_gap_sec_params_t const * const p_sec_params,
                                      uint8_t * const                    p_buf,
                                      uint32_t * const                   p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_AUTHENTICATE);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_sec_params, ble_gap_sec_params_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_authenticate_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_AUTHENTICATE);
}


uint32_t ble_gap_conn_param_update_req_enc(uint16_t                            conn_handle,
                                           ble_gap_conn_params_t const * const p_conn_params,
                                           uint8_t * const                     p_buf,
                                           uint32_t * const                    p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_CONN_PARAM_UPDATE);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_conn_params, ble_gap_conn_params_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_conn_param_update_rsp_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_CONN_PARAM_UPDATE);
}


uint32_t ble_gap_conn_sec_get_req_enc(uint16_t                         conn_handle,
                                      ble_gap_conn_sec_t const * const p_conn_sec,
                                      uint8_t * const                  p_buf,
                                      uint32_t * const                 p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_CONN_SEC_GET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_conn_sec, NULL);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_conn_sec_get_rsp_dec(uint8_t const * const        p_buf,
                                      uint32_t                     packet_len,
                                      ble_gap_conn_sec_t * * const pp_conn_sec,
                                      uint32_t * const             p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_CONN_SEC_GET);
    SER_PULL_COND(pp_conn_sec, ble_gap_conn_sec_t_dec);
    SER_RSP_DEC_END;
}

#ifndef S112
uint32_t ble_gap_connect_req_enc(ble_gap_addr_t const * const        p_peer_addr,
                                 ble_gap_scan_params_t const * const p_scan_params,
                                 ble_gap_conn_params_t const * const p_conn_params,
#if NRF_SD_BLE_API_VERSION >= 4
                                 uint8_t                             conn_cfg_tag,
#endif
                                 uint8_t * const                     p_buf,
                                 uint32_t * const                    p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_CONNECT);

    SER_PUSH_COND(p_peer_addr, ble_gap_addr_t_enc);
    SER_PUSH_COND(p_scan_params, ble_gap_scan_params_t_enc);
    SER_PUSH_COND(p_conn_params, ble_gap_conn_params_t_enc);
#if NRF_SD_BLE_API_VERSION >= 4
    SER_PUSH_uint8(&conn_cfg_tag);
#endif

    SER_REQ_ENC_END;
}

uint32_t ble_gap_connect_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_CONNECT);
}


uint32_t ble_gap_connect_cancel_req_enc(uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_CONNECT_CANCEL);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_connect_cancel_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_CONNECT_CANCEL);
}
#endif

uint32_t ble_gap_device_name_get_req_enc(uint8_t const * const  p_dev_name,
                                         uint16_t const * const p_len,
                                         uint8_t * const        p_buf,
                                         uint32_t * const       p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_DEVICE_NAME_GET);

    SER_PUSH_COND(p_len, uint16_t_enc);
    SER_PUSH_COND(p_dev_name, NULL);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_device_name_get_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint8_t * const       p_dev_name,
                                         uint16_t * const      p_dev_name_len,
                                         uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_DEVICE_NAME_GET);

    SER_PULL_COND(&p_dev_name_len, uint16_t_dec);
    if (p_dev_name_len)
    {
        SER_PULL_uint8array(p_dev_name, *p_dev_name_len);
    }

    SER_RSP_DEC_END;
}


uint32_t ble_gap_device_name_set_req_enc(ble_gap_conn_sec_mode_t const * const p_write_perm,
                                         uint8_t const * const                 p_dev_name,
                                         uint16_t                              len,
                                         uint8_t * const                       p_buf,
                                         uint32_t * const                      p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_DEVICE_NAME_SET);

    SER_ERROR_CHECK(len <= BLE_GAP_DEVNAME_MAX_LEN, NRF_ERROR_INVALID_PARAM);

    SER_PUSH_COND(p_write_perm, ble_gap_conn_sec_mode_t_enc);
    SER_PUSH_len16data(p_dev_name, len);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_device_name_set_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_DEVICE_NAME_SET);
}


uint32_t ble_gap_disconnect_req_enc(uint16_t         conn_handle,
                                    uint8_t          hci_status_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_DISCONNECT);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint8(&hci_status_code);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_disconnect_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_DISCONNECT);
}

#ifndef S112
uint32_t ble_gap_encrypt_req_enc(uint16_t                          conn_handle,
                                 ble_gap_master_id_t const * const p_master_id,
                                 ble_gap_enc_info_t const  * const p_enc_info,
                                 uint8_t                   * const p_buf,
                                 uint32_t                  * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ENCRYPT);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_master_id, ble_gap_master_id_t_enc);
    SER_PUSH_COND(p_enc_info, ble_gap_enc_info_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_encrypt_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t      * const p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_ENCRYPT);
}
#endif

uint32_t ble_gap_keypress_notify_req_enc(uint16_t                           conn_handle,
                                          uint8_t                           kp_not,
                                          uint8_t * const                   p_buf,
                                          uint32_t * const                  p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_KEYPRESS_NOTIFY);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint8(&kp_not);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_keypress_notify_rsp_dec(uint8_t const * const              p_buf,
                                        uint32_t                           packet_len,
                                        uint32_t * const                   p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_KEYPRESS_NOTIFY);
}


uint32_t ble_gap_lesc_dhkey_reply_req_enc(uint16_t             conn_handle,
                                          ble_gap_lesc_dhkey_t const *p_dhkey,
                                          uint8_t * const      p_buf,
                                          uint32_t * const     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_LESC_DHKEY_REPLY);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_dhkey, ble_gap_lesc_dhkey_t_enc);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_lesc_dhkey_reply_rsp_dec(uint8_t const * const              p_buf,
                                        uint32_t                           packet_len,
                                        uint32_t * const                   p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_LESC_DHKEY_REPLY);
}


uint32_t ble_gap_lesc_oob_data_get_req_enc(uint16_t                      conn_handle,
                                           ble_gap_lesc_p256_pk_t const *p_pk_own,
                                           ble_gap_lesc_oob_data_t      *p_oobd_own,
                                           uint8_t * const               p_buf,
                                           uint32_t * const              p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_LESC_OOB_DATA_GET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_pk_own, ble_gap_lesc_p256_pk_t_enc);
    SER_PUSH_COND(p_oobd_own, NULL);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_lesc_oob_data_get_rsp_dec(uint8_t const * const       p_buf,
                                           uint32_t                    packet_len,
                                           ble_gap_lesc_oob_data_t  * *pp_oobd_own,
                                           uint32_t * const            p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_LESC_OOB_DATA_GET);
    SER_PULL_COND(pp_oobd_own, ble_gap_lesc_oob_data_t_dec);
    SER_RSP_DEC_END;
}


uint32_t ble_gap_lesc_oob_data_set_req_enc(uint16_t             conn_handle,
                                           ble_gap_lesc_oob_data_t const *p_oobd_own,
                                           ble_gap_lesc_oob_data_t const *p_oobd_peer,
                                           uint8_t * const      p_buf,
                                           uint32_t * const     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_LESC_OOB_DATA_SET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_oobd_own, ble_gap_lesc_oob_data_t_enc);
    SER_PUSH_COND(p_oobd_peer, ble_gap_lesc_oob_data_t_enc);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_lesc_oob_data_set_rsp_dec(uint8_t const * const              p_buf,
                                           uint32_t                           packet_len,
                                           uint32_t * const                   p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_LESC_OOB_DATA_SET);
}


uint32_t ble_gap_ppcp_get_req_enc(ble_gap_conn_params_t const * const p_conn_params,
                                  uint8_t * const                     p_buf,
                                  uint32_t * const                    p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_PPCP_GET);
    SER_PUSH_COND(p_conn_params, NULL);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_ppcp_get_rsp_dec(uint8_t const * const         p_buf,
                                  uint32_t                      packet_len,
                                  ble_gap_conn_params_t * const p_conn_params,
                                  uint32_t * const              p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_PPCP_GET);
    SER_PULL_COND(&p_conn_params, ble_gap_conn_params_t_dec);
    SER_RSP_DEC_END;
}


uint32_t ble_gap_ppcp_set_req_enc(ble_gap_conn_params_t const * const p_conn_params,
                                  uint8_t * const                     p_buf,
                                  uint32_t * const                    p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_PPCP_SET);
    SER_PUSH_COND(p_conn_params, ble_gap_conn_params_t_enc);
    SER_REQ_ENC_END;
}


uint32_t ble_gap_ppcp_set_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_PPCP_SET);
}

uint32_t ble_gap_rssi_get_req_enc(uint16_t             conn_handle,
                                  int8_t const * const p_rssi,
#if NRF_SD_BLE_API_VERSION > 5
                                  uint8_t const * const p_ch_index,
#endif
                                  uint8_t  * const     p_buf,
                                  uint32_t * const     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_RSSI_GET);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_rssi, NULL);
#if NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_COND(p_ch_index, NULL);
#endif
    SER_REQ_ENC_END;
}


uint32_t ble_gap_rssi_get_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  int8_t * const        p_rssi,
#if NRF_SD_BLE_API_VERSION > 5
                                  uint8_t * const        p_ch_index,
#endif
                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_RSSI_GET);
    SER_PULL_COND(&p_rssi, uint8_t_dec);
#if NRF_SD_BLE_API_VERSION > 5
    SER_PULL_COND(&p_ch_index, uint8_t_dec);
#endif
    SER_RSP_DEC_END;
}


uint32_t ble_gap_rssi_start_req_enc(uint16_t         conn_handle,
                                    uint8_t          threshold_dbm,
                                    uint8_t          skip_count,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_RSSI_START);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint8(&threshold_dbm);
    SER_PUSH_uint8(&skip_count);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_rssi_start_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_RSSI_START);
}


uint32_t ble_gap_rssi_stop_req_enc(uint16_t         conn_handle,
                                   uint8_t * const  p_buf,
                                   uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_RSSI_STOP);
    SER_PUSH_uint16(&conn_handle);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_rssi_stop_rsp_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_RSSI_STOP);
}

#ifndef S112
uint32_t ble_gap_scan_start_req_enc(ble_gap_scan_params_t const *  p_scan_params,
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
                                    ble_data_t const *             p_adv_report_buffer,
#endif
                                    uint8_t * const                p_buf,
                                    uint32_t * const               p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_SCAN_START);
    SER_PUSH_COND(p_scan_params, ble_gap_scan_params_t_enc);
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_COND(p_adv_report_buffer, ble_data_t_enc);
#endif
    SER_REQ_ENC_END;
}
uint32_t ble_gap_scan_start_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_SCAN_START);
}


uint32_t ble_gap_scan_stop_req_enc(uint8_t * const  p_buf,
                                  uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_SCAN_STOP);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_scan_stop_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_SCAN_STOP);
}
#endif

uint32_t ble_gap_sec_info_reply_req_enc(uint16_t                    conn_handle,
                                        ble_gap_enc_info_t  const * p_enc_info,
                                        ble_gap_irk_t       const * p_id_info,
                                        ble_gap_sign_info_t const * p_sign_info,
                                        uint8_t * const             p_buf,
                                        uint32_t * const            p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_SEC_INFO_REPLY);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_enc_info, ble_gap_enc_info_t_enc);
    SER_PUSH_COND(p_id_info, ble_gap_irk_t_enc);
    SER_PUSH_COND(p_sign_info, ble_gap_sign_info_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_sec_info_reply_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_SEC_INFO_REPLY);
}


uint32_t ble_gap_sec_params_reply_req_enc(uint16_t                           conn_handle,
                                          uint8_t                            sec_status,
                                          ble_gap_sec_params_t const * const p_sec_params,
                                          ble_gap_sec_keyset_t const * const p_sec_keyset,
                                          uint8_t * const                    p_buf,
                                          uint32_t * const                   p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_SEC_PARAMS_REPLY);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint8(&sec_status);
    SER_PUSH_COND(p_sec_params, ble_gap_sec_params_t_enc);
    SER_PUSH_COND(p_sec_keyset, ble_gap_sec_keyset_t_enc);

    SER_REQ_ENC_END;
}

uint32_t ble_gap_sec_params_reply_rsp_dec(uint8_t const * const              p_buf,
                                          uint32_t                           packet_len,
                                          ble_gap_sec_keyset_t const * const p_sec_keyset,
                                          uint32_t * const                   p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_SEC_PARAMS_REPLY);
    SER_PULL_COND(&p_sec_keyset, ble_gap_sec_keyset_t_dec);
    SER_RSP_DEC_END;
}


uint32_t ble_gap_tx_power_set_req_enc(
#if NRF_SD_BLE_API_VERSION > 5
                                      uint8_t role, uint16_t handle,
#endif
                                      int8_t           tx_power,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_TX_POWER_SET);
#if NRF_SD_BLE_API_VERSION > 5
    SER_PUSH_uint8(&role);
    SER_PUSH_uint16(&handle);
#endif
    SER_PUSH_int8(&tx_power);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_tx_power_set_rsp_dec(uint8_t const * const p_buf,
                                      uint32_t              packet_len,
                                      uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_TX_POWER_SET);
}

uint32_t ble_gap_addr_get_req_enc(ble_gap_addr_t const * const p_address,
                                  uint8_t * const              p_buf,
                                  uint32_t * const             p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ADDR_GET);
    SER_PUSH_COND(p_address, NULL);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_addr_get_rsp_dec(uint8_t const * const  p_buf,
                                  uint32_t               packet_len,
                                  ble_gap_addr_t * const p_address,
                                  uint32_t * const       p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_ADDR_GET);
    SER_PULL_FIELD(p_address, ble_gap_addr_t_dec);
    SER_RSP_DEC_END;
}

uint32_t ble_gap_addr_set_req_enc(ble_gap_addr_t const * const p_addr,
                                  uint8_t * const              p_buf,
                                  uint32_t * const             p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ADDR_SET);
    SER_PUSH_COND(p_addr, ble_gap_addr_t_enc);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_addr_set_rsp_dec(uint8_t const * const p_buf,
                                  uint32_t              packet_len,
                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_ADDR_SET);
}

uint32_t ble_gap_privacy_set_req_enc(ble_gap_privacy_params_t  const * p_privacy_params,
                                     uint8_t * const                   p_buf,
                                     uint32_t * const                  p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_PRIVACY_SET);
    SER_PUSH_COND(p_privacy_params, ble_gap_privacy_params_t_enc);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_privacy_set_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_PRIVACY_SET);
}


uint32_t ble_gap_privacy_get_req_enc(ble_gap_privacy_params_t const * const p_privacy_params,
                                     uint8_t * const                        p_buf,
                                     uint32_t * const                       p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_PRIVACY_GET);
    SER_PUSH_COND(p_privacy_params, ble_gap_privacy_params_t_enc);
    SER_REQ_ENC_END;
}

uint32_t ble_gap_privacy_get_rsp_dec(uint8_t const * const                  p_buf,
                                     uint32_t                               packet_len,
                                     ble_gap_privacy_params_t const * const p_privacy_params,
                                     uint32_t * const                       p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_PRIVACY_GET);
    SER_PULL_COND((void **)&p_privacy_params, ble_gap_privacy_params_t_dec);
    SER_RSP_DEC_END;
}

uint32_t ble_gap_whitelist_set_req_enc(ble_gap_addr_t const * const * const pp_wl_addrs,
                                       uint8_t const                        len,
                                       uint8_t * const                      p_buf,
                                       uint32_t * const                     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_WHITELIST_SET);

    uint8_t presence;
    SER_PUSH_uint8(&len);

    if (pp_wl_addrs)
    {
        presence = SER_FIELD_PRESENT;
        SER_PUSH_uint8(&presence);

        for (uint32_t i = 0; i < len; ++i)
        {
            SER_PUSH_COND(pp_wl_addrs[i], ble_gap_addr_t_enc);
        }
    }
    else
    {
        presence = SER_FIELD_NOT_PRESENT;
        SER_PUSH_uint8(&presence);
    }

    SER_REQ_ENC_END;
}

uint32_t ble_gap_whitelist_set_rsp_dec(uint8_t const * const p_buf,
                                       uint32_t              packet_len,
                                       uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_WHITELIST_SET);
}

uint32_t ble_gap_device_identities_set_req_enc(ble_gap_id_key_t const * const * const pp_id_keys,
                                               ble_gap_irk_t const * const * const    pp_local_irks,
                                               uint8_t const                          len,
                                               uint8_t * const                        p_buf,
                                               uint32_t * const                       p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_DEVICE_IDENTITIES_SET);
    uint8_t presence;
    SER_PUSH_uint8(&len);

    if (pp_id_keys)
    {
        presence = SER_FIELD_PRESENT;
        SER_PUSH_uint8(&presence);

        for (uint32_t i = 0; i < len; ++i)
        {
            SER_PUSH_COND(pp_id_keys[i], ble_gap_id_key_t_enc);
        }
    }
    else
    {
        presence = SER_FIELD_NOT_PRESENT;
        SER_PUSH_uint8(&presence);
    }

    if (pp_local_irks)
    {
        presence = SER_FIELD_PRESENT;
        SER_PUSH_uint8(&presence);

        for (uint32_t i = 0; i < len; ++i)
        {
            SER_PUSH_COND(pp_local_irks[i], ble_gap_irk_t_enc);
        }
    }
    else
    {
        presence = SER_FIELD_NOT_PRESENT;
        SER_PUSH_uint8(&presence);
    }

    SER_REQ_ENC_END;
}

uint32_t ble_gap_device_identities_set_rsp_dec(uint8_t const * const p_buf,
                                               uint32_t              packet_len,
                                               uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_DEVICE_IDENTITIES_SET);
}
#if NRF_SD_BLE_API_VERSION >= 4 && !defined(S112)
uint32_t ble_gap_data_length_update_req_enc(uint16_t                             conn_handle,
                                            ble_gap_data_length_params_t const * p_dl_params,
                                            ble_gap_data_length_limitation_t *   p_dl_limitation,
                                            uint8_t * const                      p_buf,
                                            uint32_t * const                     p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_DATA_LENGTH_UPDATE);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_dl_params, ble_gap_data_length_params_t_enc);
    SER_PUSH_COND(p_dl_limitation, NULL);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_data_length_update_rsp_dec(uint8_t const * const              p_buf,
                                            uint32_t                           packet_len,
                                            ble_gap_data_length_limitation_t * p_dl_limitation,
                                            uint32_t * const                   p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_DATA_LENGTH_UPDATE);
    SER_PULL_COND((void **)&p_dl_limitation, ble_gap_data_length_limitation_t_dec);
    SER_RSP_DEC_END;
}
#endif
#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_gap_phy_update_req_enc(uint16_t                conn_handle,
                                    ble_gap_phys_t const *  p_gap_phys,
                                    uint8_t * const         p_buf,
                                    uint32_t * const        p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_PHY_UPDATE);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_gap_phys, ble_gap_phys_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_phy_update_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_PHY_UPDATE);
}
#endif

#if NRF_SD_BLE_API_VERSION > 5
uint32_t ble_gap_adv_set_configure_req_enc(uint8_t *                   p_adv_handle,
                                           ble_gap_adv_data_t const *  p_adv_data,
                                           ble_gap_adv_params_t const *p_adv_params,
                                           uint8_t * const             p_buf,
                                           uint32_t * const            p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_ADV_SET_CONFIGURE);

    SER_PUSH_COND(p_adv_handle, uint8_t_enc);
    SER_PUSH_COND(p_adv_data, ble_gap_adv_data_t_enc);
    SER_PUSH_COND(p_adv_params, ble_gap_adv_params_t_enc);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_adv_set_configure_rsp_dec(uint8_t const * const  p_buf,
                                           uint32_t               packet_len,
                                           uint8_t *              p_adv_handle,
                                           uint32_t * const       p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_GAP_ADV_SET_CONFIGURE);
    SER_PULL_COND((void **)&p_adv_handle, uint8_t_dec);
    SER_RSP_DEC_END;
}

#ifndef S112
uint32_t ble_gap_qos_channel_survey_start_req_enc(uint32_t                interval_us,
                                                  uint8_t * const         p_buf,
                                                  uint32_t * const        p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_QOS_CHANNEL_SURVEY_START);

    SER_PUSH_uint32(&interval_us);

    SER_REQ_ENC_END;
}


uint32_t ble_gap_qos_channel_survey_start_rsp_dec(uint8_t const * const p_buf,
                                                  uint32_t              packet_len,
                                                  uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_QOS_CHANNEL_SURVEY_START);
}

uint32_t ble_gap_qos_channel_survey_stop_req_enc(uint8_t * const         p_buf,
                                                 uint32_t * const        p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_GAP_QOS_CHANNEL_SURVEY_STOP);
    SER_REQ_ENC_END;
}


uint32_t ble_gap_qos_channel_survey_stop_rsp_dec(uint8_t const * const p_buf,
                                                 uint32_t              packet_len,
                                                 uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_GAP_QOS_CHANNEL_SURVEY_STOP);
}
#endif //!S112
#endif
