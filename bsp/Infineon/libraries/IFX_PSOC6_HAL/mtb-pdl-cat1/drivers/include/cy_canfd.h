/***************************************************************************//**
* \file cy_canfd.h
* \version 1.30
*
*  This file provides constants and parameter values for
*  the CAN FD driver.
*
********************************************************************************
* \copyright
* Copyright 2019-2020 Cypress Semiconductor Corporation
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
* \addtogroup group_canfd
* \{
* The CAN FD driver provides an easy method to access the CAN FD IP block registers
* and provides simple functionality for sending and receiving data between
* devices in the CAN FD network.
* The CAN FD driver provides an API to configure the main features - mode, bit time,
* message buffers - and transmit and receive message in all modes:
* - Classic CAN using 11-bit identifiers
* - Classic CAN using 29-bit identifiers
* - CAN Flexible Data using 11-bit identifiers
* - CAN Flexible Data using 29-bit identifiers.
*
* \image html canfd_solution.png "CAN FD Solution" width=948px
* \image latex canfd_solution.png
*
*
* \section group_canfd_section_configuration Configuration Considerations
* Specification of the sample code is as follows:
*   - Selectable CAN FD mode or CAN mode
*   - Configurable CAN clock
*   - Configurable CAN Bit rate
*   - Configurable CAN FD Bit rate
*   - Configurable Standard ID filter
*   - Configurable Extended Message ID Filter
*   - Tx-Rx Element Size : 8 bytes (CAN mode)
*   - Tx-Rx Element Size : 64 bytes (CAN FD mode)
*   - Rx FIFO configuration
*   - Interrupts : \n
*                  CY_CANFD_RX_FIFO_0_NEW_MESSAGE (Message stored to Rx FIFO 0) \n
*                  CY_CANFD_RX_FIFO_1_NEW_MESSAGE (Message stored to Rx FIFO 1) \n
*                  CY_CANFD_RX_BUFFER_NEW_MESSAGE (Message stored to Dedicated Rx Buffer). \n
*
* Sends data of ID:0x200 periodically in the main().
* Echobacks received data by incrementing the ID of the received packet in
* the receiving interrupt.(CanFDIrqHandler() --- CanFDCallbackRx())
*
* \subsection group_canfd_section_configuration_personalities Use ModusToolbox Device Configurator Tool to generate initialization code
* The steps to generate initialization code using
* the ModusToolbox Device Configurator Tool:
*
* 1. Launch the ModusToolbox Device Configurator Tool.
* 2. Switch to the Peripherals tab. Enable the CAN FD channel personality
*    under Communication and enter Alias (default is canfd_0_chan_0).
* 3. Go to the Parameters Pane for the CAN FD Personality and configure it with
*    the desired parameters (set the Clock Signal divider, set the bit timing
*    configuration, set the other parameters per Configuration Considerations, etc).
* 4. Perform File->Save for the initialization code to generate.
*
* Now, all required CAN FD initialization code and configuration prerequisites will be generated:
*
* - The Peripheral Clock Divider assignment and analog routing are parts of the
*   init_cycfg_all() routine. Place the call of the init_cycfg_all() function
*   before using any CAN FD API functions to ensure initialization of all external
*   resources required for the CAN FD operation.
* - The CAN FD configuration structure declaration is in the cycfg_peripherals.h
*   file and its initialization is in the cycfg_peripherals.c file. The variable
*   name is \<CAN_FD_Alias_Name\>_config (default is canfd_0_chan_0_config). It
*   must be used with Cy_CANFD_Init() function.
* - TX buffers structures are initialized. Use these structures to send data.
*
* For the CAN FD interrupt service routine, Cy_CANFD_IrqHandler() can be used.
* It handles reading data from the dedicated RX buffers and RX FIFO buffers.
* Corresponding callback functions are called for error interrupts, RX
* interrupts and TX complete interrupt. Put the names of callback functions to
* the Callback functions parameters section. Put NULL if no callback function to
* be used.
* \note Only RX interrupt sources are enabled by default.
* Use Cy_CANFD_SetInterruptMask() to enable other interrupt sources.
* \note Interrupt flags are set regardless of the interrupt enable register.
* Cy_CANFD_IrqHandler will check and process all supported interrupts when
* triggered with any enabled interrupt source.
*
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_ISR
*
* Set up the interrupt handler to be called with CAN FD events. The CAN FD block
* has two interrupt lines which can be assigned to different interrupt
* sources using Cy_CANFD_SetInterruptLine(): canfd_0_interrupts0_0_IRQn
* and canfd_0_interrupts1_0_IRQn. Also, the CAN FD block has a consolidated interrupt
* canfd_0_interrupt0_IRQn. The following code shows how to set up the interrupt
* handler.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Setup_CANFD_Interrupt
*
* \subsection group_canfd_section_configuration_manual Implement the initialization code manually
* Call Cy_CANFD_Init() to initialize the CAN FD module.
* It initializes the CAN FD module with the configuration parameters, passed
* in the \ref cy_stc_canfd_config_t structure. It consists of several elements
* to be defined first.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Config_Struct
* The Cy_CANFD_Init() function also initializes the shared context structure
* used later with other API functions.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_context
* Although the callback functions are optional, they are recommended for use,
* otherwise, there is no report to the API about any error and transmission or reception events.
* The example callback function sends received data back to the bus,
* incrementing ID by 1:
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_RX_callback
* CAN FD IP block requires the configuration of a peripheral clock divider.
* The following code configures an 8-bit clock divider. The default peripheral
* clock frequency is 72 MHz. The desired divider value minus one must be passed.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Assign_Clock_Divider
* The CAN FD block uses the Port 5 pins for receive (P5[0]) and transmit (P5[1]).
* - Connect the specified High-Speed Input Output Multiplexer (HSIOM) selection
* to the pin.
* - Set the pins drive mode for RX and TX.
*
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Assign_CANFD_Pins
*
* For the CANFD interrupt service routine, the Cy_CANFD_IrqHandler() can be used.
* It handles reading data from dedicated RX buffers and RX FIFO buffers.
* Corresponding callback functions are called for error interrupts, RX
* interrupts and TX complete interrupt.
* \note Only RX interrupt sources are enabled by default.
* Use Cy_CANFD_SetInterruptMask() to enable other interrupt sources.
* \note Interrupt flags are set regardless of the interrupt enable register.
* Cy_CANFD_IrqHandler will check and process all supported interrupts when
* triggered with any enabled interrupt source.
*
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_ISR
*
* Setup the interrupt handler to be called with the CAN FD events. The CAN FD block
* has two interrupt lines, which can be assigned to different interrupt
* sources using Cy_CANFD_SetInterruptLine(): canfd_0_interrupts0_0_IRQn
* and canfd_0_interrupts1_0_IRQn. Also, the CAN FD block has a consolidated interrupt
* canfd_0_interrupt0_IRQn. The following code shows how to set up the interrupt
* handler.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Setup_CANFD_Interrupt
*
* CAN FD has two bit rate settings, for arbitration and data phases. Both are
* configured with the same structure, containing a pre-scaler, time segment 1,
* time segment 2 and synchronization jump width.
* \note The actual interpretation by the hardware of configured values is
* one more value than programmed.
* \note The bit rate configured for the CAN FD data phase must be higher or equal to
* the bit rate configured for the arbitration phase.
*
* The CAN time quantum (tq) may be programmed in the range of 1 to 32 CAN FD clock
* periods: tq = (prescaler + 1) mtq, where mtq is CAN FD block's clock period.
* The length of the bit time is (programmed values)
* [timeSegment1 + timeSegment2 + 3] tq. \n
* The example below shows the configuration with the 100 kbps arbitration bit rate
* and 200 kbps data bit rate. This assumes the peripheral clock frequency of 72 MHz
* divided by 9 to obtain the 8 MHz clock for the CAN FD block.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Bitrate
* CAN FD driver provides API to setup Message ID filtering. There are standard
* ID and extended ID filters. The desired count of the filters of each type is
* specified in the \ref cy_stc_canfd_config_t structure and is set once during
* block initialization. It is possible to change the configured
* filters settings with Cy_CANFD_SidFilterSetup() and Cy_CANFD_XidFilterSetup().
* Use the cy_stc_id_filter_t structure to set up one standard ID filter:
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_SID_Filter
* Use the cy_stc_extid_filter_t structure to set up an extended ID filter:
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_XID_Filter
* Message IDs that do not match any filter are received according to the global
* filter set up. The global filter can be set up to receive messages with standard
* and extended IDs to different FIFO buffers. It can be configured to reject remote
* frames, as shown below.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Global_Filter
* The RX FIFO buffers, FIFO 0 and FIFO 1 are configured once on block
* initialization using cy_en_canfd_fifo_config_t structure.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_FIFO_Config
* The cy_stc_canfd_config_t structure is used to pass all configuration to
* Cy_CANFD_Init() function. It is populated with pointers to other structures
* required and constants, defined before.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Config_Struct
* The Cy_CANFD_Init() function initializes the CAN FD block by writing CAN FD
* configuration registers. Cy_CANFD_Init() enables the RX interrupts for
* new message reception into the dedicated RX buffers, FIFO 0 and FIFO 1.
* The code example also shows the test mode configuration which can be used to
* enable the Loopback mode. See \ref cy_stc_canfd_test_mode_t for details.
* Cy_CANFD_Init() sets test mode configuration to CY_CANFD_TEST_MODE_DISABLE.
* Remember to disable the echo functionality in the RX callback when using a loopback.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Init_Example
* To send a CAN FD message, a TX buffer structure must be prepared
* which consists of the T0 and T1 registers and data array.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Prepare_TX
* To transmit CAN FD messages, the function \ref Cy_CANFD_UpdateAndTransmitMsgBuffer()
* is used. The buffer status can be retrieved by Cy_CANFD_GetTxBufferStatus().
* It is possible to set a callback function which will be notified whenever a
* message transmission has been completed.
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Send_TX
*
* \section group_canfd_section_more_information More Information
*
* For more information on the CAN FD peripheral, refer to the technical
* reference manual (TRM).
*
* \section group_canfd_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.30</td>
*     <td>Updated \ref Cy_CANFD_Init() and \ref Cy_CANFD_DeInit() functions. Added volatile qualifier to prevent loop optimization.</td>
*     <td>Code Enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.20</td>
*     <td>Added const modifier to the functions parameters where needed.
*         Improved error handling in \ref Cy_CANFD_Init() and
*         \ref Cy_CANFD_IrqHandler().
*     </td>
*     <td>Source code cleanup.</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Updated \ref Cy_CANFD_Init() functions.</td>
*     <td>Allow initing CANFD with 0 number of SID/XID filters.</td>
*   </tr>
*   <tr>
*     <td>1.0.1</td>
*     <td>Updated description of the \ref Cy_CANFD_Init() and \ref Cy_CANFD_DeInit() functions.</td>
*     <td>Documentation update and clarification.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_canfd_macros Macros
* \{
    \defgroup group_canfd_rx_interrupt_masks RX Interrupt masks
    \defgroup group_canfd_tx_interrupt_masks TX Interrupt masks
    \defgroup group_canfd_error_interrupt_masks Error Interrupt masks
    \defgroup group_canfd_interrupt_line_masks Interrupt line selection masks
    \defgroup group_canfd_last_state_masks Protocol Status Register (PSR) masks
* \}
* \defgroup group_canfd_functions Functions
* \defgroup group_canfd_data_structures Data Structures
* \defgroup group_canfd_enums Enumerated Types
*
*/

