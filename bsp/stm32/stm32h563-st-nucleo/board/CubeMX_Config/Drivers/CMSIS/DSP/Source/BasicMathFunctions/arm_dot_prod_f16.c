/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_dot_prod_f16.c
 * Description:  Floating-point dot product
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
  @defgroup BasicDotProd Vector Dot Product

  Computes the dot product of two vectors.
  The vectors are multiplied element-by-element and then summed.

  <pre>
      sum = pSrcA[0]*pSrcB[0] + pSrcA[1]*pSrcB[1] + ... + pSrcA[blockSize-1]*pSrcB[blockSize-1]
  </pre>

  There are separate functions for floating-point, Q7, Q15, and Q31 data types.
 */

/**
  @addtogroup BasicDotProd
  @{
 */

/**
  @brief         Dot product of floating-point vectors.
  @param[in]     pSrcA      points to the first input vector.
  @param[in]     pSrcB      points to the second input vector.
  @param[in]     blockSize  number of samples in each vector.
  @param[out]    result     output result returned here.
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"


void arm_dot_prod_f16(
    const float16_t * pSrcA,
    const float16_t * pSrcB,
    uint32_t    blockSize,
    float16_t * result)
{
    f16x8_t vecA, vecB;
    f16x8_t vecSum;
    uint32_t blkCnt; 
    float16_t sum = 0.0f;  
    vecSum = vdupq_n_f16(0.0f);

    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 3U;
    while (blkCnt > 0U)
    {
        /*
         * C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1]
         * Calculate dot product and then store the result in a temporary buffer.
         * and advance vector source and destination pointers
         */
        vecA = vld1q(pSrcA);
        pSrcA += 8;
        
        vecB = vld1q(pSrcB);
        pSrcB += 8;

        vecSum = vfmaq(vecSum, vecA, vecB);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt --;
    }


    blkCnt = blockSize & 7;
    if (blkCnt > 0U)
    {
        /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */

        mve_pred16_t p0 = vctp16q(blkCnt);
        vecA = vld1q(pSrcA);
        vecB = vld1q(pSrcB);
        vecSum = vfmaq_m(vecSum, vecA, vecB, p0);
    }

    sum = vecAddAcrossF16Mve(vecSum);

    /* Store result in destination buffer */
    *result = sum;

}

#else
#if defined(ARM_FLOAT16_SUPPORTED)
void arm_dot_prod_f16(
  const float16_t * pSrcA,
  const float16_t * pSrcB,
        uint32_t blockSize,
        float16_t * result)
{
        uint32_t blkCnt;                               /* Loop counter */
        _Float16 sum = 0.0f;                          /* Temporary return variable */


#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  /* First part of the processing with loop unrolling. Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */

    /* Calculate dot product and store result in a temporary buffer. */
    sum += (_Float16)(*pSrcA++) * (_Float16)(*pSrcB++);

    sum += (_Float16)(*pSrcA++) * (_Float16)(*pSrcB++);

    sum += (_Float16)(*pSrcA++) * (_Float16)(*pSrcB++);

    sum += (_Float16)(*pSrcA++) * (_Float16)(*pSrcB++);

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
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */

    /* Calculate dot product and store result in a temporary buffer. */
    sum += (_Float16)(*pSrcA++) * (_Float16)(*pSrcB++);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in destination buffer */
  *result = sum;
}
#endif
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of BasicDotProd group
 */
