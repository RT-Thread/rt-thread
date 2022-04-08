/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_and_u32.c
 * Description:  uint32_t bitwise AND
 *
 * $Date:        14 November 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_math.h"

/**
  @ingroup groupMath
 */

/**
  @addtogroup And
  @{
 */

/**
  @brief         Compute the logical bitwise AND of two fixed-point vectors.
  @param[in]     pSrcA      points to input vector A
  @param[in]     pSrcB      points to input vector B
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void arm_and_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize)
{
    uint32_t blkCnt;      /* Loop counter */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
    q31x4_t vecSrcA, vecSrcB;

    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 2;

    while (blkCnt > 0U)
    {
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);

        vst1q(pDst, vandq_u32(vecSrcA, vecSrcB) );

        pSrcA += 4;
        pSrcB += 4;
        pDst  += 4;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 3;

    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp32q(blkCnt);
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);
        vstrwq_p(pDst, vandq_u32(vecSrcA, vecSrcB), p0);
    }
#else
#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint32x4_t vecA, vecB;

    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 2U;

    while (blkCnt > 0U)
    {
        vecA = vld1q_u32(pSrcA);
        vecB = vld1q_u32(pSrcB);

        vst1q_u32(pDst, vandq_u32(vecA, vecB) );

        pSrcA += 4;
        pSrcB += 4;
        pDst  += 4;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 3;
#else
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
#endif

    while (blkCnt > 0U)
    {
        *pDst++ = (*pSrcA++)&(*pSrcB++);

        /* Decrement the loop counter */
        blkCnt--;
    }
#endif /* if defined(ARM_MATH_MVEI) */
}

/**
  @} end of And group
 */
