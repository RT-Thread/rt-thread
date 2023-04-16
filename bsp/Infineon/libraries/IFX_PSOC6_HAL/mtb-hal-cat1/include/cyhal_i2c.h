/***************************************************************************//**
* \file cyhal_i2c.h
*
* \brief
* Provides a high level interface for interacting with the Infineon I2C.
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
* \addtogroup group_hal_i2c I2C (Inter-Integrated Circuit)
* \ingroup group_hal
* \{
* High level interface for interacting with the I2C resource.
*
* The I2C protocol is a synchronous serial interface protocol. This driver supports
* both master and slave mode of operation. The communication frequency and address (for slave operation) can be
* configured.
*
* \section section_i2c_features Features
*
* * Master or slave functionality
* * Configurable slave address
* * Configurable data rates
* * Configurable interrupt and callback assignment from I2C events - \ref cyhal_i2c_event_t
*
* \section section_i2c_quickstart Quick Start
* Initialize an I2C instance using the \ref cyhal_i2c_init and provide <b>sda</b> (I2C data) and <b>scl</b> (I2C clock) pins.<br>
* By default, this initializes the resource as an I2C master.<br>
* Configure the behavior (master/slave) and the interface (bus frequency, slave address) using the  \ref cyhal_i2c_configure function. <br>
* See \ref subsection_i2c_snippet_1 for example initialization as master or slave.
* \note The clock parameter (const cyhal_clock_divider_t *clk) is optional and can be set
* to NULL to generate and use an available clock resource with a default frequency (CYHAL_I2C_MASTER_DEFAULT_FREQ).
*
* \section section_i2c_snippets Code Snippets
*
* \subsection subsection_i2c_snippet_1 Snippet 1: I2C Initialization and Configuration
* This snippet initializes an I2C resource as master or slave and assigns
* the <b>sda</b> and <b>scl</b> pins.
*
* Initializing as I2C master
* \snippet hal_i2c.c snippet_cyhal_i2c_master_init
*
* Initializing as I2C slave
* \snippet hal_i2c.c snippet_cyhal_i2c_slave_init
*
* \subsection subsection_i2c_snippet_2 Snippet 2: Handling events
* This snippet shows how to enable and handle I2C events using \ref cyhal_i2c_enable_event and \ref cyhal_i2c_register_callback.<br>
* The <b>callback</b> parameter of \ref cyhal_i2c_register_callback is used to pass the callback handler that will be invoked when an event occurs.<br>
* The <b>event</b> parameter of \ref cyhal_i2c_enable_event is used to pass the bitmasks of events ( \ref cyhal_i2c_event_t) to be enabled.
*
* \snippet hal_i2c.c snippet_cyhal_handle_i2c_events
*
* \subsection subsection_i2c_snippet_3 Snippet 3: I2C Master Asynchronous Transfer
* This snippet shows how to implement asynchronous transfers using \ref cyhal_i2c_master_transfer_async.<br>
* \ref cyhal_i2c_abort_async is used to stop the transfer, in this case when an error occurs.
*
* \snippet hal_i2c.c snippet_cyhal_async_transfer
*
* \section subsection_i2c_moreinformation More Information
*
* <b>Peripheral Driver Library (PDL)</b>
* * <a href="https://infineon.github.io/psoc6pdl/pdl_api_reference_manual/html/group__group__scb.html"><b>
PSoC™ 6 PDL: SCB (Serial Communication Block)</b></a>
*
* <b>Code examples (Github)</b>
* * <a href="https://github.com/infineon/mtb-example-psoc6-i2c-master" ><b>
PSoC™ 6 MCU: I2C Master</b></a>
* * <a href="https://github.com/infineon/mtb-example-psoc6-i2c-slave-callback" ><b>
PSoC™ 6 MCU: I2C Slave Using Callbacks</b></a>
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_i2c I2C HAL Results
 *  I2C specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The requested resource type is invalid */
