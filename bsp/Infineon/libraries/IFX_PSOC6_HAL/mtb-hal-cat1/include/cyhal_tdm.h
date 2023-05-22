/***************************************************************************//**
* \file cyhal_tdm.h
*
* \brief
* Provides a high level interface for interacting with the Infineon TDM.
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
* \addtogroup group_hal_tdm TDM (Time Division Multiplexed)
* \ingroup group_hal
* \{
* High level interface for interacting with the Time Division Multiplexed controller (TDM).
*
* The TDM protocol is a asynchronous serial interface protocol. This driver supports
* both transmit and receive modes of operation. The communication frequency, sample rate,
* word size, and number of channels can all be configured.
*
* \note Certain platforms may not support all of the functionality and configuration options
* provided by this driver. Please refer to implementation specific documentation for details
* on available options.
*
* \section section_tdm_features Features
*
* * Transmit and receive functionality
* * Configurable data rates
* * Configurable channel count and word size
* * Configurable interrupt and callback assignment from TDM events - \ref cyhal_tdm_event_t
*
* \section section_tdm_quickstart Quick Start
* Initialize an TDM instance using the \ref cyhal_tdm_init and provide the transmit (tx) and/or receive (rx) pins. Call
* \ref cyhal_tdm_start_tx and/or \ref cyhal_tdm_start_rx to enable transmit and/or receive functionality as desired.<br>
* See \ref subsection_tdm_snippet_1 for example initialization as transmit or receive.
* \note The clock parameter (const \ref cyhal_clock_t *clk) is optional and can be set
* to NULL to generate and use an available clock resource with a default frequency.
*
* The sclk frequency is determined as `sclk = sample_rate_hz * channel_length * num_channels`.
* The input clock must be a multiple of this sclk frequency; see the implementation specific
* documentation for the supported multipliers.
*
* It is possible to use either only TX functionality, only RX functionality, or both RX and TX functionality at the same time.
* If RX and TX are both in use, the same sample rate, channel length, channel count, channel mask, word length, and sclk
* frequency will be used for both.
*
* \section section_tdm_snippets Code Snippets
* \note Error checking is omitted for clarity
*
* \subsection subsection_tdm_snippet_1 Snippet 1: TDM Initialization and Configuration
* This snippet initializes an TDM resource for transmit or receive and assigns the pins.
*
* Initializing as TDM transmitter
* \snippet hal_tdm.c snippet_cyhal_tdm_transmit_init
*
* Initializing as TDM receiver
* \snippet hal_tdm.c snippet_cyhal_tdm_receive_init
*
* \subsection subsection_tdm_snippet_2 Snippet 2: TDM Transmit One-shot
* This snippet shows how to transmit data using \ref cyhal_tdm_write_async when the entire sample
* is available at once. <br>
*
* \snippet hal_tdm.c snippet_cyhal_tdm_async_transmit_one_shot

* \subsection subsection_tdm_snippet_3 Snippet 3: TDM Transmit Streaming
* This snippet shows how to transmit data using \ref cyhal_tdm_write_async when sample data is
* being continuously loaded and transmitted (e.g. streaming over the network). <br>
*
* \snippet hal_tdm.c snippet_cyhal_tdm_async_transmit_streaming

* \subsection subsection_tdm_snippet_4 Snippet 4: TDM Receive
* This snippet shows how to receive data using \ref cyhal_tdm_read_async. <br>
*
* \snippet hal_tdm.c snippet_cyhal_tdm_async_receive
*
* \section subsection_tdm_moreinformation More Information
*
* <b>Code examples (Github)</b>
* * <a href="https://github.com/infineon/mtb-example-psoc6-tdm" ><b>
PSoCâ„¢ 6 MCU: Time Division Multiplexing (TDM)</b></a>
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_clock.h"
#include "cyhal_dma.h"
#include "cyhal_general_types.h"
#include "cyhal_hw_types.h"
#include "cyhal_gpio.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_tdm TDM HAL Results
 *  TDM specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** An invalid pin location was specified */
#define CYHAL_TDM_RSLT_ERR_INVALID_PIN        \
  (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TDM, 0))

/** An argument was provided */
#define CYHAL_TDM_RSLT_ERR_INVALID_ARG        \
  (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TDM, 1))

/** Initialization of the TDM hardware failed*/
#define CYHAL_TDM_RSLT_ERR_INIT_FAILED        \
  (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TDM, 2))

