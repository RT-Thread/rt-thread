/**
 * \file
 *
 * \brief Instance description for TC0
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
#ifndef _SAML10_TC0_INSTANCE_H_
#define _SAML10_TC0_INSTANCE_H_

/* ========== Register definition for TC0 peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_TC0_CTRLA           (0x42001000) /**< (TC0) Control A */
#define REG_TC0_CTRLBCLR        (0x42001004) /**< (TC0) Control B Clear */
#define REG_TC0_CTRLBSET        (0x42001005) /**< (TC0) Control B Set */
#define REG_TC0_EVCTRL          (0x42001006) /**< (TC0) Event Control */
#define REG_TC0_INTENCLR        (0x42001008) /**< (TC0) Interrupt Enable Clear */
#define REG_TC0_INTENSET        (0x42001009) /**< (TC0) Interrupt Enable Set */
#define REG_TC0_INTFLAG         (0x4200100A) /**< (TC0) Interrupt Flag Status and Clear */
#define REG_TC0_STATUS          (0x4200100B) /**< (TC0) Status */
#define REG_TC0_WAVE            (0x4200100C) /**< (TC0) Waveform Generation Control */
#define REG_TC0_DRVCTRL         (0x4200100D) /**< (TC0) Control C */
#define REG_TC0_DBGCTRL         (0x4200100F) /**< (TC0) Debug Control */
#define REG_TC0_SYNCBUSY        (0x42001010) /**< (TC0) Synchronization Status */
#define REG_TC0_COUNT8_COUNT    (0x42001014) /**< (TC0) COUNT8 Count */
#define REG_TC0_COUNT8_PER      (0x4200101B) /**< (TC0) COUNT8 Period */
#define REG_TC0_COUNT8_CC       (0x4200101C) /**< (TC0) COUNT8 Compare and Capture */
#define REG_TC0_COUNT8_CC0      (0x4200101C) /**< (TC0) COUNT8 Compare and Capture 0 */
#define REG_TC0_COUNT8_CC1      (0x4200101D) /**< (TC0) COUNT8 Compare and Capture 1 */
#define REG_TC0_COUNT8_PERBUF   (0x4200102F) /**< (TC0) COUNT8 Period Buffer */
#define REG_TC0_COUNT8_CCBUF    (0x42001030) /**< (TC0) COUNT8 Compare and Capture Buffer */
#define REG_TC0_COUNT8_CCBUF0   (0x42001030) /**< (TC0) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC0_COUNT8_CCBUF1   (0x42001031) /**< (TC0) COUNT8 Compare and Capture Buffer 1 */
#define REG_TC0_COUNT16_COUNT   (0x42001014) /**< (TC0) COUNT16 Count */
#define REG_TC0_COUNT16_PER     (0x4200101A) /**< (TC0) COUNT16 Period */
#define REG_TC0_COUNT16_CC      (0x4200101C) /**< (TC0) COUNT16 Compare and Capture */
#define REG_TC0_COUNT16_CC0     (0x4200101C) /**< (TC0) COUNT16 Compare and Capture 0 */
#define REG_TC0_COUNT16_CC1     (0x4200101E) /**< (TC0) COUNT16 Compare and Capture 1 */
#define REG_TC0_COUNT16_PERBUF  (0x4200102E) /**< (TC0) COUNT16 Period Buffer */
#define REG_TC0_COUNT16_CCBUF   (0x42001030) /**< (TC0) COUNT16 Compare and Capture Buffer */
#define REG_TC0_COUNT16_CCBUF0  (0x42001030) /**< (TC0) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC0_COUNT16_CCBUF1  (0x42001032) /**< (TC0) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC0_COUNT32_COUNT   (0x42001014) /**< (TC0) COUNT32 Count */
#define REG_TC0_COUNT32_PER     (0x42001018) /**< (TC0) COUNT32 Period */
#define REG_TC0_COUNT32_CC      (0x4200101C) /**< (TC0) COUNT32 Compare and Capture */
#define REG_TC0_COUNT32_CC0     (0x4200101C) /**< (TC0) COUNT32 Compare and Capture 0 */
#define REG_TC0_COUNT32_CC1     (0x42001020) /**< (TC0) COUNT32 Compare and Capture 1 */
#define REG_TC0_COUNT32_PERBUF  (0x4200102C) /**< (TC0) COUNT32 Period Buffer */
#define REG_TC0_COUNT32_CCBUF   (0x42001030) /**< (TC0) COUNT32 Compare and Capture Buffer */
#define REG_TC0_COUNT32_CCBUF0  (0x42001030) /**< (TC0) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC0_COUNT32_CCBUF1  (0x42001034) /**< (TC0) COUNT32 Compare and Capture Buffer 1 */

#else

