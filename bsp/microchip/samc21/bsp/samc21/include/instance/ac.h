/**
 * \file
 *
 * \brief Instance description for AC
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

#ifndef _SAMC21_AC_INSTANCE_
#define _SAMC21_AC_INSTANCE_

/* ========== Register definition for AC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_AC_CTRLA               (0x42005000) /**< \brief (AC) Control A */
#define REG_AC_CTRLB               (0x42005001) /**< \brief (AC) Control B */
#define REG_AC_EVCTRL              (0x42005002) /**< \brief (AC) Event Control */
#define REG_AC_INTENCLR            (0x42005004) /**< \brief (AC) Interrupt Enable Clear */
#define REG_AC_INTENSET            (0x42005005) /**< \brief (AC) Interrupt Enable Set */
#define REG_AC_INTFLAG             (0x42005006) /**< \brief (AC) Interrupt Flag Status and Clear */
#define REG_AC_STATUSA             (0x42005007) /**< \brief (AC) Status A */
#define REG_AC_STATUSB             (0x42005008) /**< \brief (AC) Status B */
#define REG_AC_DBGCTRL             (0x42005009) /**< \brief (AC) Debug Control */
#define REG_AC_WINCTRL             (0x4200500A) /**< \brief (AC) Window Control */
#define REG_AC_SCALER0             (0x4200500C) /**< \brief (AC) Scaler 0 */
#define REG_AC_SCALER1             (0x4200500D) /**< \brief (AC) Scaler 1 */
#define REG_AC_SCALER2             (0x4200500E) /**< \brief (AC) Scaler 2 */
#define REG_AC_SCALER3             (0x4200500F) /**< \brief (AC) Scaler 3 */
#define REG_AC_COMPCTRL0           (0x42005010) /**< \brief (AC) Comparator Control 0 */
#define REG_AC_COMPCTRL1           (0x42005014) /**< \brief (AC) Comparator Control 1 */
#define REG_AC_COMPCTRL2           (0x42005018) /**< \brief (AC) Comparator Control 2 */
#define REG_AC_COMPCTRL3           (0x4200501C) /**< \brief (AC) Comparator Control 3 */
#define REG_AC_SYNCBUSY            (0x42005020) /**< \brief (AC) Synchronization Busy */
#else
#define REG_AC_CTRLA               (*(RwReg8 *)0x42005000UL) /**< \brief (AC) Control A */
#define REG_AC_CTRLB               (*(WoReg8 *)0x42005001UL) /**< \brief (AC) Control B */
#define REG_AC_EVCTRL              (*(RwReg16*)0x42005002UL) /**< \brief (AC) Event Control */
#define REG_AC_INTENCLR            (*(RwReg8 *)0x42005004UL) /**< \brief (AC) Interrupt Enable Clear */
#define REG_AC_INTENSET            (*(RwReg8 *)0x42005005UL) /**< \brief (AC) Interrupt Enable Set */
#define REG_AC_INTFLAG             (*(RwReg8 *)0x42005006UL) /**< \brief (AC) Interrupt Flag Status and Clear */
#define REG_AC_STATUSA             (*(RoReg8 *)0x42005007UL) /**< \brief (AC) Status A */
#define REG_AC_STATUSB             (*(RoReg8 *)0x42005008UL) /**< \brief (AC) Status B */
#define REG_AC_DBGCTRL             (*(RwReg8 *)0x42005009UL) /**< \brief (AC) Debug Control */
#define REG_AC_WINCTRL             (*(RwReg8 *)0x4200500AUL) /**< \brief (AC) Window Control */
#define REG_AC_SCALER0             (*(RwReg8 *)0x4200500CUL) /**< \brief (AC) Scaler 0 */
#define REG_AC_SCALER1             (*(RwReg8 *)0x4200500DUL) /**< \brief (AC) Scaler 1 */
#define REG_AC_SCALER2             (*(RwReg8 *)0x4200500EUL) /**< \brief (AC) Scaler 2 */
#define REG_AC_SCALER3             (*(RwReg8 *)0x4200500FUL) /**< \brief (AC) Scaler 3 */
#define REG_AC_COMPCTRL0           (*(RwReg  *)0x42005010UL) /**< \brief (AC) Comparator Control 0 */
#define REG_AC_COMPCTRL1           (*(RwReg  *)0x42005014UL) /**< \brief (AC) Comparator Control 1 */
#define REG_AC_COMPCTRL2           (*(RwReg  *)0x42005018UL) /**< \brief (AC) Comparator Control 2 */
#define REG_AC_COMPCTRL3           (*(RwReg  *)0x4200501CUL) /**< \brief (AC) Comparator Control 3 */
#define REG_AC_SYNCBUSY            (*(RoReg  *)0x42005020UL) /**< \brief (AC) Synchronization Busy */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for AC peripheral ========== */
#define AC_COMPCTRL_MUXNEG_OPAMP    7        // OPAMP selection for MUXNEG
#define AC_GCLK_ID                  40       // Index of Generic Clock
#define AC_NUM_CMP                  4        // Number of comparators
#define AC_SPEED_LEVELS             2        // Number of speed values

#endif /* _SAMC21_AC_INSTANCE_ */
