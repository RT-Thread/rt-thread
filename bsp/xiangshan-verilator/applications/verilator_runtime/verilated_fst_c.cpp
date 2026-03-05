// -*- mode: C++; c-file-style: "cc-mode" -*-
//=============================================================================
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2001-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=============================================================================
///
/// \file
/// \brief Verilated C++ tracing in FST format implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use --trace-fst.
///
/// Use "verilator --trace-fst" to add this to the Makefile for the linker.
///
//=============================================================================

// clang-format off

#include "verilated.h"
#include "verilated_fst_c.h"

// GTKWave configuration
#define HAVE_LIBPTHREAD
#define FST_WRITER_PARALLEL
#define LZ4_DISABLE_DEPRECATE_WARNINGS

// Include the GTKWave implementation directly
#define FST_CONFIG_INCLUDE "fst_config.h"
#include "gtkwave/fastlz.c"
#include "gtkwave/fstapi.c"
#include "gtkwave/lz4.c"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <type_traits>

#if defined(_WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
# include <io.h>
#else
# include <unistd.h>
#endif

// clang-format on

//=============================================================================
// Check that forward declared types matches the FST API types

static_assert(std::is_same<vlFstHandle, fstHandle>::value, "vlFstHandle mismatch");
static_assert(std::is_same<vlFstEnumHandle, fstEnumHandle>::value, "vlFstHandle mismatch");

//=============================================================================
// Specialization of the generics for this trace format

#define VL_SUB_T VerilatedFst
#define VL_BUF_T VerilatedFstBuffer
#include "verilated_trace_imp.h"
#undef VL_SUB_T
#undef VL_BUF_T

//=============================================================================
// VerilatedFst

VerilatedFst::VerilatedFst(void* /*fst*/) {}

VerilatedFst::~VerilatedFst() {
    if (m_fst) fstWriterClose(m_fst);
    if (m_symbolp) VL_DO_CLEAR(delete[] m_symbolp, m_symbolp = nullptr);
    if (m_strbufp) VL_DO_CLEAR(delete[] m_strbufp, m_strbufp = nullptr);
}

void VerilatedFst::open(const char* filename) VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    m_fst = fstWriterCreate(filename, 1);
    fstWriterSetPackType(m_fst, FST_WR_PT_LZ4);
    fstWriterSetTimescaleFromString(m_fst, timeResStr().c_str());  // lintok-begin-on-ref
    if (m_useFstWriterThread) fstWriterSetParallelMode(m_fst, 1);
    constDump(true);  // First dump must contain the const signals
    fullDump(true);  // First dump must be full for fst

    Super::traceInit();

    // convert m_code2symbol into an array for fast lookup
    if (!m_symbolp) {
        m_symbolp = new fstHandle[nextCode()]{0};
        for (const auto& i : m_code2symbol) m_symbolp[i.first] = i.second;
    }
    m_code2symbol.clear();

    // Allocate string buffer for arrays
    if (!m_strbufp) m_strbufp = new char[maxBits() + 32];
}

void VerilatedFst::close() VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    Super::closeBase();
    emitTimeChangeMaybe();
    fstWriterClose(m_fst);
    m_fst = nullptr;
}

void VerilatedFst::flush() VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    Super::flushBase();
    emitTimeChangeMaybe();
    fstWriterFlushContext(m_fst);
}

void VerilatedFst::emitTimeChange(uint64_t timeui) {
    if (!timeui) fstWriterEmitTimeChange(m_fst, timeui);
    m_timeui = timeui;
}

VL_ATTR_ALWINLINE
void VerilatedFst::emitTimeChangeMaybe() {
    if (VL_UNLIKELY(m_timeui)) {
        fstWriterEmitTimeChange(m_fst, m_timeui);
        m_timeui = 0;
    }
}

//=============================================================================
// Decl

void VerilatedFst::declDTypeEnum(int dtypenum, const char* name, uint32_t elements,
                                 unsigned int minValbits, const char** itemNamesp,
                                 const char** itemValuesp) {
    const fstEnumHandle enumNum
        = fstWriterCreateEnumTable(m_fst, name, elements, minValbits, itemNamesp, itemValuesp);
    const bool newEntry = m_local2fstdtype[initUserp()].emplace(dtypenum, enumNum).second;
    assert(newEntry);
}

