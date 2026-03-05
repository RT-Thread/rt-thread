// -*- mode: C++; c-file-style: "cc-mode" -*-
//=============================================================================
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2012-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=============================================================================
///
/// \file
/// \brief Verilated run-time profiling header
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use by Verilated library routines.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_PROFILER_H_
#define VERILATOR_VERILATED_PROFILER_H_

#include "verilatedos.h"

#include "verilated.h"

#include <array>
#include <atomic>
#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

class VlExecutionProfiler;
class VlThreadPool;

//=============================================================================
// Macros to simplify generated code

#define VL_EXEC_TRACE_ADD_RECORD(vlSymsp) \
    if (VL_UNLIKELY((vlSymsp)->__Vm_executionProfilerp->enabled())) \
    (vlSymsp)->__Vm_executionProfilerp->addRecord()

//=============================================================================
// Return high-precision counter for profiling, or 0x0 if not available
VL_ATTR_ALWINLINE QData VL_CPU_TICK() {
    uint64_t val;
    VL_GET_CPU_TICK(val);
    return val;
}

//=============================================================================
// Private class used by VlExecutionProfiler

#define _VL_FOREACH_APPLY(macro, arg) macro(arg, #arg)

// clang-format off
#define FOREACH_VlExecutionRecord_TYPE(macro) \
    _VL_FOREACH_APPLY(macro, SECTION_PUSH) \
    _VL_FOREACH_APPLY(macro, SECTION_POP) \
    _VL_FOREACH_APPLY(macro, MTASK_BEGIN) \
    _VL_FOREACH_APPLY(macro, MTASK_END) \
    _VL_FOREACH_APPLY(macro, THREAD_SCHEDULE_WAIT_BEGIN) \
    _VL_FOREACH_APPLY(macro, THREAD_SCHEDULE_WAIT_END) \
    _VL_FOREACH_APPLY(macro, EXEC_GRAPH_BEGIN) \
    _VL_FOREACH_APPLY(macro, EXEC_GRAPH_END)
// clang-format on

class VlExecutionRecord final {
    friend class VlExecutionProfiler;

    // TYPES
    enum class Type : uint8_t {
#define VL_FOREACH_MACRO(id, name) id,
        FOREACH_VlExecutionRecord_TYPE(VL_FOREACH_MACRO)
#undef VL_FOREACH_MACRO
    };

    static constexpr const char* const s_ascii[] = {
#define VL_FOREACH_MACRO(id, name) name,
        FOREACH_VlExecutionRecord_TYPE(VL_FOREACH_MACRO)
#undef VL_FOREACH_MACRO
    };

    union Payload {
        struct {
            const char* m_name;  // Name of section being entered
        } sectionPush;
        struct {
            uint32_t m_id;  // MTask id
            uint32_t m_predictStart;  // Time scheduler predicted would start
            uint32_t m_cpu;  // Executing CPU id
            const char* m_hierBlock;  // Name of a hier block with this mtask
        } mtaskBegin;
        struct {
            uint32_t m_predictCost;  // How long scheduler predicted would take
        } mtaskEnd;
        struct {
            uint32_t m_cpu;  // Executing CPU id
        } threadScheduleWait;
    };

    // STATE
    // Layout below allows efficient packing.
    const uint64_t m_tick = VL_CPU_TICK();  // Tick at construction
    Payload m_payload;  // The record payload
    Type m_type;  // The record type
    static_assert(alignof(uint64_t) >= alignof(Payload), "Padding not allowed");
    static_assert(alignof(Payload) >= alignof(Type), "Padding not allowed");

public:
    // CONSTRUCTOR
    VlExecutionRecord() = default;

