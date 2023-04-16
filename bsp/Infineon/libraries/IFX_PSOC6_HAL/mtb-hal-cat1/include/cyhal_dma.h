/***************************************************************************//**
* \file cyhal_dma.h
*
* \brief
* Provides a high level interface for interacting with the Infineon DMA.
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
 * \addtogroup group_hal_dma DMA (Direct Memory Access)
 * \ingroup group_hal
 * \{
 * High level interface for interacting with the direct memory access (DMA). The DMA driver allows
 * for initializing and configuring a DMA channel in order to trigger data transfers to and from
 * memory and peripherals. The transfers occur independently of the CPU and can be triggered by
 * software or hardware. Multiple channels can be active at the same time each with their own
 * user-selectable priority and transfer characteristics.
 *
 * \section section_dma_features Features
 * * CPU independent memory access
 * * Access to memory and peripherals
 * * Multiple independent channels
 * * Configurable transer sizes and bursts
 * * Configurable priorities
 * * Event completion notification
 *
 * \section Usage Flow
 * The operational flow of the driver is listed below. This shows the basic order in which each of
 * the functions would generally be called. While Initialize must always be first and Release always
 * last, with care, the other functions can be reordered based on the implementation needs.
 * -# Initialize: \ref cyhal_dma_init or \ref cyhal_dma_init_adv or \ref cyhal_dma_init_cfg
 * -# Configure: \ref cyhal_dma_configure
 * -# Setup: \ref cyhal_dma_register_callback, \ref cyhal_dma_enable_event, \ref cyhal_dma_connect_digital, or \ref cyhal_dma_enable_output
 * -# Enable: \ref cyhal_dma_enable
 * -# Trigger: \ref cyhal_dma_start_transfer or via a hardware signal
 * -# Status/ReEnable (optional): \ref cyhal_dma_is_busy, \ref cyhal_dma_enable
 * -# Cleanup (optional): \ref cyhal_dma_disable, \ref cyhal_dma_enable_event, \ref cyhal_dma_disconnect_digital, or \ref cyhal_dma_disable_output
 * -# Release (optional): \ref cyhal_dma_free
 *
 * \section section_dma_quickstart Quick Start
 *
 * See \ref subsection_dma_snippet_1 for a code snippet that sets up a DMA
 * transfer to move memory from one location to another.
 *
 * \section section_dma_snippets Code snippets
 * \note Error handling code has been intentionally left out of snippets to highlight API usage.
 *
 * \subsection subsection_dma_snippet_1 Snippet 1: Simple DMA initialization and transfer
 * The following snippet initializes a DMA channel and uses it to transfer a a single block of memory.
 * The DMA channel is reserved by calling \ref cyhal_dma_init. It then needs to be configured with
 * \ref cyhal_dma_configure and then the transfer is started with \ref cyhal_dma_start_transfer.<br>
 * If the DMA channel is not needed anymore, it can be released by calling \ref cyhal_dma_free
 *
 * \snippet hal_dma.c snippet_cyhal_dma_simple_init
 *
 *
 * \subsection subsection_dma_snippet_2 Snippet 2: Configuring the DMA channel based on memory requirements
 * \ref cyhal_dma_configure can be used after DMA initialization to handle a variety of memory layouts.
 *
 * \snippet hal_dma.c snippet_cyhal_dma_configure
 *
 *
 * \subsection subsection_dma_snippet_3 Snippet 3: Interrupts and retriggering DMA transfers
 * DMA events like transfer complete or error events can be used to trigger a callback function. <br>
 * This snippet uses \ref cyhal_dma_configure to break the full transfer into multiple bursts. This
 * allows higher priority items access to the memory bus if necessary while the DMA operation is still
 * in progress. It then uses \ref cyhal_dma_enable_event() to enable the transfer complete event to
 * trigger the callback function registered by \ref cyhal_dma_register_callback().
 *
 * \snippet hal_dma.c snippet_cyhal_dma_events
 *
 *
 * \subsection subsection_dma_snippet_4 Snippet 4: Using hardware signals with DMA
 * DMA operations can be initiated by a hardware signal, or initiate a hardware signal on completion.
 * <br>This snippet shows how either can be done with a timer object.
 * \note Not all devices have the same internal connections. As a result, it may not be possible to
 * setup connections exactly as shown in the snippet on your device.
 *
 * In the first case, the DMA output signal (\ref cyhal_dma_enable_output) is used so that when the
 * DMA operation complets it in turn causes the timer to run.
 * <br>NOTE: The \ref cyhal_dma_init_adv can also be used insted of \ref cyhal_dma_enable_output to
 * enable the output. The advantage of using init_adv is it makes sure the DMA instance that is
 * allocated is able to connected to the specified signal.
 *
 * \snippet hal_dma.c snippet_cyhal_dma_triggers_output
 *
 * The second snippet shows how a timer overflow can be used to trigger a DMA operation. It uses
 * \ref cyhal_dma_init_adv to setup the connection, but \ref cyhal_dma_connect_digital could be used
 * instead; with the same note as above about ensuring a connection between instances.
 *
 * \snippet hal_dma.c snippet_cyhal_dma_triggers_input
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_dma DMA HAL Results
 *  DMA specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Invalid transfer width parameter error */
