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
/// \brief Verilated/Verilator common header for OS portability
///
/// This header is included by user wrappers and defines the Verilated
/// public-facing API.
///
/// User wrapper code does not generally need to include this, instead
/// include verilated.h.
///
/// This header is used by both the Verilator source code (run on the build
/// and host system), and the Verilated output (run on the target system).
///
/// Configuration code needed by only the host system is in
/// config_build.h.in, code needed by Verilated code only is in
/// verilated.h, and code needed by both is here (verilatedos.h).
///
//*************************************************************************

#ifndef VERILATOR_VERILATEDOS_H_
#define VERILATOR_VERILATEDOS_H_

// Current clang-format versions botch #ifdef inclusion, so
// clang-format off
//=========================================================================
// Compiler pragma abstraction

#if defined(__clang__)
# define VL_CLANG_ATTR(attr) __attribute__(( attr ))
#else
# define VL_CLANG_ATTR(attr)
#endif

#ifdef __GNUC__
# define VL_ATTR_ALWINLINE __attribute__((always_inline)) inline
# define VL_ATTR_NOINLINE __attribute__((noinline))
# define VL_ATTR_COLD __attribute__((cold))
# define VL_ATTR_HOT __attribute__((hot))
# define VL_ATTR_NORETURN __attribute__((noreturn))
// clang and gcc-8.0+ support no_sanitize("string") style attribute
# if defined(__clang__) || (__GNUC__ >= 8)
#  define VL_ATTR_NO_SANITIZE_ALIGN __attribute__((no_sanitize("alignment")))
# else  // The entire undefined sanitizer has to be disabled for older gcc
#  define VL_ATTR_NO_SANITIZE_ALIGN __attribute__((no_sanitize_undefined))
# endif
# define VL_ATTR_PRINTF(fmtArgNum) __attribute__((format(printf, (fmtArgNum), (fmtArgNum) + 1)))
# define VL_ATTR_PURE __attribute__((pure))
# define VL_ATTR_UNUSED __attribute__((unused))
# define VL_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
# if !defined(_WIN32) && !defined(__MINGW32__)
// All VL_ATTR_WEAK symbols must be marked with the macOS -U linker flag in verilated.mk.in
#  define VL_ATTR_WEAK __attribute__((weak))
# endif
# define VL_LIKELY(x) __builtin_expect(!!(x), 1)  // Prefer over C++20 [[likely]]
# define VL_UNLIKELY(x) __builtin_expect(!!(x), 0)  // Prefer over C++20 [[unlikely]]
# define VL_PREFETCH_RD(p) __builtin_prefetch((p), 0)
# define VL_PREFETCH_RW(p) __builtin_prefetch((p), 1)
#endif

#ifdef __cpp_lib_unreachable
/// Statement that may never be reached (for coverage etc)
# define VL_UNREACHABLE std::unreachable()  // C++23
#elif defined(__GNUC__)
# define VL_UNREACHABLE __builtin_unreachable()
#elif defined(_MSC_VER)  // MSVC
# define VL_UNREACHABLE __assume(false)
#else
# define VL_UNREACHABLE
#endif

// Function acquires a capability/lock (-fthread-safety)
#define VL_ACQUIRE(...) \
        VL_CLANG_ATTR(annotate("ACQUIRE")) \
        VL_CLANG_ATTR(acquire_capability(__VA_ARGS__))
// Function acquires a shared capability/lock (-fthread-safety)
#define VL_ACQUIRE_SHARED(...) \
        VL_CLANG_ATTR(annotate("ACQUIRE_SHARED")) \
        VL_CLANG_ATTR(acquire_shared_capability(__VA_ARGS__))
// Function releases a capability/lock (-fthread-safety)
#define VL_RELEASE(...) \
        VL_CLANG_ATTR(annotate("RELEASE")) \
        VL_CLANG_ATTR(release_capability(__VA_ARGS__))
// Function releases a shared capability/lock (-fthread-safety)
#define VL_RELEASE_SHARED(...) \
        VL_CLANG_ATTR(annotate("RELEASE_SHARED")) \
        VL_CLANG_ATTR(release_shared_capability(__VA_ARGS__))
