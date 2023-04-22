/***************************************************************************//**
* \file cy_scb_ezi2c.h
* \version 3.0
*
* Provides EZI2C API declarations of the SCB driver.
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
* \addtogroup group_scb_ezi2c
* \{
* Driver API for EZI2C Slave Peripheral
*
* The functions and other declarations used in this part of the driver are in
* cy_scb_ezi2c.h. You can also include cy_pdl.h to get access
* to all functions and declarations in the PDL.
*
* I2C - The Inter-Integrated Circuit (I2C) bus is an industry-standard.
*
* The EZI2C slave peripheral driver provides an API to implement the I2C slave
* device based on the SCB hardware block. This slave device emulates a common
* I2C EEPROM interface that acts like dual-port memory between the external
* master and your code. I2C devices based on the SCB hardware are compatible
* with the I2C Standard mode, Fast mode, and Fast mode Plus specifications, as
* defined in the I2C bus specification.
*
* EZI2C slave is a special implementation of the I2C that handles all communication
* between the master and slave through ISR (interrupt service routine) and requires
* no interaction with the main program flow from the slave side. The EZI2C should be
* used when a shared memory model between the I2C master and I2C slave is needed.
*
* Features:
* * An industry-standard I2C bus interface
* * Supports standard data rates of 100/400/1000 kbps
* * Emulates a common I2C EEPROM Interface
* * Acts like dual-port memory between the external master and your code
* * Supports Hardware Address Match
* * Supports two hardware addresses with separate buffers
* * On deep sleep-capable SCB, it supports wake from deep sleep on address match
* * Simple to set up and use; does not require calling EZI2C API
*   at run time.
*
********************************************************************************
* \section group_scb_ezi2c_configuration Configuration Considerations
********************************************************************************
* The EZI2C slave driver configuration can be divided to number of sequential
* steps listed below:
* * \ref group_scb_ezi2c_config
* * \ref group_scb_ezi2c_pins
* * \ref group_scb_ezi2c_clock
* * \ref group_scb_ezi2c_data_rate
* * \ref group_scb_ezi2c_intr
* * \ref group_scb_ezi2c_enable
*
* \note
* EZI2C slave driver is built on top of the SCB hardware block. The SCB3
* instance is used as an example for all code snippets. Modify the code to
* match your design.
*
********************************************************************************
* \subsection group_scb_ezi2c_config Configure EZI2C slave
********************************************************************************
* To set up the EZI2C slave driver, provide the configuration parameters in the
* \ref cy_stc_scb_ezi2c_config_t structure. The primary slave address
* slaveAddress1 must be provided. The other parameters are optional for
* operation. To initialize the driver, call \ref Cy_SCB_EZI2C_Init
* function providing a pointer to the populated \ref cy_stc_scb_ezi2c_config_t
* structure and the allocated \ref cy_stc_scb_ezi2c_context_t structure.
*
* \snippet scb/ezi2c_snippet/main.c EZI2C_CFG
*
* Set up the EZI2C slave buffer before enabling its
* operation by using \ref Cy_SCB_EZI2C_SetBuffer1 for the primary slave address
* and \ref Cy_SCB_EZI2C_SetBuffer2 for the secondary (if the secondary is enabled).
*
* \snippet scb/ezi2c_snippet/main.c EZI2C_CFG_BUFFER
*
********************************************************************************
* \subsection group_scb_ezi2c_pins Assign and Configure Pins
********************************************************************************
* Only dedicated SCB pins can be used for I2C operation. The HSIOM
* register must be configured to connect dedicated SCB I2C pins to the
* SCB block. Also the I2C pins must be configured in Open-Drain, Drives Low mode
* (this pin configuration implies usage of external pull-up resistors):
*
* \snippet scb/ezi2c_snippet/main.c EZI2C_CFG_PINS
*
* \note
* The alternative pins configuration is Resistive Pull-ups which implies usage
* internal pull-up resistors. This configuration is not recommended because
* resistor value is fixed and cannot be used for all supported data rates.
* Refer to device datasheet parameter RPULLUP for resistor value specifications.
*
********************************************************************************
* \subsection group_scb_ezi2c_clock Assign Clock Divider
********************************************************************************
* A clock source must be connected to the SCB block to oversample input and
* output signals, in this document this clock will be referred as clk_scb.
* You must use one of the 8-bit or 16-bit dividers. Use the \ref group_sysclk
* driver API to do this.
*
* \snippet scb/ezi2c_snippet/main.c EZI2C_CFG_ASSIGN_CLOCK
*
********************************************************************************
* \subsection group_scb_ezi2c_data_rate Configure Data Rate
********************************************************************************
* To get EZI2C slave to operate at the desired data rate, the clk_scb must be
* fast enough to provide sufficient oversampling. Use the
* \ref group_sysclk driver API to do this.
*
* <b>Refer to the technical reference manual (TRM) section I2C sub-section
* Oversampling and Bit Rate to get information about how to configure the
* I2C to run at the desired data rate</b>.
*
* \snippet scb/ezi2c_snippet/main.c EZI2C_CFG_DATA_RATE
*
********************************************************************************
* \subsection group_scb_ezi2c_intr Configure Interrupt
********************************************************************************
* The interrupt is mandatory for the EZI2C slave operation.
* The \ref Cy_SCB_EZI2C_Interrupt function must be called in the interrupt
* handler for the selected SCB instance. Also, this interrupt must be enabled
* in the NVIC or it will not work.
*
* \snippet scb/ezi2c_snippet/main.c EZI2C_INTR_A
* \snippet scb/ezi2c_snippet/main.c EZI2C_INTR_B
*
********************************************************************************
* \subsection group_scb_ezi2c_enable Enable EZI2C slave
********************************************************************************
* Finally, enable the EZI2C slave operation by calling \ref Cy_SCB_EZI2C_Enable.
* Now the I2C device responds to the assigned address.
* \snippet scb/ezi2c_snippet/main.c EZI2C_ENABLE
*
********************************************************************************
* \section group_scb_ezi2c_use_cases Common Use Cases
********************************************************************************
* The EZI2C slave operation might not require calling any EZI2C slave function
* because the I2C master is able to access the slave buffer. The application
* can directly access it as well. Note that this is an application-level task
* to ensure the buffer content integrity.
*
********************************************************************************
* \subsection group_scb_ezi2c_master_wr Master Write operation
********************************************************************************
* This operation starts with sending a base address that is one
* or two bytes, depending on the sub-address size configuration. This base
* address is retained and will be used for later read operations. Following
* the base address, there is a sequence of bytes written into the buffer
* starting from the base address location. The buffer index is incremented
* for each written byte, but this does not affect the base address that is
* retained. The length of a write operation is limited by the maximum buffer
* read/write region size.\n
* When a master attempts to write outside the read/write region or past the
* end of the buffer, the last byte is NACKed.
*
* \image html scb_ezi2c_write.png
*
********************************************************************************
* \subsection group_scb_ezi2c_master_rd Master Read operation
********************************************************************************
* This operation always starts from the base address set by the most
* recent write operation. The buffer index is incremented for each read byte.
* Two sequential read operations start from the same base address no matter
* how many bytes are read. The length of a read operation is not limited by
* the maximum size of the data buffer. The EZI2C slave returns 0xFF bytes
* if the read operation passes the end of the buffer.\n
* Typically, a read operation requires the base address to be updated before
* starting the read. In this case, the write and read operations must be
* combined together.
*
* \image html scb_ezi2c_read.png
*
* The I2C master may use the ReStart or Stop/Start conditions to combine the
* operations. The write operation sets only the base address and the following
* read operation will start from the new base address. In cases where the base
* address remains the same, there is no need for a write operation.
* \image html scb_ezi2c_set_ba_read.png
*
********************************************************************************
* \section group_scb_ezi2c_lp Low Power Support
********************************************************************************
* The EZI2C slave provides the callback functions to handle power mode
* transition. The callback \ref Cy_SCB_EZI2C_DeepSleepCallback must be called
* during execution of \ref Cy_SysPm_CpuEnterDeepSleep;
* \ref Cy_SCB_EZI2C_HibernateCallback must be called during execution of
* \ref Cy_SysPm_SystemEnterHibernate. To trigger the callback execution, the
* callback must be registered before calling the power mode transition function.
* Refer to  \ref group_syspm driver for more information about power mode
* transitions and callback registration.
*
* The EZI2C configured to support two addresses can wakeup the device on
* address match to NACK not supported address. This happens because the
* hardware address-match-logic uses address bit masking to support to two
* addresses. The address mask defines which bits in the address are treated
* as non-significant while performing an address match. One non-significant
* bit results in two matching addresses; two bits will match 4 and so on.
* If the two addresses differ by more than a single bit, then the extra
* addresses that will pass the hardware match and wakeup the device from
* Deep Sleep mode. Then firmware address matching will to generate a NAK.
* Due to this reason, it is preferable to select a secondary address that
* is different from the primary by one bit. The address mask in this case
* makes one bit non-significant.
* For example:
* * Primary address = 0x24 and secondary address = 0x34, only one bit differs.
*   Only the two addresses are treated as matching by the hardware.
* * Primary address = 0x24 and secondary address = 0x30, two bits differ.
*   Four addresses are treated as matching by the hardware: 0x24, 0x34, 0x20
*   and 0x30. Firmware is required to ACK only the primary and secondary
*   addresses 0x24 and 0x30 and NAK all others 0x20 and 0x34.
*
* \note
* Only applicable for <b>rev-08 of the CY8CKIT-062-BLE</b>.
* For proper operation, when the EZI2C slave is configured to be a wakeup
* source from Deep Sleep mode, the \ref Cy_SCB_EZI2C_DeepSleepCallback must
* be copied and modified. Refer to the function description to get the details.
*
* \defgroup group_scb_ezi2c_macros Macros
* \defgroup group_scb_ezi2c_functions Functions
* \{
* \defgroup group_scb_ezi2c_general_functions General
* \defgroup group_scb_ezi2c_slave_functions Slave
* \defgroup group_scb_ezi2c_low_power_functions Low Power Callbacks
* \}
* \defgroup group_scb_ezi2c_data_structures Data Structures
* \defgroup group_scb_ezi2c_enums Enumerated Types
*/

