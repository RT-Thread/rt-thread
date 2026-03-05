// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2009-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=========================================================================
///
/// \file
/// \brief Verilated DPI implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use the DPI.
///
/// Declare any DPI routine inside Verilog to add this to the Makefile for
/// the linker.
///
/// For documentation on the exported functions (named sv*) that are
/// implemented here, refer to the IEEE DPI chapter.
///
//=========================================================================

#define VERILATOR_VERILATED_DPI_CPP_

#include "verilatedos.h"

#include "verilated_dpi.h"

#include "verilated_imp.h"

// On MSVC++ we need svdpi.h to declare exports, not imports
#define DPI_PROTOTYPES
#undef XXTERN
#define XXTERN DPI_EXTERN DPI_DLLESPEC
#undef EETERN
#define EETERN DPI_EXTERN DPI_DLLESPEC

#include "vltstd/svdpi.h"

//======================================================================
// Internal macros

#define VL_SVDPI_WARN_(...) VL_PRINTF_MT(__VA_ARGS__)

// Function requires a "context" in the import declaration
#define VL_SVDPI_CONTEXT_WARN_() \
    VL_SVDPI_WARN_("%%Warning: DPI C Function called by Verilog DPI import with missing " \
                   "'context' keyword.\n")

//======================================================================
//======================================================================
//======================================================================
// DPI ROUTINES

const char* svDpiVersion() { return "1800-2005"; }

//======================================================================
// Bit-select utility functions.

svBit svGetBitselBit(const svBitVecVal* sp, int bit) { return VL_BITRSHIFT_W(sp, bit) & 1; }
svLogic svGetBitselLogic(const svLogicVecVal* sp, int bit) {
    // Not VL_BITRSHIFT_W as sp is a different structure type
    // Verilator doesn't support X/Z so only aval
    return (((sp[VL_BITWORD_I(bit)].aval >> VL_BITBIT_I(bit)) & 1)
            | (((sp[VL_BITWORD_I(bit)].bval >> VL_BITBIT_I(bit)) & 1) << 1));
}

void svPutBitselBit(svBitVecVal* dp, int bit, svBit s) { VL_ASSIGNBIT_WI(bit, dp, s); }
void svPutBitselLogic(svLogicVecVal* dp, int bit, svLogic s) {
    // Verilator doesn't support X/Z so only aval
    dp[VL_BITWORD_I(bit)].aval = ((dp[VL_BITWORD_I(bit)].aval & ~(VL_UL(1) << VL_BITBIT_I(bit)))
                                  | ((s & 1) << VL_BITBIT_I(bit)));
    dp[VL_BITWORD_I(bit)].bval = ((dp[VL_BITWORD_I(bit)].bval & ~(VL_UL(1) << VL_BITBIT_I(bit)))
                                  | ((s & 2) >> 1 << VL_BITBIT_I(bit)));
}

