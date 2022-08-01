/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/bootrom.h"

/// \tag::table_lookup[]

// Bootrom function: rom_table_lookup
// Returns the 32 bit pointer into the ROM if found or NULL otherwise.
typedef void *(*rom_table_lookup_fn)(uint16_t *table, uint32_t code);

// Convert a 16 bit pointer stored at the given rom address into a 32 bit pointer
#define rom_hword_as_ptr(rom_address) (void *)(uintptr_t)(*(uint16_t *)rom_address)

void *rom_func_lookup(uint32_t code) {
    rom_table_lookup_fn rom_table_lookup = (rom_table_lookup_fn) rom_hword_as_ptr(0x18);
    uint16_t *func_table = (uint16_t *) rom_hword_as_ptr(0x14);
    return rom_table_lookup(func_table, code);
}

void *rom_data_lookup(uint32_t code) {
    rom_table_lookup_fn rom_table_lookup = (rom_table_lookup_fn) rom_hword_as_ptr(0x18);
    uint16_t *data_table = (uint16_t *) rom_hword_as_ptr(0x16);
    return rom_table_lookup(data_table, code);
}
/// \end::table_lookup[]

bool rom_funcs_lookup(uint32_t *table, unsigned int count) {
    bool ok = true;
    for (unsigned int i = 0; i < count; i++) {
        table[i] = (uintptr_t) rom_func_lookup(table[i]);
        if (!table[i]) ok = false;
    }
    return ok;
}