#define CYHAL_I2C_RSLT_ERR_INVALID_PIN                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 0))
/** Can not reach desired data rate */
#define CYHAL_I2C_RSLT_ERR_CAN_NOT_REACH_DR             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 1))
/** Address size is not correct, should be 1 or two */
#define CYHAL_I2C_RSLT_ERR_INVALID_ADDRESS_SIZE         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 2))
/** User buffer is empty (TX and RX). Should be at least TX or RX or both buffers */
#define CYHAL_I2C_RSLT_ERR_TX_RX_BUFFERS_ARE_EMPTY      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 3))
/** Previous Async operation is pending */
#define CYHAL_I2C_RSLT_ERR_PREVIOUS_ASYNCH_PENDING      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 4))
/** Failed to register I2C pm callback */
#define CYHAL_I2C_RSLT_ERR_PM_CALLBACK                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 5))
/** \ref cyhal_i2c_abort_async operation failed with timeout */
#define CYHAL_I2C_RSLT_ERR_ABORT_ASYNC_TIMEOUT          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 6))
/** Bad argument provided */
#define CYHAL_I2C_RSLT_ERR_BAD_ARGUMENT                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 7))
/** Unsupported by this device */
#define CYHAL_I2C_RSLT_ERR_UNSUPPORTED                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 8))
/** No ACK received */
#define CYHAL_I2C_RSLT_ERR_NO_ACK                       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 9))
/** Command error */
#define CYHAL_I2C_RSLT_ERR_CMD_ERROR                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 10))
/** RX or TX Buffer is not initialized */
#define CYHAL_I2C_RSLT_ERR_BUFFERS_NULL_PTR             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 11))

/** Timeout warning */
#define CYHAL_I2C_RSLT_WARN_TIMEOUT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_WARNING, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 20))
/** Other operation in progress */
#define CYHAL_I2C_RSLT_WARN_DEVICE_BUSY                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_WARNING, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_I2C, 21))

/**
 * \}
 */

/** Named define for Slave mode for use when initializing the \ref cyhal_i2c_cfg_t structure. */
#define CYHAL_I2C_MODE_SLAVE (true)
/** Named define for Master mode for use when initializing the \ref cyhal_i2c_cfg_t structure. */
#define CYHAL_I2C_MODE_MASTER (false)

/** Named define for default address mask for use when initializing the \ref cyhal_i2c_adv_cfg_t structure. */
#define CYHAL_I2C_DEFAULT_ADDR_MASK               (0xFE)


/** Enum to enable/disable/report interrupt cause flags. */
typedef enum
{
    CYHAL_I2C_EVENT_NONE               = 0,       /**< No event */
    CYHAL_I2C_SLAVE_READ_EVENT         = 1 << 1,  /**< Indicates that the slave was addressed and the master wants to read data. */
    CYHAL_I2C_SLAVE_WRITE_EVENT        = 1 << 2,  /**< Indicates that the slave was addressed and the master wants to write data. */
    CYHAL_I2C_SLAVE_RD_IN_FIFO_EVENT   = 1 << 3,  /**< All slave data from the configured Read buffer has been loaded into the TX FIFO. */
    CYHAL_I2C_SLAVE_RD_BUF_EMPTY_EVENT = 1 << 4,  /**< The master has read all data out of the configured Read buffer. */
    CYHAL_I2C_SLAVE_RD_CMPLT_EVENT     = 1 << 5,  /**< Indicates the master completed reading from the slave (set by the master NAK or Stop) */
    CYHAL_I2C_SLAVE_WR_CMPLT_EVENT     = 1 << 6,  /**< Indicates the master completed writing to the slave (set by the master Stop or Restart)*/
    CYHAL_I2C_SLAVE_ERR_EVENT          = 1 << 7,  /**< Indicates the I2C hardware detected an error. */
    CYHAL_I2C_MASTER_WR_IN_FIFO_EVENT  = 1 << 17, /**< All data specified by cyhal_i2c_master_transfer_async has been loaded into the TX FIFO. */
    CYHAL_I2C_MASTER_WR_CMPLT_EVENT    = 1 << 18, /**< The master write started by cyhal_i2c_master_transfer_async is complete.*/
    CYHAL_I2C_MASTER_RD_CMPLT_EVENT    = 1 << 19, /**< The master read started by cyhal_i2c_master_transfer_async is complete.*/
    CYHAL_I2C_MASTER_ERR_EVENT         = 1 << 20, /**< Indicates the I2C hardware has detected an error. */
} cyhal_i2c_event_t;

/** Enum to enable/disable/report address interrupt cause flags. */
typedef enum
{
    CYHAL_I2C_ADDR_EVENT_NONE    = 0,       /**< No event */
    CYHAL_I2C_GENERAL_CALL_EVENT = 1 << 1,  /**< Indicates the slave was addressed by the general call address. */
    CYHAL_I2C_ADDR_MATCH_EVENT   = 1 << 2,  /**< Indicates the slave matching address received. */
} cyhal_i2c_addr_event_t;

