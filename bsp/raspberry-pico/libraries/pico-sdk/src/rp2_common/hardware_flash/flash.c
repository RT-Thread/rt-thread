/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/flash.h"
#include "pico/bootrom.h"

#define FLASH_BLOCK_ERASE_CMD 0xd8

#define __compiler_barrier() asm volatile("" ::: "memory")

//-----------------------------------------------------------------------------
// Infrastructure for reentering XIP mode after exiting for programming (take
// a copy of boot2 before XIP exit). Calling boot2 as a function works because
// it accepts a return vector in LR (and doesn't trash r4-r7). Bootrom passes
// NULL in LR, instructing boot2 to enter flash vector table's reset handler.

#if !PICO_NO_FLASH

#define BOOT2_SIZE_WORDS 64

static uint32_t boot2_copyout[BOOT2_SIZE_WORDS];
static bool boot2_copyout_valid = false;

static void __no_inline_not_in_flash_func(flash_init_boot2_copyout)() {
    if (boot2_copyout_valid)
        return;
    for (int i = 0; i < BOOT2_SIZE_WORDS; ++i)
        boot2_copyout[i] = ((uint32_t *)XIP_BASE)[i];
    __compiler_barrier();
    boot2_copyout_valid = true;
}

static void __no_inline_not_in_flash_func(flash_enable_xip_via_boot2)() {
    ((void (*)(void))boot2_copyout+1)();
}

#else

static void __no_inline_not_in_flash_func(flash_init_boot2_copyout)() {}

static void __no_inline_not_in_flash_func(flash_enable_xip_via_boot2)() {
    // Set up XIP for 03h read on bus access (slow but generic)
    void (*flash_enter_cmd_xip)(void) = (void(*)(void))rom_func_lookup(rom_table_code('C', 'X'));
    assert(flash_enter_cmd_xip);
    flash_enter_cmd_xip();
}

#endif

//-----------------------------------------------------------------------------
// Actual flash programming shims (work whether or not PICO_NO_FLASH==1)

void __no_inline_not_in_flash_func(flash_range_erase)(uint32_t flash_offs, size_t count) {
#ifdef PICO_FLASH_SIZE_BYTES
    hard_assert(flash_offs + count <= PICO_FLASH_SIZE_BYTES);
#endif
    invalid_params_if(FLASH, flash_offs & (FLASH_SECTOR_SIZE - 1));
    invalid_params_if(FLASH, count & (FLASH_SECTOR_SIZE - 1));
    void (*connect_internal_flash)(void) = (void(*)(void))rom_func_lookup(rom_table_code('I', 'F'));
    void (*flash_exit_xip)(void) = (void(*)(void))rom_func_lookup(rom_table_code('E', 'X'));
    void (*flash_range_erase)(uint32_t, size_t, uint32_t, uint8_t) =
        (void(*)(uint32_t, size_t, uint32_t, uint8_t))rom_func_lookup(rom_table_code('R', 'E'));
    void (*flash_flush_cache)(void) = (void(*)(void))rom_func_lookup(rom_table_code('F', 'C'));
    assert(connect_internal_flash && flash_exit_xip && flash_range_erase && flash_flush_cache);
    flash_init_boot2_copyout();

    // No flash accesses after this point
    __compiler_barrier();

    connect_internal_flash();
    flash_exit_xip();
    flash_range_erase(flash_offs, count, FLASH_BLOCK_SIZE, FLASH_BLOCK_ERASE_CMD);
    flash_flush_cache(); // Note this is needed to remove CSn IO force as well as cache flushing
    flash_enable_xip_via_boot2();
}

void __no_inline_not_in_flash_func(flash_range_program)(uint32_t flash_offs, const uint8_t *data, size_t count) {
#ifdef PICO_FLASH_SIZE_BYTES
    hard_assert(flash_offs + count <= PICO_FLASH_SIZE_BYTES);
#endif
    invalid_params_if(FLASH, flash_offs & (FLASH_PAGE_SIZE - 1));
    invalid_params_if(FLASH, count & (FLASH_PAGE_SIZE - 1));
    void (*connect_internal_flash)(void) = (void(*)(void))rom_func_lookup(rom_table_code('I', 'F'));
    void (*flash_exit_xip)(void) = (void(*)(void))rom_func_lookup(rom_table_code('E', 'X'));
    void (*flash_range_program)(uint32_t, const uint8_t*, size_t) =
        (void(*)(uint32_t, const uint8_t*, size_t))rom_func_lookup(rom_table_code('R', 'P'));
    void (*flash_flush_cache)(void) = (void(*)(void))rom_func_lookup(rom_table_code('F', 'C'));
    assert(connect_internal_flash && flash_exit_xip && flash_range_program && flash_flush_cache);
    flash_init_boot2_copyout();

    __compiler_barrier();

    connect_internal_flash();
    flash_exit_xip();
    flash_range_program(flash_offs, data, count);
    flash_flush_cache(); // Note this is needed to remove CSn IO force as well as cache flushing
    flash_enable_xip_via_boot2();
}
