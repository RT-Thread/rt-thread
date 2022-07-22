/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_float_to_q15.c
 * Description:  Converts the elements of the floating-point vector to Q15 vector
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
  @addtogroup float_to_x
  @{
 */

/**
  @brief         Converts the elements of the floating-point vector to f16 vector.
  @param[in]     pSrc       points to the f32 input vector
  @param[out]    pDst       points to the f16 output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none

 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) && defined(__CMSIS_GCC_H)
#pragma GCC warning "Scalar version of arm_float_to_f16 built. Helium version has build issues with gcc."
#endif

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) &&  !defined(__CMSIS_GCC_H)

void arm_float_to_f16(
  const float32_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
    int32_t  blkCnt;           /* loop counters */
    float32x4x2_t tmp;
    float16x8_t vecDst;
    float32_t const *pSrcVec;


    pSrcVec = (float32_t const *) pSrc;
    blkCnt = blockSize >> 3;
    while (blkCnt > 0)
    {
        /* convert from float32 to float16 and then store the results in the destination buffer */
        tmp = vld2q(pSrcVec);   pSrcVec += 8;
        /* narrow / merge */
        vecDst = vcvtbq_f16_f32(vecDst, tmp.val[0]);
        vecDst = vcvttq_f16_f32(vecDst, tmp.val[1]);
        vst1q(pDst, vecDst);    pDst += 8;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }

    /*
     * tail
     */
    blkCnt = blockSize & 7;
    if (blkCnt > 0)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        tmp = vld2q(pSrcVec);
        vecDst = vcvtbq_f16_f32(vecDst, tmp.val[0]);
        vecDst = vcvttq_f16_f32(vecDst, tmp.val[1]);
        vstrhq_p(pDst, vecDst, p0);
    }
}

#else

void arm_float_to_f16(
  const float32_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
    const float32_t *pIn = pSrc;      /* Src pointer */
    uint32_t  blkCnt;           /* loop counter */

    /*
     * Loop over blockSize number of values
     */
    blkCnt = blockSize;

    while (blkCnt > 0U)
    {

        *pDst++ = (float16_t) * pIn++;
        /*
         * Decrement the loop counter
         */
        blkCnt--;
    }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of float_to_x group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

