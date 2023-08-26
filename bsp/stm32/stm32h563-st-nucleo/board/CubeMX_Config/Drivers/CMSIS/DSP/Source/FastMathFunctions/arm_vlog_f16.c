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
#include "dsp/support_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

/* Degree of the polynomial approximation */
#define NB_DEG_LOGF16 3

/*
Related to the Log2 of the number of approximations.
For instance, with 3 there are 1 + 2^3 polynomials
*/
#define NB_DIV_LOGF16 3

/* Length of the LUT table */
#define NB_LUT_LOGF16 (NB_DEG_LOGF16+1)*(1 + (1<<NB_DIV_LOGF16))


/*

LUT of polynomial approximations.

Could be generated with:

ClearAll[lut, coefs, nb, deg];
nb = 3;
deg = 3;
lut = Table[
   MiniMaxApproximation[
     Log[x/2^nb + i], {x, {10^-6, 1.0/2^nb}, deg, 0},
     MaxIterations -> 1000][[2, 1]], {i, 1, 2, (1.0/2^nb)}];
coefs = Chop@Flatten[CoefficientList[lut, x]];

*/
static float16_t lut_logf16[NB_LUT_LOGF16]={
   0,0.125,-0.00781197,0.00063974,0.117783,
   0.111111,-0.00617212,0.000447935,0.223144,
   0.1,-0.00499952,0.000327193,0.318454,0.0909091,
   -0.00413191,0.000246234,0.405465,0.0833333,
   -0.00347199,0.000189928,0.485508,0.0769231,
   -0.00295841,0.00014956,0.559616,0.0714286,
   -0.0025509,0.000119868,0.628609,0.0666667,
   -0.00222213,0.0000975436,0.693147,
   0.0625,-0.00195305,0.0000804357};


float16_t logf16_scalar(float16_t x)
{
    int16_t i =  arm_typecast_s16_f16(x);

    int32_t vecExpUnBiased = (i >> 10) - 15;
    i = i - (vecExpUnBiased << 10);
    float16_t vecTmpFlt1 = arm_typecast_f16_s16(i);

    float16_t *lut;
    int n;
    float16_t tmp,v;

    tmp = ((_Float16)vecTmpFlt1 - 1.0f16) * (1 << NB_DIV_LOGF16);
    n = (int)floor((double)tmp);
    v = (_Float16)tmp - (_Float16)n;

    lut = lut_logf16 + n * (1+NB_DEG_LOGF16);

    float16_t res = lut[NB_DEG_LOGF16-1];
    for(int j=NB_DEG_LOGF16-2; j >=0 ; j--)
    {
       res = (_Float16)lut[j] + (_Float16)v * (_Float16)res;
    }

    res = (_Float16)res + 0.693147f16 * (_Float16)vecExpUnBiased;


    return(res);
}

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_common_tables.h"
#include "arm_vec_math_f16.h"


float16x8_t vlogq_lut_f16(float16x8_t vecIn)
{
    int16x8_t i =  vreinterpretq_s16_f16(vecIn);

    int16x8_t vecExpUnBiased = vsubq_n_s16(vshrq_n_s16(i,10), 15);
    i = vsubq_s16(i,vshlq_n_s16(vecExpUnBiased,10));
    float16x8_t vecTmpFlt1 = vreinterpretq_f16_s16(i);


    float16x8_t lutV;
    int16x8_t n;
    int16x8_t offset;

    float16x8_t tmp,v,res;

    tmp = vmulq_n_f16(vsubq_n_f16(vecTmpFlt1,1.0f16),(_Float16)(1 << NB_DIV_LOGF16));

    n = vcvtq_s16_f16(tmp);
    v = vsubq_f16(tmp,vcvtq_f16_s16(n));


    offset = vmulq_n_s16(n,(1+NB_DEG_LOGF16));
    offset = vaddq_n_s16(offset,NB_DEG_LOGF16-1);

    res = vldrhq_gather_shifted_offset_f16(lut_logf16,(uint16x8_t)offset);
    offset = vsubq_n_s16(offset,1);

    for(int j=NB_DEG_LOGF16-2; j >=0 ; j--)
    {
       lutV = vldrhq_gather_shifted_offset_f16(lut_logf16,(uint16x8_t)offset);
       res = vfmaq_f16(lutV,v,res);
       offset = vsubq_n_s16(offset,1);

    }

    res = vfmaq_n_f16(res,vcvtq_f16_s16(vecExpUnBiased),0.693147f16);


    return(res);

}

#endif

/**
  @ingroup groupFastMath
 */

/**
  @addtogroup vlog
  @{
 */

/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */


void arm_vlog_f16(
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
      dst = vlogq_lut_f16(src);
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
      *pDst++ = logf16_scalar(*pSrc++);

      /* Decrement loop counter */
      blkCnt--;
   }
}



/**
  @} end of vlog group
 */


#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
