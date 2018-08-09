/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
 *          Module functionality can be modified by additional defines:
 *          - BSP_SIMPLE - reduces functionality of this module to enable
 *            and read state of the buttons.
 *          - BSP_UART_SUPPORT - enables support for UART.
 */

#ifndef BSP_CONFIG_H__
#define BSP_CONFIG_H__

#include <stdint.h>
#include <stdbool.h>
#include "boards.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(BSP_DEFINES_ONLY) && !defined(BSP_SIMPLE)
#include "app_button.h"

#define BSP_BUTTON_ACTION_PUSH      (APP_BUTTON_PUSH)    /**< Represents pushing a button. See @ref bsp_button_action_t. */
#define BSP_BUTTON_ACTION_RELEASE   (APP_BUTTON_RELEASE) /**< Represents releasing a button. See @ref bsp_button_action_t. */
#define BSP_BUTTON_ACTION_LONG_PUSH (2)                  /**< Represents pushing and holding a button for @ref BSP_LONG_PUSH_TIMEOUT_MS milliseconds. See also @ref bsp_button_action_t. */
#endif

#define BSP_MS_TO_TICK(MS) (m_app_ticks_per_100ms * (MS / 100))


#define BUTTON_ERASE_BONDING BSP_BUTTON_0_MASK
#define BUTTON_ERASE_ALL     BSP_BUTTON_1_MASK
#define BUTTON_ADVERTISE     BSP_BUTTON_0_MASK
#define BUTTON_CLEAR_EVT     BSP_BUTTON_1_MASK
#define BUTTON_CAPSLOCK      BSP_BUTTON_2_MASK
#define BSP_BUTTONS_ALL      0xFFFFFFFF
#define BSP_BUTTONS_NONE     0

#define BSP_LONG_PUSH_TIMEOUT_MS (1000) /**< The time to hold for a long push (in milliseconds). */
/**@brief Types of BSP initialization.
 */

#define ADVERTISING_LED_ON_INTERVAL            200
#define ADVERTISING_LED_OFF_INTERVAL           1800

#define ADVERTISING_DIRECTED_LED_ON_INTERVAL   200
#define ADVERTISING_DIRECTED_LED_OFF_INTERVAL  200

#define ADVERTISING_WHITELIST_LED_ON_INTERVAL  200
#define ADVERTISING_WHITELIST_LED_OFF_INTERVAL 800

#define ADVERTISING_SLOW_LED_ON_INTERVAL       400
#define ADVERTISING_SLOW_LED_OFF_INTERVAL      4000

#define BONDING_INTERVAL                       100

#define SENT_OK_INTERVAL                       100
#define SEND_ERROR_INTERVAL                    500

#define RCV_OK_INTERVAL                        100
#define RCV_ERROR_INTERVAL                     500

#define ALERT_INTERVAL                         200

#define BSP_LED_INDICATE_SENT_OK               BSP_BOARD_LED_1
#define BSP_LED_INDICATE_SEND_ERROR            BSP_BOARD_LED_1
#define BSP_LED_INDICATE_RCV_OK                BSP_BOARD_LED_1
#define BSP_LED_INDICATE_RCV_ERROR             BSP_BOARD_LED_1
#define BSP_LED_INDICATE_CONNECTED             BSP_BOARD_LED_0
#define BSP_LED_INDICATE_BONDING               BSP_BOARD_LED_0
#define BSP_LED_INDICATE_ADVERTISING_DIRECTED  BSP_BOARD_LED_0
#define BSP_LED_INDICATE_ADVERTISING_SLOW      BSP_BOARD_LED_0
#define BSP_LED_INDICATE_ADVERTISING_WHITELIST BSP_BOARD_LED_0
#define BSP_LED_INDICATE_INDICATE_ADVERTISING  BSP_BOARD_LED_0

#define BSP_LED_INDICATE_USER_LED1            BSP_BOARD_LED_0
#define BSP_LED_INDICATE_USER_LED2            BSP_BOARD_LED_1
#define BSP_LED_INDICATE_USER_LED3            BSP_BOARD_LED_2
#define BSP_LED_INDICATE_USER_LED4            BSP_BOARD_LED_3

#define BSP_LED_ALERT                         BSP_BOARD_LED_2

#ifdef __cplusplus
}
#endif

#endif // BSP_CONFIG_H__

/** @} */
