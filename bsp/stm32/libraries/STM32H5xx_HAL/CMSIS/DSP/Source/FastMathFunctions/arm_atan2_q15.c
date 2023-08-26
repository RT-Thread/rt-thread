/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_atan2_q15.c
 * Description:  float32 Arc tangent of y/x
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

#include "dsp/fast_math_functions.h"        
#include "dsp/utils.h"        

/*

atan for argument between in [0, 1.0]

*/


/* Q2.13 */
#define ATANHALFQ13 0xed6
#define PIHALFQ13 0x3244
#define PIQ13 0x6488

#define ATAN2_NB_COEFS_Q15 10

static const q15_t atan2_coefs_q15[ATAN2_NB_COEFS_Q15]={0x0000
,0x7fff
,0xffff
,0xd567
,0xff70
,0x1bad
,0xfd58
,0xe9a9
,0x1129
,0xfbdb
};

__STATIC_FORCEINLINE q15_t arm_atan_limited_q15(q15_t x)
{
    q31_t res=(q31_t)atan2_coefs_q15[ATAN2_NB_COEFS_Q15-1];
    int i=1;
    for(i=1;i<ATAN2_NB_COEFS_Q15;i++)
    {
        res = ((q31_t) x * res) >> 15U;
        res = res + ((q31_t) atan2_coefs_q15[ATAN2_NB_COEFS_Q15-1-i]) ;
    }

    res = __SSAT(res>>2,16);

    
    return(res);
}


__STATIC_FORCEINLINE q15_t arm_atan_q15(q15_t y,q15_t x)
{
   int sign=0;
   q15_t res=0;

   if (y<0)
   {
     arm_negate_q15(&y,&y,1);
     sign=1-sign;
   }

   if (x < 0)
   {
      sign=1 - sign;
      arm_negate_q15(&x,&x,1);
   }

   if (y > x)
   {
    q15_t ratio;
    int16_t shift;

    arm_divide_q15(x,y,&ratio,&shift);

    arm_shift_q15(&ratio,shift,&ratio,1);
   
    res = PIHALFQ13 - arm_atan_limited_q15(ratio);
      
   }
   else
   {
    q15_t ratio;
    int16_t shift;

    arm_divide_q15(y,x,&ratio,&shift);

    arm_shift_q15(&ratio,shift,&ratio,1);

    res = arm_atan_limited_q15(ratio);

   }


   if (sign)
   {
     arm_negate_q15(&res,&res,1);
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
  @param[out]  result  Result in Q2.13
  @return  error status.
 
  @par         Compute the Arc tangent of y/x:
                   The sign of y and x are used to determine the right quadrant
                   and compute the right angle.
*/


arm_status arm_atan2_q15(q15_t y,q15_t x,q15_t *result)
{
    if (x > 0)
    {
        *result=arm_atan_q15(y,x);
        return(ARM_MATH_SUCCESS);
    }
    if (x < 0)
    {
        if (y > 0)
        {
           *result=arm_atan_q15(y,x) + PIQ13;
        }
        else if (y < 0)
        {
           *result=arm_atan_q15(y,x) - PIQ13;
        }
        else
        {
            if (y<0)
            {
               *result= -PIQ13;
            }
            else
            {
               *result= PIQ13;
            }
        }
        return(ARM_MATH_SUCCESS);
    }
    if (x == 0)
    {
        if (y > 0)
        {
            *result=PIHALFQ13;
            return(ARM_MATH_SUCCESS);
        }
        if (y < 0)
        {
            *result=-PIHALFQ13;
            return(ARM_MATH_SUCCESS);
        }
    }
    

    return(ARM_MATH_NANINF);

}

/**
  @} end of atan2 group
 */
