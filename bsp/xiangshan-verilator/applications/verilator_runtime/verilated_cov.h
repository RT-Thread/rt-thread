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
/// \brief Verilated coverage analysis support header
///
/// This must be included in user wrapper code that wants to save coverage
/// data.
///
/// It declares the VerilatedCovContext::write() which writes the collected
/// coverage information.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_COV_H_
#define VERILATOR_VERILATED_COV_H_

#include "verilatedos.h"

#include "verilated.h"

#include <iostream>
#include <sstream>
#include <string>

class VerilatedCovImp;

//=============================================================================
/// Insert an item for coverage analysis.
/// The first argument is a pointer to the count to be dumped.
/// The remaining arguments occur in pairs: A string key, and a value.
/// The value may be a string, or another type which will be auto-converted to a string.
///
/// Some typical keys:
///
///     filename        File the recording occurs in.  Defaults to __FILE__.
///     lineno          Line number the recording occurs in.  Defaults to __LINE__
///     column          Column number (or occurrence# for dup file/lines).  Defaults to undef.
///     hier            Hierarchical name.  Defaults to name()
///     type            Type of coverage.  Defaults to "user"
///                     Other types are 'block', 'fsm', 'toggle'.
///     comment         Description of the coverage event.  Should be set by the user.
///                     Comments for type==block: 'if', 'else', 'elsif', 'case'
///     thresh          Threshold to consider fully covered.
///                     If unspecified, downstream tools will determine it.
///     per_instance    If non-zero don't combine all hierarchies into one count
///
/// Example:
///
///     uint32_t m_cases[10];  // Storage for coverage data
///     constructor() {
///         // Initialize
///         for (int i = 0; i < 10; ++i) m_cases[i] = 0;
///         // Insert
///         for (int i = 0; i < 10; ++i)
///             VL_COVER_INSERT(covp, name(), &m_cases[i], "comment", "Coverage Case",
///                             "i", cvtToNumStr(i));
///     }

#define VL_COVER_INSERT(covcontextp, name, countp, ...) \
    do { \
        auto const ccontextp = covcontextp; \
        ccontextp->_inserti(countp); \
        ccontextp->_insertf(__FILE__, __LINE__); \
        ccontextp->_insertp("hier", name, __VA_ARGS__); \
    } while (false)

static inline void VL_COV_TOGGLE_CHG_ST_I(const int width, uint32_t* covp, const IData newData,
                                          const IData oldData) {
    const IData chgData = newData ^ oldData;
    for (int i = 0; i < width; ++i) {
        *(covp + 2 * i + ((newData >> i) & 1)) += (chgData >> i) & 1;
    }
}

static inline void VL_COV_TOGGLE_CHG_ST_Q(const int width, uint32_t* covp, const QData newData,
                                          const QData oldData) {
    const QData chgData = newData ^ oldData;
    for (int i = 0; i < width; ++i) {
        *(covp + 2 * i + ((newData >> i) & 1)) += (chgData >> i) & 1;
    }
}

static inline void VL_COV_TOGGLE_CHG_ST_W(const int width, uint32_t* covp, WDataInP newData,
                                          WDataInP oldData) {
    for (int i = 0; i < VL_WORDS_I(width); ++i) {
        const EData chgData = newData[i] ^ oldData[i];
        if (chgData) {
            for (int j = 0; j < width - i * VL_EDATASIZE; ++j) {
                *(covp + (i * VL_EDATASIZE + j) * 2 + ((newData[i] >> j) & 1))
                    += (chgData >> j) & 1;
            }
        }
    }
}

static inline void VL_COV_TOGGLE_CHG_MT_I(const int width, std::atomic<uint32_t>* covp,
                                          const IData newData, const IData oldData) VL_MT_SAFE {
    const IData chgData = newData ^ oldData;
    for (int i = 0; i < width; ++i) {
        if (VL_BITISSET_I(chgData, i)) {
            (covp + 2 * i + ((newData >> i) & 1))->fetch_add(1, std::memory_order_relaxed);
        }
    }
}

static inline void VL_COV_TOGGLE_CHG_MT_Q(const int width, std::atomic<uint32_t>* covp,
                                          const QData newData, const QData oldData) VL_MT_SAFE {
    const QData chgData = newData ^ oldData;
    for (int i = 0; i < width; ++i) {
        if (VL_BITISSET_Q(chgData, i)) {
            (covp + 2 * i + ((newData >> i) & 1))->fetch_add(1, std::memory_order_relaxed);
        }
    }
}

static inline void VL_COV_TOGGLE_CHG_MT_W(const int width, std::atomic<uint32_t>* covp,
                                          WDataInP newData, WDataInP oldData) VL_MT_SAFE {
    for (int i = 0; i < VL_WORDS_I(width); ++i) {
        const EData chgData = newData[i] ^ oldData[i];
        if (chgData) {
            for (int j = 0; j < width - i * VL_EDATASIZE; ++j) {
                if (VL_BITISSET_E(chgData, j)) {
                    (covp + (i * VL_EDATASIZE + j) * 2 + ((newData[i] >> j) & 1))
                        ->fetch_add(1, std::memory_order_relaxed);
                }
            }
        }
    }
}

