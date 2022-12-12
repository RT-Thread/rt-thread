/**
 * \file
 *
 * \brief Instance description for DMAC
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

/* file generated from device description version 2019-01-31T14:29:25Z */
#ifndef _SAML10_DMAC_INSTANCE_H_
#define _SAML10_DMAC_INSTANCE_H_

/* ========== Register definition for DMAC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_DMAC_CTRL           (0x41006000) /**< (DMAC) Control */
#define REG_DMAC_CRCCTRL        (0x41006002) /**< (DMAC) CRC Control */
#define REG_DMAC_CRCDATAIN      (0x41006004) /**< (DMAC) CRC Data Input */
#define REG_DMAC_CRCCHKSUM      (0x41006008) /**< (DMAC) CRC Checksum */
#define REG_DMAC_CRCSTATUS      (0x4100600C) /**< (DMAC) CRC Status */
#define REG_DMAC_DBGCTRL        (0x4100600D) /**< (DMAC) Debug Control */
#define REG_DMAC_QOSCTRL        (0x4100600E) /**< (DMAC) QOS Control */
#define REG_DMAC_SWTRIGCTRL     (0x41006010) /**< (DMAC) Software Trigger Control */
#define REG_DMAC_PRICTRL0       (0x41006014) /**< (DMAC) Priority Control 0 */
#define REG_DMAC_INTPEND        (0x41006020) /**< (DMAC) Interrupt Pending */
#define REG_DMAC_INTSTATUS      (0x41006024) /**< (DMAC) Interrupt Status */
#define REG_DMAC_BUSYCH         (0x41006028) /**< (DMAC) Busy Channels */
#define REG_DMAC_PENDCH         (0x4100602C) /**< (DMAC) Pending Channels */
#define REG_DMAC_ACTIVE         (0x41006030) /**< (DMAC) Active Channel and Levels */
#define REG_DMAC_BASEADDR       (0x41006034) /**< (DMAC) Descriptor Memory Section Base Address */
#define REG_DMAC_WRBADDR        (0x41006038) /**< (DMAC) Write-Back Memory Section Base Address */
#define REG_DMAC_CHID           (0x4100603F) /**< (DMAC) Channel ID */
#define REG_DMAC_CHCTRLA        (0x41006040) /**< (DMAC) Channel Control A */
#define REG_DMAC_CHCTRLB        (0x41006044) /**< (DMAC) Channel Control B */
#define REG_DMAC_CHINTENCLR     (0x4100604C) /**< (DMAC) Channel Interrupt Enable Clear */
#define REG_DMAC_CHINTENSET     (0x4100604D) /**< (DMAC) Channel Interrupt Enable Set */
#define REG_DMAC_CHINTFLAG      (0x4100604E) /**< (DMAC) Channel Interrupt Flag Status and Clear */
#define REG_DMAC_CHSTATUS       (0x4100604F) /**< (DMAC) Channel Status */

#else

#define REG_DMAC_CTRL           (*(__IO uint16_t*)0x41006000U) /**< (DMAC) Control */
#define REG_DMAC_CRCCTRL        (*(__IO uint16_t*)0x41006002U) /**< (DMAC) CRC Control */
#define REG_DMAC_CRCDATAIN      (*(__IO uint32_t*)0x41006004U) /**< (DMAC) CRC Data Input */
#define REG_DMAC_CRCCHKSUM      (*(__IO uint32_t*)0x41006008U) /**< (DMAC) CRC Checksum */
#define REG_DMAC_CRCSTATUS      (*(__IO uint8_t*)0x4100600CU) /**< (DMAC) CRC Status */
#define REG_DMAC_DBGCTRL        (*(__IO uint8_t*)0x4100600DU) /**< (DMAC) Debug Control */
#define REG_DMAC_QOSCTRL        (*(__IO uint8_t*)0x4100600EU) /**< (DMAC) QOS Control */
#define REG_DMAC_SWTRIGCTRL     (*(__IO uint32_t*)0x41006010U) /**< (DMAC) Software Trigger Control */
#define REG_DMAC_PRICTRL0       (*(__IO uint32_t*)0x41006014U) /**< (DMAC) Priority Control 0 */
#define REG_DMAC_INTPEND        (*(__IO uint16_t*)0x41006020U) /**< (DMAC) Interrupt Pending */
#define REG_DMAC_INTSTATUS      (*(__I  uint32_t*)0x41006024U) /**< (DMAC) Interrupt Status */
#define REG_DMAC_BUSYCH         (*(__I  uint32_t*)0x41006028U) /**< (DMAC) Busy Channels */
#define REG_DMAC_PENDCH         (*(__I  uint32_t*)0x4100602CU) /**< (DMAC) Pending Channels */
#define REG_DMAC_ACTIVE         (*(__I  uint32_t*)0x41006030U) /**< (DMAC) Active Channel and Levels */
#define REG_DMAC_BASEADDR       (*(__IO uint32_t*)0x41006034U) /**< (DMAC) Descriptor Memory Section Base Address */
#define REG_DMAC_WRBADDR        (*(__IO uint32_t*)0x41006038U) /**< (DMAC) Write-Back Memory Section Base Address */
#define REG_DMAC_CHID           (*(__IO uint8_t*)0x4100603FU) /**< (DMAC) Channel ID */
#define REG_DMAC_CHCTRLA        (*(__IO uint8_t*)0x41006040U) /**< (DMAC) Channel Control A */
#define REG_DMAC_CHCTRLB        (*(__IO uint32_t*)0x41006044U) /**< (DMAC) Channel Control B */
#define REG_DMAC_CHINTENCLR     (*(__IO uint8_t*)0x4100604CU) /**< (DMAC) Channel Interrupt Enable Clear */
#define REG_DMAC_CHINTENSET     (*(__IO uint8_t*)0x4100604DU) /**< (DMAC) Channel Interrupt Enable Set */
#define REG_DMAC_CHINTFLAG      (*(__IO uint8_t*)0x4100604EU) /**< (DMAC) Channel Interrupt Flag Status and Clear */
#define REG_DMAC_CHSTATUS       (*(__I  uint8_t*)0x4100604FU) /**< (DMAC) Channel Status */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for DMAC peripheral ========== */
#define DMAC_CH_BITS                             3          /* Number of bits to select channel */
#define DMAC_CH_NUM                              8          /* Number of channels */
#define DMAC_EVIN_NUM                            4          /* Number of input events */
#define DMAC_EVOUT_NUM                           4          /* Number of output events */
#define DMAC_LVL_BITS                            2          /* Number of bit to select level priority */
#define DMAC_LVL_NUM                             4          /* Enable priority level number */
#define DMAC_QOSCTRL_D_RESETVALUE                2          /* QOS dmac ahb interface reset value */
#define DMAC_QOSCTRL_F_RESETVALUE                2          /* QOS dmac fetch interface reset value */
#define DMAC_QOSCTRL_WRB_RESETVALUE              2          /* QOS dmac write back interface reset value */
#define DMAC_TRIG_BITS                           5          /* Number of bits to select trigger source */
#define DMAC_TRIG_NUM                            24         /* Number of peripheral triggers */
#define DMAC_INSTANCE_ID                         35         

#endif /* _SAML10_DMAC_INSTANCE_ */
