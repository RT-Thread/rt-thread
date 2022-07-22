/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_helium_utils.h
 * Description:  Utility functions for Helium development
 *
 * @version  V1.9.0
 * @date     23 April 2021
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

#ifndef _ARM_UTILS_HELIUM_H_
#define _ARM_UTILS_HELIUM_H_


#ifdef   __cplusplus
extern "C"
{
#endif
/***************************************

Definitions available for MVEF and MVEI

***************************************/
#if (defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEF) || defined(ARM_MATH_MVEI))  && !defined(ARM_MATH_AUTOVECTORIZE)

#define INACTIVELANE            0 /* inactive lane content */


#endif /* defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEF) || defined(ARM_MATH_MVEI) */

/***************************************

Definitions available for MVEF only

***************************************/
#if (defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEF))  && !defined(ARM_MATH_AUTOVECTORIZE)

__STATIC_FORCEINLINE float32_t vecAddAcrossF32Mve(float32x4_t in)
{
    float32_t acc;

    acc = vgetq_lane(in, 0) + vgetq_lane(in, 1) +
          vgetq_lane(in, 2) + vgetq_lane(in, 3);

    return acc;
}




/* newton initial guess */
#define INVSQRT_MAGIC_F32           0x5f3759df
#define INV_NEWTON_INIT_F32         0x7EF127EA


#define INVSQRT_NEWTON_MVE_F32(invSqrt, xHalf, xStart)\
{                                                     \
    float32x4_t tmp;                                  \
                                                      \
    /* tmp = xhalf * x * x */                         \
    tmp = vmulq(xStart, xStart);                      \
    tmp = vmulq(tmp, xHalf);                          \
    /* (1.5f - xhalf * x * x) */                      \
    tmp = vsubq(vdupq_n_f32(1.5f), tmp);              \
    /* x = x*(1.5f-xhalf*x*x); */                     \
    invSqrt = vmulq(tmp, xStart);                     \
}
#endif /* defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEF) */


/***************************************

Definitions available for f16 datatype with HW acceleration only

***************************************/
#if defined(ARM_FLOAT16_SUPPORTED)
#if defined (ARM_MATH_MVE_FLOAT16) && !defined(ARM_MATH_AUTOVECTORIZE)

__STATIC_FORCEINLINE float16_t vecAddAcrossF16Mve(float16x8_t in)
{
    float16x8_t tmpVec;
    _Float16 acc;

    tmpVec = (float16x8_t) vrev32q_s16((int16x8_t) in);
    in = vaddq_f16(tmpVec, in);
    tmpVec = (float16x8_t) vrev64q_s32((int32x4_t) in);
    in = vaddq_f16(tmpVec, in);
    acc = (_Float16)vgetq_lane_f16(in, 0) + (_Float16)vgetq_lane_f16(in, 4);

    return acc;
}

__STATIC_FORCEINLINE float16x8_t __mve_cmplx_sum_intra_vec_f16(
    float16x8_t   vecIn)
{
    float16x8_t   vecTmp, vecOut;
    uint32_t    tmp;

    vecTmp = (float16x8_t) vrev64q_s32((int32x4_t) vecIn);
    // TO TRACK : using canonical addition leads to unefficient code generation for f16
    // vecTmp = vecTmp + vecAccCpx0;
    /*
     * Compute
     *  re0+re1 | im0+im1 | re0+re1 | im0+im1
     *  re2+re3 | im2+im3 | re2+re3 | im2+im3
     */
    vecTmp = vaddq_f16(vecTmp, vecIn);
    vecOut = vecTmp;
    /*
     * shift left, random tmp insertion in bottom
     */
    vecOut = vreinterpretq_f16_s32(vshlcq_s32(vreinterpretq_s32_f16(vecOut)   , &tmp, 32));
    /*
     * Compute:
     *    DONTCARE     |    DONTCARE     | re0+re1+re0+re1 |im0+im1+im0+im1
     * re0+re1+re2+re3 | im0+im1+im2+im3 | re2+re3+re2+re3 |im2+im3+im2+im3
     */
    vecOut = vaddq_f16(vecOut, vecTmp);
    /*
     * Cmplx sum is in 4rd & 5th f16 elt
     * return full vector
     */
    return vecOut;
}


#define mve_cmplx_sum_intra_r_i_f16(vec, Re, Im)                \
{                                                               \
    float16x8_t   vecOut = __mve_cmplx_sum_intra_vec_f16(vec);    \
    Re = vgetq_lane(vecOut, 4);                                 \
    Im = vgetq_lane(vecOut, 5);                                 \
}

__STATIC_FORCEINLINE void mve_cmplx_sum_intra_vec_f16(
    float16x8_t   vecIn,
    float16_t  *pOut)
{
    float16x8_t   vecOut = __mve_cmplx_sum_intra_vec_f16(vecIn);
    /*
     * Cmplx sum is in 4rd & 5th f16 elt
     * use 32-bit extraction
     */
    *(float32_t *) pOut = ((float32x4_t) vecOut)[2];
}


#define INVSQRT_MAGIC_F16           0x59ba      /*  ( 0x1ba = 0x3759df >> 13) */

/* canonical version of INVSQRT_NEWTON_MVE_F16 leads to bad performance */
#define INVSQRT_NEWTON_MVE_F16(invSqrt, xHalf, xStart)                  \
{                                                                       \
    float16x8_t tmp;                                                      \
                                                                        \
    /* tmp = xhalf * x * x */                                           \
    tmp = vmulq(xStart, xStart);                                        \
    tmp = vmulq(tmp, xHalf);                                            \
    /* (1.5f - xhalf * x * x) */                                        \
    tmp = vsubq(vdupq_n_f16((float16_t)1.5), tmp);                      \
    /* x = x*(1.5f-xhalf*x*x); */                                       \
    invSqrt = vmulq(tmp, xStart);                                       \
}

#endif
#endif

/***************************************

Definitions available for MVEI and MVEF only

***************************************/
#if (defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEF) || defined(ARM_MATH_MVEI))  && !defined(ARM_MATH_AUTOVECTORIZE)
/* Following functions are used to transpose matrix in f32 and q31 cases */
__STATIC_INLINE arm_status arm_mat_trans_32bit_2x2_mve(
    uint32_t * pDataSrc,
    uint32_t * pDataDest)
{
    static const uint32x4_t vecOffs = { 0, 2, 1, 3 };
    /*
     *
     * | 0   1 |   =>  |  0   2 |
     * | 2   3 |       |  1   3 |
     *
     */
    uint32x4_t vecIn = vldrwq_u32((uint32_t const *)pDataSrc);
    vstrwq_scatter_shifted_offset_u32(pDataDest, vecOffs, vecIn);

    return (ARM_MATH_SUCCESS);
}

__STATIC_INLINE arm_status arm_mat_trans_32bit_3x3_mve(
    uint32_t * pDataSrc,
    uint32_t * pDataDest)
{
    const uint32x4_t vecOffs1 = { 0, 3, 6, 1};
    const uint32x4_t vecOffs2 = { 4, 7, 2, 5};
    /*
     *
     *  | 0   1   2 |       | 0   3   6 |  4 x 32 flattened version | 0   3   6   1 |
     *  | 3   4   5 |   =>  | 1   4   7 |            =>             | 4   7   2   5 |
     *  | 6   7   8 |       | 2   5   8 |       (row major)         | 8   .   .   . |
     *
     */
    uint32x4_t vecIn1 = vldrwq_u32((uint32_t const *) pDataSrc);
    uint32x4_t vecIn2 = vldrwq_u32((uint32_t const *) &pDataSrc[4]);

    vstrwq_scatter_shifted_offset_u32(pDataDest, vecOffs1, vecIn1);
    vstrwq_scatter_shifted_offset_u32(pDataDest, vecOffs2, vecIn2);

    pDataDest[8] = pDataSrc[8];

    return (ARM_MATH_SUCCESS);
}

__STATIC_INLINE arm_status arm_mat_trans_32bit_4x4_mve(uint32_t * pDataSrc, uint32_t * pDataDest)
{
    /*
     * 4x4 Matrix transposition
     * is 4 x de-interleave operation
     *
     * 0   1   2   3       0   4   8   12
     * 4   5   6   7       1   5   9   13
     * 8   9   10  11      2   6   10  14
     * 12  13  14  15      3   7   11  15
     */

    uint32x4x4_t vecIn;

    vecIn = vld4q((uint32_t const *) pDataSrc);
    vstrwq(pDataDest, vecIn.val[0]);
    pDataDest += 4;
    vstrwq(pDataDest, vecIn.val[1]);
    pDataDest += 4;
    vstrwq(pDataDest, vecIn.val[2]);
    pDataDest += 4;
    vstrwq(pDataDest, vecIn.val[3]);

    return (ARM_MATH_SUCCESS);
}


__STATIC_INLINE arm_status arm_mat_trans_32bit_generic_mve(
    uint16_t    srcRows,
    uint16_t    srcCols,
    uint32_t  * pDataSrc,
    uint32_t  * pDataDest)
{
    uint32x4_t vecOffs;
    uint32_t  i;
    uint32_t  blkCnt;
    uint32_t const *pDataC;
    uint32_t *pDataDestR;
    uint32x4_t vecIn;

    vecOffs = vidupq_u32((uint32_t)0, 1);
    vecOffs = vecOffs * srcCols;

    i = srcCols;
    do
    {
        pDataC = (uint32_t const *) pDataSrc;
        pDataDestR = pDataDest;

        blkCnt = srcRows >> 2;
        while (blkCnt > 0U)
        {
            vecIn = vldrwq_gather_shifted_offset_u32(pDataC, vecOffs);
            vstrwq(pDataDestR, vecIn);
            pDataDestR += 4;
            pDataC = pDataC + srcCols * 4;
            /*
             * Decrement the blockSize loop counter
             */
            blkCnt--;
        }

        /*
         * tail
         */
        blkCnt = srcRows & 3;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp32q(blkCnt);
            vecIn = vldrwq_gather_shifted_offset_u32(pDataC, vecOffs);
            vstrwq_p(pDataDestR, vecIn, p0);
        }

        pDataSrc += 1;
        pDataDest += srcRows;
    }
    while (--i);

    return (ARM_MATH_SUCCESS);
}

