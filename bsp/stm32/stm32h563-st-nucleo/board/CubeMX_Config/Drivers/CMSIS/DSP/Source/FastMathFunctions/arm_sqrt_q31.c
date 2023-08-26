/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_sqrt_q31.c
 * Description:  Q31 square root function
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

#include "dsp/fast_math_functions.h"
#include "arm_common_tables.h"

/**
  @ingroup groupFastMath
 */

/**
  @addtogroup SQRT
  @{
 */

/**
  @brief         Q31 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x00000000 to 0x7FFFFFFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref ARM_MATH_SUCCESS        : input value is positive
                   - \ref ARM_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
#define Q28QUARTER 0x20000000 

arm_status arm_sqrt_q31(
  q31_t in,
  q31_t * pOut)
{
  q31_t number, var1, signBits1 ,temp;
 
  number = in;

  /* If the input is a positive number then compute the signBits. */
  if (number > 0)
  {
    signBits1 = __CLZ(number) - 1;

    /* Shift by the number of signBits1 */
    if ((signBits1 % 2) == 0)
    {
      number = number << signBits1;
    }
    else
    {
      number = number << (signBits1 - 1);
    }

    /* Start value for 1/sqrt(x) for the Newton iteration */
    var1 = sqrt_initial_lut_q31[(number>> 26) - (Q28QUARTER >> 26)];

    /* 0.5 var1 * (3 - number * var1 * var1) */

    /* 1st iteration */

    temp = ((q63_t) var1 * var1) >> 28;
    temp = ((q63_t) number * temp) >> 31;
    temp = 0x30000000 - temp; 
    var1 = ((q63_t) var1 * temp) >> 29;

    
    /* 2nd iteration */
    temp = ((q63_t) var1 * var1) >> 28;
    temp = ((q63_t) number * temp) >> 31;
    temp = 0x30000000 - temp; 
    var1 = ((q63_t) var1 * temp) >> 29;

    /* 3nd iteration */
    temp = ((q63_t) var1 * var1) >> 28;
    temp = ((q63_t) number * temp) >> 31;
    temp = 0x30000000 - temp; 
    var1 = ((q63_t) var1 * temp) >> 29;

    /* Multiply the inverse square root with the original value */
    var1 = ((q31_t) (((q63_t) number * var1) >> 28));

    /* Shift the output down accordingly */
    if ((signBits1 % 2) == 0)
    {
      var1 = var1 >> (signBits1 / 2);
    }
    else
    {
      var1 = var1 >> ((signBits1 - 1) / 2);
    }
    *pOut = var1;

    return (ARM_MATH_SUCCESS);
  }
  /* If the number is a negative number then store zero as its square root value */
  else
  {
    *pOut = 0;

    return (ARM_MATH_ARGUMENT_ERROR);
  }
}

/**
  @} end of SQRT group
 */
