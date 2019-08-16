/*
 * Copyright (c) 2013-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $Date:        2. Feb 2017
 * $Revision:    V2.3
 *
 * Project:      MCI (Memory Card Interface) Driver definitions
 */

/* History:
 *  Version 2.3
 *    ARM_MCI_STATUS made volatile
 *  Version 2.2
 *    Added timeout and error flags to ARM_MCI_STATUS
 *    Added support for controlling optional RST_n pin (eMMC)
 *    Removed explicit Clock Control (ARM_MCI_CONTROL_CLOCK)
 *    Removed event ARM_MCI_EVENT_BOOT_ACK_TIMEOUT
 *  Version 2.1
 *    Decoupled SPI mode from MCI driver
 *    Replaced function ARM_MCI_CardSwitchRead with ARM_MCI_ReadCD and ARM_MCI_ReadWP
 *  Version 2.0
 *    Added support for:
 *      SD UHS-I (Ultra High Speed)
 *      SD I/O Interrupt
 *      Read Wait (SD I/O)
 *      Suspend/Resume (SD I/O)
 *      MMC Interrupt
 *      MMC Boot
 *      Stream Data transfer (MMC)
 *      VCCQ Power Supply Control (eMMC)
 *      Command Completion Signal (CCS) for CE-ATA
 *    Added ARM_MCI_Control function
 *    Added ARM_MCI_GetStatus function
 *    Removed ARM_MCI_BusMode, ARM_MCI_BusDataWidth, ARM_MCI_BusSingaling functions
 *      (replaced by ARM_MCI_Control)
 *    Changed ARM_MCI_CardPower function (voltage parameter)
 *    Changed ARM_MCI_SendCommnad function (flags parameter)
 *    Changed ARM_MCI_SetupTransfer function (mode parameter)
 *    Removed ARM_MCI_ReadTransfer and ARM_MCI_WriteTransfer functions
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *    Changed return values of some functions to int32_t
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_MCI_H_
#define DRIVER_MCI_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_MCI_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,3)  /* API version */


/****** MCI Send Command Flags *****/
#define ARM_MCI_RESPONSE_Pos             0
#define ARM_MCI_RESPONSE_Msk            (3UL << ARM_MCI_RESPONSE_Pos)
#define ARM_MCI_RESPONSE_NONE           (0UL << ARM_MCI_RESPONSE_Pos)   ///< No response expected (default)
#define ARM_MCI_RESPONSE_SHORT          (1UL << ARM_MCI_RESPONSE_Pos)   ///< Short response (48-bit)
#define ARM_MCI_RESPONSE_SHORT_BUSY     (2UL << ARM_MCI_RESPONSE_Pos)   ///< Short response with busy signal (48-bit)
#define ARM_MCI_RESPONSE_LONG           (3UL << ARM_MCI_RESPONSE_Pos)   ///< Long response (136-bit)

#define ARM_MCI_RESPONSE_INDEX          (1UL << 2)  ///< Check command index in response
#define ARM_MCI_RESPONSE_CRC            (1UL << 3)  ///< Check CRC in response

#define ARM_MCI_WAIT_BUSY               (1UL << 4)  ///< Wait until busy before sending the command

#define ARM_MCI_TRANSFER_DATA           (1UL << 5)  ///< Activate Data transfer

#define ARM_MCI_CARD_INITIALIZE         (1UL << 6)  ///< Execute Memory Card initialization sequence

#define ARM_MCI_INTERRUPT_COMMAND       (1UL << 7)  ///< Send Interrupt command (CMD40 - MMC only)
#define ARM_MCI_INTERRUPT_RESPONSE      (1UL << 8)  ///< Send Interrupt response (CMD40 - MMC only)

#define ARM_MCI_BOOT_OPERATION          (1UL << 9)  ///< Execute Boot operation (MMC only)
#define ARM_MCI_BOOT_ALTERNATIVE        (1UL << 10) ///< Execute Alternative Boot operation (MMC only)
#define ARM_MCI_BOOT_ACK                (1UL << 11) ///< Expect Boot Acknowledge (MMC only)

#define ARM_MCI_CCSD                    (1UL << 12) ///< Send Command Completion Signal Disable (CCSD) for CE-ATA device
#define ARM_MCI_CCS                     (1UL << 13) ///< Expect Command Completion Signal (CCS) for CE-ATA device


