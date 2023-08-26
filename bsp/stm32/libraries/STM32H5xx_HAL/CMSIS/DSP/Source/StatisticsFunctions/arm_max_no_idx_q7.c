/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_max_no_idx_q7.c
 * Description:  Maximum value of a q7 vector without returning the index
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
  @addtogroup Max
  @{
 */

/**
  @brief         Maximum value of a q7 vector without index.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    maximum value returned here
  @return        none
 */

#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_max_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
    int32_t  blkCnt;           /* loop counters */
    q7x16_t       vecSrc;
    q7_t const *pSrcVec;
    q7x16_t       curExtremValVec = vdupq_n_s8(Q7_MIN);
    q7_t           maxValue = Q7_MIN;
    mve_pred16_t    p0;


    pSrcVec = (q7_t const *) pSrc;
    blkCnt = blockSize >> 4;
    while (blkCnt > 0)
    {
        vecSrc = vld1q(pSrcVec); 
        pSrcVec += 16;
        /*
         * update per-lane max.
         */
        curExtremValVec = vmaxq(vecSrc, curExtremValVec);
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
         * Get current max per lane and current index per lane
         * when a max is selected
         */
         curExtremValVec = vmaxq_m(curExtremValVec, vecSrc, curExtremValVec, p0);
    }
    /*
     * Get max value across the vector
     */
    maxValue = vmaxvq(maxValue, curExtremValVec);
    *pResult = maxValue;
}

#else

void arm_max_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult)
{
  q7_t maxVal1, out;       /* Temporary variables to store the output value. */     
  uint32_t blkCnt;              /* loop counter */                                  
                                                                                    
  /* Load first input value that act as reference value for comparision */          
  out = *pSrc++;                                                                    
                                                                                    
  blkCnt = (blockSize - 1U);                                                        
                                                                                    
                                                                                    
  while (blkCnt > 0U)                                                               
  {                                                                                 
    /* Initialize maxVal to the next consecutive values one by one */               
    maxVal1 = *pSrc++;                                                              
                                                                                    
    /* compare for the maximum value */                                             
    if (out < maxVal1)                                                              
    {                                                                               
      /* Update the maximum value */                                                
      out = maxVal1;                                                                
    }                                                                               
                                                                                    
    /* Decrement the loop counter */                                                
    blkCnt--;                                                                       
  }                                                                                 
                                                                                    
  /* Store the maximum value into destination pointer */                            
  *pResult = out;
}

#endif /* #if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
  @} end of Max group
 */
