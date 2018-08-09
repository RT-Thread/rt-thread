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
/**@file
 *
 * @defgroup app_simple_timer Simple Timer
 * @{
 * @ingroup  app_common
 *
 * @brief    Simple timer module.
 *
 * Supported features and limitations:
 * - Two modes: single shot mode and repeated mode.
 * - No more than one timer can run simultaneously.
 * - The timer is hard-coded to use the TIMER1 peripheral and compare channel 0.
 */

#ifndef TIMER_H__
#define TIMER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Timer time-out handler type. */
typedef void (*app_simple_timer_timeout_handler_t)(void * p_context);

/**@brief Timer modes. */
typedef enum
{
    APP_SIMPLE_TIMER_MODE_SINGLE_SHOT,   /**< The timer will expire only once. */
    APP_SIMPLE_TIMER_MODE_REPEATED       /**< The timer will restart each time it expires. */
} app_simple_timer_mode_t;

/**@brief Function for configuring and setting up the timer hardware.
 *
 * @note  Timer frequency is configured statically.
 *
 * @retval NRF_SUCCESS             If the operation is successful.
 * @retval NRF_ERROR_INVALID_STATE If the operation fails because the timer is already initialized.
 * @retval NRF_ERROR_INVALID_PARAM If the operation fails because some configuration parameter is
 *                                 not valid.
 */
uint32_t app_simple_timer_init(void);

/**@brief Function for starting a timer.
 *
 * @note  If this function is called for a timer that is already running, the currently running
 *        timer is stopped before starting the new one.
 *
 * @param[in] mode                 Timer mode (see @ref app_simple_timer_mode_t).
 * @param[in] timeout_handler      Function to be executed when the timer expires
 *                                 (see @ref app_simple_timer_timeout_handler_t).
 * @param[in] timeout_ticks        Number of timer ticks to time-out event.
 * @param[in] p_context            General purpose pointer. Will be passed to the time-out handler
 *                                 when the timer expires.
 *
 * @retval NRF_SUCCESS             If the operation is successful.
 * @retval NRF_ERROR_INVALID_STATE If the operation fails because @ref app_simple_timer_init has not
 *                                 been called and the operation is not allowed in this state.
 * @retval NRF_ERROR_NULL          If the operation fails because timeout_handler is NULL.
 * @retval NRF_ERROR_INVALID_PARAM If the operation fails because "mode" parameter is not valid.
 */

uint32_t app_simple_timer_start(app_simple_timer_mode_t            mode,
                                app_simple_timer_timeout_handler_t timeout_handler,
                                uint16_t                           timeout_ticks,
                                void *                             p_context);

/**@brief Function for stopping the timer.
 *
 * @retval NRF_SUCCESS             If the operation is successful.
 */
uint32_t app_simple_timer_stop(void);

/**@brief Function for uninitializing the timer. Should be called also when the timer is not used
 *        anymore to reach lowest power consumption in system.
 *
 * @note  The function switches off the internal core of the timer to reach lowest power consumption
 *        in system. The startup time from this state may be longer compared to starting the timer
 *        from the stopped state.
 *
 * @retval NRF_SUCCESS             If the operation is successful.
 */
uint32_t app_simple_timer_uninit(void);


#ifdef __cplusplus
}
#endif

#endif // TIMER_H__

/** @} */
