/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_rfft_q31.c
 * Description:  FFT & RIFFT Q31 process function
 *
 * $Date:        18. March 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_math.h"

/* ----------------------------------------------------------------------
 * Internal functions prototypes
 * -------------------------------------------------------------------- */

void arm_split_rfft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier);

void arm_split_rifft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier);

/**
  @addtogroup RealFFT
  @{
 */

/**
  @brief         Processing function for the Q31 RFFT/RIFFT.
  @param[in]     S     points to an instance of the Q31 RFFT/RIFFT structure
  @param[in]     pSrc  points to input buffer (Source buffer is modified by this function)
  @param[out]    pDst  points to output buffer
  @return        none

  @par           Input an output formats
                   Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT/CIFFT process.
                   Hence the output format is different for different RFFT sizes.
                   The input and output formats for different RFFT sizes and number of bits to upscale are mentioned in the tables below for RFFT and RIFFT:
  @par
                   \image html RFFTQ31.gif "Input and Output Formats for Q31 RFFT"
  @par
                   \image html RIFFTQ31.gif "Input and Output Formats for Q31 RIFFT"
  @par
                   If the input buffer is of length N, the output buffer must have length 2*N.
                   The input buffer is modified by this function.
 */

void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
        q31_t * pSrc,
        q31_t * pDst)
{
#if defined(ARM_MATH_MVEI)
  const arm_cfft_instance_q31 *S_CFFT = &(S->cfftInst);
#else
  const arm_cfft_instance_q31 *S_CFFT = S->pCfft;
#endif
        uint32_t L2 = S->fftLenReal >> 1U;
        uint32_t i;

  /* Calculation of RIFFT of input */
  if (S->ifftFlagR == 1U)
  {
     /*  Real IFFT core process */
     arm_split_rifft_q31 (pSrc, L2, S->pTwiddleAReal, S->pTwiddleBReal, pDst, S->twidCoefRModifier);

     /* Complex IFFT process */
     arm_cfft_q31 (S_CFFT, pDst, S->ifftFlagR, S->bitReverseFlagR);

     for(i = 0; i < S->fftLenReal; i++)
     {
        pDst[i] = pDst[i] << 1U;
     }
  }
  else
  {
     /* Calculation of RFFT of input */

     /* Complex FFT process */
     arm_cfft_q31 (S_CFFT, pSrc, S->ifftFlagR, S->bitReverseFlagR);

     /*  Real FFT core process */
     arm_split_rfft_q31 (pSrc, L2, S->pTwiddleAReal, S->pTwiddleBReal, pDst, S->twidCoefRModifier);
  }

}

/**
  @} end of RealFFT group
 */

/**
  @brief         Core Real FFT process
  @param[in]     pSrc      points to input buffer
  @param[in]     fftLen    length of FFT
  @param[in]     pATable   points to twiddle Coef A buffer
  @param[in]     pBTable   points to twiddle Coef B buffer
  @param[out]    pDst      points to output buffer
  @param[in]     modifier  twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none
 */

#if defined(ARM_MATH_MVEI)

