/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_quaternion2rotation_f32.c
 * Description:  Floating-point quaternion 2 rotation conversion
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
  @defgroup QuatConv Quaternion conversions

  Conversions between quaternion and rotation representations.
 */

/**
  @ingroup QuatConv
 */

/**
  @defgroup QuatRot Quaternion to Rotation

  Conversions from quaternion to rotation.
 */

/**
  @addtogroup QuatRot
  @{
 */

/**
   @brief Conversion of quaternion to equivalent rotation matrix.
   @param[in]       pInputQuaternions points to an array of normalized quaternions
   @param[out]      pOutputRotations points to an array of 3x3 rotations (in row order)
   @param[in]       nbQuaternions number of quaternions in the array
   @return none.

   @par
   Format of rotation matrix


   The quaternion a + ib + jc + kd is converted into rotation matrix:
   <pre>
     a^2 + b^2 - c^2 - d^2                 2bc - 2ad                 2bd + 2ac
                 2bc + 2ad     a^2 - b^2 + c^2 - d^2                 2cd - 2ab
                 2bd - 2ac                 2cd + 2ab     a^2 - b^2 - c^2 + d^2
   </pre>
   Rotation matrix is saved in row order : R00 R01 R02 R10 R11 R12 R20 R21 R22
 */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_quaternion2rotation_f32(const float32_t *pInputQuaternions,
    float32_t *pOutputRotations,
    uint32_t nbQuaternions)
{
  f32x4_t vec0,vec1, vec2 ,vec3;
  float32_t q2q3, tmp1, tmp2 ;

  for(uint32_t nb=0; nb < nbQuaternions; nb++)
  {

    // q0 q1 q2 q3
    vec0 = vld1q(pInputQuaternions);

    // q0^2 q1^2 q2^2 q3^2
    vec1 = vmulq(vec0,vec0);

    // q0^2 q1q0 q2q0 q3q0
    vec2 = vmulq_n_f32(vec0, vgetq_lane(vec0,0));

    // 2 (q0^2 q1q0 q2q0 q3q0)
    vec2 = vmulq_n_f32(vec2, 2.0f);


    // 2 q2q3
    q2q3 = vgetq_lane(vec0,2) * vgetq_lane(vec0,3);
    q2q3 = q2q3 * 2.0f;

    // 2 (q0q1 q1^2 q2q1 q3q1)
    vec3 = vmulq_n_f32(vec0, vgetq_lane(vec0,1));
    vec3 = vmulq_n_f32(vec3, 2.0f);



    vec0 = vsetq_lane(vgetq_lane(vec1,0) + vgetq_lane(vec1,1),vec0,0);
    vec0 = vsetq_lane(vgetq_lane(vec0,0) - vgetq_lane(vec1,2),vec0,0);
    vec0 = vsetq_lane(vgetq_lane(vec0,0) - vgetq_lane(vec1,3),vec0,0);
    vec0 = vsetq_lane(vgetq_lane(vec3,2) - vgetq_lane(vec2,3),vec0,1);
    vec0 = vsetq_lane(vgetq_lane(vec3,3) + vgetq_lane(vec2,2),vec0,2);
    vec0 = vsetq_lane(vgetq_lane(vec3,2) + vgetq_lane(vec2,3),vec0,3);

    vst1q(pOutputRotations, vec0);
    pOutputRotations += 4;

    tmp1 = vgetq_lane(vec1,0) - vgetq_lane(vec1,1);
    tmp2 = vgetq_lane(vec1,2) - vgetq_lane(vec1,3);


    vec0 = vsetq_lane(tmp1 + tmp2,vec0,0);
    vec0 = vsetq_lane(q2q3 - vgetq_lane(vec2,1) ,vec0,1);
    vec0 = vsetq_lane(vgetq_lane(vec3,3) - vgetq_lane(vec2,2),vec0,2);
    vec0 = vsetq_lane(q2q3 + vgetq_lane(vec2,1) ,vec0,3);

    vst1q(pOutputRotations, vec0);
    pOutputRotations += 4;

    *pOutputRotations = tmp1 - tmp2;
    pOutputRotations ++;

    pInputQuaternions += 4;
  }
}

#else
void arm_quaternion2rotation_f32(const float32_t *pInputQuaternions,
    float32_t *pOutputRotations,
    uint32_t nbQuaternions)
{
   for(uint32_t nb=0; nb < nbQuaternions; nb++)
   {
        float32_t q00 = SQ(pInputQuaternions[0 + nb * 4]);
        float32_t q11 = SQ(pInputQuaternions[1 + nb * 4]);
        float32_t q22 = SQ(pInputQuaternions[2 + nb * 4]);
        float32_t q33 = SQ(pInputQuaternions[3 + nb * 4]);
        float32_t q01 =  pInputQuaternions[0 + nb * 4]*pInputQuaternions[1 + nb * 4];
        float32_t q02 =  pInputQuaternions[0 + nb * 4]*pInputQuaternions[2 + nb * 4];
        float32_t q03 =  pInputQuaternions[0 + nb * 4]*pInputQuaternions[3 + nb * 4];
        float32_t q12 =  pInputQuaternions[1 + nb * 4]*pInputQuaternions[2 + nb * 4];
        float32_t q13 =  pInputQuaternions[1 + nb * 4]*pInputQuaternions[3 + nb * 4];
        float32_t q23 =  pInputQuaternions[2 + nb * 4]*pInputQuaternions[3 + nb * 4];

        float32_t xx = q00 + q11 - q22 - q33;
        float32_t yy = q00 - q11 + q22 - q33;
        float32_t zz = q00 - q11 - q22 + q33;
        float32_t xy = 2*(q12 - q03);
        float32_t xz = 2*(q13 + q02);
        float32_t yx = 2*(q12 + q03);
        float32_t yz = 2*(q23 - q01);
        float32_t zx = 2*(q13 - q02);
        float32_t zy = 2*(q23 + q01);

        pOutputRotations[0 + nb * 9] = xx; pOutputRotations[1 + nb * 9] = xy; pOutputRotations[2 + nb * 9] = xz;
        pOutputRotations[3 + nb * 9] = yx; pOutputRotations[4 + nb * 9] = yy; pOutputRotations[5 + nb * 9] = yz;
        pOutputRotations[6 + nb * 9] = zx; pOutputRotations[7 + nb * 9] = zy; pOutputRotations[8 + nb * 9] = zz;
   }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of QuatRot group
 */
