/**
 * \file
 *
 * \brief Instance description for GCLK
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
#ifndef _SAML10_GCLK_INSTANCE_H_
#define _SAML10_GCLK_INSTANCE_H_

/* ========== Register definition for GCLK peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_GCLK_CTRLA          (0x40001C00) /**< (GCLK) Control */
#define REG_GCLK_SYNCBUSY       (0x40001C04) /**< (GCLK) Synchronization Busy */
#define REG_GCLK_GENCTRL        (0x40001C20) /**< (GCLK) Generic Clock Generator Control */
#define REG_GCLK_GENCTRL0       (0x40001C20) /**< (GCLK) Generic Clock Generator Control 0 */
#define REG_GCLK_GENCTRL1       (0x40001C24) /**< (GCLK) Generic Clock Generator Control 1 */
#define REG_GCLK_GENCTRL2       (0x40001C28) /**< (GCLK) Generic Clock Generator Control 2 */
#define REG_GCLK_GENCTRL3       (0x40001C2C) /**< (GCLK) Generic Clock Generator Control 3 */
#define REG_GCLK_GENCTRL4       (0x40001C30) /**< (GCLK) Generic Clock Generator Control 4 */
#define REG_GCLK_PCHCTRL        (0x40001C80) /**< (GCLK) Peripheral Clock Control */
#define REG_GCLK_PCHCTRL0       (0x40001C80) /**< (GCLK) Peripheral Clock Control 0 */
#define REG_GCLK_PCHCTRL1       (0x40001C84) /**< (GCLK) Peripheral Clock Control 1 */
#define REG_GCLK_PCHCTRL2       (0x40001C88) /**< (GCLK) Peripheral Clock Control 2 */
#define REG_GCLK_PCHCTRL3       (0x40001C8C) /**< (GCLK) Peripheral Clock Control 3 */
#define REG_GCLK_PCHCTRL4       (0x40001C90) /**< (GCLK) Peripheral Clock Control 4 */
#define REG_GCLK_PCHCTRL5       (0x40001C94) /**< (GCLK) Peripheral Clock Control 5 */
#define REG_GCLK_PCHCTRL6       (0x40001C98) /**< (GCLK) Peripheral Clock Control 6 */
#define REG_GCLK_PCHCTRL7       (0x40001C9C) /**< (GCLK) Peripheral Clock Control 7 */
#define REG_GCLK_PCHCTRL8       (0x40001CA0) /**< (GCLK) Peripheral Clock Control 8 */
#define REG_GCLK_PCHCTRL9       (0x40001CA4) /**< (GCLK) Peripheral Clock Control 9 */
#define REG_GCLK_PCHCTRL10      (0x40001CA8) /**< (GCLK) Peripheral Clock Control 10 */
#define REG_GCLK_PCHCTRL11      (0x40001CAC) /**< (GCLK) Peripheral Clock Control 11 */
#define REG_GCLK_PCHCTRL12      (0x40001CB0) /**< (GCLK) Peripheral Clock Control 12 */
#define REG_GCLK_PCHCTRL13      (0x40001CB4) /**< (GCLK) Peripheral Clock Control 13 */
#define REG_GCLK_PCHCTRL14      (0x40001CB8) /**< (GCLK) Peripheral Clock Control 14 */
#define REG_GCLK_PCHCTRL15      (0x40001CBC) /**< (GCLK) Peripheral Clock Control 15 */
#define REG_GCLK_PCHCTRL16      (0x40001CC0) /**< (GCLK) Peripheral Clock Control 16 */
#define REG_GCLK_PCHCTRL17      (0x40001CC4) /**< (GCLK) Peripheral Clock Control 17 */
#define REG_GCLK_PCHCTRL18      (0x40001CC8) /**< (GCLK) Peripheral Clock Control 18 */
#define REG_GCLK_PCHCTRL19      (0x40001CCC) /**< (GCLK) Peripheral Clock Control 19 */
#define REG_GCLK_PCHCTRL20      (0x40001CD0) /**< (GCLK) Peripheral Clock Control 20 */

#else

