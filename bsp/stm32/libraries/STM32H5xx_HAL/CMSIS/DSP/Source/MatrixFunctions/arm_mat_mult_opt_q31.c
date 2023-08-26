/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_mult_opt_q31.c
 * Description:  Q31 matrix multiplication
 *
 * $Date:        3 Nov 2021
 * $Revision:    V1.10.0
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

#include "dsp/matrix_functions.h"

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixMult
  @{
 */

/**
  @brief         Q31 matrix multiplication.
  @param[in]     pSrcA      points to the first input matrix structure
  @param[in]     pSrcB      points to the second input matrix structure
  @param[out]    pDst       points to output matrix structure
  @param[in]  pState  points to the array for storing intermediate results
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed

  @par           Scaling and Overflow Behavior
                   The function is implemented using an internal 64-bit accumulator.
                   The accumulator has a 2.62 format and maintains full precision of the intermediate
                   multiplication results but provides only a single guard bit. There is no saturation
                   on intermediate additions. Thus, if the accumulator overflows it wraps around and
                   distorts the result. The input signals should be scaled down to avoid intermediate
                   overflows. The input is thus scaled down by log2(numColsA) bits
                   to avoid overflows, as a total of numColsA additions are performed internally.
                   The 2.62 accumulator is right shifted by 31 bits and saturated to 1.31 format to yield the final result.
  @remark
                   Refer to \ref arm_mat_mult_fast_q31() for a faster but less precise implementation of this function.
  @remark
                   This function is a faster implementation of arm_mat_mult_q31 for MVE but it is requiring 
                   additional storage for intermediate results.
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)

#define MATRIX_DIM2 2
#define MATRIX_DIM3 3
#define MATRIX_DIM4 4

__STATIC_INLINE arm_status arm_mat_mult_opt_q31_2x2_mve(
    const arm_matrix_instance_q31 * pSrcA,
    const arm_matrix_instance_q31 * pSrcB,
    arm_matrix_instance_q31 * pDst)
{
    q31_t       *pInB = pSrcB->pData;  /* input data matrix pointer B */
    q31_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q31_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint32x4_t   vecColBOffs;
    q31_t       *pInA0 = pInA;
    q31_t       *pInA1 = pInA0 + MATRIX_DIM2;
    q63_t        acc0, acc1;
    q31x4_t      vecB, vecA0, vecA1;
    /* enable predication to disable half of vector elements */
    mve_pred16_t p0 = vctp32q(MATRIX_DIM2);

    vecColBOffs = vidupq_u32((uint32_t)0, 1);
    vecColBOffs = vecColBOffs * MATRIX_DIM2;

    pInB = pSrcB->pData;

    /* load 1st B column (partial load) */
    vecB = vldrwq_gather_shifted_offset_z_s32(pInB, vecColBOffs, p0);

    /* load A rows */
    vecA0 = vldrwq_s32(pInA0);
    vecA1 = vldrwq_s32(pInA1);

    acc0 = vrmlaldavhq(vecA0, vecB);
    acc1 = vrmlaldavhq(vecA1, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);

    pOut[0 * MATRIX_DIM2] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM2] = (q31_t) acc1;
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrwq_gather_shifted_offset_z_s32(pInB, vecColBOffs, p0);

    acc0 = vrmlaldavhq(vecA0, vecB);
    acc1 = vrmlaldavhq(vecA1, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);

    pOut[0 * MATRIX_DIM2] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM2] = (q31_t) acc1;
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}



