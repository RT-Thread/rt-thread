/***************************************************************************//**
* \file cyhal_pdmpcm.h
*
* \brief
* Provides a high level interface for interacting with the Infineon PDM/PCM.
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
* \addtogroup group_hal_pdmpcm PDM/PCM (Pulse-Density Modulation to Pulse-Code Modulation Converter)
* \ingroup group_hal
* \{
* High level interface for interacting with the pulse-density modulation to
* pulse-code modulation (PDM/PCM) converter.
*
* The PDM/PCM converter is a asynchronous operation. A PDM-PCM converter is used
* to convert 1-bit digital audio streaming data to PCM data. The sample rate, word
* size, and channels can all be configured.
*
* \section section_pdmpcm_features Features
*
* * Supports FIFO buffer for Incoming Data
* * Configurable Gain Settings
* * Configurable Word Length
* * Configurable interrupt and callback assignment from PDM/PCM events - \ref cyhal_pdm_pcm_event_t
*
* \section section_pdmpcm_quickstart Quick Start
* Initialize a PDM/PCM converter instance using the \ref cyhal_pdm_pcm_init and
* provide the clock and data pins.<br>
* See \ref subsection_pdmpcm_snippet_1 for example initialization.
* \note The clock parameter (const \ref cyhal_clock_t *clk) is optional and
* can be set to NULL to generate and use an available clock resource with a default
* frequency.
*
* \section section_pdmpcm_snippets Code Snippets
* \note Error checking is omitted for clarity
*
* \subsection subsection_pdmpcm_snippet_1 Snippet 1: PDM/PCM Initialization and Configuration
* This snippet initializes a PCM/PCM resource for conversion and assigns the pins.
*
* \snippet hal_pdmpcm.c snippet_cyhal_pdmpcm_init
*
* \subsection subsection_pdmpcm_snippet_2 Snippet 2: PDM/PCM Asynchronous Receive
* This snippet shows how to receive data in the background using \ref cyhal_pdm_pcm_read_async.
* Notification of the asynchronous read completion is achieved by using \ref cyhal_pdm_pcm_register_callback
* to register a callback function and \ref cyhal_pdm_pcm_enable_event to enable callling the
* callback when an synchonous read completes.
*
* \snippet hal_pdmpcm.c snippet_cyhal_pdmpcm_async_receive
*
* \section subsection_pdmpcm_moreinformation More Information
*
* <b>Code examples (Github)</b>
* * <a href="https://github.com/infineon/mtb-example-psoc6-pdm-pcm" ><b>
PSoC™ 6 MCU: PDM-to-PCM</b></a>
* * <a href="https://github.com/infineon/mtb-example-psoc6-pdm-to-i2s" ><b>
PSoC™ 6 MCU: PDM to I2S</b></a>
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "cyhal_general_types.h"
#include "cyhal_hw_types.h"
#include "cyhal_pin_package.h"
#include "cyhal_syspm.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_pdmpcm PDM/PCM HAL Results
 *  PDM/PCM specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The pin PDM/PCM hardware cannot be initialized with the passed in pin */
#define CYHAL_PDM_PCM_RSLT_ERR_INVALID_PIN              \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_PDMPCM, 0))
/** A configuration parameter is invalid: sample_rate, decimation_rate, PCM word length, left/right gain.
 * See the implementation specific documentation for valid range */
#define CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_PDMPCM, 1))
/** An async read operation is already progres */
#define CYHAL_PDM_PCM_RSLT_ERR_ASYNC_IN_PROGRESS        \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_PDMPCM, 2))

/**
 * \}
 */

/** PDM/PCM interrupt triggers */
typedef enum {
    CYHAL_PDM_PCM_RX_HALF_FULL   = 0x01, /**< RX hardware buffer is half full */
    CYHAL_PDM_PCM_RX_NOT_EMPTY   = 0x02, /**< RX hardware buffer is not empty */
    CYHAL_PDM_PCM_RX_OVERFLOW    = 0x04, /**< Attempt to write to a full RX hardware buffer */
    CYHAL_PDM_PCM_RX_UNDERFLOW   = 0x08, /**< Attempt to read from an empty buffer */
    CYHAL_PDM_PCM_ASYNC_COMPLETE = 0x10, /**< Async operation completed */
} cyhal_pdm_pcm_event_t;

/** PDM/PCM channel select */
typedef enum {
    CYHAL_PDM_PCM_MODE_LEFT,   /**< The channel mono left */
    CYHAL_PDM_PCM_MODE_RIGHT,  /**< The channel mono right */
    CYHAL_PDM_PCM_MODE_STEREO, /**< The channel stereo */
} cyhal_pdm_pcm_mode_t;

