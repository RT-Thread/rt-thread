/* Copyright (c) 2009 - 2015 ARM LIMITED
   Copyright (c) 2016, Freescale Semiconductor, Inc.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#if   defined ( __ICCARM__ )
 #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CORE_CA7_H_GENERIC
#define __CORE_CA7_H_GENERIC

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__GNUC__)
  #define FORCEDINLINE  __attribute__((always_inline))
#else
  #define FORCEDINLINE
#endif

#if   defined ( __CC_ARM )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#elif defined ( __GNUC__ )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __ICCARM__ )
  #define __ASM            __asm                                      /*!< asm keyword for IAR Compiler */
  #define __INLINE         inline                                     /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
  #define __STATIC_INLINE  static inline

#elif defined ( __TMS470__ )
  #define __ASM            __asm                                      /*!< asm keyword for TI CCS Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __TASKING__ )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler */
  #define __STATIC_INLINE  static inline

#elif defined ( __CSMC__ )
  #define __packed
  #define __ASM            _asm                                      /*!< asm keyword for COSMIC Compiler */
  #define __INLINE         inline                                    /*!< inline keyword for COSMIC Compiler. Use -pc99 on compile line */
  #define __STATIC_INLINE  static inline

#else
  #error Unknown compiler
#endif

/** __FPU_USED indicates whether an FPU is used or not.
    For this, __FPU_PRESENT has to be checked prior to making use of FPU specific registers and functions.
*/
#if defined ( __CC_ARM )
  #if defined __TARGET_FPU_VFP
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if defined __ARM_PCS_VFP
    #if (__FPU_PRESENT == 1)
      #define __FPU_USED       1U
    #else
      #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TMS470__ )
  #if defined __TI_VFP_SUPPORT__
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __TASKING__ )
  #if defined __FPU_VFP__
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#elif defined ( __CSMC__ )
  #if ( __CSMC__ & 0x400U)
    #if (__FPU_PRESENT == 1U)
      #define __FPU_USED       1U
    #else
      #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
      #define __FPU_USED       0U
    #endif
  #else
    #define __FPU_USED         0U
  #endif

#endif

#include "core_ca.h"                /* Core Instruction and Function Access */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CA7_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_CA7_H_DEPENDANT
#define __CORE_CA7_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */


/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - CPSR
  - CP15 Registers
 ******************************************************************************/

