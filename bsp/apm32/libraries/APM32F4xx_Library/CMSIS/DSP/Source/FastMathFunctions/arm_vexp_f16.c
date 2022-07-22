/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_vlog_f16.c
 * Description:  Fast vectorized log
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

#include "dsp/fast_math_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

#include "arm_common_tables.h"

#include "arm_vec_math_f16.h"


void arm_vexp_f16(
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
   uint32_t blkCnt;

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

   f16x8_t src;
   f16x8_t dst;

   blkCnt = blockSize >> 3;

   while (blkCnt > 0U)
   {
      src = vld1q(pSrc);
      dst = vexpq_f16(src);
      vst1q(pDst, dst);

      pSrc += 8;
      pDst += 8;
      /* Decrement loop counter */
      blkCnt--;
   }

   blkCnt = blockSize & 7;
#else
   blkCnt = blockSize;
#endif

   while (blkCnt > 0U)
   {
      /* C = log(A) */

      /* Calculate log and store result in destination buffer. */
      *pDst++ = expf(*pSrc++);

      /* Decrement loop counter */
      blkCnt--;
   }
}

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

