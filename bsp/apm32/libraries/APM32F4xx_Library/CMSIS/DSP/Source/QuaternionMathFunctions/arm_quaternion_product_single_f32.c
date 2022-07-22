/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_quaternion_product_single_f32.c
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
  @ingroup QuatProd
 */

/**
  @defgroup QuatProdSingle Quaternion Product

  Compute the  product of two quaternions.
 */

/**
  @addtogroup QuatProdSingle
  @{
 */

/**
  @brief         Floating-point product of two quaternions.
  @param[in]     qa       first quaternion
  @param[in]     qb       second quaternion
  @param[out]    qr       product of two quaternions
  @return        none
 */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
void arm_quaternion_product_single_f32(const float32_t *qa,
    const float32_t *qb,
    float32_t *qr)
{
    static uint32_t patternA[4] = { 0, 1, 0, 1 };
    static uint32_t patternB[4] = { 3, 2, 3, 2 };
    static uint32_t patternC[4] = { 3, 2, 1, 0 };
    static float32_t signA[4] = { -1, -1, 1, 1 };

    uint32x4_t vecA = vld1q_u32(patternA);
    uint32x4_t vecB = vld1q_u32(patternB);
    uint32x4_t vecC = vld1q_u32(patternC);
    f32x4_t vecSignA = vld1q_f32(signA);


    f32x4_t vecTmpA, vecTmpB, vecAcc;

    vecTmpA = vldrwq_gather_shifted_offset_f32(qa, vecA);
    vecTmpB = vld1q_f32(qb);

    vecAcc = vcmulq_f32(vecTmpA, vecTmpB);
    vecAcc = vcmlaq_rot90_f32(vecAcc, vecTmpA, vecTmpB);

    vecTmpA = vldrwq_gather_shifted_offset_f32(qa, vecB);
    vecTmpB = vldrwq_gather_shifted_offset_f32(qb, vecC);

    vecTmpB = vecTmpB * vecSignA;

    vecAcc = vcmlaq_rot270_f32(vecAcc, vecTmpA, vecTmpB);
    vecAcc = vcmlaq_f32(vecAcc, vecTmpA, vecTmpB);

    vst1q_f32(qr, vecAcc);
}

#else
void arm_quaternion_product_single_f32(const float32_t *qa,
    const float32_t *qb,
    float32_t *qr)
{
    qr[0] = qa[0] * qb[0] - qa[1] * qb[1] - qa[2] * qb[2] - qa[3] * qb[3];
    qr[1] = qa[0] * qb[1] + qa[1] * qb[0] + qa[2] * qb[3] - qa[3] * qb[2];
    qr[2] = qa[0] * qb[2] + qa[2] * qb[0] + qa[3] * qb[1] - qa[1] * qb[3];
    qr[3] = qa[0] * qb[3] + qa[3] * qb[0] + qa[1] * qb[2] - qa[2] * qb[1];
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of QuatProdSingle group
 */
