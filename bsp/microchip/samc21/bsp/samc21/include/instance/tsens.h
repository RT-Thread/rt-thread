/**
 * \file
 *
 * \brief Instance description for TSENS
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

#ifndef _SAMC21_TSENS_INSTANCE_
#define _SAMC21_TSENS_INSTANCE_

/* ========== Register definition for TSENS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TSENS_CTRLA            (0x40003000) /**< \brief (TSENS) Control A Register */
#define REG_TSENS_CTRLB            (0x40003001) /**< \brief (TSENS) Control B Register */
#define REG_TSENS_CTRLC            (0x40003002) /**< \brief (TSENS) Control C Register */
#define REG_TSENS_EVCTRL           (0x40003003) /**< \brief (TSENS) Event Control Register */
#define REG_TSENS_INTENCLR         (0x40003004) /**< \brief (TSENS) Interrupt Enable Clear Register */
#define REG_TSENS_INTENSET         (0x40003005) /**< \brief (TSENS) Interrupt Enable Set Register */
#define REG_TSENS_INTFLAG          (0x40003006) /**< \brief (TSENS) Interrupt Flag Status and Clear Register */
#define REG_TSENS_STATUS           (0x40003007) /**< \brief (TSENS) Status Register */
#define REG_TSENS_SYNCBUSY         (0x40003008) /**< \brief (TSENS) Synchronization Busy Register */
#define REG_TSENS_VALUE            (0x4000300C) /**< \brief (TSENS) Value Register */
#define REG_TSENS_WINLT            (0x40003010) /**< \brief (TSENS) Window Monitor Lower Threshold Register */
#define REG_TSENS_WINUT            (0x40003014) /**< \brief (TSENS) Window Monitor Upper Threshold Register */
#define REG_TSENS_GAIN             (0x40003018) /**< \brief (TSENS) Gain Register */
#define REG_TSENS_OFFSET           (0x4000301C) /**< \brief (TSENS) Offset Register */
#define REG_TSENS_CAL              (0x40003020) /**< \brief (TSENS) Calibration Register */
#define REG_TSENS_DBGCTRL          (0x40003024) /**< \brief (TSENS) Debug Control Register */
#else
#define REG_TSENS_CTRLA            (*(RwReg8 *)0x40003000UL) /**< \brief (TSENS) Control A Register */
#define REG_TSENS_CTRLB            (*(WoReg8 *)0x40003001UL) /**< \brief (TSENS) Control B Register */
#define REG_TSENS_CTRLC            (*(RwReg8 *)0x40003002UL) /**< \brief (TSENS) Control C Register */
#define REG_TSENS_EVCTRL           (*(RwReg8 *)0x40003003UL) /**< \brief (TSENS) Event Control Register */
#define REG_TSENS_INTENCLR         (*(RwReg8 *)0x40003004UL) /**< \brief (TSENS) Interrupt Enable Clear Register */
#define REG_TSENS_INTENSET         (*(RwReg8 *)0x40003005UL) /**< \brief (TSENS) Interrupt Enable Set Register */
#define REG_TSENS_INTFLAG          (*(RwReg8 *)0x40003006UL) /**< \brief (TSENS) Interrupt Flag Status and Clear Register */
#define REG_TSENS_STATUS           (*(RoReg8 *)0x40003007UL) /**< \brief (TSENS) Status Register */
#define REG_TSENS_SYNCBUSY         (*(RoReg  *)0x40003008UL) /**< \brief (TSENS) Synchronization Busy Register */
#define REG_TSENS_VALUE            (*(RoReg  *)0x4000300CUL) /**< \brief (TSENS) Value Register */
#define REG_TSENS_WINLT            (*(RwReg  *)0x40003010UL) /**< \brief (TSENS) Window Monitor Lower Threshold Register */
#define REG_TSENS_WINUT            (*(RwReg  *)0x40003014UL) /**< \brief (TSENS) Window Monitor Upper Threshold Register */
#define REG_TSENS_GAIN             (*(RwReg  *)0x40003018UL) /**< \brief (TSENS) Gain Register */
#define REG_TSENS_OFFSET           (*(RwReg  *)0x4000301CUL) /**< \brief (TSENS) Offset Register */
#define REG_TSENS_CAL              (*(RwReg  *)0x40003020UL) /**< \brief (TSENS) Calibration Register */
#define REG_TSENS_DBGCTRL          (*(RwReg8 *)0x40003024UL) /**< \brief (TSENS) Debug Control Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TSENS peripheral ========== */
#define TSENS_DMAC_ID_RESRDY        1        // Index of DMA RESRDY trigger
#define TSENS_GCLK_ID               5        // Index of Generic Clock

#endif /* _SAMC21_TSENS_INSTANCE_ */
