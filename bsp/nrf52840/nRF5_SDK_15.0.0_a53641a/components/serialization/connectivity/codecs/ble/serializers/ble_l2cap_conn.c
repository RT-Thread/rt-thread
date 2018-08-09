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
#include <stdlib.h>
#include <string.h>
#include "ble_l2cap_conn.h"
#include "ble_serialization.h"
#include "ble_struct_serialization.h"
#include "ble_l2cap_struct_serialization.h"
#include "cond_field_serialization.h"
#include "conn_ble_l2cap_sdu_pool.h"
#include "app_util.h"


#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t ble_l2cap_cid_register_req_dec(uint8_t const * const p_buf,
                                        uint32_t              buf_len,
                                        uint16_t *            p_cid)
{
    uint32_t index    = 0;
    uint32_t err_code = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_cid);
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_LENGTH_EQ(3, buf_len);
    SER_ASSERT(p_buf[index] == SD_BLE_L2CAP_CID_REGISTER, NRF_ERROR_INVALID_PARAM);

    index++;
    err_code = uint16_t_dec(p_buf, buf_len, &index, p_cid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    SER_ASSERT_LENGTH_EQ(index, buf_len);

    return err_code;
}


uint32_t ble_l2cap_cid_register_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len)
{
    return ser_ble_cmd_rsp_status_code_enc(SD_BLE_L2CAP_CID_REGISTER, return_code,
                                           p_buf, p_buf_len);
}

uint32_t ble_l2cap_cid_unregister_req_dec(uint8_t const * const p_buf,
                                          uint32_t              buf_len,
                                          uint16_t *            p_cid)
{
    uint32_t index    = 0;
    uint32_t err_code = NRF_SUCCESS;

    SER_ASSERT_NOT_NULL(p_cid);
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_LENGTH_EQ(3, buf_len);
    SER_ASSERT(p_buf[index] == SD_BLE_L2CAP_CID_UNREGISTER, NRF_ERROR_INVALID_PARAM);

    index++;
    err_code = uint16_t_dec(p_buf, buf_len, &index, p_cid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    SER_ASSERT_LENGTH_EQ(index, buf_len);

    return err_code;
}


uint32_t ble_l2cap_cid_unregister_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len)
{
    return ser_ble_cmd_rsp_status_code_enc(SD_BLE_L2CAP_CID_UNREGISTER, return_code,
                                           p_buf, p_buf_len);
}


uint32_t ble_l2cap_tx_req_dec(uint8_t const * const        p_buf,
                              uint32_t const               buf_len,
                              uint16_t *                   p_conn_handle,
                              ble_l2cap_header_t * * const pp_l2cap_header,
                              uint8_t const * *            pp_data)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_conn_handle);
    SER_ASSERT_NOT_NULL(pp_l2cap_header);
    SER_ASSERT_NOT_NULL(*pp_l2cap_header);
    SER_ASSERT_NOT_NULL(pp_data);
    //SER_ASSERT_NOT_NULL(*pp_data);

    uint32_t err_code = NRF_SUCCESS;
    uint32_t index    = SER_CMD_DATA_POS;

    err_code = uint16_t_dec(p_buf, buf_len, &index, p_conn_handle);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = cond_field_dec(p_buf, buf_len, &index, (void * *)pp_l2cap_header,
                              ble_l2cap_header_t_dec);

    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    if (*pp_l2cap_header != NULL)
    {
        *pp_data = p_buf + index + 1;
        index   += 1 + (*pp_l2cap_header)->len;
    }
    else
    {
        *pp_data = NULL;
        index++;
    }

    SER_ASSERT_LENGTH_EQ(index, buf_len);

    return err_code;
}

uint32_t ble_l2cap_tx_rsp_enc(uint32_t         return_code,
                              uint8_t * const  p_buf,
                              uint32_t * const p_buf_len)
{
    return ser_ble_cmd_rsp_status_code_enc(SD_BLE_L2CAP_TX, return_code,
                                           p_buf, p_buf_len);
}
#endif

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t ble_l2cap_ch_setup_req_dec(uint8_t const * const                  p_buf,
                                    uint16_t                               packet_len,
                                    uint16_t *                             p_conn_handle,
                                    uint16_t * *                           pp_local_cid,
                                    ble_l2cap_ch_setup_params_t  * * const pp_params)
{
    SER_REQ_DEC_BEGIN(SD_BLE_L2CAP_CH_SETUP);
    SER_PULL_uint16(p_conn_handle);
    SER_PULL_COND(pp_local_cid, uint16_t_dec);
    SER_PULL_COND(pp_params, ble_l2cap_ch_setup_params_t_dec);

    if (*pp_params && (*pp_params)->rx_params.sdu_buf.p_data)
    {
        SER_ASSERT_LENGTH_LEQ((*pp_params)->rx_params.sdu_buf.len, CONN_BLE_L2CAP_SDU_MAX_BUFFER_SIZE);
        uint8_t * p_data = conn_ble_l2cap_sdu_pool_alloc((*pp_params)->rx_params.sdu_buf.len,
                                                  (uint32_t)((*pp_params)->rx_params.sdu_buf.p_data));
        (*pp_params)->rx_params.sdu_buf.p_data = p_data;
    }
    SER_REQ_DEC_END;
}

