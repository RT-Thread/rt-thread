/*
 * RT-Thread-specific Emulator implementation.
 *
 * This is a stripped-down version of XiangShan's emu.cpp that removes
 * lightsss, getopt, sys/resource, fork, and snapshot dependencies.
 * It lives in the BSP so that the XiangShan source tree stays unmodified.
 *
 * Based on: XiangShan/difftest/src/test/csrc/emu/emu.cpp
 */

#include "xiangshan_emu_rtthread.h"
#include "compress.h"
#include "device.h"
#include "flash.h"
#include "ram.h"
#include "remote_bitbang.h"
#include "sdcard.h"
#include <signal.h>
#ifndef CONFIG_NO_DIFFTEST
#include "difftest.h"
#include "goldenmem.h"
#include "refproxy.h"
#endif // CONFIG_NO_DIFFTEST
#ifdef ENABLE_CHISEL_DB
#include "chisel_db.h"
#endif

extern remote_bitbang_t *jtag;

namespace {

const char *default_emu_argv[] = {"rtthread-xiangshan"};

inline void normalize_emu_argv(int &argc, const char **&argv) {
  if (argc <= 0 || argv == nullptr) {
    argc = 1;
    argv = default_emu_argv;
  }
}

} // namespace

Emulator::Emulator(const CommonArgs &fixed_args, int argc, const char *argv[])
    : dut_ptr(new SIMULATOR), cycles(0), trapCode(STATE_RUNNING), elapsed_time(uptime()) {

  normalize_emu_argv(argc, argv);
  initialize(fixed_args, argc, argv);
}

void Emulator::initialize(const CommonArgs &initial_args, int argc, const char *argv[]) {

  normalize_emu_argv(argc, argv);

  args = initial_args;
#ifdef VERILATOR
  Verilated::commandArgs(argc, argv); // Prepare extra args for TLMonitor
#endif

#ifdef VERILATOR
  // srand
  srand(args.seed);
  srand48(args.seed);
  Verilated::randSeed(args.seed);
  Verilated::randReset(2);
#endif // VERILATOR

  // init remote-bitbang
  if (enable_simjtag) {
    jtag_init();
  }
  // init flash
  init_flash(args.flash_bin);

  if (args.enable_waveform) {
    uint64_t waveform_clock = args.enable_waveform_full ? 2 * args.log_begin : args.log_begin;
    if (args.wave_path != NULL) {
      dut_ptr->waveform_init(waveform_clock, args.wave_path);
    } else {
      dut_ptr->waveform_init(waveform_clock);
    }
  }

  // init core
  reset_ncycles(args.reset_cycles);

  // init ram
  uint64_t ram_size = DEFAULT_EMU_RAM_SIZE;
  if (args.ram_size) {
    ram_size = parse_ramsize(args.ram_size);
  }
  // footprints
  if (args.image_as_footprints) {
    if (args.linearized_name) {
      simMemory = new LinearizedFootprintsMemory(args.image, ram_size, args.linearized_name);
    } else {
      simMemory = new FootprintsMemory(args.image, ram_size);
    }
  }
  // normal linear memory
  else {
    if (args.footprints_name) {
      simMemory = new MmapMemoryWithFootprints(args.image, ram_size, args.footprints_name);
    } else {
      init_ram(args.image, ram_size);
    }
  }

  if (args.gcpt_restore) {
    if (args.overwrite_nbytes_autoset) {
      FILE *fp = fopen(args.gcpt_restore, "rb");
      fseek(fp, 4, SEEK_SET);
      fread(&args.overwrite_nbytes, sizeof(uint32_t), 1, fp);
      fclose(fp);
    }
    overwrite_ram(args.gcpt_restore, args.overwrite_nbytes);
  }

  if (args.copy_ram_offset) {
    copy_ram(args.copy_ram_offset);
  }

#ifdef ENABLE_CHISEL_DB
  init_db(args.dump_db, (args.select_db != NULL), args.select_db);
#endif

  // set log time range and log level
  dut_ptr->set_log_begin(args.log_begin);
  dut_ptr->set_log_end(args.log_end);

#ifndef CONFIG_NO_DIFFTEST
  // init difftest
  auto ref_ramsize = args.ram_size ? simMemory->get_size() : 0;
  difftest_init(args.enable_diff, ref_ramsize);

  // init difftest traces
  if (args.trace_name) {
    for (int i = 0; i < NUM_CORES; i++) {
      difftest[i]->set_trace(args.trace_name, args.trace_is_read);
    }
  }
#endif // CONFIG_NO_DIFFTEST

  init_device();

#ifndef CONFIG_NO_DIFFTEST
#ifdef DEBUG_REFILL
  for (int i = 0; i < NUM_CORES; i++) {
    difftest[i]->set_track_instr(args.track_instr);
  }
#endif
#endif // CONFIG_NO_DIFFTEST

  for (int i = 0; i < NUM_CORES; i++) {
    core_max_instr[i] = args.max_instr;
  }

#if VM_COVERAGE == 1
  if (args.dump_coverage) {
    coverage = Verilated::threadContextp()->coveragep();
  }
#endif
}