#if !defined(CY_CANFD_H)
#define CY_CANFD_H

#include "cy_device.h"

#if defined (CY_IP_MXTTCANFD)

#include <stddef.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_canfd_macros
* \{
* This section describes the CAN FD Macros.
* These Macros can be used to check the interrupt and status flags.
* Detailed information about the macros is available in each macro description.
*/

/** Driver major version */
#define CY_CANFD_DRV_VERSION_MAJOR       1U

/** Driver minor version */
#define CY_CANFD_DRV_VERSION_MINOR       30U

/** CAN FD driver ID */
#define CY_CANFD_ID CY_PDL_DRV_ID(0x45U)

/******************************************************************************
* API Constants
******************************************************************************/

/** Size of word data bytes in a receive or transmit operation (16word = 64byte) */
#define CY_CANFD_MESSAGE_DATA_BUFFER_SIZE       (16U)

/** FIFO number 0 */
#define CY_CANFD_RX_FIFO0                       (0U)

/** FIFO number 1 */
#define CY_CANFD_RX_FIFO1                       (1U)

/** \} group_canfd_macros */


/**
* \addtogroup group_canfd_rx_interrupt_masks
* \{ This section contains interrupt bit masks to be used with:
*  - Cy_CANFD_GetInterruptStatus()
*  - Cy_CANFD_ClearInterrupt()
*  - Cy_CANFD_GetInterruptMask()
*  - Cy_CANFD_SetInterruptMask()
*  - Cy_CANFD_GetInterruptLine()
*  - Cy_CANFD_SetInterruptLine()
*/
#define CY_CANFD_RX_FIFO_0_NEW_MESSAGE          (CANFD_CH_M_TTCAN_IR_RF0N_Msk)  /**< Rx FIFO 0 New Message */
#define CY_CANFD_RX_FIFO_1_NEW_MESSAGE          (CANFD_CH_M_TTCAN_IR_RF1N_Msk)  /**< Rx FIFO 1 New Message */
#define CY_CANFD_RX_BUFFER_NEW_MESSAGE          (CANFD_CH_M_TTCAN_IR_DRX_Msk)   /**< Message stored to Dedicated Rx Buffer */
#define CY_CANFD_HIGH_PRIORITY_MESSAGE          (CANFD_CH_M_TTCAN_IR_HPM_Msk)   /**< High Priority Message */

/** \} group_canfd_rx_interrupt_masks */

/**
* \addtogroup group_canfd_tx_interrupt_masks
* \{ This section contains interrupt bit masks to use with:
*  - Cy_CANFD_GetInterruptStatus()
*  - Cy_CANFD_ClearInterrupt()
*  - Cy_CANFD_GetInterruptMask()
*  - Cy_CANFD_SetInterruptMask()
*  - Cy_CANFD_GetInterruptLine()
*  - Cy_CANFD_SetInterruptLine()
*/
#define CY_CANFD_TRANSMISSION_COMPLETE          (CANFD_CH_M_TTCAN_IR_TC_Msk)    /**< Transmission Completed */
#define CY_CANFD_TRANSMISSION_CANCEL_FINISHED   (CANFD_CH_M_TTCAN_IR_TCF_Msk)   /**< Transmission Cancellation Finished */
#define CY_CANFD_TX_FIFO_EMPTY                  (CANFD_CH_M_TTCAN_IR_TFE_Msk)   /**< Tx FIFO Empty */
#define CY_CANFD_TX_EVENT_FIFO_NEW_ENTRY        (CANFD_CH_M_TTCAN_IR_TEFN_Msk)  /**< Tx Event FIFO New Entry */

/** \} group_canfd_tx_interrupt_masks */


/**
* \addtogroup group_canfd_error_interrupt_masks
* \{ This section contains interrupt bit masks to be used with:
*  - Cy_CANFD_GetInterruptStatus()
*  - Cy_CANFD_ClearInterrupt()
*  - Cy_CANFD_GetInterruptMask()
*  - Cy_CANFD_SetInterruptMask()
*  - Cy_CANFD_GetInterruptLine()
*  - Cy_CANFD_SetInterruptLine()
*/
#define CY_CANFD_RX_FIFO_0_WATERMARK_REACHED    (CANFD_CH_M_TTCAN_IR_RF0W_Msk)  /**< Rx FIFO 0 Watermark Reached */
#define CY_CANFD_RX_FIFO_0_FULL                 (CANFD_CH_M_TTCAN_IR_RF0F_Msk)  /**< Rx FIFO 0 Full */
#define CY_CANFD_RX_FIFO_0_MSG_LOST             (CANFD_CH_M_TTCAN_IR_RF0L__Msk) /**< Rx FIFO 0 Message Lost */

#define CY_CANFD_RX_FIFO_1_WATERMARK_REACHED    (CANFD_CH_M_TTCAN_IR_RF1W_Msk)  /**< Rx FIFO 1 Watermark Reached */
#define CY_CANFD_RX_FIFO_1_FULL                 (CANFD_CH_M_TTCAN_IR_RF1F_Msk)  /**< Rx FIFO 1 Full */
#define CY_CANFD_RX_FIFO_1_MSG_LOST             (CANFD_CH_M_TTCAN_IR_RF1L__Msk) /**< Rx FIFO 1 Message Lost */

#define CY_CANFD_TX_FIFO_1_WATERMARK_REACHED    (CANFD_CH_M_TTCAN_IR_TEFW_Msk)  /**< Tx Event FIFO Watermark Reached */
#define CY_CANFD_TX_FIFO_1_FULL                 (CANFD_CH_M_TTCAN_IR_TEFF_Msk)  /**< Tx Event FIFO Full */
#define CY_CANFD_TX_FIFO_1_MSG_LOST             (CANFD_CH_M_TTCAN_IR_TEFL__Msk) /**< Tx Event FIFO Element Lost */

#define CY_CANFD_TIMESTAMP_WRAPAROUND           (CANFD_CH_M_TTCAN_IR_TSW_Msk)   /**< Timestamp Wraparound */
#define CY_CANFD_MRAM_ACCESS_FAILURE            (CANFD_CH_M_TTCAN_IR_MRAF_Msk)  /**< Message RAM Access Failure */
#define CY_CANFD_TIMEOUT_OCCURRED               (CANFD_CH_M_TTCAN_IR_TOO_Msk)   /**< Timeout Occurred */


#define CY_CANFD_BIT_ERROR_CORRECTED            (CANFD_CH_M_TTCAN_IR_BEC_Msk)   /**< Bit Error Corrected */
#define CY_CANFD_BIT_ERROR_UNCORRECTED          (CANFD_CH_M_TTCAN_IR_BEU_Msk)   /**< Bit Error Uncorrected */
#define CY_CANFD_ERROR_LOG_OVERFLOW             (CANFD_CH_M_TTCAN_IR_ELO_Msk)   /**< Error Logging Overflow */
#define CY_CANFD_ERROR_PASSIVE                  (CANFD_CH_M_TTCAN_IR_EP__Msk)   /**< Error Passive */
#define CY_CANFD_WARNING_STATUS                 (CANFD_CH_M_TTCAN_IR_EW__Msk)   /**< Warning Status */
#define CY_CANFD_BUS_OFF_STATUS                 (CANFD_CH_M_TTCAN_IR_BO__Msk)   /**< Bus_Off Status */
#define CY_CANFD_WATCHDOG_INTERRUPT             (CANFD_CH_M_TTCAN_IR_WDI_Msk)   /**< Watchdog Interrupt */
#define CY_CANFD_PROTOCOL_ERROR_ARB_PHASE       (CANFD_CH_M_TTCAN_IR_PEA_Msk)   /**< Protocol Error in
                                                                                 * Arbitration Phase
                                                                                 */
#define CY_CANFD_PROTOCOL_ERROR_DATA_PHASE      (CANFD_CH_M_TTCAN_IR_PED_Msk)   /**< Protocol Error in Data Phase */
#define CY_CANFD_ACCESS_RESERVED_ADDR           (CANFD_CH_M_TTCAN_IR_ARA_Msk)   /**< Access to Reserved Address */

/** \} group_canfd_error_interrupt_masks */

/**
* \addtogroup group_canfd_interrupt_line_masks
* \{ Interrupt line selection masks
*/


#define CY_CANFD_INTERRUPT_LINE_0_EN            (CANFD_CH_M_TTCAN_ILE_EINT0_Msk) /**< Enable Interrupt Line 0 */
#define CY_CANFD_INTERRUPT_LINE_1_EN            (CANFD_CH_M_TTCAN_ILE_EINT1_Msk) /**< Enable Interrupt Line 1 */

/** \} group_canfd_interrupt_line_masks */

/**
* \addtogroup group_canfd_last_state_masks
* \{ Masks and bit positions of the Protocol Status Register (PSR) fields
*/
#define CY_CANFD_PSR_LEC_POS    (CANFD_CH_M_TTCAN_PSR_LEC_Pos ) /**< Last Error Code position */
#define CY_CANFD_PSR_LEC_MASK   (CANFD_CH_M_TTCAN_PSR_LEC_Msk ) /**< Last Error Code bit mask */
#define CY_CANFD_PSR_ACT_POS    (CANFD_CH_M_TTCAN_PSR_ACT_Pos ) /**< Activity position */
#define CY_CANFD_PSR_ACT_MASK   (CANFD_CH_M_TTCAN_PSR_ACT_Msk ) /**< Activity bit mask */
#define CY_CANFD_PSR_EP         (CANFD_CH_M_TTCAN_PSR_EP_Msk  ) /**< Error Passive */
#define CY_CANFD_PSR_EW         (CANFD_CH_M_TTCAN_PSR_EW_Msk  ) /**< Warning Status */
#define CY_CANFD_PSR_BO         (CANFD_CH_M_TTCAN_PSR_BO_Msk  ) /**< Bus_Off Status */
#define CY_CANFD_PSR_DLEC_POS   (CANFD_CH_M_TTCAN_PSR_DLEC_Pos) /**< Data Phase Last Error Code position */
#define CY_CANFD_PSR_DLEC_MASK  (CANFD_CH_M_TTCAN_PSR_DLEC_Msk) /**< Data Phase Last Error Code bit mask */
#define CY_CANFD_PSR_RESI       (CANFD_CH_M_TTCAN_PSR_RESI_Msk) /**< ESI flag of last received CAN FD Message */
#define CY_CANFD_PSR_RBRS       (CANFD_CH_M_TTCAN_PSR_RBRS_Msk) /**< BRS flag of last received CAN FD Message */
#define CY_CANFD_PSR_RFDF       (CANFD_CH_M_TTCAN_PSR_RFDF_Msk) /**< Received a CAN FD Message */
#define CY_CANFD_PSR_PXE        (CANFD_CH_M_TTCAN_PSR_PXE_Msk ) /**< Protocol Exception Event */
#define CY_CANFD_PSR_TDCV_POS   (CANFD_CH_M_TTCAN_PSR_TDCV_Pos) /**< Transmitter Delay Compensation Value position */
#define CY_CANFD_PSR_TDCV_MASK  (CANFD_CH_M_TTCAN_PSR_TDCV_Msk) /**< Transmitter Delay Compensation Value bit mask */

/** \} group_canfd_last_state_masks */

/** \cond INTERNAL_MACROS */

/** The number loops to make the timeout */
#define CY_CANFD_RETRY_COUNT                    (1000UL)

/** The delay timeout in usec */
#define CY_CANFD_STOP_TIMEOUT_US                (1U)

/** Number clock cycles delay needed after power domain power up */
#define CY_CANFD_RAM_PWR_DELAY_CYCLES           (150UL)

/** The maximum number of 32-bit words used for storage of a CAN message's
* data field
*/
#define CY_CANFD_DATA_ELEMENTS_MAX              (16U)
#define CY_CANFD_MESSAGE_RX_BUFFERS_MAX_CNT     (64UL)
#define CY_CANFD_MESSAGE_TX_BUFFERS_MAX_CNT     (32UL)
#define CY_CANFD_CLASSIC_CAN_DATA_LENGTH        (8U)

#define CY_CANFD_IS_MESSAGE_BUFFER_IDX_VALID(idx)  ((CY_CANFD_MESSAGE_RX_BUFFERS_MAX_CNT) > (idx))

/* The initialization timeout in usec */
#define CY_CANFD_INIT_TIMEOUT_US                (1U)

/* Deprecated */
#define CY_CANFD_STOP_TIMEOUT_MS                (1UL)
#define CY_CANFD_INIT_TIMEOUT_MS                (1UL)

/** \endcond */

/***************************************
*       Enumerations
***************************************/
/**
* \addtogroup group_canfd_enums
* \{
*/

/** CAN FD status enumeration */
typedef enum
{
    CY_CANFD_SUCCESS       = 0x00U,                                     /**< Returned successful */
    CY_CANFD_BAD_PARAM     = CY_CANFD_ID | CY_PDL_STATUS_ERROR | 0x01u, /**< Bad parameter was passed */
    CY_CANFD_ERROR_TIMEOUT = CY_CANFD_ID | CY_PDL_STATUS_ERROR | 0x02u, /**< A Time out error occurred */
} cy_en_canfd_status_t;

/** CAN FD Tx Buffer status enumeration */
typedef enum
{
    CY_CANFD_TX_BUFFER_IDLE              = 0u,
    CY_CANFD_TX_BUFFER_PENDING           = 1u, /**< Pending transmission */
    CY_CANFD_TX_BUFFER_TRANSMIT_OCCURRED = 2u, /**< Transmission occurred */
    CY_CANFD_TX_BUFFER_CANCEL_REQUESTED  = 3u, /**< Cancellation requested */
    CY_CANFD_TX_BUFFER_CANCEL_FINISHED   = 4u  /**< Cancellation finished */
} cy_en_canfd_tx_buffer_status_t;

/** CAN FD Tx/Rx buffer element size */
typedef enum
{
    CY_CANFD_BUFFER_DATA_SIZE_8  = 0u,   /**< 8 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_12 = 1u,   /**< 12 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_16 = 2u,   /**< 16 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_20 = 3u,   /**< 20 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_24 = 4u,   /**< 24 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_32 = 5u,   /**< 32 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_48 = 6u,   /**< 48 byte data field */
    CY_CANFD_BUFFER_DATA_SIZE_64 = 7u    /**< 64 byte data field */
} cy_en_canfd_buffer_data_size_t;

/** CAN FD Rx FIFO operating mode */
typedef enum
{
    CY_CANFD_FIFO_MODE_BLOCKING  = 0u,   /**< FIFO blocking mode */
    CY_CANFD_FIFO_MODE_OVERWRITE = 1u    /**< FIFO overwrite mode */
} cy_en_canfd_fifo_mode_t;

/** CAN FD accept non matching frames */
typedef enum
{
    CY_CANFD_ACCEPT_IN_RXFIFO_0  = 0u,   /**< Accept in Rx FIFO 0 */
    CY_CANFD_ACCEPT_IN_RXFIFO_1  = 1u,   /**< Accept in Rx FIFO 1 */
    CY_CANFD_REJECT_NON_MATCHING = 2u    /**< Reject the frames */
} cy_en_accept_non_matching_frames_t;

/** ID Filter element configuration type */
typedef enum
{
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_DISABLE_FILETER_ELEMENT   = 0x00u, /**< Disable filter element */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_STORE_RXFIFO0             = 0x01u, /**< Store in Rx FIFO 0, if filter matches */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_STORE_RXFIFO1             = 0x02u, /**< Store in Rx FIFO 1, if filter matches */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_REJECT_ID                 = 0x03u, /**< Reject ID if filter matches */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_SET_PRIORIY               = 0x04u, /**< Set priority if filter matches */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_SET_PIORITY_STORE_RXFIFO0 = 0x05u, /**< Set priority and store in FIFO 0,
                                                                         * if filter matches
                                                                         */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_SET_PIORITY_STORE_RXFIFO1 = 0x06u, /**< Set priority and store in FIFO 1,
                                                                         * if filter matches
                                                                         */
    CY_CANFD_ID_FILTER_ELEMNT_CONFIG_STORE_RXBUFF_OR_DEBUGMSG  = 0x07u  /**< Store into Rx Buffer or as debug message,
                                                                         * configuration of SFT[1:0] ignored
                                                                         */
}cy_en_canfd_id_filter_element_config_t;

/** Standard ID filter type */
typedef enum
{
    CY_CANFD_STD_ID_FILTER_TYPE_RANGE          = 0x00u, /**< The Range filter from SFID1 to SFID2 (SFID2 = SFID1) */
    CY_CANFD_STD_ID_FILTER_TYPE_DUAL           = 0x01u, /**< The Dual ID filter for SFID1 or SFID2 */
    CY_CANFD_STD_ID_FILTER_TYPE_CLASSIC        = 0x02u  /**< The Classic filter: SFID1 = filter, SFID2 = mask */
}cy_en_canfd_std_id_filter_type_t;

/** Extended ID filter type */
typedef enum
{
    CY_CANFD_EXT_ID_FILTER_TYPE_RANGE_AND_MASK = 0x00u, /**< The range filter from EFID1 to EFID2 (EFID2 = EFID1) */
    CY_CANFD_EXT_ID_FILTER_TYPE_DUAL           = 0x01u, /**< The dual ID filter for EFID1 or EFID2 */
    CY_CANFD_EXT_ID_FILTER_TYPE_CLASSIC        = 0x02u, /**< The classic filter: EFID1 = filter, EFID2 = mask */
    CY_CANFD_EXT_ID_FILTER_TYPE_RANGE          = 0x03u  /**< The range filter from EFID1 to EFID2 (EFID2 = EFID1),
                                                         * XIDAM mask not applied
                                                         */
}cy_en_canfd_ext_id_filter_type_t;

/** Type for indication of the received frame (Remote Transmission Request) */
typedef enum
{
    CY_CANFD_RTR_DATA_FRAME                 = 0x00u, /**< The received frame is a data frame */
    CY_CANFD_RTR_REMOTE_FRAME               = 0x01u  /**< The received frame is a remote frame */
}cy_en_canfd_rtr_t;

/** Extended Identifier type (whether the received frame has a standard or extended identifier) */
typedef enum
{
    CY_CANFD_XTD_STANDARD_ID                = 0x00u, /**< The 11-bit standard identifier */
    CY_CANFD_XTD_EXTENDED_ID                = 0x01u  /**< The 29-bit extended identifier */
}cy_en_canfd_xtd_t;

/** Error State Indicator type */
typedef enum
{
    CY_CANFD_ESI_ERROR_ACTIVE               = 0x00u, /**< The transmitting node is error active */
    CY_CANFD_ESI_ERROR_PASSIVE              = 0x01u  /**< The transmitting node is error passive */
}cy_en_canfd_esi_t;

/** FD Format type */
typedef enum
{
    CY_CANFD_FDF_STANDARD_FRAME             = 0x00u, /**< The standard frame format */
    CY_CANFD_FDF_CAN_FD_FRAME               = 0x01u  /**< The CAN FD frame format (new DLC-coding and CRC) */
}cy_en_canfd_fdf_t;

/** Accepted Non-matching Frame type */
typedef enum
{
    CY_CANFD_ANMF_MATCH_FILTER              = 0x00u, /**< The received frame matching filter index FIDX */
    CY_CANFD_ANMF_NOT_MATCH_FILTER          = 0x01u  /**< The received frame did not match any Rx filter element */
}cy_en_canfd_anmf_t;

/** Standard Filter Element Configuration type */
typedef enum
{
    CY_CANFD_SFEC_DISABLE                   = 0x00u, /**< Disable the filter element */
    CY_CANFD_SFEC_STORE_RX_FIFO_0           = 0x01u, /**< Store in Rx FIFO 0 if the filter matches */
    CY_CANFD_SFEC_STORE_RX_FIFO_1           = 0x02u, /**< Store in Rx FIFO 1 if the filter matches */
    CY_CANFD_SFEC_REJECT_ID                 = 0x03u, /**< Reject ID if the filter matches */
    CY_CANFD_SFEC_SET_PRIORITY              = 0x04u, /**< Set priority if the filter matches */
    CY_CANFD_SFEC_SET_PRIORITY_STORE_FIFO_0 = 0x05u, /**< Set priority and store in FIFO 0 if the filter matches */
    CY_CANFD_SFEC_SET_PRIORITY_STORE_FIFO_1 = 0x06u, /**< Set priority and store in FIFO 1 if filter matches */
    CY_CANFD_SFEC_STORE_RX_BUFFER           = 0x07u  /**< Store into Rx Buffer or as debug message,
                                                      * configuration of SFT[1:0] ignored
                                                      */
}cy_en_canfd_sfec_t;

/** Standard Filter Type */
typedef enum
{
    CY_CANFD_SFT_RANGE_SFID1_SFID2          = 0x00u, /**< The range filter from SFID1 to SFID2 (SFID2 >= SFID1) */
    CY_CANFD_SFT_DUAL_ID                    = 0x01u, /**< The Dual ID filter for SFID1 or SFID2 */
    CY_CANFD_SFT_CLASSIC_FILTER             = 0x02u, /**< The Classic filter: SFID1 = filter, SFID2 = mask */
    CY_CANFD_SFT_DISABLED                   = 0x03u  /**< The Filter element disabled */
}cy_en_canfd_sft_t;

/** Extended Filter Element Configuration type */
typedef enum
{
    CY_CANFD_EFEC_DISABLE                   = 0x00u, /**< Disable the filter element */
    CY_CANFD_EFEC_STORE_RX_FIFO_0           = 0x01u, /**< Store in Rx FIFO 0 if the filter matches */
    CY_CANFD_EFEC_STORE_RX_FIFO_1           = 0x02u, /**< Store in Rx FIFO 1 if the filter matches */
    CY_CANFD_EFEC_REJECT_ID                 = 0x03u, /**< Reject ID if the filter matches */
    CY_CANFD_EFEC_SET_PRIORITY              = 0x04u, /**< Set priority if the filter matches */
    CY_CANFD_EFEC_SET_PRIORITY_STORE_FIFO_0 = 0x05u, /**< Set priority and store in FIFO 0 if the filter matches */
    CY_CANFD_EFEC_SET_PRIORITY_STORE_FIFO_1 = 0x06u, /**< Set priority and store in FIFO 1 if filter matches */
    CY_CANFD_EFEC_STORE_RX_BUFFER           = 0x07u  /**< Store into Rx Buffer or as debug message,
                                                      * configuration of EFT[1:0] ignored
                                                      */
}cy_en_canfd_efec_t;

/** Extended Filter Type */
typedef enum
{
    CY_CANFD_EFT_RANGE_EFID1_EFID2          = 0x00u, /**< The range filter from EFID1 to EFID2 (EFID2 >= EFID1) */
    CY_CANFD_EFT_DUAL_ID                    = 0x01u, /**< The Dual ID filter for EFID1 or EFID2 */
    CY_CANFD_EFT_CLASSIC_FILTER             = 0x02u, /**< The Classic filter: EFID1 = filter, EFID2 = mask */
    CY_CANFD_EFT_RANGE_EFID1_EFID2_NO_MSK   = 0x03u  /**< The range filter from EFID1 to EFID2 (EFID2 >= EFID1), XIDAM mask not applied */
}cy_en_canfd_eft_t;

/** Test Mode Type */
typedef enum
{
    CY_CANFD_TEST_MODE_DISABLE              = 0x00u, /**< The normal operation. Test Mode is disabled */
    CY_CANFD_TEST_MODE_BUS_MONITORING       = 0x01u, /**< The Bus Monitoring Mode */
    CY_CANFD_TEST_MODE_EXTERNAL_LOOP_BACK   = 0x02u, /**< The External Loop Back Mode */
    CY_CANFD_TEST_MODE_INTERNAL_LOOP_BACK   = 0x03u  /**< The Internal Loop Back Mode */
}cy_stc_canfd_test_mode_t;

/** Last Error Code and Data Phase Last Error Code Type. \n
*   Used with Cy_CANFD_GetLastError() for LEC and DLEC fields of the
*   Protocol Status Register.
*/
typedef enum
{
    CY_CANFD_LEC_NO_ERROR    = 0x00u, /**< No error occurred since LEC was reset
                                       * by successful reception or transmission.
                                       */
    CY_CANFD_LEC_STUFF_ERROR = 0x01u, /**< More than 5 equal bits in a sequence
                                       * occurred in a part of a received message
                                       */
    CY_CANFD_LEC_FORM_ERROR  = 0x02u, /**< A fixed format part of a received frame
                                       * has the wrong format
                                       */
    CY_CANFD_LEC_ACK_ERROR   = 0x03u, /**< The message this CAN FD Core transmitted
                                       * was not acknowledged by another node
                                       */
    CY_CANFD_LEC_BIT1_ERROR  = 0x04u, /**< While trying to send a recessive bit (1)
                                       * a dominant level (0) was sampled
                                       */
    CY_CANFD_LEC_BIT0_ERROR  = 0x05u, /**< While trying to send a dominant bit (0)
                                       * a recessive level (1) was sampled
                                       */
    CY_CANFD_LEC_CRC_ERROR   = 0x06u, /**< The CRC checksum was incorrect */
    CY_CANFD_LEC_NO_CHANGE   = 0x07u  /**< No CAN bus event was detected since the
                                       * last CPU read access to the Protocol
                                       * Status Register
                                       */
}cy_en_canfd_LEC_t;

/** Bus Activity State field of the PSR
*   Used with Cy_CANFD_GetLastError() for ACT field of the
*   Protocol Status Register. */
typedef enum
{
    CY_CANFD_PSR_ACT_SYNC = 0x00u, /**< The node is synchronizing on CAN communication */
    CY_CANFD_PSR_ACT_IDLE = 0x01u, /**< The node is neither receiver nor transmitter */
    CY_CANFD_PSR_ACT_RX   = 0x02u, /**< The node is operating as receiver */
    CY_CANFD_PSR_ACT_TX   = 0x03u  /**< The node is operating as transmitter */
}cy_en_canfd_PSR_ACT_t;

/** \} group_canfd_enums */

/** \cond PARAM_CHECK_MACROS */

#define CY_CANFD_CHANNEL_MAX_CNT                    (8U)
#define CY_CANFD_IS_CHANNEL_VALID(id)               ((CY_CANFD_CHANNEL_MAX_CNT - 1U) >= (id))
#define CY_CANFD_IS_CHS_MASK_VALID(channels)        (0U == ((channels) & (uint32_t)~CANFD_CTL_STOP_REQ_Msk))
#define CY_CANFD_NOM_PRESCALER_MAX                  (511U)
#define CY_CANFD_IS_NOM_PRESCALER_VALID(nbrp)       ((CY_CANFD_NOM_PRESCALER_MAX) >= (nbrp))
#define CY_CANFD_IS_NOM_TIME_SEG_1_VALID(ntseg1)    (0U < (ntseg1))
#define CY_CANFD_NOM_TIME_SEG_2_MAX                 (127U)
#define CY_CANFD_IS_NOM_TIME_SEG_2_VALID(ntseg2)    (((CY_CANFD_NOM_TIME_SEG_2_MAX) >= (ntseg2)) && (0U < (ntseg2)))
#define CY_CANFD_NOM_SYNC_JUMP_WIDTH_MAX            (127U)
#define CY_CANFD_IS_NOM_SYNC_JUMP_WIDTH_VALID(nsjw) ((CY_CANFD_NOM_SYNC_JUMP_WIDTH_MAX) >= (nsjw))
#define CY_CANFD_DAT_PRESCALER_MAX                  (31U)
#define CY_CANFD_IS_DAT_PRESCALER_VALID(dbrp)       ((CY_CANFD_DAT_PRESCALER_MAX) >= (dbrp))
#define CY_CANFD_DAT_TIME_SEG_1_MAX                 (31U)
#define CY_CANFD_IS_DAT_TIME_SEG_1_VALID(dtseg1)    ((CY_CANFD_DAT_TIME_SEG_1_MAX) >= (dtseg1))
#define CY_CANFD_DAT_TIME_SEG_2_MAX                 (15U)
#define CY_CANFD_IS_DAT_TIME_SEG_2_VALID(dtseg2)    ((CY_CANFD_DAT_TIME_SEG_2_MAX) >= (dtseg2))
#define CY_CANFD_DAT_SYNC_JUMP_WIDTH_MAX            (15)
#define CY_CANFD_IS_DAT_SYNC_JUMP_WIDTH_VALID(dsjw) ((CY_CANFD_DAT_SYNC_JUMP_WIDTH_MAX) >= (dsjw))
#define CY_CANFD_IS_ILE_MASK_VALID(intmsk)             (0U == ((intmsk) & (uint32_t)~(CANFD_CH_M_TTCAN_ILE_EINT0_Msk |\
                                                                                CANFD_CH_M_TTCAN_ILE_EINT1_Msk)))