__STATIC_INLINE arm_status arm_mat_mult_opt_q31_3x3_mve(
    const arm_matrix_instance_q31 * pSrcA,
    const arm_matrix_instance_q31 * pSrcB,
    arm_matrix_instance_q31 * pDst)
{
    q31_t       *pInB = pSrcB->pData;  /* input data matrix pointer B */
    q31_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q31_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint32x4_t   vecColBOffs;
    q31_t       *pInA0 = pInA;
    q31_t       *pInA1 = pInA0 + MATRIX_DIM3;
    q31_t       *pInA2 = pInA1 + MATRIX_DIM3;
    q63_t        acc0, acc1, acc2;
    q31x4_t      vecB, vecA;
    /* enable predication to disable last (4th) vector element */
    mve_pred16_t p0 = vctp32q(MATRIX_DIM3);

    vecColBOffs = vidupq_u32((uint32_t)0, 1);
    vecColBOffs = vecColBOffs * MATRIX_DIM3;

    pInB = pSrcB->pData;

    vecB = vldrwq_gather_shifted_offset_z_s32(pInB, vecColBOffs, p0);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);

    pOut[0 * MATRIX_DIM3] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM3] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM3] = (q31_t) acc2;
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrwq_gather_shifted_offset_z_s32(pInB, vecColBOffs, p0);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);

    pOut[0 * MATRIX_DIM3] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM3] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM3] = (q31_t) acc2;
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrwq_gather_shifted_offset_z_s32(pInB, vecColBOffs, p0);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);

    pOut[0 * MATRIX_DIM3] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM3] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM3] = (q31_t) acc2;
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}

__STATIC_INLINE arm_status arm_mat_mult_opt_q31_4x4_mve(
    const arm_matrix_instance_q31 * pSrcA,
    const arm_matrix_instance_q31 * pSrcB,
    arm_matrix_instance_q31 * pDst)
{
    q31_t       *pInB = pSrcB->pData;  /* input data matrix pointer B */
    q31_t       *pInA = pSrcA->pData;  /* input data matrix pointer A */
    q31_t       *pOut = pDst->pData;   /* output data matrix pointer */
    uint32x4_t   vecColBOffs;
    q31_t       *pInA0 = pInA;
    q31_t       *pInA1 = pInA0 + MATRIX_DIM4;
    q31_t       *pInA2 = pInA1 + MATRIX_DIM4;
    q31_t       *pInA3 = pInA2 + MATRIX_DIM4;
    q63_t        acc0, acc1, acc2, acc3;
    q31x4_t      vecB, vecA;

    vecColBOffs = vidupq_u32((uint32_t)0, 4);

    pInB = pSrcB->pData;

    vecB = vldrwq_gather_shifted_offset_s32(pInB, vecColBOffs);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA3);
    acc3 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);
    acc3 = asrl(acc3, 23);

    pOut[0 * MATRIX_DIM4] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM4] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM4] = (q31_t) acc2;
    pOut[3 * MATRIX_DIM4] = (q31_t) acc3;
    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrwq_gather_shifted_offset_s32(pInB, vecColBOffs);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA3);
    acc3 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);
    acc3 = asrl(acc3, 23);

    pOut[0 * MATRIX_DIM4] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM4] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM4] = (q31_t) acc2;
    pOut[3 * MATRIX_DIM4] = (q31_t) acc3;

    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrwq_gather_shifted_offset_s32(pInB, vecColBOffs);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA3);
    acc3 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);
    acc3 = asrl(acc3, 23);

    pOut[0 * MATRIX_DIM4] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM4] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM4] = (q31_t) acc2;
    pOut[3 * MATRIX_DIM4] = (q31_t) acc3;

    pOut++;

    /* move to next B column */
    pInB = pInB + 1;

    vecB = vldrwq_gather_shifted_offset_s32(pInB, vecColBOffs);

    vecA = vldrwq_s32(pInA0);
    acc0 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA1);
    acc1 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA2);
    acc2 = vrmlaldavhq(vecA, vecB);
    vecA = vldrwq_s32(pInA3);
    acc3 = vrmlaldavhq(vecA, vecB);

    acc0 = asrl(acc0, 23);
    acc1 = asrl(acc1, 23);
    acc2 = asrl(acc2, 23);
    acc3 = asrl(acc3, 23);

    pOut[0 * MATRIX_DIM4] = (q31_t) acc0;
    pOut[1 * MATRIX_DIM4] = (q31_t) acc1;
    pOut[2 * MATRIX_DIM4] = (q31_t) acc2;
    pOut[3 * MATRIX_DIM4] = (q31_t) acc3;
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
}


