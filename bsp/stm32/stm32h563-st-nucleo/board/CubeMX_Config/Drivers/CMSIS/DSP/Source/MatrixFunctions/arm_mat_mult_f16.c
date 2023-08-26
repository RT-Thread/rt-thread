/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_mult_f16.c
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
 * @ingroup groupMatrix
 */


/**
 * @addtogroup MatrixMult
 * @{
 */

/**
 * @brief Floating-point matrix multiplication.
 * @param[in]       *pSrcA points to the first input matrix structure
 * @param[in]       *pSrcB points to the second input matrix structure
 * @param[out]      *pDst points to output matrix structure
 * @return     		The function returns either
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

__STATIC_FORCEINLINE arm_status arm_mat_mult_f16_2x2_mve(
    const arm_matrix_instance_f16 *pSrcA,
    const arm_matrix_instance_f16 *pSrcB,
    arm_matrix_instance_f16 *pDst)
{
    static const uint16_t offsetA[8] = { 0, 0, 2, 2, 0, 0, 2, 2 };
    /* offsetB allows to read and duplicate 1 row of B */
    static const uint16_t offsetB[8] = { 0, 1, 0, 1, 0, 1, 0, 1 };
    uint16x8_t    vecOffsA, vecOffsB;
    f16x8_t       vecInA, vecInB, vecDst;
    float16_t      *pOut = pDst->pData;  /* output data matrix pointer */

    /*
     * load initial offsets
     */
    vecOffsA = vldrhq_u16((uint16_t const *) offsetA);
    vecOffsB = vldrhq_u16((uint16_t const *) offsetB);
    /*
     * load {a00 a00 a10 a10 x x x x }
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * load {b00 b01 b00 b01 x x x x }
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00       a00 b01
     *    a10 b00       a10 b01
     *       x             x
     *       x             x   }
     */
    vecDst = vmulq(vecInA, vecInB);
    /*
     * move to 2nd column of matrix A
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 1);
    /*
     * load {a01 a01 a11 a11 x x x x}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * move to next B row
     */
    vecOffsB = vaddq_n_u16(vecOffsB, (uint16_t) 2);
    /*
     * load {b10, b11, b10, b11, x x x x }
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00 + a01 b10   a00 b01 + a01 b11
     *    a10 b00 + a11 b10     a10 b01 + a11 b11
     *             x                    x
     *             x                    x       }
     */
    vecDst = vfmaq(vecDst, vecInA, vecInB);

    mve_pred16_t p0 = vctp16q(2*2);
    /*
     * Store the result in the destination buffer
     * (lower half of the vector)
     */
    vstrhq_p(pOut, vecDst, p0);

    return (ARM_MATH_SUCCESS);
}




__STATIC_FORCEINLINE arm_status arm_mat_mult_f16_3x3_mve(
    const arm_matrix_instance_f16 *pSrcA,
    const arm_matrix_instance_f16 *pSrcB,
    arm_matrix_instance_f16 *pDst)
{
    static const uint16_t offsetA[8] = { 0, 0, 0, 3, 3, 3, 6, 6 };
    /* offsetB allows to read and duplicate 1 row of B */
    static const uint16_t offsetB[8] = { 0, 1, 2, 0, 1, 2, 0, 1 };
    uint16x8_t    vecOffsA, vecOffsB;
    f16x8_t       vecInA, vecInB, vecDst;
    float16_t      *pOut = pDst->pData;  /* output data matrix pointer */

    /*
     * load initial offsets
     */
    vecOffsA = vldrhq_u16((uint16_t const *) offsetA);
    vecOffsB = vldrhq_u16((uint16_t const *) offsetB);

    /*
     * load {a00 a00 a00 a10 a10 a10 a20 a20}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * load {b00 b01 b02 b00 b01 b02 b00 b01}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00       a00 b01     a00 b02
     *    a10 b00       a10 b01     a10 b02
     *    a20 b00       a20 b01}
     */
    vecDst = vmulq(vecInA, vecInB);

    /*
     * move to 2nd column of matrix A
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 1);
    /*
     * load {a01 a01 a01 a11 a11 a11 a21 a21}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * move to next B row
     */
    vecOffsB = vaddq_n_u16(vecOffsB, (uint16_t) 3);
    /*
     * load {b10, b11, b12, b10, b11, b12, b10, b11}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00 + a01 b10   a00 b01 + a01 b11     a00 b02 + a01 b12
     *    a10 b00 + a11 b10     a10 b01 + a11 b11     a10 b02 + a11 b12
     *    a20 b00 + a21 b10     a20 b01 + a21 b11   }
     */
    vecDst = vfmaq(vecDst, vecInA, vecInB);
    /*
     * move to 3rd column of matrix A
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 1);
    /*
     * load {a02 a02 a02 a12 a12 a12 a22 a22}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * move to next B row
     */
    vecOffsB = vaddq_n_u16(vecOffsB, (uint16_t) 3);
    /*
     * load {b20, b21, b22, b20, b21, b22, b20, b21}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  {a00 b00 + a01 b10 + a02 b20  a00 b01 + a01 b11 + a02 b21     a00 b02 + a01 b12 + a02 b22},
     *   a10 b00 + a11 b10 + a12 b20    a10 b01 + a11 b11 + a12 b21     a10 b02 + a11 b12 + a12 b22},
     *   a20 b00 + a21 b10 + a22 b20    a20 b01 + a21 b11 + a22 b21   }
     */
    vecDst = vfmaq(vecDst, vecInA, vecInB);

    /*
     * Store the result in the destination buffer
     */
    vst1q(pOut, vecDst); pOut += 8;

    /* last element computed in scalar mode
     * a20 b02 + a21 b12 + a22 b22
     */
    _Float16 * pA = (_Float16 *)pSrcA->pData;
    _Float16 * pB = (_Float16 *)pSrcB->pData;
    *pOut = pA[2*3] * pB[2] + pA[2*3+1] * pB[3+2] + pA[2*3+2] * pB[2*3+2];

    return (ARM_MATH_SUCCESS);
}





