/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdarg.h>
#include "pico.h"

#include "hardware/regs/m0plus.h"
#include "hardware/regs/resets.h"
#include "hardware/structs/mpu.h"
#include "hardware/structs/scb.h"
#include "hardware/structs/padsbank0.h"

#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/resets.h"

#include "pico/mutex.h"
#include "pico/time.h"
#include "pico/printf.h"

#ifndef PICO_NO_RAM_VECTOR_TABLE
#define PICO_NO_RAM_VECTOR_TABLE 0
#endif

extern char __StackLimit; /* Set by linker.  */
extern void _exit(int status);

uint32_t __attribute__((section(".ram_vector_table"))) ram_vector_table[48];

// this is called for each thread since they have their own MPU
void runtime_install_stack_guard(void *stack_bottom) {
    // this is called b4 runtime_init is complete, so beware printf or assert

    // make sure no one is using the MPU yet
    if (mpu_hw->ctrl) {
        // Note that it would be tempting to change this to a panic, but it happens so early, printing is not a good idea
        __breakpoint();
    }

    uintptr_t addr = (uintptr_t) stack_bottom;
    // the minimum we can protect is 32 bytes on a 32 byte boundary, so round up which will
    // just shorten the valid stack range a tad
    addr = (addr + 31u) & ~31u;

    // mask is 1 bit per 32 bytes of the 256 byte range... clear the bit for the segment we want
    uint32_t subregion_select = 0xffu ^ (1u << ((addr >> 5u) & 7u));
    mpu_hw->ctrl = 5; // enable mpu with background default map
    mpu_hw->rbar = (addr & ~0xff) | 0x8 | 0;
    mpu_hw->rasr = 1 // enable region
                   | (0x7 << 1) // size 2^(7 + 1) = 256
                   | (subregion_select << 8)
                   | 0x10000000; // XN = disable instruction fetch; no other bits means no permissions
}

void runtime_init(void) {
    // Reset all peripherals to put system into a known state,
    // - except for QSPI pads and the XIP IO bank, as this is fatal if running from flash
    // - and the PLLs, as this is fatal if clock muxing has not been reset on this boot
    reset_block(~(
            RESETS_RESET_IO_QSPI_BITS |
            RESETS_RESET_PADS_QSPI_BITS |
            RESETS_RESET_PLL_USB_BITS |
            RESETS_RESET_PLL_SYS_BITS
    ));

    // Remove reset from peripherals which are clocked only by clk_sys and
    // clk_ref. Other peripherals stay in reset until we've configured clocks.
    unreset_block_wait(RESETS_RESET_BITS & ~(
            RESETS_RESET_ADC_BITS |
            RESETS_RESET_RTC_BITS |
            RESETS_RESET_SPI0_BITS |
            RESETS_RESET_SPI1_BITS |
            RESETS_RESET_UART0_BITS |
            RESETS_RESET_UART1_BITS |
            RESETS_RESET_USBCTRL_BITS
    ));

    // pre-init runs really early since we need it even for memcpy and divide!
    // (basically anything in aeabi that uses bootrom)

    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__preinit_array_start)();
    extern void (*__preinit_array_end)();

    // Call each function in the list.
    // We have to take the address of the symbols, as __preinit_array_start *is*
    // the first function pointer, not the address of it.
    for (void (**p)() = &__preinit_array_start; p < &__preinit_array_end; ++p) {
        (*p)();
    }

    // After calling preinit we have enough runtime to do the exciting maths
    // in clocks_init
    clocks_init();

    // Peripheral clocks should now all be running
    unreset_block_wait(RESETS_RESET_BITS);

#if !PICO_IE_26_29_UNCHANGED_ON_RESET
    // after resetting BANK0 we should disable IE on 26-29
    hw_clear_alias(padsbank0_hw)->io[26] = hw_clear_alias(padsbank0_hw)->io[27] =
            hw_clear_alias(padsbank0_hw)->io[28] = hw_clear_alias(padsbank0_hw)->io[29] = PADS_BANK0_GPIO0_IE_BITS;
#endif

    extern mutex_t __mutex_array_start;
    extern mutex_t __mutex_array_end;

    // the first function pointer, not the address of it.
    for (mutex_t *m = &__mutex_array_start; m < &__mutex_array_end; m++) {
        mutex_init(m);
    }

#if !(PICO_NO_RAM_VECTOR_TABLE || PICO_NO_FLASH)
    __builtin_memcpy(ram_vector_table, (uint32_t *) scb_hw->vtor, sizeof(ram_vector_table));
    scb_hw->vtor = (intptr_t) ram_vector_table;
#endif

#ifndef NDEBUG
    uint32_t xpsr;
    __asm volatile ("mrs %0, XPSR" : "=r" (xpsr)::);
    if (xpsr & 0xffu) {
        // crap; started in exception handler
        __asm ("bkpt #0");
    }
#endif

#if PICO_USE_STACK_GUARDS
    // install core0 stack guard
    extern char __StackBottom;
    runtime_install_stack_guard(&__StackBottom);
#endif

    spin_locks_reset();
    irq_init_priorities();
}

// exit is not useful... no desire to pull in __call_exitprocs
// void exit(int status) {
//     _exit(status);
// }

// incorrect warning from GCC 6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
void __assert_func(const char *file, int line, const char *func, const char *failedexpr) {
    weak_raw_printf("assertion \"%s\" failed: file \"%s\", line %d%s%s\n",
           failedexpr, file, line, func ? ", function: " : "",
           func ? func : "");

    _exit(1);
}

#pragma GCC diagnostic pop

void __attribute__((noreturn)) panic_unsupported() {
    panic("not supported");
}

// todo consider making this try harder to output if we panic early
//  right now, print mutex may be uninitialised (in which case it deadlocks - although after printing "PANIC")
//  more importantly there may be no stdout/UART initialized yet
// todo we may want to think about where we print panic messages to; writing to USB appears to work
//  though it doesn't seem like we can expect it to... fine for now
//
void __attribute__((noreturn)) __printflike(1, 0) panic(const char *fmt, ...) {
    puts("\n*** PANIC ***\n");
    if (fmt) {
#if PICO_PRINTF_NONE
        puts(fmt);
#else
        va_list args;
        va_start(args, fmt);
#if PICO_PRINTF_ALWAYS_INCLUDED
        vprintf(fmt, args);
#else
        weak_raw_vprintf(fmt, args);
#endif
        va_end(args);
        puts("\n");
#endif
    }

    _exit(1);
}

void hard_assertion_failure(void) {
    panic("Hard assert");
}
