/**
 * \file
 *
 * \brief Instance description for CCL
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_CCL_INSTANCE_
#define _SAMC21_CCL_INSTANCE_

/* ========== Register definition for CCL peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CCL_CTRL               (0x42005C00) /**< \brief (CCL) Control */
#define REG_CCL_SEQCTRL0           (0x42005C04) /**< \brief (CCL) SEQ Control x 0 */
#define REG_CCL_SEQCTRL1           (0x42005C05) /**< \brief (CCL) SEQ Control x 1 */
#define REG_CCL_LUTCTRL0           (0x42005C08) /**< \brief (CCL) LUT Control x 0 */
#define REG_CCL_LUTCTRL1           (0x42005C0C) /**< \brief (CCL) LUT Control x 1 */
#define REG_CCL_LUTCTRL2           (0x42005C10) /**< \brief (CCL) LUT Control x 2 */
#define REG_CCL_LUTCTRL3           (0x42005C14) /**< \brief (CCL) LUT Control x 3 */
#else
#define REG_CCL_CTRL               (*(RwReg8 *)0x42005C00UL) /**< \brief (CCL) Control */
#define REG_CCL_SEQCTRL0           (*(RwReg8 *)0x42005C04UL) /**< \brief (CCL) SEQ Control x 0 */
#define REG_CCL_SEQCTRL1           (*(RwReg8 *)0x42005C05UL) /**< \brief (CCL) SEQ Control x 1 */
#define REG_CCL_LUTCTRL0           (*(RwReg  *)0x42005C08UL) /**< \brief (CCL) LUT Control x 0 */
#define REG_CCL_LUTCTRL1           (*(RwReg  *)0x42005C0CUL) /**< \brief (CCL) LUT Control x 1 */
#define REG_CCL_LUTCTRL2           (*(RwReg  *)0x42005C10UL) /**< \brief (CCL) LUT Control x 2 */
#define REG_CCL_LUTCTRL3           (*(RwReg  *)0x42005C14UL) /**< \brief (CCL) LUT Control x 3 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for CCL peripheral ========== */
#define CCL_GCLK_ID                 38       // GCLK index for CCL
#define CCL_IO_NUM                  12       // Numer of input pins
#define CCL_LUT_NUM                 4        // Number of LUT in a CCL
#define CCL_SEQ_NUM                 2        // Number of SEQ in a CCL

#endif /* _SAMC21_CCL_INSTANCE_ */
