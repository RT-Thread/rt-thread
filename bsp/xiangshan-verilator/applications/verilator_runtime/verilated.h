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
/// \brief Verilated common header, include for all Verilated C files
///
/// This file is included automatically by Verilator at the top of all C++
/// files it generates.  It contains standard macros and classes required
/// by the Verilated code.
///
/// User wrapper code may need to include this to get appropriate
/// structures, however they would generally just include the
/// Verilated-model's header instead (which then includes this).
///
/// Those macro/function/variable starting or ending in _ are internal,
/// however many of the other function/macros here are also internal.
///
//*************************************************************************

#ifndef VERILATOR_VERILATED_H_
#define VERILATOR_VERILATED_H_
#define VERILATOR_VERILATED_H_INTERNAL_
#ifdef VERILATOR_INTERNAL_
// This file contains definition of VerilationMutex that should
// only be used by verilated code. Verilator itself should use
// mutex from V3Mutex.h. Make sure this file isn't included in
// verilator code.
#error "verilated.h should only be included in verilated code"
#endif

// clang-format off
#include "verilated_config.h"
#include "verilatedos.h"
#if VM_SC
# include "verilated_sc.h"  // Get SYSTEMC_VERSION and time declarations
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
// <iostream> avoided to reduce compile time
#include <atomic>
#include <mutex>
#include <thread>

// Allow user to specify their own include file
#ifdef VL_VERILATED_INCLUDE
// cppcheck-suppress preprocessorErrorDirective
# include VL_VERILATED_INCLUDE
#endif
// clang-format on

using namespace std::literals;  // "<std::string literal>"s; see SF.7 core guideline

//=============================================================================
// Switches

// clang-format off
#if VM_TRACE  // Verilator tracing requested
# define WAVES 1  // Set backward compatibility flag
#endif

// Version check
#if defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION < 20111121)
# warning "Verilator requires SystemC 2.3.* or newer."
#endif
// clang-format on

class VerilatedContext;
class VerilatedContextImp;
class VerilatedContextImpData;
class VerilatedCovContext;
class VerilatedEvalMsgQueue;
class VerilatedFst;
class VerilatedFstC;
class VerilatedFstSc;
class VerilatedScope;
class VerilatedScopeNameMap;
template <typename, typename>
class VerilatedTrace;
class VerilatedTraceBaseC;
class VerilatedTraceConfig;
class VerilatedVar;
class VerilatedVarNameMap;
class VerilatedVcd;
class VerilatedVcdC;
class VerilatedVcdSc;

//=========================================================================
// Basic types

// Type letters
// clang-format off
//    P                     // Packed data of bit type (C/S/I/Q/W)
using CData = uint8_t;    ///< Data representing 'bit' of 1-8 packed bits
using SData = uint16_t;   ///< Data representing 'bit' of 9-16 packed bits
using IData = uint32_t;   ///< Data representing 'bit' of 17-32 packed bits
using QData = uint64_t;   ///< Data representing 'bit' of 33-64 packed bits
using EData = uint32_t;   ///< Data representing one element of WData array
using WData = EData;        ///< Data representing >64 packed bits (used as pointer)
//    F     = float;        // No typedef needed; Verilator uses float
//    D     = double;       // No typedef needed; Verilator uses double
//    N     = std::string;  // No typedef needed; Verilator uses string
//    U     = VlUnpacked;
//    R     = VlQueue;
// clang-format on

using WDataInP = const WData*;  ///< 'bit' of >64 packed bits as array input to a function
using WDataOutP = WData*;  ///< 'bit' of >64 packed bits as array output from a function

enum VerilatedVarType : uint8_t {
    VLVT_UNKNOWN = 0,
    VLVT_PTR,  // Pointer to something
    VLVT_UINT8,  // AKA CData
    VLVT_UINT16,  // AKA SData
    VLVT_UINT32,  // AKA IData
    VLVT_UINT64,  // AKA QData
    VLVT_WDATA,  // AKA WData
    VLVT_STRING,  // C++ string
    VLVT_REAL  // AKA double
};

enum VerilatedVarFlags {
    VLVD_0 = 0,  // None
    VLVD_IN = 1,  // == vpiInput
    VLVD_OUT = 2,  // == vpiOutput
    VLVD_INOUT = 3,  // == vpiInOut
    VLVD_NODIR = 5,  // == vpiNoDirection
    VLVF_MASK_DIR = 7,  // Bit mask for above directions
    // Flags
    VLVF_PUB_RD = (1 << 8),  // Public readable
    VLVF_PUB_RW = (1 << 9),  // Public writable
    VLVF_DPI_CLAY = (1 << 10),  // DPI compatible C standard layout
    VLVF_CONTINUOUSLY = (1 << 11),  // Is continously assigned
    VLVF_FORCEABLE = (1 << 12),  // Forceable
    VLVF_SIGNED = (1 << 13),  // Signed integer
    VLVF_BITVAR = (1 << 14)  // Four state bit (vs two state logic)
};

// IEEE 1800-2023 Table 20-6
enum class VerilatedAssertType : uint8_t {
    ASSERT_TYPE_CONCURRENT = (1 << 0),
    ASSERT_TYPE_SIMPLE_IMMEDIATE = (1 << 1),
    ASSERT_TYPE_OBSERVED_DEFERRED_IMMEDIATE = (1 << 2),
    ASSERT_TYPE_FINAL_DEFERRED_IMMEDIATE = (1 << 3),
    ASSERT_TYPE_EXPECT = (1 << 4),
    ASSERT_TYPE_UNIQUE = (1 << 5),
    ASSERT_TYPE_UNIQUE0 = (1 << 6),
    ASSERT_TYPE_PRIORITY = (1 << 7),
};

// IEEE 1800-2023 Table 20-7
enum class VerilatedAssertDirectiveType : uint8_t {
    DIRECTIVE_TYPE_ASSERT = (1 << 0),
    DIRECTIVE_TYPE_COVER = (1 << 1),
    DIRECTIVE_TYPE_ASSUME = (1 << 2),
};
using VerilatedAssertType_t = std::underlying_type<VerilatedAssertType>::type;
using VerilatedAssertDirectiveType_t = std::underlying_type<VerilatedAssertDirectiveType>::type;

