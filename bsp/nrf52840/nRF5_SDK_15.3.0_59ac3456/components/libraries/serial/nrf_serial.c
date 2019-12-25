/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_SERIAL)
#include "nrf_serial.h"

#if defined (UART_PRESENT)

static void event_handler(nrf_serial_t const * p_serial,
                          nrf_serial_event_t event)
{
    if (p_serial->p_ctx->p_config->ev_handler)
    {
        p_serial->p_ctx->p_config->ev_handler(p_serial, event);
    }
}

static void sleep_handler(nrf_serial_t const * p_serial)
{
    if (p_serial->p_ctx->p_config->mode == NRF_SERIAL_MODE_POLLING)
    {
        return;
    }

    if (p_serial->p_ctx->p_config->sleep_handler)
    {
        p_serial->p_ctx->p_config->sleep_handler();
    }
}

static size_t serial_rx(nrf_serial_t const * p_serial,
                        uint8_t * p_buff,
                        size_t length)
{
    if (p_serial->p_ctx->p_config->mode == NRF_SERIAL_MODE_POLLING)
    {
        size_t rx_len = MIN(length, UINT8_MAX);
        size_t len = rx_len;

        while (nrf_drv_uart_rx_ready(&p_serial->instance) && len)
        {
            ret_code_t ret = nrf_drv_uart_rx(&p_serial->instance, p_buff, 1);
            if (ret != NRF_SUCCESS)
            {
                break;
            }
            p_buff++;
            len--;
        }

        return rx_len - len;
    }

    nrf_queue_t const * p_rxq = p_serial->p_ctx->p_config->p_queues->p_rxq;
    return nrf_queue_out(p_rxq, p_buff, length);
}

static size_t serial_tx(nrf_serial_t const * p_serial,
                        uint8_t const * p_buff,
                        size_t length)
{
    size_t tx_len = 0;

    if (p_serial->p_ctx->p_config->mode == NRF_SERIAL_MODE_POLLING)
    {
        tx_len = MIN(length, UINT8_MAX);
        ret_code_t ret = nrf_drv_uart_tx(&p_serial->instance, p_buff, tx_len);
        ASSERT(ret == NRF_SUCCESS)
        return tx_len;
    }

    nrf_queue_t const * p_txq = p_serial->p_ctx->p_config->p_queues->p_txq;
    nrf_serial_buffers_t const * p_buffs = p_serial->p_ctx->p_config->p_buffers;

    /* Try to enqueue data. */
    size_t queue_in_len = nrf_queue_in(p_txq, p_buff, length);
    if (nrf_drv_uart_tx_in_progress(&p_serial->instance))
    {
        return queue_in_len;
    }

    size_t len = nrf_queue_out(p_txq, p_buffs->p_txb, p_buffs->tx_size);
    ASSERT(len > 0);
    ret_code_t ret = nrf_drv_uart_tx(&p_serial->instance, p_buffs->p_txb, len);
    ASSERT(ret == NRF_SUCCESS);

    return queue_in_len;
}

