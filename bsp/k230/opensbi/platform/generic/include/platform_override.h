/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __PLATFORM_OVERRIDE_H__
#define __PLATFORM_OVERRIDE_H__

#include <sbi/sbi_types.h>

struct platform_override {
	const struct fdt_match *match_table;
	u64 (*features)(const struct fdt_match *match);
	u64 (*tlbr_flush_limit)(const struct fdt_match *match);
	int (*early_init)(bool cold_boot, const struct fdt_match *match);
	int (*final_init)(bool cold_boot, const struct fdt_match *match);
	void (*early_exit)(const struct fdt_match *match);
	void (*final_exit)(const struct fdt_match *match);
	int (*fdt_fixup)(void *fdt, const struct fdt_match *match);
};

#endif
