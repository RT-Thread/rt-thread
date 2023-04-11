/***************************************************************************//**
* \file cyhal_ezi2c.h
*
* \brief
* Provides a high level interface for interacting with the Infineon EZI2C.
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
* \addtogroup group_hal_ezi2c EZI2C (Inter-Integrated Circuit)
* \ingroup group_hal
* \{
* High level interface for interacting with the Cypress EZ Inter-Integrated Circuit (EZI2C).
* The EZI2C driver implements an I2C slave device that emulates a common I2C EEPROM interface between
* the external master and your application code. EZI2C Slave buffers can be set up as any variable, array,
* or structure in your code without worrying about the I2C protocol. I2C related transactions and processing
* of data from the I2C master are handled by the driver through internal interrupt routine, reducing application
* involvement to maintain the I2C buffer.
*
* \section subsection_ezi2c_features Features
* * EZI2C Slave functionality
* * Configurable standard data rates of 100/400/1000 kbps - \ref cyhal_ezi2c_data_rate_t
* * Supports one or two addresses with independent memory buffers - \ref cyhal_ezi2c_cfg_t
* * Memory buffers provide configurable read/write and read only regions - \ref cyhal_ezi2c_cfg_t
* * 8 or 16-bit sub-addressing - \ref cyhal_ezi2c_sub_addr_size_t
* * Configurable interrupt and callback assignment from EZI2C events - \ref cyhal_ezi2c_event_t
*
* \section section_ezi2c_quickstart Quick Start
* Initialize EZI2C by using \ref cyhal_ezi2c_init and selecting the <b>sda</b> and <b>scl</b> pins.
* Setup one or two memory buffers and read/write boundaries using the EZI2C configuration
* structure \ref cyhal_ezi2c_cfg_t.
* See \ref subsection_ezi2c_snippet_1
* \note The clock parameter <b>clk</b> is optional and can be set to NULL to generate and use an
* available clock resource.
*
* \section section_ezi2c_snippets Code snippets
*
* \subsection subsection_ezi2c_snippet_1 Snippet 1: EZI2C Initialization and Configuration
* The following snippet shows how to initialize and configure an EZI2C and assign the pins to the <b>sda</b> and <b>scl</b> lines.
* The <b>clk</b> need not be provided (NULL), in which case a clock resource is assigned.
*
* \snippet hal_ezi2c.c snippet_cyhal_ezi2c_init
*
* \subsection subsection_ezi2c_snippet_2 Snippet 2: Register Callback function
* The following snippet shows how to use the \ref cyhal_ezi2c_register_callback function. The <b>callback</b> parameter
* refers to the handler which will be invoked when an event triggers.
*
* \snippet hal_ezi2c.c snippet_cyhal_ezi2c_handler
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_ezi2c EZI2C HAL Results
 *  EZI2C specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The requested resource type is invalid */
#define CYHAL_EZI2C_RSLT_ERR_INVALID_PIN                \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_EZI2C, 0))
/** Can not reach desired data rate */
#define CYHAL_EZI2C_RSLT_ERR_CAN_NOT_REACH_DR           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_EZI2C, 1))
/** Number of addresses is not valid */
#define CYHAL_EZI2C_RSLT_ERR_NUM_ADDR_NOT_VALID         \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_EZI2C, 2))
/** Number of addresses is not valid */
#define CYHAL_EZI2C_RSLT_ERR_CHECK_USER_CONFIG          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_EZI2C, 3))

/**
 * \}
 */

/** CYHAL_EZI2C_EVENT_NONE event is deprecated and that CYHAL_EZI2C_STATUS_OK should be used instead */
#define CYHAL_EZI2C_EVENT_NONE CYHAL_EZI2C_STATUS_OK

/** Size of Sub-Address */
typedef enum
{
    CYHAL_EZI2C_SUB_ADDR8_BITS,    /**< Sub-address is 8 bits  */
    CYHAL_EZI2C_SUB_ADDR16_BITS    /**< Sub-address is 16 bits */
} cyhal_ezi2c_sub_addr_size_t;

/** Data rate of the slave */
typedef enum
{
    CYHAL_EZI2C_DATA_RATE_100KHZ = 100000,
    CYHAL_EZI2C_DATA_RATE_400KHZ = 400000,
    CYHAL_EZI2C_DATA_RATE_1MHZ   = 1000000
} cyhal_ezi2c_data_rate_t;

/** Return codes of ezi2c */
typedef enum
{
    /** Each EZI2C slave status is encoded in a separate bit, therefore multiple bits may be set to indicate the current status */
    CYHAL_EZI2C_STATUS_OK     = 0x1UL,   /**< Operation completed successfully */
    CYHAL_EZI2C_STATUS_READ1  = 0x2UL,  /**< The Read transfer intended for the primary slave address is complete */
    CYHAL_EZI2C_STATUS_WRITE1 = 0x4UL,  /**< The Write transfer intended for the primary slave address is complete */
    CYHAL_EZI2C_STATUS_READ2  = 0x8UL,  /**< The Read transfer intended for the secondary slave address is complete */
    CYHAL_EZI2C_STATUS_WRITE2 = 0x10UL,  /**< The Write transfer intended for the secondary slave address is complete */
    CYHAL_EZI2C_STATUS_BUSY   = 0x20UL,  /**< A transfer intended for the primary address or secondary address is in progress */
    CYHAL_EZI2C_STATUS_ERR    = 0x40UL   /**< An error occurred during a transfer intended for the primary or secondary slave address */

} cyhal_ezi2c_status_t;

