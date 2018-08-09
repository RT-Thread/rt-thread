/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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
#include "sdk_config.h"
#include "nrf_libuarte_async.h"
#include "nrf_libuarte.h"
#include "app_error.h"
#include "nrf_balloc.h"
#include "nrfx_timer.h"
#include "nrfx_ppi.h"
#include "nrf_uart.h"
#include "nrf_queue.h"

#define NRF_LOG_MODULE_NAME libUARTE_async
#if NRF_LIBUARTE_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_LIBUARTE_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_LIBUARTE_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_LIBUARTE_CONFIG_DEBUG_COLOR
#else // NRF_LIBUARTE_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NRF_LIBUARTE_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

static nrf_libuarte_async_evt_handler m_evt_handler;
#define POOL_SZ 3UL
#define MAX_CHUNK_SZ 255UL

NRF_BALLOC_DEF(m_rx_pool, MAX_CHUNK_SZ, POOL_SZ);

NRF_QUEUE_DEF(uint8_t *, m_rxdata_queue, 3, NRF_QUEUE_MODE_NO_OVERFLOW);

#define UART_DRV_TIMER CONCAT_2(NRF_TIMER, NRF_LIBUARTE_CONFIG_TIMER_USED)
#define UART_DRV_UARTE CONCAT_2(NRF_UARTE, NRF_LIBUARTE_CONFIG_UARTE_USED)

static nrfx_timer_t m_timer = NRFX_TIMER_INSTANCE(NRF_LIBUARTE_ASYNC_CONFIG_TIMER_USED);

#if CONCAT_3(NRFX_TIMER, NRF_LIBUARTE_ASYNC_CONFIG_TIMER_USED,_ENABLED) == 0
#error "Timer instance not enabled"
#endif

typedef enum
{
    PPI_CH_RXRDY_CLEAR,
    PPI_CH_COMPARE_SHUTDOWN,
    PPI_CH_MAX
} nrf_libuarte_async_ppi_channel_t;

static nrf_ppi_channel_t m_ppi_channels[PPI_CH_MAX];
static int32_t m_alloc_cnt;
static uint32_t m_rx_count;
static uint32_t m_sub_rx_count;
static uint8_t * mp_curr_rx_buf;
static uint32_t m_rx_free_cnt;
static size_t m_rx_chunk_size;

#define PPI_CH_SETUP(_ch, _evt, _tsk, _fork)                            \
    ret = nrfx_ppi_channel_assign(m_ppi_channels[_ch], _evt, _tsk);     \
    if (ret != NRF_SUCCESS)                                             \
    {                                                                   \
        return NRF_ERROR_INTERNAL;                                      \
    }                                                                   \
    if (_fork)                                                          \
    {                                                                   \
        ret = nrfx_ppi_channel_fork_assign(m_ppi_channels[_ch], _fork); \
        if (ret != NRF_SUCCESS)                                         \
        {                                                               \
            return NRF_ERROR_INTERNAL;                                  \
        }                                                               \
    }