#if !defined(CY_SCB_EZI2C_H)
#define CY_SCB_EZI2C_H

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
* \addtogroup group_scb_ezi2c_enums
* \{
*/

/** EZI2C slave status codes */
typedef enum
{
    /** Operation completed successfully */
    CY_SCB_EZI2C_SUCCESS = 0U,

    /** One or more of input parameters are invalid */
    CY_SCB_EZI2C_BAD_PARAM = (CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_EZI2C_ID | 1U),
} cy_en_scb_ezi2c_status_t;

/** Number of Addresses */
typedef enum
{
    CY_SCB_EZI2C_ONE_ADDRESS,   /**< Only one address */
    CY_SCB_EZI2C_TWO_ADDRESSES  /**< Two addresses */
} cy_en_scb_ezi2c_num_of_addr_t;

/** Size of Sub-Address */
typedef enum
{
    CY_SCB_EZI2C_SUB_ADDR8_BITS,    /**< Sub-address is 8 bits  */
    CY_SCB_EZI2C_SUB_ADDR16_BITS    /**< Sub-address is 16 bits */
} cy_en_scb_ezi2c_sub_addr_size_t;

/** \cond INTERNAL */
/** EZI2C slave FSM states */
typedef enum
{
    CY_SCB_EZI2C_STATE_IDLE,
    CY_SCB_EZI2C_STATE_ADDR,
    CY_SCB_EZI2C_STATE_RX_OFFSET_MSB,
    CY_SCB_EZI2C_STATE_RX_OFFSET_LSB,
    CY_SCB_EZI2C_STATE_RX_DATA0,
    CY_SCB_EZI2C_STATE_RX_DATA1,
    CY_SCB_EZI2C_STATE_TX_DATA
} cy_en_scb_ezi2c_state_t;
/** \endcond */
/** \} group_scb_ezi2c_enums */


/*******************************************************************************
*                            Type Definitions
*******************************************************************************/

/**
* \addtogroup group_scb_ezi2c_data_structures
* \{
*/

/** EZI2C slave configuration structure */
typedef struct cy_stc_scb_ezi2c_config
{
    /** The number of supported addresses either */
    cy_en_scb_ezi2c_num_of_addr_t numberOfAddresses;

    /** The 7-bit right justified primary slave address */
    uint8_t slaveAddress1;

    /** The 7-bit right justified secondary slave address */
    uint8_t slaveAddress2;

    /** The size of the sub-address, can either be 8 or 16 bits */
    cy_en_scb_ezi2c_sub_addr_size_t subAddressSize;

    /**
    * When set, the slave will wake the device from Deep Sleep on an address
    * match (The device datasheet must be consulted to determine which SCBs
    * support this mode)
    */
    bool enableWakeFromSleep;
} cy_stc_scb_ezi2c_config_t;

/** EZI2C slave context structure.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct cy_stc_scb_ezi2c_context
{
    /** \cond INTERNAL */
    volatile cy_en_scb_ezi2c_state_t state;  /**< The driver state */
    volatile uint32_t status;                /**< The slave status */

    uint8_t  address1;      /**< The primary slave address (7-bits right justified) */
    uint8_t  address2;      /**< The secondary slave address (7-bits right justified) */
    cy_en_scb_ezi2c_sub_addr_size_t subAddrSize;   /**< The sub-address size */

    uint32_t idx;       /**< The index within the buffer during operation */
    uint32_t baseAddr1; /**< The valid base address for the primary slave address */
    uint32_t baseAddr2; /**< The valid base address for the secondary slave address */

    bool     addr1Active; /**< Defines whether the request is intended for the primary slave address */
    uint8_t  *curBuf;     /**< The pointer to the current location in the buffer (while it is accessed) */
    uint32_t bufSize;     /**< Specifies how many bytes are left in the current buffer */

    uint8_t *buf1;          /**< The pointer to the buffer exposed  on the request intended for the primary slave address */
    uint32_t buf1Size;      /**< The buffer size assigned to the primary slave address */
    uint32_t buf1rwBondary; /**< The Read/Write boundary within the buffer assigned to the primary slave address */

    uint8_t *buf2;          /**< The pointer to the buffer exposed on the request intended for the secondary slave address */
    uint32_t buf2Size;      /**< The buffer size assigned to the secondary slave address */
    uint32_t buf2rwBondary; /**< The Read/Write boundary within the buffer assigned for the secondary slave address */
    /** \endcond */
} cy_stc_scb_ezi2c_context_t;
/** \} group_scb_ezi2c_data_structures */


