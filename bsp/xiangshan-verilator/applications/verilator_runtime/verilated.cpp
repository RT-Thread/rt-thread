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
//=========================================================================
///
/// \file
/// \brief Verilated general routine implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// (all code created from Verilator).
///
/// Verilator always adds this file to the Makefile for the linker.
///
/// Those macro/function/variable starting or ending in _ are internal,
/// however many of the other function/macros here are also internal.
///
//=========================================================================
// Internal note:
//
// verilated.o may exist both in --lib-create (incrementally linked .a/.so)
// and the main module.  Both refer the same instance of static
// variables/thread_local in verilated.o such as Verilated, or
// VerilatedImpData.  This is important to share that state, but the
// sharing may cause a double-free error when shutting down because the
// loader will insert a constructor/destructor at each reference to
// verilated.o, resulting in at runtime constructors/destructors being
// called multiple times.
//
// To avoid the trouble:
//   * Statics declared inside functions. The compiler will wrap
//     the construction in must-be-one-time checks.
//   * Or, use only C++20 constinit types. (TODO: Make a VL_CONSTINIT).
//   * Or, use types that are multi-constructor safe.
//   * Or, the static should be of a union, which will avoid compiler
//     construction, and appropriately check for duplicate construction.
//   * Or, code is not linked in protected library. e.g. the VPI
//     and DPI libraries are not needed there.
//=========================================================================

#define VERILATOR_VERILATED_CPP_

#include "verilated_config.h"
#include "verilatedos.h"

#include "verilated_imp.h"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <utility>

#include <sys/stat.h>  // mkdir

// clang-format off
#if defined(_WIN32) || defined(__MINGW32__)
# include <direct.h>  // mkdir
#endif
#ifdef __GLIBC__
# include <cxxabi.h>
# include <execinfo.h>
# define _VL_HAVE_STACKTRACE
#endif
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# include <sys/time.h>
# include <sys/resource.h>
# define _VL_HAVE_GETRLIMIT
#endif

#include "verilated_threads.h"
// clang-format on

#include "verilated_trace.h"

#ifdef VM_SOLVER_DEFAULT
#define VL_SOLVER_DEFAULT VM_SOLVER_DEFAULT
#else
#define VL_SOLVER_DEFAULT "z3 --in"
#endif

// Max characters in static char string for VL_VALUE_STRING
constexpr unsigned VL_VALUE_STRING_MAX_WIDTH = 8192;

//===========================================================================
// Static sanity checks

static_assert(sizeof(uint8_t) == 1, "uint8_t is missized");
static_assert(sizeof(uint16_t) == 2, "uint8_t is missized");
static_assert(sizeof(uint32_t) == 4, "uint8_t is missized");
static_assert(sizeof(uint64_t) == 8, "uint8_t is missized");

//===========================================================================
// Global variables
// Internal note: Globals may multi-construct, see verilated.cpp top.

// Fast path, keep together
int Verilated::s_debug = 0;
VerilatedContext* Verilated::s_lastContextp = nullptr;

// Keep below together in one cache line
// Internal note: Globals may multi-construct, see verilated.cpp top.
thread_local Verilated::ThreadLocal Verilated::t_s;

//===========================================================================
// Warning print helper

void vl_print_warn_error(const char* prefix, const char* filename, int linenum,
                         const char* msg) VL_MT_UNSAFE {
    // A msg of "ERRORCODE: ..." is a code that changes to a prefix, e.g. "%Error-ERRORCODE: ..."
    // This avoids changing public API of the vl_stop and related functions.
    const char* msgNoCp = msg;
    for (; isupper(*msgNoCp); ++msgNoCp);
    if (msgNoCp[0] == ':' && msgNoCp[1] == ' ') {
        const int codeWidth = static_cast<int>(msgNoCp - msg);
        msgNoCp += 2;
        if (filename && filename[0]) {
            VL_PRINTF(  // Not VL_PRINTF_MT, already on main thread
                "%s-%.*s: %s:%d: %s\n", prefix, codeWidth, msg, filename, linenum, msgNoCp);
        } else {
            VL_PRINTF(  // Not VL_PRINTF_MT, already on main thread
                "%s-%.*s: %s\n", prefix, codeWidth, msg, msgNoCp);
        }
    } else {
        if (filename && filename[0]) {
            VL_PRINTF(  // Not VL_PRINTF_MT, already on main thread
                "%s: %s:%d: %s\n", prefix, filename, linenum, msg);
        } else {
            VL_PRINTF(  // Not VL_PRINTF_MT, already on main thread
                "%s: %s\n", prefix, msg);
        }
    }
}

//===========================================================================
// User definable functions
// Note a TODO is a future version of the API will pass a structure so that
// the calling arguments allow for extension

#ifndef VL_USER_FINISH  ///< Define this to override the vl_finish function
void vl_finish(const char* filename, int linenum, const char* hier) VL_MT_UNSAFE {
    (void)hier;  // hier is unused in the default implementation.
    VL_PRINTF(  // Not VL_PRINTF_MT, already on main thread
        "- %s:%d: Verilog $finish\n", filename, linenum);
    Verilated::threadContextp()->gotFinish(true);
}
#endif

#ifndef VL_USER_STOP  ///< Define this to override the vl_stop function
void vl_stop(const char* filename, int linenum, const char* hier) VL_MT_UNSAFE {
    // $stop or $fatal reporting; would break current API to add param as to which
    if (Verilated::threadContextp()->gotFinish()) return;
    const char* const msg = "Verilog $stop";
    Verilated::threadContextp()->gotError(true);
    Verilated::threadContextp()->gotFinish(true);
    if (Verilated::threadContextp()->fatalOnError()) {
        vl_fatal(filename, linenum, hier, msg);
    } else {
        vl_print_warn_error("%Error", filename, linenum, msg);
        Verilated::runFlushCallbacks();
    }
}
#endif

#ifndef VL_USER_FATAL  ///< Define this to override the vl_fatal function
void vl_fatal(const char* filename, int linenum, const char* hier, const char* msg) VL_MT_UNSAFE {
    (void)hier;  // hier is unused in the default implementation.
    Verilated::threadContextp()->gotError(true);
    Verilated::threadContextp()->gotFinish(true);
    vl_print_warn_error("%Error", filename, linenum, msg);
    Verilated::runFlushCallbacks();

    VL_PRINTF("Aborting...\n");  // Not VL_PRINTF_MT, already on main thread

    // Second flush in case VL_PRINTF does something needing a flush
    Verilated::runFlushCallbacks();

    // Callbacks prior to termination
    Verilated::runExitCallbacks();

    if (Verilated::debug()) {
        std::abort();
    } else {
        std::exit(1);
    }
}
#endif

#ifndef VL_USER_STOP_MAYBE  ///< Define this to override the vl_stop_maybe function
void vl_stop_maybe(const char* filename, int linenum, const char* hier, bool maybe) VL_MT_UNSAFE {
    // $stop or $fatal
    Verilated::threadContextp()->errorCountInc();
    if (maybe
        && Verilated::threadContextp()->errorCount() < Verilated::threadContextp()->errorLimit()) {
        // Do just once when cross error limit
        if (Verilated::threadContextp()->errorCount() == 1) {
            vl_print_warn_error("-Info", filename, linenum,
                                "Verilog $stop, ignored due to +verilator+error+limit");
        }
    } else {
        vl_stop(filename, linenum, hier);
    }
}
#endif

#ifndef VL_USER_WARN  ///< Define this to override the vl_warn function
void vl_warn(const char* filename, int linenum, const char* hier, const char* msg) VL_MT_UNSAFE {
    (void)hier;  // hier is unused in the default implementation.
    vl_print_warn_error("%Warning", filename, linenum, msg);
    Verilated::runFlushCallbacks();
}
#endif

//===========================================================================
// Wrapper to call certain functions via messages when multithreaded

void VL_FINISH_MT(const char* filename, int linenum, const char* hier) VL_MT_SAFE {
    VerilatedThreadMsgQueue::post(VerilatedMsg{[=]() {  //
        vl_finish(filename, linenum, hier);
    }});
}

void VL_STOP_MT(const char* filename, int linenum, const char* hier, bool maybe) VL_MT_SAFE {
    VerilatedThreadMsgQueue::post(VerilatedMsg{[=]() {  //
        vl_stop_maybe(filename, linenum, hier, maybe);
    }});
}

void VL_FATAL_MT(const char* filename, int linenum, const char* hier, const char* msg) VL_MT_SAFE {
    VerilatedThreadMsgQueue::post(VerilatedMsg{[=]() {  //
        vl_fatal(filename, linenum, hier, msg);
    }});
}

void VL_WARN_MT(const char* filename, int linenum, const char* hier, const char* msg) VL_MT_SAFE {
    VerilatedThreadMsgQueue::post(VerilatedMsg{[=]() {  //
        vl_warn(filename, linenum, hier, msg);
    }});
}

//===========================================================================
// Debug prints

// sprintf but return as string (this isn't fast, for print messages only)
std::string _vl_string_vprintf(const char* formatp, va_list ap) VL_MT_SAFE {
    va_list aq;
    va_copy(aq, ap);
    const size_t len = VL_VSNPRINTF(nullptr, 0, formatp, aq);
    va_end(aq);
    if (VL_UNLIKELY(len < 1)) return "";

    char* const bufp = new char[len + 1];
    VL_VSNPRINTF(bufp, len + 1, formatp, ap);

    std::string result{bufp, len};  // Not const to allow move optimization
    delete[] bufp;
    return result;
}

uint64_t _vl_dbg_sequence_number() VL_MT_SAFE {
    static std::atomic<uint64_t> s_sequence;
    return ++s_sequence;
}

uint32_t VL_THREAD_ID() VL_MT_SAFE {
    // Alternative is to use std::this_thread::get_id, but that returns a
    // hard-to-read number and is very slow
    static std::atomic<uint32_t> s_nextId(0);
    static thread_local uint32_t t_myId = ++s_nextId;
    return t_myId;
}

void VL_DBG_MSGF(const char* formatp, ...) VL_MT_SAFE {
    // We're still using c printf formats instead of operator<< so we can avoid the heavy
    // includes that otherwise would be required in every Verilated module
    va_list ap;
    va_start(ap, formatp);
    const std::string result = _vl_string_vprintf(formatp, ap);
    va_end(ap);
    // printf("-imm-V{t%d,%" PRId64 "}%s", VL_THREAD_ID(), _vl_dbg_sequence_number(),
    // result.c_str());

    // Using VL_PRINTF not VL_PRINTF_MT so that we can call VL_DBG_MSGF
    // from within the guts of the thread execution machinery (and it goes
    // to the screen and not into the queues we're debugging)
    VL_PRINTF("-V{t%u,%" PRIu64 "}%s", VL_THREAD_ID(), _vl_dbg_sequence_number(), result.c_str());
}

void VL_PRINTF_MT(const char* formatp, ...) VL_MT_SAFE {
    va_list ap;
    va_start(ap, formatp);
    const std::string result = _vl_string_vprintf(formatp, ap);
    va_end(ap);
    VerilatedThreadMsgQueue::post(VerilatedMsg{[=]() {  //
        VL_PRINTF("%s", result.c_str());
    }});
}

//===========================================================================
// Process -- parts of std::process implementation

std::string VlProcess::randstate() const VL_MT_UNSAFE {
    return VlRNG::vl_thread_rng().get_randstate();
}
void VlProcess::randstate(const std::string& state) VL_MT_UNSAFE {
    VlRNG::vl_thread_rng().set_randstate(state);
}

//===========================================================================
// Random -- Mostly called at init time, so not inline.

static std::pair<uint64_t, uint64_t> vl_splitmix64(uint64_t x) VL_PURE {
    // SplitMix64 algorithm, copied under public domain from
    // https://prng.di.unimi.it/splitmix64.c
    // by Sebastiano Vigna
    uint64_t z = (x += 0x9e3779b97f4a7c15ULL);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return {x, z ^ (z >> 31)};
}

// Xoroshiro128** algorithm, copied under public domain from
// https://xoshiro.di.unimi.it/xoroshiro128starstar.c
// by David Blackman and Sebastiano Vigna

static uint64_t vl_rolt(const uint64_t x, int k) VL_PURE { return (x << k) | (x >> (64 - k)); }

static std::array<uint64_t, 2> vl_rng_state_from_seed(uint64_t seed) VL_PURE {
    const auto split1 = vl_splitmix64(seed);
    const auto split2 = vl_splitmix64(split1.first);
    return {split1.second, split2.second};
}

static uint64_t vl_rng_result(const std::array<uint64_t, 2>& state) VL_PURE {
    const uint64_t s0 = state[0];
    return vl_rolt(s0 * 5, 7) * 9;
}

static std::array<uint64_t, 2>
vl_rng_compute_new_state(const std::array<uint64_t, 2>& current_state) VL_PURE {
    const uint64_t s0 = current_state[0];
    uint64_t s1 = current_state[1];

    s1 ^= s0;
    const uint64_t new_s0 = vl_rolt(s0, 24) ^ s1 ^ (s1 << 16);  // a, b
    const uint64_t new_s1 = vl_rolt(s1, 37);  // c

    return {new_s0, new_s1};
}

VlRNG::VlRNG() VL_MT_SAFE {
    VlRNG& fromr = vl_thread_rng();

    const uint64_t s0 = vl_rng_result(fromr.m_state);
    fromr.m_state = vl_rng_compute_new_state(fromr.m_state);

    const uint64_t s1 = vl_rng_result(fromr.m_state);
    fromr.m_state = vl_rng_compute_new_state(fromr.m_state);

    m_state = {s0, s1};
}

VlRNG::VlRNG(uint64_t seed) VL_PURE { m_state = vl_rng_state_from_seed(seed); }
void VlRNG::srandom(uint64_t n) VL_MT_UNSAFE { m_state = vl_rng_state_from_seed(n); }

uint64_t VlRNG::rand64() VL_MT_UNSAFE {
    const uint64_t result = vl_rng_result(m_state);
    m_state = vl_rng_compute_new_state(m_state);
    return result;
}
uint64_t VlRNG::vl_thread_rng_rand64() VL_MT_SAFE {
    VlRNG& fromr = vl_thread_rng();
    const uint64_t result = vl_rng_result(fromr.m_state);
    fromr.m_state = vl_rng_compute_new_state(fromr.m_state);
    return result;
}

std::string VlRNG::get_randstate() const VL_MT_UNSAFE {
    // Though not stated in IEEE, assumption is the string must be printable
    const char* const stateCharsp = reinterpret_cast<const char*>(&m_state);
    static_assert(sizeof(m_state) == 16, "");
    std::string result{"R00112233445566770011223344556677"};
    for (size_t i = 0; i < sizeof(m_state); ++i) {
        result[1 + i * 2] = 'a' + ((stateCharsp[i] >> 4) & 15);
        result[1 + i * 2 + 1] = 'a' + (stateCharsp[i] & 15);
    }
    return result;
}
void VlRNG::set_randstate(const std::string& state) VL_MT_UNSAFE {
    if (VL_UNLIKELY((state.length() != 1 + 2 * sizeof(m_state)) || (state[0] != 'R'))) {
        VL_PRINTF_MT("%%Warning: set_randstate ignored as state string not from get_randstate\n");
        return;
    }
    char* const stateCharsp = reinterpret_cast<char*>(&m_state);
    for (size_t i = 0; i < sizeof(m_state); ++i) {
        stateCharsp[i]
            = (((state[1 + i * 2] - 'a') & 15) << 4) | ((state[1 + i * 2 + 1] - 'a') & 15);
    }
}

static uint32_t vl_sys_rand32() VL_MT_SAFE {
    // Return random 32-bits using system library.
    // Used only to construct seed for Verilator's PRNG.
    static VerilatedMutex s_mutex;
    const VerilatedLockGuard lock{s_mutex};  // Otherwise rand is unsafe
#if defined(_WIN32) && !defined(__CYGWIN__)
    // Windows doesn't have lrand48(), although Cygwin does.
    return (std::rand() << 16) ^ std::rand();
#else
    return (lrand48() << 16) ^ lrand48();
#endif
}

VlRNG& VlRNG::vl_thread_rng() VL_MT_SAFE {
    static thread_local VlRNG t_rng{0};
    static thread_local uint32_t t_seedEpoch = 0;
    // For speed, we use a thread-local epoch number to know when to reseed
    // A thread always belongs to a single context, so this works out ok
    if (VL_UNLIKELY(t_seedEpoch != VerilatedContextImp::randSeedEpoch())) {
        // Set epoch before state, to avoid race case with new seeding
        t_seedEpoch = VerilatedContextImp::randSeedEpoch();
        t_rng.m_state
            = vl_rng_state_from_seed(Verilated::threadContextp()->impp()->randSeedDefault64());
    }
    return t_rng;
}

WDataOutP VL_RANDOM_W(int obits, WDataOutP outwp) VL_MT_SAFE {
    for (int i = 0; i < VL_WORDS_I(obits); ++i) outwp[i] = vl_rand64();
    // Last word is unclean
    return outwp;
}

double VL_RANDOM_RNG_D(VlRNG& rngr) VL_MT_UNSAFE { return VL_CVT_D_Q(VL_RANDOM_RNG_Q(rngr)); }

WDataOutP VL_RANDOM_RNG_W(VlRNG& rngr, int obits, WDataOutP outwp) VL_MT_UNSAFE {
    for (int i = 0; i < VL_WORDS_I(obits); ++i) outwp[i] = rngr.rand64();
    // Last word is unclean
    return outwp;
}

IData VL_RANDOM_SEEDED_II(IData& seedr) VL_MT_SAFE {
    // $random - seed is a new seed to apply, then we return new seed
    Verilated::threadContextp()->randSeed(static_cast<int>(seedr));
    seedr = VL_RANDOM_I();
    return VL_RANDOM_I();
}
IData VL_URANDOM_SEEDED_II(IData seed) VL_MT_SAFE {
    // $urandom - seed is a new seed to apply
    Verilated::threadContextp()->randSeed(static_cast<int>(seed));
    return VL_RANDOM_I();
}

IData VL_SCOPED_RAND_RESET_I(int obits, uint64_t scopeHash, uint64_t salt) VL_MT_UNSAFE {
    if (Verilated::threadContextp()->randReset() == 0) return 0;
    IData data = ~0;
    if (Verilated::threadContextp()->randReset() != 1) {  // if 2, randomize
        VlRNG rng{Verilated::threadContextp()->randSeed() ^ scopeHash ^ salt};
        data = rng.rand64();
    }
    data &= VL_MASK_I(obits);
    return data;
}

QData VL_SCOPED_RAND_RESET_Q(int obits, uint64_t scopeHash, uint64_t salt) VL_MT_UNSAFE {
    if (Verilated::threadContextp()->randReset() == 0) return 0;
    QData data = ~0ULL;
    if (Verilated::threadContextp()->randReset() != 1) {  // if 2, randomize
        VlRNG rng{Verilated::threadContextp()->randSeed() ^ scopeHash ^ salt};
        data = rng.rand64();
    }
    data &= VL_MASK_Q(obits);
    return data;
}

WDataOutP VL_SCOPED_RAND_RESET_W(int obits, WDataOutP outwp, uint64_t scopeHash,
                                 uint64_t salt) VL_MT_UNSAFE {
    if (Verilated::threadContextp()->randReset() != 2) { return VL_RAND_RESET_W(obits, outwp); }
    VlRNG rng{Verilated::threadContextp()->randSeed() ^ scopeHash ^ salt};
    for (int i = 0; i < VL_WORDS_I(obits) - 1; ++i) outwp[i] = rng.rand64();
    outwp[VL_WORDS_I(obits) - 1] = rng.rand64() & VL_MASK_E(obits);
    return outwp;
}

