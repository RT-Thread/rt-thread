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
//
// Verilated tracing implementation code template common to all formats.
// This file is included by the format-specific implementations and
// should not be used otherwise.
//
//=============================================================================

// clang-format off

#ifndef VL_CPPCHECK
#if !defined(VL_SUB_T) || !defined(VL_BUF_T)
# error "This file should be included in trace format implementations"
#endif

#include "verilated_intrinsics.h"
#include "verilated_trace.h"
#include "verilated_threads.h"
#include <list>

#if 0
# include <iostream>
# define VL_TRACE_OFFLOAD_DEBUG(msg) std::cout << "TRACE OFFLOAD THREAD: " << msg << "\n"
#else
# define VL_TRACE_OFFLOAD_DEBUG(msg)
#endif

// clang-format on

//=============================================================================
// Static utility functions

static double timescaleToDouble(const char* unitp) VL_PURE {
    char* endp = nullptr;
    double value = std::strtod(unitp, &endp);
    // On error so we allow just "ns" to return 1e-9.
    if (value == 0.0 && endp == unitp) value = 1;
    unitp = endp;
    for (; *unitp && std::isspace(*unitp); ++unitp) {}
    switch (*unitp) {
    case 's': value *= 1e0; break;
    case 'm': value *= 1e-3; break;
    case 'u': value *= 1e-6; break;
    case 'n': value *= 1e-9; break;
    case 'p': value *= 1e-12; break;
    case 'f': value *= 1e-15; break;
    case 'a': value *= 1e-18; break;
    }
    return value;
}

//=========================================================================
// Buffer management