    // METHODS
    void sectionPush(const char* name) {
        m_payload.sectionPush.m_name = name;
        m_type = Type::SECTION_PUSH;
    }
    void sectionPop() { m_type = Type::SECTION_POP; }
    void mtaskBegin(uint32_t id, uint32_t predictStart, const char* hierBlock) {
        m_payload.mtaskBegin.m_id = id;
        m_payload.mtaskBegin.m_predictStart = predictStart;
        m_payload.mtaskBegin.m_cpu = VlOs::getcpu();
        m_payload.mtaskBegin.m_hierBlock = hierBlock;
        m_type = Type::MTASK_BEGIN;
    }
    void mtaskEnd(uint32_t predictCost) {
        m_payload.mtaskEnd.m_predictCost = predictCost;
        m_type = Type::MTASK_END;
    }
    void threadScheduleWaitBegin() {
        m_payload.threadScheduleWait.m_cpu = VlOs::getcpu();
        m_type = Type::THREAD_SCHEDULE_WAIT_BEGIN;
    }
    void threadScheduleWaitEnd() {
        m_payload.threadScheduleWait.m_cpu = VlOs::getcpu();
        m_type = Type::THREAD_SCHEDULE_WAIT_END;
    }
    void execGraphBegin() { m_type = Type::EXEC_GRAPH_BEGIN; }
    void execGraphEnd() { m_type = Type::EXEC_GRAPH_END; }
};

static_assert(std::is_trivially_destructible<VlExecutionRecord>::value,
              "VlExecutionRecord should be trivially destructible for fast buffer clearing");

//=============================================================================
// VlExecutionProfiler is for collecting profiling data about model execution

class VlExecutionProfiler final : public VerilatedVirtualBase {
    // CONSTANTS

    // In order to try to avoid dynamic memory allocations during the actual profiling phase,
    // trace buffers are pre-allocated to be able to hold [a multiple] of this many records.
    static constexpr size_t RESERVED_TRACE_CAPACITY = 4096;

    // TYPES

    // Execution traces are recorded into thread local vectors. We can append records of profiling
    // events to this vector with very low overhead, and then dump them out later. This prevents
    // the overhead of printf/malloc/IO from corrupting the profiling data. It's super cheap to
    // append a VlProfileRec struct on the end of a pre-allocated vector; this is the only cost we
    // pay in real-time during a profiling cycle. Internal note: Globals may multi-construct, see
    // verilated.cpp top.
    using ExecutionTrace = std::vector<VlExecutionRecord>;

    // STATE
    VerilatedContext& m_context;  // The context this profiler is under
    static thread_local ExecutionTrace t_trace;  // thread-local trace buffers
    mutable VerilatedMutex m_mutex;
    // Map from thread id to &t_trace of given thread
    std::map<uint32_t, ExecutionTrace*> m_traceps VL_GUARDED_BY(m_mutex);

    bool m_enabled = false;  // Is profiling currently enabled

    uint64_t m_tickBegin = 0;  // Sample time (rdtsc() on x86) at beginning of collection
    uint64_t m_lastStartReq = 0;  // Last requested profiling start (in simulation time)
    uint32_t m_windowCount = 0;  // Track our position in the cache warmup and profile window

public:
    // CONSTRUCTOR
    explicit VlExecutionProfiler(VerilatedContext& context);
    ~VlExecutionProfiler() override = default;

    // METHODS

    // Is profiling enabled
    bool enabled() const { return m_enabled; }
    // Append a trace record to the trace buffer of the current thread
    static VlExecutionRecord& addRecord() {
        t_trace.emplace_back();
        return t_trace.back();
    }
    // Configure profiler (called in beginning of 'eval')
    void configure();
    // Setup profiling on a particular thread;
    void setupThread(uint32_t threadId);
    // Clear all profiling data
    void clear() VL_MT_SAFE_EXCLUDES(m_mutex);
    // Write profiling data into file
    void dump(const char* filenamep, uint64_t tickEnd) VL_MT_SAFE_EXCLUDES(m_mutex);

    // Passed to VerilatedContext to create the VlExecutionProfiler profiler instance
    static VerilatedVirtualBase* construct(VerilatedContext& context);
};

//=============================================================================
// VlPgoProfiler is for collecting profiling data for PGO

template <std::size_t N_Entries>
class VlPgoProfiler final {
    // TYPES
    struct Record final {
        const std::string m_name;  // Hashed name of mtask/etc
        const size_t m_counterNumber = 0;  // Which counter has data
    };

