/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_vec_mult_f16.c
 * Description:  Floating-point matrix and vector multiplication
 *
 * $Date:        23 April 2021
 *
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
 * @ingroup groupMatrix
 */


/**
 * @addtogroup MatrixVectMult
 * @{
 */

/**
 * @brief Floating-point matrix and vector multiplication.
 * @param[in]       *pSrcMat points to the input matrix structure
 * @param[in]       *pVec points to input vector
 * @param[out]      *pDst points to output vector
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

void arm_mat_vec_mult_f16(
    const arm_matrix_instance_f16   *pSrcMat,
    const float16_t                 *pSrcVec,
    float16_t                       *pDstVec)
{
    uint32_t         numRows = pSrcMat->numRows;
    uint32_t         numCols = pSrcMat->numCols;
    const float16_t *pSrcA = pSrcMat->pData;
    const float16_t *pInA0;
    const float16_t *pInA1;
    float16_t       *px;
    int32_t          row;
    uint32_t         blkCnt;           /* loop counters */

    row = numRows;
    px = pDstVec;

    /*
     * compute 4 rows in parallel
     */
    while (row >= 4)
    {
        const float16_t     *pInA2, *pInA3;
        float16_t const    *pSrcA0Vec, *pSrcA1Vec, *pSrcA2Vec, *pSrcA3Vec, *pInVec;
        f16x8_t            vecIn, acc0, acc1, acc2, acc3;
        float16_t const     *pSrcVecPtr = pSrcVec;

        /*
         * Initialize the pointers to 4 consecutive MatrixA rows
         */
        pInA0 = pSrcA;
        pInA1 = pInA0 + numCols;
        pInA2 = pInA1 + numCols;
        pInA3 = pInA2 + numCols;
        /*
         * Initialize the vector pointer
         */
        pInVec =  pSrcVecPtr;
        /*
         * reset accumulators
         */
        acc0 = vdupq_n_f16(0.0f);
        acc1 = vdupq_n_f16(0.0f);
        acc2 = vdupq_n_f16(0.0f);
        acc3 = vdupq_n_f16(0.0f);

        pSrcA0Vec = pInA0;
        pSrcA1Vec = pInA1;
        pSrcA2Vec = pInA2;
        pSrcA3Vec = pInA3;

        blkCnt = numCols >> 3;
        while (blkCnt > 0U)
        {
            f16x8_t vecA;

            vecIn = vld1q(pInVec);
            pInVec += 8;
            vecA = vld1q(pSrcA0Vec);
            pSrcA0Vec += 8;
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vld1q(pSrcA1Vec);
            pSrcA1Vec += 8;
            acc1 = vfmaq(acc1, vecIn, vecA);
            vecA = vld1q(pSrcA2Vec);
            pSrcA2Vec += 8;
            acc2 = vfmaq(acc2, vecIn, vecA);
            vecA = vld1q(pSrcA3Vec);
            pSrcA3Vec += 8;
            acc3 = vfmaq(acc3, vecIn, vecA);

            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = numCols & 7;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(blkCnt);
            f16x8_t vecA;

            vecIn = vldrhq_z_f16(pInVec, p0);
            vecA = vld1q(pSrcA0Vec);
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vld1q(pSrcA1Vec);
            acc1 = vfmaq(acc1, vecIn, vecA);
            vecA = vld1q(pSrcA2Vec);
            acc2 = vfmaq(acc2, vecIn, vecA);
            vecA = vld1q(pSrcA3Vec);
            acc3 = vfmaq(acc3, vecIn, vecA);
        }
        /*
         * Sum the partial parts
         */
        *px++ = vecAddAcrossF16Mve(acc0);
        *px++ = vecAddAcrossF16Mve(acc1);
        *px++ = vecAddAcrossF16Mve(acc2);
        *px++ = vecAddAcrossF16Mve(acc3);

        pSrcA += numCols * 4;
        /*
         * Decrement the row loop counter
         */
        row -= 4;
    }

    /*
     * compute 2 rows in parrallel
     */
    if (row >= 2)
    {
        float16_t const    *pSrcA0Vec, *pSrcA1Vec, *pInVec;
        f16x8_t            vecIn, acc0, acc1;
        float16_t const     *pSrcVecPtr = pSrcVec;

        /*
         * Initialize the pointers to 2 consecutive MatrixA rows
         */
        pInA0 = pSrcA;
        pInA1 = pInA0 + numCols;
        /*
         * Initialize the vector pointer
         */
        pInVec = pSrcVecPtr;
        /*
         * reset accumulators
         */
        acc0 = vdupq_n_f16(0.0f);
        acc1 = vdupq_n_f16(0.0f);
        pSrcA0Vec = pInA0;
        pSrcA1Vec = pInA1;

        blkCnt = numCols >> 3;
        while (blkCnt > 0U)
        {
            f16x8_t vecA;

            vecIn = vld1q(pInVec);
            pInVec += 8;
            vecA = vld1q(pSrcA0Vec);
            pSrcA0Vec += 8;
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vld1q(pSrcA1Vec);
            pSrcA1Vec += 8;
            acc1 = vfmaq(acc1, vecIn, vecA);

            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = numCols & 7;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(blkCnt);
            f16x8_t vecA;

            vecIn = vldrhq_z_f16(pInVec, p0);
            vecA = vld1q(pSrcA0Vec);
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vld1q(pSrcA1Vec);
            acc1 = vfmaq(acc1, vecIn, vecA);
        }
        /*
         * Sum the partial parts
         */
        *px++ = vecAddAcrossF16Mve(acc0);
        *px++ = vecAddAcrossF16Mve(acc1);

        pSrcA += numCols * 2;
        row -= 2;
    }

    if (row >= 1)
    {
        f16x8_t             vecIn, acc0;
        float16_t const     *pSrcA0Vec, *pInVec;
        float16_t const      *pSrcVecPtr = pSrcVec;
        /*
         * Initialize the pointers to last MatrixA row
         */
        pInA0 = pSrcA;
        /*
         * Initialize the vector pointer
         */
        pInVec = pSrcVecPtr;
        /*
         * reset accumulators
         */
        acc0 = vdupq_n_f16(0.0f);

        pSrcA0Vec = pInA0;

        blkCnt = numCols >> 3;
        while (blkCnt > 0U)
        {
            f16x8_t vecA;

            vecIn = vld1q(pInVec);
            pInVec += 8;
            vecA = vld1q(pSrcA0Vec);
            pSrcA0Vec += 8;
            acc0 = vfmaq(acc0, vecIn, vecA);

            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = numCols & 7;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(blkCnt);
            f16x8_t vecA;

            vecIn = vldrhq_z_f16(pInVec, p0);
            vecA = vld1q(pSrcA0Vec);
            acc0 = vfmaq(acc0, vecIn, vecA);
        }
        /*
         * Sum the partial parts
         */
        *px++ = vecAddAcrossF16Mve(acc0);
    }
}
#else
void arm_mat_vec_mult_f16(const arm_matrix_instance_f16 *pSrcMat, const float16_t *pVec, float16_t *pDst)
{
    uint32_t numRows = pSrcMat->numRows;
    uint32_t numCols = pSrcMat->numCols;
    const float16_t *pSrcA = pSrcMat->pData;
    const float16_t *pInA1;      /* input data matrix pointer A of Q31 type */
    const float16_t *pInA2;      /* input data matrix pointer A of Q31 type */
    const float16_t *pInA3;      /* input data matrix pointer A of Q31 type */
    const float16_t *pInA4;      /* input data matrix pointer A of Q31 type */
    const float16_t *pInVec;     /* input data matrix pointer B of Q31 type */
    float16_t *px;               /* Temporary output data matrix pointer */
    uint16_t i, row, colCnt; /* loop counters */
    float16_t matData, matData2, vecData, vecData2;


    /* Process 4 rows at a time */
    row = numRows >> 2;
    i = 0u;
    px = pDst;

    /* The following loop performs the dot-product of each row in pSrcA with the vector */
    /* row loop */
    while (row > 0) {
        /* For every row wise process, the pInVec pointer is set
         ** to the starting address of the vector */
        pInVec = pVec;

        /* Initialize accumulators */
        float16_t sum1 = 0.0f;
        float16_t sum2 = 0.0f;
        float16_t sum3 = 0.0f;
        float16_t sum4 = 0.0f;

        /* Loop unrolling: process 2 columns per iteration */
        colCnt = numCols;

        /* Initialize pointers to the starting address of the column being processed */
        pInA1 = pSrcA + i;
        pInA2 = pInA1 + numCols;
        pInA3 = pInA2 + numCols;
        pInA4 = pInA3 + numCols;


        // Main loop: matrix-vector multiplication
        while (colCnt > 0u) {
            // Read 2 values from vector
            vecData = *(pInVec)++;
            // Read 8 values from the matrix - 2 values from each of 4 rows, and do multiply accumulate
            matData = *(pInA1)++;
            sum1 += matData * vecData;
            matData = *(pInA2)++;
            sum2 += matData * vecData;
            matData = *(pInA3)++;
            sum3 += matData * vecData;
            matData = *(pInA4)++;
            sum4 += matData * vecData;

            // Decrement the loop counter
            colCnt--;
        }

        /* Saturate and store the result in the destination buffer */
        *px++ = sum1;
        *px++ = sum2;
        *px++ = sum3;
        *px++ = sum4;

        i = i + numCols * 4;

        /* Decrement the row loop counter */
        row--;
    }

    /* process any remaining rows */
    row = numRows & 3u;
    while (row > 0) {

        float16_t sum = 0.0f;
        pInVec = pVec;
        pInA1 = pSrcA + i;

        colCnt = numCols >> 1;

        while (colCnt > 0) {
            vecData = *(pInVec)++;
            vecData2 = *(pInVec)++;
            matData = *(pInA1)++;
            matData2 = *(pInA1)++;
            sum += matData * vecData;
            sum += matData2 * vecData2;
            colCnt--;
        }
        // process remainder of row
        colCnt = numCols & 1u;
        while (colCnt > 0) {
            sum += *pInA1++ * *pInVec++;
            colCnt--;
        }

        *px++ = sum;
        i = i + numCols;
        row--;
    }
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of MatrixMult group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

