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
/// \brief Verilated VPI implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use the VPI.
///
/// Use "verilator --vpi" to add this to the Makefile for the linker.
///
/// For documentation on the exported functions (named vpi_*) that are
/// implemented here, refer to the IEEE DPI chapter.
///
//=========================================================================

#include "verilatedos.h"
#define VERILATOR_VERILATED_VPI_CPP_

#include "verilated.h"
#include "verilated_imp.h"
#include "verilated_vpi.h"

#include "vltstd/vpi_user.h"

#include <cstdarg>
#include <cstdio>
#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

//======================================================================
// Internal constants

#define VL_DEBUG_IF_PLI VL_DEBUG_IF
constexpr unsigned VL_VPI_LINE_SIZE_ = 8192;

//======================================================================
// Internal macros

#define VL_VPI_INTERNAL_ VerilatedVpiImp::error_info()->setMessage(vpiInternal)->setMessage
#define VL_VPI_SYSTEM_ VerilatedVpiImp::error_info()->setMessage(vpiSystem)->setMessage
#define VL_VPI_ERROR_ VerilatedVpiImp::error_info()->setMessage(vpiError)->setMessage
#define VL_VPI_WARNING_ VerilatedVpiImp::error_info()->setMessage(vpiWarning)->setMessage
#define VL_VPI_NOTICE_ VerilatedVpiImp::error_info()->setMessage(vpiNotice)->setMessage
#define VL_VPI_ERROR_RESET_ VerilatedVpiImp::error_info()->resetError

// Not supported yet
#define VL_VPI_UNIMP_() \
    (VL_VPI_ERROR_(__FILE__, __LINE__, Verilated::catName("Unsupported VPI function: ", __func__)))

//======================================================================
// Implementation

// Base VPI handled object
class VerilatedVpio VL_NOT_FINAL {
    // CONSTANTS
    // Magic value stored in front of object to detect double free etc
    // Must be odd, as aligned pointer can never be odd
    static constexpr uint32_t activeMagic() VL_PURE { return 0xfeed100f; }

    // MEM MANGLEMENT
    // Internal note: Globals may multi-construct, see verilated.cpp top.
    static thread_local uint8_t* t_freeHeadp;

public:
    // CONSTRUCTORS
    VerilatedVpio() = default;
    virtual ~VerilatedVpio() = default;
    static void* operator new(size_t size) VL_MT_SAFE {
        // We new and delete tons of vpi structures, so keep them around
        // To simplify our free list, we use a size large enough for all derived types
        // We reserve word zero for the next pointer, as that's safer in case a
        // dangling reference to the original remains around.
        static constexpr size_t CHUNK_SIZE = 256;
        if (VL_UNCOVERABLE(size > CHUNK_SIZE))
            VL_FATAL_MT(__FILE__, __LINE__, "", "increase CHUNK_SIZE");
        if (VL_LIKELY(t_freeHeadp)) {
            uint8_t* const newp = t_freeHeadp;
            t_freeHeadp = *(reinterpret_cast<uint8_t**>(newp));
            *(reinterpret_cast<uint32_t*>(newp)) = activeMagic();
            return newp + 8;
        }
        // +8: 8 bytes for next
        uint8_t* newp = reinterpret_cast<uint8_t*>(::operator new(CHUNK_SIZE + 8));
        *(reinterpret_cast<uint32_t*>(newp)) = activeMagic();
        return newp + 8;
    }
    static void operator delete(void* obj, size_t /*size*/) VL_MT_SAFE {
        uint8_t* const oldp = (static_cast<uint8_t*>(obj)) - 8;
        if (VL_UNLIKELY(*(reinterpret_cast<uint32_t*>(oldp)) != activeMagic())) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_release_handle() called on same object twice, or on non-Verilator "
                        "VPI object");
        }
#ifdef VL_VPI_IMMEDIATE_FREE  // Define to aid in finding leaky handles
        ::operator delete(oldp);
#else
        *(reinterpret_cast<void**>(oldp)) = t_freeHeadp;
        t_freeHeadp = oldp;
#endif
    }
    // MEMBERS
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpio* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpio*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    vpiHandle castVpiHandle() { return reinterpret_cast<vpiHandle>(this); }
    // ACCESSORS
    virtual const char* name() const { return "<null>"; }
    virtual const char* fullname() const { return "<null>"; }
    virtual const char* defname() const { return "<null>"; }
    virtual uint32_t type() const { return 0; }
    virtual uint32_t constType() const { return vpiUndefined; }
    virtual uint32_t size() const { return 0; }
    virtual const VerilatedRange* rangep() const { return nullptr; }
    virtual vpiHandle dovpi_scan() { return nullptr; }
    virtual PLI_INT32 dovpi_remove_cb() { return 0; }
};

class VerilatedVpioReasonCb final : public VerilatedVpio {
    // A handle to a timed or non-timed callback created with vpi_register_cb
    // User can call vpi_remove_cb or vpi_release_handle on it
    const uint64_t m_id;  // Unique id/sequence number to find schedule's event
    const QData m_time;  // Scheduled time, or 0 = not timed
    const PLI_INT32 m_reason;  // VPI callback reason code

public:
    // cppcheck-suppress uninitVar  // m_value
    VerilatedVpioReasonCb(uint64_t id, QData time, PLI_INT32 reason)
        : m_id{id}
        , m_time{time}
        , m_reason{reason} {}
    ~VerilatedVpioReasonCb() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioReasonCb* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioReasonCb*>(reinterpret_cast<VerilatedVpioReasonCb*>(h));
    }
    uint32_t type() const override { return vpiCallback; }
    PLI_INT32 dovpi_remove_cb() override;
};

class VerilatedVpioConst final : public VerilatedVpio {
    const int32_t m_num;

public:
    explicit VerilatedVpioConst(int32_t num)
        : m_num{num} {}
    ~VerilatedVpioConst() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioConst* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioConst*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiConstant; }
    uint32_t constType() const override { return vpiDecConst; }
    int32_t num() const { return m_num; }
};

class VerilatedVpioVarBase VL_NOT_FINAL : public VerilatedVpio {
protected:
    const VerilatedVar* m_varp = nullptr;
    const VerilatedScope* m_scopep = nullptr;

    // Usually empty, only gets filled when fullname() is called. Has to be stored as a member so
    // the char* that fullname() returns is not a temporary.
    mutable std::string m_fullname;

    int32_t m_indexedDim = -1;
    const VerilatedRange* get_range() const { return m_varp->range(m_indexedDim + 1); }

public:
    VerilatedVpioVarBase(const VerilatedVar* varp, const VerilatedScope* scopep)
        : m_varp{varp}
        , m_scopep{scopep} {}
    explicit VerilatedVpioVarBase(const VerilatedVpioVarBase* varp) {
        if (varp) {
            m_varp = varp->m_varp;
            m_scopep = varp->m_scopep;
            m_indexedDim = varp->m_indexedDim;
        }
    }
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioVarBase* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioVarBase*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    const VerilatedVar* varp() const { return m_varp; }
    const VerilatedScope* scopep() const { return m_scopep; }
    // Returns the number of the currently indexed dimension (starting at -1 for none).
    int32_t indexedDim() const { return m_indexedDim; }
    // Returns whether the currently indexed dimension is unpacked.
    bool isIndexedDimUnpacked() const { return indexedDim() + 1 < varp()->udims(); }
    // Returns a maximum accessible dimension number, counting only unpacked dimensions
    // (if onlyUnpacked == true), or both unpacked + packed.
    int32_t maxDim(bool onlyUnpacked) const {
        return onlyUnpacked ? varp()->udims() - 1 : varp()->dims() - 1;
    }
    // Returns a number of elements in the array, stopping at the unpacked-packed boundary.
    uint32_t size() const override {
        const int maxDimNum = maxDim(isIndexedDimUnpacked());
        int size = 1;
        for (int dim = indexedDim() + 1; dim <= maxDimNum; ++dim)
            size *= varp()->range(dim)->elements();
        return size;
    }
    // If the array is unpacked, returns the bitsize of a single underlying packed element.
    // If the array is packed, returns the bitsize of the whole array.
    uint32_t bitSize() const {
        if (isIndexedDimUnpacked())
            return varp()->entBits();
        else
            return size();
    }
    const VerilatedRange* rangep() const override { return get_range(); }
    const char* name() const override { return m_varp->name(); }
    const char* fullname() const override {
        if (m_fullname.empty()) m_fullname = std::string{m_scopep->name()} + '.' + m_varp->name();
        return m_fullname.c_str();
    }
    virtual void* varDatap() const { return m_varp->datap(); }
    CData* varCDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_UINT8););
        return reinterpret_cast<CData*>(varDatap());
    }
    SData* varSDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_UINT16););
        return reinterpret_cast<SData*>(varDatap());
    }
    IData* varIDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_UINT32););
        return reinterpret_cast<IData*>(varDatap());
    }
    QData* varQDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_UINT64););
        return reinterpret_cast<QData*>(varDatap());
    }
    EData* varEDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_WDATA););
        return reinterpret_cast<EData*>(varDatap());
    }
    double* varRealDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_REAL););
        return reinterpret_cast<double*>(varDatap());
    }
    std::string* varStringDatap() const {
        VL_DEBUG_IFDEF(assert(varp()->vltype() == VLVT_STRING););
        return reinterpret_cast<std::string*>(varDatap());
    }
    virtual uint32_t bitOffset() const { return 0; }
};

class VerilatedVpioParam final : public VerilatedVpioVarBase {
public:
    VerilatedVpioParam(const VerilatedVar* varp, const VerilatedScope* scopep)
        : VerilatedVpioVarBase{varp, scopep} {}
    ~VerilatedVpioParam() override = default;

    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioParam* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioParam*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiParameter; }
    uint32_t constType() const override {
        switch (m_varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return vpiDecConst;
        case VLVT_STRING: return vpiStringConst;
        case VLVT_REAL: return vpiRealConst;
        default: return vpiUndefined;
        }
    }
};

class VerilatedVpioRange final : public VerilatedVpio {
    const VerilatedRange* const m_rangep;

public:
    explicit VerilatedVpioRange(const VerilatedRange* rangep)
        : m_rangep{rangep} {}
    ~VerilatedVpioRange() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioRange* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioRange*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiRange; }
    uint32_t size() const override { return m_rangep->elements(); }
    const VerilatedRange* rangep() const override { return m_rangep; }
};

class VerilatedVpioRangeIter final : public VerilatedVpio {
    const std::vector<VerilatedRange> m_ranges;
    std::vector<VerilatedRange>::const_iterator m_iter;

public:
    explicit VerilatedVpioRangeIter(const std::vector<VerilatedRange>& ranges)
        : m_ranges{ranges} {
        m_iter = m_ranges.begin();
    }
    ~VerilatedVpioRangeIter() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioRangeIter* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioRangeIter*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiIterator; }
    vpiHandle dovpi_scan() override {
        if (VL_UNLIKELY(m_iter == m_ranges.end())) {
            delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
            return nullptr;
        }
        VerilatedRange* const rangep = new VerilatedRange{*m_iter};
        ++m_iter;
        return ((new VerilatedVpioRange{rangep})->castVpiHandle());
    }
};

class VerilatedVpioScope VL_NOT_FINAL : public VerilatedVpio {
protected:
    const VerilatedScope* const m_scopep;
    bool m_toplevel = false;
    const char* m_name;
    const char* m_fullname;
    const char* m_defname;

public:
    explicit VerilatedVpioScope(const VerilatedScope* scopep)
        : m_scopep{scopep} {
        m_fullname = m_scopep->name();
        if (std::strncmp(m_fullname, "TOP.", 4) == 0) m_fullname += 4;
        m_name = m_scopep->identifier();
        m_defname = m_scopep->defname();
    }
    ~VerilatedVpioScope() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioScope* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioScope*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiGenScope; }
    const VerilatedScope* scopep() const { return m_scopep; }
    const char* name() const override { return m_name; }
    const char* fullname() const override { return m_fullname; }
    const char* defname() const override { return m_defname; }
    bool toplevel() const { return m_toplevel; }
};

class VerilatedVpioVar VL_NOT_FINAL : public VerilatedVpioVarBase {
    uint8_t* m_prevDatap = nullptr;  // Previous value of data, for cbValueChange
    union {
        uint8_t u8[4];
        uint32_t u32;
    } m_mask;  // memoized variable mask
    uint32_t m_entSize = 0;  // memoized variable size
    uint32_t m_bitOffset = 0;

protected:
    void* m_varDatap = nullptr;  // varp()->datap() adjusted for array entries
    std::vector<int32_t> m_index;

public:
    VerilatedVpioVar(const VerilatedVar* varp, const VerilatedScope* scopep)
        : VerilatedVpioVarBase{varp, scopep} {
        m_mask.u32 = VL_MASK_I(varp->entBits());
        m_entSize = varp->entSize();
        m_varDatap = varp->datap();
    }
    explicit VerilatedVpioVar(const VerilatedVpioVar* varp)
        : VerilatedVpioVarBase{varp} {
        if (varp) {
            m_mask.u32 = varp->m_mask.u32;
            m_entSize = varp->m_entSize;
            m_varDatap = varp->m_varDatap;
            m_index = varp->m_index;
            // Not copying m_prevDatap, must be nullptr
        } else {
            m_mask.u32 = 0;
        }
    }
    ~VerilatedVpioVar() override {
        if (m_prevDatap) VL_DO_CLEAR(delete[] m_prevDatap, m_prevDatap = nullptr);
    }
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioVar* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioVar*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t bitOffset() const override { return m_bitOffset; }
    uint32_t mask() const { return m_mask.u32; }
    uint8_t mask_byte(int idx) const { return m_mask.u8[idx & 3]; }
    uint32_t entSize() const { return m_entSize; }
    const std::vector<int32_t>& index() const { return m_index; }
    VerilatedVpioVar* withIndex(int32_t index) const {
        if (VL_UNLIKELY(indexedDim() + 1 >= varp()->dims())) return nullptr;

        auto ret = new VerilatedVpioVar{this};
        ret->m_index.push_back(index);
        ret->m_indexedDim++;

        int chunkSize = 1;
        for (int dim = maxDim(isIndexedDimUnpacked()); dim > indexedDim() + 1; dim--)
            chunkSize *= varp()->range(dim)->elements();

        if (isIndexedDimUnpacked())
            ret->m_varDatap = (static_cast<uint8_t*>(ret->m_varDatap))
                              + entSize() * chunkSize * (index - get_range()->low());
        else
            ret->m_bitOffset += chunkSize * (index - get_range()->low());

        return ret;
    }
    uint32_t type() const override {
        uint32_t type;
        // TODO have V3EmitCSyms.cpp put vpiType directly into constant table
        switch (varp()->vltype()) {
        case VLVT_REAL: type = vpiRealVar; break;
        case VLVT_STRING: type = vpiStringVar; break;
        default: type = varp()->isBitVar() ? vpiBitVar : vpiReg; break;
        }
        if (isIndexedDimUnpacked())
            return vpiRegArray;
        else
            return type;
    }
    const char* fullname() const override {
        static thread_local std::string t_out;
        t_out = std::string{scopep()->name()} + "." + name();
        for (auto idx : index()) t_out += "[" + std::to_string(idx) + "]";
        return t_out.c_str();
    }
    void* prevDatap() const { return m_prevDatap; }
    void* varDatap() const override { return m_varDatap; }
    void createPrevDatap() {
        if (VL_UNLIKELY(!m_prevDatap)) {
            m_prevDatap = new uint8_t[entSize()];
            std::memcpy(prevDatap(), m_varDatap, entSize());
        }
    }
};

class VerilatedVpioVarIter final : public VerilatedVpio {
    const VerilatedScope* const m_scopep;
    VerilatedVarNameMap::const_iterator m_it;
    bool m_started = false;
    const VerilatedScope* m_topscopep = nullptr;
    bool m_onlyParams;

public:
    explicit VerilatedVpioVarIter(const VerilatedVpioScope* vop, bool onlyParams = false)
        : m_scopep{vop->scopep()}
        , m_onlyParams{onlyParams} {
        if (VL_UNLIKELY(vop->toplevel()))
            // This is a toplevel, so get TOP scope to search for ports during vpi_scan.
            m_topscopep = Verilated::threadContextp()->scopeFind("TOP");
    }
    ~VerilatedVpioVarIter() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioVarIter* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioVarIter*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiIterator; }
    vpiHandle dovpi_scan() override {
        if (VL_UNLIKELY(!m_scopep->varsp())) {
            delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
            return nullptr;  // End of list - only one deep
        }
        while (true) {
            const VerilatedVarNameMap* const varsp = m_scopep->varsp();
            if (VL_UNLIKELY(!m_started)) {
                m_it = varsp->begin();
                m_started = true;
            } else if (VL_UNLIKELY(m_it == varsp->end())) {
                delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
                return nullptr;
            } else {
                ++m_it;
            }
            if (VL_UNLIKELY(m_it == varsp->end())) {
                delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
                return nullptr;
            }
            if (m_onlyParams && !m_it->second.isParam()) continue;
            if (VL_UNLIKELY(m_topscopep)) {
                if (const VerilatedVar* topvarp = m_topscopep->varFind(m_it->second.name())) {
                    if (topvarp->isParam()) {
                        return ((new VerilatedVpioParam{topvarp, m_topscopep})->castVpiHandle());
                    } else {
                        return ((new VerilatedVpioVar{topvarp, m_topscopep})->castVpiHandle());
                    }
                }
            }
            if (m_it->second.isParam()) {
                return ((new VerilatedVpioParam{&(m_it->second), m_scopep})->castVpiHandle());
            } else {
                return ((new VerilatedVpioVar{&(m_it->second), m_scopep})->castVpiHandle());
            }
        }
    }
};

class VerilatedVpioRegIter final : public VerilatedVpio {
    VerilatedVpioVar* m_var;
    std::vector<VerilatedRange> m_ranges;
    std::vector<int> m_nextIndex;
    const int32_t m_maxDim;

public:
    explicit VerilatedVpioRegIter(const VerilatedVpioVar* vop)
        : m_var{new VerilatedVpioVar(vop)}
        , m_maxDim{vop->varp()->udims() - 1} {
        for (auto it = vop->indexedDim() + 1; it <= m_maxDim; ++it)
            m_ranges.push_back(*vop->varp()->range(it));
        for (auto it : m_ranges) m_nextIndex.push_back(it.right());
    }
    ~VerilatedVpioRegIter() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioRegIter* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioRegIter*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiIterator; }
    vpiHandle dovpi_scan() override {
        if (VL_UNLIKELY(m_var->indexedDim() >= m_maxDim)) {
            // Trying to iterate over a non-array object
            delete this;
            return nullptr;
        }
        if (m_nextIndex.front() > m_ranges.front().high()
            || m_nextIndex.front() < m_ranges.front().low()) {
            // Finished iterating
            delete this;
            return nullptr;
        }

        VerilatedVpioVar* ret = m_var;
        for (auto it : m_nextIndex) ret = ret->withIndex(it);

        // Increase the index, pretending the dimensions are flattened
        for (int32_t it = m_ranges.size() - 1; it >= 0; it--) {
            m_nextIndex.at(it) += m_ranges.at(it).increment();
            if (m_nextIndex.at(it) <= m_ranges.at(it).high()
                && m_nextIndex.at(it) >= m_ranges.at(it).low())
                break;
            else if (it > 0)
                m_nextIndex.at(it) = m_ranges.at(it).right();
        }

        return ret->castVpiHandle();
    }
};

