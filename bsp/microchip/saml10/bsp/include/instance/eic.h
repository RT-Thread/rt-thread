/**
 * \file
 *
 * \brief Instance description for EIC
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
#ifndef _SAML10_EIC_INSTANCE_H_
#define _SAML10_EIC_INSTANCE_H_

/* ========== Register definition for EIC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_EIC_CTRLA           (0x40002800) /**< (EIC) Control A */
#define REG_EIC_NMICTRL         (0x40002801) /**< (EIC) Non-Maskable Interrupt Control */
#define REG_EIC_NMIFLAG         (0x40002802) /**< (EIC) Non-Maskable Interrupt Flag Status and Clear */
#define REG_EIC_SYNCBUSY        (0x40002804) /**< (EIC) Synchronization Busy */
#define REG_EIC_EVCTRL          (0x40002808) /**< (EIC) Event Control */
#define REG_EIC_INTENCLR        (0x4000280C) /**< (EIC) Interrupt Enable Clear */
#define REG_EIC_INTENSET        (0x40002810) /**< (EIC) Interrupt Enable Set */
#define REG_EIC_INTFLAG         (0x40002814) /**< (EIC) Interrupt Flag Status and Clear */
#define REG_EIC_ASYNCH          (0x40002818) /**< (EIC) External Interrupt Asynchronous Mode */
#define REG_EIC_CONFIG          (0x4000281C) /**< (EIC) External Interrupt Sense Configuration */
#define REG_EIC_CONFIG0         (0x4000281C) /**< (EIC) External Interrupt Sense Configuration 0 */
#define REG_EIC_DEBOUNCEN       (0x40002830) /**< (EIC) Debouncer Enable */
#define REG_EIC_DPRESCALER      (0x40002834) /**< (EIC) Debouncer Prescaler */
#define REG_EIC_PINSTATE        (0x40002838) /**< (EIC) Pin State */
#define REG_EIC_NSCHK           (0x4000283C) /**< (EIC) Non-secure Interrupt Check Enable */
#define REG_EIC_NONSEC          (0x40002840) /**< (EIC) Non-secure Interrupt */

#else

#define REG_EIC_CTRLA           (*(__IO uint8_t*)0x40002800U) /**< (EIC) Control A */
#define REG_EIC_NMICTRL         (*(__IO uint8_t*)0x40002801U) /**< (EIC) Non-Maskable Interrupt Control */
#define REG_EIC_NMIFLAG         (*(__IO uint8_t*)0x40002802U) /**< (EIC) Non-Maskable Interrupt Flag Status and Clear */
#define REG_EIC_SYNCBUSY        (*(__I  uint32_t*)0x40002804U) /**< (EIC) Synchronization Busy */
#define REG_EIC_EVCTRL          (*(__IO uint32_t*)0x40002808U) /**< (EIC) Event Control */
#define REG_EIC_INTENCLR        (*(__IO uint32_t*)0x4000280CU) /**< (EIC) Interrupt Enable Clear */
#define REG_EIC_INTENSET        (*(__IO uint32_t*)0x40002810U) /**< (EIC) Interrupt Enable Set */
#define REG_EIC_INTFLAG         (*(__IO uint32_t*)0x40002814U) /**< (EIC) Interrupt Flag Status and Clear */
#define REG_EIC_ASYNCH          (*(__IO uint32_t*)0x40002818U) /**< (EIC) External Interrupt Asynchronous Mode */
#define REG_EIC_CONFIG          (*(__IO uint32_t*)0x4000281CU) /**< (EIC) External Interrupt Sense Configuration */
#define REG_EIC_CONFIG0         (*(__IO uint32_t*)0x4000281CU) /**< (EIC) External Interrupt Sense Configuration 0 */
#define REG_EIC_DEBOUNCEN       (*(__IO uint32_t*)0x40002830U) /**< (EIC) Debouncer Enable */
#define REG_EIC_DPRESCALER      (*(__IO uint32_t*)0x40002834U) /**< (EIC) Debouncer Prescaler */
#define REG_EIC_PINSTATE        (*(__I  uint32_t*)0x40002838U) /**< (EIC) Pin State */
#define REG_EIC_NSCHK           (*(__IO uint32_t*)0x4000283CU) /**< (EIC) Non-secure Interrupt Check Enable */
#define REG_EIC_NONSEC          (*(__IO uint32_t*)0x40002840U) /**< (EIC) Non-secure Interrupt */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for EIC peripheral ========== */
#define EIC_EXTINT_NUM                           8          /* Number of external interrupts */
#define EIC_GCLK_ID                              3          /* Generic Clock index */
#define EIC_NUMBER_OF_CONFIG_REGS                1          /* Number of CONFIG registers */
#define EIC_NUMBER_OF_DPRESCALER_REGS            1          /* Number of DPRESCALER registers */
#define EIC_NUMBER_OF_INTERRUPTS                 8          /* Number of external interrupts (obsolete) */
#define EIC_SECURE_IMPLEMENTED                   1          /* Security Configuration implemented? */
#define EIC_INSTANCE_ID                          10         

#endif /* _SAML10_EIC_INSTANCE_ */
