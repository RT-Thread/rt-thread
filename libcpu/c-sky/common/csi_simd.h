/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_simd.h
 * @brief    CSI Single Instruction Multiple Data (SIMD) Header File for GCC.
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_SIMD_H_
#define _CSI_SIMD_H_

/**
  \brief   Halfword packing instruction. Combines bits[15:0] of val1 with bits[31:16]
           of val2 levitated with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be left-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for left-shifting val2. Value range [0..31].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val1[15:0]              \n
                 res[31:16] = val2[31:16] << val3
 */
__ALWAYS_INLINE uint32_t __PKHBT(uint32_t val1, uint32_t val2, uint32_t val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0x0000FFFF) | (((int32_t)(val2) << val3) & (int32_t)0xFFFF0000));
}

/**
  \brief   Halfword packing instruction. Combines bits[31:16] of val1 with bits[15:0]
           of val2 right-shifted with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be right-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for right-shifting val2. Value range [1..32].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val2[15:0] >> val3        \n
                 res[31:16] = val1[31:16]
 */
__ALWAYS_INLINE uint32_t __PKHTB(uint32_t val1, uint32_t val2, uint32_t val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0xFFFF0000) | (((int32_t)(val2) >> val3) & (int32_t)0x0000FFFF));
}

/**
  \brief   Dual 16-bit signed saturate.
  \details This function saturates a signed value.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:\n
                 the signed saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the signed saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_INLINE uint32_t __SSAT16(int32_t x, const uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __SSAT((((int32_t)x << 16) >> 16), y) & (int32_t)0x0000FFFF;
    s = __SSAT((((int32_t)x) >> 16), y) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturate.
  \details This function enables you to saturate two signed 16-bit values to a selected unsigned range.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the saturation of the two signed 16-bit values, as non-negative values:
                 the saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_INLINE uint32_t __USAT16(uint32_t x, const uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT(((x << 16) >> 16), y) & 0x0000FFFF;
    s = __IUSAT(((x) >> 16), y) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit saturating addition.
  \details This function enables you to perform four 8-bit integer additions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_INLINE uint32_t __QADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) + (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating addition.
  \details This function enables you to perform four unsigned 8-bit integer additions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_INLINE uint32_t __UQADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) + ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) + ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) + ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) + ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed addition.
  \details This function performs four 8-bit signed integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_INLINE uint32_t __SADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition.
  \details This function performs four unsigned 8-bit integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_INLINE uint32_t __UADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) + ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) + ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) + ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) + ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit saturating subtract.
  \details This function enables you to perform four 8-bit integer subtractions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_INLINE uint32_t __QSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) - (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating subtraction.
  \details This function enables you to perform four unsigned 8-bit integer subtractions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit unsigned integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_INLINE uint32_t __UQSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) - ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) - ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) - ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) - ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed subtraction.
  \details This function enables you to perform four 8-bit signed integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_INLINE uint32_t __SSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtract.
  \details This function enables you to perform four 8-bit unsigned integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_INLINE uint32_t __USUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences together, returning the result as a single unsigned integer.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.\n
                 The sum is returned as a single unsigned integer.
  \remark
                 absdiff1   = val1[7:0]   - val2[7:0]        \n
                 absdiff2   = val1[15:8]  - val2[15:8]       \n
                 absdiff3   = val1[23:16] - val2[23:16]      \n
                 absdiff4   = val1[31:24] - val2[31:24]      \n
                 res[31:0]  = absdiff1 + absdiff2 + absdiff3 + absdiff4
 */
__ALWAYS_INLINE uint32_t __USAD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return (u + t + s + r);
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference with 32-bit accumulate.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences to a 32-bit accumulate operand.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \param [in]  sum  accumulation value.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:
                 the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 absdiff1 = val1[7:0]   - val2[7:0]        \n
                 absdiff2 = val1[15:8]  - val2[15:8]       \n
                 absdiff3 = val1[23:16] - val2[23:16]      \n
                 absdiff4 = val1[31:24] - val2[31:24]      \n
                 sum = absdiff1 + absdiff2 + absdiff3 + absdiff4 \n
                 res[31:0] = sum[31:0] + val3[31:0]
 */