static void uart_event_handler(nrf_drv_uart_event_t * p_event, void * p_context)
{
    uint32_t ret;
    nrf_serial_t const * p_serial = p_context;

    switch (p_event->type)
    {
        case NRF_DRV_UART_EVT_RX_DONE:
        {
            nrf_queue_t const * p_rxq =
                    p_serial->p_ctx->p_config->p_queues->p_rxq;
            size_t len = nrf_queue_in(p_rxq,
                                      p_event->data.rxtx.p_data,
                                      p_event->data.rxtx.bytes);

            if (len < p_event->data.rxtx.bytes)
            {
                event_handler(p_serial, NRF_SERIAL_EVENT_FIFO_ERR);
                break;
            }

            event_handler(p_serial, NRF_SERIAL_EVENT_RX_DATA);
            nrf_serial_buffers_t const * p_buffs =
                    p_serial->p_ctx->p_config->p_buffers;

            ret = nrf_drv_uart_rx(&p_serial->instance,
                                  p_buffs->p_rxb,
                                  p_buffs->rx_size);
            ASSERT(ret == NRF_SUCCESS);
            break;
        }
        case NRF_DRV_UART_EVT_ERROR:
        {
            event_handler(p_serial, NRF_SERIAL_EVENT_DRV_ERR);
            break;
        }
        case NRF_DRV_UART_EVT_TX_DONE:
        {
            nrf_queue_t const * p_txq =
                    p_serial->p_ctx->p_config->p_queues->p_txq;
            nrf_serial_buffers_t const * p_buffs =
                    p_serial->p_ctx->p_config->p_buffers;

            event_handler(p_serial, NRF_SERIAL_EVENT_TX_DONE);
            size_t len = nrf_queue_out(p_txq, p_buffs->p_txb, p_buffs->tx_size);
            if (len == 0)
            {
                break;
            }

            ret = nrf_drv_uart_tx(&p_serial->instance, p_buffs->p_txb, len);
            ASSERT(ret == NRF_SUCCESS);
            break;
        }
        default:
            break;
    }
}

ret_code_t nrf_serial_init(nrf_serial_t const * p_serial,
                           nrf_drv_uart_config_t const * p_drv_uart_config,
                           nrf_serial_config_t const * p_config)
{
    ret_code_t ret;
    ASSERT(p_serial && p_drv_uart_config && p_config);

    if (p_serial->p_ctx->p_config)
    {
        /*Already initialized.*/
        return NRF_ERROR_MODULE_ALREADY_INITIALIZED;
    }

    if (p_config->mode != NRF_SERIAL_MODE_POLLING)
    {
        ASSERT(p_config->p_queues && p_config->p_buffers);
    }

    nrf_drv_uart_config_t drv_config;
    memcpy(&drv_config, p_drv_uart_config, sizeof(nrf_drv_uart_config_t));
    drv_config.p_context = (void *)p_serial;
#if defined(UARTE_PRESENT) && defined(UART_PRESENT)
    drv_config.use_easy_dma = (p_config->mode == NRF_SERIAL_MODE_DMA);
#endif
    ret = nrf_drv_uart_init(&p_serial->instance,
                            &drv_config,
                            p_config->mode == NRF_SERIAL_MODE_POLLING ?
                            NULL : uart_event_handler);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    p_serial->p_ctx->p_config = p_config;

    if (p_serial->p_ctx->p_config->p_queues)
    {
        nrf_queue_reset(p_serial->p_ctx->p_config->p_queues->p_txq);
        nrf_queue_reset(p_serial->p_ctx->p_config->p_queues->p_rxq);
    }

    nrf_mtx_init(&p_serial->p_ctx->read_lock);
    nrf_mtx_init(&p_serial->p_ctx->write_lock);

    p_serial->p_ctx->flags = NRF_SERIAL_RX_ENABLED_FLAG |
                             NRF_SERIAL_TX_ENABLED_FLAG;

    if (drv_config.pseltxd == NRF_UART_PSEL_DISCONNECTED)
    {
        p_serial->p_ctx->flags &= ~NRF_SERIAL_TX_ENABLED_FLAG;
    }

    if (drv_config.pselrxd == NRF_UART_PSEL_DISCONNECTED)
    {
        p_serial->p_ctx->flags &= ~NRF_SERIAL_RX_ENABLED_FLAG;
        return NRF_SUCCESS;
    }

    if (p_serial->p_ctx->p_config->mode != NRF_SERIAL_MODE_DMA)
    {
        nrf_drv_uart_rx_enable(&p_serial->instance);
        if (p_serial->p_ctx->p_config->mode == NRF_SERIAL_MODE_POLLING)
        {
            return NRF_SUCCESS;
        }
    }

    return nrf_drv_uart_rx(&p_serial->instance,
                           p_serial->p_ctx->p_config->p_buffers->p_rxb,
                           p_serial->p_ctx->p_config->p_buffers->rx_size);
}

