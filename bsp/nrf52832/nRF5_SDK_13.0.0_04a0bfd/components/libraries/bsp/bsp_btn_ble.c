/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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

#include "bsp_btn_ble.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "ble.h"
#include "bsp.h"


#define BTN_ID_WAKEUP             0  /**< ID of button used to wake up the application. */
#define BTN_ID_SLEEP              0  /**< ID of button used to put the application into sleep mode. */
#define BTN_ID_DISCONNECT         0  /**< ID of button used to gracefully terminate a connection on long press. */
#define BTN_ID_WAKEUP_BOND_DELETE 1  /**< ID of button used to wake up the application and delete all bonding information. */
#define BTN_ID_WHITELIST_OFF      1  /**< ID of button used to turn off usage of the whitelist. */

#define BTN_ACTION_SLEEP          BSP_BUTTON_ACTION_RELEASE    /**< Button action used to put the application into sleep mode. */
#define BTN_ACTION_DISCONNECT     BSP_BUTTON_ACTION_LONG_PUSH  /**< Button action used to gracefully terminate a connection on long press. */
#define BTN_ACTION_WHITELIST_OFF  BSP_BUTTON_ACTION_LONG_PUSH  /**< Button action used to turn off usage of the whitelist. */



/**@brief This macro will return from the current function if err_code
 *        is not NRF_SUCCESS.
 */
#define RETURN_ON_ERROR(err_code)  \
do                                 \
{                                  \
    if ((err_code) != NRF_SUCCESS) \
    {                              \
        return err_code;           \
    }                              \
}                                  \
while (0)


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


/**@brief This macro will call the registered error handler if err_code
 *        is not NRF_SUCCESS and the error handler is not NULL.
 */
#define CALL_HANDLER_ON_ERROR(err_code)                           \
do                                                                \
{                                                                 \
    if (((err_code) != NRF_SUCCESS) && (m_error_handler != NULL)) \
    {                                                             \
        m_error_handler(err_code);                                \
    }                                                             \
}                                                                 \
while (0)


static bsp_btn_ble_error_handler_t m_error_handler = NULL; /**< Error handler registered by the user. */
static uint32_t                    m_num_connections = 0;  /**< Number of connections the device is currently in. */


/**@brief Function for configuring the buttons for connection.
 *
 * @retval NRF_SUCCESS  Configured successfully.
 * @return A propagated error code.
 */
static uint32_t connection_buttons_configure()
{
    uint32_t err_code;

    err_code = bsp_event_to_button_action_assign(BTN_ID_SLEEP,
                                                 BTN_ACTION_SLEEP,
                                                 BSP_EVENT_DEFAULT);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    err_code = bsp_event_to_button_action_assign(BTN_ID_WHITELIST_OFF,
                                                 BTN_ACTION_WHITELIST_OFF,
                                                 BSP_EVENT_WHITELIST_OFF);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    err_code = bsp_event_to_button_action_assign(BTN_ID_DISCONNECT,
                                                 BTN_ACTION_DISCONNECT,
                                                 BSP_EVENT_DISCONNECT);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    return NRF_SUCCESS;
}


/**@brief Function for configuring the buttons for advertisement.
 *
 * @retval NRF_SUCCESS  Configured successfully.
 * @return A propagated error code.
 */
static uint32_t advertising_buttons_configure()
{
    uint32_t err_code;

    err_code = bsp_event_to_button_action_assign(BTN_ID_DISCONNECT,
                                                 BTN_ACTION_DISCONNECT,
                                                 BSP_EVENT_DEFAULT);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    err_code = bsp_event_to_button_action_assign(BTN_ID_WHITELIST_OFF,
                                                 BTN_ACTION_WHITELIST_OFF,
                                                 BSP_EVENT_WHITELIST_OFF);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    err_code = bsp_event_to_button_action_assign(BTN_ID_SLEEP,
                                                 BTN_ACTION_SLEEP,
                                                 BSP_EVENT_SLEEP);
    RETURN_ON_ERROR_NOT_INVALID_PARAM(err_code);

    return NRF_SUCCESS;
}


/**@brief Function for extracting the BSP event valid at startup.
 *
 * @details When a button was used to wake up the device, the button press will not generate an
 *          interrupt. This function reads which button was pressed at startup, and returns the
 *          appropriate BSP event.
 *
 * @param[out] p_startup_event  Where to put the extracted BSP event.
 */
static void startup_event_extract(bsp_event_t * p_startup_event)
{
    // React to button states
    if (bsp_button_is_pressed(BTN_ID_WAKEUP_BOND_DELETE))
    {
        *p_startup_event = BSP_EVENT_CLEAR_BONDING_DATA;
    }
    else if (bsp_button_is_pressed(BTN_ID_WAKEUP))
    {
        *p_startup_event = BSP_EVENT_WAKEUP;
    }
    else
    {
        *p_startup_event = BSP_EVENT_NOTHING;
    }
}


uint32_t bsp_btn_ble_sleep_mode_prepare(void)
{
    uint32_t err_code = bsp_wakeup_button_enable(BTN_ID_WAKEUP);
    RETURN_ON_ERROR_NOT_NOT_SUPPORTED(err_code);

    err_code = bsp_wakeup_button_enable(BTN_ID_WAKEUP_BOND_DELETE);
    RETURN_ON_ERROR_NOT_NOT_SUPPORTED(err_code);

    return NRF_SUCCESS;
}


void bsp_btn_ble_on_ble_evt(ble_evt_t * p_ble_evt)
{
    uint32_t err_code;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            if (m_num_connections == 0)
            {
                err_code = connection_buttons_configure();
                CALL_HANDLER_ON_ERROR(err_code);
            }

            m_num_connections++;
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            m_num_connections--;

            if (m_num_connections == 0)
            {
                err_code = advertising_buttons_configure();
                CALL_HANDLER_ON_ERROR(err_code);
            }
            break;

        default:
            break;
    }
}


uint32_t bsp_btn_ble_init(bsp_btn_ble_error_handler_t error_handler, bsp_event_t * p_startup_bsp_evt)
{
    uint32_t err_code = NRF_SUCCESS;

    m_error_handler = error_handler;

    if (p_startup_bsp_evt != NULL)
    {
        startup_event_extract(p_startup_bsp_evt);
    }

    if (m_num_connections == 0)
    {
        err_code = advertising_buttons_configure();
    }

    return err_code;
}
