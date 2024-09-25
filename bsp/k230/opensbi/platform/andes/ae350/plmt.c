/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Andes Technology Corporation
 *
 * Authors:
 *   Zong Li <zong@andestech.com>
 *   Nylon Chen <nylon7@andestech.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_io.h>
#include <sbi/sbi_timer.h>

static u32 plmt_time_hart_count;
static volatile void *plmt_time_base;
static volatile u64 *plmt_time_val;
static volatile u64 *plmt_time_cmp;

static u64 plmt_timer_value(void)
{
#if __riscv_xlen == 64
	return readq_relaxed(plmt_time_val);
#else
	u32 lo, hi;

	do {
		hi = readl_relaxed((void *)plmt_time_val + 0x04);
		lo = readl_relaxed(plmt_time_val);
	} while (hi != readl_relaxed((void *)plmt_time_val + 0x04));

	return ((u64)hi << 32) | (u64)lo;
#endif
}

static void plmt_timer_event_stop(void)
{
	u32 target_hart = current_hartid();

	if (plmt_time_hart_count <= target_hart)
		return;

	/* Clear PLMT Time Compare */
#if __riscv_xlen == 64
	writeq_relaxed(-1ULL, &plmt_time_cmp[target_hart]);
#else
	writel_relaxed(-1UL, &plmt_time_cmp[target_hart]);
	writel_relaxed(-1UL, (void *)(&plmt_time_cmp[target_hart]) + 0x04);
#endif
}

static void plmt_timer_event_start(u64 next_event)
{
	u32 target_hart = current_hartid();

	if (plmt_time_hart_count <= target_hart)
		return;

	/* Program PLMT Time Compare */
#if __riscv_xlen == 64
	writeq_relaxed(next_event, &plmt_time_cmp[target_hart]);
#else
	u32 mask = -1UL;

	writel_relaxed(next_event & mask, &plmt_time_cmp[target_hart]);
	writel_relaxed(next_event >> 32,
		       (void *)(&plmt_time_cmp[target_hart]) + 0x04);
#endif

}

static struct sbi_timer_device plmt_timer = {
	.name = "ae350_plmt",
	.timer_value = plmt_timer_value,
	.timer_event_start = plmt_timer_event_start,
	.timer_event_stop = plmt_timer_event_stop
};

int plmt_warm_timer_init(void)
{
	u32 target_hart = current_hartid();

	if (plmt_time_hart_count <= target_hart || !plmt_time_base)
		return -1;

	/* Clear PLMT Time Compare */
#if __riscv_xlen == 64
	writeq_relaxed(-1ULL, &plmt_time_cmp[target_hart]);
#else
	writel_relaxed(-1UL, &plmt_time_cmp[target_hart]);
	writel_relaxed(-1UL, (void *)(&plmt_time_cmp[target_hart]) + 0x04);
#endif

	return 0;
}

int plmt_cold_timer_init(unsigned long base, u32 hart_count)
{
	plmt_time_hart_count = hart_count;
	plmt_time_base	     = (void *)base;
	plmt_time_val        = (u64 *)(plmt_time_base);
	plmt_time_cmp        = (u64 *)(plmt_time_base + 0x8);

	sbi_timer_set_device(&plmt_timer);

	return 0;
}