/** Describes the current configuration of a PDM/PCM */
typedef struct
{
    uint32_t sample_rate;       /**< Sample rate in Hz */
    uint8_t decimation_rate;    /**< PDM decimation rate */
    cyhal_pdm_pcm_mode_t mode;  /**< left, right, or stereo */
    uint8_t word_length;        /**< PCM word length in bits, see the implementation specific documentation for valid range */
    int16_t left_gain;           /**< PGA in 0.5 dB increment, for example a value of 5 would mean +2.5 dB. The closest fit value will be used, see the implementation specific documentation for valid ranges. This may be negative if the implementation supports it. */
    int16_t right_gain;          /**< PGA in 0.5 dB increment, for example a value of 5 would mean +2.5 dB. The closest fit value will be used, see the implementation specific documentation for valid ranges. This may be negative if the implementation supports it. */
} cyhal_pdm_pcm_cfg_t;

/** Handler for PDM/PCM interrupts */
typedef void (*cyhal_pdm_pcm_event_callback_t)(void *handler_arg, cyhal_pdm_pcm_event_t event);

/** Initialize the PDM/PCM peripheral
 *
 * Configures the pins used by PDM/PCM converter, sets a default format and frequency, and enables the peripheral
 * @param[out] obj        Pointer to a PDM/PCM object. The caller must allocate the memory
 *                          for this object but the init function will initialize its contents.
 * @param[in]  pin_data   The pin to use for PDM input
 * @param[in]  pin_clk    The pin to use for PDM clock output
 * @param[in]  clk_source The clock source for PDM/PCM block
 * @param[in]  cfg        The configuration for the PDM/PCM block
 * @return The status of the init request
 */
cy_rslt_t cyhal_pdm_pcm_init(cyhal_pdm_pcm_t *obj, cyhal_gpio_t pin_data, cyhal_gpio_t pin_clk,
                const cyhal_clock_t *clk_source, const cyhal_pdm_pcm_cfg_t *cfg);

/** Initialize the PDM/PCM out peripheral using a configurator generated configuration struct
  *
 * @param[out] obj              Pointer to a PDM/PCM object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in] cfg               Configuration structure generated by a configurator.
 * @return The status of the init request
 */
cy_rslt_t cyhal_pdm_pcm_init_cfg(cyhal_pdm_pcm_t *obj, const cyhal_pdm_pcm_configurator_t* cfg);

/** Release a PDM/PCM object, behavior is undefined if an asynchronous read is in progress
 *
 * Return the peripheral, pins and clock owned by the PDM/PCM object to their reset state
 * @param[in,out] obj The PDM/PCM object to deinitialize
 */
void cyhal_pdm_pcm_free(cyhal_pdm_pcm_t *obj);

/**
 * Start the PDM/PCM operation
 *
 * @param[in] obj The PDM/PCM object to start
 * @return the status of the start request
 */
cy_rslt_t cyhal_pdm_pcm_start(cyhal_pdm_pcm_t *obj);

/**
 * Stop the PDM/PCM operation
 *
 * @param[in] obj The PDM/PCM object to start
 * @return the status of the stop request
 */
cy_rslt_t cyhal_pdm_pcm_stop(cyhal_pdm_pcm_t *obj);

/** Checks if the specified PDM/PCM peripheral is enabled (regardless of whether any
  * unread data has been received).
  *
  * The PDM/PCM peripheral can be enabled by calling @ref cyhal_pdm_pcm_start and disabled by calling
  * @ref cyhal_pdm_pcm_stop
  *
  * @param[in] obj  The I2S peripheral to check
  * @return Whether the I2S receive function is enabled.
  */
bool cyhal_pdm_pcm_is_enabled(cyhal_pdm_pcm_t *obj);

/** Updates the PDM/PCM channel gains. Each integer increment represent a 0.5 dB value.
 * For example: a gain value of 5 would mean +2.5 dB.
 * If the exact gain value requested is not supported, it will be rounded to the
 * nearest legal value. See the implementation specific documentation for valid ranges.
 *
 * \note Gains may be negative if the implementation supports it.
 *
 * @param[in] obj        The PDM/PCM object to configure
 * @param[in] gain_left  The gain of the left channel in units of 0.5 dB
 * @param[in] gain_right The gain of the right channel in units of 0.5 dB
 * @return The status of the set gain operation. An error will be returned if the value is outside of range supported by HW.
 */
cy_rslt_t cyhal_pdm_pcm_set_gain(cyhal_pdm_pcm_t *obj, int16_t gain_left, int16_t gain_right);

