/**
 * \file
 *
 * \brief Instance description for SDADC
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

#ifndef _SAMC21_SDADC_INSTANCE_
#define _SAMC21_SDADC_INSTANCE_

/* ========== Register definition for SDADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SDADC_CTRLA            (0x42004C00) /**< \brief (SDADC) Control A */
#define REG_SDADC_REFCTRL          (0x42004C01) /**< \brief (SDADC) Reference Control */
#define REG_SDADC_CTRLB            (0x42004C02) /**< \brief (SDADC) Control B */
#define REG_SDADC_EVCTRL           (0x42004C04) /**< \brief (SDADC) Event Control */
#define REG_SDADC_INTENCLR         (0x42004C05) /**< \brief (SDADC) Interrupt Enable Clear */
#define REG_SDADC_INTENSET         (0x42004C06) /**< \brief (SDADC) Interrupt Enable Set */
#define REG_SDADC_INTFLAG          (0x42004C07) /**< \brief (SDADC) Interrupt Flag Status and Clear */
#define REG_SDADC_SEQSTATUS        (0x42004C08) /**< \brief (SDADC) Sequence Status */
#define REG_SDADC_INPUTCTRL        (0x42004C09) /**< \brief (SDADC) Input Control */
#define REG_SDADC_CTRLC            (0x42004C0A) /**< \brief (SDADC) Control C */
#define REG_SDADC_WINCTRL          (0x42004C0B) /**< \brief (SDADC) Window Monitor Control */
#define REG_SDADC_WINLT            (0x42004C0C) /**< \brief (SDADC) Window Monitor Lower Threshold */
#define REG_SDADC_WINUT            (0x42004C10) /**< \brief (SDADC) Window Monitor Upper Threshold */
#define REG_SDADC_OFFSETCORR       (0x42004C14) /**< \brief (SDADC) Offset Correction */
#define REG_SDADC_GAINCORR         (0x42004C18) /**< \brief (SDADC) Gain Correction */
#define REG_SDADC_SHIFTCORR        (0x42004C1A) /**< \brief (SDADC) Shift Correction */
#define REG_SDADC_SWTRIG           (0x42004C1C) /**< \brief (SDADC) Software Trigger */
#define REG_SDADC_SYNCBUSY         (0x42004C20) /**< \brief (SDADC) Synchronization Busy */
#define REG_SDADC_RESULT           (0x42004C24) /**< \brief (SDADC) Result */
#define REG_SDADC_SEQCTRL          (0x42004C28) /**< \brief (SDADC) Sequence Control */
#define REG_SDADC_ANACTRL          (0x42004C2C) /**< \brief (SDADC) Analog Control */
#define REG_SDADC_DBGCTRL          (0x42004C2E) /**< \brief (SDADC) Debug Control */
#else
#define REG_SDADC_CTRLA            (*(RwReg8 *)0x42004C00UL) /**< \brief (SDADC) Control A */
#define REG_SDADC_REFCTRL          (*(RwReg8 *)0x42004C01UL) /**< \brief (SDADC) Reference Control */
#define REG_SDADC_CTRLB            (*(RwReg16*)0x42004C02UL) /**< \brief (SDADC) Control B */
#define REG_SDADC_EVCTRL           (*(RwReg8 *)0x42004C04UL) /**< \brief (SDADC) Event Control */
#define REG_SDADC_INTENCLR         (*(RwReg8 *)0x42004C05UL) /**< \brief (SDADC) Interrupt Enable Clear */
#define REG_SDADC_INTENSET         (*(RwReg8 *)0x42004C06UL) /**< \brief (SDADC) Interrupt Enable Set */
#define REG_SDADC_INTFLAG          (*(RwReg8 *)0x42004C07UL) /**< \brief (SDADC) Interrupt Flag Status and Clear */
#define REG_SDADC_SEQSTATUS        (*(RoReg8 *)0x42004C08UL) /**< \brief (SDADC) Sequence Status */
#define REG_SDADC_INPUTCTRL        (*(RwReg8 *)0x42004C09UL) /**< \brief (SDADC) Input Control */
#define REG_SDADC_CTRLC            (*(RwReg8 *)0x42004C0AUL) /**< \brief (SDADC) Control C */
#define REG_SDADC_WINCTRL          (*(RwReg8 *)0x42004C0BUL) /**< \brief (SDADC) Window Monitor Control */
#define REG_SDADC_WINLT            (*(RwReg  *)0x42004C0CUL) /**< \brief (SDADC) Window Monitor Lower Threshold */
#define REG_SDADC_WINUT            (*(RwReg  *)0x42004C10UL) /**< \brief (SDADC) Window Monitor Upper Threshold */
#define REG_SDADC_OFFSETCORR       (*(RwReg  *)0x42004C14UL) /**< \brief (SDADC) Offset Correction */
#define REG_SDADC_GAINCORR         (*(RwReg16*)0x42004C18UL) /**< \brief (SDADC) Gain Correction */
#define REG_SDADC_SHIFTCORR        (*(RwReg8 *)0x42004C1AUL) /**< \brief (SDADC) Shift Correction */
#define REG_SDADC_SWTRIG           (*(RwReg8 *)0x42004C1CUL) /**< \brief (SDADC) Software Trigger */
#define REG_SDADC_SYNCBUSY         (*(RoReg  *)0x42004C20UL) /**< \brief (SDADC) Synchronization Busy */
#define REG_SDADC_RESULT           (*(RoReg  *)0x42004C24UL) /**< \brief (SDADC) Result */
#define REG_SDADC_SEQCTRL          (*(RwReg8 *)0x42004C28UL) /**< \brief (SDADC) Sequence Control */
#define REG_SDADC_ANACTRL          (*(RwReg8 *)0x42004C2CUL) /**< \brief (SDADC) Analog Control */
#define REG_SDADC_DBGCTRL          (*(RwReg8 *)0x42004C2EUL) /**< \brief (SDADC) Debug Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for SDADC peripheral ========== */
#define SDADC_DMAC_ID_RESRDY        44       // Index of DMA RESRDY trigger
#define SDADC_EXT_CHANNELS          3        // Number of external channels
#define SDADC_GCLK_ID               35       // Index of generic clock

#endif /* _SAMC21_SDADC_INSTANCE_ */
