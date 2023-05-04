/***************************************************************************//**
* \file cyhal_timer.h
*
* \brief
* Provides a high level interface for interacting with the Infineon Timer/Counter.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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
* \addtogroup group_hal_timer Timer (Timer/Counter)
* \ingroup group_hal
* \{
* High level interface for interacting with the Timer/Counter hardware resource.
*
* The timer block is commonly used to measure the time of occurrence of an event,
* to measure the time difference between two events or perform an action after
* a specified period of time. The driver also allows the user to invoke a callback function
* when a particular event occurs.
*
* Some use case scenarios of timer -
*
* * Creating a periodic interrupt for executing periodic tasks
* * Measuring time between two events
* * Triggering other system resources after a certain number of events
* * Capturing time stamps when events occur
*
* \section subsection_timer_features Features
* * Runtime configurable parameters like period and compare value - \ref cyhal_timer_cfg_t
* * Configurable counting direction - \ref cyhal_timer_direction_t
* * Interrupt on various events - \ref cyhal_timer_event_t
* * Continuous or One Shot run modes
*
* \section subsection_timer_quickstart Quick Start
*
* \ref cyhal_timer_init can be used for timer initialization by providing the timer object - \ref cyhal_timer_t,
* and shared clock source - <b> clk </b> (optional). The timer parameters needs to be populated in \ref cyhal_timer_cfg_t structure.
* The timer then needs to be configured by using the \ref cyhal_timer_configure function.
*
* \note A default frequency is set when an existing clock divider - <b> clk </b> is not provided to \ref cyhal_timer_init which is
* defined by the macro - \ref CYHAL_TIMER_DEFAULT_FREQ.
*
* \warning Currently there is no support for pin connections to Timer using this driver. So, the <b> pin </b> should be
* assigned as \ref NC while using the \ref cyhal_timer_init to initialize the timer.
*
*
* See \ref subsection_timer_snippet_1.
*
* \section subsection_timer_sample_snippets Code Snippets
*
* \subsection subsection_timer_snippet_1 Snippet 1: Measuring time of an operation
* The following snippet initializes a Timer and measures the time between two events.
* The <b>clk</b> need not be provided, in which case a clock resource is assigned.
* \snippet hal_timer.c snippet_cyhal_timer_event_measure
*
* \subsection subsection_timer_snippet_2 Snippet 2: Handling an event in a callback function
* The following snippet initializes a Timer and triggers an event after every one second.
* The <b>clk</b> need not be provided (NULL), in which case a clock resource is assigned.
* \snippet hal_timer.c snippet_cyhal_timer_event_interrupt
*
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"
#if defined(COMPONENT_CAT5)
#include "cyhal_t2timer.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_timer Timer HAL Results
 *  Timer specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bad argument. eg: null pointer */
#define CYHAL_TIMER_RSLT_ERR_BAD_ARGUMENT               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TIMER, 0))
/** Failed to initialize Timer clock */
#define CYHAL_TIMER_RSLT_ERR_CLOCK_INIT                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TIMER, 1))
/** Failed to initialize Timer */
#define CYHAL_TIMER_RSLT_ERR_INIT                       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TIMER, 2))
/** Cannot change the timer frequency when a shared clock divider is in use */
#define CYHAL_TIMER_RSLT_ERR_SHARED_CLOCK               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TIMER, 3))
/** Feature unsupported with this Timer */
#define CYHAL_TIMER_RSLT_ERR_UNSUPPORTED                \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TIMER, 4))

/**
 * \}
 */

/*******************************************************************************
*       Enumerations
*******************************************************************************/

/** Timer directions */
typedef enum
{
    CYHAL_TIMER_DIR_UP, //!< Counts up
    CYHAL_TIMER_DIR_DOWN, //!< Counts down
    CYHAL_TIMER_DIR_UP_DOWN, //!< Counts up and down, terminal count occurs on both overflow and underflow.
} cyhal_timer_direction_t;

/** Timer/counter interrupt triggers */
typedef enum {
    CYHAL_TIMER_IRQ_NONE            =  0, /**< No interrupt handled **/
    CYHAL_TIMER_IRQ_TERMINAL_COUNT  =  1 << 0, /**< Interrupt when terminal count is reached **/
    CYHAL_TIMER_IRQ_CAPTURE_COMPARE =  1 << 1, /**< Interrupt when Compare/Capture value is reached **/
    CYHAL_TIMER_IRQ_ALL             = (1 << 2) - 1, /**< Interrupt on terminal count and Compare/Capture values **/
} cyhal_timer_event_t;

