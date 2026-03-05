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
/// \brief Verilated coverage analysis implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use coverage.
///
/// Use "verilator --coverage" to add this to the Makefile for the linker.
///
//=============================================================================

#include "verilatedos.h"

#include "verilated_cov.h"

#include "verilated.h"
#include "verilated_cov_key.h"

#include <deque>
#include <fstream>
#include <map>
#include <utility>

//=============================================================================
// VerilatedCovConst
// Implementation constants

struct VerilatedCovConst VL_NOT_FINAL {
    // TYPES
    enum { MAX_KEYS = 33 };  // Maximum user arguments + filename+lineno
    enum { KEY_UNDEF = 0 };  // Magic key # for unspecified values
};

//=============================================================================
// VerilatedCovImpItem
// Implementation class for a VerilatedCov item

class VerilatedCovImpItem VL_NOT_FINAL {
public:  // But only local to this file
    // MEMBERS
    int m_keys[VerilatedCovConst::MAX_KEYS];  // Key
    int m_vals[VerilatedCovConst::MAX_KEYS];  // Value for specified key
    // CONSTRUCTORS
    // Derived classes should call zero() in their constructor
    VerilatedCovImpItem() {
        for (int i = 0; i < VerilatedCovConst::MAX_KEYS; ++i) {
            m_keys[i] = VerilatedCovConst::KEY_UNDEF;
            m_vals[i] = 0;
        }
    }
    virtual ~VerilatedCovImpItem() = default;
    virtual uint64_t count() const = 0;
    virtual void zero() const = 0;
};

//=============================================================================
// VerilatedCoverItem templated for a specific class
// Creates a new coverage item for the specified type.
// This isn't in the header file for auto-magic conversion because it
// inlines to too much code and makes compilation too slow.

template <typename T>
class VerilatedCoverItemSpec final : public VerilatedCovImpItem {
private:
    // MEMBERS
    T* m_countp;  // Count value
public:
    // METHODS
    // cppcheck-suppress truncLongCastReturn
    uint64_t count() const override { return *m_countp; }
    void zero() const override { *m_countp = 0; }
    // CONSTRUCTORS
    // cppcheck-suppress noExplicitConstructor
    explicit VerilatedCoverItemSpec(T* countp)
        : m_countp{countp} {
        *m_countp = 0;
    }
    ~VerilatedCoverItemSpec() override = default;
};

//=============================================================================
// VerilatedCovImp
//
// Implementation class for VerilatedCovContext.  See that class for
// public method information.  All value and keys are indexed into a
// unique number.  Thus we can greatly reduce the storage requirements for
// otherwise identical keys.

class VerilatedCovImp final : public VerilatedCovContext {
private:
    // TYPES
    using ValueIndexMap = std::map<const std::string, int>;
    using IndexValueMap = std::map<int, std::string>;
    using ItemList = std::deque<VerilatedCovImpItem*>;

    // MEMBERS
    VerilatedContext* const m_contextp;  // Context VerilatedCovImp is pointed-to by
    mutable VerilatedMutex m_mutex;  // Protects all members
    ValueIndexMap m_valueIndexes VL_GUARDED_BY(m_mutex);  // Unique arbitrary value for values
    IndexValueMap m_indexValues VL_GUARDED_BY(m_mutex);  // Unique arbitrary value for keys
    ItemList m_items VL_GUARDED_BY(m_mutex);  // List of all items
    int m_nextIndex VL_GUARDED_BY(m_mutex)
        = (VerilatedCovConst::KEY_UNDEF + 1);  // Next insert value