#define CYHAL_DMA_RSLT_ERR_INVALID_TRANSFER_WIDTH       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 0))
/** Invalid parameter error */
#define CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 1))
/** Invalid priority parameter error */
#define CYHAL_DMA_RSLT_ERR_INVALID_PRIORITY             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 2))
/** Invalid src or dst addr alignment error */
#define CYHAL_DMA_RSLT_ERR_INVALID_ALIGNMENT            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 3))
/** Invalid burst_size paramenter error */
#define CYHAL_DMA_RSLT_ERR_INVALID_BURST_SIZE           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 4))
/** Channel busy error */
#define CYHAL_DMA_RSLT_ERR_CHANNEL_BUSY                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 5))
/** Transfer has already been started warning */
#define CYHAL_DMA_RSLT_WARN_TRANSFER_ALREADY_STARTED    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_WARNING, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 6))
/** Unsupported hardware error */
#define CYHAL_DMA_RSLT_FATAL_UNSUPPORTED_HARDWARE       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_FATAL, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 7))
/** Requested transfer size is not supported */
#define CYHAL_DMA_RSLT_ERR_INVALID_TRANSFER_SIZE        \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_FATAL, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_DMA, 8))

/**
 * \}
 */

/** Direction for DMA transfers. */
typedef enum
{
    CYHAL_DMA_DIRECTION_MEM2MEM,       //!< Memory to memory
    CYHAL_DMA_DIRECTION_MEM2PERIPH,    //!< Memory to peripheral
    CYHAL_DMA_DIRECTION_PERIPH2MEM,    //!< Peripheral to memory
    CYHAL_DMA_DIRECTION_PERIPH2PERIPH, //!< Peripheral to peripheral
} cyhal_dma_direction_t;

/** Flags enum of DMA events. Multiple events can be enabled via \ref cyhal_dma_enable_event and
 * the callback from \ref cyhal_dma_register_callback will be run to notify. */
typedef enum
{
    CYHAL_DMA_NO_INTR             = 0,      //!< No interrupt
    CYHAL_DMA_TRANSFER_COMPLETE   = 1 << 0, /**< Indicates that an individual transfer (burst or
                                                 full) has completed based on the specified \ref
                                                 cyhal_dma_transfer_action_t */
    CYHAL_DMA_DESCRIPTOR_COMPLETE = 1 << 1, //!< Indicates that the full transfer has completed
    CYHAL_DMA_SRC_BUS_ERROR       = 1 << 2, //!< Indicates that there is a source bus error
    CYHAL_DMA_DST_BUS_ERROR       = 1 << 3, //!< Indicates that there is a destination bus error
    CYHAL_DMA_SRC_MISAL           = 1 << 4, //!< Indicates that the source address is not aligned
    CYHAL_DMA_DST_MISAL           = 1 << 5, //!< Indicates that the destination address is not aligned
    CYHAL_DMA_CURR_PTR_NULL       = 1 << 6, //!< Indicates that the current descriptor pointer is null
    CYHAL_DMA_ACTIVE_CH_DISABLED  = 1 << 7, //!< Indicates that the active channel is disabled
    CYHAL_DMA_DESCR_BUS_ERROR     = 1 << 8, //!< Indicates that there has been a descriptor bus error
} cyhal_dma_event_t;

/** Specifies the transfer type to trigger when an input signal is received. */
typedef enum
{
    CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT, //!< Transfer a single element when an input signal is received
    CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST,   //!< Transfer a single burst when an input signal is received
    CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS,   //!< Transfer all elements when an input signal is received
} cyhal_dma_input_t;

/** Specifies the transfer completion event that triggers a signal output. */
typedef enum
{
    CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT, //!< Trigger an output when a single element is transferred
    CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST,   //!< Trigger an output when a single burst is transferred
    CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS,   //!< Trigger an output when all elements are transferred
} cyhal_dma_output_t;

