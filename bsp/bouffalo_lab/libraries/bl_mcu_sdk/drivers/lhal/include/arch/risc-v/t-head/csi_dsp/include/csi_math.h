/*
 * Copyright (C) 2016-2020 T-head Limited. All rights reserved.
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

/******************************************************************************
 * @file     csi_math.h
 * @brief    Some common define
 * @version  V1.0
 * @date     Feb. 2020
 ******************************************************************************/


#ifndef _CSI_MATH_H
#define _CSI_MATH_H

#ifdef   __cplusplus
extern "C"
{
#endif


#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <unistd.h>
#include "csi_instance.h"


/**
 * @brief Processing function for the Q7 FIR filter.
 * @param[in]  S          points to an instance of the Q7 FIR filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_q7(
    const csi_fir_instance_q7 * S,
    const q7_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the Q7 FIR filter.
 * @param[in,out] S          points to an instance of the Q7 FIR structure.
 * @param[in]     numTaps    Number of filter coefficients in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of samples that are processed.
 */
void csi_fir_init_q7(
    csi_fir_instance_q7 * S,
    uint16_t numTaps,
    const q7_t * pCoeffs,
    q7_t * pState,
    uint32_t blockSize);

/**
 * @brief Processing function for the Q15 FIR filter.
 * @param[in]  S          points to an instance of the Q15 FIR structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_q15(
    const csi_fir_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);

/**
 * @brief Processing function for the fast Q15 FIR filter (fast version).
 * @param[in]  S          points to an instance of the Q15 FIR filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_fast_q15(
    const csi_fir_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the Q15 FIR filter.
 * @param[in,out] S          points to an instance of the Q15 FIR filter structure.
 * @param[in]     numTaps    Number of filter coefficients in the filter. Must be even and greater than or equal to 4.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of samples that are processed at a time.
 * @return     The function returns either
 * <code>CSI_MATH_SUCCESS</code> if initialization was successful or
 * <code>CSI_MATH_ARGUMENT_ERROR</code> if <code>numTaps</code> is not a supported value.
 */
csi_status csi_fir_init_q15(
    csi_fir_instance_q15 * S,
    uint16_t numTaps,
    const q15_t * pCoeffs,
    q15_t * pState,
    uint32_t blockSize);

/**
 * @brief Processing function for the Q31 FIR filter.
 * @param[in]  S          points to an instance of the Q31 FIR filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_q31(
    const csi_fir_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);

/**
 * @brief Processing function for the fast Q31 FIR filter (fast version).
 * @param[in]  S          points to an instance of the Q31 FIR filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_fast_q31(
    const csi_fir_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the Q31 FIR filter.
 * @param[in,out] S          points to an instance of the Q31 FIR structure.
 * @param[in]     numTaps    Number of filter coefficients in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of samples that are processed at a time.
 */
void csi_fir_init_q31(
    csi_fir_instance_q31 * S,
    uint16_t numTaps,
    const q31_t * pCoeffs,
    q31_t * pState,
    uint32_t blockSize);

/**
 * @brief Processing function for the floating-point FIR filter.
 * @param[in]  S          points to an instance of the floating-point FIR structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_f32(
    const csi_fir_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the floating-point FIR filter.
 * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
 * @param[in]     numTaps    Number of filter coefficients in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of samples that are processed at a time.
 */
void csi_fir_init_f32(
    csi_fir_instance_f32 * S,
    uint16_t numTaps,
    const float32_t * pCoeffs,
    float32_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q15 Biquad cascade filter.
 * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df1_q15(
    const csi_biquad_casd_df1_inst_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the Q15 Biquad cascade filter.
 * @param[in,out] S          points to an instance of the Q15 Biquad cascade structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
 */
void csi_biquad_cascade_df1_init_q15(
    csi_biquad_casd_df1_inst_q15 * S,
    uint8_t numStages,
    const q15_t * pCoeffs,
    q15_t * pState,
    int8_t postShift);

/**
 * @brief Fast but less precise processing function for the Q15 Biquad cascade filter for Cortex-M3 and Cortex-M4.
 * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df1_fast_q15(
    const csi_biquad_casd_df1_inst_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);

/**
 * @brief Processing function for the Q31 Biquad cascade filter
 * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df1_q31(
    const csi_biquad_casd_df1_inst_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);

/**
 * @brief Fast but less precise processing function for the Q31 Biquad cascade filter for Cortex-M3 and Cortex-M4.
 * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df1_fast_q31(
    const csi_biquad_casd_df1_inst_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the Q31 Biquad cascade filter.
 * @param[in,out] S          points to an instance of the Q31 Biquad cascade structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
 */
void csi_biquad_cascade_df1_init_q31(
    csi_biquad_casd_df1_inst_q31 * S,
    uint8_t numStages,
    const q31_t * pCoeffs,
    q31_t * pState,
    int8_t postShift);

/**
 * @brief Processing function for the floating-point Biquad cascade filter.
 * @param[in]  S          points to an instance of the floating-point Biquad cascade structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df1_f32(
    const csi_biquad_casd_df1_inst_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);

/**
 * @brief  Initialization function for the floating-point Biquad cascade filter.
 * @param[in,out] S          points to an instance of the floating-point Biquad cascade structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 */
void csi_biquad_cascade_df1_init_f32(
    csi_biquad_casd_df1_inst_f32 * S,
    uint8_t numStages,
    const float32_t * pCoeffs,
    float32_t * pState);

/**
 * @brief Floating-point matrix addition.
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_add_f32(
    const csi_matrix_instance_f32 * pSrcA,
    const csi_matrix_instance_f32 * pSrcB,
    csi_matrix_instance_f32 * pDst);

/**
 * @brief Q15 matrix addition.
 * @param[in]   pSrcA  points to the first input matrix structure
 * @param[in]   pSrcB  points to the second input matrix structure
 * @param[out]  pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_add_q15(
    const csi_matrix_instance_q15 * pSrcA,
    const csi_matrix_instance_q15 * pSrcB,
    csi_matrix_instance_q15 * pDst);

/**
 * @brief Q31 matrix addition.
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_add_q31(
    const csi_matrix_instance_q31 * pSrcA,
    const csi_matrix_instance_q31 * pSrcB,
    csi_matrix_instance_q31 * pDst);

/**
 * @brief Floating-point, complex, matrix multiplication.
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_cmplx_mult_f32(
    const csi_matrix_instance_f32 * pSrcA,
    const csi_matrix_instance_f32 * pSrcB,
    csi_matrix_instance_f32 * pDst);

/**
 * @brief Q15, complex,  matrix multiplication.
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_cmplx_mult_q15(
    const csi_matrix_instance_q15 * pSrcA,
    const csi_matrix_instance_q15 * pSrcB,
    csi_matrix_instance_q15 * pDst);

void csi_mult_q15xq31_sht(
    q15_t * pSrcA,
    q31_t * pSrcB,
    uint32_t shiftValue,
    uint32_t blockSize);

/**
 * @brief Q31, complex, matrix multiplication.
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_cmplx_mult_q31(
    const csi_matrix_instance_q31 * pSrcA,
    const csi_matrix_instance_q31 * pSrcB,
    csi_matrix_instance_q31 * pDst);

/**
 * @brief Floating-point matrix transpose.
 * @param[in]  pSrc  points to the input matrix
 * @param[out] pDst  points to the output matrix
 * @return    The function returns either  <code>CSI_MATH_SIZE_MISMATCH</code>
 * or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_trans_f32(
    const csi_matrix_instance_f32 * pSrc,
    csi_matrix_instance_f32 * pDst);

/**
 * @brief Q15 matrix transpose.
 * @param[in]  pSrc  points to the input matrix
 * @param[out] pDst  points to the output matrix
 * @return    The function returns either  <code>CSI_MATH_SIZE_MISMATCH</code>
 * or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_trans_q15(
    const csi_matrix_instance_q15 * pSrc,
    csi_matrix_instance_q15 * pDst);

/**
 * @brief Q31 matrix transpose.
 * @param[in]  pSrc  points to the input matrix
 * @param[out] pDst  points to the output matrix
 * @return    The function returns either  <code>CSI_MATH_SIZE_MISMATCH</code>
 * or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_trans_q31(
    const csi_matrix_instance_q31 * pSrc,
    csi_matrix_instance_q31 * pDst);

/**
 * @brief Floating-point matrix multiplication
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_mult_f32(
    const csi_matrix_instance_f32 * pSrcA,
    const csi_matrix_instance_f32 * pSrcB,
    csi_matrix_instance_f32 * pDst);

/**
 * @brief Q15 matrix multiplication
 * @param[in]  pSrcA   points to the first input matrix structure
 * @param[in]  pSrcB   points to the second input matrix structure
 * @param[out] pDst    points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_mult_q15(
    const csi_matrix_instance_q15 * pSrcA,
    const csi_matrix_instance_q15 * pSrcB,
    csi_matrix_instance_q15 * pDst);

  csi_status csi_mat_mult_trans_q15(
  const csi_matrix_instance_q15 * pSrcA,
  const csi_matrix_instance_q15 * pSrcB,
  csi_matrix_instance_q15 * pDst);

/**
 * @brief Q15 matrix multiplication (fast variant) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA   points to the first input matrix structure
 * @param[in]  pSrcB   points to the second input matrix structure
 * @param[out] pDst    points to output matrix structure
 * @param[in]  pState  points to the array for storing intermediate results
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_mult_fast_q15(
    const csi_matrix_instance_q15 * pSrcA,
    const csi_matrix_instance_q15 * pSrcB,
    csi_matrix_instance_q15 * pDst);

/**
 * @brief Q31 matrix multiplication
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_mult_q31(
    const csi_matrix_instance_q31 * pSrcA,
    const csi_matrix_instance_q31 * pSrcB,
    csi_matrix_instance_q31 * pDst);

csi_status csi_mat_mult_trans_q31(
  const csi_matrix_instance_q31 * pSrcA,
  const csi_matrix_instance_q31 * pSrcB,
  csi_matrix_instance_q31 * pDst);

/**
 * @brief Q31 matrix multiplication (fast variant) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_mult_fast_q31(
    const csi_matrix_instance_q31 * pSrcA,
    const csi_matrix_instance_q31 * pSrcB,
    csi_matrix_instance_q31 * pDst);

/**
 * @brief Floating-point matrix subtraction
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_sub_f32(
    const csi_matrix_instance_f32 * pSrcA,
    const csi_matrix_instance_f32 * pSrcB,
    csi_matrix_instance_f32 * pDst);

/**
 * @brief Q15 matrix subtraction
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_sub_q15(
    const csi_matrix_instance_q15 * pSrcA,
    const csi_matrix_instance_q15 * pSrcB,
    csi_matrix_instance_q15 * pDst);

/**
 * @brief Q31 matrix subtraction
 * @param[in]  pSrcA  points to the first input matrix structure
 * @param[in]  pSrcB  points to the second input matrix structure
 * @param[out] pDst   points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_sub_q31(
    const csi_matrix_instance_q31 * pSrcA,
    const csi_matrix_instance_q31 * pSrcB,
    csi_matrix_instance_q31 * pDst);

void csi_sum_q15(
    q15_t * pSrcA,
    q63_t * pDst,
    uint32_t blockSize);

/**
 * @brief Floating-point matrix scaling.
 * @param[in]  pSrc   points to the input matrix
 * @param[in]  scale  scale factor
 * @param[out] pDst   points to the output matrix
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_scale_f32(
    const csi_matrix_instance_f32 * pSrc,
    float32_t scale,
    csi_matrix_instance_f32 * pDst);

/**
 * @brief Q15 matrix scaling.
 * @param[in]  pSrc        points to input matrix
 * @param[in]  scaleFract  fractional portion of the scale factor
 * @param[in]  shift       number of bits to shift the result by
 * @param[out] pDst        points to output matrix
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_scale_q15(
    const csi_matrix_instance_q15 * pSrc,
    q15_t scaleFract,
    int32_t shift,
    csi_matrix_instance_q15 * pDst);

/**
 * @brief Q31 matrix scaling.
 * @param[in]  pSrc        points to input matrix
 * @param[in]  scaleFract  fractional portion of the scale factor
 * @param[in]  shift       number of bits to shift the result by
 * @param[out] pDst        points to output matrix structure
 * @return     The function returns either
 * <code>CSI_MATH_SIZE_MISMATCH</code> or <code>CSI_MATH_SUCCESS</code> based on the outcome of size checking.
 */
csi_status csi_mat_scale_q31(
    const csi_matrix_instance_q31 * pSrc,
    q31_t scaleFract,
    int32_t shift,
    csi_matrix_instance_q31 * pDst);

/**
 * @brief  Q31 matrix initialization.
 * @param[in,out] S         points to an instance of the floating-point matrix structure.
 * @param[in]     nRows     number of rows in the matrix.
 * @param[in]     nColumns  number of columns in the matrix.
 * @param[in]     pData     points to the matrix data array.
 */
void csi_mat_init_q31(
    csi_matrix_instance_q31 * S,
    uint16_t nRows,
    uint16_t nColumns,
    q31_t * pData);

/**
 * @brief  Q15 matrix initialization.
 * @param[in,out] S         points to an instance of the floating-point matrix structure.
 * @param[in]     nRows     number of rows in the matrix.
 * @param[in]     nColumns  number of columns in the matrix.
 * @param[in]     pData     points to the matrix data array.
 */
void csi_mat_init_q15(
    csi_matrix_instance_q15 * S,
    uint16_t nRows,
    uint16_t nColumns,
    q15_t * pData);

/**
 * @brief  Floating-point matrix initialization.
 * @param[in,out] S         points to an instance of the floating-point matrix structure.
 * @param[in]     nRows     number of rows in the matrix.
 * @param[in]     nColumns  number of columns in the matrix.
 * @param[in]     pData     points to the matrix data array.
 */
void csi_mat_init_f32(
    csi_matrix_instance_f32 * S,
    uint16_t nRows,
    uint16_t nColumns,
    float32_t * pData);


/**
 * @brief  Initialization function for the floating-point PID Control.
 * @param[in,out] S               points to an instance of the PID structure.
 * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
 */
void csi_pid_init_f32(
    csi_pid_instance_f32 * S,
    int32_t resetStateFlag);


/**
 * @brief  Reset function for the floating-point PID Control.
 * @param[in,out] S  is an instance of the floating-point PID Control structure
 */
void csi_pid_reset_f32(
    csi_pid_instance_f32 * S);


/**
 * @brief  Initialization function for the Q31 PID Control.
 * @param[in,out] S               points to an instance of the Q15 PID structure.
 * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
 */
void csi_pid_init_q31(
    csi_pid_instance_q31 * S,
    int32_t resetStateFlag);


/**
 * @brief  Reset function for the Q31 PID Control.
 * @param[in,out] S   points to an instance of the Q31 PID Control structure
 */

void csi_pid_reset_q31(
    csi_pid_instance_q31 * S);


/**
 * @brief  Initialization function for the Q15 PID Control.
 * @param[in,out] S               points to an instance of the Q15 PID structure.
 * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
 */
void csi_pid_init_q15(
    csi_pid_instance_q15 * S,
    int32_t resetStateFlag);


/**
 * @brief  Reset function for the Q15 PID Control.
 * @param[in,out] S  points to an instance of the q15 PID Control structure
 */
void csi_pid_reset_q15(
    csi_pid_instance_q15 * S);

/**
 * @brief Q7 vector multiplication.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_mult_q7(
    const q7_t * pSrcA,
    const q7_t * pSrcB,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q15 vector multiplication.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_mult_q15(
    const q15_t * pSrcA,
    const q15_t * pSrcB,
    q15_t * pDst,
    uint32_t blockSize);

void csi_mult_rnd_q15(
    q15_t * pSrcA,
    q15_t * pSrcB,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q31 vector multiplication.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_mult_q31(
    const q31_t * pSrcA,
    const q31_t * pSrcB,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Floating-point vector multiplication.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_mult_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    float32_t * pDst,
    uint32_t blockSize);


/* Deprecated */
csi_status csi_cfft_radix2_init_q15(
    csi_cfft_radix2_instance_q15 * S,
    uint16_t fftLen,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

/* Deprecated */
void csi_cfft_radix2_q15(
    const csi_cfft_radix2_instance_q15 * S,
    q15_t * pSrc);


/* Deprecated */
csi_status csi_cfft_radix4_init_q15(
    csi_cfft_radix4_instance_q15 * S,
    uint16_t fftLen,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

/* Deprecated */
void csi_cfft_radix4_q15(
    const csi_cfft_radix4_instance_q15 * S,
    q15_t * pSrc);

/* Deprecated */
csi_status csi_cfft_radix2_init_q31(
    csi_cfft_radix2_instance_q31 * S,
    uint16_t fftLen,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

/* Deprecated */
void csi_cfft_radix2_q31(
    const csi_cfft_radix2_instance_q31 * S,
    q31_t * pSrc);


/* Deprecated */
void csi_cfft_radix4_q31(
    const csi_cfft_radix4_instance_q31 * S,
    q31_t * pSrc);

/* Deprecated */
csi_status csi_cfft_radix4_init_q31(
    csi_cfft_radix4_instance_q31 * S,
    uint16_t fftLen,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);


/* Deprecated */
csi_status csi_cfft_radix2_init_f32(
    csi_cfft_radix2_instance_f32 * S,
    uint16_t fftLen,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

/* Deprecated */
  void csi_cfft_radix2_f32(
  const csi_cfft_instance_f32 * S,
  float32_t * p1,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag,
  float32_t onebyfftLen);


/* Deprecated */
csi_status csi_cfft_radix4_init_f32(
    csi_cfft_radix4_instance_f32 * S,
    uint16_t fftLen,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

/* Deprecated */
  void csi_cfft_radix4_f32(
  const csi_cfft_instance_f32 * S,
  float32_t * p1,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag,
  float32_t onebyfftLen);

  void csi_cfft_fast_radix4_f32(
  const csi_cfft_instance_f32 * S,
  float32_t * p1,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag,
  float32_t onebyfftLen);


void csi_cfft_q15(
    const csi_cfft_instance_q15 * S,
    q15_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

void csi_cfft_fast_q15(
    const csi_cfft_instance_q15 * S,
    q15_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

void csi_cfft_q31(
    const csi_cfft_instance_q31 * S,
    q31_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

void csi_cfft_fast_q31(
    const csi_cfft_instance_q31 * S,
    q31_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);


void csi_cfft_f32(
    const csi_cfft_instance_f32 * S,
    float32_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);


csi_status csi_rfft_init_q15(
    csi_rfft_instance_q15 * S,
    uint32_t fftLenReal,
    uint32_t ifftFlagR,
    uint32_t bitReverseFlag);

void csi_rfft_q15(
    const csi_rfft_instance_q15 * S,
    q15_t * pSrc,
    q15_t * pDst);

void csi_rfft_fast_q15(
    const csi_rfft_fast_instance_q15 * S,
    q15_t * pSrc,
    q15_t * pDst);


csi_status csi_rfft_init_q31(
    csi_rfft_instance_q31 * S,
    uint32_t fftLenReal,
    uint32_t ifftFlagR,
    uint32_t bitReverseFlag);

void csi_rfft_q31(
    const csi_rfft_instance_q31 * S,
    q31_t * pSrc,
    q31_t * pDst);

void csi_rfft_fast_q31(
  const csi_rfft_fast_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst);


csi_status csi_rfft_init_f32(
    csi_rfft_instance_f32 * S,
    csi_cfft_radix4_instance_f32 * S_CFFT,
    uint32_t fftLenReal,
    uint32_t ifftFlagR,
    uint32_t bitReverseFlag);

void csi_rfft_f32(
    const csi_rfft_instance_f32 * S,
    float32_t * pSrc,
    float32_t * pDst);


csi_status csi_rfft_fast_init_f32 (
    csi_rfft_fast_instance_f32 * S,
    uint16_t fftLen);

csi_status csi_rfft_32_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_64_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_128_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_256_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_512_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_1024_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_2048_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );

csi_status csi_rfft_4096_fast_init_f32 ( csi_rfft_fast_instance_f32 * S );


void csi_rfft_fast_f32(
    csi_rfft_fast_instance_f32 * S,
    float32_t * p, float32_t * pOut,
    uint8_t ifftFlag);


/**
 * @brief  Initialization function for the floating-point DCT4/IDCT4.
 * @param[in,out] S          points to an instance of floating-point DCT4/IDCT4 structure.
 * @param[in]     S_RFFT     points to an instance of floating-point RFFT/RIFFT structure.
 * @param[in]     S_CFFT     points to an instance of floating-point CFFT/CIFFT structure.
 * @param[in]     N          length of the DCT4.
 * @param[in]     Nby2       half of the length of the DCT4.
 * @param[in]     normalize  normalizing factor.
 * @return      csi_status function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_ARGUMENT_ERROR if <code>fftLenReal</code> is not a supported transform length.
 */
csi_status csi_dct4_init_f32(
    csi_dct4_instance_f32 * S,
    csi_rfft_fast_instance_f32 * S_RFFT,
    csi_cfft_radix4_instance_f32 * S_CFFT,
    uint16_t N,
    uint16_t Nby2,
    float32_t normalize);


/**
 * @brief Processing function for the floating-point DCT4/IDCT4.
 * @param[in]     S              points to an instance of the floating-point DCT4/IDCT4 structure.
 * @param[in]     pState         points to state buffer.
 * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
 */
void csi_dct4_f32(
    const csi_dct4_instance_f32 * S,
    float32_t * pState,
    float32_t * pInlineBuffer);



/**
 * @brief  Initialization function for the Q31 DCT4/IDCT4.
 * @param[in,out] S          points to an instance of Q31 DCT4/IDCT4 structure.
 * @param[in]     S_RFFT     points to an instance of Q31 RFFT/RIFFT structure
 * @param[in]     S_CFFT     points to an instance of Q31 CFFT/CIFFT structure
 * @param[in]     N          length of the DCT4.
 * @param[in]     Nby2       half of the length of the DCT4.
 * @param[in]     normalize  normalizing factor.
 * @return      csi_status function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
 */
csi_status csi_dct4_init_q31(
    csi_dct4_instance_q31 * S,
    csi_rfft_instance_q31 * S_RFFT,
    csi_cfft_radix4_instance_q31 * S_CFFT,
    uint16_t N,
    uint16_t Nby2,
    q31_t normalize);


/**
 * @brief Processing function for the Q31 DCT4/IDCT4.
 * @param[in]     S              points to an instance of the Q31 DCT4 structure.
 * @param[in]     pState         points to state buffer.
 * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
 */
void csi_dct4_q31(
    const csi_dct4_instance_q31 * S,
    q31_t * pState,
    q31_t * pInlineBuffer);

void csi_dct4_fast_q31(
    const csi_dct4_fast_instance_q31 * S,
    q31_t * pState,
    q31_t * pInlineBuffer);


/**
 * @brief  Initialization function for the Q15 DCT4/IDCT4.
 * @param[in,out] S          points to an instance of Q15 DCT4/IDCT4 structure.
 * @param[in]     S_RFFT     points to an instance of Q15 RFFT/RIFFT structure.
 * @param[in]     S_CFFT     points to an instance of Q15 CFFT/CIFFT structure.
 * @param[in]     N          length of the DCT4.
 * @param[in]     Nby2       half of the length of the DCT4.
 * @param[in]     normalize  normalizing factor.
 * @return      csi_status function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
 */
csi_status csi_dct4_init_q15(
    csi_dct4_instance_q15 * S,
    csi_rfft_instance_q15 * S_RFFT,
    csi_cfft_radix4_instance_q15 * S_CFFT,
    uint16_t N,
    uint16_t Nby2,
    q15_t normalize);


/**
 * @brief Processing function for the Q15 DCT4/IDCT4.
 * @param[in]     S              points to an instance of the Q15 DCT4 structure.
 * @param[in]     pState         points to state buffer.
 * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
 */
void csi_dct4_q15(
    const csi_dct4_instance_q15 * S,
    q15_t * pState,
    q15_t * pInlineBuffer);

void csi_dct4_fast_q15(
    const csi_dct4_fast_instance_q15 * S,
    q15_t * pState,
    q15_t * pInlineBuffer);


/**
 * @brief Floating-point vector addition.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_add_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q7 vector addition.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_add_q7(
    const q7_t * pSrcA,
    const q7_t * pSrcB,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q15 vector addition.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_add_q15(
    const q15_t * pSrcA,
    const q15_t * pSrcB,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q31 vector addition.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_add_q31(
    const q31_t * pSrcA,
    const q31_t * pSrcB,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Floating-point vector subtraction.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_sub_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q7 vector subtraction.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_sub_q7(
    const q7_t * pSrcA,
    const q7_t * pSrcB,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q15 vector subtraction.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_sub_q15(
    const q15_t * pSrcA,
    const q15_t * pSrcB,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q31 vector subtraction.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_sub_q31(
    const q31_t * pSrcA,
    const q31_t * pSrcB,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Multiplies a floating-point vector by a scalar.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  scale      scale factor to be applied
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_scale_f32(
    const float32_t * pSrc,
    float32_t scale,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Multiplies a Q7 vector by a scalar.
 * @param[in]  pSrc        points to the input vector
 * @param[in]  scaleFract  fractional portion of the scale value
 * @param[in]  shift       number of bits to shift the result by
 * @param[out] pDst        points to the output vector
 * @param[in]  blockSize   number of samples in the vector
 */
void csi_scale_q7(
    const q7_t * pSrc,
    q7_t scaleFract,
    int8_t shift,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief Multiplies a Q15 vector by a scalar.
 * @param[in]  pSrc        points to the input vector
 * @param[in]  scaleFract  fractional portion of the scale value
 * @param[in]  shift       number of bits to shift the result by
 * @param[out] pDst        points to the output vector
 * @param[in]  blockSize   number of samples in the vector
 */
void csi_scale_q15(
    const q15_t * pSrc,
    q15_t scaleFract,
    int8_t shift,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Multiplies a Q31 vector by a scalar.
 * @param[in]  pSrc        points to the input vector
 * @param[in]  scaleFract  fractional portion of the scale value
 * @param[in]  shift       number of bits to shift the result by
 * @param[out] pDst        points to the output vector
 * @param[in]  blockSize   number of samples in the vector
 */
void csi_scale_q31(
    const q31_t * pSrc,
    q31_t scaleFract,
    int8_t shift,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q7 vector absolute value.
 * @param[in]  pSrc       points to the input buffer
 * @param[out] pDst       points to the output buffer
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_abs_q7(
    const q7_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief Floating-point vector absolute value.
 * @param[in]  pSrc       points to the input buffer
 * @param[out] pDst       points to the output buffer
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_abs_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q15 vector absolute value.
 * @param[in]  pSrc       points to the input buffer
 * @param[out] pDst       points to the output buffer
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_abs_q15(
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Q31 vector absolute value.
 * @param[in]  pSrc       points to the input buffer
 * @param[out] pDst       points to the output buffer
 * @param[in]  blockSize  number of samples in each vector
 */
void csi_abs_q31(
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);

  void csi_abs_max_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);

  void csi_abs_max_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


/**
 * @brief Dot product of floating-point vectors.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[in]  blockSize  number of samples in each vector
 * @param[out] result     output result returned here
 */
void csi_dot_prod_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    uint32_t blockSize,
    float32_t * result);


/**
 * @brief Dot product of Q7 vectors.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[in]  blockSize  number of samples in each vector
 * @param[out] result     output result returned here
 */
void csi_dot_prod_q7(
    const q7_t * pSrcA,
    const q7_t * pSrcB,
    uint32_t blockSize,
    q31_t * result);


/**
 * @brief Dot product of Q15 vectors.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[in]  blockSize  number of samples in each vector
 * @param[out] result     output result returned here
 */
void csi_dot_prod_q15(
    const q15_t * pSrcA,
    const q15_t * pSrcB,
    uint32_t blockSize,
    q63_t * result);


/**
 * @brief Dot product of Q31 vectors.
 * @param[in]  pSrcA      points to the first input vector
 * @param[in]  pSrcB      points to the second input vector
 * @param[in]  blockSize  number of samples in each vector
 * @param[out] result     output result returned here
 */
void csi_dot_prod_q31(
    const q31_t * pSrcA,
    const q31_t * pSrcB,
    uint32_t blockSize,
    q63_t * result);


/**
 * @brief  Shifts the elements of a Q7 vector a specified number of bits.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_shift_q7(
    const q7_t * pSrc,
    int8_t shiftBits,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Shifts the elements of a Q15 vector a specified number of bits.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_shift_q15(
    const q15_t * pSrc,
    int8_t shiftBits,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Shifts the elements of a Q31 vector a specified number of bits.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_shift_q31(
    const q31_t * pSrc,
    int8_t shiftBits,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Adds a constant offset to a floating-point vector.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  offset     is the offset to be added
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_offset_f32(
    const float32_t * pSrc,
    float32_t offset,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Adds a constant offset to a Q7 vector.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  offset     is the offset to be added
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_offset_q7(
    const q7_t * pSrc,
    q7_t offset,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Adds a constant offset to a Q15 vector.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  offset     is the offset to be added
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_offset_q15(
    const q15_t * pSrc,
    q15_t offset,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Adds a constant offset to a Q31 vector.
 * @param[in]  pSrc       points to the input vector
 * @param[in]  offset     is the offset to be added
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_offset_q31(
    const q31_t * pSrc,
    q31_t offset,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Negates the elements of a floating-point vector.
 * @param[in]  pSrc       points to the input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_negate_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Negates the elements of a Q7 vector.
 * @param[in]  pSrc       points to the input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_negate_q7(
    const q7_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Negates the elements of a Q15 vector.
 * @param[in]  pSrc       points to the input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_negate_q15(
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Negates the elements of a Q31 vector.
 * @param[in]  pSrc       points to the input vector
 * @param[out] pDst       points to the output vector
 * @param[in]  blockSize  number of samples in the vector
 */
void csi_negate_q31(
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Copies the elements of a floating-point vector.
 * @param[in]  pSrc       input pointer
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_copy_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Copies the elements of a Q7 vector.
 * @param[in]  pSrc       input pointer
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_copy_q7(
    const q7_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Copies the elements of a Q15 vector.
 * @param[in]  pSrc       input pointer
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_copy_q15(
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Copies the elements of a Q31 vector.
 * @param[in]  pSrc       input pointer
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_copy_q31(
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Fills a constant value into a floating-point vector.
 * @param[in]  value      input value to be filled
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_fill_f32(
    float32_t value,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Fills a constant value into a Q7 vector.
 * @param[in]  value      input value to be filled
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_fill_q7(
    q7_t value,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Fills a constant value into a Q15 vector.
 * @param[in]  value      input value to be filled
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_fill_q15(
    q15_t value,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Fills a constant value into a Q31 vector.
 * @param[in]  value      input value to be filled
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_fill_q31(
    q31_t value,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Convolution of floating-point sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
void csi_conv_f32(
    const float32_t * pSrcA,
    uint32_t srcALen,
    const float32_t * pSrcB,
    uint32_t srcBLen,
    float32_t * pDst);


/**
 * @brief Convolution of Q15 sequences.
 * @param[in]  pSrcA      points to the first input sequence.
 * @param[in]  srcALen    length of the first input sequence.
 * @param[in]  pSrcB      points to the second input sequence.
 * @param[in]  srcBLen    length of the second input sequence.
 * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
 * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
 */
void csi_conv_opt_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
 * @brief Convolution of Q15 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
void csi_conv_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst);


/**
 * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
 */
void csi_conv_fast_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst);


/**
 * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA      points to the first input sequence.
 * @param[in]  srcALen    length of the first input sequence.
 * @param[in]  pSrcB      points to the second input sequence.
 * @param[in]  srcBLen    length of the second input sequence.
 * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
 * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
 */
void csi_conv_fast_opt_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
 * @brief Convolution of Q31 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
 */
void csi_conv_q31(
    const q31_t * pSrcA,
    uint32_t srcALen,
    const q31_t * pSrcB,
    uint32_t srcBLen,
    q31_t * pDst);


/**
 * @brief Convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
 */
void csi_conv_fast_q31(
    const q31_t * pSrcA,
    uint32_t srcALen,
    const q31_t * pSrcB,
    uint32_t srcBLen,
    q31_t * pDst);


/**
* @brief Convolution of Q7 sequences.
* @param[in]  pSrcA      points to the first input sequence.
* @param[in]  srcALen    length of the first input sequence.
* @param[in]  pSrcB      points to the second input sequence.
* @param[in]  srcBLen    length of the second input sequence.
* @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
* @param[in]  pScratch1  points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
* @param[in]  pScratch2  points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
*/
void csi_conv_opt_q7(
    const q7_t * pSrcA,
    uint32_t srcALen,
    const q7_t * pSrcB,
    uint32_t srcBLen,
    q7_t * pDst,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
 * @brief Convolution of Q7 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
 */
void csi_conv_q7(
    const q7_t * pSrcA,
    uint32_t srcALen,
    const q7_t * pSrcB,
    uint32_t srcBLen,
    q7_t * pDst);


/**
 * @brief Partial convolution of floating-point sequences.
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_f32(
    const float32_t * pSrcA,
    uint32_t srcALen,
    const float32_t * pSrcB,
    uint32_t srcBLen,
    float32_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints);


/**
 * @brief Partial convolution of Q15 sequences.
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_opt_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
 * @brief Partial convolution of Q15 sequences.
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints);


/**
 * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_fast_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints);


/**
 * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_fast_opt_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
 * @brief Partial convolution of Q31 sequences.
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_q31(
    const q31_t * pSrcA,
    uint32_t srcALen,
    const q31_t * pSrcB,
    uint32_t srcBLen,
    q31_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints);


/**
 * @brief Partial convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_fast_q31(
    const q31_t * pSrcA,
    uint32_t srcALen,
    const q31_t * pSrcB,
    uint32_t srcBLen,
    q31_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints);


/**
 * @brief Partial convolution of Q7 sequences
 * @param[in]  pSrcA       points to the first input sequence.
 * @param[in]  srcALen     length of the first input sequence.
 * @param[in]  pSrcB       points to the second input sequence.
 * @param[in]  srcBLen     length of the second input sequence.
 * @param[out] pDst        points to the block of output data
 * @param[in]  firstIndex  is the first output sample to start with.
 * @param[in]  numPoints   is the number of output points to be computed.
 * @param[in]  pScratch1   points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 * @param[in]  pScratch2   points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
 * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
 */
csi_status csi_conv_partial_opt_q7(
    const q7_t * pSrcA,
    uint32_t srcALen,
    const q7_t * pSrcB,
    uint32_t srcBLen,
    q7_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
   * @brief Partial convolution of Q7 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either CSI_MATH_SUCCESS if the function completed correctly or CSI_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
csi_status csi_conv_partial_q7(
    const q7_t * pSrcA,
    uint32_t srcALen,
    const q7_t * pSrcB,
    uint32_t srcBLen,
    q7_t * pDst,
    uint32_t firstIndex,
    uint32_t numPoints);



/**
  @brief         Processing function for floating-point FIR decimator.
  @param[in]     S         points to an instance of the floating-point FIR decimator structure
  @param[in]     pSrc      points to the block of input data
  @param[out]    pDst      points to the block of output data
  @param[in]     blockSize number of samples to process
 */
void csi_fir_decimate_f32(
    const csi_fir_decimate_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
  @brief         Initialization function for the floating-point FIR decimator.
  @param[in,out] S          points to an instance of the floating-point FIR decimator structure
  @param[in]     numTaps    number of coefficients in the filter
  @param[in]     M          decimation factor
  @param[in]     pCoeffs    points to the filter coefficients
  @param[in]     pState     points to the state buffer
  @param[in]     blockSize  number of input samples to process per call
  @return        execution status
                   - \ref CSI_MATH_SUCCESS      : Operation successful
                   - \ref CSI_MATH_LENGTH_ERROR : <code>blockSize</code> is not a multiple of <code>M</code>
 */
csi_status csi_fir_decimate_init_f32(
    csi_fir_decimate_instance_f32 * S,
    uint16_t numTaps,
    uint8_t M,
    const float32_t * pCoeffs,
    float32_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q15 FIR decimator.
 * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of input samples to process per call.
 */
void csi_fir_decimate_q15(
    const csi_fir_decimate_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q15 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
 * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of input samples to process per call.
 */
void csi_fir_decimate_fast_q15(
    const csi_fir_decimate_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q15 FIR decimator.
 * @param[in,out] S          points to an instance of the Q15 FIR decimator structure.
 * @param[in]     numTaps    number of coefficients in the filter.
 * @param[in]     M          decimation factor.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of input samples to process per call.
 * @return    The function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_LENGTH_ERROR if
 * <code>blockSize</code> is not a multiple of <code>M</code>.
 */
csi_status csi_fir_decimate_init_q15(
    csi_fir_decimate_instance_q15 * S,
    uint16_t numTaps,
    uint8_t M,
    const q15_t * pCoeffs,
    q15_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q31 FIR decimator.
 * @param[in]  S     points to an instance of the Q31 FIR decimator structure.
 * @param[in]  pSrc  points to the block of input data.
 * @param[out] pDst  points to the block of output data
 * @param[in] blockSize number of input samples to process per call.
 */
void csi_fir_decimate_q31(
    const csi_fir_decimate_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);

/**
 * @brief Processing function for the Q31 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
 * @param[in]  S          points to an instance of the Q31 FIR decimator structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of input samples to process per call.
 */
void csi_fir_decimate_fast_q31(
    const csi_fir_decimate_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q31 FIR decimator.
 * @param[in,out] S          points to an instance of the Q31 FIR decimator structure.
 * @param[in]     numTaps    number of coefficients in the filter.
 * @param[in]     M          decimation factor.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of input samples to process per call.
 * @return    The function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_LENGTH_ERROR if
 * <code>blockSize</code> is not a multiple of <code>M</code>.
 */
csi_status csi_fir_decimate_init_q31(
    csi_fir_decimate_instance_q31 * S,
    uint16_t numTaps,
    uint8_t M,
    const q31_t * pCoeffs,
    q31_t * pState,
    uint32_t blockSize);



/**
 * @brief Processing function for the Q15 FIR interpolator.
 * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of input samples to process per call.
 */
void csi_fir_interpolate_q15(
    const csi_fir_interpolate_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q15 FIR interpolator.
 * @param[in,out] S          points to an instance of the Q15 FIR interpolator structure.
 * @param[in]     L          upsample factor.
 * @param[in]     numTaps    number of filter coefficients in the filter.
 * @param[in]     pCoeffs    points to the filter coefficient buffer.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of input samples to process per call.
 * @return        The function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_LENGTH_ERROR if
 * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
 */
csi_status csi_fir_interpolate_init_q15(
    csi_fir_interpolate_instance_q15 * S,
    uint8_t L,
    uint16_t numTaps,
    const q15_t * pCoeffs,
    q15_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q31 FIR interpolator.
 * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of input samples to process per call.
 */
void csi_fir_interpolate_q31(
    const csi_fir_interpolate_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q31 FIR interpolator.
 * @param[in,out] S          points to an instance of the Q31 FIR interpolator structure.
 * @param[in]     L          upsample factor.
 * @param[in]     numTaps    number of filter coefficients in the filter.
 * @param[in]     pCoeffs    points to the filter coefficient buffer.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of input samples to process per call.
 * @return        The function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_LENGTH_ERROR if
 * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
 */
csi_status csi_fir_interpolate_init_q31(
    csi_fir_interpolate_instance_q31 * S,
    uint8_t L,
    uint16_t numTaps,
    const q31_t * pCoeffs,
    q31_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the floating-point FIR interpolator.
 * @param[in]  S          points to an instance of the floating-point FIR interpolator structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of input samples to process per call.
 */
void csi_fir_interpolate_f32(
    const csi_fir_interpolate_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the floating-point FIR interpolator.
 * @param[in,out] S          points to an instance of the floating-point FIR interpolator structure.
 * @param[in]     L          upsample factor.
 * @param[in]     numTaps    number of filter coefficients in the filter.
 * @param[in]     pCoeffs    points to the filter coefficient buffer.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     blockSize  number of input samples to process per call.
 * @return        The function returns CSI_MATH_SUCCESS if initialization is successful or CSI_MATH_LENGTH_ERROR if
 * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
 */
csi_status csi_fir_interpolate_init_f32(
    csi_fir_interpolate_instance_f32 * S,
    uint8_t L,
    uint16_t numTaps,
    const float32_t * pCoeffs,
    float32_t * pState,
    uint32_t blockSize);


/**
 * @param[in]  S          points to an instance of the high precision Q31 Biquad cascade filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cas_df1_32x64_q31(
    const csi_biquad_cas_df1_32x64_ins_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @param[in,out] S          points to an instance of the high precision Q31 Biquad cascade filter structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     postShift  shift to be applied to the output. Varies according to the coefficients format
 */
void csi_biquad_cas_df1_32x64_init_q31(
    csi_biquad_cas_df1_32x64_ins_q31 * S,
    uint8_t numStages,
    const q31_t * pCoeffs,
    q63_t * pState,
    uint8_t postShift);


/**
 * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
 * @param[in]  S          points to an instance of the filter data structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df2T_f32(
    const csi_biquad_cascade_df2T_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter. 2 channels
 * @param[in]  S          points to an instance of the filter data structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_stereo_df2T_f32(
    const csi_biquad_cascade_stereo_df2T_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
 * @param[in]  S          points to an instance of the filter data structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of samples to process.
 */
void csi_biquad_cascade_df2T_f64(
    const csi_biquad_cascade_df2T_instance_f64 * S,
    float64_t * pSrc,
    float64_t * pDst,
    uint32_t blockSize);


#if defined(CSI_MATH_NEON)
void csi_biquad_cascade_df2T_compute_coefs_f32(
    csi_biquad_cascade_df2T_instance_f32 * S,
    uint8_t numStages,
    float32_t * pCoeffs);
#endif
/**
 * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
 * @param[in,out] S          points to an instance of the filter data structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 */
void csi_biquad_cascade_df2T_init_f32(
    csi_biquad_cascade_df2T_instance_f32 * S,
    uint8_t numStages,
    const float32_t * pCoeffs,
    float32_t * pState);


/**
 * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
 * @param[in,out] S          points to an instance of the filter data structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 */
void csi_biquad_cascade_stereo_df2T_init_f32(
    csi_biquad_cascade_stereo_df2T_instance_f32 * S,
    uint8_t numStages,
    const float32_t * pCoeffs,
    float32_t * pState);


/**
 * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
 * @param[in,out] S          points to an instance of the filter data structure.
 * @param[in]     numStages  number of 2nd order stages in the filter.
 * @param[in]     pCoeffs    points to the filter coefficients.
 * @param[in]     pState     points to the state buffer.
 */
void csi_biquad_cascade_df2T_init_f64(
    csi_biquad_cascade_df2T_instance_f64 * S,
    uint8_t numStages,
    float64_t * pCoeffs,
    float64_t * pState);


/**
 * @brief Initialization function for the Q15 FIR lattice filter.
 * @param[in] S          points to an instance of the Q15 FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
 * @param[in] pState     points to the state buffer.  The array is of length numStages.
 */
void csi_fir_lattice_init_q15(
    csi_fir_lattice_instance_q15 * S,
    uint16_t numStages,
    const q15_t * pCoeffs,
    q15_t * pState);


/**
 * @brief Processing function for the Q15 FIR lattice filter.
 * @param[in]  S          points to an instance of the Q15 FIR lattice structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_lattice_q15(
    const csi_fir_lattice_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Initialization function for the Q31 FIR lattice filter.
 * @param[in] S          points to an instance of the Q31 FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
 * @param[in] pState     points to the state buffer.   The array is of length numStages.
 */
void csi_fir_lattice_init_q31(
    csi_fir_lattice_instance_q31 * S,
    uint16_t numStages,
    const q31_t * pCoeffs,
    q31_t * pState);


/**
 * @brief Processing function for the Q31 FIR lattice filter.
 * @param[in]  S          points to an instance of the Q31 FIR lattice structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_lattice_q31(
    const csi_fir_lattice_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Initialization function for the floating-point FIR lattice filter.
 * @param[in] S          points to an instance of the floating-point FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
 * @param[in] pState     points to the state buffer.  The array is of length numStages.
 */
void csi_fir_lattice_init_f32(
    csi_fir_lattice_instance_f32 * S,
    uint16_t numStages,
    const float32_t * pCoeffs,
    float32_t * pState);


/**
 * @brief Processing function for the floating-point FIR lattice filter.
 * @param[in]  S          points to an instance of the floating-point FIR lattice structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data
 * @param[in]  blockSize  number of samples to process.
 */
void csi_fir_lattice_f32(
    const csi_fir_lattice_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Processing function for the floating-point IIR lattice filter.
 * @param[in]  S          points to an instance of the floating-point IIR lattice structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_iir_lattice_f32(
    const csi_iir_lattice_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief Initialization function for the floating-point IIR lattice filter.
 * @param[in] S          points to an instance of the floating-point IIR lattice structure.
 * @param[in] numStages  number of stages in the filter.
 * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
 * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
 * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize-1.
 * @param[in] blockSize  number of samples to process.
 */
void csi_iir_lattice_init_f32(
    csi_iir_lattice_instance_f32 * S,
    uint16_t numStages,
    float32_t * pkCoeffs,
    float32_t * pvCoeffs,
    float32_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q31 IIR lattice filter.
 * @param[in]  S          points to an instance of the Q31 IIR lattice structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_iir_lattice_q31(
    const csi_iir_lattice_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Initialization function for the Q31 IIR lattice filter.
 * @param[in] S          points to an instance of the Q31 IIR lattice structure.
 * @param[in] numStages  number of stages in the filter.
 * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
 * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
 * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize.
 * @param[in] blockSize  number of samples to process.
 */
void csi_iir_lattice_init_q31(
    csi_iir_lattice_instance_q31 * S,
    uint16_t numStages,
    q31_t * pkCoeffs,
    q31_t * pvCoeffs,
    q31_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q15 IIR lattice filter.
 * @param[in]  S          points to an instance of the Q15 IIR lattice structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[out] pDst       points to the block of output data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_iir_lattice_q15(
    const csi_iir_lattice_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Initialization function for the Q15 IIR lattice filter.
 * @param[in] S          points to an instance of the fixed-point Q15 IIR lattice structure.
 * @param[in] numStages  number of stages in the filter.
 * @param[in] pkCoeffs   points to reflection coefficient buffer.  The array is of length numStages.
 * @param[in] pvCoeffs   points to ladder coefficient buffer.  The array is of length numStages+1.
 * @param[in] pState     points to state buffer.  The array is of length numStages+blockSize.
 * @param[in] blockSize  number of samples to process per call.
 */
void csi_iir_lattice_init_q15(
    csi_iir_lattice_instance_q15 * S,
    uint16_t numStages,
    q15_t * pkCoeffs,
    q15_t * pvCoeffs,
    q15_t * pState,
    uint32_t blockSize);


/**
 * @brief Processing function for floating-point LMS filter.
 * @param[in]  S          points to an instance of the floating-point LMS filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[in]  pRef       points to the block of reference data.
 * @param[out] pOut       points to the block of output data.
 * @param[out] pErr       points to the block of error data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_lms_f32(
    const csi_lms_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pRef,
    float32_t * pOut,
    float32_t * pErr,
    uint32_t blockSize);


/**
 * @brief Initialization function for floating-point LMS filter.
 * @param[in] S          points to an instance of the floating-point LMS filter structure.
 * @param[in] numTaps    number of filter coefficients.
 * @param[in] pCoeffs    points to the coefficient buffer.
 * @param[in] pState     points to state buffer.
 * @param[in] mu         step size that controls filter coefficient updates.
 * @param[in] blockSize  number of samples to process.
 */
void csi_lms_init_f32(
    csi_lms_instance_f32 * S,
    uint16_t numTaps,
    const float32_t * pCoeffs,
    float32_t * pState,
    float32_t mu,
    uint32_t blockSize);


/**
 * @brief Initialization function for the Q15 LMS filter.
 * @param[in] S          points to an instance of the Q15 LMS filter structure.
 * @param[in] numTaps    number of filter coefficients.
 * @param[in] pCoeffs    points to the coefficient buffer.
 * @param[in] pState     points to the state buffer.
 * @param[in] mu         step size that controls filter coefficient updates.
 * @param[in] blockSize  number of samples to process.
 * @param[in] postShift  bit shift applied to coefficients.
 */
void csi_lms_init_q15(
    csi_lms_instance_q15 * S,
    uint16_t numTaps,
    q15_t * pCoeffs,
    q15_t * pState,
    q15_t mu,
    uint32_t blockSize,
    uint32_t postShift);


/**
 * @brief Processing function for Q15 LMS filter.
 * @param[in]  S          points to an instance of the Q15 LMS filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[in]  pRef       points to the block of reference data.
 * @param[out] pOut       points to the block of output data.
 * @param[out] pErr       points to the block of error data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_lms_q15(
    const csi_lms_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pRef,
    q15_t * pOut,
    q15_t * pErr,
    uint32_t blockSize);


/**
 * @brief Processing function for Q31 LMS filter.
 * @param[in]  S          points to an instance of the Q15 LMS filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[in]  pRef       points to the block of reference data.
 * @param[out] pOut       points to the block of output data.
 * @param[out] pErr       points to the block of error data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_lms_q31(
    const csi_lms_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pRef,
    q31_t * pOut,
    q31_t * pErr,
    uint32_t blockSize);


/**
 * @brief Initialization function for Q31 LMS filter.
 * @param[in] S          points to an instance of the Q31 LMS filter structure.
 * @param[in] numTaps    number of filter coefficients.
 * @param[in] pCoeffs    points to coefficient buffer.
 * @param[in] pState     points to state buffer.
 * @param[in] mu         step size that controls filter coefficient updates.
 * @param[in] blockSize  number of samples to process.
 * @param[in] postShift  bit shift applied to coefficients.
 */
void csi_lms_init_q31(
    csi_lms_instance_q31 * S,
    uint16_t numTaps,
    q31_t * pCoeffs,
    q31_t * pState,
    q31_t mu,
    uint32_t blockSize,
    uint32_t postShift);


/**
 * @brief Processing function for floating-point normalized LMS filter.
 * @param[in]  S          points to an instance of the floating-point normalized LMS filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[in]  pRef       points to the block of reference data.
 * @param[out] pOut       points to the block of output data.
 * @param[out] pErr       points to the block of error data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_lms_norm_f32(
    csi_lms_norm_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pRef,
    float32_t * pOut,
    float32_t * pErr,
    uint32_t blockSize);


/**
 * @brief Initialization function for floating-point normalized LMS filter.
 * @param[in] S          points to an instance of the floating-point LMS filter structure.
 * @param[in] numTaps    number of filter coefficients.
 * @param[in] pCoeffs    points to coefficient buffer.
 * @param[in] pState     points to state buffer.
 * @param[in] mu         step size that controls filter coefficient updates.
 * @param[in] blockSize  number of samples to process.
 */
void csi_lms_norm_init_f32(
    csi_lms_norm_instance_f32 * S,
    uint16_t numTaps,
    const float32_t * pCoeffs,
    float32_t * pState,
    float32_t mu,
    uint32_t blockSize);


/**
 * @brief Processing function for Q31 normalized LMS filter.
 * @param[in]  S          points to an instance of the Q31 normalized LMS filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[in]  pRef       points to the block of reference data.
 * @param[out] pOut       points to the block of output data.
 * @param[out] pErr       points to the block of error data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_lms_norm_q31(
    csi_lms_norm_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pRef,
    q31_t * pOut,
    q31_t * pErr,
    uint32_t blockSize);


/**
 * @brief Initialization function for Q31 normalized LMS filter.
 * @param[in] S          points to an instance of the Q31 normalized LMS filter structure.
 * @param[in] numTaps    number of filter coefficients.
 * @param[in] pCoeffs    points to coefficient buffer.
 * @param[in] pState     points to state buffer.
 * @param[in] mu         step size that controls filter coefficient updates.
 * @param[in] blockSize  number of samples to process.
 * @param[in] postShift  bit shift applied to coefficients.
 */
void csi_lms_norm_init_q31(
    csi_lms_norm_instance_q31 * S,
    uint16_t numTaps,
    q31_t * pCoeffs,
    q31_t * pState,
    q31_t mu,
    uint32_t blockSize,
    uint8_t postShift);


/**
 * @brief Processing function for Q15 normalized LMS filter.
 * @param[in]  S          points to an instance of the Q15 normalized LMS filter structure.
 * @param[in]  pSrc       points to the block of input data.
 * @param[in]  pRef       points to the block of reference data.
 * @param[out] pOut       points to the block of output data.
 * @param[out] pErr       points to the block of error data.
 * @param[in]  blockSize  number of samples to process.
 */
void csi_lms_norm_q15(
    csi_lms_norm_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pRef,
    q15_t * pOut,
    q15_t * pErr,
    uint32_t blockSize);


/**
 * @brief Initialization function for Q15 normalized LMS filter.
 * @param[in] S          points to an instance of the Q15 normalized LMS filter structure.
 * @param[in] numTaps    number of filter coefficients.
 * @param[in] pCoeffs    points to coefficient buffer.
 * @param[in] pState     points to state buffer.
 * @param[in] mu         step size that controls filter coefficient updates.
 * @param[in] blockSize  number of samples to process.
 * @param[in] postShift  bit shift applied to coefficients.
 */
void csi_lms_norm_init_q15(
    csi_lms_norm_instance_q15 * S,
    uint16_t numTaps,
    q15_t * pCoeffs,
    q15_t * pState,
    q15_t mu,
    uint32_t blockSize,
    uint8_t postShift);


/**
 * @brief Correlation of floating-point sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void csi_correlate_f32(
    const float32_t * pSrcA,
    uint32_t srcALen,
    const float32_t * pSrcB,
    uint32_t srcBLen,
    float32_t * pDst);


/**
 @brief Correlation of Q15 sequences
 @param[in]  pSrcA     points to the first input sequence
 @param[in]  srcALen   length of the first input sequence
 @param[in]  pSrcB     points to the second input sequence
 @param[in]  srcBLen   length of the second input sequence
 @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
*/
void csi_correlate_opt_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    q15_t * pScratch);


/**
  @brief Correlation of Q15 sequences.
  @param[in]  pSrcA    points to the first input sequence
  @param[in]  srcALen  length of the first input sequence
  @param[in]  pSrcB    points to the second input sequence
  @param[in]  srcBLen  length of the second input sequence
  @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void csi_correlate_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst);


/**
  @brief         Correlation of Q15 sequences (fast version).
  @param[in]     pSrcA      points to the first input sequence
  @param[in]     srcALen    length of the first input sequence
  @param[in]     pSrcB      points to the second input sequence
  @param[in]     srcBLen    length of the second input sequence
  @param[out]    pDst       points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.
  @return        none
 */
void csi_correlate_fast_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst);


/**
  @brief Correlation of Q15 sequences (fast version).
  @param[in]  pSrcA     points to the first input sequence.
  @param[in]  srcALen   length of the first input sequence.
  @param[in]  pSrcB     points to the second input sequence.
  @param[in]  srcBLen   length of the second input sequence.
  @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
  @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
 */
void csi_correlate_fast_opt_q15(
    const q15_t * pSrcA,
    uint32_t srcALen,
    const q15_t * pSrcB,
    uint32_t srcBLen,
    q15_t * pDst,
    q15_t * pScratch);


/**
 * @brief Correlation of Q31 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void csi_correlate_q31(
    const q31_t * pSrcA,
    uint32_t srcALen,
    const q31_t * pSrcB,
    uint32_t srcBLen,
    q31_t * pDst);


/**
  @brief Correlation of Q31 sequences (fast version).
  @param[in]  pSrcA    points to the first input sequence
  @param[in]  srcALen  length of the first input sequence
  @param[in]  pSrcB    points to the second input sequence
  @param[in]  srcBLen  length of the second input sequence
  @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void csi_correlate_fast_q31(
    const q31_t * pSrcA,
    uint32_t srcALen,
    const q31_t * pSrcB,
    uint32_t srcBLen,
    q31_t * pDst);


/**
  * @brief Correlation of Q7 sequences.
  * @param[in]  pSrcA      points to the first input sequence.
  * @param[in]  srcALen    length of the first input sequence.
  * @param[in]  pSrcB      points to the second input sequence.
  * @param[in]  srcBLen    length of the second input sequence.
  * @param[out] pDst       points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
  * @param[in]  pScratch1  points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
  * @param[in]  pScratch2  points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
  */
void csi_correlate_opt_q7(
    const q7_t * pSrcA,
    uint32_t srcALen,
    const q7_t * pSrcB,
    uint32_t srcBLen,
    q7_t * pDst,
    q15_t * pScratch1,
    q15_t * pScratch2);


/**
 * @brief Correlation of Q7 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
 */
void csi_correlate_q7(
    const q7_t * pSrcA,
    uint32_t srcALen,
    const q7_t * pSrcB,
    uint32_t srcBLen,
    q7_t * pDst);

/**
 * @brief Processing function for the floating-point sparse FIR filter.
 * @param[in]  S           points to an instance of the floating-point sparse FIR structure.
 * @param[in]  pSrc        points to the block of input data.
 * @param[out] pDst        points to the block of output data
 * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
 * @param[in]  blockSize   number of input samples to process per call.
 */
void csi_fir_sparse_f32(
    csi_fir_sparse_instance_f32 * S,
    const float32_t * pSrc,
    float32_t * pDst,
    float32_t * pScratchIn,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the floating-point sparse FIR filter.
 * @param[in,out] S          points to an instance of the floating-point sparse FIR structure.
 * @param[in]     numTaps    number of nonzero coefficients in the filter.
 * @param[in]     pCoeffs    points to the array of filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     pTapDelay  points to the array of offset times.
 * @param[in]     maxDelay   maximum offset time supported.
 * @param[in]     blockSize  number of samples that will be processed per block.
 */
void csi_fir_sparse_init_f32(
    csi_fir_sparse_instance_f32 * S,
    uint16_t numTaps,
    const float32_t * pCoeffs,
    float32_t * pState,
    int32_t * pTapDelay,
    uint16_t maxDelay,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q31 sparse FIR filter.
 * @param[in]  S           points to an instance of the Q31 sparse FIR structure.
 * @param[in]  pSrc        points to the block of input data.
 * @param[out] pDst        points to the block of output data
 * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
 * @param[in]  blockSize   number of input samples to process per call.
 */
void csi_fir_sparse_q31(
    csi_fir_sparse_instance_q31 * S,
    const q31_t * pSrc,
    q31_t * pDst,
    q31_t * pScratchIn,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q31 sparse FIR filter.
 * @param[in,out] S          points to an instance of the Q31 sparse FIR structure.
 * @param[in]     numTaps    number of nonzero coefficients in the filter.
 * @param[in]     pCoeffs    points to the array of filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     pTapDelay  points to the array of offset times.
 * @param[in]     maxDelay   maximum offset time supported.
 * @param[in]     blockSize  number of samples that will be processed per block.
 */
void csi_fir_sparse_init_q31(
    csi_fir_sparse_instance_q31 * S,
    uint16_t numTaps,
    const q31_t * pCoeffs,
    q31_t * pState,
    int32_t * pTapDelay,
    uint16_t maxDelay,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q15 sparse FIR filter.
 * @param[in]  S            points to an instance of the Q15 sparse FIR structure.
 * @param[in]  pSrc         points to the block of input data.
 * @param[out] pDst         points to the block of output data
 * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
 * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
 * @param[in]  blockSize    number of input samples to process per call.
 */
void csi_fir_sparse_q15(
    csi_fir_sparse_instance_q15 * S,
    const q15_t * pSrc,
    q15_t * pDst,
    q15_t * pScratchIn,
    q31_t * pScratchOut,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q15 sparse FIR filter.
 * @param[in,out] S          points to an instance of the Q15 sparse FIR structure.
 * @param[in]     numTaps    number of nonzero coefficients in the filter.
 * @param[in]     pCoeffs    points to the array of filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     pTapDelay  points to the array of offset times.
 * @param[in]     maxDelay   maximum offset time supported.
 * @param[in]     blockSize  number of samples that will be processed per block.
 */
void csi_fir_sparse_init_q15(
    csi_fir_sparse_instance_q15 * S,
    uint16_t numTaps,
    const q15_t * pCoeffs,
    q15_t * pState,
    int32_t * pTapDelay,
    uint16_t maxDelay,
    uint32_t blockSize);


/**
 * @brief Processing function for the Q7 sparse FIR filter.
 * @param[in]  S            points to an instance of the Q7 sparse FIR structure.
 * @param[in]  pSrc         points to the block of input data.
 * @param[out] pDst         points to the block of output data
 * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
 * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
 * @param[in]  blockSize    number of input samples to process per call.
 */
void csi_fir_sparse_q7(
    csi_fir_sparse_instance_q7 * S,
    const q7_t * pSrc,
    q7_t * pDst,
    q7_t * pScratchIn,
    q31_t * pScratchOut,
    uint32_t blockSize);


/**
 * @brief  Initialization function for the Q7 sparse FIR filter.
 * @param[in,out] S          points to an instance of the Q7 sparse FIR structure.
 * @param[in]     numTaps    number of nonzero coefficients in the filter.
 * @param[in]     pCoeffs    points to the array of filter coefficients.
 * @param[in]     pState     points to the state buffer.
 * @param[in]     pTapDelay  points to the array of offset times.
 * @param[in]     maxDelay   maximum offset time supported.
 * @param[in]     blockSize  number of samples that will be processed per block.
 */
void csi_fir_sparse_init_q7(
    csi_fir_sparse_instance_q7 * S,
    uint16_t numTaps,
    const q7_t * pCoeffs,
    q7_t * pState,
    int32_t * pTapDelay,
    uint16_t maxDelay,
    uint32_t blockSize);


/**
 * @brief  Floating-point sin_cos function.
 * @param[in]  theta   input value in degrees
 * @param[out] pSinVal  points to the processed sine output.
 * @param[out] pCosVal  points to the processed cos output.
 */
void csi_sin_cos_f32(
    float32_t theta,
    float32_t * pSinVal,
    float32_t * pCosVal);


/**
 * @brief  Q31 sin_cos function.
 * @param[in]  theta    scaled input value in degrees
 * @param[out] pSinVal  points to the processed sine output.
 * @param[out] pCosVal  points to the processed cosine output.
 */
void csi_sin_cos_q31(
    q31_t theta,
    q31_t * pSinVal,
    q31_t * pCosVal);


/**
 * @brief  Floating-point complex conjugate.
 * @param[in]  pSrc        points to the input vector
 * @param[out] pDst        points to the output vector
 * @param[in]  numSamples  number of complex samples in each vector
 */
void csi_cmplx_conj_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t numSamples);

/**
 * @brief  Q31 complex conjugate.
 * @param[in]  pSrc        points to the input vector
 * @param[out] pDst        points to the output vector
 * @param[in]  numSamples  number of complex samples in each vector
 */
void csi_cmplx_conj_q31(
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q15 complex conjugate.
 * @param[in]  pSrc        points to the input vector
 * @param[out] pDst        points to the output vector
 * @param[in]  numSamples  number of complex samples in each vector
 */
void csi_cmplx_conj_q15(
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Floating-point complex magnitude squared
 * @param[in]  pSrc        points to the complex input vector
 * @param[out] pDst        points to the real output vector
 * @param[in]  numSamples  number of complex samples in the input vector
 */
void csi_cmplx_mag_squared_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q31 complex magnitude squared
 * @param[in]  pSrc        points to the complex input vector
 * @param[out] pDst        points to the real output vector
 * @param[in]  numSamples  number of complex samples in the input vector
 */
void csi_cmplx_mag_squared_q31(
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t numSamples);

void csi_cmplx_mag_squared_q31_basic(
    q31_t * pSrc,
    q63_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q15 complex magnitude squared
 * @param[in]  pSrc        points to the complex input vector
 * @param[out] pDst        points to the real output vector
 * @param[in]  numSamples  number of complex samples in the input vector
 */
void csi_cmplx_mag_squared_q15(
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t numSamples);


/**
  * @ingroup groupController
  */

/**
 * @defgroup PID PID Motor Control
 *
 * A Proportional Integral Derivative (PID) controller is a generic feedback control
 * loop mechanism widely used in industrial control systems.
 * A PID controller is the most commonly used type of feedback controller.
 *
 * This set of functions implements (PID) controllers
 * for Q15, Q31, and floating-point data types.  The functions operate on a single sample
 * of data and each call to the function returns a single processed value.
 * <code>S</code> points to an instance of the PID control data structure.  <code>in</code>
 * is the input sample value. The functions return the output value.
 *
 * \par Algorithm:
 * <pre>
 *    y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
 *    A0 = Kp + Ki + Kd
 *    A1 = (-Kp ) - (2 * Kd )
 *    A2 = Kd
 * </pre>
 *
 * \par
 * where \c Kp is proportional constant, \c Ki is Integral constant and \c Kd is Derivative constant
 *
 * \par
 * \image html PID.gif "Proportional Integral Derivative Controller"
 *
 * \par
 * The PID controller calculates an "error" value as the difference between
 * the measured output and the reference input.
 * The controller attempts to minimize the error by adjusting the process control inputs.
 * The proportional value determines the reaction to the current error,
 * the integral value determines the reaction based on the sum of recent errors,
 * and the derivative value determines the reaction based on the rate at which the error has been changing.
 *
 * \par Instance Structure
 * The Gains A0, A1, A2 and state variables for a PID controller are stored together in an instance data structure.
 * A separate instance structure must be defined for each PID Controller.
 * There are separate instance structure declarations for each of the 3 supported data types.
 *
 * \par Reset Functions
 * There is also an associated reset function for each data type which clears the state array.
 *
 * \par Initialization Functions
 * There is also an associated initialization function for each data type.
 * The initialization function performs the following operations:
 * - Initializes the Gains A0, A1, A2 from Kp,Ki, Kd gains.
 * - Zeros out the values in the state buffer.
 *
 * \par
 * Instance structure cannot be placed into a const data section and it is recommended to use the initialization function.
 *
 * \par Fixed-Point Behavior
 * Care must be taken when using the fixed-point versions of the PID Controller functions.
 * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.
 * Refer to the function specific documentation below for usage guidelines.
 */

/**
 * @addtogroup PID
 * @{
 */

/**
 * @brief         Process function for the floating-point PID Control.
 * @param[in,out] S   is an instance of the floating-point PID Control structure
 * @param[in]     in  input sample to process
 * @return        processed output sample.
 */
__STATIC_FORCEINLINE float32_t csi_pid_f32(
    csi_pid_instance_f32 * S,
    float32_t in)
{
    float32_t out;
    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
          (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);
    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    /* return to application */
    return (out);
}

/**
  @brief         Process function for the Q31 PID Control.
  @param[in,out] S  points to an instance of the Q31 PID Control structure
  @param[in]     in  input sample to process
  @return        processed output sample.

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 64-bit accumulator.
         The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
         Thus, if the accumulator result overflows it wraps around rather than clip.
         In order to avoid overflows completely the input signal must be scaled down by 2 bits as there are four additions.
         After all multiply-accumulates are performed, the 2.62 accumulator is truncated to 1.32 format and then saturated to 1.31 format.
 */
__STATIC_FORCEINLINE q31_t csi_pid_q31(
    csi_pid_instance_q31 * S,
    q31_t in)
{
    q63_t acc;
    q31_t out;
    /* acc = A0 * x[n]  */
    acc = (q63_t) S->A0 * in;
    /* acc += A1 * x[n-1] */
    acc += (q63_t) S->A1 * S->state[0];
    /* acc += A2 * x[n-2]  */
    acc += (q63_t) S->A2 * S->state[1];
    /* convert output to 1.31 format to add y[n-1] */
    out = (q31_t) (acc >> 31U);
    /* out += y[n-1] */
    out += S->state[2];
    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    /* return to application */
    return (out);
}


/**
  @brief         Process function for the Q15 PID Control.
  @param[in,out] S   points to an instance of the Q15 PID Control structure
  @param[in]     in  input sample to process
  @return        processed output sample.

  \par Scaling and Overflow Behavior
         The function is implemented using a 64-bit internal accumulator.
         Both Gains and state variables are represented in 1.15 format and multiplications yield a 2.30 result.
         The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.
         There is no risk of internal overflow with this approach and the full precision of intermediate multiplications is preserved.
         After all additions have been performed, the accumulator is truncated to 34.15 format by discarding low 15 bits.
         Lastly, the accumulator is saturated to yield a result in 1.15 format.
 */
__STATIC_FORCEINLINE q15_t csi_pid_q15(
    csi_pid_instance_q15 * S,
    q15_t in)
{
    q63_t acc;
    q15_t out;
#if defined (CSI_MATH_DSP)
    /* Implementation of PID controller */
    /* acc = A0 * x[n]  */
    acc = (q31_t) __SMUAD((uint32_t)S->A0, (uint32_t)in);
    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc = (q63_t)__SMLALD((uint32_t)S->A1, (uint32_t)read_q15x2 (S->state), (uint64_t)acc);
#else
    /* acc = A0 * x[n]  */
    acc = ((q31_t) S->A0) * in;
    /* acc += A1 * x[n-1] + A2 * x[n-2]  */
    acc += (q31_t) S->A1 * S->state[0];
    acc += (q31_t) S->A2 * S->state[1];
#endif
    /* acc += y[n-1] */
    acc += (q31_t) S->state[2] << 15;
    /* saturate the output */
    out = (q15_t) (__SSAT((q31_t)(acc >> 15), 16));
    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    /* return to application */
    return (out);
}

/**
 * @} end of PID group
 */


/**
 * @brief Floating-point matrix inverse.
 * @param[in]  src   points to the instance of the input floating-point matrix structure.
 * @param[out] dst   points to the instance of the output floating-point matrix structure.
 * @return The function returns CSI_MATH_SIZE_MISMATCH, if the dimensions do not match.
 * If the input matrix is singular (does not have an inverse), then the algorithm terminates and returns error status CSI_MATH_SINGULAR.
 */
csi_status csi_mat_inverse_f32(
    const csi_matrix_instance_f32 * src,
    csi_matrix_instance_f32 * dst);


/**
 * @brief Floating-point matrix inverse.
 * @param[in]  src   points to the instance of the input floating-point matrix structure.
 * @param[out] dst   points to the instance of the output floating-point matrix structure.
 * @return The function returns CSI_MATH_SIZE_MISMATCH, if the dimensions do not match.
 * If the input matrix is singular (does not have an inverse), then the algorithm terminates and returns error status CSI_MATH_SINGULAR.
 */
csi_status csi_mat_inverse_f64(
    const csi_matrix_instance_f64 * src,
    csi_matrix_instance_f64 * dst);



/**
 * @ingroup groupController
 */

/**
 * @defgroup clarke Vector Clarke Transform
 * Forward Clarke transform converts the instantaneous stator phases into a two-coordinate time invariant vector.
 * Generally the Clarke transform uses three-phase currents <code>Ia, Ib and Ic</code> to calculate currents
 * in the two-phase orthogonal stator axis <code>Ialpha</code> and <code>Ibeta</code>.
 * When <code>Ialpha</code> is superposed with <code>Ia</code> as shown in the figure below
 * \image html clarke.gif Stator current space vector and its components in (a,b).
 * and <code>Ia + Ib + Ic = 0</code>, in this condition <code>Ialpha</code> and <code>Ibeta</code>
 * can be calculated using only <code>Ia</code> and <code>Ib</code>.
 *
 * The function operates on a single sample of data and each call to the function returns the processed output.
 * The library provides separate functions for Q31 and floating-point data types.
 * \par Algorithm
 * \image html clarkeFormula.gif
 * where <code>Ia</code> and <code>Ib</code> are the instantaneous stator phases and
 * <code>pIalpha</code> and <code>pIbeta</code> are the two coordinates of time invariant vector.
 * \par Fixed-Point Behavior
 * Care must be taken when using the Q31 version of the Clarke transform.
 * In particular, the overflow and saturation behavior of the accumulator used must be considered.
 * Refer to the function specific documentation below for usage guidelines.
 */

/**
 * @addtogroup clarke
 * @{
 */

/**
 *
 * @brief  Floating-point Clarke transform
 * @param[in]  Ia       input three-phase coordinate <code>a</code>
 * @param[in]  Ib       input three-phase coordinate <code>b</code>
 * @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
 * @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
 * @return        none
 */
__STATIC_FORCEINLINE void csi_clarke_f32(
    float32_t Ia,
    float32_t Ib,
    float32_t * pIalpha,
    float32_t * pIbeta)
{
    /* Calculate pIalpha using the equation, pIalpha = Ia */
    *pIalpha = Ia;
    /* Calculate pIbeta using the equation, pIbeta = (1/sqrt(3)) * Ia + (2/sqrt(3)) * Ib */
    *pIbeta = ((float32_t) 0.57735026919 * Ia + (float32_t) 1.15470053838 * Ib);
}


/**
  @brief  Clarke transform for Q31 version
  @param[in]  Ia       input three-phase coordinate <code>a</code>
  @param[in]  Ib       input three-phase coordinate <code>b</code>
  @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
  @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void csi_clarke_q31(
    q31_t Ia,
    q31_t Ib,
    q31_t * pIalpha,
    q31_t * pIbeta)
{
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */
    /* Calculating pIalpha from Ia by equation pIalpha = Ia */
    *pIalpha = Ia;
    /* Intermediate product is calculated by (1/(sqrt(3)) * Ia) */
    product1 = (q31_t) (((q63_t) Ia * 0x24F34E8B) >> 30);
    /* Intermediate product is calculated by (2/sqrt(3) * Ib) */
    product2 = (q31_t) (((q63_t) Ib * 0x49E69D16) >> 30);
    /* pIbeta is calculated by adding the intermediate products */
    *pIbeta = __QADD(product1, product2);
}

/**
 * @} end of clarke group
 */


/**
 * @ingroup groupController
 */

/**
 * @defgroup inv_clarke Vector Inverse Clarke Transform
 * Inverse Clarke transform converts the two-coordinate time invariant vector into instantaneous stator phases.
 *
 * The function operates on a single sample of data and each call to the function returns the processed output.
 * The library provides separate functions for Q31 and floating-point data types.
 * \par Algorithm
 * \image html clarkeInvFormula.gif
 * where <code>pIa</code> and <code>pIb</code> are the instantaneous stator phases and
 * <code>Ialpha</code> and <code>Ibeta</code> are the two coordinates of time invariant vector.
 * \par Fixed-Point Behavior
 * Care must be taken when using the Q31 version of the Clarke transform.
 * In particular, the overflow and saturation behavior of the accumulator used must be considered.
 * Refer to the function specific documentation below for usage guidelines.
 */

/**
 * @addtogroup inv_clarke
 * @{
 */

/**
* @brief  Floating-point Inverse Clarke transform
* @param[in]  Ialpha  input two-phase orthogonal vector axis alpha
* @param[in]  Ibeta   input two-phase orthogonal vector axis beta
* @param[out] pIa     points to output three-phase coordinate <code>a</code>
* @param[out] pIb     points to output three-phase coordinate <code>b</code>
* @return     none
*/
__STATIC_FORCEINLINE void csi_inv_clarke_f32(
    float32_t Ialpha,
    float32_t Ibeta,
    float32_t * pIa,
    float32_t * pIb)
{
    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;
    /* Calculating pIb from Ialpha and Ibeta by equation pIb = -(1/2) * Ialpha + (sqrt(3)/2) * Ibeta */
    *pIb = -0.5f * Ialpha + 0.8660254039f * Ibeta;
}


/**
  @brief  Inverse Clarke transform for Q31 version
  @param[in]  Ialpha  input two-phase orthogonal vector axis alpha
  @param[in]  Ibeta   input two-phase orthogonal vector axis beta
  @param[out] pIa     points to output three-phase coordinate <code>a</code>
  @param[out] pIb     points to output three-phase coordinate <code>b</code>
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the subtraction, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void csi_inv_clarke_q31(
    q31_t Ialpha,
    q31_t Ibeta,
    q31_t * pIa,
    q31_t * pIb)
{
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */
    /* Calculating pIa from Ialpha by equation pIa = Ialpha */
    *pIa = Ialpha;
    /* Intermediate product is calculated by (1/(2*sqrt(3)) * Ia) */
    product1 = (q31_t) (((q63_t) (Ialpha) * (0x40000000)) >> 31);
    /* Intermediate product is calculated by (1/sqrt(3) * pIb) */
    product2 = (q31_t) (((q63_t) (Ibeta) * (0x6ED9EBA1)) >> 31);
    /* pIb is calculated by subtracting the products */
    *pIb = __QSUB(product2, product1);
}

/**
 * @} end of inv_clarke group
 */



/**
 * @ingroup groupController
 */

/**
 * @defgroup park Vector Park Transform
 *
 * Forward Park transform converts the input two-coordinate vector to flux and torque components.
 * The Park transform can be used to realize the transformation of the <code>Ialpha</code> and the <code>Ibeta</code> currents
 * from the stationary to the moving reference frame and control the spatial relationship between
 * the stator vector current and rotor flux vector.
 * If we consider the d axis aligned with the rotor flux, the diagram below shows the
 * current vector and the relationship from the two reference frames:
 * \image html park.gif "Stator current space vector and its component in (a,b) and in the d,q rotating reference frame"
 *
 * The function operates on a single sample of data and each call to the function returns the processed output.
 * The library provides separate functions for Q31 and floating-point data types.
 * \par Algorithm
 * \image html parkFormula.gif
 * where <code>Ialpha</code> and <code>Ibeta</code> are the stator vector components,
 * <code>pId</code> and <code>pIq</code> are rotor vector components and <code>cosVal</code> and <code>sinVal</code> are the
 * cosine and sine values of theta (rotor flux position).
 * \par Fixed-Point Behavior
 * Care must be taken when using the Q31 version of the Park transform.
 * In particular, the overflow and saturation behavior of the accumulator used must be considered.
 * Refer to the function specific documentation below for usage guidelines.
 */

/**
 * @addtogroup park
 * @{
 */

/**
 * @brief Floating-point Park transform
 * @param[in]  Ialpha  input two-phase vector coordinate alpha
 * @param[in]  Ibeta   input two-phase vector coordinate beta
 * @param[out] pId     points to output   rotor reference frame d
 * @param[out] pIq     points to output   rotor reference frame q
 * @param[in]  sinVal  sine value of rotation angle theta
 * @param[in]  cosVal  cosine value of rotation angle theta
 * @return     none
 *
 * The function implements the forward Park transform.
 *
 */
__STATIC_FORCEINLINE void csi_park_f32(
    float32_t Ialpha,
    float32_t Ibeta,
    float32_t * pId,
    float32_t * pIq,
    float32_t sinVal,
    float32_t cosVal)
{
    /* Calculate pId using the equation, pId = Ialpha * cosVal + Ibeta * sinVal */
    *pId = Ialpha * cosVal + Ibeta * sinVal;
    /* Calculate pIq using the equation, pIq = - Ialpha * sinVal + Ibeta * cosVal */
    *pIq = -Ialpha * sinVal + Ibeta * cosVal;
}


/**
  @brief  Park transform for Q31 version
  @param[in]  Ialpha  input two-phase vector coordinate alpha
  @param[in]  Ibeta   input two-phase vector coordinate beta
  @param[out] pId     points to output rotor reference frame d
  @param[out] pIq     points to output rotor reference frame q
  @param[in]  sinVal  sine value of rotation angle theta
  @param[in]  cosVal  cosine value of rotation angle theta
  @return     none

  \par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition and subtraction, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void csi_park_q31(
    q31_t Ialpha,
    q31_t Ibeta,
    q31_t * pId,
    q31_t * pIq,
    q31_t sinVal,
    q31_t cosVal)
{
#ifdef CSI_SIMD
  asm volatile(
                "rmul.s32.h t0, %0, %3\n\t"
                "rmul.s32.h t1, %1, %2\n\t"
                "add.s32.s  t0, t0, t1\n\t"
                "st.w       t0, (%4, 0x0)\n\t"
                "rmul.s32.h t0, %0, %2\n\t"
                "rmul.s32.h t1, %1, %3\n\t"
                "sub.s32.s  t1, t1, t0\n\t"
                "st.w       t1, (%5, 0x0)\n\t"
                ::"r"(Ialpha),"r"(Ibeta),"r"(sinVal),"r"(cosVal),"r"(pId),"r"(pIq)
                :"t0","t1", "memory");
#else
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */
    q31_t product3, product4;                    /* Temporary variables used to store intermediate results */
    /* Intermediate product is calculated by (Ialpha * cosVal) */
    product1 = (q31_t) (((q63_t) (Ialpha) * (cosVal)) >> 31);
    /* Intermediate product is calculated by (Ibeta * sinVal) */
    product2 = (q31_t) (((q63_t) (Ibeta) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Ialpha * sinVal) */
    product3 = (q31_t) (((q63_t) (Ialpha) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Ibeta * cosVal) */
    product4 = (q31_t) (((q63_t) (Ibeta) * (cosVal)) >> 31);
    /* Calculate pId by adding the two intermediate products 1 and 2 */
    *pId = __QADD(product1, product2);
    /* Calculate pIq by subtracting the two intermediate products 3 from 4 */
    *pIq = __QSUB(product4, product3);
#endif
}

/**
 * @} end of park group
 */


/**
 * @ingroup groupController
 */

/**
 * @defgroup inv_park Vector Inverse Park transform
 * Inverse Park transform converts the input flux and torque components to two-coordinate vector.
 *
 * The function operates on a single sample of data and each call to the function returns the processed output.
 * The library provides separate functions for Q31 and floating-point data types.
 * \par Algorithm
 * \image html parkInvFormula.gif
 * where <code>pIalpha</code> and <code>pIbeta</code> are the stator vector components,
 * <code>Id</code> and <code>Iq</code> are rotor vector components and <code>cosVal</code> and <code>sinVal</code> are the
 * cosine and sine values of theta (rotor flux position).
 * \par Fixed-Point Behavior
 * Care must be taken when using the Q31 version of the Park transform.
 * In particular, the overflow and saturation behavior of the accumulator used must be considered.
 * Refer to the function specific documentation below for usage guidelines.
 */

/**
 * @addtogroup inv_park
 * @{
 */

/**
* @brief  Floating-point Inverse Park transform
* @param[in]  Id       input coordinate of rotor reference frame d
* @param[in]  Iq       input coordinate of rotor reference frame q
* @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
* @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
* @param[in]  sinVal   sine value of rotation angle theta
* @param[in]  cosVal   cosine value of rotation angle theta
* @return     none
*/
__STATIC_FORCEINLINE void csi_inv_park_f32(
    float32_t Id,
    float32_t Iq,
    float32_t * pIalpha,
    float32_t * pIbeta,
    float32_t sinVal,
    float32_t cosVal)
{
    /* Calculate pIalpha using the equation, pIalpha = Id * cosVal - Iq * sinVal */
    *pIalpha = Id * cosVal - Iq * sinVal;
    /* Calculate pIbeta using the equation, pIbeta = Id * sinVal + Iq * cosVal */
    *pIbeta = Id * sinVal + Iq * cosVal;
}


/**
  @brief  Inverse Park transform for   Q31 version
  @param[in]  Id       input coordinate of rotor reference frame d
  @param[in]  Iq       input coordinate of rotor reference frame q
  @param[out] pIalpha  points to output two-phase orthogonal vector axis alpha
  @param[out] pIbeta   points to output two-phase orthogonal vector axis beta
  @param[in]  sinVal   sine value of rotation angle theta
  @param[in]  cosVal   cosine value of rotation angle theta
  @return     none

  @par Scaling and Overflow Behavior
         The function is implemented using an internal 32-bit accumulator.
         The accumulator maintains 1.31 format by truncating lower 31 bits of the intermediate multiplication in 2.62 format.
         There is saturation on the addition, hence there is no risk of overflow.
 */
__STATIC_FORCEINLINE void csi_inv_park_q31(
    q31_t Id,
    q31_t Iq,
    q31_t * pIalpha,
    q31_t * pIbeta,
    q31_t sinVal,
    q31_t cosVal)
{
#ifdef CSI_SIMD
  asm volatile(
                "rmul.s32.h t0, %0, %3\n\t"
                "rmul.s32.h t1, %1, %2\n\t"
                "sub.s32.s  t0, t0, t1\n\t"
                "st.w       t0, (%4, 0x0)\n\t"
                "rmul.s32.h t0, %0, %2\n\t"
                "rmul.s32.h t1, %1, %3\n\t"
                "add.s32.s  t0, t0, t1\n\t"
                "st.w       t0, (%5, 0x0)\n\t"
                ::"r"(Id),"r"(Iq),"r"(sinVal),"r"(cosVal),"r"(pIalpha),"r"(pIbeta)
                :"t0","t1", "memory");
#else
    q31_t product1, product2;                    /* Temporary variables used to store intermediate results */
    q31_t product3, product4;                    /* Temporary variables used to store intermediate results */
    /* Intermediate product is calculated by (Id * cosVal) */
    product1 = (q31_t) (((q63_t) (Id) * (cosVal)) >> 31);
    /* Intermediate product is calculated by (Iq * sinVal) */
    product2 = (q31_t) (((q63_t) (Iq) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Id * sinVal) */
    product3 = (q31_t) (((q63_t) (Id) * (sinVal)) >> 31);
    /* Intermediate product is calculated by (Iq * cosVal) */
    product4 = (q31_t) (((q63_t) (Iq) * (cosVal)) >> 31);
    /* Calculate pIalpha by using the two intermediate products 1 and 2 */
    *pIalpha = __QSUB(product1, product2);
    /* Calculate pIbeta by using the two intermediate products 3 and 4 */
    *pIbeta = __QADD(product4, product3);
#endif
}

/**
 * @} end of Inverse park group
 */


/**
 * @ingroup groupInterpolation
 */

/**
 * @defgroup LinearInterpolate Linear Interpolation
 *
 * Linear interpolation is a method of curve fitting using linear polynomials.
 * Linear interpolation works by effectively drawing a straight line between two neighboring samples and returning the appropriate point along that line
 *
 * \par
 * \image html LinearInterp.gif "Linear interpolation"
 *
 * \par
 * A  Linear Interpolate function calculates an output value(y), for the input(x)
 * using linear interpolation of the input values x0, x1( nearest input values) and the output values y0 and y1(nearest output values)
 *
 * \par Algorithm:
 * <pre>
 *       y = y0 + (x - x0) * ((y1 - y0)/(x1-x0))
 *       where x0, x1 are nearest values of input x
 *             y0, y1 are nearest values to output y
 * </pre>
 *
 * \par
 * This set of functions implements Linear interpolation process
 * for Q7, Q15, Q31, and floating-point data types.  The functions operate on a single
 * sample of data and each call to the function returns a single processed value.
 * <code>S</code> points to an instance of the Linear Interpolate function data structure.
 * <code>x</code> is the input sample value. The functions returns the output value.
 *
 * \par
 * if x is outside of the table boundary, Linear interpolation returns first value of the table
 * if x is below input range and returns last value of table if x is above range.
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
__STATIC_FORCEINLINE float32_t csi_linear_interp_f32(
    csi_linear_interp_instance_f32 * S,
    float32_t x)
{
    float32_t y;
    float32_t x0, x1;                            /* Nearest input values */
    float32_t y0, y1;                            /* Nearest output values */
    float32_t xSpacing = S->xSpacing;            /* spacing between input values */
    int32_t i;                                   /* Index variable */
    float32_t *pYData = S->pYData;               /* pointer to output table */
    /* Calculation of index */
    i = (int32_t) ((x - S->x1) / xSpacing);

    if (i < 0) {
        /* Iniatilize output for below specified range as least output value of table */
        y = pYData[0];

    } else if ((uint32_t)i >= (S->nValues - 1)) {
        /* Iniatilize output for above specified range as last output value of table */
        y = pYData[S->nValues - 1];

    } else {
        /* Calculation of nearest input values */
        x0 = S->x1 +  i      * xSpacing;
        x1 = S->x1 + (i + 1) * xSpacing;
        /* Read of nearest output values */
        y0 = pYData[i];
        y1 = pYData[i + 1];
        /* Calculation of output */
        y = y0 + (x - x0) * ((y1 - y0) / (x1 - x0));
    }

    /* returns output value */
    return (y);
}


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
__STATIC_FORCEINLINE q31_t csi_linear_interp_q31(
    q31_t * pYData,
    q31_t x,
    uint32_t nValues)
{
    q31_t y;                                     /* output */
    q31_t y0, y1;                                /* Nearest output values */
    q31_t fract;                                 /* fractional part */
    int32_t index;                               /* Index to read nearest output values */
    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    index = ((x & (q31_t)0xFFF00000) >> 20);

    if (index >= (int32_t)(nValues - 1)) {
        return (pYData[nValues - 1]);

    } else if (index < 0) {
        return (pYData[0]);

    } else {
        /* 20 bits for the fractional part */
        /* shift left by 11 to keep fract in 1.31 format */
        fract = (x & 0x000FFFFF) << 11;
        /* Read two nearest output values from the index in 1.31(q31) format */
        y0 = pYData[index];
        y1 = pYData[index + 1];
        /* Calculation of y0 * (1-fract) and y is in 2.30 format */
        y = ((q31_t) ((q63_t) y0 * (0x7FFFFFFF - fract) >> 32));
        /* Calculation of y0 * (1-fract) + y1 *fract and y is in 2.30 format */
        y += ((q31_t) (((q63_t) y1 * fract) >> 32));
        /* Convert y to 1.31 format */
        return (y << 1U);
    }
}


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
__STATIC_FORCEINLINE q15_t csi_linear_interp_q15(
    q15_t * pYData,
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

    if (index >= (int32_t)(nValues - 1)) {
        return (pYData[nValues - 1]);

    } else if (index < 0) {
        return (pYData[0]);

    } else {
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
__STATIC_FORCEINLINE q7_t csi_linear_interp_q7(
    q7_t * pYData,
    q31_t x,
    uint32_t nValues)
{
    q31_t y;                                     /* output */
    q7_t y0, y1;                                 /* Nearest output values */
    q31_t fract;                                 /* fractional part */
    uint32_t index;                              /* Index to read nearest output values */

    /* Input is in 12.20 format */
    /* 12 bits for the table index */
    /* Index value calculation */
    if (x < 0) {
        return (pYData[0]);
    }

    index = (x >> 20) & 0xfff;

    if (index >= (nValues - 1)) {
        return (pYData[nValues - 1]);

    } else {
        /* 20 bits for the fractional part */
        /* fract is in 12.20 format */
        fract = (x & 0x000FFFFF);
        /* Read two nearest output values from the index and are in 1.7(q7) format */
        y0 = pYData[index];
        y1 = pYData[index + 1];
        /* Calculation of y0 * (1-fract ) and y is in 13.27(q27) format */
        y = ((y0 * (0xFFFFF - fract)));
        /* Calculation of y1 * fract + y0 * (1-fract) and y is in 13.27(q27) format */
        y += (y1 * fract);
        /* convert y to 1.7(q7) format */
        return (q7_t) (y >> 20);
    }
}

/**
 * @} end of LinearInterpolate group
 */

/**
 * @brief  Fast approximation to the trigonometric sine function for floating-point data.
 * @param[in] x  input value in radians.
 * @return  sin(x).
 */
float32_t csi_sin_f32(
    float32_t x);


/**
 * @brief  Fast approximation to the trigonometric sine function for Q31 data.
 * @param[in] x  Scaled input value in radians.
 * @return  sin(x).
 */
q31_t csi_sin_q31(
    q31_t x);


/**
 * @brief  Fast approximation to the trigonometric sine function for Q15 data.
 * @param[in] x  Scaled input value in radians.
 * @return  sin(x).
 */
q15_t csi_sin_q15(
    q15_t x);


/**
 * @brief  Fast approximation to the trigonometric cosine function for floating-point data.
 * @param[in] x  input value in radians.
 * @return  cos(x).
 */
float32_t csi_cos_f32(
    float32_t x);


/**
 * @brief Fast approximation to the trigonometric cosine function for Q31 data.
 * @param[in] x  Scaled input value in radians.
 * @return  cos(x).
 */
q31_t csi_cos_q31(
    q31_t x);


/**
 * @brief  Fast approximation to the trigonometric cosine function for Q15 data.
 * @param[in] x  Scaled input value in radians.
 * @return  cos(x).
 */
q15_t csi_cos_q15(
    q15_t x);


/**
  @brief         Floating-point vector of log values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
void csi_vlog_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);

/**
  @brief         Floating-point vector of exp values.
  @param[in]     pSrc       points to the input vector
  @param[out]    pDst       points to the output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */
void csi_vexp_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);

/**
 * @ingroup groupFastMath
 */


/**
 * @defgroup SQRT Square Root
 *
 * Computes the square root of a number.
 * There are separate functions for Q15, Q31, and floating-point data types.
 * The square root function is computed using the Newton-Raphson algorithm.
 * This is an iterative algorithm of the form:
 * <pre>
 *      x1 = x0 - f(x0)/f'(x0)
 * </pre>
 * where <code>x1</code> is the current estimate,
 * <code>x0</code> is the previous estimate, and
 * <code>f'(x0)</code> is the derivative of <code>f()</code> evaluated at <code>x0</code>.
 * For the square root function, the algorithm reduces to:
 * <pre>
 *     x0 = in/2                         [initial guess]
 *     x1 = 1/2 * ( x0 + in / x0)        [each iteration]
 * </pre>
 */


/**
 * @addtogroup SQRT
 * @{
 */

/**
  @brief         Q15 square root function.
  @param[in]     in    input value.  The range of the input value is [0 +1) or 0x0000 to 0x7FFF
  @param[out]    pOut  points to square root of input value
  @return        execution status
                   - \ref CSI_MATH_SUCCESS        : input value is positive
                   - \ref CSI_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
csi_status csi_sqrt_q15(
    q15_t in,
    q15_t * pOut);

/**
  @brief         Floating-point square root function.
  @param[in]     in    input value
  @param[out]    pOut  square root of input value
  @return        execution status
                   - \ref CSI_MATH_SUCCESS        : input value is positive
                   - \ref CSI_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
#ifdef __riscv 
__STATIC_FORCEINLINE csi_status csi_sqrt_f32(
    float32_t in,
    float32_t * pOut)
{
    if (in >= 0.0f) {
#ifdef CSI_NEWTON_SQRTF
        float32_t eps = 0.000000011;
        float32_t val = in / 2;
        float32_t last;

        if (in <= eps) {
            *pOut = 0.0f;
        } else {
            do {
                last = val;
                val = (val + in / val) / 2;
            } while (fabsf(val - last) > eps);
            *pOut = val;
        }
#else
        *pOut = sqrtf(in);
#endif
        return (CSI_MATH_SUCCESS);
    } else {
        *pOut = 0.0f;
        return (CSI_MATH_ARGUMENT_ERROR);
    }
}
#else
csi_status csi_sqrt_f32(
    float32_t in,
    float32_t * pOut);
#endif


/**
  @brief		 Q31 square root function.
  @param[in]	 in    input value.  The range of the input value is [0 +1) or 0x00000000 to 0x7FFFFFFF
  @param[out]	 pOut  points to square root of input value
  @return		 execution status
				   - \ref CSI_MATH_SUCCESS		: input value is positive
				   - \ref CSI_MATH_ARGUMENT_ERROR : input value is negative; *pOut is set to 0
 */
csi_status csi_sqrt_q31(
    q31_t in,
    q31_t * pOut);

/**
 * @brief  Vector Floating-point square root function.
 * @param[in]  pIn   input vector.
 * @param[out] pOut  vector of square roots of input elements.
 * @param[in]  len   length of input vector.
 * @return The function returns CSI_MATH_SUCCESS if input value is positive value or CSI_MATH_ARGUMENT_ERROR if
 * <code>in</code> is negative value and returns zero output for negative values.
 */
#ifdef __csky__

void csi_vsqrt_f32(
    float32_t * pIn,
    float32_t * pOut,
    uint16_t len);

 void csi_vsqrt_q15(
    q15_t * 	pIn,
    q15_t * 	pOut,
    uint16_t	len);

void csi_vsqrt_q31(
    q31_t * 	pIn,
    q31_t * 	pOut,
    uint16_t	len);

void csi_vsqrt_q7(
    q7_t * 	pIn,
    q7_t * 	pOut,
    uint16_t	len);


#else
__STATIC_FORCEINLINE void csi_vsqrt_f32(
    float32_t * pIn,
    float32_t * pOut,
    uint16_t len)
{
    for (int i = 0; i < len; i++) {
        csi_sqrt_f32(pIn[i], pOut + i);
    }
}

__STATIC_FORCEINLINE void csi_vsqrt_q15(
    q15_t * 	pIn,
    q15_t * 	pOut,
    uint16_t	len
)
{
    for (int i = 0; i < len; i++) {
        csi_sqrt_q15(pIn[i], pOut + i);
    }
}
__STATIC_FORCEINLINE void csi_vsqrt_q31(
    q31_t * 	pIn,
    q31_t * 	pOut,
    uint16_t	len
)
{
    for (int i = 0; i < len; i++) {
        csi_sqrt_q31(pIn[i], pOut + i);
    }
}
#endif
/**
 * @} end of SQRT group
 */

/**
 * @brief floating-point Circular write function.
 a*/
#ifndef __csky__
__STATIC_FORCEINLINE void csi_circularWrite_f32(
    int32_t * circBuffer,
    int32_t L,
    uint16_t * writeOffset,
    int32_t bufferInc,
    const int32_t * src,
    int32_t srcInc,
    uint32_t blockSize)
{
    uint32_t i = 0U;
    int32_t wOffset;
    /* Copy the value of Index pointer that points
     * to the current location where the input samples to be copied */
    wOffset = *writeOffset;
    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U) {
        /* copy the input sample to the circular buffer */
        circBuffer[wOffset] = *src;
        /* Update the input pointer */
        src += srcInc;
        /* Circularly update wOffset.  Watch out for positive and negative value */
        wOffset += bufferInc;

        if (wOffset >= L)
            wOffset -= L;

        /* Decrement the loop counter */
        i--;
    }

    /* Update the index pointer */
    *writeOffset = (uint16_t)wOffset;
}



/**
 * @brief floating-point Circular Read function.
 */
__STATIC_FORCEINLINE void csi_circularRead_f32(
    int32_t * circBuffer,
    int32_t L,
    int32_t * readOffset,
    int32_t bufferInc,
    int32_t * dst,
    int32_t * dst_base,
    int32_t dst_length,
    int32_t dstInc,
    uint32_t blockSize)
{
    uint32_t i = 0U;
    int32_t rOffset;
    int32_t* dst_end;
    /* Copy the value of Index pointer that points
     * to the current location from where the input samples to be read */
    rOffset = *readOffset;
    dst_end = dst_base + dst_length;
    /* Loop over the blockSize */
    i = blockSize;

    while (i > 0U) {
        /* copy the sample from the circular buffer to the destination buffer */
        *dst = circBuffer[rOffset];
        /* Update the input pointer */
        dst += dstInc;

        if (dst == dst_end) {
            dst = dst_base;
        }

        /* Circularly update rOffset.  Watch out for positive and negative value  */
        rOffset += bufferInc;

        if (rOffset >= L) {
            rOffset -= L;
        }

        /* Decrement the loop counter */
        i--;
    }

    /* Update the index pointer */
    *readOffset = rOffset;
}
#endif
/**
 * @brief  Sum of the squares of the elements of a Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_power_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q63_t * pResult);

void csi_power_int32(
    int32_t * pSrc,
    uint32_t blockSize,
    q63_t * pResult);


/**
 * @brief  Sum of the squares of the elements of a floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_power_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult);


/**
 * @brief  Sum of the squares of the elements of a Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_power_q15(
    const q15_t * pSrc,
    uint32_t blockSize,
    q63_t * pResult);


/**
 * @brief  Sum of the squares of the elements of a Q7 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_power_q7(
    const q7_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult);


/**
 * @brief  Mean value of a Q7 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_mean_q7(
    const q7_t * pSrc,
    uint32_t blockSize,
    q7_t * pResult);


/**
 * @brief  Mean value of a Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_mean_q15(
    const q15_t * pSrc,
    uint32_t blockSize,
    q15_t * pResult);


/**
 * @brief  Mean value of a Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_mean_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult);


/**
 * @brief  Mean value of a floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_mean_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult);


/**
 * @brief  Variance of the elements of a floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_var_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult);


/**
 * @brief  Variance of the elements of a Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_var_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult);


/**
 * @brief  Variance of the elements of a Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_var_q15(
    const q15_t * pSrc,
    uint32_t blockSize,
    q15_t * pResult);


/**
 * @brief  Root Mean Square of the elements of a floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_rms_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult);


/**
 * @brief  Root Mean Square of the elements of a Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_rms_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult);


/**
 * @brief  Root Mean Square of the elements of a Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_rms_q15(
    const q15_t * pSrc,
    uint32_t blockSize,
    q15_t * pResult);


/**
 * @brief  Standard deviation of the elements of a floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_std_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult);


/**
 * @brief  Standard deviation of the elements of a Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_std_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult);


/**
 * @brief  Standard deviation of the elements of a Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output value.
 */
void csi_std_q15(
    const q15_t * pSrc,
    uint32_t blockSize,
    q15_t * pResult);


/**
 * @brief  Floating-point complex magnitude
 * @param[in]  pSrc        points to the complex input vector
 * @param[out] pDst        points to the real output vector
 * @param[in]  numSamples  number of complex samples in the input vector
 */
void csi_cmplx_mag_f32(
    const float32_t * pSrc,
    float32_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q31 complex magnitude
 * @param[in]  pSrc        points to the complex input vector
 * @param[out] pDst        points to the real output vector
 * @param[in]  numSamples  number of complex samples in the input vector
 */
void csi_cmplx_mag_q31(
    const q31_t * pSrc,
    q31_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q15 complex magnitude
 * @param[in]  pSrc        points to the complex input vector
 * @param[out] pDst        points to the real output vector
 * @param[in]  numSamples  number of complex samples in the input vector
 */
void csi_cmplx_mag_q15(
    const q15_t * pSrc,
    q15_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q15 complex dot product
 * @param[in]  pSrcA       points to the first input vector
 * @param[in]  pSrcB       points to the second input vector
 * @param[in]  numSamples  number of complex samples in each vector
 * @param[out] realResult  real part of the result returned here
 * @param[out] imagResult  imaginary part of the result returned here
 */
void csi_cmplx_dot_prod_q15(
    const q15_t * pSrcA,
    const q15_t * pSrcB,
    uint32_t numSamples,
    q31_t * realResult,
    q31_t * imagResult);


/**
 * @brief  Q31 complex dot product
 * @param[in]  pSrcA       points to the first input vector
 * @param[in]  pSrcB       points to the second input vector
 * @param[in]  numSamples  number of complex samples in each vector
 * @param[out] realResult  real part of the result returned here
 * @param[out] imagResult  imaginary part of the result returned here
 */
void csi_cmplx_dot_prod_q31(
    const q31_t * pSrcA,
    const q31_t * pSrcB,
    uint32_t numSamples,
    q63_t * realResult,
    q63_t * imagResult);

 void csi_dot_prod_u64xu8(
    uint8_t  * pSrcA,
    uint64_t * pSrcB,
    uint32_t blockSize,
    uint64_t * result);

/**
 * @brief  Floating-point complex dot product
 * @param[in]  pSrcA       points to the first input vector
 * @param[in]  pSrcB       points to the second input vector
 * @param[in]  numSamples  number of complex samples in each vector
 * @param[out] realResult  real part of the result returned here
 * @param[out] imagResult  imaginary part of the result returned here
 */
void csi_cmplx_dot_prod_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    uint32_t numSamples,
    float32_t * realResult,
    float32_t * imagResult);


/**
 * @brief  Q15 complex-by-real multiplication
 * @param[in]  pSrcCmplx   points to the complex input vector
 * @param[in]  pSrcReal    points to the real input vector
 * @param[out] pCmplxDst   points to the complex output vector
 * @param[in]  numSamples  number of samples in each vector
 */
void csi_cmplx_mult_real_q15(
    const q15_t * pSrcCmplx,
    const q15_t * pSrcReal,
    q15_t * pCmplxDst,
    uint32_t numSamples);


/**
 * @brief  Q31 complex-by-real multiplication
 * @param[in]  pSrcCmplx   points to the complex input vector
 * @param[in]  pSrcReal    points to the real input vector
 * @param[out] pCmplxDst   points to the complex output vector
 * @param[in]  numSamples  number of samples in each vector
 */
void csi_cmplx_mult_real_q31(
    const q31_t * pSrcCmplx,
    const q31_t * pSrcReal,
    q31_t * pCmplxDst,
    uint32_t numSamples);


/**
 * @brief  Floating-point complex-by-real multiplication
 * @param[in]  pSrcCmplx   points to the complex input vector
 * @param[in]  pSrcReal    points to the real input vector
 * @param[out] pCmplxDst   points to the complex output vector
 * @param[in]  numSamples  number of samples in each vector
 */
void csi_cmplx_mult_real_f32(
    const float32_t * pSrcCmplx,
    const float32_t * pSrcReal,
    float32_t * pCmplxDst,
    uint32_t numSamples);


/**
 * @brief  Minimum value of a Q7 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] result     is output pointer
 * @param[in]  index      is the array index of the minimum value in the input buffer.
 */
void csi_min_q7(
    const q7_t * pSrc,
    uint16_t blockSize,
    q7_t * result,
    uint16_t * index);


/**
 * @brief  Minimum value of a Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output pointer
 * @param[in]  pIndex     is the array index of the minimum value in the input buffer.
 */
void csi_min_q15(
    const q15_t * pSrc,
    uint16_t blockSize,
    q15_t * pResult,
    uint16_t * pIndex);


/**
 * @brief  Minimum value of a Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output pointer
 * @param[out] pIndex     is the array index of the minimum value in the input buffer.
 */
void csi_min_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult,
    uint32_t * pIndex);


/**
 * @brief  Minimum value of a floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[in]  blockSize  is the number of samples to process
 * @param[out] pResult    is output pointer
 * @param[out] pIndex     is the array index of the minimum value in the input buffer.
 */
void csi_min_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult,
    uint32_t * pIndex);


/**
 * @brief Maximum value of a Q7 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
void csi_max_q7(
    const q7_t * pSrc,
    uint16_t blockSize,
    q7_t * pResult,
    uint16_t * pIndex);


/**
 * @brief Maximum value of a Q15 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
void csi_max_q15(
    const q15_t * pSrc,
    uint16_t blockSize,
    q15_t * pResult,
    uint16_t * pIndex);


/**
 * @brief Maximum value of a Q31 vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
void csi_max_q31(
    const q31_t * pSrc,
    uint32_t blockSize,
    q31_t * pResult,
    uint32_t * pIndex);


/**
 * @brief Maximum value of a floating-point vector.
 * @param[in]  pSrc       points to the input buffer
 * @param[in]  blockSize  length of the input vector
 * @param[out] pResult    maximum value returned here
 * @param[out] pIndex     index of maximum value returned here
 */
void csi_max_f32(
    const float32_t * pSrc,
    uint32_t blockSize,
    float32_t * pResult,
    uint32_t * pIndex);

/**
  @brief         Maximum value of a floating-point vector.
  @param[in]     pSrc       points to the input vector
  @param[in]     blockSize  number of samples in input vector
  @param[out]    pResult    maximum value returned here
  @return        none
 */
void csi_max_no_idx_f32(
    const float32_t *pSrc,
    uint32_t   blockSize,
    float32_t *pResult);

/**
 * @brief  Q15 complex-by-complex multiplication
 * @param[in]  pSrcA       points to the first input vector
 * @param[in]  pSrcB       points to the second input vector
 * @param[out] pDst        points to the output vector
 * @param[in]  numSamples  number of complex samples in each vector
 */
void csi_cmplx_mult_cmplx_q15(
    const q15_t * pSrcA,
    const q15_t * pSrcB,
    q15_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Q31 complex-by-complex multiplication
 * @param[in]  pSrcA       points to the first input vector
 * @param[in]  pSrcB       points to the second input vector
 * @param[out] pDst        points to the output vector
 * @param[in]  numSamples  number of complex samples in each vector
 */
void csi_cmplx_mult_cmplx_q31(
    const q31_t * pSrcA,
    const q31_t * pSrcB,
    q31_t * pDst,
    uint32_t numSamples);


/**
 * @brief  Floating-point complex-by-complex multiplication
 * @param[in]  pSrcA       points to the first input vector
 * @param[in]  pSrcB       points to the second input vector
 * @param[out] pDst        points to the output vector
 * @param[in]  numSamples  number of complex samples in each vector
 */
void csi_cmplx_mult_cmplx_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    float32_t * pDst,
    uint32_t numSamples);

void csi_cmplx_mult_cmplx_re_f32(
    const float32_t * pSrcA,
    const float32_t * pSrcB,
    float32_t * pDst,
    uint32_t numSamples);


/**
 * @brief Converts the elements of the floating-point vector to Q31 vector.
 * @param[in]  pSrc       points to the floating-point input vector
 * @param[out] pDst       points to the Q31 output vector
 * @param[in]  blockSize  length of the input vector
 */
void csi_float_to_q31(
    const float32_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief Converts the elements of the floating-point vector to Q15 vector.
 * @param[in]  pSrc       points to the floating-point input vector
 * @param[out] pDst       points to the Q15 output vector
 * @param[in]  blockSize  length of the input vector
 */
void csi_float_to_q15(
    const float32_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief Converts the elements of the floating-point vector to Q7 vector.
 * @param[in]  pSrc       points to the floating-point input vector
 * @param[out] pDst       points to the Q7 output vector
 * @param[in]  blockSize  length of the input vector
 */
void csi_float_to_q7(
    const float32_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q31 vector to floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q31_to_float(
    const q31_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q31 vector to Q15 vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q31_to_q15(
    const q31_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);

void csi_q31_to_q7_rs(
    q31_t * pSrc,
    q7_t * pDst,
    uint32_t shiftValue,
    uint32_t blockSize);

void csi_q63_to_q31_rs(
    q63_t * pSrc,
    q31_t * pDst,
    uint32_t shiftValue,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q31 vector to Q7 vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q31_to_q7(
    const q31_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q15 vector to floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q15_to_float(
    const q15_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q15 vector to Q31 vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q15_to_q31(
    const q15_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q15 vector to Q7 vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q15_to_q7(
    const q15_t * pSrc,
    q7_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q7 vector to floating-point vector.
 * @param[in]  pSrc       is input pointer
 * @param[out] pDst       is output pointer
 * @param[in]  blockSize  is the number of samples to process
 */
void csi_q7_to_float(
    const q7_t * pSrc,
    float32_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q7 vector to Q31 vector.
 * @param[in]  pSrc       input pointer
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_q7_to_q31(
    const q7_t * pSrc,
    q31_t * pDst,
    uint32_t blockSize);


/**
 * @brief  Converts the elements of the Q7 vector to Q15 vector.
 * @param[in]  pSrc       input pointer
 * @param[out] pDst       output pointer
 * @param[in]  blockSize  number of samples to process
 */
void csi_q7_to_q15(
    const q7_t * pSrc,
    q15_t * pDst,
    uint32_t blockSize);


/**
 * @brief        SVM linear instance init function
 * @param[in]    S                      Parameters for SVM functions
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @return none.
 *
 */


void csi_svm_linear_init_f32(csi_svm_linear_instance_f32 *S,
                               uint32_t nbOfSupportVectors,
                               uint32_t vectorDimension,
                               float32_t intercept,
                               const float32_t *dualCoefficients,
                               const float32_t *supportVectors,
                               const int32_t  *classes);

/**
 * @brief SVM linear prediction
 * @param[in]    S          Pointer to an instance of the linear SVM structure.
 * @param[in]    in         Pointer to input vector
 * @param[out]   pResult    Decision value
 * @return none.
 *
 */

void csi_svm_linear_predict_f32(const csi_svm_linear_instance_f32 *S,
                                  const float32_t * in,
                                  int32_t * pResult);


/**
 * @brief        SVM polynomial instance init function
 * @param[in]    S                      points to an instance of the polynomial SVM structure.
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @param[in]    degree                 Polynomial degree
 * @param[in]    coef0                  coeff0 (scikit-learn terminology)
 * @param[in]    gamma                  gamma (scikit-learn terminology)
 * @return none.
 *
 */


void csi_svm_polynomial_init_f32(csi_svm_polynomial_instance_f32 *S,
                                   uint32_t nbOfSupportVectors,
                                   uint32_t vectorDimension,
                                   float32_t intercept,
                                   const float32_t *dualCoefficients,
                                   const float32_t *supportVectors,
                                   const int32_t   *classes,
                                   int32_t      degree,
                                   float32_t coef0,
                                   float32_t gamma
                                  );

/**
 * @brief SVM polynomial prediction
 * @param[in]    S          Pointer to an instance of the polynomial SVM structure.
 * @param[in]    in         Pointer to input vector
 * @param[out]   pResult    Decision value
 * @return none.
 *
 */
void csi_svm_polynomial_predict_f32(const csi_svm_polynomial_instance_f32 *S,
                                      const float32_t * in,
                                      int32_t * pResult);


/**
 * @brief        SVM radial basis function instance init function
 * @param[in]    S                      points to an instance of the polynomial SVM structure.
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @param[in]    gamma                  gamma (scikit-learn terminology)
 * @return none.
 *
 */

void csi_svm_rbf_init_f32(csi_svm_rbf_instance_f32 *S,
                            uint32_t nbOfSupportVectors,
                            uint32_t vectorDimension,
                            float32_t intercept,
                            const float32_t *dualCoefficients,
                            const float32_t *supportVectors,
                            const int32_t   *classes,
                            float32_t gamma
                           );

/**
 * @brief SVM rbf prediction
 * @param[in]    S         Pointer to an instance of the rbf SVM structure.
 * @param[in]    in        Pointer to input vector
 * @param[out]   pResult   decision value
 * @return none.
 *
 */
void csi_svm_rbf_predict_f32(const csi_svm_rbf_instance_f32 *S,
                               const float32_t * in,
                               int32_t * pResult);

/**
 * @brief        SVM sigmoid instance init function
 * @param[in]    S                      points to an instance of the rbf SVM structure.
 * @param[in]    nbOfSupportVectors     Number of support vectors
 * @param[in]    vectorDimension        Dimension of vector space
 * @param[in]    intercept              Intercept
 * @param[in]    dualCoefficients       Array of dual coefficients
 * @param[in]    supportVectors         Array of support vectors
 * @param[in]    classes                Array of 2 classes ID
 * @param[in]    coef0                  coeff0 (scikit-learn terminology)
 * @param[in]    gamma                  gamma (scikit-learn terminology)
 * @return none.
 *
 */

void csi_svm_sigmoid_init_f32(csi_svm_sigmoid_instance_f32 *S,
                                uint32_t nbOfSupportVectors,
                                uint32_t vectorDimension,
                                float32_t intercept,
                                const float32_t *dualCoefficients,
                                const float32_t *supportVectors,
                                const int32_t   *classes,
                                float32_t coef0,
                                float32_t gamma
                               );

/**
 * @brief SVM sigmoid prediction
 * @param[in]    S        Pointer to an instance of the rbf SVM structure.
 * @param[in]    in       Pointer to input vector
 * @param[out]   pResult  Decision value
 * @return none.
 *
 */
void csi_svm_sigmoid_predict_f32(const csi_svm_sigmoid_instance_f32 *S,
                                   const float32_t * in,
                                   int32_t * pResult);


/**
 * @brief Naive Gaussian Bayesian Estimator
 *
 * @param[in]  S         points to a naive bayes instance structure
 * @param[in]  in        points to the elements of the input vector.
 * @param[in]  pBuffer   points to a buffer of length numberOfClasses
 * @return The predicted class
 *
 */


uint32_t csi_gaussian_naive_bayes_predict_f32(const csi_gaussian_naive_bayes_instance_f32 *S,
        const float32_t * in,
        float32_t *pBuffer);

/**
 * @brief Computation of the LogSumExp
 *
 * In probabilistic computations, the dynamic of the probability values can be very
 * wide because they come from gaussian functions.
 * To avoid underflow and overflow issues, the values are represented by their log.
 * In this representation, multiplying the original exp values is easy : their logs are added.
 * But adding the original exp values is requiring some special handling and it is the
 * goal of the LogSumExp function.
 *
 * If the values are x1...xn, the function is computing:
 *
 * ln(exp(x1) + ... + exp(xn)) and the computation is done in such a way that
 * rounding issues are minimised.
 *
 * The max xm of the values is extracted and the function is computing:
 * xm + ln(exp(x1 - xm) + ... + exp(xn - xm))
 *
 * @param[in]  *in         Pointer to an array of input values.
 * @param[in]  blockSize   Number of samples in the input array.
 * @return LogSumExp
 *
 */


float32_t csi_logsumexp_f32(const float32_t *in, uint32_t blockSize);

/**
 * @brief Dot product with log arithmetic
 *
 * Vectors are containing the log of the samples
 *
 * @param[in]       pSrcA points to the first input vector
 * @param[in]       pSrcB points to the second input vector
 * @param[in]       blockSize number of samples in each vector
 * @param[in]       pTmpBuffer temporary buffer of length blockSize
 * @return The log of the dot product .
 *
 */


float32_t csi_logsumexp_dot_prod_f32(const float32_t * pSrcA,
                                       const float32_t * pSrcB,
                                       uint32_t blockSize,
                                       float32_t *pTmpBuffer);

/**
 * @brief Entropy
 *
 * @param[in]  pSrcA        Array of input values.
 * @param[in]  blockSize    Number of samples in the input array.
 * @return     Entropy      -Sum(p ln p)
 *
 */


float32_t csi_entropy_f32(const float32_t * pSrcA,uint32_t blockSize);


/**
 * @brief Kullback-Leibler
 *
 * @param[in]  pSrcA         Pointer to an array of input values for probability distribution A.
 * @param[in]  pSrcB         Pointer to an array of input values for probability distribution B.
 * @param[in]  blockSize     Number of samples in the input array.
 * @return Kullback-Leibler  Divergence D(A || B)
 *
 */
float32_t csi_kullback_leibler_f32(const float32_t * pSrcA
                                     ,const float32_t * pSrcB
                                     ,uint32_t blockSize);


/**
 * @brief Weighted sum
 *
 *
 * @param[in]    *in           Array of input values.
 * @param[in]    *weigths      Weights
 * @param[in]    blockSize     Number of samples in the input array.
 * @return Weighted sum
 *
 */
float32_t csi_weighted_sum_f32(const float32_t *in
                                 , const float32_t *weigths
                                 , uint32_t blockSize);


/**
 * @brief Barycenter
 *
 *
 * @param[in]    in         List of vectors
 * @param[in]    weights    Weights of the vectors
 * @param[out]   out        Barycenter
 * @param[in]    nbVectors  Number of vectors
 * @param[in]    vecDim     Dimension of space (vector dimension)
 * @return       None
 *
 */
void csi_barycenter_f32(const float32_t *in
                          , const float32_t *weights
                          , float32_t *out
                          , uint32_t nbVectors
                          , uint32_t vecDim);

/**
 * @brief        Euclidean distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

float32_t csi_euclidean_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);

/**
 * @brief        Bray-Curtis distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
float32_t csi_braycurtis_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);

/**
 * @brief        Canberra distance between two vectors
 *
 * This function may divide by zero when samples pA[i] and pB[i] are both zero.
 * The result of the computation will be correct. So the division per zero may be
 * ignored.
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
float32_t csi_canberra_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);


/**
 * @brief        Chebyshev distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
float32_t csi_chebyshev_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);


/**
 * @brief        Cityblock (Manhattan) distance between two vectors
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
float32_t csi_cityblock_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);

/**
 * @brief        Correlation distance between two vectors
 *
 * The input vectors are modified in place !
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */
float32_t csi_correlation_distance_f32(float32_t *pA,float32_t *pB, uint32_t blockSize);

/**
 * @brief        Cosine distance between two vectors
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

float32_t csi_cosine_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);

/**
 * @brief        Jensen-Shannon distance between two vectors
 *
 * This function is assuming that elements of second vector are > 0
 * and 0 only when the corresponding element of first vector is 0.
 * Otherwise the result of the computation does not make sense
 * and for speed reasons, the cases returning NaN or Infinity are not
 * managed.
 *
 * When the function is computing x log (x / y) with x 0 and y 0,
 * it will compute the right value (0) but a division per zero will occur
 * and shoudl be ignored in client code.
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */

float32_t csi_jensenshannon_distance_f32(const float32_t *pA,const float32_t *pB,uint32_t blockSize);

/**
 * @brief        Minkowski distance between two vectors
 *
 * @param[in]    pA         First vector
 * @param[in]    pB         Second vector
 * @param[in]    n          Norm order (>= 2)
 * @param[in]    blockSize  vector length
 * @return distance
 *
 */



float32_t csi_minkowski_distance_f32(const float32_t *pA,const float32_t *pB, int32_t order, uint32_t blockSize);

/**
 * @brief        Dice distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    order           Distance order
 * @param[in]    blockSize       Number of samples
 * @return distance
 *
 */


float32_t csi_dice_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Hamming distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_hamming_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Jaccard distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_jaccard_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Kulsinski distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_kulsinski_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Roger Stanimoto distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_rogerstanimoto_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Russell-Rao distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_russellrao_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Sokal-Michener distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_sokalmichener_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Sokal-Sneath distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_sokalsneath_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

/**
 * @brief        Yule distance between two vectors
 *
 * @param[in]    pA              First vector of packed booleans
 * @param[in]    pB              Second vector of packed booleans
 * @param[in]    numberOfBools   Number of booleans
 * @return distance
 *
 */

float32_t csi_yule_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);


/**
 * @ingroup groupInterpolation
 */

/**
 * @defgroup BilinearInterpolate Bilinear Interpolation
 *
 * Bilinear interpolation is an extension of linear interpolation applied to a two dimensional grid.
 * The underlying function <code>f(x, y)</code> is sampled on a regular grid and the interpolation process
 * determines values between the grid points.
 * Bilinear interpolation is equivalent to two step linear interpolation, first in the x-dimension and then in the y-dimension.
 * Bilinear interpolation is often used in image processing to rescale images.
 * The library provides bilinear interpolation functions for Q7, Q15, Q31, and floating-point data types.
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
 * } csi_bilinear_interp_instance_f32;
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
__STATIC_FORCEINLINE float32_t csi_bilinear_interp_f32(
    const csi_bilinear_interp_instance_f32 * S,
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
    if (xIndex < 0 || xIndex > (S->numRows - 1) || yIndex < 0 || yIndex > (S->numCols - 1)) {
        return (0);
    }

    /* Calculation of index for two nearest points in X-direction */
    index = (xIndex - 1) + (yIndex - 1) * S->numCols;
    /* Read two nearest points in X-direction */
    f00 = pData[index];
    f01 = pData[index + 1];
    /* Calculation of index for two nearest points in Y-direction */
    index = (xIndex - 1) + (yIndex) * S->numCols;
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
* @brief  Q31 bilinear interpolation.
* @param[in,out] S  points to an instance of the interpolation structure.
* @param[in]     X  interpolation coordinate in 12.20 format.
* @param[in]     Y  interpolation coordinate in 12.20 format.
* @return out interpolated value.
*/
__STATIC_FORCEINLINE q31_t csi_bilinear_interp_q31(
    csi_bilinear_interp_instance_q31 * S,
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
    if (rI < 0 || rI > (S->numRows - 1) || cI < 0 || cI > (S->numCols - 1)) {
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
* @brief  Q15 bilinear interpolation.
* @param[in,out] S  points to an instance of the interpolation structure.
* @param[in]     X  interpolation coordinate in 12.20 format.
* @param[in]     Y  interpolation coordinate in 12.20 format.
* @return out interpolated value.
*/
__STATIC_FORCEINLINE q15_t csi_bilinear_interp_q15(
    csi_bilinear_interp_instance_q15 * S,
    q31_t X,
    q31_t Y)
{
    q63_t acc = 0;                               /* output */
    q31_t out;                                   /* Temporary output */
    q15_t x1, x2, y1, y2;                        /* Nearest output values */
    q31_t xfract, yfract;                        /* X, Y fractional parts */
    int32_t rI, cI;                              /* Row and column indices */
    q15_t *pYData = S->pData;                    /* pointer to output table values */
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
    if (rI < 0 || rI > (S->numRows - 1) || cI < 0 || cI > (S->numCols - 1)) {
        return (0);
    }

    /* 20 bits for the fractional part */
    /* xfract should be in 12.20 format */
    xfract = (X & 0x000FFFFF);
    /* Read two nearest output values from the index */
    x1 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI)    ];
    x2 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI) + 1];
    /* 20 bits for the fractional part */
    /* yfract should be in 12.20 format */
    yfract = (Y & 0x000FFFFF);
    /* Read two nearest output values from the index */
    y1 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI + 1)    ];
    y2 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI + 1) + 1];
    /* Calculation of x1 * (1-xfract ) * (1-yfract) and acc is in 13.51 format */
    /* x1 is in 1.15(q15), xfract in 12.20 format and out is in 13.35 format */
    /* convert 13.35 to 13.31 by right shifting  and out is in 1.31 */
    out = (q31_t) (((q63_t) x1 * (0xFFFFF - xfract)) >> 4U);
    acc = ((q63_t) out * (0xFFFFF - yfract));
    /* x2 * (xfract) * (1-yfract)  in 1.51 and adding to acc */
    out = (q31_t) (((q63_t) x2 * (0xFFFFF - yfract)) >> 4U);
    acc += ((q63_t) out * (xfract));
    /* y1 * (1 - xfract) * (yfract)  in 1.51 and adding to acc */
    out = (q31_t) (((q63_t) y1 * (0xFFFFF - xfract)) >> 4U);
    acc += ((q63_t) out * (yfract));
    /* y2 * (xfract) * (yfract)  in 1.51 and adding to acc */
    out = (q31_t) (((q63_t) y2 * (xfract)) >> 4U);
    acc += ((q63_t) out * (yfract));
    /* acc is in 13.51 format and down shift acc by 36 times */
    /* Convert out to 1.15 format */
    return ((q15_t)(acc >> 36));
}


/**
* @brief  Q7 bilinear interpolation.
* @param[in,out] S  points to an instance of the interpolation structure.
* @param[in]     X  interpolation coordinate in 12.20 format.
* @param[in]     Y  interpolation coordinate in 12.20 format.
* @return out interpolated value.
*/
__STATIC_FORCEINLINE q7_t csi_bilinear_interp_q7(
    csi_bilinear_interp_instance_q7 * S,
    q31_t X,
    q31_t Y)
{
    q63_t acc = 0;                               /* output */
    q31_t out;                                   /* Temporary output */
    q31_t xfract, yfract;                        /* X, Y fractional parts */
    q7_t x1, x2, y1, y2;                         /* Nearest output values */
    int32_t rI, cI;                              /* Row and column indices */
    q7_t *pYData = S->pData;                     /* pointer to output table values */
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
    if (rI < 0 || rI > (S->numRows - 1) || cI < 0 || cI > (S->numCols - 1)) {
        return (0);
    }

    /* 20 bits for the fractional part */
    /* xfract should be in 12.20 format */
    xfract = (X & (q31_t)0x000FFFFF);
    /* Read two nearest output values from the index */
    x1 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI)    ];
    x2 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI) + 1];
    /* 20 bits for the fractional part */
    /* yfract should be in 12.20 format */
    yfract = (Y & (q31_t)0x000FFFFF);
    /* Read two nearest output values from the index */
    y1 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI + 1)    ];
    y2 = pYData[((uint32_t)rI) + nCols * ((uint32_t)cI + 1) + 1];
    /* Calculation of x1 * (1-xfract ) * (1-yfract) and acc is in 16.47 format */
    out = ((x1 * (0xFFFFF - xfract)));
    acc = (((q63_t) out * (0xFFFFF - yfract)));
    /* x2 * (xfract) * (1-yfract)  in 2.22 and adding to acc */
    out = ((x2 * (0xFFFFF - yfract)));
    acc += (((q63_t) out * (xfract)));
    /* y1 * (1 - xfract) * (yfract)  in 2.22 and adding to acc */
    out = ((y1 * (0xFFFFF - xfract)));
    acc += (((q63_t) out * (yfract)));
    /* y2 * (xfract) * (yfract)  in 2.22 and adding to acc */
    out = ((y2 * (yfract)));
    acc += (((q63_t) out * (xfract)));
    /* acc in 16.47 format and down shift by 40 to convert to 1.7 format */
    return ((q7_t)(acc >> 40));
}

/**
 * @} end of BilinearInterpolate group
 */

#ifdef   __cplusplus
}
#endif


#endif /* _CSI_MATH_H */

/**
 *
 * End of file.
 */
