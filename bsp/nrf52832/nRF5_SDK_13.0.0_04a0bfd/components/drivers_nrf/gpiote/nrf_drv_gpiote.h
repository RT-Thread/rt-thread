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
#ifndef NRF_DRV_GPIOTE__
#define NRF_DRV_GPIOTE__

/**
 * @addtogroup nrf_gpiote GPIOTE abstraction and driver
 * @ingroup nrf_drivers
 * @brief GPIOTE APIs.
 * @defgroup nrf_drv_gpiote GPIOTE driver
 * @{
 * @ingroup nrf_gpiote
 * @brief GPIOTE driver for managing input and output pins.
 */

#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "sdk_errors.h"
#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Input pin configuration. */
typedef struct
{
    nrf_gpiote_polarity_t sense;      /**< Transition that triggers interrupt. */
    nrf_gpio_pin_pull_t   pull;       /**< Pulling mode. */
    bool                  is_watcher; /**< True when the input pin is tracking an output pin. */
    bool                  hi_accuracy;/**< True when high accuracy (IN_EVENT) is used. */
} nrf_drv_gpiote_in_config_t;

/**@brief Macro for configuring a pin to use a GPIO IN or PORT EVENT to detect low-to-high transition.
 * @details Set hi_accu to true to use IN_EVENT. */
#define GPIOTE_CONFIG_IN_SENSE_LOTOHI(hi_accu)     \
    {                                            \
        .is_watcher = false,                     \
        .hi_accuracy = hi_accu,                  \
        .pull = NRF_GPIO_PIN_NOPULL,             \
        .sense = NRF_GPIOTE_POLARITY_LOTOHI,     \
    }

/**@brief Macro for configuring a pin to use a GPIO IN or PORT EVENT to detect high-to-low transition.
 * @details Set hi_accu to true to use IN_EVENT. */
#define GPIOTE_CONFIG_IN_SENSE_HITOLO(hi_accu)      \
    {                                            \
        .is_watcher = false,                     \
        .hi_accuracy = hi_accu,                  \
        .pull = NRF_GPIO_PIN_NOPULL,             \
        .sense = NRF_GPIOTE_POLARITY_HITOLO,     \
    }

/**@brief Macro for configuring a pin to use a GPIO IN or PORT EVENT to detect any change on the pin.
 * @details Set hi_accu to true to use IN_EVENT.*/
#define GPIOTE_CONFIG_IN_SENSE_TOGGLE(hi_accu)   \
    {                                            \
        .is_watcher = false,                     \
        .hi_accuracy = hi_accu,                  \
        .pull = NRF_GPIO_PIN_NOPULL,             \
        .sense = NRF_GPIOTE_POLARITY_TOGGLE,     \
    }

/**@brief Output pin configuration. */
typedef struct
{
    nrf_gpiote_polarity_t action;    /**< Configuration of the pin task. */
    nrf_gpiote_outinit_t  init_state; /**< Initial state of the output pin. */
    bool                  task_pin;  /**< True if the pin is controlled by a GPIOTE task. */
} nrf_drv_gpiote_out_config_t;

/**@brief Macro for configuring a pin to use as output. GPIOTE is not used for the pin. */
#define GPIOTE_CONFIG_OUT_SIMPLE(init_high)                                                        \
    {                                                                                              \
        .init_state = init_high ? NRF_GPIOTE_INITIAL_VALUE_HIGH : NRF_GPIOTE_INITIAL_VALUE_LOW,    \
        .task_pin = false,                                                                         \
    }

/**@brief Macro for configuring a pin to use the GPIO OUT TASK to change the state from high to low.
 * @details The task will clear the pin. Therefore, the pin is set initially.  */
#define GPIOTE_CONFIG_OUT_TASK_LOW                                                                 \
    {                                                                                              \
        .init_state = NRF_GPIOTE_INITIAL_VALUE_HIGH,                                               \
        .task_pin   = true,                                                                        \
        .action     = NRF_GPIOTE_POLARITY_HITOLO,                                                  \
    }