__STATIC_INLINE arm_status arm_mat_cmplx_trans_32bit(
    uint16_t    srcRows,
    uint16_t    srcCols,
    uint32_t   *pDataSrc,
    uint16_t    dstRows,
    uint16_t    dstCols,
    uint32_t   *pDataDest)
{
    uint32_t        i;
    uint32_t const *pDataC;
    uint32_t       *pDataRow;
    uint32_t       *pDataDestR, *pDataDestRow;
    uint32x4_t      vecOffsRef, vecOffsCur;
    uint32_t        blkCnt;
    uint32x4_t      vecIn;

#ifdef ARM_MATH_MATRIX_CHECK
    /*
     * Check for matrix mismatch condition
     */
    if ((srcRows != dstCols) || (srcCols != dstRows))
    {
        /*
         * Set status as ARM_MATH_SIZE_MISMATCH
         */
        return ARM_MATH_SIZE_MISMATCH;
    }
#else
    (void)dstRows;
    (void)dstCols;
#endif

    /* 2x2, 3x3 and 4x4 specialization to be added */

    vecOffsRef[0] = 0;
    vecOffsRef[1] = 1;
    vecOffsRef[2] = srcCols << 1;
    vecOffsRef[3] = (srcCols << 1) + 1;

    pDataRow = pDataSrc;
    pDataDestRow = pDataDest;
    i = srcCols;
    do
    {
        pDataC = (uint32_t const *) pDataRow;
        pDataDestR = pDataDestRow;
        vecOffsCur = vecOffsRef;

        blkCnt = (srcRows * CMPLX_DIM) >> 2;
        while (blkCnt > 0U)
        {
            vecIn = vldrwq_gather_shifted_offset(pDataC, vecOffsCur);
            vstrwq(pDataDestR, vecIn);
            pDataDestR += 4;
            vecOffsCur = vaddq(vecOffsCur, (srcCols << 2));
            /*
             * Decrement the blockSize loop counter
             */
             blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = (srcRows * CMPLX_DIM) & 3;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp32q(blkCnt);
            vecIn = vldrwq_gather_shifted_offset(pDataC, vecOffsCur);
            vstrwq_p(pDataDestR, vecIn, p0);
        }

        pDataRow += CMPLX_DIM;
        pDataDestRow += (srcRows * CMPLX_DIM);
    }
    while (--i);

    return (ARM_MATH_SUCCESS);
}