    VerilatedCovImpItem* m_insertp VL_GUARDED_BY(m_mutex) = nullptr;  // Item about to insert
    const char* m_insertFilenamep VL_GUARDED_BY(m_mutex) = nullptr;  // Filename about to insert
    int m_insertLineno VL_GUARDED_BY(m_mutex) = 0;  // Line number about to insert
    bool m_forcePerInstance VL_GUARDED_BY(m_mutex) = false;  // Force per_instance

public:
    // CONSTRUCTORS
    explicit VerilatedCovImp(VerilatedContext* contextp)
        : m_contextp{contextp} {}
    VL_UNCOPYABLE(VerilatedCovImp);

protected:
    friend class VerilatedCovContext;
    ~VerilatedCovImp() override { clearGuts(); }

private:
    // PRIVATE METHODS
    int valueIndex(const std::string& value) VL_REQUIRES(m_mutex) {
        const auto iter = m_valueIndexes.find(value);
        if (iter != m_valueIndexes.end()) return iter->second;
        ++m_nextIndex;
        assert(m_nextIndex > 0);  // Didn't rollover
        m_valueIndexes.emplace(value, m_nextIndex);
        m_indexValues.emplace(m_nextIndex, value);
        return m_nextIndex;
    }
    static std::string dequote(const std::string& text) VL_PURE {
        // Quote any special characters
        std::string rtn;
        for (const char* pos = text.c_str(); *pos; ++pos) {
            if (!std::isprint(*pos) || *pos == '%' || *pos == '"') {
                constexpr size_t LEN_MAX_HEX = 20;
                char hex[LEN_MAX_HEX];
                VL_SNPRINTF(hex, LEN_MAX_HEX, "%%%02X", pos[0]);
                rtn += hex;
            } else {
                rtn += *pos;
            }
        }
        return rtn;
    }
    static bool legalKey(const std::string& key) VL_PURE {
        // Because we compress long keys to a single letter, and
        // don't want applications to either get confused if they use
        // a letter differently, nor want them to rely on our compression...
        // (Considered using numeric keys, but will remain back compatible.)
        if (key.length() < 2) return false;
        if (key.length() == 2 && std::isdigit(key[1])) return false;
        return true;
    }
    static std::string keyValueFormatter(const std::string& key,
                                         const std::string& value) VL_PURE {
        std::string name;
        if (key.length() == 1 && std::isalpha(key[0])) {
            name += "\001"s + key;
        } else {
            name += "\001"s + dequote(key);
        }
        name += "\002"s + dequote(value);
        return name;
    }
    static std::string combineHier(const std::string& old, const std::string& add) VL_PURE {
        // (foo.a.x, foo.b.x) => foo.*.x
        // (foo.a.x, foo.b.y) => foo.*
        // (foo.a.x, foo.b)   => foo.*
        if (old == add) return add;
        if (old.empty()) return add;
        if (add.empty()) return old;

        const char* const a = old.c_str();
        const char* const b = add.c_str();

        // Scan forward to first mismatch
        const char* apre = a;
        const char* bpre = b;
        while (*apre == *bpre) {
            ++apre;
            ++bpre;
        }

        // We used to backup and split on only .'s but it seems better to be verbose
        // and not assume . is the separator
        const size_t prefix_len = apre - a;
        const std::string prefix = std::string{a, prefix_len};

        // Scan backward to last mismatch
        const char* apost = a + std::strlen(a) - 1;
        const char* bpost = b + std::strlen(b) - 1;
        while (*apost == *bpost && apost > apre && bpost > bpre) {
            --apost;
            --bpost;
        }

        // Forward to . so we have a whole word
        const std::string suffix = *bpost ? std::string{bpost + 1} : "";

        std::string result = prefix + "*" + suffix;

        // std::cout << "\nch pre=" << prefix << "  s=" << suffix << "\nch a="
        // << old << "\nch b=" << add << "\ncho=" << result << "\n";
        return result;
    }
    bool itemMatchesString(VerilatedCovImpItem* itemp, const std::string& match)
        VL_REQUIRES(m_mutex) {
        for (int i = 0; i < VerilatedCovConst::MAX_KEYS; ++i) {
            if (itemp->m_keys[i] != VerilatedCovConst::KEY_UNDEF) {
                // We don't compare keys, only values
                const std::string val = m_indexValues[itemp->m_vals[i]];
                if (std::string::npos != val.find(match)) {  // Found
                    return true;
                }
            }
        }
        return false;
    }
    static void selftest() VL_MT_SAFE {
        // Little selftest
#define SELF_CHECK(got, exp) \
    do { \
        if ((got) != (exp)) VL_FATAL_MT(__FILE__, __LINE__, "", "selftest"); \
    } while (0)
        SELF_CHECK(combineHier("a.b.c", "a.b.c"), "a.b.c");
        SELF_CHECK(combineHier("a.b.c", "a.b"), "a.b*");
        SELF_CHECK(combineHier("a.x.c", "a.y.c"), "a.*.c");
        SELF_CHECK(combineHier("a.z.z.z.c", "a.b.c"), "a.*.c");
        SELF_CHECK(combineHier("z", "a"), "*");
        SELF_CHECK(combineHier("q.a", "q.b"), "q.*");
        SELF_CHECK(combineHier("q.za", "q.zb"), "q.z*");
        SELF_CHECK(combineHier("1.2.3.a", "9.8.7.a"), "*.a");
#undef SELF_CHECK
    }
    void clearGuts() VL_REQUIRES(m_mutex) {
        for (const auto& itemp : m_items) VL_DO_DANGLING(delete itemp, itemp);
        m_items.clear();
        m_indexValues.clear();
        m_valueIndexes.clear();
        m_nextIndex = VerilatedCovConst::KEY_UNDEF + 1;
    }

public:
    // PUBLIC METHODS
    // cppcheck-suppress duplInheritedMember
    std::string defaultFilename() VL_MT_SAFE { return m_contextp->coverageFilename(); }
    // cppcheck-suppress duplInheritedMember
    void forcePerInstance(const bool flag) VL_MT_SAFE_EXCLUDES(m_mutex) {
        Verilated::quiesce();
        const VerilatedLockGuard lock{m_mutex};
        m_forcePerInstance = flag;
    }
    // cppcheck-suppress duplInheritedMember
    void clear() VL_MT_SAFE_EXCLUDES(m_mutex) {
        Verilated::quiesce();
        const VerilatedLockGuard lock{m_mutex};
        clearGuts();
    }
    // cppcheck-suppress duplInheritedMember
    void clearNonMatch(const char* const matchp) VL_MT_SAFE_EXCLUDES(m_mutex) {
        Verilated::quiesce();
        const VerilatedLockGuard lock{m_mutex};
        if (matchp && matchp[0]) {
            ItemList newlist;
            for (const auto& itemp : m_items) {
                if (!itemMatchesString(itemp, matchp)) {
                    VL_DO_DANGLING(delete itemp, itemp);
                } else {
                    newlist.push_back(itemp);
                }
            }
            m_items = newlist;
        }
    }
    // cppcheck-suppress duplInheritedMember
    void zero() VL_MT_SAFE_EXCLUDES(m_mutex) {
        Verilated::quiesce();
        const VerilatedLockGuard lock{m_mutex};
        for (const VerilatedCovImpItem* const itemp : m_items) itemp->zero();
    }