#define REG_TC0_CTRLA           (*(__IO uint32_t*)0x42001000U) /**< (TC0) Control A */
#define REG_TC0_CTRLBCLR        (*(__IO uint8_t*)0x42001004U) /**< (TC0) Control B Clear */
#define REG_TC0_CTRLBSET        (*(__IO uint8_t*)0x42001005U) /**< (TC0) Control B Set */
#define REG_TC0_EVCTRL          (*(__IO uint16_t*)0x42001006U) /**< (TC0) Event Control */
#define REG_TC0_INTENCLR        (*(__IO uint8_t*)0x42001008U) /**< (TC0) Interrupt Enable Clear */
#define REG_TC0_INTENSET        (*(__IO uint8_t*)0x42001009U) /**< (TC0) Interrupt Enable Set */
#define REG_TC0_INTFLAG         (*(__IO uint8_t*)0x4200100AU) /**< (TC0) Interrupt Flag Status and Clear */
#define REG_TC0_STATUS          (*(__IO uint8_t*)0x4200100BU) /**< (TC0) Status */
#define REG_TC0_WAVE            (*(__IO uint8_t*)0x4200100CU) /**< (TC0) Waveform Generation Control */
#define REG_TC0_DRVCTRL         (*(__IO uint8_t*)0x4200100DU) /**< (TC0) Control C */
#define REG_TC0_DBGCTRL         (*(__IO uint8_t*)0x4200100FU) /**< (TC0) Debug Control */
#define REG_TC0_SYNCBUSY        (*(__I  uint32_t*)0x42001010U) /**< (TC0) Synchronization Status */
#define REG_TC0_COUNT8_COUNT    (*(__IO uint8_t*)0x42001014U) /**< (TC0) COUNT8 Count */
#define REG_TC0_COUNT8_PER      (*(__IO uint8_t*)0x4200101BU) /**< (TC0) COUNT8 Period */
#define REG_TC0_COUNT8_CC       (*(__IO uint8_t*)0x4200101CU) /**< (TC0) COUNT8 Compare and Capture */
#define REG_TC0_COUNT8_CC0      (*(__IO uint8_t*)0x4200101CU) /**< (TC0) COUNT8 Compare and Capture 0 */
#define REG_TC0_COUNT8_CC1      (*(__IO uint8_t*)0x4200101DU) /**< (TC0) COUNT8 Compare and Capture 1 */
#define REG_TC0_COUNT8_PERBUF   (*(__IO uint8_t*)0x4200102FU) /**< (TC0) COUNT8 Period Buffer */
#define REG_TC0_COUNT8_CCBUF    (*(__IO uint8_t*)0x42001030U) /**< (TC0) COUNT8 Compare and Capture Buffer */
#define REG_TC0_COUNT8_CCBUF0   (*(__IO uint8_t*)0x42001030U) /**< (TC0) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC0_COUNT8_CCBUF1   (*(__IO uint8_t*)0x42001031U) /**< (TC0) COUNT8 Compare and Capture Buffer 1 */
#define REG_TC0_COUNT16_COUNT   (*(__IO uint16_t*)0x42001014U) /**< (TC0) COUNT16 Count */
#define REG_TC0_COUNT16_PER     (*(__IO uint16_t*)0x4200101AU) /**< (TC0) COUNT16 Period */
#define REG_TC0_COUNT16_CC      (*(__IO uint16_t*)0x4200101CU) /**< (TC0) COUNT16 Compare and Capture */
#define REG_TC0_COUNT16_CC0     (*(__IO uint16_t*)0x4200101CU) /**< (TC0) COUNT16 Compare and Capture 0 */
#define REG_TC0_COUNT16_CC1     (*(__IO uint16_t*)0x4200101EU) /**< (TC0) COUNT16 Compare and Capture 1 */
#define REG_TC0_COUNT16_PERBUF  (*(__IO uint16_t*)0x4200102EU) /**< (TC0) COUNT16 Period Buffer */
#define REG_TC0_COUNT16_CCBUF   (*(__IO uint16_t*)0x42001030U) /**< (TC0) COUNT16 Compare and Capture Buffer */
#define REG_TC0_COUNT16_CCBUF0  (*(__IO uint16_t*)0x42001030U) /**< (TC0) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC0_COUNT16_CCBUF1  (*(__IO uint16_t*)0x42001032U) /**< (TC0) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC0_COUNT32_COUNT   (*(__IO uint32_t*)0x42001014U) /**< (TC0) COUNT32 Count */
#define REG_TC0_COUNT32_PER     (*(__IO uint32_t*)0x42001018U) /**< (TC0) COUNT32 Period */
#define REG_TC0_COUNT32_CC      (*(__IO uint32_t*)0x4200101CU) /**< (TC0) COUNT32 Compare and Capture */
#define REG_TC0_COUNT32_CC0     (*(__IO uint32_t*)0x4200101CU) /**< (TC0) COUNT32 Compare and Capture 0 */
#define REG_TC0_COUNT32_CC1     (*(__IO uint32_t*)0x42001020U) /**< (TC0) COUNT32 Compare and Capture 1 */
#define REG_TC0_COUNT32_PERBUF  (*(__IO uint32_t*)0x4200102CU) /**< (TC0) COUNT32 Period Buffer */
#define REG_TC0_COUNT32_CCBUF   (*(__IO uint32_t*)0x42001030U) /**< (TC0) COUNT32 Compare and Capture Buffer */
#define REG_TC0_COUNT32_CCBUF0  (*(__IO uint32_t*)0x42001030U) /**< (TC0) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC0_COUNT32_CCBUF1  (*(__IO uint32_t*)0x42001034U) /**< (TC0) COUNT32 Compare and Capture Buffer 1 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for TC0 peripheral ========== */
#define TC0_CC_NUM                               2          
#define TC0_DMAC_ID_OVF                          10         /* Indexes of DMA Overflow trigger */
#define TC0_EXT                                  1          /* Coding of implemented extended features (keep 0 value) */
#define TC0_GCLK_ID                              14         /* Index of Generic Clock */
#define TC0_MASTER_SLAVE_MODE                    1          /* TC type 0 : NA, 1 : Master, 2 : Slave */
#define TC0_OW_NUM                               2          /* Number of Output Waveforms */
#define TC0_INSTANCE_ID                          68         

#endif /* _SAML10_TC0_INSTANCE_ */
