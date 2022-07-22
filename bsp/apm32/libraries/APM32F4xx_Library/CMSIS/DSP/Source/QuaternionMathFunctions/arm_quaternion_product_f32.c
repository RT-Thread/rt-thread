/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_quaternion_product_f32.c
 * Description:  Floating-point quaternion product
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
  @defgroup QuatProd Quaternion Product

  Compute the product of quaternions.
 */

/**
  @ingroup QuatProd
 */

/**
  @defgroup QuatProdVect Elementwise Quaternion Product

  Compute the elementwise product of quaternions.
 */

/**
  @addtogroup QuatProdVect
  @{
 */

/**
  @brief         Floating-point elementwise product two quaternions.
  @param[in]     qa                  first array of quaternions
  @param[in]     qb                  second array of quaternions
  @param[out]    qr                   elementwise product of quaternions
  @param[in]     nbQuaternions       number of quaternions in the array
  @return        none
 */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_quaternion_product_f32(const float32_t *qa,
    const float32_t *qb,
    float32_t *qr,
    uint32_t nbQuaternions)
{
    static uint32_t patternA[4] = { 0, 1, 0, 1 };
    static uint32_t patternB[4] = { 3, 2, 3, 2 };
    static uint32_t patternC[4] = { 3, 2, 1, 0 };
    static float32_t   signA[4] = { -1, -1, 1, 1 };

    uint32x4_t vecA = vld1q_u32(patternA);
    uint32x4_t vecB = vld1q_u32(patternB);
    uint32x4_t vecC = vld1q_u32(patternC);
    f32x4_t vecSignA = vld1q_f32(signA);

    while (nbQuaternions > 0U)
    {
        f32x4_t vecTmpA, vecTmpB, vecAcc;

        vecTmpA = vldrwq_gather_shifted_offset_f32(qa, vecA);
        vecTmpB = vld1q(qb);
        /*
         * vcmul(r, [a1, a2, a1, a2], [b1, b2, b3, b4], 0)
         */
        vecAcc = vcmulq(vecTmpA, vecTmpB);
        /*
         * vcmla(r, [a1, a2, a1, a2], [b1, b2, b3, b4], 90)
         */
        vecAcc = vcmlaq_rot90(vecAcc, vecTmpA, vecTmpB);

        vecTmpA = vldrwq_gather_shifted_offset_f32(qa, vecB);
        vecTmpB = vldrwq_gather_shifted_offset_f32(qb, vecC);
        /*
         * build [-b4, -b3, b2, b1]
         */
        vecTmpB = vecTmpB * vecSignA;
        /*
         * vcmla(r, [a4, a3, a4, a3], [-b4, -b3, b2, b1], 270)
         */
        vecAcc = vcmlaq_rot270(vecAcc, vecTmpA, vecTmpB);
        /*
         * vcmla(r, [a4, a3, a4, a3], [-b4, -b3, b2, b1], 0)
         */
        vecAcc = vcmlaq(vecAcc, vecTmpA, vecTmpB);
        /*
         * store accumulator
         */
        vst1q_f32(qr, vecAcc);

        /* move to next quaternion */
        qa += 4;
        qb += 4;
        qr += 4;

        nbQuaternions--;
    }
}

#else

void arm_quaternion_product_f32(const float32_t *qa,
    const float32_t *qb,
    float32_t *qr,
    uint32_t nbQuaternions)
{
   for(uint32_t i=0; i < nbQuaternions; i++)
   {
     arm_quaternion_product_single_f32(qa, qb, qr);

     qa += 4;
     qb += 4;
     qr += 4;
   }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of QuatProdVect group
 */