    // We assume there's always call to i/f/p in that order
    void inserti(VerilatedCovImpItem* itemp) VL_MT_SAFE_EXCLUDES(m_mutex) {
        const VerilatedLockGuard lock{m_mutex};
        assert(!m_insertp);
        m_insertp = itemp;
    }
    void insertf(const char* const filenamep, const int lineno) VL_MT_SAFE_EXCLUDES(m_mutex) {
        const VerilatedLockGuard lock{m_mutex};
        m_insertFilenamep = filenamep;
        m_insertLineno = lineno;
    }
    void insertp(const char* ckeyps[VerilatedCovConst::MAX_KEYS],
                 const char* valps[VerilatedCovConst::MAX_KEYS]) VL_MT_SAFE_EXCLUDES(m_mutex) {
        const VerilatedLockGuard lock{m_mutex};
        assert(m_insertp);
        // First two key/vals are filename
        ckeyps[0] = "filename";
        valps[0] = m_insertFilenamep;
        const std::string linestr = std::to_string(m_insertLineno);
        ckeyps[1] = "lineno";
        // cppcheck-suppress autoVariables  // Used only below for insert
        valps[1] = linestr.c_str();
        // Default page if not specified
        const char* fnstartp = m_insertFilenamep;
        while (const char* foundp = std::strchr(fnstartp, '/')) fnstartp = foundp + 1;
        const char* fnendp = fnstartp;
        for (; *fnendp && *fnendp != '.'; ++fnendp) {}
        const size_t page_len = fnendp - fnstartp;
        const std::string page_default = "sp_user/" + std::string{fnstartp, page_len};
        ckeyps[2] = "page";
        // cppcheck-suppress autoVariables  // Used only below for insert
        valps[2] = page_default.c_str();

        // Keys -> strings
        std::array<std::string, VerilatedCovConst::MAX_KEYS> keys;
        for (int i = 0; i < VerilatedCovConst::MAX_KEYS; ++i) {
            if (ckeyps[i] && ckeyps[i][0]) keys[i] = ckeyps[i];
        }
        // Ignore empty keys
        for (int i = 0; i < VerilatedCovConst::MAX_KEYS; ++i) {
            if (!keys[i].empty()) {
                for (int j = i + 1; j < VerilatedCovConst::MAX_KEYS; ++j) {
                    if (keys[i] == keys[j]) {  // Duplicate key.  Keep the last one
                        keys[i] = "";
                        break;
                    }
                }
            }
        }
        // Insert the values
        int addKeynum = 0;
        for (int i = 0; i < VerilatedCovConst::MAX_KEYS; ++i) {
            const std::string key = keys[i];
            if (!keys[i].empty()) {
                const std::string val = valps[i];
                // std::cout << "   " << __FUNCTION__ << "  " << key << " = " << val << "\n";
                m_insertp->m_keys[addKeynum] = valueIndex(key);
                m_insertp->m_vals[addKeynum] = valueIndex(val);
                ++addKeynum;
                if (VL_UNCOVERABLE(!legalKey(key))) {
                    const std::string msg
                        = ("%Error: Coverage keys of one character, or letter+digit are illegal: "
                           + key);  // LCOV_EXCL_LINE
                    VL_FATAL_MT("", 0, "", msg.c_str());
                }
            }
        }
        m_items.push_back(m_insertp);
        // Prepare for next
        m_insertp = nullptr;
    }