// Function returns bool if acquired a capability (-fthread-safety)
#define VL_TRY_ACQUIRE(...) \
        VL_CLANG_ATTR(try_acquire_capability(__VA_ARGS__))
// Function returns bool if acquired shared (-fthread-safety)
#define VL_TRY_ACQUIRE_SHARED(...) \
        VL_CLANG_ATTR(try_acquire_shared_capability(__VA_ARGS__))
// Function requires a capability inbound (-fthread-safety)
#define VL_CAPABILITY(x) \
        VL_CLANG_ATTR(capability(x))
// Name of mutex protecting this variable (-fthread-safety)
#define VL_EXCLUDES(x) \
        VL_CLANG_ATTR(annotate("EXCLUDES")) \
        VL_CLANG_ATTR(locks_excluded(x))
// Scoped threaded capability/lock (-fthread-safety)
#define VL_SCOPED_CAPABILITY \
        VL_CLANG_ATTR(scoped_lockable)
// Annotated function returns reference to the given capability.
// Allowed on: function, method. (-fthread-safety)
#define VL_RETURN_CAPABILITY(x) \
        VL_CLANG_ATTR(lock_returned(x))
// Assert that capability is already held.
// Allowed on: function, method. (-fthread-safety)
#define VL_ASSERT_CAPABILITY(x) \
        VL_CLANG_ATTR(assert_capability(x))
// Disable thread safety analysis for the annotted function
// Use this only when absolutely sure code is correct, but too
// complicated for the compiler to prove.
#define VL_NO_THREAD_SAFETY_ANALYSIS \
        VL_CLANG_ATTR(no_thread_safety_analysis)

// Require mutex locks only in code units which work with enabled multi-threading.
#if !defined(VL_MT_DISABLED_CODE_UNIT)
// Function requires not having a capability inbound (-fthread-safety)
# define VL_REQUIRES(x) \
        VL_CLANG_ATTR(annotate("REQUIRES")) \
        VL_CLANG_ATTR(requires_capability(x))
// Name of capability/lock (-fthread-safety)
# define VL_GUARDED_BY(x) \
        VL_CLANG_ATTR(annotate("GUARDED_BY")) \
        VL_CLANG_ATTR(guarded_by(x))
// The data that the annotated pointer points to is protected by the given capability.
// The pointer itself is not protected.
// Allowed on: pointer data member. (-fthread-safety)
# define VL_PT_GUARDED_BY(x) \
        VL_CLANG_ATTR(annotate("PT_GUARDED_BY")) \
        VL_CLANG_ATTR(pt_guarded_by(x))
#else
// Keep annotations for clang_check_attributes
# define VL_REQUIRES(x) \
        VL_CLANG_ATTR(annotate("REQUIRES"))
# define VL_GUARDED_BY(x) \
        VL_CLANG_ATTR(annotate("GUARDED_BY"))
# define VL_PT_GUARDED_BY(x) \
        VL_CLANG_ATTR(annotate("PT_GUARDED_BY"))
#endif

