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

#include "nrf_drv_uart.h"

#ifdef UARTE_PRESENT
#define INSTANCE_COUNT   UARTE_COUNT
#else
#define INSTANCE_COUNT   UART_COUNT
#endif

static nrf_uart_event_handler_t m_handlers[INSTANCE_COUNT];
static void *                   m_contexts[INSTANCE_COUNT];

#if defined(UARTE_PRESENT) && defined(UART_PRESENT)
uint8_t nrf_drv_uart_use_easy_dma[INSTANCE_COUNT];
#endif

#if defined(NRF_DRV_UART_WITH_UARTE)
static void uarte_evt_handler(nrfx_uarte_event_t const * p_event,
                              void *                     p_context)
{
    uint32_t inst_idx = (uint32_t)p_context;
    nrf_drv_uart_event_t event =
    {
        .type = (nrf_drv_uart_evt_type_t)p_event->type,
        .data =
        {
            .error =
            {
                .rxtx =
                {
                    .p_data = p_event->data.error.rxtx.p_data,
                    .bytes  = p_event->data.error.rxtx.bytes,
                },
                .error_mask = p_event->data.error.error_mask,
            }
        }
    };
    m_handlers[inst_idx](&event, m_contexts[inst_idx]);
}
#endif // defined(NRF_DRV_UART_WITH_UARTE)

#if defined(NRF_DRV_UART_WITH_UART)
static void uart_evt_handler(nrfx_uart_event_t const * p_event,
                             void *                    p_context)
{
    uint32_t inst_idx = (uint32_t)p_context;
    nrf_drv_uart_event_t event =
    {
        .type = (nrf_drv_uart_evt_type_t)p_event->type,
        .data =
        {
            .error =
            {
                .rxtx =
                {
                    .p_data = p_event->data.error.rxtx.p_data,
                    .bytes  = p_event->data.error.rxtx.bytes,
                },
                .error_mask = p_event->data.error.error_mask,
            }
        }
    };
    m_handlers[inst_idx](&event, m_contexts[inst_idx]);
}
#endif // defined(NRF_DRV_UART_WITH_UART)

ret_code_t nrf_drv_uart_init(nrf_drv_uart_t const *        p_instance,
                             nrf_drv_uart_config_t const * p_config,
                             nrf_uart_event_handler_t      event_handler)
{
    uint32_t inst_idx = p_instance->inst_idx;
    m_handlers[inst_idx] = event_handler;
    m_contexts[inst_idx] = p_config->p_context;

#if defined(NRF_DRV_UART_WITH_UARTE) && defined(NRF_DRV_UART_WITH_UART)
#ifdef NRF52840_XXAA
    if (inst_idx == 1)
    {
        ASSERT(p_config->use_easy_dma);
    }
#endif
    nrf_drv_uart_use_easy_dma[inst_idx] = p_config->use_easy_dma;
#endif

    nrf_drv_uart_config_t config = *p_config;
    config.p_context = (void *)inst_idx;

    ret_code_t result = 0;
    if (NRF_DRV_UART_USE_UARTE)
    {
        result = nrfx_uarte_init(&p_instance->uarte,
                                 (nrfx_uarte_config_t const *)&config,
                                 event_handler ? uarte_evt_handler : NULL);
    }
    else if (NRF_DRV_UART_USE_UART)
    {
        result = nrfx_uart_init(&p_instance->uart,
                                (nrfx_uart_config_t const *)&config,
                                event_handler ? uart_evt_handler : NULL);
    }
    return result;
}
