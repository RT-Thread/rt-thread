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
 * $Date:        14. Nov 2017
 * $Revision:    V2.3
 *
 * Project:      NAND Flash Driver definitions
 */

/* History:
 *  Version 2.3
 *    Extended ARM_NAND_ECC_INFO structure
 *  Version 2.2
 *    ARM_NAND_STATUS made volatile
 *  Version 2.1
 *    Updated ARM_NAND_ECC_INFO structure and ARM_NAND_ECC_xxx definitions
 *  Version 2.0
 *    New simplified driver:
 *      complexity moved to upper layer (command agnostic)
 *    Added support for:
 *      NV-DDR & NV-DDR2 Interface (ONFI specification)
 *      VCC, VCCQ and VPP Power Supply Control
 *      WP (Write Protect) Control
 *  Version 1.11
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef DRIVER_NAND_H_
#define DRIVER_NAND_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_NAND_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,3)  /* API version */


/****** NAND Device Power *****/
#define ARM_NAND_POWER_VCC_Pos           0
#define ARM_NAND_POWER_VCC_Msk          (0x07UL << ARM_NAND_POWER_VCC_Pos)
#define ARM_NAND_POWER_VCC_OFF          (0x01UL << ARM_NAND_POWER_VCC_Pos)  ///< VCC Power off
#define ARM_NAND_POWER_VCC_3V3          (0x02UL << ARM_NAND_POWER_VCC_Pos)  ///< VCC = 3.3V
#define ARM_NAND_POWER_VCC_1V8          (0x03UL << ARM_NAND_POWER_VCC_Pos)  ///< VCC = 1.8V
#define ARM_NAND_POWER_VCCQ_Pos          3
#define ARM_NAND_POWER_VCCQ_Msk         (0x07UL << ARM_NAND_POWER_VCCQ_Pos)
#define ARM_NAND_POWER_VCCQ_OFF         (0x01UL << ARM_NAND_POWER_VCCQ_Pos) ///< VCCQ I/O Power off
#define ARM_NAND_POWER_VCCQ_3V3         (0x02UL << ARM_NAND_POWER_VCCQ_Pos) ///< VCCQ = 3.3V
#define ARM_NAND_POWER_VCCQ_1V8         (0x03UL << ARM_NAND_POWER_VCCQ_Pos) ///< VCCQ = 1.8V
#define ARM_NAND_POWER_VPP_OFF          (1UL << 6)                          ///< VPP off
#define ARM_NAND_POWER_VPP_ON           (1Ul << 7)                          ///< VPP on


/****** NAND Control Codes *****/
#define ARM_NAND_BUS_MODE               (0x01)      ///< Set Bus Mode as specified with arg
#define ARM_NAND_BUS_DATA_WIDTH         (0x02)      ///< Set Bus Data Width as specified with arg
#define ARM_NAND_DRIVER_STRENGTH        (0x03)      ///< Set Driver Strength as specified with arg
#define ARM_NAND_DEVICE_READY_EVENT     (0x04)      ///< Generate \ref ARM_NAND_EVENT_DEVICE_READY; arg: 0=disabled (default), 1=enabled 
#define ARM_NAND_DRIVER_READY_EVENT     (0x05)      ///< Generate \ref ARM_NAND_EVENT_DRIVER_READY; arg: 0=disabled (default), 1=enabled 

