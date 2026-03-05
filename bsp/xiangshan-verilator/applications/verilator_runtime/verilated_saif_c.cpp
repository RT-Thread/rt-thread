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
/// \brief Verilated C++ tracing in SAIF format implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use --trace-saif.
///
/// Use "verilator --trace-saif" to add this to the Makefile for the linker.
///
//=============================================================================

// clang-format off

#include "verilatedos.h"
#include "verilated.h"
#include "verilated_saif_c.h"

#include <algorithm>
#include <cerrno>
#include <fcntl.h>
#include <string>

#if defined(_WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
# include <io.h>
#else
# include <unistd.h>
#endif

#ifndef O_LARGEFILE  // WIN32 headers omit this
# define O_LARGEFILE 0
#endif
#ifndef O_NONBLOCK  // WIN32 headers omit this
# define O_NONBLOCK 0
#endif
#ifndef O_CLOEXEC  // WIN32 headers omit this
# define O_CLOEXEC 0
#endif

// clang-format on

//=============================================================================
// Specialization of the generics for this trace format

#define VL_SUB_T VerilatedSaif
#define VL_BUF_T VerilatedSaifBuffer
#include "verilated_trace_imp.h"
#undef VL_SUB_T
#undef VL_BUF_T

//=============================================================================
// VerilatedSaifActivityBit

class VerilatedSaifActivityBit final {
    // MEMBERS
    bool m_lastVal = false;  // Last emitted activity bit value
    uint64_t m_highTime = 0;  // Total time when bit was high
    size_t m_transitions = 0;  // Total number of bit transitions

public:
    // METHODS
    VL_ATTR_ALWINLINE
    void aggregateVal(uint64_t dt, bool newVal) {
        m_transitions += newVal != m_lastVal ? 1 : 0;
        m_highTime += m_lastVal ? dt : 0;
        m_lastVal = newVal;
    }

    // ACCESSORS
    VL_ATTR_ALWINLINE bool bitValue() const { return m_lastVal; }
    VL_ATTR_ALWINLINE uint64_t highTime() const { return m_highTime; }
    VL_ATTR_ALWINLINE uint64_t toggleCount() const { return m_transitions; }
};

//=============================================================================
// VerilatedSaifActivityVar

class VerilatedSaifActivityVar final {
    // MEMBERS
    uint64_t m_lastTime = 0;  // Last time when variable value was updated
    VerilatedSaifActivityBit* m_bits;  // Pointer to variable bits objects
    uint32_t m_width;  // Width of variable (in bits)

public:
    // CONSTRUCTORS
    VerilatedSaifActivityVar(uint32_t width, VerilatedSaifActivityBit* bits)
        : m_bits{bits}
        , m_width{width} {}

    VerilatedSaifActivityVar(VerilatedSaifActivityVar&&) = default;
    VerilatedSaifActivityVar& operator=(VerilatedSaifActivityVar&&) = default;

    // METHODS
    VL_ATTR_ALWINLINE void emitBit(uint64_t time, CData newval);

    template <typename DataType>
    VL_ATTR_ALWINLINE void emitData(uint64_t time, DataType newval, uint32_t bits) {
        static_assert(std::is_integral<DataType>::value,
                      "The emitted value must be of integral type");

        const uint64_t dt = time - m_lastTime;
        for (size_t i = 0; i < std::min(m_width, bits); ++i) {
            m_bits[i].aggregateVal(dt, (newval >> i) & 1);
        }
        updateLastTime(time);
    }

    VL_ATTR_ALWINLINE void emitWData(uint64_t time, const WData* newvalp, uint32_t bits);
    VL_ATTR_ALWINLINE void updateLastTime(uint64_t val) { m_lastTime = val; }

    // ACCESSORS
    VL_ATTR_ALWINLINE uint32_t width() const { return m_width; }
    VL_ATTR_ALWINLINE VerilatedSaifActivityBit& bit(std::size_t index);
    VL_ATTR_ALWINLINE uint64_t lastUpdateTime() const { return m_lastTime; }

private:
    // CONSTRUCTORS
    VL_UNCOPYABLE(VerilatedSaifActivityVar);
};

