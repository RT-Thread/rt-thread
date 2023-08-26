/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mse_f32.c
 * Description:  Floating point mean square error
 *
 * $Date:        05 April 2022
 * $Revision:    V1.10.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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
  @addtogroup MSE
  @{
 */

/**
  @brief         Mean square error between two floating point vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize   number of samples in input vector
  @param[out]    result      mean square error
  @return        none
 */

#if !defined(ARM_MATH_AUTOVECTORIZE)

#if defined(ARM_MATH_MVEF)
#include "arm_helium_utils.h"

void arm_mse_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    uint32_t    blockSize,
    float32_t * result)

{
    float32x4_t vecA, vecB;
    float32x4_t vecSum;
    uint32_t blkCnt; 
    float32_t sum = 0.0f;  
    vecSum = vdupq_n_f32(0.0f);

    /* Compute 4 outputs at a time */
    blkCnt = (blockSize) >> 2;
    while (blkCnt > 0U)
    {
        vecA = vld1q(pSrcA);
        pSrcA += 4;
        
        vecB = vld1q(pSrcB);
        pSrcB += 4;

        vecA = vsubq(vecA, vecB);

        vecSum = vfmaq(vecSum, vecA, vecA);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt --;
    }


    blkCnt = (blockSize) & 3;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp32q(blkCnt);
        vecA = vld1q(pSrcA);
        vecB = vld1q(pSrcB);

        vecA = vsubq(vecA, vecB);
        vecSum = vfmaq_m(vecSum, vecA, vecA, p0);
    }

    sum = vecAddAcrossF32Mve(vecSum);

    /* Store result in destination buffer */
    *result = sum / blockSize;

}

#endif

#if defined(ARM_MATH_NEON) 
void arm_mse_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    uint32_t    blockSize,
    float32_t * result)

{
    float32x4_t vecA, vecB;
    float32x4_t vecSum;
    uint32_t blkCnt; 
    float32_t inA, inB;
    float32_t sum = 0.0f;  
    vecSum = vdupq_n_f32(0.0f);
#if !defined(__aarch64__)
    f32x2_t tmp = vdup_n_f32(0.0f); 
#endif 

    /* Compute 4 outputs at a time */
    blkCnt = (blockSize) >> 2;
    while (blkCnt > 0U)
    {
        vecA = vld1q_f32(pSrcA);
        pSrcA += 4;
        
        vecB = vld1q_f32(pSrcB);
        pSrcB += 4;

        vecA = vsubq_f32(vecA, vecB);

        vecSum = vfmaq_f32(vecSum, vecA, vecA);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt --;
    }

#if defined(__aarch64__)
    sum = vpadds_f32(vpadd_f32(vget_low_f32(vecSum), vget_high_f32(vecSum)));
#else
    tmp = vpadd_f32(vget_low_f32(vecSum), vget_high_f32(vecSum));
    sum = vget_lane_f32(tmp, 0) + vget_lane_f32(tmp, 1);

#endif 

    blkCnt = (blockSize) & 3;
    while (blkCnt > 0U)
    {
        /* Calculate dot product and store result in a temporary buffer. */
        inA = *pSrcA++; 
        inB = *pSrcB++;
        inA = inA - inB;
        sum += inA * inA;
    
        /* Decrement loop counter */
        blkCnt--;
    }
    
    /* Store result in destination buffer */
    *result = sum / blockSize;

}
#endif

#endif /*#if !defined(ARM_MATH_AUTOVECTORIZE)*/



#if (!defined(ARM_MATH_MVEF) && !defined(ARM_MATH_NEON)) || defined(ARM_MATH_AUTOVECTORIZE)


void arm_mse_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    uint32_t    blockSize,
    float32_t * result)

{
  uint32_t blkCnt;                               /* Loop counter */
  float32_t inA, inB;
  float32_t sum = 0.0f;                          /* Temporary return variable */
#if defined (ARM_MATH_LOOPUNROLL)
  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = (blockSize) >> 2;

  /* First part of the processing with loop unrolling. Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while (blkCnt > 0U)
  {

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    /* Decrement loop counter */
    blkCnt--;
  }

  
  /* Loop unrolling: Compute remaining outputs */
  blkCnt = (blockSize) & 3;
#else
  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;
#endif
  while (blkCnt > 0U)
  {
    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = inA - inB;
    sum += inA * inA;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in destination buffer */
  *result = sum / blockSize;
}

#endif /* end of test for vector instruction availability */

/**
  @} end of MSE group
 */
