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

#include "nrf_drv_spi.h"

#ifdef SPIM_PRESENT
#define INSTANCE_COUNT   SPIM_COUNT
#else
#define INSTANCE_COUNT   SPI_COUNT
#endif

static nrf_drv_spi_evt_handler_t m_handlers[INSTANCE_COUNT];
static void *                    m_contexts[INSTANCE_COUNT];

#ifdef SPIM_PRESENT
static void spim_evt_handler(nrfx_spim_evt_t const * p_event,
                             void *                  p_context)
{
    uint32_t inst_idx = (uint32_t)p_context;
    nrf_drv_spi_evt_t const event =
    {
        .type = (nrf_drv_spi_evt_type_t)p_event->type,
        .data =
        {
            .done =
            {
                .p_tx_buffer = p_event->xfer_desc.p_tx_buffer,
                .tx_length   = p_event->xfer_desc.tx_length,
                .p_rx_buffer = p_event->xfer_desc.p_rx_buffer,
                .rx_length   = p_event->xfer_desc.rx_length,
            }
        }
    };
    m_handlers[inst_idx](&event, m_contexts[inst_idx]);
}
#endif // SPIM_PRESENT

#ifdef SPI_PRESENT
static void spi_evt_handler(nrfx_spi_evt_t const * p_event,
                            void *                 p_context)
{
    uint32_t inst_idx = (uint32_t)p_context;
    nrf_drv_spi_evt_t const event =
    {
        .type = (nrf_drv_spi_evt_type_t)p_event->type,
        .data =
        {
            .done =
            {
                .p_tx_buffer = p_event->xfer_desc.p_tx_buffer,
                .tx_length   = p_event->xfer_desc.tx_length,
                .p_rx_buffer = p_event->xfer_desc.p_rx_buffer,
                .rx_length   = p_event->xfer_desc.rx_length,
            }
        }
    };
    m_handlers[inst_idx](&event, m_contexts[inst_idx]);
}
#endif // SPI_PRESENT

ret_code_t nrf_drv_spi_init(nrf_drv_spi_t const * const p_instance,
                            nrf_drv_spi_config_t const * p_config,
                            nrf_drv_spi_evt_handler_t    handler,
                            void *                       p_context)
{
    uint32_t inst_idx = p_instance->inst_idx;
    m_handlers[inst_idx] = handler;
    m_contexts[inst_idx] = p_context;

    ret_code_t result = 0;
    if (NRF_DRV_SPI_USE_SPIM)
    {
#ifdef SPIM_PRESENT
        nrfx_spim_config_t config_spim = NRFX_SPIM_DEFAULT_CONFIG;
        config_spim.sck_pin        = p_config->sck_pin;
        config_spim.mosi_pin       = p_config->mosi_pin;
        config_spim.miso_pin       = p_config->miso_pin;
        config_spim.ss_pin         = p_config->ss_pin;
        config_spim.irq_priority   = p_config->irq_priority;
        config_spim.orc            = p_config->orc;
        config_spim.frequency      = (nrf_spim_frequency_t)p_config->frequency;
        config_spim.mode           = (nrf_spim_mode_t)p_config->mode;
        config_spim.bit_order      = (nrf_spim_bit_order_t)p_config->bit_order;
        result = nrfx_spim_init(&p_instance->u.spim,
                                &config_spim,
                                handler ? spim_evt_handler : NULL,
                                (void *)inst_idx);
#endif
    }
    else if (NRF_DRV_SPI_USE_SPI)
    {
        result = nrfx_spi_init(&p_instance->u.spi,
                               (nrfx_spi_config_t const *)p_config,
                               handler ? spi_evt_handler : NULL,
                               (void *)inst_idx);
    }
    return result;
}