/**@brief Macro for configuring a pin to use the GPIO OUT TASK to change the state from low to high.
 * @details The task will set the pin. Therefore, the pin is cleared initially.  */
#define GPIOTE_CONFIG_OUT_TASK_HIGH                                                                \
    {                                                                                              \
        .init_state = NRF_GPIOTE_INITIAL_VALUE_LOW,                                                \
        .task_pin   = true,                                                                        \
        .action     = NRF_GPIOTE_POLARITY_LOTOHI,                                                  \
    }

/**@brief Macro for configuring a pin to use the GPIO OUT TASK to toggle the pin state.
 * @details The initial pin state must be provided.  */
#define GPIOTE_CONFIG_OUT_TASK_TOGGLE(init_high)                                                   \
    {                                                                                              \
        .init_state = init_high ? NRF_GPIOTE_INITIAL_VALUE_HIGH : NRF_GPIOTE_INITIAL_VALUE_LOW,    \
        .task_pin   = true,                                                                        \
        .action     = NRF_GPIOTE_POLARITY_TOGGLE,                                                  \
    }

/** @brief Pin. */
typedef uint32_t nrf_drv_gpiote_pin_t;

/**
 * @brief Pin event handler prototype.
 * @param pin    Pin that triggered this event.
 * @param action Action that lead to triggering this event.
 */