/*******************************************************************************
*                           Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_scb_ezi2c_general_functions
* \{
*/
cy_en_scb_ezi2c_status_t Cy_SCB_EZI2C_Init(CySCB_Type *base, cy_stc_scb_ezi2c_config_t const *config,
                                           cy_stc_scb_ezi2c_context_t *context);
void     Cy_SCB_EZI2C_DeInit(CySCB_Type *base);
__STATIC_INLINE void Cy_SCB_EZI2C_Enable(CySCB_Type *base);
void     Cy_SCB_EZI2C_Disable(CySCB_Type *base, cy_stc_scb_ezi2c_context_t *context);

void     Cy_SCB_EZI2C_SetAddress1(CySCB_Type *base, uint8_t addr, cy_stc_scb_ezi2c_context_t *context);
uint32_t Cy_SCB_EZI2C_GetAddress1(CySCB_Type const *base, cy_stc_scb_ezi2c_context_t const *context);

void     Cy_SCB_EZI2C_SetAddress2(CySCB_Type *base, uint8_t addr, cy_stc_scb_ezi2c_context_t *context);
uint32_t Cy_SCB_EZI2C_GetAddress2(CySCB_Type const *base, cy_stc_scb_ezi2c_context_t const *context);
/** \} group_scb_ezi2c_general_functions */

