// -*- mode: C++; c-file-style: "cc-mode" -*-
//=============================================================================
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
/// \brief Verilated tracing in FST format for SystemC header
///
/// User wrapper code should use this header when creating FST SystemC traces.
///
/// This class is not threadsafe, as the SystemC kernel is not threadsafe.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_FST_SC_H_
#define VERILATOR_VERILATED_FST_SC_H_

#include "verilatedos.h"

#include "verilated_fst_c.h"
#include "verilated_sc_trace.h"

//=============================================================================
// VerilatedFstSc
/// Trace file used to create FST dump for SystemC version of Verilated models. It's very similar
/// to its C version (see the class VerilatedFstC)

class VerilatedFstSc final : VerilatedScTraceBase, public VerilatedFstC {
    // CONSTRUCTORS
    VL_UNCOPYABLE(VerilatedFstSc);

public:
    VerilatedFstSc() {
        spTrace()->set_time_unit(VerilatedScTraceBase::getScTimeUnit());
        spTrace()->set_time_resolution(VerilatedScTraceBase::getScTimeResolution());
    }

    // METHODS
    // Override VerilatedFstC. Must be called after starting simulation.
    void open(const char* filename) override VL_MT_SAFE {
        VerilatedScTraceBase::checkScElaborationDone();
        VerilatedFstC::open(filename);
    }

    // METHODS - for SC kernel
    // Called from SystemC kernel
    void cycle() override { VerilatedFstC::dump(sc_core::sc_time_stamp().to_double()); }
};

#endif  // Guard