Emulator::~Emulator() {
  // Simulation ends here, do clean up & display jobs

#if VM_COVERAGE == 1
  if (args.dump_coverage) {
    save_coverage();
  }
#endif

  // warning: this function may still simulate the circuit
  // simulator resources must be released after this function
  display_stats();

#ifndef CONFIG_NO_DIFFTEST
  stats.update(difftest[0]->dut);
#endif // CONFIG_NO_DIFFTEST

  simMemory->display_stats();
  delete simMemory;
  simMemory = nullptr;

#ifndef CONFIG_NO_DIFFTEST
  if (args.enable_diff) {
    goldenmem_finish();
  }
#endif // CONFIG_NO_DIFFTEST
  flash_finish();
#ifndef CONFIG_NO_DIFFTEST
  difftest_finish();
#endif // CONFIG_NO_DIFFTEST

#ifdef ENABLE_CHISEL_DB
  if (args.dump_db) {
    save_db(logdb_filename());
  }
#endif

  elapsed_time = uptime() - elapsed_time;

  Info(ANSI_COLOR_BLUE "Seed=%d Guest cycle spent: %'" PRIu64
                       " (this will be different from cycleCnt if emu loads a snapshot)\n" ANSI_COLOR_RESET,
       args.seed, cycles);
  Info(ANSI_COLOR_BLUE "Host time spent: %'dms\n" ANSI_COLOR_RESET, elapsed_time);

  if (enable_simjtag) {
    delete jtag;
  }

  delete dut_ptr;
}

inline void Emulator::reset_ncycles(size_t cycles) {
  if (args.trace_name && args.trace_is_read) {
    return;
  }
  for (int i = 0; i < cycles; i++) {
    dut_ptr->set_reset(1);

#ifdef VERILATOR
    dut_ptr->set_clock(1);
    dut_ptr->step();
#endif // VERILATOR

    if (args.enable_waveform && args.enable_waveform_full && args.log_begin == 0) {
      dut_ptr->waveform_tick();
    }

#ifdef VERILATOR
    dut_ptr->set_clock(0);
    dut_ptr->step();
#endif // VERILATOR

    if (args.enable_waveform && args.enable_waveform_full && args.log_begin == 0) {
      dut_ptr->waveform_tick();
    }

    dut_ptr->set_reset(0);
  }
}