ret_code_t nrf_serial_uninit(nrf_serial_t const * p_serial)
{
    ASSERT(p_serial);

    if (!p_serial->p_ctx->p_config)
    {
        /*Already uninitialized.*/
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }

    if (!nrf_mtx_trylock(&p_serial->p_ctx->write_lock))
    {
        return NRF_ERROR_BUSY;
    }
    if (!nrf_mtx_trylock(&p_serial->p_ctx->read_lock))
    {
        nrf_mtx_unlock(&p_serial->p_ctx->write_lock);
        return NRF_ERROR_BUSY;
    }

    nrf_drv_uart_uninit(&p_serial->instance);
    if (p_serial->p_ctx->p_config->p_queues)
    {
        nrf_queue_reset(p_serial->p_ctx->p_config->p_queues->p_txq);
        nrf_queue_reset(p_serial->p_ctx->p_config->p_queues->p_rxq);
    }

    memset(p_serial->p_ctx, 0, sizeof(nrf_serial_ctx_t));
    return NRF_SUCCESS;
}

typedef struct {
    volatile bool expired;
} nrf_serial_timeout_ctx_t;

static void serial_timeout_handler(void * p_context)
{
    nrf_serial_timeout_ctx_t * p_tout_ctx = p_context;
    p_tout_ctx->expired = true;
}


static ret_code_t timeout_setup(nrf_serial_t const * p_serial,
                                app_timer_id_t const * p_timer_id,
                                uint32_t timeout_ms,
                                nrf_serial_timeout_ctx_t * p_tout_ctx)
{
    uint32_t ticks = APP_TIMER_TICKS(timeout_ms);

    if (ticks < APP_TIMER_MIN_TIMEOUT_TICKS)
    {
        p_tout_ctx->expired = true;
        return NRF_SUCCESS;
    }

    ret_code_t ret = app_timer_create(p_timer_id,
                                      APP_TIMER_MODE_SINGLE_SHOT,
                                      serial_timeout_handler);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    return app_timer_start(*p_timer_id, ticks, p_tout_ctx);
}

ret_code_t nrf_serial_write(nrf_serial_t const * p_serial,
                            void const * p_data,
                            size_t size,
                            size_t * p_written,
                            uint32_t timeout_ms)
{
    ret_code_t ret;

    ASSERT(p_serial);
    if (!p_serial->p_ctx->p_config)
    {
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }

    if (!(p_serial->p_ctx->flags & NRF_SERIAL_TX_ENABLED_FLAG))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (size == 0)
    {
        return NRF_SUCCESS;
    }

    if (!nrfx_is_in_ram(p_data) &&
         p_serial->p_ctx->p_config->mode == NRF_SERIAL_MODE_DMA)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    if (!nrf_mtx_trylock(&p_serial->p_ctx->write_lock))
    {
        return NRF_ERROR_BUSY;
    }

    nrf_serial_timeout_ctx_t tout_ctx = {
            .expired = false,
    };

    if (timeout_ms != NRF_SERIAL_MAX_TIMEOUT)
    {
        ret = timeout_setup(p_serial,
                            p_serial->p_tx_timer,
                            timeout_ms,
                            &tout_ctx);
        if (ret != NRF_SUCCESS)
        {
            nrf_mtx_unlock(&p_serial->p_ctx->write_lock);
            return ret;
        }
    }

    size_t left = size;
    uint8_t const * p_buff = p_data;

    do
    {
        size_t wcnt = serial_tx(p_serial, p_buff, left);
        left -= wcnt;
        p_buff += wcnt;
        if (!left)
        {
            break;
        }

        sleep_handler(p_serial);
    } while (!tout_ctx.expired);

    if (p_written)
    {
        *p_written = size - left;
    }

    if (!tout_ctx.expired && (timeout_ms != NRF_SERIAL_MAX_TIMEOUT))
    {
        (void)app_timer_stop(*p_serial->p_tx_timer);
    }

    nrf_mtx_unlock(&p_serial->p_ctx->write_lock);
    if (left && tout_ctx.expired)
    {
        return NRF_ERROR_TIMEOUT;
    }

    return NRF_SUCCESS;
}