IData VL_SCOPED_RAND_RESET_ASSIGN_I(int obits, uint64_t scopeHash, uint64_t salt) VL_MT_UNSAFE {
    VlRNG rng{Verilated::threadContextp()->randSeed() ^ scopeHash ^ salt};
    const IData data = rng.rand64() & VL_MASK_I(obits);
    return data;
}

QData VL_SCOPED_RAND_RESET_ASSIGN_Q(int obits, uint64_t scopeHash, uint64_t salt) VL_MT_UNSAFE {
    VlRNG rng{Verilated::threadContextp()->randSeed() ^ scopeHash ^ salt};
    const QData data = rng.rand64() & VL_MASK_Q(obits);
    return data;
}

WDataOutP VL_SCOPED_RAND_RESET_ASSIGN_W(int obits, WDataOutP outwp, uint64_t scopeHash,
                                        uint64_t salt) VL_MT_UNSAFE {
    VlRNG rng{Verilated::threadContextp()->randSeed() ^ scopeHash ^ salt};
    for (int i = 0; i < VL_WORDS_I(obits) - 1; ++i) outwp[i] = rng.rand64();
    outwp[VL_WORDS_I(obits) - 1] = rng.rand64() & VL_MASK_E(obits);
    return outwp;
}

IData VL_RAND_RESET_I(int obits) VL_MT_SAFE {
    if (Verilated::threadContextp()->randReset() == 0) return 0;
    IData data = ~0;
    if (Verilated::threadContextp()->randReset() != 1) {  // if 2, randomize
        data = VL_RANDOM_I();
    }
    data &= VL_MASK_I(obits);
    return data;
}

QData VL_RAND_RESET_Q(int obits) VL_MT_SAFE {
    if (Verilated::threadContextp()->randReset() == 0) return 0;
    QData data = ~0ULL;
    if (Verilated::threadContextp()->randReset() != 1) {  // if 2, randomize
        data = VL_RANDOM_Q();
    }
    data &= VL_MASK_Q(obits);
    return data;
}

WDataOutP VL_RAND_RESET_W(int obits, WDataOutP outwp) VL_MT_SAFE {
    for (int i = 0; i < VL_WORDS_I(obits) - 1; ++i) outwp[i] = VL_RAND_RESET_I(32);
    outwp[VL_WORDS_I(obits) - 1] = VL_RAND_RESET_I(32) & VL_MASK_E(obits);
    return outwp;
}
WDataOutP VL_ZERO_RESET_W(int obits, WDataOutP outwp) VL_MT_SAFE {
    // Not inlined to speed up compilation of slowpath code
    return VL_ZERO_W(obits, outwp);
}

//===========================================================================
// Debug

void _vl_debug_print_w(int lbits, const WDataInP iwp) VL_MT_SAFE {
    VL_PRINTF_MT("  Data: w%d: ", lbits);
    for (int i = VL_WORDS_I(lbits) - 1; i >= 0; --i) VL_PRINTF_MT("%08x ", iwp[i]);
    VL_PRINTF_MT("\n");
}

//===========================================================================
// Slow expressions

WDataOutP _vl_moddiv_w(int lbits, WDataOutP owp, const WDataInP lwp, const WDataInP rwp,
                       bool is_modulus) VL_MT_SAFE {
    // See Knuth Algorithm D.  Computes u/v = q.r
    // This isn't massively tuned, as wide division is rare
    // for debug see V3Number version
    // Requires clean input
    const int words = VL_WORDS_I(lbits);
    for (int i = 0; i < words; ++i) owp[i] = 0;
    // Find MSB and check for zero.
    const int umsbp1 = VL_MOSTSETBITP1_W(words, lwp);  // dividend
    const int vmsbp1 = VL_MOSTSETBITP1_W(words, rwp);  // divisor
    if (VL_UNLIKELY(vmsbp1 == 0)  // rwp==0 so division by zero.  Return 0.
        || VL_UNLIKELY(umsbp1 == 0)) {  // 0/x so short circuit and return 0
        return owp;
    }

    const int uw = VL_WORDS_I(umsbp1);  // aka "m" in the algorithm
    const int vw = VL_WORDS_I(vmsbp1);  // aka "n" in the algorithm
    VL_DEBUG_IFDEF(assert(uw <= VL_MULS_MAX_WORDS););
    VL_DEBUG_IFDEF(assert(vw <= VL_MULS_MAX_WORDS););

    if (vw == 1) {  // Single divisor word breaks rest of algorithm
        uint64_t k = 0;
        for (int j = uw - 1; j >= 0; --j) {
            const uint64_t unw64 = ((k << 32ULL) + static_cast<uint64_t>(lwp[j]));
            owp[j] = unw64 / static_cast<uint64_t>(rwp[0]);
            k = unw64 - static_cast<uint64_t>(owp[j]) * static_cast<uint64_t>(rwp[0]);
        }
        if (is_modulus) {
            owp[0] = k;
            for (int i = 1; i < words; ++i) owp[i] = 0;
        }
        return owp;
    }

    // +1 word as we may shift during normalization
    uint32_t un[VL_MULS_MAX_WORDS + 1];  // Fixed size, as MSVC++ doesn't allow [words] here
    uint32_t vn[VL_MULS_MAX_WORDS + 1];  // v normalized

    // Zero for ease of debugging and to save having to zero for shifts
    // Note +1 as loop will use extra word
    for (int i = 0; i < words + 1; ++i) un[i] = vn[i] = 0;

    // Algorithm requires divisor MSB to be set
    // Copy and shift to normalize divisor so MSB of vn[vw-1] is set
    const int s = 31 - VL_BITBIT_I(vmsbp1 - 1);  // shift amount (0...31)
    // Copy and shift dividend by same amount; may set new upper word
    if (s) {
        for (int i = vw - 1; i > 0; --i) vn[i] = (rwp[i] << s) | (rwp[i - 1] >> (32 - s));
        vn[0] = rwp[0] << s;
        un[uw] = lwp[uw - 1] >> (32 - s);
        for (int i = uw - 1; i > 0; --i) un[i] = (lwp[i] << s) | (lwp[i - 1] >> (32 - s));
        un[0] = lwp[0] << s;
    } else {
        for (int i = vw - 1; i > 0; --i) vn[i] = rwp[i];
        vn[0] = rwp[0];
        un[uw] = 0;
        for (int i = uw - 1; i > 0; --i) un[i] = lwp[i];
        un[0] = lwp[0];
    }

    // Main loop
    for (int j = uw - vw; j >= 0; --j) {
        // Estimate
        const uint64_t unw64
            = (static_cast<uint64_t>(un[j + vw]) << 32ULL | static_cast<uint64_t>(un[j + vw - 1]));
        uint64_t qhat = unw64 / static_cast<uint64_t>(vn[vw - 1]);
        uint64_t rhat = unw64 - qhat * static_cast<uint64_t>(vn[vw - 1]);

    again:
        if (qhat >= 0x100000000ULL || ((qhat * vn[vw - 2]) > ((rhat << 32ULL) + un[j + vw - 2]))) {
            qhat = qhat - 1;
            rhat = rhat + vn[vw - 1];
            if (rhat < 0x100000000ULL) goto again;
        }

        int64_t t = 0;  // Must be signed
        uint64_t k = 0;
        for (int i = 0; i < vw; ++i) {
            const uint64_t p = qhat * vn[i];  // Multiply by estimate
            t = un[i + j] - k - (p & 0xFFFFFFFFULL);  // Subtract
            un[i + j] = t;
            k = (p >> 32ULL) - (t >> 32ULL);
        }
        t = un[j + vw] - k;
        un[j + vw] = t;
        owp[j] = qhat;  // Save quotient digit

        if (t < 0) {
            // Over subtracted; correct by adding back
            owp[j]--;
            k = 0;
            for (int i = 0; i < vw; ++i) {
                t = static_cast<uint64_t>(un[i + j]) + static_cast<uint64_t>(vn[i]) + k;
                un[i + j] = t;
                k = t >> 32ULL;
            }
            un[j + vw] = un[j + vw] + k;
        }
    }

    if (is_modulus) {  // modulus
        // Need to reverse normalization on copy to output
        if (s) {
            for (int i = 0; i < vw; ++i) owp[i] = (un[i] >> s) | (un[i + 1] << (32 - s));
        } else {
            for (int i = 0; i < vw; ++i) owp[i] = un[i];
        }
        for (int i = vw; i < words; ++i) owp[i] = 0;
        return owp;
    } else {  // division
        return owp;
    }
}

WDataOutP VL_POW_WWW(int obits, int, int rbits, WDataOutP owp, const WDataInP lwp,
                     const WDataInP rwp) VL_MT_SAFE {
    // obits==lbits, rbits can be different
    const int owords = VL_WORDS_I(obits);
    VL_DEBUG_IFDEF(assert(owords <= VL_MULS_MAX_WORDS););
    owp[0] = 1;
    for (int i = 1; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
    VlWide<VL_MULS_MAX_WORDS> powstore;  // Fixed size, as MSVC++ doesn't allow [words] here
    VlWide<VL_MULS_MAX_WORDS> lastpowstore;  // Fixed size, as MSVC++ doesn't allow [words] here
    VlWide<VL_MULS_MAX_WORDS> lastoutstore;  // Fixed size, as MSVC++ doesn't allow [words] here
    VL_ASSIGN_W(obits, powstore, lwp);
    for (int bit = 0; bit < rbits; ++bit) {
        if (bit > 0) {  // power = power*power
            VL_ASSIGN_W(obits, lastpowstore, powstore);
            VL_MUL_W(owords, powstore, lastpowstore, lastpowstore);
        }
        if (VL_BITISSET_W(rwp, bit)) {  // out *= power
            VL_ASSIGN_W(obits, lastoutstore, owp);
            VL_MUL_W(owords, owp, lastoutstore, powstore);
        }
    }
    return owp;
}
WDataOutP VL_POW_WWQ(int obits, int lbits, int rbits, WDataOutP owp, const WDataInP lwp,
                     QData rhs) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> rhsw;
    VL_SET_WQ(rhsw, rhs);
    return VL_POW_WWW(obits, lbits, rbits, owp, lwp, rhsw);
}
QData VL_POW_QQW(int, int, int rbits, QData lhs, const WDataInP rwp) VL_MT_SAFE {
    const int rwords = VL_WORDS_I(rbits);
    EData rnz = rwp[0];
    for (int w = 1; w < rwords; ++w) rnz |= rwp[w];
    if (!rnz) return 1;  // rwp == 0
    if (VL_UNLIKELY(lhs == 0)) return 0;
    QData power = lhs;
    QData result = 1ULL;
    for (int bit = 0; bit < rbits; ++bit) {
        if (bit > 0) power = power * power;
        if (VL_BITISSET_W(rwp, bit)) result *= power;
    }
    return result;
}

WDataOutP VL_POWSS_WWW(int obits, int, int rbits, WDataOutP owp, const WDataInP lwp,
                       const WDataInP rwp, bool lsign, bool rsign) VL_MT_SAFE {
    // obits==lbits, rbits can be different
    if (rsign && VL_SIGN_W(rbits, rwp)) {
        const int words = VL_WORDS_I(obits);
        VL_ZERO_W(obits, owp);
        EData lor = 0;  // 0=all zeros, ~0=all ones, else mix
        for (int i = 1; i < (words - 1); ++i) lor |= lwp[i];
        lor |= ((lwp[words - 1] == VL_MASK_E(rbits)) ? ~VL_EUL(0) : 0);
        if (lor == 0 && lwp[0] == 0) {  // "X" so return 0
            return owp;
        } else if (lor == 0 && lwp[0] == 1) {  // 1
            owp[0] = 1;
            return owp;
        } else if (lsign && lor == ~VL_EUL(0) && lwp[0] == ~VL_EUL(0)) {  // -1
            if (rwp[0] & 1) {  // -1^odd=-1
                return VL_ALLONES_W(obits, owp);
            } else {  // -1^even=1
                owp[0] = 1;
                return owp;
            }
        }
        return owp;
    }
    return VL_POW_WWW(obits, rbits, rbits, owp, lwp, rwp);
}
WDataOutP VL_POWSS_WWQ(int obits, int lbits, int rbits, WDataOutP owp, const WDataInP lwp,
                       QData rhs, bool lsign, bool rsign) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> rhsw;
    VL_SET_WQ(rhsw, rhs);
    return VL_POWSS_WWW(obits, lbits, rbits, owp, lwp, rhsw, lsign, rsign);
}
QData VL_POWSS_QQW(int obits, int, int rbits, QData lhs, const WDataInP rwp, bool lsign,
                   bool rsign) VL_MT_SAFE {
    // Skip check for rhs == 0, as short-circuit doesn't save time
    if (rsign && VL_SIGN_W(rbits, rwp)) {
        if (lhs == 0) {
            return 0;  // "X"
        } else if (lhs == 1) {
            return 1;
        } else if (lsign && lhs == VL_MASK_Q(obits)) {  // -1
            if (rwp[0] & 1) {
                return VL_MASK_Q(obits);  // -1^odd=-1
            } else {
                return 1;  // -1^even=1
            }
        }
        return 0;
    }
    return VL_POW_QQW(obits, rbits, rbits, lhs, rwp);
}

double VL_ITOR_D_W(int lbits, const WDataInP lwp) VL_PURE {
    int ms_word = VL_WORDS_I(lbits) - 1;
    for (; !lwp[ms_word] && ms_word > 0;) --ms_word;
    if (ms_word == 0) return static_cast<double>(lwp[0]);
    if (ms_word == 1) return static_cast<double>(VL_SET_QW(lwp));
    // We need 53 bits of mantissa, which might mean looking at 3 words
    // namely ms_word, ms_word-1 and ms_word-2
    const EData ihi = lwp[ms_word];
    const EData imid = lwp[ms_word - 1];
    const EData ilo = lwp[ms_word - 2];
    const double hi = static_cast<double>(ihi) * std::exp2(2 * VL_EDATASIZE);
    const double mid = static_cast<double>(imid) * std::exp2(VL_EDATASIZE);
    const double lo = static_cast<double>(ilo);
    const double d = (hi + mid + lo) * std::exp2(VL_EDATASIZE * (ms_word - 2));
    return d;
}
double VL_ISTOR_D_W(int lbits, const WDataInP lwp) VL_MT_SAFE {
    if (!VL_SIGN_W(lbits, lwp)) return VL_ITOR_D_W(lbits, lwp);
    const int words = VL_WORDS_I(lbits);
    VL_DEBUG_IFDEF(assert(words <= VL_MULS_MAX_WORDS););
    uint32_t pos[VL_MULS_MAX_WORDS + 1];  // Fixed size, as MSVC++ doesn't allow [words] here
    VL_NEGATE_W(words, pos, lwp);
    _vl_clean_inplace_w(lbits, pos);
    return -VL_ITOR_D_W(lbits, pos);
}

//===========================================================================
// Formatting

// Output a string representation of a wide number
std::string VL_DECIMAL_NW(int width, const WDataInP lwp) VL_MT_SAFE {
    const int maxdecwidth = (width + 3) * 4 / 3;
    // Or (maxdecwidth+7)/8], but can't have more than 4 BCD bits per word
    VlWide<VL_VALUE_STRING_MAX_WIDTH / 4 + 2> bcd;
    VL_ZERO_W(maxdecwidth, bcd);
    VlWide<VL_VALUE_STRING_MAX_WIDTH / 4 + 2> tmp;
    VlWide<VL_VALUE_STRING_MAX_WIDTH / 4 + 2> tmp2;
    int from_bit = width - 1;
    // Skip all leading zeros
    for (; from_bit >= 0 && !(VL_BITRSHIFT_W(lwp, from_bit) & 1); --from_bit) {}
    // Double-dabble algorithm
    for (; from_bit >= 0; --from_bit) {
        // Any digits >= 5 need an add 3 (via tmp)
        for (int nibble_bit = 0; nibble_bit < maxdecwidth; nibble_bit += 4) {
            if ((VL_BITRSHIFT_W(bcd, nibble_bit) & 0xf) >= 5) {
                VL_ZERO_W(maxdecwidth, tmp2);
                tmp2[VL_BITWORD_E(nibble_bit)] |= VL_EUL(0x3) << VL_BITBIT_E(nibble_bit);
                VL_ASSIGN_W(maxdecwidth, tmp, bcd);
                VL_ADD_W(VL_WORDS_I(maxdecwidth), bcd, tmp, tmp2);
            }
        }
        // Shift; bcd = bcd << 1
        VL_ASSIGN_W(maxdecwidth, tmp, bcd);
        VL_SHIFTL_WWI(maxdecwidth, maxdecwidth, 32, bcd, tmp, 1);
        // bcd[0] = lwp[from_bit]
        if (VL_BITISSET_W(lwp, from_bit)) bcd[0] |= 1;
    }
    std::string output;
    int lsb = (maxdecwidth - 1) & ~3;
    for (; lsb > 0; lsb -= 4) {  // Skip leading zeros
        if (VL_BITRSHIFT_W(bcd, lsb) & 0xf) break;
    }
    for (; lsb >= 0; lsb -= 4) {
        output += ('0' + (VL_BITRSHIFT_W(bcd, lsb) & 0xf));  // 0..9
    }
    return output;
}

