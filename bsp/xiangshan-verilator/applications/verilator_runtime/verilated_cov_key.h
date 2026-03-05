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
/// \brief Verilated coverage item keys internal header
///
/// This file is not part of the Verilated public-facing API.
/// It is only for internal use by the Verilated library coverage routines.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_COV_KEY_H_
#define VERILATOR_VERILATED_COV_KEY_H_

#include "verilatedos.h"

#include <string>

//=============================================================================
// Data used to edit below file, using vlcovgen

#define VLCOVGEN_ITEM(string_parsed_by_vlcovgen)

// clang-format off
VLCOVGEN_ITEM("'name':'column',      'short':'n',  'group':1, 'default':0,    'descr':'Column number for the item.  Used to disambiguate multiple coverage points on the same line number'")
VLCOVGEN_ITEM("'name':'filename',    'short':'f',  'group':1, 'default':None, 'descr':'Filename of the item'")
VLCOVGEN_ITEM("'name':'linescov',    'short':'S',  'group':1, 'default':'',   'descr':'List of comma-separated lines covered'")
VLCOVGEN_ITEM("'name':'per_instance','short':'P',  'group':1, 'default':0,    'descr':'True if every hierarchy is independently counted; otherwise all hierarchies will be combined into a single count'")
VLCOVGEN_ITEM("'name':'thresh',      'short':'s',  'group':1, 'default':None, 'descr':'Number of hits to consider covered (aka at_least)'")
VLCOVGEN_ITEM("'name':'type',        'short':'t',  'group':1, 'default':'',   'descr':'Type of coverage (block, line, fsm, etc)'")
// Bin attributes
VLCOVGEN_ITEM("'name':'comment',     'short':'o',  'group':0, 'default':'',   'descr':'Textual description for the item'")
VLCOVGEN_ITEM("'name':'hier',        'short':'h',  'group':0, 'default':'',   'descr':'Hierarchy path name for the item'")
VLCOVGEN_ITEM("'name':'lineno',      'short':'l',  'group':0, 'default':0,    'descr':'Line number for the item'")
VLCOVGEN_ITEM("'name':'weight',      'short':'w',  'group':0, 'default':None, 'descr':'For totaling items, weight of this item'")
// clang-format on

// VLCOVGEN_CIK_AUTO_EDIT_BEGIN
#define VL_CIK_COLUMN "n"
#define VL_CIK_COMMENT "o"
#define VL_CIK_FILENAME "f"
#define VL_CIK_HIER "h"
#define VL_CIK_LINENO "l"
#define VL_CIK_LINESCOV "S"
#define VL_CIK_PER_INSTANCE "P"
#define VL_CIK_THRESH "s"
#define VL_CIK_TYPE "t"
#define VL_CIK_WEIGHT "w"
// VLCOVGEN_CIK_AUTO_EDIT_END

//=============================================================================
// VerilatedCovKey
// Namespace-style static class for \internal use.

class VerilatedCovKey final {
public:
    // Return the short key code for a given a long coverage key
    static std::string shortKey(const std::string& key) VL_PURE {
        // VLCOVGEN_SHORT_AUTO_EDIT_BEGIN
        if (key == "column") return VL_CIK_COLUMN;
        if (key == "comment") return VL_CIK_COMMENT;
        if (key == "filename") return VL_CIK_FILENAME;
        if (key == "hier") return VL_CIK_HIER;
        if (key == "lineno") return VL_CIK_LINENO;
        if (key == "linescov") return VL_CIK_LINESCOV;
        if (key == "per_instance") return VL_CIK_PER_INSTANCE;
        if (key == "thresh") return VL_CIK_THRESH;
        if (key == "type") return VL_CIK_TYPE;
        if (key == "weight") return VL_CIK_WEIGHT;
        // VLCOVGEN_SHORT_AUTO_EDIT_END
        return key;
    }
};

#endif  // guard