/** The requested clock frequency could not be achieved */
#define CYHAL_TDM_RSLT_ERR_CLOCK \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TDM, 3))

/** The requested configuration is not supported. */
#define CYHAL_TDM_RSLT_NOT_SUPPORTED \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_TDM, 4))

/** * \} */

/** TDM events */
typedef enum {
    /** TX HW Buffer is not full */
    CYHAL_TDM_TX_NOT_FULL         = 1 << 0,
    /** TX HW Buffer is half empty */
    CYHAL_TDM_TX_HALF_EMPTY       = 1 << 1,
    /** TX HW Buffer is empty */
    CYHAL_TDM_TX_EMPTY            = 1 << 2,
    /** Attempt to write when TX HW Buffer is full */
    CYHAL_TDM_TX_OVERFLOW         = 1 << 3,
    /** Interface ready to transfer data but HW TX buffer is empty */
    CYHAL_TDM_TX_UNDERFLOW        = 1 << 4,
    /** Pending async transmit is complete (but the HW buffer may still contain unsent data) */
    CYHAL_TDM_ASYNC_TX_COMPLETE   = 1 << 5,
    /** RX HW Buffer is not Empty */
    CYHAL_TDM_RX_NOT_EMPTY        = 1 << 6,
    /** RX HW Buffer is half full */
    CYHAL_TDM_RX_HALF_FULL        = 1 << 7,
    /** RX HW Buffer is FULL */
    CYHAL_TDM_RX_FULL             = 1 << 8,
    /** Attempt to write when RX HW Buffer is full */
    CYHAL_TDM_RX_OVERFLOW         = 1 << 9,
    /** Attempt to read when HW RX buffer is empty */
    CYHAL_TDM_RX_UNDERFLOW        = 1 << 10,
    /** Pending async receive is complete */
    CYHAL_TDM_ASYNC_RX_COMPLETE   = 1 << 11,
} cyhal_tdm_event_t;

/** Selections for TDM output signals  */
typedef enum
{
    /** An output signal should be triggered when the receive buffer is half full */
    CYHAL_TDM_TRIGGER_RX_HALF_FULL,
    /** An output signal should be triggered when the transmit buffer is half empty */
    CYHAL_TDM_TRIGGER_TX_HALF_EMPTY,
}
cyhal_tdm_output_t;

/** Pins to use for one TDM direction */
typedef struct {
    cyhal_gpio_t sck;   //!< Clock pin
    cyhal_gpio_t ws;    //!< Word select
    cyhal_gpio_t data;  //!< Data pin (sdo or sdi)
    cyhal_gpio_t mclk;  //!< Mclk input pin. Set to NC if an internal clock source should be used
} cyhal_tdm_pins_t;

/** Word select pulse width */
typedef enum
{
    CYHAL_TDM_WS_SINGLE, //!< Single SCK cycle
    CYHAL_TDM_WS_FULL,   //!< Full channel length
} cyhal_tdm_word_select_width_t;

/** TDM Configuration */
typedef struct {
    /** Configure TX to operate as slave (true) or master (false) */
    bool is_tx_slave;
    /** Word select pulse width for TX direction */
    cyhal_tdm_word_select_width_t tx_ws_width;
    /** Configure RX to operate as slave (true) or master (false) */
    bool is_rx_slave;
    /** Word select pulse width for RX direction */
    cyhal_tdm_word_select_width_t rx_ws_width;
    /** Frequency, in hertz, of the master clock if it is provided by an external pin.
     * If at least one mclk pin is not NC, this must be nonzero.
     * If both mclk pins are NC, this must be zero.
     */
    uint32_t mclk_hz;
    /** Number of bits in each channel. See the implementation specific documentation for supported values. */
    uint8_t channel_length;
    /**
      * Number of channels. Must be a value between 1 and 32. Not all implementations support
      * all channel counts; see the implementation specific documentation for details.
      */
    uint8_t num_channels;
    /**
      * Determines which channels are enabled. Disabled channels still participate in the time
      * slicing, but the contents of a disabled channel are silently discarded (for Rx) or
      * sent as all 0's (for Tx).
      * This is a mask, with each bit corresponding to the enabled state of one channel.
      * Not all implementations permit masking of arbitrary channel combinations. See the
      * implementation specific documentation for details.
      */
    uint32_t channel_mask;
    /** Number of bits in each word. Must be less than or equal to channel_length.
     * If word_length < 32, the excess bits will be padded with 0's.
     */
    uint8_t word_length;
    /** Sample rate in Hz */
    uint32_t sample_rate_hz;
} cyhal_tdm_config_t;

