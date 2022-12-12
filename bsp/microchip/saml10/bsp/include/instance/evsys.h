/**
 * \file
 *
 * \brief Instance description for EVSYS
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
#ifndef _SAML10_EVSYS_INSTANCE_H_
#define _SAML10_EVSYS_INSTANCE_H_

/* ========== Register definition for EVSYS peripheral ========== */
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_EVSYS_CHANNEL0      (0x42000020) /**< (EVSYS) Channel 0 Control */
#define REG_EVSYS_CHINTENCLR0   (0x42000024) /**< (EVSYS) Channel 0 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET0   (0x42000025) /**< (EVSYS) Channel 0 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG0    (0x42000026) /**< (EVSYS) Channel 0 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS0     (0x42000027) /**< (EVSYS) Channel 0 Status */
#define REG_EVSYS_CHANNEL1      (0x42000028) /**< (EVSYS) Channel 1 Control */
#define REG_EVSYS_CHINTENCLR1   (0x4200002C) /**< (EVSYS) Channel 1 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET1   (0x4200002D) /**< (EVSYS) Channel 1 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG1    (0x4200002E) /**< (EVSYS) Channel 1 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS1     (0x4200002F) /**< (EVSYS) Channel 1 Status */
#define REG_EVSYS_CHANNEL2      (0x42000030) /**< (EVSYS) Channel 2 Control */
#define REG_EVSYS_CHINTENCLR2   (0x42000034) /**< (EVSYS) Channel 2 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET2   (0x42000035) /**< (EVSYS) Channel 2 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG2    (0x42000036) /**< (EVSYS) Channel 2 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS2     (0x42000037) /**< (EVSYS) Channel 2 Status */
#define REG_EVSYS_CHANNEL3      (0x42000038) /**< (EVSYS) Channel 3 Control */
#define REG_EVSYS_CHINTENCLR3   (0x4200003C) /**< (EVSYS) Channel 3 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET3   (0x4200003D) /**< (EVSYS) Channel 3 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG3    (0x4200003E) /**< (EVSYS) Channel 3 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS3     (0x4200003F) /**< (EVSYS) Channel 3 Status */
#define REG_EVSYS_CHANNEL4      (0x42000040) /**< (EVSYS) Channel 4 Control */
#define REG_EVSYS_CHINTENCLR4   (0x42000044) /**< (EVSYS) Channel 4 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET4   (0x42000045) /**< (EVSYS) Channel 4 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG4    (0x42000046) /**< (EVSYS) Channel 4 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS4     (0x42000047) /**< (EVSYS) Channel 4 Status */
#define REG_EVSYS_CHANNEL5      (0x42000048) /**< (EVSYS) Channel 5 Control */
#define REG_EVSYS_CHINTENCLR5   (0x4200004C) /**< (EVSYS) Channel 5 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET5   (0x4200004D) /**< (EVSYS) Channel 5 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG5    (0x4200004E) /**< (EVSYS) Channel 5 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS5     (0x4200004F) /**< (EVSYS) Channel 5 Status */
#define REG_EVSYS_CHANNEL6      (0x42000050) /**< (EVSYS) Channel 6 Control */
#define REG_EVSYS_CHINTENCLR6   (0x42000054) /**< (EVSYS) Channel 6 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET6   (0x42000055) /**< (EVSYS) Channel 6 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG6    (0x42000056) /**< (EVSYS) Channel 6 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS6     (0x42000057) /**< (EVSYS) Channel 6 Status */
#define REG_EVSYS_CHANNEL7      (0x42000058) /**< (EVSYS) Channel 7 Control */
#define REG_EVSYS_CHINTENCLR7   (0x4200005C) /**< (EVSYS) Channel 7 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET7   (0x4200005D) /**< (EVSYS) Channel 7 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG7    (0x4200005E) /**< (EVSYS) Channel 7 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS7     (0x4200005F) /**< (EVSYS) Channel 7 Status */
#define REG_EVSYS_CTRLA         (0x42000000) /**< (EVSYS) Control */
#define REG_EVSYS_SWEVT         (0x42000004) /**< (EVSYS) Software Event */
#define REG_EVSYS_PRICTRL       (0x42000008) /**< (EVSYS) Priority Control */
#define REG_EVSYS_INTPEND       (0x42000010) /**< (EVSYS) Channel Pending Interrupt */
#define REG_EVSYS_INTSTATUS     (0x42000014) /**< (EVSYS) Interrupt Status */
#define REG_EVSYS_BUSYCH        (0x42000018) /**< (EVSYS) Busy Channels */
#define REG_EVSYS_READYUSR      (0x4200001C) /**< (EVSYS) Ready Users */
#define REG_EVSYS_USER          (0x42000120) /**< (EVSYS) User Multiplexer n */
#define REG_EVSYS_USER0         (0x42000120) /**< (EVSYS) User Multiplexer 0 */
#define REG_EVSYS_USER1         (0x42000121) /**< (EVSYS) User Multiplexer 1 */
#define REG_EVSYS_USER2         (0x42000122) /**< (EVSYS) User Multiplexer 2 */
#define REG_EVSYS_USER3         (0x42000123) /**< (EVSYS) User Multiplexer 3 */
#define REG_EVSYS_USER4         (0x42000124) /**< (EVSYS) User Multiplexer 4 */
#define REG_EVSYS_USER5         (0x42000125) /**< (EVSYS) User Multiplexer 5 */
#define REG_EVSYS_USER6         (0x42000126) /**< (EVSYS) User Multiplexer 6 */
#define REG_EVSYS_USER7         (0x42000127) /**< (EVSYS) User Multiplexer 7 */
#define REG_EVSYS_USER8         (0x42000128) /**< (EVSYS) User Multiplexer 8 */
#define REG_EVSYS_USER9         (0x42000129) /**< (EVSYS) User Multiplexer 9 */
#define REG_EVSYS_USER10        (0x4200012A) /**< (EVSYS) User Multiplexer 10 */
#define REG_EVSYS_USER11        (0x4200012B) /**< (EVSYS) User Multiplexer 11 */
#define REG_EVSYS_USER12        (0x4200012C) /**< (EVSYS) User Multiplexer 12 */
#define REG_EVSYS_USER13        (0x4200012D) /**< (EVSYS) User Multiplexer 13 */
#define REG_EVSYS_USER14        (0x4200012E) /**< (EVSYS) User Multiplexer 14 */
#define REG_EVSYS_USER15        (0x4200012F) /**< (EVSYS) User Multiplexer 15 */
#define REG_EVSYS_USER16        (0x42000130) /**< (EVSYS) User Multiplexer 16 */
#define REG_EVSYS_USER17        (0x42000131) /**< (EVSYS) User Multiplexer 17 */
#define REG_EVSYS_USER18        (0x42000132) /**< (EVSYS) User Multiplexer 18 */
#define REG_EVSYS_USER19        (0x42000133) /**< (EVSYS) User Multiplexer 19 */
#define REG_EVSYS_USER20        (0x42000134) /**< (EVSYS) User Multiplexer 20 */
#define REG_EVSYS_USER21        (0x42000135) /**< (EVSYS) User Multiplexer 21 */
#define REG_EVSYS_USER22        (0x42000136) /**< (EVSYS) User Multiplexer 22 */
#define REG_EVSYS_INTENCLR      (0x420001D4) /**< (EVSYS) Interrupt Enable Clear */
#define REG_EVSYS_INTENSET      (0x420001D5) /**< (EVSYS) Interrupt Enable Set */
#define REG_EVSYS_INTFLAG       (0x420001D6) /**< (EVSYS) Interrupt Flag Status and Clear */
#define REG_EVSYS_NONSECCHAN    (0x420001D8) /**< (EVSYS) Channels Security Attribution */
#define REG_EVSYS_NSCHKCHAN     (0x420001DC) /**< (EVSYS) Non-Secure Channels Check */
#define REG_EVSYS_NONSECUSER    (0x420001E0) /**< (EVSYS) Users Security Attribution */
#define REG_EVSYS_NONSECUSER0   (0x420001E0) /**< (EVSYS) Users Security Attribution 0 */
#define REG_EVSYS_NSCHKUSER     (0x420001F0) /**< (EVSYS) Non-Secure Users Check */
#define REG_EVSYS_NSCHKUSER0    (0x420001F0) /**< (EVSYS) Non-Secure Users Check 0 */