// Type trait: whether T is a user-defined custom struct
template <typename>
struct VlIsCustomStruct : public std::false_type {};

// Type trait: used to detect if array element is a custom struct (e.g. for struct arrays)
template <typename T>
struct VlContainsCustomStruct : VlIsCustomStruct<T> {};

//=========================================================================
// Mutex and threading support

// Return current thread ID (or 0), not super fast, cache if needed
extern uint32_t VL_THREAD_ID() VL_MT_SAFE;

#ifndef VL_LOCK_SPINS
#define VL_LOCK_SPINS 50000  /// Number of times to spin for a mutex before yielding
#endif

/// Mutex, wrapped to allow -fthread_safety checks
class VL_CAPABILITY("mutex") VerilatedMutex final {
private:
    std::mutex m_mutex;  // Mutex

public:
    /// Construct mutex (without locking it)
    VerilatedMutex() = default;
    ~VerilatedMutex() = default;
    VL_UNCOPYABLE(VerilatedMutex);
    const VerilatedMutex& operator!() const { return *this; }  // For -fthread_safety
    /// Acquire/lock mutex
    void lock() VL_ACQUIRE() VL_MT_SAFE {
        // Try to acquire the lock by spinning.  If the wait is short,
        // avoids a trap to the OS plus OS scheduler overhead.
        if (VL_LIKELY(try_lock())) return;  // Short circuit loop
        for (int i = 0; i < VL_LOCK_SPINS; ++i) {
            if (VL_LIKELY(try_lock())) return;
            VL_CPU_RELAX();
        }
        // Spinning hasn't worked, pay the cost of blocking.
        m_mutex.lock();
    }
    /// Release/unlock mutex
    void unlock() VL_RELEASE() VL_MT_SAFE { m_mutex.unlock(); }
    /// Try to acquire mutex.  Returns true on success, and false on failure.
    bool try_lock() VL_TRY_ACQUIRE(true) VL_MT_SAFE { return m_mutex.try_lock(); }
};

/// Lock guard for mutex (ala std::unique_lock), wrapped to allow -fthread_safety checks
class VL_SCOPED_CAPABILITY VerilatedLockGuard final {
    VL_UNCOPYABLE(VerilatedLockGuard);

private:
    VerilatedMutex& m_mutexr;

public:
    /// Construct and hold given mutex lock until destruction or unlock()
    explicit VerilatedLockGuard(VerilatedMutex& mutexr) VL_ACQUIRE(mutexr) VL_MT_SAFE
        : m_mutexr(mutexr) {  // Need () or GCC 4.8 false warning
        mutexr.lock();
    }
    /// Destruct and unlock the mutex
    ~VerilatedLockGuard() VL_RELEASE() { m_mutexr.unlock(); }
};

// Internals: Remember the calling thread at construction time, and make
// sure later calls use same thread

class VerilatedAssertOneThread final {
    // MEMBERS
#ifdef VL_DEBUG
    uint32_t m_threadid;  // Thread that is legal
public:
    // CONSTRUCTORS
    // The constructor establishes the thread id for all later calls.
    // If necessary, a different class could be made that inits it otherwise.
    VerilatedAssertOneThread()
        : m_threadid{VL_THREAD_ID()} {}
    ~VerilatedAssertOneThread() { check(); }
    // METHODS
    // Check that the current thread ID is the same as the construction thread ID
    void check() VL_MT_UNSAFE_ONE {
        if (VL_UNCOVERABLE(m_threadid != VL_THREAD_ID())) {
            if (m_threadid == 0) {
                m_threadid = VL_THREAD_ID();
            } else {
                fatal_different();  // LCOV_EXCL_LINE
            }
        }
    }
    static void fatal_different() VL_MT_SAFE;
#else  // !VL_DEBUG
public:
    void check() {}
#endif
};

//=========================================================================
/// Base class of a Verilator generated (Verilated) model.
///
/// VerilatedModel is a base class of the user facing primary class generated
/// by Verilator.

class VerilatedModel VL_NOT_FINAL {
    VL_UNCOPYABLE(VerilatedModel);

    VerilatedContext& m_context;  // The VerilatedContext this model is instantiated under

protected:
    explicit VerilatedModel(VerilatedContext& context);
    virtual ~VerilatedModel() = default;

public:
    /// Returns the VerilatedContext this model is instantiated under
    /// Used to get to e.g. simulation time via contextp()->time()
    VerilatedContext* contextp() const VL_MT_SAFE { return &m_context; }
    /// Returns the hierarchical name of this module instance.
    virtual const char* hierName() const = 0;
    /// Returns the name of this model (the name of the generated model class).
    virtual const char* modelName() const = 0;
    /// Returns the thread level parallelism, this model was Verilated with. Always 1 or higher.
    virtual unsigned threads() const = 0;

private:
    // The following are for use by Verilator internals only
    template <typename, typename>
    friend class VerilatedTrace;
    // Run-time trace configuration requested by this model
    virtual std::unique_ptr<VerilatedTraceConfig> traceConfig() const;
};

//=========================================================================
// Functions overridable by user defines
// (Internals however must use VL_PRINTF_MT, which calls these.)

// clang-format off
#ifndef VL_PRINTF
# define VL_PRINTF printf  ///< Print ala printf, called from main thread; redefine if desired
#endif
#ifndef VL_VPRINTF
# define VL_VPRINTF vprintf  ///< Print ala vprintf, called from main thread; redefine if desired
#endif
// clang-format on

//===========================================================================
// Internal: Base class to allow virtual destruction

class VerilatedVirtualBase VL_NOT_FINAL {
public:
    VerilatedVirtualBase() = default;
    virtual ~VerilatedVirtualBase() = default;
};

//===========================================================================
/// Verilator simulation context
///
/// The VerilatedContext contains the information common across all models
/// that are interconnected, for example this contains the simulation time
/// and if $finish was executed.
///
/// VerilatedContexts maybe created by the user wrapper code and passed
/// when a model is created.  If this is not done, then Verilator will use
/// the Verilated::defaultContextp()'s global context.

