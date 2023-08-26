/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_atan2_f16.c
 * Description:  float16 Arc tangent of y/x
 *
 * $Date:        22 April 2022
 * $Revision:    V1.10.0
 *
 * Target Processor: Cortex-M and Cortex-A cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2022 ARM Limited or its affiliates. All rights reserved.
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

/*

atan for argument between in [0, 1.0]


*/

#define PIF16 3.14f16
#define PI16HALF 1.571f16

#define ATANHALFF16 0.463648f16

#define ATAN2_NB_COEFS_F16 5

static const float16_t atan2_coefs_f16[ATAN2_NB_COEFS_F16]={0.f16
,1.f16
,0.f16
,-0.367f16
,0.152f16
};

__STATIC_FORCEINLINE float16_t arm_atan_limited_f16(float16_t x)
{
    float16_t res=atan2_coefs_f16[ATAN2_NB_COEFS_F16-1];
    int i=1;
    for(i=1;i<ATAN2_NB_COEFS_F16;i++)
    {
        res = (_Float16)x*(_Float16)res + (_Float16)atan2_coefs_f16[ATAN2_NB_COEFS_F16-1-i];
    }


    return(res);
}

__STATIC_FORCEINLINE float16_t arm_atan_f16(float16_t x)
{
   int sign=0;
   float16_t res=0.0f16;

   if ((_Float16)x < 0.0f16)
   {
      sign=1;
      x=-(_Float16)x;
   }

   if ((_Float16)x > 1.0f16)
   {
      x = 1.0f16 / (_Float16)x;
      res = (_Float16)PI16HALF - (_Float16)arm_atan_limited_f16(x);
   }
   else
   {
     res += (_Float16)arm_atan_limited_f16(x);
   }


   if (sign)
   {
     res = -(_Float16)res;
   }

   return(res);
}

/**
  @ingroup groupFastMath
 */


/**
  @addtogroup atan2
  @{
 */

/**
  @brief       Arc Tangent of y/x using sign of y and x to get right quadrant
  @param[in]   y  y coordinate
  @param[in]   x  x coordinate
  @param[out]  result  Result
  @return  error status.
 
  @par         Compute the Arc tangent of y/x:
                   The sign of y and x are used to determine the right quadrant
                   and compute the right angle.

*/
arm_status arm_atan2_f16(float16_t y,float16_t x,float16_t *result)
{
    if ((_Float16)x > 0.0f16)
    {
        *result=arm_atan_f16((_Float16)y/(_Float16)x);
        return(ARM_MATH_SUCCESS);
    }
    if ((_Float16)x < 0.0f16)
    {
        if ((_Float16)y > 0.0f16)
        {
           *result=(_Float16)arm_atan_f16((_Float16)y/(_Float16)x) + (_Float16)PIF16;
        }
        else if ((_Float16)y < 0.0f16)
        {
           *result=(_Float16)arm_atan_f16((_Float16)y/(_Float16)x) - (_Float16)PIF16;
        }
        else
        {
            if (signbit(y))
            {
               *result= -(_Float16)PIF16;
            }
            else
            {
               *result= PIF16;
            }
        }
        return(ARM_MATH_SUCCESS);
    }
    if ((_Float16)x == 0.0f16)
    {
        if ((_Float16)y > 0.0f16)
        {
            *result=PI16HALF;
            return(ARM_MATH_SUCCESS);
        }
        if ((_Float16)y < 0.0f16)
        {
            *result=-(_Float16)PI16HALF;
            return(ARM_MATH_SUCCESS);
        }
    }
    

    return(ARM_MATH_NANINF);

}

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
/**
  @} end of atan2 group
 */
