/**
 * \file
 *
 * \brief Instance description for DIVAS
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

#ifndef _SAMC21_DIVAS_INSTANCE_
#define _SAMC21_DIVAS_INSTANCE_

/* ========== Register definition for DIVAS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_DIVAS_CTRLA            (0x48000000) /**< \brief (DIVAS) Control */
#define REG_DIVAS_STATUS           (0x48000004) /**< \brief (DIVAS) Status */
#define REG_DIVAS_DIVIDEND         (0x48000008) /**< \brief (DIVAS) Dividend */
#define REG_DIVAS_DIVISOR          (0x4800000C) /**< \brief (DIVAS) Divisor */
#define REG_DIVAS_RESULT           (0x48000010) /**< \brief (DIVAS) Result */
#define REG_DIVAS_REM              (0x48000014) /**< \brief (DIVAS) Remainder */
#define REG_DIVAS_SQRNUM           (0x48000018) /**< \brief (DIVAS) Square Root Input */
#else
#define REG_DIVAS_CTRLA            (*(RwReg8 *)0x48000000UL) /**< \brief (DIVAS) Control */
#define REG_DIVAS_STATUS           (*(RwReg8 *)0x48000004UL) /**< \brief (DIVAS) Status */
#define REG_DIVAS_DIVIDEND         (*(RwReg  *)0x48000008UL) /**< \brief (DIVAS) Dividend */
#define REG_DIVAS_DIVISOR          (*(RwReg  *)0x4800000CUL) /**< \brief (DIVAS) Divisor */
#define REG_DIVAS_RESULT           (*(RoReg  *)0x48000010UL) /**< \brief (DIVAS) Result */
#define REG_DIVAS_REM              (*(RoReg  *)0x48000014UL) /**< \brief (DIVAS) Remainder */
#define REG_DIVAS_SQRNUM           (*(RwReg  *)0x48000018UL) /**< \brief (DIVAS) Square Root Input */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for DIVAS peripheral ========== */
#define DIVAS_CLK_AHB_ID            12       // AHB clock index

#endif /* _SAMC21_DIVAS_INSTANCE_ */
