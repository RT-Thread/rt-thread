/***************************************************************************//**
* \file cy_scb_i2c.h
* \version 3.0
*
* Provides I2C API declarations of the SCB driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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
* \addtogroup group_scb_i2c
* \{
* Driver API for I2C Bus Peripheral
*
* I2C - The Inter-Integrated Circuit (I2C) bus is an industry-standard.
*
* The functions and other declarations used in this part of the driver are in
* cy_scb_i2c.h. You can also include cy_pdl.h to get access
* to all functions and declarations in the PDL.
*
* The I2C peripheral driver provides an API to implement I2C slave, master,
* or master-slave devices based on the SCB hardware block.
* I2C devices based on SCB hardware are compatible with I2C
* Standard-mode, Fast-mode, and Fast-mode Plus specifications as defined in
* the I2C-bus specification.
*
* Features:
* * An industry-standard I2C bus interface
* * Supports slave, master, and master-slave operation
* * Supports standard data rates of 100/400/1000 kbps
* * Hardware Address Match, multiple addresses
* * Wake from Deep Sleep on Address Match
*
* \note
* I2C supports clock stretching. This occurs when a slave device is not capable
* of processing data, it holds the SCL line by driving a '0'. The master device monitors
* the SCL line and detects it when it cannot generate a positive clock pulse ('1') on the
* SCL line. It then reacts by delaying the generation of a positive edge on the SCL line,
* effectively synchronizing with the slave device that is stretching the clock.
* Clock stretching can occur in the case of externally clocked address matching until the
* internally clocked logic takes over. The largest reason for clock stretching is when the
* master tries to write to the slave and the slave's RX FIFO is full, the slave will then
* clock stretch until the FIFO is no longer full. For more information on FIFO size and clock
* stretching see the architecture TRM.
********************************************************************************
* \section group_scb_i2c_configuration Configuration Considerations
********************************************************************************
* The I2C driver configuration can be divided to number of sequential
* steps listed below:
* * \ref group_scb_i2c_config
* * \ref group_scb_i2c_pins
* * \ref group_scb_i2c_clock
* * \ref group_scb_i2c_data_rate
* * \ref group_scb_i2c_intr
* * \ref group_scb_i2c_enable
*
* \note
* I2C driver is built on top of the SCB hardware block. The SCB3 instance is
* used as an example for all code snippets. Modify the code to match your
* design.
*
********************************************************************************
* \subsection group_scb_i2c_config Configure I2C
********************************************************************************
* To set up the I2C  driver, provide the configuration parameters in the
* \ref cy_stc_scb_i2c_config_t structure. Provide i2cMode to the select
* operation mode slave, master or master-slave. The useRxFifo and useTxFifo
* parameters specify if RX and TX FIFO is used during operation. Typically, both
* FIFOs should be enabled to reduce possibility of clock stretching. However,
* using RX FIFO has side effects that needs to be taken into account
* (see useRxFifo field description in \ref cy_stc_scb_i2c_config_t structure).
* For master modes, parameters lowPhaseDutyCycle, highPhaseDutyCycle and
* enableDigitalFilter can be used to define output data rate (refer to section
* \ref group_scb_i2c_data_rate for more information).
* For slave mode, provide the slaveAddress and slaveAddressMask. The other
* parameters are optional for operation.\n
* To initialize the driver, call \ref Cy_SCB_I2C_Init
* function providing a pointer to the populated \ref cy_stc_scb_i2c_config_t
* structure and the allocated \ref cy_stc_scb_i2c_context_t structure.
*
* \snippet scb/i2c_snippet/main.c I2C_CFG
*
* Set up I2C slave read and write buffer before enabling its
* operation using \ref Cy_SCB_I2C_SlaveConfigReadBuf and \ref
* Cy_SCB_I2C_SlaveConfigWriteBuf appropriately. Note that the master reads
* data from the slave read buffer and writes data into the slave write buffer.
*
* \snippet scb/i2c_snippet/main.c I2C_CFG_BUFFER
*
********************************************************************************
* \subsection group_scb_i2c_pins Assign and Configure Pins
********************************************************************************
* Only dedicated SCB pins can be used for I2C operation. The HSIOM
* register must be configured to connect dedicated SCB I2C pins to the
* SCB block. Also the I2C pins must be configured in Open-Drain, Drives Low mode
* (this pins  configuration implies usage of external pull-up resistors):
*
* \snippet scb/i2c_snippet/main.c I2C_CFG_PINS
*
* \note
* The alternative pins configuration is Resistive Pull-ups which implies usage
* internal pull-up resistors. This configuration is not recommended because
* resistor value is fixed and cannot be used for all supported data rates.
* Refer to the device datasheet parameter RPULLUP for resistor value specifications.
*
********************************************************************************
* \subsection group_scb_i2c_clock Assign Clock Divider
********************************************************************************
* A clock source must be connected to the SCB block to oversample input and
* output signals, in this document this clock will be referred as clk_scb.
* You must use one of the 8-bit or 16-bit dividers. Use the \ref group_sysclk
* driver API to do this.
*
* \snippet scb/i2c_snippet/main.c I2C_CFG_ASSIGN_CLOCK
*
********************************************************************************
* \subsection group_scb_i2c_data_rate Configure Data Rate
********************************************************************************
* To get I2C slave operation with the desired data rate, the clk_scb must be
* fast enough to provide sufficient oversampling. Use the
* \ref group_sysclk driver API to do this.
*
* \snippet scb/i2c_snippet/main.c I2C_CFG_DATA_RATE_SLAVE
*
* To get I2C master operation with the desired data rate, the source clock
* frequency and SCL low and high phase duration must be configured. Use the
* \ref group_sysclk driver API to configure source clock frequency. Then call
* \ref Cy_SCB_I2C_SetDataRate to set the SCL low, high phase duration and
* digital filter. This function sets SCL low and high phase settings based on
* source clock frequency.
*
* \snippet scb/i2c_snippet/main.c I2C_CFG_DATA_RATE_MASTER
*
* Alternatively, the low, high phase and digital filter can be set directly
* using configuration structure \ref cy_stc_scb_i2c_config_t fields
* lowPhaseDutyCycle, highPhaseDutyCycle and enableDigitalFilter appropriately.\n
* <b>Refer to the technical reference manual (TRM) section I2C sub-section
* Oversampling and Bit Rate to get information how to configure I2C to run with
* the desired data rate.</b>
*
* \note
* For I2C slave, the analog filter is used for all supported data rates. \n
* For I2C master, the analog filter is used for Standard and Fast modes and the
* digital filter for Fast Plus mode.
*
********************************************************************************
* \subsection group_scb_i2c_intr Configure Interrupt
********************************************************************************
* The interrupt is mandatory for I2C operation. The exception is the when only
* the \ref group_scb_i2c_master_low_level_functions functions are used.
* The driver provides three interrupt functions: \ref Cy_SCB_I2C_Interrupt,
* \ref Cy_SCB_I2C_SlaveInterrupt, and \ref Cy_SCB_I2C_MasterInterrupt. One of
* these functions must be called in the interrupt handler for the selected SCB
* instance. Call \ref Cy_SCB_I2C_SlaveInterrupt when I2C is configured to
* operate as a slave, \ref Cy_SCB_I2C_MasterInterrupt when I2C is configured
* to operate as a master and \ref Cy_SCB_I2C_Interrupt when I2C is configured
* to operate as master and slave. Using the slave- or master-specific interrupt
* function allows reducing the flash consumed by the I2C driver. Also this
* interrupt must be enabled in the NVIC otherwise it will not work.
* \note
* The I2C driver documentation refers to the \ref Cy_SCB_I2C_Interrupt function
* when interrupt processing is mandatory for the operation. This is done to
* simplify the readability of the driver's documentation. The application should
*  call the slave- or master-specific interrupt functions \ref Cy_SCB_I2C_SlaveInterrupt
* or \ref Cy_SCB_I2C_MasterInterrupt, when appropriate.
*
* \snippet scb/i2c_snippet/main.c I2C_INTR_A
* \snippet scb/i2c_snippet/main.c I2C_INTR_B
*
********************************************************************************
* \subsection group_scb_i2c_enable Enable I2C
********************************************************************************
* Finally, enable the I2C operation by calling \ref Cy_SCB_I2C_Enable. Then I2C
* slave starts respond to the assigned address and I2C master ready to execute
* transfers.
*
* \snippet scb/i2c_snippet/main.c I2C_ENABLE
*
* \section group_scb_i2c_use_cases Common Use Cases
*
********************************************************************************
* \subsection group_scb_i2c_master_mode Master Operation
********************************************************************************
* The master API is divided into two categories:
* \ref group_scb_i2c_master_high_level_functions and
* \ref group_scb_i2c_master_low_level_functions. Therefore, there are two
* methods for initiating I2C master transactions using either <b>Low-Level or
* High-Level</b> API. These two methods are described below. Only one method
* should be used at a time. <b>They should not be mixed.</b>
*
********************************************************************************
* \subsubsection  group_scb_i2c_master_hl Use High-Level Functions
********************************************************************************
*  Call \ref Cy_SCB_I2C_MasterRead or \ref Cy_SCB_I2C_MasterWrite to
* communicate with the slave. These functions do not block and only start a
* transaction. After a transaction starts, the \ref Cy_SCB_I2C_Interrupt
* handles further data transaction until its completion (successfully or
* with error occurring). To monitor the transaction,
* use \ref Cy_SCB_I2C_MasterGetStatus or register callback function using
* \ref Cy_SCB_I2C_RegisterEventCallback to be notified about
* \ref group_scb_i2c_macros_callback_events.
*
* \snippet scb/i2c_snippet/main.c I2C_MASTER_WRITE_READ_INT
*
********************************************************************************
* \subsubsection group_scb_i2c_master_ll Use Low-Level Functions
********************************************************************************
* Call \ref Cy_SCB_I2C_MasterSendStart to generate a start, send an address
* with the Read/Write direction bit, and receive acknowledgment. After the
* address is ACKed by the slave, the transaction can be continued by calling
* \ref Cy_SCB_I2C_MasterReadByte or \ref Cy_SCB_I2C_MasterWriteByte depending
* on its direction. These functions handle one byte per call. Therefore,
* they should be called for each byte in the transaction. Note that for the
* Read transaction, the last byte must be NAKed. To complete the current
* transaction, call \ref Cy_SCB_I2C_MasterSendStop or call
* \ref Cy_SCB_I2C_MasterSendReStart to complete the current transaction and
* start a new one. Typically, do a restart to change the transaction
* direction without releasing the bus from the master control.
* The Low-Level functions are blocking and do not require calling
* \ref Cy_SCB_I2C_Interrupt inside the interrupt handler. Using these
* functions requires extensive knowledge of the I2C protocol to execute
* transactions correctly.
*
* <b>Master Write Operation</b>
* \snippet scb/i2c_snippet/main.c I2C_MASTER_WRITE_MANUAL
*
* <b>Master Read Operation</b>
* \snippet scb/i2c_snippet/main.c I2C_MASTER_READ_MANUAL
*
********************************************************************************
* \subsection group_scb_i2c_slave Slave Operation
********************************************************************************
* Slave operation requires the \ref Cy_SCB_I2C_Interrupt be
* called inside the interrupt handler. The read and write buffers must
* be provided for the slave to enable communication with the master. Use
* \ref Cy_SCB_I2C_SlaveConfigReadBuf and \ref Cy_SCB_I2C_SlaveConfigWriteBuf
* for this purpose. Note that after transaction completion the buffer must be
* configured again. Otherwise, the same buffer is used starting from the point
* where the master stopped a previous transaction.
* For example: The read buffer is configured to be 10 bytes and the master reads
* 8 bytes. If the read buffer is not configured again, the next master read
* will start from the 9th byte.
* To monitor the transaction status, use \ref Cy_SCB_I2C_SlaveGetStatus or
* use \ref Cy_SCB_I2C_RegisterEventCallback to register a callback function
* to be notified about \ref group_scb_i2c_macros_callback_events.
*
* <b>Get Slave Events Notification</b>
* \snippet scb/i2c_snippet/main.c I2C_SLAVE_REG_CALLBACK
* \snippet scb/i2c_snippet/main.c I2C_SLAVE_NOTIFICATION
*
* <b>Polling Slave Completion Events</b>
* \snippet scb/i2c_snippet/main.c I2C_SLAVE_POLLING
*
* \note
* All slave API (except \ref Cy_SCB_I2C_SlaveAbortRead and
* \ref Cy_SCB_I2C_SlaveAbortWrite) <b>are not interrupt-protected</b> and to
* prevent a race condition, they should be protected from the I2C interruption
* in the place where they are called. The code snippet Polling Slave
* Completion Events above shows how to prevent a race condition when detect
* transfer completion and update I2C slave write buffer.
* The simple example of race condition is: application updates slave read
* buffer the I2C master starts read transfer. The I2C interrupts read buffer
* update and I2C interrupt loads current read buffer content in the TX FIFO .
* After I2C interrupt returns the application updates remaining part of the read
* buffer. As a result the mater read partly updated buffer.
*
********************************************************************************
* \section group_scb_i2c_lp Low Power Support
********************************************************************************
* The I2C driver provides callback functions to handle power mode transition.
* The callback \ref Cy_SCB_I2C_DeepSleepCallback must be called
* during execution of \ref Cy_SysPm_CpuEnterDeepSleep \ref Cy_SCB_I2C_HibernateCallback
* must be called during execution of \ref Cy_SysPm_SystemEnterHibernate. To trigger the
* callback execution, the callback must be registered before calling the
* power mode transition function. Refer to \ref group_syspm driver for more
* information about power mode transitions and callback registration.
*
* \note
* Only applicable for <b>rev-08 of the CY8CKIT-062-BLE</b>.
* For proper operation, when the I2C slave is configured to be a wakeup
* source from Deep Sleep mode, the \ref Cy_SCB_I2C_DeepSleepCallback must be
* copied and modified. Refer to the function description to get the details.
*
* \defgroup group_scb_i2c_macros Macros
* \defgroup group_scb_i2c_functions Functions
* \{
* \defgroup group_scb_i2c_general_functions General
* \defgroup group_scb_i2c_slave_functions Slave
* \defgroup group_scb_i2c_master_high_level_functions Master High-Level
* \defgroup group_scb_i2c_master_low_level_functions Master Low-Level
* \defgroup group_scb_i2c_interrupt_functions Interrupt
* \defgroup group_scb_i2c_low_power_functions Low Power Callbacks
* \}
* \defgroup group_scb_i2c_data_structures Data Structures
* \defgroup group_scb_i2c_enums Enumerated Types
*/

