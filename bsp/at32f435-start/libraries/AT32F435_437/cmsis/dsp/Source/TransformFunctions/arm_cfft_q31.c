/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_cfft_q31.c
 * Description:  Combined Radix Decimation in Frequency CFFT fixed point processing function
 *
 * $Date:        18. March 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
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

#include "arm_math.h"



#if defined(ARM_MATH_MVEI)

#include "arm_vec_fft.h"

static void arm_bitreversal_32_inpl_mve(
        uint32_t *pSrc,
  const uint16_t  bitRevLen,
  const uint16_t *pBitRevTab)

{
    uint64_t       *src = (uint64_t *) pSrc;
    uint32_t        blkCnt;     /* loop counters */
    uint32x4_t      bitRevTabOff;
    uint32x4_t      one = vdupq_n_u32(1);

    blkCnt = (bitRevLen / 2) / 2;
    while (blkCnt > 0U) {
        bitRevTabOff = vldrhq_u32(pBitRevTab);
        pBitRevTab += 4;

        uint64x2_t      bitRevOff1 = vmullbq_int_u32(bitRevTabOff, one);
        uint64x2_t      bitRevOff2 = vmulltq_int_u32(bitRevTabOff, one);

        uint64x2_t      in1 = vldrdq_gather_offset_u64(src, bitRevOff1);
        uint64x2_t      in2 = vldrdq_gather_offset_u64(src, bitRevOff2);

        vstrdq_scatter_offset_u64(src, bitRevOff1, in2);
        vstrdq_scatter_offset_u64(src, bitRevOff2, in1);

        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }
}