/** Handler for TDM event callbacks */
typedef void (*cyhal_tdm_event_callback_t)(void *callback_arg, cyhal_tdm_event_t event);

/** Initialize the TDM peripheral. It sets the default parameters for TDM
 *  peripheral, and configures its specifieds pins.
 *  If only one direction is to be used, then the pins for the other direction need not be specified (i.e. they may be set to NC).
 *  For example, if only RX is needed, tx_sck, tx_ws, and tx_sdo may all be set to NC.
 *  If one pin is specified for a direction, all pins for that direction must be specified.
 *
 * @param[out] obj          Pointer to a TDM object. The caller must allocate the memory
 *                            for this object but the init function will initialize its contents.
 * @param[in]  tx_pins      Pins for TDM transmit. If NULL, transmit functionality will be disabled.
 * @param[in]  rx_pins      Pins for TDM receive. If NULL, receive functionality will be disabled.
 * @param[in]  config       Initial block configuration
 * @param[in]  clk          Clock source to use for this instance. If NULL, a dedicated clock divider will be allocated for this instance.
 * @return The status of the init request
 */
cy_rslt_t cyhal_tdm_init(cyhal_tdm_t *obj, const cyhal_tdm_pins_t* tx_pins, const cyhal_tdm_pins_t* rx_pins,
                         const cyhal_tdm_config_t* config, cyhal_clock_t* clk);

/** Initialize the TDM peripheral using a configurator generated configuration struct
  *
 * @param[out] obj              Pointer to a TDM object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[in] cfg               Configuration structure generated by a configurator.
 * @return The status of the init request
 */
 cy_rslt_t cyhal_tdm_init_cfg(cyhal_tdm_t *obj, const cyhal_tdm_configurator_t *cfg);

/** Deinitialize the tdm object
 *
 * @param[in,out] obj The tdm object
 */
void cyhal_tdm_free(cyhal_tdm_t *obj);

/** Set the TDM sample rate
 *
 * @param[in] obj           The TDM object
 * @param[in] sample_rate_hz Sample rate in Hz
 * @return The status of the set sample rate request
 */
cy_rslt_t cyhal_tdm_set_sample_rate(cyhal_tdm_t *obj, uint32_t sample_rate_hz);

/** Starts transmitting data. Transmission will continue until it is stopped by
  * calling @ref cyhal_tdm_stop_tx.
  *
  * @param[in] obj The TDM object
  * @return The status of the start request.
  */
cy_rslt_t cyhal_tdm_start_tx(cyhal_tdm_t *obj);

/** Stops transmitting data. This immediately terminates data transmission.
  *
  * @param[in] obj The TDM object
  * @return The status of the stop request.
  */
cy_rslt_t cyhal_tdm_stop_tx(cyhal_tdm_t *obj);

/** Clears the tx hardware buffer
 *
 * @param[in] obj The tdm peripheral
 * @return The status of the clear request
 */
cy_rslt_t cyhal_tdm_clear_tx(cyhal_tdm_t *obj);

/** Starts receiving data. Data will continue to be received until it is
  * stopped by calling @ref cyhal_tdm_stop_rx.
  *
  * @param[in] obj The TDM object
  * @return The status of the start request.
  */
cy_rslt_t cyhal_tdm_start_rx(cyhal_tdm_t *obj);

/** Stops receiving data. This immediately terminates data receipt.
  *
  * @param[in] obj The TDM object
  * @return The status of the stop request.
  */
cy_rslt_t cyhal_tdm_stop_rx(cyhal_tdm_t *obj);

/** Clears the rx hardware buffer
 *
 * @param[in] obj The tdm peripheral
 * @return The status of the clear request
 */
cy_rslt_t cyhal_tdm_clear_rx(cyhal_tdm_t *obj);

/** Read data synchronously
 *
 * This will read the number of words specified by the `length` parameter, or the number of words that
 * are currently available in the receive buffer, whichever is less, then return. The value pointed to
 * by `length` will be updated to reflect the number of words that were actually read.
 *
 * @param[in]  obj    The TDM object
 * @param[out] data   The buffer for receiving
 * @param[in,out] length Number of words to (as configured in cyhal_tdm_config_t.word_length) read, updated with the number actually read
 * @return The status of the read request
 *
 * @note Each word will be aligned to the next largest power of 2. For example, if the word length is 16 bits,
 * each word will consume two bytes. But if the word length is 20, each word will consume 32 bytes.
 * @return The status of the write request
 */