#define CY_CANFD_TDCO_MAX                           (0x7FU)
#define CY_CANFD_IS_TDCO_VALID(tdco)                ((CY_CANFD_TDCO_MAX) >= (tdco))
#define CY_CANFD_TDCF_MAX                           (0x7FU)
#define CY_CANFD_IS_TDCF_VALID(tdcf)                ((CY_CANFD_TDCF_MAX) >= (tdcf))
#define CY_CANFD_SID_FILTERS_MAX_CNT                (128U)
#define CY_CANFD_IS_SID_FILTERS_VALID(num)          ((CY_CANFD_SID_FILTERS_MAX_CNT) >= (num))
#define CY_CANFD_XID_FILTERS_MAX_CNT                (64U)
#define CY_CANFD_IS_XID_FILTERS_VALID(num)          ((CY_CANFD_XID_FILTERS_MAX_CNT) >= (num))
#define CY_CANFD_SFID_MAX                           (0x7FFU)
#define CY_CANFD_IS_SFID_VALID(sfid)                ((CY_CANFD_SFID_MAX) >= (sfid))
#define CY_CANFD_IS_SFEC_VALID(sfec)                ((CY_CANFD_SFEC_DISABLE == (sfec)) || \
                                                     (CY_CANFD_SFEC_STORE_RX_FIFO_0 == (sfec)) || \
                                                     (CY_CANFD_SFEC_STORE_RX_FIFO_1 == (sfec)) || \
                                                     (CY_CANFD_SFEC_REJECT_ID == (sfec)) || \
                                                     (CY_CANFD_SFEC_SET_PRIORITY == (sfec)) || \
                                                     (CY_CANFD_SFEC_SET_PRIORITY_STORE_FIFO_0 == (sfec)) || \
                                                     (CY_CANFD_SFEC_SET_PRIORITY_STORE_FIFO_1 == (sfec)) || \
                                                     (CY_CANFD_SFEC_STORE_RX_BUFFER == (sfec)))