/** I2C FIFO type */
typedef enum
{
    CYHAL_I2C_FIFO_RX, //!< Set RX FIFO level
    CYHAL_I2C_FIFO_TX, //!< Set TX FIFO level
} cyhal_i2c_fifo_type_t;

/** I2C Command ACK / NAK */
typedef enum
{
    CYHAL_I2C_CMD_ACK, //!< Send ACK to current byte
    CYHAL_I2C_CMD_NAK, //!< Send NAK to current byte
} cyhal_i2c_command_rsp_t;

/** Enum of possible output signals from an I2C */
typedef enum
{
    CYHAL_I2C_OUTPUT_TRIGGER_RX_FIFO_LEVEL_REACHED, //!< Output the RX FIFO signal which is triggered when the receive FIFO has more entries than the configured level.
    CYHAL_I2C_OUTPUT_TRIGGER_TX_FIFO_LEVEL_REACHED, //!< Output the TX FIFO signal which is triggered when the transmit FIFO has less entries than the configured level.
} cyhal_i2c_output_t;

/** Handler for I2C events */
typedef void (*cyhal_i2c_event_callback_t)(void *callback_arg, cyhal_i2c_event_t event);
/** Handler for I2C address events */
typedef cyhal_i2c_command_rsp_t (*cyhal_i2c_address_callback_t)(void *callback_arg, cyhal_i2c_addr_event_t event, uint8_t address);

/** @brief Initial I2C configuration */
typedef struct
{
    bool is_slave;            /**<  Operates as a slave when set to (<b>true</b>), else as a master (<b>false</b>) */
    uint16_t address;         /**<  Address of this slave resource (7-bit), should be set to 0 for master */
    uint32_t frequencyhal_hz; /**<  Frequency that the I2C bus runs at (I2C data rate in bits per second) <br>
                                    Refer to the device datasheet for the supported I2C data rates */
} cyhal_i2c_cfg_t;

/** @brief I2C advanced configuration */
typedef struct
{
    cyhal_i2c_cfg_t basic_cfg;                /**<  Basic I2C configuration */
    uint8_t         address_mask;             /**<  Mask of the slave resource. Not applicable for the master. */
    bool            enable_address_callback;  /**<  Indicates address callback feature is enabled or disable.
                                                    When it's true the address callback will be invoked. */
} cyhal_i2c_adv_cfg_t;

/** Initialize the I2C peripheral, and configures its specified pins. By default
 * it is configured as a Master with a bus frequency = CYHAL_I2C_MASTER_DEFAULT_FREQ.
 * Use \ref cyhal_i2c_configure() to change the default behavior.<br>
 * NOTE: Master/Slave specific functions only work when the block is configured
 * to be in that mode.<br>
 * See \ref subsection_i2c_snippet_1
 *
 * @param[out] obj  Pointer to an I2C object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  sda The sda pin
 * @param[in]  scl The scl pin
 * @param[in]  clk The clock to use can be shared, if not provided a new clock will be allocated
 * @return The status of the init request
 *
 */
cy_rslt_t cyhal_i2c_init(cyhal_i2c_t *obj, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk);

/** Deinitialize the i2c object
 *
 * @param[in,out] obj The i2c object
 */
void cyhal_i2c_free(cyhal_i2c_t *obj);

/** Configure the I2C block.
 * NOTE: Master/Slave specific functions only work when the block is configured
 * to be in that mode.<br>
 * See \ref subsection_i2c_snippet_1
 *
 * @param[in] obj     The I2C object
 * @param[in] cfg     Configuration settings to apply
 * @return The status of the configure request
 *
 */
cy_rslt_t cyhal_i2c_configure(cyhal_i2c_t *obj, const cyhal_i2c_cfg_t *cfg);

/** Configure the I2C block with advanced parameters.
 * Refer to \ref cyhal_i2c_adv_cfg_t structure for the description of advanced parameters.
 * NOTE: Master/Slave specific functions only work when the block is configured
 * to be in that mode.<br>
 * See \ref subsection_i2c_snippet_1
 *
 * @param[in] obj   The I2C object
 * @param[in] cfg   Advanced configuration settings to apply
 * @return The status of the configure request
 *
 */
