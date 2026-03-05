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
/// \brief Verilated common functions
///
/// verilated.h should be included instead of this file.
///
/// Those macro/function/variable starting or ending in _ are internal,
/// however many of the other function/macros here are also internal.
///
//*************************************************************************

#ifndef VERILATOR_VERILATED_FUNCS_H_
#define VERILATOR_VERILATED_FUNCS_H_

#ifndef VERILATOR_VERILATED_H_INTERNAL_
#error "verilated_funcs.h should only be included by verilated.h"
#endif

#include <string>

//=========================================================================
// Extern functions -- User may override -- See verilated.cpp

/// Routine to call for $finish
/// User code may wish to replace this function, to do so, define VL_USER_FINISH.
/// This code does not have to be thread safe.
/// Verilator internal code must call VL_FINISH_MT instead, which eventually calls this.
extern void vl_finish(const char* filename, int linenum, const char* hier) VL_MT_UNSAFE;

/// Routine to call for $stop and non-fatal error
/// User code may wish to replace this function, to do so, define VL_USER_STOP.
/// This code does not have to be thread safe.
/// Verilator internal code must call VL_STOP_MT instead, which eventually calls this.
extern void vl_stop(const char* filename, int linenum, const char* hier) VL_MT_UNSAFE;

/// Routine to call for fatal messages
/// User code may wish to replace this function, to do so, define VL_USER_FATAL.
/// This code does not have to be thread safe.
/// Verilator internal code must call VL_FATAL_MT instead, which eventually calls this.
extern void vl_fatal(const char* filename, int linenum, const char* hier,
                     const char* msg) VL_MT_UNSAFE;

/// Routine to call for warning messages
/// User code may wish to replace this function, to do so, define VL_USER_WARN.
/// This code does not have to be thread safe.
/// Verilator internal code must call VL_WARN_MT instead, which eventually calls this.
extern void vl_warn(const char* filename, int linenum, const char* hier,
                    const char* msg) VL_MT_UNSAFE;

//=========================================================================
// Extern functions -- Slow path

/// Multithread safe wrapper for calls to $finish
extern void VL_FINISH_MT(const char* filename, int linenum, const char* hier) VL_MT_SAFE;
/// Multithread safe wrapper for calls to $stop
extern void VL_STOP_MT(const char* filename, int linenum, const char* hier,
                       bool maybe = true) VL_MT_SAFE;
/// Multithread safe wrapper to call for fatal messages
extern void VL_FATAL_MT(const char* filename, int linenum, const char* hier,
                        const char* msg) VL_MT_SAFE;
/// Multithread safe wrapper to call for warning messages
extern void VL_WARN_MT(const char* filename, int linenum, const char* hier,
                       const char* msg) VL_MT_SAFE;

// clang-format off
/// Print a string, multithread safe. Eventually VL_PRINTF will get called.
extern void VL_PRINTF_MT(const char* formatp, ...) VL_ATTR_PRINTF(1) VL_MT_SAFE;
// clang-format on

/// Print a debug message from internals with standard prefix, with printf style format
extern void VL_DBG_MSGF(const char* formatp, ...) VL_ATTR_PRINTF(1) VL_MT_SAFE;

/// Print a debug message from string via VL_DBG_MSGF
inline void VL_DBG_MSGS(const std::string& str) VL_MT_SAFE { VL_DBG_MSGF("%s", str.c_str()); }

// EMIT_RULE: VL_RANDOM:  oclean=dirty
inline IData VL_RANDOM_I() VL_MT_SAFE { return vl_rand64(); }
inline QData VL_RANDOM_Q() VL_MT_SAFE { return vl_rand64(); }
extern WDataOutP VL_RANDOM_W(int obits, WDataOutP outwp) VL_MT_SAFE;
extern IData VL_RANDOM_SEEDED_II(IData& seedr) VL_MT_SAFE;
extern IData VL_URANDOM_SEEDED_II(IData seed) VL_MT_SAFE;
inline IData VL_URANDOM_RANGE_I(IData hi, IData lo) {
    const uint64_t rnd = vl_rand64();
    if (VL_LIKELY(hi > lo)) {
        // (hi - lo + 1) can be zero when hi is UINT_MAX and lo is zero
        if (VL_UNLIKELY(hi - lo + 1 == 0)) return rnd;
        // Modulus isn't very fast but it's common that hi-low is power-of-two
        return (rnd % (hi - lo + 1)) + lo;
    } else {
        if (VL_UNLIKELY(lo - hi + 1 == 0)) return rnd;
        return (rnd % (lo - hi + 1)) + hi;
    }
}

/// Random reset a signal of given width (init time only, var-specific PRNG)
extern IData VL_SCOPED_RAND_RESET_I(int obits, uint64_t scopeHash, uint64_t salt) VL_MT_UNSAFE;
/// Random reset a signal of given width (init time only, var-specific PRNG)
extern QData VL_SCOPED_RAND_RESET_Q(int obits, uint64_t scopeHash, uint64_t salt) VL_MT_UNSAFE;
/// Random reset a signal of given width (init time only, var-specific PRNG)
extern WDataOutP VL_SCOPED_RAND_RESET_W(int obits, WDataOutP outwp, uint64_t scopeHash,
                                        uint64_t salt) VL_MT_UNSAFE;

/// Random reset a signal of given width (assign time only)
extern IData VL_SCOPED_RAND_RESET_ASSIGN_I(int obits, uint64_t scopeHash,
                                           uint64_t salt) VL_MT_UNSAFE;
/// Random reset a signal of given width (assign time only)
extern QData VL_SCOPED_RAND_RESET_ASSIGN_Q(int obits, uint64_t scopeHash,
                                           uint64_t salt) VL_MT_UNSAFE;
/// Random reset a signal of given width (assign time only)
extern WDataOutP VL_SCOPED_RAND_RESET_ASSIGN_W(int obits, WDataOutP outwp, uint64_t scopeHash,
                                               uint64_t salt) VL_MT_UNSAFE;

/// Random reset a signal of given width (init time only)
extern IData VL_RAND_RESET_I(int obits) VL_MT_SAFE;
/// Random reset a signal of given width (init time only)
extern QData VL_RAND_RESET_Q(int obits) VL_MT_SAFE;
/// Random reset a signal of given width (init time only)
extern WDataOutP VL_RAND_RESET_W(int obits, WDataOutP outwp) VL_MT_SAFE;

/// Zero reset a signal (slow - else use VL_ZERO_W)
extern WDataOutP VL_ZERO_RESET_W(int obits, WDataOutP outwp) VL_MT_SAFE;

extern void VL_PRINTTIMESCALE(const char* namep, const char* timeunitp,
                              const VerilatedContext* contextp) VL_MT_SAFE;

extern WDataOutP _vl_moddiv_w(int lbits, WDataOutP owp, WDataInP const lwp, WDataInP const rwp,
                              bool is_modulus) VL_MT_SAFE;

extern void _vl_vsss_based(WDataOutP owp, int obits, int baseLog2, const char* strp,
                           size_t posstart, size_t posend) VL_MT_SAFE;

extern IData VL_FGETS_IXI(int obits, void* destp, IData fpi) VL_MT_SAFE;

extern void VL_FFLUSH_I(IData fdi) VL_MT_SAFE;
extern IData VL_FSEEK_I(IData fdi, IData offset, IData origin) VL_MT_SAFE;
extern IData VL_FTELL_I(IData fdi) VL_MT_SAFE;
extern void VL_FCLOSE_I(IData fdi) VL_MT_SAFE;

extern IData VL_FREAD_I(int width, int array_lsb, int array_size, void* memp, IData fpi,
                        IData start, IData count) VL_MT_SAFE;

extern void VL_WRITEF_NX(const std::string& format, int argc, ...) VL_MT_SAFE;
extern void VL_FWRITEF_NX(IData fpi, const std::string& format, int argc, ...) VL_MT_SAFE;

extern IData VL_FSCANF_INX(IData fpi, const std::string& format, int argc, ...) VL_MT_SAFE;
extern IData VL_SSCANF_IINX(int lbits, IData ld, const std::string& format, int argc,
                            ...) VL_MT_SAFE;
extern IData VL_SSCANF_IQNX(int lbits, QData ld, const std::string& format, int argc,
                            ...) VL_MT_SAFE;
extern IData VL_SSCANF_IWNX(int lbits, WDataInP const lwp, const std::string& format, int argc,
                            ...) VL_MT_SAFE;

extern void VL_SFORMAT_NX(int obits, CData& destr, const std::string& format, int argc,
                          ...) VL_MT_SAFE;
extern void VL_SFORMAT_NX(int obits, SData& destr, const std::string& format, int argc,
                          ...) VL_MT_SAFE;
extern void VL_SFORMAT_NX(int obits, IData& destr, const std::string& format, int argc,
                          ...) VL_MT_SAFE;
extern void VL_SFORMAT_NX(int obits, QData& destr, const std::string& format, int argc,
                          ...) VL_MT_SAFE;
extern void VL_SFORMAT_NX(int obits, void* destp, const std::string& format, int argc,
                          ...) VL_MT_SAFE;

extern void VL_STACKTRACE() VL_MT_SAFE;
extern std::string VL_STACKTRACE_N() VL_MT_SAFE;
extern IData VL_SYSTEM_IW(int lhswords, WDataInP const lhsp) VL_MT_SAFE;
extern IData VL_SYSTEM_IQ(QData lhs) VL_MT_SAFE;
inline IData VL_SYSTEM_II(IData lhs) VL_MT_SAFE { return VL_SYSTEM_IQ(lhs); }
extern IData VL_SYSTEM_IN(const std::string& lhs) VL_MT_SAFE;

extern IData VL_TESTPLUSARGS_I(const std::string& format) VL_MT_SAFE;
extern const char* vl_mc_scan_plusargs(const char* prefixp) VL_MT_SAFE;  // PLIish

//=========================================================================
// Base macros

// Return true if data[bit] set; not 0/1 return, but 0/non-zero return.
// Arguments must not have side effects
#define VL_BITISSETLIMIT_W(data, width, bit) (((bit) < (width)) && VL_BITISSET_W(data, bit))

// Shift appropriate word by bit. Does not account for wrapping between two words
// Argument 'bit' must not have side effects
#define VL_BITRSHIFT_W(data, bit) ((data)[VL_BITWORD_E(bit)] >> VL_BITBIT_E(bit))

// Create two 32-bit words from quadword
// WData is always at least 2 words; does not clean upper bits
#define VL_SET_WQ(owp, data) \
    do { \
        (owp)[0] = static_cast<IData>(data); \
        (owp)[1] = static_cast<IData>((data) >> VL_EDATASIZE); \
    } while (false)
#define VL_SET_WI(owp, data) \
    do { \
        (owp)[0] = static_cast<IData>(data); \
        (owp)[1] = 0; \
    } while (false)
#define VL_SET_QW(lwp) \
    ((static_cast<QData>((lwp)[0])) \
     | (static_cast<QData>((lwp)[1]) << (static_cast<QData>(VL_EDATASIZE))))
#define VL_SET_QII(ld, rd) ((static_cast<QData>(ld) << 32ULL) | static_cast<QData>(rd))

// Return FILE* from IData
extern FILE* VL_CVT_I_FP(IData lhs) VL_MT_SAFE;

// clang-format off
// Use a union to avoid cast-to-different-size warnings
// Return void* from QData
static inline void* VL_CVT_Q_VP(QData lhs) VL_PURE {
    union { void* fp; QData q; } u;
    u.q = lhs;
    return u.fp;
}
// Return QData from const void*
static inline QData VL_CVT_VP_Q(const void* fp) VL_PURE {
    union { const void* fp; QData q; } u;
    u.q = 0;
    u.fp = fp;
    return u.q;
}
// Return double from QData (bits, not numerically)
static inline double VL_CVT_D_Q(QData lhs) VL_PURE {
    union { double d; QData q; } u;
    u.q = lhs;
    return u.d;
}
// Return QData from double (bits, not numerically)
static inline QData VL_CVT_Q_D(double lhs) VL_PURE {
    union { double d; QData q; } u;
    u.d = lhs;
    return u.q;
}
// clang-format on
// Return string from DPI char*
static inline std::string VL_CVT_N_CSTR(const char* lhsp) VL_PURE {
    return lhsp ? std::string{lhsp} : ""s;
}

// Return queue from an unpacked array
template <typename T, std::size_t N_Depth>
static inline VlQueue<T> VL_CVT_UNPACK_TO_Q(const VlUnpacked<T, N_Depth>& q) VL_PURE {
    VlQueue<T> ret;
    for (size_t i = 0; i < N_Depth; ++i) ret.push_back(q[i]);
    return ret;
}

// Return double from lhs (numeric) unsigned
double VL_ITOR_D_W(int lbits, WDataInP const lwp) VL_PURE;
static inline double VL_ITOR_D_I(int, IData lhs) VL_PURE {
    return static_cast<double>(static_cast<uint32_t>(lhs));
}
static inline double VL_ITOR_D_Q(int, QData lhs) VL_PURE {
    return static_cast<double>(static_cast<uint64_t>(lhs));
}
// Return double from lhs (numeric) signed
double VL_ISTOR_D_W(int lbits, WDataInP const lwp) VL_MT_SAFE;
static inline double VL_ISTOR_D_I(int lbits, IData lhs) VL_MT_SAFE {
    if (lbits == 32) return static_cast<double>(static_cast<int32_t>(lhs));
    VlWide<VL_WQ_WORDS_E> lwp;
    VL_SET_WI(lwp, lhs);
    return VL_ISTOR_D_W(lbits, lwp);
}
static inline double VL_ISTOR_D_Q(int lbits, QData lhs) VL_MT_SAFE {
    if (lbits == 64) return static_cast<double>(static_cast<int64_t>(lhs));
    VlWide<VL_WQ_WORDS_E> lwp;
    VL_SET_WQ(lwp, lhs);
    return VL_ISTOR_D_W(lbits, lwp);
}
// Return IData truncated from double (numeric)
static inline IData VL_RTOI_I_D(double lhs) VL_PURE { return static_cast<int32_t>(VL_TRUNC(lhs)); }

// Sign extend such that if MSB set, we get ffff_ffff, else 0s
// (Requires clean input)
#define VL_SIGN_I(nbits, lhs) ((lhs) >> VL_BITBIT_I((nbits) - VL_UL(1)))
#define VL_SIGN_Q(nbits, lhs) ((lhs) >> VL_BITBIT_Q((nbits) - 1ULL))
#define VL_SIGN_E(nbits, lhs) ((lhs) >> VL_BITBIT_E((nbits) - VL_EUL(1)))
#define VL_SIGN_W(nbits, rwp) \
    ((rwp)[VL_BITWORD_E((nbits) - VL_EUL(1))] >> VL_BITBIT_E((nbits) - VL_EUL(1)))
#define VL_SIGNONES_E(nbits, lhs) (-(VL_SIGN_E(nbits, lhs)))

// Sign bit extended up to MSB, doesn't include unsigned portion
// Optimization bug in GCC 3.3 returns different bitmasks to later states for
static inline IData VL_EXTENDSIGN_I(int lbits, IData lhs) VL_PURE {
    return (-((lhs) & (VL_UL(1) << (lbits - 1))));
}
static inline QData VL_EXTENDSIGN_Q(int lbits, QData lhs) VL_PURE {
    return (-((lhs) & (1ULL << (lbits - 1))));
}

// Debugging prints
extern void _vl_debug_print_w(int lbits, WDataInP const iwp) VL_MT_SAFE;

//=========================================================================
// Time handling

// clang-format off

#if defined(SYSTEMC_VERSION)
/// Return current simulation time
// Already defined: extern sc_time sc_time_stamp();
inline uint64_t vl_time_stamp64() VL_MT_SAFE { return sc_core::sc_time_stamp().value(); }
#else  // Non-SystemC
# if !defined(VL_TIME_CONTEXT) && !defined(VL_NO_LEGACY)
#  ifdef VL_TIME_STAMP64
// vl_time_stamp64() may be optionally defined by the user to return time.
// On MSVC++ weak symbols are not supported so must be declared, or define
// VL_TIME_CONTEXT.
extern uint64_t vl_time_stamp64() VL_ATTR_WEAK VL_MT_SAFE;
#  else
// sc_time_stamp() may be optionally defined by the user to return time.
// On MSVC++ weak symbols are not supported so must be declared, or define
// VL_TIME_CONTEXT.
extern double sc_time_stamp() VL_ATTR_WEAK VL_MT_SAFE;  // Verilator 4.032 and newer
inline uint64_t vl_time_stamp64() VL_MT_SAFE {
    // clang9.0.1 requires & although we really do want the weak symbol value
    // cppcheck-suppress duplicateValueTernary
    return VL_LIKELY(&sc_time_stamp) ? static_cast<uint64_t>(sc_time_stamp()) : 0;
}
#  endif
# endif
#endif

// clang-format on

uint64_t VerilatedContext::time() const VL_MT_SAFE {
    // When using non-default context, fastest path is return time
    if (VL_LIKELY(m_s.m_time)) return m_s.m_time;
#if defined(SYSTEMC_VERSION) || (!defined(VL_TIME_CONTEXT) && !defined(VL_NO_LEGACY))
    // Zero time could mean really at zero, or using callback
    // clang9.0.1 requires & although we really do want the weak symbol value
    if (VL_LIKELY(&vl_time_stamp64)) {  // else is weak symbol that is not defined
        return vl_time_stamp64();
    }
#endif
    return 0;
}

#define VL_TIME_Q() (Verilated::threadContextp()->time())
#define VL_TIME_D() (static_cast<double>(VL_TIME_Q()))

// Time scaled from 1-per-precision into a module's time units ("Unit"-ed, not "United")
// Optimized assuming scale is always constant.
// Can't use multiply in Q flavor, as might lose precision
#define VL_TIME_ROUND(t, p) (((t) + ((p) / 2)) / (p))
#define VL_TIME_UNITED_Q(scale) VL_TIME_ROUND(VL_TIME_Q(), static_cast<QData>(scale))
#define VL_TIME_UNITED_D(scale) (VL_TIME_D() / static_cast<double>(scale))

// Return time precision as multiplier of time units
double vl_time_multiplier(int scale) VL_PURE;
// Return power of 10. e.g. returns 100 if n==2
uint64_t vl_time_pow10(int n) VL_PURE;
// Return time as string with timescale suffix
std::string vl_timescaled_double(double value, const char* format = "%0.0f%s") VL_PURE;

//=========================================================================
// Functional macros/routines
// These all take the form
//      VL_func_IW(bits, bits, op, op)
//      VL_func_WW(bits, bits, out, op, op)
// The I/W indicates if it's a integer or wide for the output and each operand.
// The bits indicate the bit width of the output and each operand.
// If wide output, a temporary storage location is specified.

//===================================================================
// SETTING OPERATORS

