/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_cholesky_f32.c
 * Description:  Floating-point Cholesky decomposition
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
  @defgroup MatrixChol Cholesky and LDLT decompositions

  Computes the Cholesky or LDL^t decomposition of a matrix.


  If the input matrix does not have a decomposition, then the
  algorithm terminates and returns error status ARM_MATH_DECOMPOSITION_FAILURE.
 */

/**
  @addtogroup MatrixChol
  @{
 */

/**
   * @brief Floating-point Cholesky decomposition of positive-definite matrix.
   * @param[in]  pSrc   points to the instance of the input floating-point matrix structure.
   * @param[out] pDst   points to the instance of the output floating-point matrix structure.
   * @return The function returns ARM_MATH_SIZE_MISMATCH, if the dimensions do not match.
   * @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
                   - \ref ARM_MATH_DECOMPOSITION_FAILURE      : Input matrix cannot be decomposed
   * @par
   * If the matrix is ill conditioned or only semi-definite, then it is better using the LDL^t decomposition.
   * The decomposition of A is returning a lower triangular matrix U such that A = U U^t
   */

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

arm_status arm_mat_cholesky_f32(
  const arm_matrix_instance_f32 * pSrc,
        arm_matrix_instance_f32 * pDst)
{

  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pSrc->numCols) ||
      (pDst->numRows != pDst->numCols) ||
      (pSrc->numRows != pDst->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    int i,j,k;
    int n = pSrc->numRows;
    float32_t invSqrtVj;
    float32_t *pA,*pG;
    int kCnt;

    mve_pred16_t p0;

    f32x4_t acc, acc0, acc1, acc2, acc3;
    f32x4_t vecGi;
    f32x4_t vecGj,vecGj0,vecGj1,vecGj2,vecGj3;


    pA = pSrc->pData;
    pG = pDst->pData;

    for(i=0 ;i < n ; i++)
    {
       for(j=i ; j+3 < n ; j+=4)
       {
          pG[(j + 0) * n + i] = pA[(j + 0) * n + i];
          pG[(j + 1) * n + i] = pA[(j + 1) * n + i];
          pG[(j + 2) * n + i] = pA[(j + 2) * n + i];
          pG[(j + 3) * n + i] = pA[(j + 3) * n + i];

          kCnt = i;
          acc0 = vdupq_n_f32(0.0f);
          acc1 = vdupq_n_f32(0.0f);
          acc2 = vdupq_n_f32(0.0f);
          acc3 = vdupq_n_f32(0.0f);

          for(k=0; k < i ; k+=4)
          {
             p0 = vctp32q(kCnt);

             vecGi=vldrwq_z_f32(&pG[i * n + k],p0);

             vecGj0=vldrwq_z_f32(&pG[(j + 0) * n + k],p0);
             vecGj1=vldrwq_z_f32(&pG[(j + 1) * n + k],p0);
             vecGj2=vldrwq_z_f32(&pG[(j + 2) * n + k],p0);
             vecGj3=vldrwq_z_f32(&pG[(j + 3) * n + k],p0);

             acc0 = vfmaq_m(acc0, vecGi, vecGj0, p0);
             acc1 = vfmaq_m(acc1, vecGi, vecGj1, p0);
             acc2 = vfmaq_m(acc2, vecGi, vecGj2, p0);
             acc3 = vfmaq_m(acc3, vecGi, vecGj3, p0);

             kCnt -= 4;
          }
          pG[(j + 0) * n + i] -= vecAddAcrossF32Mve(acc0);
          pG[(j + 1) * n + i] -= vecAddAcrossF32Mve(acc1);
          pG[(j + 2) * n + i] -= vecAddAcrossF32Mve(acc2);
          pG[(j + 3) * n + i] -= vecAddAcrossF32Mve(acc3);
       }

       for(; j < n ; j++)
       {
          pG[j * n + i] = pA[j * n + i];

          kCnt = i;
          acc = vdupq_n_f32(0.0f);

          for(k=0; k < i ; k+=4)
          {
             p0 = vctp32q(kCnt);

             vecGi=vldrwq_z_f32(&pG[i * n + k],p0);
             vecGj=vldrwq_z_f32(&pG[j * n + k],p0);

             acc = vfmaq_m(acc, vecGi, vecGj,p0);

             kCnt -= 4;
          }
          pG[j * n + i] -= vecAddAcrossF32Mve(acc);
       }

       if (pG[i * n + i] <= 0.0f)
       {
         return(ARM_MATH_DECOMPOSITION_FAILURE);
       }

       invSqrtVj = 1.0f/sqrtf(pG[i * n + i]);
       for(j=i; j < n ; j++)
       {
         pG[j * n + i] = pG[j * n + i] * invSqrtVj ;
       }
    }

    status = ARM_MATH_SUCCESS;

  }


  /* Return to application */
  return (status);
}

