/**
 * \file
 *
 * \brief Instance description for TC0
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _SAMD20_TC0_INSTANCE_
#define _SAMD20_TC0_INSTANCE_

/* ========== Register definition for TC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC0_CTRLA              (0x42002000U) /**< \brief (TC0) Control A */
#define REG_TC0_READREQ            (0x42002002U) /**< \brief (TC0) Read Request */
#define REG_TC0_CTRLBCLR           (0x42002004U) /**< \brief (TC0) Control B Clear */
#define REG_TC0_CTRLBSET           (0x42002005U) /**< \brief (TC0) Control B Set */
#define REG_TC0_CTRLC              (0x42002006U) /**< \brief (TC0) Control C */
#define REG_TC0_DBGCTRL            (0x42002008U) /**< \brief (TC0) Debug Control */
#define REG_TC0_EVCTRL             (0x4200200AU) /**< \brief (TC0) Event Control */
#define REG_TC0_INTENCLR           (0x4200200CU) /**< \brief (TC0) Interrupt Enable Clear */
#define REG_TC0_INTENSET           (0x4200200DU) /**< \brief (TC0) Interrupt Enable Set */
#define REG_TC0_INTFLAG            (0x4200200EU) /**< \brief (TC0) Interrupt Flag Status and Clear */
#define REG_TC0_STATUS             (0x4200200FU) /**< \brief (TC0) Status */
#define REG_TC0_COUNT16_COUNT      (0x42002010U) /**< \brief (TC0) COUNT16 Counter Value */
#define REG_TC0_COUNT16_CC0        (0x42002018U) /**< \brief (TC0) COUNT16 Compare/Capture 0 */
#define REG_TC0_COUNT16_CC1        (0x4200201AU) /**< \brief (TC0) COUNT16 Compare/Capture 1 */
#define REG_TC0_COUNT32_COUNT      (0x42002010U) /**< \brief (TC0) COUNT32 Counter Value */
#define REG_TC0_COUNT32_CC0        (0x42002018U) /**< \brief (TC0) COUNT32 Compare/Capture 0 */
#define REG_TC0_COUNT32_CC1        (0x4200201CU) /**< \brief (TC0) COUNT32 Compare/Capture 1 */
#define REG_TC0_COUNT8_COUNT       (0x42002010U) /**< \brief (TC0) COUNT8 Counter Value */
#define REG_TC0_COUNT8_PER         (0x42002014U) /**< \brief (TC0) COUNT8 Period Value */
#define REG_TC0_COUNT8_CC0         (0x42002018U) /**< \brief (TC0) COUNT8 Compare/Capture 0 */
#define REG_TC0_COUNT8_CC1         (0x42002019U) /**< \brief (TC0) COUNT8 Compare/Capture 1 */
#else
#define REG_TC0_CTRLA              (*(RwReg16*)0x42002000U) /**< \brief (TC0) Control A */
#define REG_TC0_READREQ            (*(RwReg16*)0x42002002U) /**< \brief (TC0) Read Request */
#define REG_TC0_CTRLBCLR           (*(RwReg8 *)0x42002004U) /**< \brief (TC0) Control B Clear */
#define REG_TC0_CTRLBSET           (*(RwReg8 *)0x42002005U) /**< \brief (TC0) Control B Set */
#define REG_TC0_CTRLC              (*(RwReg8 *)0x42002006U) /**< \brief (TC0) Control C */
#define REG_TC0_DBGCTRL            (*(RwReg8 *)0x42002008U) /**< \brief (TC0) Debug Control */
#define REG_TC0_EVCTRL             (*(RwReg16*)0x4200200AU) /**< \brief (TC0) Event Control */
#define REG_TC0_INTENCLR           (*(RwReg8 *)0x4200200CU) /**< \brief (TC0) Interrupt Enable Clear */
#define REG_TC0_INTENSET           (*(RwReg8 *)0x4200200DU) /**< \brief (TC0) Interrupt Enable Set */
#define REG_TC0_INTFLAG            (*(RwReg8 *)0x4200200EU) /**< \brief (TC0) Interrupt Flag Status and Clear */
#define REG_TC0_STATUS             (*(RoReg8 *)0x4200200FU) /**< \brief (TC0) Status */
#define REG_TC0_COUNT16_COUNT      (*(RwReg16*)0x42002010U) /**< \brief (TC0) COUNT16 Counter Value */
#define REG_TC0_COUNT16_CC0        (*(RwReg16*)0x42002018U) /**< \brief (TC0) COUNT16 Compare/Capture 0 */
#define REG_TC0_COUNT16_CC1        (*(RwReg16*)0x4200201AU) /**< \brief (TC0) COUNT16 Compare/Capture 1 */
#define REG_TC0_COUNT32_COUNT      (*(RwReg  *)0x42002010U) /**< \brief (TC0) COUNT32 Counter Value */
#define REG_TC0_COUNT32_CC0        (*(RwReg  *)0x42002018U) /**< \brief (TC0) COUNT32 Compare/Capture 0 */
#define REG_TC0_COUNT32_CC1        (*(RwReg  *)0x4200201CU) /**< \brief (TC0) COUNT32 Compare/Capture 1 */
#define REG_TC0_COUNT8_COUNT       (*(RwReg8 *)0x42002010U) /**< \brief (TC0) COUNT8 Counter Value */
#define REG_TC0_COUNT8_PER         (*(RwReg8 *)0x42002014U) /**< \brief (TC0) COUNT8 Period Value */
#define REG_TC0_COUNT8_CC0         (*(RwReg8 *)0x42002018U) /**< \brief (TC0) COUNT8 Compare/Capture 0 */
#define REG_TC0_COUNT8_CC1         (*(RwReg8 *)0x42002019U) /**< \brief (TC0) COUNT8 Compare/Capture 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC0 peripheral ========== */
#define TC0_CC8_NUM                 2
#define TC0_CC16_NUM                2
#define TC0_CC32_NUM                2
#define TC0_DITHERING_EXT           0
#define TC0_GCLK_ID                 19
#define TC0_MASTER                  1
#define TC0_OW_NUM                  2
#define TC0_PERIOD_EXT              0
#define TC0_SHADOW_EXT              0

#endif /* _SAMD20_TC0_INSTANCE_ */
