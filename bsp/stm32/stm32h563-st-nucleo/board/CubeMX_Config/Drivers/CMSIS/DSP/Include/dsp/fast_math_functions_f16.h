/******************************************************************************
 * @file     fast_math_functions_f16.h
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

 
#ifndef _FAST_MATH_FUNCTIONS_F16_H_
#define _FAST_MATH_FUNCTIONS_F16_H_

#include "arm_math_types_f16.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

/* For sqrt_f32 */
#include "dsp/fast_math_functions.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if defined(ARM_FLOAT16_SUPPORTED)

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
__STATIC_FORCEINLINE arm_status arm_sqrt_f16(
  float16_t in,
  float16_t * pOut)
  {
    float32_t r;
    arm_status status;
    status=arm_sqrt_f32((float32_t)in,&r);
    *pOut=(float16_t)r;
    return(status);
  }


/**
  @} end of SQRT group
 */
  
/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vlog_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);

/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vexp_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);

  /**
  @brief         Floating-point vector of inverse values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
  void arm_vinverse_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize);

  /**
     @brief  Arc tangent in radian of y/x using sign of x and y to determine right quadrant.
     @param[in]   y  y coordinate
     @param[in]   x  x coordinate
     @param[out]  result  Result
     @return  error status.
   */
  arm_status arm_atan2_f16(float16_t y,float16_t x,float16_t *result);

#endif /*defined(ARM_FLOAT16_SUPPORTED)*/
#ifdef   __cplusplus
}
#endif

#endif /* ifndef _FAST_MATH_FUNCTIONS_F16_H_ */