/****** MCI Setup Transfer Mode *****/
#define ARM_MCI_TRANSFER_READ           (0UL << 0)  ///< Data Read Transfer (from MCI)
#define ARM_MCI_TRANSFER_WRITE          (1UL << 0)  ///< Data Write Transfer (to MCI)
#define ARM_MCI_TRANSFER_BLOCK          (0UL << 1)  ///< Block Data transfer (default)
#define ARM_MCI_TRANSFER_STREAM         (1UL << 1)  ///< Stream Data transfer (MMC only)


/****** MCI Control Codes *****/
#define ARM_MCI_BUS_SPEED               (0x01)      ///< Set Bus Speed; arg = requested speed in bits/s; returns configured speed in bits/s
#define ARM_MCI_BUS_SPEED_MODE          (0x02)      ///< Set Bus Speed Mode as specified with arg
#define ARM_MCI_BUS_CMD_MODE            (0x03)      ///< Set CMD Line Mode as specified with arg
#define ARM_MCI_BUS_DATA_WIDTH          (0x04)      ///< Set Bus Data Width as specified with arg
#define ARM_MCI_DRIVER_STRENGTH         (0x05)      ///< Set SD UHS-I Driver Strength as specified with arg 
#define ARM_MCI_CONTROL_RESET           (0x06)      ///< Control optional RST_n Pin (eMMC); arg: 0=inactive, 1=active 
#define ARM_MCI_CONTROL_CLOCK_IDLE      (0x07)      ///< Control Clock generation on CLK Pin when idle; arg: 0=disabled, 1=enabled
#define ARM_MCI_UHS_TUNING_OPERATION    (0x08)      ///< Sampling clock Tuning operation (SD UHS-I); arg: 0=reset, 1=execute
#define ARM_MCI_UHS_TUNING_RESULT       (0x09)      ///< Sampling clock Tuning result (SD UHS-I); returns: 0=done, 1=in progress, -1=error
#define ARM_MCI_DATA_TIMEOUT            (0x0A)      ///< Set Data timeout; arg = timeout in bus cycles
#define ARM_MCI_CSS_TIMEOUT             (0x0B)      ///< Set Command Completion Signal (CCS) timeout; arg = timeout in bus cycles
#define ARM_MCI_MONITOR_SDIO_INTERRUPT  (0x0C)      ///< Monitor SD I/O interrupt: arg: 0=disabled, 1=enabled
#define ARM_MCI_CONTROL_READ_WAIT       (0x0D)      ///< Control Read/Wait for SD I/O; arg: 0=disabled, 1=enabled
#define ARM_MCI_SUSPEND_TRANSFER        (0x0E)      ///< Suspend Data transfer (SD I/O); returns number of remaining bytes to transfer
#define ARM_MCI_RESUME_TRANSFER         (0x0F)      ///< Resume Data transfer (SD I/O)

/*----- MCI Bus Speed Mode -----*/
#define ARM_MCI_BUS_DEFAULT_SPEED       (0x00)      ///< SD/MMC: Default Speed mode up to 25/26MHz
#define ARM_MCI_BUS_HIGH_SPEED          (0x01)      ///< SD/MMC: High    Speed mode up to 50/52MHz
#define ARM_MCI_BUS_UHS_SDR12           (0x02)      ///< SD: SDR12  (Single Data Rate) up to  25MHz,  12.5MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define ARM_MCI_BUS_UHS_SDR25           (0x03)      ///< SD: SDR25  (Single Data Rate) up to  50MHz,  25  MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define ARM_MCI_BUS_UHS_SDR50           (0x04)      ///< SD: SDR50  (Single Data Rate) up to 100MHz,  50  MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define ARM_MCI_BUS_UHS_SDR104          (0x05)      ///< SD: SDR104 (Single Data Rate) up to 208MHz, 104  MB/s: UHS-I (Ultra High Speed) 1.8V signaling
#define ARM_MCI_BUS_UHS_DDR50           (0x06)      ///< SD: DDR50  (Dual Data Rate)   up to  50MHz,  50  MB/s: UHS-I (Ultra High Speed) 1.8V signaling

/*----- MCI CMD Line Mode -----*/
#define ARM_MCI_BUS_CMD_PUSH_PULL       (0x00)      ///< Push-Pull CMD line (default)
#define ARM_MCI_BUS_CMD_OPEN_DRAIN      (0x01)      ///< Open Drain CMD line (MMC only)

