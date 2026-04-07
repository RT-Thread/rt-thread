/*
 * RT-Thread-specific Emulator wrapper.
 *
 * This is a stripped-down version of XiangShan's emu.h that removes
 * lightsss (fork-based snapshot), getopt, and sys/resource dependencies.
 * It lives in the BSP so that the XiangShan source tree stays unmodified.
 */

#ifndef __XIANGSHAN_EMU_RTTHREAD_H
#define __XIANGSHAN_EMU_RTTHREAD_H

#include "args.h"
#include "common.h"
#include "dut.h"
#include "simulator.h"
#include <sys/types.h>

class LightSSS;

class Emulator final : public DUT {
private:
  Simulator *dut_ptr;

  bool force_dump_wave = false;
  CommonArgs args;
  LightSSS *lightsss = NULL;
#if VM_COVERAGE == 1
  VerilatedCovContext *coverage = NULL;
#endif // VM_COVERAGE

  // emu control variable
  uint64_t cycles;
  int trapCode;
  uint32_t lasttime_snapshot = 0;
  uint64_t core_max_instr[NUM_CORES];
  uint32_t lasttime_poll = 0;
  uint32_t elapsed_time;

  void initialize(const CommonArgs &initial_args, int argc, const char *argv[]);

  inline void reset_ncycles(size_t cycles);
  inline void single_cycle();
  void trigger_stat_dump();
  void display_stats();

  inline const char *logdb_filename() {
    return create_noop_filename(".db");
  }

  void snapshot_save();
  void snapshot_load(const char *filename);

  inline const char *waveform_filename() {
#ifdef ENABLE_FST
    const char *filename = create_noop_filename(".fst");
#else
    const char *filename = create_noop_filename(".vcd");
#endif
    Info("dump wave to %s...\n", filename);
    return filename;
  }

  const char *cycle_wavefile(uint64_t cycles);

#if VM_COVERAGE == 1
  void save_coverage();
#endif

  void fork_child_init() {}
  inline bool is_fork_child() { return false; }

public:
  explicit Emulator(const CommonArgs &fixed_args, int argc = 0, const char *argv[] = nullptr);
  ~Emulator();
  uint64_t execute(uint64_t max_cycle, uint64_t max_instr);
  uint64_t get_cycles() const {
    return cycles;
  }
  CommonArgs get_args() const {
    return args;
  }
  bool is_good_trap() {
#ifdef FUZZING
    return !(trapCode == STATE_ABORT);
#else
    return trapCode == STATE_GOODTRAP || trapCode == STATE_LIMIT_EXCEEDED || trapCode == STATE_SIM_EXIT;
#endif
  };
  int get_trapcode() {
    return trapCode;
  }
  int tick();
  int is_finished();
  int is_good();
};

#endif