cy_rslt_t cyhal_tdm_read(cyhal_tdm_t *obj, void *data, size_t* length);

/** Send data synchronously
 *
 * This will write either `length` words or until the write buffer is full, whichever is less,
 * then return. The value pointed to by `length` will be updated to reflect the number of words
 * that were actually written.
 * @note This function only queues data into the write buffer; it does not block until the
 *  data has all been sent out over the wire.
 *
 * @param[in] obj     The TDM object
 * @param[in] data    The buffer for sending
 * @param[in,out] length Number of words to write (as configured in cyhal_tdm_config_t.word_length, updated with the number actually written
 * @return The status of the write request
 *
 * @note Each word will be aligned to the next largest power of 2. For example, if the word length is 16 bits,
 * each word will consume two bytes. But if the word length is 20, each word will consume 32 bytes.
 */
cy_rslt_t cyhal_tdm_write(cyhal_tdm_t *obj, const void *data, size_t *length);

/** Checks if the transmit functionality is enabled for the specified TDM peripheral (regardless of whether data
  * is currently queued for transmission).
  *
  * The transmit functionality can be enabled by calling @ref cyhal_tdm_start_tx and disabled by calling
  * @ref cyhal_tdm_stop_tx
  *
  * @param[in] obj  The TDM peripheral to check
  * @return Whether the TDM transmit function is enabled.
  */
bool cyhal_tdm_is_tx_enabled(cyhal_tdm_t *obj);

/** Checks if the receive functionality is enabled for the specified TDM peripheral (regardless of whether any
  * unread data has been received).
  *
  * The receive functionality can be enabled by calling @ref cyhal_tdm_start_rx and disabled by calling
  * @ref cyhal_tdm_stop_rx
  *
  * @param[in] obj  The TDM peripheral to check
  * @return Whether the TDM receive function is enabled.
  */
bool cyhal_tdm_is_rx_enabled(cyhal_tdm_t *obj);

/** Checks if the specified TDM peripheral is transmitting data, including if a pending async transfer is waiting
  * to write more data to the transmit buffer.
  *
  * @param[in] obj  The TDM peripheral to check
  * @return Whether the TDM is still transmitting
  */
bool cyhal_tdm_is_tx_busy(cyhal_tdm_t *obj);

/** Checks if the specified TDM peripheral has received data that has not yet been read out of the hardware buffer.
  * This includes if an async read transfer is pending.
  *
  * @param[in] obj  The TDM peripheral to check
  * @return Whether the TDM is still transmitting
  */
bool cyhal_tdm_is_rx_busy(cyhal_tdm_t *obj);

/** Start TDM asynchronous read.
 *
 * This will transfer `rx_length` words into the buffer pointed to by `rx` in the background. When the
 * requested quantity of data has been read, the @ref CYHAL_TDM_ASYNC_RX_COMPLETE event will be raised.
 * See @ref cyhal_tdm_register_callback and @ref cyhal_tdm_enable_event.
 *
 * @ref cyhal_tdm_set_async_mode can be used to control whether this uses DMA or a SW (CPU-driven) transfer.
 *
 * @note Each word will be aligned to the next largest power of 2. For example, if the word length is 16 bits,
 * each word will consume two bytes. But if the word length is 20, each word will consume 32 bytes.
 *
 * @param[in]     obj       The TDM object
 * @param[out]    rx        The receive buffer.
 * @param[in]     rx_length Number of words (as configured in cyhal_tdm_config_t.word_length) to read.
 * @return The status of the read_async request
 */
cy_rslt_t cyhal_tdm_read_async(cyhal_tdm_t *obj, void *rx, size_t rx_length);

/** Start TDM asynchronous write.
 *
 * This will transfer `tx_length` words into the tx buffer in the background. When the requested
 * quantity of data has been queued in the transmit buffer, the @ref CYHAL_TDM_ASYNC_TX_COMPLETE
 * event will be raised. See @ref cyhal_tdm_register_callback and @ref cyhal_tdm_enable_event.
 *
 * @ref cyhal_tdm_set_async_mode can be used to control whether this uses DMA or a SW (CPU-driven) transfer.
 *
 * @note Each word will be aligned to the next largest power of 2. For example, if the word length is 16 bits,
 * each word will consume two bytes. But if the word length is 20, each word will consume 32 bytes.
 *
 * @param[in]     obj       The TDM object
 * @param[in]     tx        The transmit buffer.
 * @param[in]     tx_length The number of words to transmit.
 * @return The status of the transfer_async request
 */
