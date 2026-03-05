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
/// \brief Verilated thread pool and profiling header
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use by Verilated library multithreaded
/// routines.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_THREADS_H_
#define VERILATOR_VERILATED_THREADS_H_

#include "verilatedos.h"

#include "verilated.h"  // for VerilatedMutex and clang annotations

#include <atomic>
#include <condition_variable>
#include <set>
#include <stack>
#include <thread>
#include <vector>

// Use pthreads directly on macOS (could do this on Linux too if needing APIs unavailable via C++)
#if defined(_POSIX_THREADS) && defined(__APPLE__)
#define VL_USE_PTHREADS
#endif

#ifdef VL_USE_PTHREADS
#include <pthread.h>
#endif

class VlExecutionProfiler;
class VlThreadPool;

// VlMTaskVertex and VlThreadpool will work with multiple model class types.
// Since the type is opaque to VlMTaskVertex and VlThreadPool, represent it
// as a void* here.
using VlSelfP = void*;

using VlExecFnp = void (*)(VlSelfP, bool);

// Track dependencies for a single MTask.
class VlMTaskVertex final {
    // MEMBERS
    static std::atomic<uint64_t> s_yields;  // Statistics

    // On even cycles, _upstreamDepsDone increases as upstream
    // dependencies complete. When it reaches _upstreamDepCount,
    // this MTaskVertex is ready.
    //
    // On odd cycles, _upstreamDepsDone decreases as upstream
    // dependencies complete, and when it reaches zero this MTaskVertex
    // is ready.
    //
    // An atomic is smaller than a mutex, and lock-free.
    //
    // (Why does the size of this class matter? If an mtask has many
    // downstream mtasks to notify, we hope these will pack into a
    // small number of cache lines to reduce the cost of pointer chasing
    // during done-notification. Nobody's quantified that cost though.
    // If we were really serious about shrinking this class, we could
    // use 16-bit types here...)
    std::atomic<uint32_t> m_upstreamDepsDone;
    const uint32_t m_upstreamDepCount;

public:
    // CONSTRUCTORS

    // 'upstreamDepCount' is the number of upstream MTaskVertex's
    // that must notify this MTaskVertex before it will become ready
    // to run.
    explicit VlMTaskVertex(uint32_t upstreamDepCount);
    ~VlMTaskVertex() = default;

    static uint64_t yields() { return s_yields; }
    static void yieldThread() {
        ++s_yields;  // Statistics
        std::this_thread::yield();
    }

    // Upstream mtasks must call this when they complete.
    // Returns true when the current MTaskVertex becomes ready to execute,
    // false while it's still waiting on more dependencies.
    bool signalUpstreamDone(bool evenCycle) {
        if (evenCycle) {
            const uint32_t upstreamDepsDone
                = 1 + m_upstreamDepsDone.fetch_add(1, std::memory_order_release);
            assert(upstreamDepsDone <= m_upstreamDepCount);
            return (upstreamDepsDone == m_upstreamDepCount);
        } else {
            const uint32_t upstreamDepsDone_prev
                = m_upstreamDepsDone.fetch_sub(1, std::memory_order_release);
            assert(upstreamDepsDone_prev > 0);
            return (upstreamDepsDone_prev == 1);
        }
    }
    bool areUpstreamDepsDone(bool evenCycle) const {
        const uint32_t target = evenCycle ? m_upstreamDepCount : 0;
        return m_upstreamDepsDone.load(std::memory_order_acquire) == target;
    }
    void waitUntilUpstreamDone(bool evenCycle) const {
        unsigned ct = 0;
        while (VL_UNLIKELY(!areUpstreamDepsDone(evenCycle))) {
            VL_CPU_RELAX();
            ++ct;
            if (VL_UNLIKELY(ct > VL_LOCK_SPINS)) {
                ct = 0;
                yieldThread();
            }
        }
    }
};

class VlWorkerThread final {
    friend class VlThreadPool;

    // TYPES
    struct ExecRec final {
        VlExecFnp m_fnp = nullptr;  // Function to execute
        VlSelfP m_selfp = nullptr;  // Symbol table to execute
        bool m_evenCycle = false;  // Even/odd for flag alternation
        ExecRec() = default;
        ExecRec(VlExecFnp fnp, VlSelfP selfp, bool evenCycle)
            : m_fnp{fnp}
            , m_selfp{selfp}
            , m_evenCycle{evenCycle} {}
    };

