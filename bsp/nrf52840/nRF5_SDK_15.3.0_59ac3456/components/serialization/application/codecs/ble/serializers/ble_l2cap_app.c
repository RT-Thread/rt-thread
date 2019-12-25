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
#include <string.h>
#include "ble_l2cap_app.h"
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_l2cap_struct_serialization.h"
#include "ble_gap.h"
#include "app_util.h"
#include "cond_field_serialization.h"

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_l2cap_cid_register_req_enc(uint16_t         cid,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len)
{
    uint32_t index    = 0;
    uint32_t err_code = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);

    SER_ASSERT_LENGTH_LEQ(index + 3, *p_buf_len);

    p_buf[index++] = SD_BLE_L2CAP_CID_REGISTER;
    err_code       = uint16_t_enc(&cid, p_buf, *p_buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    *p_buf_len = index;

    return err_code;
}

uint32_t ble_l2cap_cid_register_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        uint32_t * const      p_result_code)
{
    return ser_ble_cmd_rsp_dec(p_buf, packet_len, SD_BLE_L2CAP_CID_REGISTER, p_result_code);
}

uint32_t ble_l2cap_cid_unregister_req_enc(uint16_t         cid,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len)
{
    uint32_t index    = 0;
    uint32_t err_code = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);

    SER_ASSERT_LENGTH_LEQ(index + 3, *p_buf_len);

    p_buf[index++] = SD_BLE_L2CAP_CID_UNREGISTER;
    err_code       = uint16_t_enc(&cid, p_buf, *p_buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    *p_buf_len = index;

    return err_code;
}

uint32_t ble_l2cap_cid_unregister_rsp_dec(uint8_t const * const p_buf,
                                          uint32_t              packet_len,
                                          uint32_t * const      p_result_code)
{
    return ser_ble_cmd_rsp_dec(p_buf, packet_len, SD_BLE_L2CAP_CID_UNREGISTER, p_result_code);
}


uint32_t ble_l2cap_tx_req_enc(uint16_t                         conn_handle,
                              ble_l2cap_header_t const * const p_l2cap_header,
                              uint8_t const * const            p_data,
                              uint8_t * const                  p_buf,
                              uint32_t * const                 p_buf_len)
{
    uint32_t index    = 0;
    uint32_t err_code = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);

    SER_ASSERT_LENGTH_LEQ(1, *p_buf_len);
    p_buf[index++] = SD_BLE_L2CAP_TX;

    err_code = uint16_t_enc(&conn_handle, p_buf, *p_buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = cond_field_enc(p_l2cap_header, p_buf, *p_buf_len, &index, ble_l2cap_header_t_enc);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    if (p_l2cap_header != NULL)
    {
        err_code = buf_enc(p_data, p_l2cap_header->len, p_buf, *p_buf_len, &index);
    }
    else
    {
        err_code = buf_enc(NULL, 0, p_buf, *p_buf_len, &index);
    }

    *p_buf_len = index;

    return err_code;
}

uint32_t ble_l2cap_tx_rsp_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              uint32_t * const      p_result_code)
{
    return ser_ble_cmd_rsp_dec(p_buf, packet_len, SD_BLE_L2CAP_TX, p_result_code);
}
#endif

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_l2cap_ch_setup_req_enc(uint16_t conn_handle,
                                    uint16_t * p_local_cid,
                                    ble_l2cap_ch_setup_params_t const *p_params,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_L2CAP_CH_SETUP);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_COND(p_local_cid, uint16_t_enc);
    SER_PUSH_COND(p_params, ble_l2cap_ch_setup_params_t_enc);

    SER_REQ_ENC_END;
}

uint32_t ble_l2cap_ch_setup_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint16_t *            p_local_cid,
                                    uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_L2CAP_CH_SETUP);
    SER_PULL_COND((void **)&p_local_cid, uint16_t_dec);
    SER_RSP_DEC_END;
}

uint32_t ble_l2cap_ch_release_req_enc(uint16_t conn_handle,
                                      uint16_t local_cid,
                                      uint8_t * const  p_buf,
                                      uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_L2CAP_CH_RELEASE);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&local_cid);

    SER_REQ_ENC_END;
}

uint32_t ble_l2cap_ch_release_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_L2CAP_CH_RELEASE);
}

uint32_t ble_l2cap_ch_rx_req_enc(uint16_t conn_handle,
                                 uint16_t local_cid,
                                 ble_data_t const *p_sdu_buf,
                                 uint8_t * const  p_buf,
                                 uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_L2CAP_CH_RX);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&local_cid);

    SER_PUSH_COND(p_sdu_buf, NULL);
    if (p_sdu_buf)
    {
       SER_PUSH_uint16(&p_sdu_buf->len);
       SER_PUSH_uint32(&p_sdu_buf->p_data);
    }

    SER_REQ_ENC_END;
}

uint32_t ble_l2cap_ch_rx_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_L2CAP_CH_RX);
}

uint32_t ble_l2cap_ch_tx_req_enc(uint16_t conn_handle,
                                 uint16_t local_cid,
                                 ble_data_t const *p_sdu_buf,
                                 uint8_t * const  p_buf,
                                 uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_L2CAP_CH_TX);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&local_cid);

    SER_PUSH_COND(p_sdu_buf, NULL);
    if (p_sdu_buf)
    {
       SER_PUSH_uint32(&p_sdu_buf->p_data);
       SER_PUSH_uint16(&p_sdu_buf->len);
       SER_PUSH_buf(p_sdu_buf->p_data, p_sdu_buf->len);
    }

    SER_REQ_ENC_END;
}

uint32_t ble_l2cap_ch_tx_rsp_dec(uint8_t const * const p_buf,
                                 uint32_t              packet_len,
                                 uint32_t * const      p_result_code)
{
    SER_RSP_DEC_RESULT_ONLY(SD_BLE_L2CAP_CH_TX);
}

uint32_t ble_l2cap_ch_flow_control_req_enc(uint16_t conn_handle,
                                           uint16_t local_cid,
                                           uint16_t credits,
                                           uint16_t *p_credits,
                                           uint8_t * const  p_buf,
                                           uint32_t * const p_buf_len)
{
    SER_REQ_ENC_BEGIN(SD_BLE_L2CAP_CH_FLOW_CONTROL);

    SER_PUSH_uint16(&conn_handle);
    SER_PUSH_uint16(&local_cid);
    SER_PUSH_uint16(&credits);
    SER_PUSH_COND(p_credits, NULL);

    SER_REQ_ENC_END;
}

uint32_t ble_l2cap_ch_flow_control_rsp_dec(uint8_t const * const p_buf,
                                           uint32_t              packet_len,
                                           uint16_t *            p_credits,
                                           uint32_t * const      p_result_code)
{
    SER_RSP_DEC_BEGIN(SD_BLE_L2CAP_CH_FLOW_CONTROL);
    SER_PULL_COND((void **)&p_credits, uint16_t_dec);
    SER_RSP_DEC_END;
}
#endif //NRF_SD_BLE_API_VERSION >= 5
