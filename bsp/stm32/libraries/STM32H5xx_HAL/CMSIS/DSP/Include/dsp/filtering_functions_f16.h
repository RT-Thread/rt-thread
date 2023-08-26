/******************************************************************************
 * @file     filtering_functions_f16.h
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

 
#ifndef _FILTERING_FUNCTIONS_F16_H_
#define _FILTERING_FUNCTIONS_F16_H_

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
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of filter coefficients in the filter. */
          float16_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const float16_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_f16;

  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void arm_fir_init_f16(
        arm_fir_instance_f16 * S,
        uint16_t numTaps,
  const float16_t * pCoeffs,
        float16_t * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in]  S          points to an instance of the floating-point FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_f16(
  const arm_fir_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the floating-point Biquad cascade filter.
   */
  typedef struct
  {
          uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float16_t *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const float16_t *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_casd_df1_inst_f16;

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
  /**
   * @brief Instance structure for the modified Biquad coefs required by vectorized code.
   */
  typedef struct
  {
      float16_t coeffs[12][8]; /**< Points to the array of modified coefficients.  The array is of length 32. There is one per stage */
  } arm_biquad_mod_coef_f16;
#endif 

  /**
   * @brief Processing function for the floating-point Biquad cascade filter.
   * @param[in]  S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_f16(
  const arm_biquad_casd_df1_inst_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
  void arm_biquad_cascade_df1_mve_init_f16(
      arm_biquad_casd_df1_inst_f16 * S,
      uint8_t numStages,
      const float16_t * pCoeffs, 
      arm_biquad_mod_coef_f16 * pCoeffsMod, 
      float16_t * pState);
#endif

  void arm_biquad_cascade_df1_init_f16(
        arm_biquad_casd_df1_inst_f16 * S,
        uint8_t numStages,
  const float16_t * pCoeffs,
        float16_t * pState);

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float16_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    const float16_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_df2T_instance_f16;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float16_t *pState;         /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const float16_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_stereo_df2T_instance_f16;

  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df2T_f16(
  const arm_biquad_cascade_df2T_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter. 2 channels
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_stereo_df2T_f16(
  const arm_biquad_cascade_stereo_df2T_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_df2T_init_f16(
        arm_biquad_cascade_df2T_instance_f16 * S,
        uint8_t numStages,
  const float16_t * pCoeffs,
        float16_t * pState);

  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_stereo_df2T_init_f16(
        arm_biquad_cascade_stereo_df2T_instance_f16 * S,
        uint8_t numStages,
  const float16_t * pCoeffs,
        float16_t * pState);

  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_f16(
  const float16_t * pSrcA,
        uint32_t srcALen,
  const float16_t * pSrcB,
        uint32_t srcBLen,
        float16_t * pDst);


/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */
void arm_levinson_durbin_f16(const float16_t *phi,
  float16_t *a, 
  float16_t *err,
  int nbCoefs);

#endif /*defined(ARM_FLOAT16_SUPPORTED)*/
#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FILTERING_FUNCTIONS_F16_H_ */