static void _arm_radix4_butterfly_q31_mve(
    const arm_cfft_instance_q31 * S,
    q31_t   *pSrc,
    uint32_t fftLen)
{
    q31x4_t vecTmp0, vecTmp1;
    q31x4_t vecSum0, vecDiff0, vecSum1, vecDiff1;
    q31x4_t vecA, vecB, vecC, vecD;
    q31x4_t vecW;
    uint32_t  blkCnt;
    uint32_t  n1, n2;
    uint32_t  stage = 0;
    int32_t  iter = 1;
    static const uint32_t strides[4] = {
        (0 - 16) * sizeof(q31_t *), (1 - 16) * sizeof(q31_t *),
        (8 - 16) * sizeof(q31_t *), (9 - 16) * sizeof(q31_t *)
    };


    /*
     * Process first stages
     * Each stage in middle stages provides two down scaling of the input
     */
    n2 = fftLen;
    n1 = n2;
    n2 >>= 2u;

    for (int k = fftLen / 4u; k > 1; k >>= 2u)
    {
        for (int i = 0; i < iter; i++)
        {
            q31_t const *p_rearranged_twiddle_tab_stride2 =
                &S->rearranged_twiddle_stride2[
                S->rearranged_twiddle_tab_stride2_arr[stage]];
            q31_t const *p_rearranged_twiddle_tab_stride3 = &S->rearranged_twiddle_stride3[
                S->rearranged_twiddle_tab_stride3_arr[stage]];
            q31_t const *p_rearranged_twiddle_tab_stride1 =
                &S->rearranged_twiddle_stride1[
                S->rearranged_twiddle_tab_stride1_arr[stage]];
            q31_t const *pW1, *pW2, *pW3;
            q31_t    *inA = pSrc + CMPLX_DIM * i * n1;
            q31_t    *inB = inA + n2 * CMPLX_DIM;
            q31_t    *inC = inB + n2 * CMPLX_DIM;
            q31_t    *inD = inC + n2 * CMPLX_DIM;

            pW1 = p_rearranged_twiddle_tab_stride1;
            pW2 = p_rearranged_twiddle_tab_stride2;
            pW3 = p_rearranged_twiddle_tab_stride3;

            blkCnt = n2 / 2;
            /*
             * load 2 x q31 complex pair
             */
            vecA = vldrwq_s32(inA);
            vecC = vldrwq_s32(inC);
            while (blkCnt > 0U)
            {
                vecB = vldrwq_s32(inB);
                vecD = vldrwq_s32(inD);

                vecSum0 = vhaddq(vecA, vecC);
                vecDiff0 = vhsubq(vecA, vecC);

                vecSum1 = vhaddq(vecB, vecD);
                vecDiff1 = vhsubq(vecB, vecD);
                /*
                 * [ 1 1 1 1 ] * [ A B C D ]' .* 1
                 */
                vecTmp0 = vhaddq(vecSum0, vecSum1);
                vst1q(inA, vecTmp0);
                inA += 4;
                /*
                 * [ 1 -1 1 -1 ] * [ A B C D ]'
                 */
                vecTmp0 = vhsubq(vecSum0, vecSum1);
                /*
                 * [ 1 -1 1 -1 ] * [ A B C D ]'.* W2
                 */
                vecW = vld1q(pW2);
                pW2 += 4;
                vecTmp1 = MVE_CMPLX_MULT_FX_AxB(vecW, vecTmp0);

                vst1q(inB, vecTmp1);
                inB += 4;
                /*
                 * [ 1 -i -1 +i ] * [ A B C D ]'
                 */
                vecTmp0 = MVE_CMPLX_SUB_FX_A_ixB(vecDiff0, vecDiff1);
                /*
                 * [ 1 -i -1 +i ] * [ A B C D ]'.* W1
                 */
                vecW = vld1q(pW1);
                pW1 += 4;
                vecTmp1 = MVE_CMPLX_MULT_FX_AxB(vecW, vecTmp0);
                vst1q(inC, vecTmp1);
                inC += 4;
                /*
                 * [ 1 +i -1 -i ] * [ A B C D ]'
                 */
                vecTmp0 = MVE_CMPLX_ADD_FX_A_ixB(vecDiff0, vecDiff1);
                /*
                 * [ 1 +i -1 -i ] * [ A B C D ]'.* W3
                 */
                vecW = vld1q(pW3);
                pW3 += 4;
                vecTmp1 = MVE_CMPLX_MULT_FX_AxB(vecW, vecTmp0);
                vst1q(inD, vecTmp1);
                inD += 4;

                vecA = vldrwq_s32(inA);
                vecC = vldrwq_s32(inC);

                blkCnt--;
            }
        }
        n1 = n2;
        n2 >>= 2u;
        iter = iter << 2;
        stage++;
    }

    /*
     * End of 1st stages process
     * data is in 11.21(q21) format for the 1024 point as there are 3 middle stages
     * data is in 9.23(q23) format for the 256 point as there are 2 middle stages
     * data is in 7.25(q25) format for the 64 point as there are 1 middle stage
     * data is in 5.27(q27) format for the 16 point as there are no middle stages
     */

    /*
     * start of Last stage process
     */
    uint32x4_t vecScGathAddr = *(uint32x4_t *) strides;
    vecScGathAddr = vecScGathAddr + (uint32_t) pSrc;

    /*
     * load scheduling
     */
    vecA = vldrwq_gather_base_wb_s32(&vecScGathAddr, 64);
    vecC = vldrwq_gather_base_s32(vecScGathAddr, 16);

    blkCnt = (fftLen >> 3);
    while (blkCnt > 0U)
    {
        vecSum0 = vhaddq(vecA, vecC);
        vecDiff0 = vhsubq(vecA, vecC);

        vecB = vldrwq_gather_base_s32(vecScGathAddr, 8);
        vecD = vldrwq_gather_base_s32(vecScGathAddr, 24);

        vecSum1 = vhaddq(vecB, vecD);
        vecDiff1 = vhsubq(vecB, vecD);
        /*
         * pre-load for next iteration
         */
        vecA = vldrwq_gather_base_wb_s32(&vecScGathAddr, 64);
        vecC = vldrwq_gather_base_s32(vecScGathAddr, 16);

        vecTmp0 = vhaddq(vecSum0, vecSum1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64, vecTmp0);

        vecTmp0 = vhsubq(vecSum0, vecSum1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64 + 8, vecTmp0);

        vecTmp0 = MVE_CMPLX_SUB_FX_A_ixB(vecDiff0, vecDiff1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64 + 16, vecTmp0);

        vecTmp0 = MVE_CMPLX_ADD_FX_A_ixB(vecDiff0, vecDiff1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64 + 24, vecTmp0);

        blkCnt--;
    }

    /*
     * output is in 11.21(q21) format for the 1024 point
     * output is in 9.23(q23) format for the 256 point
     * output is in 7.25(q25) format for the 64 point
     * output is in 5.27(q27) format for the 16 point
     */
}


