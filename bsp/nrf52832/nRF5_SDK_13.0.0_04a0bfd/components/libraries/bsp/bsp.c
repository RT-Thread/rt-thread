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
#include "bsp.h"
#include <stddef.h>
#include <stdio.h>
#include "nordic_common.h"
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_error.h"
#include "bsp_config.h"
#include "boards.h"

#ifndef BSP_SIMPLE
#include "app_timer.h"
#include "app_button.h"
#endif // BSP_SIMPLE

#if LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)
static bsp_indication_t m_stable_state        = BSP_INDICATE_IDLE;
static bool             m_leds_clear          = false;
static uint32_t         m_indication_type     = 0;
static bool             m_alert_on            = false;
APP_TIMER_DEF(m_leds_timer_id);
APP_TIMER_DEF(m_alert_timer_id);
#endif // LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)

#if BUTTONS_NUMBER > 0
#ifndef BSP_SIMPLE
static bsp_event_callback_t   m_registered_callback         = NULL;
static bsp_button_event_cfg_t m_events_list[BUTTONS_NUMBER] = {{BSP_EVENT_NOTHING, BSP_EVENT_NOTHING}};
APP_TIMER_DEF(m_button_timer_id);
static void bsp_button_event_handler(uint8_t pin_no, uint8_t button_action);
#endif // BSP_SIMPLE