// Defaults for unsupported compiler features
#ifndef VL_ATTR_ALWINLINE
# define VL_ATTR_ALWINLINE inline  ///< Attribute to inline, even when not optimizing
#endif
#ifndef VL_ATTR_NOINLINE
# define VL_ATTR_NOINLINE  ///< Attribute to never inline, even when optimizing
#endif
#ifndef VL_ATTR_COLD
# define VL_ATTR_COLD  ///< Attribute that function is rarely executed
#endif
#ifndef VL_ATTR_HOT
# define VL_ATTR_HOT  ///< Attribute that function is highly executed
#endif
#ifndef VL_ATTR_NORETURN
# define VL_ATTR_NORETURN  ///< Attribute that function does not ever return
#endif
#ifndef VL_ATTR_NO_SANITIZE_ALIGN
# define VL_ATTR_NO_SANITIZE_ALIGN  ///< Attribute that function contains intended unaligned access
#endif
#ifndef VL_ATTR_PRINTF
# define VL_ATTR_PRINTF(fmtArgNum)  ///< Attribute for function with printf format checking
#endif
#ifndef VL_ATTR_PURE
# define VL_ATTR_PURE  ///< Attribute that function is pure (and thus also VL_MT_SAFE)
#endif
#ifndef VL_ATTR_UNUSED
# define VL_ATTR_UNUSED  ///< Attribute that function that may be never used
#endif
#ifndef VL_ATTR_WARN_UNUSED_RESULT
# define VL_ATTR_WARN_UNUSED_RESULT  ///< Attribute that return value of function must be used
#endif
#ifndef VL_ATTR_WEAK
# define VL_ATTR_WEAK  ///< Attribute that function external that is optionally defined
#endif
#ifndef VL_LIKELY
# define VL_LIKELY(x) (!!(x))  ///< Return boolean expression that is more often true
# define VL_UNLIKELY(x) (!!(x))  ///< Return boolean expression that is more often false
#endif
/// Boolean expression never hit by users (branch coverage disabled)
# define VL_UNCOVERABLE(x) VL_UNLIKELY(x)
#ifndef VL_PREFETCH_RD
# define VL_PREFETCH_RD(p)  ///< Prefetch pointer argument with read intent
#endif
#ifndef VL_PREFETCH_RW
# define VL_PREFETCH_RW(p)  ///< Prefetch pointer argument with read/write intent
#endif


#ifndef VL_NO_LEGACY
# define VL_ATTR_ALIGNED(alignment)  // Deprecated
# define VL_FUNC __func__  // Deprecated
# define VL_THREAD  // Deprecated
# define VL_THREAD_LOCAL thread_local  // Deprecated
# define VL_STATIC_OR_THREAD static  // Deprecated
#endif

// Comment tag that Function is pure (and thus also VL_MT_SAFE)
#define VL_PURE VL_CLANG_ATTR(annotate("PURE"))
// Annotated function can be called only in MT_DISABLED context, i.e. either in a code unit
// compiled with VL_MT_DISABLED_CODE_UNIT preprocessor definition, or in the main thread.
#define VL_MT_DISABLED \
    VL_CLANG_ATTR(annotate("MT_DISABLED")) \
    VL_EXCLUDES(VlOs::MtScopeMutex::s_haveThreadScope)
// Comment tag that function is threadsafe
#define VL_MT_SAFE VL_CLANG_ATTR(annotate("MT_SAFE"))
// Comment tag that function is threadsafe, only if
// other threads doesn't change tree topology
#define VL_MT_STABLE VL_CLANG_ATTR(annotate("MT_STABLE"))
// Comment tag that function is threadsafe, only
// during normal operation (post-init)
#define VL_MT_SAFE_POSTINIT VL_CLANG_ATTR(annotate("MT_SAFE_POSTINIT"))
// Attribute that function is clang threadsafe and uses given mutex
#define VL_MT_SAFE_EXCLUDES(mutex) VL_CLANG_ATTR(annotate("MT_SAFE_EXCLUDES")) VL_EXCLUDES(mutex)
// Comment tag that function is not threadsafe
#define VL_MT_UNSAFE VL_CLANG_ATTR(annotate("MT_UNSAFE"))
// Comment tag that function is not threadsafe
// protected to make sure single-caller
#define VL_MT_UNSAFE_ONE VL_CLANG_ATTR(annotate("MT_UNSAFE_ONE"))
// Comment tag that function is entry point of parallelization
#define VL_MT_START VL_CLANG_ATTR(annotate("MT_START")) VL_REQUIRES(VlOs::MtScopeMutex::s_haveThreadScope)

#ifndef VL_NO_LEGACY
# define VL_ULL(c) (c##ULL)  // Add appropriate suffix to 64-bit constant (deprecated)
#endif

// Convert argument to IData
// This is not necessarily the same as "#UL", depending on what the IData typedef is.
#define VL_UL(c) (static_cast<IData>(c##UL))