    // MEMBERS
    mutable VerilatedMutex m_mutex;
    std::condition_variable_any m_cv;
    // Only notify the condition_variable if the worker is waiting
    bool m_waiting VL_GUARDED_BY(m_mutex) = false;

    // Why a vector? We expect the pending list to be very short, typically
    // 0 or 1 or 2, so popping from the front shouldn't be
    // expensive. Revisit if we ever have longer queues...
    std::vector<ExecRec> m_ready VL_GUARDED_BY(m_mutex);
    // Store the size atomically, so we can spin wait
    std::atomic<size_t> m_ready_size;
    // Thread context
    VerilatedContext* const m_contextp;
    // Underlying thread record
#ifdef VL_USE_PTHREADS
    pthread_t m_pthread{};
#else
    std::thread m_cthread{};
#endif

    // METHDOS
    static void* start(void*);  // Static entry point, invokes 'main'
    void main();  // 'main' loop of thread

    VL_UNCOPYABLE(VlWorkerThread);

public:
    // CONSTRUCTORS
    explicit VlWorkerThread(VerilatedContext* contextp);
    ~VlWorkerThread();

    // METHODS
    template <bool N_SpinWait>
    void dequeWork(ExecRec* workp) VL_MT_SAFE_EXCLUDES(m_mutex) {
        // Spin for a while, waiting for new data
        if VL_CONSTEXPR_CXX17 (N_SpinWait) {
            for (unsigned i = 0; i < VL_LOCK_SPINS; ++i) {
                if (VL_LIKELY(m_ready_size.load(std::memory_order_relaxed))) break;
                VL_CPU_RELAX();
            }
        }
        VerilatedLockGuard lock{m_mutex};
        while (m_ready.empty()) {
            m_waiting = true;
            m_cv.wait(m_mutex);
        }
        m_waiting = false;
        // As noted above this is inefficient if our ready list is ever
        // long (but it shouldn't be)
        *workp = m_ready.front();
        m_ready.erase(m_ready.begin());
        m_ready_size.fetch_sub(1, std::memory_order_relaxed);
    }
    void addTask(VlExecFnp fnp, VlSelfP selfp, bool evenCycle = false)
        VL_MT_SAFE_EXCLUDES(m_mutex) {
        bool notify;
        {
            const VerilatedLockGuard lock{m_mutex};
            m_ready.emplace_back(fnp, selfp, evenCycle);
            m_ready_size.fetch_add(1, std::memory_order_relaxed);
            notify = m_waiting;
        }
        if (notify) m_cv.notify_one();
    }

    void shutdown();  // Finish current tasks, then terminate thread
    void wait();  // Blocks calling thread until all tasks complete in this thread
};

class VlThreadPool final : public VerilatedVirtualBase {
    // MEMBERS
    std::vector<VlWorkerThread*> m_workers;  // our workers

    mutable VerilatedMutex m_mutex;  // Guards indexes of unassigned workers
    // Indexes of unassigned workers
    std::stack<size_t> m_unassignedWorkers VL_GUARDED_BY(m_mutex);
    // For sequentially generating task IDs to avoid shadowing
    std::atomic<unsigned> m_assignedTasks{0};
    std::string m_numaStatus;  // Status of NUMA assignment

public:
    // CONSTRUCTORS
    // Construct a thread pool with 'nThreads' dedicated threads. The thread
    // pool will create these threads and make them available to execute tasks
    // via this->workerp(index)->addTask(...)
    VlThreadPool(VerilatedContext* contextp, unsigned nThreads);
    ~VlThreadPool() override;

    // METHODS
    size_t assignWorkerIndex() {
        const VerilatedLockGuard lock{m_mutex};
        assert(!m_unassignedWorkers.empty());
        const size_t index = m_unassignedWorkers.top();
        m_unassignedWorkers.pop();
        return index;
    }
    void freeWorkerIndexes(std::vector<size_t>& indexes) {
        const VerilatedLockGuard lock{m_mutex};
        for (size_t index : indexes) m_unassignedWorkers.push(index);
        indexes.clear();
    }
    unsigned assignTaskIndex() { return m_assignedTasks++; }
    int numThreads() const { return static_cast<int>(m_workers.size()); }
    std::string numaStatus() const { return m_numaStatus; }
    VlWorkerThread* workerp(int index) {
        assert(index >= 0);
        assert(index < static_cast<int>(m_workers.size()));
        return m_workers[index];
    }

private:
    VL_UNCOPYABLE(VlThreadPool);

    std::string numaAssign(VerilatedContext* contextp);
};

#endif
