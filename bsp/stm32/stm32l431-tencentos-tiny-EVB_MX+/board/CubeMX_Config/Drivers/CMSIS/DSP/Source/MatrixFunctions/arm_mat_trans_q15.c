/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_trans_q15.c
 * Description:  Q15 matrix transpose
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
  @addtogroup MatrixTrans
  @{
 */

/**
  @brief         Q15 matrix transpose.
  @param[in]     pSrc      points to input matrix
  @param[out]    pDst      points to output matrix
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
 */

arm_status arm_mat_trans_q15(
  const arm_matrix_instance_q15 * pSrc,
        arm_matrix_instance_q15 * pDst)
{
        q15_t *pIn = pSrc->pData;                      /* input data matrix pointer */
        q15_t *pOut = pDst->pData;                     /* output data matrix pointer */
        uint16_t nRows = pSrc->numRows;                /* number of rows */
        uint16_t nCols = pSrc->numCols;                /* number of columns */
        uint32_t col, row = nRows, i = 0U;             /* Loop counters */
        arm_status status;                             /* status of matrix transpose */

#if defined (ARM_MATH_LOOPUNROLL)
        q31_t in;                                      /* variable to hold temporary output  */
#endif

#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numCols) ||
      (pSrc->numCols != pDst->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    /* Matrix transpose by exchanging the rows with columns */
    /* row loop */
    do
    {
      /* Pointer pOut is set to starting address of column being processed */
      pOut = pDst->pData + i;

#if defined (ARM_MATH_LOOPUNROLL)

      /* Loop unrolling: Compute 4 outputs at a time */
      col = nCols >> 2U;

      while (col > 0U)        /* column loop */
      {
        /* Read two elements from row */
        in = read_q15x2_ia ((q15_t **) &pIn);

        /* Unpack and store one element in  destination */
#ifndef ARM_MATH_BIG_ENDIAN
        *pOut = (q15_t) in;
#else
        *pOut = (q15_t) ((in & (q31_t) 0xffff0000) >> 16);
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */

        /* Update pointer pOut to point to next row of transposed matrix */
        pOut += nRows;

        /* Unpack and store second element in destination */
#ifndef ARM_MATH_BIG_ENDIAN
        *pOut = (q15_t) ((in & (q31_t) 0xffff0000) >> 16);
#else
        *pOut = (q15_t) in;
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */

        /* Update  pointer pOut to point to next row of transposed matrix */
        pOut += nRows;

        /* Read two elements from row */
        in = read_q15x2_ia ((q15_t **) &pIn);

        /* Unpack and store one element in destination */
#ifndef ARM_MATH_BIG_ENDIAN
        *pOut = (q15_t) in;
#else
        *pOut = (q15_t) ((in & (q31_t) 0xffff0000) >> 16);

#endif /* #ifndef ARM_MATH_BIG_ENDIAN */

        /* Update pointer pOut to point to next row of transposed matrix */
        pOut += nRows;

        /* Unpack and store second element in destination */
#ifndef ARM_MATH_BIG_ENDIAN
        *pOut = (q15_t) ((in & (q31_t) 0xffff0000) >> 16);
#else
        *pOut = (q15_t) in;
#endif /* #ifndef ARM_MATH_BIG_ENDIAN */

        /* Update pointer pOut to point to next row of transposed matrix */
        pOut += nRows;

        /* Decrement column loop counter */
        col--;
      }

      /* Loop unrolling: Compute remaining outputs */
      col = nCols % 0x4U;

#else

      /* Initialize col with number of samples */
      col = nCols;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

      while (col > 0U)
      {
        /* Read and store input element in destination */
        *pOut = *pIn++;

        /* Update pointer pOut to point to next row of transposed matrix */
        pOut += nRows;

        /* Decrement column loop counter */
        col--;
      }

      i++;

      /* Decrement row loop counter */
      row--;

    } while (row > 0U);          /* row loop end */

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}

/**
  @} end of MatrixTrans group
 */
