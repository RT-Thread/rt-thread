/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_min_no_idx_f64.c
 * Description:  Maximum value of a floating-point vector without returning the index
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
  @brief         Maximum value of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    minimum value returned here
  @return        none
 */
void arm_min_no_idx_f64(
    const float64_t *pSrc,
    uint32_t   blockSize,
    float64_t *pResult)
{
   float64_t   minValue = F64_MAX;
   float64_t   newVal;

   while (blockSize > 0U)
   {
       newVal = *pSrc++;
   
       /* compare for the minimum value */
       if (minValue > newVal)
       {
           /* Update the minimum value and it's index */
           minValue = newVal;
       }
   
       blockSize --;
   }
    
   *pResult = minValue;
}

/**
  @} end of Min group
 */
