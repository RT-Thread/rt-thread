/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_df2T_init_f16.c
 * Description:  Initialization function for floating-point transposed direct form II Biquad cascade filter
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
  @brief         Initialization function for the floating-point transposed direct form II Biquad cascade filter.
  @param[in,out] S           points to an instance of the filter data structure.
  @param[in]     numStages   number of 2nd order stages in the filter.
  @param[in]     pCoeffs     points to the filter coefficients.
  @param[in]     pState      points to the state buffer.
  @return        none

  @par           Coefficient and State Ordering
                   The coefficients are stored in the array <code>pCoeffs</code> in the following order
                   in the not Neon version.
  <pre>
      {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, ...}
  </pre>

  @par
                   where <code>b1x</code> and <code>a1x</code> are the coefficients for the first stage,
                   <code>b2x</code> and <code>a2x</code> are the coefficients for the second stage,
                   and so on.  The <code>pCoeffs</code> array contains a total of <code>5*numStages</code> values.

                   For Neon version, this array is bigger. If numstages = 4x + y, then the array has size:
                   32*x + 5*y
                   and it must be initialized using the function
                   arm_biquad_cascade_df2T_compute_coefs_f16 which is taking the
                   standard array coefficient as parameters.

                   But, an array of 8*numstages is a good approximation.

                   Then, the initialization can be done with:
  <pre>
                   arm_biquad_cascade_df2T_init_f16(&SNeon, nbCascade, neonCoefs, stateNeon);
                   arm_biquad_cascade_df2T_compute_coefs_f16(&SNeon,nbCascade,coefs);
  </pre>

  @par             In this example, neonCoefs is a bigger array of size 8 * numStages.
                   coefs is the standard array:

  <pre>
      {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, ...}
  </pre>


  @par
                   The <code>pState</code> is a pointer to state array.
                   Each Biquad stage has 2 state variables <code>d1,</code> and <code>d2</code>.
                   The 2 state variables for stage 1 are first, then the 2 state variables for stage 2, and so on.
                   The state array has a total length of <code>2*numStages</code> values.
                   The state variables are updated after each block of data is processed; the coefficients are untouched.
 */

void arm_biquad_cascade_df2T_init_f16(
        arm_biquad_cascade_df2T_instance_f16 * S,
        uint8_t numStages,
  const float16_t * pCoeffs,
        float16_t * pState)
{
  /* Assign filter stages */
  S->numStages = numStages;

  /* Assign coefficient pointer */
  S->pCoeffs = pCoeffs;

  /* Clear state buffer and size is always 2 * numStages */
  memset(pState, 0, (2U * (uint32_t) numStages) * sizeof(float16_t));

  /* Assign state pointer */
  S->pState = pState;
}

/**
  @} end of BiquadCascadeDF2T group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