class VerilatedVpioModule final : public VerilatedVpioScope {

public:
    explicit VerilatedVpioModule(const VerilatedScope* modulep)
        : VerilatedVpioScope{modulep} {
        // Look for '.' not inside escaped identifier
        const std::string scopename = m_fullname;
        std::string::size_type pos = std::string::npos;
        size_t i = 0;
        while (i < scopename.length()) {
            if (scopename[i] == '\\') {
                while (i < scopename.length() && scopename[i] != ' ') ++i;
                ++i;  // Proc ' ', it should always be there. Then grab '.' on next cycle
            } else {
                while (i < scopename.length() && scopename[i] != '.') ++i;
                if (i < scopename.length()) pos = i++;
            }
        }
        if (VL_UNLIKELY(pos == std::string::npos)) m_toplevel = true;
    }
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioModule* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioModule*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiModule; }
};

class VerilatedVpioModuleIter final : public VerilatedVpio {
    const std::vector<const VerilatedScope*>* m_vec;
    std::vector<const VerilatedScope*>::const_iterator m_it;

public:
    explicit VerilatedVpioModuleIter(const std::vector<const VerilatedScope*>& vec)
        : m_vec{&vec} {
        m_it = m_vec->begin();
    }
    ~VerilatedVpioModuleIter() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioModuleIter* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioModuleIter*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiIterator; }
    vpiHandle dovpi_scan() override {
        while (true) {
            if (m_it == m_vec->end()) {
                delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
                return nullptr;
            }
            const VerilatedScope* const modp = *m_it++;
            const VerilatedScope::Type itype = modp->type();
            if (itype == VerilatedScope::SCOPE_MODULE) {
                return (new VerilatedVpioModule{modp})->castVpiHandle();
            }
        }
    }
};

class VerilatedVpioScopeIter final : public VerilatedVpio {
    const std::vector<const VerilatedScope*>* m_vec;
    std::vector<const VerilatedScope*>::const_iterator m_it;

public:
    explicit VerilatedVpioScopeIter(const std::vector<const VerilatedScope*>& vec)
        : m_vec{&vec} {
        m_it = m_vec->begin();
    }
    ~VerilatedVpioScopeIter() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioScopeIter* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioScopeIter*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiIterator; }
    vpiHandle dovpi_scan() override {
        while (true) {
            if (m_it == m_vec->end()) {
                delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
                return nullptr;
            }
            const VerilatedScope* const modp = *m_it++;
            const VerilatedScope::Type itype = modp->type();
            if (itype == VerilatedScope::SCOPE_OTHER) {
                return (new VerilatedVpioScope{modp})->castVpiHandle();
            } else if (itype == VerilatedScope::SCOPE_MODULE) {
                return (new VerilatedVpioModule{modp})->castVpiHandle();
            }
        }
    }
};

static const char* d_unit = "$unit";
class VerilatedVpioPackage final : public VerilatedVpioScope {
    std::string m_fullname_string;

public:
    explicit VerilatedVpioPackage(const VerilatedScope* modulep)
        : VerilatedVpioScope{modulep} {
        m_fullname_string = std::string{m_fullname} + "::";
        if (m_fullname_string == "\\$unit ::") m_fullname_string = "$unit::";

        if (strcmp(m_name, "\\$unit ") == 0) m_name = d_unit;
    }
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioPackage* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioPackage*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    const char* fullname() const override { return m_fullname_string.c_str(); }
    uint32_t type() const override { return vpiPackage; }
};

class VerilatedVpioInstanceIter final : public VerilatedVpio {
    const std::vector<const VerilatedScope*>* m_vec;
    std::vector<const VerilatedScope*>::const_iterator m_it;

public:
    explicit VerilatedVpioInstanceIter(const std::vector<const VerilatedScope*>& vec)
        : m_vec{&vec} {
        m_it = m_vec->begin();
    }
    ~VerilatedVpioInstanceIter() override = default;
    // cppcheck-suppress duplInheritedMember
    static VerilatedVpioInstanceIter* castp(vpiHandle h) {
        return dynamic_cast<VerilatedVpioInstanceIter*>(reinterpret_cast<VerilatedVpio*>(h));
    }
    uint32_t type() const override { return vpiIterator; }
    vpiHandle dovpi_scan() override {
        while (true) {
            if (m_it == m_vec->end()) {
                delete this;  // IEEE 37.2.2 vpi_scan at end does a vpi_release_handle
                return nullptr;
            }
            const VerilatedScope::Type itype = (*m_it)->type();
            const VerilatedScope* const modp = *m_it++;
            if (itype == VerilatedScope::SCOPE_MODULE) {
                return (new VerilatedVpioModule{modp})->castVpiHandle();
            }
            if (itype == VerilatedScope::SCOPE_PACKAGE) {
                return (new VerilatedVpioPackage{modp})->castVpiHandle();
            }
        }
    }
};

//======================================================================

using VerilatedPliCb = PLI_INT32 (*)(struct t_cb_data*);

class VerilatedVpiCbHolder final {
    // Holds information needed to call a callback
    uint64_t m_id;  // Unique id/sequence number to find schedule's event, 0 = invalid
    s_cb_data m_cbData;
    s_vpi_value m_value;
    VerilatedVpioVar m_varo;  // If a cbValueChange callback, the object we will return

public:
    // cppcheck-suppress uninitVar  // m_value
    VerilatedVpiCbHolder(uint64_t id, const s_cb_data* cbDatap, const VerilatedVpioVar* varop)
        : m_id{id}
        , m_cbData{*cbDatap}
        , m_varo{varop} {
        m_value.format = cbDatap->value ? cbDatap->value->format : vpiSuppressVal;
        m_cbData.value = &m_value;
        if (varop) {
            m_cbData.obj = m_varo.castVpiHandle();
            m_varo.createPrevDatap();
        } else {
            m_cbData.obj = nullptr;
        }
    }
    ~VerilatedVpiCbHolder() = default;
    VerilatedPliCb cb_rtnp() const { return m_cbData.cb_rtn; }
    s_cb_data* cb_datap() { return &m_cbData; }
    uint64_t id() const { return m_id; }
    bool invalid() const { return !m_id; }
    void invalidate() { m_id = 0; }
};

class VerilatedVpiPutHolder final {
    VerilatedVpioVar m_var;
    s_vpi_value m_value;
    union Storage {
        char init = 0;  // to ensure trivial constructor
        std::string str;
        std::vector<s_vpi_vecval> vec;
        ~Storage() noexcept {/* handled by VerilatedVpiPutHolder */};
    } m_storage{};

public:
    VerilatedVpiPutHolder(const VerilatedVpioVar* vop, p_vpi_value valuep)
        : m_var{vop} {
        m_value.format = valuep->format;
        switch (valuep->format) {
        case vpiBinStrVal:  // FALLTHRU
        case vpiOctStrVal:  // FALLTHRU
        case vpiDecStrVal:  // FALLTHRU
        case vpiHexStrVal:  // FALLTHRU
        case vpiStringVal: {
            new (&m_storage.str) std::string{valuep->value.str};
            m_value.value.str = const_cast<char*>(m_storage.str.c_str());
            break;
        }
        case vpiScalarVal: {
            m_value.value.scalar = valuep->value.scalar;
            break;
        }
        case vpiIntVal: {
            m_value.value.integer = valuep->value.integer;
            break;
        }
        case vpiRealVal: {
            m_value.value.real = valuep->value.real;
            break;
        }
        case vpiVectorVal: {
            size_t words = 0;
            switch (vop->varp()->vltype()) {
            case VLVT_UINT8:
            case VLVT_UINT16:
            case VLVT_UINT32: {
                words = 1;
                break;
            }
            case VLVT_UINT64: {
                words = 2;
                break;
            }
            case VLVT_WDATA: {
                words = VL_WORDS_I(vop->varp()->entBits());
                break;
            }
            default: break;
            }
            new (&m_storage.vec)
                std::vector<s_vpi_vecval>{valuep->value.vector, &valuep->value.vector[words]};
            m_value.value.vector = m_storage.vec.data();
            break;
        }
        }
    }

    VerilatedVpiPutHolder(VerilatedVpiPutHolder const& o)
        : m_var{o.m_var}
        , m_value{o.m_value} {
        switch (m_value.format) {
        case vpiBinStrVal:  // FALLTHRU
        case vpiOctStrVal:  // FALLTHRU
        case vpiDecStrVal:  // FALLTHRU
        case vpiHexStrVal:  // FALLTHRU
        case vpiStringVal: {
            new (&m_storage.str) std::string{o.m_storage.str};
            break;
        }
        case vpiVectorVal: {
            new (&m_storage.vec) std::vector<s_vpi_vecval>{o.m_storage.vec};
            break;
        }
        }
    }

    VerilatedVpiPutHolder(VerilatedVpiPutHolder&& o) noexcept
        : m_var{std::move(o.m_var)}
        , m_value{std::move(o.m_value)} {
        switch (m_value.format) {
        case vpiBinStrVal:  // FALLTHRU
        case vpiOctStrVal:  // FALLTHRU
        case vpiDecStrVal:  // FALLTHRU
        case vpiHexStrVal:  // FALLTHRU
        case vpiStringVal: {
            new (&m_storage.str) std::string{std::move(o.m_storage.str)};
            break;
        }
        case vpiVectorVal: {
            new (&m_storage.vec) std::vector<s_vpi_vecval>{std::move(o.m_storage.vec)};
            break;
        }
        }
    }

    ~VerilatedVpiPutHolder() noexcept {
        switch (m_value.format) {
        case vpiBinStrVal:  // FALLTHRU
        case vpiOctStrVal:  // FALLTHRU
        case vpiDecStrVal:  // FALLTHRU
        case vpiHexStrVal:  // FALLTHRU
        case vpiStringVal: m_storage.str.~basic_string(); break;
        case vpiVectorVal: m_storage.vec.~vector(); break;
        }
    }

    VerilatedVpioVar* varp() { return &m_var; }
    p_vpi_value valuep() { return &m_value; }

    static bool canInertialDelay(p_vpi_value valuep) {
        switch (valuep->format) {
        case vpiBinStrVal:  // FALLTHRU
        case vpiOctStrVal:  // FALLTHRU
        case vpiDecStrVal:  // FALLTHRU
        case vpiHexStrVal:  // FALLTHRU
        case vpiStringVal: {
            if (VL_UNLIKELY(!valuep->value.str)) return false;
            break;
        }
        case vpiScalarVal:  // FALLTHRU
        case vpiIntVal:  // FALLTHRU
        case vpiRealVal: break;
        case vpiVectorVal: {
            if (VL_UNLIKELY(!valuep->value.vector)) return false;
            break;
        }
        default: {
            return false;
        }
        }
        return true;
    }
};

struct VerilatedVpiTimedCbsCmp final {
    // Ordering sets keyed by time, then callback unique id
    bool operator()(const std::pair<QData, uint64_t>& a,
                    const std::pair<QData, uint64_t>& b) const {
        if (a.first < b.first) return true;
        if (a.first > b.first) return false;
        return a.second < b.second;
    }
};

class VerilatedVpiError;
void vl_vpi_put_word(const VerilatedVpioVar* vop, QData word, size_t bitCount, size_t addOffset);

class VerilatedVpiImp final {
    enum { CB_ENUM_MAX_VALUE = cbAtEndOfSimTime + 1 };  // Maximum callback reason
    using VpioCbList = std::list<VerilatedVpiCbHolder>;
    using VpioFutureCbs = std::map<std::pair<QData, uint64_t>, VerilatedVpiCbHolder>;

    // All only medium-speed, so use singleton function
    // Callbacks that are past or at current timestamp
    std::array<VpioCbList, CB_ENUM_MAX_VALUE> m_cbCurrentLists;
    VpioCbList m_cbCallList;  // List of callbacks currently being called by callCbs
    VpioFutureCbs m_futureCbs;  // Time based callbacks for future timestamps
    VpioFutureCbs m_nextCbs;  // cbNextSimTime callbacks
    std::list<VerilatedVpiPutHolder> m_inertialPuts;  // Pending vpi puts due to vpiInertialDelay
    VerilatedVpiError* m_errorInfop = nullptr;  // Container for vpi error info
    VerilatedAssertOneThread m_assertOne;  // Assert only called from single thread
    uint64_t m_nextCallbackId = 1;  // Id to identify callback
    bool m_evalNeeded = false;  // Model has had signals updated via vpi_put_value()

    static VerilatedVpiImp& s() {  // Singleton
        static VerilatedVpiImp s_s;
        return s_s;
    }

public:
    static void assertOneCheck() { s().m_assertOne.check(); }
    static uint64_t nextCallbackId() { return ++s().m_nextCallbackId; }

    static void cbCurrentAdd(uint64_t id, const s_cb_data* cb_data_p) {
        // The passed cb_data_p was property of the user, so need to recreate
        if (VL_UNCOVERABLE(cb_data_p->reason >= CB_ENUM_MAX_VALUE)) {
            VL_FATAL_MT(__FILE__, __LINE__, "", "vpi bb reason too large");
        }
        VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_register_cb reason=%d id=%" PRId64 " obj=%p\n",
                                    cb_data_p->reason, id, cb_data_p->obj););
        VerilatedVpioVar* varop = nullptr;
        if (cb_data_p->reason == cbValueChange) varop = VerilatedVpioVar::castp(cb_data_p->obj);
        s().m_cbCurrentLists[cb_data_p->reason].emplace_back(id, cb_data_p, varop);
    }
    static void cbFutureAdd(uint64_t id, const s_cb_data* cb_data_p, QData time) {
        // The passed cb_data_p was property of the user, so need to recreate
        VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_register_cb reason=%d id=%" PRId64 " time=%" PRIu64
                                    " obj=%p\n",
                                    cb_data_p->reason, id, time, cb_data_p->obj););
        s().m_futureCbs.emplace(std::piecewise_construct, std::forward_as_tuple(time, id),
                                std::forward_as_tuple(id, cb_data_p, nullptr));
    }
    static void cbNextAdd(uint64_t id, const s_cb_data* cb_data_p, QData time) {
        // The passed cb_data_p was property of the user, so need to recreate
        VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_register_cb reason=%d(NEXT) id=%" PRId64
                                    " time=%" PRIu64 " obj=%p\n",
                                    cb_data_p->reason, id, time, cb_data_p->obj););
        s().m_nextCbs.emplace(std::piecewise_construct, std::forward_as_tuple(time, id),
                              std::forward_as_tuple(id, cb_data_p, nullptr));
    }
    static void cbReasonRemove(uint64_t id, uint32_t reason, QData time) {
        // Id might no longer exist, if already removed due to call after event, or teardown
        // We do not remove it now as we may be iterating the list,
        // instead set to nullptr and will cleanup later
        // Remove from cbCurrent queue
        for (auto& ir : s().m_cbCurrentLists[reason]) {
            if (ir.id() == id) {
                ir.invalidate();
                return;  // Once found, it won't also be in m_cbCallList, m_futureCbs, or m_nextCbs
            }
        }
        for (auto& ir : s().m_cbCallList) {
            if (ir.id() == id) {
                ir.invalidate();
                return;  // Once found, it won't also be in m_futureCbs or m_nextCbs
            }
        }
        {  // Remove from cbFuture queue
            const auto it = s().m_futureCbs.find(std::make_pair(time, id));
            if (it != s().m_futureCbs.end()) {
                it->second.invalidate();
                return;
            }
        }
        {  // Remove from cbNext
            const auto it = s().m_nextCbs.find(std::make_pair(time, id));
            if (it != s().m_nextCbs.end()) {
                it->second.invalidate();
                return;
            }
        }
    }
    static void moveFutureCbs() VL_MT_UNSAFE_ONE {
        // For any events past current time, move from cbFuture queue to cbCurrent queue
        if (s().m_futureCbs.empty() && s().m_nextCbs.empty()) return;
        // VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: moveFutureCbs\n"); dumpCbs(); );
        const QData time = VL_TIME_Q();
        for (auto it = s().m_futureCbs.begin();  //
             VL_UNLIKELY(it != s().m_futureCbs.end() && it->first.first <= time);) {
            VerilatedVpiCbHolder& hor = it->second;
            const auto last_it = it;
            ++it;
            if (VL_UNLIKELY(!hor.invalid())) {
                VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: moveFutureCbs id=%" PRId64 "\n", hor.id()););
                s().m_cbCurrentLists[hor.cb_datap()->reason].emplace_back(hor);
            }
            s().m_futureCbs.erase(last_it);
        }
        for (auto it = s().m_nextCbs.begin();  //
             VL_UNLIKELY(it != s().m_nextCbs.end() && it->first.first < time);) {
            VerilatedVpiCbHolder& hor = it->second;
            const auto last_it = it;
            ++it;
            if (VL_UNLIKELY(!hor.invalid())) {
                VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: moveFutureCbs id=%" PRId64 "\n", hor.id()););
                s().m_cbCurrentLists[hor.cb_datap()->reason].emplace_back(hor);
            }
            s().m_nextCbs.erase(last_it);
        }
    }
    static QData cbNextDeadline() {
        const auto it = s().m_futureCbs.cbegin();
        if (VL_LIKELY(it != s().m_futureCbs.cend())) return it->first.first;
        return ~0ULL;  // maxquad
    }
    static bool hasCbs(const uint32_t reason) VL_MT_UNSAFE_ONE {
        return !s().m_cbCurrentLists[reason].empty();
    }
    static bool callCbs(const uint32_t reason) VL_MT_UNSAFE_ONE {
        VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: callCbs reason=%u\n", reason););
        assertOneCheck();
        moveFutureCbs();
        if (s().m_cbCurrentLists[reason].empty()) return false;
        // Iterate on old list, making new list empty, to prevent looping over newly added elements
        std::swap(s().m_cbCurrentLists[reason], s().m_cbCallList);
        bool called = false;
        for (VerilatedVpiCbHolder& ihor : s().m_cbCallList) {
            // cbReasonRemove sets to nullptr, so we know on removal the old end() will still exist
            if (VL_LIKELY(!ihor.invalid())) {  // Not deleted earlier
                VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: reason_callback reason=%d id=%" PRId64 "\n",
                                            reason, ihor.id()););
                ihor.invalidate();  // Timed callbacks are one-shot
                (ihor.cb_rtnp())(ihor.cb_datap());
                called = true;
            }
        }
        s().m_cbCallList.clear();
        return called;
    }
    static bool callValueCbs() VL_MT_UNSAFE_ONE {
        assertOneCheck();
        VpioCbList& cbObjList = s().m_cbCurrentLists[cbValueChange];
        bool called = false;
        std::set<VerilatedVpioVar*> update;  // set of objects to update after callbacks
        if (cbObjList.empty()) return called;
        const auto last = std::prev(cbObjList.end());  // prevent looping over newly added elements
        for (auto it = cbObjList.begin(); true;) {
            // cbReasonRemove sets to nullptr, so we know on removal the old end() will still exist
            const bool was_last = it == last;
            if (VL_UNLIKELY(it->invalid())) {  // Deleted earlier, cleanup
                it = cbObjList.erase(it);
                if (was_last) break;
                continue;
            }
            VerilatedVpiCbHolder& ho = *it++;
            VerilatedVpioVar* const varop
                = reinterpret_cast<VerilatedVpioVar*>(ho.cb_datap()->obj);
            void* const newDatap = varop->varDatap();
            void* const prevDatap = varop->prevDatap();  // Was malloced when we added the callback
            VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: value_test %s v[0]=%d/%d %p %p\n",
                                        varop->fullname(), *(static_cast<CData*>(newDatap)),
                                        *(static_cast<CData*>(prevDatap)), newDatap, prevDatap););
            if (std::memcmp(prevDatap, newDatap, varop->entSize()) != 0) {
                VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: value_callback %" PRId64 " %s v[0]=%d\n",
                                            ho.id(), varop->fullname(),
                                            *(static_cast<CData*>(newDatap))););
                update.insert(varop);
                vpi_get_value(ho.cb_datap()->obj, ho.cb_datap()->value);
                (ho.cb_rtnp())(ho.cb_datap());
                called = true;
            }
            if (was_last) break;
        }
        for (const VerilatedVpioVar* const ip : update) {
            std::memcpy(ip->prevDatap(), ip->varDatap(), ip->entSize());
        }
        return called;
    }
    static void dumpCbs() VL_MT_UNSAFE_ONE;
    static VerilatedVpiError* error_info() VL_MT_UNSAFE_ONE;  // getter for vpi error info
    static bool evalNeeded() { return s().m_evalNeeded; }
    static void evalNeeded(bool evalNeeded) { s().m_evalNeeded = evalNeeded; }
    static void inertialDelay(const VerilatedVpioVar* vop, p_vpi_value valuep) {
        s().m_inertialPuts.emplace_back(vop, valuep);
    }
    static void doInertialPuts() {
        for (auto& it : s().m_inertialPuts) {
            vpi_put_value(it.varp()->castVpiHandle(), it.valuep(), nullptr, vpiNoDelay);
        }
        s().m_inertialPuts.clear();
    }
    static auto getForceControlSignals(const VerilatedVpioVarBase* vop);

    // Used in the deleter of vopGuard_t, which is invoked upon
    // destruction of the return value of getForceControlSignals.
    // This means that it is called at the end of vpi_get_value whenever the signal
    // is forceable and at the end of vpi_put_value whenever the signal is both forceable and
    // either vpiForceFlag or vpiReleaseFlag is used.
    // Because it is always automatically called at the end, it should not
    // erase any previously issued errors or warnings.
    static void releaseWithoutErrorReset(vpiHandle object) {
        VerilatedVpiImp::assertOneCheck();
        VerilatedVpio* const vop = VerilatedVpio::castp(object);
        VL_DO_DANGLING(delete vop, vop);
    }

    static void releaseVop(VerilatedVpioVar* vop) {
        releaseWithoutErrorReset(vop->castVpiHandle());
    }

    using vopGuard_t = std::unique_ptr<VerilatedVpioVar, decltype(&VerilatedVpiImp::releaseVop)>;

    static std::size_t vlTypeSize(VerilatedVarType vltype);
    static void setAllBitsToValue(const VerilatedVpioVar* vop, uint8_t bitValue) {
        assert(bitValue == 0 || bitValue == 1);
        const uint64_t word = (bitValue == 1) ? -1ULL : 0ULL;
        const std::size_t wordSize = vlTypeSize(vop->varp()->vltype());
        assert(wordSize > 0);
        const uint32_t varBits = vop->bitSize();
        const std::size_t numChunks = (varBits / wordSize);
        for (std::size_t i{0}; i < numChunks; ++i) {
            vl_vpi_put_word(vop, word, wordSize, i * wordSize);
        }
        // addOffset == varBits would trigger assertion in vl_vpi_var_access_info even if
        // bitCount == 0, so first check if there is a remainder
        if (varBits % wordSize != 0)
            vl_vpi_put_word(vop, word, varBits % wordSize, numChunks * wordSize);
    }

    // Recreates the __VforceRd signal's data vector, since __VforceRd is not publicly accessible
    // in Verilated code.
    template <typename T>
    static std::vector<T>
    createReadDataVector(const void* const baseSignalDatap,
                         const std::pair<const void*, const void*> forceControlDatap,
                         const std::size_t bitCount) {
        const void* const forceEnableDatap = forceControlDatap.first;
        const void* const forceValueDatap = forceControlDatap.second;
        assert(bitCount > 0);
        const std::size_t numWords = (bitCount + (8 * sizeof(T)) - 1) / (8 * sizeof(T));  // Ceil
        std::vector<T> readData(numWords);
        for (std::size_t i{0}; i < numWords; ++i) {
            const T forceEnableWord = reinterpret_cast<const T*>(forceEnableDatap)[i];
            const T forceValueWord = reinterpret_cast<const T*>(forceValueDatap)[i];
            const T baseSignalWord = reinterpret_cast<const T*>(baseSignalDatap)[i];
            const T readDataWord
                = (forceEnableWord & forceValueWord) | (~forceEnableWord & baseSignalWord);
            readData[i] = readDataWord;
        }
        return readData;
    }
};

