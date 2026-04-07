#include <cstdint>
#include <cstdio>

#include "args.h"
#include "common.h"
#include "dut.h"
#include "xiangshan_emu_rtthread.h"

namespace {

const char *kRtThreadXiangShanProgramName = "rtthread-xiangshan";

extern "C" {
extern const unsigned char xiangshan_hello_bin_start[];
extern const unsigned char xiangshan_hello_bin_end[];
}

const char *embedded_hello_image() {
    static char image_spec[64];
    static bool initialized = false;

    if (!initialized) {
        uintptr_t start = reinterpret_cast<uintptr_t>(xiangshan_hello_bin_start);
        uintptr_t end = reinterpret_cast<uintptr_t>(xiangshan_hello_bin_end);
        unsigned long image_addr = static_cast<unsigned long>(start);
        unsigned long image_size = static_cast<unsigned long>(end - start);

        std::snprintf(image_spec, sizeof(image_spec), "wim@%lx+%lx", image_addr, image_size);
        initialized = true;
    }

    return image_spec;
}

CommonArgs build_rtthread_args() {
    CommonArgs args;
    args.enable_diff = false;
    args.enable_waveform = false;
    args.enable_waveform_full = false;
    args.enable_snapshot = false;
    args.enable_fork = false;
    args.force_dump_result = false;
    args.image = embedded_hello_image();
    args.ram_size = "16MB";
    args.flash_bin = nullptr;
    return args;
}

int run_xiangshan_emulator() {
    common_init_without_assertion(kRtThreadXiangShanProgramName);

    Verilated::threadContextp()->threads(1);
    auto emu = new Emulator(build_rtthread_args());

    common_enable_assert();

    while (!emu->is_finished()) {
        emu->tick();
    }

    bool is_good = emu->is_good();

    delete emu;

    stats.display();
    common_finish();
    return !is_good;
}

} // namespace

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    return run_xiangshan_emulator();
}