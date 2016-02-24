#include <rtgui/rtgui.h>
#include <rtgui/matrix.h>

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

/* Port to RTGUI by Grissiom */

rt_inline int _inverse_scale(const int *m , int *o)
{
    if (m[0] == 0 || m[3] == 0)
        return 1;

    o[0] = _rtgui_matrix_round_div32(RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC, m[0]);
    o[1] = 0;
    o[2] = 0;
    o[3] = _rtgui_matrix_round_div32(RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC, m[3]);
    o[4] = _rtgui_matrix_round_div32(-m[4] * o[0], RTGUI_MATRIX_FRAC);
    o[5] = _rtgui_matrix_round_div32(-m[5] * o[3], RTGUI_MATRIX_FRAC);

    return 0;
}

rt_inline int _inverse_rot(const int *m, int *o)
{
    if (m[1] == 0 || m[2] == 0)
        return 1;

    o[0] = 0;
    o[1] = _rtgui_matrix_round_div32(RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC, m[2]);
    o[2] = _rtgui_matrix_round_div32(RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC, m[1]);
    o[3] = 0;
    o[4] = _rtgui_matrix_round_div32(-m[5] * o[2], RTGUI_MATRIX_FRAC);
    o[5] = _rtgui_matrix_round_div32(-m[4] * o[1], RTGUI_MATRIX_FRAC);

    return 0;
}

int rtgui_matrix_inverse(const struct rtgui_matrix *mm, struct rtgui_matrix *mo)
{
    const int *m = mm->m;
    int *o = mo->m;
    int t;

    if (m[1] == 0 && m[2] == 0)
    {
        return _inverse_scale(m,o);
    }
    if (m[0] == 0 && m[3] == 0)
    {
        return _inverse_rot(m,o);
    }

    t = m[0] * m[3] - m[1] * m[2];
    if (t == 0)
        return 1;

    o[0] = _rtgui_matrix_round_div6432((int64_t)m[3] * (RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC), t);
    o[1] = _rtgui_matrix_round_div6432(-(int64_t)m[1] * (RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC), t);
    o[2] = _rtgui_matrix_round_div6432(-(int64_t)m[2] * (RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC), t);
    o[3] = _rtgui_matrix_round_div6432((int64_t)m[0] * (RTGUI_MATRIX_FRAC * RTGUI_MATRIX_FRAC), t);
    o[4] = _rtgui_matrix_round_div6432(-((int64_t)m[4] * o[0] + (int64_t)m[5] * o[2]), RTGUI_MATRIX_FRAC);
    o[5] = _rtgui_matrix_round_div6432(-((int64_t)m[4] * o[1] + (int64_t)m[5] * o[3]), RTGUI_MATRIX_FRAC);

    return 0;
}

#define COS_TABLE_SZ  512
/* @dd is the degree range in 0~512 */
rt_inline int icost(int dd)
{
    static const short t[COS_TABLE_SZ] = {
        2048, 2048, 2047, 2047, 2046, 2044, 2042, 2040, 2038, 2036, 2033, 2029, 2026,
        2022, 2018, 2013, 2009, 2004, 1998, 1993, 1987, 1980, 1974, 1967, 1960, 1952,
        1945, 1937, 1928, 1920, 1911, 1902, 1892, 1882, 1872, 1862, 1851, 1840, 1829,
        1818, 1806, 1794, 1782, 1769, 1757, 1744, 1730, 1717, 1703, 1689, 1674, 1660,
        1645, 1630, 1615, 1599, 1583, 1567, 1551, 1534, 1517, 1500, 1483, 1466, 1448,
        1430, 1412, 1394, 1375, 1357, 1338, 1319, 1299, 1280, 1260, 1240, 1220, 1200,
        1179, 1159, 1138, 1117, 1096, 1074, 1053, 1031, 1009, 988, 965, 943, 921, 898,
        876, 853, 830, 807, 784, 760, 737, 714, 690, 666, 642, 619, 595, 570, 546, 522,
        498, 473, 449, 424, 400, 375, 350, 325, 301, 276, 251, 226, 201, 176, 151, 126,
        100, 75, 50, 25, 0, -25, -50, -75, -100, -126, -151, -176, -201, -226, -251,
        -276, -301, -325, -350, -375, -400, -424, -449, -473, -498, -522, -546, -570,
        -595, -619, -642, -666, -690, -714, -737, -760, -784, -807, -830, -853, -876,
        -898, -921, -943, -965, -988, -1009, -1031, -1053, -1074, -1096, -1117, -1138,
        -1159, -1179, -1200, -1220, -1240, -1260, -1280, -1299, -1319, -1338, -1357,
        -1375, -1394, -1412, -1430, -1448, -1466, -1483, -1500, -1517, -1534, -1551,
        -1567, -1583, -1599, -1615, -1630, -1645, -1660, -1674, -1689, -1703, -1717,
        -1730, -1744, -1757, -1769, -1782, -1794, -1806, -1818, -1829, -1840, -1851,
        -1862, -1872, -1882, -1892, -1902, -1911, -1920, -1928, -1937, -1945, -1952,
        -1960, -1967, -1974, -1980, -1987, -1993, -1998, -2004, -2009, -2013, -2018,
        -2022, -2026, -2029, -2033, -2036, -2038, -2040, -2042, -2044, -2046, -2047,
        -2047, -2048, -2048, -2048, -2047, -2047, -2046, -2044, -2042, -2040, -2038,
        -2036, -2033, -2029, -2026, -2022, -2018, -2013, -2009, -2004, -1998, -1993,
        -1987, -1980, -1974, -1967, -1960, -1952, -1945, -1937, -1928, -1920, -1911,
        -1902, -1892, -1882, -1872, -1862, -1851, -1840, -1829, -1818, -1806, -1794,
        -1782, -1769, -1757, -1744, -1730, -1717, -1703, -1689, -1674, -1660, -1645,
        -1630, -1615, -1599, -1583, -1567, -1551, -1534, -1517, -1500, -1483, -1466,
        -1448, -1430, -1412, -1394, -1375, -1357, -1338, -1319, -1299, -1280, -1260,
        -1240, -1220, -1200, -1179, -1159, -1138, -1117, -1096, -1074, -1053, -1031,
        -1009, -988, -965, -943, -921, -898, -876, -853, -830, -807, -784, -760, -737,
        -714, -690, -666, -642, -619, -595, -570, -546, -522, -498, -473, -449, -424,
        -400, -375, -350, -325, -301, -276, -251, -226, -201, -176, -151, -126, -100,
        -75, -50, -25, 0, 25, 50, 75, 100, 126, 151, 176, 201, 226, 251, 276, 301, 325,
        350, 375, 400, 424, 449, 473, 498, 522, 546, 570, 595, 619, 642, 666, 690, 714,
        737, 760, 784, 807, 830, 853, 876, 898, 921, 943, 965, 988, 1009, 1031, 1053,
        1074, 1096, 1117, 1138, 1159, 1179, 1200, 1220, 1240, 1260, 1280, 1299, 1319,
        1338, 1357, 1375, 1394, 1412, 1430, 1448, 1466, 1483, 1500, 1517, 1534, 1551,
        1567, 1583, 1599, 1615, 1630, 1645, 1660, 1674, 1689, 1703, 1717, 1730, 1744,
        1757, 1769, 1782, 1794, 1806, 1818, 1829, 1840, 1851, 1862, 1872, 1882, 1892,
        1902, 1911, 1920, 1928, 1937, 1945, 1952, 1960, 1967, 1974, 1980, 1987, 1993,
        1998, 2004, 2009, 2013, 2018, 2022, 2026, 2029, 2033, 2036, 2038, 2040, 2042,
        2044, 2046, 2047, 2047, 2048,
    };

    dd &= COS_TABLE_SZ - 1;

	return t[dd];
}