#define REG_GCLK_CTRLA          (*(__IO uint8_t*)0x40001C00U) /**< (GCLK) Control */
#define REG_GCLK_SYNCBUSY       (*(__I  uint32_t*)0x40001C04U) /**< (GCLK) Synchronization Busy */
#define REG_GCLK_GENCTRL        (*(__IO uint32_t*)0x40001C20U) /**< (GCLK) Generic Clock Generator Control */
#define REG_GCLK_GENCTRL0       (*(__IO uint32_t*)0x40001C20U) /**< (GCLK) Generic Clock Generator Control 0 */
#define REG_GCLK_GENCTRL1       (*(__IO uint32_t*)0x40001C24U) /**< (GCLK) Generic Clock Generator Control 1 */
#define REG_GCLK_GENCTRL2       (*(__IO uint32_t*)0x40001C28U) /**< (GCLK) Generic Clock Generator Control 2 */
#define REG_GCLK_GENCTRL3       (*(__IO uint32_t*)0x40001C2CU) /**< (GCLK) Generic Clock Generator Control 3 */
#define REG_GCLK_GENCTRL4       (*(__IO uint32_t*)0x40001C30U) /**< (GCLK) Generic Clock Generator Control 4 */
#define REG_GCLK_PCHCTRL        (*(__IO uint32_t*)0x40001C80U) /**< (GCLK) Peripheral Clock Control */
#define REG_GCLK_PCHCTRL0       (*(__IO uint32_t*)0x40001C80U) /**< (GCLK) Peripheral Clock Control 0 */
#define REG_GCLK_PCHCTRL1       (*(__IO uint32_t*)0x40001C84U) /**< (GCLK) Peripheral Clock Control 1 */
#define REG_GCLK_PCHCTRL2       (*(__IO uint32_t*)0x40001C88U) /**< (GCLK) Peripheral Clock Control 2 */
#define REG_GCLK_PCHCTRL3       (*(__IO uint32_t*)0x40001C8CU) /**< (GCLK) Peripheral Clock Control 3 */
#define REG_GCLK_PCHCTRL4       (*(__IO uint32_t*)0x40001C90U) /**< (GCLK) Peripheral Clock Control 4 */
#define REG_GCLK_PCHCTRL5       (*(__IO uint32_t*)0x40001C94U) /**< (GCLK) Peripheral Clock Control 5 */
#define REG_GCLK_PCHCTRL6       (*(__IO uint32_t*)0x40001C98U) /**< (GCLK) Peripheral Clock Control 6 */
#define REG_GCLK_PCHCTRL7       (*(__IO uint32_t*)0x40001C9CU) /**< (GCLK) Peripheral Clock Control 7 */
#define REG_GCLK_PCHCTRL8       (*(__IO uint32_t*)0x40001CA0U) /**< (GCLK) Peripheral Clock Control 8 */
#define REG_GCLK_PCHCTRL9       (*(__IO uint32_t*)0x40001CA4U) /**< (GCLK) Peripheral Clock Control 9 */
#define REG_GCLK_PCHCTRL10      (*(__IO uint32_t*)0x40001CA8U) /**< (GCLK) Peripheral Clock Control 10 */
#define REG_GCLK_PCHCTRL11      (*(__IO uint32_t*)0x40001CACU) /**< (GCLK) Peripheral Clock Control 11 */
#define REG_GCLK_PCHCTRL12      (*(__IO uint32_t*)0x40001CB0U) /**< (GCLK) Peripheral Clock Control 12 */
#define REG_GCLK_PCHCTRL13      (*(__IO uint32_t*)0x40001CB4U) /**< (GCLK) Peripheral Clock Control 13 */
#define REG_GCLK_PCHCTRL14      (*(__IO uint32_t*)0x40001CB8U) /**< (GCLK) Peripheral Clock Control 14 */
#define REG_GCLK_PCHCTRL15      (*(__IO uint32_t*)0x40001CBCU) /**< (GCLK) Peripheral Clock Control 15 */
#define REG_GCLK_PCHCTRL16      (*(__IO uint32_t*)0x40001CC0U) /**< (GCLK) Peripheral Clock Control 16 */
#define REG_GCLK_PCHCTRL17      (*(__IO uint32_t*)0x40001CC4U) /**< (GCLK) Peripheral Clock Control 17 */
#define REG_GCLK_PCHCTRL18      (*(__IO uint32_t*)0x40001CC8U) /**< (GCLK) Peripheral Clock Control 18 */
#define REG_GCLK_PCHCTRL19      (*(__IO uint32_t*)0x40001CCCU) /**< (GCLK) Peripheral Clock Control 19 */
#define REG_GCLK_PCHCTRL20      (*(__IO uint32_t*)0x40001CD0U) /**< (GCLK) Peripheral Clock Control 20 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for GCLK peripheral ========== */
#define GCLK_GENDIV_BITS                         16         
#define GCLK_GEN_BITS                            3          
#define GCLK_GEN_NUM                             5          /* Number of Generic Clock Generators */
#define GCLK_GEN_NUM_MSB                         4          /* Number of Generic Clock Generators - 1 */
#define GCLK_GEN_SOURCE_NUM_MSB                  7          /* Number of Generic Clock Sources - 1 */
#define GCLK_NUM                                 21         /* Number of Generic Clock Users */
#define GCLK_SOURCE_BITS                         3          
#define GCLK_SOURCE_NUM                          8          /* Number of Generic Clock Sources */
#define GCLK_INSTANCE_ID                         7          

#endif /* _SAML10_GCLK_INSTANCE_ */
