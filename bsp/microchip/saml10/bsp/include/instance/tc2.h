/**
 * \file
 *
 * \brief Instance description for TC2
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
#ifndef _SAML10_TC2_INSTANCE_H_
#define _SAML10_TC2_INSTANCE_H_

/* ========== Register definition for TC2 peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_TC2_CTRLA           (0x42001800) /**< (TC2) Control A */
#define REG_TC2_CTRLBCLR        (0x42001804) /**< (TC2) Control B Clear */
#define REG_TC2_CTRLBSET        (0x42001805) /**< (TC2) Control B Set */
#define REG_TC2_EVCTRL          (0x42001806) /**< (TC2) Event Control */
#define REG_TC2_INTENCLR        (0x42001808) /**< (TC2) Interrupt Enable Clear */
#define REG_TC2_INTENSET        (0x42001809) /**< (TC2) Interrupt Enable Set */
#define REG_TC2_INTFLAG         (0x4200180A) /**< (TC2) Interrupt Flag Status and Clear */
#define REG_TC2_STATUS          (0x4200180B) /**< (TC2) Status */
#define REG_TC2_WAVE            (0x4200180C) /**< (TC2) Waveform Generation Control */
#define REG_TC2_DRVCTRL         (0x4200180D) /**< (TC2) Control C */
#define REG_TC2_DBGCTRL         (0x4200180F) /**< (TC2) Debug Control */
#define REG_TC2_SYNCBUSY        (0x42001810) /**< (TC2) Synchronization Status */
#define REG_TC2_COUNT8_COUNT    (0x42001814) /**< (TC2) COUNT8 Count */
#define REG_TC2_COUNT8_PER      (0x4200181B) /**< (TC2) COUNT8 Period */
#define REG_TC2_COUNT8_CC       (0x4200181C) /**< (TC2) COUNT8 Compare and Capture */
#define REG_TC2_COUNT8_CC0      (0x4200181C) /**< (TC2) COUNT8 Compare and Capture 0 */
#define REG_TC2_COUNT8_CC1      (0x4200181D) /**< (TC2) COUNT8 Compare and Capture 1 */
#define REG_TC2_COUNT8_PERBUF   (0x4200182F) /**< (TC2) COUNT8 Period Buffer */
#define REG_TC2_COUNT8_CCBUF    (0x42001830) /**< (TC2) COUNT8 Compare and Capture Buffer */
#define REG_TC2_COUNT8_CCBUF0   (0x42001830) /**< (TC2) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC2_COUNT8_CCBUF1   (0x42001831) /**< (TC2) COUNT8 Compare and Capture Buffer 1 */
#define REG_TC2_COUNT16_COUNT   (0x42001814) /**< (TC2) COUNT16 Count */
#define REG_TC2_COUNT16_PER     (0x4200181A) /**< (TC2) COUNT16 Period */
#define REG_TC2_COUNT16_CC      (0x4200181C) /**< (TC2) COUNT16 Compare and Capture */
#define REG_TC2_COUNT16_CC0     (0x4200181C) /**< (TC2) COUNT16 Compare and Capture 0 */
#define REG_TC2_COUNT16_CC1     (0x4200181E) /**< (TC2) COUNT16 Compare and Capture 1 */
#define REG_TC2_COUNT16_PERBUF  (0x4200182E) /**< (TC2) COUNT16 Period Buffer */
#define REG_TC2_COUNT16_CCBUF   (0x42001830) /**< (TC2) COUNT16 Compare and Capture Buffer */
#define REG_TC2_COUNT16_CCBUF0  (0x42001830) /**< (TC2) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC2_COUNT16_CCBUF1  (0x42001832) /**< (TC2) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC2_COUNT32_COUNT   (0x42001814) /**< (TC2) COUNT32 Count */
#define REG_TC2_COUNT32_PER     (0x42001818) /**< (TC2) COUNT32 Period */
#define REG_TC2_COUNT32_CC      (0x4200181C) /**< (TC2) COUNT32 Compare and Capture */
#define REG_TC2_COUNT32_CC0     (0x4200181C) /**< (TC2) COUNT32 Compare and Capture 0 */
#define REG_TC2_COUNT32_CC1     (0x42001820) /**< (TC2) COUNT32 Compare and Capture 1 */
#define REG_TC2_COUNT32_PERBUF  (0x4200182C) /**< (TC2) COUNT32 Period Buffer */
#define REG_TC2_COUNT32_CCBUF   (0x42001830) /**< (TC2) COUNT32 Compare and Capture Buffer */
#define REG_TC2_COUNT32_CCBUF0  (0x42001830) /**< (TC2) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC2_COUNT32_CCBUF1  (0x42001834) /**< (TC2) COUNT32 Compare and Capture Buffer 1 */

#else

