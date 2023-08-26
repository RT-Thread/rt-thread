/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_solve_lower_triangular_f64.c
 * Description:  Solve linear system LT X = A with LT lower triangular matrix
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

#include "dsp/matrix_functions.h"

/**
  @ingroup groupMatrix
 */


/**
  @addtogroup MatrixInv
  @{
 */


   /**
   * @brief Solve LT . X = A where LT is a lower triangular matrix
   * @param[in]  lt  The lower triangular matrix
   * @param[in]  a  The matrix a
   * @param[out] dst The solution X of LT . X = A
   * @return The function returns ARM_MATH_SINGULAR, if the system can't be solved.
   */
  arm_status arm_mat_solve_lower_triangular_f64(
  const arm_matrix_instance_f64 * lt,
  const arm_matrix_instance_f64 * a,
  arm_matrix_instance_f64 * dst)
  {
  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((lt->numRows != lt->numCols) ||
      (lt->numRows != a->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    /* a1 b1 c1   x1 = a1
          b2 c2   x2   a2
             c3   x3   a3

    x3 = a3 / c3 
    x2 = (a2 - c2 x3) / b2

    */
    int i,j,k,n,cols;

    float64_t *pX = dst->pData;
    float64_t *pLT = lt->pData;
    float64_t *pA = a->pData;

    float64_t *lt_row;
    float64_t *a_col;

    n = dst->numRows;
    cols = dst->numCols;

    for(j=0; j < cols; j ++)
    {
       a_col = &pA[j];

       for(i=0; i < n ; i++)
       {
            float64_t tmp=a_col[i * cols];

            lt_row = &pLT[n*i];

            for(k=0; k < i; k++)
            {
                tmp -= lt_row[k] * pX[cols*k+j];
            }

            if (lt_row[i]==0.0)
            {
              return(ARM_MATH_SINGULAR);
            }
            tmp = tmp / lt_row[i];
            pX[i*cols+j] = tmp;
       }

    }
    status = ARM_MATH_SUCCESS;

  }

  /* Return to application */
  return (status);
}
/**
  @} end of MatrixInv group
 */
