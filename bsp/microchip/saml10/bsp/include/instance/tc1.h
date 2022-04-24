/**
 * \file
 *
 * \brief Instance description for TC1
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
#ifndef _SAML10_TC1_INSTANCE_H_
#define _SAML10_TC1_INSTANCE_H_

/* ========== Register definition for TC1 peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_TC1_CTRLA           (0x42001400) /**< (TC1) Control A */
#define REG_TC1_CTRLBCLR        (0x42001404) /**< (TC1) Control B Clear */
#define REG_TC1_CTRLBSET        (0x42001405) /**< (TC1) Control B Set */
#define REG_TC1_EVCTRL          (0x42001406) /**< (TC1) Event Control */
#define REG_TC1_INTENCLR        (0x42001408) /**< (TC1) Interrupt Enable Clear */
#define REG_TC1_INTENSET        (0x42001409) /**< (TC1) Interrupt Enable Set */
#define REG_TC1_INTFLAG         (0x4200140A) /**< (TC1) Interrupt Flag Status and Clear */
#define REG_TC1_STATUS          (0x4200140B) /**< (TC1) Status */
#define REG_TC1_WAVE            (0x4200140C) /**< (TC1) Waveform Generation Control */
#define REG_TC1_DRVCTRL         (0x4200140D) /**< (TC1) Control C */
#define REG_TC1_DBGCTRL         (0x4200140F) /**< (TC1) Debug Control */
#define REG_TC1_SYNCBUSY        (0x42001410) /**< (TC1) Synchronization Status */
#define REG_TC1_COUNT8_COUNT    (0x42001414) /**< (TC1) COUNT8 Count */
#define REG_TC1_COUNT8_PER      (0x4200141B) /**< (TC1) COUNT8 Period */
#define REG_TC1_COUNT8_CC       (0x4200141C) /**< (TC1) COUNT8 Compare and Capture */
#define REG_TC1_COUNT8_CC0      (0x4200141C) /**< (TC1) COUNT8 Compare and Capture 0 */
#define REG_TC1_COUNT8_CC1      (0x4200141D) /**< (TC1) COUNT8 Compare and Capture 1 */
#define REG_TC1_COUNT8_PERBUF   (0x4200142F) /**< (TC1) COUNT8 Period Buffer */
#define REG_TC1_COUNT8_CCBUF    (0x42001430) /**< (TC1) COUNT8 Compare and Capture Buffer */
#define REG_TC1_COUNT8_CCBUF0   (0x42001430) /**< (TC1) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC1_COUNT8_CCBUF1   (0x42001431) /**< (TC1) COUNT8 Compare and Capture Buffer 1 */
#define REG_TC1_COUNT16_COUNT   (0x42001414) /**< (TC1) COUNT16 Count */
#define REG_TC1_COUNT16_PER     (0x4200141A) /**< (TC1) COUNT16 Period */
#define REG_TC1_COUNT16_CC      (0x4200141C) /**< (TC1) COUNT16 Compare and Capture */
#define REG_TC1_COUNT16_CC0     (0x4200141C) /**< (TC1) COUNT16 Compare and Capture 0 */
#define REG_TC1_COUNT16_CC1     (0x4200141E) /**< (TC1) COUNT16 Compare and Capture 1 */
#define REG_TC1_COUNT16_PERBUF  (0x4200142E) /**< (TC1) COUNT16 Period Buffer */
#define REG_TC1_COUNT16_CCBUF   (0x42001430) /**< (TC1) COUNT16 Compare and Capture Buffer */
#define REG_TC1_COUNT16_CCBUF0  (0x42001430) /**< (TC1) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC1_COUNT16_CCBUF1  (0x42001432) /**< (TC1) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC1_COUNT32_COUNT   (0x42001414) /**< (TC1) COUNT32 Count */
#define REG_TC1_COUNT32_PER     (0x42001418) /**< (TC1) COUNT32 Period */
#define REG_TC1_COUNT32_CC      (0x4200141C) /**< (TC1) COUNT32 Compare and Capture */
#define REG_TC1_COUNT32_CC0     (0x4200141C) /**< (TC1) COUNT32 Compare and Capture 0 */
#define REG_TC1_COUNT32_CC1     (0x42001420) /**< (TC1) COUNT32 Compare and Capture 1 */
#define REG_TC1_COUNT32_PERBUF  (0x4200142C) /**< (TC1) COUNT32 Period Buffer */
#define REG_TC1_COUNT32_CCBUF   (0x42001430) /**< (TC1) COUNT32 Compare and Capture Buffer */
#define REG_TC1_COUNT32_CCBUF0  (0x42001430) /**< (TC1) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC1_COUNT32_CCBUF1  (0x42001434) /**< (TC1) COUNT32 Compare and Capture Buffer 1 */

#else