/*----- MCI Bus Data Width -----*/
#define ARM_MCI_BUS_DATA_WIDTH_1        (0x00)      ///< Bus data width: 1 bit (default)
#define ARM_MCI_BUS_DATA_WIDTH_4        (0x01)      ///< Bus data width: 4 bits
#define ARM_MCI_BUS_DATA_WIDTH_8        (0x02)      ///< Bus data width: 8 bits
#define ARM_MCI_BUS_DATA_WIDTH_4_DDR    (0x03)      ///< Bus data width: 4 bits, DDR (Dual Data Rate) - MMC only
#define ARM_MCI_BUS_DATA_WIDTH_8_DDR    (0x04)      ///< Bus data width: 8 bits, DDR (Dual Data Rate) - MMC only

/*----- MCI Driver Strength -----*/
#define ARM_MCI_DRIVER_TYPE_A           (0x01)      ///< SD UHS-I Driver Type A
#define ARM_MCI_DRIVER_TYPE_B           (0x00)      ///< SD UHS-I Driver Type B (default)
#define ARM_MCI_DRIVER_TYPE_C           (0x02)      ///< SD UHS-I Driver Type C
#define ARM_MCI_DRIVER_TYPE_D           (0x03)      ///< SD UHS-I Driver Type D


/****** MCI Card Power *****/
#define ARM_MCI_POWER_VDD_Pos            0
#define ARM_MCI_POWER_VDD_Msk           (0x0FUL << ARM_MCI_POWER_VDD_Pos)
#define ARM_MCI_POWER_VDD_OFF           (0x01UL << ARM_MCI_POWER_VDD_Pos)   ///< VDD (VCC) turned off
#define ARM_MCI_POWER_VDD_3V3           (0x02UL << ARM_MCI_POWER_VDD_Pos)   ///< VDD (VCC) = 3.3V
#define ARM_MCI_POWER_VDD_1V8           (0x03UL << ARM_MCI_POWER_VDD_Pos)   ///< VDD (VCC) = 1.8V
#define ARM_MCI_POWER_VCCQ_Pos           4
#define ARM_MCI_POWER_VCCQ_Msk          (0x0FUL << ARM_MCI_POWER_VCCQ_Pos)
#define ARM_MCI_POWER_VCCQ_OFF          (0x01UL << ARM_MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ turned off
#define ARM_MCI_POWER_VCCQ_3V3          (0x02UL << ARM_MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ = 3.3V
#define ARM_MCI_POWER_VCCQ_1V8          (0x03UL << ARM_MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ = 1.8V
#define ARM_MCI_POWER_VCCQ_1V2          (0x04UL << ARM_MCI_POWER_VCCQ_Pos)  ///< eMMC VCCQ = 1.2V


/**
\brief MCI Status
*/
typedef volatile struct _ARM_MCI_STATUS {
  uint32_t command_active   : 1;        ///< Command active flag
  uint32_t command_timeout  : 1;        ///< Command timeout flag (cleared on start of next command)
  uint32_t command_error    : 1;        ///< Command error flag (cleared on start of next command)
  uint32_t transfer_active  : 1;        ///< Transfer active flag
  uint32_t transfer_timeout : 1;        ///< Transfer timeout flag (cleared on start of next command)
  uint32_t transfer_error   : 1;        ///< Transfer error flag (cleared on start of next command)
  uint32_t sdio_interrupt   : 1;        ///< SD I/O Interrupt flag (cleared on start of monitoring)
  uint32_t ccs              : 1;        ///< CCS flag (cleared on start of next command)
  uint32_t reserved         : 24;
} ARM_MCI_STATUS;


/****** MCI Card Event *****/
#define ARM_MCI_EVENT_CARD_INSERTED     (1UL << 0)  ///< Memory Card inserted
#define ARM_MCI_EVENT_CARD_REMOVED      (1UL << 1)  ///< Memory Card removed
#define ARM_MCI_EVENT_COMMAND_COMPLETE  (1UL << 2)  ///< Command completed
#define ARM_MCI_EVENT_COMMAND_TIMEOUT   (1UL << 3)  ///< Command timeout
#define ARM_MCI_EVENT_COMMAND_ERROR     (1UL << 4)  ///< Command response error (CRC error or invalid response)
#define ARM_MCI_EVENT_TRANSFER_COMPLETE (1UL << 5)  ///< Data transfer completed
#define ARM_MCI_EVENT_TRANSFER_TIMEOUT  (1UL << 6)  ///< Data transfer timeout
#define ARM_MCI_EVENT_TRANSFER_ERROR    (1UL << 7)  ///< Data transfer CRC failed
#define ARM_MCI_EVENT_SDIO_INTERRUPT    (1UL << 8)  ///< SD I/O Interrupt
#define ARM_MCI_EVENT_CCS               (1UL << 9)  ///< Command Completion Signal (CCS)
#define ARM_MCI_EVENT_CCS_TIMEOUT       (1UL << 10) ///< Command Completion Signal (CCS) Timeout