/** This type is deprecated and that cyhal_ezi2c_status_t should be used instead */
typedef cyhal_ezi2c_status_t cyhal_ezi2c_event_t;

/** Handler for I2C events */
typedef void (*cyhal_ezi2c_event_callback_t)(void *callback_arg, cyhal_ezi2c_status_t event);

/** Initial EZI2C sub configuration */
typedef struct
{
    /** The 7-bit right justified primary slave address */
    uint8_t slave_address;
    /** A pointer to the data buffer for the primary/secondary slave address */
    uint8_t *buf;
    /** The size of the buffer assigned to the primary/secondary slave address */
    uint32_t buf_size;
    /** The Read/Write boundary within the buffer assigned to the primary/secondary slave address.
    * This specifies the number of data bytes from the beginning of the buffer with
    * read and write access for the master. Data bytes at this value or greater are read
    * only by the master */
    uint32_t buf_rw_boundary;
} cyhal_ezi2c_slave_cfg_t;

/** Initial EZI2C configuration */
typedef struct
{
    /** Number of addresses (one or two). If set "true" - use two addresses otherwise ("false") one */
    bool two_addresses;
    /** When set, the slave will wake the device from Deep Sleep on an address match */
    bool enable_wake_from_sleep;
    /** Maximum frequency that the I2C Slave bus runs at. Supports standard data rates of 100/400/1000 kbps */
    cyhal_ezi2c_data_rate_t data_rate;
    /** Refer to cyhal_ezi2c_slave_cfg_t for details. This config structure is mandatory. */
    cyhal_ezi2c_slave_cfg_t slave1_cfg;
    /** Refer to cyhal_ezi2c_slave_cfg_t for details. This config structure is optional. */
    /** Set it if user want to use dual-port addressing otherwise leave blank */
    cyhal_ezi2c_slave_cfg_t slave2_cfg;
    /** The size of the sub-address, can either be 8 or 16 bits */
    cyhal_ezi2c_sub_addr_size_t sub_address_size;
} cyhal_ezi2c_cfg_t;


/** Initialize the EZI2C (slave), and configures its specified pins and clock.
 * See \ref subsection_ezi2c_snippet_1
 *
 * @param[out] obj  Pointer to an EZI2C object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  sda The sda pin
 * @param[in]  scl The scl pin
 * @param[in]  clk The clock to use can be shared, if NULL a new clock will be allocated
 * @param[in]  cfg The ezi2c configuration (refer to cyhal_ezi2c_cfg_t for details)
 * @return The status of the init request
 */
cy_rslt_t cyhal_ezi2c_init(cyhal_ezi2c_t *obj, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk, const cyhal_ezi2c_cfg_t *cfg);

/** Deinitialize the ezi2c object
 *
 * @param[in,out] obj The ezi2c object
 */
void cyhal_ezi2c_free(cyhal_ezi2c_t *obj);

/**
 * EZI2C slave get activity status
 * This function returns a non-zero value ( \ref cyhal_ezi2c_status_t) if an I2C Read or Write
 * cycle has occurred since the last time this function was called.
 * See \ref subsection_ezi2c_snippet_2
 *
 * @param[in] obj The EZI2C object
 *
 * @return The status of the EZI2C (see cyhal_ezi2c_status_t for details)
 */
cyhal_ezi2c_status_t cyhal_ezi2c_get_activity_status(cyhal_ezi2c_t *obj);

/** Register a EZI2C event callback handler
 *
 * See \ref subsection_ezi2c_snippet_2
 *
 * @param[in] obj          The EZI2C object
 * @param[in] callback     The callback handler which will be invoked when an event triggers
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_ezi2c_register_callback(cyhal_ezi2c_t *obj, cyhal_ezi2c_event_callback_t callback, void *callback_arg);

/** Configure and Enable or Disable EZI2C Interrupt.
 *
 * @param[in] obj            The EZI2C object
 * @param[in] event          The EZI2C event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on interrupts, False to turn off
 */
void cyhal_ezi2c_enable_event(cyhal_ezi2c_t *obj, cyhal_ezi2c_status_t event, uint8_t intr_priority, bool enable);

/** Initialize the EZI2C peripheral using a configurator generated configuration struct and set up slave address(es) data.
 *
 * @param[in] obj            The EZI2C peripheral to configure
 * @param[in] cfg            Configuration structure generated by a configurator.
 * @param[in] slave1_cfg     Primary slave address configuration
 * @param[in] slave2_cfg     Secondary slave address configuration (can be NULL)
 * @return The status of the operation
 */
cy_rslt_t cyhal_ezi2c_init_cfg(cyhal_ezi2c_t *obj, const cyhal_ezi2c_configurator_t *cfg, const cyhal_ezi2c_slave_cfg_t *slave1_cfg, const cyhal_ezi2c_slave_cfg_t *slave2_cfg);

#if defined(__cplusplus)
}
#endif

/** \} group_hal_ezi2c */
