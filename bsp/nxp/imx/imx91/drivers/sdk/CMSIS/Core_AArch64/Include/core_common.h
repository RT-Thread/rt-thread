/**************************************************************************//**
 * @file     core_common.h
 * @brief    CMSIS Cortex-A AArch64 Core Common Header File
 * @version  V1.0.0
 * @date     06. Feb 2023
 ******************************************************************************/
/*
 * Copyright (c) 2021 Arm Limited. All rights reserved.
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if   defined ( __ICCARM__ )
 #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CORE_COMMON_H
#define __CORE_COMMON_H

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 Register Definitions
 ******************************************************************************/

#ifndef BIT
#define BIT(n) (1 << (n))
#endif

/* DAIF Register */
#define DAIF_F_BIT                BIT(6)
#define DAIF_I_BIT                BIT(7)
#define DAIF_A_BIT                BIT(8)
#define DAIF_D_BIT                BIT(9)

/* System Control Register */
#define SCTLR_M_BIT               BIT(0)
#define SCTLR_A_BIT               BIT(1)
#define SCTLR_C_BIT               BIT(2)
#define SCTLR_SA_BIT              BIT(3)
#define SCTLR_I_BIT               BIT(12)

/* Exception levels EL0-EL3 */
#define MODE_EL_SHIFT		(0x2)
#define MODE_EL_MASK		(0x3)

#define MODE_EL3		(0x3)
#define MODE_EL2		(0x2)
#define MODE_EL1		(0x1)
#define MODE_EL0		(0x0)

#define GET_EL(_mode)		(((_mode) >> MODE_EL_SHIFT) & MODE_EL_MASK)

/* MPIDR */
#define MPIDR_AFFLVL_MASK	(0xffULL)
#define MPIDR_AFF0_SHIFT	(0)
#define MPIDR_AFF1_SHIFT	(8)
#define MPIDR_AFF2_SHIFT	(16)
#define MPIDR_AFF3_SHIFT	(32)
#define MPIDR_MT_MASK		(0x1)
#define MPIDR_MT_SHIFT		(24)

#define MPIDR_SUPPORT_MT(mpidr)	((mpidr >> MPIDR_MT_SHIFT) & MPIDR_MT_MASK)


#define MPIDR_TO_AFF_LEVEL(mpidr, aff_level) \
	(((mpidr) >> MPIDR_AFF##aff_level##_SHIFT) & MPIDR_AFFLVL_MASK)

#define MPIDR_AFFINITY_MASK				\
	((MPIDR_AFFLVL_MASK << MPIDR_AFF3_SHIFT) |	\
	(MPIDR_AFFLVL_MASK << MPIDR_AFF2_SHIFT)  |	\
	(MPIDR_AFFLVL_MASK << MPIDR_AFF1_SHIFT)  |	\
	(MPIDR_AFFLVL_MASK << MPIDR_AFF0_SHIFT))

/*******************************************************************************
 *                 Cache Functions
 ******************************************************************************/

#if defined (__CACHE_PRESENT) && (__CACHE_PRESENT == 1U)

  #include "cache_armv8a.h"

#endif


/*******************************************************************************
 *                 GIC Functions
 ******************************************************************************/

#if defined (__GIC_PRESENT) && (__GIC_PRESENT == 1U)

  #include "gic_v3.h"

#endif


/*******************************************************************************
 *                 MMU Functions
 ******************************************************************************/

#if defined (__MMU_PRESENT) && (__MMU_PRESENT == 1U)

  #include "mmu_armv8a.h"

#endif


/*******************************************************************************
 *                 Timer Functions
 ******************************************************************************/

#if defined (__TIM_PRESENT) && (__TIM_PRESENT == 1U)
  #include "timer_armv8a.h"
#endif


#ifdef __cplusplus
}
#endif

#endif /* __CORE_COMMON_H */
