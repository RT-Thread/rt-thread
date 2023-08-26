/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_logsumexp_f16.c
 * Description:  LogSumExp
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

#include "dsp/statistics_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

#include <limits.h>
#include <math.h>

/**
  @ingroup groupStats
 */

/**
  @defgroup Kullback-Leibler Kullback-Leibler divergence

  Computes the Kullback-Leibler divergence between two distributions

 */


/**
 * @addtogroup Kullback-Leibler
 * @{
 */


/**
 * @brief Kullback-Leibler
 *
 * Distribution A may contain 0 with Neon version.
 * Result will be right but some exception flags will be set.
 *
 * Distribution B must not contain 0 probability.
 *
 * @param[in]  *pSrcA         points to an array of input values for probaility distribution A.
 * @param[in]  *pSrcB         points to an array of input values for probaility distribution B.
 * @param[in]  blockSize      number of samples in the input array.
 * @return Kullback-Leibler divergence D(A || B)
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

float16_t arm_kullback_leibler_f16(const float16_t * pSrcA,const float16_t * pSrcB,uint32_t blockSize)
{
    uint32_t blkCnt;
    _Float16 accum, pA,pB;
 
    
    blkCnt = blockSize;

    accum = 0.0f16;

    f16x8_t         vSum = vdupq_n_f16(0.0f);
    blkCnt = blockSize >> 3;
    while(blkCnt > 0)
    {
        f16x8_t         vecA = vld1q(pSrcA);
        f16x8_t         vecB = vld1q(pSrcB);
        f16x8_t         vRatio;

        vRatio = vdiv_f16(vecB, vecA);
        vSum = vaddq_f16(vSum, vmulq(vecA, vlogq_f16(vRatio)));

        /*
         * Decrement the blockSize loop counter
         * Advance vector source and destination pointers
         */
        pSrcA += 8;
        pSrcB += 8;
        blkCnt --;
    }

    accum = vecAddAcrossF16Mve(vSum);

    blkCnt = blockSize & 7;
    while(blkCnt > 0)
    {
       pA = *pSrcA++;
       pB = *pSrcB++;
       accum += pA * logf(pB / pA);
       
       blkCnt--;
    
    }

    return(-accum);
}

#else
float16_t arm_kullback_leibler_f16(const float16_t * pSrcA,const float16_t * pSrcB,uint32_t blockSize)
{
    const float16_t *pInA, *pInB;
    uint32_t blkCnt;
    _Float16 accum, pA,pB;
 
    pInA = pSrcA;
    pInB = pSrcB;
    blkCnt = blockSize;

    accum = 0.0f;

    while(blkCnt > 0)
    {
       pA = *pInA++;
       pB = *pInB++;
       accum += pA * logf(pB / pA);
       
       blkCnt--;
    
    }

    return(-accum);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of Kullback-Leibler group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

