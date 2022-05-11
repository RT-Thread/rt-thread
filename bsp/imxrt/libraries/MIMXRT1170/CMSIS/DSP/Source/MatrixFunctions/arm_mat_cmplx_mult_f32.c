/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_cmplx_mult_f32.c
 * Description:  Floating-point matrix multiplication
 *
 * $Date:        18. March 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_math.h"

/**
  @ingroup groupMatrix
 */

/**
  @defgroup CmplxMatrixMult  Complex Matrix Multiplication

  Complex Matrix multiplication is only defined if the number of columns of the
  first matrix equals the number of rows of the second matrix.
  Multiplying an <code>M x N</code> matrix with an <code>N x P</code> matrix results
  in an <code>M x P</code> matrix.
  @par
  When matrix size checking is enabled, the functions check:
   - that the inner dimensions of <code>pSrcA</code> and <code>pSrcB</code> are equal;
   - that the size of the output matrix equals the outer dimensions of <code>pSrcA</code> and <code>pSrcB</code>.
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
#if defined(ARM_MATH_NEON)
arm_status arm_mat_cmplx_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst)
{
  float32_t *pIn1 = pSrcA->pData;                /* input data matrix pointer A */
  float32_t *pIn2 = pSrcB->pData;                /* input data matrix pointer B */
  float32_t *pInA = pSrcA->pData;                /* input data matrix pointer A  */
  float32_t *pOut = pDst->pData;                 /* output data matrix pointer */
  float32_t *px;                                 /* Temporary output data matrix pointer */
  uint16_t numRowsA = pSrcA->numRows;            /* number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* number of columns of input matrix A */
  float32_t sumReal1, sumImag1;                  /* accumulator */
  float32_t a0, b0, c0, d0;
  float32_t a1, a1B,b1, b1B, c1, d1;
  float32_t sumReal2, sumImag2;                  /* accumulator */


  float32x4x2_t a0V, a1V;
  float32x4_t accR0,accI0, accR1,accI1,tempR, tempI;
  float32x2_t accum = vdup_n_f32(0);
  float32_t *pIn1B = pSrcA->pData;

  uint16_t col, i = 0U, j, rowCnt, row = numRowsA, colCnt;      /* loop counters */
  arm_status status;                             /* status of matrix multiplication */
  float32_t sumReal1B, sumImag1B;
  float32_t sumReal2B, sumImag2B;
  float32_t *pxB;