/*----- NAND Bus Mode (ONFI - Open NAND Flash Interface) -----*/
#define ARM_NAND_BUS_INTERFACE_Pos       4
#define ARM_NAND_BUS_INTERFACE_Msk      (0x03UL << ARM_NAND_BUS_INTERFACE_Pos)
#define ARM_NAND_BUS_SDR                (0x00UL << ARM_NAND_BUS_INTERFACE_Pos)    ///< Data Interface:    SDR  (Single Data Rate) - Traditional interface (default)
#define ARM_NAND_BUS_DDR                (0x01UL << ARM_NAND_BUS_INTERFACE_Pos)    ///< Data Interface: NV-DDR  (Double Data Rate)
#define ARM_NAND_BUS_DDR2               (0x02UL << ARM_NAND_BUS_INTERFACE_Pos)    ///< Data Interface: NV-DDR2 (Double Data Rate)
#define ARM_NAND_BUS_TIMING_MODE_Pos     0
#define ARM_NAND_BUS_TIMING_MODE_Msk    (0x0FUL << ARM_NAND_BUS_TIMING_MODE_Pos)
#define ARM_NAND_BUS_TIMING_MODE_0      (0x00UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 0 (default)
#define ARM_NAND_BUS_TIMING_MODE_1      (0x01UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 1
#define ARM_NAND_BUS_TIMING_MODE_2      (0x02UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 2
#define ARM_NAND_BUS_TIMING_MODE_3      (0x03UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 3
#define ARM_NAND_BUS_TIMING_MODE_4      (0x04UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 4 (SDR EDO capable)
#define ARM_NAND_BUS_TIMING_MODE_5      (0x05UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 5 (SDR EDO capable)
#define ARM_NAND_BUS_TIMING_MODE_6      (0x06UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 6 (NV-DDR2 only)
#define ARM_NAND_BUS_TIMING_MODE_7      (0x07UL << ARM_NAND_BUS_TIMING_MODE_Pos)  ///< Timing Mode 7 (NV-DDR2 only)
#define ARM_NAND_BUS_DDR2_DO_WCYC_Pos    8
#define ARM_NAND_BUS_DDR2_DO_WCYC_Msk   (0x0FUL << ARM_NAND_BUS_DDR2_DO_WCYC_Pos)
#define ARM_NAND_BUS_DDR2_DO_WCYC_0     (0x00UL << ARM_NAND_BUS_DDR2_DO_WCYC_Pos) ///< DDR2 Data Output Warm-up cycles: 0 (default)
#define ARM_NAND_BUS_DDR2_DO_WCYC_1     (0x01UL << ARM_NAND_BUS_DDR2_DO_WCYC_Pos) ///< DDR2 Data Output Warm-up cycles: 1
#define ARM_NAND_BUS_DDR2_DO_WCYC_2     (0x02UL << ARM_NAND_BUS_DDR2_DO_WCYC_Pos) ///< DDR2 Data Output Warm-up cycles: 2
#define ARM_NAND_BUS_DDR2_DO_WCYC_4     (0x03UL << ARM_NAND_BUS_DDR2_DO_WCYC_Pos) ///< DDR2 Data Output Warm-up cycles: 4
#define ARM_NAND_BUS_DDR2_DI_WCYC_Pos    12
#define ARM_NAND_BUS_DDR2_DI_WCYC_Msk   (0x0FUL << ARM_NAND_BUS_DDR2_DI_WCYC_Pos)
#define ARM_NAND_BUS_DDR2_DI_WCYC_0     (0x00UL << ARM_NAND_BUS_DDR2_DI_WCYC_Pos) ///< DDR2 Data Input Warm-up cycles: 0 (default)
#define ARM_NAND_BUS_DDR2_DI_WCYC_1     (0x01UL << ARM_NAND_BUS_DDR2_DI_WCYC_Pos) ///< DDR2 Data Input Warm-up cycles: 1
#define ARM_NAND_BUS_DDR2_DI_WCYC_2     (0x02UL << ARM_NAND_BUS_DDR2_DI_WCYC_Pos) ///< DDR2 Data Input Warm-up cycles: 2
#define ARM_NAND_BUS_DDR2_DI_WCYC_4     (0x03UL << ARM_NAND_BUS_DDR2_DI_WCYC_Pos) ///< DDR2 Data Input Warm-up cycles: 4
#define ARM_NAND_BUS_DDR2_VEN           (1UL << 16)                               ///< DDR2 Enable external VREFQ as reference
#define ARM_NAND_BUS_DDR2_CMPD          (1UL << 17)                               ///< DDR2 Enable complementary DQS (DQS_c) signal
#define ARM_NAND_BUS_DDR2_CMPR          (1UL << 18)                               ///< DDR2 Enable complementary RE_n (RE_c) signal

