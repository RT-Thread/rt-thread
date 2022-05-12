/**
 * \file
 *
 * \brief Instance description for FREQM
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
#ifndef _SAML10_FREQM_INSTANCE_H_
#define _SAML10_FREQM_INSTANCE_H_

/* ========== Register definition for FREQM peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_FREQM_CTRLA         (0x40002C00) /**< (FREQM) Control A Register */
#define REG_FREQM_CTRLB         (0x40002C01) /**< (FREQM) Control B Register */
#define REG_FREQM_CFGA          (0x40002C02) /**< (FREQM) Config A register */
#define REG_FREQM_INTENCLR      (0x40002C08) /**< (FREQM) Interrupt Enable Clear Register */
#define REG_FREQM_INTENSET      (0x40002C09) /**< (FREQM) Interrupt Enable Set Register */
#define REG_FREQM_INTFLAG       (0x40002C0A) /**< (FREQM) Interrupt Flag Register */
#define REG_FREQM_STATUS        (0x40002C0B) /**< (FREQM) Status Register */
#define REG_FREQM_SYNCBUSY      (0x40002C0C) /**< (FREQM) Synchronization Busy Register */
#define REG_FREQM_VALUE         (0x40002C10) /**< (FREQM) Count Value Register */

#else

#define REG_FREQM_CTRLA         (*(__IO uint8_t*)0x40002C00U) /**< (FREQM) Control A Register */
#define REG_FREQM_CTRLB         (*(__O  uint8_t*)0x40002C01U) /**< (FREQM) Control B Register */
#define REG_FREQM_CFGA          (*(__IO uint16_t*)0x40002C02U) /**< (FREQM) Config A register */
#define REG_FREQM_INTENCLR      (*(__IO uint8_t*)0x40002C08U) /**< (FREQM) Interrupt Enable Clear Register */
#define REG_FREQM_INTENSET      (*(__IO uint8_t*)0x40002C09U) /**< (FREQM) Interrupt Enable Set Register */
#define REG_FREQM_INTFLAG       (*(__IO uint8_t*)0x40002C0AU) /**< (FREQM) Interrupt Flag Register */
#define REG_FREQM_STATUS        (*(__IO uint8_t*)0x40002C0BU) /**< (FREQM) Status Register */
#define REG_FREQM_SYNCBUSY      (*(__I  uint32_t*)0x40002C0CU) /**< (FREQM) Synchronization Busy Register */
#define REG_FREQM_VALUE         (*(__I  uint32_t*)0x40002C10U) /**< (FREQM) Count Value Register */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for FREQM peripheral ========== */
#define FREQM_GCLK_ID_MSR                        4          /* Index of measure generic clock */
#define FREQM_GCLK_ID_REF                        5          /* Index of reference generic clock */
#define FREQM_INSTANCE_ID                        11         

#endif /* _SAML10_FREQM_INSTANCE_ */
