// SPDX-License-Identifier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 */
#include "libfdt_env.h"

#include <fdt.h>
#include <libfdt.h>

#include "libfdt_internal.h"

int fdt_check_full(const void *fdt, size_t bufsize)
{
	int err;
	int num_memrsv;
	int offset, nextoffset = 0;
	uint32_t tag;
	unsigned int depth = 0;
	const void *prop;
	const char *propname;

	if (bufsize < FDT_V1_SIZE)
		return -FDT_ERR_TRUNCATED;
	err = fdt_check_header(fdt);
	if (err != 0)
		return err;
	if (bufsize < fdt_totalsize(fdt))
		return -FDT_ERR_TRUNCATED;

	num_memrsv = fdt_num_mem_rsv(fdt);
	if (num_memrsv < 0)
		return num_memrsv;

	while (1) {
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);

		if (nextoffset < 0)
			return nextoffset;

		switch (tag) {
		case FDT_NOP:
			break;

		case FDT_END:
			if (depth != 0)
				return -FDT_ERR_BADSTRUCTURE;
			return 0;

		case FDT_BEGIN_NODE:
			depth++;
			if (depth > INT_MAX)
				return -FDT_ERR_BADSTRUCTURE;
			break;

		case FDT_END_NODE:
			if (depth == 0)
				return -FDT_ERR_BADSTRUCTURE;
			depth--;
			break;

		case FDT_PROP:
			prop = fdt_getprop_by_offset(fdt, offset, &propname,
						     &err);
			if (!prop)
				return err;
			break;

		default:
			return -FDT_ERR_INTERNAL;
		}
	}
}
