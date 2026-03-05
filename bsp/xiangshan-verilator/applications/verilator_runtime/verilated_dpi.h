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
/// \brief Verilated DPI header
///
/// This file is included automatically by Verilator at the top of all C++
/// files it generates where DPI is used.  It contains DPI interface
/// functions required by the Verilated code.
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use.
///
//*************************************************************************

#ifndef VERILATOR_VERILATED_DPI_H_
#define VERILATOR_VERILATED_DPI_H_

#include "verilatedos.h"

#include "verilated.h"  // Also presumably included by caller
#include "verilated_sym_props.h"

#include "svdpi.h"

//===================================================================
// SETTING OPERATORS

// Convert svBitVecVal to Verilator internal data
static inline void VL_SET_W_SVBV(int obits, WDataOutP owp, const svBitVecVal* lwp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    for (int i = 0; i < words - 1; ++i) owp[i] = lwp[i];
    owp[words - 1] = lwp[words - 1] & VL_MASK_I(obits);
}
static inline void VL_SET_Q_SVBV(int obits, QData& out, const svBitVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_Q(obits) & VL_SET_QII(lwp[1], lwp[0]);
}
static inline void VL_SET_I_SVBV(int obits, IData& out, const svBitVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_I(obits) & lwp[0];
}
static inline void VL_SET_S_SVBV(int obits, SData& out, const svBitVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_I(obits) & lwp[0];
}
static inline void VL_SET_C_SVBV(int obits, CData& out, const svBitVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_I(obits) & lwp[0];
}

// Convert Verilator internal data to svBitVecVal
static inline void VL_SET_SVBV_W(int obits, svBitVecVal* owp, const WDataInP lwp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    for (int i = 0; i < words - 1; ++i) owp[i] = lwp[i];
    owp[words - 1] = lwp[words - 1] & VL_MASK_I(obits);
}
static inline void VL_SET_SVBV_I(int, svBitVecVal* owp, const IData ld) VL_MT_SAFE { owp[0] = ld; }
static inline void VL_SET_SVBV_Q(int, svBitVecVal* owp, const QData ld) VL_MT_SAFE {
    VL_SET_WQ(owp, ld);
}

// Convert svLogicVecVal to Verilator internal data
// Note these functions ignore X/Z in svLogicVecVal
static inline void VL_SET_W_SVLV(int obits, WDataOutP owp, const svLogicVecVal* lwp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    for (int i = 0; i < words - 1; ++i) owp[i] = lwp[i].aval;
    owp[words - 1] = lwp[words - 1].aval & VL_MASK_I(obits);
}
static inline void VL_SET_Q_SVLV(int obits, QData& out, const svLogicVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_Q(obits) & VL_SET_QII(lwp[1].aval, lwp[0].aval);
}
static inline void VL_SET_I_SVLV(int obits, IData& out, const svLogicVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_I(obits) & lwp[0].aval;
}
static inline void VL_SET_S_SVLV(int obits, SData& out, const svLogicVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_I(obits) & lwp[0].aval;
}
static inline void VL_SET_C_SVLV(int obits, CData& out, const svLogicVecVal* lwp) VL_MT_SAFE {
    out = VL_MASK_I(obits) & lwp[0].aval;
}

// Convert Verilator internal data to svLogicVecVal
// Note these functions never create X/Z in svLogicVecVal
static inline void VL_SET_SVLV_W(int obits, svLogicVecVal* owp, const WDataInP lwp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    for (int i = 0; i < words; ++i) owp[i].bval = 0;
    for (int i = 0; i < words - 1; ++i) owp[i].aval = lwp[i];
    owp[words - 1].aval = lwp[words - 1] & VL_MASK_I(obits);
}
static inline void VL_SET_SVLV_I(int, svLogicVecVal* owp, const IData ld) VL_MT_SAFE {
    owp[0].aval = ld;
    owp[0].bval = 0;
}
static inline void VL_SET_SVLV_Q(int, svLogicVecVal* owp, const QData ld) VL_MT_SAFE {
    VlWide<2> lwp;
    VL_SET_WQ(lwp, ld);
    owp[0].aval = lwp[0];
    owp[0].bval = 0;
    owp[1].aval = lwp[1];
    owp[1].bval = 0;
}

//======================================================================

#endif  // Guard
