/******************************************************************************
 * @file     fast_math_functions.h
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

 
#ifndef _FAST_MATH_FUNCTIONS_H_
#define _FAST_MATH_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#include "dsp/basic_math_functions.h"


#ifdef   __cplusplus
extern "C"
{
#endif

  /**
   * @brief Macros required for SINE and COSINE Fast math approximations
   */

#define FAST_MATH_TABLE_SIZE  512
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
  
#ifndef PI
  #define PI               3.14159265358979f
#endif


/**
 * @defgroup groupFastMath Fast Math Functions
 * This set of functions provides a fast approximation to sine, cosine, and square root.
 * As compared to most of the other functions in the CMSIS math library, the fast math functions
 * operate on individual values and not arrays.
 * There are separate functions for Q15, Q31, and floating-point data.
 *
 */

  /**
   * @ingroup groupFastMath
   */


/**
  @addtogroup sin
  @{
 */

/**
   * @brief  Fast approximation to the trigonometric sine function for floating-point data.
   * @param[in] x  input value in radians.
   * @return  sin(x).
   */
  float32_t arm_sin_f32(
  float32_t x);


  /**
   * @brief  Fast approximation to the trigonometric sine function for Q31 data.
   * @param[in] x  Scaled input value in radians.
   * @return  sin(x).
   */
  q31_t arm_sin_q31(
  q31_t x);


  /**
   * @brief  Fast approximation to the trigonometric sine function for Q15 data.
   * @param[in] x  Scaled input value in radians.
   * @return  sin(x).
   */
  q15_t arm_sin_q15(
  q15_t x);

/**
  @} end of sin group
 */

/**
  @addtogroup cos
  @{
 */

  /**
   * @brief  Fast approximation to the trigonometric cosine function for floating-point data.
   * @param[in] x  input value in radians.
   * @return  cos(x).
   */
  float32_t arm_cos_f32(
  float32_t x);


  /**
   * @brief Fast approximation to the trigonometric cosine function for Q31 data.
   * @param[in] x  Scaled input value in radians.
   * @return  cos(x).
   */
  q31_t arm_cos_q31(
  q31_t x);


  /**
   * @brief  Fast approximation to the trigonometric cosine function for Q15 data.
   * @param[in] x  Scaled input value in radians.
   * @return  cos(x).
   */
  q15_t arm_cos_q15(
  q15_t x);

/**
  @} end of cos group
 */


/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vlog_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);



/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vlog_f64(
  const float64_t * pSrc,
		float64_t * pDst,
		uint32_t blockSize);



  /**
   * @brief  q31 vector of log values.
   * @param[in]     pSrc       points to the input vector in q31
   * @param[out]    pDst       points to the output vector in q5.26
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_vlog_q31(const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);

  /**
   * @brief  q15 vector of log values.
   * @param[in]     pSrc       points to the input vector in q15
   * @param[out]    pDst       points to the output vector in q4.11
   * @param[in]     blockSize  number of samples in each vector
   * @return        none
   */
  void arm_vlog_q15(const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);



/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vexp_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);



/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vexp_f64(
  const float64_t * pSrc,
		float64_t * pDst,
		uint32_t blockSize);



 /**
   * @defgroup SQRT Square Root
   *
   * Computes the square root of a number.
   * There are separate functions for Q15, Q31, and floating-point data types.
   * The square root function is computed using the Newton-Raphson algorithm.
   * This is an iterative algorithm of the form:
   * <pre>
   *      x1 = x0 - f(x0)/f'(x0)
   * </pre>
   * where <code>x1</code> is the current estimate,
   * <code>x0</code> is the previous estimate, and
   * <code>f'(x0)</code> is the derivative of <code>f()</code> evaluated at <code>x0</code>.
   * For the square root function, the algorithm reduces to:
   * <pre>
   *     x0 = in/2                         [initial guess]
   *     x1 = 1/2 * ( x0 + in / x0)        [each iteration]
   * </pre>
   */


  /**
   * @addtogroup SQRT
   * @{
   */

/**
  @brief         Floating-point square root function.
  @param[in]     in    input value
  @param[out]    pOut  square root of input value
  @return        execution status
                   - \ref ARM_MATH_SUCCESS        : input value is positive
                   - \ref ARM_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
__STATIC_FORCEINLINE arm_status arm_sqrt_f32(
  const float32_t in,
  float32_t * pOut)
  {
    if (in >= 0.0f)
    {
#if defined ( __CC_ARM )
  #if defined __TARGET_FPU_VFP
      *pOut = __sqrtf(in);
  #else
      *pOut = sqrtf(in);
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
      __ASM("VSQRT.F32 %0,%1" : "=t"(*pOut) : "t"(in));
  #else
      *pOut = sqrtf(in);
  #endif

#else
      *pOut = sqrtf(in);
#endif

      return (ARM_MATH_SUCCESS);
    }
    else
    {
      *pOut = 0.0f;
      return (ARM_MATH_ARGUMENT_ERROR);
    }
  }


/**
  @brief         Q31 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x00000000 to 0x7FFFFFFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref ARM_MATH_SUCCESS        : input value is positive
                   - \ref ARM_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
arm_status arm_sqrt_q31(
  q31_t in,
  q31_t * pOut);


/**
  @brief         Q15 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x0000 to 0x7FFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref ARM_MATH_SUCCESS        : input value is positive
                   - \ref ARM_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
arm_status arm_sqrt_q15(
  q15_t in,
  q15_t * pOut);



  /**
   * @} end of SQRT group
   */

  /**
  @brief         Fixed point division
  @param[in]     numerator    Numerator
  @param[in]     denominator  Denominator
  @param[out]    quotient     Quotient value normalized between -1.0 and 1.0
  @param[out]    shift        Shift left value to get the unnormalized quotient
  @return        error status

  When dividing by 0, an error ARM_MATH_NANINF is returned. And the quotient is forced
  to the saturated negative or positive value.
 */

arm_status arm_divide_q15(q15_t numerator,
  q15_t denominator,
  q15_t *quotient,
  int16_t *shift);

  /**
  @brief         Fixed point division
  @param[in]     numerator    Numerator
  @param[in]     denominator  Denominator
  @param[out]    quotient     Quotient value normalized between -1.0 and 1.0
  @param[out]    shift        Shift left value to get the unnormalized quotient
  @return        error status

  When dividing by 0, an error ARM_MATH_NANINF is returned. And the quotient is forced
  to the saturated negative or positive value.
 */

arm_status arm_divide_q31(q31_t numerator,
  q31_t denominator,
  q31_t *quotient,
  int16_t *shift);



  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result
     @return  error status.
   */
  arm_status arm_atan2_f32(float32_t y,float32_t x,float32_t *result);


  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result in Q2.29
     @return  error status.
   */
  arm_status arm_atan2_q31(q31_t y,q31_t x,q31_t *result);

  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result in Q2.13
     @return  error status.
   */
  arm_status arm_atan2_q15(q15_t y,q15_t x,q15_t *result);

#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FAST_MATH_FUNCTIONS_H_ */
