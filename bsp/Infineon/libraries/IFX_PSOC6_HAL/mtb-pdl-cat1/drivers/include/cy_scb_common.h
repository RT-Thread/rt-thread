/***************************************************************************//**
* \file cy_scb_common.h
* \version 3.0
*
* Provides common API declarations of the SCB driver.
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
* \addtogroup group_scb
* \{
* The Serial Communications Block (SCB) supports three serial communication
* protocols: Serial Peripheral Interface (SPI), Universal Asynchronous Receiver
* Transmitter (UART), and Inter Integrated Circuit (I2C or IIC). Only one of
* the protocols is supported by an SCB at any given time.
*
* The functions and other declarations used in this driver are in cy_scb_spi.h,
* cy_scb_uart.h, cy_scb_ezi2c.h, cy_scb_i2c.h respectively. Include cy_pdl.h
* to get access to all functions and declarations in the PDL.

* \defgroup group_scb_common Common
* \defgroup group_scb_ezi2c  EZI2C (SCB)
* \defgroup group_scb_i2c    I2C (SCB)
* \defgroup group_scb_spi    SPI (SCB)
* \defgroup group_scb_uart   UART (SCB)
* \} */

/**
* \addtogroup group_scb
* \{
*
********************************************************************************
* \section group_scb_more_information More Information
********************************************************************************
* For more information on the SCB peripheral, refer to the technical reference
* manual (TRM).
*
*******************************************************************************
* \section group_scb_common_changelog Changelog
*******************************************************************************
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td rowspan="2">3.0</td>
*     <td>Updated \ref Cy_SCB_SPI_Init and other internal data handling functions to handle wide range of data widths.</td>
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">2.90</td>
*     <td>A new API, \ref Cy_SCB_SetEzI2CMode, has been added to help set the hardware EZ mode for the I2C protocol.</td>
*     <td>The HW EZ Mode for the I2C protocol can be enabled or disabled.</td>
*   </tr>
*   <tr>
*     <td>Newly added APIs \ref Cy_SCB_I2C_SetStretchThreshold to set the stretch threshold value,
*         \ref Cy_SCB_I2C_GetStretchCount to get the stretch count,
*         \ref Cy_SCB_I2C_IsStretchDetected to detect if I2C SCL is stretched,
*         \ref Cy_SCB_I2C_IsSyncDetected to check if synchronization is detected on I2C SCL.
*         \ref Cy_SCB_I2C_IsStretching to check if DUT is stretching the I2C SCL.</td>
*     <td>New device support.</td>
*   </tr>
*   <tr>
*     <td>2.80</td>
*     <td>Updated the behaviour of \ref Cy_SCB_UART_SetEnableMsbFirst and \ref Cy_SCB_UART_GetEnableMsbFirst functions.
*         Now the value of enableMsbFirst is being set and fetched correctly.
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">2.70</td>
*     <td>Newly added API's for runtime parameter set/get functionality which include
*         \ref Cy_SCB_UART_SetOverSample to set oversample bits of UART,
*         \ref Cy_SCB_UART_GetOverSample to add return value of oversample,
*         \ref Cy_SCB_UART_GetDataWidth to get data width,
*         \ref Cy_SCB_UART_SetDataWidth to set data width,
*         \ref Cy_SCB_UART_GetParity to get parity,
*         \ref Cy_SCB_UART_SetParity to set parity,
*         \ref Cy_SCB_UART_GetStopBits to get stop bits,
*         \ref Cy_SCB_UART_SetStopBits to set stop bits,
*         \ref Cy_SCB_UART_GetDropOnParityError to get drop on parity error,
*         \ref Cy_SCB_UART_SetDropOnParityError to set drop on parity error,
*         \ref Cy_SCB_UART_GetEnableMsbFirst to get enable MSB first and
*         \ref Cy_SCB_UART_SetEnableMsbFirst to set enable MSB first.</td>
*     <td>Runtime Parameter update.</td>
*   </tr>
*   <tr>
*     <td>Newly added API's which include
*         \ref Cy_SCB_Get_RxDataWidth to return the RX data width,
*         \ref Cy_SCB_Get_TxDataWidth to return the TX data width,
*         \ref Cy_SCB_SetMemWidth to set the RX and TX FIFOs byte mode/halfword/word mode.
*         Updated Structures \ref cy_stc_scb_uart_config_t, \ref cy_en_scb_spi_parity_t, \ref cy_stc_scb_spi_config_t.</td>
*     <td>New device support.</td>
*   </tr>
*   <tr>
*     <td  rowspan="2">2.60</td>
*     <td>Fixed the \ref Cy_SCB_UART_GetNumInRingBuffer function to
*         return correct number of the elements in ring buffer.</td>
*     <td> \ref Cy_SCB_UART_GetNumInRingBuffer function works incorrectly, when
*         write pointer of the ring buffer is behind the read pointer.</td>
*   </tr>
*   <tr>
*     <td>Fixed/Documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>2.50</td>
*     <td>Fixed the \ref Cy_SCB_SPI_SetActiveSlaveSelectPolarity function to
*         properly configure the polarity of the slave select line.</td>
*     <td> \ref Cy_SCB_SPI_SetActiveSlaveSelectPolarity function works incorrectly.</td>
*   </tr>
*   <tr>
*     <td>2.40.2</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">2.40</td>
*     <td>Update level selection logic of RX FIFO trigger in the Cy_SCB_UART_Receive().</td>
*     <td>Fix possible stuck if the RTS level is less than the RX FIFO level.</td>
*   </tr>
*   <tr>
*     <td>Exclude self-test assertion macros under release build profile.</td>
*     <td>Avoid dependency on CY_ASSERT macro implementation.</td>
*   </tr>
*   <tr>
*     <td>2.30.1</td>
*     <td>Added header guards CY_IP_MXSCB.</td>
*     <td>To enable the PDL compilation with wounded out IP blocks.</td>
*   </tr>
*   <tr>
*     <td rowspan="5">2.30</td>
*     <td>Fixed MISRA violation.</td>
*     <td>MISRA compliance.</td>
*   </tr>
*   <tr>
*     <td>Changed values CY_SCB_SPI_CPHA0_CPOL1 and CY_SCB_SPI_CPHA1_CPOL0 in enum \ref cy_en_scb_spi_sclk_mode_t.</td>
*     <td>The incorrect values in \ref cy_en_scb_spi_sclk_mode_t caused incorrect initialization of the combination of
*         phases and polarity: "CHPA = 0, CPOL = 1" and "CHPA = 1, CPOL = 0".
*     </td>
*   </tr>
*   <tr>
*     <td>Added new CY_SCB_UART_RECEIVE_NOT_EMTPY and CY_SCB_UART_TRANSMIT_EMTPY callback events \ref group_scb_uart_macros_callback_events.</td>
*     <td>Extended the driver callback events to support the MBED-OS.</td>
*   </tr>
*   <tr>
*     <td>Merged SCB changelogs for each mode into one changelog.</td>
*     <td>Changelog optimization.</td>
*   </tr>
*   <tr>
*     <td>Merged SCB MISRA-C Compliance sections for each mode into one section.</td>
*     <td>To optimize the SCB MISRA-C Compliance sections.</td>
*   </tr>
*   <tr>
*     <td> 2.20.1</td>
*     <td>Documentation of the MISRA rule violation.</td>
*     <td>MISRA compliance.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">2.20</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>Added the enableDigitalFilter, highPhaseDutyCycle and lowPhaseDutyCycle
*         fields to the \ref cy_stc_scb_i2c_config_t configuration structure.
*     </td>
*     <td>Added the I2C master data rate configuration using the configuration structure.
*     </td>
*   </tr>
*   <tr>
*     <td>Fixed the \ref Cy_SCB_I2C_SetDataRate function to properly configure data rates
*         greater than 400 kbps in Master and Master-Slave modes. \n
*         Added verification that clk_scb is within the valid range for the desired data rate.
*     </td>
*     <td>The analog filter was enabled for all data rates in Master and Master-Slave modes.
*         This prevents reaching the maximum supported data rate of 1000 kbps which requires a digital filter.
*     </td>
*   </tr>
*   <tr>
*     <td rowspan="4"> 2.10</td>
*     <td>Fixed the ReStart condition generation sequence for a write
*         transaction in the \ref Cy_SCB_I2C_MasterWrite function.</td>
*     <td>The driver can notify about a zero length write transaction completion
*         before the address byte is sent if the \ref Cy_SCB_I2C_MasterWrite
*         function execution was interrupted between setting the restart
*         generation command and writing the address byte into the TX FIFO.</td>
*   </tr>
*   <tr>
*     <td>Added the slave- and master-specific interrupt functions:
*         \ref Cy_SCB_I2C_SlaveInterrupt and \ref Cy_SCB_I2C_MasterInterrupt.
*     </td>
*     <td>Improved the interrupt configuration options for the I2C slave and
*         master mode configurations.</td>
*   </tr>
*   <tr>
*     <td>Updated the Start condition generation sequence in the \ref
*         Cy_SCB_I2C_MasterWrite and \ref Cy_SCB_I2C_MasterRead.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>Updated the ReStart condition generation sequence for a write
*         transaction in the \ref Cy_SCB_I2C_MasterSendReStart function.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td rowspan="9"> 2.0</td>
*     <td>Added parameters validation for public API.
*     <td></td>
*   </tr>
*   <tr>
*     <td>Fixed functions which return interrupt status to return only defined
*         set of interrupt statuses.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>Added missing "cy_cb_" to the callback function type names.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>Replaced variables that have limited range of values with enumerated
*         types.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>Added function \ref Cy_SCB_UART_SendBreakBlocking for break condition
*         generation.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>Fixed low power callbacks \ref Cy_SCB_UART_DeepSleepCallback and
*         \ref Cy_SCB_UART_HibernateCallback to prevent the device from entering
*         low power mode when RX FIFO is not empty.</td>
*     <td>The callbacks allowed entering device into low power mode when RX FIFO
*         had data.</td>
*   </tr>
*   <tr>
*     <td>Fixed SPI callback notification when error event occurred.</td>
*     <td>The SPI callback passed incorrect event value if error event occurred.</td>
*   </tr>
*   <tr>
*     <td>Fixed the \ref Cy_SCB_I2C_MasterSendReStart function to properly
*         generate the ReStart condition when the previous transaction was
*         a write.</td>
*     <td>The master interpreted the address byte written into the TX FIFO as a
*         data byte and continued a write transaction. The ReStart condition was
*         generated after the master completed transferring the data byte.
*         The SCL line was stretched by the master waiting for the address byte
*         to be written into the TX FIFO after the ReStart condition generation.
*         The following timeout detection released the bus from the master
*         control.</td>
*   </tr>
*   <tr>
*     <td>Fixed the slave operation after the address byte was NACKed by the
*         firmware.</td>
*     <td>The observed slave operation failure depends on whether Level 2 assert
*         is enabled or not. Enabled: the device stuck in the fault handler due
*         to the assert assignment in the \ref Cy_SCB_I2C_Interrupt. Disabled:
*         the slave sets the transaction completion status and notifies on the
*         transaction completion event after the address was NACKed. The failure
*         is observed only when the slave is configured to accept an address in
*         the RX FIFO.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version.</td>
*     <td></td>
*   </tr>
* </table>
*/