#define CY_CANFD_IS_SFT_VALID(sft)                  ((CY_CANFD_SFT_RANGE_SFID1_SFID2 == (sft)) || \
                                                     (CY_CANFD_SFT_DUAL_ID == (sft)) || \
                                                     (CY_CANFD_SFT_CLASSIC_FILTER == (sft)) || \
                                                     (CY_CANFD_SFT_DISABLED == (sft)))
#define CY_CANFD_EFID_MAX                           (0x1FFFFFFFUL)
#define CY_CANFD_IS_EFID_VALID(efid)                ((CY_CANFD_EFID_MAX) >= (efid))
#define CY_CANFD_IS_EFEC_VALID(efec)                ((CY_CANFD_EFEC_DISABLE == (efec)) || \
                                                     (CY_CANFD_EFEC_STORE_RX_FIFO_0 == (efec)) || \
                                                     (CY_CANFD_EFEC_STORE_RX_FIFO_1 == (efec)) || \
                                                     (CY_CANFD_EFEC_REJECT_ID == (efec)) || \
                                                     (CY_CANFD_EFEC_SET_PRIORITY == (efec)) || \
                                                     (CY_CANFD_EFEC_SET_PRIORITY_STORE_FIFO_0 == (efec)) || \
                                                     (CY_CANFD_EFEC_SET_PRIORITY_STORE_FIFO_1 == (efec)) || \
                                                     (CY_CANFD_EFEC_STORE_RX_BUFFER == (efec)))
#define CY_CANFD_IS_EFT_VALID(eft)                  ((CY_CANFD_EFT_RANGE_EFID1_EFID2 == (eft)) || \
                                                     (CY_CANFD_EFT_DUAL_ID == (eft)) || \
                                                     (CY_CANFD_EFT_CLASSIC_FILTER == (eft)) || \
                                                     (CY_CANFD_EFT_RANGE_EFID1_EFID2_NO_MSK == (eft)))

