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
#include <stdint.h>
#include "app_error.h"
#include "app_scheduler.h"
#include "ble_serialization.h"
#include "ser_config.h"
#include "ser_hal_transport.h"
#include "ser_conn_event_encoder.h"

#ifdef BLE_STACK_SUPPORT_REQD
#include "ble_conn.h"
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
#include "ant_event.h"
#endif // ANT_STACK_SUPPORT_REQD

#ifdef BLE_STACK_SUPPORT_REQD
void ser_conn_ble_event_encoder(void * p_event_data, uint16_t event_size)
{
    if (NULL == p_event_data)
    {
        APP_ERROR_CHECK(NRF_ERROR_NULL);
    }
    UNUSED_PARAMETER(event_size);

    uint32_t    err_code   = NRF_SUCCESS;
    uint8_t *   p_tx_buf   = NULL;
    uint32_t    tx_buf_len = 0;
    ble_evt_t * p_ble_evt  = (ble_evt_t *)p_event_data;

    /* Allocate a memory buffer from HAL Transport layer for transmitting an event.
     * Loop until a buffer is available. */
    do
    {
        err_code = ser_hal_transport_tx_pkt_alloc(&p_tx_buf, (uint16_t *)&tx_buf_len);
    }
    while (err_code == NRF_ERROR_NO_MEM);
    APP_ERROR_CHECK(err_code);

    /* Create a new packet. */
    p_tx_buf[SER_PKT_TYPE_POS] = SER_PKT_TYPE_EVT;
    tx_buf_len                -= SER_PKT_TYPE_SIZE;

    /* Pass a memory for an event (opcode + data) and encode it. */
    err_code = ble_event_enc(p_ble_evt, 0, &p_tx_buf[SER_PKT_OP_CODE_POS], &tx_buf_len);

    if (NRF_ERROR_NOT_SUPPORTED != err_code)
    {
        APP_ERROR_CHECK(err_code);
        tx_buf_len += SER_PKT_TYPE_SIZE;
        err_code    = ser_hal_transport_tx_pkt_send(p_tx_buf, (uint16_t)tx_buf_len);
        APP_ERROR_CHECK(err_code);
        /* TX buffer is going to be freed automatically in the HAL Transport layer.
         * Scheduler must be paused because this function returns before a packet is physically sent
         * by transport layer. This can cause start processing of a next event from the application
         * scheduler queue. In result the next event reserves the TX buffer before the current
         * packet is sent. If in meantime a command arrives a command response cannot be sent in
         * result. Pausing the scheduler temporary prevents processing a next event. */
        app_sched_pause();
    }
    else
    {
        /* Event was NOT encoded, therefore the buffer is freed immediately. */
        err_code = ser_hal_transport_tx_pkt_free(p_tx_buf);
        APP_ERROR_CHECK(err_code);
        APP_ERROR_CHECK(SER_WARNING_CODE);
    }
}
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
void ser_conn_ant_event_encoder(void * p_event_data, uint16_t event_size)
{

    if (NULL == p_event_data)
    {
        APP_ERROR_CHECK(NRF_ERROR_NULL);
    }
    UNUSED_PARAMETER(event_size);

    uint32_t    err_code   = NRF_SUCCESS;
    uint8_t *   p_tx_buf   = NULL;
    uint32_t    tx_buf_len = 0;
    ant_evt_t * p_ant_evt  = (ant_evt_t *)p_event_data;

    /* Allocate a memory buffer from HAL Transport layer for transmitting an event.
     * Loop until a buffer is available. */
    do
    {
        err_code = ser_hal_transport_tx_pkt_alloc(&p_tx_buf, (uint16_t *)&tx_buf_len);
    }
    while (err_code == NRF_ERROR_NO_MEM);
    APP_ERROR_CHECK(err_code);

    /* Create a new packet. */
    p_tx_buf[SER_PKT_TYPE_POS] = SER_PKT_TYPE_ANT_EVT;
    tx_buf_len                -= SER_PKT_TYPE_SIZE;

    /* Pass a memory for an event (opcode + data) and encode it. */
    err_code = ant_event_enc(p_ant_evt, 0, &p_tx_buf[SER_PKT_OP_CODE_POS], &tx_buf_len);

    if (NRF_ERROR_NOT_SUPPORTED != err_code)
    {
        APP_ERROR_CHECK(err_code);
        tx_buf_len += SER_PKT_TYPE_SIZE;
        err_code    = ser_hal_transport_tx_pkt_send(p_tx_buf, (uint16_t)tx_buf_len);
        APP_ERROR_CHECK(err_code);
        /* TX buffer is going to be freed automatically in the HAL Transport layer.
         * Scheduler must be paused because this function returns before a packet is physically sent
         * by transport layer. This can cause start processing of a next event from the application
         * scheduler queue. In result the next event reserves the TX buffer before the current
         * packet is sent. If in meantime a command arrives a command response cannot be sent in
         * result. Pausing the scheduler temporary prevents processing a next event. */
        app_sched_pause();
    }
    else
    {
        /* Event was NOT encoded, therefore the buffer is freed immediately. */
        err_code = ser_hal_transport_tx_pkt_free(p_tx_buf);
        APP_ERROR_CHECK(err_code);
        APP_ERROR_CHECK(SER_WARNING_CODE);
    }

}
#endif
