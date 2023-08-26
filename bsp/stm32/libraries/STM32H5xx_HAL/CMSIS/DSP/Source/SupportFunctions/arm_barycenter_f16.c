/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_barycenter_f16.c
 * Description:  Barycenter
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

#include <limits.h>
#include <math.h>

/**
  @ingroup groupSupport
 */

/**
  @defgroup barycenter Barycenter

  Barycenter of weighted vectors
 */

/**
  @addtogroup barycenter
  @{
 */


/**
 * @brief Barycenter
 *
 *
 * @param[in]    *in         List of vectors
 * @param[in]    *weights    Weights of the vectors
 * @param[out]   *out        Barycenter
 * @param[in]    nbVectors   Number of vectors
 * @param[in]    vecDim      Dimension of space (vector dimension)
 * @return       None
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

void arm_barycenter_f16(const float16_t *in, 
  const float16_t *weights, 
  float16_t *out, 
  uint32_t nbVectors,
  uint32_t vecDim)
{
    const float16_t *pIn, *pW;
    const float16_t *pIn1, *pIn2, *pIn3, *pIn4;
    float16_t      *pOut;
    uint32_t        blkCntVector, blkCntSample;
    float16_t       accum, w;

    blkCntVector = nbVectors;
    blkCntSample = vecDim;

    accum = 0.0f;

    pW = weights;
    pIn = in;


    arm_fill_f16(0.0f, out, vecDim);


    /* Sum */
    pIn1 = pIn;
    pIn2 = pIn1 + vecDim;
    pIn3 = pIn2 + vecDim;
    pIn4 = pIn3 + vecDim;

    blkCntVector = nbVectors >> 2;
    while (blkCntVector > 0) 
    {
        f16x8_t         outV, inV1, inV2, inV3, inV4;
        float16_t       w1, w2, w3, w4;

        pOut = out;
        w1 = *pW++;
        w2 = *pW++;
        w3 = *pW++;
        w4 = *pW++;
        accum += (_Float16)w1 + (_Float16)w2 + (_Float16)w3 + (_Float16)w4;

        blkCntSample = vecDim >> 3;
        while (blkCntSample > 0) {
            outV = vld1q((const float16_t *) pOut);
            inV1 = vld1q(pIn1);
            inV2 = vld1q(pIn2);
            inV3 = vld1q(pIn3);
            inV4 = vld1q(pIn4);
            outV = vfmaq(outV, inV1, w1);
            outV = vfmaq(outV, inV2, w2);
            outV = vfmaq(outV, inV3, w3);
            outV = vfmaq(outV, inV4, w4);
            vst1q(pOut, outV);

            pOut += 8;
            pIn1 += 8;
            pIn2 += 8;
            pIn3 += 8;
            pIn4 += 8;

            blkCntSample--;
        }

        blkCntSample = vecDim & 7;
        while (blkCntSample > 0) {
            *pOut = (_Float16)*pOut + (_Float16)*pIn1++ * (_Float16)w1;
            *pOut = (_Float16)*pOut + (_Float16)*pIn2++ * (_Float16)w2;
            *pOut = (_Float16)*pOut + (_Float16)*pIn3++ * (_Float16)w3;
            *pOut = (_Float16)*pOut + (_Float16)*pIn4++ * (_Float16)w4;
            pOut++;
            blkCntSample--;
        }

        pIn1 += 3 * vecDim;
        pIn2 += 3 * vecDim;
        pIn3 += 3 * vecDim;
        pIn4 += 3 * vecDim;

        blkCntVector--;
    }

    pIn = pIn1;

    blkCntVector = nbVectors & 3;
    while (blkCntVector > 0) 
    {
        f16x8_t         inV, outV;

        pOut = out;
        w = *pW++;
        accum += (_Float16)w;

        blkCntSample = vecDim >> 3;
        while (blkCntSample > 0) 
        {
            outV = vld1q_f16(pOut);
            inV = vld1q_f16(pIn);
            outV = vfmaq(outV, inV, w);
            vst1q_f16(pOut, outV);
            pOut += 8;
            pIn += 8;

            blkCntSample--;
        }

        blkCntSample = vecDim & 7;
        while (blkCntSample > 0) 
        {
            *pOut = (_Float16)*pOut + (_Float16)*pIn++ * (_Float16)w;
            pOut++;
            blkCntSample--;
        }

        blkCntVector--;
    }

    /* Normalize */
    pOut = out;
    accum = 1.0f16 / (_Float16)accum;

    blkCntSample = vecDim >> 3;
    while (blkCntSample > 0) 
    {
        f16x8_t         tmp;

        tmp = vld1q((const float16_t *) pOut);
        tmp = vmulq(tmp, accum);
        vst1q(pOut, tmp);
        pOut += 8;
        blkCntSample--;
    }

    blkCntSample = vecDim & 7;
    while (blkCntSample > 0) 
    {
        *pOut = (_Float16)*pOut * (_Float16)accum;
        pOut++;
        blkCntSample--;
    }
}
#else
void arm_barycenter_f16(const float16_t *in, const float16_t *weights, float16_t *out, uint32_t nbVectors,uint32_t vecDim)
{

   const float16_t *pIn,*pW;
   float16_t *pOut;
   uint32_t blkCntVector,blkCntSample;
   float16_t accum, w;

   blkCntVector = nbVectors;
   blkCntSample = vecDim;

   accum = 0.0f16;

   pW = weights;
   pIn = in;

   /* Set counters to 0 */
   blkCntSample = vecDim;
   pOut = out;

   while(blkCntSample > 0)
   {
         *pOut = 0.0f16;
         pOut++;
         blkCntSample--;
   }

   /* Sum */
   while(blkCntVector > 0)
   {
      pOut = out;
      w = *pW++;
      accum += (_Float16)w;

      blkCntSample = vecDim;
      while(blkCntSample > 0)
      {
          *pOut = (_Float16)*pOut + (_Float16)*pIn++ * (_Float16)w;
          pOut++;
          blkCntSample--;
      }

      blkCntVector--;
   }

   /* Normalize */
   blkCntSample = vecDim;
   pOut = out;

   while(blkCntSample > 0)
   {
         *pOut = (_Float16)*pOut / (_Float16)accum;
         pOut++;
         blkCntSample--;
   }

}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of barycenter group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

