/******************************************************************************
 * @file     arm_nn_math_types.h
 * @brief    Compiler include and basic types
 * @version  V1.1.0
 * @date     09 March 2022
 * Target Processor: Cortex-M
 ******************************************************************************/
/*
 * Copyright (c) 2010-2022 Arm Limited or its affiliates.
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

/**
   Copied from CMSIS/DSP/arm_math_types.h and modified
*/

#ifndef _ARM_NN_MATH_TYPES_H_

#define _ARM_NN_MATH_TYPES_H_

/* DSP inlcude for enum arm_status. */
#include "arm_math_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Compiler specific diagnostic adjustment */
#if defined(__CC_ARM)

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)

#elif defined(__GNUC__)

#elif defined(__ICCARM__)

#elif defined(__TI_ARM__)

#elif defined(__CSMC__)

#elif defined(__TASKING__)

#elif defined(_MSC_VER)

#else
#error Unknown compiler
#endif

/* Included for instrinsics definitions */
#if defined(_MSC_VER)
#include <stdint.h>
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE static __forceinline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __inline
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __declspec(align(x))
#endif

#elif defined(__GNUC_PYTHON__)
#include <stdint.h>
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE static inline __attribute__((always_inline))
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

#else
#include "cmsis_compiler.h"
#endif

#include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>

/* evaluate ARM DSP feature */
#if (defined(__ARM_FEATURE_DSP) && (__ARM_FEATURE_DSP == 1))
#ifndef ARM_MATH_DSP
#define ARM_MATH_DSP 1
#endif
#endif

#if __ARM_FEATURE_MVE
#ifndef ARM_MATH_MVEI
#define ARM_MATH_MVEI
#endif
#endif

/* Compiler specific diagnostic adjustment */
#if defined(__CC_ARM)

#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)

#elif defined(__GNUC__)
// #pragma GCC diagnostic pop

#elif defined(__ICCARM__)

#elif defined(__TI_ARM__)

#elif defined(__CSMC__)

#elif defined(__TASKING__)

#elif defined(_MSC_VER)

#else
#error Unknown compiler
#endif

#ifdef __cplusplus
}
#endif

#if __ARM_FEATURE_MVE
#include <arm_mve.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Add necessary typedefs
 */

#define NN_Q31_MAX ((q31_t)(0x7FFFFFFFL))
#define NN_Q15_MAX ((q15_t)(0x7FFF))
#define NN_Q7_MAX ((q7_t)(0x7F))
#define NN_Q31_MIN ((q31_t)(0x80000000L))
#define NN_Q15_MIN ((q15_t)(0x8000))
#define NN_Q7_MIN ((q7_t)(0x80))

/**
 * @brief Error status returned by some functions in the library.
 */

typedef enum
{
    ARM_CMSIS_NN_SUCCESS = 0,        /**< No error */
    ARM_CMSIS_NN_ARG_ERROR = -1,     /**< One or more arguments are incorrect */
    ARM_CMSIS_NN_NO_IMPL_ERROR = -2, /**<  No implementation available */
} arm_cmsis_nn_status;

#ifdef __cplusplus
}
#endif

#endif /*ifndef _ARM_NN_MATH_TYPES_H_ */
