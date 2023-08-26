/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_cmplx_mult_f16.c
 * Description:  Floating-point matrix multiplication
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

#include "dsp/matrix_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)


/**
  @ingroup groupMatrix
 */


/**
  @addtogroup CmplxMatrixMult
  @{
 */

/**
  @brief         Floating-point Complex matrix multiplication.
  @param[in]     pSrcA      points to first input complex matrix structure
  @param[in]     pSrcB      points to second input complex matrix structure
  @param[out]    pDst       points to output complex matrix structure
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) && defined(__CMSIS_GCC_H)
#pragma GCC warning "Scalar version of arm_mat_cmplx_mult_f16 built. Helium version has build issues with gcc."
#endif 

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE) &&  !defined(__CMSIS_GCC_H)

#include "arm_helium_utils.h"

#define DONTCARE            0 /* inactive lane content */


__STATIC_FORCEINLINE arm_status arm_mat_cmplx_mult_f16_2x2_mve(
    const arm_matrix_instance_f16 * pSrcA,
    const arm_matrix_instance_f16 * pSrcB,
    arm_matrix_instance_f16 * pDst)
{
#define MATRIX_DIM 2
    float16_t const *pInB = pSrcB->pData;  /* input data matrix pointer B */
    float16_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    float16_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint16x8_t     vecColBOffs0,vecColAOffs0,vecColAOffs1;
    float16_t       *pInA0 = pInA;
    f16x8_t        acc0, acc1;
    f16x8_t        vecB, vecA0, vecA1;
    f16x8_t        vecTmp;
    uint16_t         tmp;
    static const uint16_t offsetB0[8] = { 0, 1,
        MATRIX_DIM * CMPLX_DIM, MATRIX_DIM * CMPLX_DIM + 1,
        2, 3,
        MATRIX_DIM * CMPLX_DIM + 2 , MATRIX_DIM * CMPLX_DIM + 3,
    };


    vecColBOffs0 = vldrhq_u16((uint16_t const *) offsetB0);

    tmp = 0;
    vecColAOffs0 = viwdupq_u16(tmp, 4, 1);

    tmp = (CMPLX_DIM * MATRIX_DIM);
    vecColAOffs1 = vecColAOffs0 + (uint16_t)(CMPLX_DIM * MATRIX_DIM);


    pInB = (float16_t const *)pSrcB->pData;

    vecA0 = vldrhq_gather_shifted_offset_f16(pInA0, vecColAOffs0);
    vecA1 = vldrhq_gather_shifted_offset_f16(pInA0, vecColAOffs1);


    vecB = vldrhq_gather_shifted_offset(pInB, vecColBOffs0);

    acc0 = vcmulq(vecA0, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA0, vecB);

    acc1 = vcmulq(vecA1, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA1, vecB);


    /*
     * Compute
     *  re0+re1 | im0+im1 | re0+re1 | im0+im1
     *  re2+re3 | im2+im3 | re2+re3 | im2+im3
     */

    vecTmp = (f16x8_t) vrev64q_s32((int32x4_t) acc0);
    vecTmp = vaddq(vecTmp, acc0);


    *(float32_t *)(&pOut[0 * CMPLX_DIM * MATRIX_DIM]) = ((f32x4_t)vecTmp)[0];
    *(float32_t *)(&pOut[0 * CMPLX_DIM * MATRIX_DIM + CMPLX_DIM]) = ((f32x4_t)vecTmp)[2];

    vecTmp = (f16x8_t) vrev64q_s32((int32x4_t) acc1);
    vecTmp = vaddq(vecTmp, acc1);

    *(float32_t *)(&pOut[1 * CMPLX_DIM * MATRIX_DIM]) = ((f32x4_t)vecTmp)[0];
    *(float32_t *)(&pOut[1 * CMPLX_DIM * MATRIX_DIM + CMPLX_DIM]) = ((f32x4_t)vecTmp)[2];

    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
#undef MATRIX_DIM
}



