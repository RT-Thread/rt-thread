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
#include "sdk_config.h"
#include "nrf_libuarte.h"
#include "nrf_uarte.h"
#include "nrf_gpio.h"

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

#define MAX_DMA_XFER_LEN    ((1UL << UARTE0_EASYDMA_MAXCNT_SIZE) - 1)

#define INTERRUPTS_MASK  \
    (NRF_UARTE_INT_ENDRX_MASK | NRF_UARTE_INT_RXSTARTED_MASK | NRF_UARTE_INT_ERROR_MASK | \
     NRF_UARTE_INT_ENDTX_MASK | NRF_UARTE_INT_TXSTOPPED_MASK)

/** Macro is setting up PPI channel set which consist of event, task and optional fork.
 *
 * @param _ch   Channel.
 * @param _evt  Event.
 * @param _tsk  Task.
 * @param _fork Fork. If NULL fork is not configured.
 */
#define PPI_CH_SETUP(_ch, _evt, _tsk, _fork)            \
    ret = nrfx_ppi_channel_assign(_ch, _evt, _tsk);     \
    if (ret != NRFX_SUCCESS)                            \
    {                                                   \
        return NRF_ERROR_INTERNAL;                      \
    }                                                   \
    if (_fork)                                          \
    {                                                   \
        ret = nrfx_ppi_channel_fork_assign(_ch, _fork); \
        if (ret != NRFX_SUCCESS)                        \
        {                                               \
            return NRF_ERROR_INTERNAL;                  \
        }                                               \
    }

/** Macro for setting up PPI group with one channel and getting tasks to
 *  control that group.
 *
 * @param[in] _ch       Channel to be included in the group.
 * @param[in] _group    Group.
 * @param[out] _en_tsk  Address of the task to enable group.
 * @param[out] _dis_tsk Address of the task to disable group.
 */
#define PPI_GROUP_SETUP(_ch, _group, _en_tsk, _dis_tsk)           \
        ret = nrfx_ppi_channel_include_in_group(_ch,  _group);    \
        if (ret != NRFX_SUCCESS)                                  \
        {                                                         \
            return NRF_ERROR_INTERNAL;                            \
        }                                                         \
        _en_tsk = nrfx_ppi_task_addr_group_enable_get(_group);    \
        _dis_tsk = nrfx_ppi_task_addr_group_disable_get(_group)

static const nrf_libuarte_t * m_libuarte_instance[2];

