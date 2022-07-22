/******************************************************************************
 * @file     arm_math_memory.h
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

#ifndef _ARM_MATH_MEMORY_H_

#define _ARM_MATH_MEMORY_H_

#include "arm_math_types.h"


#ifdef   __cplusplus
extern "C"
{
#endif

/**
  @brief definition to read/write two 16 bit values.
  @deprecated
 */
#if   defined ( __CC_ARM )
  #define __SIMD32_TYPE int32_t __packed
#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
  #define __SIMD32_TYPE int32_t
#elif defined ( __GNUC__ )
  #define __SIMD32_TYPE int32_t
#elif defined ( __ICCARM__ )
  #define __SIMD32_TYPE int32_t __packed
#elif defined ( __TI_ARM__ )
  #define __SIMD32_TYPE int32_t
#elif defined ( __CSMC__ )
  #define __SIMD32_TYPE int32_t
#elif defined ( __TASKING__ )
  #define __SIMD32_TYPE __un(aligned) int32_t
#elif defined(_MSC_VER )
  #define __SIMD32_TYPE int32_t
#else
  #error Unknown compiler
#endif

#define __SIMD32(addr)        (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ( (__SIMD32_TYPE * )   (addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE * )   (addr))
#define __SIMD64(addr)        (*(      int64_t **) & (addr))


/* SIMD replacement */


/**
  @brief         Read 2 Q15 from Q15 pointer.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q15x2 (
  q15_t * pQ15)
{
  q31_t val;

#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (&val, pQ15, 4);
#else
  val = (pQ15[1] << 16) | (pQ15[0] & 0x0FFFF) ;
#endif

  return (val);
}

/**
  @brief         Read 2 Q15 from Q15 pointer and increment pointer afterwards.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q15x2_ia (
  q15_t ** pQ15)
{
  q31_t val;

#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (&val, *pQ15, 4);
#else
  val = ((*pQ15)[1] << 16) | ((*pQ15)[0] & 0x0FFFF);
#endif

 *pQ15 += 2;
 return (val);
}

/**
  @brief         Read 2 Q15 from Q15 pointer and decrement pointer afterwards.
  @param[in]     pQ15      points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q15x2_da (
  q15_t ** pQ15)
{
  q31_t val;

#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (&val, *pQ15, 4);
#else
  val = ((*pQ15)[1] << 16) | ((*pQ15)[0] & 0x0FFFF);
#endif

  *pQ15 -= 2;
  return (val);
}

/**
  @brief         Write 2 Q15 to Q15 pointer and increment pointer afterwards.
  @param[in]     pQ15      points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q15x2_ia (
  q15_t ** pQ15,
  q31_t    value)
{
  q31_t val = value;
#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (*pQ15, &val, 4);
#else
  (*pQ15)[0] = (val & 0x0FFFF);
  (*pQ15)[1] = (val >> 16) & 0x0FFFF;
#endif

 *pQ15 += 2;
}

/**
  @brief         Write 2 Q15 to Q15 pointer.
  @param[in]     pQ15      points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q15x2 (
  q15_t * pQ15,
  q31_t   value)
{
  q31_t val = value;

#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (pQ15, &val, 4);
#else
  pQ15[0] = val & 0x0FFFF;
  pQ15[1] = val >> 16;
#endif
}


/**
  @brief         Read 4 Q7 from Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q7x4_ia (
  q7_t ** pQ7)
{
  q31_t val;


#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (&val, *pQ7, 4);
#else
  val =(((*pQ7)[3] & 0x0FF) << 24)  | (((*pQ7)[2] & 0x0FF) << 16)  | (((*pQ7)[1] & 0x0FF) << 8)  | ((*pQ7)[0] & 0x0FF);
#endif

  *pQ7 += 4;

  return (val);
}

/**
  @brief         Read 4 Q7 from Q7 pointer and decrement pointer afterwards.
  @param[in]     pQ7       points to input value
  @return        Q31 value
 */
__STATIC_FORCEINLINE q31_t read_q7x4_da (
  q7_t ** pQ7)
{
  q31_t val;
#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (&val, *pQ7, 4);
#else
  val = ((((*pQ7)[3]) & 0x0FF) << 24) | ((((*pQ7)[2]) & 0x0FF) << 16)   | ((((*pQ7)[1]) & 0x0FF) << 8)  | ((*pQ7)[0] & 0x0FF);
#endif
  *pQ7 -= 4;

  return (val);
}

/**
  @brief         Write 4 Q7 to Q7 pointer and increment pointer afterwards.
  @param[in]     pQ7       points to input value
  @param[in]     value     Q31 value
  @return        none
 */
__STATIC_FORCEINLINE void write_q7x4_ia (
  q7_t ** pQ7,
  q31_t   value)
{
  q31_t val = value;
#ifdef __ARM_FEATURE_UNALIGNED
  memcpy (*pQ7, &val, 4);
#else
  (*pQ7)[0] = val & 0x0FF;
  (*pQ7)[1] = (val >> 8) & 0x0FF;
  (*pQ7)[2] = (val >> 16) & 0x0FF;
  (*pQ7)[3] = (val >> 24) & 0x0FF;

#endif
  *pQ7 += 4;
}


#ifdef   __cplusplus
}
#endif

#endif /*ifndef _ARM_MATH_MEMORY_H_ */
