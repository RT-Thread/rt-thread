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
#include "bsp_btn_ant.h"
#include <stdint.h>
#include "bsp.h"
#include "ant_stack_handler_types.h"
#include "ant_parameters.h"

#define BTN_ID_WAKEUP             3  /**< ID of button used to wake up the application. */
#define BTN_ID_SLEEP              3  /**< ID of button used to put the application into sleep mode. */

#define BTN_ACTION_SLEEP          BSP_BUTTON_ACTION_RELEASE    /**< Button action used to put the application into sleep mode. */


 /**@brief This macro will return from the current function if err_code
 *        is not NRF_SUCCESS or NRF_ERROR_INVALID_PARAM.
 */
#define RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code)                             \
do                                                                              \
{                                                                               \
    if (((err_code) != NRF_SUCCESS) && ((err_code) != NRF_ERROR_INVALID_PARAM)) \
    {                                                                           \
        return err_code;                                                        \
    }                                                                           \
}                                                                               \
while (0)


/**@brief This macro will return from the current function if err_code
 *        is not NRF_SUCCESS or NRF_ERROR_NOT_SUPPORTED.
 */
#define RETURN_ON_ERROR_NOT_NOT_SUPPORTED(err_code)                             \
do                                                                              \
{                                                                               \
    if (((err_code) != NRF_SUCCESS) && ((err_code) != NRF_ERROR_NOT_SUPPORTED)) \
    {                                                                           \
        return err_code;                                                        \
    }                                                                           \
}                                                                               \
while (0)


static bool m_connected = false;  /**< Notify if channel is connected. */


 /**@brief Function for configuring the buttons for connection.
 *
 * @retval NRF_SUCCESS  Configured successfully.
 * @return A propagated error code.
 */
static uint32_t connection_buttons_configure(void)
{
    uint32_t err_code;

    err_code = bsp_event_to_button_action_assign(BTN_ID_SLEEP,
                                                 BTN_ACTION_SLEEP,
                                                 BSP_EVENT_DEFAULT);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    return NRF_SUCCESS;
}


/**@brief Function for configuring the buttons for searching.
 *
 * @retval NRF_SUCCESS  Configured successfully.
 * @return A propagated error code.
 */
static uint32_t searching_buttons_configure(void)
{
    uint32_t err_code;

    err_code = bsp_event_to_button_action_assign(BTN_ID_SLEEP,
                                                 BTN_ACTION_SLEEP,
                                                 BSP_EVENT_SLEEP);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    return NRF_SUCCESS;
}


uint32_t bsp_btn_ant_sleep_mode_prepare(void)
{
    uint32_t err_code = bsp_wakeup_button_enable(BTN_ID_WAKEUP);
    RETURN_ON_ERROR_NOT_NOT_SUPPORTED(err_code);

    return NRF_SUCCESS;
}


void bsp_btn_ant_on_ant_evt(ant_evt_t * p_ant_evt)
{
    uint32_t err_code;

    switch (p_ant_evt->event)
    {
        case EVENT_RX:
            if (!m_connected)
            {
                err_code = connection_buttons_configure();
                APP_ERROR_CHECK(err_code);
            }

            m_connected = true;
            break;

        case EVENT_RX_FAIL_GO_TO_SEARCH:
            m_connected = false;

            err_code = searching_buttons_configure();
            APP_ERROR_CHECK(err_code);
            break;

        default:
            break;
    }
}


uint32_t bsp_btn_ant_init(void)
{
    uint32_t err_code = NRF_SUCCESS;

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
