/***************************************************************************//**
* \file cyhal_uart.h
*
* \brief
* Provides a high level interface for interacting with the Infineon UART.
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
* \addtogroup group_hal_uart UART (Universal Asynchronous Receiver-Transmitter)
* \ingroup group_hal
* \{
* High level interface for interacting with the Universal Asynchronous Receiver-Transmitter (UART).
*
* The Universal Asynchronous Receiver/Transmitter (UART) protocol is an
* asynchronous serial interface protocol. UART communication is typically
* point-to-point. The UART interface consists of two signals:
* * TX: Transmitter output
* * RX: Receiver input
*
* Additionally, two side-band signals are used to implement flow control in
* UART. Note that the flow control applies only to TX functionality.
* * Clear to Send (CTS): This is an input signal to the transmitter.
*   When active, it indicates that the slave is ready for the master to
*   transmit data.
* * Ready to Send (RTS): This is an output signal from the receiver. When
*   active, it indicates that the receiver is ready to receive data
*
* Flow control can be configured by providing cts / rts pins to cyhal_uart_init() and this will activate the feature in
* driver. In case flow control enablement status needs to be changed, cyhal_uart_enable_flow_control() function
* can be used.
*
* The data frame size, STOP bits and parity can be configured via \ref cyhal_uart_cfg_t.
* The UART contains dedicated hardware buffers for transmit and receive. Optionally,
* either of these can be augmented with a software buffer. This is done in scope of \ref cyhal_uart_init (if appropriate
* configuration was selected) and \ref cyhal_uart_config_software_buffer functions.
*
* \note For applications that require printing messages on a UART terminal using printf(),
* the <a href="https://github.com/infineon/retarget-io">retarget-io</a> utility library can be used directly.
*
*
* \section subsection_uart_features Features
* * Configurable UART baud rate - \ref cyhal_uart_set_baud
* * Configurable data frame size, STOP bits and parity - \ref cyhal_uart_cfg_t
* * Configurable interrupts and callback on UART events - \ref cyhal_uart_event_t
* \section subsection_uart_interrupts Interrupts and callbacks
* Interrupts are handled by callbacks based on events \ref cyhal_uart_event_t
* If an event is disabled, the underlying interrupt is still enabled. Enabling or disabling
* an event only enables or disables the callback.
* \note Care must be exercised whenusing the \ref CYHAL_UART_IRQ_RX_NOT_EMPTY event.
* The callback must read all available received data or the interrupt will not be cleared
* leading to the callback being immediately retriggered.
* \section subsection_uart_quickstart Quick Start
* \ref cyhal_uart_init is used for UART initialization
*
* \section subsection_uart_sample_snippets Code Snippets
*
* \subsection subsection_uart_snippet_1 Snippet 1: Initialization and Configuration
* The following snippet initializes the UART block and assigns the **tx**, **rx** pins and sets the baudrate.
*
* The snippet also shows how to use \ref cyhal_uart_write, \ref cyhal_uart_putc, \ref cyhal_uart_read API.
*
* \snippet hal_uart.c snippet_cyhal_uart_init
*
* \subsection subsection_uart_snippet_2 Snippet 2: Interrupts on UART events
*
* In the following snippet, UART events are handled in a callback function.
* The callback function has to be registered and then the events have to be enabled.
*
* \snippet hal_uart.c snippet_cyhal_uart_event
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

/****************************************************************
*      Defines
*****************************************************************/

/** \addtogroup group_hal_results_uart UART HAL Results
 *  UART specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */
