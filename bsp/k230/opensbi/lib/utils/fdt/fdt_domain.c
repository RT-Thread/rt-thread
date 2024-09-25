// SPDX-License-Identifier: BSD-2-Clause
/*
 * fdt_domain.c - Flat Device Tree Domain helper routines
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <libfdt.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hartmask.h>
#include <sbi/sbi_scratch.h>
#include <sbi_utils/fdt/fdt_domain.h>
#include <sbi_utils/fdt/fdt_helper.h>

int fdt_iterate_each_domain(void *fdt, void *opaque,
			    int (*fn)(void *fdt, int domain_offset,
				       void *opaque))
{
	int rc, doffset, poffset;

	if (!fdt || !fn)
		return SBI_EINVAL;

	poffset = fdt_path_offset(fdt, "/chosen");
	if (poffset < 0)
		return 0;
	poffset = fdt_node_offset_by_compatible(fdt, poffset,
						"opensbi,domain,config");
	if (poffset < 0)
		return 0;

	fdt_for_each_subnode(doffset, fdt, poffset) {
		if (fdt_node_check_compatible(fdt, doffset,
					      "opensbi,domain,instance"))
			continue;

		rc = fn(fdt, doffset, opaque);
		if (rc)
			return rc;
	}

	return 0;
}

int fdt_iterate_each_memregion(void *fdt, int domain_offset, void *opaque,
			       int (*fn)(void *fdt, int domain_offset,
					 int region_offset, u32 region_access,
					 void *opaque))
{
	u32 i, rcount;
	int rc, len, region_offset;
	const u32 *regions;

	if (!fdt || (domain_offset < 0) || !fn)
		return SBI_EINVAL;

	if (fdt_node_check_compatible(fdt, domain_offset,
				      "opensbi,domain,instance"))
		return SBI_EINVAL;

	regions = fdt_getprop(fdt, domain_offset, "regions", &len);
	if (!regions)
		return 0;

	rcount = (u32)len / (sizeof(u32) * 2);
	for (i = 0; i < rcount; i++) {
		region_offset = fdt_node_offset_by_phandle(fdt,
						fdt32_to_cpu(regions[2 * i]));
		if (region_offset < 0)
			return region_offset;

		if (fdt_node_check_compatible(fdt, region_offset,
					      "opensbi,domain,memregion"))
			return SBI_EINVAL;

		rc = fn(fdt, domain_offset, region_offset,
			fdt32_to_cpu(regions[(2 * i) + 1]), opaque);
		if (rc)
			return rc;
	}

	return 0;
}

struct __fixup_find_domain_offset_info {
	const char *name;
	int *doffset;
};

static int __fixup_find_domain_offset(void *fdt, int doff, void *p)
{
	struct __fixup_find_domain_offset_info *fdo = p;

	if (!sbi_strcmp(fdo->name, fdt_get_name(fdt, doff, NULL)))
		*fdo->doffset = doff;

	return 0;
}

#define DISABLE_DEVICES_MASK	(SBI_DOMAIN_MEMREGION_READABLE | \
				 SBI_DOMAIN_MEMREGION_WRITEABLE | \
				 SBI_DOMAIN_MEMREGION_EXECUTABLE)

static int __fixup_count_disable_devices(void *fdt, int doff, int roff,
					 u32 perm, void *p)
{
	int len;
	u32 *dcount = p;

	if (perm & DISABLE_DEVICES_MASK)
		return 0;

	len = 0;
	if (fdt_getprop(fdt, roff, "devices", &len))
		*dcount += len / sizeof(u32);

	return 0;
}

static int __fixup_disable_devices(void *fdt, int doff, int roff,
				   u32 raccess, void *p)
{
	int i, len, coff;
	const u32 *devices;

	if (raccess & DISABLE_DEVICES_MASK)
		return 0;

	len = 0;
	devices = fdt_getprop(fdt, roff, "devices", &len);
	if (!devices)
		return 0;
	len = len / sizeof(u32);

	for (i = 0; i < len; i++) {
		coff = fdt_node_offset_by_phandle(fdt,
					fdt32_to_cpu(devices[i]));
		if (coff < 0)
			return coff;

		fdt_setprop_string(fdt, coff, "status", "disabled");
	}

	return 0;
}

void fdt_domain_fixup(void *fdt)
{
	u32 i, dcount;
	int err, poffset, doffset;
	struct sbi_domain *dom = sbi_domain_thishart_ptr();
	struct __fixup_find_domain_offset_info fdo;

	/* Remove the domain assignment DT property from CPU DT nodes */
	poffset = fdt_path_offset(fdt, "/cpus");
	if (poffset < 0)
		return;
	fdt_for_each_subnode(doffset, fdt, poffset) {
		err = fdt_parse_hart_id(fdt, doffset, &i);
		if (err)
			continue;

		fdt_nop_property(fdt, doffset, "opensbi-domain");
	}

	/* Skip device disable for root domain */
	if (!dom->index)
		goto skip_device_disable;

	/* Find current domain DT node */
	doffset = -1;
	fdo.name = dom->name;
	fdo.doffset = &doffset;
	fdt_iterate_each_domain(fdt, &fdo, __fixup_find_domain_offset);
	if (doffset < 0)
		goto skip_device_disable;

	/* Count current domain device DT nodes to be disabled */
	dcount = 0;
	fdt_iterate_each_memregion(fdt, doffset, &dcount,
				   __fixup_count_disable_devices);
	if (!dcount)
		goto skip_device_disable;

	/* Expand FDT based on device DT nodes to be disabled */
	err = fdt_open_into(fdt, fdt, fdt_totalsize(fdt) + dcount * 32);
	if (err < 0)
		return;

	/* Again find current domain DT node */
	doffset = -1;
	fdo.name = dom->name;
	fdo.doffset = &doffset;
	fdt_iterate_each_domain(fdt, &fdo, __fixup_find_domain_offset);
	if (doffset < 0)
		goto skip_device_disable;

	/* Disable device DT nodes for current domain */
	fdt_iterate_each_memregion(fdt, doffset, NULL,
				   __fixup_disable_devices);
