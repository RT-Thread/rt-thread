
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_canberra_distance_f16.c
 * Description:  Canberra distance between two vectors
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
  @defgroup Canberra Canberra distance

  Canberra distance
 */


/**
  @addtogroup Canberra
  @{
 */


/**
 * @brief        Canberra distance between two vectors
 *
 * This function may divide by zero when samples pA[i] and pB[i] are both zero.
 * The result of the computation will be correct. So the division per zero may be
 * ignored.
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

float16_t arm_canberra_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
    _Float16       accum = 0.0f16;
    uint32_t         blkCnt;
    f16x8_t         a, b, c, accumV;

    accumV = vdupq_n_f16(0.0f);

    blkCnt = blockSize >> 3;
    while (blkCnt > 0) {
        a = vld1q(pA);
        b = vld1q(pB);

        c = vabdq(a, b);

        a = vabsq(a);
        b = vabsq(b);
        a = vaddq(a, b);

        /*
         * May divide by zero when a and b have both the same lane at zero.
         */
        a = vrecip_hiprec_f16(a);

        /*
         * Force result of a division by 0 to 0. It the behavior of the
         * sklearn canberra function.
         */
        a = vdupq_m_n_f16(a, 0.0f, vcmpeqq(a, 0.0f));
        c = vmulq(c, a);
        accumV = vaddq(accumV, c);

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

        a = vabsq(a);
        b = vabsq(b);
        a = vaddq(a, b);

        /*
         * May divide by zero when a and b have both the same lane at zero.
         */
        a = vrecip_hiprec_f16(a);

        /*
         * Force result of a division by 0 to 0. It the behavior of the
         * sklearn canberra function.
         */
        a = vdupq_m_n_f16(a, 0.0f, vcmpeqq(a, 0.0f));
        c = vmulq(c, a);
        accumV = vaddq_m(accumV, accumV, c, p0);
    }

    accum = vecAddAcrossF16Mve(accumV);

    return (accum);
}


#else
float16_t arm_canberra_distance_f16(const float16_t *pA,const float16_t *pB, uint32_t blockSize)
{
   _Float16 accum=0.0f, tmpA, tmpB,diff,sum;

   while(blockSize > 0)
   {
      tmpA = *pA++;
      tmpB = *pB++;

      diff = fabsf(tmpA - tmpB);
      sum = fabsf(tmpA) + fabsf(tmpB);
      if ((tmpA != 0.0f16) || (tmpB != 0.0f16))
      {
         accum += (diff / sum);
      }
      blockSize --;
   }
   return(accum);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */


/**
 * @} end of Canberra group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