#if defined(VL_CPPCHECK) || defined(__clang_analyzer__) || __cplusplus < 201103L
# define VL_DANGLING(var)
#else
/// After e.g. delete, set variable to nullptr to indicate must not use later
# define VL_DANGLING(var) \
    do { \
        *const_cast<const void**>(reinterpret_cast<const void* const*>(&var)) = nullptr; \
    } while (false)
#endif

/// Perform an e.g. delete, then set variable to nullptr to indicate must not use later.
/// Unlike VL_DO_CLEAR the setting of the variable is only for debug reasons.
#define VL_DO_DANGLING(stmt, var) \
    do { \
        do { \
            stmt; \
        } while (false); \
        VL_DANGLING(var); \
    } while (false)

/// As with VL_DO_DANGLING, but two variables dangle.
#define VL_DO_DANGLING2(stmt, var, var2) \
    do { \
        do { \
            stmt; \
        } while (false); \
        VL_DANGLING(var); \
        VL_DANGLING(var2); \
    } while (false)

/// Perform an e.g. delete, then set variable to nullptr as a requirement
#define VL_DO_CLEAR(stmt, stmt2) \
    do { \
        do { \
            stmt; \
        } while (false); \
        do { \
            stmt2; \
        } while (false); \
    } while (false)

#ifdef _MSC_VER
# if _MSC_VER < 1929
#  error "Verilator requires at least Visual Studio 2019 version 16.11.2"
# endif
#endif

//=========================================================================
// C++-2014

#if __cplusplus >= 201402L || defined(VL_CPPCHECK) || defined(_MSC_VER)
#else
# error "Verilator requires a C++14 or newer compiler"
#endif

#ifndef VL_NO_LEGACY
// These are deprecated historical defines. We leave them in case users referenced them.
# define VL_EQ_DELETE = delete
# define vl_unique_ptr std::unique_ptr
# define vl_unordered_map std::unordered_map
# define vl_unordered_set std::unordered_set
# define VL_INCLUDE_UNORDERED_MAP <unordered_map>
# define VL_INCLUDE_UNORDERED_SET <unordered_set>
# define VL_FINAL final
# define VL_MUTABLE mutable
# define VL_OVERRIDE override
#endif

//=========================================================================
// C++-2017

#if __cplusplus >= 201703L
# define VL_CONSTEXPR_CXX17 constexpr
#else
# define VL_CONSTEXPR_CXX17
#endif


//=========================================================================
// Optimization

#ifndef VL_NO_LEGACY
# ifndef VL_INLINE_OPT
#   define VL_INLINE_OPT  // Historical, has no effect on Verilated models.
# endif
#endif

//=========================================================================
// Internal coverage

#ifdef VL_GCOV
extern "C" void __gcov_dump();
// Dump internal code coverage data before e.g. std::abort()
# define VL_GCOV_DUMP() __gcov_dump()
#else
# define VL_GCOV_DUMP()
#endif

//=========================================================================
// Warning disabled

#ifndef VL_WARNINGS
# ifdef _MSC_VER
#  pragma warning(disable:4099)  // C4099: type name first seen using 'class' now seen using 'struct' (V3AstNode)
#  pragma warning(disable:4100)  // C4100: unreferenced formal parameter (L4)
#  pragma warning(disable:4127)  // C4127: conditional expression is constant (L4)
#  pragma warning(disable:4146)  // C4146: unary minus operator applied to unsigned type, result still unsigned
#  pragma warning(disable:4189)  // C4189: local variable is initialized but not referenced (L4)
#  pragma warning(disable:4244)  // C4244: conversion from 'uint64_t' to 'uint_32_t', possible loss of data
#  pragma warning(disable:4245)  // C4245: conversion from 'int' to 'unsigned', signed/unsigned mismatch
#  pragma warning(disable:4996)  // C4996: sscanf/fopen/etc may be unsafe
# endif
#endif

//=========================================================================
// Basic integer types

#ifdef __MINGW32__
# define __USE_MINGW_ANSI_STDIO 1  // Force old MinGW (GCC 5 and older) to use C99 formats
#endif

