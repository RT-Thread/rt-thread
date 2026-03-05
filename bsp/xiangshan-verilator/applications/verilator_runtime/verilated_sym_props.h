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
/// \brief Verilated symbol inspection header
///
/// This file is for inclusion by internal files that need to inspect
/// specific symbols.  Applications typically use the VPI instead.
///
/// User wrapper code wanting to inspect the symbol table should use
/// verilated_syms.h instead.
///
//*************************************************************************
// These classes are thread safe, and read only.

#ifndef VERILATOR_VERILATED_SYM_PROPS_H_
#define VERILATOR_VERILATED_SYM_PROPS_H_

#include "verilatedos.h"

#include <vector>

//===========================================================================
// Verilator range
// Thread safety: Assume is constructed only with model, then any number of readers

// See also V3Ast::VNumRange
class VerilatedRange final {
    int m_left = 0;
    int m_right = 0;

protected:
    friend class VerilatedVarProps;
    friend class VerilatedScope;
    VerilatedRange() = default;
    void init(int left, int right) {
        m_left = left;
        m_right = right;
    }

public:
    VerilatedRange(int left, int right)
        : m_left{left}
        , m_right{right} {}
    ~VerilatedRange() = default;
    int left() const VL_PURE { return m_left; }
    int right() const VL_PURE { return m_right; }
    int low() const VL_PURE { return (m_left < m_right) ? m_left : m_right; }
    int high() const VL_PURE { return (m_left > m_right) ? m_left : m_right; }
    int elements() const VL_PURE {
        return (VL_LIKELY(m_left >= m_right) ? (m_left - m_right + 1) : (m_right - m_left + 1));
    }
    int increment() const VL_PURE { return (m_left >= m_right) ? 1 : -1; }
};

//===========================================================================
// Verilator variable
// Thread safety: Assume is constructed only with model, then any number of readers

class VerilatedVarProps VL_NOT_FINAL {
    // TYPES
    static constexpr uint32_t MAGIC = 0xddc4f829UL;
    // MEMBERS
    const uint32_t m_magic;  // Magic number
    const VerilatedVarType m_vltype;  // Data type
    const VerilatedVarFlags m_vlflags;  // Direction
    std::vector<VerilatedRange> m_unpacked;  // Unpacked array ranges
    std::vector<VerilatedRange> m_packed;  // Packed array ranges
    VerilatedRange m_packedDpi;  // Flattened packed array range
    void initUnpacked(int udims, const int* ulims) {
        for (int i = 0; i < udims; ++i) {
            const int uleft = ulims ? ulims[2 * i + 0] : 0;
            const int uright = ulims ? ulims[2 * i + 1] : 0;
            m_unpacked.emplace_back(uleft, uright);
        }
    }
    void initPacked(int pdims, const int* plims) {
        int packedSize = 1;
        for (int i = 0; i < pdims; ++i) {
            const int pleft = plims ? plims[2 * i + 0] : 0;
            const int pright = plims ? plims[2 * i + 1] : 0;
            m_packed.emplace_back(pleft, pright);
            packedSize *= abs(pleft - pright) + 1;
        }
        if (pdims == 1) {
            // Preserve packed array range if the packed component is 1-D
            m_packedDpi = m_packed.front();
        } else {
            m_packedDpi = VerilatedRange{packedSize - 1, 0};
        }
    }
    // CONSTRUCTORS
protected:
    friend class VerilatedScope;
    VerilatedVarProps(VerilatedVarType vltype, VerilatedVarFlags vlflags, int udims, int pdims)
        : m_magic{MAGIC}
        , m_vltype{vltype}
        , m_vlflags{vlflags} {
        // Only preallocate the ranges
        initUnpacked(udims, nullptr);
        initPacked(pdims, nullptr);
    }

public:
    class Unpacked {};
    // Without packed
    VerilatedVarProps(VerilatedVarType vltype, int vlflags)
        : m_magic{MAGIC}
        , m_vltype{vltype}
        , m_vlflags(VerilatedVarFlags(vlflags)) {}  // Need () or GCC 4.8 false warning