skip_device_disable:

	/* Remove the OpenSBI domain config DT node */
	poffset = fdt_path_offset(fdt, "/chosen");
	if (poffset < 0)
		return;
	poffset = fdt_node_offset_by_compatible(fdt, poffset,
						"opensbi,domain,config");
	if (poffset < 0)
		return;
	fdt_nop_node(fdt, poffset);
}

#define FDT_DOMAIN_MAX_COUNT		8
#define FDT_DOMAIN_REGION_MAX_COUNT	16

static u32 fdt_domains_count;
static struct sbi_domain fdt_domains[FDT_DOMAIN_MAX_COUNT];
static struct sbi_hartmask fdt_masks[FDT_DOMAIN_MAX_COUNT];
static struct sbi_domain_memregion
	fdt_regions[FDT_DOMAIN_MAX_COUNT][FDT_DOMAIN_REGION_MAX_COUNT + 1];

static int __fdt_parse_region(void *fdt, int domain_offset,
			      int region_offset, u32 region_access,
			      void *opaque)
{
	int len;
	u32 val32;
	u64 val64;
	const u32 *val;
	u32 *region_count = opaque;
	struct sbi_domain_memregion *region;

	/* Find next region of the domain */
	if (FDT_DOMAIN_REGION_MAX_COUNT <= *region_count)
		return SBI_EINVAL;
	region = &fdt_regions[fdt_domains_count][*region_count];

	/* Read "base" DT property */
	val = fdt_getprop(fdt, region_offset, "base", &len);
	if (!val && len >= 8)
		return SBI_EINVAL;
	val64 = fdt32_to_cpu(val[0]);
	val64 = (val64 << 32) | fdt32_to_cpu(val[1]);
	region->base = val64;

	/* Read "order" DT property */
	val = fdt_getprop(fdt, region_offset, "order", &len);
	if (!val && len >= 4)
		return SBI_EINVAL;
	val32 = fdt32_to_cpu(*val);
	if (val32 < 3 || __riscv_xlen < val32)
		return SBI_EINVAL;
	region->order = val32;

	/* Read "mmio" DT property */
	region->flags = region_access & SBI_DOMAIN_MEMREGION_ACCESS_MASK;
	if (fdt_get_property(fdt, region_offset, "mmio", NULL))
		region->flags |= SBI_DOMAIN_MEMREGION_MMIO;

	(*region_count)++;

	return 0;
}

