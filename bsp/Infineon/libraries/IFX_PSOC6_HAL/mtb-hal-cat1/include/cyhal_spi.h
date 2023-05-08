/***************************************************************************//**
* \file cyhal_spi.h
*
* \brief
* Provides a high level interface for interacting with the Infineon SPI.
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
* \addtogroup group_hal_spi SPI (Serial Peripheral Interface)
* \ingroup group_hal
* \{
* High level interface for interacting with the Serial Peripheral Interface (SPI).
*
* The SPI protocol is a synchronous serial interface protocol. Devices operate
* in either master or slave mode. The master initiates the data transfer.
*
* Motorola SPI modes 0, 1, 2, and 3 are supported, with either MSB or LSB first.
* The operating mode and data frame size can be configured via \ref cyhal_spi_cfg_t.
*
* \section section_spi_features Features
* * Supports master and slave functionality.
* * Supports Motorola modes - 0, 1, 2 and 3 - \ref cyhal_spi_mode_t
* * MSb or LSb first shift direction - \ref cyhal_spi_mode_t
* * Master supports up to four slave select lines
* * Supports data frame size of 8 or 16 bits
* * Configurable interrupt and callback assignment on SPI events:
* Data transfer to FIFO complete, Transfer complete and Transmission error - \ref cyhal_spi_event_t
* * Supports changing baud rate of the transaction in run time.
* * Provides functions to send/receive a single byte or block of data.
*
* \section section_spi_quickstart Quick Start
*
* Initialise a SPI master or slave interface using \ref cyhal_spi_init() and provide the SPI pins (<b>mosi</b>, <b>miso</b>, <b>sclk</b>, <b>ssel</b>),
* number of bits per frame (<b>data_bits</b>) and SPI Motorola <b>mode</b>. The data rate can be set using \ref cyhal_spi_set_frequency(). <br>
* See \ref section_spi_snippets for code snippets to send or receive the data.
*
* \section section_spi_snippets Code snippets
*
* \subsection subsection_spi_snippet_1 Snippet 1: SPI Master - Single byte transfer operation (Read and Write)
* The following code snippet initializes an SPI Master interface using the \ref cyhal_spi_init(). The data rate of transfer is set using \ref cyhal_spi_set_frequency().
* The code snippet shows how to transfer a single byte of data using \ref cyhal_spi_send() and \ref cyhal_spi_recv().
* \snippet hal_spi.c snippet_cyhal_spi_master_byte_operation
*
* \subsection subsection_spi_snippet_2 Snippet 2: SPI Slave - Single byte transfer operation (Read and Write)
* The following code snippet initializes an SPI Slave interface using the \ref cyhal_spi_init(). The data rate of transfer is set using \ref cyhal_spi_set_frequency.
* The code snippet shows how to transfer a single byte of data using \ref cyhal_spi_send() and \ref cyhal_spi_recv.
* \snippet hal_spi.c snippet_cyhal_spi_slave_byte_operation
*
* \subsection subsection_spi_snippet_3 Snippet 3: SPI Block Data transfer
* The following snippet sends and receives an array of data in a single SPI transaction using \ref cyhal_spi_transfer(). The example
* uses SPI master to transmit 5 bytes of data and receive 5 bytes of data in a single transaction.
* \snippet hal_spi.c snippet_cyhal_spi_block_data_transfer
*
* \subsection subsection_spi_snippet_4 Snippet 4: Interrupts on SPI events
* SPI interrupt events ( \ref cyhal_spi_event_t) can be mapped to an interrupt and assigned to a callback function.
* The callback function needs to be first registered and then the event needs to be enabled.
* The following snippet initialises a SPI master to perform a block transfer using \ref cyhal_spi_transfer_async(). This is a non-blocking function.
*  A callback function is registered using \ref cyhal_spi_register_callback to notify whenever the SPI transfer is complete.
* \snippet hal_spi.c snippet_cyhal_spi_interrupt_callback_events

* \section subsection_spi_moreinfor More Information
*
* * <a href="https://github.com/infineon/mtb-example-psoc6-spi-master"><b>mtb-example-psoc6-spi-master</b></a>: This example project demonstrates
* use of SPI (HAL) resource in PSoCÂ® 6 MCU in Master mode to write data to an SPI slave.
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

/** \addtogroup group_hal_results_spi SPI HAL Results
 *  SPI specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bad argument */