VL_ATTR_ALWINLINE
static WDataOutP VL_MEMSET_ZERO_W(WDataOutP owp, int words) VL_MT_SAFE {
    return static_cast<WDataOutP>(std::memset(owp, 0, words * sizeof(EData)));
}
VL_ATTR_ALWINLINE
static WDataOutP VL_MEMSET_ONES_W(WDataOutP owp, int words) VL_MT_SAFE {
    return static_cast<WDataOutP>(std::memset(owp, 0xff, words * sizeof(EData)));
}
VL_ATTR_ALWINLINE
static WDataOutP VL_MEMCPY_W(WDataOutP owp, WDataInP const iwp, int words) VL_MT_SAFE {
    return static_cast<WDataOutP>(std::memcpy(owp, iwp, words * sizeof(EData)));
}

// Output clean
// EMIT_RULE: VL_CLEAN:  oclean=clean; obits=lbits;
#define VL_CLEAN_II(obits, lbits, lhs) ((lhs) & (VL_MASK_I(obits)))
#define VL_CLEAN_QQ(obits, lbits, lhs) ((lhs) & (VL_MASK_Q(obits)))

// EMIT_RULE: VL_ASSIGNCLEAN:  oclean=clean; obits==lbits;
#define VL_ASSIGNCLEAN_W(obits, owp, lwp) VL_CLEAN_WW((obits), (owp), (lwp))
static inline WDataOutP _vl_clean_inplace_w(int obits, WDataOutP owp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    owp[words - 1] &= VL_MASK_E(obits);
    return owp;
}
static inline WDataOutP VL_CLEAN_WW(int obits, WDataOutP owp, WDataInP const lwp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    VL_MEMCPY_W(owp, lwp, words - 1);
    owp[words - 1] = lwp[words - 1] & VL_MASK_E(obits);
    return owp;
}
static inline WDataOutP VL_ZERO_W(int obits, WDataOutP owp) VL_MT_SAFE {
    return VL_MEMSET_ZERO_W(owp, VL_WORDS_I(obits));
}
static inline WDataOutP VL_ALLONES_W(int obits, WDataOutP owp) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    VL_MEMSET_ONES_W(owp, words - 1);
    owp[words - 1] = VL_MASK_E(obits);
    return owp;
}

// EMIT_RULE: VL_ASSIGN:  oclean=rclean; obits==lbits;
// For now, we always have a clean rhs.
// Note: If a ASSIGN isn't clean, use VL_ASSIGNCLEAN instead to do the same thing.
static inline WDataOutP VL_ASSIGN_W(int obits, WDataOutP owp, WDataInP const lwp) VL_MT_SAFE {
    return VL_MEMCPY_W(owp, lwp, VL_WORDS_I(obits));
}

// EMIT_RULE: VL_ASSIGNBIT:  rclean=clean;
static inline void VL_ASSIGNBIT_II(int bit, CData& lhsr, IData rhs) VL_PURE {
    lhsr = ((lhsr & ~(VL_UL(1) << VL_BITBIT_I(bit))) | (rhs << VL_BITBIT_I(bit)));
}
static inline void VL_ASSIGNBIT_II(int bit, SData& lhsr, IData rhs) VL_PURE {
    lhsr = ((lhsr & ~(VL_UL(1) << VL_BITBIT_I(bit))) | (rhs << VL_BITBIT_I(bit)));
}
static inline void VL_ASSIGNBIT_II(int bit, IData& lhsr, IData rhs) VL_PURE {
    lhsr = ((lhsr & ~(VL_UL(1) << VL_BITBIT_I(bit))) | (rhs << VL_BITBIT_I(bit)));
}
static inline void VL_ASSIGNBIT_QI(int bit, QData& lhsr, QData rhs) VL_PURE {
    lhsr = ((lhsr & ~(1ULL << VL_BITBIT_Q(bit))) | (static_cast<QData>(rhs) << VL_BITBIT_Q(bit)));
}
static inline void VL_ASSIGNBIT_WI(int bit, WDataOutP owp, IData rhs) VL_MT_SAFE {
    const EData orig = owp[VL_BITWORD_E(bit)];
    owp[VL_BITWORD_E(bit)] = ((orig & ~(VL_EUL(1) << VL_BITBIT_E(bit)))
                              | (static_cast<EData>(rhs) << VL_BITBIT_E(bit)));
}
// Alternative form that is an instruction faster when rhs is constant one.
static inline void VL_ASSIGNBIT_IO(int bit, CData& lhsr) VL_PURE {
    lhsr = (lhsr | (VL_UL(1) << VL_BITBIT_I(bit)));
}
static inline void VL_ASSIGNBIT_IO(int bit, SData& lhsr) VL_PURE {
    lhsr = (lhsr | (VL_UL(1) << VL_BITBIT_I(bit)));
}
static inline void VL_ASSIGNBIT_IO(int bit, IData& lhsr) VL_PURE {
    lhsr = (lhsr | (VL_UL(1) << VL_BITBIT_I(bit)));
}
static inline void VL_ASSIGNBIT_QO(int bit, QData& lhsr) VL_PURE {
    lhsr = (lhsr | (1ULL << VL_BITBIT_Q(bit)));
}
static inline void VL_ASSIGNBIT_WO(int bit, WDataOutP owp) VL_MT_SAFE {
    const EData orig = owp[VL_BITWORD_E(bit)];
    owp[VL_BITWORD_E(bit)] = (orig | (VL_EUL(1) << VL_BITBIT_E(bit)));
}

//===================================================================
// SYSTEMC OPERATORS
// Copying verilog format to systemc integers, doubles, and bit vectors.
// Get a SystemC variable

#define VL_ASSIGN_DSD(obits, vvar, svar) \
    { (vvar) = (svar).read(); }
#define VL_ASSIGN_ISI(obits, vvar, svar) \
    { (vvar) = VL_CLEAN_II((obits), (obits), (svar).read()); }
#define VL_ASSIGN_QSQ(obits, vvar, svar) \
    { (vvar) = VL_CLEAN_QQ((obits), (obits), (svar).read()); }

#define VL_ASSIGN_ISW(obits, od, svar) \
    { (od) = ((svar).read().get_word(0)) & VL_MASK_I(obits); }
#define VL_ASSIGN_QSW(obits, od, svar) \
    { \
        (od) = ((static_cast<QData>((svar).read().get_word(1))) << VL_IDATASIZE \
                | (svar).read().get_word(0)) \
               & VL_MASK_Q(obits); \
    }
#define VL_ASSIGN_WSW(obits, owp, svar) \
    { \
        const int words = VL_WORDS_I(obits); \
        for (int i = 0; i < words; ++i) (owp)[i] = (svar).read().get_word(i); \
        (owp)[words - 1] &= VL_MASK_E(obits); \
    }

#define VL_ASSIGN_ISU(obits, vvar, svar) \
    { (vvar) = VL_CLEAN_II((obits), (obits), (svar).read().to_uint()); }
#define VL_ASSIGN_QSU(obits, vvar, svar) \
    { (vvar) = VL_CLEAN_QQ((obits), (obits), (svar).read().to_uint64()); }
#define VL_ASSIGN_ISB(obits, vvar, svar) \
    { (vvar) = VL_CLEAN_II((obits), (obits), (svar).read().to_uint()); }
#define VL_ASSIGN_QSB(obits, vvar, svar) \
    { (vvar) = VL_CLEAN_QQ((obits), (obits), (svar).read().to_uint64()); }
#define VL_ASSIGN_WSB(obits, owp, svar) \
    { \
        const int words = VL_WORDS_I(obits); \
        sc_dt::sc_biguint<(obits)> _butemp = (svar).read(); \
        uint32_t* chunkp = _butemp.get_raw(); \
        int32_t lsb = 0; \
        while (lsb < obits - BITS_PER_DIGIT) { \
            const uint32_t data = *chunkp; \
            ++chunkp; \
            _vl_insert_WI(owp.data(), data, lsb + BITS_PER_DIGIT - 1, lsb); \
            lsb += BITS_PER_DIGIT; \
        } \
        if (lsb < obits) { \
            const uint32_t msb_data = *chunkp; \
            _vl_insert_WI(owp.data(), msb_data, obits - 1, lsb); \
        } \
        (owp)[words - 1] &= VL_MASK_E(obits); \
    }

// Copying verilog format from systemc integers, doubles, and bit vectors.
// Set a SystemC variable

#define VL_ASSIGN_SDD(obits, svar, vvar) \
    { (svar).write(vvar); }
#define VL_ASSIGN_SII(obits, svar, vvar) \
    { (svar).write(vvar); }
#define VL_ASSIGN_SQQ(obits, svar, vvar) \
    { (svar).write(vvar); }

#define VL_ASSIGN_SWI(obits, svar, rd) \
    { \
        sc_dt::sc_bv<(obits)> _bvtemp; \
        _bvtemp.set_word(0, (rd)); \
        (svar).write(_bvtemp); \
    }
#define VL_ASSIGN_SWQ(obits, svar, rd) \
    { \
        sc_dt::sc_bv<(obits)> _bvtemp; \
        _bvtemp.set_word(0, static_cast<IData>(rd)); \
        _bvtemp.set_word(1, static_cast<IData>((rd) >> VL_IDATASIZE)); \
        (svar).write(_bvtemp); \
    }
#define VL_ASSIGN_SWW(obits, svar, rwp) \
    { \
        sc_dt::sc_bv<(obits)> _bvtemp; \
        for (int i = 0; i < VL_WORDS_I(obits); ++i) _bvtemp.set_word(i, (rwp)[i]); \
        (svar).write(_bvtemp); \
    }

#define VL_ASSIGN_SUI(obits, svar, rd) \
    { (svar).write(rd); }
#define VL_ASSIGN_SUQ(obits, svar, rd) \
    { (svar).write(rd); }
#define VL_ASSIGN_SBI(obits, svar, rd) \
    { (svar).write(rd); }
#define VL_ASSIGN_SBQ(obits, svar, rd) \
    { (svar).write(rd); }
#define VL_ASSIGN_SBW(obits, svar, rwp) \
    { \
        sc_dt::sc_biguint<(obits)> _butemp; \
        int32_t lsb = 0; \
        uint32_t* chunkp = _butemp.get_raw(); \
        while (lsb + BITS_PER_DIGIT < (obits)) { \
            static_assert(std::is_same<IData, EData>::value, "IData and EData mismatch"); \
            const uint32_t data \
                = VL_SEL_IWII(lsb + BITS_PER_DIGIT + 1, (rwp).data(), lsb, BITS_PER_DIGIT); \
            *chunkp = data & VL_MASK_E(BITS_PER_DIGIT); \
            ++chunkp; \
            lsb += BITS_PER_DIGIT; \
        } \
        if (lsb < (obits)) { \
            const uint32_t msb_data = VL_SEL_IWII((obits) + 1, (rwp).data(), lsb, (obits) - lsb); \
            *chunkp = msb_data & VL_MASK_E((obits) - lsb); \
        } \
        _butemp.set(0, *(rwp).data() & 1); /* force update the sign */ \
        (svar).write(_butemp); \
    }

//===================================================================
// Extending sizes

// CAREFUL, we're width changing, so obits!=lbits

// Right must be clean because otherwise size increase would pick up bad bits
// EMIT_RULE: VL_EXTEND:  oclean=clean; rclean==clean;
#define VL_EXTEND_II(obits, lbits, lhs) ((lhs))
#define VL_EXTEND_QI(obits, lbits, lhs) (static_cast<QData>(lhs))
#define VL_EXTEND_QQ(obits, lbits, lhs) ((lhs))

static inline WDataOutP VL_EXTEND_WI(int obits, int, WDataOutP owp, IData ld) VL_MT_SAFE {
    // Note for extracts that obits != lbits
    owp[0] = ld;
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    return owp;
}
static inline WDataOutP VL_EXTEND_WQ(int obits, int, WDataOutP owp, QData ld) VL_MT_SAFE {
    VL_SET_WQ(owp, ld);
    VL_MEMSET_ZERO_W(owp + VL_WQ_WORDS_E, VL_WORDS_I(obits) - VL_WQ_WORDS_E);
    return owp;
}
static inline WDataOutP VL_EXTEND_WW(int obits, int lbits, WDataOutP owp,
                                     WDataInP const lwp) VL_MT_SAFE {
    const int lwords = VL_WORDS_I(lbits);
    VL_PREFETCH_RD(lwp);
    VL_MEMSET_ZERO_W(owp + lwords, VL_WORDS_I(obits) - lwords);
    return VL_MEMCPY_W(owp, lwp, lwords);
}

// EMIT_RULE: VL_EXTENDS:  oclean=*dirty*; obits=lbits;
// Sign extension; output dirty
static inline IData VL_EXTENDS_II(int, int lbits, IData lhs) VL_PURE {
    return VL_EXTENDSIGN_I(lbits, lhs) | lhs;
}
static inline QData VL_EXTENDS_QI(int, int lbits, QData lhs /*Q_as_need_extended*/) VL_PURE {
    return VL_EXTENDSIGN_Q(lbits, lhs) | lhs;
}
static inline QData VL_EXTENDS_QQ(int, int lbits, QData lhs) VL_PURE {
    return VL_EXTENDSIGN_Q(lbits, lhs) | lhs;
}

static inline WDataOutP VL_EXTENDS_WI(int obits, int lbits, WDataOutP owp, IData ld) VL_MT_SAFE {
    owp[0] = ld;
    if (VL_SIGN_E(lbits, owp[0])) {
        owp[0] |= ~VL_MASK_E(lbits);
        VL_MEMSET_ONES_W(owp + 1, VL_WORDS_I(obits) - 1);
    } else {
        VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    }
    return owp;
}
static inline WDataOutP VL_EXTENDS_WQ(int obits, int lbits, WDataOutP owp, QData ld) VL_MT_SAFE {
    VL_SET_WQ(owp, ld);
    if (VL_SIGN_E(lbits, owp[1])) {
        owp[1] |= ~VL_MASK_E(lbits);
        VL_MEMSET_ONES_W(owp + VL_WQ_WORDS_E, VL_WORDS_I(obits) - VL_WQ_WORDS_E);
    } else {
        VL_MEMSET_ZERO_W(owp + VL_WQ_WORDS_E, VL_WORDS_I(obits) - VL_WQ_WORDS_E);
    }
    return owp;
}
static inline WDataOutP VL_EXTENDS_WW(int obits, int lbits, WDataOutP owp,
                                      WDataInP const lwp) VL_MT_SAFE {
    const int lwords = VL_WORDS_I(lbits);
    VL_PREFETCH_RD(lwp);
    owp[lwords - 1] = lwp[lwords - 1];
    if (VL_SIGN_E(lbits, lwp[lwords - 1])) {
        owp[lwords - 1] |= ~VL_MASK_E(lbits);
        VL_MEMSET_ONES_W(owp + lwords, VL_WORDS_I(obits) - lwords);
    } else {
        VL_MEMSET_ZERO_W(owp + lwords, VL_WORDS_I(obits) - lwords);
    }
    return VL_MEMCPY_W(owp, lwp, lwords - 1);
}

//===================================================================
// REDUCTION OPERATORS

// EMIT_RULE: VL_REDAND:  oclean=clean; lclean==clean; obits=1;
#define VL_REDAND_II(lbits, lhs) ((lhs) == VL_MASK_I(lbits))
#define VL_REDAND_IQ(lbits, lhs) ((lhs) == VL_MASK_Q(lbits))
static inline IData VL_REDAND_IW(int lbits, WDataInP const lwp) VL_PURE {
    const int words = VL_WORDS_I(lbits);
    EData combine = lwp[0];
    for (int i = 1; i < words - 1; ++i) combine &= lwp[i];
    combine &= ~VL_MASK_E(lbits) | lwp[words - 1];
    // cppcheck-suppress knownConditionTrueFalse
    return ((~combine) == 0);
}

// EMIT_RULE: VL_REDOR:  oclean=clean; lclean==clean; obits=1;
#define VL_REDOR_I(lhs) ((lhs) != 0)
#define VL_REDOR_Q(lhs) ((lhs) != 0)
static inline IData VL_REDOR_W(int words, WDataInP const lwp) VL_PURE {
    EData equal = 0;
    for (int i = 0; i < words; ++i) equal |= lwp[i];
    return (equal != 0);
}

// EMIT_RULE: VL_REDXOR:  oclean=dirty; obits=1;
static inline IData VL_REDXOR_2(IData r) VL_PURE {
    // Experiments show VL_REDXOR_2 is faster than __builtin_parityl
    r = (r ^ (r >> 1));
    return r;
}
static inline IData VL_REDXOR_4(IData r) VL_PURE {
#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(VL_NO_BUILTINS)
    return __builtin_parityl(r);
#else
    r = (r ^ (r >> 1));
    r = (r ^ (r >> 2));
    return r;
#endif
}
static inline IData VL_REDXOR_8(IData r) VL_PURE {
#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(VL_NO_BUILTINS)
    return __builtin_parityl(r);
#else
    r = (r ^ (r >> 1));
    r = (r ^ (r >> 2));
    r = (r ^ (r >> 4));
    return r;
#endif
}
static inline IData VL_REDXOR_16(IData r) VL_PURE {
#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(VL_NO_BUILTINS)
    return __builtin_parityl(r);
#else
    r = (r ^ (r >> 1));
    r = (r ^ (r >> 2));
    r = (r ^ (r >> 4));
    r = (r ^ (r >> 8));
    return r;
#endif
}
static inline IData VL_REDXOR_32(IData r) VL_PURE {
#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(VL_NO_BUILTINS)
    return __builtin_parityl(r);
#else
    r = (r ^ (r >> 1));
    r = (r ^ (r >> 2));
    r = (r ^ (r >> 4));
    r = (r ^ (r >> 8));
    r = (r ^ (r >> 16));
    return r;
#endif
}
static inline IData VL_REDXOR_64(QData r) VL_PURE {
#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(VL_NO_BUILTINS)
    return __builtin_parityll(r);
#else
    r = (r ^ (r >> 1));
    r = (r ^ (r >> 2));
    r = (r ^ (r >> 4));
    r = (r ^ (r >> 8));
    r = (r ^ (r >> 16));
    r = (r ^ (r >> 32));
    return static_cast<IData>(r);
#endif
}
static inline IData VL_REDXOR_W(int words, WDataInP const lwp) VL_PURE {
    EData r = lwp[0];
    for (int i = 1; i < words; ++i) r ^= lwp[i];
    return VL_REDXOR_32(r);
}

// EMIT_RULE: VL_COUNTONES_II:  oclean = false; lhs clean
static inline IData VL_COUNTONES_I(IData lhs) VL_PURE {
    // This is faster than __builtin_popcountl
    IData r = lhs - ((lhs >> 1) & 033333333333) - ((lhs >> 2) & 011111111111);
    r = (r + (r >> 3)) & 030707070707;
    r = (r + (r >> 6));
    r = (r + (r >> 12) + (r >> 24)) & 077;
    return r;
}
static inline IData VL_COUNTONES_Q(QData lhs) VL_PURE {
    return VL_COUNTONES_I(static_cast<IData>(lhs)) + VL_COUNTONES_I(static_cast<IData>(lhs >> 32));
}
#define VL_COUNTONES_E VL_COUNTONES_I
static inline IData VL_COUNTONES_W(int words, WDataInP const lwp) VL_PURE {
    EData r = 0;
    for (int i = 0; i < words; ++i) r += VL_COUNTONES_E(lwp[i]);
    return r;
}