//=============================================================================
// VerilatedSaifActivityScope

class VerilatedSaifActivityScope final {
    // MEMBERS
    // Absolute path to the scope
    std::string m_scopePath;
    // Name of the activity scope
    std::string m_scopeName;
    // Array indices of child scopes
    std::vector<std::unique_ptr<VerilatedSaifActivityScope>> m_childScopes{};
    // Children signals codes mapped to their names in the current scope
    std::vector<std::pair<uint32_t, std::string>> m_childActivities{};
    // Parent scope pointer
    VerilatedSaifActivityScope* m_parentScope = nullptr;

public:
    // CONSTRUCTORS
    VerilatedSaifActivityScope(std::string scopePath, std::string name,
                               VerilatedSaifActivityScope* parentScope = nullptr)
        : m_scopePath{std::move(scopePath)}
        , m_scopeName{std::move(name)}
        , m_parentScope{parentScope} {}

    VerilatedSaifActivityScope(VerilatedSaifActivityScope&&) = default;
    VerilatedSaifActivityScope& operator=(VerilatedSaifActivityScope&&) = default;

    // METHODS
    VL_ATTR_ALWINLINE void addChildScope(std::unique_ptr<VerilatedSaifActivityScope> childScope) {
        m_childScopes.emplace_back(std::move(childScope));
    }
    VL_ATTR_ALWINLINE void addActivityVar(uint32_t code, std::string name) {
        m_childActivities.emplace_back(code, std::move(name));
    }
    VL_ATTR_ALWINLINE bool hasParent() const { return m_parentScope; }

    // ACCESSORS
    VL_ATTR_ALWINLINE const std::string& path() const { return m_scopePath; }
    VL_ATTR_ALWINLINE const std::string& name() const { return m_scopeName; }
    VL_ATTR_ALWINLINE const std::vector<std::unique_ptr<VerilatedSaifActivityScope>>&
    childScopes() const {
        return m_childScopes;
    }
    VL_ATTR_ALWINLINE
    const std::vector<std::pair<uint32_t, std::string>>& childActivities() const {
        return m_childActivities;
    }
    VL_ATTR_ALWINLINE VerilatedSaifActivityScope* parentScope() const { return m_parentScope; }

private:
    // CONSTRUCTORS
    VL_UNCOPYABLE(VerilatedSaifActivityScope);
};

//=============================================================================
// VerilatedSaifActivityAccumulator

class VerilatedSaifActivityAccumulator final {
    // Give access to the private activities
    friend class VerilatedSaifBuffer;
    friend class VerilatedSaif;

    // MEMBERS
    // Map of scopes paths to codes of activities inside
    std::unordered_map<std::string, std::vector<std::pair<uint32_t, std::string>>>
        m_scopeToActivities;
    // Map of variables codes mapped to their activity objects
    std::unordered_map<uint32_t, VerilatedSaifActivityVar> m_activity;
    // Memory pool for signals bits objects
    std::vector<std::vector<VerilatedSaifActivityBit>> m_activityArena;

public:
    // METHODS
    void declare(uint32_t code, const std::string& absoluteScopePath, std::string variableName,
                 int bits, bool array, int arraynum);

    // CONSTRUCTORS
    VerilatedSaifActivityAccumulator() = default;

    VerilatedSaifActivityAccumulator(VerilatedSaifActivityAccumulator&&) = default;
    VerilatedSaifActivityAccumulator& operator=(VerilatedSaifActivityAccumulator&&) = default;

private:
    VL_UNCOPYABLE(VerilatedSaifActivityAccumulator);
};

//=============================================================================
//=============================================================================
//=============================================================================
// VerilatedSaifActivityVar implementation

VL_ATTR_ALWINLINE
void VerilatedSaifActivityVar::emitBit(const uint64_t time, const CData newval) {
    assert(m_lastTime <= time);
    m_bits[0].aggregateVal(time - m_lastTime, newval);
    updateLastTime(time);
}