    VerilatedVarProps(VerilatedVarType vltype, int vlflags, Unpacked, int udims, const int* ulims)
        : m_magic{MAGIC}
        , m_vltype{vltype}
        , m_vlflags(VerilatedVarFlags(vlflags)) {  // Need () or GCC 4.8 false warning
        initUnpacked(udims, ulims);
    }
    // With packed
    class Packed {};
    VerilatedVarProps(VerilatedVarType vltype, int vlflags, Packed, int pdims, const int* plims)
        : m_magic{MAGIC}
        , m_vltype{vltype}
        , m_vlflags(VerilatedVarFlags(vlflags)) {  // Need () or GCC 4.8 false warning
        initPacked(pdims, plims);
    }
    VerilatedVarProps(VerilatedVarType vltype, int vlflags, Unpacked, int udims, const int* ulims,
                      Packed, int pdims, const int* plims)
        : m_magic{MAGIC}
        , m_vltype{vltype}
        , m_vlflags(VerilatedVarFlags(vlflags)) {  // Need () or GCC 4.8 false warning
        initUnpacked(udims, ulims);
        initPacked(pdims, plims);
    }

    ~VerilatedVarProps() = default;
    // METHODS
    bool magicOk() const { return m_magic == MAGIC; }
    VerilatedVarType vltype() const VL_MT_SAFE { return m_vltype; }
    VerilatedVarFlags vldir() const {
        return static_cast<VerilatedVarFlags>(static_cast<int>(m_vlflags) & VLVF_MASK_DIR);
    }
    uint32_t entSize() const VL_MT_SAFE;
    uint32_t entBits() const VL_MT_SAFE {
        uint32_t bits = 1;
        for (auto it : m_packed) bits *= it.elements();
        return bits;
    }
    bool isPublicRW() const { return ((m_vlflags & VLVF_PUB_RW) != 0); }
    bool isForceable() const { return ((m_vlflags & VLVF_FORCEABLE) != 0); }
    bool isContinuously() const { return ((m_vlflags & VLVF_CONTINUOUSLY) != 0); }
    // DPI compatible C standard layout
    bool isDpiCLayout() const { return ((m_vlflags & VLVF_DPI_CLAY) != 0); }
    bool isSigned() const { return ((m_vlflags & VLVF_SIGNED) != 0); }
    bool isBitVar() const { return ((m_vlflags & VLVF_BITVAR) != 0); }
    int udims() const VL_MT_SAFE { return m_unpacked.size(); }
    int pdims() const VL_MT_SAFE { return m_packed.size(); }
    int dims() const VL_MT_SAFE { return pdims() + udims(); }
    const std::vector<VerilatedRange>& packedRanges() const VL_MT_SAFE { return m_packed; }
    const std::vector<VerilatedRange>& unpackedRanges() const VL_MT_SAFE { return m_unpacked; }
    const VerilatedRange* range(int dim) const VL_MT_SAFE {
        if (dim < udims())
            return &m_unpacked[dim];
        else if (dim < dims())
            return &m_packed[dim - udims()];
        else
            return nullptr;
    }
    // DPI accessors (with packed dimensions flattened!)
    int left(int dim) const VL_MT_SAFE {
        return dim == 0                                ? m_packedDpi.left()
               : VL_LIKELY(dim >= 1 && dim <= udims()) ? m_unpacked[dim - 1].left()
                                                       : 0;
    }
    int right(int dim) const VL_MT_SAFE {
        return dim == 0                                ? m_packedDpi.right()
               : VL_LIKELY(dim >= 1 && dim <= udims()) ? m_unpacked[dim - 1].right()
                                                       : 0;
    }
    int low(int dim) const VL_MT_SAFE {
        return dim == 0                                ? m_packedDpi.low()
               : VL_LIKELY(dim >= 1 && dim <= udims()) ? m_unpacked[dim - 1].low()
                                                       : 0;
    }
    int high(int dim) const VL_MT_SAFE {
        return dim == 0                                ? m_packedDpi.high()
               : VL_LIKELY(dim >= 1 && dim <= udims()) ? m_unpacked[dim - 1].high()
                                                       : 0;
    }
    int increment(int dim) const {
        return dim == 0                                ? m_packedDpi.increment()
               : VL_LIKELY(dim >= 1 && dim <= udims()) ? m_unpacked[dim - 1].increment()
                                                       : 0;
    }
    int elements(int dim) const VL_MT_SAFE {
        return dim == 0                                ? m_packedDpi.elements()
               : VL_LIKELY(dim >= 1 && dim <= udims()) ? m_unpacked[dim - 1].elements()
                                                       : 0;
    }
    // Total size in bytes (note DPI limited to 4GB)
    size_t totalSize() const;
    // Adjust a data pointer to access a given array element, NULL if something goes bad
    void* datapAdjustIndex(void* datap, int dim, int indx) const VL_MT_SAFE;
};