__STATIC_FORCEINLINE arm_status arm_mat_cmplx_mult_f16_3x3_mve(
    const arm_matrix_instance_f16 * pSrcA,
    const arm_matrix_instance_f16 * pSrcB,
    arm_matrix_instance_f16 * pDst)
{
#define MATRIX_DIM 3
    float16_t const *pInB = pSrcB->pData;  /* input data matrix pointer B */
    float16_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    float16_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint16x8_t     vecColBOffs0;
    float16_t       *pInA0 = pInA;
    float16_t       *pInA1 = pInA0 + CMPLX_DIM * MATRIX_DIM;
    float16_t       *pInA2 = pInA1 + CMPLX_DIM * MATRIX_DIM;
    f16x8_t        acc0, acc1, acc2;
    f16x8_t        vecB, vecA0, vecA1, vecA2;
    static const uint16_t offsetB0[8] = { 0, 1,
        MATRIX_DIM * CMPLX_DIM, MATRIX_DIM * CMPLX_DIM + 1,
        2 * MATRIX_DIM * CMPLX_DIM, 2 * MATRIX_DIM * CMPLX_DIM + 1,
        DONTCARE, DONTCARE
    };

    
    /* enable predication to disable upper half complex vector element */
    mve_pred16_t p0 = vctp16q(MATRIX_DIM * CMPLX_DIM);

    vecColBOffs0 = vldrhq_u16((uint16_t const *) offsetB0);

    pInB = (float16_t const *)pSrcB->pData;

    vecA0 = vldrhq_f16(pInA0);
    vecA1 = vldrhq_f16(pInA1);
    vecA2 = vldrhq_f16(pInA2);

    vecB = vldrhq_gather_shifted_offset_z(pInB, vecColBOffs0, p0);

    acc0 = vcmulq(vecA0, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA0, vecB);

    acc1 = vcmulq(vecA1, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA1, vecB);

    acc2 = vcmulq(vecA2, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA2, vecB);

    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    pOut += CMPLX_DIM;
    /*
     * move to next B column
     */
    pInB = pInB + CMPLX_DIM;

    vecB = vldrhq_gather_shifted_offset_z(pInB, vecColBOffs0, p0);

    acc0 = vcmulq(vecA0, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA0, vecB);

    acc1 = vcmulq(vecA1, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA1, vecB);

    acc2 = vcmulq(vecA2, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA2, vecB);

    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    pOut += CMPLX_DIM;
    /*
     * move to next B column
     */
    pInB = pInB + CMPLX_DIM;

    vecB = vldrhq_gather_shifted_offset_z(pInB, vecColBOffs0, p0);

    acc0 = vcmulq(vecA0, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA0, vecB);

    acc1 = vcmulq(vecA1, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA1, vecB);

    acc2 = vcmulq(vecA2, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA2, vecB);

    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
#undef MATRIX_DIM
}




