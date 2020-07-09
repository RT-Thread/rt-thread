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
#include <stdint.h>
#include "app_error.h"
#include "ble_dtm_app.h"
#include "ble_serialization.h"
#include "nrf_error.h"
#include "ser_config.h"
#include "ser_hal_transport.h"
#include "ser_sd_transport.h"


static uint32_t dtm_init_rsp_dec(const uint8_t * p_buffer, uint16_t length)
{
    uint32_t result_code;

    const uint32_t err_code = ble_dtm_init_rsp_dec(p_buffer, length, &result_code);
    APP_ERROR_CHECK(err_code);

    return result_code;
}


uint32_t ble_dtm_init(app_uart_stream_comm_params_t * p_uart_comm_params)
{
    if (p_uart_comm_params == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t err_code = NRF_SUCCESS;
    uint32_t index = 0;

    uint8_t * p_tx_buf = NULL;
    uint32_t tx_buf_len = 0;

    err_code = ser_hal_transport_tx_pkt_alloc(&p_tx_buf, (uint16_t *)&tx_buf_len);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    p_tx_buf[index++] = SER_PKT_TYPE_DTM_CMD;
    tx_buf_len -= SER_PKT_TYPE_SIZE;

    err_code = ble_dtm_init_req_enc(p_uart_comm_params, &(p_tx_buf[SER_PKT_TYPE_SIZE]), &tx_buf_len);
    if (err_code == NRF_SUCCESS)
    {
        tx_buf_len += SER_PKT_TYPE_SIZE;

        err_code = ser_sd_transport_cmd_write(p_tx_buf, tx_buf_len, dtm_init_rsp_dec);
        if (err_code != NRF_SUCCESS)
        {
            err_code = NRF_ERROR_INTERNAL;
        }
    }
    else
    {
        err_code = NRF_ERROR_INTERNAL;
    }

    return err_code;
}
