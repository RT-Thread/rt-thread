/**
 * \file
 *
 * \brief Instance description for TRAM
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
#ifndef _SAML10_TRAM_INSTANCE_H_
#define _SAML10_TRAM_INSTANCE_H_

/* ========== Register definition for TRAM peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_TRAM_CTRLA          (0x42003400) /**< (TRAM) Control */
#define REG_TRAM_INTENCLR       (0x42003404) /**< (TRAM) Interrupt Enable Clear */
#define REG_TRAM_INTENSET       (0x42003405) /**< (TRAM) Interrupt Enable Set */
#define REG_TRAM_INTFLAG        (0x42003406) /**< (TRAM) Interrupt Flag Status and Clear */
#define REG_TRAM_STATUS         (0x42003407) /**< (TRAM) Status */
#define REG_TRAM_SYNCBUSY       (0x42003408) /**< (TRAM) Synchronization Busy Status */
#define REG_TRAM_DSCC           (0x4200340C) /**< (TRAM) Data Scramble Control */
#define REG_TRAM_PERMW          (0x42003410) /**< (TRAM) Permutation Write */
#define REG_TRAM_PERMR          (0x42003411) /**< (TRAM) Permutation Read */
#define REG_TRAM_RAM            (0x42003500) /**< (TRAM) TrustRAM */
#define REG_TRAM_RAM0           (0x42003500) /**< (TRAM) TrustRAM 0 */
#define REG_TRAM_RAM1           (0x42003504) /**< (TRAM) TrustRAM 1 */
#define REG_TRAM_RAM2           (0x42003508) /**< (TRAM) TrustRAM 2 */
#define REG_TRAM_RAM3           (0x4200350C) /**< (TRAM) TrustRAM 3 */
#define REG_TRAM_RAM4           (0x42003510) /**< (TRAM) TrustRAM 4 */
#define REG_TRAM_RAM5           (0x42003514) /**< (TRAM) TrustRAM 5 */
#define REG_TRAM_RAM6           (0x42003518) /**< (TRAM) TrustRAM 6 */
#define REG_TRAM_RAM7           (0x4200351C) /**< (TRAM) TrustRAM 7 */
#define REG_TRAM_RAM8           (0x42003520) /**< (TRAM) TrustRAM 8 */
#define REG_TRAM_RAM9           (0x42003524) /**< (TRAM) TrustRAM 9 */
#define REG_TRAM_RAM10          (0x42003528) /**< (TRAM) TrustRAM 10 */
#define REG_TRAM_RAM11          (0x4200352C) /**< (TRAM) TrustRAM 11 */
#define REG_TRAM_RAM12          (0x42003530) /**< (TRAM) TrustRAM 12 */
#define REG_TRAM_RAM13          (0x42003534) /**< (TRAM) TrustRAM 13 */
#define REG_TRAM_RAM14          (0x42003538) /**< (TRAM) TrustRAM 14 */
#define REG_TRAM_RAM15          (0x4200353C) /**< (TRAM) TrustRAM 15 */
#define REG_TRAM_RAM16          (0x42003540) /**< (TRAM) TrustRAM 16 */
#define REG_TRAM_RAM17          (0x42003544) /**< (TRAM) TrustRAM 17 */
#define REG_TRAM_RAM18          (0x42003548) /**< (TRAM) TrustRAM 18 */
#define REG_TRAM_RAM19          (0x4200354C) /**< (TRAM) TrustRAM 19 */
#define REG_TRAM_RAM20          (0x42003550) /**< (TRAM) TrustRAM 20 */
#define REG_TRAM_RAM21          (0x42003554) /**< (TRAM) TrustRAM 21 */
#define REG_TRAM_RAM22          (0x42003558) /**< (TRAM) TrustRAM 22 */
#define REG_TRAM_RAM23          (0x4200355C) /**< (TRAM) TrustRAM 23 */
#define REG_TRAM_RAM24          (0x42003560) /**< (TRAM) TrustRAM 24 */
#define REG_TRAM_RAM25          (0x42003564) /**< (TRAM) TrustRAM 25 */
#define REG_TRAM_RAM26          (0x42003568) /**< (TRAM) TrustRAM 26 */
#define REG_TRAM_RAM27          (0x4200356C) /**< (TRAM) TrustRAM 27 */
#define REG_TRAM_RAM28          (0x42003570) /**< (TRAM) TrustRAM 28 */
#define REG_TRAM_RAM29          (0x42003574) /**< (TRAM) TrustRAM 29 */
#define REG_TRAM_RAM30          (0x42003578) /**< (TRAM) TrustRAM 30 */
#define REG_TRAM_RAM31          (0x4200357C) /**< (TRAM) TrustRAM 31 */
#define REG_TRAM_RAM32          (0x42003580) /**< (TRAM) TrustRAM 32 */
#define REG_TRAM_RAM33          (0x42003584) /**< (TRAM) TrustRAM 33 */
#define REG_TRAM_RAM34          (0x42003588) /**< (TRAM) TrustRAM 34 */
#define REG_TRAM_RAM35          (0x4200358C) /**< (TRAM) TrustRAM 35 */
#define REG_TRAM_RAM36          (0x42003590) /**< (TRAM) TrustRAM 36 */
#define REG_TRAM_RAM37          (0x42003594) /**< (TRAM) TrustRAM 37 */
#define REG_TRAM_RAM38          (0x42003598) /**< (TRAM) TrustRAM 38 */
#define REG_TRAM_RAM39          (0x4200359C) /**< (TRAM) TrustRAM 39 */
#define REG_TRAM_RAM40          (0x420035A0) /**< (TRAM) TrustRAM 40 */
#define REG_TRAM_RAM41          (0x420035A4) /**< (TRAM) TrustRAM 41 */
#define REG_TRAM_RAM42          (0x420035A8) /**< (TRAM) TrustRAM 42 */
#define REG_TRAM_RAM43          (0x420035AC) /**< (TRAM) TrustRAM 43 */
#define REG_TRAM_RAM44          (0x420035B0) /**< (TRAM) TrustRAM 44 */
#define REG_TRAM_RAM45          (0x420035B4) /**< (TRAM) TrustRAM 45 */
#define REG_TRAM_RAM46          (0x420035B8) /**< (TRAM) TrustRAM 46 */
#define REG_TRAM_RAM47          (0x420035BC) /**< (TRAM) TrustRAM 47 */
#define REG_TRAM_RAM48          (0x420035C0) /**< (TRAM) TrustRAM 48 */
#define REG_TRAM_RAM49          (0x420035C4) /**< (TRAM) TrustRAM 49 */
#define REG_TRAM_RAM50          (0x420035C8) /**< (TRAM) TrustRAM 50 */
#define REG_TRAM_RAM51          (0x420035CC) /**< (TRAM) TrustRAM 51 */
#define REG_TRAM_RAM52          (0x420035D0) /**< (TRAM) TrustRAM 52 */
#define REG_TRAM_RAM53          (0x420035D4) /**< (TRAM) TrustRAM 53 */
#define REG_TRAM_RAM54          (0x420035D8) /**< (TRAM) TrustRAM 54 */
#define REG_TRAM_RAM55          (0x420035DC) /**< (TRAM) TrustRAM 55 */
#define REG_TRAM_RAM56          (0x420035E0) /**< (TRAM) TrustRAM 56 */
#define REG_TRAM_RAM57          (0x420035E4) /**< (TRAM) TrustRAM 57 */
#define REG_TRAM_RAM58          (0x420035E8) /**< (TRAM) TrustRAM 58 */
#define REG_TRAM_RAM59          (0x420035EC) /**< (TRAM) TrustRAM 59 */
#define REG_TRAM_RAM60          (0x420035F0) /**< (TRAM) TrustRAM 60 */
#define REG_TRAM_RAM61          (0x420035F4) /**< (TRAM) TrustRAM 61 */
#define REG_TRAM_RAM62          (0x420035F8) /**< (TRAM) TrustRAM 62 */
#define REG_TRAM_RAM63          (0x420035FC) /**< (TRAM) TrustRAM 63 */