/** Timer/counter input signal */
typedef enum
{
    CYHAL_TIMER_INPUT_START,    //!< Start signal
    CYHAL_TIMER_INPUT_STOP,     //!< Stop signal
    CYHAL_TIMER_INPUT_RELOAD,   //!< Reload signal
    CYHAL_TIMER_INPUT_COUNT,    //!< Count signal
    CYHAL_TIMER_INPUT_CAPTURE,  //!< Capture signal
} cyhal_timer_input_t;

/** Timer/counter output signal */
typedef enum
{
    CYHAL_TIMER_OUTPUT_OVERFLOW,       //!< Overflow signal
    CYHAL_TIMER_OUTPUT_UNDERFLOW,      //!< Underflow signal
    CYHAL_TIMER_OUTPUT_COMPARE_MATCH,  //!< Compare Match signal
    CYHAL_TIMER_OUTPUT_TERMINAL_COUNT, //!< Terminal count signal (logical OR of overflow and underflow signal)
} cyhal_timer_output_t;

/*******************************************************************************
*       Data Structures
*******************************************************************************/

/** @brief Describes the current configuration of a timer/counter */
typedef struct
{
    /**
      * Whether the timer is set to continuously run.
      * If true, the timer will run forever.
      * Otherwise, the timer will run once and stop (one shot).
      */
    bool is_continuous; //!< Whether the timer/counter operates continuous (true) or one shot (false)
    cyhal_timer_direction_t direction; //!< Direction the timer/counter is running
    bool is_compare; //!< Is it in compare (true) or capture (false) mode
    uint32_t period; //!< Timer/counter period
    uint32_t compare_value; //!< Timer/counter comparison value
    uint32_t value; //!< Default value of the timer/counter. \ref cyhal_timer_reset() will also change counter to this value when called.
} cyhal_timer_cfg_t;

/*******************************************************************************
*       Typedefs
*******************************************************************************/

/** Handler for timer events */
typedef void(*cyhal_timer_event_callback_t)(void *callback_arg, cyhal_timer_event_t event);

/*******************************************************************************
*       Defines
*******************************************************************************/

/** Default timer frequency, used when an existing clock divider is not provided to \ref cyhal_timer_init() */
#define CYHAL_TIMER_DEFAULT_FREQ (1000000u)

/*******************************************************************************
*       Functions
*******************************************************************************/

/** Initialize the timer/counter peripheral and configure the pin. <br>
 * See \ref subsection_timer_snippet_1.
 *
 * @param[out] obj  Pointer to a timer/counter object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  pin optional - The timer/counter compare/capture pin to initialize
 * @param[in]  clk optional - The shared clock to use, if not provided a new clock will be allocated
 *                  and the timer frequency will be set to \ref CYHAL_TIMER_DEFAULT_FREQ
 * @return The status of the init request
 */
cy_rslt_t cyhal_timer_init(cyhal_timer_t *obj, cyhal_gpio_t pin, const cyhal_clock_t *clk);

/** Initialize the Timer peripheral using a configurator generated configuration struct
  *
 * @param[out] obj              Pointer to a Timer object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in] cfg               Configuration structure generated by a configurator.
 * @return The status of the init request
 */
 cy_rslt_t cyhal_timer_init_cfg(cyhal_timer_t *obj, const cyhal_timer_configurator_t *cfg);

/** Deinitialize the timer/counter object
 *
 * @param[in,out] obj The timer/counter object
 */
void cyhal_timer_free(cyhal_timer_t *obj);

/** Updates the configuration and counter value of the timer/counter object. <br>
 * This function may temporary stop the timer if it is currently running.
 * See \ref subsection_timer_snippet_1.
 * @param[in] obj  The timer/counter object
 * @param[in] cfg  The configuration of the timer/counter
 * @return The status of the configure request
 */
cy_rslt_t cyhal_timer_configure(cyhal_timer_t *obj, const cyhal_timer_cfg_t *cfg);

/** Configures the timer frequency.
 * \note This is only valid to call if a null clock divider was provided to \ref cyhal_timer_init.
 * If a custom clock was provided its frequency should be adjusted directly.
 *
 * See \ref subsection_timer_snippet_1.
 * @param[in] obj  The timer/counter object
 * @param[in] hz   The frequency rate in Hz
 * @return The status of the set_frequency request
 */
cy_rslt_t cyhal_timer_set_frequency(cyhal_timer_t *obj, uint32_t hz);

/** Starts the timer/counter with the pre-set configuration from \ref cyhal_timer_configure.
 * This does not reset the counter. The count value will start from the value that was
 * set by the last operation to modify it. See \ref cyhal_timer_configure, and \ref
 * cyhal_timer_reset for how the value can be changed. If none of these functions have
 * been called, it will start from 0.<br>
 * See \ref subsection_timer_snippet_1.
 *
 * @param[in] obj     The timer/counter object
 * @return The status of the start request
 */