/*----- NAND Data Bus Width -----*/
#define ARM_NAND_BUS_DATA_WIDTH_8       (0x00)      ///< Bus Data Width:  8 bit (default)
#define ARM_NAND_BUS_DATA_WIDTH_16      (0x01)      ///< Bus Data Width: 16 bit

/*----- NAND Driver Strength (ONFI - Open NAND Flash Interface) -----*/
#define ARM_NAND_DRIVER_STRENGTH_18     (0x00)      ///< Driver Strength 2.0x = 18 Ohms
#define ARM_NAND_DRIVER_STRENGTH_25     (0x01)      ///< Driver Strength 1.4x = 25 Ohms
#define ARM_NAND_DRIVER_STRENGTH_35     (0x02)      ///< Driver Strength 1.0x = 35 Ohms (default)
#define ARM_NAND_DRIVER_STRENGTH_50     (0x03)      ///< Driver Strength 0.7x = 50 Ohms


/****** NAND ECC for Read/Write Data Mode and Sequence Execution Code *****/
#define ARM_NAND_ECC_INDEX_Pos           0
#define ARM_NAND_ECC_INDEX_Msk          (0xFFUL << ARM_NAND_ECC_INDEX_Pos)
#define ARM_NAND_ECC(n)                 ((n) & ARM_NAND_ECC_INDEX_Msk)     ///< Select ECC
#define ARM_NAND_ECC0                   (1UL << 8)                         ///< Use ECC0 of selected ECC
#define ARM_NAND_ECC1                   (1UL << 9)                         ///< Use ECC1 of selected ECC

/****** NAND Flag for Read/Write Data Mode and Sequence Execution Code *****/
#define ARM_NAND_DRIVER_DONE_EVENT      (1UL << 16) ///< Generate \ref ARM_NAND_EVENT_DRIVER_DONE

/****** NAND Sequence Execution Code *****/
#define ARM_NAND_CODE_SEND_CMD1         (1UL << 17) ///< Send Command 1
#define ARM_NAND_CODE_SEND_ADDR_COL1    (1UL << 18) ///< Send Column Address 1
#define ARM_NAND_CODE_SEND_ADDR_COL2    (1UL << 19) ///< Send Column Address 2
#define ARM_NAND_CODE_SEND_ADDR_ROW1    (1UL << 20) ///< Send Row Address 1
#define ARM_NAND_CODE_SEND_ADDR_ROW2    (1UL << 21) ///< Send Row Address 2
#define ARM_NAND_CODE_SEND_ADDR_ROW3    (1UL << 22) ///< Send Row Address 3
#define ARM_NAND_CODE_INC_ADDR_ROW      (1UL << 23) ///< Auto-increment Row Address
#define ARM_NAND_CODE_WRITE_DATA        (1UL << 24) ///< Write Data
#define ARM_NAND_CODE_SEND_CMD2         (1UL << 25) ///< Send Command 2
#define ARM_NAND_CODE_WAIT_BUSY         (1UL << 26) ///< Wait while R/Bn busy
#define ARM_NAND_CODE_READ_DATA         (1UL << 27) ///< Read Data
#define ARM_NAND_CODE_SEND_CMD3         (1UL << 28) ///< Send Command 3
#define ARM_NAND_CODE_READ_STATUS       (1UL << 29) ///< Read Status byte and check FAIL bit (bit 0)

/*----- NAND Sequence Execution Code: Command -----*/
#define ARM_NAND_CODE_CMD1_Pos           0
#define ARM_NAND_CODE_CMD1_Msk          (0xFFUL << ARM_NAND_CODE_CMD1_Pos)
#define ARM_NAND_CODE_CMD2_Pos           8
#define ARM_NAND_CODE_CMD2_Msk          (0xFFUL << ARM_NAND_CODE_CMD2_Pos)
#define ARM_NAND_CODE_CMD3_Pos           16
#define ARM_NAND_CODE_CMD3_Msk          (0xFFUL << ARM_NAND_CODE_CMD3_Pos)