/**
* \addtogroup group_scb_ezi2c_slave_functions
* \{
*/
void Cy_SCB_EZI2C_SetBuffer1(CySCB_Type const *base, uint8_t *buffer, uint32_t size, uint32_t rwBoundary,
                             cy_stc_scb_ezi2c_context_t *context);
void Cy_SCB_EZI2C_SetBuffer2(CySCB_Type const *base, uint8_t *buffer, uint32_t size, uint32_t rwBoundary,
                             cy_stc_scb_ezi2c_context_t *context);

uint32_t Cy_SCB_EZI2C_GetActivity(CySCB_Type const *base, cy_stc_scb_ezi2c_context_t *context);

void Cy_SCB_EZI2C_Interrupt(CySCB_Type *base, cy_stc_scb_ezi2c_context_t *context);
/** \} group_scb_ezi2c_slave_functions */

/**
* \addtogroup group_scb_ezi2c_low_power_functions
* \{
*/
cy_en_syspm_status_t Cy_SCB_EZI2C_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
cy_en_syspm_status_t Cy_SCB_EZI2C_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
/** \} group_scb_ezi2c_low_power_functions */


/*******************************************************************************
*                              API Constants
*******************************************************************************/

/**
* \addtogroup group_scb_ezi2c_macros
* \{
*/