// EMIT_RULE: VL_COUNTBITS_II:  oclean = false; lhs clean
static inline IData VL_COUNTBITS_I(int lbits, IData lhs, IData ctrl0, IData ctrl1,
                                   IData ctrl2) VL_PURE {
    const int ctrlSum = (ctrl0 & 0x1) + (ctrl1 & 0x1) + (ctrl2 & 0x1);
    if (ctrlSum == 3) {
        return VL_COUNTONES_I(lhs);
    } else if (ctrlSum == 0) {
        const IData mask = (lbits == 32) ? -1 : ((1 << lbits) - 1);
        return VL_COUNTONES_I(~lhs & mask);
    } else {
        return (lbits == 32) ? 32 : lbits;
    }
}
static inline IData VL_COUNTBITS_Q(int lbits, QData lhs, IData ctrl0, IData ctrl1,
                                   IData ctrl2) VL_PURE {
    return VL_COUNTBITS_I(32, static_cast<IData>(lhs), ctrl0, ctrl1, ctrl2)
           + VL_COUNTBITS_I(lbits - 32, static_cast<IData>(lhs >> 32), ctrl0, ctrl1, ctrl2);
}
#define VL_COUNTBITS_E VL_COUNTBITS_I
static inline IData VL_COUNTBITS_W(int lbits, int words, WDataInP const lwp, IData ctrl0,
                                   IData ctrl1, IData ctrl2) VL_MT_SAFE {
    EData r = 0;
    IData wordLbits = 32;
    for (int i = 0; i < words; ++i) {
        if (i == words - 1) wordLbits = lbits % 32;
        r += VL_COUNTBITS_E(wordLbits, lwp[i], ctrl0, ctrl1, ctrl2);
    }
    return r;
}

static inline IData VL_ONEHOT_I(IData lhs) VL_PURE {
    return (((lhs & (lhs - 1)) == 0) & (lhs != 0));
}
static inline IData VL_ONEHOT_Q(QData lhs) VL_PURE {
    return (((lhs & (lhs - 1)) == 0) & (lhs != 0));
}
static inline IData VL_ONEHOT_W(int words, WDataInP const lwp) VL_PURE {
    EData one = 0;
    for (int i = 0; (i < words); ++i) {
        if (lwp[i]) {
            if (one) return 0;
            one = 1;
            if (lwp[i] & (lwp[i] - 1)) return 0;
        }
    }
    return one;
}

static inline IData VL_ONEHOT0_I(IData lhs) VL_PURE { return ((lhs & (lhs - 1)) == 0); }
static inline IData VL_ONEHOT0_Q(QData lhs) VL_PURE { return ((lhs & (lhs - 1)) == 0); }
static inline IData VL_ONEHOT0_W(int words, WDataInP const lwp) VL_PURE {
    bool one = false;
    for (int i = 0; (i < words); ++i) {
        if (lwp[i]) {
            if (one) return 0;
            one = true;
            if (lwp[i] & (lwp[i] - 1)) return 0;
        }
    }
    return 1;
}

static inline IData VL_CLOG2_I(IData lhs) VL_PURE {
    // There are faster algorithms, or fls GCC4 builtins, but rarely used
    // In C++20 there will be std::bit_width(lhs) - 1
    if (VL_UNLIKELY(!lhs)) return 0;
    --lhs;
    int shifts = 0;
    for (; lhs != 0; ++shifts) lhs = lhs >> 1;
    return shifts;
}
static inline IData VL_CLOG2_Q(QData lhs) VL_PURE {
    if (VL_UNLIKELY(!lhs)) return 0;
    --lhs;
    int shifts = 0;
    for (; lhs != 0; ++shifts) lhs = lhs >> 1ULL;
    return shifts;
}
static inline IData VL_CLOG2_W(int words, WDataInP const lwp) VL_PURE {
    const EData adjust = (VL_COUNTONES_W(words, lwp) == 1) ? 0 : 1;
    for (int i = words - 1; i >= 0; --i) {
        if (VL_UNLIKELY(lwp[i])) {  // Shorter worst case if predict not taken
            for (int bit = VL_EDATASIZE - 1; bit >= 0; --bit) {
                if (VL_UNLIKELY(VL_BITISSET_E(lwp[i], bit))) {
                    return i * VL_EDATASIZE + bit + adjust;
                }
            }
            // Can't get here - one bit must be set
        }
    }
    return 0;
}

static inline IData VL_MOSTSETBITP1_W(int words, WDataInP const lwp) VL_PURE {
    // MSB set bit plus one; similar to FLS.  0=value is zero
    for (int i = words - 1; i >= 0; --i) {
        if (VL_UNLIKELY(lwp[i])) {  // Shorter worst case if predict not taken
            for (int bit = VL_EDATASIZE - 1; bit >= 0; --bit) {
                if (VL_UNLIKELY(VL_BITISSET_E(lwp[i], bit))) return i * VL_EDATASIZE + bit + 1;
            }
            // Can't get here - one bit must be set
        }
    }
    return 0;
}

//===================================================================
// SIMPLE LOGICAL OPERATORS

// EMIT_RULE: VL_AND:  oclean=lclean||rclean; obits=lbits; lbits==rbits;
static inline WDataOutP VL_AND_W(int words, WDataOutP owp, WDataInP const lwp,
                                 WDataInP const rwp) VL_MT_SAFE {
    for (int i = 0; (i < words); ++i) owp[i] = (lwp[i] & rwp[i]);
    return owp;
}
// EMIT_RULE: VL_OR:   oclean=lclean&&rclean; obits=lbits; lbits==rbits;
static inline WDataOutP VL_OR_W(int words, WDataOutP owp, WDataInP const lwp,
                                WDataInP const rwp) VL_MT_SAFE {
    for (int i = 0; (i < words); ++i) owp[i] = (lwp[i] | rwp[i]);
    return owp;
}
// EMIT_RULE: VL_CHANGEXOR:  oclean=1; obits=32; lbits==rbits;
static inline IData VL_CHANGEXOR_W(int words, WDataInP const lwp, WDataInP const rwp) VL_PURE {
    IData od = 0;
    for (int i = 0; (i < words); ++i) od |= (lwp[i] ^ rwp[i]);
    return od;
}
// EMIT_RULE: VL_XOR:  oclean=lclean&&rclean; obits=lbits; lbits==rbits;
static inline WDataOutP VL_XOR_W(int words, WDataOutP owp, WDataInP const lwp,
                                 WDataInP const rwp) VL_MT_SAFE {
    for (int i = 0; (i < words); ++i) owp[i] = (lwp[i] ^ rwp[i]);
    return owp;
}
// EMIT_RULE: VL_NOT:  oclean=dirty; obits=lbits;
static inline WDataOutP VL_NOT_W(int words, WDataOutP owp, WDataInP const lwp) VL_MT_SAFE {
    for (int i = 0; i < words; ++i) owp[i] = ~(lwp[i]);
    return owp;
}

//=========================================================================
// Logical comparisons

// EMIT_RULE: VL_EQ:  oclean=clean; lclean==clean; rclean==clean; obits=1; lbits==rbits;
// EMIT_RULE: VL_NEQ: oclean=clean; lclean==clean; rclean==clean; obits=1; lbits==rbits;
// EMIT_RULE: VL_LT:  oclean=clean; lclean==clean; rclean==clean; obits=1; lbits==rbits;
// EMIT_RULE: VL_GT:  oclean=clean; lclean==clean; rclean==clean; obits=1; lbits==rbits;
// EMIT_RULE: VL_GTE: oclean=clean; lclean==clean; rclean==clean; obits=1; lbits==rbits;
// EMIT_RULE: VL_LTE: oclean=clean; lclean==clean; rclean==clean; obits=1; lbits==rbits;
#define VL_NEQ_W(words, lwp, rwp) (!VL_EQ_W(words, lwp, rwp))
#define VL_LT_W(words, lwp, rwp) (_vl_cmp_w(words, lwp, rwp) < 0)
#define VL_LTE_W(words, lwp, rwp) (_vl_cmp_w(words, lwp, rwp) <= 0)
#define VL_GT_W(words, lwp, rwp) (_vl_cmp_w(words, lwp, rwp) > 0)
#define VL_GTE_W(words, lwp, rwp) (_vl_cmp_w(words, lwp, rwp) >= 0)

// Output clean, <lhs> AND <rhs> MUST BE CLEAN
static inline IData VL_EQ_W(int words, WDataInP const lwp, WDataInP const rwp) VL_PURE {
    EData nequal = 0;
    for (int i = 0; (i < words); ++i) nequal |= (lwp[i] ^ rwp[i]);
    return (nequal == 0);
}

// Internal usage
static inline int _vl_cmp_w(int words, WDataInP const lwp, WDataInP const rwp) VL_PURE {
    for (int i = words - 1; i >= 0; --i) {
        if (lwp[i] > rwp[i]) return 1;
        if (lwp[i] < rwp[i]) return -1;
    }
    return 0;  // ==
}

#define VL_LTS_IWW(lbits, lwp, rwp) (_vl_cmps_w(lbits, lwp, rwp) < 0)
#define VL_LTES_IWW(lbits, lwp, rwp) (_vl_cmps_w(lbits, lwp, rwp) <= 0)
#define VL_GTS_IWW(lbits, lwp, rwp) (_vl_cmps_w(lbits, lwp, rwp) > 0)
#define VL_GTES_IWW(lbits, lwp, rwp) (_vl_cmps_w(lbits, lwp, rwp) >= 0)

static inline IData VL_GTS_III(int lbits, IData lhs, IData rhs) VL_PURE {
    // For lbits==32, this becomes just a single instruction, otherwise ~5.
    // GCC 3.3.4 sign extension bugs on AMD64 architecture force us to use quad logic
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);  // Q for gcc
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);  // Q for gcc
    return lhs_signed > rhs_signed;
}
static inline IData VL_GTS_IQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);
    return lhs_signed > rhs_signed;
}

static inline IData VL_GTES_III(int lbits, IData lhs, IData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);  // Q for gcc
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);  // Q for gcc
    return lhs_signed >= rhs_signed;
}
static inline IData VL_GTES_IQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);
    return lhs_signed >= rhs_signed;
}

static inline IData VL_LTS_III(int lbits, IData lhs, IData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);  // Q for gcc
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);  // Q for gcc
    return lhs_signed < rhs_signed;
}
static inline IData VL_LTS_IQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);
    return lhs_signed < rhs_signed;
}

static inline IData VL_LTES_III(int lbits, IData lhs, IData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);  // Q for gcc
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);  // Q for gcc
    return lhs_signed <= rhs_signed;
}
static inline IData VL_LTES_IQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);
    return lhs_signed <= rhs_signed;
}

static inline int _vl_cmps_w(int lbits, WDataInP const lwp, WDataInP const rwp) VL_PURE {
    const int words = VL_WORDS_I(lbits);
    int i = words - 1;
    // We need to flip sense if negative comparison
    const EData lsign = VL_SIGN_E(lbits, lwp[i]);
    const EData rsign = VL_SIGN_E(lbits, rwp[i]);
    if (!lsign && rsign) return 1;  // + > -
    if (lsign && !rsign) return -1;  // - < +
    for (; i >= 0; --i) {
        if (lwp[i] > rwp[i]) return 1;
        if (lwp[i] < rwp[i]) return -1;
    }
    return 0;  // ==
}

//=========================================================================
// Expressions

// Output NOT clean
static inline WDataOutP VL_NEGATE_W(int words, WDataOutP owp, WDataInP const lwp) VL_MT_SAFE {
    EData carry = 1;
    for (int i = 0; i < words; ++i) {
        owp[i] = ~lwp[i] + carry;
        carry = (owp[i] < ~lwp[i]);
    }
    return owp;
}
static inline void VL_NEGATE_INPLACE_W(int words, WDataOutP owp_lwp) VL_MT_SAFE {
    EData carry = 1;
    for (int i = 0; i < words; ++i) {
        const EData word = ~owp_lwp[i] + carry;
        carry = (word < ~owp_lwp[i]);
        owp_lwp[i] = word;
    }
}

// EMIT_RULE: VL_MUL:    oclean=dirty; lclean==clean; rclean==clean;
// EMIT_RULE: VL_DIV:    oclean=dirty; lclean==clean; rclean==clean;
// EMIT_RULE: VL_MODDIV: oclean=dirty; lclean==clean; rclean==clean;
static inline IData VL_DIV_III(int lbits, IData lhs, IData rhs) {
    return (rhs == 0) ? 0 : lhs / rhs;
}
static inline QData VL_DIV_QQQ(int lbits, QData lhs, QData rhs) {
    return (rhs == 0) ? 0 : lhs / rhs;
}
#define VL_DIV_WWW(lbits, owp, lwp, rwp) (_vl_moddiv_w(lbits, owp, lwp, rwp, 0))
static inline IData VL_MODDIV_III(int lbits, IData lhs, IData rhs) {
    return (rhs == 0) ? 0 : lhs % rhs;
}
static inline QData VL_MODDIV_QQQ(int lbits, QData lhs, QData rhs) {
    return (rhs == 0) ? 0 : lhs % rhs;
}
#define VL_MODDIV_WWW(lbits, owp, lwp, rwp) (_vl_moddiv_w(lbits, owp, lwp, rwp, 1))

static inline WDataOutP VL_ADD_W(int words, WDataOutP owp, WDataInP const lwp,
                                 WDataInP const rwp) VL_MT_SAFE {
    QData carry = 0;
    for (int i = 0; i < words; ++i) {
        carry = carry + static_cast<QData>(lwp[i]) + static_cast<QData>(rwp[i]);
        owp[i] = (carry & 0xffffffffULL);
        carry = (carry >> 32ULL) & 0xffffffffULL;
    }
    // Last output word is dirty
    return owp;
}

static inline WDataOutP VL_SUB_W(int words, WDataOutP owp, WDataInP const lwp,
                                 WDataInP const rwp) VL_MT_SAFE {
    QData carry = 0;
    for (int i = 0; i < words; ++i) {
        carry = (carry + static_cast<QData>(lwp[i])
                 + static_cast<QData>(static_cast<IData>(~rwp[i])));
        if (i == 0) ++carry;  // Negation of rwp
        owp[i] = (carry & 0xffffffffULL);
        carry = (carry >> 32ULL) & 0xffffffffULL;
    }
    // Last output word is dirty
    return owp;
}

static inline WDataOutP VL_MUL_W(int words, WDataOutP owp, WDataInP const lwp,
                                 WDataInP const rwp) VL_MT_SAFE {
    for (int i = 0; i < words; ++i) owp[i] = 0;
    for (int lword = 0; lword < words; ++lword) {
        for (int rword = 0; rword < words; ++rword) {
            QData mul = static_cast<QData>(lwp[lword]) * static_cast<QData>(rwp[rword]);
            for (int qword = lword + rword; qword < words; ++qword) {
                mul += static_cast<QData>(owp[qword]);
                owp[qword] = (mul & 0xffffffffULL);
                mul = (mul >> 32ULL) & 0xffffffffULL;
            }
        }
    }
    // Last output word is dirty
    return owp;
}

static inline IData VL_MULS_III(int lbits, IData lhs, IData rhs) VL_PURE {
    const int32_t lhs_signed = VL_EXTENDS_II(32, lbits, lhs);
    const int32_t rhs_signed = VL_EXTENDS_II(32, lbits, rhs);
    return lhs_signed * rhs_signed;
}
static inline QData VL_MULS_QQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    const int64_t lhs_signed = VL_EXTENDS_QQ(64, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(64, lbits, rhs);
    return lhs_signed * rhs_signed;
}

static inline WDataOutP VL_MULS_WWW(int lbits, WDataOutP owp, WDataInP const lwp,
                                    WDataInP const rwp) VL_MT_SAFE {
    const int words = VL_WORDS_I(lbits);
    VL_DEBUG_IFDEF(assert(words <= VL_MULS_MAX_WORDS););
    // cppcheck-suppress variableScope
    WData lwstore[VL_MULS_MAX_WORDS];  // Fixed size, as MSVC++ doesn't allow [words] here
    // cppcheck-suppress variableScope
    WData rwstore[VL_MULS_MAX_WORDS];
    WDataInP lwusp = lwp;
    WDataInP rwusp = rwp;
    const EData lneg = VL_SIGN_E(lbits, lwp[words - 1]);
    if (lneg) {  // Negate lhs
        lwusp = lwstore;
        VL_NEGATE_W(words, lwstore, lwp);
        lwstore[words - 1] &= VL_MASK_E(lbits);  // Clean it
    }
    const EData rneg = VL_SIGN_E(lbits, rwp[words - 1]);
    if (rneg) {  // Negate rhs
        rwusp = rwstore;
        VL_NEGATE_W(words, rwstore, rwp);
        rwstore[words - 1] &= VL_MASK_E(lbits);  // Clean it
    }
    VL_MUL_W(words, owp, lwusp, rwusp);
    owp[words - 1] &= VL_MASK_E(
        lbits);  // Clean.  Note it's ok for the multiply to overflow into the sign bit
    if ((lneg ^ rneg) & 1) {  // Negate output (not using NEGATE, as owp==lwp)
        QData carry = 0;
        for (int i = 0; i < words; ++i) {
            carry = carry + static_cast<QData>(static_cast<IData>(~owp[i]));
            if (i == 0) ++carry;  // Negation of temp2
            owp[i] = (carry & 0xffffffffULL);
            carry = (carry >> 32ULL) & 0xffffffffULL;
        }
        // Not needed: owp[words-1] |= 1<<VL_BITBIT_E(lbits-1);  // Set sign bit
    }
    // Last output word is dirty
    return owp;
}

static inline IData VL_DIVS_III(int lbits, IData lhs, IData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs == 0)) return 0;
    // -MAX / -1 cannot be represented in twos complement, and will cause SIGFPE
    if (VL_UNLIKELY(lhs == 0x80000000 && rhs == 0xffffffff)) return 0;
    const int32_t lhs_signed = VL_EXTENDS_II(VL_IDATASIZE, lbits, lhs);
    const int32_t rhs_signed = VL_EXTENDS_II(VL_IDATASIZE, lbits, rhs);
    return lhs_signed / rhs_signed;
}
static inline QData VL_DIVS_QQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs == 0)) return 0;
    // -MAX / -1 cannot be represented in twos complement, and will cause SIGFPE
    if (VL_UNLIKELY(lhs == 0x8000000000000000ULL && rhs == 0xffffffffffffffffULL)) return 0;
    const int64_t lhs_signed = VL_EXTENDS_QQ(VL_QUADSIZE, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(VL_QUADSIZE, lbits, rhs);
    return lhs_signed / rhs_signed;
}
static inline IData VL_MODDIVS_III(int lbits, IData lhs, IData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs == 0)) return 0;
    if (VL_UNLIKELY(lhs == 0x80000000 && rhs == 0xffffffff)) return 0;
    const int32_t lhs_signed = VL_EXTENDS_II(VL_IDATASIZE, lbits, lhs);
    const int32_t rhs_signed = VL_EXTENDS_II(VL_IDATASIZE, lbits, rhs);
    return lhs_signed % rhs_signed;
}
static inline QData VL_MODDIVS_QQQ(int lbits, QData lhs, QData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs == 0)) return 0;
    if (VL_UNLIKELY(lhs == 0x8000000000000000ULL && rhs == 0xffffffffffffffffULL)) return 0;
    const int64_t lhs_signed = VL_EXTENDS_QQ(VL_QUADSIZE, lbits, lhs);
    const int64_t rhs_signed = VL_EXTENDS_QQ(VL_QUADSIZE, lbits, rhs);
    return lhs_signed % rhs_signed;
}

