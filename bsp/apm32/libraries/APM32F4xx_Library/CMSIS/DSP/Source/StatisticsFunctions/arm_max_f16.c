/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_max_f16.c
 * Description:  Maximum value of a floating-point vector
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

#if (defined(ARM_MATH_NEON) || defined(ARM_MATH_MVEF)) && !defined(ARM_MATH_AUTOVECTORIZE)
#include <limits.h>
#endif

/**
  @ingroup groupStats
 */


/**
  @addtogroup Max
  @{
 */

/**
  @brief         Maximum value of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    maximum value returned here
  @param[out]    pIndex     index of maximum value returned here
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_max_f16(
  const float16_t * pSrc,
  uint32_t blockSize,
  float16_t * pResult,
  uint32_t * pIndex)
{
     int32_t blkCnt;
    f16x8_t vecSrc;
    f16x8_t curExtremValVec = vdupq_n_f16(F16_MIN);
    float16_t maxValue = F16_MIN;
    uint32_t idx = blockSize;
    uint16x8_t indexVec;
    uint16x8_t curExtremIdxVec;
    uint32_t curIdx = 0;
    mve_pred16_t p0;
    float16_t tmp;


    indexVec = vidupq_wb_u16(&curIdx, 1);
    curExtremIdxVec = vdupq_n_u16(0);

    /* Compute 4 outputs at a time */
    blkCnt = blockSize >> 3;
    while (blkCnt > 0)
    {
        vecSrc = vldrhq_f16(pSrc);
        /*
         * Get current max per lane and current index per lane
         * when a max is selected
         */
        p0 = vcmpgeq(vecSrc, curExtremValVec);
        curExtremValVec = vpselq(vecSrc, curExtremValVec, p0);
        curExtremIdxVec = vpselq(indexVec, curExtremIdxVec, p0);

        indexVec = vidupq_wb_u16(&curIdx, 1);

        pSrc += 8;
        /* Decrement the loop counter */
        blkCnt--;
    }


    /*
     * Get max value across the vector
     */
    maxValue = vmaxnmvq(maxValue, curExtremValVec);
    /*
     * set index for lower values to max possible index
     */
    p0 = vcmpgeq(curExtremValVec, maxValue);
    indexVec = vpselq(curExtremIdxVec, vdupq_n_u16(blockSize), p0);
    /*
     * Get min index which is thus for a max value
     */
    idx = vminvq(idx, indexVec);

    /* Tail */
    blkCnt = blockSize & 7;

    while (blkCnt > 0)
    {
      /* Initialize tmp to the next consecutive values one by one */
      tmp = *pSrc++;

      /* compare for the maximum value */
      if (maxValue < tmp)
      {
        /* Update the maximum value and it's index */
        maxValue = tmp;
        idx = blockSize - blkCnt;
      }

      /* Decrement loop counter */
      blkCnt--;
    }

    /*
     * Save result
     */
    *pIndex = idx;
    *pResult = maxValue;
}

#else
void arm_max_f16(
  const float16_t * pSrc,
        uint32_t blockSize,
        float16_t * pResult,
        uint32_t * pIndex)
{
        float16_t maxVal, out;                         /* Temporary variables to store the output value. */
        uint32_t blkCnt, outIndex;                     /* Loop counter */

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)
        uint32_t index;                                /* index of maximum value */
#endif

  /* Initialise index value to zero. */
  outIndex = 0U;

  /* Load first input value that act as reference value for comparision */
  out = *pSrc++;

#if defined (ARM_MATH_LOOPUNROLL) && !defined(ARM_MATH_AUTOVECTORIZE)
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
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of Max group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

