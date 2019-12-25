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
#include "nrf_bootloader_wdt.h"
#include "nrf_wdt.h"
#include "nrf_bootloader_dfu_timers.h"
#include "nrf_log_ctrl.h"

#define NRF_LOG_MODULE_NAME nrf_bootloader_wdt
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


static void wdt_feed(void)
{
    if (nrf_wdt_started())
    {
        for (nrf_wdt_rr_register_t i = NRF_WDT_RR0; i < NRF_WDT_RR7; i++)
        {
            if (nrf_wdt_reload_request_is_enabled(i))
            {
                nrf_wdt_reload_request_set(i);
            }
        }
    }
}


static void wdt_feed_timer_handler(void)
{
    NRF_LOG_INFO("Internal feed");
    wdt_feed();
}


void WDT_IRQHandler(void)
{
    nrf_wdt_event_clear(NRF_WDT_EVENT_TIMEOUT);
    NRF_LOG_FINAL_FLUSH();
}

#define MAX_FLASH_OP_TIME_TICKS 3200 // ~100 ms

void nrf_bootloader_wdt_init(void)
{
    static bool initialized = false;

    if (initialized)
    {
        return;
    }

    if (nrf_wdt_started())
    {
        uint32_t wdt_ticks = nrf_wdt_reload_value_get();

        NRF_LOG_INFO("WDT enabled CRV:%d ticks", wdt_ticks);

        //wdt_ticks must be reduced to feed the watchdog before the timeout.
        uint32_t reduced_timeout_ticks = MAX((int32_t)wdt_ticks - MAX_FLASH_OP_TIME_TICKS,
                                             NRF_BOOTLOADER_MIN_TIMEOUT_TICKS);

        /* initial watchdog feed */
        wdt_feed();

        NRF_LOG_INFO("Starting a timer (%d ticks) for feeding watchdog.", reduced_timeout_ticks);
        nrf_bootloader_wdt_feed_timer_start(reduced_timeout_ticks, wdt_feed_timer_handler);

        NVIC_EnableIRQ(WDT_IRQn);
    }
    else
    {
        NRF_LOG_INFO("WDT is not enabled");
    }

    initialized = true;
}

void nrf_bootloader_wdt_feed(void)
{
    if (nrf_wdt_started())
    {
        wdt_feed();
    }
}
