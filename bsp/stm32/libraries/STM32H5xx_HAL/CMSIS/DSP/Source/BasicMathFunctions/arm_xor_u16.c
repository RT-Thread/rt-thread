/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_xor_u16.c
 * Description:  uint16_t bitwise exclusive OR
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
  @defgroup Xor Vector bitwise exclusive OR

  Compute the logical bitwise XOR.

  There are separate functions for uint32_t, uint16_t, and uint8_t data types.
 */

/**
  @addtogroup Xor
  @{
 */

/**
  @brief         Compute the logical bitwise XOR of two fixed-point vectors.
  @param[in]     pSrcA      points to input vector A
  @param[in]     pSrcB      points to input vector B
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void arm_xor_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize)
{
    uint32_t blkCnt;      /* Loop counter */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint16x8_t vecSrcA, vecSrcB;

    /* Compute 8 outputs at a time */
    blkCnt = blockSize >> 3;

    while (blkCnt > 0U)
    {
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);

        vst1q(pDst, veorq_u16(vecSrcA, vecSrcB) );

        pSrcA += 8;
        pSrcB += 8;
        pDst  += 8;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 7;

    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);
        vstrhq_p(pDst, veorq_u16(vecSrcA, vecSrcB), p0);
    }
#else
#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint16x8_t vecA, vecB;

    /* Compute 8 outputs at a time */
    blkCnt = blockSize >> 3U;

    while (blkCnt > 0U)
    {
        vecA = vld1q_u16(pSrcA);
        vecB = vld1q_u16(pSrcB);

        vst1q_u16(pDst, veorq_u16(vecA, vecB) );

        pSrcA += 8;
        pSrcB += 8;
        pDst  += 8;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 7;
#else
    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;
#endif

    while (blkCnt > 0U)
    {
        *pDst++ = (*pSrcA++)^(*pSrcB++);

        /* Decrement the loop counter */
        blkCnt--;
    }
#endif /* if defined(ARM_MATH_MVEI) */
}

/**
  @} end of Xor group
 */