/** The requested resource type is invalid */
#define CYHAL_UART_RSLT_ERR_INVALID_PIN                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 0))
/** Failed to configure power management callback */
#define CYHAL_UART_RSLT_ERR_PM_CALLBACK                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 1))
/** The getc call timed out with no received data */
#define CY_RSLT_ERR_CSP_UART_GETC_TIMEOUT               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 2))
/** The actual baud rate is greater than 10% off the requested baud rate */
#define CY_RSLT_WRN_CSP_UART_BAUD_TOLERANCE             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_WARNING, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 3))
/** The requested configuration is not supported on the current hardware */
#define CYHAL_UART_RSLT_ERR_UNSUPPORTED_CONFIG          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 4))
/** The requested operation is not supported on the current hardware */
#define CYHAL_UART_RSLT_ERR_UNSUPPORTED_OPERATION       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 5))
/** Can't make changes in user-provided clock */
#define CYHAL_UART_RSLT_CLOCK_ERROR                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_UART, 6))

/**
 * \}
 */

/** The baud rate to set to if no clock is specified in the init function */
#define CYHAL_UART_DEFAULT_BAUD 115200
/** The maximum allowable difference between baud requested and actual baud **/
#define CYHAL_UART_MAX_BAUD_PERCENT_DIFFERENCE 10


/****************************************************************
*      Enumerations
*****************************************************************/


/** UART Parity */
typedef enum
{
    CYHAL_UART_PARITY_NONE,   /**< UART has no parity check   */
    CYHAL_UART_PARITY_EVEN,   /**< UART has even parity check */
    CYHAL_UART_PARITY_ODD,    /**< UART has odd parity check  */
} cyhal_uart_parity_t;

/** Enum to enable/disable/report interrupt cause flags. */
typedef enum
{
    CYHAL_UART_IRQ_NONE                = 0,      //!< No interrupt
    CYHAL_UART_IRQ_TX_TRANSMIT_IN_FIFO = 1 << 1, //!< All TX data from transmit has been moved to the HW TX FIFO buffer
    CYHAL_UART_IRQ_TX_DONE             = 1 << 2, //!< All TX data has been transmitted (applicable only for cyhal_uart_write_async)
    CYHAL_UART_IRQ_TX_ERROR            = 1 << 3, //!< An error occurred during TX
    CYHAL_UART_IRQ_RX_FULL             = 1 << 4, //!< The SW RX buffer (if used) is full. Additional data will be stored in the HW RX FIFO buffer
    CYHAL_UART_IRQ_RX_DONE             = 1 << 5, //!< All RX data has been received (applicable only for cyhal_uart_read_async)
    CYHAL_UART_IRQ_RX_ERROR            = 1 << 6, //!< An error occurred during RX
    CYHAL_UART_IRQ_RX_NOT_EMPTY        = 1 << 7, //!< The HW RX FIFO buffer is not empty
    CYHAL_UART_IRQ_TX_EMPTY            = 1 << 8, //!< The HW TX FIFO buffer is empty
    CYHAL_UART_IRQ_TX_FIFO             = 1 << 9, //!< Number of entries in the HW TX FIFO is less than the TX FIFO trigger level
    CYHAL_UART_IRQ_RX_FIFO             = 1 << 10, //!< Number of entries in the HW RX FIFO is more than the RX FIFO trigger level
} cyhal_uart_event_t;

/** UART FIFO type */
typedef enum
{
    CYHAL_UART_FIFO_RX, //!< Set RX FIFO level
    CYHAL_UART_FIFO_TX, //!< Set TX FIFO level
} cyhal_uart_fifo_type_t;

/** Enum of possible output signals from a UART */
typedef enum
{
    CYHAL_UART_OUTPUT_TRIGGER_RX_FIFO_LEVEL_REACHED, //!< Output the RX FIFO signal which is triggered when the receive FIFO has more entries than the configured level.
    CYHAL_UART_OUTPUT_TRIGGER_TX_FIFO_LEVEL_REACHED, //!< Output the TX FIFO signal which is triggered when the transmit FIFO has less entries than the configured level.
} cyhal_uart_output_t;

/****************************************************************
*      Typedef
*****************************************************************/

/** @brief Initial UART configuration */

typedef struct
{
    uint32_t data_bits;         //!< The number of data bits (generally 8 or 9)
    uint32_t stop_bits;         //!< The number of stop bits (generally 0 or 1)
    cyhal_uart_parity_t parity; //!< The parity
    uint8_t *rx_buffer;         //!< The rx software buffer pointer, if NULL, no rx software buffer will be used
    uint32_t rx_buffer_size;    //!< The number of bytes in the rx software buffer
} cyhal_uart_cfg_t;


