/**
 * \file
 *
 * \brief Instance description for PORT
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
#ifndef _SAML10_PORT_INSTANCE_H_
#define _SAML10_PORT_INSTANCE_H_

/* ========== Register definition for PORT peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_PORT_DIR0           (0x40003000) /**< (PORT) Data Direction 0 */
#define REG_PORT_DIRCLR0        (0x40003004) /**< (PORT) Data Direction Clear 0 */
#define REG_PORT_DIRSET0        (0x40003008) /**< (PORT) Data Direction Set 0 */
#define REG_PORT_DIRTGL0        (0x4000300C) /**< (PORT) Data Direction Toggle 0 */
#define REG_PORT_OUT0           (0x40003010) /**< (PORT) Data Output Value 0 */
#define REG_PORT_OUTCLR0        (0x40003014) /**< (PORT) Data Output Value Clear 0 */
#define REG_PORT_OUTSET0        (0x40003018) /**< (PORT) Data Output Value Set 0 */
#define REG_PORT_OUTTGL0        (0x4000301C) /**< (PORT) Data Output Value Toggle 0 */
#define REG_PORT_IN0            (0x40003020) /**< (PORT) Data Input Value 0 */
#define REG_PORT_CTRL0          (0x40003024) /**< (PORT) Control 0 */
#define REG_PORT_WRCONFIG0      (0x40003028) /**< (PORT) Write Configuration 0 */
#define REG_PORT_EVCTRL0        (0x4000302C) /**< (PORT) Event Input Control 0 */
#define REG_PORT_PMUX0          (0x40003030) /**< (PORT) Peripheral Multiplexing 0 */
#define REG_PORT_PINCFG0        (0x40003040) /**< (PORT) Pin Configuration 0 */
#define REG_PORT_INTENCLR0      (0x40003060) /**< (PORT) Interrupt Enable Clear 0 */
#define REG_PORT_INTENSET0      (0x40003064) /**< (PORT) Interrupt Enable Set 0 */
#define REG_PORT_INTFLAG0       (0x40003068) /**< (PORT) Interrupt Flag Status and Clear 0 */
#define REG_PORT_NONSEC0        (0x4000306C) /**< (PORT) Security Attribution 0 */
#define REG_PORT_NSCHK0         (0x40003070) /**< (PORT) Security Attribution Check 0 */

#else

#define REG_PORT_DIR0           (*(__IO uint32_t*)0x40003000U) /**< (PORT) Data Direction 0 */
#define REG_PORT_DIRCLR0        (*(__IO uint32_t*)0x40003004U) /**< (PORT) Data Direction Clear 0 */
#define REG_PORT_DIRSET0        (*(__IO uint32_t*)0x40003008U) /**< (PORT) Data Direction Set 0 */
#define REG_PORT_DIRTGL0        (*(__IO uint32_t*)0x4000300CU) /**< (PORT) Data Direction Toggle 0 */
#define REG_PORT_OUT0           (*(__IO uint32_t*)0x40003010U) /**< (PORT) Data Output Value 0 */
#define REG_PORT_OUTCLR0        (*(__IO uint32_t*)0x40003014U) /**< (PORT) Data Output Value Clear 0 */
#define REG_PORT_OUTSET0        (*(__IO uint32_t*)0x40003018U) /**< (PORT) Data Output Value Set 0 */
#define REG_PORT_OUTTGL0        (*(__IO uint32_t*)0x4000301CU) /**< (PORT) Data Output Value Toggle 0 */
#define REG_PORT_IN0            (*(__I  uint32_t*)0x40003020U) /**< (PORT) Data Input Value 0 */
#define REG_PORT_CTRL0          (*(__IO uint32_t*)0x40003024U) /**< (PORT) Control 0 */
#define REG_PORT_WRCONFIG0      (*(__O  uint32_t*)0x40003028U) /**< (PORT) Write Configuration 0 */
#define REG_PORT_EVCTRL0        (*(__IO uint32_t*)0x4000302CU) /**< (PORT) Event Input Control 0 */
#define REG_PORT_PMUX0          (*(__IO uint8_t*)0x40003030U) /**< (PORT) Peripheral Multiplexing 0 */
#define REG_PORT_PINCFG0        (*(__IO uint8_t*)0x40003040U) /**< (PORT) Pin Configuration 0 */
#define REG_PORT_INTENCLR0      (*(__IO uint32_t*)0x40003060U) /**< (PORT) Interrupt Enable Clear 0 */
#define REG_PORT_INTENSET0      (*(__IO uint32_t*)0x40003064U) /**< (PORT) Interrupt Enable Set 0 */
#define REG_PORT_INTFLAG0       (*(__IO uint32_t*)0x40003068U) /**< (PORT) Interrupt Flag Status and Clear 0 */
#define REG_PORT_NONSEC0        (*(__IO uint32_t*)0x4000306CU) /**< (PORT) Security Attribution 0 */
#define REG_PORT_NSCHK0         (*(__IO uint32_t*)0x40003070U) /**< (PORT) Security Attribution Check 0 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for PORT peripheral ========== */
#define PORT_BITS                                32         
#define PORT_DRVSTR                              1          /* DRVSTR supported */
#define PORT_EV_NUM                              4          
#define PORT_GROUPS                              1          
#define PORT_MSB                                 31         
#define PORT_ODRAIN                              0          /* ODRAIN supported */
#define PORT_PPP_IMPLEMENTED                     0          /* IOBUS2 implemented? */
#define PORT_SECURE_IMPLEMENTED                  1          /* Secure I/Os supported? */
#define PORT_SLEWLIM                             0          /* SLEWLIM supported */
#define PORT_INSTANCE_ID                         12         

#endif /* _SAML10_PORT_INSTANCE_ */