#else

#define REG_EVSYS_CHANNEL0      (*(__IO uint32_t*)0x42000020U) /**< (EVSYS) Channel 0 Control */
#define REG_EVSYS_CHINTENCLR0   (*(__IO uint8_t*)0x42000024U) /**< (EVSYS) Channel 0 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET0   (*(__IO uint8_t*)0x42000025U) /**< (EVSYS) Channel 0 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG0    (*(__IO uint8_t*)0x42000026U) /**< (EVSYS) Channel 0 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS0     (*(__I  uint8_t*)0x42000027U) /**< (EVSYS) Channel 0 Status */
#define REG_EVSYS_CHANNEL1      (*(__IO uint32_t*)0x42000028U) /**< (EVSYS) Channel 1 Control */
#define REG_EVSYS_CHINTENCLR1   (*(__IO uint8_t*)0x4200002CU) /**< (EVSYS) Channel 1 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET1   (*(__IO uint8_t*)0x4200002DU) /**< (EVSYS) Channel 1 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG1    (*(__IO uint8_t*)0x4200002EU) /**< (EVSYS) Channel 1 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS1     (*(__I  uint8_t*)0x4200002FU) /**< (EVSYS) Channel 1 Status */
#define REG_EVSYS_CHANNEL2      (*(__IO uint32_t*)0x42000030U) /**< (EVSYS) Channel 2 Control */
#define REG_EVSYS_CHINTENCLR2   (*(__IO uint8_t*)0x42000034U) /**< (EVSYS) Channel 2 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET2   (*(__IO uint8_t*)0x42000035U) /**< (EVSYS) Channel 2 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG2    (*(__IO uint8_t*)0x42000036U) /**< (EVSYS) Channel 2 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS2     (*(__I  uint8_t*)0x42000037U) /**< (EVSYS) Channel 2 Status */
#define REG_EVSYS_CHANNEL3      (*(__IO uint32_t*)0x42000038U) /**< (EVSYS) Channel 3 Control */
#define REG_EVSYS_CHINTENCLR3   (*(__IO uint8_t*)0x4200003CU) /**< (EVSYS) Channel 3 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET3   (*(__IO uint8_t*)0x4200003DU) /**< (EVSYS) Channel 3 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG3    (*(__IO uint8_t*)0x4200003EU) /**< (EVSYS) Channel 3 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS3     (*(__I  uint8_t*)0x4200003FU) /**< (EVSYS) Channel 3 Status */
#define REG_EVSYS_CHANNEL4      (*(__IO uint32_t*)0x42000040U) /**< (EVSYS) Channel 4 Control */
#define REG_EVSYS_CHINTENCLR4   (*(__IO uint8_t*)0x42000044U) /**< (EVSYS) Channel 4 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET4   (*(__IO uint8_t*)0x42000045U) /**< (EVSYS) Channel 4 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG4    (*(__IO uint8_t*)0x42000046U) /**< (EVSYS) Channel 4 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS4     (*(__I  uint8_t*)0x42000047U) /**< (EVSYS) Channel 4 Status */
#define REG_EVSYS_CHANNEL5      (*(__IO uint32_t*)0x42000048U) /**< (EVSYS) Channel 5 Control */
#define REG_EVSYS_CHINTENCLR5   (*(__IO uint8_t*)0x4200004CU) /**< (EVSYS) Channel 5 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET5   (*(__IO uint8_t*)0x4200004DU) /**< (EVSYS) Channel 5 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG5    (*(__IO uint8_t*)0x4200004EU) /**< (EVSYS) Channel 5 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS5     (*(__I  uint8_t*)0x4200004FU) /**< (EVSYS) Channel 5 Status */
#define REG_EVSYS_CHANNEL6      (*(__IO uint32_t*)0x42000050U) /**< (EVSYS) Channel 6 Control */
#define REG_EVSYS_CHINTENCLR6   (*(__IO uint8_t*)0x42000054U) /**< (EVSYS) Channel 6 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET6   (*(__IO uint8_t*)0x42000055U) /**< (EVSYS) Channel 6 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG6    (*(__IO uint8_t*)0x42000056U) /**< (EVSYS) Channel 6 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS6     (*(__I  uint8_t*)0x42000057U) /**< (EVSYS) Channel 6 Status */
#define REG_EVSYS_CHANNEL7      (*(__IO uint32_t*)0x42000058U) /**< (EVSYS) Channel 7 Control */
#define REG_EVSYS_CHINTENCLR7   (*(__IO uint8_t*)0x4200005CU) /**< (EVSYS) Channel 7 Interrupt Enable Clear */
#define REG_EVSYS_CHINTENSET7   (*(__IO uint8_t*)0x4200005DU) /**< (EVSYS) Channel 7 Interrupt Enable Set */
#define REG_EVSYS_CHINTFLAG7    (*(__IO uint8_t*)0x4200005EU) /**< (EVSYS) Channel 7 Interrupt Flag Status and Clear */
#define REG_EVSYS_CHSTATUS7     (*(__I  uint8_t*)0x4200005FU) /**< (EVSYS) Channel 7 Status */
#define REG_EVSYS_CTRLA         (*(__O  uint8_t*)0x42000000U) /**< (EVSYS) Control */
#define REG_EVSYS_SWEVT         (*(__O  uint32_t*)0x42000004U) /**< (EVSYS) Software Event */
#define REG_EVSYS_PRICTRL       (*(__IO uint8_t*)0x42000008U) /**< (EVSYS) Priority Control */
#define REG_EVSYS_INTPEND       (*(__IO uint16_t*)0x42000010U) /**< (EVSYS) Channel Pending Interrupt */
#define REG_EVSYS_INTSTATUS     (*(__I  uint32_t*)0x42000014U) /**< (EVSYS) Interrupt Status */
#define REG_EVSYS_BUSYCH        (*(__I  uint32_t*)0x42000018U) /**< (EVSYS) Busy Channels */
#define REG_EVSYS_READYUSR      (*(__I  uint32_t*)0x4200001CU) /**< (EVSYS) Ready Users */
#define REG_EVSYS_USER          (*(__IO uint8_t*)0x42000120U) /**< (EVSYS) User Multiplexer n */
#define REG_EVSYS_USER0         (*(__IO uint8_t*)0x42000120U) /**< (EVSYS) User Multiplexer 0 */
#define REG_EVSYS_USER1         (*(__IO uint8_t*)0x42000121U) /**< (EVSYS) User Multiplexer 1 */
#define REG_EVSYS_USER2         (*(__IO uint8_t*)0x42000122U) /**< (EVSYS) User Multiplexer 2 */
#define REG_EVSYS_USER3         (*(__IO uint8_t*)0x42000123U) /**< (EVSYS) User Multiplexer 3 */
#define REG_EVSYS_USER4         (*(__IO uint8_t*)0x42000124U) /**< (EVSYS) User Multiplexer 4 */
#define REG_EVSYS_USER5         (*(__IO uint8_t*)0x42000125U) /**< (EVSYS) User Multiplexer 5 */
#define REG_EVSYS_USER6         (*(__IO uint8_t*)0x42000126U) /**< (EVSYS) User Multiplexer 6 */
#define REG_EVSYS_USER7         (*(__IO uint8_t*)0x42000127U) /**< (EVSYS) User Multiplexer 7 */
#define REG_EVSYS_USER8         (*(__IO uint8_t*)0x42000128U) /**< (EVSYS) User Multiplexer 8 */
#define REG_EVSYS_USER9         (*(__IO uint8_t*)0x42000129U) /**< (EVSYS) User Multiplexer 9 */
#define REG_EVSYS_USER10        (*(__IO uint8_t*)0x4200012AU) /**< (EVSYS) User Multiplexer 10 */
#define REG_EVSYS_USER11        (*(__IO uint8_t*)0x4200012BU) /**< (EVSYS) User Multiplexer 11 */
#define REG_EVSYS_USER12        (*(__IO uint8_t*)0x4200012CU) /**< (EVSYS) User Multiplexer 12 */
#define REG_EVSYS_USER13        (*(__IO uint8_t*)0x4200012DU) /**< (EVSYS) User Multiplexer 13 */
#define REG_EVSYS_USER14        (*(__IO uint8_t*)0x4200012EU) /**< (EVSYS) User Multiplexer 14 */
#define REG_EVSYS_USER15        (*(__IO uint8_t*)0x4200012FU) /**< (EVSYS) User Multiplexer 15 */
#define REG_EVSYS_USER16        (*(__IO uint8_t*)0x42000130U) /**< (EVSYS) User Multiplexer 16 */
#define REG_EVSYS_USER17        (*(__IO uint8_t*)0x42000131U) /**< (EVSYS) User Multiplexer 17 */
#define REG_EVSYS_USER18        (*(__IO uint8_t*)0x42000132U) /**< (EVSYS) User Multiplexer 18 */
#define REG_EVSYS_USER19        (*(__IO uint8_t*)0x42000133U) /**< (EVSYS) User Multiplexer 19 */
#define REG_EVSYS_USER20        (*(__IO uint8_t*)0x42000134U) /**< (EVSYS) User Multiplexer 20 */
#define REG_EVSYS_USER21        (*(__IO uint8_t*)0x42000135U) /**< (EVSYS) User Multiplexer 21 */
#define REG_EVSYS_USER22        (*(__IO uint8_t*)0x42000136U) /**< (EVSYS) User Multiplexer 22 */
#define REG_EVSYS_INTENCLR      (*(__IO uint8_t*)0x420001D4U) /**< (EVSYS) Interrupt Enable Clear */
#define REG_EVSYS_INTENSET      (*(__IO uint8_t*)0x420001D5U) /**< (EVSYS) Interrupt Enable Set */
#define REG_EVSYS_INTFLAG       (*(__IO uint8_t*)0x420001D6U) /**< (EVSYS) Interrupt Flag Status and Clear */
#define REG_EVSYS_NONSECCHAN    (*(__IO uint32_t*)0x420001D8U) /**< (EVSYS) Channels Security Attribution */
#define REG_EVSYS_NSCHKCHAN     (*(__IO uint32_t*)0x420001DCU) /**< (EVSYS) Non-Secure Channels Check */
#define REG_EVSYS_NONSECUSER    (*(__IO uint32_t*)0x420001E0U) /**< (EVSYS) Users Security Attribution */
#define REG_EVSYS_NONSECUSER0   (*(__IO uint32_t*)0x420001E0U) /**< (EVSYS) Users Security Attribution 0 */
#define REG_EVSYS_NSCHKUSER     (*(__IO uint32_t*)0x420001F0U) /**< (EVSYS) Non-Secure Users Check */
#define REG_EVSYS_NSCHKUSER0    (*(__IO uint32_t*)0x420001F0U) /**< (EVSYS) Non-Secure Users Check 0 */

