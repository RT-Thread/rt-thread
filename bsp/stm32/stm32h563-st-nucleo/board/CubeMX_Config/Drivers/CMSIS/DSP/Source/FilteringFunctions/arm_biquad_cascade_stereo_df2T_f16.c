/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_stereo_df2T_f16.c
 * Description:  Processing function for floating-point transposed direct form II Biquad cascade filter. 2 channels
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

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) && defined(__CMSIS_GCC_H)
#pragma GCC warning "Scalar version of arm_biquad_cascade_stereo_df2T_f16 built. Helium version has build issues with gcc."
#endif 

#if (defined(ARM_MATH_MVE_FLOAT16) && defined(ARM_MATH_HELIUM_EXPERIMENTAL)) && !defined(ARM_MATH_AUTOVECTORIZE) && !defined(__CMSIS_GCC_H)
void arm_biquad_cascade_stereo_df2T_f16(
  const arm_biquad_cascade_stereo_df2T_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
    float16_t *pIn = (float16_t *)pSrc;      /*  source pointer            */
    float16_t *pOut = pDst;     /*  destination pointer       */
    float16_t *pState = S->pState;  /*  State pointer             */
    const float16_t *pCoeffs = S->pCoeffs;    /*  coefficient pointer       */
    float16_t b0, b1, b2, a1, a2;   /*  Filter coefficients       */
    uint32_t  sample, stage = S->numStages; /*  loop counters             */
    static const uint16_t idx2[] = {2, 3, 8, 9, 2, 3, 8, 9};
    f16x8_t aCoeffs, bCoeffs;
    float16_t scratch[16];
    uint16x8_t loadIdxVec;
    uint16x8_t reshufledIdxVec;
    uint16_t  startIdx = 0;
    f16x8_t stateVec0, stateVec1;
    f16x8_t inVec;

    /*
     * {0, 1, 0, 1, 0, 1, 0, 1} generator
     */
    loadIdxVec = viwdupq_u16(startIdx, 2, 1);
    reshufledIdxVec = *(uint16x8_t *)&idx2;

    /*
     * scratch top clearing
     * layout : [d1a d1b d2a d2b d1a d1b d2a d2b 0 0]
     */
    scratch[8] = (float16_t)0.0;
    scratch[9] = (float16_t)0.0;

    do
    {
        /*
         * Reading the coefficients
         */
        b0 = *pCoeffs++;
        b1 = *pCoeffs++;
        b2 = *pCoeffs++;
        a1 = *pCoeffs++;
        a2 = *pCoeffs++;

        /* aCoeffs = {a1 a1 a2 a2 a1 a1 a2 a2} */
        aCoeffs = vdupq_n_f16(a1);
        aCoeffs = vsetq_lane(a2, aCoeffs, 2);
        aCoeffs = vsetq_lane(a2, aCoeffs, 3);
        aCoeffs = vsetq_lane(a2, aCoeffs, 6);
        aCoeffs = vsetq_lane(a2, aCoeffs, 7);

        /* bCoeffs = {b1 b1 b2 b2 b1 b1 b2 b2} */
        bCoeffs = vdupq_n_f16(b1);
        bCoeffs = vsetq_lane(b2, bCoeffs, 2);
        bCoeffs = vsetq_lane(b2, bCoeffs, 3);
        bCoeffs = vsetq_lane(b2, bCoeffs, 6);
        bCoeffs = vsetq_lane(b2, bCoeffs, 7);

        /*
         * Reading the state values
         * Save into scratch
         */
        *(f16x8_t *) scratch = *(f16x8_t *) pState;

        sample = blockSize;

        while (sample > 0U)
        {
            /*
             * step 1
             *
             * 0   | acc1a = xn1a * b0 + d1a
             * 1   | acc1b = xn1b * b0 + d1b
             * 2   | acc1a = xn1a * b0 + d1a
             * 3   | acc1b = xn1b * b0 + d1b
             * 4   |   <repeat>
             * 5   |   ...
             */

            /*
             * load {d1a, d1b, d1a, d1b, d1a, d1b, d1a, d1b}
             */
            stateVec0 = vldrhq_gather_shifted_offset((float16_t const *) scratch, loadIdxVec);
            /*
             * load {in0 in1 in0 in1 in0 in1 in0 in1}
             */
            inVec = vldrhq_gather_shifted_offset_f16(pIn, loadIdxVec);

            stateVec0 = vfmaq(stateVec0, inVec, b0);
            *pOut++ = vgetq_lane(stateVec0, 0);
            *pOut++ = vgetq_lane(stateVec0, 1);

            /*
             * step 2
             *
             * 0  | d1a = b1 * xn1a  +  a1 * acc1a  +  d2a
             * 1  | d1b = b1 * xn1b  +  a1 * acc1b  +  d2b
             * 2  | d2a = b2 * xn1a  +  a2 * acc1a  +  0
             * 3  | d2b = b2 * xn1b  +  a2 * acc1b  +  0
             * 4  |   <repeat>
             * 5  |   ...
             */

            /*
             * load {d2a, d2b, 0, 0, d2a, d2b, 0, 0}
             */
            stateVec1 = vldrhq_gather_shifted_offset((float16_t const *) scratch, reshufledIdxVec);
            stateVec1 = vfmaq(stateVec1, stateVec0, aCoeffs);
            stateVec1 = vfmaq(stateVec1, inVec, bCoeffs);
            *(f16x8_t *) scratch = stateVec1;

            pIn = pIn + 2;
            sample--;
        }

        /*
         * Store the updated state variables back into the state array
         */
         *pState++ = vgetq_lane(stateVec1, 0);
         *pState++ = vgetq_lane(stateVec1, 1);
         *pState++ = vgetq_lane(stateVec1, 2);
         *pState++ = vgetq_lane(stateVec1, 3);

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

void arm_biquad_cascade_stereo_df2T_f16(
  const arm_biquad_cascade_stereo_df2T_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
  const float16_t *pIn = pSrc;                         /* Source pointer */
        float16_t *pOut = pDst;                        /* Destination pointer */
        float16_t *pState = S->pState;                 /* State pointer */
  const float16_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        _Float16 acc1a, acc1b;                        /* Accumulator */
        _Float16 b0, b1, b2, a1, a2;                  /* Filter coefficients */
        _Float16 Xn1a, Xn1b;                          /* Temporary input */
        _Float16 d1a, d2a, d1b, d2b;                  /* State variables */
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

        /* The current stage output is given as the input to the next stage */
        pIn = pDst;

        /* Reset the output working pointer */
        pOut = pDst;

        /* Decrement the loop counter */
        stage--;

    } while (stage > 0U);

}

#endif /* #if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of BiquadCascadeDF2T group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
