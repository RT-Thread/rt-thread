/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_absmin_no_idx_q7.c
 * Description:  Minimum value of absolute values of a Q7 vector
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

#include "dsp/statistics_functions.h"

/**
  @ingroup groupStats
 */


/**
  @addtogroup AbsMin
  @{
 */

/**
  @brief         Minimum value of absolute values of a Q7 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @return        none
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include <stdint.h>
#include "arm_helium_utils.h"



void arm_absmin_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
    int32_t  blkCnt;           /* loop counters */
    q7x16_t        vecSrc;
    q7_t   const *pSrcVec;
    uint8x16_t     curExtremValVec = vdupq_n_s8(Q7_ABSMAX);
    q7_t            minValue = Q7_ABSMAX;
    mve_pred16_t    p0;


    pSrcVec = (q7_t const *) pSrc;
    blkCnt = blockSize >> 4;
    while (blkCnt > 0)
    {
        vecSrc = vld1q(pSrcVec); 
        pSrcVec += 16;
        /*
         * update per-lane min.
         */
        curExtremValVec = vminaq(curExtremValVec, vecSrc);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = blockSize & 0xF;
    if (blkCnt > 0)
    {
        vecSrc = vld1q(pSrcVec); 
        pSrcVec += 16;
        p0 = vctp8q(blkCnt);
        /*
         * Get current min per lane and current index per lane
         * when a min is selected
         */
         curExtremValVec = vminaq_m(curExtremValVec, vecSrc, p0);
    }
    /*
     * Get min value across the vector
     */
    minValue = vminavq(minValue, (q7x16_t)curExtremValVec);
    *pResult = minValue;
}

#else
#if defined(ARM_MATH_DSP)
void arm_absmin_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
        q7_t cur_absmin, out;                     /* Temporary variables to store the output value. */\
        uint32_t blkCnt;                     /* Loop counter */                                   \
                                                                                                            \
                                                                                           \
  /* Load first input value that act as reference value for comparision */                                  \
  out = *pSrc++;                                                                                            \
  out = (out > 0) ? out : (q7_t)__QSUB8(0, out);                                                                           \
                                                                                                            \
  /* Loop unrolling: Compute 4 outputs at a time */                                                         \
  blkCnt = (blockSize - 1U) >> 2U;                                                                          \
                                                                                                            \
  while (blkCnt > 0U)                                                                                       \
  {                                                                                                         \
    /* Initialize cur_absmin to next consecutive values one by one */                                         \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                \
    /* compare for the extrema value */                                                                     \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      /* Update the extrema value and it's index */                                                         \
      out = cur_absmin;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                \
    if (cur_absmin < out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                 \
    if (cur_absmin < out)                                                                          \
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
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                 \
    if (cur_absmin < out)                                                                         \
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
void arm_absmin_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
        q7_t minVal, out;                              /* Temporary variables to store the output value. */
        uint32_t blkCnt;                     /* Loop counter */


  /* Load first input value that act as reference value for comparision */
  out = (*pSrc > 0) ? *pSrc : ((*pSrc == (q7_t) 0x80) ? (q7_t) 0x7f : -*pSrc);
  pSrc++;

  /* Initialize blkCnt with number of samples */
  blkCnt = (blockSize - 1U);

  while (blkCnt > 0U)
  {
    /* Initialize minVal to the next consecutive values one by one */
    minVal = (*pSrc > 0) ? *pSrc : ((*pSrc == (q7_t) 0x80) ? (q7_t) 0x7f : -*pSrc);
    pSrc++;

    /* compare for the minimum value */
    if (out > minVal)
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
#endif /* defined(ARM_MATH_DSP) */
#endif /* defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of AbsMin group
 */
