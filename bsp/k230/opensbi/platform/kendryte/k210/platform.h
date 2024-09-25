/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Damien Le Moal <damien.lemoal@wdc.com>
 */
#ifndef _K210_PLATFORM_H_
#define _K210_PLATFORM_H_

#include <sbi/riscv_io.h>

#define K210_HART_COUNT		2

#define K210_UART_BAUDRATE	115200

#define K210_CLK0_FREQ		26000000UL
#define K210_PLIC_NUM_SOURCES	65

/* Registers base address */
#define K210_SYSCTL_BASE_ADDR	0x50440000ULL
#define K210_UART_BASE_ADDR	0x38000000ULL
#define K210_CLINT_BASE_ADDR	0x02000000ULL
#define K210_PLIC_BASE_ADDR	0x0C000000ULL

/* Registers */
#define K210_PLL0		0x08
#define K210_CLKSEL0		0x20
#define K210_RESET		0x30

/* Register bit masks */
#define K210_RESET_MASK		0x01

static inline u32 k210_read_sysreg(u32 reg)
{
	return readl((volatile void *)(K210_SYSCTL_BASE_ADDR + reg));
}

static inline void k210_write_sysreg(u32 val, u32 reg)
{
	writel(val, (volatile void *)(K210_SYSCTL_BASE_ADDR + reg));
}

#endif /* _K210_PLATFORM_H_ */