__STATIC_FORCEINLINE arm_status arm_mat_cmplx_mult_f16_4x4_mve(
    const arm_matrix_instance_f16 * pSrcA,
    const arm_matrix_instance_f16 * pSrcB,
    arm_matrix_instance_f16 * pDst)
{
#define MATRIX_DIM 4
    float16_t const *pInB = pSrcB->pData;  /* input data matrix pointer B */
    float16_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    float16_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint16x8_t     vecColBOffs0;
    float16_t       *pInA0 = pInA;
    float16_t       *pInA1 = pInA0 + CMPLX_DIM * MATRIX_DIM;
    float16_t       *pInA2 = pInA1 + CMPLX_DIM * MATRIX_DIM;
    float16_t       *pInA3 = pInA2 + CMPLX_DIM * MATRIX_DIM;
    f16x8_t        acc0, acc1, acc2, acc3;
    f16x8_t        vecB, vecA;
    static const uint16_t offsetB0[8] = { 0, 1,
        MATRIX_DIM * CMPLX_DIM, MATRIX_DIM * CMPLX_DIM + 1,
        2 * MATRIX_DIM * CMPLX_DIM, 2 * MATRIX_DIM * CMPLX_DIM + 1,
        3 * MATRIX_DIM * CMPLX_DIM, 3 * MATRIX_DIM * CMPLX_DIM + 1
    };

    vecColBOffs0 = vldrhq_u16((uint16_t const *) offsetB0);

    pInB = (float16_t const *)pSrcB->pData;

    vecB = vldrhq_gather_shifted_offset(pInB, vecColBOffs0);

    vecA = vldrhq_f16(pInA0);
    acc0 = vcmulq(vecA, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA, vecB);

    vecA = vldrhq_f16(pInA1);
    acc1 = vcmulq(vecA, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA, vecB);

    vecA = vldrhq_f16(pInA2);
    acc2 = vcmulq(vecA, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA, vecB);

    vecA = vldrhq_f16(pInA3);
    acc3 = vcmulq(vecA, vecB);
    acc3 = vcmlaq_rot90(acc3, vecA, vecB);


    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc3, &pOut[3 * CMPLX_DIM * MATRIX_DIM]);
    pOut += CMPLX_DIM;
    /*
     * move to next B column
     */
    pInB = pInB + CMPLX_DIM;

    vecB = vldrhq_gather_shifted_offset(pInB, vecColBOffs0);

    vecA = vldrhq_f16(pInA0);
    acc0 = vcmulq(vecA, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA, vecB);

    vecA = vldrhq_f16(pInA1);
    acc1 = vcmulq(vecA, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA, vecB);

    vecA = vldrhq_f16(pInA2);
    acc2 = vcmulq(vecA, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA, vecB);

    vecA = vldrhq_f16(pInA3);
    acc3 = vcmulq(vecA, vecB);
    acc3 = vcmlaq_rot90(acc3, vecA, vecB);


    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc3, &pOut[3 * CMPLX_DIM * MATRIX_DIM]);
    pOut += CMPLX_DIM;
    /*
     * move to next B column
     */
    pInB = pInB + CMPLX_DIM;

    vecB = vldrhq_gather_shifted_offset(pInB, vecColBOffs0);

    vecA = vldrhq_f16(pInA0);
    acc0 = vcmulq(vecA, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA, vecB);

    vecA = vldrhq_f16(pInA1);
    acc1 = vcmulq(vecA, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA, vecB);

    vecA = vldrhq_f16(pInA2);
    acc2 = vcmulq(vecA, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA, vecB);

    vecA = vldrhq_f16(pInA3);
    acc3 = vcmulq(vecA, vecB);
    acc3 = vcmlaq_rot90(acc3, vecA, vecB);


    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc3, &pOut[3 * CMPLX_DIM * MATRIX_DIM]);
    pOut += CMPLX_DIM;
    /*
     * move to next B column
     */
    pInB = pInB + CMPLX_DIM;

    vecB = vldrhq_gather_shifted_offset(pInB, vecColBOffs0);

    vecA = vldrhq_f16(pInA0);
    acc0 = vcmulq(vecA, vecB);
    acc0 = vcmlaq_rot90(acc0, vecA, vecB);

    vecA = vldrhq_f16(pInA1);
    acc1 = vcmulq(vecA, vecB);
    acc1 = vcmlaq_rot90(acc1, vecA, vecB);

    vecA = vldrhq_f16(pInA2);
    acc2 = vcmulq(vecA, vecB);
    acc2 = vcmlaq_rot90(acc2, vecA, vecB);

    vecA = vldrhq_f16(pInA3);
    acc3 = vcmulq(vecA, vecB);
    acc3 = vcmlaq_rot90(acc3, vecA, vecB);


    mve_cmplx_sum_intra_vec_f16(acc0, &pOut[0 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc1, &pOut[1 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc2, &pOut[2 * CMPLX_DIM * MATRIX_DIM]);
    mve_cmplx_sum_intra_vec_f16(acc3, &pOut[3 * CMPLX_DIM * MATRIX_DIM]);
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
#undef MATRIX_DIM
}



arm_status arm_mat_cmplx_mult_f16(
  const arm_matrix_instance_f16 * pSrcA,
  const arm_matrix_instance_f16 * pSrcB,
  arm_matrix_instance_f16 * pDst)
{
    float16_t const *pInB = (float16_t const *) pSrcB->pData;   /* input data matrix pointer B */
    float16_t const *pInA = (float16_t const *) pSrcA->pData;   /* input data matrix pointer A */
    float16_t *pOut = pDst->pData;  /* output data matrix pointer */
    float16_t *px;              /* Temporary output data matrix pointer */
    uint16_t  numRowsA = pSrcA->numRows;    /* number of rows of input matrix A    */
    uint16_t  numColsB = pSrcB->numCols;    /* number of columns of input matrix B */
    uint16_t  numColsA = pSrcA->numCols;    /* number of columns of input matrix A */
    uint16_t  col, i = 0U, row = numRowsA;  /* loop counters */
    arm_status status;          /* status of matrix multiplication */
    uint16x8_t vecOffs, vecColBOffs;
    uint32_t  blkCnt,rowCnt;           /* loop counters */

    #ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
if ((pSrcA->numCols != pSrcB->numRows) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcB->numCols != pDst->numCols)    )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {

    /*
     * small squared matrix specialized routines
     */
    if (numRowsA == numColsB && numColsB == numColsA)
    {
        if (numRowsA == 1)
        {
            pOut[0] = (_Float16)pInA[0] * (_Float16)pInB[0] - (_Float16)pInA[1] * (_Float16)pInB[1];
            pOut[1] = (_Float16)pInA[0] * (_Float16)pInB[1] + (_Float16)pInA[1] * (_Float16)pInB[0];
            return (ARM_MATH_SUCCESS);
        }
        else if  (numRowsA == 2)
            return arm_mat_cmplx_mult_f16_2x2_mve(pSrcA, pSrcB, pDst);
        else if (numRowsA == 3)
            return arm_mat_cmplx_mult_f16_3x3_mve(pSrcA, pSrcB, pDst);
        else if (numRowsA == 4)
            return arm_mat_cmplx_mult_f16_4x4_mve(pSrcA, pSrcB, pDst);
    }

    vecColBOffs[0] = 0;
    vecColBOffs[1] = 1;
    vecColBOffs[2] = numColsB * CMPLX_DIM;
    vecColBOffs[3] = (numColsB * CMPLX_DIM) + 1;
    vecColBOffs[4] = 2*numColsB * CMPLX_DIM;
    vecColBOffs[5] = 2*(numColsB * CMPLX_DIM) + 1;
    vecColBOffs[6] = 3*numColsB * CMPLX_DIM;
    vecColBOffs[7] = 3*(numColsB * CMPLX_DIM) + 1;

    /*
     * The following loop performs the dot-product of each row in pSrcA with each column in pSrcB
     */

    /*
     * row loop
     */
    rowCnt = row >> 2;
    while (rowCnt > 0u)
    {
        /*
         * Output pointer is set to starting address of the row being processed
         */
        px = pOut + i * CMPLX_DIM;
        i = i + 4 * numColsB;
        /*
         * For every row wise process, the column loop counter is to be initiated
         */
        col = numColsB;
        /*
         * For every row wise process, the pInB pointer is set
         * to the starting address of the pSrcB data
         */
        pInB = (float16_t const *) pSrcB->pData;
        /*
         * column loop
         */
        while (col > 0u)
        {
            /*
             * generate 4 columns elements
             */
            /*
             * Matrix A columns number of MAC operations are to be performed
             */

            float16_t const *pSrcA0Vec, *pSrcA1Vec, *pSrcA2Vec, *pSrcA3Vec;
            float16_t const *pInA0 = pInA;
            float16_t const *pInA1 = pInA0 + numColsA * CMPLX_DIM;
            float16_t const *pInA2 = pInA1 + numColsA * CMPLX_DIM;
            float16_t const *pInA3 = pInA2 + numColsA * CMPLX_DIM;
            f16x8_t acc0, acc1, acc2, acc3;

            acc0 = vdupq_n_f16(0.0f16);
            acc1 = vdupq_n_f16(0.0f16);
            acc2 = vdupq_n_f16(0.0f16);
            acc3 = vdupq_n_f16(0.0f16);

            pSrcA0Vec = (float16_t const *) pInA0;
            pSrcA1Vec = (float16_t const *) pInA1;
            pSrcA2Vec = (float16_t const *) pInA2;
            pSrcA3Vec = (float16_t const *) pInA3;

            vecOffs = vecColBOffs;

            /*
             * process 1 x 4 block output
             */
            blkCnt = (numColsA * CMPLX_DIM) >> 3;
            while (blkCnt > 0U)
            {
                f16x8_t vecB, vecA;

                vecB = vldrhq_gather_shifted_offset_f16(pInB, vecOffs);
                /*
                 * move Matrix B read offsets, 4 rows down
                 */
                vecOffs = vaddq_n_u16(vecOffs , (uint16_t) (numColsB * 4 * CMPLX_DIM));

                vecA = vld1q(pSrcA0Vec);  pSrcA0Vec += 8;
                acc0 = vcmlaq(acc0, vecA, vecB);
                acc0 = vcmlaq_rot90(acc0, vecA, vecB);

                vecA = vld1q(pSrcA1Vec);  pSrcA1Vec += 8;
                acc1 = vcmlaq(acc1, vecA, vecB);
                acc1 = vcmlaq_rot90(acc1, vecA, vecB);

                vecA = vld1q(pSrcA2Vec);  pSrcA2Vec += 8;
                acc2 = vcmlaq(acc2, vecA, vecB);
                acc2 = vcmlaq_rot90(acc2, vecA, vecB);

                vecA = vld1q(pSrcA3Vec);  pSrcA3Vec += 8;
                acc3 = vcmlaq(acc3, vecA, vecB);
                acc3 = vcmlaq_rot90(acc3, vecA, vecB);

                blkCnt--;
            }
            /*
             * Unsupported addressing mode compiler crash
             */
            /*
             * tail
             * (will be merged thru tail predication)
             */
            blkCnt = (numColsA * CMPLX_DIM) & 7;
            if (blkCnt > 0U)
            {
                mve_pred16_t p0 = vctp16q(blkCnt);
                f16x8_t vecB, vecA;

                vecB = vldrhq_gather_shifted_offset_z_f16(pInB, vecOffs, p0);
                /*
                 * move Matrix B read offsets, 4 rows down
                 */
                vecOffs = vaddq_n_u16(vecOffs, (uint16_t) (numColsB * 4 * CMPLX_DIM));

                vecA = vld1q(pSrcA0Vec);
                acc0 = vcmlaq(acc0, vecA, vecB);
                acc0 = vcmlaq_rot90(acc0, vecA, vecB);

                vecA = vld1q(pSrcA1Vec);
                acc1 = vcmlaq(acc1, vecA, vecB);
                acc1 = vcmlaq_rot90(acc1, vecA, vecB);

                vecA = vld1q(pSrcA2Vec);
                acc2 = vcmlaq(acc2, vecA, vecB);
                acc2 = vcmlaq_rot90(acc2, vecA, vecB);

                vecA = vld1q(pSrcA3Vec);
                acc3 = vcmlaq(acc3, vecA, vecB);
                acc3 = vcmlaq_rot90(acc3, vecA, vecB);

            }


            mve_cmplx_sum_intra_vec_f16(acc0, &px[0 * CMPLX_DIM * numColsB + 0]);
            mve_cmplx_sum_intra_vec_f16(acc1, &px[1 * CMPLX_DIM * numColsB + 0]);
            mve_cmplx_sum_intra_vec_f16(acc2, &px[2 * CMPLX_DIM * numColsB + 0]);
            mve_cmplx_sum_intra_vec_f16(acc3, &px[3 * CMPLX_DIM * numColsB + 0]);
           
            px += CMPLX_DIM;
            /*
             * Decrement the column loop counter
             */
            col--;
            /*
             * Update the pointer pInB to point to the  starting address of the next column
             */
            pInB = (float16_t const *) pSrcB->pData + (numColsB - col) * CMPLX_DIM;
        }

        /*
         * Update the pointer pInA to point to the  starting address of the next row
         */
        pInA += (numColsA * 4) * CMPLX_DIM;
        /*
         * Decrement the row loop counter
         */
        rowCnt --;

    }

    rowCnt = row & 3;
    while (rowCnt > 0u)
    {
           /*
         * Output pointer is set to starting address of the row being processed
         */
        px = pOut + i * CMPLX_DIM;
        i = i + numColsB;
        /*
         * For every row wise process, the column loop counter is to be initiated
         */
        col = numColsB;
        /*
         * For every row wise process, the pInB pointer is set
         * to the starting address of the pSrcB data
         */
        pInB = (float16_t const *) pSrcB->pData;
        /*
         * column loop
         */
        while (col > 0u)
        {
            /*
             * generate 4 columns elements
             */
            /*
             * Matrix A columns number of MAC operations are to be performed
             */

            float16_t const *pSrcA0Vec;
            float16_t const *pInA0 = pInA;
            f16x8_t acc0;

            acc0 = vdupq_n_f16(0.0f16);

            pSrcA0Vec = (float16_t const *) pInA0;
           
            vecOffs = vecColBOffs;

            /*
             * process 1 x 4 block output
             */
            blkCnt = (numColsA * CMPLX_DIM) >> 3;
            while (blkCnt > 0U)
            {
                f16x8_t vecB, vecA;

                vecB = vldrhq_gather_shifted_offset(pInB, vecOffs);
                /*
                 * move Matrix B read offsets, 4 rows down
                 */
                vecOffs = vaddq_n_u16(vecOffs, (uint16_t) (4*numColsB * CMPLX_DIM));

                vecA = vld1q(pSrcA0Vec);  
                pSrcA0Vec += 8;
                acc0 = vcmlaq(acc0, vecA, vecB);
                acc0 = vcmlaq_rot90(acc0, vecA, vecB);
                

                blkCnt--;
            }


            /*
             * tail
             */
            blkCnt = (numColsA * CMPLX_DIM) & 7;
            if (blkCnt > 0U)
            {
                mve_pred16_t p0 = vctp16q(blkCnt);
                f16x8_t vecB, vecA;

                vecB = vldrhq_gather_shifted_offset_z(pInB, vecOffs, p0);
               
                vecA = vld1q(pSrcA0Vec);
                acc0 = vcmlaq(acc0, vecA, vecB);
                acc0 = vcmlaq_rot90(acc0, vecA, vecB);

            }

            mve_cmplx_sum_intra_vec_f16(acc0, &px[0]);

           
            px += CMPLX_DIM;
            /*
             * Decrement the column loop counter
             */
            col--;
            /*
             * Update the pointer pInB to point to the  starting address of the next column
             */
            pInB = (float16_t const *) pSrcB->pData + (numColsB - col) * CMPLX_DIM;
        }

        /*
         * Update the pointer pInA to point to the  starting address of the next row
         */
        pInA += numColsA  * CMPLX_DIM;
        rowCnt--;
    }

    /*
     * set status as ARM_MATH_SUCCESS
     */
    status = ARM_MATH_SUCCESS;
 }
    /*
     * Return to application
     */
    return (status);
}
#else

