/**
 * \file
 *
 * \brief Instance description for WDT
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
#ifndef _SAML10_WDT_INSTANCE_H_
#define _SAML10_WDT_INSTANCE_H_

/* ========== Register definition for WDT peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_WDT_CTRLA           (0x40002000) /**< (WDT) Control */
#define REG_WDT_CONFIG          (0x40002001) /**< (WDT) Configuration */
#define REG_WDT_EWCTRL          (0x40002002) /**< (WDT) Early Warning Interrupt Control */
#define REG_WDT_INTENCLR        (0x40002004) /**< (WDT) Interrupt Enable Clear */
#define REG_WDT_INTENSET        (0x40002005) /**< (WDT) Interrupt Enable Set */
#define REG_WDT_INTFLAG         (0x40002006) /**< (WDT) Interrupt Flag Status and Clear */
#define REG_WDT_SYNCBUSY        (0x40002008) /**< (WDT) Synchronization Busy */
#define REG_WDT_CLEAR           (0x4000200C) /**< (WDT) Clear */

#else

#define REG_WDT_CTRLA           (*(__IO uint8_t*)0x40002000U) /**< (WDT) Control */
#define REG_WDT_CONFIG          (*(__IO uint8_t*)0x40002001U) /**< (WDT) Configuration */
#define REG_WDT_EWCTRL          (*(__IO uint8_t*)0x40002002U) /**< (WDT) Early Warning Interrupt Control */
#define REG_WDT_INTENCLR        (*(__IO uint8_t*)0x40002004U) /**< (WDT) Interrupt Enable Clear */
#define REG_WDT_INTENSET        (*(__IO uint8_t*)0x40002005U) /**< (WDT) Interrupt Enable Set */
#define REG_WDT_INTFLAG         (*(__IO uint8_t*)0x40002006U) /**< (WDT) Interrupt Flag Status and Clear */
#define REG_WDT_SYNCBUSY        (*(__I  uint32_t*)0x40002008U) /**< (WDT) Synchronization Busy */
#define REG_WDT_CLEAR           (*(__O  uint8_t*)0x4000200CU) /**< (WDT) Clear */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for WDT peripheral ========== */
#define WDT_INSTANCE_ID                          8          

#endif /* _SAML10_WDT_INSTANCE_ */
