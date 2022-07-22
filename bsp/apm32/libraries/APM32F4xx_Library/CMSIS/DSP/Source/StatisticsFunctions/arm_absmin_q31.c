/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_absmin_q31.c
 * Description:  Minimum value of absolute values of a Q31 vector
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
  @brief         Minimum value of absolute values of a Q31 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @param[out]    pIndex     index of minimum value returned here
  @return        none
 */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_absmin_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex)
{
      uint16_t        blkCnt;           /* loop counters */
    q31x4_t       vecSrc;
    q31_t const   *pSrcVec;
    q31x4_t       curExtremValVec = vdupq_n_s32(Q31_ABSMAX);
    q31_t           minValue = Q31_ABSMAX;
    uint16_t        idx = blockSize;
    uint32x4_t    indexVec;
    uint32x4_t    curExtremIdxVec;
    uint32_t        startIdx = 0;
    mve_pred16_t    p0;


    indexVec = vidupq_wb_u32(&startIdx, 1);
    curExtremIdxVec = vdupq_n_u32(0);

    pSrcVec = (q31_t const *) pSrc;
    blkCnt = blockSize >> 2;
    while (blkCnt > 0U)
    {
        vecSrc = vldrwq_s32(pSrcVec);
        pSrcVec += 4;
        vecSrc = vabsq(vecSrc);
        /*
         * Get current min per lane and current index per lane
         * when a min is selected
         */
        p0 = vcmpleq(vecSrc, curExtremValVec);
        curExtremValVec = vpselq(vecSrc, curExtremValVec, p0);
        curExtremIdxVec = vpselq(indexVec, curExtremIdxVec, p0);

        indexVec = vidupq_wb_u32(&startIdx, 1);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = blockSize & 3;
    if (blkCnt > 0U)
    {
        vecSrc = vldrwq_s32(pSrcVec);
        pSrcVec += 4;
        vecSrc = vabsq(vecSrc);

        p0 = vctp32q(blkCnt);
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
    indexVec = vpselq(curExtremIdxVec, vdupq_n_u32(blockSize), p0);
    /*
     * Get min index which is thus for a min value
     */
    idx = vminvq(idx, indexVec);
    /*
     * Save result
     */
    *pIndex = idx;
    *pResult = minValue;
}

#else
#if defined(ARM_MATH_DSP)
void arm_absmin_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex)
{
        q31_t cur_absmin, out;                     /* Temporary variables to store the output value. */\
        uint32_t blkCnt, outIndex;                     /* Loop counter */                                   \
        uint32_t index;                                /* index of maximum value */                         \
                                                                                                            \
  /* Initialize index value to zero. */                                                                     \
  outIndex = 0U;                                                                                            \
  /* Load first input value that act as reference value for comparision */                                  \
  out = *pSrc++;                                                                                            \
  out = (out > 0) ? out : (q31_t)__QSUB(0, out);                                                                           \
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
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q31_t)__QSUB(0, cur_absmin);                                                                \
    /* compare for the extrema value */                                                                     \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      /* Update the extrema value and it's index */                                                         \
      out = cur_absmin;                                                                                       \
      outIndex = index + 1U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q31_t)__QSUB(0, cur_absmin);                                                                \
    if (cur_absmin < out)                                                                         \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 2U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q31_t)__QSUB(0, cur_absmin);                                                                \
    if (cur_absmin < out)                                                                          \
    {                                                                                                       \
      out = cur_absmin;                                                                                       \
      outIndex = index + 3U;                                                                                \
    }                                                                                                       \
                                                                                                            \
    cur_absmin = *pSrc++;                                                                                     \
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q31_t)__QSUB(0, cur_absmin);                                                                 \
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
    cur_absmin = (cur_absmin > 0) ? cur_absmin : (q31_t)__QSUB(0, cur_absmin);                                                                 \
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
void arm_absmin_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex)
{
        q31_t minVal, out;                             /* Temporary variables to store the output value. */
        uint32_t blkCnt, outIndex;                     /* Loop counter */

  /* Initialise index value to zero. */
  outIndex = 0U;
  /* Load first input value that act as reference value for comparision */
  out = (*pSrc > 0) ? *pSrc : ((*pSrc == INT32_MIN) ? INT32_MAX : -*pSrc);
  pSrc++;

  /* Initialize blkCnt with number of samples */
  blkCnt = (blockSize - 1U);

  while (blkCnt > 0U)
  {
    /* Initialize minVal to the next consecutive values one by one */
    minVal = (*pSrc > 0) ? *pSrc : ((*pSrc == INT32_MIN) ? INT32_MAX : -*pSrc);
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
