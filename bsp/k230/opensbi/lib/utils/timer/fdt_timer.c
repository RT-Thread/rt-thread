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
#include <sbi_utils/timer/fdt_timer.h>

extern struct fdt_timer fdt_timer_clint;

static struct fdt_timer *timer_drivers[] = {
	&fdt_timer_clint
};

static struct fdt_timer dummy = {
	.match_table = NULL,
	.cold_init = NULL,
	.warm_init = NULL,
	.exit = NULL,
};

static struct fdt_timer *current_driver = &dummy;

void fdt_timer_exit(void)
{
	if (current_driver->exit)
		current_driver->exit();
}

static int fdt_timer_warm_init(void)
{
	if (current_driver->warm_init)
		return current_driver->warm_init();
	return 0;
}

static int fdt_timer_cold_init(void)
{
	int pos, noff, rc;
	struct fdt_timer *drv;
	const struct fdt_match *match;
	void *fdt = sbi_scratch_thishart_arg1_ptr();

	for (pos = 0; pos < array_size(timer_drivers); pos++) {
		drv = timer_drivers[pos];

		noff = -1;
		while ((noff = fdt_find_match(fdt, noff,
					drv->match_table, &match)) >= 0) {
			if (drv->cold_init) {
				rc = drv->cold_init(fdt, noff, match);
				if (rc)
					return rc;
			}
			current_driver = drv;
		}

		if (current_driver != &dummy)
			break;
	}

	return 0;
}

int fdt_timer_init(bool cold_boot)
{
	int rc;

	if (cold_boot) {
		rc = fdt_timer_cold_init();
		if (rc)
			return rc;
	}

	return fdt_timer_warm_init();
}
