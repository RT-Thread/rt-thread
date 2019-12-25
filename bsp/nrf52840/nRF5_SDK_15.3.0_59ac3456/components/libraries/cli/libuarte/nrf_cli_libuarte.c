/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#include "nrf_cli_libuarte.h"
#include "nrf_libuarte_async.h"
#include "nrf_assert.h"

#define NRF_LOG_MODULE_NAME cli_libuarte
#if NRF_CLI_LIBUARTE_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_CLI_LIBUARTE_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_CLI_LIBUARTE_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_CLI_LIBUARTE_CONFIG_DEBUG_COLOR
#else //NRF_CLI_LIBUARTE_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //NRF_CLI_LIBUARTE_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

static cli_libuarte_internal_t * mp_internal;
static bool m_uart_busy;

NRF_LIBUARTE_ASYNC_DEFINE(libuarte,
                          NRF_CLI_LIBUARTE_UARTE_INSTANCE,
                          NRF_CLI_LIBUARTE_TIMER_INSTANCE,
                          NRF_CLI_LIBUARTE_TIMEOUT_RTC_INSTANCE,
                          NRF_CLI_LIBUARTE_TIMEOUT_TIMER_INSTANCE,
                          3, 255);

static void uart_event_handler(void * context, nrf_libuarte_async_evt_t * p_event)
{
    cli_libuarte_internal_t * p_internal = mp_internal;
    ret_code_t err_code = NRF_SUCCESS;
    size_t len;
    UNUSED_VARIABLE(err_code);
    switch (p_event->type)
    {
        case NRF_LIBUARTE_ASYNC_EVT_ERROR:
            NRF_LOG_WARNING("(evt) ERROR");

            break;

        case NRF_LIBUARTE_ASYNC_EVT_RX_DATA:
        {
            len = (size_t)((uint32_t)p_event->data.rxtx.length & 0x0000FFFF);
            err_code = nrf_ringbuf_cpy_put(p_internal->p_rx_ringbuf,
                                           p_event->data.rxtx.p_data,
                                           &len);
            ASSERT(err_code == NRF_SUCCESS);

            if (len != p_event->data.rxtx.length)
            {
                NRF_LOG_WARNING("Data lost, no room in RX ringbuf");
            }
            nrf_libuarte_async_rx_free(&libuarte, p_event->data.rxtx.p_data, p_event->data.rxtx.length);

            if (p_event->data.rxtx.length)
            {
                NRF_LOG_DEBUG("(evt) RXRDY length:%d", p_event->data.rxtx.length);
                NRF_LOG_HEXDUMP_DEBUG(p_event->data.rxtx.p_data, p_event->data.rxtx.length);
                p_internal->p_cb->handler(NRF_CLI_TRANSPORT_EVT_RX_RDY,
                                          p_internal->p_cb->p_context);
            }

            break;
        }

        case NRF_LIBUARTE_ASYNC_EVT_TX_DONE:
            err_code = nrf_ringbuf_free(p_internal->p_tx_ringbuf, p_event->data.rxtx.length);
            ASSERT(err_code == NRF_SUCCESS);
            uint8_t * p_data;
            len = 255;
            err_code = nrf_ringbuf_get(p_internal->p_tx_ringbuf, &p_data, &len, true);
            ASSERT(err_code == NRF_SUCCESS);
            if (len)
            {
                NRF_LOG_DEBUG("(evt) Started TX (%d).", len);
                err_code = nrf_libuarte_async_tx(&libuarte, p_data, len);
                ASSERT(err_code == NRF_SUCCESS);
            }
            else
            {
                m_uart_busy = false;
            }
            p_internal->p_cb->handler(NRF_CLI_TRANSPORT_EVT_TX_RDY, p_internal->p_cb->p_context);
            NRF_LOG_DEBUG("(evt) TX completed (%d)", p_event->data.rxtx.length);
            break;

        default:
            NRF_LOG_ERROR("(evt) Unknown event");
            ASSERT(false);
            break;
    }
}

