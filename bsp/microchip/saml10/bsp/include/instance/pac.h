/**
 * \file
 *
 * \brief Instance description for PAC
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
#ifndef _SAML10_PAC_INSTANCE_H_
#define _SAML10_PAC_INSTANCE_H_

/* ========== Register definition for PAC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_PAC_WRCTRL          (0x40000000) /**< (PAC) Write control */
#define REG_PAC_EVCTRL          (0x40000004) /**< (PAC) Event control */
#define REG_PAC_INTENCLR        (0x40000008) /**< (PAC) Interrupt enable clear */
#define REG_PAC_INTENSET        (0x40000009) /**< (PAC) Interrupt enable set */
#define REG_PAC_INTFLAGAHB      (0x40000010) /**< (PAC) Bridge interrupt flag status */
#define REG_PAC_INTFLAGA        (0x40000014) /**< (PAC) Peripheral interrupt flag status - Bridge A */
#define REG_PAC_INTFLAGB        (0x40000018) /**< (PAC) Peripheral interrupt flag status - Bridge B */
#define REG_PAC_INTFLAGC        (0x4000001C) /**< (PAC) Peripheral interrupt flag status - Bridge C */
#define REG_PAC_STATUSA         (0x40000034) /**< (PAC) Peripheral write protection status - Bridge A */
#define REG_PAC_STATUSB         (0x40000038) /**< (PAC) Peripheral write protection status - Bridge B */
#define REG_PAC_STATUSC         (0x4000003C) /**< (PAC) Peripheral write protection status - Bridge C */
#define REG_PAC_NONSECA         (0x40000054) /**< (PAC) Peripheral non-secure status - Bridge A */
#define REG_PAC_NONSECB         (0x40000058) /**< (PAC) Peripheral non-secure status - Bridge B */
#define REG_PAC_NONSECC         (0x4000005C) /**< (PAC) Peripheral non-secure status - Bridge C */
#define REG_PAC_SECLOCKA        (0x40000074) /**< (PAC) Peripheral secure status locked - Bridge A */
#define REG_PAC_SECLOCKB        (0x40000078) /**< (PAC) Peripheral secure status locked - Bridge B */
#define REG_PAC_SECLOCKC        (0x4000007C) /**< (PAC) Peripheral secure status locked - Bridge C */

#else

#define REG_PAC_WRCTRL          (*(__IO uint32_t*)0x40000000U) /**< (PAC) Write control */
#define REG_PAC_EVCTRL          (*(__IO uint8_t*)0x40000004U) /**< (PAC) Event control */
#define REG_PAC_INTENCLR        (*(__IO uint8_t*)0x40000008U) /**< (PAC) Interrupt enable clear */
#define REG_PAC_INTENSET        (*(__IO uint8_t*)0x40000009U) /**< (PAC) Interrupt enable set */
#define REG_PAC_INTFLAGAHB      (*(__IO uint32_t*)0x40000010U) /**< (PAC) Bridge interrupt flag status */
#define REG_PAC_INTFLAGA        (*(__IO uint32_t*)0x40000014U) /**< (PAC) Peripheral interrupt flag status - Bridge A */
#define REG_PAC_INTFLAGB        (*(__IO uint32_t*)0x40000018U) /**< (PAC) Peripheral interrupt flag status - Bridge B */
#define REG_PAC_INTFLAGC        (*(__IO uint32_t*)0x4000001CU) /**< (PAC) Peripheral interrupt flag status - Bridge C */
#define REG_PAC_STATUSA         (*(__I  uint32_t*)0x40000034U) /**< (PAC) Peripheral write protection status - Bridge A */
#define REG_PAC_STATUSB         (*(__I  uint32_t*)0x40000038U) /**< (PAC) Peripheral write protection status - Bridge B */
#define REG_PAC_STATUSC         (*(__I  uint32_t*)0x4000003CU) /**< (PAC) Peripheral write protection status - Bridge C */
#define REG_PAC_NONSECA         (*(__I  uint32_t*)0x40000054U) /**< (PAC) Peripheral non-secure status - Bridge A */
#define REG_PAC_NONSECB         (*(__I  uint32_t*)0x40000058U) /**< (PAC) Peripheral non-secure status - Bridge B */
#define REG_PAC_NONSECC         (*(__I  uint32_t*)0x4000005CU) /**< (PAC) Peripheral non-secure status - Bridge C */
#define REG_PAC_SECLOCKA        (*(__I  uint32_t*)0x40000074U) /**< (PAC) Peripheral secure status locked - Bridge A */
#define REG_PAC_SECLOCKB        (*(__I  uint32_t*)0x40000078U) /**< (PAC) Peripheral secure status locked - Bridge B */
#define REG_PAC_SECLOCKC        (*(__I  uint32_t*)0x4000007CU) /**< (PAC) Peripheral secure status locked - Bridge C */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for PAC peripheral ========== */
#define PAC_HPB_NUM                              3          /* Number of bridges AHB/APB */
#define PAC_SECURE_IMPLEMENTED                   1          /* Security Configuration implemented? */
#define PAC_INSTANCE_ID                          0          

#endif /* _SAML10_PAC_INSTANCE_ */