#else

#define REG_TRAM_CTRLA          (*(__IO uint8_t*)0x42003400U) /**< (TRAM) Control */
#define REG_TRAM_INTENCLR       (*(__IO uint8_t*)0x42003404U) /**< (TRAM) Interrupt Enable Clear */
#define REG_TRAM_INTENSET       (*(__IO uint8_t*)0x42003405U) /**< (TRAM) Interrupt Enable Set */
#define REG_TRAM_INTFLAG        (*(__IO uint8_t*)0x42003406U) /**< (TRAM) Interrupt Flag Status and Clear */
#define REG_TRAM_STATUS         (*(__I  uint8_t*)0x42003407U) /**< (TRAM) Status */
#define REG_TRAM_SYNCBUSY       (*(__I  uint32_t*)0x42003408U) /**< (TRAM) Synchronization Busy Status */
#define REG_TRAM_DSCC           (*(__O  uint32_t*)0x4200340CU) /**< (TRAM) Data Scramble Control */
#define REG_TRAM_PERMW          (*(__O  uint8_t*)0x42003410U) /**< (TRAM) Permutation Write */
#define REG_TRAM_PERMR          (*(__I  uint8_t*)0x42003411U) /**< (TRAM) Permutation Read */
#define REG_TRAM_RAM            (*(__IO uint32_t*)0x42003500U) /**< (TRAM) TrustRAM */
#define REG_TRAM_RAM0           (*(__IO uint32_t*)0x42003500U) /**< (TRAM) TrustRAM 0 */
#define REG_TRAM_RAM1           (*(__IO uint32_t*)0x42003504U) /**< (TRAM) TrustRAM 1 */
#define REG_TRAM_RAM2           (*(__IO uint32_t*)0x42003508U) /**< (TRAM) TrustRAM 2 */
#define REG_TRAM_RAM3           (*(__IO uint32_t*)0x4200350CU) /**< (TRAM) TrustRAM 3 */
#define REG_TRAM_RAM4           (*(__IO uint32_t*)0x42003510U) /**< (TRAM) TrustRAM 4 */
#define REG_TRAM_RAM5           (*(__IO uint32_t*)0x42003514U) /**< (TRAM) TrustRAM 5 */
#define REG_TRAM_RAM6           (*(__IO uint32_t*)0x42003518U) /**< (TRAM) TrustRAM 6 */
#define REG_TRAM_RAM7           (*(__IO uint32_t*)0x4200351CU) /**< (TRAM) TrustRAM 7 */
#define REG_TRAM_RAM8           (*(__IO uint32_t*)0x42003520U) /**< (TRAM) TrustRAM 8 */
#define REG_TRAM_RAM9           (*(__IO uint32_t*)0x42003524U) /**< (TRAM) TrustRAM 9 */
#define REG_TRAM_RAM10          (*(__IO uint32_t*)0x42003528U) /**< (TRAM) TrustRAM 10 */
#define REG_TRAM_RAM11          (*(__IO uint32_t*)0x4200352CU) /**< (TRAM) TrustRAM 11 */
#define REG_TRAM_RAM12          (*(__IO uint32_t*)0x42003530U) /**< (TRAM) TrustRAM 12 */
#define REG_TRAM_RAM13          (*(__IO uint32_t*)0x42003534U) /**< (TRAM) TrustRAM 13 */
#define REG_TRAM_RAM14          (*(__IO uint32_t*)0x42003538U) /**< (TRAM) TrustRAM 14 */
#define REG_TRAM_RAM15          (*(__IO uint32_t*)0x4200353CU) /**< (TRAM) TrustRAM 15 */
#define REG_TRAM_RAM16          (*(__IO uint32_t*)0x42003540U) /**< (TRAM) TrustRAM 16 */
#define REG_TRAM_RAM17          (*(__IO uint32_t*)0x42003544U) /**< (TRAM) TrustRAM 17 */
#define REG_TRAM_RAM18          (*(__IO uint32_t*)0x42003548U) /**< (TRAM) TrustRAM 18 */
#define REG_TRAM_RAM19          (*(__IO uint32_t*)0x4200354CU) /**< (TRAM) TrustRAM 19 */
#define REG_TRAM_RAM20          (*(__IO uint32_t*)0x42003550U) /**< (TRAM) TrustRAM 20 */
#define REG_TRAM_RAM21          (*(__IO uint32_t*)0x42003554U) /**< (TRAM) TrustRAM 21 */
#define REG_TRAM_RAM22          (*(__IO uint32_t*)0x42003558U) /**< (TRAM) TrustRAM 22 */
#define REG_TRAM_RAM23          (*(__IO uint32_t*)0x4200355CU) /**< (TRAM) TrustRAM 23 */
#define REG_TRAM_RAM24          (*(__IO uint32_t*)0x42003560U) /**< (TRAM) TrustRAM 24 */
#define REG_TRAM_RAM25          (*(__IO uint32_t*)0x42003564U) /**< (TRAM) TrustRAM 25 */
#define REG_TRAM_RAM26          (*(__IO uint32_t*)0x42003568U) /**< (TRAM) TrustRAM 26 */
#define REG_TRAM_RAM27          (*(__IO uint32_t*)0x4200356CU) /**< (TRAM) TrustRAM 27 */
#define REG_TRAM_RAM28          (*(__IO uint32_t*)0x42003570U) /**< (TRAM) TrustRAM 28 */
#define REG_TRAM_RAM29          (*(__IO uint32_t*)0x42003574U) /**< (TRAM) TrustRAM 29 */
#define REG_TRAM_RAM30          (*(__IO uint32_t*)0x42003578U) /**< (TRAM) TrustRAM 30 */
#define REG_TRAM_RAM31          (*(__IO uint32_t*)0x4200357CU) /**< (TRAM) TrustRAM 31 */
#define REG_TRAM_RAM32          (*(__IO uint32_t*)0x42003580U) /**< (TRAM) TrustRAM 32 */
#define REG_TRAM_RAM33          (*(__IO uint32_t*)0x42003584U) /**< (TRAM) TrustRAM 33 */
#define REG_TRAM_RAM34          (*(__IO uint32_t*)0x42003588U) /**< (TRAM) TrustRAM 34 */
#define REG_TRAM_RAM35          (*(__IO uint32_t*)0x4200358CU) /**< (TRAM) TrustRAM 35 */
#define REG_TRAM_RAM36          (*(__IO uint32_t*)0x42003590U) /**< (TRAM) TrustRAM 36 */
#define REG_TRAM_RAM37          (*(__IO uint32_t*)0x42003594U) /**< (TRAM) TrustRAM 37 */
#define REG_TRAM_RAM38          (*(__IO uint32_t*)0x42003598U) /**< (TRAM) TrustRAM 38 */
#define REG_TRAM_RAM39          (*(__IO uint32_t*)0x4200359CU) /**< (TRAM) TrustRAM 39 */
#define REG_TRAM_RAM40          (*(__IO uint32_t*)0x420035A0U) /**< (TRAM) TrustRAM 40 */
#define REG_TRAM_RAM41          (*(__IO uint32_t*)0x420035A4U) /**< (TRAM) TrustRAM 41 */
#define REG_TRAM_RAM42          (*(__IO uint32_t*)0x420035A8U) /**< (TRAM) TrustRAM 42 */
#define REG_TRAM_RAM43          (*(__IO uint32_t*)0x420035ACU) /**< (TRAM) TrustRAM 43 */
#define REG_TRAM_RAM44          (*(__IO uint32_t*)0x420035B0U) /**< (TRAM) TrustRAM 44 */
#define REG_TRAM_RAM45          (*(__IO uint32_t*)0x420035B4U) /**< (TRAM) TrustRAM 45 */
#define REG_TRAM_RAM46          (*(__IO uint32_t*)0x420035B8U) /**< (TRAM) TrustRAM 46 */
#define REG_TRAM_RAM47          (*(__IO uint32_t*)0x420035BCU) /**< (TRAM) TrustRAM 47 */
#define REG_TRAM_RAM48          (*(__IO uint32_t*)0x420035C0U) /**< (TRAM) TrustRAM 48 */
#define REG_TRAM_RAM49          (*(__IO uint32_t*)0x420035C4U) /**< (TRAM) TrustRAM 49 */
#define REG_TRAM_RAM50          (*(__IO uint32_t*)0x420035C8U) /**< (TRAM) TrustRAM 50 */
#define REG_TRAM_RAM51          (*(__IO uint32_t*)0x420035CCU) /**< (TRAM) TrustRAM 51 */
#define REG_TRAM_RAM52          (*(__IO uint32_t*)0x420035D0U) /**< (TRAM) TrustRAM 52 */
#define REG_TRAM_RAM53          (*(__IO uint32_t*)0x420035D4U) /**< (TRAM) TrustRAM 53 */
#define REG_TRAM_RAM54          (*(__IO uint32_t*)0x420035D8U) /**< (TRAM) TrustRAM 54 */
#define REG_TRAM_RAM55          (*(__IO uint32_t*)0x420035DCU) /**< (TRAM) TrustRAM 55 */
#define REG_TRAM_RAM56          (*(__IO uint32_t*)0x420035E0U) /**< (TRAM) TrustRAM 56 */
#define REG_TRAM_RAM57          (*(__IO uint32_t*)0x420035E4U) /**< (TRAM) TrustRAM 57 */
#define REG_TRAM_RAM58          (*(__IO uint32_t*)0x420035E8U) /**< (TRAM) TrustRAM 58 */
#define REG_TRAM_RAM59          (*(__IO uint32_t*)0x420035ECU) /**< (TRAM) TrustRAM 59 */
#define REG_TRAM_RAM60          (*(__IO uint32_t*)0x420035F0U) /**< (TRAM) TrustRAM 60 */
#define REG_TRAM_RAM61          (*(__IO uint32_t*)0x420035F4U) /**< (TRAM) TrustRAM 61 */
#define REG_TRAM_RAM62          (*(__IO uint32_t*)0x420035F8U) /**< (TRAM) TrustRAM 62 */
#define REG_TRAM_RAM63          (*(__IO uint32_t*)0x420035FCU) /**< (TRAM) TrustRAM 63 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for TRAM peripheral ========== */
#define TRAM_INSTANCE_ID                         77         

#endif /* _SAML10_TRAM_INSTANCE_ */