#define CYHAL_SPI_RSLT_BAD_ARGUMENT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 0))
/** Failed to initialize SPI clock or can't make changes in user-provided clock */
#define CYHAL_SPI_RSLT_CLOCK_ERROR                      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 1))
/** Failed to Transfer SPI data */
#define CYHAL_SPI_RSLT_TRANSFER_ERROR                   \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 2))
/** Provided clock is not supported by SPI */
#define CYHAL_SPI_RSLT_CLOCK_NOT_SUPPORTED              \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 3))
/** Provided PIN configuration is not supported by SPI */
#define CYHAL_SPI_RSLT_PIN_CONFIG_NOT_SUPPORTED         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 5))
/** Provided PIN configuration is not supported by SPI */
#define CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 6))
/** The requested resource type is invalid */
#define CYHAL_SPI_RSLT_ERR_INVALID_PIN                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 7))
/** Cannot configure SSEL signal */
#define CYHAL_SPI_RSLT_ERR_CANNOT_CONFIG_SSEL           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 8))
/** Cannot switch SSEL - device is busy or incorrect pin provided */
#define CYHAL_SPI_RSLT_ERR_CANNOT_SWITCH_SSEL           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 9))
/** Provided configuration is not supported */
#define CYHAL_SPI_RSLT_ERR_CFG_NOT_SUPPORTED            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 10))
/** Unsupported by this device */
#define CYHAL_SPI_RSLT_ERR_UNSUPPORTED                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 11))

/** Timeout warning */
#define CYHAL_SPI_RSLT_WARN_TIMEOUT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_WARNING, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SPI, 20))

/**
 * \}
 */

/** Compatibility define for cyhal_spi_set_frequency. */
#define cyhal_spi_frequency cyhal_spi_set_frequency

/** SPI interrupt triggers */
typedef enum {
    /** All transfer data has been moved into data FIFO */
    CYHAL_SPI_IRQ_DATA_IN_FIFO        = 1 << 1,
    /** Transfer complete. */
    CYHAL_SPI_IRQ_DONE                = 1 << 2,
    /** An error occurred while transferring data */
    CYHAL_SPI_IRQ_ERROR               = 1 << 3,
} cyhal_spi_event_t;

/** SPI Slave Select polarity */
typedef enum {
    /** SSEL signal is active low */
    CYHAL_SPI_SSEL_ACTIVE_LOW         = 0,
    /** SSEL signal is active high */
    CYHAL_SPI_SSEL_ACTIVE_HIGH        = 1,
} cyhal_spi_ssel_polarity_t;

/** Handler for SPI interrupts */
typedef void (*cyhal_spi_event_callback_t)(void *callback_arg, cyhal_spi_event_t event);

/** Flag for SPI \ref cyhal_spi_mode_t values indicating that the LSB is sent first. */
#define CYHAL_SPI_MODE_FLAG_LSB             (0x01u)
/** Flag for SPI \ref cyhal_spi_mode_t values indicating that the CPHA=1. */
#define CYHAL_SPI_MODE_FLAG_CPHA            (0x02u)
/** Flag for SPI \ref cyhal_spi_mode_t values indicating that the CPOL=1. */
#define CYHAL_SPI_MODE_FLAG_CPOL            (0x04u)
/** Creates a \ref cyhal_spi_mode_t value given the cpol, cpha, lsb values. */
#define CYHAL_SPI_MODE(cpol, cpha, lsb)     ((((cpol) > 0) ? CYHAL_SPI_MODE_FLAG_CPOL : 0) | \
                                             (((cpha) > 0) ? CYHAL_SPI_MODE_FLAG_CPHA : 0) | \
                                              (((lsb) > 0) ? CYHAL_SPI_MODE_FLAG_LSB  : 0))

/** SPI operating modes */
typedef enum
{
    /** Standard motorola SPI CPOL=0, CPHA=0 with MSB first operation */
    CYHAL_SPI_MODE_00_MSB = CYHAL_SPI_MODE(0, 0, 0),
    /** Standard motorola SPI CPOL=0, CPHA=0 with LSB first operation */
    CYHAL_SPI_MODE_00_LSB = CYHAL_SPI_MODE(0, 0, 1),
    /** Standard motorola SPI CPOL=0, CPHA=1 with MSB first operation */
    CYHAL_SPI_MODE_01_MSB = CYHAL_SPI_MODE(0, 1, 0),
    /** Standard motorola SPI CPOL=0, CPHA=1 with LSB first operation */
    CYHAL_SPI_MODE_01_LSB = CYHAL_SPI_MODE(0, 1, 1),
    /** Standard motorola SPI CPOL=1, CPHA=0 with MSB first operation */
    CYHAL_SPI_MODE_10_MSB = CYHAL_SPI_MODE(1, 0, 0),
    /** Standard motorola SPI CPOL=1, CPHA=0 with LSB first operation */
    CYHAL_SPI_MODE_10_LSB = CYHAL_SPI_MODE(1, 0, 1),
    /** Standard motorola SPI CPOL=1, CPHA=1 with MSB first operation */
    CYHAL_SPI_MODE_11_MSB = CYHAL_SPI_MODE(1, 1, 0),
    /** Standard motorola SPI CPOL=1, CPHA=1 with LSB first operation */
    CYHAL_SPI_MODE_11_LSB = CYHAL_SPI_MODE(1, 1, 1),
} cyhal_spi_mode_t;

