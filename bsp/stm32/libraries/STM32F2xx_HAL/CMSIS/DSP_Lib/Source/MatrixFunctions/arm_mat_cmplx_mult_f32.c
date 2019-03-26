/* ----------------------------------------------------------------------      
* Copyright (C) 2010-2014 ARM Limited. All rights reserved. 
*      
* $Date:        19. March 2015
* $Revision: 	V.1.4.5
*      
* Project:      CMSIS DSP Library 
* Title:	    arm_mat_cmplx_mult_f32.c      
*      
* Description:  Floating-point matrix multiplication.      
*      
* Target Processor:          Cortex-M4/Cortex-M3/Cortex-M0
*
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the 
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.    
* -------------------------------------------------------------------- */
#include "arm_math.h"

/**      
 * @ingroup groupMatrix      
 */

/**      
 * @defgroup CmplxMatrixMult  Complex Matrix Multiplication     
 *     
 * Complex Matrix multiplication is only defined if the number of columns of the      
 * first matrix equals the number of rows of the second matrix.      
 * Multiplying an <code>M x N</code> matrix with an <code>N x P</code> matrix results      
 * in an <code>M x P</code> matrix.      
 * When matrix size checking is enabled, the functions check: (1) that the inner dimensions of      
 * <code>pSrcA</code> and <code>pSrcB</code> are equal; and (2) that the size of the output      
 * matrix equals the outer dimensions of <code>pSrcA</code> and <code>pSrcB</code>.      
 */


/**      
 * @addtogroup CmplxMatrixMult      
 * @{      
 */

/**      
 * @brief Floating-point Complex matrix multiplication.      
 * @param[in]       *pSrcA points to the first input complex matrix structure      
 * @param[in]       *pSrcB points to the second input complex matrix structure      
 * @param[out]      *pDst points to output complex matrix structure      
 * @return     		The function returns either      
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 */

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
  float32_t a1, b1, c1, d1;
  float32_t sumReal2, sumImag2;                  /* accumulator */


  /* Run the below code for Cortex-M4 and Cortex-M3 */

  uint16_t col, i = 0u, j, row = numRowsA, colCnt;      /* loop counters */
  arm_status status;                             /* status of matrix multiplication */

#ifdef ARM_MATH_MATRIX_CHECK


  /* Check for matrix mismatch condition */
  if((pSrcA->numCols != pSrcB->numRows) ||
     (pSrcA->numRows != pDst->numRows) || (pSrcB->numCols != pDst->numCols))
  {

    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*      #ifdef ARM_MATH_MATRIX_CHECK    */

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

      j = 0u;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sumReal1 = 0.0f;
        sumImag1 = 0.0f;

        sumReal2 = 0.0f;
        sumImag2 = 0.0f;

        /* Initiate the pointer pIn1 to point to the starting address of the column being processed */
        pIn1 = pInA;

        /* Apply loop unrolling and compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2;

        /* matrix multiplication        */
        while(colCnt > 0u)
        {

          /* Reading real part of complex matrix A */
          a0 = *pIn1;

          /* Reading real part of complex matrix B */
          c0 = *pIn2;

          /* Reading imaginary part of complex matrix A */
          b0 = *(pIn1 + 1u);

          /* Reading imaginary part of complex matrix B */
          d0 = *(pIn2 + 1u);

          sumReal1 += a0 * c0;
          sumImag1 += b0 * c0;

          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          sumReal2 -= b0 * d0;
          sumImag2 += a0 * d0;

          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */

          a1 = *pIn1;
          c1 = *pIn2;

          b1 = *(pIn1 + 1u);
          d1 = *(pIn2 + 1u);

          sumReal1 += a1 * c1;
          sumImag1 += b1 * c1;

          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          sumReal2 -= b1 * d1;
          sumImag2 += a1 * d1;

          a0 = *pIn1;
          c0 = *pIn2;

          b0 = *(pIn1 + 1u);
          d0 = *(pIn2 + 1u);

          sumReal1 += a0 * c0;
          sumImag1 += b0 * c0;

          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          sumReal2 -= b0 * d0;
          sumImag2 += a0 * d0;

          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */

          a1 = *pIn1;
          c1 = *pIn2;

          b1 = *(pIn1 + 1u);
          d1 = *(pIn2 + 1u);

          sumReal1 += a1 * c1;
          sumImag1 += b1 * c1;

          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          sumReal2 -= b1 * d1;
          sumImag2 += a1 * d1;

          /* Decrement the loop count */
          colCnt--;
        }

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining MACs here.      
         ** No loop unrolling is used. */
        colCnt = numColsA % 0x4u;

        while(colCnt > 0u)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */
          a1 = *pIn1;
          c1 = *pIn2;

          b1 = *(pIn1 + 1u);
          d1 = *(pIn2 + 1u);

          sumReal1 += a1 * c1;
          sumImag1 += b1 * c1;

          pIn1 += 2u;
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
        pIn2 = pSrcB->pData + 2u * j;

        /* Decrement the column loop counter */
        col--;

      } while(col > 0u);

      /* Update the pointer pInA to point to the  starting address of the next row */
      i = i + numColsB;
      pInA = pInA + 2 * numColsA;

      /* Decrement the row loop counter */
      row--;

    } while(row > 0u);

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**      
 * @} end of MatrixMult group      
 */
