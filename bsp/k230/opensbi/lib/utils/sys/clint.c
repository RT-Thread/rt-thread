/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_atomic.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hartmask.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_timer.h>
#include <sbi_utils/sys/clint.h>

#define CLINT_IPI_OFF		0
#define CLINT_IPI_SIZE		0x4000

#define CLINT_TIME_CMP_OFF	0x4000
#define CLINT_TIME_CMP_SIZE	0x4000

#define CLINT_TIME_VAL_OFF	0xbff8
#define CLINT_TIME_VAL_SIZE	0x4000

static struct clint_data *clint_ipi_hartid2data[SBI_HARTMASK_MAX_BITS];

static void clint_ipi_send(u32 target_hart)
{
	struct clint_data *clint;

	if (SBI_HARTMASK_MAX_BITS <= target_hart)
		return;
	clint = clint_ipi_hartid2data[target_hart];
	if (!clint)
		return;

	/* Set CLINT IPI */
	writel(1, &clint->ipi[target_hart - clint->first_hartid]);
}

static void clint_ipi_clear(u32 target_hart)
{
	struct clint_data *clint;

	if (SBI_HARTMASK_MAX_BITS <= target_hart)
		return;
	clint = clint_ipi_hartid2data[target_hart];
	if (!clint)
		return;

	/* Clear CLINT IPI */
	writel(0, &clint->ipi[target_hart - clint->first_hartid]);
}

static struct sbi_ipi_device clint_ipi = {
	.name = "clint",
	.ipi_send = clint_ipi_send,
	.ipi_clear = clint_ipi_clear
};

int clint_warm_ipi_init(void)
{
	/* Clear CLINT IPI for current HART */
	clint_ipi_clear(current_hartid());

	return 0;
}

int clint_cold_ipi_init(struct clint_data *clint)
{
	u32 i;
	int rc;
	struct sbi_domain_memregion reg;

	if (!clint)
		return SBI_EINVAL;

	/* Initialize private data */
	clint->ipi = (void *)clint->addr;

	/* Update IPI hartid table */
	for (i = 0; i < clint->hart_count; i++)
		clint_ipi_hartid2data[clint->first_hartid + i] = clint;

	/* Add CLINT ipi region to the root domain */
	sbi_domain_memregion_init(clint->addr + CLINT_IPI_OFF,
				  CLINT_IPI_SIZE,
				  SBI_DOMAIN_MEMREGION_MMIO, &reg);
	rc = sbi_domain_root_add_memregion(&reg);
	if (rc)
		return rc;

	sbi_ipi_set_device(&clint_ipi);

	return 0;
}

static struct clint_data *clint_timer_hartid2data[SBI_HARTMASK_MAX_BITS];

#if __riscv_xlen != 32
static u64 clint_time_rd64(volatile u64 *addr)
{
	return readq_relaxed(addr);
}

static void clint_time_wr64(u64 value, volatile u64 *addr)
{
	writeq_relaxed(value, addr);
}
#endif

static u64 clint_time_rd32(volatile u64 *addr)
{
	u32 lo, hi;

	do {
		hi = readl_relaxed((u32 *)addr + 1);
		lo = readl_relaxed((u32 *)addr);
	} while (hi != readl_relaxed((u32 *)addr + 1));

	return ((u64)hi << 32) | (u64)lo;
}

static void clint_time_wr32(u64 value, volatile u64 *addr)
{
	u32 mask = -1U;

	writel_relaxed(value & mask, (void *)(addr));
	writel_relaxed(value >> 32, (void *)(addr) + 0x04);
}

static u64 clint_timer_value(void)
{
	struct clint_data *clint = clint_timer_hartid2data[current_hartid()];

	/* Read CLINT Time Value */
	return clint->time_rd(clint->time_val) + clint->time_delta;
}

static void clint_timer_event_stop(void)
{
	u32 target_hart = current_hartid();
	struct clint_data *clint = clint_timer_hartid2data[target_hart];

	/* Clear CLINT Time Compare */
	clint->time_wr(-1ULL,
			&clint->time_cmp[target_hart - clint->first_hartid]);
}

static void clint_timer_event_start(u64 next_event)
{
	u32 target_hart = current_hartid();
	struct clint_data *clint = clint_timer_hartid2data[target_hart];

	/* Program CLINT Time Compare */
	clint->time_wr(next_event - clint->time_delta,
		       &clint->time_cmp[target_hart - clint->first_hartid]);
}

static struct sbi_timer_device clint_timer = {
	.name = "clint",
	.timer_value = clint_timer_value,
	.timer_event_start = clint_timer_event_start,
	.timer_event_stop = clint_timer_event_stop
};

int clint_warm_timer_init(void)
{
	u64 v1, v2, mv;
	u32 target_hart = current_hartid();
	struct clint_data *reference;
	struct clint_data *clint = clint_timer_hartid2data[target_hart];

	if (!clint)
		return SBI_ENODEV;

	/*
	 * Compute delta if reference available
	 *
	 * We deliberately compute time_delta in warm init so that time_delta
	 * is computed on a HART which is going to use given CLINT. We use
	 * atomic flag timer_delta_computed to ensure that only one HART does
	 * time_delta computation.
	 */
	if (clint->time_delta_reference) {
		reference = clint->time_delta_reference;
		if (!atomic_raw_xchg_ulong(&clint->time_delta_computed, 1)) {
			v1 = clint->time_rd(clint->time_val);
			mv = reference->time_rd(reference->time_val);
			v2 = clint->time_rd(clint->time_val);
			clint->time_delta = mv - ((v1 / 2) + (v2 / 2));
		}
	}

	/* Clear CLINT Time Compare */
	clint->time_wr(-1ULL,
		       &clint->time_cmp[target_hart - clint->first_hartid]);

	return 0;
}

int clint_cold_timer_init(struct clint_data *clint,
			  struct clint_data *reference)
{
	u32 i;
	int rc;
	struct sbi_domain_memregion reg;

	if (!clint)
		return SBI_EINVAL;

	/* Initialize private data */
	clint->time_delta_reference = reference;
	clint->time_delta_computed = 0;
	clint->time_delta = 0;
	clint->time_val = (u64 *)((void *)clint->addr + CLINT_TIME_VAL_OFF);
	clint->time_cmp = (u64 *)((void *)clint->addr + CLINT_TIME_CMP_OFF);
	clint->time_rd = clint_time_rd32;
	clint->time_wr = clint_time_wr32;

	/* Override read/write accessors for 64bit MMIO */
#if __riscv_xlen != 32
	if (clint->has_64bit_mmio) {
		clint->time_rd = clint_time_rd64;
		clint->time_wr = clint_time_wr64;
	}
#endif

	/* Update timer hartid table */
	for (i = 0; i < clint->hart_count; i++)
		clint_timer_hartid2data[clint->first_hartid + i] = clint;

	/* Add CLINT mtime region to the root domain */
	sbi_domain_memregion_init(clint->addr + CLINT_TIME_VAL_OFF,
				  CLINT_TIME_VAL_SIZE,
				  SBI_DOMAIN_MEMREGION_MMIO, &reg);
	rc = sbi_domain_root_add_memregion(&reg);
	if (rc)
		return rc;

	/* Add CLINT timecmp region to the root domain */
	sbi_domain_memregion_init(clint->addr + CLINT_TIME_CMP_OFF,
				  CLINT_TIME_CMP_SIZE,
				  SBI_DOMAIN_MEMREGION_MMIO, &reg);
	rc = sbi_domain_root_add_memregion(&reg);
	if (rc)
		return rc;

	sbi_timer_set_device(&clint_timer);

	return 0;
}
