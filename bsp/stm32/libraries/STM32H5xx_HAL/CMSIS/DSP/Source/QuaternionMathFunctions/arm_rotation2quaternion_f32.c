/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_rotation2quaternion_f32.c
 * Description:  Floating-point rotation to quaternion conversion
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

#define RI(x,y) r[(3*(x) + (y))]


/**
  @ingroup QuatConv
 */

/**
  @defgroup RotQuat Rotation to Quaternion

  Conversions from rotation to quaternion.
 */

/**
  @addtogroup RotQuat
  @{
 */

/**
 * @brief Conversion of a rotation matrix to an equivalent quaternion.
 * @param[in]       pInputRotations points to an array 3x3 rotation matrix (in row order)
 * @param[out]      pOutputQuaternions points to an array quaternions
 * @param[in]       nbQuaternions number of quaternions in the array
 * @return none.
 *
 * q and -q are representing the same rotation. This ambiguity must be taken into
 * account when using the output of this function.
 * 
 */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

#define R00  vgetq_lane(q1,0)
#define R01  vgetq_lane(q1,1)
#define R02  vgetq_lane(q1,2)
#define R10  vgetq_lane(q1,3)
#define R11  vgetq_lane(q2,0)
#define R12  vgetq_lane(q2,1)
#define R20  vgetq_lane(q2,2)
#define R21  vgetq_lane(q2,3)
#define R22  ro22

void arm_rotation2quaternion_f32(const float32_t *pInputRotations, 
    float32_t *pOutputQuaternions,  
    uint32_t nbQuaternions)
{
   float32_t ro22, trace;
   f32x4_t q1,q2, q; 

   float32_t doubler;
   float32_t s;

   q = vdupq_n_f32(0.0f);

   for(uint32_t nb=0; nb < nbQuaternions; nb++)
   {
      q1 = vld1q(pInputRotations);
      pInputRotations += 4;

      q2 = vld1q(pInputRotations);
      pInputRotations += 4;

      ro22 = *pInputRotations++;

      trace = R00 + R11 + R22;


      if (trace > 0)
      {
        (void)arm_sqrt_f32(trace + 1.0f, &doubler) ; // invs=4*qw
        doubler = 2.0f*doubler;
        s = 1.0f / doubler;

        q1 = vmulq_n_f32(q1,s);
        q2 = vmulq_n_f32(q2,s);

        q[0] = 0.25f * doubler;
        q[1] = R21 - R12;
        q[2] = R02 - R20;
        q[3] = R10 - R01;
      }
      else if ((R00 > R11) && (R00 > R22) )
      {
        (void)arm_sqrt_f32(1.0f + R00 - R11 - R22,&doubler); // invs=4*qx
        doubler = 2.0f*doubler;
        s = 1.0f / doubler;

        q1 = vmulq_n_f32(q1,s);
        q2 = vmulq_n_f32(q2,s);

        q[0] = R21 - R12;
        q[1] = 0.25f * doubler;
        q[2] = R01 + R10;
        q[3] = R02 + R20;
      }
      else if (R11 > R22)
      {
        (void)arm_sqrt_f32(1.0f + R11 - R00 - R22,&doubler); // invs=4*qy
        doubler = 2.0f*doubler;
        s = 1.0f / doubler;

        q1 = vmulq_n_f32(q1,s);
        q2 = vmulq_n_f32(q2,s);

        q[0] = R02 - R20;
        q[1] = R01 + R10;
        q[2] = 0.25f * doubler;
        q[3] = R12 + R21;
      }
      else
      {
        (void)arm_sqrt_f32(1.0f + R22 - R00 - R11,&doubler); // invs=4*qz
        doubler = 2.0f*doubler;
        s = 1.0f / doubler;

        q1 = vmulq_n_f32(q1,s);
        q2 = vmulq_n_f32(q2,s);

        q[0] = R10 - R01;
        q[1] = R02 + R20;
        q[2] = R12 + R21;
        q[3] = 0.25f * doubler;
      }

      vst1q(pOutputQuaternions, q);
      pOutputQuaternions += 4;

   }
}

#else
void arm_rotation2quaternion_f32(const float32_t *pInputRotations, 
    float32_t *pOutputQuaternions,  
    uint32_t nbQuaternions)
{
   uint32_t nb;
   for(nb=0; nb < nbQuaternions; nb++)
   {
       const float32_t *r=&pInputRotations[nb*9];
       float32_t *q=&pOutputQuaternions[nb*4];

       float32_t trace = RI(0,0) + RI(1,1) + RI(2,2);

       float32_t doubler;
       float32_t s;



      if (trace > 0.0f)
      {
        doubler = sqrtf(trace + 1.0f) * 2.0f; // invs=4*qw
        s = 1.0f / doubler;
        q[0] = 0.25f * doubler;
        q[1] = (RI(2,1) - RI(1,2)) * s;
        q[2] = (RI(0,2) - RI(2,0)) * s;
        q[3] = (RI(1,0) - RI(0,1)) * s;
      }
      else if ((RI(0,0) > RI(1,1)) && (RI(0,0) > RI(2,2)) )
      {
        doubler = sqrtf(1.0f + RI(0,0) - RI(1,1) - RI(2,2)) * 2.0f; // invs=4*qx
        s = 1.0f / doubler;
        q[0] = (RI(2,1) - RI(1,2)) * s;
        q[1] = 0.25f * doubler;
        q[2] = (RI(0,1) + RI(1,0)) * s;
        q[3] = (RI(0,2) + RI(2,0)) * s;
      }
      else if (RI(1,1) > RI(2,2))
      {
        doubler = sqrtf(1.0f + RI(1,1) - RI(0,0) - RI(2,2)) * 2.0f; // invs=4*qy
        s = 1.0f / doubler;
        q[0] = (RI(0,2) - RI(2,0)) * s;
        q[1] = (RI(0,1) + RI(1,0)) * s;
        q[2] = 0.25f * doubler;
        q[3] = (RI(1,2) + RI(2,1)) * s;
      }
      else
      {
        doubler = sqrtf(1.0f + RI(2,2) - RI(0,0) - RI(1,1)) * 2.0f; // invs=4*qz
        s = 1.0f / doubler;
        q[0] = (RI(1,0) - RI(0,1)) * s;
        q[1] = (RI(0,2) + RI(2,0)) * s;
        q[2] = (RI(1,2) + RI(2,1)) * s;
        q[3] = 0.25f * doubler;
      }

    }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of RotQuat group
 */
