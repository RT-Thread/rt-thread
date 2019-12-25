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
#if NRF_MODULE_ENABLED(NRF_LOG) && NRF_MODULE_ENABLED(NRF_LOG_BACKEND_RTT)
#include "nrf_log_backend_rtt.h"
#include "nrf_log_backend_serial.h"
#include "nrf_log_str_formatter.h"
#include "nrf_log_internal.h"
#include "nrf_delay.h"
#include <SEGGER_RTT_Conf.h>
#include <SEGGER_RTT.h>

static bool m_host_present;

static uint8_t m_string_buff[NRF_LOG_BACKEND_RTT_TEMP_BUFFER_SIZE];

void nrf_log_backend_rtt_init(void)
{
    SEGGER_RTT_Init();
}

static void serial_tx(void const * p_context, char const * buffer, size_t len)
{
    if (len)
    {
        uint32_t idx    = 0;
        uint32_t processed;
        uint32_t watchdog_counter = NRF_LOG_BACKEND_RTT_TX_RETRY_CNT;
        do
        {
            processed = SEGGER_RTT_WriteNoLock(0, &buffer[idx], len);
            idx += processed;
            len -= processed;
            if (processed == 0)
            {
                /* There are two possible reasons for not writing any data to RTT:
                 * - The host is not connected and not reading the data.
                 * - The buffer got full and will be read by the host.
                 * These two situations are distinguished using the following algorithm.
                 * At the begining, the module assumes that the host is active,
                 * so when no data is read, it busy waits and retries.
                 * If, after retrying, the host reads the data, the module assumes that the host is active.
                 * If it fails, the module assumes that the host is inactive and stores that information. On next
                 * call, only one attempt takes place. The host is marked as active if the attempt is successful.
                 */
                if (!m_host_present)
                {
                    break;
                }
                else
                {
                    nrf_delay_ms(NRF_LOG_BACKEND_RTT_TX_RETRY_DELAY_MS);
                    watchdog_counter--;
                    if (watchdog_counter == 0)
                    {
                        m_host_present = false;
                        break;
                    }
                }
            }
            m_host_present = true;
        } while (len);
    }
}
static void nrf_log_backend_rtt_put(nrf_log_backend_t const * p_backend,
                               nrf_log_entry_t * p_msg)
{
    nrf_log_backend_serial_put(p_backend, p_msg, m_string_buff, NRF_LOG_BACKEND_RTT_TEMP_BUFFER_SIZE, serial_tx);
}

static void nrf_log_backend_rtt_flush(nrf_log_backend_t const * p_backend)
{

}

static void nrf_log_backend_rtt_panic_set(nrf_log_backend_t const * p_backend)
{

}

const nrf_log_backend_api_t nrf_log_backend_rtt_api = {
        .put       = nrf_log_backend_rtt_put,
        .flush     = nrf_log_backend_rtt_flush,
        .panic_set = nrf_log_backend_rtt_panic_set,
};
#endif //NRF_MODULE_ENABLED(NRF_LOG) && NRF_MODULE_ENABLED(NRF_LOG_BACKEND_RTT)