#ifndef BSP_SIMPLE
static const app_button_cfg_t app_buttons[BUTTONS_NUMBER] =
{
    #ifdef BSP_BUTTON_0
    {BSP_BUTTON_0, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_0

    #ifdef BSP_BUTTON_1
    {BSP_BUTTON_1, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_1

    #ifdef BSP_BUTTON_2
    {BSP_BUTTON_2, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_2

    #ifdef BSP_BUTTON_3
    {BSP_BUTTON_3, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_3

    #ifdef BSP_BUTTON_4
    {BSP_BUTTON_4, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_4

    #ifdef BSP_BUTTON_5
    {BSP_BUTTON_5, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_5

    #ifdef BSP_BUTTON_6
    {BSP_BUTTON_6, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_6

    #ifdef BSP_BUTTON_7
    {BSP_BUTTON_7, false, BUTTON_PULL, bsp_button_event_handler},
    #endif // BUTTON_7

};
#endif // BSP_SIMPLE
#endif // BUTTONS_NUMBER > 0

#if (BUTTONS_NUMBER > 0)
bool bsp_button_is_pressed(uint32_t button)
{
    return bsp_board_button_state_get(button);
}
#endif

#if (BUTTONS_NUMBER > 0) && !(defined BSP_SIMPLE)
/**@brief Function for handling button events.
 *
 * @param[in]   pin_no          The pin number of the button pressed.
 * @param[in]   button_action   Action button.
 */
static void bsp_button_event_handler(uint8_t pin_no, uint8_t button_action)
{
    bsp_event_t        event  = BSP_EVENT_NOTHING;
    uint32_t           button = 0;
    uint32_t           err_code;
    static uint8_t     current_long_push_pin_no;              /**< Pin number of a currently pushed button, that could become a long push if held long enough. */
    static bsp_event_t release_event_at_push[BUTTONS_NUMBER]; /**< Array of what the release event of each button was last time it was pushed, so that no release event is sent if the event was bound after the push of the button. */

    button = bsp_board_pin_to_button_idx(pin_no);

    if (button < BUTTONS_NUMBER)
    {
        switch (button_action)
        {
            case APP_BUTTON_PUSH:
                event = m_events_list[button].push_event;
                if (m_events_list[button].long_push_event != BSP_EVENT_NOTHING)
                {
                    err_code = app_timer_start(m_button_timer_id, APP_TIMER_TICKS(BSP_LONG_PUSH_TIMEOUT_MS), (void*)&current_long_push_pin_no);
                    if (err_code == NRF_SUCCESS)
                    {
                        current_long_push_pin_no = pin_no;
                    }
                }
                release_event_at_push[button] = m_events_list[button].release_event;
                break;
            case APP_BUTTON_RELEASE:
                (void)app_timer_stop(m_button_timer_id);
                if (release_event_at_push[button] == m_events_list[button].release_event)
                {
                    event = m_events_list[button].release_event;
                }
                break;
            case BSP_BUTTON_ACTION_LONG_PUSH:
                event = m_events_list[button].long_push_event;
        }
    }

    if ((event != BSP_EVENT_NOTHING) && (m_registered_callback != NULL))
    {
        m_registered_callback(event);
    }
}

/**@brief Handle events from button timer.
 *
 * @param[in]   p_context   parameter registered in timer start function.
 */
static void button_timer_handler(void * p_context)
{
    bsp_button_event_handler(*(uint8_t *)p_context, BSP_BUTTON_ACTION_LONG_PUSH);
}


#endif // (BUTTONS_NUMBER > 0) && !(defined BSP_SIMPLE)


#if LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)
static void leds_off(void)
{
    if (m_alert_on)
    {
        uint32_t i;
        for(i = 0; i < LEDS_NUMBER; i++)
        {
            if (i != BSP_LED_ALERT)
            {
                bsp_board_led_off(i);
            }
        }
    }
    else
    {
        bsp_board_leds_off();
    }
}


/**@brief       Configure leds to indicate required state.
 * @param[in]   indicate   State to be indicated.
 */
static uint32_t bsp_led_indication(bsp_indication_t indicate)
{
    uint32_t err_code   = NRF_SUCCESS;
    uint32_t next_delay = 0;

    if(m_leds_clear)
    {
        m_leds_clear = false;
        leds_off();
    }

    switch (indicate)
    {
        case BSP_INDICATE_IDLE:
            leds_off();
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_SCANNING:
        case BSP_INDICATE_ADVERTISING:
            // in advertising blink LED_0
            if (bsp_board_led_state_get(BSP_LED_INDICATE_INDICATE_ADVERTISING))
            {
                bsp_board_led_off(BSP_LED_INDICATE_INDICATE_ADVERTISING);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING ? ADVERTISING_LED_OFF_INTERVAL :
                             ADVERTISING_SLOW_LED_OFF_INTERVAL;
            }
            else
            {
                bsp_board_led_on(BSP_LED_INDICATE_INDICATE_ADVERTISING);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING ? ADVERTISING_LED_ON_INTERVAL :
                             ADVERTISING_SLOW_LED_ON_INTERVAL;
            }

            m_stable_state = indicate;
            err_code       = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay), NULL);
            break;

        case BSP_INDICATE_ADVERTISING_WHITELIST:
            // in advertising quickly blink LED_0
            if (bsp_board_led_state_get(BSP_LED_INDICATE_ADVERTISING_WHITELIST))
            {
                bsp_board_led_off(BSP_LED_INDICATE_ADVERTISING_WHITELIST);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING_WHITELIST ?
                             ADVERTISING_WHITELIST_LED_OFF_INTERVAL :
                             ADVERTISING_SLOW_LED_OFF_INTERVAL;
            }
            else
            {
                bsp_board_led_on(BSP_LED_INDICATE_ADVERTISING_WHITELIST);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING_WHITELIST ?
                             ADVERTISING_WHITELIST_LED_ON_INTERVAL :
                             ADVERTISING_SLOW_LED_ON_INTERVAL;
            }
            m_stable_state = indicate;
            err_code       = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay), NULL);
            break;

        case BSP_INDICATE_ADVERTISING_SLOW:
            // in advertising slowly blink LED_0
            if (bsp_board_led_state_get(BSP_LED_INDICATE_ADVERTISING_SLOW))
            {
                bsp_board_led_off(BSP_LED_INDICATE_ADVERTISING_SLOW);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING_SLOW ? ADVERTISING_SLOW_LED_OFF_INTERVAL :
                             ADVERTISING_SLOW_LED_OFF_INTERVAL;
            }
            else
            {
                bsp_board_led_on(BSP_LED_INDICATE_ADVERTISING_SLOW);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING_SLOW ? ADVERTISING_SLOW_LED_ON_INTERVAL :
                             ADVERTISING_SLOW_LED_ON_INTERVAL;
            }
            m_stable_state = indicate;
            err_code       = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay), NULL);
            break;

        case BSP_INDICATE_ADVERTISING_DIRECTED:
            // in advertising very quickly blink LED_0
            if (bsp_board_led_state_get(BSP_LED_INDICATE_ADVERTISING_DIRECTED))
            {
                bsp_board_led_off(BSP_LED_INDICATE_ADVERTISING_DIRECTED);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING_DIRECTED ?
                             ADVERTISING_DIRECTED_LED_OFF_INTERVAL :
                             ADVERTISING_SLOW_LED_OFF_INTERVAL;
            }
            else
            {
                bsp_board_led_on(BSP_LED_INDICATE_ADVERTISING_DIRECTED);
                next_delay = indicate ==
                             BSP_INDICATE_ADVERTISING_DIRECTED ?
                             ADVERTISING_DIRECTED_LED_ON_INTERVAL :
                             ADVERTISING_SLOW_LED_ON_INTERVAL;
            }
            m_stable_state = indicate;
            err_code       = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay), NULL);
            break;

        case BSP_INDICATE_BONDING:
            // in bonding fast blink LED_0
            bsp_board_led_invert(BSP_LED_INDICATE_BONDING);

            m_stable_state = indicate;
            err_code       =
                app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(BONDING_INTERVAL), NULL);
            break;

        case BSP_INDICATE_CONNECTED:
            bsp_board_led_on(BSP_LED_INDICATE_CONNECTED);
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_SENT_OK:
            // when sending shortly invert LED_1
            m_leds_clear = true;
            bsp_board_led_invert(BSP_LED_INDICATE_SENT_OK);
            err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(SENT_OK_INTERVAL), NULL);
            break;

        case BSP_INDICATE_SEND_ERROR:
            // on receving error invert LED_1 for long time
            m_leds_clear = true;
            bsp_board_led_invert(BSP_LED_INDICATE_SEND_ERROR);
            err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(SEND_ERROR_INTERVAL), NULL);
            break;

        case BSP_INDICATE_RCV_OK:
            // when receving shortly invert LED_1
            m_leds_clear = true;
            bsp_board_led_invert(BSP_LED_INDICATE_RCV_OK);
            err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(RCV_OK_INTERVAL), NULL);
            break;

        case BSP_INDICATE_RCV_ERROR:
            // on receving error invert LED_1 for long time
            m_leds_clear = true;
            bsp_board_led_invert(BSP_LED_INDICATE_RCV_ERROR);
            err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(RCV_ERROR_INTERVAL), NULL);
            break;

        case BSP_INDICATE_FATAL_ERROR:
            // on fatal error turn on all leds
            bsp_board_leds_on();
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_ALERT_0:
        case BSP_INDICATE_ALERT_1:
        case BSP_INDICATE_ALERT_2:
        case BSP_INDICATE_ALERT_3:
        case BSP_INDICATE_ALERT_OFF:
            err_code   = app_timer_stop(m_alert_timer_id);
            next_delay = (uint32_t)BSP_INDICATE_ALERT_OFF - (uint32_t)indicate;

            // a little trick to find out that if it did not fall through ALERT_OFF
            if (next_delay && (err_code == NRF_SUCCESS))
            {
                if (next_delay > 1)
                {
                    err_code = app_timer_start(m_alert_timer_id,
                                               APP_TIMER_TICKS(((uint16_t)next_delay * ALERT_INTERVAL)),
                                               NULL);
                }
                bsp_board_led_on(BSP_LED_ALERT);
                m_alert_on = true;
            }
            else
            {
                bsp_board_led_off(BSP_LED_ALERT);
                m_alert_on = false;

            }
            break;

        case BSP_INDICATE_USER_STATE_OFF:
            leds_off();
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_USER_STATE_0:
            leds_off();
            bsp_board_led_on(BSP_LED_INDICATE_USER_LED1);
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_USER_STATE_1:
            leds_off();
            bsp_board_led_on(BSP_LED_INDICATE_USER_LED2);
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_USER_STATE_2:
            leds_off();
            bsp_board_led_on(BSP_LED_INDICATE_USER_LED1);
            bsp_board_led_on(BSP_LED_INDICATE_USER_LED2);
            m_stable_state = indicate;
            break;

        case BSP_INDICATE_USER_STATE_3:

        case BSP_INDICATE_USER_STATE_ON:
            bsp_board_leds_on();
            m_stable_state = indicate;
            break;

        default:
            break;
    }

    return err_code;
}