static ret_code_t ppi_configure(const nrf_libuarte_t * const p_libuarte,
                                nrf_libuarte_config_t * p_config)
{
    nrfx_err_t ret;

/*lint -save -e666 */

    uint32_t group1_en_tsk = 0;
    uint32_t group1_dis_tsk = 0;
    uint32_t group2_en_tsk = 0;
    uint32_t group2_dis_tsk = 0;

    if (p_config->endrx_evt)
    {
        PPI_GROUP_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDRX_STARTRX],
                        p_libuarte->ctrl_blk->ppi_groups[NRF_LIBUARTE_PPI_GROUP_ENDRX_STARTRX],
                        group1_en_tsk, group1_dis_tsk);

        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDRX_STARTRX],
                     nrf_uarte_event_address_get(p_libuarte->uarte, NRF_UARTE_EVENT_ENDRX),
                     nrf_uarte_task_address_get(p_libuarte->uarte, NRF_UARTE_TASK_STARTRX),
                     nrfx_timer_capture_task_address_get(&p_libuarte->timer, 0));

        PPI_GROUP_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDRX_EXT_TSK],
                        p_libuarte->ctrl_blk->ppi_groups[NRF_LIBUARTE_PPI_GROUP_ENDRX_EXT_RXDONE_TSK],
                        group2_en_tsk, group2_dis_tsk);

        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_EXT_TRIGGER_STARTRX_EN_ENDRX_STARTX],
                     p_config->startrx_evt,
                     nrf_uarte_task_address_get(p_libuarte->uarte, NRF_UARTE_TASK_STARTRX),
                     group1_en_tsk);
    }
    else
    {
        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_EXT_TRIGGER_STARTRX_EN_ENDRX_STARTX],
                     p_config->startrx_evt,
                     nrf_uarte_task_address_get(p_libuarte->uarte, NRF_UARTE_TASK_STARTRX),
                     nrfx_timer_capture_task_address_get(&p_libuarte->timer, 0));
    }

    if (p_config->endrx_evt && p_config->rxdone_tsk)
    {
        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDRX_EXT_TSK],
                     nrf_uarte_event_address_get(p_libuarte->uarte, NRF_UARTE_EVENT_ENDRX),
                     nrfx_timer_capture_task_address_get(&p_libuarte->timer, 0),
                     p_config->rxdone_tsk);
    }


    if (p_config->rxstarted_tsk)
    {
        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_RXSTARTED_EXT_TSK],
                     nrf_uarte_event_address_get(p_libuarte->uarte, NRF_UARTE_EVENT_RXSTARTED),
                     group2_dis_tsk,
                     p_config->rxstarted_tsk);
    }

    if (p_config->endrx_evt)
    {
        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_EXT_STOP_STOPRX],
                     p_config->endrx_evt,
                     nrf_uarte_task_address_get(p_libuarte->uarte, NRF_UARTE_TASK_STOPRX),
                     group2_en_tsk);

        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_EXT_STOP_GROUPS_EN],
                     p_config->endrx_evt,
                     group1_dis_tsk,
                     nrfx_timer_capture_task_address_get(&p_libuarte->timer, 1));
    }

    if (MAX_DMA_XFER_LEN < UINT16_MAX)
    {
        PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDTX_STARTTX],
                     nrf_uarte_event_address_get(p_libuarte->uarte, NRF_UARTE_EVENT_ENDTX),
                     nrf_uarte_task_address_get(p_libuarte->uarte, NRF_UARTE_TASK_STARTTX),
                     0);
    }

    PPI_CH_SETUP(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_RXRDY_TIMER_COUNT],
                 nrf_uarte_event_address_get(p_libuarte->uarte, NRF_UARTE_EVENT_RXDRDY),
                 nrfx_timer_task_address_get(&p_libuarte->timer, NRF_TIMER_TASK_COUNT),
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

