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
#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "app_error.h"
#include "ble_serialization.h"
#include "ser_config.h"
#include "conn_mw.h"
#include "ser_hal_transport.h"
#include "ser_conn_cmd_decoder.h"
#include "ser_conn_handlers.h"
#include "nrf_log_ctrl.h"

#define NRF_LOG_MODULE_NAME ser_conn_dec
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

uint32_t ser_conn_command_process(uint8_t * p_command, uint16_t command_len)
{
    SER_ASSERT_NOT_NULL(p_command);
    SER_ASSERT_LENGTH_LEQ(SER_OP_CODE_SIZE, command_len);

    uint32_t  err_code   = NRF_SUCCESS;
    uint8_t * p_tx_buf   = NULL;
    uint32_t  tx_buf_len = 0;
    uint8_t   opcode     = p_command[SER_CMD_OP_CODE_POS];
    uint32_t  index      = 0;

    /* Allocate a memory buffer from HAL Transport layer for transmitting the Command Response.
     * Loop until a buffer is available. */
    NRF_LOG_INFO("Command process start");
    do
    {
        err_code = ser_hal_transport_tx_pkt_alloc(&p_tx_buf, (uint16_t *)&tx_buf_len);
        if (err_code == NRF_ERROR_NO_MEM)
        {
            ser_conn_on_no_mem_handler();
        }
    }
    while (NRF_ERROR_NO_MEM == err_code);

    NRF_LOG_INFO("Tx buffer allocated");
    if (NRF_SUCCESS == err_code)
    {
        /* Create a new response packet. */
        p_tx_buf[SER_PKT_TYPE_POS] = SER_PKT_TYPE_RESP;
        tx_buf_len                -= SER_PKT_TYPE_SIZE;

        /* Decode a request, pass a memory for a response command (opcode + data) and encode it. */
        err_code = conn_mw_handler
                       (p_command, command_len, &p_tx_buf[SER_PKT_OP_CODE_POS], &tx_buf_len);


        /* Command decoder not found. */
        if (NRF_ERROR_NOT_SUPPORTED == err_code)
        {
            NRF_LOG_ERROR("Command not supported opcode:%d", p_tx_buf[SER_PKT_OP_CODE_POS]);
            APP_ERROR_CHECK(SER_WARNING_CODE);
            err_code = op_status_enc
                           (opcode, NRF_ERROR_NOT_SUPPORTED,
                           &p_tx_buf[SER_PKT_OP_CODE_POS], &tx_buf_len, &index);
            if (NRF_SUCCESS == err_code)
            {
                tx_buf_len += SER_PKT_TYPE_SIZE;
                err_code   = ser_hal_transport_tx_pkt_send(p_tx_buf, (uint16_t)tx_buf_len);
                /* TX buffer is going to be freed automatically in the HAL Transport layer. */
                if (NRF_SUCCESS != err_code)
                {
                    err_code = NRF_ERROR_INTERNAL;
                }
            }
            else
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }
        else if (NRF_SUCCESS == err_code) /* Send a response. */
        {
            tx_buf_len += SER_PKT_TYPE_SIZE;
            err_code    = ser_hal_transport_tx_pkt_send(p_tx_buf, (uint16_t)tx_buf_len);

            /* TX buffer is going to be freed automatically in the HAL Transport layer. */
            if (NRF_SUCCESS != err_code)
            {
                err_code = NRF_ERROR_INTERNAL;
            }
        }
        else
        {
            NRF_LOG_ERROR("Internal error during command decoding.");
            err_code = NRF_ERROR_INTERNAL;
        }
    }
    else
    {
        err_code = NRF_ERROR_INTERNAL;
    }

    return err_code;
}