//======================================================================
// Statics
// Internal note: Globals may multi-construct, see verilated.cpp top.

thread_local uint8_t* VerilatedVpio::t_freeHeadp = nullptr;

//======================================================================
// VerilatedVpiError
// Internal container for vpi error info

class VerilatedVpiError final {
    t_vpi_error_info m_errorInfo;
    bool m_flag = false;
    char m_buff[VL_VPI_LINE_SIZE_];
    void setError(PLI_BYTE8* message, PLI_BYTE8* code, PLI_BYTE8* file, PLI_INT32 line) {
        m_errorInfo.message = message;
        m_errorInfo.file = file;
        m_errorInfo.line = line;
        m_errorInfo.code = code;
        do_callbacks();
    }
    void do_callbacks() {
        if (getError()->level >= vpiError && Verilated::threadContextp()->fatalOnVpiError()) {
            // Stop on vpi error/unsupported
            vpi_unsupported();
        }
        // We need to run above code first because in the case that the
        // callback executes further vpi functions we will loose the error
        // as it will be overwritten.
        VerilatedVpiImp::callCbs(cbPLIError);
    }

public:
    VerilatedVpiError() {
        m_buff[0] = '\0';
        m_errorInfo.product = const_cast<PLI_BYTE8*>(Verilated::productName());
    }
    ~VerilatedVpiError() = default;
    static void selfTest() VL_MT_UNSAFE_ONE;
    VerilatedVpiError* setMessage(PLI_INT32 level) {
        m_flag = true;
        m_errorInfo.level = level;
        return this;
    }
    void setMessage(const std::string& file, PLI_INT32 line, const char* message, ...) {
        // message cannot be a const string& as va_start cannot use a reference
        static thread_local std::string t_filehold;
        va_list args;
        va_start(args, message);
        VL_VSNPRINTF(m_buff, sizeof(m_buff), message, args);
        va_end(args);
        m_errorInfo.state = vpiPLI;
        t_filehold = file;
        setError(static_cast<PLI_BYTE8*>(m_buff), nullptr,
                 const_cast<PLI_BYTE8*>(t_filehold.c_str()), line);
    }
    p_vpi_error_info getError() {
        if (m_flag) return &m_errorInfo;
        return nullptr;
    }
    void resetError() { m_flag = false; }
    static void vpi_unsupported() {
        // Not supported yet
        const p_vpi_error_info error_info_p = VerilatedVpiImp::error_info()->getError();
        if (error_info_p) {
            VL_FATAL_MT(error_info_p->file, error_info_p->line, "", error_info_p->message);
            return;
        }
        VL_FATAL_MT(__FILE__, __LINE__, "", "vpi_unsupported called without error info set");
    }
    static const char* strFromVpiVal(PLI_INT32 vpiVal) VL_PURE;
    static const char* strFromVpiObjType(PLI_INT32 vpiVal) VL_PURE;
    static const char* strFromVpiMethod(PLI_INT32 vpiVal) VL_PURE;
    static const char* strFromVpiCallbackReason(PLI_INT32 vpiVal) VL_PURE;
    static const char* strFromVpiProp(PLI_INT32 vpiVal) VL_PURE;
    static const char* strFromVpiConstType(PLI_INT32 vpiVal) VL_PURE;
};

//======================================================================
// VerilatedVpi implementation

bool VerilatedVpi::callCbs(uint32_t reason) VL_MT_UNSAFE_ONE {
    return VerilatedVpiImp::callCbs(reason);
}

bool VerilatedVpi::hasCbs(uint32_t reason) VL_MT_UNSAFE_ONE {
    return VerilatedVpiImp::hasCbs(reason);
}

// Historical, before we had multiple kinds of timed callbacks
void VerilatedVpi::callTimedCbs() VL_MT_UNSAFE_ONE { VerilatedVpiImp::callCbs(cbAfterDelay); }

bool VerilatedVpi::callValueCbs() VL_MT_UNSAFE_ONE { return VerilatedVpiImp::callValueCbs(); }

QData VerilatedVpi::cbNextDeadline() VL_MT_UNSAFE_ONE { return VerilatedVpiImp::cbNextDeadline(); }

void VerilatedVpi::dumpCbs() VL_MT_UNSAFE_ONE { VerilatedVpiImp::dumpCbs(); }

PLI_INT32 VerilatedVpioReasonCb::dovpi_remove_cb() {
    VerilatedVpiImp::cbReasonRemove(m_id, m_reason, m_time);
    delete this;  // IEEE 37.2.2 a vpi_remove_cb does a vpi_release_handle
    return 1;
}

void VerilatedVpi::clearEvalNeeded() VL_MT_UNSAFE_ONE { VerilatedVpiImp::evalNeeded(false); }
bool VerilatedVpi::evalNeeded() VL_MT_UNSAFE_ONE { return VerilatedVpiImp::evalNeeded(); }

void VerilatedVpi::doInertialPuts() VL_MT_UNSAFE_ONE { VerilatedVpiImp::doInertialPuts(); }

//======================================================================
// VerilatedVpiImp implementation

void VerilatedVpiImp::dumpCbs() VL_MT_UNSAFE_ONE {
    assertOneCheck();
    VL_DBG_MSGF("- vpi: dumpCbs\n");
    for (uint32_t reason = 0; reason < CB_ENUM_MAX_VALUE; ++reason) {
        VpioCbList& cbObjList = s().m_cbCurrentLists[reason];
        for (auto& ho : cbObjList) {
            if (VL_UNLIKELY(!ho.invalid())) {
                VL_DBG_MSGF("- vpi:   reason=%d=%s  id=%" PRId64 "\n", reason,
                            VerilatedVpiError::strFromVpiCallbackReason(reason), ho.id());
            }
        }
    }
    for (auto& ifuture : s().m_nextCbs) {
        const QData time = ifuture.first.first;
        VerilatedVpiCbHolder& ho = ifuture.second;
        if (VL_UNLIKELY(!ho.invalid())) {
            VL_DBG_MSGF("- vpi:   time=%" PRId64 "(NEXT) reason=%d=%s  id=%" PRId64 "\n", time,
                        ho.cb_datap()->reason,
                        VerilatedVpiError::strFromVpiCallbackReason(ho.cb_datap()->reason),
                        ho.id());
        }
    }
    for (auto& ifuture : s().m_futureCbs) {
        const QData time = ifuture.first.first;
        VerilatedVpiCbHolder& ho = ifuture.second;
        if (VL_UNLIKELY(!ho.invalid())) {
            VL_DBG_MSGF("- vpi:   time=%" PRId64 " reason=%d=%s  id=%" PRId64 "\n", time,
                        ho.cb_datap()->reason,
                        VerilatedVpiError::strFromVpiCallbackReason(ho.cb_datap()->reason),
                        ho.id());
        }
    }
}

VerilatedVpiError* VerilatedVpiImp::error_info() VL_MT_UNSAFE_ONE {
    VerilatedVpiImp::assertOneCheck();
    if (VL_UNLIKELY(!s().m_errorInfop)) s().m_errorInfop = new VerilatedVpiError;
    return s().m_errorInfop;
}

auto VerilatedVpiImp::getForceControlSignals(const VerilatedVpioVarBase* const vop) {
    const std::string signalName = vop->fullname();
    const std::string forceEnableSignalName = signalName + "__VforceEn";
    const std::string forceValueSignalName = signalName + "__VforceVal";

    vpiHandle const forceEnableSignalp  // NOLINT(misc-misplaced-const)
        = vpi_handle_by_name(const_cast<PLI_BYTE8*>(forceEnableSignalName.c_str()), nullptr);
    vpiHandle const forceValueSignalp  // NOLINT(misc-misplaced-const)
        = vpi_handle_by_name(const_cast<PLI_BYTE8*>(forceValueSignalName.c_str()), nullptr);
    VerilatedVpioVar* forceEnableSignalVop = VerilatedVpioVar::castp(forceEnableSignalp);
    VerilatedVpioVar* forceValueSignalVop = VerilatedVpioVar::castp(forceValueSignalp);
    if (VL_UNLIKELY(!forceEnableSignalVop)) {
        VL_VPI_ERROR_(__FILE__, __LINE__,
                      "%s: VPI force or release requested for '%s', but vpiHandle '%p' of enable "
                      "signal '%s' could not be cast to VerilatedVpioVar*. Ensure signal is "
                      "marked as forceable",
                      __func__, signalName.c_str(), forceEnableSignalp,
                      forceEnableSignalName.c_str());
    }
    if (VL_UNLIKELY(!forceValueSignalVop)) {
        VL_VPI_ERROR_(__FILE__, __LINE__,
                      "%s: VPI force or release requested for '%s', but vpiHandle '%p' of value "
                      "signal '%s' could not be cast to VerilatedVpioVar*. Ensure signal is "
                      "marked as forceable",
                      __func__, signalName.c_str(), forceValueSignalp,
                      forceValueSignalName.c_str());
    }
    return std::pair<vopGuard_t, vopGuard_t>{vopGuard_t{forceEnableSignalVop, releaseVop},
                                             vopGuard_t{forceValueSignalVop, releaseVop}};
}

std::size_t VerilatedVpiImp::vlTypeSize(const VerilatedVarType vltype) {
    switch (vltype) {
    case VLVT_UINT8: return sizeof(CData); break;
    case VLVT_UINT16: return sizeof(SData); break;
    case VLVT_UINT32: return sizeof(IData); break;
    case VLVT_UINT64: return sizeof(QData); break;
    case VLVT_WDATA: return sizeof(EData); break;
    default:  // LCOV_EXCL_START
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vltype (%d)", __func__, vltype);
        return 0;
    }  // LCOV_EXCL_STOP
}
//======================================================================
// VerilatedVpiError Methods

