/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_var_f64.c
 * Description:  Variance of the elements of a floating-point vector
 *
 * $Date:        13 September 2021
 * $Revision:    V1.10.0
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
  @addtogroup variance
  @{
 */

/**
  @brief         Variance of the elements of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    variance value returned here
  @return        none
 */
void arm_var_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        float64_t sum = 0.;                          /* Temporary result storage */
        float64_t fSum = 0.;
        float64_t fMean, fValue;
  const float64_t * pInput = pSrc;

  if (blockSize <= 1U)
  {
    *pResult = 0;
    return;
  }

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */

    sum += *pInput++;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) / blockSize  */
  fMean = sum / (float64_t) blockSize;

  pInput = pSrc;

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

  while (blkCnt > 0U)
  {
    fValue = *pInput++ - fMean;
    fSum += fValue * fValue;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Variance */
  *pResult = fSum / (float64_t)(blockSize - 1.);
}

/**
  @} end of variance group
 */
