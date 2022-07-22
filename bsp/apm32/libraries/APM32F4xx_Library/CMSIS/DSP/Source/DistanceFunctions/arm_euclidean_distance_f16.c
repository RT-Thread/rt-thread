
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_euclidean_distance_f16.c
 * Description:  Euclidean distance between two vectors
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

#include "dsp/distance_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

#include <limits.h>
#include <math.h>


/**
  @ingroup FloatDist
 */

/**
  @defgroup Euclidean Euclidean distance

  Euclidean distance
 */


/**
  @addtogroup Euclidean
  @{
 */


/**
 * @brief        Euclidean distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math.h"
float16_t arm_euclidean_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
    uint32_t        blkCnt;
    float16_t       tmp;
    f16x8_t         a, b, accumV, tempV;

    accumV = vdupq_n_f16(0.0f);

    blkCnt = blockSize >> 3;
    while (blkCnt > 0U) {
        a = vld1q(pA);
        b = vld1q(pB);

        tempV = vsubq(a, b);
        accumV = vfmaq(accumV, tempV, tempV);

        pA += 8;
        pB += 8;
        blkCnt--;
    }

    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = blockSize & 7;
    if (blkCnt > 0U) {
        mve_pred16_t    p0 = vctp16q(blkCnt);

        a = vldrhq_z_f16(pA, p0);
        b = vldrhq_z_f16(pB, p0);

        tempV = vsubq(a, b);
        accumV = vfmaq_m(accumV, tempV, tempV, p0);
    }

    arm_sqrt_f16(vecAddAcrossF16Mve(accumV), &tmp);
    return (tmp);
}

#else
float16_t arm_euclidean_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
   _Float16 accum=0.0f,tmp;
   float16_t result;

   while(blockSize > 0)
   {
      tmp = (_Float16)*pA++ - (_Float16)*pB++;
      accum += SQ(tmp);
      blockSize --;
   }
   arm_sqrt_f16(accum,&result);
   return(result);
}

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */


/**
 * @} end of Euclidean group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