/** This defines the behavior of the the channel when transfers are initiated. It can specify both
 * how the transfer is broken up and what happens at the end of the transfer.
 * If burst_size from \ref cyhal_dma_cfg_t is used, this specifies the granularity of operations
 * that occur. Using \ref CYHAL_DMA_TRANSFER_BURST or \ref CYHAL_DMA_TRANSFER_BURST_DISABLE means
 * a single trigger will transfer a single burst (of burst_size) and raise the \ref
 * CYHAL_DMA_TRANSFER_COMPLETE interrupt. Using \ref CYHAL_DMA_TRANSFER_FULL means a single trigger
 * will transfer all bursts (total size length) and raise the \ref CYHAL_DMA_TRANSFER_COMPLETE
 * interrupt. If burst_size is not used, this has no impact and a single trigger will perform a
 * complete transfer and raise a single interrupt at the end.
 * When the transfer is complete, the channel can be left enabled, or automatically disabled. When
 * left enabled (\ref CYHAL_DMA_TRANSFER_BURST or \ref CYHAL_DMA_TRANSFER_FULL) subsequent triggers
 * will re-start the transfers. If the channel is diabled on completion (\ref
 * CYHAL_DMA_TRANSFER_BURST_DISABLE or \ref CYHAL_DMA_TRANSFER_FULL_DISABLE), \ref
 * cyhal_dma_configure must be called to reconfigure the channel for future transfers.
 *
 * \note When using \ref cyhal_dma_connect_digital for a hardware input trigger, the
 * \ref cyhal_dma_input_t argument defines how much of the transfer is initiated at a time. This
 * enum will still define when interrupts are raised. */
typedef enum
{
    /** A single burst is triggered and a \ref CYHAL_DMA_TRANSFER_COMPLETE will occur after
     * each burst. The channel will be left enabled and can continue to be triggered. */
    CYHAL_DMA_TRANSFER_BURST,
    /** All bursts are triggered and a single \ref CYHAL_DMA_TRANSFER_COMPLETE will occur at
     * the end. The channel will be left enabled and can continue to be triggered. */
    CYHAL_DMA_TRANSFER_FULL,
    /** A single burst is triggered and a \ref CYHAL_DMA_TRANSFER_COMPLETE will occur after
     * each burst. When all bursts are complete, the channel will be disabled. */
    CYHAL_DMA_TRANSFER_BURST_DISABLE,
    /** All bursts are triggered and a single \ref CYHAL_DMA_TRANSFER_COMPLETE will occur at
     * the end. When complete, the channel will be disabled. */
    CYHAL_DMA_TRANSFER_FULL_DISABLE,
} cyhal_dma_transfer_action_t;

/** \brief Configuration of a DMA channel. When configuring address,
 * increments, and transfer width keep in mind your hardware may have more
 * stringent address and data alignment requirements. */
typedef struct
{
    uint32_t src_addr;                  //!< Source address. Some devices can apply special requirements for user data arrays. Please refer to implementation-specific documentation to see whether any limitations exist for used device.
    int16_t  src_increment;             //!< Source address auto increment amount in multiples of transfer_width
    uint32_t dst_addr;                  //!< Destination address. Some devices can apply special requirements for user data arrays. Please refer to implementation-specific documentation to see whether any limitations exist for used device.
    int16_t  dst_increment;             //!< Destination address auto increment amount in multiples of transfer_width
    uint8_t  transfer_width;            //!< Transfer width in bits. Valid values are: 8, 16, or 32
    uint32_t length;                    //!< Number of elements to be transferred in total
    uint32_t burst_size;                //!< Number of elements to be transferred per trigger. If set to 0 every element is transferred, otherwise burst_size must evenly divide length.
    cyhal_dma_transfer_action_t action; //!< Sets the behavior of the channel when triggered (using start_transfer). Ignored if burst_size is not configured.
} cyhal_dma_cfg_t;

/** Event handler for DMA interrupts */
typedef void (*cyhal_dma_event_callback_t)(void *callback_arg, cyhal_dma_event_t event);

/** DMA input connection information to setup while initializing the driver. */
typedef struct
{
    cyhal_source_t      source; //!< Source of signal to DMA; obtained from another driver's cyhal_<PERIPH>_enable_output
    cyhal_dma_input_t   input;  //!< DMA input signal to be driven
} cyhal_dma_src_t;

/** DMA output connection information to setup while initializing the driver. */
typedef struct
{
    cyhal_dma_output_t  output; //!< Output signal of DMA
    cyhal_dest_t        dest;   //!< Destination of DMA signal
} cyhal_dma_dest_t;

