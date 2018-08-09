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
#if NRF_MODULE_ENABLED(APP_GPIOTE)
#include "app_gpiote.h"
#include "nrf_bitmask.h"
#define MODULE_INITIALIZED (mp_users != NULL) /**< Macro designating whether the module has been initialized properly. */

/**@brief GPIOTE user type. */
typedef struct
{
    uint32_t                   pins_mask[GPIO_COUNT];             /**< Mask defining which pins user wants to monitor. */
    uint32_t                   pins_low_to_high_mask[GPIO_COUNT]; /**< Mask defining which pins will generate events to this user when toggling low->high. */
    uint32_t                   pins_high_to_low_mask[GPIO_COUNT]; /**< Mask defining which pins will generate events to this user when toggling high->low. */
    uint32_t                   sense_high_pins[GPIO_COUNT];       /**< Mask defining which pins are configured to generate GPIOTE interrupt on transition to high level. */
    app_gpiote_event_handler_t event_handler;                     /**< Pointer to function to be executed when an event occurs. */
    bool                       enabled;                           /**< Flag indicating whether user is enabled. */
} gpiote_user_t;

STATIC_ASSERT(sizeof(gpiote_user_t) <= GPIOTE_USER_NODE_SIZE);
STATIC_ASSERT(sizeof(gpiote_user_t) % 4 == 0);

static uint8_t         m_user_array_size;             /**< Size of user array. */
static uint8_t         m_user_count;                  /**< Number of registered users. */
static gpiote_user_t * mp_users = NULL;               /**< Array of GPIOTE users. */
static uint32_t        m_pins[GPIO_COUNT];            /**< Mask of initialized pins. */
static uint32_t        m_last_pins_state[GPIO_COUNT]; /**< Most recent state of pins. */

void gpiote_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    int i;
    uint32_t pin_mask[GPIO_COUNT] = {0};
    uint32_t empty_pin_mask[GPIO_COUNT] = {0};
    nrf_bitmask_bit_set(pin, pin_mask);
    bool hitolo = nrf_bitmask_bit_is_set(pin, m_last_pins_state);
    nrf_gpio_ports_read(0, GPIO_COUNT, m_last_pins_state);

    for (i = 0; i < m_user_count; i++)
    {
        if (mp_users[i].enabled && nrf_bitmask_bit_is_set(pin, mp_users[i].pins_mask))
        {
            if (
          nrf_bitmask_bit_is_set(pin, mp_users[i].pins_high_to_low_mask)
          && hitolo)
            {
                mp_users[i].event_handler(empty_pin_mask,pin_mask);
            }
            else if (
          nrf_bitmask_bit_is_set(pin, mp_users[i].pins_low_to_high_mask)
          && !hitolo)
            {
                mp_users[i].event_handler(pin_mask,empty_pin_mask);
            }
        }
    }
}

