/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_absmin_no_idx_f16.c
 * Description:  Minimum value of absolute values of a floating-point vector
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
  @addtogroup AbsMin
  @{
 */

/**
  @brief         Minimum value of absolute values of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
void arm_absmin_no_idx_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
   int32_t  blkCnt;           /* loop counters */
    f16x8_t vecSrc;
    float16_t const *pSrcVec;
    f16x8_t curExtremValVec = vdupq_n_f16(F16_ABSMAX);
    float16_t minValue = F16_ABSMAX;
    mve_pred16_t p0;


    pSrcVec = (float16_t const *) pSrc;
    blkCnt = blockSize >> 3;
    while (blkCnt > 0)
    {
        vecSrc = vld1q(pSrcVec); 
        pSrcVec += 8;
        /*
         * update per-lane min.
         */
        curExtremValVec = vminnmaq(vecSrc, curExtremValVec);
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
    if (blkCnt > 0)
    {
        vecSrc = vld1q(pSrcVec); 
        pSrcVec += 8;
        p0 = vctp16q(blkCnt);
        /*
         * Get current min per lane and current index per lane
         * when a min is selected
         */
         curExtremValVec = vminnmaq_m(curExtremValVec, vecSrc, p0);
    }
    /*
     * Get min value across the vector
     */
    minValue = vminnmavq(minValue, curExtremValVec);
    *pResult = minValue;
}

#else
#if defined(ARM_MATH_LOOPUNROLL)
void arm_absmin_no_idx_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
        float16_t cur_absmin, out;                     /* Temporary variables to store the output value. */\
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
    /* Initialize cur_absmin to next consecutive values one by one */                                         \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = ((_Float16)cur_absmin > 0.0f16) ? cur_absmin : -(_Float16)cur_absmin;                                                                 \
    /* compare for the extrema value */                                                                     \
    if ((_Float16)cur_absmin < (_Float16)out)                                                                         \
    {                                                                                                       \
      /* Update the extrema value and it's index */                                                         \
      out = cur_absmin;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = ((_Float16)cur_absmin > 0.0f16) ? cur_absmin : -(_Float16)cur_absmin;                                                                 \
    if ((_Float16)cur_absmin < (_Float16)out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = ((_Float16)cur_absmin > 0.0f16) ? cur_absmin : -(_Float16)cur_absmin;                                                                 \
    if ((_Float16)cur_absmin < (_Float16)out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = ((_Float16)cur_absmin > 0.0f16) ? cur_absmin : -(_Float16)cur_absmin;                                                                 \
    if ((_Float16)cur_absmin < (_Float16)out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
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
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = ((_Float16)cur_absmin > 0.0f16) ? cur_absmin : -(_Float16)cur_absmin;                                                                 \
    if ((_Float16)cur_absmin < (_Float16)out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
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
void arm_absmin_no_idx_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult)
{
        float16_t minVal, out;                         /* Temporary variables to store the output value. */
        uint32_t blkCnt;                     /* Loop counter */



  /* Load first input value that act as reference value for comparision */
  out = (_Float16)fabsf((float32_t)*pSrc++);

  /* Initialize blkCnt with number of samples */
  blkCnt = (blockSize - 1U);

  while (blkCnt > 0U)
  {
    /* Initialize minVal to the next consecutive values one by one */
    minVal = (_Float16)fabsf((float32_t)*pSrc++);

    /* compare for the minimum value */
    if ((_Float16)out > (_Float16)minVal)
    {
      /* Update the minimum value and it's index */
      out = minVal;
    }

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store the minimum value and it's index into destination pointers */
  *pResult = out;
}
#endif /* defined(ARM_MATH_LOOPUNROLL) */
#endif /* defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of AbsMin group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

