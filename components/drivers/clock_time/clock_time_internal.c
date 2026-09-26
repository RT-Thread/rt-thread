/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2025-09-25     Yonggang Luo  the first version
 * 2026-07-14     Yonggang Luo  keep muldiv private to clock_time
 */

#include "clock_time_internal.h"

/**
 * @brief Count leading zero bits in a 64-bit value.
 *
 * @param n Input value.
 *
 * @return Number of leading zero bits; 64 when @p n is 0.
 */
static rt_int32_t _u64_count_leading_zeros(rt_uint64_t n)
{
    if (n == 0)
    {
        return 64;
    }
#ifdef __GNUC__
    return __builtin_clzll(n);
#else
    rt_int32_t count = 0;
    rt_uint64_t mask = 1ULL << (sizeof(rt_uint64_t) * 8 - 1);

    while ((n & mask) == 0)
    {
        count++;
        mask >>= 1;
    }
    return count;
#endif
}

/**
 * @brief Narrowing division of a 128-bit numerator by a 64-bit denominator.
 *
 * Algorithm from:
 * https://ridiculousfish.com/blog/posts/labor-of-division-episode-v.html
 *
 * The dividend is formed by high word @p numhi and low word @p numlo.
 * When @p den is 0, both the quotient and the optional remainder are 0 and
 * @p overflow is set. When the full quotient needs more than 64 bits,
 * @c numhi %= den truncates to a 64-bit quotient and @p overflow is set.
 *
 * These functions are released into the public domain, where applicable, or
 * the CC0 license.
 *
 * @param numhi    High 64 bits of the numerator.
 * @param numlo    Low 64 bits of the numerator.
 * @param den      Denominator.
 * @param r        Optional remainder output; may be @c RT_NULL.
 * @param overflow Optional overflow flag; may be @c RT_NULL.
 *
 * @return The truncated 64-bit quotient.
 */