void arm_split_rfft_q31(
    q31_t       *pSrc,
    uint32_t     fftLen,
    const q31_t       *pATable,
    const q31_t       *pBTable,
    q31_t       *pDst,
    uint32_t     modifier)
{
    q31_t const     *pCoefA, *pCoefB; /* Temporary pointers for twiddle factors */
    q31_t           *pDst1 = &pDst[2], *pDst2 = &pDst[(4U * fftLen) - 1U];    /* temp pointers for output buffer */
    q31_t const     *pSrc1 = &pSrc[2], *pSrc2 = &pSrc[(2U * fftLen) - 1U];    /* temp pointers for input buffer */
    q31_t const    *pVecSrc1;
    q31_t          *pVecDst1;
    q31x4x2_t      vecIn, vecSum;
    uint32_t         blkCnt;
    uint32x4_t     vecStridesFwd, vecStridesBkwd;
    q31x4_t        vecInBkwd, vecCoefFwd0, vecCoefFwd1;

    /*
     * Init coefficient pointers
     */
    pCoefA = &pATable[modifier * 2U];
    pCoefB = &pBTable[modifier * 2U];
    /*
     * scatter / gather offsets
     * for ascending & descending addressing
     */
    vecStridesFwd = vidupq_u32((uint32_t)0, 2);
    vecStridesBkwd = -vecStridesFwd;
    vecStridesFwd = vecStridesFwd * modifier;

    pVecSrc1 = (q31_t const *) pSrc1;
    pVecDst1 = pDst1;

    blkCnt = fftLen >> 2;
    while (blkCnt > 0U)
    {
        vecCoefFwd0 = vldrwq_gather_shifted_offset(pCoefA, vecStridesFwd);
        vecCoefFwd1 = vldrwq_gather_shifted_offset(&pCoefA[1], vecStridesFwd);
        vecIn = vld2q(pVecSrc1);
        pVecSrc1 += 8;
        /*
         * outR = *pSrc1 * CoefA1;
         */
        vecSum.val[0] = vmulhq(vecIn.val[0], vecCoefFwd0);
        /*
         * outI = *pSrc1++ * CoefA2;
         */
        vecSum.val[1] = vmulhq(vecIn.val[0], vecCoefFwd1);

        vecInBkwd = vldrwq_gather_shifted_offset(pSrc2, vecStridesBkwd);
        /*
         * outR -= (*pSrc1 + *pSrc2) * CoefA2;
         */
        vecInBkwd = vqaddq(vecIn.val[1], vecInBkwd);
        vecSum.val[0] = vqsubq(vecSum.val[0], vmulhq(vecInBkwd, vecCoefFwd1));

        vecInBkwd = vldrwq_gather_shifted_offset(pSrc2, vecStridesBkwd);
        /*
         * outI += *pSrc1++ * CoefA1;
         */
        vecSum.val[1] = vqaddq(vecSum.val[1], vmulhq(vecIn.val[1], vecCoefFwd0));

        vecCoefFwd0 = vldrwq_gather_shifted_offset(pCoefB, vecStridesFwd);
        /*
         * outI -= *pSrc2-- * CoefB1;
         */
        vecSum.val[1] = vqsubq(vecSum.val[1], vmulhq(vecInBkwd, vecCoefFwd0));

        vecInBkwd = vldrwq_gather_shifted_offset(&pSrc2[-1], vecStridesBkwd);
        /*
         * outI -= *pSrc2 * CoefA2;
         */
        vecSum.val[1] = vqsubq(vecSum.val[1], vmulhq(vecInBkwd, vecCoefFwd1));
        /*
         * outR += *pSrc2-- * CoefB1;
         */
        vecSum.val[0] = vqaddq(vecSum.val[0], vmulhq(vecInBkwd, vecCoefFwd0));

        vst2q(pVecDst1, vecSum);
        pVecDst1 += 8;
        /*
         * write complex conjugate output
         */
        vecSum.val[1] = -vecSum.val[1];
        vstrwq_scatter_shifted_offset(pDst2, vecStridesBkwd, vecSum.val[1]);
        vstrwq_scatter_shifted_offset(&pDst2[-1], vecStridesBkwd, vecSum.val[0]);
        /*
         * update fwd and backwd offsets
         */
        vecStridesFwd = vecStridesFwd + (modifier * 8U);
        vecStridesBkwd = vecStridesBkwd - 8;

        blkCnt--;
    }

    pDst[2U * fftLen] = (pSrc[0] - pSrc[1]) >> 1;
    pDst[(2U * fftLen) + 1U] = 0;

    pDst[0] = (pSrc[0] + pSrc[1]) >> 1;
    pDst[1] = 0;
}
#else
void arm_split_rfft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier)
{
        uint32_t i;                                    /* Loop Counter */
        q31_t outR, outI;                              /* Temporary variables for output */
  const q31_t *pCoefA, *pCoefB;                        /* Temporary pointers for twiddle factors */
        q31_t CoefA1, CoefA2, CoefB1;                  /* Temporary variables for twiddle coefficients */
        q31_t *pOut1 = &pDst[2], *pOut2 = &pDst[4 * fftLen - 1];
        q31_t *pIn1 =  &pSrc[2], *pIn2 =  &pSrc[2 * fftLen - 1];

  /* Init coefficient pointers */
  pCoefA = &pATable[modifier * 2];
  pCoefB = &pBTable[modifier * 2];

  i = fftLen - 1U;

  while (i > 0U)
  {
     /*
       outR = (  pSrc[2 * i]             * pATable[2 * i]
               - pSrc[2 * i + 1]         * pATable[2 * i + 1]
               + pSrc[2 * n - 2 * i]     * pBTable[2 * i]
               + pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);

       outI = (  pIn[2 * i + 1]         * pATable[2 * i]
               + pIn[2 * i]             * pATable[2 * i + 1]
               + pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
               - pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);
      */

     CoefA1 = *pCoefA++;
     CoefA2 = *pCoefA;

     /* outR = (pSrc[2 * i] * pATable[2 * i] */
     mult_32x32_keep32_R (outR, *pIn1, CoefA1);

     /* outI = pIn[2 * i] * pATable[2 * i + 1] */
     mult_32x32_keep32_R (outI, *pIn1++, CoefA2);

     /* - pSrc[2 * i + 1] * pATable[2 * i + 1] */
     multSub_32x32_keep32_R (outR, *pIn1, CoefA2);

     /* (pIn[2 * i + 1] * pATable[2 * i] */
     multAcc_32x32_keep32_R (outI, *pIn1++, CoefA1);

     /* pSrc[2 * n - 2 * i] * pBTable[2 * i]  */
     multSub_32x32_keep32_R (outR, *pIn2, CoefA2);
     CoefB1 = *pCoefB;

     /* pIn[2 * n - 2 * i] * pBTable[2 * i + 1] */
     multSub_32x32_keep32_R (outI, *pIn2--, CoefB1);

     /* pSrc[2 * n - 2 * i + 1] * pBTable[2 * i + 1] */
     multAcc_32x32_keep32_R (outR, *pIn2, CoefB1);

     /* pIn[2 * n - 2 * i + 1] * pBTable[2 * i] */
     multSub_32x32_keep32_R (outI, *pIn2--, CoefA2);

     /* write output */
     *pOut1++ = outR;
     *pOut1++ = outI;

     /* write complex conjugate output */
     *pOut2-- = -outI;
     *pOut2-- = outR;

     /* update coefficient pointer */
     pCoefB = pCoefB + (2 * modifier);
     pCoefA = pCoefA + (2 * modifier - 1);

     /* Decrement loop count */
     i--;
  }

  pDst[2 * fftLen]     = (pSrc[0] - pSrc[1]) >> 1U;
  pDst[2 * fftLen + 1] = 0;

  pDst[0] = (pSrc[0] + pSrc[1]) >> 1U;
  pDst[1] = 0;
}
#endif /* defined(ARM_MATH_MVEI) */