ret_code_t nrf_libuarte_init(const nrf_libuarte_t * const p_libuarte,
                             nrf_libuarte_config_t * p_config,
                             nrf_libuarte_evt_handler_t evt_handler,
                             void * context)
{
    ret_code_t ret;
    IRQn_Type irqn = nrfx_get_irq_number(p_libuarte->uarte);

    p_libuarte->ctrl_blk->evt_handler = evt_handler;
    p_libuarte->ctrl_blk->p_cur_rx = NULL;
    p_libuarte->ctrl_blk->p_next_rx = NULL;
    p_libuarte->ctrl_blk->p_next_next_rx = NULL;
    p_libuarte->ctrl_blk->p_tx = NULL;
    p_libuarte->ctrl_blk->context = context;

    m_libuarte_instance[p_libuarte->uarte == NRF_UARTE0 ? 0 : 1] = p_libuarte;

    //UART init
    nrf_gpio_pin_set(p_config->tx_pin);
    nrf_gpio_cfg_output(p_config->tx_pin);
    nrf_gpio_cfg_input(p_config->rx_pin, NRF_GPIO_PIN_NOPULL);
    nrf_uarte_baudrate_set(p_libuarte->uarte, p_config->baudrate);
    nrf_uarte_configure(p_libuarte->uarte, p_config->parity, p_config->hwfc);
    nrf_uarte_txrx_pins_set(p_libuarte->uarte, p_config->tx_pin, p_config->rx_pin);

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
        nrf_uarte_hwfc_pins_set(p_libuarte->uarte, p_config->rts_pin, p_config->cts_pin);
    }

    nrf_uarte_int_enable(p_libuarte->uarte, INTERRUPTS_MASK);

    NVIC_SetPriority(irqn, p_config->irq_priority);
    NVIC_ClearPendingIRQ(irqn);
    NVIC_EnableIRQ(irqn);

    nrf_uarte_enable(p_libuarte->uarte);

    nrfx_timer_config_t tmr_config = NRFX_TIMER_DEFAULT_CONFIG;
    tmr_config.mode = NRF_TIMER_MODE_COUNTER;
    tmr_config.bit_width = NRF_TIMER_BIT_WIDTH_32;
    ret = nrfx_timer_init(&p_libuarte->timer, &tmr_config, tmr_evt_handler);
    if (ret != NRFX_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
    nrfx_timer_enable(&p_libuarte->timer);
    nrfx_timer_clear(&p_libuarte->timer);
    p_libuarte->ctrl_blk->last_rx_byte_cnt = 0;
    p_libuarte->ctrl_blk->last_pin_rx_byte_cnt = 0;

    uint32_t i;
    for (i = 0; i < NRF_LIBUARTE_PPI_CH_MAX; i++)
    {
        if ((p_config->endrx_evt == 0) &&
            ((i == NRF_LIBUARTE_PPI_CH_EXT_STOP_STOPRX) ||
             (i == NRF_LIBUARTE_PPI_CH_EXT_STOP_GROUPS_EN) ||
             (i == NRF_LIBUARTE_PPI_CH_ENDRX_STARTRX) ||
             (i == NRF_LIBUARTE_PPI_CH_ENDRX_EXT_TSK)
             )
           ) {
            // skip ppi allocation
            p_libuarte->ctrl_blk->ppi_channels[i] = (nrf_ppi_channel_t)PPI_CH_NUM;
        }
        else if (p_config->rxstarted_tsk == 0 &&
                (i == NRF_LIBUARTE_PPI_CH_RXSTARTED_EXT_TSK))
        {
            p_libuarte->ctrl_blk->ppi_channels[i] = (nrf_ppi_channel_t)PPI_CH_NUM;
        }
        else if ((MAX_DMA_XFER_LEN >= UINT16_MAX) &&
                (i == NRF_LIBUARTE_PPI_CH_ENDTX_STARTTX))
        {
            p_libuarte->ctrl_blk->ppi_channels[i] = (nrf_ppi_channel_t)PPI_CH_NUM;
        }
        else
        {
            ret = nrfx_ppi_channel_alloc(&p_libuarte->ctrl_blk->ppi_channels[i]);
            if (ret != NRFX_SUCCESS)
            {
                //we don't free already allocated channels, system is wrongly configured.
                return NRF_ERROR_INTERNAL;
            }
        }
    }

    for (i = 0; i < NRF_LIBUARTE_PPI_GROUP_MAX; i++)
    {
        if (p_config->endrx_evt)
        {
            ret = nrfx_ppi_group_alloc(&p_libuarte->ctrl_blk->ppi_groups[i]);
            if (ret != NRFX_SUCCESS)
            {
                //we don't free already allocated channels, system is wrongly configured.
                return NRF_ERROR_INTERNAL;
            }
        }
        else
        {
            p_libuarte->ctrl_blk->ppi_groups[i] = (nrf_ppi_channel_group_t)PPI_GROUP_NUM;
        }
    }

    return ppi_configure(p_libuarte, p_config);
}

void nrf_libuarte_uninit(const nrf_libuarte_t * const p_libuarte)
{
    IRQn_Type irqn = nrfx_get_irq_number(p_libuarte->uarte);

    NVIC_DisableIRQ(irqn);
    nrf_uarte_int_disable(p_libuarte->uarte, 0xFFFFFFFF);
    nrf_uarte_disable(p_libuarte->uarte);

    nrfx_timer_disable(&p_libuarte->timer);
    nrfx_timer_uninit(&p_libuarte->timer);

    uint32_t i;
    ret_code_t ret;
    for (i = 0; i < NRF_LIBUARTE_PPI_CH_MAX; i++)
    {
        if (p_libuarte->ctrl_blk->ppi_channels[i] < PPI_CH_NUM)
        {
            ret = nrfx_ppi_channel_disable(p_libuarte->ctrl_blk->ppi_channels[i]);
            ASSERT(ret == NRFX_SUCCESS)
            ret = nrfx_ppi_channel_free(p_libuarte->ctrl_blk->ppi_channels[i]);
            ASSERT(ret == NRFX_SUCCESS)
        }
    }

    for (i = 0; i < NRF_LIBUARTE_PPI_GROUP_MAX; i++)
    {
        if (p_libuarte->ctrl_blk->ppi_groups[i] < PPI_GROUP_NUM)
        {
            ret = nrfx_ppi_group_free(p_libuarte->ctrl_blk->ppi_groups[i]);
            ASSERT(ret == NRFX_SUCCESS)
        }
    }

}

