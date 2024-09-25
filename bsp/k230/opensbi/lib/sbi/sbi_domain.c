/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_hartmask.h>
#include <sbi/sbi_hsm.h>
#include <sbi/sbi_math.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_string.h>

struct sbi_domain *hartid_to_domain_table[SBI_HARTMASK_MAX_BITS] = { 0 };
struct sbi_domain *domidx_to_domain_table[SBI_DOMAIN_MAX_INDEX] = { 0 };
static u32 domain_count = 0;
static bool domain_finalized = false;

static struct sbi_hartmask root_hmask = { 0 };

#define ROOT_REGION_MAX	16
static u32 root_memregs_count = 0;
static struct sbi_domain_memregion root_fw_region;
static struct sbi_domain_memregion root_memregs[ROOT_REGION_MAX + 1] = { 0 };

struct sbi_domain root = {
	.name = "root",
	.possible_harts = &root_hmask,
	.regions = root_memregs,
	.system_reset_allowed = TRUE,
};

bool sbi_domain_is_assigned_hart(const struct sbi_domain *dom, u32 hartid)
{
	if (dom)
		return sbi_hartmask_test_hart(hartid, &dom->assigned_harts);

	return FALSE;
}

ulong sbi_domain_get_assigned_hartmask(const struct sbi_domain *dom,
				       ulong hbase)
{
	ulong ret, bword, boff;

	if (!dom)
		return 0;

	bword = BIT_WORD(hbase);
	boff = BIT_WORD_OFFSET(hbase);

	ret = sbi_hartmask_bits(&dom->assigned_harts)[bword++] >> boff;
	if (boff && bword < BIT_WORD(SBI_HARTMASK_MAX_BITS)) {
		ret |= (sbi_hartmask_bits(&dom->assigned_harts)[bword] &
			(BIT(boff) - 1UL)) << (BITS_PER_LONG - boff);
	}

	return ret;
}

static void domain_memregion_initfw(struct sbi_domain_memregion *reg)
{
	if (!reg)
		return;

	sbi_memcpy(reg, &root_fw_region, sizeof(*reg));
}

void sbi_domain_memregion_init(unsigned long addr,
				unsigned long size,
				unsigned long flags,
				struct sbi_domain_memregion *reg)
{
	unsigned long base = 0, order;

	for (order = log2roundup(size) ; order <= __riscv_xlen; order++) {
		if (order < __riscv_xlen) {
			base = addr & ~((1UL << order) - 1UL);
			if ((base <= addr) &&
			    (addr < (base + (1UL << order))) &&
			    (base <= (addr + size - 1UL)) &&
			    ((addr + size - 1UL) < (base + (1UL << order))))
				break;
		} else {
			base = 0;
			break;
		}

	}

	if (reg) {
		reg->base = base;
		reg->order = order;
		reg->flags = flags;
	}
}

bool sbi_domain_check_addr(const struct sbi_domain *dom,
			   unsigned long addr, unsigned long mode,
			   unsigned long access_flags)
{
	bool mmio = FALSE;
	struct sbi_domain_memregion *reg;
	unsigned long rstart, rend, rflags, rwx = 0;

	if (!dom)
		return FALSE;

	if (access_flags & SBI_DOMAIN_READ)
		rwx |= SBI_DOMAIN_MEMREGION_READABLE;
	if (access_flags & SBI_DOMAIN_WRITE)
		rwx |= SBI_DOMAIN_MEMREGION_WRITEABLE;
	if (access_flags & SBI_DOMAIN_EXECUTE)
		rwx |= SBI_DOMAIN_MEMREGION_EXECUTABLE;
	if (access_flags & SBI_DOMAIN_MMIO)
		mmio = TRUE;

	sbi_domain_for_each_memregion(dom, reg) {
		rflags = reg->flags;
		if (mode == PRV_M && !(rflags & SBI_DOMAIN_MEMREGION_MMODE))
			continue;

		rstart = reg->base;
		rend = (reg->order < __riscv_xlen) ?
			rstart + ((1UL << reg->order) - 1) : -1UL;
		if (rstart <= addr && addr <= rend) {
			if ((mmio && !(rflags & SBI_DOMAIN_MEMREGION_MMIO)) ||
			    (!mmio && (rflags & SBI_DOMAIN_MEMREGION_MMIO)))
				return FALSE;
			return ((rflags & rwx) == rwx) ? TRUE : FALSE;
		}
	}

	return (mode == PRV_M) ? TRUE : FALSE;
}