#ifdef ARM_MATH_MATRIX_CHECK


  /* Check for matrix mismatch condition */
  if ((pSrcA->numCols != pSrcB->numRows) ||
     (pSrcA->numRows != pDst->numRows) || (pSrcB->numCols != pDst->numCols))
  {

    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*      #ifdef ARM_MATH_MATRIX_CHECK    */

  {
    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */

    rowCnt = row >> 1;

    /* Row loop */
    while (rowCnt > 0U)
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + 2 * i;
      pxB = px + 2 * numColsB;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      j = 0U;

      /* Column loop */
      while (col > 0U)
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sumReal1 = 0.0f;
        sumImag1 = 0.0f;
        sumReal1B = 0.0f;
        sumImag1B = 0.0f;

        sumReal2 = 0.0f;
        sumImag2 = 0.0f;
        sumReal2B = 0.0f;
        sumImag2B = 0.0f;

        /* Initiate the pointer pIn1 to point to the starting address of the column being processed */
        pIn1 = pInA;
        pIn1B = pIn1 + 2*numColsA;

        accR0 = vdupq_n_f32(0.0);
        accI0 = vdupq_n_f32(0.0);
        accR1 = vdupq_n_f32(0.0);
        accI1 = vdupq_n_f32(0.0);

        /* Compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2;

        /* Matrix multiplication */
        while (colCnt > 0U)
        {
          /* Reading real part of complex matrix A */
          a0V = vld2q_f32(pIn1);  // load & separate real/imag pSrcA (de-interleave 2)
          a1V = vld2q_f32(pIn1B);  // load & separate real/imag pSrcA (de-interleave 2)

          pIn1 += 8;
          pIn1B += 8;

          tempR[0] = *pIn2;
          tempI[0] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          tempR[1] = *pIn2;
          tempI[1] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          tempR[2] = *pIn2;
          tempI[2] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          tempR[3] = *pIn2;
          tempI[3] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          accR0 = vmlaq_f32(accR0,a0V.val[0],tempR);
          accR0 = vmlsq_f32(accR0,a0V.val[1],tempI);

          accI0 = vmlaq_f32(accI0,a0V.val[1],tempR);
          accI0 = vmlaq_f32(accI0,a0V.val[0],tempI);

          accR1 = vmlaq_f32(accR1,a1V.val[0],tempR);
          accR1 = vmlsq_f32(accR1,a1V.val[1],tempI);

          accI1 = vmlaq_f32(accI1,a1V.val[1],tempR);
          accI1 = vmlaq_f32(accI1,a1V.val[0],tempI);

          /* Decrement the loop count */
          colCnt--;
        }

        accum = vpadd_f32(vget_low_f32(accR0), vget_high_f32(accR0));
        sumReal1 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(accI0), vget_high_f32(accI0));
        sumImag1 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(accR1), vget_high_f32(accR1));
        sumReal1B += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(accI1), vget_high_f32(accI1));
        sumImag1B += accum[0] + accum[1];

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining MACs here.
         ** No loop unrolling is used. */
        colCnt = numColsA & 3;

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2)*b(2,1) + ... + a(m,p)*b(p,n) */
          a1 = *pIn1;
          a1B = *pIn1B;

          c1 = *pIn2;

          b1 = *(pIn1 + 1U);
          b1B = *(pIn1B + 1U);

          d1 = *(pIn2 + 1U);

          sumReal1 += a1 * c1;
          sumImag1 += b1 * c1;

          sumReal1B += a1B * c1;
          sumImag1B += b1B * c1;

          pIn1 += 2U;
          pIn1B += 2U;
          pIn2 += 2 * numColsB;

          sumReal2 -= b1 * d1;
          sumImag2 += a1 * d1;

          sumReal2B -= b1B * d1;
          sumImag2B += a1B * d1;

          /* Decrement the loop counter */
          colCnt--;
        }

        sumReal1 += sumReal2;
        sumImag1 += sumImag2;

        sumReal1B += sumReal2B;
        sumImag1B += sumImag2B;

        /* Store the result in the destination buffer */
        *px++ = sumReal1;
        *px++ = sumImag1;
        *pxB++ = sumReal1B;
        *pxB++ = sumImag1B;

        /* Update the pointer pIn2 to point to the  starting address of the next column */
        j++;
        pIn2 = pSrcB->pData + 2U * j;

        /* Decrement the column loop counter */
        col--;
      }

      /* Update the pointer pInA to point to the  starting address of the next 2 row */
      i = i + 2*numColsB;
      pInA = pInA + 4 * numColsA;

      /* Decrement the row loop counter */
      rowCnt--;
    }

    rowCnt = row & 1;
    while (rowCnt > 0U)
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + 2 * i;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      j = 0U;

      /* Column loop */
      while (col > 0U)
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sumReal1 = 0.0f;
        sumImag1 = 0.0f;

        sumReal2 = 0.0f;
        sumImag2 = 0.0f;

        /* Initiate the pointer pIn1 to point to the starting address of the column being processed */
        pIn1 = pInA;

        accR0 = vdupq_n_f32(0.0);
        accI0 = vdupq_n_f32(0.0);

        /* Compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2;

        /* Matrix multiplication */
        while (colCnt > 0U)
        {
          /* Reading real part of complex matrix A */
          a0V = vld2q_f32(pIn1);  // load & separate real/imag pSrcA (de-interleave 2)
          pIn1 += 8;

          tempR[0] = *pIn2;
          tempI[0] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          tempR[1] = *pIn2;
          tempI[1] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          tempR[2] = *pIn2;
          tempI[2] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          tempR[3] = *pIn2;
          tempI[3] = *(pIn2 + 1U);
          pIn2 += 2 * numColsB;

          accR0 = vmlaq_f32(accR0,a0V.val[0],tempR);
          accR0 = vmlsq_f32(accR0,a0V.val[1],tempI);

          accI0 = vmlaq_f32(accI0,a0V.val[1],tempR);
          accI0 = vmlaq_f32(accI0,a0V.val[0],tempI);

          /* Decrement the loop count */
          colCnt--;
        }

        accum = vpadd_f32(vget_low_f32(accR0), vget_high_f32(accR0));
        sumReal1 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(accI0), vget_high_f32(accI0));
        sumImag1 += accum[0] + accum[1];

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining MACs here.
         ** No loop unrolling is used. */
        colCnt = numColsA & 3;

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2)*b(2,1) + ... + a(m,p)*b(p,n) */
          a1 = *pIn1;
          c1 = *pIn2;

          b1 = *(pIn1 + 1U);
          d1 = *(pIn2 + 1U);

          sumReal1 += a1 * c1;
          sumImag1 += b1 * c1;

          pIn1 += 2U;
          pIn2 += 2 * numColsB;

          sumReal2 -= b1 * d1;
          sumImag2 += a1 * d1;

          /* Decrement the loop counter */
          colCnt--;
        }

        sumReal1 += sumReal2;
        sumImag1 += sumImag2;

        /* Store the result in the destination buffer */
        *px++ = sumReal1;
        *px++ = sumImag1;

        /* Update the pointer pIn2 to point to the  starting address of the next column */
        j++;
        pIn2 = pSrcB->pData + 2U * j;

        /* Decrement the column loop counter */
        col--;

      }

      /* Update the pointer pInA to point to the  starting address of the next row */
      i = i + numColsB;
      pInA = pInA + 2 * numColsA;

      /* Decrement the row loop counter */
      rowCnt--;

    }

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}
#else
arm_status arm_mat_cmplx_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
        arm_matrix_instance_f32 * pDst)
{
  float32_t *pIn1 = pSrcA->pData;                /* Input data matrix pointer A */
  float32_t *pIn2 = pSrcB->pData;                /* Input data matrix pointer B */
  float32_t *pInA = pSrcA->pData;                /* Input data matrix pointer A */
  float32_t *pOut = pDst->pData;                 /* Output data matrix pointer */
  float32_t *px;                                 /* Temporary output data matrix pointer */
  uint16_t numRowsA = pSrcA->numRows;            /* Number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* Number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* Number of columns of input matrix A */
  float32_t sumReal, sumImag;                    /* Accumulator */
  float32_t a1, b1, c1, d1;
  uint32_t col, i = 0U, j, row = numRowsA, colCnt; /* loop counters */
  arm_status status;                             /* status of matrix multiplication */

#if defined (ARM_MATH_LOOPUNROLL)
  float32_t a0, b0, c0, d0;
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
        sumReal = 0.0f;
        sumImag = 0.0f;

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

#endif /* #if defined(ARM_MATH_NEON) */

/**
  @} end of MatrixMult group
 */
