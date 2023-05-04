/***************************************************************************//**
* \file cyhal_sdio.h
*
* \brief
* Provides a high level interface for interacting with the Infineon SDIO interface.
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
* \addtogroup group_hal_sdio SDIO (Secure Digital Input Output)
* \ingroup group_hal
* \{
* High level interface to the Secure Digital Input Output (SDIO).
*
* This driver allows commands to be sent over the SDIO bus; the supported commands
* can be found in \ref cyhal_sdio_command_t. Bulk data transfer is also supported
* via cyhal_sdio_bulk_transfer().
*
* The SDIO protocol is an extension of the SD
* interface for general I/O functions. Refer to the SD Specifications Part 1 SDIO
* Specifications Version 4.10 for more information on the SDIO protocol and specifications.
*
*
* \section subsection_sdio_features Features
* * Supports 4-bit interface
* * Supports Ultra High Speed (UHS-I) mode
* * Supports Default Speed (DS), High Speed (HS), SDR12, SDR25 and SDR50 speed modes
* * Supports SDIO card interrupts in both 1-bit and 4-bit modes
* * Supports Standard capacity (SDSC), High capacity (SDHC) and Extended capacity (SDXC) memory
*
* \section subsection_sdio_quickstart Quick Start
*
* \ref cyhal_sdio_init initializes the SDIO peripheral and passes a pointer to the SDIO block through the **obj** object of type \ref cyhal_sdio_t.
*
* \section subsection_sdio_code_snippets Code Snippets
*
* \subsection subsection_sdio_use_case_1 Snippet1: Simple SDIO Initialization example
* The following snippet shows how to initialize the SDIO interface with a pre-defined configuration
*
* \snippet hal_sdio.c snippet_cyhal_sdio_simple_init
*
* \subsection subsection_sdio_use_case_2 Snippet2: Configure Interrupt
* The following snippet shows how to configure an interrupt and handle specific events. Refer \ref cyhal_sdio_event_t for different types of events.
*
* \snippet hal_sdio.c snippet_cyhal_sdio_interrupt_callback
*
* \subsection subsection_sdio_use_case_3 Snippet3: Sending Commands
* The following snippet shows how to send a particular command. Some steps of the card initialization have been provided for reference. Refer \ref cyhal_sdio_command_t for different commands.
*
* \snippet hal_sdio.c snippet_cyhal_sdio_send_command
*
* \subsection subsection_sdio_use_case_4 Snippet4: Bulk Data Transfer
* The following snippet shows how to start a bulk data transfer.
*
* \snippet hal_sdio.c snippet_cyhal_sdio_bulk_transfer
*
* \subsection subsection_sdio_use_case_5 Snippet5: Async Data Transfer
*
* The following snippet shows how to start an async data transfer.
* \snippet hal_sdio.c snippet_cyhal_sdio_async_transfer
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*       Defines
*******************************************************************************/

/* HAL return value defines */

/** \addtogroup group_hal_results_sdio SDIO HAL Results
 *  SDIO specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Incorrect parameter value define */
#define CYHAL_SDIO_RSLT_ERR_BAD_PARAM                   \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 0))
/** Define to indicate canceled operation */
#define CYHAL_SDIO_RSLT_CANCELED                        \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 1))
/** Transfers are not allowed after the SDIO block has allowed power mode transition. */
#define CYHAL_SDIO_RSLT_ERR_PM_PENDING                  \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 2))
/** Requested feature is not supported on this hardware. */
#define CYHAL_SDIO_RSLT_ERR_UNSUPPORTED                 \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 3))
/** Failure in command send. */
#define CYHAL_SDIO_RSLT_ERR_COMMAND_SEND               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 4))
/** SDIO Configuration error. */
#define CYHAL_SDIO_RSLT_ERR_CONFIG                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 5))
/** Another SDIO IO volt select pin already configured. */
#define CYHAL_SDIO_RSLT_ERR_IO_VOLT_SEL_PIN_CONFIGURED \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 6))
/** Error occured during I/O voltage switch sequence. */
#define CYHAL_SDIO_RSLT_ERR_IO_VOLT_SWITCH_SEQ          \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 7))
/** Clock initialization error define */
#define CYHAL_SDIO_RSLT_ERR_CLOCK                       \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_SDIO, 7))

/**
 * \}
 */


/*******************************************************************************
*       Enumerations
*******************************************************************************/

