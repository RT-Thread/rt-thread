/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_fir_f16.c
 * Description:  Floating-point FIR filter processing function
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

#include "dsp/filtering_functions_f16.h"

#if defined(ARM_FLOAT16_SUPPORTED)
/**
  @ingroup groupFilters
 */


/**
  @addtogroup FIR
  @{
 */

/**
  @brief         Processing function for floating-point FIR filter.
  @param[in]     S          points to an instance of the floating-point FIR filter structure
  @param[in]     pSrc       points to the block of input data
  @param[out]    pDst       points to the block of output data
  @param[in]     blockSize  number of samples to process
  @return        none
 */

#if defined(ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

#define FIR_F32_MAX_COEF_BLK        8

#define FIR_F16_CORE(pSamples, c, NB_TAPS)                                 \
        vecAcc0 = vdupq_n_f16(0.0f16);                                     \
        for (int i = 0; i < NB_TAPS; i++) {                                \
            vecIn0 = vld1q(&pSamples[i]);                                  \
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c[i]);                        \
        }

#define NB_TAPS 4
__STATIC_INLINE void arm_fir_f16_1_4_mve(const arm_fir_instance_f16 * S,
    const float16_t * __restrict pSrc,
    float16_t * __restrict pDst, uint32_t blockSize)
{
    float16_t      *pState = S->pState;     /* State pointer */
    const float16_t *pCoeffs = S->pCoeffs;  /* Coefficient pointer */
    float16_t      *pStateCur;              /* Points to the current sample of the state */
    const float16_t *pSamples;              /* Temporary pointer to the sample buffer */
    float16_t      *pOutput;                /* Temporary pointer to the output buffer */
    const float16_t *pTempSrc;              /* Temporary pointer to the source data */
    float16_t      *pTempDest;              /* Temporary pointer to the destination buffer */
    uint32_t        numTaps = S->numTaps;   /* Number of filter coefficients in the filter */
    int32_t         blkCnt;
    float16x8_t         vecIn0;
    float16x8_t         vecAcc0;
    float16_t       c[NB_TAPS];


    /*
     * pState points to state array which contains previous frame (numTaps - 1) samples
     * pStateCur points to the location where the new input data should be written
     */
    pStateCur = &(pState[(numTaps - 1u)]);
    /*
     * Copy new data into state so that we obtain a continuous sample buffer
     * containing both the tail end of the old data and the new data.
     */
    pSamples = pState;
    pTempSrc = pSrc;
    pOutput = pDst;

    for (int i = 0; i < NB_TAPS; i++)
        c[i] = pCoeffs[i];

    blkCnt = blockSize >> 3;
    while (blkCnt > 0) {
        /*
         * Save 8 input samples in the history buffer
         */
        vst1q(pStateCur, vld1q(pTempSrc));
        pStateCur += 8;
        pTempSrc += 8;

        FIR_F16_CORE(pSamples, c, NB_TAPS);

        vst1q(pOutput, vecAcc0);

        pOutput += 8;
        pSamples += 8;

        blkCnt--;
    }

    blkCnt = blockSize & 7;
    if (blkCnt)
    {
        mve_pred16_t    p0 = vctp16q(blkCnt);

        vst1q(pStateCur, vld1q(pTempSrc));
        pStateCur += 8;
        pTempSrc += 8;

        FIR_F16_CORE(pSamples, c, NB_TAPS);

        vstrhq_p_f16(pOutput, vecAcc0, p0);
    }

    /*
     * Copy the samples back into the history buffer start
     */
    pTempSrc = &pState[blockSize];
    pTempDest = pState;

    blkCnt = numTaps >> 3;
    while (blkCnt > 0) {
        vst1q(pTempDest, vld1q(pTempSrc));
        pTempSrc += 8;
        pTempDest += 8;
        blkCnt--;
    }
    blkCnt = numTaps & 7;
    if (blkCnt > 0) {
        mve_pred16_t    p0 = vctp16q(blkCnt);
        vstrhq_p_f16(pTempDest, vld1q(pTempSrc), p0);
    }

}
#undef NB_TAPS

