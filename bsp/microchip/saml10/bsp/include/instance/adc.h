/**
 * \file
 *
 * \brief Instance description for ADC
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
#ifndef _SAML10_ADC_INSTANCE_H_
#define _SAML10_ADC_INSTANCE_H_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_ADC_CTRLA           (0x42001C00) /**< (ADC) Control A */
#define REG_ADC_CTRLB           (0x42001C01) /**< (ADC) Control B */
#define REG_ADC_REFCTRL         (0x42001C02) /**< (ADC) Reference Control */
#define REG_ADC_EVCTRL          (0x42001C03) /**< (ADC) Event Control */
#define REG_ADC_INTENCLR        (0x42001C04) /**< (ADC) Interrupt Enable Clear */
#define REG_ADC_INTENSET        (0x42001C05) /**< (ADC) Interrupt Enable Set */
#define REG_ADC_INTFLAG         (0x42001C06) /**< (ADC) Interrupt Flag Status and Clear */
#define REG_ADC_SEQSTATUS       (0x42001C07) /**< (ADC) Sequence Status */
#define REG_ADC_INPUTCTRL       (0x42001C08) /**< (ADC) Input Control */
#define REG_ADC_CTRLC           (0x42001C0A) /**< (ADC) Control C */
#define REG_ADC_AVGCTRL         (0x42001C0C) /**< (ADC) Average Control */
#define REG_ADC_SAMPCTRL        (0x42001C0D) /**< (ADC) Sample Time Control */
#define REG_ADC_WINLT           (0x42001C0E) /**< (ADC) Window Monitor Lower Threshold */
#define REG_ADC_WINUT           (0x42001C10) /**< (ADC) Window Monitor Upper Threshold */
#define REG_ADC_GAINCORR        (0x42001C12) /**< (ADC) Gain Correction */
#define REG_ADC_OFFSETCORR      (0x42001C14) /**< (ADC) Offset Correction */
#define REG_ADC_SWTRIG          (0x42001C18) /**< (ADC) Software Trigger */
#define REG_ADC_DBGCTRL         (0x42001C1C) /**< (ADC) Debug Control */
#define REG_ADC_SYNCBUSY        (0x42001C20) /**< (ADC) Synchronization Busy */
#define REG_ADC_RESULT          (0x42001C24) /**< (ADC) Result */
#define REG_ADC_SEQCTRL         (0x42001C28) /**< (ADC) Sequence Control */
#define REG_ADC_CALIB           (0x42001C2C) /**< (ADC) Calibration */

#else

#define REG_ADC_CTRLA           (*(__IO uint8_t*)0x42001C00U) /**< (ADC) Control A */
#define REG_ADC_CTRLB           (*(__IO uint8_t*)0x42001C01U) /**< (ADC) Control B */
#define REG_ADC_REFCTRL         (*(__IO uint8_t*)0x42001C02U) /**< (ADC) Reference Control */
#define REG_ADC_EVCTRL          (*(__IO uint8_t*)0x42001C03U) /**< (ADC) Event Control */
#define REG_ADC_INTENCLR        (*(__IO uint8_t*)0x42001C04U) /**< (ADC) Interrupt Enable Clear */
#define REG_ADC_INTENSET        (*(__IO uint8_t*)0x42001C05U) /**< (ADC) Interrupt Enable Set */
#define REG_ADC_INTFLAG         (*(__IO uint8_t*)0x42001C06U) /**< (ADC) Interrupt Flag Status and Clear */
#define REG_ADC_SEQSTATUS       (*(__I  uint8_t*)0x42001C07U) /**< (ADC) Sequence Status */
#define REG_ADC_INPUTCTRL       (*(__IO uint16_t*)0x42001C08U) /**< (ADC) Input Control */
#define REG_ADC_CTRLC           (*(__IO uint16_t*)0x42001C0AU) /**< (ADC) Control C */
#define REG_ADC_AVGCTRL         (*(__IO uint8_t*)0x42001C0CU) /**< (ADC) Average Control */
#define REG_ADC_SAMPCTRL        (*(__IO uint8_t*)0x42001C0DU) /**< (ADC) Sample Time Control */
#define REG_ADC_WINLT           (*(__IO uint16_t*)0x42001C0EU) /**< (ADC) Window Monitor Lower Threshold */
#define REG_ADC_WINUT           (*(__IO uint16_t*)0x42001C10U) /**< (ADC) Window Monitor Upper Threshold */
#define REG_ADC_GAINCORR        (*(__IO uint16_t*)0x42001C12U) /**< (ADC) Gain Correction */
#define REG_ADC_OFFSETCORR      (*(__IO uint16_t*)0x42001C14U) /**< (ADC) Offset Correction */
#define REG_ADC_SWTRIG          (*(__IO uint8_t*)0x42001C18U) /**< (ADC) Software Trigger */
#define REG_ADC_DBGCTRL         (*(__IO uint8_t*)0x42001C1CU) /**< (ADC) Debug Control */
#define REG_ADC_SYNCBUSY        (*(__I  uint16_t*)0x42001C20U) /**< (ADC) Synchronization Busy */
#define REG_ADC_RESULT          (*(__I  uint16_t*)0x42001C24U) /**< (ADC) Result */
#define REG_ADC_SEQCTRL         (*(__IO uint32_t*)0x42001C28U) /**< (ADC) Sequence Control */
#define REG_ADC_CALIB           (*(__IO uint16_t*)0x42001C2CU) /**< (ADC) Calibration */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for ADC peripheral ========== */
#define ADC_DMAC_ID_RESRDY                       19         /* index of DMA RESRDY trigger */
#define ADC_EXTCHANNEL_MSB                       9          /* Number of external channels */
#define ADC_GCLK_ID                              16         /* index of Generic Clock */
#define ADC_INT_CH30                             1          /* Select OPAMP or CTAT on Channel 30 */
#define ADC_MASTER_SLAVE_MODE                    0          /* ADC Master/Slave Mode */
#define ADC_INSTANCE_ID                          71         

#endif /* _SAML10_ADC_INSTANCE_ */