__STATIC_FORCEINLINE arm_status arm_mat_mult_f16_4x4_mve(
    const arm_matrix_instance_f16 *pSrcA,
    const arm_matrix_instance_f16 *pSrcB,
    arm_matrix_instance_f16 *pDst)
{
    /* offsetA allows to read and duplicate 2 successive column elements of A */
    static const uint16_t offsetA[8] = { 0, 0, 0, 0, 4, 4, 4, 4 };
    /* offsetB allows to read and duplicate 1 row of B */
    static const uint16_t offsetB[8] = { 0, 1, 2, 3, 0, 1, 2, 3 };
    uint16x8_t    vecOffsA, vecOffsB;
    f16x8_t       vecInA, vecInB, vecDst0, vecDst1;
    float16_t      *pOut = pDst->pData;  /* output data matrix pointer */

    /*
     * load initial offsets
     */
    vecOffsA = vldrhq_u16((uint16_t const *) offsetA);
    vecOffsB = vldrhq_u16((uint16_t const *) offsetB);

    /*
     * load {a00 a00 a00 a00 a10 a10 a10 a10}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * load {b00 b01 b02 b03 b00 b01 b02 b03}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00       a00 b01     a00 b02     a00 b03
     *    a10 b00       a10 b01     a10 b02     a10 b03 }
     */
    vecDst0 = vmulq(vecInA, vecInB);
    /*
     * jump 2 x A rows (2nd half of matrix)
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 8);
    /*
     * load {a20 a20 a20 a20 a30 a30 a30 a30}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     *  { a20 b00       a20 b01     a20 b02     a20 b03
     *    a30 b00       a30 b01     a30 b02 +   a31 b12 }
     */
    vecDst1 = vmulq(vecInA, vecInB);
    /*
     * rewind back to top half of the A matrix (2nd column)
     */
    vecOffsA = vsubq(vecOffsA, (uint16_t) 7);
    /*
     * load {a01 a01 a01 a01 a11 a11 a11 a11}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * move to next B row
     */
    vecOffsB = vaddq_n_u16(vecOffsB, (uint16_t) 4);
    /*
     * load {b10, b11, b12, b13, b10, b11, b12, b13}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00 + a01 b10         a00 b01 + a01 b11       a00 b02 + a01 b12       a00 b03 + a01 b13
     *    a10 b00 + a11 b10         a10 b01 + a11 b11       a10 b02 + a11 b12       a10 b03 + a11 b13 }
     */
    vecDst0 = vfmaq(vecDst0, vecInA, vecInB);
    /*
     * jump 2 x A rows (2nd half of matrix)
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 8);
    /*
     * load {a21 a21 a21 a21 a31 a31 a31 a31}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     *  {a20 b00 + a21 b10      a20 b01 + a21 b11       a20 b02 + a21 b12       a20 b03 + a21 b13
     *   a30 b00 + a31 b10      a30 b01 + a31 b11       a30 b02 + a31 b12       a30 b03 + a31 b13 }
     */
    vecDst1 = vfmaq(vecDst1, vecInA, vecInB);

    /*
     * rewind back to top half of the A matrix (3rd column)
     */
    vecOffsA = vsubq(vecOffsA, (uint16_t) 7);
    /*
     * load {a02 a02 a02 a02 a12 a12 a12 a12}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * move to next B row
     */
    vecOffsB = vaddq_n_u16(vecOffsB, (uint16_t) 4);
    /*
     * load {b20, b21, b22, b23, b20, b21, b22, b23}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     *  { a00 b00 + a01 b10 + a02 b20    a00 b01 + a01 b11 + a02 b21    a00 b02 + a01 b12 + a02 b22   a00 b03 + a01 b13 + a02 b23
     *    a10 b00 + a11 b10 + a12 b20    a10 b01 + a11 b11 + a12 b21    a10 b02 + a11 b12 + a12 b22   a10 b03 + a11 b13 + a12 b23 }
     */
    vecDst0 = vfmaq(vecDst0, vecInA, vecInB);
    /*
     * jump 2 x A rows
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 8);

    /*
     * load {a22 a22 a22 a22 a32 a32 a32 a32}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     *  {a20 b00 + a21 b10 + a22 b20   a20 b01 + a21 b11 + a22 b21  a20 b02 + a21 b12 + a22 b22    a20 b03 + a21 b13 + a22 b23
     *   a30 b00 + a31 b10 + a32 b20   a30 b01 + a31 b11 + a32 b21  a30 b02 + a31 b12 + a32 b22    a30 b03 + a31 b13 + a32 b23 }
     */
    vecDst1 = vfmaq(vecDst1, vecInA, vecInB);

    /*
     * rewind back to top half of the A matrix (4th column)
     */
    vecOffsA = vsubq(vecOffsA, (uint16_t) 7);
    /*
     * load {a03 a03 a03 a03 a13 a13 a13 a13}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     * move to next B row
     */
    vecOffsB = vaddq_n_u16(vecOffsB, (uint16_t) 4);
    /*
     * load {b30, b31, b32, b33, b30, b31, b32, b33}
     */
    vecInB = vldrhq_gather_shifted_offset((float16_t const *) pSrcB->pData, vecOffsB);
    /*
     * { a00 b00 +...+ a03 b30,    a00 b01 +...+ a03 b31,   a00 b02 +...+ a03 b32,   a00 b03 +...+ a03 b33
     *   a10 b00 +...+ a13 b30,    a10 b01 +...+ a13 b31,   a10 b02 +...+ a13 b32,   a10 b03 +...+ a13 b33 }
     */
    vecDst0 = vfmaq(vecDst0, vecInA, vecInB);
    /*
     * jump 2 x A rows
     */
    vecOffsA = vaddq_n_u16(vecOffsA, (uint16_t) 8);
    /*
     * load {a23 a23 a23 a23 a33 a33 a33 a33}
     */
    vecInA = vldrhq_gather_shifted_offset((float16_t const *) pSrcA->pData, vecOffsA);
    /*
     *  {a20 b00 +...+ a23 b30,   a20 b01 +...+ a23 b31,   a20 b02 +...+ a23 b32,   a20 b03 +...+ a23 b33
     *   a30 b00 +...+ a33 b30,   a30 b01 +...+ a33 b31,   a30 b02 +...+ a33 b32,   a30 b03 +...+ a33 b33 }
     */
    vecDst1 = vfmaq(vecDst1, vecInA, vecInB);

    /*
     * Store the result in the destination buffer
     */
    vst1q(pOut, vecDst0); pOut += 8;
    vst1q(pOut, vecDst1);

    return (ARM_MATH_SUCCESS);
}


