/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_CLI_UART)
#include "nrf_cli_uart.h"
#include "nrf_drv_uart.h"
#include "nrf_assert.h"

#define NRF_LOG_MODULE_NAME cli_uart

#define NRF_LOG_LEVEL       (NRF_CLI_UART_CONFIG_LOG_ENABLED ? NRF_CLI_UART_CONFIG_LOG_LEVEL : 0)
#define NRF_LOG_INFO_COLOR  NRF_CLI_UART_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_CLI_UART_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define CLI_UART_RX_TIMEOUT 100

static ret_code_t rx_try(nrf_cli_uart_internal_t * p_internal)
{
    ret_code_t err_code;
    size_t     len = 255;
    uint8_t *  p_data;

    err_code = nrf_ringbuf_alloc(p_internal->p_rx_ringbuf, &p_data, &len, true);
    ASSERT(err_code == NRF_SUCCESS);

    if ((err_code == NRF_SUCCESS) && len)
    {
        err_code = nrf_drv_uart_rx(p_internal->p_uart, p_data, len);

        if (err_code == NRF_SUCCESS)
        {
            err_code = app_timer_start(*p_internal->p_timer,
                                        APP_TIMER_TICKS(CLI_UART_RX_TIMEOUT),
                                        p_internal);
        }
    }

    return err_code;
}

static void uart_event_handler(nrf_drv_uart_event_t * p_event, void * p_context)
{
    nrf_cli_uart_internal_t * p_internal = (nrf_cli_uart_internal_t *)p_context;
    ret_code_t err_code = NRF_SUCCESS;
    UNUSED_VARIABLE(err_code);
    uint8_t * p_data;
    size_t len = 255;
    switch (p_event->type)
    {
        case NRF_DRV_UART_EVT_ERROR:
            NRF_LOG_WARNING("id:%d, evt: ERROR:%d",
                            p_internal->p_uart->inst_idx,
                            p_event->data.error.error_mask);
            err_code = nrf_ringbuf_put(p_internal->p_rx_ringbuf, p_event->data.error.rxtx.bytes);
            ASSERT((err_code == NRF_SUCCESS) || (err_code == NRF_ERROR_NO_MEM));
            err_code = rx_try(p_internal);
            ASSERT(err_code == NRF_SUCCESS);

            break;

        case NRF_DRV_UART_EVT_RX_DONE:
            err_code = nrf_ringbuf_put(p_internal->p_rx_ringbuf, p_event->data.rxtx.bytes);
            ASSERT((err_code == NRF_SUCCESS) || (err_code == NRF_ERROR_NO_MEM));

            if (p_event->data.rxtx.bytes)
            {
                NRF_LOG_INFO("id:%d, evt: RXRDY len:%d",
                             p_internal->p_uart->inst_idx,
                             p_event->data.rxtx.bytes);
                NRF_LOG_HEXDUMP_DEBUG(p_event->data.rxtx.p_data, p_event->data.rxtx.bytes);
                p_internal->p_cb->handler(NRF_CLI_TRANSPORT_EVT_RX_RDY,
                                          p_internal->p_cb->p_context);
            }
            err_code = rx_try(p_internal);
            ASSERT(err_code == NRF_SUCCESS);

            break;

        case NRF_DRV_UART_EVT_TX_DONE:
            err_code = nrf_ringbuf_free(p_internal->p_tx_ringbuf, p_event->data.rxtx.bytes);
            ASSERT(err_code == NRF_SUCCESS);
            len = 255;
            err_code = nrf_ringbuf_get(p_internal->p_tx_ringbuf, &p_data, &len, true);
            ASSERT(err_code == NRF_SUCCESS);
            if (len)
            {
                NRF_LOG_INFO("id:%d, evt uart_tx, len:%d", p_internal->p_uart->inst_idx, len);
                err_code = nrf_drv_uart_tx(p_internal->p_uart, p_data, len);
            ASSERT(err_code == NRF_SUCCESS);
            }
            p_internal->p_cb->handler(NRF_CLI_TRANSPORT_EVT_TX_RDY, p_internal->p_cb->p_context);
            NRF_LOG_INFO("id:%d, evt: TXRDY, len:%d",
                         p_internal->p_uart->inst_idx,
                         p_event->data.rxtx.bytes);
            break;

        default:
            NRF_LOG_ERROR("Unknown event");
            ASSERT(false);
    }
}

static void timer_handler(void * p_context)
{
    nrf_cli_uart_internal_t * p_internal = (nrf_cli_uart_internal_t *)p_context;
    NRF_LOG_DEBUG("id:%d, evt: Timeout", p_internal->p_uart->inst_idx);
    nrf_drv_uart_rx_abort(p_internal->p_uart);
}