/** SPI FIFO type */
typedef enum
{
    CYHAL_SPI_FIFO_RX, //!< Set RX FIFO level
    CYHAL_SPI_FIFO_TX, //!< Set TX FIFO level
} cyhal_spi_fifo_type_t;

/** Enum of possible output signals from an SPI */
typedef enum
{
    CYHAL_SPI_OUTPUT_TRIGGER_RX_FIFO_LEVEL_REACHED, //!< Output the RX FIFO signal which is triggered when the receive FIFO has more entries than the configured level.
    CYHAL_SPI_OUTPUT_TRIGGER_TX_FIFO_LEVEL_REACHED, //!< Output the TX FIFO signal which is triggered when the transmit FIFO has less entries than the configured level.
} cyhal_spi_output_t;

/** @brief Initial SPI configuration. */
typedef struct
{
    cyhal_spi_mode_t mode; //!< The operating mode
    uint8_t data_bits; //!< The number of bits per transfer
    bool is_slave; //!< Whether the peripheral is operating as slave or master
} cyhal_spi_cfg_t;

/** Initialize the SPI peripheral.
 *
 * Configures the pins used by SPI, sets a default format and frequency, and enables the peripheral.
 * Depending on the configuration, some pins may not be needed.
 * Master mode: MOSI used, MISO unused: SCLK & SSEL are both optional
 * Master mode: MISO used, MOSI unused: SCLK is mandatory, SSEL is optional
 * Slave  mode: MOSI or MISO are used:  SCLK & SSEL are both mandatory
 *
 * @param[out] obj  Pointer to a SPI object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  mosi The pin to use for MOSI
 * @note At least MOSI or MISO pin should be non-NC
 * @param[in]  miso The pin to use for MISO
 * @note At least MOSI or MISO pin should be non-NC
 * @param[in]  sclk The pin to use for SCLK
 * @note This pin can be NC if in master mode with only MOSI used
 * @param[in]  ssel The pin to use for SSEL
 * @note Provided pin will be configured for \ref CYHAL_SPI_SSEL_ACTIVE_LOW polarity and set as active. This can be changed
 * (as well as additional ssel pins can be added) by \ref cyhal_spi_slave_select_config and \ref cyhal_spi_select_active_ssel
 * functions. This pin can be NC.
 * @param[in]  clk The clock to use can be shared, if not provided a new clock will be allocated
 * @param[in]  bits      The number of bits per frame
 * @note \ref section_hal_impl_spi_data_width describes what data width options are supported by certain hardware
 * @param[in]  mode      The SPI mode (clock polarity, phase, and shift direction)
 * @param[in]  is_slave  false for master mode or true for slave mode operation
 * @return The status of the init request
 */
cy_rslt_t cyhal_spi_init(cyhal_spi_t *obj, cyhal_gpio_t mosi, cyhal_gpio_t miso, cyhal_gpio_t sclk, cyhal_gpio_t ssel,
                         const cyhal_clock_t *clk, uint8_t bits, cyhal_spi_mode_t mode, bool is_slave);

/** Release a SPI object
 *
 * Return the peripheral, pins and clock owned by the SPI object to their reset state
 * @param[in,out] obj The SPI object to deinitialize
 */
void cyhal_spi_free(cyhal_spi_t *obj);

/** Set the SPI baud rate
 *
 * Actual frequency may differ from the desired frequency due to available dividers and bus clock
 * Configures the SPI peripheral's baud rate
 * @param[in,out] obj The SPI object to configure
 * @param[in]     hz  The baud rate in Hz
 * @return The status of the set_frequency request
 */
cy_rslt_t cyhal_spi_set_frequency(cyhal_spi_t *obj, uint32_t hz);

/** Configures provided ssel pin to work as SPI slave select with specified polarity.
 *
 * Multiple pins can be configured as SPI slave select pins. Please refer to device datasheet for details. Switching
 * between configured slave select pins is done by \ref cyhal_spi_select_active_ssel function.
 * Unless modified with this function, the SSEL pin provided as part of \ref cyhal_spi_init is the default.
 * @param[in] obj       The SPI object to add slave select for
 * @param[in] ssel      Slave select pin to be added
 * @param[in] polarity  Polarity of slave select
 * @return The status of ssel pin configuration
 */
