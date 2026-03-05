// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2003-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=========================================================================
///
/// \file
/// \brief Verilated probability distribution implementation code
///
/// Verilator always adds this file to the Makefile for the linker.
///
/// Those macro/function/variable starting or ending in _ are internal,
/// however many of the other function/macros here are also internal.
///
//=========================================================================

#include "verilated_config.h"
#include "verilatedos.h"

#include "verilated.h"

//===========================================================================
// Dist

static double _vl_dbase_uniform(IData& seedr, int32_t start, int32_t end) VL_MT_SAFE {
    union u_s {
        float s;
        unsigned stemp;
    } u;

    const double d = 0.00000011920928955078125;
    if (VL_UNLIKELY(seedr == 0)) seedr = 259341593;

    double a;
    double b;
    if (VL_UNCOVERABLE(start >= end)) {  // With current usage shound't occur
        a = 0.0;  // LCOV_EXCL_LINE
        b = 2147483647.0;  // LCOV_EXCL_LINE
    } else {
        a = static_cast<double>(start);
        b = static_cast<double>(end);
    }
    seedr = 69069 * seedr + 1;
    u.stemp = seedr;
    u.stemp = (u.stemp >> 9) | 0x3f800000;

    double c = static_cast<double>(u.s);
    c = c + (c * d);
    c = ((b - a) * (c - 1.0)) + a;
    return c;
}

static double _vl_dbase_normal(IData& seedr, int32_t mean, int32_t deviation) VL_MT_SAFE {
    double v1 = 0.0;
    double v2 = 0.0;
    double s = 1.0;
    while ((s >= 1.0) || (s == 0.0)) {
        v1 = _vl_dbase_uniform(seedr, -1, 1);
        v2 = _vl_dbase_uniform(seedr, -1, 1);
        s = v1 * v1 + v2 * v2;
    }
    s = v1 * std::sqrt(-2.0 * log(s) / s);
    v1 = static_cast<double>(deviation);
    v2 = static_cast<double>(mean);
    return (s * v1 + v2);
}

static double _vl_dbase_exponential(IData& seedr, int32_t mean) VL_MT_SAFE {
    double n = _vl_dbase_uniform(seedr, 0, 1);
    if (n != 0) n = -log(n) * mean;
    return n;
}

static double _vl_dbase_chi_square(IData& seedr, int32_t deg_of_free) VL_MT_SAFE {
    double x;
    if (deg_of_free % 2) {
        x = _vl_dbase_normal(seedr, 0, 1);
        x = x * x;
    } else {
        x = 0.0;
    }
    for (int32_t k = 2; k <= deg_of_free; k += 2) x = x + 2 * _vl_dbase_exponential(seedr, 1);
    return x;
}

IData VL_DIST_CHI_SQUARE(IData& seedr, IData udf) VL_MT_SAFE {
    const int32_t df = static_cast<int32_t>(udf);
    if (VL_UNLIKELY(df <= 0)) {
        // Chi_square distribution must have positive degree of freedom
        return 0;
    }
    double r = _vl_dbase_chi_square(seedr, df);
    int32_t i;
    if (r >= 0) {
        i = static_cast<int32_t>(r + 0.5);
    } else {
        r = -r;  // LCOV_EXCL_LINE
        i = static_cast<int32_t>(r + 0.5);  // LCOV_EXCL_LINE
        i = -i;  // LCOV_EXCL_LINE
    }
    return static_cast<IData>(i);
}

IData VL_DIST_ERLANG(IData& seedr, IData uk, IData umean) VL_MT_SAFE {
    const int32_t k = static_cast<int32_t>(uk);
    const int32_t mean = static_cast<int32_t>(umean);
    if (VL_UNLIKELY(k <= 0)) {
        // k-stage erlangian distribution must have positive k
        return 0;
    }
    double x = 1.0;
    for (int32_t i = 1; i <= k; ++i) x = x * _vl_dbase_uniform(seedr, 0, 1);
    const double a = static_cast<double>(mean);
    const double b = static_cast<double>(k);
    double r = -a * log(x) / b;
    int32_t i;
    if (r >= 0) {
        i = static_cast<int32_t>(r + 0.5);
    } else {
        r = -r;
        i = static_cast<int32_t>(r + 0.5);
        i = -i;
    }
    return static_cast<IData>(i);
}