#define REG_TC1_CTRLA           (*(__IO uint32_t*)0x42001400U) /**< (TC1) Control A */
#define REG_TC1_CTRLBCLR        (*(__IO uint8_t*)0x42001404U) /**< (TC1) Control B Clear */
#define REG_TC1_CTRLBSET        (*(__IO uint8_t*)0x42001405U) /**< (TC1) Control B Set */
#define REG_TC1_EVCTRL          (*(__IO uint16_t*)0x42001406U) /**< (TC1) Event Control */
#define REG_TC1_INTENCLR        (*(__IO uint8_t*)0x42001408U) /**< (TC1) Interrupt Enable Clear */
#define REG_TC1_INTENSET        (*(__IO uint8_t*)0x42001409U) /**< (TC1) Interrupt Enable Set */
#define REG_TC1_INTFLAG         (*(__IO uint8_t*)0x4200140AU) /**< (TC1) Interrupt Flag Status and Clear */
#define REG_TC1_STATUS          (*(__IO uint8_t*)0x4200140BU) /**< (TC1) Status */
#define REG_TC1_WAVE            (*(__IO uint8_t*)0x4200140CU) /**< (TC1) Waveform Generation Control */
#define REG_TC1_DRVCTRL         (*(__IO uint8_t*)0x4200140DU) /**< (TC1) Control C */
#define REG_TC1_DBGCTRL         (*(__IO uint8_t*)0x4200140FU) /**< (TC1) Debug Control */
#define REG_TC1_SYNCBUSY        (*(__I  uint32_t*)0x42001410U) /**< (TC1) Synchronization Status */
#define REG_TC1_COUNT8_COUNT    (*(__IO uint8_t*)0x42001414U) /**< (TC1) COUNT8 Count */
#define REG_TC1_COUNT8_PER      (*(__IO uint8_t*)0x4200141BU) /**< (TC1) COUNT8 Period */
#define REG_TC1_COUNT8_CC       (*(__IO uint8_t*)0x4200141CU) /**< (TC1) COUNT8 Compare and Capture */
#define REG_TC1_COUNT8_CC0      (*(__IO uint8_t*)0x4200141CU) /**< (TC1) COUNT8 Compare and Capture 0 */
#define REG_TC1_COUNT8_CC1      (*(__IO uint8_t*)0x4200141DU) /**< (TC1) COUNT8 Compare and Capture 1 */
#define REG_TC1_COUNT8_PERBUF   (*(__IO uint8_t*)0x4200142FU) /**< (TC1) COUNT8 Period Buffer */
#define REG_TC1_COUNT8_CCBUF    (*(__IO uint8_t*)0x42001430U) /**< (TC1) COUNT8 Compare and Capture Buffer */
#define REG_TC1_COUNT8_CCBUF0   (*(__IO uint8_t*)0x42001430U) /**< (TC1) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC1_COUNT8_CCBUF1   (*(__IO uint8_t*)0x42001431U) /**< (TC1) COUNT8 Compare and Capture Buffer 1 */
#define REG_TC1_COUNT16_COUNT   (*(__IO uint16_t*)0x42001414U) /**< (TC1) COUNT16 Count */
#define REG_TC1_COUNT16_PER     (*(__IO uint16_t*)0x4200141AU) /**< (TC1) COUNT16 Period */
#define REG_TC1_COUNT16_CC      (*(__IO uint16_t*)0x4200141CU) /**< (TC1) COUNT16 Compare and Capture */
#define REG_TC1_COUNT16_CC0     (*(__IO uint16_t*)0x4200141CU) /**< (TC1) COUNT16 Compare and Capture 0 */
#define REG_TC1_COUNT16_CC1     (*(__IO uint16_t*)0x4200141EU) /**< (TC1) COUNT16 Compare and Capture 1 */
#define REG_TC1_COUNT16_PERBUF  (*(__IO uint16_t*)0x4200142EU) /**< (TC1) COUNT16 Period Buffer */
#define REG_TC1_COUNT16_CCBUF   (*(__IO uint16_t*)0x42001430U) /**< (TC1) COUNT16 Compare and Capture Buffer */
#define REG_TC1_COUNT16_CCBUF0  (*(__IO uint16_t*)0x42001430U) /**< (TC1) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC1_COUNT16_CCBUF1  (*(__IO uint16_t*)0x42001432U) /**< (TC1) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC1_COUNT32_COUNT   (*(__IO uint32_t*)0x42001414U) /**< (TC1) COUNT32 Count */
#define REG_TC1_COUNT32_PER     (*(__IO uint32_t*)0x42001418U) /**< (TC1) COUNT32 Period */
#define REG_TC1_COUNT32_CC      (*(__IO uint32_t*)0x4200141CU) /**< (TC1) COUNT32 Compare and Capture */
#define REG_TC1_COUNT32_CC0     (*(__IO uint32_t*)0x4200141CU) /**< (TC1) COUNT32 Compare and Capture 0 */
#define REG_TC1_COUNT32_CC1     (*(__IO uint32_t*)0x42001420U) /**< (TC1) COUNT32 Compare and Capture 1 */
#define REG_TC1_COUNT32_PERBUF  (*(__IO uint32_t*)0x4200142CU) /**< (TC1) COUNT32 Period Buffer */
#define REG_TC1_COUNT32_CCBUF   (*(__IO uint32_t*)0x42001430U) /**< (TC1) COUNT32 Compare and Capture Buffer */
#define REG_TC1_COUNT32_CCBUF0  (*(__IO uint32_t*)0x42001430U) /**< (TC1) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC1_COUNT32_CCBUF1  (*(__IO uint32_t*)0x42001434U) /**< (TC1) COUNT32 Compare and Capture Buffer 1 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for TC1 peripheral ========== */
#define TC1_CC_NUM                               2          
#define TC1_DMAC_ID_OVF                          13         /* Indexes of DMA Overflow trigger */
#define TC1_EXT                                  1          /* Coding of implemented extended features (keep 0 value) */
#define TC1_GCLK_ID                              14         /* Index of Generic Clock */
#define TC1_MASTER_SLAVE_MODE                    2          /* TC type 0 : NA, 1 : Master, 2 : Slave */
#define TC1_OW_NUM                               2          /* Number of Output Waveforms */
#define TC1_INSTANCE_ID                          69         

#endif /* _SAML10_TC1_INSTANCE_ */