static inline WDataOutP VL_DIVS_WWW(int lbits, WDataOutP owp, WDataInP const lwp,
                                    WDataInP const rwp) VL_MT_SAFE {
    const int lwords = VL_WORDS_I(lbits);
    const EData lsign = VL_SIGN_E(lbits, lwp[lwords - 1]);
    const EData rsign = VL_SIGN_E(lbits, rwp[lwords - 1]);
    VL_DEBUG_IFDEF(assert(lwords <= VL_MULS_MAX_WORDS););
    // cppcheck-suppress variableScope
    WData lwstore[VL_MULS_MAX_WORDS];  // Fixed size, as MSVC++ doesn't allow [words] here
    // cppcheck-suppress variableScope
    WData rwstore[VL_MULS_MAX_WORDS];
    WDataInP ltup = lwp;
    WDataInP rtup = rwp;
    if (lsign) ltup = _vl_clean_inplace_w(lbits, VL_NEGATE_W(lwords, lwstore, lwp));
    if (rsign) rtup = _vl_clean_inplace_w(lbits, VL_NEGATE_W(lwords, rwstore, rwp));
    if ((lsign && !rsign) || (!lsign && rsign)) {
        WData qNoSign[VL_MULS_MAX_WORDS];
        VL_DIV_WWW(lbits, qNoSign, ltup, rtup);
        _vl_clean_inplace_w(lbits, VL_NEGATE_W(lwords, owp, qNoSign));
        return owp;
    } else {
        return VL_DIV_WWW(lbits, owp, ltup, rtup);
    }
}
static inline WDataOutP VL_MODDIVS_WWW(int lbits, WDataOutP owp, WDataInP const lwp,
                                       WDataInP const rwp) VL_MT_SAFE {
    const int lwords = VL_WORDS_I(lbits);
    const EData lsign = VL_SIGN_E(lbits, lwp[lwords - 1]);
    const EData rsign = VL_SIGN_E(lbits, rwp[lwords - 1]);
    VL_DEBUG_IFDEF(assert(lwords <= VL_MULS_MAX_WORDS););
    // cppcheck-suppress variableScope
    WData lwstore[VL_MULS_MAX_WORDS];  // Fixed size, as MSVC++ doesn't allow [words] here
    // cppcheck-suppress variableScope
    WData rwstore[VL_MULS_MAX_WORDS];
    WDataInP ltup = lwp;
    WDataInP rtup = rwp;
    if (lsign) ltup = _vl_clean_inplace_w(lbits, VL_NEGATE_W(lwords, lwstore, lwp));
    if (rsign) rtup = _vl_clean_inplace_w(lbits, VL_NEGATE_W(lwords, rwstore, rwp));
    if (lsign) {  // Only dividend sign matters for modulus
        WData qNoSign[VL_MULS_MAX_WORDS];
        VL_MODDIV_WWW(lbits, qNoSign, ltup, rtup);
        _vl_clean_inplace_w(lbits, VL_NEGATE_W(lwords, owp, qNoSign));
        return owp;
    } else {
        return VL_MODDIV_WWW(lbits, owp, ltup, rtup);
    }
}

#define VL_POW_IIQ(obits, lbits, rbits, lhs, rhs) VL_POW_QQQ(obits, lbits, rbits, lhs, rhs)
#define VL_POW_IIW(obits, lbits, rbits, lhs, rwp) VL_POW_QQW(obits, lbits, rbits, lhs, rwp)
#define VL_POW_QQI(obits, lbits, rbits, lhs, rhs) VL_POW_QQQ(obits, lbits, rbits, lhs, rhs)
#define VL_POW_WWI(obits, lbits, rbits, owp, lwp, rhs) \
    VL_POW_WWQ(obits, lbits, rbits, owp, lwp, rhs)

static inline IData VL_POW_III(int, int, int rbits, IData lhs, IData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs == 0)) return 1;
    if (VL_UNLIKELY(lhs == 0)) return 0;
    IData power = lhs;
    IData out = 1;
    for (int i = 0; i < rbits; ++i) {
        if (i > 0) power = power * power;
        if (rhs & (1ULL << i)) out *= power;
    }
    return out;
}
static inline QData VL_POW_QQQ(int, int, int rbits, QData lhs, QData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs == 0)) return 1;
    if (VL_UNLIKELY(lhs == 0)) return 0;
    QData power = lhs;
    QData out = 1ULL;
    for (int i = 0; i < rbits; ++i) {
        if (i > 0) power = power * power;
        if (rhs & (1ULL << i)) out *= power;
    }
    return out;
}
WDataOutP VL_POW_WWW(int obits, int, int rbits, WDataOutP owp, WDataInP const lwp,
                     WDataInP const rwp) VL_MT_SAFE;
WDataOutP VL_POW_WWQ(int obits, int, int rbits, WDataOutP owp, WDataInP const lwp,
                     QData rhs) VL_MT_SAFE;
QData VL_POW_QQW(int obits, int, int rbits, QData lhs, WDataInP const rwp) VL_MT_SAFE;

#define VL_POWSS_IIQ(obits, lbits, rbits, lhs, rhs, lsign, rsign) \
    VL_POWSS_QQQ(obits, lbits, rbits, lhs, rhs, lsign, rsign)
#define VL_POWSS_IIQ(obits, lbits, rbits, lhs, rhs, lsign, rsign) \
    VL_POWSS_QQQ(obits, lbits, rbits, lhs, rhs, lsign, rsign)
#define VL_POWSS_IIW(obits, lbits, rbits, lhs, rwp, lsign, rsign) \
    VL_POWSS_QQW(obits, lbits, rbits, lhs, rwp, lsign, rsign)
#define VL_POWSS_QQI(obits, lbits, rbits, lhs, rhs, lsign, rsign) \
    VL_POWSS_QQQ(obits, lbits, rbits, lhs, rhs, lsign, rsign)
#define VL_POWSS_WWI(obits, lbits, rbits, owp, lwp, rhs, lsign, rsign) \
    VL_POWSS_WWQ(obits, lbits, rbits, owp, lwp, rhs, lsign, rsign)

static inline IData VL_POWSS_III(int obits, int, int rbits, IData lhs, IData rhs, bool lsign,
                                 bool rsign) VL_MT_SAFE {
    if (VL_UNLIKELY(rhs == 0)) return 1;
    if (rsign && VL_SIGN_I(rbits, rhs)) {
        if (lhs == 0) {
            return 0;  // "X"
        } else if (lhs == 1) {
            return 1;
        } else if (lsign && lhs == VL_MASK_I(obits)) {  // -1
            if (rhs & 1) {
                return VL_MASK_I(obits);  // -1^odd=-1
            } else {
                return 1;  // -1^even=1
            }
        }
        return 0;
    }
    return VL_POW_III(obits, rbits, rbits, lhs, rhs);
}
static inline QData VL_POWSS_QQQ(int obits, int, int rbits, QData lhs, QData rhs, bool lsign,
                                 bool rsign) VL_MT_SAFE {
    if (VL_UNLIKELY(rhs == 0)) return 1;
    if (rsign && VL_SIGN_Q(rbits, rhs)) {
        if (lhs == 0) {
            return 0;  // "X"
        } else if (lhs == 1) {
            return 1;
        } else if (lsign && lhs == VL_MASK_Q(obits)) {  // -1
            if (rhs & 1) {
                return VL_MASK_Q(obits);  // -1^odd=-1
            } else {
                return 1;  // -1^even=1
            }
        }
        return 0;
    }
    return VL_POW_QQQ(obits, rbits, rbits, lhs, rhs);
}
WDataOutP VL_POWSS_WWW(int obits, int, int rbits, WDataOutP owp, WDataInP const lwp,
                       WDataInP const rwp, bool lsign, bool rsign) VL_MT_SAFE;
WDataOutP VL_POWSS_WWQ(int obits, int, int rbits, WDataOutP owp, WDataInP const lwp, QData rhs,
                       bool lsign, bool rsign) VL_MT_SAFE;
QData VL_POWSS_QQW(int obits, int, int rbits, QData lhs, WDataInP const rwp, bool lsign,
                   bool rsign) VL_MT_SAFE;

//===================================================================
// Concat/replication

// INTERNAL: Stuff LHS bit 0++ into OUTPUT at specified offset
// ld may be "dirty", output is clean
static inline void _vl_insert_II(CData& lhsr, IData ld, int hbit, int lbit, int rbits) VL_PURE {
    const IData cleanmask = VL_MASK_I(rbits);
    const IData insmask = (VL_MASK_I(hbit - lbit + 1)) << lbit;
    lhsr = (lhsr & ~insmask) | ((ld << lbit) & (insmask & cleanmask));
}
static inline void _vl_insert_II(SData& lhsr, IData ld, int hbit, int lbit, int rbits) VL_PURE {
    const IData cleanmask = VL_MASK_I(rbits);
    const IData insmask = (VL_MASK_I(hbit - lbit + 1)) << lbit;
    lhsr = (lhsr & ~insmask) | ((ld << lbit) & (insmask & cleanmask));
}
static inline void _vl_insert_II(IData& lhsr, IData ld, int hbit, int lbit, int rbits) VL_PURE {
    const IData cleanmask = VL_MASK_I(rbits);
    const IData insmask = (VL_MASK_I(hbit - lbit + 1)) << lbit;
    lhsr = (lhsr & ~insmask) | ((ld << lbit) & (insmask & cleanmask));
}
static inline void _vl_insert_QQ(QData& lhsr, QData ld, int hbit, int lbit, int rbits) VL_PURE {
    const QData cleanmask = VL_MASK_Q(rbits);
    const QData insmask = (VL_MASK_Q(hbit - lbit + 1)) << lbit;
    lhsr = (lhsr & ~insmask) | ((ld << lbit) & (insmask & cleanmask));
}
static inline void _vl_insert_WI(WDataOutP iowp, IData ld, int hbit, int lbit,
                                 int rbits = 0) VL_MT_SAFE {
    // Insert value ld into iowp at bit slice [hbit:lbit]. iowp is rbits wide.
    const int hoffset = VL_BITBIT_E(hbit);
    const int loffset = VL_BITBIT_E(lbit);
    const int roffset = VL_BITBIT_E(rbits);
    const int hword = VL_BITWORD_E(hbit);
    const int lword = VL_BITWORD_E(lbit);
    const int rword = VL_BITWORD_E(rbits);
    const EData cleanmask = hword == rword ? VL_MASK_E(roffset) : VL_MASK_E(0);

    if (hoffset == VL_SIZEBITS_E && loffset == 0) {
        // Fast and common case, word based insertion
        iowp[lword] = ld & cleanmask;
    } else {
        const EData lde = static_cast<EData>(ld);
        if (hword == lword) {  // know < EData bits because above checks it
            // Assignment is contained within one word of destination
            const EData insmask = (VL_MASK_E(hoffset - loffset + 1)) << loffset;
            iowp[lword] = (iowp[lword] & ~insmask) | ((lde << loffset) & (insmask & cleanmask));
        } else {
            // Assignment crosses a word boundary in destination
            const EData hinsmask = (VL_MASK_E(hoffset - 0 + 1)) << 0;
            const EData linsmask = (VL_MASK_E((VL_EDATASIZE - 1) - loffset + 1)) << loffset;
            const int nbitsonright = VL_EDATASIZE - loffset;  // bits that end up in lword
            iowp[lword] = (iowp[lword] & ~linsmask) | ((lde << loffset) & linsmask);
            // Prevent unsafe write where lword was final writable location and hword is
            // out-of-bounds.
            if (VL_LIKELY(!(hword == rword && roffset == 0))) {
                iowp[hword]
                    = (iowp[hword] & ~hinsmask) | ((lde >> nbitsonright) & (hinsmask & cleanmask));
            }
        }
    }
}

// Copy bits from lwp[hbit:lbit] to low bits of lhsr. rbits is real width of lshr
static inline void _vl_insert_IW(IData& lhsr, WDataInP const lwp, int hbit, int lbit,
                                 int rbits = 0) VL_MT_SAFE {
    const int hoffset = VL_BITBIT_E(hbit);
    const int loffset = VL_BITBIT_E(lbit);
    const int hword = VL_BITWORD_E(hbit);
    const int lword = VL_BITWORD_E(lbit);
    const IData cleanmask = VL_MASK_I(rbits);
    if (hword == lword) {
        const IData insmask = (VL_MASK_I(hoffset - loffset + 1));
        lhsr = (lhsr & ~insmask) | ((lwp[lword] >> loffset) & (insmask & cleanmask));
    } else {
        const int nbitsonright = VL_IDATASIZE - loffset;  // bits that filled by lword
        const IData hinsmask = (VL_MASK_E(hoffset - 0 + 1)) << nbitsonright;
        const IData linsmask = VL_MASK_E(VL_EDATASIZE - loffset);
        lhsr = (lhsr & ~linsmask) | ((lwp[lword] >> loffset) & (linsmask & cleanmask));
        lhsr = (lhsr & ~hinsmask) | ((lwp[hword] << nbitsonright) & (hinsmask & cleanmask));
    }
}

// INTERNAL: Stuff large LHS bit 0++ into OUTPUT at specified offset
// lwp may be "dirty"
static inline void _vl_insert_WW(WDataOutP iowp, WDataInP const lwp, int hbit, int lbit,
                                 int rbits = 0) VL_MT_SAFE {
    const int hoffset = VL_BITBIT_E(hbit);
    const int loffset = VL_BITBIT_E(lbit);
    const int roffset = VL_BITBIT_E(rbits);
    const int lword = VL_BITWORD_E(lbit);
    const int hword = VL_BITWORD_E(hbit);
    const int rword = VL_BITWORD_E(rbits);
    const int words = VL_WORDS_I(hbit - lbit + 1);
    // Cleaning mask, only applied to top word of the assignment.  Is a no-op
    // if we don't assign to the top word of the destination.
    const EData cleanmask = hword == rword ? VL_MASK_E(roffset) : VL_MASK_E(0);

    if (hoffset == VL_SIZEBITS_E && loffset == 0) {
        // Fast and common case, word based insertion
        for (int i = 0; i < (words - 1); ++i) iowp[lword + i] = lwp[i];
        iowp[hword] = lwp[words - 1] & cleanmask;
    } else if (loffset == 0) {
        // Non-32bit, but nicely aligned, so stuff all but the last word
        for (int i = 0; i < (words - 1); ++i) iowp[lword + i] = lwp[i];
        // Know it's not a full word as above fast case handled it
        const EData hinsmask = (VL_MASK_E(hoffset - 0 + 1));
        iowp[hword] = (iowp[hword] & ~hinsmask) | (lwp[words - 1] & (hinsmask & cleanmask));
    } else {
        const EData hinsmask = (VL_MASK_E(hoffset - 0 + 1)) << 0;
        const EData linsmask = (VL_MASK_E((VL_EDATASIZE - 1) - loffset + 1)) << loffset;
        const int nbitsonright
            = VL_EDATASIZE - loffset;  // bits that end up in lword (know loffset!=0)
        // Middle words
        for (int i = 0; i < words; ++i) {
            {  // Lower word
                const int oword = lword + i;
                const EData d = lwp[i] << loffset;
                const EData od = (iowp[oword] & ~linsmask) | (d & linsmask);
                if (oword == hword) {
                    iowp[oword] = (iowp[oword] & ~hinsmask) | (od & (hinsmask & cleanmask));
                } else {
                    iowp[oword] = od;
                }
            }
            {  // Upper word
                const int oword = lword + i + 1;
                if (oword <= hword) {
                    const EData d = lwp[i] >> nbitsonright;
                    const EData od = (d & ~linsmask) | (iowp[oword] & linsmask);
                    if (oword == hword) {
                        iowp[oword] = (iowp[oword] & ~hinsmask) | (od & (hinsmask & cleanmask));
                    } else {
                        iowp[oword] = od;
                    }
                }
            }
        }
    }
}

static inline void _vl_insert_WQ(WDataOutP iowp, QData ld, int hbit, int lbit,
                                 int rbits = 0) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> lwp;
    VL_SET_WQ(lwp, ld);
    _vl_insert_WW(iowp, lwp, hbit, lbit, rbits);
}

// EMIT_RULE: VL_REPLICATE:  oclean=clean>width32, dirty<=width32; lclean=clean; rclean==clean;
// RHS MUST BE CLEAN CONSTANT.
#define VL_REPLICATE_IOI(lbits, ld, rep) (-(ld))  // Iff lbits==1
#define VL_REPLICATE_QOI(lbits, ld, rep) (-(static_cast<QData>(ld)))  // Iff lbits==1

static inline IData VL_REPLICATE_III(int lbits, IData ld, IData rep) VL_PURE {
    IData returndata = ld;
    for (unsigned i = 1; i < rep; ++i) {
        returndata = returndata << lbits;
        returndata |= ld;
    }
    return returndata;
}
static inline QData VL_REPLICATE_QII(int lbits, IData ld, IData rep) VL_PURE {
    QData returndata = ld;
    for (unsigned i = 1; i < rep; ++i) {
        returndata = returndata << lbits;
        returndata |= static_cast<QData>(ld);
    }
    return returndata;
}
static inline WDataOutP VL_REPLICATE_WII(int lbits, WDataOutP owp, IData ld,
                                         IData rep) VL_MT_SAFE {
    owp[0] = ld;
    // Zeroing all words isn't strictly needed but allows compiler to know
    // it does not need to preserve data in word(s) not being written
    for (unsigned i = 1; i < VL_WORDS_I(static_cast<unsigned>(lbits) * rep); ++i) owp[i] = 0;
    for (unsigned i = 1; i < rep; ++i) {
        _vl_insert_WI(owp, ld, i * lbits + lbits - 1, i * lbits);
    }
    return owp;
}
static inline WDataOutP VL_REPLICATE_WQI(int lbits, WDataOutP owp, QData ld,
                                         IData rep) VL_MT_SAFE {
    VL_SET_WQ(owp, ld);
    // Zeroing all words isn't strictly needed but allows compiler to know
    // it does not need to preserve data in word(s) not being written
    for (unsigned i = 2; i < VL_WORDS_I(static_cast<unsigned>(lbits) * rep); ++i) owp[i] = 0;
    for (unsigned i = 1; i < rep; ++i) {
        _vl_insert_WQ(owp, ld, i * lbits + lbits - 1, i * lbits);
    }
    return owp;
}
static inline WDataOutP VL_REPLICATE_WWI(int lbits, WDataOutP owp, WDataInP const lwp,
                                         IData rep) VL_MT_SAFE {
    for (unsigned i = 0; i < VL_WORDS_I(static_cast<unsigned>(lbits)); ++i) owp[i] = lwp[i];
    // Zeroing all words isn't strictly needed but allows compiler to know
    // it does not need to preserve data in word(s) not being written
    for (unsigned i = VL_WORDS_I(static_cast<unsigned>(lbits));
         i < VL_WORDS_I(static_cast<unsigned>(lbits * rep)); ++i)
        owp[i] = 0;
    for (unsigned i = 1; i < rep; ++i) {
        _vl_insert_WW(owp, lwp, i * lbits + lbits - 1, i * lbits);
    }
    return owp;
}