VL_ATTR_ALWINLINE
void VerilatedSaifActivityVar::emitWData(const uint64_t time, const WData* newvalp,
                                         const uint32_t bits) {
    assert(m_lastTime <= time);
    const uint64_t dt = time - m_lastTime;
    for (std::size_t i = 0; i < std::min(m_width, bits); ++i) {
        const size_t wordIndex = i / VL_EDATASIZE;
        m_bits[i].aggregateVal(dt, (newvalp[wordIndex] >> VL_BITBIT_E(i)) & 1);
    }

    updateLastTime(time);
}

VerilatedSaifActivityBit& VerilatedSaifActivityVar::bit(const std::size_t index) {
    assert(index < m_width);
    return m_bits[index];
}

//=============================================================================
//=============================================================================
//=============================================================================
// VerilatedSaifActivityAccumulator implementation

void VerilatedSaifActivityAccumulator::declare(uint32_t code, const std::string& absoluteScopePath,
                                               std::string variableName, int bits, bool array,
                                               int arraynum) {
    const size_t block_size = 1024;
    if (m_activityArena.empty()
        || m_activityArena.back().size() + bits > m_activityArena.back().capacity()) {
        m_activityArena.emplace_back();
        m_activityArena.back().reserve(block_size);
    }
    const size_t bitsIdx = m_activityArena.back().size();
    m_activityArena.back().resize(m_activityArena.back().size() + bits);

    if (array) {
        variableName += '[';
        variableName += std::to_string(arraynum);
        variableName += ']';
    }
    m_scopeToActivities[absoluteScopePath].emplace_back(code, variableName);
    m_activity.emplace(code, VerilatedSaifActivityVar{static_cast<uint32_t>(bits),
                                                      m_activityArena.back().data() + bitsIdx});
}

//=============================================================================
//=============================================================================
//=============================================================================
// VerilatedSaif implementation

VerilatedSaif::VerilatedSaif(void* filep) {
    m_activityAccumulators.emplace_back(std::make_unique<VerilatedSaifActivityAccumulator>());
}

void VerilatedSaif::open(const char* filename) VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    if (isOpen()) return;

    m_filename = filename;  // "" is ok, as someone may overload open
    m_filep = ::open(m_filename.c_str(),
                     O_CREAT | O_WRONLY | O_TRUNC | O_LARGEFILE | O_NONBLOCK | O_CLOEXEC, 0666);
    m_isOpen = true;

    initializeSaifFileContents();

    Super::traceInit();
}

void VerilatedSaif::initializeSaifFileContents() {
    printStr("// Generated by verilated_saif\n");
    printStr("(SAIFILE\n");
    printStr("(SAIFVERSION \"2.0\")\n");
    printStr("(DIRECTION \"backward\")\n");
    printStr("(PROGRAM_NAME \"Verilator\")\n");
    printStr("(DIVIDER / )\n");
    printStr("(TIMESCALE ");
    printStr(timeResStr());
    printStr(")\n");
}

void VerilatedSaif::emitTimeChange(uint64_t timeui) { m_time = timeui; }

VerilatedSaif::~VerilatedSaif() { close(); }

void VerilatedSaif::close() VL_MT_SAFE_EXCLUDES(m_mutex) {
    // This function is on the flush() call path
    const VerilatedLockGuard lock{m_mutex};
    if (!isOpen()) return;

    finalizeSaifFileContents();
    clearCurrentlyCollectedData();

    writeBuffered(true);
    ::close(m_filep);
    m_isOpen = false;

    Super::closeBase();
}

void VerilatedSaif::finalizeSaifFileContents() {
    printStr("(DURATION ");
    printStr(std::to_string(currentTime()));
    printStr(")\n");

    incrementIndent();
    for (const auto& topScope : m_scopes) recursivelyPrintScopes(*topScope);
    decrementIndent();

    printStr(")\n");  // SAIFILE
}

void VerilatedSaif::recursivelyPrintScopes(const VerilatedSaifActivityScope& scope) {
    openInstanceScope(scope.name());
    printScopeActivities(scope);
    for (const auto& childScope : scope.childScopes()) recursivelyPrintScopes(*childScope);
    closeInstanceScope();
}

