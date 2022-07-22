/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_ldl_f32.c
 * Description:  Floating-point LDL decomposition
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





#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)


/// @private
#define SWAP_ROWS_F32(A,i,j)                 \
  {                                      \
    int cnt = n;                         \
                                         \
    for(int w=0;w < n; w+=4)             \
    {                                    \
       f32x4_t tmpa,tmpb;                \
       mve_pred16_t p0 = vctp32q(cnt);   \
                                         \
       tmpa=vldrwq_z_f32(&A[i*n + w],p0);\
       tmpb=vldrwq_z_f32(&A[j*n + w],p0);\
                                         \
       vstrwq_p(&A[i*n + w], tmpb, p0);  \
       vstrwq_p(&A[j*n + w], tmpa, p0);  \
                                         \
       cnt -= 4;                         \
    }                                    \
  }

/// @private
#define SWAP_COLS_F32(A,i,j)     \
  for(int w=0;w < n; w++)    \
  {                          \
     float32_t tmp;          \
     tmp = A[w*n + i];       \
     A[w*n + i] = A[w*n + j];\
     A[w*n + j] = tmp;       \
  }

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixChol
  @{
 */

/**
   * @brief Floating-point LDL^t decomposition of positive semi-definite matrix.
   * @param[in]  pSrc   points to the instance of the input floating-point matrix structure.
   * @param[out] pl   points to the instance of the output floating-point triangular matrix structure.
   * @param[out] pd   points to the instance of the output floating-point diagonal matrix structure.
   * @param[out] pp   points to the instance of the output floating-point permutation vector.
   * @return The function returns ARM_MATH_SIZE_MISMATCH, if the dimensions do not match.
   * @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
                   - \ref ARM_MATH_DECOMPOSITION_FAILURE      : Input matrix cannot be decomposed
   * @par
   *  Computes the LDL^t decomposition of a matrix A such that P A P^t = L D L^t.
   */
arm_status arm_mat_ldlt_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pl,
  arm_matrix_instance_f32 * pd,
  uint16_t * pp)
{

  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pSrc->numCols) ||
      (pl->numRows != pl->numCols) ||
      (pd->numRows != pd->numCols) ||
      (pl->numRows != pd->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {

    const int n=pSrc->numRows;
    int fullRank = 1, diag,k;
    float32_t *pA;

    memcpy(pl->pData,pSrc->pData,n*n*sizeof(float32_t));
    pA = pl->pData;

    int cnt = n;
    uint16x8_t vecP;

    for(int k=0;k < n; k+=8)
    {
      mve_pred16_t p0;
      p0 = vctp16q(cnt);

      vecP = vidupq_u16((uint16_t)k, 1);

      vstrhq_p(&pp[k], vecP, p0);

      cnt -= 8;
    }


    for(k=0;k < n; k++)
    {
        /* Find pivot */
        float32_t m=F32_MIN,a;
        int j=k;


        for(int r=k;r<n;r++)
        {
           if (pA[r*n+r] > m)
           {
             m = pA[r*n+r];
             j = r;
           }
        }

        if(j != k)
        {
          SWAP_ROWS_F32(pA,k,j);
          SWAP_COLS_F32(pA,k,j);
        }


        pp[k] = j;

        a = pA[k*n+k];

        if (fabs(a) < 1.0e-8)
        {

            fullRank = 0;
            break;
        }

        float32_t invA;

        invA = 1.0f / a;

        int32x4_t vecOffs;
        int w;
        vecOffs = vidupq_u32((uint32_t)0, 1);
        vecOffs = vmulq_n_s32(vecOffs,n);

        for(w=k+1; w<n; w+=4)
        {
          int cnt = n - k - 1;

          f32x4_t vecX;

          f32x4_t vecA;
          f32x4_t vecW0,vecW1, vecW2, vecW3;

          mve_pred16_t p0;

          vecW0 = vdupq_n_f32(pA[(w + 0)*n+k]);
          vecW1 = vdupq_n_f32(pA[(w + 1)*n+k]);
          vecW2 = vdupq_n_f32(pA[(w + 2)*n+k]);
          vecW3 = vdupq_n_f32(pA[(w + 3)*n+k]);

          for(int x=k+1;x<n;x += 4)
          {
             p0 = vctp32q(cnt);

             //pA[w*n+x] = pA[w*n+x] - pA[w*n+k] * (pA[x*n+k] * invA);


             vecX = vldrwq_gather_shifted_offset_z_f32(&pA[x*n+k], vecOffs, p0);
             vecX = vmulq_m_n_f32(vuninitializedq_f32(),vecX,invA,p0);


             vecA = vldrwq_z_f32(&pA[(w + 0)*n+x],p0);
             vecA = vfmsq_m(vecA, vecW0, vecX, p0);
             vstrwq_p(&pA[(w + 0)*n+x], vecA, p0);

             vecA = vldrwq_z_f32(&pA[(w + 1)*n+x],p0);
             vecA = vfmsq_m(vecA, vecW1, vecX, p0);
             vstrwq_p(&pA[(w + 1)*n+x], vecA, p0);

             vecA = vldrwq_z_f32(&pA[(w + 2)*n+x],p0);
             vecA = vfmsq_m(vecA, vecW2, vecX, p0);
             vstrwq_p(&pA[(w + 2)*n+x], vecA, p0);

             vecA = vldrwq_z_f32(&pA[(w + 3)*n+x],p0);
             vecA = vfmsq_m(vecA, vecW3, vecX, p0);
             vstrwq_p(&pA[(w + 3)*n+x], vecA, p0);

             cnt -= 4;
          }
        }

        for(; w<n; w++)
        {
          int cnt = n - k - 1;

          f32x4_t vecA,vecX,vecW;


          mve_pred16_t p0;

          vecW = vdupq_n_f32(pA[w*n+k]);

          for(int x=k+1;x<n;x += 4)
          {
             p0 = vctp32q(cnt);

             //pA[w*n+x] = pA[w*n+x] - pA[w*n+k] * (pA[x*n+k] * invA);

             vecA = vldrwq_z_f32(&pA[w*n+x],p0);

             vecX = vldrwq_gather_shifted_offset_z_f32(&pA[x*n+k], vecOffs, p0);
             vecX = vmulq_m_n_f32(vuninitializedq_f32(),vecX,invA,p0);

             vecA = vfmsq_m(vecA, vecW, vecX, p0);

             vstrwq_p(&pA[w*n+x], vecA, p0);

             cnt -= 4;
          }
        }

        for(int w=k+1;w<n;w++)
        {
               pA[w*n+k] = pA[w*n+k] * invA;
        }



    }



    diag=k;
    if (!fullRank)
    {
      diag--;
      for(int row=0; row < n;row++)
      {
        mve_pred16_t p0;
        int cnt= n-k;
        f32x4_t zero=vdupq_n_f32(0.0f);

        for(int col=k; col < n;col += 4)
        {
           p0 = vctp32q(cnt);

           vstrwq_p(&pl->pData[row*n+col], zero, p0);

           cnt -= 4;
        }
      }
    }

    for(int row=0; row < n;row++)
    {
       mve_pred16_t p0;
       int cnt= n-row-1;
       f32x4_t zero=vdupq_n_f32(0.0f);

       for(int col=row+1; col < n;col+=4)
       {
         p0 = vctp32q(cnt);

         vstrwq_p(&pl->pData[row*n+col], zero, p0);

         cnt -= 4;
       }
    }

    for(int d=0; d < diag;d++)
    {
      pd->pData[d*n+d] = pl->pData[d*n+d];
      pl->pData[d*n+d] = 1.0;
    }

    status = ARM_MATH_SUCCESS;

  }


  /* Return to application */
  return (status);
}
#else