const char* VerilatedVpiError::strFromVpiVal(PLI_INT32 vpiVal) VL_PURE {
    // clang-format off
    static const char* const names[] = {
        "*undefined*",
        "vpiBinStrVal",
        "vpiOctStrVal",
        "vpiDecStrVal",
        "vpiHexStrVal",
        "vpiScalarVal",
        "vpiIntVal",
        "vpiRealVal",
        "vpiStringVal",
        "vpiVectorVal",
        "vpiStrengthVal",
        "vpiTimeVal",
        "vpiObjTypeVal",
        "vpiSuppressVal",
        "vpiShortIntVal",
        "vpiLongIntVal",
        "vpiShortRealVal",
        "vpiRawTwoStateVal",
        "vpiRawFourStateVal",
    };
    // clang-format on
    if (VL_UNCOVERABLE(vpiVal < 0)) return names[0];
    return names[(vpiVal <= vpiRawFourStateVal) ? vpiVal : 0];
}
const char* VerilatedVpiError::strFromVpiObjType(PLI_INT32 vpiVal) VL_PURE {
    // clang-format off
    static const char* const names[] = {
        "*undefined*",
        "vpiAlways",
        "vpiAssignStmt",
        "vpiAssignment",
        "vpiBegin",
        "vpiCase",
        "vpiCaseItem",
        "vpiConstant",
        "vpiContAssign",
        "vpiDeassign",
        "vpiDefParam",
        "vpiDelayControl",
        "vpiDisable",
        "vpiEventControl",
        "vpiEventStmt",
        "vpiFor",
        "vpiForce",
        "vpiForever",
        "vpiFork",
        "vpiFuncCall",
        "vpiFunction",
        "vpiGate",
        "vpiIf",
        "vpiIfElse",
        "vpiInitial",
        "vpiIntegerVar",
        "vpiInterModPath",
        "vpiIterator",
        "vpiIODecl",
        "vpiMemory",
        "vpiMemoryWord",
        "vpiModPath",
        "vpiModule",
        "vpiNamedBegin",
        "vpiNamedEvent",
        "vpiNamedFork",
        "vpiNet",
        "vpiNetBit",
        "vpiNullStmt",
        "vpiOperation",
        "vpiParamAssign",
        "vpiParameter",
        "vpiPartSelect",
        "vpiPathTerm",
        "vpiPort",
        "vpiPortBit",
        "vpiPrimTerm",
        "vpiRealVar",
        "vpiReg",
        "vpiRegBit",
        "vpiRelease",
        "vpiRepeat",
        "vpiRepeatControl",
        "vpiSchedEvent",
        "vpiSpecParam",
        "vpiSwitch",
        "vpiSysFuncCall",
        "vpiSysTaskCall",
        "vpiTableEntry",
        "vpiTask",
        "vpiTaskCall",
        "vpiTchk",
        "vpiTchkTerm",
        "vpiTimeVar",
        "vpiTimeQueue",
        "vpiUdp",
        "vpiUdpDefn",
        "vpiUserSystf",
        "vpiVarSelect",
        "vpiWait",
        "vpiWhile",
        "vpiCondition",
        "vpiDelay",
        "vpiElseStmt",
        "vpiForIncStmt",
        "vpiForInitStmt",
        "vpiHighConn",
        "vpiLhs",
        "vpiIndex",
        "vpiLeftRange",
        "vpiLowConn",
        "vpiParent",
        "vpiRhs",
        "vpiRightRange",
        "vpiScope",
        "vpiSysTfCall",
        "vpiTchkDataTerm",
        "vpiTchkNotifier",
        "vpiTchkRefTerm",
        "vpiArgument",
        "vpiBit",
        "vpiDriver",
        "vpiInternalScope",
        "vpiLoad",
        "vpiModDataPathIn",
        "vpiModPathIn",
        "vpiModPathOut",
        "vpiOperand",
        "vpiPortInst",
        "vpiProcess",
        "vpiVariables",
        "vpiUse",
        "vpiExpr",
        "vpiPrimitive",
        "vpiStmt",
        "vpiAttribute",
        "vpiBitSelect",
        "vpiCallback",
        "vpiDelayTerm",
        "vpiDelayDevice",
        "vpiFrame",
        "vpiGateArray",
        "vpiModuleArray",
        "vpiPrimitiveArray",
        "vpiNetArray",
        "vpiRange",
        "vpiRegArray",
        "vpiSwitchArray",
        "vpiUdpArray",
        "vpiActiveTimeFormat",
        "vpiInTerm",
        "vpiInstanceArray",
        "vpiLocalDriver",
        "vpiLocalLoad",
        "vpiOutTerm",
        "vpiPorts",
        "vpiSimNet",
        "vpiTaskFunc",
        "vpiContAssignBit",
        "vpiNamedEventArray",
        "vpiIndexedPartSelect",
        "vpiBaseExpr",
        "vpiWidthExpr",
        "vpiGenScopeArray",
        "vpiGenScope",
        "vpiGenVar",
        "vpiAutomatics"
    };
    static const char* const sv_names1[] = {
        "vpiPackage",
        "vpiInterface",
        "vpiProgram",
        "vpiInterfaceArray",
        "vpiProgramArray",
        "vpiTypespec",
        "vpiModport",
        "vpiInterfaceTfDecl",
        "vpiRefObj",
        "vpiTypeParameter",
        "vpiLongIntVar",
        "vpiShortIntVar",
        "vpiIntVar",
        "vpiShortRealVar",
        "vpiByteVar",
        "vpiClassVar",
        "vpiStringVar",
        "vpiEnumVar",
        "vpiStructVar",
        "vpiUnionVar",
        "vpiBitVar",
        "vpiClassObj",
        "vpiChandleVar",
        "vpiPackedArrayVar",
        "*undefined*",  // 624 is not defined for object types
        "vpiLongIntTypespec",
        "vpiShortRealTypespec",
        "vpiByteTypespec",
        "vpiShortIntTypespec",
        "vpiIntTypespec",
        "vpiClassTypespec",
        "vpiStringTypespec",
        "vpiChandleTypespec",
        "vpiEnumTypespec",
        "vpiEnumConst",
        "vpiIntegerTypespec",
        "vpiTimeTypespec",
        "vpiRealTypespec",
        "vpiStructTypespec",
        "vpiUnionTypespec",
        "vpiBitTypespec",
        "vpiLogicTypespec",
        "vpiArrayTypespec",
        "vpiVoidTypespec",
        "vpiTypespecMember",
        "vpiDistItem",
        "vpiAliasStmt",
        "vpiThread",
        "vpiMethodFuncCall",
        "vpiMethodTaskCall",
        "vpiClockingBlock",
        "vpiClockingIODecl",
        "vpiClassDefn",
        "vpiConstraint",
        "vpiConstraintOrdering",
        "vpiPropertyDecl",
        "vpiPropertySpec",
        "vpiPropertyExpr",
        "vpiMulticlockSequenceExpr",
        "vpiClockedSeq",
        "vpiPropertyInst",
        "vpiSequenceDecl",
        "vpiCaseProperty",
        "*undefined*", // 663 is not defined for object types
        "vpiSequenceInst",
        "vpiImmediateAssert",
        "vpiReturn",
        "vpiAnyPattern",
        "vpiTaggedPattern",
        "vpiStructPattern",
        "vpiDoWhile",
        "vpiOrderedWait",
        "vpiWaitFork",
        "vpiDisableFork",
        "vpiExpectStmt",
        "vpiForeachStmt",
        "vpiFinal",
        "vpiExtends",
        "vpiDistribution",
        "vpiSeqFormalDecl",
        "vpiEnumNet",
        "vpiIntegerNet",
        "vpiTimeNet",
        "vpiStructNet",
        "vpiBreak",
        "vpiContinue",
        "vpiAssert",
        "vpiAssume",
        "vpiCover",
        "vpiDisableCondition",
        "vpiClockingEvent",
        "vpiReturnStmt",
        "vpiPackedArrayTypespec",
        "vpiPackedArrayNet",
        "vpiImmediateAssume",
        "vpiImmediateCover",
        "vpiSequenceTypespec",
        "vpiPropertyTypespec",
        "vpiEventTypespec",
        "vpiPropFormalDecl",
    };
    // clang-format on
    if (VL_UNCOVERABLE(vpiVal < 0))
        return names[0];
    else if (vpiVal <= vpiAutomatics)
        return names[vpiVal];
    else if (vpiVal >= vpiPackage && vpiVal <= vpiPropFormalDecl)
        return sv_names1[(vpiVal - vpiPackage)];
    else
        return names[0];
}
const char* VerilatedVpiError::strFromVpiMethod(PLI_INT32 vpiVal) VL_PURE {
    // clang-format off
    static const char* const names[] = {
        "vpiCondition",
        "vpiDelay",
        "vpiElseStmt",
        "vpiForIncStmt",
        "vpiForInitStmt",
        "vpiHighConn",
        "vpiLhs",
        "vpiIndex",
        "vpiLeftRange",
        "vpiLowConn",
        "vpiParent",
        "vpiRhs",
        "vpiRightRange",
        "vpiScope",
        "vpiSysTfCall",
        "vpiTchkDataTerm",
        "vpiTchkNotifier",
        "vpiTchkRefTerm",
        "vpiArgument",
        "vpiBit",
        "vpiDriver",
        "vpiInternalScope",
        "vpiLoad",
        "vpiModDataPathIn",
        "vpiModPathIn",
        "vpiModPathOut",
        "vpiOperand",
        "vpiPortInst",
        "vpiProcess",
        "vpiVariables",
        "vpiUse",
        "vpiExpr",
        "vpiPrimitive",
        "vpiStmt"
    };
    // clang-format on
    if (vpiVal > vpiStmt || vpiVal < vpiCondition) return "*undefined*";
    return names[vpiVal - vpiCondition];
}

const char* VerilatedVpiError::strFromVpiCallbackReason(PLI_INT32 vpiVal) VL_PURE {
    // clang-format off
    static const char* const names[] = {
        "*undefined*",
        "cbValueChange",
        "cbStmt",
        "cbForce",
        "cbRelease",
        "cbAtStartOfSimTime",
        "cbReadWriteSynch",
        "cbReadOnlySynch",
        "cbNextSimTime",
        "cbAfterDelay",
        "cbEndOfCompile",
        "cbStartOfSimulation",
        "cbEndOfSimulation",
        "cbError",
        "cbTchkViolation",
        "cbStartOfSave",
        "cbEndOfSave",
        "cbStartOfRestart",
        "cbEndOfRestart",
        "cbStartOfReset",
        "cbEndOfReset",
        "cbEnterInteractive",
        "cbExitInteractive",
        "cbInteractiveScopeChange",
        "cbUnresolvedSystf",
        "cbAssign",
        "cbDeassign",
        "cbDisable",
        "cbPLIError",
        "cbSignal",
        "cbNBASynch",
        "cbAtEndOfSimTime"
    };
    // clang-format on
    if (VL_UNCOVERABLE(vpiVal < 0)) return names[0];
    return names[(vpiVal <= cbAtEndOfSimTime) ? vpiVal : 0];
}

const char* VerilatedVpiError::strFromVpiProp(PLI_INT32 vpiVal) VL_PURE {
    // clang-format off
    static const char* const names[] = {
        "*undefined or other*",
        "vpiType",
        "vpiName",
        "vpiFullName",
        "vpiSize",
        "vpiFile",
        "vpiLineNo",
        "vpiTopModule",
        "vpiCellInstance",
        "vpiDefName",
        "vpiProtected",
        "vpiTimeUnit",
        "vpiTimePrecision",
        "vpiDefNetType",
        "vpiUnconnDrive",
        "vpiDefFile",
        "vpiDefLineNo",
        "vpiScalar",
        "vpiVector",
        "vpiExplicitName",
        "vpiDirection",
        "vpiConnByName",
        "vpiNetType",
        "vpiExplicitScalared",
        "vpiExplicitVectored",
        "vpiExpanded",
        "vpiImplicitDecl",
        "vpiChargeStrength",
        "vpiArray",
        "vpiPortIndex",
        "vpiTermIndex",
        "vpiStrength0",
        "vpiStrength1",
        "vpiPrimType",
        "vpiPolarity",
        "vpiDataPolarity",
        "vpiEdge",
        "vpiPathType",
        "vpiTchkType",
        "vpiOpType",
        "vpiConstType",
        "vpiBlocking",
        "vpiCaseType",
        "vpiFuncType",
        "vpiNetDeclAssign",
        "vpiUserDefn",
        "vpiScheduled",
        "*undefined*",
        "*undefined*",
        "vpiActive",
        "vpiAutomatic",
        "vpiCell",
        "vpiConfig",
        "vpiConstantSelect",
        "vpiDecompile",
        "vpiDefAttribute",
        "vpiDelayType",
        "vpiIteratorType",
        "vpiLibrary",
        "*undefined*",
        "vpiOffset",
        "vpiResolvedNetType",
        "vpiSaveRestartID",
        "vpiSaveRestartLocation",
        "vpiValid",
        "vpiSigned",
        "vpiStop",
        "vpiFinish",
        "vpiReset",
        "vpiSetInteractiveScope",
        "vpiLocalParam",
        "vpiModPathHasIfNone",
        "vpiIndexedPartSelectType",
        "vpiIsMemory",
        "vpiIsProtected"
    };
    // clang-format on
    if (vpiVal == vpiUndefined) return "vpiUndefined";
    return names[(vpiVal <= vpiIsProtected) ? vpiVal : 0];
}
const char* VerilatedVpiError::strFromVpiConstType(PLI_INT32 constType) VL_PURE {
    // clang-format off
    static const char* const names[] = {
        "*undefined*",
        "vpiDecConst",
        "vpiRealConst",
        "vpiBinaryConst",
        "vpiOctConst",
        "vpiHexConst",
        "vpiStringConst",
        "vpiIntConst",
        "vpiTimeConst",
    };
    // clang-format on
    if (VL_UNCOVERABLE(constType < 0)) return names[0];
    return names[(constType <= vpiTimeConst) ? constType : 0];
}

#define SELF_CHECK_RESULT_CSTR(got, exp) \
    if (0 != std::strcmp((got), (exp))) { \
        const std::string msg = "%Error: GOT = '"s + (got) + "'" + "  EXP = '" + (exp) + "'"; \
        VL_FATAL_MT(__FILE__, __LINE__, "", msg.c_str()); \
    }

#define SELF_CHECK_ENUM_STR(fn, enumn) \
    do { \
        const char* const strVal = VerilatedVpiError::fn(enumn); \
        SELF_CHECK_RESULT_CSTR(strVal, #enumn); \
    } while (0)

void VerilatedVpi::selfTest() VL_MT_UNSAFE_ONE { VerilatedVpiError::selfTest(); }
void VerilatedVpiError::selfTest() VL_MT_UNSAFE_ONE {
    VerilatedVpiImp::assertOneCheck();

    SELF_CHECK_ENUM_STR(strFromVpiVal, vpiBinStrVal);
    SELF_CHECK_ENUM_STR(strFromVpiVal, vpiRawFourStateVal);

    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAlways);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAssignStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAssignment);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBegin);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiCase);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiCaseItem);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiConstant);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiContAssign);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDeassign);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDefParam);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDelayControl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDisable);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEventControl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEventStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiFor);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiForce);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiForever);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiFork);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiFuncCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiFunction);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiGate);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIf);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIfElse);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInitial);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIntegerVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInterModPath);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIterator);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIODecl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiMemory);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiMemoryWord);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModPath);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModule);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNamedBegin);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNamedEvent);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNamedFork);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNetBit);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNullStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiOperation);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiParamAssign);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiParameter);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPartSelect);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPathTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPort);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPortBit);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPrimTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRealVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiReg);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRegBit);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRelease);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRepeat);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRepeatControl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSchedEvent);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSpecParam);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSwitch);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSysFuncCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSysTaskCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTableEntry);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTask);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTaskCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTchk);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTchkTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTimeVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTimeQueue);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUdp);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUdpDefn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUserSystf);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiVarSelect);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiWait);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiWhile);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiCondition);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDelay);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiElseStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiForIncStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiForInitStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiHighConn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLhs);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIndex);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLeftRange);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLowConn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiParent);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRhs);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRightRange);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiScope);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSysTfCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTchkDataTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTchkNotifier);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTchkRefTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiArgument);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBit);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDriver);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInternalScope);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLoad);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModDataPathIn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModPathIn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModPathOut);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiOperand);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPortInst);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiProcess);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiVariables);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUse);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiExpr);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPrimitive);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAttribute);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBitSelect);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiCallback);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDelayTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDelayDevice);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiFrame);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiGateArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModuleArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPrimitiveArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNetArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRange);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRegArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSwitchArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUdpArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiActiveTimeFormat);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInstanceArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLocalDriver);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLocalLoad);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiOutTerm);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPorts);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSimNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTaskFunc);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiContAssignBit);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiNamedEventArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIndexedPartSelect);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBaseExpr);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiWidthExpr);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiGenScopeArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiGenScope);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiGenVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAutomatics);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPackage);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInterface);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiProgram);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInterfaceArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiProgramArray);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiModport);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiInterfaceTfDecl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRefObj);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTypeParameter);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLongIntVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiShortIntVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIntVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiShortRealVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiByteVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClassVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStringVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEnumVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStructVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUnionVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBitVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClassObj);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiChandleVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPackedArrayVar);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLongIntTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiShortRealTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiByteTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiShortIntTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIntTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClassTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStringTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiChandleTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEnumTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEnumConst);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIntegerTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTimeTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiRealTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStructTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiUnionTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBitTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiLogicTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiArrayTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiVoidTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTypespecMember);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDistItem);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAliasStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiThread);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiMethodFuncCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiMethodTaskCall);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClockingBlock);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClockingIODecl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClassDefn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiConstraint);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiConstraintOrdering);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPropertyDecl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPropertySpec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPropertyExpr);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiMulticlockSequenceExpr);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClockedSeq);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPropertyInst);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSequenceDecl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiCaseProperty);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSequenceInst);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiImmediateAssert);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiReturn);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAnyPattern);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTaggedPattern);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStructPattern);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDoWhile);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiOrderedWait);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiWaitFork);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDisableFork);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiExpectStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiForeachStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiFinal);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiExtends);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDistribution);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSeqFormalDecl);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEnumNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiIntegerNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiTimeNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiStructNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiBreak);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiContinue);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAssert);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiAssume);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiCover);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiDisableCondition);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiClockingEvent);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiReturnStmt);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPackedArrayTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPackedArrayNet);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiImmediateAssume);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiImmediateCover);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiSequenceTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPropertyTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiEventTypespec);
    SELF_CHECK_ENUM_STR(strFromVpiObjType, vpiPropFormalDecl);

    SELF_CHECK_ENUM_STR(strFromVpiMethod, vpiCondition);
    SELF_CHECK_ENUM_STR(strFromVpiMethod, vpiStmt);

    SELF_CHECK_ENUM_STR(strFromVpiCallbackReason, cbValueChange);
    SELF_CHECK_ENUM_STR(strFromVpiCallbackReason, cbAtEndOfSimTime);

    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiType);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiProtected);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiDirection);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiTermIndex);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiConstType);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiAutomatic);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiOffset);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiStop);
    SELF_CHECK_ENUM_STR(strFromVpiProp, vpiIsProtected);

    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiDecConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiRealConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiBinaryConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiOctConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiHexConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiStringConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiIntConst);
    SELF_CHECK_ENUM_STR(strFromVpiConstType, vpiTimeConst);
}

#undef SELF_CHECK_ENUM_STR
#undef SELF_CHECK_RESULT_CSTR

//======================================================================
// callback related

vpiHandle vpi_register_cb(p_cb_data cb_data_p) {
    // Returns handle so user can remove the callback, user must vpi_release_handle it
    // Don't confuse with the callback-activated t_cb_data object handle
    // which is the object causing the callback rather than the callback itself
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    // cppcheck-suppress nullPointer
    if (VL_UNLIKELY(!cb_data_p)) {
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: VPI callback data pointer is null", __func__);
        return nullptr;
    }
    const PLI_INT32 reason = cb_data_p->reason;
    switch (reason) {
    case cbAfterDelay:  // FALLTHRU // One-shot; time relative
    case cbAtEndOfSimTime:  // FALLTHRU // One-shot; time absolute; supported via vlt_main.cpp
    case cbAtStartOfSimTime:  // FALLTHRU // One-shot; time absolute; supported via vlt_main.cpp
    case cbReadOnlySynch:  // FALLTHRU // One-shot; time relative; supported via vlt_main.cpp
    case cbReadWriteSynch: {  // One-shot; time relative; supported via vlt_main.cpp
        const bool abs = reason == cbAtStartOfSimTime || reason == cbAtEndOfSimTime;
        const QData time = VL_TIME_Q();
        QData abstime = 0;
        if (cb_data_p->time) {
            if (abs) {
                abstime = VL_SET_QII(cb_data_p->time->high, cb_data_p->time->low);
            } else {
                abstime = time + VL_SET_QII(cb_data_p->time->high, cb_data_p->time->low);
            }
        }
        const uint64_t id = VerilatedVpiImp::nextCallbackId();
        VerilatedVpioReasonCb* const vop = new VerilatedVpioReasonCb{id, abstime, reason};
        if (abstime <= time) {
            VerilatedVpiImp::cbCurrentAdd(id, cb_data_p);
        } else {
            VerilatedVpiImp::cbFutureAdd(id, cb_data_p, abstime);
        }
        return vop->castVpiHandle();
    }
    case cbNextSimTime: {  // One-shot; time always next; supported via vlt_main.cpp
        const QData time = VL_TIME_Q();
        const uint64_t id = VerilatedVpiImp::nextCallbackId();
        VerilatedVpioReasonCb* const vop = new VerilatedVpioReasonCb{id, 0, reason};
        VerilatedVpiImp::cbNextAdd(id, cb_data_p, time);
        return vop->castVpiHandle();
    }
    case cbEndOfSimulation:  // FALLTHRU // One-shot; time ignored; supported via vlt_main.cpp
    case cbEnterInteractive:  // FALLTHRU // NOP, but need to return handle, so make object
    case cbExitInteractive:  // FALLTHRU // NOP, but need to return handle, so make object
    case cbInteractiveScopeChange:  // FALLTHRU // NOP, but need to return handle, so make object
    case cbPLIError:  // FALLTHRU // NOP, but need to return handle, so make object
    case cbStartOfSimulation:  // FALLTHRU // One-shot; time ignored; supported via vlt_main.cpp
    case cbValueChange: {  // Multi-shot; supported via vlt_main.cpp
        const uint64_t id = VerilatedVpiImp::nextCallbackId();
        VerilatedVpioReasonCb* const vop = new VerilatedVpioReasonCb{id, 0, reason};
        VerilatedVpiImp::cbCurrentAdd(id, cb_data_p);
        return vop->castVpiHandle();
    }
    default:
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Unsupported callback type %s", __func__,
                        VerilatedVpiError::strFromVpiCallbackReason(reason));
        return nullptr;
    }
}

