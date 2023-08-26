/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_absmax_no_idx_f16.c
 * Description:  Maximum value of a absolute values of a floating-point vector
 *
 * $Date:        16 November 2021
 * $Revision:    V1.10.0
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

#if (defined(ARM_MATH_NEON) || defined(ARM_MATH_MVEF)) && !defined(ARM_MATH_AUTOVECTORIZE)
#include <limits.h>
#endif

/**
  @ingroup groupStats
 */


/**
  @addtogroup AbsMax
  @{
 */

/**
  @brief         Maximum value of absolute values of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    maximum value returned here
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
void arm_absmax_no_idx_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
   uint16_t  blkCnt;           /* loop counters */
    f16x8_t vecSrc;
    float16_t const *pSrcVec;
    f16x8_t curExtremValVec = vdupq_n_f16(F16_ABSMIN);
    float16_t maxValue = F16_ABSMIN;
    mve_pred16_t p0;


    pSrcVec = (float16_t const *) pSrc;
    blkCnt = blockSize >> 3;
    while (blkCnt > 0)
    {
        vecSrc = vldrhq_f16(pSrcVec);  
        pSrcVec += 8;
        /*
         * update per-lane max.
         */
        curExtremValVec = vmaxnmaq(vecSrc, curExtremValVec);
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
    if (blkCnt > 0U)
    {
        vecSrc = vldrhq_f16(pSrcVec);  
        pSrcVec += 8;
        p0 = vctp16q(blkCnt);
        /*
         * Get current max per lane and current index per lane
         * when a max is selected
         */
         curExtremValVec = vmaxnmaq_m(curExtremValVec, vecSrc, p0);
    }
    /*
     * Get max value across the vector
     */
    maxValue = vmaxnmavq(maxValue, curExtremValVec);
    *pResult = maxValue;
}
#else
#if defined(ARM_MATH_LOOPUNROLL)
void arm_absmax_no_idx_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
        float16_t cur_absmax, out;                     /* Temporary variables to store the output value. */\
        uint32_t blkCnt;                     /* Loop counter */                                   \
                                                                                                            \
                                                                                           \
  /* Load first input value that act as reference value for comparision */                                  \
  out = *pSrc++;                                                                                            \
  out = ((_Float16)out > 0.0f16) ? out : -(_Float16)out;                                                                             \
                                                                                             \
                                                                                                            \
  /* Loop unrolling: Compute 4 outputs at a time */                                                         \
  blkCnt = (blockSize - 1U) >> 2U;                                                                          \
                                                                                                            \
  while (blkCnt > 0U)                                                                                       \
  {                                                                                                         \
    /* Initialize cur_absmax to next consecutive values one by one */                                         \
    cur_absmax = *pSrc++;                                                                                     \
    cur_absmax = ((_Float16)cur_absmax > 0.0f16) ? cur_absmax : -(_Float16)cur_absmax;                                                                 \
    /* compare for the extrema value */                                                                     \
    if ((_Float16)cur_absmax > (_Float16)out)                                                                         \
    {                                                                                                       \
      /* Update the extrema value and it's index */                                                         \
      out = cur_absmax;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmax = *pSrc++;                                                                                     \
    cur_absmax = ((_Float16)cur_absmax > 0.0f16) ? cur_absmax : -(_Float16)cur_absmax;                                                                 \
    if ((_Float16)cur_absmax > (_Float16)out)                                                                         \
    {                                                                                                       \
      out = cur_absmax;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmax = *pSrc++;                                                                                     \
    cur_absmax = ((_Float16)cur_absmax > 0.0f16) ? cur_absmax : -(_Float16)cur_absmax;                                                                 \
    if ((_Float16)cur_absmax > (_Float16)out)                                                                          \
    {                                                                                                       \
      out = cur_absmax;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmax = *pSrc++;                                                                                     \
    cur_absmax = ((_Float16)cur_absmax > 0.0f16) ? cur_absmax : -(_Float16)cur_absmax;                                                                 \
    if ((_Float16)cur_absmax > (_Float16)out)                                                                          \
    {                                                                                                       \
      out = cur_absmax;                                                                                       \
    }                                                                                                       \
                                                                                                            \
                                                                                                            \
    /* Decrement loop counter */                                                                            \
    blkCnt--;                                                                                               \
  }                                                                                                         \
                                                                                                            \
  /* Loop unrolling: Compute remaining outputs */                                                           \
  blkCnt = (blockSize - 1U) % 4U;                                                                           \
                                                                                                            \
                                                                                                            \
  while (blkCnt > 0U)                                                                                       \
  {                                                                                                         \
    cur_absmax = *pSrc++;                                                                                     \
    cur_absmax = ((_Float16)cur_absmax > 0.0f16) ? cur_absmax : -(_Float16)cur_absmax;                                                                 \
    if ((_Float16)cur_absmax > (_Float16)out)                                                                         \
    {                                                                                                       \
      out = cur_absmax;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    /* Decrement loop counter */                                                                            \
    blkCnt--;                                                                                               \
  }                                                                                                         \
                                                                                                            \
  /* Store the extrema value and it's index into destination pointers */                                    \
  *pResult = out;                                                                                           \
}
#else
void arm_absmax_no_idx_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
        float16_t maxVal, out;                         /* Temporary variables to store the output value. */
        uint32_t blkCnt;                     /* Loop counter */



  /* Load first input value that act as reference value for comparision */
  out = (_Float16)fabsf((float32_t)*pSrc++);

  /* Initialize blkCnt with number of samples */
  blkCnt = (blockSize - 1U);

  while (blkCnt > 0U)
  {
    /* Initialize maxVal to the next consecutive values one by one */
    maxVal = (_Float16)fabsf((float32_t)*pSrc++);

    /* compare for the maximum value */
    if ((_Float16)out < (_Float16)maxVal)
    {
      /* Update the maximum value and it's index */
      out = maxVal;
    }

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store the maximum value and it's index into destination pointers */
  *pResult = out;
}
#endif /* defined(ARM_MATH_LOOPUNROLL) */
#endif /* defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of AbsMax group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