/** Commands that can be issued */
typedef enum
{
    CYHAL_SDIO_CMD_GO_IDLE_STATE      =  0, //!< Go to idle state
    CYHAL_SDIO_CMD_SEND_RELATIVE_ADDR =  3, //!< Send a relative address
    CYHAL_SDIO_CMD_IO_SEND_OP_COND    =  5, //!< Send an OP IO
    CYHAL_SDIO_CMD_SELECT_CARD        =  7, //!< Send a card select
    CYHAL_SDIO_CMD_VOLTAGE_SWITCH     = 11, //!< Voltage switch
    CYHAL_SDIO_CMD_GO_INACTIVE_STATE  = 15, //!< Go to inactive state
    CYHAL_SDIO_CMD_IO_RW_DIRECT       = 52, //!< Perform a direct read/write
    CYHAL_SDIO_CMD_IO_RW_EXTENDED     = 53, //!< Perform an extended read/write
} cyhal_sdio_command_t;

/** Types of transfer that can be performed */
typedef enum
{
    CYHAL_SDIO_XFER_TYPE_READ, //!< Read from the card
    CYHAL_SDIO_XFER_TYPE_WRITE //!< Write to the card
} cyhal_sdio_transfer_type_t;

/** Types of events that could be asserted by SDIO */
typedef enum {
    /* Interrupt-based thread events */
    CYHAL_SDIO_CMD_COMPLETE   = 0x00001,  //!< Command Complete
    CYHAL_SDIO_XFER_COMPLETE  = 0x00002,  //!< Host read/write transfer is complete
    CYHAL_SDIO_BGAP_EVENT     = 0x00004,  //!< This bit is set when both read/write transaction is stopped
    CYHAL_SDIO_DMA_INTERRUPT  = 0x00008,  //!< Host controller detects an SDMA Buffer Boundary during transfer
    CYHAL_SDIO_BUF_WR_READY   = 0x00010,  //!< This bit is set if the Buffer Write Enable changes from 0 to 1
    CYHAL_SDIO_BUF_RD_READY   = 0x00020,  //!< This bit is set if the Buffer Read Enable changes from 0 to 1
    CYHAL_SDIO_CARD_INSERTION = 0x00040,  //!< This bit is set if the Card Inserted in the Present State
    CYHAL_SDIO_CARD_REMOVAL   = 0x00080,  //!< This bit is set if the Card Inserted in the Present State
    CYHAL_SDIO_CARD_INTERRUPT = 0x00100,  //!< The synchronized value of the DAT[1] interrupt input for SD mode
    CYHAL_SDIO_INT_A          = 0x00200,  //!< Reserved: set to 0
    CYHAL_SDIO_INT_B          = 0x00400,  //!< Reserved: set to 0
    CYHAL_SDIO_INT_C          = 0x00800,  //!< Reserved: set to 0
    CYHAL_SDIO_RE_TUNE_EVENT  = 0x01000,  //!< Reserved: set to 0
    CYHAL_SDIO_FX_EVENT       = 0x02000,  //!< This status is set when R[14] of response register is set to 1
    CYHAL_SDIO_CQE_EVENT      = 0x04000,  //!< This status is set if Command Queuing/Crypto event has occurred
    CYHAL_SDIO_ERR_INTERRUPT  = 0x08000,  //!< If any of the bits in the Error Interrupt Status register are set

    /* Non-interrupt-based thread events */
    CYHAL_SDIO_GOING_DOWN     = 0x10000, //!< The interface is going away (eg: powering down for some period of time)
    CYHAL_SDIO_COMING_UP      = 0x20000, //!< The interface is back up (eg: came back from a low power state)

    CYHAL_SDIO_ALL_INTERRUPTS = 0x0E1FF,  //!< Is used to enable/disable all interrupts events
} cyhal_sdio_event_t;

/** I/O voltage levels */
typedef enum
{
    CYHAL_SDIO_IO_VOLTAGE_3_3V                  = 0U,   //!< I/O voltage is 3.3V.
    CYHAL_SDIO_IO_VOLTAGE_1_8V                  = 1U    //!< I/O voltage is 1.8V.
} cyhal_sdio_io_voltage_t;

/** SDIO I/O voltage select principle */
typedef enum
{
    CYHAL_SDIO_IO_VOLT_ACTION_SWITCH_SEQ_ONLY   = 1U,   //!< HAL driver performs switching sequence (if voltage is being switched to 1.8V) and changes io_volt_sel pin level accordingly. No commands are being send to the card in this mode.
    CYHAL_SDIO_IO_VOLT_ACTION_NONE              = 2U,   //!< I/O voltage is changed by changing io_volt_sel pin's level. No commands are being send to the card in this mode.
} cyhal_sdio_io_volt_action_type_t;