/*----- NAND Sequence Execution Code: Column Address -----*/
#define ARM_NAND_CODE_ADDR_COL1_Pos      0
#define ARM_NAND_CODE_ADDR_COL1_Msk     (0xFFUL << ARM_NAND_CODE_ADDR_COL1_Pos)
#define ARM_NAND_CODE_ADDR_COL2_Pos      8
#define ARM_NAND_CODE_ADDR_COL2_Msk     (0xFFUL << ARM_NAND_CODE_ADDR_COL2_Pos)

/*----- NAND Sequence Execution Code: Row Address -----*/
#define ARM_NAND_CODE_ADDR_ROW1_Pos      0
#define ARM_NAND_CODE_ADDR_ROW1_Msk     (0xFFUL << ARM_NAND_CODE_ADDR_ROW1_Pos)
#define ARM_NAND_CODE_ADDR_ROW2_Pos      8
#define ARM_NAND_CODE_ADDR_ROW2_Msk     (0xFFUL << ARM_NAND_CODE_ADDR_ROW2_Pos)
#define ARM_NAND_CODE_ADDR_ROW3_Pos      16
#define ARM_NAND_CODE_ADDR_ROW3_Msk     (0xFFUL << ARM_NAND_CODE_ADDR_ROW3_Pos)


/****** NAND specific error codes *****/
#define ARM_NAND_ERROR_ECC              (ARM_DRIVER_ERROR_SPECIFIC - 1)     ///< ECC generation/correction failed


/**
\brief NAND ECC (Error Correction Code) Information
*/
typedef struct _ARM_NAND_ECC_INFO {
  uint32_t type             :  2;       ///< Type: 1=ECC0 over Main, 2=ECC0 over Main+Spare, 3=ECC0 over Main and ECC1 over Spare
  uint32_t page_layout      :  1;       ///< Page layout: 0=|Main0|Spare0|...|MainN-1|SpareN-1|, 1=|Main0|...|MainN-1|Spare0|...|SpareN-1|
  uint32_t page_count       :  3;       ///< Number of virtual pages: N = 2 ^ page_count
  uint32_t page_size        :  4;       ///< Virtual Page size (Main+Spare): 0=512+16, 1=1k+32, 2=2k+64, 3=4k+128, 4=8k+256, 8=512+28, 9=1k+56, 10=2k+112, 11=4k+224, 12=8k+448, 15=Not used (extended description)
  uint32_t reserved         : 14;       ///< Reserved (must be zero)
  uint32_t correctable_bits :  8;       ///< Number of correctable bits (based on 512 byte codeword size)
  uint16_t codeword_size     [2];       ///< Number of bytes over which ECC is calculated
  uint16_t ecc_size          [2];       ///< ECC size in bytes (rounded up)
  uint16_t ecc_offset        [2];       ///< ECC offset in bytes (where ECC starts in Spare)
  /* Extended description */
  uint16_t virtual_page_size [2];       ///< Virtual Page size in bytes (Main/Spare)
  uint16_t codeword_offset   [2];       ///< Codeword offset in bytes (where ECC protected data starts in Main/Spare)
  uint16_t codeword_gap      [2];       ///< Codeword gap in bytes till next protected data
  uint16_t ecc_gap           [2];       ///< ECC gap in bytes till next generated ECC
} ARM_NAND_ECC_INFO;


/**
\brief NAND Status
*/
typedef volatile struct _ARM_NAND_STATUS {
  uint32_t busy      : 1;               ///< Driver busy flag
  uint32_t ecc_error : 1;               ///< ECC error detected (cleared on next Read/WriteData or ExecuteSequence)
  uint32_t reserved  : 30;
} ARM_NAND_STATUS;


