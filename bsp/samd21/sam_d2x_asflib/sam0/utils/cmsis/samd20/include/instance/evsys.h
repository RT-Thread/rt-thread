/**
 * \file
 *
 * \brief Instance description for EVSYS
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
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

#ifndef _SAMD20_EVSYS_INSTANCE_
#define _SAMD20_EVSYS_INSTANCE_

/* ========== Register definition for EVSYS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_EVSYS_CTRL             (0x42000400U) /**< \brief (EVSYS) Control */
#define REG_EVSYS_CHANNEL          (0x42000404U) /**< \brief (EVSYS) Channel */
#define REG_EVSYS_USER             (0x42000408U) /**< \brief (EVSYS) User Multiplexer */
#define REG_EVSYS_CHSTATUS         (0x4200040CU) /**< \brief (EVSYS) Channel Status */
#define REG_EVSYS_INTENCLR         (0x42000410U) /**< \brief (EVSYS) Interrupt Enable Clear */
#define REG_EVSYS_INTENSET         (0x42000414U) /**< \brief (EVSYS) Interrupt Enable Set */
#define REG_EVSYS_INTFLAG          (0x42000418U) /**< \brief (EVSYS) Interrupt Flag Status and Clear */
#else
#define REG_EVSYS_CTRL             (*(WoReg8 *)0x42000400U) /**< \brief (EVSYS) Control */
#define REG_EVSYS_CHANNEL          (*(RwReg  *)0x42000404U) /**< \brief (EVSYS) Channel */
#define REG_EVSYS_USER             (*(RwReg16*)0x42000408U) /**< \brief (EVSYS) User Multiplexer */
#define REG_EVSYS_CHSTATUS         (*(RoReg  *)0x4200040CU) /**< \brief (EVSYS) Channel Status */
#define REG_EVSYS_INTENCLR         (*(RwReg  *)0x42000410U) /**< \brief (EVSYS) Interrupt Enable Clear */
#define REG_EVSYS_INTENSET         (*(RwReg  *)0x42000414U) /**< \brief (EVSYS) Interrupt Enable Set */
#define REG_EVSYS_INTFLAG          (*(RwReg  *)0x42000418U) /**< \brief (EVSYS) Interrupt Flag Status and Clear */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for EVSYS peripheral ========== */
#define EVSYS_CHANNELS              8        // Number of Channels
#define EVSYS_CHANNELS_BITS         3        // Number of bits to select Channel
#define EVSYS_CHANNELS_MSB          7        // Number of Channels - 1
#define EVSYS_EXTEVT_NUM                     // Number of External Event Generators
#define EVSYS_EXT_EVT_MSB           0        // Number of External Event Generators - 1
#define EVSYS_GCLK_ID_0             4
#define EVSYS_GCLK_ID_1             5
#define EVSYS_GCLK_ID_2             6
#define EVSYS_GCLK_ID_3             7
#define EVSYS_GCLK_ID_4             8
#define EVSYS_GCLK_ID_5             9
#define EVSYS_GCLK_ID_6             10
#define EVSYS_GCLK_ID_7             11
#define EVSYS_GCLK_ID_LSB           4
#define EVSYS_GCLK_ID_MSB           11
#define EVSYS_GCLK_ID_SIZE          8
#define EVSYS_GENERATORS            59       // Total Number of Event Generators
#define EVSYS_GENERATORS_BITS       6        // Number of bits to select Event Generator
#define EVSYS_USERS                 14       // Total Number of Event Users
#define EVSYS_USERS_BITS            4        // Number of bits to select Event User