void svGetPartselBit(svBitVecVal* dp, const svBitVecVal* sp, int lsb, int width) {
    // Verilator supports > 32 bit widths, which is an extension to IEEE DPI
    // See also VL_SEL_WWI
    const int msb = lsb + width - 1;
    const int word_shift = VL_BITWORD_I(lsb);
    if (VL_BITBIT_I(lsb) == 0) {
        // Just a word extract
        for (int i = 0; i < VL_WORDS_I(width); ++i) dp[i] = sp[i + word_shift];
    } else {
        const int loffset = lsb & VL_SIZEBITS_I;
        const int nbitsfromlow = 32 - loffset;  // bits that end up in lword (know loffset!=0)
        // Middle words
        const int words = VL_WORDS_I(msb - lsb + 1);
        for (int i = 0; i < words; ++i) {
            dp[i] = sp[i + word_shift] >> loffset;
            const int upperword = i + word_shift + 1;
            if (upperword <= static_cast<int>(VL_BITWORD_I(msb))) {
                dp[i] |= sp[upperword] << nbitsfromlow;
            }
        }
    }
    // Clean result
    dp[VL_WORDS_I(width) - 1] &= VL_MASK_I(width);
}
void svGetPartselLogic(svLogicVecVal* dp, const svLogicVecVal* sp, int lsb, int width) {
    // Verilator supports > 32 bit widths, which is an extension to IEEE DPI
    const int msb = lsb + width - 1;
    const int word_shift = VL_BITWORD_I(lsb);
    if (VL_BITBIT_I(lsb) == 0) {
        // Just a word extract
        for (int i = 0; i < VL_WORDS_I(width); ++i) dp[i] = sp[i + word_shift];
    } else {
        const int loffset = lsb & VL_SIZEBITS_I;
        const int nbitsfromlow = 32 - loffset;  // bits that end up in lword (know loffset!=0)
        // Middle words
        const int words = VL_WORDS_I(msb - lsb + 1);
        for (int i = 0; i < words; ++i) {
            dp[i].aval = sp[i + word_shift].aval >> loffset;
            dp[i].bval = sp[i + word_shift].bval >> loffset;
            const int upperword = i + word_shift + 1;
            if (upperword <= static_cast<int>(VL_BITWORD_I(msb))) {
                dp[i].aval |= sp[upperword].aval << nbitsfromlow;
                dp[i].bval |= sp[upperword].bval << nbitsfromlow;
            }
        }
    }
    // Clean result
    dp[VL_WORDS_I(width) - 1].aval &= VL_MASK_I(width);
    dp[VL_WORDS_I(width) - 1].bval &= VL_MASK_I(width);
}
void svPutPartselBit(svBitVecVal* dp, const svBitVecVal s, int lbit, int width) {
    // See also _vl_insert_WI
    const int hbit = lbit + width - 1;
    const int hoffset = VL_BITBIT_I(hbit);
    const int loffset = VL_BITBIT_I(lbit);
    if (hoffset == VL_SIZEBITS_I && loffset == 0) {
        // Fast and common case, word based insertion
        dp[VL_BITWORD_I(lbit)] = s;
    } else {
        const int hword = VL_BITWORD_I(hbit);
        const int lword = VL_BITWORD_I(lbit);
        if (hword == lword) {  // know < 32 bits because above checks it
            const IData insmask = (VL_MASK_I(hoffset - loffset + 1)) << loffset;
            dp[lword] = (dp[lword] & ~insmask) | ((s << loffset) & insmask);
        } else {
            const IData hinsmask = (VL_MASK_I(hoffset - 0 + 1)) << 0;
            const IData linsmask = (VL_MASK_I(31 - loffset + 1)) << loffset;
            const int nbitsonright = 32 - loffset;  // bits that end up in lword
            dp[lword] = (dp[lword] & ~linsmask) | ((s << loffset) & linsmask);
            dp[hword] = (dp[hword] & ~hinsmask) | ((s >> nbitsonright) & hinsmask);
        }
    }
}
// cppcheck-suppress passedByValue
void svPutPartselLogic(svLogicVecVal* dp, const svLogicVecVal s, int lbit, int width) {
    const int hbit = lbit + width - 1;
    const int hoffset = VL_BITBIT_I(hbit);
    const int loffset = VL_BITBIT_I(lbit);
    if (hoffset == VL_SIZEBITS_I && loffset == 0) {
        // Fast and common case, word based insertion
        dp[VL_BITWORD_I(lbit)].aval = s.aval;
        dp[VL_BITWORD_I(lbit)].bval = s.bval;
    } else {
        const int hword = VL_BITWORD_I(hbit);
        const int lword = VL_BITWORD_I(lbit);
        if (hword == lword) {  // know < 32 bits because above checks it
            const IData insmask = (VL_MASK_I(hoffset - loffset + 1)) << loffset;
            dp[lword].aval = (dp[lword].aval & ~insmask) | ((s.aval << loffset) & insmask);
            dp[lword].bval = (dp[lword].bval & ~insmask) | ((s.bval << loffset) & insmask);
        } else {
            const IData hinsmask = (VL_MASK_I(hoffset - 0 + 1)) << 0;
            const IData linsmask = (VL_MASK_I(31 - loffset + 1)) << loffset;
            const int nbitsonright = 32 - loffset;  // bits that end up in lword
            dp[lword].aval = (dp[lword].aval & ~linsmask) | ((s.aval << loffset) & linsmask);
            dp[lword].bval = (dp[lword].bval & ~linsmask) | ((s.bval << loffset) & linsmask);
            dp[hword].aval = (dp[hword].aval & ~hinsmask) | ((s.aval >> nbitsonright) & hinsmask);
            dp[hword].bval = (dp[hword].bval & ~hinsmask) | ((s.bval >> nbitsonright) & hinsmask);
        }
    }
}