// The inttypes supplied with some GCC & MINGW32 versions requires STDC_FORMAT_MACROS
// to be declared in order to get the PRIxx macros used by fstapi.c
#define __STDC_FORMAT_MACROS

// Now that C++ requires these standard types the vl types are deprecated
#include <cstdint>
#include <cinttypes>
#include <cmath>
#include <ctime>

#ifndef VL_NO_LEGACY
using vluint8_t = uint8_t;  ///< 8-bit unsigned type (backward compatibility)
using vluint16_t = uint16_t;  ///< 16-bit unsigned type (backward compatibility)
using vluint32_t = uint32_t;  ///< 32-bit unsigned type (backward compatibility)
using vluint64_t = uint64_t;  ///< 64-bit unsigned type (backward compatibility)
using vlsint8_t = int8_t;  ///< 8-bit signed type (backward compatibility)
using vlsint16_t = int16_t;  ///< 16-bit signed type (backward compatibility)
using vlsint32_t = int32_t;  ///< 32-bit signed type (backward compatibility)
using vlsint64_t = int64_t;  ///< 64-bit signed type (backward compatibility)
#endif

#if defined(__CYGWIN__)

# include <sys/types.h>  // __WORDSIZE
# include <unistd.h>  // ssize_t

#elif defined(_WIN32) && defined(_MSC_VER)

# ifndef _SSIZE_T_DEFINED
#  ifdef _WIN64
using ssize_t = uint64_t;  ///< signed size_t; returned from read()
#  else
using ssize_t = uint32_t;  ///< signed size_t; returned from read()
#  endif
# endif

#else  // Linux or compliant Unix flavors, -m64

# include <inttypes.h>  // Solaris
# include <sys/types.h>  // __WORDSIZE
# include <unistd.h>  // ssize_t
#endif

//=========================================================================
// Printing printf/scanf formats

// Use Microsoft-specific format specifiers for Microsoft Visual C++ only
// Deprecated, favor C++11's PRIx64, etc, instead
#ifndef VL_NO_LEGACY
# ifdef _MSC_VER
#  define VL_PRI64 "I64"  ///< print a uint64_t (backward compatibility)
# else  // use standard C99 format specifiers
#  if defined(__WORDSIZE) && (__WORDSIZE == 64)
#   define VL_PRI64 "l"  ///< print a uint64_t (backward compatibility)
#  else
#   define VL_PRI64 "ll"  ///< print a uint64_t (backward compatibility)
#  endif
# endif
#endif

#if defined(_WIN32) && defined(_MSC_VER)
# if (_MSC_VER < 1900)
#  define VL_SNPRINTF _snprintf
# else
#  define VL_SNPRINTF snprintf
# endif
# define VL_VSNPRINTF vsnprintf
#else
# define VL_SNPRINTF snprintf
# define VL_VSNPRINTF vsnprintf
#endif

//=========================================================================
// File system functions

#ifdef _WIN32
# define VL_DEV_NULL "nul"
#else  // Linux or compliant Unix flavors
# define VL_DEV_NULL "/dev/null"
#endif

//=========================================================================
// Integer size macros

#define VL_BYTESIZE 8  ///< Bits in a CData / byte
#define VL_SHORTSIZE 16  ///< Bits in a SData / short
#define VL_IDATASIZE 32  ///< Bits in an IData / word
#define VL_QUADSIZE 64  ///< Bits in a QData / quadword
#define VL_EDATASIZE 32  ///< Bits in an EData (WData entry)
#define VL_EDATASIZE_LOG2 5  ///< log2(VL_EDATASIZE)
#define VL_CACHE_LINE_BYTES 64  ///< Bytes in a cache line (for alignment)

#ifndef VL_NO_LEGACY
# define VL_WORDSIZE VL_IDATASIZE  // Legacy define
#endif

/// Return number of bytes argument-number of bits needs (1 bit=1 byte)
#define VL_BYTES_I(nbits) (((nbits) + (VL_BYTESIZE - 1)) / VL_BYTESIZE)
/// Return Words/EDatas in argument-number of bits needs (1 bit=1 word)
#define VL_WORDS_I(nbits) (((nbits) + (VL_EDATASIZE - 1)) / VL_EDATASIZE)
// Number of Words/EDatas a quad requires
#define VL_WQ_WORDS_E VL_WORDS_I(VL_QUADSIZE)

