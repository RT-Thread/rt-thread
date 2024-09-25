/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/serial/fdt_serial.h>
#include <sbi_utils/sys/htif.h>

static const struct fdt_match serial_htif_match[] = {
	{ .compatible = "ucb,htif0" },
	{ },
};

static int serial_htif_init(void *fdt, int nodeoff,
			    const struct fdt_match *match)
{
	return htif_serial_init();
}

struct fdt_serial fdt_serial_htif = {
	.match_table = serial_htif_match,
	.init = serial_htif_init
};