ret_code_t nrf_libuarte_tx(const nrf_libuarte_t * const p_libuarte, uint8_t * p_data, size_t len)
{
    if (p_libuarte->ctrl_blk->p_tx)
    {
        return NRF_ERROR_BUSY;
    }
    p_libuarte->ctrl_blk->p_tx = p_data;
    p_libuarte->ctrl_blk->tx_len = len;
    p_libuarte->ctrl_blk->tx_cur_idx = 0;
    uint16_t first_chunk;

    if ((MAX_DMA_XFER_LEN <= UINT16_MAX) && (len <= MAX_DMA_XFER_LEN))
    {
        first_chunk = len;
        p_libuarte->ctrl_blk->tx_chunk8 = 0;
    }
    else
    {
        uint32_t num_of_chunks = CEIL_DIV(len, MAX_DMA_XFER_LEN);
        p_libuarte->ctrl_blk->tx_chunk8 =  len/num_of_chunks;
        first_chunk = p_libuarte->ctrl_blk->tx_chunk8 + len%p_libuarte->ctrl_blk->tx_chunk8;
    }

    NRF_LOG_WARNING("Started TX total length:%d, first chunk:%d", len, first_chunk);
    nrf_uarte_tx_buffer_set(p_libuarte->uarte, p_data, first_chunk);
    nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTARTED);
    nrf_uarte_task_trigger(p_libuarte->uarte, NRF_UARTE_TASK_STARTTX);

    if ((MAX_DMA_XFER_LEN <= UINT16_MAX) && (len > MAX_DMA_XFER_LEN))
    {
        while(nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTARTED) == 0)
        {
        }
        nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTARTED);
        nrfx_err_t err = nrfx_ppi_channel_enable(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDTX_STARTTX]);
        if (err != NRFX_SUCCESS)
        {
            return NRF_ERROR_INTERNAL;
        }

        nrf_uarte_tx_buffer_set(p_libuarte->uarte, &p_data[first_chunk], p_libuarte->ctrl_blk->tx_chunk8);
    }
    return NRF_SUCCESS;
}

ret_code_t nrf_libuarte_rx_start(const nrf_libuarte_t * const p_libuarte,
                                 uint8_t * p_data, size_t len, bool ext_trigger_en)
{

    p_libuarte->ctrl_blk->chunk_size = len;

    uint32_t i;
    for (i = 0; i < NRF_LIBUARTE_PPI_CH_RX_MAX; i++)
    {
        if (p_libuarte->ctrl_blk->ppi_channels[i] < PPI_CH_NUM)
        {
            nrfx_err_t err = nrfx_ppi_channel_enable(p_libuarte->ctrl_blk->ppi_channels[i]);
            if (err != NRFX_SUCCESS)
            {
                return NRF_ERROR_INTERNAL;
            }
        }
    }

    ASSERT(len <= MAX_DMA_XFER_LEN);

    if (p_data)
    {
        p_libuarte->ctrl_blk->p_cur_rx = p_data;
        nrf_uarte_rx_buffer_set(p_libuarte->uarte, p_data, len);
    }

    nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_ENDRX);
    nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_RXSTARTED);

    if (!ext_trigger_en)
    {
        *(uint32_t *)nrfx_ppi_task_addr_group_enable_get(p_libuarte->ctrl_blk->ppi_groups[NRF_LIBUARTE_PPI_GROUP_ENDRX_STARTRX]) = 1;
        nrf_uarte_task_trigger(p_libuarte->uarte, NRF_UARTE_TASK_STARTRX);
    }
    NRF_LOG_DEBUG("Start continues RX. Provided buffer:0x%08X", p_data);
    return NRF_SUCCESS;
}

