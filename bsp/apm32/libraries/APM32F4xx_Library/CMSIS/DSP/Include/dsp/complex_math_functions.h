/******************************************************************************
 * @file     complex_math_functions.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.9.0
 * @date     23 April 2021
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


#ifndef _COMPLEX_MATH_FUNCTIONS_H_
#define _COMPLEX_MATH_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"
#include "dsp/fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @defgroup groupCmplxMath Complex Math Functions
 * This set of functions operates on complex data vectors.
 * The data in the complex arrays is stored in an interleaved fashion
 * (real, imag, real, imag, ...).
 * In the API functions, the number of samples in a complex array refers
 * to the number of complex values; the array contains twice this number of
 * real values.
 */

 /**
   * @brief  Floating-point complex conjugate.
   * @param[in]  pSrc        points to the input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_conj_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t numSamples);

  /**
   * @brief  Q31 complex conjugate.
   * @param[in]  pSrc        points to the input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_conj_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q15 complex conjugate.
   * @param[in]  pSrc        points to the input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_conj_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Floating-point complex magnitude squared
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_squared_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q31 complex magnitude squared
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_squared_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q15 complex magnitude squared
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_squared_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);


/**
   * @brief  Floating-point complex magnitude
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q31 complex magnitude
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q15 complex magnitude
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q15 complex dot product
   * @param[in]  pSrcA       points to the first input vector
   * @param[in]  pSrcB       points to the second input vector
   * @param[in]  numSamples  number of complex samples in each vector
   * @param[out] realResult  real part of the result returned here
   * @param[out] imagResult  imaginary part of the result returned here
   */
  void arm_cmplx_dot_prod_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t numSamples,
        q31_t * realResult,
        q31_t * imagResult);


  /**
   * @brief  Q31 complex dot product
   * @param[in]  pSrcA       points to the first input vector
   * @param[in]  pSrcB       points to the second input vector
   * @param[in]  numSamples  number of complex samples in each vector
   * @param[out] realResult  real part of the result returned here
   * @param[out] imagResult  imaginary part of the result returned here
   */
  void arm_cmplx_dot_prod_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        uint32_t numSamples,
        q63_t * realResult,
        q63_t * imagResult);


  /**
   * @brief  Floating-point complex dot product
   * @param[in]  pSrcA       points to the first input vector
   * @param[in]  pSrcB       points to the second input vector
   * @param[in]  numSamples  number of complex samples in each vector
   * @param[out] realResult  real part of the result returned here
   * @param[out] imagResult  imaginary part of the result returned here
   */
  void arm_cmplx_dot_prod_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        uint32_t numSamples,
        float32_t * realResult,
        float32_t * imagResult);


  /**
   * @brief  Q15 complex-by-real multiplication
   * @param[in]  pSrcCmplx   points to the complex input vector
   * @param[in]  pSrcReal    points to the real input vector
   * @param[out] pCmplxDst   points to the complex output vector
   * @param[in]  numSamples  number of samples in each vector
   */
  void arm_cmplx_mult_real_q15(
  const q15_t * pSrcCmplx,
  const q15_t * pSrcReal,
        q15_t * pCmplxDst,
        uint32_t numSamples);


  /**
   * @brief  Q31 complex-by-real multiplication
   * @param[in]  pSrcCmplx   points to the complex input vector
   * @param[in]  pSrcReal    points to the real input vector
   * @param[out] pCmplxDst   points to the complex output vector
   * @param[in]  numSamples  number of samples in each vector
   */
  void arm_cmplx_mult_real_q31(
  const q31_t * pSrcCmplx,
  const q31_t * pSrcReal,
        q31_t * pCmplxDst,
        uint32_t numSamples);


  /**
   * @brief  Floating-point complex-by-real multiplication
   * @param[in]  pSrcCmplx   points to the complex input vector
   * @param[in]  pSrcReal    points to the real input vector
   * @param[out] pCmplxDst   points to the complex output vector
   * @param[in]  numSamples  number of samples in each vector
   */
  void arm_cmplx_mult_real_f32(
  const float32_t * pSrcCmplx,
  const float32_t * pSrcReal,
        float32_t * pCmplxDst,
        uint32_t numSamples);

  /**
   * @brief  Q15 complex-by-complex multiplication
   * @param[in]  pSrcA       points to the first input vector
   * @param[in]  pSrcB       points to the second input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_mult_cmplx_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Q31 complex-by-complex multiplication
   * @param[in]  pSrcA       points to the first input vector
   * @param[in]  pSrcB       points to the second input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_mult_cmplx_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t numSamples);


  /**
   * @brief  Floating-point complex-by-complex multiplication
   * @param[in]  pSrcA       points to the first input vector
   * @param[in]  pSrcB       points to the second input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_mult_cmplx_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t numSamples);



#ifdef   __cplusplus
}
#endif

#endif /* ifndef _COMPLEX_MATH_FUNCTIONS_H_ */