class VerilatedContext VL_NOT_FINAL {
    friend class VerilatedContextImp;

private:
    // MEMBERS
    // Numer of assertion directive type members. Then each of them will represented as 1-bit in a
    // mask.
    static constexpr size_t ASSERT_DIRECTIVE_TYPE_MASK_WIDTH = 3;
    // Specifies how many groups of directive type bit groups there are based on a number of
    // assertion types.
    // Note: we add one bit to store information whether Verilator's internal
    // directive types are enabled, for example `violation if`s.
    static constexpr size_t ASSERT_ON_WIDTH
        = ASSERT_DIRECTIVE_TYPE_MASK_WIDTH * std::numeric_limits<VerilatedAssertType_t>::digits
          + 1;

protected:
    // TYPES
    using traceBaseModelCb_t
        = std::function<void(VerilatedTraceBaseC*, int, int)>;  // Type of traceBaseModel callbacks

    // MEMBERS
    // Slow path variables
    mutable VerilatedMutex m_mutex;  // Mutex for most s_s/s_ns members

    struct Serialized final {  // All these members serialized/deserialized
        // No std::strings or pointers or will serialize badly!
        // Fast path
        uint64_t m_time = 0;  // Current $time (unscaled), 0=at zero, or legacy
        std::atomic<uint32_t> m_assertOn{
            std::numeric_limits<uint32_t>::max()};  // Enabled assertions,
                                                    // for each VerilatedAssertType we store
                                                    // 3-bits, one for each directive type. Last
                                                    // bit guards internal directive types.
        bool m_calcUnusedSigs = false;  // Waves file on, need all signals calculated
        bool m_fatalOnError = true;  // Fatal on $stop/non-fatal error
        bool m_fatalOnVpiError = true;  // Fatal on vpi error/unsupported
        bool m_gotError = false;  // A $finish statement executed
        bool m_gotFinish = false;  // A $finish or $stop statement executed
        bool m_quiet = false;  // Quiet, no summary report
        // Slow path
        int8_t m_timeunit;  // Time unit as 0..15
        int8_t m_timeprecision;  // Time precision as 0..15
        int m_errorCount = 0;  // Number of errors
        int m_errorLimit = 1;  // Stop on error number
        int m_randReset = 0;  // Random reset: 0=all 0s, 1=all 1s, 2=random
        int m_randSeed = 0;  // Random seed: 0=random
        enum { UNITS_NONE = 99 };  // Default based on precision
        int m_timeFormatUnits = UNITS_NONE;  // $timeformat units
        int m_timeFormatPrecision = 0;  // $timeformat number of decimal places
        int m_timeFormatWidth = 20;  // $timeformat character width
        // CONSTRUCTORS
        Serialized();
        ~Serialized() = default;
    } m_s;

    mutable VerilatedMutex m_timeDumpMutex;  // Protect misc slow strings
    std::string m_timeFormatSuffix VL_GUARDED_BY(m_timeDumpMutex);  // $timeformat printf format
    std::string m_dumpfile VL_GUARDED_BY(m_timeDumpMutex);  // $dumpfile setting

    struct NonSerialized final {  // Non-serialized information
        // These are reloaded from on command-line settings, so do not need to persist
        // Fast path
        uint64_t m_profExecStart = 1;  // +prof+exec+start time
        uint32_t m_profExecWindow = 2;  // +prof+exec+window size
        // Slow path
        std::string m_coverageFilename;  // +coverage+file filename
        std::string m_profExecFilename;  // +prof+exec+file filename
        std::string m_profVltFilename;  // +prof+vlt filename
        std::string m_solverProgram;  // SMT solver program
        bool m_warnUnsatConstr = true;  // Warn on unsatisfied constraints
        VlOs::DeltaCpuTime m_cpuTimeStart{false};  // CPU time, starts when create first model
        VlOs::DeltaWallTime m_wallTimeStart{false};  // Wall time, starts when create first model
        std::vector<traceBaseModelCb_t> m_traceBaseModelCbs;  // Callbacks to traceRegisterModel
    } m_ns;

    mutable VerilatedMutex m_argMutex;  // Protect m_argVec, m_argVecLoaded
    // no need to be save-restored (serialized) the
    // assumption is that the restore is allowed to pass different arguments
    struct NonSerializedCommandArgs final {
        // Medium speed
        std::vector<std::string> m_argVec;  // Argument list
        bool m_argVecLoaded = false;  // Ever loaded argument list
    } m_args VL_GUARDED_BY(m_argMutex);

    // Implementation details
    const std::unique_ptr<VerilatedContextImpData> m_impdatap;
    // Number of threads to use for simulation (size of m_threadPool + 1 for main thread)
    unsigned m_threads = VlOs::getProcessDefaultParallelism();
    // Use numa automatic CPU-to-thread assignment
    bool m_useNumaAssign = false;
    // Number of threads in added models
    unsigned m_threadsInModels = 0;
    // The thread pool shared by all models added to this context
    std::unique_ptr<VerilatedVirtualBase> m_threadPool;
    // The execution profiler shared by all models added to this context
    std::unique_ptr<VerilatedVirtualBase> m_executionProfiler;
    // Coverage access
    std::unique_ptr<VerilatedVirtualBase> m_coveragep;  // Pointer for coveragep()

    // File I/O
    // Not serialized
    mutable VerilatedMutex m_fdMutex;  // Protect m_fdps, m_fdFree
    std::vector<FILE*> m_fdps VL_GUARDED_BY(m_fdMutex);  // File descriptors
    // List of free descriptors (SLOW - FOPEN/CLOSE only)
    std::vector<IData> m_fdFree VL_GUARDED_BY(m_fdMutex);
    // List of free descriptors in the MCT region [4, 32)
    std::vector<IData> m_fdFreeMct VL_GUARDED_BY(m_fdMutex);

