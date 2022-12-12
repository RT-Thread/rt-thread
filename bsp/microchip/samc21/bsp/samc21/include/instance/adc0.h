/**
 * \file
 *
 * \brief Instance description for ADC0
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

#ifndef _SAMC21_ADC0_INSTANCE_
#define _SAMC21_ADC0_INSTANCE_

/* ========== Register definition for ADC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC0_CTRLA             (0x42004400) /**< \brief (ADC0) Control A */
#define REG_ADC0_CTRLB             (0x42004401) /**< \brief (ADC0) Control B */
#define REG_ADC0_REFCTRL           (0x42004402) /**< \brief (ADC0) Reference Control */
#define REG_ADC0_EVCTRL            (0x42004403) /**< \brief (ADC0) Event Control */
#define REG_ADC0_INTENCLR          (0x42004404) /**< \brief (ADC0) Interrupt Enable Clear */
#define REG_ADC0_INTENSET          (0x42004405) /**< \brief (ADC0) Interrupt Enable Set */
#define REG_ADC0_INTFLAG           (0x42004406) /**< \brief (ADC0) Interrupt Flag Status and Clear */
#define REG_ADC0_SEQSTATUS         (0x42004407) /**< \brief (ADC0) Sequence Status */
#define REG_ADC0_INPUTCTRL         (0x42004408) /**< \brief (ADC0) Input Control */
#define REG_ADC0_CTRLC             (0x4200440A) /**< \brief (ADC0) Control C */
#define REG_ADC0_AVGCTRL           (0x4200440C) /**< \brief (ADC0) Average Control */
#define REG_ADC0_SAMPCTRL          (0x4200440D) /**< \brief (ADC0) Sample Time Control */
#define REG_ADC0_WINLT             (0x4200440E) /**< \brief (ADC0) Window Monitor Lower Threshold */
#define REG_ADC0_WINUT             (0x42004410) /**< \brief (ADC0) Window Monitor Upper Threshold */
#define REG_ADC0_GAINCORR          (0x42004412) /**< \brief (ADC0) Gain Correction */
#define REG_ADC0_OFFSETCORR        (0x42004414) /**< \brief (ADC0) Offset Correction */
#define REG_ADC0_SWTRIG            (0x42004418) /**< \brief (ADC0) Software Trigger */
#define REG_ADC0_DBGCTRL           (0x4200441C) /**< \brief (ADC0) Debug Control */
#define REG_ADC0_SYNCBUSY          (0x42004420) /**< \brief (ADC0) Synchronization Busy */
#define REG_ADC0_RESULT            (0x42004424) /**< \brief (ADC0) Result */
#define REG_ADC0_SEQCTRL           (0x42004428) /**< \brief (ADC0) Sequence Control */
#define REG_ADC0_CALIB             (0x4200442C) /**< \brief (ADC0) Calibration */
#else
#define REG_ADC0_CTRLA             (*(RwReg8 *)0x42004400UL) /**< \brief (ADC0) Control A */
#define REG_ADC0_CTRLB             (*(RwReg8 *)0x42004401UL) /**< \brief (ADC0) Control B */
#define REG_ADC0_REFCTRL           (*(RwReg8 *)0x42004402UL) /**< \brief (ADC0) Reference Control */
#define REG_ADC0_EVCTRL            (*(RwReg8 *)0x42004403UL) /**< \brief (ADC0) Event Control */
#define REG_ADC0_INTENCLR          (*(RwReg8 *)0x42004404UL) /**< \brief (ADC0) Interrupt Enable Clear */
#define REG_ADC0_INTENSET          (*(RwReg8 *)0x42004405UL) /**< \brief (ADC0) Interrupt Enable Set */
#define REG_ADC0_INTFLAG           (*(RwReg8 *)0x42004406UL) /**< \brief (ADC0) Interrupt Flag Status and Clear */
#define REG_ADC0_SEQSTATUS         (*(RoReg8 *)0x42004407UL) /**< \brief (ADC0) Sequence Status */
#define REG_ADC0_INPUTCTRL         (*(RwReg16*)0x42004408UL) /**< \brief (ADC0) Input Control */
#define REG_ADC0_CTRLC             (*(RwReg16*)0x4200440AUL) /**< \brief (ADC0) Control C */
#define REG_ADC0_AVGCTRL           (*(RwReg8 *)0x4200440CUL) /**< \brief (ADC0) Average Control */
#define REG_ADC0_SAMPCTRL          (*(RwReg8 *)0x4200440DUL) /**< \brief (ADC0) Sample Time Control */
#define REG_ADC0_WINLT             (*(RwReg16*)0x4200440EUL) /**< \brief (ADC0) Window Monitor Lower Threshold */
#define REG_ADC0_WINUT             (*(RwReg16*)0x42004410UL) /**< \brief (ADC0) Window Monitor Upper Threshold */
#define REG_ADC0_GAINCORR          (*(RwReg16*)0x42004412UL) /**< \brief (ADC0) Gain Correction */
#define REG_ADC0_OFFSETCORR        (*(RwReg16*)0x42004414UL) /**< \brief (ADC0) Offset Correction */
#define REG_ADC0_SWTRIG            (*(RwReg8 *)0x42004418UL) /**< \brief (ADC0) Software Trigger */
#define REG_ADC0_DBGCTRL           (*(RwReg8 *)0x4200441CUL) /**< \brief (ADC0) Debug Control */
#define REG_ADC0_SYNCBUSY          (*(RoReg16*)0x42004420UL) /**< \brief (ADC0) Synchronization Busy */
#define REG_ADC0_RESULT            (*(RoReg16*)0x42004424UL) /**< \brief (ADC0) Result */
#define REG_ADC0_SEQCTRL           (*(RwReg  *)0x42004428UL) /**< \brief (ADC0) Sequence Control */
#define REG_ADC0_CALIB             (*(RwReg16*)0x4200442CUL) /**< \brief (ADC0) Calibration */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for ADC0 peripheral ========== */
#define ADC0_DMAC_ID_RESRDY         42       // index of DMA RESRDY trigger
#define ADC0_EXTCHANNEL_MSB         11       // Number of external channels
#define ADC0_GCLK_ID                33       // index of Generic Clock
#define ADC0_INT_CH30               0        // Select OPAMP or CTAT on Channel 30
#define ADC0_MASTER_SLAVE_MODE      1        // ADC Master/Slave Mode

#endif /* _SAMC21_ADC0_INSTANCE_ */
