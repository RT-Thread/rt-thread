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
#include "nrf_libuarte.h"
#include "nrfx_ppi.h"
#include "nrf_uarte.h"
#include "nrf_gpio.h"
#include "nrfx_timer.h"



#define NRF_LOG_MODULE_NAME libUARTE
#if NRF_LIBUARTE_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_LIBUARTE_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_LIBUARTE_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_LIBUARTE_CONFIG_DEBUG_COLOR
#else // NRF_LIBUARTE_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NRF_LIBUARTE_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#define INTERRUPTS_MASK  \
    (NRF_UARTE_INT_ENDRX_MASK | NRF_UARTE_INT_RXSTARTED_MASK | NRF_UARTE_INT_ERROR_MASK | \
     NRF_UARTE_INT_ENDTX_MASK | NRF_UARTE_INT_TXSTOPPED_MASK)

#define UART_DRV_UARTE CONCAT_2(NRF_UARTE, NRF_LIBUARTE_CONFIG_UARTE_USED)

#if NRF_LIBUARTE_CONFIG_UARTE_USED == 0
#define UART_DRV_IRQn       UARTE0_UART0_IRQn
#define UART_DRV_IRQHandler UARTE0_UART0_IRQHandler
#define MAX_DMA_XFER_LEN    (1<<UARTE0_EASYDMA_MAXCNT_SIZE)
#elif NRF_LIBUARTE_CONFIG_UARTE_USED == 1
#define UART_DRV_IRQn       UARTE1_UART1_IRQn
#define UART_DRV_IRQHandler UARTE1_IRQHandler
#define MAX_DMA_XFER_LEN    (1<<UARTE1_EASYDMA_MAXCNT_SIZE)
#endif

typedef enum
{
    PPI_CH_EXT_TRIGGER_STARTRX_EN_ENDRX_STARTX,
    PPI_CH_RXSTARTED_EXT_TSK,
    PPI_CH_EXT_STOP_STOPRX,
    PPI_CH_EXT_STOP_GROUPS_EN,
    PPI_CH_RXRDY_TIMER_COUNT,

    PPI_CH_RX_MAX,
    PPI_CH_ENDRX_STARTRX = PPI_CH_RX_MAX,
    PPI_CH_ENDRX_EXT_TSK,

    PPI_CH_RX_GROUP_MAX,

    PPI_CH_ENDTX_STARTTX = PPI_CH_RX_GROUP_MAX,

    PPI_CH_MAX
} nrf_libuarte_ppi_channel_t;

typedef enum
{
    PPI_GROUP_ENDRX_STARTRX,
    PPI_GROUP_ENDRX_EXT_RXDONE_TSK,
    PPI_GROUP_MAX
} nrf_libuarte_ppi_group_t;

static nrfx_timer_t m_timer = NRFX_TIMER_INSTANCE(NRF_LIBUARTE_CONFIG_TIMER_USED);

#if CONCAT_3(NRFX_TIMER, NRF_LIBUARTE_CONFIG_TIMER_USED,_ENABLED) == 0
#error "Timer instance not enabled"
#endif

static nrf_ppi_channel_t m_ppi_channels[PPI_CH_MAX];
static nrf_ppi_channel_group_t m_ppi_groups[PPI_GROUP_MAX];

static uint8_t * mp_tx;
static size_t m_tx_len;
static size_t m_tx_cur_idx;

static uint8_t * mp_cur_rx;
static uint8_t * mp_next_rx;
static uint8_t * mp_next_next_rx;
static nrf_libuarte_evt_handler_t m_evt_handler;
static uint32_t m_last_rx_byte_cnt;
static uint32_t m_last_pin_rx_byte_cnt;
static uint8_t m_tx_chunk8;
static uint32_t m_chunk_size;

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

#define PPI_GROUP_SETUP(_ch, _group, _en_tsk, _dis_tsk)                        \
        ret = nrfx_ppi_channel_include_in_group(m_ppi_channels[_ch],           \
                                                 m_ppi_groups[_group]);        \
        if (ret != NRF_SUCCESS)                                                \
        {                                                                      \
            return NRF_ERROR_INTERNAL;                                         \
        }                                                                      \
        _en_tsk = nrfx_ppi_task_addr_group_enable_get(m_ppi_groups[_group]);   \
        _dis_tsk = nrfx_ppi_task_addr_group_disable_get(m_ppi_groups[_group]);


