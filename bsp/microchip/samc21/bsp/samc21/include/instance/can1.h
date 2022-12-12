/**
 * \file
 *
 * \brief Instance description for CAN1
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_CAN1_INSTANCE_
#define _SAMC21_CAN1_INSTANCE_

/* ========== Register definition for CAN1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CAN1_CREL              (0x42002000) /**< \brief (CAN1) Core Release */
#define REG_CAN1_ENDN              (0x42002004) /**< \brief (CAN1) Endian */
#define REG_CAN1_MRCFG             (0x42002008) /**< \brief (CAN1) Message RAM Configuration */
#define REG_CAN1_DBTP              (0x4200200C) /**< \brief (CAN1) Fast Bit Timing and Prescaler */
#define REG_CAN1_TEST              (0x42002010) /**< \brief (CAN1) Test */
#define REG_CAN1_RWD               (0x42002014) /**< \brief (CAN1) RAM Watchdog */
#define REG_CAN1_CCCR              (0x42002018) /**< \brief (CAN1) CC Control */
#define REG_CAN1_NBTP              (0x4200201C) /**< \brief (CAN1) Nominal Bit Timing and Prescaler */
#define REG_CAN1_TSCC              (0x42002020) /**< \brief (CAN1) Timestamp Counter Configuration */
#define REG_CAN1_TSCV              (0x42002024) /**< \brief (CAN1) Timestamp Counter Value */
#define REG_CAN1_TOCC              (0x42002028) /**< \brief (CAN1) Timeout Counter Configuration */
#define REG_CAN1_TOCV              (0x4200202C) /**< \brief (CAN1) Timeout Counter Value */
#define REG_CAN1_ECR               (0x42002040) /**< \brief (CAN1) Error Counter */
#define REG_CAN1_PSR               (0x42002044) /**< \brief (CAN1) Protocol Status */
#define REG_CAN1_TDCR              (0x42002048) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_IR                (0x42002050) /**< \brief (CAN1) Interrupt */
#define REG_CAN1_IE                (0x42002054) /**< \brief (CAN1) Interrupt Enable */
#define REG_CAN1_ILS               (0x42002058) /**< \brief (CAN1) Interrupt Line Select */
#define REG_CAN1_ILE               (0x4200205C) /**< \brief (CAN1) Interrupt Line Enable */
#define REG_CAN1_GFC               (0x42002080) /**< \brief (CAN1) Global Filter Configuration */
#define REG_CAN1_SIDFC             (0x42002084) /**< \brief (CAN1) Standard ID Filter Configuration */
#define REG_CAN1_XIDFC             (0x42002088) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_XIDAM             (0x42002090) /**< \brief (CAN1) Extended ID AND Mask */
#define REG_CAN1_HPMS              (0x42002094) /**< \brief (CAN1) High Priority Message Status */
#define REG_CAN1_NDAT1             (0x42002098) /**< \brief (CAN1) New Data 1 */
#define REG_CAN1_NDAT2             (0x4200209C) /**< \brief (CAN1) New Data 2 */
#define REG_CAN1_RXF0C             (0x420020A0) /**< \brief (CAN1) Rx FIFO 0 Configuration */
#define REG_CAN1_RXF0S             (0x420020A4) /**< \brief (CAN1) Rx FIFO 0 Status */
#define REG_CAN1_RXF0A             (0x420020A8) /**< \brief (CAN1) Rx FIFO 0 Acknowledge */
#define REG_CAN1_RXBC              (0x420020AC) /**< \brief (CAN1) Rx Buffer Configuration */
#define REG_CAN1_RXF1C             (0x420020B0) /**< \brief (CAN1) Rx FIFO 1 Configuration */
#define REG_CAN1_RXF1S             (0x420020B4) /**< \brief (CAN1) Rx FIFO 1 Status */
#define REG_CAN1_RXF1A             (0x420020B8) /**< \brief (CAN1) Rx FIFO 1 Acknowledge */
#define REG_CAN1_RXESC             (0x420020BC) /**< \brief (CAN1) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN1_TXBC              (0x420020C0) /**< \brief (CAN1) Tx Buffer Configuration */
#define REG_CAN1_TXFQS             (0x420020C4) /**< \brief (CAN1) Tx FIFO / Queue Status */
#define REG_CAN1_TXESC             (0x420020C8) /**< \brief (CAN1) Tx Buffer Element Size Configuration */
#define REG_CAN1_TXBRP             (0x420020CC) /**< \brief (CAN1) Tx Buffer Request Pending */
#define REG_CAN1_TXBAR             (0x420020D0) /**< \brief (CAN1) Tx Buffer Add Request */
#define REG_CAN1_TXBCR             (0x420020D4) /**< \brief (CAN1) Tx Buffer Cancellation Request */
#define REG_CAN1_TXBTO             (0x420020D8) /**< \brief (CAN1) Tx Buffer Transmission Occurred */
#define REG_CAN1_TXBCF             (0x420020DC) /**< \brief (CAN1) Tx Buffer Cancellation Finished */
#define REG_CAN1_TXBTIE            (0x420020E0) /**< \brief (CAN1) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN1_TXBCIE            (0x420020E4) /**< \brief (CAN1) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN1_TXEFC             (0x420020F0) /**< \brief (CAN1) Tx Event FIFO Configuration */
#define REG_CAN1_TXEFS             (0x420020F4) /**< \brief (CAN1) Tx Event FIFO Status */
#define REG_CAN1_TXEFA             (0x420020F8) /**< \brief (CAN1) Tx Event FIFO Acknowledge */
#else
#define REG_CAN1_CREL              (*(RoReg  *)0x42002000UL) /**< \brief (CAN1) Core Release */
#define REG_CAN1_ENDN              (*(RoReg  *)0x42002004UL) /**< \brief (CAN1) Endian */
#define REG_CAN1_MRCFG             (*(RwReg  *)0x42002008UL) /**< \brief (CAN1) Message RAM Configuration */
#define REG_CAN1_DBTP              (*(RwReg  *)0x4200200CUL) /**< \brief (CAN1) Fast Bit Timing and Prescaler */
#define REG_CAN1_TEST              (*(RwReg  *)0x42002010UL) /**< \brief (CAN1) Test */
#define REG_CAN1_RWD               (*(RwReg  *)0x42002014UL) /**< \brief (CAN1) RAM Watchdog */
#define REG_CAN1_CCCR              (*(RwReg  *)0x42002018UL) /**< \brief (CAN1) CC Control */
#define REG_CAN1_NBTP              (*(RwReg  *)0x4200201CUL) /**< \brief (CAN1) Nominal Bit Timing and Prescaler */
#define REG_CAN1_TSCC              (*(RwReg  *)0x42002020UL) /**< \brief (CAN1) Timestamp Counter Configuration */
#define REG_CAN1_TSCV              (*(RoReg  *)0x42002024UL) /**< \brief (CAN1) Timestamp Counter Value */
#define REG_CAN1_TOCC              (*(RwReg  *)0x42002028UL) /**< \brief (CAN1) Timeout Counter Configuration */
#define REG_CAN1_TOCV              (*(RwReg  *)0x4200202CUL) /**< \brief (CAN1) Timeout Counter Value */
#define REG_CAN1_ECR               (*(RoReg  *)0x42002040UL) /**< \brief (CAN1) Error Counter */
#define REG_CAN1_PSR               (*(RoReg  *)0x42002044UL) /**< \brief (CAN1) Protocol Status */
#define REG_CAN1_TDCR              (*(RwReg  *)0x42002048UL) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_IR                (*(RwReg  *)0x42002050UL) /**< \brief (CAN1) Interrupt */
#define REG_CAN1_IE                (*(RwReg  *)0x42002054UL) /**< \brief (CAN1) Interrupt Enable */
#define REG_CAN1_ILS               (*(RwReg  *)0x42002058UL) /**< \brief (CAN1) Interrupt Line Select */
#define REG_CAN1_ILE               (*(RwReg  *)0x4200205CUL) /**< \brief (CAN1) Interrupt Line Enable */
#define REG_CAN1_GFC               (*(RwReg  *)0x42002080UL) /**< \brief (CAN1) Global Filter Configuration */
#define REG_CAN1_SIDFC             (*(RwReg  *)0x42002084UL) /**< \brief (CAN1) Standard ID Filter Configuration */
#define REG_CAN1_XIDFC             (*(RwReg  *)0x42002088UL) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_XIDAM             (*(RwReg  *)0x42002090UL) /**< \brief (CAN1) Extended ID AND Mask */
#define REG_CAN1_HPMS              (*(RoReg  *)0x42002094UL) /**< \brief (CAN1) High Priority Message Status */
#define REG_CAN1_NDAT1             (*(RwReg  *)0x42002098UL) /**< \brief (CAN1) New Data 1 */
#define REG_CAN1_NDAT2             (*(RwReg  *)0x4200209CUL) /**< \brief (CAN1) New Data 2 */
#define REG_CAN1_RXF0C             (*(RwReg  *)0x420020A0UL) /**< \brief (CAN1) Rx FIFO 0 Configuration */
#define REG_CAN1_RXF0S             (*(RoReg  *)0x420020A4UL) /**< \brief (CAN1) Rx FIFO 0 Status */
#define REG_CAN1_RXF0A             (*(RwReg  *)0x420020A8UL) /**< \brief (CAN1) Rx FIFO 0 Acknowledge */
#define REG_CAN1_RXBC              (*(RwReg  *)0x420020ACUL) /**< \brief (CAN1) Rx Buffer Configuration */
#define REG_CAN1_RXF1C             (*(RwReg  *)0x420020B0UL) /**< \brief (CAN1) Rx FIFO 1 Configuration */
#define REG_CAN1_RXF1S             (*(RoReg  *)0x420020B4UL) /**< \brief (CAN1) Rx FIFO 1 Status */
#define REG_CAN1_RXF1A             (*(RwReg  *)0x420020B8UL) /**< \brief (CAN1) Rx FIFO 1 Acknowledge */
#define REG_CAN1_RXESC             (*(RwReg  *)0x420020BCUL) /**< \brief (CAN1) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN1_TXBC              (*(RwReg  *)0x420020C0UL) /**< \brief (CAN1) Tx Buffer Configuration */
#define REG_CAN1_TXFQS             (*(RoReg  *)0x420020C4UL) /**< \brief (CAN1) Tx FIFO / Queue Status */
#define REG_CAN1_TXESC             (*(RwReg  *)0x420020C8UL) /**< \brief (CAN1) Tx Buffer Element Size Configuration */
#define REG_CAN1_TXBRP             (*(RoReg  *)0x420020CCUL) /**< \brief (CAN1) Tx Buffer Request Pending */
#define REG_CAN1_TXBAR             (*(RwReg  *)0x420020D0UL) /**< \brief (CAN1) Tx Buffer Add Request */
#define REG_CAN1_TXBCR             (*(RwReg  *)0x420020D4UL) /**< \brief (CAN1) Tx Buffer Cancellation Request */
#define REG_CAN1_TXBTO             (*(RoReg  *)0x420020D8UL) /**< \brief (CAN1) Tx Buffer Transmission Occurred */
#define REG_CAN1_TXBCF             (*(RoReg  *)0x420020DCUL) /**< \brief (CAN1) Tx Buffer Cancellation Finished */
#define REG_CAN1_TXBTIE            (*(RwReg  *)0x420020E0UL) /**< \brief (CAN1) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN1_TXBCIE            (*(RwReg  *)0x420020E4UL) /**< \brief (CAN1) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN1_TXEFC             (*(RwReg  *)0x420020F0UL) /**< \brief (CAN1) Tx Event FIFO Configuration */
#define REG_CAN1_TXEFS             (*(RoReg  *)0x420020F4UL) /**< \brief (CAN1) Tx Event FIFO Status */
#define REG_CAN1_TXEFA             (*(RwReg  *)0x420020F8UL) /**< \brief (CAN1) Tx Event FIFO Acknowledge */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for CAN1 peripheral ========== */
#define CAN1_CLK_AHB_ID             9        // Index of AHB clock
#define CAN1_DMAC_ID_DEBUG          15       // DMA CAN Debug Req
#define CAN1_GCLK_ID                27       // Index of Generic Clock
#define CAN1_MSG_RAM_ADDR           0x200000000
#define CAN1_QOS_RESET_VAL          2        // QOS reset value

#endif /* _SAMC21_CAN1_INSTANCE_ */