    // Magic to check for bad construction
    static constexpr uint64_t MAGIC = 0xC35F9A6E5298EE6EULL;  // SHA256 "VerilatedContext"
    uint64_t m_magic = MAGIC;

private:
    // CONSTRUCTORS
    VL_UNCOPYABLE(VerilatedContext);

public:
    /// Construct context. Also sets Verilated::threadContextp to the created context.
    VerilatedContext();
    ~VerilatedContext();

    // METHODS - User called

    /// Return if assertions enabled
    bool assertOn() const VL_MT_SAFE;
    /// Enable all assertion types
    void assertOn(bool flag) VL_MT_SAFE;
    /// Get enabled status for given assertion types
    bool assertOnGet(VerilatedAssertType_t type,
                     VerilatedAssertDirectiveType_t directive) const VL_MT_SAFE;
    /// Set enabled status for given assertion types
    void assertOnSet(VerilatedAssertType_t types,
                     VerilatedAssertDirectiveType_t directives) VL_MT_SAFE;
    /// Clear enabled status for given assertion types
    void assertOnClear(VerilatedAssertType_t types,
                       VerilatedAssertDirectiveType_t directives) VL_MT_SAFE;
    /// Return if calculating of unused signals (for traces)
    bool calcUnusedSigs() const VL_MT_SAFE { return m_s.m_calcUnusedSigs; }
    /// Enable calculation of unused signals (for traces)
    void calcUnusedSigs(bool flag) VL_MT_SAFE;
    /// Record command-line arguments, for retrieval by $test$plusargs/$value$plusargs,
    /// and for parsing +verilator+ run-time arguments.
    /// This should be called before the first model is created.
    void commandArgs(int argc, const char** argv) VL_MT_SAFE_EXCLUDES(m_argMutex);
    void commandArgs(int argc, char** argv) VL_MT_SAFE {
        commandArgs(argc, const_cast<const char**>(argv));
    }
    /// Add a command-line argument to existing arguments
    void commandArgsAdd(int argc, const char** argv) VL_MT_SAFE_EXCLUDES(m_argMutex);
    /// Match plusargs with a given prefix. Returns static char* valid only for a single call
    const char* commandArgsPlusMatch(const char* prefixp) VL_MT_SAFE_EXCLUDES(m_argMutex);
    /// Return VerilatedCovContext, allocate if needed
    /// Note if get unresolved reference then likely forgot to link verilated_cov.cpp
    VerilatedCovContext* coveragep() VL_MT_SAFE;
    /// Return debug level
    static inline int debug() VL_MT_SAFE;  /// Set debug level
    /// Debug is currently global, but for forward compatibility have a per-context method
    static inline void debug(int val) VL_MT_SAFE;
    /// Return current number of errors/assertions
    int errorCount() const VL_MT_SAFE { return m_s.m_errorCount; }
    /// Set current number of errors/assertions
    void errorCount(int val) VL_MT_SAFE;
    /// Increment current number of errors/assertions
    void errorCountInc() VL_MT_SAFE;
    /// Return number of errors/assertions before stop
    int errorLimit() const VL_MT_SAFE { return m_s.m_errorLimit; }
    /// Set number of errors/assertions before stop
    void errorLimit(int val) VL_MT_SAFE;
    /// Return if to throw fatal error on $stop/non-fatal
    bool fatalOnError() const VL_MT_SAFE { return m_s.m_fatalOnError; }
    /// Set to throw fatal error on $stop/non-fatal error
    void fatalOnError(bool flag) VL_MT_SAFE;
    /// Return if to throw fatal error on VPI errors
    bool fatalOnVpiError() const VL_MT_SAFE { return m_s.m_fatalOnVpiError; }
    /// Set to throw fatal error on VPI errors
    void fatalOnVpiError(bool flag) VL_MT_SAFE;
    /// Return if got a $stop or non-fatal error
    bool gotError() const VL_MT_SAFE { return m_s.m_gotError; }
    /// Set if got a $stop or non-fatal error
    void gotError(bool flag) VL_MT_SAFE;
    /// Return if got a $finish or $stop/error
    bool gotFinish() const VL_MT_SAFE { return m_s.m_gotFinish; }
    /// Set if got a $finish or $stop/error
    void gotFinish(bool flag) VL_MT_SAFE;
    /// Return if quiet enabled
    bool quiet() const VL_MT_SAFE { return m_s.m_quiet; }
    /// Enable quiet (also prevents need for OS calls to get CPU time)
    void quiet(bool flag) VL_MT_SAFE;
    /// Return randReset value
    int randReset() VL_MT_SAFE { return m_s.m_randReset; }
    /// Select initial value of otherwise uninitialized signals.
    /// 0 = Set to zeros
    /// 1 = Set all bits to one
    /// 2 = Randomize all bits
    void randReset(int val) VL_MT_SAFE;
    /// Return default random seed
    int randSeed() const VL_MT_SAFE { return m_s.m_randSeed; }
    /// Set default random seed, 0 = seed it automatically
    void randSeed(int val) VL_MT_SAFE;

    /// Return statistic: CPU time delta from model created until now
    double statCpuTimeSinceStart() const VL_MT_SAFE_EXCLUDES(m_mutex);
    /// Return statistic: Wall time delta from model created until now
    double statWallTimeSinceStart() const VL_MT_SAFE_EXCLUDES(m_mutex);
    /// Print statistics summary (if not quiet)
    void statsPrintSummary() VL_MT_UNSAFE;