//===========================================================================
// Verilator DPI open array variable

class VerilatedDpiOpenVar final {
    // MEMBERS
    const VerilatedVarProps* const m_propsp;  // Variable properties
    void* const m_datap;  // Location of data (local to thread always, so safe)
public:
    // CONSTRUCTORS
    VerilatedDpiOpenVar(const VerilatedVarProps* propsp, void* datap)
        : m_propsp{propsp}
        , m_datap{datap} {}
    VerilatedDpiOpenVar(const VerilatedVarProps* propsp, const void* datap)
        : m_propsp{propsp}
        , m_datap{const_cast<void*>(datap)} {}
    ~VerilatedDpiOpenVar() = default;
    // METHODS
    void* datap() const VL_MT_SAFE { return m_datap; }
    // METHODS - from VerilatedVarProps
    bool magicOk() const { return m_propsp->magicOk(); }
    VerilatedVarType vltype() const { return m_propsp->vltype(); }
    bool isDpiStdLayout() const { return m_propsp->isDpiCLayout(); }
    int entBits() const { return m_propsp->entBits(); }
    int udims() const VL_MT_SAFE { return m_propsp->udims(); }
    int left(int dim) const VL_MT_SAFE { return m_propsp->left(dim); }
    int right(int dim) const VL_MT_SAFE { return m_propsp->right(dim); }
    int low(int dim) const { return m_propsp->low(dim); }
    int high(int dim) const { return m_propsp->high(dim); }
    int increment(int dim) const { return m_propsp->increment(dim); }
    int elements(int dim) const { return m_propsp->elements(dim); }
    size_t totalSize() const { return m_propsp->totalSize(); }
    void* datapAdjustIndex(void* datap, int dim, int indx) const VL_MT_SAFE {
        return m_propsp->datapAdjustIndex(datap, dim, indx);
    }
};

//===========================================================================
// Verilator variable
// Thread safety: Assume is constructed only with model, then any number of readers

class VerilatedVar final : public VerilatedVarProps {
    // MEMBERS
    void* const m_datap;  // Location of data
    const char* const m_namep;  // Name - slowpath
protected:
    const bool m_isParam;
    friend class VerilatedScope;
    // CONSTRUCTORS
    VerilatedVar(const char* namep, void* datap, VerilatedVarType vltype,
                 VerilatedVarFlags vlflags, int udims, int pdims, bool isParam)
        : VerilatedVarProps{vltype, vlflags, udims, pdims}
        , m_datap{datap}
        , m_namep{namep}
        , m_isParam{isParam} {}

public:
    ~VerilatedVar() = default;
    // ACCESSORS
    void* datap() const { return m_datap; }
    const char* name() const { return m_namep; }
    bool isParam() const { return m_isParam; }
};

#endif  // Guard