cy_rslt_t cyhal_i2c_configure_adv(cyhal_i2c_t *obj, const cyhal_i2c_adv_cfg_t *cfg);

/**
 * I2C master blocking write
 *
 * This will write `size` bytes of data from the buffer pointed to by `data`. It will not return
 * until either all of the data has been written, or the timeout has elapsed.
 *
 * @param[in]  obj        The I2C object
 * @param[in]  dev_addr   device address (7-bit)
 * @param[in]  data       I2C send data
 * @param[in]  size       I2C send data size
 * @param[in]  timeout    timeout in millisecond, set this value to 0 if you want to wait forever
 * @param[in]  send_stop  whether the stop should be send, used to support repeat start conditions
 *
 * @return The status of the master_write request
 */
cy_rslt_t cyhal_i2c_master_write(cyhal_i2c_t *obj, uint16_t dev_addr, const uint8_t *data, uint16_t size, uint32_t timeout, bool send_stop);

/**
 * I2C master blocking read
 *
 * This will read `size` bytes of data into the buffer pointed to by `data`. It will not return
 * until either all of the data has been read, or the timeout has elapsed.
 *
 * @param[in]   obj        The I2C object
 * @param[in]   dev_addr   device address (7-bit)
 * @param[out]  data       I2C receive data
 * @param[in]   size       I2C receive data size
 * @param[in]   timeout    timeout in millisecond, set this value to 0 if you want to wait forever
 * @param[in]   send_stop  whether the stop should be send, used to support repeat start conditions
 *
 * @return The status of the master_read request
 */
cy_rslt_t cyhal_i2c_master_read(cyhal_i2c_t *obj, uint16_t dev_addr, uint8_t *data, uint16_t size, uint32_t timeout, bool send_stop);

/**
 * The function configures the write buffer on an I2C Slave. This is the buffer to which the master writes data to.
 * The user needs to setup a new buffer every time (i.e. call \ref cyhal_i2c_slave_config_write_buffer and \ref cyhal_i2c_slave_config_read_buffer
 * every time the buffer has been used up)<br>
 * See related code example: <a href="https://github.com/infineon/mtb-example-psoc6-i2c-master" ><b>PSoC™ 6 MCU: I2C Master</b></a>
 *
 * @param[in]  obj      The I2C object
 * @param[in]  data     I2C slave send data
 * @param[in]  size     I2C slave send data size
 *
 * @return The status of the slave_config_write_buffer request
 */
cy_rslt_t cyhal_i2c_slave_config_write_buffer(cyhal_i2c_t *obj, const uint8_t *data, uint16_t size);

/**
 * The function configures the read buffer on an I2C Slave. This is the buffer from which the master reads data from.
 * The user needs to setup a new buffer every time (i.e. call \ref cyhal_i2c_slave_config_write_buffer and \ref cyhal_i2c_slave_config_read_buffer
 * every time the buffer has been used up)<br>
 * See related code example: <a href="https://github.com/infineon/mtb-example-psoc6-i2c-master" ><b>PSoC™ 6 MCU: I2C Master</b></a>
 *
 * @param[in]   obj      The I2C object
 * @param[out]  data     I2C slave receive data
 * @param[in]   size     I2C slave receive data size
 *
 * @return The status of the slave_config_read_buffer request
 */
cy_rslt_t cyhal_i2c_slave_config_read_buffer(cyhal_i2c_t *obj, uint8_t *data, uint16_t size);


/** Perform an I2C write using a block of data stored at the specified memory location
 *
 * @param[in]  obj            The I2C object
 * @param[in]  address        device address (7-bit)
 * @param[in]  mem_addr       mem address to store the written data
 * @param[in]  mem_addr_size  number of bytes in the mem address
 * @param[in]  data           I2C master send data
 * @param[in]  size           I2C master send data size
 * @param[in]  timeout        timeout in millisecond, set this value to 0 if you want to wait forever
 * @return The status of the write request
 */

cy_rslt_t cyhal_i2c_master_mem_write(cyhal_i2c_t *obj, uint16_t address, uint16_t mem_addr, uint16_t mem_addr_size, const uint8_t *data, uint16_t size, uint32_t timeout);

/** Perform an I2C read using a block of data stored at the specified memory location
 *
 * @param[in]  obj            The I2C object
 * @param[in]  address        device address (7-bit)
 * @param[in]  mem_addr       mem address to read the data from
 * @param[in]  mem_addr_size  number of bytes in the mem address
 * @param[out] data           I2C master receive data
 * @param[in]  size           I2C master receive data size
 * @param[in]  timeout        timeout in millisecond, set this value to 0 if you want to wait forever
 * @return The status of the read request
 */
