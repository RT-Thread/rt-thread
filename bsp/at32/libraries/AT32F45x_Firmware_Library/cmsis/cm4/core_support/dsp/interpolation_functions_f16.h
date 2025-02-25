/******************************************************************************
 * @file     interpolation_functions_f16.h
 * @brief    Public header file for CMSIS DSP Library
 * @version  V1.10.0
 * @date     08 July 2021
 * Target Processor: Cortex-M and Cortex-A cores
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


#ifndef _INTERPOLATION_FUNCTIONS_F16_H_
#define _INTERPOLATION_FUNCTIONS_F16_H_

#include "arm_math_types_f16.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if defined(ARM_FLOAT16_SUPPORTED)

typedef struct
{
    uint32_t  nValues;        /**< nValues */
    float16_t x1;             /**< x1 */
    float16_t xSpacing;       /**< xSpacing */
    float16_t *pYData;        /**< pointer to the table of Y values */
} arm_linear_interp_instance_f16;

/**
 * @brief Instance structure for the floating-point bilinear interpolation function.
 */
typedef struct
{
    uint16_t  numRows;/**< number of rows in the data table. */
    uint16_t  numCols;/**< number of columns in the data table. */
    float16_t *pData; /**< points to the data table. */
} arm_bilinear_interp_instance_f16;

  /**
   * @addtogroup LinearInterpolate
   * @{
   */

    /**
   * @brief  Process function for the floating-point Linear Interpolation Function.
   * @param[in,out] S  is an instance of the floating-point Linear Interpolation structure
   * @param[in]     x  input sample to process
   * @return y processed output sample.
   *
   */
  float16_t arm_linear_interp_f16(
  arm_linear_interp_instance_f16 * S,
  float16_t x);

    /**
   * @} end of LinearInterpolate group
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
  float16_t arm_bilinear_interp_f16(
  const arm_bilinear_interp_instance_f16 * S,
  float16_t X,
  float16_t Y);


  /**
   * @} end of BilinearInterpolate group
   */
#endif /*defined(ARM_FLOAT16_SUPPORTED)*/
#ifdef   __cplusplus
}
#endif

#endif /* ifndef _INTERPOLATION_FUNCTIONS_F16_H_ */
