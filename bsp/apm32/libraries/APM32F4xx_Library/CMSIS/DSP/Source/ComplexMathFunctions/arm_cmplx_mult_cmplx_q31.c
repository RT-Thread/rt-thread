/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cmplx_mult_cmplx_q31.c
 * Description:  Q31 complex-by-complex multiplication
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
  @addtogroup CmplxByCmplxMult
  @{
 */

/**
  @brief         Q31 complex-by-complex multiplication.
  @param[in]     pSrcA       points to first input vector
  @param[in]     pSrcB       points to second input vector
  @param[out]    pDst        points to output vector
  @param[in]     numSamples  number of samples in each vector
  @return        none

  @par           Scaling and Overflow Behavior
                   The function implements 1.31 by 1.31 multiplications and finally output is converted into 3.29 format.
                   Input down scaling is not required.
 */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
void arm_cmplx_mult_cmplx_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t numSamples)
{
    int32_t         blkCnt;
    q31x4_t         vecSrcA, vecSrcB;
    q31x4_t         vecSrcC, vecSrcD;
    q31x4_t         vecDst;

    blkCnt = numSamples >> 2;
    blkCnt -= 1;
    if (blkCnt > 0) {
        /* should give more freedom to generate stall free code */
        vecSrcA = vld1q(pSrcA);
        vecSrcB = vld1q(pSrcB);
        pSrcA += 4;
        pSrcB += 4;

        while (blkCnt > 0) {

            /* C[2 * i] = A[2 * i] * B[2 * i] - A[2 * i + 1] * B[2 * i + 1].  */
            vecDst = vqdmlsdhq(vuninitializedq_s32(), vecSrcA, vecSrcB);
            vecSrcC = vld1q(pSrcA);
            pSrcA += 4;

            /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i].  */
            vecDst = vqdmladhxq(vecDst, vecSrcA, vecSrcB);
            vecSrcD = vld1q(pSrcB);
            pSrcB += 4;

            vst1q(pDst, vshrq(vecDst, 2));
            pDst += 4;

            vecDst = vqdmlsdhq(vuninitializedq_s32(), vecSrcC, vecSrcD);
            vecSrcA = vld1q(pSrcA);
            pSrcA += 4;

            vecDst = vqdmladhxq(vecDst, vecSrcC, vecSrcD);
            vecSrcB = vld1q(pSrcB);
            pSrcB += 4;

            vst1q(pDst, vshrq(vecDst, 2));
            pDst += 4;

            /*
             * Decrement the blockSize loop counter
             */
            blkCnt--;
        }

        /* process last elements out of the loop avoid the armclang breaking the SW pipeline */
        vecDst = vqdmlsdhq(vuninitializedq_s32(), vecSrcA, vecSrcB);
        vecSrcC = vld1q(pSrcA);

        vecDst = vqdmladhxq(vecDst, vecSrcA, vecSrcB);
        vecSrcD = vld1q(pSrcB);

        vst1q(pDst, vshrq(vecDst, 2));
        pDst += 4;

        vecDst = vqdmlsdhq(vuninitializedq_s32(), vecSrcC, vecSrcD);
        vecDst = vqdmladhxq(vecDst, vecSrcC, vecSrcD);

        vst1q(pDst, vshrq(vecDst, 2));
        pDst += 4;

        /*
         * tail
         */
        blkCnt = CMPLX_DIM * (numSamples & 3);
        do {
            mve_pred16_t    p = vctp32q(blkCnt);

            pSrcA += 4;
            pSrcB += 4;

            vecSrcA = vldrwq_z_s32(pSrcA, p);
            vecSrcB = vldrwq_z_s32(pSrcB, p);

            vecDst = vqdmlsdhq_m(vuninitializedq_s32(), vecSrcA, vecSrcB, p);
            vecDst = vqdmladhxq_m(vecDst, vecSrcA, vecSrcB, p);

            vecDst = vshrq_m(vuninitializedq_s32(), vecDst, 2, p);
            vstrwq_p_s32(pDst, vecDst, p);
            pDst += 4;

            blkCnt -= 4;
        }
        while ((int32_t) blkCnt > 0);
    } else {
        blkCnt = numSamples * CMPLX_DIM;
        while (blkCnt > 0) {
            mve_pred16_t    p = vctp32q(blkCnt);

            vecSrcA = vldrwq_z_s32(pSrcA, p);
            vecSrcB = vldrwq_z_s32(pSrcB, p);

            vecDst = vqdmlsdhq_m(vuninitializedq_s32(), vecSrcA, vecSrcB, p);
            vecDst = vqdmladhxq_m(vecDst, vecSrcA, vecSrcB, p);

            vecDst = vshrq_m(vuninitializedq_s32(), vecDst, 2, p);
            vstrwq_p_s32(pDst, vecDst, p);

            pDst += 4;
            pSrcA += 4;
            pSrcB += 4;

            blkCnt -= 4;
        }
    }
}
#else
void arm_cmplx_mult_cmplx_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t numSamples)
{
        uint32_t blkCnt;                               /* Loop counter */
        q31_t a, b, c, d;                              /* Temporary variables */

#if defined (ARM_MATH_LOOPUNROLL)

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
    /* store result in 3.29 format in destination buffer. */
    *pDst++ = (q31_t) ( (((q63_t) a * c) >> 33) - (((q63_t) b * d) >> 33) );
    *pDst++ = (q31_t) ( (((q63_t) a * d) >> 33) + (((q63_t) b * c) >> 33) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q31_t) ( (((q63_t) a * c) >> 33) - (((q63_t) b * d) >> 33) );
    *pDst++ = (q31_t) ( (((q63_t) a * d) >> 33) + (((q63_t) b * c) >> 33) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q31_t) ( (((q63_t) a * c) >> 33) - (((q63_t) b * d) >> 33) );
    *pDst++ = (q31_t) ( (((q63_t) a * d) >> 33) + (((q63_t) b * c) >> 33) );

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;
    *pDst++ = (q31_t) ( (((q63_t) a * c) >> 33) - (((q63_t) b * d) >> 33) );
    *pDst++ = (q31_t) ( (((q63_t) a * d) >> 33) + (((q63_t) b * c) >> 33) );

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
    /* C[2 * i    ] = A[2 * i] * B[2 * i    ] - A[2 * i + 1] * B[2 * i + 1]. */
    /* C[2 * i + 1] = A[2 * i] * B[2 * i + 1] + A[2 * i + 1] * B[2 * i    ]. */

    a = *pSrcA++;
    b = *pSrcA++;
    c = *pSrcB++;
    d = *pSrcB++;

    /* store result in 3.29 format in destination buffer. */
    *pDst++ = (q31_t) ( (((q63_t) a * c) >> 33) - (((q63_t) b * d) >> 33) );
    *pDst++ = (q31_t) ( (((q63_t) a * d) >> 33) + (((q63_t) b * c) >> 33) );

    /* Decrement loop counter */
    blkCnt--;
  }

}
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of CmplxByCmplxMult group
 */
