/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_quaternion_conjugate_f32.c
 * Description:  Floating-point quaternion conjugate
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

#include "dsp/quaternion_math_functions.h"
#include <math.h>

/**
  @ingroup groupQuaternionMath
 */

/**
  @defgroup QuatConjugate Quaternion Conjugate

  Compute the conjugate of a quaternion.
 */

/**
  @addtogroup QuatConjugate
  @{
 */

/**
  @brief         Floating-point quaternion conjugates.
  @param[in]     pInputQuaternions            points to the input vector of quaternions
  @param[out]    pConjugateQuaternions        points to the output vector of conjugate quaternions
  @param[in]     nbQuaternions                number of quaternions in each vector
  @return        none
 */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
void arm_quaternion_conjugate_f32(const float32_t *pInputQuaternions, 
    float32_t *pConjugateQuaternions, 
    uint32_t nbQuaternions)
{
   f32x4_t vec1;

   for(uint32_t i=0; i < nbQuaternions; i++)
   {
      vec1 = vld1q(pInputQuaternions);
      

      vec1 = vsetq_lane_f32(-vgetq_lane(vec1, 0),vec1,0);
      vec1 = vnegq_f32(vec1);

      vst1q(pConjugateQuaternions, vec1);


      pInputQuaternions   += 4;
      pConjugateQuaternions += 4;
   }
}
#else
void arm_quaternion_conjugate_f32(const float32_t *pInputQuaternions, 
    float32_t *pConjugateQuaternions, 
    uint32_t nbQuaternions)
{
   uint32_t i;
   for(i=0; i < nbQuaternions; i++)
   {

      pConjugateQuaternions[4 * i + 0] = pInputQuaternions[4 * i + 0];
      pConjugateQuaternions[4 * i + 1] = -pInputQuaternions[4 * i + 1];
      pConjugateQuaternions[4 * i + 2] = -pInputQuaternions[4 * i + 2];
      pConjugateQuaternions[4 * i + 3] = -pInputQuaternions[4 * i + 3];
   }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of QuatConjugate group
 */