cy_rslt_t cyhal_i2c_master_mem_read(cyhal_i2c_t *obj, uint16_t address, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *data, uint16_t size, uint32_t timeout);

/** Initiate a non-blocking I2C master asynchronous transfer. Supports simultaneous write and read operation.<br>
 *
 * This will transfer `rx_size` bytes into the buffer pointed to by `rx`, while simultaneously transfering
 * `tx_size` bytes of data from the buffer pointed to by `tx`, both in the background.
 * When the requested quantity of data has been received, the @ref CYHAL_I2C_MASTER_RD_CMPLT_EVENT will be raised.
 * When the requested quantity of data has been transmitted, the @ref CYHAL_I2C_MASTER_WR_CMPLT_EVENT will be raised.
 * See @ref cyhal_i2c_register_callback and @ref cyhal_i2c_enable_event.
 * If either of <b>tx_size</b> or <b>rx_size</b> is '0', the respective write or read operation is not performed.
 * See \ref subsection_i2c_snippet_3
 *
 * @param[in]  obj      The I2C object
 * @param[in]  address  device address (7-bit)
 * @param[in]  tx       The transmit buffer
 * @param[in]  tx_size  The number of bytes to transmit. Use '0' if write operation is not required.
 * @param[out] rx       The receive buffer
 * @param[in]  rx_size  The number of bytes to receive. Use '0' if read operation is not required.
 * @return The status of the master_transfer_async request
 *
 */
cy_rslt_t cyhal_i2c_master_transfer_async(cyhal_i2c_t *obj, uint16_t address, const void *tx, size_t tx_size, void *rx, size_t rx_size);


/** Abort asynchronous transfer.<br>
 *This function aborts the ongoing transfer by generating a stop condition.<br>
 * See \ref subsection_i2c_snippet_3
 *
 * @param[in] obj The I2C object
 * @return The status of the abort_async request
 *
 */
cy_rslt_t cyhal_i2c_abort_async(cyhal_i2c_t *obj);

/** Register an I2C event callback handler<br>
 *
 * This function will be called when one of the events enabled by \ref cyhal_i2c_enable_event occurs.
 *
 * See \ref subsection_i2c_snippet_2
 *
 * @param[in] obj          The I2C object
 * @param[in] callback     The callback handler which will be invoked when an event triggers
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 *
 */
void cyhal_i2c_register_callback(cyhal_i2c_t *obj, cyhal_i2c_event_callback_t callback, void *callback_arg);

/** Register an I2C address callback handler<br>
 *
 * This function will be called when one of the events enabled by \ref cyhal_i2c_enable_address_event occurs.
 * NOTE: This function will not have an effect if enable_address_callback parameter of
 * \ref cyhal_i2c_adv_cfg_t structure was false when \ref cyhal_i2c_configure_adv was called.
 *
 * See \ref subsection_i2c_snippet_2
 *
 * @param[in] obj          The I2C object
 * @param[in] callback     The callback handler which will be invoked when an event triggers
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 *
 */
void cyhal_i2c_register_address_callback(cyhal_i2c_t *obj, cyhal_i2c_address_callback_t callback, void *callback_arg);

/** Configure and Enable or Disable I2C Interrupt.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_i2c_register_callback will be called.
 *
 * See \ref subsection_i2c_snippet_2
 *
 * @param[in] obj            The I2C object
 * @param[in] event          The I2C event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_i2c_enable_event(cyhal_i2c_t *obj, cyhal_i2c_event_t event, uint8_t intr_priority, bool enable);

/** Configure and Enable or Disable I2C Address Interrupt.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_i2c_register_address_callback will be called.
 *
 * See \ref subsection_i2c_snippet_2
 *
 * @param[in] obj            The I2C object
 * @param[in] event          The I2C address event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_i2c_enable_address_event(cyhal_i2c_t *obj, cyhal_i2c_addr_event_t event, uint8_t intr_priority, bool enable);

/** Sets a threshold level for a FIFO that will generate an interrupt and a
 * trigger output. The RX FIFO interrupt and trigger will be activated when
 * the receive FIFO has more entries than the threshold. The TX FIFO interrupt
 * and trigger will be activated when the transmit FIFO has less entries than
 * the threshold.
 *
 * @param[in]  obj        The I2C object
 * @param[in]  type       FIFO type to set level for
 * @param[in]  level      Level threshold to set
 * @return The status of the level set
 * */
