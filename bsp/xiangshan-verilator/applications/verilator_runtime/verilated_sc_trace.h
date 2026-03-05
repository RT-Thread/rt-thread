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
/// \brief Verilated tracing for SystemC implementation code
///
///
///
//=============================================================================

#ifndef VERILATOR_VERILATED_SC_TRACE_H_
#define VERILATOR_VERILATED_SC_TRACE_H_

#include "verilatedos.h"

#include "verilated.h"
#include "verilated_sc.h"

#if SYSTEMC_VERSION >= 20140417 && SYSTEMC_VERSION < 20231124
// SystemC's simulation phase callback introduced in 2.3.1, and removed since 3.0.0 (PubRev)
#define _VL_HAVE_SYSTEMC_PHASE_CALLBACK
#endif
#if SYSTEMC_VERSION >= 20231124
// SystemC's stage callback introduced in 3.0.0 (PubRev)
#define _VL_HAVE_SYSTEMC_STAGE_CALLBACK
#endif

//=============================================================================
// VerilatedScTraceBase
// Base class for VCD/FST trace format on SystemC
// This is an internally used class - see VerilatedVcdSc and VerilatedFstSc for what to call from
// applications
//
/// This class utilizes SystemC's callbacks, which allows to dump signals inside the Verilated
/// module automatically as time advances.
///
/// For SystemC prior to 2.3.1, the only approach for being notified after each update is by adding
/// a trace file (sc_trace_file) to the simulation context. And after this version the simulation
/// phase callback approach has been introduced (sc_trace_file also utilizes this), which is
/// presented only if it's enabled with the `--enable-phase-callbacks` option. However, when it's
/// enabled with `--enable-phase-callbacks=tracing`, trace files will be therefore disabled, thus
/// failing to provide its functionality.
///
/// To provide a universal way for tracing, the class attempts to register a phase callback first.
/// If it fails (proving that the feature has been disabled), it'll use the trace file approach
/// instead.

class VerilatedScTraceBase VL_NOT_FINAL : private sc_core::sc_object,
#ifdef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
                                          private sc_core::sc_stage_callback_if,
