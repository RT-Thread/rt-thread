/***************************************************************************//**
* \file cy_sd_host.h
* \version 2.1
*
*  This file provides constants and parameter values for
*  the SD Host Controller driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation
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
* \addtogroup group_sd_host
* \{
* This driver provides the user an easy method for accessing standard
* Host Controller Interface (HCI) registers and provides some simple
* functionality on top of the HCI for reading and writing data to
* an SD card, eMMc card or a SDIO device.
*
* The functions and other declarations used in this driver are in cy_sd_host.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* Features:
* * Supports data transfer using CPU, SDMA, ADMA2 and ADMA3 modes
* * Supports a configurable block size (1 to 65,535 Bytes)
* * Supports interrupt enabling and masking
* * Supports SD-HCI Host version 4 mode or less
* * Compliant with the SD 6.0, SDIO 4.10 and eMMC 5.1 specifications and earlier versions
* * SD interface features:
* * - Supports the 4-bit interface
* * - Supports Ultra High Speed (UHS-I) mode
* * - Supports Default Speed (DS), High Speed (HS), SDR12, SDR25, SDR50, and DDR50 speed modes
* * - Supports SDIO card interrupts in both 1-bit and 4-bit modes
* * - Supports Standard capacity (SDSC), High capacity (SDHC)
* and Extended capacity (SDXC) memory
* * - Supports CRC and check for command and data packets
* * - Supports packet timeouts
* * - Handles the SDIO card interrupt
* * eMMC interface features:
* * - Supports 1-bit/4-bit/8-bit interfaces
* * - Supports legacy and High Speed SDR speed modes
* * - Supports CRC and check for command and data packets
* * - Supports packet timeouts
*
* Unsupported Features:
* * Wrap address transfers
* * eMMC boot operation
* * Suspend/Resume operation in an SDIO card
* * Operation in SDR104, UHS-II mode, HS200, and HS400
* * Serial Peripheral Interface (SPI) protocol mode
* * Interrupt input pins for the embedded SD system
* * Auto-tuning
* * Command queuing
*
* The SD, eMMC, and SDIO cards have the similar physical interface:
* clock, command line, and data lines.
* The SD card is removable and requires the SD card connector to connect
* to the PSoC device. This connector also has the card_mech_write_prot switch
* for mechanical write protection and the card_detect_n switch for card detection.
* The eMMC card also has DAT4-DAT7 pins for 8-bit mode and the EMMC_RESET pin.
* \image html sd_card_connector.png
* The driver has a low-level and high-level APIs.
* The low-level functions provide an easy method to read and write registers.
* Also, these functions allow valid interaction with an SD Card, eMMC card,
* and SDIO card.
* The high-level functions provide an easy mechanism to enumerate a device,
* read, write, and erase data. They are RTOS-friendly.
* When starting a command, these functions do not wait until the command completes.
* The interrupt and flags are used to check when the transfer completes.
* This allows to put RTOS delays in the user code.
*
* \section group_sd_host_section_Configuration_Considerations Configuration Considerations
* The SD Host driver configuration can be divided to a number of sequential
* steps listed below:
* * \ref group_sd_host_enable
* * \ref group_sd_host_pins
* * \ref group_sd_host_clock
* * \ref group_sd_host_intr
* * \ref group_sd_host_config
* * \ref group_sd_host_card_init
*
* \note
* The SD Host driver is built on top of the SDHC hardware block. The SDHC1 instance is
* used as an example for all code snippets. Modify the code to match your
* design.
*
* \subsection group_sd_host_enable Enable SD Host
* Enable the SDHC block calling \ref Cy_SD_Host_Enable.
*
* \subsection group_sd_host_pins Assign and Configure Pins
* Only dedicated SD Host pins can be used for SD Host operation. The HSIOM
* register must be configured to connect the block to the pins. Also, the SD Host
* pins must be configured in Strong Drive, Input buffer on:
*
* \snippet sd_host/snippet/main.c SD_HOST_CFG_PINS
*
* \subsection group_sd_host_clock Assign Clock Source
* The SD Host is sourced from the CLK_HF clock. The clock must be set to 100 MHz:
*
* \snippet sd_host/snippet/main.c SD_HOST_CFG_ASSIGN_CLOCK
*
* \subsection group_sd_host_intr Configure Interrupt (Optional)
* The user can set up the interrupt for SD Host operation.
* The user is responsible for writing its own Interrupt handler.
* The Interrupt must be called in the interrupt handler for the selected SDHC
* instance. Also this interrupt must be enabled in the NVIC otherwise
* it will not work.
* It is the user's responsibility to clear the normal and error interrupt statuses.
* The interrupt statuses can be read using \ref Cy_SD_Host_GetNormalInterruptStatus
* and \ref Cy_SD_Host_GetErrorInterruptStatus.
* To clear the interrupt statuses, use \ref Cy_SD_Host_ClearNormalInterruptStatus
* and \ref Cy_SD_Host_ClearErrorInterruptStatus.
*
* \snippet sd_host/snippet/main.c SD_HOST_INTR_A
* \snippet sd_host/snippet/main.c SD_HOST_INTR_B
*
* \subsection group_sd_host_config Configure SD Host
* To set up the SD Host driver, provide the configuration parameters in the
* \ref cy_stc_sd_host_init_config_t structure. Set the emmc parameter to true for
* the eMMC-device, otherwise set it to false. Set dmaType if DMA mode
* is used for read/write operations. The other parameters are optional for
* operation. To initialize the driver, call the \ref Cy_SD_Host_Init
* function providing a pointer to the filled \ref cy_stc_sd_host_init_config_t
* structure and allocated \ref cy_stc_sd_host_context_t.
*
* \snippet sd_host/snippet/main.c SD_HOST_CONTEXT
* \snippet sd_host/snippet/main.c SD_HOST_CFG
*
* The SD, eMMC or SDIO card can be configured using the \ref Cy_SD_Host_InitCard
* function as a pointer to the filled \ref cy_stc_sd_host_sd_card_config_t
* structure and allocated \ref cy_stc_sd_host_context_t.
*
* \subsection group_sd_host_card_init Initialize the card
* Finally, enable the card operation calling
* \ref Cy_SD_Host_InitCard.
*
* \snippet sd_host/snippet/main.c SD_HOST_ENABLE_CARD_INIT
*
* \section group_sd_host_use_cases Common Use Cases
*
* \subsection group_sd_host_sd_card_mode SD card Operation
* The master API is divided into two categories:
* \ref group_sd_host_high_level_functions and
* \ref group_sd_host_low_level_functions. Therefore, there are two
* methods for initiating SD card transactions using either <b>Low-Level</b> or
* <b>High-Level</b> API.
*
* \subsubsection group_sd_host_master_hl Use High-Level Functions
* Call \ref Cy_SD_Host_Read or \ref Cy_SD_Host_Write to
* communicate with the SD memory device. These functions do not block
* in DMA mode and only start a transaction. After a transaction starts,
* the user should check the further data-transaction complete event.
* The example below shows sending and reading data in DMA mode.
*
* \snippet sd_host/snippet/main.c SD_HOST_WRITE_READ_ADMA2
*
* \subsubsection group_sd_host_master_ll Use Low-Level Functions
* Call \ref Cy_SD_Host_InitDataTransfer to initialize the SD block
* for a data transfer. It does not start a transfer. To start a transfer
* call \ref Cy_SD_Host_SendCommand after calling this function.
* If DMA is not used for Data transfer then the buffer needs to be filled
* with data first if this is a write.
* Wait the transfer complete event.
* ADMA3 mode requires calling \ref Cy_SD_Host_InitDataTransfer to
* initialize the DMA transaction. The ADMA3 mode example is shown below.
*
* \snippet sd_host/snippet/main.c SD_HOST_WRITE_READ_ADMA3
*
* \subsection group_sd_host_emmc_card_mode eMMC Card Operation
* eMMC cards use the same API for writing and reading data.
* Additionally, eMMC requires configuring GPIO pins for DAT signals
* in 8-bit mode and card_emmc_reset_n pin if needed.
* The emmc member of \ref cy_stc_sd_host_init_config_t structure must
* be set to "true".
*
* \subsection group_sd_host_sdio_combo_card_mode eMMC SDIO or Combo Card Operation
* \ref Cy_SD_Host_InitCard() initializes all types of cards and
* automatically detects the card type: SD, SDIO or Combo card.
* SDIO cards have their input-output (I/O) functions that can be
* controlled using the GPIO driver.
* Combo Cards can use both I/O and memory API.
*
* \section group_sd_host_lp Low Power Support
* The SD Host does not operate in Hibernate and Deep Sleep modes but it
* can automatically continue write/read operation after restoring from
* Deep Sleep mode. SD CLK must be disabled before going to Deep Sleep mode
* and can be enabled after wake up from Deep Sleep mode.
* To reduce the power consumption in Active mode, the user can stop
* the clock of the SD bus but the following interrupts can be allowed:
* Card Insert, Card Removal and SDIO Interrupt.
*
* \section group_sd_host_remove_insert SD Card Removal and Insertion
* SD card removal or insertion can be detected by calling
* \ref Cy_SD_Host_GetNormalInterruptStatus which returns
* the card removal or card insertion events
* (CY_SD_HOST_CARD_REMOVAL or CY_SD_HOST_CARD_INSERTION bits).
* These events should be reset using
* \ref Cy_SD_Host_ClearNormalInterruptStatus when they occur.
* When the card is removed, the SDHC block disables the CMD/DAT output.
* It is recommended to set DAT pins to
* the Digital High-Z (CY_GPIO_DM_HIGHZ) drive mode when
* card removal is detected. This can be doing using the GPIO driver.
* When the card is inserted, the SDHC block automatically disables
* the card power and clock. After card insertion,
* the user should set the DAT pins drive mode back to Strong Drive,
* Input buffer on (CY_GPIO_DM_STRONG), and then call \ref Cy_SD_Host_InitCard.
* \note If CARD_INTERRUPT is enabled and DAT pins are not set to
* Digital High-Z drive mode then the interrupt will continuously
* trigger because the DAT1 line is driven low upon card re-insertion.
* The user will have to detect the card removal in the ISR handler,
* apply the power to the card using \ref Cy_SD_Host_EnableCardVoltage,
* set to the DAT pins drive mode to the Digital High-Z (CY_GPIO_DM_HIGHZ)
* and clear CY_SD_HOST_CARD_INTERRUPT bit
* using \ref Cy_SD_Host_ClearNormalInterruptStatus.
*
* \section group_sd_host_low_voltage_signaling Low Voltage Signaling
* When lowVoltageSignaling is true, the SD Host driver sets UHS-I mode
* during the card initialization. The SD Host driver always starts talking
* to the card at 3.3V and then later switches to 1.8V. There is no internal
* regulator in the PSoC 6 to change SD signals from 3.3V to 1.8V.
* Thus, an external regulator is needed for the VDDIO of the PSoC device
* to provide the ability to go from 3.3V to 1.8V.
* The SD Host driver sets the io_volt_sel pin to high which is used to
* control the external regulator.
* \image html sd_host_low_voltage_signaling.png
*
* \section group_sd_host_more_information More Information
*
* Refer to the appropriate device technical reference manual (TRM) for
* a detailed description of the registers.
*
* \section group_sd_host_Changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td> 2.1</td>
*     <td>Updated the behaviour of \ref Cy_SD_Host_AbortTransfer function to check the R1B response. Minor documentation updates.</td>
*     <td>Defect fixing. Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td> 2.0</td>
*     <td>Added support for DDR50 mode and modified Cy_SD_Host_InitCard() API
*         to set highest possible bus speed mode. Minor documentation updates.</td>
*     <td>New feature implementation and documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td> 1.90</td>
*     <td>Fixed the Cy_SD_Host_SoftwareReset() function behaviour.
*         Now it waits until corresponding reset bit gets cleared by SDHC IP block.</td>
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td> 1.80</td>
*     <td>Added an internal function.</td>
*     <td>Code efficiency enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.70</td>
*     <td>Allow SDIO Card initialization through Cy_SD_Host_InitCard() API.
*         Added new API Cy_SD_Host_GetBlockCount().
*     </td>
*     <td>Code enhancement, minor defect fixing.</td>
*   </tr>
*   <tr>
*     <td>1.60</td>
*     <td>Fixed/Documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.50.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>The default value of the SD-clock rump-up time during a wakeup
*         from Deep Sleep is reduced to 1 us, for details,
*         see \ref Cy_SD_Host_DeepSleepCallback description.</td>
*     <td>Optimization for cases of specific wakeup timing requirements.</td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>Added a possibility to
*         customize the SD-clock rump-up time during a wakeup from Deep Sleep,
*         for details, see \ref Cy_SD_Host_DeepSleepCallback description.</td>
*     <td>Workaround for cases of specific wakeup timing requirements.</td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>The internal function implementation is changed.</td>
*     <td>Code efficiency enhancement, minor defect fixing.</td>
*   </tr>
*   <tr>
*     <td rowspan="2"> 1.20</td>
*     <td>Added the Cy_SD_Host_DeepSleepCallback() function.</td>
*     <td>Driver maintenance.</td>
*   </tr>
*   <tr>
*     <td>Fixed the Cy_SD_Host_GetCsd() function behaviour.
*         Now the cy_stc_sd_host_context_t::maxSectorNum is being updated correctly</td>
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td> 1.10.1</td>
*     <td>Documentation of the MISRA rule violation.</td>
*     <td>MISRA compliance.</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>The PLL and CLK disable sequence in \ref Cy_SD_Host_DisableSdClk()
*         is changed to disable CLK first.<br>
*         The Low-Power Support section is updated with additional
*         information about disabling CLK.<br>
*         The context initialization in \ref Cy_SD_Host_Init() is corrected.<br>
*         Updated the Write/Read sequence in \ref Cy_SD_Host_Read() and
*         \ref Cy_SD_Host_Write()functions for non DMA mode.<br>
*     </td>
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>The initial version.</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sd_host_macros Macros
* \{
* \defgroup group_sd_host_macros_general_purpose General Purpose Macros
* \defgroup group_sd_host_macros_card_states Card States
* \{
* The masks below can be used to check the CURRENT_STATE bitfield
* of the \ref Cy_SD_Host_GetCardStatus function return value.
* \}
* \defgroup group_sd_host_macros_card_status Card Status (CMD13) Bits
* \{
* The masks below can be used with the
* \ref Cy_SD_Host_GetCardStatus function.
* \}
* \defgroup group_sd_host_macros_scr SCR Register Masks
* \{
* The masks below can be used with the
* \ref Cy_SD_Host_GetScr function.
* \}
* \defgroup group_sd_host_macros_cid CID Register Masks
* \{
* The masks below can be used with the
* \ref Cy_SD_Host_GetCid function.
* \}
* \defgroup group_sd_host_macros_csd CSD Register Masks
* \{
* The masks below are for CSD Register Version 2.0 and can be
* used with the \ref Cy_SD_Host_GetCsd function.
* \}
* \defgroup group_sd_host_macros_events SD Host Events
* \{
* The constants below can be used with
* \ref Cy_SD_Host_GetNormalInterruptStatus,
* \ref Cy_SD_Host_ClearNormalInterruptStatus,
* \ref Cy_SD_Host_GetErrorInterruptStatus and
* \ref Cy_SD_Host_ClearErrorInterruptStatus functions.
* Each event is encoded in a separate bit, and therefore it is possible to
* notify about multiple events.
* \}
* \defgroup group_sd_host_macros_present_status SD Host Present Status
* \{
* The constants below can be used with the
* \ref Cy_SD_Host_GetPresentState function.
* Each status is encoded in a separate bit, and therefore it is possible to
* notify about multiple statuses.
* \}
* \}
* \defgroup group_sd_host_functions Functions
* \{
* \defgroup group_sd_host_high_level_functions High-Level
* \defgroup group_sd_host_low_level_functions Low-Level
* \defgroup group_sd_host_interrupt_functions Interrupt
* \}
* \defgroup group_sd_host_data_structures Data Structures
* \defgroup group_sd_host_enums Enumerated Types
*/

