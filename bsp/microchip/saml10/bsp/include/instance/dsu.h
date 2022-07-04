/**
 * \file
 *
 * \brief Instance description for DSU
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
#ifndef _SAML10_DSU_INSTANCE_H_
#define _SAML10_DSU_INSTANCE_H_

/* ========== Register definition for DSU peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_DSU_CTRL            (0x41002000) /**< (DSU) Control */
#define REG_DSU_STATUSA         (0x41002001) /**< (DSU) Status A */
#define REG_DSU_STATUSB         (0x41002002) /**< (DSU) Status B */
#define REG_DSU_STATUSC         (0x41002003) /**< (DSU) Status C */
#define REG_DSU_ADDR            (0x41002004) /**< (DSU) Address */
#define REG_DSU_LENGTH          (0x41002008) /**< (DSU) Length */
#define REG_DSU_DATA            (0x4100200C) /**< (DSU) Data */
#define REG_DSU_DCC             (0x41002010) /**< (DSU) Debug Communication Channel n */
#define REG_DSU_DCC0            (0x41002010) /**< (DSU) Debug Communication Channel 0 */
#define REG_DSU_DCC1            (0x41002014) /**< (DSU) Debug Communication Channel 1 */
#define REG_DSU_DID             (0x41002018) /**< (DSU) Device Identification */
#define REG_DSU_CFG             (0x4100201C) /**< (DSU) Configuration */
#define REG_DSU_BCC             (0x41002020) /**< (DSU) Boot ROM Communication Channel n */
#define REG_DSU_BCC0            (0x41002020) /**< (DSU) Boot ROM Communication Channel 0 */
#define REG_DSU_BCC1            (0x41002024) /**< (DSU) Boot ROM Communication Channel 1 */
#define REG_DSU_DCFG            (0x410020F0) /**< (DSU) Device Configuration */
#define REG_DSU_DCFG0           (0x410020F0) /**< (DSU) Device Configuration 0 */
#define REG_DSU_DCFG1           (0x410020F4) /**< (DSU) Device Configuration 1 */
#define REG_DSU_ENTRY0          (0x41003000) /**< (DSU) CoreSight ROM Table Entry 0 */
#define REG_DSU_ENTRY1          (0x41003004) /**< (DSU) CoreSight ROM Table Entry 1 */
#define REG_DSU_END             (0x41003008) /**< (DSU) CoreSight ROM Table End */
#define REG_DSU_MEMTYPE         (0x41003FCC) /**< (DSU) CoreSight ROM Table Memory Type */
#define REG_DSU_PID4            (0x41003FD0) /**< (DSU) Peripheral Identification 4 */
#define REG_DSU_PID5            (0x41003FD4) /**< (DSU) Peripheral Identification 5 */
#define REG_DSU_PID6            (0x41003FD8) /**< (DSU) Peripheral Identification 6 */
#define REG_DSU_PID7            (0x41003FDC) /**< (DSU) Peripheral Identification 7 */
#define REG_DSU_PID0            (0x41003FE0) /**< (DSU) Peripheral Identification 0 */
#define REG_DSU_PID1            (0x41003FE4) /**< (DSU) Peripheral Identification 1 */
#define REG_DSU_PID2            (0x41003FE8) /**< (DSU) Peripheral Identification 2 */
#define REG_DSU_PID3            (0x41003FEC) /**< (DSU) Peripheral Identification 3 */
#define REG_DSU_CID0            (0x41003FF0) /**< (DSU) Component Identification 0 */
#define REG_DSU_CID1            (0x41003FF4) /**< (DSU) Component Identification 1 */
#define REG_DSU_CID2            (0x41003FF8) /**< (DSU) Component Identification 2 */
#define REG_DSU_CID3            (0x41003FFC) /**< (DSU) Component Identification 3 */

#else

