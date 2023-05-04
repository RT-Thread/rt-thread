/***************************************************************************//**
* \file cyhal_qspi.h
*
* \brief
* Provides a high level interface for interacting with the Infineon Quad-SPI.
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
* \addtogroup group_hal_qspi QSPI (Quad Serial Peripheral Interface)
* \ingroup group_hal
* \{
* High level interface for interacting with the Quad-SPI interface.
*
* QSPI is an SPI-based communication interface, often used with external memory devices.
* The QSPI driver supports sending and receiving commands to/from from another
* device via a single, dual, quad, or octal SPI interface.
*
* \section subsection_qspi_features Features
* * Standard SPI Master interface
* * Supports Single/Dual/Quad/Octal SPI memories
* * Supports Dual-Quad SPI mode
* * Execute-In-Place (XIP) from external Quad SPI Flash
* * Supports external serial memory initialization via Serial Flash Discoverable Parameters (SFDP) standard
*
* \section subsection_qspi_code_snippets Code Snippets
* \note The following snippets show commands specific to the
* <a href="https://www.cypress.com/documentation/datasheets/s25fl512s-512-mbit-64-mbyte-30v-spi-flash-memory">S25FL512S Cypress NOR Flash device</a>.
* Refer to the datasheet of the external memory device for device specific memory commands.
* \subsection subsection_qspi_snippet_1 Code Snippet 1: Initializing the cyhal_qspi_command_t structure
* The following code snip demonstrates an example for initializing the cyhal_qspi_command_t structure for
* any given flash command. The cyhal_qspi_command_t.mode_bits structure has several other components which should
* be set as per the command. Mode bits are not required for single SPI read command, hence, mode_bits.disabled
* is set to TRUE in the below example code.
* \snippet hal_qspi.c snippet_cyhal_qspi_structure_initialisation
* \subsection subsection_qspi_snippet_2 Code Snippet 2: QSPI initialization and Reading Flash memory
* This example function demonstrates the initialization of the QSPI component and use of the cyhal_qspi_read() function
* to complete the read operation and receive the read data in a buffer.
* \snippet hal_qspi.c snippet_cyhal_qspi_read
* \subsection subsection_qspi_snippet_3 Code Snippet 3: Erasing Flash memory
* The following code snippet demonstrates the use of cyhal_qspi_transfer() API for sending single byte instruction
* that may or may not need any address or data bytes. It also shows the usage of status register read command within
* a while loop to poll the WIP bit status.
* \snippet hal_qspi.c snippet_cyhal_qspi_erase
* \note Flash memories need erase operation before programming.
* \subsection subsection_qspi_snippet_4 Code Snippet 4: Programming Flash memory
* This code snippet demonstrates the usage cyhal_qspi_write() API for executing program operation on flash memory.
* \snippet hal_qspi.c snippet_cyhal_qspi_program
* \subsection subsection_qspi_snippet_5 Code Snippet 5: Configuring multiple memories
* This code snippet demonstrates the usage cyhal_qspi_slave_configure() and cyhal_qspi_select_active_ssel() API for
* for initialization environment for additional (additional to one, that was initialized in scope of cyhal_qspi_init())
* QSPI memory and switching between memories.
* \snippet hal_qspi.c snippet_cyhal_qspi_multiple_memories
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_qspi QSPI HAL Results
 *  QSPI specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bus width Error. */
#define CYHAL_QSPI_RSLT_ERR_BUS_WIDTH                   \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 0))
/** Pin related Error. */
#define CYHAL_QSPI_RSLT_ERR_PIN                         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 1))
/** Data select Error. */
#define CYHAL_QSPI_RSLT_ERR_DATA_SEL                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 2))
/** QSPI instance related error. */
#define CYHAL_QSPI_RSLT_ERR_INSTANCE                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 3))
/** Clock frequency error. */
#define CYHAL_QSPI_RSLT_ERR_FREQUENCY                   \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 4))
/** Waiting for certain event error. */
#define CYHAL_QSPI_RSLT_ERR_TIMEOUT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 5))
/** Cannot configure SSEL signal */
#define CYHAL_QSPI_RSLT_ERR_CANNOT_CONFIG_SSEL          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 6))
/** Cannot switch to specified SSEL signal */
#define CYHAL_QSPI_RSLT_ERR_CANNOT_SWITCH_SSEL          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 7))
/** Data rate error. */
#define CYHAL_QSPI_RSLT_ERR_DATARATE                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 8))
/** Instruction error. */
#define CYHAL_QSPI_RSLT_ERR_INSTRUCTION                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 9))
/** Dummy cycles error. */
#define CYHAL_QSPI_RSLT_ERR_DUMMY_CYCLES                \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 10))
/** Cannot make changes in user provided clock configuration or provided clock is incorrect. */
#define CYHAL_QSPI_RSLT_ERR_CLOCK                       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 11))
/** Requested feature is not supported by this driver. */
#define CYHAL_QSPI_RSLT_ERR_UNSUPPORTED                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_QSPI, 12))

