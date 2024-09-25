/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SYS_CLINT_H__
#define __SYS_CLINT_H__

#include <sbi/sbi_types.h>

struct clint_data {
	/* Public details */
	unsigned long addr;
	u32 first_hartid;
	u32 hart_count;
	bool has_64bit_mmio;
	/* Private details (initialized and used by CLINT library)*/
	u32 *ipi;
	struct clint_data *time_delta_reference;
	unsigned long time_delta_computed;
	u64 time_delta;
	u64 *time_val;
	u64 *time_cmp;
	u64 (*time_rd)(volatile u64 *addr);
	void (*time_wr)(u64 value, volatile u64 *addr);
};

int clint_warm_ipi_init(void);

int clint_cold_ipi_init(struct clint_data *clint);

int clint_warm_timer_init(void);

int clint_cold_timer_init(struct clint_data *clint,
			  struct clint_data *reference);

#endif
