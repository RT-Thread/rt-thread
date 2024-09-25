/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/sbi_scratch.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/reset/fdt_reset.h>
#include <sbi_utils/sys/sifive_test.h>

static int sifive_test_reset_init(void *fdt, int nodeoff,
				  const struct fdt_match *match)
{
	int rc;
	unsigned long addr;

	rc = fdt_get_node_addr_size(fdt, nodeoff, &addr, NULL);
	if (rc)
		return rc;

	return sifive_test_init(addr);
}

static const struct fdt_match sifive_test_reset_match[] = {
	{ .compatible = "sifive,test1" },
	{ },
};

struct fdt_reset fdt_reset_sifive = {
	.match_table = sifive_test_reset_match,
	.init = sifive_test_reset_init,
};
