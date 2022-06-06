/**
 * \file
 *
 * \brief Instance description for TRNG
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
#ifndef _SAML10_TRNG_INSTANCE_H_
#define _SAML10_TRNG_INSTANCE_H_

/* ========== Register definition for TRNG peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_TRNG_CTRLA          (0x42002800) /**< (TRNG) Control A */
#define REG_TRNG_EVCTRL         (0x42002804) /**< (TRNG) Event Control */
#define REG_TRNG_INTENCLR       (0x42002808) /**< (TRNG) Interrupt Enable Clear */
#define REG_TRNG_INTENSET       (0x42002809) /**< (TRNG) Interrupt Enable Set */
#define REG_TRNG_INTFLAG        (0x4200280A) /**< (TRNG) Interrupt Flag Status and Clear */
#define REG_TRNG_DATA           (0x42002820) /**< (TRNG) Output Data */

#else

#define REG_TRNG_CTRLA          (*(__IO uint8_t*)0x42002800U) /**< (TRNG) Control A */
#define REG_TRNG_EVCTRL         (*(__IO uint8_t*)0x42002804U) /**< (TRNG) Event Control */
#define REG_TRNG_INTENCLR       (*(__IO uint8_t*)0x42002808U) /**< (TRNG) Interrupt Enable Clear */
#define REG_TRNG_INTENSET       (*(__IO uint8_t*)0x42002809U) /**< (TRNG) Interrupt Enable Set */
#define REG_TRNG_INTFLAG        (*(__IO uint8_t*)0x4200280AU) /**< (TRNG) Interrupt Flag Status and Clear */
#define REG_TRNG_DATA           (*(__I  uint32_t*)0x42002820U) /**< (TRNG) Output Data */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for TRNG peripheral ========== */
#define TRNG_INSTANCE_ID                         74         

#endif /* _SAML10_TRNG_INSTANCE_ */
