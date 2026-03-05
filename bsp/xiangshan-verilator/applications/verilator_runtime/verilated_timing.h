// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2001-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************
///
/// \file
/// \brief Verilated timing header
///
/// This file is included automatically by Verilator in some of the C++ files
/// it generates if timing features are used.
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use.
///
/// See the internals documentation docs/internals.rst for details.
///
//*************************************************************************
#ifndef VERILATOR_VERILATED_TIMING_H_
#define VERILATOR_VERILATED_TIMING_H_

#include "verilated.h"

#include <limits>
#include <vector>

// clang-format off
// Some preprocessor magic to support both Clang and GCC coroutines with both libc++ and libstdc++
#if defined _LIBCPP_VERSION  // libc++
# if defined(__has_include) && !__has_include(<coroutine>) && __has_include(<experimental/coroutine>)
#  if __clang_major__ > 13  // Clang > 13 warns that coroutine types in std::experimental are deprecated
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wdeprecated-experimental-coroutine"
#  endif
#  include <experimental/coroutine>
   namespace std {
       using namespace experimental;  // Bring std::experimental into the std namespace
   }
# else
#  include <coroutine>
# endif
#else
# if defined __clang__ && defined __GLIBCXX__ && !defined __cpp_impl_coroutine
#  define __cpp_impl_coroutine 1  // Clang doesn't define this, but it's needed for libstdc++
# endif
# include <coroutine>
# if __clang_major__ < 14
   namespace std {  // Bring coroutine library into std::experimental, as Clang < 14 expects it to be there
       namespace experimental {
           using namespace std;
       }
   }
# endif
#endif
// clang-format on

// Placeholder for compiling with --protect-ids
#define VL_UNKNOWN "<unknown>"

//=============================================================================
// VlFileLineDebug stores a SystemVerilog source code location. Used in VlCoroutineHandle for
// debugging purposes.

class VlFileLineDebug final {
    // MEMBERS
#ifdef VL_DEBUG
    const char* m_filename = nullptr;
    int m_lineno = 0;
#endif

public:
    // CONSTRUCTORS
    // Construct
    VlFileLineDebug() = default;
    VlFileLineDebug(const char* filename, int lineno)
#ifdef VL_DEBUG
        : m_filename{filename}
        , m_lineno{lineno}
#endif
    {
    }

    // METHODS
#ifdef VL_DEBUG
    const char* filename() const { return m_filename; }
    int lineno() const { return m_lineno; }
#endif
};

//=============================================================================
// VlCoroutineHandle is a non-copyable (but movable) coroutine handle. On resume, the handle is
// cleared, as we assume that either the coroutine has finished and deleted itself, or, if it got
// suspended, another VlCoroutineHandle was created to manage it.

class VlCoroutineHandle final {
    VL_UNCOPYABLE(VlCoroutineHandle);

    // MEMBERS
    std::coroutine_handle<> m_coro;  // The wrapped coroutine handle
    VlProcessRef m_process;  // Data of the suspended process, null if not needed
    VlFileLineDebug m_fileline;

public:
    // CONSTRUCTORS
    // Construct
    // non-explicit:
    // cppcheck-suppress noExplicitConstructor
    VlCoroutineHandle(VlProcessRef process)
        : m_coro{nullptr}
        , m_process{process} {
        if (m_process) m_process->state(VlProcess::WAITING);
    }
    VlCoroutineHandle(std::coroutine_handle<> coro, VlProcessRef process, VlFileLineDebug fileline)
        : m_coro{coro}
        , m_process{process}
        , m_fileline{fileline} {
        if (m_process) m_process->state(VlProcess::WAITING);
    }
    // Move the handle, leaving a nullptr
    // non-explicit:
    // cppcheck-suppress noExplicitConstructor
    VlCoroutineHandle(VlCoroutineHandle&& moved)
        : m_coro{std::exchange(moved.m_coro, nullptr)}
        , m_process{std::exchange(moved.m_process, nullptr)}
        , m_fileline{moved.m_fileline} {}
    // Destroy if the handle isn't null
    ~VlCoroutineHandle() {
        // Usually these coroutines should get resumed; we only need to clean up if we destroy a
        // model with some coroutines suspended
        if (VL_UNLIKELY(m_coro)) {
            m_coro.destroy();
            if (m_process && m_process->state() != VlProcess::KILLED) {
                m_process->state(VlProcess::FINISHED);
            }
        }
    }
    // METHODS
    // Move the handle, leaving a null handle
    auto& operator=(VlCoroutineHandle&& moved) {
        m_coro = std::exchange(moved.m_coro, nullptr);
        m_process = std::exchange(moved.m_process, nullptr);
        m_fileline = moved.m_fileline;
        return *this;
    }
    // Resume the coroutine if the handle isn't null and the process isn't killed
    void resume();
#ifdef VL_DEBUG
    void dump() const;
#endif
};

