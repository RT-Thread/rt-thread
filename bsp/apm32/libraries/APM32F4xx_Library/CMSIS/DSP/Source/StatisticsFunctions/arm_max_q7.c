/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_max_q7.c
 * Description:  Maximum value of a Q7 vector
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
  @addtogroup Max
  @{
 */

/**
  @brief         Maximum value of a Q7 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    maximum value returned here
  @param[out]    pIndex     index of maximum value returned here
  @return        none
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

static void arm_small_blk_max_q7(
    const q7_t * pSrc,
    uint16_t blockSize,
    q7_t * pResult,
    uint32_t * pIndex)
{
    int32_t        blkCnt;     /* loop counters */
    q7x16_t        extremValVec = vdupq_n_s8(Q7_MIN);
    q7_t           maxValue = Q7_MIN;
    uint8x16_t     indexVec;
    uint8x16_t     extremIdxVec;
    mve_pred16_t   p0;
    uint8_t        extremIdxArr[16];

    indexVec = vidupq_u8(0U, 1);

    blkCnt = blockSize;
    do {
        mve_pred16_t    p = vctp8q(blkCnt);
        q7x16_t         extremIdxVal = vld1q_z_s8(pSrc, p);
        /*
         * Get current max per lane and current index per lane
         * when a max is selected
         */
        p0 = vcmpgeq_m(extremIdxVal, extremValVec, p);

        extremValVec = vorrq_m(extremValVec, extremIdxVal, extremIdxVal, p0);
        /* store per-lane extrema indexes */
        vst1q_p_u8(extremIdxArr, indexVec, p0);

        indexVec += 16;
        pSrc += 16;
        blkCnt -= 16;
    }
    while (blkCnt > 0);


    /* Get max value across the vector   */
    maxValue = vmaxvq(maxValue, extremValVec);

    /* set index for lower values to max possible index   */
    p0 = vcmpgeq(extremValVec, maxValue);
    extremIdxVec = vld1q_u8(extremIdxArr);

    indexVec = vpselq(extremIdxVec, vdupq_n_u8(blockSize - 1), p0);
    *pIndex = vminvq_u8(blockSize - 1, indexVec);
    *pResult = maxValue;
}

void arm_max_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex)
{
    int32_t   totalSize = blockSize;
    const uint16_t sub_blk_sz = UINT8_MAX + 1;

    if (totalSize <= sub_blk_sz)
    {
        arm_small_blk_max_q7(pSrc, blockSize, pResult, pIndex);
    }
    else
    {
        uint32_t  curIdx = 0;
        q7_t      curBlkExtr = Q7_MIN;
        uint32_t  curBlkPos = 0;
        uint32_t  curBlkIdx = 0;
        /*
         * process blocks of 255 elts
         */
        while (totalSize >= sub_blk_sz)
        {
            const q7_t     *curSrc = pSrc;

            arm_small_blk_max_q7(curSrc, sub_blk_sz, pResult, pIndex);
            if (*pResult > curBlkExtr)
            {
                /*
                 * update partial extrema
                 */
                curBlkExtr = *pResult;
                curBlkPos = *pIndex;
                curBlkIdx = curIdx;
            }
            curIdx++;
            pSrc += sub_blk_sz;
            totalSize -= sub_blk_sz;
        }
        /*
         * remainder
         */
        arm_small_blk_max_q7(pSrc, totalSize, pResult, pIndex);
        if (*pResult > curBlkExtr)
        {
            curBlkExtr = *pResult;
            curBlkPos = *pIndex;
            curBlkIdx = curIdx;
        }
        *pIndex = curBlkIdx * sub_blk_sz + curBlkPos;
        *pResult = curBlkExtr;
    }
}
#else
void arm_max_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex)
{
        q7_t maxVal, out;                              /* Temporary variables to store the output value. */
        uint32_t blkCnt, outIndex;                     /* Loop counter */

#if defined (ARM_MATH_LOOPUNROLL)
        uint32_t index;                                /* index of maximum value */
#endif

  /* Initialise index value to zero. */
  outIndex = 0U;
  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

#if defined (ARM_MATH_LOOPUNROLL)
  /* Initialise index of maximum value. */
  index = 0U;

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = (blockSize - 1U) >> 2U;

  while (blkCnt > 0U)
  {
    /* Initialize maxVal to next consecutive values one by one */
    maxVal = *pSrc++;

    /* compare for the maximum value */
    if (out < maxVal)
    {
      /* Update the maximum value and it's index */
      out = maxVal;
      outIndex = index + 1U;
    }

    maxVal = *pSrc++;
    if (out < maxVal)
    {
      out = maxVal;
      outIndex = index + 2U;
    }

    maxVal = *pSrc++;
    if (out < maxVal)
    {
      out = maxVal;
      outIndex = index + 3U;
    }

    maxVal = *pSrc++;
    if (out < maxVal)
    {
      out = maxVal;
      outIndex = index + 4U;
    }

    index += 4U;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = (blockSize - 1U) % 4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = (blockSize - 1U);

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* Initialize maxVal to the next consecutive values one by one */
    maxVal = *pSrc++;

    /* compare for the maximum value */
    if (out < maxVal)
    {
      /* Update the maximum value and it's index */
      out = maxVal;
      outIndex = blockSize - blkCnt;
    }

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store the maximum value and it's index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of Max group
 */
