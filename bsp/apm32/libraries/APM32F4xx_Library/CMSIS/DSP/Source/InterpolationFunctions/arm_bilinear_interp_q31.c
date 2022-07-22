/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_linear_interp_q31.c
 * Description:  Q31 linear interpolation
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
   * @addtogroup BilinearInterpolate
   * @{
   */

 /**
  * @brief  Q31 bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate in 12.20 format.
  * @param[in]     Y  interpolation coordinate in 12.20 format.
  * @return out interpolated value.
  */
  q31_t arm_bilinear_interp_q31(
  arm_bilinear_interp_instance_q31 * S,
  q31_t X,
  q31_t Y)
  {
    q31_t out;                                   /* Temporary output */
    q31_t acc = 0;                               /* output */
    q31_t xfract, yfract;                        /* X, Y fractional parts */
    q31_t x1, x2, y1, y2;                        /* Nearest output values */
    int32_t rI, cI;                              /* Row and column indices */
    q31_t *pYData = S->pData;                    /* pointer to output table values */
    uint32_t nCols = S->numCols;                 /* num of rows */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    rI = ((X & (q31_t)0xFFF00000) >> 20);

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    cI = ((Y & (q31_t)0xFFF00000) >> 20);

    /* Care taken for table outside boundary */
    /* Returns zero output when values are outside table boundary */
    if (rI < 0 || rI > (S->numCols - 2) || cI < 0 || cI > (S->numRows - 2))
    {
      return (0);
    }

    /* 20 bits for the fractional part */
    /* shift left xfract by 11 to keep 1.31 format */
    xfract = (X & 0x000FFFFF) << 11U;

    /* Read two nearest output values from the index */
    x1 = pYData[(rI) + (int32_t)nCols * (cI)    ];
    x2 = pYData[(rI) + (int32_t)nCols * (cI) + 1];

    /* 20 bits for the fractional part */
    /* shift left yfract by 11 to keep 1.31 format */
    yfract = (Y & 0x000FFFFF) << 11U;

    /* Read two nearest output values from the index */
    y1 = pYData[(rI) + (int32_t)nCols * (cI + 1)    ];
    y2 = pYData[(rI) + (int32_t)nCols * (cI + 1) + 1];

    /* Calculation of x1 * (1-xfract ) * (1-yfract) and acc is in 3.29(q29) format */
    out = ((q31_t) (((q63_t) x1  * (0x7FFFFFFF - xfract)) >> 32));
    acc = ((q31_t) (((q63_t) out * (0x7FFFFFFF - yfract)) >> 32));

    /* x2 * (xfract) * (1-yfract)  in 3.29(q29) and adding to acc */
    out = ((q31_t) ((q63_t) x2 * (0x7FFFFFFF - yfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (xfract) >> 32));

    /* y1 * (1 - xfract) * (yfract)  in 3.29(q29) and adding to acc */
    out = ((q31_t) ((q63_t) y1 * (0x7FFFFFFF - xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));

    /* y2 * (xfract) * (yfract)  in 3.29(q29) and adding to acc */
    out = ((q31_t) ((q63_t) y2 * (xfract) >> 32));
    acc += ((q31_t) ((q63_t) out * (yfract) >> 32));

    /* Convert acc to 1.31(q31) format */
    return ((q31_t)(acc << 2));
  }



  /**
   * @} end of BilinearInterpolate group
   */