static void uart_evt_handler(nrf_libuarte_evt_t * p_evt)
{
    ret_code_t ret;
    switch (p_evt->type)
    {
    case NRF_LIBUARTE_EVT_TX_DONE:
    {
        NRF_LOG_DEBUG("(evt) TX completed (%d)", p_evt->data.rxtx.length);
        nrf_libuarte_async_evt_t evt = {
            .type = NRF_LIBUARTE_ASYNC_EVT_TX_DONE,
            .data.rxtx.p_data = p_evt->data.rxtx.p_data,
            .data.rxtx.length = p_evt->data.rxtx.length,
        };
        m_evt_handler(&evt);
        break;
    }
    case NRF_LIBUARTE_EVT_RX_BUF_REQ:
    {
        uint8_t * p_data = nrf_balloc_alloc(&m_rx_pool);
        if (p_data)
        {
            ret = nrf_queue_push(&m_rxdata_queue, &p_data);
            if (ret != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("(evt) RX buffer queue full.");
                APP_ERROR_CHECK_BOOL(false);
            }

            m_alloc_cnt++;
            nrf_libuarte_rx_buf_rsp(p_data, m_rx_chunk_size);
        }
        else
        {
            NRF_LOG_ERROR("(evt) Failed to allocate buffer for RX.");
            APP_ERROR_CHECK_BOOL(false);
        }
        break;
    }
    case NRF_LIBUARTE_EVT_RX_DATA:
    {

        uint32_t rx_amount = p_evt->data.rxtx.length - m_sub_rx_count;
        if (rx_amount)
        {
            m_rx_count += rx_amount;
            nrf_libuarte_async_evt_t evt = {
                .type = NRF_LIBUARTE_ASYNC_EVT_RX_DATA,
                .data.rxtx.p_data = &p_evt->data.rxtx.p_data[m_sub_rx_count],
                .data.rxtx.length = rx_amount,
            };
            NRF_LOG_DEBUG("(evt) RX: %d (addr:0x%08X, internal index: %d)",
                          rx_amount,
                          p_evt->data.rxtx.p_data,
                          m_sub_rx_count);

            m_sub_rx_count = 0;

            if(p_evt->data.rxtx.p_data != mp_curr_rx_buf)
            {
                NRF_LOG_ERROR("(evt) RX buffer address mismatch");
            }

            ret = nrf_queue_pop(&m_rxdata_queue, &mp_curr_rx_buf);
            if (ret != NRF_SUCCESS)
            {
                NRF_LOG_ERROR("RX buffer queue empty.");
                APP_ERROR_CHECK_BOOL(false);
            }

            m_evt_handler(&evt);
        }
        else
        {
            NRF_LOG_ERROR("(evt) RX with 0 length: 0x%08X", p_evt->data.rxtx.p_data);
            //zero length packet is freed immediately and not forwarded to the application.
            APP_ERROR_CHECK_BOOL(false);
        }
        break;
    }
    default:
        APP_ERROR_CHECK_BOOL(false);
        break;
    }
}

static void tmr_evt_handler(nrf_timer_event_t event_type, void * p_context)
{
    uint32_t capt_rx_count = UART_DRV_TIMER->CC[2];

    if (capt_rx_count > m_rx_count)
    {
        uint32_t rx_amount = capt_rx_count - m_rx_count;
        nrf_libuarte_async_evt_t evt = {
            .type = NRF_LIBUARTE_ASYNC_EVT_RX_DATA,
            .data.rxtx.p_data = &mp_curr_rx_buf[m_sub_rx_count],
            .data.rxtx.length = rx_amount,
        };
        NRF_LOG_DEBUG("(tmr evt) RX: %d (addr:0x%08X, internal index: %d)",
                      rx_amount,
                      evt.data.rxtx.p_data,
                      m_sub_rx_count);

        m_sub_rx_count += rx_amount;
        m_rx_count = capt_rx_count;
        m_evt_handler(&evt);
    }
}

ret_code_t nrf_libuarte_async_init(nrf_libuarte_async_config_t const * p_config, nrf_libuarte_async_evt_handler evt_handler)
{
    ret_code_t ret;

    m_evt_handler  = evt_handler;
    m_rx_count     = 0;
    mp_curr_rx_buf = NULL;
    m_rx_free_cnt  = 0;
    m_sub_rx_count = 0;
    m_alloc_cnt    = 0;

    nrfx_timer_config_t tmr_config = NRFX_TIMER_DEFAULT_CONFIG;
    tmr_config.frequency = NRF_TIMER_FREQ_1MHz;
    ret = nrfx_timer_init(&m_timer, &tmr_config, tmr_evt_handler);
    if (ret != NRFX_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
    nrfx_timer_compare(&m_timer, NRF_TIMER_CC_CHANNEL0, p_config->timeout_us, true);

    uint32_t i;
    for (i = 0; i < PPI_CH_MAX; i++)
    {
        ret = nrfx_ppi_channel_alloc(&m_ppi_channels[i]);
        if (ret != NRFX_SUCCESS)
        {
            //we don't free already allocated channels, system is wrongly configured.
            return NRF_ERROR_INTERNAL;
        }
    }

/*lint -save -e666 */
    PPI_CH_SETUP(m_ppi_channels[PPI_CH_RXRDY_CLEAR],
                 nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_RXDRDY),
                 nrfx_timer_task_address_get(&m_timer, NRF_TIMER_TASK_START),
                 nrfx_timer_task_address_get(&m_timer, NRF_TIMER_TASK_CLEAR));

    PPI_CH_SETUP(m_ppi_channels[PPI_CH_COMPARE_SHUTDOWN],
                nrfx_timer_compare_event_address_get(&m_timer, 0),
                nrfx_timer_task_address_get(&m_timer, NRF_TIMER_TASK_SHUTDOWN),
                (uint32_t)&UART_DRV_TIMER->TASKS_CAPTURE[2]);

/*lint -restore */

    nrf_libuarte_config_t uart_config = {
        .tx_pin        = p_config->tx_pin,
        .rx_pin        = p_config->rx_pin,
        .cts_pin       = p_config->cts_pin,
        .rts_pin       = p_config->rts_pin,
        .startrx_evt   = nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDRX),
        .endrx_evt     = 0,
        .rxstarted_tsk = 0,
        .rxdone_tsk    = 0,
        .hwfc          = p_config->hwfc,
        .parity        = p_config->parity,
        .baudrate      = p_config->baudrate,
        .irq_priority  = 7,
    };

    ret = nrf_libuarte_init(&uart_config, uart_evt_handler);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    ret = nrf_balloc_init(&m_rx_pool);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    nrf_queue_reset(&m_rxdata_queue);

    return ret;
}

