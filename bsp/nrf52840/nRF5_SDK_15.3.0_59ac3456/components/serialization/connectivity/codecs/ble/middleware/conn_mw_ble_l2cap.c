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
#include "ble_l2cap_conn.h"
#include "conn_mw_ble_l2cap.h"
#include "ble_serialization.h"

#if defined(NRF_SD_BLE_API_VERSION) && NRF_SD_BLE_API_VERSION < 4
uint32_t conn_mw_ble_l2cap_cid_register(uint8_t const * const p_rx_buf,
                                        uint32_t              rx_buf_len,
                                        uint8_t * const       p_tx_buf,
                                        uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t cid;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_l2cap_cid_register_req_dec(p_rx_buf, rx_buf_len, &cid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_cid_register(cid);

    err_code = ble_l2cap_cid_register_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_l2cap_cid_unregister(uint8_t const * const p_rx_buf,
                                          uint32_t              rx_buf_len,
                                          uint8_t * const       p_tx_buf,
                                          uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t cid;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ble_l2cap_cid_unregister_req_dec(p_rx_buf, rx_buf_len, &cid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_cid_unregister(cid);

    err_code = ble_l2cap_cid_unregister_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ble_l2cap_tx(uint8_t const * const p_rx_buf,
                              uint32_t              rx_buf_len,
                              uint8_t * const       p_tx_buf,
                              uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t             conn_handle;
    ble_l2cap_header_t   l2cap_header;
    ble_l2cap_header_t * p_l2cap_header = &l2cap_header;
    uint32_t             err_code       = NRF_SUCCESS;
    uint32_t             sd_err_code;
    uint8_t const *      p_data = NULL;

    err_code = ble_l2cap_tx_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_l2cap_header, &p_data);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_tx(conn_handle, p_l2cap_header, p_data);

    err_code = ble_l2cap_tx_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
#endif

#if NRF_SD_BLE_API_VERSION >= 5
uint32_t conn_mw_l2cap_ch_setup(uint8_t const * const p_rx_buf,
                                uint32_t              rx_buf_len,
                                uint8_t * const       p_tx_buf,
                                uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t                      conn_handle;
    uint16_t                      local_cid;
    uint16_t * p_local_cid = &local_cid;
    ble_l2cap_ch_setup_params_t   params;
    ble_l2cap_ch_setup_params_t * p_params = &params;
    uint32_t                      sd_err_code;
    uint32_t                      err_code = NRF_SUCCESS;

    err_code = ble_l2cap_ch_setup_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &p_local_cid, &p_params);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_ch_setup(conn_handle, p_local_cid, p_params);

    err_code = ble_l2cap_ch_setup_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_local_cid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_l2cap_ch_release(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t conn_handle;
    uint16_t local_cid;
    uint32_t sd_err_code;
    uint32_t err_code = NRF_SUCCESS;

    err_code = ble_l2cap_ch_release_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &local_cid);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_ch_release(conn_handle, local_cid);

    err_code = ble_l2cap_ch_release_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_l2cap_ch_rx(uint8_t const * const p_rx_buf,
                             uint32_t              rx_buf_len,
                             uint8_t * const       p_tx_buf,
                             uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t     conn_handle;
    uint16_t     local_cid;
    ble_data_t   ble_data;
    ble_data_t * p_ble_data = &ble_data;
    uint32_t     sd_err_code;
    uint32_t     err_code = NRF_SUCCESS;

    err_code = ble_l2cap_ch_rx_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &local_cid, &p_ble_data);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_ch_rx(conn_handle, local_cid, p_ble_data);

    err_code = ble_l2cap_ch_rx_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_l2cap_ch_tx(uint8_t const * const p_rx_buf,
                             uint32_t              rx_buf_len,
                             uint8_t * const       p_tx_buf,
                             uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t     conn_handle;
    uint16_t     local_cid;
    ble_data_t   ble_data;
    ble_data_t * p_ble_data = &ble_data;
    uint32_t     sd_err_code;
    uint32_t     err_code = NRF_SUCCESS;

    err_code = ble_l2cap_ch_tx_req_dec(p_rx_buf, rx_buf_len, &conn_handle, &local_cid, &p_ble_data);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_ch_tx(conn_handle, local_cid, p_ble_data);

    err_code = ble_l2cap_ch_tx_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_l2cap_ch_flow_control(uint8_t const * const p_rx_buf,
                                       uint32_t              rx_buf_len,
                                       uint8_t * const       p_tx_buf,
                                       uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint16_t   conn_handle;
    uint16_t   local_cid;
    uint16_t   credits;
    uint16_t   out_credits;
    uint16_t * p_out_credits = &out_credits;
    uint32_t   sd_err_code;
    uint32_t   err_code = NRF_SUCCESS;

    err_code = ble_l2cap_ch_flow_control_req_dec(p_rx_buf, rx_buf_len,
                                                &conn_handle, &local_cid, &credits, &p_out_credits);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ble_l2cap_ch_flow_control(conn_handle, local_cid, credits, p_out_credits);

    err_code = ble_l2cap_ch_flow_control_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_out_credits);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

#endif