//=========================================================================
// Class definition helpers

// Comment tag to indicate a base class, e.g. cannot label "class final"
#define VL_NOT_FINAL

// Declare a class as uncopyable; put after a private:
#define VL_UNCOPYABLE(Type) \
    Type(const Type& other) = delete; \
    Type& operator=(const Type&) = delete

// Declare a class as unmovable; put after a private:
#define VL_UNMOVABLE(Type) \
    Type(Type&& other) = delete; \
    Type& operator=(Type&&) = delete

//=========================================================================
// Verilated function size macros

#define VL_MULS_MAX_WORDS 128  ///< Max size in words of MULS operation

#ifndef VL_VALUE_STRING_MAX_WORDS
    #define VL_VALUE_STRING_MAX_WORDS 64  ///< Max size in words of String conversion operation
#endif
#define VL_VALUE_STRING_MAX_CHARS (VL_VALUE_STRING_MAX_WORDS) * 4

//=========================================================================
// Base macros

#define VL_SIZEBITS_I (VL_IDATASIZE - 1)  ///< Bit mask for bits in a word
#define VL_SIZEBITS_Q (VL_QUADSIZE - 1)  ///< Bit mask for bits in a quad
#define VL_SIZEBITS_E (VL_EDATASIZE - 1)  ///< Bit mask for bits in a quad

/// Return mask for words with 1's where relevant bits are (0=all bits)
/// Arguments must not have side effects
#define VL_MASK_I(nbits) (((nbits) & VL_SIZEBITS_I) ? ((1U << ((nbits) & VL_SIZEBITS_I)) - 1) : ~0)
/// Return mask for quads with 1's where relevant bits are (0=all bits)
/// Arguments must not have side effects
#define VL_MASK_Q(nbits) \
    (((nbits) & VL_SIZEBITS_Q) ? ((1ULL << ((nbits) & VL_SIZEBITS_Q)) - 1ULL) : ~0ULL)
/// Return mask for EData with 1's where relevant bits are (0=all bits)
/// Arguments must not have side effects
#define VL_MASK_E(nbits) VL_MASK_I(nbits)

#define VL_EUL(n) VL_UL(n)  // Make constant number EData sized

#define VL_BITWORD_I(bit) ((bit) / VL_IDATASIZE)  ///< Word number for sv DPI vectors
#define VL_BITWORD_E(bit) ((bit) >> VL_EDATASIZE_LOG2)  ///< Word number for a wide quantity
#define VL_BITBIT_I(bit) ((bit) & VL_SIZEBITS_I)  ///< Bit number for a bit in a long
#define VL_BITBIT_Q(bit) ((bit) & VL_SIZEBITS_Q)  ///< Bit number for a bit in a quad
#define VL_BITBIT_E(bit) ((bit) & VL_SIZEBITS_E)  ///< Bit number for a bit in an EData

// Return true if data[bit] set; not 0/1 return, but 0/non-zero return.
#define VL_BITISSET_I(data, bit) ((data) & (VL_UL(1) << VL_BITBIT_I(bit)))
#define VL_BITISSET_Q(data, bit) ((data) & (1ULL << VL_BITBIT_Q(bit)))
#define VL_BITISSET_E(data, bit) ((data) & (VL_EUL(1) << VL_BITBIT_E(bit)))
#define VL_BITISSET_W(data, bit) ((data)[VL_BITWORD_E(bit)] & (VL_EUL(1) << VL_BITBIT_E(bit)))

//=========================================================================
// Floating point
// #defines, to avoid requiring math.h on all compile runs

#ifdef _MSC_VER
static inline double VL_TRUNC(double n) {
    return (n < 0) ? std::ceil(n) : std::floor(n);
}
static inline double VL_ROUND(double n) {
    return (n < 0) ? std::ceil(n-0.5) : std::floor(n + 0.5);
}
#else
# define VL_TRUNC(n) std::trunc(n)
# define VL_ROUND(n) std::round(n)
#endif

