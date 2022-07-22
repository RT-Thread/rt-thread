
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_chebyshev_distance_f16.c
 * Description:  Chebyshev distance between two vectors
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
  @defgroup Chebyshev Chebyshev distance

  Chebyshev distance
 */

/**
  @addtogroup Chebyshev
  @{
 */


/**
 * @brief        Chebyshev distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math.h"

float16_t arm_chebyshev_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
    uint32_t        blkCnt;     /* loop counters */
    f16x8_t         vecA, vecB;
    f16x8_t         vecDiff = vdupq_n_f16(0.0);
    float16_t       maxValue = 0.0f16;


    blkCnt = blockSize >> 3;
    while (blkCnt > 0U) {
        vecA = vld1q(pA);
        pA += 8;
        vecB = vld1q(pB);
        pB += 8;
        /*
         * update per-lane max.
         */
        vecDiff = vmaxnmaq(vsubq(vecA, vecB), vecDiff);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = blockSize & 7;
    if (blkCnt > 0U) {
        mve_pred16_t    p0 = vctp16q(blkCnt);

        vecA = vldrhq_z_f16(pA, p0);
        vecB = vldrhq_z_f16(pB, p0);

        /*
         * Get current max per lane and current index per lane
         * when a max is selected
         */
        vecDiff = vmaxnmaq_m(vecDiff, vsubq(vecA, vecB), p0);
    }
    /*
     * Get max value across the vector
     */
    return vmaxnmavq(maxValue, vecDiff);
}

#else
float16_t arm_chebyshev_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
   _Float16 diff=0.0f,  maxVal,tmpA, tmpB;

   tmpA = *pA++;
   tmpB = *pB++;
   diff = fabsf(tmpA - tmpB);
   maxVal = diff;
   blockSize--;

   while(blockSize > 0)
   {
      tmpA = *pA++;
      tmpB = *pB++;
      diff = fabsf(tmpA - tmpB);
      if (diff > maxVal)
      {
        maxVal = diff;
      }
      blockSize --;
   }

   return(maxVal);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */


/**
 * @} end of Chebyshev group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