void VerilatedSaif::openInstanceScope(const std::string& instanceName) {
    printIndent();
    printStr("(INSTANCE ");
    printStr(instanceName);
    printStr("\n");
    incrementIndent();
}

void VerilatedSaif::closeInstanceScope() {
    decrementIndent();
    printIndent();
    printStr(")\n");  // INSTANCE
}

void VerilatedSaif::printScopeActivities(const VerilatedSaifActivityScope& scope) {
    bool anyNetWritten = false;

    for (auto& accumulator : m_activityAccumulators) {
        anyNetWritten |= printScopeActivitiesFromAccumulatorIfPresent(scope.path(), *accumulator,
                                                                      anyNetWritten);
    }

    if (anyNetWritten) closeNetScope();
}

bool VerilatedSaif::printScopeActivitiesFromAccumulatorIfPresent(
    const std::string& absoluteScopePath, VerilatedSaifActivityAccumulator& accumulator,
    bool anyNetWritten) {
    if (accumulator.m_scopeToActivities.count(absoluteScopePath) == 0) return false;

    for (const auto& childSignal : accumulator.m_scopeToActivities.at(absoluteScopePath)) {
        VerilatedSaifActivityVar& activityVariable = accumulator.m_activity.at(childSignal.first);
        anyNetWritten
            = printActivityStats(activityVariable, childSignal.second.c_str(), anyNetWritten);
    }

    return anyNetWritten;
}

void VerilatedSaif::openNetScope() {
    printIndent();
    printStr("(NET\n");
    incrementIndent();
}

void VerilatedSaif::closeNetScope() {
    decrementIndent();
    printIndent();
    printStr(")\n");  // NET
}

bool VerilatedSaif::printActivityStats(VerilatedSaifActivityVar& activity,
                                       const std::string& activityName, bool anyNetWritten) {
    for (size_t i = 0; i < activity.width(); ++i) {
        VerilatedSaifActivityBit& bit = activity.bit(i);

        bit.aggregateVal(currentTime() - activity.lastUpdateTime(), bit.bitValue());

        if (!anyNetWritten) {
            openNetScope();
            anyNetWritten = true;
        }

        printIndent();
        printStr("(");
        printStr(activityName);
        if (activity.width() > 1) {
            printStr("\\[");
            printStr(std::to_string(i));
            printStr("\\]");
        }

        // We only have two-value logic so TZ, TX and TB will always be 0
        printStr(" (T0 ");
        printStr(std::to_string(currentTime() - bit.highTime()));
        printStr(") (T1 ");
        printStr(std::to_string(bit.highTime()));
        printStr(") (TZ 0) (TX 0) (TB 0) (TC ");
        printStr(std::to_string(bit.toggleCount()));
        printStr("))\n");
    }

    activity.updateLastTime(currentTime());

    return anyNetWritten;
}

void VerilatedSaif::clearCurrentlyCollectedData() {
    m_currentScope = nullptr;
    m_scopes.clear();
    m_activityAccumulators.clear();
}

void VerilatedSaif::printStr(const char* str) {
    m_buffer.append(str);
    writeBuffered(false);
}

void VerilatedSaif::printStr(const std::string& str) {
    m_buffer.append(str);
    writeBuffered(false);
}

void VerilatedSaif::writeBuffered(bool force) {
    if (VL_UNLIKELY(m_buffer.size() >= WRITE_BUFFER_SIZE || force)) {
        if (VL_UNLIKELY(!m_buffer.empty())) {
            ::write(m_filep, m_buffer.data(), m_buffer.size());
            m_buffer = "";
            m_buffer.reserve(WRITE_BUFFER_SIZE * 2);
        }
    }
}

//=============================================================================
// Definitions

void VerilatedSaif::flush() VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    Super::flushBase();
}

void VerilatedSaif::incrementIndent() { m_indent += 1; }

void VerilatedSaif::decrementIndent() { m_indent -= 1; }

void VerilatedSaif::printIndent() {
    printStr(std::string(m_indent, ' '));  // Must use () constructor
}

