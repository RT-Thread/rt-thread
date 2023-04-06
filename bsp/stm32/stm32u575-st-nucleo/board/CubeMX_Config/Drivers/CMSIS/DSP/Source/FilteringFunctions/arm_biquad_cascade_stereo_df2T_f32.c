/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_stereo_df2T_f32.c
 * Description:  Processing function for floating-point transposed direct form II Biquad cascade filter. 2 channels
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

LOW_OPTIMIZATION_ENTER
void arm_biquad_cascade_stereo_df2T_f32(
  const arm_biquad_cascade_stereo_df2T_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize)
{
  const float32_t *pIn = pSrc;                         /* Source pointer */
        float32_t *pOut = pDst;                        /* Destination pointer */
        float32_t *pState = S->pState;                 /* State pointer */
  const float32_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        float32_t acc1a, acc1b;                        /* Accumulator */
        float32_t b0, b1, b2, a1, a2;                  /* Filter coefficients */
        float32_t Xn1a, Xn1b;                          /* Temporary input */
        float32_t d1a, d2a, d1b, d2b;                  /* State variables */
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
        d1a = pState[0];
        d2a = pState[1];
        d1b = pState[2];
        d2b = pState[3];

        pCoeffs += 5U;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 8 outputs at a time */
        sample = blockSize >> 3U;

        while (sample > 0U) {
          /* y[n] = b0 * x[n] + d1 */
          /* d1 = b1 * x[n] + a1 * y[n] + d2 */
          /* d2 = b2 * x[n] + a2 * y[n] */

/*  1 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  2 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  3 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  4 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  5 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  6 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  7 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

/*  8 */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          *pOut++ = acc1a;
          *pOut++ = acc1b;

          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

          /* decrement loop counter */
          sample--;
        }

        /* Loop unrolling: Compute remaining outputs */
        sample = blockSize & 0x7U;

#else

        /* Initialize blkCnt with number of samples */
        sample = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

        while (sample > 0U) {
          /* Read the input */
          Xn1a = *pIn++; /* Channel a */
          Xn1b = *pIn++; /* Channel b */

          /* y[n] = b0 * x[n] + d1 */
          acc1a = (b0 * Xn1a) + d1a;
          acc1b = (b0 * Xn1b) + d1b;

          /* Store the result in the accumulator in the destination buffer. */
          *pOut++ = acc1a;
          *pOut++ = acc1b;

          /* Every time after the output is computed state should be updated. */
          /* d1 = b1 * x[n] + a1 * y[n] + d2 */
          d1a = ((b1 * Xn1a) + (a1 * acc1a)) + d2a;
          d1b = ((b1 * Xn1b) + (a1 * acc1b)) + d2b;

          /* d2 = b2 * x[n] + a2 * y[n] */
          d2a = (b2 * Xn1a) + (a2 * acc1a);
          d2b = (b2 * Xn1b) + (a2 * acc1b);

          /* decrement loop counter */
          sample--;
        }

        /* Store the updated state variables back into the state array */
        pState[0] = d1a;
        pState[1] = d2a;

        pState[2] = d1b;
        pState[3] = d2b;

        pState += 4U;

        /* The current stage input is given as the output to the next stage */
        pIn = pDst;

        /* Reset the output working pointer */
        pOut = pDst;

        /* Decrement the loop counter */
        stage--;

    } while (stage > 0U);

}
LOW_OPTIMIZATION_EXIT
/**
  @} end of BiquadCascadeDF2T group
 */
