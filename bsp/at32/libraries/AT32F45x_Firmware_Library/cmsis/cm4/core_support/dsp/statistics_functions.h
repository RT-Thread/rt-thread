/******************************************************************************
 * @file     statistics_functions.h
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


#ifndef _STATISTICS_FUNCTIONS_H_
#define _STATISTICS_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/basic_math_functions.h"
#include "dsp/fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif


/**
 * @defgroup groupStats Statistics Functions
 */

/**
 * @brief Computation of the LogSumExp
 *
 * In probabilistic computations, the dynamic of the probability values can be very
 * wide because they come from gaussian functions.
 * To avoid underflow and overflow issues, the values are represented by their log.
 * In this representation, multiplying the original exp values is easy : their logs are added.
 * But adding the original exp values is requiring some special handling and it is the
 * goal of the LogSumExp function.
 *
 * If the values are x1...xn, the function is computing:
 *
 * ln(exp(x1) + ... + exp(xn)) and the computation is done in such a way that
 * rounding issues are minimised.
 *
 * The max xm of the values is extracted and the function is computing:
 * xm + ln(exp(x1 - xm) + ... + exp(xn - xm))
 *
 * @param[in]  *in         Pointer to an array of input values.
 * @param[in]  blockSize   Number of samples in the input array.
 * @return LogSumExp
 *
 */


float32_t arm_logsumexp_f32(const float32_t *in, uint32_t blockSize);

/**
 * @brief Dot product with log arithmetic
 *
 * Vectors are containing the log of the samples
 *
 * @param[in]       pSrcA points to the first input vector
 * @param[in]       pSrcB points to the second input vector
 * @param[in]       blockSize number of samples in each vector
 * @param[in]       pTmpBuffer temporary buffer of length blockSize
 * @return The log of the dot product .
 *
 */


float32_t arm_logsumexp_dot_prod_f32(const float32_t * pSrcA,
  const float32_t * pSrcB,
  uint32_t blockSize,
  float32_t *pTmpBuffer);

/**
 * @brief Entropy
 *
 * @param[in]  pSrcA        Array of input values.
 * @param[in]  blockSize    Number of samples in the input array.
 * @return     Entropy      -Sum(p ln p)
 *
 */


float32_t arm_entropy_f32(const float32_t * pSrcA,uint32_t blockSize);


/**
 * @brief Entropy
 *
 * @param[in]  pSrcA        Array of input values.
 * @param[in]  blockSize    Number of samples in the input array.
 * @return     Entropy      -Sum(p ln p)
 *
 */


float64_t arm_entropy_f64(const float64_t * pSrcA, uint32_t blockSize);


/**
 * @brief Kullback-Leibler
 *
 * @param[in]  pSrcA         Pointer to an array of input values for probability distribution A.
 * @param[in]  pSrcB         Pointer to an array of input values for probability distribution B.
 * @param[in]  blockSize     Number of samples in the input array.
 * @return Kullback-Leibler  Divergence D(A || B)
 *
 */
float32_t arm_kullback_leibler_f32(const float32_t * pSrcA
  ,const float32_t * pSrcB
  ,uint32_t blockSize);


/**
 * @brief Kullback-Leibler
 *
 * @param[in]  pSrcA         Pointer to an array of input values for probability distribution A.
 * @param[in]  pSrcB         Pointer to an array of input values for probability distribution B.
 * @param[in]  blockSize     Number of samples in the input array.
 * @return Kullback-Leibler  Divergence D(A || B)
 *
 */
float64_t arm_kullback_leibler_f64(const float64_t * pSrcA,
                const float64_t * pSrcB,
                uint32_t blockSize);


 /**
   * @brief  Sum of the squares of the elements of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_power_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q63_t * pResult);


  /**
   * @brief  Sum of the squares of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_power_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);


  /**
   * @brief  Sum of the squares of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_power_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);


  /**
   * @brief  Sum of the squares of the elements of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_power_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q63_t * pResult);


  /**
   * @brief  Sum of the squares of the elements of a Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_power_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);


  /**
   * @brief  Mean value of a Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_mean_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult);


  /**
   * @brief  Mean value of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_mean_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);


  /**
   * @brief  Mean value of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_mean_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);


  /**
   * @brief  Mean value of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_mean_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);


  /**
   * @brief  Mean value of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_mean_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);


  /**
   * @brief  Variance of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_var_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);


  /**
   * @brief  Variance of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_var_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);


  /**
   * @brief  Variance of the elements of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_var_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);


  /**
   * @brief  Variance of the elements of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_var_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);


  /**
   * @brief  Root Mean Square of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_rms_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);


  /**
   * @brief  Root Mean Square of the elements of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_rms_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);


  /**
   * @brief  Root Mean Square of the elements of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_rms_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);


  /**
   * @brief  Standard deviation of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_std_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);


  /**
   * @brief  Standard deviation of the elements of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_std_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);


  /**
   * @brief  Standard deviation of the elements of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_std_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);


  /**
   * @brief  Standard deviation of the elements of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output value.
   */
  void arm_std_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);



  /**
   * @brief  Minimum value of a Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] result     is output pointer
   * @param[in]  index      is the array index of the minimum value in the input buffer.
   */
  void arm_min_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * result,
        uint32_t * index);

  /**
   * @brief  Minimum value of absolute values of a Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] result     is output pointer
   * @param[in]  index      is the array index of the minimum value in the input buffer.
   */
  void arm_absmin_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * result,
        uint32_t * index);

    /**
   * @brief  Minimum value of absolute values of a Q7 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] result     is output pointer
   */
  void arm_absmin_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * result);


  /**
   * @brief  Minimum value of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[in]  pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_min_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);

/**
   * @brief  Minimum value of absolute values of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[in]  pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_absmin_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);

  /**
   * @brief  Minimum value of absolute values of a Q15 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   */
  void arm_absmin_no_idx_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);


  /**
   * @brief  Minimum value of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[out] pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_min_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);

  /**
   * @brief  Minimum value of absolute values of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[out] pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_absmin_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);

 /**
   * @brief  Minimum value of absolute values of a Q31 vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   */
  void arm_absmin_no_idx_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);


  /**
   * @brief  Minimum value of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[out] pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_min_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);

  /**
   * @brief  Minimum value of absolute values of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[out] pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_absmin_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);

  /**
   * @brief  Minimum value of absolute values of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   */
  void arm_absmin_no_idx_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);


  /**
   * @brief  Minimum value of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[out] pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_min_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);

  /**
   * @brief  Minimum value of absolute values of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   * @param[out] pIndex     is the array index of the minimum value in the input buffer.
   */
  void arm_absmin_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);

  /**
   * @brief  Minimum value of absolute values of a floating-point vector.
   * @param[in]  pSrc       is input pointer
   * @param[in]  blockSize  is the number of samples to process
   * @param[out] pResult    is output pointer
   */
  void arm_absmin_no_idx_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);