#define CY_CANFD_IS_ACCEPT_MATCHING_VALID(match)    ((CY_CANFD_ACCEPT_IN_RXFIFO_0 == (match)) || \
                                                     (CY_CANFD_ACCEPT_IN_RXFIFO_1 == (match)) || \
                                                     (CY_CANFD_REJECT_NON_MATCHING == (match)))

#define CY_CANFD_IS_BUF_DATA_SIZE_VALID(size, mode) ((mode) ? \
                                                     ((CY_CANFD_BUFFER_DATA_SIZE_8 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_12 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_16 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_20 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_24 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_32 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_48 == (size)) || \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_64 == (size))) : \
                                                      (CY_CANFD_BUFFER_DATA_SIZE_8 == (size)))

#define CY_CANFD_IS_FIFO_MODE_VALID(mode)           ((CY_CANFD_FIFO_MODE_BLOCKING == (mode)) || \
                                                     (CY_CANFD_FIFO_MODE_OVERWRITE == (mode)))

#define CY_CANFD_FIFO_MAX_CNT                       (64U)
#define CY_CANFD_IS_FIFO_NUM_VALID(num)             ((CY_CANFD_FIFO_MAX_CNT) >= (num))

#define CY_CANFD_WATERMARK_MAX                      (127U)
#define CY_CANFD_IS_WATERMARK_VALID(watermark)      ((CY_CANFD_WATERMARK_MAX) >= (watermark))

#define CY_CANFD_IS_RX_BUF_NUM_VALID(num)           ((CY_CANFD_MESSAGE_RX_BUFFERS_MAX_CNT) >= (num))
#define CY_CANFD_IS_TX_BUF_NUM_VALID(num)           ((CY_CANFD_MESSAGE_TX_BUFFERS_MAX_CNT) >= (num))

#define CY_CANFD_ID_MAX                             (0X1FFFFFFFUL)
#define CY_CANFD_IS_ID_VALID(id)                    ((CY_CANFD_ID_MAX) >= (id))
#define CY_CANFD_IS_RTR_VALID(rtr)                  ((CY_CANFD_RTR_DATA_FRAME == (rtr)) || \
                                                     (CY_CANFD_RTR_REMOTE_FRAME == (rtr)))
#define CY_CANFD_IS_XTD_VALID(xtd)                  ((CY_CANFD_XTD_STANDARD_ID == (xtd)) || \
                                                     (CY_CANFD_XTD_EXTENDED_ID == (xtd)))
#define CY_CANFD_IS_ESI_VALID(esi)                  ((CY_CANFD_ESI_ERROR_ACTIVE == (esi)) || \
                                                     (CY_CANFD_ESI_ERROR_PASSIVE == (esi)))

#define CY_CANFD_RXTS_MAX                           (0XFFFFUL)
#define CY_CANFD_IS_RXTS_VALID(rxts)                ((CY_CANFD_RXTS_MAX) >= (rxts))
#define CY_CANFD_DLC_MAX                            (0XFFFFUL)
#define CY_CANFD_IS_DLC_VALID(dlc)                  ((CY_CANFD_DLC_MAX) >= (dlc))
#define CY_CANFD_IS_FDF_VALID(fdf)                  ((CY_CANFD_FDF_STANDARD_FRAME == (fdf)) || \
                                                     (CY_CANFD_FDF_CAN_FD_FRAME == (fdf)))
#define CY_CANFD_FIDX_MAX                           (127U)
#define CY_CANFD_IS_FIDX_VALID(fidx)                ((CY_CANFD_FIDX_MAX) >= (fidx))
#define CY_CANFD_IS_ANMF_VALID(anmf)                ((CY_CANFD_ANMF_MATCH_FILTER == (anmf)) || \
                                                     (CY_CANFD_ANMF_NOT_MATCH_FILTER == (anmf)))

#define CY_CANFD_TX_BUFFER_MM_MAX                   (255U)
#define CY_CANFD_IS_TX_BUFFER_MM_VALID(mm)          ((CY_CANFD_TX_BUFFER_MM_MAX) >= (mm))

/** \endcond */


/***************************************
*       Configuration Structures
***************************************/

/**
* \addtogroup group_canfd_data_structures
* \{
*/

/** R0 register */
typedef struct
{
    volatile uint32_t id;                /**< Identifier */
    volatile cy_en_canfd_rtr_t    rtr;   /**< Remote transmission request */
    volatile cy_en_canfd_xtd_t    xtd;   /**< Extended identifier */
    volatile cy_en_canfd_esi_t    esi;   /**< Error state indicator */
} cy_stc_canfd_r0_t;

/** R1 register */
typedef struct
{
    volatile uint32_t rxts;              /**< Rx timestamp */
    volatile uint32_t dlc;               /**< Data length code */
    volatile bool     brs;               /**< Bit rate switch */
    volatile cy_en_canfd_fdf_t    fdf;   /**< Extended data length */
    volatile uint32_t fidx;              /**< Filter index */
    volatile cy_en_canfd_anmf_t   anmf;  /**< Accepted non-matching frame */
} cy_stc_canfd_r1_t;

/** Rx buffer */
typedef struct
{
    cy_stc_canfd_r0_t *r0_f;             /**< Rx buffer element for R0. See \ref cy_stc_canfd_r0_t */
    cy_stc_canfd_r1_t *r1_f;             /**< Rx buffer element for R1. See \ref cy_stc_canfd_r1_t */
    uint32_t          *data_area_f; /**< Rx buffer element for Rn */
} cy_stc_canfd_rx_buffer_t;

/** T0 register */
typedef struct
{
    volatile uint32_t id;            /**< Identifier */
    volatile cy_en_canfd_rtr_t rtr;  /**< Remote transmission request. 0:data frame, 1:remote frame */
    volatile cy_en_canfd_xtd_t xtd;  /**< Extended identifier. 0:11-bit standard identifier, 1:29-bit
                                      * extended identifier
                                      */
    volatile cy_en_canfd_esi_t esi;  /**< Error state indicator */
} cy_stc_canfd_t0_t;

/** T1 register */
typedef struct
{
    volatile uint32_t dlc;           /**< Data length code */
    volatile bool     brs;           /**< Bit rate switching */
    volatile cy_en_canfd_fdf_t fdf;  /**< FD Format */
    volatile bool    efc;            /**< Event FIFO control. false: Do not store Tx events, true: Store Tx events */
    volatile uint32_t mm;            /**< Message marker */
} cy_stc_canfd_t1_t;

/** Tx buffer register */
typedef struct
{
    cy_stc_canfd_t0_t *t0_f;          /**< Tx buffer element for T0. See \ref cy_stc_canfd_t0_t */
    cy_stc_canfd_t1_t *t1_f;          /**< Tx buffer element for T1. See \ref cy_stc_canfd_t1_t */
    uint32_t          *data_area_f; /**< Tx buffer element for Tn */
} cy_stc_canfd_tx_buffer_t;

/** Message ID filter register */
typedef struct
{
    volatile uint32_t sfid2;            /**< Standard filter ID 2 */
    volatile uint32_t sfid1;            /**< Standard filter ID 1 */
    volatile cy_en_canfd_sfec_t sfec;   /**< Standard filter element configuration */
    volatile cy_en_canfd_sft_t sft;     /**< Standard filter Type */
} cy_stc_id_filter_t;

/** F0 register */
typedef struct
{
    volatile uint32_t efid1;            /**< Extended filter ID 1 */
    volatile cy_en_canfd_efec_t efec;   /**< Extended filter element configuration */
} cy_stc_canfd_f0_t;

/** F1 register */
typedef struct
{
    volatile uint32_t efid2;            /**< Extended filter ID 2 */
    volatile cy_en_canfd_eft_t eft;     /**< Extended filter type */
} cy_stc_canfd_f1_t;

/** Extended message ID filter register */
typedef struct
{
    const cy_stc_canfd_f0_t *f0_f;   /**< Extended message ID filter element for F0. See \ref cy_stc_canfd_f0_t */
    const cy_stc_canfd_f1_t *f1_f;   /**< Extended message ID filter element for F1. See \ref cy_stc_canfd_f1_t */
} cy_stc_extid_filter_t;

/** CAN FD bitrate */
typedef struct
{
    uint16_t prescaler;      /**< Baud rate prescaler */
    uint8_t  timeSegment1;   /**< Time segment before sample point */
    uint8_t  timeSegment2;   /**< Time segment after sample point */
    uint8_t  syncJumpWidth;  /**< Synchronization jump width */
} cy_stc_canfd_bitrate_t;

/** CAN FD transceiver delay compensation offset configuration */
typedef struct
{
    bool    tdcEnabled;      /**< Transceiver delay compensation enabled */
    uint8_t tdcOffset;       /**< Transmitter delay compensation offset */
    uint8_t tdcFilterWindow; /**< Transmitter delay compensation filter window length */
} cy_stc_canfd_transceiver_delay_compensation_t;

/** Standard ID filter configuration */
typedef struct
{
    uint8_t             numberOfSIDFilters;        /**< Number Of standard ID filters */
    const cy_stc_id_filter_t *sidFilter;           /**< Message ID Filter register */
} cy_stc_canfd_sid_filter_config_t;

/** Extended ID filter configuration */
typedef struct
{
    uint8_t                 numberOfEXTIDFilters;  /**< Number Of extended ID filters */
    const cy_stc_extid_filter_t *extidFilter;     /**< Extended message ID filter register */
    uint32_t                extIDANDMask;          /**< Extended ID AND Mask */
} cy_stc_canfd_extid_filter_config_t;

/** Global filter configuration */
typedef struct
{
  cy_en_accept_non_matching_frames_t nonMatchingFramesStandard;  /**< Non matching frames standard */
  cy_en_accept_non_matching_frames_t nonMatchingFramesExtended;  /**< Non matching frames extended */
  bool                               rejectRemoteFramesStandard; /**< Reject remote frames standard */
  bool                               rejectRemoteFramesExtended; /**< Reject remote frames extended */
} cy_stc_canfd_global_filter_config_t;

/** Rx FIFO configuration */
typedef struct
{
    cy_en_canfd_fifo_mode_t mode;                   /**< CAN FD Rx FIFO operating mode */
    uint8_t                 watermark;              /**< Watermark */
    uint8_t                 numberOfFIFOElements;   /**< Number Of FIFO elements. Note:
                                                     * The Rx FIFO size must be greater than 1 when
                                                     * FIFO Top Pointer Logic is enabled.
                                                     */
    bool                    topPointerLogicEnabled; /**< Top pointer logic enabled */
}cy_en_canfd_fifo_config_t;

/**
* Message transmission complete callback function (cy_canfd_tx_msg_func_ptr_t).
* Signals a successful completed transmission.
* Triggered with
* \ref CY_CANFD_TRANSMISSION_COMPLETE
* interrupt event
*/
typedef void (*cy_canfd_tx_msg_func_ptr_t)( void );