/** Initialize the DMA peripheral.
 *
 * If a source signal is provided for \p src, this will connect the provided signal to the DMA
 * just as would be done by calling \ref cyhal_dma_connect_digital. Similarly, if a destination
 * target is provided for \p dest this will enable the specified output just as would be done
 * by calling \ref cyhal_dma_enable_output.
 * @param[out] obj  Pointer to a DMA object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  src          An optional source signal to connect to the DMA
 * @param[in]  dest         An optional destination signal to drive from the DMA
 * @param[out] dest_source  An optional pointer to user-allocated source signal object which
 * will be initialized by enable_output. If \p dest is non-null, this must also be non-null.
 * \p dest_source should be passed to (dis)connect_digital functions to (dis)connect the
 * associated endpoints.
 * @param[in]  priority     The priority of this DMA operation relative to others. The number of
 * priority levels which are supported is hardware dependent. All implementations define a
 * #CYHAL_DMA_PRIORITY_DEFAULT constant which is always valid. If supported, implementations will
 * also define #CYHAL_DMA_PRIORITY_HIGH, #CYHAL_DMA_PRIORITY_MEDIUM, and #CYHAL_DMA_PRIORITY_LOW.
 * The behavior of any other value is implementation defined. See the implementation-specific DMA
 * documentation for more details.
 * @param[in]  direction    The direction memory is copied
 * @return The status of the init request
 */
cy_rslt_t cyhal_dma_init_adv(cyhal_dma_t *obj, cyhal_dma_src_t *src, cyhal_dma_dest_t *dest, cyhal_source_t *dest_source, uint8_t priority, cyhal_dma_direction_t direction);

/** Initialize the DMA peripheral.
 *
 * @param[out] obj          Pointer to a DMA object. The caller must allocate the memory for this
 * object but the init function will initialize its contents.
 * @param[in]  priority     The priority of this DMA operation relative to others. The number of
 * priority levels which are supported is hardware dependent. All implementations define a
 * #CYHAL_DMA_PRIORITY_DEFAULT constant which is always valid. If supported, implementations will
 * also define #CYHAL_DMA_PRIORITY_HIGH, #CYHAL_DMA_PRIORITY_MEDIUM, and #CYHAL_DMA_PRIORITY_LOW.
 * The behavior of any other value is implementation defined. See the implementation-specific DMA
 * documentation for more details.
 * @param[in]  direction    The direction memory is copied
 * @return The status of the init request
 */
#define cyhal_dma_init(obj, priority, direction)    (cyhal_dma_init_adv(obj, NULL, NULL, NULL, priority, direction))

/** Initialize the DMA peripheral using data provided by the configurator.
 *
 * \note Depending on what the configurator allows filling it, it is likely that at least the source
 * and destination addresses of the transfer(s) still need to be setup.
 *
 * @param[out] obj  Pointer to a DMA object. The caller must allocate the memory for this
 * object but the init function will initialize its contents.
 * @param[in]  cfg  Configuration structure generated by a configurator.
 * @return The status of the init request
 */
cy_rslt_t cyhal_dma_init_cfg(cyhal_dma_t *obj, const cyhal_dma_configurator_t *cfg);

/** Free the DMA object. Freeing a DMA object while a transfer is in progress
 * (\ref cyhal_dma_is_busy) is invalid.
 *
 * @param[in,out] obj The DMA object
 */
void cyhal_dma_free(cyhal_dma_t *obj);

/** Setup the DMA channel behavior. This will also enable the channel to allow it to be triggered.
 * The transfer can be software triggered by calling \ref cyhal_dma_start_transfer or by hardware.
 * A hardware input signal is setup by \ref cyhal_dma_connect_digital or \ref cyhal_dma_init_adv.
 * \note If hardware triggers are used, any necessary event callback setup (\ref
 * cyhal_dma_register_callback and \ref cyhal_dma_enable_event) should be done before calling
 * this function to ensure the handlers are in place before the transfer can happen.
 * \note The automatic enablement of the channel as part of this function is expected to change
 * in a future update. This would only happen on a new major release (eg: 1.0 -> 2.0).
 * \note If the DMA was setup using \ref cyhal_dma_init_cfg, this function should not be used.
 *
 * @param[in] obj    The DMA object
 * @param[in] cfg    Configuration parameters for the transfer
 * @return The status of the configure request
 */
cy_rslt_t cyhal_dma_configure(cyhal_dma_t *obj, const cyhal_dma_cfg_t *cfg);