#if !defined(CY_SCB_I2C_H)
#define CY_SCB_I2C_H

#include "cy_device.h"

#if (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB))

#include "cy_scb_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*                            Enumerated Types
*******************************************************************************/

/**
* \addtogroup group_scb_i2c_enums
* \{
*/

/** I2C status codes */
typedef enum
{
    /** Operation completed successfully */
    CY_SCB_I2C_SUCCESS = 0U,

    /** One or more of input parameters are invalid */
    CY_SCB_I2C_BAD_PARAM = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 1U),

    /**
    * The master is not ready to start a new transaction.
    * Either the master is still processing a previous transaction or in the
    * master-slave mode, the slave operation is in progress.
    */
    CY_SCB_I2C_MASTER_NOT_READY = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 2U),

    /**
    * The master operation timed out before completing. Applicable only for
    * the \ref group_scb_i2c_master_low_level_functions functions.
    */
    CY_SCB_I2C_MASTER_MANUAL_TIMEOUT = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 3U),

    /** The slave NACKed the address. Applicable only for the
    * \ref group_scb_i2c_master_low_level_functions functions.
    */
    CY_SCB_I2C_MASTER_MANUAL_ADDR_NAK = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 4U),

    /** The slave NACKed the data byte.  Applicable only for the
    * \ref group_scb_i2c_master_low_level_functions.
    */
    CY_SCB_I2C_MASTER_MANUAL_NAK = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 5U),

    /**
    * The master lost arbitration, the transaction was aborted. Applicable only
    * for the \ref group_scb_i2c_master_low_level_functions functions.
    */
    CY_SCB_I2C_MASTER_MANUAL_ARB_LOST = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 6U),

    /**
    * The master detected an erroneous start or stop, the transaction was
    * aborted. Applicable only for the
    * \ref group_scb_i2c_master_low_level_functions functions.
    */
    CY_SCB_I2C_MASTER_MANUAL_BUS_ERR = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 7U),

    /**
    * The master transaction was aborted and the slave transaction is on-going
    * because the slave was addressed before the master generated a start.
    * Applicable only for the \ref group_scb_i2c_master_low_level_functions
    * functions.
    */
    CY_SCB_I2C_MASTER_MANUAL_ABORT_START = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_I2C_ID | 8U)
} cy_en_scb_i2c_status_t;

