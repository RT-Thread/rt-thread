/* ----------------------------------------------------------------------      
* Copyright (C) 2010-2014 ARM Limited. All rights reserved. 
*      
* $Date:        19. March 2015
* $Revision: 	V.1.4.5
*      
* Project:      CMSIS DSP Library 
* Title:	    arm_mat_cmplx_mult_q31.c      
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
 * @addtogroup CmplxMatrixMult      
 * @{      
 */

/**      
 * @brief Q31 Complex matrix multiplication      
 * @param[in]       *pSrcA points to the first input complex matrix structure      
 * @param[in]       *pSrcB points to the second input complex matrix structure      
 * @param[out]      *pDst points to output complex matrix structure      
 * @return     		The function returns either      
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 *      
 * \par      
 * The function is implemented using an internal 64-bit accumulator.      
 * The accumulator has a 2.62 format and maintains full precision of the intermediate      
 * multiplication results but provides only a single guard bit. There is no saturation      
 * on intermediate additions. Thus, if the accumulator overflows it wraps around and      
 * distorts the result. The input signals should be scaled down to avoid intermediate      
 * overflows. The input is thus scaled down by log2(numColsA) bits      
 * to avoid overflows, as a total of numColsA additions are performed internally.      
 * The 2.62 accumulator is right shifted by 31 bits and saturated to 1.31 format to yield the final result.      
 *      
 *      
 */

arm_status arm_mat_cmplx_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst)
{
  q31_t *pIn1 = pSrcA->pData;                    /* input data matrix pointer A */
  q31_t *pIn2 = pSrcB->pData;                    /* input data matrix pointer B */
  q31_t *pInA = pSrcA->pData;                    /* input data matrix pointer A  */
  q31_t *pOut = pDst->pData;                     /* output data matrix pointer */
  q31_t *px;                                     /* Temporary output data matrix pointer */
  uint16_t numRowsA = pSrcA->numRows;            /* number of rows of input matrix A */
  uint16_t numColsB = pSrcB->numCols;            /* number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* number of columns of input matrix A */
  q63_t sumReal1, sumImag1;                      /* accumulator */
  q31_t a0, b0, c0, d0;
  q31_t a1, b1, c1, d1;


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
        sumReal1 = 0.0;
        sumImag1 = 0.0;

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

          /* Multiply and Accumlates */
          sumReal1 += (q63_t) a0 *c0;
          sumImag1 += (q63_t) b0 *c0;

          /* update pointers */
          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal1 -= (q63_t) b0 *d0;
          sumImag1 += (q63_t) a0 *d0;

          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */

          /* read real and imag values from pSrcA and pSrcB buffer */
          a1 = *pIn1;
          c1 = *pIn2;
          b1 = *(pIn1 + 1u);
          d1 = *(pIn2 + 1u);

          /* Multiply and Accumlates */
          sumReal1 += (q63_t) a1 *c1;
          sumImag1 += (q63_t) b1 *c1;

          /* update pointers */
          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal1 -= (q63_t) b1 *d1;
          sumImag1 += (q63_t) a1 *d1;

          a0 = *pIn1;
          c0 = *pIn2;

          b0 = *(pIn1 + 1u);
          d0 = *(pIn2 + 1u);

          /* Multiply and Accumlates */
          sumReal1 += (q63_t) a0 *c0;
          sumImag1 += (q63_t) b0 *c0;

          /* update pointers */
          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal1 -= (q63_t) b0 *d0;
          sumImag1 += (q63_t) a0 *d0;

          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */

          a1 = *pIn1;
          c1 = *pIn2;

          b1 = *(pIn1 + 1u);
          d1 = *(pIn2 + 1u);

          /* Multiply and Accumlates */
          sumReal1 += (q63_t) a1 *c1;
          sumImag1 += (q63_t) b1 *c1;

          /* update pointers */
          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal1 -= (q63_t) b1 *d1;
          sumImag1 += (q63_t) a1 *d1;

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

          /* Multiply and Accumlates */
          sumReal1 += (q63_t) a1 *c1;
          sumImag1 += (q63_t) b1 *c1;

          /* update pointers */
          pIn1 += 2u;
          pIn2 += 2 * numColsB;

          /* Multiply and Accumlates */
          sumReal1 -= (q63_t) b1 *d1;
          sumImag1 += (q63_t) a1 *d1;

          /* Decrement the loop counter */
          colCnt--;
        }

        /* Store the result in the destination buffer */
        *px++ = (q31_t) clip_q63_to_q31(sumReal1 >> 31);
        *px++ = (q31_t) clip_q63_to_q31(sumImag1 >> 31);
        
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