/** Enable the DMA transfer so that it can start transferring data when triggered. A trigger is
 * caused either by calling \ref cyhal_dma_start_transfer or by hardware as a result of a connection
 * made in either \ref cyhal_dma_connect_digital or \ref cyhal_dma_init_adv. The DMA can be disabled
 * by calling \ref cyhal_dma_disable or by setting the \ref cyhal_dma_cfg_t action to \ref
 * CYHAL_DMA_TRANSFER_BURST_DISABLE, or \ref CYHAL_DMA_TRANSFER_FULL_DISABLE.
 *
 * @param[in] obj    The DMA object
 * @return The status of the enable request
 */
cy_rslt_t cyhal_dma_enable(cyhal_dma_t *obj);

/** Disable the DMA transfer so that it does not continue to trigger. It can be reenabled by calling
 * \ref cyhal_dma_enable or \ref cyhal_dma_configure.
 *
 * @param[in] obj    The DMA object
 * @return The status of the enable request
 */
cy_rslt_t cyhal_dma_disable(cyhal_dma_t *obj);

/** Initiates DMA channel transfer for specified DMA object. This should only be done after the
 * channel has been configured (\ref cyhal_dma_configure) and any necessary event callbacks setup
 * (\ref cyhal_dma_register_callback \ref cyhal_dma_enable_event)
 *
 * @param[in] obj    The DMA object
 * @return The status of the start_transfer request
 */
cy_rslt_t cyhal_dma_start_transfer(cyhal_dma_t *obj);

/** Checks if the transfer has been triggered, but not yet complete (eg: is pending, blocked or running)
 *
 * @param[in] obj    The DMA object
 * @return True if DMA channel is busy
 */
bool cyhal_dma_is_busy(cyhal_dma_t *obj);

/** Register a DMA callback handler.
 *
 * This function will be called when one of the events enabled by \ref cyhal_dma_enable_event occurs.
 *
 * @param[in] obj          The DMA object
 * @param[in] callback     The callback handler which will be invoked when an event triggers
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_dma_register_callback(cyhal_dma_t *obj, cyhal_dma_event_callback_t callback, void *callback_arg);

/** Configure DMA event enablement.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_dma_register_callback will be called.
 *
 * @param[in] obj            The DMA object
 * @param[in] event          The DMA event type
 * @param[in] intr_priority  The priority for NVIC interrupt events. The priority from the most
 * recent call will take precedence, i.e all events will have the same priority.
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_dma_enable_event(cyhal_dma_t *obj, cyhal_dma_event_t event, uint8_t intr_priority, bool enable);

/** Connects a source signal and enables the specified input to the DMA channel. This connection
 * can also be setup automatically on initialization via \ref cyhal_dma_init_adv. If the signal
 * needs to be disconnected later, \ref cyhal_dma_disconnect_digital can be used.
 *
 * @param[in] obj         The DMA object
 * @param[in] source      Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] input       Which input to enable
 * @return The status of the connection
 */
cy_rslt_t cyhal_dma_connect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input);

/** Enables the specified output signal from a DMA channel that is triggered when a transfer is
 * completed. This can also be setup automatically on initialization via \ref cyhal_dma_init_adv.
 * If the output is not needed in the future, \ref cyhal_dma_disable_output can be used.
 *
 * @param[in]  obj         The DMA object
 * @param[in]  output      Which event triggers the output
 * @param[out] source      Pointer to user-allocated source signal object which
 * will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 */
cy_rslt_t cyhal_dma_enable_output(cyhal_dma_t *obj, cyhal_dma_output_t output, cyhal_source_t *source);

/** Disconnects a source signal and disables the specified input to the DMA channel. This removes
 * the connection that was established by either \ref cyhal_dma_init_adv or \ref
 * cyhal_dma_connect_digital.
 *
 * @param[in] obj         The DMA object
 * @param[in] source      Source signal from cyhal_<PERIPH>_enable_output to disable
 * @param[in] input       Which input to disable
 * @return The status of the disconnect
 */
cy_rslt_t cyhal_dma_disconnect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input);

/** Disables the specified output signal from a DMA channel. This turns off the signal that was
 * enabled by either \ref cyhal_dma_init_adv or \ref cyhal_dma_enable_output. It is recommended
 * that the signal is disconnected (cyhal_<PERIPH>_disconnect_digital) from anything it might be
 * driving before being disabled.
 *
 * @param[in]  obj         The DMA object
 * @param[in]  output      Which output to disable
 * @return The status of the disablement
 * */
cy_rslt_t cyhal_dma_disable_output(cyhal_dma_t *obj, cyhal_dma_output_t output);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_DMA_IMPL_HEADER
#include CYHAL_DMA_IMPL_HEADER
#endif /* CYHAL_DMA_IMPL_HEADER */

/** \} group_hal_dma */
