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
#include <string.h>
#include "ble_conn.h"
#include "ble_serialization.h"
#include "cond_field_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_gap_struct_serialization.h"
#include "ble_gatt_struct_serialization.h"
#include "ble_gattc_struct_serialization.h"
#include "ble_gatts_struct_serialization.h"
#include "app_util.h"

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_enable_req_dec(uint8_t const * const         p_buf,
                            uint32_t                      packet_len,
                            ble_enable_params_t * * const pp_ble_enable_params)
{
    SER_REQ_DEC_BEGIN(SD_BLE_ENABLE);
    SER_PULL_COND(pp_ble_enable_params, ble_enable_params_t_dec);
    SER_REQ_DEC_END;
}
#else
uint32_t ble_enable_req_dec(uint8_t const * const         p_buf,
                            uint32_t                      packet_len)
{
    SER_REQ_DEC_BEGIN(SD_BLE_ENABLE);
    SER_REQ_DEC_END;
}
#endif

uint32_t ble_enable_rsp_enc(uint32_t         return_code,
                            uint8_t * const  p_buf,
                            uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_ENABLE);
}


uint32_t ble_opt_get_req_dec(uint8_t const * const   p_buf,
                             uint16_t                packet_len,
                             uint32_t *  const       p_opt_id,
                             ble_opt_t **const       pp_opt )
{
    SER_REQ_DEC_BEGIN(SD_BLE_OPT_GET);

    SER_ASSERT_NOT_NULL(p_opt_id);
    SER_ASSERT_NOT_NULL(pp_opt);
    SER_ASSERT_NOT_NULL(*pp_opt);

    SER_PULL_uint32(p_opt_id);

    SER_PULL_COND(pp_opt, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_opt_get_rsp_enc(uint32_t                return_code,
                             uint8_t * const         p_buf,
                             uint32_t * const        p_buf_len,
                             uint32_t                opt_id,
                             ble_opt_t const * const p_opt)
{
    SER_RSP_ENC_BEGIN(SD_BLE_OPT_GET);

    SER_ASSERT_NOT_NULL(p_opt);

    SER_PUSH_uint32(&opt_id);

    field_encoder_handler_t fp_encoder = NULL;
    void const *            p_struct = NULL;

    switch (opt_id)
    {
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
        case BLE_COMMON_OPT_CONN_BW:
            fp_encoder = ble_common_opt_conn_bw_t_enc;
            p_struct   = &p_opt->common_opt.conn_bw;
        break;
#endif
        case BLE_COMMON_OPT_PA_LNA:
            fp_encoder = ble_common_opt_pa_lna_t_enc;
            p_struct   = &p_opt->common_opt.pa_lna;
        break;
        case BLE_COMMON_OPT_CONN_EVT_EXT:
            fp_encoder = ble_common_opt_conn_evt_ext_t_enc;
            p_struct   = &p_opt->common_opt.conn_evt_ext;
        break;
        case BLE_GAP_OPT_CH_MAP:
            fp_encoder = ble_gap_opt_ch_map_t_enc;
            p_struct   = &p_opt->gap_opt.ch_map;
        break;
        case BLE_GAP_OPT_LOCAL_CONN_LATENCY:
            fp_encoder = ble_gap_opt_local_conn_latency_t_enc;
            p_struct   = &p_opt->gap_opt.local_conn_latency;
        break;
        case BLE_GAP_OPT_PASSKEY:
            fp_encoder = ble_gap_opt_passkey_t_enc;
            p_struct   = &p_opt->gap_opt.passkey;
        break;
        case BLE_GAP_OPT_AUTH_PAYLOAD_TIMEOUT:
            fp_encoder = ble_gap_opt_auth_payload_timeout_t_enc;
            p_struct   = &p_opt->gap_opt.auth_payload_timeout;
        break;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
        case BLE_GAP_OPT_EXT_LEN:
            fp_encoder = ble_gap_opt_ext_len_t_enc;
            p_struct   = &p_opt->gap_opt.ext_len;
        break;
#endif
        case BLE_GAP_OPT_SCAN_REQ_REPORT:
            fp_encoder = ble_gap_opt_scan_req_report_t_enc;
            p_struct   = &p_opt->gap_opt.scan_req_report;
        break;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
        case BLE_GAP_OPT_COMPAT_MODE:
            fp_encoder = ble_gap_opt_compat_mode_t_enc;
            p_struct   = &p_opt->gap_opt.compat_mode;
        break;
#else
        case BLE_GAP_OPT_COMPAT_MODE_1:
            fp_encoder = ble_gap_opt_compat_mode_1_t_enc;
            p_struct   = &p_opt->gap_opt.compat_mode_1;
        break;
        case BLE_GAP_OPT_COMPAT_MODE_2:
            fp_encoder = ble_gap_opt_compat_mode_2_t_enc;
            p_struct   = &p_opt->gap_opt.compat_mode_2;
        break;
#endif
        default:
            SER_ASSERT(NRF_ERROR_INVALID_PARAM, NRF_ERROR_INVALID_PARAM);
        break;
    }

    SER_PUSH_FIELD(p_struct, fp_encoder);

    SER_RSP_ENC_END;
}


uint32_t ble_opt_set_req_dec(uint8_t const * const   p_buf,
                             uint16_t                packet_len,
                             uint32_t *  const       p_opt_id,
                             ble_opt_t **const       pp_opt )
{
    SER_REQ_DEC_BEGIN(SD_BLE_OPT_SET);

    SER_ASSERT_NOT_NULL(p_opt_id);
    SER_ASSERT_NOT_NULL(pp_opt);
    SER_ASSERT_NOT_NULL(*pp_opt);

    SER_PULL_uint32(p_opt_id);

    SER_PULL_COND(pp_opt, NULL);
    if (*pp_opt)
    {
        field_decoder_handler_t fp_decoder = NULL;
        void * p_struct = NULL;

        switch(*p_opt_id)
        {
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
            case BLE_COMMON_OPT_CONN_BW:
                fp_decoder = ble_common_opt_conn_bw_t_dec;
                p_struct   = &((*pp_opt)->common_opt.conn_bw);
            break;
#endif
            case BLE_COMMON_OPT_PA_LNA:
                fp_decoder = ble_common_opt_pa_lna_t_dec;
                p_struct   = &((*pp_opt)->common_opt.pa_lna);
            break;
            case BLE_COMMON_OPT_CONN_EVT_EXT:
                fp_decoder = ble_common_opt_conn_evt_ext_t_dec;
                p_struct   = &((*pp_opt)->common_opt.conn_evt_ext);
            break;
            case BLE_GAP_OPT_CH_MAP:
                fp_decoder = ble_gap_opt_ch_map_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.ch_map);
            break;
            case BLE_GAP_OPT_LOCAL_CONN_LATENCY:
                fp_decoder = ble_gap_opt_local_conn_latency_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.local_conn_latency);
            break;
            case BLE_GAP_OPT_PASSKEY:
                fp_decoder = ble_gap_opt_passkey_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.passkey);
            break;
            case BLE_GAP_OPT_AUTH_PAYLOAD_TIMEOUT:
                fp_decoder = ble_gap_opt_auth_payload_timeout_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.auth_payload_timeout);
            break;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
            case BLE_GAP_OPT_EXT_LEN:
                fp_decoder = ble_gap_opt_ext_len_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.ext_len);
            break;
