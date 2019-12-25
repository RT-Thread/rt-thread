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
#if NRF_MODULE_ENABLED(ANT_STATE_INDICATOR)
#include "ant_state_indicator.h"
#include "bsp.h"
#include "app_error.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ant.h"
#include "nrf_pwr_mgmt.h"

static uint8_t m_channel = UINT8_MAX;               /**< ANT channel number linked to indication. */
static uint8_t m_channel_type;                      /**< Type of linked ANT channel. */

ret_code_t ant_state_indicator_init( uint8_t channel, uint8_t channel_type)
{
    m_channel       = channel;
    m_channel_type  = channel_type;

    return bsp_indication_set(BSP_INDICATE_IDLE);
}

ret_code_t ant_state_indicator_channel_opened(void)
{
    ret_code_t err_code = NRF_SUCCESS;

    switch (m_channel_type)
    {
        case CHANNEL_TYPE_SLAVE:
            /* fall through */
        case CHANNEL_TYPE_SLAVE_RX_ONLY:
            err_code = bsp_indication_set(BSP_INDICATE_SCANNING);
            break;

        case CHANNEL_TYPE_MASTER:
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            break;
    }

    return err_code;
}

/**
 * @brief Function for handling ANT events.
 *
 * @param[in]   p_ant_evt       Event received from the ANT stack.
 * @param[in]   p_context       Context.
 */
static void ant_evt_handler(ant_evt_t * p_ant_evt, void * p_context)
{
    ret_code_t err_code = NRF_SUCCESS;

    if (m_channel != p_ant_evt->channel)
    {
        return;
    }

    switch (m_channel_type)
    {
        case CHANNEL_TYPE_SLAVE:
            /* fall through */
        case CHANNEL_TYPE_SLAVE_RX_ONLY:
            switch (p_ant_evt->event)
            {
                case EVENT_RX:
                    err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
                    break;

                case EVENT_RX_FAIL:
                    err_code = bsp_indication_set(BSP_INDICATE_RCV_ERROR);
                    break;

                case EVENT_RX_FAIL_GO_TO_SEARCH:
                    err_code = bsp_indication_set(BSP_INDICATE_SCANNING);
                    break;

                case EVENT_CHANNEL_CLOSED:
                    nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_GOTO_SYSOFF);
                    break;

                case EVENT_RX_SEARCH_TIMEOUT:
                    err_code = bsp_indication_set(BSP_INDICATE_IDLE);
                    break;
            }
            break;
    }
    APP_ERROR_CHECK(err_code);
}

NRF_SDH_ANT_OBSERVER(m_ant_observer, ANT_STATE_INDICATOR_ANT_OBSERVER_PRIO, ant_evt_handler, NULL);

/**
 * @brief Function for shutdown events.
 *
 * @param[in]   event       Shutdown type.
 */
static bool m_shutdown_handler(nrf_pwr_mgmt_evt_t event)
{
    ret_code_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);

    return true;
}


NRF_PWR_MGMT_HANDLER_REGISTER(m_shutdown_handler, ANT_STATE_INDICATOR_CONFIG_SHUTDOWN_HANDLER_PRIORITY);

#endif // NRF_MODULE_ENABLED(ANT_STATE_INDICATOR)