    // Time handling
    /// Returns current simulation time in units of timeprecision().
    ///
    /// How Verilator runtime gets the current simulation time:
    ///
    /// * If using SystemC, time comes from the SystemC kernel-defined
    /// sc_time_stamp64(). User's wrapper must not call
    /// SimulationContext::time(value) nor timeInc(value).
    ///
    /// * Else, if SimulationContext::time(value) or
    /// SimulationContext::timeInc(value) is ever called with non-zero,
    /// then time will come via the context.  This allows multiple contexts
    /// to exist and have different simulation times. This must not be used
    /// with SystemC.  Note Verilated::time(value) and
    /// Verilated::timeInc(value) call into SimulationContext::time and
    /// timeInc, operating on the thread's context.
    ///
    /// * Else, if VL_TIME_STAMP64 is defined, time comes from the legacy
    /// 'uint64_t vl_time_stamp64()' which must a function be defined by
    /// the user's wrapper.
    ///
    /// * Else, time comes from the legacy 'double sc_time_stamp()' which
    /// must be a function defined by the user's wrapper.
    inline uint64_t time() const VL_MT_SAFE;
    /// Set current simulation time. See time() for side effect details
    void time(uint64_t value) VL_MT_SAFE { m_s.m_time = value; }
    /// Advance current simulation time. See time() for side effect details
    void timeInc(uint64_t add) VL_MT_UNSAFE { m_s.m_time += add; }
    /// Return time units as power-of-ten
    int timeunit() const VL_MT_SAFE { return -m_s.m_timeunit; }
    /// Set time units as power-of-ten
    void timeunit(int value) VL_MT_SAFE;
    /// Return time units as IEEE-standard text
    const char* timeunitString() const VL_MT_SAFE;
    /// Get time precision as power-of-ten
    int timeprecision() const VL_MT_SAFE { return -m_s.m_timeprecision; }
    /// Return time precision as power-of-ten
    inline void timeprecision(int value) VL_MT_SAFE;
    /// Get time precision as IEEE-standard text
    const char* timeprecisionString() const VL_MT_SAFE;

    /// Get number of threads used for simulation (including the main thread)
    unsigned threads() const { return m_threads; }
    /// Get number of threads in added models (for statistical use only)
    unsigned threadsInModels() const { return m_threadsInModels; }
    /// Set number of threads used for simulation (including the main thread)
    /// Can only be called before the thread pool is created (before first model is added).
    void threads(unsigned n);

    /// Use numa automatic CPU-to-thread assignment.
    bool useNumaAssign() const VL_MT_SAFE { return m_useNumaAssign; }
    /// Set numa assignment of threads to cores
    /// Defaults false; set true automatically when threads() called;
    /// call this to override back to false if numa assignment not wanted.
    void useNumaAssign(bool flag);

    /// Trace signals in models within the context; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0);
    /// Allow traces to at some point be enabled (disables some optimizations)
    void traceEverOn(bool flag) VL_MT_SAFE {
        if (flag) calcUnusedSigs(true);
    }

    /// For debugging, print much of the Verilator internal state.
    /// The output of this function may change in future
    /// releases - contact the authors before production use.
    void internalsDump() const VL_MT_SAFE;

    /// For debugging, print text list of all scope names with
    /// dpiImport/Export context.  This function may change in future
    /// releases - contact the authors before production use.
    void scopesDump() const VL_MT_SAFE;

    // METHODS - public but for internal use only

    // Internal: access to implementation class
    VerilatedContextImp* impp() VL_MT_SAFE { return reinterpret_cast<VerilatedContextImp*>(this); }
    const VerilatedContextImp* impp() const VL_MT_SAFE {
        return reinterpret_cast<const VerilatedContextImp*>(this);
    }

    // Internal: Model and thread setup
    void addModel(const VerilatedModel* modelp);
    VerilatedVirtualBase* threadPoolp();
    void prepareClone();
    VerilatedVirtualBase* threadPoolpOnClone();
    VerilatedVirtualBase*
    enableExecutionProfiler(VerilatedVirtualBase* (*construct)(VerilatedContext&));

    // Internal: coverage
    std::string coverageFilename() const VL_MT_SAFE;
    void coverageFilename(const std::string& flag) VL_MT_SAFE;

    // Internal: $dumpfile
    std::string dumpfile() const VL_MT_SAFE_EXCLUDES(m_timeDumpMutex);
    void dumpfile(const std::string& flag) VL_MT_SAFE_EXCLUDES(m_timeDumpMutex);
    std::string dumpfileCheck() const VL_MT_SAFE_EXCLUDES(m_timeDumpMutex);

    // Internal: --prof-exec related settings
    uint64_t profExecStart() const VL_MT_SAFE { return m_ns.m_profExecStart; }
    void profExecStart(uint64_t flag) VL_MT_SAFE;
    uint32_t profExecWindow() const VL_MT_SAFE { return m_ns.m_profExecWindow; }
    void profExecWindow(uint64_t flag) VL_MT_SAFE;
    std::string profExecFilename() const VL_MT_SAFE;
    void profExecFilename(const std::string& flag) VL_MT_SAFE;
    std::string profVltFilename() const VL_MT_SAFE;
    void profVltFilename(const std::string& flag) VL_MT_SAFE;

    // Internal: SMT solver program
    std::string solverProgram() const VL_MT_SAFE;
    void solverProgram(const std::string& flag) VL_MT_SAFE;
    // Internal: Control display of unsatisfied constraints
    bool warnUnsatConstr() const VL_MT_SAFE { return m_ns.m_warnUnsatConstr; }
    void warnUnsatConstr(bool flag) VL_MT_SAFE { m_ns.m_warnUnsatConstr = flag; }

    // Internal: Find scope
    const VerilatedScope* scopeFind(const char* namep) const VL_MT_SAFE;
    const VerilatedScopeNameMap* scopeNameMap() VL_MT_SAFE;

    // Internal: Serialization setup
    static constexpr size_t serialized1Size() VL_PURE { return sizeof(m_s); }
    void* serialized1Ptr() VL_MT_UNSAFE { return &m_s; }

    // Internal: trace registration
    void traceBaseModelCbAdd(traceBaseModelCb_t cb) VL_MT_SAFE;

    // Internal: Check magic number
    static void checkMagic(const VerilatedContext* contextp);
    void selfTestClearMagic() { m_magic = 0x2; }
};

//===========================================================================
// Verilator symbol table base class
// Used for internal VPI implementation, and introspection into scopes

class VerilatedSyms VL_NOT_FINAL {
public:  // But for internal use only
    // MEMBERS
    // Keep first so is at zero offset for fastest code
    VerilatedContext* const _vm_contextp__;  // Context for current model
    VerilatedEvalMsgQueue* __Vm_evalMsgQp;
    explicit VerilatedSyms(VerilatedContext* contextp);  // Pass null for default context
    ~VerilatedSyms();
    VL_UNCOPYABLE(VerilatedSyms);