static ret_code_t ppi_configure(nrf_libuarte_config_t * p_config)
{
    ret_code_t ret;

/*lint -save -e666 */

    ///////////////////////////////////////////////////////////////////////////////
    uint32_t group1_en_tsk;
    uint32_t group1_dis_tsk;

    PPI_GROUP_SETUP(PPI_CH_ENDRX_STARTRX, PPI_GROUP_ENDRX_STARTRX, group1_en_tsk, group1_dis_tsk);

    PPI_CH_SETUP(PPI_CH_ENDRX_STARTRX,
                 nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDRX),
                 nrf_uarte_task_address_get(UART_DRV_UARTE, NRF_UARTE_TASK_STARTRX),
                 nrfx_timer_capture_task_address_get(&m_timer, 0));


    ///////////////////////////////////////////////////////////////////////////////
    uint32_t group2_en_tsk;
    uint32_t group2_dis_tsk;

    PPI_GROUP_SETUP(PPI_CH_ENDRX_EXT_TSK, PPI_GROUP_ENDRX_EXT_RXDONE_TSK, group2_en_tsk, group2_dis_tsk);

    PPI_CH_SETUP(PPI_CH_ENDRX_EXT_TSK,
                 nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDRX),
                 nrfx_timer_capture_task_address_get(&m_timer, 0),
                 p_config->rxdone_tsk);

    ///////////////////////////////////////////////////////////////////////////////
    PPI_CH_SETUP(PPI_CH_EXT_TRIGGER_STARTRX_EN_ENDRX_STARTX,
                 p_config->startrx_evt,
                 group1_en_tsk,
                 nrf_uarte_task_address_get(UART_DRV_UARTE, NRF_UARTE_TASK_STARTRX));

    ///////////////////////////////////////////////////////////////////////////////
    PPI_CH_SETUP(PPI_CH_RXSTARTED_EXT_TSK,
                 nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_RXSTARTED),
                 group2_dis_tsk,
                 p_config->rxstarted_tsk);

    if (p_config->endrx_evt)
    {
        ///////////////////////////////////////////////////////////////////////////////
        PPI_CH_SETUP(PPI_CH_EXT_STOP_STOPRX,
                     p_config->endrx_evt,
                     nrf_uarte_task_address_get(UART_DRV_UARTE, NRF_UARTE_TASK_STOPRX),
                     group2_en_tsk);

        ///////////////////////////////////////////////////////////////////////////////
        PPI_CH_SETUP(PPI_CH_EXT_STOP_GROUPS_EN,
                     p_config->endrx_evt,
                     group1_dis_tsk,
                     nrfx_timer_capture_task_address_get(&m_timer, 1));
    }

    ////////////////////////////////TX///////////////////////////////////////////////
    PPI_CH_SETUP(PPI_CH_ENDTX_STARTTX,
                 nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDTX),
                 nrf_uarte_task_address_get(UART_DRV_UARTE, NRF_UARTE_TASK_STARTTX),
                 0);

    ////////////////////////////////TX///////////////////////////////////////////////
    PPI_CH_SETUP(PPI_CH_RXRDY_TIMER_COUNT,
                 nrf_uarte_event_address_get(UART_DRV_UARTE, NRF_UARTE_EVENT_RXDRDY),
                 nrfx_timer_task_address_get(&m_timer, NRF_TIMER_TASK_COUNT),
                 0);

    if (ret != NRFX_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
    return NRF_SUCCESS;
/*lint -restore */
}

void tmr_evt_handler(nrf_timer_event_t event_type, void * p_context)
{
    UNUSED_PARAMETER(event_type);
    UNUSED_PARAMETER(p_context);
}

