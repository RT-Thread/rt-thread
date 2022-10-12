/**
 * \file
 *
 * \brief Instance description for SMC
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

/* file generated from device description version 2019-01-18T21:19:59Z */
#ifndef _SAME70_SMC_INSTANCE_H_
#define _SAME70_SMC_INSTANCE_H_

/* ========== Register definition for SMC peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_SMC_SETUP0          (0x40080000) /**< (SMC) SMC Setup Register 0 */
#define REG_SMC_PULSE0          (0x40080004) /**< (SMC) SMC Pulse Register 0 */
#define REG_SMC_CYCLE0          (0x40080008) /**< (SMC) SMC Cycle Register 0 */
#define REG_SMC_MODE0           (0x4008000C) /**< (SMC) SMC Mode Register 0 */
#define REG_SMC_SETUP1          (0x40080010) /**< (SMC) SMC Setup Register 1 */
#define REG_SMC_PULSE1          (0x40080014) /**< (SMC) SMC Pulse Register 1 */
#define REG_SMC_CYCLE1          (0x40080018) /**< (SMC) SMC Cycle Register 1 */
#define REG_SMC_MODE1           (0x4008001C) /**< (SMC) SMC Mode Register 1 */
#define REG_SMC_SETUP2          (0x40080020) /**< (SMC) SMC Setup Register 2 */
#define REG_SMC_PULSE2          (0x40080024) /**< (SMC) SMC Pulse Register 2 */
#define REG_SMC_CYCLE2          (0x40080028) /**< (SMC) SMC Cycle Register 2 */
#define REG_SMC_MODE2           (0x4008002C) /**< (SMC) SMC Mode Register 2 */
#define REG_SMC_SETUP3          (0x40080030) /**< (SMC) SMC Setup Register 3 */
#define REG_SMC_PULSE3          (0x40080034) /**< (SMC) SMC Pulse Register 3 */
#define REG_SMC_CYCLE3          (0x40080038) /**< (SMC) SMC Cycle Register 3 */
#define REG_SMC_MODE3           (0x4008003C) /**< (SMC) SMC Mode Register 3 */
#define REG_SMC_OCMS            (0x40080080) /**< (SMC) SMC Off-Chip Memory Scrambling Register */
#define REG_SMC_KEY1            (0x40080084) /**< (SMC) SMC Off-Chip Memory Scrambling KEY1 Register */
#define REG_SMC_KEY2            (0x40080088) /**< (SMC) SMC Off-Chip Memory Scrambling KEY2 Register */
#define REG_SMC_WPMR            (0x400800E4) /**< (SMC) SMC Write Protection Mode Register */
#define REG_SMC_WPSR            (0x400800E8) /**< (SMC) SMC Write Protection Status Register */

#else

#define REG_SMC_SETUP0          (*(__IO uint32_t*)0x40080000U) /**< (SMC) SMC Setup Register 0 */
#define REG_SMC_PULSE0          (*(__IO uint32_t*)0x40080004U) /**< (SMC) SMC Pulse Register 0 */
#define REG_SMC_CYCLE0          (*(__IO uint32_t*)0x40080008U) /**< (SMC) SMC Cycle Register 0 */
#define REG_SMC_MODE0           (*(__IO uint32_t*)0x4008000CU) /**< (SMC) SMC Mode Register 0 */
#define REG_SMC_SETUP1          (*(__IO uint32_t*)0x40080010U) /**< (SMC) SMC Setup Register 1 */
#define REG_SMC_PULSE1          (*(__IO uint32_t*)0x40080014U) /**< (SMC) SMC Pulse Register 1 */
#define REG_SMC_CYCLE1          (*(__IO uint32_t*)0x40080018U) /**< (SMC) SMC Cycle Register 1 */
#define REG_SMC_MODE1           (*(__IO uint32_t*)0x4008001CU) /**< (SMC) SMC Mode Register 1 */
#define REG_SMC_SETUP2          (*(__IO uint32_t*)0x40080020U) /**< (SMC) SMC Setup Register 2 */
#define REG_SMC_PULSE2          (*(__IO uint32_t*)0x40080024U) /**< (SMC) SMC Pulse Register 2 */
#define REG_SMC_CYCLE2          (*(__IO uint32_t*)0x40080028U) /**< (SMC) SMC Cycle Register 2 */
#define REG_SMC_MODE2           (*(__IO uint32_t*)0x4008002CU) /**< (SMC) SMC Mode Register 2 */
#define REG_SMC_SETUP3          (*(__IO uint32_t*)0x40080030U) /**< (SMC) SMC Setup Register 3 */
#define REG_SMC_PULSE3          (*(__IO uint32_t*)0x40080034U) /**< (SMC) SMC Pulse Register 3 */
#define REG_SMC_CYCLE3          (*(__IO uint32_t*)0x40080038U) /**< (SMC) SMC Cycle Register 3 */
#define REG_SMC_MODE3           (*(__IO uint32_t*)0x4008003CU) /**< (SMC) SMC Mode Register 3 */
#define REG_SMC_OCMS            (*(__IO uint32_t*)0x40080080U) /**< (SMC) SMC Off-Chip Memory Scrambling Register */
#define REG_SMC_KEY1            (*(__O  uint32_t*)0x40080084U) /**< (SMC) SMC Off-Chip Memory Scrambling KEY1 Register */
#define REG_SMC_KEY2            (*(__O  uint32_t*)0x40080088U) /**< (SMC) SMC Off-Chip Memory Scrambling KEY2 Register */
#define REG_SMC_WPMR            (*(__IO uint32_t*)0x400800E4U) /**< (SMC) SMC Write Protection Mode Register */
#define REG_SMC_WPSR            (*(__I  uint32_t*)0x400800E8U) /**< (SMC) SMC Write Protection Status Register */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for SMC peripheral ========== */
#define SMC_INSTANCE_ID                          9          
#define SMC_CLOCK_ID                             9          

#endif /* _SAME70_SMC_INSTANCE_ */