void nrf_libuarte_rx_buf_rsp(const nrf_libuarte_t * const p_libuarte, uint8_t * p_data, size_t len)
{
    if (p_libuarte->ctrl_blk->p_next_rx == NULL)
    {
        p_libuarte->ctrl_blk->p_next_rx = p_data;
        NRF_LOG_DEBUG("RX buf response (next). Provided buffer:0x%08X", p_data);
        nrf_uarte_rx_buffer_set(p_libuarte->uarte, p_data, len);
    }
    else
    {
        NRF_LOG_DEBUG("RX buf response (mp_next_rx not NULL:0x%08X), Provided buffer:0x%08X",
                        p_libuarte->ctrl_blk->p_next_rx, p_data);
        p_libuarte->ctrl_blk->p_next_next_rx = p_data;
    }
}

void nrf_libuarte_rx_stop(const nrf_libuarte_t * const p_libuarte)
{
    uint32_t i;
    for (i = 0; i < NRF_LIBUARTE_PPI_CH_RX_MAX; i++)
    {
        if (p_libuarte->ctrl_blk->ppi_channels[i] < PPI_CH_NUM)
        {
            nrfx_err_t err = nrfx_ppi_channel_disable(p_libuarte->ctrl_blk->ppi_channels[i]);
            ASSERT(err == NRFX_SUCCESS);
        }
    }

    NRF_LOG_DEBUG("RX stopped.");
    nrf_uarte_task_trigger(p_libuarte->uarte, NRF_UARTE_TASK_STOPRX);
}

