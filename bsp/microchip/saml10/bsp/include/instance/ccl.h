/**
 * \file
 *
 * \brief Instance description for CCL
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
#ifndef _SAML10_CCL_INSTANCE_H_
#define _SAML10_CCL_INSTANCE_H_

/* ========== Register definition for CCL peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_CCL_CTRL            (0x42002C00) /**< (CCL) Control */
#define REG_CCL_SEQCTRL         (0x42002C04) /**< (CCL) SEQ Control x */
#define REG_CCL_SEQCTRL0        (0x42002C04) /**< (CCL) SEQ Control x 0 */
#define REG_CCL_LUTCTRL         (0x42002C08) /**< (CCL) LUT Control x */
#define REG_CCL_LUTCTRL0        (0x42002C08) /**< (CCL) LUT Control x 0 */
#define REG_CCL_LUTCTRL1        (0x42002C0C) /**< (CCL) LUT Control x 1 */

#else

#define REG_CCL_CTRL            (*(__IO uint8_t*)0x42002C00U) /**< (CCL) Control */
#define REG_CCL_SEQCTRL         (*(__IO uint8_t*)0x42002C04U) /**< (CCL) SEQ Control x */
#define REG_CCL_SEQCTRL0        (*(__IO uint8_t*)0x42002C04U) /**< (CCL) SEQ Control x 0 */
#define REG_CCL_LUTCTRL         (*(__IO uint32_t*)0x42002C08U) /**< (CCL) LUT Control x */
#define REG_CCL_LUTCTRL0        (*(__IO uint32_t*)0x42002C08U) /**< (CCL) LUT Control x 0 */
#define REG_CCL_LUTCTRL1        (*(__IO uint32_t*)0x42002C0CU) /**< (CCL) LUT Control x 1 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for CCL peripheral ========== */
#define CCL_GCLK_ID                              20         /* GCLK index for CCL */
#define CCL_LUT_NUM                              2          /* Number of LUT in a CCL */
#define CCL_SEQ_NUM                              1          /* Number of SEQ in a CCL */
#define CCL_INSTANCE_ID                          75         

#endif /* _SAML10_CCL_INSTANCE_ */