void VerilatedSaif::pushPrefix(const char* namep, VerilatedTracePrefixType type) {
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

    if (type != VerilatedTracePrefixType::ARRAY_UNPACKED
        && type != VerilatedTracePrefixType::ARRAY_PACKED) {

        std::string scopePath = prevPrefix + name;
        std::string scopeName = lastWord(scopePath);

        auto newScope = std::make_unique<VerilatedSaifActivityScope>(
            std::move(scopePath), std::move(scopeName), m_currentScope);
        VerilatedSaifActivityScope* newScopePtr = newScope.get();

        if (m_currentScope) {
            m_currentScope->addChildScope(std::move(newScope));
        } else {
            m_scopes.emplace_back(std::move(newScope));
        }

        m_currentScope = newScopePtr;
    }

    const std::string newPrefix = prevPrefix + name;
    bool properScope = (type != VerilatedTracePrefixType::ARRAY_UNPACKED
                        && type != VerilatedTracePrefixType::ARRAY_PACKED
                        && type != VerilatedTracePrefixType::ROOTIO_WRAPPER);
    m_prefixStack.emplace_back(newPrefix + (properScope ? " " : ""), type);
}

void VerilatedSaif::popPrefix() {
    if (m_prefixStack.back().second != VerilatedTracePrefixType::ARRAY_UNPACKED
        && m_prefixStack.back().second != VerilatedTracePrefixType::ARRAY_PACKED
        && m_prefixStack.back().second != VerilatedTracePrefixType::ROOTIO_WRAPPER
        && m_currentScope) {
        m_currentScope = m_currentScope->parentScope();
    }
    m_prefixStack.pop_back();
    assert(!m_prefixStack.empty());  // Always one left, the constructor's initial one
}

void VerilatedSaif::declare(const uint32_t code, uint32_t fidx, const char* name,
                            const char* wirep, const bool array, const int arraynum,
                            const bool bussed, const int msb, const int lsb) {
    assert(m_activityAccumulators.size() > fidx);
    VerilatedSaifActivityAccumulator& accumulator = *m_activityAccumulators.at(fidx);

    const int bits = ((msb > lsb) ? (msb - lsb) : (lsb - msb)) + 1;

    const std::string hierarchicalName = m_prefixStack.back().first + name;

    if (!Super::declCode(code, hierarchicalName, bits)) return;

    std::string variableName = lastWord(hierarchicalName);
    m_currentScope->addActivityVar(code, variableName);

    accumulator.declare(code, m_currentScope->path(), std::move(variableName), bits, array,
                        arraynum);
}

void VerilatedSaif::declEvent(const uint32_t code, const uint32_t fidx, const char* name,
                              const int dtypenum, const VerilatedTraceSigDirection,
                              const VerilatedTraceSigKind, const VerilatedTraceSigType,
                              const bool array, const int arraynum) {
    declare(code, fidx, name, "event", array, arraynum, false, 0, 0);
}

void VerilatedSaif::declBit(const uint32_t code, const uint32_t fidx, const char* name,
                            const int dtypenum, const VerilatedTraceSigDirection,
                            const VerilatedTraceSigKind, const VerilatedTraceSigType,
                            const bool array, const int arraynum) {
    declare(code, fidx, name, "wire", array, arraynum, false, 0, 0);
}
void VerilatedSaif::declBus(const uint32_t code, const uint32_t fidx, const char* name,
                            const int dtypenum, const VerilatedTraceSigDirection,
                            const VerilatedTraceSigKind, const VerilatedTraceSigType,
                            const bool array, const int arraynum, const int msb, const int lsb) {
    declare(code, fidx, name, "wire", array, arraynum, true, msb, lsb);
}
void VerilatedSaif::declQuad(const uint32_t code, const uint32_t fidx, const char* name,
                             const int dtypenum, const VerilatedTraceSigDirection,
                             const VerilatedTraceSigKind, const VerilatedTraceSigType,
                             const bool array, const int arraynum, const int msb, const int lsb) {
    declare(code, fidx, name, "wire", array, arraynum, true, msb, lsb);
}
void VerilatedSaif::declArray(const uint32_t code, const uint32_t fidx, const char* name,
                              const int dtypenum, const VerilatedTraceSigDirection,
                              const VerilatedTraceSigKind, const VerilatedTraceSigType,
                              const bool array, const int arraynum, const int msb, const int lsb) {
    declare(code, fidx, name, "wire", array, arraynum, true, msb, lsb);
}
void VerilatedSaif::declDouble(const uint32_t code, const uint32_t fidx, const char* name,
                               const int dtypenum, const VerilatedTraceSigDirection,
                               const VerilatedTraceSigKind, const VerilatedTraceSigType,
                               const bool array, const int arraynum) {
    declare(code, fidx, name, "real", array, arraynum, false, 63, 0);
}