/****** NAND Event *****/
#define ARM_NAND_EVENT_DEVICE_READY     (1UL << 0)  ///< Device Ready: R/Bn rising edge
#define ARM_NAND_EVENT_DRIVER_READY     (1UL << 1)  ///< Driver Ready
#define ARM_NAND_EVENT_DRIVER_DONE      (1UL << 2)  ///< Driver operation done
#define ARM_NAND_EVENT_ECC_ERROR        (1UL << 3)  ///< ECC could not correct data


// Function documentation
/**
  \fn            ARM_DRIVER_VERSION ARM_NAND_GetVersion (void)
  \brief         Get driver version.
  \return        \ref ARM_DRIVER_VERSION
*/
/**
  \fn            ARM_NAND_CAPABILITIES ARM_NAND_GetCapabilities (void)
  \brief         Get driver capabilities.
  \return        \ref ARM_NAND_CAPABILITIES
*/
/**
  \fn            int32_t ARM_NAND_Initialize (ARM_NAND_SignalEvent_t cb_event)
  \brief         Initialize the NAND Interface.
  \param[in]     cb_event  Pointer to \ref ARM_NAND_SignalEvent
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_Uninitialize (void)
  \brief         De-initialize the NAND Interface.
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_PowerControl (ARM_POWER_STATE state)
  \brief         Control the NAND interface power.
  \param[in]     state  Power state
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_DevicePower (uint32_t voltage)
  \brief         Set device power supply voltage.
  \param[in]     voltage  NAND Device supply voltage
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_WriteProtect (uint32_t dev_num, bool enable)
  \brief         Control WPn (Write Protect).
  \param[in]     dev_num  Device number
  \param[in]     enable
                - \b false Write Protect off
                - \b true  Write Protect on
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_ChipEnable (uint32_t dev_num, bool enable)
  \brief         Control CEn (Chip Enable).
  \param[in]     dev_num  Device number
  \param[in]     enable
                - \b false Chip Enable off
                - \b true  Chip Enable on
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_GetDeviceBusy (uint32_t dev_num)
  \brief         Get Device Busy pin state.
  \param[in]     dev_num  Device number
  \return        1=busy, 0=not busy, or error
*/
/**
  \fn            int32_t ARM_NAND_SendCommand (uint32_t dev_num, uint8_t cmd)
  \brief         Send command to NAND device.
  \param[in]     dev_num  Device number
  \param[in]     cmd      Command
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_SendAddress (uint32_t dev_num, uint8_t addr)
  \brief         Send address to NAND device.
  \param[in]     dev_num  Device number
  \param[in]     addr     Address
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_ReadData (uint32_t dev_num, void *data, uint32_t cnt, uint32_t mode)
  \brief         Read data from NAND device.
  \param[in]     dev_num  Device number
  \param[out]    data     Pointer to buffer for data to read from NAND device
  \param[in]     cnt      Number of data items to read
  \param[in]     mode     Operation mode
  \return        number of data items read or \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_WriteData (uint32_t dev_num, const void *data, uint32_t cnt, uint32_t mode)
  \brief         Write data to NAND device.
  \param[in]     dev_num  Device number
  \param[out]    data     Pointer to buffer with data to write to NAND device
  \param[in]     cnt      Number of data items to write
  \param[in]     mode     Operation mode
  \return        number of data items written or \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_ExecuteSequence (uint32_t dev_num, uint32_t code, uint32_t cmd,
                                                   uint32_t addr_col, uint32_t addr_row,
                                                   void *data, uint32_t data_cnt,
                                                   uint8_t *status, uint32_t *count)
  \brief         Execute sequence of operations.
  \param[in]     dev_num  Device number
  \param[in]     code     Sequence code
  \param[in]     cmd      Command(s)
  \param[in]     addr_col Column address
  \param[in]     addr_row Row address
  \param[in,out] data     Pointer to data to be written or read 
  \param[in]     data_cnt Number of data items in one iteration
  \param[out]    status   Pointer to status read
  \param[in,out] count    Number of iterations
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_AbortSequence (uint32_t dev_num)
  \brief         Abort sequence execution.
  \param[in]     dev_num  Device number
  \return        \ref execution_status
*/
/**
  \fn            int32_t ARM_NAND_Control (uint32_t dev_num, uint32_t control, uint32_t arg)
  \brief         Control NAND Interface.
  \param[in]     dev_num  Device number
  \param[in]     control  Operation
  \param[in]     arg      Argument of operation
  \return        \ref execution_status
*/
/**
  \fn            ARM_NAND_STATUS ARM_NAND_GetStatus (uint32_t dev_num)
  \brief         Get NAND status.
  \param[in]     dev_num  Device number
  \return        NAND status \ref ARM_NAND_STATUS
*/
/**
  \fn            int32_t ARM_NAND_InquireECC (int32_t index, ARM_NAND_ECC_INFO *info)
  \brief         Inquire about available ECC.
  \param[in]     index   Inquire ECC index
  \param[out]    info    Pointer to ECC information \ref ARM_NAND_ECC_INFO retrieved
  \return        \ref execution_status
*/