// Left stream operator. Output will always be clean. LHS and RHS must be clean.
// Special "fast" versions for slice sizes that are a power of 2. These use
// shifts and masks to execute faster than the slower for-loop approach where a
// subset of bits is copied in during each iteration.
static inline IData VL_STREAML_FAST_III(int lbits, IData ld, IData rd_log2) VL_PURE {
    // Pre-shift bits in most-significant slice:
    //
    // If lbits is not a multiple of the slice size (i.e., lbits % rd != 0),
    // then we end up with a "gap" in our reversed result. For example, if we
    // have a 5-bit Verilog signal (lbits=5) in an 8-bit C data type:
    //
    //   ld = ---43210
    //
    // (where numbers are the Verilog signal bit numbers and '-' is an unused bit).
    // Executing the switch statement below with a slice size of two (rd=2,
    // rd_log2=1) produces:
    //
    //   ret = 1032-400
    //
    // Pre-shifting the bits in the most-significant slice allows us to avoid
    // this gap in the shuffled data:
    //
    //   ld_adjusted = --4-3210
    //   ret = 10324---
    IData ret = ld;
    if (rd_log2) {
        const uint32_t lbitsFloor = lbits & ~VL_MASK_I(rd_log2);  // max multiple of rd <= lbits
        const uint32_t lbitsRem = lbits - lbitsFloor;  // number of bits in most-sig slice (MSS)
        const IData msbMask = lbitsFloor == 32 ? 0UL : VL_MASK_I(lbitsRem) << lbitsFloor;
        ret = (ret & ~msbMask) | ((ret & msbMask) << ((VL_UL(1) << rd_log2) - lbitsRem));
    }
    switch (rd_log2) {
    case 0: ret = ((ret >> 1) & VL_UL(0x55555555)) | ((ret & VL_UL(0x55555555)) << 1);  // FALLTHRU
    case 1: ret = ((ret >> 2) & VL_UL(0x33333333)) | ((ret & VL_UL(0x33333333)) << 2);  // FALLTHRU
    case 2: ret = ((ret >> 4) & VL_UL(0x0f0f0f0f)) | ((ret & VL_UL(0x0f0f0f0f)) << 4);  // FALLTHRU
    case 3: ret = ((ret >> 8) & VL_UL(0x00ff00ff)) | ((ret & VL_UL(0x00ff00ff)) << 8);  // FALLTHRU
    case 4: ret = ((ret >> 16) | (ret << 16));  // FALLTHRU
    default:;
    }
    return ret >> (VL_IDATASIZE - lbits);
}

static inline QData VL_STREAML_FAST_QQI(int lbits, QData ld, IData rd_log2) VL_PURE {
    // Pre-shift bits in most-significant slice (see comment in VL_STREAML_FAST_III)
    QData ret = ld;
    if (rd_log2) {
        const uint32_t lbitsFloor = lbits & ~VL_MASK_I(rd_log2);
        const uint32_t lbitsRem = lbits - lbitsFloor;
        const QData msbMask = lbitsFloor == 64 ? 0ULL : VL_MASK_Q(lbitsRem) << lbitsFloor;
        ret = (ret & ~msbMask) | ((ret & msbMask) << ((1ULL << rd_log2) - lbitsRem));
    }
    switch (rd_log2) {
    case 0:
        ret = (((ret >> 1) & 0x5555555555555555ULL)
               | ((ret & 0x5555555555555555ULL) << 1));  // FALLTHRU
    case 1:
        ret = (((ret >> 2) & 0x3333333333333333ULL)
               | ((ret & 0x3333333333333333ULL) << 2));  // FALLTHRU
    case 2:
        ret = (((ret >> 4) & 0x0f0f0f0f0f0f0f0fULL)
               | ((ret & 0x0f0f0f0f0f0f0f0fULL) << 4));  // FALLTHRU
    case 3:
        ret = (((ret >> 8) & 0x00ff00ff00ff00ffULL)
               | ((ret & 0x00ff00ff00ff00ffULL) << 8));  // FALLTHRU
    case 4:
        ret = (((ret >> 16) & 0x0000ffff0000ffffULL)
               | ((ret & 0x0000ffff0000ffffULL) << 16));  // FALLTHRU
    case 5: ret = ((ret >> 32) | (ret << 32));  // FALLTHRU
    default:;
    }
    return ret >> (VL_QUADSIZE - lbits);
}

// Regular "slow" streaming operators
static inline IData VL_STREAML_III(int lbits, IData ld, IData rd) VL_PURE {
    IData ret = 0;
    // Slice size should never exceed the lhs width
    const IData mask = VL_MASK_I(rd);
    for (int istart = 0; istart < lbits; istart += rd) {
        int ostart = lbits - rd - istart;
        ostart = ostart > 0 ? ostart : 0;
        ret |= ((ld >> istart) & mask) << ostart;
    }
    return ret;
}

static inline QData VL_STREAML_QQI(int lbits, QData ld, IData rd) VL_PURE {
    QData ret = 0;
    // Slice size should never exceed the lhs width
    const QData mask = VL_MASK_Q(rd);
    for (int istart = 0; istart < lbits; istart += rd) {
        int ostart = lbits - rd - istart;
        ostart = ostart > 0 ? ostart : 0;
        ret |= ((ld >> istart) & mask) << ostart;
    }
    return ret;
}

static inline WDataOutP VL_STREAML_WWI(int lbits, WDataOutP owp, WDataInP const lwp,
                                       IData rd) VL_MT_SAFE {
    VL_ZERO_W(lbits, owp);
    // Slice size should never exceed the lhs width
    const int ssize = (rd < static_cast<IData>(lbits)) ? rd : (static_cast<IData>(lbits));
    for (int istart = 0; istart < lbits; istart += rd) {
        int ostart = lbits - rd - istart;
        ostart = ostart > 0 ? ostart : 0;
        for (int sbit = 0; sbit < ssize && sbit < lbits - istart; ++sbit) {
            // Extract a single bit from lwp and shift it to the correct
            // location for owp.
            const EData bit = (VL_BITRSHIFT_W(lwp, (istart + sbit)) & 1)
                              << VL_BITBIT_E(ostart + sbit);
            owp[VL_BITWORD_E(ostart + sbit)] |= bit;
        }
    }
    return owp;
}

static inline IData VL_PACK_I_RI(int obits, int lbits, const VlQueue<CData>& q) {
    IData ret = 0;
    for (size_t i = 0; i < q.size(); ++i)
        ret |= static_cast<IData>(q.at(q.size() - 1 - i)) << (i * lbits);
    return ret;
}

static inline IData VL_PACK_I_RI(int obits, int lbits, const VlQueue<SData>& q) {
    IData ret = 0;
    for (size_t i = 0; i < q.size(); ++i)
        ret |= static_cast<IData>(q.at(q.size() - 1 - i)) << (i * lbits);
    return ret;
}

static inline IData VL_PACK_I_RI(int obits, int lbits, const VlQueue<IData>& q) {
    IData ret = 0;
    for (size_t i = 0; i < q.size(); ++i) ret |= q.at(q.size() - 1 - i) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline IData VL_PACK_I_UI(int obits, int lbits, const VlUnpacked<CData, N_Depth>& q) {
    IData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i)
        ret |= static_cast<IData>(q[N_Depth - 1 - i]) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline IData VL_PACK_I_UI(int obits, int lbits, const VlUnpacked<SData, N_Depth>& q) {
    IData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i)
        ret |= static_cast<IData>(q[N_Depth - 1 - i]) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline IData VL_PACK_I_UI(int obits, int lbits, const VlUnpacked<IData, N_Depth>& q) {
    IData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i) ret |= q[N_Depth - 1 - i] << (i * lbits);
    return ret;
}

static inline QData VL_PACK_Q_RI(int obits, int lbits, const VlQueue<CData>& q) {
    QData ret = 0;
    for (size_t i = 0; i < q.size(); ++i)
        ret |= static_cast<QData>(q.at(q.size() - 1 - i)) << (i * lbits);
    return ret;
}

static inline QData VL_PACK_Q_RI(int obits, int lbits, const VlQueue<SData>& q) {
    QData ret = 0;
    for (size_t i = 0; i < q.size(); ++i)
        ret |= static_cast<QData>(q.at(q.size() - 1 - i)) << (i * lbits);
    return ret;
}

static inline QData VL_PACK_Q_RI(int obits, int lbits, const VlQueue<IData>& q) {
    QData ret = 0;
    for (size_t i = 0; i < q.size(); ++i)
        ret |= static_cast<QData>(q.at(q.size() - 1 - i)) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline QData VL_PACK_Q_UI(int obits, int lbits, const VlUnpacked<CData, N_Depth>& q) {
    QData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i)
        ret |= static_cast<QData>(q[N_Depth - 1 - i]) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline QData VL_PACK_Q_UI(int obits, int lbits, const VlUnpacked<SData, N_Depth>& q) {
    QData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i)
        ret |= static_cast<QData>(q[N_Depth - 1 - i]) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline QData VL_PACK_Q_UI(int obits, int lbits, const VlUnpacked<IData, N_Depth>& q) {
    QData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i)
        ret |= static_cast<QData>(q[N_Depth - 1 - i]) << (i * lbits);
    return ret;
}

static inline QData VL_PACK_Q_RQ(int obits, int lbits, const VlQueue<QData>& q) {
    QData ret = 0;
    for (size_t i = 0; i < q.size(); ++i) ret |= q.at(q.size() - 1 - i) << (i * lbits);
    return ret;
}

template <std::size_t N_Depth>
static inline QData VL_PACK_Q_UQ(int obits, int lbits, const VlUnpacked<QData, N_Depth>& q) {
    QData ret = 0;
    for (size_t i = 0; i < N_Depth; ++i) ret |= q[N_Depth - 1 - i] << (i * lbits);
    return ret;
}

static inline WDataOutP VL_PACK_W_RI(int obits, int lbits, WDataOutP owp,
                                     const VlQueue<CData>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    if (VL_UNLIKELY(obits < q.size() * lbits)) return owp;  // Though is illegal for q to be larger
    const int offset = obits - q.size() * lbits;
    for (size_t i = 0; i < q.size(); ++i)
        _vl_insert_WI(owp, q.at(q.size() - i - 1), i * lbits + lbits - 1 + offset,
                      i * lbits + offset);
    return owp;
}

static inline WDataOutP VL_PACK_W_RI(int obits, int lbits, WDataOutP owp,
                                     const VlQueue<SData>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    if (VL_UNLIKELY(obits < q.size() * lbits)) return owp;  // Though is illegal for q to be larger
    const int offset = obits - q.size() * lbits;
    for (size_t i = 0; i < q.size(); ++i)
        _vl_insert_WI(owp, q.at(q.size() - i - 1), i * lbits + lbits - 1 + offset,
                      i * lbits + offset);
    return owp;
}

static inline WDataOutP VL_PACK_W_RI(int obits, int lbits, WDataOutP owp,
                                     const VlQueue<IData>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    if (VL_UNLIKELY(obits < q.size() * lbits)) return owp;  // Though is illegal for q to be larger
    const int offset = obits - q.size() * lbits;
    for (size_t i = 0; i < q.size(); ++i)
        _vl_insert_WI(owp, q.at(q.size() - 1 - i), i * lbits + lbits - 1 + offset,
                      i * lbits + offset);
    return owp;
}

template <std::size_t N_Depth>
static inline WDataOutP VL_PACK_W_UI(int obits, int lbits, WDataOutP owp,
                                     const VlUnpacked<CData, N_Depth>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    for (size_t i = 0; i < N_Depth; ++i)
        _vl_insert_WI(owp, q[N_Depth - 1 - i], i * lbits + lbits - 1, i * lbits);
    return owp;
}

template <std::size_t N_Depth>
static inline WDataOutP VL_PACK_W_UI(int obits, int lbits, WDataOutP owp,
                                     const VlUnpacked<SData, N_Depth>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    for (size_t i = 0; i < N_Depth; ++i)
        _vl_insert_WI(owp, q[N_Depth - 1 - i], i * lbits + lbits - 1, i * lbits);
    return owp;
}

template <std::size_t N_Depth>
static inline WDataOutP VL_PACK_W_UI(int obits, int lbits, WDataOutP owp,
                                     const VlUnpacked<IData, N_Depth>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    for (size_t i = 0; i < N_Depth; ++i)
        _vl_insert_WI(owp, q[N_Depth - 1 - i], i * lbits + lbits - 1, i * lbits);
    return owp;
}

static inline WDataOutP VL_PACK_W_RQ(int obits, int lbits, WDataOutP owp,
                                     const VlQueue<QData>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    if (VL_UNLIKELY(obits < q.size() * lbits)) return owp;  // Though is illegal for q to be larger
    const int offset = obits - q.size() * lbits;
    for (size_t i = 0; i < q.size(); ++i)
        _vl_insert_WQ(owp, q.at(q.size() - 1 - i), i * lbits + lbits - 1 + offset,
                      i * lbits + offset);
    return owp;
}

template <std::size_t N_Depth>
static inline WDataOutP VL_PACK_W_UQ(int obits, int lbits, WDataOutP owp,
                                     const VlUnpacked<QData, N_Depth>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    for (size_t i = 0; i < N_Depth; ++i)
        _vl_insert_WQ(owp, q[N_Depth - 1 - i], i * lbits + lbits - 1, i * lbits);
    return owp;
}

template <std::size_t N_Words>
static inline WDataOutP VL_PACK_W_RW(int obits, int lbits, WDataOutP owp,
                                     const VlQueue<VlWide<N_Words>>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    if (VL_UNLIKELY(obits < q.size() * lbits)) return owp;  // Though is illegal for q to be larger
    const int offset = obits - q.size() * lbits;
    for (size_t i = 0; i < q.size(); ++i)
        _vl_insert_WW(owp, q.at(q.size() - 1 - i), i * lbits + lbits - 1 + offset,
                      i * lbits + offset);
    return owp;
}

template <std::size_t N_Depth, std::size_t N_Words>
static inline WDataOutP VL_PACK_W_UW(int obits, int lbits, WDataOutP owp,
                                     const VlUnpacked<VlWide<N_Words>, N_Depth>& q) {
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    if (VL_UNLIKELY(obits < q.size() * lbits)) return owp;  // Though is illegal for q to be larger
    const int offset = obits - q.size() * lbits;
    for (size_t i = 0; i < N_Depth; ++i)
        _vl_insert_WW(owp, q[N_Depth - 1 - i], i * lbits + lbits - 1 + offset, i * lbits + offset);
    return owp;
}

// Because concats are common and wide, it's valuable to always have a clean output.
// Thus we specify inputs must be clean, so we don't need to clean the output.
// Note the bit shifts are always constants, so the adds in these constify out.
// Casts required, as args may be 8 bit entities, and need to shift to appropriate output size
#define VL_CONCAT_III(obits, lbits, rbits, ld, rd) \
    (static_cast<IData>(ld) << (rbits) | static_cast<IData>(rd))
#define VL_CONCAT_QII(obits, lbits, rbits, ld, rd) \
    (static_cast<QData>(ld) << (rbits) | static_cast<QData>(rd))
#define VL_CONCAT_QIQ(obits, lbits, rbits, ld, rd) \
    (static_cast<QData>(ld) << (rbits) | static_cast<QData>(rd))
#define VL_CONCAT_QQI(obits, lbits, rbits, ld, rd) \
    (static_cast<QData>(ld) << (rbits) | static_cast<QData>(rd))
#define VL_CONCAT_QQQ(obits, lbits, rbits, ld, rd) \
    (static_cast<QData>(ld) << (rbits) | static_cast<QData>(rd))

