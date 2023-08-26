/******************************************************************************
 * @file     filtering_functions.h
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

 
#ifndef _FILTERING_FUNCTIONS_H_
#define _FILTERING_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/support_functions.h"
#include "dsp/fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif



#define DELTA_Q31          ((q31_t)(0x100))
#define DELTA_Q15          ((q15_t)0x5)

/**
 * @defgroup groupFilters Filtering Functions
 */
    
  /**
   * @brief Instance structure for the Q7 FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;        /**< number of filter coefficients in the filter. */
          q7_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q7_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
  } arm_fir_instance_q7;

  /**
   * @brief Instance structure for the Q15 FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;         /**< number of filter coefficients in the filter. */
          q15_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q15_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
  } arm_fir_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;         /**< number of filter coefficients in the filter. */
          q31_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const q31_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of filter coefficients in the filter. */
          float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_f32;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of filter coefficients in the filter. */
          float64_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    const float64_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_f64;

  /**
   * @brief Processing function for the Q7 FIR filter.
   * @param[in]  S          points to an instance of the Q7 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_q7(
  const arm_fir_instance_q7 * S,
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q7 FIR filter.
   * @param[in,out] S          points to an instance of the Q7 FIR structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed.
   *
   * For the MVE version, the coefficient length must be a multiple of 16.
   * You can pad with zeros if you have less coefficients.
   */
  void arm_fir_init_q7(
        arm_fir_instance_q7 * S,
        uint16_t numTaps,
  const q7_t * pCoeffs,
        q7_t * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q15 FIR filter.
   * @param[in]  S          points to an instance of the Q15 FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_q15(
  const arm_fir_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the fast Q15 FIR filter (fast version).
   * @param[in]  S          points to an instance of the Q15 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_fast_q15(
  const arm_fir_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q15 FIR filter.
   * @param[in,out] S          points to an instance of the Q15 FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter. Must be even and greater than or equal to 4.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   * @return     The function returns either
   * <code>ARM_MATH_SUCCESS</code> if initialization was successful or
   * <code>ARM_MATH_ARGUMENT_ERROR</code> if <code>numTaps</code> is not a supported value.
   *
   * For the MVE version, the coefficient length must be a multiple of 8.
   * You can pad with zeros if you have less coefficients.
   *
   */
  arm_status arm_fir_init_q15(
        arm_fir_instance_q15 * S,
        uint16_t numTaps,
  const q15_t * pCoeffs,
        q15_t * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 FIR filter.
   * @param[in]  S          points to an instance of the Q31 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_q31(
  const arm_fir_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the fast Q31 FIR filter (fast version).
   * @param[in]  S          points to an instance of the Q31 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_fast_q31(
  const arm_fir_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q31 FIR filter.
   * @param[in,out] S          points to an instance of the Q31 FIR structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   *
   * For the MVE version, the coefficient length must be a multiple of 4.
   * You can pad with zeros if you have less coefficients.
   */
  void arm_fir_init_q31(
        arm_fir_instance_q31 * S,
        uint16_t numTaps,
  const q31_t * pCoeffs,
        q31_t * pState,
        uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in]  S          points to an instance of the floating-point FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_f32(
  const arm_fir_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in]  S          points to an instance of the floating-point FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_f64(
  const arm_fir_instance_f64 * S,
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void arm_fir_init_f32(
        arm_fir_instance_f32 * S,
        uint16_t numTaps,
  const float32_t * pCoeffs,
        float32_t * pState,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void arm_fir_init_f64(
        arm_fir_instance_f64 * S,
        uint16_t numTaps,
  const float64_t * pCoeffs,
        float64_t * pState,
        uint32_t blockSize);

  /**
   * @brief Instance structure for the Q15 Biquad cascade filter.
   */
  typedef struct
  {
          int8_t numStages;        /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          q15_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const q15_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
          int8_t postShift;        /**< Additional shift, in bits, applied to each output sample. */
  } arm_biquad_casd_df1_inst_q15;

  /**
   * @brief Instance structure for the Q31 Biquad cascade filter.
   */
  typedef struct
  {
          uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          q31_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const q31_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
          uint8_t postShift;       /**< Additional shift, in bits, applied to each output sample. */
  } arm_biquad_casd_df1_inst_q31;

  /**
   * @brief Instance structure for the floating-point Biquad cascade filter.
   */
  typedef struct
  {
          uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float32_t *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    const float32_t *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_casd_df1_inst_f32;

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
  /**
   * @brief Instance structure for the modified Biquad coefs required by vectorized code.
   */
  typedef struct
  {
      float32_t coeffs[8][4]; /**< Points to the array of modified coefficients.  The array is of length 32. There is one per stage */
  } arm_biquad_mod_coef_f32;
#endif 

  /**
   * @brief Processing function for the Q15 Biquad cascade filter.
   * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q15 Biquad cascade filter.
   * @param[in,out] S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
   */
  void arm_biquad_cascade_df1_init_q15(
        arm_biquad_casd_df1_inst_q15 * S,
        uint8_t numStages,
  const q15_t * pCoeffs,
        q15_t * pState,
        int8_t postShift);

  /**
   * @brief Fast but less precise processing function for the Q15 Biquad cascade filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_fast_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 Biquad cascade filter
   * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Fast but less precise processing function for the Q31 Biquad cascade filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_fast_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the Q31 Biquad cascade filter.
   * @param[in,out] S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
   */
  void arm_biquad_cascade_df1_init_q31(
        arm_biquad_casd_df1_inst_q31 * S,
        uint8_t numStages,
  const q31_t * pCoeffs,
        q31_t * pState,
        int8_t postShift);

  /**
   * @brief Processing function for the floating-point Biquad cascade filter.
   * @param[in]  S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_f32(
  const arm_biquad_casd_df1_inst_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  Initialization function for the floating-point Biquad cascade filter.
   * @param[in,out] S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pCoeffsMod points to the modified filter coefficients (only MVE version).
   * @param[in]     pState     points to the state buffer.
   */
#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
  void arm_biquad_cascade_df1_mve_init_f32(
      arm_biquad_casd_df1_inst_f32 * S,
      uint8_t numStages,
      const float32_t * pCoeffs, 
      arm_biquad_mod_coef_f32 * pCoeffsMod, 
      float32_t * pState);
#endif
  
  void arm_biquad_cascade_df1_init_f32(
        arm_biquad_casd_df1_inst_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);


/**
 * @brief Convolution of floating-point sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
  void arm_conv_f32(
  const float32_t * pSrcA,
        uint32_t srcALen,
  const float32_t * pSrcB,
        uint32_t srcBLen,
        float32_t * pDst);


  /**
   * @brief Convolution of Q15 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
   */
  void arm_conv_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);


/**
 * @brief Convolution of Q15 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
  void arm_conv_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);


  /**
   * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_fast_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);


  /**
   * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
   */
  void arm_conv_fast_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);


  /**
   * @brief Convolution of Q31 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);


  /**
   * @brief Convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_fast_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);


    /**
   * @brief Convolution of Q7 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
   */
  void arm_conv_opt_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);


  /**
   * @brief Convolution of Q7 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst);


  /**
   * @brief Partial convolution of floating-point sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_f32(
  const float32_t * pSrcA,
        uint32_t srcALen,
  const float32_t * pSrcB,
        uint32_t srcBLen,
        float32_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15_t * pScratch1,
        q15_t * pScratch2);


  /**
   * @brief Partial convolution of Q15 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_fast_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_fast_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15_t * pScratch1,
        q15_t * pScratch2);


  /**
   * @brief Partial convolution of Q31 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_fast_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Partial convolution of Q7 sequences
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_opt_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15_t * pScratch1,
        q15_t * pScratch2);


/**
   * @brief Partial convolution of Q7 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);


  /**
   * @brief Instance structure for the Q15 FIR decimator.
   */
  typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const q15_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
          q15_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR decimator.
   */
  typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const q31_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
          q31_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_q31;

/**
  @brief Instance structure for floating-point FIR decimator.
 */
typedef struct
  {
          uint8_t M;                  /**< decimation factor. */
          uint16_t numTaps;           /**< number of coefficients in the filter. */
    const float32_t *pCoeffs;         /**< points to the coefficient array. The array is of length numTaps.*/
          float32_t *pState;          /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_f32;


/**
  @brief         Processing function for floating-point FIR decimator.
  @param[in]     S         points to an instance of the floating-point FIR decimator structure
  @param[in]     pSrc      points to the block of input data
  @param[out]    pDst      points to the block of output data
  @param[in]     blockSize number of samples to process
 */
void arm_fir_decimate_f32(
  const arm_fir_decimate_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);


/**
  @brief         Initialization function for the floating-point FIR decimator.
  @param[in,out] S          points to an instance of the floating-point FIR decimator structure
  @param[in]     numTaps    number of coefficients in the filter
  @param[in]     M          decimation factor
  @param[in]     pCoeffs    points to the filter coefficients
  @param[in]     pState     points to the state buffer
  @param[in]     blockSize  number of input samples to process per call
  @return        execution status
                   - \ref ARM_MATH_SUCCESS      : Operation successful
                   - \ref ARM_MATH_LENGTH_ERROR : <code>blockSize</code> is not a multiple of <code>M</code>
 */
arm_status arm_fir_decimate_init_f32(
        arm_fir_decimate_instance_f32 * S,
        uint16_t numTaps,
        uint8_t M,
  const float32_t * pCoeffs,
        float32_t * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR decimator.
   * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_fast_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR decimator.
   * @param[in,out] S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  arm_status arm_fir_decimate_init_q15(
        arm_fir_decimate_instance_q15 * S,
        uint16_t numTaps,
        uint8_t M,
  const q15_t * pCoeffs,
        q15_t * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR decimator.
   * @param[in]  S     points to an instance of the Q31 FIR decimator structure.
   * @param[in]  pSrc  points to the block of input data.
   * @param[out] pDst  points to the block of output data
   * @param[in] blockSize number of input samples to process per call.
   */
  void arm_fir_decimate_q31(
  const arm_fir_decimate_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_fast_q31(
  const arm_fir_decimate_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR decimator.
   * @param[in,out] S          points to an instance of the Q31 FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  arm_status arm_fir_decimate_init_q31(
        arm_fir_decimate_instance_q31 * S,
        uint16_t numTaps,
        uint8_t M,
  const q31_t * pCoeffs,
        q31_t * pState,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 FIR interpolator.
   */
  typedef struct
  {
        uint8_t L;                      /**< upsample factor. */
        uint16_t phaseLength;           /**< length of each polyphase filter component. */
  const q15_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
        q15_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } arm_fir_interpolate_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR interpolator.
   */
  typedef struct
  {
        uint8_t L;                      /**< upsample factor. */
        uint16_t phaseLength;           /**< length of each polyphase filter component. */
  const q31_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
        q31_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } arm_fir_interpolate_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR interpolator.
   */
  typedef struct
  {
        uint8_t L;                     /**< upsample factor. */
        uint16_t phaseLength;          /**< length of each polyphase filter component. */
  const float32_t *pCoeffs;            /**< points to the coefficient array. The array is of length L*phaseLength. */
        float32_t *pState;             /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
  } arm_fir_interpolate_instance_f32;


  /**
   * @brief Processing function for the Q15 FIR interpolator.
   * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_interpolate_q15(
  const arm_fir_interpolate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR interpolator.
   * @param[in,out] S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  arm_status arm_fir_interpolate_init_q15(
        arm_fir_interpolate_instance_q15 * S,
        uint8_t L,
        uint16_t numTaps,
  const q15_t * pCoeffs,
        q15_t * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR interpolator.
   * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_interpolate_q31(
  const arm_fir_interpolate_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR interpolator.
   * @param[in,out] S          points to an instance of the Q31 FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  arm_status arm_fir_interpolate_init_q31(
        arm_fir_interpolate_instance_q31 * S,
        uint8_t L,
        uint16_t numTaps,
  const q31_t * pCoeffs,
        q31_t * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point FIR interpolator.
   * @param[in]  S          points to an instance of the floating-point FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point FIR interpolator.
   * @param[in,out] S          points to an instance of the floating-point FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  arm_status arm_fir_interpolate_init_f32(
        arm_fir_interpolate_instance_f32 * S,
        uint8_t L,
        uint16_t numTaps,
  const float32_t * pCoeffs,
        float32_t * pState,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the high precision Q31 Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;       /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          q63_t *pState;           /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const q31_t *pCoeffs;          /**< points to the array of coefficients.  The array is of length 5*numStages. */
          uint8_t postShift;       /**< additional shift, in bits, applied to each output sample. */
  } arm_biquad_cas_df1_32x64_ins_q31;


  /**
   * @param[in]  S          points to an instance of the high precision Q31 Biquad cascade filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cas_df1_32x64_q31(
  const arm_biquad_cas_df1_32x64_ins_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @param[in,out] S          points to an instance of the high precision Q31 Biquad cascade filter structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  shift to be applied to the output. Varies according to the coefficients format
   */
  void arm_biquad_cas_df1_32x64_init_q31(
        arm_biquad_cas_df1_32x64_ins_q31 * S,
        uint8_t numStages,
  const q31_t * pCoeffs,
        q63_t * pState,
        uint8_t postShift);


  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    const float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_df2T_instance_f32;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    const float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_stereo_df2T_instance_f32;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
          uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
          float64_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    const float64_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_df2T_instance_f64;


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df2T_f32(
  const arm_biquad_cascade_df2T_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter. 2 channels
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_stereo_df2T_f32(
  const arm_biquad_cascade_stereo_df2T_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df2T_f64(
  const arm_biquad_cascade_df2T_instance_f64 * S,
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);


#if defined(ARM_MATH_NEON) 
/**
  @brief         Compute new coefficient arrays for use in vectorized filter (Neon only).
  @param[in]     numStages         number of 2nd order stages in the filter.
  @param[in]     pCoeffs           points to the original filter coefficients.
  @param[in]     pComputedCoeffs   points to the new computed coefficients for the vectorized version.
  @return        none
*/
void arm_biquad_cascade_df2T_compute_coefs_f32(
  uint8_t numStages,
  const float32_t * pCoeffs,
  float32_t * pComputedCoeffs);
#endif
  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_df2T_init_f32(
        arm_biquad_cascade_df2T_instance_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_stereo_df2T_init_f32(
        arm_biquad_cascade_stereo_df2T_instance_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_df2T_init_f64(
        arm_biquad_cascade_df2T_instance_f64 * S,
        uint8_t numStages,
        const float64_t * pCoeffs,
        float64_t * pState);


  /**
   * @brief Instance structure for the Q15 FIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of filter stages. */
          q15_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
    const q15_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of filter stages. */
          q31_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
    const q31_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of filter stages. */
          float32_t *pState;                   /**< points to the state variable array. The array is of length numStages. */
    const float32_t *pCoeffs;                  /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_f32;


  /**
   * @brief Initialization function for the Q15 FIR lattice filter.
   * @param[in] S          points to an instance of the Q15 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
   * @param[in] pState     points to the state buffer.  The array is of length numStages.
   */
  void arm_fir_lattice_init_q15(
        arm_fir_lattice_instance_q15 * S,
        uint16_t numStages,
  const q15_t * pCoeffs,
        q15_t * pState);


  /**
   * @brief Processing function for the Q15 FIR lattice filter.
   * @param[in]  S          points to an instance of the Q15 FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_lattice_q15(
  const arm_fir_lattice_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 FIR lattice filter.
   * @param[in] S          points to an instance of the Q31 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
   * @param[in] pState     points to the state buffer.   The array is of length numStages.
   */
  void arm_fir_lattice_init_q31(
        arm_fir_lattice_instance_q31 * S,
        uint16_t numStages,
  const q31_t * pCoeffs,
        q31_t * pState);


  /**
   * @brief Processing function for the Q31 FIR lattice filter.
   * @param[in]  S          points to an instance of the Q31 FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);


/**
 * @brief Initialization function for the floating-point FIR lattice filter.
 * @param[in] S          points to an instance of the floating-point FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
 * @param[in] pState     points to the state buffer.  The array is of length numStages.
 */
  void arm_fir_lattice_init_f32(
        arm_fir_lattice_instance_f32 * S,
        uint16_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);


  /**
   * @brief Processing function for the floating-point FIR lattice filter.
   * @param[in]  S          points to an instance of the floating-point FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_lattice_f32(
  const arm_fir_lattice_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          q15_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
          q15_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
          q15_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          q31_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
          q31_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
          q31_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point IIR lattice filter.
   */
  typedef struct
  {
          uint16_t numStages;                  /**< number of stages in the filter. */
          float32_t *pState;                   /**< points to the state variable array. The array is of length numStages+blockSize. */
          float32_t *pkCoeffs;                 /**< points to the reflection coefficient array. The array is of length numStages. */
          float32_t *pvCoeffs;                 /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_f32;


  /**
   * @brief Processing function for the floating-point IIR lattice filter.
   * @param[in]  S          points to an instance of the floating-point IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_iir_lattice_f32(
  const arm_iir_lattice_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Initialization function for the floating-point IIR lattice filter.
   * @param[in] S          points to an instance of the floating-point IIR lattice structure.
   * @param[in] numStages  number of stages in the filter.
   * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize-1.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_iir_lattice_init_f32(
        arm_iir_lattice_instance_f32 * S,
        uint16_t numStages,
        float32_t * pkCoeffs,
        float32_t * pvCoeffs,
        float32_t * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 IIR lattice filter.
   * @param[in]  S          points to an instance of the Q31 IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_iir_lattice_q31(
  const arm_iir_lattice_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 IIR lattice filter.
   * @param[in] S          points to an instance of the Q31 IIR lattice structure.
   * @param[in] numStages  number of stages in the filter.
   * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_iir_lattice_init_q31(
        arm_iir_lattice_instance_q31 * S,
        uint16_t numStages,
        q31_t * pkCoeffs,
        q31_t * pvCoeffs,
        q31_t * pState,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 IIR lattice filter.
   * @param[in]  S          points to an instance of the Q15 IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_iir_lattice_q15(
  const arm_iir_lattice_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


/**
 * @brief Initialization function for the Q15 IIR lattice filter.
 * @param[in] S          points to an instance of the fixed-point Q15 IIR lattice structure.
 * @param[in] numStages  number of stages in the filter.
 * @param[in] pkCoeffs   points to reflection coefficient buffer.  The array is of length numStages.
 * @param[in] pvCoeffs   points to ladder coefficient buffer.  The array is of length numStages+1.
 * @param[in] pState     points to state buffer.  The array is of length numStages+blockSize.
 * @param[in] blockSize  number of samples to process per call.
 */
  void arm_iir_lattice_init_q15(
        arm_iir_lattice_instance_q15 * S,
        uint16_t numStages,
        q15_t * pkCoeffs,
        q15_t * pvCoeffs,
        q15_t * pState,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the floating-point LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          float32_t *pState;   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          float32_t *pCoeffs;  /**< points to the coefficient array. The array is of length numTaps. */
          float32_t mu;        /**< step size that controls filter coefficient updates. */
  } arm_lms_instance_f32;


  /**
   * @brief Processing function for floating-point LMS filter.
   * @param[in]  S          points to an instance of the floating-point LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_f32(
  const arm_lms_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pRef,
        float32_t * pOut,
        float32_t * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for floating-point LMS filter.
   * @param[in] S          points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to the coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_lms_init_f32(
        arm_lms_instance_f32 * S,
        uint16_t numTaps,
        float32_t * pCoeffs,
        float32_t * pState,
        float32_t mu,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          q15_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q15_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
          q15_t mu;            /**< step size that controls filter coefficient updates. */
          uint32_t postShift;  /**< bit shift applied to coefficients. */
  } arm_lms_instance_q15;


  /**
   * @brief Initialization function for the Q15 LMS filter.
   * @param[in] S          points to an instance of the Q15 LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to the coefficient buffer.
   * @param[in] pState     points to the state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_init_q15(
        arm_lms_instance_q15 * S,
        uint16_t numTaps,
        q15_t * pCoeffs,
        q15_t * pState,
        q15_t mu,
        uint32_t blockSize,
        uint32_t postShift);


  /**
   * @brief Processing function for Q15 LMS filter.
   * @param[in]  S          points to an instance of the Q15 LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_q15(
  const arm_lms_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pRef,
        q15_t * pOut,
        q15_t * pErr,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;    /**< number of coefficients in the filter. */
          q31_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q31_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
          q31_t mu;            /**< step size that controls filter coefficient updates. */
          uint32_t postShift;  /**< bit shift applied to coefficients. */
  } arm_lms_instance_q31;


  /**
   * @brief Processing function for Q31 LMS filter.
   * @param[in]  S          points to an instance of the Q15 LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_q31(
  const arm_lms_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pRef,
        q31_t * pOut,
        q31_t * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for Q31 LMS filter.
   * @param[in] S          points to an instance of the Q31 LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_init_q31(
        arm_lms_instance_q31 * S,
        uint16_t numTaps,
        q31_t * pCoeffs,
        q31_t * pState,
        q31_t mu,
        uint32_t blockSize,
        uint32_t postShift);


  /**
   * @brief Instance structure for the floating-point normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of coefficients in the filter. */
          float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
          float32_t mu;         /**< step size that control filter coefficient updates. */
          float32_t energy;     /**< saves previous frame energy. */
          float32_t x0;         /**< saves previous input sample. */
  } arm_lms_norm_instance_f32;


  /**
   * @brief Processing function for floating-point normalized LMS filter.
   * @param[in]  S          points to an instance of the floating-point normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_norm_f32(
        arm_lms_norm_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pRef,
        float32_t * pOut,
        float32_t * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for floating-point normalized LMS filter.
   * @param[in] S          points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_lms_norm_init_f32(
        arm_lms_norm_instance_f32 * S,
        uint16_t numTaps,
        float32_t * pCoeffs,
        float32_t * pState,
        float32_t mu,
        uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< number of coefficients in the filter. */
          q31_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q31_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
          q31_t mu;             /**< step size that controls filter coefficient updates. */
          uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q31_t *recipTable;    /**< points to the reciprocal initial value table. */
          q31_t energy;         /**< saves previous frame energy. */
          q31_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q31;


  /**
   * @brief Processing function for Q31 normalized LMS filter.
   * @param[in]  S          points to an instance of the Q31 normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_norm_q31(
        arm_lms_norm_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pRef,
        q31_t * pOut,
        q31_t * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for Q31 normalized LMS filter.
   * @param[in] S          points to an instance of the Q31 normalized LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_norm_init_q31(
        arm_lms_norm_instance_q31 * S,
        uint16_t numTaps,
        q31_t * pCoeffs,
        q31_t * pState,
        q31_t mu,
        uint32_t blockSize,
        uint8_t postShift);


  /**
   * @brief Instance structure for the Q15 normalized LMS filter.
   */
  typedef struct
  {
          uint16_t numTaps;     /**< Number of coefficients in the filter. */
          q15_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
          q15_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
          q15_t mu;             /**< step size that controls filter coefficient updates. */
          uint8_t postShift;    /**< bit shift applied to coefficients. */
    const q15_t *recipTable;    /**< Points to the reciprocal initial value table. */
          q15_t energy;         /**< saves previous frame energy. */
          q15_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q15;


  /**
   * @brief Processing function for Q15 normalized LMS filter.
   * @param[in]  S          points to an instance of the Q15 normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_norm_q15(
        arm_lms_norm_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pRef,
        q15_t * pOut,
        q15_t * pErr,
        uint32_t blockSize);


  /**
   * @brief Initialization function for Q15 normalized LMS filter.
   * @param[in] S          points to an instance of the Q15 normalized LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_norm_init_q15(
        arm_lms_norm_instance_q15 * S,
        uint16_t numTaps,
        q15_t * pCoeffs,
        q15_t * pState,
        q15_t mu,
        uint32_t blockSize,
        uint8_t postShift);


  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_f32(
  const float32_t * pSrcA,
        uint32_t srcALen,
  const float32_t * pSrcB,
        uint32_t srcBLen,
        float32_t * pDst);


  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_f64(
  const float64_t * pSrcA,
        uint32_t srcALen,
  const float64_t * pSrcB,
        uint32_t srcBLen,
        float64_t * pDst);


/**
 @brief Correlation of Q15 sequences
 @param[in]  pSrcA     points to the first input sequence
 @param[in]  srcALen   length of the first input sequence
 @param[in]  pSrcB     points to the second input sequence
 @param[in]  srcBLen   length of the second input sequence
 @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
*/
void arm_correlate_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch);


/**
  @brief Correlation of Q15 sequences.
  @param[in]  pSrcA    points to the first input sequence
  @param[in]  srcALen  length of the first input sequence
  @param[in]  pSrcB    points to the second input sequence
  @param[in]  srcBLen  length of the second input sequence
  @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
  void arm_correlate_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);


/**
  @brief         Correlation of Q15 sequences (fast version).
  @param[in]     pSrcA      points to the first input sequence
  @param[in]     srcALen    length of the first input sequence
  @param[in]     pSrcB      points to the second input sequence
  @param[in]     srcBLen    length of the second input sequence
  @param[out]    pDst       points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.
  @return        none
 */
void arm_correlate_fast_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);


/**
  @brief Correlation of Q15 sequences (fast version).
  @param[in]  pSrcA     points to the first input sequence.
  @param[in]  srcALen   length of the first input sequence.
  @param[in]  pSrcB     points to the second input sequence.
  @param[in]  srcBLen   length of the second input sequence.
  @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
  @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 */
void arm_correlate_fast_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch);


  /**
   * @brief Correlation of Q31 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);


/**
  @brief Correlation of Q31 sequences (fast version).
  @param[in]  pSrcA    points to the first input sequence
  @param[in]  srcALen  length of the first input sequence
  @param[in]  pSrcB    points to the second input sequence
  @param[in]  srcBLen  length of the second input sequence
  @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void arm_correlate_fast_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);


 /**
   * @brief Correlation of Q7 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[in]  pScratch1  points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
   */
  void arm_correlate_opt_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);


  /**
   * @brief Correlation of Q7 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst);


  /**
   * @brief Instance structure for the floating-point sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          float32_t *pState;            /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const float32_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_f32;

  /**
   * @brief Instance structure for the Q31 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q31_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q31_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q31;

  /**
   * @brief Instance structure for the Q15 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q15_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q15_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q15;

  /**
   * @brief Instance structure for the Q7 sparse FIR filter.
   */
  typedef struct
  {
          uint16_t numTaps;             /**< number of coefficients in the filter. */
          uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
          q7_t *pState;                 /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    const q7_t *pCoeffs;                /**< points to the coefficient array. The array is of length numTaps.*/
          uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
          int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q7;


  /**
   * @brief Processing function for the floating-point sparse FIR filter.
   * @param[in]  S           points to an instance of the floating-point sparse FIR structure.
   * @param[in]  pSrc        points to the block of input data.
   * @param[out] pDst        points to the block of output data
   * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   */
  void arm_fir_sparse_f32(
        arm_fir_sparse_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        float32_t * pScratchIn,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point sparse FIR filter.
   * @param[in,out] S          points to an instance of the floating-point sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_f32(
        arm_fir_sparse_instance_f32 * S,
        uint16_t numTaps,
  const float32_t * pCoeffs,
        float32_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 sparse FIR filter.
   * @param[in]  S           points to an instance of the Q31 sparse FIR structure.
   * @param[in]  pSrc        points to the block of input data.
   * @param[out] pDst        points to the block of output data
   * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   */
  void arm_fir_sparse_q31(
        arm_fir_sparse_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        q31_t * pScratchIn,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q31 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_q31(
        arm_fir_sparse_instance_q31 * S,
        uint16_t numTaps,
  const q31_t * pCoeffs,
        q31_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 sparse FIR filter.
   * @param[in]  S            points to an instance of the Q15 sparse FIR structure.
   * @param[in]  pSrc         points to the block of input data.
   * @param[out] pDst         points to the block of output data
   * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
   * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize    number of input samples to process per call.
   */
  void arm_fir_sparse_q15(
        arm_fir_sparse_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        q15_t * pScratchIn,
        q31_t * pScratchOut,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q15 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_q15(
        arm_fir_sparse_instance_q15 * S,
        uint16_t numTaps,
  const q15_t * pCoeffs,
        q15_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);


  /**
   * @brief Processing function for the Q7 sparse FIR filter.
   * @param[in]  S            points to an instance of the Q7 sparse FIR structure.
   * @param[in]  pSrc         points to the block of input data.
   * @param[out] pDst         points to the block of output data
   * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
   * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize    number of input samples to process per call.
   */
  void arm_fir_sparse_q7(
        arm_fir_sparse_instance_q7 * S,
  const q7_t * pSrc,
        q7_t * pDst,
        q7_t * pScratchIn,
        q31_t * pScratchOut,
        uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q7 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q7 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_q7(
        arm_fir_sparse_instance_q7 * S,
        uint16_t numTaps,
  const q7_t * pCoeffs,
        q7_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);




 

  /**
   * @brief floating-point Circular write function.
   */
  __STATIC_FORCEINLINE void arm_circularWrite_f32(
  int32_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const int32_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;

    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the input sample to the circular buffer */
      circBuffer[wOffset] = *src;

      /* Update the input pointer */
      src += srcInc;

      /* Circularly update wOffset.  Watch out for positive and negative value */
      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
  }



  /**
   * @brief floating-point Circular Read function.
   */
  __STATIC_FORCEINLINE void arm_circularRead_f32(
  int32_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  int32_t * dst,
  int32_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t rOffset;
    int32_t* dst_end;

    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;
    dst_end = dst_base + dst_length;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the sample from the circular buffer to the destination buffer */
      *dst = circBuffer[rOffset];

      /* Update the input pointer */
      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }

      /* Circularly update rOffset.  Watch out for positive and negative value  */
      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
  }


  /**
   * @brief Q15 Circular write function.
   */
  __STATIC_FORCEINLINE void arm_circularWrite_q15(
  q15_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q15_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;

    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the input sample to the circular buffer */
      circBuffer[wOffset] = *src;

      /* Update the input pointer */
      src += srcInc;

      /* Circularly update wOffset.  Watch out for positive and negative value */
      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
  }


  /**
   * @brief Q15 Circular Read function.
   */
  __STATIC_FORCEINLINE void arm_circularRead_q15(
  q15_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q15_t * dst,
  q15_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset;
    q15_t* dst_end;

    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;

    dst_end = dst_base + dst_length;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the sample from the circular buffer to the destination buffer */
      *dst = circBuffer[rOffset];

      /* Update the input pointer */
      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }

      /* Circularly update wOffset.  Watch out for positive and negative value */
      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
  }


  /**
   * @brief Q7 Circular write function.
   */
  __STATIC_FORCEINLINE void arm_circularWrite_q7(
  q7_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q7_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;

    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the input sample to the circular buffer */
      circBuffer[wOffset] = *src;

      /* Update the input pointer */
      src += srcInc;

      /* Circularly update wOffset.  Watch out for positive and negative value */
      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
  }


  /**
   * @brief Q7 Circular Read function.
   */
  __STATIC_FORCEINLINE void arm_circularRead_q7(
  q7_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q7_t * dst,
  q7_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset;
    q7_t* dst_end;

    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;

    dst_end = dst_base + dst_length;

    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U)
    {
      /* copy the sample from the circular buffer to the destination buffer */
      *dst = circBuffer[rOffset];

      /* Update the input pointer */
      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }

      /* Circularly update rOffset.  Watch out for positive and negative value */
      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }

      /* Decrement the loop counter */
      i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
  }


/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */
void arm_levinson_durbin_f32(const float32_t *phi,
  float32_t *a, 
  float32_t *err,
  int nbCoefs);


/**
  @brief         Levinson Durbin
  @param[in]     phi      autocovariance vector starting with lag 0 (length is nbCoefs + 1)
  @param[out]    a        autoregressive coefficients
  @param[out]    err      prediction error (variance)
  @param[in]     nbCoefs  number of autoregressive coefficients
  @return        none
 */
void arm_levinson_durbin_q31(const q31_t *phi,
  q31_t *a, 
  q31_t *err,
  int nbCoefs);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FILTERING_FUNCTIONS_H_ */
