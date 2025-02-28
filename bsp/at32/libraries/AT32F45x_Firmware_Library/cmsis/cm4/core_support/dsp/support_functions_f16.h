/******************************************************************************
 * @file     support_functions_f16.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.10.0
 * @date     08 July 2021
 * Target Processor: Cortex-M and Cortex-A cores
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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


#ifndef _SUPPORT_FUNCTIONS_F16_H_
#define _SUPPORT_FUNCTIONS_F16_H_

#include "arm_math_types_f16.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if defined(ARM_FLOAT16_SUPPORTED)

  /**
   * @brief  Copies the elements of a floating-point vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
void arm_copy_f16(const float16_t * pSrc, float16_t * pDst, uint32_t blockSize);

  /**
   * @brief  Fills a constant value into a floating-point vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
void arm_fill_f16(float16_t value, float16_t * pDst, uint32_t blockSize);

/**
   * @brief Converts the elements of the floating-point vector to Q31 vector.
   * @param[in]  pSrc       points to the f16 input vector
   * @param[out] pDst       points to the q15 output vector
   * @param[in]  blockSize  length of the input vector
   */
void arm_f16_to_q15(const float16_t * pSrc, q15_t * pDst, uint32_t blockSize);

/**
   * @brief Converts the elements of the floating-point vector to Q31 vector.
   * @param[in]  pSrc       points to the q15 input vector
   * @param[out] pDst       points to the f16 output vector
   * @param[in]  blockSize  length of the input vector
   */
void arm_q15_to_f16(const q15_t * pSrc, float16_t * pDst, uint32_t blockSize);


/**
   * @brief Converts the elements of the floating-point vector to Q31 vector.
   * @param[in]  pSrc       points to the f32 input vector
   * @param[out] pDst       points to the f16 output vector
   * @param[in]  blockSize  length of the input vector
   */
void arm_float_to_f16(const float32_t * pSrc, float16_t * pDst, uint32_t blockSize);

/**
   * @brief Converts the elements of the floating-point vector to Q31 vector.
   * @param[in]  pSrc       points to the f16 input vector
   * @param[out] pDst       points to the f32 output vector
   * @param[in]  blockSize  length of the input vector
   */
void arm_f16_to_float(const float16_t * pSrc, float32_t * pDst, uint32_t blockSize);

/**
 * @brief Weighted sum
 *
 *
 * @param[in]    *in           Array of input values.
 * @param[in]    *weigths      Weights
 * @param[in]    blockSize     Number of samples in the input array.
 * @return Weighted sum
 *
 */
float16_t arm_weighted_sum_f16(const float16_t *in
  , const float16_t *weigths
  , uint32_t blockSize);

/**
 * @brief Barycenter
 *
 *
 * @param[in]    in         List of vectors
 * @param[in]    weights    Weights of the vectors
 * @param[out]   out        Barycenter
 * @param[in]    nbVectors  Number of vectors
 * @param[in]    vecDim     Dimension of space (vector dimension)
 * @return       None
 *
 */
void arm_barycenter_f16(const float16_t *in
  , const float16_t *weights
  , float16_t *out
  , uint32_t nbVectors
  , uint32_t vecDim);


/**
  @ingroup groupSupport
 */

/**
 * @defgroup typecast Typecasting
 */

/**
  @addtogroup typecast
  @{
 */

/**
   * @brief  Interpret a f16 as an s16 value
   * @param[in] x  input value.
   * @return  return value.
   *
   * @par    Description
   *            It is a typecast. No conversion of the float to int is done.
   *            The memcpy will be optimized out by the compiler.
   *            memcpy is used to prevent type punning issues.
   *            With gcc, -fno-builtins MUST not be used or the
   *            memcpy will not be optimized out.
   */
__STATIC_INLINE int16_t arm_typecast_s16_f16(float16_t x)
{
   int16_t res;
   res=*(int16_t*)memcpy((char*)&res,(char*)&x,sizeof(float16_t));
   return(res);
}

/**
   * @brief  Interpret an s16 as an f16 value
   * @param[in] x  input value.
   * @return  return value.
   *
   * @par    Description
   *            It is a typecast. No conversion of the int to float is done.
   *            The memcpy will be optimized out by the compiler.
   *            memcpy is used to prevent type punning issues.
   *            With gcc, -fno-builtins MUST not be used or the
   *            memcpy will not be optimized out.
   */
__STATIC_INLINE float16_t arm_typecast_f16_s16(int16_t x)
{
   float16_t res;
   res=*(float16_t*)memcpy((char*)&res,(char*)&x,sizeof(int16_t));
   return(res);
}


/**
  @} end of typecast group
 */


#endif /*defined(ARM_FLOAT16_SUPPORTED)*/
#ifdef   __cplusplus
}
#endif

#endif /* ifndef _SUPPORT_FUNCTIONS_F16_H_ */
