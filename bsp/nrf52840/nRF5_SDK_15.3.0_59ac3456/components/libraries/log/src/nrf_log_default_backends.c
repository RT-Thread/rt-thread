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
#if NRF_MODULE_ENABLED(NRF_LOG)
#include "nrf_log_default_backends.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_internal.h"
#include "nrf_assert.h"

#if defined(NRF_LOG_BACKEND_RTT_ENABLED) && NRF_LOG_BACKEND_RTT_ENABLED
#include "nrf_log_backend_rtt.h"
NRF_LOG_BACKEND_RTT_DEF(rtt_log_backend);
#endif

#if defined(NRF_LOG_BACKEND_UART_ENABLED) && NRF_LOG_BACKEND_UART_ENABLED
#include "nrf_log_backend_uart.h"
NRF_LOG_BACKEND_UART_DEF(uart_log_backend);
#endif

void nrf_log_default_backends_init(void)
{
    int32_t backend_id = -1;
    (void)backend_id;
#if defined(NRF_LOG_BACKEND_RTT_ENABLED) && NRF_LOG_BACKEND_RTT_ENABLED
    nrf_log_backend_rtt_init();
    backend_id = nrf_log_backend_add(&rtt_log_backend, NRF_LOG_SEVERITY_DEBUG);
    ASSERT(backend_id >= 0);
    nrf_log_backend_enable(&rtt_log_backend);
#endif

#if defined(NRF_LOG_BACKEND_UART_ENABLED) && NRF_LOG_BACKEND_UART_ENABLED
    nrf_log_backend_uart_init();
    backend_id = nrf_log_backend_add(&uart_log_backend, NRF_LOG_SEVERITY_DEBUG);
    ASSERT(backend_id >= 0);
    nrf_log_backend_enable(&uart_log_backend);
#endif
}
#endif
