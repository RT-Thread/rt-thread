/**
 * \file
 *
 * \brief Instance description for ADC1
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

#ifndef _SAMC21_ADC1_INSTANCE_
#define _SAMC21_ADC1_INSTANCE_

/* ========== Register definition for ADC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC1_CTRLA             (0x42004800) /**< \brief (ADC1) Control A */
#define REG_ADC1_CTRLB             (0x42004801) /**< \brief (ADC1) Control B */
#define REG_ADC1_REFCTRL           (0x42004802) /**< \brief (ADC1) Reference Control */
#define REG_ADC1_EVCTRL            (0x42004803) /**< \brief (ADC1) Event Control */
#define REG_ADC1_INTENCLR          (0x42004804) /**< \brief (ADC1) Interrupt Enable Clear */
#define REG_ADC1_INTENSET          (0x42004805) /**< \brief (ADC1) Interrupt Enable Set */
#define REG_ADC1_INTFLAG           (0x42004806) /**< \brief (ADC1) Interrupt Flag Status and Clear */
#define REG_ADC1_SEQSTATUS         (0x42004807) /**< \brief (ADC1) Sequence Status */
#define REG_ADC1_INPUTCTRL         (0x42004808) /**< \brief (ADC1) Input Control */
#define REG_ADC1_CTRLC             (0x4200480A) /**< \brief (ADC1) Control C */
#define REG_ADC1_AVGCTRL           (0x4200480C) /**< \brief (ADC1) Average Control */
#define REG_ADC1_SAMPCTRL          (0x4200480D) /**< \brief (ADC1) Sample Time Control */
#define REG_ADC1_WINLT             (0x4200480E) /**< \brief (ADC1) Window Monitor Lower Threshold */
#define REG_ADC1_WINUT             (0x42004810) /**< \brief (ADC1) Window Monitor Upper Threshold */
#define REG_ADC1_GAINCORR          (0x42004812) /**< \brief (ADC1) Gain Correction */
#define REG_ADC1_OFFSETCORR        (0x42004814) /**< \brief (ADC1) Offset Correction */
#define REG_ADC1_SWTRIG            (0x42004818) /**< \brief (ADC1) Software Trigger */
#define REG_ADC1_DBGCTRL           (0x4200481C) /**< \brief (ADC1) Debug Control */
#define REG_ADC1_SYNCBUSY          (0x42004820) /**< \brief (ADC1) Synchronization Busy */
#define REG_ADC1_RESULT            (0x42004824) /**< \brief (ADC1) Result */
#define REG_ADC1_SEQCTRL           (0x42004828) /**< \brief (ADC1) Sequence Control */
#define REG_ADC1_CALIB             (0x4200482C) /**< \brief (ADC1) Calibration */
#else
#define REG_ADC1_CTRLA             (*(RwReg8 *)0x42004800UL) /**< \brief (ADC1) Control A */
#define REG_ADC1_CTRLB             (*(RwReg8 *)0x42004801UL) /**< \brief (ADC1) Control B */
#define REG_ADC1_REFCTRL           (*(RwReg8 *)0x42004802UL) /**< \brief (ADC1) Reference Control */
#define REG_ADC1_EVCTRL            (*(RwReg8 *)0x42004803UL) /**< \brief (ADC1) Event Control */
#define REG_ADC1_INTENCLR          (*(RwReg8 *)0x42004804UL) /**< \brief (ADC1) Interrupt Enable Clear */
#define REG_ADC1_INTENSET          (*(RwReg8 *)0x42004805UL) /**< \brief (ADC1) Interrupt Enable Set */
#define REG_ADC1_INTFLAG           (*(RwReg8 *)0x42004806UL) /**< \brief (ADC1) Interrupt Flag Status and Clear */
#define REG_ADC1_SEQSTATUS         (*(RoReg8 *)0x42004807UL) /**< \brief (ADC1) Sequence Status */
#define REG_ADC1_INPUTCTRL         (*(RwReg16*)0x42004808UL) /**< \brief (ADC1) Input Control */
#define REG_ADC1_CTRLC             (*(RwReg16*)0x4200480AUL) /**< \brief (ADC1) Control C */
#define REG_ADC1_AVGCTRL           (*(RwReg8 *)0x4200480CUL) /**< \brief (ADC1) Average Control */
#define REG_ADC1_SAMPCTRL          (*(RwReg8 *)0x4200480DUL) /**< \brief (ADC1) Sample Time Control */
#define REG_ADC1_WINLT             (*(RwReg16*)0x4200480EUL) /**< \brief (ADC1) Window Monitor Lower Threshold */
#define REG_ADC1_WINUT             (*(RwReg16*)0x42004810UL) /**< \brief (ADC1) Window Monitor Upper Threshold */
#define REG_ADC1_GAINCORR          (*(RwReg16*)0x42004812UL) /**< \brief (ADC1) Gain Correction */
#define REG_ADC1_OFFSETCORR        (*(RwReg16*)0x42004814UL) /**< \brief (ADC1) Offset Correction */
#define REG_ADC1_SWTRIG            (*(RwReg8 *)0x42004818UL) /**< \brief (ADC1) Software Trigger */
#define REG_ADC1_DBGCTRL           (*(RwReg8 *)0x4200481CUL) /**< \brief (ADC1) Debug Control */
#define REG_ADC1_SYNCBUSY          (*(RoReg16*)0x42004820UL) /**< \brief (ADC1) Synchronization Busy */
#define REG_ADC1_RESULT            (*(RoReg16*)0x42004824UL) /**< \brief (ADC1) Result */
#define REG_ADC1_SEQCTRL           (*(RwReg  *)0x42004828UL) /**< \brief (ADC1) Sequence Control */
#define REG_ADC1_CALIB             (*(RwReg16*)0x4200482CUL) /**< \brief (ADC1) Calibration */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for ADC1 peripheral ========== */
#define ADC1_DMAC_ID_RESRDY         43       // index of DMA RESRDY trigger
#define ADC1_EXTCHANNEL_MSB         11       // Number of external channels
#define ADC1_GCLK_ID                34       // index of Generic Clock
#define ADC1_INT_CH30               0        // Select OPAMP or CTAT on Channel 30
#define ADC1_MASTER_SLAVE_MODE      2        // ADC Master/Slave Mode

#endif /* _SAMC21_ADC1_INSTANCE_ */