arm_status arm_mat_mult_opt_q31(
    const arm_matrix_instance_q31 * pSrcA,
    const arm_matrix_instance_q31 * pSrcB,
    arm_matrix_instance_q31 * pDst,
    q31_t *pState)
{
    q31_t          *pInA = pSrcA->pData;        /* input data matrix pointer A */
    q31_t          *pInB = pSrcB->pData;        /* input data matrix pointer B */
    q31_t          *pInA2;
    q31_t          *pInB2;
    q31_t          *px;         /* Temporary output data matrix pointer */
    q31_t          *px2;        /* Temporary output data matrix pointer */
    uint32_t        numRowsA = pSrcA->numRows;  /* number of rows of input matrix A    */
    uint32_t        numColsB = pSrcB->numCols;  /* number of columns of input matrix B */
    uint32_t        numColsA = pSrcA->numCols;  /* number of columns of input matrix A */
    uint32_t        numRowsB = pSrcB->numRows;  /* number of rows of input matrix A    */
    uint32_t        col, i = 0u, j, row = numRowsB;     /* loop counters */
    q31_t          *pSrcBT = pState;     /* input data matrix pointer for transpose */
    uint32_t        blkCnt;     /* loop counters */
    arm_status      status;                            /* Status of matrix multiplication */
    arm_matrix_instance_q31 BT;
#ifdef ARM_MATH_MATRIX_CHECK

    /* Check for matrix mismatch condition */
    if ((pSrcA->numCols != pSrcB->numRows) ||
        (pSrcA->numRows != pDst->numRows) || (pSrcB->numCols != pDst->numCols)) {
        /* Set status as ARM_MATH_SIZE_MISMATCH */
        status = ARM_MATH_SIZE_MISMATCH;
    } else
#endif                          /* #ifdef ARM_MATH_MATRIX_CHECK */
    {

         /* small squared matrix specialized routines */
    if(numRowsA == numColsB && numColsB == numColsA) {
        if (numRowsA == 1)
        {
          q63_t sum =  (q63_t) *pInA * *pInB;
          pDst->pData[0] = (q31_t)(sum >> 31);
          return (ARM_MATH_SUCCESS);
        }
        else if(numRowsA == 2)
            return arm_mat_mult_opt_q31_2x2_mve(pSrcA, pSrcB, pDst);
        else if(numRowsA == 3)
            return arm_mat_mult_opt_q31_3x3_mve(pSrcA, pSrcB, pDst);
        else if (numRowsA == 4)
            return arm_mat_mult_opt_q31_4x4_mve(pSrcA, pSrcB, pDst);
    }


        /*
         * Matrix transpose
         */
        BT.numRows = numColsB;
        BT.numCols = numRowsB;
        BT.pData = pSrcBT;

        arm_mat_trans_q31(pSrcB, &BT);


        /*
         * Reset the variables for the usage in the following multiplication process
         */
        i = 0;
        row = numRowsA >> 1;
        px = pDst->pData;
        px2 = px + numColsB;

        /*
         * main loop
         * compute 2 x 2 output blocks
         * with dot products (Matrix A rows * Transposed MAtrix B rows)
         */
        while (row > 0u) {
            /*
             * For every row wise process, the column loop counter is to be initiated
             * Compute 2 columns and 2 rows in parrallel
             */
            col = numColsB >> 1;
            j = 0;

            /*
             * column pair loop
             */
            while (col > 0u) {
                q31_t const    *pSrcAVec, *pSrcBVec, *pSrcA2Vec, *pSrcB2Vec;
                q31x4_t         vecA, vecA2, vecB, vecB2;
                q63_t           acc0, acc1, acc2, acc3;

                /*
                 * Initiate the pointers
                 * - 2 x consecutive Matrix A rows (i increment is 2 x numColsA)
                 * - 2 x consecutive Matrix B' rows (j increment is 2 x numRowsB)
                 */
                pInA = pSrcA->pData + i;
                pInA2 = pInA + numColsA;
                pInB = pSrcBT + j;
                pInB2 = pInB + numRowsB;


                pSrcAVec = (q31_t const *) pInA;
                pSrcA2Vec = (q31_t const *) pInA2;
                pSrcBVec = (q31_t const *) pInB;
                pSrcB2Vec = (q31_t const *) pInB2;

                acc0 = 0LL;
                acc1 = 0LL;
                acc2 = 0LL;
                acc3 = 0LL;

                /* load scheduling */
                vecA = vld1q(pSrcAVec);
                pSrcAVec += 4;

                blkCnt = (numColsA / 4);
                while (blkCnt > 0U) {
                    vecB = vld1q(pSrcBVec);
                    pSrcBVec += 4;
                    acc0 = vrmlaldavhaq(acc0, vecA, vecB);
                    vecA2 = vld1q(pSrcA2Vec);
                    pSrcA2Vec += 4;
                    acc1 = vrmlaldavhaq(acc1, vecA2, vecB);
                    vecB2 = vld1q(pSrcB2Vec);
                    pSrcB2Vec += 4;
                    acc2 = vrmlaldavhaq(acc2, vecA, vecB2);
                    vecA = vld1q(pSrcAVec);
                    pSrcAVec += 4;
                    acc3 = vrmlaldavhaq(acc3, vecA2, vecB2);

                    blkCnt--;
                }
                /*
                 * tail
                 * (will be merged thru tail predication)
                 */
                blkCnt = (numColsA & 3);
                if (blkCnt > 0U) {
                    mve_pred16_t    p0 = vctp32q(blkCnt);
                    vecB = vld1q(pSrcBVec);
                    acc0 = vrmlaldavhaq_p(acc0, vecA, vecB, p0);
                    vecA2 = vld1q(pSrcA2Vec);
                    acc1 = vrmlaldavhaq_p(acc1, vecA2, vecB, p0);
                    vecB2 = vld1q(pSrcB2Vec);
                    acc2 = vrmlaldavhaq_p(acc2, vecA, vecB2, p0);
                    vecA = vld1q(pSrcAVec);
                    acc3 = vrmlaldavhaq_p(acc3, vecA2, vecB2, p0);
                }

                /* Convert to 1.31 */
                acc0 = asrl(acc0, 23);
                acc1 = asrl(acc1, 23);
                acc2 = asrl(acc2, 23);
                acc3 = asrl(acc3, 23);

                /* Store the results (2 x 2 block) in the destination buffer */
                *px++ = (q31_t) acc0;
                *px++ = (q31_t) acc2;
                *px2++ = (q31_t) acc1;
                *px2++ = (q31_t) acc3;

                j += numRowsB * 2;
                /*
                 * Decrement the column pair loop counter
                 */
                col--;

            }

            i = i + numColsA * 2;
            px = px2 + (numColsB & 1u);
            px2 = px + numColsB;
            /*
             * Decrement the row pair loop counter
             */
            row--;
        }

        /*
         * Compute remaining row and/or column below
         */
        if (numColsB & 1u) {
            row = numRowsA & (~0x1);    //avoid redundant computation
            px = pDst->pData + numColsB - 1;
            i = 0;

            /*
             * row loop
             */
            while (row > 0) {
                q31_t const    *pSrcAVec, *pSrcBVec;
                q31x4_t         vecA, vecB;
                q63_t           acc0;

                /*
                 * point to last column in matrix B
                 */
                pInB = pSrcBT + numRowsB * (numColsB - 1);
                pInA = pSrcA->pData + i;

                pSrcAVec = (q31_t const *) pInA;
                pSrcBVec = (q31_t const *) pInB;

                /* single dot-product */
                acc0 = 0LL;
                blkCnt = (numColsA / 4);
                while (blkCnt > 0U) {
                    vecA = vld1q(pSrcAVec);
                    pSrcAVec += 4;
                    vecB = vld1q(pSrcBVec);
                    pSrcBVec += 4;
                    acc0 = vrmlaldavhaq(acc0, vecA, vecB);

                    blkCnt--;
                }
                /*
                 * tail
                 * (will be merged thru tail predication)
                 */
                blkCnt = (numColsA & 3);
                if (blkCnt > 0U) {
                    mve_pred16_t    p0 = vctp32q(blkCnt);
                    vecA = vld1q(pSrcAVec);
                    vecB = vld1q(pSrcBVec);
                    acc0 = vrmlaldavhaq_p(acc0, vecA, vecB, p0);
                }

                acc0 = asrl(acc0, 23);
                *px = (q31_t) acc0;

                px += numColsB;

                i += numColsA;
                /*
                 * Decrement the row loop counter
                 */
                row--;
            }
        }

        if (numRowsA & 1u) {
            col = numColsB;
            i = 0u;
            /*
             * point to last row in output matrix
             */
            px = pDst->pData + (numColsB) * (numRowsA - 1);
            /*
             * col loop
             */
            while (col > 0) {
                q31_t const    *pSrcAVec, *pSrcBVec;
                q31x4_t         vecA, vecB;
                q63_t           acc0;

                /*
                 * point to last row in matrix A
                 */
                pInA = pSrcA->pData + (numRowsA - 1) * numColsA;
                pInB = pSrcBT + i;

                /*
                 * Set the variable sum, that acts as accumulator, to zero
                 */
                pSrcAVec = (q31_t const *) pInA;
                pSrcBVec = (q31_t const *) pInB;
                acc0 = 0LL;

                blkCnt = (numColsA / 4);
                while (blkCnt > 0U) {
                    vecA = vld1q(pSrcAVec);
                    pSrcAVec += 4;
                    vecB = vld1q(pSrcBVec);
                    pSrcBVec += 4;
                    acc0 = vrmlaldavhaq(acc0, vecA, vecB);

                    blkCnt--;
                }
                /*
                 * tail
                 * (will be merged thru tail predication)
                 */
                blkCnt = (numColsA & 3);
                if (blkCnt > 0U) {
                    mve_pred16_t    p0 = vctp32q(blkCnt);
                    vecA = vld1q(pSrcAVec);
                    vecB = vld1q(pSrcBVec);
                    acc0 = vrmlaldavhaq_p(acc0, vecA, vecB, p0);
                }

                acc0 = asrl(acc0, 23);
                *px++ = (q31_t) acc0;

                i += numColsA;
                /*
                 * Decrement the col loop counter
                 */
                col--;
            }
        }
        /* Set status as ARM_MATH_SUCCESS */
        status = ARM_MATH_SUCCESS;
    }
    /*
     * Return to application
     */
    return (status);
}

