/******************************************************************************
 * @file     basic_math_functions.h
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

 
#ifndef _BASIC_MATH_FUNCTIONS_H_
#define _BASIC_MATH_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"


#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @defgroup groupMath Basic Math Functions
 */

 /**
   * @brief Q7 vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q15 vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q31 vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Floating-point vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t blockSize);



/**
 * @brief Floating-point vector multiplication.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void arm_mult_f64(
const float64_t * pSrcA,
const float64_t * pSrcB,
	  float64_t * pDst,
	  uint32_t blockSize);



 /**
   * @brief Floating-point vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t blockSize);



/**
  * @brief Floating-point vector addition.
  * @param[in]  pSrcA      points to the first input vector
  * @param[in]  pSrcB      points to the second input vector
  * @param[out] pDst       points to the output vector
  * @param[in]  blockSize  number of samples in each vector
  */
 void arm_add_f64(
 const float64_t * pSrcA,
 const float64_t * pSrcB,
	   float64_t * pDst,
	   uint32_t blockSize);



  /**
   * @brief Q7 vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q15 vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q31 vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Floating-point vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t blockSize);



  /**
   * @brief Floating-point vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_f64(
  const float64_t * pSrcA,
  const float64_t * pSrcB,
        float64_t * pDst,
        uint32_t blockSize);



  /**
   * @brief Q7 vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q15 vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q31 vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Multiplies a floating-point vector by a scalar.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  scale      scale factor to be applied
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_scale_f32(
  const float32_t * pSrc,
        float32_t scale,
        float32_t * pDst,
        uint32_t blockSize);



  /**
   * @brief Multiplies a floating-point vector by a scalar.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  scale      scale factor to be applied
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_scale_f64(
  const float64_t * pSrc,
        float64_t scale,
        float64_t * pDst,
        uint32_t blockSize);



  /**
   * @brief Multiplies a Q7 vector by a scalar.
   * @param[in]  pSrc        points to the input vector
   * @param[in]  scaleFract  fractional portion of the scale value
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to the output vector
   * @param[in]  blockSize   number of samples in the vector
   */
  void arm_scale_q7(
  const q7_t * pSrc,
        q7_t scaleFract,
        int8_t shift,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Multiplies a Q15 vector by a scalar.
   * @param[in]  pSrc        points to the input vector
   * @param[in]  scaleFract  fractional portion of the scale value
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to the output vector
   * @param[in]  blockSize   number of samples in the vector
   */
  void arm_scale_q15(
  const q15_t * pSrc,
        q15_t scaleFract,
        int8_t shift,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Multiplies a Q31 vector by a scalar.
   * @param[in]  pSrc        points to the input vector
   * @param[in]  scaleFract  fractional portion of the scale value
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to the output vector
   * @param[in]  blockSize   number of samples in the vector
   */
  void arm_scale_q31(
  const q31_t * pSrc,
        q31_t scaleFract,
        int8_t shift,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q7 vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_q7(
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Floating-point vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);



/**
 * @brief Floating-point vector absolute value.
 * @param[in]  pSrc       points to the input buffer
 * @param[out] pDst       points to the output buffer
 * @param[in]  blockSize  number of samples in each vector
 */
void arm_abs_f64(
const float64_t * pSrc,
	  float64_t * pDst,
	  uint32_t blockSize);



  /**
   * @brief Q15 vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Q31 vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief Dot product of floating-point vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        uint32_t blockSize,
        float32_t * result);



/**
 * @brief Dot product of floating-point vectors.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[in]  blockSize  number of samples in each vector
 * @param[out] result     output result returned here
 */
void arm_dot_prod_f64(
const float64_t * pSrcA,
const float64_t * pSrcB,
	  uint32_t blockSize,
	  float64_t * result);



  /**
   * @brief Dot product of Q7 vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        uint32_t blockSize,
        q31_t * result);


  /**
   * @brief Dot product of Q15 vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t blockSize,
        q63_t * result);


  /**
   * @brief Dot product of Q31 vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        uint32_t blockSize,
        q63_t * result);


  /**
   * @brief  Shifts the elements of a Q7 vector a specified number of bits.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_shift_q7(
  const q7_t * pSrc,
        int8_t shiftBits,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Shifts the elements of a Q15 vector a specified number of bits.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_shift_q15(
  const q15_t * pSrc,
        int8_t shiftBits,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Shifts the elements of a Q31 vector a specified number of bits.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_shift_q31(
  const q31_t * pSrc,
        int8_t shiftBits,
        q31_t * pDst,
        uint32_t blockSize);


/**
 * @brief  Adds a constant offset to a floating-point vector.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  offset     is the offset to be added
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void arm_offset_f64(
const float64_t * pSrc,
	  float64_t offset,
	  float64_t * pDst,
	  uint32_t blockSize);



  /**
   * @brief  Adds a constant offset to a floating-point vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_f32(
  const float32_t * pSrc,
        float32_t offset,
        float32_t * pDst,
        uint32_t blockSize);



  /**
   * @brief  Adds a constant offset to a Q7 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_q7(
  const q7_t * pSrc,
        q7_t offset,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Adds a constant offset to a Q15 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_q15(
  const q15_t * pSrc,
        q15_t offset,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Adds a constant offset to a Q31 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_q31(
  const q31_t * pSrc,
        q31_t offset,
        q31_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Negates the elements of a floating-point vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);



/**
 * @brief  Negates the elements of a floating-point vector.
 * @param[in]  pSrc       points to the input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void arm_negate_f64(
const float64_t * pSrc,
	  float64_t * pDst,
	  uint32_t blockSize);



  /**
   * @brief  Negates the elements of a Q7 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_q7(
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Negates the elements of a Q15 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);


  /**
   * @brief  Negates the elements of a Q31 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

/**
   * @brief         Compute the logical bitwise AND of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_and_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise AND of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_and_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise AND of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_and_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise OR of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_or_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise OR of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_or_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise OR of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_or_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise NOT of a fixed-point vector.
   * @param[in]     pSrc       points to input vector 
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_not_u16(
    const uint16_t * pSrc,
          uint16_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise NOT of a fixed-point vector.
   * @param[in]     pSrc       points to input vector 
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_not_u32(
    const uint32_t * pSrc,
          uint32_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise NOT of a fixed-point vector.
   * @param[in]     pSrc       points to input vector 
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_not_u8(
    const uint8_t * pSrc,
          uint8_t * pDst,
          uint32_t blockSize);

/**
   * @brief         Compute the logical bitwise XOR of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_xor_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise XOR of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_xor_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize);

  /**
   * @brief         Compute the logical bitwise XOR of two fixed-point vectors.
   * @param[in]     pSrcA      points to input vector A
   * @param[in]     pSrcB      points to input vector B
   * @param[out]    pDst       points to output vector
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_xor_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
    uint32_t blockSize);

  /**
  @brief         Elementwise floating-point clipping
  @param[in]     pSrc          points to input values
  @param[out]    pDst          points to output clipped values
  @param[in]     low           lower bound
  @param[in]     high          higher bound
  @param[in]     numSamples    number of samples to clip
  @return        none
 */

void arm_clip_f32(const float32_t * pSrc, 
  float32_t * pDst, 
  float32_t low, 
  float32_t high, 
  uint32_t numSamples);

  /**
  @brief         Elementwise fixed-point clipping
  @param[in]     pSrc          points to input values
  @param[out]    pDst          points to output clipped values
  @param[in]     low           lower bound
  @param[in]     high          higher bound
  @param[in]     numSamples    number of samples to clip
  @return        none
 */

void arm_clip_q31(const q31_t * pSrc, 
  q31_t * pDst, 
  q31_t low, 
  q31_t high, 
  uint32_t numSamples);

  /**
  @brief         Elementwise fixed-point clipping
  @param[in]     pSrc          points to input values
  @param[out]    pDst          points to output clipped values
  @param[in]     low           lower bound
  @param[in]     high          higher bound
  @param[in]     numSamples    number of samples to clip
  @return        none
 */

void arm_clip_q15(const q15_t * pSrc, 
  q15_t * pDst, 
  q15_t low, 
  q15_t high, 
  uint32_t numSamples);

  /**
  @brief         Elementwise fixed-point clipping
  @param[in]     pSrc          points to input values
  @param[out]    pDst          points to output clipped values
  @param[in]     low           lower bound
  @param[in]     high          higher bound
  @param[in]     numSamples    number of samples to clip
  @return        none
 */

void arm_clip_q7(const q7_t * pSrc, 
  q7_t * pDst, 
  q7_t low, 
  q7_t high, 
  uint32_t numSamples);


#ifdef   __cplusplus
}
#endif

#endif /* ifndef _BASIC_MATH_FUNCTIONS_H_ */