static ret_code_t cli_libuarte_init(nrf_cli_transport_t const * p_transport,
                                    void const *                p_config,
                                    nrf_cli_transport_handler_t evt_handler,
                                    void *                      p_context)
{
    cli_libuarte_internal_t * p_internal = CONTAINER_OF(p_transport,
                                                        cli_libuarte_internal_t,
                                                        transport);
    mp_internal = p_internal;
    m_uart_busy = false;

    p_internal->p_cb->handler   = evt_handler;
    p_internal->p_cb->p_context = p_context;
    p_internal->p_cb->blocking  = false;

    cli_libuarte_config_t const * p_cli_libuarte_config = (cli_libuarte_config_t *)p_config;
    nrf_libuarte_async_config_t uart_async_config = {
            .tx_pin     = p_cli_libuarte_config->tx_pin,
            .rx_pin     = p_cli_libuarte_config->rx_pin,
            .baudrate   = p_cli_libuarte_config->baudrate,
            .parity     = p_cli_libuarte_config->parity,
            .hwfc       = p_cli_libuarte_config->hwfc,
            .timeout_us = 100,
    };
    ret_code_t err_code = nrf_libuarte_async_init(&libuarte, &uart_async_config, uart_event_handler, NULL);
    if (err_code == NRF_SUCCESS)
    {
        nrf_ringbuf_init(p_internal->p_rx_ringbuf);
        nrf_ringbuf_init(p_internal->p_tx_ringbuf);
    }
    return err_code;
}

static ret_code_t cli_libuarte_uninit(nrf_cli_transport_t const * p_transport)
{
    UNUSED_PARAMETER(p_transport);
    nrf_libuarte_async_uninit(&libuarte);
    return NRF_SUCCESS;
}

static ret_code_t cli_libuarte_enable(nrf_cli_transport_t const * p_transport,
                                      bool                        blocking)
{
    UNUSED_PARAMETER(p_transport);
    if (blocking)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }
    else
    {
        nrf_libuarte_async_enable(&libuarte);
    }
    return NRF_SUCCESS;
}

static ret_code_t cli_libuarte_read(nrf_cli_transport_t const * p_transport,
                                    void *                      p_data,
                                    size_t                      length,
                                    size_t *                    p_cnt)
{
    ASSERT(p_cnt);
    cli_libuarte_internal_t * p_instance =
                                 CONTAINER_OF(p_transport, cli_libuarte_internal_t, transport);

    *p_cnt = length;
    ret_code_t err_code = nrf_ringbuf_cpy_get(p_instance->p_rx_ringbuf, p_data, p_cnt);

    if (*p_cnt)
    {
        NRF_LOG_DEBUG("Read %d bytes (requested %d)", *p_cnt, length);
    }

    return err_code;
}

static ret_code_t cli_libuarte_write(nrf_cli_transport_t const * p_transport,
                                     void const *                p_data,
                                     size_t                      length,
                                     size_t *                    p_cnt)
{
    ASSERT(p_cnt);
    cli_libuarte_internal_t * p_instance = CONTAINER_OF(p_transport,
                                                        cli_libuarte_internal_t,
                                                        transport);
    *p_cnt = length;
    ret_code_t err_code = nrf_ringbuf_cpy_put(p_instance->p_tx_ringbuf, p_data, p_cnt);
    if (err_code == NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("Requested write: %d, copied to ringbuf: %d.", length, *p_cnt);

        if (m_uart_busy)
        {
            return err_code;
        }

        uint8_t * p_buf;
        size_t len = 255;
        if (nrf_ringbuf_get(p_instance->p_tx_ringbuf, &p_buf, &len, true) == NRF_SUCCESS)
        {
            NRF_LOG_DEBUG("Started TX (%d).", len);

            err_code = nrf_libuarte_async_tx(&libuarte, p_buf, len);
            if (p_instance->p_cb->blocking && (err_code == NRF_SUCCESS))
            {
                (void)nrf_ringbuf_free(p_instance->p_tx_ringbuf, len);
            }
            else
            {
                m_uart_busy = true;
            }
        }
    }
    return err_code;
}

const nrf_cli_transport_api_t cli_libuarte_transport_api = {
        .init = cli_libuarte_init,
        .uninit = cli_libuarte_uninit,
        .enable = cli_libuarte_enable,
        .read = cli_libuarte_read,
        .write = cli_libuarte_write,
};

