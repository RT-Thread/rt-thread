/******************************************************************************
 * @file     interpolation_functions.h
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

 
#ifndef _INTERPOLATION_FUNCTIONS_H_
#define _INTERPOLATION_FUNCTIONS_H_

#include "arm_math_types.h"
#include "arm_math_memory.h"

#include "dsp/none.h"
#include "dsp/utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif


/**
 * @defgroup groupInterpolation Interpolation Functions
 * These functions perform 1- and 2-dimensional interpolation of data.
 * Linear interpolation is used for 1-dimensional data and
 * bilinear interpolation is used for 2-dimensional data.
 */


  /**
   * @brief Instance structure for the floating-point Linear Interpolate function.
   */
  typedef struct
  {
          uint32_t nValues;           /**< nValues */
          float32_t x1;               /**< x1 */
          float32_t xSpacing;         /**< xSpacing */
          float32_t *pYData;          /**< pointer to the table of Y values */
  } arm_linear_interp_instance_f32;

  /**
   * @brief Instance structure for the floating-point bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          float32_t *pData;   /**< points to the data table. */
  } arm_bilinear_interp_instance_f32;

   /**
   * @brief Instance structure for the Q31 bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          q31_t *pData;       /**< points to the data table. */
  } arm_bilinear_interp_instance_q31;

   /**
   * @brief Instance structure for the Q15 bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          q15_t *pData;       /**< points to the data table. */
  } arm_bilinear_interp_instance_q15;

   /**
   * @brief Instance structure for the Q15 bilinear interpolation function.
   */
  typedef struct
  {
          uint16_t numRows;   /**< number of rows in the data table. */
          uint16_t numCols;   /**< number of columns in the data table. */
          q7_t *pData;        /**< points to the data table. */
  } arm_bilinear_interp_instance_q7;


  /**
   * @brief Struct for specifying cubic spline type
   */
  typedef enum
  {
    ARM_SPLINE_NATURAL = 0,           /**< Natural spline */
    ARM_SPLINE_PARABOLIC_RUNOUT = 1   /**< Parabolic runout spline */
  } arm_spline_type;

  /**
   * @brief Instance structure for the floating-point cubic spline interpolation.
   */
  typedef struct
  {
    arm_spline_type type;      /**< Type (boundary conditions) */
    const float32_t * x;       /**< x values */
    const float32_t * y;       /**< y values */
    uint32_t n_x;              /**< Number of known data points */
    float32_t * coeffs;        /**< Coefficients buffer (b,c, and d) */
  } arm_spline_instance_f32;




  /**
   * @ingroup groupInterpolation
   */

  /**
   * @addtogroup SplineInterpolate
   * @{
   */

  
  /**
   * @brief Processing function for the floating-point cubic spline interpolation.
   * @param[in]  S          points to an instance of the floating-point spline structure.
   * @param[in]  xq         points to the x values ot the interpolated data points.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples of output data.
   */
  void arm_spline_f32(
        arm_spline_instance_f32 * S, 
  const float32_t * xq,
        float32_t * pDst,
        uint32_t blockSize);

  /**
   * @brief Initialization function for the floating-point cubic spline interpolation.
   * @param[in,out] S        points to an instance of the floating-point spline structure.
   * @param[in]     type     type of cubic spline interpolation (boundary conditions)
   * @param[in]     x        points to the x values of the known data points.
   * @param[in]     y        points to the y values of the known data points.
   * @param[in]     n        number of known data points.
   * @param[in]     coeffs   coefficients array for b, c, and d
   * @param[in]     tempBuffer   buffer array for internal computations
   */
  void arm_spline_init_f32(
          arm_spline_instance_f32 * S,
          arm_spline_type type,
    const float32_t * x,
    const float32_t * y,
          uint32_t n, 
          float32_t * coeffs,
          float32_t * tempBuffer);


  /**
   * @} end of SplineInterpolate group
   */


  
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
  float32_t arm_linear_interp_f32(
  arm_linear_interp_instance_f32 * S,
  float32_t x);

   /**
   *
   * @brief  Process function for the Q31 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q31 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   *
   */
  q31_t arm_linear_interp_q31(
  const q31_t * pYData,
  q31_t x,
  uint32_t nValues);

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
  uint32_t nValues);

  /**
   *
   * @brief  Process function for the Q7 Linear Interpolation Function.
   * @param[in] pYData   pointer to Q7 Linear Interpolation table
   * @param[in] x        input sample to process
   * @param[in] nValues  number of table values
   * @return y processed output sample.
   *
   * \par
   * Input sample <code>x</code> is in 12.20 format which contains 12 bits for table index and 20 bits for fractional part.
   * This function can support maximum of table size 2^12.
   */
q7_t arm_linear_interp_q7(
  const q7_t * pYData,
  q31_t x,
  uint32_t nValues);

  /**
   * @} end of LinearInterpolate group
   */

  


  /**
   * @ingroup groupInterpolation
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
  float32_t Y);

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
  q31_t Y);


  /**
  * @brief  Q15 bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate in 12.20 format.
  * @param[in]     Y  interpolation coordinate in 12.20 format.
  * @return out interpolated value.
  */
  q15_t arm_bilinear_interp_q15(
  arm_bilinear_interp_instance_q15 * S,
  q31_t X,
  q31_t Y);

  /**
  * @brief  Q7 bilinear interpolation.
  * @param[in,out] S  points to an instance of the interpolation structure.
  * @param[in]     X  interpolation coordinate in 12.20 format.
  * @param[in]     Y  interpolation coordinate in 12.20 format.
  * @return out interpolated value.
  */
  q7_t arm_bilinear_interp_q7(
  arm_bilinear_interp_instance_q7 * S,
  q31_t X,
  q31_t Y);
  /**
   * @} end of BilinearInterpolate group
   */



#ifdef   __cplusplus
}
#endif

#endif /* ifndef _INTERPOLATION_FUNCTIONS_H_ */