/**
* \defgroup group_scb_ezi2c_macros_get_activity EZI2C Activity Status
* Macros to check current EZI2C activity slave status returned by
* \ref Cy_SCB_EZI2C_GetActivity function. Each EZI2C slave status is encoded
* in a separate bit, therefore multiple bits may be set to indicate the
* current status.
* \{
*/

/**
* The Read transfer intended for the primary slave address is complete.
* The error condition status bit must be checked to ensure that the Read
* transfer was completed successfully.
*/
#define CY_SCB_EZI2C_STATUS_READ1       (0x01UL)

/**
* The Write transfer intended for the primary slave address is complete.
* The buffer content was modified.
* The error condition status bit must be checked to ensure that the Write
* transfer was completed successfully.
*/
#define CY_SCB_EZI2C_STATUS_WRITE1      (0x02UL)

/**
* The Read transfer intended for the secondary slave address is complete.
* The error condition status bit must be checked to ensure that the Read
* transfer was completed successfully.
*/
#define CY_SCB_EZI2C_STATUS_READ2       (0x04UL)

/**
* The Write transfer intended for the secondary slave address is complete.
* The buffer content was modified.
* The error condition status bit must be checked to ensure that the Write
* transfer was completed successfully.
*/
#define CY_SCB_EZI2C_STATUS_WRITE2       (0x08UL)

/**
* A transfer intended for the primary address or secondary address is in
* progress. The status bit is set after an address match and cleared
* on a Stop or ReStart condition.
*/
#define CY_SCB_EZI2C_STATUS_BUSY        (0x10UL)

/**
* An error occurred during a transfer intended for the primary or secondary
* slave address. The sources of the error are: a misplaced Start or Stop
* condition or lost arbitration while the slave drives SDA.
* When CY_SCB_EZI2C_STATUS_ERR is set, the slave buffer may contain an
* invalid byte. Discard the buffer content in this case.
*/
#define CY_SCB_EZI2C_STATUS_ERR         (0x20UL)
/** \} group_scb_ezi2c_macros_get_activity */

/**
* This value is returned by the slave when the buffer is not configured or
* the master requests more bytes than are available in the buffer.
*/
#define CY_SCB_EZI2C_DEFAULT_TX  (0xFFUL)


/*******************************************************************************
*                          Internal Constants
*******************************************************************************/

/** \cond INTERNAL */
/* Default registers values */
#if ((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
#define CY_SCB_EZI2C_I2C_CTRL   (SCB_I2C_CTRL_S_GENERAL_IGNORE_Msk | SCB_I2C_CTRL_SLAVE_MODE_Msk | \
                                 SCB_I2C_CTRL_S_READY_ADDR_ACK_Msk | SCB_I2C_CTRL_S_READY_DATA_ACK_Msk)
