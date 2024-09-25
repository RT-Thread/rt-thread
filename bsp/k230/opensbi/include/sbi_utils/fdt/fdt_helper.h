// SPDX-License-Identifier: BSD-2-Clause
/*
 * fdt_helper.h - Flat Device Tree parsing helper routines
 * Implement helper routines to parse FDT nodes on top of
 * libfdt for OpenSBI usage
 *
 * Copyright (C) 2020 Bin Meng <bmeng.cn@gmail.com>
 */

#ifndef __FDT_HELPER_H__
#define __FDT_HELPER_H__

#include <sbi/sbi_types.h>

struct fdt_match {
	const char *compatible;
	void *data;
};

struct platform_uart_data {
	unsigned long addr;
	unsigned long freq;
	unsigned long baud;
	unsigned long reg_shift;
	unsigned long reg_io_width;
};

const struct fdt_match *fdt_match_node(void *fdt, int nodeoff,
				       const struct fdt_match *match_table);

int fdt_find_match(void *fdt, int startoff,
		   const struct fdt_match *match_table,
		   const struct fdt_match **out_match);

int fdt_get_node_addr_size(void *fdt, int node, unsigned long *addr,
			   unsigned long *size);

int fdt_parse_hart_id(void *fdt, int cpu_offset, u32 *hartid);

int fdt_parse_max_hart_id(void *fdt, u32 *max_hartid);

int fdt_parse_shakti_uart_node(void *fdt, int nodeoffset,
			       struct platform_uart_data *uart);

int fdt_parse_sifive_uart_node(void *fdt, int nodeoffset,
			       struct platform_uart_data *uart);

int fdt_parse_uart8250_node(void *fdt, int nodeoffset,
			    struct platform_uart_data *uart);

int fdt_parse_uart8250(void *fdt, struct platform_uart_data *uart,
		       const char *compatible);

struct plic_data;

int fdt_parse_plic_node(void *fdt, int nodeoffset, struct plic_data *plic);

int fdt_parse_plic(void *fdt, struct plic_data *plic, const char *compat);

struct clint_data;

int fdt_parse_clint_node(void *fdt, int nodeoffset, bool for_timer,
			 struct clint_data *clint);

int fdt_parse_compat_addr(void *fdt, unsigned long *addr,
			  const char *compatible);

#endif /* __FDT_HELPER_H__ */
