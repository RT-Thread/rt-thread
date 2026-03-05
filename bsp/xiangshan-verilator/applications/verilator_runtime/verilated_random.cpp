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
//=========================================================================
///
/// \file
/// \brief Verilated randomization implementation code
///
/// This file must be compiled and linked against all Verilated objects
/// that use randomization features.
///
/// See the internals documentation docs/internals.rst for details.
///
//=========================================================================

#include "verilated_random.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <streambuf>

#define _VL_SOLVER_HASH_LEN 1
#define _VL_SOLVER_HASH_LEN_TOTAL 4

// clang-format off
#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
# define _VL_SOLVER_PIPE  // Allow pipe SMT solving.  Needs fork()
#endif

#ifdef _VL_SOLVER_PIPE
# include <sys/wait.h>
# include <fcntl.h>
#endif

#if defined(_WIN32) || defined(__MINGW32__)
# include <io.h>  // open, read, write, close
#endif
// clang-format on

class VlRProcess final : private std::streambuf, public std::iostream {
    static constexpr int BUFFER_SIZE = 4096;
    const char* const* m_cmd = nullptr;  // fork() process argv
#ifdef _VL_SOLVER_PIPE
    pid_t m_pid = 0;  // fork() process id
#else
    int m_pid = 0;  // fork() process id - always zero as disabled
#endif
    bool m_pidExited = true;  // If subprocess has exited and can be opened
    int m_pidStatus = 0;  // fork() process exit status, valid if m_pidExited
    int m_writeFd = -1;  // File descriptor TO subprocess
    int m_readFd = -1;  // File descriptor FROM subprocess
    char m_readBuf[BUFFER_SIZE];
    char m_writeBuf[BUFFER_SIZE];

public:
    typedef std::streambuf::traits_type traits_type;

protected:
    int overflow(int c = traits_type::eof()) override {
        char c2 = static_cast<char>(c);
        if (pbase() == pptr()) return 0;
        size_t size = pptr() - pbase();
        ssize_t n = ::write(m_writeFd, pbase(), size);
        // VL_PRINTF_MT("solver-write '%s'\n", std::string(pbase(), size).c_str());
        if (n == -1) perror("write");
        if (n <= 0) {
            wait_report();
            return traits_type::eof();
        }
        if (n == size)
            setp(m_writeBuf, m_writeBuf + sizeof(m_writeBuf));
        else
            setp(m_writeBuf + n, m_writeBuf + sizeof(m_writeBuf));
        if (c != traits_type::eof()) sputc(c2);
        return 0;
    }
    int underflow() override {
        sync();
        ssize_t n = ::read(m_readFd, m_readBuf, sizeof(m_readBuf));
        if (n == -1) perror("read");
        if (n <= 0) {
            wait_report();
            return traits_type::eof();
        }
        setg(m_readBuf, m_readBuf, m_readBuf + n);
        return traits_type::to_int_type(m_readBuf[0]);
    }
    int sync() override {
        overflow();
        return 0;
    }

public:
    explicit VlRProcess(const char* const* const cmd = nullptr)
        : std::streambuf{}
        , std::iostream{this}
        , m_cmd{cmd} {
        open(cmd);
    }

    void wait_report() {
        if (m_pidExited) return;
#ifdef _VL_SOLVER_PIPE
        if (waitpid(m_pid, &m_pidStatus, 0) != m_pid) return;
        if (m_pidStatus) {
            std::stringstream msg;
            msg << "Subprocess command `" << m_cmd[0];
            for (const char* const* arg = m_cmd + 1; *arg; ++arg) msg << ' ' << *arg;
            msg << "' failed: ";
            if (WIFSIGNALED(m_pidStatus))
                msg << strsignal(WTERMSIG(m_pidStatus))
                    << (WCOREDUMP(m_pidStatus) ? " (core dumped)" : "");
            else if (WIFEXITED(m_pidStatus))
                msg << "exit status " << WEXITSTATUS(m_pidStatus);
            const std::string str = msg.str();
            VL_WARN_MT("", 0, "VlRProcess", str.c_str());
        }
#endif
        m_pidExited = true;
        m_pid = 0;
        closeFds();
    }

    void closeFds() {
        if (m_writeFd != -1) {
            close(m_writeFd);
            m_writeFd = -1;
        }
        if (m_readFd != -1) {
            close(m_readFd);
            m_readFd = -1;
        }
    }

    bool open(const char* const* const cmd) {
        setp(std::begin(m_writeBuf), std::end(m_writeBuf));
        setg(m_readBuf, m_readBuf, m_readBuf);
#ifdef _VL_SOLVER_PIPE
        if (!cmd || !cmd[0]) return false;
        m_cmd = cmd;
        int fd_stdin[2];  // Can't use std::array
        int fd_stdout[2];  // Can't use std::array
        constexpr int P_RD = 0;
        constexpr int P_WR = 1;

        if (pipe(fd_stdin) != 0) {
            perror("VlRProcess::open: pipe");
            return false;
        }
        if (pipe(fd_stdout) != 0) {
            perror("VlRProcess::open: pipe");
            close(fd_stdin[P_RD]);
            close(fd_stdin[P_WR]);
            return false;
        }

        if (fd_stdin[P_RD] <= 2 || fd_stdin[P_WR] <= 2 || fd_stdout[P_RD] <= 2
            || fd_stdout[P_WR] <= 2) {
            // We'd have to rearrange all of the FD usages in this case.
            // Too unlikely; verilator isn't a daemon.
            fprintf(stderr, "stdin/stdout closed before pipe opened\n");
            close(fd_stdin[P_RD]);
            close(fd_stdin[P_WR]);
            close(fd_stdout[P_RD]);
            close(fd_stdout[P_WR]);
            return false;
        }

        const pid_t pid = fork();
        if (pid < 0) {
            perror("VlRProcess::open: fork");
            close(fd_stdin[P_RD]);
            close(fd_stdin[P_WR]);
            close(fd_stdout[P_RD]);
            close(fd_stdout[P_WR]);
            return false;
        }
        if (pid == 0) {
            // Child
            close(fd_stdin[P_WR]);
            dup2(fd_stdin[P_RD], STDIN_FILENO);
            close(fd_stdout[P_RD]);
            dup2(fd_stdout[P_WR], STDOUT_FILENO);
            execvp(cmd[0], const_cast<char* const*>(cmd));
            std::stringstream msg;
            msg << "VlRProcess::open: execvp(" << cmd[0] << ")";
            const std::string str = msg.str();
            perror(str.c_str());
            _exit(127);
        }
        // Parent
        m_pid = pid;
        m_pidExited = false;
        m_pidStatus = 0;
        m_readFd = fd_stdout[P_RD];
        m_writeFd = fd_stdin[P_WR];

        close(fd_stdin[P_RD]);
        close(fd_stdout[P_WR]);

        return true;
#else
        return false;
#endif
    }
};

static VlRProcess& getSolver() {
    static VlRProcess s_solver;
    static bool s_done = false;
    if (s_done) return s_solver;
    s_done = true;

    static std::vector<const char*> s_argv;
    static std::string s_program = Verilated::threadContextp()->solverProgram();
    s_argv.emplace_back(&s_program[0]);
    for (char* arg = &s_program[0]; *arg; ++arg) {
        if (*arg == ' ') {
            *arg = '\0';
            s_argv.emplace_back(arg + 1);
        }
    }
    s_argv.emplace_back(nullptr);

    const char* const* const cmd = &s_argv[0];
    s_solver.open(cmd);
    s_solver << "(set-logic QF_ABV)\n";
    s_solver << "(check-sat)\n";
    s_solver << "(reset)\n";
    std::string s;
    getline(s_solver, s);
    if (s == "sat") return s_solver;

    std::stringstream msg;
    msg << "Unable to communicate with SAT solver, please check its installation or specify a "
           "different one in VERILATOR_SOLVER environment variable.\n";
    msg << " ... Tried: $";
    for (const char* const* arg = cmd; *arg; ++arg) msg << ' ' << *arg;
    msg << '\n';
    const std::string str = msg.str();
    VL_WARN_MT("", 0, "randomize", str.c_str());

    while (getline(s_solver, s)) {}
    return s_solver;
}

static std::string readUntilBalanced(std::istream& stream) {
    std::string result;
    std::string token;
    int parenCount = 1;
    while (stream >> token) {
        for (const char c : token) {
            if (c == '(') {
                ++parenCount;
            } else if (c == ')') {
                --parenCount;
            }
        }
        result += token + " ";
        if (parenCount == 0) break;
    }
    return result;
}

static std::string parseNestedSelect(const std::string& nested_select_expr,
                                     std::vector<std::string>& indices) {
    std::istringstream nestedStream(nested_select_expr);
    std::string name, idx;
    nestedStream >> name;
    if (name == "(select") {
        const std::string further_nested_expr = readUntilBalanced(nestedStream);
        name = parseNestedSelect(further_nested_expr, indices);
    }
    std::getline(nestedStream, idx, ')');
    indices.push_back(idx);
    return name;
}

//======================================================================
// VlRandomizer:: Methods

void VlRandomVar::emitGetValue(std::ostream& s) const { s << ' ' << m_name; }
void VlRandomVar::emitExtract(std::ostream& s, int i) const {
    s << " ((_ extract " << i << ' ' << i << ") " << m_name << ')';
}
void VlRandomVar::emitType(std::ostream& s) const { s << "(_ BitVec " << width() << ')'; }
int VlRandomVar::totalWidth() const { return m_width; }
static bool parseSMTNum(int obits, WDataOutP owp, const std::string& val) {
    int i;
    for (i = 0; val[i] && val[i] != '#'; ++i) {}
    if (val[i++] != '#') return false;
    switch (val[i++]) {
    case 'b': _vl_vsss_based(owp, obits, 1, &val[i], 0, val.size() - i); break;
    case 'o': _vl_vsss_based(owp, obits, 3, &val[i], 0, val.size() - i); break;
    case 'h':  // FALLTHRU
    case 'x': _vl_vsss_based(owp, obits, 4, &val[i], 0, val.size() - i); break;
    default:
        VL_WARN_MT(__FILE__, __LINE__, "randomize",
                   "Internal: Unable to parse solver's randomized number");
        return false;
    }
    return true;
}
bool VlRandomVar::set(const std::string& idx, const std::string& val) const {
    VlWide<VL_WQ_WORDS_E> qowp;
    VL_SET_WQ(qowp, 0ULL);
    WDataOutP owp = qowp;
    const int obits = width();
    VlWide<VL_WQ_WORDS_E> qiwp;
    VL_SET_WQ(qiwp, 0ULL);
    if (!idx.empty() && !parseSMTNum(64, qiwp, idx)) return false;
    const int nidx = qiwp[0];
    if (obits > VL_QUADSIZE) owp = reinterpret_cast<WDataOutP>(datap(nidx));
    if (!parseSMTNum(obits, owp, val)) return false;

    if (obits <= VL_BYTESIZE) {
        CData* const p = static_cast<CData*>(datap(nidx));
        *p = VL_CLEAN_II(obits, obits, owp[0]);
    } else if (obits <= VL_SHORTSIZE) {
        SData* const p = static_cast<SData*>(datap(nidx));
        *p = VL_CLEAN_II(obits, obits, owp[0]);
    } else if (obits <= VL_IDATASIZE) {
        IData* const p = static_cast<IData*>(datap(nidx));
        *p = VL_CLEAN_II(obits, obits, owp[0]);
    } else if (obits <= VL_QUADSIZE) {
        QData* const p = static_cast<QData*>(datap(nidx));
        *p = VL_CLEAN_QQ(obits, obits, VL_SET_QW(owp));
    } else {
        _vl_clean_inplace_w(obits, owp);
    }
    return true;
}

void VlRandomizer::randomConstraint(std::ostream& os, VlRNG& rngr, int bits) {
    const IData hash = VL_RANDOM_RNG_I(rngr) & ((1 << bits) - 1);
    int varBits = 0;
    for (const auto& var : m_vars) varBits += var.second->totalWidth();
    os << "(= #b";
    for (int i = bits - 1; i >= 0; i--) os << (VL_BITISSET_I(hash, i) ? '1' : '0');
    if (bits > 1) os << " (concat";
    for (int i = 0; i < bits; ++i) {
        IData varBitsLeft = varBits;
        IData varBitsWant = (varBits + 1) / 2;
        if (varBits > 2) os << " (bvxor";
        for (const auto& var : m_vars) {
            for (int j = 0; j < var.second->totalWidth(); j++, varBitsLeft--) {
                const bool doEmit = (VL_RANDOM_RNG_I(rngr) % varBitsLeft) < varBitsWant;
                if (doEmit) {
                    var.second->emitExtract(os, j);
                    if (--varBitsWant == 0) break;
                }
            }
            if (varBitsWant == 0) break;
        }
        if (varBits > 2) os << ')';
    }
    if (bits > 1) os << ')';
    os << ')';
}

size_t VlRandomizer::hashConstraints() const {
    size_t h = 0;
    for (const auto& c : m_constraints) {
        h ^= std::hash<std::string>{}(c) + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
}

void VlRandomizer::enumerateRandcValues(const std::string& varName, VlRNG& rngr) {
    std::vector<uint64_t> values;
    const auto varIt = m_vars.find(varName);
    if (varIt == m_vars.end()) return;
    const int width = varIt->second->width();

    std::iostream& os = getSolver();
    if (!os) return;

    // Set up a single incremental solver session for enumeration
    os << "(set-option :produce-models true)\n";
    os << "(set-logic QF_ABV)\n";
    os << "(define-fun __Vbv ((b Bool)) (_ BitVec 1) (ite b #b1 #b0))\n";
    os << "(define-fun __Vbool ((v (_ BitVec 1))) Bool (= #b1 v))\n";

    // Declare all variables (solver needs full context for cross-var constraints)
    for (const auto& var : m_vars) {
        if (var.second->dimension() > 0) {
            auto arrVarsp = std::make_shared<const ArrayInfoMap>(m_arr_vars);
            var.second->setArrayInfo(arrVarsp);
        }
        os << "(declare-fun " << var.first << " () ";
        var.second->emitType(os);
        os << ")\n";
    }

    // Assert all user constraints
    for (const std::string& constraint : m_constraints) {
        os << "(assert (= #b1 " << constraint << "))\n";
    }

    // Incrementally enumerate all valid values for this randc variable
    while (true) {
        os << "(check-sat)\n";
        std::string sat;
        do { std::getline(os, sat); } while (sat.empty());
        if (sat != "sat") break;

        // Read just this variable's value
        os << "(get-value (" << varName << "))\n";
        char c;
        os >> c;  // '('
        os >> c;  // '('
        std::string name, value;
        os >> name;  // Consume variable name token from solver output
        (void)name;
        std::getline(os, value, ')');
        os >> c;  // ')'

        // Parse the SMT value to uint64_t
        VlWide<VL_WQ_WORDS_E> qowp;
        VL_SET_WQ(qowp, 0ULL);
        if (!parseSMTNum(width, qowp, value)) break;
        const uint64_t numVal = (width <= 32) ? qowp[0] : VL_SET_QW(qowp);

        values.push_back(numVal);

        // Exclude this value for next iteration (incremental)
        os << "(assert (not (= " << varName << " (_ bv" << numVal << " " << width << "))))\n";
    }

    os << "(reset)\n";

    // Shuffle using Fisher-Yates
    for (size_t i = values.size(); i > 1; --i) {
        const size_t j = VL_RANDOM_RNG_I(rngr) % i;
        std::swap(values[i - 1], values[j]);
    }

    m_randcValueQueues[varName] = std::deque<uint64_t>(values.begin(), values.end());
}

bool VlRandomizer::next(VlRNG& rngr) {
    if (m_vars.empty() && m_unique_arrays.empty()) return true;
    for (const std::string& baseName : m_unique_arrays) {
        const auto it = m_vars.find(baseName);
        const uint32_t size = m_unique_array_sizes.at(baseName);

        if (it != m_vars.end()) {
            std::string distinctExpr = "(__Vbv (distinct";
            for (uint32_t i = 0; i < size; ++i) {
                char hexIdx[12];
                sprintf(hexIdx, "#x%08x", i);
                distinctExpr += " (select " + it->first + " " + hexIdx + ")";
            }
            distinctExpr += "))";
            m_constraints.push_back(distinctExpr);
        }
    }

    // Randc queue-based cycling: enumerate valid values once, then pop per call
    if (!m_randcVarNames.empty()) {
        const size_t currentHash = hashConstraints();
        // Invalidate queues if constraints changed (e.g., constraint_mode toggled)
        if (currentHash != m_randcConstraintHash) {
            m_randcValueQueues.clear();
            m_randcConstraintHash = currentHash;
        }
        // Refill empty queues (start of new cycle)
        for (const auto& name : m_randcVarNames) {
            auto& queue = m_randcValueQueues[name];
            if (queue.empty()) enumerateRandcValues(name, rngr);
        }
    }

    // Pop randc values from queues (will be pinned in solver)
    std::map<std::string, uint64_t> randcPinned;
    for (const auto& name : m_randcVarNames) {
        auto& queue = m_randcValueQueues[name];
        if (queue.empty()) return false;  // No valid values exist
        randcPinned[name] = queue.front();
        queue.pop_front();
    }

    // If solve-before constraints are present, use phased solving
    if (!m_solveBefore.empty()) return nextPhased(rngr);

    std::iostream& os = getSolver();
    if (!os) return false;

    os << "(set-option :produce-models true)\n";
    os << "(set-logic QF_ABV)\n";
    os << "(define-fun __Vbv ((b Bool)) (_ BitVec 1) (ite b #b1 #b0))\n";
    os << "(define-fun __Vbool ((v (_ BitVec 1))) Bool (= #b1 v))\n";
    for (const auto& var : m_vars) {
        if (var.second->dimension() > 0) {
            auto arrVarsp = std::make_shared<const ArrayInfoMap>(m_arr_vars);
            var.second->setArrayInfo(arrVarsp);
        }
        os << "(declare-fun " << var.first << " () ";
        var.second->emitType(os);
        os << ")\n";
    }

    for (const std::string& constraint : m_constraints) {
        os << "(assert (= #b1 " << constraint << "))\n";
    }

    // Pin randc values from pre-enumerated queues
    for (const auto& pair : randcPinned) {
        const int w = m_vars.at(pair.first)->width();
        os << "(assert (= " << pair.first << " (_ bv" << pair.second << " " << w << ")))\n";
    }

    os << "(check-sat)\n";

    bool sat = parseSolution(os, true);
    if (!sat) {
        // If unsat, use named assertions to get unsat-core
        os << "(reset)\n";
        os << "(set-option :produce-unsat-cores true)\n";
        os << "(set-logic QF_ABV)\n";
        os << "(define-fun __Vbv ((b Bool)) (_ BitVec 1) (ite b #b1 #b0))\n";
        os << "(define-fun __Vbool ((v (_ BitVec 1))) Bool (= #b1 v))\n";
        for (const auto& var : m_vars) {
            if (var.second->dimension() > 0) {
                auto arrVarsp = std::make_shared<const ArrayInfoMap>(m_arr_vars);
                var.second->setArrayInfo(arrVarsp);
            }
            os << "(declare-fun " << var.first << " () ";
            var.second->emitType(os);
            os << ")\n";
        }
        int j = 0;
        for (const std::string& constraint : m_constraints) {
            os << "(assert (! (= #b1 " << constraint << ") :named cons" << j << "))\n";
            j++;
        }
        os << "(check-sat)\n";
        sat = parseSolution(os, true);
        (void)sat;
        os << "(reset)\n";
        return false;
    }
    for (int i = 0; i < _VL_SOLVER_HASH_LEN_TOTAL && sat; ++i) {
        os << "(assert ";
        randomConstraint(os, rngr, _VL_SOLVER_HASH_LEN);
        os << ")\n";
        os << "\n(check-sat)\n";
        sat = parseSolution(os, false);
        (void)sat;
    }

    os << "(reset)\n";
    return true;
}

bool VlRandomizer::parseSolution(std::iostream& os, bool log) {
    std::string sat;
    do { std::getline(os, sat); } while (sat == "");
    if (sat == "unsat") {
        if (!log) return false;
        os << "(get-unsat-core) \n";
        sat.clear();
        std::getline(os, sat);
        std::vector<int> numbers;
        std::string currentNum;
        for (char c : sat) {
            if (std::isdigit(c)) {
                currentNum += c;
                numbers.push_back(std::stoi(currentNum));
                currentNum.clear();
            }
        }
        if (Verilated::threadContextp()->warnUnsatConstr()) {
            for (int n : numbers) {
                if (n < m_constraints_line.size()) {
                    const std::string& constraint_info = m_constraints_line[n];
                    // Parse "filename:linenum   source" format
                    size_t colon_pos = constraint_info.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string filename = constraint_info.substr(0, colon_pos);
                        size_t space_pos = constraint_info.find("   ", colon_pos);
                        std::string linenum_str;
                        std::string source;
                        if (space_pos != std::string::npos) {
                            linenum_str
                                = constraint_info.substr(colon_pos + 1, space_pos - colon_pos - 1);
                            source = constraint_info.substr(space_pos + 3);
                        } else {
                            linenum_str = constraint_info.substr(colon_pos + 1);
                        }
                        const int linenum = std::stoi(linenum_str);
                        std::string msg = "UNSATCONSTR: Unsatisfied constraint";
                        if (!source.empty()) {
                            // Trim leading whitespace and add quotes
                            size_t start = source.find_first_not_of(" \t");
                            if (start != std::string::npos) {
                                msg += ": '" + source.substr(start) + "'";
                            }
                        }
                        VL_WARN_MT(filename.c_str(), linenum, "", msg.c_str());
                    } else {
                        VL_PRINTF("%%Warning-UNSATCONSTR: Unsatisfied constraint: %s\n",
                                  constraint_info.c_str());
                    }
                }
            }
        }
        return false;
    }
    if (sat != "sat") {
        std::stringstream msg;
        msg << "Internal: Solver error: " << sat;
        const std::string str = msg.str();
        VL_WARN_MT(__FILE__, __LINE__, "randomize", str.c_str());
        return false;
    }

    os << "(get-value (";
    for (const auto& var : m_vars) {
        if (var.second->dimension() > 0) {
            auto arrVarsp = std::make_shared<const ArrayInfoMap>(m_arr_vars);
            var.second->setArrayInfo(arrVarsp);
        }
        var.second->emitGetValue(os);
    }
    os << "))\n";
    // Quasi-parse S-expression of the form ((x #xVALUE) (y #bVALUE) (z #xVALUE))
    char c;
    os >> c;
    if (c != '(') {
        VL_WARN_MT(__FILE__, __LINE__, "randomize",
                   "Internal: Unable to parse solver's response: invalid S-expression");
        return false;
    }
    while (true) {
        os >> c;
        if (c == ')') break;
        if (c != '(') {
            VL_WARN_MT(__FILE__, __LINE__, "randomize",
                       "Internal: Unable to parse solver's response: invalid S-expression");
            return false;
        }
        std::string name, idx, value;
        std::vector<std::string> indices;
        os >> name;
        indices.clear();
        if (name == "(select") {
            const std::string selectExpr = readUntilBalanced(os);
            name = parseNestedSelect(selectExpr, indices);
        }
        std::getline(os, value, ')');
        const auto it = m_vars.find(name);
        if (it == m_vars.end()) continue;
        const VlRandomVar& varr = *it->second;
        if (m_randmodep && !varr.randModeIdxNone()) {
            if (!m_randmodep->at(varr.randModeIdx())) continue;
        }
        if (!indices.empty()) {
            std::ostringstream oss;
            oss << varr.name();
            for (const auto& hex_index : indices) {
                const size_t start = hex_index.find_first_not_of(" ");
                if (start == std::string::npos || hex_index.substr(start, 2) != "#x") {
                    VL_FATAL_MT(__FILE__, __LINE__, "randomize",
                                "hex_index contains invalid format");
                    continue;
                }
                std::string trimmed_hex = hex_index.substr(start + 2);

                if (trimmed_hex.size() <= 8) {  // Small numbers: <= 32 bits
                    // Convert to decimal and output directly
                    oss << "[" << std::to_string(std::stoll(trimmed_hex, nullptr, 16)) << "]";
                } else {  // Large numbers: > 32 bits
                    // Trim leading zeros and handle empty case
                    trimmed_hex.erase(0, trimmed_hex.find_first_not_of('0'));
                    oss << "[" << (trimmed_hex.empty() ? "0" : trimmed_hex) << "]";
                }
            }
            const std::string indexed_name = oss.str();

            const auto iti = std::find_if(m_arr_vars.begin(), m_arr_vars.end(),
                                          [&indexed_name](const auto& entry) {
                                              return entry.second->m_name == indexed_name;
                                          });
            if (iti != m_arr_vars.end()) {
                std::ostringstream ss;
                ss << "#x" << std::hex << std::setw(8) << std::setfill('0')
                   << iti->second->m_index;
                idx = ss.str();
            } else {
                VL_FATAL_MT(__FILE__, __LINE__, "randomize",
                            "indexed_name not found in m_arr_vars");
            }
        }
        varr.set(idx, value);
    }
    return true;
}

void VlRandomizer::hard(std::string&& constraint, const char* filename, uint32_t linenum,
                        const char* source) {
    m_constraints.emplace_back(std::move(constraint));
    // Format constraint location: "filename:linenum   source"
    if (filename[0] != '\0' || source[0] != '\0') {
        std::string line;
        if (filename[0] != '\0') {
            line = std::string(filename) + ":" + std::to_string(linenum);
            if (source[0] != '\0') line += "   " + std::string(source);
        } else {
            line = source;
        }
        m_constraints_line.emplace_back(std::move(line));
    }
}

void VlRandomizer::clearConstraints() {
    m_constraints.clear();
    m_constraints_line.clear();
    m_solveBefore.clear();
    // Keep m_vars for class member randomization
}

void VlRandomizer::clearAll() {
    m_constraints.clear();
    m_vars.clear();
    m_randcVarNames.clear();
    m_randcValueQueues.clear();
    m_randcConstraintHash = 0;
}

void VlRandomizer::markRandc(const char* name) { m_randcVarNames.insert(name); }

void VlRandomizer::solveBefore(const char* beforeName, const char* afterName) {
    m_solveBefore.emplace_back(std::string(beforeName), std::string(afterName));
}

bool VlRandomizer::nextPhased(VlRNG& rngr) {
    // Phased solving for solve...before constraints.
    // Variables are solved in layers determined by topological sort of the
    // solve-before dependency graph. Each layer is solved with ALL constraints
    // (preserving the solution space) but earlier layers' values are pinned.

    // Step 1: Build dependency graph (before -> {after vars})
    std::map<std::string, std::set<std::string>> graph;
    std::map<std::string, int> inDegree;
    std::set<std::string> solveBeforeVars;

    for (const auto& pair : m_solveBefore) {
        const std::string& before = pair.first;
        const std::string& after = pair.second;
        // Only consider variables that are actually registered
        if (m_vars.find(before) == m_vars.end() || m_vars.find(after) == m_vars.end()) continue;
        graph[before].insert(after);
        solveBeforeVars.insert(before);
        solveBeforeVars.insert(after);
        if (inDegree.find(before) == inDegree.end()) inDegree[before] = 0;
        if (inDegree.find(after) == inDegree.end()) inDegree[after] = 0;
    }

    // Compute in-degrees (after depends on before, so edge is before->after,
    // but for solving order: before has no incoming edge from after)
    // Actually: "solve x before y" means x should be solved first.
    // Dependency: y depends on x. Edge: x -> y. in-degree of y increases.
    for (const auto& entry : graph) {
        for (const auto& to : entry.second) { inDegree[to]++; }
    }

    // Step 2: Topological sort into layers (Kahn's algorithm)
    std::vector<std::vector<std::string>> layers;
    std::set<std::string> remaining = solveBeforeVars;

    while (!remaining.empty()) {
        std::vector<std::string> currentLayer;
        for (const auto& var : remaining) {
            if (inDegree[var] == 0) currentLayer.push_back(var);
        }
        if (currentLayer.empty()) {
            VL_WARN_MT("", 0, "randomize", "Circular dependency in solve-before constraints");
            return false;
        }
        std::sort(currentLayer.begin(), currentLayer.end());
        for (const auto& var : currentLayer) {
            remaining.erase(var);
            if (graph.count(var)) {
                for (const auto& to : graph[var]) { inDegree[to]--; }
            }
        }
        layers.push_back(std::move(currentLayer));
    }

    // If only one layer, no phased solving needed -- fall through to normal path
    // (all solve_before vars are independent, no actual ordering required)
    if (layers.size() <= 1) {
        // Clear solve_before temporarily and call normal next()
        const auto saved = std::move(m_solveBefore);
        m_solveBefore.clear();
        const bool result = next(rngr);
        m_solveBefore = std::move(saved);
        return result;
    }

    // Step 3: Solve phase by phase
    std::map<std::string, std::string> solvedValues;  // varName -> SMT value literal

    for (size_t phase = 0; phase < layers.size(); phase++) {
        const bool isFinalPhase = (phase == layers.size() - 1);

        std::iostream& os = getSolver();
        if (!os) return false;

        // Solver session setup
        os << "(set-option :produce-models true)\n";
        os << "(set-logic QF_ABV)\n";
        os << "(define-fun __Vbv ((b Bool)) (_ BitVec 1) (ite b #b1 #b0))\n";
        os << "(define-fun __Vbool ((v (_ BitVec 1))) Bool (= #b1 v))\n";

        // Declare ALL variables
        for (const auto& var : m_vars) {
            if (var.second->dimension() > 0) {
                auto arrVarsp = std::make_shared<const ArrayInfoMap>(m_arr_vars);
                var.second->setArrayInfo(arrVarsp);
            }
            os << "(declare-fun " << var.first << " () ";
            var.second->emitType(os);
            os << ")\n";
        }

        // Pin all previously solved variables
        for (const auto& entry : solvedValues) {
            os << "(assert (= " << entry.first << " " << entry.second << "))\n";
        }

        // Assert ALL constraints
        for (const std::string& constraint : m_constraints) {
            os << "(assert (= #b1 " << constraint << "))\n";
        }

        // Initial check-sat WITHOUT diversity (guaranteed sat if constraints are consistent)
        os << "(check-sat)\n";

        if (isFinalPhase) {
            // Final phase: use parseSolution to write ALL values to memory
            bool sat = parseSolution(os, true);
            if (!sat) {
                os << "(reset)\n";
                return false;
            }
            // Diversity loop (same as normal next())
            for (int i = 0; i < _VL_SOLVER_HASH_LEN_TOTAL && sat; ++i) {
                os << "(assert ";
                randomConstraint(os, rngr, _VL_SOLVER_HASH_LEN);
                os << ")\n";
                os << "\n(check-sat)\n";
                sat = parseSolution(os, false);
                (void)sat;
            }
            os << "(reset)\n";
        } else {
            // Intermediate phase: extract values for current layer variables only
            std::string satResponse;
            do { std::getline(os, satResponse); } while (satResponse.empty());

            if (satResponse != "sat") {
                os << "(reset)\n";
                return false;
            }

            // Build get-value variable list for this layer
            const auto& layerVars = layers[phase];
            auto getValueCmd = [&]() {
                os << "(get-value (";
                for (const auto& varName : layerVars) {
                    if (m_vars.count(varName)) os << varName << " ";
                }
                os << "))\n";
            };

            // Helper to parse ((name1 value1) (name2 value2) ...) response
            auto parseGetValue = [&]() -> bool {
                char c;
                os >> c;  // outer '('
                while (true) {
                    os >> c;
                    if (c == ')') break;  // outer closing
                    if (c != '(') return false;
                    std::string name;
                    os >> name;

                    // Read value handling nested parens for (_ bvN W) format
                    os >> std::ws;
                    std::string value;
                    char firstChar;
                    os.get(firstChar);
                    if (firstChar == '(') {
                        // Compound value like (_ bv5 32)
                        value = "(";
                        int depth = 1;
                        while (depth > 0) {
                            os.get(c);
                            value += c;
                            if (c == '(')
                                depth++;
                            else if (c == ')')
                                depth--;
                        }
                        // Read closing ')' of the pair
                        os >> c;
                    } else {
                        // Atom value like #x00000005 or #b101
                        value += firstChar;
                        while (os.get(c) && c != ')') { value += c; }
                        // Trim trailing whitespace
                        const size_t end = value.find_last_not_of(" \t\n\r");
                        if (end != std::string::npos) value = value.substr(0, end + 1);
                    }

                    solvedValues[name] = value;
                }
                return true;
            };

            // Get baseline values (deterministic, always valid)
            getValueCmd();
            if (!parseGetValue()) {
                os << "(reset)\n";
                return false;
            }

            // Try diversity: add random constraint, re-check. If sat, get
            // updated (more diverse) values. If unsat, keep baseline values.
            os << "(assert ";
            randomConstraint(os, rngr, _VL_SOLVER_HASH_LEN);
            os << ")\n";
            os << "(check-sat)\n";
            satResponse.clear();
            do { std::getline(os, satResponse); } while (satResponse.empty());
            if (satResponse == "sat") {
                getValueCmd();
                parseGetValue();
            }

            os << "(reset)\n";
        }
    }

    return true;
}

#ifdef VL_DEBUG
void VlRandomizer::dump() const {
    for (const auto& var : m_vars) {
        VL_PRINTF("Variable (%d): %s\n", var.second->width(), var.second->name().c_str());
    }
    for (const std::string& c : m_constraints) VL_PRINTF("Constraint: %s\n", c.c_str());
}
#endif
