/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_absmin_q7.c
 * Description:  Minimum value of absolute values of a Q7 vector
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
  @param[out]    pIndex     index of minimum value returned here
  @return        none
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include <stdint.h>
#include "arm_helium_utils.h"

#define MAX_BLKSZ_S8  (UINT8_MAX+1)

static void arm_small_blk_absmin_q7(
    const q7_t        *pSrc,
    uint32_t     blockSize,
    q7_t        *pResult,
    uint32_t    *pIndex)
{
    uint16_t        blkCnt;           /* loop counters */
    q7x16_t       vecSrc;
    q7_t const   *pSrcVec;
    q7x16_t       curExtremValVec = vdupq_n_s8(Q7_ABSMAX);
    q7_t           minValue = Q7_ABSMAX;
    uint16_t       idx = blockSize - 1;
    uint8x16_t    indexVec;
    uint8x16_t    curExtremIdxVec;
    uint32_t       startIdx = 0;
    mve_pred16_t   p0;


    indexVec = vidupq_wb_u8(&startIdx, 1);
    curExtremIdxVec = vdupq_n_u8(0);

    pSrcVec = (q7_t const *) pSrc;
    blkCnt = blockSize >> 4;
    while (blkCnt > 0U)
    {
        vecSrc = vld1q(pSrcVec);
        pSrcVec += 16;
        vecSrc = vabsq(vecSrc);
        /*
         * Get current min per lane and current index per lane
         * when a min is selected
         */
        p0 = vcmpleq(vecSrc, curExtremValVec);
        curExtremValVec = vpselq(vecSrc, curExtremValVec, p0);
        curExtremIdxVec = vpselq(indexVec, curExtremIdxVec, p0);

        indexVec = vidupq_wb_u8(&startIdx, 1);
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
    if (blkCnt > 0U)
    {
        vecSrc = vld1q(pSrcVec);
        pSrcVec += 16;
        vecSrc = vabsq(vecSrc);

        p0 = vctp8q(blkCnt);
        /*
         * Get current min per lane and current index per lane
         * when a min is selected
         */
        p0 = vcmpleq_m(vecSrc, curExtremValVec, p0);
        curExtremValVec = vpselq(vecSrc, curExtremValVec, p0);
        curExtremIdxVec = vpselq(indexVec, curExtremIdxVec, p0);
    }
    /*
     * Get min value across the vector
     */
    minValue = vminvq(minValue, curExtremValVec);
    /*
     * set index for lower values to min possible index
     */
    p0 = vcmpleq(curExtremValVec, minValue);
    idx = vminvq_p_u8(idx, curExtremIdxVec, p0);
    /*
     * Save result
     */
    *pIndex = idx;
    *pResult = minValue;
}


void arm_absmin_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex)
{
     int32_t   totalSize = blockSize;

    if (totalSize <= MAX_BLKSZ_S8)
    {
        arm_small_blk_absmin_q7(pSrc, blockSize, pResult, pIndex);
    }
    else
    {
        uint32_t  curIdx = 0;
        q7_t      curBlkExtr = Q7_MAX;
        uint32_t  curBlkPos = 0;
        uint32_t  curBlkIdx = 0;
        /*
         * process blocks of 255 elts
         */
        while (totalSize >= MAX_BLKSZ_S8)
        {
            const q7_t     *curSrc = pSrc;

            arm_small_blk_absmin_q7(curSrc, MAX_BLKSZ_S8, pResult, pIndex);
            if (*pResult < curBlkExtr)
            {
                /*
                 * update partial extrema
                 */
                curBlkExtr = *pResult;
                curBlkPos = *pIndex;
                curBlkIdx = curIdx;
            }
            curIdx++;
            pSrc += MAX_BLKSZ_S8;
            totalSize -= MAX_BLKSZ_S8;
        }
        /*
         * remainder
         */
        arm_small_blk_absmin_q7(pSrc, totalSize, pResult, pIndex);
        if (*pResult < curBlkExtr)
        {
            curBlkExtr = *pResult;
            curBlkPos = *pIndex;
            curBlkIdx = curIdx;
        }
        *pIndex = curBlkIdx * MAX_BLKSZ_S8 + curBlkPos;
        *pResult = curBlkExtr;
    }
}

#else
#if defined(ARM_MATH_DSP)
void arm_absmin_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex)
{
        q7_t cur_absmin, out;                     /* Temporary variables to store the output value. */\
        uint32_t blkCnt, outIndex;                     /* Loop counter */                                   \
        uint32_t index;                                /* index of maximum value */                         \
                                                                                                            \
  /* Initialize index value to zero. */                                                                     \
  outIndex = 0U;                                                                                            \
  /* Load first input value that act as reference value for comparision */                                  \
  out = *pSrc++;                                                                                            \
  out = (out > 0) ? out : (q7_t)__QSUB8(0, out);                                                                           \
  /* Initialize index of extrema value. */                                                                  \
  index = 0U;                                                                                               \
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
      outIndex = index + 1U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 2U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                \
    if (cur_absmin < out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 3U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q7_t)__QSUB8(0, cur_absmin);                                                                 \
    if (cur_absmin < out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 4U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    index += 4U;                                                                                            \
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
      outIndex = blockSize - blkCnt;                                                                        \
    }                                                                                                       \
                                                                                                            \
    /* Decrement loop counter */                                                                            \
    blkCnt--;                                                                                               \
  }                                                                                                         \
                                                                                                            \
  /* Store the extrema value and it's index into destination pointers */                                    \
  *pResult = out;                                                                                           \
  *pIndex = outIndex;
}
#else
void arm_absmin_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex)
{
        q7_t minVal, out;                              /* Temporary variables to store the output value. */
        uint32_t blkCnt, outIndex;                     /* Loop counter */

  /* Initialise index value to zero. */
  outIndex = 0U;
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
      outIndex = blockSize - blkCnt;
    }

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store the minimum value and it's index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}
#endif /* defined(ARM_MATH_DSP) */
#endif /* defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of AbsMin group
 */