    virtual const char* name() const = 0;
};

//===========================================================================
// Verilator scope information class
// Used for internal VPI implementation, and introspection into scopes

class VerilatedScope final {
public:
    enum Type : uint8_t {
        SCOPE_MODULE,
        SCOPE_OTHER,
        SCOPE_PACKAGE
    };  // Type of a scope, currently only module and package are interesting
private:
    // Fastpath:
    VerilatedSyms* const m_symsp;  // Symbol table
    void** m_callbacksp = nullptr;  // Callback table pointer (Fastpath)
    int m_funcnumMax = 0;  // Maximum function number stored (Fastpath)
    // 4 bytes padding (on -m64), for rent.
    VerilatedVarNameMap* m_varsp = nullptr;  // Variable map
    const char* const m_namep;  // Scope name (Slowpath)
    const char* const m_identifierp;  // Identifier of scope (with escapes removed)
    const char* const m_defnamep;  // Definition name (SCOPE_MODULE only)
    const int8_t m_timeunit;  // Timeunit in negative power-of-10
    const Type m_type;  // Type of the scope

public:  // But internals only - called from verilated modules, VerilatedSyms
    VerilatedScope(VerilatedSyms* symsp, const char* suffixp, const char* identifier,
                   const char* defnamep, int8_t timeunit, Type type);
    ~VerilatedScope();

    void exportInsert(int finalize, const char* namep, void* cb) VL_MT_UNSAFE;
    void varInsert(const char* namep, void* datap, bool isParam, VerilatedVarType vltype,
                   int vlflags, int udims, int pdims, ...) VL_MT_UNSAFE;
    // ACCESSORS
    const char* name() const VL_MT_SAFE_POSTINIT { return m_namep; }
    const char* identifier() const VL_MT_SAFE_POSTINIT { return m_identifierp; }
    const char* defname() const VL_MT_SAFE_POSTINIT { return m_defnamep; }
    int8_t timeunit() const VL_MT_SAFE_POSTINIT { return m_timeunit; }
    VerilatedSyms* symsp() const VL_MT_SAFE_POSTINIT { return m_symsp; }
    VerilatedVar* varFind(const char* namep) const VL_MT_SAFE_POSTINIT;
    VerilatedVarNameMap* varsp() const VL_MT_SAFE_POSTINIT { return m_varsp; }
    void scopeDump() const;
    void* exportFindError(int funcnum) const VL_MT_SAFE;
    static void* exportFindNullError(int funcnum) VL_MT_SAFE;
    static void* exportFind(const VerilatedScope* scopep, int funcnum) VL_MT_SAFE;
    Type type() const { return m_type; }
};

class VerilatedHierarchy final {
public:
    static void add(const VerilatedScope* fromp, const VerilatedScope* top);
    static void remove(const VerilatedScope* fromp, const VerilatedScope* top);
    static void clear();
};

//===========================================================================
/// Verilator global static information class

class Verilated final {
    // MEMBERS

    // Internal Note: There should be no Serialized state in Verilated::,
    // instead serialized state should all be in VerilatedContext:: as by
    // definition it needs to vary per-simulation

    // Internal note: Globals may multi-construct, see verilated.cpp top.

    // Debug is reloaded from on command-line settings, so do not need to persist
    static int s_debug;  // See accessors... only when VL_DEBUG set

    static VerilatedContext* s_lastContextp;  // Last context constructed/attached

    // Not covered by mutex, as per-thread
    static thread_local struct ThreadLocal {
        // No non-POD objects here due to this:
        // Internal note: Globals may multi-construct, see verilated.cpp top.

        // Fast path
        VerilatedContext* t_contextp = nullptr;  // Thread's context
        uint32_t t_mtaskId = 0;  // mtask# executing on this thread
        // Messages maybe pending on thread, needs end-of-eval calls
        uint32_t t_endOfEvalReqd = 0;
        const VerilatedScope* t_dpiScopep = nullptr;  // DPI context scope
        const char* t_dpiFilename = nullptr;  // DPI context filename
        int t_dpiLineno = 0;  // DPI context line number

        ThreadLocal() = default;
        ~ThreadLocal() = default;
    } t_s;

    friend struct VerilatedInitializer;

    // CONSTRUCTORS
    VL_UNCOPYABLE(Verilated);

public:
    // METHODS - User called

#ifdef VL_DEBUG
    /// Return debug level
    /// When multithreaded this may not immediately react to another thread
    /// changing the level (no mutex)
    static int debug() VL_MT_SAFE { return s_debug; }
#else
    /// Return constant 0 debug level, so C++'s optimizer rips up
    static constexpr int debug() VL_PURE { return 0; }
#endif
    /// Enable debug of internal verilated code
    static void debug(int level) VL_MT_SAFE;

    /// Set the last VerilatedContext accessed
    /// Generally threadContextp(value) should be called instead
    static void lastContextp(VerilatedContext* contextp) VL_MT_SAFE { s_lastContextp = contextp; }
    /// Return the last VerilatedContext accessed
    /// Generally threadContextp() should be called instead
    static VerilatedContext* lastContextp() VL_MT_SAFE {
        if (!s_lastContextp) lastContextp(defaultContextp());
        return s_lastContextp;
    }
    /// Set the VerilatedContext used by the current thread