/** UART callback function type */
typedef void (*cyhal_uart_event_callback_t)(void *callback_arg, cyhal_uart_event_t event);

/*******************************************************************************
*       Functions
*******************************************************************************/

/** Initialize the UART peripheral.
 *
 * \note This will set the baud rate to a default of \ref CYHAL_UART_DEFAULT_BAUD. This can
 * be changed by calling \ref cyhal_uart_set_baud.
 * \note Function activates the flow control feature if CTS / RTS pins are provided.
 *
 * @param[out] obj              Pointer to a UART object. The caller must allocate the memory
 * for this object but the init function will initialize its contents.
 * @param[in]  tx               The TX pin name, if no TX pin use NC
 * @param[in]  rx               The RX pin name, if no RX pin use NC
 * @param[in]  cts              The CTS pin name, if no CTS pin use NC
 * @param[in]  rts              The RTS pin name, if no RTS pin use NC
 * @param[in]  clk              The clock to use can be shared. If not provided, a new clock will be
 * allocated and the default baud rate will be set
 * @param[in]  cfg              The UART configuration data for data bits, stop bits and parity.
 * If not provided, default values of (8, 1, none) will be used
 * @return The status of the init request
 */
cy_rslt_t cyhal_uart_init(cyhal_uart_t *obj, cyhal_gpio_t tx, cyhal_gpio_t rx, cyhal_gpio_t cts, cyhal_gpio_t rts, const cyhal_clock_t *clk, const cyhal_uart_cfg_t *cfg);

/** Release the UART peripheral.
 *
 * @param[in,out] obj The UART object
 */
void cyhal_uart_free(cyhal_uart_t *obj);

/** Configure the baud rate
 *
 * @note This function should only be called if a shared clock divider is not used i.e. the clock
 *       parameter is set to NULL when calling \ref cyhal_uart_init.
 *
 * @param[in,out] obj           The UART object
 * @param[in]     baudrate      The baud rate to be configured
 * @param[out]    actualbaud    The actual baud rate achieved by the HAL
 * Specify NULL if you do not want this information.
 * @return The status of the set_baud request
 */
cy_rslt_t cyhal_uart_set_baud(cyhal_uart_t *obj, uint32_t baudrate, uint32_t *actualbaud);

/** Configure the data bits, stop bits, and parity
 *
 * @param[in,out] obj           The UART object
 * @param[in]     cfg           The UART configuration data for data bits, stop bits and parity.
 * rx_buffer and rx_buffer_size are ignored.
 * @return The status of the configure request
 */
cy_rslt_t cyhal_uart_configure(cyhal_uart_t *obj, const cyhal_uart_cfg_t *cfg);

/** Get a character. This is a blocking call which waits till a character is received.
 *
 * @param[in] obj               The UART object
 * @param[out] value            The value read from the serial port
 * @param[in] timeout           The time in ms to spend attempting to receive from serial port.
 * Zero is wait forever
 * @return The status of the getc request
 */
cy_rslt_t cyhal_uart_getc(cyhal_uart_t *obj, uint8_t *value, uint32_t timeout);

/** Send a character. This is a blocking call which waits till the character is sent out from the UART completely.
 *
 * @param[in] obj               The UART object
 * @param[in] value             The character to be sent
 * @return The status of the putc request
 */
cy_rslt_t cyhal_uart_putc(cyhal_uart_t *obj, uint32_t value);

/** Check the number of bytes available to read from the receive buffers
 *
 * @param[in]  obj              The UART object
 * @return The number of readable bytes
 */
uint32_t cyhal_uart_readable(cyhal_uart_t *obj);

/** Check the number of bytes than can be written to the transmit buffer
 *
 * @param[in]  obj              The UART object
 * @return The number of bytes that can be written
 */
