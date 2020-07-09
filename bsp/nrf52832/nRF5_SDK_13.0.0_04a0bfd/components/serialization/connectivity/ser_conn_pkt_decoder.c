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
#include <string.h>
#include "nordic_common.h"
#include "app_error.h"
#include "softdevice_handler.h"
#include "ble_serialization.h"
#include "ser_config.h"
#include "ser_hal_transport.h"
#include "ser_conn_pkt_decoder.h"
#include "ser_conn_cmd_decoder.h"
#include "ser_conn_dtm_cmd_decoder.h"
#include "ser_conn_reset_cmd_decoder.h"
#include "ser_dbg_sd_str.h"

#define NRF_LOG_MODULE_NAME "SER_CONN"
#include "nrf_log.h"


uint32_t ser_conn_received_pkt_process(
    ser_hal_transport_evt_rx_pkt_received_params_t * p_rx_pkt_params)
{
    uint32_t err_code = NRF_SUCCESS;

    if (NULL != p_rx_pkt_params)
    {
        /* For further processing pass only command (opcode + data).  */
        uint8_t * p_command   = &p_rx_pkt_params->p_buffer[SER_PKT_OP_CODE_POS];
        uint16_t  command_len = p_rx_pkt_params->num_of_bytes - SER_PKT_TYPE_SIZE;

        NRF_LOG_DEBUG("[SD_CALL]:%s\r\n",
            (uint32_t)ser_dbg_sd_call_str_get(*p_command));

        switch (p_rx_pkt_params->p_buffer[SER_PKT_TYPE_POS])
        {
        #if defined(ANT_STACK_SUPPORT_REQD)
            case SER_PKT_TYPE_ANT_CMD:
            //!! INTENTIONAL FALLTHROUGH
        #endif
            case SER_PKT_TYPE_CMD:
            {
                err_code = ser_conn_command_process(p_command, command_len);
                break;
            }

            case SER_PKT_TYPE_DTM_CMD:
            {
                err_code = ser_conn_dtm_command_process(p_command, command_len);
                break;
            }

            case SER_PKT_TYPE_RESET_CMD:
            {
                ser_conn_reset_command_process();
                break;
            }

            default:
            {
                APP_ERROR_CHECK(SER_WARNING_CODE);
                break;
            }
        }

        if (NRF_SUCCESS == err_code)
        {
            /* Free a received packet. */
            err_code = ser_hal_transport_rx_pkt_free(p_rx_pkt_params->p_buffer);

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
    else
    {
        err_code = NRF_ERROR_NULL;
    }

    return err_code;
}
