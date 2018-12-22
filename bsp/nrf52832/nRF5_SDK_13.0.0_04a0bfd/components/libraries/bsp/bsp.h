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
/**@file
 *
 * @defgroup bsp Board Support Package
 * @{
 * @ingroup app_common
 *
 * @brief BSP module.
 * @details This module provides a layer of abstraction from the board.
 *          It allows the user to indicate certain states on LEDs in a simple way.
 *          Module functionality can be modified by defining BSP_SIMPLE to reduce
 *          functionality of this module to enable and read state of the buttons.
 */

#ifndef BSP_H__
#define BSP_H__

#include <stdint.h>
#include <stdbool.h>
#include "boards.h"

#define BSP_INIT_NONE    0        /**< This define specifies the type of initialization without support for LEDs and buttons (@ref bsp_init).*/
#define BSP_INIT_LED     (1 << 0) /**< This bit enables LEDs during initialization (@ref bsp_init).*/
#define BSP_INIT_BUTTONS (1 << 1) /**< This bit enables buttons during initialization (@ref bsp_init).*/

#if !defined(BSP_DEFINES_ONLY) && !defined(BSP_SIMPLE)
#include "app_button.h"

#define BSP_BUTTON_ACTION_PUSH      (APP_BUTTON_PUSH)    /**< Represents pushing a button. See @ref bsp_button_action_t. */
#define BSP_BUTTON_ACTION_RELEASE   (APP_BUTTON_RELEASE) /**< Represents releasing a button. See @ref bsp_button_action_t. */
#define BSP_BUTTON_ACTION_LONG_PUSH (2)                  /**< Represents pushing and holding a button for @ref BSP_LONG_PUSH_TIMEOUT_MS milliseconds. See also @ref bsp_button_action_t. */

#endif

/* BSP_UART_SUPPORT
 * This define enables UART support module.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t bsp_button_action_t; /**< The different actions that can be performed on a button. */

#define BSP_INDICATIONS_LIST {                \
        "BSP_INDICATE_IDLE",                  \
        "BSP_INDICATE_SCANNING",              \
        "BSP_INDICATE_ADVERTISING",           \
        "BSP_INDICATE_ADVERTISING_WHITELIST", \
        "BSP_INDICATE_ADVERTISING_SLOW",      \
        "BSP_INDICATE_ADVERTISING_DIRECTED",  \
        "BSP_INDICATE_BONDING",               \
        "BSP_INDICATE_CONNECTED",             \
        "BSP_INDICATE_SENT_OK",               \
        "BSP_INDICATE_SEND_ERROR",            \
        "BSP_INDICATE_RCV_OK",                \
        "BSP_INDICATE_RCV_ERROR",             \
        "BSP_INDICATE_FATAL_ERROR",           \
        "BSP_INDICATE_ALERT_0",               \
        "BSP_INDICATE_ALERT_1",               \
        "BSP_INDICATE_ALERT_2",               \
        "BSP_INDICATE_ALERT_3",               \
        "BSP_INDICATE_ALERT_OFF",             \
        "BSP_INDICATE_USER_STATE_OFF",        \
        "BSP_INDICATE_USER_STATE_0",          \
        "BSP_INDICATE_USER_STATE_1",          \
        "BSP_INDICATE_USER_STATE_2",          \
        "BSP_INDICATE_USER_STATE_3",          \
        "BSP_INDICATE_USER_STATE_ON"          \
} /**< See @ref examples_bsp_states for a list of how these states are indicated for the PCA10028/PCA10040 board and the PCA10031 dongle.*/


/**@brief BSP indication states.
 *
 * @details See @ref examples_bsp_states for a list of how these states are indicated for the PCA10028/PCA10040 board and the PCA10031 dongle.
 */