static void arm_cfft_radix4by2_q31_mve(const arm_cfft_instance_q31 *S, q31_t *pSrc, uint32_t fftLen)
{
    uint32_t     n2;
    q31_t       *pIn0;
    q31_t       *pIn1;
    const q31_t *pCoef = S->pTwiddle;
    uint32_t     blkCnt;
    q31x4_t    vecIn0, vecIn1, vecSum, vecDiff;
    q31x4_t    vecCmplxTmp, vecTw;

    n2 = fftLen >> 1;
    pIn0 = pSrc;
    pIn1 = pSrc + fftLen;

    blkCnt = n2 / 2;

    while (blkCnt > 0U)
    {
        vecIn0 = vld1q_s32(pIn0);
        vecIn1 = vld1q_s32(pIn1);

        vecIn0 = vecIn0 >> 1;
        vecIn1 = vecIn1 >> 1;
        vecSum = vhaddq(vecIn0, vecIn1);
        vst1q(pIn0, vecSum);
        pIn0 += 4;

        vecTw = vld1q_s32(pCoef);
        pCoef += 4;
        vecDiff = vhsubq(vecIn0, vecIn1);

        vecCmplxTmp = MVE_CMPLX_MULT_FX_AxConjB(vecDiff, vecTw);
        vst1q(pIn1, vecCmplxTmp);
        pIn1 += 4;

        blkCnt--;
    }

   _arm_radix4_butterfly_q31_mve(S, pSrc, n2);

   _arm_radix4_butterfly_q31_mve(S, pSrc + fftLen, n2);

    pIn0 = pSrc;
    blkCnt = (fftLen << 1) >> 2;
    while (blkCnt > 0U)
    {
        vecIn0 = vld1q_s32(pIn0);
        vecIn0 = vecIn0 << 1;
        vst1q(pIn0, vecIn0);
        pIn0 += 4;
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = (fftLen << 1) & 3;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp32q(blkCnt);

        vecIn0 = vld1q_s32(pIn0);
        vecIn0 = vecIn0 << 1;
        vstrwq_p(pIn0, vecIn0, p0);
    }

}

