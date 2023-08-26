/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_or_u8.c
 * Description:  uint8_t bitwise inclusive OR
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

#include "dsp/basic_math_functions.h"

/**
  @ingroup groupMath
 */

/**
  @addtogroup Or
  @{
 */

/**
  @brief         Compute the logical bitwise OR of two fixed-point vectors.
  @param[in]     pSrcA      points to input vector A
  @param[in]     pSrcB      points to input vector B
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void arm_or_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
          uint32_t blockSize)
{
    uint32_t blkCnt;      /* Loop counter */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint8x16_t vecSrcA, vecSrcB;

    /* Compute 16 outputs at a time */
    blkCnt = blockSize >> 4;

    while (blkCnt > 0U)
    {
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);

        vst1q(pDst, vorrq_u8(vecSrcA, vecSrcB) );

        pSrcA += 16;
        pSrcB += 16;
        pDst  += 16;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 0xF;

    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp8q(blkCnt);
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);
        vstrbq_p(pDst, vorrq_u8(vecSrcA, vecSrcB), p0);
    }
#else
#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint8x16_t vecA, vecB;

    /* Compute 16 outputs at a time */
    blkCnt = blockSize >> 4U;

    while (blkCnt > 0U)
    {
        vecA = vld1q_u8(pSrcA);
        vecB = vld1q_u8(pSrcB);

        vst1q_u8(pDst, vorrq_u8(vecA, vecB) );

        pSrcA += 16;
        pSrcB += 16;
        pDst  += 16;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 0xF;
#else
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
#endif

    while (blkCnt > 0U)
    {
        *pDst++ = (*pSrcA++)|(*pSrcB++);

        /* Decrement the loop counter */
        blkCnt--;
    }
#endif /* if defined(ARM_MATH_MVEI) */
}
/**
  @} end of Or group
 */
