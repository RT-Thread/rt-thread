/***************************************************************************//**
* \file cyhal_comp.h
*
* Provides a high level interface for interacting with the Infineon Analog Comparator.
* This interface abstracts out the chip specific details.
* If any chip specific functionality is required the low level functions can
* be used directly.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_hal_comp COMP (Analog Comparator)
* \ingroup group_hal
* \{
* High level interface for interacting with an analog Comparator.
*
* \section cyhal_comp_features Features
* The analog comparator measures one input voltage from the non-inverting pin against
* a second voltage provided on the inverting pin. The result of this comparison can
* be used in three ways:
* - Output to pin
* - Read state via firmware (see @ref cyhal_comp_read)
* - Event triggered on rising or falling edge (see @ref cyhal_comp_event_t)
*
* These three abilities can be used in any combination.
*
* \section cyhal_comp_quickstart Quickstart
* Call \ref cyhal_comp_init to initialize a comparator instance by providing the comparator
* object (**obj**), non-inverting input pin (**vin_p**), inverting input pin (**vin_m**), optional
* output pin (**output**), and configuration (**cfg**).
*
* Use \ref cyhal_comp_read to read the comparator state from firmware.
*
* Use \ref cyhal_comp_register_callback and \ref cyhal_comp_enable_event to configure a
* callback that will be invoked on a rising and/or falling edge of the comparator output.
*
* \section subsection_comp_snippets Code Snippets:
* \note Error checking is omitted for clarity
* \section subsection_comp_snippet_1 Snippet 1: Comparator initialization
* The following snippet initializes the comparator and powers it on
* \snippet hal_comp.c snippet_cyhal_comp_init
*
* \section subsection_comp_snippet_2 Snippet 2: Comparator read value
* The following snippet reads the current comparator value into a variable
* \snippet hal_comp.c snippet_cyhal_comp_read
*
* \section subsection_comp_snippet_3 Snippet 3: Comparator event registration
* The following snippet registers a callback that will be called on either a rising or falling
* edge of the comparator output.
* \snippet hal_comp.c snippet_cyhal_comp_event
*
* \section subsection_comp_snippet_4 Snippet 4: Comparator powering-off and on
* The following snippet demonstrates temporarily powering-off the comparator without freeing it.
* \snippet hal_comp.c snippet_cyhal_comp_start_stop
*
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cyhal_gpio.h"
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_comp Comparator HAL Results
 *  Comparator specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The requested pins are invalid */
#define CYHAL_COMP_RSLT_ERR_INVALID_PIN                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_COMP, 1))
/** Bad argument */
#define CYHAL_COMP_RSLT_ERR_BAD_ARGUMENT                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_COMP, 2))

/**
 * \}
 */

/** Comparator event types */
typedef enum
{
    CYHAL_COMP_RISING_EDGE      = 0x01,  //!< Rising edge on comparator output
    CYHAL_COMP_FALLING_EDGE     = 0x02,  //!< Falling edge on comparator output
} cyhal_comp_event_t;

/** Configuration options for the Comparator */
typedef struct
{
    /** Power mode the comparator should operate in. Lower modes save power but operate at lower speed. */
    cyhal_power_level_t power;
    /** Whether hysteresis should be used. See the implementation-specific documentation for the hysteresis value */
    bool hysteresis;
} cyhal_comp_config_t;

/**
  * Handler for Comparator events
  *
  * \note Not all hardware is capable of differentiating which type of edge triggered an
  * event when both rising and falling edges are enabled. If the edge cannot be determined,
  * the `event` argument will be `CYHAL_COMP_RISING_EDGE | CYHAL_COMP_FALLING_EDGE`
  */
typedef void (*cyhal_comp_event_callback_t)(void *callback_arg, cyhal_comp_event_t event);


/** Initialize the Comparator peripheral.
 *
 * @param[out] obj          Pointer to a Comparator object. The caller must allocate the memory
 *                            for this object but the init function will initialize its contents.
 * @param[in]  vin_p        Non-inverting input pin
 * @param[in]  vin_m        Inverting input pin
 * @param[in]  output       Comparator output pin. May be @ref NC.
 * @param[in]  cfg          Configuration structure
 * @return The status of the init request
 */
cy_rslt_t cyhal_comp_init(cyhal_comp_t *obj, cyhal_gpio_t vin_p, cyhal_gpio_t vin_m, cyhal_gpio_t output, cyhal_comp_config_t *cfg);

/** Initialize the comparator peripheral using a configurator generated configuration struct
  *
 * @param[out] obj              Pointer to a comparator object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in] cfg               Configuration structure generated by a configurator.
 * @return The status of the init request
 */
cy_rslt_t cyhal_comp_init_cfg(cyhal_comp_t *obj, const cyhal_comp_configurator_t *cfg);

/** Deinitialize the Comparator peripheral.
 *
 * @param[in] obj Comparator object
 */
void cyhal_comp_free(cyhal_comp_t *obj);

/** Changes the current operating power level of the comparator.
 *
 * If the power level is set to @ref CYHAL_POWER_LEVEL_OFF, the comparator will be powered-off
 * but it will retain its configuration, so it is not necessary to reconfigure it when changing
 * the power level from @ref CYHAL_POWER_LEVEL_OFF to any other value.
 *
 * @param[in] obj   Comparator object
 * @param[in] power The power level to set
 * @return The status of the set power request
 */
cy_rslt_t cyhal_comp_set_power(cyhal_comp_t *obj, cyhal_power_level_t power);

/** Reconfigure the Comparator.
 *
 * This retains the powered state of the comparator.
 * Depending on the implementation, it may be necessary to temporarily deconfigure and/or
 * power off the comparator in order to apply the new configuration. However, if the
 * comparator is powered-off when this function is called, it will remain powered-off after
 * it returns. Likewise, if the comparator is powered-on when this function is called,
 * it will remain powered-on after it returns.
 *
 * @param[in] obj  Comparator object
 * @param[in] cfg  New configuration to apply
 * @return The status of the configure request
 */
cy_rslt_t cyhal_comp_configure(cyhal_comp_t *obj, cyhal_comp_config_t *cfg);

/** Reads the Comparator state.
 *
 * @param[in]  obj    Comparator object
 * @return The Comparator state. True if the non-inverting pin voltage is greater than the
 * inverting pin voltage, false otherwise.
 */
bool cyhal_comp_read(cyhal_comp_t *obj);

/** Register/clear a callback handler for Comparator events
 *
 * This function will be called when one of the events enabled by \ref cyhal_comp_enable_event occurs.
 *
 * @param[in] obj          Comparator object
 * @param[in] callback     Function to call when the specified event happens
 * @param[in] callback_arg Generic argument that will be provided to the handler when called
 */
void cyhal_comp_register_callback(cyhal_comp_t *obj, cyhal_comp_event_callback_t callback, void *callback_arg);

/** Enable or Disable a Comparator event
 *
 * When an enabled event occurs, the function specified by \ref cyhal_comp_register_callback will be called.
 *
 * @param[in] obj            Comparator object
 * @param[in] event          Comparator event
 * @param[in] intr_priority  Priority for NVIC interrupt events
 * @param[in] enable         True to turn on event, False to turn off
 */
void cyhal_comp_enable_event(cyhal_comp_t *obj, cyhal_comp_event_t event, uint8_t intr_priority, bool enable);


#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_COMP_IMPL_HEADER
#include CYHAL_COMP_IMPL_HEADER
#endif /* CYHAL_COMP_IMPL_HEADER */

/** \} group_hal_comp */