#define REG_TC2_CTRLA           (*(__IO uint32_t*)0x42001800U) /**< (TC2) Control A */
#define REG_TC2_CTRLBCLR        (*(__IO uint8_t*)0x42001804U) /**< (TC2) Control B Clear */
#define REG_TC2_CTRLBSET        (*(__IO uint8_t*)0x42001805U) /**< (TC2) Control B Set */
#define REG_TC2_EVCTRL          (*(__IO uint16_t*)0x42001806U) /**< (TC2) Event Control */
#define REG_TC2_INTENCLR        (*(__IO uint8_t*)0x42001808U) /**< (TC2) Interrupt Enable Clear */
#define REG_TC2_INTENSET        (*(__IO uint8_t*)0x42001809U) /**< (TC2) Interrupt Enable Set */
#define REG_TC2_INTFLAG         (*(__IO uint8_t*)0x4200180AU) /**< (TC2) Interrupt Flag Status and Clear */
#define REG_TC2_STATUS          (*(__IO uint8_t*)0x4200180BU) /**< (TC2) Status */
#define REG_TC2_WAVE            (*(__IO uint8_t*)0x4200180CU) /**< (TC2) Waveform Generation Control */
#define REG_TC2_DRVCTRL         (*(__IO uint8_t*)0x4200180DU) /**< (TC2) Control C */
#define REG_TC2_DBGCTRL         (*(__IO uint8_t*)0x4200180FU) /**< (TC2) Debug Control */
#define REG_TC2_SYNCBUSY        (*(__I  uint32_t*)0x42001810U) /**< (TC2) Synchronization Status */
#define REG_TC2_COUNT8_COUNT    (*(__IO uint8_t*)0x42001814U) /**< (TC2) COUNT8 Count */
#define REG_TC2_COUNT8_PER      (*(__IO uint8_t*)0x4200181BU) /**< (TC2) COUNT8 Period */
#define REG_TC2_COUNT8_CC       (*(__IO uint8_t*)0x4200181CU) /**< (TC2) COUNT8 Compare and Capture */
#define REG_TC2_COUNT8_CC0      (*(__IO uint8_t*)0x4200181CU) /**< (TC2) COUNT8 Compare and Capture 0 */
#define REG_TC2_COUNT8_CC1      (*(__IO uint8_t*)0x4200181DU) /**< (TC2) COUNT8 Compare and Capture 1 */
#define REG_TC2_COUNT8_PERBUF   (*(__IO uint8_t*)0x4200182FU) /**< (TC2) COUNT8 Period Buffer */
#define REG_TC2_COUNT8_CCBUF    (*(__IO uint8_t*)0x42001830U) /**< (TC2) COUNT8 Compare and Capture Buffer */
#define REG_TC2_COUNT8_CCBUF0   (*(__IO uint8_t*)0x42001830U) /**< (TC2) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC2_COUNT8_CCBUF1   (*(__IO uint8_t*)0x42001831U) /**< (TC2) COUNT8 Compare and Capture Buffer 1 */
#define REG_TC2_COUNT16_COUNT   (*(__IO uint16_t*)0x42001814U) /**< (TC2) COUNT16 Count */
#define REG_TC2_COUNT16_PER     (*(__IO uint16_t*)0x4200181AU) /**< (TC2) COUNT16 Period */
#define REG_TC2_COUNT16_CC      (*(__IO uint16_t*)0x4200181CU) /**< (TC2) COUNT16 Compare and Capture */
#define REG_TC2_COUNT16_CC0     (*(__IO uint16_t*)0x4200181CU) /**< (TC2) COUNT16 Compare and Capture 0 */
#define REG_TC2_COUNT16_CC1     (*(__IO uint16_t*)0x4200181EU) /**< (TC2) COUNT16 Compare and Capture 1 */
#define REG_TC2_COUNT16_PERBUF  (*(__IO uint16_t*)0x4200182EU) /**< (TC2) COUNT16 Period Buffer */
#define REG_TC2_COUNT16_CCBUF   (*(__IO uint16_t*)0x42001830U) /**< (TC2) COUNT16 Compare and Capture Buffer */
#define REG_TC2_COUNT16_CCBUF0  (*(__IO uint16_t*)0x42001830U) /**< (TC2) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC2_COUNT16_CCBUF1  (*(__IO uint16_t*)0x42001832U) /**< (TC2) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC2_COUNT32_COUNT   (*(__IO uint32_t*)0x42001814U) /**< (TC2) COUNT32 Count */
#define REG_TC2_COUNT32_PER     (*(__IO uint32_t*)0x42001818U) /**< (TC2) COUNT32 Period */
#define REG_TC2_COUNT32_CC      (*(__IO uint32_t*)0x4200181CU) /**< (TC2) COUNT32 Compare and Capture */
#define REG_TC2_COUNT32_CC0     (*(__IO uint32_t*)0x4200181CU) /**< (TC2) COUNT32 Compare and Capture 0 */
#define REG_TC2_COUNT32_CC1     (*(__IO uint32_t*)0x42001820U) /**< (TC2) COUNT32 Compare and Capture 1 */
#define REG_TC2_COUNT32_PERBUF  (*(__IO uint32_t*)0x4200182CU) /**< (TC2) COUNT32 Period Buffer */
#define REG_TC2_COUNT32_CCBUF   (*(__IO uint32_t*)0x42001830U) /**< (TC2) COUNT32 Compare and Capture Buffer */
#define REG_TC2_COUNT32_CCBUF0  (*(__IO uint32_t*)0x42001830U) /**< (TC2) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC2_COUNT32_CCBUF1  (*(__IO uint32_t*)0x42001834U) /**< (TC2) COUNT32 Compare and Capture Buffer 1 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for TC2 peripheral ========== */
#define TC2_CC_NUM                               2          
#define TC2_DMAC_ID_OVF                          16         /* Indexes of DMA Overflow trigger */
#define TC2_EXT                                  1          /* Coding of implemented extended features (keep 0 value) */
#define TC2_GCLK_ID                              15         /* Index of Generic Clock */
#define TC2_MASTER_SLAVE_MODE                    0          /* TC type 0 : NA, 1 : Master, 2 : Slave */
#define TC2_OW_NUM                               2          /* Number of Output Waveforms */
#define TC2_INSTANCE_ID                          70         

#endif /* _SAML10_TC2_INSTANCE_ */