// Function documentation
/**
  \fn            ARM_DRIVER_VERSION ARM_MCI_GetVersion (void)
  \brief         Get driver version.
  \return        \ref ARM_DRIVER_VERSION
*/
/**
  \fn            ARM_MCI_CAPABILITIES ARM_MCI_GetCapabilities (void)
  \brief         Get driver capabilities.
  \return        \ref ARM_MCI_CAPABILITIES
*/
/**
  \fn            int32_t ARM_MCI_Initialize (ARM_MCI_SignalEvent_t cb_event)
  \brief         Initialize the Memory Card Interface
  \param[in]     cb_event  Pointer to \ref ARM_MCI_SignalEvent
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_Uninitialize (void)
  \brief         De-initialize Memory Card Interface.
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_PowerControl (ARM_POWER_STATE state)
  \brief         Control Memory Card Interface Power.
  \param[in]     state   Power state \ref ARM_POWER_STATE
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_CardPower (uint32_t voltage)
  \brief         Set Memory Card Power supply voltage.
  \param[in]     voltage  Memory Card Power supply voltage
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_ReadCD (void)
  \brief         Read Card Detect (CD) state.
  \return        1:card detected, 0:card not detected, or error
*/
/**
  \fn            int32_t ARM_MCI_ReadWP (void)
  \brief         Read Write Protect (WP) state.
  \return        1:write protected, 0:not write protected, or error
*/
/**
  \fn            int32_t ARM_MCI_SendCommand (uint32_t  cmd,
                                              uint32_t  arg,
                                              uint32_t  flags,
                                              uint32_t *response)
  \brief         Send Command to card and get the response.
  \param[in]     cmd       Memory Card command
  \param[in]     arg       Command argument
  \param[in]     flags     Command flags
  \param[out]    response  Pointer to buffer for response
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_SetupTransfer (uint8_t *data,
                                                uint32_t block_count,
                                                uint32_t block_size,
                                                uint32_t mode)
  \brief         Setup read or write transfer operation.
  \param[in,out] data         Pointer to data block(s) to be written or read
  \param[in]     block_count  Number of blocks
  \param[in]     block_size   Size of a block in bytes
  \param[in]     mode         Transfer mode
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_AbortTransfer (void)
  \brief         Abort current read/write data transfer.
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_MCI_Control (uint32_t control, uint32_t arg)
  \brief         Control MCI Interface.
  \param[in]     control  Operation
  \param[in]     arg      Argument of operation (optional)
  \return        \ref execution_status
*/
/**
  \fn            ARM_MCI_STATUS ARM_MCI_GetStatus (void)
  \brief         Get MCI status.
  \return        MCI status \ref ARM_MCI_STATUS
*/

/**
  \fn            void ARM_MCI_SignalEvent (uint32_t event)
  \brief         Callback function that signals a MCI Card Event.
  \param[in]     event \ref mci_event_gr
  \return        none
*/