__STATIC_INLINE arm_status arm_mat_trans_16bit_2x2(uint16_t * pDataSrc, uint16_t * pDataDest)
{
    pDataDest[0] = pDataSrc[0];
    pDataDest[3] = pDataSrc[3];
    pDataDest[2] = pDataSrc[1];
    pDataDest[1] = pDataSrc[2];

    return (ARM_MATH_SUCCESS);
}

__STATIC_INLINE arm_status arm_mat_trans_16bit_3x3_mve(uint16_t * pDataSrc, uint16_t * pDataDest)
{
    static const uint16_t stridesTr33[8] = { 0, 3, 6, 1, 4, 7, 2, 5 };
    uint16x8_t    vecOffs1;
    uint16x8_t    vecIn1;
    /*
     *
     *  | 0   1   2 |       | 0   3   6 |  8 x 16 flattened version | 0   3   6   1   4   7   2   5 |
     *  | 3   4   5 | =>    | 1   4   7 |            =>             | 8   .   .   .   .   .   .   . |
     *  | 6   7   8 |       | 2   5   8 |       (row major)
     *
     */
    vecOffs1 = vldrhq_u16((uint16_t const *) stridesTr33);
    vecIn1 = vldrhq_u16((uint16_t const *) pDataSrc);

    vstrhq_scatter_shifted_offset_u16(pDataDest, vecOffs1, vecIn1);

    pDataDest[8] = pDataSrc[8];

    return (ARM_MATH_SUCCESS);
}