    /// If using multiple contexts, and threads are created by the user's
    /// wrapper (not Verilator itself) then this must be called to set the
    /// context that applies to each thread
    static void threadContextp(VerilatedContext* contextp) VL_MT_SAFE {
        t_s.t_contextp = contextp;
        lastContextp(contextp);
    }
    /// Return the VerilatedContext for the current thread
    static VerilatedContext* threadContextp() VL_MT_SAFE {
        if (VL_UNLIKELY(!t_s.t_contextp)) t_s.t_contextp = lastContextp();
        return t_s.t_contextp;
    }
    /// Return the global VerilatedContext, used if none created by user
    static VerilatedContext* defaultContextp() VL_MT_SAFE {
        static VerilatedContext s_s;
        return &s_s;
    }

#ifndef VL_NO_LEGACY
    /// Return VerilatedContext::assertOn() using current thread's VerilatedContext
    static bool assertOn() VL_MT_SAFE { return Verilated::threadContextp()->assertOn(); }
    /// Call VerilatedContext::assertOn using current thread's VerilatedContext
    static void assertOn(bool flag) VL_MT_SAFE { Verilated::threadContextp()->assertOn(flag); }
    /// Return VerilatedContext::calcUnusedSigs using current thread's VerilatedContext
    static bool calcUnusedSigs() VL_MT_SAFE {
        return Verilated::threadContextp()->calcUnusedSigs();
    }
    /// Call VerilatedContext::calcUnusedSigs using current thread's VerilatedContext
    static void calcUnusedSigs(bool flag) VL_MT_SAFE {
        Verilated::threadContextp()->calcUnusedSigs(flag);
    }
    /// Call VerilatedContext::commandArgs using current thread's VerilatedContext
    static void commandArgs(int argc, const char** argv) VL_MT_SAFE {
        Verilated::threadContextp()->commandArgs(argc, argv);
    }
    static void commandArgs(int argc, char** argv) VL_MT_SAFE {
        commandArgs(argc, const_cast<const char**>(argv));
    }
    /// Call VerilatedContext::commandArgsAdd using current thread's VerilatedContext
    static void commandArgsAdd(int argc, const char** argv) {
        Verilated::threadContextp()->commandArgsAdd(argc, argv);
    }
    /// Return VerilatedContext::commandArgsPlusMatch using current thread's VerilatedContext
    static const char* commandArgsPlusMatch(const char* prefixp) VL_MT_SAFE {
        return Verilated::threadContextp()->commandArgsPlusMatch(prefixp);
    }
    /// Return VerilatedContext::errorLimit using current thread's VerilatedContext
    static int errorLimit() VL_MT_SAFE { return Verilated::threadContextp()->errorLimit(); }
    /// Call VerilatedContext::errorLimit using current thread's VerilatedContext
    static void errorLimit(int val) VL_MT_SAFE { Verilated::threadContextp()->errorLimit(val); }
    /// Return VerilatedContext::fatalOnError using current thread's VerilatedContext
    static bool fatalOnError() VL_MT_SAFE { return Verilated::threadContextp()->fatalOnError(); }
    /// Call VerilatedContext::fatalOnError using current thread's VerilatedContext
    static void fatalOnError(bool flag) VL_MT_SAFE {
        Verilated::threadContextp()->fatalOnError(flag);
    }
    /// Return VerilatedContext::fatalOnVpiError using current thread's VerilatedContext
    static bool fatalOnVpiError() VL_MT_SAFE {
        return Verilated::threadContextp()->fatalOnVpiError();
    }
    /// Call VerilatedContext::fatalOnVpiError using current thread's VerilatedContext
    static void fatalOnVpiError(bool flag) VL_MT_SAFE {
        Verilated::threadContextp()->fatalOnVpiError(flag);
    }
    /// Return VerilatedContext::gotError using current thread's VerilatedContext
    static bool gotError() VL_MT_SAFE { return Verilated::threadContextp()->gotError(); }
    /// Call VerilatedContext::gotError using current thread's VerilatedContext
    static void gotError(bool flag) VL_MT_SAFE { Verilated::threadContextp()->gotError(flag); }
    /// Return VerilatedContext::gotFinish using current thread's VerilatedContext
    static bool gotFinish() VL_MT_SAFE { return Verilated::threadContextp()->gotFinish(); }
    /// Call VerilatedContext::gotFinish using current thread's VerilatedContext
    static void gotFinish(bool flag) VL_MT_SAFE { Verilated::threadContextp()->gotFinish(flag); }
    /// Return VerilatedContext::randReset using current thread's VerilatedContext
    static int randReset() VL_MT_SAFE { return Verilated::threadContextp()->randReset(); }
    /// Call VerilatedContext::randReset using current thread's VerilatedContext
    static void randReset(int val) VL_MT_SAFE { Verilated::threadContextp()->randReset(val); }
    /// Return VerilatedContext::randSeed using current thread's VerilatedContext
    static int randSeed() VL_MT_SAFE { return Verilated::threadContextp()->randSeed(); }
    /// Call VerilatedContext::randSeed using current thread's VerilatedContext
    static void randSeed(int val) VL_MT_SAFE { Verilated::threadContextp()->randSeed(val); }
    /// Return VerilatedContext::time using current thread's VerilatedContext
    static uint64_t time() VL_MT_SAFE { return Verilated::threadContextp()->time(); }
    /// Call VerilatedContext::time using current thread's VerilatedContext
    static void time(uint64_t val) VL_MT_SAFE { Verilated::threadContextp()->time(val); }
    /// Call VerilatedContext::timeInc using current thread's VerilatedContext
    static void timeInc(uint64_t add) VL_MT_UNSAFE { Verilated::threadContextp()->timeInc(add); }
    // Deprecated
    static int timeunit() VL_MT_SAFE { return Verilated::threadContextp()->timeunit(); }
    static int timeprecision() VL_MT_SAFE { return Verilated::threadContextp()->timeprecision(); }
    /// Call VerilatedContext::tracesEverOn using current thread's VerilatedContext
    static void traceEverOn(bool flag) VL_MT_SAFE {
        Verilated::threadContextp()->traceEverOn(flag);
    }
#endif

    /// Callback typedef for addFlushCb, addExitCb
    using VoidPCb = void (*)(void*);
    /// Add callback to run on global flush
    static void addFlushCb(VoidPCb cb, void* datap) VL_MT_SAFE;
    /// Remove callback to run on global flush
    static void removeFlushCb(VoidPCb cb, void* datap) VL_MT_SAFE;
    /// Run flush callbacks registered with addFlushCb
    static void runFlushCallbacks() VL_MT_SAFE;
#ifndef VL_NO_LEGACY
    static void flushCall() VL_MT_SAFE { runFlushCallbacks(); }  // Deprecated
#endif
    /// Add callback to run prior to exit termination
    static void addExitCb(VoidPCb cb, void* datap) VL_MT_SAFE;
    /// Remove callback to run prior to exit termination
    static void removeExitCb(VoidPCb cb, void* datap) VL_MT_SAFE;
    /// Run exit callbacks registered with addExitCb
    static void runExitCallbacks() VL_MT_SAFE;

