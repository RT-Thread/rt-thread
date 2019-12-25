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
#if NRF_MODULE_ENABLED(LOW_POWER_PWM)
#include <string.h>
#include "low_power_pwm.h"
#include "nrf_gpio.h"
#include "app_timer.h"
#include "nrf_assert.h"

/**
 * @brief Function for turning on pins.
 *
 * Sets the pin high state according to active_high parameter.
 *
 * @param[in] p_pwm_instance        Pointer to instance of low-power PWM.
 */
__STATIC_INLINE void pin_on(low_power_pwm_t * p_pwm_instance)
{
    if (p_pwm_instance->active_high)
    {
        nrf_gpio_port_out_set(p_pwm_instance->p_port, p_pwm_instance->bit_mask_toggle);
    }
    else
    {
        nrf_gpio_port_out_clear(p_pwm_instance->p_port, p_pwm_instance->bit_mask_toggle);
    }
    p_pwm_instance->pin_is_on = true;
}


/**
 * @brief Function for turning off pins.
 *
 * Sets the pin low state according to active_high parameter.
 *
 * @param[in] p_pwm_instance        Pointer to instance of low-power PWM.
 */
__STATIC_INLINE void pin_off(low_power_pwm_t * p_pwm_instance)
{
    if (p_pwm_instance->active_high)
    {
        nrf_gpio_port_out_clear(p_pwm_instance->p_port, p_pwm_instance->bit_mask_toggle);
    }
    else
    {
        nrf_gpio_port_out_set(p_pwm_instance->p_port, p_pwm_instance->bit_mask_toggle);
    }
    p_pwm_instance->pin_is_on = false;
}


/**
 * @brief Timer event handler for PWM.
 *
 * @param[in] p_context             General purpose pointer. Will be passed to the time-out handler
 *                                  when the timer expires.
 *
 */
static void pwm_timeout_handler(void * p_context)
{
    ret_code_t err_code;
    uint8_t duty_cycle;

    low_power_pwm_t * p_pwm_instance = (low_power_pwm_t *)p_context;

    if (p_pwm_instance->evt_type == LOW_POWER_PWM_EVENT_PERIOD)
    {
        if (p_pwm_instance->handler)
        {
            p_pwm_instance->handler(p_pwm_instance);

            if (p_pwm_instance->pwm_state != NRFX_DRV_STATE_POWERED_ON)
            {
                return;
            }
        }

        duty_cycle = p_pwm_instance->duty_cycle;

        if (duty_cycle == p_pwm_instance->period)    // Process duty cycle 100%
        {
            pin_on(p_pwm_instance);
            p_pwm_instance->timeout_ticks = p_pwm_instance->period + APP_TIMER_MIN_TIMEOUT_TICKS;
        }
        else if (duty_cycle == 0)   // Process duty cycle 0%
        {
            pin_off(p_pwm_instance);
            p_pwm_instance->timeout_ticks = p_pwm_instance->period + APP_TIMER_MIN_TIMEOUT_TICKS;
        }
        else // Process any other duty cycle than 0 or 100%
        {
            pin_on(p_pwm_instance);
            p_pwm_instance->timeout_ticks = ((duty_cycle * p_pwm_instance->period)>>8) +
                                APP_TIMER_MIN_TIMEOUT_TICKS;
            // setting next state
            p_pwm_instance->evt_type = LOW_POWER_PWM_EVENT_DUTY_CYCLE;
        }
    }
    else
    {
        pin_off(p_pwm_instance);
        p_pwm_instance->evt_type = LOW_POWER_PWM_EVENT_PERIOD;
        p_pwm_instance->timeout_ticks = (((p_pwm_instance->period - p_pwm_instance->duty_cycle) *
                                    p_pwm_instance->period)>>8) + APP_TIMER_MIN_TIMEOUT_TICKS;
    }

    if (p_pwm_instance->pwm_state == NRFX_DRV_STATE_POWERED_ON)
    {
        err_code = app_timer_start(*p_pwm_instance->p_timer_id, p_pwm_instance->timeout_ticks, p_pwm_instance);
        APP_ERROR_CHECK(err_code);
    }
}


ret_code_t low_power_pwm_init(low_power_pwm_t * p_pwm_instance,
                            low_power_pwm_config_t const * p_pwm_config,
                            app_timer_timeout_handler_t handler)
{
    ASSERT(p_pwm_instance->pwm_state == NRFX_DRV_STATE_UNINITIALIZED);
    ASSERT(p_pwm_config->bit_mask != 0);
    ASSERT(p_pwm_config->p_port != NULL);
    ASSERT(p_pwm_config->period != 0);

    ret_code_t err_code;
    uint32_t bit_mask;
    uint32_t pin_number = 0;

    p_pwm_instance->handler = handler;

    bit_mask = p_pwm_config->bit_mask;

    p_pwm_instance->active_high = p_pwm_config->active_high;
    p_pwm_instance->bit_mask = p_pwm_config->bit_mask;
    p_pwm_instance->bit_mask_toggle = p_pwm_config->bit_mask;
    p_pwm_instance->p_port = p_pwm_config->p_port;
    p_pwm_instance->period = p_pwm_config->period;
    p_pwm_instance->p_timer_id = p_pwm_config->p_timer_id;

    err_code = app_timer_create(p_pwm_instance->p_timer_id, APP_TIMER_MODE_SINGLE_SHOT, pwm_timeout_handler);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    while (bit_mask)
    {
        if (bit_mask & 0x1UL)
        {
            nrf_gpio_cfg_output(pin_number);
        }

        pin_number++;
        bit_mask >>= 1UL;
    }

    pin_off(p_pwm_instance);
    p_pwm_instance->pwm_state = NRFX_DRV_STATE_INITIALIZED;

    return NRF_SUCCESS;
}


ret_code_t low_power_pwm_start(low_power_pwm_t * p_pwm_instance,
                               uint32_t          pin_bit_mask)
{
    ASSERT(p_pwm_instance->pwm_state != NRFX_DRV_STATE_UNINITIALIZED);
    ASSERT(((p_pwm_instance->bit_mask) & pin_bit_mask) != 0x00);

    p_pwm_instance->pwm_state = NRFX_DRV_STATE_POWERED_ON;
    p_pwm_instance->bit_mask_toggle = pin_bit_mask;

    pin_off(p_pwm_instance);

    p_pwm_instance->bit_mask |= pin_bit_mask;
    p_pwm_instance->evt_type = LOW_POWER_PWM_EVENT_PERIOD;

    app_timer_timeout_handler_t handler = p_pwm_instance->handler;
    p_pwm_instance->handler = NULL;
    pwm_timeout_handler(p_pwm_instance);
    p_pwm_instance->handler = handler;

    return NRF_SUCCESS;
}


ret_code_t low_power_pwm_stop(low_power_pwm_t * p_pwm_instance)
{
    ASSERT(p_pwm_instance->pwm_state == NRFX_DRV_STATE_POWERED_ON);

    ret_code_t err_code;

    err_code = app_timer_stop(*p_pwm_instance->p_timer_id);

    pin_off(p_pwm_instance);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    p_pwm_instance->pwm_state = NRFX_DRV_STATE_INITIALIZED;


    return NRF_SUCCESS;
}


ret_code_t low_power_pwm_duty_set(low_power_pwm_t * p_pwm_instance, uint8_t duty_cycle)
{
    if ( p_pwm_instance->period < duty_cycle)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_pwm_instance->duty_cycle = duty_cycle;

    return NRF_SUCCESS;
}
#endif //NRF_MODULE_ENABLED(LOW_POWER_PWM)
