/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_mat_trans_q7.c
 * Description:  Q7 matrix transpose
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
  @addtogroup MatrixTrans
  @{
 */

/**
  @brief         Q7 matrix transpose.
  @param[in]     pSrc      points to input matrix
  @param[out]    pDst      points to output matrix
  @return        execution status
                   - \ref ARM_MATH_SUCCESS       : Operation successful
                   - \ref ARM_MATH_SIZE_MISMATCH : Matrix size check failed
 */
#if defined(ARM_MATH_MVEI) && !defined(ARM_MATH_AUTOVECTORIZE)
arm_status arm_mat_trans_q7(const arm_matrix_instance_q7 *pSrc, arm_matrix_instance_q7 *pDst)
{

    uint16x8_t    vecOffs;
    uint32_t        i;
    uint32_t        blkCnt;
    uint8_t const  *pDataC;
    uint8_t        *pDataDestR;
    uint16x8_t    vecIn;

    const uint8_t   * pDataSrc=(const uint8_t  *)pSrc->pData;
    uint8_t   * pDataDst=(uint8_t  *)pDst->pData;

#ifdef ARM_MATH_MATRIX_CHECK
    /* Check for matrix mismatch condition */
    if ((pSrc->numRows != pDst->numCols) || (pSrc->numCols != pDst->numRows))
    {
        /* Set status as ARM_MATH_SIZE_MISMATCH */
        return ARM_MATH_SIZE_MISMATCH;
    }
#endif

    vecOffs = vidupq_u16((uint32_t)0, 1);
    vecOffs = vecOffs * pSrc->numCols;

    i = pSrc->numCols;
    do
    {
        pDataC = (uint8_t const *) pDataSrc;
        pDataDestR = (uint8_t*)pDataDst;

        blkCnt = pSrc->numRows >> 3;
        while (blkCnt > 0U)
        {
            /* widened loads */
            vecIn = vldrbq_gather_offset_u16(pDataC, vecOffs);
            vstrbq_u16(pDataDestR, vecIn);
            pDataDestR += 8;
            pDataC = pDataC + pSrc->numCols * 8;
            /*
             * Decrement the blockSize loop counter
             */
            blkCnt--;
        }

        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = pSrc->numRows & 7;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(blkCnt);
            vecIn = vldrbq_gather_offset_u16(pDataC, vecOffs);
            vstrbq_p_u16(pDataDestR, vecIn, p0);
        }
        pDataSrc += 1;
        pDataDst += pSrc->numRows;
    }
    while (--i);

    return (ARM_MATH_SUCCESS);
}
#else
arm_status arm_mat_trans_q7(const arm_matrix_instance_q7 *pSrc, arm_matrix_instance_q7 *pDst)
{
    q7_t *pSrcA = pSrc->pData;         /* input data matrix pointer */
    q7_t *pOut = pDst->pData;          /* output data matrix pointer */
    uint16_t nRows = pSrc->numRows;    /* number of nRows */
    uint16_t nColumns = pSrc->numCols; /* number of nColumns */
    uint16_t col, row = nRows, i = 0U; /* row and column loop counters */
    arm_status status;                 /* status of matrix transpose */


#ifdef ARM_MATH_MATRIX_CHECK
    /* Check for matrix mismatch condition */
    if ((pSrc->numRows != pDst->numCols) || (pSrc->numCols != pDst->numRows)) {
        /* Set status as ARM_MATH_SIZE_MISMATCH */
        status = ARM_MATH_SIZE_MISMATCH;
    } else
#endif /*    #ifdef ARM_MATH_MATRIX_CHECK    */

    {
        /* Matrix transpose by exchanging the rows with columns */
        /* row loop     */
        do {
            /* The pointer pOut is set to starting address of the column being processed */
            pOut = pDst->pData + i;

            /* Initialize column loop counter */
            col = nColumns;


            while (col > 0U) {
                /* Read and store the input element in the destination */
                *pOut = *pSrcA++;

                /* Update the pointer pOut to point to the next row of the transposed matrix */
                pOut += nRows;

                /* Decrement the column loop counter */
                col--;
            }

            i++;

            /* Decrement the row loop counter */
            row--;

        } while (row > 0U);

        /* set status as ARM_MATH_SUCCESS */
        status = ARM_MATH_SUCCESS;
    }
    /* Return to application */
    return (status);
}
#endif /* defined(ARM_MATH_MVEI) */


/**
  @} end of MatrixTrans group
 */