inline void Emulator::single_cycle() {
  if (args.trace_name && args.trace_is_read) {
    goto end_single_cycle;
  }

#ifdef VERILATOR
  dut_ptr->set_clock(1);
  dut_ptr->step();
#endif // VERILATOR

  if (args.enable_waveform) {
#if !defined(CONFIG_NO_DIFFTEST) && !defined(CONFIG_DIFFTEST_SQUASH)
    uint64_t cycle = difftest[0]->get_trap_event()->cycleCnt;
#else
    static uint64_t cycle = -1UL;
    cycle++;
#endif
    bool in_range = (args.log_begin <= cycle) && (cycle <= args.log_end);
    if (in_range || force_dump_wave) {
      dut_ptr->waveform_tick();
    }
  }

  dut_ptr->step_uart();

#ifdef VERILATOR
  dut_ptr->set_clock(0);
  dut_ptr->step();
#endif // VERILATOR

  if (args.enable_waveform && args.enable_waveform_full) {
#if !defined(CONFIG_NO_DIFFTEST) && !defined(CONFIG_DIFFTEST_MERGE)
    uint64_t cycle = difftest[0]->get_trap_event()->cycleCnt;
#else
    static uint64_t cycle = -1UL;
    cycle++;
#endif
    bool in_range = (args.log_begin <= cycle) && (cycle <= args.log_end);
    if (in_range || force_dump_wave) {
      dut_ptr->waveform_tick();
    }
  }

end_single_cycle:
  cycles++;
}

int Emulator::tick() {

  // cycle limitation
  bool exceed_cycle_limit = false;
#ifdef CONFIG_NO_DIFFTEST
  exceed_cycle_limit = !args.max_cycles;
#else
  for (int i = 0; i < NUM_CORES; i++) {
    auto trap = difftest[i]->get_trap_event();
    if (trap->cycleCnt >= args.max_cycles) {
      exceed_cycle_limit = true;
    }
  }
#endif // CONFIG_NO_DIFFTEST

  if (exceed_cycle_limit) {
    trapCode = STATE_LIMIT_EXCEEDED;
    return trapCode;
  }

  // instruction limitation
#ifndef CONFIG_NO_DIFFTEST
  for (int i = 0; i < NUM_CORES; i++) {
    auto trap = difftest[i]->get_trap_event();
    if (trap->instrCnt >= core_max_instr[i]) {
      trapCode = STATE_LIMIT_EXCEEDED;
      return trapCode;
    }
  }
#endif // CONFIG_NO_DIFFTEST
  // assertions
  if (assert_count > 0) {
    Info("The simulation stopped. There might be some assertion failed.\n");
    trapCode = STATE_ABORT;
    return trapCode;
  }
  // signals
  if (signal_num != 0) {
    trapCode = STATE_SIG;
  }

  // exit signal: non-zero exit exits the simulation. exit all 1's indicates good.
  uint64_t difftest_exit = dut_ptr->get_difftest_exit();
  if (difftest_exit) {
    if (difftest_exit == -1UL) {
      trapCode = STATE_SIM_EXIT;
    } else {
      Info("The simulation aborted via the top-level exit of 0x%lx.\n", difftest_exit);
      trapCode = STATE_ABORT;
    }
  }

  if (trapCode != STATE_RUNNING) {
    return trapCode;
  }
#ifndef CONFIG_NO_DIFFTEST
  for (int i = 0; i < NUM_CORES; i++) {
    auto trap = difftest[i]->get_trap_event();
    if (trap->instrCnt >= args.warmup_instr) {
      Info("Warmup finished. The performance counters will be dumped and then reset.\n");
      dut_ptr->set_perf_clean(1);
      dut_ptr->set_perf_dump(1);
      args.warmup_instr = -1;
    }
    if (trap->cycleCnt % args.stat_cycles == args.stat_cycles - 1) {
      dut_ptr->set_perf_clean(1);
      dut_ptr->set_perf_dump(1);
    }
    if (args.enable_ref_trace) {
      bool is_debug = difftest[i]->proxy->get_debug();
      if (trap->cycleCnt >= args.log_begin && !is_debug) {
        difftest[i]->proxy->set_debug(true);
      }
      if (trap->cycleCnt >= args.log_end && is_debug) {
        difftest[i]->proxy->set_debug(false);
      }
    }
    if (args.enable_commit_trace) {
      bool is_commit_trace = difftest[i]->get_commit_trace();
      if (trap->cycleCnt >= args.log_begin && !is_commit_trace) {
        difftest[i]->set_commit_trace(true);
      }
      if (trap->cycleCnt >= args.log_end && is_commit_trace) {
        difftest[i]->set_commit_trace(false);
      }
    }
  }
#endif // CONFIG_NO_DIFFTEST

  single_cycle();
#ifdef CONFIG_NO_DIFFTEST
  args.max_cycles--;
#endif // CONFIG_NO_DIFFTEST

  dut_ptr->set_perf_clean(0);
  dut_ptr->set_perf_dump(0);

#ifndef CONFIG_NO_DIFFTEST
  int step = 0;
  if (args.trace_name && args.trace_is_read) {
    step = 1;
    difftest_trace_read();
  } else {
    step = dut_ptr->get_difftest_step();
  }

  static uint64_t stuck_timer = 0;
  if (step) {
    stuck_timer = 0;
  } else {
    stuck_timer++;
    if (stuck_timer >= Difftest::stuck_limit) {
      Info("No difftest check for more than %lu cycles, maybe get stuck.", Difftest::stuck_limit);
      return STATE_ABORT;
    }
  }

  if (args.trace_name && !args.trace_is_read) {
    difftest_trace_write(step);
  }

  trapCode = difftest_nstep(step, args.enable_diff);

  if (trapCode != STATE_RUNNING) {
    return trapCode;
  }
#endif // CONFIG_NO_DIFFTEST

  return 0;
}

