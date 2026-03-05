// -*- mode: C++; c-file-style: "cc-mode"
//-*- *************************************************************************
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
/// \brief Verilated symbol inspection header
///
/// This file is for inclusion by user wrapper code that needs to inspect
/// the symbol table.  It is not included in verilated.h (instead see
/// verilated_sym_props.h) as it requires some heavyweight C++ classes.
///
/// These classes are rarely used by user code; typical user code will
/// instead use the VPI to access this information.
///
/// These classes are thread safe and read only. It is constructed only
/// when a model is built (from the main thread).
///
//*************************************************************************

#ifndef VERILATOR_VERILATED_SYMS_H_
#define VERILATOR_VERILATED_SYMS_H_

#include "verilatedos.h"

#include "verilated.h"
#include "verilated_sym_props.h"

#include <map>
#include <unordered_map>
#include <vector>

//======================================================================
// Types

// Class to sort maps keyed by const char*'s
struct VerilatedCStrCmp final {
    bool operator()(const char* a, const char* b) const { return std::strcmp(a, b) < 0; }
};

// Map of sorted scope names to find associated scope class
// This is a class instead of typedef/using to allow forward declaration in verilated.h
class VerilatedScopeNameMap final
    : public std::map<const char*, const VerilatedScope*, VerilatedCStrCmp> {
public:
    VerilatedScopeNameMap() = default;
    ~VerilatedScopeNameMap() = default;
};

// Map of sorted variable names to find associated variable class
// This is a class instead of typedef/using to allow forward declaration in verilated.h
class VerilatedVarNameMap final : public std::map<const char*, VerilatedVar, VerilatedCStrCmp> {
public:
    VerilatedVarNameMap() = default;
    ~VerilatedVarNameMap() = default;
};

// Map of parent scope to vector of children scopes
// This is a class instead of typedef/using to allow forward declaration in verilated.h
class VerilatedHierarchyMap final
    : public std::unordered_map<const VerilatedScope*, std::vector<const VerilatedScope*>> {
public:
    VerilatedHierarchyMap() = default;
    ~VerilatedHierarchyMap() = default;
};

#endif  // Guard