template <>
uint32_t* VerilatedTrace<VL_SUB_T, VL_BUF_T>::getOffloadBuffer() {
    uint32_t* bufferp;
    // Some jitter is expected, so some number of alternative offload buffers are
    // required, but don't allocate more than 8 buffers.
    if (m_numOffloadBuffers < 8) {
        // Allocate a new buffer if none is available
        if (!m_offloadBuffersFromWorker.tryGet(bufferp)) {
            ++m_numOffloadBuffers;
            // Note: over allocate a bit so pointer comparison is well defined
            // if we overflow only by a small amount
            bufferp = new uint32_t[m_offloadBufferSize + 16];
        }
    } else {
        // Block until a buffer becomes available
        bufferp = m_offloadBuffersFromWorker.get();
    }
    return bufferp;
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::waitForOffloadBuffer(const uint32_t* buffp) {
    // Slow path code only called on flush/shutdown, so use a simple algorithm.
    // Collect buffers from worker and stash them until we get the one we want.
    std::deque<uint32_t*> stash;
    do { stash.push_back(m_offloadBuffersFromWorker.get()); } while (stash.back() != buffp);
    // Now put them back in the queue, in the original order.
    while (!stash.empty()) {
        m_offloadBuffersFromWorker.put_front(stash.back());
        stash.pop_back();
    }
}

//=========================================================================
// Worker thread

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::offloadWorkerThreadMain() {
    bool shutdown = false;

    do {
        uint32_t* const bufferp = m_offloadBuffersToWorker.get();

        VL_TRACE_OFFLOAD_DEBUG("");
        VL_TRACE_OFFLOAD_DEBUG("Got buffer: " << bufferp);

        const uint32_t* readp = bufferp;

        std::unique_ptr<Buffer> traceBufp;  // We own the passed tracebuffer

        while (true) {
            const uint32_t cmd = readp[0];
            const uint32_t top = cmd >> 4;
            // Always set this up, as it is almost always needed
            uint32_t* const oldp = m_sigs_oldvalp + readp[1];
            // Note this increment needs to be undone on commands which do not
            // actually contain a code, but those are the rare cases.
            readp += 2;

            switch (cmd & 0xF) {
                //===
                // CHG_* commands
            case VerilatedTraceOffloadCommand::CHG_BIT_0:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_BIT_0 " << top);
                traceBufp->chgBit(oldp, 0);
                continue;
            case VerilatedTraceOffloadCommand::CHG_BIT_1:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_BIT_1 " << top);
                traceBufp->chgBit(oldp, 1);
                continue;
            case VerilatedTraceOffloadCommand::CHG_CDATA:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_CDATA " << top);
                // Bits stored in bottom byte of command
                traceBufp->chgCData(oldp, *readp, top);
                readp += 1;
                continue;
            case VerilatedTraceOffloadCommand::CHG_SDATA:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_SDATA " << top);
                // Bits stored in bottom byte of command
                traceBufp->chgSData(oldp, *readp, top);
                readp += 1;
                continue;
            case VerilatedTraceOffloadCommand::CHG_IDATA:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_IDATA " << top);
                // Bits stored in bottom byte of command
                traceBufp->chgIData(oldp, *readp, top);
                readp += 1;
                continue;
            case VerilatedTraceOffloadCommand::CHG_QDATA:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_QDATA " << top);
                // Bits stored in bottom byte of command
                traceBufp->chgQData(oldp, *reinterpret_cast<const QData*>(readp), top);
                readp += 2;
                continue;
            case VerilatedTraceOffloadCommand::CHG_WDATA:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_WDATA " << top);
                traceBufp->chgWData(oldp, readp, top);
                readp += VL_WORDS_I(top);
                continue;
            case VerilatedTraceOffloadCommand::CHG_DOUBLE:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_DOUBLE " << top);
                traceBufp->chgDouble(oldp, *reinterpret_cast<const double*>(readp));
                readp += 2;
                continue;
            case VerilatedTraceOffloadCommand::CHG_EVENT:
                VL_TRACE_OFFLOAD_DEBUG("Command CHG_EVENT " << top);
                traceBufp->chgEventTriggered(oldp);
                continue;

                //===
                // Rare commands
            case VerilatedTraceOffloadCommand::TIME_CHANGE: {
                VL_TRACE_OFFLOAD_DEBUG("Command TIME_CHANGE " << top);
                readp -= 1;  // No code in this command, undo increment
                const uint64_t timeui
                    = static_cast<uint64_t>(*reinterpret_cast<const uint32_t*>(readp)) << 32ULL
                      | static_cast<uint64_t>(*reinterpret_cast<const uint32_t*>(readp + 1));
                emitTimeChange(timeui);
                readp += 2;
                continue;
            }
            case VerilatedTraceOffloadCommand::TRACE_BUFFER:
                VL_TRACE_OFFLOAD_DEBUG("Command TRACE_BUFFER " << top);
                readp -= 1;  // No code in this command, undo increment
                traceBufp.reset(*reinterpret_cast<Buffer* const*>(readp));
                readp += 2;
                continue;

                //===
                // Commands ending this buffer
            case VerilatedTraceOffloadCommand::END:  //
                VL_TRACE_OFFLOAD_DEBUG("Command END");
                break;
            case VerilatedTraceOffloadCommand::SHUTDOWN:
                VL_TRACE_OFFLOAD_DEBUG("Command SHUTDOWN");
                shutdown = true;
                break;

            //===
            // Unknown command
            default: {  // LCOV_EXCL_START
                VL_TRACE_OFFLOAD_DEBUG("Command UNKNOWN " << cmd);
                VL_FATAL_MT(__FILE__, __LINE__, "", "Unknown trace command");
                break;
            }  // LCOV_EXCL_STOP
            }

            // The above switch will execute 'continue' when necessary,
            // so if we ever reach here, we are done with the buffer.
            break;
        }

        VL_TRACE_OFFLOAD_DEBUG("Returning buffer");

        // Return buffer
        m_offloadBuffersFromWorker.put(bufferp);
    } while (VL_LIKELY(!shutdown));
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::shutdownOffloadWorker() {
    // If the worker thread is not running, done..
    if (!m_workerThread) return;

    // Hand an buffer with a shutdown command to the worker thread
    uint32_t* const bufferp = getOffloadBuffer();
    bufferp[0] = VerilatedTraceOffloadCommand::SHUTDOWN;
    m_offloadBuffersToWorker.put(bufferp);
    // Wait for it to return
    waitForOffloadBuffer(bufferp);
    // Join the thread and delete it
    m_workerThread->join();
    m_workerThread.reset(nullptr);
}

//=============================================================================
// Life cycle

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::closeBase() {
    if (offload()) {
        shutdownOffloadWorker();
        while (m_numOffloadBuffers) {
            delete[] m_offloadBuffersFromWorker.get();
            --m_numOffloadBuffers;
        }
    }
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::flushBase() {
    if (offload()) {
        // Hand an empty buffer to the worker thread
        uint32_t* const bufferp = getOffloadBuffer();
        *bufferp = VerilatedTraceOffloadCommand::END;
        m_offloadBuffersToWorker.put(bufferp);
        // Wait for it to be returned. As the processing is in-order,
        // this ensures all previous buffers have been processed.
        waitForOffloadBuffer(bufferp);
    }
}

//=============================================================================
// Callbacks to run on global events

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::onFlush(void* selfp) {
    // This calls 'flush' on the derived class (which must then get any mutex)
    reinterpret_cast<VL_SUB_T*>(selfp)->flush();
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::onExit(void* selfp) {
    // This calls 'close' on the derived class (which must then get any mutex)
    reinterpret_cast<VL_SUB_T*>(selfp)->close();
}

//=============================================================================
// VerilatedTrace

template <>
VerilatedTrace<VL_SUB_T, VL_BUF_T>::VerilatedTrace() {
    set_time_unit(Verilated::threadContextp()->timeunitString());
    set_time_resolution(Verilated::threadContextp()->timeprecisionString());
}

template <>
VerilatedTrace<VL_SUB_T, VL_BUF_T>::~VerilatedTrace() {
    if (m_sigs_oldvalp) VL_DO_CLEAR(delete[] m_sigs_oldvalp, m_sigs_oldvalp = nullptr);
    if (m_sigs_enabledp) VL_DO_CLEAR(delete[] m_sigs_enabledp, m_sigs_enabledp = nullptr);
    Verilated::removeFlushCb(VerilatedTrace<VL_SUB_T, VL_BUF_T>::onFlush, this);
    Verilated::removeExitCb(VerilatedTrace<VL_SUB_T, VL_BUF_T>::onExit, this);
    if (offload()) closeBase();
}

//=========================================================================
// Internals available to format-specific implementations

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::traceInit() VL_MT_UNSAFE {
    // Note: It is possible to re-open a trace file (VCD in particular),
    // so we must reset the next code here, but it must have the same number
    // of codes on re-open
    const uint32_t expectedCodes = nextCode();
    m_nextCode = 1;
    m_numSignals = 0;
    m_maxBits = 0;
    m_sigs_enabledVec.clear();

    // Call all initialize callbacks for root (non-library) instances, which will:
    // - Call decl* for each signal (these eventually call ::declCode)
    // - Call the initialize callbacks of library instances underneath
    // - Store the base code
    for (const CallbackRecord& cbr : m_initCbs) {
        if (cbr.m_isLibInstance) continue;  // Will be called from parent callback
        const uint32_t baseCode = nextCode();
        m_nextCode += cbr.m_nTraceCodes;
        m_initUserp = cbr.m_userp;
        cbr.m_initCb(cbr.m_userp, self(), baseCode);
    }

    if (expectedCodes && nextCode() != expectedCodes) {
        VL_FATAL_MT(__FILE__, __LINE__, "",
                    "Reopening trace file with different number of signals");
    }

    // Now that we know the number of codes, allocate space for the buffer
    // holding previous signal values.
    if (!m_sigs_oldvalp) m_sigs_oldvalp = new uint32_t[nextCode()];

    // Apply enables
    if (m_sigs_enabledp) VL_DO_CLEAR(delete[] m_sigs_enabledp, m_sigs_enabledp = nullptr);
    if (!m_sigs_enabledVec.empty()) {
        // Else if was empty, m_sigs_enabledp = nullptr to short circuit tests
        // But it isn't, so alloc one bit for each code to indicate enablement
        // We don't want to still use m_signs_enabledVec as std::vector<bool> is not
        // guaranteed to be fast
        m_sigs_enabledp = new uint32_t[1 + VL_WORDS_I(nextCode())]{0};
        m_sigs_enabledVec.reserve(nextCode());
        for (size_t code = 0; code < nextCode(); ++code) {
            if (m_sigs_enabledVec[code]) {
                m_sigs_enabledp[VL_BITWORD_I(code)] |= 1U << VL_BITBIT_I(code);
            }
        }
        m_sigs_enabledVec.clear();
    }

    // Set callback so flush/abort will flush this file
    Verilated::addFlushCb(VerilatedTrace<VL_SUB_T, VL_BUF_T>::onFlush, this);
    Verilated::addExitCb(VerilatedTrace<VL_SUB_T, VL_BUF_T>::onExit, this);

    if (offload()) {
        // Compute offload buffer size. we need to be able to store a new value for
        // each signal, which is 'nextCode()' entries after the init callbacks
        // above have been run, plus up to 2 more words of metadata per signal,
        // plus fixed overhead of 1 for a termination flag and 3 for a time stamp
        // update and 2 for the buffer address.
        m_offloadBufferSize = nextCode() + numSignals() * 2 + 6;

        // Start the worker thread
        m_workerThread.reset(
            new std::thread{&VerilatedTrace<VL_SUB_T, VL_BUF_T>::offloadWorkerThreadMain, this});
    }
}

template <>
bool VerilatedTrace<VL_SUB_T, VL_BUF_T>::declCode(uint32_t code, const std::string& declName,
                                                  uint32_t bits) {
    if (VL_UNCOVERABLE(!code)) {
        VL_FATAL_MT(__FILE__, __LINE__, "", "Internal: internal trace problem, code 0 is illegal");
    }
    // To keep it simple, this is O(enables * signals), but we expect few enables
    bool enabled = false;
    if (m_dumpvars.empty()) enabled = true;
    for (const auto& item : m_dumpvars) {
        const int dumpvarsLevel = item.first;
        const char* dvp = item.second.c_str();
        const char* np = declName.c_str();
        while (*dvp && *dvp == *np) {
            ++dvp;
            ++np;
        }
        if (*dvp) continue;  // Didn't match dumpvar item
        if (*np && *np != ' ') continue;  // e.g. "t" isn't a match for "top"
        int levels = 0;
        while (*np) {
            if (*np++ == ' ') ++levels;
        }
        if (levels > dumpvarsLevel) continue;  // Too deep
        // We only need to set first code word if it's a multicode signal
        // as that's all we'll check for later
        if (m_sigs_enabledVec.size() <= code) m_sigs_enabledVec.resize((code + 1024) * 2);
        m_sigs_enabledVec[code] = true;
        enabled = true;
        break;
    }

    ++m_numSignals;
    m_maxBits = std::max(m_maxBits, bits);
    return enabled;
}

//=========================================================================
// Internals available to format-specific implementations

template <>
std::string VerilatedTrace<VL_SUB_T, VL_BUF_T>::timeResStr() const {
    return vl_timescaled_double(m_timeRes);
}

//=========================================================================
// External interface to client code

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::set_time_unit(const char* unitp) VL_MT_SAFE {
    m_timeUnit = timescaleToDouble(unitp);
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::set_time_unit(const std::string& unit) VL_MT_SAFE {
    set_time_unit(unit.c_str());
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::set_time_resolution(const char* unitp) VL_MT_SAFE {
    m_timeRes = timescaleToDouble(unitp);
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::set_time_resolution(const std::string& unit) VL_MT_SAFE {
    set_time_resolution(unit.c_str());
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::dumpvars(int level, const std::string& hier) VL_MT_SAFE {
    if (level == 0) {
        m_dumpvars.clear();  // empty = everything on
    } else {
        // Convert Verilog . separators to trace space separators
        std::string hierSpaced = hier;
        for (auto& i : hierSpaced) {
            if (i == '.') i = ' ';
        }
        m_dumpvars.emplace_back(level, hierSpaced);
    }
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::parallelWorkerTask(void* datap, bool) {
    ParallelWorkerData* const wdp = reinterpret_cast<ParallelWorkerData*>(datap);
    // Run the task
    wdp->m_cb(wdp->m_userp, wdp->m_bufp);
    // Mark buffer as ready
    const VerilatedLockGuard lock{wdp->m_mutex};
    wdp->m_ready.store(true);
    if (wdp->m_waiting) wdp->m_cv.notify_one();
}

template <>
VL_ATTR_NOINLINE void VerilatedTrace<VL_SUB_T, VL_BUF_T>::ParallelWorkerData::wait() {
    // Spin for a while, waiting for the buffer to become ready
    for (int i = 0; i < VL_LOCK_SPINS; ++i) {
        if (VL_LIKELY(m_ready.load(std::memory_order_relaxed))) return;
        VL_CPU_RELAX();
    }
    // We have been spinning for a while, so yield the thread
    VerilatedLockGuard lock{m_mutex};
    m_waiting = true;
    m_cv.wait(m_mutex, [this] { return m_ready.load(std::memory_order_relaxed); });
    m_waiting = false;
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::runCallbacks(const std::vector<CallbackRecord>& cbVec) {
    if (parallel()) {
        // If tracing in parallel, dispatch to the thread pool
        VlThreadPool* threadPoolp = static_cast<VlThreadPool*>(m_contextp->threadPoolp());
        // List of work items for thread (std::list, as ParallelWorkerData is not movable)
        std::list<ParallelWorkerData> workerData;
        // We use the whole pool + the main thread
        const unsigned threads = threadPoolp->numThreads() + 1;
        // Main thread executes all jobs with index % threads == 0
        std::vector<ParallelWorkerData*> mainThreadWorkerData;
        // Enqueue all the jobs
        for (const CallbackRecord& cbr : cbVec) {
            // Always get the trace buffer on the main thread
            Buffer* const bufp = getTraceBuffer(cbr.m_fidx);
            // Create new work item
            workerData.emplace_back(cbr.m_dumpCb, cbr.m_userp, bufp);
            // Grab the new work item
            ParallelWorkerData* const itemp = &workerData.back();
            // Enqueue task to thread pool, or main thread
            if (unsigned rem = cbr.m_fidx % threads) {
                threadPoolp->workerp(rem - 1)->addTask(parallelWorkerTask, itemp);
            } else {
                mainThreadWorkerData.push_back(itemp);
            }
        }
        // Execute main thread jobs
        for (ParallelWorkerData* const itemp : mainThreadWorkerData) {
            parallelWorkerTask(itemp, false);
        }
        // Commit all trace buffers in order
        for (ParallelWorkerData& item : workerData) {
            // Wait until ready
            item.wait();
            // Commit the buffer
            commitTraceBuffer(item.m_bufp);
        }

        // Done
        return;
    }
    // Fall back on sequential execution
    for (const CallbackRecord& cbr : cbVec) {
        Buffer* const traceBufferp = getTraceBuffer(cbr.m_fidx);
        cbr.m_dumpCb(cbr.m_userp, traceBufferp);
        commitTraceBuffer(traceBufferp);
    }
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::runOffloadedCallbacks(
    const std::vector<CallbackRecord>& cbVec) {
    // Fall back on sequential execution
    for (const CallbackRecord& cbr : cbVec) {
        Buffer* traceBufferp = getTraceBuffer(cbr.m_fidx);
        cbr.m_dumpOffloadCb(cbr.m_userp, static_cast<OffloadBuffer*>(traceBufferp));
        commitTraceBuffer(traceBufferp);
    }
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::dump(uint64_t timeui) VL_MT_SAFE_EXCLUDES(m_mutex) {
    // Not really VL_MT_SAFE but more VL_MT_UNSAFE_ONE.
    // This does get the mutex, but if multiple threads are trying to dump
    // chances are the data being dumped will have other problems
    const VerilatedLockGuard lock{m_mutex};
    if (VL_UNCOVERABLE(m_didSomeDump && timeui <= m_timeLastDump)) {  // LCOV_EXCL_START
        VL_PRINTF_MT("%%Warning: previous dump at t=%" PRIu64 ", requesting t=%" PRIu64
                     ", dump call ignored\n",
                     m_timeLastDump, timeui);
        return;
    }  // LCOV_EXCL_STOP
    m_timeLastDump = timeui;
    m_didSomeDump = true;

    Verilated::quiesce();

    // Call hook for format-specific behaviour
    if (VL_UNLIKELY(m_fullDump)) {
        if (!preFullDump()) return;
    } else {
        if (!preChangeDump()) return;
    }

    uint32_t* bufferp = nullptr;
    if (offload()) {
        // Currently only incremental dumps run on the worker thread
        if (VL_LIKELY(!m_fullDump)) {
            // Get the offload buffer we are about to fill
            bufferp = getOffloadBuffer();
            m_offloadBufferWritep = bufferp;
            m_offloadBufferEndp = bufferp + m_offloadBufferSize;

            // Tell worker to update time point
            m_offloadBufferWritep[0] = VerilatedTraceOffloadCommand::TIME_CHANGE;
            *reinterpret_cast<uint32_t*>(m_offloadBufferWritep + 1)
                = static_cast<uint32_t>(timeui >> 32ULL);
            *reinterpret_cast<uint32_t*>(m_offloadBufferWritep + 2)
                = static_cast<uint32_t>(timeui);
            m_offloadBufferWritep += 3;
        } else {
            // Update time point
            flushBase();
            emitTimeChange(timeui);
        }
    } else {
        // Update time point
        emitTimeChange(timeui);
    }

    // Run the callbacks
    if (VL_UNLIKELY(m_fullDump)) {
        m_fullDump = false;  // No more need for next dump to be full
        if (offload()) {
            runOffloadedCallbacks(m_fullOffloadCbs);
        } else {
            runCallbacks(m_fullCbs);
        }
    } else {
        if (offload()) {
            runOffloadedCallbacks(m_chgOffloadCbs);
        } else {
            runCallbacks(m_chgCbs);
        }
    }

    if (VL_UNLIKELY(m_constDump)) {
        m_constDump = false;
        if (offload()) {
            runOffloadedCallbacks(m_constOffloadCbs);
        } else {
            runCallbacks(m_constCbs);
        }
    }

    for (const CallbackRecord& cbr : m_cleanupCbs) cbr.m_cleanupCb(cbr.m_userp, self());

    if (offload() && VL_LIKELY(bufferp)) {
        // Mark end of the offload buffer we just filled
        *m_offloadBufferWritep++ = VerilatedTraceOffloadCommand::END;

        // Assert no buffer overflow
        assert(static_cast<size_t>(m_offloadBufferWritep - bufferp) <= m_offloadBufferSize);

        // Reset our pointers as we are giving up the buffer
        m_offloadBufferWritep = nullptr;
        m_offloadBufferEndp = nullptr;

        // Pass it to the worker thread
        m_offloadBuffersToWorker.put(bufferp);
    }
}

//=============================================================================
// Non-hot path internal interface to Verilator generated code

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addModel(VerilatedModel* modelp)
    VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};

    const bool firstModel = m_models.empty();
    const bool newModel = m_models.insert(modelp).second;
    VerilatedContext* const contextp = modelp->contextp();

    // Validate
    if (!newModel) {  // LCOV_EXCL_START
        VL_FATAL_MT(
            __FILE__, __LINE__, "",
            "The same model has already been added to this trace file or VerilatedContext");
    }
    if (VL_UNCOVERABLE(m_contextp && contextp != m_contextp)) {
        VL_FATAL_MT(__FILE__, __LINE__, "",
                    "A trace file instance can only handle models from the same VerilatedContext");
    }
    if (VL_UNCOVERABLE(m_didSomeDump)) {
        VL_FATAL_MT(__FILE__, __LINE__, "",
                    "Cannot add models to a trace file if 'dump' has already been called");
    }  // LCOV_EXCL_STOP

    // Keep hold of the context
    m_contextp = contextp;

    // Get the desired trace config from the model
    const std::unique_ptr<VerilatedTraceConfig> configp = modelp->traceConfig();

    // Configure trace base class
    if (!firstModel) {
        if (m_offload != configp->m_useOffloading) {
            VL_FATAL_MT(__FILE__, __LINE__, "",
                        "Either all or no models using the same trace file must use offloading");
        }
    }
    m_offload = configp->m_useOffloading;
    // If at least one model requests parallel tracing, then use it
    m_parallel |= configp->m_useParallel;

    if (VL_UNCOVERABLE(m_parallel && m_offload)) {  // LCOV_EXCL_START
        VL_FATAL_MT(__FILE__, __LINE__, "", "Cannot use parallel tracing with offloading");
    }  // LCOV_EXCL_STOP

    // Configure format-specific sub class
    configure(*(configp.get()));
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addCallbackRecord(std::vector<CallbackRecord>& cbVec,
                                                           CallbackRecord&& cbRec)
    VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    cbVec.push_back(cbRec);
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addInitCb(initCb_t cb, void* userp,
                                                   const std::string& name, bool isLibInstance,
                                                   uint32_t nTraceCodes) VL_MT_SAFE {
    addCallbackRecord(m_initCbs, CallbackRecord{cb, userp, isLibInstance, name, nTraceCodes});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addConstCb(dumpCb_t cb, uint32_t fidx,
                                                    void* userp) VL_MT_SAFE {
    addCallbackRecord(m_constCbs, CallbackRecord{cb, fidx, userp});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addConstCb(dumpOffloadCb_t cb, uint32_t fidx,
                                                    void* userp) VL_MT_SAFE {
    addCallbackRecord(m_constOffloadCbs, CallbackRecord{cb, fidx, userp});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addFullCb(dumpCb_t cb, uint32_t fidx,
                                                   void* userp) VL_MT_SAFE {
    addCallbackRecord(m_fullCbs, CallbackRecord{cb, fidx, userp});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addFullCb(dumpOffloadCb_t cb, uint32_t fidx,
                                                   void* userp) VL_MT_SAFE {
    addCallbackRecord(m_fullOffloadCbs, CallbackRecord{cb, fidx, userp});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addChgCb(dumpCb_t cb, uint32_t fidx,
                                                  void* userp) VL_MT_SAFE {
    addCallbackRecord(m_chgCbs, CallbackRecord{cb, fidx, userp});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addChgCb(dumpOffloadCb_t cb, uint32_t fidx,
                                                  void* userp) VL_MT_SAFE {
    addCallbackRecord(m_chgOffloadCbs, CallbackRecord{cb, fidx, userp});
}
template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::addCleanupCb(cleanupCb_t cb, void* userp) VL_MT_SAFE {
    addCallbackRecord(m_cleanupCbs, CallbackRecord{cb, userp});
}

template <>
void VerilatedTrace<VL_SUB_T, VL_BUF_T>::initLib(const std::string& name) VL_MT_SAFE {
    // Note it's possible the instance doesn't exist if the lib was compiled without tracing
    void* const prevInitUserp = m_initUserp;
    for (const CallbackRecord& cbr : m_initCbs) {
        if (cbr.m_name != name) continue;
        const uint32_t baseCode = nextCode();
        m_nextCode += cbr.m_nTraceCodes;
        m_initUserp = cbr.m_userp;
        cbr.m_initCb(cbr.m_userp, self(), baseCode);
        m_initUserp = prevInitUserp;
    }
}

//=========================================================================
// Primitives converting binary values to strings...

// All of these take a destination pointer where the string will be emitted,
// and a value to convert. There are a couple of variants for efficiency.

static inline void cvtCDataToStr(char* dstp, CData value) {
#ifdef VL_HAVE_SSE2
    // Similar to cvtSDataToStr but only the bottom 8 byte lanes are used
    const __m128i a = _mm_cvtsi32_si128(value);
    const __m128i b = _mm_unpacklo_epi8(a, a);
    const __m128i c = _mm_shufflelo_epi16(b, 0);
    const __m128i m = _mm_set1_epi64x(0x0102040810204080);
    const __m128i d = _mm_cmpeq_epi8(_mm_and_si128(c, m), m);
    const __m128i result = _mm_sub_epi8(_mm_set1_epi8('0'), d);
    _mm_storel_epi64(reinterpret_cast<__m128i*>(dstp), result);
#else
    dstp[0] = '0' | static_cast<char>((value >> 7) & 1);
    dstp[1] = '0' | static_cast<char>((value >> 6) & 1);
    dstp[2] = '0' | static_cast<char>((value >> 5) & 1);
    dstp[3] = '0' | static_cast<char>((value >> 4) & 1);
    dstp[4] = '0' | static_cast<char>((value >> 3) & 1);
    dstp[5] = '0' | static_cast<char>((value >> 2) & 1);
    dstp[6] = '0' | static_cast<char>((value >> 1) & 1);
    dstp[7] = '0' | static_cast<char>(value & 1);
#endif
}

static inline void cvtSDataToStr(char* dstp, SData value) {
#ifdef VL_HAVE_SSE2
    // We want each bit in the 16-bit input value to end up in a byte lane
    // within the 128-bit XMM register. Note that x86 is little-endian and we
    // want the MSB of the input at the low address, so we will bit-reverse
    // at the same time.

    // Put value in bottom of 128-bit register a[15:0] = value
    const __m128i a = _mm_cvtsi32_si128(value);
    // Interleave bytes with themselves
    // b[15: 0] = {2{a[ 7:0]}} == {2{value[ 7:0]}}
    // b[31:16] = {2{a[15:8]}} == {2{value[15:8]}}
    const __m128i b = _mm_unpacklo_epi8(a, a);
    // Shuffle bottom 64 bits, note swapping high bytes with low bytes
    // c[31: 0] = {2{b[31:16]}} == {4{value[15:8}}
    // c[63:32] = {2{b[15: 0]}} == {4{value[ 7:0}}
    const __m128i c = _mm_shufflelo_epi16(b, 0x05);
    // Shuffle whole register
    // d[ 63: 0] = {2{c[31: 0]}} == {8{value[15:8}}
    // d[126:54] = {2{c[63:32]}} == {8{value[ 7:0}}
    const __m128i d = _mm_shuffle_epi32(c, 0x50);
    // Test each bit within the bytes, this sets each byte lane to 0
    // if the bit for that lane is 0 and to 0xff if the bit is 1.
    const __m128i m = _mm_set1_epi64x(0x0102040810204080);
    const __m128i e = _mm_cmpeq_epi8(_mm_and_si128(d, m), m);
    // Convert to ASCII by subtracting the masks from ASCII '0':
    // '0' - 0 is '0', '0' - -1 is '1'
    const __m128i result = _mm_sub_epi8(_mm_set1_epi8('0'), e);
    // Store the 16 characters to the un-aligned buffer
    _mm_storeu_si128(reinterpret_cast<__m128i*>(dstp), result);
#else
    cvtCDataToStr(dstp, value >> 8);
    cvtCDataToStr(dstp + 8, value);
#endif
}

static inline void cvtIDataToStr(char* dstp, IData value) {
#ifdef VL_HAVE_AVX2
    // Similar to cvtSDataToStr but the bottom 16-bits are processed in the
    // top half of the YMM registers
    const __m256i a = _mm256_insert_epi32(_mm256_undefined_si256(), value, 0);
    const __m256i b = _mm256_permute4x64_epi64(a, 0);
    const __m256i s = _mm256_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
                                      2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3);
    const __m256i c = _mm256_shuffle_epi8(b, s);
    const __m256i m = _mm256_set1_epi64x(0x0102040810204080);
    const __m256i d = _mm256_cmpeq_epi8(_mm256_and_si256(c, m), m);
    const __m256i result = _mm256_sub_epi8(_mm256_set1_epi8('0'), d);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(dstp), result);
#else
    cvtSDataToStr(dstp, value >> 16);
    cvtSDataToStr(dstp + 16, value);
#endif
}

static inline void cvtQDataToStr(char* dstp, QData value) {
    cvtIDataToStr(dstp, value >> 32);
    cvtIDataToStr(dstp + 32, value);
}

#define cvtEDataToStr cvtIDataToStr

//=========================================================================
// VerilatedTraceBuffer

template <>
VerilatedTraceBuffer<VL_BUF_T>::VerilatedTraceBuffer(Trace& owner)
    : VL_BUF_T{owner}
    , m_sigs_oldvalp{owner.m_sigs_oldvalp}
    , m_sigs_enabledp{owner.m_sigs_enabledp} {}

// These functions must write the new value back into the old value store,
// and subsequently call the format-specific emit* implementations. Note
// that this file must be included in the format-specific implementation, so
// the emit* functions can be inlined for performance.

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullBit(uint32_t* oldp, CData newval) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    *oldp = newval;  // Still copy even if not tracing so chg doesn't call full
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    emitBit(code, newval);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullEvent(uint32_t* oldp, const VlEventBase* newvalp) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    // No need to update *oldp
    if (newvalp->isTriggered()) emitEvent(code);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullEventTriggered(uint32_t* oldp) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    // No need to update *oldp
    emitEvent(code);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullCData(uint32_t* oldp, CData newval, int bits) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    *oldp = newval;  // Still copy even if not tracing so chg doesn't call full
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    emitCData(code, newval, bits);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullSData(uint32_t* oldp, SData newval, int bits) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    *oldp = newval;  // Still copy even if not tracing so chg doesn't call full
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    emitSData(code, newval, bits);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullIData(uint32_t* oldp, IData newval, int bits) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    *oldp = newval;  // Still copy even if not tracing so chg doesn't call full
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    emitIData(code, newval, bits);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullQData(uint32_t* oldp, QData newval, int bits) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    std::memcpy(oldp, &newval, sizeof(newval));
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    emitQData(code, newval, bits);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullWData(uint32_t* oldp, const WData* newvalp, int bits) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    for (int i = 0; i < VL_WORDS_I(bits); ++i) oldp[i] = newvalp[i];
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    emitWData(code, newvalp, bits);
}

template <>
void VerilatedTraceBuffer<VL_BUF_T>::fullDouble(uint32_t* oldp, double newval) {
    const uint32_t code = oldp - m_sigs_oldvalp;
    std::memcpy(oldp, &newval, sizeof(newval));
    if (VL_UNLIKELY(m_sigs_enabledp && !(VL_BITISSET_W(m_sigs_enabledp, code)))) return;
    // cppcheck-suppress invalidPointerCast
    emitDouble(code, newval);
}

//=========================================================================
// VerilatedTraceOffloadBuffer

template <>
VerilatedTraceOffloadBuffer<VL_BUF_T>::VerilatedTraceOffloadBuffer(VL_SUB_T& owner)
    : VerilatedTraceBuffer<VL_BUF_T>{owner}
    , m_offloadBufferWritep{owner.m_offloadBufferWritep}
    , m_offloadBufferEndp{owner.m_offloadBufferEndp} {
    if (m_offloadBufferWritep) {
        using This = VerilatedTraceBuffer<VL_BUF_T>*;
        // Tack on the buffer address
        static_assert(2 * sizeof(uint32_t) >= sizeof(This),
                      "This should be enough on all platforms");
        *m_offloadBufferWritep++ = VerilatedTraceOffloadCommand::TRACE_BUFFER;
        *reinterpret_cast<This*>(m_offloadBufferWritep) = static_cast<This>(this);
        m_offloadBufferWritep += 2;
    }
}

#endif  // VL_CPPCHECK