PLI_INT32 vpi_remove_cb(vpiHandle cb_obj) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_remove_cb %p\n", cb_obj););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    VerilatedVpio* const vop = VerilatedVpio::castp(cb_obj);
    if (VL_UNLIKELY(!vop)) return 0;
    return vop->dovpi_remove_cb();
}

void vpi_get_cb_info(vpiHandle /*object*/, p_cb_data /*cb_data_p*/) { VL_VPI_UNIMP_(); }
vpiHandle vpi_register_systf(p_vpi_systf_data /*systf_data_p*/) {
    VL_VPI_UNIMP_();
    return nullptr;
}
void vpi_get_systf_info(vpiHandle /*object*/, p_vpi_systf_data /*systf_data_p*/) {
    VL_VPI_UNIMP_();
}

// for obtaining handles

vpiHandle vpi_handle_by_name(PLI_BYTE8* namep, vpiHandle scope) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!namep)) return nullptr;
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_handle_by_name %s %p\n", namep, scope););
    const VerilatedVar* varp = nullptr;
    const VerilatedScope* scopep;
    const VerilatedVpioScope* const voScopep = VerilatedVpioScope::castp(scope);
    std::string scopeAndName = namep;
    if (0 == std::strncmp(namep, "$root.", std::strlen("$root."))) {
        namep += std::strlen("$root.");
        scopeAndName = namep;
    } else if (voScopep) {
        const bool scopeIsPackage = VerilatedVpioPackage::castp(scope) != nullptr;
        scopeAndName = std::string{voScopep->fullname()} + (scopeIsPackage ? "" : ".") + namep;
        namep = const_cast<PLI_BYTE8*>(scopeAndName.c_str());
    }
    {
        // This doesn't yet follow the hierarchy in the proper way
        bool isPackage = false;
        scopep = Verilated::threadContextp()->scopeFind(namep);
        if (scopep) {  // Whole thing found as a scope
            if (scopep->type() == VerilatedScope::SCOPE_MODULE) {
                return (new VerilatedVpioModule{scopep})->castVpiHandle();
            } else if (scopep->type() == VerilatedScope::SCOPE_PACKAGE) {
                return (new VerilatedVpioPackage{scopep})->castVpiHandle();
            } else {
                return (new VerilatedVpioScope{scopep})->castVpiHandle();
            }
        }
        std::string basename = scopeAndName;
        std::string scopename;
        std::string::size_type prevpos = std::string::npos;
        std::string::size_type pos = std::string::npos;
        // Split hierarchical names at last '.' not inside escaped identifier
        size_t i = 0;
        while (i < scopeAndName.length()) {
            if (scopeAndName[i] == '\\') {
                while (i < scopeAndName.length() && scopeAndName[i] != ' ') ++i;
                ++i;  // Proc ' ', it should always be there. Then grab '.' on next cycle
            } else {
                while (i < scopeAndName.length()
                       && (scopeAndName[i] != '.'
                           && (i + 1 >= scopeAndName.length() || scopeAndName[i] != ':'
                               || scopeAndName[i + 1] != ':')))
                    ++i;
                if (i < scopeAndName.length()) {
                    prevpos = pos;
                    pos = i++;
                    if (scopeAndName[i - 1] == ':') isPackage = true;
                }
            }
        }
        // Do the split
        if (VL_LIKELY(pos != std::string::npos)) {
            basename.erase(0, pos + (isPackage ? 2 : 1));
            scopename = scopeAndName.substr(0, pos);
            if (scopename == "$unit") scopename = "\\$unit ";
        }
        if (prevpos == std::string::npos) {
            // scopename is a toplevel (no '.' separator), so search in our TOP ports first.
            scopep = Verilated::threadContextp()->scopeFind("TOP");
            if (scopep) varp = scopep->varFind(basename.c_str());
        }
        if (!varp) {
            scopep = Verilated::threadContextp()->scopeFind(scopename.c_str());
            if (!scopep) return nullptr;
            varp = scopep->varFind(basename.c_str());
        }
    }
    if (!varp) return nullptr;

    if (varp->isParam()) {
        return (new VerilatedVpioParam{varp, scopep})->castVpiHandle();
    } else {
        return (new VerilatedVpioVar{varp, scopep})->castVpiHandle();
    }
}

vpiHandle vpi_handle_by_index(vpiHandle object, PLI_INT32 indx) {
    // Used to get array entries
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_handle_by_index %p %d\n", object, indx););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    const VerilatedVpioVar* const varop = VerilatedVpioVar::castp(object);
    if (VL_LIKELY(varop)) {
        // Case: no dimensions left to index
        if (VL_UNLIKELY(varop->indexedDim() + 1 > varop->varp()->dims() - 1)) return nullptr;

        // Case: index out of range
        if (VL_UNLIKELY(indx < varop->rangep()->low() || indx > varop->rangep()->high()))
            return nullptr;

        return varop->withIndex(indx)->castVpiHandle();
    }
    VL_VPI_INTERNAL_(__FILE__, __LINE__, "%s : can't resolve handle", __func__);
    return nullptr;
}

// for traversing relationships

vpiHandle vpi_handle(PLI_INT32 type, vpiHandle object) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_handle %d %p\n", type, object););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    switch (type) {
    case vpiLeftRange: {
        if (const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object)) {
            if (VL_UNLIKELY(!vop->rangep())) return nullptr;
            return (new VerilatedVpioConst{vop->rangep()->left()})->castVpiHandle();
        } else if (const VerilatedVpioRange* const vop = VerilatedVpioRange::castp(object)) {
            if (VL_UNLIKELY(!vop->rangep())) return nullptr;
            return (new VerilatedVpioConst{vop->rangep()->left()})->castVpiHandle();
        }
        VL_VPI_WARNING_(__FILE__, __LINE__,
                        "%s: Unsupported vpiHandle (%p) for type %s, nothing will be returned",
                        __func__, object, VerilatedVpiError::strFromVpiMethod(type));
        return nullptr;
    }
    case vpiRightRange: {
        if (const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object)) {
            if (VL_UNLIKELY(!vop->rangep())) return nullptr;
            return (new VerilatedVpioConst{vop->rangep()->right()})->castVpiHandle();
        } else if (const VerilatedVpioRange* const vop = VerilatedVpioRange::castp(object)) {
            if (VL_UNLIKELY(!vop->rangep())) return nullptr;
            return (new VerilatedVpioConst{vop->rangep()->right()})->castVpiHandle();
        }
        VL_VPI_WARNING_(__FILE__, __LINE__,
                        "%s: Unsupported vpiHandle (%p) for type %s, nothing will be returned",
                        __func__, object, VerilatedVpiError::strFromVpiMethod(type));
        return nullptr;
    }
    case vpiIndex: {
        const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
        if (VL_UNLIKELY(!vop)) return nullptr;
        const int32_t val = vop->index().back();
        return (new VerilatedVpioConst{val})->castVpiHandle();
    }
    case vpiScope: {
        const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object);
        if (VL_UNLIKELY(!vop)) return nullptr;
        return (new VerilatedVpioScope{vop->scopep()})->castVpiHandle();
    }
    case vpiParent: {
        const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
        if (VL_UNLIKELY(!vop)) return nullptr;
        return (new VerilatedVpioVar{vop->varp(), vop->scopep()})->castVpiHandle();
    }
    default:
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Unsupported type %s, nothing will be returned",
                        __func__, VerilatedVpiError::strFromVpiMethod(type));
        return nullptr;
    }
}

vpiHandle vpi_handle_multi(PLI_INT32 /*type*/, vpiHandle /*refHandle1*/, vpiHandle /*refHandle2*/,
                           ...) {
    VL_VPI_UNIMP_();
    return nullptr;
}

vpiHandle vpi_iterate(PLI_INT32 type, vpiHandle object) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_iterate %d %p\n", type, object););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    switch (type) {
    case vpiRange: {
        const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
        if (VL_UNLIKELY(!vop)) return nullptr;

        std::vector<VerilatedRange> ranges;
        const int maxDim = vop->maxDim(vop->isIndexedDimUnpacked());
        for (int dim = vop->indexedDim() + 1; dim <= maxDim; ++dim)
            ranges.emplace_back(*vop->varp()->range(dim));

        // allow one more range layer (regbit)
        if (ranges.empty()) ranges.emplace_back(VerilatedRange(0, 0));
        return ((new VerilatedVpioRangeIter{ranges})->castVpiHandle());
    }
    case vpiReg: {
        const VerilatedVpioScope* const vscopep = VerilatedVpioScope::castp(object);
        if (vscopep) return ((new VerilatedVpioVarIter{vscopep, false})->castVpiHandle());
        const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
        if (vop) return ((new VerilatedVpioRegIter{vop})->castVpiHandle());
        return nullptr;
    }
    case vpiParameter: {
        const VerilatedVpioScope* const vop = VerilatedVpioScope::castp(object);
        if (VL_UNLIKELY(!vop)) return nullptr;
        return ((new VerilatedVpioVarIter{vop, true})->castVpiHandle());
    }
    case vpiModule: {
        const VerilatedVpioScope* const vop = VerilatedVpioScope::castp(object);
        const VerilatedHierarchyMap* const map = VerilatedImp::hierarchyMap();
        const VerilatedScope* const modp = vop ? vop->scopep() : nullptr;
        const auto it = vlstd::as_const(map)->find(const_cast<VerilatedScope*>(modp));
        if (it == map->end()) return nullptr;
        return ((new VerilatedVpioModuleIter{it->second})->castVpiHandle());
    }
    case vpiInternalScope: {
        const VerilatedVpioScope* const vop = VerilatedVpioScope::castp(object);
        const VerilatedHierarchyMap* const map = VerilatedImp::hierarchyMap();
        const VerilatedScope* const modp = vop ? vop->scopep() : nullptr;
        const auto it = vlstd::as_const(map)->find(const_cast<VerilatedScope*>(modp));
        if (it == map->end()) return nullptr;
        return ((new VerilatedVpioScopeIter{it->second})->castVpiHandle());
    }
    case vpiInstance: {
        if (object) return nullptr;
        const VerilatedHierarchyMap* const map = VerilatedImp::hierarchyMap();
        const auto it = vlstd::as_const(map)->find(nullptr);
        if (it == map->end()) return nullptr;
        return ((new VerilatedVpioInstanceIter{it->second})->castVpiHandle());
    }
    default:
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Unsupported type %s, nothing will be returned",
                        __func__, VerilatedVpiError::strFromVpiObjType(type));
        return nullptr;
    }
}
vpiHandle vpi_scan(vpiHandle object) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_scan %p\n", object););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    VerilatedVpio* const vop = VerilatedVpio::castp(object);
    if (VL_UNLIKELY(!vop)) return nullptr;
    return vop->dovpi_scan();
}

// for processing properties

PLI_INT32 vpi_get(PLI_INT32 property, vpiHandle object) {
    // Leave this in the header file - in many cases the compiler can constant propagate "object"
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_get %d %p\n", property, object););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    switch (property) {
    case vpiTimePrecision: {
        return Verilated::threadContextp()->timeprecision();
    }
    case vpiTimeUnit: {
        const VerilatedVpioScope* const vop = VerilatedVpioScope::castp(object);
        if (!vop)
            return Verilated::threadContextp()->timeunit();  // Null asks for global, not unlikely
        return vop->scopep()->timeunit();
    }
    case vpiType: {
        const VerilatedVpio* const vop = VerilatedVpio::castp(object);
        if (VL_UNLIKELY(!vop)) return vpiUndefined;
        return vop->type();
    }
    case vpiConstType: {
        const VerilatedVpio* const vop = VerilatedVpio::castp(object);
        if (VL_UNLIKELY(!vop)) return vpiUndefined;
        return vop->constType();
    }
    case vpiDirection: {
        // By forethought, the directions already are vpi enumerated
        const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object);
        if (VL_UNLIKELY(!vop)) return vpiUndefined;
        return vop->varp()->vldir();
    }
    case vpiScalar:  // FALLTHRU
    case vpiVector: {
        const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object);
        if (VL_UNLIKELY(!vop)) return vpiUndefined;
        return (property == vpiVector) ^ (vop->varp()->packedRanges().empty() || !vop->rangep());
    }
    case vpiSize: {
        const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object);
        if (VL_UNLIKELY(!vop)) return vpiUndefined;
        return vop->size();
    }
    case vpiSigned: {
        const VerilatedVpioVarBase* const vop = VerilatedVpioVarBase::castp(object);
        if (VL_UNLIKELY(!vop)) return vpiUndefined;
        return vop->varp()->isSigned();
    }
    default:
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported property %s, nothing will be returned",
                      __func__, VerilatedVpiError::strFromVpiProp(property));
        return vpiUndefined;
    }
}

PLI_INT64 vpi_get64(PLI_INT32 /*property*/, vpiHandle /*object*/) {
    VL_VPI_UNIMP_();
    return vpiUndefined;
}

PLI_BYTE8* vpi_get_str(PLI_INT32 property, vpiHandle object) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_get_str %d %p\n", property, object););
    VerilatedVpiImp::assertOneCheck();
    const VerilatedVpio* const vop = VerilatedVpio::castp(object);
    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!vop)) return nullptr;
    switch (property) {
    case vpiName: {
        return const_cast<PLI_BYTE8*>(vop->name());
    }
    case vpiFullName: {
        return const_cast<PLI_BYTE8*>(vop->fullname());
    }
    case vpiDefName: {
        return const_cast<PLI_BYTE8*>(vop->defname());
    }
    case vpiType: {
        return const_cast<PLI_BYTE8*>(VerilatedVpiError::strFromVpiObjType(vop->type()));
    }
    case vpiConstType: {
        const PLI_INT32 constType = vpi_get(vpiConstType, object);
        VL_VPI_ERROR_RESET_();
        return const_cast<PLI_BYTE8*>(VerilatedVpiError::strFromVpiConstType(constType));
    }
    default:
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Unsupported type %s, nothing will be returned",
                        __func__, VerilatedVpiError::strFromVpiProp(property));
        return nullptr;
    }
}

// delay processing

void vpi_get_delays(vpiHandle /*object*/, p_vpi_delay /*delay_p*/) { VL_VPI_UNIMP_(); }
void vpi_put_delays(vpiHandle /*object*/, p_vpi_delay /*delay_p*/) { VL_VPI_UNIMP_(); }

// value processing
bool vl_check_format(const VerilatedVpioVarBase* vop, const p_vpi_value valuep, bool isGetValue) {
    const VerilatedVar* varp = vop->varp();
    bool status = true;
    if ((valuep->format == vpiVectorVal) || (valuep->format == vpiBinStrVal)
        || (valuep->format == vpiOctStrVal) || (valuep->format == vpiHexStrVal)) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return status;
        default: status = false;  // LCOV_EXCL_LINE
        }
    } else if (valuep->format == vpiDecStrVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64: return status;
        default: status = false;  // LCOV_EXCL_LINE
        }
    } else if (valuep->format == vpiStringVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return status;
        case VLVT_STRING:
            // string parameter values can't be changed
            if (isGetValue || !varp->isParam()) {
                return status;
            } else {
                status = false;
                break;
            }
        default: status = false;  // LCOV_EXCL_LINE
        }
    } else if (valuep->format == vpiIntVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return status;
        default: status = false;  // LCOV_EXCL_LINE
        }
    } else if (valuep->format == vpiRealVal) {
        switch (varp->vltype()) {
        case VLVT_REAL: return status;
        default: status = false;  // LCOV_EXCL_LINE
        }
    } else if (valuep->format == vpiScalarVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return status;
        default: status = false;  // LCOV_EXCL_LINE
        }
    } else if (valuep->format == vpiSuppressVal) {
        return status;
    } else {
        status = false;
    }
    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) for %s", __func__,
                  VerilatedVpiError::strFromVpiVal(valuep->format), vop->fullname());
    return status;
}

static void vl_strprintf(std::string& buffer, char const* fmt, ...) {
    va_list args, args_copy;
    va_start(args, fmt);
    buffer.clear();
    // Make copy of args since we may need to call VL_VSNPRINTF more than once
    va_copy(args_copy, args);
    // Try VL_VSNPRINTF in existing buffer
    const int result
        = VL_VSNPRINTF(const_cast<char*>(buffer.data()), buffer.capacity(), fmt, args_copy);
    va_end(args_copy);
    const int required = result + 1;  // Returned size doesn't include NUL terminator
    // If there wasn't enough space, reallocate and try again
    if (buffer.capacity() < required) {
        buffer.reserve(required * 2);
        VL_VSNPRINTF(const_cast<char*>(buffer.data()), buffer.capacity(), fmt, args);
    }
    va_end(args);
}

// Information about how to access packed array data.
// If underlying type is multi-word (VLVT_WDATA), the packed element might straddle word
// boundaries, in which case m_maskHi != 0.
template <typename T>
struct VarAccessInfo final {
    T* m_datap;  // Typed pointer to packed array base address
    size_t m_bitOffset;  // Data start location (bit offset)
    size_t m_wordOffset;  // Data start location (word offset, VLVT_WDATA only)
    T m_maskLo;  // Access mask for m_datap[m_wordOffset]
    T m_maskHi;  // Access mask for m_datap[m_wordOffset + 1] (VLVT_WDATA only)
};

template <typename T>
VarAccessInfo<T> vl_vpi_var_access_info(const VerilatedVpioVarBase* vop, size_t bitCount,
                                        size_t addOffset) {
    // VarAccessInfo generation
    // vop - variable to access (already indexed)
    // bitCount - how many bits to write/read
    // addOffset - additional offset to apply (within the packed array element)

    const size_t wordBits = sizeof(T) * 8;
    uint32_t varBits = vop->bitSize();

    if (vop->varp()->vltype() == VLVT_REAL) varBits *= sizeof(double) * 8;

    // make sure we're not trying to write outside var bounds
    assert(varBits > addOffset);
    bitCount = std::min(bitCount, varBits - addOffset);

    VarAccessInfo<T> info;
    info.m_datap = reinterpret_cast<T*>(vop->varDatap());
    if (vop->varp()->vltype() == VLVT_WDATA) {
        assert(sizeof(T) == sizeof(EData));
        assert(bitCount <= wordBits);
        info.m_wordOffset = (vop->bitOffset() + addOffset) / wordBits;
        info.m_bitOffset = (vop->bitOffset() + addOffset) % wordBits;
        if (bitCount + info.m_bitOffset <= wordBits) {
            // within single word
            if (bitCount == wordBits)
                info.m_maskLo = ~static_cast<T>(0);
            else
                info.m_maskLo = (static_cast<T>(1) << bitCount) - 1;
            info.m_maskLo = info.m_maskLo << info.m_bitOffset;
            info.m_maskHi = 0;
        } else {
            // straddles word boundary
            info.m_maskLo = (static_cast<T>(1) << (wordBits - info.m_bitOffset)) - 1;
            info.m_maskLo = info.m_maskLo << info.m_bitOffset;
            info.m_maskHi = (static_cast<T>(1) << (bitCount + info.m_bitOffset - wordBits)) - 1;
        }
    } else {
        info.m_wordOffset = 0;
        info.m_bitOffset = vop->bitOffset() + addOffset;
        assert(bitCount + info.m_bitOffset <= wordBits);
        if (bitCount < wordBits) {
            info.m_maskLo = (static_cast<T>(1) << bitCount) - 1;
            info.m_maskLo = info.m_maskLo << info.m_bitOffset;
        } else {
            info.m_maskLo = ~static_cast<T>(0);
        }
        info.m_maskHi = 0;
    }
    return info;
}

