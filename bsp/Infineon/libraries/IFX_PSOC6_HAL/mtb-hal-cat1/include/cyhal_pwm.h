/***************************************************************************//**
* \file cyhal_pwm.h
*
* \brief
* Provides a high level interface for interacting with the Infineon PWM.
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
* \addtogroup group_hal_pwm PWM (Pulse Width Modulator)
* \ingroup group_hal
* \{
 * High level interface for interacting with the pulse width modulator (PWM) hardware resource
 *
 * The PWM driver can be used to generate periodic digital waveforms with configurable frequency and duty cycle.
 * The driver allows assigning the PWM output and an optional inverted output to supplied pins.
 * The driver supports interrupt generation on PWM terminal count and compare events.
 *
 * \section section_pwm_features Features
 * * Configurable pin assignment for the PWM output
 * * Optional complementary (inverted) PWM output to a second pin
 * * Configurable dead time between normal and inverted PWM outputs
 * * Configurable alignment: left, right or center
 * * Continuous or One-shot operation
 * * Option to instantiate and use a new clock or use pre-allocated clock for clock input
 * * Configurable interrupt and callback assignment on PWM events: terminal count, compare match or combination of both
 *
 * \section section_pwm_quickstart Quick Start
 *
 * See \ref subsection_pwm_snippet_1 for a code snippet that generates a signal with the specified frequency and duty cycle on the specified pin.
 *
 * \section section_pwm_snippets Code snippets
 *
 * \subsection subsection_pwm_snippet_1 Snippet 1: Simple PWM initialization and output to pin
 * The following snippet initializes a PWM resource and assigns the output to the supplied <b>pin</b> using \ref cyhal_pwm_init. <br>
 * The clock parameter <b>clk</b> is optional and need not be provided (NULL), to generate and use an available clock resource with a default frequency. <br>
 * The clock frequency and the duty cycle is set using \ref cyhal_pwm_set_duty_cycle. <br>
 * \ref cyhal_pwm_start starts the PWM output on the pin.
 *
 * \snippet hal_pwm.c snippet_cyhal_pwm_simple_init
 *
 *
 * \subsection subsection_pwm_snippet_2 Snippet 2: Starting and stopping the PWM output
 * \ref cyhal_pwm_start and \ref cyhal_pwm_stop functions can be used after PWM initialization to start and stop the PWM output.
 *
 * \snippet hal_pwm.c snippet_cyhal_pwm_start_stop
 *
 *
 * \subsection subsection_pwm_snippet_3 Snippet 3: Advanced PWM output to pin
 * \ref cyhal_pwm_init_adv can be used to specify advanced PWM options like an additional inverted PWM output, pulse alignment
 * (left, right, center) and run mode (one-shot or continuous). The following snippet initializes a left-aligned, continuous running PWM
 * assigned to the supplied pin. The inverted output is assigned to a second pin (<b>compl_pin</b>).
 *
 * \snippet hal_pwm.c snippet_cyhal_pwm_adv_init
 *
 *
 * \subsection subsection_pwm_snippet_4 Snippet 4: Interrupts on PWM events
 * PWM events like hitting the terminal count or a compare event can be used to trigger a callback function. <br>
 * \ref cyhal_pwm_enable_event() can be used to enable one or more events to trigger the callback function.
 *
 * \snippet hal_pwm.c snippet_cyhal_pwm_events
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_pwm PWM HAL Results
 *  PWM specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bad argument */
#define CYHAL_PWM_RSLT_BAD_ARGUMENT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_PWM, 0))
/** Failed to initialize PWM clock */
#define CYHAL_PWM_RSLT_FAILED_CLOCK_INIT                \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_PWM, 1))
/** Failed to initialize PWM */
#define CYHAL_PWM_RSLT_FAILED_INIT                      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_PWM, 2))

/**
 * \}
 */

/** Initialize the PWM out peripheral and configure the pin
 * This is similar to the \ref cyhal_pwm_init_adv() but uses defaults for some of the
 * more advanced setup options. See \ref subsection_pwm_snippet_1.
 *
 * @param[out] obj  Pointer to a PWM object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  pin  The PWM pin to initialize. This pin is required, it cannot be \ref NC (No Connect).
 * @param[in]  clk  An optional, pre-allocated clock to use, if NULL a new clock will be allocated
 * @return The status of the init request.
 */
#define cyhal_pwm_init(obj, pin, clk) (cyhal_pwm_init_adv(obj, pin, NC, CYHAL_PWM_LEFT_ALIGN, true, 0u, false, clk))

