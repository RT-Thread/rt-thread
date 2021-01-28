/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

#define PICO_SRAM_SIZE         256
#define PICO_SRAM_END          (0x20000000 + PICO_SRAM_SIZE * 1024)

extern int __bss_end;
#define HEAP_BEGIN      (&__bss_end)
#define HEAP_END        PICO_SRAM_END

int rt_hw_uart_init(void);

#endif
