/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_weighted_sum_f16.c
 * Description:  Weighted Sum
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

#include <limits.h>
#include <math.h>

#include "dsp/support_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

/**
  @ingroup groupSupport
 */

/**
  @defgroup weightedsum Weighted Sum

  Weighted sum of values
 */


/**
 * @addtogroup weightedsum
 * @{
 */


/**
 * @brief Weighted sum
 *
 *
 * @param[in]    *in           Array of input values.
 * @param[in]    *weigths      Weights
 * @param[in]    blockSize     Number of samples in the input array.
 * @return       Weighted sum
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

float16_t arm_weighted_sum_f16(const float16_t *in,const float16_t *weigths, uint32_t blockSize)
{
    _Float16       accum1, accum2;
    float16x8_t    accum1V, accum2V;
    float16x8_t    inV, wV;
    const float16_t *pIn, *pW;
    uint32_t        blkCnt;


    pIn = in;
    pW = weigths;


    accum1V = vdupq_n_f16(0.0f16);
    accum2V = vdupq_n_f16(0.0f16);

    blkCnt = blockSize >> 3;
    while (blkCnt > 0) 
    {
        inV = vld1q(pIn);
        wV = vld1q(pW);

        pIn += 4;
        pW += 4;

        accum1V = vfmaq(accum1V, inV, wV);
        accum2V = vaddq(accum2V, wV);
        blkCnt--;
    }

    accum1 = vecAddAcrossF16Mve(accum1V);
    accum2 = vecAddAcrossF16Mve(accum2V);

    blkCnt = blockSize & 7;
    while(blkCnt > 0)
    {
        accum1 += (_Float16)*pIn++ * (_Float16)*pW;
        accum2 += (_Float16)*pW++;
        blkCnt--;
    }


    return (accum1 / accum2);
}

#else

float16_t arm_weighted_sum_f16(const float16_t *in, const float16_t *weigths, uint32_t blockSize)
{

    _Float16 accum1, accum2;
    const float16_t *pIn, *pW;
    uint32_t blkCnt;


    pIn = in;
    pW = weigths;

    accum1=0.0f16;
    accum2=0.0f16;

    blkCnt = blockSize;
    while(blkCnt > 0)
    {
        accum1 += (_Float16)*pIn++ * (_Float16)*pW;
        accum2 += (_Float16)*pW++;
        blkCnt--;
    }

    return(accum1 / accum2);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of weightedsum group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