//=========================================================================
// Performance counters

#if defined(__i386__) || defined(__x86_64__)
// The uint64_t argument is loaded with a high-performance counter for profiling
// or 0x0 if not implemented on this platform
#define VL_GET_CPU_TICK(val) \
    { \
        uint32_t hi; \
        uint32_t lo; \
        asm volatile("rdtsc" : "=a"(lo), "=d"(hi)); \
        (val) = ((uint64_t)lo) | (((uint64_t)hi) << 32); \
    }
#elif defined(__aarch64__)
// 1 GHz virtual system timer on SBSA level 5 compliant systems, else often 100 MHz
# define VL_GET_CPU_TICK(val) \
    { \
        asm volatile("isb" : : : "memory"); \
        asm volatile("mrs %[rt],CNTVCT_EL0" : [rt] "=r"(val)); \
    }
#else
// We just silently ignore unknown OSes, as only leads to missing statistics
# define VL_GET_CPU_TICK(val) (val) = 0;
#endif

//=========================================================================
// Threading related OS-specific functions

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# ifndef NOMINMAX
#  define NOMINMAX
# endif
# include "windows.h"
# define VL_CPU_RELAX() YieldProcessor()
#elif defined(__i386__) || defined(__x86_64__) || defined(VL_CPPCHECK)
// For more efficient busy waiting on SMT CPUs, let the processor know
// we're just waiting so it can let another thread run
# define VL_CPU_RELAX() asm volatile("rep; nop" ::: "memory")
#elif defined(__ia64__)
# define VL_CPU_RELAX() asm volatile("hint @pause" ::: "memory")
#elif defined(__armel__) || defined(__ARMEL__)  // Arm, but broken, must be before __arm__
# define VL_CPU_RELAX() asm volatile("nop" ::: "memory");
#elif defined(__aarch64__) || defined(__arm__)
# define VL_CPU_RELAX() asm volatile("yield" ::: "memory")
#elif defined(__hppa__)  // HPPA does not currently have yield/pause
# define VL_CPU_RELAX() asm volatile("nop" ::: "memory")
#elif defined(__loongarch__)  // LoongArch does not currently have yield/pause
# define VL_CPU_RELAX() asm volatile("nop" ::: "memory")
#elif defined(__mips64el__) || defined(__mips__) || defined(__mips64__) || defined(__mips64)
# define VL_CPU_RELAX() asm volatile("pause" ::: "memory")
#elif defined(__POWERPC__) && defined(__APPLE__) // First check for a special case of macOS
# define VL_CPU_RELAX() asm volatile("or r1, r1, r1; or r2, r2, r2;" ::: "memory")
#elif defined(__powerpc64__) || defined(__powerpc__) // Generic powerpc
# define VL_CPU_RELAX() asm volatile("or 1, 1, 1; or 2, 2, 2;" ::: "memory")
#elif defined(__riscv)  // RiscV does not currently have yield/pause, but one is proposed
# define VL_CPU_RELAX() asm volatile("nop" ::: "memory")
#elif defined(__s390x__)
# define VL_CPU_RELAX() asm volatile("lr 0,0" ::: "memory")
#elif defined(__sparc__)
# define VL_CPU_RELAX() asm volatile("rd %%ccr, %%g0" ::: "memory")
#elif defined(VL_IGNORE_UNKNOWN_ARCH)
# define VL_CPU_RELAX()
#else
# error "Missing VL_CPU_RELAX() definition."
#endif

//=========================================================================
// String/time related OS-specific functions

#ifdef _MSC_VER
# define VL_STRCASECMP _stricmp
#else
# define VL_STRCASECMP strcasecmp
#endif

//=========================================================================
// Macros controlling target-specific optimizations

// Define VL_PORTABLE_ONLY to disable all target-specific optimizations
#ifndef VL_PORTABLE_ONLY
# ifdef __x86_64__
#  define VL_X86_64 1
# endif
#endif  // VL_PORTABLE_ONLY
// clang-format on