uint32_t cyhal_uart_writable(cyhal_uart_t *obj);

/** Clear the UART buffers
 *
 * @param[in] obj               The UART object
 * @return The status of the clear request
 */
cy_rslt_t cyhal_uart_clear(cyhal_uart_t *obj);

/** Configure the UART for flow control. It sets flow control in the hardware
 *  if a UART peripheral supports it, otherwise software emulation is used.
 *
 * @param[in,out] obj           The UART object
 * @param[in]     enable_cts    Enable or disable CTS functionality
 * @param[in]     enable_rts    Enable or disable RTS functionality
 * @return The status of the enable_flow_control request
 */
cy_rslt_t cyhal_uart_enable_flow_control(cyhal_uart_t *obj, bool enable_cts, bool enable_rts);

/** Begin synchronous TX transfer.
 *
 * This will write either `length` bytes or until the write buffer is full, whichever is less,
 * then return. The value pointed to by `length` will be updated to reflect the number of bytes
 * that was actually written.
 *
 * @param[in]     obj           The UART object
 * @param[in]     tx            The transmit buffer
 * @param[in,out] tx_length     [in] The number of bytes to transmit, [out] number actually transmitted
 * @return The status of the tx request
 */
cy_rslt_t cyhal_uart_write(cyhal_uart_t *obj, void *tx, size_t *tx_length);

/** Begin synchronous RX transfer (enable interrupt for data collecting)
 *
 * This will read either `length` bytes or the number of bytes that are currently available in the
 * receive buffer, whichever is less, then return. The value pointed to by `length` will be updated
 * to reflect the number of bytes that was actually read.
 *
 * @param[in]     obj           The UART object
 * @param[in]     rx            The receive buffer
 * @param[in,out] rx_length     [in] The number of bytes to receive, [out] number actually received
 * @return The status of the rx request
 */
cy_rslt_t cyhal_uart_read(cyhal_uart_t *obj, void *rx, size_t *rx_length);

/** Begin asynchronous TX transfer.
 *
 * This will transfer `length` bytes into the buffer pointed to by `tx` in the background. When the
 * requested quantity of data has been transferred, the @ref CYHAL_UART_IRQ_TX_TRANSMIT_IN_FIFO event will
 * be raised. The transmit buffer is a user defined buffer that will be sent on the UART. The user
 * must register a callback with \ref cyhal_uart_register_callback. If desired, TX callback
 * events can be enabled using \ref cyhal_uart_enable_event with the appropriate events.
 *
 * @param[in] obj               The UART object
 * @param[in] tx                The transmit buffer
 * @param[in] length            The number of bytes to transmit
 * @return The status of the tx_async request
 */
cy_rslt_t cyhal_uart_write_async(cyhal_uart_t *obj, void *tx, size_t length);

/** Begin asynchronous RX transfer.
 *
 * This will transfer `length` bytes into the buffer pointed to by `rx` in the background. When the
 * requested quantity of data has been transferred, the @ref CYHAL_UART_IRQ_RX_DONE event will be raised.
 * Received data is placed in the user specified buffer. The user must register a callback with
 * \ref cyhal_uart_register_callback. RX callback events can be enabled using \ref
 * cyhal_uart_enable_event with the appropriate events.
 *
 * @param[in]  obj              The UART object
 * @param[out] rx               The user specified receive buffer
 * @param[in]  length           The number of bytes to receive
 * @return The status of the rx_async request
 */
cy_rslt_t cyhal_uart_read_async(cyhal_uart_t *obj, void *rx, size_t length);

/** Determines if the UART peripheral is currently in use for TX
 *
 * @param[in]  obj              The UART object
 * @return TX channel active status (active=true)
 */
bool cyhal_uart_is_tx_active(cyhal_uart_t *obj);

/** Determines if the UART peripheral is currently in use for RX
 *
 * @param[in]  obj              The UART object
 * @return RX channel active status (active=true)
 */
bool cyhal_uart_is_rx_active(cyhal_uart_t *obj);