arm_status arm_mat_cmplx_mult_f16(
  const arm_matrix_instance_f16 * pSrcA,
  const arm_matrix_instance_f16 * pSrcB,
        arm_matrix_instance_f16 * pDst)
{
  float16_t *pIn1 = pSrcA->pData;                /* Input data matrix pointer A */
  float16_t *pIn2 = pSrcB->pData;                /* Input data matrix pointer B */
  float16_t *pInA = pSrcA->pData;                /* Input data matrix pointer A */
  float16_t *pOut = pDst->pData;                 /* Output data matrix pointer */
  float16_t *px;                                 /* Temporary output data matrix pointer */
  uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
  _Float16 sumReal, sumImag;                    /* Accumulator */
  _Float16 a1, b1, c1, d1;
  uint32_t col, i = 0U, j, row = numRowsA, colCnt; /* loop counters */
  arm_status status;                             /* status of matrix multiplication */

#if defined (ARM_MATH_LOOPUNROLL)
  _Float16 a0, b0, c0, d0;
#endif

#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrcA->numCols != pSrcB->numRows) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcB->numCols != pDst->numCols)    )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    do
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + 2 * i;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      j = 0U;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sumReal = 0.0f16;
        sumImag = 0.0f16;

        /* Initiate pointer pIn1 to point to starting address of column being processed */
        pIn1 = pInA;

#if defined (ARM_MATH_LOOPUNROLL)

        /* Apply loop unrolling and compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {

          /* Reading real part of complex matrix A */
          a0 = *pIn1;

          /* Reading real part of complex matrix B */
          c0 = *pIn2;

          /* Reading imaginary part of complex matrix A */
          b0 = *(pIn1 + 1U);

          /* Reading imaginary part of complex matrix B */
          d0 = *(pIn2 + 1U);

          /* Multiply and Accumlates */
          sumReal += a0 * c0;
          sumImag += b0 * c0;

          /* update pointers */
          pIn1 += 2U;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal -= b0 * d0;
          sumImag += a0 * d0;

          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          /* read real and imag values from pSrcA and pSrcB buffer */
          a1 = *(pIn1     );
          c1 = *(pIn2     );
          b1 = *(pIn1 + 1U);
          d1 = *(pIn2 + 1U);

          /* Multiply and Accumlates */
          sumReal += a1 * c1;
          sumImag += b1 * c1;

          /* update pointers */
          pIn1 += 2U;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal -= b1 * d1;
          sumImag += a1 * d1;

          a0 = *(pIn1     );
          c0 = *(pIn2     );
          b0 = *(pIn1 + 1U);
          d0 = *(pIn2 + 1U);

          /* Multiply and Accumlates */
          sumReal += a0 * c0;
          sumImag += b0 * c0;

          /* update pointers */
          pIn1 += 2U;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal -= b0 * d0;
          sumImag += a0 * d0;

          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          a1 = *(pIn1     );
          c1 = *(pIn2     );
          b1 = *(pIn1 + 1U);
          d1 = *(pIn2 + 1U);

          /* Multiply and Accumlates */
          sumReal += a1 * c1;
          sumImag += b1 * c1;

          /* update pointers */
          pIn1 += 2U;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal -= b1 * d1;
          sumImag += a1 * d1;

          /* Decrement loop count */
          colCnt--;
        }

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining MACs here.
         ** No loop unrolling is used. */
        colCnt = numColsA % 0x4U;

#else

        /* Initialize blkCnt with number of samples */
        colCnt = numColsA;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */
          a1 = *(pIn1     );
          c1 = *(pIn2     );
          b1 = *(pIn1 + 1U);
          d1 = *(pIn2 + 1U);

          /* Multiply and Accumlates */
          sumReal += a1 * c1;
          sumImag += b1 * c1;

          /* update pointers */
          pIn1 += 2U;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal -= b1 * d1;
          sumImag += a1 * d1;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Store result in destination buffer */
        *px++ = sumReal;
        *px++ = sumImag;

        /* Update pointer pIn2 to point to starting address of next column */
        j++;
        pIn2 = pSrcB->pData + 2U * j;

        /* Decrement column loop counter */
        col--;

      } while (col > 0U);

      /* Update pointer pInA to point to starting address of next row */
      i = i + numColsB;
      pInA = pInA + 2 * numColsA;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of MatrixMult group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

