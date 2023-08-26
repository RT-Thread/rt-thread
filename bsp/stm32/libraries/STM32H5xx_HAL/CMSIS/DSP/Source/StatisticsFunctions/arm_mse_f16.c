/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mse_f16.c
 * Description:  Half floating point mean square error
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

#include "dsp/statistics_functions_f16.h"

/**
  @ingroup groupStats
 */

/**
  @addtogroup MSE
  @{
 */

/**
  @brief         Mean square error between two half floating point vectors.
  @param[in]     pSrcA       points to the first input vector
  @param[in]     pSrcB       points to the second input vector
  @param[in]     blockSize   number of samples in input vector
  @param[out]    result      mean square error
  @return        none
 */

#if !defined(ARM_MATH_AUTOVECTORIZE)

#if defined(ARM_MATH_MVE_FLOAT16)
#include "arm_helium_utils.h"

void arm_mse_f16(
    const float16_t * pSrcA,
    const float16_t * pSrcB,
    uint32_t    blockSize,
    float16_t * result)

{
    float16x8_t vecA, vecB;
    float16x8_t vecSum;
    uint32_t blkCnt; 
    _Float16 sum = 0.0f16;  
    vecSum = vdupq_n_f16(0.0f16);

    blkCnt = (blockSize) >> 3;
    while (blkCnt > 0U)
    {
        vecA = vld1q(pSrcA);
        pSrcA += 8;
        
        vecB = vld1q(pSrcB);
        pSrcB += 8;

        vecA = vsubq(vecA, vecB);

        vecSum = vfmaq(vecSum, vecA, vecA);
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt --;
    }


    blkCnt = (blockSize) & 7;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        vecA = vld1q(pSrcA);
        vecB = vld1q(pSrcB);

        vecA = vsubq(vecA, vecB);
        vecSum = vfmaq_m(vecSum, vecA, vecA, p0);
    }

    sum = vecAddAcrossF16Mve(vecSum);

    /* Store result in destination buffer */
    *result = (_Float16)sum / (_Float16)blockSize;

}

#endif


#endif /*#if !defined(ARM_MATH_AUTOVECTORIZE)*/


#if defined(ARM_FLOAT16_SUPPORTED)

#if (!defined(ARM_MATH_MVE_FLOAT16)) || defined(ARM_MATH_AUTOVECTORIZE)



void arm_mse_f16(
    const float16_t * pSrcA,
    const float16_t * pSrcB,
    uint32_t    blockSize,
    float16_t * result)

{
  uint32_t blkCnt;                               /* Loop counter */
  _Float16 inA, inB;
  _Float16 sum = 0.0f16;                          /* Temporary return variable */
#if defined (ARM_MATH_LOOPUNROLL)
  blkCnt = (blockSize) >> 3;

 
  while (blkCnt > 0U)
  {
    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    /* Decrement loop counter */
    blkCnt--;
  }

  
  /* Loop unrolling: Compute remaining outputs */
  blkCnt = (blockSize) & 7;
#else
  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;
#endif
  while (blkCnt > 0U)
  {
    inA = *pSrcA++; 
    inB = *pSrcB++;
    inA = (_Float16)inA - (_Float16)inB;
    sum += (_Float16)inA * (_Float16)inA;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Store result in destination buffer */
  *result = (_Float16)sum / (_Float16)blockSize;
}

#endif /* end of test for vector instruction availability */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
/**
  @} end of MSE group
 */