template <typename T>
std::string _vl_vsformat_time(char* tmp, T ld, int timeunit, bool left, size_t width) VL_MT_SAFE {
    const VerilatedContextImp* const ctxImpp = Verilated::threadContextp()->impp();
    const std::string suffix = ctxImpp->timeFormatSuffix();
    const int userUnits = ctxImpp->timeFormatUnits();  // 0..-15
    const int fracDigits = ctxImpp->timeFormatPrecision();  // 0..N
    const int shift = -userUnits + fracDigits + timeunit;  // 0..-15
    int digits = 0;
    if (std::numeric_limits<T>::is_integer) {
        constexpr int b = 128;
        constexpr int w = VL_WORDS_I(b);
        VlWide<w> tmp0;
        VlWide<w> tmp1;
        VlWide<w> tmp2;
        VlWide<w> tmp3;

        WDataInP shifted = VL_EXTEND_WQ(b, 0, tmp0, static_cast<QData>(ld));
        if (shift < 0) {
            const WDataInP pow10 = VL_EXTEND_WQ(b, 0, tmp1, vl_time_pow10(-shift));
            shifted = VL_DIV_WWW(b, tmp2, shifted, pow10);
        } else {
            const WDataInP pow10 = VL_EXTEND_WQ(b, 0, tmp1, vl_time_pow10(shift));
            shifted = VL_MUL_W(w, tmp2, shifted, pow10);
        }

        const WDataInP fracDigitsPow10 = VL_EXTEND_WQ(b, 0, tmp3, vl_time_pow10(fracDigits));
        const WDataInP integer = VL_DIV_WWW(b, tmp0, shifted, fracDigitsPow10);
        const WDataInP frac = VL_MODDIV_WWW(b, tmp1, shifted, fracDigitsPow10);
        const WDataInP max64Bit
            = VL_EXTEND_WQ(b, 0, tmp2, std::numeric_limits<uint64_t>::max());  // breaks shifted
        if (VL_GT_W(w, integer, max64Bit)) {
            WDataOutP v = VL_ASSIGN_W(b, tmp3, integer);  // breaks fracDigitsPow10
            VlWide<w> zero;
            VlWide<w> ten;
            VL_ZERO_W(b, zero);
            VL_EXTEND_WI(b, 0, ten, 10);
            char buf[128];  // 128B is obviously long enough to represent 128bit integer in decimal
            char* ptr = buf + sizeof(buf) - 1;
            *ptr = '\0';
            while (VL_GT_W(w, v, zero)) {
                --ptr;
                const WDataInP mod = VL_MODDIV_WWW(b, tmp2, v, ten);  // breaks max64Bit
                *ptr = "0123456789"[VL_SET_QW(mod)];
                VlWide<w> divided;
                VL_DIV_WWW(b, divided, v, ten);
                VL_ASSIGN_W(b, v, divided);
            }
            if (!fracDigits) {
                digits = VL_SNPRINTF(tmp, VL_VALUE_STRING_MAX_WIDTH, "%s%s", ptr, suffix.c_str());
            } else {
                digits = VL_SNPRINTF(tmp, VL_VALUE_STRING_MAX_WIDTH, "%s.%0*" PRIu64 "%s", ptr,
                                     fracDigits, VL_SET_QW(frac), suffix.c_str());
            }
        } else {
            const uint64_t integer64 = VL_SET_QW(integer);
            if (!fracDigits) {
                digits = VL_SNPRINTF(tmp, VL_VALUE_STRING_MAX_WIDTH, "%" PRIu64 "%s", integer64,
                                     suffix.c_str());
            } else {
                digits = VL_SNPRINTF(tmp, VL_VALUE_STRING_MAX_WIDTH, "%" PRIu64 ".%0*" PRIu64 "%s",
                                     integer64, fracDigits, VL_SET_QW(frac), suffix.c_str());
            }
        }
    } else {
        const double shiftd = vl_time_multiplier(shift);
        const double scaled = ld * shiftd;
        const double fracDiv = vl_time_multiplier(fracDigits);
        const double whole = scaled / fracDiv;
        if (!fracDigits) {
            digits = VL_SNPRINTF(tmp, VL_VALUE_STRING_MAX_WIDTH, "%.0f%s", whole, suffix.c_str());
        } else {
            digits = VL_SNPRINTF(tmp, VL_VALUE_STRING_MAX_WIDTH, "%.*f%s", fracDigits, whole,
                                 suffix.c_str());
        }
    }

    const int needmore = static_cast<int>(width) - digits;
    std::string padding;
    if (needmore > 0) padding.append(needmore, ' ');  // Pad with spaces
    return left ? (tmp + padding) : (padding + tmp);
}

// Do a va_arg returning a quad, assuming input argument is anything less than wide
#define VL_VA_ARG_Q_(ap, bits) (((bits) <= VL_IDATASIZE) ? va_arg(ap, IData) : va_arg(ap, QData))

void _vl_vsformat(std::string& output, const std::string& format, va_list ap) VL_MT_SAFE {
    // Format a Verilog $write style format into the output list
    // The format must be pre-processed (and lower cased) by Verilator
    // Arguments are in "width, arg-value (or WDataIn* if wide)" form
    //
    // Note uses a single buffer internally; presumes only one usage per printf
    // Note also assumes variables < 64 are not wide, this assumption is
    // sometimes not true in low-level routines written here in verilated.cpp
    static thread_local char t_tmp[VL_VALUE_STRING_MAX_WIDTH];
    std::string::const_iterator pctit = format.end();  // Most recent %##.##g format
    bool inPct = false;
    bool widthSet = false;
    bool left = false;
    size_t width = 0;
    for (std::string::const_iterator pos = format.cbegin(); pos != format.cend(); ++pos) {
        if (!inPct && pos[0] == '%') {
            pctit = pos;
            inPct = true;
            widthSet = false;
            width = 0;
        } else if (!inPct) {  // Normal text
            // Fast-forward to next escape and add to output
            std::string::const_iterator ep = pos;
            while (ep != format.end() && ep[0] != '%') ++ep;
            if (ep != pos) {
                output.append(pos, ep);
                pos = ep - 1;
            }
        } else {  // Format character
            inPct = false;
            const char fmt = pos[0];
            switch (fmt) {
            case '0':  // FALLTHRU
            case '1':  // FALLTHRU
            case '2':  // FALLTHRU
            case '3':  // FALLTHRU
            case '4':  // FALLTHRU
            case '5':  // FALLTHRU
            case '6':  // FALLTHRU
            case '7':  // FALLTHRU
            case '8':  // FALLTHRU
            case '9':
                inPct = true;  // Get more digits
                widthSet = true;
                width = width * 10 + (fmt - '0');
                break;
            case '-':
                left = true;
                inPct = true;  // Get more digits
                break;
            case '.':
                inPct = true;  // Get more digits
                break;
            case '%':  //
                output += '%';
                break;
            case 'N': {  // "C" string with name of module, add . if needed
                const char* const cstrp = va_arg(ap, const char*);
                if (VL_LIKELY(*cstrp)) {
                    output += cstrp;
                    output += '.';
                }
                break;
            }
            case 'S': {  // "C" string
                const char* const cstrp = va_arg(ap, const char*);
                output += cstrp;
                break;
            }
            case '@': {  // Verilog/C++ string
                va_arg(ap, int);  // # bits is ignored
                const std::string* const cstrp = va_arg(ap, const std::string*);
                std::string padding;
                if (width > cstrp->size()) padding.append(width - cstrp->size(), ' ');
                output += left ? (*cstrp + padding) : (padding + *cstrp);
                break;
            }
            case 'e':
            case 'f':
            case 'g':
            case '^': {  // Realtime
                const int lbits = va_arg(ap, int);
                const double d = va_arg(ap, double);
                (void)lbits;  // UNUSED - always 64
                if (fmt == '^') {  // Realtime
                    if (!widthSet) width = Verilated::threadContextp()->impp()->timeFormatWidth();
                    const int timeunit = va_arg(ap, int);
                    output += _vl_vsformat_time(t_tmp, d, timeunit, left, width);
                } else {
                    const std::string fmts{pctit, pos + 1};
                    VL_SNPRINTF(t_tmp, VL_VALUE_STRING_MAX_WIDTH, fmts.c_str(), d);
                    output += t_tmp;
                }
                break;
            }
            case 'p': {  // 'x' but parameter is string
                const int lbits = va_arg(ap, int);
                (void)lbits;
                const std::string* const cstr = va_arg(ap, const std::string*);
                std::ostringstream oss;
                for (unsigned char c : *cstr) oss << std::hex << static_cast<int>(c);
                std::string hex_str = oss.str();
                if (width > 0 && widthSet) {
                    hex_str = hex_str.size() > width
                                  ? hex_str.substr(0, width)
                                  : std::string(width - hex_str.size(), '0') + hex_str;
                    output += hex_str;
                }
                break;
            }
            default: {
                // Deal with all read-and-print somethings
                const int lbits = va_arg(ap, int);
                QData ld = 0;
                VlWide<VL_WQ_WORDS_E> qlwp;
                WDataInP lwp = nullptr;
                if (lbits <= VL_QUADSIZE) {
                    ld = VL_VA_ARG_Q_(ap, lbits);
                    VL_SET_WQ(qlwp, ld);
                    lwp = qlwp;
                } else {
                    lwp = va_arg(ap, WDataInP);
                    ld = lwp[0];
                }
                int lsb = lbits - 1;
                if (widthSet && width == 0) {
                    while (lsb && !VL_BITISSET_W(lwp, lsb)) --lsb;
                }
                switch (fmt) {
                case 'c': {
                    const IData charval = ld & 0xff;
                    output += static_cast<char>(charval);
                    break;
                }
                case 's': {
                    std::string field;
                    for (; lsb >= 0; --lsb) {
                        lsb = (lsb / 8) * 8;  // Next digit
                        const IData charval = VL_BITRSHIFT_W(lwp, lsb) & 0xff;
                        field += (charval == 0) ? ' ' : charval;
                    }
                    std::string padding;
                    if (width > field.size()) padding.append(width - field.size(), ' ');
                    output += left ? (field + padding) : (padding + field);
                    break;
                }
                case 'd': {  // Signed decimal
                    int digits = 0;
                    std::string append;
                    if (lbits <= VL_QUADSIZE) {
                        digits
                            = VL_SNPRINTF(t_tmp, VL_VALUE_STRING_MAX_WIDTH, "%" PRId64,
                                          static_cast<int64_t>(VL_EXTENDS_QQ(lbits, lbits, ld)));
                        append = t_tmp;
                    } else {
                        if (VL_SIGN_E(lbits, lwp[VL_WORDS_I(lbits) - 1])) {
                            VlWide<VL_VALUE_STRING_MAX_WIDTH / 4 + 2> neg;
                            VL_NEGATE_W(VL_WORDS_I(lbits), neg, lwp);
                            append = "-"s + VL_DECIMAL_NW(lbits, neg);
                        } else {
                            append = VL_DECIMAL_NW(lbits, lwp);
                        }
                        digits = static_cast<int>(append.length());
                    }
                    const int needmore = static_cast<int>(width) - digits;
                    if (needmore > 0) {
                        std::string padding;
                        if (left) {
                            padding.append(needmore, ' ');  // Pre-pad spaces
                            output += append + padding;
                        } else {
                            if (pctit != format.end() && pctit[0] && pctit[1] == '0') {  // %0
                                padding.append(needmore, '0');  // Pre-pad zero
                            } else {
                                padding.append(needmore, ' ');  // Pre-pad spaces
                            }
                            output += padding + append;
                        }
                    } else {
                        output += append;
                    }
                    break;
                }
                case '#': {  // Unsigned decimal
                    int digits = 0;
                    std::string append;
                    if (lbits <= VL_QUADSIZE) {
                        digits = VL_SNPRINTF(t_tmp, VL_VALUE_STRING_MAX_WIDTH, "%" PRIu64, ld);
                        append = t_tmp;
                    } else {
                        append = VL_DECIMAL_NW(lbits, lwp);
                        digits = static_cast<int>(append.length());
                    }
                    const int needmore = static_cast<int>(width) - digits;
                    if (needmore > 0) {
                        std::string padding;
                        if (left) {
                            padding.append(needmore, ' ');  // Pre-pad spaces
                            output += append + padding;
                        } else {
                            if (pctit != format.end() && pctit[0] && pctit[1] == '0') {  // %0
                                padding.append(needmore, '0');  // Pre-pad zero
                            } else {
                                padding.append(needmore, ' ');  // Pre-pad spaces
                            }
                            output += padding + append;
                        }
                    } else {
                        output += append;
                    }
                    break;
                }
                case 't': {  // Time
                    if (!widthSet) width = Verilated::threadContextp()->impp()->timeFormatWidth();
                    const int timeunit = va_arg(ap, int);
                    output += _vl_vsformat_time(t_tmp, ld, timeunit, left, width);
                    break;
                }
                case 'b':  // FALLTHRU
                case 'o':  // FALLTHRU
                case 'x': {
                    if (widthSet || left) {
                        lsb = VL_MOSTSETBITP1_W(VL_WORDS_I(lbits), lwp);
                        lsb = (lsb < 1) ? 0 : (lsb - 1);
                    }

                    std::string append;
                    int digits;
                    switch (fmt) {
                    case 'b': {
                        digits = lsb + 1;
                        for (; lsb >= 0; --lsb) append += (VL_BITRSHIFT_W(lwp, lsb) & 1) + '0';
                        break;
                    }
                    case 'o': {
                        digits = (lsb + 1 + 2) / 3;
                        for (; lsb >= 0; --lsb) {
                            lsb = (lsb / 3) * 3;  // Next digit
                            // Octal numbers may span more than one wide word,
                            // so we need to grab each bit separately and check for overrun
                            // Octal is rare, so we'll do it a slow simple way
                            append += static_cast<char>(
                                '0' + ((VL_BITISSETLIMIT_W(lwp, lbits, lsb + 0)) ? 1 : 0)
                                + ((VL_BITISSETLIMIT_W(lwp, lbits, lsb + 1)) ? 2 : 0)
                                + ((VL_BITISSETLIMIT_W(lwp, lbits, lsb + 2)) ? 4 : 0));
                        }
                        break;
                    }
                    default: {  // 'x'
                        digits = (lsb + 1 + 3) / 4;
                        for (; lsb >= 0; --lsb) {
                            lsb = (lsb / 4) * 4;  // Next digit
                            const IData charval = VL_BITRSHIFT_W(lwp, lsb) & 0xf;
                            append += "0123456789abcdef"[charval];
                        }
                        break;
                    }
                    }  // switch

                    const int needmore = static_cast<int>(width) - digits;
                    if (needmore > 0) {
                        std::string padding;
                        if (left) {
                            padding.append(needmore, ' ');  // Pre-pad spaces
                            output += append + padding;
                        } else {
                            padding.append(needmore, '0');  // Pre-pad zero
                            output += padding + append;
                        }
                    } else {
                        output += append;
                    }
                    break;
                }  // b / o / x
                case 'u':
                case 'z': {  // Packed 4-state
                    const bool is_4_state = (fmt == 'z');
                    output.reserve(output.size() + ((is_4_state ? 2 : 1) * VL_WORDS_I(lbits)));
                    int bytes_to_go = VL_BYTES_I(lbits);
                    int bit = 0;
                    while (bytes_to_go > 0) {
                        const int wr_bytes = std::min(4, bytes_to_go);
                        for (int byte = 0; byte < wr_bytes; byte++, bit += 8)
                            output += static_cast<char>(VL_BITRSHIFT_W(lwp, bit) & 0xff);
                        output.append(4 - wr_bytes, static_cast<char>(0));
                        if (is_4_state) output.append(4, static_cast<char>(0));
                        bytes_to_go -= wr_bytes;
                    }
                    break;
                }
                case 'v':  // Strength; assume always strong
                    for (lsb = lbits - 1; lsb >= 0; --lsb) {
                        if (VL_BITRSHIFT_W(lwp, lsb) & 1) {
                            output += "St1 ";
                        } else {
                            output += "St0 ";
                        }
                    }
                    break;
                default: {  // LCOV_EXCL_START
                    const std::string msg = "Unknown _vl_vsformat code: "s + pos[0];
                    VL_FATAL_MT(__FILE__, __LINE__, "", msg.c_str());
                    break;
                }  // LCOV_EXCL_STOP
                }  // switch
            }
            }  // switch
        }
    }
}

static bool _vl_vsss_eof(FILE* fp, int floc) VL_MT_SAFE {
    if (VL_LIKELY(fp)) {
        return std::feof(fp) ? true : false;  // true : false to prevent MSVC++ warning
    } else {
        return floc < 0;
    }
}
static void _vl_vsss_advance(FILE* fp, int& floc) VL_MT_SAFE {
    if (VL_LIKELY(fp)) {
        std::fgetc(fp);
    } else {
        floc -= 8;
    }
}
static int _vl_vsss_peek(FILE* fp, int& floc, const WDataInP fromp,
                         const std::string& fstr) VL_MT_SAFE {
    // Get a character without advancing
    if (VL_LIKELY(fp)) {
        const int data = std::fgetc(fp);
        if (data == EOF) return EOF;
        ungetc(data, fp);
        return data;
    } else {
        if (floc < 0) return EOF;
        floc = floc & ~7;  // Align to closest character
        if (fromp == nullptr) {
            return fstr[fstr.length() - 1 - (floc >> 3)];
        } else {
            return VL_BITRSHIFT_W(fromp, floc) & 0xff;
        }
    }
}
static void _vl_vsss_skipspace(FILE* fp, int& floc, const WDataInP fromp,
                               const std::string& fstr) VL_MT_SAFE {
    while (true) {
        const int c = _vl_vsss_peek(fp, floc, fromp, fstr);
        if (c == EOF || !std::isspace(c)) return;
        _vl_vsss_advance(fp, floc);
    }
}
static void _vl_vsss_read_str(FILE* fp, int& floc, const WDataInP fromp, const std::string& fstr,
                              char* tmpp, const char* acceptp) VL_MT_SAFE {
    // Read into tmp, consisting of characters from acceptp list
    char* cp = tmpp;
    while (true) {
        int c = _vl_vsss_peek(fp, floc, fromp, fstr);
        if (c == EOF || std::isspace(c)) break;
        if (acceptp && nullptr == std::strchr(acceptp, c)) break;  // String - allow anything
        if (acceptp) c = std::tolower(c);  // Non-strings we'll simplify
        *cp++ = c;
        _vl_vsss_advance(fp, floc);
    }
    *cp++ = '\0';
    // VL_DBG_MSGF(" _read got='"<<tmpp<<"'\n");
}
static char* _vl_vsss_read_bin(FILE* fp, int& floc, const WDataInP fromp, const std::string& fstr,
                               char* beginp, std::size_t n,
                               const bool inhibit = false) VL_MT_SAFE {
    // Variant of _vl_vsss_read_str using the same underlying I/O functions but optimized
    // specifically for block reads of N bytes (read operations are not demarcated by
    // whitespace). In the fp case, except descriptor to have been opened in binary mode.
    while (n-- > 0) {
        const int c = _vl_vsss_peek(fp, floc, fromp, fstr);
        if (c == EOF) return nullptr;
        if (!inhibit) *beginp++ = c;
        _vl_vsss_advance(fp, floc);
    }
    return beginp;
}
static void _vl_vsss_setbit(WDataOutP iowp, int obits, int lsb, int nbits, IData ld) VL_MT_SAFE {
    for (; nbits && lsb < obits; nbits--, lsb++, ld >>= 1) VL_ASSIGNBIT_WI(lsb, iowp, ld & 1);
}
void _vl_vsss_based(WDataOutP owp, int obits, int baseLog2, const char* strp, size_t posstart,
                    size_t posend) VL_MT_SAFE {
    // Read in base "2^^baseLog2" digits from strp[posstart..posend-1] into owp of size obits.
    VL_ZERO_W(obits, owp);
    int lsb = 0;
    for (int i = 0, pos = static_cast<int>(posend) - 1;
         i < obits && pos >= static_cast<int>(posstart); --pos) {
        // clang-format off
        switch (tolower (strp[pos])) {
        case 'x': case 'z': case '?':  // FALLTHRU
        case '0': lsb += baseLog2; break;
        case '1': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  1); lsb += baseLog2; break;
        case '2': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  2); lsb += baseLog2; break;
        case '3': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  3); lsb += baseLog2; break;
        case '4': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  4); lsb += baseLog2; break;
        case '5': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  5); lsb += baseLog2; break;
        case '6': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  6); lsb += baseLog2; break;
        case '7': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  7); lsb += baseLog2; break;
        case '8': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  8); lsb += baseLog2; break;
        case '9': _vl_vsss_setbit(owp, obits, lsb, baseLog2,  9); lsb += baseLog2; break;
        case 'a': _vl_vsss_setbit(owp, obits, lsb, baseLog2, 10); lsb += baseLog2; break;
        case 'b': _vl_vsss_setbit(owp, obits, lsb, baseLog2, 11); lsb += baseLog2; break;
        case 'c': _vl_vsss_setbit(owp, obits, lsb, baseLog2, 12); lsb += baseLog2; break;
        case 'd': _vl_vsss_setbit(owp, obits, lsb, baseLog2, 13); lsb += baseLog2; break;
        case 'e': _vl_vsss_setbit(owp, obits, lsb, baseLog2, 14); lsb += baseLog2; break;
        case 'f': _vl_vsss_setbit(owp, obits, lsb, baseLog2, 15); lsb += baseLog2; break;
        case '_': break;
        }
        // clang-format on
    }
}

