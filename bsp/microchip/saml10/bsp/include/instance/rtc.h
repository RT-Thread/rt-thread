/**
 * \file
 *
 * \brief Instance description for RTC
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
#ifndef _SAML10_RTC_INSTANCE_H_
#define _SAML10_RTC_INSTANCE_H_

/* ========== Register definition for RTC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_RTC_DBGCTRL         (0x4000240E) /**< (RTC) Debug Control */
#define REG_RTC_FREQCORR        (0x40002414) /**< (RTC) Frequency Correction */
#define REG_RTC_GP              (0x40002440) /**< (RTC) General Purpose */
#define REG_RTC_GP0             (0x40002440) /**< (RTC) General Purpose 0 */
#define REG_RTC_GP1             (0x40002444) /**< (RTC) General Purpose 1 */
#define REG_RTC_TAMPCTRL        (0x40002460) /**< (RTC) Tamper Control */
#define REG_RTC_TAMPID          (0x40002468) /**< (RTC) Tamper ID */
#define REG_RTC_TAMPCTRLB       (0x4000246C) /**< (RTC) Tamper Control B */
#define REG_RTC_MODE0_CTRLA     (0x40002400) /**< (RTC) MODE0 Control A */
#define REG_RTC_MODE0_CTRLB     (0x40002402) /**< (RTC) MODE0 Control B */
#define REG_RTC_MODE0_EVCTRL    (0x40002404) /**< (RTC) MODE0 Event Control */
#define REG_RTC_MODE0_INTENCLR  (0x40002408) /**< (RTC) MODE0 Interrupt Enable Clear */
#define REG_RTC_MODE0_INTENSET  (0x4000240A) /**< (RTC) MODE0 Interrupt Enable Set */
#define REG_RTC_MODE0_INTFLAG   (0x4000240C) /**< (RTC) MODE0 Interrupt Flag Status and Clear */
#define REG_RTC_MODE0_SYNCBUSY  (0x40002410) /**< (RTC) MODE0 Synchronization Busy Status */
#define REG_RTC_MODE0_COUNT     (0x40002418) /**< (RTC) MODE0 Counter Value */
#define REG_RTC_MODE0_COMP      (0x40002420) /**< (RTC) MODE0 Compare n Value */
#define REG_RTC_MODE0_COMP0     (0x40002420) /**< (RTC) MODE0 Compare 0 Value */
#define REG_RTC_MODE0_TIMESTAMP (0x40002464) /**< (RTC) MODE0 Timestamp */
#define REG_RTC_MODE1_CTRLA     (0x40002400) /**< (RTC) MODE1 Control A */
#define REG_RTC_MODE1_CTRLB     (0x40002402) /**< (RTC) MODE1 Control B */
#define REG_RTC_MODE1_EVCTRL    (0x40002404) /**< (RTC) MODE1 Event Control */
#define REG_RTC_MODE1_INTENCLR  (0x40002408) /**< (RTC) MODE1 Interrupt Enable Clear */
#define REG_RTC_MODE1_INTENSET  (0x4000240A) /**< (RTC) MODE1 Interrupt Enable Set */
#define REG_RTC_MODE1_INTFLAG   (0x4000240C) /**< (RTC) MODE1 Interrupt Flag Status and Clear */
#define REG_RTC_MODE1_SYNCBUSY  (0x40002410) /**< (RTC) MODE1 Synchronization Busy Status */
#define REG_RTC_MODE1_COUNT     (0x40002418) /**< (RTC) MODE1 Counter Value */
#define REG_RTC_MODE1_PER       (0x4000241C) /**< (RTC) MODE1 Counter Period */
#define REG_RTC_MODE1_COMP      (0x40002420) /**< (RTC) MODE1 Compare n Value */
#define REG_RTC_MODE1_COMP0     (0x40002420) /**< (RTC) MODE1 Compare 0 Value */
#define REG_RTC_MODE1_COMP1     (0x40002422) /**< (RTC) MODE1 Compare 1 Value */
#define REG_RTC_MODE1_TIMESTAMP (0x40002464) /**< (RTC) MODE1 Timestamp */
#define REG_RTC_MODE2_ALARM0    (0x40002420) /**< (RTC) MODE2_ALARM Alarm 0 Value */
#define REG_RTC_MODE2_MASK0     (0x40002424) /**< (RTC) MODE2_ALARM Alarm 0 Mask */
#define REG_RTC_MODE2_CTRLA     (0x40002400) /**< (RTC) MODE2 Control A */
#define REG_RTC_MODE2_CTRLB     (0x40002402) /**< (RTC) MODE2 Control B */
#define REG_RTC_MODE2_EVCTRL    (0x40002404) /**< (RTC) MODE2 Event Control */
#define REG_RTC_MODE2_INTENCLR  (0x40002408) /**< (RTC) MODE2 Interrupt Enable Clear */
#define REG_RTC_MODE2_INTENSET  (0x4000240A) /**< (RTC) MODE2 Interrupt Enable Set */
#define REG_RTC_MODE2_INTFLAG   (0x4000240C) /**< (RTC) MODE2 Interrupt Flag Status and Clear */
#define REG_RTC_MODE2_SYNCBUSY  (0x40002410) /**< (RTC) MODE2 Synchronization Busy Status */
#define REG_RTC_MODE2_CLOCK     (0x40002418) /**< (RTC) MODE2 Clock Value */
#define REG_RTC_MODE2_TIMESTAMP (0x40002464) /**< (RTC) MODE2 Timestamp */