/**
  \fn            void ARM_NAND_SignalEvent (uint32_t dev_num, uint32_t event)
  \brief         Signal NAND event.
  \param[in]     dev_num  Device number
  \param[in]     event    Event notification mask
  \return        none
*/

typedef void (*ARM_NAND_SignalEvent_t) (uint32_t dev_num, uint32_t event);    ///< Pointer to \ref ARM_NAND_SignalEvent : Signal NAND Event.


/**
\brief NAND Driver Capabilities.
*/
typedef struct _ARM_NAND_CAPABILITIES {
  uint32_t event_device_ready  : 1;     ///< Signal Device Ready event (R/Bn rising edge)
  uint32_t reentrant_operation : 1;     ///< Supports re-entrant operation (SendCommand/Address, Read/WriteData)
  uint32_t sequence_operation  : 1;     ///< Supports Sequence operation (ExecuteSequence, AbortSequence)
  uint32_t vcc                 : 1;     ///< Supports VCC Power Supply Control
  uint32_t vcc_1v8             : 1;     ///< Supports 1.8 VCC Power Supply
  uint32_t vccq                : 1;     ///< Supports VCCQ I/O Power Supply Control
  uint32_t vccq_1v8            : 1;     ///< Supports 1.8 VCCQ I/O Power Supply
  uint32_t vpp                 : 1;     ///< Supports VPP High Voltage Power Supply Control
  uint32_t wp                  : 1;     ///< Supports WPn (Write Protect) Control
  uint32_t ce_lines            : 4;     ///< Number of CEn (Chip Enable) lines: ce_lines + 1
  uint32_t ce_manual           : 1;     ///< Supports manual CEn (Chip Enable) Control
  uint32_t rb_monitor          : 1;     ///< Supports R/Bn (Ready/Busy) Monitoring
  uint32_t data_width_16       : 1;     ///< Supports 16-bit data
  uint32_t ddr                 : 1;     ///< Supports NV-DDR  Data Interface (ONFI)
  uint32_t ddr2                : 1;     ///< Supports NV-DDR2 Data Interface (ONFI)
  uint32_t sdr_timing_mode     : 3;     ///< Fastest (highest) SDR     Timing Mode supported (ONFI)
  uint32_t ddr_timing_mode     : 3;     ///< Fastest (highest) NV_DDR  Timing Mode supported (ONFI)
  uint32_t ddr2_timing_mode    : 3;     ///< Fastest (highest) NV_DDR2 Timing Mode supported (ONFI)
  uint32_t driver_strength_18  : 1;     ///< Supports Driver Strength 2.0x = 18 Ohms
  uint32_t driver_strength_25  : 1;     ///< Supports Driver Strength 1.4x = 25 Ohms
  uint32_t driver_strength_50  : 1;     ///< Supports Driver Strength 0.7x = 50 Ohms
  uint32_t reserved            : 2;     ///< Reserved (must be zero)
} ARM_NAND_CAPABILITIES;