ret_code_t nrf_libuarte_init(nrf_libuarte_config_t * p_config, nrf_libuarte_evt_handler_t evt_handler)
{
    ret_code_t ret;
    m_evt_handler = evt_handler;
    mp_cur_rx = NULL;
    mp_next_rx = NULL;
    mp_next_next_rx = NULL;
    mp_tx = NULL;

    //UART init
    nrf_gpio_pin_set(p_config->tx_pin);
    nrf_gpio_cfg_output(p_config->tx_pin);
    nrf_gpio_cfg_input(p_config->rx_pin, NRF_GPIO_PIN_NOPULL);
    nrf_uarte_baudrate_set(UART_DRV_UARTE, p_config->baudrate);
    nrf_uarte_configure(UART_DRV_UARTE, p_config->parity, p_config->hwfc);
    nrf_uarte_txrx_pins_set(UART_DRV_UARTE, p_config->tx_pin, p_config->rx_pin);

    if (p_config->hwfc == NRF_UARTE_HWFC_ENABLED)
    {
        if (p_config->cts_pin != NRF_UARTE_PSEL_DISCONNECTED)
        {
            nrf_gpio_cfg_input(p_config->cts_pin, NRF_GPIO_PIN_NOPULL);
        }
        if (p_config->rts_pin != NRF_UARTE_PSEL_DISCONNECTED)
        {
            nrf_gpio_pin_set(p_config->rts_pin);
            nrf_gpio_cfg_output(p_config->rts_pin);
        }
        nrf_uarte_hwfc_pins_set(UART_DRV_UARTE, p_config->rts_pin, p_config->cts_pin);
    }

    nrf_uarte_int_enable(UART_DRV_UARTE, INTERRUPTS_MASK);

    NVIC_SetPriority(UART_DRV_IRQn, p_config->irq_priority);
    NVIC_ClearPendingIRQ(UART_DRV_IRQn);
    NVIC_EnableIRQ(UART_DRV_IRQn);

    nrf_uarte_enable(UART_DRV_UARTE);

    nrfx_timer_config_t tmr_config = NRFX_TIMER_DEFAULT_CONFIG;
    tmr_config.mode = NRF_TIMER_MODE_COUNTER;
    tmr_config.bit_width = NRF_TIMER_BIT_WIDTH_32;
    ret = nrfx_timer_init(&m_timer, &tmr_config, tmr_evt_handler);
    if (ret != NRFX_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
    nrfx_timer_enable(&m_timer);
    nrfx_timer_clear(&m_timer);
    m_last_rx_byte_cnt = 0;
    m_last_pin_rx_byte_cnt = 0;

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

    for (i = 0; i < PPI_GROUP_MAX; i++)
    {
        ret = nrfx_ppi_group_alloc(&m_ppi_groups[i]);
        if (ret != NRFX_SUCCESS)
        {
            //we don't free already allocated channels, system is wrongly configured.
            return NRF_ERROR_INTERNAL;
        }
    }

    return ppi_configure(p_config);
}

void nrf_libuarte_uninit(void)
{
    NVIC_DisableIRQ(UART_DRV_IRQn);
    nrf_uarte_int_disable(UART_DRV_UARTE, 0xFFFFFFFF);
    nrf_uarte_disable(UART_DRV_UARTE);

    nrfx_timer_disable(&m_timer);
    nrfx_timer_uninit(&m_timer);

    uint32_t i;
    ret_code_t ret;
    for (i = 0; i < PPI_CH_MAX; i++)
    {
        ret = nrfx_ppi_channel_disable(m_ppi_channels[i]);
        ASSERT(ret == NRFX_SUCCESS)
        ret = nrfx_ppi_channel_free(m_ppi_channels[i]);
        ASSERT(ret == NRFX_SUCCESS)
    }

    for (i = 0; i < PPI_GROUP_MAX; i++)
    {
        ret = nrfx_ppi_group_free(m_ppi_groups[i]);
        ASSERT(ret == NRFX_SUCCESS)
    }

}

ret_code_t nrf_libuarte_tx(uint8_t * p_data, size_t len)
{
    if (mp_tx)
    {
        return NRF_ERROR_BUSY;
    }
    mp_tx = p_data;
    m_tx_len = len;
    m_tx_cur_idx = 0;
    uint8_t first_chunk;

    if (len <= MAX_DMA_XFER_LEN)
    {
        first_chunk = len;
        m_tx_chunk8 = 0;
    }
    else
    {
        uint32_t num_of_chunks = CEIL_DIV(len, MAX_DMA_XFER_LEN);
        m_tx_chunk8 =  len/num_of_chunks;
        first_chunk = m_tx_chunk8 + len%m_tx_chunk8;
    }

    NRF_LOG_DEBUG("Started TX total length:%d, first chunk:%d", len, first_chunk);
    nrf_uarte_tx_buffer_set(UART_DRV_UARTE, p_data, first_chunk);
    nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTARTED);
    nrf_uarte_task_trigger(UART_DRV_UARTE, NRF_UARTE_TASK_STARTTX);

    if (len > MAX_DMA_XFER_LEN)
    {
        while(nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTARTED) == 0)
        {
        }
        nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTARTED);
        nrfx_err_t err = nrfx_ppi_channel_enable(m_ppi_channels[PPI_CH_ENDTX_STARTTX]);
        if (err != NRFX_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }

        nrf_uarte_tx_buffer_set(UART_DRV_UARTE, &p_data[first_chunk], m_tx_chunk8);
    }
    return NRF_SUCCESS;
}