uint32_t app_gpiote_init(uint8_t max_users, void * p_buffer)
{
    uint32_t ret_code = NRF_SUCCESS;

    if (p_buffer == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Check that buffer is correctly aligned.
    if (!is_word_aligned(p_buffer))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Initialize file globals.
    mp_users             = (gpiote_user_t *)p_buffer;
    m_user_array_size    = max_users;
    m_user_count         = 0;
    memset(m_pins,0, sizeof(m_pins));

    memset(mp_users, 0, m_user_array_size * sizeof(gpiote_user_t));

    if (nrf_drv_gpiote_is_init()==false)
    {
        ret_code = nrf_drv_gpiote_init();
    }

    return ret_code;
}

uint32_t app_gpiote_user_register(app_gpiote_user_id_t     * p_user_id,
                                  uint32_t const *           p_pins_low_to_high_mask,
                                  uint32_t const *           p_pins_high_to_low_mask,
                                  app_gpiote_event_handler_t event_handler)
{
    uint32_t user_pin_mask[GPIO_COUNT];
    ASSERT(event_handler != NULL);

    // Check state and parameters.
    VERIFY_MODULE_INITIALIZED();

    if (m_user_count >= m_user_array_size)
    {
        return NRF_ERROR_NO_MEM;
    }

    nrf_bitmask_masks_or(p_pins_low_to_high_mask, p_pins_high_to_low_mask,
                user_pin_mask, sizeof(user_pin_mask));
    // Allocate new user.
    mp_users[m_user_count].enabled       = false;
    mp_users[m_user_count].event_handler = event_handler;

    memcpy(mp_users[m_user_count].pins_mask,
          user_pin_mask,
          sizeof(mp_users[m_user_count].pins_mask));
    memcpy(mp_users[m_user_count].pins_low_to_high_mask,
           p_pins_low_to_high_mask,
           sizeof(mp_users[m_user_count].pins_low_to_high_mask));
    memcpy(mp_users[m_user_count].pins_high_to_low_mask,
           p_pins_high_to_low_mask,
           sizeof(mp_users[m_user_count].pins_high_to_low_mask));

    uint32_t i;
    const nrf_drv_gpiote_in_config_t config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(false);

    uint32_t num_of_pins = NUMBER_OF_PINS ;
    for (i = 0; i < num_of_pins; i++)
    {
        if (nrf_bitmask_bit_is_set(i, user_pin_mask) &&
           !nrf_bitmask_bit_is_set(i, m_pins))
        {
            uint32_t ret_val = nrf_drv_gpiote_in_init(i, &config, gpiote_handler);
            VERIFY_SUCCESS(ret_val);
            nrf_bitmask_bit_set(i, m_pins);
        }
    }

    /* Success - return user id and increment counter */
    *p_user_id = m_user_count++;
    return NRF_SUCCESS;
}

uint32_t app_gpiote_user_register_ex(app_gpiote_user_id_t * p_user_id,
                                     app_gpiote_user_pin_config_t const * p_pins_config,
                                     size_t pin_count,
                                     app_gpiote_event_handler_t event_handler)
{
    ASSERT(event_handler != NULL);

    // Check state and parameters.
    VERIFY_MODULE_INITIALIZED();
    if (m_user_count >= m_user_array_size)
    {
        return NRF_ERROR_NO_MEM;
    }
    /* Prepare user structure */
    gpiote_user_t * p_user = &mp_users[m_user_count];

    p_user->enabled = false;
    memset(p_user, 0, sizeof(gpiote_user_t));
    mp_users[m_user_count].event_handler = event_handler;

    for (; pin_count != 0; --pin_count, ++p_pins_config)
    {
        nrfx_gpiote_pin_t pin = (nrfx_gpiote_pin_t)p_pins_config->pin_number;
        const nrf_drv_gpiote_in_config_t config = GPIOTE_RAW_CONFIG_IN_SENSE_TOGGLE(false);
        if (!nrf_bitmask_bit_is_set(pin, m_pins))
        {
            uint32_t ret_val = nrf_drv_gpiote_in_init(pin, &config, gpiote_handler);
            VERIFY_SUCCESS(ret_val);
            nrf_bitmask_bit_set(pin, m_pins);
        }

        //lint -save -e650  Lint seems not properly support bitfields that uses enum as a base type
        if ((p_pins_config->sense == NRF_GPIOTE_POLARITY_LOTOHI) ||
            (p_pins_config->sense == NRF_GPIOTE_POLARITY_TOGGLE))
        {
            nrf_bitmask_bit_set(pin, p_user->pins_low_to_high_mask);
        }
        if ((p_pins_config->sense == NRF_GPIOTE_POLARITY_HITOLO) ||
            (p_pins_config->sense == NRF_GPIOTE_POLARITY_TOGGLE))
        {
            nrf_bitmask_bit_set(pin, p_user->pins_high_to_low_mask);
        }
        //lint -restore
    }
    /* Mark all pins used by the selected user */
    nrf_bitmask_masks_or(
        p_user->pins_low_to_high_mask,
        p_user->pins_high_to_low_mask,
        p_user->pins_mask,
        sizeof(p_user->pins_mask));
    /* Success - return user id and increment counter */
    *p_user_id = m_user_count++;

    return NRF_SUCCESS;
}

__STATIC_INLINE uint32_t error_check(app_gpiote_user_id_t user_id)
{
    // Check state and parameters.
    VERIFY_MODULE_INITIALIZED();

    if (user_id >= m_user_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    return NRF_SUCCESS;
}
/**
 * @brief Function for enabling event on pin (if not yet enabled) or disabling the event if no other
 *        user requires it.
 *
 * @param pin    Pin to enable
 * @param enable If true function will attempt to enable the pin else it will attempt to disable it.
 */
static void pin_event_enable(uint32_t pin, bool enable)
{
    uint32_t i;
    bool enabled = false;
    //search if any user already enabled given pin
    for (i = 0; i < m_user_count; i++)
    {
        if (mp_users[i].enabled &&
                nrf_bitmask_bit_is_set(pin, mp_users[i].pins_mask))
        {
            enabled = true;
            break;
        }
    }
    if (!enabled)
    {
        if (enable)
        {
            nrf_gpio_ports_read(0, GPIO_COUNT, m_last_pins_state);
            nrf_drv_gpiote_in_event_enable(pin, true);
        }
        else
        {
            nrf_drv_gpiote_in_event_disable(pin);
        }
    }
}

/**
 * @brief Function for enabling or disabling events for pins used by the user.
 *
 * Function will enable pin events only if they are not yet enabled. Function will disable pin
 * events only if there is no other enabled user that is using them.
 *
 * @param user_id  User id.
 * @param enable   If true function will attempt to enable the pin else it will attempt to disable it.
 */
static uint32_t user_enable(app_gpiote_user_id_t user_id, bool enable)
{
    uint32_t ret_code = error_check(user_id);

    if (ret_code == NRF_SUCCESS)
    {
        uint32_t i;
        for (i = 0; i < NUMBER_OF_PINS; i++)
        {
            if (nrf_bitmask_bit_is_set(i, mp_users[user_id].pins_mask))
            {
                pin_event_enable(i, enable);
            }
        }
    }
    return ret_code;
}

uint32_t app_gpiote_user_enable(app_gpiote_user_id_t user_id)
{
    uint32_t ret_code = NRF_SUCCESS;

    if (mp_users[user_id].enabled == false)
    {
        ret_code = user_enable(user_id, true);
        VERIFY_SUCCESS(ret_code);

        mp_users[user_id].enabled = true;
        return ret_code;
    }
    else
    {
        return ret_code;
    }
}

uint32_t app_gpiote_user_disable(app_gpiote_user_id_t user_id)
{
    uint32_t ret_code = NRF_SUCCESS;

    if (mp_users[user_id].enabled)
    {
        mp_users[user_id].enabled = false;
        ret_code = user_enable(user_id, false);
    }

    return ret_code;
}

uint32_t app_gpiote_pins_state_get(app_gpiote_user_id_t user_id, uint32_t * p_pins)
{
    gpiote_user_t * p_user;
    uint32_t ret_code = error_check(user_id);

    if (ret_code == NRF_SUCCESS)
    {
        p_user  = &mp_users[user_id];

        nrf_gpio_ports_read(0, GPIO_COUNT, p_pins);
        nrf_bitmask_masks_and(p_pins, p_user->pins_mask, p_pins, sizeof(p_user->pins_mask));
    }
    return ret_code;
}
#endif //NRF_MODULE_ENABLED(APP_GPIOTE)