/// @private
#define SWAP_ROWS_F32(A,i,j)     \
  for(int w=0;w < n; w++)    \
  {                          \
     float32_t tmp;          \
     tmp = A[i*n + w];       \
     A[i*n + w] = A[j*n + w];\
     A[j*n + w] = tmp;       \
  }

/// @private
#define SWAP_COLS_F32(A,i,j)     \
  for(int w=0;w < n; w++)    \
  {                          \
     float32_t tmp;          \
     tmp = A[w*n + i];       \
     A[w*n + i] = A[w*n + j];\
     A[w*n + j] = tmp;       \
  }

/**
  @ingroup groupMatrix
 */

/**
  @addtogroup MatrixChol
  @{
 */

/**
   * @brief Floating-point LDL^t decomposition of positive semi-definite matrix.
   * @param[in]  pSrc   points to the instance of the input floating-point matrix structure.
   * @param[out] pl   points to the instance of the output floating-point triangular matrix structure.
   * @param[out] pd   points to the instance of the output floating-point diagonal matrix structure.
   * @param[out] pp   points to the instance of the output floating-point permutation vector.
   * @return The function returns ARM_MATH_SIZE_MISMATCH, if the dimensions do not match.
   * @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
                   - \ref ARM_MATH_DECOMPOSITION_FAILURE      : Input matrix cannot be decomposed
   * @par
   *  Computes the LDL^t decomposition of a matrix A such that P A P^t = L D L^t.
   */
arm_status arm_mat_ldlt_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pl,
  arm_matrix_instance_f32 * pd,
  uint16_t * pp)
{

  arm_status status;                             /* status of matrix inverse */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pSrc->numCols) ||
      (pl->numRows != pl->numCols) ||
      (pd->numRows != pd->numCols) ||
      (pl->numRows != pd->numRows)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {

    const int n=pSrc->numRows;
    int fullRank = 1, diag,k;
    float32_t *pA;

    memcpy(pl->pData,pSrc->pData,n*n*sizeof(float32_t));
    pA = pl->pData;

    for(int k=0;k < n; k++)
    {
      pp[k] = k;
    }


    for(k=0;k < n; k++)
    {
        /* Find pivot */
        float32_t m=F32_MIN,a;
        int j=k;


        for(int r=k;r<n;r++)
        {
           if (pA[r*n+r] > m)
           {
             m = pA[r*n+r];
             j = r;
           }
        }

        if(j != k)
        {
          SWAP_ROWS_F32(pA,k,j);
          SWAP_COLS_F32(pA,k,j);
        }


        pp[k] = j;

        a = pA[k*n+k];

        if (fabs(a) < 1.0e-8)
        {

            fullRank = 0;
            break;
        }

        for(int w=k+1;w<n;w++)
        {
          for(int x=k+1;x<n;x++)
          {
             pA[w*n+x] = pA[w*n+x] - pA[w*n+k] * pA[x*n+k] / a;
          }
        }

        for(int w=k+1;w<n;w++)
        {
               pA[w*n+k] = pA[w*n+k] / a;
        }



    }



    diag=k;
    if (!fullRank)
    {
      diag--;
      for(int row=0; row < n;row++)
      {
        for(int col=k; col < n;col++)
        {
           pl->pData[row*n+col]=0.0;
        }
      }
    }

    for(int row=0; row < n;row++)
    {
       for(int col=row+1; col < n;col++)
       {
         pl->pData[row*n+col] = 0.0;
       }
    }

    for(int d=0; d < diag;d++)
    {
      pd->pData[d*n+d] = pl->pData[d*n+d];
      pl->pData[d*n+d] = 1.0;
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
