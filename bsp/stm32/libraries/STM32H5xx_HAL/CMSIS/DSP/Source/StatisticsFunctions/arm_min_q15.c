/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_min_q15.c
 * Description:  Minimum value of a Q15 vector
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
  @addtogroup Min
  @{
 */

/**
  @brief         Minimum value of a Q15 vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @param[out]    pIndex     index of minimum value returned here
  @return        none
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_min_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex)
{

    int32_t         blkCnt;     /* loop counters */
    q15x8_t         extremValVec = vdupq_n_s16(Q15_MAX);
    q15_t           minValue = Q15_MAX;
    uint16x8_t      indexVec;
    uint16x8_t      extremIdxVec;
    mve_pred16_t    p0;
    uint16_t        extremIdxArr[8];

    indexVec = vidupq_u16(0U, 1);

    blkCnt = blockSize;
    do {
        mve_pred16_t    p = vctp16q(blkCnt);
        q15x8_t         extremIdxVal = vld1q_z_s16(pSrc, p);
        /*
         * Get current min per lane and current index per lane
         * when a min is selected
         */
        p0 = vcmpleq_m(extremIdxVal, extremValVec, p);

        extremValVec = vorrq_m(extremValVec, extremIdxVal, extremIdxVal, p0);
        /* store per-lane extrema indexes */
        vst1q_p_u16(extremIdxArr, indexVec, p0);

        indexVec += 8;
        pSrc += 8;
        blkCnt -= 8;
    }
    while (blkCnt > 0);

    /* Get min value across the vector   */
    minValue = vminvq(minValue, extremValVec);

    /* set index for lower values to min possible index   */
    p0 = vcmpleq(extremValVec, minValue);
    extremIdxVec = vld1q_u16(extremIdxArr);

    indexVec = vpselq(extremIdxVec, vdupq_n_u16(blockSize - 1), p0);
    *pIndex = vminvq(blockSize - 1, indexVec);
    *pResult = minValue;
 
}
#else
void arm_min_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex)
{
        q15_t minVal, out;                             /* Temporary variables to store the output value. */
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
    /* Initialize minVal to next consecutive values one by one */
    minVal = *pSrc++;

    /* compare for the minimum value */
    if (out > minVal)
    {
      /* Update the minimum value and it's index */
      out = minVal;
      outIndex = index + 1U;
    }

    minVal = *pSrc++;
    if (out > minVal)
    {
      out = minVal;
      outIndex = index + 2U;
    }

    minVal = *pSrc++;
    if (out > minVal)
    {
      out = minVal;
      outIndex = index + 3U;
    }

    minVal = *pSrc++;
    if (out > minVal)
    {
      out = minVal;
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
    /* Initialize minVal to the next consecutive values one by one */
    minVal = *pSrc++;

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
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of Min group
 */
