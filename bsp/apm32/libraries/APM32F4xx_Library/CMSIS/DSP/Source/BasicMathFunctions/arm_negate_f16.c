/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_negate_f16.c
 * Description:  Negates floating-point vectors
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
  @defgroup BasicNegate Vector Negate

  Negates the elements of a vector.

  <pre>
      pDst[n] = -pSrc[n],   0 <= n < blockSize.
  </pre>

  The functions support in-place computation allowing the source and
  destination pointers to reference the same memory buffer.
  There are separate functions for floating-point, Q7, Q15, and Q31 data types.
 */

/**
  @addtogroup BasicNegate
  @{
 */

/**
  @brief         Negates the elements of a floating-point vector.
  @param[in]     pSrc       points to input vector.
  @param[out]    pDst       points to output vector.
  @param[in]     blockSize  number of samples in each vector.
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_negate_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
    uint32_t blkCnt;                               /* Loop counter */
    f16x8_t vec1;
    f16x8_t res;


    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 3U;
    while (blkCnt > 0U)
    {
        /* C = |A| */

        /* Calculate absolute values and then store the results in the destination buffer. */
        vec1 = vld1q(pSrc);
        res = vnegq(vec1);
        vst1q(pDst, res);

        /* Increment pointers */
        pSrc += 8;
        pDst += 8;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = blockSize & 0x7;
    if (blkCnt > 0U)
    {
      /* C = |A| */
      mve_pred16_t p0 = vctp16q(blkCnt);
      vec1 = vld1q((float16_t const *) pSrc);
      vstrhq_p(pDst, vnegq(vec1), p0);
    }

}

#else
#if defined(ARM_FLOAT16_SUPPORTED)
void arm_negate_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */


#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = -A */

    /* Negate and store result in destination buffer. */
    *pDst++ = -*pSrc++;

    *pDst++ = -*pSrc++;

    *pDst++ = -*pSrc++;

    *pDst++ = -*pSrc++;

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
    /* C = -A */

    /* Negate and store result in destination buffer. */
    *pDst++ = -*pSrc++;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of BasicNegate group
 */