typedef void (*nrf_drv_gpiote_evt_handler_t)(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

/**
 * @brief Function for initializing the GPIOTE module.
 *
 * @details Only static configuration is supported to prevent the shared
 * resource being customized by the initiator.
 *
 * @retval    NRF_SUCCESS If initialization was successful.
 * @retval    NRF_ERROR_INVALID_STATE If the driver was already initialized.
 */
ret_code_t nrf_drv_gpiote_init(void);

/**
 * @brief Function for checking if the GPIOTE module is initialized.
 *
 * @details The GPIOTE module is a shared module. Therefore, you should check if
 * the module is already initialized and skip initialization if it is.
 *
 * @retval    true  If the module is already initialized.
 * @retval    false If the module is not initialized.
 */
bool nrf_drv_gpiote_is_init(void);

/**
 * @brief Function for uninitializing the GPIOTE module.
 */
void nrf_drv_gpiote_uninit(void);

/**
 * @brief Function for initializing a GPIOTE output pin.
 * @details The output pin can be controlled by the CPU or by PPI. The initial
 * configuration specifies which mode is used. If PPI mode is used, the driver
 * attempts to allocate one of the available GPIOTE channels. If no channel is
 * available, an error is returned.
 *
 * @param[in] pin       Pin.
 * @param[in] p_config  Initial configuration.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver is not initialized or the pin is already used.
 * @retval NRF_ERROR_NO_MEM        If no GPIOTE channel is available.
 */
ret_code_t nrf_drv_gpiote_out_init(nrf_drv_gpiote_pin_t pin,
                                   nrf_drv_gpiote_out_config_t const * p_config);

/**
 * @brief Function for uninitializing a GPIOTE output pin.
 * @details The driver frees the GPIOTE channel if the output pin was using one.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_uninit(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for setting a GPIOTE output pin.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_set(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for clearing a GPIOTE output pin.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_clear(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for toggling a GPIOTE output pin.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_toggle(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for enabling a GPIOTE output pin task.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_task_enable(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for disabling a GPIOTE output pin task.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_task_disable(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for getting the address of a configurable GPIOTE task.
 *
 * @param[in] pin       Pin.
 *
 * @return Address of OUT task.
 */
uint32_t nrf_drv_gpiote_out_task_addr_get(nrf_drv_gpiote_pin_t pin);

#if defined(GPIOTE_FEATURE_SET_PRESENT)
/**
 * @brief Function for getting the address of a configurable GPIOTE task.
 *
 * @param[in] pin       Pin.
 *
 * @return Address of SET task.
 */
uint32_t nrf_drv_gpiote_set_task_addr_get(nrf_drv_gpiote_pin_t pin);
#endif // defined(GPIOTE_FEATURE_SET_PRESENT)

#if defined(GPIOTE_FEATURE_CLR_PRESENT)
/**
 * @brief Function for getting the address of a configurable GPIOTE task.
 *
 * @param[in] pin       Pin.
 *
 * @return Address of CLR task.
 */
uint32_t nrf_drv_gpiote_clr_task_addr_get(nrf_drv_gpiote_pin_t pin);
#endif // defined(GPIOTE_FEATURE_CLR_PRESENT)

/**
 * @brief Function for initializing a GPIOTE input pin.
 * @details The input pin can act in two ways:
 * - lower accuracy but low power (high frequency clock not needed)
 * - higher accuracy (high frequency clock required)
 *
 * The initial configuration specifies which mode is used.
 * If high-accuracy mode is used, the driver attempts to allocate one
 * of the available GPIOTE channels. If no channel is
 * available, an error is returned.
 * In low accuracy mode SENSE feature is used. In this case only one active pin
 * can be detected at a time. It can be worked around by setting all of the used
 * low accuracy pins to toggle mode.
 * For more information about SENSE functionality, refer to Product Specification.
 *
 * @param[in] pin       Pin.
 * @param[in] p_config    Initial configuration.
 * @param[in] evt_handler User function to be called when the configured transition occurs.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_STATE If the driver is not initialized or the pin is already used.
 * @retval NRF_ERROR_NO_MEM        If no GPIOTE channel is available.
 */
ret_code_t nrf_drv_gpiote_in_init(nrf_drv_gpiote_pin_t pin,
                                  nrf_drv_gpiote_in_config_t const * p_config,
                                  nrf_drv_gpiote_evt_handler_t evt_handler);

/**
 * @brief Function for uninitializing a GPIOTE input pin.
 * @details The driver frees the GPIOTE channel if the input pin was using one.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_in_uninit(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for enabling sensing of a GPIOTE input pin.
 *
 * @details If the input pin is configured as high-accuracy pin, the function
 * enables an IN_EVENT. Otherwise, the function enables the GPIO sense mechanism.
 * Note that a PORT event is shared between multiple pins, therefore the
 * interrupt is always enabled.
 *
 * @param[in] pin       Pin.
 * @param[in] int_enable  True to enable the interrupt. Always valid for a high-accuracy pin.
 */
void nrf_drv_gpiote_in_event_enable(nrf_drv_gpiote_pin_t pin, bool int_enable);

/**
 * @brief Function for disabling a GPIOTE input pin.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_in_event_disable(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for checking if a GPIOTE input pin is set.
 *
 * @param[in] pin       Pin.
 * @retval    true If the input pin is set.
 * @retval    false If the input pin is not set.
 */
bool nrf_drv_gpiote_in_is_set(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for getting the address of a GPIOTE input pin event.
 * @details If the pin is configured to use low-accuracy mode, the address of the PORT event is returned.
 *
 * @param[in] pin       Pin.
 */
uint32_t nrf_drv_gpiote_in_event_addr_get(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for forcing a specific state on the pin configured as task.
 *
 * @param[in] pin       Pin.
 * @param[in] state     Pin state.
 */
void nrf_drv_gpiote_out_task_force(nrf_drv_gpiote_pin_t pin, uint8_t state);

/**
 * @brief Function for triggering the task OUT manually.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_out_task_trigger(nrf_drv_gpiote_pin_t pin);

#ifdef NRF52_SERIES
/**
 * @brief Function for triggering the task SET manually.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_set_task_trigger(nrf_drv_gpiote_pin_t pin);

/**
 * @brief Function for triggering the task CLR manually.
 *
 * @param[in] pin       Pin.
 */
void nrf_drv_gpiote_clr_task_trigger(nrf_drv_gpiote_pin_t pin);
#endif

/**
 *@}
 **/


#ifdef __cplusplus
}
#endif

#endif //NRF_DRV_GPIOTE__