cy_rslt_t cyhal_spi_slave_select_config(cyhal_spi_t *obj, cyhal_gpio_t ssel, cyhal_spi_ssel_polarity_t polarity);

/** Selects an active slave select line from one of available.
 *
 * This function is applicable for the master and slave.
 * SSEL pin should be configured by \ref cyhal_spi_slave_select_config or \ref cyhal_spi_init functions prior
 * to selecting it as active. The active slave select line will automatically be toggled as part of any transfer.
 * @param[in] obj       The SPI object for switching
 * @param[in] ssel      Slave select pin to be set as active
 * @return CY_RSLT_SUCCESS if slave select was switched successfully, otherwise - CYHAL_SPI_RSLT_ERR_CANNOT_SWITCH_SSEL
 */
cy_rslt_t cyhal_spi_select_active_ssel(cyhal_spi_t *obj, cyhal_gpio_t ssel);

/** Synchronously get a received value out of the SPI receive buffer
 *
 * In Master mode - transmits fill-in value and read the data from RxFifo
 * In Slave mode - Blocks until a value is available
 *
 * @param[in] obj   The SPI peripheral to read
 * @param[in] value The value received
 * @return The status of the read request
 * @note
 * - In Master mode, MISO pin required to be non-NC for this API to operate
 * - In Slave mode, MOSI pin required to be non-NC for this API to operate
 */
cy_rslt_t cyhal_spi_recv(cyhal_spi_t *obj, uint32_t* value);

/** Synchronously send a byte out
 *
 * In Master mode transmits value to slave and read/drop a value from the RxFifo.
 * In Slave mode writes a value to TxFifo
 *
 * @param[in] obj   The SPI peripheral to use for sending
 * @param[in] value The value to send
 * @return The status of the write request
 * @note
 * - In Master mode, MOSI pin required to be non-NC for this API to operate
 * - In Slave mode, MISO pin required to be non-NC for this API to operate
 */
cy_rslt_t cyhal_spi_send(cyhal_spi_t *obj, uint32_t value);

/** Wait for master send data to RX buffer and store them to the user-defined buffer.
 * NOTE: If size of actual data is less then expected the function copy only available data.
 *
 * @param[in]     obj        The SPI object
 * @param[in]     dst_buff   Pointer on memory to store the data from the slave RX buffer.
 * @param[in,out] size       [in] The number of bytes to read, [out] number actually read.
 * @param[in]     timeout    Timeout in millisecond, set this value to 0 if you don't want to wait at all.
 * @return  The status of the read request
 * */
cy_rslt_t cyhal_spi_slave_read(cyhal_spi_t *obj, uint8_t *dst_buff, uint16_t *size, uint32_t timeout);

/** Write data from the user-defined buffer to TX buffer.
 * NOTE: If size of actual data is less then expected the function copy only available data.
 *
 * @param[in]     obj        The SPI object
 * @param[in]     src_buff   Pointer on memory to copy the data to the slave TX buffer.
 * @param[in,out] size       [in] The number of bytes to send, [out] number actually sent.
 * @param[in]     timeout    Timeout in millisecond,  set this value to 0 if you don't want to wait at all.
 * @return  The status of the write request
 * */
cy_rslt_t cyhal_spi_slave_write(cyhal_spi_t *obj, const uint8_t *src_buff, uint16_t *size, uint32_t timeout);


/** Returns the number of bytes that can be read from the RX buffer.
 *
 * @param[in]  obj          The SPI object
 * @return  The number of bytes in the RX buffer.
 * */
uint32_t cyhal_spi_readable(cyhal_spi_t *obj);

/** Returns the number of bytes that can be written to the TX buffer.
 *
 * @param[in]  obj          The SPI object
 * @return  The number of bytes that can be written
 * */
uint32_t cyhal_spi_writable(cyhal_spi_t *obj);

/** Synchronously Write a block out and receive a value
 *
 *  The total number of bytes sent and received will be the maximum of tx_length
 *  and rx_length. The bytes written will be padded (at the end) with the value
 *  given by write_fill.
 *
 * This function will block for the duration of the transfer. \ref cyhal_spi_transfer_async
 * can be used for non-blocking transfers.
 *
 * @param[in] obj           The SPI peripheral to use for sending
 * @param[in] tx            Pointer to the byte-array of data to write to the device
 * @param[in,out] tx_length Number of bytes to write, updated with the number actually written
 * @param[out] rx           Pointer to the byte-array of data to read from the device
 * @param[in,out] rx_length Number of bytes to read, updated with the number actually read
 * @param[in] write_fill    Default data transmitted while performing a read
 * @return The status of the transfer request
 * @note Both MOSI and MISO pins required to be non-NC for this API to operate
 */
