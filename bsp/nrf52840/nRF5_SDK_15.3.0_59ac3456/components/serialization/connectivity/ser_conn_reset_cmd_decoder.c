/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include "nrf_nvic.h"
#include "ser_conn_reset_cmd_decoder.h"
#include "app_scheduler.h"
#include "nrf_sdh.h"
#include "app_error.h"
#include "ble_serialization.h"
#include "nrf_log.h"
#include "ser_conn_handlers.h"
#include "ser_hal_transport.h"
#include "app_timer.h"
#ifdef SER_PHY_HCI
#include "ser_phy_hci.h"
#endif
APP_TIMER_DEF(reset_timer);

bool m_reset_ongoing;
static bool m_timer_created;

#ifdef SER_PHY_HCI
extern void ser_phy_hci_reset(void);
#endif
static void sd_start_from_app_sched(void * p_event_data, uint16_t event_size)
{

    NRF_LOG_DEBUG("sdh enable request.");
    (void)nrf_sdh_enable_request();
    m_reset_ongoing = false;
}

static void sdh_observer_handler(nrf_sdh_state_evt_t state, void * p_context)
{
    if (state == NRF_SDH_EVT_STATE_DISABLED)
    {
        APP_ERROR_CHECK(app_sched_event_put(NULL, 0, sd_start_from_app_sched));
        app_sched_resume();
    }
    else if (state == NRF_SDH_EVT_STATE_ENABLED)
    {
	   NRF_LOG_DEBUG("sdh enabled.");
    }
    else
    {
        /* empty */
    }
}

NRF_SDH_STATE_OBSERVER(sdh_observer, 0) =
{
    .handler = sdh_observer_handler
};

void timer_handler(void * p_ctx)
{
     NRF_LOG_DEBUG("transport reset");
    ser_hal_transport_reset();
#ifdef SER_PHY_HCI
    ser_phy_hci_reset();
    ser_phy_hci_slip_reset();
#endif
}

bool soft_reset_trigger(void)
{
    if (m_reset_ongoing)
    {
        return false;
    }

    m_reset_ongoing = true;

    NRF_LOG_INFO("reset ongoing");
    if (!m_timer_created)
    {
	    (void)app_timer_create(&reset_timer, APP_TIMER_MODE_SINGLE_SHOT, timer_handler);
    }

    (void)app_timer_start(reset_timer, APP_TIMER_TICKS(100), NULL);

    (void)nrf_sdh_disable_request();
#ifdef BLE_STACK_SUPPORT_REQD
    ser_conn_reset();
#endif
    return true;
}

void ser_conn_generic_command_process(uint8_t * p_command, uint16_t command_len)
{
    switch (p_command[0])
    {
    case SER_GENERIC_CMD_RESET:
        (void)sd_nvic_SystemReset();
        break;
    case SER_GENERIC_CMD_SOFT_RESET:
        (void)soft_reset_trigger();
        break;
    default:
        break;
    }
}
