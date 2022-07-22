/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_std_f32.c
 * Description:  Standard deviation of the elements of a floating-point vector
 *
 * $Date:        23 April 2021
 * $Revision:    V1.9.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2021 ARM Limited or its affiliates. All rights reserved.
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

#include "dsp/statistics_functions.h"

/**
  @ingroup groupStats
 */

/**
  @defgroup STD Standard deviation

  Calculates the standard deviation of the elements in the input vector.

  The float implementation is relying on arm_var_f32 which is using a two-pass algorithm
  to avoid problem of numerical instabilities and cancellation errors.

  Fixed point versions are using the standard textbook algorithm since the fixed point
  numerical behavior is different from the float one.

  Algorithm for fixed point versions is summarized below:


  <pre>
      Result = sqrt((sumOfSquares - sum<sup>2</sup> / blockSize) / (blockSize - 1))

      sumOfSquares = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + ... + pSrc[blockSize-1] * pSrc[blockSize-1]
      sum = pSrc[0] + pSrc[1] + pSrc[2] + ... + pSrc[blockSize-1]
  </pre>

  There are separate functions for floating point, Q31, and Q15 data types.
 */

/**
  @addtogroup STD
  @{
 */

/**
  @brief         Standard deviation of the elements of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    standard deviation value returned here
  @return        none
 */
void arm_std_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult)
{
  float32_t var;
  arm_var_f32(pSrc,blockSize,&var);
  arm_sqrt_f32(var, pResult);
}

/**
  @} end of STD group
 */