//=========================================================================
// Stringify macros

#define VL_STRINGIFY(...) VL_STRINGIFY2(__VA_ARGS__)
#define VL_STRINGIFY2(...) #__VA_ARGS__

//=========================================================================
// Offset of field in type

// Address zero can cause compiler problems
#define VL_OFFSETOF(type, field) \
    (reinterpret_cast<size_t>(&(reinterpret_cast<type*>(0x10000000)->field)) - 0x10000000)

//=========================================================================
// Time and performance

#include <string>

namespace VlOs {

/// Get environment variable
extern std::string getenvStr(const std::string& envvar,
                             const std::string& defaultValue) VL_MT_SAFE;

/// Return currently executing processor number; may do an OS call underneath so slow
extern uint16_t getcpu() VL_MT_SAFE;

/// Return number of processors available to the current process. This might be
/// less than the number of logical processors in the machine, if a processor
/// affinity mask was used, e.g. via 'numactl -C 0-3'. Returns 0 if cannot
/// be determiend.
extern unsigned getProcessAvailableParallelism() VL_MT_SAFE;

/// Return getProcessAvailableParallelism if non-zero, otherwise the number of
/// hardware threads in the host machine.
extern unsigned getProcessDefaultParallelism() VL_MT_SAFE;

/// Return memory usage in bytes, or 0 if unknown
extern void memUsageBytes(uint64_t& peakr, uint64_t& currentr) VL_MT_SAFE;

// Internal: Record CPU time, starting point on construction, and current delta from that
class DeltaCpuTime final {
    double m_start{};  // Time constructed at
    static double gettime() VL_MT_SAFE;

public:
    // Construct, and if startit is true, start() timer
    explicit DeltaCpuTime(bool startit) {
        if (startit) start();
    }
    void start() VL_MT_SAFE { m_start = gettime(); }  // Start timer; record current time
    double deltaTime() const VL_MT_SAFE {  // Return time between now and start()
        return (m_start == 0.0) ? 0.0 : gettime() - m_start;
    }
};
// Internal: Record wall time, starting point on construction, and current delta from that
class DeltaWallTime final {
    double m_start{};  // Time constructed at
    static double gettime() VL_MT_SAFE;

public:
    // Construct, and if startit is true, start() timer
    explicit DeltaWallTime(bool startit) {
        if (startit) start();
    }
    void start() VL_MT_SAFE { m_start = gettime(); }  // Start timer; record current time
    double deltaTime() const VL_MT_SAFE {  // Return time between now and start()
        return (m_start == 0.0) ? 0.0 : gettime() - m_start;
    }
};

// Used by clang's -fthread-safety, ensures that only one instance of V3ThreadScope
// is created at a time
class VL_CAPABILITY("mutex") MtScopeMutex final {
public:
    static MtScopeMutex s_haveThreadScope;
};

}  //namespace VlOs

//=========================================================================
// Conversions

#include <utility>

namespace vlstd {

template <typename T>
struct reverse_wrapper final {
    const T& m_v;

    explicit reverse_wrapper(const T& a_v)
        : m_v(a_v) {}  // Need () constructor
    auto begin() -> decltype(m_v.rbegin()) { return m_v.rbegin(); }
    auto end() -> decltype(m_v.rend()) { return m_v.rend(); }
};

// C++20's std::ranges::reverse_view
template <typename T>
reverse_wrapper<T> reverse_view(const T& v) {
    return reverse_wrapper<T>(v);
}

// C++17's std::as_const
// `VL_MT_SAFE` annotation only applies to this function.
// Object that is returned by this function is not considered
// as MT_SAFE and any function call on this object still
// needs to be `VL_MT_SAFE`.
template <typename T>
T const& as_const(T& v) VL_MT_SAFE {
    return v;
}

// Utility function
template <size_t N>
inline constexpr size_t roundUpToMultipleOf(size_t value) {
    static_assert((N & (N - 1)) == 0, "'N' must be a power of 2");
    return (value + N - 1) & ~(N - 1);
}

};  // namespace vlstd

//=========================================================================

#endif  // Guard
