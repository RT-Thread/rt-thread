/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(SIMPLE_TIMER)
#include "app_simple_timer.h"
#include "nrf.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_timer.h"
#include "nrf_drv_timer.h"

/**@brief States of simple timer state machine.
 */
typedef enum
{
    SIMPLE_TIMER_STATE_IDLE = 0,
    SIMPLE_TIMER_STATE_INITIALIZED,
    SIMPLE_TIMER_STATE_STOPPED,
    SIMPLE_TIMER_STATE_STARTED
}simple_timer_states_t;

static app_simple_timer_mode_t            m_mode;                                               /**< Registered timer mode. */
static app_simple_timer_timeout_handler_t m_timeout_handler          = NULL;                    /**< Registered time-out handler. */
static void *                             mp_timeout_handler_context = NULL;                    /**< Registered time-out handler context. */
static simple_timer_states_t              m_simple_timer_state       = SIMPLE_TIMER_STATE_IDLE; /**< State machine state. */

const nrf_drv_timer_t SIMPLE_TIMER = NRF_DRV_TIMER_INSTANCE(SIMPLE_TIMER_CONFIG_INSTANCE);

/**
 * @brief Handler for timer events.
 */
static void app_simple_timer_event_handler(nrf_timer_event_t event_type, void * p_context)
{
    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            if (m_mode == APP_SIMPLE_TIMER_MODE_SINGLE_SHOT)
            {
                m_simple_timer_state = SIMPLE_TIMER_STATE_STOPPED;
            }

            //@note: No NULL check required as performed in timer_start(...).
            m_timeout_handler(mp_timeout_handler_context);
            break;

        default:
            //Do nothing.
            break;
    }
}

uint32_t app_simple_timer_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    nrf_drv_timer_config_t t_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    t_cfg.mode = NRF_TIMER_MODE_TIMER;
    t_cfg.bit_width = NRF_TIMER_BIT_WIDTH_16;
    t_cfg.frequency = (nrf_timer_frequency_t)SIMPLE_TIMER_CONFIG_FREQUENCY;
    err_code = nrf_drv_timer_init(&SIMPLE_TIMER, &t_cfg, app_simple_timer_event_handler);

    if (NRF_SUCCESS == err_code)
    {
        m_simple_timer_state = SIMPLE_TIMER_STATE_INITIALIZED;
    }

    return err_code;
}

uint32_t app_simple_timer_start(app_simple_timer_mode_t            mode,
                                app_simple_timer_timeout_handler_t timeout_handler,
                                uint16_t                           timeout_ticks,
                                void *                             p_context)
{
    uint32_t err_code = NRF_SUCCESS;
    nrf_timer_short_mask_t timer_short;

    VERIFY_PARAM_NOT_NULL(timeout_handler);

    if (APP_SIMPLE_TIMER_MODE_REPEATED == mode)
    {
        timer_short = NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK;
    }
    else if (APP_SIMPLE_TIMER_MODE_SINGLE_SHOT == mode)
    {
        timer_short = NRF_TIMER_SHORT_COMPARE0_STOP_MASK;
    }
    else
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (SIMPLE_TIMER_STATE_IDLE == m_simple_timer_state)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (SIMPLE_TIMER_STATE_STARTED == m_simple_timer_state)
    {
        err_code = app_simple_timer_stop();
        APP_ERROR_CHECK(err_code);
    }

    if (SIMPLE_TIMER_STATE_STOPPED == m_simple_timer_state)
    {
        nrf_drv_timer_clear(&SIMPLE_TIMER);
    }

    m_mode                      = mode;
    m_timeout_handler           = timeout_handler;
    mp_timeout_handler_context  = p_context;

    nrf_drv_timer_extended_compare(
            &SIMPLE_TIMER, NRF_TIMER_CC_CHANNEL0, (uint32_t)timeout_ticks, timer_short, true);

    if (m_simple_timer_state == SIMPLE_TIMER_STATE_STOPPED)
    {
        nrf_drv_timer_resume(&SIMPLE_TIMER);
    }
    else
    {
        nrf_drv_timer_enable(&SIMPLE_TIMER);
    }


    m_simple_timer_state = SIMPLE_TIMER_STATE_STARTED;

    return NRF_SUCCESS;
}

uint32_t app_simple_timer_stop(void)
{
    if (SIMPLE_TIMER_STATE_STARTED == m_simple_timer_state)
    {
        nrf_drv_timer_pause(&SIMPLE_TIMER);

        m_simple_timer_state = SIMPLE_TIMER_STATE_STOPPED;
    }

    return NRF_SUCCESS;
}

uint32_t app_simple_timer_uninit(void)
{
    uint32_t err_code = NRF_SUCCESS;

    if (SIMPLE_TIMER_STATE_IDLE != m_simple_timer_state)
    {
        nrf_drv_timer_uninit(&SIMPLE_TIMER);
        m_simple_timer_state = SIMPLE_TIMER_STATE_IDLE;
    }

    return err_code;
}
#endif //NRF_MODULE_ENABLED(SIMPLE_TIMER)