enum class VlDelayPhase : bool { ACTIVE, INACTIVE };

//=============================================================================
// VlDelayScheduler stores coroutines to be resumed at a certain simulation time. If the current
// time is equal to a coroutine's resume time, the coroutine gets resumed.

class VlDelayScheduler final {
    // TYPES
    // Time-sorted queue of timestamps and handles
    using VlDelayedCoroutineQueue = std::multimap<uint64_t, VlCoroutineHandle>;

    // MEMBERS
    VerilatedContext& m_context;
    VlDelayedCoroutineQueue m_queue;  // Coroutines to be restored at a certain simulation time
    std::vector<VlCoroutineHandle> m_zeroDelayed;  // Coroutines waiting for #0
    // Coroutines that waited for #0 and are being resumed now. As member to avoid reallocations
    std::vector<VlCoroutineHandle> m_zeroDelayesSwap;

public:
    // CONSTRUCTORS
    explicit VlDelayScheduler(VerilatedContext& context)
        : m_context{context} {}
    // METHODS
    // Resume coroutines waiting for the current simulation time
    void resume();
    // Resume coroutines waiting for #0
    void resumeZeroDelay();
    // Returns the simulation time of the next time slot (aborts if there are no delayed
    // coroutines)
    uint64_t nextTimeSlot() const;
    // Are there no delayed coroutines awaiting?
    bool empty() const { return m_queue.empty() && m_zeroDelayed.empty(); }
    // Are there coroutines to resume at the current simulation time?
    bool awaitingCurrentTime() const {
        return (!m_queue.empty() && (m_queue.cbegin()->first <= m_context.time()));
    }
    // Are there coroutines to resume in the inactive region after a #0 delay?
    bool awaitingZeroDelay() const { return !m_zeroDelayed.empty(); }
#ifdef VL_DEBUG
    void dump() const;
#endif
    // Used by coroutines for co_awaiting a certain simulation time
    auto delay(uint64_t delay, VlProcessRef process, const char* filename = VL_UNKNOWN,
               int lineno = 0) {
        struct Awaitable final {
            VlProcessRef process;  // Data of the suspended process, null if not needed
            VlDelayedCoroutineQueue& queue;
            std::vector<VlCoroutineHandle>& queueZeroDelay;
            const uint64_t delay;
            const VlDelayPhase phase;
            const VlFileLineDebug fileline;

            bool await_ready() const { return false; }  // Always suspend
            void await_suspend(std::coroutine_handle<> coro) {
                // Both active delays and fork..join_none #0 are resumed out of the time queue.
                if (phase != VlDelayPhase::INACTIVE) {
                    queue.emplace(delay, VlCoroutineHandle{coro, process, fileline});
                } else {
                    queueZeroDelay.emplace_back(VlCoroutineHandle{coro, process, fileline});
                }
            }
            void await_resume() const {}
        };

        VlDelayPhase phase;
        if (delay != 0) {
            // UINT64_MAX is a sentinel for synthetic fork..join_none delays.
            if (delay == std::numeric_limits<uint64_t>::max()) delay = 0;
            phase = VlDelayPhase::ACTIVE;
        } else {
            phase = VlDelayPhase::INACTIVE;
        }
        return Awaitable{process,       m_queue,
                         m_zeroDelayed, m_context.time() + delay,
                         phase,         VlFileLineDebug{filename, lineno}};
    }
};

//=============================================================================
// VlTriggerScheduler stores coroutines to be resumed by a trigger. It does not keep track of its
// trigger, relying on calling code to resume when appropriate. Coroutines are kept in three stages
// - 'awaiting', 'fired' and 'toResume'. Whenever a coroutine is suspended, it lands in the
// 'awaiting' stage. Only when ready() is called, these coroutines get moved to the 'fired' stage.
// When moveToResumeQueue() is begin called all coroutines from 'ready' are moved to 'toResume'.
// That's when they can be resumed. This is done to avoid resuming processes before they start
// waiting.

class VlTriggerScheduler final {
    // TYPES
    using VlCoroutineVec = std::vector<VlCoroutineHandle>;

