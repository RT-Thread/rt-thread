/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_df1_init_f16.c
 * Description:  Floating-point Biquad cascade DirectFormI(DF1) filter initialization function
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
  @brief         Initialization function for the floating-point Biquad cascade filter.
  @param[in,out] S           points to an instance of the floating-point Biquad cascade structure.
  @param[in]     numStages   number of 2nd order stages in the filter.
  @param[in]     pCoeffs     points to the filter coefficients.
  @param[in]     pState      points to the state buffer.
  @return        none

  @par           Coefficient and State Ordering
                   The coefficients are stored in the array <code>pCoeffs</code> in the following order:
  <pre>
      {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, ...}
  </pre>

  @par
                   where <code>b1x</code> and <code>a1x</code> are the coefficients for the first stage,
                   <code>b2x</code> and <code>a2x</code> are the coefficients for the second stage,
                   and so on. The <code>pCoeffs</code> array contains a total of <code>5*numStages</code> values.
  @par
                   The <code>pState</code> is a pointer to state array.
                   Each Biquad stage has 4 state variables <code>x[n-1], x[n-2], y[n-1],</code> and <code>y[n-2]</code>.
                   The state variables are arranged in the <code>pState</code> array as:
  <pre>
      {x[n-1], x[n-2], y[n-1], y[n-2]}
  </pre>
                   The 4 state variables for stage 1 are first, then the 4 state variables for stage 2, and so on.
                   The state array has a total length of <code>4*numStages</code> values.
                   The state variables are updated after each block of data is processed; the coefficients are untouched.

  @par             For MVE code, an additional buffer of modified coefficients is required.
                   Its size is numStages and each element of this buffer has type arm_biquad_mod_coef_f16.
                   So, its total size is 96*numStages float16_t elements.

                   The initialization function which must be used is arm_biquad_cascade_df1_mve_init_f16.
 */


void arm_biquad_cascade_df1_init_f16(
        arm_biquad_casd_df1_inst_f16 * S,
        uint8_t numStages,
  const float16_t * pCoeffs,
        float16_t * pState)
{
  /* Assign filter stages */
  S->numStages = numStages;

  /* Assign coefficient pointer */
  S->pCoeffs = pCoeffs;

  /* Clear state buffer and size is always 4 * numStages */
  memset(pState, 0, (4U * (uint32_t) numStages) * sizeof(float16_t));

  /* Assign state pointer */
  S->pState = pState;
}

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

static void generateCoefsFastBiquadF16(float16_t b0, float16_t b1, float16_t b2, float16_t a1, float16_t a2,
                                arm_biquad_mod_coef_f16 * newCoef)
{
    float32_t coeffs[8][12] = {
        {0, 0, 0, 0, 0, 0, 0, b0, b1, b2, a1, a2},
        {0, 0, 0, 0, 0, 0, b0, b1, b2, 0, a2, 0},
        {0, 0, 0, 0, 0, b0, b1, b2, 0, 0, 0, 0},
        {0, 0, 0, 0, b0, b1, b2, 0, 0, 0, 0, 0},
        {0, 0, 0, b0, b1, b2, 0, 0, 0, 0, 0, 0},
        {0, 0, b0, b1, b2, 0, 0, 0, 0, 0, 0, 0},
        {0, b0, b1, b2, 0, 0, 0, 0, 0, 0, 0, 0},
        {b0, b1, b2, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < 12; i++)
    {
        coeffs[1][i] += (a1 * coeffs[0][i]);
        coeffs[2][i] += (a1 * coeffs[1][i]) + (a2 * coeffs[0][i]);
        coeffs[3][i] += (a1 * coeffs[2][i]) + (a2 * coeffs[1][i]);
        coeffs[4][i] += (a1 * coeffs[3][i]) + (a2 * coeffs[2][i]);
        coeffs[5][i] += (a1 * coeffs[4][i]) + (a2 * coeffs[3][i]);
        coeffs[6][i] += (a1 * coeffs[5][i]) + (a2 * coeffs[4][i]);
        coeffs[7][i] += (a1 * coeffs[6][i]) + (a2 * coeffs[5][i]);

        /*
         * transpose
         */
        newCoef->coeffs[i][0] = (float16_t) coeffs[0][i];
        newCoef->coeffs[i][1] = (float16_t) coeffs[1][i];
        newCoef->coeffs[i][2] = (float16_t) coeffs[2][i];
        newCoef->coeffs[i][3] = (float16_t) coeffs[3][i];
        newCoef->coeffs[i][4] = (float16_t) coeffs[4][i];
        newCoef->coeffs[i][5] = (float16_t) coeffs[5][i];
        newCoef->coeffs[i][6] = (float16_t) coeffs[6][i];
        newCoef->coeffs[i][7] = (float16_t) coeffs[7][i];

    }
}

void arm_biquad_cascade_df1_mve_init_f16(arm_biquad_casd_df1_inst_f16 * S,
                                         uint8_t numStages,
                                         const float16_t * pCoeffs,
                                         arm_biquad_mod_coef_f16 * pCoeffsMod,
                                         float16_t * pState)
{
    arm_biquad_cascade_df1_init_f16(S, numStages, (float16_t *)pCoeffsMod, pState);

    /* Generate SIMD friendly modified coefs */
    for (int i = 0; i < numStages; i++)
    {
        generateCoefsFastBiquadF16(pCoeffs[0], pCoeffs[1], pCoeffs[2], pCoeffs[3], pCoeffs[4], pCoeffsMod);
        pCoeffs += 5;
        pCoeffsMod++;
    }
}

#endif

/**
  @} end of BiquadCascadeDF1 group
 */
#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