ret_code_t nrf_serial_read(nrf_serial_t const * p_serial,
                           void * p_data,
                           size_t size,
                           size_t * p_read,
                           uint32_t timeout_ms)
{
    ret_code_t ret;

    ASSERT(p_serial);
    if (!p_serial->p_ctx->p_config)
    {
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }

    if (!(p_serial->p_ctx->flags & NRF_SERIAL_RX_ENABLED_FLAG))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (size == 0)
    {
        return NRF_SUCCESS;
    }

    if (!nrf_mtx_trylock(&p_serial->p_ctx->read_lock))
    {
        return NRF_ERROR_BUSY;
    }

    nrf_serial_timeout_ctx_t tout_ctx = {
            .expired = false,
    };

    if (timeout_ms != NRF_SERIAL_MAX_TIMEOUT)
    {
        ret = timeout_setup(p_serial,
                            p_serial->p_rx_timer,
                            timeout_ms,
                            &tout_ctx);

        if (ret != NRF_SUCCESS)
        {
            nrf_mtx_unlock(&p_serial->p_ctx->read_lock);
            return ret;
        }
    }

    size_t left = size;
    uint8_t * p_buff = p_data;
    do
    {
        size_t rcnt = serial_rx(p_serial, p_buff, left);
        left -= rcnt;
        p_buff += rcnt;
        if (!left)
        {
            break;
        }

        if (tout_ctx.expired)
        {
            if (p_serial->p_ctx->p_config->mode != NRF_SERIAL_MODE_POLLING)
            {
                nrf_drv_uart_rx_abort(&p_serial->instance);
            }
            break;
        }

        sleep_handler(p_serial);
    } while (1);

    if (p_read)
    {
        *p_read = size - left;
    }

    if (!tout_ctx.expired && (timeout_ms != NRF_SERIAL_MAX_TIMEOUT))
    {
        (void)app_timer_stop(*p_serial->p_rx_timer);
    }

    nrf_mtx_unlock(&p_serial->p_ctx->read_lock);
    if (left && tout_ctx.expired)
    {
        return NRF_ERROR_TIMEOUT;
    }

    return NRF_SUCCESS;
}

ret_code_t nrf_serial_flush(nrf_serial_t const * p_serial, uint32_t timeout_ms)
{

    ret_code_t ret;

    ASSERT(p_serial);
    if (!p_serial->p_ctx->p_config)
    {
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }

    if (!(p_serial->p_ctx->flags & NRF_SERIAL_TX_ENABLED_FLAG))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (p_serial->p_ctx->p_config->mode == NRF_SERIAL_MODE_POLLING)
    {
        return NRF_SUCCESS;
    }

    if (!nrf_mtx_trylock(&p_serial->p_ctx->write_lock))
    {
        return NRF_ERROR_BUSY;
    }

    nrf_serial_timeout_ctx_t tout_ctx = {
            .expired = false,
    };

    if (timeout_ms != NRF_SERIAL_MAX_TIMEOUT)
    {
        ret = timeout_setup(p_serial,
                            p_serial->p_tx_timer,
                            timeout_ms,
                            &tout_ctx);
        if (ret != NRF_SUCCESS)
        {
            nrf_mtx_unlock(&p_serial->p_ctx->write_lock);
            return ret;
        }
    }

    bool empty;
    do
    {
        empty = nrf_queue_is_empty(p_serial->p_ctx->p_config->p_queues->p_txq)
                && !nrf_drv_uart_tx_in_progress(&p_serial->instance);
        if (empty)
        {
            break;
        }

        sleep_handler(p_serial);
    } while (!tout_ctx.expired);

    if (!tout_ctx.expired && (timeout_ms != NRF_SERIAL_MAX_TIMEOUT))
    {
        (void)app_timer_stop(*p_serial->p_tx_timer);
    }

    nrf_mtx_unlock(&p_serial->p_ctx->write_lock);
    if (!empty && tout_ctx.expired)
    {
        return NRF_ERROR_TIMEOUT;
    }

    return NRF_SUCCESS;
}

