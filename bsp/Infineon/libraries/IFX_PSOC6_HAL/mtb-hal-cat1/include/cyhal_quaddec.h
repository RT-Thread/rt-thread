/***************************************************************************//**
* \file cyhal_quaddec.h
*
* \brief
* Provides a high level interface for interacting with the Quadrature Decoder.
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
* \addtogroup group_hal_quaddec Quadrature Decoder
* \ingroup group_hal
* \{
* High level interface for interacting with the Quadrature Decoder hardware resource.
*
* The quadrature decoder block is commonly used to measure the time of occurrence of an event,
* to measure the time difference between two events or perform an action after a specified
* period of time.
*
* The Quadrature Decoder block provides the ability to count transitions on a pair of digital
* signals. The signals are typically provided by a speed/position feedback system mounted on
* a motor or trackball. The driver allows the user to invoke a callback function when a
* particular event occurs.
* The signals, typically called A and B, are positioned 90Â° out-of-phase, which results in a Gray
* code output (a sequence where only one bit changes on each count). It also allows detection of
* direction and relative position. A third optional signal, named index, is used as a reference
* to establish an absolute position once per rotation.
*
* The Quadrature Decoder operates in one of three resolution modes.  (see \ref
* cyhal_quaddec_resolution_t)  The mode dictates the number of events that are counted.
*
* \image html quadrature_mode.png
*
* An index event causes the counter to be set to the midpoint.  For example, if the hardware
* has 16-bit resolution, the midpoint would be 0x8000.  For 32-bit resolution: 0x80000000.
*
* \image html quadrature_index.png
*
* For more details about this functionality, see the "Quadrature Decoder Mode" section of the
* Technical Reference Manual.
*
* Some use case scenarios of the Quadrature Decoder:
*
* * Decode the output of a quadrature encoder (e.g., mouse, trackball, robotic axles, etc.).
* * Precision measurement of speed, acceleration, and position of a motor's rotor and with rotary
* knobs to determine user input.
*
* \section subsection_quaddec_features Features
* * Configurable resolution - \ref cyhal_quaddec_resolution_t
* * Interrupt on various events - \ref cyhal_quaddec_event_t
*
* \section subsection_quaddec_quickstart Quick Start
*
* \ref cyhal_quaddec_init can be used for quadrature decoder initialization by providing the quaddec
* object - \ref cyhal_quaddec_t, input pins, and shared clock source - <b> clk </b> (optional).
*
*
* See \ref subsection_quaddec_snippet_1.
*
* \section subsection_quaddec_sample_snippets Code Snippets
*
* \subsection subsection_quaddec_snippet_1 Snippet 1: Initialization and direction detection
* The following snippet initializes a quadrature decoder and measures the counter to determine direction.
* The <b>clk</b> may be left NULL, in which case a clock resource is automatically assigned.
* \snippet hal_quaddec.c snippet_cyhal_quaddec_direction
*
* \subsection subsection_quaddec_snippet_2 Snippet 2: Handling an event in a callback function
* The following snippet initializes a quadrature decoder and triggers an event as changes happen.
* The <b>clk</b> need not be provided (NULL), in which case a clock resource is assigned.
* \snippet hal_quaddec.c snippet_cyhal_quaddec_event_interrupt
*
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_quaddec Quadrature Decoder HAL Results
 *  Quadrature Decoder specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bad argument. eg: null pointer */
#define CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QUADDEC, 0))
/** Failed to initialize the quadrature decoder clock */
#define CYHAL_QUADDEC_RSLT_ERR_CLOCK_INIT                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QUADDEC, 1))
/** The function is not supported with a particular device */
#define CYHAL_QUADDEC_RSLT_ERR_NOT_SUPPORTED              \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QUADDEC, 2))

/**
 * \}
 */

/*******************************************************************************
*       Enumerations
*******************************************************************************/

/** Operating resolutions for the quadrature decoder */
typedef enum
{
    CYHAL_QUADDEC_RESOLUTION_1X, //!< 1x resolution
    CYHAL_QUADDEC_RESOLUTION_2X, //!< 2x resolution
    CYHAL_QUADDEC_RESOLUTION_4X  //!< 4x resolution
} cyhal_quaddec_resolution_t;

/** Quadrature decoder input signal */
typedef enum
{
    CYHAL_QUADDEC_INPUT_PHI_A, //!< The "A" input of the quadrature decoder.
    CYHAL_QUADDEC_INPUT_PHI_B, //!< The "B" input of the quadrature decoder.
    CYHAL_QUADDEC_INPUT_STOP,  //!< Stops the counter from counting when activated.
    CYHAL_QUADDEC_INPUT_INDEX  //!< A reference signal that resets the counter when activated.
} cyhal_quaddec_input_t;