template <typename T>
T vl_vpi_get_word_gen(const VerilatedVpioVarBase* vop, size_t bitCount, size_t addOffset) {
    const size_t wordBits = sizeof(T) * 8;
    const VarAccessInfo<T> info = vl_vpi_var_access_info<T>(vop, bitCount, addOffset);
    if (info.m_maskHi)
        return ((info.m_datap[info.m_wordOffset] & info.m_maskLo) >> info.m_bitOffset)
               | ((info.m_datap[info.m_wordOffset + 1] & info.m_maskHi)
                  << (wordBits - info.m_bitOffset));
    else
        return (info.m_datap[info.m_wordOffset] & info.m_maskLo) >> info.m_bitOffset;
}

template <typename T>
void vl_vpi_put_word_gen(const VerilatedVpioVar* vop, T word, size_t bitCount, size_t addOffset) {
    const size_t wordBits = sizeof(T) * 8;
    const VarAccessInfo<T> info = vl_vpi_var_access_info<T>(vop, bitCount, addOffset);

    if (info.m_maskHi) {
        info.m_datap[info.m_wordOffset + 1]
            = (info.m_datap[info.m_wordOffset + 1] & ~info.m_maskHi)
              | ((word >> (wordBits - info.m_bitOffset)) & info.m_maskHi);
    }
    // cppcheck-suppress unreadVariable
    info.m_datap[info.m_wordOffset] = (info.m_datap[info.m_wordOffset] & ~info.m_maskLo)
                                      | ((word << info.m_bitOffset) & info.m_maskLo);
}

// bitCount: maximum number of bits to read, will stop earlier if it reaches the var bounds
// addOffset: additional read bitoffset
QData vl_vpi_get_word(const VerilatedVpioVarBase* vop, size_t bitCount, size_t addOffset) {
    switch (vop->varp()->vltype()) {
    case VLVT_UINT8: return vl_vpi_get_word_gen<CData>(vop, bitCount, addOffset);
    case VLVT_UINT16: return vl_vpi_get_word_gen<SData>(vop, bitCount, addOffset);
    case VLVT_UINT32: return vl_vpi_get_word_gen<IData>(vop, bitCount, addOffset);
    case VLVT_UINT64: return vl_vpi_get_word_gen<QData>(vop, bitCount, addOffset);
    case VLVT_WDATA: return vl_vpi_get_word_gen<EData>(vop, bitCount, addOffset);
    default:
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vltype (%d)", __func__,
                      vop->varp()->vltype());
        return 0;
    }
}

// word: data to be written
// bitCount: maximum number of bits to write, will stop earlier if it reaches the var bounds
// addOffset: additional write bitoffset
void vl_vpi_put_word(const VerilatedVpioVar* vop, QData word, size_t bitCount, size_t addOffset) {
    switch (vop->varp()->vltype()) {
    case VLVT_UINT8: vl_vpi_put_word_gen<CData>(vop, word, bitCount, addOffset); break;
    case VLVT_UINT16: vl_vpi_put_word_gen<SData>(vop, word, bitCount, addOffset); break;
    case VLVT_UINT32: vl_vpi_put_word_gen<IData>(vop, word, bitCount, addOffset); break;
    case VLVT_UINT64: vl_vpi_put_word_gen<QData>(vop, word, bitCount, addOffset); break;
    case VLVT_WDATA: vl_vpi_put_word_gen<EData>(vop, word, bitCount, addOffset); break;
    default:
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vltype (%d)", __func__,
                      vop->varp()->vltype());
    }
}

void vl_vpi_get_value(const VerilatedVpioVarBase* vop, p_vpi_value valuep) {
    const VerilatedVar* const varp = vop->varp();
    void* const varDatap = vop->varDatap();

    if (!vl_check_format(vop, valuep, true)) return;
    // string data type is dynamic and may vary in size during simulation
    static thread_local std::string t_outDynamicStr;

    const int varBits = vop->bitSize();

    // __VforceRd already has the correct value, but that signal is not public and thus not
    // present in the scope's m_varsp map, so its value has to be recreated using the __VforceEn
    // and __VforceVal signals.
    // TODO: Implement a way to retrieve __VforceRd, rather than needing to recreate it.
    const auto forceControlSignals
        = vop->varp()->isForceable()
              ? VerilatedVpiImp::getForceControlSignals(vop)
              : std::pair<VerilatedVpiImp::vopGuard_t, VerilatedVpiImp::vopGuard_t>{
                    VerilatedVpiImp::vopGuard_t{nullptr, VerilatedVpiImp::releaseVop},
                    VerilatedVpiImp::vopGuard_t{nullptr, VerilatedVpiImp::releaseVop}};
    const VerilatedVpioVarBase* const forceEnableSignalVop = forceControlSignals.first.get();
    const VerilatedVpioVarBase* const forceValueSignalVop = forceControlSignals.second.get();
    t_vpi_error_info getForceControlSignalsError{};
    const bool errorOccurred = vpi_chk_error(&getForceControlSignalsError);
    // LCOV_EXCL_START - Cannot test, since getForceControlSignals does not (currently) produce
    // any notices or warnings.
    if (errorOccurred && getForceControlSignalsError.level < vpiError) {
        vpi_printf(getForceControlSignalsError.message);
        VL_VPI_ERROR_RESET_();
    }  // LCOV_EXCL_STOP
    // NOLINTNEXTLINE(readability-simplify-boolean-expr);
    if (VL_UNLIKELY(
            (errorOccurred && getForceControlSignalsError.level >= vpiError)
            || (vop->varp()->isForceable() && (!forceEnableSignalVop || !forceValueSignalVop)))) {

        // Check if getForceControlSignals provided any additional error info
        const bool gotErrorMessage = vpi_chk_error(&getForceControlSignalsError);
        const std::string previousErrorMessage
            = gotErrorMessage
                  ? std::string{" Error message: "} + getForceControlSignalsError.message
                  : "";

        VL_VPI_ERROR_(__FILE__, __LINE__,
                      "%s: Signal '%s' is marked forceable, but force "
                      "control signals could not be retrieved.%s",
                      __func__, vop->fullname(),
                      gotErrorMessage ? previousErrorMessage.c_str() : "");
        return;
    }

    const std::function<QData(const VerilatedVpioVarBase*, size_t, size_t)> getForceableSignalWord
        = [forceEnableSignalVop, forceValueSignalVop](const VerilatedVpioVarBase* baseSignalVop,
                                                      size_t bitCount, size_t addOffset) -> QData {
        // variables are QData, even though signals may have different representation, because any
        // extraneous bits are simply truncated upon implicit casting when this function is called.
        const QData baseSignalData = vl_vpi_get_word(baseSignalVop, bitCount, addOffset);
        const QData forceEnableData = vl_vpi_get_word(forceEnableSignalVop, bitCount, addOffset);
        const QData forceValueData = vl_vpi_get_word(forceValueSignalVop, bitCount, addOffset);
        const QData readData
            = (forceEnableData & forceValueData) | (~forceEnableData & baseSignalData);
        return readData;
    };

    const std::function<QData(const VerilatedVpioVarBase*, size_t, size_t)> get_word
        = vop->varp()->isForceable() ? getForceableSignalWord : vl_vpi_get_word;

    // We used to presume vpiValue.format = vpiIntVal or if single bit vpiScalarVal
    // This may cause backward compatibility issues with older code.
    if (valuep->format == vpiVectorVal) {
        // Vector pointer must come from our memory pool
        // It only needs to persist until the next vpi_get_value
        static thread_local t_vpi_vecval t_out[VL_VALUE_STRING_MAX_WORDS * 2];
        valuep->value.vector = t_out;
        if (varp->vltype() == VLVT_WDATA) {
            const int words = VL_WORDS_I(varBits);
            if (VL_UNCOVERABLE(words >= VL_VALUE_STRING_MAX_WORDS)) {
                VL_VPI_ERROR_(
                    __FILE__, __LINE__,
                    "vpi_get_value with more than VL_VALUE_STRING_MAX_WORDS; increase and "
                    "recompile");
                return;
            }
            for (int i = 0; i < words; ++i) {
                t_out[i].aval = get_word(vop, 32, i * 32);
                t_out[i].bval = 0;
            }
            return;
        } else if (varp->vltype() == VLVT_UINT64 && varBits > 32) {
            const QData data = get_word(vop, 64, 0);
            t_out[1].aval = static_cast<IData>(data >> 32ULL);
            t_out[1].bval = 0;
            t_out[0].aval = static_cast<IData>(data);
            t_out[0].bval = 0;
            return;
        } else {
            t_out[0].aval = get_word(vop, 32, 0);
            t_out[0].bval = 0;
            return;
        }
    } else if (valuep->format == vpiBinStrVal) {
        t_outDynamicStr.resize(varBits);

        static thread_local std::vector<uint8_t> forceReadCData;
        forceReadCData
            = vop->varp()->isForceable()
                  ? VerilatedVpiImp::createReadDataVector<uint8_t>(
                        varDatap,
                        {forceEnableSignalVop->varDatap(), forceValueSignalVop->varDatap()},
                        vop->bitSize())
                  : std::vector<uint8_t>{};
        const uint8_t* const varCDatap = vop->varp()->isForceable()
                                             ? forceReadCData.data()
                                             : reinterpret_cast<CData*>(varDatap);

        const CData* datap = varCDatap;
        for (size_t i = 0; i < varBits; ++i) {
            const size_t pos = i + vop->bitOffset();
            const char val = (datap[pos >> 3] >> (pos & 7)) & 1;
            t_outDynamicStr[varBits - i - 1] = val ? '1' : '0';
        }
        valuep->value.str = const_cast<PLI_BYTE8*>(t_outDynamicStr.c_str());
        return;
    } else if (valuep->format == vpiOctStrVal) {
        const int chars = (varBits + 2) / 3;
        t_outDynamicStr.resize(chars);
        for (size_t i = 0; i < chars; ++i) {
            const char val = get_word(vop, 3, i * 3);
            t_outDynamicStr[chars - i - 1] = '0' + val;
        }
        valuep->value.str = const_cast<PLI_BYTE8*>(t_outDynamicStr.c_str());
        return;
    } else if (valuep->format == vpiDecStrVal) {
        if (varp->vltype() == VLVT_UINT8) {
            vl_strprintf(t_outDynamicStr, "%hhu", static_cast<unsigned char>(get_word(vop, 8, 0)));
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_strprintf(t_outDynamicStr, "%hu",
                         static_cast<unsigned short>(get_word(vop, 16, 0)));
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_strprintf(t_outDynamicStr, "%u", static_cast<unsigned int>(get_word(vop, 32, 0)));
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_strprintf(t_outDynamicStr, "%llu",  // lintok-format-ll
                         static_cast<unsigned long long>(get_word(vop, 64, 0)));
        }
        valuep->value.str = const_cast<PLI_BYTE8*>(t_outDynamicStr.c_str());
        return;
    } else if (valuep->format == vpiHexStrVal) {
        const int chars = (varBits + 3) >> 2;
        t_outDynamicStr.resize(chars);
        for (size_t i = 0; i < chars; ++i) {
            const char val = get_word(vop, 4, i * 4);
            t_outDynamicStr[chars - i - 1] = "0123456789abcdef"[static_cast<int>(val)];
        }
        valuep->value.str = const_cast<PLI_BYTE8*>(t_outDynamicStr.c_str());
        return;
    } else if (valuep->format == vpiStringVal) {
        if (varp->vltype() == VLVT_STRING) {
            if (varp->isParam()) {
                valuep->value.str = reinterpret_cast<char*>(varDatap);
                return;
            } else {
                t_outDynamicStr = *vop->varStringDatap();
                valuep->value.str = const_cast<char*>(t_outDynamicStr.c_str());
                return;
            }
        } else {
            const int chars = VL_BYTES_I(varBits);
            t_outDynamicStr.resize(chars);
            for (size_t i = 0; i < chars; ++i) {
                const char val = get_word(vop, 8, i * 8);
                // other simulators replace [leading?] zero chars with spaces, replicate here.
                t_outDynamicStr[chars - i - 1] = val ? val : ' ';
            }
            valuep->value.str = const_cast<PLI_BYTE8*>(t_outDynamicStr.c_str());
            return;
        }
    } else if (valuep->format == vpiIntVal) {
        valuep->value.integer = get_word(vop, 32, 0);
        return;
    } else if (valuep->format == vpiRealVal) {
        // Only cover the scalar case, since reals cannot be packed (IEEE 1800, section 7.4.1), and
        // unpacked arrays are not supported for forcing in Verilator (#4735).
        if (vop->varp()->isForceable() && *forceEnableSignalVop->varCDatap())
            valuep->value.real = *forceValueSignalVop->varRealDatap();
        else
            valuep->value.real = *vop->varRealDatap();

        return;
    } else if (valuep->format == vpiScalarVal) {
        valuep->value.scalar = get_word(vop, 32, 0) ? vpi1 : vpi0;
        return;
    } else if (valuep->format == vpiSuppressVal) {
        return;
    }
    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) as requested for %s", __func__,
                  VerilatedVpiError::strFromVpiVal(valuep->format), vop->fullname());
}

void vpi_get_value(vpiHandle object, p_vpi_value valuep) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_get_value %p\n", object););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!valuep)) return;

    if (const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object)) {
        vl_vpi_get_value(vop, valuep);
        return;
    } else if (const VerilatedVpioParam* const vop = VerilatedVpioParam::castp(object)) {
        vl_vpi_get_value(vop, valuep);
        return;
    } else if (const VerilatedVpioConst* const vop = VerilatedVpioConst::castp(object)) {
        if (valuep->format == vpiIntVal) {
            valuep->value.integer = vop->num();
            return;
        }
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) for %s", __func__,
                      VerilatedVpiError::strFromVpiVal(valuep->format), vop->fullname());
        return;
    }
    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vpiHandle (%p)", __func__, object);
}

