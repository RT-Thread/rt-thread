
/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_minkowski_distance_f16.c
 * Description:  Minkowski distance between two vectors
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
  @defgroup Minkowski Minkowski distance

  Minkowski distance
 */

/**
  @addtogroup Minkowski
  @{
 */


/**
 * @brief        Minkowski distance between two vectors
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    order      Distance order
 * @param[in]    blockSize  Number of samples
 * @return distance
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

float16_t arm_minkowski_distance_f16(const float16_t *pA,const float16_t *pB, int32_t order, uint32_t blockSize)
{
    uint32_t        blkCnt;
    f16x8_t         a, b, tmpV, sumV;

    sumV = vdupq_n_f16(0.0f);

    blkCnt = blockSize >> 3;
    while (blkCnt > 0U) {
        a = vld1q(pA);
        b = vld1q(pB);

        tmpV = vabdq(a, b);
        tmpV = vpowq_f16(tmpV, vdupq_n_f16(order));
        sumV = vaddq(sumV, tmpV);

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

        tmpV = vabdq(a, b);
        tmpV = vpowq_f16(tmpV, vdupq_n_f16(order));
        sumV = vaddq_m(sumV, sumV, tmpV, p0);
    }

    return (powf(vecAddAcrossF16Mve(sumV), (1.0f / (float16_t) order)));
}


#else


float16_t arm_minkowski_distance_f16(const float16_t *pA,const float16_t *pB, int32_t order, uint32_t blockSize)
{
    _Float16 sum;
    uint32_t i;

    sum = 0.0f;
    for(i=0; i < blockSize; i++)
    {
       sum += (_Float16)powf(fabsf(pA[i] - pB[i]),order);
    }


    return(powf(sum,(1.0f/order)));

}

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */


/**
 * @} end of Minkowski group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

