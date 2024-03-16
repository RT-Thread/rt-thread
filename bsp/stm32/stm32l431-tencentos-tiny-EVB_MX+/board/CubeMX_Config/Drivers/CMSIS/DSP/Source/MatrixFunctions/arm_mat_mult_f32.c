/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_mult_f32.c
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
 * @ingroup groupMatrix
 */

/**
 * @defgroup MatrixMult Matrix Multiplication
 *
 * Multiplies two matrices.
 *
 * \image html MatrixMultiplication.gif "Multiplication of two 3 x 3 matrices"

 * Matrix multiplication is only defined if the number of columns of the
 * first matrix equals the number of rows of the second matrix.
 * Multiplying an <code>M x N</code> matrix with an <code>N x P</code> matrix results
 * in an <code>M x P</code> matrix.
 * When matrix size checking is enabled, the functions check: (1) that the inner dimensions of
 * <code>pSrcA</code> and <code>pSrcB</code> are equal; and (2) that the size of the output
 * matrix equals the outer dimensions of <code>pSrcA</code> and <code>pSrcB</code>.
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
#if defined(ARM_MATH_NEON)

#define GROUPOFROWS 8

arm_status arm_mat_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst)
{
  float32_t *pIn1 = pSrcA->pData;                /* input data matrix pointer A */
  float32_t *pIn2 = pSrcB->pData;                /* input data matrix pointer B */
  float32_t *pInA = pSrcA->pData;                /* input data matrix pointer A  */
  float32_t *pOut = pDst->pData;                 /* output data matrix pointer */
  float32_t *px;                                 /* Temporary output data matrix pointer */
  float32_t sum;                                 /* Accumulator */
  uint16_t numRowsA = pSrcA->numRows;            /* number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* number of columns of input matrix A */


  float32_t in1, in2, in3, in4;
  uint16_t col, i = 0U, j, row = numRowsA, rowCnt, colCnt;      /* loop counters */
  arm_status status;                             /* status of matrix multiplication */

  float32x4_t a0V, a1V, a2V, a3V, a4V, a5V, a6V, a7V;
  float32x4_t acc0,acc1,acc2,acc3,acc4,acc5,acc6,acc7,temp;
  float32x2_t accum = vdup_n_f32(0);
  float32_t *pIn1B = pSrcA->pData;    
  float32_t *pIn1C = pSrcA->pData;    
  float32_t *pIn1D = pSrcA->pData;  
  float32_t *pIn1E = pSrcA->pData; 
  float32_t *pIn1F = pSrcA->pData; 
  float32_t *pIn1G = pSrcA->pData; 
  float32_t *pIn1H = pSrcA->pData;   

  float32_t *pxB,*pxC, *pxD, *pxE, *pxF, *pxG, *pxH;                                 /* Temporary output data matrix pointer */
  float32_t sum0,sum1, sum2,sum3, sum4, sum5 , sum6, sum7;

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
    /* Row loop */
    rowCnt = row >> 3;

    while(rowCnt > 0)
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + GROUPOFROWS*i;
      pxB = px + numColsB;
      pxC = px + 2*numColsB;
      pxD = px + 3*numColsB;
      pxE = px + 4*numColsB;
      pxF = px + 5*numColsB;
      pxG = px + 6*numColsB;
      pxH = px + 7*numColsB;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      j = 0U;

      /* Column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum0 = 0.0f;
        sum1 = 0.0f;
        sum2 = 0.0f;
        sum3 = 0.0f;
        sum4 = 0.0f;
        sum5 = 0.0f;
        sum6 = 0.0f;
        sum7 = 0.0f;

        /* Initiate the pointer pIn1 to point to the starting address of the column being processed */
        pIn1 = pInA;
        pIn1B = pIn1 + numColsA;
        pIn1C = pIn1 + 2*numColsA;
        pIn1D = pIn1 + 3*numColsA;
        pIn1E = pIn1 + 4*numColsA;
        pIn1F = pIn1 + 5*numColsA;
        pIn1G = pIn1 + 6*numColsA;
        pIn1H = pIn1 + 7*numColsA;

        acc0 = vdupq_n_f32(0.0);
        acc1 = vdupq_n_f32(0.0);
        acc2 = vdupq_n_f32(0.0);
        acc3 = vdupq_n_f32(0.0);
        acc4 = vdupq_n_f32(0.0);
        acc5 = vdupq_n_f32(0.0);
        acc6 = vdupq_n_f32(0.0);
        acc7 = vdupq_n_f32(0.0);

        /* Compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2U;

        /* Matrix multiplication */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2)*b(2,1) + ... + a(m,p)*b(p,n) */
          a0V = vld1q_f32(pIn1);  
          a1V = vld1q_f32(pIn1B);  
          a2V = vld1q_f32(pIn1C); 
          a3V = vld1q_f32(pIn1D); 
          a4V = vld1q_f32(pIn1E); 
          a5V = vld1q_f32(pIn1F); 
          a6V = vld1q_f32(pIn1G); 
          a7V = vld1q_f32(pIn1H); 

	  pIn1 += 4;
          pIn1B += 4;
          pIn1C += 4;
          pIn1D += 4;
          pIn1E += 4;
          pIn1F += 4;
          pIn1G += 4;
          pIn1H += 4;
          
          temp[0] = *pIn2;
          pIn2 += numColsB;
          temp[1] = *pIn2;
          pIn2 += numColsB;
          temp[2] = *pIn2;
          pIn2 += numColsB;
          temp[3] = *pIn2;
          pIn2 += numColsB;

          acc0 = vmlaq_f32(acc0,a0V,temp);
          acc1 = vmlaq_f32(acc1,a1V,temp);
          acc2 = vmlaq_f32(acc2,a2V,temp);
          acc3 = vmlaq_f32(acc3,a3V,temp);
          acc4 = vmlaq_f32(acc4,a4V,temp);
          acc5 = vmlaq_f32(acc5,a5V,temp);
          acc6 = vmlaq_f32(acc6,a6V,temp);
          acc7 = vmlaq_f32(acc7,a7V,temp);

          /* Decrement the loop count */
          colCnt--;
        }

        accum = vpadd_f32(vget_low_f32(acc0), vget_high_f32(acc0));
        sum0 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc1), vget_high_f32(acc1));
        sum1 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc2), vget_high_f32(acc2));
        sum2 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc3), vget_high_f32(acc3));
        sum3 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc4), vget_high_f32(acc4));
        sum4 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc5), vget_high_f32(acc5));
        sum5 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc6), vget_high_f32(acc6));
        sum6 += accum[0] + accum[1];

        accum = vpadd_f32(vget_low_f32(acc7), vget_high_f32(acc7));
        sum7 += accum[0] + accum[1];

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining MACs here.
         ** No loop unrolling is used. */
        colCnt = numColsA & 3;

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2)*b(2,1) + ... + a(m,p)*b(p,n) */
          sum0 += *pIn1++ * (*pIn2);
          sum1 += *pIn1B++ * (*pIn2);
          sum2 += *pIn1C++ * (*pIn2);
          sum3 += *pIn1D++ * (*pIn2);
          sum4 += *pIn1E++ * (*pIn2);
          sum5 += *pIn1F++ * (*pIn2);
          sum6 += *pIn1G++ * (*pIn2);
          sum7 += *pIn1H++ * (*pIn2);
          pIn2 += numColsB;

          /* Decrement the loop counter */
          colCnt--;
        }

        /* Store the result in the destination buffer */
        *px++ = sum0;
        *pxB++ = sum1;
        *pxC++ = sum2;
        *pxD++ = sum3;
        *pxE++ = sum4;
        *pxF++ = sum5;
        *pxG++ = sum6;
        *pxH++ = sum7;

        /* Update the pointer pIn2 to point to the  starting address of the next column */
        j++;
        pIn2 = pSrcB->pData + j;

        /* Decrement the column loop counter */
        col--;

      } while (col > 0U);

      /* Update the pointer pInA to point to the  starting address of the next row */
      i = i + numColsB;
      pInA = pInA + GROUPOFROWS*numColsA;

      /* Decrement the row loop counter */
      rowCnt--;
    } 

    /*

    i was the index of a group of rows computed by previous loop.
    Now i is the index of a row since below code is computing row per row
    and no more group of row per group of rows.

    */

    i = GROUPOFROWS*i;
    rowCnt = row & 7;

    while(rowCnt > 0)
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + i;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      j = 0U;

      /* Column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum = 0.0f;

        /* Initiate the pointer pIn1 to point to the starting address of the column being processed */
        pIn1 = pInA;

        acc0 = vdupq_n_f32(0.0);

        /* Compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2U;

        /* Matrix multiplication   */
        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2)*b(2,1) + ... + a(m,p)*b(p,n) */
          a0V = vld1q_f32(pIn1);  // load & separate real/imag pSrcA (de-interleave 2)
          pIn1 += 4;
          
          temp[0] = *pIn2;
          pIn2 += numColsB;
          temp[1] = *pIn2;
          pIn2 += numColsB;
          temp[2] = *pIn2;
          pIn2 += numColsB;
          temp[3] = *pIn2;
          pIn2 += numColsB;

          acc0 = vmlaq_f32(acc0,a0V,temp);

          /* Decrement the loop count */
          colCnt--;
        }

        accum = vpadd_f32(vget_low_f32(acc0), vget_high_f32(acc0));
        sum += accum[0] + accum[1];

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining MACs here.
         ** No loop unrolling is used. */
        colCnt = numColsA % 0x4U;

        while (colCnt > 0U)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2)*b(2,1) + ... + a(m,p)*b(p,n) */
          sum += *pIn1++ * (*pIn2);
          pIn2 += numColsB;

          /* Decrement the loop counter */
          colCnt--;
        }

        /* Store the result in the destination buffer */
        *px++ = sum;

        /* Update the pointer pIn2 to point to the  starting address of the next column */
        j++;
        pIn2 = pSrcB->pData + j;

        /* Decrement the column loop counter */
        col--;

      } while (col > 0U);


      /* Update the pointer pInA to point to the  starting address of the next row */
      i = i + numColsB;
      pInA = pInA + numColsA;

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
arm_status arm_mat_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
        arm_matrix_instance_f32 * pDst)
{
  float32_t *pIn1 = pSrcA->pData;                /* Input data matrix pointer A */
  float32_t *pIn2 = pSrcB->pData;                /* Input data matrix pointer B */
  float32_t *pInA = pSrcA->pData;                /* Input data matrix pointer A */
  float32_t *pInB = pSrcB->pData;                /* Input data matrix pointer B */
  float32_t *pOut = pDst->pData;                 /* Output data matrix pointer */
  float32_t *px;                                 /* Temporary output data matrix pointer */
  float32_t sum;                                 /* Accumulator */
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
        sum = 0.0f;

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
          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += *pIn1++ * *pIn2;
          pIn2 += numColsB;

          sum += *pIn1++ * *pIn2;
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
          sum += *pIn1++ * *pIn2;
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

#endif /* #if defined(ARM_MATH_NEON) */

/**
 * @} end of MatrixMult group
 */