    // MEMBERS
    VlCoroutineVec m_awaiting;  // Coroutines suspended before ready() was called
                                // (not resumable)
    VlCoroutineVec m_fired;  // Coroutines that were triggered (all coros from m_awaiting are moved
                             // here in ready())
    VlCoroutineVec m_toResume;  // Coroutines to resume in next resumePrep()
                                // - moved here in commit()

public:
    // METHODS
    // Resumes all coroutines from the m_toResume
    void resume(const char* eventDescription = VL_UNKNOWN);
    // Moves all coroutines from m_fired to m_toResume
    void moveToResumeQueue(const char* eventDescription = VL_UNKNOWN);
    // Moves all coroutines from m_awaiting to m_fired
    void ready(const char* eventDescription = VL_UNKNOWN);
    // Are there no coroutines awaiting?
    bool empty() const { return m_fired.empty() && m_awaiting.empty(); }
#ifdef VL_DEBUG
    void dump(const char* eventDescription) const;
#endif
    // Used by coroutines for co_awaiting a certain trigger
    auto trigger(bool ready, VlProcessRef process, const char* eventDescription = VL_UNKNOWN,
                 const char* filename = VL_UNKNOWN, int lineno = 0) {
        VL_DEBUG_IF(VL_DBG_MSGF("         Suspending process waiting for %s at %s:%d\n",
                                eventDescription, filename, lineno););
        struct Awaitable final {
            VlCoroutineVec& suspended;  // Coros waiting on trigger
            VlProcessRef process;  // Data of the suspended process, null if not needed
            VlFileLineDebug fileline;

            bool await_ready() const { return false; }  // Always suspend
            void await_suspend(std::coroutine_handle<> coro) {
                suspended.emplace_back(coro, process, fileline);
            }
            void await_resume() const {}
        };
        return Awaitable{ready ? m_fired : m_awaiting, process, VlFileLineDebug{filename, lineno}};
    }
};

//=============================================================================
// VlDynamicTriggerScheduler is used for cases where triggers cannot be statically referenced and
// evaluated. Coroutines that make use of this scheduler must adhere to a certain procedure:
//     __Vtrigger = 0;
//     <locals and inits required for trigger eval>
//     while (!__Vtrigger) {
//         co_await __VdynSched.evaluation();
//         <pre updates>;
//         __Vtrigger = <trigger eval>;
//         __VdynShed.anyTriggered(__Vtrigger);
//         [optionally] co_await __VdynSched.postUpdate();
//         <post updates>;
//     }
//    co_await __VdynSched.resumption();
// The coroutines get resumed at trigger evaluation time, evaluate their local triggers, optionally
// await the post update step, and if the trigger is set, await proper resumption in the 'act' eval
// step.

class VlDynamicTriggerScheduler final {
    // TYPES
    using VlCoroutineVec = std::vector<VlCoroutineHandle>;

    // MEMBERS
    bool m_anyTriggered = false;  // If true, at least one trigger was set
    VlCoroutineVec m_suspended;  // Suspended coroutines awaiting trigger evaluation
    VlCoroutineVec m_evaluated;  // Coroutines currently being evaluated (for evaluate())
    VlCoroutineVec m_triggered;  // Coroutines whose triggers were set, and are awaiting resumption
    VlCoroutineVec m_post;  // Coroutines awaiting the post update step (only relevant for triggers
                            // with destructive post updates, e.g. named events)

    // METHODS
    auto awaitable(VlProcessRef process, VlCoroutineVec& queue, const char* filename, int lineno) {
        struct Awaitable final {
            VlProcessRef process;  // Data of the suspended process, null if not needed
            VlCoroutineVec& suspended;  // Coros waiting on trigger
            VlFileLineDebug fileline;

            bool await_ready() const { return false; }  // Always suspend
            void await_suspend(std::coroutine_handle<> coro) {
                suspended.emplace_back(coro, process, fileline);
            }
            void await_resume() const {}
        };
        return Awaitable{process, queue, VlFileLineDebug{filename, lineno}};
    }

public:
    // Evaluates all dynamic triggers (resumed coroutines that co_await evaluation())
    bool evaluate();
    // Called by coroutines that evaluate triggers to notify the scheduler if any triggers were set
    void anyTriggered(bool triggered) { m_anyTriggered = m_anyTriggered || triggered; }
    // Runs post updates for all dynamic triggers (resumes coroutines that co_await postUpdate())
    void doPostUpdates();
    // Resumes all coroutines whose triggers are set (those that co_await resumption())
    void resume();
#ifdef VL_DEBUG
    void dump() const;
#endif
    // Used by coroutines for co_awaiting trigger evaluation
    auto evaluation(VlProcessRef process, const char* eventDescription, const char* filename,
                    int lineno) {
        VL_DEBUG_IF(VL_DBG_MSGF("         Suspending process waiting for %s at %s:%d\n",
                                eventDescription, filename, lineno););
        return awaitable(process, m_suspended, filename, lineno);
    }
    // Used by coroutines for co_awaiting the trigger post update step
    auto postUpdate(VlProcessRef process, const char* eventDescription, const char* filename,
                    int lineno) {
        VL_DEBUG_IF(
            VL_DBG_MSGF("         Process waiting for %s at %s:%d awaiting the post update step\n",
                        eventDescription, filename, lineno););
        return awaitable(process, m_post, filename, lineno);
    }
    // Used by coroutines for co_awaiting the resumption step (in 'act' eval)
    auto resumption(VlProcessRef process, const char* eventDescription, const char* filename,
                    int lineno) {
        VL_DEBUG_IF(VL_DBG_MSGF("         Process waiting for %s at %s:%d awaiting resumption\n",
                                eventDescription, filename, lineno););
        return awaitable(process, m_triggered, filename, lineno);
    }
};