static inline WDataOutP VL_CONCAT_WII(int obits, int lbits, int rbits, WDataOutP owp, IData ld,
                                      IData rd) VL_MT_SAFE {
    owp[0] = rd;
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    _vl_insert_WI(owp, ld, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WWI(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, IData rd) VL_MT_SAFE {
    owp[0] = rd;
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    _vl_insert_WW(owp, lwp, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WIW(int obits, int lbits, int rbits, WDataOutP owp, IData ld,
                                      WDataInP const rwp) VL_MT_SAFE {
    const int rwords = VL_WORDS_I(rbits);
    VL_MEMCPY_W(owp, rwp, rwords);
    VL_MEMSET_ZERO_W(owp + rwords, VL_WORDS_I(obits) - rwords);
    _vl_insert_WI(owp, ld, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WIQ(int obits, int lbits, int rbits, WDataOutP owp, IData ld,
                                      QData rd) VL_MT_SAFE {
    VL_SET_WQ(owp, rd);
    VL_MEMSET_ZERO_W(owp + VL_WQ_WORDS_E, VL_WORDS_I(obits) - VL_WQ_WORDS_E);
    _vl_insert_WI(owp, ld, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WQI(int obits, int lbits, int rbits, WDataOutP owp, QData ld,
                                      IData rd) VL_MT_SAFE {
    owp[0] = rd;
    VL_MEMSET_ZERO_W(owp + 1, VL_WORDS_I(obits) - 1);
    _vl_insert_WQ(owp, ld, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WQQ(int obits, int lbits, int rbits, WDataOutP owp, QData ld,
                                      QData rd) VL_MT_SAFE {
    VL_SET_WQ(owp, rd);
    VL_MEMSET_ZERO_W(owp + VL_WQ_WORDS_E, VL_WORDS_I(obits) - VL_WQ_WORDS_E);
    _vl_insert_WQ(owp, ld, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WWQ(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, QData rd) VL_MT_SAFE {
    VL_SET_WQ(owp, rd);
    VL_MEMSET_ZERO_W(owp + VL_WQ_WORDS_E, VL_WORDS_I(obits) - VL_WQ_WORDS_E);
    _vl_insert_WW(owp, lwp, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WQW(int obits, int lbits, int rbits, WDataOutP owp, QData ld,
                                      WDataInP const rwp) VL_MT_SAFE {
    const int rwords = VL_WORDS_I(rbits);
    VL_MEMCPY_W(owp, rwp, rwords);
    VL_MEMSET_ZERO_W(owp + rwords, VL_WORDS_I(obits) - rwords);
    _vl_insert_WQ(owp, ld, rbits + lbits - 1, rbits);
    return owp;
}
static inline WDataOutP VL_CONCAT_WWW(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, WDataInP const rwp) VL_MT_SAFE {
    const int rwords = VL_WORDS_I(rbits);
    VL_MEMCPY_W(owp, rwp, rwords);
    VL_MEMSET_ZERO_W(owp + rwords, VL_WORDS_I(obits) - rwords);
    _vl_insert_WW(owp, lwp, rbits + lbits - 1, rbits);
    return owp;
}

//===================================================================
// Shifts

// Static shift, used by internal functions
// The output is the same as the input - it overlaps!
static inline void _vl_shiftl_inplace_w(int obits, WDataOutP iowp,
                                        IData rd /*1 or 4*/) VL_MT_SAFE {
    const int words = VL_WORDS_I(obits);
    const EData linsmask = VL_MASK_E(rd);
    for (int i = words - 1; i >= 1; --i) {
        iowp[i]
            = ((iowp[i] << rd) & ~linsmask) | ((iowp[i - 1] >> (VL_EDATASIZE - rd)) & linsmask);
    }
    iowp[0] = ((iowp[0] << rd) & ~linsmask);
    iowp[VL_WORDS_I(obits) - 1] &= VL_MASK_E(obits);
}

// EMIT_RULE: VL_SHIFTL:  oclean=lclean; rclean==clean;
// Important: Unlike most other funcs, the shift might well be a computed
// expression.  Thus consider this when optimizing.  (And perhaps have 2 funcs?)
// If RHS (rd/rwp) is larger than the output, zeros (or all ones for >>>) must be returned
// (This corresponds to AstShift*Ovr Ast nodes)
static inline IData VL_SHIFTL_III(int obits, int, int, IData lhs, IData rhs) VL_MT_SAFE {
    if (VL_UNLIKELY(rhs >= VL_IDATASIZE)) return 0;
    return lhs << rhs;  // Small is common so not clean return
}
static inline IData VL_SHIFTL_IIQ(int obits, int, int, IData lhs, QData rhs) VL_MT_SAFE {
    if (VL_UNLIKELY(rhs >= VL_IDATASIZE)) return 0;
    return VL_CLEAN_II(obits, obits, lhs << rhs);
}
static inline QData VL_SHIFTL_QQI(int obits, int, int, QData lhs, IData rhs) VL_MT_SAFE {
    if (VL_UNLIKELY(rhs >= VL_QUADSIZE)) return 0;
    return lhs << rhs;  // Small is common so not clean return
}
static inline QData VL_SHIFTL_QQQ(int obits, int, int, QData lhs, QData rhs) VL_MT_SAFE {
    if (VL_UNLIKELY(rhs >= VL_QUADSIZE)) return 0;
    return VL_CLEAN_QQ(obits, obits, lhs << rhs);
}
static inline WDataOutP VL_SHIFTL_WWI(int obits, int, int, WDataOutP owp, WDataInP const lwp,
                                      IData rd) VL_MT_SAFE {
    const int word_shift = VL_BITWORD_E(rd);
    const int bit_shift = VL_BITBIT_E(rd);
    if (rd >= static_cast<IData>(obits)) {  // rd may be huge with MSB set
        for (int i = 0; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
    } else if (bit_shift == 0) {  // Aligned word shift (<<0,<<32,<<64 etc)
        for (int i = 0; i < word_shift; ++i) owp[i] = 0;
        for (int i = word_shift; i < VL_WORDS_I(obits); ++i) owp[i] = lwp[i - word_shift];
    } else {
        for (int i = 0; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
        _vl_insert_WW(owp, lwp, obits - 1, rd);
    }
    return owp;
}
static inline WDataOutP VL_SHIFTL_WWW(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, WDataInP const rwp) VL_MT_SAFE {
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) {
        if (VL_UNLIKELY(rwp[i])) {  // Huge shift 1>>32 or more
            return VL_ZERO_W(obits, owp);
        }
    }
    return VL_SHIFTL_WWI(obits, lbits, 32, owp, lwp, rwp[0]);
}
static inline WDataOutP VL_SHIFTL_WWQ(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, QData rd) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> rwp;
    VL_SET_WQ(rwp, rd);
    return VL_SHIFTL_WWW(obits, lbits, rbits, owp, lwp, rwp);
}
static inline IData VL_SHIFTL_IIW(int obits, int, int rbits, IData lhs,
                                  WDataInP const rwp) VL_MT_SAFE {
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) {
        if (VL_UNLIKELY(rwp[i])) {  // Huge shift 1>>32 or more
            return 0;
        }
    }
    return VL_SHIFTL_III(obits, obits, 32, lhs, rwp[0]);
}
static inline QData VL_SHIFTL_QQW(int obits, int, int rbits, QData lhs,
                                  WDataInP const rwp) VL_MT_SAFE {
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) {
        if (VL_UNLIKELY(rwp[i])) {  // Huge shift 1>>32 or more
            return 0;
        }
    }
    // Above checks rwp[1]==0 so not needed in below shift
    return VL_SHIFTL_QQI(obits, obits, 32, lhs, rwp[0]);
}

// EMIT_RULE: VL_SHIFTR:  oclean=lclean; rclean==clean;
// Important: Unlike most other funcs, the shift might well be a computed
// expression.  Thus consider this when optimizing.  (And perhaps have 2 funcs?)
static inline IData VL_SHIFTR_III(int obits, int, int, IData lhs, IData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs >= VL_IDATASIZE)) return 0;
    return lhs >> rhs;
}
static inline IData VL_SHIFTR_IIQ(int obits, int, int, IData lhs, QData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs >= VL_IDATASIZE)) return 0;
    return lhs >> rhs;
}
static inline QData VL_SHIFTR_QQI(int obits, int, int, QData lhs, IData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs >= VL_QUADSIZE)) return 0;
    return lhs >> rhs;
}
static inline QData VL_SHIFTR_QQQ(int obits, int, int, QData lhs, QData rhs) VL_PURE {
    if (VL_UNLIKELY(rhs >= VL_QUADSIZE)) return 0;
    return lhs >> rhs;
}
static inline WDataOutP VL_SHIFTR_WWI(int obits, int, int, WDataOutP owp, WDataInP const lwp,
                                      IData rd) VL_MT_SAFE {
    const int word_shift = VL_BITWORD_E(rd);  // Maybe 0
    const int bit_shift = VL_BITBIT_E(rd);
    if (rd >= static_cast<IData>(obits)) {  // rd may be huge with MSB set
        for (int i = 0; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
    } else if (bit_shift == 0) {  // Aligned word shift (>>0,>>32,>>64 etc)
        const int copy_words = (VL_WORDS_I(obits) - word_shift);
        for (int i = 0; i < copy_words; ++i) owp[i] = lwp[i + word_shift];
        for (int i = copy_words; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
    } else {
        const int loffset = rd & VL_SIZEBITS_E;
        const int nbitsonright = VL_EDATASIZE - loffset;  // bits that end up in lword (know
                                                          // loffset!=0) Middle words
        const int words = VL_WORDS_I(obits - rd);
        for (int i = 0; i < words; ++i) {
            owp[i] = lwp[i + word_shift] >> loffset;
            const int upperword = i + word_shift + 1;
            if (upperword < VL_WORDS_I(obits)) owp[i] |= lwp[upperword] << nbitsonright;
        }
        for (int i = words; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
    }
    return owp;
}
static inline WDataOutP VL_SHIFTR_WWW(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, WDataInP const rwp) VL_MT_SAFE {
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) {
        if (VL_UNLIKELY(rwp[i])) {  // Huge shift 1>>32 or more
            return VL_ZERO_W(obits, owp);
        }
    }
    return VL_SHIFTR_WWI(obits, lbits, 32, owp, lwp, rwp[0]);
}
static inline WDataOutP VL_SHIFTR_WWQ(int obits, int lbits, int rbits, WDataOutP owp,
                                      WDataInP const lwp, QData rd) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> rwp;
    VL_SET_WQ(rwp, rd);
    return VL_SHIFTR_WWW(obits, lbits, rbits, owp, lwp, rwp);
}

static inline IData VL_SHIFTR_IIW(int obits, int, int rbits, IData lhs,
                                  WDataInP const rwp) VL_PURE {
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) {
        if (VL_UNLIKELY(rwp[i])) return 0;  // Huge shift 1>>32 or more
    }
    return VL_SHIFTR_III(obits, obits, 32, lhs, rwp[0]);
}
static inline QData VL_SHIFTR_QQW(int obits, int, int rbits, QData lhs,
                                  WDataInP const rwp) VL_PURE {
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) {
        if (VL_UNLIKELY(rwp[i])) return 0;  // Huge shift 1>>32 or more
    }
    return VL_SHIFTR_QQI(obits, obits, 32, lhs, rwp[0]);
}

// EMIT_RULE: VL_SHIFTRS:  oclean=false; lclean=clean, rclean==clean;
static inline IData VL_SHIFTRS_III(int obits, int lbits, int, IData lhs, IData rhs) VL_PURE {
    // Note the C standard does not specify the >> operator as a arithmetic shift!
    // IEEE says signed if output signed, but bit position from lbits;
    // must use lbits for sign; lbits might != obits,
    // an EXTEND(SHIFTRS(...)) can became a SHIFTRS(...) within same 32/64 bit word length
    const IData sign = -(lhs >> (lbits - 1));  // ffff_ffff if negative
    if (VL_UNLIKELY(rhs >= VL_IDATASIZE)) return sign & VL_MASK_I(obits);
    const IData signext = ~(VL_MASK_I(lbits) >> rhs);  // One with bits where we've shifted "past"
    return (lhs >> rhs) | (sign & VL_CLEAN_II(obits, obits, signext));
}
static inline QData VL_SHIFTRS_QQI(int obits, int lbits, int, QData lhs, IData rhs) VL_PURE {
    const QData sign = -(lhs >> (lbits - 1));
    if (VL_UNLIKELY(rhs >= VL_QUADSIZE)) return sign & VL_MASK_Q(obits);
    const QData signext = ~(VL_MASK_Q(lbits) >> rhs);
    return (lhs >> rhs) | (sign & VL_CLEAN_QQ(obits, obits, signext));
}
static inline IData VL_SHIFTRS_IQI(int obits, int lbits, int rbits, QData lhs, IData rhs) VL_PURE {
    return static_cast<IData>(VL_SHIFTRS_QQI(obits, lbits, rbits, lhs, rhs));
}
static inline WDataOutP VL_SHIFTRS_WWI(int obits, int lbits, int, WDataOutP owp,
                                       WDataInP const lwp, IData rd) VL_MT_SAFE {
    const int word_shift = VL_BITWORD_E(rd);
    const int bit_shift = VL_BITBIT_E(rd);
    const int lmsw = VL_WORDS_I(obits) - 1;
    const EData sign = VL_SIGNONES_E(lbits, lwp[lmsw]);
    if (rd >= static_cast<IData>(obits)) {  // Shifting past end, sign in all of lbits
        for (int i = 0; i <= lmsw; ++i) owp[i] = sign;
        owp[lmsw] &= VL_MASK_E(lbits);
    } else if (bit_shift == 0) {  // Aligned word shift (>>0,>>32,>>64 etc)
        const int copy_words = (VL_WORDS_I(obits) - word_shift);
        for (int i = 0; i < copy_words; ++i) owp[i] = lwp[i + word_shift];
        if (copy_words >= 0) owp[copy_words - 1] |= ~VL_MASK_E(obits) & sign;
        for (int i = copy_words; i < VL_WORDS_I(obits); ++i) owp[i] = sign;
        owp[lmsw] &= VL_MASK_E(lbits);
    } else {
        const int loffset = rd & VL_SIZEBITS_E;
        const int nbitsonright
            = VL_EDATASIZE - loffset;  // bits that end up in lword (know loffset!=0)
        // Middle words
        const int words = VL_WORDS_I(obits - rd);
        for (int i = 0; i < words; ++i) {
            owp[i] = lwp[i + word_shift] >> loffset;
            const int upperword = i + word_shift + 1;
            if (upperword < VL_WORDS_I(obits)) owp[i] |= lwp[upperword] << nbitsonright;
        }
        if (words) owp[words - 1] |= sign & ~VL_MASK_E(obits - loffset);
        for (int i = words; i < VL_WORDS_I(obits); ++i) owp[i] = sign;
        owp[lmsw] &= VL_MASK_E(lbits);
    }
    return owp;
}
static inline WDataOutP VL_SHIFTRS_WWW(int obits, int lbits, int rbits, WDataOutP owp,
                                       WDataInP const lwp, WDataInP const rwp) VL_MT_SAFE {
    EData overshift = 0;  // Huge shift 1>>32 or more
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) overshift |= rwp[i];
    if (VL_UNLIKELY(overshift || rwp[0] >= static_cast<IData>(obits))) {
        const int owords = VL_WORDS_I(obits);
        if (VL_SIGN_E(lbits, lwp[owords - 1])) {
            VL_MEMSET_ONES_W(owp, owords);
            owp[owords - 1] &= VL_MASK_E(lbits);
        } else {
            VL_MEMSET_ZERO_W(owp, owords);
        }
        return owp;
    }
    return VL_SHIFTRS_WWI(obits, lbits, 32, owp, lwp, rwp[0]);
}
static inline WDataOutP VL_SHIFTRS_WWQ(int obits, int lbits, int rbits, WDataOutP owp,
                                       WDataInP const lwp, QData rd) VL_MT_SAFE {
    VlWide<VL_WQ_WORDS_E> rwp;
    VL_SET_WQ(rwp, rd);
    return VL_SHIFTRS_WWW(obits, lbits, rbits, owp, lwp, rwp);
}
static inline IData VL_SHIFTRS_IIW(int obits, int lbits, int rbits, IData lhs,
                                   WDataInP const rwp) VL_PURE {
    EData overshift = 0;  // Huge shift 1>>32 or more
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) overshift |= rwp[i];
    if (VL_UNLIKELY(overshift || rwp[0] >= static_cast<IData>(obits))) {
        const IData sign = -(lhs >> (lbits - 1));  // ffff_ffff if negative
        return VL_CLEAN_II(obits, obits, sign);
    }
    return VL_SHIFTRS_III(obits, lbits, 32, lhs, rwp[0]);
}
static inline QData VL_SHIFTRS_QQW(int obits, int lbits, int rbits, QData lhs,
                                   WDataInP const rwp) VL_PURE {
    EData overshift = 0;  // Huge shift 1>>32 or more
    for (int i = 1; i < VL_WORDS_I(rbits); ++i) overshift |= rwp[i];
    if (VL_UNLIKELY(overshift || rwp[0] >= static_cast<IData>(obits))) {
        const QData sign = -(lhs >> (lbits - 1));  // ffff_ffff if negative
        return VL_CLEAN_QQ(obits, obits, sign);
    }
    return VL_SHIFTRS_QQI(obits, lbits, 32, lhs, rwp[0]);
}
static inline IData VL_SHIFTRS_IIQ(int obits, int lbits, int rbits, IData lhs, QData rhs) VL_PURE {
    VlWide<VL_WQ_WORDS_E> rwp;
    VL_SET_WQ(rwp, rhs);
    return VL_SHIFTRS_IIW(obits, lbits, rbits, lhs, rwp);
}
static inline QData VL_SHIFTRS_QQQ(int obits, int lbits, int rbits, QData lhs, QData rhs) VL_PURE {
    VlWide<VL_WQ_WORDS_E> rwp;
    VL_SET_WQ(rwp, rhs);
    return VL_SHIFTRS_QQW(obits, lbits, rbits, lhs, rwp);
}

//===================================================================
// Bit selection

// EMIT_RULE: VL_BITSEL:  oclean=dirty; rclean==clean;
#define VL_BITSEL_IIII(lbits, lhs, rhs) ((lhs) >> (rhs))
#define VL_BITSEL_QIII(lbits, lhs, rhs) ((lhs) >> (rhs))
#define VL_BITSEL_QQII(lbits, lhs, rhs) ((lhs) >> (rhs))
#define VL_BITSEL_IQII(lbits, lhs, rhs) (static_cast<IData>((lhs) >> (rhs)))

static inline IData VL_BITSEL_IWII(int lbits, WDataInP const lwp, IData rd) VL_MT_SAFE {
    const int word = VL_BITWORD_E(rd);
    if (VL_UNLIKELY(rd > static_cast<IData>(lbits))) {
        return ~0;  // Spec says you can go outside the range of a array.  Don't coredump if so.
        // We return all 1's as that's more likely to find bugs (?) than 0's.
    } else {
        return (lwp[word] >> VL_BITBIT_E(rd));
    }
}

// EMIT_RULE: VL_RANGE:  oclean=lclean;  out=dirty
// <msb> & <lsb> MUST BE CLEAN (currently constant)
#define VL_SEL_IIII(lbits, lhs, lsb, width) ((lhs) >> (lsb))
#define VL_SEL_QQII(lbits, lhs, lsb, width) ((lhs) >> (lsb))
#define VL_SEL_IQII(lbits, lhs, lsb, width) (static_cast<IData>((lhs) >> (lsb)))

static inline IData VL_SEL_IWII(int lbits, WDataInP const lwp, IData lsb, IData width) VL_MT_SAFE {
    const int msb = lsb + width - 1;
    if (VL_UNLIKELY(msb >= lbits)) {
        return ~0;  // Spec says you can go outside the range of a array.  Don't coredump if so.
    } else if (VL_BITWORD_E(msb) == VL_BITWORD_E(static_cast<int>(lsb))) {
        return VL_BITRSHIFT_W(lwp, lsb);
    } else {
        // 32 bit extraction may span two words
        const int nbitsfromlow = VL_EDATASIZE - VL_BITBIT_E(lsb);  // bits that come from low word
        return ((lwp[VL_BITWORD_E(msb)] << nbitsfromlow) | VL_BITRSHIFT_W(lwp, lsb));
    }
}

static inline QData VL_SEL_QWII(int lbits, WDataInP const lwp, IData lsb, IData width) VL_MT_SAFE {
    const int msb = lsb + width - 1;
    if (VL_UNLIKELY(msb > lbits)) {
        return ~0;  // Spec says you can go outside the range of a array.  Don't coredump if so.
    } else if (VL_BITWORD_E(msb) == VL_BITWORD_E(static_cast<int>(lsb))) {
        return VL_BITRSHIFT_W(lwp, lsb);
    } else if (VL_BITWORD_E(msb) == 1 + VL_BITWORD_E(static_cast<int>(lsb))) {
        const int nbitsfromlow = VL_EDATASIZE - VL_BITBIT_E(lsb);
        const QData hi = (lwp[VL_BITWORD_E(msb)]);
        const QData lo = VL_BITRSHIFT_W(lwp, lsb);
        return (hi << nbitsfromlow) | lo;
    } else {
        // 64 bit extraction may span three words
        const int nbitsfromlow = VL_EDATASIZE - VL_BITBIT_E(lsb);
        const QData hi = (lwp[VL_BITWORD_E(msb)]);
        const QData mid = (lwp[VL_BITWORD_E(lsb) + 1]);
        const QData lo = VL_BITRSHIFT_W(lwp, lsb);
        return (hi << (nbitsfromlow + VL_EDATASIZE)) | (mid << nbitsfromlow) | lo;
    }
}

static inline WDataOutP VL_SEL_WWII(int obits, int lbits, WDataOutP owp, WDataInP const lwp,
                                    IData lsb, IData width) VL_MT_SAFE {
    const int msb = lsb + width - 1;
    const int word_shift = VL_BITWORD_E(lsb);
    if (VL_UNLIKELY(msb > lbits)) {  // Outside bounds,
        for (int i = 0; i < VL_WORDS_I(obits) - 1; ++i) owp[i] = ~0;
        owp[VL_WORDS_I(obits) - 1] = VL_MASK_E(obits);
    } else if (VL_BITBIT_E(lsb) == 0) {
        // Just a word extract
        for (int i = 0; i < VL_WORDS_I(obits); ++i) owp[i] = lwp[i + word_shift];
    } else {
        // Not a _vl_insert because the bits come from any bit number and goto bit 0
        const int loffset = lsb & VL_SIZEBITS_E;
        const int nbitsfromlow = VL_EDATASIZE - loffset;  // bits that end up in lword (know
                                                          // loffset!=0) Middle words
        const int words = VL_WORDS_I(msb - lsb + 1);
        for (int i = 0; i < words; ++i) {
            owp[i] = lwp[i + word_shift] >> loffset;
            const int upperword = i + word_shift + 1;
            if (upperword <= static_cast<int>(VL_BITWORD_E(msb))) {
                owp[i] |= lwp[upperword] << nbitsfromlow;
            }
        }
        for (int i = words; i < VL_WORDS_I(obits); ++i) owp[i] = 0;
    }
    return owp;
}

template <typename T>
static inline VlQueue<T> VL_CLONE_Q(const VlQueue<T>& from, int lbits, int srcElementBits,
                                    int dstElementBits) {
    VlQueue<T> ret;
    VL_COPY_Q(ret, from, lbits, srcElementBits, dstElementBits);
    return ret;
}

template <typename T>
static inline VlQueue<T> VL_REVCLONE_Q(const VlQueue<T>& from, int lbits, int srcElementBits,
                                       int dstElementBits) {
    VlQueue<T> ret;
    VL_REVCOPY_Q(ret, from, lbits, srcElementBits, dstElementBits);
    return ret;
}

// Helper function to get a bit from a queue at a specific bit index
template <typename T>
static inline bool VL_GET_QUEUE_BIT(const VlQueue<T>& queue, int srcElementBits, size_t bitIndex) {
    const size_t elemIdx = bitIndex / srcElementBits;
    if (VL_UNLIKELY(elemIdx >= queue.size())) return false;

    const T element = queue.at(elemIdx);
    if (srcElementBits == 1) {
        return element & 1;
    } else {
        const size_t bitInElem = bitIndex % srcElementBits;
        const size_t actualBitPos = srcElementBits - 1 - bitInElem;
        return (element >> actualBitPos) & 1;
    }
}

// Helper function to set a bit in the destination queue
template <typename T>
static inline void VL_SET_QUEUE_BIT(VlQueue<T>& queue, int dstElementBits, size_t bitIndex,
                                    bool value) {
    if (dstElementBits == 1) {
        if (VL_UNLIKELY(bitIndex >= queue.size())) return;
        queue.atWrite(bitIndex) = value ? 1 : 0;
    } else {
        const size_t elemIdx = bitIndex / dstElementBits;
        if (VL_UNLIKELY(elemIdx >= queue.size())) return;
        const size_t bitInElem = bitIndex % dstElementBits;
        const size_t actualBitPos = dstElementBits - 1 - bitInElem;
        if (value) {
            queue.atWrite(elemIdx) |= (static_cast<T>(1) << actualBitPos);
        } else {
            queue.atWrite(elemIdx) &= ~(static_cast<T>(1) << actualBitPos);
        }
    }
}

// Helper function to get a bit from a VlWide queue at a specific bit index
template <std::size_t N_Words>
static inline bool VL_GET_QUEUE_BIT(const VlQueue<VlWide<N_Words>>& queue, int srcElementBits,
                                    size_t bitIndex) {
    const size_t elemIdx = bitIndex / srcElementBits;
    if (VL_UNLIKELY(elemIdx >= queue.size())) return false;

    const VlWide<N_Words>& element = queue.at(elemIdx);
    const size_t bitInElem = bitIndex % srcElementBits;
    const size_t actualBitPos = srcElementBits - 1 - bitInElem;

    return VL_BITISSET_W(element.data(), actualBitPos);
}

// Helper function to set a bit in a VlWide queue at a specific bit index
template <std::size_t N_Words>
static inline void VL_SET_QUEUE_BIT(VlQueue<VlWide<N_Words>>& queue, int dstElementBits,
                                    size_t bitIndex, bool value) {
    const size_t elemIdx = bitIndex / dstElementBits;
    if (VL_UNLIKELY(elemIdx >= queue.size())) return;

    const size_t bitInElem = bitIndex % dstElementBits;
    const size_t actualBitPos = dstElementBits - 1 - bitInElem;

    VlWide<N_Words>& element = queue.atWrite(elemIdx);
    if (value) {
        VL_ASSIGNBIT_WO(actualBitPos, element.data());
    } else {
        VL_ASSIGNBIT_WI(actualBitPos, element.data(), 0);
    }
}

template <typename T>
static inline void VL_ZERO_INIT_QUEUE_ELEM(T& elem) {
    elem = 0;
}

template <std::size_t N_Words>
static inline void VL_ZERO_INIT_QUEUE_ELEM(VlWide<N_Words>& elem) {
    for (size_t j = 0; j < N_Words; ++j) { elem.at(j) = 0; }
}

// This specialization works for both VlQueue<CData> (and similar) as well
// as VlQueue<VlWide<N>>.
template <typename T>
static inline void VL_COPY_Q(VlQueue<T>& q, const VlQueue<T>& from, int lbits, int srcElementBits,
                             int dstElementBits) {
    if (srcElementBits == dstElementBits) {
        // Simple case: same element bit width, direct copy of each element
        if (VL_UNLIKELY(&q == &from)) return;  // Skip self-assignment when it's truly a no-op
        q = from;
    } else {
        // Different element bit widths: use streaming conversion
        VlQueue<T> srcCopy = from;
        const size_t srcTotalBits = from.size() * srcElementBits;
        const size_t dstSize = (srcTotalBits + dstElementBits - 1) / dstElementBits;
        q.renew(dstSize);
        for (size_t i = 0; i < dstSize; ++i) { VL_ZERO_INIT_QUEUE_ELEM(q.atWrite(i)); }
        for (size_t bitIndex = 0; bitIndex < srcTotalBits; ++bitIndex) {
            VL_SET_QUEUE_BIT(q, dstElementBits, bitIndex,
                             VL_GET_QUEUE_BIT(srcCopy, srcElementBits, bitIndex));
        }
    }
}

// This specialization works for both VlQueue<CData> (and similar) as well
// as VlQueue<VlWide<N>>.
template <typename T>
static inline void VL_REVCOPY_Q(VlQueue<T>& q, const VlQueue<T>& from, int lbits,
                                int srcElementBits, int dstElementBits) {
    const size_t srcTotalBits = from.size() * srcElementBits;
    const size_t dstSize = (srcTotalBits + dstElementBits - 1) / dstElementBits;

    // Always make a copy to handle the case where q and from are the same queue
    VlQueue<T> srcCopy = from;

    // Initialize all elements to zero using appropriate method
    q.renew(dstSize);
    for (size_t i = 0; i < dstSize; ++i) VL_ZERO_INIT_QUEUE_ELEM(q.atWrite(i));

    if (lbits == 1) {
        // Simple bit reversal: write directly to destination
        for (int i = srcTotalBits - 1; i >= 0; --i) {
            VL_SET_QUEUE_BIT(q, dstElementBits, srcTotalBits - 1 - i,
                             VL_GET_QUEUE_BIT(srcCopy, srcElementBits, i));
        }
    } else {
        // Generalized block-reversal for lbits > 1:
        // 1. Reverse all bits using 1-bit blocks
        // 2. Split into lbits-sized blocks and pad incomplete blocks on the left
        // 3. Reverse each lbits-sized block using 1-bit blocks
        const size_t numCompleteBlocks = srcTotalBits / lbits;
        const size_t remainderBits = srcTotalBits % lbits;
        const size_t srcBlocks = numCompleteBlocks + (remainderBits > 0 ? 1 : 0);

        size_t dstBitIndex = 0;

        for (size_t block = 0; block < srcBlocks; ++block) {
            const size_t blockStart = block * lbits;
            const int bitsToProcess = VL_LIKELY(block < numCompleteBlocks) ? lbits : remainderBits;
            for (int bit = bitsToProcess - 1; bit >= 0; --bit) {
                const size_t reversedBitIndex = blockStart + bit;
                const size_t originalBitIndex = srcTotalBits - 1 - reversedBitIndex;
                VL_SET_QUEUE_BIT(q, dstElementBits, dstBitIndex++,
                                 VL_GET_QUEUE_BIT(srcCopy, srcElementBits, originalBitIndex));
            }
            dstBitIndex += lbits - bitsToProcess;
        }
    }
}

//======================================================================
// Expressions needing insert/select

static inline void VL_UNPACK_RI_I(int lbits, int rbits, VlQueue<CData>& q, IData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RI_I(int lbits, int rbits, VlQueue<SData>& q, IData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RI_I(int lbits, int rbits, VlQueue<IData>& q, IData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RI_Q(int lbits, int rbits, VlQueue<CData>& q, QData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RI_Q(int lbits, int rbits, VlQueue<SData>& q, QData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RI_Q(int lbits, int rbits, VlQueue<IData>& q, QData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RQ_Q(int lbits, int rbits, VlQueue<QData>& q, QData from) {
    const size_t size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const QData mask = VL_MASK_Q(lbits);
    for (size_t i = 0; i < size; ++i) q.atWrite(size - 1 - i) = (from >> (i * lbits)) & mask;
}

static inline void VL_UNPACK_RI_W(int lbits, int rbits, VlQueue<CData>& q, WDataInP rwp) {
    const int size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) {
        // Extract from MSB to LSB: MSB goes to index 0
        const int bitPos = rbits - (i + 1) * lbits;
        const int actualBitPos = (bitPos < 0) ? 0 : bitPos;
        const int actualWidth = (bitPos < 0) ? (lbits + bitPos) : lbits;
        q.atWrite(i) = VL_SEL_IWII(rbits, rwp, actualBitPos, actualWidth) & mask;
    }
}

static inline void VL_UNPACK_RI_W(int lbits, int rbits, VlQueue<SData>& q, WDataInP rwp) {
    const int size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) {
        // Extract from MSB to LSB: MSB goes to index 0
        const int bitPos = rbits - (i + 1) * lbits;
        const int actualBitPos = (bitPos < 0) ? 0 : bitPos;
        const int actualWidth = (bitPos < 0) ? (lbits + bitPos) : lbits;
        q.atWrite(i) = VL_SEL_IWII(rbits, rwp, actualBitPos, actualWidth) & mask;
    }
}

static inline void VL_UNPACK_RI_W(int lbits, int rbits, VlQueue<IData>& q, WDataInP rwp) {
    const int size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < size; ++i) {
        // Extract from MSB to LSB: MSB goes to index 0
        const int bitPos = rbits - (i + 1) * lbits;
        const int actualBitPos = (bitPos < 0) ? 0 : bitPos;
        const int actualWidth = (bitPos < 0) ? (lbits + bitPos) : lbits;
        q.atWrite(i) = VL_SEL_IWII(rbits, rwp, actualBitPos, actualWidth) & mask;
    }
}

static inline void VL_UNPACK_RQ_W(int lbits, int rbits, VlQueue<QData>& q, WDataInP rwp) {
    const int size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    const QData mask = VL_MASK_Q(lbits);
    for (size_t i = 0; i < size; ++i) {
        // Extract from MSB to LSB: MSB goes to index 0
        const int bitPos = rbits - (i + 1) * lbits;
        const int actualBitPos = (bitPos < 0) ? 0 : bitPos;
        const int actualWidth = (bitPos < 0) ? (lbits + bitPos) : lbits;
        q.atWrite(i) = VL_SEL_QWII(rbits, rwp, actualBitPos, actualWidth) & mask;
    }
}

template <std::size_t N_Words>
static inline void VL_UNPACK_RW_W(int lbits, int rbits, VlQueue<VlWide<N_Words>>& q,
                                  WDataInP rwp) {
    const int size = (rbits + lbits - 1) / lbits;
    q.renew(size);
    for (size_t i = 0; i < size; ++i) {
        // Extract from MSB to LSB: MSB goes to index 0
        const int bitPos = rbits - (i + 1) * lbits;
        const int actualBitPos = (bitPos < 0) ? 0 : bitPos;
        const int actualWidth = (bitPos < 0) ? (lbits + bitPos) : lbits;
        VL_SEL_WWII(actualWidth, rbits, q.atWrite(i), rwp, actualBitPos, actualWidth);
    }
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_I(int lbits, int rbits, VlUnpacked<CData, N_Depth>& q,
                                  IData from) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_I(int lbits, int rbits, VlUnpacked<SData, N_Depth>& q,
                                  IData from) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_I(int lbits, int rbits, VlUnpacked<IData, N_Depth>& q,
                                  IData from) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_Q(int lbits, int rbits, VlUnpacked<CData, N_Depth>& q,
                                  QData from) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_Q(int lbits, int rbits, VlUnpacked<SData, N_Depth>& q,
                                  QData from) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_Q(int lbits, int rbits, VlUnpacked<IData, N_Depth>& q,
                                  QData from) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UQ_Q(int lbits, int rbits, VlUnpacked<QData, N_Depth>& q,
                                  QData from) {
    const QData mask = VL_MASK_Q(lbits);
    for (size_t i = 0; i < N_Depth; ++i) q[i] = (from >> ((N_Depth - 1 - i) * lbits)) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_W(int lbits, int rbits, VlUnpacked<CData, N_Depth>& q,
                                  WDataInP rwp) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i)
        q[i] = VL_SEL_IWII(rbits, rwp, (N_Depth - 1 - i) * lbits, lbits) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_W(int lbits, int rbits, VlUnpacked<SData, N_Depth>& q,
                                  WDataInP rwp) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i)
        q[i] = VL_SEL_IWII(rbits, rwp, (N_Depth - 1 - i) * lbits, lbits) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UI_W(int lbits, int rbits, VlUnpacked<IData, N_Depth>& q,
                                  WDataInP rwp) {
    const IData mask = VL_MASK_I(lbits);
    for (size_t i = 0; i < N_Depth; ++i)
        q[i] = VL_SEL_IWII(rbits, rwp, (N_Depth - 1 - i) * lbits, lbits) & mask;
}

template <std::size_t N_Depth>
static inline void VL_UNPACK_UQ_W(int lbits, int rbits, VlUnpacked<QData, N_Depth>& q,
                                  WDataInP rwp) {
    const QData mask = VL_MASK_Q(lbits);
    for (size_t i = 0; i < N_Depth; ++i)
        q[i] = VL_SEL_QWII(rbits, rwp, (N_Depth - 1 - i) * lbits, lbits) & mask;
}

template <std::size_t N_Depth, std::size_t N_Words>
static inline void VL_UNPACK_UW_W(int lbits, int rbits, VlUnpacked<VlWide<N_Words>, N_Depth>& q,
                                  WDataInP rwp) {
    for (size_t i = 0; i < N_Depth; ++i)
        VL_SEL_WWII(lbits, rbits, q[i], rwp, (N_Depth - 1 - i) * lbits, lbits);
}

// Return QData from double (numeric)
// EMIT_RULE: VL_RTOIROUND_Q_D:  oclean=dirty; lclean==clean/real
static inline QData VL_RTOIROUND_Q_D(double lhs) VL_PURE {
    // IEEE format: [63]=sign [62:52]=exp+1023 [51:0]=mantissa
    // This does not need to support subnormals as they are sub-integral
    lhs = VL_ROUND(lhs);
    if (lhs == 0.0) return 0;
    const QData q = VL_CVT_Q_D(lhs);
    const int lsb = static_cast<int>((q >> 52ULL) & VL_MASK_Q(11)) - 1023 - 52;
    const uint64_t mantissa = (q & VL_MASK_Q(52)) | (1ULL << 52);
    uint64_t out = 0;
    if (lsb < 0) {
        out = mantissa >> -lsb;
    } else if (lsb < 64) {
        out = mantissa << lsb;
    }
    if (lhs < 0) out = -out;
    return out;
}
static inline IData VL_RTOIROUND_I_D(double lhs) VL_PURE {
    return static_cast<IData>(VL_RTOIROUND_Q_D(lhs));
}
static inline WDataOutP VL_RTOIROUND_W_D(int obits, WDataOutP owp, double lhs) VL_MT_SAFE {
    // IEEE format: [63]=sign [62:52]=exp+1023 [51:0]=mantissa
    // This does not need to support subnormals as they are sub-integral
    lhs = VL_ROUND(lhs);
    VL_ZERO_W(obits, owp);
    if (lhs == 0.0) return owp;
    const QData q = VL_CVT_Q_D(lhs);
    const int lsb = static_cast<int>((q >> 52ULL) & VL_MASK_Q(11)) - 1023 - 52;
    const uint64_t mantissa = (q & VL_MASK_Q(52)) | (1ULL << 52);
    if (lsb < 0) {
        VL_SET_WQ(owp, mantissa >> -lsb);
    } else if (lsb < obits) {
        _vl_insert_WQ(owp, mantissa, lsb + 52, lsb);
    }
    if (lhs < 0) VL_NEGATE_INPLACE_W(VL_WORDS_I(obits), owp);
    return owp;
}

//======================================================================
// Range assignments

// EMIT_RULE: VL_ASSIGNRANGE:  rclean=dirty;
static inline void VL_ASSIGNSEL_II(int rbits, int obits, int lsb, CData& lhsr, IData rhs) VL_PURE {
    _vl_insert_II(lhsr, rhs, lsb + obits - 1, lsb, rbits);
}
static inline void VL_ASSIGNSEL_II(int rbits, int obits, int lsb, SData& lhsr, IData rhs) VL_PURE {
    _vl_insert_II(lhsr, rhs, lsb + obits - 1, lsb, rbits);
}
static inline void VL_ASSIGNSEL_II(int rbits, int obits, int lsb, IData& lhsr, IData rhs) VL_PURE {
    _vl_insert_II(lhsr, rhs, lsb + obits - 1, lsb, rbits);
}
static inline void VL_ASSIGNSEL_QI(int rbits, int obits, int lsb, QData& lhsr, IData rhs) VL_PURE {
    _vl_insert_QQ(lhsr, rhs, lsb + obits - 1, lsb, rbits);
}
static inline void VL_ASSIGNSEL_QQ(int rbits, int obits, int lsb, QData& lhsr, QData rhs) VL_PURE {
    _vl_insert_QQ(lhsr, rhs, lsb + obits - 1, lsb, rbits);
}
// static inline void VL_ASSIGNSEL_IIIW(int obits, int lsb, IData& lhsr, WDataInP const rwp)
// VL_MT_SAFE { Illegal, as lhs width >= rhs width
static inline void VL_ASSIGNSEL_WI(int rbits, int obits, int lsb, WDataOutP iowp,
                                   IData rhs) VL_MT_SAFE {
    _vl_insert_WI(iowp, rhs, lsb + obits - 1, lsb, rbits);
}
static inline void VL_ASSIGNSEL_WQ(int rbits, int obits, int lsb, WDataOutP iowp,
                                   QData rhs) VL_MT_SAFE {
    _vl_insert_WQ(iowp, rhs, lsb + obits - 1, lsb, rbits);
}
static inline void VL_ASSIGNSEL_WW(int rbits, int obits, int lsb, WDataOutP iowp,
                                   WDataInP const rwp) VL_MT_SAFE {
    _vl_insert_WW(iowp, rwp, lsb + obits - 1, lsb, rbits);
}

//====================================================
// Range assignments

// These additional functions copy bits range [obis+roffset-1:roffset] from rhs to lower bits
// of lhs(select before assigning). Rhs should always be wider than lhs.
static inline void VL_SELASSIGN_II(int rbits, int obits, CData& lhsr, IData rhs,
                                   int roffset) VL_PURE {
    _vl_insert_II(lhsr, rhs >> roffset, obits - 1, 0, rbits);
}
static inline void VL_SELASSIGN_II(int rbits, int obits, SData& lhsr, IData rhs,
                                   int roffset) VL_PURE {
    _vl_insert_II(lhsr, rhs >> roffset, obits - 1, 0, rbits);
}
static inline void VL_SELASSIGN_II(int rbits, int obits, IData& lhsr, IData rhs,
                                   int roffset) VL_PURE {
    _vl_insert_II(lhsr, rhs >> roffset, obits - 1, 0, rbits);
}
static inline void VL_SELASSIGN_IQ(int rbits, int obits, CData& lhsr, QData rhs,
                                   int roffset) VL_PURE {
    // it will be truncated to right CData mask
    const CData cleanmask = VL_MASK_I(rbits);
    const CData insmask = VL_MASK_I(obits);
    lhsr = (lhsr & ~insmask) | (static_cast<CData>(rhs >> roffset) & (insmask & cleanmask));
}
static inline void VL_SELASSIGN_IQ(int rbits, int obits, SData& lhsr, QData rhs,
                                   int roffset) VL_PURE {
    // it will be truncated to right CData mask
    const SData cleanmask = VL_MASK_I(rbits);
    const SData insmask = VL_MASK_I(obits);
    lhsr = (lhsr & ~insmask) | (static_cast<SData>(rhs >> roffset) & (insmask & cleanmask));
}
static inline void VL_SELASSIGN_IQ(int rbits, int obits, IData& lhsr, QData rhs,
                                   int roffset) VL_PURE {
    const IData cleanmask = VL_MASK_I(rbits);
    const IData insmask = VL_MASK_I(obits);
    lhsr = (lhsr & ~insmask) | (static_cast<IData>(rhs >> roffset) & (insmask & cleanmask));
}

static inline void VL_SELASSIGN_QQ(int rbits, int obits, QData& lhsr, QData rhs,
                                   int roffset) VL_PURE {
    _vl_insert_QQ(lhsr, rhs >> roffset, obits - 1, 0, rbits);
}

static inline void VL_SELASSIGN_IW(int rbits, int obits, CData& lhsr, WDataInP const rhs,
                                   int roffset) VL_MT_SAFE {
    IData l = static_cast<IData>(lhsr);
    _vl_insert_IW(l, rhs, roffset + obits - 1, roffset, rbits);
    lhsr = static_cast<CData>(l);
}
static inline void VL_SELASSIGN_IW(int rbits, int obits, SData& lhsr, WDataInP const rhs,
                                   int roffset) VL_MT_SAFE {
    IData l = static_cast<IData>(lhsr);
    _vl_insert_IW(l, rhs, roffset + obits - 1, roffset, rbits);
    lhsr = static_cast<SData>(l);
}
static inline void VL_SELASSIGN_IW(int rbits, int obits, IData& lhsr, WDataInP const rhs,
                                   int roffset) VL_MT_SAFE {
    _vl_insert_IW(lhsr, rhs, roffset + obits - 1, roffset, rbits);
}
static inline void VL_SELASSIGN_QW(int rbits, int obits, QData& lhsr, WDataInP const rhs,
                                   int roffset) VL_MT_SAFE {
    // assert VL_QDATASIZE >= rbits > VL_IDATASIZE;
    IData low = static_cast<IData>(lhsr);
    IData high = static_cast<IData>(lhsr >> VL_IDATASIZE);
    if (obits <= VL_IDATASIZE) {
        _vl_insert_IW(low, rhs, obits + roffset - 1, roffset, VL_IDATASIZE);
    } else {
        _vl_insert_IW(low, rhs, roffset + VL_IDATASIZE - 1, roffset, VL_IDATASIZE);
        _vl_insert_IW(high, rhs, roffset + obits - 1, roffset + VL_IDATASIZE,
                      rbits - VL_IDATASIZE);
    }
    lhsr = (static_cast<QData>(high) << VL_IDATASIZE) | low;
}

static inline void VL_SELASSIGN_WW(int rbits, int obits, WDataOutP iowp, WDataInP const rwp,
                                   int roffset) VL_MT_SAFE {
    // assert rbits > VL_QDATASIZE
    const int wordoff = roffset / VL_EDATASIZE;
    const int lsb = roffset & VL_SIZEBITS_E;
    const int upperbits = lsb == 0 ? 0 : VL_EDATASIZE - lsb;
    // If roffset is not aligned, we copy some bits to align it.
    if (lsb != 0) {
        const int w = obits < upperbits ? obits : upperbits;
        const int insmask = VL_MASK_E(w);
        iowp[0] = (iowp[0] & ~insmask) | ((rwp[wordoff] >> lsb) & insmask);
        // cppcheck-suppress knownConditionTrueFalse
        if (w == obits) return;
        obits -= w;
    }
    _vl_insert_WW(iowp, rwp + wordoff + (lsb != 0), upperbits + obits - 1, upperbits, rbits);
}

//======================================================================
// Triops

static inline WDataOutP VL_COND_WIWW(int obits, WDataOutP owp, int cond, WDataInP const w1p,
                                     WDataInP const w2p) VL_MT_SAFE {
    return VL_MEMCPY_W(owp, cond ? w1p : w2p, VL_WORDS_I(obits));
}

//======================================================================
// Constification

// VL_CONST_W_#X(int obits, WDataOutP owp, IData data0, .... IData data(#-1))
// Sets wide vector words to specified constant words.
// These macros are used when o might represent more words then are given as constants,
// hence all upper words must be zeroed.
// If changing the number of functions here, also change EMITCINLINES_NUM_CONSTW

#define VL_C_END_(obits, wordsSet) \
    VL_MEMSET_ZERO_W(o + (wordsSet), VL_WORDS_I(obits) - (wordsSet)); \
    return o

// clang-format off
static inline WDataOutP VL_CONST_W_1X(int obits, WDataOutP o, EData d0) VL_MT_SAFE {
    o[0] = d0;
    VL_C_END_(obits, 1);
}
static inline WDataOutP VL_CONST_W_2X(int obits, WDataOutP o, EData d1, EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;
    VL_C_END_(obits, 2);
}
static inline WDataOutP VL_CONST_W_3X(int obits, WDataOutP o, EData d2, EData d1,
                                      EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;  o[2] = d2;
    VL_C_END_(obits, 3);
}
static inline WDataOutP VL_CONST_W_4X(int obits, WDataOutP o,
                                      EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;  o[2] = d2;  o[3] = d3;
    VL_C_END_(obits, 4);
}
static inline WDataOutP VL_CONST_W_5X(int obits, WDataOutP o,
                                      EData d4,
                                      EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;  o[2] = d2;  o[3] = d3;
    o[4] = d4;
    VL_C_END_(obits, 5);
}
static inline WDataOutP VL_CONST_W_6X(int obits, WDataOutP o,
                                      EData d5, EData d4,
                                      EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;  o[2] = d2;  o[3] = d3;
    o[4] = d4;  o[5] = d5;
    VL_C_END_(obits, 6);
}
static inline WDataOutP VL_CONST_W_7X(int obits, WDataOutP o,
                                      EData d6, EData d5, EData d4,
                                      EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;  o[2] = d2;  o[3] = d3;
    o[4] = d4;  o[5] = d5;  o[6] = d6;
    VL_C_END_(obits, 7);
}
static inline WDataOutP VL_CONST_W_8X(int obits, WDataOutP o,
                                      EData d7, EData d6, EData d5, EData d4,
                                      EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    o[0] = d0;  o[1] = d1;  o[2] = d2;  o[3] = d3;
    o[4] = d4;  o[5] = d5;  o[6] = d6;  o[7] = d7;
    VL_C_END_(obits, 8);
}
//
static inline WDataOutP VL_CONSTHI_W_1X(int obits, int lsb, WDataOutP o,
                                        EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 1);
}
static inline WDataOutP VL_CONSTHI_W_2X(int obits, int lsb, WDataOutP o,
                                        EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 2);
}
static inline WDataOutP VL_CONSTHI_W_3X(int obits, int lsb, WDataOutP o,
                                        EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;  ohi[2] = d2;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 3);
}
static inline WDataOutP VL_CONSTHI_W_4X(int obits, int lsb, WDataOutP o,
                                        EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;  ohi[2] = d2;  ohi[3] = d3;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 4);
}
static inline WDataOutP VL_CONSTHI_W_5X(int obits, int lsb, WDataOutP o,
                                        EData d4,
                                        EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;  ohi[2] = d2;  ohi[3] = d3;
    ohi[4] = d4;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 5);
}
static inline WDataOutP VL_CONSTHI_W_6X(int obits, int lsb, WDataOutP o,
                                        EData d5, EData d4,
                                        EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;  ohi[2] = d2;  ohi[3] = d3;
    ohi[4] = d4;  ohi[5] = d5;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 6);
}
static inline WDataOutP VL_CONSTHI_W_7X(int obits, int lsb, WDataOutP o,
                                        EData d6, EData d5, EData d4,
                                        EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;  ohi[2] = d2;  ohi[3] = d3;
    ohi[4] = d4;  ohi[5] = d5;  ohi[6] = d6;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 7);
}
static inline WDataOutP VL_CONSTHI_W_8X(int obits, int lsb, WDataOutP o,
                                        EData d7, EData d6, EData d5, EData d4,
                                        EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP ohi = o + VL_WORDS_I(lsb);
    ohi[0] = d0;  ohi[1] = d1;  ohi[2] = d2;  ohi[3] = d3;
    ohi[4] = d4;  ohi[5] = d5;  ohi[6] = d6;  ohi[7] = d7;
    VL_C_END_(obits, VL_WORDS_I(lsb) + 8);
}

