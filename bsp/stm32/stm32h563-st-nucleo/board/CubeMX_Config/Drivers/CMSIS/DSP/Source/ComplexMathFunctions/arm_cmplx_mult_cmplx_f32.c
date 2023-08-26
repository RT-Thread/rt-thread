/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cmplx_mult_cmplx_f32.c
 * Description:  Floating-point complex-by-complex multiplication
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

#include "dsp/complex_math_functions.h"

/**
  @ingroup groupCmplxMath
 */

/**
  @defgroup CmplxByCmplxMult Complex-by-Complex Multiplication

  Multiplies a complex vector by another complex vector and generates a complex result.
  The data in the complex arrays is stored in an interleaved fashion
  (real, imag, real, imag, ...).
  The parameter <code>numSamples</code> represents the number of complex
  samples processed.  The complex arrays have a total of <code>2*numSamples</code>
  real values.

  The underlying algorithm is used:

  <pre>
  for (n = 0; n < numSamples; n++) {
      pDst[(2*n)+0] = pSrcA[(2*n)+0] * pSrcB[(2*n)+0] - pSrcA[(2*n)+1] * pSrcB[(2*n)+1];
      pDst[(2*n)+1] = pSrcA[(2*n)+0] * pSrcB[(2*n)+1] + pSrcA[(2*n)+1] * pSrcB[(2*n)+0];
  }
  </pre>

  There are separate functions for floating-point, Q15, and Q31 data types.
 */

/**
  @addtogroup CmplxByCmplxMult
  @{
 */

/**
  @brief         Floating-point complex-by-complex multiplication.
  @param[in]     pSrcA       points to first input vector
  @param[in]     pSrcB       points to second input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none
 */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_cmplx_mult_cmplx_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t numSamples)
{
     int32_t         blkCnt;
    f32x4_t         vecSrcA, vecSrcB;
    f32x4_t         vecSrcC, vecSrcD;
    f32x4_t         vec_acc;

    blkCnt = numSamples >> 2;
    blkCnt -= 1;
    if (blkCnt > 0) {
        /* should give more freedom to generate stall free code */
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);
        pSrcA += 4;
        pSrcB += 4;

        while (blkCnt > 0) {
            vec_acc = vcmulq(vecSrcA, vecSrcB);
            vecSrcC = vld1q(pSrcA);
            pSrcA += 4;

            vec_acc = vcmlaq_rot90(vec_acc, vecSrcA, vecSrcB);
            vecSrcD = vld1q(pSrcB);
            pSrcB += 4;
            vst1q(pDst, vec_acc);
            pDst += 4;

            vec_acc = vcmulq(vecSrcC, vecSrcD);
            vecSrcA = vld1q(pSrcA);
            pSrcA += 4;

            vec_acc = vcmlaq_rot90(vec_acc, vecSrcC, vecSrcD);
            vecSrcB = vld1q(pSrcB);
            pSrcB += 4;
            vst1q(pDst, vec_acc);
            pDst += 4;
            /*
             * Decrement the blockSize loop counter
             */
            blkCnt--;
        }

        /* process last elements out of the loop avoid the armclang breaking the SW pipeline */
        vec_acc = vcmulq(vecSrcA, vecSrcB);
        vecSrcC = vld1q(pSrcA);

        vec_acc = vcmlaq_rot90(vec_acc, vecSrcA, vecSrcB);
        vecSrcD = vld1q(pSrcB);
        vst1q(pDst, vec_acc);
        pDst += 4;

        vec_acc = vcmulq(vecSrcC, vecSrcD);
        vec_acc = vcmlaq_rot90(vec_acc, vecSrcC, vecSrcD);
        vst1q(pDst, vec_acc);
        pDst += 4;

        /*
         * tail
         */
        blkCnt = CMPLX_DIM * (numSamples & 3);
        while (blkCnt > 0) {
            mve_pred16_t    p = vctp32q(blkCnt);
            pSrcA += 4;
            pSrcB += 4;

            vecSrcA = vldrwq_z_f32(pSrcA, p);
            vecSrcB = vldrwq_z_f32(pSrcB, p);
            vec_acc = vcmulq_m(vuninitializedq_f32(),vecSrcA, vecSrcB, p);
            vec_acc = vcmlaq_rot90_m(vec_acc, vecSrcA, vecSrcB, p);

            vstrwq_p_f32(pDst, vec_acc, p);
            pDst += 4;

            blkCnt -= 4;
        }
    } else {
        /* small vector */
        blkCnt = numSamples * CMPLX_DIM;
        vec_acc = vdupq_n_f32(0.0f);

        do {
            mve_pred16_t    p = vctp32q(blkCnt);

            vecSrcA = vldrwq_z_f32(pSrcA, p);
            vecSrcB = vldrwq_z_f32(pSrcB, p);

            vec_acc = vcmulq_m(vuninitializedq_f32(),vecSrcA, vecSrcB, p);
            vec_acc = vcmlaq_rot90_m(vec_acc, vecSrcA, vecSrcB, p);
            vstrwq_p_f32(pDst, vec_acc, p);
            pDst += 4;

            /*
             * Decrement the blkCnt loop counter
             * Advance vector source and destination pointers
             */
            pSrcA += 4;
            pSrcB += 4;
            blkCnt -= 4;
        }
        while (blkCnt > 0);
    }

}

