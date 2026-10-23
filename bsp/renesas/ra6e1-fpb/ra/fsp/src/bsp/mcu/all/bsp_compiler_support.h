/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

#ifndef BSP_COMPILER_SUPPORT_H
 #define BSP_COMPILER_SUPPORT_H

 #if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3))
  #include "arm_cmse.h"
 #endif

 #ifdef __cplusplus
extern "C" {
 #endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #if defined(__ARMCC_VERSION)          /* AC6 compiler */

/* The AC6 linker requires uninitialized code to be placed in a section that starts with ".bss." Without this, load
 * memory (ROM) is reserved unnecessarily. */
  #define BSP_UNINIT_SECTION_PREFIX         ".bss"
  #ifndef BSP_SECTION_HEAP
   #define BSP_SECTION_HEAP                 BSP_UNINIT_SECTION_PREFIX ".heap"
  #endif
  #define BSP_DONT_REMOVE                   __attribute__((used))
  #define BSP_ATTRIBUTE_STACKLESS           __attribute__((naked))
  #define BSP_FORCE_INLINE                  __attribute__((always_inline))
 #elif   defined(__GNUC__)             /* GCC compiler */
  #define BSP_UNINIT_SECTION_PREFIX
  #ifndef BSP_SECTION_HEAP
   #define BSP_SECTION_HEAP                 ".heap"
  #endif
  #define BSP_DONT_REMOVE
  #define BSP_ATTRIBUTE_STACKLESS           __attribute__((naked))
  #define BSP_FORCE_INLINE                  __attribute__((always_inline))
 #elif defined(__ICCARM__)             /* IAR compiler */
  #define BSP_UNINIT_SECTION_PREFIX
  #ifndef BSP_SECTION_HEAP
   #define BSP_SECTION_HEAP                 "HEAP"
  #endif
  #define BSP_DONT_REMOVE                   __root
  #define BSP_ATTRIBUTE_STACKLESS           __stackless
  #define BSP_FORCE_INLINE                  _Pragma("inline=forced")
 #endif

 #ifndef BSP_SECTION_STACK
  #define BSP_SECTION_STACK                 BSP_UNINIT_SECTION_PREFIX ".stack"
 #endif
 #ifndef BSP_SECTION_FLASH_GAP
  #define BSP_SECTION_FLASH_GAP
 #endif
 #define BSP_SECTION_NOINIT                 BSP_UNINIT_SECTION_PREFIX ".noinit"
 #define BSP_SECTION_FIXED_VECTORS          ".fixed_vectors"
 #define BSP_SECTION_APPLICATION_VECTORS    ".application_vectors"
 #define BSP_SECTION_ROM_REGISTERS          ".rom_registers"
 #define BSP_SECTION_ID_CODE                ".id_code"

/* Compiler neutral macros. */
 #define BSP_PLACE_IN_SECTION(x)    __attribute__((section(x))) __attribute__((__used__))

 #define BSP_ALIGN_VARIABLE(x)      __attribute__((aligned(x)))

 #define BSP_PACKED                    __attribute__((aligned(1))) // DEPRECATED

 #define BSP_WEAK_REFERENCE            __attribute__((weak))

/** Stacks (and heap) must be sized and aligned to an integer multiple of this number. */
 #define BSP_STACK_ALIGNMENT           (8)

/***********************************************************************************************************************
 * TrustZone definitions
 **********************************************************************************************************************/
 #if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3)) && !defined(__clang_analyzer__)
  #if defined(__ICCARM__)              /* IAR compiler */
   #define BSP_CMSE_NONSECURE_CALL     __cmse_nonsecure_call
   #define BSP_CMSE_NONSECURE_ENTRY    __cmse_nonsecure_entry
  #else
   #define BSP_CMSE_NONSECURE_CALL     __attribute__((cmse_nonsecure_call))
   #define BSP_CMSE_NONSECURE_ENTRY    __attribute__((cmse_nonsecure_entry))
  #endif
 #else
  #define BSP_CMSE_NONSECURE_CALL
  #define BSP_CMSE_NONSECURE_ENTRY
 #endif

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/** @} (end of addtogroup BSP_MCU) */

 #ifdef __cplusplus
}
 #endif

#endif