static void _arm_radix4_butterfly_inverse_q31_mve(
    const arm_cfft_instance_q31 *S,
    q31_t   *pSrc,
    uint32_t fftLen)
{
    q31x4_t vecTmp0, vecTmp1;
    q31x4_t vecSum0, vecDiff0, vecSum1, vecDiff1;
    q31x4_t vecA, vecB, vecC, vecD;
    q31x4_t vecW;
    uint32_t  blkCnt;
    uint32_t  n1, n2;
    uint32_t  stage = 0;
    int32_t  iter = 1;
    static const uint32_t strides[4] = {
        (0 - 16) * sizeof(q31_t *), (1 - 16) * sizeof(q31_t *),
        (8 - 16) * sizeof(q31_t *), (9 - 16) * sizeof(q31_t *)
    };

    /*
     * Process first stages
     * Each stage in middle stages provides two down scaling of the input
     */
    n2 = fftLen;
    n1 = n2;
    n2 >>= 2u;

    for (int k = fftLen / 4u; k > 1; k >>= 2u)
    {
        for (int i = 0; i < iter; i++)
        {
            q31_t const *p_rearranged_twiddle_tab_stride2 =
                &S->rearranged_twiddle_stride2[
                S->rearranged_twiddle_tab_stride2_arr[stage]];
            q31_t const *p_rearranged_twiddle_tab_stride3 = &S->rearranged_twiddle_stride3[
                S->rearranged_twiddle_tab_stride3_arr[stage]];
            q31_t const *p_rearranged_twiddle_tab_stride1 =
                &S->rearranged_twiddle_stride1[
                S->rearranged_twiddle_tab_stride1_arr[stage]];

            q31_t const *pW1, *pW2, *pW3;
            q31_t    *inA = pSrc + CMPLX_DIM * i * n1;
            q31_t    *inB = inA + n2 * CMPLX_DIM;
            q31_t    *inC = inB + n2 * CMPLX_DIM;
            q31_t    *inD = inC + n2 * CMPLX_DIM;

            pW1 = p_rearranged_twiddle_tab_stride1;
            pW2 = p_rearranged_twiddle_tab_stride2;
            pW3 = p_rearranged_twiddle_tab_stride3;

            blkCnt = n2 / 2;
            /*
             * load 2 x q31 complex pair
             */
            vecA = vldrwq_s32(inA);
            vecC = vldrwq_s32(inC);
            while (blkCnt > 0U)
            {
                vecB = vldrwq_s32(inB);
                vecD = vldrwq_s32(inD);

                vecSum0 = vhaddq(vecA, vecC);
                vecDiff0 = vhsubq(vecA, vecC);

                vecSum1 = vhaddq(vecB, vecD);
                vecDiff1 = vhsubq(vecB, vecD);
                /*
                 * [ 1 1 1 1 ] * [ A B C D ]' .* 1
                 */
                vecTmp0 = vhaddq(vecSum0, vecSum1);
                vst1q(inA, vecTmp0);
                inA += 4;
                /*
                 * [ 1 -1 1 -1 ] * [ A B C D ]'
                 */
                vecTmp0 = vhsubq(vecSum0, vecSum1);
                /*
                 * [ 1 -1 1 -1 ] * [ A B C D ]'.* W2
                 */
                vecW = vld1q(pW2);
                pW2 += 4;
                vecTmp1 = MVE_CMPLX_MULT_FX_AxConjB(vecTmp0, vecW);

                vst1q(inB, vecTmp1);
                inB += 4;
                /*
                 * [ 1 -i -1 +i ] * [ A B C D ]'
                 */
                vecTmp0 = MVE_CMPLX_ADD_FX_A_ixB(vecDiff0, vecDiff1);
                /*
                 * [ 1 -i -1 +i ] * [ A B C D ]'.* W1
                 */
                vecW = vld1q(pW1);
                pW1 += 4;
                vecTmp1 = MVE_CMPLX_MULT_FX_AxConjB(vecTmp0, vecW);
                vst1q(inC, vecTmp1);
                inC += 4;
                /*
                 * [ 1 +i -1 -i ] * [ A B C D ]'
                 */
                vecTmp0 = MVE_CMPLX_SUB_FX_A_ixB(vecDiff0, vecDiff1);
                /*
                 * [ 1 +i -1 -i ] * [ A B C D ]'.* W3
                 */
                vecW = vld1q(pW3);
                pW3 += 4;
                vecTmp1 = MVE_CMPLX_MULT_FX_AxConjB(vecTmp0, vecW);
                vst1q(inD, vecTmp1);
                inD += 4;

                vecA = vldrwq_s32(inA);
                vecC = vldrwq_s32(inC);

                blkCnt--;
            }
        }
        n1 = n2;
        n2 >>= 2u;
        iter = iter << 2;
        stage++;
    }

    /*
     * End of 1st stages process
     * data is in 11.21(q21) format for the 1024 point as there are 3 middle stages
     * data is in 9.23(q23) format for the 256 point as there are 2 middle stages
     * data is in 7.25(q25) format for the 64 point as there are 1 middle stage
     * data is in 5.27(q27) format for the 16 point as there are no middle stages
     */

    /*
     * start of Last stage process
     */
    uint32x4_t vecScGathAddr = *(uint32x4_t *) strides;
    vecScGathAddr = vecScGathAddr + (uint32_t) pSrc;

    /*
     * load scheduling
     */
    vecA = vldrwq_gather_base_wb_s32(&vecScGathAddr, 64);
    vecC = vldrwq_gather_base_s32(vecScGathAddr, 16);

    blkCnt = (fftLen >> 3);
    while (blkCnt > 0U)
    {
        vecSum0 = vhaddq(vecA, vecC);
        vecDiff0 = vhsubq(vecA, vecC);

        vecB = vldrwq_gather_base_s32(vecScGathAddr, 8);
        vecD = vldrwq_gather_base_s32(vecScGathAddr, 24);

        vecSum1 = vhaddq(vecB, vecD);
        vecDiff1 = vhsubq(vecB, vecD);
        /*
         * pre-load for next iteration
         */
        vecA = vldrwq_gather_base_wb_s32(&vecScGathAddr, 64);
        vecC = vldrwq_gather_base_s32(vecScGathAddr, 16);

        vecTmp0 = vhaddq(vecSum0, vecSum1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64, vecTmp0);

        vecTmp0 = vhsubq(vecSum0, vecSum1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64 + 8, vecTmp0);

        vecTmp0 = MVE_CMPLX_ADD_FX_A_ixB(vecDiff0, vecDiff1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64 + 16, vecTmp0);

        vecTmp0 = MVE_CMPLX_SUB_FX_A_ixB(vecDiff0, vecDiff1);
        vstrwq_scatter_base_s32(vecScGathAddr, -64 + 24, vecTmp0);

        blkCnt--;
    }
    /*
     * output is in 11.21(q21) format for the 1024 point
     * output is in 9.23(q23) format for the 256 point
     * output is in 7.25(q25) format for the 64 point
     * output is in 5.27(q27) format for the 16 point
     */
}

