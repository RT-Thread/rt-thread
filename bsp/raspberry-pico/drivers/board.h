/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

#define PICO_SRAM_SIZE         256
#define PICO_SRAM_END          (0x20000000 + PICO_SRAM_SIZE * 1024)

extern int __bss_end__;
#define HEAP_BEGIN      (&__bss_end__)
#define HEAP_END        ((void *)PICO_SRAM_END)

int rt_hw_uart_init(void);

#endif