IData VL_DIST_EXPONENTIAL(IData& seedr, IData umean) VL_MT_SAFE {
    const int32_t mean = static_cast<int32_t>(umean);
    if (VL_UNLIKELY(mean <= 0)) {
        // Exponential distribution must have a positive mean
        return 0;
    }
    int32_t i;
    double r = _vl_dbase_exponential(seedr, mean);
    if (r >= 0) {
        i = static_cast<int32_t>(r + 0.5);
    } else {
        r = -r;  // LCOV_EXCL_LINE
        i = static_cast<int32_t>(r + 0.5);  // LCOV_EXCL_LINE
        i = -i;  // LCOV_EXCL_LINE
    }
    return static_cast<IData>(i);
}

IData VL_DIST_NORMAL(IData& seedr, IData umean, IData usd) VL_MT_SAFE {
    const int32_t mean = static_cast<int32_t>(umean);
    const int32_t sd = static_cast<int32_t>(usd);
    double r = _vl_dbase_normal(seedr, mean, sd);
    int32_t i;
    if (r >= 0) {
        i = static_cast<int32_t>(r + 0.5);
    } else {
        r = -r;
        i = static_cast<int32_t>(r + 0.5);
        i = -i;
    }
    return static_cast<IData>(i);
}

IData VL_DIST_POISSON(IData& seedr, IData umean) VL_MT_SAFE {
    const int32_t mean = static_cast<int32_t>(umean);
    if (VL_UNLIKELY(mean <= 0)) {
        // Poisson distribution must have a positive mean
        return 0;
    }
    int32_t i = 0;
    double q = -static_cast<double>(mean);
    double p = exp(q);
    q = _vl_dbase_uniform(seedr, 0, 1);
    while (p < q) {
        ++i;
        q = _vl_dbase_uniform(seedr, 0, 1) * q;
    }
    return static_cast<IData>(i);
}

IData VL_DIST_T(IData& seedr, IData udf) VL_MT_SAFE {
    const int32_t df = static_cast<int32_t>(udf);
    if (VL_UNLIKELY(df <= 0)) {
        // t distribution must have positive degree of freedom
        return 0;
    }
    const double chi2 = _vl_dbase_chi_square(seedr, df);
    const double div = chi2 / static_cast<double>(df);
    const double root = std::sqrt(div);
    double r = _vl_dbase_normal(seedr, 0, 1) / root;
    int32_t i;
    if (r >= 0) {
        i = static_cast<int32_t>(r + 0.5);
    } else {
        r = -r;
        i = static_cast<int32_t>(r + 0.5);
        i = -i;
    }
    return static_cast<IData>(i);
}

IData VL_DIST_UNIFORM(IData& seedr, IData ustart, IData uend) VL_MT_SAFE {
    int32_t start = static_cast<int32_t>(ustart);
    int32_t end = static_cast<int32_t>(uend);
    if (VL_UNLIKELY(start >= end)) return start;
    int32_t i;
    if (end != std::numeric_limits<int32_t>::max()) {
        ++end;
        const double r = _vl_dbase_uniform(seedr, start, end);
        if (r >= 0) {
            i = static_cast<int32_t>(r);
        } else {
            i = static_cast<int32_t>(r - 1);
        }
        if (i < start) i = start;
        if (i >= end) i = end - 1;
    } else if (start != std::numeric_limits<int32_t>::min()) {
        --start;
        const double r = _vl_dbase_uniform(seedr, start, end) + 1.0;
        if (r >= 0) {
            i = static_cast<int32_t>(r);
        } else {
            i = static_cast<int32_t>(r - 1);  // LCOV_EXCL_LINE
        }
        if (i <= start) i = start + 1;
        if (i > end) i = end;
    } else {
        double r = (_vl_dbase_uniform(seedr, start, end) + 2147483648.0) / 4294967295.0;
        r = r * 4294967296.0 - 2147483648.0;
        if (r >= 0) {
            i = static_cast<int32_t>(r);
        } else {
            i = static_cast<int32_t>(r - 1);
        }
    }
    return static_cast<IData>(i);
}
