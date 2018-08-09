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
#include "nrf_bootloader_dfu_timers.h"

#include "app_timer.h"
#include "nrf_clock.h"

APP_TIMER_DEF(m_dfu_inactivity_timer); //!< Timer for aborting DFU if no update happens.
APP_TIMER_DEF(m_wdt_feed_timer);       //!< Timer for feeding the application's watchdog (WDT) while the bootloader is running.

static bool m_app_timer_initialized;

/** @brief Function for handling the timeouts by calling the callback in the context.
 */
static void timeout_handler(void * p_context)
{
    if (p_context)
    {
        //lint -save -e611 "Suspicious cast"
        ((nrf_bootloader_dfu_timeout_callback_t)p_context)();
        //lint -restore
    }
}


/**@brief Initialization of app_timer. Function ensures that initialization happens only once.
 */
static void timer_init(void)
{
    if (!m_app_timer_initialized)
    {
        if (!nrf_clock_lf_is_running())
        {
            nrf_clock_task_trigger(NRF_CLOCK_TASK_LFCLKSTART);

            // Wait for the clock to be ready.
            while (!nrf_clock_lf_is_running()) {;}
        }

        uint32_t err_code = app_timer_init();
        APP_ERROR_CHECK(err_code);

        // Start a single shot timer that will reset the DFU on timeout.
        err_code = app_timer_create(&m_dfu_inactivity_timer,
                                    APP_TIMER_MODE_SINGLE_SHOT,
                                    timeout_handler);
        ASSERT(err_code == NRF_SUCCESS);

        err_code = app_timer_create(&m_wdt_feed_timer,
                                    APP_TIMER_MODE_REPEATED,
                                    timeout_handler);
        ASSERT(err_code == NRF_SUCCESS);

        m_app_timer_initialized = true;
    }
}


/**@brief Function for initializing app_timer if necessary, and (re)starting a timer.
 */
static void timer_start(app_timer_t * p_timer, uint32_t timeout_ms, nrf_bootloader_dfu_timeout_callback_t callback)
{
    ret_code_t err_code;

    timer_init();

    err_code = app_timer_stop(p_timer);
    ASSERT(err_code == NRF_SUCCESS);

    if (timeout_ms != 0)
    {
        //lint -save -e611 "Suspicious cast"
        err_code = app_timer_start(p_timer, APP_TIMER_TICKS(timeout_ms), (void *)callback);
        //lint -restore
        ASSERT(err_code == NRF_SUCCESS);
    }
}


void nrf_bootloader_dfu_inactivity_timer_restart(uint32_t timeout_ms, nrf_bootloader_dfu_timeout_callback_t callback)
{
    timer_start(m_dfu_inactivity_timer, timeout_ms, callback);
}


void nrf_bootloader_wdt_feed_timer_start(uint32_t timeout_ms, nrf_bootloader_dfu_timeout_callback_t callback)
{
    timer_start(m_wdt_feed_timer, timeout_ms, callback);
}