/**
 * \}
 */

/** QSPI Bus width. Some parts of commands provide variable bus width. */

typedef enum cyhal_qspi_bus_width
{
    CYHAL_QSPI_CFG_BUS_SINGLE       = 1,            /**< Normal SPI Mode */
    CYHAL_QSPI_CFG_BUS_DUAL         = 2,            /**< Dual SPI Mode */
    CYHAL_QSPI_CFG_BUS_QUAD         = 4,            /**< Quad SPI Mode */
    CYHAL_QSPI_CFG_BUS_OCTAL        = 8,            /**< Octal SPI Mode */
} cyhal_qspi_bus_width_t;

/** Address size in bits */
typedef enum cyhal_qspi_size
{
    CYHAL_QSPI_CFG_SIZE_8           = 8,            /**< 8 bits address */
    CYHAL_QSPI_CFG_SIZE_16          = 16,           /**< 16 bits address */
    CYHAL_QSPI_CFG_SIZE_24          = 24,           /**< 24 bits address */
    CYHAL_QSPI_CFG_SIZE_32          = 32,           /**< 32 bits address */
} cyhal_qspi_size_t;

/** QSPI interrupt triggers */
typedef enum
{
    CYHAL_QSPI_EVENT_NONE           = 0,            /**< No event */
    CYHAL_QSPI_IRQ_TRANSMIT_DONE    = 1 << 0,       /**< Async transmit done */
    CYHAL_QSPI_IRQ_RECEIVE_DONE     = 1 << 1,       /**< Async receive done */
} cyhal_qspi_event_t;

/** QSPI data rate */
typedef enum
{
    CYHAL_QSPI_DATARATE_SDR         = 0,            /**< Single data rate */
    CYHAL_QSPI_DATARATE_DDR         = 1,            /**< Double data rate */
} cyhal_qspi_datarate_t;

/** @brief QSPI command settings */
typedef struct cyhal_qspi_command
{
    struct
    {
        cyhal_qspi_bus_width_t  bus_width;      /**< Bus width for the instruction */
        cyhal_qspi_datarate_t   data_rate;      /**< Data rate SDR/DDR */
        bool                    two_byte_cmd;   /**< Defines whether cmd is 2-byte value, or 1-byte (if false) */
        uint16_t                value;          /**< Instruction value */
        bool                    disabled;       /**< Instruction phase skipped if disabled is set to true */
    } instruction;                              /**< Instruction structure */
    struct
    {
        cyhal_qspi_bus_width_t  bus_width;      /**< Bus width for the address */
        cyhal_qspi_datarate_t   data_rate;      /**< Data rate SDR/DDR */
        cyhal_qspi_size_t       size;           /**< Address size */
        /* Address is specified as argument for write/read functions */
        bool                    disabled;       /**< Address phase skipped if disabled is set to true */
    } address;                                  /**< Address structure */
    struct
    {
        cyhal_qspi_bus_width_t  bus_width;      /**< Bus width for mode bits  */
        cyhal_qspi_datarate_t   data_rate;      /**< Data rate SDR/DDR */
        cyhal_qspi_size_t       size;           /**< Mode bits size */
        uint32_t                value;          /**< Mode bits value */
        bool                    disabled;       /**< Mode bits phase skipped if disabled is set to true */
    } mode_bits;                                /**< Mode bits structure */
    struct
    {
        cyhal_qspi_bus_width_t  bus_width;      /**< Bus width for mode bits  */
        cyhal_qspi_datarate_t   data_rate;      /**< Data rate SDR/DDR */
        uint32_t                dummy_count;    /**< Dummy cycles count */
    } dummy_cycles;                             /**< Dummy cycles structure */
    struct
    {
        cyhal_qspi_bus_width_t  bus_width;      /**< Bus width for data */
        cyhal_qspi_datarate_t   data_rate;      /**< Data rate SDR/DDR */
    } data;                                     /**< Data structure */
} cyhal_qspi_command_t;

/** @brief QSPI slave pin set. Each pin set should represent the pins connected to a single slave memory device.
 * Pin io[0] is data[0] signal of the memory (and not necessarily data[0] of underlying QSPI hardware block),
 * io[1] is the memory IC's data[1] and so on. The ssel is the pin connected to the memory chip's select signal.
 * The number of data pins configured should match the maximum \ref cyhal_qspi_bus_width_t for transfers. */
