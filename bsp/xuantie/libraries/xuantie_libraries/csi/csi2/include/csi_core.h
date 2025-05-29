 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/******************************************************************************
 * @file     csi_core.h
 * @brief    CSI Core Layer Header File
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CORE_H_
#define _CORE_H_

#include <stdint.h>

#if defined(__csky__)

#if defined(__CK801__) || defined(__E801__)
#include <core/core_801.h>
#elif defined(__CK802__) || defined(__E802__) || defined(__E802T__) || defined(__S802__) || defined(__S802T__)
#include <core/core_802.h>
#elif defined(__CK804__) || defined(__E804D__) || defined(__E804DT__) || defined(__E804F__)  || defined(__E804FT__) || defined (__E804DF__) || defined(__E804DFT__)
#include <core/core_804.h>
#elif defined(__CK803__) || defined(__E803__) || defined(__E803T__) || defined(__S803__) || defined(__S803T__)
#include <core/core_803.h>
#elif defined(__CK805__) || defined(__I805__) || defined(__I805F__)
#include <core/core_805.h>
#elif defined(__CK610__)
#include <core/core_ck610.h>
#elif defined(__CK810__) || defined(__C810__) || defined(__C810T__) || defined(__C810V__) || defined(__C810VT__)
#include <core/core_810.h>
#elif defined(__CK807__) || defined(__C807__) || defined(__C807F__) || defined(__C807FV__) || defined(__R807__)
#include <core/core_807.h>
#endif
#include <core/csi_gcc.h>

#elif defined(__riscv)

#if CONFIG_CPU_XUANTIE_E906 || CONFIG_CPU_XUANTIE_E906F || CONFIG_CPU_XUANTIE_E906FD || CONFIG_CPU_XUANTIE_E906P || CONFIG_CPU_XUANTIE_E906FP || CONFIG_CPU_XUANTIE_E906FDP \
    || CONFIG_CPU_XUANTIE_E907 || CONFIG_CPU_XUANTIE_E907F || CONFIG_CPU_XUANTIE_E907FD || CONFIG_CPU_XUANTIE_E907P || CONFIG_CPU_XUANTIE_E907FP || CONFIG_CPU_XUANTIE_E907FDP \
    || CONFIG_CPU_XUANTIE_E902 || CONFIG_CPU_XUANTIE_E902M || CONFIG_CPU_XUANTIE_E902T || CONFIG_CPU_XUANTIE_E902MT
#include <core/core_rv32.h>
#include <core/csi_rv32_gcc.h>
#else
#include <core/core_rv64.h>
#include <core/csi_rv64_gcc.h>
#endif /* end exx */

#endif /* __csky__ */

#ifdef __arm__
#include <csi_core_cmsis.h>
#endif

#ifdef __ARM_ARCH_ISA_A64
#include <core/csi_arm64_gcc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_CPU_XUANTIE_E9XX || CONFIG_CPU_XUANTIE_C906 || CONFIG_CPU_XUANTIE_C906FD || CONFIG_CPU_XUANTIE_C906FDV
#if CONFIG_SMP
#error "This CPU does not support SMP."
#endif
#endif

__STATIC_INLINE const char* csi_get_cpu_name()
{
#if CONFIG_CPU_XUANTIE_C906
	return "c906";
#elif CONFIG_CPU_XUANTIE_C906FD
	return "c906fd";
#elif CONFIG_CPU_XUANTIE_C906FDV
	return "c906fdv";
#elif CONFIG_CPU_XUANTIE_C907
	return "c907";
#elif CONFIG_CPU_XUANTIE_C907FD
	return "c907fd";
#elif CONFIG_CPU_XUANTIE_C907FDV
	return "c907fdv";
#elif CONFIG_CPU_XUANTIE_C907FDVM
	return "c907fdvm";
#elif CONFIG_CPU_XUANTIE_C907_RV32
	return "c907-rv32";
#elif CONFIG_CPU_XUANTIE_C907FD_RV32
	return "c907fd-rv32";
#elif CONFIG_CPU_XUANTIE_C907FDV_RV32
	return "c907fdv-rv32";
#elif CONFIG_CPU_XUANTIE_C907FDVM_RV32
	return "c907fdvm-rv32";
#elif CONFIG_CPU_XUANTIE_C908
	return "c908";
#elif CONFIG_CPU_XUANTIE_C908V
	return "c908v";
#elif CONFIG_CPU_XUANTIE_C908I
	return "c908i";
#elif CONFIG_CPU_XUANTIE_C910V2
	return "c910v2";
#elif CONFIG_CPU_XUANTIE_C910V3
	return "c910v3";
#elif CONFIG_CPU_XUANTIE_C910V3_CP
	return "c910v3-cp";
#elif CONFIG_CPU_XUANTIE_C920V2
	return "c920v2";
#elif CONFIG_CPU_XUANTIE_C920V3
	return "c920v3";
#elif CONFIG_CPU_XUANTIE_C920V3_CP
	return "c920v3-cp";
#elif CONFIG_CPU_XUANTIE_R910
	return "r910";
#elif CONFIG_CPU_XUANTIE_R920
	return "r920";
#elif CONFIG_CPU_XUANTIE_R908
	return "r908";
#elif CONFIG_CPU_XUANTIE_R908FD
	return "r908fd";
#elif CONFIG_CPU_XUANTIE_R908FDV
	return "r908fdv";
#elif CONFIG_CPU_XUANTIE_R908_CP
	return "r908-cp";
#elif CONFIG_CPU_XUANTIE_R908FD_CP
	return "r908fd-cp";
#elif CONFIG_CPU_XUANTIE_R908FDV_CP
	return "r908fdv-cp";

#elif CONFIG_CPU_XUANTIE_E902
	return "e902";
#elif CONFIG_CPU_XUANTIE_E902M
	return "e902m";
#elif CONFIG_CPU_XUANTIE_E902T
	return "e902t";
#elif CONFIG_CPU_XUANTIE_E902MT
	return "e902mt";
#elif CONFIG_CPU_XUANTIE_E906
	return "e906";
#elif CONFIG_CPU_XUANTIE_E906F
	return "e906f";
#elif CONFIG_CPU_XUANTIE_E906FD
	return "e906fd";
#elif CONFIG_CPU_XUANTIE_E906P
	return "e906p";
#elif CONFIG_CPU_XUANTIE_E906FP
	return "e906fp";
#elif CONFIG_CPU_XUANTIE_E906FDP
	return "e906fdp";
#elif CONFIG_CPU_XUANTIE_E907
	return "e907";
#elif CONFIG_CPU_XUANTIE_E907F
	return "e907f";
#elif CONFIG_CPU_XUANTIE_E907FD
	return "e907fd";
#elif CONFIG_CPU_XUANTIE_E907P
	return "e907p";
#elif CONFIG_CPU_XUANTIE_E907FP
	return "e907fp";
#elif CONFIG_CPU_XUANTIE_E907FDP
	return "e907fdp";
#else
	return "unknown";
#endif
}


#ifdef __cplusplus
}
#endif

#endif /* _CORE_H_ */
