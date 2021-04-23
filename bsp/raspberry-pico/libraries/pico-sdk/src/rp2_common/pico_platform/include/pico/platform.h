/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_PLATFORM_H_
#define _PICO_PLATFORM_H_

#include <sys/cdefs.h>
#include "pico/types.h"
#include "hardware/platform_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file platform.h
*  \defgroup pico_platform pico_platform
* Compiler definitions for the selected PICO_PLATFORM
*/

#define __isr

#define __not_in_flash(group) __attribute__((section(".time_critical." group)))
#define __not_in_flash_func(x) __not_in_flash(__STRING(x)) x
#define __no_inline_not_in_flash_func(x) __attribute__((noinline)) __not_in_flash_func(x)

// For use with PICO_COPY_TO_RAM:
#define __in_flash(group) __attribute__((section(".flashdata" group)))

#define __scratch_x(group) __attribute__((section(".scratch_x." group)))
#define __scratch_y(group) __attribute__((section(".scratch_y." group)))

#define __time_critical_func(x) __not_in_flash_func(x)
#define __after_data(group) __attribute__((section(".after_data." group)))
#define __packed_aligned __packed __aligned(4)

#ifndef count_of
#define count_of(a) (sizeof(a)/sizeof((a)[0]))
#endif

#ifndef MAX
#define MAX(a, b) ((a)>(b)?(a):(b))
#endif

#ifndef MIN
#define MIN(a, b) ((b)>(a)?(a):(b))
#endif

#define __uninitialized_ram(group) __attribute__((section(".uninitialized_ram." #group))) group

inline static void __breakpoint() {
    __asm__("bkpt #0");
}

// return a 32 bit handle for a raw ptr; DMA chaining for example embeds pointers in 32 bit values
// which of course does not work if we're running the code natively on a 64 bit platforms. Therefore
// we provide this macro which allows that code to provide a 64->32 bit mapping in host mode
#define host_safe_hw_ptr(x) ((uintptr_t)(x))

void __attribute__((noreturn)) panic_unsupported();

void __attribute__((noreturn)) panic(const char *fmt, ...);

bool running_on_fpga();
uint8_t rp2040_chip_version();

static inline uint8_t rp2040_rom_version() {
    return *(uint8_t*)0x13;
}

// called by any tight hardware polling loop... nominally empty, but can be modified for debugging
static inline void tight_loop_contents() {}

// return a 32 bit handle for a raw ptr; DMA chaining for example embeds pointers in 32 bit values
// which of course does not work if we're running the code natively on a 64 bit platform for testing.
// Therefore we provide this function which allows the host runtime to provide a mapping
#define native_safe_hw_ptr(x) ((uintptr_t)(x))

// multiplies a by b using multiply instruction using the ARM mul instruction regardless of values
inline static int32_t __mul_instruction(int32_t a, int32_t b) {
asm ("mul %0, %1" : "+l" (a) : "l" (b) : );
return a;
}

#define WRAPPER_FUNC(x) __wrap_ ## x
#define REAL_FUNC(x) __real_ ## x

// macro to multiply value a by possibly constant value b
// if b is known to be constant and not zero or a power of 2, then a mul instruction is used rather than gcc's default
#define __fast_mul(a, b) __builtin_choose_expr(__builtin_constant_p(b) && !__builtin_constant_p(a), \
(__builtin_popcount(b) >= 2 ? __mul_instruction(a,b) : (a)*(b)), \
(a)*(b))

#define __check_type_compatible(type_a, type_b) static_assert(__builtin_types_compatible_p(type_a, type_b), __STRING(type_a) " is not compatible with " __STRING(type_b));
#ifdef __cplusplus
}
#endif
#endif
