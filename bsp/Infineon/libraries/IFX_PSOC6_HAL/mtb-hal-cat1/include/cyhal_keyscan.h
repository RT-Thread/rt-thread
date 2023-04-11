/***************************************************************************//**
* \file cyhal_keyscan.h
*
* \brief
* Provides a high level interface for interacting with the Infineon KeyScan.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2020-2022 Cypress Semiconductor Corporation (an Infineon company) or
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
* \addtogroup group_hal_keyscan Keyscan
* \ingroup group_hal
* \{
* High level interface for interacting with the KeyScan
*
* The KeyScan driver monitors a key matrix for actions and provides keycodes
* to the application for processing.
*
* \section section_keyscan_features Features
* * Configurable number of rows and columns
* * Detection of  press, double press, triple press, and release actions
* * Buffering of multiple key actions without application intervention
* * Configurable callback for event-driven response to key actions
*
* See the implementation-specific documentation for information about device-specific
* limits on row count, column count, and buffer depth.
*
* \section section_keyscan_quickstart Quick Start
* Initialize a KeyScan instance using @ref cyhal_keyscan_init, providing the pins that should
* be used for the rows and columns of the key matrix. Use @ref cyhal_keyscan_read to read
* key actions.
*
* See @ref subsection_keyscan_snippet_1 for an example initialization.
* \note The clock parameter (const \ref cyhal_clock_t *clk) is optional and can be set to
* NULL to automatically configure and use an available clock resource with a default frequency.
*
* \section section_keyscan_snippets Code Snippets
* \note Error handling is omitted for clarity
* \subsection subsection_keyscan_snippet_1 Snippet 1: KeyScan initialization
* This snippet initializes a KeyScan resource to scan a matrix of pins.
*
* \snippet hal_keyscan.c snippet_cyhal_keyscan_init
*
* \subsection subsection_keyscan_snippet_2 Snippet 2: Polling
* This snippet illustrates periodic polling for key actions
*
* \snippet hal_keyscan.c snippet_cyhal_keyscan_poll
*
* \subsection subsection_keyscan_snippet_3 Snippet 3: Event Handling
* This snippet shows how to register a callback which is invoked when a key action occurs.
*
* \snippet hal_keyscan.c snippet_cyhal_keyscan_event
*/

#pragma once

#include "cyhal_hw_types.h"
#include "cyhal_gpio.h"
#include "cy_result.h"
#include "cyhal_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** An invalid pin location was specified */
#define CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN        \
  (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_KEYSCAN, 0))

/** An invalid argument was provided */
#define CYHAL_KEYSCAN_RSLT_ERR_INVALID_ARG        \
  (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_KEYSCAN, 1))

/** Initialization of the KeyScan hardware failed */
#define CYHAL_KEYSCAN_RSLT_ERR_INIT_FAILED        \
  (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_KEYSCAN, 2))

/** KeyScan events */
typedef enum {
    CYHAL_KEYSCAN_EVENT_NONE            = 0, //!< No interrupt
    CYHAL_KEYSCAN_EVENT_ACTION_DETECTED = 1 << 0, //!< Key action detected
    CYHAL_KEYSCAN_EVENT_BUFFER_FULL     = 1 << 1, //!< Keycode buffer is full
} cyhal_keyscan_event_t;

/** Key action types */
typedef enum {
    CYHAL_KEYSCAN_ACTION_PRESS,        //<! The key was pressed
    CYHAL_KEYSCAN_ACTION_RELEASE,      //<! The key was released
} cyhal_keyscan_action_type_t;

/** Key action description */
typedef struct {
    /** Code indicating which key the action applies to. Keycodes are assigned sequentially in column
      * order. For example, in a key matrix with five rows and two columns, column 0 would be represented
      * by keycode 0 - 4, and column 1 by keycode 5-9.
      */
    uint8_t keycode;
    /** The type of key action that was performd */
    cyhal_keyscan_action_type_t action;
} cyhal_keyscan_action_t;

/** Handler for KeyScan event callbacks */
typedef void (*cyhal_keyscan_event_callback_t)(void *callback_arg, cyhal_keyscan_event_t event);

/** Initialize the KeyScan peripheral.
 *
 * @param[out] obj          Pointer to a KeyScan object. The caller must allocate the memory
 *                          for this object but the init function will initialize its contents.
 * @param[in]  num_rows     The number of rows in the key matrix
 * @param[in]  rows         Array of pins corresponding to the key matrix rows
 * @param[in]  num_columns  The number of columns in the key matrix
 * @param[in]  columns      Array of pins corresponding to the key matrix columns
 * @param[in]  clock        Clock source to use for this instance. If NULL, a dedicated clock
 *                          will be automatically allocated for this instance.
 * @return The status of the init request
 */
cy_rslt_t cyhal_keyscan_init(cyhal_keyscan_t *obj, uint8_t num_rows, const cyhal_gpio_t *rows,
                                uint8_t num_columns, const cyhal_gpio_t *columns, const cyhal_clock_t *clock);

/** Deinitialize the KeyScan object and release the associated hardware resources.
 *
 * @param[in] obj  The KeyScan object
 */
void cyhal_keyscan_free(cyhal_keyscan_t *obj);

/** Reads up to the specified number of key actions.
  *
  * \note If an error code is returned, this function will contain partial information up to the number of keys read.
  *
  * @param[in]      obj     The KeyScan object
  * @param[in,out]  count   The number of key action to read. Updated with the number of keys actually read.
  * @param[out]     keys    The array into which key action descriptions should be written, starting from the
  *                         least recent key action at index 0.
  * @return The status of the read request
  */
cy_rslt_t cyhal_keyscan_read(cyhal_keyscan_t *obj, uint8_t* count, cyhal_keyscan_action_t* keys);

/** Register a keyscan callback handler.
 *
 * This function will be called when one of the events enabled by @ref cyhal_keyscan_enable_event occurs.
 *
 * @param[in] obj          The KeyScan object
 * @param[in] callback     The callback handler which will be invoked when the event occurs
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_keyscan_register_callback(cyhal_keyscan_t *obj, cyhal_keyscan_event_callback_t callback, void *callback_arg);

/** Configure KeyScan events.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_keyscan_register_callback will be called.
 *
 * @param[in] obj            The KeyScan object
 * @param[in] event          The KeyScan event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on the specified event, False to turn off
 */
void cyhal_keyscan_enable_event(cyhal_keyscan_t *obj, cyhal_keyscan_event_t event, uint8_t intr_priority, bool enable);

/** Initialize the KeyScan peripheral using a configurator generated configuration struct.
 *
 * @param[in]  obj                  Pointer to a KeyScan object. The caller must allocate the memory
 *                                  for this object but the init function will initialize its contents.
 * @param[in]  cfg                  Configuration structure generated by a configurator.
 * @return The status of the operation
 */
cy_rslt_t cyhal_keyscan_init_cfg(cyhal_keyscan_t *obj, const cyhal_keyscan_configurator_t *cfg);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_KEYSCAN_IMPL_HEADER
#include CYHAL_KEYSCAN_IMPL_HEADER
#endif /* CYHAL_KEYSCAN_IMPL_HEADER */

/** \} group_hal_keyscan */

