/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_bilinear_interp_f32.c
 * Description:  Floating-point bilinear interpolation
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
   * @defgroup BilinearInterpolate Bilinear Interpolation
   *
   * Bilinear interpolation is an extension of linear interpolation applied to a two dimensional grid.
   * The underlying function <code>f(x, y)</code> is sampled on a regular grid and the interpolation process
   * determines values between the grid points.
   * Bilinear interpolation is equivalent to two step linear interpolation, first in the x-dimension and then in the y-dimension.
   * Bilinear interpolation is often used in image processing to rescale images.
   * The CMSIS DSP library provides bilinear interpolation functions for Q7, Q15, Q31, and floating-point data types.
   *
   * <b>Algorithm</b>
   * \par
   * The instance structure used by the bilinear interpolation functions describes a two dimensional data table.
   * For floating-point, the instance structure is defined as:
   * <pre>
   *   typedef struct
   *   {
   *     uint16_t numRows;
   *     uint16_t numCols;
   *     float32_t *pData;
   * } arm_bilinear_interp_instance_f32;
   * </pre>
   *
   * \par
   * where <code>numRows</code> specifies the number of rows in the table;
   * <code>numCols</code> specifies the number of columns in the table;
   * and <code>pData</code> points to an array of size <code>numRows*numCols</code> values.
   * The data table <code>pTable</code> is organized in row order and the supplied data values fall on integer indexes.
   * That is, table element (x,y) is located at <code>pTable[x + y*numCols]</code> where x and y are integers.
   *
   * \par
   * Let <code>(x, y)</code> specify the desired interpolation point.  Then define:
   * <pre>
   *     XF = floor(x)
   *     YF = floor(y)
   * </pre>
   * \par
   * The interpolated output point is computed as:
   * <pre>
   *  f(x, y) = f(XF, YF) * (1-(x-XF)) * (1-(y-YF))
   *           + f(XF+1, YF) * (x-XF)*(1-(y-YF))
   *           + f(XF, YF+1) * (1-(x-XF))*(y-YF)
   *           + f(XF+1, YF+1) * (x-XF)*(y-YF)
   * </pre>
   * Note that the coordinates (x, y) contain integer and fractional components.
   * The integer components specify which portion of the table to use while the
   * fractional components control the interpolation processor.
   *
   * \par
   * if (x,y) are outside of the table boundary, Bilinear interpolation returns zero output.
   */


  /**
   * @addtogroup BilinearInterpolate
   * @{
   */


  /**
  * @brief  Floating-point bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate.
  * @param[in]     Y  interpolation coordinate.
  * @return out interpolated value.
  */
  float32_t arm_bilinear_interp_f32(
  const arm_bilinear_interp_instance_f32 * S,
  float32_t X,
  float32_t Y)
  {
    float32_t out;
    float32_t f00, f01, f10, f11;
    float32_t *pData = S->pData;
    int32_t xIndex, yIndex, index;
    float32_t xdiff, ydiff;
    float32_t b1, b2, b3, b4;

    xIndex = (int32_t) X;
    yIndex = (int32_t) Y;

    /* Care taken for table outside boundary */
    /* Returns zero output when values are outside table boundary */
    if (xIndex < 0 || xIndex > (S->numCols - 2) || yIndex < 0 || yIndex > (S->numRows - 2))
    {
      return (0);
    }

    /* Calculation of index for two nearest points in X-direction */
    index = (xIndex ) + (yIndex ) * S->numCols;


    /* Read two nearest points in X-direction */
    f00 = pData[index];
    f01 = pData[index + 1];

    /* Calculation of index for two nearest points in Y-direction */
    index = (xIndex ) + (yIndex+1) * S->numCols;


    /* Read two nearest points in Y-direction */
    f10 = pData[index];
    f11 = pData[index + 1];

    /* Calculation of intermediate values */
    b1 = f00;
    b2 = f01 - f00;
    b3 = f10 - f00;
    b4 = f00 - f01 - f10 + f11;

    /* Calculation of fractional part in X */
    xdiff = X - xIndex;

    /* Calculation of fractional part in Y */
    ydiff = Y - yIndex;

    /* Calculation of bi-linear interpolated output */
    out = b1 + b2 * xdiff + b3 * ydiff + b4 * xdiff * ydiff;

    /* return to application */
    return (out);
  }

  /**
   * @} end of BilinearInterpolate group
   */

