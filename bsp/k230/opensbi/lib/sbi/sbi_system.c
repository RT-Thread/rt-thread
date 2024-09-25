/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 *   Nick Kossifidis <mick@ics.forth.gr>
 */

#include <sbi/riscv_asm.h>
#include <sbi/sbi_bitops.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_hsm.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_system.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_init.h>

static const struct sbi_system_reset_device *reset_dev = NULL;

const struct sbi_system_reset_device *sbi_system_reset_get_device(void)
{
	return reset_dev;
}

void sbi_system_reset_set_device(const struct sbi_system_reset_device *dev)
{
	if (!dev || reset_dev)
		return;

	reset_dev = dev;
}

bool sbi_system_reset_supported(u32 reset_type, u32 reset_reason)
{
	if (reset_dev && reset_dev->system_reset_check &&
	    reset_dev->system_reset_check(reset_type, reset_reason))
		return TRUE;

	return FALSE;
}

#include <sbi/riscv_io.h>
void __noreturn sbi_system_reset(u32 reset_type, u32 reset_reason)
{
	ulong hbase = 0, hmask;
	u32 cur_hartid = current_hartid();
	struct sbi_domain *dom = sbi_domain_thishart_ptr();
	struct sbi_scratch *scratch = sbi_scratch_thishart_ptr();

	/* Send HALT IPI to every hart other than the current hart */
	while (!sbi_hsm_hart_interruptible_mask(dom, hbase, &hmask)) {
		if (hbase <= cur_hartid)
			hmask &= ~(1UL << (cur_hartid - hbase));
		if (hmask)
			sbi_ipi_send_halt(hmask, hbase);
		hbase += BITS_PER_LONG;
	}

	/* Stop current HART */
	sbi_hsm_hart_stop(scratch, FALSE);

	/* Platform specific reset if domain allowed system reset */
	if (dom->system_reset_allowed &&
	    reset_dev && reset_dev->system_reset)
		reset_dev->system_reset(reset_type, reset_reason);

	writew(0x5555, (void *)0x100000); // qemu poweroff

	/* If platform specific reset did not work then do sbi_exit() */
	sbi_exit(scratch);
}
