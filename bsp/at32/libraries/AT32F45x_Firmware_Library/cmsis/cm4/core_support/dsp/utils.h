/******************************************************************************
 * @file     arm_math_utils.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.9.0
 * @date     20. July 2020
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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

#ifndef _ARM_MATH_UTILS_H_

#define _ARM_MATH_UTILS_H_

#include "arm_math_types.h"

#ifdef   __cplusplus
extern "C"
{
#endif

  /**
   * @brief Macros required for reciprocal calculation in Normalized LMS
   */

#define INDEX_MASK         0x0000003F


#define SQ(x) ((x) * (x))

#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))


  /**
   * @brief Function to Calculates 1/in (reciprocal) value of Q31 Data type.
   */
  __STATIC_FORCEINLINE uint32_t arm_recip_q31(
        q31_t in,
        q31_t * dst,
  const q31_t * pRecipTable)
  {
    q31_t out;
    uint32_t tempVal;
    uint32_t index, i;
    uint32_t signBits;

    if (in > 0)
    {
      signBits = ((uint32_t) (__CLZ( in) - 1));
    }
    else
    {
      signBits = ((uint32_t) (__CLZ(-in) - 1));
    }

    /* Convert input sample to 1.31 format */
    in = (in << signBits);

    /* calculation of index for initial approximated Val */
    index = (uint32_t)(in >> 24);
    index = (index & INDEX_MASK);

    /* 1.31 with exp 1 */
    out = pRecipTable[index];

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0U; i < 2U; i++)
    {
      tempVal = (uint32_t) (((q63_t) in * out) >> 31);
      tempVal = 0x7FFFFFFFu - tempVal;
      /*      1.31 with exp 1 */
      /* out = (q31_t) (((q63_t) out * tempVal) >> 30); */
      out = clip_q63_to_q31(((q63_t) out * tempVal) >> 30);
    }

    /* write output */
    *dst = out;

    /* return num of signbits of out = 1/in value */
    return (signBits + 1U);
  }


  /**
   * @brief Function to Calculates 1/in (reciprocal) value of Q15 Data type.
   */
  __STATIC_FORCEINLINE uint32_t arm_recip_q15(
        q15_t in,
        q15_t * dst,
  const q15_t * pRecipTable)
  {
    q15_t out = 0;
    uint32_t tempVal = 0;
    uint32_t index = 0, i = 0;
    uint32_t signBits = 0;

    if (in > 0)
    {
      signBits = ((uint32_t)(__CLZ( in) - 17));
    }
    else
    {
      signBits = ((uint32_t)(__CLZ(-in) - 17));
    }

    /* Convert input sample to 1.15 format */
    in = (in << signBits);

    /* calculation of index for initial approximated Val */
    index = (uint32_t)(in >>  8);
    index = (index & INDEX_MASK);

    /*      1.15 with exp 1  */
    out = pRecipTable[index];

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0U; i < 2U; i++)
    {
      tempVal = (uint32_t) (((q31_t) in * out) >> 15);
      tempVal = 0x7FFFu - tempVal;
      /*      1.15 with exp 1 */
      out = (q15_t) (((q31_t) out * tempVal) >> 14);
      /* out = clip_q31_to_q15(((q31_t) out * tempVal) >> 14); */
    }

    /* write output */
    *dst = out;

    /* return num of signbits of out = 1/in value */
    return (signBits + 1);
  }


/**
 * @brief  64-bit to 32-bit unsigned normalization
 * @param[in]  in           is input unsigned long long value
 * @param[out] normalized   is the 32-bit normalized value
 * @param[out] norm         is norm scale
 */
__STATIC_INLINE  void arm_norm_64_to_32u(uint64_t in, int32_t * normalized, int32_t *norm)
{
    int32_t     n1;
    int32_t     hi = (int32_t) (in >> 32);
    int32_t     lo = (int32_t) ((in << 32) >> 32);

    n1 = __CLZ(hi) - 32;
    if (!n1)
    {
        /*
         * input fits in 32-bit
         */
        n1 = __CLZ(lo);
        if (!n1)
        {
            /*
             * MSB set, need to scale down by 1
             */
            *norm = -1;
            *normalized = (((uint32_t) lo) >> 1);
        } else
        {
            if (n1 == 32)
            {
                /*
                 * input is zero
                 */
                *norm = 0;
                *normalized = 0;
            } else
            {
                /*
                 * 32-bit normalization
                 */
                *norm = n1 - 1;
                *normalized = lo << *norm;
            }
        }
    } else
    {
        /*
         * input fits in 64-bit
         */
        n1 = 1 - n1;
        *norm = -n1;
        /*
         * 64 bit normalization
         */
        *normalized = (((uint32_t) lo) >> n1) | (hi << (32 - n1));
    }
}

__STATIC_INLINE q31_t arm_div_q63_to_q31(q63_t num, q31_t den)
{
    q31_t   result;
    uint64_t   absNum;
    int32_t   normalized;
    int32_t   norm;

    /*
     * if sum fits in 32bits
     * avoid costly 64-bit division
     */
    absNum = num > 0 ? num : -num;
    arm_norm_64_to_32u(absNum, &normalized, &norm);
    if (norm > 0)
        /*
         * 32-bit division
         */
        result = (q31_t) num / den;
    else
        /*
         * 64-bit division
         */
        result = (q31_t) (num / den);

    return result;
}


#ifdef   __cplusplus
}
#endif

#endif /*ifndef _ARM_MATH_UTILS_H_ */