#elif (CY_IP_MXSCB_VERSION==1)
#define CY_SCB_EZI2C_I2C_CTRL   (SCB_I2C_CTRL_S_GENERAL_IGNORE_Msk | SCB_I2C_CTRL_SLAVE_MODE_Msk)
#endif /* CY_IP_MXSCB_VERSION */
#define CY_SCB_EZI2C_RX_CTRL    (CY_SCB_I2C_RX_CTRL)
#define CY_SCB_EZI2C_TX_CTRL    (CY_SCB_I2C_TX_CTRL)

#define CY_SCB_EZI2C_SLAVE_INTR     (CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH | CY_SCB_SLAVE_INTR_I2C_STOP | \
                                     CY_SCB_SLAVE_INTR_I2C_BUS_ERROR  | CY_SCB_SLAVE_INTR_I2C_ARB_LOST)
/* Error interrupt sources */
#define CY_SCB_EZI2C_SLAVE_INTR_ERROR   (CY_SCB_SLAVE_INTR_I2C_BUS_ERROR  | CY_SCB_SLAVE_INTR_I2C_ARB_LOST)

/* Disables Stop interrupt source */
#define CY_SCB_EZI2C_SLAVE_INTR_NO_STOP (CY_SCB_EZI2C_SLAVE_INTR & ((uint32_t) ~CY_SCB_SLAVE_INTR_I2C_STOP))

/* Disable Address interrupt source */
#define CY_SCB_EZI2C_SLAVE_INTR_NO_ADDR (CY_SCB_EZI2C_SLAVE_INTR & ((uint32_t) ~CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH))

/* FIFO size */
#define CY_SCB_EZI2C_FIFO_SIZE          CY_SCB_FIFO_SIZE
#define CY_SCB_EZI2C_HALF_FIFO_SIZE    (CY_SCB_FIFO_SIZE / 2UL)

#define CY_SCB_EZI2C_ONE_ADDRESS_MASK   (0xFFUL)

#define CY_SCB_EZI2C_IS_NUM_OF_ADDR_VALID(numAddr)  ( (CY_SCB_EZI2C_ONE_ADDRESS   == (numAddr)) || \
                                                      (CY_SCB_EZI2C_TWO_ADDRESSES == (numAddr)) )

#define CY_SCB_EZI2C_IS_SUB_ADDR_SIZE_VALID(subAddrSize)    ( (CY_SCB_EZI2C_SUB_ADDR8_BITS  == (subAddrSize)) || \
                                                              (CY_SCB_EZI2C_SUB_ADDR16_BITS == (subAddrSize)) )
/** \endcond */
/** \} group_scb_ezi2c_macros */


/*******************************************************************************
*                  In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_scb_ezi2c_general_functions
* \{
*/
/*******************************************************************************
* Function Name: Cy_SCB_EZI2C_Enable
****************************************************************************//**
*
* Enables the SCB block for the EZI2C operation
*
* \param base
* The pointer to the EZI2C SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_EZI2C_Enable(CySCB_Type *base)
{
    SCB_CTRL(base) |= SCB_CTRL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_SCB_SetEzI2CMode
****************************************************************************//**
*
* Sets EZ mode for I2C protocol.
* EZ mode is only used for synchronous serial interface protocols.
* This mode is only applicable to slave functionality.
* In EZ mode, the slave can read from and write to an addressable memory.
*
* \param base
* The pointer to the EZI2C SCB instance.
*
* \param ezMode
* If true, HW EZ mode is enabled. If false, HW EZ mode is disabled.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetEzI2CMode(CySCB_Type *base, bool ezMode)
{
    if(ezMode)
    {
        SCB_CTRL(base) |= SCB_CTRL_EZ_MODE_Msk;
    }
    else
    {
        SCB_CTRL(base) &= ~(SCB_CTRL_EZ_MODE_Msk);
    }
}


/** \} group_scb_ezi2c_general_functions */

#if defined(__cplusplus)
}
#endif

/** \} group_scb_ezi2c */

#endif /* (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB)) */

#endif /* (CY_SCB_EZI2C_H) */
/* [] END OF FILE */