vpiHandle vpi_put_value(vpiHandle object, p_vpi_value valuep, p_vpi_time /*time_p*/,
                        PLI_INT32 flags) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_put_value %p %p\n", object, valuep););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!valuep)) {
        VL_VPI_WARNING_(__FILE__, __LINE__, "Ignoring vpi_put_value with nullptr value pointer");
        return nullptr;
    }
    const PLI_INT32 delay_mode = flags & 0xfff;
    const PLI_INT32 forceFlag = flags & 0xfff;
    if (const VerilatedVpioVar* const baseSignalVop = VerilatedVpioVar::castp(object)) {
        VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi:   vpi_put_value name=%s fmt=%d vali=%d\n",
                                    baseSignalVop->fullname(), valuep->format,
                                    valuep->value.integer);
                        VL_DBG_MSGF("- vpi:   varp=%p  putatp=%p\n",
                                    baseSignalVop->varp()->datap(), baseSignalVop->varDatap()););

        if (VL_UNLIKELY(!baseSignalVop->varp()->isPublicRW())) {
            VL_VPI_ERROR_(__FILE__, __LINE__,
                          "vpi_put_value was used on signal marked read-only,"
                          " use public_flat_rw instead for '%s'",
                          baseSignalVop->fullname());
            return nullptr;
        }

        // NOLINTNEXTLINE(readability-simplify-boolean-expr);
        if (VL_UNLIKELY((forceFlag == vpiForceFlag || forceFlag == vpiReleaseFlag)
                        && !baseSignalVop->varp()->isForceable())) {
            VL_VPI_ERROR_("", 0, "vpi_put_value used with %s on non-forceable signal '%s'",
                          forceFlag == vpiForceFlag ? "vpiForceFlag" : "vpiReleaseFlag",
                          baseSignalVop->fullname());
            return nullptr;
        }
        if (!vl_check_format(baseSignalVop, valuep, false)) return nullptr;
        if (delay_mode == vpiInertialDelay) {
            if (!VerilatedVpiPutHolder::canInertialDelay(valuep)) {
                VL_VPI_WARNING_(
                    __FILE__, __LINE__,
                    "%s: Unsupported p_vpi_value as requested for '%s' with vpiInertialDelay",
                    __func__, baseSignalVop->fullname());
                return nullptr;
            }
            VerilatedVpiImp::inertialDelay(baseSignalVop, valuep);
            return object;
        }
        VerilatedVpiImp::evalNeeded(true);
        const int varBits = baseSignalVop->bitSize();

        const auto forceControlSignals
            = baseSignalVop->varp()->isForceable()
                      && (forceFlag == vpiForceFlag || forceFlag == vpiReleaseFlag)
                  ? VerilatedVpiImp::getForceControlSignals(baseSignalVop)
                  : std::pair<VerilatedVpiImp::vopGuard_t, VerilatedVpiImp::vopGuard_t>{
                        VerilatedVpiImp::vopGuard_t{nullptr, VerilatedVpiImp::releaseVop},
                        VerilatedVpiImp::vopGuard_t{nullptr, VerilatedVpiImp::releaseVop}};
        const VerilatedVpioVar* const forceEnableSignalVop = forceControlSignals.first.get();
        const VerilatedVpioVar* const forceValueSignalVop = forceControlSignals.second.get();
        t_vpi_error_info getForceControlSignalsError{};
        bool errorOccurred = vpi_chk_error(&getForceControlSignalsError);
        // LCOV_EXCL_START - Cannot test, since getForceControlSignals does not (currently) produce
        // any notices or warnings.
        if (errorOccurred && getForceControlSignalsError.level < vpiError) {
            vpi_printf(getForceControlSignalsError.message);
            VL_VPI_ERROR_RESET_();
        }  // LCOV_EXCL_STOP
        // NOLINTNEXTLINE(readability-simplify-boolean-expr);
        if (VL_UNLIKELY(baseSignalVop->varp()->isForceable()
                        && (forceFlag == vpiForceFlag || forceFlag == vpiReleaseFlag)
                        && (!forceEnableSignalVop || !forceValueSignalVop))) {

            // Check if getForceControlSignals provided any additional error info
            const bool gotErrorMessage = vpi_chk_error(&getForceControlSignalsError);
            const std::string previousErrorMessage
                = gotErrorMessage
                      ? std::string{" Error message: "} + getForceControlSignalsError.message
                      : "";

            VL_VPI_ERROR_(__FILE__, __LINE__,
                          "%s: Signal '%s' with vpiHandle '%p' is marked forceable, but force "
                          "control signals could not be retrieved.%s",
                          __func__, baseSignalVop->fullname(), object,
                          gotErrorMessage ? previousErrorMessage.c_str() : "");
            return nullptr;
        }

        const VerilatedVpioVar* const valueVop
            = (forceFlag == vpiForceFlag) ? forceValueSignalVop : baseSignalVop;

        if (forceFlag == vpiForceFlag) {
            // Enable __VforceEn
            VerilatedVpiImp::setAllBitsToValue(forceEnableSignalVop, 1);
        }
        if (forceFlag == vpiReleaseFlag) {
            // If signal is continuously assigned, first clear the force enable bits, then get the
            // (non-forced) value. Else, get the (still forced) value first, then clear the force
            // enable bits.

            if (baseSignalVop->varp()->isContinuously())
                VerilatedVpiImp::setAllBitsToValue(forceEnableSignalVop, 0);

            vl_vpi_get_value(baseSignalVop, valuep);

            t_vpi_error_info baseValueGetError{};
            errorOccurred = vpi_chk_error(&baseValueGetError);
            // LCOV_EXCL_START - Cannot test, because missing signal would already trigger error
            // earlier, at the getForceControlSignals stage
            // NOLINTNEXTLINE(readability-simplify-boolean-expr);
            if (VL_UNLIKELY(errorOccurred && baseValueGetError.level >= vpiError)) {
                const std::string baseValueSignalName = baseSignalVop->fullname();
                const std::string previousErrorMessage = baseValueGetError.message;
                VL_VPI_ERROR_(__FILE__, __LINE__,
                              "%s: Could not retrieve value of signal '%s' with "
                              "vpiHandle '%p'. Error message: %s",
                              __func__, baseValueSignalName.c_str(), object,
                              previousErrorMessage.c_str());
                return nullptr;
            }
            // NOLINTNEXTLINE(readability-simplify-boolean-expr);
            if (VL_UNCOVERABLE(errorOccurred && baseValueGetError.level < vpiError)) {
                vpi_printf(baseValueGetError.message);
                VL_VPI_ERROR_RESET_();
            }  // LCOV_EXCL_STOP

            if (!baseSignalVop->varp()->isContinuously())
                VerilatedVpiImp::setAllBitsToValue(forceEnableSignalVop, 0);

            return nullptr;
        }

        if (valuep->format == vpiVectorVal) {
            if (VL_UNLIKELY(!valuep->value.vector)) return nullptr;
            if (valueVop->varp()->vltype() == VLVT_WDATA) {
                const int words = VL_WORDS_I(varBits);
                for (int i = 0; i < words; ++i)
                    vl_vpi_put_word(valueVop, valuep->value.vector[i].aval, 32, i * 32);
                return object;
            } else if (valueVop->varp()->vltype() == VLVT_UINT64 && varBits > 32) {
                const QData val = (static_cast<QData>(valuep->value.vector[1].aval) << 32)
                                  | static_cast<QData>(valuep->value.vector[0].aval);
                vl_vpi_put_word(valueVop, val, 64, 0);
                return object;
            } else {
                vl_vpi_put_word(valueVop, valuep->value.vector[0].aval, 32, 0);
                return object;
            }
        } else if (valuep->format == vpiBinStrVal) {
            const int len = std::strlen(valuep->value.str);
            CData* const datap = reinterpret_cast<CData*>(valueVop->varDatap());
            for (int i = 0; i < varBits; ++i) {
                const bool set = (i < len) && (valuep->value.str[len - i - 1] == '1');
                const size_t pos = valueVop->bitOffset() + i;

                if (set)
                    datap[pos >> 3] |= 1 << (pos & 7);
                else
                    datap[pos >> 3] &= ~(1 << (pos & 7));
            }
            return object;
        } else if (valuep->format == vpiOctStrVal) {
            const int len = std::strlen(valuep->value.str);
            for (int i = 0; i < len; ++i) {
                unsigned char digit = valuep->value.str[len - i - 1] - '0';
                if (digit > 7) {  // If str was < '0', then as unsigned, digit > 7
                    VL_VPI_WARNING_(__FILE__, __LINE__,
                                    "%s: Non octal character '%c' in '%s' as value %s for %s",
                                    __func__, digit + '0', valuep->value.str,
                                    VerilatedVpiError::strFromVpiVal(valuep->format),
                                    valueVop->fullname());
                    digit = 0;
                }
                vl_vpi_put_word(valueVop, digit, 3, i * 3);
            }
            return object;
        } else if (valuep->format == vpiDecStrVal) {
            char remainder[16];
            unsigned long long val;
            const int success = std::sscanf(valuep->value.str, "%30llu%15s",  // lintok-format-ll
                                            &val, remainder);
            if (success < 1) {
                VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Parsing failed for '%s' as value %s for %s",
                              __func__, valuep->value.str,
                              VerilatedVpiError::strFromVpiVal(valuep->format),
                              valueVop->fullname());
                return nullptr;
            }
            if (success > 1) {
                VL_VPI_WARNING_(
                    __FILE__, __LINE__, "%s: Trailing garbage '%s' in '%s' as value %s for %s",
                    __func__, remainder, valuep->value.str,
                    VerilatedVpiError::strFromVpiVal(valuep->format), valueVop->fullname());
            }
            vl_vpi_put_word(valueVop, val, 64, 0);
            return object;
        } else if (valuep->format == vpiHexStrVal) {
            const int chars = (varBits + 3) >> 2;
            const char* val = valuep->value.str;
            // skip hex ident if one is detected at the start of the string
            if (val[0] == '0' && (val[1] == 'x' || val[1] == 'X')) val += 2;
            const int len = std::strlen(val);
            for (int i = 0; i < chars; ++i) {
                char hex;
                // compute hex digit value
                if (i < len) {
                    const char digit = val[len - i - 1];
                    if (digit >= '0' && digit <= '9') {
                        hex = digit - '0';
                    } else if (digit >= 'a' && digit <= 'f') {
                        hex = digit - 'a' + 10;
                    } else if (digit >= 'A' && digit <= 'F') {
                        hex = digit - 'A' + 10;
                    } else {
                        VL_VPI_WARNING_(__FILE__, __LINE__,
                                        "%s: Non hex character '%c' in '%s' as value %s for %s",
                                        __func__, digit, valuep->value.str,
                                        VerilatedVpiError::strFromVpiVal(valuep->format),
                                        valueVop->fullname());
                        hex = 0;
                    }
                } else {
                    hex = 0;
                }
                // assign hex digit value to destination
                vl_vpi_put_word(valueVop, hex, 4, i * 4);
            }
            return object;
        } else if (valuep->format == vpiStringVal) {
            if (valueVop->varp()->vltype() == VLVT_STRING) {
                // Does not use valueVop, because strings are not forceable anyway
                *(baseSignalVop->varStringDatap()) = valuep->value.str;
                return object;
            } else {
                const int chars = VL_BYTES_I(varBits);
                const int len = std::strlen(valuep->value.str);
                for (int i = 0; i < chars; ++i) {
                    // prepend with 0 values before placing string the least significant bytes
                    const char c = (i < len) ? valuep->value.str[len - i - 1] : 0;
                    vl_vpi_put_word(valueVop, c, 8, i * 8);
                }
            }
            return object;
        } else if (valuep->format == vpiIntVal) {
            vl_vpi_put_word(valueVop, valuep->value.integer, 64, 0);
            return object;
        } else if (valuep->format == vpiRealVal) {
            if (valueVop->varp()->vltype() == VLVT_REAL) {
                *(valueVop->varRealDatap()) = valuep->value.real;
                return object;
            }
        } else if (valuep->format == vpiScalarVal) {
            vl_vpi_put_word(valueVop, (valuep->value.scalar == vpi1 ? 1 : 0), 1, 0);
            return object;
        }
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) as requested for %s",
                      __func__, VerilatedVpiError::strFromVpiVal(valuep->format),
                      valueVop->fullname());
        return nullptr;
    } else if (const VerilatedVpioParam* const vop = VerilatedVpioParam::castp(object)) {
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Ignoring vpi_put_value to vpiParameter: %s",
                        __func__, vop->fullname());
        return nullptr;
    } else if (const VerilatedVpioConst* const vop = VerilatedVpioConst::castp(object)) {
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Ignoring vpi_put_value to vpiConstant: %s",
                        __func__, vop->fullname());
        return nullptr;
    }
    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vpiHandle (%p)", __func__, object);
    return nullptr;
}

bool vl_check_array_format(const VerilatedVar* varp, const p_vpi_arrayvalue arrayvalue_p,
                           const char* fullname) {
    if (arrayvalue_p->format == vpiVectorVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return true;
        default:;  // LCOV_EXCL_LINE
        }
    } else if (arrayvalue_p->format == vpiIntVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32: return true;
        default:;  // LCOV_EXCL_LINE
        }
    } else if ((arrayvalue_p->format == vpiRawTwoStateVal)
               || (arrayvalue_p->format == vpiRawFourStateVal)) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64:
        case VLVT_WDATA: return true;
        default:;  // LCOV_EXCL_LINE
        }
    } else if (arrayvalue_p->format == vpiShortIntVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16: return true;
        default:;  // LCOV_EXCL_LINE
        }
    } else if (arrayvalue_p->format == vpiLongIntVal) {
        switch (varp->vltype()) {
        case VLVT_UINT8:
        case VLVT_UINT16:
        case VLVT_UINT32:
        case VLVT_UINT64: return true;
        default:;  // LCOV_EXCL_LINE
        }
    }

    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) as requested for %s", __func__,
                  VerilatedVpiError::strFromVpiVal(arrayvalue_p->format), fullname);

    return false;
}

template <typename T, typename K>
void vl_get_value_array_integrals(unsigned index, const unsigned num, const unsigned size,
                                  const unsigned packedSize, const bool leftIsLow, const T* src,
                                  K* dst) {
    static_assert(sizeof(K) >= sizeof(T), "size of type K is less than size of type T");
    for (int i = 0; i < num; ++i) {
        dst[i] = src[index];
        index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                : index == 0 ? size - 1
                             : index - 1;
    }
}

template <typename T, typename K>
void vl_put_value_array_integrals(unsigned index, const unsigned num, const unsigned size,
                                  const unsigned packedSize, const bool leftIsLow, const T* src,
                                  K* dst) {
    static_assert(std::is_integral<T>::value, "type T is not an integral type");
    static_assert(std::is_unsigned<T>::value, "type T is not unsigned");
    static_assert(sizeof(T) >= sizeof(K), "size of type T is less than size of type K");
    const unsigned element_size_bytes = VL_BYTES_I(packedSize);
    const T mask = element_size_bytes == sizeof(T)
                       ? static_cast<T>(-1)
                       : ~(static_cast<T>(-1) << (element_size_bytes * 8));
    for (unsigned i = 0; i < num; ++i) {
        dst[index] = src[i] & static_cast<T>(mask);
        index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                : index == 0 ? size - 1
                             : index - 1;
    }
}

template <typename T>
void vl_get_value_array_vectors(unsigned index, const unsigned num, const unsigned size,
                                const unsigned packedSize, const bool leftIsLow, const T* src,
                                p_vpi_vecval dst) {
    static_assert(std::is_unsigned<T>::value,
                  "type T is not unsigned");  // ensure logical right shift
    const unsigned element_size_words = VL_WORDS_I(packedSize);
    if (sizeof(T) == sizeof(QData)) {
        for (unsigned i = 0; i < num; ++i) {
            dst[i * 2].aval = static_cast<QData>(src[index]);
            dst[i * 2].bval = 0;
            dst[(i * 2) + 1].aval = static_cast<QData>(src[index]) >> 32;
            dst[(i * 2) + 1].bval = 0;
            index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                    : index == 0 ? size - 1
                                 : index - 1;
        }
    } else {
        for (unsigned i = 0; i < num; ++i) {
            const size_t dst_index = i * element_size_words;
            const size_t src_index = index * element_size_words;
            for (unsigned j = 0; j < element_size_words; ++j) {
                dst[dst_index + j].aval = src[src_index + j];
                dst[dst_index + j].bval = 0;
            }
            index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                    : index == 0 ? size - 1
                                 : index - 1;
        }
    }
}

template <typename T>
void vl_put_value_array_vectors(unsigned index, const unsigned num, const unsigned size,
                                const unsigned packedSize, const bool leftIsLow,
                                const bool fourState, const p_vpi_vecval src, T* dst) {
    static_assert(std::is_unsigned<T>::value, "type T is not unsigned");
    static_assert(std::is_integral<T>::value, "type T is not an integral type");
    const unsigned element_size_bytes VL_BYTES_I(packedSize);
    const unsigned element_size_words VL_WORDS_I(packedSize);
    if (sizeof(T) == sizeof(QData)) {  //destination is QDATA
        const QData mask = element_size_bytes == sizeof(T)
                               ? static_cast<QData>(-1)
                               : ~(static_cast<QData>(-1) << (element_size_bytes * 8));
        for (unsigned i = 0; i < num; ++i) {
            dst[index] = src[i * 2].aval;
            dst[index]
                |= (static_cast<QData>(src[(i * 2) + 1].aval) << (sizeof(PLI_UINT32) * 8)) & mask;
            index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                    : index == 0 ? size - 1
                                 : index - 1;
        }
    } else {
        for (unsigned i = 0; i < num; ++i) {
            unsigned bytes_stored = 0;
            for (unsigned j = 0; j < element_size_words; ++j) {
                if (bytes_stored >= element_size_bytes) break;
                const T mask
                    = (element_size_bytes - bytes_stored) >= sizeof(PLI_UINT32)
                          ? static_cast<T>(-1)
                          : ~(static_cast<T>(-1) << ((element_size_bytes - bytes_stored) * 8));
                dst[(index * element_size_words) + j]
                    = static_cast<T>(src[(i * element_size_words) + j].aval) & mask;
                bytes_stored += sizeof(PLI_UINT32);
            }
            index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                    : index == 0 ? size - 1
                                 : index - 1;
        }
    }
}

template <typename T>
void vl_get_value_array_rawvals(unsigned index, unsigned num, const unsigned size,
                                const unsigned packedSize, const bool leftIsLow,
                                const bool fourState, const T* src, PLI_BYTE8* dst) {
    static_assert(std::is_unsigned<T>::value,
                  "type T is not unsigned");  //ensure logical right shift
    const unsigned element_size_bytes VL_BYTES_I(packedSize);
    const unsigned element_size_repr = (element_size_bytes + sizeof(T) - 1) / sizeof(T);
    size_t dst_index = 0;
    while (num-- > 0) {
        const size_t src_offset = index * element_size_repr;
        unsigned bytes_copied = 0;
        for (unsigned j = 0; j < element_size_repr; ++j) {
            const T& src_data = src[src_offset + j];
            for (unsigned k = 0; k < sizeof(T); ++k) {
                if (bytes_copied++ == element_size_bytes) break;
                dst[dst_index++] = src_data >> (k * 8);
            }
        }
        if (fourState) {
            std::fill(dst + dst_index, dst + dst_index + element_size_bytes, 0);
            dst_index += element_size_bytes;
        }
        index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                : index == 0 ? size - 1
                             : index - 1;
    }
}

template <typename T>
void vl_put_value_array_rawvals(unsigned index, const unsigned num, const unsigned size,
                                const unsigned packedSize, const bool leftIsLow,
                                const bool fourState, const PLI_UBYTE8* src, T* dst) {
    const unsigned element_size_bytes VL_BYTES_I(packedSize);
    const unsigned element_size_repr = (element_size_bytes + sizeof(T) - 1) / sizeof(T);
    for (unsigned i = 0; i < num; ++i) {
        unsigned bytes_copied = 0;
        const size_t dst_offset = index * element_size_repr;
        const size_t src_offset = i * element_size_bytes;
        for (unsigned j = 0; j < element_size_repr; ++j) {
            T& dst_data = dst[dst_offset + j];
            for (unsigned k = 0; k < sizeof(T); ++k) {
                if (bytes_copied == element_size_bytes) break;
                const unsigned src_index
                    = fourState ? (src_offset * 2) + bytes_copied : (src_offset) + bytes_copied;
                dst_data &= ~((static_cast<T>(0xFF) & 0xFF) << (k * 8));
                dst_data |= ((static_cast<T>(src[src_index]) & 0xFF) << (k * 8));
                bytes_copied++;
            }
        }
        index = leftIsLow    ? index == (size - 1) ? 0 : index + 1
                : index == 0 ? size - 1
                             : index - 1;
    }
}

