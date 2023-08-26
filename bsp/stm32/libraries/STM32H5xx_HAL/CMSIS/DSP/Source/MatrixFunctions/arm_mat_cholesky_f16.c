/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_cholesky_f16.c
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

#include "dsp/matrix_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

/**
  @ingroup groupMatrix
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

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"

arm_status arm_mat_cholesky_f16(
  const arm_matrix_instance_f16 * pSrc,
        arm_matrix_instance_f16 * pDst)
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
    _Float16 invSqrtVj;
    float16_t *pA,*pG;
    int kCnt;

    mve_pred16_t p0;

    f16x8_t acc, acc0, acc1, acc2, acc3;
    f16x8_t vecGi;
    f16x8_t vecGj,vecGj0,vecGj1,vecGj2,vecGj3;


    pA = pSrc->pData;
    pG = pDst->pData;
    
    for(i=0 ;i < n ; i++)
    {
       for(j=i ; j+3 < n ; j+=4)
       {
          acc0 = vdupq_n_f16(0.0f16);
          acc0[0]=pA[(j + 0) * n + i];

          acc1 = vdupq_n_f16(0.0f16);
          acc1[0]=pA[(j + 1) * n + i];

          acc2 = vdupq_n_f16(0.0f16);
          acc2[0]=pA[(j + 2) * n + i];

          acc3 = vdupq_n_f16(0.0f16);
          acc3[0]=pA[(j + 3) * n + i];

          kCnt = i;
          for(k=0; k < i ; k+=8)
          {
             p0 = vctp16q(kCnt);

             vecGi=vldrhq_z_f16(&pG[i * n + k],p0);
             
             vecGj0=vldrhq_z_f16(&pG[(j + 0) * n + k],p0);
             vecGj1=vldrhq_z_f16(&pG[(j + 1) * n + k],p0);
             vecGj2=vldrhq_z_f16(&pG[(j + 2) * n + k],p0);
             vecGj3=vldrhq_z_f16(&pG[(j + 3) * n + k],p0);

             acc0 = vfmsq_m(acc0, vecGi, vecGj0, p0);
             acc1 = vfmsq_m(acc1, vecGi, vecGj1, p0);
             acc2 = vfmsq_m(acc2, vecGi, vecGj2, p0);
             acc3 = vfmsq_m(acc3, vecGi, vecGj3, p0);

             kCnt -= 8;
          }
          pG[(j + 0) * n + i] = vecAddAcrossF16Mve(acc0);
          pG[(j + 1) * n + i] = vecAddAcrossF16Mve(acc1);
          pG[(j + 2) * n + i] = vecAddAcrossF16Mve(acc2);
          pG[(j + 3) * n + i] = vecAddAcrossF16Mve(acc3);
       }

       for(; j < n ; j++)
       {

          kCnt = i;
          acc = vdupq_n_f16(0.0f16);
          acc[0] = pA[j * n + i];

          for(k=0; k < i ; k+=8)
          {
             p0 = vctp16q(kCnt);

             vecGi=vldrhq_z_f16(&pG[i * n + k],p0);
             vecGj=vldrhq_z_f16(&pG[j * n + k],p0);

             acc = vfmsq_m(acc, vecGi, vecGj,p0);

             kCnt -= 8;
          }
          pG[j * n + i] = vecAddAcrossF16Mve(acc);
       }

       if ((_Float16)pG[i * n + i] <= 0.0f16)
       {
         return(ARM_MATH_DECOMPOSITION_FAILURE);
       }

       invSqrtVj = 1.0f16/(_Float16)sqrtf((float32_t)pG[i * n + i]);
       for(j=i; j < n ; j++)
       {
         pG[j * n + i] = (_Float16)pG[j * n + i] * (_Float16)invSqrtVj ;
       }
    }

    status = ARM_MATH_SUCCESS;

  }

  
  /* Return to application */
  return (status);
}

#else
arm_status arm_mat_cholesky_f16(
  const arm_matrix_instance_f16 * pSrc,
        arm_matrix_instance_f16 * pDst)
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
    float16_t invSqrtVj;
    float16_t *pA,*pG;

    pA = pSrc->pData;
    pG = pDst->pData;
    

    for(i=0 ; i < n ; i++)
    {
       for(j=i ; j < n ; j++)
       {
          pG[j * n + i] = pA[j * n + i];

          for(k=0; k < i ; k++)
          {
             pG[j * n + i] = (_Float16)pG[j * n + i] - (_Float16)pG[i * n + k] * (_Float16)pG[j * n + k];
          }
       }

       if ((_Float16)pG[i * n + i] <= 0.0f16)
       {
         return(ARM_MATH_DECOMPOSITION_FAILURE);
       }

       /* The division is done in float32 for accuracy reason and
       because doing it in f16 would not have any impact on the performances.
       */
       invSqrtVj = 1.0f/sqrtf((float32_t)pG[i * n + i]);
       for(j=i ; j < n ; j++)
       {
         pG[j * n + i] = (_Float16)pG[j * n + i] * (_Float16)invSqrtVj ;
       }
    }

    status = ARM_MATH_SUCCESS;

  }

  
  /* Return to application */
  return (status);
}

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of MatrixChol group
 */
#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 
