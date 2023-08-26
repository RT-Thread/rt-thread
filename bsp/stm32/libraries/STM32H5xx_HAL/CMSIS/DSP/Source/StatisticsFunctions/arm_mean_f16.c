/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mean_f16.c
 * Description:  Mean value of a floating-point vector
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

#include "dsp/statistics_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)


/**
  @ingroup groupStats
 */

/**
  @defgroup mean Mean

  Calculates the mean of the input vector. Mean is defined as the average of the elements in the vector.
  The underlying algorithm is used:

  <pre>
      Result = (pSrc[0] + pSrc[1] + pSrc[2] + ... + pSrc[blockSize-1]) / blockSize;
  </pre>

  There are separate functions for floating-point, Q31, Q15, and Q7 data types.
 */

/**
  @addtogroup mean
  @{
 */

/**
  @brief         Mean value of a floating-point vector.
  @param[in]     pSrc       points to the input vector.
  @param[in]     blockSize  number of samples in input vector.
  @param[out]    pResult    mean value returned here.
  @return        none
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_mean_f16(
  const float16_t * pSrc,
  uint32_t blockSize,
  float16_t * pResult)
{
    int32_t  blkCnt;           /* loop counters */
    f16x8_t vecSrc;
    f16x8_t sumVec = vdupq_n_f16(0.0f16);

    blkCnt = blockSize;
    do {
        mve_pred16_t p = vctp16q(blkCnt);

        vecSrc = vldrhq_z_f16((float16_t const *) pSrc, p);
        sumVec = vaddq_m_f16(sumVec, sumVec, vecSrc, p);

        blkCnt -= 8;
        pSrc += 8;
    }
    while (blkCnt > 0);

    *pResult = vecAddAcrossF16Mve(sumVec) / (float16_t) blockSize;
}


#else

void arm_mean_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        float16_t sum = 0.0f;                          /* Temporary result storage */

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    sum += *pSrc++;

    sum += *pSrc++;

    sum += *pSrc++;

    sum += *pSrc++;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) */
    sum += *pSrc++;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* C = (A[0] + A[1] + A[2] + ... + A[blockSize-1]) / blockSize  */
  /* Store result to destination */
  *pResult = (sum / (float16_t)blockSize);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of mean group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