__ALWAYS_INLINE uint32_t __USADA8(uint32_t x, uint32_t y, uint32_t sum)
{
    int32_t r, s, t, u;

    r = (abs(((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs(((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs(((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs(((x) >> 24) - ((y) >> 24))) & 0x000000FF;

    return (u + t + s + r + sum);
}

/**
  \brief   Dual 16-bit saturating addition.
  \details This function enables you to perform two 16-bit integer arithmetic additions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_INLINE uint32_t __QADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition.
  \details This function enables you to perform two unsigned 16-bit integer additions, saturating
           the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The results are saturated to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_INLINE uint32_t __UQADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT((((x << 16) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition.
  \details This function enables you to perform two 16-bit signed integer additions.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_INLINE uint32_t __SADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition
  \details This function enables you to perform two 16-bit unsigned integer additions.
  \param [in]    x   first two 16-bit summands for each addition.
  \param [in]    y   second two 16-bit summands for each addition.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_INLINE uint32_t __UADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = (((x << 16) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}


/**
  \brief   Dual 16-bit signed addition with halved results.
  \details This function enables you to perform two signed 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_INLINE uint32_t __SHADD16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition with halved results.
  \details This function enables you to perform two unsigned 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_INLINE uint32_t __UHADD16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_INLINE uint32_t __SHADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition with halved results.
  \details This function enables you to perform four unsigned 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_INLINE uint32_t __UHADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) + ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) + ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) + ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) + ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit saturating subtract.
  \details This function enables you to perform two 16-bit integer subtractions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_INLINE uint32_t __QSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction.
  \details This function enables you to perform two unsigned 16-bit integer subtractions,
           saturating the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit operands for each subtraction.
  \param [in]    y   second two 16-bit operands for each subtraction.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_INLINE uint32_t __UQSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction.
  \details This function enables you to perform two 16-bit signed integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_INLINE uint32_t __SSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtract.
  \details This function enables you to perform two 16-bit unsigned integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_INLINE uint32_t __USUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction with halved results.
  \details This function enables you to perform two signed 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_INLINE uint32_t __SHSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction with halved results.
  \details This function enables you to perform two unsigned 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_INLINE uint32_t __UHSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_INLINE uint32_t __SHSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtraction with halved results.
  \details This function enables you to perform four unsigned 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_INLINE uint32_t __UHSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) - ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) - ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) - ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) - ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit add and subtract with exchange.
  \details This function enables you to exchange the halfwords of the one operand,
           then add the high halfwords and subtract the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_INLINE uint32_t __QASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition and subtraction with exchange.
  \details This function enables you to exchange the halfwords of the second operand and
           perform one unsigned 16-bit integer addition and one unsigned 16-bit subtraction,
           saturating the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_INLINE uint32_t __UQASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit addition and subtraction with exchange.
  \details It enables you to exchange the halfwords of the second operand, add the high halfwords
           and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_INLINE uint32_t __SASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with exchange.
  \details This function enables you to exchange the two halfwords of the second operand,
           add the high halfwords and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_INLINE uint32_t __UASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition and subtraction with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one
           signed 16-bit integer addition and one signed 16-bit subtraction, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_INLINE uint32_t __SHASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           add the high halfwords and subtract the low halfwords, halving the results.
  \param [in]    x   first operand for the subtraction in the low halfword, and
                     the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword, and
                     the second operand for the addition in the low halfword.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_INLINE uint32_t __UHASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit subtract and add with exchange.
  \details This function enables you to exchange the halfwords of one operand,
           then subtract the high halfwords and add the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_INLINE uint32_t __QSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction and addition with exchange.
  \details This function enables you to exchange the halfwords of the second operand and perform
           one unsigned 16-bit integer subtraction and one unsigned 16-bit addition, saturating
           the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_INLINE uint32_t __UQSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit unsigned subtract and add with exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_INLINE uint32_t __USAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) + ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction and addition with exchange.
  \details This function enables you to exchange the two halfwords of one operand and perform one
           16-bit integer subtraction and one 16-bit addition.
  \param [in]    x   first operand for the addition in the low halfword, and the first operand
                     for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and the second
                     operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_INLINE uint32_t __SSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}


/**
  \brief   Dual 16-bit signed subtraction and addition with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one signed
           16-bit integer subtraction and one signed 16-bit addition, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_INLINE uint32_t __SHSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction and addition with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords, halving the results.
  \param [in]    x   first operand for the addition in the low halfword, and
                     the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and
                     the second operand for the subtraction in the low halfword.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_INLINE uint32_t __UHSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed multiply with exchange returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, subtracting
           one of the products from the other. The halfwords of the second operand are exchanged
           before performing the arithmetic. This produces top * bottom and bottom * top multiplication.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_INLINE uint32_t __SMUSDX(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}

/**
  \brief   Sum of dual 16-bit signed multiply with exchange.
  \details This function enables you to perform two 16-bit signed multiplications with exchanged
           halfwords of the second operand, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications with exchanged halfwords of the second operand.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_INLINE uint32_t __SMUADX(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}


/**
  \brief   Saturating add.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 + SAT(val2))
 */
__ALWAYS_INLINE int32_t __QADD(int32_t x, int32_t y)
{
    int32_t result;

    if (y >= 0)
    {
        if (x + y >= x)
        {
            result = x + y;
        }
        else
        {
            result = 0x7FFFFFFF;
        }
    }
    else
    {
        if (x + y < x)
        {
            result = x + y;
        }
        else
        {
            result = 0x80000000;
        }
    }

    return result;
}

/**
  \brief   Saturating subtract.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 + SAT(val2))
 */
__ALWAYS_INLINE int32_t __QSUB(int32_t x, int32_t y)
{
    int64_t tmp;
    int32_t result;

    tmp = (int64_t)x - (int64_t)y;

    if (tmp > 0x7fffffff)
    {
        tmp = 0x7fffffff;
    }
    else if (tmp < (-2147483647 - 1))
    {
        tmp = -2147483647 - 1;
    }

    result = tmp;
    return result;
}

/**
  \brief   Dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications,
           adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_INLINE uint32_t __SMLAD(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Pre-exchanged dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications with exchanged
           halfwords of the second operand, adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication with exchanged halfwords of the second
                 operand added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_INLINE uint32_t __SMLADX(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to perform two 16-bit signed multiplications, take the
           difference of the products, subtracting the high halfword product from the low
           halfword product, and add the difference to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]       \n
                 p2 = val1[31:16] * val2[31:16]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_INLINE uint32_t __SMLSD(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to exchange the halfwords in the second operand, then perform two 16-bit
           signed multiplications. The difference of the products is added to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_INLINE uint32_t __SMLSDX(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with single 64-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications, adding both results
           to a 64-bit accumulate operand. Overflow is only possible as a result of the 64-bit addition.
           This overflow is not detected if it occurs. Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_INLINE uint64_t __SMLALD(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange with single 64-bit accumulator.
  \details This function enables you to exchange the halfwords of the second operand, and perform two
           signed 16-bit multiplications, adding both results to a 64-bit accumulate operand. Overflow
           is only possible as a result of the 64-bit addition. This overflow is not detected if it occurs.
           Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_INLINE uint64_t __SMLALDX(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   dual 16-bit signed multiply subtract with 64-bit accumulate.
  \details This function It enables you to perform two 16-bit signed multiplications, take the difference
           of the products, subtracting the high halfword product from the low halfword product, and add the
           difference to a 64-bit accumulate operand. Overflow cannot occur during the multiplications or the
           subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow is not
           detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[63:0] = p1 - p2 + val3[63:0]
 */
__ALWAYS_INLINE uint64_t __SMLSLD(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 64-bit accumulate.
  \details This function enables you to exchange the halfwords of the second operand, perform two 16-bit multiplications,
           adding the difference of the products to a 64-bit accumulate operand. Overflow cannot occur during the
           multiplications or the subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow
           is not detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]      \n
                 p2 = val1[31:16] * val2[15:0]       \n
                 res[63:0] = p1 - p2 + val3[63:0]
 */
__ALWAYS_INLINE uint64_t __SMLSLDX(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   32-bit signed multiply with 32-bit truncated accumulator.
  \details This function enables you to perform a signed 32-bit multiplications, adding the most
           significant 32 bits of the 64-bit result to a 32-bit accumulate operand.
  \param [in]    x   first operand for multiplication.
  \param [in]    y   second operand for multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of multiplication (most significant 32 bits) is added to the accumulate value, as a 32-bit integer.
  \remark
                 p = val1 * val2      \n
                 res[31:0] = p[61:32] + val3[31:0]
 */
__ALWAYS_INLINE uint32_t __SMMLA(int32_t x, int32_t y, int32_t sum)
{
    return (uint32_t)((int32_t)((int64_t)((int64_t)x * (int64_t)y) >> 32) + sum);
}

/**
  \brief   Sum of dual 16-bit signed multiply.
  \details This function enables you to perform two 16-bit signed multiplications, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_INLINE uint32_t __SMUAD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual 16-bit signed multiply returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, taking the difference
           of the products by subtracting the high halfword product from the low halfword product.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_INLINE uint32_t __SMUSD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual extracted 8-bit to 16-bit signed addition.
  \details This function enables you to extract two 8-bit values from the second operand (at bit positions
           [7:0] and [23:16]), sign-extend them to 16-bits each, and add the results to the first operand.
  \param [in]    x   values added to the sign-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and sign-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and sign-extended prior to the addition.
  \remark
                 res[15:0]  = val1[15:0] + SignExtended(val2[7:0])      \n
                 res[31:16] = val1[31:16] + SignExtended(val2[23:16])
 */
__ALWAYS_INLINE uint32_t __SXTAB16(uint32_t x, uint32_t y)
{
    return ((uint32_t)((((((int32_t)y << 24) >> 24) + (((int32_t)x << 16) >> 16)) & (int32_t)0x0000FFFF) |
                       (((((int32_t)y <<  8) >>  8)  + (((int32_t)x >> 16) << 16)) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Extracted 16-bit to 32-bit unsigned addition.
  \details This function enables you to extract two 8-bit values from one operand, zero-extend
           them to 16 bits each, and add the results to two 16-bit values from another operand.
  \param [in]    x   values added to the zero-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and zero-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and zero-extended prior to the addition.
  \remark
                 res[15:0]  = ZeroExt(val2[7:0]   to 16 bits) + val1[15:0]      \n
                 res[31:16] = ZeroExt(val2[31:16] to 16 bits) + val1[31:16]
 */
__ALWAYS_INLINE uint32_t __UXTAB16(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((y << 24) >> 24) + ((x << 16) >> 16)) & 0x0000FFFF) |
                       ((((y <<  8) >>  8) + ((x >> 16) << 16)) & 0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and sign extend each to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and sign-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be sign-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_INLINE uint32_t __SXTB16(uint32_t x)
{
    return ((uint32_t)(((((int32_t)x << 24) >> 24) & (int32_t)0x0000FFFF) |
                       ((((int32_t)x <<  8) >>  8) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and zero-extend to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and zero-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be zero-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_INLINE uint32_t __UXTB16(uint32_t x)
{
    return ((uint32_t)((((x << 24) >> 24) & 0x0000FFFF) |
                       (((x <<  8) >>  8) & 0xFFFF0000)));
}

#endif /* _CSI_SIMD_H_ */