typedef struct cyhal_qspi_slave_pin_config
{
    cyhal_gpio_t io[8];                         /**< IOx lines of connected memory */
    cyhal_gpio_t ssel;                          /**< Slave Select line of connected memory */
} cyhal_qspi_slave_pin_config_t;

/** Handler for QSPI callbacks */
typedef void (*cyhal_qspi_event_callback_t)(void *callback_arg, cyhal_qspi_event_t event);


/** Initialize QSPI peripheral.
 *
 * It should initialize QSPI pins (io0-io7, sclk and ssel), set frequency, clock polarity and phase mode.
 *  The clock for the peripheral should be enabled
 *
 * @param[out] obj      Pointer to a QSPI object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  sclk     The clock pin
 * @param[in]  pin_set  Set of pins, that will primarily be used for communication with memory. Depends on device,
 * QSPI HAL can service multiple memories which can be registered and controlled using \ref cyhal_qspi_slave_configure and
 * \ref cyhal_qspi_select_active_ssel functions. There is no need to call \ref cyhal_qspi_select_active_ssel after
 * this function - provided ssel pin as part of pin_set parameter become active.
 * @param[in]  hz       The bus frequency
 * @param[in]  mode     Clock polarity and phase mode (0 - 3)
 * @param[in]  clk      The clock to use can be shared, if not provided a new clock will be allocated
 * @note QSPI HAL cannot make changes into provided clock configuration. In this case \ref cyhal_qspi_set_frequency function
 * cannot be used and will return error once called. With provided clock only user application can configure QSPI bus frequency by
 * configuring parameters of shared clock.
 * @return The status of the init request
 */
cy_rslt_t cyhal_qspi_init(
    cyhal_qspi_t *obj, cyhal_gpio_t sclk, const cyhal_qspi_slave_pin_config_t *pin_set, uint32_t hz, uint8_t mode,
    cyhal_clock_t *clk);

/** Initialize the QSPI peripheral using a configurator generated configuration struct. This function may not support all
 * features, that can be configured via configurator. For limitations list please refer to \ref section_hal_impl_qspi_init_cfg section.
 *
 * @param[in]  obj                  The QSPI peripheral to configure
 * @param[in]  cfg                  Configuration structure generated by a configurator.
 * @return The status of the operation
 */
cy_rslt_t cyhal_qspi_init_cfg(cyhal_qspi_t *obj, const cyhal_qspi_configurator_t *cfg);

/** Deinitilize QSPI peripheral
 *
 * It should release pins that are associated with the QSPI object, and disable clocks for QSPI peripheral module
 *  that was associated with the object
 *
 * @param[in,out] obj QSPI object
 */
void cyhal_qspi_free(cyhal_qspi_t *obj);

/** Set the QSPI baud rate
 *
 * Actual frequency may differ from the desired frequency due to available dividers and the bus clock. Function will
 * apply achieved frequency only if it is in +0% /-10% deviation bounds from desired.
 * Use @ref cyhal_qspi_get_frequency function to get actual frequency value that was achieved and set.
 *
 * @param[in] obj The QSPI object to configure
 * @param[in] hz  The baud rate in Hz
 * @return The status of the set_frequency request
 */
cy_rslt_t cyhal_qspi_set_frequency(cyhal_qspi_t *obj, uint32_t hz);

/** Get the actual frequency that QSPI is configured for
 *
 * @param[in] obj The QSPI object
 * @return Frequency in Hz
 */
uint32_t cyhal_qspi_get_frequency(cyhal_qspi_t *obj);

/** Configure provided set of pins to service additional slave memory.
 *
 * Multiple pins can be configured as QSPI slave select pins as well as IO pins may be (or may not be) shared and used
 * to service multiple connected slave memories. This function can be called multiple times - each call for each additional
 * slave memory. Please refer to device datasheet for details.
 * Switching between configured slave select pins is done by \ref cyhal_qspi_select_active_ssel function.
 * Unless modified with this function, the SSEL pin provided as part of \ref cyhal_qspi_init is the default.
 * Please refer to \ref subsection_qspi_snippet_5 for example of configuration multiple memory devices and switching between
 * them.
 * \note Provided IO pins can overlap with those, that are configured in scope of \ref cyhal_qspi_init function.
 * @param[in] obj       The QSPI object to configure
 * @param[in] pin_set   Set of pins, that will be used to service additional slave memory.
 * @return The status of pin configuration
 */
cy_rslt_t cyhal_qspi_slave_configure(cyhal_qspi_t *obj, const cyhal_qspi_slave_pin_config_t *pin_set);

