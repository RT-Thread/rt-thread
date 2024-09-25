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
#include <sbi_utils/ipi/fdt_ipi.h>
#include <sbi_utils/sys/clint.h>

#define CLINT_IPI_MAX_NR			16

static unsigned long clint_ipi_count = 0;
static struct clint_data clint_ipi[CLINT_IPI_MAX_NR];

static int ipi_clint_cold_init(void *fdt, int nodeoff,
			       const struct fdt_match *match)
{
	int rc;
	struct clint_data *ci;

	if (CLINT_IPI_MAX_NR <= clint_ipi_count)
		return SBI_ENOSPC;
	ci = &clint_ipi[clint_ipi_count++];

	rc = fdt_parse_clint_node(fdt, nodeoff, FALSE, ci);
	if (rc)
		return rc;

	return clint_cold_ipi_init(ci);
}

static const struct fdt_match ipi_clint_match[] = {
	{ .compatible = "riscv,clint0" },
	{ .compatible = "sifive,clint0" },
	{ },
};

struct fdt_ipi fdt_ipi_clint = {
	.match_table = ipi_clint_match,
	.cold_init = ipi_clint_cold_init,
	.warm_init = clint_warm_ipi_init,
	.exit = NULL,
};
