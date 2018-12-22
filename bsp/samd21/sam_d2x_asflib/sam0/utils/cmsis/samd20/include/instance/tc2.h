/**
 * \file
 *
 * \brief Instance description for TC2
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

#ifndef _SAMD20_TC2_INSTANCE_
#define _SAMD20_TC2_INSTANCE_

/* ========== Register definition for TC2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC2_CTRLA              (0x42002800U) /**< \brief (TC2) Control A */
#define REG_TC2_READREQ            (0x42002802U) /**< \brief (TC2) Read Request */
#define REG_TC2_CTRLBCLR           (0x42002804U) /**< \brief (TC2) Control B Clear */
#define REG_TC2_CTRLBSET           (0x42002805U) /**< \brief (TC2) Control B Set */
#define REG_TC2_CTRLC              (0x42002806U) /**< \brief (TC2) Control C */
#define REG_TC2_DBGCTRL            (0x42002808U) /**< \brief (TC2) Debug Control */
#define REG_TC2_EVCTRL             (0x4200280AU) /**< \brief (TC2) Event Control */
#define REG_TC2_INTENCLR           (0x4200280CU) /**< \brief (TC2) Interrupt Enable Clear */
#define REG_TC2_INTENSET           (0x4200280DU) /**< \brief (TC2) Interrupt Enable Set */
#define REG_TC2_INTFLAG            (0x4200280EU) /**< \brief (TC2) Interrupt Flag Status and Clear */
#define REG_TC2_STATUS             (0x4200280FU) /**< \brief (TC2) Status */
#define REG_TC2_COUNT16_COUNT      (0x42002810U) /**< \brief (TC2) COUNT16 Counter Value */
#define REG_TC2_COUNT16_CC0        (0x42002818U) /**< \brief (TC2) COUNT16 Compare/Capture 0 */
#define REG_TC2_COUNT16_CC1        (0x4200281AU) /**< \brief (TC2) COUNT16 Compare/Capture 1 */
#define REG_TC2_COUNT32_COUNT      (0x42002810U) /**< \brief (TC2) COUNT32 Counter Value */
#define REG_TC2_COUNT32_CC0        (0x42002818U) /**< \brief (TC2) COUNT32 Compare/Capture 0 */
#define REG_TC2_COUNT32_CC1        (0x4200281CU) /**< \brief (TC2) COUNT32 Compare/Capture 1 */
#define REG_TC2_COUNT8_COUNT       (0x42002810U) /**< \brief (TC2) COUNT8 Counter Value */
#define REG_TC2_COUNT8_PER         (0x42002814U) /**< \brief (TC2) COUNT8 Period Value */
#define REG_TC2_COUNT8_CC0         (0x42002818U) /**< \brief (TC2) COUNT8 Compare/Capture 0 */
#define REG_TC2_COUNT8_CC1         (0x42002819U) /**< \brief (TC2) COUNT8 Compare/Capture 1 */
#else
#define REG_TC2_CTRLA              (*(RwReg16*)0x42002800U) /**< \brief (TC2) Control A */
#define REG_TC2_READREQ            (*(RwReg16*)0x42002802U) /**< \brief (TC2) Read Request */
#define REG_TC2_CTRLBCLR           (*(RwReg8 *)0x42002804U) /**< \brief (TC2) Control B Clear */
#define REG_TC2_CTRLBSET           (*(RwReg8 *)0x42002805U) /**< \brief (TC2) Control B Set */
#define REG_TC2_CTRLC              (*(RwReg8 *)0x42002806U) /**< \brief (TC2) Control C */
#define REG_TC2_DBGCTRL            (*(RwReg8 *)0x42002808U) /**< \brief (TC2) Debug Control */
#define REG_TC2_EVCTRL             (*(RwReg16*)0x4200280AU) /**< \brief (TC2) Event Control */
#define REG_TC2_INTENCLR           (*(RwReg8 *)0x4200280CU) /**< \brief (TC2) Interrupt Enable Clear */
#define REG_TC2_INTENSET           (*(RwReg8 *)0x4200280DU) /**< \brief (TC2) Interrupt Enable Set */
#define REG_TC2_INTFLAG            (*(RwReg8 *)0x4200280EU) /**< \brief (TC2) Interrupt Flag Status and Clear */
#define REG_TC2_STATUS             (*(RoReg8 *)0x4200280FU) /**< \brief (TC2) Status */
#define REG_TC2_COUNT16_COUNT      (*(RwReg16*)0x42002810U) /**< \brief (TC2) COUNT16 Counter Value */
#define REG_TC2_COUNT16_CC0        (*(RwReg16*)0x42002818U) /**< \brief (TC2) COUNT16 Compare/Capture 0 */
#define REG_TC2_COUNT16_CC1        (*(RwReg16*)0x4200281AU) /**< \brief (TC2) COUNT16 Compare/Capture 1 */
#define REG_TC2_COUNT32_COUNT      (*(RwReg  *)0x42002810U) /**< \brief (TC2) COUNT32 Counter Value */
#define REG_TC2_COUNT32_CC0        (*(RwReg  *)0x42002818U) /**< \brief (TC2) COUNT32 Compare/Capture 0 */
#define REG_TC2_COUNT32_CC1        (*(RwReg  *)0x4200281CU) /**< \brief (TC2) COUNT32 Compare/Capture 1 */
#define REG_TC2_COUNT8_COUNT       (*(RwReg8 *)0x42002810U) /**< \brief (TC2) COUNT8 Counter Value */
#define REG_TC2_COUNT8_PER         (*(RwReg8 *)0x42002814U) /**< \brief (TC2) COUNT8 Period Value */
#define REG_TC2_COUNT8_CC0         (*(RwReg8 *)0x42002818U) /**< \brief (TC2) COUNT8 Compare/Capture 0 */
#define REG_TC2_COUNT8_CC1         (*(RwReg8 *)0x42002819U) /**< \brief (TC2) COUNT8 Compare/Capture 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC2 peripheral ========== */
#define TC2_CC8_NUM                 2
#define TC2_CC16_NUM                2
#define TC2_CC32_NUM                2
#define TC2_DITHERING_EXT           0
#define TC2_GCLK_ID                 20
#define TC2_MASTER                  1
#define TC2_OW_NUM                  2
#define TC2_PERIOD_EXT              0
#define TC2_SHADOW_EXT              0

#endif /* _SAMD20_TC2_INSTANCE_ */