/** PWM interrupt triggers */
typedef enum {
    CYHAL_PWM_IRQ_NONE            =  0,             /**< No interrupts */
    CYHAL_PWM_IRQ_TERMINAL_COUNT  =  1 << 0,        /**< Interrupt on terminal count match event */
    CYHAL_PWM_IRQ_COMPARE         =  1 << 1,        /**< Interrupt on compare match event */
    CYHAL_PWM_IRQ_ALL             = (1 << 2) - 1,   /**< Interrupt on any events */

/** \cond INTERNAL */
    CYHAL_PWM_IRQ_CAPTURE_COMPARE /* __attribute__ ((deprecated)) */ = CYHAL_PWM_IRQ_COMPARE,
/** \endcond */
} cyhal_pwm_event_t;

/** PWM alignment */
typedef enum {
    CYHAL_PWM_LEFT_ALIGN       = 0, /**< PWM is left aligned (signal starts high and goes low after compare match) */
    CYHAL_PWM_RIGHT_ALIGN      = 1, /**< PWM is right aligned (signal starts low and goes high after compare match) */
    CYHAL_PWM_CENTER_ALIGN     = 2, /**< PWM is centered aligned (signal starts and ends low with a center aligned pulse) */
} cyhal_pwm_alignment_t;

/** PWM input signal */
typedef enum
{
    CYHAL_PWM_INPUT_START,    //!< Start signal
    CYHAL_PWM_INPUT_STOP,     //!< Stop signal
    CYHAL_PWM_INPUT_RELOAD,   //!< Reload signal
    CYHAL_PWM_INPUT_COUNT,    //!< Count signal
    CYHAL_PWM_INPUT_CAPTURE,  //!< Capture/swap signal
} cyhal_pwm_input_t;

/** PWM output signal */
typedef enum
{
    CYHAL_PWM_OUTPUT_OVERFLOW,      //!< Overflow signal
    CYHAL_PWM_OUTPUT_UNDERFLOW,     //!< Underflow signal
    CYHAL_PWM_OUTPUT_COMPARE_MATCH, //!< Compare Match signal
    CYHAL_PWM_OUTPUT_LINE_OUT,      //!< PWM line out signal
} cyhal_pwm_output_t;

/** Handler for PWM interrupts */
typedef void(*cyhal_pwm_event_callback_t)(void *callback_arg, cyhal_pwm_event_t event);

/** Initialize the PWM out peripheral and configure the pin.
 * This is similar to the \ref cyhal_pwm_init() but provides additional setup options. <br>
 * See \ref subsection_pwm_snippet_3.
 *
 * @param[out] obj              Pointer to a PWM object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in]  pin              The PWM pin to initialize. This pin is required, it cannot be \ref NC (No Connect).
 * @param[in]  compl_pin        An optional, additional inverted output pin. <br>
 *                              If supplied, this must be connected to the same or related PWM instance as <b>pin</b>, see
 *                              \ref section_hal_impl_pwm_compl_pins for details.<br>
 *                              If this output is not needed, use \ref NC (No Connect).
 * @param[in]  pwm_alignment    PWM alignment: left, right, or center.
 * @param[in]  continuous       PWM run type: continuous (true) or one shot (false).
 * @param[in]  dead_time_us     The number of micro-seconds for dead time. This is
 * only meaningful if both <b>pin</b> and <b>compl_pin</b> are provided.
 * @param[in]  invert           An option for the user to invert the PWM output
 * @param[in]  clk              An optional, pre-allocated clock to use, if NULL a
 * new clock will be allocated.
 * @return The status of the init request
 *
 * @note In some cases, it is possible to use a pin designated for non-inverting output as an inverting output and vice versa. Whether this is possible is dependent on the HAL implementation and operating mode. See the implementation specific documentation for details.
 */
cy_rslt_t cyhal_pwm_init_adv(cyhal_pwm_t *obj, cyhal_gpio_t pin, cyhal_gpio_t compl_pin, cyhal_pwm_alignment_t pwm_alignment, bool continuous, uint32_t dead_time_us, bool invert, const cyhal_clock_t *clk);

/** Initialize the PWM out peripheral using a configurator generated configuration struct
  *
 * @param[out] obj              Pointer to a PWM object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in] cfg               Configuration structure generated by a configurator.
 * @return The status of the init request
 */
 cy_rslt_t cyhal_pwm_init_cfg(cyhal_pwm_t *obj, const cyhal_pwm_configurator_t *cfg);

/** Deinitialize the PWM object
 *
 * @param[in,out] obj The PWM object
 */
void cyhal_pwm_free(cyhal_pwm_t *obj);

/** Set the number of microseconds for the PWM period & pulse width
 *
 * @param[in] obj            The PWM object
 * @param[in] period_us      The period in microseconds
 * @param[in] pulse_width_us The pulse width in microseconds
 * @return The status of the period request
 */
