/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_df1_f16.c
 * Description:  Processing function for the floating-point Biquad cascade DirectFormI(DF1) filter
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

#include "dsp/filtering_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)
/**
  @ingroup groupFilters
 */


/**
  @addtogroup BiquadCascadeDF1
  @{
 */

/**
  @brief         Processing function for the floating-point Biquad cascade filter.
  @param[in]     S         points to an instance of the floating-point Biquad cascade structure
  @param[in]     pSrc      points to the block of input data
  @param[out]    pDst      points to the block of output data
  @param[in]     blockSize  number of samples to process
  @return        none
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_biquad_cascade_df1_f16(
  const arm_biquad_casd_df1_inst_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
    float16_t *pIn = (float16_t *)pSrc;      /*  source pointer            */
    float16_t *pOut = pDst;     /*  destination pointer       */
    float16_t *pState = S->pState;  /*  pState pointer            */
    const float16_t *pCoeffs = S->pCoeffs;    /*  coefficient pointer       */
    float16_t Xn1, Xn2, Yn1, Yn2;   /*  Filter pState variables   */
    float16_t X0, X1, X2, X3;   /*  temporary input           */
    float16_t X4, X5, X6, X7;   /*  temporary input           */
    _Float16 lastX, lastY;             /*  X,Y history for tail handling */
    f16x8_t coeffs;
    f16x8_t accVec;           /* accumultor vector */
    uint32_t  sample, stage = S->numStages; /*  loop counters             */

    do
    {
        /*
         * Reading the pState values
         */
        Xn1 = pState[0];
        Xn2 = pState[1];
        Yn1 = pState[2];
        Yn2 = pState[3];

        sample = blockSize >> 3U;

        /*
         * First part of the processing with loop unrolling.  Compute 8 outputs at a time.
         */
        while (sample > 0U)
        {
            X0 = *pIn++;
            X1 = *pIn++;
            X2 = *pIn++;
            X3 = *pIn++;
            X4 = *pIn++;
            X5 = *pIn++;
            X6 = *pIn++;
            X7 = *pIn++;

            coeffs = vld1q(pCoeffs);
            accVec = vmulq(coeffs, X7);

            coeffs = vld1q(&pCoeffs[8]);
            accVec = vfmaq(accVec, coeffs, X6);

            coeffs = vld1q(&pCoeffs[16]);
            accVec = vfmaq(accVec, coeffs, X5);

            coeffs = vld1q(&pCoeffs[24]);
            accVec = vfmaq(accVec, coeffs, X4);

            coeffs = vld1q(&pCoeffs[32]);
            accVec = vfmaq(accVec, coeffs, X3);

            coeffs = vld1q(&pCoeffs[40]);
            accVec = vfmaq(accVec, coeffs, X2);

            coeffs = vld1q(&pCoeffs[48]);
            accVec = vfmaq(accVec, coeffs, X1);

            coeffs = vld1q(&pCoeffs[56]);
            accVec = vfmaq(accVec, coeffs, X0);

            coeffs = vld1q(&pCoeffs[64]);
            accVec = vfmaq(accVec, coeffs, Xn1);

            coeffs = vld1q(&pCoeffs[72]);
            accVec = vfmaq(accVec, coeffs, Xn2);

            coeffs = vld1q(&pCoeffs[80]);
            accVec = vfmaq(accVec, coeffs, Yn1);

            coeffs = vld1q(&pCoeffs[88]);
            accVec = vfmaq(accVec, coeffs, Yn2);
            /*
             * Store the result in the accumulator in the destination buffer.
             */
            vst1q(pOut, accVec);
            pOut += 8;

            /*
             * update recurrence
             */
            Xn1 = X7;
            Xn2 = X6;
            Yn1 = vgetq_lane(accVec, 7);
            Yn2 = vgetq_lane(accVec, 6);
            /*
             * decrement the loop counter
             */
            sample--;
        }

        /*
         * If the blockSize is not a multiple of 8,
         * compute any remaining output samples here.
         */
        sample = blockSize & 0x7U;
        if (sample)
        {
            /* save previous X, Y for modulo 1 length case */
            lastX = X7;
            lastY = Yn1;

            X0 = *pIn++;
            X1 = *pIn++;
            X2 = *pIn++;
            X3 = *pIn++;
            X4 = *pIn++;
            X5 = *pIn++;
            X6 = *pIn++;
            X7 = *pIn++;

            coeffs = vld1q(pCoeffs);
            accVec = vmulq(coeffs, X7);

            coeffs = vld1q(&pCoeffs[8]);
            accVec = vfmaq(accVec, coeffs, X6);

            coeffs = vld1q(&pCoeffs[16]);
            accVec = vfmaq(accVec, coeffs, X5);

            coeffs = vld1q(&pCoeffs[24]);
            accVec = vfmaq(accVec, coeffs, X4);

            coeffs = vld1q(&pCoeffs[32]);
            accVec = vfmaq(accVec, coeffs, X3);

            coeffs = vld1q(&pCoeffs[40]);
            accVec = vfmaq(accVec, coeffs, X2);

            coeffs = vld1q(&pCoeffs[48]);
            accVec = vfmaq(accVec, coeffs, X1);

            coeffs = vld1q(&pCoeffs[56]);
            accVec = vfmaq(accVec, coeffs, X0);

            coeffs = vld1q(&pCoeffs[64]);
            accVec = vfmaq(accVec, coeffs, Xn1);

            coeffs = vld1q(&pCoeffs[72]);
            accVec = vfmaq(accVec, coeffs, Xn2);

            coeffs = vld1q(&pCoeffs[80]);
            accVec = vfmaq(accVec, coeffs, Yn1);

            coeffs = vld1q(&pCoeffs[88]);
            accVec = vfmaq(accVec, coeffs, Yn2);

            switch(sample)
            {
               case 1:
                 *pOut++ = vgetq_lane(accVec, 0);
                  Xn1 = X0;
                  Xn2 = lastX;
                  Yn1 = vgetq_lane(accVec, 0);
                  Yn2 = lastY;
               break;
               case 2:
                 *pOut++ = vgetq_lane(accVec, 0);
                 *pOut++ = vgetq_lane(accVec, 1);
                 Xn1 = X1;
                 Xn2 = X0;
                 Yn1 = vgetq_lane(accVec, 1);
                 Yn2 = vgetq_lane(accVec, 0);
               break;
               case 3:
                *pOut++ = vgetq_lane(accVec, 0);
                *pOut++ = vgetq_lane(accVec, 1);
                *pOut++ = vgetq_lane(accVec, 2);
                Xn1 = X2;
                Xn2 = X1;
                Yn1 = vgetq_lane(accVec, 2);
                Yn2 = vgetq_lane(accVec, 1);
               break;

               case 4:
                *pOut++ = vgetq_lane(accVec, 0);
                *pOut++ = vgetq_lane(accVec, 1);
                *pOut++ = vgetq_lane(accVec, 2);
                *pOut++ = vgetq_lane(accVec, 3);
                Xn1 = X3;
                Xn2 = X2;
                Yn1 = vgetq_lane(accVec, 3);
                Yn2 = vgetq_lane(accVec, 2);
               break;

               case 5:
                *pOut++ = vgetq_lane(accVec, 0);
                *pOut++ = vgetq_lane(accVec, 1);
                *pOut++ = vgetq_lane(accVec, 2);
                *pOut++ = vgetq_lane(accVec, 3);
                *pOut++ = vgetq_lane(accVec, 4);
                Xn1 = X4;
                Xn2 = X3;
                Yn1 = vgetq_lane(accVec, 4);
                Yn2 = vgetq_lane(accVec, 3);
               break;

               case 6:
                *pOut++ = vgetq_lane(accVec, 0);
                *pOut++ = vgetq_lane(accVec, 1);
                *pOut++ = vgetq_lane(accVec, 2);
                *pOut++ = vgetq_lane(accVec, 3);
                *pOut++ = vgetq_lane(accVec, 4);
                *pOut++ = vgetq_lane(accVec, 5);
                Xn1 = X5;
                Xn2 = X4;
                Yn1 = vgetq_lane(accVec, 5);
                Yn2 = vgetq_lane(accVec, 4);
               break;

               case 7:
                *pOut++ = vgetq_lane(accVec, 0);
                *pOut++ = vgetq_lane(accVec, 1);
                *pOut++ = vgetq_lane(accVec, 2);
                *pOut++ = vgetq_lane(accVec, 3);
                *pOut++ = vgetq_lane(accVec, 4);
                *pOut++ = vgetq_lane(accVec, 5);
                *pOut++ = vgetq_lane(accVec, 6);
                Xn1 = X6;
                Xn2 = X5;
                Yn1 = vgetq_lane(accVec, 6);
                Yn2 = vgetq_lane(accVec, 5);
               break;
            }
        }
        /*
         * Store the updated state variables back into the pState array
         */
        *pState++ = Xn1;
        *pState++ = Xn2;
        *pState++ = Yn1;
        *pState++ = Yn2;

        pCoeffs += sizeof(arm_biquad_mod_coef_f16) / sizeof(float16_t);
        /*
         * The first stage goes from the input buffer to the output buffer.
         * Subsequent numStages  occur in-place in the output buffer
         */
        pIn = pDst;
        /*
         * Reset the output pointer
         */
        pOut = pDst;
        /*
         * decrement the loop counter
         */
        stage--;
    }
    while (stage > 0U);
}

