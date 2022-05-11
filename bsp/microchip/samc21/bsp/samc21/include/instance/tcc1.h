/**
 * \file
 *
 * \brief Instance description for TCC1
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

#ifndef _SAMC21_TCC1_INSTANCE_
#define _SAMC21_TCC1_INSTANCE_

/* ========== Register definition for TCC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TCC1_CTRLA             (0x42002800) /**< \brief (TCC1) Control A */
#define REG_TCC1_CTRLBCLR          (0x42002804) /**< \brief (TCC1) Control B Clear */
#define REG_TCC1_CTRLBSET          (0x42002805) /**< \brief (TCC1) Control B Set */
#define REG_TCC1_SYNCBUSY          (0x42002808) /**< \brief (TCC1) Synchronization Busy */
#define REG_TCC1_FCTRLA            (0x4200280C) /**< \brief (TCC1) Recoverable Fault A Configuration */
#define REG_TCC1_FCTRLB            (0x42002810) /**< \brief (TCC1) Recoverable Fault B Configuration */
#define REG_TCC1_DRVCTRL           (0x42002818) /**< \brief (TCC1) Driver Control */
#define REG_TCC1_DBGCTRL           (0x4200281E) /**< \brief (TCC1) Debug Control */
#define REG_TCC1_EVCTRL            (0x42002820) /**< \brief (TCC1) Event Control */
#define REG_TCC1_INTENCLR          (0x42002824) /**< \brief (TCC1) Interrupt Enable Clear */
#define REG_TCC1_INTENSET          (0x42002828) /**< \brief (TCC1) Interrupt Enable Set */
#define REG_TCC1_INTFLAG           (0x4200282C) /**< \brief (TCC1) Interrupt Flag Status and Clear */
#define REG_TCC1_STATUS            (0x42002830) /**< \brief (TCC1) Status */
#define REG_TCC1_COUNT             (0x42002834) /**< \brief (TCC1) Count */
#define REG_TCC1_PATT              (0x42002838) /**< \brief (TCC1) Pattern */
#define REG_TCC1_WAVE              (0x4200283C) /**< \brief (TCC1) Waveform Control */
#define REG_TCC1_PER               (0x42002840) /**< \brief (TCC1) Period */
#define REG_TCC1_CC0               (0x42002844) /**< \brief (TCC1) Compare and Capture 0 */
#define REG_TCC1_CC1               (0x42002848) /**< \brief (TCC1) Compare and Capture 1 */
#define REG_TCC1_PATTBUF           (0x42002864) /**< \brief (TCC1) Pattern Buffer */
#define REG_TCC1_PERBUF            (0x4200286C) /**< \brief (TCC1) Period Buffer */
#define REG_TCC1_CCBUF0            (0x42002870) /**< \brief (TCC1) Compare and Capture Buffer 0 */
#define REG_TCC1_CCBUF1            (0x42002874) /**< \brief (TCC1) Compare and Capture Buffer 1 */
#else
#define REG_TCC1_CTRLA             (*(RwReg  *)0x42002800UL) /**< \brief (TCC1) Control A */
#define REG_TCC1_CTRLBCLR          (*(RwReg8 *)0x42002804UL) /**< \brief (TCC1) Control B Clear */
#define REG_TCC1_CTRLBSET          (*(RwReg8 *)0x42002805UL) /**< \brief (TCC1) Control B Set */
#define REG_TCC1_SYNCBUSY          (*(RoReg  *)0x42002808UL) /**< \brief (TCC1) Synchronization Busy */
#define REG_TCC1_FCTRLA            (*(RwReg  *)0x4200280CUL) /**< \brief (TCC1) Recoverable Fault A Configuration */
#define REG_TCC1_FCTRLB            (*(RwReg  *)0x42002810UL) /**< \brief (TCC1) Recoverable Fault B Configuration */
#define REG_TCC1_DRVCTRL           (*(RwReg  *)0x42002818UL) /**< \brief (TCC1) Driver Control */
#define REG_TCC1_DBGCTRL           (*(RwReg8 *)0x4200281EUL) /**< \brief (TCC1) Debug Control */
#define REG_TCC1_EVCTRL            (*(RwReg  *)0x42002820UL) /**< \brief (TCC1) Event Control */
#define REG_TCC1_INTENCLR          (*(RwReg  *)0x42002824UL) /**< \brief (TCC1) Interrupt Enable Clear */
#define REG_TCC1_INTENSET          (*(RwReg  *)0x42002828UL) /**< \brief (TCC1) Interrupt Enable Set */
#define REG_TCC1_INTFLAG           (*(RwReg  *)0x4200282CUL) /**< \brief (TCC1) Interrupt Flag Status and Clear */
#define REG_TCC1_STATUS            (*(RwReg  *)0x42002830UL) /**< \brief (TCC1) Status */
#define REG_TCC1_COUNT             (*(RwReg  *)0x42002834UL) /**< \brief (TCC1) Count */
#define REG_TCC1_PATT              (*(RwReg16*)0x42002838UL) /**< \brief (TCC1) Pattern */
#define REG_TCC1_WAVE              (*(RwReg  *)0x4200283CUL) /**< \brief (TCC1) Waveform Control */
#define REG_TCC1_PER               (*(RwReg  *)0x42002840UL) /**< \brief (TCC1) Period */
#define REG_TCC1_CC0               (*(RwReg  *)0x42002844UL) /**< \brief (TCC1) Compare and Capture 0 */
#define REG_TCC1_CC1               (*(RwReg  *)0x42002848UL) /**< \brief (TCC1) Compare and Capture 1 */
#define REG_TCC1_PATTBUF           (*(RwReg16*)0x42002864UL) /**< \brief (TCC1) Pattern Buffer */
#define REG_TCC1_PERBUF            (*(RwReg  *)0x4200286CUL) /**< \brief (TCC1) Period Buffer */
#define REG_TCC1_CCBUF0            (*(RwReg  *)0x42002870UL) /**< \brief (TCC1) Compare and Capture Buffer 0 */
#define REG_TCC1_CCBUF1            (*(RwReg  *)0x42002874UL) /**< \brief (TCC1) Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TCC1 peripheral ========== */
#define TCC1_CC_NUM                 2        // Number of Compare/Capture units
#define TCC1_DITHERING              1        // Dithering feature implemented
#define TCC1_DMAC_ID_MC_0           22
#define TCC1_DMAC_ID_MC_1           23
#define TCC1_DMAC_ID_MC_LSB         22
#define TCC1_DMAC_ID_MC_MSB         23
#define TCC1_DMAC_ID_MC_SIZE        2
#define TCC1_DMAC_ID_OVF            21       // DMA overflow/underflow/retrigger trigger
#define TCC1_DTI                    0        // Dead-Time-Insertion feature implemented
#define TCC1_EXT                    24       // Coding of implemented extended features
#define TCC1_GCLK_ID                28       // Index of Generic Clock
#define TCC1_OTMX                   0        // Output Matrix feature implemented
#define TCC1_OW_NUM                 4        // Number of Output Waveforms
#define TCC1_PG                     1        // Pattern Generation feature implemented
#define TCC1_SIZE                   24      
#define TCC1_SWAP                   0        // DTI outputs swap feature implemented
#define TCC1_TYPE                   2        // TCC type 0 : NA, 1 : Master, 2 : Slave

#endif /* _SAMC21_TCC1_INSTANCE_ */
