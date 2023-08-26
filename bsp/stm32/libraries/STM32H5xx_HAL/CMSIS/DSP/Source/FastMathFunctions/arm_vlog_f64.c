/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_vlog_f64.c
 * Description:  Fast vectorized log
 *
 * $Date:        13 September 2021
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

#include "dsp/fast_math_functions.h"
#include "arm_common_tables.h"

void arm_vlog_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize)
{
   uint32_t blkCnt; 

   blkCnt = blockSize;

   while (blkCnt > 0U)
   {
      /* C = log(A) */
  
      /* Calculate log and store result in destination buffer. */
      *pDst++ = log(*pSrc++);
  
      /* Decrement loop counter */
      blkCnt--;
   }
}