IData _vl_vsscanf(FILE* fp,  // If a fscanf
                  int fbits, const WDataInP fromp,  // Else if a sscanf
                  const std::string& fstr,  // if a sscanf to string
                  const std::string& format, va_list ap) VL_MT_SAFE {
    // Read a Verilog $sscanf/$fscanf style format into the output list
    // The format must be pre-processed (and lower cased) by Verilator
    // Arguments are in "width, arg-value (or WDataIn* if wide)" form
    static thread_local char t_tmp[VL_VALUE_STRING_MAX_WIDTH];
    int floc = fbits - 1;
    IData got = 0;
    bool inPct = false;
    bool inIgnore = false;
    std::string::const_iterator pos = format.cbegin();
    for (; pos != format.cend(); ++pos) {
        // VL_DBG_MSGF("_vlscan fmt='%c' floc=%d file='%c'\n", pos[0], floc,
        // _vl_vsss_peek(fp, floc, fromp, fstr));
        if (!inPct && pos[0] == '%') {
            inPct = true;
            inIgnore = false;
        } else if (!inPct && std::isspace(pos[0])) {  // Format spaces
            while (std::isspace(pos[1])) ++pos;
            _vl_vsss_skipspace(fp, floc, fromp, fstr);
        } else if (!inPct) {  // Expected Format
            _vl_vsss_skipspace(fp, floc, fromp, fstr);
            const int c = _vl_vsss_peek(fp, floc, fromp, fstr);
            if (c != pos[0]) goto done;
            _vl_vsss_advance(fp, floc);
        } else {  // Format character
            // Skip loading spaces
            inPct = false;
            const char fmt = pos[0];
            switch (fmt) {
            case '%': {
                const int c = _vl_vsss_peek(fp, floc, fromp, fstr);
                if (c != '%') goto done;
                _vl_vsss_advance(fp, floc);
                break;
            }
            case '0':  // FALLTHRU
            case '1':  // FALLTHRU
            case '2':  // FALLTHRU
            case '3':  // FALLTHRU
            case '4':  // FALLTHRU
            case '5':  // FALLTHRU
            case '6':  // FALLTHRU
            case '7':  // FALLTHRU
            case '8':  // FALLTHRU
            case '9': {
                inPct = true;
                break;
            }
            case '*':
                inPct = true;
                inIgnore = true;
                break;
            default: {
                // Deal with all read-and-scan somethings
                // Note LSBs are preserved if there's an overflow
                int obits = inIgnore ? 0 : va_arg(ap, int);
                VlWide<VL_WQ_WORDS_E> qowp;
                VL_SET_WQ(qowp, 0ULL);
                WDataOutP owp = qowp;
                if (obits == -1) {  // string
                    owp = nullptr;
                    if (VL_UNCOVERABLE(fmt != 's')) {
                        VL_FATAL_MT(
                            __FILE__, __LINE__, "",
                            "Internal: format other than %s is passed to string");  // LCOV_EXCL_LINE
                    }
                } else if (obits > VL_QUADSIZE) {
                    owp = va_arg(ap, WDataOutP);
                }

                for (int i = 0; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
                switch (fmt) {
                case 'c': {
                    const int c = _vl_vsss_peek(fp, floc, fromp, fstr);
                    if (c == EOF) goto done;
                    _vl_vsss_advance(fp, floc);
                    owp[0] = c;
                    break;
                }
                case 's': {
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, nullptr);
                    if (!t_tmp[0]) goto done;
                    if (owp) {
                        int lpos = (static_cast<int>(std::strlen(t_tmp))) - 1;
                        int lsb = 0;
                        for (int i = 0; i < obits && lpos >= 0; --lpos) {
                            _vl_vsss_setbit(owp, obits, lsb, 8, t_tmp[lpos]);
                            lsb += 8;
                        }
                    }
                    break;
                }
                case 'd': {  // Signed decimal
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, "0123456789+-xXzZ?_");
                    if (!t_tmp[0]) goto done;
                    int64_t ld = 0;
                    std::sscanf(t_tmp, "%30" PRId64, &ld);
                    VL_SET_WQ(owp, ld);
                    break;
                }
                case 'f':
                case 'e':
                case 'g': {  // Real number
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, "+-.0123456789eE");
                    if (!t_tmp[0]) goto done;
                    union {
                        double r;
                        int64_t ld;
                    } u;
                    u.r = std::strtod(t_tmp, nullptr);
                    VL_SET_WQ(owp, u.ld);
                    break;
                }
                case 't': {  // Time
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, "+-.0123456789eE");
                    if (!t_tmp[0]) goto done;
                    union {
                        double r;
                        int64_t ld;
                    } u;
                    // Get pointer argument first, as proceeds the timeunit value
                    if (obits != 64) goto done;
                    QData* const realp = va_arg(ap, QData*);
                    const int timeunit = va_arg(ap, int);
                    const int userUnits
                        = Verilated::threadContextp()->impp()->timeFormatUnits();  // 0..-15
                    const int shift = -userUnits + timeunit;  // 0..-15
                    u.r = std::strtod(t_tmp, nullptr) * vl_time_multiplier(-shift);
                    *realp = VL_CLEAN_QQ(obits, obits, u.ld);
                    obits = 0;  // Already loaded the value, don't read arg
                    break;
                }
                case '#': {  // Unsigned decimal
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, "0123456789+-xXzZ?_");
                    if (!t_tmp[0]) goto done;
                    QData ld = 0;
                    std::sscanf(t_tmp, "%30" PRIu64, &ld);
                    VL_SET_WQ(owp, ld);
                    break;
                }
                case 'b': {
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, "01xXzZ?_");
                    if (!t_tmp[0]) goto done;
                    _vl_vsss_based(owp, obits, 1, t_tmp, 0, std::strlen(t_tmp));
                    break;
                }
                case 'o': {
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp, "01234567xXzZ?_");
                    if (!t_tmp[0]) goto done;
                    _vl_vsss_based(owp, obits, 3, t_tmp, 0, std::strlen(t_tmp));
                    break;
                }
                case 'x': {
                    _vl_vsss_skipspace(fp, floc, fromp, fstr);
                    _vl_vsss_read_str(fp, floc, fromp, fstr, t_tmp,
                                      "0123456789abcdefABCDEFxXzZ?_");
                    if (!t_tmp[0]) goto done;
                    _vl_vsss_based(owp, obits, 4, t_tmp, 0, std::strlen(t_tmp));
                    break;
                }
                case 'u': {
                    // Read packed 2-value binary data
                    const int bytes = VL_BYTES_I(obits);
                    char* const out = reinterpret_cast<char*>(owp);
                    if (!_vl_vsss_read_bin(fp, floc, fromp, fstr, out, bytes)) goto done;
                    const int last = bytes % 4;
                    if (last != 0
                        && !_vl_vsss_read_bin(fp, floc, fromp, fstr, out, 4 - last, true))
                        goto done;
                    break;
                }
                case 'z': {
                    // Read packed 4-value binary data
                    char* out = reinterpret_cast<char*>(owp);
                    int bytes = VL_BYTES_I(obits);
                    while (bytes > 0) {
                        const int abytes = std::min(4, bytes);
                        // aval (4B) read {0, 1} state
                        out = _vl_vsss_read_bin(fp, floc, fromp, fstr, out, abytes);
                        if (!out) goto done;
                        // bval (4B) disregard {X, Z} state and align to new 8B boundary.
                        out = _vl_vsss_read_bin(fp, floc, fromp, fstr, out, 8 - abytes, true);
                        if (!out) goto done;
                        bytes -= abytes;
                    }
                    break;
                }
                default: {  // LCOV_EXCL_START
                    const std::string msg = "Unknown _vl_vsscanf code: "s + pos[0];
                    VL_FATAL_MT(__FILE__, __LINE__, "", msg.c_str());
                    break;
                }  // LCOV_EXCL_STOP

                }  // switch

                if (!inIgnore) ++got;
                // Reload data if non-wide (if wide, we put it in the right place directly)
                if (obits == 0) {  // Due to inIgnore
                } else if (obits == -1) {  // string
                    std::string* const p = va_arg(ap, std::string*);
                    *p = t_tmp;
                } else if (obits <= VL_BYTESIZE) {
                    CData* const p = va_arg(ap, CData*);
                    *p = VL_CLEAN_II(obits, obits, owp[0]);
                } else if (obits <= VL_SHORTSIZE) {
                    SData* const p = va_arg(ap, SData*);
                    *p = VL_CLEAN_II(obits, obits, owp[0]);
                } else if (obits <= VL_IDATASIZE) {
                    IData* const p = va_arg(ap, IData*);
                    *p = VL_CLEAN_II(obits, obits, owp[0]);
                } else if (obits <= VL_QUADSIZE) {
                    QData* const p = va_arg(ap, QData*);
                    *p = VL_CLEAN_QQ(obits, obits, VL_SET_QW(owp));
                } else {
                    _vl_clean_inplace_w(obits, owp);
                }
            }
            }  // switch
        }
    }
    // Processed all arguments
    return got;

done:
    // Scan stopped early, return parsed or EOF
    if (_vl_vsss_eof(fp, floc)) return -1;
    return got;
}

//===========================================================================
// File I/O

FILE* VL_CVT_I_FP(IData lhs) VL_MT_SAFE {
    // Expected non-MCD case; returns null on MCD descriptors.
    return Verilated::threadContextp()->impp()->fdToFp(lhs);
}

void _vl_vint_to_string(int obits, char* destoutp, const WDataInP sourcep) VL_MT_SAFE {
    // See also VL_DATA_TO_STRING_NW
    int lsb = obits - 1;
    bool start = true;
    char* destp = destoutp;
    for (; lsb >= 0; --lsb) {
        lsb = (lsb / 8) * 8;  // Next digit
        const IData charval = VL_BITRSHIFT_W(sourcep, lsb) & 0xff;
        if (!start || charval) {
            *destp++ = (charval == 0) ? ' ' : charval;
            start = false;  // Drop leading 0s
        }
    }
    *destp = '\0';  // Terminate
    if (!start) {  // Drop trailing spaces
        while (std::isspace(*(destp - 1)) && destp > destoutp) *--destp = '\0';
    }
}

void _vl_string_to_vint(int obits, void* destp, size_t srclen, const char* srcp) VL_MT_SAFE {
    // Convert C string to Verilog format
    const size_t bytes = VL_BYTES_I(obits);
    char* op = reinterpret_cast<char*>(destp);
    if (srclen > bytes) srclen = bytes;  // Don't overflow destination
    size_t i = 0;
    for (i = 0; i < srclen; ++i) *op++ = srcp[srclen - 1 - i];
    for (; i < bytes; ++i) *op++ = 0;
}

static IData getLine(std::string& str, IData fpi, size_t maxLen) VL_MT_SAFE {
    str.clear();

    // While threadsafe, each thread can only access different file handles
    FILE* const fp = VL_CVT_I_FP(fpi);
    if (VL_UNLIKELY(!fp)) return 0;

    // We don't use fgets, as we must read \0s.
    while (str.size() < maxLen) {
        const int c = getc(fp);  // getc() is threadsafe
        if (c == EOF) break;
        str.push_back(c);
        if (c == '\n') break;
    }
    return static_cast<IData>(str.size());
}

IData VL_FGETS_IXI(int obits, void* destp, IData fpi) VL_MT_SAFE {
    std::string str;
    const IData bytes = VL_BYTES_I(obits);
    const IData got = getLine(str, fpi, bytes);

    if (VL_UNLIKELY(str.empty())) return 0;

    // V3Emit has static check that bytes < VL_VALUE_STRING_MAX_WORDS, but be safe
    if (VL_UNCOVERABLE(bytes < str.size())) {
        VL_FATAL_MT(__FILE__, __LINE__, "", "Internal: fgets buffer overrun");  // LCOV_EXCL_LINE
    }

    _vl_string_to_vint(obits, destp, got, str.data());
    return got;
}

IData VL_FGETS_NI(std::string& dest, IData fpi) VL_MT_SAFE {
    return getLine(dest, fpi, std::numeric_limits<size_t>::max());
}

IData VL_FERROR_IN(IData, std::string& outputr) VL_MT_SAFE {
    // We ignore lhs/fpi - IEEE says "most recent error" so probably good enough
    const IData ret = errno;
    outputr = std::string{::std::strerror(ret)};
    return ret;
}
IData VL_FERROR_IW(IData fpi, int obits, WDataOutP outwp) VL_MT_SAFE {
    std::string output;
    const IData ret = VL_FERROR_IN(fpi, output /*ref*/);
    _vl_string_to_vint(obits, outwp, output.length(), output.c_str());
    return ret;
}

IData VL_FOPEN_NN(const std::string& filename, const std::string& mode) {
    return Verilated::threadContextp()->impp()->fdNew(filename.c_str(), mode.c_str());
}
IData VL_FOPEN_MCD_N(const std::string& filename) VL_MT_SAFE {
    return Verilated::threadContextp()->impp()->fdNewMcd(filename.c_str());
}

void VL_FFLUSH_I(IData fdi) VL_MT_SAFE { Verilated::threadContextp()->impp()->fdFlush(fdi); }
IData VL_FSEEK_I(IData fdi, IData offset, IData origin) VL_MT_SAFE {
    return Verilated::threadContextp()->impp()->fdSeek(fdi, offset, origin);
}
IData VL_FTELL_I(IData fdi) VL_MT_SAFE { return Verilated::threadContextp()->impp()->fdTell(fdi); }
void VL_FCLOSE_I(IData fdi) VL_MT_SAFE {
    // While threadsafe, each thread can only access different file handles
    Verilated::threadContextp()->impp()->fdClose(fdi);
}

void VL_SFORMAT_NX(int obits, CData& destr, const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    _vl_string_to_vint(obits, &destr, t_output.length(), t_output.c_str());
}

void VL_SFORMAT_NX(int obits, SData& destr, const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    _vl_string_to_vint(obits, &destr, t_output.length(), t_output.c_str());
}

void VL_SFORMAT_NX(int obits, IData& destr, const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    _vl_string_to_vint(obits, &destr, t_output.length(), t_output.c_str());
}

void VL_SFORMAT_NX(int obits, QData& destr, const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    _vl_string_to_vint(obits, &destr, t_output.length(), t_output.c_str());
}

void VL_SFORMAT_NX(int obits, void* destp, const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    _vl_string_to_vint(obits, destp, t_output.length(), t_output.c_str());
}

void VL_SFORMAT_NX(int obits_ignored, std::string& output, const std::string& format, int argc,
                   ...) VL_MT_SAFE {
    (void)obits_ignored;  // So VL_SFORMAT_NNX function signatures all match
    std::string temp_output;
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(temp_output, format, ap);
    va_end(ap);
    output = temp_output;
}

std::string VL_SFORMATF_N_NX(const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    return t_output;
}

void VL_WRITEF_NX(const std::string& format, int argc, ...) VL_MT_SAFE {
    static thread_local std::string t_output;  // static only for speed
    t_output = "";
    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    VL_PRINTF_MT("%s", t_output.c_str());
}

void VL_FWRITEF_NX(IData fpi, const std::string& format, int argc, ...) VL_MT_SAFE {
    // While threadsafe, each thread can only access different file handles
    static thread_local std::string t_output;  // static only for speed
    t_output = "";

    va_list ap;
    va_start(ap, argc);
    _vl_vsformat(t_output, format, ap);
    va_end(ap);

    Verilated::threadContextp()->impp()->fdWrite(fpi, t_output);
}

IData VL_FSCANF_INX(IData fpi, const std::string& format, int argc, ...) VL_MT_SAFE {
    // While threadsafe, each thread can only access different file handles
    FILE* const fp = VL_CVT_I_FP(fpi);
    if (VL_UNLIKELY(!fp)) return ~0U;  // -1

    va_list ap;
    va_start(ap, argc);
    const IData got = _vl_vsscanf(fp, 0, nullptr, "", format, ap);
    va_end(ap);
    return got;
}

IData VL_SSCANF_IINX(int lbits, IData ld, const std::string& format, int argc, ...) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> fnw;
    VL_SET_WI(fnw, ld);

    va_list ap;
    va_start(ap, argc);
    const IData got = _vl_vsscanf(nullptr, lbits, fnw, "", format, ap);
    va_end(ap);
    return got;
}
IData VL_SSCANF_IQNX(int lbits, QData ld, const std::string& format, int argc, ...) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> fnw;
    VL_SET_WQ(fnw, ld);

    va_list ap;
    va_start(ap, argc);
    const IData got = _vl_vsscanf(nullptr, lbits, fnw, "", format, ap);
    va_end(ap);
    return got;
}
IData VL_SSCANF_IWNX(int lbits, const WDataInP lwp, const std::string& format, int argc,
                     ...) VL_MT_SAFE {
    va_list ap;
    va_start(ap, argc);
    const IData got = _vl_vsscanf(nullptr, lbits, lwp, "", format, ap);
    va_end(ap);
    return got;
}
IData VL_SSCANF_INNX(int, const std::string& ld, const std::string& format, int argc,
                     ...) VL_MT_SAFE {
    va_list ap;
    va_start(ap, argc);
    const IData got
        = _vl_vsscanf(nullptr, static_cast<int>(ld.length() * 8), nullptr, ld, format, ap);
    va_end(ap);
    return got;
}