cy_rslt_t cyhal_i2c_set_fifo_level(cyhal_i2c_t *obj, cyhal_i2c_fifo_type_t type, uint16_t level);

/** Enables the specified output signal from an I2C.
 *
 * @param[in]  obj        The I2C object
 * @param[in]  output     Which output signal to enable
 * @param[out] source     Pointer to user-allocated source signal object which
 * will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
 * @return The status of the output enable
 * */
cy_rslt_t cyhal_i2c_enable_output(cyhal_i2c_t *obj, cyhal_i2c_output_t output, cyhal_source_t *source);

/** Disables the specified output signal from an I2C
 *
 * @param[in]  obj        The I2C object
 * @param[in]  output     Which output signal to disable
 * @return The status of the output disable
 * */
cy_rslt_t cyhal_i2c_disable_output(cyhal_i2c_t *obj, cyhal_i2c_output_t output);

/** Initialize the I2C peripheral using a configurator generated configuration struct.
 *
 * @param[in]  obj        The I2C peripheral to configure
 * @param[in]  cfg        Configuration structure generated by a configurator.
 * @return The status of the operation
 */
cy_rslt_t cyhal_i2c_init_cfg(cyhal_i2c_t *obj, const cyhal_i2c_configurator_t *cfg);


/** Returns the number of bytes written by the I2C master.
 * Calling the \ref cyhal_i2c_slave_config_write_buffer API will clear the counter of bytes sent by master
 *
 * @param[in]  obj          The I2C object
 * @return  The number of bytes written by the I2C master.
 * */
uint32_t cyhal_i2c_slave_readable(cyhal_i2c_t *obj);

/** Returns the number of bytes can be read by the I2C master.
 * Calling the \ref cyhal_i2c_slave_config_read_buffer API will clear the counter of bytes read by master
 *
 * @param[in]  obj          The I2C object
 * @return  The number of bytes can be read by the I2C master.
 * */
uint32_t cyhal_i2c_slave_writable(cyhal_i2c_t *obj);

/** Wait for master send data to RX buffer and store them to the user-defined buffer.
 * NOTE: If size of actual data is less then expected the function copy only available data.
 *
 * @param[in]     obj        The I2C object
 * @param[in]     dst_buff   Pointer on memory to store the data from the slave RX buffer.
 * @param[in,out] size       [in] The number of bytes to read, [out] number actually read.
 * @param[in]     timeout    Timeout in millisecond, set this value to 0 if you don't want to wait at all.
 * @return  The status of the read request
 * */
cy_rslt_t cyhal_i2c_slave_read(cyhal_i2c_t *obj, uint8_t *dst_buff, uint16_t *size, uint32_t timeout);

/** Write data from the user-defined buffer to I2C TX buffer.
 * NOTE: If size of actual data is less then expected the function copy only available data.
 *
 * @param[in]     obj        The I2C object
 * @param[in]     src_buff   Pointer on memory to copy the data to the slave TX buffer.
 * @param[in,out] size       [in] The number of bytes to send, [out] number actually sent.
 * @param[in]     timeout    Timeout in millisecond,  set this value to 0 if you don't want to wait at all.
 * @return  The status of the write request
 * */
cy_rslt_t cyhal_i2c_slave_write(cyhal_i2c_t *obj, const uint8_t *src_buff, uint16_t *size, uint32_t timeout);

/**
 * The function aborts the configured slave read buffer to be read by the master.
 * If the master reads and "abort operation" is requested, the
 * \ref CYHAL_I2C_SLAVE_RD_BUF_EMPTY_EVENT event occurs.
 *
 * @param[in]  obj                The I2C object
 *
 * @return The status of the slave_abort_read request
 */
cy_rslt_t cyhal_i2c_slave_abort_read(cyhal_i2c_t *obj);

/** Clear the I2C buffers
 *
 * @param[in]  obj        The I2C object
 * @return The status of the clear request
 * */
cy_rslt_t cyhal_i2c_clear(cyhal_i2c_t *obj);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_I2C_IMPL_HEADER
#include CYHAL_I2C_IMPL_HEADER
#endif /* CYHAL_I2C_IMPL_HEADER */

/** \} group_hal_i2c */
