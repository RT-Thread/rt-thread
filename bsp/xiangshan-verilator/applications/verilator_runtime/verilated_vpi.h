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
/// \brief Verilated VPI header
///
/// This file contains routines related to using VPI with Verilated models.
///
/// User wrapper code may need to include this if controlling Verilated
/// models that use ths VPI.
///
//=========================================================================

#ifndef VERILATOR_VERILATED_VPI_H_
#define VERILATOR_VERILATED_VPI_H_

#include "verilatedos.h"

#include "verilated.h"
#include "verilated_syms.h"

//======================================================================
// From IEEE 1800-2023 annex M

#include "vltstd/sv_vpi_user.h"

//======================================================================

/// Class for namespace-like grouping of Verilator VPI functions.

class VerilatedVpi final {
public:
    /// Call timed callbacks.
    /// User wrapper code should call this from their main loops.
    static void callTimedCbs() VL_MT_UNSAFE_ONE;
    /// Call value based callbacks.
    /// User wrapper code should call this from their main loops.
    static bool callValueCbs() VL_MT_UNSAFE_ONE;
    /// Call callbacks of arbitrary types.
    /// User wrapper code should call this from their main loops.
    static bool callCbs(uint32_t reason) VL_MT_UNSAFE_ONE;
    /// Returns true if there are callbacks of the given reason registered.
    /// User wrapper code should call this from their main loops.
    static bool hasCbs(uint32_t reason) VL_MT_UNSAFE_ONE;
    /// Returns time of the next registered VPI callback, or
    /// ~(0ULL) if none are registered
    static QData cbNextDeadline() VL_MT_UNSAFE_ONE;
    /// Debug dump of callbacks
    static void dumpCbs() VL_MT_UNSAFE_ONE;
    /// Checks VPI dirty state (i.e. whether vpi_put_value() has
    /// been called since the last clearEvalNeeded())
    static bool evalNeeded() VL_MT_UNSAFE_ONE;
    /// Clears VPI dirty state (see evalNeeded())
    static void clearEvalNeeded() VL_MT_UNSAFE_ONE;
    /// Perform inertially delayed puts
    static void doInertialPuts() VL_MT_UNSAFE_ONE;

    // Self test, for internal use only
    static void selfTest() VL_MT_UNSAFE_ONE;
};

#endif  // Guard
