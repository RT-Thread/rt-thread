/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-10     Siwei Xu     Add i.MX91 SDK
 * 2025-09-15     Siwei Xu     Fix LPUART driver
 * 2025-12-10     Siwei Xu     Fix ioremap issues
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "imx91.h"
#include "rtconfig.h"

#ifndef KERNEL_BOOT_ADDR
#define KERNEL_BOOT_ADDR (ARCH_RAM_OFFSET + ARCH_TEXT_OFFSET)
#endif

/* defined in linker script */
extern unsigned char __bss_end;

#define BOARD_PAGE_START RT_ALIGN((rt_base_t) & __bss_end, KB_SIZE(4))
#define BOARD_PAGE_END   (BOARD_PAGE_START + MB_SIZE(1))

#define BOARD_HEAP_BEGIN (BOARD_PAGE_END)
#define BOARD_HEAP_END   (BOARD_HEAP_BEGIN + MB_SIZE(32))

void rt_hw_board_init(void);

#endif
