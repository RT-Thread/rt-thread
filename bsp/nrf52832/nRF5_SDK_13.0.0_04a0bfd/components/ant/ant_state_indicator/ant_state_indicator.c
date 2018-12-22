/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#include "ant_parameters.h"
#include "bsp.h"
#include "ant_state_indicator.h"
#include "app_error.h"
#include "bsp_btn_ant.h"
#include "nrf_soc.h"

/**
 * @addtogroup ant_sdk_state_indicator ANT channel state indicator module.
 * @{
 */

static uint8_t m_related_channel;  ///< ANT channel number linked to indication
static uint8_t m_channel_type;     ///< type of linked ANT channel


void ant_state_indicator_init( uint8_t channel, uint8_t channel_type)
{
    m_related_channel   = channel;
    m_channel_type      = channel_type;

    uint32_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);
}


uint32_t ant_state_indicator_channel_opened(void)
{
    uint32_t err_code = NRF_SUCCESS;

    switch (m_channel_type)
    {
        case CHANNEL_TYPE_SLAVE:
            err_code = bsp_indication_set(BSP_INDICATE_SCANNING);
            break;

        case CHANNEL_TYPE_SLAVE_RX_ONLY:
            err_code = bsp_indication_set(BSP_INDICATE_SCANNING);
            break;

        case CHANNEL_TYPE_MASTER:
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            break;
    }

    return err_code;
}


void ant_state_indicator_evt_handler(ant_evt_t * p_ant_evt)
{
    uint32_t err_code = NRF_SUCCESS;

    if (m_related_channel != p_ant_evt->channel)
        return;

    switch (m_channel_type)
    {
        case CHANNEL_TYPE_SLAVE:
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
                    err_code = bsp_indication_set(BSP_INDICATE_IDLE);
                    ant_state_indicator_sleep_mode_enter();
                    break;

                case EVENT_RX_SEARCH_TIMEOUT:
                    err_code = bsp_indication_set(BSP_INDICATE_IDLE);
                    break;
            }
            break;

        case CHANNEL_TYPE_MASTER:
            switch (p_ant_evt->event)
            {
                case EVENT_TX:
                    break;
            }
            break;
    }
    APP_ERROR_CHECK(err_code);
}


void ant_state_indicator_sleep_mode_enter(void)
{
    uint32_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);

    // Prepare wakeup buttons.
    err_code = bsp_btn_ant_sleep_mode_prepare();
    APP_ERROR_CHECK(err_code);

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    for (;;)
    {
        // Infinite loop after sd_power_system_off for emulated System OFF.
    }
}

/**
 *@}
 */

#endif // NRF_MODULE_ENABLED(ANT_STATE_INDICATOR)
