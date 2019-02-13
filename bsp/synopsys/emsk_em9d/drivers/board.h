/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "emsk_hardware.h"

#define BOARD_OS_TIMER_ID       0
#define BOARD_OS_TIMER_INTNO    16
#define BOARD_CPU_CLOCK         25000000

#if defined(__GNUC__)
extern int __start_heap;
#define HEAP_BEGIN      ((void*)&__start_heap)
#endif

extern int __end_heap;
#define HEAP_END        (void*)(&__end_heap)

void rt_hw_board_init();

int rt_hw_uart_init(void);

#endif