/** Quadrature decoder output signal */
typedef enum
{
    CYHAL_QUADDEC_OUTPUT_COMPARE_MATCH  //!< Compare Match signal
} cyhal_quaddec_output_t;

/** Interrupt triggers for the quadrature decoder */
typedef enum
{
    CYHAL_QUADDEC_IRQ_NONE            = 0,            //!< No interrupt handled
    CYHAL_QUADDEC_IRQ_TERMINAL_COUNT  = (1 << 0),     //!< Interrupt when terminal count is reached
    CYHAL_QUADDEC_IRQ_CAPTURE         = (1 << 1),     //!< Interrupt when capture value is reached
    CYHAL_QUADDEC_IRQ_ALL             = (1 << 2) - 1  //!< Interrupt on any event
} cyhal_quaddec_event_t;

/*******************************************************************************
*       Typedefs
*******************************************************************************/

/** Handler for quadrature decoder events */
typedef void(*cyhal_quaddec_event_callback_t)(void *callback_arg, cyhal_quaddec_event_t event);

/*******************************************************************************
*       Functions
*******************************************************************************/

/** Initialize the quadrature decoder peripheral and configure the pin. <br>
 * See \ref subsection_quaddec_snippet_1.
 *
 * @param[out] obj  Pointer to a quadrature decoder object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  phi_a - The "A" input of the quadrature decoder.
 * @param[in]  phi_b - The "B" input of the quadrature decoder.
 * @param[in]  index - Optional, resets the counter when active to act as a reference position
 *                     for the quadrature decoder.
 * @param[in]  resolution - The resolution that the quadrature decoder runs at
 * @param[in]  clk - Optional, the shared clock to use, if not provided a new clock will be
 *                   allocated and the quadrature decoder frequency will be set to the value passed
 *                   in with the frequency parameter.
 * @param[in]  frequency - This is the frequency, in hertz, to use with the clock allocated by this
 *                         function.  This parameter is only used if the clk parameter is set to NULL.
 *                         When the clk parameter is not NULL, this must be set to zero.  When the clk
 *                         paramether is NULL, this must be set to something other than zero.
 * @return The status of the init request
 */
cy_rslt_t cyhal_quaddec_init(cyhal_quaddec_t *obj, cyhal_gpio_t phi_a, cyhal_gpio_t phi_b,
                             cyhal_gpio_t index, cyhal_quaddec_resolution_t resolution,
                             const cyhal_clock_t *clk, uint32_t frequency);

/** Initialize the quadrature decoder peripheral using a configurator generated configuration struct
  *
 * @param[out] obj              Pointer to a quadrature decoder object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in] cfg               Configuration structure generated by a configurator.
 * @return The status of the init request
 */
 cy_rslt_t cyhal_quaddec_init_cfg(cyhal_quaddec_t *obj, const cyhal_quaddec_configurator_t *cfg);

/** Deinitialize the quadrature decoder object
 *
 * @param[in,out] obj The quadrature decoder object
 */
void cyhal_quaddec_free(cyhal_quaddec_t *obj);

/** Starts the quadrature decoder.  This function also acts as a reset, in that it will trigger
 * reload/index the QuadDec.  When this function is called, the count value gets stored in the
 * capture register and the count value is returned to the mid point. For example, if the hardware
 * has 16-bit resolution, the midpoint would be 0x8000.  For 32-bit resolution: 0x80000000.
 * See \ref subsection_quaddec_snippet_1.
 *
 * @param[in] obj     The quadrature decoder object
 * @return The status of the start request
 */
cy_rslt_t cyhal_quaddec_start(cyhal_quaddec_t *obj);

/** Stops the quadrature decoder. Does not reset counter value. <br>
 *
 * @param[in] obj     The quadrature decoder object
 * @return The status of the stop request
 */
cy_rslt_t cyhal_quaddec_stop(cyhal_quaddec_t *obj);

/** Gets the change in the quadrature decoder counter, either positive or negative, since the last
 * time that this function was called.
 *
 * \note This function is not intended for applications requiring high speed or high accuracy such
 * as getting motor positions.  It is intended for applications involving devices like radial dials.
 *
 * @param[in] obj     The quadrature decoder object
 * @return The amount that the counter has changed
 */
int32_t cyhal_quaddec_get_delta(cyhal_quaddec_t *obj);

