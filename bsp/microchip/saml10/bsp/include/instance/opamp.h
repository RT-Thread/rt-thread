/**
 * \file
 *
 * \brief Instance description for OPAMP
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
#ifndef _SAML10_OPAMP_INSTANCE_H_
#define _SAML10_OPAMP_INSTANCE_H_

/* ========== Register definition for OPAMP peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_OPAMP_CTRLA         (0x42003000) /**< (OPAMP) Control A */
#define REG_OPAMP_STATUS        (0x42003002) /**< (OPAMP) Status */
#define REG_OPAMP_OPAMPCTRL     (0x42003004) /**< (OPAMP) OPAMP n Control */
#define REG_OPAMP_OPAMPCTRL0    (0x42003004) /**< (OPAMP) OPAMP 0 Control */
#define REG_OPAMP_OPAMPCTRL1    (0x42003008) /**< (OPAMP) OPAMP 1 Control */
#define REG_OPAMP_OPAMPCTRL2    (0x4200300C) /**< (OPAMP) OPAMP 2 Control */
#define REG_OPAMP_RESCTRL       (0x42003010) /**< (OPAMP) Resister Control */

#else

#define REG_OPAMP_CTRLA         (*(__IO uint8_t*)0x42003000U) /**< (OPAMP) Control A */
#define REG_OPAMP_STATUS        (*(__I  uint8_t*)0x42003002U) /**< (OPAMP) Status */
#define REG_OPAMP_OPAMPCTRL     (*(__IO uint32_t*)0x42003004U) /**< (OPAMP) OPAMP n Control */
#define REG_OPAMP_OPAMPCTRL0    (*(__IO uint32_t*)0x42003004U) /**< (OPAMP) OPAMP 0 Control */
#define REG_OPAMP_OPAMPCTRL1    (*(__IO uint32_t*)0x42003008U) /**< (OPAMP) OPAMP 1 Control */
#define REG_OPAMP_OPAMPCTRL2    (*(__IO uint32_t*)0x4200300CU) /**< (OPAMP) OPAMP 2 Control */
#define REG_OPAMP_RESCTRL       (*(__IO uint8_t*)0x42003010U) /**< (OPAMP) Resister Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for OPAMP peripheral ========== */
#define OPAMP_INSTANCE_ID                        76         

#endif /* _SAML10_OPAMP_INSTANCE_ */
