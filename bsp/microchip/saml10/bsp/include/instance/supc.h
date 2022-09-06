/**
 * \file
 *
 * \brief Instance description for SUPC
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
#ifndef _SAML10_SUPC_INSTANCE_H_
#define _SAML10_SUPC_INSTANCE_H_

/* ========== Register definition for SUPC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_SUPC_INTENCLR       (0x40001800) /**< (SUPC) Interrupt Enable Clear */
#define REG_SUPC_INTENSET       (0x40001804) /**< (SUPC) Interrupt Enable Set */
#define REG_SUPC_INTFLAG        (0x40001808) /**< (SUPC) Interrupt Flag Status and Clear */
#define REG_SUPC_STATUS         (0x4000180C) /**< (SUPC) Power and Clocks Status */
#define REG_SUPC_BOD33          (0x40001810) /**< (SUPC) BOD33 Control */
#define REG_SUPC_BOD12          (0x40001814) /**< (SUPC) BOD12 Control */
#define REG_SUPC_VREG           (0x40001818) /**< (SUPC) VREG Control */
#define REG_SUPC_VREF           (0x4000181C) /**< (SUPC) VREF Control */
#define REG_SUPC_EVCTRL         (0x4000182C) /**< (SUPC) Event Control */
#define REG_SUPC_VREGSUSP       (0x40001830) /**< (SUPC) VREG Suspend Control */

#else

#define REG_SUPC_INTENCLR       (*(__IO uint32_t*)0x40001800U) /**< (SUPC) Interrupt Enable Clear */
#define REG_SUPC_INTENSET       (*(__IO uint32_t*)0x40001804U) /**< (SUPC) Interrupt Enable Set */
#define REG_SUPC_INTFLAG        (*(__IO uint32_t*)0x40001808U) /**< (SUPC) Interrupt Flag Status and Clear */
#define REG_SUPC_STATUS         (*(__I  uint32_t*)0x4000180CU) /**< (SUPC) Power and Clocks Status */
#define REG_SUPC_BOD33          (*(__IO uint32_t*)0x40001810U) /**< (SUPC) BOD33 Control */
#define REG_SUPC_BOD12          (*(__IO uint32_t*)0x40001814U) /**< (SUPC) BOD12 Control */
#define REG_SUPC_VREG           (*(__IO uint32_t*)0x40001818U) /**< (SUPC) VREG Control */
#define REG_SUPC_VREF           (*(__IO uint32_t*)0x4000181CU) /**< (SUPC) VREF Control */
#define REG_SUPC_EVCTRL         (*(__IO uint32_t*)0x4000182CU) /**< (SUPC) Event Control */
#define REG_SUPC_VREGSUSP       (*(__IO uint32_t*)0x40001830U) /**< (SUPC) VREG Suspend Control */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for SUPC peripheral ========== */
#define SUPC_BOD12_CALIB_MSB                     5          
#define SUPC_BOD33_CALIB_MSB                     5          
#define SUPC_INSTANCE_ID                         6          

#endif /* _SAML10_SUPC_INSTANCE_ */