#define REG_DSU_CTRL            (*(__O  uint8_t*)0x41002000U) /**< (DSU) Control */
#define REG_DSU_STATUSA         (*(__IO uint8_t*)0x41002001U) /**< (DSU) Status A */
#define REG_DSU_STATUSB         (*(__I  uint8_t*)0x41002002U) /**< (DSU) Status B */
#define REG_DSU_STATUSC         (*(__I  uint8_t*)0x41002003U) /**< (DSU) Status C */
#define REG_DSU_ADDR            (*(__IO uint32_t*)0x41002004U) /**< (DSU) Address */
#define REG_DSU_LENGTH          (*(__IO uint32_t*)0x41002008U) /**< (DSU) Length */
#define REG_DSU_DATA            (*(__IO uint32_t*)0x4100200CU) /**< (DSU) Data */
#define REG_DSU_DCC             (*(__IO uint32_t*)0x41002010U) /**< (DSU) Debug Communication Channel n */
#define REG_DSU_DCC0            (*(__IO uint32_t*)0x41002010U) /**< (DSU) Debug Communication Channel 0 */
#define REG_DSU_DCC1            (*(__IO uint32_t*)0x41002014U) /**< (DSU) Debug Communication Channel 1 */
#define REG_DSU_DID             (*(__I  uint32_t*)0x41002018U) /**< (DSU) Device Identification */
#define REG_DSU_CFG             (*(__IO uint32_t*)0x4100201CU) /**< (DSU) Configuration */
#define REG_DSU_BCC             (*(__IO uint32_t*)0x41002020U) /**< (DSU) Boot ROM Communication Channel n */
#define REG_DSU_BCC0            (*(__IO uint32_t*)0x41002020U) /**< (DSU) Boot ROM Communication Channel 0 */
#define REG_DSU_BCC1            (*(__IO uint32_t*)0x41002024U) /**< (DSU) Boot ROM Communication Channel 1 */
#define REG_DSU_DCFG            (*(__IO uint32_t*)0x410020F0U) /**< (DSU) Device Configuration */
#define REG_DSU_DCFG0           (*(__IO uint32_t*)0x410020F0U) /**< (DSU) Device Configuration 0 */
#define REG_DSU_DCFG1           (*(__IO uint32_t*)0x410020F4U) /**< (DSU) Device Configuration 1 */
#define REG_DSU_ENTRY0          (*(__I  uint32_t*)0x41003000U) /**< (DSU) CoreSight ROM Table Entry 0 */
#define REG_DSU_ENTRY1          (*(__I  uint32_t*)0x41003004U) /**< (DSU) CoreSight ROM Table Entry 1 */
#define REG_DSU_END             (*(__I  uint32_t*)0x41003008U) /**< (DSU) CoreSight ROM Table End */
#define REG_DSU_MEMTYPE         (*(__I  uint32_t*)0x41003FCCU) /**< (DSU) CoreSight ROM Table Memory Type */
#define REG_DSU_PID4            (*(__I  uint32_t*)0x41003FD0U) /**< (DSU) Peripheral Identification 4 */
#define REG_DSU_PID5            (*(__I  uint32_t*)0x41003FD4U) /**< (DSU) Peripheral Identification 5 */
#define REG_DSU_PID6            (*(__I  uint32_t*)0x41003FD8U) /**< (DSU) Peripheral Identification 6 */
#define REG_DSU_PID7            (*(__I  uint32_t*)0x41003FDCU) /**< (DSU) Peripheral Identification 7 */
#define REG_DSU_PID0            (*(__I  uint32_t*)0x41003FE0U) /**< (DSU) Peripheral Identification 0 */
#define REG_DSU_PID1            (*(__I  uint32_t*)0x41003FE4U) /**< (DSU) Peripheral Identification 1 */
#define REG_DSU_PID2            (*(__I  uint32_t*)0x41003FE8U) /**< (DSU) Peripheral Identification 2 */
#define REG_DSU_PID3            (*(__I  uint32_t*)0x41003FECU) /**< (DSU) Peripheral Identification 3 */
#define REG_DSU_CID0            (*(__I  uint32_t*)0x41003FF0U) /**< (DSU) Component Identification 0 */
#define REG_DSU_CID1            (*(__I  uint32_t*)0x41003FF4U) /**< (DSU) Component Identification 1 */
#define REG_DSU_CID2            (*(__I  uint32_t*)0x41003FF8U) /**< (DSU) Component Identification 2 */
#define REG_DSU_CID3            (*(__I  uint32_t*)0x41003FFCU) /**< (DSU) Component Identification 3 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for DSU peripheral ========== */
#define DSU_DMAC_ID_DCC0                         2          /* DMAC ID for DCC0 register */
#define DSU_DMAC_ID_DCC1                         3          /* DMAC ID for DCC1 register */
#define DSU_INSTANCE_ID                          33         

#endif /* _SAML10_DSU_INSTANCE_ */
