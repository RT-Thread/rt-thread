/**
 * \file
 *
 * \brief Instance description for TC3
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

#ifndef _SAMC21_TC3_INSTANCE_
#define _SAMC21_TC3_INSTANCE_

/* ========== Register definition for TC3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC3_CTRLA              (0x42003C00) /**< \brief (TC3) Control A */
#define REG_TC3_CTRLBCLR           (0x42003C04) /**< \brief (TC3) Control B Clear */
#define REG_TC3_CTRLBSET           (0x42003C05) /**< \brief (TC3) Control B Set */
#define REG_TC3_EVCTRL             (0x42003C06) /**< \brief (TC3) Event Control */
#define REG_TC3_INTENCLR           (0x42003C08) /**< \brief (TC3) Interrupt Enable Clear */
#define REG_TC3_INTENSET           (0x42003C09) /**< \brief (TC3) Interrupt Enable Set */
#define REG_TC3_INTFLAG            (0x42003C0A) /**< \brief (TC3) Interrupt Flag Status and Clear */
#define REG_TC3_STATUS             (0x42003C0B) /**< \brief (TC3) Status */
#define REG_TC3_WAVE               (0x42003C0C) /**< \brief (TC3) Waveform Generation Control */
#define REG_TC3_DRVCTRL            (0x42003C0D) /**< \brief (TC3) Control C */
#define REG_TC3_DBGCTRL            (0x42003C0F) /**< \brief (TC3) Debug Control */
#define REG_TC3_SYNCBUSY           (0x42003C10) /**< \brief (TC3) Synchronization Status */
#define REG_TC3_COUNT16_COUNT      (0x42003C14) /**< \brief (TC3) COUNT16 Count */
#define REG_TC3_COUNT16_CC0        (0x42003C1C) /**< \brief (TC3) COUNT16 Compare and Capture 0 */
#define REG_TC3_COUNT16_CC1        (0x42003C1E) /**< \brief (TC3) COUNT16 Compare and Capture 1 */
#define REG_TC3_COUNT16_CCBUF0     (0x42003C30) /**< \brief (TC3) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC3_COUNT16_CCBUF1     (0x42003C32) /**< \brief (TC3) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC3_COUNT32_COUNT      (0x42003C14) /**< \brief (TC3) COUNT32 Count */
#define REG_TC3_COUNT32_CC0        (0x42003C1C) /**< \brief (TC3) COUNT32 Compare and Capture 0 */
#define REG_TC3_COUNT32_CC1        (0x42003C20) /**< \brief (TC3) COUNT32 Compare and Capture 1 */
#define REG_TC3_COUNT32_CCBUF0     (0x42003C30) /**< \brief (TC3) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC3_COUNT32_CCBUF1     (0x42003C34) /**< \brief (TC3) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC3_COUNT8_COUNT       (0x42003C14) /**< \brief (TC3) COUNT8 Count */
#define REG_TC3_COUNT8_PER         (0x42003C1B) /**< \brief (TC3) COUNT8 Period */
#define REG_TC3_COUNT8_CC0         (0x42003C1C) /**< \brief (TC3) COUNT8 Compare and Capture 0 */
#define REG_TC3_COUNT8_CC1         (0x42003C1D) /**< \brief (TC3) COUNT8 Compare and Capture 1 */
#define REG_TC3_COUNT8_PERBUF      (0x42003C2F) /**< \brief (TC3) COUNT8 Period Buffer */
#define REG_TC3_COUNT8_CCBUF0      (0x42003C30) /**< \brief (TC3) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC3_COUNT8_CCBUF1      (0x42003C31) /**< \brief (TC3) COUNT8 Compare and Capture Buffer 1 */
#else
#define REG_TC3_CTRLA              (*(RwReg  *)0x42003C00UL) /**< \brief (TC3) Control A */
#define REG_TC3_CTRLBCLR           (*(RwReg8 *)0x42003C04UL) /**< \brief (TC3) Control B Clear */
#define REG_TC3_CTRLBSET           (*(RwReg8 *)0x42003C05UL) /**< \brief (TC3) Control B Set */
#define REG_TC3_EVCTRL             (*(RwReg16*)0x42003C06UL) /**< \brief (TC3) Event Control */
#define REG_TC3_INTENCLR           (*(RwReg8 *)0x42003C08UL) /**< \brief (TC3) Interrupt Enable Clear */
#define REG_TC3_INTENSET           (*(RwReg8 *)0x42003C09UL) /**< \brief (TC3) Interrupt Enable Set */
#define REG_TC3_INTFLAG            (*(RwReg8 *)0x42003C0AUL) /**< \brief (TC3) Interrupt Flag Status and Clear */
#define REG_TC3_STATUS             (*(RwReg8 *)0x42003C0BUL) /**< \brief (TC3) Status */
#define REG_TC3_WAVE               (*(RwReg8 *)0x42003C0CUL) /**< \brief (TC3) Waveform Generation Control */
#define REG_TC3_DRVCTRL            (*(RwReg8 *)0x42003C0DUL) /**< \brief (TC3) Control C */
#define REG_TC3_DBGCTRL            (*(RwReg8 *)0x42003C0FUL) /**< \brief (TC3) Debug Control */
#define REG_TC3_SYNCBUSY           (*(RoReg  *)0x42003C10UL) /**< \brief (TC3) Synchronization Status */
#define REG_TC3_COUNT16_COUNT      (*(RwReg16*)0x42003C14UL) /**< \brief (TC3) COUNT16 Count */
#define REG_TC3_COUNT16_CC0        (*(RwReg16*)0x42003C1CUL) /**< \brief (TC3) COUNT16 Compare and Capture 0 */
#define REG_TC3_COUNT16_CC1        (*(RwReg16*)0x42003C1EUL) /**< \brief (TC3) COUNT16 Compare and Capture 1 */
#define REG_TC3_COUNT16_CCBUF0     (*(RwReg16*)0x42003C30UL) /**< \brief (TC3) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC3_COUNT16_CCBUF1     (*(RwReg16*)0x42003C32UL) /**< \brief (TC3) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC3_COUNT32_COUNT      (*(RwReg  *)0x42003C14UL) /**< \brief (TC3) COUNT32 Count */
#define REG_TC3_COUNT32_CC0        (*(RwReg  *)0x42003C1CUL) /**< \brief (TC3) COUNT32 Compare and Capture 0 */
#define REG_TC3_COUNT32_CC1        (*(RwReg  *)0x42003C20UL) /**< \brief (TC3) COUNT32 Compare and Capture 1 */
#define REG_TC3_COUNT32_CCBUF0     (*(RwReg  *)0x42003C30UL) /**< \brief (TC3) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC3_COUNT32_CCBUF1     (*(RwReg  *)0x42003C34UL) /**< \brief (TC3) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC3_COUNT8_COUNT       (*(RwReg8 *)0x42003C14UL) /**< \brief (TC3) COUNT8 Count */
#define REG_TC3_COUNT8_PER         (*(RwReg8 *)0x42003C1BUL) /**< \brief (TC3) COUNT8 Period */
#define REG_TC3_COUNT8_CC0         (*(RwReg8 *)0x42003C1CUL) /**< \brief (TC3) COUNT8 Compare and Capture 0 */
#define REG_TC3_COUNT8_CC1         (*(RwReg8 *)0x42003C1DUL) /**< \brief (TC3) COUNT8 Compare and Capture 1 */
#define REG_TC3_COUNT8_PERBUF      (*(RwReg8 *)0x42003C2FUL) /**< \brief (TC3) COUNT8 Period Buffer */
#define REG_TC3_COUNT8_CCBUF0      (*(RwReg8 *)0x42003C30UL) /**< \brief (TC3) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC3_COUNT8_CCBUF1      (*(RwReg8 *)0x42003C31UL) /**< \brief (TC3) COUNT8 Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC3 peripheral ========== */
#define TC3_CC_NUM                  2       
#define TC3_DMAC_ID_MC_0            37
#define TC3_DMAC_ID_MC_1            38
#define TC3_DMAC_ID_MC_LSB          37
#define TC3_DMAC_ID_MC_MSB          38
#define TC3_DMAC_ID_MC_SIZE         2
#define TC3_DMAC_ID_OVF             36       // Indexes of DMA Overflow trigger
#define TC3_EXT                     0       
#define TC3_GCLK_ID                 31      
#define TC3_MASTER                  0       
#define TC3_OW_NUM                  2       

#endif /* _SAMC21_TC3_INSTANCE_ */