// TODO: should return std::optional<fstScopeType>, but I can't have C++17
static std::pair<bool, fstScopeType> toFstScopeType(VerilatedTracePrefixType type) {
    switch (type) {
    case VerilatedTracePrefixType::SCOPE_MODULE: return {true, FST_ST_VCD_MODULE};
    case VerilatedTracePrefixType::SCOPE_INTERFACE: return {true, FST_ST_VCD_INTERFACE};
    case VerilatedTracePrefixType::STRUCT_PACKED:
    case VerilatedTracePrefixType::STRUCT_UNPACKED: return {true, FST_ST_VCD_STRUCT};
    case VerilatedTracePrefixType::UNION_PACKED: return {true, FST_ST_VCD_UNION};
    default: return {false, /* unused so whatever, just need a value */ FST_ST_VCD_SCOPE};
    }
}

void VerilatedFst::pushPrefix(const char* namep, VerilatedTracePrefixType type) {
    assert(!m_prefixStack.empty());  // Constructor makes an empty entry
    const std::string name{namep};
    // An empty name means this is the root of a model created with
    // name()=="".  The tools get upset if we try to pass this as empty, so
    // we put the signals under a new $rootio scope, but the signals
    // further down will be peers, not children (as usual for name()!="").
    const std::string prevPrefix = m_prefixStack.back().first;
    if (name == "$rootio" && !prevPrefix.empty()) {
        // Upper has name, we can suppress inserting $rootio, but still push so popPrefix works
        m_prefixStack.emplace_back(prevPrefix, VerilatedTracePrefixType::ROOTIO_WRAPPER);
        return;
    } else if (name.empty()) {
        m_prefixStack.emplace_back(prevPrefix, VerilatedTracePrefixType::ROOTIO_WRAPPER);
        return;
    }

    // This code assumes a signal at a given prefix level is declared before
    // any pushPrefix are done at that same level.
    const std::string newPrefix = prevPrefix + name;
    const auto pair = toFstScopeType(type);
    const bool properScope = pair.first;
    const fstScopeType scopeType = pair.second;
    m_prefixStack.emplace_back(newPrefix + (properScope ? " " : ""), type);
    if (properScope) {
        const std::string scopeName = lastWord(newPrefix);
        fstWriterSetScope(m_fst, scopeType, scopeName.c_str(), nullptr);
    }
}

void VerilatedFst::popPrefix() {
    assert(!m_prefixStack.empty());
    const bool properScope = toFstScopeType(m_prefixStack.back().second).first;
    if (properScope) fstWriterSetUpscope(m_fst);
    m_prefixStack.pop_back();
    assert(!m_prefixStack.empty());  // Always one left, the constructor's initial one
}