//======================================================================
// Open array internals

static const VerilatedDpiOpenVar* _vl_openhandle_varp(const svOpenArrayHandle h) VL_MT_SAFE {
    if (VL_UNLIKELY(!h)) {
        VL_FATAL_MT(__FILE__, __LINE__, "",
                    "%%Error: DPI svOpenArrayHandle function called with nullptr handle");
    }
    const VerilatedDpiOpenVar* const varp = reinterpret_cast<const VerilatedDpiOpenVar*>(h);
    if (VL_UNLIKELY(!varp->magicOk())) {
        VL_FATAL_MT(__FILE__, __LINE__, "",
                    "%%Error: DPI svOpenArrayHandle function called with non-Verilator handle");
    }
    return varp;
}

//======================================================================
// Open array querying functions

int svLeft(const svOpenArrayHandle h, int d) { return _vl_openhandle_varp(h)->left(d); }
int svRight(const svOpenArrayHandle h, int d) { return _vl_openhandle_varp(h)->right(d); }
int svLow(const svOpenArrayHandle h, int d) { return _vl_openhandle_varp(h)->low(d); }
int svHigh(const svOpenArrayHandle h, int d) { return _vl_openhandle_varp(h)->high(d); }
int svIncrement(const svOpenArrayHandle h, int d) { return _vl_openhandle_varp(h)->increment(d); }
int svSize(const svOpenArrayHandle h, int d) { return _vl_openhandle_varp(h)->elements(d); }
int svDimensions(const svOpenArrayHandle h) { return _vl_openhandle_varp(h)->udims(); }

// Return pointer to open array data, or nullptr if not in IEEE standard C layout
void* svGetArrayPtr(const svOpenArrayHandle h) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(h);
    if (VL_UNLIKELY(!varp->isDpiStdLayout())) return nullptr;
    return varp->datap();
}
// Return size of open array, or 0 if not in IEEE standard C layout
int svSizeOfArray(const svOpenArrayHandle h) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(h);
    if (VL_UNLIKELY(!varp->isDpiStdLayout())) return 0;
    // Truncate 64 bits to int; DPI is limited to 4GB
    return static_cast<int>(varp->totalSize());
}

//======================================================================
// Open array access internals

static void* _vl_sv_adjusted_datap(const VerilatedDpiOpenVar* varp, int nargs, int indx1,
                                   int indx2, int indx3) VL_MT_SAFE {
    void* datap = varp->datap();
    if (VL_UNLIKELY(nargs != varp->udims())) {
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function called on"
                       " %d dimensional array using %d dimensional function.\n",
                       varp->udims(), nargs);
        return nullptr;
    }
    if (nargs >= 1) {
        datap = varp->datapAdjustIndex(datap, 1, indx1);
        if (VL_UNLIKELY(!datap)) {
            VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function index 1 "
                           "out of bounds; %d outside [%d:%d].\n",
                           indx1, varp->left(1), varp->right(1));
            return nullptr;
        }
    }
    if (nargs >= 2) {
        datap = varp->datapAdjustIndex(datap, 2, indx2);
        if (VL_UNLIKELY(!datap)) {
            VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function index 2 "
                           "out of bounds; %d outside [%d:%d].\n",
                           indx2, varp->left(2), varp->right(2));
            return nullptr;
        }
    }
    if (nargs >= 3) {
        datap = varp->datapAdjustIndex(datap, 3, indx3);
        if (VL_UNLIKELY(!datap)) {
            VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function index 3 "
                           "out of bounds; %d outside [%d:%d].\n",
                           indx1, varp->left(3), varp->right(3));
            return nullptr;
        }
    }
    return datap;
}

// Return pointer to simulator open array element, or nullptr if outside range
static void* _vl_svGetArrElemPtr(const svOpenArrayHandle h, int nargs, int indx1, int indx2,
                                 int indx3) VL_MT_SAFE {
    const VerilatedDpiOpenVar* varp = _vl_openhandle_varp(h);
    if (VL_UNLIKELY(!varp->isDpiStdLayout())) return nullptr;
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    return datap;
}