void nrf_libuarte_async_uninit(void)
{
    nrfx_err_t err = nrfx_ppi_channel_disable(m_ppi_channels[PPI_CH_RXRDY_CLEAR]);
    APP_ERROR_CHECK_BOOL(err == NRFX_SUCCESS);
    nrf_libuarte_uninit();
    nrfx_timer_disable(&m_timer);
    nrfx_timer_uninit(&m_timer);

    uint32_t i;
    ret_code_t ret;
    for (i = 0; i < PPI_CH_MAX; i++)
    {
        ret = nrfx_ppi_channel_disable(m_ppi_channels[i]);
        ASSERT(ret == NRF_SUCCESS)
        ret = nrfx_ppi_channel_free(m_ppi_channels[i]);
        ASSERT(ret == NRF_SUCCESS)
    }
}

void nrf_libuarte_async_enable(size_t chunk_size)
{
    ASSERT(chunk_size <= MAX_CHUNK_SZ);
    uint8_t * p_data;
    p_data = nrf_balloc_alloc(&m_rx_pool);
    m_alloc_cnt++;
    if (p_data == NULL)
    {
        APP_ERROR_CHECK_BOOL(false);
    }
    nrfx_timer_clear(&m_timer);
    nrfx_err_t err = nrfx_ppi_channel_enable(m_ppi_channels[PPI_CH_RXRDY_CLEAR]);
    APP_ERROR_CHECK_BOOL(err == NRFX_SUCCESS);
    err = nrfx_ppi_channel_enable(m_ppi_channels[PPI_CH_COMPARE_SHUTDOWN]);
    APP_ERROR_CHECK_BOOL(err == NRFX_SUCCESS);

    mp_curr_rx_buf = p_data;
    m_rx_chunk_size = chunk_size;
    ret_code_t ret =  nrf_libuarte_rx_start(p_data, chunk_size, false);
    APP_ERROR_CHECK_BOOL(ret == NRF_SUCCESS);
}

ret_code_t nrf_libuarte_async_tx(uint8_t * p_data, size_t length)
{
    return nrf_libuarte_tx(p_data, length);
}

void nrf_libuarte_async_rx_free(uint8_t * p_data, size_t length)
{
    m_rx_free_cnt += length;
    if (m_rx_free_cnt == m_rx_chunk_size)
    {
        p_data -= (m_rx_free_cnt - length);
        m_rx_free_cnt = 0;
        nrf_balloc_free(&m_rx_pool, p_data);

        m_alloc_cnt--;
        if (m_alloc_cnt<0)
        {
            NRF_LOG_ERROR("Freeing more RX buffers than allocated.");
            APP_ERROR_CHECK_BOOL(false);
        }
        NRF_LOG_INFO("Freeing full buffer 0x%08X, %d, (currently allocated:%d).",p_data, length, m_alloc_cnt);
    }
    else if (m_rx_free_cnt > m_rx_chunk_size)
    {
        NRF_LOG_ERROR("Unexpected RX free input parameter.")
        APP_ERROR_CHECK_BOOL(false);
    }
    else
    {
        NRF_LOG_INFO("Freeing partial buffer: 0x%08X, length:%d", p_data, length)
    }

}