/**
* The message reception callback function for message received in the dedicated
* Rx Buffer or in Rx FIFO (cy_canfd_rx_msg_func_ptr_t)
*
* Signals that CAN FD has received a new message.
* - If message was received in the dedicated Rx Buffer (0 - 63), rxFIFOMsg is False
*   and u8MsgBufOrFIFONum indicates the Rx Buffer number.
*
* - If message was received in Rx FIFO (0/1),
*   rxFIFOMsg is True and u8MsgBufOrFIFONum indicates  the FIFO number.
*
* Triggered with corresponding         \n
* \ref CY_CANFD_RX_BUFFER_NEW_MESSAGE  \n
* \ref CY_CANFD_RX_FIFO_0_NEW_MESSAGE  \n
* \ref CY_CANFD_RX_FIFO_1_NEW_MESSAGE  \n
* interrupt events.
*/
typedef void (*cy_canfd_rx_msg_func_ptr_t)(bool rxFIFOMsg,
                                           uint8_t msgBufOrRxFIFONum,
                                           cy_stc_canfd_rx_buffer_t* basemsg
                                           );

/**
* The error callback function (cy_canfd_error_func_ptr_t).
* Signals that the CAN bus status changed or an error occurred. \n
* Triggered with                               \n
* \ref CY_CANFD_RX_FIFO_0_WATERMARK_REACHED    \n
* \ref CY_CANFD_RX_FIFO_0_FULL                 \n
* \ref CY_CANFD_RX_FIFO_0_MSG_LOST             \n
* \ref CY_CANFD_RX_FIFO_1_WATERMARK_REACHED    \n
* \ref CY_CANFD_RX_FIFO_1_FULL                 \n
* \ref CY_CANFD_RX_FIFO_1_MSG_LOST             \n
* \ref CY_CANFD_TX_FIFO_1_WATERMARK_REACHED    \n
* \ref CY_CANFD_TX_FIFO_1_FULL                 \n
* \ref CY_CANFD_TX_FIFO_1_MSG_LOST             \n
* \ref CY_CANFD_TIMESTAMP_WRAPAROUND           \n
* \ref CY_CANFD_MRAM_ACCESS_FAILURE            \n
* \ref CY_CANFD_TIMEOUT_OCCURRED               \n
* \ref CY_CANFD_BIT_ERROR_CORRECTED            \n
* \ref CY_CANFD_BIT_ERROR_UNCORRECTED          \n
* \ref CY_CANFD_ERROR_LOG_OVERFLOW             \n
* \ref CY_CANFD_ERROR_PASSIVE                  \n
* \ref CY_CANFD_WARNING_STATUS                 \n
* \ref CY_CANFD_BUS_OFF_STATUS                 \n
* \ref CY_CANFD_WATCHDOG_INTERRUPT             \n
* \ref CY_CANFD_PROTOCOL_ERROR_ARB_PHASE       \n
* \ref CY_CANFD_PROTOCOL_ERROR_DATA_PHASE      \n
* \ref CY_CANFD_ACCESS_RESERVED_ADDR           \n
* interrupt events.
*/
typedef void (*cy_canfd_error_func_ptr_t)(uint32_t errorMask);

/** CAN FD configuration */
typedef struct
{
    cy_canfd_tx_msg_func_ptr_t          txCallback;         /**< Callback function for transmit completed.
                                                             * Can be NULL
                                                             */
    cy_canfd_rx_msg_func_ptr_t          rxCallback;         /**< Callback function for receive completed.
                                                             * Can be NULL
                                                             */
    cy_canfd_error_func_ptr_t           errorCallback;      /**< Callback function for CAN related errors.
                                                             *   Can be NULL
                                                             */
    bool                                canFDMode;          /**< TRUE:CAN FD mode, FALSE:Classic CAN mode */
    const cy_stc_canfd_bitrate_t        *bitrate;           /**< CAN bitrate setting */
    const cy_stc_canfd_bitrate_t        *fastBitrate;       /**< CAN Fast bitrate setting */
    const cy_stc_canfd_transceiver_delay_compensation_t *tdcConfig; /**< CAN transceiver delay compensation setting */

    const cy_stc_canfd_sid_filter_config_t    *sidFilterConfig;    /**< CAN Standard ID filter setting */
    const cy_stc_canfd_extid_filter_config_t  *extidFilterConfig;  /**< CAN Extended ID filter setting */
    const cy_stc_canfd_global_filter_config_t *globalFilterConfig; /**< CAN global filter setting */

    cy_en_canfd_buffer_data_size_t      rxBufferDataSize;   /**< Rx Buffer Data Size */
    cy_en_canfd_buffer_data_size_t      rxFIFO1DataSize;    /**< Rx FIFO 1 Data Size */
    cy_en_canfd_buffer_data_size_t      rxFIFO0DataSize;    /**< Rx FIFO 0 Data Size */
    cy_en_canfd_buffer_data_size_t      txBufferDataSize;   /**< Tx Buffer Data Size */

    const cy_en_canfd_fifo_config_t     *rxFIFO0Config;      /**< Rx FIFO 0 configuration */
    const cy_en_canfd_fifo_config_t     *rxFIFO1Config;      /**< Rx FIFO 1 configuration */
    uint8_t                             noOfRxBuffers;      /**< Number of Rx Buffers (Max 64) */
    uint8_t                             noOfTxBuffers;      /**< Number of Rx Buffers (Max 32) */
    uint32_t                            messageRAMaddress;  /**< The start address of Message RAM for the channel */
    uint32_t                            messageRAMsize;     /**< The size in bytes of Message RAM for the channel */
} cy_stc_canfd_config_t;


/**
*  CAN FD interrupt pointer structure. Holds some pointers to callback functions and buffer
*/
typedef struct
{
    cy_canfd_tx_msg_func_ptr_t  canFDTxInterruptFunction; /**< The pointer to transmit interrupt callback */
    cy_canfd_rx_msg_func_ptr_t  canFDRxInterruptFunction; /**< The pointer to receive interrupt callback
                                                           * (dedicated Rx Buffer or RxFIFO without Top pointer logic)
                                                           */
    cy_canfd_error_func_ptr_t   canFDErrorInterruptFunction;  /**< The pointer to error interrupt callback */
} cy_stc_canfd_interrupt_handling_t;

/** Context structure */
typedef struct
{
    cy_stc_canfd_interrupt_handling_t canFDInterruptHandling;  /**< Interrupt callback */
    uint32_t                          messageRAMaddress;  /**< The start address of Message RAM for the channel */
    uint32_t                          messageRAMsize;     /**< The size in bytes of Message RAM for the channel */
} cy_stc_canfd_context_t;

/** \} group_canfd_data_structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_canfd_functions
* \{
*/
__STATIC_INLINE void Cy_CANFD_Enable(CANFD_Type *base, uint32_t channelMask);
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_Disable(CANFD_Type *base, uint32_t channelMask);
__STATIC_INLINE void Cy_CANFD_EnableMRAM(CANFD_Type *base, uint32_t channelMask, uint16_t delay);
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_DisableMRAM(CANFD_Type *base);
__STATIC_INLINE void Cy_CANFD_SetBitrate(CANFD_Type *base, uint32_t chan, const cy_stc_canfd_bitrate_t *bitrate);
__STATIC_INLINE void Cy_CANFD_SetFastBitrate(CANFD_Type *base, uint32_t chan, const cy_stc_canfd_bitrate_t *fastBitrate);
void Cy_CANFD_SidFilterSetup(CANFD_Type const *base, uint32_t chan,
                             const cy_stc_id_filter_t *filter,
                             uint32_t index,
                             cy_stc_canfd_context_t const *context);
void Cy_CANFD_SidFiltersSetup(CANFD_Type const *base, uint32_t chan,
                              const cy_stc_canfd_sid_filter_config_t *filterConfig,
                              cy_stc_canfd_context_t const *context);
void Cy_CANFD_XidFilterSetup(CANFD_Type const *base, uint32_t chan,
                             const cy_stc_extid_filter_t *filter,
                             uint32_t index,
                             cy_stc_canfd_context_t const *context);

void Cy_CANFD_XidFiltersSetup(CANFD_Type const *base, uint32_t chan,
                              const cy_stc_canfd_extid_filter_config_t *filterConfig,
                              cy_stc_canfd_context_t const *context);
cy_en_canfd_status_t Cy_CANFD_TxBufferConfig(CANFD_Type const *base, uint32_t chan,
                                             const cy_stc_canfd_tx_buffer_t *txBuffer,
                                             uint8_t index,
                                             cy_stc_canfd_context_t const *context);
uint32_t Cy_CANFD_CalcRxBufAdrs(CANFD_Type const *base, uint32_t chan,
                                        uint32_t index,
                                        cy_stc_canfd_context_t const *context);
uint32_t Cy_CANFD_CalcRxFifoAdrs(CANFD_Type const *base, uint32_t chan,
                                         uint32_t fifoNumber,
                                         uint32_t index,
                                         cy_stc_canfd_context_t const *context);
cy_en_canfd_status_t Cy_CANFD_GetRxBuffer(CANFD_Type const *base, uint32_t chan,
                                          const uint32_t bufferAddress,
                                          cy_stc_canfd_rx_buffer_t const *rxBuffer);
cy_en_canfd_status_t Cy_CANFD_GetFIFOTop(CANFD_Type const *base, uint32_t chan,
                                          const uint8_t FIFONumber,
                                          cy_stc_canfd_rx_buffer_t const *rxBuffer);
cy_en_canfd_status_t Cy_CANFD_ExtractMsgFromRXBuffer(CANFD_Type *base, uint32_t chan, bool rxFIFOMsg,
                                                     uint8_t msgBufOrRxFIFONum,
                                                     cy_stc_canfd_rx_buffer_t const *rxBuffer,
                                                     cy_stc_canfd_context_t const *context);
void Cy_CANFD_AckRxBuf(CANFD_Type *base, uint32_t chan, uint32_t bufNum);
void Cy_CANFD_AckRxFifo(CANFD_Type *base, uint32_t chan, uint32_t FIFOnumber);
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_ConfigChangesEnable(CANFD_Type *base, uint32_t chan);
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_ConfigChangesDisable(CANFD_Type *base, uint32_t chan);
__STATIC_INLINE void Cy_CANFD_TestModeConfig(CANFD_Type *base, uint32_t chan, cy_stc_canfd_test_mode_t testMode);
__STATIC_INLINE void Cy_CANFD_SetTDC(CANFD_Type *base, uint32_t chan,
                                     const cy_stc_canfd_transceiver_delay_compensation_t *tdcConfig);
uint32_t Cy_CANFD_GetLastError(CANFD_Type const *base, uint32_t chan);

/** \} group_canfd_functions */

/**
* \addtogroup group_canfd_functions
* \{
*/

void Cy_CANFD_IrqHandler(CANFD_Type *base, uint32_t chan, cy_stc_canfd_context_t const *context);
cy_en_canfd_status_t Cy_CANFD_Init(CANFD_Type *base, uint32_t chan,
                                   const cy_stc_canfd_config_t *config,
                                   cy_stc_canfd_context_t *context);
cy_en_canfd_status_t Cy_CANFD_DeInit(CANFD_Type *base, uint32_t chan, cy_stc_canfd_context_t *context);
cy_en_canfd_status_t Cy_CANFD_TransmitTxBuffer(CANFD_Type *base, uint32_t chan,
                                                         uint8_t index);