    // cppcheck-suppress duplInheritedMember
    void write(const std::string& filename) VL_MT_SAFE_EXCLUDES(m_mutex) {
        Verilated::quiesce();
        const VerilatedLockGuard lock{m_mutex};
        selftest();

        std::ofstream os{filename};
        if (os.fail()) {
            const std::string msg = "%Error: Can't write '"s + filename + "'";
            VL_FATAL_MT("", 0, "", msg.c_str());
            return;
        }
        os << "# SystemC::Coverage-3\n";

        // Build list of events; totalize if collapsing hierarchy
        std::map<const std::string, std::pair<std::string, uint64_t>> eventCounts;
        for (const auto& itemp : m_items) {
            std::string name;
            std::string hier;
            bool per_instance = false;
            if (m_forcePerInstance) per_instance = true;

            for (int i = 0; i < VerilatedCovConst::MAX_KEYS; ++i) {
                if (itemp->m_keys[i] != VerilatedCovConst::KEY_UNDEF) {
                    const std::string key
                        = VerilatedCovKey::shortKey(m_indexValues[itemp->m_keys[i]]);
                    const std::string val = m_indexValues[itemp->m_vals[i]];
                    if (key == VL_CIK_PER_INSTANCE) {
                        if (val != "0") per_instance = true;
                    }
                    if (key == VL_CIK_HIER) {
                        hier = val;
                    } else {
                        // Print it
                        if (key == "page") {
                            const std::string type = val.substr(2, val.find('/') - 2);
                            name += keyValueFormatter(VL_CIK_TYPE, type);
                        }
                        name += keyValueFormatter(key, val);
                    }
                }
            }
            if (per_instance) {  // Not collapsing hierarchies
                name += keyValueFormatter(VL_CIK_HIER, hier);
                hier = "";
            }

            // Group versus point labels don't matter here, downstream
            // deals with it.  Seems bad for sizing though and doesn't
            // allow easy addition of new group codes (would be
            // inefficient)

            // Find or insert the named event
            const auto cit = eventCounts.find(name);
            if (cit != eventCounts.end()) {
                const std::string& oldhier = cit->second.first;
                cit->second.second += itemp->count();
                cit->second.first = combineHier(oldhier, hier);
            } else {
                eventCounts.emplace(name, std::make_pair(hier, itemp->count()));
            }
        }

        // Output body
        for (const auto& i : eventCounts) {
            os << "C '" << std::dec;
            os << i.first;
            if (!i.second.first.empty()) os << keyValueFormatter(VL_CIK_HIER, i.second.first);
            os << "' " << i.second.second;
            os << '\n';
        }
    }
};

//=============================================================================
// VerilatedCovContext

std::string VerilatedCovContext::defaultFilename() VL_MT_SAFE { return impp()->defaultFilename(); }
void VerilatedCovContext::forcePerInstance(bool flag) VL_MT_SAFE {
    impp()->forcePerInstance(flag);
}
void VerilatedCovContext::clear() VL_MT_SAFE { impp()->clear(); }
void VerilatedCovContext::clearNonMatch(const char* matchp) VL_MT_SAFE {
    impp()->clearNonMatch(matchp);
}
void VerilatedCovContext::zero() VL_MT_SAFE { impp()->zero(); }
void VerilatedCovContext::write(const std::string& filename) VL_MT_SAFE {
    impp()->write(filename);
}
void VerilatedCovContext::_inserti(uint32_t* itemp) VL_MT_SAFE {
    impp()->inserti(new VerilatedCoverItemSpec<uint32_t>{itemp});
}
void VerilatedCovContext::_inserti(uint64_t* itemp) VL_MT_SAFE {
    impp()->inserti(new VerilatedCoverItemSpec<uint64_t>{itemp});
}
void VerilatedCovContext::_insertf(const char* filename, int lineno) VL_MT_SAFE {
    impp()->insertf(filename, lineno);
}