/* Core Register CPSR */
typedef union
{
  struct
  {
    uint32_t M:5;                        /*!< bit:  0.. 4  Mode field */
    uint32_t T:1;                        /*!< bit:      5  Thumb execution state bit */
    uint32_t F:1;                        /*!< bit:      6  FIQ mask bit */
    uint32_t I:1;                        /*!< bit:      7  IRQ mask bit */
    uint32_t A:1;                        /*!< bit:      8  Asynchronous abort mask bit */
    uint32_t E:1;                        /*!< bit:      9  Endianness execution state bit */
    uint32_t IT1:6;                      /*!< bit: 10..15  If-Then execution state bits 2-7 */
    uint32_t GE:4;                       /*!< bit: 16..19  Greater than or Equal flags */
    uint32_t _reserved0:4;               /*!< bit: 20..23  Reserved */
    uint32_t J:1;                        /*!< bit:     24  Jazelle bit */
    uint32_t IT0:2;                      /*!< bit: 25..26  If-Then execution state bits 0-1 */
    uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
    uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
    uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
    uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
    uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} CPSR_Type;

/* CPSR Register Definitions */
#define CPSR_N_Pos                       31U                                    /*!< CPSR: N Position */
#define CPSR_N_Msk                       (1UL << CPSR_N_Pos)                    /*!< CPSR: N Mask */

#define CPSR_Z_Pos                       30U                                    /*!< CPSR: Z Position */
#define CPSR_Z_Msk                       (1UL << CPSR_Z_Pos)                    /*!< CPSR: Z Mask */

#define CPSR_C_Pos                       29U                                    /*!< CPSR: C Position */
#define CPSR_C_Msk                       (1UL << CPSR_C_Pos)                    /*!< CPSR: C Mask */

#define CPSR_V_Pos                       28U                                    /*!< CPSR: V Position */
#define CPSR_V_Msk                       (1UL << CPSR_V_Pos)                    /*!< CPSR: V Mask */

#define CPSR_Q_Pos                       27U                                    /*!< CPSR: Q Position */
#define CPSR_Q_Msk                       (1UL << CPSR_Q_Pos)                    /*!< CPSR: Q Mask */

#define CPSR_IT0_Pos                     25U                                    /*!< CPSR: IT0 Position */
#define CPSR_IT0_Msk                     (3UL << CPSR_IT0_Pos)                  /*!< CPSR: IT0 Mask */

#define CPSR_J_Pos                       24U                                    /*!< CPSR: J Position */
#define CPSR_J_Msk                       (1UL << CPSR_J_Pos)                    /*!< CPSR: J Mask */

#define CPSR_GE_Pos                      16U                                    /*!< CPSR: GE Position */
#define CPSR_GE_Msk                      (0xFUL << CPSR_GE_Pos)                 /*!< CPSR: GE Mask */

#define CPSR_IT1_Pos                     10U                                    /*!< CPSR: IT1 Position */
#define CPSR_IT1_Msk                     (0x3FUL << CPSR_IT1_Pos)               /*!< CPSR: IT1 Mask */

#define CPSR_E_Pos                       9U                                     /*!< CPSR: E Position */
#define CPSR_E_Msk                       (1UL << CPSR_E_Pos)                    /*!< CPSR: E Mask */

#define CPSR_A_Pos                       8U                                     /*!< CPSR: A Position */
#define CPSR_A_Msk                       (1UL << CPSR_A_Pos)                    /*!< CPSR: A Mask */

#define CPSR_I_Pos                       7U                                     /*!< CPSR: I Position */
#define CPSR_I_Msk                       (1UL << CPSR_I_Pos)                    /*!< CPSR: I Mask */

#define CPSR_F_Pos                       6U                                     /*!< CPSR: F Position */
#define CPSR_F_Msk                       (1UL << CPSR_F_Pos)                    /*!< CPSR: F Mask */

#define CPSR_T_Pos                       5U                                     /*!< CPSR: T Position */
#define CPSR_T_Msk                       (1UL << CPSR_T_Pos)                    /*!< CPSR: T Mask */

#define CPSR_M_Pos                       0U                                     /*!< CPSR: M Position */
#define CPSR_M_Msk                       (0x1FUL << CPSR_M_Pos)                 /*!< CPSR: M Mask */


/* CP15 Register SCTLR */
typedef union
{
  struct
  {
    uint32_t M:1;                        /*!< bit:     0  MMU enable */
    uint32_t A:1;                        /*!< bit:     1  Alignment check enable */
    uint32_t C:1;                        /*!< bit:     2  Cache enable */
    uint32_t _reserved0:2;               /*!< bit: 3.. 4  Reserved */
    uint32_t CP15BEN:1;                  /*!< bit:     5  CP15 barrier enable */
    uint32_t _reserved1:1;               /*!< bit:     6  Reserved */
    uint32_t B:1;                        /*!< bit:     7  Endianness model */
    uint32_t _reserved2:2;               /*!< bit: 8.. 9  Reserved */
    uint32_t SW:1;                       /*!< bit:    10  SWP and SWPB enable */
    uint32_t Z:1;                        /*!< bit:    11  Branch prediction enable */
    uint32_t I:1;                        /*!< bit:    12  Instruction cache enable */
    uint32_t V:1;                        /*!< bit:    13  Vectors bit */
    uint32_t RR:1;                       /*!< bit:    14  Round Robin select */
    uint32_t _reserved3:2;               /*!< bit:15..16  Reserved */
    uint32_t HA:1;                       /*!< bit:    17  Hardware Access flag enable */
    uint32_t _reserved4:1;               /*!< bit:    18  Reserved */
    uint32_t WXN:1;                      /*!< bit:    19  Write permission implies XN */
    uint32_t UWXN:1;                     /*!< bit:    20  Unprivileged write permission implies PL1 XN */
    uint32_t FI:1;                       /*!< bit:    21  Fast interrupts configuration enable */
    uint32_t U:1;                        /*!< bit:    22  Alignment model */
    uint32_t _reserved5:1;               /*!< bit:    23  Reserved */
    uint32_t VE:1;                       /*!< bit:    24  Interrupt Vectors Enable */
    uint32_t EE:1;                       /*!< bit:    25  Exception Endianness */
    uint32_t _reserved6:1;               /*!< bit:    26  Reserved */
    uint32_t NMFI:1;                     /*!< bit:    27  Non-maskable FIQ (NMFI) support */
    uint32_t TRE:1;                      /*!< bit:    28  TEX remap enable. */
    uint32_t AFE:1;                      /*!< bit:    29  Access flag enable */
    uint32_t TE:1;                       /*!< bit:    30  Thumb Exception enable */
    uint32_t _reserved7:1;               /*!< bit:    31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} SCTLR_Type;

#define SCTLR_TE_Pos                     30U                                    /*!< SCTLR: TE Position */
#define SCTLR_TE_Msk                     (1UL << SCTLR_TE_Pos)                  /*!< SCTLR: TE Mask */

#define SCTLR_AFE_Pos                    29U                                    /*!< SCTLR: AFE Position */
#define SCTLR_AFE_Msk                    (1UL << SCTLR_AFE_Pos)                 /*!< SCTLR: AFE Mask */

#define SCTLR_TRE_Pos                    28U                                    /*!< SCTLR: TRE Position */
#define SCTLR_TRE_Msk                    (1UL << SCTLR_TRE_Pos)                 /*!< SCTLR: TRE Mask */

#define SCTLR_NMFI_Pos                   27U                                    /*!< SCTLR: NMFI Position */
#define SCTLR_NMFI_Msk                   (1UL << SCTLR_NMFI_Pos)                /*!< SCTLR: NMFI Mask */

#define SCTLR_EE_Pos                     25U                                    /*!< SCTLR: EE Position */
#define SCTLR_EE_Msk                     (1UL << SCTLR_EE_Pos)                  /*!< SCTLR: EE Mask */

#define SCTLR_VE_Pos                     24U                                    /*!< SCTLR: VE Position */
#define SCTLR_VE_Msk                     (1UL << SCTLR_VE_Pos)                  /*!< SCTLR: VE Mask */

#define SCTLR_U_Pos                      22U                                    /*!< SCTLR: U Position */
#define SCTLR_U_Msk                      (1UL << SCTLR_U_Pos)                   /*!< SCTLR: U Mask */

#define SCTLR_FI_Pos                     21U                                    /*!< SCTLR: FI Position */
#define SCTLR_FI_Msk                     (1UL << SCTLR_FI_Pos)                  /*!< SCTLR: FI Mask */

#define SCTLR_UWXN_Pos                   20U                                    /*!< SCTLR: UWXN Position */
#define SCTLR_UWXN_Msk                   (1UL << SCTLR_UWXN_Pos)                /*!< SCTLR: UWXN Mask */

#define SCTLR_WXN_Pos                    19U                                    /*!< SCTLR: WXN Position */
#define SCTLR_WXN_Msk                    (1UL << SCTLR_WXN_Pos)                 /*!< SCTLR: WXN Mask */

#define SCTLR_HA_Pos                     17U                                    /*!< SCTLR: HA Position */
#define SCTLR_HA_Msk                     (1UL << SCTLR_HA_Pos)                  /*!< SCTLR: HA Mask */

#define SCTLR_RR_Pos                     14U                                    /*!< SCTLR: RR Position */
#define SCTLR_RR_Msk                     (1UL << SCTLR_RR_Pos)                  /*!< SCTLR: RR Mask */

#define SCTLR_V_Pos                      13U                                    /*!< SCTLR: V Position */
#define SCTLR_V_Msk                      (1UL << SCTLR_V_Pos)                   /*!< SCTLR: V Mask */

#define SCTLR_I_Pos                      12U                                    /*!< SCTLR: I Position */
#define SCTLR_I_Msk                      (1UL << SCTLR_I_Pos)                   /*!< SCTLR: I Mask */

#define SCTLR_Z_Pos                      11U                                    /*!< SCTLR: Z Position */
#define SCTLR_Z_Msk                      (1UL << SCTLR_Z_Pos)                   /*!< SCTLR: Z Mask */

#define SCTLR_SW_Pos                     10U                                    /*!< SCTLR: SW Position */
#define SCTLR_SW_Msk                     (1UL << SCTLR_SW_Pos)                  /*!< SCTLR: SW Mask */

#define SCTLR_B_Pos                      7U                                     /*!< SCTLR: B Position */
#define SCTLR_B_Msk                      (1UL << SCTLR_B_Pos)                   /*!< SCTLR: B Mask */

#define SCTLR_CP15BEN_Pos                5U                                     /*!< SCTLR: CP15BEN Position */
#define SCTLR_CP15BEN_Msk                (1UL << SCTLR_CP15BEN_Pos)             /*!< SCTLR: CP15BEN Mask */

#define SCTLR_C_Pos                      2U                                     /*!< SCTLR: C Position */
#define SCTLR_C_Msk                      (1UL << SCTLR_C_Pos)                   /*!< SCTLR: C Mask */

#define SCTLR_A_Pos                      1U                                     /*!< SCTLR: A Position */
#define SCTLR_A_Msk                      (1UL << SCTLR_A_Pos)                   /*!< SCTLR: A Mask */

#define SCTLR_M_Pos                      0U                                     /*!< SCTLR: M Position */
#define SCTLR_M_Msk                      (1UL << SCTLR_M_Pos)                   /*!< SCTLR: M Mask */

/* CP15 Register ACTLR */
typedef union
{
  struct
  {
    uint32_t _reserved0:6;               /*!< bit: 0.. 5  Reserved */
    uint32_t SMP:1;                      /*!< bit:     6  Enables coherent requests to the processor */
    uint32_t _reserved1:3;               /*!< bit: 7.. 9  Reserved */
    uint32_t DODMBS:1;                   /*!< bit:    10  Disable optimized data memory barrier behavior */
    uint32_t L2RADIS:1;                  /*!< bit:    11  L2 Data Cache read-allocate mode disable */
    uint32_t L1RADIS:1;                  /*!< bit:    12  L1 Data Cache read-allocate mode disable */
    uint32_t L1PCTL:2;                   /*!< bit:13..14  L1 Data prefetch control */
    uint32_t DDVM:1;                     /*!< bit:    15  Disable Distributed Virtual Memory (DVM) transactions */
    uint32_t _reserved3:12;              /*!< bit:16..27  Reserved */
    uint32_t DDI:1;                      /*!< bit:    28  Disable dual issue */
    uint32_t _reserved7:3;               /*!< bit:29..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} ACTLR_Type;

#define ACTLR_DDI_Pos                    28U                                     /*!< ACTLR: DDI Position */
#define ACTLR_DDI_Msk                    (1UL << ACTLR_DDI_Pos)                  /*!< ACTLR: DDI Mask */

#define ACTLR_DDVM_Pos                   15U                                     /*!< ACTLR: DDVM Position */
#define ACTLR_DDVM_Msk                   (1UL << ACTLR_DDVM_Pos)                 /*!< ACTLR: DDVM Mask */

#define ACTLR_L1PCTL_Pos                 13U                                     /*!< ACTLR: L1PCTL Position */
#define ACTLR_L1PCTL_Msk                 (3UL << ACTLR_L1PCTL_Pos)               /*!< ACTLR: L1PCTL Mask */

#define ACTLR_L1RADIS_Pos                12U                                     /*!< ACTLR: L1RADIS Position */
#define ACTLR_L1RADIS_Msk                (1UL << ACTLR_L1RADIS_Pos)              /*!< ACTLR: L1RADIS Mask */

#define ACTLR_L2RADIS_Pos                11U                                     /*!< ACTLR: L2RADIS Position */
#define ACTLR_L2RADIS_Msk                (1UL << ACTLR_L2RADIS_Pos)              /*!< ACTLR: L2RADIS Mask */

#define ACTLR_DODMBS_Pos                 10U                                     /*!< ACTLR: DODMBS Position */
#define ACTLR_DODMBS_Msk                 (1UL << ACTLR_DODMBS_Pos)               /*!< ACTLR: DODMBS Mask */

#define ACTLR_SMP_Pos                    6U                                      /*!< ACTLR: SMP Position */
#define ACTLR_SMP_Msk                    (1UL << ACTLR_SMP_Pos)                  /*!< ACTLR: SMP Mask */


/* CP15 Register CPACR */
typedef union
{
  struct
  {
    uint32_t _reserved0:20;              /*!< bit: 0..19  Reserved */
    uint32_t cp10:2;                     /*!< bit:20..21  Access rights for coprocessor 10 */
    uint32_t cp11:2;                     /*!< bit:22..23  Access rights for coprocessor 11 */
    uint32_t _reserved1:6;               /*!< bit:24..29  Reserved */
    uint32_t D32DIS:1;                   /*!< bit:    30  Disable use of registers D16-D31 of the VFP register file */
    uint32_t ASEDIS:1;                   /*!< bit:    31  Disable Advanced SIMD Functionality */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} CPACR_Type;

#define CPACR_ASEDIS_Pos                 31U                                    /*!< CPACR: ASEDIS Position */
#define CPACR_ASEDIS_Msk                 (1UL << CPACR_ASEDIS_Pos)              /*!< CPACR: ASEDIS Mask */

#define CPACR_D32DIS_Pos                 30U                                    /*!< CPACR: D32DIS Position */
#define CPACR_D32DIS_Msk                 (1UL << CPACR_D32DIS_Pos)              /*!< CPACR: D32DIS Mask */

#define CPACR_cp11_Pos                   22U                                    /*!< CPACR: cp11 Position */
#define CPACR_cp11_Msk                   (3UL << CPACR_cp11_Pos)                /*!< CPACR: cp11 Mask */

#define CPACR_cp10_Pos                   20U                                    /*!< CPACR: cp10 Position */
#define CPACR_cp10_Msk                   (3UL << CPACR_cp10_Pos)                /*!< CPACR: cp10 Mask */


/* CP15 Register DFSR */
typedef union
{
  struct
  {
    uint32_t FS0:4;                      /*!< bit: 0.. 3  Fault Status bits bit 0-3 */
    uint32_t Domain:4;                   /*!< bit: 4.. 7  Fault on which domain */
    uint32_t _reserved0:2;               /*!< bit: 8.. 9  Reserved */
    uint32_t FS1:1;                      /*!< bit:    10  Fault Status bits bit 4 */
    uint32_t WnR:1;                      /*!< bit:    11  Write not Read bit */
    uint32_t ExT:1;                      /*!< bit:    12  External abort type */
    uint32_t CM:1;                       /*!< bit:    13  Cache maintenance fault */
    uint32_t _reserved1:18;              /*!< bit:14..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} DFSR_Type;

#define DFSR_CM_Pos                      13U                                    /*!< DFSR: CM Position */
#define DFSR_CM_Msk                      (1UL << DFSR_CM_Pos)                   /*!< DFSR: CM Mask */

#define DFSR_Ext_Pos                     12U                                    /*!< DFSR: Ext Position */
#define DFSR_Ext_Msk                     (1UL << DFSR_Ext_Pos)                  /*!< DFSR: Ext Mask */

#define DFSR_WnR_Pos                     11U                                    /*!< DFSR: WnR Position */
#define DFSR_WnR_Msk                     (1UL << DFSR_WnR_Pos)                  /*!< DFSR: WnR Mask */

#define DFSR_FS1_Pos                     10U                                    /*!< DFSR: FS1 Position */
#define DFSR_FS1_Msk                     (1UL << DFSR_FS1_Pos)                  /*!< DFSR: FS1 Mask */

#define DFSR_Domain_Pos                  4U                                     /*!< DFSR: Domain Position */
#define DFSR_Domain_Msk                  (0xFUL << DFSR_Domain_Pos)             /*!< DFSR: Domain Mask */

#define DFSR_FS0_Pos                     0U                                     /*!< DFSR: FS0 Position */
#define DFSR_FS0_Msk                     (0xFUL << DFSR_FS0_Pos)                /*!< DFSR: FS0 Mask */


/* CP15 Register IFSR */
typedef union
{
  struct
  {
    uint32_t FS0:4;                      /*!< bit: 0.. 3  Fault Status bits bit 0-3 */
    uint32_t _reserved0:6;               /*!< bit: 4.. 9  Reserved */
    uint32_t FS1:1;                      /*!< bit:    10  Fault Status bits bit 4 */
    uint32_t _reserved1:1;               /*!< bit:    11  Reserved */
    uint32_t ExT:1;                      /*!< bit:    12  External abort type */
    uint32_t _reserved2:19;              /*!< bit:13..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} IFSR_Type;

#define IFSR_ExT_Pos                     12U                                    /*!< IFSR: ExT Position */
#define IFSR_ExT_Msk                     (1UL << IFSR_ExT_Pos)                  /*!< IFSR: ExT Mask */

#define IFSR_FS1_Pos                     10U                                    /*!< IFSR: FS1 Position */
#define IFSR_FS1_Msk                     (1UL << IFSR_FS1_Pos)                  /*!< IFSR: FS1 Mask */

#define IFSR_FS0_Pos                     0U                                     /*!< IFSR: FS0 Position */
#define IFSR_FS0_Msk                     (0xFUL << IFSR_FS0_Pos)                /*!< IFSR: FS0 Mask */


/* CP15 Register ISR */
typedef union
{
  struct
  {
    uint32_t _reserved0:6;               /*!< bit: 0.. 5  Reserved */
    uint32_t F:1;                        /*!< bit:     6  FIQ pending bit */
    uint32_t I:1;                        /*!< bit:     7  IRQ pending bit */
    uint32_t A:1;                        /*!< bit:     8  External abort pending bit */
    uint32_t _reserved1:23;              /*!< bit:14..31  Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} ISR_Type;

#define ISR_A_Pos                        13U                                    /*!< ISR: A Position */
#define ISR_A_Msk                        (1UL << ISR_A_Pos)                     /*!< ISR: A Mask */

#define ISR_I_Pos                        12U                                    /*!< ISR: I Position */
#define ISR_I_Msk                        (1UL << ISR_I_Pos)                     /*!< ISR: I Mask */

#define ISR_F_Pos                        11U                                    /*!< ISR: F Position */
#define ISR_F_Msk                        (1UL << ISR_F_Pos)                     /*!< ISR: F Mask */


/* Mask and shift a bit field value for use in a register bit range. */
#define _VAL2FLD(field, value)    ((value << field ## _Pos) & field ## _Msk)

/* Mask and shift a register value to extract a bit filed value. */
#define _FLD2VAL(field, value)    ((value & field ## _Msk) >> field ## _Pos)



/*******************************************************************************
 *                 CP15 Access Functions
 ******************************************************************************/
FORCEDINLINE __STATIC_INLINE uint32_t __get_SCTLR(void)
{
  return __MRC(15, 0, 1, 0, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_SCTLR(uint32_t sctlr)
{
  __MCR(15, 0, sctlr, 1, 0, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_ACTLR(void)
{
  return __MRC(15, 0, 1, 0, 1);
}

FORCEDINLINE __STATIC_INLINE void __set_ACTLR(uint32_t actlr)
{
  __MCR(15, 0, actlr, 1, 0, 1);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_CPACR(void)
{
  return __MRC(15, 0, 1, 0, 2);
}

FORCEDINLINE __STATIC_INLINE void __set_CPACR(uint32_t cpacr)
{
  __MCR(15, 0, cpacr, 1, 0, 2);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_TTBR0(void)
{
  return __MRC(15, 0, 2, 0, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_TTBR0(uint32_t ttbr0)
{
  __MCR(15, 0, ttbr0, 2, 0, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_TTBR1(void)
{
  return __MRC(15, 0, 2, 0, 1);
}

FORCEDINLINE __STATIC_INLINE void __set_TTBR1(uint32_t ttbr1)
{
  __MCR(15, 0, ttbr1, 2, 0, 1);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_TTBCR(void)
{
  return __MRC(15, 0, 2, 0, 2);
}

FORCEDINLINE __STATIC_INLINE void __set_TTBCR(uint32_t ttbcr)
{
  __MCR(15, 0, ttbcr, 2, 0, 2);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_DACR(void)
{
  return __MRC(15, 0, 3, 0, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_DACR(uint32_t dacr)
{
  __MCR(15, 0, dacr, 3, 0, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_DFSR(void)
{
  return __MRC(15, 0, 5, 0, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_DFSR(uint32_t dfsr)
{
  __MCR(15, 0, dfsr, 5, 0, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_IFSR(void)
{
  return __MRC(15, 0, 5, 0, 1);
}

FORCEDINLINE __STATIC_INLINE void __set_IFSR(uint32_t ifsr)
{
  __MCR(15, 0, ifsr, 5, 0, 1);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_DFAR(void)
{
  return __MRC(15, 0, 6, 0, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_DFAR(uint32_t dfar)
{
  __MCR(15, 0, dfar, 6, 0, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_IFAR(void)
{
  return __MRC(15, 0, 6, 0, 2);
}

FORCEDINLINE __STATIC_INLINE void __set_IFAR(uint32_t ifar)
{
  __MCR(15, 0, ifar, 6, 0, 2);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_VBAR(void)
{
  return __MRC(15, 0, 12, 0, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_VBAR(uint32_t vbar)
{
  __MCR(15, 0, vbar, 12, 0, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_ISR(void)
{
  return __MRC(15, 0, 12, 1, 0);
}

FORCEDINLINE __STATIC_INLINE void __set_ISR(uint32_t isr)
{
  __MCR(15, 0, isr, 12, 1, 0);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_CONTEXTIDR(void)
{
  return __MRC(15, 0, 13, 0, 1);
}

FORCEDINLINE __STATIC_INLINE void __set_CONTEXTIDR(uint32_t contextidr)
{
  __MCR(15, 0, contextidr, 13, 0, 1);
}

FORCEDINLINE __STATIC_INLINE uint32_t __get_CBAR(void)
{
  return __MRC(15, 4, 15, 0, 0);
}


/*******************************************************************************
 *                 L1 Cache Functions
 ******************************************************************************/
#define L1C_INSTRUCTION_CACHE_LINE_SIZE          (32U)
#define L1C_DATA_CACHE_LINE_SIZE                 (64U)

#define L1C_DATA_CACHE_OP_CLEAN                  (1U)
#define L1C_DATA_CACHE_OP_INVALIDATE             (2U)
#define L1C_DATA_CACHE_OP_CLEAN_INVALIDATE       (3U)

/* Invalidate both intruction cache and branch predictor */
FORCEDINLINE __STATIC_INLINE void L1C_InvalidateInstructionCacheAll(void)
{
  /* ICIALLU only affects self core. */
  __MCR(15, 0, 0, 7, 5, 0);
  /* BPIALL only affects self core. */
  __MCR(15, 0, 0, 7, 5, 6);
  /* Ensure completion of the invalidation */
  __DSB();
  __ISB();
}

FORCEDINLINE __STATIC_INLINE void L1C_InvalidateInstructionCacheLine(const void *VirtAddr)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_INSTRUCTION_CACHE_LINE_SIZE - 1);
  /* ICIMVAU */
  __MCR(15, 0, base, 7, 5, 1);
  /* BPIMVA */
  __MCR(15, 0, base, 7, 5, 7);
  /* Ensure completion of the invalidation */
  __DSB();
  __ISB();
}

FORCEDINLINE __STATIC_INLINE void L1C_InvalidateInstructionCacheRange(const void *VirtAddr, uint32_t length)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_INSTRUCTION_CACHE_LINE_SIZE - 1);
  uint32_t end = (uint32_t)VirtAddr + length;

  while (base < end)
  {
    /* ICIMVAU */
    __MCR(15, 0, base, 7, 5, 1);
    /* BPIMVA */
    __MCR(15, 0, base, 7, 5, 7);
    base += L1C_INSTRUCTION_CACHE_LINE_SIZE;
  }

  /* Ensure completion of the invalidation */
  __DSB();
  __ISB();
}

FORCEDINLINE __STATIC_INLINE void L1C_EnableInstructionCache()
{
  uint32_t sctlr = __get_SCTLR();

  if ((sctlr & (SCTLR_I_Msk | SCTLR_Z_Msk)) != (SCTLR_I_Msk | SCTLR_Z_Msk))
  { /* Enable cache and branch predictor */
    L1C_InvalidateInstructionCacheAll();
    sctlr |= SCTLR_I_Msk | SCTLR_Z_Msk;
    __set_SCTLR(sctlr);
    /* __ISB() is not needed as there's no instruction changes */
  }
}

FORCEDINLINE __STATIC_INLINE void L1C_DisableInstructionCache()
{
  uint32_t sctlr = __get_SCTLR();

  if ((sctlr & (SCTLR_I_Msk | SCTLR_Z_Msk)) != 0)
  { /* Disable cache and branch predictor */
    sctlr &= ~(SCTLR_I_Msk | SCTLR_Z_Msk);
    __set_SCTLR(sctlr);
    /* __ISB() is not needed as there's no instruction changes */
  }
}

FORCEDINLINE __STATIC_INLINE void L1C_OpDataCacheAll(uint32_t operation)
{
  uint32_t clidr, loc, ctype;
  uint32_t level;
  uint32_t ccsidr, set, ass, setshift, assshift;
  uint32_t i, j, reg;

  clidr = __MRC(15, 1, 0, 0, 1);
  loc = (clidr >> 24) & 0x7UL;

  for (level = 0; level < loc; level++)
  { /* Clean each level */
    ctype = (clidr >> (level * 3)) & 0x7UL;
    if (ctype == 2 || /* Data cache only */
        ctype == 3 || /* Separate instruction and data caches */
        ctype == 4)   /* Unified cache */
    {
      __MCR(15, 2, level << 1, 0, 0, 0); /* Select data cache */

      ccsidr = __MRC(15, 1, 0, 0, 0); /* Get cache size ID */
      set = ((ccsidr >> 13) & 0x7FFFUL) + 1;
      ass = ((ccsidr >> 3) & 0x3FFUL) + 1;

      setshift = (ccsidr & 0x7UL) + 2 + 2;
      for (i = 1; i < 10 && ass > (1UL << i); i++)
      {
      }
      assshift = 32 - i;

      for (i = 0; i < ass; i++)
      {
        for (j = 0; j < set; j++)
        {
          reg = (i << assshift) | (j << setshift) | (level << 1);
          switch (operation)
          {
            case L1C_DATA_CACHE_OP_CLEAN:
              /* DCCSW */
              __MCR(15, 0, reg, 7, 10, 2);
              break;
            case L1C_DATA_CACHE_OP_INVALIDATE:
              /* DCISW */
              __MCR(15, 0, reg, 7, 6, 2);
              break;
            case L1C_DATA_CACHE_OP_CLEAN_INVALIDATE:
              /* DCCISW */
              __MCR(15, 0, reg, 7, 14, 2);
              break;
            default:
              break;
          }
        }
      }
      /* Ensure completion of the L1 cache operation */
      __DSB();
    }
  }

  /* Ensure completion of the cache operation */
  __DSB();
}

/* Invalidate data cache */
FORCEDINLINE __STATIC_INLINE void L1C_InvalidateDataCacheAll(void)
{
  L1C_OpDataCacheAll(L1C_DATA_CACHE_OP_INVALIDATE);
}

FORCEDINLINE __STATIC_INLINE void L1C_InvalidateDataCacheLine(const void *VirtAddr)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_DATA_CACHE_LINE_SIZE - 1);
  /* DCIMVAC */
  __MCR(15, 0, base, 7, 6, 1);
  /* Ensure completion of the invalidation */
  __DSB();
}

FORCEDINLINE __STATIC_INLINE void L1C_InvalidateDataCacheRange(const void *VirtAddr, uint32_t length)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_DATA_CACHE_LINE_SIZE - 1);
  uint32_t end = (uint32_t)VirtAddr + length;

  while (base < end)
  {
    /* DCIMVAC */
    __MCR(15, 0, base, 7, 6, 1);
    base += L1C_DATA_CACHE_LINE_SIZE;
  }

  /* Ensure completion of the invalidation */
  __DSB();
}

/* Clean data cache */
FORCEDINLINE __STATIC_INLINE void L1C_CleanDataCacheAll(void)
{
  L1C_OpDataCacheAll(L1C_DATA_CACHE_OP_CLEAN);
}

FORCEDINLINE __STATIC_INLINE void L1C_CleanDataCacheLine(const void *VirtAddr)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_DATA_CACHE_LINE_SIZE - 1);
  /* DCCMVAC */
  __MCR(15, 0, base, 7, 10, 1);
  /* Ensure completion of the clean */
  __DSB();
}

FORCEDINLINE __STATIC_INLINE void L1C_CleanDataCacheRange(const void *VirtAddr, uint32_t length)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_DATA_CACHE_LINE_SIZE - 1);
  uint32_t end = (uint32_t)VirtAddr + length;

  while (base < end)
  {
    /* DCCMVAC */
    __MCR(15, 0, base, 7, 10, 1);
    base += L1C_DATA_CACHE_LINE_SIZE;
  }

  /* Ensure completion of the clean */
  __DSB();
}

/* Clean and invalidate data cache */
FORCEDINLINE __STATIC_INLINE void L1C_CleanInvalidateDataCacheAll(void)
{
  L1C_OpDataCacheAll(L1C_DATA_CACHE_OP_CLEAN_INVALIDATE);
}

FORCEDINLINE __STATIC_INLINE void L1C_CleanInvalidateDataCacheLine(const void *VirtAddr)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_DATA_CACHE_LINE_SIZE - 1);
  /* DCCIMVAC */
  __MCR(15, 0, base, 7, 14, 1);
  /* Ensure completion of the clean */
  __DSB();
}

FORCEDINLINE __STATIC_INLINE void L1C_CleanInvalidateDataCacheRange(const void *VirtAddr, uint32_t length)
{
  uint32_t base = (uint32_t)VirtAddr & ~(L1C_DATA_CACHE_LINE_SIZE - 1);
  uint32_t end = (uint32_t)VirtAddr + length;

  while (base < end)
  {
    /* DCCIMVAC */
    __MCR(15, 0, base, 7, 14, 1);
    base += L1C_DATA_CACHE_LINE_SIZE;
  }

  /* Ensure completion of the clean */
  __DSB();
}

FORCEDINLINE __STATIC_INLINE void L1C_EnableDataCache()
{
  uint32_t sctlr = __get_SCTLR();

  if ((sctlr & SCTLR_C_Msk) != SCTLR_C_Msk)
  { /* Enable cache */
    L1C_InvalidateDataCacheAll();
    sctlr |= SCTLR_C_Msk;
    __set_SCTLR(sctlr);
    /* __ISB() is not needed as there's no instruction changes */
  }
}

FORCEDINLINE __STATIC_INLINE void L1C_DisableDataCache()
{
  uint32_t sctlr = __get_SCTLR();

  if ((sctlr & SCTLR_C_Msk) != 0)
  { /* Disable cache */
    sctlr &= ~SCTLR_C_Msk;
    __set_SCTLR(sctlr);
    L1C_CleanInvalidateDataCacheAll();
    /* __ISB() is not needed as there's no instruction changes */
  }
}

/*******************************************************************************
 *                 MMU Functions
 ******************************************************************************/
enum _mmu_memory_type
{
  MMU_MemoryStronglyOrdered               = 0U,   /*!< TEX: 0, C: 0, B: 0 */
  MMU_MemoryDevice                        = 1U,   /*!< TEX: 0, C: 0, B: 1 */
  MMU_MemoryWriteBackNoWriteAllocate      = 3U,   /*!< TEX: 0, C: 1, B: 1 */
  MMU_MemoryNonCacheable                  = 4U,   /*!< TEX: 1, C: 0, B: 0 */
  MMU_MemoryWriteBackWriteAllocate        = 7U,   /*!< TEX: 1, C: 1, B: 1 */
};

enum _mmu_domain_access
{
  MMU_DomainNA                            = 0U,   /*!< No acces. Any access to the domain generates a Domain fault */
  MMU_DomainClient                        = 1U,   /*!< Accesses are checked against the permission bits in the translation tables */
  MMU_DomainManager                       = 3U,   /*!< Accesses are not checked against the permission bits in the translation tables */
};

enum _mmu_access_permission
{
  MMU_AccessNANA                          = 0U,   /*!< No access in both privileged and unprivileged modes */
  MMU_AccessRWNA                          = 1U,   /*!< Read/Write in privileged mode, no access in unprivileged mode */
  MMU_AccessRWRO                          = 2U,   /*!< Read/Write in privileged mode, Read Only in unprivileged mode */
  MMU_AccessRWRW                          = 3U,   /*!< Read/Write in privileged mode, Read/Write in unprivileged mode */
  MMU_AccessRONA                          = 5U,   /*!< Read Only in privileged mode, no access in unprivileged mode */
  MMU_AccessRORO                          = 7U,   /*!< Read Only in privileged mode, Read Only in unprivileged mode */
};

typedef struct _mmu_attribute_t
{
  uint8_t  type;           /*!< memory type, see _mmu_memory_type */
  uint8_t  domain;         /*!< memory domain assignment */
  uint8_t  accessPerm;     /*!< the memory region access permission, see _mmu_access_permission */
  uint8_t  shareable:1;    /*!< memory region is shareable among multiple cores or system master */
  uint8_t  notSecure:1;    /*!< translated physical address is in non-secure memory map */
  uint8_t  notGlob:1;      /*!< the region translation is process specific */
  uint8_t  notExec:1;      /*!< the memory region cannot execute code */
} mmu_attribute_t;

/* L1Table must be 16KB aligned (bit [13:0] all 0) with size 16KB */
FORCEDINLINE __STATIC_INLINE void MMU_Init(uint32_t *L1Table)
{
  uint32_t L1Base = (uint32_t)L1Table;

  /* Use TTBR translation, with 16KB L1Table size (N=0) */
  __set_TTBCR(0);

  /* Set TTBR0 with inner/outer write back write allocate and not shareable, [4:3]=01, [1]=0, [6,0]=01 */
  __set_TTBR0((L1Base & 0xFFFFC000UL) | 0x9UL);

  /* Set all domains to client */
  __set_DACR(0x55555555UL);

  /* Set PROCID and ASID to 0 */
  __MCR(15, 0, 0, 13, 0, 1);

  /* Set all virtual space to invalid */
  memset(L1Table, 0, 4096*4);
}

/* L1Table[4096], L2Table[256] */
/* L2Table == NULL: use L1Table entry */
FORCEDINLINE __STATIC_INLINE void MMU_ConfigPage(uint32_t *L1Table, uint32_t *L2Table, const void *VirtAddr,
                                    uint32_t PhysAddr, const mmu_attribute_t *Attr)
{
  uint32_t index1 = (uint32_t)VirtAddr >> 20;
  uint32_t index2 = ((uint32_t)VirtAddr >> 12) & 0xFFUL;
  uint32_t descriptor1 = L1Table[index1];
  uint32_t descriptor2 = (PhysAddr & 0xFFFFF000UL)           |     /* Physical address */
                         (Attr->notGlob ? (1UL << 11) : 0)   |     /* nG */
                         (Attr->shareable ? (1UL << 10) : 0) |     /* S */
                         (Attr->notExec ? 1UL : 0)           |     /* XN */
                         (((Attr->type >> 2) & 7UL) << 6)    |     /* TEX */
                         ((Attr->type & 3UL) << 2)           |     /* C,B */
                         ((Attr->accessPerm & 4UL) << 9)     |     /* AP[2] */
                         ((Attr->accessPerm & 3UL) << 4)     |     /* AP[1:0] */
                         2UL;                                      /* Small Page */

  if ((descriptor1 & 3UL) == 1)  /* Page table first level already exists */
  {
    /* Ignore the parameter and use the descriptor */
    L2Table = (uint32_t *)(descriptor1 & 0xFFFFFC00UL);
    L2Table[index2] = descriptor2;
  }
  else if ((descriptor1 & 3UL) == 0) /* No L2 table available */
  {
    L1Table[index1] = ((uint32_t)L2Table & 0xFFFFFC00UL)     |     /* L2 Table address */
                      ((Attr->domain & 15UL) << 5)           |     /* Domain */
                      (Attr->notSecure ? (1UL << 3) : 0)     |     /* NS */
                      1UL;                                         /* Page Table */
    /* Use L2Table in parameter */
    L2Table[index2] = descriptor2;
  }
}

/* L1Table[4096], L2Table[256] */
FORCEDINLINE __STATIC_INLINE void MMU_ConfigLargePage(uint32_t *L1Table, uint32_t *L2Table, const void *VirtAddr,
                                         uint32_t PhysAddr, const mmu_attribute_t *Attr)
{
  uint32_t i;
  uint32_t index1 = (uint32_t)VirtAddr >> 20;
  uint32_t index2 = ((uint32_t)VirtAddr >> 12) & 0xF0UL;
  uint32_t descriptor1 = L1Table[index1];
  uint32_t descriptor2 = (PhysAddr & 0xFFFF0000UL)           |     /* Physical address */
                         (Attr->notGlob ? (1UL << 11) : 0)   |     /* nG */
                         (Attr->shareable ? (1UL << 10) : 0) |     /* S */
                         (Attr->notExec ? (1UL << 15) : 0)   |     /* XN */
                         (((Attr->type >> 2) & 7UL) << 12)   |     /* TEX */
                         ((Attr->type & 3UL) << 2)           |     /* C,B */
                         ((Attr->accessPerm & 4UL) << 9)     |     /* AP[2] */
                         ((Attr->accessPerm & 3UL) << 4)     |     /* AP[1:0] */
                         1UL;                                      /* Large Page */

  if ((descriptor1 & 3UL) == 1)  /* Page table first level already exists */
  {
    /* Ignore the parameter and use the descriptor */
    L2Table = (uint32_t *)(descriptor1 & 0xFFFFFC00UL);
    for (i = 0; i < 16; i++)
      L2Table[index2 + i] = descriptor2;
  }
  else if ((descriptor1 & 3UL) == 0) /* No L2 table available */
  {
    L1Table[index1] = ((uint32_t)L2Table & 0xFFFFFC00UL)     |     /* L2 Table address */
                      ((Attr->domain & 15UL) << 5)           |     /* Domain */
                      (Attr->notSecure ? (1UL << 3) : 0)     |     /* NS */
                      1UL;                                         /* Page Table */
    /* Use L2Table in parameter */
    for (i = 0; i < 16; i++)
      L2Table[index2 + i] = descriptor2;
  }
}

/* L1Table[4096] */
FORCEDINLINE __STATIC_INLINE void MMU_ConfigSection(uint32_t *L1Table, const void *VirtAddr,
                                       uint32_t PhysAddr, const mmu_attribute_t *Attr)
{
  uint32_t index = (uint32_t)VirtAddr >> 20;
  uint32_t descriptor = (PhysAddr & 0xFFF00000UL)           |     /* Physical address */
                        (Attr->notSecure ? (1UL << 19) : 0) |     /* NS */
                        (Attr->notGlob ? (1UL << 17) : 0)   |     /* nG */
                        (Attr->shareable ? (1UL << 16) : 0) |     /* S */
                        (Attr->notExec ? (1UL << 4) : 0)    |     /* XN */
                        (((Attr->type >> 2) & 7UL) << 12)   |     /* TEX */
                        ((Attr->type & 3UL) << 2)           |     /* C,B */
                        ((Attr->domain & 15UL) << 5)        |     /* Domain */
                        ((Attr->accessPerm & 4UL) << 15)    |     /* AP[2] */
                        ((Attr->accessPerm & 3UL) << 10)    |     /* AP[1:0] */
                        2UL;                                      /* Section */

  L1Table[index] = descriptor;
}

/* L1Table[4096] */
FORCEDINLINE __STATIC_INLINE void MMU_ConfigSuperSection(uint32_t *L1Table, const void *VirtAddr,
                                            uint32_t PhysAddr, const mmu_attribute_t *Attr)
{
  uint32_t i;
  uint32_t index = ((uint32_t)VirtAddr >> 20) & 0xFF0UL;
  uint32_t descriptor = (PhysAddr & 0xFF000000UL)           |     /* Physical address */
                        (Attr->notSecure ? (1UL << 19) : 0) |     /* NS */
                        (Attr->notGlob ? (1UL << 17) : 0)   |     /* nG */
                        (Attr->shareable ? (1UL << 16) : 0) |     /* S */
                        (Attr->notExec ? (1UL << 4) : 0)    |     /* XN */
                        (((Attr->type >> 2) & 7UL) << 12)   |     /* TEX */
                        ((Attr->type & 3UL) << 2)           |     /* C,B */
                                                                /* Supersection has fixed domain 0 */
                        ((Attr->accessPerm & 4UL) << 15)    |     /* AP[2] */
                        ((Attr->accessPerm & 3UL) << 10)    |     /* AP[1:0] */
                        2;                                      /* Section */

  for (i = 0; i < 16; i++)
    L1Table[index + i] = descriptor;
}

FORCEDINLINE __STATIC_INLINE uint32_t * MMU_GetL1Table(void)
{
  return (uint32_t *)(__get_TTBR0() & 0xFFFFC000UL);
}

FORCEDINLINE __STATIC_INLINE void MMU_SetL1Table(uint32_t *L1Table)
{
  /* update L1Table base address without changing other attributes */
  __set_TTBR0(((uint32_t)L1Table & 0xFFFFC000UL) | (__get_TTBR0() & 0x3FFFUL));
}

FORCEDINLINE __STATIC_INLINE uint32_t * MMU_GetL2Table(const void *VirtAddr)
{
  uint32_t index1 = (uint32_t)VirtAddr >> 20;
  uint32_t descriptor1;
  uint32_t *L1Table = MMU_GetL1Table();
  uint32_t *L2Table = NULL;

  descriptor1 = L1Table[index1];
  if ((descriptor1 & 3UL) == 1)  /* Page */
    L2Table = (uint32_t *)(descriptor1 & 0xFFFFFC00UL);

  return L2Table;
}

FORCEDINLINE __STATIC_INLINE void MMU_SetContext(uint32_t procid, uint32_t asid)
{
  uint32_t reg = (procid << 8) | (asid & 0xFFUL);

  __MCR(15, 0, reg, 13, 0, 1);
}

/* access: _mmu_domain_access */
FORCEDINLINE __STATIC_INLINE void MMU_ConfigDomain(uint32_t domain, uint32_t access)
{
  uint32_t dacr = __get_DACR();
  uint32_t mask = 3UL << ((domain & 0xFUL) * 2);
  uint32_t reg = (dacr & ~mask) | ((access & 3) << ((domain & 0xFUL) * 2));

  __set_DACR(reg);
}

FORCEDINLINE __STATIC_INLINE void MMU_InvalidateTLB(void)
{
  /* TLBIALL only affects self core */
  __MCR(15, 0, 0, 8, 7, 0);
  __DSB();
  __ISB();
}

FORCEDINLINE __STATIC_INLINE void MMU_Disable(void)
{
  uint32_t sctlr = __get_SCTLR();

  sctlr &= ~SCTLR_M_Msk;
  __set_SCTLR(sctlr);
  __ISB();
}

FORCEDINLINE __STATIC_INLINE void MMU_Enable(void)
{
  uint32_t sctlr = __get_SCTLR();

  MMU_InvalidateTLB();
  sctlr |= SCTLR_M_Msk;
  __set_SCTLR(sctlr);
  __ISB();
}

/*******************************************************************************
 *                 GIC Functions
 ******************************************************************************/
typedef struct
{
        uint32_t RESERVED0[1024];
  __IOM uint32_t D_CTLR;                 /*!< Offset: 0x1000 (R/W) Distributor Control Register */
  __IM  uint32_t D_TYPER;                /*!< Offset: 0x1004 (R/ )  Interrupt Controller Type Register */
  __IM  uint32_t D_IIDR;                 /*!< Offset: 0x1008 (R/ )  Distributor Implementer Identification Register */
        uint32_t RESERVED1[29];
  __IOM uint32_t D_IGROUPR[16];          /*!< Offset: 0x1080 - 0x0BC (R/W) Interrupt Group Registers */
        uint32_t RESERVED2[16];
  __IOM uint32_t D_ISENABLER[16];        /*!< Offset: 0x1100 - 0x13C (R/W) Interrupt Set-Enable Registers */
        uint32_t RESERVED3[16];
  __IOM uint32_t D_ICENABLER[16];        /*!< Offset: 0x1180 - 0x1BC (R/W) Interrupt Clear-Enable Registers */
        uint32_t RESERVED4[16];
  __IOM uint32_t D_ISPENDR[16];          /*!< Offset: 0x1200 - 0x23C (R/W) Interrupt Set-Pending Registers */
        uint32_t RESERVED5[16];
  __IOM uint32_t D_ICPENDR[16];          /*!< Offset: 0x1280 - 0x2BC (R/W) Interrupt Clear-Pending Registers */
        uint32_t RESERVED6[16];
  __IOM uint32_t D_ISACTIVER[16];        /*!< Offset: 0x1300 - 0x33C (R/W) Interrupt Set-Active Registers */
        uint32_t RESERVED7[16];
  __IOM uint32_t D_ICACTIVER[16];        /*!< Offset: 0x1380 - 0x3BC (R/W) Interrupt Clear-Active Registers */
        uint32_t RESERVED8[16];
  __IOM uint8_t  D_IPRIORITYR[512];      /*!< Offset: 0x1400 - 0x5FC (R/W) Interrupt Priority Registers */
        uint32_t RESERVED9[128];
  __IOM uint8_t  D_ITARGETSR[512];       /*!< Offset: 0x1800 - 0x9FC (R/W) Interrupt Targets Registers */
        uint32_t RESERVED10[128];
  __IOM uint32_t D_ICFGR[32];            /*!< Offset: 0x1C00 - 0xC7C (R/W) Interrupt configuration registers */
        uint32_t RESERVED11[32];
  __IM  uint32_t D_PPISR;                /*!< Offset: 0x1D00 (R/ ) Private Peripheral Interrupt Status Register */
  __IM  uint32_t D_SPISR[15];            /*!< Offset: 0x1D04 - 0xD3C (R/ ) Shared Peripheral Interrupt Status Registers */
        uint32_t RESERVED12[112];
  __OM  uint32_t D_SGIR;                 /*!< Offset: 0x1F00 ( /W) Software Generated Interrupt Register */
        uint32_t RESERVED13[3];
  __IOM uint8_t  D_CPENDSGIR[16];        /*!< Offset: 0x1F10 - 0xF1C (R/W) SGI Clear-Pending Registers */
  __IOM uint8_t  D_SPENDSGIR[16];        /*!< Offset: 0x1F20 - 0xF2C (R/W) SGI Set-Pending Registers */
        uint32_t RESERVED14[40];
  __IM  uint32_t D_PIDR4;                /*!< Offset: 0x1FD0 (R/ ) Peripheral ID4 Register */
  __IM  uint32_t D_PIDR5;                /*!< Offset: 0x1FD4 (R/ ) Peripheral ID5 Register */
  __IM  uint32_t D_PIDR6;                /*!< Offset: 0x1FD8 (R/ ) Peripheral ID6 Register */
  __IM  uint32_t D_PIDR7;                /*!< Offset: 0x1FDC (R/ ) Peripheral ID7 Register */
  __IM  uint32_t D_PIDR0;                /*!< Offset: 0x1FE0 (R/ ) Peripheral ID0 Register */
  __IM  uint32_t D_PIDR1;                /*!< Offset: 0x1FE4 (R/ ) Peripheral ID1 Register */
  __IM  uint32_t D_PIDR2;                /*!< Offset: 0x1FE8 (R/ ) Peripheral ID2 Register */
  __IM  uint32_t D_PIDR3;                /*!< Offset: 0x1FEC (R/ ) Peripheral ID3 Register */
  __IM  uint32_t D_CIDR0;                /*!< Offset: 0x1FF0 (R/ ) Component ID0 Register */
  __IM  uint32_t D_CIDR1;                /*!< Offset: 0x1FF4 (R/ ) Component ID1 Register */
  __IM  uint32_t D_CIDR2;                /*!< Offset: 0x1FF8 (R/ ) Component ID2 Register */
  __IM  uint32_t D_CIDR3;                /*!< Offset: 0x1FFC (R/ ) Component ID3 Register */

  __IOM uint32_t C_CTLR;                 /*!< Offset: 0x2000 (R/W) CPU Interface Control Register */
  __IOM uint32_t C_PMR;                  /*!< Offset: 0x2004 (R/W) Interrupt Priority Mask Register */
  __IOM uint32_t C_BPR;                  /*!< Offset: 0x2008 (R/W) Binary Point Register */
  __IM  uint32_t C_IAR;                  /*!< Offset: 0x200C (R/ ) Interrupt Acknowledge Register */
  __OM  uint32_t C_EOIR;                 /*!< Offset: 0x2010 ( /W) End Of Interrupt Register */
  __IM  uint32_t C_RPR;                  /*!< Offset: 0x2014 (R/ ) Running Priority Register */
  __IM  uint32_t C_HPPIR;                /*!< Offset: 0x2018 (R/ ) Highest Priority Pending Interrupt Register */
  __IOM uint32_t C_ABPR;                 /*!< Offset: 0x201C (R/W) Aliased Binary Point Register */
  __IM  uint32_t C_AIAR;                 /*!< Offset: 0x2020 (R/ ) Aliased Interrupt Acknowledge Register */
  __OM  uint32_t C_AEOIR;                /*!< Offset: 0x2024 ( /W) Aliased End Of Interrupt Register */
  __IM  uint32_t C_AHPPIR;               /*!< Offset: 0x2028 (R/ ) Aliased Highest Priority Pending Interrupt Register */
        uint32_t RESERVED15[41];
  __IOM uint32_t C_APR0;                 /*!< Offset: 0x20D0 (R/W) Active Priority Register */
        uint32_t RESERVED16[3];
  __IOM uint32_t C_NSAPR0;               /*!< Offset: 0x20E0 (R/W) Non-secure Active Priority Register */
        uint32_t RESERVED17[6];
  __IM  uint32_t C_IIDR;                 /*!< Offset: 0x20FC (R/ ) CPU Interface Identification Register */
        uint32_t RESERVED18[960];
  __OM  uint32_t C_DIR;                  /*!< Offset: 0x3000 ( /W) Deactivate Interrupt Register */
} GIC_Type;


/* For simplicity, we only use group0 of GIC */
FORCEDINLINE __STATIC_INLINE void GIC_Init(void)
{
  uint32_t i;
  uint32_t irqRegs;
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  irqRegs = (gic->D_TYPER & 0x1FUL) + 1;

  /* On POR, all SPI is in group 0, level-sensitive and using 1-N model */

  /* Disable all PPI, SGI and SPI */
  for (i = 0; i < irqRegs; i++)
    gic->D_ICENABLER[i] = 0xFFFFFFFFUL;

  /* Make all interrupts have higher priority */
  gic->C_PMR = (0xFFUL << (8 - __GIC_PRIO_BITS)) & 0xFFUL;

  /* No subpriority, all priority level allows preemption */
  gic->C_BPR = 7 - __GIC_PRIO_BITS;

  /* Enable group0 distribution */
  gic->D_CTLR = 1UL;

  /* Enable group0 signaling */
  gic->C_CTLR = 1UL;
}

FORCEDINLINE __STATIC_INLINE void GIC_EnableIRQ(IRQn_Type IRQn)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  gic->D_ISENABLER[((uint32_t)(int32_t)IRQn) >> 5] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

FORCEDINLINE __STATIC_INLINE void GIC_DisableIRQ(IRQn_Type IRQn)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  gic->D_ICENABLER[((uint32_t)(int32_t)IRQn) >> 5] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/* Return IRQ number (and CPU source in SGI case) */
FORCEDINLINE __STATIC_INLINE uint32_t GIC_AcknowledgeIRQ(void)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  return gic->C_IAR & 0x1FFFUL;
}

/* value should be got from GIC_AcknowledgeIRQ() */
FORCEDINLINE __STATIC_INLINE void GIC_DeactivateIRQ(uint32_t value)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  gic->C_EOIR = value;
}

FORCEDINLINE __STATIC_INLINE uint32_t GIC_GetRunningPriority(void)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  return gic->C_RPR & 0xFFUL;
}

FORCEDINLINE __STATIC_INLINE void GIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  gic->C_BPR = PriorityGroup & 0x7UL;
}

FORCEDINLINE __STATIC_INLINE uint32_t GIC_GetPriorityGrouping(void)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  return gic->C_BPR & 0x7UL;
}

FORCEDINLINE __STATIC_INLINE void GIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  gic->D_IPRIORITYR[((uint32_t)(int32_t)IRQn)] = (uint8_t)((priority << (8UL - __GIC_PRIO_BITS)) & (uint32_t)0xFFUL);
}

FORCEDINLINE __STATIC_INLINE uint32_t GIC_GetPriority(IRQn_Type IRQn)
{
  GIC_Type *gic = (GIC_Type *)(__get_CBAR() & 0xFFFF0000UL);

  return(((uint32_t)gic->D_IPRIORITYR[((uint32_t)(int32_t)IRQn)] >> (8UL - __GIC_PRIO_BITS)));
}

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CA7_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
