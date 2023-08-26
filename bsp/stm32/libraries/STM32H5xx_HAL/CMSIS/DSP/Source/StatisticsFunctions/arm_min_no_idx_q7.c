/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_min_no_idx_q7.c
 * Description:  Minimum value of a q7 vector without returning the index
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
  @addtogroup Min
  @{
 */

/**
  @brief         Minimum value of a q7 vector without index.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @return        none
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_min_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
    int32_t  blkCnt;           /* loop counters */
    q7x16_t vecSrc;
    q7_t const *pSrcVec;
    q7x16_t curExtremValVec = vdupq_n_s8(Q7_MAX);
    q7_t minValue = Q7_MAX;
    mve_pred16_t p0;


    pSrcVec = (q7_t const *) pSrc;
    blkCnt = blockSize >> 4;
    while (blkCnt > 0)
    {
        vecSrc = vld1q(pSrcVec); 
        pSrcVec += 16;
        /*
         * update per-lane min.
         */
        curExtremValVec = vminq(vecSrc, curExtremValVec);
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
         curExtremValVec = vminq_m(curExtremValVec, vecSrc, curExtremValVec, p0);
    }
    /*
     * Get min value across the vector
     */
    minValue = vminvq(minValue, curExtremValVec);
    *pResult = minValue;
}

#else
void arm_min_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
  q7_t minVal1, out;       /* Temporary variables to store the output value. */    
  uint32_t blkCnt;              /* loop counter */                                  
                                                                                    
  /* Load first input value that act as reference value for comparision */          
  out = *pSrc++;                                                                    
                                                                                    
  blkCnt = (blockSize - 1U);                                                        
                                                                                    
                                                                                    
  while (blkCnt > 0U)                                                               
  {                                                                                 
    /* Initialize minVal to the next consecutive values one by one */               
    minVal1 = *pSrc++;                                                              
                                                                                    
    /* compare for the minimum value */                                             
    if (out > minVal1)                                                              
    {                                                                               
      /* Update the minimum value */                                                
      out = minVal1;                                                                
    }                                                                               
                                                                                    
    /* Decrement the loop counter */                                                
    blkCnt--;                                                                       
  }                                                                                 
                                                                                    
  /* Store the minimum value into destination pointer */                            
  *pResult = out;
}

#endif /* #if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of Min group
 */