//=============================================================================
// Get/commit trace buffer

VerilatedSaif::Buffer* VerilatedSaif::getTraceBuffer(uint32_t fidx) { return new Buffer{*this}; }

void VerilatedSaif::commitTraceBuffer(VerilatedSaif::Buffer* bufp) { delete bufp; }

//=============================================================================
//=============================================================================
//=============================================================================
// VerilatedSaifBuffer implementation

//=============================================================================
// emit* trace routines

// Note: emit* are only ever called from one place (full* in
// verilated_trace_imp.h, which is included in this file at the top),
// so always inline them.

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitEvent(const uint32_t code) {
    // NOP
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitBit(const uint32_t code, const CData newval) {
    assert(m_owner.m_activityAccumulators.at(m_fidx)->m_activity.count(code)
           && "Activity must be declared earlier");
    VerilatedSaifActivityVar& activity
        = m_owner.m_activityAccumulators.at(m_fidx)->m_activity.at(code);
    activity.emitBit(m_owner.currentTime(), newval);
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitCData(const uint32_t code, const CData newval, const int bits) {
    assert(m_owner.m_activityAccumulators.at(m_fidx)->m_activity.count(code)
           && "Activity must be declared earlier");
    VerilatedSaifActivityVar& activity
        = m_owner.m_activityAccumulators.at(m_fidx)->m_activity.at(code);
    activity.emitData<CData>(m_owner.currentTime(), newval, bits);
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitSData(const uint32_t code, const SData newval, const int bits) {
    assert(m_owner.m_activityAccumulators.at(m_fidx)->m_activity.count(code)
           && "Activity must be declared earlier");
    VerilatedSaifActivityVar& activity
        = m_owner.m_activityAccumulators.at(m_fidx)->m_activity.at(code);
    activity.emitData<SData>(m_owner.currentTime(), newval, bits);
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitIData(const uint32_t code, const IData newval, const int bits) {
    assert(m_owner.m_activityAccumulators.at(m_fidx)->m_activity.count(code)
           && "Activity must be declared earlier");
    VerilatedSaifActivityVar& activity
        = m_owner.m_activityAccumulators.at(m_fidx)->m_activity.at(code);
    activity.emitData<IData>(m_owner.currentTime(), newval, bits);
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitQData(const uint32_t code, const QData newval, const int bits) {
    assert(m_owner.m_activityAccumulators.at(m_fidx)->m_activity.count(code)
           && "Activity must be declared earlier");
    VerilatedSaifActivityVar& activity
        = m_owner.m_activityAccumulators.at(m_fidx)->m_activity.at(code);
    activity.emitData<QData>(m_owner.currentTime(), newval, bits);
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitWData(const uint32_t code, const WData* newvalp, const int bits) {
    assert(m_owner.m_activityAccumulators.at(m_fidx)->m_activity.count(code)
           && "Activity must be declared earlier");
    VerilatedSaifActivityVar& activity
        = m_owner.m_activityAccumulators.at(m_fidx)->m_activity.at(code);
    activity.emitWData(m_owner.currentTime(), newvalp, bits);
}

VL_ATTR_ALWINLINE
void VerilatedSaifBuffer::emitDouble(const uint32_t code, const double newval) {
    // NOP
}
