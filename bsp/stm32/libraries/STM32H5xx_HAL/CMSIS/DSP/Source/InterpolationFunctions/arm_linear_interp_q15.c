/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_linear_interp_q15.c
 * Description:  Q15 linear interpolation
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

#include "dsp/interpolation_functions.h"

/**
  @ingroup groupInterpolation
 */

/**
   * @addtogroup LinearInterpolate
   * @{
   */

  /**
   *
   * @brief  Process function for the Q15 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q15 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   *
   */
  q15_t arm_linear_interp_q15(
  const q15_t * pYData,
  q31_t x,
  uint32_t nValues)
  {
    q63_t y;                                     /* output */
    q15_t y0, y1;                                /* Nearest output values */
    q31_t fract;                                 /* fractional part */
    int32_t index;                               /* Index to read nearest output values */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    index = ((x & (int32_t)0xFFF00000) >> 20);

    if (index >= (int32_t)(nValues - 1))
    {
      return (pYData[nValues - 1]);
    }
    else if (index < 0)
    {
      return (pYData[0]);
    }
    else
    {
      /* 20 bits for the fractional part */
      /* fract is in 12.20 format */
      fract = (x & 0x000FFFFF);

      /* Read two nearest output values from the index */
      y0 = pYData[index];
      y1 = pYData[index + 1];

      /* Calculation of y0 * (1-fract) and y is in 13.35 format */
      y = ((q63_t) y0 * (0xFFFFF - fract));

      /* Calculation of (y0 * (1-fract) + y1 * fract) and y is in 13.35 format */
      y += ((q63_t) y1 * (fract));

      /* convert y to 1.15 format */
      return (q15_t) (y >> 20);
    }
  }


  /**
   * @} end of LinearInterpolate group
   */