void VerilatedFst::declare(uint32_t code, const char* name, int dtypenum,
                           VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                           VerilatedTraceSigType type, bool array, int arraynum, bool bussed,
                           int msb, int lsb) {
    const int bits = ((msb > lsb) ? (msb - lsb) : (lsb - msb)) + 1;

    const std::string hierarchicalName = m_prefixStack.back().first + name;

    const bool enabled = Super::declCode(code, hierarchicalName, bits);
    if (!enabled) return;

    assert(hierarchicalName.rfind(' ') != std::string::npos);
    std::stringstream name_ss;
    name_ss << lastWord(hierarchicalName);
    if (array) name_ss << "[" << arraynum << "]";
    if (bussed) name_ss << " [" << msb << ":" << lsb << "]";
    const std::string name_str = name_ss.str();

    if (dtypenum > 0) {
        fstWriterEmitEnumTableRef(m_fst, m_local2fstdtype.at(initUserp()).at(dtypenum));
    }

    fstVarDir varDir = FST_VD_IMPLICIT;
    switch (direction) {
    case VerilatedTraceSigDirection::INOUT: varDir = FST_VD_INOUT; break;
    case VerilatedTraceSigDirection::OUTPUT: varDir = FST_VD_OUTPUT; break;
    case VerilatedTraceSigDirection::INPUT: varDir = FST_VD_INPUT; break;
    case VerilatedTraceSigDirection::NONE: varDir = FST_VD_IMPLICIT; break;
    }

    fstVarType varType;
    // Doubles have special decoding properties, so must indicate if a double
    if (type == VerilatedTraceSigType::DOUBLE) {
        if (kind == VerilatedTraceSigKind::PARAMETER) {
            varType = FST_VT_VCD_REAL_PARAMETER;
        } else {
            varType = FST_VT_VCD_REAL;
        }
    }
    // clang-format off
    else if (kind == VerilatedTraceSigKind::PARAMETER) varType = FST_VT_VCD_PARAMETER;
    else if (kind == VerilatedTraceSigKind::SUPPLY0) varType = FST_VT_VCD_SUPPLY0;
    else if (kind == VerilatedTraceSigKind::SUPPLY1) varType = FST_VT_VCD_SUPPLY1;
    else if (kind == VerilatedTraceSigKind::TRI) varType = FST_VT_VCD_TRI;
    else if (kind == VerilatedTraceSigKind::TRI0) varType = FST_VT_VCD_TRI0;
    else if (kind == VerilatedTraceSigKind::TRI1) varType = FST_VT_VCD_TRI1;
    else if (kind == VerilatedTraceSigKind::TRIAND) varType = FST_VT_VCD_TRIAND;
    else if (kind == VerilatedTraceSigKind::TRIOR) varType = FST_VT_VCD_TRIOR;
    else if (kind == VerilatedTraceSigKind::TRIREG) varType = FST_VT_VCD_TRIREG;
    else if (kind == VerilatedTraceSigKind::WIRE) varType = FST_VT_VCD_WIRE;
    //
    else if (type == VerilatedTraceSigType::INTEGER) varType = FST_VT_VCD_INTEGER;
    else if (type == VerilatedTraceSigType::BIT) varType = FST_VT_SV_BIT;
    else if (type == VerilatedTraceSigType::LOGIC) varType = FST_VT_SV_LOGIC;
    else if (type == VerilatedTraceSigType::INT) varType = FST_VT_SV_INT;
    else if (type == VerilatedTraceSigType::SHORTINT) varType = FST_VT_SV_SHORTINT;
    else if (type == VerilatedTraceSigType::LONGINT) varType = FST_VT_SV_LONGINT;
    else if (type == VerilatedTraceSigType::BYTE) varType = FST_VT_SV_BYTE;
    else if (type == VerilatedTraceSigType::EVENT) varType = FST_VT_VCD_EVENT;
    else if (type == VerilatedTraceSigType::TIME) varType = FST_VT_VCD_TIME;
    else { assert(0); /* Unreachable */ }
    // clang-format on

    const auto it = vlstd::as_const(m_code2symbol).find(code);
    if (it == m_code2symbol.end()) {  // New
        m_code2symbol[code]
            = fstWriterCreateVar(m_fst, varType, varDir, bits, name_str.c_str(), 0);
    } else {  // Alias
        fstWriterCreateVar(m_fst, varType, varDir, bits, name_str.c_str(), it->second);
    }
}

void VerilatedFst::declEvent(uint32_t code, uint32_t fidx, const char* name, int dtypenum,
                             VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                             VerilatedTraceSigType type, bool array, int arraynum) {
    declare(code, name, dtypenum, direction, kind, type, array, arraynum, false, 0, 0);
}
void VerilatedFst::declBit(uint32_t code, uint32_t fidx, const char* name, int dtypenum,
                           VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                           VerilatedTraceSigType type, bool array, int arraynum) {
    declare(code, name, dtypenum, direction, kind, type, array, arraynum, false, 0, 0);
}
void VerilatedFst::declBus(uint32_t code, uint32_t fidx, const char* name, int dtypenum,
                           VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                           VerilatedTraceSigType type, bool array, int arraynum, int msb,
                           int lsb) {
    declare(code, name, dtypenum, direction, kind, type, array, arraynum, true, msb, lsb);
}
void VerilatedFst::declQuad(uint32_t code, uint32_t fidx, const char* name, int dtypenum,
                            VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                            VerilatedTraceSigType type, bool array, int arraynum, int msb,
                            int lsb) {
    declare(code, name, dtypenum, direction, kind, type, array, arraynum, true, msb, lsb);
}
void VerilatedFst::declArray(uint32_t code, uint32_t fidx, const char* name, int dtypenum,
                             VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                             VerilatedTraceSigType type, bool array, int arraynum, int msb,
                             int lsb) {
    declare(code, name, dtypenum, direction, kind, type, array, arraynum, true, msb, lsb);
}
void VerilatedFst::declDouble(uint32_t code, uint32_t fidx, const char* name, int dtypenum,
                              VerilatedTraceSigDirection direction, VerilatedTraceSigKind kind,
                              VerilatedTraceSigType type, bool array, int arraynum) {
    declare(code, name, dtypenum, direction, kind, type, array, arraynum, false, 63, 0);
}