typedef enum
{
    BSP_INDICATE_FIRST = 0,
    BSP_INDICATE_IDLE  = BSP_INDICATE_FIRST, /**< See \ref BSP_INDICATE_IDLE.*/
    BSP_INDICATE_SCANNING,                   /**< See \ref BSP_INDICATE_SCANNING.*/
    BSP_INDICATE_ADVERTISING,                /**< See \ref BSP_INDICATE_ADVERTISING.*/
    BSP_INDICATE_ADVERTISING_WHITELIST,      /**< See \ref BSP_INDICATE_ADVERTISING_WHITELIST.*/
    BSP_INDICATE_ADVERTISING_SLOW,           /**< See \ref BSP_INDICATE_ADVERTISING_SLOW.*/
    BSP_INDICATE_ADVERTISING_DIRECTED,       /**< See \ref BSP_INDICATE_ADVERTISING_DIRECTED.*/
    BSP_INDICATE_BONDING,                    /**< See \ref BSP_INDICATE_BONDING.*/
    BSP_INDICATE_CONNECTED,                  /**< See \ref BSP_INDICATE_CONNECTED.*/
    BSP_INDICATE_SENT_OK,                    /**< See \ref BSP_INDICATE_SENT_OK.*/
    BSP_INDICATE_SEND_ERROR,                 /**< See \ref BSP_INDICATE_SEND_ERROR.*/
    BSP_INDICATE_RCV_OK,                     /**< See \ref BSP_INDICATE_RCV_OK.*/
    BSP_INDICATE_RCV_ERROR,                  /**< See \ref BSP_INDICATE_RCV_ERROR.*/
    BSP_INDICATE_FATAL_ERROR,                /**< See \ref BSP_INDICATE_FATAL_ERROR.*/
    BSP_INDICATE_ALERT_0,                    /**< See \ref BSP_INDICATE_ALERT_0.*/
    BSP_INDICATE_ALERT_1,                    /**< See \ref BSP_INDICATE_ALERT_1.*/
    BSP_INDICATE_ALERT_2,                    /**< See \ref BSP_INDICATE_ALERT_2.*/
    BSP_INDICATE_ALERT_3,                    /**< See \ref BSP_INDICATE_ALERT_3.*/
    BSP_INDICATE_ALERT_OFF,                  /**< See \ref BSP_INDICATE_ALERT_OFF.*/
    BSP_INDICATE_USER_STATE_OFF,             /**< See \ref BSP_INDICATE_USER_STATE_OFF.*/
    BSP_INDICATE_USER_STATE_0,               /**< See \ref BSP_INDICATE_USER_STATE_0.*/
    BSP_INDICATE_USER_STATE_1,               /**< See \ref BSP_INDICATE_USER_STATE_1.*/
    BSP_INDICATE_USER_STATE_2,               /**< See \ref BSP_INDICATE_USER_STATE_2.*/
    BSP_INDICATE_USER_STATE_3,               /**< See \ref BSP_INDICATE_USER_STATE_3.*/
    BSP_INDICATE_USER_STATE_ON,              /**< See \ref BSP_INDICATE_USER_STATE_ON.*/
    BSP_INDICATE_LAST = BSP_INDICATE_USER_STATE_ON
} bsp_indication_t;

/**@brief BSP events.
 *
 * @note Events from BSP_EVENT_KEY_0 to BSP_EVENT_KEY_LAST are by default assigned to buttons.
 */
typedef enum
{
    BSP_EVENT_NOTHING = 0,                  /**< Assign this event to an action to prevent the action from generating an event (disable the action). */
    BSP_EVENT_DEFAULT,                      /**< Assign this event to an action to assign the default event to the action. */
    BSP_EVENT_CLEAR_BONDING_DATA,           /**< Persistent bonding data should be erased. */
    BSP_EVENT_CLEAR_ALERT,                  /**< An alert should be cleared. */
    BSP_EVENT_DISCONNECT,                   /**< A link should be disconnected. */
    BSP_EVENT_ADVERTISING_START,            /**< The device should start advertising. */
    BSP_EVENT_ADVERTISING_STOP,             /**< The device should stop advertising. */
    BSP_EVENT_WHITELIST_OFF,                /**< The device should remove its advertising whitelist. */
    BSP_EVENT_BOND,                         /**< The device should bond to the currently connected peer. */
    BSP_EVENT_RESET,                        /**< The device should reset. */
    BSP_EVENT_SLEEP,                        /**< The device should enter sleep mode. */
    BSP_EVENT_WAKEUP,                       /**< The device should wake up from sleep mode. */
    BSP_EVENT_SYSOFF,                       /**< The device should enter system off mode (without wakeup). */
    BSP_EVENT_DFU,                          /**< The device should enter DFU mode. */
    BSP_EVENT_KEY_0,                        /**< Default event of the push action of BSP_BUTTON_0 (only if this button is present). */
    BSP_EVENT_KEY_1,                        /**< Default event of the push action of BSP_BUTTON_1 (only if this button is present). */
    BSP_EVENT_KEY_2,                        /**< Default event of the push action of BSP_BUTTON_2 (only if this button is present). */
    BSP_EVENT_KEY_3,                        /**< Default event of the push action of BSP_BUTTON_3 (only if this button is present). */
    BSP_EVENT_KEY_4,                        /**< Default event of the push action of BSP_BUTTON_4 (only if this button is present). */
    BSP_EVENT_KEY_5,                        /**< Default event of the push action of BSP_BUTTON_5 (only if this button is present). */
    BSP_EVENT_KEY_6,                        /**< Default event of the push action of BSP_BUTTON_6 (only if this button is present). */
    BSP_EVENT_KEY_7,                        /**< Default event of the push action of BSP_BUTTON_7 (only if this button is present). */
    BSP_EVENT_KEY_LAST = BSP_EVENT_KEY_7,
} bsp_event_t;


typedef struct
{
    bsp_event_t push_event;      /**< The event to fire on regular button press. */
    bsp_event_t long_push_event; /**< The event to fire on long button press. */
    bsp_event_t release_event;   /**< The event to fire on button release. */
} bsp_button_event_cfg_t;