// Copy to user bit array from simulator open array
static void _vl_svGetBitArrElemVecVal(svBitVecVal* d, const svOpenArrayHandle s, int nargs,
                                      int indx1, int indx2, int indx3) VL_MT_SAFE {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    if (VL_UNLIKELY(!datap)) return;
    switch (varp->vltype()) {  // LCOV_EXCL_BR_LINE
    case VLVT_UINT8: d[0] = *(reinterpret_cast<CData*>(datap)); return;
    case VLVT_UINT16: d[0] = *(reinterpret_cast<SData*>(datap)); return;
    case VLVT_UINT32: d[0] = *(reinterpret_cast<IData*>(datap)); return;
    case VLVT_UINT64: {
        VlWide<2> lwp;
        VL_SET_WQ(lwp, *(reinterpret_cast<QData*>(datap)));
        d[0] = lwp[0];
        d[1] = lwp[1];
        break;
    }
    case VLVT_WDATA: {
        WDataInP wdatap = (reinterpret_cast<WDataInP>(datap));
        for (int i = 0; i < VL_WORDS_I(varp->entBits()); ++i) d[i] = wdatap[i];
        return;
    }
    default:  // LCOV_EXCL_START  // Errored earlier
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function unsupported datatype (%d).\n",
                       varp->vltype());
        return;  // LCOV_EXCL_STOP
    }
}
// Copy to user logic array from simulator open array
static void _vl_svGetLogicArrElemVecVal(svLogicVecVal* d, const svOpenArrayHandle s, int nargs,
                                        int indx1, int indx2, int indx3) VL_MT_SAFE {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    if (VL_UNLIKELY(!datap)) return;
    switch (varp->vltype()) {  // LCOV_EXCL_BR_LINE
    case VLVT_UINT8:
        d[0].aval = *(reinterpret_cast<CData*>(datap));
        d[0].bval = 0;
        return;
    case VLVT_UINT16:
        d[0].aval = *(reinterpret_cast<SData*>(datap));
        d[0].bval = 0;
        return;
    case VLVT_UINT32:
        d[0].aval = *(reinterpret_cast<IData*>(datap));
        d[0].bval = 0;
        return;
    case VLVT_UINT64: {
        VlWide<2> lwp;
        VL_SET_WQ(lwp, *(reinterpret_cast<QData*>(datap)));
        d[0].aval = lwp[0];
        d[0].bval = 0;
        d[1].aval = lwp[1];
        d[1].bval = 0;
        break;
    }
    case VLVT_WDATA: {
        WDataInP wdatap = (reinterpret_cast<WDataInP>(datap));
        for (int i = 0; i < VL_WORDS_I(varp->entBits()); ++i) {
            d[i].aval = wdatap[i];
            d[i].bval = 0;
        }
        return;
    }
    default:  // LCOV_EXCL_START  // Errored earlier
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function unsupported datatype (%d).\n",
                       varp->vltype());
        return;  // LCOV_EXCL_STOP
    }
}

