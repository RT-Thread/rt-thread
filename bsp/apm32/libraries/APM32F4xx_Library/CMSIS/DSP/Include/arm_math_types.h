/******************************************************************************
 * @file     arm_math_types.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.9.0
 * @date     23 April 2021
 * Target Processor: Cortex-M and Cortex-A cores
 ******************************************************************************/
/*
 * Copyright (c) 2010-2021 Arm Limited or its affiliates. All rights reserved.
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

#ifndef _ARM_MATH_TYPES_H_

#define _ARM_MATH_TYPES_H_

#ifdef   __cplusplus
extern "C"
{
#endif

/* Compiler specific diagnostic adjustment */
#if   defined ( __CC_ARM )

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )

#elif defined ( __GNUC__ )
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  #pragma GCC diagnostic ignored "-Wconversion"
  #pragma GCC diagnostic ignored "-Wunused-parameter"

#elif defined ( __ICCARM__ )

#elif defined ( __TI_ARM__ )

#elif defined ( __CSMC__ )

#elif defined ( __TASKING__ )

#elif defined ( _MSC_VER )

#else
  #error Unknown compiler
#endif


/* Included for instrinsics definitions */
#if defined (_MSC_VER )
#include <stdint.h>
#define __STATIC_FORCEINLINE static __forceinline
#define __STATIC_INLINE static __inline
#define __ALIGNED(x) __declspec(align(x))

#elif defined (__GNUC_PYTHON__)
#include <stdint.h>
#define  __ALIGNED(x) __attribute__((aligned(x)))
#define __STATIC_FORCEINLINE static inline __attribute__((always_inline))
#define __STATIC_INLINE static inline

#else
#include "cmsis_compiler.h"
#endif



#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>

/* evaluate ARM DSP feature */
#if (defined (__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1))
  #define ARM_MATH_DSP                   1
#endif

#if defined(ARM_MATH_NEON)
#include <arm_neon.h>
#if __ARM_FEATURE_FP16_VECTOR_ARITHMETIC
  #if !defined(ARM_MATH_NEON_FLOAT16)
  #define ARM_MATH_NEON_FLOAT16
  #endif
#endif
#endif

#if !defined(ARM_MATH_AUTOVECTORIZE)

#if __ARM_FEATURE_MVE
  #if !defined(ARM_MATH_MVEI)
    #define ARM_MATH_MVEI
  #endif
#endif

#if (__ARM_FEATURE_MVE & 2)
  #if !defined(ARM_MATH_MVEF)
    #define ARM_MATH_MVEF
  #endif
  #if !defined(ARM_MATH_MVE_FLOAT16)
       #define ARM_MATH_MVE_FLOAT16
  #endif
#endif

#endif /*!defined(ARM_MATH_AUTOVECTORIZE)*/


#if defined (ARM_MATH_HELIUM)
  #if !defined(ARM_MATH_MVEF)
    #define ARM_MATH_MVEF
  #endif

  #if !defined(ARM_MATH_MVEI)
    #define ARM_MATH_MVEI
  #endif

  #if !defined(ARM_MATH_MVE_FLOAT16)
       #define ARM_MATH_MVE_FLOAT16
  #endif
#endif



