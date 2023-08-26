/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_q15_to_float.c
 * Description:  Converts the elements of the Q15 vector to floating-point vector
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

#include "dsp/support_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)


/**
  @ingroup groupSupport
 */

/**
 * @defgroup q15_to_x  Convert 16-bit fixed point value
 */

/**
  @addtogroup q15_to_x
  @{
 */

/**
  @brief         Converts the elements of the Q15 vector to f16 vector.
  @param[in]     pSrc       points to the Q15 input vector
  @param[out]    pDst       points to the f16 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

  @par           Details
                   The equation used for the conversion process is:
  <pre>
      pDst[n] = (float16_t) pSrc[n] / 32768;   0 <= n < blockSize.
  </pre>
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_q15_to_f16(
  const q15_t * pSrc,
  float16_t * pDst,
  uint32_t blockSize)
{
    int32_t  blkCnt;           /* loop counters */
    q15x8_t vecDst;
    q15_t const *pSrcVec;

    pSrcVec = (q15_t const *) pSrc;
    blkCnt = blockSize >> 3;
    while (blkCnt > 0)
    {
        /* C = (float16_t) A / 32768 */
        /* convert from q15 to float and then store the results in the destination buffer */
        vecDst = vld1q(pSrcVec);   pSrcVec += 8;
        vstrhq(pDst, vcvtq_n_f16_s16(vecDst, 15));  pDst += 8;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = blockSize & 7;
    if (blkCnt > 0)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        vecDst = vld1q(pSrcVec);   pSrcVec += 8;
        vstrhq_p(pDst, vcvtq_n_f16_s16(vecDst, 15), p0);
    }
}
#else

void arm_q15_to_f16(
  const q15_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
        uint32_t blkCnt;                               /* Loop counter */
  const q15_t *pIn = pSrc;                             /* Source pointer */

#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = (float16_t) A / 32768 */

    /* Convert from q15 to float and store result in destination buffer */
    *pDst++ = ((_Float16) * pIn++ / 32768.0f16);
    *pDst++ = ((_Float16) * pIn++ / 32768.0f16);
    *pDst++ = ((_Float16) * pIn++ / 32768.0f16);
    *pDst++ = ((_Float16) * pIn++ / 32768.0f16);

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
    /* C = (float16_t) A / 32768 */

    /* Convert from q15 to float and store result in destination buffer */
    *pDst++ = ((_Float16) *pIn++ / 32768.0f16);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of q15_to_x group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