#else
void arm_biquad_cascade_df1_f16(
  const arm_biquad_casd_df1_inst_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
  const float16_t *pIn = pSrc;                         /* Source pointer */
        float16_t *pOut = pDst;                        /* Destination pointer */
        float16_t *pState = S->pState;                 /* pState pointer */
  const float16_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        _Float16 acc;                                 /* Accumulator */
        _Float16 b0, b1, b2, a1, a2;                  /* Filter coefficients */
        _Float16 Xn1, Xn2, Yn1, Yn2;                  /* Filter pState variables */
        _Float16 Xn;                                  /* Temporary input */
        uint32_t sample, stage = S->numStages;         /* Loop counters */

  do
  {
    /* Reading the coefficients */
    b0 = *pCoeffs++;
    b1 = *pCoeffs++;
    b2 = *pCoeffs++;
    a1 = *pCoeffs++;
    a2 = *pCoeffs++;

    /* Reading the pState values */
    Xn1 = pState[0];
    Xn2 = pState[1];
    Yn1 = pState[2];
    Yn2 = pState[3];

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)

    /* Apply loop unrolling and compute 4 output values simultaneously. */
    /* Variable acc hold output values that are being computed:
     *
     * acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]
     * acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]
     * acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]
     * acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]
     */

    /* Loop unrolling: Compute 4 outputs at a time */
    sample = blockSize >> 2U;

    while (sample > 0U)
    {
      /* Read the first input */
      Xn = *pIn++;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      Yn2 = (b0 * Xn) + (b1 * Xn1) + (b2 * Xn2) + (a1 * Yn1) + (a2 * Yn2);

      /* Store output in destination buffer. */
      *pOut++ = Yn2;

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as: */
      /* Xn2 = Xn1 */
      /* Xn1 = Xn  */
      /* Yn2 = Yn1 */
      /* Yn1 = acc */

      /* Read the second input */
      Xn2 = *pIn++;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      Yn1 = (b0 * Xn2) + (b1 * Xn) + (b2 * Xn1) + (a1 * Yn2) + (a2 * Yn1);

      /* Store output in destination buffer. */
      *pOut++ = Yn1;

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as: */
      /* Xn2 = Xn1 */
      /* Xn1 = Xn  */
      /* Yn2 = Yn1 */
      /* Yn1 = acc */

      /* Read the third input */
      Xn1 = *pIn++;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      Yn2 = (b0 * Xn1) + (b1 * Xn2) + (b2 * Xn) + (a1 * Yn1) + (a2 * Yn2);

      /* Store output in destination buffer. */
      *pOut++ = Yn2;

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as: */
      /* Xn2 = Xn1 */
      /* Xn1 = Xn  */
      /* Yn2 = Yn1 */
      /* Yn1 = acc */

      /* Read the forth input */
      Xn = *pIn++;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      Yn1 = (b0 * Xn) + (b1 * Xn1) + (b2 * Xn2) + (a1 * Yn2) + (a2 * Yn1);

      /* Store output in destination buffer. */
      *pOut++ = Yn1;

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as: */
      /* Xn2 = Xn1 */
      /* Xn1 = Xn  */
      /* Yn2 = Yn1 */
      /* Yn1 = acc */
      Xn2 = Xn1;
      Xn1 = Xn;

      /* decrement loop counter */
      sample--;
    }

    /* Loop unrolling: Compute remaining outputs */
    sample = blockSize & 0x3U;

#else

    /* Initialize blkCnt with number of samples */
    sample = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (sample > 0U)
    {
      /* Read the input */
      Xn = *pIn++;

      /* acc =  b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2] */
      acc = (b0 * Xn) + (b1 * Xn1) + (b2 * Xn2) + (a1 * Yn1) + (a2 * Yn2);

      /* Store output in destination buffer. */
      *pOut++ = acc;

      /* Every time after the output is computed state should be updated. */
      /* The states should be updated as: */
      /* Xn2 = Xn1 */
      /* Xn1 = Xn  */
      /* Yn2 = Yn1 */
      /* Yn1 = acc */
      Xn2 = Xn1;
      Xn1 = Xn;
      Yn2 = Yn1;
      Yn1 = acc;

      /* decrement loop counter */
      sample--;
    }

    /* Store the updated state variables back into the pState array */
    *pState++ = Xn1;
    *pState++ = Xn2;
    *pState++ = Yn1;
    *pState++ = Yn2;

    /* The first stage goes from the input buffer to the output buffer. */
    /* Subsequent numStages occur in-place in the output buffer */
    pIn = pDst;

    /* Reset output pointer */
    pOut = pDst;

    /* decrement loop counter */
    stage--;

  } while (stage > 0U);

}

/**
  @} end of BiquadCascadeDF1 group
 */
#endif /* #if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) */

#endif /*#if defined(ARM_FLOAT16_SUPPORTED)*/
