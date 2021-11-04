//See LICENSE for license details.
#include <stdint.h>
#include <stdio.h>
#include "riscv_encoding.h"
#include "n22_func.h"
#include <rtthread.h>

__attribute__((weak))  uintptr_t handle_nmi() {
    rt_kprintf("nmi\n");
    return 0;
}

__attribute__((weak))  uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp) {
    if (mcause == 0xFFF) {
        handle_nmi();
    }
    rt_kprintf("trap\n");
    return 0;
}