    /// Return product name for (at least) VPI
    static const char* productName() VL_PURE;
    /// Return product version for (at least) VPI
    static const char* productVersion() VL_PURE;

    /// Call OS to make a directory
    static void mkdir(const char* dirname) VL_MT_UNSAFE;

    /// When multithreaded, quiesce the model to prepare for trace/saves/coverage
    /// This may only be called when no locks are held.
    static void quiesce() VL_MT_SAFE;

#ifndef VL_NO_LEGACY
    /// For debugging, print much of the Verilator internal state.
    /// The output of this function may change in future
    /// releases - contact the authors before production use.
    static void internalsDump() VL_MT_SAFE { Verilated::threadContextp()->internalsDump(); }
    /// For debugging, print text list of all scope names with
    /// dpiImport/Export context.  This function may change in future
    /// releases - contact the authors before production use.
    static void scopesDump() VL_MT_SAFE { Verilated::threadContextp()->scopesDump(); }
    // Internal: Find scope
    static const VerilatedScope* scopeFind(const char* namep) VL_MT_SAFE {
        return Verilated::threadContextp()->scopeFind(namep);
    }
    static const VerilatedScopeNameMap* scopeNameMap() VL_MT_SAFE {
        return Verilated::threadContextp()->scopeNameMap();
    }
#endif

    // METHODS - INTERNAL USE ONLY (but public due to what uses it)
    // Internal: Create a new module name by concatenating two strings
    // Returns pointer to thread-local static data (overwritten on next call)
    static const char* catName(const char* n1, const char* n2,
                               const char* delimiter = ".") VL_MT_SAFE;

    // Internal: Throw signal assertion
    static void nullPointerError(const char* filename, int linenum) VL_ATTR_NORETURN VL_MT_SAFE;
    static void overWidthError(const char* signame) VL_ATTR_NORETURN VL_MT_SAFE;
    static void scTimePrecisionError(int sc_prec, int vl_prec) VL_ATTR_NORETURN VL_MT_SAFE;
    static void scTraceBeforeElaborationError() VL_ATTR_NORETURN VL_MT_SAFE;
    static void stackCheck(QData needSize) VL_MT_UNSAFE;

    // Internal: Get and set DPI context
    static const VerilatedScope* dpiScope() VL_MT_SAFE { return t_s.t_dpiScopep; }
    static void dpiScope(const VerilatedScope* scopep) VL_MT_SAFE { t_s.t_dpiScopep = scopep; }
    static void dpiContext(const VerilatedScope* scopep, const char* filenamep,
                           int lineno) VL_MT_SAFE {
        t_s.t_dpiScopep = scopep;
        t_s.t_dpiFilename = filenamep;
        t_s.t_dpiLineno = lineno;
    }
    static void dpiClearContext() VL_MT_SAFE { t_s.t_dpiScopep = nullptr; }
    static bool dpiInContext() VL_MT_SAFE { return t_s.t_dpiScopep != nullptr; }
    static const char* dpiFilenamep() VL_MT_SAFE { return t_s.t_dpiFilename; }
    static int dpiLineno() VL_MT_SAFE { return t_s.t_dpiLineno; }
    static int exportFuncNum(const char* namep) VL_MT_SAFE;

    // Internal: Set the mtaskId, called when an mtask starts
    // Per thread, so no need to be in VerilatedContext
    static uint32_t mtaskId() VL_MT_SAFE { return t_s.t_mtaskId; }
    static void mtaskId(uint32_t id) VL_MT_SAFE { t_s.t_mtaskId = id; }
    static void endOfEvalReqdInc() VL_MT_SAFE { ++t_s.t_endOfEvalReqd; }
    static void endOfEvalReqdDec() VL_MT_SAFE { --t_s.t_endOfEvalReqd; }

    // Internal: Called at end of each thread mtask, before finishing eval
    static void endOfThreadMTask(VerilatedEvalMsgQueue* evalMsgQp) VL_MT_SAFE {
        mtaskId(0);
        if (VL_UNLIKELY(t_s.t_endOfEvalReqd)) endOfThreadMTaskGuts(evalMsgQp);
    }
    // Internal: Called at end of eval loop
    static void endOfEval(VerilatedEvalMsgQueue* evalMsgQp) VL_MT_SAFE;

private:
    static void endOfThreadMTaskGuts(VerilatedEvalMsgQueue* evalMsgQp) VL_MT_SAFE;
};

void VerilatedContext::debug(int val) VL_MT_SAFE { Verilated::debug(val); }
int VerilatedContext::debug() VL_MT_SAFE { return Verilated::debug(); }

//=========================================================================
// Data Types

#include "verilated_types.h"

//=========================================================================
// Functions

#include "verilated_funcs.h"

//======================================================================

void VerilatedContext::timeprecision(int value) VL_MT_SAFE {
    if (value < 0) value = -value;  // Stored as 0..15
#if VM_SC
    int sc_prec = 99;
#endif
    {
        const VerilatedLockGuard lock{m_mutex};
        m_s.m_timeprecision = value;
#if VM_SC
        const sc_core::sc_time sc_res = sc_core::sc_get_time_resolution();
        double mult = 1.0;
        for (int i = 0; i < 16; i++) {
            if (sc_res == sc_core::sc_time(mult, sc_core::SC_FS)) {
                sc_prec = 15 - i;
                break;
            }
            mult *= 10.0;
        }
        // SC_AS, SC_ZS, SC_YS not supported as no Verilog equivalent; will error below
#endif
    }
#if VM_SC
    if (VL_UNLIKELY(value != sc_prec)) Verilated::scTimePrecisionError(sc_prec, value);
#endif
}

#undef VERILATOR_VERILATED_H_INTERNAL_
#endif  // Guard