/** Abort the ongoing TX transaction.
 *
 * Disables the TX interrupt and flushes the TX hardware buffer if TX FIFO is used.
 *
 * @param[in] obj               The UART object
 * @return The status of the tx_abort request
 */
cy_rslt_t cyhal_uart_write_abort(cyhal_uart_t *obj);

/** Abort the ongoing read transaction.
 *
 * Disables the RX interrupt and flushes the RX hardware buffer if RX FIFO is used.
 *
 * @param[in] obj               The UART object
 * @return The status of the read_abort request
 */
cy_rslt_t cyhal_uart_read_abort(cyhal_uart_t *obj);

/** Register a uart callback handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_uart_enable_event occurs.
 *
 * @param[in] obj               The UART object
 * @param[in] callback          The callback handler which will be invoked when the interrupt fires
 * @param[in] callback_arg      Generic argument that will be provided to the callback when called
 */
void cyhal_uart_register_callback(cyhal_uart_t *obj, cyhal_uart_event_callback_t callback, void *callback_arg);

/** Enable or disable specified UART events.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_uart_register_callback will be called.
 *
 * @param[in] obj               The UART object
 * @param[in] event             The uart event type, this argument supports the bitwise-or of multiple enum flag values
 * @param[in] intr_priority     The priority for NVIC interrupt events
 * @param[in] enable            True to turn on interrupts, False to turn off
 */
void cyhal_uart_enable_event(cyhal_uart_t *obj, cyhal_uart_event_t event, uint8_t intr_priority, bool enable);

/** Sets a threshold level for a FIFO that will generate an interrupt and a
 * trigger output.
 *
 * The RX FIFO interrupt and trigger will be activated when
 * the receive FIFO has more entries than the threshold. The TX FIFO interrupt
 * and trigger will be activated when the transmit FIFO has less entries than
 * the threshold.
 *
 * @param[in]  obj              The UART object
 * @param[in]  type             FIFO type to set level for
 * @param[in]  level            Level threshold to set
 * @return The status of the level set
 * */
cy_rslt_t cyhal_uart_set_fifo_level(cyhal_uart_t *obj, cyhal_uart_fifo_type_t type, uint16_t level);

/** Enables the specified output signal from a UART.
 *
 * @param[in]  obj              The UART object
 * @param[in]  output           Which output signal to enable
 * @param[out] source           Pointer to user-allocated source signal object
 * which will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t cyhal_uart_enable_output(cyhal_uart_t *obj, cyhal_uart_output_t output, cyhal_source_t *source);

/** Disables the specified output signal from a UART
 *
 * @param[in]  obj              The UART object
 * @param[in]  output           Which output signal to disable
 * @return The status of the output disable
 * */
cy_rslt_t cyhal_uart_disable_output(cyhal_uart_t *obj, cyhal_uart_output_t output);

/** Initialize the UART peripheral using a configurator generated configuration struct.
 *
 * @param[in]  obj              The UART peripheral to configure
 * @param[in]  cfg              Configuration structure generated by a configurator.
 * @return The status of the operation
 */
cy_rslt_t cyhal_uart_init_cfg(cyhal_uart_t *obj, const cyhal_uart_configurator_t *cfg);

/** Configure UART RX software buffer, which will extend the hardware RX FIFO buffer. \ref cyhal_uart_init function does
 * not require this function call if a non-null value was provided for `rx_buffer`.
 *
 * @param[in]  obj              The UART peripheral to configure
 * @param[in]  rx_buffer        The RX software buffer pointer
 * @param[in]  rx_buffer_size   The number of bytes in the RX software buffer
 * @return The status of the operation
 */
cy_rslt_t cyhal_uart_config_software_buffer(cyhal_uart_t *obj, uint8_t *rx_buffer, uint32_t rx_buffer_size);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_UART_IMPL_HEADER
#include CYHAL_UART_IMPL_HEADER
#endif /* CYHAL_UART_IMPL_HEADER */

/** \} group_hal_uart */