__STATIC_INLINE arm_status arm_mat_trans_16bit_4x4_mve(uint16_t * pDataSrc, uint16_t * pDataDest)
{
    static const uint16_t stridesTr44_1[8] = { 0, 4, 8, 12, 1, 5, 9, 13 };
    static const uint16_t stridesTr44_2[8] = { 2, 6, 10, 14, 3, 7, 11, 15 };
    uint16x8_t    vecOffs1, vecOffs2;
    uint16x8_t    vecIn1, vecIn2;
    uint16_t const * pDataSrcVec = (uint16_t const *) pDataSrc;

    /*
     * 4x4 Matrix transposition
     *
     * | 0   1   2   3  |       | 0   4   8   12 |   8 x 16 flattened version
     * | 4   5   6   7  |  =>   | 1   5   9   13 |   =>      [0   4   8   12  1   5   9   13]
     * | 8   9   10  11 |       | 2   6   10  14 |           [2   6   10  14  3   7   11  15]
     * | 12  13  14  15 |       | 3   7   11  15 |
     */

    vecOffs1 = vldrhq_u16((uint16_t const *) stridesTr44_1);
    vecOffs2 = vldrhq_u16((uint16_t const *) stridesTr44_2);
    vecIn1 = vldrhq_u16(pDataSrcVec);
    pDataSrcVec += 8;
    vecIn2 = vldrhq_u16(pDataSrcVec);

    vstrhq_scatter_shifted_offset_u16(pDataDest, vecOffs1, vecIn1);
    vstrhq_scatter_shifted_offset_u16(pDataDest, vecOffs2, vecIn2);


    return (ARM_MATH_SUCCESS);
}



__STATIC_INLINE arm_status arm_mat_trans_16bit_generic(
    uint16_t    srcRows,
    uint16_t    srcCols,
    uint16_t  * pDataSrc,
    uint16_t  * pDataDest)
{
    uint16x8_t    vecOffs;
    uint32_t        i;
    uint32_t        blkCnt;
    uint16_t const *pDataC;
    uint16_t       *pDataDestR;
    uint16x8_t    vecIn;

    vecOffs = vidupq_u16((uint32_t)0, 1);
    vecOffs = vecOffs * srcCols;

    i = srcCols;
    while(i > 0U)
    {
        pDataC = (uint16_t const *) pDataSrc;
        pDataDestR = pDataDest;

        blkCnt = srcRows >> 3;
        while (blkCnt > 0U)
        {
            vecIn = vldrhq_gather_shifted_offset_u16(pDataC, vecOffs);
            vstrhq_u16(pDataDestR, vecIn);
            pDataDestR += 8;
            pDataC = pDataC + srcCols * 8;
            /*
             * Decrement the blockSize loop counter
             */
            blkCnt--;
        }

        /*
         * tail
         */
        blkCnt = srcRows & 7;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(blkCnt);
            vecIn = vldrhq_gather_shifted_offset_u16(pDataC, vecOffs);
            vstrhq_p_u16(pDataDestR, vecIn, p0);
        }
        pDataSrc += 1;
        pDataDest += srcRows;
        i--;
    }

    return (ARM_MATH_SUCCESS);
}