/** Selects an active slave select (SSEL) line from one of available and previously configured.
 *
 * Slave memories (in addition to one, that was configured in scope of \ref cyhal_qspi_init) can be added with help of
 * \ref cyhal_qspi_slave_configure function.
 * @param[in] obj   The QSPI object to configure
 * @param[in] ssel  SSEL pin to be set as active
 * @return CY_RSLT_SUCCESS if slave select was switched successfully, otherwise - CYHAL_QSPI_RSLT_ERR_CANNOT_SWITCH_SSEL
 */
cy_rslt_t cyhal_qspi_select_active_ssel(cyhal_qspi_t *obj, cyhal_gpio_t ssel);

/** Receive a command and block of data, synchronously.
 *
 * This will read either `length` bytes or the number of bytes that are currently available in the
 * receive buffer, whichever is less, then return. The value pointed to by `length` will be updated
 * to reflect the number of bytes that were actually read.
 *
 * @param[in]  obj      QSPI object
 * @param[in]  command  QSPI command
 * @param[in]  address  Address to access to
 * @param[out] data     RX buffer
 * @param[in]  length   RX buffer length in bytes
 * @return The status of the read request
 */
cy_rslt_t cyhal_qspi_read(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, void *data, size_t *length);

/** Receive a command and block of data in asynchronous mode.
 *
 * This will transfer `length` bytes into the buffer pointed to by `data` in the background. When the
 * requested quantity of data has been read, the @ref CYHAL_QSPI_IRQ_RECEIVE_DONE event will be raised.
 * See @ref cyhal_qspi_register_callback and @ref cyhal_qspi_enable_event.
 *
 * @param[in]  obj      QSPI object
 * @param[in]  command  QSPI command
 * @param[in]  address  Address to access to
 * @param[out] data     RX buffer
 * @param[in]  length   RX buffer length in bytes
 * @return The status of the read request
 */
cy_rslt_t cyhal_qspi_read_async(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, void *data, size_t *length);

/** Send a command and block of data, synchronously.
 *
 * This will write either `length` bytes or until the write buffer is full, whichever is less,
 * then return. The value pointed to by `length` will be updated to reflect the number of bytes
 * that were actually written.
 *
 * @param[in] obj      QSPI object
 * @param[in] command  QSPI command
 * @param[in] address  Address to access to
 * @param[in] data     TX buffer
 * @param[in] length   TX buffer length in bytes
 * @return The status of the write request
 */
cy_rslt_t cyhal_qspi_write(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, const void *data, size_t *length);

/** Send a command and block of data in asynchronous mode.
 *
 * This will transfer `length` bytes into the tx buffer in the background. When the requested
 * quantity of data has been queued in the transmit buffer, the @ref CYHAL_QSPI_IRQ_TRANSMIT_DONE
 * event will be raised. See @ref cyhal_qspi_register_callback and @ref cyhal_qspi_enable_event.
 *
 * @param[in] obj      QSPI object
 * @param[in] command  QSPI command
 * @param[in] address  Address to access to
 * @param[in] data     TX buffer
 * @param[in] length   TX buffer length in bytes
 * @return The status of the write request
 */
cy_rslt_t cyhal_qspi_write_async(cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, const void *data, size_t *length);

/** Send a command (and optionally data) and get the response. Can be used to send/receive device specific commands
 *
 * @param[in]  obj      QSPI object
 * @param[in]  command  QSPI command
 * @param[in]  address  Address to access to
 * @param[in]  tx_data  TX buffer
 * @param[in]  tx_size  TX buffer length in bytes
 * @param[out] rx_data  RX buffer
 * @param[in]  rx_size  RX buffer length in bytes
 * @return The status of the transfer request
 */
cy_rslt_t cyhal_qspi_transfer(
    cyhal_qspi_t *obj, const cyhal_qspi_command_t *command, uint32_t address, const void *tx_data, size_t tx_size,
    void *rx_data, size_t rx_size
);

/** Register a QSPI event handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_qspi_enable_event occurs.
 *
 * @param[in] obj          The QSPI object
 * @param[in] callback     The callback handler which will be invoked when the interrupt fires
 * @param[in] callback_arg Generic argument that will be provided to the handler when called
 */
void cyhal_qspi_register_callback(cyhal_qspi_t *obj, cyhal_qspi_event_callback_t callback, void *callback_arg);

/** Configure QSPI interrupt enablement.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_qspi_register_callback will be called.
 *
 * @param[in] obj            The QSPI object
 * @param[in] event          The QSPI event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_qspi_enable_event(cyhal_qspi_t *obj, cyhal_qspi_event_t event, uint8_t intr_priority, bool enable);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_QSPI_IMPL_HEADER
#include CYHAL_QSPI_IMPL_HEADER
#endif /* CYHAL_QSPI_IMPL_HEADER */

/** \} group_hal_qspi */
