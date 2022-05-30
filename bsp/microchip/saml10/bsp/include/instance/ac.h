/**
 * \file
 *
 * \brief Instance description for AC
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
#ifndef _SAML10_AC_INSTANCE_H_
#define _SAML10_AC_INSTANCE_H_

/* ========== Register definition for AC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_AC_CTRLA            (0x40003400) /**< (AC) Control A */
#define REG_AC_CTRLB            (0x40003401) /**< (AC) Control B */
#define REG_AC_EVCTRL           (0x40003402) /**< (AC) Event Control */
#define REG_AC_INTENCLR         (0x40003404) /**< (AC) Interrupt Enable Clear */
#define REG_AC_INTENSET         (0x40003405) /**< (AC) Interrupt Enable Set */
#define REG_AC_INTFLAG          (0x40003406) /**< (AC) Interrupt Flag Status and Clear */
#define REG_AC_STATUSA          (0x40003407) /**< (AC) Status A */
#define REG_AC_STATUSB          (0x40003408) /**< (AC) Status B */
#define REG_AC_DBGCTRL          (0x40003409) /**< (AC) Debug Control */
#define REG_AC_WINCTRL          (0x4000340A) /**< (AC) Window Control */
#define REG_AC_SCALER           (0x4000340C) /**< (AC) Scaler n */
#define REG_AC_SCALER0          (0x4000340C) /**< (AC) Scaler 0 */
#define REG_AC_SCALER1          (0x4000340D) /**< (AC) Scaler 1 */
#define REG_AC_COMPCTRL         (0x40003410) /**< (AC) Comparator Control n */
#define REG_AC_COMPCTRL0        (0x40003410) /**< (AC) Comparator Control 0 */
#define REG_AC_COMPCTRL1        (0x40003414) /**< (AC) Comparator Control 1 */
#define REG_AC_SYNCBUSY         (0x40003420) /**< (AC) Synchronization Busy */

#else

#define REG_AC_CTRLA            (*(__IO uint8_t*)0x40003400U) /**< (AC) Control A */
#define REG_AC_CTRLB            (*(__O  uint8_t*)0x40003401U) /**< (AC) Control B */
#define REG_AC_EVCTRL           (*(__IO uint16_t*)0x40003402U) /**< (AC) Event Control */
#define REG_AC_INTENCLR         (*(__IO uint8_t*)0x40003404U) /**< (AC) Interrupt Enable Clear */
#define REG_AC_INTENSET         (*(__IO uint8_t*)0x40003405U) /**< (AC) Interrupt Enable Set */
#define REG_AC_INTFLAG          (*(__IO uint8_t*)0x40003406U) /**< (AC) Interrupt Flag Status and Clear */
#define REG_AC_STATUSA          (*(__I  uint8_t*)0x40003407U) /**< (AC) Status A */
#define REG_AC_STATUSB          (*(__I  uint8_t*)0x40003408U) /**< (AC) Status B */
#define REG_AC_DBGCTRL          (*(__IO uint8_t*)0x40003409U) /**< (AC) Debug Control */
#define REG_AC_WINCTRL          (*(__IO uint8_t*)0x4000340AU) /**< (AC) Window Control */
#define REG_AC_SCALER           (*(__IO uint8_t*)0x4000340CU) /**< (AC) Scaler n */
#define REG_AC_SCALER0          (*(__IO uint8_t*)0x4000340CU) /**< (AC) Scaler 0 */
#define REG_AC_SCALER1          (*(__IO uint8_t*)0x4000340DU) /**< (AC) Scaler 1 */
#define REG_AC_COMPCTRL         (*(__IO uint32_t*)0x40003410U) /**< (AC) Comparator Control n */
#define REG_AC_COMPCTRL0        (*(__IO uint32_t*)0x40003410U) /**< (AC) Comparator Control 0 */
#define REG_AC_COMPCTRL1        (*(__IO uint32_t*)0x40003414U) /**< (AC) Comparator Control 1 */
#define REG_AC_SYNCBUSY         (*(__I  uint32_t*)0x40003420U) /**< (AC) Synchronization Busy */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for AC peripheral ========== */
#define AC_GCLK_ID                               17         /* Index of Generic Clock */
#define AC_NUM_CMP                               2          /* Number of comparators */
#define AC_PAIRS                                 1          /* Number of pairs of comparators */
#define AC_INSTANCE_ID                           13         

#endif /* _SAML10_AC_INSTANCE_ */