static rt_uint64_t _u128_div_u64_u64(rt_uint64_t numhi, rt_uint64_t numlo, rt_uint64_t den,
                                     rt_uint64_t *r, rt_bool_t *overflow)
{
    /*
     * We work in base 2**32.
     * A uint32 holds a single digit. A uint64 holds two digits.
     * Our numerator is conceptually [num3, num2, num1, num0].
     * Our denominator is [den1, den0].
     */
    const rt_uint64_t b = (1ull << 32);

    /* The high and low digits of our computed quotient. */
    rt_uint32_t q1;
    rt_uint32_t q0;

    /* The normalization shift factor. */
    rt_int32_t shift;

    /*
     * The high and low digits of our denominator (after normalizing).
     * Also the low 2 digits of our numerator (after normalizing).
     */
    rt_uint32_t den1;
    rt_uint32_t den0;
    rt_uint32_t num1;
    rt_uint32_t num0;

    /* A partial remainder. */
    rt_uint64_t rem;

    /* The estimated quotient, and its corresponding remainder (unrelated to true remainder). */
    rt_uint64_t qhat;
    rt_uint64_t rhat;

    /* Variables used to correct the estimated quotient. */
    rt_uint64_t c1;
    rt_uint64_t c2;

    if (overflow != RT_NULL)
    {
        *overflow = RT_FALSE;
    }

    /* Divide by 0: treat as a zero result. */
    if (den == 0)
    {
        if (r != RT_NULL)
        {
            *r = 0;
        }
        if (overflow != RT_NULL)
        {
            *overflow = RT_TRUE;
        }
        return 0;
    }

    /* Truncate a wider-than-64-bit quotient to 64 bits. */
    if (numhi >= den)
    {
        if (overflow != RT_NULL)
        {
            *overflow = RT_TRUE;
        }
        numhi = numhi % den;
    }

    /*
     * Determine the normalization factor. We multiply den by this, so that its leading digit is at
     * least half b. In binary this means just shifting left by the number of leading zeros, so that
     * there's a 1 in the MSB.
     * We also shift numer by the same amount. This cannot overflow because numhi < den.
     * The expression (-shift & 63) is the same as (64 - shift), except it avoids the UB of shifting
     * by 64. The funny bitwise 'and' ensures that numlo does not get shifted into numhi if shift is 0.
     * clang 11 has an x86 codegen bug here: see LLVM bug 50118. The sequence below avoids it.
     */
    shift = _u64_count_leading_zeros(den);
    den <<= shift;
    numhi <<= shift;
    numhi |= (numlo >> (-shift & 63)) & (-(rt_int64_t)shift >> 63);
    numlo <<= shift;

    /* Extract the low digits of the numerator and both digits of the denominator. */
    num1 = (rt_uint32_t)(numlo >> 32);
    num0 = (rt_uint32_t)(numlo & 0xFFFFFFFFu);
    den1 = (rt_uint32_t)(den >> 32);
    den0 = (rt_uint32_t)(den & 0xFFFFFFFFu);

    /*
     * We wish to compute q1 = [n3 n2 n1] / [d1 d0].
     * Estimate q1 as [n3 n2] / [d1], and then correct it.
     * Note while qhat may be 2 digits, q1 is always 1 digit.
     */
    qhat = numhi / den1;
    rhat = numhi % den1;
    c1 = qhat * den0;
    c2 = rhat * b + num1;
    if (c1 > c2)
        qhat -= (c1 - c2 > den) ? 2 : 1;
    q1 = (rt_uint32_t)qhat;

    /* Compute the true (partial) remainder. */
    rem = numhi * b + num1 - q1 * den;

    /*
     * We wish to compute q0 = [rem1 rem0 n0] / [d1 d0].
     * Estimate q0 as [rem1 rem0] / [d1] and correct it.
     */
    qhat = rem / den1;
    rhat = rem % den1;
    c1 = qhat * den0;
    c2 = rhat * b + num0;
    if (c1 > c2)
        qhat -= (c1 - c2 > den) ? 2 : 1;
    q0 = (rt_uint32_t)qhat;

    /* Return remainder if requested. */
    if (r != RT_NULL)
        *r = (rem * b + num0 - q0 * den) >> shift;
    return ((rt_uint64_t)q1 << 32) | q0;
}

rt_uint64_t rt_clock_time_muldiv_u64(rt_uint64_t a, rt_uint64_t b, rt_uint64_t c,
                                     rt_uint64_t *r, rt_bool_t *overflow)
{
    rt_uint64_t remainder = 0;
    rt_uint64_t ret;

    if (c == 0)
    {
        if (r != RT_NULL)
        {
            *r = 0;
        }
        if (overflow != RT_NULL)
        {
            *overflow = RT_TRUE;
        }
        return 0;
    }

    {
        rt_uint64_t a_lo = a & 0xFFFFFFFF;
        rt_uint64_t a_hi = a >> 32;
        rt_uint64_t b_lo = b & 0xFFFFFFFF;
        rt_uint64_t b_hi = b >> 32;

        /* Perform partial products */
        rt_uint64_t p0 = a_lo * b_lo;
        rt_uint64_t p1 = a_lo * b_hi;
        rt_uint64_t p2 = a_hi * b_lo;
        rt_uint64_t p3 = a_hi * b_hi;

        rt_uint64_t carry = (p0 >> 32) + (p1 & 0xFFFFFFFFULL) + (p2 & 0xFFFFFFFFULL);

        rt_uint64_t lo = (p0 & 0xFFFFFFFFULL) + ((carry & 0xFFFFFFFFULL) << 32);
        rt_uint64_t hi = p3 + (p1 >> 32) + (p2 >> 32) + (carry >> 32);
        ret = _u128_div_u64_u64(hi, lo, c, &remainder, overflow);
    }

    if (r != RT_NULL)
    {
        *r = remainder;
    }
    return ret;
}
