/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_rfft_q31.c
 * Description:  FFT & RIFFT Q31 process function
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

#include "dsp/transform_functions.h"

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
  @par
                   For the RIFFT, the source buffer must at least have length 
                   fftLenReal + 2.
                   The last two elements must be equal to what would be generated
                   by the RFFT:
                     (pSrc[0] - pSrc[1]) >> 1 and 0

 */

void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
        q31_t * pSrc,
        q31_t * pDst)
{
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
  const arm_cfft_instance_q31 *S_CFFT = &(S->cfftInst);
#else
  const arm_cfft_instance_q31 *S_CFFT = S->pCfft;
#endif
        uint32_t L2 = S->fftLenReal >> 1U;

  /* Calculation of RIFFT of input */
  if (S->ifftFlagR == 1U)
  {
     /*  Real IFFT core process */
     arm_split_rifft_q31 (pSrc, L2, S->pTwiddleAReal, S->pTwiddleBReal, pDst, S->twidCoefRModifier);

     /* Complex IFFT process */
     arm_cfft_q31 (S_CFFT, pDst, S->ifftFlagR, S->bitReverseFlagR);

     arm_shift_q31(pDst, 1, pDst, S->fftLenReal);
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

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_fft.h"

#if defined(__CMSIS_GCC_H)

#define MVE_CMPLX_MULT_FX_AxB_S32(A,B)          vqdmladhxq_s32(vqdmlsdhq_s32((__typeof(A))vuninitializedq_s32(), A, B), A, B)
#define MVE_CMPLX_MULT_FX_AxConjB_S32(A,B)      vqdmladhq_s32(vqdmlsdhxq_s32((__typeof(A))vuninitializedq_s32(), A, B), A, B)

#endif 

void arm_split_rfft_q31(
    q31_t       *pSrc,
    uint32_t     fftLen,
    const q31_t       *pATable,
    const q31_t       *pBTable,
    q31_t       *pDst,
    uint32_t     modifier)
{
    uint32_t        i;          /* Loop Counter */
    const q31_t    *pCoefA, *pCoefB;    /* Temporary pointers for twiddle factors */
    q31_t          *pOut1 = &pDst[2];
    q31_t          *pIn1 = &pSrc[2];
    uint32x4_t      offset = { 2, 3, 0, 1 };
    uint32x4_t      offsetCoef = { 0, 1, modifier * 2, modifier * 2 + 1 };

    offset = offset + (2 * fftLen - 4);


    /* Init coefficient pointers */
    pCoefA = &pATable[modifier * 2];
    pCoefB = &pBTable[modifier * 2];

    const q31_t    *pCoefAb, *pCoefBb;
    pCoefAb = pCoefA;
    pCoefBb = pCoefB;

    pIn1 = &pSrc[2];

    i = fftLen - 1U;
    i = i / 2 + 1;
    while (i > 0U) {
        q31x4_t         in1 = vld1q_s32(pIn1);
        q31x4_t         in2 = vldrwq_gather_shifted_offset_s32(pSrc, offset);
        q31x4_t         coefA = vldrwq_gather_shifted_offset_s32(pCoefAb, offsetCoef);
        q31x4_t         coefB = vldrwq_gather_shifted_offset_s32(pCoefBb, offsetCoef);
#if defined(__CMSIS_GCC_H)
        q31x4_t         out = vhaddq_s32(MVE_CMPLX_MULT_FX_AxB_S32(in1, coefA),MVE_CMPLX_MULT_FX_AxConjB_S32(coefB, in2));
#else
        q31x4_t         out = vhaddq_s32(MVE_CMPLX_MULT_FX_AxB(in1, coefA, q31x4_t),
                                         MVE_CMPLX_MULT_FX_AxConjB(coefB, in2, q31x4_t));
#endif
        vst1q(pOut1, out);
        pOut1 += 4;

        offsetCoef += modifier * 4;
        offset -= 4;

        pIn1 += 4;
        i -= 1;
    }

    pDst[2 * fftLen] = (pSrc[0] - pSrc[1]) >> 1U;
    pDst[2 * fftLen + 1] = 0;

    pDst[0] = (pSrc[0] + pSrc[1]) >> 1U;
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

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_split_rifft_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pATable,
  const q31_t * pBTable,
        q31_t * pDst,
        uint32_t modifier)
{
    uint32_t        i;          /* Loop Counter */
    const q31_t    *pCoefA, *pCoefB;    /* Temporary pointers for twiddle factors */
    q31_t          *pIn1;
    uint32x4_t      offset = { 2, 3, 0, 1 };
    uint32x4_t      offsetCoef = { 0, 1, modifier * 2, modifier * 2 + 1 };
    int32x4_t       conj = { 1, -1, 1, -1 };

    offset = offset + (2 * fftLen - 2);

    /* Init coefficient pointers */
    pCoefA = &pATable[0];
    pCoefB = &pBTable[0];

    const q31_t    *pCoefAb, *pCoefBb;
    pCoefAb = pCoefA;
    pCoefBb = pCoefB;

    pIn1 = &pSrc[0];

    i = fftLen;
    i = i >> 1;
    while (i > 0U) {
        q31x4_t         in1 = vld1q_s32(pIn1);
        q31x4_t         in2 = vldrwq_gather_shifted_offset_s32(pSrc, offset);
        q31x4_t         coefA = vldrwq_gather_shifted_offset_s32(pCoefAb, offsetCoef);
        q31x4_t         coefB = vldrwq_gather_shifted_offset_s32(pCoefBb, offsetCoef);

        /* can we avoid the conjugate here ? */
#if defined(__CMSIS_GCC_H)
        q31x4_t         out = vhaddq_s32(MVE_CMPLX_MULT_FX_AxConjB_S32(in1, coefA),
                                     vmulq_s32(conj, MVE_CMPLX_MULT_FX_AxB_S32(in2, coefB)));
#else
        q31x4_t         out = vhaddq_s32(MVE_CMPLX_MULT_FX_AxConjB(in1, coefA, q31x4_t),
                                         vmulq_s32(conj, MVE_CMPLX_MULT_FX_AxB(in2, coefB, q31x4_t)));
#endif
        vst1q_s32(pDst, out);
        pDst += 4;

        offsetCoef += modifier * 4;
        offset -= 4;

        pIn1 += 4;
        i -= 1;
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