#ifndef DOXYGEN
#define K(n) const char* key##n
#define A(n) const char *key##n, const char *valp##n  // Argument list
#define C(n) key##n, valp##n  // Calling argument list
#define N(n) "", ""  // Null argument list
void VerilatedCovContext::_insertp(A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), A(8), A(9),
                                   A(10), A(11), A(12), A(13), A(14), A(15), A(16), A(17), A(18),
                                   A(19), A(20), A(21), A(22), A(23), A(24), A(25), A(26), A(27),
                                   A(28), A(29)) VL_MT_SAFE {
    const char* keyps[VerilatedCovConst::MAX_KEYS]
        = {nullptr, nullptr, nullptr,  // filename,lineno,page
           key0,    key1,    key2,    key3,  key4,  key5,  key6,  key7,  key8,  key9,
           key10,   key11,   key12,   key13, key14, key15, key16, key17, key18, key19,
           key20,   key21,   key22,   key23, key24, key25, key26, key27, key28, key29};
    const char* valps[VerilatedCovConst::MAX_KEYS]
        = {nullptr, nullptr, nullptr,  // filename,lineno,page
           valp0,   valp1,   valp2,   valp3,  valp4,  valp5,  valp6,  valp7,  valp8,  valp9,
           valp10,  valp11,  valp12,  valp13, valp14, valp15, valp16, valp17, valp18, valp19,
           valp20,  valp21,  valp22,  valp23, valp24, valp25, valp26, valp27, valp28, valp29};
    impp()->insertp(keyps, valps);
}

// And versions with fewer arguments  (oh for a language with named parameters!)
void VerilatedCovContext::_insertp(A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), A(8),
                                   A(9)) VL_MT_SAFE {
    _insertp(C(0), C(1), C(2), C(3), C(4), C(5), C(6), C(7), C(8), C(9), N(10), N(11), N(12),
             N(13), N(14), N(15), N(16), N(17), N(18), N(19), N(20), N(21), N(22), N(23), N(24),
             N(25), N(26), N(27), N(28), N(29));
}
void VerilatedCovContext::_insertp(A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), A(8), A(9),
                                   A(10), A(11), A(12), A(13), A(14), A(15), A(16), A(17), A(18),
                                   A(19)) VL_MT_SAFE {
    _insertp(C(0), C(1), C(2), C(3), C(4), C(5), C(6), C(7), C(8), C(9), C(10), C(11), C(12),
             C(13), C(14), C(15), C(16), C(17), C(18), C(19), N(20), N(21), N(22), N(23), N(24),
             N(25), N(26), N(27), N(28), N(29));
}
// Backward compatibility for Verilator
void VerilatedCovContext::_insertp(A(0), A(1), K(2), int val2, K(3), int val3, K(4),
                                   const std::string& val4, A(5), A(6), A(7)) VL_MT_SAFE {
    const std::string val2str = std::to_string(val2);
    const std::string val3str = std::to_string(val3);
    _insertp(C(0), C(1), key2, val2str.c_str(), key3, val3str.c_str(), key4, val4.c_str(), C(5),
             C(6), C(7), N(8), N(9), N(10), N(11), N(12), N(13), N(14), N(15), N(16), N(17), N(18),
             N(19), N(20), N(21), N(22), N(23), N(24), N(25), N(26), N(27), N(28), N(29));
}
#undef A
#undef C
#undef N
#undef K

#endif  // DOXYGEN

//=============================================================================
// VerilatedCov

#ifndef VL_NO_LEGACY
VerilatedCovContext* VerilatedCov::threadCovp() VL_MT_SAFE {
    return Verilated::threadContextp()->coveragep();
}
#endif

//=============================================================================
// VerilatedContext

VerilatedCovContext* VerilatedContext::coveragep() VL_MT_SAFE {
    static VerilatedMutex s_mutex;
    // cppcheck-suppress identicalInnerCondition
    if (VL_UNLIKELY(!m_coveragep)) {
        const VerilatedLockGuard lock{s_mutex};
        // cppcheck-suppress identicalInnerCondition
        if (VL_LIKELY(!m_coveragep)) {  // LCOV_EXCL_LINE // Not redundant, prevents race
            m_coveragep.reset(new VerilatedCovImp{this});
        }
    }
    return reinterpret_cast<VerilatedCovContext*>(m_coveragep.get());
}