#endif
            case BLE_GAP_OPT_SCAN_REQ_REPORT:
                fp_decoder = ble_gap_opt_scan_req_report_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.scan_req_report);
            break;
#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
            case BLE_GAP_OPT_COMPAT_MODE:
                fp_decoder = ble_gap_opt_compat_mode_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.compat_mode);
            break;
#else
            case BLE_GAP_OPT_COMPAT_MODE_1:
                fp_decoder = ble_gap_opt_compat_mode_1_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.compat_mode_1);
            break;
            case BLE_GAP_OPT_COMPAT_MODE_2:
                fp_decoder = ble_gap_opt_compat_mode_2_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.compat_mode_2);
            break;
            case BLE_GAP_OPT_SLAVE_LATENCY_DISABLE:
                fp_decoder = ble_gap_opt_slave_latency_disable_t_dec;
                p_struct   = &((*pp_opt)->gap_opt.slave_latency_disable);
            break;
#endif
            default:
                SER_ASSERT(NRF_ERROR_INVALID_PARAM,NRF_ERROR_INVALID_PARAM);
            break;
        }

        SER_PULL_FIELD(p_struct, fp_decoder);
    }

    SER_REQ_DEC_END;
}


uint32_t ble_opt_set_rsp_enc(uint32_t                return_code,
                             uint8_t * const         p_buf,
                             uint32_t * const        p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_OPT_SET);
}

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_tx_packet_count_get_req_dec(uint8_t const * const p_buf,
                                         uint16_t              packet_len,
                                         uint16_t      * const p_conn_handle,
                                         uint8_t * * const     pp_count)
{
    SER_REQ_DEC_BEGIN(SD_BLE_TX_PACKET_COUNT_GET);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_COND(pp_count, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_tx_packet_count_get_rsp_enc(uint32_t              return_code,
                                         uint8_t * const       p_buf,
                                         uint32_t * const      p_buf_len,
                                         uint8_t const * const p_count)
{
    SER_RSP_ENC_BEGIN(SD_BLE_TX_PACKET_COUNT_GET);
    SER_PUSH_COND(p_count, uint8_t_enc);
    SER_RSP_ENC_END;
}
#endif

uint32_t ble_user_mem_reply_req_dec(uint8_t const * const          p_buf,
                                    uint32_t                       packet_len,
                                    uint16_t * const               p_conn_handle,
                                    ble_user_mem_block_t * * const pp_mem_block)
{
    SER_REQ_DEC_BEGIN(SD_BLE_USER_MEM_REPLY);

    SER_ASSERT_NOT_NULL(p_conn_handle);
    SER_ASSERT_NOT_NULL(pp_mem_block);
    SER_ASSERT_NOT_NULL(*pp_mem_block);

    SER_PULL_uint16(p_conn_handle);
    SER_PULL_COND(pp_mem_block, ble_user_mem_block_t_dec);

    SER_REQ_DEC_END;
}


uint32_t ble_user_mem_reply_rsp_enc(uint32_t         return_code,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_USER_MEM_REPLY);
}

uint32_t ble_uuid_decode_req_dec(uint8_t const * const p_buf,
                                 uint32_t const        packet_len,
                                 uint8_t *             p_uuid_le_len,
                                 uint8_t * * const     pp_uuid_le,
                                 ble_uuid_t * * const  pp_uuid)
{
    SER_REQ_DEC_BEGIN(SD_BLE_UUID_DECODE);

    SER_PULL_len8data(pp_uuid_le, p_uuid_le_len);
    SER_PULL_COND(pp_uuid, NULL);

    SER_REQ_DEC_END;
}

uint32_t ble_uuid_decode_rsp_enc(uint32_t                 return_code,
                                 uint8_t * const          p_buf,
                                 uint32_t * const         p_buf_len,
                                 ble_uuid_t const * const p_uuid)
{
    SER_RSP_ENC_BEGIN(SD_BLE_UUID_DECODE);
    SER_PUSH_COND(p_uuid, ble_uuid_t_enc);
    SER_RSP_ENC_END;
}

uint32_t ble_uuid_encode_req_dec(uint8_t const * const p_buf,
                                 uint16_t              packet_len,
                                 ble_uuid_t * * const  pp_uuid,
                                 uint8_t * * const     pp_uuid_le_len,
                                 uint8_t * * const     pp_uuid_le)
{
    SER_REQ_DEC_BEGIN(SD_BLE_UUID_ENCODE);

    SER_ASSERT_NOT_NULL(pp_uuid);
    SER_ASSERT_NOT_NULL(pp_uuid_le_len);
    SER_ASSERT_NOT_NULL(pp_uuid_le);
    SER_ASSERT_NOT_NULL(*pp_uuid);
    SER_ASSERT_NOT_NULL(*pp_uuid_le_len);
    SER_ASSERT_NOT_NULL(*pp_uuid_le);

    SER_PULL_COND(pp_uuid, ble_uuid_t_dec);
    SER_PULL_COND(pp_uuid_le_len, NULL);
    SER_PULL_COND(pp_uuid_le, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_uuid_encode_rsp_enc(uint32_t              return_code,
                                 uint8_t * const       p_buf,
                                 uint32_t * const      p_buf_len,
                                 uint8_t               uuid_le_len,
                                 uint8_t const * const p_uuid_le)
{
    SER_RSP_ENC_BEGIN(SD_BLE_UUID_ENCODE);

    SER_PUSH_uint8(&uuid_le_len);
    if (p_uuid_le != NULL)
    {
        SER_PUSH_uint8array(p_uuid_le, uuid_le_len);
    }

    SER_RSP_ENC_END;
}

uint32_t ble_uuid_vs_add_req_dec(uint8_t const * const   p_buf,
                                 uint16_t                packet_len,
                                 ble_uuid128_t * * const pp_uuid,
                                 uint8_t * * const       pp_uuid_type)
{
    SER_REQ_DEC_BEGIN(SD_BLE_UUID_VS_ADD);

    SER_ASSERT_NOT_NULL(pp_uuid);
    SER_ASSERT_NOT_NULL(pp_uuid_type);
    SER_ASSERT_NOT_NULL(*pp_uuid);
    SER_ASSERT_NOT_NULL(*pp_uuid_type);

    SER_PULL_COND(pp_uuid, ble_uuid128_t_dec);
    SER_PULL_COND(pp_uuid_type, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_uuid_vs_add_rsp_enc(uint32_t              return_code,
                                 uint8_t * const       p_buf,
                                 uint32_t * const      p_buf_len,
                                 uint8_t const * const p_uuid_type)
{
    SER_RSP_ENC_BEGIN(SD_BLE_UUID_VS_ADD);
    SER_PUSH_COND(p_uuid_type, uint8_t_enc);
    SER_RSP_ENC_END;
}

uint32_t ble_version_get_req_dec(uint8_t const * const   p_buf,
                                 uint16_t                packet_len,
                                 ble_version_t * * const pp_version)
{
    SER_REQ_DEC_BEGIN(SD_BLE_VERSION_GET);

    SER_ASSERT_NOT_NULL(pp_version);
    SER_ASSERT_NOT_NULL(*pp_version);

    SER_PULL_COND(pp_version, NULL);

    SER_REQ_DEC_END;
}


uint32_t ble_version_get_rsp_enc(uint32_t                    return_code,
                                 uint8_t * const             p_buf,
                                 uint32_t * const            p_buf_len,
                                 ble_version_t const * const p_version)
{
    SER_RSP_ENC_BEGIN(SD_BLE_VERSION_GET);
    SER_PUSH_FIELD(p_version, ble_version_t_enc);
    SER_RSP_ENC_END;
}



uint32_t ble_opt_id_pre_dec(uint8_t const * const   p_buf,
                            uint16_t                packet_len,
                            uint32_t *  const       p_opt_id)
{
    SER_REQ_DEC_BEGIN(SD_BLE_OPT_SET);

    SER_ASSERT_NOT_NULL(p_opt_id);
    SER_PULL_uint32(p_opt_id);

    // Pre-decoding; do not check if the whole packet was processed.
    return NRF_SUCCESS;
}
#if NRF_SD_BLE_API_VERSION >= 4

uint32_t ble_cfg_set_req_dec(uint8_t const * const p_buf,
                            uint32_t               packet_len,
                            uint32_t *             p_cfg_id,
                            ble_cfg_t * * const    pp_cfg)
{
    SER_REQ_DEC_BEGIN(SD_BLE_CFG_SET);
    SER_PULL_uint32(p_cfg_id);
    SER_PULL_COND(pp_cfg, NULL);

    if (*pp_cfg)
    {

        field_decoder_handler_t fp_decoder = NULL;
        void * p_struct = NULL;

        switch(*p_cfg_id)
        {
            case BLE_CONN_CFG_GAP:
                fp_decoder = ble_gap_conn_cfg_t_dec;
                p_struct   = &((*pp_cfg)->conn_cfg.params.gap_conn_cfg);
                break;
            case BLE_CONN_CFG_GATTC:
                fp_decoder = ble_gattc_conn_cfg_t_dec;
                p_struct   = &((*pp_cfg)->conn_cfg.params.gattc_conn_cfg);
                break;
            case BLE_CONN_CFG_GATTS:
                fp_decoder = ble_gatts_conn_cfg_t_dec;
                p_struct   = &((*pp_cfg)->conn_cfg.params.gatts_conn_cfg);
                break;
            case BLE_CONN_CFG_GATT:
                fp_decoder = ble_gatt_conn_cfg_t_dec;
                p_struct   = &((*pp_cfg)->conn_cfg.params.gatt_conn_cfg);
                break;
            case BLE_COMMON_CFG_VS_UUID:
                fp_decoder = ble_common_cfg_vs_uuid_t_dec;
                p_struct   = &((*pp_cfg)->common_cfg.vs_uuid_cfg);
                break;
            case BLE_GAP_CFG_ROLE_COUNT:
                fp_decoder = ble_gap_cfg_role_count_t_dec;
                p_struct   = &((*pp_cfg)->gap_cfg.role_count_cfg);
                break;
            case BLE_GAP_CFG_DEVICE_NAME:
                fp_decoder = ble_gap_cfg_device_name_t_dec;
                p_struct   = &((*pp_cfg)->gap_cfg.device_name_cfg);
                break;
            case BLE_GATTS_CFG_SERVICE_CHANGED:
                fp_decoder = ble_gatts_cfg_service_changed_t_dec;
                p_struct   = &((*pp_cfg)->gatts_cfg.service_changed);
                break;
            case BLE_GATTS_CFG_ATTR_TAB_SIZE:
                fp_decoder = ble_gatts_cfg_attr_tab_size_t_dec;
                p_struct   = &((*pp_cfg)->gatts_cfg.attr_tab_size);
                break;
            default:
                SER_ASSERT(NRF_ERROR_INVALID_PARAM,NRF_ERROR_INVALID_PARAM);
                break;
        }

        if (*p_cfg_id >= BLE_CONN_CFG_BASE && *p_cfg_id <= BLE_CONN_CFG_GATT)
        {
            SER_PULL_uint8(&(*pp_cfg)->conn_cfg.conn_cfg_tag);
        }
        SER_PULL_FIELD(p_struct, fp_decoder);
    }
    SER_REQ_DEC_END;
}



uint32_t ble_cfg_set_rsp_enc(uint32_t        return_code,
                            uint8_t * const  p_buf,
                            uint32_t * const p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_CFG_SET);
}

#endif
