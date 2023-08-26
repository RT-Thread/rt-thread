
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_braycurtis_distance_f16.c
 * Description:  Bray-Curtis distance between two vectors
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
 * @ingroup groupDistance
 */

/**
 * @defgroup FloatDist Float Distances
 *
 * Distances between two vectors of float values.
 */

/**
  @ingroup FloatDist
 */

/**
  @defgroup braycurtis Bray-Curtis distance

  Bray-Curtis distance between two vectors
 */

/**
  @addtogroup braycurtis
  @{
 */


/**
 * @brief        Bray-Curtis distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

float16_t arm_braycurtis_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
    _Float16        accumDiff = 0.0f, accumSum = 0.0f;
    uint32_t        blkCnt;
    f16x8_t         a, b, c, accumDiffV, accumSumV;


    accumDiffV = vdupq_n_f16(0.0f);
    accumSumV = vdupq_n_f16(0.0f);

    blkCnt = blockSize >> 3;
    while (blkCnt > 0) {
        a = vld1q(pA);
        b = vld1q(pB);

        c = vabdq(a, b);
        accumDiffV = vaddq(accumDiffV, c);

        c = vaddq_f16(a, b);
        c = vabsq_f16(c);
        accumSumV = vaddq(accumSumV, c);

        pA += 8;
        pB += 8;
        blkCnt--;
    }

    blkCnt = blockSize & 7;
    if (blkCnt > 0U) {
        mve_pred16_t    p0 = vctp16q(blkCnt);

        a = vldrhq_z_f16(pA, p0);
        b = vldrhq_z_f16(pB, p0);

        c = vabdq(a, b);
        accumDiffV = vaddq_m(accumDiffV, accumDiffV, c, p0);

        c = vaddq_f16(a, b);
        c = vabsq_f16(c);
        accumSumV = vaddq_m(accumSumV, accumSumV, c, p0);
    }

    accumDiff = vecAddAcrossF16Mve(accumDiffV);
    accumSum = vecAddAcrossF16Mve(accumSumV);

    /*
       It is assumed that accumSum is not zero. Since it is the sum of several absolute
       values it would imply that all of them are zero. It is very unlikely for long vectors.
     */
    return (accumDiff / accumSum);
}
#else

float16_t arm_braycurtis_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
   _Float16 accumDiff=0.0f16, accumSum=0.0f16, tmpA, tmpB;

   while(blockSize > 0)
   {
      tmpA = *pA++;
      tmpB = *pB++;
      accumDiff += (_Float16)fabsf((float32_t)((_Float16)tmpA - (_Float16)tmpB));
      accumSum += (_Float16)fabsf((float32_t)((_Float16)tmpA + (_Float16)tmpB));
      blockSize --;
   }
   /*

   It is assumed that accumSum is not zero. Since it is the sum of several absolute
   values it would imply that all of them are zero. It is very unlikely for long vectors.

   */
   return(accumDiff / accumSum);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */


/**
 * @} end of braycurtis group
 */



#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