/**@brief BSP module event callback function type.
 *
 * @details     Upon an event in the BSP module, this callback function will be called to notify
 *              the application about the event.
 *
 * @param[in]   bsp_event_t BSP event type.
 */
typedef void (* bsp_event_callback_t)(bsp_event_t);


/**@brief       Function for initializing BSP.
 *
 * @details     The function initializes the board support package to allow state indication and
 *              button reaction. Default events are assigned to buttons.
 * @note        Before calling this function, you must initiate the following required modules:
 *              - @ref app_timer for LED support
 *              - @ref app_gpiote for button support
 *
 * @param[in]   type               Type of peripherals used.
 * @param[in]   callback           Function to be called when button press/event is detected.
 *
 * @retval      NRF_SUCCESS               If the BSP module was successfully initialized.
 * @retval      NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized.
 * @retval      NRF_ERROR_NO_MEM          If the maximum number of timers has already been reached.
 * @retval      NRF_ERROR_INVALID_PARAM   If GPIOTE has too many users.
 * @retval      NRF_ERROR_INVALID_STATE   If button or GPIOTE has not been initialized.
 */
uint32_t bsp_init(uint32_t type, bsp_event_callback_t callback);


/**@brief       Function for checking button states.
 *
 * @details     This function checks if the button is pressed. If the button ID is out of range,
 *              the function returns false.
 *
 * @param[in]   button                  Button ID to check.
 *
 * @retval      true                    If the button is pressed.
 * @retval      false                   If the button is not pressed.
 */
bool bsp_button_is_pressed(uint32_t button);


/**@brief       Function for assigning a specific event to a button.
 *
 * @details     This function allows redefinition of standard events assigned to buttons.
 *              To unassign events, provide the event @ref BSP_EVENT_NOTHING.
 *
 * @param[in]   button                   Button ID to be redefined.
 * @param[in]   action                   Button action to assign event to.
 * @param[in]   event                    Event to be assigned to button.
 *
 * @retval      NRF_SUCCESS              If the event was successfully assigned to button.
 * @retval      NRF_ERROR_INVALID_PARAM  If the button ID or button action was invalid.
 */
uint32_t bsp_event_to_button_action_assign(uint32_t button, bsp_button_action_t action, bsp_event_t event);


/**@brief       Function for configuring indicators to required state.
 *
 * @details     This function indicates the required state by means of LEDs (if enabled).
 *
 * @note        Alerts are indicated independently.
 *
 * @param[in]   indicate   State to be indicated.
 *
 * @retval      NRF_SUCCESS               If the state was successfully indicated.
 * @retval      NRF_ERROR_NO_MEM          If the internal timer operations queue was full.
 * @retval      NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized,
 *                                        or internal timer has not been created.
 */
uint32_t bsp_indication_set(bsp_indication_t indicate);


/**@brief       Function for enabling all buttons.
 *
 * @details     After calling this function, all buttons will generate events when pressed, and
 *              all buttons will be able to wake the system up from sleep mode.
 *
 * @retval      NRF_SUCCESS              If the buttons were successfully enabled.
 * @retval      NRF_ERROR_NOT_SUPPORTED  If the board has no buttons or BSP_SIMPLE is defined.
 * @return      A propagated error.
 */
uint32_t bsp_buttons_enable(void);


/**@brief       Function for disabling all buttons.
 *
 * @details     After calling this function, no buttons will generate events when pressed, and
 *              no buttons will be able to wake the system up from sleep mode.
 *
 * @retval      NRF_SUCCESS              If the buttons were successfully disabled.
 * @retval      NRF_ERROR_NOT_SUPPORTED  If the board has no buttons or BSP_SIMPLE is defined.
 * @return      A propagated error.
 */
uint32_t bsp_buttons_disable(void);


/**@brief       Function for enabling wakeup from SYSTEM OFF for given button.
 *
 * @details     After calling this function, button can be used to wake up the chip.
 *              This function should only be called immediately before going into sleep.
 *
 * @param[in]   button_idx  Index of the button.
 *
 * @retval      NRF_SUCCESS              If the button was successfully enabled.
 * @retval      NRF_ERROR_NOT_SUPPORTED  If the board has no buttons or BSP_SIMPLE is defined.
 */
uint32_t bsp_wakeup_button_enable(uint32_t button_idx);


/**@brief       Function for disabling wakeup for the given button.
 *
 * @param[in]   button_idx  index of the button.
 *
 * @retval      NRF_SUCCESS              If the button was successfully disabled.
 * @retval      NRF_ERROR_NOT_SUPPORTED  If the board has no buttons or BSP_SIMPLE is defined.
 */
uint32_t bsp_wakeup_button_disable(uint32_t button_idx);


#ifdef __cplusplus
}
#endif

#endif // BSP_H__

/** @} */