#ifndef CY_SD_HOST_PDL_H
#define CY_SD_HOST_PDL_H

#include "cy_device.h"

#if defined (CY_IP_MXSDHC)

#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

#if defined (__CC_ARM)
    #pragma anon_unions
#endif

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
* \addtogroup group_sd_host_macros_general_purpose
* \{
*/

/** Driver major version */
#define CY_SD_HOST_DRV_VERSION_MAJOR       2

/** Driver minor version */
#define CY_SD_HOST_DRV_VERSION_MINOR       1

/******************************************************************************
* API Constants
******************************************************************************/

#define CY_SD_HOST_ID                       CY_PDL_DRV_ID(0x3AU) /**< SD_HOST PDL ID */

#define CY_SD_HOST_BLOCK_SIZE               (512UL) /**< The SD memory card block size. */

#define CY_SD_HOST_SDSC_ADDR_SHIFT          (9U)    /**< This constant is used to get the
                                                      * address for the SDSC card using the
                                                      * shift operation instead of multiply to 512.
                                                      */

/* SD output clock. */
#define CY_SD_HOST_CLK_25M                  (25UL * 1000UL * 1000UL) /**< Clk = 25 MHz. */
#define CY_SD_HOST_CLK_50M                  (50UL * 1000UL * 1000UL) /**< Clk = 50 MHz. */
#define CY_SD_HOST_CLK_100M                 (100UL * 1000UL * 1000UL) /**< Clk = 100 MHz. */

#define CY_SD_HOST_CLK_RAMP_UP_TIME_MS      (100UL)  /**< The host power ramp up time. */

#ifndef CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP  /* Define of the CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP
                                                * suppresses CY_SD_HOST_CLK_RAMP_UP_TIME_MS_WAKEUP
                                                */
#ifndef CY_SD_HOST_CLK_RAMP_UP_TIME_MS_WAKEUP   /*
                                                 * This is legacy constant.
                                                 * It is left here just for backward compatibility.
                                                 * Do not use it in new designs.
                                                 */
#define CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP (1U) /**< The default host power ramp up time during wake up from deep sleep. */
#else
#define CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP (CY_SD_HOST_CLK_RAMP_UP_TIME_MS_WAKEUP * 1000U)
#endif /* !defined CY_SD_HOST_CLK_RAMP_UP_TIME_MS_WAKEUP */
#endif /* !defined CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP */

/* ADMA constants. */
#define CY_SD_HOST_ADMA_NOP                 (0x0UL) /**< Does not execute the current line and go to next line. */
#define CY_SD_HOST_ADMA_RSV                 (0x2UL) /**< Reserved. */
#define CY_SD_HOST_ADMA_TRAN                (0x4UL) /**< Transfers data of one descriptor line. */
#define CY_SD_HOST_ADMA_LINK                (0x6UL) /**< The link to another descriptor. */
#define CY_SD_HOST_ADMA3_CMD                (0x1UL) /**< The Command descriptor. */
#define CY_SD_HOST_ADMA3_INTERGRATED        (0x7UL) /**< The Integrated descriptor. */
#define CY_SD_HOST_ADMA2_DESCR_SIZE         (0x2UL) /**< The ADMA2 descriptor size. */

/* ADMA descriptor table positions. */
#define CY_SD_HOST_ADMA_ATTR_VALID_POS      (0U) /**< The ADMA Attr Valid position. */
#define CY_SD_HOST_ADMA_ATTR_END_POS        (1U) /**< The ADMA Attr End position. */
#define CY_SD_HOST_ADMA_ATTR_INT_POS        (2U) /**< The ADMA Attr Int position. */
#define CY_SD_HOST_ADMA_ACT_POS             (3U) /**< The ADMA Act position. */
#define CY_SD_HOST_ADMA_RESERVED2_POS       (6U) /**< The ADMA Reserved2 position. */
#define CY_SD_HOST_ADMA_LEN_POS             (16U) /**< The ADMA Len position. */

/** \cond INTERNAL_MACROS */

#define CY_SD_HOST_EMMC_T_RSTW_US           (1U)
#define CY_SD_HOST_EMMC_T_RSCA_US           (200U)
#define CY_SD_HOST_INIT_CLK_FREQUENCY_KHZ   (400U)  /* The CLK frequency in kHz during card initialization. */
#define CY_SD_HOST_3_PERIODS_US             (((1000U * 3U) / CY_SD_HOST_INIT_CLK_FREQUENCY_KHZ) + 1U)

/** \endcond */

/** \} group_sd_host_macros_general_purpose */

/**
* \addtogroup group_sd_host_macros_card_states
* \{
*/

#define CY_SD_HOST_CARD_IDLE                (0x0UL)  /**< The card idle state. */
#define CY_SD_HOST_CARD_READY               (0x1UL)  /**< The card ready state. */
#define CY_SD_HOST_CARD_IDENT               (0x2UL)  /**< The card identification state. */
#define CY_SD_HOST_CARD_STBY                (0x3UL)  /**< The card stand-by state. */
#define CY_SD_HOST_CARD_TRAN                (0x4UL)  /**< The card transition state. */
#define CY_SD_HOST_CARD_DATA                (0x5UL)  /**< The card sending-data state. */
#define CY_SD_HOST_CARD_RCV                 (0x6UL)  /**< The card receive-data state. */
#define CY_SD_HOST_CARD_PRG                 (0x7UL)  /**< The card programming state. */
#define CY_SD_HOST_CARD_DIS                 (0x8UL)  /**< The card disconnect state. */

/** \} group_sd_host_macros_card_states */

/**
* \addtogroup group_sd_host_macros_card_status
* \{
*/

#define CY_SD_HOST_CMD13_OUT_OF_RANGE       (31U) /**< The command's argument is out of range. */
#define CY_SD_HOST_CMD13_ADDRESS_ERROR      (30U) /**< The address does not match the block length. */
#define CY_SD_HOST_CMD13_BLOCK_LEN_ERROR    (29U) /**< The block length is not allowed for this card. */
#define CY_SD_HOST_CMD13_ERASE_SEQ_ERROR    (28U) /**< An error in the sequence of erase commands occurred. */
#define CY_SD_HOST_CMD13_ERASE_PARAM        (27U) /**< An invalid selection of write blocks for erase occurred. */
#define CY_SD_HOST_CMD13_WP_VIOLATION       (26U) /**< The host attempts to write to a protected block
                                                    * or to the permanent write-protected card.
                                                    */
#define CY_SD_HOST_CMD13_CARD_IS_LOCKED     (25U) /**< The card is locked by the host. */
#define CY_SD_HOST_CMD13_LOCK_ULOCK_FAILED  (24U) /**< A sequence or password error occurred
                                                    * has been detected in the lock/unlock card command.
                                                    */
#define CY_SD_HOST_CMD13_COM_CRC_ERROR      (23U) /**< The CRC of the previous command failed. */
#define CY_SD_HOST_CMD13_ILLEGAL_COMMAND    (22U) /**< The command is not legal for the card state. */
#define CY_SD_HOST_CMD13_CARD_ECC_FAILED    (21U) /**< The card internal ECC failed. */
#define CY_SD_HOST_CMD13_CC_ERROR           (20U) /**< An internal card-controller error. */
#define CY_SD_HOST_CMD13_ERROR              (19U) /**< A general or unknown error occurred. */
#define CY_SD_HOST_CMD13_CSD_OVERWRITE      (16U) /**< Can be either one of the following
                                                    * errors:
                                                    * - The read only section of the CSD
                                                    * does not match the card content.
                                                    * - An attempt to reverse the copy (set
                                                    * as original) or permanent WP
                                                    * (unprotected) bits was made.
                                                    */
#define CY_SD_HOST_CMD13_WP_ERASE_SKIP      (15U) /**< Set when only partial address space
                                                    * was erased due to existing write protected blocks
                                                    * or a temporary or permanent write protected
                                                    * card was erased.
                                                    */
#define CY_SD_HOST_CMD13_CARD_ECC_DISABLED  (14U) /**< The command has been executed
                                                    * without using the internal ECC.
                                                    */
#define CY_SD_HOST_CMD13_CURRENT_STATE      (9U)  /**< The state of the card. */
#define CY_SD_HOST_CMD13_READY_FOR_DATA     (8U)  /**< The buffer is empty on the bus. */
#define CY_SD_HOST_CMD13_APP_CMD            (5U)  /**< The card will expect ACMD, or an
                                                    * indication that the command has
                                                    * been interpreted as ACMD.
                                                    */
#define CY_SD_HOST_CMD13_AKE_SEQ_ERROR      (3U)  /**< Error in the sequence of the
                                                    * authentication process.
                                                    */

#define CY_SD_HOST_CMD13_CURRENT_STATE_MSK  (0x00001E00UL) /**< The current state mask of the card. */

/** \} group_sd_host_macros_card_status */

/**
* \addtogroup group_sd_host_macros_scr
* \{
*/

#define CY_SD_HOST_SCR_SCR_STRUCTURE        (0x000000F0UL)  /**< Version number of the related SCR structure
                                                              * in the SD Memory Card Physical Layer Specification.
                                                              */

#define CY_SD_HOST_SCR_SD_SPEC              (0x0000000FUL)  /**< Describes the SD Memory Card Physical Layer
                                                              * Specification version supported by this card.
                                                              */

#define CY_SD_HOST_SCR_DATA_STAT_AFTER_ERASE (0x00008000UL)  /**< Defines the data status after erase,
                                                               * whether it is '0' or '1' (the status is
                                                               * card vendor dependent).
                                                               */

#define CY_SD_HOST_SCR_SD_SECURITY          (0x00007000UL)  /**< Describes the security algorithm
                                                              * supported by the card.
                                                              */

#define CY_SD_HOST_SCR_SD_BUS_WIDTHS        (0x00000F00UL)  /**< Describes all the DAT bus widths that
                                                              * are supported by this card.
                                                              */

/** \} group_sd_host_macros_scr */

/**
* \addtogroup group_sd_host_macros_cid
* \{
*/

#define CY_SD_HOST_SCR_CID_MDT              (0x00000FFFUL)  /**< The manufacturing date is composed of
                                                              * two hexadecimal digits (contained in cid[0]),
                                                              * one is 8 bits representing the year(y) and the
                                                              * other is 4 bits representing the month (m).
                                                              * The "m" field [11:8] is the month code. 1 = January.
                                                              * The "y" field [19:12] is the year code. 0 = 2000.
                                                              * As an example, the binary value of the Date field
                                                              * for production date "April 2018" will be:
                                                              * 00010010 0100.
                                                              */

#define CY_SD_HOST_SCR_CID_PSN_LSB          (0xFFFF0000UL)  /**< The mask for LSB part of the Serial Number
                                                              * (contained in cid[0]). The Serial Number is
                                                              * 32 bits of binary number.
                                                              */

#define CY_SD_HOST_SCR_CID_PSN_MSB          (0x0000FFFFUL)  /**< The mask for MSB part of the Serial Number
                                                              * (contained in cid[1]). The Serial Number is
                                                              * 32 bits of binary number.
                                                              */

#define CY_SD_HOST_SCR_CID_PRV              (0x00FF0000UL)  /**< The product revision is composed of two
                                                              * Binary Coded Decimal (BCD) digits (contained in cid[1]),
                                                              * four bits each, representing an "n.m" revision number.
                                                              * The "n" is the most significant nibble and "m" is the
                                                              * least significant nibble.
                                                              * As an example, the PRV binary value field for product
                                                              * revision "6.2" will be: 0110 0010b.
                                                              */

#define CY_SD_HOST_SCR_CID_PNM_LSB          (0xFF000000UL)  /**< The mask for LSB part (the first 8 bits) of the
                                                              * product name (contained in cid[1]). The product
                                                              * name is a string, 5-character ASCII string.
                                                              * As an example, the PNM hex value field for product name
                                                              * "EB1QT" will be: 0x4542315154.
                                                              */

#define CY_SD_HOST_SCR_CID_PNM_MSB          (0xFFFFFFFFUL)  /**< The mask for MSB part (the last 32 bits) of the
                                                              * product name (contained in cid[2]). The product
                                                              * name is a string, 5-character ASCII string.
                                                              * As an example, the PNM hex value field for product name
                                                              * "EB1QT" will be: 0x4542315154.
                                                              */

#define CY_SD_HOST_SCR_CID_OID              (0x0000FFFFUL)  /**< The mask for the OID (contained in cid[3]).
                                                              * The OID is a 2-character ASCII string that
                                                              * identifies the card OEM and/or the card contents
                                                              * (when used as a distribution media either on ROM or
                                                              * FLASH cards). The OID number is controlled, defined,
                                                              * and allocated to a SD Memory Card manufacturer by
                                                              * the SD-3C, LLC. This procedure is established to ensure
                                                              * uniqueness of the CID register.
                                                              * As an example, the OID hex value field for the card OEM
                                                              * "SM" will be: 0x534D.
                                                              */

#define CY_SD_HOST_SCR_CID_MID              (0x00FF0000UL)  /**< The mask for the MID (contained in cid[3]).
                                                              * MID is a 8-bit binary number that identifies the
                                                              * card manufacturer. The MID number is controlled,
                                                              * defined, and allocated to a SD Memory Card manufacturer
                                                              * by the SD-3C, LLC. This procedure is established to
                                                              * ensure uniqueness of the CID register.
                                                              */

/** \} group_sd_host_macros_cid */

/**
* \addtogroup group_sd_host_macros_csd
* \{
*/

#define CY_SD_HOST_CSD_V2_CSD_STRUCTURE     (0x0000FF00UL)  /**< CSD structure (contained in csd[3]) */

#define CY_SD_HOST_CSD_V2_TAAC              (0x0000FF00UL)  /**< The data read access-time (contained in csd[3]).
                                                              * This field is fixed to 0Eh, which indicates 1 ms.
                                                              */

#define CY_SD_HOST_CSD_V2_NSAC              (0x000000FFUL)  /**< The data read access-time in CLK cycles (NSAC*100)
                                                              * (contained in csd[3]).
                                                              * This field is fixed to 00h. NSAC should not
                                                              * be used to calculate time-out values
                                                              * for CSD Version 2.0.
                                                              */

#define CY_SD_HOST_CSD_V2_TRAN_SPEED        (0xFF000000UL)  /**< The max. data transfer rate (contained in csd[2]).
                                                              * Equals to 0x32 (25 MHz) or 0x5A (50 MHz).
                                                              */

#define CY_SD_HOST_CSD_V2_CCC               (0x00FFF000UL)  /**< The card command classes (contained in csd[2]).
                                                              * The card command class register CCC defines which
                                                              * command classes are supported by this card.
                                                              * A value of 1 in a CCC bit means that the
                                                              * corresponding command class is supported.
                                                              */

#define CY_SD_HOST_CSD_V2_READ_BL_LEN       (0x00000F00UL)  /**< The max. read data block length (contained in csd[2]).
                                                              * This field is fixed to 9h, which
                                                              * indicates READ_BL_LEN=512 Byte.
                                                              */

#define CY_SD_HOST_CSD_V2_READ_BL_PARTIAL   (0x00000080UL)  /**< The partial blocks for read allowed (contained in csd[2]).
                                                              * This field is fixed to 0, which indicates
                                                              * partial block read is inhibited and only unit
                                                              * of block access is allowed.
                                                              */

#define CY_SD_HOST_CSD_V2_WRITE_BLK_MISALIGN (0x00000040UL)  /**< The write block misalignment (contained in csd[2]).
                                                              * This field is fixed to 0, which indicates
                                                              * write access crossing physical block boundaries
                                                              * is always disabled in High Capacity SD Memory Card.
                                                              */

#define CY_SD_HOST_CSD_V2_READ_BLK_MISALIGN (0x00000020UL)  /**< The read block misalignment (contained in csd[2]).
                                                              * This field is fixed to 0, which indicates
                                                              * read access crossing physical block boundaries
                                                              * is always disabled in High Capacity SD Memory Card.
                                                              */

#define CY_SD_HOST_CSD_V2_DSR_IMP           (0x00000010UL)  /**< The DSR implemented (contained in csd[2]).
                                                              * Defines if the configurable driver stage is
                                                              * integrated on the card.
                                                              */

#define CY_SD_HOST_CSD_V2_C_SIZE_MASK       (0x3FFFFF00UL)  /**< The device size (contained in csd[1]).
                                                              * This parameter is used to calculate the
                                                              * user data area capacity in the SD memory card
                                                              * (not include the protected area).
                                                              * The user data area capacity is calculated
                                                              * from C_SIZE as follows:
                                                              * memory capacity = (C_SIZE+1) * 512K byte.
                                                              */

#define CY_SD_HOST_CSD_V2_ERASE_BLK_EN      (0x00000040UL)  /**< The erase single block enable (contained in csd[1]).
                                                              * This field is fixed to 1, which means the
                                                              * host can erase one or multiple units of 512 bytes.
                                                              */

#define CY_SD_HOST_CSD_V2_SECTOR_SIZE_MSB   (0x0000003FUL)  /**< The MSB of erase sector size (6 MSB bits contained in csd[1]).
                                                              * SECTOR_SIZE is fixed to 7Fh, which indicates 64 KBytes.
                                                              * This value does not relate to erase operation.
                                                              * Version 2.00 cards indicates memory boundary by
                                                              * AU size and this field should not be used.
                                                              */

#define CY_SD_HOST_CSD_V2_SECTOR_SIZE_LSB   (0x80000000UL)  /**< The LSB of erase sector size
                                                              * (1 LSB bit of SECTOR_SIZE contained in csd[0]).
                                                              */

#define CY_SD_HOST_CSD_V2_WP_GRP_SIZE       (0x7F000000UL)  /**< The write protect group size (contained in csd[0]).
                                                              * This field is fixed to 00h. The High Capacity
                                                              * SD Memory Card does not support write protected groups.
                                                              */

#define CY_SD_HOST_CSD_V2_WP_GRP_ENABLE     (0x00800000UL)  /**< The write protect group enable (contained in csd[0]).
                                                              * This field is fixed to 0. The High Capacity SD Memory
                                                              * Card does not support write protected groups.
                                                              */

#define CY_SD_HOST_CSD_V2_R2W_FACTOR        (0x001C0000UL)  /**< The write speed factor (contained in csd[0]).
                                                              * This field is fixed to 2h, which indicates 4 multiples.
                                                              */

#define CY_SD_HOST_CSD_V2_WRITE_BL_LEN      (0x0003C000UL)  /**< The max. write data block length (contained in csd[0]).
                                                              * This field is fixed to 9h, which indicates
                                                              * WRITE_BL_LEN=512 Byte.
                                                              */

#define CY_SD_HOST_CSD_V2_WRITE_BL_PARTIAL  (0x00002000UL)  /**< The partial blocks for write allowed (contained in csd[0]).
                                                              * This field is fixed to 0, which indicates partial
                                                              * block read is inhibited and only unit of block
                                                              * access is allowed.
                                                              */

#define CY_SD_HOST_CSD_V2_FILE_FORMAT_GRP   (0x00000080UL)  /**< The File format group (contained in csd[0]).
                                                              * This field is set to 0. Host should not use this field.
                                                              */

#define CY_SD_HOST_CSD_V2_COPY              (0x00000040UL)  /**< The copy flag (OTP) (contained in csd[0]).
                                                              * Defines if the contents is original (=0) or
                                                              * has been copied (=1). The COPY bit for OTP and MTP
                                                              * devices, sold to end consumers, is set to 1,
                                                              * which identifies the card contents as a copy.
                                                              * The COPY bit is a one time programmable bit.
                                                              */

#define CY_SD_HOST_CSD_V2_PERM_WRITE_PROTECT (0x00000020UL)  /**< The permanent write protection (contained in csd[0]).
                                                              * Permanently protects the entire card content
                                                              * against overwriting or erasing (all write and erase
                                                              * commands for this card are permanently disabled).
                                                              * The default value is 0, i.e. not permanently write
                                                              * protected.
                                                              */

#define CY_SD_HOST_CSD_V2_TMP_WRITE_PROTECT (0x00000010UL)   /**< The temporary write protection (contained in csd[0]).
                                                              * Temporarily protects the entire card content
                                                              * from being overwritten or erased (all write
                                                              * and erase commands for this card are temporarily
                                                              * disabled). This bit can be set and reset.
                                                              * The default value is 0, i.e. not write protected.
                                                              */

#define CY_SD_HOST_CSD_V2_FILE_FORMAT       (0x0000000CUL)   /**< The File format (contained in csd[0]).
                                                              * This field is set to 0. Host should not use this field.
                                                              */


/** \} group_sd_host_macros_csd */

/**
* \addtogroup group_sd_host_macros_events
* \{
*/

/**
* Command complete. In SD/eMMC mode, this event is set
* after detecting the end bit of a response except for Auto CMD12 and Auto CMD23.
* This event is not generated when the Response Interrupt is disabled.
*/
#define CY_SD_HOST_CMD_COMPLETE            (0x0001U)

/**
* Transfer complete. This event is set when a read/write
* transfer and a command with the Busy Status are completed.
*/
#define CY_SD_HOST_XFER_COMPLETE           (0x0002U)

/**
* Block gap. This event is set when both read/write
* transactions are stopped at the block gap due to a
* Stop-at-Block-Gap Request.
*/
#define CY_SD_HOST_BGAP                    (0x0004U)

/**
* DMA Interrupt. This event is set if the Host Controller
* detects a SDMA Buffer Boundary during a transfer.
* For ADMA, the Host controller generates this
* interrupt by setting the Int field in the
* descriptor table.
* This interrupt is not generated after a Transfer
* Complete.
*/
#define CY_SD_HOST_DMA_INTERRUPT           (0x0008U)

/**
* The Buffer Write is ready. This event is set if
* the Buffer Write Enable changes from 0 to 1.
*/
#define CY_SD_HOST_BUF_WR_READY            (0x0010U)

/**
* The Buffer Read is ready. This event is set if
* the Buffer Read Enable changes from 0 to 1.
*/
#define CY_SD_HOST_BUF_RD_READY            (0x0020U)

/**
* Card insertion. This event is set if
* the Card Inserted in the Present State
* register changes from 0 to 1.
*/
#define CY_SD_HOST_CARD_INSERTION          (0x0040U)

/**
* Card removal. This event is set if
* the Card Inserted in the Present State
* register changes from 1 to 0.
*/
#define CY_SD_HOST_CARD_REMOVAL            (0x0080U)

/**
* The Card interrupt. This event reflects the
* synchronized value of DAT[1] Interrupt Input for SD Mode
*/
#define CY_SD_HOST_CARD_INTERRUPT          (0x0100U)

/**
* FX event.
* This status is set when R[14] of the response register is set to 1
* and Response Type R1/R5 is set to 0 in the Transfer Mode
* register. This interrupt is used with the response check function.
*/
#define CY_SD_HOST_FX_EVENT                (0x2000U)

/**
* Command Queuing event.
* This status is set if a Command Queuing/Crypto related event
* has occurred in eMMC/SD mode.
*/
#define CY_SD_HOST_CQE_EVENT               (0x4000U)

/**
* Error Interrupt.
* If any of the bits in the Error Interrupt Status
* register are set, then this bit is set.
*/
#define CY_SD_HOST_ERR_INTERRUPT           (0x8000U)

/**
* Command timeout error. In SD/eMMC Mode,
* this event is set only if no response is returned
* within 64 SD clock cycles from the end bit of the
* command. If the Host Controller detects a CMD line conflict,
* along with Command CRC Error bit, this event is set to 1,
* without waiting for 64 SD/eMMC card clock cycles.
*/
#define CY_SD_HOST_CMD_TOUT_ERR            (0x0001U)

/**
* Command CRC error. A Command CRC Error is generated
* in SD/eMMC mode when:
* 1. A response is returned and the Command Timeout
* Error is set to 0 (indicating no timeout),
* this bit is set to 1 when detecting a CRC error
* in the command response.
* 2. The Host Controller detects a CMD line conflict by
* monitoring the CMD line when a command is issued. If
* the Host Controller drives the CMD line to level 1, but
* detects level 0 on the CMD line at the next SD clock
* edge, then the Host Controller aborts the command (stop
* driving CMD line) and sets this bit to 1. The Command
* Timeout Error is also set to 1 to distinguish a CMD line
* conflict.
*/
#define CY_SD_HOST_CMD_CRC_ERR             (0x0002U)

/**
* Command End Bit error.
* This bit is set after detecting that the end bit of a command
* response is 0 in SD/eMMC mode.
*/
#define CY_SD_HOST_CMD_END_BIT_ERR         (0x0004U)

/**
* Command Index error.
* This bit is set if a Command Index error occurs in the
* command response in SD/eMMC mode.
*/
#define CY_SD_HOST_CMD_IDX_ERR             (0x0008U)

/**
* Data Timeout error.
* This bit is set in SD/eMMC mode when detecting one of the
* following timeout conditions:
* *  Busy timeout for R1b, R5b type
* *  Busy timeout after Write CRC status
* *  Write CRC Status timeout
* *  Read Data timeout.
*/
#define CY_SD_HOST_DATA_TOUT_ERR           (0x0010U)

/**
* Data CRC error.
* This error occurs in SD/eMMC mode after detecting a CRC
* error while transferring read data that uses the DAT line,
* after detecting the Write CRC status having a value other
* than 010 or when writing a CRC status timeout.
*/
#define CY_SD_HOST_DATA_CRC_ERR            (0x0020U)

/**
* Data End Bit error.
* This error occurs in SD/eMMC mode either when detecting 0
* at the end bit position of read data that uses the DAT line or
* at the end bit position of the CRC status.
*/
#define CY_SD_HOST_DATA_END_BIT_ERR        (0x0040U)

/**
* Current Limit error.
* The SD Host driver does not support this function,
* this bit is always set to 0.
*/
#define CY_SD_HOST_CUR_LMT_ERR             (0x0080U)

/**
* Auto CMD error.
* This error status is used by Auto CMD12 and Auto CMD23 in
* SD/eMMC mode. This bit is set after detecting that any of
* the bits D00 to D05 in the Auto CMD Error Status register has
* changed from 0 to 1. D07 is effective in case for Auto CMD12.
* The Auto CMD Error Status register is valid while this bit is set to
* 1 and may be cleared by clearing this bit.
*/
#define CY_SD_HOST_AUTO_CMD_ERR            (0x0100U)

/**
* ADMA error.
* This bit is set when the Host Controller detects an error during
* an ADMA-based data transfer. The possible reasons for an error:
* * An error response is received from the System bus;
* * ADMA3, ADMA2 Descriptors are invalid;
* * CQE Task or Transfer descriptors are invalid.
* When an error occurs, the state of the ADMA is saved in the
* ADMA Error Status register.
*/
#define CY_SD_HOST_ADMA_ERR                (0x0200U)

/**
* Tuning error.
* The SD Host driver does not support this function.
*/
#define CY_SD_HOST_TUNING_ERR              (0x0400U)

/**
* Response error.
* Host Controller Version 4.00 supports the response error check
* function to avoid overhead of the response error check by Host
* Driver during DMA execution. If the Response Error Check
* Enable is set to 1 in the Transfer Mode register, the Host
* Controller checks R1 or R5 response. If an error is detected
* in a response, this bit is set to 1. This is applicable in
* SD/eMMC mode.
*/
#define CY_SD_HOST_RESP_ERR                (0x0800U)

/**
* Boot Acknowledgement error.
* This bit is set when there is a timeout for boot
* acknowledgement or after detecting the boot ACK status having
* a value other than 010. This is applicable only when boot
* acknowledgement is expected in eMMC mode.
*/
#define CY_SD_HOST_BOOT_ACK_ERR            (0x1000U)

/** \} group_sd_host_macros_events */

/**
* \addtogroup group_sd_host_macros_present_status
* \{
*/

/**
* Command Inhibit (CMD).
* This bit indicates the following:
* - SD/eMMC mode: If this bit is set to 0, it indicates that the
* CMD line is not in use and the Host controller can issue
* an SD/eMMC command using the CMD line. This bit is
* set when the command register is written. This bit is
* cleared when the command response is received. This bit
* is not cleared by the response of auto CMD12/23 but
* cleared by the response of the Read/Write command.
*/
#define CY_SD_HOST_CMD_INHIBIT             (0x00000001UL)

/**
* Command Inhibit (DAT).
* This bit is applicable for SD/eMMC mode and is generated if
* either the DAT line active or Read transfer active is set to 1. If
* this bit is set to 0, it indicates that the Host Controller can
* issue subsequent SD/eMMC commands.
*/
#define CY_SD_HOST_CMD_CMD_INHIBIT_DAT     (0x00000002UL)

/**
* DAT Line Active (SD/eMMC Mode only).
* This bit indicates whether one of the DAT lines on the
* SD/eMMC bus is in use.
* For Read transactions, this bit indicates whether a
* read transfer is executing on the SD/eMMC bus.
* For Write transactions, this bit indicates whether a
* write transfer is executing on the SD/eMMC bus.
* For a command with the Busy status, this status indicates whether the
* command executing busy is executing on an SD or eMMC
* bus.
*/
#define CY_SD_HOST_DAT_LINE_ACTIVE         (0x00000004UL)

/**
* DAT[7:4] Line Signal Level.
* These bits are used to check the DAT line level to recover from
* errors and for debugging. These bits reflect the value of the
* sd_dat_in (upper nibble) signal.
*/
#define CY_SD_HOST_DAT_7_4                 (0x000000F0UL)

/**
* Write Transfer Active
* This status indicates whether the Write transfer is active for
* SD/eMMC mode.
*/
#define CY_SD_HOST_WR_XFER_ACTIVE          (0x00000100UL)

/**
* Read Transfer Active.
* This bit indicates whether the Read transfer is active for
* SD/eMMC mode.
*/
#define CY_SD_HOST_RD_XFER_ACTIVE          (0x00000200UL)

/**
* Buffer Write Enable.
* This bit is used for non-DMA transfers. This bit is set if space
* is available for writing data.
*/
#define CY_SD_HOST_BUF_WR_ENABLE           (0x00000400UL)

/**
* Buffer Read Enable.
* This bit is used for non-DMA transfers. This bit is set if valid
* data exists in the Host buffer.
*/
#define CY_SD_HOST_BUF_RD_ENABLE           (0x00000800UL)

/**
* Card Inserted.
* This bit indicates whether a card has been inserted. The
* Host Controller debounces this signal so that the Host Driver
* does not need to wait for the signal to stabilize.
*/
#define CY_SD_HOST_CARD_INSERTED           (0x00010000UL)

/**
* Card Stable.
* This bit indicates the stability of the Card Detect Pin Level. A
* card is not detected if this bit is set to 1 and the value of the
* CARD_INSERTED bit is 0.
*/
#define CY_SD_HOST_CARD_STABLE             (0x00020000UL)

/**
* Card Detect Pin Level.
* This bit reflects the inverse synchronized value of the
* card_detect_n signal.
*/
#define CY_SD_HOST_CARD_DETECT_PIN_LEVEL   (0x00040000UL)

/**
* Write Protect Switch Pin Level.
* This bit is supported only for memory and combo cards. This
* bit reflects the synchronized value of the card_write_prot
* signal.
*/
#define CY_SD_HOST_WR_PROTECT_SW_LVL       (0x00080000UL)

/**
* DAT[3:0] Line Signal Level.
* This bit is used to check the DAT line level to recover from
* errors and for debugging. These bits reflect the value of the
* sd_dat_in (lower nibble) signal.
*/
#define CY_SD_HOST_DAT_3_0                 (0x00F00000UL)

/**
* DAT[0] Line Signal Level.
* This bit is used to check the DAT0 line level to check R1b
* response. This bit reflects the value of the sd_dat_in[0]
* signal.
*/
#define CY_SD_HOST_DAT_0_Msk                   (0x00100000UL)

/**
* Command-Line Signal Level.
* This bit is used to check the CMD line level to recover from
* errors and for debugging. These bits reflect the value of the
* sd_cmd_in signal.
*/
#define CY_SD_HOST_CMD_LINE_LVL            (0x01000000UL)

/**
* Host Regulator Voltage Stable.
* This bit is used to check whether the host regulator voltage is
* stable for switching the voltage of UHS-I mode. This bit
* reflects the synchronized value of the host_reg_vol_stable
* signal.
*/
#define CY_SD_HOST_HOST_REG_VOL            (0x02000000UL)

/**
* Command Not Issued by Error.
* This bit is set if a command cannot be issued after setting
* the command register due to an error except an Auto
* CMD12 error.
*/
#define CY_SD_HOST_CMD_ISSU_ERR            (0x08000000UL)

/**
* Sub Command Status.
* This bit is used to distinguish between a main command and
* a sub command status.
*/
#define CY_SD_HOST_SUB_CMD_STAT            (0x10000000UL)

/**
* In Dormant Status.
* This bit indicates whether UHS-II lanes enter the Dormant state
* in the UHS-II mode. For SD/eMMC mode, this bit always
* returns 0.
*/
#define CY_SD_HOST_IN_DORMANT_ST           (0x20000000UL)

/**
* Lane Synchronization.
* This bit indicates whether a lane is synchronized in UHSII
* mode. For SD/eMMC mode, this bit always returns 0.
*/
#define CY_SD_HOST_LANE_SYNC               (0x40000000UL)

/**
* UHS-II Interface Detection.
* This bit indicates whether a card supports the UHS-II
* interface. For SD/eMMC mode, this bit always returns 0.
*/
#define CY_SD_HOST_UHS2_IF_DETECT          (0x80000000UL)

/** \} group_sd_host_macros_present_status */


/**
* \addtogroup group_sd_host_enums
* \{
*/

/******************************************************************************
 * Enumerations
 *****************************************************************************/

/** SD command types. */
typedef enum
{
    CY_SD_HOST_CMD_NORMAL     = 0U,  /**< Other commands */
    CY_SD_HOST_CMD_SUSPEND    = 1U,  /**< CMD52 for writing "Bus Suspend" in CCCR */
    CY_SD_HOST_CMD_RESUME     = 2U,  /**< CMD52 for writing "Function Select" in CCCR */
    CY_SD_HOST_CMD_ABORT      = 3U  /**< CMD12, CMD52 for writing "I/O Abort" in CCCR */
}cy_en_sd_host_cmd_type_t;

/** SD Host auto command enable selection. */
typedef enum
{
    CY_SD_HOST_AUTO_CMD_NONE  = 0U,  /**< Auto command disable. */
    CY_SD_HOST_AUTO_CMD_12    = 1U,  /**< Auto command 12 enable. */
    CY_SD_HOST_AUTO_CMD_23    = 2U,  /**< Auto command 23 enable. */
    CY_SD_HOST_AUTO_CMD_AUTO  = 3U   /**< Auto command Auto enable. */
}cy_en_sd_host_auto_cmd_t;

/** SD Host reset types. */
typedef enum
{
    CY_SD_HOST_RESET_DATALINE = 0U, /**< Reset the data circuit only. */
    CY_SD_HOST_RESET_CMD_LINE = 1U, /**< Reset the command circuit only. */
    CY_SD_HOST_RESET_ALL      = 2U  /**< Reset the whole SD Host controller. */
}cy_en_sd_host_reset_t;

/** SD Host error interrupt types. */
typedef enum
{
    CY_SD_HOST_ADMA_ST_STOP   = 0U,   /**< Stop DMA - The SYS_ADR register points to
                                        * a location next to the error descriptor.
                                        */
    CY_SD_HOST_ADMA_ST_FDS    = 1U,   /**< Fetch Descriptor - The SYS_ADR register
                                        * points to the error descriptor.
                                        */
    CY_SD_HOST_ADMA_ST_TFR    = 3U,   /**< Transfer Data - SYS_ADR register points
                                        * to a location next to the error descriptor.
                                        */
    CY_SD_HOST_ADMA_LEN_ERR   = 4U   /**< The ADMA Length Mismatch error. */
}cy_en_sd_host_adma_error_t;

/** Auto CMD Status error codes. */
typedef enum
{
    CY_SD_HOST_AUTO_CMD12_NOT_EXEC         = 0U,  /**< Auto CMD12 Not Executed. */
    CY_SD_HOST_AUTO_CMD_TOUT_ERR           = 1U,  /**< Auto CMD Timeout Error. */
    CY_SD_HOST_AUTO_CMD_CRC_ERR            = 2U,  /**< Auto CMD CRC Error. */
    CY_SD_HOST_AUTO_CMD_EBIT_ERR           = 3U,  /**< Auto CMD End Bit Error. */
    CY_SD_HOST_AUTO_CMD_IDX_ERR            = 4U,  /**< Auto CMD Index Error. */
    CY_SD_HOST_AUTO_CMD_RESP_ERR           = 5U,  /**< Auto CMD Response Error. */
    CY_SD_HOST_CMD_NOT_ISSUED_AUTO_CMD12   = 7U   /**< Command Not Issued By Auto CMD12 Error. */
} cy_en_sd_host_auto_cmd_status_t;

/** SD host error codes. */
typedef enum
{
    CY_SD_HOST_SUCCESS                     = 0U,  /**< Successful. */
    CY_SD_HOST_ERROR                       = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 1U,  /**< Non-specific error code. */
    CY_SD_HOST_ERROR_INVALID_PARAMETER     = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 2U,  /**< The provided parameter is not valid. */
    CY_SD_HOST_ERROR_OPERATION_IN_PROGRESS = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 3U,  /**< A conflicting or requested operation is still in progress. */
    CY_SD_HOST_ERROR_UNINITIALIZED         = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 4U,  /**< The module (or part of it) was not initialized properly. */
    CY_SD_HOST_ERROR_TIMEOUT               = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 5U,  /**< A Time Out error occurred */
    CY_SD_HOST_OPERATION_INPROGRESS        = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 6U,  /**< The indicator for operation in progress. */
    CY_SD_HOST_ERROR_UNUSABLE_CARD         = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 7U,  /**< The card is unusable. */
    CY_SD_HOST_ERROR_DISCONNECTED          = CY_SD_HOST_ID | CY_PDL_STATUS_ERROR | 8U   /**< The card is disconnected. */
} cy_en_sd_host_status_t;

/** The widths of the data bus. */
typedef enum
{
    CY_SD_HOST_BUS_WIDTH_1_BIT              = 0U,  /**< The 1-bit mode data transfer width. */
    CY_SD_HOST_BUS_WIDTH_4_BIT              = 1U,  /**< The 4-bit mode data transfer width. */
    CY_SD_HOST_BUS_WIDTH_8_BIT              = 2U  /**< The 8-bit mode data transfer width. */
} cy_en_sd_host_bus_width_t;

/** The bus speed modes. */
typedef enum
{
    CY_SD_HOST_BUS_SPEED_DEFAULT            = 0U,  /**< Default Speed mode: 3.3V signaling at 25 MHz SDClk. */
    CY_SD_HOST_BUS_SPEED_HIGHSPEED          = 1U,  /**< High Speed mode: 3.3V signaling at 50 MHz SDClk. */
    CY_SD_HOST_BUS_SPEED_SDR12_5            = 2U,  /**< SDR12: UHS-I (1.8V signaling) at 25 MHz SDClk (12.5 MB/sec). */
    CY_SD_HOST_BUS_SPEED_SDR25              = 3U,  /**< SDR25: UHS-I (1.8V signaling) at 50 MHz SDClk (25 MB/sec). */
    CY_SD_HOST_BUS_SPEED_SDR50              = 4U,  /**< SDR50: UHS-I (1.8V signaling) at 100 MHz SDClk (50 MB/sec). */
    CY_SD_HOST_BUS_SPEED_EMMC_LEGACY        = 5U,  /**< Backwards Compatibility with legacy MMC card (26MB/sec max). */
    CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR = 6U,   /**< eMMC High speed SDR (52MB/sec max) */
    CY_SD_HOST_BUS_SPEED_DDR50              = 7U  /**< DDR50: UHS-I (1.8V signaling) at 50 MHz SDClk (50 MB/sec). */
} cy_en_sd_host_bus_speed_mode_t;

/** The SD bus voltage select. */
typedef enum
{
    CY_SD_HOST_IO_VOLT_3_3V                 = 0U,  /**< 3.3V.*/
    CY_SD_HOST_IO_VOLT_1_8V                 = 1U   /**< 1.8V. */
} cy_en_sd_host_io_voltage_t;

/** Erase type. */
typedef enum
{
    CY_SD_HOST_ERASE_ERASE               = 0U,  /**< The ERASE operation.*/
    CY_SD_HOST_ERASE_DISCARD             = 1U,  /**< The DISCARD operation. */
    CY_SD_HOST_ERASE_FULE                = 2U,  /**< The Full User Area Logical Erase (FULE) operation. */
    CY_SD_HOST_ERASE_SECURE              = 3U,  /**< The secure purge according to
                                                * Secure Removal Type in EXT_CSD
                                                * on the erase groups identified by the
                                                * startAddr&endAddr parameters and
                                                * any copies of those erase groups.
                                                */
    CY_SD_HOST_ERASE_SECURE_TRIM_STEP_2  = 4U,  /**< The secure purge operation on
                                                * the write blocks according to
                                                * Secure Removal Type in EXT_CSD
                                                * and copies of those write blocks
                                                * that were previously identified
                                                * using \ref Cy_SD_Host_Erase with
                                                * CY_SD_HOST_ERASE_SECURE_TRIM_STEP_1
                                                */
    CY_SD_HOST_ERASE_SECURE_TRIM_STEP_1  = 5U,  /**< Mark the write blocks, indicated
                                                * by the startAddr&endAddr parameters,
                                                * for secure erase.
                                                */
    CY_SD_HOST_ERASE_TRIM                = 6U   /**< Trim the write blocks identified by
                                                * the startAddr&endAddr parameters. The controller
                                                * can perform the actual erase at convenient time.
                                                */
} cy_en_sd_host_erase_type_t;

/** Card type. */
typedef enum
{
    CY_SD_HOST_SD               = 0U,  /**< The Secure Digital card (SD). */
    CY_SD_HOST_SDIO             = 1U,  /**< The CD Input Output card (SDIO). */
    CY_SD_HOST_EMMC             = 2U,  /**< The Embedded Multimedia card (eMMC). */
    CY_SD_HOST_COMBO            = 3U,  /**< The Combo card (SD + SDIO). */
    CY_SD_HOST_UNUSABLE         = 4U,  /**< The unusable or not supported. */
    CY_SD_HOST_NOT_EMMC         = 5U   /**< The card is not eMMC. */
} cy_en_sd_host_card_type_t;

/** The card capacity type. */
typedef enum
{
    CY_SD_HOST_SDSC             = 0U,   /**< SDSC - Secure Digital Standard Capacity (up to 2 GB). */
    CY_SD_HOST_SDHC             = 1U,   /**< SDHC - Secure Digital High Capacity (up to 32 GB). */
    CY_SD_HOST_EMMC_LESS_2G     = 0U,   /**< The eMMC block addressing for less than 2GB. */
    CY_SD_HOST_EMMC_GREATER_2G  = 1U,   /**< The eMMC block addressing for greater than 2GB. */
    CY_SD_HOST_SDXC             = 2U,   /**< SDXC - Secure Digital Extended Capacity (up to 2 TB). */
    CY_SD_HOST_UNSUPPORTED      = 4U    /**< Not supported. */
}cy_en_sd_host_card_capacity_t;

/** SDHC response types. */
typedef enum
{
    CY_SD_HOST_RESPONSE_NONE    = 0U, /**< No Response. */
    CY_SD_HOST_RESPONSE_LEN_136 = 1U, /**< Response Length 136. */
    CY_SD_HOST_RESPONSE_LEN_48  = 2U, /**< Response Length 48. */
    CY_SD_HOST_RESPONSE_LEN_48B = 3U  /**< Response Length 48. Check Busy after response. */
}cy_en_sd_host_response_type_t;

/** The DMA type enum. */
typedef enum
{
    CY_SD_HOST_DMA_SDMA         = 0U, /**< SDMA mode. */
    CY_SD_HOST_DMA_ADMA2        = 2U, /**< ADMA2 mode. */
    CY_SD_HOST_DMA_ADMA2_ADMA3  = 3U  /**< ADMA2-ADMA3 mode. */
}cy_en_sd_host_dma_type_t;

/** Write Protect type enum. */
typedef enum
{
    CY_SD_HOST_PERMANENT         = 0U, /**< The permanent write protect. */
    CY_SD_HOST_ENABLE_TEMPORARY  = 1U, /**< The temporary write protect. */
    CY_SD_HOST_DISABLE_TEMPORARY = 2U  /**< Clear the temporary write protect. */
} cy_en_sd_host_write_protect_t;

/** Card status in R1 response type enum. */
typedef enum
{
    CY_SD_HOST_AKE_SEQ_ERROR_R1_RESP         = 3U, /**< Error in the sequence of the authentication process. */
    CY_SD_HOST_APP_CMD_R1_RESP               = 5U, /**< The card will expect ACMD, or an indication that the command has been interpreted as ACMD. */
    CY_SD_HOST_FX_EVENT_R1_RESP              = 6U, /**< Extension Functions may set this bit to get host to deal with events. */
    CY_SD_HOST_READY_FOR_DATA_R1_RESP        = 8U, /**< Corresponds to buffer empty signaling on the bus. */
    CY_SD_HOST_CURRENT_STATE_0_R1_RESP       = 9U, /**< The state of the card when receiving the command. The four bits are interpreted as a binary coded number between 0 and 15. It is 0th bit. */
    CY_SD_HOST_CURRENT_STATE_1_R1_RESP       = 10U, /**< The state of the card when receiving the command. The four bits are interpreted as a binary coded number between 0 and 15. It is 1st bit. */
    CY_SD_HOST_CURRENT_STATE_2_R1_RESP       = 11U, /**< The state of the card when receiving the command. The four bits are interpreted as a binary coded number between 0 and 15. It is 2nd bit. */
    CY_SD_HOST_CURRENT_STATE_3_R1_RESP       = 12U, /**< The state of the card when receiving the command. The four bits are interpreted as a binary coded number between 0 and 15. It is 3rd bit. */
    CY_SD_HOST_ERASE_RESET_R1_RESP           = 13U, /**< It indicates if an erase sequence was cleared before executing because an out of erase sequence command was received. */
    CY_SD_HOST_CARD_ECC_DISABLED_R1_RESP     = 14U, /**< It indicates if the command has been executed without using the internal ECC. */
    CY_SD_HOST_WP_ERASE_SKIP_R1_RESP         = 15U, /**< It is set when only partial address space was erased due to existing write protected blocks or the temporary or permanent write protected card was erased. */
    CY_SD_HOST_CSD_OVERWRITE_R1_RESP         = 16U, /**< It indicates read only section of the CSD does not match the card content or there was an attempt to reverse the copy or permanent WP bits was made. */
    CY_SD_HOST_ERROR_R1_RESP                 = 19U, /**< A general or an unknown error occurred during the operation. */
    CY_SD_HOST_CC_ERROR_R1_RESP              = 20U, /**< Internal card controller error. */
    CY_SD_HOST_CARD_ECC_FAILED_R1_RESP       = 21U, /**< Card internal ECC was applied but failed to correct the data. */
    CY_SD_HOST_ILLEGAL_COMMAND_R1_RESP       = 22U, /**< Command  not  legal  for  the  card. */
    CY_SD_HOST_COM_CRC_ERROR_R1_RESP         = 23U, /**< The CRC check of the previous command failed. */
    CY_SD_HOST_LOCK_UNLOCK_FAILED_R1_RESP    = 24U, /**< Set when a sequence or password error has been detected in lock/unlock card command. */
    CY_SD_HOST_CARD_IS_LOCKED_R1_RESP        = 25U, /**< When set, signals that the card is locked by the host. */
    CY_SD_HOST_WP_VIOLATION_R1_RESP          = 26U, /**< Set when the host attempts to write to a protected block or to the temporary or permanent write protected card. */
    CY_SD_HOST_ERASE_PARAM_R1_RESP           = 27U, /**< An invalid selection of write-blocks for erase occurred. */
    CY_SD_HOST_ERASE_SEQ_ERROR_R1_RESP       = 28U, /**< An error in the sequence of erase commands occurred. */
    CY_SD_HOST_BLOCK_LEN_ERROR_R1_RESP       = 29U, /**< The transferred block length is not allowed for this card, or the number of transferred bytes does not match the block length. */
    CY_SD_HOST_ADDRESS_ERROR_R1_RESP         = 30U, /**< A misaligned address which did not match the block length was used in the command. */
    CY_SD_HOST_OUT_OF_RANGE_R1_RESP          = 31U, /**< The command's argument was out of the allowed range for this card. */
} cy_en_sd_host_r1_response_t;

/** \} group_sd_host_enums */

/**
* \addtogroup group_sd_host_data_structures
* \{
*/

/******************************************************************************
 * Structures
 *****************************************************************************/

/** SD Host initialization configuration structure. */
typedef struct
{
    bool                          emmc;             /**< Set to true of eMMC otherwise false. */
    cy_en_sd_host_dma_type_t      dmaType;          /**< Selects the DMA type to be used. */
    bool                          enableLedControl; /**< If true the SD clock controls one IO
                                                     *   used to indicate when the card
                                                     *    is being accessed.
                                                     */
} cy_stc_sd_host_init_config_t;

/** SD/eMMC card configuration structure. */
typedef struct
{
    bool                          lowVoltageSignaling; /**< If true, the host supports the 1.8V signaling. */
    cy_en_sd_host_bus_width_t     busWidth;            /**< The desired bus width. */
    cy_en_sd_host_card_type_t     *cardType;           /**< The card type. */
    uint32_t                      *rca;                /**< The pointer to where to store the cards relative card address. */
    cy_en_sd_host_card_capacity_t *cardCapacity;       /**< Stores the card capacity. */
}cy_stc_sd_host_sd_card_config_t;

/** SD Host command configuration structure. */
typedef struct
{
    uint32_t                      commandIndex;      /**< The index of the command. */
    uint32_t                      commandArgument;   /**< The argument for the command. */
    bool                          enableCrcCheck;    /**< Enables the CRC check on the response. */
    bool                          enableAutoResponseErrorCheck; /**< If true the hardware checks the response for errors. */
    cy_en_sd_host_response_type_t respType;          /**< The response type. */
    bool                          enableIdxCheck;    /**< Checks the index of the response. */
    bool                          dataPresent;       /**< true: Data is present to
                                                      * be transferred using the DAT line,
                                                      * false: Commands use the CMD line only.
                                                      */
    cy_en_sd_host_cmd_type_t      cmdType;           /**< The command type. */
} cy_stc_sd_host_cmd_config_t;

/** The SD Host data transfer configuration structure. */
typedef struct
{
    uint32_t                      blockSize;           /**< The size of the data block. */
    uint32_t                      numberOfBlock;       /**< The number of blocks to send. */
    bool                          enableDma;           /**< Enables DMA for the transaction. */
    cy_en_sd_host_auto_cmd_t      autoCommand;         /**< Selects which auto commands are used if any. */
    bool                          read;                /**< true = Read from the card, false = Write to the card. */
    uint32_t*                     data;                /**< The pointer to data to send/receive or
                                                        *   the pointer to the DMA descriptor.
                                                        */
    uint32_t                      dataTimeout;         /**< The timeout value for the transfer. */
    bool                          enableIntAtBlockGap; /**< Enables the interrupt generation at the block gap. */
    bool                          enReliableWrite;     /**< For EMMC enables the reliable write. */
}cy_stc_sd_host_data_config_t;

/** SD Host Write/Read structure. */
typedef struct
{
    uint32_t*                     data;            /**< The pointer to data. */
    uint32_t                      address;         /**< The address to Write/Read data on the card or eMMC. */
    uint32_t                      numberOfBlocks;  /**< The number of blocks to Write/Read. */
    cy_en_sd_host_auto_cmd_t      autoCommand;     /**< Selects which auto commands are used if any. */
    uint32_t                      dataTimeout;     /**< The timeout value for the transfer. */
    bool                          enReliableWrite; /**< For EMMC cards, enables the reliable write. */
    bool                          enableDma;       /**< Enables DMA for the transaction. */
} cy_stc_sd_host_write_read_config_t;

/** Context structure. */
typedef struct
{
    cy_en_sd_host_dma_type_t      dmaType;      /**< Defines the DMA type to be used. */
    cy_en_sd_host_card_capacity_t cardCapacity; /**< The standard card or the card with the high capacity. */
    uint32_t                      maxSectorNum; /**< The SD card maximum number of the sectors. */
    uint32_t                      RCA;          /**< The relative card address. */
    cy_en_sd_host_card_type_t     cardType;     /**< The card type. */
    uint32_t                      csd[4];       /**< The Card-Specific Data register. */
}cy_stc_sd_host_context_t;

/** \} group_sd_host_data_structures */


/**
* \addtogroup group_sd_host_high_level_functions
* \{
*/

/******************************************************************************
* Functions
*******************************************************************************/

/* High level section */

cy_en_sd_host_status_t Cy_SD_Host_InitCard(SDHC_Type *base,
                                           cy_stc_sd_host_sd_card_config_t *config,
                                           cy_stc_sd_host_context_t *context);
cy_en_sd_host_status_t Cy_SD_Host_Read(SDHC_Type *base,
                                       cy_stc_sd_host_write_read_config_t *config,
                                       cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_Write(SDHC_Type *base,
                                        cy_stc_sd_host_write_read_config_t *config,
                                        cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_Erase(SDHC_Type *base,
                                        uint32_t startAddr,
                                        uint32_t endAddr,
                                        cy_en_sd_host_erase_type_t eraseType,
                                        cy_stc_sd_host_context_t const *context);

/** \} group_sd_host_high_level_functions */

/**
* \addtogroup group_sd_host_low_level_functions
* \{
*/

cy_en_sd_host_status_t Cy_SD_Host_Init(SDHC_Type *base,
                                       const cy_stc_sd_host_init_config_t* config,
                                       cy_stc_sd_host_context_t *context);
void Cy_SD_Host_DeInit(SDHC_Type *base);
void Cy_SD_Host_Enable(SDHC_Type *base);
void Cy_SD_Host_Disable(SDHC_Type *base);
__STATIC_INLINE void Cy_SD_Host_EnableSdClk(SDHC_Type *base);
__STATIC_INLINE void Cy_SD_Host_DisableSdClk(SDHC_Type *base);
cy_en_sd_host_status_t Cy_SD_Host_SetSdClkDiv(SDHC_Type *base, uint16_t clkDiv);
bool Cy_SD_Host_IsWpSet(SDHC_Type const *base);
cy_en_sd_host_status_t Cy_SD_Host_SetHostBusWidth(SDHC_Type *base,
                                                  cy_en_sd_host_bus_width_t width);
cy_en_sd_host_status_t Cy_SD_Host_SetBusWidth(SDHC_Type *base,
                                              cy_en_sd_host_bus_width_t width,
                                              cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_SetHostSpeedMode(SDHC_Type *base,
                                                  cy_en_sd_host_bus_speed_mode_t speedMode);
cy_en_sd_host_status_t Cy_SD_Host_SetBusSpeedMode(SDHC_Type *base,
                                                  cy_en_sd_host_bus_speed_mode_t speedMode,
                                                  cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_SelBusVoltage(SDHC_Type *base,
                                                bool enable18VSignal,
                                                cy_stc_sd_host_context_t *context);
void Cy_SD_Host_EnableCardVoltage(SDHC_Type *base);
void Cy_SD_Host_DisableCardVoltage(SDHC_Type *base);
cy_en_sd_host_status_t Cy_SD_Host_GetResponse(SDHC_Type const *base,
                                              uint32_t *responsePtr,
                                              bool largeResponse);
cy_en_sd_host_status_t Cy_SD_Host_SendCommand(SDHC_Type *base,
                                              cy_stc_sd_host_cmd_config_t const *config);
cy_en_sd_host_status_t Cy_SD_Host_InitDataTransfer(SDHC_Type *base,
                                                   cy_stc_sd_host_data_config_t const *dataConfig);
__STATIC_INLINE uint32_t Cy_SD_Host_BufferRead(SDHC_Type const *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_BufferWrite(SDHC_Type *base, uint32_t data);
void Cy_SD_Host_ChangeIoVoltage(SDHC_Type *base, cy_en_sd_host_io_voltage_t ioVoltage);
__STATIC_INLINE void Cy_SD_Host_StopAtBlockGap(SDHC_Type *base);
__STATIC_INLINE void Cy_SD_Host_ContinueFromBlockGap(SDHC_Type *base);
__STATIC_INLINE uint32_t Cy_SD_Host_GetAutoCmdErrStatus(SDHC_Type const *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_EnableAutoCmd23(SDHC_Type *base);
__STATIC_INLINE void Cy_SD_Host_DisableAutoCmd23(SDHC_Type *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_EnableAsyncInterrupt(SDHC_Type *base);
__STATIC_INLINE void Cy_SD_Host_DisableAsyncInterrupt(SDHC_Type *base);
__STATIC_INLINE uint32_t Cy_SD_Host_GetAdmaErrorStatus(SDHC_Type const *base);
__STATIC_INLINE void Cy_SD_Host_EMMC_Reset(SDHC_Type *base);
cy_en_sd_host_status_t Cy_SD_Host_AbortTransfer(SDHC_Type *base,
                                                cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_WriteProtect(SDHC_Type *base,
                                               cy_en_sd_host_write_protect_t writeProtect,
                                               cy_stc_sd_host_context_t *context);
uint32_t Cy_SD_Host_GetCardStatus(SDHC_Type *base, cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_GetSdStatus(SDHC_Type *base,
                                              uint32_t *sdStatus,
                                              cy_stc_sd_host_context_t const *context);
uint32_t Cy_SD_Host_GetOcr(SDHC_Type *base, cy_stc_sd_host_context_t const *context);
cy_en_sd_host_status_t Cy_SD_Host_GetCid(SDHC_Type *base, uint32_t *cid);
cy_en_sd_host_status_t Cy_SD_Host_GetCsd(SDHC_Type *base,
                                         uint32_t *csd,
                                         cy_stc_sd_host_context_t *context);
cy_en_sd_host_status_t Cy_SD_Host_GetExtCsd(SDHC_Type *base,
                                            uint32_t *extCsd,
                                            cy_stc_sd_host_context_t *context);
uint32_t Cy_SD_Host_GetRca(SDHC_Type *base);
cy_en_sd_host_status_t Cy_SD_Host_GetScr(SDHC_Type *base,
                                         uint32_t *scr,
                                         cy_stc_sd_host_context_t const *context);
uint32_t Cy_SD_Host_GetPresentState(SDHC_Type const *base);
bool Cy_SD_Host_IsCardConnected(SDHC_Type const *base);
void Cy_SD_Host_SoftwareReset(SDHC_Type *base, cy_en_sd_host_reset_t reset);
cy_en_syspm_status_t Cy_SD_Host_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams,
                                                  cy_en_syspm_callback_mode_t mode);
cy_en_sd_host_status_t Cy_SD_Host_GetBlockCount(SDHC_Type *base,
                                         uint32_t *block_count,
                                         cy_stc_sd_host_context_t *context);


/** \} group_sd_host_low_level_functions */

/**
* \addtogroup group_sd_host_interrupt_functions
* \{
*/

__STATIC_INLINE uint32_t Cy_SD_Host_GetNormalInterruptStatus(SDHC_Type const *base);
__STATIC_INLINE void Cy_SD_Host_ClearNormalInterruptStatus(SDHC_Type *base, uint32_t status);
__STATIC_INLINE void Cy_SD_Host_SetNormalInterruptEnable(SDHC_Type *base, uint32_t interrupt);
__STATIC_INLINE uint32_t Cy_SD_Host_GetNormalInterruptEnable(SDHC_Type const *base);
__STATIC_INLINE void Cy_SD_Host_SetNormalInterruptMask(SDHC_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SD_Host_GetNormalInterruptMask(SDHC_Type const *base);
__STATIC_INLINE uint32_t Cy_SD_Host_GetErrorInterruptStatus(SDHC_Type const *base);
__STATIC_INLINE void Cy_SD_Host_ClearErrorInterruptStatus(SDHC_Type *base, uint32_t status);
__STATIC_INLINE void Cy_SD_Host_SetErrorInterruptEnable(SDHC_Type *base, uint32_t interrupt);
__STATIC_INLINE uint32_t Cy_SD_Host_GetErrorInterruptEnable(SDHC_Type const *base);
__STATIC_INLINE void Cy_SD_Host_SetErrorInterruptMask(SDHC_Type *base, uint32_t interruptMask);
__STATIC_INLINE uint32_t Cy_SD_Host_GetErrorInterruptMask(SDHC_Type const *base);

/** \} group_sd_host_interrupt_functions */

/**
* \addtogroup group_sd_host_low_level_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_SD_Host_EnableSdClk
****************************************************************************//**
*
*  Enables the SD clock (SD host drives the SDCLK line).
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_EnableSdClk(SDHC_Type *base)
{
    /* Check for NULL pointer */
    if (NULL != base)
    {
        SDHC_CORE_CLK_CTRL_R(base) = (uint16_t)((uint32_t)SDHC_CORE_CLK_CTRL_R(base) |
                                                SDHC_CORE_CLK_CTRL_R_SD_CLK_EN_Msk |
                                                SDHC_CORE_CLK_CTRL_R_PLL_ENABLE_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_DisableSdClk
****************************************************************************//**
*
*  Disables the SD clock (The SD Host doesn't drive the SDCLK line).
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_DisableSdClk(SDHC_Type *base)
{
    /* Check for NULL pointer */
    if (NULL != base)
    {
        /* Disable SD CLK */
        SDHC_CORE_CLK_CTRL_R(base) = _CLR_SET_FLD16U(SDHC_CORE_CLK_CTRL_R(base),
                                        SDHC_CORE_CLK_CTRL_R_SD_CLK_EN, 0UL);

        /* Wait for at least 3 card clock periods */
        Cy_SysLib_DelayUs(CY_SD_HOST_3_PERIODS_US);

        /* Disable PLL */
        SDHC_CORE_CLK_CTRL_R(base) = _CLR_SET_FLD16U(SDHC_CORE_CLK_CTRL_R(base),
                                        SDHC_CORE_CLK_CTRL_R_PLL_ENABLE, 0UL);
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_BufferRead
****************************************************************************//**
*
*  Reads 32-bits of data from the read buffer.
*  Only use this function if not using SD block DMA to transfer data from buffer.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     Data that is being read.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SD_Host_BufferRead(SDHC_Type const *base)
{
    /* Return the Buffer Data Port Register value */
    return SDHC_CORE_BUF_DATA_R(base);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_BufferWrite
****************************************************************************//**
*
*  Writes 32-bits of data into the write buffer.
*  Only use this function if not using SD block DMA to transfer data to buffer.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param data
*     Data to be written.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t  Cy_SD_Host_BufferWrite(SDHC_Type *base, uint32_t data)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        SDHC_CORE_BUF_DATA_R(base) = data;

        ret = CY_SD_HOST_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_StopAtBlockGap
****************************************************************************//**
*
*  Commands SD host to stop transmitting at the next block gap.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_StopAtBlockGap(SDHC_Type *base)
{
    SDHC_CORE_BGAP_CTRL_R(base) = _CLR_SET_FLD8U(SDHC_CORE_BGAP_CTRL_R(base),
                                            SDHC_CORE_BGAP_CTRL_R_STOP_BG_REQ,
                                            1UL);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_ContinueFromBlockGap
****************************************************************************//**
*
*  Commands SD host to continue transmitting after stopping at the block gap.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_ContinueFromBlockGap(SDHC_Type *base)
{
    SDHC_CORE_BGAP_CTRL_R(base) = (uint8_t)(((uint32_t)SDHC_CORE_BGAP_CTRL_R(base) &
        ~SDHC_CORE_BGAP_CTRL_R_STOP_BG_REQ_Msk) |  /* Clear the Stop At Block Gap Request bit. */
        SDHC_CORE_BGAP_CTRL_R_CONTINUE_REQ_Msk);   /* Set the Continue Request bit. */
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetAutoCmdErrStatus
****************************************************************************//**
*
*  Gets the SD host error status of the auto command.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The bit mask of the Auto Command status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetAutoCmdErrStatus(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_AUTO_CMD_STAT_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_EnableAutoCmd23
****************************************************************************//**
*
*  If the card supports AutoCmd23 call this function to enable it in the host.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t.
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t  Cy_SD_Host_EnableAutoCmd23(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        SDHC_CORE_XFER_MODE_R(base) = _CLR_SET_FLD16U(SDHC_CORE_XFER_MODE_R(base),
                                      SDHC_CORE_XFER_MODE_R_AUTO_CMD_ENABLE,
                                      2UL);

        ret = CY_SD_HOST_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_DisableAutoCmd23
****************************************************************************//**
*
* Removes support for AutoCmd23 if it was previously set.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_DisableAutoCmd23(SDHC_Type *base)
{
    SDHC_CORE_XFER_MODE_R(base) = _CLR_SET_FLD16U(SDHC_CORE_XFER_MODE_R(base),
                                  SDHC_CORE_XFER_MODE_R_AUTO_CMD_ENABLE,
                                  0UL);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_EnableAsyncInterrupt
****************************************************************************//**
*
*  Enables the Asynchronous Interrupt for SDIO cards. Set this only
*  if the card supports this feature.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t  Cy_SD_Host_EnableAsyncInterrupt(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        SDHC_CORE_HOST_CTRL2_R(base) = _CLR_SET_FLD16U(SDHC_CORE_HOST_CTRL2_R(base),
                              SDHC_CORE_HOST_CTRL2_R_ASYNC_INT_ENABLE,
                              1UL);
    }

    return ret;
}



/*******************************************************************************
* Function Name: Cy_SD_Host_DisableAsyncInterrupt
****************************************************************************//**
*
* Removes the support for the Asynchronous Interrupt if it was previously set.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_DisableAsyncInterrupt(SDHC_Type *base)
{
    SDHC_CORE_HOST_CTRL2_R(base) = _CLR_SET_FLD16U(SDHC_CORE_HOST_CTRL2_R(base),
                                              SDHC_CORE_HOST_CTRL2_R_ASYNC_INT_ENABLE,
                                              0UL);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetAdmaErrorStatus
****************************************************************************//**
*
*  Returns the ADMA Error Status register.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The bit mask of ADMA Error Status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetAdmaErrorStatus(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_ADMA_ERR_STAT_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_EMMC_Reset
****************************************************************************//**
*
* Resets the eMMC card.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_EMMC_Reset(SDHC_Type *base)
{
        SDHC_CORE_EMMC_CTRL_R(base) = _CLR_SET_FLD16U(SDHC_CORE_EMMC_CTRL_R(base),
                                                 SDHC_CORE_EMMC_CTRL_R_EMMC_RST_N,
                                                 0UL);

        /* Wait RST_n pulse width of 1 us */
        Cy_SysLib_DelayUs(CY_SD_HOST_EMMC_T_RSTW_US);

        SDHC_CORE_EMMC_CTRL_R(base) = _CLR_SET_FLD16U(SDHC_CORE_EMMC_CTRL_R(base),
                                                 SDHC_CORE_EMMC_CTRL_R_EMMC_RST_N,
                                                 1UL);

        /* Wait RST_n to Command time (74 cycles of clock signal required
         * before issuing CMD1 or CMD0 with argument 0xFFFFFFFA) - 200 us
         */
        Cy_SysLib_DelayUs(CY_SD_HOST_EMMC_T_RSCA_US);
}

/** \} group_sd_host_low_level_functions */

/**
* \addtogroup group_sd_host_interrupt_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SD_Host_GetNormalInterruptStatus
****************************************************************************//**
*
*  Returns the normal Int Status register.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The Bit mask of the normal Int Status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetNormalInterruptStatus(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_NORMAL_INT_STAT_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_ClearNormalInterruptStatus
****************************************************************************//**
*
*  Clears the selected SD host normal status.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param status
*     The bitmask of statuses to clear.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_ClearNormalInterruptStatus(SDHC_Type *base, uint32_t status)
{
    SDHC_CORE_NORMAL_INT_STAT_R(base) = (uint16_t)status;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetNormalInterruptEnable
****************************************************************************//**
*
*  Sets the bit to be active in the Int status register.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param interrupt
*     The Bit field of which normal interrupt status to enable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_SetNormalInterruptEnable(SDHC_Type *base, uint32_t interrupt)
{
    SDHC_CORE_NORMAL_INT_STAT_EN_R(base) = (uint16_t)interrupt;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetNormalInterruptEnable
****************************************************************************//**
*
*  Returns which normal interrupts are enabled.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The Bit field of which normal interrupt statuses are enabled.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetNormalInterruptEnable(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_NORMAL_INT_STAT_EN_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetNormalInterruptMask
****************************************************************************//**
*
*  Setting a bit in this register allows the enabled status to cause an interrupt.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param interruptMask
*     The Bit field of which normal interrupts can cause an interrupt.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_SetNormalInterruptMask(SDHC_Type *base, uint32_t interruptMask)
{
    SDHC_CORE_NORMAL_INT_SIGNAL_EN_R(base) = (uint16_t)interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetNormalInterruptMask
****************************************************************************//**
*
*  Returns which normal interrupts are masked to cause an interrupt.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The Bit field of which normal interrupts are masked to cause an interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetNormalInterruptMask(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_NORMAL_INT_SIGNAL_EN_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetErrorInterruptStatus
****************************************************************************//**
*
*  Returns the error Int Status register.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The bit mask of the error Int status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetErrorInterruptStatus(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_ERROR_INT_STAT_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_ClearErrorInterruptStatus
****************************************************************************//**
*
*  Clears the error interrupt status.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param status
*     The bitmask of statuses to clear.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_ClearErrorInterruptStatus(SDHC_Type *base, uint32_t status)
{
    SDHC_CORE_ERROR_INT_STAT_R(base) = (uint16_t)status;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetErrorInterruptEnable
****************************************************************************//**
*
*  Setting a bit in this register allows for the bit to be active in
*  the Int status register.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param interrupt
*     The Bit field of which error interrupt status to enable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_SetErrorInterruptEnable(SDHC_Type *base, uint32_t interrupt)
{
    SDHC_CORE_ERROR_INT_STAT_EN_R(base) = (uint16_t)interrupt;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetErrorInterruptEnable
****************************************************************************//**
*
*  Returns which error interrupts are enabled.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The Bit field of which error interrupt statuses are enabled.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetErrorInterruptEnable(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_ERROR_INT_STAT_EN_R(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetErrorInterruptMask
****************************************************************************//**
*
* Setting a bit in this register allows the enabled status to cause an interrupt.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param interruptMask
*     The Bit filed of which error interrupts can cause an interrupt.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SD_Host_SetErrorInterruptMask(SDHC_Type *base, uint32_t interruptMask)
{
    SDHC_CORE_ERROR_INT_SIGNAL_EN_R(base) = (uint16_t)interruptMask;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetErrorInterruptMask
****************************************************************************//**
*
*  Returns which error interrupts are masked to cause an interrupt.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The Bit field of which error interrupts are masked to cause an interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SD_Host_GetErrorInterruptMask(SDHC_Type const *base)
{
    uint32_t ret;

    ret = (uint32_t)SDHC_CORE_ERROR_INT_SIGNAL_EN_R(base);

    return ret;
}

/** \} group_sd_host_interrupt_functions */

#ifdef __cplusplus
}
#endif

/** \} group_sd_host */

#endif /* defined (CY_IP_MXSDHC) */

#endif /* CY_SD_HOST_PDL_H */


/* [] END OF FILE */