static int __fdt_parse_domain(void *fdt, int domain_offset, void *opaque)
{
	u32 val32;
	u64 val64;
	const u32 *val;
	struct sbi_domain *dom;
	struct sbi_hartmask *mask;
	struct sbi_hartmask assign_mask;
	int *cold_domain_offset = opaque;
	struct sbi_domain_memregion *reg, *regions;
	int i, err, len, cpus_offset, cpu_offset, doffset;

	/* Sanity check on maximum domains we can handle */
	if (FDT_DOMAIN_MAX_COUNT <= fdt_domains_count)
		return SBI_EINVAL;
	dom = &fdt_domains[fdt_domains_count];
	mask = &fdt_masks[fdt_domains_count];
	regions = &fdt_regions[fdt_domains_count][0];

	/* Read DT node name */
	sbi_strncpy(dom->name, fdt_get_name(fdt, domain_offset, NULL),
		    sizeof(dom->name));
	dom->name[sizeof(dom->name) - 1] = '\0';

	/* Setup possible HARTs mask */
	SBI_HARTMASK_INIT(mask);
	dom->possible_harts = mask;
	val = fdt_getprop(fdt, domain_offset, "possible-harts", &len);
	len = len / sizeof(u32);
	if (val && len) {
		for (i = 0; i < len; i++) {
			cpu_offset = fdt_node_offset_by_phandle(fdt,
							fdt32_to_cpu(val[i]));
			if (cpu_offset < 0)
				return cpu_offset;

			err = fdt_parse_hart_id(fdt, cpu_offset, &val32);
			if (err)
				return err;

			sbi_hartmask_set_hart(val32, mask);
		}
	}

	/* Setup memregions from DT */
	val32 = 0;
	sbi_memset(regions, 0,
		   sizeof(*regions) * (FDT_DOMAIN_REGION_MAX_COUNT + 1));
	dom->regions = regions;
	err = fdt_iterate_each_memregion(fdt, domain_offset, &val32,
					 __fdt_parse_region);
	if (err)
		return err;

	/*
	 * Copy over root domain memregions which don't allow
	 * read, write and execute from lower privilege modes.
	 *
	 * These root domain memregions without read, write,
	 * and execute permissions include:
	 * 1) firmware region protecting the firmware memory
	 * 2) mmio regions protecting M-mode only mmio devices
	 */
	sbi_domain_for_each_memregion(&root, reg) {
		if ((reg->flags & SBI_DOMAIN_MEMREGION_READABLE) ||
		    (reg->flags & SBI_DOMAIN_MEMREGION_WRITEABLE) ||
		    (reg->flags & SBI_DOMAIN_MEMREGION_EXECUTABLE))
			continue;
		if (FDT_DOMAIN_REGION_MAX_COUNT <= val32)
			return SBI_EINVAL;
		sbi_memcpy(&regions[val32++], reg, sizeof(*reg));
	}

	/* Read "boot-hart" DT property */
	val32 = -1U;
	val = fdt_getprop(fdt, domain_offset, "boot-hart", &len);
	if (val && len >= 4) {
		cpu_offset = fdt_node_offset_by_phandle(fdt,
							 fdt32_to_cpu(*val));
		if (cpu_offset >= 0)
			fdt_parse_hart_id(fdt, cpu_offset, &val32);
	} else {
		if (domain_offset == *cold_domain_offset)
			val32 = current_hartid();
	}
	dom->boot_hartid = val32;

	/* Read "next-arg1" DT property */
	val64 = 0;
	val = fdt_getprop(fdt, domain_offset, "next-arg1", &len);
	if (val && len >= 8) {
		val64 = fdt32_to_cpu(val[0]);
		val64 = (val64 << 32) | fdt32_to_cpu(val[1]);
	} else {
		if (domain_offset == *cold_domain_offset)
			val64 = sbi_scratch_thishart_ptr()->next_arg1;
	}
	dom->next_arg1 = val64;

	/* Read "next-addr" DT property */
	val64 = 0;
	val = fdt_getprop(fdt, domain_offset, "next-addr", &len);
	if (val && len >= 8) {
		val64 = fdt32_to_cpu(val[0]);
		val64 = (val64 << 32) | fdt32_to_cpu(val[1]);
	} else {
		if (domain_offset == *cold_domain_offset)
			val64 = sbi_scratch_thishart_ptr()->next_addr;
	}
	dom->next_addr = val64;

	/* Read "next-mode" DT property */
	val32 = 0x1;
	val = fdt_getprop(fdt, domain_offset, "next-mode", &len);
	if (val && len >= 4) {
		val32 = fdt32_to_cpu(val[0]);
		if (val32 != 0x0 && val32 != 0x1)
			val32 = 0x1;
	} else {
		if (domain_offset == *cold_domain_offset)
			val32 = sbi_scratch_thishart_ptr()->next_mode;
	}
	dom->next_mode = val32;

	/* Read "system-reset-allowed" DT property */
	if (fdt_get_property(fdt, domain_offset,
			     "system-reset-allowed", NULL))
		dom->system_reset_allowed = TRUE;
	else
		dom->system_reset_allowed = FALSE;

	/* Find /cpus DT node */
	cpus_offset = fdt_path_offset(fdt, "/cpus");
	if (cpus_offset < 0)
		return cpus_offset;

	/* HART to domain assignment mask based on CPU DT nodes */
	sbi_hartmask_clear_all(&assign_mask);
	fdt_for_each_subnode(cpu_offset, fdt, cpus_offset) {
		err = fdt_parse_hart_id(fdt, cpu_offset, &val32);
		if (err)
			continue;

		if (SBI_HARTMASK_MAX_BITS <= val32)
			continue;

		val = fdt_getprop(fdt, cpu_offset, "opensbi-domain", &len);
		if (!val || len < 4)
			return SBI_EINVAL;

		doffset = fdt_node_offset_by_phandle(fdt, fdt32_to_cpu(*val));
		if (doffset < 0)
			return doffset;

		if (doffset == domain_offset)
			sbi_hartmask_set_hart(val32, &assign_mask);
	}

	/* Increment domains count */
	fdt_domains_count++;

	/* Register the domain */
	return sbi_domain_register(dom, &assign_mask);
}

int fdt_domains_populate(void *fdt)
{
	const u32 *val;
	int cold_domain_offset;
	u32 hartid, cold_hartid;
	int err, len, cpus_offset, cpu_offset;

	/* Sanity checks */
	if (!fdt)
		return SBI_EINVAL;

	/* Find /cpus DT node */
	cpus_offset = fdt_path_offset(fdt, "/cpus");
	if (cpus_offset < 0)
		return cpus_offset;

	/* Find coldboot HART domain DT node offset */
	cold_domain_offset = -1;
	cold_hartid = current_hartid();
	fdt_for_each_subnode(cpu_offset, fdt, cpus_offset) {
		err = fdt_parse_hart_id(fdt, cpu_offset, &hartid);
		if (err)
			continue;

		if (hartid != cold_hartid)
			continue;

		val = fdt_getprop(fdt, cpu_offset, "opensbi-domain", &len);
		if (val && len >= 4)
			cold_domain_offset = fdt_node_offset_by_phandle(fdt,
							   fdt32_to_cpu(*val));

		break;
	}

	/* Iterate over each domain in FDT and populate details */
	return fdt_iterate_each_domain(fdt, &cold_domain_offset,
				       __fdt_parse_domain);
}