ret_code_t nrf_serial_tx_abort(nrf_serial_t const * p_serial)
{
    ASSERT(p_serial);
    if (!p_serial->p_ctx->p_config)
    {
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }

    if (!(p_serial->p_ctx->flags & NRF_SERIAL_TX_ENABLED_FLAG))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (!nrf_mtx_trylock(&p_serial->p_ctx->write_lock))
    {
        return NRF_ERROR_BUSY;
    }

    nrf_drv_uart_tx_abort(&p_serial->instance);
    if (p_serial->p_ctx->p_config->p_queues->p_txq)
    {
        nrf_queue_reset(p_serial->p_ctx->p_config->p_queues->p_txq);
    }

    nrf_mtx_unlock(&p_serial->p_ctx->write_lock);
    return NRF_SUCCESS;
}

ret_code_t nrf_serial_rx_drain(nrf_serial_t const * p_serial)
{
    ASSERT(p_serial);
    if (!p_serial->p_ctx->p_config)
    {
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }

    if (!(p_serial->p_ctx->flags & NRF_SERIAL_RX_ENABLED_FLAG))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (!nrf_mtx_trylock(&p_serial->p_ctx->read_lock))
    {
        return NRF_ERROR_BUSY;
    }

    uint8_t c;
    /*Drain HW FIFO*/
    while (serial_rx(p_serial, &c, sizeof(c)))
    {

    }

    /*Drain SW FIFO*/
    if (p_serial->p_ctx->p_config->p_queues->p_rxq)
    {
        nrf_queue_reset(p_serial->p_ctx->p_config->p_queues->p_rxq);
    }
    nrf_mtx_unlock(&p_serial->p_ctx->read_lock);
    return NRF_SUCCESS;
}
#else
ret_code_t nrf_serial_init(nrf_serial_t const * p_serial,
                           nrf_drv_uart_config_t const * p_drv_uart_config,
                           nrf_serial_config_t const * p_config)
{
    return NRF_ERROR_NOT_SUPPORTED;
}

ret_code_t nrf_serial_uninit(nrf_serial_t const * p_serial)
{
    return NRF_ERROR_NOT_SUPPORTED;
}
ret_code_t nrf_serial_write(nrf_serial_t const * p_serial,
                            void const * p_data,
                            size_t size,
                            size_t * p_written,
                            uint32_t timeout_ms)
{
    return NRF_ERROR_NOT_SUPPORTED;
}
ret_code_t nrf_serial_read(nrf_serial_t const * p_serial,
                           void * p_data,
                           size_t size,
                           size_t * p_read,
                           uint32_t timeout_ms)
{
    return NRF_ERROR_NOT_SUPPORTED;
}
ret_code_t nrf_serial_flush(nrf_serial_t const * p_serial, uint32_t timeout_ms)
{
    return NRF_ERROR_NOT_SUPPORTED;
}
ret_code_t nrf_serial_tx_abort(nrf_serial_t const * p_serial)
{
    return NRF_ERROR_NOT_SUPPORTED;
}
ret_code_t nrf_serial_rx_drain(nrf_serial_t const * p_serial)
{
    return NRF_ERROR_NOT_SUPPORTED;
}

#endif // UART_PRESENT
#endif //NRF_MODULE_ENABLED(NRF_SERIAL)