#else

#define REG_RTC_DBGCTRL         (*(__IO uint8_t*)0x4000240EU) /**< (RTC) Debug Control */
#define REG_RTC_FREQCORR        (*(__IO uint8_t*)0x40002414U) /**< (RTC) Frequency Correction */
#define REG_RTC_GP              (*(__IO uint32_t*)0x40002440U) /**< (RTC) General Purpose */
#define REG_RTC_GP0             (*(__IO uint32_t*)0x40002440U) /**< (RTC) General Purpose 0 */
#define REG_RTC_GP1             (*(__IO uint32_t*)0x40002444U) /**< (RTC) General Purpose 1 */
#define REG_RTC_TAMPCTRL        (*(__IO uint32_t*)0x40002460U) /**< (RTC) Tamper Control */
#define REG_RTC_TAMPID          (*(__IO uint32_t*)0x40002468U) /**< (RTC) Tamper ID */
#define REG_RTC_TAMPCTRLB       (*(__IO uint32_t*)0x4000246CU) /**< (RTC) Tamper Control B */
#define REG_RTC_MODE0_CTRLA     (*(__IO uint16_t*)0x40002400U) /**< (RTC) MODE0 Control A */
#define REG_RTC_MODE0_CTRLB     (*(__IO uint16_t*)0x40002402U) /**< (RTC) MODE0 Control B */
#define REG_RTC_MODE0_EVCTRL    (*(__IO uint32_t*)0x40002404U) /**< (RTC) MODE0 Event Control */
#define REG_RTC_MODE0_INTENCLR  (*(__IO uint16_t*)0x40002408U) /**< (RTC) MODE0 Interrupt Enable Clear */
#define REG_RTC_MODE0_INTENSET  (*(__IO uint16_t*)0x4000240AU) /**< (RTC) MODE0 Interrupt Enable Set */
#define REG_RTC_MODE0_INTFLAG   (*(__IO uint16_t*)0x4000240CU) /**< (RTC) MODE0 Interrupt Flag Status and Clear */
#define REG_RTC_MODE0_SYNCBUSY  (*(__I  uint32_t*)0x40002410U) /**< (RTC) MODE0 Synchronization Busy Status */
#define REG_RTC_MODE0_COUNT     (*(__IO uint32_t*)0x40002418U) /**< (RTC) MODE0 Counter Value */
#define REG_RTC_MODE0_COMP      (*(__IO uint32_t*)0x40002420U) /**< (RTC) MODE0 Compare n Value */
#define REG_RTC_MODE0_COMP0     (*(__IO uint32_t*)0x40002420U) /**< (RTC) MODE0 Compare 0 Value */
#define REG_RTC_MODE0_TIMESTAMP (*(__I  uint32_t*)0x40002464U) /**< (RTC) MODE0 Timestamp */
#define REG_RTC_MODE1_CTRLA     (*(__IO uint16_t*)0x40002400U) /**< (RTC) MODE1 Control A */
#define REG_RTC_MODE1_CTRLB     (*(__IO uint16_t*)0x40002402U) /**< (RTC) MODE1 Control B */
#define REG_RTC_MODE1_EVCTRL    (*(__IO uint32_t*)0x40002404U) /**< (RTC) MODE1 Event Control */
#define REG_RTC_MODE1_INTENCLR  (*(__IO uint16_t*)0x40002408U) /**< (RTC) MODE1 Interrupt Enable Clear */
#define REG_RTC_MODE1_INTENSET  (*(__IO uint16_t*)0x4000240AU) /**< (RTC) MODE1 Interrupt Enable Set */
#define REG_RTC_MODE1_INTFLAG   (*(__IO uint16_t*)0x4000240CU) /**< (RTC) MODE1 Interrupt Flag Status and Clear */
#define REG_RTC_MODE1_SYNCBUSY  (*(__I  uint32_t*)0x40002410U) /**< (RTC) MODE1 Synchronization Busy Status */
#define REG_RTC_MODE1_COUNT     (*(__IO uint16_t*)0x40002418U) /**< (RTC) MODE1 Counter Value */
#define REG_RTC_MODE1_PER       (*(__IO uint16_t*)0x4000241CU) /**< (RTC) MODE1 Counter Period */
#define REG_RTC_MODE1_COMP      (*(__IO uint16_t*)0x40002420U) /**< (RTC) MODE1 Compare n Value */
#define REG_RTC_MODE1_COMP0     (*(__IO uint16_t*)0x40002420U) /**< (RTC) MODE1 Compare 0 Value */
#define REG_RTC_MODE1_COMP1     (*(__IO uint16_t*)0x40002422U) /**< (RTC) MODE1 Compare 1 Value */
#define REG_RTC_MODE1_TIMESTAMP (*(__I  uint32_t*)0x40002464U) /**< (RTC) MODE1 Timestamp */
#define REG_RTC_MODE2_ALARM0    (*(__IO uint32_t*)0x40002420U) /**< (RTC) MODE2_ALARM Alarm 0 Value */
#define REG_RTC_MODE2_MASK0     (*(__IO uint8_t*)0x40002424U) /**< (RTC) MODE2_ALARM Alarm 0 Mask */
#define REG_RTC_MODE2_CTRLA     (*(__IO uint16_t*)0x40002400U) /**< (RTC) MODE2 Control A */
#define REG_RTC_MODE2_CTRLB     (*(__IO uint16_t*)0x40002402U) /**< (RTC) MODE2 Control B */
#define REG_RTC_MODE2_EVCTRL    (*(__IO uint32_t*)0x40002404U) /**< (RTC) MODE2 Event Control */
#define REG_RTC_MODE2_INTENCLR  (*(__IO uint16_t*)0x40002408U) /**< (RTC) MODE2 Interrupt Enable Clear */
#define REG_RTC_MODE2_INTENSET  (*(__IO uint16_t*)0x4000240AU) /**< (RTC) MODE2 Interrupt Enable Set */
#define REG_RTC_MODE2_INTFLAG   (*(__IO uint16_t*)0x4000240CU) /**< (RTC) MODE2 Interrupt Flag Status and Clear */
#define REG_RTC_MODE2_SYNCBUSY  (*(__I  uint32_t*)0x40002410U) /**< (RTC) MODE2 Synchronization Busy Status */
#define REG_RTC_MODE2_CLOCK     (*(__IO uint32_t*)0x40002418U) /**< (RTC) MODE2 Clock Value */
#define REG_RTC_MODE2_TIMESTAMP (*(__I  uint32_t*)0x40002464U) /**< (RTC) MODE2 Timestamp */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for RTC peripheral ========== */
#define RTC_DMAC_ID_TIMESTAMP                    1          /* DMA RTC timestamp trigger */
#define RTC_GPR_NUM                              2          /* Number of General-Purpose Registers */
#define RTC_NUM_OF_ALARMS                        1          /* Number of Alarms */
#define RTC_NUM_OF_BKREGS                        0          /* Number of Backup Registers */
#define RTC_NUM_OF_COMP16                        2          /* Number of 16-bit Comparators */
#define RTC_NUM_OF_COMP32                        1          /* Number of 32-bit Comparators */
#define RTC_NUM_OF_TAMPERS                       4          /* Number of Tamper Inputs */
#define RTC_PER_NUM                              8          /* Number of Periodic Intervals */
#define RTC_INSTANCE_ID                          9          

#endif /* _SAML10_RTC_INSTANCE_ */