// GENERATORS
#define EVSYS_ID_GEN_RTC_CMP_0      1
#define EVSYS_ID_GEN_RTC_CMP_1      2
#define EVSYS_ID_GEN_RTC_OVF        3
#define EVSYS_ID_GEN_RTC_PER_0      4
#define EVSYS_ID_GEN_RTC_PER_1      5
#define EVSYS_ID_GEN_RTC_PER_2      6
#define EVSYS_ID_GEN_RTC_PER_3      7
#define EVSYS_ID_GEN_RTC_PER_4      8
#define EVSYS_ID_GEN_RTC_PER_5      9
#define EVSYS_ID_GEN_RTC_PER_6      10
#define EVSYS_ID_GEN_RTC_PER_7      11
#define EVSYS_ID_GEN_EIC_EXTINT_0   12
#define EVSYS_ID_GEN_EIC_EXTINT_1   13
#define EVSYS_ID_GEN_EIC_EXTINT_2   14
#define EVSYS_ID_GEN_EIC_EXTINT_3   15
#define EVSYS_ID_GEN_EIC_EXTINT_4   16
#define EVSYS_ID_GEN_EIC_EXTINT_5   17
#define EVSYS_ID_GEN_EIC_EXTINT_6   18
#define EVSYS_ID_GEN_EIC_EXTINT_7   19
#define EVSYS_ID_GEN_EIC_EXTINT_8   20
#define EVSYS_ID_GEN_EIC_EXTINT_9   21
#define EVSYS_ID_GEN_EIC_EXTINT_10  22
#define EVSYS_ID_GEN_EIC_EXTINT_11  23
#define EVSYS_ID_GEN_EIC_EXTINT_12  24
#define EVSYS_ID_GEN_EIC_EXTINT_13  25
#define EVSYS_ID_GEN_EIC_EXTINT_14  26
#define EVSYS_ID_GEN_EIC_EXTINT_15  27
#define EVSYS_ID_GEN_TC0_OVF        28
#define EVSYS_ID_GEN_TC0_MCX_0      29
#define EVSYS_ID_GEN_TC0_MCX_1      30
#define EVSYS_ID_GEN_TC1_OVF        31
#define EVSYS_ID_GEN_TC1_MCX_0      32
#define EVSYS_ID_GEN_TC1_MCX_1      33
#define EVSYS_ID_GEN_TC2_OVF        34
#define EVSYS_ID_GEN_TC2_MCX_0      35
#define EVSYS_ID_GEN_TC2_MCX_1      36
#define EVSYS_ID_GEN_TC3_OVF        37
#define EVSYS_ID_GEN_TC3_MCX_0      38
#define EVSYS_ID_GEN_TC3_MCX_1      39
#define EVSYS_ID_GEN_TC4_OVF        40
#define EVSYS_ID_GEN_TC4_MCX_0      41
#define EVSYS_ID_GEN_TC4_MCX_1      42
#define EVSYS_ID_GEN_TC5_OVF        43
#define EVSYS_ID_GEN_TC5_MCX_0      44
#define EVSYS_ID_GEN_TC5_MCX_1      45
#define EVSYS_ID_GEN_TC6_OVF        46
#define EVSYS_ID_GEN_TC6_MCX_0      47
#define EVSYS_ID_GEN_TC6_MCX_1      48
#define EVSYS_ID_GEN_TC7_OVF        49
#define EVSYS_ID_GEN_TC7_MCX_0      50
#define EVSYS_ID_GEN_TC7_MCX_1      51
#define EVSYS_ID_GEN_ADC_RESRDY     52
#define EVSYS_ID_GEN_ADC_WINMON     53
#define EVSYS_ID_GEN_AC_COMP_0      54
#define EVSYS_ID_GEN_AC_COMP_1      55
#define EVSYS_ID_GEN_AC_WIN_0       56
#define EVSYS_ID_GEN_DAC_EMPTY      57
#define EVSYS_ID_GEN_PTC_EOC        58
#define EVSYS_ID_GEN_PTC_WCOMP      59

// USERS
#define EVSYS_ID_USER_TC0_EVU       0
#define EVSYS_ID_USER_TC1_EVU       1
#define EVSYS_ID_USER_TC2_EVU       2
#define EVSYS_ID_USER_TC3_EVU       3
#define EVSYS_ID_USER_TC4_EVU       4
#define EVSYS_ID_USER_TC5_EVU       5
#define EVSYS_ID_USER_TC6_EVU       6
#define EVSYS_ID_USER_TC7_EVU       7
#define EVSYS_ID_USER_ADC_START     8
#define EVSYS_ID_USER_ADC_SYNC      9
#define EVSYS_ID_USER_AC_SOC_0      10
#define EVSYS_ID_USER_AC_SOC_1      11
#define EVSYS_ID_USER_DAC_START     12
#define EVSYS_ID_USER_PTC_STCONV    13

#endif /* _SAMD20_EVSYS_INSTANCE_ */