//=============================================================================
// VlForever is a helper awaitable type for suspending coroutines forever. Used for constant
// wait statements.

struct VlForever final {
    bool await_ready() const { return false; }  // Always suspend
    void await_suspend(std::coroutine_handle<> coro) const { coro.destroy(); }
    void await_resume() const {}
};

//=============================================================================
// VlForkSync is used to manage fork..join and fork..join_any constructs.

class VlForkSync final {
    // VlJoin stores the handle of a suspended coroutine that did a fork..join or fork..join_any.
    // If the counter reaches 0, the suspended coroutine shall be resumed.
    struct VlJoin final {
        size_t m_counter = 0;  // When reaches 0, resume suspended coroutine
        VlCoroutineHandle m_susp;  // Coroutine to resume
    };

    // The join info is shared among all forked processes
    std::shared_ptr<VlJoin> m_join;

public:
    // Create the join object and set the counter to the specified number
    void init(size_t count, VlProcessRef process) { m_join.reset(new VlJoin{count, {process}}); }
    // Called whenever any of the forked processes finishes. If the join counter reaches 0, the
    // main process gets resumed
    void done(const char* filename = VL_UNKNOWN, int lineno = 0);
    // Used by coroutines for co_awaiting a join
    auto join(VlProcessRef process, const char* filename = VL_UNKNOWN, int lineno = 0) {
        assert(m_join);
        VL_DEBUG_IF(
            VL_DBG_MSGF("             Awaiting join of fork at: %s:%d\n", filename, lineno););
        struct Awaitable final {
            VlProcessRef process;  // Data of the suspended process, null if not needed
            const std::shared_ptr<VlJoin> join;  // Join to await on
            VlFileLineDebug fileline;

            bool await_ready() { return join->m_counter == 0; }  // Suspend if join still exists
            void await_suspend(std::coroutine_handle<> coro) {
                join->m_susp = {coro, process, fileline};
            }
            void await_resume() const {}
        };
        return Awaitable{process, m_join, VlFileLineDebug{filename, lineno}};
    }
};

//=============================================================================
// VlCoroutine
// Return value of a coroutine. Used for chaining coroutine suspension/resumption.

class VlCoroutine final {
private:
    // TYPES
    struct VlPromise final {
        std::coroutine_handle<> m_continuation;  // Coroutine to resume after this one finishes
        VlCoroutine* m_corop = nullptr;  // Pointer to the coroutine return object

        ~VlPromise();

        VlCoroutine get_return_object() { return {this}; }

        // Never suspend at the start of the coroutine
        std::suspend_never initial_suspend() const { return {}; }

        // Never suspend at the end of the coroutine (thanks to this, the coroutine will clean up
        // after itself)
        std::suspend_never final_suspend() noexcept;

        void unhandled_exception() const { std::abort(); }
        void return_void() const {}
    };

    // MEMBERS
    VlPromise* m_promisep;  // The promise created for this coroutine

public:
    // TYPES
    using promise_type = VlPromise;  // promise_type has to be public

    // CONSTRUCTORS
    // Construct
    // cppcheck-suppress noExplicitConstructor
    VlCoroutine(VlPromise* promisep)
        : m_promisep{promisep} {
        m_promisep->m_corop = this;
    }
    // Move. Update the pointers each time the return object is moved
    // cppcheck-suppress noExplicitConstructor
    VlCoroutine(VlCoroutine&& other)
        : m_promisep{std::exchange(other.m_promisep, nullptr)} {
        if (m_promisep) m_promisep->m_corop = this;
    }
    ~VlCoroutine() {
        // Indicate to the promise that the return object is gone
        if (m_promisep) m_promisep->m_corop = nullptr;
    }

    // METHODS
    // Suspend the awaiter if the coroutine is suspended (the promise exists)
    bool await_ready() const noexcept { return !m_promisep; }
    // Set the awaiting coroutine as the continuation of the current coroutine
    void await_suspend(std::coroutine_handle<> coro) { m_promisep->m_continuation = coro; }
    void await_resume() const noexcept {}
};

#endif  // Guard
