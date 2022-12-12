/**
 * \file
 *
 * \brief Instance description for DAC
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

#ifndef _SAMC21_DAC_INSTANCE_
#define _SAMC21_DAC_INSTANCE_

/* ========== Register definition for DAC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_DAC_CTRLA              (0x42005400) /**< \brief (DAC) Control A */
#define REG_DAC_CTRLB              (0x42005401) /**< \brief (DAC) Control B */
#define REG_DAC_EVCTRL             (0x42005402) /**< \brief (DAC) Event Control */
#define REG_DAC_INTENCLR           (0x42005404) /**< \brief (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET           (0x42005405) /**< \brief (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG            (0x42005406) /**< \brief (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS             (0x42005407) /**< \brief (DAC) Status */
#define REG_DAC_DATA               (0x42005408) /**< \brief (DAC) Data */
#define REG_DAC_DATABUF            (0x4200540C) /**< \brief (DAC) Data Buffer */
#define REG_DAC_SYNCBUSY           (0x42005410) /**< \brief (DAC) Synchronization Busy */
#define REG_DAC_DBGCTRL            (0x42005414) /**< \brief (DAC) Debug Control */
#else
#define REG_DAC_CTRLA              (*(RwReg8 *)0x42005400UL) /**< \brief (DAC) Control A */
#define REG_DAC_CTRLB              (*(RwReg8 *)0x42005401UL) /**< \brief (DAC) Control B */
#define REG_DAC_EVCTRL             (*(RwReg8 *)0x42005402UL) /**< \brief (DAC) Event Control */
#define REG_DAC_INTENCLR           (*(RwReg8 *)0x42005404UL) /**< \brief (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET           (*(RwReg8 *)0x42005405UL) /**< \brief (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG            (*(RwReg8 *)0x42005406UL) /**< \brief (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS             (*(RoReg8 *)0x42005407UL) /**< \brief (DAC) Status */
#define REG_DAC_DATA               (*(WoReg16*)0x42005408UL) /**< \brief (DAC) Data */
#define REG_DAC_DATABUF            (*(WoReg16*)0x4200540CUL) /**< \brief (DAC) Data Buffer */
#define REG_DAC_SYNCBUSY           (*(RoReg  *)0x42005410UL) /**< \brief (DAC) Synchronization Busy */
#define REG_DAC_DBGCTRL            (*(RwReg8 *)0x42005414UL) /**< \brief (DAC) Debug Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for DAC peripheral ========== */
#define DAC_DMAC_ID_EMPTY           45       // Index of DMA EMPTY trigger
#define DAC_GCLK_ID                 36      

#endif /* _SAMC21_DAC_INSTANCE_ */