/**@brief Handle events from leds timer.
 *
 * @note Timer handler does not support returning an error code.
 * Errors from bsp_led_indication() are not propagated.
 *
 * @param[in]   p_context   parameter registered in timer start function.
 */
static void leds_timer_handler(void * p_context)
{
    UNUSED_PARAMETER(p_context);

    if (m_indication_type & BSP_INIT_LED)
    {
        UNUSED_VARIABLE(bsp_led_indication(m_stable_state));
    }
}


/**@brief Handle events from alert timer.
 *
 * @param[in]   p_context   parameter registered in timer start function.
 */
static void alert_timer_handler(void * p_context)
{
    UNUSED_PARAMETER(p_context);
    bsp_board_led_invert(BSP_LED_ALERT);
}
#endif // #if LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)


/**@brief Configure indicators to required state.
 */
uint32_t bsp_indication_set(bsp_indication_t indicate)
{
    uint32_t err_code = NRF_SUCCESS;

#if LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)

    if (m_indication_type & BSP_INIT_LED)
    {
        err_code = bsp_led_indication(indicate);
    }

#endif // LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)
    return err_code;
}


uint32_t bsp_init(uint32_t type, bsp_event_callback_t callback)
{
    uint32_t err_code = NRF_SUCCESS;

#if LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)
    m_indication_type     = type;
#endif // LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)

#if (BUTTONS_NUMBER > 0) && !(defined BSP_SIMPLE)
    m_registered_callback = callback;

    // BSP will support buttons and generate events
    if (type & BSP_INIT_BUTTONS)
    {
        uint32_t num;

        for (num = 0; ((num < BUTTONS_NUMBER) && (err_code == NRF_SUCCESS)); num++)
        {
            err_code = bsp_event_to_button_action_assign(num, BSP_BUTTON_ACTION_PUSH, BSP_EVENT_DEFAULT);
        }

        if (err_code == NRF_SUCCESS)
        {
            err_code = app_button_init((app_button_cfg_t *)app_buttons,
                                       BUTTONS_NUMBER,
                                       APP_TIMER_TICKS(50));
        }

        if (err_code == NRF_SUCCESS)
        {
            err_code = app_button_enable();
        }

        if (err_code == NRF_SUCCESS)
        {
            err_code = app_timer_create(&m_button_timer_id,
                                        APP_TIMER_MODE_SINGLE_SHOT,
                                        button_timer_handler);
        }
    }
#elif (BUTTONS_NUMBER > 0) && (defined BSP_SIMPLE)

    if (type & BSP_INIT_BUTTONS)
    {
        bsp_board_buttons_init();
    }
#endif // (BUTTONS_NUMBER > 0) && !(defined BSP_SIMPLE)

#if LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)

    if (type & BSP_INIT_LED)
    {
        bsp_board_leds_init();
    }

    // timers module must be already initialized!
    if (err_code == NRF_SUCCESS)
    {
        err_code =
            app_timer_create(&m_leds_timer_id, APP_TIMER_MODE_SINGLE_SHOT, leds_timer_handler);
    }

    if (err_code == NRF_SUCCESS)
    {
        err_code =
            app_timer_create(&m_alert_timer_id, APP_TIMER_MODE_REPEATED, alert_timer_handler);
    }
#endif // LEDS_NUMBER > 0 && !(defined BSP_SIMPLE)

    return err_code;
}