#define NB_TAPS 8
__STATIC_INLINE void arm_fir_f16_5_8_mve(const arm_fir_instance_f16 * S,
    const float16_t * __restrict pSrc,
    float16_t * __restrict pDst, uint32_t blockSize)
{
    float16_t      *pState = S->pState;     /* State pointer */
    const float16_t *pCoeffs = S->pCoeffs;  /* Coefficient pointer */
    float16_t      *pStateCur;              /* Points to the current sample of the state */
    const float16_t *pSamples;              /* Temporary pointer to the sample buffer */
    float16_t      *pOutput;                /* Temporary pointer to the output buffer */
    const float16_t *pTempSrc;              /* Temporary pointer to the source data */
    float16_t      *pTempDest;              /* Temporary pointer to the destination buffer */
    uint32_t        numTaps = S->numTaps;   /* Number of filter coefficients in the filter */
    int32_t         blkCnt;
    float16x8_t         vecIn0;
    float16x8_t         vecAcc0;
    float16_t       c[NB_TAPS];


    /*
     * pState points to state array which contains previous frame (numTaps - 1) samples
     * pStateCur points to the location where the new input data should be written
     */
    pStateCur = &(pState[(numTaps - 1u)]);
    /*
     * Copy new data into state so that we obtain a continuous sample buffer
     * containing both the tail end of the old data and the new data.
     */
    pSamples = pState;
    pTempSrc = pSrc;
    pOutput = pDst;

    for (int i = 0; i < NB_TAPS; i++)
        c[i] = pCoeffs[i];

    blkCnt = blockSize >> 3;
    while (blkCnt > 0) {
        /*
         * Save 8 input samples in the history buffer
         */
        vst1q(pStateCur, vld1q(pTempSrc));
        pStateCur += 8;
        pTempSrc += 8;

        FIR_F16_CORE(pSamples, c, NB_TAPS);

        vst1q(pOutput, vecAcc0);

        pOutput += 8;
        pSamples += 8;

        blkCnt--;
    }

    blkCnt = blockSize & 7;
    if (blkCnt)
    {
        mve_pred16_t    p0 = vctp16q(blkCnt);

        vst1q(pStateCur, vld1q(pTempSrc));
        pStateCur += 8;
        pTempSrc += 8;

        FIR_F16_CORE(pSamples, c, NB_TAPS);

        vstrhq_p_f16(pOutput, vecAcc0, p0);
    }

    /*
     * Copy the samples back into the history buffer start
     */
    pTempSrc = &pState[blockSize];
    pTempDest = pState;

    blkCnt = numTaps >> 3;
    while (blkCnt > 0) {
        vst1q(pTempDest, vld1q(pTempSrc));
        pTempSrc += 8;
        pTempDest += 8;
        blkCnt--;
    }
    blkCnt = numTaps & 7;
    if (blkCnt > 0) {
        mve_pred16_t    p0 = vctp16q(blkCnt);
        vstrhq_p_f16(pTempDest, vld1q(pTempSrc), p0);
    }

}
#undef NB_TAPS