#if   defined ( __CC_ARM )
  /* Enter low optimization region - place directly above function definition */
  #if defined( __ARM_ARCH_7EM__ )
    #define LOW_OPTIMIZATION_ENTER \
       _Pragma ("push")         \
       _Pragma ("O1")
  #else
    #define LOW_OPTIMIZATION_ENTER
  #endif

  /* Exit low optimization region - place directly after end of function definition */
  #if defined ( __ARM_ARCH_7EM__ )
    #define LOW_OPTIMIZATION_EXIT \
       _Pragma ("pop")
  #else
    #define LOW_OPTIMIZATION_EXIT
  #endif

  /* Enter low optimization region - place directly above function definition */
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER

  /* Exit low optimization region - place directly after end of function definition */
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined (__ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
  #define LOW_OPTIMIZATION_ENTER
  #define LOW_OPTIMIZATION_EXIT
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined ( __GNUC__ )
  #define LOW_OPTIMIZATION_ENTER \
       __attribute__(( optimize("-O1") ))
  #define LOW_OPTIMIZATION_EXIT
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined ( __ICCARM__ )
  /* Enter low optimization region - place directly above function definition */
  #if defined ( __ARM_ARCH_7EM__ )
    #define LOW_OPTIMIZATION_ENTER \
       _Pragma ("optimize=low")
  #else
    #define LOW_OPTIMIZATION_ENTER
  #endif

  /* Exit low optimization region - place directly after end of function definition */
  #define LOW_OPTIMIZATION_EXIT

  /* Enter low optimization region - place directly above function definition */
  #if defined ( __ARM_ARCH_7EM__ )
    #define IAR_ONLY_LOW_OPTIMIZATION_ENTER \
       _Pragma ("optimize=low")
  #else
    #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #endif

  /* Exit low optimization region - place directly after end of function definition */
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined ( __TI_ARM__ )
  #define LOW_OPTIMIZATION_ENTER
  #define LOW_OPTIMIZATION_EXIT
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined ( __CSMC__ )
  #define LOW_OPTIMIZATION_ENTER
  #define LOW_OPTIMIZATION_EXIT
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined ( __TASKING__ )
  #define LOW_OPTIMIZATION_ENTER
  #define LOW_OPTIMIZATION_EXIT
  #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
  #define IAR_ONLY_LOW_OPTIMIZATION_EXIT

#elif defined ( _MSC_VER ) || defined(__GNUC_PYTHON__)
      #define LOW_OPTIMIZATION_ENTER
      #define LOW_OPTIMIZATION_EXIT
      #define IAR_ONLY_LOW_OPTIMIZATION_ENTER
      #define IAR_ONLY_LOW_OPTIMIZATION_EXIT
#endif



/* Compiler specific diagnostic adjustment */
#if   defined ( __CC_ARM )

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )

#elif defined ( __GNUC__ )
#pragma GCC diagnostic pop

#elif defined ( __ICCARM__ )

#elif defined ( __TI_ARM__ )

#elif defined ( __CSMC__ )

#elif defined ( __TASKING__ )

#elif defined ( _MSC_VER )

#else
  #error Unknown compiler
#endif

#ifdef   __cplusplus
}
#endif

#if __ARM_FEATURE_MVE
#include <arm_mve.h>
#endif