// MurmurHash64A
uint64_t VL_MURMUR64_HASH(const char* key) VL_PURE {
    const size_t len = strlen(key);
    const uint64_t seed = 0;
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t* data = reinterpret_cast<const uint64_t*>(key);
    const uint64_t* end = data + (len / 8);

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char* data2 = reinterpret_cast<const unsigned char*>(data);

    switch (len & 7) {
    case 7: h ^= uint64_t(data2[6]) << 48; /* fallthrough */
    case 6: h ^= uint64_t(data2[5]) << 40; /* fallthrough */
    case 5: h ^= uint64_t(data2[4]) << 32; /* fallthrough */
    case 4: h ^= uint64_t(data2[3]) << 24; /* fallthrough */
    case 3: h ^= uint64_t(data2[2]) << 16; /* fallthrough */
    case 2: h ^= uint64_t(data2[1]) << 8; /* fallthrough */
    case 1: h ^= uint64_t(data2[0]); h *= m; /* fallthrough */
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

IData VL_FREAD_I(int width, int array_lsb, int array_size, void* memp, IData fpi, IData start,
                 IData count) VL_MT_SAFE {
    // While threadsafe, each thread can only access different file handles
    FILE* const fp = VL_CVT_I_FP(fpi);
    if (VL_UNLIKELY(!fp)) return 0;
    if (count > (array_size - (start - array_lsb))) count = array_size - (start - array_lsb);
    // Prep for reading
    IData read_count = 0;
    IData read_elements = 0;
    const int start_shift = (width - 1) & ~7;  // bit+7:bit gets first character
    int shift = start_shift;
    // Read the data
    // We process a character at a time, as then we don't need to deal
    // with changing buffer sizes dynamically, etc.
    while (true) {
        const int c = std::fgetc(fp);
        if (VL_UNLIKELY(c == EOF)) break;
        // Shift value in
        const IData entry = read_elements + start - array_lsb;
        if (width <= 8) {
            CData* const datap = &(reinterpret_cast<CData*>(memp))[entry];
            if (shift == start_shift) *datap = 0;
            *datap |= (c << shift) & VL_MASK_I(width);
        } else if (width <= 16) {
            SData* const datap = &(reinterpret_cast<SData*>(memp))[entry];
            if (shift == start_shift) *datap = 0;
            *datap |= (c << shift) & VL_MASK_I(width);
        } else if (width <= VL_IDATASIZE) {
            IData* const datap = &(reinterpret_cast<IData*>(memp))[entry];
            if (shift == start_shift) *datap = 0;
            *datap |= (c << shift) & VL_MASK_I(width);
        } else if (width <= VL_QUADSIZE) {
            QData* const datap = &(reinterpret_cast<QData*>(memp))[entry];
            if (shift == start_shift) *datap = 0;
            *datap |= ((static_cast<QData>(c) << static_cast<QData>(shift)) & VL_MASK_Q(width));
        } else {
            WDataOutP datap = &(reinterpret_cast<WDataOutP>(memp))[entry * VL_WORDS_I(width)];
            if (shift == start_shift) VL_ZERO_W(width, datap);
            datap[VL_BITWORD_E(shift)] |= (static_cast<EData>(c) << VL_BITBIT_E(shift));
        }
        // Prep for next
        ++read_count;
        shift -= 8;
        if (shift < 0) {
            shift = start_shift;
            ++read_elements;
            if (VL_UNLIKELY(read_elements >= count)) break;
        }
    }
    return read_count;
}

#ifdef _VL_HAVE_STACKTRACE
static std::string _vl_stacktrace_demangle(const std::string& input) VL_MT_SAFE {
    static VerilatedMutex s_demangleMutex;
    const VerilatedLockGuard lock{s_demangleMutex};

    std::string result;
    result.reserve(input.size());

    std::string word;
    for (const char c : input) {
        if (std::isalpha(c) || c == '_') {
            word += c;
        } else if (!word.empty() && std::isdigit(c)) {
            word += c;
        } else {
            if (!word.empty()) {
                // abi::__cxa_demangle mallocs demangled_name
                int status = 0;
                char* const demangled_name
                    = abi::__cxa_demangle(word.c_str(), NULL, NULL, &status);
                if (status == 0) {
                    result += std::string{demangled_name};
                    std::free(demangled_name);  // Free the allocated memory
                } else {
                    result += word;
                }
                word.clear();
            }
            result += c;
        }
    }
    // input requires final newline, so last word can't be symbol
    result += word;
    return result;
}
#endif

std::string VL_STACKTRACE_N() VL_MT_SAFE {
    static VerilatedMutex s_stackTraceMutex;
    const VerilatedLockGuard lock{s_stackTraceMutex};

#ifdef _VL_HAVE_STACKTRACE
    int nptrs = 0;
    char** strings = nullptr;

    constexpr int BT_BUF_SIZE = 100;
    void* buffer[BT_BUF_SIZE];
    nptrs = backtrace(buffer, BT_BUF_SIZE);
    strings = backtrace_symbols(buffer, nptrs);

    // cppcheck-suppress knownConditionTrueFalse
    if (!strings) return "Unable to backtrace, call failed\n";

    std::string result = "Backtrace:\n";
    for (int j = 0; j < nptrs; ++j)
        result += _vl_stacktrace_demangle(std::string{strings[j]} + "\n"s);

    free(strings);
    return result;
#else
    return "Unable to backtrace; not supported\n";
#endif
}

void VL_STACKTRACE() VL_MT_SAFE {
    const std::string result = VL_STACKTRACE_N();
    VL_PRINTF("%s", result.c_str());
}

IData VL_SYSTEM_IQ(QData lhs) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> lhsw;
    VL_SET_WQ(lhsw, lhs);
    return VL_SYSTEM_IW(VL_WQ_WORDS_E, lhsw);
}
IData VL_SYSTEM_IW(int lhswords, const WDataInP lhsp) VL_MT_SAFE {
    const std::string lhs = VL_CVT_PACK_STR_NW(lhswords, lhsp);
    return VL_SYSTEM_IN(lhs);
}
IData VL_SYSTEM_IN(const std::string& lhs) VL_MT_SAFE {
    const int code = std::system(lhs.c_str());  // Yes, std::system() is threadsafe
    return code >> 8;  // Want exit status
}

IData VL_TESTPLUSARGS_I(const std::string& format) VL_MT_SAFE {
    const std::string& match = Verilated::threadContextp()->impp()->argPlusMatch(format.c_str());
    return match.empty() ? 0 : 1;
}

IData VL_VALUEPLUSARGS_INW(int rbits, const std::string& ld, WDataOutP rwp) VL_MT_SAFE {
    std::string prefix;
    bool inPct = false;
    bool done = false;
    char fmt = ' ';
    for (const char* posp = ld.c_str(); !done && *posp; ++posp) {
        if (!inPct && posp[0] == '%') {
            inPct = true;
        } else if (!inPct) {  // Normal text
            prefix += *posp;
        } else if (*posp == '0') {  // %0
        } else {  // Format character
            switch (std::tolower(*posp)) {
            case '%':
                prefix += *posp;
                inPct = false;
                break;
            default:
                fmt = *posp;
                done = true;
                break;
            }
        }
    }

    const std::string& match = Verilated::threadContextp()->impp()->argPlusMatch(prefix.c_str());
    const char* const dp = match.c_str() + 1 /*leading + */ + prefix.length();
    if (match.empty()) return 0;

    VL_ZERO_W(rbits, rwp);
    switch (std::tolower(fmt)) {
    case 'd': {
        int64_t lld = 0;
        std::sscanf(dp, "%30" PRId64, &lld);
        VL_SET_WQ(rwp, lld);
        break;
    }
    case 'b': _vl_vsss_based(rwp, rbits, 1, dp, 0, std::strlen(dp)); break;
    case 'o': _vl_vsss_based(rwp, rbits, 3, dp, 0, std::strlen(dp)); break;
    case 'h':  // FALLTHRU
    case 'x': _vl_vsss_based(rwp, rbits, 4, dp, 0, std::strlen(dp)); break;
    case 's': {  // string/no conversion
        for (int i = 0, lsb = 0, posp = static_cast<int>(std::strlen(dp)) - 1;
             i < rbits && posp >= 0; --posp) {
            _vl_vsss_setbit(rwp, rbits, lsb, 8, dp[posp]);
            lsb += 8;
        }
        break;
    }
    case 'e': {
        double temp = 0.F;
        std::sscanf(dp, "%le", &temp);
        VL_SET_WQ(rwp, VL_CVT_Q_D(temp));
        break;
    }
    case 'f': {
        double temp = 0.F;
        std::sscanf(dp, "%lf", &temp);
        VL_SET_WQ(rwp, VL_CVT_Q_D(temp));
        break;
    }
    case 'g': {
        double temp = 0.F;
        std::sscanf(dp, "%lg", &temp);
        VL_SET_WQ(rwp, VL_CVT_Q_D(temp));
        break;
    }
    default:  // Other simulators return 0 in these cases and don't error out
        return 0;
    }
    _vl_clean_inplace_w(rbits, rwp);
    return 1;
}
IData VL_VALUEPLUSARGS_INN(int, const std::string& ld, std::string& rdr) VL_MT_SAFE {
    std::string prefix;
    bool inPct = false;
    bool done = false;
    for (const char* posp = ld.c_str(); !done && *posp; ++posp) {
        if (!inPct && posp[0] == '%') {
            inPct = true;
        } else if (!inPct) {  // Normal text
            prefix += *posp;
        } else {  // Format character
            switch (std::tolower(*posp)) {
            case '%':
                prefix += *posp;
                inPct = false;
                break;
            default:  //
                done = true;
                break;
            }
        }
    }
    const std::string& match = Verilated::threadContextp()->impp()->argPlusMatch(prefix.c_str());
    const char* const dp = match.c_str() + 1 /*leading + */ + prefix.length();
    if (match.empty()) return 0;
    rdr = std::string{dp};
    return 1;
}

const char* vl_mc_scan_plusargs(const char* prefixp) VL_MT_SAFE {
    const std::string& match = Verilated::threadContextp()->impp()->argPlusMatch(prefixp);
    static thread_local char t_outstr[VL_VALUE_STRING_MAX_WIDTH];
    if (match.empty()) return nullptr;
    char* dp = t_outstr;
    for (const char* sp = match.c_str() + std::strlen(prefixp) + 1;  // +1 to skip the "+"
         *sp && (dp - t_outstr) < (VL_VALUE_STRING_MAX_WIDTH - 2);)
        *dp++ = *sp++;
    *dp++ = '\0';
    return t_outstr;
}

//===========================================================================
// Heavy string functions

std::string VL_TO_STRING(CData lhs) { return VL_SFORMATF_N_NX("'h%0x", 0, 8, lhs); }
std::string VL_TO_STRING(SData lhs) { return VL_SFORMATF_N_NX("'h%0x", 0, 16, lhs); }
std::string VL_TO_STRING(IData lhs) { return VL_SFORMATF_N_NX("'h%0x", 0, 32, lhs); }
std::string VL_TO_STRING(QData lhs) { return VL_SFORMATF_N_NX("'h%0x", 0, 64, lhs); }
std::string VL_TO_STRING(double lhs) { return VL_SFORMATF_N_NX("%g", 0, 64, lhs); }
std::string VL_TO_STRING_W(int words, const WDataInP obj) {
    return VL_SFORMATF_N_NX("'h%0x", 0, words * VL_EDATASIZE, obj);
}

std::string VL_TOLOWER_NN(const std::string& ld) VL_PURE {
    std::string result = ld;
    for (auto& cr : result) cr = std::tolower(cr);
    return result;
}
std::string VL_TOUPPER_NN(const std::string& ld) VL_PURE {
    std::string result = ld;
    for (auto& cr : result) cr = std::toupper(cr);
    return result;
}

std::string VL_CVT_PACK_STR_NW(int lwords, const WDataInP lwp) VL_PURE {
    // See also _vl_vint_to_string
    std::string result;
    result.reserve((lwords * VL_EDATASIZE) / 8 + 1);
    const int obits = lwords * VL_EDATASIZE;
    int lsb = obits - 1;
    for (; lsb >= 0; --lsb) {
        lsb = (lsb / 8) * 8;  // Next digit
        const IData charval = VL_BITRSHIFT_W(lwp, lsb) & 0xff;
        if (charval) result += static_cast<char>(charval);
    }
    return result;
}

std::string VL_CVT_PACK_STR_ND(const VlQueue<std::string>& q) VL_PURE {
    std::string output;
    for (const std::string& s : q) output += s;
    return output;
}

std::string VL_PUTC_N(const std::string& lhs, IData rhs, CData ths) VL_PURE {
    std::string lstring = lhs;
    const int32_t rhs_s = rhs;  // To signed value
    // 6.16.2:str.putc(i, c) does not change the value when i < 0 || i >= str.len() || c == 0
    if (0 <= rhs_s && rhs < lhs.length() && ths != 0) lstring[rhs] = ths;
    return lstring;
}

CData VL_GETC_N(const std::string& lhs, IData rhs) VL_PURE {
    CData v = 0;
    const int32_t rhs_s = rhs;  // To signed value
    // 6.16.3:str.getc(i) returns 0 if i < 0 || i >= str.len()
    if (0 <= rhs_s && rhs < lhs.length()) v = lhs[rhs];
    return v;
}

std::string VL_SUBSTR_N(const std::string& lhs, IData rhs, IData ths) VL_PURE {
    const int32_t rhs_s = rhs;  // To signed value
    const int32_t ths_s = ths;  // To signed value
    // 6.16.8:str.substr(i, j) returns an empty string when i < 0 || j < i || j >= str.len()
    if (rhs_s < 0 || ths_s < rhs_s || ths >= lhs.length()) return "";
    // Second parameter of std::string::substr(i, n) is length, not position as in SystemVerilog
    return lhs.substr(rhs, ths - rhs + 1);
}

IData VL_ATOI_N(const std::string& str, int base) VL_PURE {
    std::string str_mod = str;
    // IEEE 1800-2023 6.16.9 says '_' may exist.
    str_mod.erase(std::remove(str_mod.begin(), str_mod.end(), '_'), str_mod.end());

    errno = 0;
    auto v = std::strtol(str_mod.c_str(), nullptr, base);
    if (errno != 0) v = 0;
    return static_cast<IData>(v);
}
IData VL_NTOI_I(int obits, const std::string& str) VL_PURE { return VL_NTOI_Q(obits, str); }
QData VL_NTOI_Q(int obits, const std::string& str) VL_PURE {
    QData out = 0;
    const char* const datap = str.data();
    int pos = static_cast<int>(str.length()) - 1;
    int bit = 0;
    while (bit < obits && pos >= 0) {
        out |= static_cast<QData>(datap[pos]) << VL_BITBIT_Q(bit);
        bit += 8;
        --pos;
    }
    return out & VL_MASK_Q(obits);
}
void VL_NTOI_W(int obits, WDataOutP owp, const std::string& str) VL_PURE {
    const int words = VL_WORDS_I(obits);
    for (int i = 0; i < words; ++i) owp[i] = 0;
    const char* const datap = str.data();
    int pos = static_cast<int>(str.length()) - 1;
    int bit = 0;
    while (bit < obits && pos >= 0) {
        owp[VL_BITWORD_I(bit)] |= static_cast<EData>(datap[pos]) << VL_BITBIT_I(bit);
        bit += 8;
        --pos;
    }
    owp[words - 1] &= VL_MASK_E(obits);
}

//===========================================================================
// Readmem/writemem

static const char* memhFormat(int nBits) {
    assert((nBits >= 1) && (nBits <= 32));

    static thread_local char t_buf[32];
    switch ((nBits - 1) / 4) {
    case 0: VL_SNPRINTF(t_buf, 32, "%%01x"); break;
    case 1: VL_SNPRINTF(t_buf, 32, "%%02x"); break;
    case 2: VL_SNPRINTF(t_buf, 32, "%%03x"); break;
    case 3: VL_SNPRINTF(t_buf, 32, "%%04x"); break;
    case 4: VL_SNPRINTF(t_buf, 32, "%%05x"); break;
    case 5: VL_SNPRINTF(t_buf, 32, "%%06x"); break;
    case 6: VL_SNPRINTF(t_buf, 32, "%%07x"); break;
    case 7: VL_SNPRINTF(t_buf, 32, "%%08x"); break;
    default: assert(false); break;  // LCOV_EXCL_LINE
    }
    return t_buf;
}

static const char* formatBinary(int nBits, uint32_t bits) {
    assert((nBits >= 1) && (nBits <= 32));

    static thread_local char t_buf[64];
    for (int i = 0; i < nBits; ++i) {
        const bool isOne = bits & (1 << (nBits - 1 - i));
        t_buf[i] = (isOne ? '1' : '0');
    }
    t_buf[nBits] = '\0';
    return t_buf;
}

VlReadMem::VlReadMem(bool hex, int bits, const std::string& filename, QData start, QData end)
    : m_hex{hex}
    , m_bits{bits}
    , m_filename(filename)  // Need () or GCC 4.8 false warning
    , m_end{end}
    , m_addr{start} {
    m_fp = std::fopen(filename.c_str(), "r");
    if (VL_UNLIKELY(!m_fp)) {
        // We don't report the Verilog source filename as it slow to have to pass it down
        VL_WARN_MT(filename.c_str(), 0, "", "$readmem file not found");
        return;
    }
}
VlReadMem::~VlReadMem() {
    if (m_fp) {
        std::fclose(m_fp);
        m_fp = nullptr;
    }
}
bool VlReadMem::get(QData& addrr, std::string& valuer) {
    if (VL_UNLIKELY(!m_fp)) return false;
    valuer = "";
    // Prep for reading
    bool inData = false;
    bool ignoreToEol = false;
    bool ignoreToComment = false;
    bool readingAddress = false;
    int lastCh = ' ';
    // Read the data
    // We process a character at a time, as then we don't need to deal
    // with changing buffer sizes dynamically, etc.
    while (true) {
        int c = std::fgetc(m_fp);
        if (VL_UNLIKELY(c == EOF)) break;
        const bool chIs4StateBin
            = c == '0' || c == '1' || c == 'x' || c == 'X' || c == 'z' || c == 'Z';
        const bool chIs2StateHex = std::isxdigit(c);
        const bool chIs4StateHex = std::isxdigit(c) || chIs4StateBin;
        // printf("%d: Got '%c' Addr%lx IN%d IgE%d IgC%d\n",
        //        m_linenum, c, m_addr, inData, ignoreToEol, ignoreToComment);
        // See if previous data value has completed, and if so return
        if (c == '_') continue;  // Ignore _ e.g. inside a number
        if (inData && !chIs4StateHex) {
            // printf("Got data @%lx = %s\n", m_addr, valuer.c_str());
            ungetc(c, m_fp);
            addrr = m_addr;
            ++m_addr;
            return true;
        }
        // Parse line
        if (c == '\n') {
            ++m_linenum;
            ignoreToEol = false;
            readingAddress = false;
        } else if (c == '\t' || c == ' ' || c == '\r' || c == '\f') {
            readingAddress = false;
        }
        // Skip // comments and detect /* comments
        else if (ignoreToComment && lastCh == '*' && c == '/') {
            ignoreToComment = false;
            readingAddress = false;
        } else if (!ignoreToEol && !ignoreToComment) {
            if (lastCh == '/' && c == '*') {
                ignoreToComment = true;
            } else if (lastCh == '/' && c == '/') {
                ignoreToEol = true;
            } else if (c == '/') {  // Part of /* or //
            } else if (c == '#') {
                ignoreToEol = true;
            } else if (c == '@') {
                readingAddress = true;
                m_anyAddr = true;
                m_addr = 0;
            } else if (readingAddress && chIs2StateHex) {
                c = std::tolower(c);
                const int addressValue = (c >= 'a') ? (c - 'a' + 10) : (c - '0');
                m_addr = (m_addr << 4) + addressValue;
            } else if (readingAddress && chIs4StateHex) {
                VL_FATAL_MT(m_filename.c_str(), m_linenum, "",
                            "$readmem address contains 4-state characters");
            } else if (chIs4StateHex) {
                inData = true;
                valuer += static_cast<char>(c);
                if (VL_UNLIKELY(!m_hex && !chIs4StateBin)) {
                    VL_FATAL_MT(m_filename.c_str(), m_linenum, "",
                                "$readmemb (binary) file contains hex characters");
                }
            } else {
                VL_FATAL_MT(m_filename.c_str(), m_linenum, "", "$readmem file syntax error");
            }
        }
        lastCh = c;
    }

    if (VL_UNLIKELY(m_end != ~0ULL && m_addr <= m_end && !m_anyAddr)) {
        VL_WARN_MT(m_filename.c_str(), m_linenum, "",
                   "$readmem file ended before specified final address (IEEE 1800-2023 21.4)");
    }

    addrr = m_addr;
    return inData;  // EOF
}
void VlReadMem::setData(void* valuep, const std::string& rhs) {
    const QData shift = m_hex ? 4ULL : 1ULL;
    bool innum = false;
    // Shift value in
    for (const auto& i : rhs) {
        const char c = std::tolower(i);
        const int value = (c == 'x' || c == 'z') ? VL_RAND_RESET_I(m_hex ? 4 : 1)
                          : (c >= 'a')           ? (c - 'a' + 10)
                                                 : (c - '0');
        if (m_bits <= 8) {
            CData* const datap = reinterpret_cast<CData*>(valuep);
            if (!innum) *datap = 0;
            *datap = ((*datap << shift) + value) & VL_MASK_I(m_bits);
        } else if (m_bits <= 16) {
            SData* const datap = reinterpret_cast<SData*>(valuep);
            if (!innum) *datap = 0;
            *datap = ((*datap << shift) + value) & VL_MASK_I(m_bits);
        } else if (m_bits <= VL_IDATASIZE) {
            IData* const datap = reinterpret_cast<IData*>(valuep);
            if (!innum) *datap = 0;
            *datap = ((*datap << shift) + value) & VL_MASK_I(m_bits);
        } else if (m_bits <= VL_QUADSIZE) {
            QData* const datap = reinterpret_cast<QData*>(valuep);
            if (!innum) *datap = 0;
            *datap = ((*datap << static_cast<QData>(shift)) + static_cast<QData>(value))
                     & VL_MASK_Q(m_bits);
        } else {
            WDataOutP datap = reinterpret_cast<WDataOutP>(valuep);
            if (!innum) VL_ZERO_W(m_bits, datap);
            _vl_shiftl_inplace_w(m_bits, datap, static_cast<IData>(shift));
            datap[0] |= value;
        }
        innum = true;
    }
}

VlWriteMem::VlWriteMem(bool hex, int bits, const std::string& filename, QData start, QData end)
    : m_hex{hex}
    , m_bits{bits} {
    if (VL_UNLIKELY(start > end)) {
        VL_FATAL_MT(filename.c_str(), 0, "", "$writemem invalid address range");
        return;
    }

    m_fp = std::fopen(filename.c_str(), "w");
    if (VL_UNLIKELY(!m_fp)) {
        VL_FATAL_MT(filename.c_str(), 0, "", "$writemem file not found");
        return;
    }
}
VlWriteMem::~VlWriteMem() {
    if (m_fp) {
        std::fclose(m_fp);
        m_fp = nullptr;
    }
}
void VlWriteMem::print(QData addr, bool addrstamp, const void* valuep) {
    if (VL_UNLIKELY(!m_fp)) return;
    if (addr != m_addr && addrstamp) {  // Only assoc has time stamps
        fprintf(m_fp, "@%" PRIx64 "\n", addr);
    }
    m_addr = addr + 1;
    if (m_bits <= 8) {
        const CData* const datap = reinterpret_cast<const CData*>(valuep);
        if (m_hex) {
            fprintf(m_fp, memhFormat(m_bits), VL_MASK_I(m_bits) & *datap);
            fprintf(m_fp, "\n");
        } else {
            fprintf(m_fp, "%s\n", formatBinary(m_bits, *datap));
        }
    } else if (m_bits <= 16) {
        const SData* const datap = reinterpret_cast<const SData*>(valuep);
        if (m_hex) {
            fprintf(m_fp, memhFormat(m_bits), VL_MASK_I(m_bits) & *datap);
            fprintf(m_fp, "\n");
        } else {
            fprintf(m_fp, "%s\n", formatBinary(m_bits, *datap));
        }
    } else if (m_bits <= 32) {
        const IData* const datap = reinterpret_cast<const IData*>(valuep);
        if (m_hex) {
            fprintf(m_fp, memhFormat(m_bits), VL_MASK_I(m_bits) & *datap);
            fprintf(m_fp, "\n");
        } else {
            fprintf(m_fp, "%s\n", formatBinary(m_bits, *datap));
        }
    } else if (m_bits <= 64) {
        const QData* const datap = reinterpret_cast<const QData*>(valuep);
        const uint64_t value = VL_MASK_Q(m_bits) & *datap;
        const uint32_t lo = value & 0xffffffff;
        const uint32_t hi = value >> 32;
        if (m_hex) {
            fprintf(m_fp, memhFormat(m_bits - 32), hi);
            fprintf(m_fp, "%08x\n", lo);
        } else {
            fprintf(m_fp, "%s", formatBinary(m_bits - 32, hi));
            fprintf(m_fp, "%s\n", formatBinary(32, lo));
        }
    } else {
        const WDataInP datap = reinterpret_cast<WDataInP>(valuep);
        // output as a sequence of VL_EDATASIZE'd words
        // from MSB to LSB. Mask off the MSB word which could
        // contain junk above the top of valid data.
        int word_idx = ((m_bits - 1) / VL_EDATASIZE);
        bool first = true;
        while (word_idx >= 0) {
            EData data = datap[word_idx];
            if (first) {
                data &= VL_MASK_E(m_bits);
                const int top_word_nbits = VL_BITBIT_E(m_bits - 1) + 1;
                if (m_hex) {
                    fprintf(m_fp, memhFormat(top_word_nbits), data);
                } else {
                    fprintf(m_fp, "%s", formatBinary(top_word_nbits, data));
                }
            } else {
                if (m_hex) {
                    fprintf(m_fp, "%08x", data);
                } else {
                    fprintf(m_fp, "%s", formatBinary(32, data));
                }
            }
            --word_idx;
            first = false;
        }
        fprintf(m_fp, "\n");
    }
}

void VL_READMEM_N(bool hex,  // Hex format, else binary
                  int bits,  // M_Bits of each array row
                  QData depth,  // Number of rows
                  int array_lsb,  // Index of first row. Valid row addresses
                  //              //  range from array_lsb up to (array_lsb + depth - 1)
                  const std::string& filename,  // Input file name
                  void* memp,  // Array state
                  QData start,  // First array row address to read
                  QData end  // Last row address to read
                  ) VL_MT_SAFE {
    if (start < static_cast<QData>(array_lsb)) start = array_lsb;

    VlReadMem rmem{hex, bits, filename, start, end};
    if (VL_UNLIKELY(!rmem.isOpen())) return;
    while (true) {
        QData addr = 0;
        std::string value;
        if (rmem.get(addr /*ref*/, value /*ref*/)) {
            // printf("readmem.get [%" PRIu64 "]=%s\n", addr, value.c_str());
            if (VL_UNLIKELY(addr < static_cast<QData>(array_lsb)
                            || addr >= static_cast<QData>(array_lsb + depth))) {
                VL_FATAL_MT(filename.c_str(), rmem.linenum(), "",
                            "$readmem file address beyond bounds of array");
            } else {
                const QData entry = addr - array_lsb;
                if (bits <= 8) {
                    CData* const datap = &(reinterpret_cast<CData*>(memp))[entry];
                    rmem.setData(datap, value);
                } else if (bits <= 16) {
                    SData* const datap = &(reinterpret_cast<SData*>(memp))[entry];
                    rmem.setData(datap, value);
                } else if (bits <= VL_IDATASIZE) {
                    IData* const datap = &(reinterpret_cast<IData*>(memp))[entry];
                    rmem.setData(datap, value);
                } else if (bits <= VL_QUADSIZE) {
                    QData* const datap = &(reinterpret_cast<QData*>(memp))[entry];
                    rmem.setData(datap, value);
                } else {
                    WDataOutP datap
                        = &(reinterpret_cast<WDataOutP>(memp))[entry * VL_WORDS_I(bits)];
                    rmem.setData(datap, value);
                }
            }
        } else {
            break;
        }
    }
}

void VL_WRITEMEM_N(bool hex,  // Hex format, else binary
                   int bits,  // Width of each array row
                   QData depth,  // Number of rows
                   int array_lsb,  // Index of first row. Valid row addresses
                   //              //  range from array_lsb up to (array_lsb + depth - 1)
                   const std::string& filename,  // Output file name
                   const void* memp,  // Array state
                   QData start,  // First array row address to write
                   QData end  // Last address to write, or ~0 when not specified
                   ) VL_MT_SAFE {
    const QData addr_max = array_lsb + depth - 1;
    if (start < static_cast<QData>(array_lsb)) start = array_lsb;
    if (end > addr_max) end = addr_max;

    VlWriteMem wmem{hex, bits, filename, start, end};
    if (VL_UNLIKELY(!wmem.isOpen())) return;

    for (QData addr = start; addr <= end; ++addr) {
        const QData row_offset = addr - array_lsb;
        if (bits <= 8) {
            const CData* const datap = &(reinterpret_cast<const CData*>(memp))[row_offset];
            wmem.print(addr, false, datap);
        } else if (bits <= 16) {
            const SData* const datap = &(reinterpret_cast<const SData*>(memp))[row_offset];
            wmem.print(addr, false, datap);
        } else if (bits <= 32) {
            const IData* const datap = &(reinterpret_cast<const IData*>(memp))[row_offset];
            wmem.print(addr, false, datap);
        } else if (bits <= 64) {
            const QData* const datap = &(reinterpret_cast<const QData*>(memp))[row_offset];
            wmem.print(addr, false, datap);
        } else {
            const WDataInP memDatap = reinterpret_cast<WDataInP>(memp);
            const WDataInP datap = &memDatap[row_offset * VL_WORDS_I(bits)];
            wmem.print(addr, false, datap);
        }
    }
}

//===========================================================================
// Timescale conversion

static const char* vl_time_str(int scale) VL_PURE {
    static const char* const s_names[]
        = {"100s",  "10s",  "1s",  "100ms", "10ms", "1ms", "100us", "10us", "1us",
           "100ns", "10ns", "1ns", "100ps", "10ps", "1ps", "100fs", "10fs", "1fs"};
    if (VL_UNLIKELY(scale > 2 || scale < -15)) scale = 0;
    return s_names[2 - scale];
}
double vl_time_multiplier(int scale) VL_PURE {
    // Return timescale multiplier -18 to +18
    // For speed, this does not check for illegal values
    if (scale < 0) {
        static const double neg10[] = {1.0,
                                       0.1,
                                       0.01,
                                       0.001,
                                       0.0001,
                                       0.00001,
                                       0.000001,
                                       0.0000001,
                                       0.00000001,
                                       0.000000001,
                                       0.0000000001,
                                       0.00000000001,
                                       0.000000000001,
                                       0.0000000000001,
                                       0.00000000000001,
                                       0.000000000000001,
                                       0.0000000000000001,
                                       0.00000000000000001,
                                       0.000000000000000001};
        return neg10[-scale];
    } else {
        static const double pow10[] = {1.0,
                                       10.0,
                                       100.0,
                                       1000.0,
                                       10000.0,
                                       100000.0,
                                       1000000.0,
                                       10000000.0,
                                       100000000.0,
                                       1000000000.0,
                                       10000000000.0,
                                       100000000000.0,
                                       1000000000000.0,
                                       10000000000000.0,
                                       100000000000000.0,
                                       1000000000000000.0,
                                       10000000000000000.0,
                                       100000000000000000.0,
                                       1000000000000000000.0};
        return pow10[scale];
    }
}
uint64_t vl_time_pow10(int n) {
    static const uint64_t pow10[20] = {
        1ULL,
        10ULL,
        100ULL,
        1000ULL,
        10000ULL,
        100000ULL,
        1000000ULL,
        10000000ULL,
        100000000ULL,
        1000000000ULL,
        10000000000ULL,
        100000000000ULL,
        1000000000000ULL,
        10000000000000ULL,
        100000000000000ULL,
        1000000000000000ULL,
        10000000000000000ULL,
        100000000000000000ULL,
        1000000000000000000ULL,
    };
    return pow10[n];
}

std::string vl_timescaled_double(double value, const char* format) VL_PURE {
    const char* suffixp = "s";
    // clang-format off
    if      (value >= 1e0)   { suffixp = "s"; value *= 1e0; }
    else if (value >= 1e-3)  { suffixp = "ms"; value *= 1e3; }
    else if (value >= 1e-6)  { suffixp = "us"; value *= 1e6; }
    else if (value >= 1e-9)  { suffixp = "ns"; value *= 1e9; }
    else if (value >= 1e-12) { suffixp = "ps"; value *= 1e12; }
    else if (value >= 1e-15) { suffixp = "fs"; value *= 1e15; }
    else if (value >= 1e-18) { suffixp = "as"; value *= 1e18; }
    // clang-format on
    char valuestr[100];
    VL_SNPRINTF(valuestr, 100, format, value, suffixp);
    return std::string{valuestr};  // Gets converted to string, so no ref to stack
}

void VL_PRINTTIMESCALE(const char* namep, const char* timeunitp,
                       const VerilatedContext* contextp) VL_MT_SAFE {
    VL_PRINTF_MT("Time scale of %s is %s / %s\n", namep, timeunitp,
                 contextp->timeprecisionString());
}
void VL_TIMEFORMAT_IINI(bool hasUnits, int units, bool hasPrecision, int precision, bool hasSuffix,
                        const std::string& suffix, bool hasWidth, int width,
                        VerilatedContext* contextp) VL_MT_SAFE {
    if (hasUnits) contextp->impp()->timeFormatUnits(units);
    if (hasPrecision) contextp->impp()->timeFormatPrecision(precision);
    if (hasSuffix) contextp->impp()->timeFormatSuffix(suffix);
    if (hasWidth) contextp->impp()->timeFormatWidth(width);
}

//======================================================================
// VerilatedContext:: Methods

VerilatedContext::VerilatedContext()
    : m_impdatap{new VerilatedContextImpData} {
    Verilated::lastContextp(this);
    Verilated::threadContextp(this);
    m_ns.m_coverageFilename = "coverage.dat";
    m_ns.m_profExecFilename = "profile_exec.dat";
    m_ns.m_profVltFilename = "profile.vlt";
    m_ns.m_solverProgram = VlOs::getenvStr("VERILATOR_SOLVER", VL_SOLVER_DEFAULT);
    m_fdps.resize(31);
    std::fill(m_fdps.begin(), m_fdps.end(), static_cast<FILE*>(nullptr));
    m_fdFreeMct.resize(30);
    IData id = 1;
    for (std::size_t i = 0; i < m_fdFreeMct.size(); ++i, ++id) m_fdFreeMct[i] = id;
}

// Must declare here not in interface, as otherwise forward declarations not known
VerilatedContext::~VerilatedContext() {
    checkMagic(this);
    m_magic = 0x1;  // Arbitrary but 0x1 is what Verilator src uses for a deleted pointer
}

void VerilatedContext::checkMagic(const VerilatedContext* contextp) {
    if (VL_UNLIKELY(!contextp || contextp->m_magic != MAGIC)) {
        VL_FATAL_MT("", 0, "",  // LCOV_EXCL_LINE
                    "Attempt to create model using a bad/deleted VerilatedContext pointer");
    }
}

VerilatedContext::Serialized::Serialized() {
    constexpr int8_t picosecond = -12;
    m_timeunit = picosecond;  // Initial value until overridden by _Vconfigure
    m_timeprecision = picosecond;  // Initial value until overridden by _Vconfigure
}

bool VerilatedContext::assertOn() const VL_MT_SAFE { return m_s.m_assertOn; }
void VerilatedContext::assertOn(bool flag) VL_MT_SAFE {
    // Set all assert and directive types when true, clear otherwise.
    m_s.m_assertOn = VL_MASK_I(ASSERT_ON_WIDTH) * flag;
}
bool VerilatedContext::assertOnGet(VerilatedAssertType_t type,
                                   VerilatedAssertDirectiveType_t directive) const VL_MT_SAFE {
    // Check if selected directive type bit in the assertOn is enabled for assertion type.
    // Note: it is assumed that this is checked only for one type at the time.

    // Flag unspecified assertion types as disabled.
    if (type == 0) return false;

    // Get index of 3-bit group guarding assertion type status.
    // Since the assertOnGet is generated __always__ for a single assert type, we assume that only
    // a single bit will be set. Thus, ceil log2 will work fine.
    VL_DEBUG_IFDEF(assert((type & (type - 1)) == 0););
    const IData typeMaskPosition = VL_CLOG2_I(type);

    // Check if directive type bit is enabled in corresponding assertion type bits.
    return m_s.m_assertOn & (directive << (typeMaskPosition * ASSERT_DIRECTIVE_TYPE_MASK_WIDTH));
}
void VerilatedContext::assertOnSet(VerilatedAssertType_t types,
                                   VerilatedAssertDirectiveType_t directives) VL_MT_SAFE {
    // For each assertion type, set directive bits.

    // Iterate through all positions of assertion type bits. If bit for this assertion type is set,
    // set directive type bits mask at this group index.
    for (int i = 0; i < std::numeric_limits<VerilatedAssertType_t>::digits; ++i) {
        if (VL_BITISSET_I(types, i))
            m_s.m_assertOn |= directives << (i * ASSERT_DIRECTIVE_TYPE_MASK_WIDTH);
    }
}
void VerilatedContext::assertOnClear(VerilatedAssertType_t types,
                                     VerilatedAssertDirectiveType_t directives) VL_MT_SAFE {
    // Iterate through all positions of assertion type bits. If bit for this assertion type is set,
    // clear directive type bits mask at this group index.
    for (int i = 0; i < std::numeric_limits<VerilatedAssertType_t>::digits; ++i) {
        if (VL_BITISSET_I(types, i))
            m_s.m_assertOn &= ~(directives << (i * ASSERT_DIRECTIVE_TYPE_MASK_WIDTH));
    }
}
void VerilatedContext::calcUnusedSigs(bool flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_calcUnusedSigs = flag;
}
void VerilatedContext::coverageFilename(const std::string& flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_coverageFilename = flag;
}
std::string VerilatedContext::coverageFilename() const VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    return m_ns.m_coverageFilename;
}
void VerilatedContext::dumpfile(const std::string& flag) VL_MT_SAFE_EXCLUDES(m_timeDumpMutex) {
    const VerilatedLockGuard lock{m_timeDumpMutex};
    m_dumpfile = flag;
}
std::string VerilatedContext::dumpfile() const VL_MT_SAFE_EXCLUDES(m_timeDumpMutex) {
    const VerilatedLockGuard lock{m_timeDumpMutex};
    return m_dumpfile;
}
std::string VerilatedContext::dumpfileCheck() const VL_MT_SAFE_EXCLUDES(m_timeDumpMutex) {
    std::string out = dumpfile();
    if (VL_UNLIKELY(out.empty())) {
        VL_PRINTF_MT("%%Warning: $dumpvar ignored as not preceded by $dumpfile\n");
        return "";
    }
    return out;
}
void VerilatedContext::errorCount(int val) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_errorCount = val;
}
void VerilatedContext::errorCountInc() VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    ++m_s.m_errorCount;
}
void VerilatedContext::errorLimit(int val) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_errorLimit = val;
}
void VerilatedContext::fatalOnError(bool flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_fatalOnError = flag;
}
void VerilatedContext::fatalOnVpiError(bool flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_fatalOnVpiError = flag;
}
void VerilatedContext::gotError(bool flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_gotError = flag;
}
void VerilatedContext::gotFinish(bool flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_gotFinish = flag;
}
void VerilatedContext::profExecStart(uint64_t flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_profExecStart = flag;
}
void VerilatedContext::profExecWindow(uint64_t flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_profExecWindow = flag;
}
void VerilatedContext::profExecFilename(const std::string& flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_profExecFilename = flag;
}
std::string VerilatedContext::profExecFilename() const VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    return m_ns.m_profExecFilename;
}
void VerilatedContext::profVltFilename(const std::string& flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_profVltFilename = flag;
}
std::string VerilatedContext::profVltFilename() const VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    return m_ns.m_profVltFilename;
}
void VerilatedContext::solverProgram(const std::string& flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_solverProgram = flag;
}
std::string VerilatedContext::solverProgram() const VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    return m_ns.m_solverProgram;
}
void VerilatedContext::quiet(bool flag) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_quiet = flag;
}
void VerilatedContext::randReset(int val) VL_MT_SAFE {
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_randReset = val;
}
void VerilatedContext::timeunit(int value) VL_MT_SAFE {
    if (value < 0) value = -value;  // Stored as 0..15
    const VerilatedLockGuard lock{m_mutex};
    m_s.m_timeunit = value;
}
const char* VerilatedContext::timeunitString() const VL_MT_SAFE { return vl_time_str(timeunit()); }
const char* VerilatedContext::timeprecisionString() const VL_MT_SAFE {
    return vl_time_str(timeprecision());
}