    // Counters are stored packed, all together to reduce cache effects
    std::array<uint64_t, N_Entries> m_counters{};  // Time spent on this record
    std::vector<Record> m_records;  // Record information
    // An original cost of a profiled hier block. During Verilation with
    // collected profiling data, costs of hier blocks change thus hashes of
    // original mtasks does not match those from the previous,
    // instrumented, run. We shall not assume that a single top-level mtask
    // will correspond to the hier block as multiple hier block DPIs can be
    // contracted into a single mtask.  Therefore, the old cost, from
    // previous instrumented run, is used to stabilize profiled scheduling.
    const uint64_t m_currentHierBlockCost;

public:
    // METHODS
    explicit VlPgoProfiler(uint64_t currentHierBlockCost = 0)
        : m_currentHierBlockCost{currentHierBlockCost} {}
    ~VlPgoProfiler() = default;
    VL_UNMOVABLE(VlPgoProfiler);
    VL_UNCOPYABLE(VlPgoProfiler);
    void writeHeader(const std::string& filename) VL_MT_SAFE;
    void write(const char* modelp, const std::string& filename) VL_MT_SAFE;
    void addCounter(size_t counter, const std::string& name) {
        VL_DEBUG_IF(assert(counter < N_Entries););
        m_records.emplace_back(Record{name, counter});
    }
    void startCounter(size_t counter) {
        // -= so when we add end time in stopCounter, the net effect is adding the difference,
        // without needing to hold onto a temporary
        m_counters[counter] -= VL_CPU_TICK();
    }
    void stopCounter(size_t counter) { m_counters[counter] += VL_CPU_TICK(); }
};

template <std::size_t N_Entries>
void VlPgoProfiler<N_Entries>::writeHeader(const std::string& filename) VL_MT_SAFE {
    static VerilatedMutex s_mutex;
    const VerilatedLockGuard lock{s_mutex};

    // On the first call we create the file.  On later calls we append.
    // So when we have multiple models in an executable, possibly even
    // running on different threads, each will have a different symtab so
    // each will collect is own data correctly.  However when each is
    // destroyed we need to get all the data, not keep overwriting and only
    // get the last model's data.

    FILE* const fp = std::fopen(filename.c_str(), "w");
    if (VL_UNLIKELY(!fp)) {
        VL_FATAL_MT(filename.c_str(), 0, "", "+prof+vlt+file file not writable");
    }

    VL_DEBUG_IF(VL_DBG_MSGF("+prof+vlt+file initializing '%s'\n", filename.c_str()););

    // TODO Perhaps merge with verilated_coverage output format, so can
    // have a common merging and reporting tool, etc.
    fprintf(fp, "// Verilated model profile-guided optimization data dump file\n");
    fprintf(fp, "`verilator_config\n");

    std::fclose(fp);
}

template <std::size_t N_Entries>
void VlPgoProfiler<N_Entries>::write(const char* modelp, const std::string& filename) VL_MT_SAFE {
    static VerilatedMutex s_mutex;
    const VerilatedLockGuard lock{s_mutex};

    FILE* const fp = std::fopen(filename.c_str(), "a");
    if (VL_UNLIKELY(!fp)) {
        VL_FATAL_MT(filename.c_str(), 0, "", "+prof+vlt+file file not writable");
    }

    VL_DEBUG_IF(VL_DBG_MSGF("+prof+vlt+file writing to '%s'\n", filename.c_str()););

    if (m_currentHierBlockCost) {
        fprintf(fp, "profile_data -hier-dpi \"%s\" -cost 64'd%" PRIu64 "\n", modelp,
                m_currentHierBlockCost);
    }

    for (const Record& rec : m_records) {
        fprintf(fp, "profile_data -model \"%s\" -mtask \"%s\" -cost 64'd%" PRIu64 "\n", modelp,
                rec.m_name.c_str(), m_counters[rec.m_counterNumber]);
    }

    std::fclose(fp);
}

#endif
