/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_scale_f16.c
 * Description:  Multiplies a floating-point matrix by a scalar
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
  @addtogroup MatrixScale
  @{
 */

/**
  @brief         Floating-point matrix scaling.
  @param[in]     pSrc       points to input matrix
  @param[in]     scale      scale factor to be applied
  @param[out]    pDst       points to output matrix structure
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
 */
#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

arm_status arm_mat_scale_f16(
  const arm_matrix_instance_f16 * pSrc,
  float16_t scale,
  arm_matrix_instance_f16 * pDst)
{
  arm_status status;                             /* status of matrix scaling     */
  #ifdef ARM_MATH_MATRIX_CHECK
  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numRows) || (pSrc->numCols != pDst->numCols))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*    #ifdef ARM_MATH_MATRIX_CHECK    */
  {
    float16_t *pIn = pSrc->pData;   /* input data matrix pointer */
    float16_t *pOut = pDst->pData;  /* output data matrix pointer */
    uint32_t  numSamples;           /* total number of elements in the matrix */
    uint32_t  blkCnt;               /* loop counters */
    f16x8_t vecIn, vecOut, vecScale;
    float16_t const *pInVec;

    pInVec = (float16_t const *) pIn;

    vecScale = vdupq_n_f16(scale);
    /*
     * Total number of samples in the input matrix
     */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;
    blkCnt = numSamples >> 3;
    while (blkCnt > 0U)
    {
        /*
         * C(m,n) = A(m,n) * scale
         * Scaling and results are stored in the destination buffer.
         */
        vecIn = vld1q(pInVec); 
        pInVec += 8;

        vecOut = vmulq_f16(vecIn, vecScale);

        vst1q(pOut, vecOut); 
        pOut += 8;
        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
    /*
     * tail
     */
    blkCnt = numSamples & 7;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp16q(blkCnt);
        vecIn = vld1q(pInVec); 
        vecOut = vecIn * scale;

        vstrhq_p(pOut, vecOut, p0);
    }
    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);

}
#else

arm_status arm_mat_scale_f16(
  const arm_matrix_instance_f16 * pSrc,
        float16_t                 scale,
        arm_matrix_instance_f16 * pDst)
{
  float16_t *pIn = pSrc->pData;                  /* Input data matrix pointer */
  float16_t *pOut = pDst->pData;                 /* Output data matrix pointer */
  uint32_t numSamples;                           /* Total number of elements in the matrix */
  uint32_t blkCnt;                               /* Loop counters */
  arm_status status;                             /* Status of matrix scaling */

#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if ((pSrc->numRows != pDst->numRows) ||
      (pSrc->numCols != pDst->numCols)   )
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else

#endif /* #ifdef ARM_MATH_MATRIX_CHECK */

  {
    /* Total number of samples in input matrix */
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = numSamples >> 2U;

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * scale */

      /* Scale and store result in destination buffer. */
      *pOut++ = (_Float16)(*pIn++) * (_Float16)scale;
      *pOut++ = (_Float16)(*pIn++) * (_Float16)scale;
      *pOut++ = (_Float16)(*pIn++) * (_Float16)scale;
      *pOut++ = (_Float16)(*pIn++) * (_Float16)scale;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    blkCnt = numSamples % 0x4U;

#else

    /* Initialize blkCnt with number of samples */
    blkCnt = numSamples;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while (blkCnt > 0U)
    {
      /* C(m,n) = A(m,n) * scale */

      /* Scale and store result in destination buffer. */
      *pOut++ = (_Float16)(*pIn++) * (_Float16)scale;

      /* Decrement loop counter */
      blkCnt--;
    }

    /* Set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }

  /* Return to application */
  return (status);
}
#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
  @} end of MatrixScale group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

