/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_PLATFORM_DEFS_H
#define _HARDWARE_PLATFORM_DEFS_H

// This header is included from C and assembler - only define macros

#include "hardware/regs/addressmap.h"

#define NUM_CORES 2u
#define NUM_DMA_CHANNELS 12u
#define NUM_IRQS 32u
#define NUM_PIOS 2u
#define NUM_PIO_STATE_MACHINES 4u
#define NUM_PWM_SLICES 8u
#define NUM_SPIN_LOCKS 32u
#define NUM_UARTS 2u
#define NUM_BANK0_GPIOS 30u

#define PIO_INSTRUCTION_COUNT 32u

#define XOSC_MHZ 12u

// PICO_CONFIG: PICO_STACK_SIZE, Stack Size, min=0x100, default=0x800, advanced=true, group=pico_standard_link
#ifndef PICO_STACK_SIZE
#define PICO_STACK_SIZE 0x800u
#endif

// PICO_CONFIG: PICO_HEAP_SIZE, Heap size to reserve, min=0x100, default=0x800, advanced=true, group=pico_standard_link
#ifndef PICO_HEAP_SIZE
#define PICO_HEAP_SIZE 0x800
#endif

// PICO_CONFIG: PICO_NO_RAM_VECTOR_TABLE, Enable/disable the RAM vector table, type=bool, default=0, advanced=true, group=pico_runtime
#ifndef PICO_NO_RAM_VECTOR_TABLE
#define PICO_NO_RAM_VECTOR_TABLE 0
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif

#endif

