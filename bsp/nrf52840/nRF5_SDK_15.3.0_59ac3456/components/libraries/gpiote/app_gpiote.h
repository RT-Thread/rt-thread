/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
 * @defgroup app_gpiote GPIOTE Handler
 * @{
 * @ingroup app_common
 *
 * @brief GPIOTE handler module.
 *
 * @details The GPIOTE handler allows several modules ("users") to share the GPIOTE interrupt,
 *          each user defining a set of pins able to generate events to the user.
 *          When a GPIOTE interrupt occurs, the GPIOTE interrupt handler will call the event handler
 *          of each user for which at least one of the pins generated an event.
 *
 *          The GPIOTE users are responsible for configuring all their corresponding pins, except
 *          the SENSE field, which should be initialized to GPIO_PIN_CNF_SENSE_Disabled.
 *          The SENSE field will be updated by the GPIOTE module when it is enabled or disabled,
 *          and also while it is enabled.
 *
 *          The module specifies on which pins events should be generated if the pin(s) goes
 *          from low->high or high->low or both directions.
 *
 * @note    Even if the application is using the @ref app_scheduler, the GPIOTE event handlers will
 *          be called directly from the GPIOTE interrupt handler.
 *
 * @warning If multiple users registers for the same pins the behavior for those pins are undefined.
 */

#ifndef APP_GPIOTE_H__
#define APP_GPIOTE_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GPIOTE_USER_NODE_SIZE   ((4*sizeof(uint32_t)*GPIO_COUNT)+8)          /**< Size of app_gpiote.gpiote_user_t (only for use inside APP_GPIOTE_BUF_SIZE()). */

/**@brief Compute number of bytes required to hold the GPIOTE data structures.
 *
 * @param[in]   MAX_USERS   Maximum number of GPIOTE users.
 *
 * @retval      Required buffer size (in bytes).
 */
#define APP_GPIOTE_BUF_SIZE(MAX_USERS)  ((MAX_USERS) * GPIOTE_USER_NODE_SIZE)

typedef uint8_t app_gpiote_user_id_t;

/**@brief GPIOTE event handler type. */
typedef void (*app_gpiote_event_handler_t)(uint32_t const * p_event_pins_low_to_high,
                                           uint32_t const * p_event_pins_high_to_low);

/**@brief GPIOTE input event handler type. */
typedef void (*app_gpiote_input_event_handler_t)(void);


/* Make the pin config descriptor packed */
#pragma pack(push, 1)

/**
 * @brief Single pin configuration
 *
 * Structure used to describe single pin configuration
 * when registering user.
 * @sa app_gpiote_user_register_ex
 */
typedef struct
{
    /** Pin number to observe */
    uint32_t              pin_number  : VBITS(NRF_GPIO_PIN_MAP(GPIO_COUNT - 1, 31));
    /** Transition to observe */
    nrf_gpiote_polarity_t sense       : 2;
} app_gpiote_user_pin_config_t;

// Check if we can fitt all the nrf_gpiote_polarity_t values into 2 bits field
STATIC_ASSERT(NRF_GPIOTE_POLARITY_LOTOHI <= 3);
STATIC_ASSERT(NRF_GPIOTE_POLARITY_HITOLO <= 3);
STATIC_ASSERT(NRF_GPIOTE_POLARITY_TOGGLE <= 3);

#pragma pack(pop)

/**@brief Macro for initializing the GPIOTE module.
 *
 * @details It will handle dimensioning and allocation of the memory buffer required by the module,
 *          making sure that the buffer is correctly aligned.
 *
 * @param[in]   MAX_USERS   Maximum number of GPIOTE users.
 *
 * @note Since this macro allocates a buffer, it must only be called once (it is OK to call it
 *       several times as long as it is from the same location, e.g. to do a reinitialization).
 */
/*lint -emacro(506, APP_GPIOTE_INIT) */ /* Suppress "Constant value Boolean */
#define APP_GPIOTE_INIT(MAX_USERS)                                                                 \
    do                                                                                             \
    {                                                                                              \
        static uint32_t app_gpiote_buf[CEIL_DIV(APP_GPIOTE_BUF_SIZE(MAX_USERS), sizeof(uint32_t))];\
        uint32_t ERR_CODE = app_gpiote_init((MAX_USERS), app_gpiote_buf);                          \
        APP_ERROR_CHECK(ERR_CODE);                                                                 \
    } while (0)

/**@brief Function for initializing the GPIOTE module.
 *
 * @note Normally initialization should be done using the APP_GPIOTE_INIT() macro, as that will
 *       allocate the buffer needed by the GPIOTE module (including aligning the buffer correctly).
 *
 * @param[in]   max_users               Maximum number of GPIOTE users.
 * @param[in]   p_buffer                Pointer to memory buffer for internal use in the app_gpiote
 *                                      module. The size of the buffer can be computed using the
 *                                      APP_GPIOTE_BUF_SIZE() macro. The buffer must be aligned to
 *                                      a 4 byte boundary.
 *
 * @retval      NRF_SUCCESS             Successful initialization.
 * @retval      NRF_ERROR_INVALID_PARAM Invalid parameter (buffer not aligned to a 4 byte
 *                                      boundary).
 */
uint32_t app_gpiote_init(uint8_t max_users, void * p_buffer);

/**@brief Function for registering a GPIOTE user.
 *
 * @param[out]  p_user_id               Id for the new GPIOTE user.
 * @param[in]   p_pins_low_to_high_mask Pointer to word array with mask defining which pins
 *                                      will generate events to this user when state is changed
 *                                      from low->high. Size of array depends on number of ports
 *                                      in the device.
 * @param[in]   p_pins_high_to_low_mask Pointer to word array with mask defining which pins
 *                                      will generate events to this user when state is changed
 *                                      from high->low. Size of array depends on number of ports
 *                                      in the device.
 * @param[in]   event_handler           Pointer to function to be executed when an event occurs.
 *                                      Cannot be NULL.
 *
 * @retval      NRF_SUCCESS             Successful initialization.
 * @retval      NRF_ERROR_INALID_STATE  If @ref app_gpiote_init has not been called on the GPIOTE
 *                                      module.
 * @retval      NRF_ERROR_NO_MEM        Returned if the application tries to register more users
 *                                      than defined when the GPIOTE module was initialized in
 *                                      @ref app_gpiote_init.
 *
 * @note The function can also return error codes from internally
 * called @ref nrf_drv_gpiote_in_init
 *
 * @sa app_gpiote_user_register_ex
 */
uint32_t app_gpiote_user_register(app_gpiote_user_id_t *     p_user_id,
                                  uint32_t const *           p_pins_low_to_high_mask,
                                  uint32_t const *           p_pins_high_to_low_mask,
                                  app_gpiote_event_handler_t event_handler);

/**@brief Function for registering GPIOTE user using pins configuration list.
 *
 * Function for registering GPIOTE user that uses array of pins configuration.
 * This function do not change pins configuration.
 * Pins must be configured before calling this function.
 *
 * @param[out]  p_user_id      Id for the new GPIOTE user.
 * @param[in]   p_pins_config  Pointer to the array of pins configuration for the user.
 * @param[in]   pin_count      Number of pins to configure for the user.
 * @param[in]   event_handler  Pointer to function to be executed when an event occurs.
 *                             Cannot be NULL.
 *
 * @retval      NRF_SUCCESS             Successful user registration.
 * @retval      NRF_ERROR_INVALID_STATE If @ref app_gpiote_init has not been called before calling
 *                                      this function.
 * @retval      NRF_ERROR_NO_MEM        Returned if the application tries to register more users
 *                                      than defined when the GPIOTE module was initialized in
 *                                      @ref app_gpiote_init.
 *
 * @note The function can also return error codes from internally
 * called @ref nrf_drv_gpiote_in_init
 *
 * @sa app_gpiote_user_register
 */
uint32_t app_gpiote_user_register_ex(app_gpiote_user_id_t * p_user_id,
                                     app_gpiote_user_pin_config_t const * p_pins_config,
                                     size_t pin_count,
                                     app_gpiote_event_handler_t event_handler);

/**@brief Function for informing the GPIOTE module that the specified user wants to use the GPIOTE module.
 *
 * @param[in]   user_id                 Id of user to enable.
 *
 * @retval      NRF_SUCCESS             On success.
 * @retval      NRF_ERROR_INVALID_PARAM Invalid user_id provided, No a valid user.
 * @retval      NRF_ERROR_INALID_STATE  If @ref app_gpiote_init has not been called on the GPIOTE
 *                                      module.
 */
uint32_t app_gpiote_user_enable(app_gpiote_user_id_t user_id);

/**@brief Function for informing the GPIOTE module that the specified user is done using the GPIOTE module.
 *
 * @param[in]   user_id                   Id of user to enable.
 *
 * @retval      NRF_SUCCESS               On success.
 * @retval      NRF_ERROR_INVALID_PARAM   Invalid user_id provided, No a valid user.
 * @retval      NRF_ERROR_INALID_STATE    If @ref app_gpiote_init has not been called on the GPIOTE
 *                                        module.
 */
uint32_t app_gpiote_user_disable(app_gpiote_user_id_t user_id);

/**@brief Function for getting the state of the pins which are registered for the specified user.
 *
 * @param[in]   user_id         Id of user to check.
 * @param[out]  p_pins          Pointer to array of words with bit mask corresponding to the pins
 *                              configured to generate events to the specified user. All bits
 *                              corresponding to pins in the state 'high' will have value '1',
 *                              all others will have value '0'. Size of array depends on number
 *                              of ports in the device.
 *
 * @retval      NRF_SUCCESS               On success.
 * @retval      NRF_ERROR_INVALID_PARAM   Invalid user_id provided, No a valid user.
 * @retval      NRF_ERROR_INALID_STATE    If @ref app_gpiote_init has not been called on the GPIOTE
 *                                        module.
 */
uint32_t app_gpiote_pins_state_get(app_gpiote_user_id_t user_id, uint32_t * p_pins);

#ifdef __cplusplus
}
#endif

#endif // APP_GPIOTE_H__

/** @} */
