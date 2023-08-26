/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mse_q15.c
 * Description:  Mean square error between two Q15 vectors
 *
 * $Date:        04 April 2022
 * $Revision:    V1.10.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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
  @addtogroup MSE
  @{
 */

/**
  @brief         Mean square error between two Q15 vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize   number of samples in input vector
  @param[out]    pResult     mean square error
  @return        none
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
void arm_mse_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t blockSize,
        q15_t * pResult)
{
    uint32_t  blkCnt;           /* loop counters */
    q15x8_t vecSrcA,vecSrcB;
    q63_t   sum = 0LL;

    blkCnt = blockSize >> 3U;
    while (blkCnt > 0U)
    {
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);

        vecSrcA = vshrq(vecSrcA,1);
        vecSrcB = vshrq(vecSrcB,1);

        vecSrcA = vqsubq(vecSrcA,vecSrcB);
        /*
         * sum lanes
         */
        sum = vmlaldavaq(sum, vecSrcA, vecSrcA);

        blkCnt--;
        pSrcA += 8;
        pSrcB += 8;
    }

    /*
     * tail
     */
    blkCnt = blockSize & 7;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);

        vecSrcA = vshrq(vecSrcA,1);
        vecSrcB = vshrq(vecSrcB,1);

        vecSrcA = vqsubq(vecSrcA,vecSrcB);

        sum = vmlaldavaq_p(sum, vecSrcA, vecSrcA, p0);
    }

    

    *pResult = (q15_t) __SSAT((q31_t) (sum / blockSize)>>13, 16);
}
#else
void arm_mse_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t blockSize,
        q15_t * pResult)
{
        uint32_t blkCnt;                               /* Loop counter */
        q63_t sum = 0;                                 /* Temporary result storage */
        q15_t inA,inB;                                       /* Temporary variable to store input value */


#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q15_t) __SSAT(((q31_t) inA - (q31_t)inB), 16);
    sum += (q63_t)((q31_t) inA * inA);

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q15_t) __SSAT(((q31_t) inA - (q31_t)inB), 16);
    sum += (q63_t)((q31_t) inA * inA);

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q15_t) __SSAT(((q31_t) inA - (q31_t)inB), 16);
    sum += (q63_t)((q31_t) inA * inA);

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q15_t) __SSAT(((q31_t) inA - (q31_t)inB), 16);
    sum += (q63_t)((q31_t) inA * inA);

    /* Decrement loop counter */
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

    inA = *pSrcA++ >> 1;
    inB = *pSrcB++ >> 1;
    inA = (q15_t) __SSAT(((q31_t) inA - (q31_t)inB), 16);
    sum += (q63_t)((q31_t) inA * inA);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in q15 format */
  *pResult = (q15_t) __SSAT((q31_t) (sum / blockSize)>>13, 16);
}
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of MSE group
 */