static void irq_handler(const nrf_libuarte_t * const p_libuarte)
{
    if (nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_ERROR))
    {
        nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_ERROR);
        nrf_libuarte_evt_t evt = {
                .type = NRF_LIBUARTE_EVT_ERROR
        };
        p_libuarte->ctrl_blk->evt_handler(p_libuarte->ctrl_blk->context, &evt);
    }

    if (nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_RXSTARTED))
    {
        nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_RXSTARTED);

        nrf_libuarte_evt_t evt = {
                .type = NRF_LIBUARTE_EVT_RX_BUF_REQ,
        };
        p_libuarte->ctrl_blk->evt_handler(p_libuarte->ctrl_blk->context, &evt);
    }

    if (nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_ENDRX))
    {
        nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_ENDRX);

        uint32_t endrx_byte_cnt = nrfx_timer_capture_get(&p_libuarte->timer, NRF_TIMER_CC_CHANNEL0);
        uint32_t stop_byte_cnt  = nrfx_timer_capture_get(&p_libuarte->timer, NRF_TIMER_CC_CHANNEL1);

        uint32_t dma_amount = endrx_byte_cnt - p_libuarte->ctrl_blk->last_rx_byte_cnt;
        uint32_t pin_amount = stop_byte_cnt - p_libuarte->ctrl_blk->last_pin_rx_byte_cnt;
        NRF_LOG_DEBUG("(evt) RX dma_cnt:%d, endrx_cnt:%d, stop_cnt:%d",
                     dma_amount,
                     endrx_byte_cnt,
                     stop_byte_cnt);
        p_libuarte->ctrl_blk->last_rx_byte_cnt = endrx_byte_cnt;
        p_libuarte->ctrl_blk->last_pin_rx_byte_cnt = stop_byte_cnt;

        if (dma_amount || pin_amount)
        {
            uint32_t chunk0 = (dma_amount > p_libuarte->ctrl_blk->chunk_size) ?
                                p_libuarte->ctrl_blk->chunk_size : dma_amount;
            uint32_t chunk1 = dma_amount - chunk0;

            NRF_LOG_DEBUG("RX END chunk0:%d, chunk1:%d, data[0]=%d %d",
                         chunk0,
                         chunk1,
                         p_libuarte->ctrl_blk->p_cur_rx[0],
                         p_libuarte->ctrl_blk->p_cur_rx[1]);
            nrf_libuarte_evt_t evt = {
                    .type = NRF_LIBUARTE_EVT_RX_DATA,
                    .data = {
                            .rxtx = {
                                .p_data = p_libuarte->ctrl_blk->p_cur_rx,
                                .length = chunk0
                            }
                    }
            };
            p_libuarte->ctrl_blk->p_cur_rx = p_libuarte->ctrl_blk->p_next_rx;
            p_libuarte->ctrl_blk->p_next_rx = NULL;
            if (p_libuarte->ctrl_blk->p_next_next_rx)
            {
                p_libuarte->ctrl_blk->p_next_rx = p_libuarte->ctrl_blk->p_next_next_rx;
                p_libuarte->ctrl_blk->p_next_next_rx = NULL;
                nrf_uarte_rx_buffer_set(p_libuarte->uarte,
                                        p_libuarte->ctrl_blk->p_next_rx,
                                        p_libuarte->ctrl_blk->chunk_size);
            }
            p_libuarte->ctrl_blk->evt_handler(p_libuarte->ctrl_blk->context, &evt);

            if ( chunk1 ||
                ((dma_amount == p_libuarte->ctrl_blk->chunk_size) && (endrx_byte_cnt == stop_byte_cnt)))
            {
                NRF_LOG_WARNING("RX END Chunk1:%d", chunk1);

                evt.data.rxtx.length = chunk1;
                evt.data.rxtx.p_data = p_libuarte->ctrl_blk->p_cur_rx;

                p_libuarte->ctrl_blk->p_cur_rx  = p_libuarte->ctrl_blk->p_next_rx;
                p_libuarte->ctrl_blk->p_next_rx = NULL;
                p_libuarte->ctrl_blk->evt_handler(p_libuarte->ctrl_blk->context, &evt);
            }
        }
    }

    if (nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTOPPED))
    {
        nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTOPPED);
        nrf_libuarte_evt_t evt = {
           .type = NRF_LIBUARTE_EVT_TX_DONE,
           .data = {
               .rxtx = {
                   .p_data = p_libuarte->ctrl_blk->p_tx,
                   .length = p_libuarte->ctrl_blk->tx_len
               }
           }
       };
       p_libuarte->ctrl_blk->p_tx = NULL;
       p_libuarte->ctrl_blk->evt_handler(p_libuarte->ctrl_blk->context, &evt);
    }

    if (nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_ENDTX))
    {
        nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_ENDTX);
        size_t amount = nrf_uarte_tx_amount_get(p_libuarte->uarte);

        NRF_LOG_DEBUG("(evt) TX completed (%d)", amount);
        p_libuarte->ctrl_blk->tx_cur_idx += amount;
        if (p_libuarte->ctrl_blk->tx_cur_idx == p_libuarte->ctrl_blk->tx_len)
        {
            nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTOPPED);
            nrf_uarte_task_trigger(p_libuarte->uarte, NRF_UARTE_TASK_STOPTX);
        }
        else
        {
            size_t rem_len = (p_libuarte->ctrl_blk->tx_len - p_libuarte->ctrl_blk->tx_cur_idx);
            if ( rem_len <= MAX_DMA_XFER_LEN)
            {
                nrfx_err_t err =
                   nrfx_ppi_channel_disable(p_libuarte->ctrl_blk->ppi_channels[NRF_LIBUARTE_PPI_CH_ENDTX_STARTTX]);
                ASSERT(err == NRFX_SUCCESS);
            }
            else
            {
                uint8_t * p_buffer = &p_libuarte->ctrl_blk->p_tx[
                                                               p_libuarte->ctrl_blk->tx_cur_idx +
                                                               p_libuarte->ctrl_blk->tx_chunk8];
                if (nrf_uarte_event_check(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTARTED) == 0)
                {
                    NRF_LOG_ERROR("Tx not started yet!");
                    ASSERT(false);
                }
                nrf_uarte_event_clear(p_libuarte->uarte, NRF_UARTE_EVENT_TXSTARTED);
                nrf_uarte_tx_buffer_set(p_libuarte->uarte,
                                        p_buffer,
                                        p_libuarte->ctrl_blk->tx_chunk8);
            }
        }

    }
}

#if NRF_LIBUARTE_UARTE0
void UARTE0_UART0_IRQHandler(void)
{
    irq_handler(m_libuarte_instance[0]);
}
#endif

#if NRF_LIBUARTE_UARTE1
void UARTE1_IRQHandler(void)
{
    irq_handler(m_libuarte_instance[1]);
}
#endif