rt_inline int icosd(int d)
{
	int dd = d;
	return icost(dd);
}

rt_inline int isind(int d)
{
	int dd = COS_TABLE_SZ / 4 - d;
	return icost(dd);
}

rt_inline void rot_mat(int *m, int d)
{
	int cosd = icosd(d);
	int sind = isind(d);

	int m0_cosd = m[0] * cosd;
	int m0_sind = m[0] * sind;
	int m1_cosd = m[1] * cosd;
	int m1_sind = m[1] * sind;
	int m2_cosd = m[2] * cosd;
	int m2_sind = m[2] * sind;
	int m3_cosd = m[3] * cosd;
	int m3_sind = m[3] * sind;
	int m4_cosd = m[4] * cosd;
	int m4_sind = m[4] * sind;
	int m5_cosd = m[5] * cosd;
	int m5_sind = m[5] * sind;

	m[0] = _rtgui_matrix_round_div32(m0_cosd - m1_sind, RTGUI_MATRIX_FRAC);
	m[1] = _rtgui_matrix_round_div32(m0_sind + m1_cosd, RTGUI_MATRIX_FRAC);
	m[2] = _rtgui_matrix_round_div32(m2_cosd - m3_sind, RTGUI_MATRIX_FRAC);
	m[3] = _rtgui_matrix_round_div32(m2_sind + m3_cosd, RTGUI_MATRIX_FRAC);
	m[4] = _rtgui_matrix_round_div32(m4_cosd - m5_sind, RTGUI_MATRIX_FRAC);
	m[5] = _rtgui_matrix_round_div32(m4_sind + m5_cosd, RTGUI_MATRIX_FRAC);
}

rt_inline void scale_mat(int *m, int sx, int sy)
{
	if (sx != RTGUI_MATRIX_FRAC)
    {
		m[0] = _rtgui_matrix_round_div32(m[0] * sx, RTGUI_MATRIX_FRAC);
		m[2] = _rtgui_matrix_round_div32(m[2] * sx, RTGUI_MATRIX_FRAC);
		m[4] = _rtgui_matrix_round_div32(m[4] * sx, RTGUI_MATRIX_FRAC);
	}
	if (sy != RTGUI_MATRIX_FRAC)
    {
		m[1] = _rtgui_matrix_round_div32(m[1] * sy, RTGUI_MATRIX_FRAC);
		m[3] = _rtgui_matrix_round_div32(m[3] * sy, RTGUI_MATRIX_FRAC);
		m[5] = _rtgui_matrix_round_div32(m[5] * sy, RTGUI_MATRIX_FRAC);
	}
}

void rtgui_matrix_rotate(struct rtgui_matrix *m, int rot)
{
    if (rot)
        rot_mat(m->m, rot / (RTGUI_MATRIX_FRAC / COS_TABLE_SZ));
}
RTM_EXPORT(rtgui_matrix_rotate);

void rtgui_matrix_scale(struct rtgui_matrix *m, int sx, int sy)
{
	scale_mat(m->m, sx, sy);
}

void rtgui_matrix_move(struct rtgui_matrix *m, int dx, int dy)
{
	m->m[4] += dx;
	m->m[5] += dy;
}

void rtgui_matrix_dump(const struct rtgui_matrix *m)
{
	const int *mm = m->m;
    rt_kprintf("|%6d, %6d, %6d|\n", mm[0], mm[1], 0);
    rt_kprintf("|%6d, %6d, %6d|\n", mm[2], mm[3], 0);
    rt_kprintf("|%6d, %6d, %6d|\n", mm[4], mm[5], 1);
}