/* Check if region complies with constraints */
static bool is_region_valid(const struct sbi_domain_memregion *reg)
{
	if (reg->order < 3 || __riscv_xlen < reg->order)
		return FALSE;

	if (reg->base & (BIT(reg->order) - 1))
		return FALSE;

	return TRUE;
}

/** Check if regionA is sub-region of regionB */
static bool is_region_subset(const struct sbi_domain_memregion *regA,
			     const struct sbi_domain_memregion *regB)
{
	ulong regA_start = regA->base;
	ulong regA_end = regA->base + (BIT(regA->order) - 1);
	ulong regB_start = regB->base;
	ulong regB_end = regB->base + (BIT(regA->order) - 1);

	if ((regB_start <= regA_start) &&
	    (regA_start < regB_end) &&
	    (regB_start < regA_end) &&
	    (regA_end <= regB_end))
		return TRUE;

	return FALSE;
}

/** Check if regionA conflicts regionB */
static bool is_region_conflict(const struct sbi_domain_memregion *regA,
				const struct sbi_domain_memregion *regB)
{
	if ((is_region_subset(regA, regB) || is_region_subset(regB, regA)) &&
	    regA->flags == regB->flags)
		return TRUE;

	return FALSE;
}

/** Check if regionA should be placed before regionB */
static bool is_region_before(const struct sbi_domain_memregion *regA,
			     const struct sbi_domain_memregion *regB)
{
	if (regA->order < regB->order)
		return TRUE;

	if ((regA->order == regB->order) &&
	    (regA->base < regB->base))
		return TRUE;

	return FALSE;
}

static int sanitize_domain(const struct sbi_platform *plat,
			   struct sbi_domain *dom)
{
	u32 i, j, count;
	bool have_fw_reg;
	struct sbi_domain_memregion treg, *reg, *reg1;

	/* Check possible HARTs */
	if (!dom->possible_harts) {
		sbi_printf("%s: %s possible HART mask is NULL\n",
			   __func__, dom->name);
		return SBI_EINVAL;
	}
	sbi_hartmask_for_each_hart(i, dom->possible_harts) {
		if (sbi_platform_hart_invalid(plat, i)) {
			sbi_printf("%s: %s possible HART mask has invalid "
				   "hart %d\n", __func__, dom->name, i);
			return SBI_EINVAL;
		}
	};

	/* Check memory regions */
	if (!dom->regions) {
		sbi_printf("%s: %s regions is NULL\n",
			   __func__, dom->name);
		return SBI_EINVAL;
	}
	sbi_domain_for_each_memregion(dom, reg) {
		if (!is_region_valid(reg)) {
			sbi_printf("%s: %s has invalid region base=0x%lx "
				   "order=%lu flags=0x%lx\n", __func__,
				   dom->name, reg->base, reg->order,
				   reg->flags);
			return SBI_EINVAL;
		}
	}

	/* Count memory regions and check presence of firmware region */
	count = 0;
	have_fw_reg = FALSE;
	sbi_domain_for_each_memregion(dom, reg) {
		if (reg->order == root_fw_region.order &&
		    reg->base == root_fw_region.base &&
		    reg->flags == root_fw_region.flags)
			have_fw_reg = TRUE;
		count++;
	}
	if (!have_fw_reg) {
		sbi_printf("%s: %s does not have firmware region\n",
			   __func__, dom->name);
		return SBI_EINVAL;
	}

	/* Sort the memory regions */
	for (i = 0; i < (count - 1); i++) {
		reg = &dom->regions[i];
		for (j = i + 1; j < count; j++) {
			reg1 = &dom->regions[j];

			if (is_region_conflict(reg1, reg)) {
				sbi_printf("%s: %s conflict between regions "
					"(base=0x%lx order=%lu flags=0x%lx) and "
					"(base=0x%lx order=%lu flags=0x%lx)\n",
					__func__, dom->name,
					reg->base, reg->order, reg->flags,
					reg1->base, reg1->order, reg1->flags);
				return SBI_EINVAL;
			}

			if (!is_region_before(reg1, reg))
				continue;

			sbi_memcpy(&treg, reg1, sizeof(treg));
			sbi_memcpy(reg1, reg, sizeof(treg));
			sbi_memcpy(reg, &treg, sizeof(treg));
		}
	}

	/*
	 * We don't need to check boot HART id of domain because if boot
	 * HART id is not possible/assigned to this domain then it won't
	 * be started at boot-time by sbi_domain_finalize().
	 */

	/*
	 * Check next mode
	 *
	 * We only allow next mode to be S-mode or U-mode.so that we can
	 * protect M-mode context and enforce checks on memory accesses.
	 */
	if (dom->next_mode != PRV_S &&
	    dom->next_mode != PRV_U) {
		sbi_printf("%s: %s invalid next booting stage mode 0x%lx\n",
			   __func__, dom->name, dom->next_mode);
		return SBI_EINVAL;
	}

	/* Check next address and next mode*/
	if (!sbi_domain_check_addr(dom, dom->next_addr, dom->next_mode,
				   SBI_DOMAIN_EXECUTE)) {
		sbi_printf("%s: %s next booting stage addres 0x%lx can't "
			   "execute\n", __func__, dom->name, dom->next_addr);
		return SBI_EINVAL;
	}

	return 0;
}

void sbi_domain_dump(const struct sbi_domain *dom, const char *suffix)
{
	u32 i, k;
	unsigned long rstart, rend;
	struct sbi_domain_memregion *reg;

	sbi_printf("Domain%d Name        %s: %s\n",
		   dom->index, suffix, dom->name);

	sbi_printf("Domain%d Boot HART   %s: %d\n",
		   dom->index, suffix, dom->boot_hartid);

	k = 0;
	sbi_printf("Domain%d HARTs       %s: ", dom->index, suffix);
	sbi_hartmask_for_each_hart(i, dom->possible_harts)
		sbi_printf("%s%d%s", (k++) ? "," : "",
			   i, sbi_domain_is_assigned_hart(dom, i) ? "*" : "");
	sbi_printf("\n");

	i = 0;
	sbi_domain_for_each_memregion(dom, reg) {
		rstart = reg->base;
		rend = (reg->order < __riscv_xlen) ?
			rstart + ((1UL << reg->order) - 1) : -1UL;

#if __riscv_xlen == 32
		sbi_printf("Domain%d Region%02d    %s: 0x%08lx-0x%08lx ",
#else
		sbi_printf("Domain%d Region%02d    %s: 0x%016lx-0x%016lx ",
#endif
			   dom->index, i, suffix, rstart, rend);

		k = 0;
		if (reg->flags & SBI_DOMAIN_MEMREGION_MMODE)
			sbi_printf("%cM", (k++) ? ',' : '(');
		if (reg->flags & SBI_DOMAIN_MEMREGION_MMIO)
			sbi_printf("%cI", (k++) ? ',' : '(');
		if (reg->flags & SBI_DOMAIN_MEMREGION_READABLE)
			sbi_printf("%cR", (k++) ? ',' : '(');
		if (reg->flags & SBI_DOMAIN_MEMREGION_WRITEABLE)
			sbi_printf("%cW", (k++) ? ',' : '(');
		if (reg->flags & SBI_DOMAIN_MEMREGION_EXECUTABLE)
			sbi_printf("%cX", (k++) ? ',' : '(');
		sbi_printf("%s\n", (k++) ? ")" : "()");

		i++;
	}

#if __riscv_xlen == 32
	sbi_printf("Domain%d Next Address%s: 0x%08lx\n",
#else
	sbi_printf("Domain%d Next Address%s: 0x%016lx\n",
#endif
		   dom->index, suffix, dom->next_addr);

#if __riscv_xlen == 32
	sbi_printf("Domain%d Next Arg1   %s: 0x%08lx\n",
#else
	sbi_printf("Domain%d Next Arg1   %s: 0x%016lx\n",
#endif
		   dom->index, suffix, dom->next_arg1);

	sbi_printf("Domain%d Next Mode   %s: ", dom->index, suffix);
	switch (dom->next_mode) {
	case PRV_M:
		sbi_printf("M-mode\n");
		break;
	case PRV_S:
		sbi_printf("S-mode\n");
		break;
	case PRV_U:
		sbi_printf("U-mode\n");
		break;
	default:
		sbi_printf("Unknown\n");
		break;
	};

	sbi_printf("Domain%d SysReset    %s: %s\n",
		   dom->index, suffix, (dom->system_reset_allowed) ? "yes" : "no");
}

void sbi_domain_dump_all(const char *suffix)
{
	u32 i;
	const struct sbi_domain *dom;

	sbi_domain_for_each(i, dom) {
		sbi_domain_dump(dom, suffix);
		sbi_printf("\n");
	}
}

int sbi_domain_register(struct sbi_domain *dom,
			const struct sbi_hartmask *assign_mask)
{
	u32 i;
	int rc;
	struct sbi_domain *tdom;
	u32 cold_hartid = current_hartid();
	const struct sbi_platform *plat = sbi_platform_thishart_ptr();

	/* Sanity checks */
	if (!dom || !assign_mask || domain_finalized)
		return SBI_EINVAL;

	/* Check if domain already discovered */
	sbi_domain_for_each(i, tdom) {
		if (tdom == dom)
			return SBI_EALREADY;
	}

	/*
	 * Ensure that we have room for Domain Index to
	 * HART ID mapping
	 */
	if (SBI_DOMAIN_MAX_INDEX <= domain_count) {
		sbi_printf("%s: No room for %s\n",
			   __func__, dom->name);
		return SBI_ENOSPC;
	}

	/* Sanitize discovered domain */
	rc = sanitize_domain(plat, dom);
	if (rc) {
		sbi_printf("%s: sanity checks failed for"
			   " %s (error %d)\n", __func__,
			   dom->name, rc);
		return rc;
	}

	/* Assign index to domain */
	dom->index = domain_count++;
	domidx_to_domain_table[dom->index] = dom;

	/* Clear assigned HARTs of domain */
	sbi_hartmask_clear_all(&dom->assigned_harts);

	/* Assign domain to HART if HART is a possible HART */
	sbi_hartmask_for_each_hart(i, assign_mask) {
		if (!sbi_hartmask_test_hart(i, dom->possible_harts))
			continue;

		tdom = hartid_to_domain_table[i];
		if (tdom)
			sbi_hartmask_clear_hart(i,
					&tdom->assigned_harts);
		hartid_to_domain_table[i] = dom;
		sbi_hartmask_set_hart(i, &dom->assigned_harts);

		/*
		 * If cold boot HART is assigned to this domain then
		 * override boot HART of this domain.
		 */
		if (i == cold_hartid &&
		    dom->boot_hartid != cold_hartid) {
			sbi_printf("Domain%d Boot HARTID forced to"
				   " %d\n", dom->index, cold_hartid);
			dom->boot_hartid = cold_hartid;
		}
	}

	return 0;
}

int sbi_domain_root_add_memregion(const struct sbi_domain_memregion *reg)
{
	int rc;
	bool reg_merged;
	struct sbi_domain_memregion *nreg, *nreg1, *nreg2;
	const struct sbi_platform *plat = sbi_platform_thishart_ptr();

	/* Sanity checks */
	if (!reg || domain_finalized ||
	    (root.regions != root_memregs) ||
	    (ROOT_REGION_MAX <= root_memregs_count))
		return SBI_EINVAL;

	/* Check for conflicts */
	sbi_domain_for_each_memregion(&root, nreg) {
		if (is_region_conflict(reg, nreg))
			return SBI_EINVAL;
	}

	/* Append the memregion to root memregions */
	nreg = &root_memregs[root_memregs_count];
	sbi_memcpy(nreg, reg, sizeof(*reg));
	root_memregs_count++;
	root_memregs[root_memregs_count].order = 0;

	/* Sort and optimize root regions */
	do {
		/* Sanitize the root domain so that memregions are sorted */
		rc = sanitize_domain(plat, &root);
		if (rc) {
			sbi_printf("%s: sanity checks failed for"
				   " %s (error %d)\n", __func__,
				   root.name, rc);
			return rc;
		}

		/* Merge consecutive memregions with same order and flags */
		reg_merged = false;
		sbi_domain_for_each_memregion(&root, nreg) {
			nreg1 = nreg + 1;
			if (!nreg1->order)
				continue;

			if ((nreg->base + BIT(nreg->order)) == nreg1->base &&
			    nreg->order == nreg1->order &&
			    nreg->flags == nreg1->flags) {
				nreg->order++;
				while (nreg1->order) {
					nreg2 = nreg1 + 1;
					sbi_memcpy(nreg1, nreg2, sizeof(*nreg1));
					nreg1++;
				}
				reg_merged = true;
				root_memregs_count--;
			}
		}
	} while (reg_merged);

	return 0;
}

int sbi_domain_finalize(struct sbi_scratch *scratch, u32 cold_hartid)
{
	int rc;
	u32 i, dhart;
	struct sbi_domain *dom;
	const struct sbi_platform *plat = sbi_platform_ptr(scratch);

	/* Initialize and populate domains for the platform */
	rc = sbi_platform_domains_init(plat);
	if (rc) {
		sbi_printf("%s: platform domains_init() failed (error %d)\n",
			   __func__, rc);
		return rc;
	}

	/* Startup boot HART of domains */
	sbi_domain_for_each(i, dom) {
		/* Domain boot HART */
		dhart = dom->boot_hartid;

		/* Ignore of boot HART is off limits */
		if (SBI_HARTMASK_MAX_BITS <= dhart)
			continue;

		/* Ignore if boot HART not possible for this domain */
		if (!sbi_hartmask_test_hart(dhart, dom->possible_harts))
			continue;

		/* Ignore if boot HART assigned different domain */
		if (sbi_hartid_to_domain(dhart) != dom ||
		    !sbi_hartmask_test_hart(dhart, &dom->assigned_harts))
			continue;

		/* Startup boot HART of domain */
		if (dhart == cold_hartid) {
			scratch->next_addr = dom->next_addr;
			scratch->next_mode = dom->next_mode;
			scratch->next_arg1 = dom->next_arg1;
		} else {
			rc = sbi_hsm_hart_start(scratch, NULL, dhart,
						dom->next_addr,
						dom->next_mode,
						dom->next_arg1);
			if (rc) {
				sbi_printf("%s: failed to start boot HART %d"
					   " for %s (error %d)\n", __func__,
					   dhart, dom->name, rc);
				return rc;
			}
		}
	}

	/*
	 * Set the finalized flag so that the root domain
	 * regions can't be changed.
	 */
	domain_finalized = true;

	return 0;
}

int sbi_domain_init(struct sbi_scratch *scratch, u32 cold_hartid)
{
	u32 i;
	const struct sbi_platform *plat = sbi_platform_ptr(scratch);

	/* Root domain firmware memory region */
	sbi_domain_memregion_init(scratch->fw_start, scratch->fw_size, 0,
				  &root_fw_region);
	domain_memregion_initfw(&root_memregs[root_memregs_count++]);

	/* Root domain allow everything memory region */
	sbi_domain_memregion_init(0, ~0UL,
				  (SBI_DOMAIN_MEMREGION_READABLE |
				   SBI_DOMAIN_MEMREGION_WRITEABLE |
				   SBI_DOMAIN_MEMREGION_EXECUTABLE),
				  &root_memregs[root_memregs_count++]);

	/* Root domain memory region end */
	root_memregs[root_memregs_count].order = 0;

	/* Root domain boot HART id is same as coldboot HART id */
	root.boot_hartid = cold_hartid;

	/* Root domain next booting stage details */
	root.next_arg1 = scratch->next_arg1;
	root.next_addr = scratch->next_addr;
	root.next_mode = scratch->next_mode;

	/* Root domain possible and assigned HARTs */
	for (i = 0; i < SBI_HARTMASK_MAX_BITS; i++) {
		if (sbi_platform_hart_invalid(plat, i))
			continue;
		sbi_hartmask_set_hart(i, &root_hmask);
	}

	return sbi_domain_register(&root, &root_hmask);
}