#else
arm_status arm_mat_mult_opt_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst,
        q31_t *pState)
{
  q31_t *pIn1 = pSrcA->pData;                    /* Input data matrix pointer A */
  q31_t *pIn2 = pSrcB->pData;                    /* Input data matrix pointer B */
  q31_t *pInA = pSrcA->pData;                    /* Input data matrix pointer A */
  q31_t *pInB = pSrcB->pData;                    /* Input data matrix pointer B */
  q31_t *pOut = pDst->pData;                     /* Output data matrix pointer */
  q31_t *px;                                     /* Temporary output data matrix pointer */
  q63_t sum;                                     /* Accumulator */
  uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
  uint32_t col, i = 0U, row = numRowsA, colCnt;  /* Loop counters */
  arm_status status;                             /* Status of matrix multiplication */
  (void)pState;
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
      /* Output pointer is set to starting address of row being processed */
      px = pOut + i;

      /* For every row wise process, column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, pIn2 pointer is set to starting address of pSrcB data */
      pIn2 = pSrcB->pData;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum = 0;

        /* Initialize pointer pIn1 to point to starting address of column being processed */
        pIn1 = pInA;

#if defined (ARM_MATH_LOOPUNROLL)

        /* Loop unrolling: Compute 4 MACs at a time. */
        colCnt = numColsA >> 2U;

        /* matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          /* Perform the multiply-accumulates */
          sum += (q63_t) *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += (q63_t) *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += (q63_t) *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += (q63_t) *pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Loop unrolling: Compute remaining MACs */
        colCnt = numColsA % 0x4U;

#else

        /* Initialize cntCnt with number of columns */
        colCnt = numColsA;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1) * b(1,1) + a(1,2) * b(2,1) + .... + a(m,p) * b(p,n) */

          /* Perform the multiply-accumulates */
          sum += (q63_t) *pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Convert result from 2.62 to 1.31 format and store in destination buffer */
        *px++ = (q31_t) (sum >> 31);

        /* Decrement column loop counter */
        col--;

        /* Update pointer pIn2 to point to starting address of next column */
        pIn2 = pInB + (numColsB - col);

      } while (col > 0U);

      /* Update pointer pInA to point to starting address of next row */
      i = i + numColsB;
      pInA = pInA + numColsA;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}
#endif /* defined(ARM_MATH_MVEI) */

/**
  @} end of MatrixMult group
 */