cy_rslt_t cyhal_tdm_write_async(cyhal_tdm_t *obj, const void *tx, size_t tx_length);

/** Set the mechanism that is used to perform TDM asynchronous transfers. The default is SW.
 *  @warning The effect of calling this function while an async transfer is pending is undefined.
 *
 * @param[in]     obj          The TDM object
 * @param[in]     mode         The transfer mode
 * @param[in]     dma_priority The priority, if DMA is used. Valid values are the same as for @ref cyhal_dma_init.
 *                             If DMA is not selected, the only valid value is CYHAL_DMA_PRIORITY_DEFAULT, and no
                               guarantees are made about prioritization.
 * @return The status of the set mode request
 */
cy_rslt_t cyhal_tdm_set_async_mode(cyhal_tdm_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority);

/** Checks if the specified TDM peripheral is in the process of reading data from the hardware buffer into RAM.
 *
 * @note: This only checks whether there is an ongoing transfer (e.g. via cyhal_tdm_read_async) into RAM from the
 *  TDM peripheral's hardware buffer. It does not check whether unread data exists in the hardware buffer.
 *
 * @param[in] obj  The TDM peripheral to check
 * @return Whether an asynchronous read operation is still in progress
 */
bool cyhal_tdm_is_read_pending(cyhal_tdm_t *obj);

/** Checks if the specified TDM peripheral is in the process of writing data into the hardware buffer.
 *
 * @note: This only checks whether there is an ongoing transfer (e.g. via cyhal_tdm_transfer_async) from RAM into the
 *  TDM peripheral's hardware buffer. It does not check whether unwritten data exists in the hardware buffer.
 *
 * @param[in] obj  The TDM peripheral to check
 * @return Whether an asynchronous write operation is still in progress
 */
bool cyhal_tdm_is_write_pending(cyhal_tdm_t *obj);

/** Abort TDM asynchronous read
 *
 * This function does not perform any validation before aborting the transfer.
 * Any validation which is required is the responsibility of the application.
 *
 * @param[in] obj The TDM object
 * @return The status of the abort_async_read request
 */
cy_rslt_t cyhal_tdm_abort_read_async(cyhal_tdm_t *obj);

/** Abort TDM asynchronous write
 *
 * This function does not perform any validation before aborting the transfer.
 * Any validation which is required is the responsibility of the application.
 *
 * @param[in] obj The TDM object
 * @return The status of the abort_async_write request
 */
cy_rslt_t cyhal_tdm_abort_write_async(cyhal_tdm_t *obj);

/** Register a TDM callback handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_tdm_enable_event occurs.
 *
 * @param[in] obj          The TDM object
 * @param[in] callback     The callback handler which will be invoked when the interrupt fires
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_tdm_register_callback(cyhal_tdm_t *obj, cyhal_tdm_event_callback_t callback, void *callback_arg);

/** Configure TDM events.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_tdm_register_callback will be called.
 *
 * @param[in] obj            The TDM object
 * @param[in] event          The TDM event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on specified events, False to turn off
 */
void cyhal_tdm_enable_event(cyhal_tdm_t *obj, cyhal_tdm_event_t event, uint8_t intr_priority, bool enable);

/** Enables the specified output signal
 *
 * @param[in]  obj          The TDM object
 * @param[in]  output       Which output signal to enable
 * @param[out] source       Pointer to user-allocated source signal object
 * which will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
  * @return The status of the output enable
 */
cy_rslt_t cyhal_tdm_enable_output(cyhal_tdm_t *obj, cyhal_tdm_output_t output, cyhal_source_t *source);

/** Disables the specified output signal
 *
 * @param[in]  obj          The TDM object
 * @param[in]  output       Which output signal to disable
 *
 * @return The status of the disablement
 */
cy_rslt_t cyhal_tdm_disable_output(cyhal_tdm_t *obj, cyhal_tdm_output_t output);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_TDM_IMPL_HEADER
#include CYHAL_TDM_IMPL_HEADER
#endif /* CYHAL_TDM_IMPL_HEADER */

/** \} group_hal_tdm */
