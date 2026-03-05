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
/// \brief Verilated run-time profiling implementation code
///
//=============================================================================

#include "verilatedos.h"

#include "verilated_profiler.h"

#include "verilated_threads.h"

#include <fstream>
#include <string>

//=============================================================================
// Globals

// Internal note: Globals may multi-construct, see verilated.cpp top.

thread_local VlExecutionProfiler::ExecutionTrace VlExecutionProfiler::t_trace;

constexpr const char* const VlExecutionRecord::s_ascii[];

//=============================================================================
// VlExecutionProfiler implementation

template <size_t N>
static size_t roundUptoMultipleOf(size_t value) {
    static_assert((N & (N - 1)) == 0, "'N' must be a power of 2");
    size_t mask = N - 1;
    return (value + mask) & ~mask;
}

VlExecutionProfiler::VlExecutionProfiler(VerilatedContext& context)
    : m_context{context} {
    // Setup profiling on main thread
    setupThread(0);
}

void VlExecutionProfiler::configure() {

    if (VL_UNLIKELY(m_enabled)) {
        --m_windowCount;
        if (VL_UNLIKELY(m_windowCount == m_context.profExecWindow())) {
            VL_DEBUG_IF(VL_DBG_MSGF("+ profile start collection\n"););
            clear();  // Clear the profile after the cache warm-up cycles.
            m_tickBegin = VL_CPU_TICK();
        } else if (VL_UNLIKELY(m_windowCount == 0)) {
            const uint64_t tickEnd = VL_CPU_TICK();
            VL_DEBUG_IF(VL_DBG_MSGF("+ profile end\n"););
            const std::string& fileName = m_context.profExecFilename();
            dump(fileName.c_str(), tickEnd);
            m_enabled = false;
        }
        return;
    }

    const uint64_t startReq = m_context.profExecStart() + 1;  // + 1, so we can start at time 0

    if (VL_UNLIKELY(m_lastStartReq < startReq && VL_TIME_Q() >= m_context.profExecStart())) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ profile start warmup\n"););
        VL_DEBUG_IF(assert(m_windowCount == 0););
        m_enabled = true;
        m_windowCount = m_context.profExecWindow() * 2;
        m_lastStartReq = startReq;
    }
}

VerilatedVirtualBase* VlExecutionProfiler::construct(VerilatedContext& context) {
    VlExecutionProfiler* const selfp = new VlExecutionProfiler{context};
    if (VlThreadPool* const threadPoolp = static_cast<VlThreadPool*>(context.threadPoolp())) {
        for (int i = 0; i < threadPoolp->numThreads(); ++i) {
            // Data to pass to worker thread initialization
            struct Data final {
                VlExecutionProfiler* const selfp;
                const uint32_t threadId;
            } data{selfp, static_cast<uint32_t>(i + 1)};

            // Initialize worker thread
            threadPoolp->workerp(i)->addTask(
                [](void* userp, bool) {
                    Data* const datap = static_cast<Data*>(userp);
                    datap->selfp->setupThread(datap->threadId);
                },
                &data);

            // Wait until initialization is complete
            threadPoolp->workerp(i)->wait();
        }
    }
    return selfp;
}

void VlExecutionProfiler::setupThread(uint32_t threadId) {
    // Reserve some space in the thread-local profiling buffer, in order to try to avoid malloc
    // while profiling.
    t_trace.reserve(RESERVED_TRACE_CAPACITY);
    // Register thread-local buffer in list of all buffers
    bool exists;
    {
        const VerilatedLockGuard lock{m_mutex};
        exists = !m_traceps.emplace(threadId, &t_trace).second;
    }
    if (VL_UNLIKELY(exists)) {
        VL_FATAL_MT(__FILE__, __LINE__, "", "multiple initialization of profiler on some thread");
    }
}

void VlExecutionProfiler::clear() VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    for (const auto& pair : m_traceps) {
        ExecutionTrace* const tracep = pair.second;
        const size_t reserve = roundUptoMultipleOf<RESERVED_TRACE_CAPACITY>(tracep->size());
        tracep->clear();
        tracep->reserve(reserve);
    }
}

