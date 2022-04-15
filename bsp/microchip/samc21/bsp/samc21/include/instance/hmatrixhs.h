/**
 * \file
 *
 * \brief Instance description for HMATRIXHS
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

#ifndef _SAMC21_HMATRIXHS_INSTANCE_
#define _SAMC21_HMATRIXHS_INSTANCE_

/* ========== Register definition for HMATRIXHS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_HMATRIXHS_MCFG0        (0x4100A000) /**< \brief (HMATRIXHS) Master Configuration 0 */
#define REG_HMATRIXHS_MCFG1        (0x4100A004) /**< \brief (HMATRIXHS) Master Configuration 1 */
#define REG_HMATRIXHS_MCFG2        (0x4100A008) /**< \brief (HMATRIXHS) Master Configuration 2 */
#define REG_HMATRIXHS_MCFG3        (0x4100A00C) /**< \brief (HMATRIXHS) Master Configuration 3 */
#define REG_HMATRIXHS_MCFG4        (0x4100A010) /**< \brief (HMATRIXHS) Master Configuration 4 */
#define REG_HMATRIXHS_MCFG5        (0x4100A014) /**< \brief (HMATRIXHS) Master Configuration 5 */
#define REG_HMATRIXHS_MCFG6        (0x4100A018) /**< \brief (HMATRIXHS) Master Configuration 6 */
#define REG_HMATRIXHS_MCFG7        (0x4100A01C) /**< \brief (HMATRIXHS) Master Configuration 7 */
#define REG_HMATRIXHS_MCFG8        (0x4100A020) /**< \brief (HMATRIXHS) Master Configuration 8 */
#define REG_HMATRIXHS_MCFG9        (0x4100A024) /**< \brief (HMATRIXHS) Master Configuration 9 */
#define REG_HMATRIXHS_MCFG10       (0x4100A028) /**< \brief (HMATRIXHS) Master Configuration 10 */
#define REG_HMATRIXHS_MCFG11       (0x4100A02C) /**< \brief (HMATRIXHS) Master Configuration 11 */
#define REG_HMATRIXHS_MCFG12       (0x4100A030) /**< \brief (HMATRIXHS) Master Configuration 12 */
#define REG_HMATRIXHS_MCFG13       (0x4100A034) /**< \brief (HMATRIXHS) Master Configuration 13 */
#define REG_HMATRIXHS_MCFG14       (0x4100A038) /**< \brief (HMATRIXHS) Master Configuration 14 */
#define REG_HMATRIXHS_MCFG15       (0x4100A03C) /**< \brief (HMATRIXHS) Master Configuration 15 */
#define REG_HMATRIXHS_SCFG0        (0x4100A040) /**< \brief (HMATRIXHS) Slave Configuration 0 */
#define REG_HMATRIXHS_SCFG1        (0x4100A044) /**< \brief (HMATRIXHS) Slave Configuration 1 */
#define REG_HMATRIXHS_SCFG2        (0x4100A048) /**< \brief (HMATRIXHS) Slave Configuration 2 */
#define REG_HMATRIXHS_SCFG3        (0x4100A04C) /**< \brief (HMATRIXHS) Slave Configuration 3 */
#define REG_HMATRIXHS_SCFG4        (0x4100A050) /**< \brief (HMATRIXHS) Slave Configuration 4 */
#define REG_HMATRIXHS_SCFG5        (0x4100A054) /**< \brief (HMATRIXHS) Slave Configuration 5 */
#define REG_HMATRIXHS_SCFG6        (0x4100A058) /**< \brief (HMATRIXHS) Slave Configuration 6 */
#define REG_HMATRIXHS_SCFG7        (0x4100A05C) /**< \brief (HMATRIXHS) Slave Configuration 7 */
#define REG_HMATRIXHS_SCFG8        (0x4100A060) /**< \brief (HMATRIXHS) Slave Configuration 8 */
#define REG_HMATRIXHS_SCFG9        (0x4100A064) /**< \brief (HMATRIXHS) Slave Configuration 9 */
#define REG_HMATRIXHS_SCFG10       (0x4100A068) /**< \brief (HMATRIXHS) Slave Configuration 10 */
#define REG_HMATRIXHS_SCFG11       (0x4100A06C) /**< \brief (HMATRIXHS) Slave Configuration 11 */
#define REG_HMATRIXHS_SCFG12       (0x4100A070) /**< \brief (HMATRIXHS) Slave Configuration 12 */
#define REG_HMATRIXHS_SCFG13       (0x4100A074) /**< \brief (HMATRIXHS) Slave Configuration 13 */
#define REG_HMATRIXHS_SCFG14       (0x4100A078) /**< \brief (HMATRIXHS) Slave Configuration 14 */
#define REG_HMATRIXHS_SCFG15       (0x4100A07C) /**< \brief (HMATRIXHS) Slave Configuration 15 */
#define REG_HMATRIXHS_PRAS0        (0x4100A080) /**< \brief (HMATRIXHS) Priority A for Slave 0 */
#define REG_HMATRIXHS_PRBS0        (0x4100A084) /**< \brief (HMATRIXHS) Priority B for Slave 0 */
#define REG_HMATRIXHS_PRAS1        (0x4100A088) /**< \brief (HMATRIXHS) Priority A for Slave 1 */
#define REG_HMATRIXHS_PRBS1        (0x4100A08C) /**< \brief (HMATRIXHS) Priority B for Slave 1 */
#define REG_HMATRIXHS_PRAS2        (0x4100A090) /**< \brief (HMATRIXHS) Priority A for Slave 2 */
#define REG_HMATRIXHS_PRBS2        (0x4100A094) /**< \brief (HMATRIXHS) Priority B for Slave 2 */
#define REG_HMATRIXHS_PRAS3        (0x4100A098) /**< \brief (HMATRIXHS) Priority A for Slave 3 */
#define REG_HMATRIXHS_PRBS3        (0x4100A09C) /**< \brief (HMATRIXHS) Priority B for Slave 3 */
#define REG_HMATRIXHS_MRCR         (0x4100A100) /**< \brief (HMATRIXHS) Master Remap Control */
#define REG_HMATRIXHS_SFR0         (0x4100A110) /**< \brief (HMATRIXHS) Special Function 0 */
#define REG_HMATRIXHS_SFR1         (0x4100A114) /**< \brief (HMATRIXHS) Special Function 1 */
#define REG_HMATRIXHS_SFR2         (0x4100A118) /**< \brief (HMATRIXHS) Special Function 2 */
#define REG_HMATRIXHS_SFR3         (0x4100A11C) /**< \brief (HMATRIXHS) Special Function 3 */
#define REG_HMATRIXHS_SFR4         (0x4100A120) /**< \brief (HMATRIXHS) Special Function 4 */
#define REG_HMATRIXHS_SFR5         (0x4100A124) /**< \brief (HMATRIXHS) Special Function 5 */
#define REG_HMATRIXHS_SFR6         (0x4100A128) /**< \brief (HMATRIXHS) Special Function 6 */
#define REG_HMATRIXHS_SFR7         (0x4100A12C) /**< \brief (HMATRIXHS) Special Function 7 */
#define REG_HMATRIXHS_SFR8         (0x4100A130) /**< \brief (HMATRIXHS) Special Function 8 */
#define REG_HMATRIXHS_SFR9         (0x4100A134) /**< \brief (HMATRIXHS) Special Function 9 */
#define REG_HMATRIXHS_SFR10        (0x4100A138) /**< \brief (HMATRIXHS) Special Function 10 */
#define REG_HMATRIXHS_SFR11        (0x4100A13C) /**< \brief (HMATRIXHS) Special Function 11 */
#define REG_HMATRIXHS_SFR12        (0x4100A140) /**< \brief (HMATRIXHS) Special Function 12 */
#define REG_HMATRIXHS_SFR13        (0x4100A144) /**< \brief (HMATRIXHS) Special Function 13 */
#define REG_HMATRIXHS_SFR14        (0x4100A148) /**< \brief (HMATRIXHS) Special Function 14 */
#define REG_HMATRIXHS_SFR15        (0x4100A14C) /**< \brief (HMATRIXHS) Special Function 15 */
#else
#define REG_HMATRIXHS_MCFG0        (*(RwReg  *)0x4100A000UL) /**< \brief (HMATRIXHS) Master Configuration 0 */
#define REG_HMATRIXHS_MCFG1        (*(RwReg  *)0x4100A004UL) /**< \brief (HMATRIXHS) Master Configuration 1 */
#define REG_HMATRIXHS_MCFG2        (*(RwReg  *)0x4100A008UL) /**< \brief (HMATRIXHS) Master Configuration 2 */
#define REG_HMATRIXHS_MCFG3        (*(RwReg  *)0x4100A00CUL) /**< \brief (HMATRIXHS) Master Configuration 3 */
#define REG_HMATRIXHS_MCFG4        (*(RwReg  *)0x4100A010UL) /**< \brief (HMATRIXHS) Master Configuration 4 */
#define REG_HMATRIXHS_MCFG5        (*(RwReg  *)0x4100A014UL) /**< \brief (HMATRIXHS) Master Configuration 5 */
#define REG_HMATRIXHS_MCFG6        (*(RwReg  *)0x4100A018UL) /**< \brief (HMATRIXHS) Master Configuration 6 */
#define REG_HMATRIXHS_MCFG7        (*(RwReg  *)0x4100A01CUL) /**< \brief (HMATRIXHS) Master Configuration 7 */
#define REG_HMATRIXHS_MCFG8        (*(RwReg  *)0x4100A020UL) /**< \brief (HMATRIXHS) Master Configuration 8 */
#define REG_HMATRIXHS_MCFG9        (*(RwReg  *)0x4100A024UL) /**< \brief (HMATRIXHS) Master Configuration 9 */
#define REG_HMATRIXHS_MCFG10       (*(RwReg  *)0x4100A028UL) /**< \brief (HMATRIXHS) Master Configuration 10 */
#define REG_HMATRIXHS_MCFG11       (*(RwReg  *)0x4100A02CUL) /**< \brief (HMATRIXHS) Master Configuration 11 */
#define REG_HMATRIXHS_MCFG12       (*(RwReg  *)0x4100A030UL) /**< \brief (HMATRIXHS) Master Configuration 12 */
#define REG_HMATRIXHS_MCFG13       (*(RwReg  *)0x4100A034UL) /**< \brief (HMATRIXHS) Master Configuration 13 */
#define REG_HMATRIXHS_MCFG14       (*(RwReg  *)0x4100A038UL) /**< \brief (HMATRIXHS) Master Configuration 14 */
#define REG_HMATRIXHS_MCFG15       (*(RwReg  *)0x4100A03CUL) /**< \brief (HMATRIXHS) Master Configuration 15 */
#define REG_HMATRIXHS_SCFG0        (*(RwReg  *)0x4100A040UL) /**< \brief (HMATRIXHS) Slave Configuration 0 */
#define REG_HMATRIXHS_SCFG1        (*(RwReg  *)0x4100A044UL) /**< \brief (HMATRIXHS) Slave Configuration 1 */
#define REG_HMATRIXHS_SCFG2        (*(RwReg  *)0x4100A048UL) /**< \brief (HMATRIXHS) Slave Configuration 2 */
#define REG_HMATRIXHS_SCFG3        (*(RwReg  *)0x4100A04CUL) /**< \brief (HMATRIXHS) Slave Configuration 3 */
#define REG_HMATRIXHS_SCFG4        (*(RwReg  *)0x4100A050UL) /**< \brief (HMATRIXHS) Slave Configuration 4 */
#define REG_HMATRIXHS_SCFG5        (*(RwReg  *)0x4100A054UL) /**< \brief (HMATRIXHS) Slave Configuration 5 */
#define REG_HMATRIXHS_SCFG6        (*(RwReg  *)0x4100A058UL) /**< \brief (HMATRIXHS) Slave Configuration 6 */
#define REG_HMATRIXHS_SCFG7        (*(RwReg  *)0x4100A05CUL) /**< \brief (HMATRIXHS) Slave Configuration 7 */
#define REG_HMATRIXHS_SCFG8        (*(RwReg  *)0x4100A060UL) /**< \brief (HMATRIXHS) Slave Configuration 8 */
#define REG_HMATRIXHS_SCFG9        (*(RwReg  *)0x4100A064UL) /**< \brief (HMATRIXHS) Slave Configuration 9 */
#define REG_HMATRIXHS_SCFG10       (*(RwReg  *)0x4100A068UL) /**< \brief (HMATRIXHS) Slave Configuration 10 */
#define REG_HMATRIXHS_SCFG11       (*(RwReg  *)0x4100A06CUL) /**< \brief (HMATRIXHS) Slave Configuration 11 */
#define REG_HMATRIXHS_SCFG12       (*(RwReg  *)0x4100A070UL) /**< \brief (HMATRIXHS) Slave Configuration 12 */
#define REG_HMATRIXHS_SCFG13       (*(RwReg  *)0x4100A074UL) /**< \brief (HMATRIXHS) Slave Configuration 13 */
#define REG_HMATRIXHS_SCFG14       (*(RwReg  *)0x4100A078UL) /**< \brief (HMATRIXHS) Slave Configuration 14 */
#define REG_HMATRIXHS_SCFG15       (*(RwReg  *)0x4100A07CUL) /**< \brief (HMATRIXHS) Slave Configuration 15 */
#define REG_HMATRIXHS_PRAS0        (*(RwReg  *)0x4100A080UL) /**< \brief (HMATRIXHS) Priority A for Slave 0 */
#define REG_HMATRIXHS_PRBS0        (*(RwReg  *)0x4100A084UL) /**< \brief (HMATRIXHS) Priority B for Slave 0 */
#define REG_HMATRIXHS_PRAS1        (*(RwReg  *)0x4100A088UL) /**< \brief (HMATRIXHS) Priority A for Slave 1 */
#define REG_HMATRIXHS_PRBS1        (*(RwReg  *)0x4100A08CUL) /**< \brief (HMATRIXHS) Priority B for Slave 1 */
#define REG_HMATRIXHS_PRAS2        (*(RwReg  *)0x4100A090UL) /**< \brief (HMATRIXHS) Priority A for Slave 2 */
#define REG_HMATRIXHS_PRBS2        (*(RwReg  *)0x4100A094UL) /**< \brief (HMATRIXHS) Priority B for Slave 2 */
#define REG_HMATRIXHS_PRAS3        (*(RwReg  *)0x4100A098UL) /**< \brief (HMATRIXHS) Priority A for Slave 3 */
#define REG_HMATRIXHS_PRBS3        (*(RwReg  *)0x4100A09CUL) /**< \brief (HMATRIXHS) Priority B for Slave 3 */
#define REG_HMATRIXHS_MRCR         (*(RwReg  *)0x4100A100UL) /**< \brief (HMATRIXHS) Master Remap Control */
#define REG_HMATRIXHS_SFR0         (*(RwReg  *)0x4100A110UL) /**< \brief (HMATRIXHS) Special Function 0 */
#define REG_HMATRIXHS_SFR1         (*(RwReg  *)0x4100A114UL) /**< \brief (HMATRIXHS) Special Function 1 */
#define REG_HMATRIXHS_SFR2         (*(RwReg  *)0x4100A118UL) /**< \brief (HMATRIXHS) Special Function 2 */
#define REG_HMATRIXHS_SFR3         (*(RwReg  *)0x4100A11CUL) /**< \brief (HMATRIXHS) Special Function 3 */
#define REG_HMATRIXHS_SFR4         (*(RwReg  *)0x4100A120UL) /**< \brief (HMATRIXHS) Special Function 4 */
#define REG_HMATRIXHS_SFR5         (*(RwReg  *)0x4100A124UL) /**< \brief (HMATRIXHS) Special Function 5 */
#define REG_HMATRIXHS_SFR6         (*(RwReg  *)0x4100A128UL) /**< \brief (HMATRIXHS) Special Function 6 */
#define REG_HMATRIXHS_SFR7         (*(RwReg  *)0x4100A12CUL) /**< \brief (HMATRIXHS) Special Function 7 */
#define REG_HMATRIXHS_SFR8         (*(RwReg  *)0x4100A130UL) /**< \brief (HMATRIXHS) Special Function 8 */
#define REG_HMATRIXHS_SFR9         (*(RwReg  *)0x4100A134UL) /**< \brief (HMATRIXHS) Special Function 9 */
#define REG_HMATRIXHS_SFR10        (*(RwReg  *)0x4100A138UL) /**< \brief (HMATRIXHS) Special Function 10 */
#define REG_HMATRIXHS_SFR11        (*(RwReg  *)0x4100A13CUL) /**< \brief (HMATRIXHS) Special Function 11 */
#define REG_HMATRIXHS_SFR12        (*(RwReg  *)0x4100A140UL) /**< \brief (HMATRIXHS) Special Function 12 */
#define REG_HMATRIXHS_SFR13        (*(RwReg  *)0x4100A144UL) /**< \brief (HMATRIXHS) Special Function 13 */
#define REG_HMATRIXHS_SFR14        (*(RwReg  *)0x4100A148UL) /**< \brief (HMATRIXHS) Special Function 14 */
#define REG_HMATRIXHS_SFR15        (*(RwReg  *)0x4100A14CUL) /**< \brief (HMATRIXHS) Special Function 15 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for HMATRIXHS peripheral ========== */
#define HMATRIXHS_CLK_AHB_ID        4        // Index of AHB Clock in MCLK.AHBMASK register (MASK may be tied to 1 depending on chip integration)
#define HMATRIXHS_DEFINED                   

#endif /* _SAMC21_HMATRIXHS_INSTANCE_ */
