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
#include "app_util.h"
#include "ble_dtm_conn.h"
#include "ble_serialization.h"
#include "nrf_error.h"
#include "nrf_sdm.h"
#include "ser_conn_dtm_cmd_decoder.h"
#include "ser_conn_handlers.h"
#include "ser_hal_transport.h"

static bool                          m_is_ready_to_enter_dtm = false;
static app_uart_stream_comm_params_t m_comm_params           = { 0 };

uint32_t ser_conn_dtm_command_process(uint8_t * p_command, uint16_t command_len)
{
    SER_ASSERT_NOT_NULL(p_command);

    uint32_t  err_code   = NRF_SUCCESS;
    uint8_t * p_tx_buf   = NULL;
    uint32_t  tx_buf_len = 0;

    /* Allocate a memory buffer from HAL Transport layer for transmitting the Command Response.
     * Loop until a buffer is available. */
    do
    {
        err_code = ser_hal_transport_tx_pkt_alloc(&p_tx_buf, (uint16_t *)&tx_buf_len);
        if (err_code == NRF_ERROR_NO_MEM)
        {
            ser_conn_on_no_mem_handler();
        }
    }
    while (NRF_ERROR_NO_MEM == err_code);

    if (err_code == NRF_SUCCESS)
    {
        p_tx_buf[SER_PKT_TYPE_POS] = SER_PKT_TYPE_DTM_RESP;
        tx_buf_len                -= SER_PKT_TYPE_SIZE;

        err_code = ble_dtm_init_req_dec(p_command, command_len, &m_comm_params);

        if (NRF_SUCCESS == err_code)
        {
            err_code = ble_dtm_init_rsp_enc(NRF_SUCCESS,
                                            &p_tx_buf[SER_PKT_TYPE_SIZE],
                                            &tx_buf_len);

            if (err_code != NRF_SUCCESS)
            {
                return NRF_ERROR_INTERNAL;
            }

            tx_buf_len += SER_PKT_TYPE_SIZE;

            /* Set a flag that device is ready to enter DTM mode. */
            m_is_ready_to_enter_dtm = true;

            err_code = ser_hal_transport_tx_pkt_send(p_tx_buf, (uint16_t)tx_buf_len);
            if (err_code != NRF_SUCCESS)
            {
                err_code = NRF_ERROR_INTERNAL;
            }

            /* TX buffer is going to be freed automatically in the HAL Transport layer. */
        }
        else
        {
            err_code = NRF_ERROR_INTERNAL;
        }
    }

    return err_code;
}


void ser_conn_is_ready_to_enter_dtm(void)
{
    if (m_is_ready_to_enter_dtm)
    {
        /* Disable SoftDevice. */
        (void)sd_softdevice_disable();

        /* Close HAL Transport Layer. */
        ser_hal_transport_close();

        /* Start DTM mode. */
        (void)dtm_start(m_comm_params);
    }
}