/** Clears the hardware buffer
 *
 * @param[in] obj The PDM/PCM peripheral
 * @return The status of the clear request
 */
cy_rslt_t cyhal_pdm_pcm_clear(cyhal_pdm_pcm_t *obj);

/** Reads data synchronously
 *
 * This will read either `length` words or the number of words that are currently available in the
 * receive buffer, whichever is less, then return. The value pointed to by `length` will be updated
 * to reflect the number of words that were actually read.
 *  If there are less data in FIFO than length, length will be update with number of words read.
 *
 * @param[in]     obj    The PDM/PCM peripheral
 * @param[out]    data   Pointer to word array where incoming data will be stored. Buffer must be aligned to word-size.
 *                       Each word will be aligned to the next largest power of 2. For example, if the word length is 16 bits,
 *                       each word will consume two bytes. But if the word length is 20, each word will consume 32 bits.
 *                       Negative value will use sign-extension. -1 with 24-bit word length will have 32-bit value of 0xFFFFFFFF.
 * @param[in,out] length Number of 32-bit words to read, updated with the number actually read
 * @return The status of the read request
 */
cy_rslt_t cyhal_pdm_pcm_read(cyhal_pdm_pcm_t *obj, void *data, size_t *length);

/** Begin asynchronous PDM/PCM read
 *
 * This will transfer `length` words into the buffer pointed to by `data` in the background. When the
 * requested quantity of data has been read, the @ref CYHAL_PDM_PCM_ASYNC_COMPLETE event will be raised.
 * See @ref cyhal_pdm_pcm_register_callback and @ref cyhal_pdm_pcm_enable_event.
 *
 * cyhal_pdm_pcm_set_async_mode can be used to control whether this uses DMA or a CPU-driven transfer.
 *
 * @param[in]  obj     The PDM/PCM object
 * @param[out] data    Pointer to word array where incoming data will be stored. Buffer must be aligned to word-size.
 *                     Each word will be aligned to the next largest power of 2. For example, if the word length is 16 bits,
 *                     each word will consume two bytes. But if the word length is 20, each word will consume 32 bits.
 *                     Negative value will use sign-extension. -1 with 24-bit word length will have 32-bit value of 0xFFFFFFFF.
 * @param[in]  length  Number of  words to read
 * @return The status of the read_async request
 */
cy_rslt_t cyhal_pdm_pcm_read_async(cyhal_pdm_pcm_t *obj, void *data, size_t length);

/** Checks if an async read operation is pending
 *
 * @param[in] obj  The PDM/PCM peripheral to check
 * @return Indication of whether a PDM/PCM async operation is pending
 */
bool cyhal_pdm_pcm_is_pending(cyhal_pdm_pcm_t *obj);

/** Abort an PDM/PCM operation started by cyhal_pdm_pcm_read_async function
 *
 * @param[in] obj The PDM/PCM peripheral to stop
 * @return The status of the abort_async request
 */
cy_rslt_t cyhal_pdm_pcm_abort_async(cyhal_pdm_pcm_t *obj);

/** Register a PDM/PCM event handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_pdm_pcm_enable_event occurs.
 *
 * @param[in] obj          The PDM/PCM object
 * @param[in] callback     The callback handler which will be invoked when the interrupt fires
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_pdm_pcm_register_callback(cyhal_pdm_pcm_t *obj, cyhal_pdm_pcm_event_callback_t callback, void *callback_arg);

/** Configure PDM/PCM event enablement.
 *
 * @param[in] obj            The PDM/PCM object
 * @param[in] event          The PDM/PCM event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on events, False to turn off
 */
void cyhal_pdm_pcm_enable_event(cyhal_pdm_pcm_t *obj, cyhal_pdm_pcm_event_t event, uint8_t intr_priority, bool enable);

/** Set the mechanism that is used to perform PDM/PCM asynchronous operation. The default is SW.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_pdm_pcm_register_callback will be called.
 *
 * @param[in] obj          The PDM/PCM object
 * @param[in] mode         The transfer mode
 * @param[in] dma_priority The priority, if DMA is used. Valid values are the same as for @ref cyhal_dma_init.
 *                         If DMA is not selected, the only valid value is CYHAL_DMA_PRIORITY_DEFAULT, and no
                           guarantees are made about prioritization.
 * @return The status of the set mode request
 */
cy_rslt_t cyhal_pdm_pcm_set_async_mode(cyhal_pdm_pcm_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_PDMPCM_IMPL_HEADER
#include CYHAL_PDMPCM_IMPL_HEADER
#endif /* CYHAL_PDMPCM_IMPL_HEADER */

/** \} group_hal_pdmpcm */