static void arm_cfft_radix4by2_inverse_q31_mve(const arm_cfft_instance_q31 *S, q31_t *pSrc, uint32_t fftLen)
{
    uint32_t     n2;
    q31_t       *pIn0;
    q31_t       *pIn1;
    const q31_t *pCoef = S->pTwiddle;

    //uint16_t     twidCoefModifier = arm_cfft_radix2_twiddle_factor(S->fftLen);
    //q31_t        twidIncr = (2 * twidCoefModifier * sizeof(q31_t));
    uint32_t     blkCnt;
    //uint64x2_t   vecOffs;
    q31x4_t    vecIn0, vecIn1, vecSum, vecDiff;
    q31x4_t    vecCmplxTmp, vecTw;

    n2 = fftLen >> 1;

    pIn0 = pSrc;
    pIn1 = pSrc + fftLen;
    //vecOffs[0] = 0;
    //vecOffs[1] = (uint64_t) twidIncr;
    blkCnt = n2 / 2;

    while (blkCnt > 0U)
    {
        vecIn0 = vld1q_s32(pIn0);
        vecIn1 = vld1q_s32(pIn1);

        vecIn0 = vecIn0 >> 1;
        vecIn1 = vecIn1 >> 1;
        vecSum = vhaddq(vecIn0, vecIn1);
        vst1q(pIn0, vecSum);
        pIn0 += 4;

        //vecTw = (q31x4_t) vldrdq_gather_offset_s64(pCoef, vecOffs);
        vecTw = vld1q_s32(pCoef);
        pCoef += 4;
        vecDiff = vhsubq(vecIn0, vecIn1);

        vecCmplxTmp = MVE_CMPLX_MULT_FX_AxB(vecDiff, vecTw);
        vst1q(pIn1, vecCmplxTmp);
        pIn1 += 4;

        //vecOffs = vaddq((q31x4_t) vecOffs, 2 * twidIncr);
        blkCnt--;
    }

    _arm_radix4_butterfly_inverse_q31_mve(S, pSrc, n2);

    _arm_radix4_butterfly_inverse_q31_mve(S, pSrc + fftLen, n2);

    pIn0 = pSrc;
    blkCnt = (fftLen << 1) >> 2;
    while (blkCnt > 0U)
    {
        vecIn0 = vld1q_s32(pIn0);
        vecIn0 = vecIn0 << 1;
        vst1q(pIn0, vecIn0);
        pIn0 += 4;
        blkCnt--;
    }
    /*
     * tail
     * (will be merged thru tail predication)
     */
    blkCnt = (fftLen << 1) & 3;
    if (blkCnt > 0U)
    {
        mve_pred16_t p0 = vctp32q(blkCnt);

        vecIn0 = vld1q_s32(pIn0);
        vecIn0 = vecIn0 << 1;
        vstrwq_p(pIn0, vecIn0, p0);
    }

}

/**
  @ingroup groupTransforms
 */

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Processing function for the Q31 complex FFT.
  @param[in]     S               points to an instance of the fixed-point CFFT structure
  @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @param[in]     ifftFlag       flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        none
 */
void arm_cfft_q31(
  const arm_cfft_instance_q31 * S,
        q31_t * pSrc,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
        uint32_t fftLen = S->fftLen;

        if (ifftFlag == 1U) {

            switch (fftLen) {
            case 16:
            case 64:
            case 256:
            case 1024:
            case 4096:
                _arm_radix4_butterfly_inverse_q31_mve(S, pSrc, fftLen);
                break;

            case 32:
            case 128:
            case 512:
            case 2048:
                arm_cfft_radix4by2_inverse_q31_mve(S, pSrc, fftLen);
                break;
            }
        } else {
            switch (fftLen) {
            case 16:
            case 64:
            case 256:
            case 1024:
            case 4096:
                _arm_radix4_butterfly_q31_mve(S, pSrc, fftLen);
                break;

            case 32:
            case 128:
            case 512:
            case 2048:
                arm_cfft_radix4by2_q31_mve(S, pSrc, fftLen);
                break;
            }
        }


        if (bitReverseFlag)
        {

            arm_bitreversal_32_inpl_mve((uint32_t*)pSrc, S->bitRevLength, S->pBitRevTable);

        }
}
#else

extern void arm_radix4_butterfly_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef,
        uint32_t twidCoefModifier);

extern void arm_radix4_butterfly_inverse_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef,
        uint32_t twidCoefModifier);

extern void arm_bitreversal_32(
        uint32_t * pSrc,
  const uint16_t bitRevLen,
  const uint16_t * pBitRevTable);

void arm_cfft_radix4by2_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef);

void arm_cfft_radix4by2_inverse_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef);


/**
  @ingroup groupTransforms
 */

/**
  @addtogroup ComplexFFT
  @{
 */

/**
  @brief         Processing function for the Q31 complex FFT.
  @param[in]     S               points to an instance of the fixed-point CFFT structure
  @param[in,out] p1              points to the complex data buffer of size <code>2*fftLen</code>. Processing occurs in-place
  @param[in]     ifftFlag       flag that selects transform direction
                   - value = 0: forward transform
                   - value = 1: inverse transform
  @param[in]     bitReverseFlag flag that enables / disables bit reversal of output
                   - value = 0: disables bit reversal of output
                   - value = 1: enables bit reversal of output
  @return        none
 */
void arm_cfft_q31(
  const arm_cfft_instance_q31 * S,
        q31_t * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag)
{
  uint32_t L = S->fftLen;

  if (ifftFlag == 1U)
  {
     switch (L)
     {
     case 16:
     case 64:
     case 256:
     case 1024:
     case 4096:
       arm_radix4_butterfly_inverse_q31 ( p1, L, (q31_t*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       arm_cfft_radix4by2_inverse_q31 ( p1, L, S->pTwiddle );
       break;
     }
  }
  else
  {
     switch (L)
     {
     case 16:
     case 64:
     case 256:
     case 1024:
     case 4096:
       arm_radix4_butterfly_q31 ( p1, L, (q31_t*)S->pTwiddle, 1 );
       break;

     case 32:
     case 128:
     case 512:
     case 2048:
       arm_cfft_radix4by2_q31 ( p1, L, S->pTwiddle );
       break;
     }
  }

  if ( bitReverseFlag )
    arm_bitreversal_32 ((uint32_t*) p1, S->bitRevLength, S->pBitRevTable);
}

/**
  @} end of ComplexFFT group
 */

void arm_cfft_radix4by2_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef)
{
        uint32_t i, l;
        uint32_t n2;
        q31_t xt, yt, cosVal, sinVal;
        q31_t p0, p1;

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =          (pSrc[2 * i] >> 2U) - (pSrc[2 * l] >> 2U);
     pSrc[2 * i] = (pSrc[2 * i] >> 2U) + (pSrc[2 * l] >> 2U);

     yt =              (pSrc[2 * i + 1] >> 2U) - (pSrc[2 * l + 1] >> 2U);
     pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2U) + (pSrc[2 * i + 1] >> 2U);

     mult_32x32_keep32_R(p0, xt, cosVal);
     mult_32x32_keep32_R(p1, yt, cosVal);
     multAcc_32x32_keep32_R(p0, yt, sinVal);
     multSub_32x32_keep32_R(p1, xt, sinVal);

     pSrc[2 * l]     = p0 << 1;
     pSrc[2 * l + 1] = p1 << 1;
  }


  /* first col */
  arm_radix4_butterfly_q31 (pSrc,          n2, (q31_t*)pCoef, 2U);

  /* second col */
  arm_radix4_butterfly_q31 (pSrc + fftLen, n2, (q31_t*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     xt = pSrc[4 * i + 2];
     yt = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     xt <<= 1U;
     yt <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = xt;
     pSrc[4 * i + 3] = yt;
  }

}

void arm_cfft_radix4by2_inverse_q31(
        q31_t * pSrc,
        uint32_t fftLen,
  const q31_t * pCoef)
{
  uint32_t i, l;
  uint32_t n2;
  q31_t xt, yt, cosVal, sinVal;
  q31_t p0, p1;

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     cosVal = pCoef[2 * i];
     sinVal = pCoef[2 * i + 1];

     l = i + n2;

     xt =          (pSrc[2 * i] >> 2U) - (pSrc[2 * l] >> 2U);
     pSrc[2 * i] = (pSrc[2 * i] >> 2U) + (pSrc[2 * l] >> 2U);

     yt =              (pSrc[2 * i + 1] >> 2U) - (pSrc[2 * l + 1] >> 2U);
     pSrc[2 * i + 1] = (pSrc[2 * l + 1] >> 2U) + (pSrc[2 * i + 1] >> 2U);

     mult_32x32_keep32_R(p0, xt, cosVal);
     mult_32x32_keep32_R(p1, yt, cosVal);
     multSub_32x32_keep32_R(p0, yt, sinVal);
     multAcc_32x32_keep32_R(p1, xt, sinVal);

     pSrc[2 * l]     = p0 << 1U;
     pSrc[2 * l + 1] = p1 << 1U;
  }

  /* first col */
  arm_radix4_butterfly_inverse_q31( pSrc,          n2, (q31_t*)pCoef, 2U);

  /* second col */
  arm_radix4_butterfly_inverse_q31( pSrc + fftLen, n2, (q31_t*)pCoef, 2U);

  n2 = fftLen >> 1U;
  for (i = 0; i < n2; i++)
  {
     p0 = pSrc[4 * i + 0];
     p1 = pSrc[4 * i + 1];
     xt = pSrc[4 * i + 2];
     yt = pSrc[4 * i + 3];

     p0 <<= 1U;
     p1 <<= 1U;
     xt <<= 1U;
     yt <<= 1U;

     pSrc[4 * i + 0] = p0;
     pSrc[4 * i + 1] = p1;
     pSrc[4 * i + 2] = xt;
     pSrc[4 * i + 3] = yt;
  }
}
#endif /* defined(ARM_MATH_MVEI) */