/** Reads the current value from the quadrature decoder <br>
 * The read operation works even if the counter is stopped.
 * See \ref subsection_quaddec_snippet_1.
 *
 * @param[in] obj     The quadrature decoder object
 * @return The current value of the quadrature decoder counter register
 */
uint32_t cyhal_quaddec_read_counter(const cyhal_quaddec_t *obj);

/** Reads the value from the quadrature decoder's capture register <br>
 * This function does not clear the counter value.  The capture register
 * is updated whenever there is an index event.
 *
 * @param[in] obj     The quadrature decoder object
 * @return The current value of the quadrature decoder capture register
 */
uint32_t cyhal_quaddec_read_capture(const cyhal_quaddec_t *obj);

/** Register a quadrature decoder callback handler<br>
 * This function does not clear the counter value.
 *
 * This function will be called when one of the events enabled by \ref cyhal_quaddec_enable_event
 * occurs.
 *
 * See \ref subsection_quaddec_snippet_2.
 *
 * @param[in] obj          The quadrature decoder object
 * @param[in] callback     The callback handler which will be invoked when the event occurs
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_quaddec_register_callback(cyhal_quaddec_t *obj, cyhal_quaddec_event_callback_t callback,
                                     void *callback_arg);

/** Configure quadrature decoder event enable <br>
 *
 * When an enabled event occurs, the function specified by \ref cyhal_quaddec_register_callback
 * will be called.
 *
 * See \ref subsection_quaddec_snippet_2.
 *
 * @param[in] obj           The quadrature decoder object
 * @param[in] event         The quadrature decoder event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable        True to turn on interrupts, False to turn off
 */
void cyhal_quaddec_enable_event(cyhal_quaddec_t *obj, cyhal_quaddec_event_t event,
                                uint8_t intr_priority, bool enable);

/** Connects a source signal and configures and enables a quadrature decoder
 * event to be triggered from that signal. These quadrature decoder events can
 * be configured independently and connect to the same or different source
 * signals.
 * @note For "edge" signals, this function will default to rising edge. To control the edge type,
 * use @ref cyhal_quaddec_connect_digital2
 *
 * @param[in] obj      Quadrature decoder obj
 * @param[in] source   Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal   The quadrature decoder input signal
 * @return The status of the connection
 * */
cy_rslt_t cyhal_quaddec_connect_digital(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal);

/** Connects a source signal and configures and enables a quadrature decoder
 * event to be triggered from that signal with a configurable edge type.
 * These quadrature decoder events can be configured independently and connect
 * to the same or different source signals.
 *
 * @param[in] obj       Quadrature decoder obj
 * @param[in] source    Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal    The quadrature decoder input signal
 * @param[in] edge_type The edge type that should trigger the event. This must be consistent with the
 *                      edge type of `source`. If `source` produces a "level" signal, the only valid
 *                      value is @ref CYHAL_EDGE_TYPE_LEVEL. If `source` produces an "edge" signal, then
 *                      @ref CYHAL_EDGE_TYPE_LEVEL is not a valid value.
 * @return The status of the connection
 * */
cy_rslt_t cyhal_quaddec_connect_digital2(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal, cyhal_edge_type_t edge_type);

/** Disconnects a source signal and disables the quadrature decoder event.
 *
 * @param[in] obj      Quadrature decoder obj
 * @param[in] source   Source signal from cyhal_<PERIPH>_enable_output to disable
 * @param[in] signal   The quadrature decoder input signal
 * @return The status of the disconnection
 * */
cy_rslt_t cyhal_quaddec_disconnect_digital(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal);

/** Enables the specified output signal from a quadrature decoder that will be
 * triggered when the corresponding event occurs. Multiple output signals can
 * be configured simultaneously.
 *
 * @param[in]  obj      Quadrature decoder obj
 * @param[in]  signal   The quadrature decoder output signal
 * @param[out] source   Pointer to user-allocated source signal object which
 * will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t cyhal_quaddec_enable_output(cyhal_quaddec_t *obj, cyhal_quaddec_output_t signal, cyhal_source_t *source);

/** Disables the specified output signal from a quadrature decoder.
 *
 * @param[in]  obj      Quadrature decoder obj
 * @param[in]  signal   The quadrature decoder output signal
 * @return The status of the output disable
 * */
cy_rslt_t cyhal_quaddec_disable_output(cyhal_quaddec_t *obj, cyhal_quaddec_output_t signal);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_QUADDEC_IMPL_HEADER
#include CYHAL_QUADDEC_IMPL_HEADER
#endif /* CYHAL_QUADDEC_IMPL_HEADER */

/** \} group_hal_quaddec */