#endif
                                          private sc_core::sc_trace_file {
    bool m_enableDeltaCycles = false;
    bool m_traceFileAdded = false;
    static void stubReportHandler(const sc_core::sc_report&, const sc_core::sc_actions&) {};

public:
    void enableDeltaCycles(bool flag = true) {
        using namespace sc_core;
#ifdef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
        // Save old report handler before overriding it
        const auto oldHandler = sc_report_handler::get_handler();
        // Override the old handler to hide 'phase callbacks not enabled' message
        sc_report_handler::set_handler(&stubReportHandler);
        if (flag) {
            // Register simulation phase callback for delta cycles
            sc_object::register_simulation_phase_callback(SC_END_OF_UPDATE);
        } else {
            sc_object::unregister_simulation_phase_callback(SC_END_OF_UPDATE);
        }
        // Restore the old handler
        sc_report_handler::set_handler(oldHandler);
#endif
#ifdef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
        if (flag) {
            sc_register_stage_callback(*this, SC_POST_UPDATE);
        } else {
            sc_unregister_stage_callback(*this, SC_POST_UPDATE);
        }
#endif
        m_enableDeltaCycles = flag;
    }

protected:
    VerilatedScTraceBase()
        : sc_object(sc_core::sc_gen_unique_name("$$$$verilator_sc_trace$$$$"))
        , sc_trace_file() {
        registerTraceCallback();
    };
    ~VerilatedScTraceBase() override {
        using namespace sc_core;
#ifdef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
        // remove_trace_file added in 2.3.1 and removed in 3.0.0
        // Phase callback is automatically unregistered in ~sc_object(). Only the trace file is
        // needed to be removed here
        if (m_traceFileAdded) simcontext()->remove_trace_file(this);
#else
        (void)m_traceFileAdded;
#endif
#ifdef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
        sc_unregister_stage_callback(*this, SC_PRE_TIMESTEP | SC_POST_UPDATE);
#endif
    };
    void registerTraceCallback() {
        using namespace sc_core;
#ifdef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
        // Save old report handler before overriding it
        const auto oldHandler = sc_report_handler::get_handler();
        // Override the old handler to hide 'phase callbacks not enabled' message
        sc_report_handler::set_handler(&stubReportHandler);
        // Register regular simulation phase (non-delta cycle) callback
        phase_cb_mask cb_mask = sc_object::register_simulation_phase_callback(SC_BEFORE_TIMESTEP);
        if (cb_mask == SC_UNITIALIZED) {
#endif
#if SYSTEMC_VERSION < 20231124  // add_trace_file removed in 3.0.0
            // Phase callback not enabled, use trace file instead
            simcontext()->add_trace_file(this);
            m_traceFileAdded = true;
#endif
#ifdef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
        }
        // Restore the old handler
        sc_report_handler::set_handler(oldHandler);
#endif
#ifdef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
        sc_register_stage_callback(*this, SC_PRE_TIMESTEP);
#endif
    }
    static std::string getScTimeUnit() {
        // We want to avoid a depreciated warning, but still be back compatible.
        // Turning off the message just for this still results in an
        // annoying "to turn off" message.
        const sc_core::sc_time t1sec{1, sc_core::SC_SEC};
        if (t1sec.to_default_time_units() == 0) {
            VL_FATAL_MT(__FILE__, __LINE__, "",  // LCOV_EXCL_LINE
                        "Cannot to get valid SystemC default time unit for trace file");
        }
        const sc_core::sc_time tunits{1.0 / t1sec.to_default_time_units(), sc_core::SC_SEC};
        return tunits.to_string();
    }
    static std::string getScTimeResolution() {
        return sc_core::sc_get_time_resolution().to_string();
    }
    static void checkScElaborationDone() {
        if (!sc_core::sc_get_curr_simcontext()->elaboration_done()) {
            Verilated::scTraceBeforeElaborationError();
        }
    }

    // METHODS - for SC kernel
#ifdef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
    // Override sc_object. Called if using phase callback
    void simulation_phase_callback() final { cycle(); }
#endif
#ifdef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
    // Override sc_stage_callback_if. Called if using stage callback
    void stage_callback(const sc_core::sc_stage&) final { cycle(); }
#endif
    // Override sc_trace_file. Called if using trace file
    void cycle(bool delta_cycle) final {
        if (!delta_cycle || m_enableDeltaCycles) cycle();
    }
    // METHODS - callbacks
    // Subclasses should implement this callback method
    virtual void cycle() = 0;

private:
    // METHODS - Fake outs for linker
    // LCOV_EXCL_START

#ifdef NC_SYSTEMC
    // Cadence Incisive has these as abstract functions so we must create them
    void set_time_unit(int exponent10_seconds) override {}  // deprecated
#endif
    void set_time_unit(double v, sc_core::sc_time_unit tu) override {}

    //--------------------------------------------------
    // SystemC 2.1.v1

    void write_comment(const std::string&) override {}
    void trace(sc_core::sc_trace_file*) const override {}
    void trace(const unsigned int&, const std::string&, const char**) override {}

#define DECL_TRACE_METHOD_A(tp) \
    void trace(const tp& object, const std::string& name) override {}
#define DECL_TRACE_METHOD_B(tp) \
    void trace(const tp& object, const std::string& name, int width) override {}

    // clang-format off
    // Formatting matches that of sc_trace.h
#if SYSTEMC_VERSION >= 20171012  // SystemC >= 2.3.2
    DECL_TRACE_METHOD_A( sc_core::sc_event )
    DECL_TRACE_METHOD_A( sc_core::sc_time )
#endif

    DECL_TRACE_METHOD_A( bool )
    DECL_TRACE_METHOD_A( sc_dt::sc_bit )
    DECL_TRACE_METHOD_A( sc_dt::sc_logic )

    DECL_TRACE_METHOD_B( unsigned char )
    DECL_TRACE_METHOD_B( unsigned short )
    DECL_TRACE_METHOD_B( unsigned int )
    DECL_TRACE_METHOD_B( unsigned long )
    DECL_TRACE_METHOD_B( char )
    DECL_TRACE_METHOD_B( short )
    DECL_TRACE_METHOD_B( int )
    DECL_TRACE_METHOD_B( long )
    DECL_TRACE_METHOD_B( sc_dt::int64 )
    DECL_TRACE_METHOD_B( sc_dt::uint64 )

    DECL_TRACE_METHOD_A( float )
    DECL_TRACE_METHOD_A( double )
    DECL_TRACE_METHOD_A( sc_dt::sc_int_base )
    DECL_TRACE_METHOD_A( sc_dt::sc_uint_base )
    DECL_TRACE_METHOD_A( sc_dt::sc_signed )
    DECL_TRACE_METHOD_A( sc_dt::sc_unsigned )

    DECL_TRACE_METHOD_A( sc_dt::sc_fxval )
    DECL_TRACE_METHOD_A( sc_dt::sc_fxval_fast )
    DECL_TRACE_METHOD_A( sc_dt::sc_fxnum )
    DECL_TRACE_METHOD_A( sc_dt::sc_fxnum_fast )

    DECL_TRACE_METHOD_A( sc_dt::sc_bv_base )
    DECL_TRACE_METHOD_A( sc_dt::sc_lv_base )
    // LCOV_EXCL_STOP
    // clang-format on

#undef DECL_TRACE_METHOD_A
#undef DECL_TRACE_METHOD_B
};

#ifdef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
#undef _VL_HAVE_SYSTEMC_PHASE_CALLBACK
#endif
#ifdef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
#undef _VL_HAVE_SYSTEMC_STAGE_CALLBACK
#endif

#endif  // Guard
