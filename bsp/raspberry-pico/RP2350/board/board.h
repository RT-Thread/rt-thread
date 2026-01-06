/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define PICO_SRAM_SIZE         520
#define PICO_SRAM_END          (0x20000000 + PICO_SRAM_SIZE * 1024)

extern int _sstack;
#define HEAP_BEGIN      (&_sstack)
#define HEAP_END        ((void *)PICO_SRAM_END)

#endif