cy_en_canfd_status_t Cy_CANFD_UpdateAndTransmitMsgBuffer(CANFD_Type *base, uint32_t chan,
                                                         const cy_stc_canfd_tx_buffer_t *txBuffer,
                                                         uint8_t index,
                                                         cy_stc_canfd_context_t const *context);

cy_en_canfd_tx_buffer_status_t Cy_CANFD_GetTxBufferStatus(CANFD_Type const *base, uint32_t chan, uint8_t index);


/** \} group_canfd_functions */

/**
* \addtogroup group_canfd_functions
* \{
*/

__STATIC_INLINE uint32_t Cy_CANFD_GetInterruptStatus(CANFD_Type const *base, uint32_t chan);
__STATIC_INLINE void Cy_CANFD_ClearInterrupt(CANFD_Type *base, uint32_t chan, uint32_t status);
__STATIC_INLINE uint32_t Cy_CANFD_GetInterruptMask(CANFD_Type const *base, uint32_t chan);
__STATIC_INLINE void Cy_CANFD_SetInterruptMask(CANFD_Type *base, uint32_t chan, uint32_t interrupt);
__STATIC_INLINE uint32_t Cy_CANFD_GetInterruptLine(CANFD_Type const *base, uint32_t chan);
__STATIC_INLINE void Cy_CANFD_SetInterruptLine(CANFD_Type *base, uint32_t chan, uint32_t interruptLineMask);
__STATIC_INLINE bool Cy_CANFD_IsInterruptLineEnabled(CANFD_Type const *base, uint32_t chan,
                                                     uint32_t interruptLineMask);
__STATIC_INLINE void Cy_CANFD_EnableInterruptLine(CANFD_Type *base, uint32_t chan, uint32_t interruptLineMask);

/** \} group_canfd_functions */

/**
* \addtogroup group_canfd_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_CANFD_Enable
****************************************************************************//**
*
*  Enables the CAN FD channels.
*
* \note
* Call Cy_CANFD_Enable before Cy_CANFD_Init.
*
* \param *base
* The CAN FD registers structure pointer.
*
* \param channelMask
* The channel mask (0-0xFF).
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Enable
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_Enable(CANFD_Type *base, uint32_t channelMask)
{
    CY_ASSERT_L2(CY_CANFD_IS_CHS_MASK_VALID(channelMask));

    /* Clock Start Request for the channels */
    CANFD_CTL(base) = _CLR_SET_FLD32U(CANFD_CTL(base),
                                     CANFD_CTL_STOP_REQ,
                                     ~channelMask);
}


