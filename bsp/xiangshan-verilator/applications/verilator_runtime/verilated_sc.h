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
//*************************************************************************
///
/// \file
/// \brief Verilated SystemC header for all Verilated SystemC files
///
/// This file is included automatically by Verilator at the top of all
/// SystemC files it generates.  It contains functions Verilated code uses
/// internally to connect the Verilated model into SystemC.
///
/// User wrapper code is not required to include nor use anything in this
/// header, but may prefer to include it in place of "verilated.h" when
/// using Verilator with SystemC.
///
//*************************************************************************

#ifndef VERILATOR_VERILATED_SC_H_
#define VERILATOR_VERILATED_SC_H_

#include "verilatedos.h"

#include <systemc>

//=============================================================================
// For \internal use, get a pointer to m_data in the sc_bv_base class,
// getting around that it is protected.  So make an exposing class, then
// use cast magic to get at it.  Saves patching get_datap in SystemC.
#define VL_SC_BV_DATAP(bv) (VlScBvExposer::sp_datap(bv))
// This class is thread safe (though most of SystemC is not).
class VlScBvExposer final : public sc_dt::sc_bv_base {
public:
    static const uint32_t* sp_datap(const sc_dt::sc_bv_base& base) VL_MT_SAFE {
        return static_cast<const VlScBvExposer*>(&base)->sp_datatp();
    }
    const uint32_t* sp_datatp() const { return reinterpret_cast<uint32_t*>(m_data); }
    // Above reads this protected element in sc_bv_base:
    //   sc_digit* m_data; // data array
};

//=========================================================================

#endif  // Guard