// Copy to simulator open array from from user bit array
static void _vl_svPutBitArrElemVecVal(const svOpenArrayHandle d, const svBitVecVal* s, int nargs,
                                      int indx1, int indx2, int indx3) VL_MT_SAFE {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    if (VL_UNLIKELY(!datap)) return;
    switch (varp->vltype()) {  // LCOV_EXCL_BR_LINE
    case VLVT_UINT8: *(reinterpret_cast<CData*>(datap)) = s[0]; return;
    case VLVT_UINT16: *(reinterpret_cast<SData*>(datap)) = s[0]; return;
    case VLVT_UINT32: *(reinterpret_cast<IData*>(datap)) = s[0]; return;
    case VLVT_UINT64: *(reinterpret_cast<QData*>(datap)) = VL_SET_QII(s[1], s[0]); break;
    case VLVT_WDATA: {
        WDataOutP wdatap = (reinterpret_cast<WDataOutP>(datap));
        for (int i = 0; i < VL_WORDS_I(varp->entBits()); ++i) wdatap[i] = s[i];
        return;
    }
    default:  // LCOV_EXCL_START  // Errored earlier
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function unsupported datatype (%d).\n",
                       varp->vltype());
        return;  // LCOV_EXCL_STOP
    }
}
// Copy to simulator open array from from user logic array
static void _vl_svPutLogicArrElemVecVal(const svOpenArrayHandle d, const svLogicVecVal* s,
                                        int nargs, int indx1, int indx2, int indx3) VL_MT_SAFE {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    if (VL_UNLIKELY(!datap)) return;
    switch (varp->vltype()) {  // LCOV_EXCL_BR_LINE
    case VLVT_UINT8: *(reinterpret_cast<CData*>(datap)) = s[0].aval; return;
    case VLVT_UINT16: *(reinterpret_cast<SData*>(datap)) = s[0].aval; return;
    case VLVT_UINT32: *(reinterpret_cast<IData*>(datap)) = s[0].aval; return;
    case VLVT_UINT64: *(reinterpret_cast<QData*>(datap)) = VL_SET_QII(s[1].aval, s[0].aval); break;
    case VLVT_WDATA: {
        WDataOutP wdatap = (reinterpret_cast<WDataOutP>(datap));
        for (int i = 0; i < VL_WORDS_I(varp->entBits()); ++i) wdatap[i] = s[i].aval;
        return;
    }
    default:  // LCOV_EXCL_START  // Errored earlier
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function unsupported datatype (%d).\n",
                       varp->vltype());
        return;  // LCOV_EXCL_STOP
    }
}

// Return bit from simulator open array
static svBit _vl_svGetBitArrElem(const svOpenArrayHandle s, int nargs, int indx1, int indx2,
                                 int indx3, int) VL_MT_SAFE {
    // One extra index supported, as need bit number
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    if (VL_UNLIKELY(!datap)) return 0;
    switch (varp->vltype()) {  // LCOV_EXCL_BR_LINE
    case VLVT_UINT8: return (*(reinterpret_cast<CData*>(datap))) & 1;
    default:  // LCOV_EXCL_START  // Errored earlier
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function unsupported datatype (%d).\n",
                       varp->vltype());
        return 0;  // LCOV_EXCL_STOP
    }
}
// Update simulator open array from bit
static void _vl_svPutBitArrElem(const svOpenArrayHandle d, svBit value, int nargs, int indx1,
                                int indx2, int indx3, int) VL_MT_SAFE {
    // One extra index supported, as need bit number
    value &= 1;  // Make sure clean
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    void* const datap = _vl_sv_adjusted_datap(varp, nargs, indx1, indx2, indx3);
    if (VL_UNLIKELY(!datap)) return;
    switch (varp->vltype()) {  // LCOV_EXCL_BR_LINE
    case VLVT_UINT8: *(reinterpret_cast<CData*>(datap)) = value; return;
    default:  // LCOV_EXCL_START  // Errored earlier
        VL_SVDPI_WARN_("%%Warning: DPI svOpenArrayHandle function unsupported datatype (%d).\n",
                       varp->vltype());
        return;  // LCOV_EXCL_STOP
    }
}

//======================================================================
// DPI accessors that call above functions