#endif /* (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for EVSYS peripheral ========== */
#define EVSYS_ASYNCHRONOUS_CHANNELS              0x000000F0 /* Mask of Only Asynchronous Channels */
#define EVSYS_CHANNELS                           8          /* Number of Channels */
#define EVSYS_CHANNELS_BITS                      3          /* Number of bits to select Channel */
#define EVSYS_GCLK_ID_0                          6          /* Index of Generic Clock 0 */
#define EVSYS_GCLK_ID_1                          7          /* Index of Generic Clock 1 */
#define EVSYS_GCLK_ID_2                          8          /* Index of Generic Clock 2 */
#define EVSYS_GCLK_ID_3                          9          /* Index of Generic Clock 3 */
#define EVSYS_GENERATORS                         49         /* Total Number of Event Generators */
#define EVSYS_GENERATORS_BITS                    6          /* Number of bits to select Event Generator */
#define EVSYS_SECURE_IMPLEMENTED                 1          /* Secure Channels/Users supported? */
#define EVSYS_SYNCH_NUM                          4          /* Number of Synchronous Channels */
#define EVSYS_SYNCH_NUM_BITS                     2          /* Number of bits to select Synchronous Channels */
#define EVSYS_USERS                              23         /* Total Number of Event Users */
#define EVSYS_USERS_BITS                         5          /* Number of bits to select Event User */
#define EVSYS_USERS_GROUPS                       1          /* Number of 32-user groups */
#define EVSYS_INSTANCE_ID                        64         

#endif /* _SAML10_EVSYS_INSTANCE_ */
