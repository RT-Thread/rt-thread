#ifndef __MATRIX_H__
#define __MATRIX_H__

/* Port from ejoy2d: https://github.com/cloudwu/ejoy2d/blob/master/LICENSE
 * Original License:
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Ejoy.com Inc.
 *
 * Permission is hereby granted,  free of charge,  to any person obtaining a copy of
 * this software and associated documentation files (the "Software"),  to deal in
 * the Software without restriction,  including without limitation the rights to
 * use,  copy,  modify,  merge,  publish,  distribute,  sublicense,  and/or sell copies of
 * the Software,  and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR
 * IMPLIED,  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY,  WHETHER
 * IN AN ACTION OF CONTRACT,  TORT OR OTHERWISE,  ARISING FROM,  OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Port to RTGUI and modified by Grissiom */

#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#define RTGUI_MATRIX_FRAC_BITS   11
#define RTGUI_MATRIX_FRAC      (1 << RTGUI_MATRIX_FRAC_BITS)

struct rtgui_matrix
{
    /* The matrix format is :
     *
     * | m[0] m[1] 0 |
     * | m[2] m[3] 0 |
     * | m[4] m[5] 1 |
     *
     * The format of the coordinate of a point is:
     *
     * | x y 1 |
     *
     * So, if you want to transform a point p with a matrix m, do:
     *
     * p * m
     *
     * Note: m[0-3] is in fix presentation that has 10 bits decimal
     * fraction(m/RTGUI_MATRIX_FRAC). While the unit of m[4-5] is pixel.
     *
     */
	int m[6];
};

rt_inline int32_t _rtgui_matrix_round_div32(int32_t n, int32_t d)
{
    if (n == 0)
        return 0;

    if (d < 0)
    {
        d = -d;
        n = -n;
    }
    if (n > 0)
        return (n + d / 2) / d;
    else
        return (n - d / 2) / d;
}

rt_inline int32_t _rtgui_matrix_round_div6432(int64_t n, int32_t d)
{
    if (n == 0)
        return 0;

    if (d < 0)
    {
        d = -d;
        n = -n;
    }
    if (n > 0)
        return (n + d / 2) / d;
    else
        return (n - d / 2) / d;
}

/* mm = mm1 * mm2 */
rt_inline void rtgui_matrix_mul(struct rtgui_matrix *mm,
                                const struct rtgui_matrix *mm1,
                                const struct rtgui_matrix *mm2)
{
	int *m = mm->m;
	const int *m1 = mm1->m;
	const int *m2 = mm2->m;

	m[0] = _rtgui_matrix_round_div32(m1[0] * m2[0] + m1[1] * m2[2], RTGUI_MATRIX_FRAC);
	m[1] = _rtgui_matrix_round_div32(m1[0] * m2[1] + m1[1] * m2[3], RTGUI_MATRIX_FRAC);
	m[2] = _rtgui_matrix_round_div32(m1[2] * m2[0] + m1[3] * m2[2], RTGUI_MATRIX_FRAC);
	m[3] = _rtgui_matrix_round_div32(m1[2] * m2[1] + m1[3] * m2[3], RTGUI_MATRIX_FRAC);
	m[4] = _rtgui_matrix_round_div32(m1[4] * m2[0] + m1[5] * m2[2], RTGUI_MATRIX_FRAC) + m2[4];
	m[5] = _rtgui_matrix_round_div32(m1[4] * m2[1] + m1[5] * m2[3], RTGUI_MATRIX_FRAC) + m2[5];
}

/* Matrix multiply point[(p) = (x, y) * m], ignore the movement components. */
rt_inline void rtgui_matrix_mul_point_nomove(struct rtgui_point *p,
                                             int x, int y,
                                             struct rtgui_matrix *m)
{
    int *mm = m->m;

    p->x = _rtgui_matrix_round_div32(x * mm[0] + y * mm[2], RTGUI_MATRIX_FRAC);
    p->y = _rtgui_matrix_round_div32(x * mm[1] + y * mm[3], RTGUI_MATRIX_FRAC);
}

/* Matrix multiply point[(p) = (x, y) * m]. */
rt_inline void rtgui_matrix_mul_point(struct rtgui_point *p,
                                      int x, int y,
                                      struct rtgui_matrix *m)
{
    int *mm = m->m;

    p->x = _rtgui_matrix_round_div32(x * mm[0] + y * mm[2], RTGUI_MATRIX_FRAC) + mm[4];
    p->y = _rtgui_matrix_round_div32(x * mm[1] + y * mm[3], RTGUI_MATRIX_FRAC) + mm[5];
}

/** Set @mm to an identity matrix. */
rt_inline void rtgu_matrix_identity(struct rtgui_matrix *mm)
{
	int *mat = mm->m;
	mat[0] = RTGUI_MATRIX_FRAC;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = RTGUI_MATRIX_FRAC;
	mat[4] = 0;
	mat[5] = 0;
}

/** Save the inversed matrix of @mm to @mo.
 *
 * @return If the matrix is not inversale, return 1. Otherwise, return 0. */
int rtgui_matrix_inverse(const struct rtgui_matrix *mm, struct rtgui_matrix *mo);

/** @degree range from 0 ~ 512. */
void rtgui_matrix_rotate(struct rtgui_matrix *m, int degree);
/** The unit is fixed point number. RTGUI_MATRIX_FRAC means 1.0. */
void rtgui_matrix_scale(struct rtgui_matrix *m, int sx, int sy);
/** The unit is pixel. Not the fixed point number. */
void rtgui_matrix_move(struct rtgui_matrix *m, int dx, int dy);

#endif /* end of include guard: __MATRIX_H__ */

