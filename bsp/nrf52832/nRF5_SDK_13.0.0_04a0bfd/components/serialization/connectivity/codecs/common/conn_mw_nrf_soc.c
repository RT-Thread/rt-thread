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
#include "nrf_soc_conn.h"
#include "conn_mw_nrf_soc.h"
#include "ble_serialization.h"

uint32_t conn_mw_power_system_off(uint8_t const * const p_rx_buf,
                                  uint32_t              rx_buf_len,
                                  uint8_t * const       p_tx_buf,
                                  uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    uint32_t err_code = NRF_SUCCESS;

    err_code = power_system_off_req_dec(p_rx_buf, rx_buf_len);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = sd_power_system_off();
    /* There should be no return from sd_power_system_off() */

    return err_code;
}

uint32_t conn_mw_temp_get(uint8_t const * const p_rx_buf,
                          uint32_t              rx_buf_len,
                          uint8_t * const       p_tx_buf,
                          uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    int32_t   temperature;
    int32_t * p_temperature = &temperature;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = temp_get_req_dec(p_rx_buf, rx_buf_len, &p_temperature);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_temp_get(p_temperature);

    err_code = temp_get_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_temperature);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}

uint32_t conn_mw_ecb_block_encrypt(uint8_t const * const p_rx_buf,
                                   uint32_t              rx_buf_len,
                                   uint8_t * const       p_tx_buf,
                                   uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    nrf_ecb_hal_data_t ecb_data;
    nrf_ecb_hal_data_t * p_ecb_data = &ecb_data;

    uint32_t err_code = NRF_SUCCESS;
    uint32_t sd_err_code;

    err_code = ecb_block_encrypt_req_dec(p_rx_buf, rx_buf_len, &p_ecb_data);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    sd_err_code = sd_ecb_block_encrypt(p_ecb_data);

    err_code = ecb_block_encrypt_rsp_enc(sd_err_code, p_tx_buf, p_tx_buf_len, p_ecb_data);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    return err_code;
}
