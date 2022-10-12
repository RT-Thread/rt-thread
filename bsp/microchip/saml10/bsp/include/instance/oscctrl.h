/**
 * \file
 *
 * \brief Instance description for OSCCTRL
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
#ifndef _SAML10_OSCCTRL_INSTANCE_H_
#define _SAML10_OSCCTRL_INSTANCE_H_

/* ========== Register definition for OSCCTRL peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_OSCCTRL_EVCTRL      (0x40001000) /**< (OSCCTRL) Event Control */
#define REG_OSCCTRL_INTENCLR    (0x40001004) /**< (OSCCTRL) Interrupt Enable Clear */
#define REG_OSCCTRL_INTENSET    (0x40001008) /**< (OSCCTRL) Interrupt Enable Set */
#define REG_OSCCTRL_INTFLAG     (0x4000100C) /**< (OSCCTRL) Interrupt Flag Status and Clear */
#define REG_OSCCTRL_STATUS      (0x40001010) /**< (OSCCTRL) Status */
#define REG_OSCCTRL_XOSCCTRL    (0x40001014) /**< (OSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control */
#define REG_OSCCTRL_CFDPRESC    (0x40001016) /**< (OSCCTRL) Clock Failure Detector Prescaler */
#define REG_OSCCTRL_OSC16MCTRL  (0x40001018) /**< (OSCCTRL) 16MHz Internal Oscillator (OSC16M) Control */
#define REG_OSCCTRL_DFLLULPCTRL (0x4000101C) /**< (OSCCTRL) DFLLULP Control */
#define REG_OSCCTRL_DFLLULPDITHER (0x4000101E) /**< (OSCCTRL) DFLLULP Dither Control */
#define REG_OSCCTRL_DFLLULPRREQ (0x4000101F) /**< (OSCCTRL) DFLLULP Read Request */
#define REG_OSCCTRL_DFLLULPDLY  (0x40001020) /**< (OSCCTRL) DFLLULP Delay Value */
#define REG_OSCCTRL_DFLLULPRATIO (0x40001024) /**< (OSCCTRL) DFLLULP Target Ratio */
#define REG_OSCCTRL_DFLLULPSYNCBUSY (0x40001028) /**< (OSCCTRL) DFLLULP Synchronization Busy */
#define REG_OSCCTRL_DPLLCTRLA   (0x4000102C) /**< (OSCCTRL) DPLL Control A */
#define REG_OSCCTRL_DPLLRATIO   (0x40001030) /**< (OSCCTRL) DPLL Ratio Control */
#define REG_OSCCTRL_DPLLCTRLB   (0x40001034) /**< (OSCCTRL) DPLL Control B */
#define REG_OSCCTRL_DPLLPRESC   (0x40001038) /**< (OSCCTRL) DPLL Prescaler */
#define REG_OSCCTRL_DPLLSYNCBUSY (0x4000103C) /**< (OSCCTRL) DPLL Synchronization Busy */
#define REG_OSCCTRL_DPLLSTATUS  (0x40001040) /**< (OSCCTRL) DPLL Status */

#else

#define REG_OSCCTRL_EVCTRL      (*(__IO uint8_t*)0x40001000U) /**< (OSCCTRL) Event Control */
#define REG_OSCCTRL_INTENCLR    (*(__IO uint32_t*)0x40001004U) /**< (OSCCTRL) Interrupt Enable Clear */
#define REG_OSCCTRL_INTENSET    (*(__IO uint32_t*)0x40001008U) /**< (OSCCTRL) Interrupt Enable Set */
#define REG_OSCCTRL_INTFLAG     (*(__IO uint32_t*)0x4000100CU) /**< (OSCCTRL) Interrupt Flag Status and Clear */
#define REG_OSCCTRL_STATUS      (*(__I  uint32_t*)0x40001010U) /**< (OSCCTRL) Status */
#define REG_OSCCTRL_XOSCCTRL    (*(__IO uint16_t*)0x40001014U) /**< (OSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control */
#define REG_OSCCTRL_CFDPRESC    (*(__IO uint8_t*)0x40001016U) /**< (OSCCTRL) Clock Failure Detector Prescaler */
#define REG_OSCCTRL_OSC16MCTRL  (*(__IO uint8_t*)0x40001018U) /**< (OSCCTRL) 16MHz Internal Oscillator (OSC16M) Control */
#define REG_OSCCTRL_DFLLULPCTRL (*(__IO uint16_t*)0x4000101CU) /**< (OSCCTRL) DFLLULP Control */
#define REG_OSCCTRL_DFLLULPDITHER (*(__IO uint8_t*)0x4000101EU) /**< (OSCCTRL) DFLLULP Dither Control */
#define REG_OSCCTRL_DFLLULPRREQ (*(__IO uint8_t*)0x4000101FU) /**< (OSCCTRL) DFLLULP Read Request */
#define REG_OSCCTRL_DFLLULPDLY  (*(__IO uint32_t*)0x40001020U) /**< (OSCCTRL) DFLLULP Delay Value */
#define REG_OSCCTRL_DFLLULPRATIO (*(__IO uint32_t*)0x40001024U) /**< (OSCCTRL) DFLLULP Target Ratio */
#define REG_OSCCTRL_DFLLULPSYNCBUSY (*(__I  uint32_t*)0x40001028U) /**< (OSCCTRL) DFLLULP Synchronization Busy */
#define REG_OSCCTRL_DPLLCTRLA   (*(__IO uint8_t*)0x4000102CU) /**< (OSCCTRL) DPLL Control A */
#define REG_OSCCTRL_DPLLRATIO   (*(__IO uint32_t*)0x40001030U) /**< (OSCCTRL) DPLL Ratio Control */
#define REG_OSCCTRL_DPLLCTRLB   (*(__IO uint32_t*)0x40001034U) /**< (OSCCTRL) DPLL Control B */
#define REG_OSCCTRL_DPLLPRESC   (*(__IO uint8_t*)0x40001038U) /**< (OSCCTRL) DPLL Prescaler */
#define REG_OSCCTRL_DPLLSYNCBUSY (*(__I  uint8_t*)0x4000103CU) /**< (OSCCTRL) DPLL Synchronization Busy */
#define REG_OSCCTRL_DPLLSTATUS  (*(__I  uint8_t*)0x40001040U) /**< (OSCCTRL) DPLL Status */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for OSCCTRL peripheral ========== */
#define OSCCTRL_GCLK_ID_DFLLULP                  2          /* Index of Generic Clock for DFLLULP */
#define OSCCTRL_GCLK_ID_DPLL                     0          /* Index of Generic Clock for DPLL */
#define OSCCTRL_GCLK_ID_DPLL32K                  1          /* Index of Generic Clock for DPLL 32K */
#define OSCCTRL_CFD_VERSION                      0x112      
#define OSCCTRL_DFLLULP_VERSION                  0x100      
#define OSCCTRL_FDPLL_VERSION                    0x213      
#define OSCCTRL_OSC16M_VERSION                   0x102      
#define OSCCTRL_XOSC_VERSION                     0x210      
#define OSCCTRL_INSTANCE_ID                      4          

#endif /* _SAML10_OSCCTRL_INSTANCE_ */