void arm_fir_f16(const arm_fir_instance_f16 * S,
  const float16_t * pSrc,
  float16_t * pDst,
  uint32_t blockSize)
{
    float16_t *pRefStatePtr = S->pState + ROUND_UP(blockSize, 8);
    float16_t *pState = pRefStatePtr ;      /* State pointer */
    const float16_t *pCoeffs = S->pCoeffs;      /* Coefficient pointer */
    const float16_t *pSamples;  /* Temporary pointer to the sample buffer */
    float16_t      *pOutput;    /* Temporary pointer to the output buffer */
    const float16_t *pTempSrc;  /* Temporary pointer to the source data */
    float16_t      *pTempDest;  /* Temporary pointer to the destination buffer */
    uint32_t        numTaps = S->numTaps;       /* Number of filter coefficients in the filter */
    uint32_t        blkCnt;
    float16_t       c0, c1, c2, c3;
    float16_t       c4, c5, c6, c7;

    /*
     * [1 to 8 taps] specialized routines
     */
    if (numTaps <= 4) {
        arm_fir_f16_1_4_mve(S, pSrc, pDst, blockSize);
        return;
    } else if (numTaps <= 8) {
        arm_fir_f16_5_8_mve(S, pSrc, pDst, blockSize);
        return;
    }

    pTempSrc = pSrc;
    pTempDest = &(pState[(numTaps - 1u)]);
    int             cnt = blockSize;
    do {
        mve_pred16_t    p0 = vctp16q(cnt);
        vstrhq_p_f16(pTempDest, vld1q(pTempSrc), p0);
        pTempDest += 8;
        pTempSrc += 8;
        cnt -= 8;
    } while (cnt > 0);

    float16_t      *partial_accu_ptr = S->pState;

    pSamples = pState;
    c0 = *pCoeffs++;
    c1 = *pCoeffs++;
    c2 = *pCoeffs++;
    c3 = *pCoeffs++;
    c4 = *pCoeffs++;
    c5 = *pCoeffs++;
    c6 = *pCoeffs++;
    c7 = *pCoeffs++;

    cnt = blockSize >> 3;
    while (cnt > 0) {
        float16x8_t     vecAcc0;
        float16x8_t     vecIn0;

        vecIn0 = vld1q(pSamples);
        vecAcc0 = vmulq(vecIn0, c0);
        vecIn0 = vld1q(&pSamples[1]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
        vecIn0 = vld1q(&pSamples[2]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
        vecIn0 = vld1q(&pSamples[3]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
        vecIn0 = vld1q(&pSamples[4]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c4);
        vecIn0 = vld1q(&pSamples[5]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c5);
        vecIn0 = vld1q(&pSamples[6]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c6);
        vecIn0 = vld1q(&pSamples[7]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c7);
        pSamples += 8;
        vst1q(partial_accu_ptr, vecAcc0);
        cnt--;
        partial_accu_ptr += 8;
    }

    cnt = blockSize & 7;
    if (cnt > 0) {
        float16x8_t     vecAcc0;
        float16x8_t     vecIn0;

        mve_pred16_t p0 = vctp16q(cnt);


        vecIn0 = vld1q(pSamples);
        vecAcc0 = vmulq(vecIn0, c0);
        vecIn0 = vld1q(&pSamples[1]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
        vecIn0 = vld1q(&pSamples[2]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
        vecIn0 = vld1q(&pSamples[3]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
        vecIn0 = vld1q(&pSamples[4]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c4);
        vecIn0 = vld1q(&pSamples[5]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c5);
        vecIn0 = vld1q(&pSamples[6]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c6);
        vecIn0 = vld1q(&pSamples[7]);
        vecAcc0 = vfmaq(vecAcc0, vecIn0, c7);
        vstrhq_p_f16(partial_accu_ptr, vecAcc0,p0);
    }

    int             localTaps = numTaps - FIR_F32_MAX_COEF_BLK;
    int             sample_offset = FIR_F32_MAX_COEF_BLK;
    while (localTaps > FIR_F32_MAX_COEF_BLK) {
        c0 = *pCoeffs++;
        c1 = *pCoeffs++;
        c2 = *pCoeffs++;
        c3 = *pCoeffs++;
        c4 = *pCoeffs++;
        c5 = *pCoeffs++;
        c6 = *pCoeffs++;
        c7 = *pCoeffs++;

        partial_accu_ptr = S->pState;
        pSamples = pState + sample_offset;
        int  cnt = blockSize >> 3;
        while (cnt > 0) {
            float16x8_t     vecAcc0;
            float16x8_t     vecIn0;


            vecIn0 = vld1q(pSamples);
            vecAcc0 = vmulq(vecIn0, c0);
            vecIn0 = vld1q(&pSamples[1]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
            vecIn0 = vld1q(&pSamples[2]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
            vecIn0 = vld1q(&pSamples[3]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
            vecIn0 = vld1q(&pSamples[4]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c4);
            vecIn0 = vld1q(&pSamples[5]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c5);
            vecIn0 = vld1q(&pSamples[6]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c6);
            vecIn0 = vld1q(&pSamples[7]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c7);
            pSamples += 8;
            vecAcc0 += vld1q_f16(partial_accu_ptr);
            vst1q(partial_accu_ptr, vecAcc0);
            cnt--;
            partial_accu_ptr += 8;
        }

        cnt = blockSize & 7;
        if (cnt > 0) {
            float16x8_t     vecAcc0;
            float16x8_t     vecIn0;

            mve_pred16_t p0 = vctp16q(cnt);

            vecIn0 = vld1q(pSamples);
            vecAcc0 = vmulq(vecIn0, c0);
            vecIn0 = vld1q(&pSamples[1]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
            vecIn0 = vld1q(&pSamples[2]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
            vecIn0 = vld1q(&pSamples[3]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
            vecIn0 = vld1q(&pSamples[4]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c4);
            vecIn0 = vld1q(&pSamples[5]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c5);
            vecIn0 = vld1q(&pSamples[6]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c6);
            vecIn0 = vld1q(&pSamples[7]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c7);
            vecAcc0 += vld1q_f16(partial_accu_ptr);
            vstrhq_p_f16(partial_accu_ptr, vecAcc0,p0);
        }

        localTaps -= FIR_F32_MAX_COEF_BLK;
        sample_offset += FIR_F32_MAX_COEF_BLK;
    }

    pSamples = pState + sample_offset;

    if (localTaps > 4) {
        c0 = *pCoeffs++;
        c1 = *pCoeffs++;
        c2 = *pCoeffs++;
        c3 = *pCoeffs++;
        c4 = *pCoeffs++;
        c5 = *pCoeffs++;
        c6 = *pCoeffs++;
        c7 = *pCoeffs++;
        pOutput = pDst;

        partial_accu_ptr = S->pState;
        cnt = blockSize >> 3;
        while (cnt > 0) {
            float16x8_t     vecAcc0;
            float16x8_t     vecIn0;

            vecIn0 = vld1q(pSamples);
            vecAcc0 = vmulq(vecIn0, c0);
            vecIn0 = vld1q(&pSamples[1]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
            vecIn0 = vld1q(&pSamples[2]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
            vecIn0 = vld1q(&pSamples[3]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
            vecIn0 = vld1q(&pSamples[4]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c4);
            vecIn0 = vld1q(&pSamples[5]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c5);
            vecIn0 = vld1q(&pSamples[6]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c6);
            vecIn0 = vld1q(&pSamples[7]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c7);
            pSamples += 8;
            float16x8_t     pap = vld1q_f16(partial_accu_ptr);
            vst1q(pOutput, vecAcc0 + pap);
            cnt--;
            partial_accu_ptr += 8;
            pOutput += 8;
        }

        cnt = blockSize & 7;
        if (cnt > 0) {
            float16x8_t     vecAcc0;
            float16x8_t     vecIn0;

            mve_pred16_t p0 = vctp16q(cnt);

            vecIn0 = vld1q(pSamples);
            vecAcc0 = vmulq(vecIn0, c0);
            vecIn0 = vld1q(&pSamples[1]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
            vecIn0 = vld1q(&pSamples[2]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
            vecIn0 = vld1q(&pSamples[3]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
            vecIn0 = vld1q(&pSamples[4]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c4);
            vecIn0 = vld1q(&pSamples[5]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c5);
            vecIn0 = vld1q(&pSamples[6]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c6);
            vecIn0 = vld1q(&pSamples[7]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c7);
            float16x8_t     pap = vld1q_f16(partial_accu_ptr);
            vstrhq_p_f16(pOutput, vecAcc0 + pap, p0);
            pOutput += cnt;
        }

    } else {
        c0 = *pCoeffs++;
        c1 = *pCoeffs++;
        c2 = *pCoeffs++;
        c3 = *pCoeffs++;
        pOutput = pDst;

        partial_accu_ptr = S->pState;
        cnt = blockSize >> 3;
        while (cnt > 0) {
            float16x8_t     vecAcc0;
            float16x8_t     vecIn0;

            vecIn0 = vld1q(pSamples);
            vecAcc0 = vmulq(vecIn0, c0);
            vecIn0 = vld1q(&pSamples[1]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
            vecIn0 = vld1q(&pSamples[2]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
            vecIn0 = vld1q(&pSamples[3]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
            pSamples += 8;
            float16x8_t     pap = vld1q_f16(partial_accu_ptr);
            vst1q(pOutput, vecAcc0 + pap);
            cnt--;
            partial_accu_ptr += 8;
            pOutput += 8;
        }

        cnt = blockSize & 7;
        if (cnt > 0) {
            float16x8_t     vecAcc0;
            float16x8_t     vecIn0;

            mve_pred16_t p0 = vctp16q(cnt);

            vecIn0 = vld1q(pSamples);
            vecAcc0 = vmulq(vecIn0, c0);
            vecIn0 = vld1q(&pSamples[1]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c1);
            vecIn0 = vld1q(&pSamples[2]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c2);
            vecIn0 = vld1q(&pSamples[3]);
            vecAcc0 = vfmaq(vecAcc0, vecIn0, c3);
            float16x8_t     pap = vld1q_f16(partial_accu_ptr);
            vstrhq_p_f16(pOutput, vecAcc0 + pap, p0);
            pOutput += cnt;
        }
    }

    /*
     * Copy the samples back into the history buffer start
     */
    pTempSrc = &pState[blockSize];
    pTempDest = pState;

    blkCnt = numTaps >> 3;
    while (blkCnt > 0U) {
        vst1q(pTempDest, vld1q(pTempSrc));
        pTempSrc += 8;
        pTempDest += 8;
        blkCnt--;
    }
    blkCnt = numTaps & 7;
    if (blkCnt > 0U) {
        mve_pred16_t    p0 = vctp16q(blkCnt);
        vstrhq_p_f16(pTempDest, vld1q(pTempSrc), p0);
    }
}

#else

void arm_fir_f16(
  const arm_fir_instance_f16 * S,
  const float16_t * pSrc,
        float16_t * pDst,
        uint32_t blockSize)
{
        float16_t *pState = S->pState;                 /* State pointer */
  const float16_t *pCoeffs = S->pCoeffs;               /* Coefficient pointer */
        float16_t *pStateCurnt;                        /* Points to the current sample of the state */
        float16_t *px;                                 /* Temporary pointer for state buffer */
  const float16_t *pb;                                 /* Temporary pointer for coefficient buffer */
        _Float16 acc0;                                /* Accumulator */
        uint32_t numTaps = S->numTaps;                 /* Number of filter coefficients in the filter */
        uint32_t i, tapCnt, blkCnt;                    /* Loop counters */

#if defined (ARM_MATH_LOOPUNROLL)
        _Float16 acc1, acc2, acc3, acc4, acc5, acc6, acc7;     /* Accumulators */
        _Float16 x0, x1, x2, x3, x4, x5, x6, x7;               /* Temporary variables to hold state values */
        _Float16 c0;                                           /* Temporary variable to hold coefficient value */
#endif

  /* S->pState points to state array which contains previous frame (numTaps - 1) samples */
  /* pStateCurnt points to the location where the new input data should be written */
  pStateCurnt = &(S->pState[(numTaps - 1U)]);

#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 8 output values simultaneously.
   * The variables acc0 ... acc7 hold output values that are being computed:
   *
   *    acc0 =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0]
   *    acc1 =  b[numTaps-1] * x[n-numTaps]   + b[numTaps-2] * x[n-numTaps-1] + b[numTaps-3] * x[n-numTaps-2] +...+ b[0] * x[1]
   *    acc2 =  b[numTaps-1] * x[n-numTaps+1] + b[numTaps-2] * x[n-numTaps]   + b[numTaps-3] * x[n-numTaps-1] +...+ b[0] * x[2]
   *    acc3 =  b[numTaps-1] * x[n-numTaps+2] + b[numTaps-2] * x[n-numTaps+1] + b[numTaps-3] * x[n-numTaps]   +...+ b[0] * x[3]
   */

  blkCnt = blockSize >> 3U;

  while (blkCnt > 0U)
  {
    /* Copy 4 new input samples into the state buffer. */
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;

    /* Set all accumulators to zero */
    acc0 = 0.0f;
    acc1 = 0.0f;
    acc2 = 0.0f;
    acc3 = 0.0f;
    acc4 = 0.0f;
    acc5 = 0.0f;
    acc6 = 0.0f;
    acc7 = 0.0f;

    /* Initialize state pointer */
    px = pState;

    /* Initialize coefficient pointer */
    pb = pCoeffs;

    /* This is separated from the others to avoid
     * a call to __aeabi_memmove which would be slower
     */
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;
    *pStateCurnt++ = *pSrc++;

    /* Read the first 7 samples from the state buffer:  x[n-numTaps], x[n-numTaps-1], x[n-numTaps-2] */
    x0 = *px++;
    x1 = *px++;
    x2 = *px++;
    x3 = *px++;
    x4 = *px++;
    x5 = *px++;
    x6 = *px++;

    /* Loop unrolling: process 8 taps at a time. */
    tapCnt = numTaps >> 3U;

    while (tapCnt > 0U)
    {
      /* Read the b[numTaps-1] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-3] sample */
      x7 = *(px++);

      /* acc0 +=  b[numTaps-1] * x[n-numTaps] */
      acc0 += x0 * c0;

      /* acc1 +=  b[numTaps-1] * x[n-numTaps-1] */
      acc1 += x1 * c0;

      /* acc2 +=  b[numTaps-1] * x[n-numTaps-2] */
      acc2 += x2 * c0;

      /* acc3 +=  b[numTaps-1] * x[n-numTaps-3] */
      acc3 += x3 * c0;

      /* acc4 +=  b[numTaps-1] * x[n-numTaps-4] */
      acc4 += x4 * c0;

      /* acc1 +=  b[numTaps-1] * x[n-numTaps-5] */
      acc5 += x5 * c0;

      /* acc2 +=  b[numTaps-1] * x[n-numTaps-6] */
      acc6 += x6 * c0;

      /* acc3 +=  b[numTaps-1] * x[n-numTaps-7] */
      acc7 += x7 * c0;

      /* Read the b[numTaps-2] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-4] sample */
      x0 = *(px++);

      /* Perform the multiply-accumulate */
      acc0 += x1 * c0;
      acc1 += x2 * c0;
      acc2 += x3 * c0;
      acc3 += x4 * c0;
      acc4 += x5 * c0;
      acc5 += x6 * c0;
      acc6 += x7 * c0;
      acc7 += x0 * c0;

      /* Read the b[numTaps-3] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-5] sample */
      x1 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += x2 * c0;
      acc1 += x3 * c0;
      acc2 += x4 * c0;
      acc3 += x5 * c0;
      acc4 += x6 * c0;
      acc5 += x7 * c0;
      acc6 += x0 * c0;
      acc7 += x1 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x2 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += x3 * c0;
      acc1 += x4 * c0;
      acc2 += x5 * c0;
      acc3 += x6 * c0;
      acc4 += x7 * c0;
      acc5 += x0 * c0;
      acc6 += x1 * c0;
      acc7 += x2 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x3 = *(px++);
      /* Perform the multiply-accumulates */
      acc0 += x4 * c0;
      acc1 += x5 * c0;
      acc2 += x6 * c0;
      acc3 += x7 * c0;
      acc4 += x0 * c0;
      acc5 += x1 * c0;
      acc6 += x2 * c0;
      acc7 += x3 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x4 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += x5 * c0;
      acc1 += x6 * c0;
      acc2 += x7 * c0;
      acc3 += x0 * c0;
      acc4 += x1 * c0;
      acc5 += x2 * c0;
      acc6 += x3 * c0;
      acc7 += x4 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x5 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += x6 * c0;
      acc1 += x7 * c0;
      acc2 += x0 * c0;
      acc3 += x1 * c0;
      acc4 += x2 * c0;
      acc5 += x3 * c0;
      acc6 += x4 * c0;
      acc7 += x5 * c0;

      /* Read the b[numTaps-4] coefficient */
      c0 = *(pb++);

      /* Read x[n-numTaps-6] sample */
      x6 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += x7 * c0;
      acc1 += x0 * c0;
      acc2 += x1 * c0;
      acc3 += x2 * c0;
      acc4 += x3 * c0;
      acc5 += x4 * c0;
      acc6 += x5 * c0;
      acc7 += x6 * c0;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    tapCnt = numTaps % 0x8U;

    while (tapCnt > 0U)
    {
      /* Read coefficients */
      c0 = *(pb++);

      /* Fetch 1 state variable */
      x7 = *(px++);

      /* Perform the multiply-accumulates */
      acc0 += x0 * c0;
      acc1 += x1 * c0;
      acc2 += x2 * c0;
      acc3 += x3 * c0;
      acc4 += x4 * c0;
      acc5 += x5 * c0;
      acc6 += x6 * c0;
      acc7 += x7 * c0;

      /* Reuse the present sample states for next sample */
      x0 = x1;
      x1 = x2;
      x2 = x3;
      x3 = x4;
      x4 = x5;
      x5 = x6;
      x6 = x7;

      /* Decrement loop counter */
      tapCnt--;
    }

    /* Advance the state pointer by 8 to process the next group of 8 samples */
    pState = pState + 8;

    /* The results in the 8 accumulators, store in the destination buffer. */
    *pDst++ = acc0;
    *pDst++ = acc1;
    *pDst++ = acc2;
    *pDst++ = acc3;
    *pDst++ = acc4;
    *pDst++ = acc5;
    *pDst++ = acc6;
    *pDst++ = acc7;


    /* Decrement loop counter */
    blkCnt--;
  }

  /* Loop unrolling: Compute remaining output samples */
  blkCnt = blockSize % 0x8U;

#else

  /* Initialize blkCnt with number of taps */
  blkCnt = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  while (blkCnt > 0U)
  {
    /* Copy one sample at a time into state buffer */
    *pStateCurnt++ = *pSrc++;

    /* Set the accumulator to zero */
    acc0 = 0.0f;

    /* Initialize state pointer */
    px = pState;

    /* Initialize Coefficient pointer */
    pb = pCoeffs;

    i = numTaps;

    /* Perform the multiply-accumulates */
    while (i > 0U)
    {
      /* acc =  b[numTaps-1] * x[n-numTaps-1] + b[numTaps-2] * x[n-numTaps-2] + b[numTaps-3] * x[n-numTaps-3] +...+ b[0] * x[0] */
      acc0 += *px++ * *pb++;

      i--;
    }

    /* Store result in destination buffer. */
    *pDst++ = acc0;

    /* Advance state pointer by 1 for the next sample */
    pState = pState + 1U;

    /* Decrement loop counter */
    blkCnt--;
  }

  /* Processing is complete.
     Now copy the last numTaps - 1 samples to the start of the state buffer.
     This prepares the state buffer for the next function call. */

  /* Points to the start of the state buffer */
  pStateCurnt = S->pState;

#if defined (ARM_MATH_LOOPUNROLL)

  /* Loop unrolling: Compute 4 taps at a time */
  tapCnt = (numTaps - 1U) >> 2U;

  /* Copy data */
  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

  /* Calculate remaining number of copies */
  tapCnt = (numTaps - 1U) % 0x4U;

#else

  /* Initialize tapCnt with number of taps */
  tapCnt = (numTaps - 1U);

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

  /* Copy remaining data */
  while (tapCnt > 0U)
  {
    *pStateCurnt++ = *pState++;

    /* Decrement loop counter */
    tapCnt--;
  }

}

#endif /* #if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE) */
/**
* @} end of FIR group
*/

#endif /* #if defined(ARM_FLOAT16_SUPPORTED) */