#else
#if defined(ARM_MATH_NEON) && !defined(ARM_MATH_AUTOVECTORIZE)

arm_status arm_mat_cholesky_f32(
  const arm_matrix_instance_f32 * pSrc,
        arm_matrix_instance_f32 * pDst)
{

  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pSrc->numCols) ||
      (pDst->numRows != pDst->numCols) ||
      (pSrc->numRows != pDst->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    int i,j,k;
    int n = pSrc->numRows;
    float32_t invSqrtVj;
    float32_t *pA,*pG;
    int kCnt;


    f32x4_t acc, acc0, acc1, acc2, acc3;
    f32x4_t vecGi;
    f32x4_t vecGj,vecGj0,vecGj1,vecGj2,vecGj3;
    f32x2_t tmp = vdup_n_f32(0);
    float32_t sum=0.0f;
    float32_t sum0=0.0f,sum1=0.0f,sum2=0.0f,sum3=0.0f;


    pA = pSrc->pData;
    pG = pDst->pData;

    for(i=0 ;i < n ; i++)
    {
       for(j=i ; j+3 < n ; j+=4)
       {
          pG[(j + 0) * n + i] = pA[(j + 0) * n + i];
          pG[(j + 1) * n + i] = pA[(j + 1) * n + i];
          pG[(j + 2) * n + i] = pA[(j + 2) * n + i];
          pG[(j + 3) * n + i] = pA[(j + 3) * n + i];

          acc0 = vdupq_n_f32(0.0f);
          acc1 = vdupq_n_f32(0.0f);
          acc2 = vdupq_n_f32(0.0f);
          acc3 = vdupq_n_f32(0.0f);

          kCnt = i >> 2;
          k=0;
          while(kCnt > 0)
          {

             vecGi=vld1q_f32(&pG[i * n + k]);

             vecGj0=vld1q_f32(&pG[(j + 0) * n + k]);
             vecGj1=vld1q_f32(&pG[(j + 1) * n + k]);
             vecGj2=vld1q_f32(&pG[(j + 2) * n + k]);
             vecGj3=vld1q_f32(&pG[(j + 3) * n + k]);

             acc0 = vfmaq_f32(acc0, vecGi, vecGj0);
             acc1 = vfmaq_f32(acc1, vecGi, vecGj1);
             acc2 = vfmaq_f32(acc2, vecGi, vecGj2);
             acc3 = vfmaq_f32(acc3, vecGi, vecGj3);

             kCnt--;
             k+=4;
          }

#if __aarch64__
          sum0 = vpadds_f32(vpadd_f32(vget_low_f32(acc0), vget_high_f32(acc0)));
          sum1 = vpadds_f32(vpadd_f32(vget_low_f32(acc1), vget_high_f32(acc1)));
          sum2 = vpadds_f32(vpadd_f32(vget_low_f32(acc2), vget_high_f32(acc2)));
          sum3 = vpadds_f32(vpadd_f32(vget_low_f32(acc3), vget_high_f32(acc3)));

#else
          tmp = vpadd_f32(vget_low_f32(acc0), vget_high_f32(acc0));
          sum0 = vget_lane_f32(tmp, 0) + vget_lane_f32(tmp, 1);

          tmp = vpadd_f32(vget_low_f32(acc1), vget_high_f32(acc1));
          sum1 = vget_lane_f32(tmp, 0) + vget_lane_f32(tmp, 1);

          tmp = vpadd_f32(vget_low_f32(acc2), vget_high_f32(acc2));
          sum2 = vget_lane_f32(tmp, 0) + vget_lane_f32(tmp, 1);

          tmp = vpadd_f32(vget_low_f32(acc3), vget_high_f32(acc3));
          sum3 = vget_lane_f32(tmp, 0) + vget_lane_f32(tmp, 1);
#endif

          kCnt = i & 3;
          while(kCnt > 0)
          {

             sum0 = sum0 + pG[i * n + k] * pG[(j + 0) * n + k];
             sum1 = sum1 + pG[i * n + k] * pG[(j + 1) * n + k];
             sum2 = sum2 + pG[i * n + k] * pG[(j + 2) * n + k];
             sum3 = sum3 + pG[i * n + k] * pG[(j + 3) * n + k];
             kCnt--;
             k++;
          }

          pG[(j + 0) * n + i] -= sum0;
          pG[(j + 1) * n + i] -= sum1;
          pG[(j + 2) * n + i] -= sum2;
          pG[(j + 3) * n + i] -= sum3;
       }

       for(; j < n ; j++)
       {
          pG[j * n + i] = pA[j * n + i];

          acc = vdupq_n_f32(0.0f);

          kCnt = i >> 2;
          k=0;
          while(kCnt > 0)
          {

             vecGi=vld1q_f32(&pG[i * n + k]);
             vecGj=vld1q_f32(&pG[j * n + k]);

             acc = vfmaq_f32(acc, vecGi, vecGj);

             kCnt--;
             k+=4;
          }

#if __aarch64__
          sum = vpadds_f32(vpadd_f32(vget_low_f32(acc), vget_high_f32(acc)));
#else
          tmp = vpadd_f32(vget_low_f32(acc), vget_high_f32(acc));
          sum = vget_lane_f32(tmp, 0) + vget_lane_f32(tmp, 1);
#endif

          kCnt = i & 3;
          while(kCnt > 0)
          {
             sum = sum + pG[i * n + k] * pG[(j + 0) * n + k];


             kCnt--;
             k++;
          }

          pG[j * n + i] -= sum;
       }

       if (pG[i * n + i] <= 0.0f)
       {
         return(ARM_MATH_DECOMPOSITION_FAILURE);
       }

       invSqrtVj = 1.0f/sqrtf(pG[i * n + i]);
       for(j=i; j < n ; j++)
       {
         pG[j * n + i] = pG[j * n + i] * invSqrtVj ;
       }
    }

    status = ARM_MATH_SUCCESS;

  }


  /* Return to application */
  return (status);
}

#else
arm_status arm_mat_cholesky_f32(
  const arm_matrix_instance_f32 * pSrc,
        arm_matrix_instance_f32 * pDst)
{

  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pSrc->numCols) ||
      (pDst->numRows != pDst->numCols) ||
      (pSrc->numRows != pDst->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    int i,j,k;
    int n = pSrc->numRows;
    float32_t invSqrtVj;
    float32_t *pA,*pG;

    pA = pSrc->pData;
    pG = pDst->pData;


    for(i=0 ; i < n ; i++)
    {
       for(j=i ; j < n ; j++)
       {
          pG[j * n + i] = pA[j * n + i];

          for(k=0; k < i ; k++)
          {
             pG[j * n + i] = pG[j * n + i] - pG[i * n + k] * pG[j * n + k];
          }
       }

       if (pG[i * n + i] <= 0.0f)
       {
         return(ARM_MATH_DECOMPOSITION_FAILURE);
       }

       invSqrtVj = 1.0f/sqrtf(pG[i * n + i]);
       for(j=i ; j < n ; j++)
       {
         pG[j * n + i] = pG[j * n + i] * invSqrtVj ;
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
  @} end of MatrixChol group
 */