#undef VL_C_END_

// Partial constant, lower words of vector wider than 8*32, starting at bit number lsb
static inline void VL_CONSTLO_W_8X(int lsb, WDataOutP obase,
                                   EData d7, EData d6, EData d5, EData d4,
                                   EData d3, EData d2, EData d1, EData d0) VL_MT_SAFE {
    WDataOutP o = obase + VL_WORDS_I(lsb);
    o[0] = d0; o[1] = d1; o[2] = d2; o[3] = d3; o[4] = d4; o[5] = d5; o[6] = d6; o[7] = d7;
}
// clang-format on

//======================================================================
// Strings

extern std::string VL_PUTC_N(const std::string& lhs, IData rhs, CData ths) VL_PURE;
extern CData VL_GETC_N(const std::string& lhs, IData rhs) VL_PURE;
extern std::string VL_SUBSTR_N(const std::string& lhs, IData rhs, IData ths) VL_PURE;

inline IData VL_CMP_NN(const std::string& lhs, const std::string& rhs, bool ignoreCase) VL_PURE {
    // SystemVerilog does not allow a string variable to contain '\0'.
    // So C functions such as strcmp() can correctly compare strings.
    if (ignoreCase) {
        return VL_STRCASECMP(lhs.c_str(), rhs.c_str());
    } else {
        return std::strcmp(lhs.c_str(), rhs.c_str());
    }
}