void VerilatedContext::threads(unsigned n) {
    if (n == 0) VL_FATAL_MT(__FILE__, __LINE__, "", "Simulation threads must be >= 1");

    if (m_threadPool) {
        VL_FATAL_MT(
            __FILE__, __LINE__, "",
            "%Error: Cannot set simulation threads after the thread pool has been created.");
    }

    m_useNumaAssign = true;
    if (m_threads == n) return;  // To avoid unnecessary warnings
    m_threads = n;
    const unsigned threadsAvailableToProcess = VlOs::getProcessDefaultParallelism();
    if (m_threads > threadsAvailableToProcess) {
        VL_PRINTF_MT("%%Warning: Process has %u hardware threads available, but simulation thread "
                     "count set to %u. This will likely cause significant slowdown.\n",
                     threadsAvailableToProcess, m_threads);
    }
}

void VerilatedContext::useNumaAssign(bool flag) { m_useNumaAssign = flag; }

void VerilatedContext::commandArgs(int argc, const char** argv) VL_MT_SAFE_EXCLUDES(m_argMutex) {
    // Not locking m_argMutex here, it is done in impp()->commandArgsAddGuts
    // m_argMutex here is the same as in impp()->commandArgsAddGuts;
    // due to clang limitations, it doesn't properly check it
    impp()->commandArgsGuts(argc, argv);
}
void VerilatedContext::commandArgsAdd(int argc, const char** argv)
    VL_MT_SAFE_EXCLUDES(m_argMutex) {
    // Not locking m_argMutex here, it is done in impp()->commandArgsAddGuts
    // m_argMutex here is the same as in impp()->commandArgsAddGuts;
    // due to clang limitations, it doesn't properly check it
    impp()->commandArgsAddGutsLock(argc, argv);
}
const char* VerilatedContext::commandArgsPlusMatch(const char* prefixp)
    VL_MT_SAFE_EXCLUDES(m_argMutex) {
    const std::string& match = impp()->argPlusMatch(prefixp);
    static thread_local char t_outstr[VL_VALUE_STRING_MAX_WIDTH];
    if (match.empty()) return "";
    char* dp = t_outstr;
    for (const char* sp = match.c_str(); *sp && (dp - t_outstr) < (VL_VALUE_STRING_MAX_WIDTH - 2);)
        *dp++ = *sp++;
    *dp++ = '\0';
    return t_outstr;
}
void VerilatedContext::internalsDump() const VL_MT_SAFE {
    VL_PRINTF_MT("internalsDump:\n");
    VerilatedImp::versionDump();
    impp()->commandArgDump();
    impp()->scopesDump();
    VerilatedImp::exportsDump();
    VerilatedImp::userDump();
}