/*******************************************************************************
* Function Name: Cy_CANFD_Disable
****************************************************************************//**
*
* Disables the CAN FD channels to stop providing clocks to un-used CAN channels
* for power saving with this functionality.
*
* \note
* Call Cy_CANFD_Disable only after Cy_CANFD_DeInit. Do not access the CAN FD
* registers until calling Cy_CANFD_Enable again.
*
* \param *base
*  The CAN FD registers structure pointer.
*
* \param channelMask
*     The channel mask (0-0xFF).
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_Disable
*
*******************************************************************************/
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_Disable(CANFD_Type *base, uint32_t channelMask)
{
    cy_en_canfd_status_t ret = CY_CANFD_ERROR_TIMEOUT;
    uint32_t                retry = CY_CANFD_RETRY_COUNT;

    CY_ASSERT_L2(CY_CANFD_IS_CHS_MASK_VALID(channelMask));

    /* Clock Stop Request for the channels */
    CANFD_CTL(base) = _CLR_SET_FLD32U(CANFD_CTL(base),
                                     CANFD_CTL_STOP_REQ,
                                     channelMask);

    /* Wait for Clock Stop Acknowledge for the channel */
    while ((retry > 0UL) &&
           !(channelMask == (channelMask & CANFD_STATUS(base))))
    {
        Cy_SysLib_DelayUs(CY_CANFD_STOP_TIMEOUT_US);
        retry--;
    }

    if (retry > 0UL)
    {
        ret = CY_CANFD_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_EnableMRAM
****************************************************************************//**
*
*  Switches MRAM on and enables the channels.
*
* \param *base
*     The CAN FD registers structure pointer.
*
* \param channelMask
*     The channel mask (0-0xFF).
*
* \param delay
*     The delay in usec to wait power up time before MRAM can be used.
*     Recommended value is 150 CPU cycles or 6 usec for the 25 MHz CPU clock.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_EnableMRAM
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_EnableMRAM(CANFD_Type *base, uint32_t channelMask, uint16_t delay)
{
    CY_ASSERT_L2(CY_CANFD_IS_CHS_MASK_VALID(channelMask));

    /* MRAM power on */
    CANFD_CTL(base) = _CLR_SET_FLD32U(CANFD_CTL(base), CANFD_CTL_MRAM_OFF, 0UL);

    /* Wait a certain power up time before MRAM can be used,
     * i.e. before STOP_REQ can be de-asserted (before Clock Stop reset)
     */
    Cy_SysLib_DelayUs(delay);

    /* Reset the Clock Stop request */
    Cy_CANFD_Enable(base, channelMask);
}


/*******************************************************************************
* Function Name: Cy_CANFD_DisableMRAM
****************************************************************************//**
*
*  Disables the channels and switches MRAM off.
*
* \param *base
*     The CAN FD registers structure pointer.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_DisableMRAM
*
*******************************************************************************/
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_DisableMRAM(CANFD_Type *base)
{
    cy_en_canfd_status_t ret = CY_CANFD_ERROR_TIMEOUT;

    /* Request Clock Stop for all channels */
    ret = Cy_CANFD_Disable(base, ((1UL << CY_CANFD_CHANNELS_NUM) - 1UL));

    /* MRAM power down */
    CANFD_CTL(base) = _CLR_SET_FLD32U(CANFD_CTL(base),
                                     CANFD_CTL_MRAM_OFF,
                                     1UL);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_SetBitrate
****************************************************************************//**
*
*  Sets Nominal Bit Timing and Prescaler Register parameters:
*  -Nominal Time segment after sample point;
*  -Nominal Time segment before sample point;
*  -Nominal Baud Rate Prescaler;
*  -Nominal Synchronization Jump Width.
*
* \note Before calling the Cy_CANFD_SetBitrate() function,
*  the Cy_CANFD_ConfigChangesEnable() function must be called to set
*  bits CCCR.CCE and CCCR.INIT. It is recommended to call
*  Cy_CANFD_ConfigChangesDisable() after updating Bitrate.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \param *bitrate \ref cy_stc_canfd_bitrate_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_SetBitrate
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_SetBitrate(CANFD_Type *base, uint32_t chan, const cy_stc_canfd_bitrate_t *bitrate)
{
    if (NULL != bitrate)
    {
        CY_ASSERT_L2(CY_CANFD_IS_NOM_PRESCALER_VALID(bitrate->prescaler));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_TIME_SEG_1_VALID(bitrate->timeSegment1));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_TIME_SEG_2_VALID(bitrate->timeSegment2));
        CY_ASSERT_L2(CY_CANFD_IS_NOM_SYNC_JUMP_WIDTH_VALID(bitrate->syncJumpWidth));

        CANFD_NBTP(base, chan) = _VAL2FLD(CANFD_CH_M_TTCAN_NBTP_NTSEG2, bitrate->timeSegment2) |
                           _VAL2FLD(CANFD_CH_M_TTCAN_NBTP_NTSEG1, bitrate->timeSegment1) |
                           _VAL2FLD(CANFD_CH_M_TTCAN_NBTP_NBRP, bitrate->prescaler)      |
                           _VAL2FLD(CANFD_CH_M_TTCAN_NBTP_NSJW, bitrate->syncJumpWidth);
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_SetFastBitrate
****************************************************************************//**
*
*  Sets Data Bit Timing and Prescaler Register parameters for data:
*  -Data Time segment after sample point;
*  -Data Time segment before sample point;
*  -Data Baud Rate Prescaler;
*  -Data Synchronization Jump Width.
*
* \note Before calling the Cy_CANFD_SetFastBitrate() function,
*  the Cy_CANFD_ConfigChangesEnable() function must be called to set
*  bits CCCR.CCE and CCCR.INIT. It is recommended to call
*  Cy_CANFD_ConfigChangesDisable() after updating Bitrate.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param *fastBitrate \ref cy_stc_canfd_bitrate_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_SetFastBitrate
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_SetFastBitrate(CANFD_Type *base, uint32_t chan, const cy_stc_canfd_bitrate_t *fastBitrate)
{
    uint32_t regValue;

    if (NULL != fastBitrate)
    {
        CY_ASSERT_L2(CY_CANFD_IS_DAT_PRESCALER_VALID(fastBitrate->prescaler));
        CY_ASSERT_L2(CY_CANFD_IS_DAT_TIME_SEG_1_VALID(fastBitrate->timeSegment1));
        CY_ASSERT_L2(CY_CANFD_IS_DAT_TIME_SEG_2_VALID(fastBitrate->timeSegment2));
        CY_ASSERT_L2(CY_CANFD_IS_DAT_SYNC_JUMP_WIDTH_VALID(fastBitrate->syncJumpWidth));

        regValue = CANFD_DBTP(base, chan);  /* Get Data Bit Timing and Prescaler Register */

        regValue &= ~ (CANFD_CH_M_TTCAN_DBTP_DTSEG2_Msk |
                       CANFD_CH_M_TTCAN_DBTP_DTSEG1_Msk |
                       CANFD_CH_M_TTCAN_DBTP_DBRP_Msk   |
                       CANFD_CH_M_TTCAN_DBTP_DSJW_Msk);

        regValue |= _VAL2FLD(CANFD_CH_M_TTCAN_DBTP_DTSEG2, fastBitrate->timeSegment2) |
                    _VAL2FLD(CANFD_CH_M_TTCAN_DBTP_DTSEG1, fastBitrate->timeSegment1) |
                    _VAL2FLD(CANFD_CH_M_TTCAN_DBTP_DBRP, fastBitrate->prescaler)      |
                    _VAL2FLD(CANFD_CH_M_TTCAN_DBTP_DSJW, fastBitrate->syncJumpWidth);

        CANFD_DBTP(base, chan) = regValue; /* Set Data Bit Timing and Prescaler Register */
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_ConfigChangesEnable
****************************************************************************//**
*
*  Enables the CPU write access to the protected configuration registers
*  of the CAN FD block and sets the CAN FD block into the initialization
*  state.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
* The CAN FD channel number.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_ConfigChangesEnable
*
*******************************************************************************/
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_ConfigChangesEnable(CANFD_Type *base, uint32_t chan)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    uint32_t  retry = CY_CANFD_RETRY_COUNT;

    /* Set CCCR_INIT and wait until it is settled */
    CANFD_CCCR(base, chan) = CANFD_CH_M_TTCAN_CCCR_INIT_Msk;

    while ((retry > 0UL) && !_FLD2BOOL(CANFD_CH_M_TTCAN_CCCR_INIT, CANFD_CCCR(base, chan)))
    {
        Cy_SysLib_DelayUs(CY_CANFD_INIT_TIMEOUT_US);
        retry--;
    }

    if (retry > 0UL)
    {
        /* Enable configuration changes by setting the CCE bit */
        CANFD_CCCR(base, chan) |= CANFD_CH_M_TTCAN_CCCR_CCE_Msk;

        ret = CY_CANFD_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_ConfigChangesDisable
****************************************************************************//**
*
*  Disables the CPU write access to the protected configuration registers
*  of the CAN FD block and sets the CAN FD block into the Normal Operation.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \return
* \ref cy_en_canfd_status_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_ConfigChangesDisable
*
*******************************************************************************/
__STATIC_INLINE cy_en_canfd_status_t Cy_CANFD_ConfigChangesDisable(CANFD_Type *base, uint32_t chan)
{
    cy_en_canfd_status_t ret = CY_CANFD_BAD_PARAM;
    uint32_t  retry = CY_CANFD_RETRY_COUNT;

    /* Clear CCCR_INIT bit and wait until it is updated to finalize CAN FD initialization */
    CANFD_CCCR(base, chan) &= (uint32_t) ~CANFD_CH_M_TTCAN_CCCR_INIT_Msk;

    while ((retry > 0UL) && _FLD2BOOL(CANFD_CH_M_TTCAN_CCCR_INIT, CANFD_CCCR(base, chan)))
    {
        Cy_SysLib_DelayUs(CY_CANFD_INIT_TIMEOUT_US);
        retry--;
    }

    if (retry > 0UL)
    {
        ret = CY_CANFD_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_CANFD_TestModeConfig
****************************************************************************//**
*
*  Configures test mode.
*
* \note The \ref Cy_CANFD_ConfigChangesEnable must be called before calling
*  this function to enable the configuration changes.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param testMode \ref cy_stc_canfd_test_mode_t
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_TestModeConfig
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_TestModeConfig(CANFD_Type *base, uint32_t chan, cy_stc_canfd_test_mode_t testMode)
{
    switch (testMode)
    {
        case CY_CANFD_TEST_MODE_DISABLE:
            CANFD_CCCR(base, chan) &= (uint32_t) ~(CANFD_CH_M_TTCAN_CCCR_TEST_Msk | /* Disable Test Mode */
                                            CANFD_CH_M_TTCAN_CCCR_MON__Msk);  /* Disable Bus Monitoring Mode */
            CANFD_TEST(base, chan) &= (uint32_t) ~CANFD_CH_M_TTCAN_TEST_LBCK_Msk;   /* Disable Loop Back Mode */
            break;
        case CY_CANFD_TEST_MODE_BUS_MONITORING:
            CANFD_CCCR(base, chan) |= (CANFD_CH_M_TTCAN_CCCR_MON__Msk);  /* Enable Bus Monitoring Mode */
            break;
        case CY_CANFD_TEST_MODE_EXTERNAL_LOOP_BACK:
            CANFD_CCCR(base, chan) |= CANFD_CH_M_TTCAN_CCCR_TEST_Msk;  /* Enable Test Mode */
            CANFD_TEST(base, chan) |= CANFD_CH_M_TTCAN_TEST_LBCK_Msk;  /* Enable Loop Back Mode */
            break;
        case CY_CANFD_TEST_MODE_INTERNAL_LOOP_BACK:
            CANFD_CCCR(base, chan) |= (CANFD_CH_M_TTCAN_CCCR_TEST_Msk |  /* Enable Test Mode */
                                 CANFD_CH_M_TTCAN_CCCR_MON__Msk);  /* Enable Bus Monitoring Mode */
            CANFD_TEST(base, chan) |= CANFD_CH_M_TTCAN_TEST_LBCK_Msk;  /* Enable Loop Back Mode */
            break;
        default:
            /* Unsupported test mode */
            break;
    }
}


/*******************************************************************************
* Function Name: Cy_CANFD_SetTDC
****************************************************************************//**
*
* Sets the CAN FD transceiver delay compensation offset.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*  The CAN FD channel number.
*
* \param *tdcConfig
*  The CAN FD transceiver delay compensation offset configuration.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_SetTDC(CANFD_Type *base, uint32_t chan,
                                     const  cy_stc_canfd_transceiver_delay_compensation_t *tdcConfig)
{
    if (NULL != tdcConfig)
    {
        CY_ASSERT_L2(CY_CANFD_IS_TDCO_VALID(tdcConfig->tdcOffset));
        CY_ASSERT_L2(CY_CANFD_IS_TDCF_VALID(tdcConfig->tdcFilterWindow));

        /* Transceiver Delay Compensation is enabled or disabled */
        CANFD_DBTP(base, chan) = _CLR_SET_FLD32U(CANFD_DBTP(base, chan),
                                         CANFD_CH_M_TTCAN_DBTP_TDC,
                                         ((tdcConfig->tdcEnabled) ? 1UL : 0UL));

        /* Transmitter Delay Compensation Offset and Filter Window Length */
        CANFD_TDCR(base, chan) = _VAL2FLD(CANFD_CH_M_TTCAN_TDCR_TDCO, tdcConfig->tdcOffset) |
                           _VAL2FLD(CANFD_CH_M_TTCAN_TDCR_TDCF, tdcConfig->tdcFilterWindow);
    }
}

/** \} group_canfd_functions */

/**
* \addtogroup group_canfd_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_CANFD_GetInterruptStatus
****************************************************************************//**
*
*  Returns a status of CAN FD interrupt requests.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \return uint32_t
*     The bit mask of the Interrupt Status.
* Valid masks can be found in
* \ref group_canfd_rx_interrupt_masks, \ref group_canfd_tx_interrupt_masks and
* \ref group_canfd_error_interrupt_masks.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetInterruptStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_CANFD_GetInterruptStatus(CANFD_Type const *base, uint32_t chan)
{
    return CANFD_IR(base, chan);
}


/*******************************************************************************
* Function Name: Cy_CANFD_ClearInterrupt
****************************************************************************//**
*
*  Clears CAN FD interrupts by setting each bit.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param status
*     The bitmask of statuses to clear.
* Valid masks can be found in
* \ref group_canfd_rx_interrupt_masks, \ref group_canfd_tx_interrupt_masks and
* \ref group_canfd_error_interrupt_masks.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_ClearInterrupt
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_ClearInterrupt(CANFD_Type *base, uint32_t chan, uint32_t status)
{
    CANFD_IR(base, chan) = status;
}


/*******************************************************************************
* Function Name: Cy_CANFD_GetInterruptMask
****************************************************************************//**
*
*  Returns an interrupt mask.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \return uint32_t
*     The bit field determines which status changes can cause an interrupt.
* Valid masks can be found in
* \ref group_canfd_rx_interrupt_masks, \ref group_canfd_tx_interrupt_masks and
* \ref group_canfd_error_interrupt_masks.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetInterruptMask
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_CANFD_GetInterruptMask(CANFD_Type const *base, uint32_t chan)
{
    return CANFD_IE(base, chan);
}


/*******************************************************************************
* Function Name: Cy_CANFD_SetInterruptMask
****************************************************************************//**
*
*  Configures which bits of the interrupt request register can trigger an
*  interrupt event.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param interrupt
*     The bit field determines which status changes can cause an interrupt.
* Valid masks can be found in
* \ref group_canfd_rx_interrupt_masks, \ref group_canfd_tx_interrupt_masks and
* \ref group_canfd_error_interrupt_masks.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_SetInterruptMask
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_SetInterruptMask(CANFD_Type *base, uint32_t chan, uint32_t interrupt)
{
    CANFD_IE(base, chan) = interrupt;
}


/*******************************************************************************
* Function Name: Cy_CANFD_GetInterruptLine
****************************************************************************//**
*
*  Returns the interrupt signals assigned to the line m_ttcan_int0
* or m_ttcan_int1.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \return uint32_t
*     The mask where 1 corresponds to the interrupt signals assigned
*     to the line m_ttcan_int1 and 0 corresponds to m_ttcan_int0.
* Valid masks can be found in
* \ref group_canfd_rx_interrupt_masks, \ref group_canfd_tx_interrupt_masks and
* \ref group_canfd_error_interrupt_masks.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_GetInterruptLine
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_CANFD_GetInterruptLine(CANFD_Type const *base, uint32_t chan)
{
    return CANFD_ILS(base, chan);
}


/*******************************************************************************
* Function Name: Cy_CANFD_SetInterruptLine
****************************************************************************//**
*
*  Configures the bits of the Interrupt Line Select Register to assign the
*  interrupt signal to the line m_ttcan_int0 or m_ttcan_int1.
*  Bit = 0: The interrupt assigned to the interrupt line m_ttcan_int0,
*  bit = 1: The interrupt assigned to the interrupt line m_ttcan_int1.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param interruptLineMask
*     The mask where 1 corresponds to the interrupt signals assigned
*     to the line m_ttcan_int1 and 0 corresponds to m_ttcan_int0.
* Valid masks can be found in
* \ref group_canfd_rx_interrupt_masks, \ref group_canfd_tx_interrupt_masks and
* \ref group_canfd_error_interrupt_masks.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_SetInterruptLine
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_SetInterruptLine(CANFD_Type *base, uint32_t chan, uint32_t interruptLineMask)
{
    CANFD_ILS(base, chan) = interruptLineMask;
}


/*******************************************************************************
* Function Name: Cy_CANFD_IsInterruptLineEnabled
****************************************************************************//**
*
*  Checks whether Interrupt Line 0, Interrupt Line 1 or both are enabled.
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param interruptLineMask
*    The bit mask to check which interrupt line is enabled.
*    Can be CY_CANFD_INTERRUPT_LINE_0_EN, CY_CANFD_INTERRUPT_LINE_1_EN or
*    (CY_CANFD_INTERRUPT_LINE_0_EN | CY_CANFD_INTERRUPT_LINE_1_EN)
*
* \return bool
*     The bit mask of the enabled interrupt lines.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_IsInterruptLineEnabled
*
*******************************************************************************/
__STATIC_INLINE bool Cy_CANFD_IsInterruptLineEnabled(CANFD_Type const *base, uint32_t chan,
                                                     uint32_t interruptLineMask)
{
    return (interruptLineMask == (CANFD_ILE(base, chan) & interruptLineMask));
}


/*******************************************************************************
* Function Name: Cy_CANFD_EnableInterruptLine
****************************************************************************//**
*
*  Configures which interrupt line is enabled (Interrupt Line 0, Interrupt Line 1 or both).
*
* \param *base
* The pointer to a CAN FD instance.
*
* \param chan
*     The CAN FD channel number.
*
* \param interruptLineMask
*    The bit mask whose bits define interrupt lines to enable or disable.
*
* \funcusage
* \snippet canfd/snippet/main.c snippet_Cy_CANFD_EnableInterruptLine
*
*******************************************************************************/
__STATIC_INLINE void Cy_CANFD_EnableInterruptLine(CANFD_Type *base, uint32_t chan, uint32_t interruptLineMask)
{
    CY_ASSERT_L2(CY_CANFD_IS_ILE_MASK_VALID(interruptLineMask));

    CANFD_ILE(base, chan) = interruptLineMask;
}

/** \} group_canfd_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTTCANFD */

#endif /* CY_CANFD_H */

/** \} group_canfd */

/* [] END OF FILE */
