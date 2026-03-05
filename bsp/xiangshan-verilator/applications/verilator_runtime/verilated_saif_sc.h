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
/// \brief Verilated tracing in SAIF format for SystemC header
///
/// User wrapper code should use this header when creating SAIF SystemC traces.
///
/// This class is not threadsafe, as the SystemC kernel is not threadsafe.
///
//=============================================================================

#ifndef VERILATOR_VERILATED_SAIF_SC_H_
#define VERILATOR_VERILATED_SAIF_SC_H_

#include "verilatedos.h"

#include "verilated_saif_c.h"
#include "verilated_sc_trace.h"

//=============================================================================
// VerilatedSaifSc
/// Trace file used to create SAIF dump for SystemC version of Verilated models. It's very similar
/// to its C version (see the class VerilatedSaifC)

class VerilatedSaifSc final : VerilatedScTraceBase, public VerilatedSaifC {
    // CONSTRUCTORS
    VL_UNCOPYABLE(VerilatedSaifSc);

public:
    VerilatedSaifSc() {
        spTrace()->set_time_unit(VerilatedScTraceBase::getScTimeUnit());
        spTrace()->set_time_resolution(VerilatedScTraceBase::getScTimeResolution());
    }

    // METHODS
    // Override VerilatedSaifC. Must be called after starting simulation.
    void open(const char* filename) override VL_MT_SAFE {
        VerilatedScTraceBase::checkScElaborationDone();
        VerilatedSaifC::open(filename);
    }

    // METHODS - for SC kernel
    // Called from SystemC kernel
    void cycle() override { VerilatedSaifC::dump(sc_core::sc_time_stamp().to_double()); }
};

#endif  // Guard
