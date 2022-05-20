/**
 * \file
 *
 * \brief Instance description for RTC
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

#ifndef _SAMC21_RTC_INSTANCE_
#define _SAMC21_RTC_INSTANCE_

/* ========== Register definition for RTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_RTC_DBGCTRL            (0x4000240E) /**< \brief (RTC) Debug Control */
#define REG_RTC_FREQCORR           (0x40002414) /**< \brief (RTC) Frequency Correction */
#define REG_RTC_MODE0_CTRLA        (0x40002400) /**< \brief (RTC) MODE0 Control A */
#define REG_RTC_MODE0_EVCTRL       (0x40002404) /**< \brief (RTC) MODE0 Event Control */
#define REG_RTC_MODE0_INTENCLR     (0x40002408) /**< \brief (RTC) MODE0 Interrupt Enable Clear */
#define REG_RTC_MODE0_INTENSET     (0x4000240A) /**< \brief (RTC) MODE0 Interrupt Enable Set */
#define REG_RTC_MODE0_INTFLAG      (0x4000240C) /**< \brief (RTC) MODE0 Interrupt Flag Status and Clear */
#define REG_RTC_MODE0_SYNCBUSY     (0x40002410) /**< \brief (RTC) MODE0 Synchronization Busy Status */
#define REG_RTC_MODE0_COUNT        (0x40002418) /**< \brief (RTC) MODE0 Counter Value */
#define REG_RTC_MODE0_COMP0        (0x40002420) /**< \brief (RTC) MODE0 Compare 0 Value */
#define REG_RTC_MODE1_CTRLA        (0x40002400) /**< \brief (RTC) MODE1 Control A */
#define REG_RTC_MODE1_EVCTRL       (0x40002404) /**< \brief (RTC) MODE1 Event Control */
#define REG_RTC_MODE1_INTENCLR     (0x40002408) /**< \brief (RTC) MODE1 Interrupt Enable Clear */
#define REG_RTC_MODE1_INTENSET     (0x4000240A) /**< \brief (RTC) MODE1 Interrupt Enable Set */
#define REG_RTC_MODE1_INTFLAG      (0x4000240C) /**< \brief (RTC) MODE1 Interrupt Flag Status and Clear */
#define REG_RTC_MODE1_SYNCBUSY     (0x40002410) /**< \brief (RTC) MODE1 Synchronization Busy Status */
#define REG_RTC_MODE1_COUNT        (0x40002418) /**< \brief (RTC) MODE1 Counter Value */
#define REG_RTC_MODE1_PER          (0x4000241C) /**< \brief (RTC) MODE1 Counter Period */
#define REG_RTC_MODE1_COMP0        (0x40002420) /**< \brief (RTC) MODE1 Compare 0 Value */
#define REG_RTC_MODE1_COMP1        (0x40002422) /**< \brief (RTC) MODE1 Compare 1 Value */
#define REG_RTC_MODE2_CTRLA        (0x40002400) /**< \brief (RTC) MODE2 Control A */
#define REG_RTC_MODE2_EVCTRL       (0x40002404) /**< \brief (RTC) MODE2 Event Control */
#define REG_RTC_MODE2_INTENCLR     (0x40002408) /**< \brief (RTC) MODE2 Interrupt Enable Clear */
#define REG_RTC_MODE2_INTENSET     (0x4000240A) /**< \brief (RTC) MODE2 Interrupt Enable Set */
#define REG_RTC_MODE2_INTFLAG      (0x4000240C) /**< \brief (RTC) MODE2 Interrupt Flag Status and Clear */
#define REG_RTC_MODE2_SYNCBUSY     (0x40002410) /**< \brief (RTC) MODE2 Synchronization Busy Status */
#define REG_RTC_MODE2_CLOCK        (0x40002418) /**< \brief (RTC) MODE2 Clock Value */
#define REG_RTC_MODE2_ALARM_ALARM0 (0x40002420) /**< \brief (RTC) MODE2_ALARM Alarm 0 Value */
#define REG_RTC_MODE2_ALARM_MASK0  (0x40002424) /**< \brief (RTC) MODE2_ALARM Alarm 0 Mask */
#else
#define REG_RTC_DBGCTRL            (*(RwReg8 *)0x4000240EUL) /**< \brief (RTC) Debug Control */
#define REG_RTC_FREQCORR           (*(RwReg8 *)0x40002414UL) /**< \brief (RTC) Frequency Correction */
#define REG_RTC_MODE0_CTRLA        (*(RwReg16*)0x40002400UL) /**< \brief (RTC) MODE0 Control A */
#define REG_RTC_MODE0_EVCTRL       (*(RwReg  *)0x40002404UL) /**< \brief (RTC) MODE0 Event Control */
#define REG_RTC_MODE0_INTENCLR     (*(RwReg16*)0x40002408UL) /**< \brief (RTC) MODE0 Interrupt Enable Clear */
#define REG_RTC_MODE0_INTENSET     (*(RwReg16*)0x4000240AUL) /**< \brief (RTC) MODE0 Interrupt Enable Set */
#define REG_RTC_MODE0_INTFLAG      (*(RwReg16*)0x4000240CUL) /**< \brief (RTC) MODE0 Interrupt Flag Status and Clear */
#define REG_RTC_MODE0_SYNCBUSY     (*(RoReg  *)0x40002410UL) /**< \brief (RTC) MODE0 Synchronization Busy Status */
#define REG_RTC_MODE0_COUNT        (*(RwReg  *)0x40002418UL) /**< \brief (RTC) MODE0 Counter Value */
#define REG_RTC_MODE0_COMP0        (*(RwReg  *)0x40002420UL) /**< \brief (RTC) MODE0 Compare 0 Value */
#define REG_RTC_MODE1_CTRLA        (*(RwReg16*)0x40002400UL) /**< \brief (RTC) MODE1 Control A */
#define REG_RTC_MODE1_EVCTRL       (*(RwReg  *)0x40002404UL) /**< \brief (RTC) MODE1 Event Control */
#define REG_RTC_MODE1_INTENCLR     (*(RwReg16*)0x40002408UL) /**< \brief (RTC) MODE1 Interrupt Enable Clear */
#define REG_RTC_MODE1_INTENSET     (*(RwReg16*)0x4000240AUL) /**< \brief (RTC) MODE1 Interrupt Enable Set */
#define REG_RTC_MODE1_INTFLAG      (*(RwReg16*)0x4000240CUL) /**< \brief (RTC) MODE1 Interrupt Flag Status and Clear */
#define REG_RTC_MODE1_SYNCBUSY     (*(RoReg  *)0x40002410UL) /**< \brief (RTC) MODE1 Synchronization Busy Status */
#define REG_RTC_MODE1_COUNT        (*(RwReg16*)0x40002418UL) /**< \brief (RTC) MODE1 Counter Value */
#define REG_RTC_MODE1_PER          (*(RwReg16*)0x4000241CUL) /**< \brief (RTC) MODE1 Counter Period */
#define REG_RTC_MODE1_COMP0        (*(RwReg16*)0x40002420UL) /**< \brief (RTC) MODE1 Compare 0 Value */
#define REG_RTC_MODE1_COMP1        (*(RwReg16*)0x40002422UL) /**< \brief (RTC) MODE1 Compare 1 Value */
#define REG_RTC_MODE2_CTRLA        (*(RwReg16*)0x40002400UL) /**< \brief (RTC) MODE2 Control A */
#define REG_RTC_MODE2_EVCTRL       (*(RwReg  *)0x40002404UL) /**< \brief (RTC) MODE2 Event Control */
#define REG_RTC_MODE2_INTENCLR     (*(RwReg16*)0x40002408UL) /**< \brief (RTC) MODE2 Interrupt Enable Clear */
#define REG_RTC_MODE2_INTENSET     (*(RwReg16*)0x4000240AUL) /**< \brief (RTC) MODE2 Interrupt Enable Set */
#define REG_RTC_MODE2_INTFLAG      (*(RwReg16*)0x4000240CUL) /**< \brief (RTC) MODE2 Interrupt Flag Status and Clear */
#define REG_RTC_MODE2_SYNCBUSY     (*(RoReg  *)0x40002410UL) /**< \brief (RTC) MODE2 Synchronization Busy Status */
#define REG_RTC_MODE2_CLOCK        (*(RwReg  *)0x40002418UL) /**< \brief (RTC) MODE2 Clock Value */
#define REG_RTC_MODE2_ALARM_ALARM0 (*(RwReg  *)0x40002420UL) /**< \brief (RTC) MODE2_ALARM Alarm 0 Value */
#define REG_RTC_MODE2_ALARM_MASK0  (*(RwReg8 *)0x40002424UL) /**< \brief (RTC) MODE2_ALARM Alarm 0 Mask */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for RTC peripheral ========== */
#define RTC_ALARM_NUM               1        // Number of Alarms
#define RTC_COMP16_NUM              2        // Number of 16-bit Comparators
#define RTC_COMP32_NUM              1        // Number of 32-bit Comparators
#define RTC_GPR_NUM                 0        // Number of General-Purpose Registers
#define RTC_PER_NUM                 8        // Number of Periodic Intervals

#endif /* _SAMC21_RTC_INSTANCE_ */
