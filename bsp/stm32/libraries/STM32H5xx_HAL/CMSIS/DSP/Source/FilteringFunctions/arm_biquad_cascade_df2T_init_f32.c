/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_biquad_cascade_df2T_init_f32.c
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

#include "dsp/filtering_functions.h"

/**
  @ingroup groupFilters
 */

/**
  @addtogroup BiquadCascadeDF2T
  @{
 */



#if defined(ARM_MATH_NEON) 
/**
  @brief         Compute new coefficient arrays for use in vectorized filter (Neon only).
  @param[in]     numStages         number of 2nd order stages in the filter.
  @param[in]     pCoeffs           points to the original filter coefficients.
  @param[in]     pComputedCoeffs   points to the new computed coefficients for the vectorized Neon version.
  @return        none

  @par   Size of coefficient arrays:
            pCoeffs has size 5 * numStages 

            pComputedCoeffs has size 8 * numStages

            pComputedCoeffs is the array to be used in arm_biquad_cascade_df2T_init_f32.

*/
void arm_biquad_cascade_df2T_compute_coefs_f32(
  uint8_t numStages,
  const float32_t * pCoeffs,
  float32_t * pComputedCoeffs)
{
   uint8_t cnt;
   float32_t b0[4],b1[4],b2[4],a1[4],a2[4];

   cnt = numStages >> 2; 
   while(cnt > 0)
   {
      for(int i=0;i<4;i++)
      {
        b0[i] = pCoeffs[0];
        b1[i] = pCoeffs[1];
        b2[i] = pCoeffs[2];
        a1[i] = pCoeffs[3];
        a2[i] = pCoeffs[4];
        pCoeffs += 5;
      }

      /* Vec 1 */
      *pComputedCoeffs++ = 0;
      *pComputedCoeffs++ = b0[1];
      *pComputedCoeffs++ = b0[2];
      *pComputedCoeffs++ = b0[3];

      /* Vec 2 */
      *pComputedCoeffs++ = 0;
      *pComputedCoeffs++ = 0;
      *pComputedCoeffs++ = b0[1] * b0[2];
      *pComputedCoeffs++ = b0[2] * b0[3];

      /* Vec 3 */
      *pComputedCoeffs++ = 0;
      *pComputedCoeffs++ = 0;
      *pComputedCoeffs++ = 0;
      *pComputedCoeffs++ = b0[1] * b0[2] * b0[3];
      
      /* Vec 4 */
      *pComputedCoeffs++ = b0[0];
      *pComputedCoeffs++ = b0[0] * b0[1];
      *pComputedCoeffs++ = b0[0] * b0[1] * b0[2];
      *pComputedCoeffs++ = b0[0] * b0[1] * b0[2] * b0[3];

      /* Vec 5 */
      *pComputedCoeffs++ = b1[0];
      *pComputedCoeffs++ = b1[1];
      *pComputedCoeffs++ = b1[2];
      *pComputedCoeffs++ = b1[3];

      /* Vec 6 */
      *pComputedCoeffs++ = b2[0];
      *pComputedCoeffs++ = b2[1];
      *pComputedCoeffs++ = b2[2];
      *pComputedCoeffs++ = b2[3];

      /* Vec 7 */
      *pComputedCoeffs++ = a1[0];
      *pComputedCoeffs++ = a1[1];
      *pComputedCoeffs++ = a1[2];
      *pComputedCoeffs++ = a1[3];

      /* Vec 8 */
      *pComputedCoeffs++ = a2[0];
      *pComputedCoeffs++ = a2[1];
      *pComputedCoeffs++ = a2[2];
      *pComputedCoeffs++ = a2[3];

      cnt--;
   }

   cnt = numStages & 0x3;
   while(cnt > 0)
   {
      *pComputedCoeffs++ = *pCoeffs++;
      *pComputedCoeffs++ = *pCoeffs++;
      *pComputedCoeffs++ = *pCoeffs++;
      *pComputedCoeffs++ = *pCoeffs++;
      *pComputedCoeffs++ = *pCoeffs++;
      cnt--;
   }

}
#endif 

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
                   arm_biquad_cascade_df2T_compute_coefs_f32 which is taking the
                   standard array coefficient as parameters.

                   But, an array of 8*numstages is a good approximation.

                   Then, the initialization can be done with:
  <pre>
                   arm_biquad_cascade_df2T_compute_coefs_f32(nbCascade,coefs,computedCoefs);
                   arm_biquad_cascade_df2T_init_f32(&SNeon, nbCascade, computedCoefs, stateNeon);
  </pre>

  @par             In this example, computedCoefs is a bigger array of size 8 * numStages.
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
void arm_biquad_cascade_df2T_init_f32(
        arm_biquad_cascade_df2T_instance_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState)
{
  /* Assign filter stages */
  S->numStages = numStages;

  /* Assign coefficient pointer */
  S->pCoeffs = pCoeffs;

  /* Clear state buffer and size is always 2 * numStages */
  memset(pState, 0, (2U * (uint32_t) numStages) * sizeof(float32_t));

  /* Assign state pointer */
  S->pState = pState;
}

/**
  @} end of BiquadCascadeDF2T group
 */