uint32_t ble_l2cap_ch_setup_rsp_enc(uint32_t          return_code,
                                    uint8_t * const   p_buf,
                                    uint32_t * const  p_buf_len,
                                    uint16_t * p_local_cid)
{
    SER_RSP_ENC_BEGIN(SD_BLE_L2CAP_CH_SETUP);

    SER_PUSH_COND(p_local_cid, uint16_t_enc);
    SER_RSP_ENC_END;
}

uint32_t ble_l2cap_ch_release_req_dec(uint8_t const * const p_buf,
                                      uint16_t              packet_len,
                                      uint16_t *            p_conn_handle,
                                      uint16_t *            p_local_cid)
{
    SER_REQ_DEC_BEGIN(SD_BLE_L2CAP_CH_RELEASE);
    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_local_cid);
    SER_REQ_DEC_END;
}


uint32_t ble_l2cap_ch_release_rsp_enc(uint32_t          return_code,
                                      uint8_t * const   p_buf,
                                      uint32_t * const  p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_L2CAP_CH_RELEASE);
}

uint32_t ble_l2cap_ch_rx_req_dec(uint8_t const * const p_buf,
                                 uint16_t              packet_len,
                                 uint16_t *            p_conn_handle,
                                 uint16_t *            p_local_cid,
                                 ble_data_t * *        pp_sdu_buf)
{
    SER_REQ_DEC_BEGIN(SD_BLE_L2CAP_CH_RX);
    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_local_cid);

    uint8_t * p_tmp = (uint8_t *)1;
    SER_PULL_COND(&p_tmp, NULL);
    if (p_tmp)
    {
        SER_PULL_uint16((uint16_t*)&(*pp_sdu_buf)->len);
        uint32_t addr;
        SER_PULL_uint32(&addr);
        SER_ASSERT_LENGTH_LEQ((*pp_sdu_buf)->len, CONN_BLE_L2CAP_SDU_MAX_BUFFER_SIZE);
        uint8_t * p_data = conn_ble_l2cap_sdu_pool_alloc((*pp_sdu_buf)->len, addr);
        (*pp_sdu_buf)->p_data = p_data;
    }
    else
    {
        *pp_sdu_buf = NULL;
    }

    SER_REQ_DEC_END;
}


uint32_t ble_l2cap_ch_rx_rsp_enc(uint32_t          return_code,
                                 uint8_t * const   p_buf,
                                 uint32_t * const  p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_L2CAP_CH_RX);
}

uint32_t ble_l2cap_ch_tx_req_dec(uint8_t const * const p_buf,
                                 uint16_t              packet_len,
                                 uint16_t *            p_conn_handle,
                                 uint16_t *            p_local_cid,
                                 ble_data_t * * const pp_sdu_buf)
{
    SER_REQ_DEC_BEGIN(SD_BLE_L2CAP_CH_TX);
    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_local_cid);

    uint8_t * p_tmp = (uint8_t *)1;
    SER_PULL_COND(&p_tmp, NULL);

    if (p_tmp)
    {
        uint32_t id;
        uint16_t len;
        SER_PULL_uint32(&id);
        SER_PULL_uint16(&len);

        SER_ASSERT_LENGTH_LEQ(len, CONN_BLE_L2CAP_SDU_MAX_BUFFER_SIZE);
        uint8_t * p_data = conn_ble_l2cap_sdu_pool_alloc(len, id);
        if (p_data)
        {
            SER_PULL_buf(&p_data, len, len);
        }
        (*pp_sdu_buf)->p_data = p_data;
        (*pp_sdu_buf)->len    = len;

    }
    else
    {
        *pp_sdu_buf = NULL;
    }

    SER_REQ_DEC_END;
}


uint32_t ble_l2cap_ch_tx_rsp_enc(uint32_t          return_code,
                                    uint8_t * const   p_buf,
                                    uint32_t * const  p_buf_len)
{
    SER_RSP_ENC_RESULT_ONLY(SD_BLE_L2CAP_CH_TX);
}

uint32_t ble_l2cap_ch_flow_control_req_dec(uint8_t const * const                  p_buf,
                                    uint16_t                               packet_len,
                                    uint16_t *                             p_conn_handle,
                                    uint16_t *                             p_local_cid,
                                    uint16_t *                             p_credits,
                                    uint16_t * *                           pp_credits)
{
    SER_REQ_DEC_BEGIN(SD_BLE_L2CAP_CH_FLOW_CONTROL);
    SER_PULL_uint16(p_conn_handle);
    SER_PULL_uint16(p_local_cid);
    SER_PULL_uint16(p_credits);
    SER_PULL_COND(pp_credits, NULL);
    SER_REQ_DEC_END;
}


uint32_t ble_l2cap_ch_flow_control_rsp_enc(uint32_t          return_code,
                                    uint8_t * const   p_buf,
                                    uint32_t * const  p_buf_len,
                                    uint16_t const * const p_credits)
{
    SER_RSP_ENC_BEGIN(SD_BLE_L2CAP_CH_FLOW_CONTROL);

    SER_PUSH_COND(p_credits, uint16_t_enc);
    SER_RSP_ENC_END;
}
#endif //NRF_SD_BLE_API_VERSION >= 5