//=============================================================================
//  VerilatedCov
/// Per-VerilatedContext coverage data class.
/// All public methods in this class are thread safe.
///
/// This structure is accessed and constructed on first access via
/// VerilatedContext::coveragep()

class VerilatedCovContext VL_NOT_FINAL : public VerilatedVirtualBase {
    VL_UNCOPYABLE(VerilatedCovContext);

public:
    // METHODS
    /// Return default filename, may override with +verilator+coverage+file
    std::string defaultFilename() VL_MT_SAFE;
    /// Make all data per_instance, overriding point's per_instance
    void forcePerInstance(bool flag) VL_MT_SAFE;
    /// Write all coverage data to a file
    void write() VL_MT_SAFE { write(defaultFilename()); }
    void write(const std::string& filename) VL_MT_SAFE;
    /// Clear coverage points (and call delete on all items)
    void clear() VL_MT_SAFE;
    /// Clear items not matching the provided string
    void clearNonMatch(const char* matchp) VL_MT_SAFE;
    /// Zero coverage points
    void zero() VL_MT_SAFE;

    // METHODS - public but Internal use only

    // Insert a coverage item
    // We accept from 1-30 key/value pairs, all as strings.
    // Call _insert1, followed by _insert2 and _insert3
    // Do not call directly; use VL_COVER_INSERT or higher level macros instead
    // _insert1: Remember item pointer with count.  (Not const, as may add zeroing function)
    void _inserti(uint32_t* itemp) VL_MT_SAFE;
    void _inserti(uint64_t* itemp) VL_MT_SAFE;
    // _insert2: Set default filename and line number
    void _insertf(const char* filename, int lineno) VL_MT_SAFE;
    // _insert3: Set parameters
    // We could have just the maximum argument version, but this compiles
    // much slower (nearly 2x) than having smaller versions also.  However
    // there's not much more gain in having a version for each number of args.
#ifndef DOXYGEN
#define K(n) const char* key##n
#define A(n) const char *key##n, const char *valp##n  // Argument list
#define D(n) const char *key##n = nullptr, const char *valp##n = nullptr  // Argument list
    void _insertp(D(0), D(1), D(2), D(3), D(4), D(5), D(6), D(7), D(8), D(9)) VL_MT_SAFE;
    void _insertp(A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), A(8), A(9), A(10), D(11), D(12),
                  D(13), D(14), D(15), D(16), D(17), D(18), D(19)) VL_MT_SAFE;
    void _insertp(A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), A(8), A(9), A(10), A(11), A(12),
                  A(13), A(14), A(15), A(16), A(17), A(18), A(19), A(20), D(21), D(22), D(23),
                  D(24), D(25), D(26), D(27), D(28), D(29)) VL_MT_SAFE;
    // Backward compatibility for Verilator
    void _insertp(A(0), A(1), K(2), int val2, K(3), int val3, K(4), const std::string& val4, A(5),
                  A(6), A(7)) VL_MT_SAFE;

#undef K
#undef A
#undef D
#endif  // DOXYGEN

protected:
    friend class VerilatedCovImp;
    // CONSTRUCTORS
    // Internal: Only made as part of VerilatedCovImp
    VerilatedCovContext() = default;
    ~VerilatedCovContext() override = default;

    // METHODS
    // Internal: access to implementation class
    VerilatedCovImp* impp() VL_MT_SAFE { return reinterpret_cast<VerilatedCovImp*>(this); }
};

//=============================================================================
//  VerilatedCov
/// Coverage global class.
///
/// Global class that accesses via current thread's context's
/// VerilatedCovContext.  This class is provided only for
/// backward-compatibility, use VerilatedContext::coveragep() instead.

#ifndef VL_NO_LEGACY
class VerilatedCov final {
    VL_UNCOPYABLE(VerilatedCov);

public:
    // METHODS
    /// Return default filename for the current thread
    static std::string defaultFilename() VL_MT_SAFE { return threadCovp()->defaultFilename(); }
    /// Write all coverage data to a file for the current thread
    static void write() VL_MT_SAFE { write(defaultFilename()); }
    static void write(const std::string& filename) VL_MT_SAFE { threadCovp()->write(filename); }
    /// Clear coverage points (and call delete on all items) for the current thread
    static void clear() VL_MT_SAFE { threadCovp()->clear(); }
    /// Clear items not matching the provided string for the current thread
    static void clearNonMatch(const char* matchp) VL_MT_SAFE {
        threadCovp()->clearNonMatch(matchp);
    }
    /// Zero coverage points for the current thread
    static void zero() VL_MT_SAFE { threadCovp()->zero(); }

private:
    // Current thread's coverage structure
    static VerilatedCovContext* threadCovp() VL_MT_SAFE;
};
#endif  // VL_NO_LEGACY

#endif  // Guard
