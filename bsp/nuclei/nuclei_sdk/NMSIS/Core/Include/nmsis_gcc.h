/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
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

#ifndef __NMSIS_GCC_H__
#define __NMSIS_GCC_H__
/*!
 * @file     nmsis_gcc.h
 * @brief    NMSIS compiler GCC header file
 */
#include <stdint.h>
#include "riscv_encoding.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* #########################  Startup and Lowlevel Init  ######################## */
/**
 * \defgroup NMSIS_Core_CompilerControl    Compiler Control
 * \ingroup  NMSIS_Core
 * \brief    Compiler agnostic \#define symbols for generic c/c++ source code
 * \details
 *
 * The NMSIS-Core provides the header file <b>nmsis_compiler.h</b> with consistent \#define symbols for generate C or C++ source files that should be compiler agnostic.
 * Each NMSIS compliant compiler should support the functionality described in this section.
 *
 * The header file <b>nmsis_compiler.h</b> is also included by each Device Header File <device.h> so that these definitions are available.
 *   @{
 */
/* ignore some GCC warnings */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* Fallback for __has_builtin */
#ifndef __has_builtin
  #define __has_builtin(x) (0)
#endif

/* NMSIS compiler specific defines */
/** \brief Pass information from the compiler to the assembler. */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif

/** \brief Recommend that function should be inlined by the compiler. */
#ifndef   __INLINE
  #define __INLINE                               inline
#endif

/** \brief Define a static function that may be inlined by the compiler. */
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif

/** \brief Define a static function that should be always inlined by the compiler. */
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif

/** \brief Inform the compiler that a function does not return. */
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif

/** \brief Inform that a variable shall be retained in executable image. */
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif

/** \brief restrict pointer qualifier to enable additional optimizations. */
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif

/** \brief specified the vector size of the variable, measured in bytes */
#ifndef   __VECTOR_SIZE
  #define __VECTOR_SIZE(x)                       __attribute__((vector_size(x)))
#endif

/** \brief Request smallest possible alignment. */
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif

/** \brief Request smallest possible alignment for a structure. */
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif

/** \brief Request smallest possible alignment for a union. */
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif

#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint16_t write access */
  __PACKED_STRUCT T_UINT16_WRITE {
      uint16_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned write of a uint16_t variable. */
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif

#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint16_t read access */
  __PACKED_STRUCT T_UINT16_READ {
      uint16_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned read of a uint16_t variable. */
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif

#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint32_t write access */
  __PACKED_STRUCT T_UINT32_WRITE {
      uint32_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned write of a uint32_t variable. */
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif

#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  /** \brief Packed struct for unaligned uint32_t read access */
  __PACKED_STRUCT T_UINT32_READ {
      uint32_t v;
  };
  #pragma GCC diagnostic pop
  /** \brief Pointer for unaligned read of a uint32_t variable. */
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif

/** \brief Minimum `x` bytes alignment for a variable. */
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif

/** \brief restrict pointer qualifier to enable additional optimizations. */
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif

/** \brief Barrier to prevent compiler from reordering instructions. */
#ifndef   __COMPILER_BARRIER
  #define __COMPILER_BARRIER()                   __ASM volatile("":::"memory")
#endif

/** \brief provide the compiler with branch prediction information, the branch is usually true */
#ifndef   __USUALLY
  #define __USUALLY(exp)                         __builtin_expect((exp), 1)
#endif

/** \brief provide the compiler with branch prediction information, the branch is rarely true */
#ifndef   __RARELY
  #define __RARELY(exp)                          __builtin_expect((exp), 0)
#endif

/** \brief Use this attribute to indicate that the specified function is an interrupt handler. */
#ifndef   __INTERRUPT
  #define __INTERRUPT                            __attribute__((interrupt))
#endif

/** @} */ /* End of Doxygen Group NMSIS_Core_CompilerControl */

/* IO definitions (access restrictions to peripheral registers) */
/**
 * \defgroup NMSIS_Core_PeriphAccess     Peripheral Access
 * \brief  Naming conventions and optional features for accessing peripherals.
 *
 * The section below describes the naming conventions, requirements, and optional features
 * for accessing device specific peripherals.
 * Most of the rules also apply to the core peripherals.
 *
 * The **Device Header File <device.h>** contains typically these definition
 * and also includes the core specific header files.
 *
 * @{
 */
/** \brief Defines 'read only' permissions */
#ifdef __cplusplus
  #define   __I     volatile
#else
  #define   __I     volatile const
#endif
/** \brief Defines 'write only' permissions */
#define     __O     volatile
/** \brief Defines 'read / write' permissions */
#define     __IO    volatile

/* following defines should be used for structure members */
/** \brief Defines 'read only' structure member permissions */
#define     __IM     volatile const
/** \brief Defines 'write only' structure member permissions */
#define     __OM     volatile
/** \brief Defines 'read/write' structure member permissions */
#define     __IOM    volatile

/**
 * \brief   Mask and shift a bit field value for use in a register bit range.
 * \details The macro \ref _VAL2FLD uses the #define's _Pos and _Msk of the related bit
 * field to shift bit-field values for assigning to a register.
 *
 * **Example**:
 * \code
 * ECLIC->CFG = _VAL2FLD(CLIC_CLICCFG_NLBIT, 3);
 * \endcode
 * \param[in] field  Name of the register bit field.
 * \param[in] value  Value of the bit field. This parameter is interpreted as an uint32_t type.
 * \return           Masked and shifted value.
 */
#define _VAL2FLD(field, value)    (((uint32_t)(value) << field ## _Pos) & field ## _Msk)

/**
 * \brief   Mask and shift a register value to extract a bit filed value.
 * \details The macro \ref _FLD2VAL uses the #define's _Pos and _Msk of the related bit
 * field to extract the value of a bit field from a register.
 *
 * **Example**:
 * \code
 * nlbits = _FLD2VAL(CLIC_CLICCFG_NLBIT, ECLIC->CFG);
 * \endcode
 * \param[in] field  Name of the register bit field.
 * \param[in] value  Value of register. This parameter is interpreted as an uint32_t type.
 * \return           Masked and shifted bit field value.
 */
#define _FLD2VAL(field, value)    (((uint32_t)(value) & field ## _Msk) >> field ## _Pos)

/** @} */ /* end of group NMSIS_Core_PeriphAccess */


#ifdef __cplusplus
}
#endif
#endif /* __NMSIS_GCC_H__ */
