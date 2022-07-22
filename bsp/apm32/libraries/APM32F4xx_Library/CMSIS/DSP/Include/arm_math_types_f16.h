/******************************************************************************
 * @file     arm_math_types_f16.h
 * @brief    Public header file for f16 function of the CMSIS DSP Library
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

#ifndef _ARM_MATH_TYPES_F16_H
#define _ARM_MATH_TYPES_F16_H

#include "arm_math_types.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if !defined( __CC_ARM )

/**
 * @brief 16-bit floating-point type definition.
 * This is already defined in arm_mve.h
 *
 * This is not fully supported on ARM AC5.
 */

/*

Check if the type __fp16 is available.
If it is not available, f16 version of the kernels
won't be built.

*/
#if !(__ARM_FEATURE_MVE & 2)
  #if !defined(DISABLEFLOAT16)
    #if defined(__ARM_FP16_FORMAT_IEEE) || defined(__ARM_FP16_FORMAT_ALTERNATIVE)
      typedef __fp16 float16_t;
      #define ARM_FLOAT16_SUPPORTED
    #endif
  #endif
#else
  /* When Vector float16, this flag is always defined and can't be disabled */
  #define ARM_FLOAT16_SUPPORTED
#endif

#if defined(ARM_MATH_NEON) || (defined(ARM_MATH_MVEF)  && !defined(ARM_MATH_AUTOVECTORIZE)) /* floating point vector*/

#if defined(ARM_MATH_MVE_FLOAT16) || defined(ARM_MATH_NEON_FLOAT16)

  /**
   * @brief 16-bit floating-point 128-bit vector data type
   */
  typedef __ALIGNED(2) float16x8_t f16x8_t;

  /**
   * @brief 16-bit floating-point 128-bit vector pair data type
   */
  typedef float16x8x2_t f16x8x2_t;

  /**
   * @brief 16-bit floating-point 128-bit vector quadruplet data type
   */
  typedef float16x8x4_t f16x8x4_t;

  /**
   * @brief 16-bit ubiquitous 128-bit vector data type
   */
  typedef union _any16x8_t
  {
      float16x8_t     f;
      int16x8_t       i;
  } any16x8_t;
#endif

#endif

#if defined(ARM_MATH_NEON)


#if defined(ARM_MATH_NEON_FLOAT16)
  /**
   * @brief 16-bit float 64-bit vector data type.
   */
  typedef  __ALIGNED(2) float16x4_t f16x4_t;

  /**
   * @brief 16-bit floating-point 128-bit vector triplet data type
   */
  typedef float16x8x3_t f16x8x3_t;

  /**
   * @brief 16-bit floating-point 64-bit vector pair data type
   */
  typedef float16x4x2_t f16x4x2_t;

  /**
   * @brief 16-bit floating-point 64-bit vector triplet data type
   */
  typedef float16x4x3_t f16x4x3_t;

  /**
   * @brief 16-bit floating-point 64-bit vector quadruplet data type
   */
  typedef float16x4x4_t f16x4x4_t;

  /**
   * @brief 16-bit ubiquitous 64-bit vector data type
   */
  typedef union _any16x4_t
  {
      float16x4_t     f;
      int16x4_t       i;
  } any16x4_t;
#endif

#endif



#if defined(ARM_FLOAT16_SUPPORTED)
#define F16_MAX   ((float16_t)__FLT16_MAX__)
#define F16_MIN   (-(float16_t)__FLT16_MAX__)

#define F16_ABSMAX   ((float16_t)__FLT16_MAX__)
#define F16_ABSMIN   ((float16_t)0.0f16)

#define F16INFINITY ((float16_t)__builtin_inf())

#endif /* ARM_FLOAT16_SUPPORTED*/
#endif /* !defined( __CC_ARM ) */

#ifdef   __cplusplus
}
#endif

#endif /* _ARM_MATH_F16_H */


