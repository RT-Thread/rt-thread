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
#ifndef __CLOCK_TIME_INTERNAL_H__
#define __CLOCK_TIME_INTERNAL_H__

#include <rtdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute (a * b) / c with 128-bit intermediate precision.
 *
 * Pure arithmetic helper. When @p c is 0, returns 0 and sets @p overflow
 * (if not @c RT_NULL). When the mathematical quotient does not fit in 64
 * bits, the high part of the 128-bit product is reduced so the returned
 * value is the truncated low 64-bit quotient, and @p overflow is set.
 *
 * Callers that need wrap, clamp, or error semantics must inspect @p overflow
 * and apply that policy themselves.
 *
 * If @p r is not @c RT_NULL, @c *r receives the remainder of the reduced
 * division, or 0 when @p c is 0.
 *
 * @param a         Multiplicand.
 * @param b         Multiplier.
 * @param c         Divisor.
 * @param r         Optional remainder output; may be @c RT_NULL.
 * @param overflow  Optional overflow flag; may be @c RT_NULL. Set to
 *                  @c RT_TRUE when @p c is 0 or the quotient needs more
 *                  than 64 bits; otherwise @c RT_FALSE.
 *
 * @return The truncated 64-bit quotient of (a * b) / c.
 */
rt_uint64_t rt_clock_time_muldiv_u64(rt_uint64_t a, rt_uint64_t b, rt_uint64_t c,
                                     rt_uint64_t *r, rt_bool_t *overflow);

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_TIME_INTERNAL_H__ */
