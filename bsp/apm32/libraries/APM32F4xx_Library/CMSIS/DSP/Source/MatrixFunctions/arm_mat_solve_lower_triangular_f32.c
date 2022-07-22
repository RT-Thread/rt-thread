/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_solve_lower_triangular_f32.c
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

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

  arm_status arm_mat_solve_lower_triangular_f32(
  const arm_matrix_instance_f32 * lt,
  const arm_matrix_instance_f32 * a,
  arm_matrix_instance_f32 * dst)
  {
  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((lt->numRows != lt->numCols) ||
      (a->numRows != a->numCols) ||
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
    int i,j,k,n;

    n = dst->numRows;

    float32_t *pX = dst->pData;
    float32_t *pLT = lt->pData;
    float32_t *pA = a->pData;

    float32_t *lt_row;
    float32_t *a_col;

    float32_t invLT;

    f32x4_t vecA;
    f32x4_t vecX;

    for(i=0; i < n ; i++)
    {

      for(j=0; j+3 < n; j += 4)
      {
            vecA = vld1q_f32(&pA[i * n + j]);

            for(k=0; k < i; k++)
            {
                vecX = vld1q_f32(&pX[n*k+j]);
                vecA = vfmsq(vecA,vdupq_n_f32(pLT[n*i + k]),vecX);
            }

            if (pLT[n*i + i]==0.0f)
            {
              return(ARM_MATH_SINGULAR);
            }

            invLT = 1.0f / pLT[n*i + i];
            vecA = vmulq(vecA,vdupq_n_f32(invLT));
            vst1q(&pX[i*n+j],vecA);

       }

       for(; j < n; j ++)
       {
            a_col = &pA[j];
            lt_row = &pLT[n*i];

            float32_t tmp=a_col[i * n];

            for(k=0; k < i; k++)
            {
                tmp -= lt_row[k] * pX[n*k+j];
            }

            if (lt_row[i]==0.0f)
            {
              return(ARM_MATH_SINGULAR);
            }
            tmp = tmp / lt_row[i];
            pX[i*n+j] = tmp;
        }

    }
    status = ARM_MATH_SUCCESS;

  }

  /* Return to application */
  return (status);
}
#else
#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)
  arm_status arm_mat_solve_lower_triangular_f32(
  const arm_matrix_instance_f32 * lt,
  const arm_matrix_instance_f32 * a,
  arm_matrix_instance_f32 * dst)
  {
  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((lt->numRows != lt->numCols) ||
      (a->numRows != a->numCols) ||
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
    int i,j,k,n;

    n = dst->numRows;

    float32_t *pX = dst->pData;
    float32_t *pLT = lt->pData;
    float32_t *pA = a->pData;

    float32_t *lt_row;
    float32_t *a_col;

    float32_t invLT;

    f32x4_t vecA;
    f32x4_t vecX;

    for(i=0; i < n ; i++)
    {

      for(j=0; j+3 < n; j += 4)
      {
            vecA = vld1q_f32(&pA[i * n + j]);

            for(k=0; k < i; k++)
            {
                vecX = vld1q_f32(&pX[n*k+j]);
                vecA = vfmsq_f32(vecA,vdupq_n_f32(pLT[n*i + k]),vecX);
            }

            if (pLT[n*i + i]==0.0f)
            {
              return(ARM_MATH_SINGULAR);
            }

            invLT = 1.0f / pLT[n*i + i];
            vecA = vmulq_f32(vecA,vdupq_n_f32(invLT));
            vst1q_f32(&pX[i*n+j],vecA);

       }

       for(; j < n; j ++)
       {
            a_col = &pA[j];
            lt_row = &pLT[n*i];

            float32_t tmp=a_col[i * n];

            for(k=0; k < i; k++)
            {
                tmp -= lt_row[k] * pX[n*k+j];
            }

            if (lt_row[i]==0.0f)
            {
              return(ARM_MATH_SINGULAR);
            }
            tmp = tmp / lt_row[i];
            pX[i*n+j] = tmp;
        }

    }
    status = ARM_MATH_SUCCESS;

  }

  /* Return to application */
  return (status);
}
#else
  arm_status arm_mat_solve_lower_triangular_f32(
  const arm_matrix_instance_f32 * lt,
  const arm_matrix_instance_f32 * a,
  arm_matrix_instance_f32 * dst)
  {
  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK
  /* Check for matrix mismatch condition */
  if ((lt->numRows != lt->numCols) ||
      (a->numRows != a->numCols) ||
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
    int i,j,k,n;

    n = dst->numRows;

    float32_t *pX = dst->pData;
    float32_t *pLT = lt->pData;
    float32_t *pA = a->pData;

    float32_t *lt_row;
    float32_t *a_col;

    for(j=0; j < n; j ++)
    {
       a_col = &pA[j];

       for(i=0; i < n ; i++)
       {
            lt_row = &pLT[n*i];

            float32_t tmp=a_col[i * n];

            for(k=0; k < i; k++)
            {
                tmp -= lt_row[k] * pX[n*k+j];
            }

            if (lt_row[i]==0.0f)
            {
              return(ARM_MATH_SINGULAR);
            }
            tmp = tmp / lt_row[i];
            pX[i*n+j] = tmp;
       }

    }
    status = ARM_MATH_SUCCESS;

  }

  /* Return to application */
  return (status);
}
#endif /* #if defined(ARM_MATH_NEON) */
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of MatrixInv group
 */
