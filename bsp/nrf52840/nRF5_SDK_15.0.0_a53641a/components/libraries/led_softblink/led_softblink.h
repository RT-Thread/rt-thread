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
/** @file
 *
 * @defgroup led_softblink LED softblink
 * @{
 * @ingroup app_common
 *
 * @brief Module for generating a changing pulse-width modulated output signal that is used to smoothly blink LEDs.
 *
 * @details This module provides an LED softblink implementation using timers and GPIO.
 *
 * LED softblink needs one timer. It can use any number of output channels that are available.
 *
 * Only one instance of LED softblink can run at a time.
 */

#ifndef LED_SOFTBLINK_H__
#define LED_SOFTBLINK_H__

#include <stdbool.h>
#include <stdint.h>
#include "sdk_errors.h"
#include "nrf_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure holding the initialization parameters.
 */
typedef struct
{
    bool            active_high;     /**< Activate negative polarity. */
    uint8_t         duty_cycle_max;  /**< Maximum impulse width. */
    uint8_t         duty_cycle_min;  /**< Minimum impulse width. */
    uint8_t         duty_cycle_step; /**< Cycle step. */
    uint32_t        off_time_ticks;  /**< Ticks to stay in low impulse state. */
    uint32_t        on_time_ticks;   /**< Ticks to stay in high impulse state. */
    uint32_t        leds_pin_bm;     /**< Mask of used LEDs. */
    NRF_GPIO_Type * p_leds_port;     /**< Port of used LEDs mask. */
}led_sb_init_params_t;

/**
 * @name Default settings
 * @brief Default settings for LED softblink.
 * @{
 */
#define LED_SB_INIT_PARAMS_ACTIVE_HIGH            false
#define LED_SB_INIT_PARAMS_DUTY_CYCLE_MAX         220
#define LED_SB_INIT_PARAMS_DUTY_CYCLE_MIN         0
#define LED_SB_INIT_PARAMS_DUTY_CYCLE_STEP        5
#define LED_SB_INIT_PARAMS_OFF_TIME_TICKS         65536
#define LED_SB_INIT_PARAMS_ON_TIME_TICKS          0
#define LED_SB_INIT_PARAMS_LEDS_PIN_BM(mask)      (mask)
#define LED_SB_INIT_PARAMS_LEDS_PORT              NRF_GPIO
/** @} */

/**
 * @brief LED softblink default configuration.
 */
#define LED_SB_INIT_DEFAULT_PARAMS(mask)                            \
{                                                                   \
    .active_high        = LED_SB_INIT_PARAMS_ACTIVE_HIGH,           \
    .duty_cycle_max     = LED_SB_INIT_PARAMS_DUTY_CYCLE_MAX,        \
    .duty_cycle_min     = LED_SB_INIT_PARAMS_DUTY_CYCLE_MIN,        \
    .duty_cycle_step    = LED_SB_INIT_PARAMS_DUTY_CYCLE_STEP,       \
    .off_time_ticks     = LED_SB_INIT_PARAMS_OFF_TIME_TICKS,        \
    .on_time_ticks      = LED_SB_INIT_PARAMS_ON_TIME_TICKS,         \
    .leds_pin_bm        = LED_SB_INIT_PARAMS_LEDS_PIN_BM(mask),     \
    .p_leds_port        = LED_SB_INIT_PARAMS_LEDS_PORT              \
}

/**
 * @brief Function for initializing LED softblink.
 *
 * @param[in] p_init_params Pointer to the initialization structure.
 *
 * @return Values returned by @ref app_timer_create.
 */
ret_code_t led_softblink_init(led_sb_init_params_t const * p_init_params);

/**
 * @brief Function for starting to blink LEDs.
 *
 * @param[in] leds_pin_bit_mask Bit mask containing the pins for the LEDs to be blinked.
 *
 * @return Values returned by @ref app_timer_start.
 */
ret_code_t led_softblink_start(uint32_t leds_pin_bit_mask);

/**
 * @brief Function for stopping to blink LEDs.
 *
 * @return Values returned by @ref app_timer_stop.
 */
ret_code_t led_softblink_stop(void);

/**
 * @brief Function for setting the off time.
 *
 * This function configures the time that the LEDs will be off between each blink.
 *
 * @param[in] off_time_ticks Off time in ticks.
 *
 */
void led_softblink_off_time_set(uint32_t off_time_ticks);

/**
 * @brief Function for setting the on time.
 *
 * This function configures the time that the LEDs will be on between each blink.
 *
 * @param[in] on_time_ticks On time in ticks.
 *
 */
void led_softblink_on_time_set(uint32_t on_time_ticks);

/**
 * @brief Function for uninitializing LED softblink.
 *
 * @retval NRF_SUCCESS If LED softblink was uninitialized successfully.
 */
ret_code_t led_softblink_uninit(void);

#ifdef __cplusplus
}
#endif

#endif // LED_SOFTBLINK_H__

/** @} */

