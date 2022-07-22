/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_svm_sigmoid_predict_f16.c
 * Description:  SVM Sigmoid Classifier
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

#include "dsp/svm_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

#include <limits.h>
#include <math.h>

/**
 * @addtogroup sigmoidsvm
 * @{
 */



/**
 * @brief SVM sigmoid prediction
 * @param[in]    S        Pointer to an instance of the rbf SVM structure.
 * @param[in]    in       Pointer to input vector
 * @param[out]   pResult  Decision value
 * @return none.
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

void arm_svm_sigmoid_predict_f16(
    const arm_svm_sigmoid_instance_f16 *S,
    const float16_t * in,
    int32_t * pResult)
{
        /* inlined Matrix x Vector function interleaved with dot prod */
    uint32_t        numRows = S->nbOfSupportVectors;
    uint32_t        numCols = S->vectorDimension;
    const float16_t *pSupport = S->supportVectors;
    const float16_t *pSrcA = pSupport;
    const float16_t *pInA0;
    const float16_t *pInA1;
    uint32_t         row;
    uint32_t         blkCnt;     /* loop counters */
    const float16_t *pDualCoef = S->dualCoefficients;
    _Float16       sum = S->intercept;
    f16x8_t         vSum = vdupq_n_f16(0.0f);

    row = numRows;

    /*
     * compute 4 rows in parrallel
     */
    while (row >= 4) {
        const float16_t *pInA2, *pInA3;
        float16_t const *pSrcA0Vec, *pSrcA1Vec, *pSrcA2Vec, *pSrcA3Vec, *pInVec;
        f16x8_t         vecIn, acc0, acc1, acc2, acc3;
        float16_t const *pSrcVecPtr = in;

        /*
         * Initialize the pointers to 4 consecutive MatrixA rows
         */
        pInA0 = pSrcA;
        pInA1 = pInA0 + numCols;
        pInA2 = pInA1 + numCols;
        pInA3 = pInA2 + numCols;
        /*
         * Initialize the vector pointer
         */
        pInVec = pSrcVecPtr;
        /*
         * reset accumulators
         */
        acc0 = vdupq_n_f16(0.0f);
        acc1 = vdupq_n_f16(0.0f);
        acc2 = vdupq_n_f16(0.0f);
        acc3 = vdupq_n_f16(0.0f);

        pSrcA0Vec = pInA0;
        pSrcA1Vec = pInA1;
        pSrcA2Vec = pInA2;
        pSrcA3Vec = pInA3;

        blkCnt = numCols >> 3;
        while (blkCnt > 0U) {
            f16x8_t         vecA;

            vecIn = vld1q(pInVec);
            pInVec += 8;
            vecA = vld1q(pSrcA0Vec);
            pSrcA0Vec += 8;
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vld1q(pSrcA1Vec);
            pSrcA1Vec += 8;
            acc1 = vfmaq(acc1, vecIn, vecA);
            vecA = vld1q(pSrcA2Vec);
            pSrcA2Vec += 8;
            acc2 = vfmaq(acc2, vecIn, vecA);
            vecA = vld1q(pSrcA3Vec);
            pSrcA3Vec += 8;
            acc3 = vfmaq(acc3, vecIn, vecA);

            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = numCols & 7;
        if (blkCnt > 0U) {
            mve_pred16_t    p0 = vctp16q(blkCnt);
            f16x8_t         vecA;

            vecIn = vldrhq_z_f16(pInVec, p0);
            vecA = vldrhq_z_f16(pSrcA0Vec, p0);
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vldrhq_z_f16(pSrcA1Vec, p0);
            acc1 = vfmaq(acc1, vecIn, vecA);
            vecA = vldrhq_z_f16(pSrcA2Vec, p0);
            acc2 = vfmaq(acc2, vecIn, vecA);
            vecA = vldrhq_z_f16(pSrcA3Vec, p0);
            acc3 = vfmaq(acc3, vecIn, vecA);
        }
        /*
         * Sum the partial parts
         */
        f16x8_t         vtmp = vuninitializedq_f16();
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc0), vtmp, 0);
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc1), vtmp, 1);
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc2), vtmp, 2);
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc3), vtmp, 3);

        vSum =
            vfmaq_m_f16(vSum, vld1q(pDualCoef),
                      vtanhq_f16(vaddq_n_f16(vmulq_n_f16(vtmp, S->gamma), S->coef0)),vctp16q(4));

        pDualCoef += 4;

        pSrcA += numCols * 4;
        /*
         * Decrement the row loop counter
         */
        row -= 4;
    }

    /*
     * compute 2 rows in parrallel
     */
    if (row >= 2) {
        float16_t const *pSrcA0Vec, *pSrcA1Vec, *pInVec;
        f16x8_t         vecIn, acc0, acc1;
        float16_t const *pSrcVecPtr = in;

        /*
         * Initialize the pointers to 2 consecutive MatrixA rows
         */
        pInA0 = pSrcA;
        pInA1 = pInA0 + numCols;
        /*
         * Initialize the vector pointer
         */
        pInVec = pSrcVecPtr;
        /*
         * reset accumulators
         */
        acc0 = vdupq_n_f16(0.0f);
        acc1 = vdupq_n_f16(0.0f);
        pSrcA0Vec = pInA0;
        pSrcA1Vec = pInA1;

        blkCnt = numCols >> 3;
        while (blkCnt > 0U) {
            f16x8_t         vecA;

            vecIn = vld1q(pInVec);
            pInVec += 8;
            vecA = vld1q(pSrcA0Vec);
            pSrcA0Vec += 8;
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vld1q(pSrcA1Vec);
            pSrcA1Vec += 8;
            acc1 = vfmaq(acc1, vecIn, vecA);

            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = numCols & 7;
        if (blkCnt > 0U) {
            mve_pred16_t    p0 = vctp16q(blkCnt);
            f16x8_t         vecA;

            vecIn = vldrhq_z_f16(pInVec, p0);
            vecA = vldrhq_z_f16(pSrcA0Vec, p0);
            acc0 = vfmaq(acc0, vecIn, vecA);
            vecA = vldrhq_z_f16(pSrcA1Vec, p0);
            acc1 = vfmaq(acc1, vecIn, vecA);
        }
        /*
         * Sum the partial parts
         */
        f16x8_t         vtmp = vuninitializedq_f16();
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc0), vtmp, 0);
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc1), vtmp, 1);

        vSum =
            vfmaq_m_f16(vSum, vld1q(pDualCoef),
                        vtanhq_f16(vaddq_n_f16(vmulq_n_f16(vtmp, S->gamma), S->coef0)),
                        vctp16q(2));

        pSrcA += numCols * 2;
        row -= 2;
    }

    if (row >= 1) {
        f16x8_t         vecIn, acc0;
        float16_t const *pSrcA0Vec, *pInVec;
        float16_t const *pSrcVecPtr = in;
        /*
         * Initialize the pointers to last MatrixA row
         */
        pInA0 = pSrcA;
        /*
         * Initialize the vector pointer
         */
        pInVec = pSrcVecPtr;
        /*
         * reset accumulators
         */
        acc0 = vdupq_n_f16(0.0f);

        pSrcA0Vec = pInA0;

        blkCnt = numCols >> 3;
        while (blkCnt > 0U) {
            f16x8_t         vecA;

            vecIn = vld1q(pInVec);
            pInVec += 8;
            vecA = vld1q(pSrcA0Vec);
            pSrcA0Vec += 8;
            acc0 = vfmaq(acc0, vecIn, vecA);

            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = numCols & 7;
        if (blkCnt > 0U) {
            mve_pred16_t    p0 = vctp16q(blkCnt);
            f16x8_t         vecA;

            vecIn = vldrhq_z_f16(pInVec, p0);
            vecA = vldrhq_z_f16(pSrcA0Vec, p0);
            acc0 = vfmaq(acc0, vecIn, vecA);
        }
        /*
         * Sum the partial parts
         */
        f16x8_t         vtmp = vuninitializedq_f16();
        vtmp = vsetq_lane(vecAddAcrossF16Mve(acc0), vtmp, 0);

        vSum =
            vfmaq_m_f16(vSum, vld1q(pDualCoef),
                        vtanhq_f16(vaddq_n_f16(vmulq_n_f16(vtmp, S->gamma), S->coef0)),
                        vctp16q(1));
    }
    sum += vecAddAcrossF16Mve(vSum);

    *pResult = S->classes[STEP(sum)];
}

#else
void arm_svm_sigmoid_predict_f16(
    const arm_svm_sigmoid_instance_f16 *S,
    const float16_t * in,
    int32_t * pResult)
{
    _Float16 sum=S->intercept;
    _Float16 dot=0.0f16;
    uint32_t i,j;
    const float16_t *pSupport = S->supportVectors;

    for(i=0; i < S->nbOfSupportVectors; i++)
    {
        dot=0.0f16;
        for(j=0; j < S->vectorDimension; j++)
        {
            dot = dot + (_Float16)in[j] * (_Float16)*pSupport++;
        }
        sum += (_Float16)S->dualCoefficients[i] * (_Float16)tanhf((_Float16)S->gamma * dot + (_Float16)S->coef0);
    }
    *pResult=S->classes[STEP(sum)];
}

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of sigmoidsvm group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */

