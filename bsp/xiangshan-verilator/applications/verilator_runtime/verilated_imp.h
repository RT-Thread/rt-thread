// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
//
// Code available from: https://verilator.org
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2009-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//=========================================================================
///
/// \file
/// \brief Verilated implementation Header, only for verilated.cpp internals.
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use by the Verilated libraries.
///
//=========================================================================

#ifndef VERILATOR_VERILATED_IMP_H_
#define VERILATOR_VERILATED_IMP_H_

// clang-format off
#if !defined(VERILATOR_VERILATED_CPP_) && !defined(VERILATOR_VERILATED_DPI_CPP_) \
    && !defined(VERILATOR_VERILATED_VPI_CPP_) && !defined(VERILATOR_VERILATED_SAVE_CPP_)
# error "verilated_imp.h only to be included by verilated*.cpp internals"
#endif

#include "verilatedos.h"
#include "verilated.h"
#include "verilated_syms.h"

#include <algorithm>
#include <deque>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <queue>
// clang-format on

class VerilatedScope;

//======================================================================
// Threaded message passing

// Message, enqueued on an mtask, and consumed on the main eval thread
class VerilatedMsg final {
public:
    // TYPES
    struct Cmp final {
        bool operator()(const VerilatedMsg& a, const VerilatedMsg& b) const {
            return a.mtaskId() < b.mtaskId();
        }
    };

private:
    // MEMBERS
    uint32_t m_mtaskId;  // MTask that did enqueue
    std::function<void()> m_cb;  // Lambda to execute when message received
public:
    // CONSTRUCTORS
    explicit VerilatedMsg(const std::function<void()>& cb)
        : m_mtaskId{Verilated::mtaskId()}
        , m_cb{cb} {}
    ~VerilatedMsg() = default;
    VerilatedMsg(const VerilatedMsg&) = default;
    VerilatedMsg(VerilatedMsg&&) = default;
    VerilatedMsg& operator=(const VerilatedMsg&) = default;
    VerilatedMsg& operator=(VerilatedMsg&&) = default;
    // METHODS
    uint32_t mtaskId() const { return m_mtaskId; }
    // Execute the lambda function
    void run() const { m_cb(); }
};

// Each thread has a queue it pushes to
// This assumes no thread starts pushing the next tick until the previous has drained.
// If more aggressiveness is needed, a double-buffered scheme might work well.
class VerilatedEvalMsgQueue final {
    using VerilatedThreadQueue = std::multiset<VerilatedMsg, VerilatedMsg::Cmp>;

    std::atomic<uint64_t> m_depth;  // Current depth of queue (see comments below)

    mutable VerilatedMutex m_mutex;  // Mutex protecting queue
    VerilatedThreadQueue m_queue VL_GUARDED_BY(m_mutex);  // Message queue
public:
    // CONSTRUCTORS
    VerilatedEvalMsgQueue()
        : m_depth{0} {
        assert(atomic_is_lock_free(&m_depth));
    }
    ~VerilatedEvalMsgQueue() = default;

private:
    VL_UNCOPYABLE(VerilatedEvalMsgQueue);

public:
    // METHODS
    // Add message to queue (called by producer)
    void post(const VerilatedMsg& msg) VL_MT_SAFE_EXCLUDES(m_mutex) {
        const VerilatedLockGuard lock{m_mutex};
        m_queue.insert(msg);  // Pass by value to copy the message into queue
        ++m_depth;
    }
    // Service queue until completion (called by consumer)
    void process() VL_MT_SAFE_EXCLUDES(m_mutex) {
        // Tracking m_depth is redundant to e.g. getting the mutex and looking at queue size,
        // but on the reader side it's 4x faster to test an atomic then getting a mutex
        while (m_depth) {
            // Wait for a message to be added to the queue
            // We don't use unique_lock as want to unlock with the message copy still in scope
            m_mutex.lock();
            assert(!m_queue.empty());  // Otherwise m_depth is wrong
            // Unfortunately to release the lock we need to copy the message
            // (Or have the message be a pointer, but then new/delete cost on each message)
            // We assume messages are small, so copy
            const auto it = m_queue.begin();
            const VerilatedMsg msg = *(it);
            m_queue.erase(it);
            m_mutex.unlock();
            --m_depth;  // Ok if outside critical section as only this code checks the value
            {
                VL_DEBUG_IF(VL_DBG_MSGF("Executing callback from mtaskId=%d\n", msg.mtaskId()););
                msg.run();
            }
        }
    }
};

// Each thread has a local queue to build up messages until the end of the eval() call
class VerilatedThreadMsgQueue final {
    std::queue<VerilatedMsg> m_queue;

public:
    // CONSTRUCTORS
    VerilatedThreadMsgQueue() = default;
    ~VerilatedThreadMsgQueue() = default;
    // The only call of destructor with a non-empty queue is a fatal error.
    // So this does not flush the queue, as the destination queue is not known to this class.

private:
    VL_UNCOPYABLE(VerilatedThreadMsgQueue);
    // METHODS
    static VerilatedThreadMsgQueue& threadton() VL_MT_SAFE {
        static thread_local VerilatedThreadMsgQueue t_s;
        return t_s;
    }

public:
    // Add message to queue, called by producer
    static void post(const VerilatedMsg& msg) VL_MT_SAFE {
        // Handle calls to threaded routines outside
        // of any mtask -- if an initial block calls $finish, say.
        if (Verilated::mtaskId() == 0) {
            // No queueing, just do the action immediately
            msg.run();
        } else {
            Verilated::endOfEvalReqdInc();
            threadton().m_queue.push(msg);  // Pass by value to copy the message into queue
        }
    }
    // Push all messages to the eval's queue
    static void flush(VerilatedEvalMsgQueue* evalMsgQp) VL_MT_SAFE {
        while (!threadton().m_queue.empty()) {
            evalMsgQp->post(threadton().m_queue.front());
            threadton().m_queue.pop();
            Verilated::endOfEvalReqdDec();
        }
    }
};

// FILE* list constructed from a file-descriptor
class VerilatedFpList final {
    FILE* m_fp[31] = {};
    std::size_t m_sz = 0;

public:
    using const_iterator = FILE* const*;
    explicit VerilatedFpList() = default;
    const_iterator begin() const { return m_fp; }
    const_iterator end() const { return m_fp + m_sz; }
    std::size_t size() const { return m_sz; }
    static std::size_t capacity() { return 31; }
    void push_back(FILE* fd) {
        if (VL_LIKELY(size() < capacity())) m_fp[m_sz++] = fd;
    }
};

//======================================================================
// VerilatedContextImpData

// Class for hidden implementation members inside VerilatedContext
// Avoids needing std::unordered_map inside verilated.h
class VerilatedContextImpData final {
    friend class VerilatedContext;
    friend class VerilatedContextImp;

protected:
    // Map of <scope_name, scope pointer>
    // Used by scopeInsert, scopeFind, scopeErase, scopeNameMap
    mutable VerilatedMutex m_nameMutex;  // Protect m_nameMap
    VerilatedScopeNameMap m_nameMap VL_GUARDED_BY(m_nameMutex);
};

//======================================================================
// VerilatedContextImp
// Class to "add" implementation-only methods to VerilatedContext

class VerilatedContextImp final : VerilatedContext {
    friend class VerilatedContext;

    // MEMBERS - non-static not allowed, use only VerilatedContext
    // Select initial value of otherwise uninitialized signals.
    // Internal note: Globals may multi-construct, see verilated.cpp top.

    // Medium speed, so uses singleton accessing
    struct Statics final {
        VerilatedMutex s_randMutex;  // Mutex protecting s_randSeedEpoch
        // Number incrementing on each reseed, 0=illegal
        int s_randSeedEpoch = 1;  // Reads ok, wish had a VL_WRITE_GUARDED_BY(s_randMutex)
    };
    static Statics& s() VL_MT_SAFE {
        static Statics s_s;
        return s_s;
    }

public:  // But only for verilated*.cpp
    // CONSTRUCTORS - no data can live here, use only VerilatedContext
    VerilatedContextImp() = delete;
    ~VerilatedContextImp() = delete;

    // METHODS - extending into VerilatedContext, call via impp()->

    // Random seed handling
    uint64_t randSeedDefault64() const VL_MT_SAFE;
    static uint32_t randSeedEpoch() VL_MT_SAFE { return s().s_randSeedEpoch; }

    // METHODS - timeformat
    int timeFormatUnits() const VL_MT_SAFE {
        if (m_s.m_timeFormatUnits == VerilatedContext::Serialized::UNITS_NONE)
            return timeprecision();
        return m_s.m_timeFormatUnits;
    }
    void timeFormatUnits(int value) VL_MT_SAFE { m_s.m_timeFormatUnits = value; }
    int timeFormatPrecision() const VL_MT_SAFE { return m_s.m_timeFormatPrecision; }
    void timeFormatPrecision(int value) VL_MT_SAFE { m_s.m_timeFormatPrecision = value; }
    int timeFormatWidth() const VL_MT_SAFE { return m_s.m_timeFormatWidth; }
    void timeFormatWidth(int value) VL_MT_SAFE { m_s.m_timeFormatWidth = value; }
    std::string timeFormatSuffix() const VL_MT_SAFE_EXCLUDES(m_timeDumpMutex) {
        const VerilatedLockGuard lock{m_timeDumpMutex};
        return m_timeFormatSuffix;
    }
    void timeFormatSuffix(const std::string& value) VL_MT_SAFE_EXCLUDES(m_timeDumpMutex) {
        const VerilatedLockGuard lock{m_timeDumpMutex};
        m_timeFormatSuffix = value;
    }

    // METHODS - arguments
    std::string argPlusMatch(const char* prefixp) VL_MT_SAFE_EXCLUDES(m_argMutex);
    std::pair<int, char**> argc_argv() VL_MT_SAFE_EXCLUDES(m_argMutex);

    // METHODS - scope name - INTERNAL only for verilated*.cpp
    void scopeInsert(const VerilatedScope* scopep) VL_MT_SAFE;
    void scopeErase(const VerilatedScope* scopep) VL_MT_SAFE;

    // METHODS - file IO - INTERNAL only for verilated*.cpp

    IData fdNewMcd(const char* filenamep) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        if (m_fdFreeMct.empty()) return 0;
        const IData idx = m_fdFreeMct.back();
        m_fdFreeMct.pop_back();
        m_fdps[idx] = std::fopen(filenamep, "w");
        if (VL_UNLIKELY(!m_fdps[idx])) return 0;
        return (1 << idx);
    }
    IData fdNew(const char* filenamep, const char* modep) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        FILE* const fp = std::fopen(filenamep, modep);
        if (VL_UNLIKELY(!fp)) return 0;
        // Bit 31 indicates it's a descriptor not a MCD
        const VerilatedLockGuard lock{m_fdMutex};
        if (m_fdFree.empty()) {
            // Need to create more space in m_fdps and m_fdFree
            const std::size_t start = std::max<std::size_t>(31UL + 1UL + 3UL, m_fdps.size());
            const std::size_t excess = 10;
            m_fdps.resize(start + excess);
            std::fill(m_fdps.begin() + start, m_fdps.end(), static_cast<FILE*>(nullptr));
            m_fdFree.resize(excess);
            for (std::size_t i = 0, id = start; i < m_fdFree.size(); ++i, ++id) {
                m_fdFree[i] = static_cast<IData>(id);
            }
        }
        const IData idx = m_fdFree.back();
        m_fdFree.pop_back();
        m_fdps[idx] = fp;
        return (idx | (1UL << 31));  // bit 31 indicates not MCD
    }
    void fdFlush(IData fdi) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        const VerilatedFpList fdlist = fdToFpList(fdi);
        for (const auto& i : fdlist) std::fflush(i);
    }
    IData fdSeek(IData fdi, IData offset, IData origin) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        const VerilatedFpList fdlist = fdToFpList(fdi);
        if (VL_UNLIKELY(fdlist.size() != 1)) return ~0U;  // -1
        return static_cast<IData>(
            std::fseek(*fdlist.begin(), static_cast<long>(offset), static_cast<int>(origin)));
    }
    IData fdTell(IData fdi) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        const VerilatedFpList fdlist = fdToFpList(fdi);
        if (VL_UNLIKELY(fdlist.size() != 1)) return ~0U;  // -1
        return static_cast<IData>(std::ftell(*fdlist.begin()));
    }
    void fdWrite(IData fdi, const std::string& output) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        const VerilatedFpList fdlist = fdToFpList(fdi);
        for (const auto& i : fdlist) {
            if (VL_UNLIKELY(!i)) continue;
            (void)fwrite(output.c_str(), 1, output.size(), i);
        }
    }
    void fdClose(IData fdi) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        if (VL_BITISSET_I(fdi, 31)) {
            // Non-MCD case
            const IData idx = VL_MASK_I(31) & fdi;
            if (VL_UNLIKELY(idx >= m_fdps.size())) return;
            if (VL_UNLIKELY(idx <= 2)) return;  // stdout/stdin/stderr
            if (VL_UNLIKELY(!m_fdps[idx])) return;  // Already free
            std::fclose(m_fdps[idx]);
            m_fdps[idx] = nullptr;
            m_fdFree.push_back(idx);
        } else {
            // MCD case
            // Starts at 1 to skip stdout
            fdi >>= 1;
            for (int i = 1; (fdi != 0) && (i < 31); i++, fdi >>= 1) {
                if (fdi & VL_MASK_I(1)) {
                    std::fclose(m_fdps[i]);
                    m_fdps[i] = nullptr;
                    m_fdFreeMct.push_back(i);
                }
            }
        }
    }
    FILE* fdToFp(IData fdi) VL_MT_SAFE_EXCLUDES(m_fdMutex) {
        const VerilatedLockGuard lock{m_fdMutex};
        const VerilatedFpList fdlist = fdToFpList(fdi);
        if (VL_UNLIKELY(fdlist.size() != 1)) return nullptr;
        return *fdlist.begin();
    }

private:
    VerilatedFpList fdToFpList(IData fdi) VL_REQUIRES(m_fdMutex) {
        VerilatedFpList fp;
        // cppverilator-suppress integerOverflow shiftTooManyBitsSigned
        if (VL_BITISSET_I(fdi, 31)) {
            // Non-MCD case
            const IData idx = fdi & VL_MASK_I(31);
            switch (idx) {
            case 0: fp.push_back(stdin); break;
            case 1: fp.push_back(stdout); break;
            case 2: fp.push_back(stderr); break;
            default:
                if (VL_LIKELY(idx < m_fdps.size())) fp.push_back(m_fdps[idx]);
                break;
            }
        } else {
            // MCD Case
            if (fdi & 1) fp.push_back(stdout);
            fdi >>= 1;
            for (size_t i = 1; (fdi != 0) && (i < fp.capacity()); ++i, fdi >>= 1) {
                if (fdi & VL_MASK_I(1)) fp.push_back(m_fdps[i]);
            }
        }
        return fp;
    }

protected:
    // METHODS - protected
    void commandArgsGuts(int argc, const char** argv) VL_MT_SAFE_EXCLUDES(m_argMutex);
    void commandArgsAddGutsLock(int argc, const char** argv) VL_MT_SAFE_EXCLUDES(m_argMutex);
    void commandArgsAddGuts(int argc, const char** argv) VL_REQUIRES(m_argMutex);
    void commandArgVl(const std::string& arg);
    bool commandArgVlString(const std::string& arg, const std::string& prefix,
                            std::string& valuer);
    bool commandArgVlUint64(const std::string& arg, const std::string& prefix, uint64_t& valuer,
                            uint64_t min = std::numeric_limits<uint64_t>::min(),
                            uint64_t max = std::numeric_limits<uint64_t>::max());
    void commandArgDump() const VL_MT_SAFE_EXCLUDES(m_argMutex);
};

//======================================================================
// VerilatedImp

class VerilatedImpData final {
    // Whole class is internal use only - Global information shared between verilated*.cpp files.
    // All only medium-speed, so use singleton function
protected:
    friend class Verilated;
    friend class VerilatedImp;

    // TYPES
    using UserMap = std::map<std::pair<const void*, void*>, void*>;
    using ExportNameMap = std::map<const char*, int, VerilatedCStrCmp>;

    // MEMBERS
    // Nothing below here is save-restored; users expected to re-register appropriately

    VerilatedMutex m_userMapMutex;  // Protect m_userMap
    // For userInsert, userFind.  As indexed by pointer is common across contexts.
    UserMap m_userMap VL_GUARDED_BY(m_userMapMutex);  // Map of <(scope,userkey), userData>

    VerilatedMutex m_hierMapMutex;  // Protect m_hierMap
    // Map that represents scope hierarchy
    // Used by hierarchyAdd, hierarchyRemove, hierarchyMap
    VerilatedHierarchyMap m_hierMap VL_GUARDED_BY(m_hierMapMutex);

    // Slow - somewhat static:
    VerilatedMutex m_exportMutex;  // Protect m_nameMap
    // Map of <export_func_proto, func number>
    // Used by exportInsert, exportFind, exportName.
    // Export numbers same across all contexts as just a string-to-number conversion
    ExportNameMap m_exportMap VL_GUARDED_BY(m_exportMutex);
    int m_exportNext VL_GUARDED_BY(m_exportMutex) = 0;  // Next export funcnum

    // No guard, as init-time loaded
    std::vector<void*> m_exportFlatCbs;  // Exports when only single scope registered
    std::vector<bool> m_exportFlatMulti;  // Multiple scopes registerd; cannot use m_exportScopes

    // CONSTRUCTORS
    VerilatedImpData() = default;
};

class VerilatedImp final {
    // Whole class is internal use only - Global information shared between verilated*.cpp files.
protected:
    friend class Verilated;

    // MEMBERS
    static VerilatedImpData& s() VL_MT_SAFE {  // Singleton
        static VerilatedImpData s_s;
        return s_s;
    }

public:  // But only for verilated*.cpp
    // CONSTRUCTORS
    VerilatedImp() = default;
    ~VerilatedImp() = default;

private:
    VL_UNCOPYABLE(VerilatedImp);

public:
    // METHODS - debug
    static void versionDump() VL_MT_SAFE;

    // METHODS - user scope tracking
    // We implement this as a single large map instead of one map per scope.
    // There's often many more scopes than userdata's and thus having a ~48byte
    // per map overhead * N scopes would take much more space and cache thrashing.
    // As scopep's are pointers, this implicitly handles multiple Context's
    static void userInsert(const void* scopep, void* userKey, void* userData) VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_userMapMutex};
        const auto it = s().m_userMap.find(std::make_pair(scopep, userKey));
        if (it != s().m_userMap.end()) {
            it->second = userData;
        } else {
            s().m_userMap.emplace(std::make_pair(scopep, userKey), userData);
        }
    }
    static void* userFind(const void* scopep, void* userKey) VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_userMapMutex};
        const auto& it = vlstd::as_const(s().m_userMap).find(std::make_pair(scopep, userKey));
        if (VL_UNLIKELY(it == s().m_userMap.end())) return nullptr;
        return it->second;
    }

    // METHODS - But only for verilated.cpp

    // Symbol table destruction cleans up the entries for each scope.
    static void userEraseScope(const VerilatedScope* scopep) VL_MT_SAFE {
        // Slow ok - called once/scope on destruction, so we only iterate.
        const VerilatedLockGuard lock{s().m_userMapMutex};
        for (auto it = s().m_userMap.begin(); it != s().m_userMap.end();) {
            if (it->first.first == scopep) {
                s().m_userMap.erase(it++);
            } else {
                ++it;
            }
        }
    }
    static void userDump() VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_userMapMutex};  // Avoid it changing in middle of dump
        bool first = true;
        for (const auto& i : s().m_userMap) {
            if (first) {
                VL_PRINTF_MT("  userDump:\n");
                first = false;
            }
            VL_PRINTF_MT("    DPI_USER_DATA scope %p key %p: %p\n", i.first.first, i.first.second,
                         i.second);
        }
    }

    // METHODS - hierarchy - only for verilated*.cpp
    static void hierarchyAdd(const VerilatedScope* fromp, const VerilatedScope* top) VL_MT_SAFE {
        // Slow ok - called at construction for VPI accessible elements
        const VerilatedLockGuard lock{s().m_hierMapMutex};
        s().m_hierMap[fromp].push_back(top);
    }
    static void hierarchyRemove(const VerilatedScope* fromp,
                                const VerilatedScope* top) VL_MT_SAFE {
        // Slow ok - called at destruction for VPI accessible elements
        const VerilatedLockGuard lock{s().m_hierMapMutex};
        VerilatedHierarchyMap& map = s().m_hierMap;
        if (map.find(fromp) == map.end()) return;
        auto& scopes = map[fromp];
        const auto it = find(scopes.begin(), scopes.end(), top);
        if (it != scopes.end()) scopes.erase(it);
    }
    static void hierarchyClear() VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_hierMapMutex};
        VerilatedHierarchyMap& map = s().m_hierMap;
        map.clear();
    }
    static const VerilatedHierarchyMap* hierarchyMap() VL_MT_SAFE_POSTINIT {
        // Thread save only assuming this is called only after model construction completed
        return &s().m_hierMap;
    }

    // METHODS - export names - only for verilated*.cpp

    // Each function prototype is converted to a function number which we
    // then use to index a 2D table also indexed by scope number, because we
    // can't know at Verilation time what scopes will exist in other modules
    // in the design that also happen to have our same callback function.
    // Rather than a 2D map, the integer scheme saves 500ish ns on a likely
    // miss at the cost of a multiply, and all lookups move to slowpath.
private:
    static int exportInsertName(const char* namep) VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_exportMutex};
        const auto it = s().m_exportMap.find(namep);
        if (it == s().m_exportMap.end()) {
            s().m_exportMap.emplace(namep, s().m_exportNext++);
            return s().m_exportNext++;
        } else {
            return it->second;
        }
    }

public:
    static int exportInsert(const char* namep, void* cb) VL_MT_SAFE {
        const int funcnum = VerilatedImp::exportInsertName(namep);
        const VerilatedLockGuard lock{s().m_exportMutex};
        // Slow ok - called once/function at creation
        if (funcnum >= s().m_exportFlatCbs.size()) {
            s().m_exportFlatCbs.resize(funcnum + 1);
            s().m_exportFlatMulti.resize(funcnum + 1);
        }
        if (!s().m_exportFlatMulti[funcnum]) {
            if (s().m_exportFlatCbs[funcnum] == cb) {  // Duplicate
            } else if (!s().m_exportFlatCbs[funcnum]) {  // First
                s().m_exportFlatCbs[funcnum] = cb;
            } else {  // Multiple registrants
                s().m_exportFlatCbs[funcnum] = nullptr;
                s().m_exportFlatMulti[funcnum] = true;
            }
        }
        return funcnum;
    }
    static int exportFindNum(const char* namep) VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_exportMutex};
        const auto& it = s().m_exportMap.find(namep);
        if (VL_LIKELY(it != s().m_exportMap.end())) return it->second;
        const std::string msg = "%Error: Testbench C called "s + namep
                                + " but no such DPI export function name exists in ANY model";
        VL_FATAL_MT("unknown", 0, "", msg.c_str());
        return -1;
    }
    static const std::vector<void*>& exportFlatCbs() VL_MT_SAFE { return s().m_exportFlatCbs; }
    static const char* exportName(int funcnum) VL_MT_SAFE {
        // Slowpath; find name for given export; errors only so no map to reverse-map it
        const VerilatedLockGuard lock{s().m_exportMutex};
        for (const auto& i : s().m_exportMap) {
            if (i.second == funcnum) return i.first;
        }
        return "*UNKNOWN*";
    }
    static void exportsDump() VL_MT_SAFE {
        const VerilatedLockGuard lock{s().m_exportMutex};
        bool first = true;
        for (const auto& i : s().m_exportMap) {
            if (first) {
                VL_PRINTF_MT("  exportDump:\n");
                first = false;
            }
            VL_PRINTF_MT("    DPI_EXPORT_NAME %05d: %s\n", i.second, i.first);
        }
    }
    // We don't free up m_exportMap until the end, because we can't be sure
    // what other models are using the assigned funcnum's.
};

//======================================================================

#endif  // Guard