ret_code_t nrf_libuarte_rx_start(uint8_t * p_data, size_t len, bool ext_trigger_en)
{

    m_chunk_size = len;

    uint32_t i;
    for (i = 0; i < PPI_CH_RX_MAX; i++)
    {
        nrfx_err_t err = nrfx_ppi_channel_enable(m_ppi_channels[i]);
        if (err != NRFX_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }
    }

    ASSERT(len <= MAX_DMA_XFER_LEN);

    if (p_data)
    {
        mp_cur_rx = p_data;
        nrf_uarte_rx_buffer_set(UART_DRV_UARTE, p_data, len);
    }

    nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDRX);
    nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_RXSTARTED);
    if (ext_trigger_en)
    {
    }
    else
    {

        *(uint32_t *)nrfx_ppi_task_addr_group_enable_get(m_ppi_groups[PPI_GROUP_ENDRX_STARTRX]) = 1;
        nrf_uarte_task_trigger(UART_DRV_UARTE, NRF_UARTE_TASK_STARTRX);
    }
    NRF_LOG_DEBUG("Start continues RX. Provided buffer:0x%08X", p_data);
    return NRF_SUCCESS;
}

void nrf_libuarte_rx_buf_rsp(uint8_t * p_data, size_t len)
{
    if (mp_next_rx == NULL)
    {
        mp_next_rx = p_data;
        NRF_LOG_DEBUG("RX buf response (next). Provided buffer:0x%08X", p_data);
        nrf_uarte_rx_buffer_set(UART_DRV_UARTE, p_data, len);
    }
    else
    {
        NRF_LOG_DEBUG("RX buf response (mp_next_rx not NULL:0x%08X), Provided buffer:0x%08X",
                                                                                         mp_next_rx,
                                                                                         p_data);
        mp_next_next_rx = p_data;
    }
}

void nrf_libuarte_rx_stop(void)
{
    uint32_t i;
    for (i = 0; i < PPI_CH_RX_MAX; i++)
    {
        nrfx_err_t err = nrfx_ppi_channel_disable(m_ppi_channels[i]);
        ASSERT(err == NRFX_SUCCESS);
    }

    NRF_LOG_DEBUG("RX stopped.");
    nrf_uarte_task_trigger(UART_DRV_UARTE, NRF_UARTE_TASK_STOPRX);
}

