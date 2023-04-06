/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_min_f32.c
 * Description:  Minimum value of a floating-point vector
 *
 * $Date:        18. March 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_math.h"
#include <limits.h>

/**
  @ingroup groupStats
 */

/**
  @defgroup Min Minimum

  Computes the minimum value of an array of data.
  The function returns both the minimum value and its position within the array.
  There are separate functions for floating-point, Q31, Q15, and Q7 data types.
 */

/**
  @addtogroup Min
  @{
 */

/**
  @brief         Minimum value of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @param[out]    pIndex     index of minimum value returned here
  @return        none
 */
#if defined(ARM_MATH_NEON)
void arm_min_f32(
  const float32_t * pSrc,
  uint32_t blockSize,
  float32_t * pResult,
  uint32_t * pIndex)
{
  float32_t maxVal1, maxVal2, out;               /* Temporary variables to store the output value. */
  uint32_t blkCnt, outIndex, count;              /* loop counter */

  float32x4_t outV, srcV;
  float32x2_t outV2;

  uint32x4_t idxV;
  uint32x4_t maxIdx={ULONG_MAX,ULONG_MAX,ULONG_MAX,ULONG_MAX};
  uint32x4_t index={4,5,6,7};
  uint32x4_t delta={4,4,4,4};
  uint32x4_t countV={0,1,2,3};
  uint32x2_t countV2;

  /* Initialise the count value. */
  count = 0U;

  /* Initialise the index value to zero. */
  outIndex = 0U;

  /* Load first input value that act as reference value for comparison */
  if (blockSize <= 3)
  {
      out = *pSrc++;

      blkCnt = blockSize - 1;

      while (blkCnt > 0U)
      {
        /* Initialize maxVal to the next consecutive values one by one */
        maxVal1 = *pSrc++;
    
        /* compare for the maximum value */
        if (out > maxVal1)
        {
          /* Update the maximum value and it's index */
          out = maxVal1;
          outIndex = blockSize - blkCnt;
        }
    
        /* Decrement the loop counter */
        blkCnt--;
      }
  }
  else
  {
      outV = vld1q_f32(pSrc);
      pSrc += 4;
    
      /* Compute 4 outputs at a time */
      blkCnt = (blockSize - 4 ) >> 2U;
    
      while (blkCnt > 0U)
      {
        srcV = vld1q_f32(pSrc);
        pSrc += 4;
    
        idxV = vcltq_f32(srcV, outV);
        outV = vbslq_f32(idxV, srcV, outV );
        countV = vbslq_u32(idxV, index,countV );
    
        index = vaddq_u32(index,delta);
    
        /* Decrement the loop counter */
        blkCnt--;
      }
    
      outV2 = vpmin_f32(vget_low_f32(outV),vget_high_f32(outV));
      outV2 = vpmin_f32(outV2,outV2);
      out = outV2[0];
    
      idxV = vceqq_f32(outV, vdupq_n_f32(out));
      countV = vbslq_u32(idxV, countV,maxIdx);
      
      countV2 = vpmin_u32(vget_low_u32(countV),vget_high_u32(countV));
      countV2 = vpmin_u32(countV2,countV2);
      outIndex = countV2[0];
    
      /* if (blockSize - 1U) is not multiple of 4 */
      blkCnt = (blockSize - 4 ) % 4U;
    
      while (blkCnt > 0U)
      {
        /* Initialize maxVal to the next consecutive values one by one */
        maxVal1 = *pSrc++;
    
        /* compare for the maximum value */
        if (out > maxVal1)
        {
          /* Update the maximum value and it's index */
          out = maxVal1;
          outIndex = blockSize - blkCnt ;
        }
    
        /* Decrement the loop counter */
        blkCnt--;
      }
  }

  /* Store the maximum value and it's index into destination pointers */
  *pResult = out;
  *pIndex = outIndex;
}
#else
void arm_min_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex)
{
        float32_t minVal, out;                         /* Temporary variables to store the output value. */
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
#endif /* #if defined(ARM_MATH_NEON) */

/**
  @} end of Min group
 */