void VerilatedContext::addModel(const VerilatedModel* modelp) {
    if (!quiet()) {
        // CPU time isn't read as starting point until model creation, so that quiet() is set
        // Thus if quiet(), avoids slow OS read affecting some usages that make many models
        const VerilatedLockGuard lock{m_mutex};
        m_ns.m_cpuTimeStart.start();
        m_ns.m_wallTimeStart.start();
    }

    // We look for time passing, as opposed to post-eval(), as embedded
    // models might get added inside initial blocks.
    if (VL_UNLIKELY(time())) {
        const std::string msg
            = "Adding model '"s + modelp->hierName()
              + "' when time is non-zero. ... Suggest check time(), or for restarting"
                " model use a new VerilatedContext";
        VL_FATAL_MT("", 0, "", msg.c_str());
    }

    threadPoolp();  // Ensure thread pool is created, so m_threads cannot change any more
    m_threadsInModels += modelp->threads();
    if (VL_UNLIKELY(modelp->threads() > m_threads)) {
        std::ostringstream msg;
        msg << "VerilatedContext has " << m_threads << " threads but model '"
            << modelp->modelName() << "' (instantiated as '" << modelp->hierName()
            << "') was Verilated with --threads " << modelp->threads() << ".\n";
        const std::string str = msg.str();
        VL_FATAL_MT(__FILE__, __LINE__, modelp->hierName(), str.c_str());
    }
}

VerilatedVirtualBase* VerilatedContext::threadPoolp() {
    if (m_threads == 1) return nullptr;
    if (!m_threadPool) m_threadPool.reset(new VlThreadPool{this, m_threads - 1});
    return m_threadPool.get();
}

void VerilatedContext::prepareClone() { delete m_threadPool.release(); }

VerilatedVirtualBase* VerilatedContext::threadPoolpOnClone() {
    if (VL_UNLIKELY(m_threadPool)) (void)m_threadPool.release();
    m_threadPool = std::unique_ptr<VlThreadPool>(new VlThreadPool{this, m_threads - 1});
    return m_threadPool.get();
}

VerilatedVirtualBase*
VerilatedContext::enableExecutionProfiler(VerilatedVirtualBase* (*construct)(VerilatedContext&)) {
    if (!m_executionProfiler) m_executionProfiler.reset(construct(*this));
    return m_executionProfiler.get();
}

//======================================================================
// VerilatedContextImp:: Methods - command line

void VerilatedContextImp::commandArgsGuts(int argc, const char** argv)
    VL_MT_SAFE_EXCLUDES(m_argMutex) {
    const VerilatedLockGuard lock{m_argMutex};
    m_args.m_argVec.clear();  // Empty first, then add
    commandArgsAddGuts(argc, argv);
}

void VerilatedContextImp::commandArgsAddGutsLock(int argc, const char** argv)
    VL_MT_SAFE_EXCLUDES(m_argMutex) {
    const VerilatedLockGuard lock{m_argMutex};
    commandArgsAddGuts(argc, argv);
}

void VerilatedContextImp::commandArgsAddGuts(int argc, const char** argv) VL_REQUIRES(m_argMutex) {
    if (!m_args.m_argVecLoaded) m_args.m_argVec.clear();
    for (int i = 0; i < argc; ++i) {
        m_args.m_argVec.emplace_back(argv[i]);
        commandArgVl(argv[i]);
    }
    m_args.m_argVecLoaded = true;  // Can't just test later for empty vector, no arguments is ok
}
void VerilatedContextImp::commandArgDump() const VL_MT_SAFE_EXCLUDES(m_argMutex) {
    const VerilatedLockGuard lock{m_argMutex};
    VL_PRINTF_MT("  Argv:");
    for (const auto& i : m_args.m_argVec) VL_PRINTF_MT(" %s", i.c_str());
    VL_PRINTF_MT("\n");
}
std::string VerilatedContextImp::argPlusMatch(const char* prefixp)
    VL_MT_SAFE_EXCLUDES(m_argMutex) {
    const VerilatedLockGuard lock{m_argMutex};
    // Note prefixp does not include the leading "+"
    const size_t len = std::strlen(prefixp);
    if (VL_UNLIKELY(!m_args.m_argVecLoaded)) {
        m_args.m_argVecLoaded = true;  // Complain only once
        VL_FATAL_MT("unknown", 0, "",
                    "%Error: Verilog called $test$plusargs or $value$plusargs without"
                    " testbench C first calling Verilated::commandArgs(argc,argv).");
    }
    for (const auto& i : m_args.m_argVec) {
        if (i[0] == '+') {
            if (0 == std::strncmp(prefixp, i.c_str() + 1, len)) return i;
        }
    }
    return "";
}
// Return string representing current argv
// Only used by VPI so uses static storage, only supports most recent called context
std::pair<int, char**> VerilatedContextImp::argc_argv() VL_MT_SAFE_EXCLUDES(m_argMutex) {
    const VerilatedLockGuard lock{m_argMutex};
    static bool s_loaded = false;
    static int s_argc = 0;
    static char** s_argvp = nullptr;
    if (VL_UNLIKELY(!s_loaded)) {
        s_loaded = true;
        s_argc = static_cast<int>(m_args.m_argVec.size());
        s_argvp = new char*[s_argc + 1];
        int in = 0;
        for (const auto& i : m_args.m_argVec) {
            s_argvp[in] = new char[i.length() + 1];
            std::memcpy(s_argvp[in], i.c_str(), i.length() + 1);
            ++in;
        }
        s_argvp[s_argc] = nullptr;
    }
    return std::make_pair(s_argc, s_argvp);
}

void VerilatedContextImp::commandArgVl(const std::string& arg) {
    if (0 == std::strncmp(arg.c_str(), "+verilator+", std::strlen("+verilator+"))) {
        std::string str;
        uint64_t u64;
        if (commandArgVlString(arg, "+verilator+coverage+file+", str)) {
            coverageFilename(str);
        } else if (arg == "+verilator+debug") {
            Verilated::debug(4);
        } else if (commandArgVlUint64(arg, "+verilator+debugi+", u64, 0,
                                      std::numeric_limits<int>::max())) {
            Verilated::debug(static_cast<int>(u64));
        } else if (commandArgVlUint64(arg, "+verilator+error+limit+", u64, 0,
                                      std::numeric_limits<int>::max())) {
            errorLimit(static_cast<int>(u64));
        } else if (arg == "+verilator+help") {
            VerilatedImp::versionDump();
            VL_PRINTF_MT("For help, please see 'verilator --help'\n");
            VL_FATAL_MT("COMMAND_LINE", 0, "",
                        "Exiting due to command line argument (not an error)");
        } else if (arg == "+verilator+noassert") {
            assertOn(false);
        } else if (commandArgVlUint64(arg, "+verilator+prof+exec+start+", u64)) {
            profExecStart(u64);
        } else if (commandArgVlUint64(arg, "+verilator+prof+exec+window+", u64, 1)) {
            profExecWindow(u64);
        } else if (commandArgVlString(arg, "+verilator+prof+exec+file+", str)) {
            profExecFilename(str);
        } else if (commandArgVlString(arg, "+verilator+prof+vlt+file+", str)) {
            profVltFilename(str);
        } else if (arg == "+verilator+quiet") {
            quiet(true);
        } else if (commandArgVlUint64(arg, "+verilator+rand+reset+", u64, 0, 2)) {
            randReset(static_cast<int>(u64));
        } else if (commandArgVlUint64(arg, "+verilator+wno+unsatconstr+", u64, 0, 1)) {
            warnUnsatConstr(u64 == 0);  // wno means disable, so invert
        } else if (commandArgVlUint64(arg, "+verilator+seed+", u64, 1,
                                      std::numeric_limits<int>::max())) {
            randSeed(static_cast<int>(u64));
        } else if (arg == "+verilator+V") {
            VerilatedImp::versionDump();  // Someday more info too
            VL_FATAL_MT("COMMAND_LINE", 0, "",
                        "Exiting due to command line argument (not an error)");
        } else if (arg == "+verilator+version") {
            VerilatedImp::versionDump();
            VL_FATAL_MT("COMMAND_LINE", 0, "",
                        "Exiting due to command line argument (not an error)");
        } else {
            const std::string msg = "Unknown runtime argument: " + arg;
            VL_FATAL_MT("COMMAND_LINE", 0, "", msg.c_str());
        }
    }
}

bool VerilatedContextImp::commandArgVlString(const std::string& arg, const std::string& prefix,
                                             std::string& valuer) {
    const size_t len = prefix.length();
    if (0 == std::strncmp(prefix.c_str(), arg.c_str(), len)) {
        valuer = arg.substr(len);
        return true;
    } else {
        return false;
    }
}

bool VerilatedContextImp::commandArgVlUint64(const std::string& arg, const std::string& prefix,
                                             uint64_t& valuer, uint64_t min, uint64_t max) {
    std::string str;
    if (commandArgVlString(arg, prefix, str)) {
        const auto fail = [&](const std::string& extra = "") {
            std::stringstream ss;
            ss << "Argument '" << prefix << "' must be an unsigned integer";
            if (min != std::numeric_limits<uint64_t>::min()) ss << ", greater than " << min - 1;
            if (max != std::numeric_limits<uint64_t>::max()) ss << ", less than " << max + 1;
            if (!extra.empty()) ss << ". " << extra;
            const std::string& msg = ss.str();
            VL_FATAL_MT("COMMAND_LINE", 0, "", msg.c_str());
        };

        if (std::any_of(str.cbegin(), str.cend(), [](int c) { return !std::isdigit(c); })) fail();
        char* end;
        valuer = std::strtoull(str.c_str(), &end, 10);
        if (errno == ERANGE) fail("Value out of range of uint64_t");
        if (valuer < min || valuer > max) fail();
        return true;
    }
    return false;
}

//======================================================================
// VerilatedContext:: + VerilatedContextImp:: Methods - random

void VerilatedContext::randSeed(int val) VL_MT_SAFE {
    // As we have per-thread state, the epoch must be static,
    // and so the rand seed's mutex must also be static
    const VerilatedLockGuard lock{VerilatedContextImp::s().s_randMutex};
    m_s.m_randSeed = val;
    const uint64_t newEpoch = VerilatedContextImp::s().s_randSeedEpoch + 1;
    // Observers must see new epoch AFTER seed updated
    std::atomic_signal_fence(std::memory_order_release);
    VerilatedContextImp::s().s_randSeedEpoch = newEpoch;
}
uint64_t VerilatedContextImp::randSeedDefault64() const VL_MT_SAFE {
    if (randSeed() != 0) {
        return ((static_cast<uint64_t>(randSeed()) << 32) ^ (static_cast<uint64_t>(randSeed())));
    } else {
        return ((static_cast<uint64_t>(vl_sys_rand32()) << 32)
                ^ (static_cast<uint64_t>(vl_sys_rand32())));
    }
}

//======================================================================
// VerilatedContext:: Statistics

double VerilatedContext::statCpuTimeSinceStart() const VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    return m_ns.m_cpuTimeStart.deltaTime();
}
double VerilatedContext::statWallTimeSinceStart() const VL_MT_SAFE_EXCLUDES(m_mutex) {
    const VerilatedLockGuard lock{m_mutex};
    return m_ns.m_wallTimeStart.deltaTime();
}
void VerilatedContext::statsPrintSummary() VL_MT_UNSAFE {
    if (quiet()) return;
    VL_PRINTF("- S i m u l a t i o n   R e p o r t: %s %s\n", Verilated::productName(),
              Verilated::productVersion());
    const std::string endwhy = gotError() ? "$stop" : gotFinish() ? "$finish" : "end";
    const double simtimeInUnits = VL_TIME_Q() * vl_time_multiplier(timeunit())
                                  * vl_time_multiplier(timeprecision() - timeunit());
    const std::string simtime = vl_timescaled_double(simtimeInUnits);
    const double walltime = statWallTimeSinceStart();
    const double cputime = statCpuTimeSinceStart();
    const std::string simtimePerf
        = vl_timescaled_double((cputime != 0.0) ? (simtimeInUnits / cputime) : 0, "%0.3f %s");
    VL_PRINTF("- Verilator: %s at %s; walltime %0.3f s; speed %s/s\n", endwhy.c_str(),
              simtime.c_str(), walltime, simtimePerf.c_str());
    uint64_t memPeak, memCurrent;
    VlOs::memUsageBytes(memPeak /*ref*/, memCurrent /*ref*/);
    const double modelMB = memPeak / 1024.0 / 1024.0;
    VL_PRINTF("- Verilator: cpu %0.3f s on %u threads; allocated %0.0f MB\n", cputime,
              threadsInModels(), modelMB);
}

//======================================================================
// VerilatedContext:: Methods - scopes

void VerilatedContext::scopesDump() const VL_MT_SAFE {
    const VerilatedLockGuard lock{m_impdatap->m_nameMutex};
    VL_PRINTF_MT("  scopesDump:\n");
    for (const auto& i : m_impdatap->m_nameMap) {
        const VerilatedScope* const scopep = i.second;
        scopep->scopeDump();
    }
    VL_PRINTF_MT("\n");
}

void VerilatedContextImp::scopeInsert(const VerilatedScope* scopep) VL_MT_SAFE {
    // Slow ok - called once/scope at construction
    const VerilatedLockGuard lock{m_impdatap->m_nameMutex};
    const auto it = m_impdatap->m_nameMap.find(scopep->name());
    if (it == m_impdatap->m_nameMap.end()) m_impdatap->m_nameMap.emplace(scopep->name(), scopep);
}
void VerilatedContextImp::scopeErase(const VerilatedScope* scopep) VL_MT_SAFE {
    // Slow ok - called once/scope at destruction
    const VerilatedLockGuard lock{m_impdatap->m_nameMutex};
    VerilatedImp::userEraseScope(scopep);
    const auto it = m_impdatap->m_nameMap.find(scopep->name());
    if (it != m_impdatap->m_nameMap.end()) m_impdatap->m_nameMap.erase(it);
}
const VerilatedScope* VerilatedContext::scopeFind(const char* namep) const VL_MT_SAFE {
    // Thread save only assuming this is called only after model construction completed
    const VerilatedLockGuard lock{m_impdatap->m_nameMutex};
    // If too slow, can assume this is only VL_MT_SAFE_POSINIT
    const auto& it = m_impdatap->m_nameMap.find(namep);
    if (VL_UNLIKELY(it == m_impdatap->m_nameMap.end())) return nullptr;
    return it->second;
}
const VerilatedScopeNameMap* VerilatedContext::scopeNameMap() VL_MT_SAFE {
    return &(impp()->m_impdatap->m_nameMap);
}

//======================================================================
// VerilatedContext:: Methods - trace

void VerilatedContext::trace(VerilatedTraceBaseC* tfp, int levels, int options) {
    VL_DEBUG_IF(VL_DBG_MSGF("+ VerilatedContext::trace\n"););
    if (tfp->isOpen()) {
        VL_FATAL_MT("", 0, "",
                    "Testbench C call to 'VerilatedContext::trace()' must not be called"
                    " after 'VerilatedTrace*::open()'\n");
    }
    {
        // Legacy usage may call {modela}->trace(...) then {modelb}->trace(...)
        // So check for and suppress second and later calls
        if (tfp->modelConnected()) return;
        tfp->modelConnected(true);
    }
    // We rely on m_ns.m_traceBaseModelCbs being stable when trace() is called
    // nope: const VerilatedLockGuard lock{m_mutex};
    if (m_ns.m_traceBaseModelCbs.empty())
        VL_FATAL_MT("", 0, "",
                    "Testbench C call to 'VerilatedContext::trace()' requires model(s) Verilated"
                    " with --trace-fst or --trace-vcd option");
    for (const auto& cbr : m_ns.m_traceBaseModelCbs) cbr(tfp, levels, options);
}
void VerilatedContext::traceBaseModelCbAdd(traceBaseModelCb_t cb) VL_MT_SAFE {
    // Model creation registering a callback for when Verilated::trace() called
    const VerilatedLockGuard lock{m_mutex};
    m_ns.m_traceBaseModelCbs.push_back(cb);
}

//======================================================================
// VerilatedSyms:: Methods

VerilatedSyms::VerilatedSyms(VerilatedContext* contextp)
    : _vm_contextp__(contextp ? contextp : Verilated::threadContextp()) {
    VerilatedContext::checkMagic(_vm_contextp__);
    Verilated::threadContextp(_vm_contextp__);
    __Vm_evalMsgQp = new VerilatedEvalMsgQueue;
}

VerilatedSyms::~VerilatedSyms() {
    VerilatedContext::checkMagic(_vm_contextp__);
    delete __Vm_evalMsgQp;
}

//===========================================================================
// Verilated:: Methods

void Verilated::debug(int level) VL_MT_SAFE {
    s_debug = level;
    if (level) {
#ifdef VL_DEBUG
        VL_DEBUG_IF(VL_DBG_MSGF("- Verilated::debug is on."
                                " Message prefix indicates {<thread>,<sequence_number>}.\n"););
#else
        VL_PRINTF_MT("- Verilated::debug attempted,"
                     " but compiled without VL_DEBUG, so messages suppressed.\n"
                     "- Suggest remake using 'make ... CPPFLAGS=-DVL_DEBUG'\n");
#endif
    }
}