/** I2C Operation Modes */
typedef enum
{
    CY_SCB_I2C_SLAVE        = 1U,    /**< Configures SCB for I2C Slave operation */
    CY_SCB_I2C_MASTER       = 2U,    /**< Configures SCB for I2C Master operation */
    CY_SCB_I2C_MASTER_SLAVE = 3U,    /**< Configures SCB for I2C Master-Slave operation */
} cy_en_scb_i2c_mode_t;

/** I2C Transaction Direction */
typedef enum
{
    CY_SCB_I2C_WRITE_XFER = 0U,  /**< Current transaction is Write */
    CY_SCB_I2C_READ_XFER  = 1U,  /**< Current transaction is Read */
} cy_en_scb_i2c_direction_t;

/** I2C Command ACK / NAK */
typedef enum
{
    CY_SCB_I2C_ACK,     /**< Send ACK to current byte */
    CY_SCB_I2C_NAK,     /**< Send NAK to current byte */
} cy_en_scb_i2c_command_t;
/** \} group_scb_i2c_enums */


/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_scb_i2c_data_structures
* \{
*/

/**
* Provides the typedef for the callback function called in the
* \ref Cy_SCB_I2C_Interrupt to notify the user about occurrences of
* \ref group_scb_i2c_macros_callback_events.
*/
typedef void (* cy_cb_scb_i2c_handle_events_t)(uint32_t event);

/**
* Provides the typedef for the callback function called in the
* \ref Cy_SCB_I2C_Interrupt to notify the user about occurrences of
* \ref group_scb_i2c_macros_addr_callback_events.
* This callback must return a decision to ACK (continue transaction) or
* NAK (end transaction) the received address.
* Note if the slave is configured to accept an address in RX FIFO, it must read
* from it using the \ref Cy_SCB_ReadRxFifo function.
*/
typedef cy_en_scb_i2c_command_t (* cy_cb_scb_i2c_handle_addr_t)(uint32_t event);

/** I2C configuration structure */
typedef struct cy_stc_scb_i2c_config
{
    /** Specifies the mode of operation */
    cy_en_scb_i2c_mode_t i2cMode;

    /**
    * The SCB provides an RX FIFO in hardware (consult the selected device
    * datasheet to get the actual FIFO size). The useRxFifo field defines
    * how the driver firmware reads data from the RX FIFO:
    * * If this option is enabled, the hardware is configured to automatically
    *   ACK incoming data, and interrupt is enabled to take data out of the RX
    *   FIFO when it has some number of bytes (typically, when it is half full).
    * * If this option is disabled, the interrupt is enabled to take data out of
    *   the RX FIFO when a byte is available. Also, hardware does not
    *   automatically ACK the data. Firmware must tell the hardware to ACK
    *   the byte (so each byte requires interrupt processing).
    * \n <b>Typically, this option should be enabled</b> to configure hardware to
    * automatically ACK incoming data. Otherwise hardware might not get the command
    * to ACK or NACK a byte fast enough, and clock stretching is applied
    * (the transaction is delayed) until the command is set. When this option is
    * enabled, the number of interrupts required to process the transaction
    * is significantly reduced because several bytes are handled at once.
    * \n <b>However, there is a side effect:</b>
    * * For master mode, the drawback is that the master may receive more
    *   data than desired due to the interrupt latency. An interrupt fires
    *   when the second-to-last byte has been received. This interrupt tells
    *   the hardware to stop receiving data. If the latency of this interrupt
    *   is longer than one transaction of the byte on the I2C bus, then the
    *   hardware automatically ACKs the following bytes until the interrupt
    *   is serviced or the RX FIFO becomes full.
    * * For slave mode, the drawback is that the slave only NACKs
    *   the master when the RX FIFO becomes full, NOT when the slave write
    *   firmware buffer becomes full.
    * \n In either master or slave mode, all received extra bytes are dropped.
    * \note The useRxFifo option is not available if acceptAddrInFifo is true.
    */
    bool useRxFifo;

    /**
    * The SCB provides a TX FIFO in hardware (consult the selected device
    * datasheet to get the actual FIFO size). The useTxFifo option defines how the
    * driver firmware loads data into the TX FIFO:
    * * If this option is enabled, the TX FIFO is fully loaded with data and the
    *   interrupt is enabled to keep the TX FIFO loaded until the end of the transaction.
    * * If this option is disabled, a single byte is loaded into the TX FIFO and
    *   the interrupt enabled to load the next byte when the TX FIFO becomes empty
    *   (so each byte requires interrupt processing).
    * \n <b>Typically, this option should be enabled</b> to keep the TX FIFO loaded with
    * data and reduce the probability of clock stretching. When there is no data
    * to transfer, clock stretching is applied (the transaction is delayed) until
    * the data is loaded. When this option is enabled, the number of interrupts required
    * to process the transaction is significantly reduced because several
    * bytes are handled at once.
    * \n <b>The drawback of enabling useTxFifo</b> is that the abort operation clears
    * the TX FIFO. The TX FIFO clear operation also clears the shift
    * register. As a result the shifter may be cleared in the middle of a byte
    * transaction, corrupting it. The remaining bits to transaction within the
    * corrupted byte are complemented with 1s. If this is an issue,
    * then do not enable this option.
    */
    bool useTxFifo;

    /**
    * The 7-bit right justified slave address, used only for the slave mode
    */
    uint8_t slaveAddress;

    /**
    * The slave address mask is used to mask bits of the slave address during
    * the address match procedure (it is used only for the slave mode).
    * Bit 0 of the address mask corresponds to the
    * read/write direction bit and is always a do not care in the address match
    * therefore must be set 0. Bit value 0 - excludes bit from address
    * comparison. Bit value 1 - the bit needs to match with the corresponding
    * bit of the I2C slave address.
    */
    uint8_t slaveAddressMask;

    /**
    * True - the slave address is accepted in the RX FIFO, false - the slave
    * addresses are not accepted in the RX FIFO
    */
    bool acceptAddrInFifo;

    /**
    * True - accept the general call address; false - ignore the general
    * call address.
    */
    bool ackGeneralAddr;

    /**
    * When set, the slave will wake the device from Deep Sleep on an address
    * match (the device datasheet must be consulted to determine which SCBs
    * support this mode)
    */
    bool enableWakeFromSleep;

    /**
    * Enables a digital 3-tap median filter to be applied to the inputs
    * of filter glitches on the lines.
    */
    bool enableDigitalFilter;

    /**
    * The number of SCB clock cycles in the low phase of SCL. Only applicable
    * in master modes. The valid range is 7 to 16.
    */
    uint32_t lowPhaseDutyCycle;

    /**
    * The number of SCB clock cycles in the high phase of SCL. Only applicable
    * in master modes. The valid range is 5 to 16.
    */
    uint32_t highPhaseDutyCycle;

} cy_stc_scb_i2c_config_t;

/** I2C context structure.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct cy_stc_scb_i2c_context
{
    /** \cond INTERNAL */
    bool useRxFifo;             /**< Stores RX FIFO configuration */
    bool useTxFifo;             /**< Stores TX FIFO configuration */

    volatile uint32_t state;    /**< The driver state */

    volatile uint32_t masterStatus; /**< The master status */
    bool     masterPause;           /**< Stores how the master ends the transaction */
    bool     masterRdDir;           /**< The direction of the master transaction */

    uint8_t  *masterBuffer;     /**< The pointer to the master buffer (either for a transmit or a receive operation) */
    uint32_t  masterBufferSize;         /**< The current master buffer size */
    volatile uint32_t masterBufferIdx;  /**< The current location in the master buffer */
    volatile uint32_t masterNumBytes;   /**< The number of bytes to send or receive */

    volatile uint32_t slaveStatus;       /**< The slave status */
    volatile bool     slaveRdBufEmpty;   /**< Tracks slave Read buffer empty event */

    uint8_t  *slaveTxBuffer;             /**< The pointer to the slave transmit buffer (a master reads from it) */
    uint32_t  slaveTxBufferSize;         /**< The current slave transmit buffer size */
    volatile uint32_t slaveTxBufferIdx;  /**< The current location in the slave buffer */
    volatile uint32_t slaveTxBufferCnt;  /**< The number of transferred bytes */

    uint8_t  *slaveRxBuffer;             /**< The pointer to the slave receive buffer (a master writes into it) */
    uint32_t  slaveRxBufferSize;         /**< The current slave receive buffer size */
    volatile uint32_t slaveRxBufferIdx;  /**< The current location in the slave buffer */

    /**
    * The pointer to an event callback that is called when any of
    * \ref group_scb_i2c_macros_callback_events occurs
    */
    cy_cb_scb_i2c_handle_events_t cbEvents;

    /**
    * The pointer to an address callback that is called when any of
    * \ref group_scb_i2c_macros_addr_callback_events occurs (applicable only
    * for the slave)
    */
    cy_cb_scb_i2c_handle_addr_t   cbAddr;

    /** \endcond */
} cy_stc_scb_i2c_context_t;

