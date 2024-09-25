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

extern struct fdt_reset fdt_reset_sifive;
extern struct fdt_reset fdt_reset_htif;
extern struct fdt_reset fdt_reset_thead;

static struct fdt_reset *reset_drivers[] = {
	&fdt_reset_sifive,
	&fdt_reset_htif,
	&fdt_reset_thead,
};

static struct fdt_reset *current_driver = NULL;

int fdt_reset_init(void)
{
	int pos, noff, rc;
	struct fdt_reset *drv;
	const struct fdt_match *match;
	void *fdt = sbi_scratch_thishart_arg1_ptr();

	for (pos = 0; pos < array_size(reset_drivers); pos++) {
		drv = reset_drivers[pos];

		noff = fdt_find_match(fdt, -1, drv->match_table, &match);
		if (noff < 0)
			continue;

		if (drv->init) {
			rc = drv->init(fdt, noff, match);
			if (rc)
				return rc;
		}
		current_driver = drv;
		break;
	}

	return 0;
}
