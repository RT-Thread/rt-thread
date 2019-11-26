//See LICENSE for license details.
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "riscv_encoding.h"
#include "n22_func.h"
__attribute__((weak))  uintptr_t handle_nmi() {
    write(1, "nmi\n", 5);
    _exit(1);
    return 0;
}

__attribute__((weak))  uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp) {
    if (mcause == 0xFFF) {
        handle_nmi();
    }
    write(1, "trap\n", 5);
    _exit(mcause);
    return 0;
}

