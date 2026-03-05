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
//*************************************************************************
///
/// \file
/// \brief Verilator common target-specific intrinsics header
///
/// This file is not part of the Verilated public-facing API.
///
/// It is only for internal use; code using machine-specific intrinsics for
/// optimization should include this header rather than directly including
/// the target-specific headers. We provide macros to check for availability
/// of instruction sets, and a common mechanism to disable them.
///
//*************************************************************************

#ifndef VERILATOR_VERILATED_INTRINSICS_H_
#define VERILATOR_VERILATED_INTRINSICS_H_

// clang-format off

// Use VL_PORTABLE_ONLY to disable all intrinsics based optimization
#ifndef VL_PORTABLE_ONLY
# if defined(__SSE2__) && !defined(VL_DISABLE_SSE2)
#  define VL_HAVE_SSE2 1
#  include <emmintrin.h>
# endif
# if defined(__AVX2__) && defined(VL_HAVE_SSE2) && !defined(VL_DISABLE_AVX2)
#  define VL_HAVE_AVX2 1
#  include <immintrin.h>
# endif
#endif

// clang-format on

#endif  // Guard
