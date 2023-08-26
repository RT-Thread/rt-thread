/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cmplx_mag_squared_f16.c
 * Description:  Floating-point complex magnitude squared
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

#include "dsp/complex_math_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

/**
  @ingroup groupCmplxMath
 */

/**
  @defgroup cmplx_mag_squared Complex Magnitude Squared

  Computes the magnitude squared of the elements of a complex data vector.

  The <code>pSrc</code> points to the source data and
  <code>pDst</code> points to the where the result should be written.
  <code>numSamples</code> specifies the number of complex samples
  in the input array and the data is stored in an interleaved fashion
  (real, imag, real, imag, ...).
  The input array has a total of <code>2*numSamples</code> values;
  the output array has a total of <code>numSamples</code> values.

  The underlying algorithm is used:

  <pre>
  for (n = 0; n < numSamples; n++) {
      pDst[n] = pSrc[(2*n)+0]^2 + pSrc[(2*n)+1]^2;
  }
  </pre>

  There are separate functions for floating-point, Q15, and Q31 data types.
 */

/**
  @addtogroup cmplx_mag_squared
  @{
 */

/**
  @brief         Floating-point complex magnitude squared.
  @param[in]     pSrc        points to input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_cmplx_mag_squared_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t numSamples)
{
    int32_t blockSize = numSamples;  /* loop counters */
    f16x8x2_t vecSrc;
    f16x8_t sum;

    /* Compute 4 complex samples at a time */
    while (blockSize > 0)
    {
        mve_pred16_t p = vctp16q(blockSize);
        vecSrc = vld2q(pSrc);
        sum = vmulq_m(vuninitializedq_f16(),vecSrc.val[0], vecSrc.val[0],p);
        sum = vfmaq_m(sum, vecSrc.val[1], vecSrc.val[1],p);
        vstrhq_p_f16(pDst, sum,p);

        pSrc += 16;
        pDst += 8;
        
        /*
         * Decrement the blockSize loop counter
         */
        blockSize-= 8;
    }

}

#else
void arm_cmplx_mag_squared_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
        _Float16 real, imag;                          /* Temporary input variables */

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */

    real = *pSrc++;
    imag = *pSrc++;
    *pDst++ = (real * real) + (imag * imag);

    real = *pSrc++;
    imag = *pSrc++;
    *pDst++ = (real * real) + (imag * imag);

    real = *pSrc++;
    imag = *pSrc++;
    *pDst++ = (real * real) + (imag * imag);

    real = *pSrc++;
    imag = *pSrc++;
    *pDst++ = (real * real) + (imag * imag);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = numSamples % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = numSamples;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* C[0] = (A[0] * A[0] + A[1] * A[1]) */

    real = *pSrc++;
    imag = *pSrc++;

    /* store result in destination buffer. */
    *pDst++ = (real * real) + (imag * imag);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of cmplx_mag_squared group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */