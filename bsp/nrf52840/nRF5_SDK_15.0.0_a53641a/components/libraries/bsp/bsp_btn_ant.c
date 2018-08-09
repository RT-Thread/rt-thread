/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(BSP_BTN_ANT)
#include "bsp_btn_ant.h"
#include "nrf_sdh_ant.h"
#include "bsp.h"


static bool    m_connected  = false;                /**< Notify if channel is connected. */
static uint8_t m_channel    = UINT8_MAX;            /**< ANT channel number linked to indication. */
static uint8_t m_channel_type;                      /**< Type of linked ANT channel. */

/**@brief Function for configuring the buttons for connection.
 *
 * @retval NRF_SUCCESS  Configured successfully.
 * @return A propagated error code.
 */
static ret_code_t connection_buttons_configure(void)
{
    ret_code_t err_code = bsp_event_to_button_action_assign(BSP_BTN_ANT_CONFIG_SLEEP_BTN_ID,
                                                            BSP_BUTTON_ACTION_RELEASE,
                                                            BSP_EVENT_DEFAULT);
    if (err_code == NRF_ERROR_INVALID_PARAM)
    {
        return NRF_SUCCESS;
    }

    return err_code;
}

/**@brief Function for configuring the buttons for searching.
 *
 * @retval NRF_SUCCESS  Configured successfully.
 * @return A propagated error code.
 */
static ret_code_t searching_buttons_configure(void)
{
    ret_code_t err_code = bsp_event_to_button_action_assign(BSP_BTN_ANT_CONFIG_SLEEP_BTN_ID,
                                                            BSP_BUTTON_ACTION_RELEASE,
                                                            BSP_EVENT_SLEEP);
    if (err_code == NRF_ERROR_INVALID_PARAM)
    {
        return NRF_SUCCESS;
    }

    return err_code;
}


ret_code_t bsp_btn_ant_sleep_mode_prepare(void)
{
    ret_code_t err_code = bsp_buttons_disable();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = bsp_wakeup_button_enable(BSP_BTN_ANT_CONFIG_WAKEUP_BTN_ID);
    if (err_code == NRF_ERROR_NOT_SUPPORTED)
    {
        return NRF_SUCCESS;
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
                    if (!m_connected)
                    {
                        err_code = connection_buttons_configure();
                    }

                    m_connected = true;
                    break;

                case EVENT_RX_FAIL_GO_TO_SEARCH:
                    m_connected = false;

                    err_code = searching_buttons_configure();
                    break;

                default:
                    break;
            }
            break;
    }

    APP_ERROR_CHECK(err_code);
}

NRF_SDH_ANT_OBSERVER(m_ant_observer, BSP_BTN_ANT_OBSERVER_PRIO, ant_evt_handler, NULL);

ret_code_t bsp_btn_ant_init(uint8_t channel, uint8_t channel_type)
{
    ret_code_t err_code = NRF_SUCCESS;

    m_channel       = channel;
    m_channel_type  = channel_type;

    if (!m_connected)
    {
        err_code = searching_buttons_configure();
    }
    else
    {
        err_code = connection_buttons_configure();
    }

    return err_code;
}

#endif // NRF_MODULE_ENABLED(BSP_BTN_ANT)