/** The I2C Master transfer structure */
typedef struct cy_stc_scb_i2c_master_xfer_config
{
    /** The 7-bit right justified slave address to communicate with */
    uint8_t  slaveAddress;

    /**
    * The pointer to the buffer for data to read from the slave or
    * data to write into the slave
    */
    uint8_t  *buffer;

    /** The size of the buffer */
    uint32_t bufferSize;

    /**
    * The transfer operation is pending - the stop condition will not
    * be generated.
    * A new transfer starts from start condition and ends
    * with or without stop condition. The stop condition releases I2C
    * bus from master control. When stop is not generated master keeps
    * bus control (transfer is pending) and can issue the next transfer
    * using restart condition instead of start. The I2C driver
    * automatically generates start or restart condition depends on
    * current state.
    * Note if master lost arbitration during transfer it stops control
    * the bus and does not send/receive data or generate stop condition - the
    * transfer ends.
    */
    bool     xferPending;
} cy_stc_scb_i2c_master_xfer_config_t;
/** \} group_scb_i2c_data_structures */


/*******************************************************************************
*                            Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_scb_i2c_general_functions
* \{
*/
cy_en_scb_i2c_status_t Cy_SCB_I2C_Init(CySCB_Type *base, cy_stc_scb_i2c_config_t const *config,
                                       cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_DeInit(CySCB_Type *base);
__STATIC_INLINE void Cy_SCB_I2C_Enable(CySCB_Type *base);
void Cy_SCB_I2C_Disable(CySCB_Type *base, cy_stc_scb_i2c_context_t *context);

uint32_t Cy_SCB_I2C_SetDataRate(CySCB_Type *base, uint32_t dataRateHz, uint32_t scbClockHz);
uint32_t Cy_SCB_I2C_GetDataRate(CySCB_Type const *base, uint32_t scbClockHz);

__STATIC_INLINE void     Cy_SCB_I2C_SlaveSetAddress(CySCB_Type *base, uint8_t addr);
__STATIC_INLINE uint32_t Cy_SCB_I2C_SlaveGetAddress(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_I2C_SlaveSetAddressMask(CySCB_Type *base, uint8_t addrMask);
__STATIC_INLINE uint32_t Cy_SCB_I2C_SlaveGetAddressMask(CySCB_Type const *base);

__STATIC_INLINE bool Cy_SCB_I2C_IsBusBusy(CySCB_Type const *base);

__STATIC_INLINE void Cy_SCB_I2C_MasterSetLowPhaseDutyCycle (CySCB_Type *base, uint32_t clockCycles);
__STATIC_INLINE void Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(CySCB_Type *base, uint32_t clockCycles);
#if (((CY_IP_MXSCB_VERSION>=3) || defined (CY_IP_MXS22SCB)) || defined (CY_DOXYGEN))
void Cy_SCB_I2C_SetStretchThreshold(CySCB_Type const *base, uint32_t value);
uint32_t Cy_SCB_I2C_GetStretchCount(CySCB_Type const *base);
bool Cy_SCB_I2C_IsStretchDetected(CySCB_Type const *base);
bool Cy_SCB_I2C_IsSyncDetected(CySCB_Type const *base);
bool Cy_SCB_I2C_IsStretching(CySCB_Type const *base);
#endif /* CY_IP_MXSCB_VERSION */

/** \} group_scb_i2c_general_functions */

/**
* \addtogroup group_scb_i2c_slave_functions
* \{
*/
void Cy_SCB_I2C_SlaveConfigReadBuf (CySCB_Type const *base, uint8_t *buffer, uint32_t size,
                                    cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_SlaveAbortRead     (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_SlaveConfigWriteBuf(CySCB_Type const *base, uint8_t *buffer, uint32_t size,
                                    cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_SlaveAbortWrite    (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);

uint32_t Cy_SCB_I2C_SlaveGetStatus       (CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context);
uint32_t Cy_SCB_I2C_SlaveClearReadStatus (CySCB_Type const *base, cy_stc_scb_i2c_context_t *context);
uint32_t Cy_SCB_I2C_SlaveClearWriteStatus(CySCB_Type const *base, cy_stc_scb_i2c_context_t *context);

uint32_t Cy_SCB_I2C_SlaveGetReadTransferCount (CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context);
uint32_t Cy_SCB_I2C_SlaveGetWriteTransferCount(CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context);
/** \} group_scb_i2c_slave_functions */

/**
* \addtogroup group_scb_i2c_master_high_level_functions
* \{
*/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterWrite(CySCB_Type *base, cy_stc_scb_i2c_master_xfer_config_t *xferConfig,
                                              cy_stc_scb_i2c_context_t *context);
void     Cy_SCB_I2C_MasterAbortWrite         (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterRead (CySCB_Type *base, cy_stc_scb_i2c_master_xfer_config_t* xferConfig,
                                              cy_stc_scb_i2c_context_t *context);
void     Cy_SCB_I2C_MasterAbortRead          (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
uint32_t Cy_SCB_I2C_MasterGetStatus          (CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context);
uint32_t Cy_SCB_I2C_MasterGetTransferCount   (CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context);
/** \} group_scb_i2c_master_low_high_functions */

/**
* \addtogroup group_scb_i2c_master_low_level_functions
* \{
*/
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendStart  (CySCB_Type *base, uint32_t address, cy_en_scb_i2c_direction_t bitRnW,
                                                    uint32_t timeoutMs, cy_stc_scb_i2c_context_t *context);
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendReStart(CySCB_Type *base, uint32_t address, cy_en_scb_i2c_direction_t bitRnW,
                                                    uint32_t timeoutMs, cy_stc_scb_i2c_context_t *context);
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterSendStop   (CySCB_Type *base,uint32_t timeoutMs, cy_stc_scb_i2c_context_t *context);
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterReadByte   (CySCB_Type *base, cy_en_scb_i2c_command_t ackNack, uint8_t *byte,
                                                    uint32_t timeoutMs, cy_stc_scb_i2c_context_t *context);
cy_en_scb_i2c_status_t Cy_SCB_I2C_MasterWriteByte  (CySCB_Type *base, uint8_t byte, uint32_t timeoutMs,
                                                    cy_stc_scb_i2c_context_t *context);
/** \} group_scb_i2c_master_low_level_functions */

/**
* \addtogroup group_scb_i2c_interrupt_functions
* \{
*/
void Cy_SCB_I2C_Interrupt      (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_SlaveInterrupt (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_MasterInterrupt (CySCB_Type *base, cy_stc_scb_i2c_context_t *context);

__STATIC_INLINE void Cy_SCB_I2C_RegisterEventCallback(CySCB_Type const *base, cy_cb_scb_i2c_handle_events_t callback,
                                                      cy_stc_scb_i2c_context_t *context);
__STATIC_INLINE void Cy_SCB_I2C_RegisterAddrCallback (CySCB_Type const *base, cy_cb_scb_i2c_handle_addr_t callback,
                                                      cy_stc_scb_i2c_context_t *context);
/** \} group_scb_i2c_interrupt_functions */

/**
* \addtogroup group_scb_i2c_low_power_functions
* \{
*/
cy_en_syspm_status_t Cy_SCB_I2C_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
cy_en_syspm_status_t Cy_SCB_I2C_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
/** \} group_scb_i2c_low_power_functions */


/*******************************************************************************
*                               API Constants
*******************************************************************************/

/**
* \addtogroup group_scb_i2c_macros
* \{
*/

/**
* \defgroup group_scb_i2c_macros_slave_status I2C Slave Status
* Macros to check current I2C slave status returned by
* \ref Cy_SCB_I2C_SlaveGetStatus function. Each I2C slave status is encoded
* in a separate bit, therefore multiple bits may be set to indicate the
* current status.
* \{
*/
/** There is a read transaction in progress */
#define CY_SCB_I2C_SLAVE_RD_BUSY       (0x00000001UL)

/**
* All read data has been loaded into the TX FIFO, applicable only if
* the TX FIFO is used
*/
#define CY_SCB_I2C_SLAVE_RD_IN_FIFO    (0x00000002UL)

/**
* The master has finished reading data from the slave
*/
#define CY_SCB_I2C_SLAVE_RD_CMPLT      (0x00000004UL)

/**
* Set when the master tried to read more bytes than available in the configured
* read buffer. The slave is not able to finish the transaction and sends
* \ref CY_SCB_I2C_DEFAULT_TX.
*/
#define CY_SCB_I2C_SLAVE_RD_UNDRFL     (0x00000008UL)

/** There is a write transaction in progress */
#define CY_SCB_I2C_SLAVE_WR_BUSY       (0x00000010UL)

/**
* The master has finished writing data into the slave
*/
#define CY_SCB_I2C_SLAVE_WR_CMPLT      (0x00000020UL)

/**
* The master attempted to write more bytes than space available in the
* configured Write buffer. Note that all subsequent bytes are dropped.
*/
#define CY_SCB_I2C_SLAVE_WR_OVRFL      (0x00000040UL)

/** The slave lost arbitration, and the transaction was aborted */
#define CY_SCB_I2C_SLAVE_ARB_LOST      (0x00000080UL)

/**
* The slave captured an error on the bus during a master transaction (source
* of error is misplaced Start or Stop).
*/
#define CY_SCB_I2C_SLAVE_BUS_ERR       (0x00000100UL)
/** \} group_scb_i2c_macros_slave_status */

/**
* \defgroup group_scb_i2c_macros_master_status I2C Master Status
* Macros to check current I2C master status returned by
* \ref Cy_SCB_I2C_MasterGetStatus function. Each I2C master status is encoded
* in a separate bit, therefore multiple bits may be set to indicate the
* current status.
* \{
*/

/**
* The master is busy executing operation started by \ref Cy_SCB_I2C_MasterRead
* or \ref Cy_SCB_I2C_MasterWrite
*/
#define CY_SCB_I2C_MASTER_BUSY         (0x00010000UL)

/**
* All Write data has been loaded into the TX FIFO
*/
#define CY_SCB_I2C_MASTER_WR_IN_FIFO   (0x00020000UL)

/** The slave NACKed the address. */
#define CY_SCB_I2C_MASTER_ADDR_NAK     (0x00100000UL)

/** Write completed before all bytes were sent (last byte was NAKed)
*/
#define CY_SCB_I2C_MASTER_DATA_NAK     (0x00200000UL)

/** The master lost arbitration, the transaction was aborted */
#define CY_SCB_I2C_MASTER_ARB_LOST     (0x00400000UL)

/**
* The master detected an erroneous start or stop, the transaction was aborted
*/
#define CY_SCB_I2C_MASTER_BUS_ERR      (0x00800000UL)

/**
* The master transaction was aborted and the slave transaction is on-going
* because the slave was addressed before the master generated a start
*/
#define CY_SCB_I2C_MASTER_ABORT_START  (0x01000000UL)
/** \} group_scb_i2c_macros_master_status */

/**
* \defgroup group_scb_i2c_macros_callback_events I2C Callback Events
* \{
* Macros to check I2C events passed by \ref cy_cb_scb_i2c_handle_events_t callback.
* Each event is encoded in a separate bit, and therefore it is possible to
* notify about multiple events.
*/
/**
* Indicates that the slave was addressed and the master wants to read data.
* This event can be used to configure the slave Read buffer.
*/
#define CY_SCB_I2C_SLAVE_READ_EVENT            (0x00000001UL)

/**
* Indicates that the slave was addressed and the master wants to write data.
* This event can be used to configure the slave Write buffer.
*/
#define CY_SCB_I2C_SLAVE_WRITE_EVENT           (0x00000002UL)

/**
* All slave data from the configured Read buffer has been loaded into the
* TX FIFO. The content of the Read buffer can be modified. Applicable only
* if the TX FIFO is used.
*/
#define CY_SCB_I2C_SLAVE_RD_IN_FIFO_EVENT      (0x00000004UL)

/**
* The master has read all data out of the configured Read buffer.
* This event can be used to configure the next Read buffer. If the buffer
* remains empty, the \ref CY_SCB_I2C_DEFAULT_TX bytes are returned to the master.
*/
#define CY_SCB_I2C_SLAVE_RD_BUF_EMPTY_EVENT    (0x00000008UL)

/**
* Indicates the master completed reading from the slave (set by the master NAK
* or Stop)
*/
#define CY_SCB_I2C_SLAVE_RD_CMPLT_EVENT        (0x00000010UL)

/**
* Indicates the master completed writing to the slave (set by the master Stop
* or Restart)
*/
#define CY_SCB_I2C_SLAVE_WR_CMPLT_EVENT        (0x00000020UL)

/**
* Indicates the I2C hardware detected an error.
* Check \ref Cy_SCB_I2C_SlaveGetStatus to determine the source of the error.
*/
#define CY_SCB_I2C_SLAVE_ERR_EVENT             (0x00000040UL)

/**
* All data specified by \ref Cy_SCB_I2C_MasterWrite has been loaded
* into the TX FIFO. The content of the master write buffer can be modified.
* Applicable only if the TX FIFO is used.
*/
#define CY_SCB_I2C_MASTER_WR_IN_FIFO_EVENT     (0x00010000UL)

/** The master write started by \ref Cy_SCB_I2C_MasterWrite is complete */
#define CY_SCB_I2C_MASTER_WR_CMPLT_EVENT       (0x00020000UL)

/** The master read started by \ref Cy_SCB_I2C_MasterRead is complete */
#define CY_SCB_I2C_MASTER_RD_CMPLT_EVENT       (0x00040000UL)

/**
* Indicates the I2C hardware has detected an error. It occurs together with
* \ref CY_SCB_I2C_MASTER_RD_CMPLT_EVENT or \ref CY_SCB_I2C_MASTER_WR_CMPLT_EVENT
* depends on the direction of the transfer.
* Check \ref Cy_SCB_I2C_MasterGetStatus to determine the source of the error.
*/
#define CY_SCB_I2C_MASTER_ERR_EVENT            (0x00080000UL)
/** \} group_scb_i2c_macros_callback_events */

/**
* \defgroup group_scb_i2c_macros_addr_callback_events I2C Address Callback Events
* Macros to check I2C address events passed by \ref cy_cb_scb_i2c_handle_addr_t callback.
* Each event is encoded in a separate bit and therefore it is possible to
* notify about multiple events.
* \{
*/
/**
* Indicates the slave was addressed by the general call address
*/
#define CY_SCB_I2C_GENERAL_CALL_EVENT      (0x01UL)

/**
* The slave address is in the RX FIFO.
* Note that the address must be read from the RX FIFO using the
* \ref Cy_SCB_ReadRxFifo function.
*/
#define CY_SCB_I2C_ADDR_IN_FIFO_EVENT      (0x02UL)
/** \} group_scb_i2c_macros_addr_callback_events */

/**
* This value is returned by the slave when there is no data in the
* Read buffer
*/
#define CY_SCB_I2C_DEFAULT_TX  (0xFFUL)


/*******************************************************************************
*                          Internal Constants
*******************************************************************************/

/** \cond INTERNAL */

/* Slave statuses */
#define CY_SCB_I2C_SLAVE_RD_CLEAR  (CY_SCB_I2C_SLAVE_RD_CMPLT  | CY_SCB_I2C_SLAVE_RD_IN_FIFO | \
                                    CY_SCB_I2C_SLAVE_RD_UNDRFL | CY_SCB_I2C_SLAVE_ARB_LOST   | \
                                    CY_SCB_I2C_SLAVE_BUS_ERR)

#define CY_SCB_I2C_SLAVE_WR_CLEAR  (CY_SCB_I2C_SLAVE_WR_CMPLT | CY_SCB_I2C_SLAVE_WR_OVRFL | \
                                    CY_SCB_I2C_SLAVE_ARB_LOST | CY_SCB_I2C_SLAVE_BUS_ERR)

/* Master error statuses */
#define CY_SCB_I2C_MASTER_ERR (CY_SCB_I2C_MASTER_ABORT_START | CY_SCB_I2C_MASTER_ADDR_NAK | \
                               CY_SCB_I2C_MASTER_DATA_NAK    | CY_SCB_I2C_MASTER_BUS_ERR  | \
                               CY_SCB_I2C_MASTER_ARB_LOST)

/* Master interrupt masks */
#define CY_SCB_I2C_MASTER_INTR     (CY_SCB_MASTER_INTR_I2C_ARB_LOST | CY_SCB_MASTER_INTR_I2C_BUS_ERROR | \
                                    CY_SCB_MASTER_INTR_I2C_NACK     | CY_SCB_MASTER_INTR_I2C_STOP)

#define CY_SCB_I2C_MASTER_INTR_ALL   (CY_SCB_I2C_MASTER_INTR | CY_SCB_MASTER_INTR_I2C_ACK)

#define CY_SCB_I2C_MASTER_INTR_ERR   (CY_SCB_MASTER_INTR_I2C_BUS_ERROR | CY_SCB_MASTER_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_MASTER_INTR_CMPLT (CY_SCB_I2C_MASTER_INTR_ERR | CY_SCB_MASTER_INTR_I2C_STOP)

/* Master statuses. */
#define CY_SCB_I2C_MASTER_TX_BYTE_DONE (CY_SCB_MASTER_INTR_I2C_ACK       | CY_SCB_MASTER_INTR_I2C_NACK | \
                                        CY_SCB_MASTER_INTR_I2C_BUS_ERROR | CY_SCB_MASTER_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_MASTER_RX_BYTE_DONE (CY_SCB_MASTER_INTR_I2C_BUS_ERROR | CY_SCB_MASTER_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_MASTER_STOP_DONE    (CY_SCB_MASTER_INTR_I2C_STOP      | \
                                        CY_SCB_MASTER_INTR_I2C_BUS_ERROR | CY_SCB_MASTER_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_MASTER_TIMEOUT_DONE (0x80000000UL)

/* The slave interrupt mask */
#define CY_SCB_I2C_SLAVE_INTR      (CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH | CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR | \
                                    CY_SCB_SLAVE_INTR_I2C_STOP       | CY_SCB_SLAVE_INTR_I2C_BUS_ERROR    | \
                                    CY_SCB_SLAVE_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_SLAVE_INTR_NO_STOP   (CY_SCB_I2C_SLAVE_INTR & (uint32_t) ~CY_SCB_SLAVE_INTR_I2C_STOP)

#define CY_SCB_I2C_SLAVE_INTR_ADDR      (CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH | CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR)

#define CY_SCB_I2C_SLAVE_ADDR_DONE      (CY_SCB_I2C_SLAVE_INTR_ADDR)

#define CY_SCB_I2C_SLAVE_INTR_NO_ADDR   (CY_SCB_I2C_SLAVE_INTR & (uint32_t) ~CY_SCB_I2C_SLAVE_INTR_ADDR)

#define CY_SCB_I2C_SLAVE_INTR_TX        (CY_SCB_TX_INTR_LEVEL | CY_SCB_TX_INTR_UNDERFLOW)

#define CY_SCB_I2C_SLAVE_INTR_ERROR     (CY_SCB_SLAVE_INTR_I2C_BUS_ERROR | CY_SCB_SLAVE_INTR_I2C_ARB_LOST)

/* I2C states */
#define CY_SCB_I2C_IDLE              (0x10000000UL)
#define CY_SCB_I2C_IDLE_MASK         (0x10000000UL)

/* Master states */
#define CY_SCB_I2C_MASTER_ACTIVE     (0x00100000UL)
#define CY_SCB_I2C_MASTER_WAIT       (0x10100000UL)
#define CY_SCB_I2C_MASTER_RX0        (0x00110000UL)
#define CY_SCB_I2C_MASTER_RX1        (0x00120000UL)
#define CY_SCB_I2C_MASTER_ADDR       (0x10130000UL)
#define CY_SCB_I2C_MASTER_TX         (0x00140000UL)
#define CY_SCB_I2C_MASTER_TX_DONE    (0x00150000UL)
#define CY_SCB_I2C_MASTER_STOP       (0x00160000UL)
#define CY_SCB_I2C_MASTER_WAIT_STOP  (0x00170000UL)
#define CY_SCB_I2C_MASTER_CMPLT      (0x00180000UL)

/* Slave states */
#define CY_SCB_I2C_SLAVE_ACTIVE      (0x00001000UL)
#define CY_SCB_I2C_SLAVE_RX_MASK     (0x00001001UL)
#define CY_SCB_I2C_SLAVE_RX          (0x00001001UL)
#define CY_SCB_I2C_SLAVE_TX          (0x00001002UL)

/* FIFO size */
#define CY_SCB_I2C_FIFO_SIZE          CY_SCB_FIFO_SIZE
#define CY_SCB_I2C_HALF_FIFO_SIZE     (CY_SCB_FIFO_SIZE / 2UL)

#define CY_SCB_I2C_DEFAULT_RETURN    (0xFFUL)

/* Convert the timeout in milliseconds to microseconds */
#define CY_SCB_I2C_CONVERT_TIMEOUT_TO_US(timeoutMs)     ((timeoutMs) * 1000UL)

/* I2C data rates max (Hz): standard, fast and fast plus modes */
#define CY_SCB_I2C_STD_DATA_RATE    (100000U)
#define CY_SCB_I2C_FST_DATA_RATE    (400000U)
#define CY_SCB_I2C_FSTP_DATA_RATE  (1000000U)

/* Slave clock limits */
#define CY_SCB_I2C_SLAVE_STD_CLK_MIN    (1550000U)
#define CY_SCB_I2C_SLAVE_STD_CLK_MAX   (12800000U)
#define CY_SCB_I2C_SLAVE_FST_CLK_MIN    (7820000U)
#define CY_SCB_I2C_SLAVE_FST_CLK_MAX   (15380000U)
#define CY_SCB_I2C_SLAVE_FSTP_CLK_MIN  (15840000U)
#define CY_SCB_I2C_SLAVE_FSTP_CLK_MAX  (89000000U)

/* Master clock (Hz) and duty cycle limits for standard mode */
#define CY_SCB_I2C_MASTER_STD_CLK_MIN           (1550000U)
#define CY_SCB_I2C_MASTER_STD_CLK_MAX           (3200000U)
#define CY_SCB_I2C_MASTER_STD_LOW_PHASE_MIN     (8U)
#define CY_SCB_I2C_MASTER_STD_HIGH_PHASE_MIN    (8U)

/* Master clock (Hz) and duty cycle limits for fast mode */
#define CY_SCB_I2C_MASTER_FST_CLK_MIN           (7820000U)
#define CY_SCB_I2C_MASTER_FST_CLK_MAX           (10000000U)
#define CY_SCB_I2C_MASTER_FST_LOW_PHASE_MIN     (13U)
#define CY_SCB_I2C_MASTER_FST_HIGH_PHASE_MIN    (8U)

/* Master clock (Hz) and duty cycle limits for fast plus mode */
#define CY_SCB_I2C_MASTER_FSTP_CLK_MIN          (14320000U)
#define CY_SCB_I2C_MASTER_FSTP_CLK_MAX          (25800000U)
#define CY_SCB_I2C_MASTER_FSTP_LOW_PHASE_MIN    (9U)
#define CY_SCB_I2C_MASTER_FSTP_HIGH_PHASE_MIN   (6U)

/* SCL low and high time in ns. Takes into account tF and tR */
#define CY_SCB_I2C_MASTER_STD_SCL_LOW   (5000U) /* tLOW  + tF = 4700 + 300  */
#define CY_SCB_I2C_MASTER_STD_SCL_HIGH  (5000U) /* tHIGH + tR = 4000 + 1000 */
#define CY_SCB_I2C_MASTER_FST_SCL_LOW   (1600U) /* tLOW  + tF = 1300 + 300  */
#define CY_SCB_I2C_MASTER_FST_SCL_HIGH   (900U) /* tHIGH + tR = 600 + 300   */
#define CY_SCB_I2C_MASTER_FSTP_SCL_LOW   (620U) /* tLOW  + tF = 500 + 120   */
#define CY_SCB_I2C_MASTER_FSTP_SCL_HIGH  (380U) /* tHIGH + tR = 260 + 120   */

/* Master duty cycle limits */
#define CY_SCB_I2C_LOW_PHASE_MAX    (16U)
#define CY_SCB_I2C_HIGH_PHASE_MAX   (16U)
#define CY_SCB_I2C_DUTY_CYCLE_MAX   (CY_SCB_I2C_LOW_PHASE_MAX + CY_SCB_I2C_HIGH_PHASE_MAX)

/* Analog filter settings. */
#define CY_SCB_I2C_ENABLE_ANALOG_FITLER    (CY_SCB_I2C_CFG_DEF_VAL)
#define CY_SCB_I2C_DISABLE_ANALOG_FITLER   (CY_SCB_I2C_CFG_DEF_VAL & \
                                            (uint32_t) ~(SCB_I2C_CFG_SDA_IN_FILT_SEL_Msk | \
                                                         SCB_I2C_CFG_SCL_IN_FILT_SEL_Msk))

#define CY_SCB_I2C_IS_MODE_VALID(mode)      ( (CY_SCB_I2C_SLAVE  == (mode)) || \
                                              (CY_SCB_I2C_MASTER == (mode)) || \
                                              (CY_SCB_I2C_MASTER_SLAVE == (mode)) )

#define CY_SCB_I2C_IS_RW_BIT_VALID(dir)     ( (CY_SCB_I2C_WRITE_XFER == (dir)) || \
                                              (CY_SCB_I2C_READ_XFER  == (dir)) )

#define CY_SCB_I2C_IS_RESPONSE_VALID(cmd)   ( (CY_SCB_I2C_ACK == (cmd))  || \
                                              (CY_SCB_I2C_NAK == (cmd)) )

#define CY_SCB_I2C_IS_ADDR_MASK_VALID(mask)         ( (0U == ((mask) & 0x01U)) )

#define CY_SCB_I2C_IS_PHASE_OVERSAMPLE_VALID(phaseOvs)  ((phaseOvs) <= 16U)

#define CY_SCB_I2C_IS_DATA_RATE_VALID(dataRateHz)   ( ((dataRateHz) > 0UL) && \
                                                      ((dataRateHz) <= CY_SCB_I2C_FSTP_DATA_RATE) )

#define CY_SCB_I2C_IS_TIMEOUT_VALID(timeoutMs)              ( (timeoutMs) <= (0xFFFFFFFFUL / 1000UL) )
#define CY_SCB_I2C_IS_LOW_PHASE_CYCLES_VALID(clockCycles)   ( ((clockCycles) >= 7UL) && ((clockCycles) <= 16UL) )
#define CY_SCB_I2C_IS_HIGH_PHASE_CYCLES_VALID(clockCycles)  ( ((clockCycles) >= 5UL) && ((clockCycles) <= 16UL) )
#if((CY_IP_MXSCB_VERSION>=3) || defined (CY_IP_MXS22SCB))
#define CY_SCB_I2C_STRETCH_THRESHOLD_VALUE_VALID(value)      ( (value) <= SCB_I2C_STRETCH_CTRL_STRETCH_THRESHOLD_Msk )
#endif /* CY_IP_MXSCB_VERSION */

/** \endcond */

/** \} group_scb_i2c_macros */


/*******************************************************************************
*                     In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_scb_i2c_general_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SCB_I2C_Enable
****************************************************************************//**
*
* Enables the SCB block for the I2C operation
*
* \param base
* The pointer to the I2C SCB instance.
* \note
* Ensure SCB is initialized with \ref Cy_SCB_I2C_Init before calling this function
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_Enable(CySCB_Type *base)
{
    SCB_CTRL(base) |= SCB_CTRL_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_IsBusBusy
****************************************************************************//**
*
* Checks whether the I2C bus is busy.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \return
* A bus status: busy or not busy.
*
* \note
* After the SCB block is enabled or reset, the valid bus busy-status returns
* after half of the SCL period.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_I2C_IsBusBusy(CySCB_Type const *base)
{
    return _FLD2BOOL(SCB_I2C_STATUS_BUS_BUSY, SCB_I2C_STATUS(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_SlaveSetAddress
****************************************************************************//**
*
* Sets the slave address for the I2C slave.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param addr
* The 7-bit right justified slave address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_SlaveSetAddress(CySCB_Type *base, uint8_t addr)
{
    CY_ASSERT_L2(CY_SCB_IS_I2C_ADDR_VALID(addr));

    CY_REG32_CLR_SET(SCB_RX_MATCH(base), SCB_RX_MATCH_ADDR, ((uint32_t)((uint32_t) addr << 1UL)));
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_SlaveGetAddress
****************************************************************************//**
*
* Returns the slave address of the I2C slave.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \return
* The 7-bit right justified slave address.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_I2C_SlaveGetAddress(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_RX_MATCH_ADDR, SCB_RX_MATCH(base)) >> 1UL);
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_SlaveSetAddressMask
****************************************************************************//**
*
* Sets the slave address mask for the I2C slave. The LSBit must always be 0.
* In all other bit positions a 1 indicates that the incoming address must match
* the corresponding bit in the slave address. A 0 in the mask means that the
* incoming address does not need to match.
* Example Slave Address = 0x0C. Slave Address Mask = 0x08. This means that the
* hardware will accept both 0x08 and 0x0C as valid addresses.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param addrMask
* The 8-bit address mask, the upper 7 bits correspond to the slave address.
* LSBit must always be 0.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_SlaveSetAddressMask(CySCB_Type *base, uint8_t addrMask)
{
    CY_ASSERT_L2(CY_SCB_I2C_IS_ADDR_MASK_VALID(addrMask));

    CY_REG32_CLR_SET(SCB_RX_MATCH(base), SCB_RX_MATCH_MASK, ((uint32_t) addrMask));
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_SlaveGetAddressMask
****************************************************************************//**
*
* Returns the slave address mask.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \return
* The 8-bit address mask, the upper 7 bits correspond to the slave address.
* LSBit must always be 0.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_I2C_SlaveGetAddressMask(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_RX_MATCH_MASK, SCB_RX_MATCH(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterSetLowPhaseDutyCycle
****************************************************************************//**
*
* This function sets the number of SCB clock cycles in the low phase of SCL.
* If \ref Cy_SCB_I2C_SetDataRate is called after this function, the values
* specified in this function are overwritten.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param clockCycles
* The number of SCB clock cycles in the low phase of SCL.
* The valid range is 7 to 16.
*
* \note
* This function should be used at your own risk. Changing the number of clock
* cycles in a phase of SCL may violate the I2C specification. Make this
* change only while the block is disabled.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_MasterSetLowPhaseDutyCycle(CySCB_Type *base, uint32_t clockCycles)
{
    CY_ASSERT_L2(CY_SCB_I2C_IS_LOW_PHASE_CYCLES_VALID(clockCycles));

    CY_REG32_CLR_SET(SCB_I2C_CTRL(base), SCB_I2C_CTRL_LOW_PHASE_OVS, (clockCycles - 1UL));
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_MasterSetHighPhaseDutyCycle
****************************************************************************//**
*
* This function sets the number of SCB clock cycles in the high phase of SCL.
* If \ref Cy_SCB_I2C_SetDataRate is called after this function, the values
* specified in this function get overwritten.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param clockCycles
* The number of SCB clock cycles in the high phase of SCL.
* The valid range is 5 to 16.
*
* \note
* This function should be used at your own risk. Changing the number of clock
* cycles in a phase of SCL may violate the I2C specification. Make this
* change only while the block is disabled.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(CySCB_Type *base, uint32_t clockCycles)
{
    CY_ASSERT_L2(CY_SCB_I2C_IS_HIGH_PHASE_CYCLES_VALID(clockCycles));

    CY_REG32_CLR_SET(SCB_I2C_CTRL(base), SCB_I2C_CTRL_HIGH_PHASE_OVS, (clockCycles - 1UL));
}
/** \} group_scb_i2c_general_functions */

/**
* \addtogroup group_scb_i2c_interrupt_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SCB_I2C_RegisterEventCallback
****************************************************************************//**
*
* Registers a callback function that notifies that
* \ref group_scb_i2c_macros_callback_events occurred in the
* \ref Cy_SCB_I2C_Interrupt.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param callback
* The pointer to a callback function.
* See \ref cy_cb_scb_i2c_handle_events_t for the function prototype.
*
* \param context
* The pointer to context structure \ref cy_stc_scb_i2c_context_t allocated by
* the user. The structure is used while the I2C operation for internal
* configuration and data retention. The user should not modify anything in
* this structure.
*
* \note
* To remove the callback, pass NULL as the pointer to the callback function.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_RegisterEventCallback(CySCB_Type const *base,
            cy_cb_scb_i2c_handle_events_t callback, cy_stc_scb_i2c_context_t *context)
{
    /* Suppress a compiler warning about unused variables */
    (void) base;

    context->cbEvents = callback;
}


/*******************************************************************************
* Function Name: Cy_SCB_I2C_RegisterAddrCallback
****************************************************************************//**
*
* Registers a callback function that notifies that
* \ref group_scb_i2c_macros_addr_callback_events occurred in the
* \ref Cy_SCB_I2C_Interrupt.
*
* \param base
* The pointer to the I2C SCB instance.
*
* \param callback
* The pointer to a callback function.
* See \ref cy_cb_scb_i2c_handle_addr_t for the function prototype.
*
* \param context
* The pointer to context structure \ref cy_stc_scb_i2c_context_t allocated by
* the user. The structure is used during the I2C operation for internal
* configuration and data retention. The user should not modify anything in
* this structure.
*
* \note
* To remove the callback, pass NULL as the pointer to a callback function.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_I2C_RegisterAddrCallback(CySCB_Type const *base,
              cy_cb_scb_i2c_handle_addr_t callback, cy_stc_scb_i2c_context_t *context)
{
    /* Suppress a compiler warning about unused variables */
    (void) base;

    context->cbAddr = callback;
}
/** \} group_scb_i2c_interrupt_functions */

#if defined(__cplusplus)
}
#endif

/** \} group_scb_i2c */

#endif /* (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB)) */

#endif /* (CY_SCB_I2C_H) */

/* [] END OF FILE */
