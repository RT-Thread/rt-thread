/******************************************************************************
 * @file     transform_functions_f16.h
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


#ifndef _TRANSFORM_FUNCTIONS_F16_H_
#define _TRANSFORM_FUNCTIONS_F16_H_

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
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
          uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const float16_t *pTwiddle;               /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
          float16_t onebyfftLen;             /**< value of 1/fftLen. */
  } arm_cfft_radix2_instance_f16;

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
          uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
          uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    const float16_t *pTwiddle;               /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
          uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
          uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
          float16_t onebyfftLen;             /**< value of 1/fftLen. */
  } arm_cfft_radix4_instance_f16;

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
          uint16_t fftLen;                   /**< length of the FFT. */
    const float16_t *pTwiddle;         /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
          uint16_t bitRevLength;             /**< bit reversal table length. */
#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
   const uint32_t *rearranged_twiddle_tab_stride1_arr;        /**< Per stage reordered twiddle pointer (offset 1) */                                                       \
   const uint32_t *rearranged_twiddle_tab_stride2_arr;        /**< Per stage reordered twiddle pointer (offset 2) */                                                       \
   const uint32_t *rearranged_twiddle_tab_stride3_arr;        /**< Per stage reordered twiddle pointer (offset 3) */                                                       \
   const float16_t *rearranged_twiddle_stride1; /**< reordered twiddle offset 1 storage */                                                                   \
   const float16_t *rearranged_twiddle_stride2; /**< reordered twiddle offset 2 storage */                                                                   \
   const float16_t *rearranged_twiddle_stride3;
#endif
  } arm_cfft_instance_f16;


  arm_status arm_cfft_init_f16(
  arm_cfft_instance_f16 * S,
  uint16_t fftLen);

  void arm_cfft_f16(
  const arm_cfft_instance_f16 * S,
        float16_t * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the floating-point RFFT/RIFFT function.
   */
typedef struct
  {
          arm_cfft_instance_f16 Sint;      /**< Internal CFFT structure. */
          uint16_t fftLenRFFT;             /**< length of the real sequence */
    const float16_t * pTwiddleRFFT;        /**< Twiddle factors real stage  */
  } arm_rfft_fast_instance_f16 ;

arm_status arm_rfft_fast_init_f16 (
         arm_rfft_fast_instance_f16 * S,
         uint16_t fftLen);


  void arm_rfft_fast_f16(
        const arm_rfft_fast_instance_f16 * S,
        float16_t * p, float16_t * pOut,
        uint8_t ifftFlag);

/* Deprecated */
  arm_status arm_cfft_radix4_init_f16(
        arm_cfft_radix4_instance_f16 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix4_f16(
  const arm_cfft_radix4_instance_f16 * S,
        float16_t * pSrc);


/* Deprecated */
  arm_status arm_cfft_radix2_init_f16(
        arm_cfft_radix2_instance_f16 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix2_f16(
  const arm_cfft_radix2_instance_f16 * S,
        float16_t * pSrc);

#endif /* defined(ARM_FLOAT16_SUPPORTED)*/

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _TRANSFORM_FUNCTIONS_F16_H_ */
