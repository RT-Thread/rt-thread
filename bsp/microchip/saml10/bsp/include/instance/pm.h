/**
 * \file
 *
 * \brief Instance description for PM
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
#ifndef _SAML10_PM_INSTANCE_H_
#define _SAML10_PM_INSTANCE_H_

/* ========== Register definition for PM peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_PM_SLEEPCFG         (0x40000401) /**< (PM) Sleep Configuration */
#define REG_PM_PLCFG            (0x40000402) /**< (PM) Performance Level Configuration */
#define REG_PM_PWCFG            (0x40000403) /**< (PM) Power Configuration */
#define REG_PM_INTENCLR         (0x40000404) /**< (PM) Interrupt Enable Clear */
#define REG_PM_INTENSET         (0x40000405) /**< (PM) Interrupt Enable Set */
#define REG_PM_INTFLAG          (0x40000406) /**< (PM) Interrupt Flag Status and Clear */
#define REG_PM_STDBYCFG         (0x40000408) /**< (PM) Standby Configuration */

#else

#define REG_PM_SLEEPCFG         (*(__IO uint8_t*)0x40000401U) /**< (PM) Sleep Configuration */
#define REG_PM_PLCFG            (*(__IO uint8_t*)0x40000402U) /**< (PM) Performance Level Configuration */
#define REG_PM_PWCFG            (*(__IO uint8_t*)0x40000403U) /**< (PM) Power Configuration */
#define REG_PM_INTENCLR         (*(__IO uint8_t*)0x40000404U) /**< (PM) Interrupt Enable Clear */
#define REG_PM_INTENSET         (*(__IO uint8_t*)0x40000405U) /**< (PM) Interrupt Enable Set */
#define REG_PM_INTFLAG          (*(__IO uint8_t*)0x40000406U) /**< (PM) Interrupt Flag Status and Clear */
#define REG_PM_STDBYCFG         (*(__IO uint16_t*)0x40000408U) /**< (PM) Standby Configuration */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for PM peripheral ========== */
#define PM_BIAS_RAM_HS                           1          /* one if RAM HS can be back biased */
#define PM_PD_NUM                                1          /* Number of switchable Power Domain */
#define PM_INSTANCE_ID                           1          

#endif /* _SAML10_PM_INSTANCE_ */