cy_rslt_t cyhal_timer_start(cyhal_timer_t *obj);

/** Stops the timer/counter. Does not reset counter value. <br>
 *
 * @param[in] obj     The timer/counter object
 * @return The status of the stop request
 */
cy_rslt_t cyhal_timer_stop(cyhal_timer_t *obj);

/** Reset the timer/counter value to the default value set from \ref cyhal_timer_configure.
 * If \ref cyhal_timer_configure was never called, this will reset timer/counter value to 0.
 * This function may temporary stop the timer. <br>
 *
 * @param[in] obj     The timer/counter object
 * @return The status of the reset request
 */
cy_rslt_t cyhal_timer_reset(cyhal_timer_t *obj);

/** Reads the current value from the timer/counter <br>
 * See \ref subsection_timer_snippet_1.
 *
 * @param[in] obj     The timer/counter object
 * @return The current value of the timer/counter
 */
uint32_t cyhal_timer_read(const cyhal_timer_t *obj);

/** Register a timer/counter callback handler<br>
 *
 * This function will be called when one of the events enabled by \ref cyhal_timer_enable_event occurs.
 *
 * See \ref subsection_timer_snippet_2.
 *
 * @param[in] obj          The timer/counter object
 * @param[in] callback     The callback handler which will be invoked when the event occurs
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_timer_register_callback(cyhal_timer_t *obj, cyhal_timer_event_callback_t callback, void *callback_arg);

/** Configure timer/counter event enablement <br>
 *
 * When an enabled event occurs, the function specified by \ref cyhal_timer_register_callback will be called.
 *
 * See \ref subsection_timer_snippet_2.
 *
 * @param[in] obj           The timer/counter object
 * @param[in] event         The timer/counter event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable        True to turn on interrupts, False to turn off
 */
void cyhal_timer_enable_event(cyhal_timer_t *obj, cyhal_timer_event_t event, uint8_t intr_priority, bool enable);

/** Connects a source signal and configures and enables a timer event to be
 * triggered from that signal. These timer events can be configured
 * independently and connect to the same or different source signals.
 * @note For "edge" signals, this function will default to rising edge. To control the edge type,
 * use @ref cyhal_timer_connect_digital2
 *
 * @param[in] obj      Timer obj
 * @param[in] source   Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal   The timer input signal
 * @return The current status of the connection
 * */
cy_rslt_t cyhal_timer_connect_digital(cyhal_timer_t *obj, cyhal_source_t source, cyhal_timer_input_t signal);

/** Connects a source signal and configures and enables a timer event to be
 * triggered from that signal with a configurable edge type. These timer events
 * can be configured independently and connect to the same or different source signals.
 *
 * @param[in] obj       Timer obj
 * @param[in] source    Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal    The timer input signal
 * @param[in] edge_type The edge type that should trigger the event. This must be consistent with the
 *                      edge type of `source`. If `source` produces a "level" signal, the only valid
 *                      value is @ref CYHAL_EDGE_TYPE_LEVEL. If `source` produces an "edge" signal, then
 *                      @ref CYHAL_EDGE_TYPE_LEVEL is not a valid value.
 * @return The current status of the connection
 * */
cy_rslt_t cyhal_timer_connect_digital2(cyhal_timer_t *obj, cyhal_source_t source, cyhal_timer_input_t signal, cyhal_edge_type_t edge_type);

/** Enables the specified output signal from a tcpwm that will be triggered
 * when the corresponding event occurs. Multiple output signals can be
 * configured simultaneously.
 *
 * @param[in]  obj      Timer obj
 * @param[in]  signal   The timer output signal
 * @param[out] source   Pointer to user-allocated source signal object which
 * will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The current status of the output enable
 * */
cy_rslt_t cyhal_timer_enable_output(cyhal_timer_t *obj, cyhal_timer_output_t signal, cyhal_source_t *source);

/** Disconnects a source signal and disables the timer event.
 *
 * @param[in] obj      Timer obj
 * @param[in] source   Source signal from cyhal_<PERIPH>_enable_output to disable
 * @param[in] signal   The timer input signal
 * @return The status of the disconnection
 * */
cy_rslt_t cyhal_timer_disconnect_digital(cyhal_timer_t *obj, cyhal_source_t source, cyhal_timer_input_t signal);

/** Disables the specified output signal from a timer.
 *
 * @param[in]  obj      Timer obj
 * @param[in]  signal   The timer output signal
 * @return The status of the output disable
 * */
cy_rslt_t cyhal_timer_disable_output(cyhal_timer_t *obj, cyhal_timer_output_t signal);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_TIMER_IMPL_HEADER
#include CYHAL_TIMER_IMPL_HEADER
#endif /* CYHAL_TIMER_IMPL_HEADER */

/** \} group_hal_timer */