typedef void (*ARM_MCI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref ARM_MCI_SignalEvent : Signal MCI Card Event.


/**
\brief  MCI Driver Capabilities.
*/
typedef struct _ARM_MCI_CAPABILITIES {
  uint32_t cd_state          : 1;       ///< Card Detect State available
  uint32_t cd_event          : 1;       ///< Signal Card Detect change event
  uint32_t wp_state          : 1;       ///< Write Protect State available
  uint32_t vdd               : 1;       ///< Supports VDD Card Power Supply Control
  uint32_t vdd_1v8           : 1;       ///< Supports 1.8 VDD Card Power Supply
  uint32_t vccq              : 1;       ///< Supports VCCQ Card Power Supply Control (eMMC)
  uint32_t vccq_1v8          : 1;       ///< Supports 1.8 VCCQ Card Power Supply (eMMC)
  uint32_t vccq_1v2          : 1;       ///< Supports 1.2 VCCQ Card Power Supply (eMMC)
  uint32_t data_width_4      : 1;       ///< Supports 4-bit data
  uint32_t data_width_8      : 1;       ///< Supports 8-bit data
  uint32_t data_width_4_ddr  : 1;       ///< Supports 4-bit data, DDR (Dual Data Rate) - MMC only
  uint32_t data_width_8_ddr  : 1;       ///< Supports 8-bit data, DDR (Dual Data Rate) - MMC only
  uint32_t high_speed        : 1;       ///< Supports SD/MMC High Speed Mode
  uint32_t uhs_signaling     : 1;       ///< Supports SD UHS-I (Ultra High Speed) 1.8V signaling 
  uint32_t uhs_tuning        : 1;       ///< Supports SD UHS-I tuning 
  uint32_t uhs_sdr50         : 1;       ///< Supports SD UHS-I SDR50  (Single Data Rate) up to  50MB/s
  uint32_t uhs_sdr104        : 1;       ///< Supports SD UHS-I SDR104 (Single Data Rate) up to 104MB/s
  uint32_t uhs_ddr50         : 1;       ///< Supports SD UHS-I DDR50  (Dual   Data Rate) up to  50MB/s
  uint32_t uhs_driver_type_a : 1;       ///< Supports SD UHS-I Driver Type A
  uint32_t uhs_driver_type_c : 1;       ///< Supports SD UHS-I Driver Type C
  uint32_t uhs_driver_type_d : 1;       ///< Supports SD UHS-I Driver Type D 
  uint32_t sdio_interrupt    : 1;       ///< Supports SD I/O Interrupt 
  uint32_t read_wait         : 1;       ///< Supports Read Wait (SD I/O)
  uint32_t suspend_resume    : 1;       ///< Supports Suspend/Resume (SD I/O)
  uint32_t mmc_interrupt     : 1;       ///< Supports MMC Interrupt 
  uint32_t mmc_boot          : 1;       ///< Supports MMC Boot 
  uint32_t rst_n             : 1;       ///< Supports RST_n Pin Control (eMMC)
  uint32_t ccs               : 1;       ///< Supports Command Completion Signal (CCS) for CE-ATA
  uint32_t ccs_timeout       : 1;       ///< Supports Command Completion Signal (CCS) timeout for CE-ATA
  uint32_t reserved          : 3;       ///< Reserved (must be zero)
} ARM_MCI_CAPABILITIES;


/**
\brief  Access structure of the MCI Driver.
*/
typedef struct _ARM_DRIVER_MCI {
  ARM_DRIVER_VERSION   (*GetVersion)     (void);                           ///< Pointer to \ref ARM_MCI_GetVersion : Get driver version.
  ARM_MCI_CAPABILITIES (*GetCapabilities)(void);                           ///< Pointer to \ref ARM_MCI_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)     (ARM_MCI_SignalEvent_t cb_event); ///< Pointer to \ref ARM_MCI_Initialize : Initialize MCI Interface.
  int32_t              (*Uninitialize)   (void);                           ///< Pointer to \ref ARM_MCI_Uninitialize : De-initialize MCI Interface.
  int32_t              (*PowerControl)   (ARM_POWER_STATE state);          ///< Pointer to \ref ARM_MCI_PowerControl : Control MCI Interface Power.
  int32_t              (*CardPower)      (uint32_t voltage);               ///< Pointer to \ref ARM_MCI_CardPower : Set card power supply voltage.
  int32_t              (*ReadCD)         (void);                           ///< Pointer to \ref ARM_MCI_ReadCD : Read Card Detect (CD) state.
  int32_t              (*ReadWP)         (void);                           ///< Pointer to \ref ARM_MCI_ReadWP : Read Write Protect (WP) state.
  int32_t              (*SendCommand)    (uint32_t cmd, 
                                          uint32_t arg, 
                                          uint32_t flags,
                                          uint32_t *response);             ///< Pointer to \ref ARM_MCI_SendCommand : Send Command to card and get the response.
  int32_t              (*SetupTransfer)  (uint8_t *data,
                                          uint32_t block_count,
                                          uint32_t block_size,
                                          uint32_t mode);                  ///< Pointer to \ref ARM_MCI_SetupTransfer : Setup data transfer operation.
  int32_t              (*AbortTransfer)  (void);                           ///< Pointer to \ref ARM_MCI_AbortTransfer : Abort current data transfer.
  int32_t              (*Control)        (uint32_t control, uint32_t arg); ///< Pointer to \ref ARM_MCI_Control : Control MCI Interface.
  ARM_MCI_STATUS       (*GetStatus)      (void);                           ///< Pointer to \ref ARM_MCI_GetStatus : Get MCI status.
} const ARM_DRIVER_MCI;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_MCI_H_ */