/*******************************************************************************
*       Data Structures
*******************************************************************************/

/** @brief SDIO controller initial configuration */
typedef struct
{
    uint32_t frequencyhal_hz; //!< Clock frequency, in hertz
    uint16_t block_size;      //!< Block size
} cyhal_sdio_cfg_t;

/** Callback for SDIO events */
typedef void (*cyhal_sdio_event_callback_t)(void *callback_arg, cyhal_sdio_event_t event);


/*******************************************************************************
*       Data Structures
*******************************************************************************/
/** Initialize the SDIO peripheral
 *
 * @param[out] obj                Pointer to an SDIO object.
 *  The caller must allocate the memory for this object but the init
 *  function will initialize its contents.
 * @param[out] clk               The pin connected to the clk signal
 * @param[in]  cmd               The pin connected to the command signal
 * @param[in]  data0             The pin connected to the data0 signal
 * @param[in]  data1             The pin connected to the data1 signal
 * @param[in]  data2             The pin connected to the data2 signal
 * @param[in]  data3             The pin connected to the data3 signal
 * @return The status of the init request
 *
 * Returns \ref CY_RSLT_SUCCESS on successful operation. Refer \ref subsection_sdio_use_case_1 for more information.
 */
cy_rslt_t cyhal_sdio_init(cyhal_sdio_t *obj, cyhal_gpio_t cmd, cyhal_gpio_t clk, cyhal_gpio_t data0, cyhal_gpio_t data1, cyhal_gpio_t data2, cyhal_gpio_t data3);

/** Release the SDIO block.
 *
 * @param[in,out] obj The SDIO object
 */
void cyhal_sdio_free(cyhal_sdio_t *obj);

/** Configure the SDIO block with required parameters. Refer \ref cyhal_sdio_cfg_t for more information.
 *
 * @param[in,out] obj    The SDIO object
 * @param[in]     config The SDIO configuration to apply
 * @return The status of the configure request.
 *
 * Returns \ref CY_RSLT_SUCCESS on successful operation.
 */
cy_rslt_t cyhal_sdio_configure(cyhal_sdio_t *obj, const cyhal_sdio_cfg_t *config);

/** Sends command to the SDIO device. See \ref cyhal_sdio_command_t for list of available commands.
 *
 * This will block until the command is completed.
 *
 * @param[in,out] obj       The SDIO object
 * @param[in]     direction The direction of transfer (read/write)
 * @param[in]     command   The command to send to the SDIO device
 * @param[in]     argument  The argument to the command
 * @param[out]    response  The response from the SDIO device
 * @return The status of the command transfer.
 *
 * Returns \ref CY_RSLT_SUCCESS on successful operation. Refer \ref subsection_sdio_use_case_3 for more information.
 */
cy_rslt_t cyhal_sdio_send_cmd(cyhal_sdio_t *obj, cyhal_sdio_transfer_type_t direction, cyhal_sdio_command_t command, uint32_t argument, uint32_t* response);

/** Performs a bulk data transfer. Sends \ref CYHAL_SDIO_CMD_IO_RW_EXTENDED command (CMD=53) which allows writing and reading of a large number of I/O registers with a single command.
 *
 * This will block until the transfer is completed.
 *
 * @param[in,out] obj       The SDIO object
 * @param[in]     direction The direction of transfer (read/write)
 * @param[in]     argument  The argument to the command
 * @param[in]     data      The data to send to the SDIO device. A bulk transfer is done in block
 *                          size (default: 64 bytes) chunks for better performance. Therefore,
 *                          the size of the data buffer passed into this function must be at least
 *                          `length` bytes and a multiple of the block size. For example, when
 *                          requesting to read 100 bytes of data with a block size 64 bytes, the
 *                          data buffer needs to be at least 128 bytes. The first 100 bytes of data
 *                          in the buffer will be the requested data.
 * @param[in]     length    The number of bytes to send
 * @param[out]    response  The response from the SDIO device
 * @return The status of the bulk transfer operation.
 *
 * Returns \ref CY_RSLT_SUCCESS on successful operation. Refer \ref subsection_sdio_use_case_4 for more information.
 */
cy_rslt_t cyhal_sdio_bulk_transfer(cyhal_sdio_t *obj, cyhal_sdio_transfer_type_t direction, uint32_t argument, const uint32_t* data, uint16_t length, uint32_t* response);

