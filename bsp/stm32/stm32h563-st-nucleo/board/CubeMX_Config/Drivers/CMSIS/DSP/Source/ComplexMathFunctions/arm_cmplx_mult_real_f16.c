/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cmplx_mult_real_f16.c
 * Description:  Floating-point complex by real multiplication
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
  @defgroup CmplxByRealMult Complex-by-Real Multiplication

  Multiplies a complex vector by a real vector and generates a complex result.
  The data in the complex arrays is stored in an interleaved fashion
  (real, imag, real, imag, ...).
  The parameter <code>numSamples</code> represents the number of complex
  samples processed.  The complex arrays have a total of <code>2*numSamples</code>
  real values while the real array has a total of <code>numSamples</code>
  real values.

  The underlying algorithm is used:

  <pre>
  for (n = 0; n < numSamples; n++) {
      pCmplxDst[(2*n)+0] = pSrcCmplx[(2*n)+0] * pSrcReal[n];
      pCmplxDst[(2*n)+1] = pSrcCmplx[(2*n)+1] * pSrcReal[n];
  }
  </pre>

  There are separate functions for floating-point, Q15, and Q31 data types.
 */

/**
  @addtogroup CmplxByRealMult
  @{
 */

/**
  @brief         Floating-point complex-by-real multiplication.
  @param[in]     pSrcCmplx   points to complex input vector
  @param[in]     pSrcReal    points to real input vector
  @param[out]    pCmplxDst   points to complex output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_cmplx_mult_real_f16(
  const float16_t * pSrcCmplx,
  const float16_t * pSrcReal,
        float16_t * pCmplxDst,
        uint32_t numSamples)
{
    static const uint16_t stride_cmplx_x_real_16[8] = {
        0, 0, 1, 1, 2, 2, 3, 3
        };
    uint32_t blockSizeC = numSamples * CMPLX_DIM;   /* loop counters */
    uint32_t blkCnt;
    f16x8_t rVec;
    f16x8_t cmplxVec;
    f16x8_t dstVec;
    uint16x8_t strideVec;


    /* stride vector for pairs of real generation */
    strideVec = vld1q(stride_cmplx_x_real_16);

    /* Compute 4 complex outputs at a time */
    blkCnt = blockSizeC >> 3;
    while (blkCnt > 0U) 
    {
        cmplxVec = vld1q(pSrcCmplx);
        rVec = vldrhq_gather_shifted_offset_f16(pSrcReal, strideVec);
        dstVec = vmulq(cmplxVec, rVec);
        vst1q(pCmplxDst, dstVec);

        pSrcReal += 4;
        pSrcCmplx += 8;
        pCmplxDst += 8;
        blkCnt--;
    }

    blkCnt = blockSizeC & 7;
    if (blkCnt > 0U) {
        mve_pred16_t p0 = vctp16q(blkCnt);

        cmplxVec = vld1q(pSrcCmplx);
        rVec = vldrhq_gather_shifted_offset_f16(pSrcReal, strideVec);
        dstVec = vmulq(cmplxVec, rVec);
        vstrhq_p_f16(pCmplxDst, dstVec, p0);
    }
}

#else
void arm_cmplx_mult_real_f16(
  const float16_t * pSrcCmplx,
  const float16_t * pSrcReal,
        float16_t * pCmplxDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
        float16_t in;                                  /* Temporary variable */

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[2 * i    ] = A[2 * i    ] * B[i]. */
    /* C[2 * i + 1] = A[2 * i + 1] * B[i]. */

    in = *pSrcReal++;
    /* store result in destination buffer. */
    *pCmplxDst++ = *pSrcCmplx++ * in;
    *pCmplxDst++ = *pSrcCmplx++ * in;

    in = *pSrcReal++;
    *pCmplxDst++ = *pSrcCmplx++ * in;
    *pCmplxDst++ = *pSrcCmplx++ * in;

    in = *pSrcReal++;
    *pCmplxDst++ = *pSrcCmplx++ * in;
    *pCmplxDst++ = *pSrcCmplx++ * in;

    in = *pSrcReal++;
    *pCmplxDst++ = *pSrcCmplx++* in;
    *pCmplxDst++ = *pSrcCmplx++ * in;

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
    /* C[2 * i    ] = A[2 * i    ] * B[i]. */
    /* C[2 * i + 1] = A[2 * i + 1] * B[i]. */

    in = *pSrcReal++;
    /* store result in destination buffer. */
    *pCmplxDst++ = *pSrcCmplx++ * in;
    *pCmplxDst++ = *pSrcCmplx++ * in;

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of CmplxByRealMult group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */