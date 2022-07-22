/******************************************************************************
 * @file     arm_vec_fft.h
 * @brief    Private header file for CMSIS DSP Library
 * @version  V1.7.0
 * @date     07. January 2020
 ******************************************************************************/
/*
 * Copyright (c) 2010-2020 Arm Limited or its affiliates. All rights reserved.
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

#ifndef _ARM_VEC_FFT_H_
#define _ARM_VEC_FFT_H_

#include "arm_math.h"
#include "arm_helium_utils.h"

#ifdef   __cplusplus
extern "C"
{
#endif

#if (defined(ARM_MATH_MVEF) || defined(ARM_MATH_MVEI) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE)

#define MVE_CMPLX_ADD_A_ixB(A, B)           vcaddq_rot90(A,B)
#define MVE_CMPLX_SUB_A_ixB(A,B)            vcaddq_rot270(A,B)
#define MVE_CMPLX_MULT_FLT_AxB(A,B)         vcmlaq_rot90(vcmulq(A, B), A, B)
#define MVE_CMPLX_MULT_FLT_Conj_AxB(A,B)    vcmlaq_rot270(vcmulq(A, B), A, B)

#define MVE_CMPLX_MULT_FX_AxB(A,B)          vqdmladhxq(vqdmlsdhq((__typeof(A))vuninitializedq_s32(), A, B), A, B)
#define MVE_CMPLX_MULT_FX_AxConjB(A,B)      vqdmladhq(vqdmlsdhxq((__typeof(A))vuninitializedq_s32(), A, B), A, B)

#define MVE_CMPLX_ADD_FX_A_ixB(A, B)        vhcaddq_rot90(A,B)
#define MVE_CMPLX_SUB_FX_A_ixB(A,B)         vhcaddq_rot270(A,B)


/**
  @brief         In-place 32 bit reversal function for helium
  @param[in,out] pSrc        points to in-place buffer of unknown 32-bit data type
  @param[in]     bitRevLen   bit reversal table length
  @param[in]     pBitRevTab  points to bit reversal table
  @return        none
*/

__STATIC_INLINE void arm_bitreversal_32_inpl_mve(
        uint32_t *pSrc,
  const uint16_t  bitRevLen,
  const uint16_t *pBitRevTab)

{
    uint64_t       *src = (uint64_t *) pSrc;
    int32_t         blkCnt;     /* loop counters */
    uint32x4_t      bitRevTabOff;
    uint32x4_t      one = vdupq_n_u32(1);
    uint64x2_t      inLow, inHigh;
    uint64x2_t      bitRevOff1Low, bitRevOff0Low;
    uint64x2_t      bitRevOff1High, bitRevOff0High;

    /* load scheduling to increase gather load idx update / gather load distance */
    bitRevTabOff = vldrhq_u32(pBitRevTab);
    pBitRevTab += 4;

    bitRevOff0Low = vmullbq_int_u32(bitRevTabOff, one);
    bitRevOff0High = vmulltq_int_u32(bitRevTabOff, one);


    blkCnt = bitRevLen / 8;
    while (blkCnt > 0) {
        bitRevTabOff = vldrhq_u32(pBitRevTab);
        pBitRevTab += 4;

        /* 64-bit index expansion */
        bitRevOff1Low = vmullbq_int_u32(bitRevTabOff, one);
        bitRevOff1High = vmulltq_int_u32(bitRevTabOff, one);

        inLow = vldrdq_gather_offset_u64(src, bitRevOff0Low);
        inHigh = vldrdq_gather_offset_u64(src, bitRevOff0High);

        vstrdq_scatter_offset_u64(src, bitRevOff0Low, inHigh);
        vstrdq_scatter_offset_u64(src, bitRevOff0High, inLow);


        /* unrolled */
        bitRevTabOff = vldrhq_u32(pBitRevTab);
        pBitRevTab += 4;

        bitRevOff0Low = vmullbq_int_u32(bitRevTabOff, one);
        bitRevOff0High = vmulltq_int_u32(bitRevTabOff, one);

        inLow = vldrdq_gather_offset_u64(src, bitRevOff1Low);
        inHigh = vldrdq_gather_offset_u64(src, bitRevOff1High);

        vstrdq_scatter_offset_u64(src, bitRevOff1Low, inHigh);
        vstrdq_scatter_offset_u64(src, bitRevOff1High, inLow);

        /*
         * Decrement the blockSize loop counter
         */
        blkCnt--;
    }

    if (bitRevLen & 7) {
        /* FFT size = 16 */
        inLow = vldrdq_gather_offset_u64(src, bitRevOff0Low);
        inHigh = vldrdq_gather_offset_u64(src, bitRevOff0High);

        vstrdq_scatter_offset_u64(src, bitRevOff0Low, inHigh);
        vstrdq_scatter_offset_u64(src, bitRevOff0High, inLow);
    }
}



/**
  @brief         In-place 16 bit reversal function for helium
  @param[in,out] pSrc        points to in-place buffer of unknown 16-bit data type
  @param[in]     bitRevLen   bit reversal table length
  @param[in]     pBitRevTab  points to bit reversal table
  @return        none
*/

__STATIC_INLINE void arm_bitreversal_16_inpl_mve(
        uint16_t *pSrc,
  const uint16_t bitRevLen,
  const uint16_t *pBitRevTab)

{
    uint32_t       *src = (uint32_t *) pSrc;
    int32_t         blkCnt;     /* loop counters */
    uint32x4_t      bitRevTabOff;
    uint16x8_t      one = vdupq_n_u16(1);
    uint32x4_t      bitRevOff1Low, bitRevOff0Low;
    uint32x4_t      bitRevOff1High, bitRevOff0High;
    uint32x4_t      inLow, inHigh;

    /* load scheduling to increase gather load idx update / gather load distance */
    bitRevTabOff = vldrhq_u16(pBitRevTab);
    pBitRevTab += 8;

    bitRevOff0Low = vmullbq_int_u16(bitRevTabOff, one);
    bitRevOff0High = vmulltq_int_u16(bitRevTabOff, one);
    bitRevOff0Low = vshrq_n_u16(bitRevOff0Low, 3);
    bitRevOff0High = vshrq_n_u16(bitRevOff0High, 3);

    blkCnt = (bitRevLen / 16);
    while (blkCnt > 0) {
        bitRevTabOff = vldrhq_u16(pBitRevTab);
        pBitRevTab += 8;

        bitRevOff1Low = vmullbq_int_u16(bitRevTabOff, one);
        bitRevOff1High = vmulltq_int_u16(bitRevTabOff, one);
        bitRevOff1Low = vshrq_n_u16(bitRevOff1Low, 3);
        bitRevOff1High = vshrq_n_u16(bitRevOff1High, 3);

        inLow = vldrwq_gather_shifted_offset_u32(src, bitRevOff0Low);
        inHigh = vldrwq_gather_shifted_offset_u32(src, bitRevOff0High);

        vstrwq_scatter_shifted_offset_u32(src, bitRevOff0Low, inHigh);
        vstrwq_scatter_shifted_offset_u32(src, bitRevOff0High, inLow);

        /* loop unrolling */
        bitRevTabOff = vldrhq_u16(pBitRevTab);
        pBitRevTab += 8;

        bitRevOff0Low = vmullbq_int_u16(bitRevTabOff, one);
        bitRevOff0High = vmulltq_int_u16(bitRevTabOff, one);
        bitRevOff0Low = vshrq_n_u16(bitRevOff0Low, 3);
        bitRevOff0High = vshrq_n_u16(bitRevOff0High, 3);

        inLow = vldrwq_gather_shifted_offset_u32(src, bitRevOff1Low);
        inHigh = vldrwq_gather_shifted_offset_u32(src, bitRevOff1High);

        vstrwq_scatter_shifted_offset_u32(src, bitRevOff1Low, inHigh);
        vstrwq_scatter_shifted_offset_u32(src, bitRevOff1High, inLow);

        blkCnt--;
    }

    /* tail handling */
    blkCnt = bitRevLen & 0xf;
    if (blkCnt == 8) {
        inLow = vldrwq_gather_shifted_offset_u32(src, bitRevOff0Low);
        inHigh = vldrwq_gather_shifted_offset_u32(src, bitRevOff0High);

        vstrwq_scatter_shifted_offset_u32(src, bitRevOff0Low, inHigh);
        vstrwq_scatter_shifted_offset_u32(src, bitRevOff0High, inLow);
    } else if (blkCnt == 12) {
        /* FFT 16 special case */
        mve_pred16_t    p = vctp16q(4);

        bitRevTabOff = vldrhq_z_u16(pBitRevTab, p);

        inLow = vldrwq_gather_shifted_offset_u32(src, bitRevOff0Low);
        inHigh = vldrwq_gather_shifted_offset_u32(src, bitRevOff0High);

        vstrwq_scatter_shifted_offset_u32(src, bitRevOff0Low, inHigh);
        vstrwq_scatter_shifted_offset_u32(src, bitRevOff0High, inLow);

        bitRevOff0Low = vmullbq_int_u16(bitRevTabOff, one);
        bitRevOff0High = vmulltq_int_u16(bitRevTabOff, one);
        bitRevOff0Low = vshrq_n_u16(bitRevOff0Low, 3);
        bitRevOff0High = vshrq_n_u16(bitRevOff0High, 3);

        inLow = vldrwq_gather_shifted_offset_z_u32(src, bitRevOff0Low, p);
        inHigh = vldrwq_gather_shifted_offset_z_u32(src, bitRevOff0High, p);

        vstrwq_scatter_shifted_offset_p_u32(src, bitRevOff0Low, inHigh, p);
        vstrwq_scatter_shifted_offset_p_u32(src, bitRevOff0High, inLow, p);
    }
}

/**
  @brief         Out-of-place 32 bit reversal function for helium
  @param[out]   pDst        points to destination buffer of unknown 32-bit data type
  @param[in]    pSrc        points to input buffer of unknown 32-bit data type
  @param[in]    fftLen      FFT length
  @return       none
*/
__STATIC_INLINE void arm_bitreversal_32_outpl_mve(void *pDst, void *pSrc, uint32_t fftLen)
{
    uint32x4_t      idxOffs0, idxOffs1, bitRevOffs0, bitRevOffs1;
    uint32_t        bitRevPos, blkCnt;
    uint32_t       *pDst32 = (uint32_t *) pDst;

    /* fwd indexes */
    idxOffs0 = vdupq_n_u32(0);
    idxOffs1 = vdupq_n_u32(0);
    idxOffs0[0] = 0;    idxOffs0[2] = 4;
    idxOffs1[0] = 8;    idxOffs1[2] = 12;

    bitRevPos = (31 - __CLZ(fftLen)) + 5;
    blkCnt = fftLen >> 2;

    /* issued earlier to increase gather load idx update / gather load distance */
    /* bit-reverse fwd indexes */
    bitRevOffs0 = vbrsrq(idxOffs0, bitRevPos);
    bitRevOffs1 = vbrsrq(idxOffs1, bitRevPos);
    while (blkCnt > 0) {
        uint64x2_t      vecIn;

        vecIn = vldrdq_gather_offset_u64(pSrc, (int64x2_t) bitRevOffs0);
        idxOffs0 = idxOffs0 + 16;
        vst1q(pDst32, (uint32x4_t) vecIn);
        pDst32 += 4;
        bitRevOffs0 = vbrsrq(idxOffs0, bitRevPos);

        vecIn = vldrdq_gather_offset_u64(pSrc, (int64x2_t) bitRevOffs1);
        idxOffs1 = idxOffs1 + 16;
        vst1q(pDst32, (uint32x4_t) vecIn);
        pDst32 += 4;
        bitRevOffs1 = vbrsrq(idxOffs1, bitRevPos);

        blkCnt--;
    }
}


/**
  @brief         Out-of-place 16 bit reversal function for helium
  @param[out]   pDst        points to destination buffer of unknown 16-bit data type
  @param[in]    pSrc        points to input buffer of unknown 16-bit data type
  @param[in]    fftLen      FFT length
  @return       none
*/

__STATIC_INLINE void arm_bitreversal_16_outpl_mve(void *pDst, void *pSrc, uint32_t fftLen)
{
    uint32x4_t      idxOffs0, idxOffs1, bitRevOffs0, bitRevOffs1;
    uint32_t        bitRevPos, blkCnt;
    uint16_t       *pDst16 = (uint16_t *) pDst;
    uint32_t        incrIdx = 0;

    /* fwd indexes */
    idxOffs0 = vidupq_wb_u32(&incrIdx, 4);    // {0, 4, 8, 12}
    idxOffs1 = vidupq_wb_u32(&incrIdx, 4);    // {16, 20, 24, 28}

    bitRevPos = (31 - __CLZ(fftLen)) + 4;
    blkCnt = fftLen >> 3;

    /* issued earlier to increase gather load idx update / gather load distance */
    /* bit-reverse fwd indexes */
    bitRevOffs0 = vbrsrq(idxOffs0, bitRevPos);
    bitRevOffs1 = vbrsrq(idxOffs1, bitRevPos);
    while (blkCnt > 0) {
        uint32x4_t      vecIn;

        vecIn = vldrwq_gather_offset_s32(pSrc, bitRevOffs0);
        idxOffs0 = idxOffs0 + 32;
        vst1q(pDst16, (uint16x8_t) vecIn);
        pDst16 += 8;
        bitRevOffs0 = vbrsrq(idxOffs0, bitRevPos);

        vecIn = vldrwq_gather_offset_s32(pSrc, bitRevOffs1);
        idxOffs1 = idxOffs1 + 32;
        vst1q(pDst16, (uint16x8_t) vecIn);
        pDst16 += 8;
        bitRevOffs1 = vbrsrq(idxOffs1, bitRevPos);

        blkCnt--;
    }
}


#endif /* (defined(ARM_MATH_MVEF) || defined(ARM_MATH_HELIUM)) && !defined(ARM_MATH_AUTOVECTORIZE)*/


#ifdef   __cplusplus
}
#endif


#endif /* _ARM_VEC_FFT_H_ */