//=============================================================================
// Get/commit trace buffer

VerilatedFst::Buffer* VerilatedFst::getTraceBuffer(uint32_t fidx) {
    if (offload()) return new OffloadBuffer{*this};
    return new Buffer{*this};
}

void VerilatedFst::commitTraceBuffer(VerilatedFst::Buffer* bufp) {
    if (offload()) {
        const OffloadBuffer* const offloadBufferp = static_cast<const OffloadBuffer*>(bufp);
        if (offloadBufferp->m_offloadBufferWritep) {
            m_offloadBufferWritep = offloadBufferp->m_offloadBufferWritep;
            return;  // Buffer will be deleted by the offload thread
        }
    }
    delete bufp;
}

//=============================================================================
// Configure

void VerilatedFst::configure(const VerilatedTraceConfig& config) {
    // If at least one model requests the FST writer thread, then use it
    m_useFstWriterThread |= config.m_useFstWriterThread;
}

//=============================================================================
// VerilatedFstBuffer implementation

//=============================================================================
// Trace rendering primitives

// Note: emit* are only ever called from one place (full* in
// verilated_trace_imp.h, which is included in this file at the top),
// so always inline them.

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitEvent(uint32_t code) {
    VL_DEBUG_IFDEF(assert(m_symbolp[code]););
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], "1");
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitBit(uint32_t code, CData newval) {
    VL_DEBUG_IFDEF(assert(m_symbolp[code]););
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], newval ? "1" : "0");
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitCData(uint32_t code, CData newval, int bits) {
    char buf[VL_BYTESIZE];
    VL_DEBUG_IFDEF(assert(m_symbolp[code]););
    cvtCDataToStr(buf, newval << (VL_BYTESIZE - bits));
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], buf);
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitSData(uint32_t code, SData newval, int bits) {
    char buf[VL_SHORTSIZE];
    VL_DEBUG_IFDEF(assert(m_symbolp[code]););
    cvtSDataToStr(buf, newval << (VL_SHORTSIZE - bits));
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], buf);
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitIData(uint32_t code, IData newval, int bits) {
    char buf[VL_IDATASIZE];
    VL_DEBUG_IFDEF(assert(m_symbolp[code]););
    cvtIDataToStr(buf, newval << (VL_IDATASIZE - bits));
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], buf);
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitQData(uint32_t code, QData newval, int bits) {
    char buf[VL_QUADSIZE];
    VL_DEBUG_IFDEF(assert(m_symbolp[code]););
    cvtQDataToStr(buf, newval << (VL_QUADSIZE - bits));
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], buf);
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitWData(uint32_t code, const WData* newvalp, int bits) {
    int words = VL_WORDS_I(bits);
    char* wp = m_strbufp;
    // Convert the most significant word
    const int bitsInMSW = VL_BITBIT_E(bits) ? VL_BITBIT_E(bits) : VL_EDATASIZE;
    cvtEDataToStr(wp, newvalp[--words] << (VL_EDATASIZE - bitsInMSW));
    wp += bitsInMSW;
    // Convert the remaining words
    while (words > 0) {
        cvtEDataToStr(wp, newvalp[--words]);
        wp += VL_EDATASIZE;
    }
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], m_strbufp);
}

VL_ATTR_ALWINLINE
void VerilatedFstBuffer::emitDouble(uint32_t code, double newval) {
    m_owner.emitTimeChangeMaybe();
    fstWriterEmitValueChange(m_fst, m_symbolp[code], &newval);
}