arm_status arm_mat_mult_f16(
  const arm_matrix_instance_f16 * pSrcA,
  const arm_matrix_instance_f16 * pSrcB,
  arm_matrix_instance_f16 * pDst)
{
       float16_t  *pInB = pSrcB->pData;        /* input data matrix pointer B */
    float16_t  *pInA = pSrcA->pData;        /* input data matrix pointer A  */
    float16_t  *pOut = pDst->pData;         /* output data matrix pointer */
    int         numRowsA = pSrcA->numRows;  /* number of rows of input matrix A */
    int         numColsB = pSrcB->numCols;  /* number of columns of input matrix B */
    int         numColsA = pSrcA->numCols;  /* number of columns of input matrix A */
    uint32_t    blkCnt;                     /* loop counters */
    int         i;


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrcA->numCols != pSrcB->numRows) ||
      (pSrcA->numRows != pDst->numRows)  ||
      (pSrcB->numCols != pDst->numCols)    )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    return(ARM_MATH_SIZE_MISMATCH);
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */
{
    /* small squared matrix specialized routines */
    if(numRowsA == numColsB && numColsB == numColsA) {
        if(numRowsA == 2)
            return arm_mat_mult_f16_2x2_mve(pSrcA, pSrcB, pDst);
        else if(numRowsA == 3)
            return arm_mat_mult_f16_3x3_mve(pSrcA, pSrcB, pDst);
        else if(numRowsA == 4)
            return arm_mat_mult_f16_4x4_mve(pSrcA, pSrcB, pDst);
    }

    /* main loop process 4 rows */
    i = numRowsA / 4;
    while(i > 0)
    {
        float16_t   *pInA0, *pInA1, *pInA2, *pInA3;
        float16_t   *pInB0;
        float16_t   *pOut0, *pOut1, *pOut2, *pOut3;
        f16x8_t    vecMac0, vecMac1, vecMac2, vecMac3;
        f16x8_t    vecInB;

        /* pointers to 4 consecutive output rows */
        pOut0 = pOut;
        pOut1 = pOut0 + numColsB;
        pOut2 = pOut1 + numColsB;
        pOut3 = pOut2 + numColsB;
        pInB0 = pInB;

        int       k = numColsB >> 3;
        while(k > 0)
        {
            /* pointers to 4 consecutive Matrix A rows */
            pInA0 = pInA;
            pInA1 = pInA0 + numColsA;
            pInA2 = pInA1 + numColsA;
            pInA3 = pInA2 + numColsA;

            vecMac0 = vdupq_n_f16(0.0f16);
            vecMac1 = vdupq_n_f16(0.0f16);
            vecMac2 = vdupq_n_f16(0.0f16);
            vecMac3 = vdupq_n_f16(0.0f16);

            blkCnt = numColsA;

            while (blkCnt > 0U)
            {
                /*
                 * load {bi,4n+0, bi,4n+1, bi,4n+2, bi,4n+3..., bi,4n+7}
                 */
                vecInB = *(f16x8_t *)pInB0; /* vldrhq_f16(pInB0, 0); */

                vecMac0 = vfmaq(vecMac0, vecInB, *pInA0++);
                vecMac1 = vfmaq(vecMac1, vecInB, *pInA1++);
                vecMac2 = vfmaq(vecMac2, vecInB, *pInA2++);
                vecMac3 = vfmaq(vecMac3, vecInB, *pInA3++);

                pInB0 = pInB0 + numColsB;
                /*
                 * Decrement the blockSize loop counter
                 */
                blkCnt--;
            }

            /* Store the results (4 x 8 block) in the destination buffer */
            vst1q(pOut0, vecMac0);  pOut0 += 8;
            vst1q(pOut1, vecMac1);  pOut1 += 8;
            vst1q(pOut2, vecMac2);  pOut2 += 8;
            vst1q(pOut3, vecMac3);  pOut3 += 8;
            /*
             * rewind
             */
            pInB0 -= (numColsB * numColsA) - 8;
            k--;
        }

        int       colBLeft = numColsB & 7;
        if (colBLeft)
        {
            pInA0 = pInA;
            pInA1 = pInA0 + numColsA;
            pInA2 = pInA1 + numColsA;
            pInA3 = pInA2 + numColsA;
            mve_pred16_t p0 = vctp16q(colBLeft);

            vecMac0 = vdupq_n_f16(0.0f16);
            vecMac1 = vdupq_n_f16(0.0f16);
            vecMac2 = vdupq_n_f16(0.0f16);
            vecMac3 = vdupq_n_f16(0.0f16);

            blkCnt = numColsA;

            while (blkCnt > 0U)
            {
                /*
                 * load {bi,4n+0, bi,4n+1, bi,4n+2, ..bi,4n+colBLeft-1, 0, ..}
                 */
                vecInB = vldrhq_z_f16(pInB0, p0);

                vecMac0 = vfmaq(vecMac0, vecInB, *pInA0++);
                vecMac1 = vfmaq(vecMac1, vecInB, *pInA1++);
                vecMac2 = vfmaq(vecMac2, vecInB, *pInA2++);
                vecMac3 = vfmaq(vecMac3, vecInB, *pInA3++);

                pInB0 = pInB0 + numColsB;
                /*
                 * Decrement the blockSize loop counter
                 */
                blkCnt--;
            }

            /* Store the results (4 x colBLeft block) in the destination buffer */
            vstrhq_p_f16(pOut0, vecMac0, p0);
            vstrhq_p_f16(pOut1, vecMac1, p0);
            vstrhq_p_f16(pOut2, vecMac2, p0);
            vstrhq_p_f16(pOut3, vecMac3, p0);
        }

        pInA += 4 * numColsA;
        pOut += 4 * numColsB;
        i--;
    }

    /*
     * non multiple of 4 rows for Matrix A
     * process single row
     */
    if (numRowsA & 3)
    {
        i = numRowsA & 3;
        do
        {
            float16_t   *pInA0;
            float16_t   *pInB0;
            float16_t   *pOut0;
            f16x8_t    vecInB;
            f16x8_t    vecMac0;

            pOut0 = pOut;
            pInB0 = pInB;

            int       k = numColsB >> 3;
            while(k > 0)
            {
                pInA0 = pInA;

                vecMac0 = vdupq_n_f16(0.0f16);
                blkCnt = numColsA;

                while (blkCnt > 0U)
                {
                    /*
                     * load {bi,4n+0, bi,4n+1, bi,4n+2, bi,4n+3, ...bi,4n+7}
                     */
                    vecInB = *(f16x8_t *)pInB0; /* vldrhq_f16(pInB0, 0); */

                    vecMac0 = vfmaq(vecMac0, vecInB, *pInA0++);

                    pInB0 = pInB0 + numColsB;
                    /*
                     * Decrement the blockSize loop counter
                     */
                    blkCnt--;
                }
                /* Store the results (1 x 8 block) in the destination buffer */
                vst1q(pOut0, vecMac0);   pOut0 += 8;
                /*
                 * rewind
                 */
                pInB0 -= (numColsB * numColsA) - 8;
                k--;
            }

            int  colBLeft = numColsB & 7;
            if (colBLeft)
            {
                pInA0 = pInA;
                mve_pred16_t p0 = vctp16q(colBLeft);

                vecMac0 = vdupq_n_f16(0.0f16);
                blkCnt = numColsA;

                while (blkCnt > 0U)
                {
                    /*
                     * load {bi,4n+0, bi,4n+1, bi,4n+2, ..., bi,4n+colBLeft, 0, ...}
                     */
                    vecInB = vldrhq_z_f16(pInB0, p0);

                    vecMac0 = vfmaq(vecMac0, vecInB, *pInA0++);

                    pInB0 = pInB0 + numColsB;
                    /*
                     * Decrement the blockSize loop counter
                     */
                    blkCnt--;
                }
                /* Store the results (1 x colBLeft block) in the destination buffer */
                vstrhq_p_f16(pOut0, vecMac0, p0);
            }

            pInA += 1 * numColsA;
            pOut += 1 * numColsB;
        }
        while (--i);
    }
    /*
     * Return to application
     */
    return (ARM_MATH_SUCCESS);
  }
}
#else