/**
  @brief         Core Real IFFT process
  @param[in]     pSrc      points to input buffer
  @param[in]     fftLen    length of FFT
  @param[in]     pATable   points to twiddle Coef A buffer
  @param[in]     pBTable   points to twiddle Coef B buffer
  @param[out]    pDst      points to output buffer
  @param[in]     modifier  twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table
  @return        none
 */

#if defined(ARM_MATH_MVEI)

void arm_split_rifft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier)
{
    q31_t const     *pCoefA, *pCoefB; /* Temporary pointers for twiddle factors */
    q31_t const     *pSrc1 = &pSrc[0], *pSrc2 = &pSrc[(2U * fftLen) + 1U];
    q31_t const    *pVecSrc1;
    q31_t          *pVecDst;
    q31x4x2_t      vecIn, vecSum;
    uint32_t         blkCnt;
    uint32x4_t     vecStridesFwd, vecStridesBkwd;
    q31x4_t        vecInBkwd, vecCoefFwd0, vecCoefFwd1;


    /*
     * Init coefficient pointers
     */
    pCoefA = &pATable[0];
    pCoefB = &pBTable[0];
    /*
     * scatter / gather offsets
     * for ascending & descending addressing
     */
    vecStridesFwd = vidupq_u32((uint32_t)0, 2);
    vecStridesBkwd = -vecStridesFwd;
    vecStridesFwd = vecStridesFwd * modifier;

    pVecSrc1 = (q31_t const *) pSrc1;
    pVecDst = pDst;

    blkCnt = fftLen >> 2;
    while (blkCnt > 0U)
    {
        vecCoefFwd0 = vldrwq_gather_shifted_offset(pCoefA, vecStridesFwd);
        vecCoefFwd1 = vldrwq_gather_shifted_offset(&pCoefA[1], vecStridesFwd);
        vecIn = vld2q(pVecSrc1);
        pVecSrc1 += 8;
        /*
         * outR = *pSrc1 * CoefA1;
         */
        vecSum.val[0] = vmulhq(vecIn.val[0], vecCoefFwd0);
        /*
         * outI = -(*pSrc1++) * CoefA2;
         */
        vecIn.val[0] =  (-vecIn.val[0]);
        vecSum.val[1] = vmulhq(vecIn.val[0], vecCoefFwd1);

        vecInBkwd = vldrwq_gather_shifted_offset(pSrc2, vecStridesBkwd);
        /*
         * outR += (*pSrc1 + *pSrc2) * CoefA2;
         */
        vecInBkwd = vqaddq(vecIn.val[1], vecInBkwd);
        vecSum.val[0] = vqaddq(vecSum.val[0], vmulhq(vecInBkwd, vecCoefFwd1));

        vecInBkwd = vldrwq_gather_shifted_offset(pSrc2, vecStridesBkwd);
        /*
         * outI += *pSrc1++ * CoefA1;
         */
        vecSum.val[1] = vqaddq(vecSum.val[1], vmulhq(vecIn.val[1], vecCoefFwd0));

        vecCoefFwd0 = vldrwq_gather_shifted_offset(pCoefB, vecStridesFwd);
        /*
         * outI -= *pSrc2-- * CoefB1;
         */
        vecSum.val[1] = vqsubq(vecSum.val[1], vmulhq(vecInBkwd, vecCoefFwd0));

        vecInBkwd = vldrwq_gather_shifted_offset(&pSrc2[-1], vecStridesBkwd);
        /*
         * outI += *pSrc2-- * CoefA2;;
         */
        vecSum.val[1] = vqaddq(vecSum.val[1], vmulhq(vecInBkwd, vecCoefFwd1));
        /*
         * outR += *pSrc2-- * CoefB1;
         */
        vecSum.val[0] = vqaddq(vecSum.val[0], vmulhq(vecInBkwd, vecCoefFwd0));

        vst2q(pVecDst, vecSum);
        pVecDst += 8;
        /*
         * update fwd and backwd offsets
         */
        vecStridesFwd = vecStridesFwd + (modifier * 8U);
        vecStridesBkwd = vecStridesBkwd - 8;

        blkCnt--;
    }
}
#else
void arm_split_rifft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier)
{
        q31_t outR, outI;                              /* Temporary variables for output */
  const q31_t *pCoefA, *pCoefB;                        /* Temporary pointers for twiddle factors */
        q31_t CoefA1, CoefA2, CoefB1;                  /* Temporary variables for twiddle coefficients */
        q31_t *pIn1 = &pSrc[0], *pIn2 = &pSrc[2 * fftLen + 1];

  pCoefA = &pATable[0];
  pCoefB = &pBTable[0];

  while (fftLen > 0U)
  {
     /*
       outR = (  pIn[2 * i]             * pATable[2 * i]
               + pIn[2 * i + 1]         * pATable[2 * i + 1]
               + pIn[2 * n - 2 * i]     * pBTable[2 * i]
               - pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1]);

       outI = (  pIn[2 * i + 1]         * pATable[2 * i]
               - pIn[2 * i]             * pATable[2 * i + 1]
               - pIn[2 * n - 2 * i]     * pBTable[2 * i + 1]
               - pIn[2 * n - 2 * i + 1] * pBTable[2 * i]);
      */

     CoefA1 = *pCoefA++;
     CoefA2 = *pCoefA;

     /* outR = (pIn[2 * i] * pATable[2 * i] */
     mult_32x32_keep32_R (outR, *pIn1, CoefA1);

     /* - pIn[2 * i] * pATable[2 * i + 1] */
     mult_32x32_keep32_R (outI, *pIn1++, -CoefA2);

     /* pIn[2 * i + 1] * pATable[2 * i + 1] */
     multAcc_32x32_keep32_R (outR, *pIn1, CoefA2);

     /* pIn[2 * i + 1] * pATable[2 * i] */
     multAcc_32x32_keep32_R (outI, *pIn1++, CoefA1);

     /* pIn[2 * n - 2 * i] * pBTable[2 * i] */
     multAcc_32x32_keep32_R (outR, *pIn2, CoefA2);
     CoefB1 = *pCoefB;

     /* pIn[2 * n - 2 * i] * pBTable[2 * i + 1] */
     multSub_32x32_keep32_R (outI, *pIn2--, CoefB1);

     /* pIn[2 * n - 2 * i + 1] * pBTable[2 * i + 1] */
     multAcc_32x32_keep32_R (outR, *pIn2, CoefB1);

     /* pIn[2 * n - 2 * i + 1] * pBTable[2 * i] */
     multAcc_32x32_keep32_R (outI, *pIn2--, CoefA2);

     /* write output */
     *pDst++ = outR;
     *pDst++ = outI;

     /* update coefficient pointer */
     pCoefB = pCoefB + (modifier * 2);
     pCoefA = pCoefA + (modifier * 2 - 1);

     /* Decrement loop count */
     fftLen--;
  }

}

#endif /* defined(ARM_MATH_MVEI) */