/** Performs a bulk asynchronous data transfer by issuing the \ref CYHAL_SDIO_CMD_IO_RW_EXTENDED command(CMD=53) to the SDIO block.
 * After exiting this function the \ref CYHAL_SDIO_CMD_COMPLETE and \ref CYHAL_SDIO_XFER_COMPLETE events are not asserted.
 *
 * The \ref CYHAL_SDIO_CMD_COMPLETE and \ref CYHAL_SDIO_XFER_COMPLETE events are enabled
 * after the asynchronous transfer is complete and in the condition they were
 * enabled in before the transfer operation started. Handle these events in the interrupt callback.
 *
 * When the transfer is complete, the \ref CYHAL_SDIO_XFER_COMPLETE event will be raised.
 * See \ref cyhal_sdio_register_callback and \ref cyhal_sdio_enable_event.
 *
 * @param[in,out] obj       The SDIO object
 * @param[in]     direction The direction of transfer (read/write)
 * @param[in]     argument  The argument to the command
 * @param[in]     data      The data to send to the SDIO device
 * @param[in]     length    The number of bytes to send
 * @return The status of the async tranfer operation.
 *
 * Returns \ref CY_RSLT_SUCCESS on successful operation. Refer \ref subsection_sdio_use_case_5 for more information.
 */
cy_rslt_t cyhal_sdio_transfer_async(cyhal_sdio_t *obj, cyhal_sdio_transfer_type_t direction, uint32_t argument, const uint32_t* data, uint16_t length);

/** Checks if the specified SDIO is in use
 *
 * @param[in]  obj  The SDIO peripheral to check
 * @return true if SDIO is in use. false, otherwise.
 */
bool cyhal_sdio_is_busy(const cyhal_sdio_t *obj);

/** Abort an SDIO transfer
 *
 * @param[in] obj The SDIO peripheral to stop
 * @return The status of the abort_async request.
 *
 * Returns \ref CY_RSLT_SUCCESS on successful operation.
 */
cy_rslt_t cyhal_sdio_abort_async(cyhal_sdio_t *obj);

/** Register an SDIO event callback to be invoked when the event is triggered.
 *
 * This function will be called when one of the events enabled by \ref cyhal_sdio_enable_event occurs.
 *
 * @param[in] obj          The SDIO object
 * @param[in] callback     The callback function which will be invoked when the event triggers
 * @param[in] callback_arg Generic argument that will be provided to the callback when executed
 *
 * Refer \ref subsection_sdio_use_case_2 for more implementation.
 */
void cyhal_sdio_register_callback(cyhal_sdio_t *obj, cyhal_sdio_event_callback_t callback, void *callback_arg);

/** Enables callbacks to be triggered for specified SDIO events. Refer \ref cyhal_sdio_event_t for all events.
 *
 * @param[in] obj           The SDIO object
 * @param[in] event         The SDIO event type
 * @param[in] intr_priority The priority for NVIC interrupt events
 * @param[in] enable        Set to true to enable events, or false to disable them
 *
 * Refer \ref subsection_sdio_use_case_2 for more information.
 */
void cyhal_sdio_enable_event(cyhal_sdio_t *obj, cyhal_sdio_event_t event, uint8_t intr_priority, bool enable);

/** Sets the voltage level of the I/O lines.
 *
 * @param[in]  obj                  The SDIO object
 * @param[in]  io_volt_sel          The pin connected to the io_volt_sel signal. This pin changes the logic level on the
 *  sd_io_volt_sel line. It assumes that this line is used to control a regulator connected to the VDDIO of the MCU.
 *  This regulator allows for switching between the 3.3V and 1.8V signaling. High level on the pin stands for
 *  1.8V signaling, while low - for 3.3V.
 *  This pin can be NC.
 * @param[in]  io_voltage           I/O voltage to be set on lines
 * @param[in]  io_switch_type       Defines how I/O voltage will be switched
 * @return The status of the operation
 */
cy_rslt_t cyhal_sdio_set_io_voltage(cyhal_sdio_t *obj, cyhal_gpio_t io_volt_sel, cyhal_sdio_io_voltage_t io_voltage,
                                    cyhal_sdio_io_volt_action_type_t io_switch_type);

/** Initialize the SDIO peripheral using a configurator generated configuration struct.
 *
 * @param[in]  obj                  The SDIO peripheral to configure
 * @param[in]  cfg                  Configuration structure generated by a configurator.
 * @return The status of the operation
 */
cy_rslt_t cyhal_sdio_init_cfg(cyhal_sdio_t *obj, const cyhal_sdio_configurator_t *cfg);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_SDIO_IMPL_HEADER
#include CYHAL_SDIO_IMPL_HEADER
#endif /* CYHAL_SDIO_IMPL_HEADER */

/** \} group_hal_sdio */