__STATIC_INLINE arm_status arm_mat_cmplx_trans_16bit(
    uint16_t    srcRows,
    uint16_t    srcCols,
    uint16_t   *pDataSrc,
    uint16_t    dstRows,
    uint16_t    dstCols,
    uint16_t   *pDataDest)
{
    static const uint16_t loadCmplxCol[8] = { 0, 0, 1, 1, 2, 2, 3, 3 };
    int             i;
    uint16x8_t    vecOffsRef, vecOffsCur;
    uint16_t const *pDataC;
    uint16_t       *pDataRow;
    uint16_t       *pDataDestR, *pDataDestRow;
    uint32_t        blkCnt;
    uint16x8_t    vecIn;

#ifdef ARM_MATH_MATRIX_CHECK
    /*
     * Check for matrix mismatch condition
     */
    if ((srcRows != dstCols) || (srcCols != dstRows))
    {
        /*
         * Set status as ARM_MATH_SIZE_MISMATCH
         */
        return ARM_MATH_SIZE_MISMATCH;
    }
#else
    (void)dstRows;
    (void)dstCols;
#endif

    /*
     * 2x2, 3x3 and 4x4 specialization to be added
     */


    /*
     * build  [0, 1, 2xcol, 2xcol+1, 4xcol, 4xcol+1, 6xcol, 6xcol+1]
     */
    vecOffsRef = vldrhq_u16((uint16_t const *) loadCmplxCol);
    vecOffsRef = vmulq(vecOffsRef, (uint16_t) (srcCols * CMPLX_DIM))
                    + viwdupq_u16((uint32_t)0, (uint16_t) 2, 1);

    pDataRow = pDataSrc;
    pDataDestRow = pDataDest;
    i = srcCols;
    do
    {
        pDataC = (uint16_t const *) pDataRow;
        pDataDestR = pDataDestRow;
        vecOffsCur = vecOffsRef;

        blkCnt = (srcRows * CMPLX_DIM) >> 3;
        while (blkCnt > 0U)
        {
            vecIn = vldrhq_gather_shifted_offset(pDataC, vecOffsCur);
            vstrhq(pDataDestR, vecIn);
            pDataDestR+= 8; // VEC_LANES_U16
            vecOffsCur = vaddq(vecOffsCur, (srcCols << 3));
            /*
             * Decrement the blockSize loop counter
             */
            blkCnt--;
        }
        /*
         * tail
         * (will be merged thru tail predication)
         */
        blkCnt = (srcRows * CMPLX_DIM) & 0x7;
        if (blkCnt > 0U)
        {
            mve_pred16_t p0 = vctp16q(blkCnt);
            vecIn = vldrhq_gather_shifted_offset(pDataC, vecOffsCur);
            vstrhq_p(pDataDestR, vecIn, p0);
        }

        pDataRow += CMPLX_DIM;
        pDataDestRow += (srcRows * CMPLX_DIM);
    }
    while (--i);

    return (ARM_MATH_SUCCESS);
}
#endif /* MVEF and MVEI */

/***************************************

Definitions available for MVEI only

***************************************/
#if (defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEI))  && !defined(ARM_MATH_AUTOVECTORIZE)

#include "arm_common_tables.h"

#define MVE_ASRL_SAT16(acc, shift)          ((sqrshrl_sat48(acc, -(32-shift)) >> 32) & 0xffffffff)
#define MVE_ASRL_SAT32(acc, shift)          ((sqrshrl(acc, -(32-shift)) >> 32) & 0xffffffff)


