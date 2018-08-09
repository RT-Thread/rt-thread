/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#include "ant_parameters.h"
#include "nrf_sdh_ant.h"
#include "ant_struct_serialization.h"
#include "ble_serialization.h"
#include "ant_event_rx.h"
#include "app_util.h"
#include "cond_field_serialization.h"


uint32_t ant_event_enc(ant_evt_t const * const p_event,
                       uint32_t                event_len,
                       uint8_t * const         p_buf,
                       uint32_t * const        p_buf_len)
{
    uint32_t ret_val = NRF_SUCCESS;
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);
    SER_ASSERT_NOT_NULL(p_event);

    switch (p_event->event)
    {
        case NO_EVENT:
        case EVENT_RX_SEARCH_TIMEOUT:
        case EVENT_RX_FAIL:
        case EVENT_TRANSFER_RX_FAILED:
        case EVENT_TRANSFER_TX_COMPLETED:
        case EVENT_TRANSFER_TX_FAILED:
        case EVENT_CHANNEL_CLOSED:
        case EVENT_RX_FAIL_GO_TO_SEARCH:
        case EVENT_CHANNEL_COLLISION:
        case EVENT_TRANSFER_TX_START:
        case EVENT_TRANSFER_NEXT_DATA_BLOCK:
        case CHANNEL_IN_WRONG_STATE:
        case CHANNEL_NOT_OPENED:
        case CHANNEL_ID_NOT_SET:
        case CLOSE_ALL_CHANNELS:
        case TRANSFER_IN_PROGRESS:
        case TRANSFER_SEQUENCE_NUMBER_ERROR:
        case TRANSFER_IN_ERROR:
        case TRANSFER_BUSY:
        case MESSAGE_SIZE_EXCEEDS_LIMIT:
        case INVALID_MESSAGE:
        case INVALID_NETWORK_NUMBER:
        case INVALID_LIST_ID:
        case INVALID_SCAN_TX_CHANNEL:
        case INVALID_PARAMETER_PROVIDED:
        case EVENT_QUE_OVERFLOW:
        case EVENT_ENCRYPT_NEGOTIATION_SUCCESS:
        case EVENT_ENCRYPT_NEGOTIATION_FAIL:
        case EVENT_RFACTIVE_NOTIFICATION:
        case EVENT_CONNECTION_START:
        case EVENT_CONNECTION_SUCCESS:
        case EVENT_CONNECTION_FAIL:
        case EVENT_CONNECTION_TIMEOUT:
        case EVENT_CONNECTION_UPDATE:
        case NO_RESPONSE_MESSAGE:
        case EVENT_RX:
        case EVENT_BLOCKED:
        case EVENT_TX:
        {
            uint32_t index = 0;
            // TO DO - SER_ASSERT_LENGTH_LEQ(index + SER_EVT_HEADER_SIZE + 2 + 1, *p_buf_len);
            uint32_t err_code = ant_evt_t_enc(p_event, p_buf, *p_buf_len, &index);
            SER_ASSERT(err_code == NRF_SUCCESS, err_code);
            *p_buf_len = index;
            break;
        }
        default:
            ret_val = NRF_ERROR_NOT_SUPPORTED;
            break;
    }

    return ret_val;
}