cy_rslt_t cyhal_pwm_set_period(cyhal_pwm_t *obj, uint32_t period_us, uint32_t pulse_width_us);

/** Set the PWM duty cycle and frequency
 *
 * @param[in] obj             The PWM object
 * @param[in] duty_cycle      The percentage of time the output is high (0 - 100%)
 * @param[in] frequencyhal_hz The frequency of the PWM in Hz
 * @return                    The status of the duty cycle request
 */
cy_rslt_t cyhal_pwm_set_duty_cycle(cyhal_pwm_t *obj, float duty_cycle, uint32_t frequencyhal_hz);

/** Starts the PWM generation and outputs on <b>pin</b> and <b>compl_pin</b>.
 *
 * @param[in] obj           The PWM object
 * @return                  The status of the start request
 */
cy_rslt_t cyhal_pwm_start(cyhal_pwm_t *obj);

/** Stops the PWM generation and outputs on <b>pin</b> and <b>compl_pin</b>.
 *
 * @param[in] obj          The PWM object
 * @return                 The status of the stop request
 */
cy_rslt_t cyhal_pwm_stop(cyhal_pwm_t *obj);

/** Register a PWM interrupt handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_pwm_enable_event occurs.
 *
 * @param[in] obj          The PWM object
 * @param[in] callback     The callback handler which will be invoked when the event occurs
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_pwm_register_callback(cyhal_pwm_t *obj, cyhal_pwm_event_callback_t callback, void *callback_arg);

/** Configure PWM event enablement.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_pwm_register_callback will be called.
 *
 * @param[in] obj            The PWM object
 * @param[in] event          The PWM event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on events, False to turn off
 */
void cyhal_pwm_enable_event(cyhal_pwm_t *obj, cyhal_pwm_event_t event, uint8_t intr_priority, bool enable);

/** Connects a source signal and configures and enables a PWM event to be
 * triggered from that signal. These PWM events can be configured
 * independently and connect to the same or different source signals.
 * @note For "edge" signals, this function will default to rising edge. To control the edge type,
 * use @ref cyhal_pwm_connect_digital2
 *
 * @param[in] obj      PWM obj
 * @param[in] source   Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal   The PWM input signal
 * @return The status of the connection
 * */
cy_rslt_t cyhal_pwm_connect_digital(cyhal_pwm_t *obj, cyhal_source_t source, cyhal_pwm_input_t signal);

/** Connects a source signal and configures and enables a PWM event to be
 * triggered from that signal with a configurable edge type. These PWM events
 * can be configured independently and connect to the same or different source signals.
 *
 * @param[in] obj       PWM obj
 * @param[in] source    Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] signal    The PWM input signal
 * @param[in] edge_type The edge type that should trigger the event. This must be consistent with the
 *                      edge type of `source`. If `source` produces a "level" signal, the only valid
 *                      value is @ref CYHAL_EDGE_TYPE_LEVEL. If `source` produces an "edge" signal, then
 *                      @ref CYHAL_EDGE_TYPE_LEVEL is not a valid value.
 * @return The status of the connection
 * */
cy_rslt_t cyhal_pwm_connect_digital2(cyhal_pwm_t *obj, cyhal_source_t source, cyhal_pwm_input_t signal, cyhal_edge_type_t edge_type);

/** Enables the specified output signal from a PWM that will be triggered
 * when the corresponding event occurs. Multiple output signals can be
 * configured simultaneously.
 *
 * @param[in]  obj      PWM obj
 * @param[in]  signal   The PWM output signal
 * @param[out] source   Pointer to user-allocated source signal object which
 * will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t cyhal_pwm_enable_output(cyhal_pwm_t *obj, cyhal_pwm_output_t signal, cyhal_source_t *source);

/** Disconnects a source signal and disables the PWM event.
 *
 * @param[in] obj      PWM obj
 * @param[in] source   Source signal from cyhal_<PERIPH>_enable_output to disable
 * @param[in] signal   The PWM input signal
 * @return The status of the disconnection
 * */
cy_rslt_t cyhal_pwm_disconnect_digital(cyhal_pwm_t *obj, cyhal_source_t source, cyhal_pwm_input_t signal);

/** Disables the specified output signal from a PWM.
 *
 * @param[in]  obj      PWM obj
 * @param[in]  signal   The PWM output signal
 * @return The status of the output disable
 * */
cy_rslt_t cyhal_pwm_disable_output(cyhal_pwm_t *obj, cyhal_pwm_output_t signal);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_PWM_IMPL_HEADER
#include CYHAL_PWM_IMPL_HEADER
#endif /* CYHAL_PWM_IMPL_HEADER */

/** \} group_hal_pwm */