const char* Verilated::catName(const char* n1, const char* n2, const char* delimiter) VL_MT_SAFE {
    // Used by symbol table creation to make module names
    static thread_local char* t_strp = nullptr;
    static thread_local size_t t_len = 0;
    const size_t newlen = std::strlen(n1) + std::strlen(n2) + std::strlen(delimiter) + 1;
    if (VL_UNLIKELY(!t_strp || newlen > t_len)) {
        if (t_strp) delete[] t_strp;
        t_strp = new char[newlen];
        t_len = newlen;
    }
    char* dp = t_strp;
    for (const char* sp = n1; *sp;) *dp++ = *sp++;
    for (const char* sp = delimiter; *sp;) *dp++ = *sp++;
    for (const char* sp = n2; *sp;) *dp++ = *sp++;
    *dp++ = '\0';
    return t_strp;
}

//=========================================================================
// Flush and exit callbacks

// Keeping these out of class Verilated to avoid having to include <list>
// in verilated.h (for compilation speed)
using VoidPCbList = std::list<std::pair<Verilated::VoidPCb, void*>>;
static struct {
    VerilatedMutex s_flushMutex;
    VoidPCbList s_flushCbs VL_GUARDED_BY(s_flushMutex);
    VerilatedMutex s_exitMutex;
    VoidPCbList s_exitCbs VL_GUARDED_BY(s_exitMutex);
} VlCbStatic;

static void addCbFlush(Verilated::VoidPCb cb, void* datap)
    VL_MT_SAFE_EXCLUDES(VlCbStatic.s_flushMutex) {
    const VerilatedLockGuard lock{VlCbStatic.s_flushMutex};
    std::pair<Verilated::VoidPCb, void*> pair(cb, datap);
    VlCbStatic.s_flushCbs.remove(pair);  // Just in case it's a duplicate
    VlCbStatic.s_flushCbs.push_back(pair);
}
static void addCbExit(Verilated::VoidPCb cb, void* datap)
    VL_MT_SAFE_EXCLUDES(VlCbStatic.s_exitMutex) {
    const VerilatedLockGuard lock{VlCbStatic.s_exitMutex};
    std::pair<Verilated::VoidPCb, void*> pair(cb, datap);
    VlCbStatic.s_exitCbs.remove(pair);  // Just in case it's a duplicate
    VlCbStatic.s_exitCbs.push_back(pair);
}
static void removeCbFlush(Verilated::VoidPCb cb, void* datap)
    VL_MT_SAFE_EXCLUDES(VlCbStatic.s_flushMutex) {
    const VerilatedLockGuard lock{VlCbStatic.s_flushMutex};
    std::pair<Verilated::VoidPCb, void*> pair(cb, datap);
    VlCbStatic.s_flushCbs.remove(pair);
}
static void removeCbExit(Verilated::VoidPCb cb, void* datap)
    VL_MT_SAFE_EXCLUDES(VlCbStatic.s_exitMutex) {
    const VerilatedLockGuard lock{VlCbStatic.s_exitMutex};
    std::pair<Verilated::VoidPCb, void*> pair(cb, datap);
    VlCbStatic.s_exitCbs.remove(pair);
}
static void runCallbacks(const VoidPCbList& cbs) VL_MT_SAFE {
    for (const auto& i : cbs) i.first(i.second);
}

void Verilated::addFlushCb(VoidPCb cb, void* datap) VL_MT_SAFE { addCbFlush(cb, datap); }
void Verilated::removeFlushCb(VoidPCb cb, void* datap) VL_MT_SAFE { removeCbFlush(cb, datap); }
void Verilated::runFlushCallbacks() VL_MT_SAFE {
    // Flush routines may call flush, so avoid mutex deadlock
    static std::atomic<int> s_recursing;
    if (!s_recursing++) {
        const VerilatedLockGuard lock{VlCbStatic.s_flushMutex};
        runCallbacks(VlCbStatic.s_flushCbs);
    }
    --s_recursing;
    std::fflush(stderr);
    std::fflush(stdout);
    // When running internal code coverage (gcc --coverage, as opposed to
    // verilator --coverage), dump coverage data to properly cover failing
    // tests.
    VL_GCOV_DUMP();
}

void Verilated::addExitCb(VoidPCb cb, void* datap) VL_MT_SAFE { addCbExit(cb, datap); }
void Verilated::removeExitCb(VoidPCb cb, void* datap) VL_MT_SAFE { removeCbExit(cb, datap); }
void Verilated::runExitCallbacks() VL_MT_SAFE {
    static std::atomic<int> s_recursing;
    if (!s_recursing++) {
        const VerilatedLockGuard lock{VlCbStatic.s_exitMutex};
        runCallbacks(VlCbStatic.s_exitCbs);
    }
    --s_recursing;
}

const char* Verilated::productName() VL_PURE { return VERILATOR_PRODUCT; }
const char* Verilated::productVersion() VL_PURE { return VERILATOR_VERSION; }

void Verilated::nullPointerError(const char* filename, int linenum) VL_MT_SAFE {
    // Slowpath - Called only on error
    VL_FATAL_MT(filename, linenum, "", "Null pointer dereferenced");
    VL_UNREACHABLE;
}

void Verilated::overWidthError(const char* signame) VL_MT_SAFE {
    // Slowpath - Called only when signal sets too high of a bit
    const std::string msg = ("Testbench C set input '"s + signame
                             + "' to value that overflows what the signal's width can fit");
    VL_FATAL_MT("unknown", 0, "", msg.c_str());
    VL_UNREACHABLE;
}

void Verilated::scTimePrecisionError(int sc_prec, int vl_prec) VL_MT_SAFE {
    std::ostringstream msg;
    msg << "SystemC's sc_set_time_resolution is 10^-" << sc_prec
        << ", which does not match Verilog timeprecision 10^-" << vl_prec
        << ". Suggest use 'sc_set_time_resolution(" << vl_time_str(vl_prec)
        << ")', or Verilator '--timescale-override " << vl_time_str(sc_prec) << "/"
        << vl_time_str(sc_prec) << "'";
    const std::string msgs = msg.str();
    VL_FATAL_MT("", 0, "", msgs.c_str());
    VL_UNREACHABLE;
}

void Verilated::scTraceBeforeElaborationError() VL_MT_SAFE {
    // Slowpath - Called only when trace file opened before SystemC elaboration
    VL_FATAL_MT("unknown", 0, "",
                "%Error: Verilated*Sc::open(...) was called before sc_core::sc_start(). "
                "Run sc_core::sc_start(sc_core::SC_ZERO_TIME) before opening a wave file.");
    VL_UNREACHABLE;
}

void Verilated::stackCheck(QData needSize) VL_MT_UNSAFE {
    // Slowpath - Called only when constructing
#ifdef _VL_HAVE_GETRLIMIT
    QData haveSize = 0;
    rlimit rlim;
    if (0 == getrlimit(RLIMIT_STACK, &rlim)) {
        haveSize = rlim.rlim_cur;
        if (haveSize == RLIM_INFINITY) haveSize = rlim.rlim_max;
        if (haveSize == RLIM_INFINITY) haveSize = 0;
    }
    // VL_PRINTF_MT("-Info: stackCheck(%" PRIu64 ") have %" PRIu64 "\n", needSize, haveSize);
    // Check and request for 1.5x need. This is automated so the user doesn't need to do anything.
    QData requestSize = needSize + needSize / 2;
    if (VL_UNLIKELY(haveSize && needSize && haveSize < requestSize)) {
        // Try to increase the stack limit to the requested size
        rlim.rlim_cur = requestSize;
        if (
#ifdef _VL_TEST_RLIMIT_FAIL
            true ||
#endif
            setrlimit(RLIMIT_STACK, &rlim)) {
            VL_PRINTF_MT("%%Warning: System has stack size %" PRIu64 " kb"
                         " which may be too small; failed to request more"
                         " using 'ulimit -s %" PRIu64 "'\n",
                         haveSize / 1024, requestSize);
        }
    }
#else
    (void)needSize;  // Unused argument
#endif
}

void Verilated::mkdir(const char* dirname) VL_MT_UNSAFE {
#if defined(_WIN32) || defined(__MINGW32__)
    ::mkdir(dirname);
#else
    ::mkdir(dirname, 0777);
#endif
}

void Verilated::quiesce() VL_MT_SAFE {
    // Wait until all threads under this evaluation are quiet
}

int Verilated::exportFuncNum(const char* namep) VL_MT_SAFE {
    return VerilatedImp::exportFindNum(namep);
}

void Verilated::endOfThreadMTaskGuts(VerilatedEvalMsgQueue* evalMsgQp) VL_MT_SAFE {
    VL_DEBUG_IF(VL_DBG_MSGF("End of thread mtask\n"););
    VerilatedThreadMsgQueue::flush(evalMsgQp);
}

void Verilated::endOfEval(VerilatedEvalMsgQueue* evalMsgQp) VL_MT_SAFE {
    // It doesn't work to set endOfEvalReqd on the threadpool thread
    // and then check it on the eval thread since it's thread local.
    // It should be ok to call into endOfEvalGuts, it returns immediately
    // if there are no transactions.
    VL_DEBUG_IF(VL_DBG_MSGF("End-of-eval cleanup\n"););
    VerilatedThreadMsgQueue::flush(evalMsgQp);
    evalMsgQp->process();
}

//===========================================================================
// VerilatedImp:: Methods

void VerilatedImp::versionDump() VL_MT_SAFE {
    VL_PRINTF_MT("  Version: %s %s\n", Verilated::productName(), Verilated::productVersion());
}

//===========================================================================
// VerilatedModel:: Methods

VerilatedModel::VerilatedModel(VerilatedContext& context)
    : m_context{context} {}

std::unique_ptr<VerilatedTraceConfig> VerilatedModel::traceConfig() const { return nullptr; }

//======================================================================
// VerilatedVar:: Methods

// cppcheck-suppress unusedFunction  // Used by applications
uint32_t VerilatedVarProps::entSize() const VL_MT_SAFE {
    uint32_t size = 1;
    switch (vltype()) {
    case VLVT_PTR: size = sizeof(void*); break;
    case VLVT_UINT8: size = sizeof(CData); break;
    case VLVT_UINT16: size = sizeof(SData); break;
    case VLVT_UINT32: size = sizeof(IData); break;
    case VLVT_UINT64: size = sizeof(QData); break;
    case VLVT_WDATA: size = VL_WORDS_I(entBits()) * sizeof(IData); break;
    default: size = 0; break;  // LCOV_EXCL_LINE
    }
    return size;
}

size_t VerilatedVarProps::totalSize() const {
    size_t size = entSize();
    for (int udim = 0; udim < udims(); ++udim) size *= m_unpacked[udim].elements();
    return size;
}

void* VerilatedVarProps::datapAdjustIndex(void* datap, int dim, int indx) const VL_MT_SAFE {
    if (VL_UNLIKELY(dim <= 0 || dim > udims())) return nullptr;
    if (VL_UNLIKELY(indx < low(dim) || indx > high(dim))) return nullptr;
    const int indxAdj = indx - low(dim);
    uint8_t* bytep = reinterpret_cast<uint8_t*>(datap);
    // If on index 1 of a 2 index array, then each index 1 is index2sz*entsz
    size_t slicesz = entSize();
    for (int d = dim + 1; d <= udims(); ++d) slicesz *= elements(d);
    bytep += indxAdj * slicesz;
    return bytep;
}

//======================================================================
// VerilatedScope:: Methods

VerilatedScope::VerilatedScope(VerilatedSyms* symsp, const char* suffixp, const char* identifier,
                               const char* defnamep, int8_t timeunit, Type type)
    : m_symsp{symsp}
    , m_namep{[symsp, suffixp]() {
        // We don't want the space and reference-count access overhead of strings.
        const char* prefixp = symsp->name();
        char* const namep = new char[std::strlen(prefixp) + std::strlen(suffixp) + 2];
        char* dp = namep;
        for (const char* sp = prefixp; *sp;) *dp++ = *sp++;
        if (*prefixp && *suffixp) *dp++ = '.';
        for (const char* sp = suffixp; *sp;) *dp++ = *sp++;
        *dp++ = '\0';
        return namep;
    }()}
    , m_identifierp{identifier}
    , m_defnamep{defnamep}
    , m_timeunit{timeunit}
    , m_type{type} {
    Verilated::threadContextp()->impp()->scopeInsert(this);
}

VerilatedScope::~VerilatedScope() {
    // Memory cleanup - not called during normal operation
    Verilated::threadContextp()->impp()->scopeErase(this);
    VL_DO_DANGLING(delete[] m_namep, m_namep);
    VL_DO_DANGLING(delete[] m_callbacksp, m_callbacksp);
    VL_DO_DANGLING(delete m_varsp, m_varsp);
    VL_DEBUG_IFDEF(m_funcnumMax = 0;);
}

void VerilatedScope::exportInsert(int finalize, const char* namep, void* cb) VL_MT_UNSAFE {
    // Slowpath - called once/scope*export at construction
    // Insert a exported function into scope table
    const int funcnum = VerilatedImp::exportInsert(namep, cb);
    if (!finalize) {
        // Need two passes so we know array size to create
        // Alternative is to dynamically stretch the array, which is more code, and slower.
        if (funcnum >= m_funcnumMax) m_funcnumMax = funcnum + 1;
    } else {
        if (VL_UNCOVERABLE(funcnum >= m_funcnumMax)) {
            VL_FATAL_MT(__FILE__, __LINE__, "",  // LCOV_EXCL_LINE
                        "Internal: Bad funcnum vs. pre-finalize maximum");
        }
        if (VL_UNLIKELY(!m_callbacksp)) {  // First allocation
            m_callbacksp = new void*[m_funcnumMax];
            std::memset(m_callbacksp, 0, m_funcnumMax * sizeof(void*));
        }
        m_callbacksp[funcnum] = cb;
    }
}

void VerilatedScope::varInsert(const char* namep, void* datap, bool isParam,
                               VerilatedVarType vltype, int vlflags, int udims,
                               int pdims...) VL_MT_UNSAFE {
    // Grab dimensions
    // In the future we may just create a large table at emit time and
    // statically construct from that.

    if (!m_varsp) m_varsp = new VerilatedVarNameMap;
    VerilatedVar var(namep, datap, vltype, static_cast<VerilatedVarFlags>(vlflags), udims, pdims,
                     isParam);

    va_list ap;
    va_start(ap, pdims);
    for (int i = 0; i < udims; ++i) {
        const int msb = va_arg(ap, int);
        const int lsb = va_arg(ap, int);
        var.m_unpacked[i].m_left = msb;
        var.m_unpacked[i].m_right = lsb;
    }
    for (int i = 0; i < pdims; ++i) {
        const int msb = va_arg(ap, int);
        const int lsb = va_arg(ap, int);
        var.m_packed[i].m_left = msb;
        var.m_packed[i].m_right = lsb;
    }
    va_end(ap);

    m_varsp->emplace(namep, var);
}

// cppcheck-suppress unusedFunction  // Used by applications
VerilatedVar* VerilatedScope::varFind(const char* namep) const VL_MT_SAFE_POSTINIT {
    if (VL_LIKELY(m_varsp)) {
        const auto it = m_varsp->find(namep);
        if (VL_LIKELY(it != m_varsp->end())) return &(it->second);
    }
    return nullptr;
}

void* VerilatedScope::exportFind(const VerilatedScope* scopep, int funcnum) VL_MT_SAFE {
    if (VL_UNLIKELY(!scopep)) return exportFindNullError(funcnum);
    // If function is registered only once across all scopes, fast path it.
    // UVM for example expects to find uvm_polling_value_change_notify
    // from a different scope than where decared.
    VL_DEBUG_IFDEF(assert(funcnum < VerilatedImp::exportFlatCbs().size()););
    {
        void* const cbp = VerilatedImp::exportFlatCbs()[funcnum];
        if (VL_LIKELY(cbp)) return cbp;
    }
    // Else specific scope-based export call
    if (VL_LIKELY(funcnum < scopep->m_funcnumMax)) {
        // m_callbacksp must be declared, as Max'es are > 0
        void* const cbp = scopep->m_callbacksp[funcnum];
        if (VL_LIKELY(cbp)) return cbp;
    }
    return scopep->exportFindError(funcnum);  // LCOV_EXCL_LINE
}

void* VerilatedScope::exportFindNullError(int funcnum) VL_MT_SAFE {
    // Slowpath - Called only when find has failed
    const std::string msg = ("Testbench C called '"s + VerilatedImp::exportName(funcnum)
                             + "' but scope wasn't set, perhaps due to dpi import call without "
                             + "'context', or missing svSetScope. See IEEE 1800-2023 35.5.3.");
    VL_FATAL_MT("unknown", 0, "", msg.c_str());
    return nullptr;
}

void* VerilatedScope::exportFindError(int funcnum) const VL_MT_SAFE {
    // Slowpath - Called only when find has failed
    const std::string msg
        = ("Testbench C called '"s + VerilatedImp::exportName(funcnum)
           + "' but this DPI export function exists only in other scopes, not scope '" + name()
           + "'");
    VL_FATAL_MT("unknown", 0, "", msg.c_str());
    return nullptr;
}

void VerilatedScope::scopeDump() const {
    VL_PRINTF_MT("    SCOPE %p: %s\n", this, name());
    for (int i = 0; i < m_funcnumMax; ++i) {
        if (m_callbacksp && m_callbacksp[i]) {
            VL_PRINTF_MT("       DPI-EXPORT %p: %s\n", m_callbacksp[i],
                         VerilatedImp::exportName(i));
        }
    }
    if (const VerilatedVarNameMap* const ivarsp = this->varsp()) {
        for (const auto& i : *ivarsp) VL_PRINTF_MT("       VAR %p: %s\n", &(i.second), i.first);
    }
}

void VerilatedHierarchy::add(const VerilatedScope* fromp, const VerilatedScope* top) {
    VerilatedImp::hierarchyAdd(fromp, top);
}

void VerilatedHierarchy::remove(const VerilatedScope* fromp, const VerilatedScope* top) {
    VerilatedImp::hierarchyRemove(fromp, top);
}

void VerilatedHierarchy::clear() { VerilatedImp::hierarchyClear(); }

//===========================================================================
// VerilatedOneThreaded:: Methods

#ifdef VL_DEBUG
void VerilatedAssertOneThread::fatal_different() VL_MT_SAFE {
    VL_FATAL_MT(__FILE__, __LINE__, "",
                "Routine called that is single threaded, but called from"
                " a different thread than the expected constructing thread");
}
#endif

//===========================================================================
// VlDeleter:: Methods

void VlDeleter::deleteAll() VL_EXCLUDES(m_mutex) VL_EXCLUDES(m_deleteMutex) VL_MT_SAFE {
    while (true) {
        {
            VerilatedLockGuard lock{m_mutex};
            if (m_newGarbage.empty()) break;
            m_deleteMutex.lock();
            std::swap(m_newGarbage, m_deleteNow);
            // m_mutex is unlocked here, so destructors can enqueue new objects
        }
        for (VlDeletable* const objp : m_deleteNow) delete objp;
        m_deleteNow.clear();
        m_deleteMutex.unlock();
    }
}

//===========================================================================
// OS functions (last, so we have minimal OS dependencies above)

#define VL_ALLOW_VERILATEDOS_C
#include "verilatedos_c.h"
