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
  @defgroup Entropy Entropy

  Computes the entropy of a distribution

 */

/**
 * @addtogroup Entropy
 * @{
 */


/**
 * @brief Entropy
 *
 * @param[in]  pSrcA        Array of input values.
 * @param[in]  blockSize    Number of samples in the input array.
 * @return     Entropy      -Sum(p ln p)
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

float16_t arm_entropy_f16(const float16_t * pSrcA,uint32_t blockSize)
{
    uint32_t        blkCnt;
    _Float16       accum=0.0f16,p;


    blkCnt = blockSize;

    f16x8_t         vSum = vdupq_n_f16(0.0f);
    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 3U;

    while (blkCnt > 0U)
    {
        f16x8_t         vecIn = vld1q(pSrcA);

        vSum = vaddq_f16(vSum, vmulq(vecIn, vlogq_f16(vecIn)));

        /*
         * Decrement the blockSize loop counter
         * Advance vector source and destination pointers
         */
        pSrcA += 8;
        blkCnt --;
    }

    accum = vecAddAcrossF16Mve(vSum);

    /* Tail */
    blkCnt = blockSize & 0x7;
    while(blkCnt > 0)
    {
       p = *pSrcA++;
       accum += p * logf(p);

       blkCnt--;

    }

    return (-accum);
}

#else

float16_t arm_entropy_f16(const float16_t * pSrcA,uint32_t blockSize)
{
    const float16_t *pIn;
    uint32_t blkCnt;
    _Float16 accum, p;

    pIn = pSrcA;
    blkCnt = blockSize;

    accum = 0.0f;

    while(blkCnt > 0)
    {
       p = *pIn++;
       accum += p * logf(p);

       blkCnt--;

    }

    return(-accum);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of Entropy group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

