/**
 * \file
 *
 * \brief Instance description for OSC32KCTRL
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
#ifndef _SAML10_OSC32KCTRL_INSTANCE_H_
#define _SAML10_OSC32KCTRL_INSTANCE_H_

/* ========== Register definition for OSC32KCTRL peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_OSC32KCTRL_INTENCLR (0x40001400) /**< (OSC32KCTRL) Interrupt Enable Clear */
#define REG_OSC32KCTRL_INTENSET (0x40001404) /**< (OSC32KCTRL) Interrupt Enable Set */
#define REG_OSC32KCTRL_INTFLAG  (0x40001408) /**< (OSC32KCTRL) Interrupt Flag Status and Clear */
#define REG_OSC32KCTRL_STATUS   (0x4000140C) /**< (OSC32KCTRL) Power and Clocks Status */
#define REG_OSC32KCTRL_RTCCTRL  (0x40001410) /**< (OSC32KCTRL) RTC Clock Selection */
#define REG_OSC32KCTRL_XOSC32K  (0x40001414) /**< (OSC32KCTRL) 32kHz External Crystal Oscillator (XOSC32K) Control */
#define REG_OSC32KCTRL_CFDCTRL  (0x40001416) /**< (OSC32KCTRL) Clock Failure Detector Control */
#define REG_OSC32KCTRL_EVCTRL   (0x40001417) /**< (OSC32KCTRL) Event Control */
#define REG_OSC32KCTRL_OSCULP32K (0x4000141C) /**< (OSC32KCTRL) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */

#else

#define REG_OSC32KCTRL_INTENCLR (*(__IO uint32_t*)0x40001400U) /**< (OSC32KCTRL) Interrupt Enable Clear */
#define REG_OSC32KCTRL_INTENSET (*(__IO uint32_t*)0x40001404U) /**< (OSC32KCTRL) Interrupt Enable Set */
#define REG_OSC32KCTRL_INTFLAG  (*(__IO uint32_t*)0x40001408U) /**< (OSC32KCTRL) Interrupt Flag Status and Clear */
#define REG_OSC32KCTRL_STATUS   (*(__I  uint32_t*)0x4000140CU) /**< (OSC32KCTRL) Power and Clocks Status */
#define REG_OSC32KCTRL_RTCCTRL  (*(__IO uint8_t*)0x40001410U) /**< (OSC32KCTRL) RTC Clock Selection */
#define REG_OSC32KCTRL_XOSC32K  (*(__IO uint16_t*)0x40001414U) /**< (OSC32KCTRL) 32kHz External Crystal Oscillator (XOSC32K) Control */
#define REG_OSC32KCTRL_CFDCTRL  (*(__IO uint8_t*)0x40001416U) /**< (OSC32KCTRL) Clock Failure Detector Control */
#define REG_OSC32KCTRL_EVCTRL   (*(__IO uint8_t*)0x40001417U) /**< (OSC32KCTRL) Event Control */
#define REG_OSC32KCTRL_OSCULP32K (*(__IO uint32_t*)0x4000141CU) /**< (OSC32KCTRL) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for OSC32KCTRL peripheral ========== */
#define OSC32KCTRL_OSC32K_COARSE_CALIB_MSB       0          
#define OSC32KCTRL_INSTANCE_ID                   5          

#endif /* _SAML10_OSC32KCTRL_INSTANCE_ */
