/**
 * \file
 *
 * \brief Instance description for MCLK
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
#ifndef _SAML10_MCLK_INSTANCE_H_
#define _SAML10_MCLK_INSTANCE_H_

/* ========== Register definition for MCLK peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_MCLK_CTRLA          (0x40000800) /**< (MCLK) Control */
#define REG_MCLK_INTENCLR       (0x40000801) /**< (MCLK) Interrupt Enable Clear */
#define REG_MCLK_INTENSET       (0x40000802) /**< (MCLK) Interrupt Enable Set */
#define REG_MCLK_INTFLAG        (0x40000803) /**< (MCLK) Interrupt Flag Status and Clear */
#define REG_MCLK_CPUDIV         (0x40000804) /**< (MCLK) CPU Clock Division */
#define REG_MCLK_AHBMASK        (0x40000810) /**< (MCLK) AHB Mask */
#define REG_MCLK_APBAMASK       (0x40000814) /**< (MCLK) APBA Mask */
#define REG_MCLK_APBBMASK       (0x40000818) /**< (MCLK) APBB Mask */
#define REG_MCLK_APBCMASK       (0x4000081C) /**< (MCLK) APBC Mask */

#else

#define REG_MCLK_CTRLA          (*(__IO uint8_t*)0x40000800U) /**< (MCLK) Control */
#define REG_MCLK_INTENCLR       (*(__IO uint8_t*)0x40000801U) /**< (MCLK) Interrupt Enable Clear */
#define REG_MCLK_INTENSET       (*(__IO uint8_t*)0x40000802U) /**< (MCLK) Interrupt Enable Set */
#define REG_MCLK_INTFLAG        (*(__IO uint8_t*)0x40000803U) /**< (MCLK) Interrupt Flag Status and Clear */
#define REG_MCLK_CPUDIV         (*(__IO uint8_t*)0x40000804U) /**< (MCLK) CPU Clock Division */
#define REG_MCLK_AHBMASK        (*(__IO uint32_t*)0x40000810U) /**< (MCLK) AHB Mask */
#define REG_MCLK_APBAMASK       (*(__IO uint32_t*)0x40000814U) /**< (MCLK) APBA Mask */
#define REG_MCLK_APBBMASK       (*(__IO uint32_t*)0x40000818U) /**< (MCLK) APBB Mask */
#define REG_MCLK_APBCMASK       (*(__IO uint32_t*)0x4000081CU) /**< (MCLK) APBC Mask */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for MCLK peripheral ========== */
#define MCLK_MCLK_CLK_APB_NUM                    3          
#define MCLK_SYSTEM_CLOCK                        4000000    /* System Clock Frequency at Reset */
#define MCLK_INSTANCE_ID                         2          

#endif /* _SAML10_MCLK_INSTANCE_ */