arm_status arm_mat_mult_f16(
  const arm_matrix_instance_f16 * pSrcA,
  const arm_matrix_instance_f16 * pSrcB,
        arm_matrix_instance_f16 * pDst)
{
  float16_t *pIn1 = pSrcA->pData;                /* Input data matrix pointer A */
  float16_t *pIn2 = pSrcB->pData;                /* Input data matrix pointer B */
  float16_t *pInA = pSrcA->pData;                /* Input data matrix pointer A */
  float16_t *pInB = pSrcB->pData;                /* Input data matrix pointer B */
  float16_t *pOut = pDst->pData;                 /* Output data matrix pointer */
  float16_t *px;                                 /* Temporary output data matrix pointer */
  _Float16 sum;                                 /* Accumulator */
  uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
  uint32_t col, i = 0U, row = numRowsA, colCnt;  /* Loop counters */
  arm_status status;                             /* Status of matrix multiplication */

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
        sum = 0.0f16;

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
          sum += (_Float16)*pIn1++ * (_Float16)*pIn2;
          pIn2 += numColsB;

          sum += (_Float16)*pIn1++ * (_Float16)*pIn2;
          pIn2 += numColsB;

          sum += (_Float16)*pIn1++ * (_Float16)*pIn2;
          pIn2 += numColsB;

          sum += (_Float16)*pIn1++ * (_Float16)*pIn2;
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
          sum += (_Float16)*pIn1++ * (_Float16)*pIn2;
          pIn2 += numColsB;

          /* Decrement loop counter */
          colCnt--;
        }

        /* Store result in destination buffer */
        *px++ = sum;

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

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of MatrixMult group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