/** \} group_scb */
/**
* \addtogroup group_scb_common
* \{
*
* Common API for the Serial Communication Block.
*
* This is the common API that provides an interface to the SCB hardware.
* The I2C, SPI, and UART drivers use this common API.
* Most users will use individual drivers and do not need to use the common
* API for the SCB. However, you can use the common SCB API to implement
* a custom driver based on the SCB hardware.
*
* The functions and other declarations used in this part of the driver are in
* cy_scb_common.h. You can include either of cy_scb_spi.h, cy_scb_uart.h,
* cy_scb_ezi2c.h, cy_scb_i2c.h depending on the desired functionality.
* You can also include cy_pdl.h to get access to all functions and declarations
* in the PDL.
*
*******************************************************************************
* \section group_scb_common_configuration Configuration Considerations
********************************************************************************
* This is not a driver and it does not require configuration.
*
* \defgroup group_scb_common_macros Macros
* \defgroup group_scb_common_functions Functions
* \defgroup group_scb_common_data_structures Data Structures
*
*/

#if !defined(CY_SCB_COMMON_H)
#define CY_SCB_COMMON_H

#include "cy_device.h"

#if (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB))

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                            Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_scb_common_functions
* \{
*/
__STATIC_FORCEINLINE uint32_t Cy_SCB_ReadRxFifo    (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetRxFifoLevel(CySCB_Type *base, uint32_t level);
__STATIC_INLINE uint32_t Cy_SCB_GetNumInRxFifo(CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetRxSrValid  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearRxFifo   (CySCB_Type *base);

__STATIC_FORCEINLINE void     Cy_SCB_WriteTxFifo   (CySCB_Type *base, uint32_t data);
__STATIC_INLINE void     Cy_SCB_SetTxFifoLevel(CySCB_Type *base, uint32_t level);
__STATIC_INLINE uint32_t Cy_SCB_GetNumInTxFifo(CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetTxSrValid  (CySCB_Type const *base);
__STATIC_INLINE bool     Cy_SCB_IsTxComplete  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearTxFifo   (CySCB_Type *base);

__STATIC_INLINE void     Cy_SCB_SetByteMode(CySCB_Type *base, bool byteMode);

__STATIC_INLINE uint32_t Cy_SCB_GetInterruptCause(CySCB_Type const *base);

__STATIC_INLINE uint32_t Cy_SCB_GetRxInterruptStatus(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetRxInterruptMask  (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SCB_GetRxInterruptMask  (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetRxInterruptStatusMasked(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearRxInterrupt    (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE void     Cy_SCB_SetRxInterrupt      (CySCB_Type *base, uint32_t interruptMask);

__STATIC_INLINE uint32_t Cy_SCB_GetTxInterruptStatus(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetTxInterruptMask  (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SCB_GetTxInterruptMask  (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetTxInterruptStatusMasked(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearTxInterrupt    (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE void     Cy_SCB_SetTxInterrupt      (CySCB_Type *base, uint32_t interruptMask);

__STATIC_INLINE uint32_t Cy_SCB_GetMasterInterruptStatus(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetMasterInterruptMask  (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SCB_GetMasterInterruptMask  (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetMasterInterruptStatusMasked(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearMasterInterrupt    (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE void     Cy_SCB_SetMasterInterrupt      (CySCB_Type *base, uint32_t interruptMask);

__STATIC_INLINE uint32_t Cy_SCB_GetSlaveInterruptStatus(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetSlaveInterruptMask  (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SCB_GetSlaveInterruptMask  (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetSlaveInterruptStatusMasked(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearSlaveInterrupt    (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE void     Cy_SCB_SetSlaveInterrupt      (CySCB_Type *base, uint32_t interruptMask);

__STATIC_INLINE uint32_t Cy_SCB_GetI2CInterruptStatus(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetI2CInterruptMask  (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SCB_GetI2CInterruptMask  (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetI2CInterruptStatusMasked(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearI2CInterrupt    (CySCB_Type *base, uint32_t interruptMask);

__STATIC_INLINE uint32_t Cy_SCB_GetSpiInterruptStatus(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SetSpiInterruptMask  (CySCB_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SCB_GetSpiInterruptMask  (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetSpiInterruptStatusMasked(CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_ClearSpiInterrupt    (CySCB_Type *base, uint32_t interruptMask);


/*******************************************************************************
*                         Internal Function Prototypes
*******************************************************************************/

/** \cond INTERNAL */
void     Cy_SCB_ReadArrayNoCheck  (CySCB_Type const *base, void *buffer, uint32_t size);
uint32_t Cy_SCB_ReadArray         (CySCB_Type const *base, void *buffer, uint32_t size);
void     Cy_SCB_ReadArrayBlocking (CySCB_Type const *base, void *buffer, uint32_t size);
uint32_t Cy_SCB_Write             (CySCB_Type *base, uint32_t data);
void     Cy_SCB_WriteArrayNoCheck (CySCB_Type *base, void *buffer, uint32_t size);
uint32_t Cy_SCB_WriteArray        (CySCB_Type *base, void *buffer, uint32_t size);
void     Cy_SCB_WriteArrayBlocking(CySCB_Type *base, void *buffer, uint32_t size);
void     Cy_SCB_WriteString       (CySCB_Type *base, char_t const string[]);
void     Cy_SCB_WriteDefaultArrayNoCheck(CySCB_Type *base, uint32_t txData, uint32_t size);
uint32_t Cy_SCB_WriteDefaultArray (CySCB_Type *base, uint32_t txData, uint32_t size);

__STATIC_INLINE uint32_t Cy_SCB_GetFifoSize (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_FwBlockReset(CySCB_Type *base);
__STATIC_INLINE bool     Cy_SCB_IsRxDataWidthByte(CySCB_Type const *base);
__STATIC_INLINE bool     Cy_SCB_IsTxDataWidthByte(CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_GetRxFifoLevel   (CySCB_Type const *base);
#if((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
__STATIC_INLINE uint32_t Cy_SCB_Get_RxDataWidth(CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_Get_TxDataWidth(CySCB_Type const *base);
#endif /* CY_IP_MXSCB_VERSION */
/** \endcond */

/** \} group_scb_common_functions */


/*******************************************************************************
*                        API Constants
*******************************************************************************/

/**
* \addtogroup group_scb_common_macros
* \{
*/

/** Driver major version */
#define CY_SCB_DRV_VERSION_MAJOR    (3)

/** Driver minor version */
#define CY_SCB_DRV_VERSION_MINOR    (0)

/** SCB driver identifier */
#define CY_SCB_ID           CY_PDL_DRV_ID(0x2AU)

/** Position for SCB driver sub mode */
#define CY_SCB_SUB_MODE_Pos (13UL)

/** EZI2C mode identifier */
#define CY_SCB_EZI2C_ID     (0x0UL << CY_SCB_SUB_MODE_Pos)

/** I2C mode identifier */
#define CY_SCB_I2C_ID       (0x1UL << CY_SCB_SUB_MODE_Pos)

/** SPI mode identifier */
#define CY_SCB_SPI_ID       (0x2UL << CY_SCB_SUB_MODE_Pos)

/** UART mode identifier */
#define CY_SCB_UART_ID      (0x3UL << CY_SCB_SUB_MODE_Pos)

/**
* \defgroup group_scb_common_macros_intr_cause SCB Interrupt Causes
* \{
*/
/** Interrupt from Master interrupt sources */
#define CY_SCB_MASTER_INTR SCB_INTR_CAUSE_M_Msk

/** Interrupt from Slave interrupt sources  */
#define CY_SCB_SLAVE_INTR  SCB_INTR_CAUSE_S_Msk

/** Interrupt from TX interrupt sources */
#define CY_SCB_TX_INTR     SCB_INTR_CAUSE_TX_Msk

/** Interrupt from RX interrupt sources */
#define CY_SCB_RX_INTR     SCB_INTR_CAUSE_RX_Msk

/** Interrupt from I2C externally clocked interrupt sources */
#define CY_SCB_I2C_INTR    SCB_INTR_CAUSE_I2C_EC_Msk

/** Interrupt from SPI externally clocked interrupt sources */
#define CY_SCB_SPI_INTR    SCB_INTR_CAUSE_SPI_EC_Msk
/** \} group_scb_common_macros_intr_cause */

/**
* \defgroup group_scb_common_macros_tx_intr TX Interrupt Statuses
* \{
*/
/**
* The number of data elements in the TX FIFO is less than the value
* of the TX FIFO level
*/
#define CY_SCB_TX_INTR_LEVEL           SCB_INTR_TX_TRIGGER_Msk

/** The TX FIFO is not full */
#define CY_SCB_TX_INTR_NOT_FULL        SCB_INTR_TX_NOT_FULL_Msk

/** The TX FIFO is empty */
#define CY_SCB_TX_INTR_EMPTY           SCB_INTR_TX_EMPTY_Msk

/** An attempt to write to a full TX FIFO */
#define CY_SCB_TX_INTR_OVERFLOW        SCB_INTR_TX_OVERFLOW_Msk

/** An attempt to read from an empty TX FIFO */
#define CY_SCB_TX_INTR_UNDERFLOW       SCB_INTR_TX_UNDERFLOW_Msk

/** The UART transfer is complete: all data elements from the TX FIFO are sent
*/
#define CY_SCB_TX_INTR_UART_DONE       SCB_INTR_TX_UART_DONE_Msk

/** SmartCard only: UART received a NACK */
#define CY_SCB_TX_INTR_UART_NACK       SCB_INTR_TX_UART_NACK_Msk

/**
* SmartCard only: the value on the TX line of the UART does not match the
* value on the RX line
*/
#define CY_SCB_TX_INTR_UART_ARB_LOST   SCB_INTR_TX_UART_ARB_LOST_Msk
/** \} group_scb_common_macros_tx_intr */

/**
* \defgroup group_scb_common_macros_rx_intr RX Interrupt Statuses
* \{
*/
/**
* The number of data elements in the RX FIFO is greater than the value of the
* RX FIFO level
*/
#define CY_SCB_RX_INTR_LEVEL             SCB_INTR_RX_TRIGGER_Msk

/** The RX FIFO is not empty */
#define CY_SCB_RX_INTR_NOT_EMPTY         SCB_INTR_RX_NOT_EMPTY_Msk

/** The RX FIFO is full */
#define CY_SCB_RX_INTR_FULL              SCB_INTR_RX_FULL_Msk

/** An attempt to write to a full RX FIFO */
#define CY_SCB_RX_INTR_OVERFLOW          SCB_INTR_RX_OVERFLOW_Msk

/** An attempt to read from an empty RX FIFO */
#define CY_SCB_RX_INTR_UNDERFLOW         SCB_INTR_RX_UNDERFLOW_Msk

/** A UART framing error detected */
#define CY_SCB_RX_INTR_UART_FRAME_ERROR  SCB_INTR_RX_FRAME_ERROR_Msk

/** A UART parity error detected  */
#define CY_SCB_RX_INTR_UART_PARITY_ERROR SCB_INTR_RX_PARITY_ERROR_Msk

/** A UART break detected */
#define CY_SCB_RX_INTR_UART_BREAK_DETECT SCB_INTR_RX_BREAK_DETECT_Msk
/** \} group_scb_common_macros_rx_intr */

/**
* \defgroup group_scb_common_macros_slave_intr Slave Interrupt Statuses
* \{
*/
/**
* I2C slave lost arbitration: the value driven on the SDA line is not the same
* as the value observed on the SDA line
*/
#define CY_SCB_SLAVE_INTR_I2C_ARB_LOST      SCB_INTR_S_I2C_ARB_LOST_Msk

/** The I2C slave received a NAK */
#define CY_SCB_SLAVE_INTR_I2C_NACK          SCB_INTR_S_I2C_NACK_Msk

/** The I2C slave received  an ACK */
#define CY_SCB_SLAVE_INTR_I2C_ACK           SCB_INTR_S_I2C_ACK_Msk

/**
* A Stop or Repeated Start event for a write transfer intended for this slave
* was detected.
*/
#define CY_SCB_SLAVE_INTR_I2C_WRITE_STOP    SCB_INTR_S_I2C_WRITE_STOP_Msk

/** A Stop or Repeated Start event intended for this slave was detected */
#define CY_SCB_SLAVE_INTR_I2C_STOP          SCB_INTR_S_I2C_STOP_Msk

/** The I2C slave received a Start condition */
#define CY_SCB_SLAVE_INTR_I2C_START         SCB_INTR_S_I2C_START_Msk

/** The I2C slave received the matching address */
#define CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH    SCB_INTR_S_I2C_ADDR_MATCH_Msk

/** The I2C Slave received the general call address */
#define CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR  SCB_INTR_S_I2C_GENERAL_Msk

/** The I2C slave bus error (detection of unexpected Start or Stop condition) */
#define CY_SCB_SLAVE_INTR_I2C_BUS_ERROR     SCB_INTR_S_I2C_BUS_ERROR_Msk

/**
* The SPI slave select line is deselected at an expected time during an
* SPI transfer.
*/
#define CY_SCB_SLAVE_INTR_SPI_BUS_ERROR     SCB_INTR_S_SPI_BUS_ERROR_Msk
/** \} group_scb_common_macros_slave_intr */

/**
* \defgroup group_scb_common_macros_master_intr Master Interrupt Statuses
* \{
*/
/** The I2C master lost arbitration */
#define CY_SCB_MASTER_INTR_I2C_ARB_LOST    SCB_INTR_M_I2C_ARB_LOST_Msk

/** The I2C master received a NACK */
#define CY_SCB_MASTER_INTR_I2C_NACK        SCB_INTR_M_I2C_NACK_Msk

/** The I2C master received an ACK */
#define CY_SCB_MASTER_INTR_I2C_ACK         SCB_INTR_M_I2C_ACK_Msk

/** The I2C master generated a Stop */
#define CY_SCB_MASTER_INTR_I2C_STOP        SCB_INTR_M_I2C_STOP_Msk

/** The I2C master bus error (detection of unexpected START or STOP condition)
*/
#define CY_SCB_MASTER_INTR_I2C_BUS_ERROR   SCB_INTR_M_I2C_BUS_ERROR_Msk

/**
* The SPI master transfer is complete: all data elements transferred from the
* TX FIFO and TX shift register.
*/
#define CY_SCB_MASTER_INTR_SPI_DONE        SCB_INTR_M_SPI_DONE_Msk
/** \} group_scb_common_macros_master_intr */

/**
* \defgroup group_scb_common_macros_i2c_intr I2C Interrupt Statuses
* \{
*/
/**
* Wake up request: the I2C slave received the matching address.
* Note that this interrupt source triggers in active mode.
*/
#define CY_SCB_I2C_INTR_WAKEUP     SCB_INTR_I2C_EC_WAKE_UP_Msk
/** \} group_scb_common_macros_i2c_intr */

/**
* \defgroup group_scb_common_macros_SpiIntrStatuses SPI Interrupt Statuses
* \{
*/
/**
* Wake up request: the SPI slave detects an active edge of the slave select
* signal. Note that this interrupt source triggers in active mode.
*/
#define CY_SCB_SPI_INTR_WAKEUP     SCB_INTR_SPI_EC_WAKE_UP_Msk
/** \} group_scb_common_macros_SpiIntrStatuses */


/*******************************************************************************
*                           Internal Constants
*******************************************************************************/

/** \cond INTERNAL */

/* Default registers values */
#define CY_SCB_CTRL_DEF_VAL         (_VAL2FLD(SCB_CTRL_OVS, 15UL) | \
                                     _VAL2FLD(SCB_CTRL_MODE, 3UL))

#define CY_SCB_I2C_CTRL_DEF_VAL     (_VAL2FLD(SCB_I2C_CTRL_HIGH_PHASE_OVS, 8UL)        | \
                                     _VAL2FLD(SCB_I2C_CTRL_HIGH_PHASE_OVS, 8UL)        | \
                                     _VAL2FLD(SCB_I2C_CTRL_M_READY_DATA_ACK, 1UL)      | \
                                     _VAL2FLD(SCB_I2C_CTRL_M_NOT_READY_DATA_NACK, 1UL) | \
                                     _VAL2FLD(SCB_I2C_CTRL_S_GENERAL_IGNORE, 1UL)      | \
                                     _VAL2FLD(SCB_I2C_CTRL_S_READY_ADDR_ACK, 1UL)      | \
                                     _VAL2FLD(SCB_I2C_CTRL_S_READY_DATA_ACK, 1UL)      | \
                                     _VAL2FLD(SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK, 1UL) | \
                                     _VAL2FLD(SCB_I2C_CTRL_S_NOT_READY_DATA_NACK, 1UL))

#define CY_SCB_I2C_CFG_DEF_VAL      (_VAL2FLD(SCB_I2C_CFG_SDA_IN_FILT_TRIM, 3UL)   | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_IN_FILT_SEL, 1UL)    | \
                                     _VAL2FLD(SCB_I2C_CFG_SCL_IN_FILT_SEL, 1UL)    | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_OUT_FILT0_TRIM, 2UL) | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_OUT_FILT1_TRIM, 2UL) | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_OUT_FILT2_TRIM, 2UL))

#define CY_SCB_SPI_CTRL_DEF_VAL     _VAL2FLD(SCB_SPI_CTRL_MODE, 3UL)
#define CY_SCB_UART_CTRL_DEF_VAL    _VAL2FLD(SCB_UART_CTRL_MODE, 3UL)

#define CY_SCB_UART_RX_CTRL_DEF_VAL (_VAL2FLD(SCB_UART_RX_CTRL_STOP_BITS, 2UL) | \
                                     _VAL2FLD(SCB_UART_RX_CTRL_BREAK_WIDTH, 10UL))

#define CY_SCB_UART_TX_CTRL_DEF_VAL _VAL2FLD(SCB_UART_TX_CTRL_STOP_BITS, 2UL)

#define CY_SCB_RX_CTRL_DEF_VAL      (_VAL2FLD(SCB_RX_CTRL_DATA_WIDTH, 7UL) | \
                                     _VAL2FLD(SCB_RX_CTRL_MSB_FIRST,  1UL))

#define CY_SCB_TX_CTRL_DEF_VAL      (_VAL2FLD(SCB_TX_CTRL_DATA_WIDTH, 7UL) | \
                                     _VAL2FLD(SCB_TX_CTRL_MSB_FIRST,  1UL))

/* SCB CTRL modes */
#define CY_SCB_CTRL_MODE_I2C   (0UL)
#define CY_SCB_CTRL_MODE_SPI   (1UL)
#define CY_SCB_CTRL_MODE_UART  (2UL)

/* The position and mask to set the I2C mode */
#define CY_SCB_I2C_CTRL_MODE_Pos    SCB_I2C_CTRL_SLAVE_MODE_Pos
#define CY_SCB_I2C_CTRL_MODE_Msk    (SCB_I2C_CTRL_SLAVE_MODE_Msk | \
                                     SCB_I2C_CTRL_MASTER_MODE_Msk)

/* Cypress ID #282226:
* SCB_I2C_CFG_SDA_IN_FILT_TRIM[1]: SCB clock enable (1), clock disable (0).
*/
#define CY_SCB_I2C_CFG_CLK_ENABLE_Msk  (_VAL2FLD(SCB_I2C_CFG_SDA_IN_FILT_TRIM, 2UL))

/* I2C has fixed data width */
#define CY_SCB_I2C_DATA_WIDTH   (7UL)

/* RX and TX control register values */
#define CY_SCB_I2C_RX_CTRL      (_VAL2FLD(SCB_RX_CTRL_DATA_WIDTH, CY_SCB_I2C_DATA_WIDTH) | \
                                 SCB_RX_CTRL_MSB_FIRST_Msk)
#if((CY_IP_MXSCB_VERSION<=2) && (!defined (CY_IP_MXS22SCB)))
#define CY_SCB_I2C_TX_CTRL      (_VAL2FLD(SCB_TX_CTRL_DATA_WIDTH, CY_SCB_I2C_DATA_WIDTH) | \
                                 SCB_TX_CTRL_MSB_FIRST_Msk | SCB_TX_CTRL_OPEN_DRAIN_Msk)
#else
#define CY_SCB_I2C_TX_CTRL      (_VAL2FLD(SCB_TX_CTRL_DATA_WIDTH, CY_SCB_I2C_DATA_WIDTH) | \
                                 SCB_TX_CTRL_MSB_FIRST_Msk | SCB_TX_CTRL_OPEN_DRAIN_Msk | \
                                 SCB_TX_CTRL_OPEN_DRAIN_SCL_Msk)
#endif
/* The position and mask to make an address byte */
#define CY_SCB_I2C_ADDRESS_Pos  (1UL)
#define CY_SCB_I2C_ADDRESS_Msk  (0xFEUL)

/* SPI slave select polarity */
#define CY_SCB_SPI_CTRL_SSEL_POLARITY_Pos   SCB_SPI_CTRL_SSEL_POLARITY0_Pos
#define CY_SCB_SPI_CTRL_SSEL_POLARITY_Msk   (SCB_SPI_CTRL_SSEL_POLARITY0_Msk | \
                                             SCB_SPI_CTRL_SSEL_POLARITY1_Msk | \
                                             SCB_SPI_CTRL_SSEL_POLARITY2_Msk | \
                                             SCB_SPI_CTRL_SSEL_POLARITY3_Msk)

#if((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
/* SPI parity and parity enable combination */
#define CY_SCB_SPI_RX_CTRL_SET_PARITY_Msk      (SCB_SPI_RX_CTRL_PARITY_ENABLED_Msk | \
                                                 SCB_SPI_RX_CTRL_PARITY_Msk)
#define CY_SCB_SPI_RX_CTRL_SET_PARITY_Pos      SCB_SPI_RX_CTRL_PARITY_Pos

#define CY_SCB_SPI_TX_CTRL_SET_PARITY_Msk      (SCB_SPI_TX_CTRL_PARITY_ENABLED_Msk | \
                                                 SCB_SPI_TX_CTRL_PARITY_Msk)
#define CY_SCB_SPI_TX_CTRL_SET_PARITY_Pos      SCB_SPI_TX_CTRL_PARITY_Pos
#endif /* CY_IP_MXSCB_VERSION */

/* SPI clock modes: CPHA and CPOL */
#define CY_SCB_SPI_CTRL_CLK_MODE_Pos    SCB_SPI_CTRL_CPHA_Pos
#define CY_SCB_SPI_CTRL_CLK_MODE_Msk    (SCB_SPI_CTRL_CPHA_Msk | SCB_SPI_CTRL_CPOL_Msk)

/* UART parity and parity enable combination */
#define CY_SCB_UART_RX_CTRL_SET_PARITY_Msk      (SCB_UART_RX_CTRL_PARITY_ENABLED_Msk | \
                                                 SCB_UART_RX_CTRL_PARITY_Msk)
#define CY_SCB_UART_RX_CTRL_SET_PARITY_Pos      SCB_UART_RX_CTRL_PARITY_Pos

#define CY_SCB_UART_TX_CTRL_SET_PARITY_Msk      (SCB_UART_TX_CTRL_PARITY_ENABLED_Msk | \
                                                 SCB_UART_TX_CTRL_PARITY_Msk)
#define CY_SCB_UART_TX_CTRL_SET_PARITY_Pos      SCB_UART_TX_CTRL_PARITY_Pos

/* Max number of bits for byte mode */
#define CY_SCB_BYTE_WIDTH   (8UL)

#if((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
/* Max number of bits for HALF WORD mode */
#define CY_SCB_HALF_WORD_WIDTH   (16UL)

/* Max number of bits for WORD mode */
#define CY_SCB_WORD_WIDTH   (32UL)

/*SCB Mem width modes */
#define CY_SCB_MEM_WIDTH_BYTE   (0UL)
#define CY_SCB_MEM_WIDTH_HALFWORD   (1UL)
#define CY_SCB_MEM_WIDTH_WORD   (2UL)
#endif /* ((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) */

/* Single unit to wait */
#define CY_SCB_WAIT_1_UNIT  (1U)

/* Clear interrupt sources */
#define CY_SCB_CLEAR_ALL_INTR_SRC   (0UL)

/* Hardware FIFO size: EZ_DATA_NR / 4 = (512 / 4) = 128 */
#define CY_SCB_FIFO_SIZE            (128UL)

/* Provides a list of allowed sources */
#define CY_SCB_TX_INTR_MASK     (CY_SCB_TX_INTR_LEVEL     | CY_SCB_TX_INTR_NOT_FULL  | CY_SCB_TX_INTR_EMPTY     | \
                                 CY_SCB_TX_INTR_OVERFLOW  | CY_SCB_TX_INTR_UNDERFLOW | CY_SCB_TX_INTR_UART_DONE | \
                                 CY_SCB_TX_INTR_UART_NACK | CY_SCB_TX_INTR_UART_ARB_LOST)

#define CY_SCB_RX_INTR_MASK     (CY_SCB_RX_INTR_LEVEL             | CY_SCB_RX_INTR_NOT_EMPTY | CY_SCB_RX_INTR_FULL | \
                                 CY_SCB_RX_INTR_OVERFLOW          | CY_SCB_RX_INTR_UNDERFLOW                       | \
                                 CY_SCB_RX_INTR_UART_FRAME_ERROR  | CY_SCB_RX_INTR_UART_PARITY_ERROR               | \
                                 CY_SCB_RX_INTR_UART_BREAK_DETECT)


#define CY_SCB_SLAVE_INTR_MASK  (CY_SCB_SLAVE_INTR_I2C_ARB_LOST   | CY_SCB_SLAVE_INTR_I2C_NACK | CY_SCB_SLAVE_INTR_I2C_ACK   | \
                                 CY_SCB_SLAVE_INTR_I2C_WRITE_STOP | CY_SCB_SLAVE_INTR_I2C_STOP | CY_SCB_SLAVE_INTR_I2C_START | \
                                 CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH | CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR                       | \
                                 CY_SCB_SLAVE_INTR_I2C_BUS_ERROR  | CY_SCB_SLAVE_INTR_SPI_BUS_ERROR)

#define CY_SCB_MASTER_INTR_MASK (CY_SCB_MASTER_INTR_I2C_ARB_LOST  | CY_SCB_MASTER_INTR_I2C_NACK | \
                                 CY_SCB_MASTER_INTR_I2C_ACK       | CY_SCB_MASTER_INTR_I2C_STOP | \
                                 CY_SCB_MASTER_INTR_I2C_BUS_ERROR | CY_SCB_MASTER_INTR_SPI_DONE)

#define CY_SCB_I2C_INTR_MASK    CY_SCB_I2C_INTR_WAKEUP

#define CY_SCB_SPI_INTR_MASK    CY_SCB_SPI_INTR_WAKEUP

#if((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
#define CY_SCB_IS_MEMWIDTH_VALID(memwidth)          ((memwidth) <= CY_SCB_MEM_WIDTH_WORD)
#endif /* CY_IP_MXSCB_VERSION */

#define CY_SCB_IS_INTR_VALID(intr, mask)            ( 0UL == ((intr) & ((uint32_t) ~(mask))) )
#define CY_SCB_IS_TRIGGER_LEVEL_VALID(base, level)  ((level) < Cy_SCB_GetFifoSize(base))

#define CY_SCB_IS_I2C_ADDR_VALID(addr)              ( (0U == ((addr) & 0x80U)) )
#define CY_SCB_IS_BUFFER_VALID(buffer, size)        ( (NULL != (buffer)) && ((size) > 0UL) )
#define CY_SCB_IS_I2C_BUFFER_VALID(buffer, size)    ( (0UL == (size)) ? true : (NULL != (buffer)) )
/** \endcond */

/** \} group_scb_common_macros */


/*******************************************************************************
*                       In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_scb_common_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SCB_ReadRxFifo
****************************************************************************//**
*
* Reads a data element directly out of the RX FIFO.
* This function does not check whether the RX FIFO has data before reading it.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Data from RX FIFO.
*
*******************************************************************************/
__STATIC_FORCEINLINE uint32_t Cy_SCB_ReadRxFifo(CySCB_Type const *base)
{
    return (SCB_RX_FIFO_RD(base));
}

/*******************************************************************************
* Function Name: Cy_SCB_SetRxFifoLevel
****************************************************************************//**
*
* Sets the RX FIFO level. When there are more data elements in the RX FIFO than
* this level, the RX FIFO level interrupt is triggered.
*
* \param base
* The pointer to the SCB instance.
*
* \param level
* When there are more data elements in the FIFO than this level, the RX level
* interrupt is triggered.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetRxFifoLevel(CySCB_Type *base, uint32_t level)
{
    CY_ASSERT_L2(CY_SCB_IS_TRIGGER_LEVEL_VALID(base, level));

    CY_REG32_CLR_SET(SCB_RX_FIFO_CTRL(base), SCB_RX_FIFO_CTRL_TRIGGER_LEVEL, level);
}


/*******************************************************************************
* Function Name: Cy_SCB_GetNumInRxFifo
****************************************************************************//**
*
* Returns the number of data elements currently in the RX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The number or data elements in RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetNumInRxFifo(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_RX_FIFO_STATUS_USED, SCB_RX_FIFO_STATUS(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetRxSrValid
****************************************************************************//**
*
* Returns the status of the RX FIFO Shift Register valid bit.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* 1 - RX shift register valid; 0 - RX shift register not valid.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetRxSrValid(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_RX_FIFO_STATUS_SR_VALID, SCB_RX_FIFO_STATUS(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearRxFifo
****************************************************************************//**
*
* Clears the RX FIFO and shifter.
*
* \param base
* The pointer to the SCB instance.
*
* \note
* If there is partial data in the shifter, it is cleared and lost.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearRxFifo(CySCB_Type* base)
{
    SCB_RX_FIFO_CTRL(base) |= (uint32_t)  SCB_RX_FIFO_CTRL_CLEAR_Msk;
    SCB_RX_FIFO_CTRL(base) &= (uint32_t) ~SCB_RX_FIFO_CTRL_CLEAR_Msk;

    (void) SCB_RX_FIFO_CTRL(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_WriteTxFifo
****************************************************************************//**
*
* Writes data directly into the TX FIFO.
* This function does not check whether the TX FIFO is not full before writing
* into it.
*
* \param base
* The pointer to the SCB instance.
*
* \param data
* Data to write to the TX FIFO.
*
*******************************************************************************/
__STATIC_FORCEINLINE void Cy_SCB_WriteTxFifo(CySCB_Type* base, uint32_t data)
{
    SCB_TX_FIFO_WR(base) = data;
}


/*******************************************************************************
* Function Name: Cy_SCB_SetTxFifoLevel
****************************************************************************//**
*
* Sets the TX FIFO level. When there are fewer data elements in the TX FIFO than
* this level, the TX FIFO level interrupt is triggered.
*
* \param base
* The pointer to the SCB instance.
*
* \param level
* When there are fewer data elements in the FIFO than this level, the TX level
* interrupt is triggered.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetTxFifoLevel(CySCB_Type *base, uint32_t level)
{
    CY_ASSERT_L2(CY_SCB_IS_TRIGGER_LEVEL_VALID(base, level));

    CY_REG32_CLR_SET(SCB_TX_FIFO_CTRL(base), SCB_TX_FIFO_CTRL_TRIGGER_LEVEL, level);
}


/*******************************************************************************
* Function Name: Cy_SCB_GetNumInTxFifo
****************************************************************************//**
*
* Returns the number of data elements currently in the TX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The number or data elements in the TX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetNumInTxFifo(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_TX_FIFO_STATUS_USED, SCB_TX_FIFO_STATUS(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetTxSrValid
****************************************************************************//**
*
* Returns the status of the TX FIFO Shift Register valid bit.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* 1 - TX shift register valid; 0 - TX shift register not valid.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetTxSrValid(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_TX_FIFO_STATUS_SR_VALID, SCB_TX_FIFO_STATUS(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_IsTxComplete
****************************************************************************//**
*
* Checks whether the TX FIFO and Shifter are empty and there is no more data to send.
*
* \param base
* Pointer to SPI the SCB instance.
*
* \return
* If true, transmission complete. If false, transmission is not complete.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_IsTxComplete(CySCB_Type const *base)
{
     return (0UL == (Cy_SCB_GetNumInTxFifo(base) + Cy_SCB_GetTxSrValid(base)));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearTxFifo
****************************************************************************//**
*
* Clears the TX FIFO.
*
* \param base
* The pointer to the SCB instance.
*
* \note
* The TX FIFO clear operation also clears the shift register. Thus the shifter
* could be cleared in the middle of a data element transfer. Thia results in
* "ones" being sent on the bus for the remainder of the transfer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearTxFifo(CySCB_Type *base)
{
    SCB_TX_FIFO_CTRL(base) |= (uint32_t)  SCB_TX_FIFO_CTRL_CLEAR_Msk;
    SCB_TX_FIFO_CTRL(base) &= (uint32_t) ~SCB_TX_FIFO_CTRL_CLEAR_Msk;

    (void) SCB_TX_FIFO_CTRL(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetByteMode
****************************************************************************//**
*
* Sets whether the RX and TX FIFOs are in byte mode.
* The FIFOs are either 16-bit wide or 8-bit wide (byte mode).
* When the FIFO is in byte mode it is twice as deep. See the device datasheet
* for FIFO depths.
*
* \param base
* The pointer to the SCB instance.
*
* \param byteMode
* If true, TX and RX FIFOs are 8-bit wide. If false, the FIFOs are 16-bit wide.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetByteMode(CySCB_Type *base, bool byteMode)
{
#if((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
    SCB_CTRL(base) &= ~SCB_CTRL_MEM_WIDTH_Msk;
    if (byteMode)
    {
        SCB_CTRL(base) |=  _VAL2FLD(SCB_CTRL_MEM_WIDTH, CY_SCB_MEM_WIDTH_BYTE);
    }
    else
    {
        SCB_CTRL(base) |=  _VAL2FLD(SCB_CTRL_MEM_WIDTH, CY_SCB_MEM_WIDTH_HALFWORD);
    }
#elif(CY_IP_MXSCB_VERSION==1)
    if (byteMode)
    {
        SCB_CTRL(base) |=  SCB_CTRL_BYTE_MODE_Msk;
    }
    else
    {
        SCB_CTRL(base) &= ~SCB_CTRL_BYTE_MODE_Msk;
    }
#endif /* ((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) */
}

#if(((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) || defined (CY_DOXYGEN))
/*******************************************************************************
* Function Name: Cy_SCB_SetMemWidth
****************************************************************************//**
*
* Sets the RX and TX FIFOs byte mode/halfword/word mode.
* The FIFOs are either 8-bit(byte),16-bit(halfword) or 32-bit (word) wide.
* See the device datasheet for FIFO depths.
*
* \param base
* The pointer to the SCB instance.
*
* \param MemWidthMode
* If 0x0, TX and RX FIFOs are 8-bit wide.
* If 0x1, the FIFOs are 16-bit wide.
* If 0x2, the FIFOs are 32-bit wide.
*
* \note
* This API is available for CAT1B and CAT1C devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetMemWidth(CySCB_Type *base, uint32_t MemWidthMode)
{
        CY_ASSERT_L2(CY_SCB_IS_MEMWIDTH_VALID(MemWidthMode));

        SCB_CTRL(base) &= ~SCB_CTRL_MEM_WIDTH_Msk;

        SCB_CTRL(base) |=  _VAL2FLD(SCB_CTRL_MEM_WIDTH, MemWidthMode);
}
#endif /* CY_IP_MXSCB_VERSION */

/*******************************************************************************
* Function Name: Cy_SCB_GetInterruptCause
****************************************************************************//**
*
* Returns the mask of bits showing the source of the current triggered
* interrupt. This is useful for modes of operation where an interrupt can
* be generated by conditions in multiple interrupt source registers.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The mask with the OR of the following conditions that have been triggered.
* See \ref group_scb_common_macros_intr_cause for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetInterruptCause(CySCB_Type const *base)
{
    return (SCB_INTR_CAUSE(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetRxInterruptStatus
****************************************************************************//**
*
* Returns the RX interrupt request register. This register contains the current
* status of the RX interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the RX interrupt sources. Each constant is a bit field
* value. The value returned may have multiple bits set to indicate the
* current status.
* See \ref group_scb_common_macros_rx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetRxInterruptStatus(CySCB_Type const *base)
{
    return (SCB_INTR_RX(base) & CY_SCB_RX_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetRxInterruptMask
****************************************************************************//**
*
* Writes the RX interrupt mask register. This register configures which bits
* from the RX interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Enabled RX interrupt sources.
* See \ref group_scb_common_macros_rx_intr.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetRxInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_RX_INTR_MASK));

    SCB_INTR_RX_MASK(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetRxInterruptMask
****************************************************************************//**
*
* Returns the RX interrupt mask register. This register specifies which bits
* from the RX interrupt request register trigger can an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Enabled RX interrupt sources.
* See \ref group_scb_common_macros_rx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetRxInterruptMask(CySCB_Type const *base)
{
    return (SCB_INTR_RX_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetRxInterruptStatusMasked
****************************************************************************//**
*
* Returns the RX interrupt masked request register. This register contains
* a logical AND of corresponding bits from the RX interrupt request and
* mask registers.
* This function is intended to be used in the interrupt service routine to
* identify which of the enabled RX interrupt sources caused the interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of enabled RX interrupt sources.
* See \ref group_scb_common_macros_rx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetRxInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_RX_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearRxInterrupt
****************************************************************************//**
*
* Clears the RX interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The RX interrupt sources to be cleared.
* See \ref group_scb_common_macros_rx_intr for the set of constants.
*
* \note
*  - CY_SCB_INTR_RX_FIFO_LEVEL interrupt source is not cleared when
*    the RX FIFO has more entries than the level.
*  - CY_SCB_INTR_RX_NOT_EMPTY interrupt source is not cleared when the
*    RX FIFO is not empty.
*  - CY_SCB_INTR_RX_FULL interrupt source is not cleared when the
*    RX FIFO is full.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearRxInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_RX_INTR_MASK));

    SCB_INTR_RX(base) = interruptMask;
    (void) SCB_INTR_RX(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetRxInterrupt
****************************************************************************//**
*
* Sets the RX interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The RX interrupt sources to set in the RX interrupt request register.
* See \ref group_scb_common_macros_rx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetRxInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_RX_INTR_MASK));

    SCB_INTR_RX_SET(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetTxInterruptStatus
****************************************************************************//**
*
* Returns the TX interrupt request register. This register contains the current
* status of the TX interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of TX interrupt sources.
* Each constant is a bit field value. The value returned may have multiple
* bits set to indicate the current status.
* See \ref group_scb_common_macros_tx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetTxInterruptStatus(CySCB_Type const *base)
{
    return (SCB_INTR_TX(base) & CY_SCB_TX_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetTxInterruptMask
****************************************************************************//**
*
* Writes the TX interrupt mask register. This register configures which bits
* from the TX interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Enabled TX interrupt sources.
* See \ref group_scb_common_macros_tx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetTxInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_TX_INTR_MASK));

    SCB_INTR_TX_MASK(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetTxInterruptMask
****************************************************************************//**
*
* Returns the TX interrupt mask register. This register specifies which
* bits from the TX interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Enabled TX interrupt sources.
* See \ref group_scb_common_macros_tx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetTxInterruptMask(CySCB_Type const *base)
{
    return (SCB_INTR_TX_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetTxInterruptStatusMasked
****************************************************************************//**
*
* Returns the TX interrupt masked request register. This register contains
* a logical AND of corresponding bits from the TX interrupt request and
* mask registers.
* This function is intended to be used in the interrupt service routine to
* identify which of enabled TX interrupt sources caused the interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of enabled TX interrupt sources.
* See \ref group_scb_common_macros_tx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetTxInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_TX_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearTxInterrupt
****************************************************************************//**
*
* Clears the TX interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The TX interrupt sources to be cleared.
* See \ref group_scb_common_macros_tx_intr for the set of constants.
*
* \note
*  - CY_SCB_INTR_TX_FIFO_LEVEL interrupt source is not cleared when the
*    TX FIFO has fewer entries than the TX level.
*  - CY_SCB_INTR_TX_NOT_FULL interrupt source is not cleared when the
*    TX FIFO has empty entries in the TX FIFO.
*  - CY_SCB_INTR_TX_EMPTY interrupt source is not cleared when the
*    TX FIFO is empty.
*  - CY_SCB_INTR_TX_UNDERFLOW interrupt source is not cleared when the
*    TX FIFO is empty. Put data into the TX FIFO before clearing it.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearTxInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_TX_INTR_MASK));

    SCB_INTR_TX(base) = interruptMask;
    (void) SCB_INTR_TX(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetTxInterrupt
****************************************************************************//**
*
* Sets TX interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The TX interrupt sources to set in the TX interrupt request register.
* See \ref group_scb_common_macros_tx_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetTxInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_TX_INTR_MASK));

    SCB_INTR_TX_SET(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetMasterInterruptStatus
****************************************************************************//**
*
* Returns the master interrupt request register. This register contains the current
* status of the master interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the master interrupt sources.
* Each constant is a bit field value. The value returned may have multiple
* bits set to indicate the current status.
* See \ref group_scb_common_macros_master_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetMasterInterruptStatus(CySCB_Type const *base)
{
    return (SCB_INTR_M(base) & CY_SCB_MASTER_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetMasterInterruptMask
****************************************************************************//**
*
* Writes the master interrupt mask register. This register specifies which bits
* from the master interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The master interrupt sources to be enable.
* See \ref group_scb_common_macros_master_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetMasterInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_MASTER_INTR_MASK));

    SCB_INTR_M_MASK(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetMasterInterruptMask
****************************************************************************//**
*
* Returns the master interrupt mask register. This register specifies which bits
* from the master interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Enabled master interrupt sources.
* See \ref group_scb_common_macros_master_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetMasterInterruptMask(CySCB_Type const *base)
{
    return (SCB_INTR_M_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetMasterInterruptStatusMasked
****************************************************************************//**
*
* Returns the master interrupt masked request register. This register contains a
* logical AND of corresponding bits from the master interrupt request and mask
* registers.
* This function is intended to be used in the interrupt service routine to
* identify which of the enabled master interrupt sources caused the interrupt
* event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of enabled master interrupt sources.
* See \ref group_scb_common_macros_master_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetMasterInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_M_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearMasterInterrupt
****************************************************************************//**
*
* Clears master interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The master interrupt sources to be cleared.
* See \ref group_scb_common_macros_master_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearMasterInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_MASTER_INTR_MASK));

    SCB_INTR_M(base) = interruptMask;
    (void) SCB_INTR_M(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetMasterInterrupt
****************************************************************************//**
*
* Sets master interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The master interrupt sources to set in the master interrupt request register.
* See \ref group_scb_common_macros_master_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetMasterInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_MASTER_INTR_MASK));

    SCB_INTR_M_SET(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSlaveInterruptStatus
****************************************************************************//**
*
* Returns the slave interrupt request register. This register contains the current
* status of the slave interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the slave interrupt sources.
* Each constant is a bit field value. The value returned may have multiple
* bits set to indicate the current status.
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetSlaveInterruptStatus(CySCB_Type const *base)
{
    return (SCB_INTR_S(base) & CY_SCB_SLAVE_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetSlaveInterruptMask
****************************************************************************//**
*
* Writes slave interrupt mask register.
* This register specifies which bits from the slave interrupt request register
* can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Enabled slave interrupt sources.
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetSlaveInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_SLAVE_INTR_MASK));

    SCB_INTR_S_MASK(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSlaveInterruptMask
****************************************************************************//**
*
* Returns the slave interrupt mask register.
* This register specifies which bits from the slave interrupt request register
* can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Enabled slave interrupt sources.
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetSlaveInterruptMask(CySCB_Type const *base)
{
    return (SCB_INTR_S_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSlaveInterruptStatusMasked
****************************************************************************//**
*
* Returns the slave interrupt masked request register. This register contains a
* logical AND of corresponding bits from the slave interrupt request and mask
* registers.
* This function is intended to be used in the interrupt service routine to
* identify which of enabled slave interrupt sources caused the interrupt
* event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of enabled slave interrupt sources.
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetSlaveInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_S_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearSlaveInterrupt
****************************************************************************//**
*
* Clears the slave interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Slave interrupt sources to be cleared.
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearSlaveInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_SLAVE_INTR_MASK));

    SCB_INTR_S(base) = interruptMask;
    (void) SCB_INTR_S(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetSlaveInterrupt
****************************************************************************//**
*
* Sets slave interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The slave interrupt sources to set in the slave interrupt request register
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetSlaveInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_SLAVE_INTR_MASK));

    SCB_INTR_S_SET(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetI2CInterruptStatus
****************************************************************************//**
*
* Returns the I2C interrupt request register. This register contains the
* current status of the I2C interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of the I2C interrupt sources. Each constant is a bit
* field value.
* The value returned may have multiple bits set to indicate the current status.
* See \ref group_scb_common_macros_slave_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetI2CInterruptStatus(CySCB_Type const *base)
{
    return (SCB_INTR_I2C_EC(base) & CY_SCB_I2C_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetI2CInterruptMask
****************************************************************************//**
*
* Writes the I2C interrupt mask register. This register specifies which bits
* from the I2C interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Enabled I2C interrupt sources.
* See \ref group_scb_common_macros_i2c_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetI2CInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_I2C_INTR_MASK));

    SCB_INTR_I2C_EC_MASK(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetI2CInterruptMask
****************************************************************************//**
*
* Returns the I2C interrupt mask register. This register specifies which bits
* from the I2C interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Enabled I2C interrupt sources.
* See \ref group_scb_common_macros_i2c_intr.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetI2CInterruptMask(CySCB_Type const *base)
{
    return (SCB_INTR_I2C_EC_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetI2CInterruptStatusMasked
****************************************************************************//**
*
* Returns the I2C interrupt masked request register. This register contains
* a logical AND of corresponding bits from I2C interrupt request and mask
* registers.
* This function is intended to be used in the interrupt service routine to
* identify which of enabled I2C interrupt sources caused the interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of enabled I2C interrupt sources.
* See \ref group_scb_common_macros_i2c_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetI2CInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_I2C_EC_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearI2CInterrupt
****************************************************************************//**
*
* Clears I2C interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The I2C interrupt sources to be cleared.
* See \ref group_scb_common_macros_i2c_intr for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearI2CInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_I2C_INTR_MASK));

    SCB_INTR_I2C_EC(base) = interruptMask;
    (void) SCB_INTR_I2C_EC(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSpiInterruptStatus
****************************************************************************//**
*
* Returns the SPI interrupt request register. This register contains the current
* status of the SPI interrupt sources.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of SPI interrupt sources. Each constant is a bit field value.
* The value returned may have multiple bits set to indicate the current status
* See \ref group_scb_common_macros_SpiIntrStatuses for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetSpiInterruptStatus(CySCB_Type const *base)
{
    return (SCB_INTR_SPI_EC(base) & CY_SCB_SPI_INTR_MASK);
}


/*******************************************************************************
* Function Name: Cy_SCB_SetSpiInterruptMask
****************************************************************************//**
*
* Writes the SPI interrupt mask register. This register specifies which
* bits from the SPI interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* Enabled SPI interrupt sources.
* See \ref group_scb_common_macros_SpiIntrStatuses for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SetSpiInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_SPI_INTR_MASK));

    SCB_INTR_SPI_EC_MASK(base) = interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSpiInterruptMask
****************************************************************************//**
*
* Returns the SPI interrupt mask register. This register specifies which bits
* from the SPI interrupt request register can trigger an interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* Enabled SPI interrupt sources.
* See \ref group_scb_common_macros_SpiIntrStatuses for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetSpiInterruptMask(CySCB_Type const *base)
{
    return (SCB_INTR_SPI_EC_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_GetSpiInterruptStatusMasked
****************************************************************************//**
*
* Returns the SPI interrupt masked request register. This register contains
* a logical AND of corresponding bits from the SPI interrupt request and
* mask registers.
* This function is intended to be used in the interrupt service routine to
* identify which of enabled SPI interrupt sources caused the interrupt event.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The current status of enabled SPI interrupt sources.
* See \ref group_scb_common_macros_SpiIntrStatuses for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetSpiInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_SPI_EC_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SCB_ClearSpiInterrupt
****************************************************************************//**
*
* Clears SPI interrupt sources in the interrupt request register.
*
* \param base
* The pointer to the SCB instance.
*
* \param interruptMask
* The SPI interrupt sources to be cleared.
* See \ref group_scb_common_macros_SpiIntrStatuses for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_ClearSpiInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    CY_ASSERT_L2(CY_SCB_IS_INTR_VALID(interruptMask, CY_SCB_SPI_INTR_MASK));

    SCB_INTR_SPI_EC(base) = interruptMask;
    (void) SCB_INTR_SPI_EC(base);
}

/** \cond INTERNAL */
/*******************************************************************************
* Function Name: Cy_SCB_GetFifoSize
****************************************************************************//**
*
* Returns the RX and TX FIFO depth.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* FIFO depth.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetFifoSize(CySCB_Type const *base)
{
#if((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB))
    {return (((uint32_t)(CY_SCB_FIFO_SIZE)) >> _FLD2VAL(SCB_CTRL_MEM_WIDTH, SCB_CTRL(base)));}
#elif(CY_IP_MXSCB_VERSION==1)
    {return (_FLD2BOOL(SCB_CTRL_BYTE_MODE, SCB_CTRL(base)) ? (CY_SCB_FIFO_SIZE) : (CY_SCB_FIFO_SIZE / 2UL));}
#else
    return 0;
#endif /* ((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) */

}


/*******************************************************************************
* Function Name: Cy_SCB_IsRxDataWidthByte
****************************************************************************//**
*
* Returns true if the RX data width is a byte (8 bits).
*
* \param base
* The pointer to the SCB instance.
*
* \return
* True if the RX data width is a byte (8 bits).
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_IsRxDataWidthByte(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_RX_CTRL_DATA_WIDTH, SCB_RX_CTRL(base)) < CY_SCB_BYTE_WIDTH);
}

/** \endcond */

#if(((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) || defined (CY_DOXYGEN))
/*******************************************************************************
* Function Name: Cy_SCB_Get_RxDataWidth
****************************************************************************//**
*
* Returns the RX data width.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* RX data width.
*
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_Get_RxDataWidth(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_RX_CTRL_DATA_WIDTH, SCB_RX_CTRL(base)) + 1UL);
}
#endif /* CY_IP_MXSCB_VERSION */

/*******************************************************************************
* Function Name: Cy_SCB_IsTxDataWidthByte
****************************************************************************//**
*
* Returns true if the TX data width is a byte (8 bits).
*
* \param base
* The pointer to the SCB instance.
*
* \return
* If true, the TX data width is a byte (8 bits). Otherwise, false.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_IsTxDataWidthByte(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_TX_CTRL_DATA_WIDTH, SCB_TX_CTRL(base)) < CY_SCB_BYTE_WIDTH);
}

#if(((CY_IP_MXSCB_VERSION>=2) || defined (CY_IP_MXS22SCB)) || defined (CY_DOXYGEN))
/*******************************************************************************
* Function Name: Cy_SCB_Get_TxDataWidth
****************************************************************************//**
*
* Returns the TX data width.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* The TX data width.
*
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_Get_TxDataWidth(CySCB_Type const *base)
{
        return (_FLD2VAL(SCB_TX_CTRL_DATA_WIDTH, SCB_TX_CTRL(base)) + 1UL);
}
#endif /* CY_IP_MXSCB_VERSION */

/** \cond INTERNAL */

/*******************************************************************************
* Function Name: Cy_SCB_FwBlockReset
****************************************************************************//**
*
* Disables and enables the block to return it into the known state (default):
* FIFOs and interrupt statuses are cleared.
*
* \param base
* The pointer to the SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_FwBlockReset(CySCB_Type *base)
{
    SCB_CTRL(base) &= (uint32_t) ~SCB_CTRL_ENABLED_Msk;

    /* Clean-up command registers */
    SCB_I2C_M_CMD(base) = 0UL;
    SCB_I2C_S_CMD(base) = 0UL;

    SCB_CTRL(base) |= (uint32_t)  SCB_CTRL_ENABLED_Msk;

    (void) SCB_CTRL(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_GetRxFifoLevel
****************************************************************************//**
*
* Returns the RX FIFO level when there are more words in the RX FIFO than the
* level, the RX FIFO level interrupt is triggered.
*
* \param base
* The pointer to the SCB instance.
*
* \return
* RX FIFO level.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_GetRxFifoLevel(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_RX_FIFO_CTRL_TRIGGER_LEVEL, SCB_RX_FIFO_CTRL(base));
}

/** \endcond */
/** \} group_scb_common_functions */

#if defined(__cplusplus)
}
#endif

/** \} group_scb_common */

#endif /* (defined (CY_IP_MXSCB) || defined (CY_IP_MXS22SCB)) */

#endif /* (CY_SCB_COMMON_H) */

/* [] END OF FILE */
