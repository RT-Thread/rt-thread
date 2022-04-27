/**
 * \file
 *
 * \brief Instance description for DAC
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
#ifndef _SAML10_DAC_INSTANCE_H_
#define _SAML10_DAC_INSTANCE_H_

/* ========== Register definition for DAC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_DAC_CTRLA           (0x42002000) /**< (DAC) Control A */
#define REG_DAC_CTRLB           (0x42002001) /**< (DAC) Control B */
#define REG_DAC_EVCTRL          (0x42002002) /**< (DAC) Event Control */
#define REG_DAC_INTENCLR        (0x42002004) /**< (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET        (0x42002005) /**< (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG         (0x42002006) /**< (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS          (0x42002007) /**< (DAC) Status */
#define REG_DAC_DATA            (0x42002008) /**< (DAC) Data */
#define REG_DAC_DATABUF         (0x4200200C) /**< (DAC) Data Buffer */
#define REG_DAC_SYNCBUSY        (0x42002010) /**< (DAC) Synchronization Busy */
#define REG_DAC_DBGCTRL         (0x42002014) /**< (DAC) Debug Control */

#else

#define REG_DAC_CTRLA           (*(__IO uint8_t*)0x42002000U) /**< (DAC) Control A */
#define REG_DAC_CTRLB           (*(__IO uint8_t*)0x42002001U) /**< (DAC) Control B */
#define REG_DAC_EVCTRL          (*(__IO uint8_t*)0x42002002U) /**< (DAC) Event Control */
#define REG_DAC_INTENCLR        (*(__IO uint8_t*)0x42002004U) /**< (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET        (*(__IO uint8_t*)0x42002005U) /**< (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG         (*(__IO uint8_t*)0x42002006U) /**< (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS          (*(__I  uint8_t*)0x42002007U) /**< (DAC) Status */
#define REG_DAC_DATA            (*(__O  uint16_t*)0x42002008U) /**< (DAC) Data */
#define REG_DAC_DATABUF         (*(__O  uint16_t*)0x4200200CU) /**< (DAC) Data Buffer */
#define REG_DAC_SYNCBUSY        (*(__I  uint32_t*)0x42002010U) /**< (DAC) Synchronization Busy */
#define REG_DAC_DBGCTRL         (*(__IO uint8_t*)0x42002014U) /**< (DAC) Debug Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for DAC peripheral ========== */
#define DAC_DMAC_ID_EMPTY                        20         /* Index of DMA EMPTY trigger */
#define DAC_GCLK_ID                              18         
#define DAC_INSTANCE_ID                          72         

#endif /* _SAML10_DAC_INSTANCE_ */
