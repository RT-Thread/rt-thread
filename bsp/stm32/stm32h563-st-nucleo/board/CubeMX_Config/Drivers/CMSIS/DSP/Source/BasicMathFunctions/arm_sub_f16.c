/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_sub_f16.c
 * Description:  Floating-point vector subtraction
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

#include "dsp/basic_math_functions_f16.h"

/**
  @ingroup groupMath
 */

/**
  @defgroup BasicSub Vector Subtraction

  Element-by-element subtraction of two vectors.

  <pre>
      pDst[n] = pSrcA[n] - pSrcB[n],   0 <= n < blockSize.
  </pre>

  There are separate functions for floating-point, Q7, Q15, and Q31 data types.
 */

/**
  @addtogroup BasicSub
  @{
 */

/**
  @brief         Floating-point vector subtraction.
  @param[in]     pSrcA      points to the first input vector
  @param[in]     pSrcB      points to the second input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)
#include "arm_helium_utils.h"

void arm_sub_f16(
  const float16_t * pSrcA,
  const float16_t * pSrcB,
        float16_t * pDst,
        uint32_t blockSize)
{
    uint32_t blkCnt;                               /* Loop counter */

    f16x8_t vec1;
    f16x8_t vec2;
    f16x8_t res;

    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 3U;

    while (blkCnt > 0U)
    {
        /* C = A + B */

      /* Add and then store the results in the destination buffer. */
        vec1 = vld1q(pSrcA);
        vec2 = vld1q(pSrcB);
        res = vsubq(vec1, vec2);
        vst1q(pDst, res);

        /* Increment pointers */
        pSrcA += 8;
        pSrcB += 8; 
        pDst += 8;
        
        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 0x7;

    if (blkCnt > 0U)
    {
      /* C = A + B */
      mve_pred16_t p0 = vctp16q(blkCnt);
      vec1 = vld1q(pSrcA);
      vec2 = vld1q(pSrcB);
      vstrhq_p(pDst, vsubq(vec1,vec2), p0);
    }

}

#else
#if defined(ARM_FLOAT16_SUPPORTED)
void arm_sub_f16(
  const float16_t * pSrcA,
  const float16_t * pSrcB,
        float16_t * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = A - B */

    /* Subtract and store result in destination buffer. */
    *pDst++ = (_Float16)(*pSrcA++) - (_Float16)(*pSrcB++);

    *pDst++ = (_Float16)(*pSrcA++) - (_Float16)(*pSrcB++);

    *pDst++ = (_Float16)(*pSrcA++) - (_Float16)(*pSrcB++);

    *pDst++ = (_Float16)(*pSrcA++) - (_Float16)(*pSrcB++);

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
    /* C = A - B */

    /* Subtract and store result in destination buffer. */
    *pDst++ = (_Float16)(*pSrcA++) - (_Float16)(*pSrcB++);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of BasicSub group
 */
