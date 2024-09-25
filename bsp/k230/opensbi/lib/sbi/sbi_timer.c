/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_timer.h>

static unsigned long time_delta_off;
static u64 (*get_time_val)(void);
static const struct sbi_timer_device *timer_dev = NULL;

#if __riscv_xlen == 32
static u64 get_ticks(void)
{
	u32 lo, hi, tmp;
	__asm__ __volatile__("1:\n"
			     "rdtimeh %0\n"
			     "rdtime %1\n"
			     "rdtimeh %2\n"
			     "bne %0, %2, 1b"
			     : "=&r"(hi), "=&r"(lo), "=&r"(tmp));
	return ((u64)hi << 32) | lo;
}
#else
static u64 get_ticks(void)
{
	unsigned long n;

	__asm__ __volatile__("rdtime %0" : "=r"(n));
	return n;
}
#endif

static u64 get_platform_ticks(void)
{
	return timer_dev->timer_value();
}

u64 sbi_timer_value(void)
{
	if (get_time_val)
		return get_time_val();
	return 0;
}

u64 sbi_timer_virt_value(void)
{
	u64 *time_delta = sbi_scratch_offset_ptr(sbi_scratch_thishart_ptr(),
						 time_delta_off);

	return sbi_timer_value() + *time_delta;
}

u64 sbi_timer_get_delta(void)
{
	u64 *time_delta = sbi_scratch_offset_ptr(sbi_scratch_thishart_ptr(),
						 time_delta_off);

	return *time_delta;
}

void sbi_timer_set_delta(ulong delta)
{
	u64 *time_delta = sbi_scratch_offset_ptr(sbi_scratch_thishart_ptr(),
						 time_delta_off);

	*time_delta = (u64)delta;
}

void sbi_timer_set_delta_upper(ulong delta_upper)
{
	u64 *time_delta = sbi_scratch_offset_ptr(sbi_scratch_thishart_ptr(),
						 time_delta_off);

	*time_delta &= 0xffffffffULL;
	*time_delta |= ((u64)delta_upper << 32);
}

void sbi_timer_event_start(u64 next_event)
{
	if (timer_dev && timer_dev->timer_event_start)
		timer_dev->timer_event_start(next_event);
	csr_clear(CSR_MIP, MIP_STIP);
	csr_set(CSR_MIE, MIP_MTIP);
}

void sbi_timer_process(void)
{
	csr_clear(CSR_MIE, MIP_MTIP);
	csr_set(CSR_MIP, MIP_STIP);
}

const struct sbi_timer_device *sbi_timer_get_device(void)
{
	return timer_dev;
}

void sbi_timer_set_device(const struct sbi_timer_device *dev)
{
	if (!dev || timer_dev)
		return;

	timer_dev = dev;
	if (!get_time_val && timer_dev->timer_value)
		get_time_val = get_platform_ticks;
}

int sbi_timer_init(struct sbi_scratch *scratch, bool cold_boot)
{
	u64 *time_delta;
	const struct sbi_platform *plat = sbi_platform_ptr(scratch);

	if (cold_boot) {
		time_delta_off = sbi_scratch_alloc_offset(sizeof(*time_delta),
							  "TIME_DELTA");
		if (!time_delta_off)
			return SBI_ENOMEM;

		if (sbi_hart_has_feature(scratch, SBI_HART_HAS_TIME))
			get_time_val = get_ticks;
	} else {
		if (!time_delta_off)
			return SBI_ENOMEM;
	}

	time_delta = sbi_scratch_offset_ptr(scratch, time_delta_off);
	*time_delta = 0;

	return sbi_platform_timer_init(plat, cold_boot);
}

void sbi_timer_exit(struct sbi_scratch *scratch)
{
	if (timer_dev && timer_dev->timer_event_stop)
		timer_dev->timer_event_stop();

	csr_clear(CSR_MIP, MIP_STIP);
	csr_clear(CSR_MIE, MIP_MTIP);

	sbi_platform_timer_exit(sbi_platform_ptr(scratch));
}