/**
\brief Access structure of the NAND Driver.
*/
typedef struct _ARM_DRIVER_NAND {
  ARM_DRIVER_VERSION    (*GetVersion)     (void);                                                             ///< Pointer to \ref ARM_NAND_GetVersion : Get driver version.
  ARM_NAND_CAPABILITIES (*GetCapabilities)(void);                                                             ///< Pointer to \ref ARM_NAND_GetCapabilities : Get driver capabilities.
  int32_t               (*Initialize)     (ARM_NAND_SignalEvent_t cb_event);                                  ///< Pointer to \ref ARM_NAND_Initialize : Initialize NAND Interface.
  int32_t               (*Uninitialize)   (void);                                                             ///< Pointer to \ref ARM_NAND_Uninitialize : De-initialize NAND Interface.
  int32_t               (*PowerControl)   (ARM_POWER_STATE state);                                            ///< Pointer to \ref ARM_NAND_PowerControl : Control NAND Interface Power.
  int32_t               (*DevicePower)    (uint32_t voltage);                                                 ///< Pointer to \ref ARM_NAND_DevicePower : Set device power supply voltage.
  int32_t               (*WriteProtect)   (uint32_t dev_num, bool enable);                                    ///< Pointer to \ref ARM_NAND_WriteProtect : Control WPn (Write Protect).
  int32_t               (*ChipEnable)     (uint32_t dev_num, bool enable);                                    ///< Pointer to \ref ARM_NAND_ChipEnable : Control CEn (Chip Enable).
  int32_t               (*GetDeviceBusy)  (uint32_t dev_num);                                                 ///< Pointer to \ref ARM_NAND_GetDeviceBusy : Get Device Busy pin state.
  int32_t               (*SendCommand)    (uint32_t dev_num, uint8_t cmd);                                    ///< Pointer to \ref ARM_NAND_SendCommand : Send command to NAND device.
  int32_t               (*SendAddress)    (uint32_t dev_num, uint8_t addr);                                   ///< Pointer to \ref ARM_NAND_SendAddress : Send address to NAND device.
  int32_t               (*ReadData)       (uint32_t dev_num,       void *data, uint32_t cnt, uint32_t mode);  ///< Pointer to \ref ARM_NAND_ReadData : Read data from NAND device.
  int32_t               (*WriteData)      (uint32_t dev_num, const void *data, uint32_t cnt, uint32_t mode);  ///< Pointer to \ref ARM_NAND_WriteData : Write data to NAND device.
  int32_t               (*ExecuteSequence)(uint32_t dev_num, uint32_t code, uint32_t cmd,
                                           uint32_t addr_col, uint32_t addr_row,
                                           void *data, uint32_t data_cnt,
                                           uint8_t *status, uint32_t *count);                                 ///< Pointer to \ref ARM_NAND_ExecuteSequence : Execute sequence of operations.
  int32_t               (*AbortSequence)  (uint32_t dev_num);                                                 ///< Pointer to \ref ARM_NAND_AbortSequence : Abort sequence execution. 
  int32_t               (*Control)        (uint32_t dev_num, uint32_t control, uint32_t arg);                 ///< Pointer to \ref ARM_NAND_Control : Control NAND Interface.
  ARM_NAND_STATUS       (*GetStatus)      (uint32_t dev_num);                                                 ///< Pointer to \ref ARM_NAND_GetStatus : Get NAND status.
  int32_t               (*InquireECC)     ( int32_t index, ARM_NAND_ECC_INFO *info);                          ///< Pointer to \ref ARM_NAND_InquireECC : Inquire about available ECC. 
} const ARM_DRIVER_NAND;

#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_NAND_H_ */