#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q31_MVE)
__STATIC_INLINE q31x4_t FAST_VSQRT_Q31(q31x4_t vecIn)
{
    q63x2_t         vecTmpLL;
    q31x4_t         vecTmp0, vecTmp1;
    q31_t           scale;
    q63_t           tmp64;
    q31x4_t         vecNrm, vecDst, vecIdx, vecSignBits;


    vecSignBits = vclsq(vecIn);
    vecSignBits = vbicq_n_s32(vecSignBits, 1);
    /*
     * in = in << no_of_sign_bits;
     */
    vecNrm = vshlq(vecIn, vecSignBits);
    /*
     * index = in >> 24;
     */
    vecIdx = vecNrm >> 24;
    vecIdx = vecIdx << 1;

    vecTmp0 = vldrwq_gather_shifted_offset_s32(sqrtTable_Q31, (uint32x4_t)vecIdx);

    vecIdx = vecIdx + 1;

    vecTmp1 = vldrwq_gather_shifted_offset_s32(sqrtTable_Q31, (uint32x4_t)vecIdx);

    vecTmp1 = vqrdmulhq(vecTmp1, vecNrm);
    vecTmp0 = vecTmp0 - vecTmp1;
    vecTmp1 = vqrdmulhq(vecTmp0, vecTmp0);
    vecTmp1 = vqrdmulhq(vecNrm, vecTmp1);
    vecTmp1 = vdupq_n_s32(0x18000000) - vecTmp1;
    vecTmp0 = vqrdmulhq(vecTmp0, vecTmp1);
    vecTmpLL = vmullbq_int(vecNrm, vecTmp0);

    /*
     * scale elements 0, 2
     */
    scale = 26 + (vecSignBits[0] >> 1);
    tmp64 = asrl(vecTmpLL[0], scale);
    vecDst[0] = (q31_t) tmp64;

    scale = 26 + (vecSignBits[2] >> 1);
    tmp64 = asrl(vecTmpLL[1], scale);
    vecDst[2] = (q31_t) tmp64;

    vecTmpLL = vmulltq_int(vecNrm, vecTmp0);

    /*
     * scale elements 1, 3
     */
    scale = 26 + (vecSignBits[1] >> 1);
    tmp64 = asrl(vecTmpLL[0], scale);
    vecDst[1] = (q31_t) tmp64;

    scale = 26 + (vecSignBits[3] >> 1);
    tmp64 = asrl(vecTmpLL[1], scale);
    vecDst[3] = (q31_t) tmp64;
    /*
     * set negative values to 0
     */
    vecDst = vdupq_m(vecDst, 0, vcmpltq_n_s32(vecIn, 0));

    return vecDst;
}
#endif

#if !defined(ARM_DSP_CONFIG_TABLES) || defined(ARM_ALL_FAST_TABLES) || defined(ARM_TABLE_FAST_SQRT_Q15_MVE)
__STATIC_INLINE q15x8_t FAST_VSQRT_Q15(q15x8_t vecIn)
{
    q31x4_t         vecTmpLev, vecTmpLodd, vecSignL;
    q15x8_t         vecTmp0, vecTmp1;
    q15x8_t         vecNrm, vecDst, vecIdx, vecSignBits;

    vecDst = vuninitializedq_s16();

    vecSignBits = vclsq(vecIn);
    vecSignBits = vbicq_n_s16(vecSignBits, 1);
    /*
     * in = in << no_of_sign_bits;
     */
    vecNrm = vshlq(vecIn, vecSignBits);

    vecIdx = vecNrm >> 8;
    vecIdx = vecIdx << 1;

    vecTmp0 = vldrhq_gather_shifted_offset_s16(sqrtTable_Q15, (uint16x8_t)vecIdx);

    vecIdx = vecIdx + 1;

    vecTmp1 = vldrhq_gather_shifted_offset_s16(sqrtTable_Q15, (uint16x8_t)vecIdx);

    vecTmp1 = vqrdmulhq(vecTmp1, vecNrm);
    vecTmp0 = vecTmp0 - vecTmp1;
    vecTmp1 = vqrdmulhq(vecTmp0, vecTmp0);
    vecTmp1 = vqrdmulhq(vecNrm, vecTmp1);
    vecTmp1 = vdupq_n_s16(0x1800) - vecTmp1;
    vecTmp0 = vqrdmulhq(vecTmp0, vecTmp1);

    vecSignBits = vecSignBits >> 1;

    vecTmpLev = vmullbq_int(vecNrm, vecTmp0);
    vecTmpLodd = vmulltq_int(vecNrm, vecTmp0);

    vecTmp0 = vecSignBits + 10;
    /*
     * negate sign to apply register based vshl
     */
    vecTmp0 = -vecTmp0;

    /*
     * shift even elements
     */
    vecSignL = vmovlbq(vecTmp0);
    vecTmpLev = vshlq(vecTmpLev, vecSignL);
    /*
     * shift odd elements
     */
    vecSignL = vmovltq(vecTmp0);
    vecTmpLodd = vshlq(vecTmpLodd, vecSignL);
    /*
     * merge and narrow odd and even parts
     */
    vecDst = vmovnbq_s32(vecDst, vecTmpLev);
    vecDst = vmovntq_s32(vecDst, vecTmpLodd);
    /*
     * set negative values to 0
     */
    vecDst = vdupq_m(vecDst, 0, vcmpltq_n_s16(vecIn, 0));

    return vecDst;
}
#endif

#endif /* defined (ARM_MATH_HELIUM) || defined(ARM_MATH_MVEI) */

#ifdef   __cplusplus
}
#endif

#endif