void vl_get_value_array(vpiHandle object, p_vpi_arrayvalue arrayvalue_p, const PLI_INT32* index_p,
                        PLI_UINT32 num) {
    const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
    if (!vl_check_array_format(vop->varp(), arrayvalue_p, vop->fullname())) return;

    const VerilatedVar* const varp = vop->varp();

    static thread_local EData t_out_data[VL_VALUE_STRING_MAX_WORDS * 2];

    const unsigned size = vop->size();
    if (VL_UNCOVERABLE(num > size)) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Requested elements (%u) exceed array size (%u)",
                      __func__, num, size);
        return;
    }

    const bool leftIsLow = vop->rangep()->left() == vop->rangep()->low();
    const int index
        = leftIsLow ? index_p[0] - vop->rangep()->left() : vop->rangep()->left() - index_p[0];

    if (arrayvalue_p->format == vpiShortIntVal) {
        if (VL_UNCOVERABLE((sizeof(PLI_INT16) * num) >= VL_VALUE_STRING_MAX_CHARS)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_get_value_array with more than VL_VALUE_STRING_MAX_WORDS; "
                        "increase and recompile");
        }

        PLI_INT16* shortintsp = reinterpret_cast<PLI_INT16*>(t_out_data);
        arrayvalue_p->value.shortints = shortintsp;

        if (varp->vltype() == VLVT_UINT8) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varCDatap(), shortintsp);
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varSDatap(), shortintsp);
        }

        return;
    } else if (arrayvalue_p->format == vpiIntVal) {
        if (VL_UNCOVERABLE(num >= VL_VALUE_STRING_MAX_WORDS)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_get_value_array with more than VL_VALUE_STRING_MAX_WORDS; "
                        "increase and recompile");
        }

        PLI_INT32* integersp = reinterpret_cast<PLI_INT32*>(t_out_data);
        arrayvalue_p->value.integers = integersp;

        if (varp->vltype() == VLVT_UINT8) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varCDatap(), integersp);
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varSDatap(), integersp);
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varIDatap(), integersp);
        }

        return;
    } else if (arrayvalue_p->format == vpiLongIntVal) {
        if (VL_UNCOVERABLE((sizeof(PLI_INT64) * num) >= VL_VALUE_STRING_MAX_CHARS)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_get_value_array with more than VL_VALUE_STRING_MAX_WORDS; "
                        "increase and recompile");
        }

        PLI_INT64* longintsp = reinterpret_cast<PLI_INT64*>(t_out_data);
        arrayvalue_p->value.longints = longintsp;

        if (varp->vltype() == VLVT_UINT8) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varCDatap(), longintsp);
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varSDatap(), longintsp);
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varIDatap(), longintsp);
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_get_value_array_integrals(index, num, size, varp->entBits(), leftIsLow,
                                         vop->varQDatap(), longintsp);
        }

        return;
    } else if (arrayvalue_p->format == vpiVectorVal) {
        if (VL_UNCOVERABLE((VL_WORDS_I(varp->entBits()) * 2 * num) >= VL_VALUE_STRING_MAX_WORDS)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_get_value_array with more than VL_VALUE_STRING_MAX_WORDS; "
                        "increase and recompile");
        }

        p_vpi_vecval vectorsp = reinterpret_cast<p_vpi_vecval>(t_out_data);
        arrayvalue_p->value.vectors = vectorsp;

        if (varp->vltype() == VLVT_UINT8) {
            vl_get_value_array_vectors(index, num, size, varp->entBits(), leftIsLow,
                                       vop->varCDatap(), vectorsp);
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_get_value_array_vectors(index, num, size, varp->entBits(), leftIsLow,
                                       vop->varSDatap(), vectorsp);
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_get_value_array_vectors(index, num, size, varp->entBits(), leftIsLow,
                                       vop->varIDatap(), vectorsp);
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_get_value_array_vectors(index, num, size, varp->entBits(), leftIsLow,
                                       vop->varQDatap(), vectorsp);
        } else if (varp->vltype() == VLVT_WDATA) {
            vl_get_value_array_vectors(index, num, size, varp->entBits(), leftIsLow,
                                       vop->varEDatap(), vectorsp);
        }

        return;
    } else if (arrayvalue_p->format == vpiRawFourStateVal) {
        if (VL_UNCOVERABLE((VL_BYTES_I(varp->entBits()) * 2 * num) >= VL_VALUE_STRING_MAX_CHARS)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_get_value_array with more than VL_VALUE_STRING_MAX_WORDS; "
                        "increase and recompile");
        }

        PLI_BYTE8* valuep = reinterpret_cast<PLI_BYTE8*>(t_out_data);
        arrayvalue_p->value.rawvals = valuep;

        if (varp->vltype() == VLVT_UINT8) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true,
                                       vop->varCDatap(), valuep);
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true,
                                       vop->varSDatap(), valuep);
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true,
                                       vop->varIDatap(), valuep);
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true,
                                       vop->varQDatap(), valuep);
        } else if (varp->vltype() == VLVT_WDATA) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true,
                                       vop->varEDatap(), valuep);
        }

        return;
    } else if (arrayvalue_p->format == vpiRawTwoStateVal) {
        if (VL_UNCOVERABLE((VL_BYTES_I(varp->entBits()) * num) >= VL_VALUE_STRING_MAX_CHARS)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "vpi_get_value_array with more than VL_VALUE_STRING_MAX_WORDS; "
                        "increase and recompile");
        }

        PLI_BYTE8* valuep = reinterpret_cast<PLI_BYTE8*>(t_out_data);
        arrayvalue_p->value.rawvals = valuep;

        if (varp->vltype() == VLVT_UINT8) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false,
                                       vop->varCDatap(), valuep);
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false,
                                       vop->varSDatap(), valuep);
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false,
                                       vop->varIDatap(), valuep);
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false,
                                       vop->varQDatap(), valuep);
        } else if (varp->vltype() == VLVT_WDATA) {
            vl_get_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false,
                                       vop->varEDatap(), valuep);
        }

        return;
    }

    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) as requested for %s", __func__,
                  VerilatedVpiError::strFromVpiVal(arrayvalue_p->format), vop->fullname());
}

void vpi_get_value_array(vpiHandle object, p_vpi_arrayvalue arrayvalue_p, PLI_INT32* index_p,
                         PLI_UINT32 num) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_get_value_array %p\n", object););
    VerilatedVpiImp::assertOneCheck();

    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!object)) return;

    if (VL_UNLIKELY(!arrayvalue_p)) {
        VL_VPI_WARNING_(__FILE__, __LINE__,
                        "Ignoring vpi_get_value_array with null value pointer");
        return;
    }

    if (VL_UNLIKELY(!index_p)) {
        VL_VPI_WARNING_(__FILE__, __LINE__,
                        "Ignoring vpi_get_value_array with null index pointer");
        return;
    }

    const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
    if (VL_UNLIKELY(!vop)) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vpiHandle (%p)", __func__, object);
        return;
    }

    if (vop->type() != vpiRegArray) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported type (%p, %s)", __func__, object,
                      VerilatedVpiError::strFromVpiObjType(vop->type()));
        return;
    }

    const int lowRange = vop->rangep()->low();
    const int highRange = vop->rangep()->high();
    if ((index_p[0] > highRange) || (index_p[0] < lowRange)) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Index %u for object '%s' is out of bounds [%u,%u]",
                      __func__, index_p[0], vop->fullname(), lowRange, highRange);
        return;
    }

    if (arrayvalue_p->flags & vpiUserAllocFlag) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vpiUserAllocFlag (%x)", __func__,
                      arrayvalue_p->flags);
        return;
    }

    vl_get_value_array(object, arrayvalue_p, index_p, num);
}

void vl_put_value_array(vpiHandle object, p_vpi_arrayvalue arrayvalue_p, const PLI_INT32* index_p,
                        PLI_UINT32 num) {
    const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
    if (!vl_check_array_format(vop->varp(), arrayvalue_p, vop->fullname())) return;

    const VerilatedVar* const varp = vop->varp();

    const int size = vop->size();
    if (VL_UNCOVERABLE(num > size)) {
        VL_VPI_ERROR_(__FILE__, __LINE__,
                      "%s: Requested elements to set (%u) exceed array size (%u)", __func__, num,
                      size);
        return;
    }

    const bool leftIsLow = vop->rangep()->left() == vop->rangep()->low();
    const int index
        = leftIsLow ? index_p[0] - vop->rangep()->left() : vop->rangep()->left() - index_p[0];

    if (arrayvalue_p->format == vpiShortIntVal) {
        const PLI_UINT16* shortintsp
            = reinterpret_cast<PLI_UINT16*>(arrayvalue_p->value.shortints);

        if (varp->vltype() == VLVT_UINT8) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, shortintsp,
                                         vop->varCDatap());
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, shortintsp,
                                         vop->varSDatap());
        }

        return;
    } else if (arrayvalue_p->format == vpiIntVal) {
        const PLI_UINT32* integersp = reinterpret_cast<PLI_UINT32*>(arrayvalue_p->value.integers);

        if (varp->vltype() == VLVT_UINT8) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, integersp,
                                         vop->varCDatap());
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, integersp,
                                         vop->varSDatap());
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, integersp,
                                         vop->varIDatap());
        }

        return;
    } else if (arrayvalue_p->format == vpiLongIntVal) {
        const PLI_UINT64* longintsp = reinterpret_cast<PLI_UINT64*>(arrayvalue_p->value.longints);

        if (varp->vltype() == VLVT_UINT8) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, longintsp,
                                         vop->varCDatap());
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, longintsp,
                                         vop->varSDatap());
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, longintsp,
                                         vop->varIDatap());
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_put_value_array_integrals(index, num, size, varp->entBits(), leftIsLow, longintsp,
                                         vop->varQDatap());
        }

        return;
    } else if (arrayvalue_p->format == vpiVectorVal) {
        const p_vpi_vecval vectorsp = arrayvalue_p->value.vectors;

        if (varp->vltype() == VLVT_UINT8) {
            vl_put_value_array_vectors(index, num, size, varp->entBits(), leftIsLow, true,
                                       vectorsp, vop->varCDatap());
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_put_value_array_vectors(index, num, size, varp->entBits(), leftIsLow, true,
                                       vectorsp, vop->varSDatap());
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_put_value_array_vectors(index, num, size, varp->entBits(), leftIsLow, true,
                                       vectorsp, vop->varIDatap());
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_put_value_array_vectors(index, num, size, varp->entBits(), leftIsLow, true,
                                       vectorsp, vop->varQDatap());
        } else if (varp->vltype() == VLVT_WDATA) {
            vl_put_value_array_vectors(index, num, size, varp->entBits(), leftIsLow, true,
                                       vectorsp, vop->varEDatap());
        }

        return;
    } else if (arrayvalue_p->format == vpiRawFourStateVal) {
        const PLI_UBYTE8* valuep = reinterpret_cast<PLI_UBYTE8*>(arrayvalue_p->value.rawvals);

        if (varp->vltype() == VLVT_UINT8) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true, valuep,
                                       vop->varCDatap());
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true, valuep,
                                       vop->varSDatap());
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true, valuep,
                                       vop->varIDatap());
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true, valuep,
                                       vop->varQDatap());
        } else if (varp->vltype() == VLVT_WDATA) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, true, valuep,
                                       vop->varEDatap());
        }

        return;
    } else if (arrayvalue_p->format == vpiRawTwoStateVal) {
        const PLI_UBYTE8* valuep = reinterpret_cast<PLI_UBYTE8*>(arrayvalue_p->value.rawvals);

        if (varp->vltype() == VLVT_UINT8) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false, valuep,
                                       vop->varCDatap());
        } else if (varp->vltype() == VLVT_UINT16) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false, valuep,
                                       vop->varSDatap());
        } else if (varp->vltype() == VLVT_UINT32) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false, valuep,
                                       vop->varIDatap());
        } else if (varp->vltype() == VLVT_UINT64) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false, valuep,
                                       vop->varQDatap());
        } else if (varp->vltype() == VLVT_WDATA) {
            vl_put_value_array_rawvals(index, num, size, varp->entBits(), leftIsLow, false, valuep,
                                       vop->varEDatap());
        }

        return;
    }

    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported format (%s) as requested for %s", __func__,
                  VerilatedVpiError::strFromVpiVal(arrayvalue_p->format), vop->fullname());
}

void vpi_put_value_array(vpiHandle object, p_vpi_arrayvalue arrayvalue_p, PLI_INT32* index_p,
                         PLI_UINT32 num) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_put_value_array %p\n", object););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();

    if (VL_UNLIKELY(!arrayvalue_p)) {
        VL_VPI_WARNING_(__FILE__, __LINE__,
                        "Ignoring vpi_put_value_array with null value pointer");
        return;
    }

    if (VL_UNLIKELY(!index_p)) {
        VL_VPI_WARNING_(__FILE__, __LINE__,
                        "Ignoring vpi_put_value_array with null index pointer");
        return;
    }

    const VerilatedVpioVar* const vop = VerilatedVpioVar::castp(object);
    if (VL_UNLIKELY(!vop)) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported vpiHandle (%p)", __func__, object);
        return;
    }

    if (vop->type() != vpiRegArray) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported type (%p, %s)", __func__, object,
                      VerilatedVpiError::strFromVpiObjType(vop->type()));
        return;
    }

    const int lowRange = vop->rangep()->low();
    const int highRange = vop->rangep()->high();
    if ((index_p[0] > highRange) || (index_p[0] < lowRange)) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Index %u for object '%s' is out of bounds [%u,%u]",
                      __func__, index_p[0], vop->fullname(), lowRange, highRange);
        return;
    }

    if (VL_UNLIKELY(!vop->varp()->isPublicRW())) {
        VL_VPI_ERROR_(__FILE__, __LINE__,
                      "Ignoring vpi_put_value_array to signal marked read-only,"
                      " use public_flat_rw instead: %s",
                      vop->fullname());
        return;
    }

    if (arrayvalue_p->flags & (vpiPropagateOff | vpiOneValue)) {
        VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported flags (%x)", __func__,
                      arrayvalue_p->flags);
        return;
    }

    vl_put_value_array(object, arrayvalue_p, index_p, num);
}

// time processing

void vpi_get_time(vpiHandle object, p_vpi_time time_p) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    // cppcheck-suppress nullPointer
    if (VL_UNLIKELY(!time_p)) {
        VL_VPI_WARNING_(__FILE__, __LINE__, "Ignoring vpi_get_time with nullptr value pointer");
        return;
    }
    if (time_p->type == vpiSimTime) {
        const QData qtime = VL_TIME_Q();
        VlWide<2> itime;
        VL_SET_WQ(itime, qtime);
        time_p->low = itime[0];
        time_p->high = itime[1];
        return;
    } else if (time_p->type == vpiScaledRealTime) {
        double dtime = VL_TIME_D();
        if (const VerilatedVpioScope* const vop = VerilatedVpioScope::castp(object)) {
            const int scalePow10
                = Verilated::threadContextp()->timeprecision() - vop->scopep()->timeunit();
            const double scale = vl_time_multiplier(scalePow10);  // e.g. 0.0001
            dtime *= scale;
        }
        time_p->real = dtime;
        return;
    }
    VL_VPI_ERROR_(__FILE__, __LINE__, "%s: Unsupported type (%d)", __func__, time_p->type);
}

// I/O routines

PLI_UINT32 vpi_mcd_open(PLI_BYTE8* filenamep) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    return VL_FOPEN_NN(filenamep, "wb");
}

PLI_UINT32 vpi_mcd_close(PLI_UINT32 mcd) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    VL_FCLOSE_I(mcd);
    return 0;
}

PLI_BYTE8* vpi_mcd_name(PLI_UINT32 /*mcd*/) {
    VL_VPI_UNIMP_();
    return nullptr;
}

PLI_INT32 vpi_mcd_printf(PLI_UINT32 mcd, PLI_BYTE8* formatp, ...) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    va_list ap;
    va_start(ap, formatp);
    const int chars = vpi_mcd_vprintf(mcd, formatp, ap);
    va_end(ap);
    return chars;
}

PLI_INT32 vpi_printf(PLI_BYTE8* formatp, ...) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    va_list ap;
    va_start(ap, formatp);
    const int chars = vpi_vprintf(formatp, ap);
    va_end(ap);
    return chars;
}

// cppcheck-suppress constParameterPointer
PLI_INT32 vpi_vprintf(PLI_BYTE8* formatp, va_list ap) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    return VL_VPRINTF(formatp, ap);
}

// cppcheck-suppress constParameterPointer
PLI_INT32 vpi_mcd_vprintf(PLI_UINT32 mcd, PLI_BYTE8* format, va_list ap) {
    VerilatedVpiImp::assertOneCheck();
    FILE* const fp = VL_CVT_I_FP(mcd);
    VL_VPI_ERROR_RESET_();
    // cppcheck-suppress nullPointer
    if (VL_UNLIKELY(!fp)) return 0;
    const int chars = vfprintf(fp, format, ap);
    return chars;
}

PLI_INT32 vpi_flush(void) {
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    Verilated::runFlushCallbacks();
    return 0;  // Gcc coverage bug // LCOV_EXCL_LINE
}

PLI_INT32 vpi_mcd_flush(PLI_UINT32 mcd) {
    VerilatedVpiImp::assertOneCheck();
    FILE* const fp = VL_CVT_I_FP(mcd);
    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!fp)) return 1;
    std::fflush(fp);
    return 0;
}

// utility routines

PLI_INT32 vpi_compare_objects(vpiHandle /*object1*/, vpiHandle /*object2*/) {
    VL_VPI_UNIMP_();
    return 0;
}
PLI_INT32 vpi_chk_error(p_vpi_error_info error_info_p) {
    // executing vpi_chk_error does not reset error
    // error_info_p can be nullptr, so only return level in that case
    VerilatedVpiImp::assertOneCheck();
    const p_vpi_error_info imp_info_p = VerilatedVpiImp::error_info()->getError();
    if (error_info_p && imp_info_p) *error_info_p = *imp_info_p;
    if (!imp_info_p) return 0;  // no error occurred
    return imp_info_p->level;  // return error severity level
}

#ifndef VL_NO_LEGACY
PLI_INT32 vpi_free_object(vpiHandle object) {
    // vpi_free_object is IEEE deprecated, use vpi_release_handle
    return vpi_release_handle(object);
}
#endif

PLI_INT32 vpi_release_handle(vpiHandle object) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_release_handle %p\n", object););
    VerilatedVpiImp::assertOneCheck();
    VerilatedVpio* const vop = VerilatedVpio::castp(object);
    VL_VPI_ERROR_RESET_();
    if (VL_UNLIKELY(!vop)) return 0;
    VL_DO_DANGLING(delete vop, vop);
    return 1;
}

PLI_INT32 vpi_get_vlog_info(p_vpi_vlog_info vlog_info_p) {
    // This is VL_MT_SAFE, but not marked as can't indicate it in the standardized header file
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    const auto argc_argv = Verilated::threadContextp()->impp()->argc_argv();
    vlog_info_p->argc = argc_argv.first;
    vlog_info_p->argv = argc_argv.second;
    vlog_info_p->product = const_cast<PLI_BYTE8*>(Verilated::productName());
    vlog_info_p->version = const_cast<PLI_BYTE8*>(Verilated::productVersion());
    return 1;
}

// routines added with 1364-2001

PLI_INT32 vpi_get_data(PLI_INT32 /*id*/, PLI_BYTE8* /*dataLoc*/, PLI_INT32 /*numOfBytes*/) {
    VL_VPI_UNIMP_();
    return 0;
}
PLI_INT32 vpi_put_data(PLI_INT32 /*id*/, PLI_BYTE8* /*dataLoc*/, PLI_INT32 /*numOfBytes*/) {
    VL_VPI_UNIMP_();
    return 0;
}
void* vpi_get_userdata(vpiHandle /*obj*/) {
    VL_VPI_UNIMP_();
    return nullptr;
}
PLI_INT32 vpi_put_userdata(vpiHandle /*obj*/, void* /*userdata*/) {
    VL_VPI_UNIMP_();
    return 0;
}

PLI_INT32 vpi_control(PLI_INT32 operation, ...) {
    VL_DEBUG_IF_PLI(VL_DBG_MSGF("- vpi: vpi_control %d\n", operation););
    VerilatedVpiImp::assertOneCheck();
    VL_VPI_ERROR_RESET_();
    switch (operation) {
    case vpiFinish: {
        VL_FINISH_MT("", 0, "*VPI*");
        return 1;
    }
    case vpiStop: {
        VL_STOP_MT("", 0, "*VPI*");
        return 1;  // LCOV_EXCL_LINE
    }
    default: {
        VL_VPI_WARNING_(__FILE__, __LINE__, "%s: Unsupported type %s, ignoring", __func__,
                        VerilatedVpiError::strFromVpiProp(operation));
        return 0;
    }
    }
}

vpiHandle vpi_handle_by_multi_index(vpiHandle /*obj*/, PLI_INT32 /*num_index*/,
                                    PLI_INT32* /*index_array*/) {
    VL_VPI_UNIMP_();
    return nullptr;
}
