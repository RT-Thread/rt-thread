/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_not_u8.c
 * Description:  uint8_t bitwise NOT
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
  @addtogroup Not
  @{
 */

/**
  @brief         Compute the logical bitwise NOT of a fixed-point vector.
  @param[in]     pSrc       points to input vector
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void arm_not_u8(
    const uint8_t * pSrc,
          uint8_t * pDst,
          uint32_t blockSize)
{
    uint32_t blkCnt;      /* Loop counter */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint8x16_t vecSrc;

    /* Compute 16 outputs at a time */
    blkCnt = blockSize >> 4;

    while (blkCnt > 0U)
    {
        vecSrc = vld1q(pSrc);

        vst1q(pDst, vmvnq_u8(vecSrc) );

        pSrc += 16;
        pDst += 16;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 0xF;

    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp8q(blkCnt);
        vecSrc = vld1q(pSrc);
        vstrbq_p(pDst, vmvnq_u8(vecSrc), p0);
    }
#else
#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)
    uint8x16_t inV;

    /* Compute 16 outputs at a time */
    blkCnt = blockSize >> 4U;

    while (blkCnt > 0U)
    {
        inV = vld1q_u8(pSrc);

        vst1q_u8(pDst, vmvnq_u8(inV) );

        pSrc += 16;
        pDst += 16;

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
        *pDst++ = ~(*pSrc++);

        /* Decrement the loop counter */
        blkCnt--;
    }
#endif /* if defined(ARM_MATH_MVEI) */
}

/**
  @} end of Not group
 */
