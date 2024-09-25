/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/sbi_error.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/timer/fdt_timer.h>
#include <sbi_utils/sys/clint.h>

#define CLINT_TIMER_MAX_NR			16

static unsigned long clint_timer_count = 0;
static struct clint_data clint_timer[CLINT_TIMER_MAX_NR];

static int timer_clint_cold_init(void *fdt, int nodeoff,
				  const struct fdt_match *match)
{
	int rc;
	struct clint_data *ct, *ctmaster = NULL;

	if (CLINT_TIMER_MAX_NR <= clint_timer_count)
		return SBI_ENOSPC;
	ct = &clint_timer[clint_timer_count++];
	if (1 < clint_timer_count)
		ctmaster = &clint_timer[0];

	rc = fdt_parse_clint_node(fdt, nodeoff, TRUE, ct);
	if (rc)
		return rc;

	return clint_cold_timer_init(ct, ctmaster);
}

static const struct fdt_match timer_clint_match[] = {
	{ .compatible = "riscv,clint0" },
	{ .compatible = "sifive,clint0" },
	{ },
};

struct fdt_timer fdt_timer_clint = {
	.match_table = timer_clint_match,
	.cold_init = timer_clint_cold_init,
	.warm_init = clint_warm_timer_init,
	.exit = NULL,
};