extern IData VL_ATOI_N(const std::string& str, int base) VL_PURE;
extern IData VL_NTOI_I(int obits, const std::string& str) VL_PURE;
extern QData VL_NTOI_Q(int obits, const std::string& str) VL_PURE;
extern void VL_NTOI_W(int obits, WDataOutP owp, const std::string& str) VL_PURE;

extern IData VL_FGETS_NI(std::string& dest, IData fpi) VL_MT_SAFE;

//======================================================================
// Dist functions

extern IData VL_DIST_CHI_SQUARE(IData& seedr, IData udeg_of_free) VL_MT_SAFE;
extern IData VL_DIST_ERLANG(IData& seedr, IData uk, IData umean) VL_MT_SAFE;
extern IData VL_DIST_EXPONENTIAL(IData& seedr, IData umean) VL_MT_SAFE;
extern IData VL_DIST_NORMAL(IData& seedr, IData umean, IData udeviation) VL_MT_SAFE;
extern IData VL_DIST_POISSON(IData& seedr, IData umean) VL_MT_SAFE;
extern IData VL_DIST_T(IData& seedr, IData udeg_of_free) VL_MT_SAFE;
extern IData VL_DIST_UNIFORM(IData& seedr, IData ustart, IData uend) VL_MT_SAFE;

//======================================================================
// Conversion functions

extern std::string VL_CVT_PACK_STR_NW(int lwords, const WDataInP lwp) VL_PURE;
extern std::string VL_CVT_PACK_STR_ND(const VlQueue<std::string>& q) VL_PURE;
inline std::string VL_CVT_PACK_STR_NQ(QData lhs) VL_PURE {
    VlWide<VL_WQ_WORDS_E> lw;
    VL_SET_WQ(lw, lhs);
    return VL_CVT_PACK_STR_NW(VL_WQ_WORDS_E, lw);
}
inline std::string VL_CVT_PACK_STR_NN(const std::string& lhs) VL_PURE { return lhs; }
inline std::string& VL_CVT_PACK_STR_NN(std::string& lhs) VL_PURE { return lhs; }
inline std::string VL_CVT_PACK_STR_NI(IData lhs) VL_PURE {
    VlWide<VL_WQ_WORDS_E> lw;
    VL_SET_WI(lw, lhs);
    return VL_CVT_PACK_STR_NW(1, lw);
}
inline std::string VL_CONCATN_NNN(const std::string& lhs, const std::string& rhs) VL_PURE {
    return lhs + rhs;
}
inline std::string VL_REPLICATEN_NNQ(const std::string& lhs, IData rep) VL_PURE {
    std::string result;
    result.reserve(lhs.length() * rep);
    for (unsigned times = 0; times < rep; ++times) result += lhs;
    return result;
}
inline std::string VL_REPLICATEN_NNI(const std::string& lhs, IData rep) VL_PURE {
    return VL_REPLICATEN_NNQ(lhs, rep);
}

inline IData VL_LEN_IN(const std::string& ld) { return static_cast<IData>(ld.length()); }
extern std::string VL_TOLOWER_NN(const std::string& ld) VL_PURE;
extern std::string VL_TOUPPER_NN(const std::string& ld) VL_PURE;

extern IData VL_FERROR_IN(IData fpi, std::string& outputr) VL_MT_SAFE;
extern IData VL_FERROR_IW(IData fpi, int obits, WDataOutP outwp) VL_MT_SAFE;
extern IData VL_FOPEN_NN(const std::string& filename, const std::string& mode) VL_MT_SAFE;
extern IData VL_FOPEN_MCD_N(const std::string& filename) VL_MT_SAFE;
extern void VL_READMEM_N(bool hex, int bits, QData depth, int array_lsb,
                         const std::string& filename, void* memp, QData start,
                         QData end) VL_MT_SAFE;
extern void VL_WRITEMEM_N(bool hex, int bits, QData depth, int array_lsb,
                          const std::string& filename, const void* memp, QData start,
                          QData end) VL_MT_SAFE;
extern IData VL_SSCANF_INNX(int lbits, const std::string& ld, const std::string& format, int argc,
                            ...) VL_MT_SAFE;
extern void VL_SFORMAT_NX(int obits_ignored, std::string& output, const std::string& format,
                          int argc, ...) VL_MT_SAFE;
extern std::string VL_SFORMATF_N_NX(const std::string& format, int argc, ...) VL_MT_SAFE;
extern void VL_TIMEFORMAT_IINI(bool hasUnits, int units, bool hasPrecision, int precision,
                               bool hasSuffix, const std::string& suffix, bool hasWidth, int width,
                               VerilatedContext* contextp) VL_MT_SAFE;
extern IData VL_VALUEPLUSARGS_INW(int rbits, const std::string& ld, WDataOutP rwp) VL_MT_SAFE;
inline IData VL_VALUEPLUSARGS_IND(int rbits, const std::string& ld, double& rdr) VL_MT_SAFE {
    VlWide<2> rwp;
    const IData got = VL_VALUEPLUSARGS_INW(rbits, ld, rwp);
    if (got) rdr = VL_CVT_D_Q(VL_SET_QW(rwp));
    return got;
}
inline IData VL_VALUEPLUSARGS_INI(int rbits, const std::string& ld, CData& rdr) VL_MT_SAFE {
    VlWide<2> rwp;
    const IData got = VL_VALUEPLUSARGS_INW(rbits, ld, rwp);
    if (got) rdr = rwp[0];
    return got;
}
inline IData VL_VALUEPLUSARGS_INI(int rbits, const std::string& ld, SData& rdr) VL_MT_SAFE {
    VlWide<2> rwp;
    const IData got = VL_VALUEPLUSARGS_INW(rbits, ld, rwp);
    if (got) rdr = rwp[0];
    return got;
}
inline IData VL_VALUEPLUSARGS_INI(int rbits, const std::string& ld, IData& rdr) VL_MT_SAFE {
    VlWide<2> rwp;
    const IData got = VL_VALUEPLUSARGS_INW(rbits, ld, rwp);
    if (got) rdr = rwp[0];
    return got;
}
inline IData VL_VALUEPLUSARGS_INQ(int rbits, const std::string& ld, QData& rdr) VL_MT_SAFE {
    VlWide<2> rwp;
    const IData got = VL_VALUEPLUSARGS_INW(rbits, ld, rwp);
    if (got) rdr = VL_SET_QW(rwp);
    return got;
}
inline IData VL_VALUEPLUSARGS_INQ(int rbits, const std::string& ld, double& rdr) VL_MT_SAFE {
    VlWide<2> rwp;
    const IData got = VL_VALUEPLUSARGS_INW(rbits, ld, rwp);
    if (got) rdr = VL_CVT_D_Q(VL_SET_QW(rwp));
    return got;
}
extern IData VL_VALUEPLUSARGS_INN(int, const std::string& ld, std::string& rdr) VL_MT_SAFE;

uint64_t VL_MURMUR64_HASH(const char* key) VL_PURE;

//======================================================================

#endif  // Guard