cy_rslt_t cyhal_spi_transfer(cyhal_spi_t *obj, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length, uint8_t write_fill);

/** Start an asynchronous SPI transfer.
 *
 * This will transfer `rx_length` bytes into the buffer pointed to by `rx`, while simultaneously transfering
 * `tx_length` bytes of data from the buffer pointed to by `tx`, both in the background.
 * When the transfer is complete, the @ref CYHAL_SPI_IRQ_DONE event will be raised.
 * See @ref cyhal_spi_register_callback and @ref cyhal_spi_enable_event.
 * \note For blocking transfers cyhal_spi_transfer can be used.
 *
 * @param[in] obj           The SPI object that holds the transfer information
 * @param[in] tx            The transmit buffer
 * @param[in,out] tx_length The number of bytes to transmit
 * @param[out] rx           The receive buffer
 * @param[in,out] rx_length The number of bytes to receive
 * @return The status of the transfer_async request
 * @note Both MOSI and MISO pins required to be non-NC for this API to operate
 */
cy_rslt_t cyhal_spi_transfer_async(cyhal_spi_t *obj, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length);

/** Checks if the specified SPI peripheral is in use
 *
 * @param[in] obj  The SPI peripheral to check
 * @return Indication of whether the SPI is still transmitting
 */
bool cyhal_spi_is_busy(cyhal_spi_t *obj);

/** Abort an SPI transfer
 *
 * @param[in] obj The SPI peripheral to stop
 * @return The status of the abort_async request
 */
cy_rslt_t cyhal_spi_abort_async(cyhal_spi_t *obj);

/** Register a SPI callback handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_spi_enable_event occurs.
 *
 * @param[in] obj          The SPI object
 * @param[in] callback     The callback handler which will be invoked when the interrupt fires
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_spi_register_callback(cyhal_spi_t *obj, cyhal_spi_event_callback_t callback, void *callback_arg);

/** Configure SPI interrupt. This function is used for word-approach
 *
 * When an enabled event occurs, the function specified by \ref cyhal_spi_register_callback will be called.
 *
 * @param[in] obj            The SPI object
 * @param[in] event          The SPI event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_spi_enable_event(cyhal_spi_t *obj, cyhal_spi_event_t event, uint8_t intr_priority, bool enable);

/** Sets a threshold level for a FIFO that will generate an interrupt and a
 * trigger output. The RX FIFO interrupt and trigger will be activated when
 * the receive FIFO has more entries than the threshold. The TX FIFO interrupt
 * and trigger will be activated when the transmit FIFO has less entries than
 * the threshold.
 *
 * @param[in]  obj        The SPI object
 * @param[in]  type       FIFO type to set level for
 * @param[in]  level      Level threshold to set
 * @return The status of the level set
 * */
cy_rslt_t cyhal_spi_set_fifo_level(cyhal_spi_t *obj, cyhal_spi_fifo_type_t type, uint16_t level);

/** Enables the specified output signal from an SPI.
 *
 * @param[in]  obj        The SPI object
 * @param[in]  output     Which output signal to enable
 * @param[out] source     Pointer to user-allocated source signal object which
 * will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t cyhal_spi_enable_output(cyhal_spi_t *obj, cyhal_spi_output_t output, cyhal_source_t *source);

/** Disables the specified output signal from an SPI
 *
 * @param[in]  obj        The SPI object
 * @param[in]  output     Which output signal to disable
 * @return The status of the output disable
 * */
cy_rslt_t cyhal_spi_disable_output(cyhal_spi_t *obj, cyhal_spi_output_t output);

/** Initialize the SPI peripheral using a configurator generated configuration struct.
 *
 * @param[in]  obj                  The SPI peripheral to configure
 * @param[in]  cfg                  Configuration structure generated by a configurator.
 * @return The status of the operation
 */
cy_rslt_t cyhal_spi_init_cfg(cyhal_spi_t *obj, const cyhal_spi_configurator_t *cfg);

/** Clear the SPI buffers
 *
 * @param[in]  obj        The SPI object
 * @return The status of the clear request
 * */
cy_rslt_t cyhal_spi_clear(cyhal_spi_t *obj);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_SPI_IMPL_HEADER
#include CYHAL_SPI_IMPL_HEADER
#endif /* CYHAL_SPI_IMPL_HEADER */

/** \} group_hal_spi */