void UART_DRV_IRQHandler(void)
{
    if (nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_ERROR))
    {
        nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_ERROR);
        nrf_libuarte_evt_t evt = {
                .type = NRF_LIBUARTE_EVT_ERROR
        };
        m_evt_handler(&evt);
    }

    if (nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_RXSTARTED))
    {
        nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_RXSTARTED);

        nrf_libuarte_evt_t evt = {
                .type = NRF_LIBUARTE_EVT_RX_BUF_REQ,
        };
        m_evt_handler(&evt);
    }

    if (nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDRX))
    {
        nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDRX);

        uint32_t endrx_byte_cnt = nrfx_timer_capture_get(&m_timer, NRF_TIMER_CC_CHANNEL0);
        uint32_t stop_byte_cnt  = nrfx_timer_capture_get(&m_timer, NRF_TIMER_CC_CHANNEL1);

        uint32_t dma_amount = endrx_byte_cnt - m_last_rx_byte_cnt;
        uint32_t pin_amount = stop_byte_cnt - m_last_pin_rx_byte_cnt;
        NRF_LOG_DEBUG("(evt) RX dma_cnt:%d, endrx_cnt:%d, stop_cnt:%d",
                     dma_amount,
                     endrx_byte_cnt,
                     stop_byte_cnt);
        m_last_rx_byte_cnt = endrx_byte_cnt;
        m_last_pin_rx_byte_cnt = stop_byte_cnt;

        if (dma_amount || pin_amount)
        {
            uint32_t chunk0 = (dma_amount > m_chunk_size) ? m_chunk_size : dma_amount;
            uint32_t chunk1 = dma_amount - chunk0;

            NRF_LOG_DEBUG("RX END chunk0:%d, chunk1:%d, data[0]=%d %d",
                         chunk0,
                         chunk1,
                         mp_cur_rx[0],
                         mp_cur_rx[1]);
            nrf_libuarte_evt_t evt = {
                    .type = NRF_LIBUARTE_EVT_RX_DATA,
                    .data = {
                            .rxtx = {
                                .p_data = mp_cur_rx,
                                .length = chunk0
                            }
                    }
            };
            mp_cur_rx = mp_next_rx;
            mp_next_rx = NULL;
            if (mp_next_next_rx)
            {
                mp_next_rx      = mp_next_next_rx;
                mp_next_next_rx = NULL;
                nrf_uarte_rx_buffer_set(UART_DRV_UARTE, mp_next_rx, m_chunk_size);
            }
            m_evt_handler(&evt);

            if ( chunk1 ||
                ((dma_amount == m_chunk_size) && (endrx_byte_cnt == stop_byte_cnt)))
            {
                NRF_LOG_WARNING("RX END Chunk1:%d", chunk1);

                evt.data.rxtx.length = chunk1;
                evt.data.rxtx.p_data = mp_cur_rx;

                mp_cur_rx  = mp_next_rx;
                mp_next_rx = NULL;
                m_evt_handler(&evt);
            }
        }
    }

    if (nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTOPPED))
    {
        nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTOPPED);
        nrf_libuarte_evt_t evt = {
           .type = NRF_LIBUARTE_EVT_TX_DONE,
           .data = {
               .rxtx = {
                   .p_data = mp_tx,
                   .length = m_tx_len
               }
           }
       };
       mp_tx = NULL;
       m_evt_handler(&evt);
    }

    if (nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDTX))
    {
        nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_ENDTX);
        uint8_t amount = nrf_uarte_tx_amount_get(UART_DRV_UARTE);
        NRF_LOG_DEBUG("(evt) TX completed (%d)", amount);
        m_tx_cur_idx += amount;
        if (m_tx_cur_idx == m_tx_len)
        {
            nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTOPPED);
            nrf_uarte_task_trigger(UART_DRV_UARTE, NRF_UARTE_TASK_STOPTX);
        }
        else
        {
            size_t rem_len = (m_tx_len - m_tx_cur_idx);
            if ( rem_len <= MAX_DMA_XFER_LEN)
            {
                nrfx_err_t err = nrfx_ppi_channel_disable(m_ppi_channels[PPI_CH_ENDTX_STARTTX]);
                ASSERT(err == NRFX_SUCCESS);
            }
            else
            {
                if (nrf_uarte_event_check(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTARTED) == 0)
                {
                    NRF_LOG_ERROR("Tx not started yet!");
                    ASSERT(false);
                }
                nrf_uarte_event_clear(UART_DRV_UARTE, NRF_UARTE_EVENT_TXSTARTED);
                nrf_uarte_tx_buffer_set(UART_DRV_UARTE, &mp_tx[m_tx_cur_idx + m_tx_chunk8], m_tx_chunk8);
            }
        }

    }
}