#ifdef   __cplusplus
extern "C"
{
#endif

 /**
   * @brief 8-bit fractional data type in 1.7 format.
   */
  typedef int8_t q7_t;

  /**
   * @brief 16-bit fractional data type in 1.15 format.
   */
  typedef int16_t q15_t;

  /**
   * @brief 32-bit fractional data type in 1.31 format.
   */
  typedef int32_t q31_t;

  /**
   * @brief 64-bit fractional data type in 1.63 format.
   */
  typedef int64_t q63_t;

  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float float32_t;

  /**
   * @brief 64-bit floating-point type definition.
   */
  typedef double float64_t;

  /**
   * @brief vector types
   */
#if defined(ARM_MATH_NEON) || (defined (ARM_MATH_MVEI)  && !defined(ARM_MATH_AUTOVECTORIZE))
  /**
   * @brief 64-bit fractional 128-bit vector data type in 1.63 format
   */
  typedef int64x2_t q63x2_t;

  /**
   * @brief 32-bit fractional 128-bit vector data type in 1.31 format.
   */
  typedef int32x4_t q31x4_t;

  /**
   * @brief 16-bit fractional 128-bit vector data type with 16-bit alignment in 1.15 format.
   */
  typedef __ALIGNED(2) int16x8_t q15x8_t;

 /**
   * @brief 8-bit fractional 128-bit vector data type with 8-bit alignment in 1.7 format.
   */
  typedef __ALIGNED(1) int8x16_t q7x16_t;

    /**
   * @brief 32-bit fractional 128-bit vector pair data type in 1.31 format.
   */
  typedef int32x4x2_t q31x4x2_t;

  /**
   * @brief 32-bit fractional 128-bit vector quadruplet data type in 1.31 format.
   */
  typedef int32x4x4_t q31x4x4_t;

  /**
   * @brief 16-bit fractional 128-bit vector pair data type in 1.15 format.
   */
  typedef int16x8x2_t q15x8x2_t;

  /**
   * @brief 16-bit fractional 128-bit vector quadruplet data type in 1.15 format.
   */
  typedef int16x8x4_t q15x8x4_t;

  /**
   * @brief 8-bit fractional 128-bit vector pair data type in 1.7 format.
   */
  typedef int8x16x2_t q7x16x2_t;

  /**
   * @brief 8-bit fractional 128-bit vector quadruplet data type in 1.7 format.
   */
   typedef int8x16x4_t q7x16x4_t;

  /**
   * @brief 32-bit fractional data type in 9.23 format.
   */
  typedef int32_t q23_t;

  /**
   * @brief 32-bit fractional 128-bit vector data type in 9.23 format.
   */
  typedef int32x4_t q23x4_t;

  /**
   * @brief 64-bit status 128-bit vector data type.
   */
  typedef int64x2_t status64x2_t;

  /**
   * @brief 32-bit status 128-bit vector data type.
   */
  typedef int32x4_t status32x4_t;

  /**
   * @brief 16-bit status 128-bit vector data type.
   */
  typedef int16x8_t status16x8_t;

  /**
   * @brief 8-bit status 128-bit vector data type.
   */
  typedef int8x16_t status8x16_t;


#endif

#if defined(ARM_MATH_NEON) || (defined(ARM_MATH_MVEF)  && !defined(ARM_MATH_AUTOVECTORIZE)) /* floating point vector*/
  /**
   * @brief 32-bit floating-point 128-bit vector type
   */
  typedef float32x4_t f32x4_t;

  /**
   * @brief 32-bit floating-point 128-bit vector pair data type
   */
  typedef float32x4x2_t f32x4x2_t;

  /**
   * @brief 32-bit floating-point 128-bit vector quadruplet data type
   */
  typedef float32x4x4_t f32x4x4_t;

  /**
   * @brief 32-bit ubiquitous 128-bit vector data type
   */
  typedef union _any32x4_t
  {
      float32x4_t     f;
      int32x4_t       i;
  } any32x4_t;

#endif

#if defined(ARM_MATH_NEON)
  /**
   * @brief 32-bit fractional 64-bit vector data type in 1.31 format.
   */
  typedef int32x2_t  q31x2_t;

  /**
   * @brief 16-bit fractional 64-bit vector data type in 1.15 format.
   */
  typedef  __ALIGNED(2) int16x4_t q15x4_t;

  /**
   * @brief 8-bit fractional 64-bit vector data type in 1.7 format.
   */
  typedef  __ALIGNED(1) int8x8_t q7x8_t;

  /**
   * @brief 32-bit float 64-bit vector data type.
   */
  typedef float32x2_t  f32x2_t;

  /**
   * @brief 32-bit floating-point 128-bit vector triplet data type
   */
  typedef float32x4x3_t f32x4x3_t;


  /**
   * @brief 32-bit fractional 128-bit vector triplet data type in 1.31 format
   */
  typedef int32x4x3_t q31x4x3_t;

  /**
   * @brief 16-bit fractional 128-bit vector triplet data type in 1.15 format
   */
  typedef int16x8x3_t q15x8x3_t;

  /**
   * @brief 8-bit fractional 128-bit vector triplet data type in 1.7 format
   */
  typedef int8x16x3_t q7x16x3_t;

  /**
   * @brief 32-bit floating-point 64-bit vector pair data type
   */
  typedef float32x2x2_t f32x2x2_t;

  /**
   * @brief 32-bit floating-point 64-bit vector triplet data type
   */
  typedef float32x2x3_t f32x2x3_t;

  /**
   * @brief 32-bit floating-point 64-bit vector quadruplet data type
   */
  typedef float32x2x4_t f32x2x4_t;


  /**
   * @brief 32-bit fractional 64-bit vector pair data type in 1.31 format
   */
  typedef int32x2x2_t q31x2x2_t;

  /**
   * @brief 32-bit fractional 64-bit vector triplet data type in 1.31 format
   */
  typedef int32x2x3_t q31x2x3_t;

  /**
   * @brief 32-bit fractional 64-bit vector quadruplet data type in 1.31 format
   */
  typedef int32x4x3_t q31x2x4_t;

  /**
   * @brief 16-bit fractional 64-bit vector pair data type in 1.15 format
   */
  typedef int16x4x2_t q15x4x2_t;

  /**
   * @brief 16-bit fractional 64-bit vector triplet data type in 1.15 format
   */
  typedef int16x4x2_t q15x4x3_t;

  /**
   * @brief 16-bit fractional 64-bit vector quadruplet data type in 1.15 format
   */
  typedef int16x4x3_t q15x4x4_t;

  /**
   * @brief 8-bit fractional 64-bit vector pair data type in 1.7 format
   */
  typedef int8x8x2_t q7x8x2_t;

  /**
   * @brief 8-bit fractional 64-bit vector triplet data type in 1.7 format
   */
  typedef int8x8x3_t q7x8x3_t;

  /**
   * @brief 8-bit fractional 64-bit vector quadruplet data type in 1.7 format
   */
  typedef int8x8x4_t q7x8x4_t;

  /**
   * @brief 32-bit ubiquitous 64-bit vector data type
   */
  typedef union _any32x2_t
  {
      float32x2_t     f;
      int32x2_t       i;
  } any32x2_t;


  /**
   * @brief 32-bit status 64-bit vector data type.
   */
  typedef int32x4_t status32x2_t;

  /**
   * @brief 16-bit status 64-bit vector data type.
   */
  typedef int16x8_t status16x4_t;

  /**
   * @brief 8-bit status 64-bit vector data type.
   */
  typedef int8x16_t status8x8_t;

#endif





#define F64_MAX   ((float64_t)DBL_MAX)
#define F32_MAX   ((float32_t)FLT_MAX)



#define F64_MIN   (-DBL_MAX)
#define F32_MIN   (-FLT_MAX)



#define F64_ABSMAX   ((float64_t)DBL_MAX)
#define F32_ABSMAX   ((float32_t)FLT_MAX)



#define F64_ABSMIN   ((float64_t)0.0)
#define F32_ABSMIN   ((float32_t)0.0)


#define Q31_MAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_MAX   ((q15_t)(0x7FFF))
#define Q7_MAX    ((q7_t)(0x7F))
#define Q31_MIN   ((q31_t)(0x80000000L))
#define Q15_MIN   ((q15_t)(0x8000))
#define Q7_MIN    ((q7_t)(0x80))

#define Q31_ABSMAX   ((q31_t)(0x7FFFFFFFL))
#define Q15_ABSMAX   ((q15_t)(0x7FFF))
#define Q7_ABSMAX    ((q7_t)(0x7F))
#define Q31_ABSMIN   ((q31_t)0)
#define Q15_ABSMIN   ((q15_t)0)
#define Q7_ABSMIN    ((q7_t)0)

  /* Dimension C vector space */
  #define CMPLX_DIM 2

  /**
   * @brief Error status returned by some functions in the library.
   */

  typedef enum
  {
    ARM_MATH_SUCCESS                 =  0,        /**< No error */
    ARM_MATH_ARGUMENT_ERROR          = -1,        /**< One or more arguments are incorrect */
    ARM_MATH_LENGTH_ERROR            = -2,        /**< Length of data buffer is incorrect */
    ARM_MATH_SIZE_MISMATCH           = -3,        /**< Size of matrices is not compatible with the operation */
    ARM_MATH_NANINF                  = -4,        /**< Not-a-number (NaN) or infinity is generated */
    ARM_MATH_SINGULAR                = -5,        /**< Input matrix is singular and cannot be inverted */
    ARM_MATH_TEST_FAILURE            = -6,        /**< Test Failed */
    ARM_MATH_DECOMPOSITION_FAILURE   = -7         /**< Decomposition Failed */
  } arm_status;


#ifdef   __cplusplus
}
#endif

#endif /*ifndef _ARM_MATH_TYPES_H_ */