void* svGetArrElemPtr(const svOpenArrayHandle h, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(h);
    void* datap;
    va_list ap;
    va_start(ap, indx1);
    // va_arg is a macro, so need temporaries as used below
    switch (varp->udims()) {
    case 1: datap = _vl_svGetArrElemPtr(h, 1, indx1, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        datap = _vl_svGetArrElemPtr(h, 2, indx1, indx2, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        datap = _vl_svGetArrElemPtr(h, 3, indx1, indx2, indx3);
        break;
    }
    default: datap = _vl_svGetArrElemPtr(h, -1, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
    return datap;
}
void* svGetArrElemPtr1(const svOpenArrayHandle h, int indx1) {
    return _vl_svGetArrElemPtr(h, 1, indx1, 0, 0);
}
void* svGetArrElemPtr2(const svOpenArrayHandle h, int indx1, int indx2) {
    return _vl_svGetArrElemPtr(h, 2, indx1, indx2, 0);
}
void* svGetArrElemPtr3(const svOpenArrayHandle h, int indx1, int indx2, int indx3) {
    return _vl_svGetArrElemPtr(h, 3, indx1, indx2, indx3);
}

void svPutBitArrElemVecVal(const svOpenArrayHandle d, const svBitVecVal* s, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: _vl_svPutBitArrElemVecVal(d, s, 1, indx1, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        _vl_svPutBitArrElemVecVal(d, s, 2, indx1, indx2, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        _vl_svPutBitArrElemVecVal(d, s, 3, indx1, indx2, indx3);
        break;
    }
    default: _vl_svPutBitArrElemVecVal(d, s, -1, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
}
void svPutBitArrElem1VecVal(const svOpenArrayHandle d, const svBitVecVal* s, int indx1) {
    _vl_svPutBitArrElemVecVal(d, s, 1, indx1, 0, 0);
}
void svPutBitArrElem2VecVal(const svOpenArrayHandle d, const svBitVecVal* s, int indx1,
                            int indx2) {
    _vl_svPutBitArrElemVecVal(d, s, 2, indx1, indx2, 0);
}
void svPutBitArrElem3VecVal(const svOpenArrayHandle d, const svBitVecVal* s, int indx1, int indx2,
                            int indx3) {
    _vl_svPutBitArrElemVecVal(d, s, 3, indx1, indx2, indx3);
}
void svPutLogicArrElemVecVal(const svOpenArrayHandle d, const svLogicVecVal* s, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: _vl_svPutLogicArrElemVecVal(d, s, 1, indx1, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        _vl_svPutLogicArrElemVecVal(d, s, 2, indx1, indx2, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        _vl_svPutLogicArrElemVecVal(d, s, 3, indx1, indx2, indx3);
        break;
    }
    default: _vl_svPutLogicArrElemVecVal(d, s, -1, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
}
void svPutLogicArrElem1VecVal(const svOpenArrayHandle d, const svLogicVecVal* s, int indx1) {
    _vl_svPutLogicArrElemVecVal(d, s, 1, indx1, 0, 0);
}
void svPutLogicArrElem2VecVal(const svOpenArrayHandle d, const svLogicVecVal* s, int indx1,
                              int indx2) {
    _vl_svPutLogicArrElemVecVal(d, s, 2, indx1, indx2, 0);
}
void svPutLogicArrElem3VecVal(const svOpenArrayHandle d, const svLogicVecVal* s, int indx1,
                              int indx2, int indx3) {
    _vl_svPutLogicArrElemVecVal(d, s, 3, indx1, indx2, indx3);
}

//======================================================================
// From simulator storage into user space

void svGetBitArrElemVecVal(svBitVecVal* d, const svOpenArrayHandle s, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: _vl_svGetBitArrElemVecVal(d, s, 1, indx1, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        _vl_svGetBitArrElemVecVal(d, s, 2, indx1, indx2, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        _vl_svGetBitArrElemVecVal(d, s, 3, indx1, indx2, indx3);
        break;
    }
    default: _vl_svGetBitArrElemVecVal(d, s, -1, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
}
void svGetBitArrElem1VecVal(svBitVecVal* d, const svOpenArrayHandle s, int indx1) {
    _vl_svGetBitArrElemVecVal(d, s, 1, indx1, 0, 0);
}
void svGetBitArrElem2VecVal(svBitVecVal* d, const svOpenArrayHandle s, int indx1, int indx2) {
    _vl_svGetBitArrElemVecVal(d, s, 2, indx1, indx2, 0);
}
void svGetBitArrElem3VecVal(svBitVecVal* d, const svOpenArrayHandle s, int indx1, int indx2,
                            int indx3) {
    _vl_svGetBitArrElemVecVal(d, s, 3, indx1, indx2, indx3);
}
void svGetLogicArrElemVecVal(svLogicVecVal* d, const svOpenArrayHandle s, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: _vl_svGetLogicArrElemVecVal(d, s, 1, indx1, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        _vl_svGetLogicArrElemVecVal(d, s, 2, indx1, indx2, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        _vl_svGetLogicArrElemVecVal(d, s, 3, indx1, indx2, indx3);
        break;
    }
    default: _vl_svGetLogicArrElemVecVal(d, s, -1, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
}
void svGetLogicArrElem1VecVal(svLogicVecVal* d, const svOpenArrayHandle s, int indx1) {
    _vl_svGetLogicArrElemVecVal(d, s, 1, indx1, 0, 0);
}
void svGetLogicArrElem2VecVal(svLogicVecVal* d, const svOpenArrayHandle s, int indx1, int indx2) {
    _vl_svGetLogicArrElemVecVal(d, s, 2, indx1, indx2, 0);
}
void svGetLogicArrElem3VecVal(svLogicVecVal* d, const svOpenArrayHandle s, int indx1, int indx2,
                              int indx3) {
    _vl_svGetLogicArrElemVecVal(d, s, 3, indx1, indx2, indx3);
}

svBit svGetBitArrElem(const svOpenArrayHandle s, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    svBit out;
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: out = _vl_svGetBitArrElem(s, 1, indx1, 0, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        out = _vl_svGetBitArrElem(s, 2, indx1, indx2, 0, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        out = _vl_svGetBitArrElem(s, 3, indx1, indx2, indx3, 0);
        break;
    }
    default: out = _vl_svGetBitArrElem(s, -1, 0, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
    return out;
}
svBit svGetBitArrElem1(const svOpenArrayHandle s, int indx1) {
    return _vl_svGetBitArrElem(s, 1, indx1, 0, 0, 0);
}
svBit svGetBitArrElem2(const svOpenArrayHandle s, int indx1, int indx2) {
    return _vl_svGetBitArrElem(s, 2, indx1, indx2, 0, 0);
}
svBit svGetBitArrElem3(const svOpenArrayHandle s, int indx1, int indx2, int indx3) {
    return _vl_svGetBitArrElem(s, 3, indx1, indx2, indx3, 0);
}
svLogic svGetLogicArrElem(const svOpenArrayHandle s, int indx1, ...) {
    // Verilator doesn't support X/Z so can just call Bit version
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(s);
    svBit out;
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: out = _vl_svGetBitArrElem(s, 1, indx1, 0, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        out = _vl_svGetBitArrElem(s, 2, indx1, indx2, 0, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        out = _vl_svGetBitArrElem(s, 3, indx1, indx2, indx3, 0);
        break;
    }
    default: out = _vl_svGetBitArrElem(s, -1, 0, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
    return out;
}
svLogic svGetLogicArrElem1(const svOpenArrayHandle s, int indx1) {
    // Verilator doesn't support X/Z so can just call Bit version
    return svGetBitArrElem1(s, indx1);
}
svLogic svGetLogicArrElem2(const svOpenArrayHandle s, int indx1, int indx2) {
    // Verilator doesn't support X/Z so can just call Bit version
    return svGetBitArrElem2(s, indx1, indx2);
}
svLogic svGetLogicArrElem3(const svOpenArrayHandle s, int indx1, int indx2, int indx3) {
    // Verilator doesn't support X/Z so can just call Bit version
    return svGetBitArrElem3(s, indx1, indx2, indx3);
}

void svPutBitArrElem(const svOpenArrayHandle d, svBit value, int indx1, ...) {
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: _vl_svPutBitArrElem(d, value, 1, indx1, 0, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        _vl_svPutBitArrElem(d, value, 2, indx1, indx2, 0, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        _vl_svPutBitArrElem(d, value, 3, indx1, indx2, indx3, 0);
        break;
    }
    default: _vl_svPutBitArrElem(d, value, -1, 0, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
}
void svPutBitArrElem1(const svOpenArrayHandle d, svBit value, int indx1) {
    _vl_svPutBitArrElem(d, value, 1, indx1, 0, 0, 0);
}
void svPutBitArrElem2(const svOpenArrayHandle d, svBit value, int indx1, int indx2) {
    _vl_svPutBitArrElem(d, value, 2, indx1, indx2, 0, 0);
}
void svPutBitArrElem3(const svOpenArrayHandle d, svBit value, int indx1, int indx2, int indx3) {
    _vl_svPutBitArrElem(d, value, 3, indx1, indx2, indx3, 0);
}
void svPutLogicArrElem(const svOpenArrayHandle d, svLogic value, int indx1, ...) {
    // Verilator doesn't support X/Z so can just call Bit version
    const VerilatedDpiOpenVar* const varp = _vl_openhandle_varp(d);
    va_list ap;
    va_start(ap, indx1);
    switch (varp->udims()) {
    case 1: _vl_svPutBitArrElem(d, value, 1, indx1, 0, 0, 0); break;
    case 2: {
        const int indx2 = va_arg(ap, int);
        _vl_svPutBitArrElem(d, value, 2, indx1, indx2, 0, 0);
        break;
    }
    case 3: {
        const int indx2 = va_arg(ap, int);
        const int indx3 = va_arg(ap, int);
        _vl_svPutBitArrElem(d, value, 3, indx1, indx2, indx3, 0);
        break;
    }
    default: _vl_svPutBitArrElem(d, value, -1, 0, 0, 0, 0); break;  // Will error
    }
    va_end(ap);
}
void svPutLogicArrElem1(const svOpenArrayHandle d, svLogic value, int indx1) {
    // Verilator doesn't support X/Z so can just call Bit version
    svPutBitArrElem1(d, value, indx1);
}
void svPutLogicArrElem2(const svOpenArrayHandle d, svLogic value, int indx1, int indx2) {
    // Verilator doesn't support X/Z so can just call Bit version
    svPutBitArrElem2(d, value, indx1, indx2);
}
void svPutLogicArrElem3(const svOpenArrayHandle d, svLogic value, int indx1, int indx2,
                        int indx3) {
    // Verilator doesn't support X/Z so can just call Bit version
    svPutBitArrElem3(d, value, indx1, indx2, indx3);
}

//======================================================================
// Functions for working with DPI context

svScope svGetScope() {
    if (VL_UNLIKELY(!Verilated::dpiInContext())) {
        VL_SVDPI_CONTEXT_WARN_();
        return nullptr;
    }
    // NOLINTNEXTLINE(google-readability-casting)
    return (svScope)(Verilated::dpiScope());
}

svScope svSetScope(const svScope scope) {
    const VerilatedScope* const prevScopep = Verilated::dpiScope();
    const VerilatedScope* const vscopep = reinterpret_cast<const VerilatedScope*>(scope);
    Verilated::dpiScope(vscopep);
    // NOLINTNEXTLINE(google-readability-casting)
    return (svScope)(prevScopep);
}

const char* svGetNameFromScope(const svScope scope) {
    const VerilatedScope* const vscopep = reinterpret_cast<const VerilatedScope*>(scope);
    return vscopep->name();
}

svScope svGetScopeFromName(const char* scopeName) {
    // NOLINTNEXTLINE(google-readability-casting)
    return (svScope)(Verilated::threadContextp()->scopeFind(scopeName));
}

int svPutUserData(const svScope scope, void* userKey, void* userData) {
    VerilatedImp::userInsert(scope, userKey, userData);
    return 0;
}

void* svGetUserData(const svScope scope, void* userKey) {
    return VerilatedImp::userFind(scope, userKey);
}

int svGetCallerInfo(const char** fileNamepp, int* lineNumberp) {
    if (VL_UNLIKELY(!Verilated::dpiInContext())) {
        VL_SVDPI_CONTEXT_WARN_();
        return false;
    }
    if (VL_LIKELY(fileNamepp)) *fileNamepp = Verilated::dpiFilenamep();  // thread local
    if (VL_LIKELY(lineNumberp)) *lineNumberp = Verilated::dpiLineno();  // thread local
    return true;
}

//======================================================================
// Time

int svGetTime(const svScope scope, svTimeVal* time) {
    if (VL_UNLIKELY(!time)) return -1;
    const QData qtime = VL_TIME_Q();
    VlWide<2> itime;
    VL_SET_WQ(itime, qtime);
    time->low = itime[0];
    time->high = itime[1];
    return 0;
}

int svGetTimeUnit(const svScope scope, int32_t* time_unit) {
    if (VL_UNLIKELY(!time_unit)) return -1;
    const VerilatedScope* const vscopep = reinterpret_cast<const VerilatedScope*>(scope);
    if (!vscopep) {  // Null asks for global, not unlikely
        *time_unit = Verilated::threadContextp()->timeunit();
    } else {
        *time_unit = vscopep->timeunit();
    }
    return 0;
}

int svGetTimePrecision(const svScope scope, int32_t* time_precision) {
    if (VL_UNLIKELY(!time_precision)) return -1;
    *time_precision = Verilated::threadContextp()->timeprecision();
    return 0;
}

//======================================================================
// Disables

int svIsDisabledState() {
    return 0;  // Disables not implemented
}

void svAckDisabledState() {
    // Disables not implemented
}
