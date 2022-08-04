/**
 * \file
 *
 * \brief Instance description for CAN0
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

#ifndef _SAMC21_CAN0_INSTANCE_
#define _SAMC21_CAN0_INSTANCE_

/* ========== Register definition for CAN0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CAN0_CREL              (0x42001C00) /**< \brief (CAN0) Core Release */
#define REG_CAN0_ENDN              (0x42001C04) /**< \brief (CAN0) Endian */
#define REG_CAN0_MRCFG             (0x42001C08) /**< \brief (CAN0) Message RAM Configuration */
#define REG_CAN0_DBTP              (0x42001C0C) /**< \brief (CAN0) Fast Bit Timing and Prescaler */
#define REG_CAN0_TEST              (0x42001C10) /**< \brief (CAN0) Test */
#define REG_CAN0_RWD               (0x42001C14) /**< \brief (CAN0) RAM Watchdog */
#define REG_CAN0_CCCR              (0x42001C18) /**< \brief (CAN0) CC Control */
#define REG_CAN0_NBTP              (0x42001C1C) /**< \brief (CAN0) Nominal Bit Timing and Prescaler */
#define REG_CAN0_TSCC              (0x42001C20) /**< \brief (CAN0) Timestamp Counter Configuration */
#define REG_CAN0_TSCV              (0x42001C24) /**< \brief (CAN0) Timestamp Counter Value */
#define REG_CAN0_TOCC              (0x42001C28) /**< \brief (CAN0) Timeout Counter Configuration */
#define REG_CAN0_TOCV              (0x42001C2C) /**< \brief (CAN0) Timeout Counter Value */
#define REG_CAN0_ECR               (0x42001C40) /**< \brief (CAN0) Error Counter */
#define REG_CAN0_PSR               (0x42001C44) /**< \brief (CAN0) Protocol Status */
#define REG_CAN0_TDCR              (0x42001C48) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_IR                (0x42001C50) /**< \brief (CAN0) Interrupt */
#define REG_CAN0_IE                (0x42001C54) /**< \brief (CAN0) Interrupt Enable */
#define REG_CAN0_ILS               (0x42001C58) /**< \brief (CAN0) Interrupt Line Select */
#define REG_CAN0_ILE               (0x42001C5C) /**< \brief (CAN0) Interrupt Line Enable */
#define REG_CAN0_GFC               (0x42001C80) /**< \brief (CAN0) Global Filter Configuration */
#define REG_CAN0_SIDFC             (0x42001C84) /**< \brief (CAN0) Standard ID Filter Configuration */
#define REG_CAN0_XIDFC             (0x42001C88) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_XIDAM             (0x42001C90) /**< \brief (CAN0) Extended ID AND Mask */
#define REG_CAN0_HPMS              (0x42001C94) /**< \brief (CAN0) High Priority Message Status */
#define REG_CAN0_NDAT1             (0x42001C98) /**< \brief (CAN0) New Data 1 */
#define REG_CAN0_NDAT2             (0x42001C9C) /**< \brief (CAN0) New Data 2 */
#define REG_CAN0_RXF0C             (0x42001CA0) /**< \brief (CAN0) Rx FIFO 0 Configuration */
#define REG_CAN0_RXF0S             (0x42001CA4) /**< \brief (CAN0) Rx FIFO 0 Status */
#define REG_CAN0_RXF0A             (0x42001CA8) /**< \brief (CAN0) Rx FIFO 0 Acknowledge */
#define REG_CAN0_RXBC              (0x42001CAC) /**< \brief (CAN0) Rx Buffer Configuration */
#define REG_CAN0_RXF1C             (0x42001CB0) /**< \brief (CAN0) Rx FIFO 1 Configuration */
#define REG_CAN0_RXF1S             (0x42001CB4) /**< \brief (CAN0) Rx FIFO 1 Status */
#define REG_CAN0_RXF1A             (0x42001CB8) /**< \brief (CAN0) Rx FIFO 1 Acknowledge */
#define REG_CAN0_RXESC             (0x42001CBC) /**< \brief (CAN0) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN0_TXBC              (0x42001CC0) /**< \brief (CAN0) Tx Buffer Configuration */
#define REG_CAN0_TXFQS             (0x42001CC4) /**< \brief (CAN0) Tx FIFO / Queue Status */
#define REG_CAN0_TXESC             (0x42001CC8) /**< \brief (CAN0) Tx Buffer Element Size Configuration */
#define REG_CAN0_TXBRP             (0x42001CCC) /**< \brief (CAN0) Tx Buffer Request Pending */
#define REG_CAN0_TXBAR             (0x42001CD0) /**< \brief (CAN0) Tx Buffer Add Request */
#define REG_CAN0_TXBCR             (0x42001CD4) /**< \brief (CAN0) Tx Buffer Cancellation Request */
#define REG_CAN0_TXBTO             (0x42001CD8) /**< \brief (CAN0) Tx Buffer Transmission Occurred */
#define REG_CAN0_TXBCF             (0x42001CDC) /**< \brief (CAN0) Tx Buffer Cancellation Finished */
#define REG_CAN0_TXBTIE            (0x42001CE0) /**< \brief (CAN0) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN0_TXBCIE            (0x42001CE4) /**< \brief (CAN0) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN0_TXEFC             (0x42001CF0) /**< \brief (CAN0) Tx Event FIFO Configuration */
#define REG_CAN0_TXEFS             (0x42001CF4) /**< \brief (CAN0) Tx Event FIFO Status */
#define REG_CAN0_TXEFA             (0x42001CF8) /**< \brief (CAN0) Tx Event FIFO Acknowledge */
#else
#define REG_CAN0_CREL              (*(RoReg  *)0x42001C00UL) /**< \brief (CAN0) Core Release */
#define REG_CAN0_ENDN              (*(RoReg  *)0x42001C04UL) /**< \brief (CAN0) Endian */
#define REG_CAN0_MRCFG             (*(RwReg  *)0x42001C08UL) /**< \brief (CAN0) Message RAM Configuration */
#define REG_CAN0_DBTP              (*(RwReg  *)0x42001C0CUL) /**< \brief (CAN0) Fast Bit Timing and Prescaler */
#define REG_CAN0_TEST              (*(RwReg  *)0x42001C10UL) /**< \brief (CAN0) Test */
#define REG_CAN0_RWD               (*(RwReg  *)0x42001C14UL) /**< \brief (CAN0) RAM Watchdog */
#define REG_CAN0_CCCR              (*(RwReg  *)0x42001C18UL) /**< \brief (CAN0) CC Control */
#define REG_CAN0_NBTP              (*(RwReg  *)0x42001C1CUL) /**< \brief (CAN0) Nominal Bit Timing and Prescaler */
#define REG_CAN0_TSCC              (*(RwReg  *)0x42001C20UL) /**< \brief (CAN0) Timestamp Counter Configuration */
#define REG_CAN0_TSCV              (*(RoReg  *)0x42001C24UL) /**< \brief (CAN0) Timestamp Counter Value */
#define REG_CAN0_TOCC              (*(RwReg  *)0x42001C28UL) /**< \brief (CAN0) Timeout Counter Configuration */
#define REG_CAN0_TOCV              (*(RwReg  *)0x42001C2CUL) /**< \brief (CAN0) Timeout Counter Value */
#define REG_CAN0_ECR               (*(RoReg  *)0x42001C40UL) /**< \brief (CAN0) Error Counter */
#define REG_CAN0_PSR               (*(RoReg  *)0x42001C44UL) /**< \brief (CAN0) Protocol Status */
#define REG_CAN0_TDCR              (*(RwReg  *)0x42001C48UL) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_IR                (*(RwReg  *)0x42001C50UL) /**< \brief (CAN0) Interrupt */
#define REG_CAN0_IE                (*(RwReg  *)0x42001C54UL) /**< \brief (CAN0) Interrupt Enable */
#define REG_CAN0_ILS               (*(RwReg  *)0x42001C58UL) /**< \brief (CAN0) Interrupt Line Select */
#define REG_CAN0_ILE               (*(RwReg  *)0x42001C5CUL) /**< \brief (CAN0) Interrupt Line Enable */
#define REG_CAN0_GFC               (*(RwReg  *)0x42001C80UL) /**< \brief (CAN0) Global Filter Configuration */
#define REG_CAN0_SIDFC             (*(RwReg  *)0x42001C84UL) /**< \brief (CAN0) Standard ID Filter Configuration */
#define REG_CAN0_XIDFC             (*(RwReg  *)0x42001C88UL) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_XIDAM             (*(RwReg  *)0x42001C90UL) /**< \brief (CAN0) Extended ID AND Mask */
#define REG_CAN0_HPMS              (*(RoReg  *)0x42001C94UL) /**< \brief (CAN0) High Priority Message Status */
#define REG_CAN0_NDAT1             (*(RwReg  *)0x42001C98UL) /**< \brief (CAN0) New Data 1 */
#define REG_CAN0_NDAT2             (*(RwReg  *)0x42001C9CUL) /**< \brief (CAN0) New Data 2 */
#define REG_CAN0_RXF0C             (*(RwReg  *)0x42001CA0UL) /**< \brief (CAN0) Rx FIFO 0 Configuration */
#define REG_CAN0_RXF0S             (*(RoReg  *)0x42001CA4UL) /**< \brief (CAN0) Rx FIFO 0 Status */
#define REG_CAN0_RXF0A             (*(RwReg  *)0x42001CA8UL) /**< \brief (CAN0) Rx FIFO 0 Acknowledge */
#define REG_CAN0_RXBC              (*(RwReg  *)0x42001CACUL) /**< \brief (CAN0) Rx Buffer Configuration */
#define REG_CAN0_RXF1C             (*(RwReg  *)0x42001CB0UL) /**< \brief (CAN0) Rx FIFO 1 Configuration */
#define REG_CAN0_RXF1S             (*(RoReg  *)0x42001CB4UL) /**< \brief (CAN0) Rx FIFO 1 Status */
#define REG_CAN0_RXF1A             (*(RwReg  *)0x42001CB8UL) /**< \brief (CAN0) Rx FIFO 1 Acknowledge */
#define REG_CAN0_RXESC             (*(RwReg  *)0x42001CBCUL) /**< \brief (CAN0) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN0_TXBC              (*(RwReg  *)0x42001CC0UL) /**< \brief (CAN0) Tx Buffer Configuration */
#define REG_CAN0_TXFQS             (*(RoReg  *)0x42001CC4UL) /**< \brief (CAN0) Tx FIFO / Queue Status */
#define REG_CAN0_TXESC             (*(RwReg  *)0x42001CC8UL) /**< \brief (CAN0) Tx Buffer Element Size Configuration */
#define REG_CAN0_TXBRP             (*(RoReg  *)0x42001CCCUL) /**< \brief (CAN0) Tx Buffer Request Pending */
#define REG_CAN0_TXBAR             (*(RwReg  *)0x42001CD0UL) /**< \brief (CAN0) Tx Buffer Add Request */
#define REG_CAN0_TXBCR             (*(RwReg  *)0x42001CD4UL) /**< \brief (CAN0) Tx Buffer Cancellation Request */
#define REG_CAN0_TXBTO             (*(RoReg  *)0x42001CD8UL) /**< \brief (CAN0) Tx Buffer Transmission Occurred */
#define REG_CAN0_TXBCF             (*(RoReg  *)0x42001CDCUL) /**< \brief (CAN0) Tx Buffer Cancellation Finished */
#define REG_CAN0_TXBTIE            (*(RwReg  *)0x42001CE0UL) /**< \brief (CAN0) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN0_TXBCIE            (*(RwReg  *)0x42001CE4UL) /**< \brief (CAN0) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN0_TXEFC             (*(RwReg  *)0x42001CF0UL) /**< \brief (CAN0) Tx Event FIFO Configuration */
#define REG_CAN0_TXEFS             (*(RoReg  *)0x42001CF4UL) /**< \brief (CAN0) Tx Event FIFO Status */
#define REG_CAN0_TXEFA             (*(RwReg  *)0x42001CF8UL) /**< \brief (CAN0) Tx Event FIFO Acknowledge */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for CAN0 peripheral ========== */
#define CAN0_CLK_AHB_ID             8        // Index of AHB clock
#define CAN0_DMAC_ID_DEBUG          14       // DMA CAN Debug Req
#define CAN0_GCLK_ID                26       // Index of Generic Clock
#define CAN0_MSG_RAM_ADDR           0x200000000
#define CAN0_QOS_RESET_VAL          2        // QOS reset value

#endif /* _SAMC21_CAN0_INSTANCE_ */