#ifndef BSP_SIMPLE
/**@brief Assign specific event to button.
 */
uint32_t bsp_event_to_button_action_assign(uint32_t button, bsp_button_action_t action, bsp_event_t event)
{
    uint32_t err_code = NRF_SUCCESS;

#if BUTTONS_NUMBER > 0
    if (button < BUTTONS_NUMBER)
    {
        if (event == BSP_EVENT_DEFAULT)
        {
            // Setting default action: BSP_EVENT_KEY_x for PUSH actions, BSP_EVENT_NOTHING for RELEASE and LONG_PUSH actions.
            event = (action == BSP_BUTTON_ACTION_PUSH) ? (bsp_event_t)(BSP_EVENT_KEY_0 + button) : BSP_EVENT_NOTHING;
        }
        switch (action)
        {
            case BSP_BUTTON_ACTION_PUSH:
                m_events_list[button].push_event = event;
                break;
            case BSP_BUTTON_ACTION_LONG_PUSH:
                m_events_list[button].long_push_event = event;
                break;
            case BSP_BUTTON_ACTION_RELEASE:
                m_events_list[button].release_event = event;
                break;
            default:
                err_code = NRF_ERROR_INVALID_PARAM;
                break;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_PARAM;
    }
#else
    err_code = NRF_ERROR_INVALID_PARAM;
#endif // BUTTONS_NUMBER > 0

    return err_code;
}

#endif // BSP_SIMPLE


uint32_t bsp_buttons_enable()
{
#if (BUTTONS_NUMBER > 0) && !defined(BSP_SIMPLE)
    return app_button_enable();
#else
    return NRF_ERROR_NOT_SUPPORTED;
#endif
}

uint32_t bsp_buttons_disable()
{
#if (BUTTONS_NUMBER > 0) && !defined(BSP_SIMPLE)
    return app_button_disable();
#else
    return NRF_ERROR_NOT_SUPPORTED;
#endif
}

uint32_t bsp_wakeup_button_enable(uint32_t button_idx)
{
#if (BUTTONS_NUMBER > 0) && !defined(BSP_SIMPLE)
    nrf_gpio_cfg_sense_set(bsp_board_button_idx_to_pin(button_idx),
            BUTTONS_ACTIVE_STATE ? NRF_GPIO_PIN_SENSE_HIGH :NRF_GPIO_PIN_SENSE_LOW);
    return NRF_SUCCESS;
#else
    UNUSED_PARAMETER(button_idx);
    return NRF_ERROR_NOT_SUPPORTED;
#endif
}

uint32_t bsp_wakeup_button_disable(uint32_t button_idx)
{
#if (BUTTONS_NUMBER > 0) && !defined(BSP_SIMPLE)
    nrf_gpio_cfg_sense_set(bsp_board_button_idx_to_pin(button_idx),
                           NRF_GPIO_PIN_NOSENSE);
    return NRF_SUCCESS;
#else
    UNUSED_PARAMETER(button_idx);
    return NRF_ERROR_NOT_SUPPORTED;
#endif
}