#else
void arm_cmplx_mult_cmplx_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t numSamples)
{
    uint32_t blkCnt;                               /* Loop counter */
    float32_t a, b, c, d;  /* Temporary variables to store real and imaginary values */

#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)
    float32x4x2_t va, vb;
    float32x4x2_t outCplx;

    /* Compute 4 outputs at a time */
    blkCnt = numSamples >> 2U;

    while (blkCnt > 0U)
    {
        va = vld2q_f32(pSrcA);  // load & separate real/imag pSrcA (de-interleave 2)
        vb = vld2q_f32(pSrcB);  // load & separate real/imag pSrcB

	/* Increment pointers */
        pSrcA += 8;
        pSrcB += 8;
	
	/* Re{C} = Re{A}*Re{B} - Im{A}*Im{B} */
        outCplx.val[0] = vmulq_f32(va.val[0], vb.val[0]);
        outCplx.val[0] = vmlsq_f32(outCplx.val[0], va.val[1], vb.val[1]);

	/* Im{C} = Re{A}*Im{B} + Im{A}*Re{B} */
        outCplx.val[1] = vmulq_f32(va.val[0], vb.val[1]);
        outCplx.val[1] = vmlaq_f32(outCplx.val[1], va.val[1], vb.val[0]);

        vst2q_f32(pDst, outCplx);

	/* Increment pointer */
        pDst += 8;

	/* Decrement the loop counter */
        blkCnt--;
    }

    /* Tail */
    blkCnt = numSamples & 3;

#else
#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = numSamples >> 2U;

  while (blkCnt > 0U)
  {
    /* C[2 * i    ] = A[2 * i] * B[2 * i    ] - A[2 * i + 1] * B[2 * i + 1]. */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i    ]. */

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    /* store result in destination buffer. */
    *pDst++ = (a * c) - (b * d);
    *pDst++ = (a * d) + (b * c);

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (a * c) - (b * d);
    *pDst++ = (a * d) + (b * c);

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (a * c) - (b * d);
    *pDst++ = (a * d) + (b * c);

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (a * c) - (b * d);
    *pDst++ = (a * d) + (b * c);

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = numSamples % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = numSamples;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */
#endif /* #if defined(ARM_MATH_NEON) */

  while (blkCnt > 0U)
  {
    /* C[2 * i    ] = A[2 * i] * B[2 * i    ] - A[2 * i + 1] * B[2 * i + 1]. */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i    ]. */

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store result in destination buffer. */
    *pDst++ = (a * c) - (b * d);
    *pDst++ = (a * d) + (b * c);

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of CmplxByCmplxMult group
 */
