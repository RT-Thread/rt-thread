/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_fill_f16.c
 * Description:  Fills a constant value into a floating-point vector
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

#include "dsp/support_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)


/**
  @ingroup groupSupport
 */


/**
  @addtogroup Fill
  @{
 */

/**
  @brief         Fills a constant value into a f16 vector.
  @param[in]     value      input value to be filled
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_fill_f16(
  float16_t value,
  float16_t * pDst,
  uint32_t blockSize)
{
     do {
        mve_pred16_t    p = vctp16q(blockSize);

        vstrhq_p_f16(pDst,
            vdupq_m_n_f16(vuninitializedq_f16(), value, p), p);
        /*
         * Decrement the blockSize loop counter
         * Advance vector source and destination pointers
         */
        pDst += 8;
        blockSize -= 8;
    }
    while ((int32_t) blockSize > 0);
}
#else
void arm_fill_f16(
  float16_t value,
  float16_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* Loop counter */

#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 outputs at a time */
  blkCnt = blockSize >> 2U;

  while (blkCnt > 0U)
  {
    /* C = value */

    /* Fill value in destination buffer */
    *pDst++ = value;
    *pDst++ = value;
    *pDst++ = value;
    *pDst++ = value;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining outputs */
  blkCnt = blockSize % 0x4U;

#else

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* C = value */

    /* Fill value in destination buffer */
    *pDst++ = value;

    /* Decrement loop counter */
    blkCnt--;
  }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of Fill group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