static ret_code_t cli_uart_init(nrf_cli_transport_t const * p_transport,
                                void const *                p_config,
                                nrf_cli_transport_handler_t evt_handler,
                                void *                      p_context)
{
    nrf_cli_uart_internal_t * p_internal =
                                       CONTAINER_OF(p_transport,
                                                    nrf_cli_uart_internal_t,
                                                    transport);
    p_internal->p_cb->handler = evt_handler;
    p_internal->p_cb->p_context = p_context;
    p_internal->p_cb->timer_created = false;
    p_internal->p_cb->blocking      = false;

    nrf_drv_uart_config_t * p_uart_config = (nrf_drv_uart_config_t *)p_config;
    memcpy(&p_internal->p_cb->uart_config, p_uart_config, sizeof(nrf_drv_uart_config_t));
    p_uart_config->p_context = (void *)p_internal;
    ret_code_t err_code = nrf_drv_uart_init(p_internal->p_uart,
                                            p_uart_config,
                                            uart_event_handler);
    if (err_code == NRF_SUCCESS)
    {
        nrf_ringbuf_init(p_internal->p_rx_ringbuf);
        nrf_ringbuf_init(p_internal->p_tx_ringbuf);
    }
    return err_code;
}

static ret_code_t cli_uart_uninit(nrf_cli_transport_t const * p_transport)
{
    nrf_cli_uart_internal_t * p_internal =
                                       CONTAINER_OF(p_transport,
                                                    nrf_cli_uart_internal_t,
                                                    transport);

    nrf_drv_uart_uninit(p_internal->p_uart);

    return app_timer_stop(*p_internal->p_timer);
}

static ret_code_t cli_uart_enable(nrf_cli_transport_t const * p_transport,
                                 bool                         blocking)
{
    nrf_cli_uart_internal_t * p_internal =
                                       CONTAINER_OF(p_transport,
                                                    nrf_cli_uart_internal_t,
                                                    transport);
    ret_code_t err_code = NRF_SUCCESS;

    if (p_internal->p_cb->timer_created)
    {
        err_code = app_timer_stop(*p_internal->p_timer); //Timer may be running or inactive
        if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_INVALID_STATE))
        {
            return err_code;
        }
        else
        {
            err_code = NRF_SUCCESS;
        }
    }

    if (blocking)
    {
        nrf_drv_uart_uninit(p_internal->p_uart);
        err_code = nrf_drv_uart_init(p_internal->p_uart, &p_internal->p_cb->uart_config, NULL);
        if (err_code == NRF_SUCCESS)
        {
            p_internal->p_cb->blocking = true;
            return NRF_SUCCESS;
        }
        else
        {
            return NRF_ERROR_NOT_SUPPORTED;
        }
    }
    else
    {
        if (!p_internal->p_cb->timer_created)
        {
            err_code = app_timer_create(p_internal->p_timer,
                                        APP_TIMER_MODE_SINGLE_SHOT,
                                        timer_handler);
            p_internal->p_cb->timer_created = true;
        }
        if (err_code == NRF_SUCCESS)
        {
            err_code = rx_try(p_internal);
        }
    }
    return err_code;
}

static ret_code_t cli_uart_read(nrf_cli_transport_t const * p_transport,
                                void *                      p_data,
                                size_t                      length,
                                size_t *                    p_cnt)
{
    ASSERT(p_cnt);
    nrf_cli_uart_internal_t * p_instance =
                                 CONTAINER_OF(p_transport, nrf_cli_uart_internal_t, transport);

    *p_cnt = length;
    ret_code_t err_code = nrf_ringbuf_cpy_get(p_instance->p_rx_ringbuf, p_data, p_cnt);

    if (*p_cnt)
    {
        NRF_LOG_INFO("id:%d, read:%d", p_instance->p_uart->inst_idx, *p_cnt);
    }

    return err_code;
}

static ret_code_t cli_uart_write(nrf_cli_transport_t const * p_transport,
                                 void const *                p_data,
                                 size_t                      length,
                                 size_t *                    p_cnt)
{
    ASSERT(p_cnt);
    nrf_cli_uart_internal_t * p_instance =
                                     CONTAINER_OF(p_transport, nrf_cli_uart_internal_t, transport);
    ret_code_t err_code;
    *p_cnt = length;
    err_code = nrf_ringbuf_cpy_put(p_instance->p_tx_ringbuf, p_data, p_cnt);
    if (err_code == NRF_SUCCESS)
    {
        NRF_LOG_INFO("id:%d, write, req:%d, done:%d",
                     p_instance->p_uart->inst_idx,
                     length,
                     *p_cnt);

        if (!nrf_drv_uart_tx_in_progress(p_instance->p_uart))
        {
            uint8_t * p_buf;
            size_t len = 255;
            if (nrf_ringbuf_get(p_instance->p_tx_ringbuf, &p_buf, &len, true) == NRF_SUCCESS)
            {
                NRF_LOG_INFO("id:%d, uart_tx, len:%d", p_instance->p_uart->inst_idx, len);

                err_code = nrf_drv_uart_tx(p_instance->p_uart, p_buf, len);
                if (p_instance->p_cb->blocking && (err_code == NRF_SUCCESS))
                {
                    (void)nrf_ringbuf_free(p_instance->p_tx_ringbuf, len);
                }
            }
        }
    }
    return err_code;
}

const nrf_cli_transport_api_t nrf_cli_uart_transport_api = {
        .init = cli_uart_init,
        .uninit = cli_uart_uninit,
        .enable = cli_uart_enable,
        .read = cli_uart_read,
        .write = cli_uart_write,
};

#endif
