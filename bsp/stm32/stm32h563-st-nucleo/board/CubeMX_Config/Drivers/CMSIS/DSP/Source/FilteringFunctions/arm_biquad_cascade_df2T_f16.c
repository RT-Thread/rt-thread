/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_df2T_f16.c
 * Description:  Processing function for floating-point transposed direct form II Biquad cascade filter
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
  @addtogroup BiquadCascadeDF2T
  @{
 */

/**
  @brief         Processing function for the floating-point transposed direct form II Biquad cascade filter.
  @param[in]     S         points to an instance of the filter data structure
  @param[in]     pSrc      points to the block of input data
  @param[out]    pDst      points to the block of output data
  @param[in]     blockSize number of samples to process
  @return        none
 */

#if (defined(ARM_MATH_MVE_FLOAT16) && defined(ARM_MATH_HELIUM_EXPERIMENTAL)) && !defined(ARM_MATH_AUTOVECTORIZE)
void arm_biquad_cascade_df2T_f16(
  const arm_biquad_cascade_df2T_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
    float16_t *pIn = (float16_t *)pSrc;                  /*  source pointer            */
    float16_t Xn0, Xn1;
    float16_t acc0, acc1;
    float16_t *pOut = pDst;                 /*  destination pointer       */
    float16_t *pState = S->pState;          /*  State pointer             */
    uint32_t  sample, stage = S->numStages; /*  loop counters             */
    float16_t const *pCurCoeffs =          /*  coefficient pointer       */
                (float16_t const *) S->pCoeffs;
    f16x8_t b0Coeffs, a0Coeffs;           /*  Coefficients vector       */
    f16x8_t b1Coeffs, a1Coeffs;           /*  Modified coef. vector     */
    f16x8_t state;                        /*  State vector              */

    do
    {
        /*
         * temporary carry variable for feeding the 128-bit vector shifter
         */
        uint32_t  tmp = 0;
        /*
         * Reading the coefficients
         * b0Coeffs = {b0, b1, b2, x, x, x, x, x}
         * a0Coeffs = { x, a1, a2, x, x, x, x, x}
         */
        b0Coeffs = vld1q(pCurCoeffs);   pCurCoeffs += 2;
        a0Coeffs = vld1q(pCurCoeffs);   pCurCoeffs += 3;
        /*
         * Reading the state values
         * state = {d1, d2, 0, 0, x, x, x, x}
         */
        state = *(f16x8_t *) pState;
        state = vsetq_lane((float16_t)0.0, state, 2);
        state = vsetq_lane((float16_t)0.0, state, 3);

        /* b1Coeffs = {0, b0, b1, b2, x, x, x, x} */
        /* b1Coeffs = { x, x, a1, a2, x, x, x, x} */
        b1Coeffs = (f16x8_t)vshlcq_s16((int16x8_t)b0Coeffs, &tmp, 16);
        a1Coeffs = (f16x8_t)vshlcq_s16((int16x8_t)a0Coeffs, &tmp, 16);

        sample = blockSize / 2;

        /* unrolled 2 x */
        while (sample > 0U)
        {
            /*
             * Read 2 inputs
             */
            Xn0 = *pIn++;
            Xn1 = *pIn++;

            /*
             * 1st half:
             * / acc1 \   / b0 \         / d1 \   / 0  \
             * |  d1  |   | b1 |         | d2 |   | a1 |
             * |  d2  |   | b2 |         | 0  |   | a2 |
             * |  x   | = | x  | * Xn1 + | x  | + | x  | x acc1
             *   ...       ...            ...      ...
             * \  x   /   \ x  /         \ x  /   \ x  /
             */

            state = vfmaq(state, b0Coeffs, Xn0);
            acc0 = vgetq_lane(state, 0);
            state = vfmaq(state, a0Coeffs, acc0);
            state = vsetq_lane((float16_t)0.0, state, 3);

            /*
             * 2nd half:
             * same as 1st half, but all vector elements shifted down.
             * /  x   \   / x  \         / x  \   / x  \
             * | acc1 |   | b0 |         | d1 |   | 0  |
             * |  d1  |   | b1 |         | d2 |   | a1 |
             * |  d2  |   | b2 |         | 0  |   | a2 |
             * |  x   | = | x  | * Xn1 + | x  | + | x  | x acc1
             *   ...       ...            ...      ...
             * \  x   /   \ x  /         \ x  /   \ x  /
             */

            state = vfmaq(state, b1Coeffs, Xn1);
            acc1 = vgetq_lane(state, 1);
            state = vfmaq(state, a1Coeffs, acc1);

            /* move d1, d2 up + clearing */
            /* expect dual move or long move */
            state = vsetq_lane(vgetq_lane(state, 2), state, 0);
            state = vsetq_lane(vgetq_lane(state, 3), state, 1);
            state = vsetq_lane((float16_t)0.0, state, 2);
            /*
             * Store the results in the destination buffer.
             */
            *pOut++ = acc0;
            *pOut++ = acc1;
            /*
             * decrement the loop counter
             */
            sample--;
        }

        /* compiler does not come back when enabled */
        /*
         * tail handling
         */
        if (blockSize & 1)
        {
            Xn0 = *pIn++;
            state = vfmaq_n_f16(state, b0Coeffs, Xn0);
            acc0 = vgetq_lane(state, 0);

            state = vfmaq_n_f16(state, a0Coeffs, acc0);
            *pOut++ = acc0;
            *pState++ = vgetq_lane(state, 1);
            *pState++ = vgetq_lane(state, 2);
        }
        else
        {
            *pState++ = vgetq_lane(state, 0);
            *pState++ = vgetq_lane(state, 1);
        }
        /*
         * The current stage input is given as the output to the next stage
         */
        pIn = pDst;
        /*
         * Reset the output working pointer
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

void arm_biquad_cascade_df2T_f16(
  const arm_biquad_cascade_df2T_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
  const float16_t *pIn = pSrc;                         /* Source pointer */
        float16_t *pOut = pDst;                        /* Destination pointer */
        float16_t *pState = S->pState;                 /* State pointer */
  const float16_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        _Float16 acc1;                                /* Accumulator */
        _Float16 b0, b1, b2, a1, a2;                  /* Filter coefficients */
        _Float16 Xn1;                                 /* Temporary input */
        _Float16 d1, d2;                              /* State variables */
        uint32_t sample, stage = S->numStages;         /* Loop counters */

  do
  {
     /* Reading the coefficients */
     b0 = pCoeffs[0];
     b1 = pCoeffs[1];
     b2 = pCoeffs[2];
     a1 = pCoeffs[3];
     a2 = pCoeffs[4];

     /* Reading the state values */
     d1 = pState[0];
     d2 = pState[1];

     pCoeffs += 5U;

#if defined (ARM_MATH_LOOPUNROLL)

     /* Loop unrolling: Compute 16 outputs at a time */
     sample = blockSize >> 4U;

     while (sample > 0U) {

       /* y[n] = b0 * x[n] + d1 */
       /* d1 = b1 * x[n] + a1 * y[n] + d2 */
       /* d2 = b2 * x[n] + a2 * y[n] */

/*  1 */
       Xn1 = *pIn++;

       acc1 = b0 * Xn1 + d1;

       d1 = b1 * Xn1 + d2;
       d1 += a1 * acc1;

       d2 = b2 * Xn1;
       d2 += a2 * acc1;

       *pOut++ = acc1;

/*  2 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  3 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  4 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  5 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  6 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  7 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  8 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/*  9 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 10 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 11 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 12 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 13 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 14 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 15 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

/* 16 */
         Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

        /* decrement loop counter */
        sample--;
      }

      /* Loop unrolling: Compute remaining outputs */
      sample = blockSize & 0xFU;

#else

      /* Initialize blkCnt with number of samples */
      sample = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

      while (sample > 0U) {
        Xn1 = *pIn++;

        acc1 = b0 * Xn1 + d1;

        d1 = b1 * Xn1 + d2;
        d1 += a1 * acc1;

        d2 = b2 * Xn1;
        d2 += a2 * acc1;

        *pOut++ = acc1;

        /* decrement loop counter */
        sample--;
      }

      /* Store the updated state variables back into the state array */
      pState[0] = d1;
      pState[1] = d2;

      pState += 2U;

      /* The current stage output is given as the input to the next stage */
      pIn = pDst;

      /* Reset the output working pointer */
      pOut = pDst;

      /* decrement loop counter */
      stage--;

   } while (stage > 0U);

}
#endif /* #if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of BiquadCascadeDF2T group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
