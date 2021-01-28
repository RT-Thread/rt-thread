/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_MULTICORE_H
#define _PICO_MULTICORE_H

#include "pico/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void multicore_reset_core1();
void multicore_launch_core1(void (*entry)(void));
void multicore_launch_core1_with_stack(void (*entry)(void), uint32_t *stack_bottom, size_t stack_size_bytes);
void multicore_sleep_core1();
void multicore_launch_core1_raw(void (*entry)(void), uint32_t *sp, uint32_t vector_table);

bool multicore_fifo_rvalid();
bool multicore_fifo_wready();
void multicore_fifo_push(uint32_t data);
uint32_t multicore_fifo_pop_blocking();
void multicore_fifo_drain();
void multicore_fifo_clear_irq();
int32_t multicore_fifo_get_status();

// call this from the lockout victim thread
void multicore_lockout_victim_init();

// start locking out the other core (it will be
bool multicore_lockout_start_timeout_us(uint64_t timeout_us);
void multicore_lockout_start_blocking();

bool multicore_lockout_end_timeout_us(uint64_t timeout_us);
void multicore_lockout_end_blocking();

#ifdef __cplusplus
}
#endif

#endif