/**
 * @brief Maximum value of a Q7 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_max_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a Q7 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_absmax_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a Q7 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 */
  void arm_absmax_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult);


/**
 * @brief Maximum value of a Q15 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_max_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a Q15 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_absmax_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);

  /**
 * @brief Maximum value of absolute values of a Q15 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 */
  void arm_absmax_no_idx_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);

/**
 * @brief Maximum value of a Q31 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_max_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a Q31 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_absmax_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);

 /**
 * @brief Maximum value of absolute values of a Q31 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 */
  void arm_absmax_no_idx_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);

/**
 * @brief Maximum value of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_max_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_absmax_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);

 /**
 * @brief Maximum value of absolute values of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 */
  void arm_absmax_no_idx_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);

/**
 * @brief Maximum value of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_max_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
  void arm_absmax_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);

/**
 * @brief Maximum value of absolute values of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 */
  void arm_absmax_no_idx_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);

  /**
    @brief         Maximum value of a floating-point vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    maximum value returned here
    @return        none
   */
  void arm_max_no_idx_f32(
      const float32_t *pSrc,
      uint32_t   blockSize,
      float32_t *pResult);

  /**
    @brief         Minimum value of a floating-point vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    minimum value returned here
    @return        none
   */
  void arm_min_no_idx_f32(
      const float32_t *pSrc,
      uint32_t   blockSize,
      float32_t *pResult);

  /**
    @brief         Maximum value of a floating-point vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    maximum value returned here
    @return        none
   */
  void arm_max_no_idx_f64(
      const float64_t *pSrc,
      uint32_t   blockSize,
      float64_t *pResult);

  /**
    @brief         Maximum value of a q31 vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    maximum value returned here
    @return        none
   */
  void arm_max_no_idx_q31(
      const q31_t *pSrc,
      uint32_t   blockSize,
      q31_t *pResult);

  /**
    @brief         Maximum value of a q15 vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    maximum value returned here
    @return        none
   */
  void arm_max_no_idx_q15(
      const q15_t *pSrc,
      uint32_t   blockSize,
      q15_t *pResult);

  /**
    @brief         Maximum value of a q7 vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    maximum value returned here
    @return        none
   */
  void arm_max_no_idx_q7(
      const q7_t *pSrc,
      uint32_t   blockSize,
      q7_t *pResult);

  /**
    @brief         Minimum value of a floating-point vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    minimum value returned here
    @return        none
   */
  void arm_min_no_idx_f64(
      const float64_t *pSrc,
      uint32_t   blockSize,
      float64_t *pResult);

/**
    @brief         Minimum value of a q31 vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    minimum value returned here
    @return        none
   */
  void arm_min_no_idx_q31(
      const q31_t *pSrc,
      uint32_t   blockSize,
      q31_t *pResult);

  /**
    @brief         Minimum value of a q15 vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    minimum value returned here
    @return        none
   */
  void arm_min_no_idx_q15(
      const q15_t *pSrc,
      uint32_t   blockSize,
      q15_t *pResult);

  /**
    @brief         Minimum value of a q7 vector.
    @param[in]     pSrc       points to the input vector
    @param[in]     blockSize  number of samples in input vector
    @param[out]    pResult    minimum value returned here
    @return        none
   */
  void arm_min_no_idx_q7(
      const q7_t *pSrc,
      uint32_t   blockSize,
      q7_t *pResult);

/**
  @brief         Mean square error between two Q7 vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    mean square error
  @return        none
*/

void arm_mse_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        uint32_t blockSize,
        q7_t * pResult);

/**
  @brief         Mean square error between two Q15 vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    mean square error
  @return        none
*/

void arm_mse_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t blockSize,
        q15_t * pResult);

/**
  @brief         Mean square error between two Q31 vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    mean square error
  @return        none
*/

void arm_mse_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        uint32_t blockSize,
        q31_t * pResult);

/**
  @brief         Mean square error between two single precision float vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    mean square error
  @return        none
*/

void arm_mse_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        uint32_t blockSize,
        float32_t * pResult);

/**
  @brief         Mean square error between two double precision float vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    mean square error
  @return        none
*/

void arm_mse_f64(
  const float64_t * pSrcA,
  const float64_t * pSrcB,
        uint32_t blockSize,
        float64_t * pResult);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _STATISTICS_FUNCTIONS_H_ */