int Emulator::is_finished() {
  return
#ifdef VERILATOR
      Verilated::gotFinish() ||
#endif // VERILATOR
      trapCode != STATE_RUNNING;
}

int Emulator::is_good() {
  return is_good_trap();
}

#if VM_COVERAGE == 1
void Emulator::save_coverage() {
  const char *p = create_noop_filename(".coverage.dat");
  Info("dump coverage data to %s...\n", p);
  coverage->write(p);
}
#endif

void Emulator::trigger_stat_dump() {
  dut_ptr->set_perf_dump(1);
  if (get_args().force_dump_result) {
    dut_ptr->set_log_end(-1);
  }
  single_cycle();
}

void Emulator::display_stats() {
#ifndef CONFIG_NO_DIFFTEST
  for (int i = 0; i < NUM_CORES; i++) {
    printf("Core %d: ", i);
    uint64_t pc = difftest[i]->get_trap_event()->pc;
    switch (trapCode) {
      case STATE_GOODTRAP:
        eprintf(ANSI_COLOR_GREEN "HIT GOOD TRAP at pc = 0x%" PRIx64 "\n" ANSI_COLOR_RESET, pc);
        break;
      case STATE_BADTRAP: eprintf(ANSI_COLOR_RED "HIT BAD TRAP at pc = 0x%" PRIx64 "\n" ANSI_COLOR_RESET, pc); break;
      case STATE_ABORT: eprintf(ANSI_COLOR_RED "ABORT at pc = 0x%" PRIx64 "\n" ANSI_COLOR_RESET, pc); break;
      case STATE_LIMIT_EXCEEDED:
        eprintf(ANSI_COLOR_YELLOW "EXCEEDING CYCLE/INSTR LIMIT at pc = 0x%" PRIx64 "\n" ANSI_COLOR_RESET, pc);
        break;
      case STATE_SIG:
        eprintf(ANSI_COLOR_YELLOW "SOME SIGNAL STOPS THE PROGRAM at pc = 0x%" PRIx64 "\n" ANSI_COLOR_RESET, pc);
        break;
      case STATE_SIM_EXIT: eprintf(ANSI_COLOR_YELLOW "EXIT at pc = 0x%" PRIx64 "\n" ANSI_COLOR_RESET, pc); break;
      default: eprintf(ANSI_COLOR_RED "Unknown trap code: %d\n", trapCode);
    }

    difftest[i]->display_stats();
  }
#endif // CONFIG_NO_DIFFTEST

  if (trapCode != STATE_ABORT) {
    trigger_stat_dump();
  }
}

void Emulator::snapshot_save() {}

void Emulator::snapshot_load(const char *filename) {
  (void)filename;
}
