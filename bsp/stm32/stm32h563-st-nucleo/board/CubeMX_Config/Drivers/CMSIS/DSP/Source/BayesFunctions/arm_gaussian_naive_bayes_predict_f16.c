/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_naive_gaussian_bayes_predict_f16
 * Description:  Naive Gaussian Bayesian Estimator
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

#include "dsp/bayes_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)

#include <limits.h>
#include <math.h>

#define PI_F 3.1415926535897932384626433832795f16

/**
 * @addtogroup groupBayes
 * @{
 */

/**
 * @brief Naive Gaussian Bayesian Estimator
 *
 * @param[in]  *S                       points to a naive bayes instance structure
 * @param[in]  *in                      points to the elements of the input vector.
 * @param[out] *pOutputProbabilities    points to a buffer of length numberOfClasses containing estimated probabilities
 * @param[out] *pBufferB                points to a temporary buffer of length numberOfClasses
 * @return The predicted class
 *
 *
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_helium_utils.h"
#include "arm_vec_math_f16.h"

uint32_t arm_gaussian_naive_bayes_predict_f16(const arm_gaussian_naive_bayes_instance_f16 *S, 
   const float16_t * in, 
   float16_t *pOutputProbabilities,
   float16_t *pBufferB
   )
{
    uint32_t         nbClass;
    const float16_t *pTheta = S->theta;
    const float16_t *pSigma = S->sigma;
    float16_t      *buffer = pOutputProbabilities;
    const float16_t *pIn = in;
    float16_t       result;
    f16x8_t         vsigma;
    _Float16       tmp;
    f16x8_t         vacc1, vacc2;
    uint32_t        index;
    float16_t       *logclassPriors=pBufferB;
    float16_t      *pLogPrior = logclassPriors;

    arm_vlog_f16((float16_t *) S->classPriors, logclassPriors, S->numberOfClasses);

    pTheta = S->theta;
    pSigma = S->sigma;

    for (nbClass = 0; nbClass < S->numberOfClasses; nbClass++) {
        pIn = in;

        vacc1 = vdupq_n_f16(0.0f16);
        vacc2 = vdupq_n_f16(0.0f16);

        uint32_t         blkCnt =S->vectorDimension >> 3;
        while (blkCnt > 0U) {
            f16x8_t         vinvSigma, vtmp;

            vsigma = vaddq_n_f16(vld1q(pSigma), S->epsilon);
            vacc1 = vaddq(vacc1, vlogq_f16(vmulq_n_f16(vsigma, 2.0f16 * (_Float16)PI)));

            vinvSigma = vrecip_medprec_f16(vsigma);

            vtmp = vsubq(vld1q(pIn), vld1q(pTheta));
            /* squaring */
            vtmp = vmulq(vtmp, vtmp);

            vacc2 = vfmaq(vacc2, vtmp, vinvSigma);

            pIn += 8;
            pTheta += 8;
            pSigma += 8;
            blkCnt--;
        }

        blkCnt = S->vectorDimension & 7;
        if (blkCnt > 0U) {
            mve_pred16_t    p0 = vctp16q(blkCnt);
            f16x8_t         vinvSigma, vtmp;

            vsigma = vaddq_n_f16(vld1q(pSigma), S->epsilon);
            vacc1 =
                vaddq_m_f16(vacc1, vacc1, vlogq_f16(vmulq_n_f16(vsigma, 2.0f16 * (_Float16)PI)), p0);

            vinvSigma = vrecip_medprec_f16(vsigma);

            vtmp = vsubq(vld1q(pIn), vld1q(pTheta));
            /* squaring */
            vtmp = vmulq(vtmp, vtmp);

            vacc2 = vfmaq_m_f16(vacc2, vtmp, vinvSigma, p0);

            pTheta += blkCnt;
            pSigma += blkCnt;
        }

        tmp = -0.5f16 * (_Float16)vecAddAcrossF16Mve(vacc1);
        tmp -= 0.5f16 * (_Float16)vecAddAcrossF16Mve(vacc2);

        *buffer = tmp + *pLogPrior++;
        buffer++;
    }

    arm_max_f16(pOutputProbabilities, S->numberOfClasses, &result, &index);

    return (index);
}

#else

uint32_t arm_gaussian_naive_bayes_predict_f16(const arm_gaussian_naive_bayes_instance_f16 *S, 
   const float16_t * in, 
   float16_t *pOutputProbabilities,
   float16_t *pBufferB)
{
    uint32_t nbClass;
    uint32_t nbDim;
    const float16_t *pPrior = S->classPriors;
    const float16_t *pTheta = S->theta;
    const float16_t *pSigma = S->sigma;
    float16_t *buffer = pOutputProbabilities;
    const float16_t *pIn=in;
    float16_t result;
    _Float16 sigma;
    _Float16 tmp;
    _Float16 acc1,acc2;
    uint32_t index;
    (void)pBufferB;

    pTheta=S->theta;
    pSigma=S->sigma;

    for(nbClass = 0; nbClass < S->numberOfClasses; nbClass++)
    {

        
        pIn = in;

        tmp = 0.0f16;
        acc1 = 0.0f16;
        acc2 = 0.0f16;
        for(nbDim = 0; nbDim < S->vectorDimension; nbDim++)
        {
           sigma = *pSigma + S->epsilon;
           acc1 += logf(2.0f16 * (_Float16)PI_F * sigma);
           acc2 += (*pIn - *pTheta) * (*pIn - *pTheta) / sigma;

           pIn++;
           pTheta++;
           pSigma++;
        }

        tmp = -0.5f16 * acc1;
        tmp -= 0.5f16 * acc2;


        *buffer = tmp + logf(*pPrior++);
        buffer++;
    }

    arm_max_f16(pOutputProbabilities,S->numberOfClasses,&result,&index);

    return(index);
}

#endif /* defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */

/**
 * @} end of groupBayes group
 */

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */ 

