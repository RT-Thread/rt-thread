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
 * @addtogroup LogSumExp
 * @{
 */


/**
 * @brief Computation of the LogSumExp
 *
 * In probabilistic computations, the dynamic of the probability values can be very
 * wide because they come from gaussian functions.
 * To avoid underflow and overflow issues, the values are represented by their log.
 * In this representation, multiplying the original exp values is easy : their logs are added.
 * But adding the original exp values is requiring some special handling and it is the
 * goal of the LogSumExp function.
 *
 * If the values are x1...xn, the function is computing:
 *
 * ln(exp(x1) + ... + exp(xn)) and the computation is done in such a way that
 * rounding issues are minimised.
 *
 * The max xm of the values is extracted and the function is computing:
 * xm + ln(exp(x1 - xm) + ... + exp(xn - xm))
 *
 * @param[in]  *in         Pointer to an array of input values.
 * @param[in]  blockSize   Number of samples in the input array.
 * @return LogSumExp
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

float16_t arm_logsumexp_f16(const float16_t *in, uint32_t blockSize)
{
    float16_t       maxVal;
    const float16_t *pIn;
    int32_t         blkCnt;
    _Float16       accum=0.0f16;
    _Float16       tmp;


    arm_max_no_idx_f16((float16_t *) in, blockSize, &maxVal);


    blkCnt = blockSize;
    pIn = in;


    f16x8_t         vSum = vdupq_n_f16(0.0f16);
    blkCnt = blockSize >> 3;
    while(blkCnt > 0)
    {
        f16x8_t         vecIn = vld1q(pIn);
        f16x8_t         vecExp;

        vecExp = vexpq_f16(vsubq_n_f16(vecIn, maxVal));

        vSum = vaddq_f16(vSum, vecExp);

        /*
         * Decrement the blockSize loop counter
         * Advance vector source and destination pointers
         */
        pIn += 8;
        blkCnt --;
    }

    /* sum + log */
    accum = vecAddAcrossF16Mve(vSum);

    blkCnt = blockSize & 0x7;
    while(blkCnt > 0)
    {
       tmp = *pIn++;
       accum += expf(tmp - maxVal);
       blkCnt--;

    }

    accum = maxVal + logf(accum);

    return (accum);
}

#else
float16_t arm_logsumexp_f16(const float16_t *in, uint32_t blockSize)
{
    _Float16 maxVal;
    _Float16 tmp;
    const float16_t *pIn;
    uint32_t blkCnt;
    _Float16 accum;

    pIn = in;
    blkCnt = blockSize;

    maxVal = *pIn++;
    blkCnt--;

    while(blkCnt > 0)
    {
       tmp = *pIn++;

       if (tmp > maxVal)
       {
          maxVal = tmp;
       }
       blkCnt--;

    }

    blkCnt = blockSize;
    pIn = in;
    accum = 0;
    while(blkCnt > 0)
    {
       tmp = *pIn++;
       accum += expf(tmp - maxVal);
       blkCnt--;

    }
    accum = maxVal + logf(accum);

    return(accum);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of LogSumExp group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