void VlExecutionProfiler::dump(const char* filenamep, uint64_t tickEnd)
    VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    VL_DEBUG_IF(VL_DBG_MSGF("+prof+exec writing to '%s'\n", filenamep););

    FILE* const fp = std::fopen(filenamep, "w");
    if (VL_UNLIKELY(!fp)) VL_FATAL_MT(filenamep, 0, "", "+prof+exec+file file not writable");

    // TODO Perhaps merge with verilated_coverage output format, so can
    // have a common merging and reporting tool, etc.
    fprintf(fp, "VLPROFVERSION 2.2 # Verilator execution profile version 2.2\n");
    fprintf(fp, "VLPROF arg +verilator+prof+exec+start+%" PRIu64 "\n",
            Verilated::threadContextp()->profExecStart());
    fprintf(fp, "VLPROF arg +verilator+prof+exec+window+%u\n",
            Verilated::threadContextp()->profExecWindow());
    std::string numa = "no threads";
    if (const VlThreadPool* const threadPoolp
        = static_cast<VlThreadPool*>(Verilated::threadContextp()->threadPoolp())) {
        numa = threadPoolp->numaStatus();
    }
    fprintf(fp, "VLPROF info numa %s\n", numa.c_str());
    // Note that VerilatedContext will by default create as many threads as there are hardware
    // processors, but not all of them might be utilized. Report the actual number that has trace
    // entries to avoid over-counting.
    unsigned threads = 0;
    for (const auto& pair : m_traceps) {
        if (!pair.second->empty()) ++threads;
    }
    fprintf(fp, "VLPROF stat threads %u\n", threads);
    fprintf(fp, "VLPROF stat yields %" PRIu64 "\n", VlMTaskVertex::yields());

    // Copy /proc/cpuinfo into this output so verilator_gantt can be run on
    // a different machine
    {
        const std::unique_ptr<std::ifstream> ifp{new std::ifstream{"/proc/cpuinfo"}};
        if (!ifp->fail()) {
            std::string line;
            while (std::getline(*ifp, line)) { fprintf(fp, "VLPROFPROC %s\n", line.c_str()); }
        }
    }

    for (const auto& pair : m_traceps) {
        const uint32_t threadId = pair.first;
        ExecutionTrace* const tracep = pair.second;
        if (tracep->empty()) continue;
        fprintf(fp, "VLPROFTHREAD %" PRIu32 "\n", threadId);

        for (const VlExecutionRecord& er : *tracep) {
            const char* const name = VlExecutionRecord::s_ascii[static_cast<uint8_t>(er.m_type)];
            const uint64_t time = er.m_tick - m_tickBegin;
            fprintf(fp, "VLPROFEXEC %s %" PRIu64, name, time);

            switch (er.m_type) {
            case VlExecutionRecord::Type::SECTION_POP:
            case VlExecutionRecord::Type::EXEC_GRAPH_BEGIN:
            case VlExecutionRecord::Type::EXEC_GRAPH_END:
                // No payload
                fprintf(fp, "\n");
                break;
            case VlExecutionRecord::Type::MTASK_BEGIN: {
                const auto& payload = er.m_payload.mtaskBegin;
                if (payload.m_hierBlock[0] != '\0') {
                    fprintf(fp, " id %u predictStart %u cpu %u hierBlock %s\n", payload.m_id,
                            payload.m_predictStart, payload.m_cpu, payload.m_hierBlock);
                } else {
                    fprintf(fp, " id %u predictStart %u cpu %u\n", payload.m_id,
                            payload.m_predictStart, payload.m_cpu);
                }
                break;
            }
            case VlExecutionRecord::Type::MTASK_END: {
                const auto& payload = er.m_payload.mtaskEnd;
                fprintf(fp, " predictCost %u\n", payload.m_predictCost);
                break;
            }
            case VlExecutionRecord::Type::THREAD_SCHEDULE_WAIT_BEGIN:
            case VlExecutionRecord::Type::THREAD_SCHEDULE_WAIT_END: {
                const auto& payload = er.m_payload.threadScheduleWait;
                fprintf(fp, " cpu %u\n", payload.m_cpu);
                break;
            }
            case VlExecutionRecord::Type::SECTION_PUSH: {
                const auto& payload = er.m_payload.sectionPush;
                fprintf(fp, " %s\n", payload.m_name);
                break;
            }
            default: abort();  // LCOV_EXCL_LINE
            }
        }
    }
    fprintf(fp, "VLPROF stat ticks %" PRIu64 "\n", tickEnd - m_tickBegin);

    std::fclose(fp);
}
