/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi_utils/reset/fdt_reset.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/sys/htif.h>

static int htif_reset_init(void *fdt, int nodeoff,
			   const struct fdt_match *match)
{
	return htif_system_reset_init();
}

static const struct fdt_match htif_reset_match[] = {
	{ .compatible = "ucb,htif0" },
	{ },
};

struct fdt_reset fdt_reset_htif = {
	.match_table = htif_reset_match,
	.init = htif_reset_init
};
